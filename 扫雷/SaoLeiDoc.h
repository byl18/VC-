// SaoLeiDoc.h : interface of the CSaoLeiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAOLEIDOC_H__2782C80C_0C62_488C_BE87_CD15F2AA0CCD__INCLUDED_)
#define AFX_SAOLEIDOC_H__2782C80C_0C62_488C_BE87_CD15F2AA0CCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSaoLeiDoc : public CDocument
{
protected: // create from serialization only
	CSaoLeiDoc();
	DECLARE_DYNCREATE(CSaoLeiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaoLeiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSaoLeiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSaoLeiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAOLEIDOC_H__2782C80C_0C62_488C_BE87_CD15F2AA0CCD__INCLUDED_)
