#pragma once
#include "afxwin.h"

// CMainSection 对话框

class CMainSection : public CDialogEx
{
	DECLARE_DYNAMIC(CMainSection)

public:
	CMainSection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainSection();
	char * Download(LPCTSTR URL, ULONG &Number);
	void AnalyzePDF(LPCTSTR URL);

// 对话框数据
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void DrawBackBuff();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CScrollBar m_Scroll;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnNMThemeChangedScrollcontent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
