// SaoLeiView.cpp : implementation of the CSaoLeiView class
//

/***********************************************************************\
�߷ְ�  ��  �����ļ��洢 �Ż��Ի���(�ȼ�)
\***********************************************************************/

#include "stdafx.h"
#include "SaoLei.h"

#include "SaoLeiDoc.h"
#include "SaoLeiView.h"
#include <ctime>

#include "HIGHSCORE.h"  //��ʾ�߷ְ�
#include "GAMESIZE.h"  //������Ϸ���

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define originX 40  //ԭ������
#define originY 50  //ԭ������
#define length 20  //��λ��

extern GAMESIZE a;  //ͨ���Ի��������Ϸ���

int _x,_y;  //��¼���������
int set_mine;  //�Ƿ���

int win;  //ȫ�ֱ��� ��¼�Ƿ�ʤ�� ���ݲ���ֵ
int game_time;  //ȫ�ֱ��� ��¼��Ϸʱ��
/////////////////////////////////////////////////////////////////////////////
// CSaoLeiView

IMPLEMENT_DYNCREATE(CSaoLeiView, CView)

BEGIN_MESSAGE_MAP(CSaoLeiView, CView)
	//{{AFX_MSG_MAP(CSaoLeiView)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(AFX_ID_GAOFEN, OnIdGaofen)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_RESTART, &CSaoLeiView::OnRestart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaoLeiView construction/destruction

CSaoLeiView::CSaoLeiView()
{
	set_mine = 0;

	X=a.m_length;
	Y=a.m_width;
	Mine_number=a.m_number;

	for(int i=0;i<X;i++)
		for(int j=0;j<Y;j++)
		{
			flag[i][j]=0;
			Click[i][j]=0;
			flagnumber[i][j]=0;
		}
	Time = 0;
	second = 0;
}

CSaoLeiView::~CSaoLeiView()
{}

BOOL CSaoLeiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSaoLeiView drawing

void CSaoLeiView::SetMine()
{
	set_mine=1;
	k=0;
	srand((unsigned)time(NULL));

	int previous;  //֮ǰ���õ���
	while(k<=Mine_number)  //����
	{
		lei[k]=rand()%(X*Y);

		for(previous=0;previous<k;previous++)
			if(lei[k]==lei[previous])
				lei[k]=rand()%(X*Y);
		k++;
	}

	for(i=0;i<X;i++)  //��ʼ��������Ϊ0
			for(j=0;j<Y;j++)
				fangge[i][j]=0;

	for(k=0;k<Mine_number;k++)
		for(i=0;i<X;i++)  //���� Ϊ1
			for(j=0;j<Y;j++)
				if( (i*X+j)==lei[k] )
					fangge[i][j]=1;
}

void CSaoLeiView::SetNumber()
{
    //����ÿ���е�����
	//���Ͻ�
	if(fangge[0][0]==0)
		switch(fangge[0][1] + fangge[1][1] + fangge[1][0])
		{
			case 0:{number[0][0]=0;break;}
			case 1:{number[0][0]=1;break;}
			case 2:{number[0][0]=2;break;}
			case 3:{number[0][0]=3;break;}
		}
	//���Ͻ�
	if(fangge[X-1][0]==0)
		switch(fangge[X-2][0] + fangge[X-2][1] + fangge[X-1][1])
		{
			case 0:{number[X-1][0]=0;break;}
			case 1:{number[X-1][0]=1;break;}
			case 2:{number[X-1][0]=2;break;}
			case 3:{number[X-1][0]=3;break;}
		}
	//���½�
	if(fangge[0][Y-1]==0)
		switch(fangge[0][Y-2] + fangge[1][Y-2] + fangge[1][Y-1])
		{
			case 0:{number[0][Y-1]=0;break;}
			case 1:{number[0][Y-1]=1;break;}
			case 2:{number[0][Y-1]=2;break;}
			case 3:{number[0][Y-1]=3;break;}
		}
	//���½�
	if(fangge[X-1][Y-1]==0)
		switch(fangge[X-2][Y-1] + fangge[X-1][Y-2] + fangge[X-2][Y-2])
		{
			case 0:{number[X-1][Y-1]=0;break;}
			case 1:{number[X-1][Y-1]=1;break;}
			case 2:{number[X-1][Y-1]=2;break;}
			case 3:{number[X-1][Y-1]=3;break;}
		}
	//�ϱ�
	for(i=0,j=0;i<X-1;i++)
		if(fangge[i][j]==0)
			switch(fangge[i-1][j] + fangge[i-1][j+1] + fangge[i][j+1] + fangge[i+1][j] + fangge[i+1][j+1] )
			{
				case 0:{number[i][j]=0;break;}
				case 1:{number[i][j]=1;break;}
				case 2:{number[i][j]=2;break;}
				case 3:{number[i][j]=3;break;}
				case 4:{number[i][j]=4;break;}
				case 5:{number[i][j]=5;break;}
			}
	//�±�
	for(i=0,j=Y-1;i<X-1;i++)
		if(fangge[i][j]==0)
			switch(fangge[i-1][j] + fangge[i-1][j-1] + fangge[i][j-1] + fangge[i+1][j] + fangge[i+1][j-1] )
			{
				case 0:{number[i][j]=0;break;}
				case 1:{number[i][j]=1;break;}
				case 2:{number[i][j]=2;break;}
				case 3:{number[i][j]=3;break;}
				case 4:{number[i][j]=4;break;}
				case 5:{number[i][j]=5;break;}
			}
	//���
	for(i=0,j=0;j<Y-1;j++)
		if(fangge[i][j]==0)
			switch(fangge[i][j-1] + fangge[i][j+1] + fangge[i+1][j] + fangge[i+1][j-1] + fangge[i+1][j+1] )
			{
				case 0:{number[i][j]=0;break;}
				case 1:{number[i][j]=1;break;}
				case 2:{number[i][j]=2;break;}
				case 3:{number[i][j]=3;break;}
				case 4:{number[i][j]=4;break;}
				case 5:{number[i][j]=5;break;}
			}
	//�ұ�
	for(i=X-1,j=0;j<Y-1;j++)
		if(fangge[i][j]==0)
			switch(fangge[i][j-1] + fangge[i][j+1] + fangge[i-1][j] + fangge[i-1][j-1] + fangge[i-1][j+1] )
			{
				case 0:{number[i][j]=0;break;}
				case 1:{number[i][j]=1;break;}
				case 2:{number[i][j]=2;break;}
				case 3:{number[i][j]=3;break;}
				case 4:{number[i][j]=4;break;}
				case 5:{number[i][j]=5;break;}
			}
	//��������
	for(i=1;i<X-1;i++)
		for(j=1;j<Y-1;j++)
			if(fangge[i][j]==0)
			switch(fangge[i-1][j-1] + fangge[i-1][j] + 
				fangge[i-1][j+1] + fangge[i][j-1] + fangge[i][j+1] + 
				fangge[i+1][j] + fangge[i+1][j-1] + fangge[i+1][j+1])
			{
				case 0:{number[i][j]=0;break;}
				case 1:{number[i][j]=1;break;}
				case 2:{number[i][j]=2;break;}
				case 3:{number[i][j]=3;break;}
				case 4:{number[i][j]=4;break;}
				case 5:{number[i][j]=5;break;}
				case 6:{number[i][j]=6;break;}
				case 7:{number[i][j]=7;break;}
				case 8:{number[i][j]=8;break;}
			}
}

void CSaoLeiView::SetFlagNumber()
{
	//���Ͻ�
		switch(flag[0][1] + flag[1][1] + flag[1][0])
		{
			case 0:{flagnumber[0][0]=0;break;}
			case 1:{flagnumber[0][0]=1;break;}
			case 2:{flagnumber[0][0]=2;break;}
			case 3:{flagnumber[0][0]=3;break;}
		}
	//���Ͻ�
		switch(flag[X-2][0] + flag[X-2][1] + flag[X-1][1])
		{
			case 0:{flagnumber[X-1][0]=0;break;}
			case 1:{flagnumber[X-1][0]=1;break;}
			case 2:{flagnumber[X-1][0]=2;break;}
			case 3:{flagnumber[X-1][0]=3;break;}
		}
	//���½�
		switch(flag[0][Y-2] + flag[1][Y-2] + flag[1][Y-1])
		{
			case 0:{flagnumber[0][Y-1]=0;break;}
			case 1:{flagnumber[0][Y-1]=1;break;}
			case 2:{flagnumber[0][Y-1]=2;break;}
			case 3:{flagnumber[0][Y-1]=3;break;}
		}
	//���½�
		switch(flag[X-2][Y-1] + flag[X-1][Y-2] + flag[X-2][Y-2])
		{
			case 0:{flagnumber[X-1][Y-1]=0;break;}
			case 1:{flagnumber[X-1][Y-1]=1;break;}
			case 2:{flagnumber[X-1][Y-1]=2;break;}
			case 3:{flagnumber[X-1][Y-1]=3;break;}
		}
	//�ϱ�
	for(i=1,j=0;i<X-1;i++)
			switch(flag[i-1][j] + flag[i-1][j+1] + flag[i][j+1] + flag[i+1][j] + flag[i+1][j+1] )
			{
				case 0:{flagnumber[i][j]=0;break;}
				case 1:{flagnumber[i][j]=1;break;}
				case 2:{flagnumber[i][j]=2;break;}
				case 3:{flagnumber[i][j]=3;break;}
				case 4:{flagnumber[i][j]=4;break;}
				case 5:{flagnumber[i][j]=5;break;}
			}
	//�±�
	for(i=1,j=Y-1;i<X-1;i++)
			switch(flag[i-1][j] + flag[i-1][j-1] + flag[i][j-1] + flag[i+1][j] + flag[i+1][j-1] )
			{
				case 0:{flagnumber[i][j]=0;break;}
				case 1:{flagnumber[i][j]=1;break;}
				case 2:{flagnumber[i][j]=2;break;}
				case 3:{flagnumber[i][j]=3;break;}
				case 4:{flagnumber[i][j]=4;break;}
				case 5:{flagnumber[i][j]=5;break;}
			}
	//���
	for(i=0,j=0;j<Y-1;j++)
			switch(flag[i][j-1] + flag[i][j+1] + flag[i+1][j] + flag[i+1][j-1] + flag[i+1][j+1] )
			{
				case 0:{flagnumber[i][j]=0;break;}
				case 1:{flagnumber[i][j]=1;break;}
				case 2:{flagnumber[i][j]=2;break;}
				case 3:{flagnumber[i][j]=3;break;}
				case 4:{flagnumber[i][j]=4;break;}
				case 5:{flagnumber[i][j]=5;break;}
			}
	//�ұ�
	for(i=X-1,j=0;j<Y-1;j++)
			switch(flag[i][j-1] + flag[i][j+1] + flag[i-1][j] + flag[i-1][j-1] + flag[i-1][j+1] )
			{
				case 0:{flagnumber[i][j]=0;break;}
				case 1:{flagnumber[i][j]=1;break;}
				case 2:{flagnumber[i][j]=2;break;}
				case 3:{flagnumber[i][j]=3;break;}
				case 4:{flagnumber[i][j]=4;break;}
				case 5:{flagnumber[i][j]=5;break;}
			}
	//��������
	for(i=1;i<X-1;i++)
		for(j=1;j<Y-1;j++)
			switch(flag[i-1][j-1] + flag[i-1][j] + 
				flag[i-1][j+1] + flag[i][j-1] + flag[i][j+1] + 
				flag[i+1][j] + flag[i+1][j-1] + flag[i+1][j+1])
			{
				case 0:{flagnumber[i][j]=0;break;}
				case 1:{flagnumber[i][j]=1;break;}
				case 2:{flagnumber[i][j]=2;break;}
				case 3:{flagnumber[i][j]=3;break;}
				case 4:{flagnumber[i][j]=4;break;}
				case 5:{flagnumber[i][j]=5;break;}
				case 6:{flagnumber[i][j]=6;break;}
				case 7:{flagnumber[i][j]=7;break;}
				case 8:{flagnumber[i][j]=8;break;}
			}
}


void CSaoLeiView::SetClick()
{
	for(int u=0;u<X*Y;u++)  //����ÿ������
		for(int p=0;p<X;p++)
			for(int q=0;q<Y;q++)
				if( (number[p][q]==0)&& (Click[p][q]==1))
				{
					if( (p-1>=0) && (p-1<=X-1) && (q-1>=0) && (q-1<=Y-1) && (fangge[p-1][q-1]==0) )
						Click[p-1][q-1]=1;
					if( (p-1>=0) && (p-1<=X-1) && (q>=0) && (q<=Y-1) && (fangge[p-1][q]==0) )
						Click[p-1][q]=1;
					if( (p-1>=0) && (p-1<=X-1) && (q+1>=0) && (q+1<=Y-1) && (fangge[p-1][q+1]==0) )
						Click[p-1][q+1]=1;
					if( (p>=0) && (p<=X-1) && (q-1>=0) && (q-1<=Y-1) && (fangge[p][q-1]==0) )
						Click[p][q-1]=1;
					if( (p>=0) && (p<=X-1) && (q+1>=0) && (q+1<=Y-1) && (fangge[p][q+1]==0) )
						Click[p][q+1]=1;
					if( (p+1>=0) && (p+1<=X-1) && (q-1>=0) && (q-1<=Y-1) && (fangge[p+1][q-1]==0) )
						Click[p+1][q-1]=1;
					if( (p+1>=0) && (p+1<=X-1) && (q>=0) && (q<=Y-1) && (fangge[p+1][q]==0) )
						Click[p+1][q]=1;
					if( (p+1>=0) && (p+1<=X-1) && (q+1>=0) && (q+1<=Y-1) && (fangge[p+1][q+1]==0) )
						Click[p+1][q+1]=1;
				}

		for(int p=0;p<X;p++)
			for(int q=0;q<Y;q++)
			{
				if( (LeftClick[p][q]==1) && (RightClick[p][q]==1) )
					if(number[p][q]==flagnumber[p][q])
						{
							if( (p-1>=0) && (p-1<=X-1) && (q-1>=0) && (q-1<=Y-1) && (flag[p-1][q-1]==0) )
								Click[p-1][q-1]=1;
							if( (p-1>=0) && (p-1<=X-1) && (q>=0) && (q<=Y-1) && (flag[p-1][q]==0) )
								Click[p-1][q]=1;
							if( (p-1>=0) && (p-1<=X-1) && (q+1>=0) && (q+1<=Y-1) && (flag[p-1][q+1]==0) )
								Click[p-1][q+1]=1;
							if( (p>=0) && (p<=X-1) && (q-1>=0) && (q-1<=Y-1) && (flag[p][q-1]==0) )
								Click[p][q-1]=1;
							if( (p>=0) && (p<=X-1) && (q+1>=0) && (q+1<=Y-1) && (flag[p][q+1]==0) )
								Click[p][q+1]=1;
							if( (p+1>=0) && (p+1<=X-1) && (q-1>=0) && (q-1<=Y-1) && (flag[p+1][q-1]==0) )
								Click[p+1][q-1]=1;
							if( (p+1>=0) && (p+1<=X-1) && (q>=0) && (q<=Y-1) && (flag[p+1][q]==0) )
								Click[p+1][q]=1;
							if( (p+1>=0) && (p+1<=X-1) && (q+1>=0) && (q+1<=Y-1) && (flag[p+1][q+1]==0) )
								Click[p+1][q+1]=1;
						}
			}
}

void CSaoLeiView::OnDraw(CDC* pDC)
{
	if(set_mine!=1)
		SetMine();  //���в���
	
	SetNumber();  //��������

	SetFlagNumber();  //������Χ������
	
	SetClick();  //�����������

	CSaoLeiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	
	if(!pDoc)
		return ;

	CRect HuaXian;
	this->GetClientRect(&HuaXian);
	int x,y;
	for(x=originX; x<(X+1)*length+originX; x+=length)  //������
		for(y=originY; y<(Y+1)*length+originY; y+=length)
		{
			pDC->MoveTo(x,50);
			pDC->LineTo(x,y);
			pDC->MoveTo(50,y);
			pDC->LineTo(x,y);
		}

	for(i=0;i<X;i++)  //�������
		for(j=0;j<Y;j++)
		{
			if(Click[i][j]==0)
			{
				if(flag[i][j]==1)
					{
						CBitmap bitmap;
						bitmap.LoadBitmap(IDB_BITFLAG);  //����λͼ��Դ
						BITMAP bmp;
						bitmap.GetBitmap(&bmp);  //��λͼ�л�ȡ��Ϣ�������BITMAP�ṹ
						int w=bmp.bmWidth;  //��
						int h=bmp.bmHeight;  //��
						CDC dc;
						dc.CreateCompatibleDC(pDC);
						dc.SelectObject(&bitmap);  //����һ����ָ���豸���ݵ��ڴ��豸�������ݴ�����������λͼװ��û���
						pDC->StretchBlt(i*length+originX+1,j*length+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
					}
				if(flag[i][j]==0)
					{
						CBitmap bitmap;
						bitmap.LoadBitmap(IDB_UNCLICKED);
						BITMAP bmp;
						bitmap.GetBitmap(&bmp);
						int w=bmp.bmWidth;
						int h=bmp.bmHeight;
						CDC dc;
						dc.CreateCompatibleDC(pDC);
						dc.SelectObject(&bitmap);
						pDC->StretchBlt(i*length+originX+1,j*length+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
					}
			}
			
			if(Click[i][j]==1)
			{
				if(fangge[i][j]==0)
					switch(number[i][j])
							{
								case 0:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_0);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 1:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_1);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 2:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_2);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 3:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_3);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 4:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_4);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 5:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_5);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 6:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_6);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 7:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_7);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 8:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_8);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);
										break;
									}
							}
					if(fangge[i][j]==1)
						{
							CBitmap bitmap;
							bitmap.LoadBitmap(IDB_BITMINE);
							BITMAP bmp;
							bitmap.GetBitmap(&bmp);
							int w=bmp.bmWidth;
							int h=bmp.bmHeight;
							CDC dc;
							dc.CreateCompatibleDC(pDC);
							dc.SelectObject(&bitmap);
							pDC->StretchBlt(i*20+originX+1,j*20+originY+1,length-2,length-2,&dc,0,0,w,h,SRCCOPY);					
						}
				}
			}	

	for(i=0;i<X;i++)
		for(j=0;j<Y;j++)
			if( (fangge[i][j]==1) && (Click[i][j]==1) )
				win_or_lose=-1;

	int judge=0;
	for(i=0;i<X;i++)
		for(j=0;j<Y;j++)
		{
			if( (fangge[i][j]==0) && (Click[i][j]==1) )
				judge++;
		}

	if(judge==X*Y-Mine_number)  
		win_or_lose=1;
		
	if(win_or_lose==1)  //�ж�ʤ��
		{
			win=1;
			game_time=second;
			KillTimer(1);
     		MessageBox("��ϲ��ʤ������");	
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_VICTORY);
			BITMAP bmp;
			bitmap.GetBitmap(&bmp);
			int w=bmp.bmWidth;
			int h=bmp.bmHeight;
			CDC dc;
			dc.CreateCompatibleDC(pDC);
			dc.SelectObject(&bitmap);
			pDC->StretchBlt(originX,originY,3*X*length+1,3*Y*length+1,&dc,0,0,w,h,SRCCOPY);
			return;
		}
	else if(win_or_lose==-1)
			{
					KillTimer(1);
					MessageBox("���ź�ʧ���ˣ�");
					CBitmap bitmap;
					bitmap.LoadBitmap(IDB_FAIL);
					BITMAP bmp;
					bitmap.GetBitmap(&bmp);
					int w=bmp.bmWidth;
					int h=bmp.bmHeight;
					CDC dc;
					dc.CreateCompatibleDC(pDC);
					dc.SelectObject(&bitmap);
					pDC->StretchBlt(originX,originY,3*X*length+1,3*Y*length+1,&dc,0,0,w,h,SRCCOPY);			
			}

	 			switch(second%10)
							{
								case 0:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BIT_0);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 1:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_1);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 2:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_2);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 3:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_3);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 4:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_4);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 5:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_5);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 6:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_6);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 7:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_7);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 8:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_8);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 9:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_9);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length*2+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								}
						
						switch( (second%100)/10 )
							{
								case 0:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BIT_0);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 1:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_1);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 2:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_2);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 3:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_3);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 4:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_4);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 5:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_5);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 6:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_6);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 7:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_7);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 8:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_8);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 9:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_9);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(length+1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								}


						switch(second/100)
							{
								case 0:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BIT_0);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 1:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_1);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 2:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_2);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 3:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_3);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 4:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_4);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 5:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_5);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 6:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_6);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 7:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_7);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 8:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_8);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								case 9:
									{
										CBitmap bitmap;
										bitmap.LoadBitmap(IDB_BITMINE_9);
										BITMAP bmp;
										bitmap.GetBitmap(&bmp);
										int w=bmp.bmWidth;
										int h=bmp.bmHeight;
										CDC dc;
										dc.CreateCompatibleDC(pDC);
										dc.SelectObject(&bitmap);
										pDC->StretchBlt(1,1,length,length,&dc,0,0,w,h,SRCCOPY);
										break;
									}
								}
								
}
/////////////////////////////////////////////////////////////////////////////
// CSaoLeiView printing

BOOL CSaoLeiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSaoLeiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSaoLeiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


#ifdef _DEBUG
void CSaoLeiView::AssertValid() const
{
	CView::AssertValid();
}

void CSaoLeiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSaoLeiDoc* CSaoLeiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaoLeiDoc)));
	return (CSaoLeiDoc*)m_pDocument;
}
#endif //_DEBUG

void CSaoLeiView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(Time != 1)
		Time = 1;  //��ʼ��ʱ
	for(int SquareX=0;SquareX<=X;SquareX++)  //�ж�λ���ĸ�����
		for(int SquareY=0;SquareY<=Y;SquareY++)
			if( (point.x>=SquareX*length+originX) && (point.x<= (SquareX+1) *length+originX) )
				if( (point.y>=SquareY*length+originY) && (point.y<= (SquareY+1) *length+originY) )
				{
					_x=SquareX;
					_y=SquareY;
				}

if( (win_or_lose!=1) && (win_or_lose!=-1) )
	if( (_x<X) && (_x>=0) && (_y<Y) && (_y>=0) )
	{
		Click[_x][_y]=1;  //��¼��������㿪
		LeftClick[_x][_y]=1;  //��¼���������
		Invalidate();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CSaoLeiView::OnTimer(UINT nIDEvent) 
{
	if( (win_or_lose==1) || (win_or_lose==-1) )  //�ж���Ϸ�Ƿ����
		return ;
	if(Time>0)  //��ʼ��ʱ
	{
		second++;
		CRect rect;  //�����ػ�����
		rect.left=1;
		rect.right=3*length+1;
		rect.top=1;
		rect.bottom=length+1;
		InvalidateRect(&rect);
	}
	CView::OnTimer(nIDEvent);
}

BOOL CSaoLeiView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CSaoLeiView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(1,1000,NULL);  //��ʱ��
	return 0;
}

void CSaoLeiView::OnIdGaofen()
{
	// TODO: Add your command handler code here
	CHIGHSCORE highscore;
	highscore.DoModal();
}

void CSaoLeiView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	for(int SquareX=0;SquareX<=X;SquareX++)  //�ж�λ���ĸ�����
		for(int SquareY=0;SquareY<=Y;SquareY++)
			if( (point.x>=SquareX*length+originX) && (point.x<= (SquareX+1) *length+originX) )
				if( (point.y>=SquareY*length+originY) && (point.y<= (SquareY+1) *length+originY) )
				{
					_x=SquareX;
					_y=SquareY;
				}
	if( (win_or_lose!=1) && (win_or_lose!=-1) )  //�ж��Ƿ������Ϸ
		if( (_x<X) && (_x>=0) && (_y<Y) && (_y>=0) )
		{
			if(flag[_x][_y]==0)
				flag[_x][_y]=1;  //��¼�������
			else 
				if(flag[_x][_y]==1)
					flag[_x][_y]=0;

			RightClick[_x][_y]=1;
			Invalidate();
		}

	CView::OnRButtonUp(nFlags, point);
}
void CSaoLeiView::OnRestart()
{
 BOOL bNormal =true;
 PROCESS_INFORMATION   info;
 STARTUPINFO startup;
 char szPath[128];
 char *szCmdLine;

 GetModuleFileName(AfxGetApp()-> m_hInstance,   szPath,   sizeof(szPath));
 szCmdLine   =   GetCommandLine();
 GetStartupInfo(&startup);

 BOOL   bSucc   =   CreateProcess(szPath,   szCmdLine,   NULL,   NULL,
  FALSE,   NORMAL_PRIORITY_CLASS,   NULL,   NULL,   &startup,   &info);

 if(bNormal   &&   bSucc)
 {
  CWnd *pWnd   =   AfxGetMainWnd();

  if(pWnd   !=   NULL)
  {
   pWnd-> PostMessage(WM_CLOSE,   0,   0);
  }
  else
   ExitProcess(-1);
 }
 else
  ExitProcess(-1);
	Invalidate();
}
