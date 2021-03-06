// HIGHSCORE.cpp : implementation file
#include "stdafx.h"
#include "SaoLei.h"
#include "HIGHSCORE.h"
#include "SETNAME.h"  
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CHIGHSCORE dialog

extern SETNAME b;
extern int game_time;
extern int win;

CHIGHSCORE::CHIGHSCORE(CWnd* pParent /*=NULL*/)  //初始化
	: CDialog(CHIGHSCORE::IDD, pParent)
{
	int x;
	FILE *fp;
	fp = fopen("highscore.txt","r");  //读取文件出现问题
	//{{AFX_DATA_INIT(CHIGHSCORE)
	//}}AFX_DATA_INIT
	for(x=0;x<3;x++)  //读取文件数据
		{
			fscanf(fp,"%s",&p[x]);
			fscanf(fp,"%d",&q[x]);
		}

	for(x=0;x<3;x++)
		if( (game_time<q[x]) && (win==1) )
		{
			Sort(x);
			q[x]=game_time;
			strcpy(p[x],b.m_name);
			break;
		}
	m_first_name = p[0];
	m_second_name = p[1];
	m_third_name = p[2];
	m_first_time = q[0];
	m_second_time = q[1];
	m_third_time = q[2];

fp = fopen("highscore.txt","w");

	for(x=0;x<3;x++)
	{
		fprintf(fp,"%s ",p[x]);
		fprintf(fp,"%d ",q[x]);
	}
	fclose(fp);
}


void CHIGHSCORE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHIGHSCORE)
	DDX_Text(pDX, IDC_FIRST_TIME, m_first_time);
	DDX_Text(pDX, IDC_FIRST_NAME, m_first_name);
	DDX_Text(pDX, IDC_SECOND_NAME, m_second_name);
	DDX_Text(pDX, IDC_SECOND_TIME, m_second_time);
	DDX_Text(pDX, IDC_THIRD_NAME, m_third_name);
	DDX_Text(pDX, IDC_THIRD_TIME, m_third_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHIGHSCORE, CDialog)
	//{{AFX_MSG_MAP(CHIGHSCORE)
	ON_COMMAND(AFX_ID_GAOFEN, OnIdGaofen)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHIGHSCORE message handlers

BOOL CHIGHSCORE::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::OnCommand(wParam, lParam);
}

int CHIGHSCORE::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DoModal();
}

void CHIGHSCORE::OnIdGaofen() 
{
	// TODO: Add your command handler code here
}

void CHIGHSCORE::Sort(int rank)  //排序
{
	for(int x=2;x>rank;x--)
		{
			q[x]=q[x-1];
			for(int y=0;y<20;y++)
			p[x][y]=p[x-1][y];
		}
}
