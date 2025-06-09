
// TestGridViewDoc.cpp : CTestGridViewDoc 类的实现
//

#include "stdafx.h"
#include "TestGridView.h"

#include "TestGridViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestGridViewDoc

IMPLEMENT_DYNCREATE(CTestGridViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestGridViewDoc, CDocument)
END_MESSAGE_MAP()


// CTestGridViewDoc 构造/析构

CTestGridViewDoc::CTestGridViewDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTestGridViewDoc::~CTestGridViewDoc()
{
}

BOOL CTestGridViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTestGridViewDoc 序列化

void CTestGridViewDoc::Serialize(CArchive& ar)
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


// CTestGridViewDoc 诊断

#ifdef _DEBUG
void CTestGridViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestGridViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestGridViewDoc 命令
