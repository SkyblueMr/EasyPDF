#pragma once


// CMainSection 对话框

class CMainSection : public CDialogEx
{
	DECLARE_DYNAMIC(CMainSection)

public:
	CMainSection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainSection();

// 对话框数据
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	bool m_IsPlay;
	ATL::CImage * m_Img;
	afx_msg void OnBnClickedButton1();
};
