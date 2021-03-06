// MineView.h : interface of the CMineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINEVIEW_H__6A8D85D3_45D5_4560_8E2E_1A5C31828EE8__INCLUDED_)
#define AFX_MINEVIEW_H__6A8D85D3_45D5_4560_8E2E_1A5C31828EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MineDef.h"
#include "Btn.h"	// Added by ClassView

class CMineView : public CView
{
protected: // create from serialization only
	CMineView();
	DECLARE_DYNCREATE(CMineView)

// Attributes
public:
	CMineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CMineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMineView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStart();
	afx_msg void OnRestart();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void ONFresh();
	DECLARE_MESSAGE_MAP()
private:
	BITMAP m_bitMeas;
	CBitmap m_bitmap;
private:
	int m_bomRemain;
	BOOL IsSuccess();
	BOOL ShowAll();
	int m_gameState;
	BOOL InitBom();
	BOOL Expand(int ln, int col);
	int Around(int ln,int col);
	BOOL SetBom();
	CBtn m_btn[MLN][MCOL];
	int m_ln,m_col;
	BOOL PointTo(CPoint &point);
};

#ifndef _DEBUG  // debug version in MineView.cpp
inline CMineDoc* CMineView::GetDocument()
   { return (CMineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINEVIEW_H__6A8D85D3_45D5_4560_8E2E_1A5C31828EE8__INCLUDED_)
