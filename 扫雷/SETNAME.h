#if !defined(AFX_SETNAME_H__646748B5_0793_4DDD_93DA_379688096363__INCLUDED_)
#define AFX_SETNAME_H__646748B5_0793_4DDD_93DA_379688096363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SETNAME.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SETNAME dialog

class SETNAME : public CDialog
{
// Construction
public:
	SETNAME(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SETNAME)
	enum { IDD = IDD_SETNAME };
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SETNAME)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SETNAME)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETNAME_H__646748B5_0793_4DDD_93DA_379688096363__INCLUDED_)
