// SclFileDoc.cpp : 实现文件
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


// CSclFileDoc 诊断

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
// CSclFileDoc 序列化

void CSclFileDoc::Serialize(CArchive& ar)
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


// CSclFileDoc 命令
