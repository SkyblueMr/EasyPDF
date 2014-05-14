// MainSection.cpp : 实现文件
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


// CMainSection 对话框

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


// CMainSection 消息处理程序

std::vector<Gdiplus::Bitmap*> * PicSet = new std::vector<Gdiplus::Bitmap*>();

int PicWidth = 1400;	// 图片宽
int PicHeight = 1400;	// 图片高
int ScreenHeight = 0;	// 屏幕高
long Total = 0;	// 总高度
long Curren = 0;	// 当前顶层位置

void CMainSection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

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

// MAX_BUFFER限制每次下载小于等于50M的文件，超过则下载失败
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

	// TODO: 在此处添加消息处理程序代码

	// 获取对话框矩形
	
}


int CMainSection::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	

	return 0;
}


void CMainSection::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMainSection::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int Pos = m_Scroll.GetScrollPos();
	if((SB_LINEUP == nSBCode || SB_PAGEUP == nSBCode) && (Pos >= 0))
	{
		m_Scroll.SetScrollPos(Pos - 100);
		Curren = Curren + 100;

		if(Curren > 0)
		{
			Curren = 0;
		}

		Invalidate();	// 重绘客户区
	}

	if((SB_LINEDOWN == nSBCode || SB_PAGEDOWN == nSBCode))
	{
		m_Scroll.SetScrollPos(Pos + 100);
		Curren = Curren - 100;

		Invalidate();	// 重绘客户区
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

	// 初始化GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// TODO:  在此添加额外的初始化
	//获得屏幕的宽（像素值）
	int Width = GetSystemMetrics (SM_CXSCREEN);

	//获得屏幕的高（像素值）
	int Height = GetSystemMetrics(SM_CYSCREEN);	

	m_Scroll.SetWindowPos(NULL, Width - 38, 0, 18, Height - 100, SWP_SHOWWINDOW);

	m_Scroll.SetScrollRange(1, Total);

	Curren = 0;

	m_Scroll.ModifyStyle(0, BS_OWNERDRAW | BS_RIGHT, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CMainSection::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int Pos = m_Scroll.GetScrollPos();
	if(zDelta > 0)
	{
		m_Scroll.SetScrollPos(Pos - 100);
		Curren = Curren + 100;

		if(Curren > 0)
		{
			Curren = 0;
		}

		Invalidate();	// 重绘客户区
	}
	else
	{
		m_Scroll.SetScrollPos(Pos + 100);
		Curren = Curren - 100;

		if(Curren < (Curren - PicHeight))
		{
			MessageBox(_T("ok"));
		}
		Invalidate();	// 重绘客户区
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CMainSection::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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