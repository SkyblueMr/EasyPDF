#pragma once


// CMainSection �Ի���

class CMainSection : public CDialogEx
{
	DECLARE_DYNAMIC(CMainSection)

public:
	CMainSection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainSection();

// �Ի�������
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	bool m_IsPlay;
	ATL::CImage * m_Img;
	afx_msg void OnBnClickedButton1();
};
