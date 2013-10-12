// EasyPDFPropPage.cpp : CEasyPDFPropPage 属性页类的实现。

#include "stdafx.h"
#include "EasyPDF.h"
#include "EasyPDFPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPDFPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CEasyPDFPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CEasyPDFPropPage, "EASYPDF.EasyPDFPropPage.1",
	0x35c1043a, 0x61ec, 0x4cac, 0xa6, 0xfa, 0x92, 0xa8, 0x4e, 0xfa, 0x13, 0xf)



// CEasyPDFPropPage::CEasyPDFPropPageFactory::UpdateRegistry -
// 添加或移除 CEasyPDFPropPage 的系统注册表项

BOOL CEasyPDFPropPage::CEasyPDFPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EASYPDF_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CEasyPDFPropPage::CEasyPDFPropPage - 构造函数

CEasyPDFPropPage::CEasyPDFPropPage() :
	COlePropertyPage(IDD, IDS_EASYPDF_PPG_CAPTION)
{
}



// CEasyPDFPropPage::DoDataExchange - 在页和属性间移动数据

void CEasyPDFPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEasyPDFPropPage 消息处理程序
