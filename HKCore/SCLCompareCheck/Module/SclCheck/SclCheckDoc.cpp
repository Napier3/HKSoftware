// SclFileDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SclCheckDoc.h"


// CSclVisualCCDoc

IMPLEMENT_DYNCREATE(CSclCheckDoc, CDocument)

CSclCheckDoc::CSclCheckDoc()
{
}

BOOL CSclCheckDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSclCheckDoc::~CSclCheckDoc()
{
}


BEGIN_MESSAGE_MAP(CSclCheckDoc, CDocument)
END_MESSAGE_MAP()


// CSclVisualCCDoc ���

#ifdef _DEBUG
void CSclCheckDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CSclCheckDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CSclVisualCCDoc ���л�

void CSclCheckDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif


// CSclVisualCCDoc ����
