// MainSection.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EasyPDF.h"
#include "MainSection.h"
#include "afxdialogex.h"


// CMainSection �Ի���

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


// CMainSection ��Ϣ�������


void CMainSection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
