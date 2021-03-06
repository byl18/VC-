// SETNAME.cpp : implementation file
//

#include "stdafx.h"
#include "SaoLei.h"
#include "SETNAME.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SETNAME dialog
SETNAME b;

SETNAME::SETNAME(CWnd* pParent /*=NULL*/)
	: CDialog(SETNAME::IDD, pParent)
{
	//{{AFX_DATA_INIT(SETNAME)
	m_name = _T("");
	//}}AFX_DATA_INIT
}


void SETNAME::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SETNAME)
	DDX_Text(pDX, IDC_NAME, m_name);
	b.m_name=m_name;
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SETNAME, CDialog)
	//{{AFX_MSG_MAP(SETNAME)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()