
// Draw_starrynightDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw_starrynight.h"
#include "Draw_starrynightDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraw_starrynightDlg �Ի���




CDraw_starrynightDlg::CDraw_starrynightDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDraw_starrynightDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDraw_starrynightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scrollbar1);
	DDX_Control(pDX, IDC_EDIT1, m_disinfo);
	DDX_Control(pDX, IDC_EDIT2, m_disinfo2);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_scrollbar2);
	DDX_Control(pDX, IDC_EDIT3, m_disinfo3);
	DDX_Control(pDX, IDC_SCROLLBAR3, m_scrollbar3);
}

BEGIN_MESSAGE_MAP(CDraw_starrynightDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON5, &CDraw_starrynightDlg::OnBnClickedButton5)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CDraw_starrynightDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDraw_starrynightDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CDraw_starrynightDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDraw_starrynightDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDraw_starrynightDlg ��Ϣ�������

BOOL CDraw_starrynightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_scrollbar1.SetScrollRange(0,50);
	m_scrollbar1.SetScrollPos(0);
	ChangeDisplayInfo(m_scrollbar1.GetScrollPos());
	m_scrollbar2.SetScrollRange(0,50);
	m_scrollbar2.SetScrollPos(0);
	ChangeDisplayInfo2(m_scrollbar2.GetScrollPos());
	m_scrollbar3.SetScrollRange(0,100);
	m_scrollbar3.SetScrollPos(0);
	ChangeDisplayInfo3(m_scrollbar3.GetScrollPos());
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

int CDraw_starrynightDlg::ChangeDisplayInfo(int pos)
{
	TCHAR sPos[10];
	_itow_s(pos,sPos,10);
	m_disinfo.SetSel(0,-1);
	m_disinfo.ReplaceSel(sPos);
	UpdateData(FALSE);
	return 0;
}

int CDraw_starrynightDlg::ChangeDisplayInfo2(int pos2)
{
	TCHAR sPos[10];
	_itow_s(pos2,sPos,10);
	m_disinfo2.SetSel(0,-1);
	m_disinfo2.ReplaceSel(sPos);
	UpdateData(FALSE);
	return 0;
}

int CDraw_starrynightDlg::ChangeDisplayInfo3(int pos3)
{
	TCHAR sPos[10];
	_itow_s(pos3,sPos,10);
	m_disinfo3.SetSel(0,-1);
	m_disinfo3.ReplaceSel(sPos);
	UpdateData(FALSE);
	return 0;
}


void CDraw_starrynightDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDraw_starrynightDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






//void CDraw_starrynightDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//
//
//	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
//}


void CDraw_starrynightDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}


void CDraw_starrynightDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		int iNowPos;
    switch(nSBCode)
    {
		
	case SB_THUMBTRACK://�϶���������ʱ
	  if(pScrollBar==&m_scrollbar1)
     { m_scrollbar1.SetScrollPos(nPos);
	   ChangeDisplayInfo(m_scrollbar1.GetScrollPos());}
	  else if(pScrollBar==&m_scrollbar2)
		 { m_scrollbar2.SetScrollPos(nPos);
	   ChangeDisplayInfo2(m_scrollbar2.GetScrollPos());}
	  else if(pScrollBar==&m_scrollbar3)
		 { m_scrollbar3.SetScrollPos(nPos);
	   ChangeDisplayInfo3(m_scrollbar3.GetScrollPos());}
	   break;
     case SB_LINERIGHT://�������������ҵļ�ͷ
		 if(pScrollBar==&m_scrollbar1)
       { 
       iNowPos=m_scrollbar1.GetScrollPos();
       iNowPos=iNowPos+1;
       if(iNowPos>50)           
            iNowPos=50;
       m_scrollbar1.SetScrollPos(iNowPos);
	   ChangeDisplayInfo(m_scrollbar1.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar2)
       { 
       iNowPos=m_scrollbar2.GetScrollPos();
       iNowPos=iNowPos+1;
       if(iNowPos>50)           
            iNowPos=50;
       m_scrollbar2.SetScrollPos(iNowPos);
	   ChangeDisplayInfo2(m_scrollbar2.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar3)
       { 
       iNowPos=m_scrollbar3.GetScrollPos();
       iNowPos=iNowPos+1;
       if(iNowPos>100)           
            iNowPos=100;
       m_scrollbar3.SetScrollPos(iNowPos);
	   ChangeDisplayInfo3(m_scrollbar3.GetScrollPos());}
       break;
    case SB_LINELEFT:	//�������������ϵļ�ͷ
		if(pScrollBar==&m_scrollbar1)
       { 
       iNowPos=m_scrollbar1.GetScrollPos();
       iNowPos=iNowPos-1;
       if(iNowPos<0)
       iNowPos=0;
       m_scrollbar1.SetScrollPos(iNowPos);
	   ChangeDisplayInfo(m_scrollbar1.GetScrollPos());}
	   	 if(pScrollBar==&m_scrollbar2)
       { 
       iNowPos=m_scrollbar2.GetScrollPos();
       iNowPos=iNowPos-1;
       if(iNowPos<0)           
            iNowPos=0;
       m_scrollbar2.SetScrollPos(iNowPos);
	   ChangeDisplayInfo2(m_scrollbar2.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar3)
       { 
       iNowPos=m_scrollbar3.GetScrollPos();
       iNowPos=iNowPos-1;
       if(iNowPos<0)           
            iNowPos=0;
       m_scrollbar3.SetScrollPos(iNowPos);
	   ChangeDisplayInfo3(m_scrollbar3.GetScrollPos());}
       break;

    case SB_PAGELEFT://��������������ļ�ͷ�������֮������
      if(pScrollBar==&m_scrollbar1)
       { 
       iNowPos=m_scrollbar1.GetScrollPos();
	   iNowPos=iNowPos-3;
       if(iNowPos<0)           
            iNowPos=0;
       m_scrollbar1.SetScrollPos(iNowPos);
	   ChangeDisplayInfo(m_scrollbar1.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar2)
       { 
       iNowPos=m_scrollbar2.GetScrollPos();
       iNowPos=iNowPos-3;
       if(iNowPos<0)           
            iNowPos=0;
       m_scrollbar2.SetScrollPos(iNowPos);
	   ChangeDisplayInfo2(m_scrollbar2.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar3)
       { 
       iNowPos=m_scrollbar3.GetScrollPos();
       iNowPos=iNowPos-3;
       if(iNowPos<0)           
            iNowPos=0;
       m_scrollbar3.SetScrollPos(iNowPos);
	   ChangeDisplayInfo3(m_scrollbar3.GetScrollPos());}
       break;
   case SB_PAGERIGHT://��������������ļ�ͷ�������֮�������
     if(pScrollBar==&m_scrollbar1)
       { 
       iNowPos=m_scrollbar1.GetScrollPos();
	   iNowPos=iNowPos+3;
       if(iNowPos>50)           
            iNowPos=50;
       m_scrollbar1.SetScrollPos(iNowPos);
	   ChangeDisplayInfo(m_scrollbar1.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar2)
       { 
       iNowPos=m_scrollbar2.GetScrollPos();
       iNowPos=iNowPos+3;
       if(iNowPos>50)           
            iNowPos=50;
       m_scrollbar2.SetScrollPos(iNowPos);
	   ChangeDisplayInfo2(m_scrollbar2.GetScrollPos());}
		 if(pScrollBar==&m_scrollbar3)
       { 
       iNowPos=m_scrollbar3.GetScrollPos();
       iNowPos=iNowPos+3;
       if(iNowPos>100)           
            iNowPos=100;
       m_scrollbar3.SetScrollPos(iNowPos);
	   ChangeDisplayInfo3(m_scrollbar3.GetScrollPos());}
      break;

	}
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	
}




void CDraw_starrynightDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CClientDC dc(this);
	CBrush *hbrush,brush1;
	CRect rectClient;
	GetClientRect(&rectClient);
    CRect rectDraw(rectClient.right-285,17.5,rectClient.right-30,272.5);
	brush1.CreateSolidBrush(RGB(10,10,60));
	hbrush=dc.SelectObject(&brush1);
	dc.Rectangle(rectDraw);
	CWnd*cSeBkBtnMy=GetDlgItem(IDC_BUTTON1);
	cSeBkBtnMy->EnableWindow(FALSE);
}


void CDraw_starrynightDlg::OnBnClickedButton4()
{
	OnBnClickedButton1();
}


void CDraw_starrynightDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CClientDC dc(this);
	CRect rectClient;
	GetClientRect(&rectClient);
	CBrush *hbrush,brush2;
	CPen *hpen,pen1;
	pen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	brush2.CreateSolidBrush(RGB(255,255,10));
	//dc.MoveTo(rectClient.right-285+5*m_scrollbar1.GetScrollPos(),20+5*m_scrollbar2.GetScrollPos());
	int m_x=rectClient.right-285+5*m_scrollbar1.GetScrollPos()+2.5;
	int m_y=267.5-5*m_scrollbar2.GetScrollPos();
	POINT lpPoints[4]={m_x,m_y,m_x-2.5,m_y+2.5,m_x,m_y+5,m_x+2.5,m_y+2.5};
	//m_x-0.7,m_y+1.8,m_x-2.5,m_y+2.5,m_x-0.7,m_y+3.2,m_x+0.7,m_y+3.2,m_x+2.5,m_y+2.5,m_x+0.7,m_y+1.8
	dc.SelectObject(brush2);
	dc.SelectObject(pen1);
	Polygon(dc,lpPoints,4);
}


void CDraw_starrynightDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CClientDC dc(this);
	CRect rectClient;
	GetClientRect(&rectClient);
	CBrush *hbrush,brush2;
	CPen *hpen,pen1;
	pen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	brush2.CreateSolidBrush(RGB(255,255,10));
	dc.SelectObject(brush2);
	dc.SelectObject(pen1);
	int num=m_scrollbar3.GetScrollPos();
	int i=0;
	while(i<num)
	{
	//srand((unsigned)time(NULL));
	int rx=rectClient.right-285+rand()%255+2.5;
	int ry=267.5-rand()%255;
	POINT lpPoints[4]={rx,ry,rx-2.5,ry+2.5,rx,ry+5,rx+2.5,ry+2.5};
	Polygon(dc,lpPoints,4);
	i++;
	};
}
