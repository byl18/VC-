// SaoLeiDoc.cpp : implementation of the CSaoLeiDoc class
//

#include "stdafx.h"
#include "SaoLei.h"

#include "SaoLeiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaoLeiDoc

IMPLEMENT_DYNCREATE(CSaoLeiDoc, CDocument)

BEGIN_MESSAGE_MAP(CSaoLeiDoc, CDocument)
	//{{AFX_MSG_MAP(CSaoLeiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaoLeiDoc construction/destruction

CSaoLeiDoc::CSaoLeiDoc()
{
	// TODO: add one-time construction code here

}

CSaoLeiDoc::~CSaoLeiDoc()
{
}

BOOL CSaoLeiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSaoLeiDoc serialization

void CSaoLeiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSaoLeiDoc diagnostics

#ifdef _DEBUG
void CSaoLeiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSaoLeiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG