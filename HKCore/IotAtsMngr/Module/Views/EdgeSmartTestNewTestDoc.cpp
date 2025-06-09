
// iSmartTestNewTestDoc.cpp : CiSmartTestNewTestDoc 类的实现
//

#include "stdafx.h"

#include "EdgeSmartTestNewTestDoc.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


// CiSmartTestNewTestDoc

IMPLEMENT_DYNCREATE(CEdgeSmartTestNewTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CEdgeSmartTestNewTestDoc, CDocument)
END_MESSAGE_MAP()


// CiSmartTestNewTestDoc 构造/析构

CEdgeSmartTestNewTestDoc::CEdgeSmartTestNewTestDoc()
{
	// TODO: 在此添加一次性构造代码

}

CEdgeSmartTestNewTestDoc::~CEdgeSmartTestNewTestDoc()
{
}

BOOL CEdgeSmartTestNewTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CiSmartTestNewTestDoc 序列化

void CEdgeSmartTestNewTestDoc::Serialize(CArchive& ar)
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


// CiSmartTestNewTestDoc 诊断

#ifdef _DEBUG
void CEdgeSmartTestNewTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEdgeSmartTestNewTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CiSmartTestNewTestDoc 命令
