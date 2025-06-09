// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// CharLibDevDoc.cpp : CCharLibDevDoc 类的实现
//

#include "stdafx.h"
#include "CharLibDev.h"

#include "CharLibDevDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharLibDevDoc

IMPLEMENT_DYNCREATE(CCharLibDevDoc, CDocument)

BEGIN_MESSAGE_MAP(CCharLibDevDoc, CDocument)
END_MESSAGE_MAP()


// CCharLibDevDoc 构造/析构

CCharLibDevDoc::CCharLibDevDoc()
{
	// TODO: 在此添加一次性构造代码

}

CCharLibDevDoc::~CCharLibDevDoc()
{
}

BOOL CCharLibDevDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCharLibDevDoc 序列化

void CCharLibDevDoc::Serialize(CArchive& ar)
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


// CCharLibDevDoc 诊断

#ifdef _DEBUG
void CCharLibDevDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCharLibDevDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCharLibDevDoc 命令
