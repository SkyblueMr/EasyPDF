// EasyPDFCtrl.cpp : CEasyPDFCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "EasyPDF.h"
#include "EasyPDFCtrl.h"
#include "EasyPDFPropPage.h"
#include "afxdialogex.h"
#include "PDFHelper.h"
#include "Gdiplusnew.h"
#include <Windows.h>
#include <wininet.h>
#include <atlimage.h>

#pragma comment( lib, "wininet.lib" )

#include <regex>


IMPLEMENT_DYNCREATE(CEasyPDFCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CEasyPDFCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_PAINT(125, OnStaticPaint)
END_MESSAGE_MAP()


// 调度映射

BEGIN_DISPATCH_MAP(CEasyPDFCtrl, COleControl)
	DISP_FUNCTION_ID(CEasyPDFCtrl, "Load", dispidLoad, Load, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CEasyPDFCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CEasyPDFCtrl, 1)
	PROPPAGEID(CEasyPDFPropPage::guid)
END_PROPPAGEIDS(CEasyPDFCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CEasyPDFCtrl, "EASYPDF.EasyPDFCtrl.1",
	0x52805e94, 0x7a4, 0x42c9, 0x9c, 0xf8, 0xc8, 0x3c, 0xcb, 0xd9, 0xc0, 0xc1)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CEasyPDFCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DEasyPDF = { 0x7D6957D9, 0x8EC9, 0x40F2, { 0x85, 0x97, 0x85, 0x70, 0x62, 0xAF, 0x5F, 0xE5 } };
const IID IID_DEasyPDFEvents = { 0x5BAE4438, 0xFE58, 0x4131, { 0xBE, 0xF4, 0x74, 0x37, 0x4F, 0xE2, 0x8, 0x12 } };


// 控件类型信息

static const DWORD _dwEasyPDFOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEasyPDFCtrl, IDS_EASYPDF, _dwEasyPDFOleMisc)



// CEasyPDFCtrl::CEasyPDFCtrlFactory::UpdateRegistry -
// 添加或移除 CEasyPDFCtrl 的系统注册表项

BOOL CEasyPDFCtrl::CEasyPDFCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EASYPDF,
			IDB_EASYPDF,
			afxRegApartmentThreading,
			_dwEasyPDFOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CEasyPDFCtrl::CEasyPDFCtrl - 构造函数

CEasyPDFCtrl::CEasyPDFCtrl()
{
	InitializeIIDs(&IID_DEasyPDF, &IID_DEasyPDFEvents);
	// TODO: 在此初始化控件的实例数据。
	
}



// CEasyPDFCtrl::~CEasyPDFCtrl - 析构函数

CEasyPDFCtrl::~CEasyPDFCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CEasyPDFCtrl::DoPropExchange - 持久性支持

void CEasyPDFCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CEasyPDFCtrl::GetControlFlags -
// 自定义 MFC 的 ActiveX 控件实现的标志。
//
DWORD CEasyPDFCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// 控件通过不还原设备上下文中的
	// 原始 GDI 对象，可以优化它的 OnDraw 方法。
	dwFlags |= canOptimizeDraw;
	return dwFlags;
}



// CEasyPDFCtrl::OnResetState - 将控件重置为默认状态

void CEasyPDFCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CEasyPDFCtrl 消息处理程序

#define MAX_BUFFER 102400

char * Download(const char * URL, ULONG &Number)
{
	char * Data = new char[MAX_BUFFER];

	HINTERNET hSession =  InternetOpen((LPCWSTR)"IE", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
	if (NULL != hSession)
	{
		HINTERNET InternalHandle = InternetOpenUrlA(hSession, URL, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
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

ATL::CImage img;
void CEasyPDFCtrl::Load(LPCTSTR URL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	/*ULONG size = 0;
	char * heap = Download("http://localhost:8080/1.pdf", size);

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
				img.Destroy();
			
				img.Load(pStream);
				rect.top = (i * 1024) + 10;
				rect.bottom = ((i + 1) * 1024);
				rect.right = 1024;
				img.Draw(cdc->m_hDC, rect);
				pStream->Release();
			}
			GlobalFree(hGlobal);	
			ReleaseDC(cdc);
		}
	}*/

	/*ULONG size = 0;
	char * heap = Download("http://news.xinhuanet.com/legal/2013-11/01/125632558_11n.jpg", size);

	CDC * cdc = GetDC();
	HGLOBAL hGlobal = ::GlobalAlloc(GHND, MAX_BUFFER);
    LPBYTE  lpByte  = (LPBYTE)::GlobalLock(hGlobal);
	CopyMemory(lpByte, heap, MAX_BUFFER);
    ::GlobalUnlock(hGlobal);
    IStream* pStream = NULL;
    if ( SUCCEEDED(::CreateStreamOnHGlobal(hGlobal, FALSE, &pStream)) )
    {
        img.Destroy();
        img.Load(pStream);
		RECT rect = { 0 };
		rect.bottom = img.GetHeight();
		rect.right = img.GetWidth();
		img.Draw(cdc->m_hDC, rect);
        pStream->Release();
    }
    GlobalFree(hGlobal);	
	ReleaseDC(cdc);*/
	Display();
}

// CEasyPDFCtrl::OnDraw - 绘图函数

Gdiplus::Bitmap * girl;
CDC * sDC;

void CEasyPDFCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	/*pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);*/
	if (!IsOptimizedDraw())
	{
		// 容器不支持优化绘图。

		// TODO: 如果将任何 GDI 对象选入到设备上下文 *pdc 中，
		//		请在此处恢复先前选定的对象。
		/*Gdiplus::Bitmap * imgs = new Gdiplus::Bitmap(_T("C:/Users/Administrator/Desktop/Other/girl.jpg"));

		CDC * dc = GetDC();

		Gdiplus::Graphics * g = new Gdiplus::Graphics(dc->m_hDC);
		g->ScaleTransform(0.5, 0.5);
		g->DrawImage(imgs, 0, 0);
		g->DrawImage(imgs, 0, 650);

		ReleaseDC(dc);*/
		CStatic * cStatic = (CStatic*)GetDlgItem(125);
		CScrollBar * cScroll = (CScrollBar*)GetDlgItem(123);
		if(NULL == cStatic)
		{
			CStatic * panel = new CStatic();
			ASSERT_VALID(panel);
			RECT rect = { 0 };
			rect.bottom = 400;
			rect.right = 400;
			panel->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_BITMAP, rect, this, 125);
			sDC = panel->GetDC();
			Gdiplus::Bitmap * imgs = new Gdiplus::Bitmap(_T("C:/Users/Administrator/Desktop/Other/war3.jpg"));
			girl = imgs;

			CScrollBar * Scroll = new CScrollBar();
			ASSERT_VALID(Scroll);
			RECT ScrollRect;
			ScrollRect.top = 0;
			ScrollRect.right = 500;
			Scroll->Create(WS_CHILD | WS_VISIBLE, ScrollRect, panel, 123);
			Scroll->SetScrollRange(0, 100);
			Scroll->SetScrollPos(0);
			Scroll->ShowScrollBar();
		}

		Gdiplus::Graphics * g = Gdiplus::Graphics::FromHDC(sDC->m_hDC);
		g->ScaleTransform(0.5, 0.5);
		g->DrawImage(girl, 0, -200, 400, 400);
		g->DrawImage(girl, 0, 210, 400, 400);
		g->DrawImage(girl, 0, 620, 400, 400);
		
	}
}

void CEasyPDFCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	/*RECT activeRect;
	GetClientRect(&activeRect);
	m_Main.MoveWindow(&activeRect);*/
}


int CEasyPDFCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//m_Main.Create(IDD_MAIN, this);

	return 0;
}

void CEasyPDFCtrl::Display()
{  
    // Bitmap * dest = new Bitmap(_T("C:/Users/Administrator/Desktop/Other/girl.jpg"));
	
} 

void CEasyPDFCtrl::OnStaticPaint()
{
	MessageBox(_T("load"));
	if(NULL == girl)
	{
		MessageBox(_T("load"));
		Gdiplus::Bitmap * imgs = new Gdiplus::Bitmap(_T("C:/Users/Administrator/Desktop/Other/war3.jpg"));
		girl = imgs;
	}

	Gdiplus::Graphics * g = new Gdiplus::Graphics(sDC->m_hDC);
	g->ScaleTransform(0.5, 0.5);
	g->DrawImage(girl, 0, 0);
	g->DrawImage(girl, 0, 800);
}

