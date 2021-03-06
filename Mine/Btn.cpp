// Btn.cpp: implementation of the CBtn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mine.h"
#include "Btn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CBtn::CBtn()
{
	click=NULL;
	IDbitmap=IDB_NORMAL;
	bom=MNOTBOM;
	bomAround=-1;
}

CBtn::~CBtn()
{

}

BOOL CBtn::Init()
{
	click=NULL;
	IDbitmap=IDB_NORMAL;
	bom=MNOTBOM;
	bomAround=-1;

	return true;
}
