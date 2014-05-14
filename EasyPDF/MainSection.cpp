// MainSection.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EasyPDF.h"
#include "MainSection.h"
#include "afxdialogex.h"
#include "PDFHelper.h"
#include "Gdiplusnew.h"
#include <Windows.h>
#include <wininet.h>
#include <atlimage.h>

#pragma comment( lib, "wininet.lib" )

#include <regex>


// CMainSection �Ի���

IMPLEMENT_DYNAMIC(CMainSection, CDialogEx)

CMainSection::CMainSection(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainSection::IDD, pParent)
{
	
}

CMainSection::~CMainSection()
{
}

void CMainSection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLCONTENT, m_Scroll);
}


BEGIN_MESSAGE_MAP(CMainSection, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
//	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLCONTENT, &CMainSection::OnNMThemeChangedScrollcontent)
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_MOUSEWHEEL()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMainSection ��Ϣ�������

std::vector<Gdiplus::Bitmap*> * PicSet = new std::vector<Gdiplus::Bitmap*>();

int PicWidth = 1400;	// ͼƬ��
int PicHeight = 1400;	// ͼƬ��
int ScreenHeight = 0;	// ��Ļ��
long Total = 0;	// �ܸ߶�
long Curren = 0;	// ��ǰ����λ��

void CMainSection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CDC BackCDC;	
	CDC * FrontDC = GetDC();
	CBitmap MemBitmap;
	BackCDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(FrontDC, PicWidth, Total);
	SelectObject(BackCDC, MemBitmap);
	Gdiplus::Graphics * g = Gdiplus::Graphics::FromHDC(BackCDC.GetSafeHdc());
	g->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed);

	int Height = ScreenHeight * 2;
	int CurrenTemp = Curren;
	for(size_t i = 0; i < PicSet->size(); i++)
	{
		
		g->DrawImage(PicSet->at(i), 0, CurrenTemp, PicWidth, PicHeight);
		CurrenTemp = CurrenTemp + PicHeight + 10;
		Height = Height - PicWidth;
	}

	FrontDC->BitBlt(0, 0, PicWidth, Total, &BackCDC, 0, 0, SRCCOPY);
	BackCDC.DeleteDC();
}


#define MAX_BUFFER 51200000  // 50MB

// MAX_BUFFER����ÿ������С�ڵ���50M���ļ�������������ʧ��
char * CMainSection::Download(LPCTSTR URL, ULONG &Number)
{
	char * Data = new char[MAX_BUFFER];

	HINTERNET hSession =  InternetOpen((LPCTSTR)"IE", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
	if (NULL != hSession)
	{
		HINTERNET InternalHandle = InternetOpenUrl(hSession, URL, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		DWORD err =GetLastError();
		if(NULL != InternalHandle)
		{
			InternetReadFile(InternalHandle, Data, MAX_BUFFER, &Number);
			InternetCloseHandle(InternalHandle);
			InternalHandle = NULL;
		}

		InternetCloseHandle(hSession);
		hSession = NULL;
	}
	
	return Data;
}


void CMainSection::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	// ��ȡ�Ի������
	
}


int CMainSection::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	

	return 0;
}


void CMainSection::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMainSection::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int Pos = m_Scroll.GetScrollPos();
	if((SB_LINEUP == nSBCode || SB_PAGEUP == nSBCode) && (Pos >= 0))
	{
		m_Scroll.SetScrollPos(Pos - 100);
		Curren = Curren + 100;

		if(Curren > 0)
		{
			Curren = 0;
		}

		Invalidate();	// �ػ�ͻ���
	}

	if((SB_LINEDOWN == nSBCode || SB_PAGEDOWN == nSBCode))
	{
		m_Scroll.SetScrollPos(Pos + 100);
		Curren = Curren - 100;

		Invalidate();	// �ػ�ͻ���
	}

	if(SB_THUMBPOSITION == nSBCode)
	{
		m_Scroll.SetScrollPos(nPos);
	}

	if(SB_THUMBTRACK == nSBCode)
	{
		m_Scroll.SetScrollPos(nPos);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}



BOOL CMainSection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// ��ʼ��GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//�����Ļ�Ŀ�����ֵ��
	int Width = GetSystemMetrics (SM_CXSCREEN);

	//�����Ļ�ĸߣ�����ֵ��
	int Height = GetSystemMetrics(SM_CYSCREEN);	

	m_Scroll.SetWindowPos(NULL, Width - 38, 0, 18, Height - 100, SWP_SHOWWINDOW);

	m_Scroll.SetScrollRange(1, Total);

	Curren = 0;

	m_Scroll.ModifyStyle(0, BS_OWNERDRAW | BS_RIGHT, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CMainSection::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int Pos = m_Scroll.GetScrollPos();
	if(zDelta > 0)
	{
		m_Scroll.SetScrollPos(Pos - 100);
		Curren = Curren + 100;

		if(Curren > 0)
		{
			Curren = 0;
		}

		Invalidate();	// �ػ�ͻ���
	}
	else
	{
		m_Scroll.SetScrollPos(Pos + 100);
		Curren = Curren - 100;

		if(Curren < (Curren - PicHeight))
		{
			MessageBox(_T("ok"));
		}
		Invalidate();	// �ػ�ͻ���
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CMainSection::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// return CDialogEx::OnEraseBkgnd(pDC);
	return FALSE;
}

void CMainSection::AnalyzePDF(LPCTSTR URL)
{
	ULONG size = 0;
	CString s = URL;
	char * heap = Download(URL, size);

	std::vector<std::string> Set;
	std::string str(heap, size);
	Set.push_back(str);
	PDFHelper * pdf = new PDFHelper(Set, "admin");
	if(pdf->Set.size() > 0)
	{
		// this->MoveWindow(0, 0, 1024, 768);

		RECT rect = { 0 };
		long h = 0;
		for(size_t i = 0; i < pdf->Set.size(); i++)
		{
			PicInfo pic = pdf->Set[i];

			CDC * cdc = GetDC();
			HGLOBAL hGlobal = ::GlobalAlloc(GHND, MAX_BUFFER);
			LPBYTE  lpByte  = (LPBYTE)::GlobalLock(hGlobal);
			memcpy(lpByte, pic.buff.c_str(), pic.buff.size());
			::GlobalUnlock(hGlobal);
			IStream* pStream = NULL;
			if ( SUCCEEDED(::CreateStreamOnHGlobal(hGlobal, FALSE, &pStream)) )
			{
				Gdiplus::Bitmap * imgs = new Gdiplus::Bitmap(pStream);
				PicSet->push_back(imgs);
				Total += PicWidth + 10;
			}
			GlobalFree(hGlobal);	
			ReleaseDC(cdc);
		}
	}
}