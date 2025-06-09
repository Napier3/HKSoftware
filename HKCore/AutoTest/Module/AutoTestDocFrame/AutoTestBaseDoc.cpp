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

// AutoTestDoc.cpp : CAutoTestDoc 类的实现
//

#include "stdafx.h"

#include "AutoTestBaseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestDoc

IMPLEMENT_DYNCREATE(CAutoTestBaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoTestBaseDoc, CDocument)
END_MESSAGE_MAP()


// CAutoTestDoc 构造/析构

CAutoTestBaseDoc::CAutoTestBaseDoc()
{
	// TODO: 在此添加一次性构造代码

}

CAutoTestBaseDoc::~CAutoTestBaseDoc()
{
	
}

BOOL CAutoTestBaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

BOOL CAutoTestBaseDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}

// CAutoTestDoc 序列化

void CAutoTestBaseDoc::Serialize(CArchive& ar)
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


void CAutoTestBaseDoc::SetTitle(LPCTSTR lpszTitle)
{
	m_strTitle = lpszTitle;

	if (m_strTitle.GetLength() > 30)
	{
		m_strTitle = GetPathFileNameFromFilePathName(m_strTitle);
	}

	if (m_strTitle.GetLength() == 0)
	{
		m_strTitle = lpszTitle;
	}

	UpdateFrameCounts();        // will cause name change in views
}

// CAutoTestDoc 诊断

#ifdef _DEBUG
void CAutoTestBaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoTestBaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAutoTestDoc 命令
