// EasyPDFCtrl.cpp : CEasyPDFCtrl ActiveX �ؼ����ʵ�֡�
#include <afxwin.h>
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
#include <afxdisp.h>
#include <MsHTML.h>

#pragma comment( lib, "wininet.lib" )

#include <regex>


IMPLEMENT_DYNCREATE(CEasyPDFCtrl, COleControl)


// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CEasyPDFCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// ����ӳ��

BEGIN_DISPATCH_MAP(CEasyPDFCtrl, COleControl)
	DISP_FUNCTION_ID(CEasyPDFCtrl, "Load", dispidLoad, Load, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPDFCtrl, "InvokeFunc", dispidInvokeFunc, InvokeFunc, VT_EMPTY, VTS_BSTR VTS_DISPATCH)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CEasyPDFCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CEasyPDFCtrl, 1)
	PROPPAGEID(CEasyPDFPropPage::guid)
END_PROPPAGEIDS(CEasyPDFCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CEasyPDFCtrl, "EASYPDF.EasyPDFCtrl.1",
	0x52805e94, 0x7a4, 0x42c9, 0x9c, 0xf8, 0xc8, 0x3c, 0xcb, 0xd9, 0xc0, 0xc1)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CEasyPDFCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DEasyPDF = { 0x7D6957D9, 0x8EC9, 0x40F2, { 0x85, 0x97, 0x85, 0x70, 0x62, 0xAF, 0x5F, 0xE5 } };
const IID IID_DEasyPDFEvents = { 0x5BAE4438, 0xFE58, 0x4131, { 0xBE, 0xF4, 0x74, 0x37, 0x4F, 0xE2, 0x8, 0x12 } };


// �ؼ�������Ϣ

static const DWORD _dwEasyPDFOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEasyPDFCtrl, IDS_EASYPDF, _dwEasyPDFOleMisc)



// CEasyPDFCtrl::CEasyPDFCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CEasyPDFCtrl ��ϵͳע�����

BOOL CEasyPDFCtrl::CEasyPDFCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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



// CEasyPDFCtrl::CEasyPDFCtrl - ���캯��

CEasyPDFCtrl::CEasyPDFCtrl()
{
	InitializeIIDs(&IID_DEasyPDF, &IID_DEasyPDFEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
	
}



// CEasyPDFCtrl::~CEasyPDFCtrl - ��������

CEasyPDFCtrl::~CEasyPDFCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CEasyPDFCtrl::DoPropExchange - �־���֧��

void CEasyPDFCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CEasyPDFCtrl::GetControlFlags -
// �Զ��� MFC �� ActiveX �ؼ�ʵ�ֵı�־��
//
DWORD CEasyPDFCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// �ؼ�ͨ������ԭ�豸�������е�
	// ԭʼ GDI ���󣬿����Ż����� OnDraw ������
	dwFlags |= canOptimizeDraw;
	return dwFlags;
}



// CEasyPDFCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CEasyPDFCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CEasyPDFCtrl ��Ϣ�������

void CEasyPDFCtrl::Load(LPCTSTR URL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

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

	m_Main.Create(IDD_MAIN, this);
	m_Main.AnalyzePDF(URL);
	m_Main.ShowWindow(SW_SHOW);

	
	// ��ȡ�û�������
	RECT ClientRect = { 0 };
	GetClientRect(&ClientRect);

	// ���öԻ������
	m_Main.MoveWindow(0, 0, ClientRect.right, ClientRect.bottom);
}

// CEasyPDFCtrl::OnDraw - ��ͼ����

void CEasyPDFCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	/*pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);*/
	if (!IsOptimizedDraw())
	{
		// ������֧���Ż���ͼ��

		// TODO: ������κ� GDI ����ѡ�뵽�豸������ *pdc �У�
		//		���ڴ˴��ָ���ǰѡ���Ķ���
		
	}
}

void CEasyPDFCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	/*RECT activeRect;
	GetClientRect(&activeRect);
	m_Main.MoveWindow(&activeRect);*/
}


int CEasyPDFCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetURL();

	return 0;
}


void CEasyPDFCtrl::GetURL()
{
	USES_CONVERSION;  

	IOleContainer* pContainer = NULL;
	IHTMLDocument* pDoc = NULL;
	m_pClientSite->GetContainer( &pContainer );
	if ( pContainer != NULL )
	pContainer->QueryInterface( IID_IHTMLDocument, (void**)&pDoc );

	HRESULT hresult;
	OLECHAR FAR* szMember = T2W(_T("Initilize"));

	DISPID dispid;
	DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};

	IDispatch * pdisp = NULL;
	pDoc->get_Script(&pdisp);
	hresult = pdisp->GetIDsOfNames(IID_NULL,&szMember,1, LOCALE_SYSTEM_DEFAULT,&dispid);
	hresult = pdisp->Invoke(dispid,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_METHOD,&dispparamsNoArgs, NULL, NULL, NULL);
	pContainer->Release();
}


void CEasyPDFCtrl::InvokeFunc(LPCTSTR FuncName, IDispatch* Func)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

}