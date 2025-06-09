// SclFileDoc.cpp : 实现文件
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


// CSclVisualCCDoc 诊断

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
// CSclVisualCCDoc 序列化

void CSclCheckDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
#endif


// CSclVisualCCDoc 命令
