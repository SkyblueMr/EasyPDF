#pragma once

// EasyPDFPropPage.h : CEasyPDFPropPage ����ҳ���������


// CEasyPDFPropPage : �й�ʵ�ֵ���Ϣ������� EasyPDFPropPage.cpp��

class CEasyPDFPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEasyPDFPropPage)
	DECLARE_OLECREATE_EX(CEasyPDFPropPage)

// ���캯��
public:
	CEasyPDFPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_EASYPDF };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

