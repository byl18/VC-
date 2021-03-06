// SaoLeiView.cpp : implementation of the CSaoLeiView class
//

/***********************************************************************\
高分榜  √  开启文件存储 优化对话框(等级)
\***********************************************************************/

#include "stdafx.h"
#include "SaoLei.h"

#include "SaoLeiDoc.h"
#include "SaoLeiView.h"
#include <ctime>

#include "HIGHSCORE.h"  //显示高分榜
#include "GAMESIZE.h"  //设置游戏规格

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define originX 40  //原点坐标
#define originY 50  //原点坐标
#define length 20  //单位长

extern GAMESIZE a;  //通过对话框控制游戏规格

int _x,_y;  //记录鼠标点击方格
int set_mine;  //是否布雷

int win;  //全局变量 记录是否胜利 传递参数值
int game_time;  //全局变量 记录游戏时间
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

	int previous;  //之前设置的雷
	while(k<=Mine_number)  //产雷
	{
		lei[k]=rand()%(X*Y);

		for(previous=0;previous<k;previous++)
			if(lei[k]==lei[previous])
				lei[k]=rand()%(X*Y);
		k++;
	}

	for(i=0;i<X;i++)  //初始化无雷区为0
			for(j=0;j<Y;j++)
				fangge[i][j]=0;

	for(k=0;k<Mine_number;k++)
		for(i=0;i<X;i++)  //布雷 为1
			for(j=0;j<Y;j++)
				if( (i*X+j)==lei[k] )
					fangge[i][j]=1;
}

void CSaoLeiView::SetNumber()
{
    //计算每格中的数字
	//左上角
	if(fangge[0][0]==0)
		switch(fangge[0][1] + fangge[1][1] + fangge[1][0])
		{
			case 0:{number[0][0]=0;break;}
			case 1:{number[0][0]=1;break;}
			case 2:{number[0][0]=2;break;}
			case 3:{number[0][0]=3;break;}
		}
	//右上角
	if(fangge[X-1][0]==0)
		switch(fangge[X-2][0] + fangge[X-2][1] + fangge[X-1][1])
		{
			case 0:{number[X-1][0]=0;break;}
			case 1:{number[X-1][0]=1;break;}
			case 2:{number[X-1][0]=2;break;}
			case 3:{number[X-1][0]=3;break;}
		}
	//左下角
	if(fangge[0][Y-1]==0)
		switch(fangge[0][Y-2] + fangge[1][Y-2] + fangge[1][Y-1])
		{
			case 0:{number[0][Y-1]=0;break;}
			case 1:{number[0][Y-1]=1;break;}
			case 2:{number[0][Y-1]=2;break;}
			case 3:{number[0][Y-1]=3;break;}
		}
	//右下角
	if(fangge[X-1][Y-1]==0)
		switch(fangge[X-2][Y-1] + fangge[X-1][Y-2] + fangge[X-2][Y-2])
		{
			case 0:{number[X-1][Y-1]=0;break;}
			case 1:{number[X-1][Y-1]=1;break;}
			case 2:{number[X-1][Y-1]=2;break;}
			case 3:{number[X-1][Y-1]=3;break;}
		}
	//上边
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
	//下边
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
	//左边
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
	//右边
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
	//中心数字
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
	//左上角
		switch(flag[0][1] + flag[1][1] + flag[1][0])
		{
			case 0:{flagnumber[0][0]=0;break;}
			case 1:{flagnumber[0][0]=1;break;}
			case 2:{flagnumber[0][0]=2;break;}
			case 3:{flagnumber[0][0]=3;break;}
		}
	//右上角
		switch(flag[X-2][0] + flag[X-2][1] + flag[X-1][1])
		{
			case 0:{flagnumber[X-1][0]=0;break;}
			case 1:{flagnumber[X-1][0]=1;break;}
			case 2:{flagnumber[X-1][0]=2;break;}
			case 3:{flagnumber[X-1][0]=3;break;}
		}
	//左下角
		switch(flag[0][Y-2] + flag[1][Y-2] + flag[1][Y-1])
		{
			case 0:{flagnumber[0][Y-1]=0;break;}
			case 1:{flagnumber[0][Y-1]=1;break;}
			case 2:{flagnumber[0][Y-1]=2;break;}
			case 3:{flagnumber[0][Y-1]=3;break;}
		}
	//右下角
		switch(flag[X-2][Y-1] + flag[X-1][Y-2] + flag[X-2][Y-2])
		{
			case 0:{flagnumber[X-1][Y-1]=0;break;}
			case 1:{flagnumber[X-1][Y-1]=1;break;}
			case 2:{flagnumber[X-1][Y-1]=2;break;}
			case 3:{flagnumber[X-1][Y-1]=3;break;}
		}
	//上边
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
	//下边
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
	//左边
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
	//右边
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
	//中心数字
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
	for(int u=0;u<X*Y;u++)  //遍历每个方格
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
		SetMine();  //进行布雷
	
	SetNumber();  //计算数字

	SetFlagNumber();  //计算周围红旗数
	
	SetClick();  //点击操作结算

	CSaoLeiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	
	if(!pDoc)
		return ;

	CRect HuaXian;
	this->GetClientRect(&HuaXian);
	int x,y;
	for(x=originX; x<(X+1)*length+originX; x+=length)  //画方格
		for(y=originY; y<(Y+1)*length+originY; y+=length)
		{
			pDC->MoveTo(x,50);
			pDC->LineTo(x,y);
			pDC->MoveTo(50,y);
			pDC->LineTo(x,y);
		}

	for(i=0;i<X;i++)  //输出画布
		for(j=0;j<Y;j++)
		{
			if(Click[i][j]==0)
			{
				if(flag[i][j]==1)
					{
						CBitmap bitmap;
						bitmap.LoadBitmap(IDB_BITFLAG);  //加载位图资源
						BITMAP bmp;
						bitmap.GetBitmap(&bmp);  //从位图中获取信息，并填充BITMAP结构
						int w=bmp.bmWidth;  //宽
						int h=bmp.bmHeight;  //高
						CDC dc;
						dc.CreateCompatibleDC(pDC);
						dc.SelectObject(&bitmap);  //构造一个与指定设备兼容的内存设备环境（暂存区），并将位图装入该环境
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
		
	if(win_or_lose==1)  //判断胜利
		{
			win=1;
			game_time=second;
			KillTimer(1);
     		MessageBox("恭喜你胜利啦！");	
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
					MessageBox("很遗憾失败了！");
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
		Time = 1;  //开始计时
	for(int SquareX=0;SquareX<=X;SquareX++)  //判断位于哪个方格
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
		Click[_x][_y]=1;  //记录：左键被点开
		LeftClick[_x][_y]=1;  //记录：左键摁下
		Invalidate();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CSaoLeiView::OnTimer(UINT nIDEvent) 
{
	if( (win_or_lose==1) || (win_or_lose==-1) )  //判断游戏是否结束
		return ;
	if(Time>0)  //开始计时
	{
		second++;
		CRect rect;  //控制重画部分
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
	SetTimer(1,1000,NULL);  //计时器
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
	for(int SquareX=0;SquareX<=X;SquareX++)  //判断位于哪个方格
		for(int SquareY=0;SquareY<=Y;SquareY++)
			if( (point.x>=SquareX*length+originX) && (point.x<= (SquareX+1) *length+originX) )
				if( (point.y>=SquareY*length+originY) && (point.y<= (SquareY+1) *length+originY) )
				{
					_x=SquareX;
					_y=SquareY;
				}
	if( (win_or_lose!=1) && (win_or_lose!=-1) )  //判断是否结束游戏
		if( (_x<X) && (_x>=0) && (_y<Y) && (_y>=0) )
		{
			if(flag[_x][_y]==0)
				flag[_x][_y]=1;  //记录：被标记
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
