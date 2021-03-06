// MineDoc.h : interface of the CMineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINEDOC_H__621533BD_C331_46D1_A78A_D87100105767__INCLUDED_)
#define AFX_MINEDOC_H__621533BD_C331_46D1_A78A_D87100105767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMineDoc : public CDocument
{
protected: // create from serialization only
	CMineDoc();
	DECLARE_DYNCREATE(CMineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINEDOC_H__621533BD_C331_46D1_A78A_D87100105767__INCLUDED_)