// SaoLeiView.h : interface of the CSaoLeiView class
//
/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_SAOLEIVIEW_H__5C27BEF7_F572_49F7_872B_ED3227BEE0B8__INCLUDED_)
#define AFX_SAOLEIVIEW_H__5C27BEF7_F572_49F7_872B_ED3227BEE0B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSaoLeiView : public CView  //最大游戏界面 50*50
{
	int fangge[50][50];  //记录是否有雷
	int number[50][50];  //记录方框内数字
	int Click[50][50];  //记录是否被点开
	int flag[50][50];  //记录是否被红旗标记

	int LeftClick[50][50];
	int RightClick[50][50];
	int flagnumber[50][50];

	int i,j;  //坐标
	int k;  //雷循环变量
	int lei[50];  //产雷上限50
	
	int X;  //游戏界面长
	int Y;  //游戏界面宽
	int Mine_number;  //雷数


	int win_or_lose;  //是否胜利(1/-1)

public:
	void SetMine();  //布雷函数
	void SetNumber();  //计算数字函数
	void SetClick();  //点开方格

	void SetFlagNumber();  //计算附近红旗数

protected: // create from serialization only
	CSaoLeiView();
	DECLARE_DYNCREATE(CSaoLeiView)

// Attributes
public:
	CSaoLeiDoc* GetDocument();

// Operations
public:
		int Time;  //开始计时标志
		int second;  //计时
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaoLeiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSaoLeiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSaoLeiView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnIdGaofen();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRESTART();
	afx_msg void OnRestart();
};

#ifndef _DEBUG  // debug version in SaoLeiView.cpp
inline CSaoLeiDoc* CSaoLeiView::GetDocument()
   { return (CSaoLeiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAOLEIVIEW_H__5C27BEF7_F572_49F7_872B_ED3227BEE0B8__INCLUDED_)
