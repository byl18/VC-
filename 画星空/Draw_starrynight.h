
// Draw_starrynight.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDraw_starrynightApp:
// �йش����ʵ�֣������ Draw_starrynight.cpp
//

class CDraw_starrynightApp : public CWinApp
{
public:
	CDraw_starrynightApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDraw_starrynightApp theApp;