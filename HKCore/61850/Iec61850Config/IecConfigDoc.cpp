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

// IecConfigDoc.cpp : CIecConfigDoc 类的实现
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "IecConfigDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIecConfigDoc

IMPLEMENT_DYNCREATE(CIecConfigDoc, CDocument)

BEGIN_MESSAGE_MAP(CIecConfigDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CIecConfigDoc::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CIecConfigDoc::OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CIecConfigDoc::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CIecConfigDoc::OnUpdateFileSaveAs)

	ON_COMMAND(ID_FILE_SAVE_AT02D, &CIecConfigDoc::OnFileSaveAT02D)//周宏军 20200616  增加AT02配置
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AT02D, &CIecConfigDoc::OnUpdateFileSaveAT02D)
	ON_COMMAND(ID_FILE_SAVE_AS_AT02D, &CIecConfigDoc::OnFileSaveAsAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_AT02D, &CIecConfigDoc::OnUpdateFileSaveAsAT02D)
END_MESSAGE_MAP()


// CIecConfigDoc 构造/析构

CIecConfigDoc::CIecConfigDoc()
{
	m_pIecCfgFile = NULL;
}

CIecConfigDoc::~CIecConfigDoc()
{
}

BOOL CIecConfigDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CIecConfigDoc 序列化

void CIecConfigDoc::Serialize(CArchive& ar)
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

void CIecConfigDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(lpszTitle);
}

// CIecConfigDoc 诊断

#ifdef _DEBUG
void CIecConfigDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIecConfigDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIecConfigDoc 命令

void CIecConfigDoc::OnFileSave()
{
	theApp.OnFileSave();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
// 	{
// 		return;
// 	}
// 
// 	// 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
// 	// 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
// 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
// 	pIecConfigFrame->Save();
}

void CIecConfigDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSave(pCmdUI);
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (pFrame == NULL)
// 	{
// 		pCmdUI->Enable(FALSE);
// 		return;
// 	}
// 
// 	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
// 	pCmdUI->Enable(b);
}

void CIecConfigDoc::OnFileSaveAs()
{
	theApp.OnFileSaveAs();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
// 	{
// 		return;
// 	}
// 
// 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	//pIecConfigFrame->SaveAs();
}

void CIecConfigDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAs(pCmdUI);
	//OnUpdateFileSave(pCmdUI);
}

void CIecConfigDoc::OnFileSaveAT02D()//周宏军 20200616  增加AT02配置
{
	theApp.OnFileSaveAT02D();
}

void CIecConfigDoc::OnUpdateFileSaveAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAT02D(pCmdUI);
}

void CIecConfigDoc::OnFileSaveAsAT02D()
{
	theApp.OnFileSaveAsAT02D();
}

void CIecConfigDoc::OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAsAT02D(pCmdUI);
}
