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

// StateToolDoc.cpp : CStateToolDoc 类的实现
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "StateToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStateToolDoc

IMPLEMENT_DYNCREATE(CStateToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CStateToolDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CStateToolDoc::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CStateToolDoc::OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CStateToolDoc::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CStateToolDoc::OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_AT02D, &CStateToolDoc::OnFileSaveAT02D)//周宏军 20200616  增加AT02配置
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AT02D, &CStateToolDoc::OnUpdateFileSaveAT02D)
	ON_COMMAND(ID_FILE_SAVE_AS_AT02D, &CStateToolDoc::OnFileSaveAsAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_AT02D, &CStateToolDoc::OnUpdateFileSaveAsAT02D)
END_MESSAGE_MAP()


// CStateToolDoc 构造/析构

CStateToolDoc::CStateToolDoc()
{
	m_pIecCfgFile = NULL;
}

CStateToolDoc::~CStateToolDoc()
{
}

BOOL CStateToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CStateToolDoc 序列化

void CStateToolDoc::Serialize(CArchive& ar)
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

void CStateToolDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(lpszTitle);

}

// CStateToolDoc 诊断

#ifdef _DEBUG
void CStateToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStateToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStateToolDoc 命令

void CStateToolDoc::OnFileSave()
{
	theApp.OnFileSave();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CStateToolFrame)))
// 	{
// 		return;
// 	}
// 
// 	// 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
// 	// 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
// 	CStateToolFrame *pStateToolFrame = (CStateToolFrame*)pFrame;
// 	pStateToolFrame->Save();
}

void CStateToolDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
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
// 	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CStateToolFrame));
// 	pCmdUI->Enable(b);
}

void CStateToolDoc::OnFileSaveAs()
{
	theApp.OnFileSaveAs();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CStateToolFrame)))
// 	{
// 		return;
// 	}
// 
// 	CStateToolFrame *pStateToolFrame = (CStateToolFrame*)pFrame;
	//pStateToolFrame->SaveAs();
}

void CStateToolDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAs(pCmdUI);
	//OnUpdateFileSave(pCmdUI);
}

void CStateToolDoc::OnFileSaveAT02D()//周宏军 20200616  增加AT02配置
{
	theApp.OnFileSaveAT02D();
}

void CStateToolDoc::OnUpdateFileSaveAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAT02D(pCmdUI);
}

void CStateToolDoc::OnFileSaveAsAT02D()
{
	theApp.OnFileSaveAsAT02D();
}

void CStateToolDoc::OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAsAT02D(pCmdUI);
}
