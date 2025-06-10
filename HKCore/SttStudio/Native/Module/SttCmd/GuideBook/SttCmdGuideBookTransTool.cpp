//SttCmdGuideBookTransTool.cpp  CSttCmdGuideBookTransTool


#include "stdafx.h"
#include "SttCmdGuideBookTransTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL CSttCmdGuideBookTransTool::g_bOnlyItemsTree = FALSE;  //只转换项目分类目录

CSttCmdGuideBookTransTool::CSttCmdGuideBookTransTool()
{
}

CSttCmdGuideBookTransTool::~CSttCmdGuideBookTransTool()
{
}

void CSttCmdGuideBookTransTool::Trans(CGuideBook *pGuideBook, CSttGuideBook *pSttGuideBook)
{
	pSttGuideBook->m_strName = pGuideBook->m_strName;
	pSttGuideBook->m_strID = pGuideBook->m_strID;
	pSttGuideBook->m_strTestMacroFileID = 	pGuideBook->m_strTestMacroFileID;
	pSttGuideBook->m_strTestTypeFile = 	pGuideBook->m_strTestTypeFile;
	pSttGuideBook->m_strDevID = 	pGuideBook->m_strDevID;
	pSttGuideBook->m_strDevBy = 	pGuideBook->m_strDevBy;
	pSttGuideBook->m_strVersion = 	pGuideBook->m_strVersion;
	pSttGuideBook->m_strCommCmdConfigFile = 	pGuideBook->m_strCommCmdConfigFile;
	pSttGuideBook->m_strPpTemplateFile = 	pGuideBook->m_strPpTemplateFile;
	pSttGuideBook->m_strScriptMngrFile = 	pGuideBook->m_strScriptMngrFile;
	pSttGuideBook->m_strPpEngineProgID = 	pGuideBook->m_strPpEngineProgID;
	pSttGuideBook->m_strDvmFile = 	pGuideBook->m_strDvmFile;
	pSttGuideBook->m_strStandNameFile = 	pGuideBook->m_strStandNameFile;
	pSttGuideBook->m_strDeviceModelFile = 	pGuideBook->m_strDeviceModelFile;
	pSttGuideBook->m_nTestControlMode = 	pGuideBook->m_nTestControlMode;
	pSttGuideBook->m_strExpandConfigFile = 	pGuideBook->m_strExpandConfigFile;
	pSttGuideBook->m_strIecfgFile = 	pGuideBook->m_strIecfgFile;
	pSttGuideBook->m_nReadOnly = 	pGuideBook->m_nIsReadOnly;
	pSttGuideBook->m_nIsSaveRptToDB = 	pGuideBook->m_nIsSaveRptToDB;
	pSttGuideBook->m_strAuthoritySN = 	pGuideBook->m_strAuthoritySN;
	pSttGuideBook->m_strAuthorityCop = 	pGuideBook->m_strAuthorityCop;
	pSttGuideBook->m_strScriptType = 	pGuideBook->m_strScriptType;
    TransItemBase(pGuideBook, pSttGuideBook);

	POS pos = pGuideBook->GetHeadPosition();
	CExBaseObject *p = NULL;
	CSttDevice *pNew = NULL;

	while (pos != NULL)
	{
		p = pGuideBook->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DEVICE)
		{
			pNew = new CSttDevice();
			pSttGuideBook->AddNewChild(pNew);
			Trans((CDevice*)p, pNew);
		}
	}
}

void CSttCmdGuideBookTransTool::Trans(CDevice *pDevice, CSttDevice *pSttDevice)
{
	pSttDevice->m_strName = pDevice->m_strName;
	pSttDevice->m_strID = pDevice->m_strID;

	pSttDevice-> m_strFactory = pDevice->m_strFactory;
	pSttDevice->m_strDeviceType = pDevice->m_strDeviceType;
	pSttDevice-> m_nIsTimeSetsUnit_ms = pDevice->m_nIsTimeSetsUnit_ms;
	pSttDevice->m_nDsvTextWithValue = pDevice->m_nDsvTextWithValue;
	pSttDevice->m_nDsvTextWithUtcTime = pDevice->m_nDsvTextWithUtcTime;
	pSttDevice->m_strSrcDeviceModelFile = pDevice->m_strSrcDeviceModelFile;

    TransItemBase(pDevice, pSttDevice);
	Trans((CExBaseList*)pDevice,  (CExBaseList*)pSttDevice);
}

void CSttCmdGuideBookTransTool::Trans(CExBaseList *pGbList, CExBaseList *pSttParent)
{
	POS pos = pGbList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pNew = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pGbList->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_ITEMS:
			pNew = new CSttItems();
			pSttParent->AddNewChild(pNew);
			Trans((CItems*)p, (CSttItems*)pNew);
			break;

		case GBCLASSID_MACROTEST:
			pNew = new CSttMacroTest();
			pSttParent->AddNewChild(pNew);
			Trans((CMacroTest*)p, (CSttMacroTest*)pNew);
			break;

		case GBCLASSID_COMMCMD:
			pNew = new CSttCommCmd();
			pSttParent->AddNewChild(pNew);
			Trans((CCommCmd*)p, (CSttCommCmd*)pNew);
			break;

		case GBCLASSID_SAFETY:
			pNew = new CSttSafety();
			pSttParent->AddNewChild(pNew);
			Trans((CSafety*)p, (CSttSafety*)pNew);
			break;

		case GBCLASSID_SYSPARAEDIT:
			pNew = new CSttSysParaEdit();
			pSttParent->AddNewChild(pNew);
			Trans((CSysParaEdit*)p, (CSttSysParaEdit*)pNew);
			break;
		case GBCLASSID_MACROCHARITEMS:
			pNew = new CSttMacroCharItems();
			pSttParent->AddNewChild(pNew);
			Trans((CMacroCharItems *)p, (CSttMacroCharItems *)pNew);
			break;
		case CHARCLASSID_CCHARACTERISTIC:
			pNew = new CSttCharacteristic();
			pSttParent->AddNewChild(pNew);
			Trans((CCharacteristic *)p, (CSttCharacteristic *)pNew);
			break;
		case GBCLASSID_ITEMRSLTEXPRRUN:
			pNew = new CSttItemRsltExpr();
			pSttParent->AddNewChild(pNew);
			Trans((CItemRsltExprRun *)p, (CSttItemRsltExpr *)pNew);
			break;
		}

		if (p->GetClassID() == GBCLASSID_DEVICE)
		{
			pNew = new CSttDevice();
			pSttParent->AddNewChild(pNew);
			Trans((CDevice*)p, (CSttDevice*)pNew);
		}
	}
}

void CSttCmdGuideBookTransTool::Trans(CItems *pItems, CSttItems *pSttItems)
{
	pSttItems->m_strName = pItems->m_strName;
	pSttItems->m_strID = pItems->m_strID;

	pSttItems->m_strType = pItems->m_strType;
	pSttItems->m_strCharacteristicID = pItems->m_strCharacteristicID;
	pSttItems->m_strstxmlFile = pItems->m_strStxmlFile;
	pSttItems->m_strWzdMapFile = pItems->m_strWzdMapFile;
	pSttItems->m_strActLogic = pItems->m_strActLogic;
	pSttItems->m_nTestTimes = pItems->m_nTestTimes;

	//2023-6-20 shaolei
	pSttItems->m_nRptTitle = pItems->m_nRptTitle;
	pSttItems->m_nTitleLevel = pItems->m_nTitleLevel;

    TransItemBase(pItems, pSttItems);
	Trans((CExBaseList*)pItems,  (CExBaseList*)pSttItems);

	if (g_bOnlyItemsTree)
	{
		return;
	}

	Trans(pItems->GetTestMacroUiParas(), pSttItems->GetSttTestMacroUiParas(TRUE));
	Trans(pItems->GetTestMacroCharParas(), pSttItems->GetSttTestMacroCharParas(TRUE));
}

void CSttCmdGuideBookTransTool::Trans(CMacroTest *pMacroTest, CSttMacroTest *pSttMacroTest)
{
	pSttMacroTest->m_strName = pMacroTest->m_strName;
	pSttMacroTest->m_strID = pMacroTest->m_strID;
    pSttMacroTest->m_strMacroID = pMacroTest->GetTestMacroID();  //2022-3-14  lijunqing

	pSttMacroTest->m_strType = pMacroTest->m_strType;
	pSttMacroTest->m_nRepeatTimes = pMacroTest->m_nRepeatTimes;
	pSttMacroTest->m_strReportMode = pMacroTest->m_strReportMode;
	pSttMacroTest->m_nReportFillUseNoRepeat = pMacroTest->m_nReportFillUseNoRepeat;
    TransItemBase(pMacroTest, pSttMacroTest);
	Trans((CExBaseList*)pMacroTest,  (CExBaseList*)pSttMacroTest);

	if (g_bOnlyItemsTree)
	{
		return;
	}

	Trans(pMacroTest->GetTestMacroUiParas(), pSttMacroTest->GetSttTestMacroUiParas(TRUE));
}

void CSttCmdGuideBookTransTool::TransEx(CMacroTest *pMacroTest, CSttMacroTest *pSttMacroTest)
{
	if (g_bOnlyItemsTree)
	{
		return;
	}

	//Trans(pMacroTest, pSttMacroTest);
	Trans(pMacroTest->GetTestMacroUiParas(), pSttMacroTest->GetSttTestMacroUiParas(TRUE));
	Trans((CExBaseList*)pMacroTest,  (CExBaseList*)pSttMacroTest);
}

void CSttCmdGuideBookTransTool::Trans(CCommCmd *pCommCmd, CSttCommCmd *pSttCommCmd)
{
	pSttCommCmd->m_strName = pCommCmd->m_strName;
	pSttCommCmd->m_strID = pCommCmd->m_strID;

	pSttCommCmd->m_strCommCmdID = pCommCmd->m_strCommCmdID;
	pSttCommCmd->m_strRwOptr = pCommCmd->m_strRwOptr;
	pSttCommCmd->m_nSortSoeByT = pCommCmd->m_nSortSoeByT;
	pSttCommCmd->m_nDsvRunAfterResultScript = pCommCmd->m_nDsvRunAfterResultScript;
	pSttCommCmd->m_nCmdExecModeForMgrpt = pCommCmd->m_nCmdExecModeForMgbrpt;
	pSttCommCmd->m_nFillRptDataset = pCommCmd->m_nFillRptDataset;
    TransItemBase(pCommCmd, pSttCommCmd);

	if (g_bOnlyItemsTree)
	{
		return;
	}


	Trans(pCommCmd->GetRsltExpr(), pSttCommCmd->GetRsltExpr());
	Trans(pCommCmd->GetReportMap(), pSttCommCmd->GetReportMap(TRUE));
	Trans(pCommCmd->GetCmd(), pSttCommCmd->GetCommCmdData(TRUE));
}

void CSttCmdGuideBookTransTool::TransEx(CCommCmd *pCommCmd, CSttCommCmd *pSttCommCmd)
{
	Trans(pCommCmd, pSttCommCmd);

	if (g_bOnlyItemsTree)
	{
		return;
	}

	Trans(pCommCmd->GetReportMap(), pSttCommCmd->GetReportMap(TRUE));
	Trans(pCommCmd->GetCmd(), pSttCommCmd->GetCommCmdData(TRUE));
}

//2022-9-14  lijunqing
void CSttCmdGuideBookTransTool::Trans(CCmd *pCmd, CSttCommCmdData *pSttCommCmdData)
{
	pSttCommCmdData->m_strDatasetPath = pCmd->m_strDatasetPath;
	pSttCommCmdData->m_strDelayBeforeCmd = pCmd->m_strDelayBeforeCmd;
	pSttCommCmdData->m_strDelayAfterCmd = pCmd->m_strDelayAfterCmd;
	pSttCommCmdData->m_strDelayBeforeRetry = pCmd->m_strDelayBeforeRetry;
	pSttCommCmdData->m_nMaxRetrytimes = pCmd->m_nMaxRetrytimes;
	pSttCommCmdData->m_strTimeLong = pCmd->m_strTimeLong;
	pSttCommCmdData->m_strTimeGap = pCmd->m_strTimeGap;
	pSttCommCmdData->m_strCalMode = pCmd->m_strCalMode;
	pSttCommCmdData->m_nRepeatTimes = pCmd->m_nRepeatTimes;
	pSttCommCmdData->m_nReportFillUseNoRepeat = pCmd->m_nReportFillUseNoRepeat;
	pSttCommCmdData->m_nUseCurrSetData = pCmd->m_nUseCurrSetData;
	pSttCommCmdData->m_nUseDeviceEx = pCmd->m_nUseDeviceEx;
	pSttCommCmdData->m_strBeginMode = pCmd->m_strBeginMode;
	pSttCommCmdData->m_nUseConnect = pCmd->m_nUseConnect;
	pSttCommCmdData->m_nZoneIndex = pCmd->m_nZoneIndex;

	pSttCommCmdData->DeleteAll();
	pSttCommCmdData->AppendClone(pCmd);
}

//2022-9-24 shaolei
void CSttCmdGuideBookTransTool::Trans(CReportMap *pRptMap, CSttReportMap *pSttRptMap)
{
	if (pRptMap == NULL)
	{
		return;
	}
}

void CSttCmdGuideBookTransTool::Trans(CSafety *pSafety, CSttSafety *pSttSafety)
{
	pSttSafety->m_strName = pSafety->m_strName;
	pSttSafety->m_strID = pSafety->m_strID;

	pSttSafety->m_strType = pSafety->m_strType;
	pSttSafety->m_strSoundFile = pSafety->m_strSoundFile;
	pSttSafety->m_nManyDeviceTestMode = pSafety->m_nManyDeviceTestMode;
    TransItemBase(pSafety, pSttSafety);
	Trans((CExBaseList*)pSafety,  (CExBaseList*)pSttSafety);

	if (g_bOnlyItemsTree)
	{
		return;
	}

	CShortDatas *pDatas = pSafety->m_pDatas;
	CShortDatas *pDestDatas = pSttSafety->GetDatas();
	pDestDatas->DeleteAll();
	pDestDatas->AppendCloneEx(*pDatas, TRUE);

	CExBaseList* pMsgs = pSafety->GetMsgs();
	MsgLists_to_SttMsgs(pMsgs, pSttSafety);
}

void CSttCmdGuideBookTransTool::Trans(CSysParaEdit *pSysParaEdit, CSttSysParaEdit *pSttSysParaEdit)
{
	pSttSysParaEdit->m_strName = pSysParaEdit->m_strName;
	pSttSysParaEdit->m_strID = pSysParaEdit->m_strID;

	pSttSysParaEdit->m_strDatasetPath = pSysParaEdit->m_strDatasetPath;
    TransItemBase(pSysParaEdit, pSttSysParaEdit);
	Trans((CExBaseList*)pSysParaEdit,  (CExBaseList*)pSttSysParaEdit);
}

void CSttCmdGuideBookTransTool::TransItemBase(CGbItemBase *pItemBase, CSttItemBase *pSttItemBase)
{    
    pSttItemBase->m_nTkID = pItemBase->m_nTkID;
    pSttItemBase->m_nShow = pItemBase->m_nShow;
    pSttItemBase->m_nEnable = pItemBase->m_nEnable;
    pSttItemBase->m_nExecType = pItemBase->m_nExecType;
    pSttItemBase->m_nBatchItem = pItemBase->m_nBatchItem ;
    pSttItemBase->m_nSelect = pItemBase->m_nSelect;
    pSttItemBase->m_nState = pItemBase->GetState();

	if (g_bOnlyItemsTree)
	{
		return;
	}

	CReports *pReports = pItemBase->GetReports();

	if (pReports->GetCount() == 0)
	{//如果没有报告数据，则不处理
		return;
	}

	CSttReports *pNew = new CSttReports();
	pSttItemBase->AddNewChild(pNew);

	Trans(pReports, pNew);
}

void CSttCmdGuideBookTransTool::Trans(CReports *pReports, CSttReports *pSttReports)
{
	pSttReports->m_strName = pReports->m_strName;
	pSttReports->m_strID = pReports->m_strID;

	POS pos = pReports->GetHeadPosition();
	CReport *pReport = NULL;
	CSttReport *pSttReport = NULL;

	while (pos != NULL)
	{
		pReport = (CReport*)pReports->GetNext(pos);
		pSttReport = new CSttReport();
		pSttReports->AddNewChild(pSttReport);
		Trans(pReport, pSttReport);
	}
}

void CSttCmdGuideBookTransTool::Trans(CReport *pReport, CSttReport *pSttReport)
{
	pSttReport->m_strName = pReport->m_strName;
	pSttReport->m_strID = pReport->m_strID;

	pSttReport->m_strBeginTime = pReport->m_strBeginTime;
	pSttReport->m_strEndTime = pReport->m_strEndTime;

	pSttReport->InitValues(pReport->m_pValues);
	pSttReport->InitRptDvmDataset(pReport->m_pRptDvmDataset); 

	//电气量项目，报告数据根据TestMacro中的参数，重新赋值data-type和name
	CGbItemBase *pItem = (CGbItemBase *)(pReport->GetParent())->GetParent();
	stt_AtsInitSttReport_DataType(pSttReport, pItem, TRUE);
}

void CSttCmdGuideBookTransTool::Trans(CTestMacroCharParas *pCharParas, CSttTestMacroCharParas *pSttCharParas)
{
	if (pCharParas == NULL)
	{
		CSttItems *pSttItems = (CSttItems *)pSttCharParas->GetParent();
		pSttItems->Delete(pSttCharParas);
		return;
	}

	pSttCharParas->m_strName = pCharParas->m_strName;
	pSttCharParas->m_strID = pCharParas->m_strID;

	pSttCharParas->m_strParaText = pCharParas->m_strParaText;
}

void CSttCmdGuideBookTransTool::Trans(CTestMacroUiParas *pUiParas, CSttTestMacroUiParas *pSttUiParas)
{
	if (pUiParas == NULL)
	{
		CSttItems *pSttItems = (CSttItems *)pSttUiParas->GetParent();
		pSttItems->Delete(pSttUiParas);
		return;
	}

	pSttUiParas->m_strName = pUiParas->m_strName;
	pSttUiParas->m_strID = pUiParas->m_strID;

	pSttUiParas->m_strParaText = pUiParas->m_strParaText;
}

void CSttCmdGuideBookTransTool::Trans(CMacroCharItems *pMacroCharItems, CSttMacroCharItems *pSttMacroCharItems)
{
	pSttMacroCharItems->m_strName = pMacroCharItems->m_strName;
	pSttMacroCharItems->m_strID = pMacroCharItems->m_strID;

	TransItemBase(pMacroCharItems, pSttMacroCharItems);
	Trans((CExBaseList*)pMacroCharItems,  (CExBaseList*)pSttMacroCharItems);
}

void CSttCmdGuideBookTransTool::Trans(CCharacteristic *pCharacteristic, CSttCharacteristic *pSttCharacteristic)
{
	pSttCharacteristic->m_strName = pCharacteristic->m_strName;
	pSttCharacteristic->m_strID = pCharacteristic->m_strID;

	pSttCharacteristic->m_nAutoClose = pCharacteristic->m_nAutoClose;
	pSttCharacteristic->m_strAxis = pCharacteristic->m_strAxis;
	pSttCharacteristic->m_strXMin = pCharacteristic->m_strXMin;
	pSttCharacteristic->m_strXMax = pCharacteristic->m_strXMax;
	pSttCharacteristic->m_strYMin = pCharacteristic->m_strYMin;
	pSttCharacteristic->m_strYMax = pCharacteristic->m_strYMax;
	pSttCharacteristic->m_strTestLineMode = pCharacteristic->m_strTestLineMode;
	pSttCharacteristic->m_strIndex = pCharacteristic->m_strIndex;
}

//2022-9-14  lijunqing
void CSttCmdGuideBookTransTool::Trans(CSttCommCmd *pSrc, CCommCmd *pDest)
{
	pDest->m_strName = pSrc->m_strName;
	pDest->m_strID = pSrc->m_strID;

	pDest->m_strCommCmdID = pSrc->m_strCommCmdID;
	pDest->m_strRwOptr = pSrc->m_strRwOptr;
	pDest->m_nSortSoeByT = pSrc->m_nSortSoeByT;
	pDest->m_nDsvRunAfterResultScript = pSrc->m_nDsvRunAfterResultScript;
	pDest->m_nCmdExecModeForMgbrpt = pSrc->m_nCmdExecModeForMgrpt;
	pDest->m_nFillRptDataset = pSrc->m_nFillRptDataset;

	if (g_bOnlyItemsTree)
	{
		return;
	}

	Trans(pSrc->GetCommCmdData(TRUE), pDest->GetCmd());
}

void CSttCmdGuideBookTransTool::Trans(CSttCommCmdData *pSrc, CCmd *pDest)
{
	if (pSrc == NULL)
	{
		return;
	}

	pDest->m_strDatasetPath = pSrc->m_strDatasetPath;
	pDest->m_strDelayBeforeCmd = pSrc->m_strDelayBeforeCmd;
	pDest->m_strDelayAfterCmd = pSrc->m_strDelayAfterCmd;
	pDest->m_strDelayBeforeRetry = pSrc->m_strDelayBeforeRetry;
	pDest->m_nMaxRetrytimes = pSrc->m_nMaxRetrytimes;
	pDest->m_strTimeLong = pSrc->m_strTimeLong;
	pDest->m_strTimeGap = pSrc->m_strTimeGap;
	pDest->m_strCalMode = pSrc->m_strCalMode;
	pDest->m_nRepeatTimes = pSrc->m_nRepeatTimes;
	pDest->m_nReportFillUseNoRepeat = pSrc->m_nReportFillUseNoRepeat;
	pDest->m_nUseCurrSetData = pSrc->m_nUseCurrSetData;
	pDest->m_nUseDeviceEx = pSrc->m_nUseDeviceEx;
	pDest->m_strBeginMode = pSrc->m_strBeginMode;
	pDest->m_nUseConnect = pSrc->m_nUseConnect;
	pDest->m_nZoneIndex = pSrc->m_nZoneIndex;

	pDest->DeleteAll();
	pDest->AppendClone(pSrc);
}

void CSttCmdGuideBookTransTool::Trans(CItemRsltExprRun*pRsltExpr, CSttItemRsltExpr*pSttRsltExpr)
{
	pSttRsltExpr->m_strLogic = pRsltExpr->m_strLogic;
	pSttRsltExpr->m_nCntRslt = pRsltExpr->m_nCntRslt;
	pSttRsltExpr->m_strUse = pRsltExpr->m_strUse;
	pSttRsltExpr->AppendClone(pRsltExpr);
}

void CSttCmdGuideBookTransTool::ReverseTrans(CReports *pReports, CSttReports *pSttReports)
{
	pReports->m_strName = pSttReports->m_strName;
	pReports->m_strID = pSttReports->m_strID;

	POS pos = pSttReports->GetHeadPosition();
	CReport *pReport = NULL;
	CSttReport *pSttReport = NULL;

	while (pos != NULL)
	{
		pSttReport = (CSttReport*)pSttReports->GetNext(pos);
		pReport = new CReport();
		pReports->AddNewChild(pReport);
		pReport->DeleteRptValues();  //删除CReport构造时自动添加的报告数据，例如：结果判断
		ReverseTrans(pReport, pSttReport);
	}
}

void CSttCmdGuideBookTransTool::ReverseTrans(CReport *pReport, CSttReport *pSttReport)
{
	pReport->m_strName = pSttReport->m_strName;
	pReport->m_strID = pSttReport->m_strID;

	pReport->m_strBeginTime = pSttReport->m_strBeginTime;
	pReport->m_strEndTime = pSttReport->m_strEndTime;

	pReport->InitValues(pSttReport->m_pValues);
	pReport->InitRptDvmDataset(pSttReport->m_pRptDvmDataset); 
}


//////////////////////////////////////////////////////////////////////////////////
//2022-06-14 shaolei
//安全措施的Msg列表，转换成CSttMsgs链表
void MsgLists_to_SttMsgs(CExBaseList *pMsgs, CExBaseList *pSttMsgs)
{
	POS pos = pMsgs->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pMsgs->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_MSG)
		{
			continue;
		}

		CMsg *pMsg = (CMsg *)pObj;
		CSttMsg *pSttMsg = new CSttMsg;
		pSttMsg->m_strMsg = pMsg->m_strMsg;
		pSttMsg->m_nType = pMsg->m_nUseCData;
		pSttMsgs->AddNewChild(pSttMsg);
	}
}

//shaolei  2023-1-6  处理电气量项目报告数据的数据类型和名称
void stt_AtsInitSttReport_DataType(CSttReport *pSttReport, CGbItemBase *pItem, BOOL bInitName)
{
	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		return;
	}

	CMacroTest *pMacroTest = (CMacroTest *)pItem;
	CGuideBook *pGuideBook = (CGuideBook *)pMacroTest->GetAncestor(GBCLASSID_GUIDEBOOK);
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CString strMacroID = pMacroTestPara->GetMacroID();
	CTestMacro *pTestMacro = (CTestMacro *)pGuideBook->m_pTestMacros->FindByID(strMacroID);

	if (pTestMacro == NULL)
	{
		return;
	}

    long nIndex = 0;
	POS pos = pSttReport->m_pValues->GetHeadPosition();

	while (pos != NULL)
	{
        CDvmValue *pValue = (CDvmValue *)pSttReport->m_pValues->GetNext(pos);

		if (pValue->m_strID == g_strTestResultJudgeKey)
		{
			pValue->m_strDataType = _T("long");

			if (bInitName)
			{
				pValue->m_strName = g_strTestResultJudgeNameKey/*_T("结果判断")*/;
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultDescriptKey)
		{
			pValue->m_strDataType = _T("string");

			if (bInitName)
			{
				pValue->m_strName = g_strTestResultDescriptNameKey/*_T("结果描述")*/;
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultTimeKey)
		{
			pValue->m_strDataType = _T("string");

			if (bInitName)
			{
				pValue->m_strName = g_strTestResultTimeNameKey/*_T("报告时间")*/;
			}

			continue;
		}
/*
		if (pValue->m_strID == g_strTestResultAbsRsltCal1Key)
		{
			pValue->m_strDataType = _T("float");

			if (bInitName)
			{
				pValue->m_strName = _T("绝对误差计算结果1");
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultAbsRsltCal2Key)
		{
			pValue->m_strDataType = _T("float");

			if (bInitName)
			{
				pValue->m_strName = _T("绝对误差计算结果2");
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultRelRsltCal1Key)
		{
			pValue->m_strDataType = _T("float");

			if (bInitName)
			{
				pValue->m_strName = _T("相对误差计算结果1");
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultRelRsltCal2Key)
		{
			pValue->m_strDataType = _T("float");

			if (bInitName)
			{
				pValue->m_strName = _T("相对误差计算结果2");
			}

			continue;
		}
*/
        CShortData *pData = pTestMacro->FindDataByID(pValue->m_strID);

		if (pData != NULL)
		{
			if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
			{
				continue;
			}

			pValue->m_strDataType = pData->m_strDataTypeID;

			if (bInitName)
			{
				if (pData->m_strName.IsEmpty())
				{
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestMacro.xml中，参数【%s】未配置name属性！"), pData->m_strID.GetString());
				}
				else
				{
					pValue->m_strName = pTestMacro->GetParaNamePath(pData);//pData->m_strName;
				}
			}
		}
		else
		{
			//找不到，考虑从结果判断表达式中查找。
			CXExprNode *pNode = (CXExprNode *)pItem->GetRsltExpr();

			//结果判断里面，只有名称
			if (bInitName && pNode != NULL)
			{
				stt_AtsInitSttReport_Name(pValue, pNode);
			}
		}
	}
}

void stt_AtsInitSttReport_Name(CDvmValue *pValue, CXExprNode *pNode)
{
	if (pNode == NULL || pValue == NULL)
	{
		return;
	}

	CString strName;
	pNode->GetValueName(pValue->m_strID, strName);

	if ( !strName.IsEmpty())
	{
		pValue->m_strName = strName;
	}
}
