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

// IecConfigFrame.cpp : CIecConfigFrame ���ʵ��
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "IecConfigFrame.h"
#include "..\Module\IecCfgTool\IecCfgTool.h"
#include "MainFrm.h"
#include "..\..\Module\XfileMngrBase\XFileSaveAsDlg.h"

#include "IecCfgSmvDataView.h"
#include "IecCfgGinDataView.h"
#include "IecCfgGoutDataView.h"

#include "IecCfgSmvDataChsView.h"
#include "IecCfgGoutDataChsView.h"
#include "IecCfgGinDataChsView.h"
#include "TestEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIecConfigFrame

IMPLEMENT_DYNCREATE(CIecConfigFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CIecConfigFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_MDIACTIVATE()
	ON_MESSAGE(WM_IECCFGDATA_CHANGED, OnIecCfgDataChanged)
	ON_MESSAGE(WM_IECCFGDATA_CHANGED_MIX, OnIecCfgDataMixCtrlsChanged)
	ON_MESSAGE(WM_VIEW_IECCFG_ONLY_USEDIN, OnIecCfgOnlyViewUsedInChs)
	ON_MESSAGE(WM_VIEW_IECCFG_UPDATE_CHS_GRID, OnIecCfgUpdateChsGrid)

END_MESSAGE_MAP()

// CIecConfigFrame ����/����

CIecConfigFrame::CIecConfigFrame()
{
	m_bCloseFrameByDelete = FALSE;
	m_pIecCfgFile = NULL;
	m_pDocument = NULL;
}

CIecConfigFrame::~CIecConfigFrame()
{
}


BOOL CIecConfigFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CIecConfigFrame ���

#ifdef _DEBUG
void CIecConfigFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CIecConfigFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CIecConfigFrame ��Ϣ�������

void CIecConfigFrame::OnClose()
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

	if (g_nEngineDispMode == _DISP_MODE_PN466)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("��ǰ���ڵ�������ģʽ,������رյ�ǰ�������ô���."));
		return;
	}

	if (!m_bCloseFrameByDelete)
	{
		if (m_pIecCfgFile->IsModified())
		{
			CString strMsg;
			strMsg.Format(_T("�����ļ���%s�����޸�,�Ƿ񱣴�?"), m_pIecCfgFile->m_strName);

			UINT nRet = MessageBox(strMsg, _T("��ʾ"), MB_YESNOCANCEL | MB_ICONQUESTION);

			if (nRet == IDCANCEL)
			{
				return;
			}

			if (nRet == IDYES)
			{
				Save();
			}
		}
	}
	
	BOOL bDelete = m_bCloseFrameByDelete;
	CIecCfgFile *pFile = m_pIecCfgFile;
	CMDIChildWndEx::OnClose();

	CIecCfgTool::CloseIecFile(pFile, bDelete);
	theApp.UpdateIecCfgFilesComboBox();
}

BOOL CIecConfigFrame::Save(CXFolder *pXFolder)
{
	return FALSE;
}

BOOL CIecConfigFrame::Save(BOOL bIsAT02D_CFG)//�ܺ�� 20200616  ����AT02����
{
// 	CExBaseObject *pAncestor = (CExBaseObject*)m_pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
// 
// 	if (pAncestor == NULL)
// 	{
// 		//�Ѿ����ļ�·��
// 		if (m_pIecCfgFile->m_strID.GetLength() > 8)
// 		{
// 			m_pIecCfgFile->Save();
// 		}
// 		else
// 		{
// 			SaveAs();
// 		}
// 	}
// 	else
// 	{
// 		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pAncestor;
// 
// 		if (pIecCfgFileDevice->m_strID.GetLength() > 8)
// 		{
// 			pIecCfgFileDevice->Save();
// 		}
// 		else
// 		{
// 			SaveAs();
// 		}
// 	}
	return theApp.SaveIecfgFile(m_pIecCfgFile, m_pDocument,bIsAT02D_CFG);
}

BOOL CIecConfigFrame::SaveAs(BOOL bIsAT02D_CFG)
{
// 	CExBaseObject *pAncestor = (CExBaseObject*)m_pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
// 
// 	CXFileSaveAsDlg dlg;
// 	dlg.m_strXFile = m_pIecCfgFile->m_strName;
// 	CXFileMngr *pXFileMngr = NULL;
// 	CString strFilePostFix;
// 
// 	if (pAncestor == NULL)
// 	{
// 		pXFileMngr = CIecCfgTool::GetIecCfgFileMngr();
// 		strFilePostFix = g_strIecCfgFilePostfix;
// 	}
// 	else
// 	{
// 		pXFileMngr = CIecCfgTool::GetIecCfgDeviceFileMngr();
// 		strFilePostFix = g_strDeviceIecCfgFilePostfix;
// 	}
// 
// 	dlg.m_pXFileMngr = pXFileMngr;
// 	dlg.m_strXFilePostFix = strFilePostFix;
// 
// 	if (dlg.DoModal() != IDOK)
// 	{
// 		return FALSE;
// 	}
// 
// 	CXFolder *pXCurrFolder = dlg.m_pCurrSelFolder;
// 
// 	//����
// 	m_pIecCfgFile->SaveAs(dlg.m_strXFilePath);
// 	CXFile *pXFile = pXCurrFolder->AddFile2(GetPathFileNameFromFilePathName(dlg.m_strXFilePath));
// 
// 	//���½���
// 	CXFolderTreeCtrl *pTreeCtrl = (CXFolderTreeCtrl*)pXFileMngr->GetRefTreeCtrl();
// 	ASSERT(pTreeCtrl != NULL);
// 	pTreeCtrl->Insert(pXFile);
// 	m_pDocument->SetTitle(m_pIecCfgFile->m_strName);
// 	theApp.ShowIecCfgFileTitleToStatusBar(m_pIecCfgFile);

	theApp.SaveAsIecfgFile(m_pIecCfgFile, m_pDocument,bIsAT02D_CFG);

	return TRUE;
}

BOOL CIecConfigFrame::SaveAs(const CString &strFileName)
{
	CXFileMngr *pXFileMngr = CIecCfgTool::GetIecCfgFileMngr();
	CXFolder *pXCurrFolder = pXFileMngr->GetCurrSelFolder();

	if (pXCurrFolder == NULL)
	{
		pXCurrFolder = pXFileMngr;
	}

	CString strName, strPostfix;
	CString strTemp;
	CString strPath;
	ParseFileNameAndPostfix(strFileName, strName, strPostfix);

	while (TRUE)
	{
		strTemp.Format(_T("%s.%s"), strName, strPostfix);

		if (pXCurrFolder->FindByID(strFileName) == NULL)
		{
			strPath = pXCurrFolder->GetFolderPath(TRUE);
			strPath += strTemp;
			break;
		}
	}

	m_pIecCfgFile->SaveAs(strPath);
	CXFile *pXFile = pXCurrFolder->AddFile2(GetPathFileNameFromFilePathName(strPath));
	
	//���½���
	CXFolderTreeCtrl *pTreeCtrl = (CXFolderTreeCtrl*)pXFileMngr->GetRefTreeCtrl();
	ASSERT(pTreeCtrl != NULL);
	pTreeCtrl->Insert(pXFile);
	m_pDocument->SetTitle(m_pIecCfgFile->m_strName);

	theApp.ShowIecCfgFileTitleToStatusBar(m_pIecCfgFile);

	return TRUE;
}

BOOL CIecConfigFrame::SaveAs(CXFolder *pXFolder)
{
	return FALSE;
}


void CIecConfigFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd*)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pActivateWnd);

	if (m_pIecCfgFile != NULL && bActivate)
	{
		theApp.ShowIecCfgFileTitleToStatusBar(m_pIecCfgFile);
	}

}


LRESULT CIecConfigFrame::OnIecCfgDataChanged(WPARAM wParam, LPARAM lParam)
{
	POSITION pos = m_pDocument->GetFirstViewPosition();
	CView *pView = NULL;
	CIecCfgFile *pIecCfgFile = (CIecCfgFile*)wParam;
	UINT nClassID = lParam;

	while (pos != NULL)
	{
		pView = m_pDocument->GetNextView(pos);

		switch(nClassID)
		{
		case CFGCLASSID_CIECCFGDATASSMV:
			if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgSmvDataView)) )
			{
				((CIecCfgSmvDataView*)pView)->ShowIecCfgData();
				pos = NULL;
			}
			break;

		case CFGCLASSID_CIECCFGDATASGIN:
			if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGinDataView)) )
			{
				((CIecCfgGinDataView*)pView)->ShowIecCfgData();
				pos = NULL;
			}
			break;

		case CFGCLASSID_CIECCFGDATASGOUT:
			if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGoutDataView)) )
			{
				((CIecCfgGoutDataView*)pView)->ShowIecCfgData();
				pos = NULL;
			}
			break;

		}
	}

	return 0;
}

LRESULT CIecConfigFrame::OnIecCfgDataMixCtrlsChanged(WPARAM wParam, LPARAM lParam)
{
	POSITION pos = m_pDocument->GetFirstViewPosition();
	CView *pView = NULL;
	CIecCfgFile *pIecCfgFile = (CIecCfgFile*)wParam;
	DWORD dwValue = lParam;

	while (pos != NULL)
	{
		pView = m_pDocument->GetNextView(pos);

		if (((dwValue&&SCL_IECFG_CTRL_TYPE_GS_SUB)>0)&&(pView->IsKindOf(RUNTIME_CLASS(CIecCfgGinDataView))))
		{
			((CIecCfgGinDataView*)pView)->ShowIecCfgData();
		}

		if (((dwValue&&SCL_IECFG_CTRL_TYPE_GS_PUB)>0)&&(pView->IsKindOf(RUNTIME_CLASS(CIecCfgGoutDataView))))
		{
			((CIecCfgGoutDataView*)pView)->ShowIecCfgData();
		}

		if (((dwValue&&SCL_IECFG_CTRL_TYPE_SMV)>0)&&(pView->IsKindOf(RUNTIME_CLASS(CIecCfgSmvDataView))))
		{
			((CIecCfgSmvDataView*)pView)->ShowIecCfgData();
		}
	}

	if ((g_nEngineDispMode == _DISP_MODE_PN466))
	{
		ActivateFrame(1);
	}

	return 0;
}

LRESULT CIecConfigFrame::OnIecCfgOnlyViewUsedInChs(WPARAM wParam, LPARAM lParam)
{
	POSITION pos = m_pDocument->GetFirstViewPosition();

	while (pos != NULL)
	{
		CView* pView = m_pDocument->GetNextView(pos);
		
		if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgSmvDataChsView)) )
		{
			CIecCfgSmvDataChsView *pSmvDataChsView = (CIecCfgSmvDataChsView*)pView;
			pSmvDataChsView->UpdateGrid();
		}
		else if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGoutDataChsView)) )
		{
			CIecCfgGoutDataChsView *pSmvDataChsView = (CIecCfgGoutDataChsView*)pView;
			pSmvDataChsView->UpdateGrid();
		}
		
	}

	return 0;
}

LRESULT CIecConfigFrame::OnIecCfgUpdateChsGrid(WPARAM wParam, LPARAM lParam)
{
	POSITION pos = m_pDocument->GetFirstViewPosition();

	while (pos != NULL)
	{
		CView* pView = m_pDocument->GetNextView(pos);

		if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgSmvDataChsView)) )
		{
			CIecCfgSmvDataChsView *pSmvDataChsView = (CIecCfgSmvDataChsView*)pView;
			pSmvDataChsView->UpdateGrid(TRUE);
		}
		else if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGoutDataChsView)) )
		{
 			CIecCfgGoutDataChsView *pSmvDataChsView = (CIecCfgGoutDataChsView*)pView;
 			pSmvDataChsView->UpdateGrid(TRUE);
		}
		else if (pView->IsKindOf(RUNTIME_CLASS(CIecCfgGinDataChsView)) )
		{
			CIecCfgGinDataChsView *pGinDataChsView = (CIecCfgGinDataChsView*)pView;
			pGinDataChsView->UpdateGrid(TRUE);
		}

	}

	return 0;
}


