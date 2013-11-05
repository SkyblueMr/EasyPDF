#pragma once

// EasyPDFCtrl.h : CEasyPDFCtrl ActiveX 控件类的声明。

#include "MainSection.h"

// CEasyPDFCtrl : 有关实现的信息，请参阅 EasyPDFCtrl.cpp。

class CEasyPDFCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEasyPDFCtrl)

// 构造函数
public:
	CEasyPDFCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// 实现
protected:
	~CEasyPDFCtrl();

	DECLARE_OLECREATE_EX(CEasyPDFCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CEasyPDFCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEasyPDFCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CEasyPDFCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidLoad = 1L
	};
protected:
	void Load(LPCTSTR URL);
	void Display();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStaticPaint( );
	CMainSection m_Main;
};

