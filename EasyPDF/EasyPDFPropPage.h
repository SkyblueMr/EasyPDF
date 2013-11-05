#pragma once

// EasyPDFPropPage.h : CEasyPDFPropPage 属性页类的声明。


// CEasyPDFPropPage : 有关实现的信息，请参阅 EasyPDFPropPage.cpp。

class CEasyPDFPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEasyPDFPropPage)
	DECLARE_OLECREATE_EX(CEasyPDFPropPage)

// 构造函数
public:
	CEasyPDFPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_EASYPDF };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

