// GAMESIZE.cpp : implementation file
//

#include "stdafx.h"
#include "SaoLei.h"
#include "GAMESIZE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GAMESIZE dialog
	GAMESIZE a;

GAMESIZE::GAMESIZE(CWnd* pParent /*=NULL*/)
	: CDialog(GAMESIZE::IDD, pParent)
{
	//{{AFX_DATA_INIT(GAMESIZE)
	m_length = 6;
	m_number = 7;
	m_width = 6;
	//}}AFX_DATA_INIT
}

void GAMESIZE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GAMESIZE)
	DDX_Text(pDX, IDC_L, m_length);
	DDX_Text(pDX, IDC_N, m_number);
	DDX_Text(pDX, IDC_W, m_width);

	a.m_length = m_length;
	a.m_width = m_width;
	a.m_number = m_number;
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(GAMESIZE, CDialog)
	//{{AFX_MSG_MAP(GAMESIZE)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GAMESIZE message handlers

int GAMESIZE::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}
