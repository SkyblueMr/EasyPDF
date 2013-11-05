// MainSection.cpp : 实现文件
//

#include "stdafx.h"
#include "EasyPDF.h"
#include "MainSection.h"
#include "afxdialogex.h"


// CMainSection 对话框

IMPLEMENT_DYNAMIC(CMainSection, CDialogEx)

CMainSection::CMainSection(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainSection::IDD, pParent)
{
	m_IsPlay = false;
}

CMainSection::~CMainSection()
{
}

void CMainSection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainSection, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainSection::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMainSection 消息处理程序


void CMainSection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if(m_IsPlay)
	{
		CDC * cdc = this->GetWindowDC();
		TextOut(cdc->m_hDC, 10, 10, _T("Hello world"), 10);
		RECT rect = {0};
		rect.bottom = m_Img->GetHeight();
		rect.right = m_Img->GetWidth();
		m_Img->Draw(cdc->m_hDC, rect);
		ReleaseDC(cdc);
	}
}


void CMainSection::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
