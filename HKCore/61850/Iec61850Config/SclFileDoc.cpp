// SclFileDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileDoc.h"


// CSclFileDoc

IMPLEMENT_DYNCREATE(CSclFileDoc, CDocument)

CSclFileDoc::CSclFileDoc()
{
}

BOOL CSclFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSclFileDoc::~CSclFileDoc()
{
}


BEGIN_MESSAGE_MAP(CSclFileDoc, CDocument)
END_MESSAGE_MAP()


// CSclFileDoc ���

#ifdef _DEBUG
void CSclFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CSclFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CSclFileDoc ���л�

void CSclFileDoc::Serialize(CArchive& ar)
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


// CSclFileDoc ����
