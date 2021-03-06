// MineView.cpp : implementation of the CMineView class
//

#include "stdafx.h"
#include "Mine.h"

#include "MineDoc.h"
#include "MineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMineView

IMPLEMENT_DYNCREATE(CMineView, CView)

BEGIN_MESSAGE_MAP(CMineView, CView)
	//{{AFX_MSG_MAP(CMineView)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_START, OnStart)
	ON_COMMAND(IDM_RESTART, OnRestart)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_FRESH,ONFresh)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMineView construction/destruction

CMineView::CMineView()
{
	// TODO: add construction code here
	m_bitmap.LoadBitmap(IDB_NORMAL);//IDB_BITMAP1 IDB_NORMAL
	m_bitmap.GetBitmap(&m_bitMeas);
	m_ln=-1;
	m_col=-1;
	m_bomRemain=MBOMSUM;
	InitBom();
}

CMineView::~CMineView()
{
}

BOOL CMineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMineView drawing

void CMineView::OnDraw(CDC* pDC)
{
	CMineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC dccom;
	dccom.CreateCompatibleDC(pDC);
	dccom.SelectObject(m_bitmap);
	int over=0;

	CString str;
	str.Format("地雷剩余数：                  ");
	pDC->TextOut(MBIAS*2+MSTEP*MCOL-120,MBIAS*2+MSTEP*MLN-20,str);
	str.Format("地雷剩余数：%d",m_bomRemain);
	pDC->TextOut(MBIAS*2+MSTEP*MCOL-120,MBIAS*2+MSTEP*MLN-20,str);

	for(int i=0;i<MLN;i++)
		for(int j=0;j<MCOL;j++)
		{
			switch(m_btn[i][j].click)
			{
			case MLCLICK:
				m_bitmap.DeleteObject();
				if(MYESBOM==m_btn[i][j].bom)
				{
					m_bitmap.LoadBitmap(IDB_BOM);
					if(MRUN==m_gameState)
					{
						m_gameState=MOVER;
						PostMessage(UM_FRESH);
					}
				}
				else
				{
					m_bitmap.LoadBitmap(IDB_EMPTY+m_btn[i][j].bomAround);
				}
				dccom.SelectObject(m_bitmap);
				pDC->StretchBlt(MBIAS+j*MSTEP,MBIAS+i*MSTEP,MSTEP,MSTEP,&dccom,
							0,0,m_bitMeas.bmWidth,m_bitMeas.bmHeight,SRCCOPY);
				m_bitmap.DeleteObject();
				m_bitmap.LoadBitmap(IDB_NORMAL);
				dccom.SelectObject(m_bitmap);
				break;
			case MRCLICK:
				m_bitmap.DeleteObject();
				m_bitmap.LoadBitmap(IDB_FLAG);
				dccom.SelectObject(m_bitmap);
				pDC->StretchBlt(MBIAS+j*MSTEP,MBIAS+i*MSTEP,MSTEP,MSTEP,&dccom,
							0,0,m_bitMeas.bmWidth,m_bitMeas.bmHeight,SRCCOPY);
				m_bitmap.DeleteObject();
				m_bitmap.LoadBitmap(IDB_NORMAL);
				dccom.SelectObject(m_bitmap);
				break;
			case NULL:
				pDC->StretchBlt(MBIAS+j*MSTEP,MBIAS+i*MSTEP,MSTEP,MSTEP,&dccom,
							0,0,m_bitMeas.bmWidth,m_bitMeas.bmHeight,SRCCOPY);
				over++;
				break;
			default:
				break;
			}
		}
	if(0==over)
	{
		m_gameState=MWAIT;
		IsSuccess();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMineView diagnostics

#ifdef _DEBUG
void CMineView::AssertValid() const
{
	CView::AssertValid();
}

void CMineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMineDoc* CMineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMineDoc)));
	return (CMineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMineView message handlers

void CMineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PointTo(point);
	CRect rect(0,0,MCOL*MSTEP,MLN*MSTEP);
	
	if(rect.PtInRect(point))
	{
		m_ln=point.y/MSTEP;
		m_col=point.x/MSTEP;
		if(NULL==m_btn[m_ln][m_col].click)
		{
			m_btn[m_ln][m_col].click=MLCLICK;
			if(!(m_btn[m_ln][m_col].bomAround=Around(m_ln,m_col)))
				Expand(m_ln,m_col);
			Invalidate();
		}
	}

	

	CView::OnLButtonUp(nFlags, point);
}

BOOL CMineView::PointTo(CPoint &point)
{
	point.x-=MBIAS;
	point.y-=MBIAS;
	return true;
}

BOOL CMineView::SetBom()
{
	srand((unsigned)time(NULL));

	int index,i,j;
	for(index=0;index<MBOMSUM;)
	{
		i=rand()%MLN;
		j=rand()%MCOL;
		if(MYESBOM!=m_btn[i][j].bom)
		{
			
			m_btn[i][j].bom=MYESBOM;
			index++;
		}
	}

	return true;
}

int CMineView::Around(int ln, int col)
{
	int count=0;
	int minl,minc,maxl,maxc;

	minl=(0==ln)?0:ln-1;
	minc=(0==col)?0:col-1;
	maxl=(MLN-1==ln)?ln:ln+1;
	maxc=(MCOL-1==col)?col:col+1;
	
	for(int i=minl;i<=maxl;i++)
		for(int j=minc;j<=maxc;j++)
		{
			if(i==ln && j==col)
				continue;
			count+=m_btn[i][j].bom;
		}
	return count;
}

BOOL CMineView::Expand(int ln, int col)
{
	int minl,minc,maxl,maxc;

	minl=(0==ln)?0:ln-1;
	minc=(0==col)?0:col-1;
	maxl=(MLN-1==ln)?ln:ln+1;
	maxc=(MCOL-1==col)?col:col+1;
	
	for(int i=minl;i<=maxl;i++)
		for(int j=minc;j<=maxc;j++)
		{
			if(0==m_btn[i][j].click)
			{
				m_btn[i][j].click=MLCLICK;
				if(!(m_btn[i][j].bomAround=Around(i,j)))
					Expand(i,j);
			}
		}

	return true;
}

void CMineView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PointTo(point);
	CRect rect(0,0,MCOL*MSTEP,MLN*MSTEP);
	
	if(rect.PtInRect(point))
	{
		m_ln=point.y/MSTEP;
		m_col=point.x/MSTEP;
		if(MLCLICK!=m_btn[m_ln][m_col].click)
		{
			m_btn[m_ln][m_col].click=(m_btn[m_ln][m_col].click)?NULL:MRCLICK;
			if(MRCLICK==m_btn[m_ln][m_col].click)
				m_bomRemain--;
			else
				m_bomRemain++;
			Invalidate();
		}
	}

	
	CView::OnRButtonUp(nFlags, point);
}

BOOL CMineView::InitBom()
{
	for(int i=0;i<MLN;i++)
		for(int j=0;j<MCOL;j++)
		{
			m_btn[i][j].Init();
		}
	SetBom();
	m_gameState=MRUN;
	return true;
}


BOOL CMineView::ShowAll()
{
	for(int i=0;i<MLN;i++)
		for(int j=0;j<MCOL;j++)
		{
			if(!m_btn[i][j].click)
			{
				m_btn[i][j].click=MLCLICK;
				m_btn[i][j].bomAround=Around(i,j);
			}
		}
	return true;
}

void CMineView::OnStart() 
{
	// TODO: Add your command handler code here
	if(MWAIT==m_gameState)
	{
		InitBom();
		Invalidate();
		CClientDC dc(this);
		CString str;
		str.Format("行：%d    列：%d    总地雷数：%d",MLN,MCOL,MBOMSUM);
//		MessageBox(str);
		dc.TextOut(0,0,str);
//		MessageBox("Game Start!!!");
	}
}

void CMineView::OnRestart() 
{
	// TODO: Add your command handler code here
	
	if(IDYES==MessageBox("是否重新开始？", "Warning", MB_ICONWARNING | MB_YESNO))
	{
		InitBom();
		Invalidate();
		CClientDC dc(this);
		CString str;
		str.Format("行：%d    列：%d    总地雷数：%d",MLN,MCOL,MBOMSUM);
//		MessageBox(str);
		dc.TextOut(0,0,str);
//		MessageBox("Game Start!!!");
	}	
}

void CMineView::ONFresh()
{
	if(MWAIT!=m_gameState)
	{
		ShowAll();
		Invalidate();
	}
}

BOOL CMineView::IsSuccess()
{
	int count=0;
	for(int i=0;i<MLN;i++)
		for(int j=0;j<MCOL;j++)
		{
			if(MRCLICK==m_btn[i][j].click && MYESBOM==m_btn[i][j].bom)
				count++;
		}
	if(MBOMSUM==count)
	{
		MessageBox("You win!!!","Mine",MB_ICONASTERISK);
		return true;
	}
	else
	{
		MessageBox("You lost!!!","猪头",MB_ICONHAND);
		return false;
	}
}

BOOL CMineView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
			CClientDC dc(this);
		CString str;
		str.Format("行：%d    列：%d    总地雷数：%d",MLN,MCOL,MBOMSUM);
//		MessageBox(str);
		dc.TextOut(0,0,str);
	return true;
//	return CView::OnEraseBkgnd(pDC);
}
