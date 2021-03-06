#if !defined(AFX_GAMESIZE_H__552029C6_8A88_4BC4_9FB6_D3EC17918A42__INCLUDED_)
#define AFX_GAMESIZE_H__552029C6_8A88_4BC4_9FB6_D3EC17918A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GAMESIZE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GAMESIZE dialog

class GAMESIZE : public CDialog
{
// Construction
public:
	GAMESIZE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GAMESIZE)
	enum { IDD = IDD_SIZE };
	int		m_length;
	int		m_number;
	int		m_width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GAMESIZE)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GAMESIZE)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMESIZE_H__552029C6_8A88_4BC4_9FB6_D3EC17918A42__INCLUDED_)
