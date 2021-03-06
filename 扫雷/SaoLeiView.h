// SaoLeiView.h : interface of the CSaoLeiView class
//
/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_SAOLEIVIEW_H__5C27BEF7_F572_49F7_872B_ED3227BEE0B8__INCLUDED_)
#define AFX_SAOLEIVIEW_H__5C27BEF7_F572_49F7_872B_ED3227BEE0B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSaoLeiView : public CView  //�����Ϸ���� 50*50
{
	int fangge[50][50];  //��¼�Ƿ�����
	int number[50][50];  //��¼����������
	int Click[50][50];  //��¼�Ƿ񱻵㿪
	int flag[50][50];  //��¼�Ƿ񱻺�����

	int LeftClick[50][50];
	int RightClick[50][50];
	int flagnumber[50][50];

	int i,j;  //����
	int k;  //��ѭ������
	int lei[50];  //��������50
	
	int X;  //��Ϸ���泤
	int Y;  //��Ϸ�����
	int Mine_number;  //����


	int win_or_lose;  //�Ƿ�ʤ��(1/-1)

public:
	void SetMine();  //���׺���
	void SetNumber();  //�������ֺ���
	void SetClick();  //�㿪����

	void SetFlagNumber();  //���㸽��������

protected: // create from serialization only
	CSaoLeiView();
	DECLARE_DYNCREATE(CSaoLeiView)

// Attributes
public:
	CSaoLeiDoc* GetDocument();

// Operations
public:
		int Time;  //��ʼ��ʱ��־
		int second;  //��ʱ
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
