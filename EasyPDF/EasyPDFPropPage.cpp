// EasyPDFPropPage.cpp : CEasyPDFPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "EasyPDF.h"
#include "EasyPDFPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPDFPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CEasyPDFPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CEasyPDFPropPage, "EASYPDF.EasyPDFPropPage.1",
	0x35c1043a, 0x61ec, 0x4cac, 0xa6, 0xfa, 0x92, 0xa8, 0x4e, 0xfa, 0x13, 0xf)



// CEasyPDFPropPage::CEasyPDFPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CEasyPDFPropPage ��ϵͳע�����

BOOL CEasyPDFPropPage::CEasyPDFPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EASYPDF_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CEasyPDFPropPage::CEasyPDFPropPage - ���캯��

CEasyPDFPropPage::CEasyPDFPropPage() :
	COlePropertyPage(IDD, IDS_EASYPDF_PPG_CAPTION)
{
}



// CEasyPDFPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CEasyPDFPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEasyPDFPropPage ��Ϣ�������
