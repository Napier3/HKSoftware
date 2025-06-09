#include "stdafx.h"
#include "GbInsertStxmlFileTool.h"
#include "..\XLanguageResourceAts.h"
#include "..\..\Module\GuideBook\ReportMap\WPSRptEdit.h"
//////////////////////////////////////////////////////////////////////////
CGbInsertStxmlFileTool::CGbInsertStxmlFileTool()
{
	m_pGbStxml = NULL;
	m_pGuideBookDest = NULL;

	m_pRptEditSrc = NULL;
	m_pRptEditDest = NULL;

	m_pParentItems = NULL;
	m_bDataChanged = FALSE;
	m_pNewRootItems = NULL;

// 	m_oGbInsertStxmlFileMngr->SetParent(this);
// 	m_oGbtBatchItemGroups->SetParent(this);

	m_pProgressDlg = NULL;
	m_pInsertThread = NULL;
	m_bExInsertState = FALSE;

	//pThread->ResumeThread();

	m_pGbtBatchItemGroups = new CGbtBatchItemGroups();
	AddNewChild(m_pGbtBatchItemGroups);
	m_pGbInsertStxmlFileMngr = new CGbInsertStxmlFileMngr();
	AddNewChild(m_pGbInsertStxmlFileMngr);
	m_pGbWzdDatasetRefMngr = new CGbWzdDatasetRefMngr();
	AddNewChild(m_pGbWzdDatasetRefMngr);

	m_pGbtCommCmdItemEditMngr = new CGbtCommCmdItemEditMngr();
	AddNewChild(m_pGbtCommCmdItemEditMngr);

	m_bInsertRootItems = TRUE;
	m_nAddRptGroupTitle = 1;
}

void CGbInsertStxmlFileTool::SetParentWnd(CWnd *pWnd)
{	
	m_pParentWnd = pWnd;
	CGbWzdInsertThread *pThread = CGbWzdInsertThread::CreateTestCtrlThread(m_pParentWnd);
	m_pInsertThread = pThread;
}


CGbInsertStxmlFileTool::~CGbInsertStxmlFileTool()
{
	ClearListDataset();
	Free();
	m_oListStxmlItem.RemoveAll();
	m_oListNewItems.RemoveAll();

	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->DestroyWindow();
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	}

	CGbWzdInsertThread *pThread = (CGbWzdInsertThread*)m_pInsertThread;
	m_pInsertThread = NULL;

	if (pThread != NULL)
	{
		if (pThread->GetParentWnd() != NULL)
		{
			pThread->PostThreadMessage(WM_QUIT, 0, 0);
		}
	}
}


long CGbInsertStxmlFileTool::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strRootItemsNameKey, oNode, m_strRootItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strRootItemsIDKey, oNode, m_strRootItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strIec61850ConfigFileKey, oNode, m_strIec61850ConfigFile);

	xml_GetAttibuteValue(pXmlKeys->m_strAddRptGroupTitleKey, oNode, m_nAddRptGroupTitle);
	//m_oGbInsertStxmlFileMngr

	return 0;
}

long CGbInsertStxmlFileTool::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strRootItemsNameKey, oElement, m_strRootItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strRootItemsIDKey, oElement, m_strRootItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strIec61850ConfigFileKey, oElement, m_strIec61850ConfigFile);
	xml_SetAttributeValue(pXmlKeys->m_strAddRptGroupTitleKey, oElement, m_nAddRptGroupTitle);

	return 0;
}

CExBaseObject* CGbInsertStxmlFileTool::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtBatchItemGroupsKey())
	{
		return new CGbtBatchItemGroups();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbtCommCmdItemEditMngrKey())
	{
		return new CGbtCommCmdItemEditMngr();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbInsertStxmlFileMngrKey())
	{
		return new CGbInsertStxmlFileMngr();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdDatasetRefsKey())
	{
		return new CGbWzdDatasetRefMngr();
	}

	return NULL;
}

BOOL CGbInsertStxmlFileTool::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return TRUE;
	}

	CGbInsertStxmlFileTool *pTool = (CGbInsertStxmlFileTool*)pDesObj;
	pTool->m_strRootItemsID = m_strRootItemsID;
	pTool->m_strRootItemsName = m_strRootItemsName;
	pTool->m_strName = m_strName;
	pTool->m_strID = m_strID;
	pTool->m_strIec61850ConfigFile = m_strIec61850ConfigFile;

	return TRUE;
}

CBaseObject* CGbInsertStxmlFileTool::Clone()
{
	CGbInsertStxmlFileTool *pNew = new CGbInsertStxmlFileTool();
	Copy(pNew);
	return pNew;
}


void CGbInsertStxmlFileTool::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CScriptTextMngr *pScriptTextMngr = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBTWZDCLASSID_BATCHITEMGROUPS:
			m_pGbtBatchItemGroups = (CGbtBatchItemGroups*)p;
			break;

		case GBTWZDCLASSID_COMMCMDEDITMNGR:
			m_pGbtCommCmdItemEditMngr = (CGbtCommCmdItemEditMngr*)p;
			break;

		case GBTWZDCLASSID_GBTINSERTSTXMLFILEMNGR:
			m_pGbInsertStxmlFileMngr = (CGbInsertStxmlFileMngr *)p;
			break;

		case GBTWZDCLASSID_GBTDATASETREFMNGR:
			m_pGbWzdDatasetRefMngr = (CGbWzdDatasetRefMngr *)p;
			break;

		default:
			break;
		}
	}

	if (m_pGbtBatchItemGroups == NULL)
	{
		m_pGbtBatchItemGroups = new CGbtBatchItemGroups;
		AddNewChild(m_pGbtBatchItemGroups);
	}

	if (m_pGbtCommCmdItemEditMngr == NULL)
	{
		m_pGbtCommCmdItemEditMngr = new CGbtCommCmdItemEditMngr;
		AddNewChild(m_pGbtCommCmdItemEditMngr);
	}

	if (m_pGbInsertStxmlFileMngr == NULL)
	{
		m_pGbInsertStxmlFileMngr = new CGbInsertStxmlFileMngr();
		AddNewChild(m_pGbInsertStxmlFileMngr);
	}

	if (m_pGbWzdDatasetRefMngr == NULL)
	{
		m_pGbWzdDatasetRefMngr = new CGbWzdDatasetRefMngr();
		AddNewChild(m_pGbWzdDatasetRefMngr);
	}
}

void CGbInsertStxmlFileTool::Free()
{
	if (m_pGbStxml != NULL)
	{
		delete m_pGbStxml;
		m_pGbStxml = NULL;
	}

	m_pGbStxml = NULL;

	if (m_pRptEditSrc != NULL)
	{
		m_pRptEditSrc->ExitWord(FALSE);
		delete m_pRptEditSrc;
		m_pRptEditSrc = NULL;
	}

	DeleteAll();
	m_pGbtBatchItemGroups = NULL;
	m_pGbInsertStxmlFileMngr = NULL;
	m_pGbWzdDatasetRefMngr = NULL;
	m_pGbtCommCmdItemEditMngr = NULL;

	InitAfterRead();
}

CRptEditInterface* CGbInsertStxmlFileTool::CreateRptEdit()
{
	CRptEditInterface* pRptEdit = NULL;

	CString strReportMode = CTCtrlCntrConfig::GetReportMode();
	if (strReportMode == REPORTFILL_PROGID_WORD)
	{
		pRptEdit = new CWordRptEdit();
	}
	else if (strReportMode == REPORTFILL_PROGID_WPS)
	{
		pRptEdit = new CWPSRptEdit();
	}

	return pRptEdit;
}

BOOL CGbInsertStxmlFileTool::Init(const CString &strStxmlFile)
{
	Free();

	m_strStxmlFile = strStxmlFile;

	m_pRptEditSrc = CreateRptEdit();
	m_pRptEditSrc->InitRptEdit();

	m_pGbStxml = new CGuideBook();
	
	m_pGbStxml->m_strGuideBookFileType = ParseFilePostfix(m_strStxmlFile);
	m_pGbStxml->m_strGuideBookFileType.MakeLower();

	if (m_pRptEditDest != NULL)
	{
		m_pRptEditDest->CopyApp(m_pRptEditSrc);
	}

	m_pGbStxml->Open(strStxmlFile);

	//如果是子模板，则处理实例化时的映射关系
	if (m_pGbStxml->m_strGuideBookFileType == g_strTGbFileFilter)
	{
		InitGbtDataInterfaceMaps();
		XMatch();
	}

	return TRUE;
}

BOOL CGbInsertStxmlFileTool::Init(CGuideBook *pGuideBookDest, CXKeyDB *pKeyDB, CRptEditInterface *pRptEditDest)
{
	m_pGuideBookDest = pGuideBookDest;
	m_pXKeyDB = pKeyDB;

	m_pRptEditDest = pRptEditDest;

	ASSERT (m_pGuideBookDest != NULL);
	ASSERT (m_pXKeyDB != NULL);
	
	return TRUE;
}

void CGbInsertStxmlFileTool::AddDataset(CDataSet *pDataset)
{
	if (m_listDataset.Find(pDataset) == NULL)
	{
		m_listDataset.AddTail(pDataset);
		m_listRefDatas.Append(pDataset);

		CGbWzdDatasetRef *pNew = new CGbWzdDatasetRef();
		pNew->SetDataSet(pDataset);
		m_pGbWzdDatasetRefMngr->AddNewChild(pNew);
	}

	return;
}

void CGbInsertStxmlFileTool::ClearListDataset()	
{
	m_listDataset.RemoveAll();	
	m_listRefDatas.RemoveAll();	
	m_pGbWzdDatasetRefMngr->DeleteAll();
}

//子模板插入到的项目分类对象，如果没有指定，则插入到Device的根目录下
void CGbInsertStxmlFileTool::SetParentItems(CExBaseList *pParent)
{
	m_pParentItems = pParent;
}

void CGbInsertStxmlFileTool::XMatch(long nIndex, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	m_bDataChanged = TRUE;

	m_oXMatchList.DeleteAll();
	m_oXMatchList.Init(&m_listRefDatas, m_pXKeyDB);
	
	m_pGbInsertStxmlFileMngr->XMatch(m_oXMatchList, nIndex, bNotUpdateSingle, bNotUpdateNone);
// 	POS pos = GetHeadPosition();
// 	CGbtDataInterfaceMap *pMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
// 		pMap->XMatch(m_oXMatchList);
// 	}
}

BOOL CGbInsertStxmlFileTool::ValidateMapKeys(CString &strErrorMsg)
{
	BOOL bTrue = TRUE;
// 	POS pos = GetHeadPosition();
// 	CGbtDataInterfaceMap *pMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
// 		
// 		if (!pMap->ValidateMapKeys(strErrorMsg))
// 		{
// 			bTrue = FALSE;
// 		}
// 	}

	bTrue = m_pGbInsertStxmlFileMngr->ValidateMapKeys(strErrorMsg);

	return bTrue;
}

BOOL CGbInsertStxmlFileTool::ValidateBatchItemsGroups(CString &strErrorMsg)
{
	return m_pGbtBatchItemGroups->ValidateBatchItemsGroups(strErrorMsg);
}

CDevice* CGbInsertStxmlFileTool::GetCurrDeviceDest()
{
	CDevice *pDevice = NULL;
	
	if (m_pParentItems->GetClassID() == GBCLASSID_DEVICE)
	{
		pDevice = (CDevice*)m_pParentItems;
	}
	else
	{
		pDevice = (CDevice*)m_pParentItems->GetAncestor(GBCLASSID_DEVICE);
	}

	return pDevice;
}

UINT CGbInsertStxmlFileTool::ExecInsertThread(LPVOID pParam)
{
	CGbInsertStxmlFileTool *pTool = (CGbInsertStxmlFileTool*)pParam;

	CWnd *pWnd = CWnd::GetDesktopWindow();
	pTool->m_pProgressDlg = new CThreadProgrssDlg(pWnd);//pTool->m_pParentWnd);
	pTool->m_pProgressDlg->CreateThreadDlg(pWnd, _T(""));//pTool->m_pParentWnd, _T(""));
	//pTool->ExecInsertEx(pTool->m_pProgressDlg);

	while (pTool->m_bExInsertState)
	{
		Sleep(100);
	}

	return 0;
}

CExBaseObject* CGbInsertStxmlFileTool::ExecInsert()
{
	m_bExInsertState = TRUE;

	m_pGbtCommCmdItemEditMngr->EditCommCmdItems();
	ExecInsertEx((CGbWzdInsertThread*)m_pInsertThread);
	m_bExInsertState = FALSE;

	return NULL;
}

long CGbInsertStxmlFileTool::GetProgressStepCount()
{
	long nCount = m_pGbInsertStxmlFileMngr->GetProgressStepCount();
	long nBatchGroup = m_pGbtBatchItemGroups->GetCount();

	if (nBatchGroup == 0)
	{
		nBatchGroup = 1;
	}

	return nBatchGroup * nCount * 2 + 4;
}

CExBaseObject* CGbInsertStxmlFileTool::ExecInsertEx(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->SetMaxRange(GetProgressStepCount());
	}

	InsertRootItems(pThreadProgress);
	InitListStxmlItem();
	InsertSysParas(pThreadProgress);
	InsertCharacters(pThreadProgress);
	InsertScriptLibLocal(pThreadProgress);
	InsertGlobalDatas(pThreadProgress);
	InsertExtendRptDef(pThreadProgress);
	InsertReportMap(pThreadProgress);

	if (m_pGbStxml->IsGuideBookTemplateFile())
	{
		ExecInsert_Stxml(pThreadProgress);
	}
	else
	{
		ExecInsert_Gbxml(pThreadProgress);
	}

	if (pThreadProgress != NULL)
	{
		pThreadProgress->Exit();
	}

	m_pParentWnd->PostMessage(WM_WZD_INSERT_STXML_FINISH, 0, 0);
	m_pInsertThread = NULL;

	return NULL;
}

CExBaseObject* CGbInsertStxmlFileTool::ExecInsert_Stxml(CThreadProgressInterface *pThreadProgress)
{
	wzd_InsertIecConfigMacroTest(m_strIec61850ConfigFile, m_pNewRootItems);

	m_pGbInsertStxmlFileMngr->InitDatasetList(NULL);

	//插入1级标题
	long nStart = m_pRptEditDest->GetCurrPos();
	m_pRptEditDest->InsertTitle(m_strRootItemsName, 1);

	if (m_pGbtBatchItemGroups->GetCount() == 0)
	{
		//没有批量组别
		InsertByGbtBatchItemGroup(NULL, pThreadProgress);
	}
	else
	{
		if (m_pGbtBatchItemGroups->m_nBatchItemsMode == BATCH_ITEMS_MODE_EXTERNER)
		{
			POS pos = m_pGbtBatchItemGroups->GetHeadPosition();
			CGbtBatchItemGroup *pGroup = NULL;

			while (pos != NULL)
			{
				pGroup = (CGbtBatchItemGroup *)m_pGbtBatchItemGroups->GetNext(pos);
				InsertByGbtBatchItemGroup(pGroup, pThreadProgress);
			}
		}
		else
		{
			POS pos = m_pGbInsertStxmlFileMngr->GetHeadPosition();
			CGbInsertStxmlFile *pStxmlFile = NULL;

			while (pos != NULL)
			{
				pStxmlFile = (CGbInsertStxmlFile *)m_pGbInsertStxmlFileMngr->GetNext(pos);
				pStxmlFile->m_nAddRptGroupTitle = m_nAddRptGroupTitle;
				pStxmlFile->ExecInsertByBatchItemGroups(m_pGbtBatchItemGroups, m_pNewRootItems, m_oListStxmlItem, pThreadProgress);
			}
		}
	}

	long nEnd = m_pRptEditDest->GetCurrPos();
	m_pRptEditDest->AddArea(m_pNewRootItems, nStart, nEnd);

	return NULL;
}

CExBaseObject* CGbInsertStxmlFileTool::ExecInsert_Gbxml(CThreadProgressInterface *pThreadProgress)
{
	CGbInsertStxmlFile oGbInsertStxmlFile;

	oGbInsertStxmlFile.InitGbFileInsert(m_strStxmlFile, m_pRptEditDest, m_pRptEditSrc);

	if (m_strRootItemsName.Find(_T("X")) == 0)   //电源插件或DIO插件
	{
		m_pRptEditDest->InsertTitle(m_strRootItemsName, 1);   //插入一级标题
	}

	oGbInsertStxmlFile.ExcuteInsertFile(m_pNewRootItems, m_oListStxmlItem, pThreadProgress);

	return NULL;
}

void CGbInsertStxmlFileTool::InsertRootItems(CThreadProgressInterface *pThreadProgress)
{
	if (m_bInsertRootItems)
	{

	}
	else
	{

	}

	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(/*_T("初始化........")*/g_sLangTxt_Initial);
	}

	CItems *pNewRootItems = new CItems();
	pNewRootItems = new CItems();
	pNewRootItems->m_strName = m_strRootItemsName;
	pNewRootItems->m_strID   = m_strRootItemsID;
	m_pParentItems->AddNewChild(pNewRootItems);

	m_oListNewItems.AddTail(pNewRootItems);
	m_pNewRootItems = pNewRootItems;

	m_pNewRootItems->m_strWzdMapFile = m_strWzdFile;
	m_pNewRootItems->m_strStxmlFile  = m_strStxmlFile;
}

void CGbInsertStxmlFileTool::InitListStxmlItem()
{
	CDevice *pDevice = m_pGbStxml->GetDevice();
	pDevice->SelectAllRootItem(m_oListStxmlItem);
}


void CGbInsertStxmlFileTool::InsertSysParas(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(/*_T("处理子模板测试参数........")*/g_sLangTxt_DealSubTemTestPara);
	}

	CDevice *pDeviceSrc = m_pGbStxml->GetDevice();
	CDevice *pDeviceDest = m_pGuideBookDest->GetDevice();

	CSysParas *pSysParaSrc = pDeviceSrc->GetSysParas();
	CSysParas *pSysParaDest = pDeviceDest->GetSysParas();

	POS pos = pSysParaSrc->GetHeadPosition();
	CDataObj *pData = NULL;
	CDataObj *pNew = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDeviceSrc->GetNext(pos);

		if (pSysParaDest->FindByID(pData->m_strID) == NULL)
		{
			pNew = (CDataObj *)pData->Clone();
			pSysParaDest->AddNewChild(pNew);
		}
	}
}

void CGbInsertStxmlFileTool::InsertScriptLibLocal(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->ShowMsg(/*_T("处理子模板测试参数........")*/g_sLangTxt_DealSubTemTestPara);
	}

	CScriptTextMngr *pLibSrc = m_pGbStxml->GetScriptLibLocal();
	CScriptTextMngr *pLibDest = m_pGuideBookDest->GetScriptLibLocal();

	pLibDest->Import(pLibSrc);
}

void CGbInsertStxmlFileTool::InsertCharacters(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(_T("处理特性曲线........"));
	}

	CDevice *pDeviceSrc = m_pGbStxml->GetDevice();
	CDevice *pDeviceDest = m_pGuideBookDest->GetDevice();

	CCharacteristics *pCharsSrc = pDeviceSrc->GetCharacteristics();
	CCharacteristics *pCharsDest = pDeviceDest->GetCharacteristics();

	POS pos = pCharsSrc->GetHeadPosition();
	CCharacteristic *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CCharacteristic *)pDeviceSrc->GetNext(pos);
		pCharsDest->AddCharTempClone(pSrc);
	}
}

void CGbInsertStxmlFileTool::InsertGlobalDatas(CThreadProgressInterface *pThreadProgress)
{
	CDvmDataset *pGlobalDatasSrc = (CDvmDataset *)m_pGbStxml->FindByID(g_strGbGlobalDatasID);
	CDvmDataset *pGlobalDatasDest = (CDvmDataset *)m_pGuideBookDest->FindByID(g_strGbGlobalDatasID);

	if (pGlobalDatasSrc == NULL)
	{
		return;
	}

	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(_T("处理全局数据........"));
	}
	
	pGlobalDatasDest->AppendCloneWithoutRepeat(pGlobalDatasSrc);
}

void CGbInsertStxmlFileTool::InsertExtendRptDef(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(_T("处理报告模板定义........"));
	}

	CDvmDataset *pExtendRptDefSrc = m_pGbStxml->m_pExtendRptTemplateDef;
	CDvmDataset *pExtendRptDefDest = m_pGuideBookDest->m_pExtendRptTemplateDef;

	if(pExtendRptDefSrc == NULL)
	{
		return;
	}

	if (pExtendRptDefDest == NULL)
	{
		pExtendRptDefDest = m_pGuideBookDest->GetExtendRptTemplateDef(TRUE);
	}

	pExtendRptDefDest->AppendCloneWithoutRepeat(pExtendRptDefSrc);
}

void CGbInsertStxmlFileTool::InsertReportMap(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(_T("处理报告数据........"));
	}

	//先处理guidebook下的ReportMap
	CReportMap *pReportMapSrc = (CReportMap *)m_pGbStxml->GetReportMap();
	CReportMap *pReportMapDest = (CReportMap *)m_pGuideBookDest->GetReportMap();

	POS pos = pReportMapSrc->GetHeadPosition();
	CRptData *pSrc = NULL;

	while(pos != NULL)
	{
		pSrc = (CRptData *)pReportMapSrc->GetNext(pos);
		pReportMapDest->AddRptDataClone(pSrc);
	}

	//再处理Device下的ReportMap
	CDevice *pDeviceSrc = m_pGbStxml->GetDevice();
	CDevice *pDeviceDest = m_pGuideBookDest->GetDevice();

	pReportMapSrc = (CReportMap *)pDeviceSrc->GetReportMap();
	pReportMapDest = (CReportMap *)pDeviceDest->GetReportMap();

	pos = pReportMapSrc->GetHeadPosition();
	pSrc = NULL;

	while(pos != NULL)
	{
		pSrc = (CRptData *)pReportMapSrc->GetNext(pos);
		pReportMapDest->AddRptDataClone(pSrc);
	}
}

// 
// BOOL CGbInsertStxmlFileTool::ExecInsert(CXMatchList &oXMatchList)
// {
// 	return FALSE;
// }

void CGbInsertStxmlFileTool::InitGbtDataInterfaceMaps()
{
	CDevice *pDevice = m_pGbStxml->GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	m_pGbInsertStxmlFileMngr->InitGbtDataInterfaceMaps(pDevice, m_strStxmlFile, m_pRptEditDest, m_pRptEditSrc);
	m_pGbtBatchItemGroups->InitListBatchItem(m_pGbStxml);

	m_pGbtCommCmdItemEditMngr->InitGuideBookDest(m_pGuideBookDest);
	m_pGbtCommCmdItemEditMngr->InitGbtCommCmdItemEdit(m_pGbStxml);
}


void CGbInsertStxmlFileTool::InsertByGbtBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CThreadProgressInterface *pThreadProgress)
{
	m_pGbInsertStxmlFileMngr->m_nAddRptGroupTitle = m_nAddRptGroupTitle;

	//每一个grou，创建一个Items
	if (pBatchGroup != NULL)
	{
		CItems *pNewItems = new CItems();
		pNewItems->m_strName = pBatchGroup->m_strName;
		pNewItems->m_strID = pBatchGroup->m_strID;
		m_pNewRootItems->AddNewChild(pNewItems, TRUE);
		m_pGbInsertStxmlFileMngr->ExecInsertByBatchItemGroup(pBatchGroup, pNewItems, m_oListStxmlItem, pThreadProgress);
	}
	else
	{	
		//没有定义批量插入组别，则直插入子模板组的项目
		m_pGbInsertStxmlFileMngr->ExecInsertByBatchItemGroup(pBatchGroup, m_pNewRootItems, m_oListStxmlItem, pThreadProgress);
	}
}

void CGbInsertStxmlFileTool::InitTool(CGbInsertStxmlFileTool *pTool)
{
	m_strRootItemsID = pTool->m_strRootItemsID;
	m_strRootItemsName = pTool->m_strRootItemsName;
	m_strName = pTool->m_strName;
	m_strID = pTool->m_strID;
	m_strIec61850ConfigFile = pTool->m_strIec61850ConfigFile;

	//初始化数据集
	InitDatasetList(pTool->m_pGbWzdDatasetRefMngr);

	//初始化子模板文件组
	InitGbInsertStxmlFileMngr(pTool->m_pGbInsertStxmlFileMngr);

	//初始化批量组
	InitGbtBatchItemGroups(pTool->m_pGbtBatchItemGroups);

	InitCmdItemEditMngr(pTool->m_pGbtCommCmdItemEditMngr);
}

void CGbInsertStxmlFileTool::OpenWzdFile(const CString &strWzdFile)
{
	m_strWzdFile = strWzdFile;
	CGbInsertStxmlFileTool oTool;
	oTool.OpenXmlFile(strWzdFile, CGbWzdToolXmlRWKeys::CGbInsertStxmlFileToolKey(), CGbWzdToolXmlRWKeys::g_pXmlKeys);

	//检查打开的文件数据的有效性
	CGbInsertStxmlFile *pFile = (CGbInsertStxmlFile*)oTool.m_pGbInsertStxmlFileMngr->GetHead();

	if (pFile != NULL)
	{
		if (pFile->GetClassID() == GBTWZDCLASSID_GBTINSERTSTXMLFILE)
		{
			if (pFile->m_strStxmlFile.CompareNoCase(m_strStxmlFile) != 0)
			{
				CString strMsg;
				strMsg.Format(/*_T("打开的向导文件：\r\n【%s】\r\n子模板：\r\n【%s】\r\n与当前子模板：\r\n【%s】\r\n不一致！")*/g_sLangTxt_OpenedWizardFile
					, strWzdFile, pFile->m_strStxmlFile, m_strStxmlFile);
				AfxMessageBox(strMsg, MB_OK | MB_ICONERROR);
			}
		}
	}

	InitTool(&oTool);
}

void CGbInsertStxmlFileTool::SaveWzdFile(const CString &strWzdFile)
{
	m_strWzdFile = strWzdFile;
	SaveXmlFile(strWzdFile, CGbWzdToolXmlRWKeys::g_pXmlKeys);
}

void CGbInsertStxmlFileTool::InitDatasetList(CGbWzdDatasetRefMngr *pWzdDatasetMngr)
{
	ClearListDataset();
	POS pos = pWzdDatasetMngr->GetHeadPosition();
	CGbWzdDatasetRef *pRef = NULL;
	CDataSet *pDataset = NULL;

	CDevice *pDevice = m_pGuideBookDest->GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		pRef = (CGbWzdDatasetRef *)pWzdDatasetMngr->GetNext(pos);
		pDataset = pDevice->SelectDataSet(pRef->m_strID, DSID_ALL_DVM);

		if (pDataset != NULL)
		{
			AddDataset(pDataset);
		}
	}
}

void CGbInsertStxmlFileTool::InitGbtBatchItemGroups(CGbtBatchItemGroups *pGbtBatchItemGroups)
{
	m_pGbtBatchItemGroups->InitByCopy(pGbtBatchItemGroups);
}

void CGbInsertStxmlFileTool::InitGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pGbInsertStxmlFileMngr)
{
	m_pGbInsertStxmlFileMngr->InitByCopy(pGbInsertStxmlFileMngr);
}

void CGbInsertStxmlFileTool::InitCmdItemEditMngr(CGbtCommCmdItemEditMngr *pCmdItemEditMngr)
{
	m_pGbtCommCmdItemEditMngr->InitByCopy(pCmdItemEditMngr);
}

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNCREATE(CGbWzdInsertThread, CWinThread)

CGbWzdInsertThread::CGbWzdInsertThread()
{
	m_pProgressDlg = NULL;
	memset(m_pszMessage, 0, 4096);
	m_nMaxRange = 100;
	m_pParentWnd = NULL;
}


CGbWzdInsertThread::~CGbWzdInsertThread()
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->DestroyWindow();
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	}
}


BOOL CGbWzdInsertThread::InitInstance()
{
	CWnd *pWnd = CWnd::GetDesktopWindow();
	CThreadProgrssDlg *pProgressDlg = new CThreadProgrssDlg(pWnd);//pTool->m_pParentWnd);
	pProgressDlg->CreateThreadDlg(pWnd, _T(""));//pTool->m_pParentWnd, _T(""));
	pProgressDlg->SetMaxRange(m_nMaxRange);

	m_pProgressDlg = pProgressDlg;
	m_pProgressDlg->ShowWindow(SW_HIDE);

	return TRUE;
}

int CGbWzdInsertThread::ExitInstance()
{
	int nReturn = CWinThread::ExitInstance();
	m_pParentWnd = NULL;
	return nReturn;
}


BEGIN_MESSAGE_MAP(CGbWzdInsertThread, CWinThread)
	//{{AFX_MSG_MAP(CGbWzdInsertThread)
	ON_THREAD_MESSAGE(WM_USER + 2355, On2355)
	ON_THREAD_MESSAGE(WM_USER + 2356, On2356)
	ON_THREAD_MESSAGE(WM_USER + 2357, On2357)
	ON_THREAD_MESSAGE(WM_USER + 2358, On2358)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGbWzdInsertThread message handlers

void CGbWzdInsertThread::On2355(WPARAM wParam, LPARAM lParam)
{
	m_nMaxRange = wParam;

	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ShowWindow(SW_SHOW);
		m_pProgressDlg->SetMaxRange(wParam);
		m_pProgressDlg->ResetProcess();
		CRect rc;
		m_pProgressDlg->GetWindowRect(&rc);
		m_pProgressDlg->SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}
}

void CGbWzdInsertThread::On2356(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ResetProcess();
	}
}

void CGbWzdInsertThread::On2357(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		//m_pProgressDlg->StepIt();
		m_pProgressDlg->StepPos(m_nStepIndex);
	}
}

void CGbWzdInsertThread::On2358(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		CString strMsg ;
		strMsg = m_pszMessage;
		m_pProgressDlg->ShowMsg(strMsg);
	}
}
