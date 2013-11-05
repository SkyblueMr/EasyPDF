#pragma once

// EasyPDFCtrl.h : CEasyPDFCtrl ActiveX �ؼ����������

#include "MainSection.h"

// CEasyPDFCtrl : �й�ʵ�ֵ���Ϣ������� EasyPDFCtrl.cpp��

class CEasyPDFCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEasyPDFCtrl)

// ���캯��
public:
	CEasyPDFCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// ʵ��
protected:
	~CEasyPDFCtrl();

	DECLARE_OLECREATE_EX(CEasyPDFCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CEasyPDFCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEasyPDFCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CEasyPDFCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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

