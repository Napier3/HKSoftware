
// StationTestMainDoc.cpp : CStationTestMainDoc 类的实现
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"

#include "StationTestGraphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStationTestMainDoc

IMPLEMENT_DYNCREATE(CStationTestGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CStationTestGraphDoc, CDocument)
END_MESSAGE_MAP()


// CStationTestMainDoc 构造/析构

CStationTestGraphDoc::CStationTestGraphDoc()
{
	// TODO: 在此添加一次性构造代码

}

CStationTestGraphDoc::~CStationTestGraphDoc()
{
}

BOOL CStationTestGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CStationTestMainDoc 序列化

void CStationTestGraphDoc::Serialize(CArchive& ar)
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


// CStationTestMainDoc 诊断

#ifdef _DEBUG
void CStationTestGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStationTestGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStationTestMainDoc 命令
