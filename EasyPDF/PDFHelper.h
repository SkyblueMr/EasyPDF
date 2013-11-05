#pragma once
#include <vector>
#include <string>

#ifndef MY_MUPDF_CONVERT_PDF_PNG
#define MY_MUPDF_CONVERT_PDF_PNG


extern "C" 
{
#include "mupdf\fitz.h"
#include "mupdf\fitz-internal.h"
}

#pragma comment(lib, "libmupdf.lib")

typedef struct _PDFContent
{
	std::string Title;
	std::vector<std::string> Content;
} PDFContent;

typedef struct _PicInfo
{
	int width;
	int height;
	std::string buff;
} PicInfo;

class PDFHelper
{
private:
	static const fz_matrix fz_identity;
	static fz_colorspace k_device_rgb;
	fz_colorspace *fz_device_rgb;

	fz_document * m_doc;
	fz_stream * m_pStream;
	fz_context * m_ctx;

	int uselist;
	int alphabits;

	char output[1024];
	float resolution;
	float rotation;
	int res_specified;
	int width;
	int height;
	int fit;
	fz_colorspace *colorspace;
	int savealpha;
	int invert;
	float gamma_value;

	

public:
	PDFHelper(std::vector<std::string> PdfSet, char * password);
	bool PdfToPng(unsigned char * buffer, int len, char * password, int &pageNum, std::vector<PicInfo> &Set);
	PicInfo drawpage(fz_context *ctx, fz_document *doc, int pagenum);
	~PDFHelper(void);

	std::vector<PDFContent> PDFSet;
	std::vector<PicInfo> Set;
};


#endif