#include "stdafx.h"
#include "GuideBookWizard.h"

#include "GbWzdCmdCommCmd.h"
#include "GbWzdCmdDeviceModel.h"
#include "GbWzdCmdInitGbByStxmlFile.h"
#include "GbWzdCmdFolder.h"
#include "GbWzdCmdGbtDataInterface.h"
#include "GbWzdCmdSelectStxmlFile.h"
#include "GbWzdCmdSave.h"
#include "GbWzdCmdGbAttr.h"
#include "..\XLanguageResourceAts.h"
#ifdef GB_USE_XFILEMNGRBASE
#include "..\..\..\Module\XFileMngrBase\DlgXFileMngr.h"
#else
#include "..\..\..\Module\FileMngr\Dlg\DlgFileMngr.h"
#endif

#include "..\GbDevConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGuideBookWizard* CGuideBookWizard::g_pGuideBookWizard = NULL;
long CGuideBookWizard::g_nGuideBookWizardRef = 0;

CGuideBookWizard* CGuideBookWizard::Create(const CString &strWzdAutoCfgFile)
{
	g_nGuideBookWizardRef ++;

	if(g_pGuideBookWizard == NULL)
	{
		g_pGuideBookWizard = new CGuideBookWizard();
		g_pGuideBookWizard->CreateWzdAutoConfig(strWzdAutoCfgFile);
	}

	return g_pGuideBookWizard;
}

void CGuideBookWizard::Release()
{
	if (g_nGuideBookWizardRef == 0)
	{
		return;
	}

	g_nGuideBookWizardRef --;

	if(g_nGuideBookWizardRef == 0)
	{
		delete g_pGuideBookWizard;
		g_pGuideBookWizard = NULL;
	}
}

void CGuideBookWizard::CreateWzdAutoConfig(const CString &strWzdAutoCfgFile)
{
	if (strWzdAutoCfgFile.GetLength() < 4)
	{
		return;
	}

	if (!IsFileExist(strWzdAutoCfgFile))
	{
		return;
	}

	m_pGbWzdAutoConfig = new CGbWzdAutoConfig();
	m_pGbWzdAutoConfig->OpenXmlFile(strWzdAutoCfgFile, CGbXMLKeys::g_pGbXMLKeys);
}

//CWordRptEdit* CGuideBookWizard::GetCWordRptEdit()
CRptEditInterface* CGuideBookWizard::GetCWordRptEdit()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->m_pRptEdit;
}

CGuideBook* CGuideBookWizard::GetCGuideBook()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->m_pGuideBook;
}

BOOL CGuideBookWizard::IsWizardValid()
{
	return (g_pGuideBookWizard != NULL);
}

CGuideBookWizard::CGuideBookWizard()
{
	CGbXMLKeys::CreatetGbXMLkeys();

	m_bQuickWizard = FALSE;
	m_pGuideBook = NULL;
	m_nWzdCmdIndex = -1;
	m_pRptEdit = NULL;

	m_dwWzdExecMode = WZDEXEC_NONE;
	m_bWordPageOrientationVert = !CGbDevConfig::IsWordPageDir_Horz();
	m_pGbWzdAutoConfig = NULL;
}	

CGuideBookWizard::~CGuideBookWizard()
{
	CGbXMLKeys::Release();

	if (m_pGbWzdAutoConfig != NULL)
	{
		delete m_pGbWzdAutoConfig;
		m_pGbWzdAutoConfig = NULL;
	}
}

//初始化
CString CGuideBookWizard::GetGbFileType()
{
	ASSERT (g_pGuideBookWizard != NULL);
	return g_pGuideBookWizard->m_strGbFileType;
}

BOOL CGuideBookWizard::SetGbWizardType(const CString &strGbFileType)
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_SetGbWizardType(strGbFileType);
}

//BOOL CGuideBookWizard::InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit, BOOL bQuick)
BOOL CGuideBookWizard::InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit, BOOL bQuick)
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

//	return g_pGuideBookWizard->In_InitGbWizard(pGuideBook, pGbTree, pMainFrame, pWzdWnd, pWordEdit, bQuick);
	return g_pGuideBookWizard->In_InitGbWizard(pGuideBook, pGbTree, pMainFrame, pWzdWnd, pRptEdit, bQuick);
}

//BOOL CGuideBookWizard::InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit)
BOOL CGuideBookWizard::InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit)
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

//	return g_pGuideBookWizard->In_InitStxmlWizard(pGuideBook, pGbTree, pMainFrame, pWzdWnd, pWordEdit);
	return g_pGuideBookWizard->In_InitStxmlWizard(pGuideBook, pGbTree, pMainFrame, pWzdWnd, pRptEdit);
}

CGbWzdCmd* CGuideBookWizard::AddFile(const CString &strFile)
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->In_AddFile(strFile);
}

CGbWzdCmd* CGuideBookWizard::AddSaveCmd(long &nOldSaveCmdIndex)
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->In_AddSaveCmd(nOldSaveCmdIndex);
}

CWnd* CGuideBookWizard::GetWndGbWzd()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

// 	CGbWzdCmd *pCurr = g_pGuideBookWizard->In_GetCurrGbWzdCmd();
// 
// 	if (pCurr == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	if (pCurr->GetClassID() == GBWZDCLASSID_SAVE)
	{
		return g_pGuideBookWizard->m_pWndGbWzd;
	}
// 	else
// 	{
// 		return NULL;
// 	}
}

void CGuideBookWizard::OnGbNodeSelChange(CExBaseObject *pGbNode)
{
	if (g_pGuideBookWizard == NULL)
	{
		return ;
	}

	g_pGuideBookWizard->In_OnGbNodeSelChange(pGbNode);
}

BOOL CGuideBookWizard::IsSubWzdCmd(CGbWzdCmd *pWzdCmd)
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_IsSubWzdCmd(pWzdCmd);
}

long CGuideBookWizard::GetWzdCmdIndex(CGbWzdCmd *pWzdCmd)
{
	if (g_pGuideBookWizard == NULL)
	{
		return -1;
	}

	return g_pGuideBookWizard->In_GetWzdCmdIndex(pWzdCmd);
}

//向导函数
BOOL CGuideBookWizard::IsWizardFinish()
{
	if (g_pGuideBookWizard == NULL)
	{
		return TRUE;
	}

	return g_pGuideBookWizard->In_IsWizardFinish();
}

BOOL CGuideBookWizard::InitWizardCmdHead()
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_InitWizardCmdHead();
}

long CGuideBookWizard::GetCurrGbWzdCmdIndex()
{
	if (g_pGuideBookWizard == NULL)
	{
		return -1;
	}

	return g_pGuideBookWizard->m_nWzdCmdIndex;
}

CGbWzdCmd* CGuideBookWizard::GetCurrGbWzdCmd()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->In_GetCurrGbWzdCmd();
}

CGbWzdCmd* CGuideBookWizard::GetNextGbWzdCmd()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->In_GetNextGbWzdCmd();
}

CGbWzdCmd* CGuideBookWizard::GetGbWzdCmd(long nCmdIndex)
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return (CGbWzdCmd *)g_pGuideBookWizard->GetAtIndex(nCmdIndex);
}

BOOL CGuideBookWizard::ExecCurr(DWORD dwExecMode)
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_ExecCurrGbWzdCmd(dwExecMode);
}


BOOL CGuideBookWizard::ExecNext(DWORD dwExecMode)
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_ExecNextGbWzdCmd(dwExecMode);
}

BOOL CGuideBookWizard::IsGuideBookFileWzd()
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return (g_pGuideBookWizard->m_strGbFileType == g_strGbFileFilter);
}

BOOL CGuideBookWizard::IsStxmlFileWzd()
{
	ASSERT (g_pGuideBookWizard != NULL);

	return (g_pGuideBookWizard->m_strGbFileType == g_strTGbFileFilter);
}

BOOL CGuideBookWizard::MoveUp(CGbWzdCmd *pWzdCmd)
{
	ASSERT (g_pGuideBookWizard != NULL);

	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_MoveUp(pWzdCmd);
}

BOOL CGuideBookWizard::MoveDown(CGbWzdCmd *pWzdCmd)
{
	ASSERT (g_pGuideBookWizard != NULL);

	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_MoveDown(pWzdCmd);
}

BOOL CGuideBookWizard::DeleteWzdCmd(CGbWzdCmd *pWzdCmd)
{
	ASSERT (g_pGuideBookWizard != NULL);

	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->In_DeleteWzdCmd(pWzdCmd);
}

//获取命令相关函数
CGbWzdCmdGbAttr* CGuideBookWizard::GetCurrWzdCmd_GbAttr()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->In_GetCurrWzdCmd_GbAttr();
}

CGbWzdCmdDeviceModel* CGuideBookWizard::GetCurrWzdCmd_DeviceModel()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->In_GetCurrWzdCmd_DeviceModel();
}

void CGuideBookWizard::SetCurrWzdCmd_GbAttr(CGuideBook *pGuideBook)
{
	CGbWzdCmdGbAttr *pGbAttr = GetCurrWzdCmd_GbAttr();

	if (pGbAttr != NULL)
	{
		pGbAttr->InitByGuideBook(pGuideBook);
	}
}

void CGuideBookWizard::SetCurrWzdCmd_DeviceModel(CDevice *pDevice)
{
	CGbWzdCmdDeviceModel *pGbDvm = GetCurrWzdCmd_DeviceModel();

	if (pGbDvm != NULL)
	{
		pGbDvm->InitByDevice(pDevice);
	}
}

void CGuideBookWizard::SetCurrWzdCmd_DeviceModel(CCpus *pCpus)
{
	CGbWzdCmdDeviceModel *pGbDvm = GetCurrWzdCmd_DeviceModel();

	if (pGbDvm != NULL)
	{
		pGbDvm->SetCpus(pCpus);
	}
}

void CGuideBookWizard::SetCurrWzdCmd_DeviceModel(CCharacteristics *pCharacteristics)
{
	CGbWzdCmdDeviceModel *pGbDvm = GetCurrWzdCmd_DeviceModel();

	if (pGbDvm != NULL)
	{
		pGbDvm->SetCharacteristics(pCharacteristics);
	}
}

//自动向导文件
void CGuideBookWizard::SaveWizard()
{
	if (g_pGuideBookWizard == NULL)
	{
		return;
	}

	g_pGuideBookWizard->In_SaveWizard();
}

void CGuideBookWizard::OpenWizard()
{
	if (g_pGuideBookWizard == NULL)
	{
		return;
	}

	g_pGuideBookWizard->In_OpenWizard();
}

DWORD CGuideBookWizard::GetWzdExecMode()
{
	if (g_pGuideBookWizard == NULL)
	{
		return WZDEXEC_NONE;
	}

	return g_pGuideBookWizard->m_dwWzdExecMode;
}

void CGuideBookWizard::SetWzdExecMode(DWORD dwWzdExecMode)
{
	if (g_pGuideBookWizard == NULL)
	{
		return ;
	}

	g_pGuideBookWizard->m_dwWzdExecMode = dwWzdExecMode;
}

BOOL CGuideBookWizard::IsQuickWizard()
{
	if (g_pGuideBookWizard == NULL)
	{
		return FALSE;
	}

	return g_pGuideBookWizard->m_bQuickWizard;
}

BOOL CGuideBookWizard::IsWordPageVert()
{
	if (g_pGuideBookWizard == NULL)
	{
		return TRUE;
	}

	return g_pGuideBookWizard->m_bWordPageOrientationVert;
}

void CGuideBookWizard::InitWordPage()
{
	if (g_pGuideBookWizard == NULL)
	{
		return ;
	}

	g_pGuideBookWizard->In_InitWordPage();
}

CGbWzdAutoConfig* CGuideBookWizard::GetGbWzdAutoConfig()
{
	if (g_pGuideBookWizard == NULL)
	{
		return NULL;
	}

	return g_pGuideBookWizard->m_pGbWzdAutoConfig;
}

BOOL CGuideBookWizard::IsGbWzdAuto()
{
	return (GetGbWzdAutoConfig() != NULL);
}

BOOL CGuideBookWizard::IsGbWzdAuto_Auto()
{
	ASSERT (g_pGuideBookWizard != NULL);

	if (g_pGuideBookWizard->m_pGbWzdAutoConfig == NULL)
	{
		return FALSE;
	}

	CString strAuto = GetGbWzdAutoConfig()->m_strAuto;

	if (strAuto == _T("1"))
	{
		return TRUE;
	}
	else
		return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL CGuideBookWizard::In_SetGbWizardType(const CString &strGbFileType)
{
	m_strGbFileType = strGbFileType;
	ASSERT ((m_strGbFileType == g_strGbFileFilter) || (m_strGbFileType == g_strTGbFileFilter) );
	return TRUE;
}

//BOOL  CGuideBookWizard::In_InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit, BOOL bQuick)
BOOL  CGuideBookWizard::In_InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit, BOOL bQuick)
{
	m_bQuickWizard = bQuick;
	m_pGuideBook = pGuideBook;
	m_pGbTree = pGbTree;
	m_pMainFrame = pMainFrame;
	m_pWndGbWzd = pWzdWnd;
	m_pRptEdit = pRptEdit;

	//设置模板属性
	CGbWzdCmdGbAttr *pCmdGbAttr = new CGbWzdCmdGbAttr();
	AddNewChild(pCmdGbAttr);

	//创建设备，选择设备数据模型
	CGbWzdCmdDeviceModel *pCmdDvm = new CGbWzdCmdDeviceModel();
	AddNewChild(pCmdDvm);

	//选择子模板
	CGbWzdCmdSelectStxmlFile *pSelStxmlFile = new CGbWzdCmdSelectStxmlFile();
	AddNewChild(pSelStxmlFile);

	return TRUE;
}

//BOOL CGuideBookWizard::In_InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit)
BOOL CGuideBookWizard::In_InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit)
{
	m_pGuideBook = pGuideBook;
	m_pGbTree = pGbTree;
	m_pMainFrame = pMainFrame;
	m_pWndGbWzd = pWzdWnd;
	m_pRptEdit = pRptEdit;

	//选择子模板
	CGbWzdCmdSelectStxmlFile *pSelStxmlFile = new CGbWzdCmdSelectStxmlFile();
	AddNewChild(pSelStxmlFile);


	return TRUE;
}

CGbWzdCmd*  CGuideBookWizard::In_AddFile(const CString &strFile)
{
	CGbWzdCmdInitGbByStxmlFile *p = NULL;
	
	CString strName = GetPathFileNameFromFilePathName(strFile);
	//p = (CGbWzdCmdInitGbByStxmlFile*)FindByName(strName);

	if (p == NULL)
	{
		p = new CGbWzdCmdInitGbByStxmlFile();
		p->m_strName = strName;
		p->m_strID = strFile;
		AddNewChild(p);
		return p;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("已经添加相同名称【%s】的子模板"), strName);
		return NULL;
	}
}

CGbWzdCmd* CGuideBookWizard::In_AddSaveCmd(long &nOldSaveCmdIndex)
{
	POS pos = GetHeadPosition();
	CGbWzdCmd *pFind = NULL;
	CGbWzdCmd *p = NULL;
	nOldSaveCmdIndex = 0;

	while (pos != NULL)
	{
		p = (CGbWzdCmd *)GetNext(pos);

		if (p->GetClassID() == GBWZDCLASSID_SAVE)
		{
			pFind = p;
			break;
		}

		nOldSaveCmdIndex++;
	}

	if (pFind == NULL)
	{
		nOldSaveCmdIndex = -1;
		pFind = new CGbWzdCmdSave();
		AddNewChild(pFind);
	}
	else
	{
		BringToTail(nOldSaveCmdIndex);
	}

	return pFind;
}

void CGuideBookWizard::In_OnGbNodeSelChange(CExBaseObject *pGbNode)
{
	CGbWzdCmd *pCurrCmd = In_GetCurrGbWzdCmd();

	if (pCurrCmd == NULL)
	{
		return;
	}

	ASSERT (pGbNode != NULL);
	UINT nClassID = pGbNode->GetClassID();
	UINT nCmdClassID = pCurrCmd->GetClassID();

	switch (nCmdClassID)
	{
	case GBWZDCLASSID_INITGBBYSTXML:
		{
			CGbWzdCmdInitGbByStxmlFile *pGbWzdCmdInitGbByStxmlFile = (CGbWzdCmdInitGbByStxmlFile*)pCurrCmd;
			
			if (pGbWzdCmdInitGbByStxmlFile->OnGbNodeSelChange(pGbNode))
			{
				BOOL bEnable = pGbWzdCmdInitGbByStxmlFile->GetRootItems() != NULL;
				pCurrCmd->GetGbWzdWnd()->PostMessage(WM_EXEC_GBWZD_NEXT_ENABLE, bEnable ,bEnable);
			}
		}
		break;
	}
	
	if (nClassID == GBCLASSID_ITEMS)
	{
		
	}
}

//向导函数
BOOL CGuideBookWizard::In_IsWizardFinish()
{
	return FALSE;
}

BOOL CGuideBookWizard::In_InitWizardCmdHead()
{
	m_nWzdCmdIndex = 0;
	return (GetCount() > 0);
}

CGbWzdCmd* CGuideBookWizard::In_GetCurrGbWzdCmd()
{
	CGbWzdCmd *pGbWzdCmd = NULL;
//	ASSERT (m_nWzdCmdIndex < GetCount());

	if (m_nWzdCmdIndex >= GetCount())
	{
		pGbWzdCmd = NULL;
		InsertBmkByGlobalDatas();
		InsertDIORsltJdgs();
		InsertItemParas();

		AfxGetMainWnd()->SendMessage(WM_SAVE_GUIDEBOOK_FILE, 0, 0);

		m_pWndGbWzd->PostMessage(WM_EXEC_GBWZD_FINISH, 0, 0);
	}
	else
	{
		pGbWzdCmd = (CGbWzdCmd *)GetAtIndex(m_nWzdCmdIndex);
	}

	return pGbWzdCmd;
}

CGbWzdCmd* CGuideBookWizard::In_GetNextGbWzdCmd()
{
	m_nWzdCmdIndex++;
	return In_GetCurrGbWzdCmd();
}

BOOL CGuideBookWizard::In_ExecCurrGbWzdCmd(DWORD dwExecMode)
{
	CGbWzdCmd *pGbWzdCmd = In_GetCurrGbWzdCmd();
	ASSERT (pGbWzdCmd != NULL);

	if (pGbWzdCmd == NULL)
	{
		return FALSE;
	}
	else
	{
		return pGbWzdCmd->Execute(dwExecMode);
	}
}

BOOL CGuideBookWizard::In_ExecNextGbWzdCmd(DWORD dwExecMode)
{
	CGbWzdCmd *pGbWzdCmd = In_GetCurrGbWzdCmd();
	ASSERT (pGbWzdCmd != NULL);
	BOOL bTrue = FALSE;

	if (pGbWzdCmd == NULL)
	{
		m_pWndGbWzd->PostMessage(WM_EXEC_GBWZD_FINISH, 0, 0);
		return FALSE;
	}
	
	if (!pGbWzdCmd->IsCmdFinish())
	{
		bTrue = pGbWzdCmd->Execute(dwExecMode);
		pGbWzdCmd->UpdateWzdState();
		return bTrue;
	}

	pGbWzdCmd->UpdateWzdState();
	pGbWzdCmd = In_GetNextGbWzdCmd();

	if (pGbWzdCmd == NULL)
	{
		return FALSE;
	}

	bTrue = pGbWzdCmd->Execute(dwExecMode);
	pGbWzdCmd->UpdateWzdState();

	return bTrue;
}

BOOL CGuideBookWizard::In_IsCurrCmdFinish()
{
	CGbWzdCmd *pGbWzdCmd = In_GetCurrGbWzdCmd();
	ASSERT (pGbWzdCmd != NULL);

	if (pGbWzdCmd == NULL)
	{
		return TRUE;
	}

	return pGbWzdCmd->IsCmdFinish();
}

BOOL CGuideBookWizard::In_IsSubWzdCmd(CGbWzdCmd *pWzdCmd)
{
	if (Find(pWzdCmd) != NULL)
	{
		return FALSE;
	}

	return TRUE;
}

long CGuideBookWizard::In_GetWzdCmdIndex(CGbWzdCmd *pWzdCmd)
{
	if (In_IsSubWzdCmd(pWzdCmd))
	{
		CGbWzdCmd *pCurr = In_GetCurrGbWzdCmd();
		CGbWzdCmdList *pCmdList = (CGbWzdCmdList*)pCurr;
		return pCmdList->m_listCmd.FindIndex(pWzdCmd);
	}
	else
	{
		return FindIndex(pWzdCmd);
	}
}

//操作函数
BOOL CGuideBookWizard::In_MoveUp(CGbWzdCmd *pWzdCmd)
{
	POS pos = Find(pWzdCmd);

	if (pos == NULL)
	{
		return FALSE;
	}

	POS posPrev = pos;
	GetPrev(posPrev);

	if (posPrev == NULL)
	{
		return FALSE;
	}

	ChangePosition(pos, posPrev);

	return TRUE;
}

BOOL CGuideBookWizard::In_MoveDown(CGbWzdCmd *pWzdCmd)
{
	POS pos = Find(pWzdCmd);

	if (pos == NULL)
	{
		return FALSE;
	}

	POS posNext = pos;
	GetNext(posNext);

	if (posNext == NULL)
	{
		return FALSE;
	}

	ChangePosition(pos, posNext);

	return TRUE;
}

BOOL CGuideBookWizard::In_DeleteWzdCmd(CGbWzdCmd *pWzdCmd)
{
	POS pos = Find(pWzdCmd);

	if (pos == NULL)
	{
		return FALSE;
	}

	DeleteAt(pos);

	return TRUE;
}

CGbWzdCmdGbAttr* CGuideBookWizard::In_GetCurrWzdCmd_GbAttr()
{
	CGbWzdCmd *pCmd = (CGbWzdCmd*)GetAtIndex(0);

	if (pCmd == NULL)
	{
		return NULL;
	}

	if (pCmd->GetClassID() != GBWZDCLASSID_GBATTR)
	{
		return NULL;
	}

	return (CGbWzdCmdGbAttr*)pCmd;
}

CGbWzdCmdDeviceModel* CGuideBookWizard::In_GetCurrWzdCmd_DeviceModel()
{
	CGbWzdCmd *pCmd = (CGbWzdCmd*)GetAtIndex(1);

	if (pCmd == NULL)
	{
		return NULL;
	}

	if (pCmd->GetClassID() != GBWZDCLASSID_DEVICEMODEL)
	{
		return NULL;
	}

	return (CGbWzdCmdDeviceModel*)pCmd;
}

//自动向导文件
void CGuideBookWizard::In_SaveWizard()
{
	ASSERT (m_pMainFrame != NULL);

	CString strPath;
	strPath = wzd_GetWzdFilePath();

#ifdef GB_USE_XFILEMNGRBASE
	CXFileMngr oFileMngrBase;
	oFileMngrBase.SearchFiles(g_sLangTxt_GuideAutoWizardFile, g_strGbWzdAutoFilePostFix, strPath);
#else
	CFileMngrBase oFileMngrBase;
	oFileMngrBase.SetRootPath(strPath);
	oFileMngrBase.m_strName.Format(_T("%s管理"), g_sLangTxt_GuideAutoWizardFile);
	oFileMngrBase.m_strID = strPath;
	oFileMngrBase.Traverse(strPath, g_strGbWzdAutoFilePostFix, TRUE);
#endif

#ifdef GB_USE_XFILEMNGRBASE
	CDlgXFileMngr dlg(0, g_strGbWzdAutoFilePostFix, g_sLangTxt_GuideAutoWizardFile, &oFileMngrBase, SAVE_FILE_MODE, m_pMainFrame);
#else
	CDlgFileMngr dlg(0, g_strGbWzdAutoFilePostFix, g_sLangTxt_GuideAutoWizardFile, &oFileMngrBase, SAVE_FILE_MODE, m_pMainFrame);
#endif

	if(dlg.DoModal() == IDOK)
	{
		CString strWzdFile = dlg.GetFileName();
		SaveXmlFile(strWzdFile, CGbWzdToolXmlRWKeys::g_pXmlKeys);
	}
}

void CGuideBookWizard::In_OpenWizard()
{
	DeleteAll();
	ASSERT (m_pMainFrame != NULL);

	CString strPath;
	strPath = wzd_GetWzdFilePath();

#ifdef GB_USE_XFILEMNGRBASE
	CXFileMngr oFileMngrBase;
	oFileMngrBase.SearchFiles(g_sLangTxt_GuideAutoWizardFile, g_strGbWzdAutoFilePostFix, strPath);

	CDlgXFileMngr dlg(0, g_strGbWzdAutoFilePostFix, g_sLangTxt_GuideAutoWizardFile, &oFileMngrBase, SAVE_FILE_MODE, m_pMainFrame);
#else
	CFileMngrBase oFileMngrBase;
	oFileMngrBase.SetRootPath(strPath);
	oFileMngrBase.m_strName.Format(_T("%s管理"), g_sLangTxt_GuideAutoWizardFile);
	oFileMngrBase.m_strID = strPath;
	oFileMngrBase.Traverse(strPath, g_strGbWzdAutoFilePostFix, TRUE);

	CDlgFileMngr dlg(0, g_strGbWzdAutoFilePostFix, g_sLangTxt_GuideAutoWizardFile, &oFileMngrBase, SAVE_FILE_MODE, m_pMainFrame);
#endif

	if(dlg.DoModal() == IDOK)
	{
		CString strWzdFile = dlg.GetFileName();
		OpenXmlFile(strWzdFile,CGbWzdToolXmlRWKeys::CGuideBookWizardKey(), CGbWzdToolXmlRWKeys::g_pXmlKeys);
	}
}

void CGuideBookWizard::In_InitWordPage()
{
	if (CGbDevConfig::IsWordPageDir_Horz())
	{
		m_pRptEdit->InitPage(1);
		m_bWordPageOrientationVert = FALSE;
	}
	else
	{
		m_bWordPageOrientationVert = TRUE;
		g_pGuideBookWizard->m_pRptEdit->InitPage(0);
	}
}

//////////////////////////////////////////////////////////////////////////
//
long CGuideBookWizard::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CGuideBookWizard::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

BSTR CGuideBookWizard::GetXmlElementKey() 
{
	return CGbWzdToolXmlRWKeys::CGuideBookWizardKey();
}

CExBaseObject* CGuideBookWizard::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdCmdInitGbByStxmlFileKey())
	{
		return new CGbWzdCmdInitGbByStxmlFile();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdCmdGbAttrKey())
	{
		return new CGbWzdCmdGbAttr();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdCmdDeviceModelKey())
	{
		return new CGbWzdCmdDeviceModel();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdCmdSaveKey())
	{
		return new CGbWzdCmdSave();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdCmdSelectStxmlFileKey())
	{
		return new CGbWzdCmdSelectStxmlFile();
	}

	return NULL;
}

void CGuideBookWizard::InsertBmkByGlobalDatas()
{
	CGuideBook *pGuideBook = GetCGuideBook();
	CReportMap *pReportMap = pGuideBook->GetReportMap();
	CDvmData *pGlobalDatas = (CDvmData *)pGuideBook->FindByID(g_strGbGlobalDatasID);

	POS pos = pGlobalDatas->GetHeadPosition();
	CDvmData *pData = NULL;
	CRptData *pRptData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pGlobalDatas->GetNext(pos);

 		pRptData = (CRptData *)pReportMap->FindByID(pData->m_strID);

		if (pRptData == NULL)
		{
			pRptData = new CRptData();
			pReportMap->AddNewChild(pRptData);
		}
			
 		pRptData->m_strName = pData->m_strName;
 		pRptData->m_strID = pData->m_strID;

 		CRptBkmk *pBkmk = new CRptBkmk();
 		pBkmk->m_strID.Format(_T("Bmk%s"), pData->m_strID);
 		pBkmk->m_strDataAttrID = _T("value");
 		pRptData->AddNewChild(pBkmk);
	}
}

void CGuideBookWizard::InsertDIORsltJdgs()
{
	if (m_pGbWzdAutoConfig == NULL)
	{
		return;
	}

	CTestItemMngr *pItemMngr = (CTestItemMngr *)m_pGbWzdAutoConfig->FindByClassID(GBCLASSID_TESTITEMMNGR);

	if (pItemMngr == NULL)
	{
		return;
	}

	CGuideBook *pGuideBook = GetCGuideBook();
	CDevice *pDevice = (CDevice *)pGuideBook->FindByClassID(GBCLASSID_DEVICE);

	POS pos = pItemMngr->GetHeadPosition();
	CItems *pItems = NULL;
	CExBaseList oListItems;

	while (pos != NULL)
	{
		CGbWzdAutoItems *pWzdAutoItems = (CGbWzdAutoItems *)pItemMngr->GetNext(pos);

		pItems = new CItems();
		pItems->m_strName = pWzdAutoItems->m_strName;
		pItems->m_strID = pWzdAutoItems->m_strID;
		pDevice->AddNewChild(pItems);

		AddSubItems(pItems, pWzdAutoItems);
		pItems->InitAfterRead();
		oListItems.AddTail(pItems);	
	}	

	m_pGbTree->SendMessage(WM_USER + 1056, (WPARAM)&oListItems, (LPARAM)&oListItems);
	oListItems.RemoveAll();
}

void CGuideBookWizard::InsertItemParas()
{
	if (m_pGbWzdAutoConfig == NULL)
	{
		return;
	}

	CTestItemParaMngr *pItemParaMngr = (CTestItemParaMngr *)m_pGbWzdAutoConfig->FindByClassID(GBCLASSID_TESTITEMPARAMNGR);

	if (pItemParaMngr == NULL)
	{
		return;
	}

	CGuideBook *pGuideBook = GetCGuideBook();
	CDevice *pDevice = (CDevice *)pGuideBook->FindByClassID(GBCLASSID_DEVICE);

	POS pos = pItemParaMngr->GetHeadPosition();

	while (pos != NULL)
	{
		CGbWzdAutoItemPara *pWzdAutoItemPara = (CGbWzdAutoItemPara *)pItemParaMngr->GetNext(pos);

		if (pWzdAutoItemPara->GetCount() == 0)
		{
			continue;
		}
	
		CCommCmd *pCommCmd = NULL;
		pCommCmd = (CCommCmd *)pDevice->FindItemByID(pWzdAutoItemPara->m_strID, GBCLASSID_COMMCMD);

		if (pCommCmd == NULL)
		{
			continue;
		}

		CCmd *pCmd = pCommCmd->GetCmd();
		pCmd->DeleteAll();

		pCmd->AppendCloneEx(*pWzdAutoItemPara);
	}
}

void CGuideBookWizard::AddSubItems(CItems *pItems, CGbWzdAutoItems *pGbWzdAutoItems)
{
	POS pos = pGbWzdAutoItems->GetHeadPosition();
	CItems *pSubItems = NULL;
	CExBaseObject *pObj = NULL;
	CGbWzdAutoItems *pGbWzdAutoSubItems = NULL;
	CGbWzdAutoSafety *pWzdAutoSafety = NULL;

	while (pos != NULL)
	{
		pObj = pGbWzdAutoItems->GetNext(pos);

		if (pObj->GetClassID() == GBCLASSID_GBWZDAUTOITEMS)
		{
			pGbWzdAutoSubItems = (CGbWzdAutoItems *)pObj;
			pSubItems = new CItems();
			pSubItems->m_strName = pGbWzdAutoSubItems->m_strName;
			pSubItems->m_strID = pGbWzdAutoSubItems->m_strID;
			pItems->AddNewChild(pSubItems);

			AddSubItems(pSubItems, pGbWzdAutoSubItems);
		}

		else if (pObj->GetClassID() == GBCLASSID_GBWZDAUTOSAFETY)
		{
			pWzdAutoSafety = (CGbWzdAutoSafety *)pObj;
			CSafety *pSafety = new CSafety();
			pSafety->m_strName = pWzdAutoSafety->m_strName;
			pSafety->m_strID = pWzdAutoSafety->m_strID;
			pItems->AddNewChild(pSafety);
			pSafety->m_strType = pWzdAutoSafety->m_strItemType;
			pSafety->m_nManyDeviceTestMode = pWzdAutoSafety->m_nManyRptTestMode;
			pSafety->InitDataMode();

			CScriptTextInit *pScriptInit = (CScriptTextInit *)pWzdAutoSafety->FindByClassID(GBCLASSID_SCRIPTTEXT_INIT);
			if (pScriptInit != NULL)
			{
				CScriptTextInit *pNew = (CScriptTextInit *)pScriptInit->Clone();
				pSafety->AddNewChild(pNew);
			}

			CScriptTextResult *pScriptResult = (CScriptTextResult *)pWzdAutoSafety->FindByClassID(GBCLASSID_SCRIPTTEXT_RESULT);
			if (pScriptResult != NULL)
			{
				CScriptTextResult *pNew = (CScriptTextResult *)pScriptResult->Clone();
				pSafety->AddNewChild(pNew);
			}

			pSafety->InitAfterRead();

			if (pSafety->m_strID.Find(_T("DI")) >= 0)
			{
				AddRsltJdgBmk(pSafety, m_pGbWzdAutoConfig->m_strBmk_DITest, _T("value"));
			}

			else if (pSafety->m_strID.Find(_T("DO")) >= 0)
			{
				AddRsltJdgBmk(pSafety, m_pGbWzdAutoConfig->m_strBmk_DOTest, _T("value"));
			}
		}
	}
}

void CGuideBookWizard::AddRsltJdgBmk(CSafety *pSafety, const CString &strBmkText, const CString &strBmkAttrid)
{
	CRptData *pRptData = NULL;
	CReportMap *pReportMap = NULL;
	CRptBkmk *pBkmk = NULL;

	pReportMap = (CReportMap *)pSafety->FindByClassID(RPTCLASSID_RPTREPORTMAP);

	if (pReportMap == NULL)
	{
		pReportMap = new CReportMap();
		pSafety->AddNewChild(pReportMap);
	}
	
	pRptData = (CRptData *)pReportMap->FindByID(g_strTestResultDescriptKey);

	if (pRptData == NULL)
	{
		pRptData = new CRptData();
		pReportMap->AddNewChild(pRptData);
		pRptData->m_strName = _T("结果描述");
		pRptData->m_strID = g_strTestResultDescriptKey;
	}
	
	pBkmk = new CRptBkmk();
	pBkmk->m_strID = strBmkText;
	pBkmk->m_strDataAttrID = strBmkAttrid;
	pRptData->AddNewChild(pBkmk);
}