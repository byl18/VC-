#if !defined(AFX_HIGHSCORE_H__3E1F11B8_02D7_4C68_8393_D4FEC5DC0D1F__INCLUDED_)
#define AFX_HIGHSCORE_H__3E1F11B8_02D7_4C68_8393_D4FEC5DC0D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HIGHSCORE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHIGHSCORE dialog

class CHIGHSCORE : public CDialog
{
// Construction
public:
	CHIGHSCORE(CWnd* pParent = NULL);   // standard constructor

	void Sort(int rank);
// Dialog Data
	//{{AFX_DATA(CHIGHSCORE)
	enum { IDD = IDD_HIGHSCORE };
	int	m_first_time;
	CString	m_first_name;
	CString	m_second_name;
	int	m_second_time;
	CString	m_third_name;
	int	m_third_time;
	//}}AFX_DATA
	char p[3][20];
	int q[3];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHIGHSCORE)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHIGHSCORE)
	afx_msg void OnIdGaofen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGHSCORE_H__3E1F11B8_02D7_4C68_8393_D4FEC5DC0D1F__INCLUDED_)
