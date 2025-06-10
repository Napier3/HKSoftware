// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// StateToolFrame.cpp : CStateToolFrame ���ʵ��
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

// CStateToolFrame ����/����

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
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CStateToolFrame ���

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

// CStateToolFrame ��Ϣ�������

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
// 		strMsg.Format(_T("�ļ���%s��û�б��棬������"), m_pIecCfgFile->m_strName);
// 
// 		UINT nRet = MessageBox(strMsg, _T("��ʾ"), MB_YESNOCANCEL | MB_ICONQUESTION);
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
// 	//�Ѿ����ļ�·��
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
