#include "StdAfx.h"
#include "PDFHelper.h"
#include <zlib.h>

const int ImgQualiry = 90;

static void rgb_to_rgb(fz_context *ctx, fz_colorspace *cs, float *rgb, float *xyz)
{
	xyz[0] = rgb[0];
	xyz[1] = rgb[1];
	xyz[2] = rgb[2];
}

const fz_matrix PDFHelper::fz_identity = { 1, 0, 0, 1, 0, 0 };
fz_colorspace PDFHelper::k_device_rgb = { {-1, fz_free_colorspace_imp}, 0, "DeviceRGB", 3, rgb_to_rgb, rgb_to_rgb };

PDFHelper::PDFHelper(std::vector<std::string> PdfSet, char * password)
{
	fz_device_rgb = &k_device_rgb;

	uselist = 1;
	alphabits = 8;

	//output = NULL;
	resolution = 72;
	rotation = 0;
	res_specified = 0;
	width = 0;
	height = 0;
	fit = 0;
	colorspace = NULL;
	savealpha = 0;
	invert = 0;
	gamma_value = 1;

	m_doc = NULL;
	m_ctx = NULL;

	for(std::vector<std::string>::iterator i = PdfSet.begin(); i != PdfSet.end(); i++)
	{
		int num = 0;
		PdfToPng((unsigned char*)(*i).c_str(), (*i).size(), password, num, Set);
	}
}

bool PDFHelper::PdfToPng(unsigned char * buffer, int len, char * password, int &pageNum, std::vector<PicInfo> &Set)
{
	m_ctx = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
	if (!m_ctx)
	{
		return false;
	}

	fz_try(m_ctx)
	{
		fz_set_aa_level(m_ctx, alphabits);
		colorspace = fz_device_rgb;

		m_pStream = fz_open_memory(m_ctx, buffer, len);

		if (m_pStream)
		{
			m_doc = fz_open_document_with_stream(m_ctx, ".pdf", m_pStream);
			int n = fz_needs_password(m_doc);
			if(n > 0)
			{
				int j = fz_authenticate_password(m_doc, password);
				if(j > 0)
				{

				}
			}
		}

		if (!m_doc)
		{
			return false;
		}

		int pn = fz_count_pages(m_doc);
		pageNum = pn;
		for (int i=0; i<pn; ++i)
		{
			fz_page *page = fz_load_page(m_doc, i);
			// fz_rect bound = fz_bound_page(m_doc, page);

			//PDF-->PNG
			PicInfo pic = drawpage(m_ctx, m_doc, i+1);
			Set.push_back(pic);

			fz_free_page(m_doc, page);
			page = NULL;
		}	
	}
	fz_catch(m_ctx)
	{
		return false;
	}

	return true;
}


static inline void big32(unsigned char *buf, unsigned int v)
{
	buf[0] = (v >> 24) & 0xff;
	buf[1] = (v >> 16) & 0xff;
	buf[2] = (v >> 8) & 0xff;
	buf[3] = (v) & 0xff;
}

static inline void put32(unsigned int v, FILE *fp)
{
	putc(v >> 24, fp);
	putc(v >> 16, fp);
	putc(v >> 8, fp);
	putc(v, fp);
}

static inline void fz_write(std::string &out, char * data, int x)
{
	out.append(data, x);
}

static inline void fz_write_int32be(std::string &out, int x)
{
	char data[4];

	data[0] = x>>24;
	data[1] = x>>16;
	data[2] = x>>8;
	data[3] = x;
	out.append(data, 4);
}

static void putchunk(char * tag, unsigned char * data, int size, std::string & out)
{
	unsigned int sum;
	fz_write_int32be(out, size);
	fz_write(out, tag, 4);
	fz_write(out, (char*)data, size);
	sum = crc32(0, NULL, 0);
	sum = crc32(sum, (unsigned char*)tag, 4);
	sum = crc32(sum, data, size);
	fz_write_int32be(out, sum);
}

PicInfo fz_write_pngs(fz_context *ctx, fz_pixmap *pixmap, int savealpha)
{
	static const unsigned char pngsig[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
	unsigned char head[13];
	unsigned char *udata = NULL;
	unsigned char *cdata = NULL;
	unsigned char *sp, *dp;
	uLong usize = 0, csize = 0;
	int y = 0, x = 0, k = 0, sn = 0, dn = 0;
	int color = 0;
	int err = 0;

	fz_var(udata);
	fz_var(cdata);

	if (pixmap->n != 1 && pixmap->n != 2 && pixmap->n != 4)
		fz_throw(ctx, "pixmap must be grayscale or rgb to write as png");

	sn = pixmap->n;
	dn = pixmap->n;
	if (!savealpha && dn > 1)
		dn--;

	switch (dn)
	{
	default:
	case 1: color = 0; break;
	case 2: color = 4; break;
	case 3: color = 2; break;
	case 4: color = 6; break;
	}

	usize = (pixmap->w * dn + 1) * pixmap->h;
	csize = compressBound(usize);
	fz_try(ctx)
	{
		udata = (unsigned char *)fz_malloc(ctx, usize);
		cdata = (unsigned char *)fz_malloc(ctx, csize);
	}
	fz_catch(ctx)
	{
		fz_free(ctx, udata);
		fz_rethrow(ctx);
	}

	sp = pixmap->samples;
	dp = udata;
	for (y = 0; y < pixmap->h; y++)
	{
		*dp++ = 1; /* sub prediction filter */
		for (x = 0; x < pixmap->w; x++)
		{
			for (k = 0; k < dn; k++)
			{
				if (x == 0)
					dp[k] = sp[k];
				else
					dp[k] = sp[k] - sp[k-sn];
			}
			sp += sn;
			dp += dn;
		}
	}

	err = compress(cdata, &csize, udata, usize);
	if (err != Z_OK)
	{
		fz_free(ctx, udata);
		fz_free(ctx, cdata);
		fz_throw(ctx, "cannot compress image data");
	}

	big32(head+0, pixmap->w);
	big32(head+4, pixmap->h);
	head[8] = 8; /* depth */
	head[9] = color;
	head[10] = 0; /* compression */
	head[11] = 0; /* filter */
	head[12] = 0; /* interlace */

	std::string buff;
	fz_write(buff, (char*)pngsig, 8);
	putchunk("IHDR", head, 13, buff);
	putchunk("IDAT", cdata, csize, buff);
	putchunk("IEND", head, 0, buff);

	fz_free(ctx, udata);
	fz_free(ctx, cdata);

	PicInfo pic;
	pic.buff = buff;
	pic.width = pixmap->w;
	pic.height = pixmap->h;

	return pic;
}


PicInfo PDFHelper::drawpage(fz_context *ctx, fz_document *doc, int pagenum)
{
	fz_page *page;
	fz_display_list *list = NULL;
	fz_device *dev = NULL;
	PicInfo pic;	

	fz_var(list);
	fz_var(dev);

	fz_try(ctx)
	{
		page = fz_load_page(doc, pagenum - 1);
	}
	fz_catch(ctx)
	{
		fz_throw(ctx, "cannot load page %d", pagenum);
	}

	if (uselist)
	{
		fz_try(ctx)
		{
			list = fz_new_display_list(ctx);
			dev = fz_new_list_device(ctx, list);
			fz_run_page(doc, page, dev, fz_identity, NULL);
		}
		fz_catch(ctx)
		{
			fz_free_device(dev);
			fz_free_display_list(ctx, list);
			fz_free_page(doc, page);
			fz_throw(ctx, "cannot draw page %d", pagenum);
		}
		fz_free_device(dev);
		dev = NULL;
	}

	if (output)
	{
		float zoom;
		fz_matrix ctm;
		fz_rect bounds, bounds2;
		fz_bbox bbox;
		fz_pixmap *pix = NULL;
		int w, h;

		fz_var(pix);

		bounds = fz_bound_page(doc, page);
		zoom = resolution / ImgQualiry;
		ctm = fz_scale(zoom, zoom);
		ctm = fz_concat(ctm, fz_rotate(rotation));
		bounds2 = fz_transform_rect(ctm, bounds);
		bbox = fz_round_rect(bounds2);
		/* Make local copies of our width/height */
		w = width;
		h = height;
		/* If a resolution is specified, check to see whether w/h are
		 * exceeded; if not, unset them. */
		if (res_specified)
		{
			int t;
			t = bbox.x1 - bbox.x0;
			if (w && t <= w)
				w = 0;
			t = bbox.y1 - bbox.y0;
			if (h && t <= h)
				h = 0;
		}
		/* Now w or h will be 0 unless then need to be enforced. */
		if (w || h)
		{
			float scalex = w/(bounds2.x1-bounds2.x0);
			float scaley = h/(bounds2.y1-bounds2.y0);

			if (fit)
			{
				if (w == 0)
					scalex = 1.0f;
				if (h == 0)
					scaley = 1.0f;
			}
			else
			{
				if (w == 0)
					scalex = scaley;
				if (h == 0)
					scaley = scalex;
			}
			if (!fit)
			{
				if (scalex > scaley)
					scalex = scaley;
				else
					scaley = scalex;
			}
			ctm = fz_concat(ctm, fz_scale(scalex, scaley));
			bounds2 = fz_transform_rect(ctm, bounds);
		}
		bbox = fz_round_rect(bounds2);

		/* TODO: banded rendering and multi-page ppm */

		fz_try(ctx)
		{
			pix = fz_new_pixmap_with_bbox(ctx, colorspace, bbox);

			if (savealpha)
				fz_clear_pixmap(ctx, pix);
			else
				fz_clear_pixmap_with_value(ctx, pix, 255);

			dev = fz_new_draw_device(ctx, pix);
			if (list)
				fz_run_display_list(list, dev, ctm, bbox, NULL);
			else
				fz_run_page(doc, page, dev, ctm, NULL);
			fz_free_device(dev);
			dev = NULL;

			if (invert)
				fz_invert_pixmap(ctx, pix);
			if (gamma_value != 1)
				fz_gamma_pixmap(ctx, pix, gamma_value);

			if (savealpha)
				fz_unmultiply_pixmap(ctx, pix);
			int size = fz_pixmap_size(ctx, pix);

			if (output)
			{
				pic = fz_write_pngs(ctx, pix, savealpha);
			}

			fz_drop_pixmap(ctx, pix);
		}
		fz_catch(ctx)
		{
			fz_free_device(dev);
			fz_drop_pixmap(ctx, pix);
			fz_free_display_list(ctx, list);
			fz_free_page(doc, page);
			fz_rethrow(ctx);
		}
	}

	if (list)
		fz_free_display_list(ctx, list);

	fz_free_page(doc, page);

	fz_flush_warnings(ctx);

	return pic;
}

PDFHelper::~PDFHelper(void)
{
}
