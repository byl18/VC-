// Btn.h: interface for the CBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BTN_H__000C7785_0EA2_497E_A2A9_51CC1D7995B7__INCLUDED_)
#define AFX_BTN_H__000C7785_0EA2_497E_A2A9_51CC1D7995B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MineDef.h"

class CBtn  
{
public:
	BOOL Init();
	int click;
	int IDbitmap;
	int bom;
	int bomAround;
	CBtn();
	virtual ~CBtn();

};

#endif // !defined(AFX_BTN_H__000C7785_0EA2_497E_A2A9_51CC1D7995B7__INCLUDED_)
