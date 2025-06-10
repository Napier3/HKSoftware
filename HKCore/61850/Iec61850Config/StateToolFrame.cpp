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

// StateToolFrame.cpp : CStateToolFrame 类的实现
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "StateToolFrame.h"
#include "..\Module\IecCfgTool\IecCfgTool.h"
#include "MainFrm.h"
#include "..\..\Module\XfileMngrBase\XFileSaveAsDlg.h"

#include "StateToolDoc.h"
#include "StateToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStateToolFrame

IMPLEMENT_DYNCREATE(CStateToolFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CStateToolFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

// CStateToolFrame 构造/析构

CStateToolFrame::CStateToolFrame()
{
	m_pDocument = NULL;
}

CStateToolFrame::~CStateToolFrame()
{
}

void CStateToolFrame::GetTestPara(CString &strParas)
{
	CStateToolView *pView = (CStateToolView*)GetActiveView();
	ASSERT (pView != NULL);

	pView->GetTestPara(strParas);
}

BOOL CStateToolFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CStateToolFrame 诊断

#ifdef _DEBUG
void CStateToolFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CStateToolFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CStateToolFrame 消息处理程序

void CStateToolFrame::OnClose()
{
// 	UINT nDown = ::GetKeyState(VK_SHIFT) & 0x80 ;
// 	nDown += ::GetKeyState(VK_CONTROL) & 0x80;
// 	nDown += ::GetKeyState(VK_MENU) & 0x80;
// 
// 	if (nDown == 384)
// 	{
// // 		if (m_pCfgData != NULL)
// // 		{
// // 			SaveStCfgData();
// // 			m_pCfgData->SaveCfgDefaultConfigFile();
// // 			return;
// // 		}
// 		return;
// 	}

// 	ASSERT (m_pIecCfgFile != NULL);
// 
// 	if (m_pIecCfgFile->IsModified())
// 	{
// 		CString strMsg;
// 		strMsg.Format(_T("文件【%s】没有保存，保存吗？"), m_pIecCfgFile->m_strName);
// 
// 		UINT nRet = MessageBox(strMsg, _T("提示"), MB_YESNOCANCEL | MB_ICONQUESTION);
// 
// 		if (nRet == IDCANCEL)
// 		{
// 			return;
// 		}
// 
// 		if (nRet == IDYES)
// 		{
// 			Save();
// 		}
// 	}
// 	
// 	CIecCfgFile *pFile = m_pIecCfgFile;
	//CMDIChildWndEx::OnClose();

// 	CIecCfgTool::CloseIecFile(pFile);
// 	theApp.UpdateIecCfgFilesComboBox();
}
// 
// BOOL CStateToolFrame::Save(CXFolder *pXFolder)
// {
// 	return FALSE;
// }
// 
// BOOL CStateToolFrame::Save()
// {
// 	//已经有文件路径
// 	
// 
// 	return FALSE;
// }
// 

void CStateToolFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd*)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pActivateWnd);
}
// 
// LRESULT CStateToolFrame::OnIecCfgDataChanged(WPARAM wParam, LPARAM lParam)
// {
// 	POSITION pos = m_pDocument->GetFirstViewPosition();
// 	CView *pView = NULL;
// 	CIecCfgFile *pIecCfgFile = (CIecCfgFile*)wParam;
// 	UINT nClassID = lParam;
// 
// 	while (pos != NULL)
// 	{
// 		pView = m_pDocument->GetNextView(pos);
// 
// 		switch(nClassID)
// 		{
// 		case CFGCLASSID_CIECCFGDATASSMV:
// 			if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgSmvDataView)) )
// 			{
// 				((CIecCfgSmvDataView*)pView)->ShowIecCfgData();
// 				pos = NULL;
// 			}
// 			break;
// 
// 		case CFGCLASSID_CIECCFGDATASGIN:
// 			if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGinDataView)) )
// 			{
// 				((CIecCfgGinDataView*)pView)->ShowIecCfgData();
// 				pos = NULL;
// 			}
// 			break;
// 
// 		case CFGCLASSID_CIECCFGDATASGOUT:
// 			if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGoutDataView)) )
// 			{
// 				((CIecCfgGoutDataView*)pView)->ShowIecCfgData();
// 				pos = NULL;
// 			}
// 			break;
// 
// 		}
// 	}
// 
// 	return 0;
// }
// 
