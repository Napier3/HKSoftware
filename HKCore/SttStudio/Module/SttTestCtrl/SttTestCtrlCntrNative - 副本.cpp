#include "SttTestCtrlCntrNative.h"
#include "../UI/Interface/SttHtmlViewApi.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "SttTestAppBase.h"
#include "../SttTestSysGlobalPara.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"

#include "../../../Module/SmartCap/SmartCapCtrl.h"
#include "../SttCmd/GuideBook/SttItemStateObject.h"
#include "../UI/SttTestCntrFrameBase.h"
#include "../SttCmd/GuideBook/SttContents.h"
#include "../ReplayTest/BigComtradeTransPlay.h"
//2022-10-5  lijunqing
#include "../Engine/PpMeas/PpSttIotMeasServer.h"
#include "../../../Module/SmartCap/X61850CapBase.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"

//2022-10-7  lijunqing
#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineServer.h"
#include "../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../UI/SttTestCntrCmdDefine.h"
extern CSttXHtmlRptGenFactoryBase *g_theHtmlRptGenFactory;


CSttTestCtrlCntrNative::CSttTestCtrlCntrNative()
{
	m_pSttGuideBook = new CSttGuideBook();
	m_oSttAtsClient.m_pAtsEventRcv = this;
}

CSttTestCtrlCntrNative::~CSttTestCtrlCntrNative()
{
	m_oSttAtsClient.FreeXClientEngine();
	//g_theBigComtradeTransPlay->FreeClientEngine();

	if (m_pSttGuideBook != NULL)
	{
		delete m_pSttGuideBook;
		m_pSttGuideBook = NULL;
	}
}

void CSttTestCtrlCntrNative::SttOpen(const CString &strTestAppCfgFile)
{
	m_oSttAtsClient.SttOpen(strTestAppCfgFile);
}


long CSttTestCtrlCntrNative::OnUpdateSyncTime(CDataGroup *pRtSyncTime)
{	
	m_pTestCtrlCntrMsg->OnUpdateSyncTime(pRtSyncTime);
	return 0;
}

long CSttTestCtrlCntrNative::OnUpdateException()
{
	m_pTestCtrlCntrMsg->OnUpdateException();
	return 0;
}

long CSttTestCtrlCntrNative::OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex,
												long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	CSttItemBase *pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemID);

	if (pItem == NULL)
	{
		return 0;
	}

	pItem->m_nState = nState;

	//���Ͳ���״̬�ı��¼������²���ģ�����οؼ�
	CSttItemStateObject* pObj = new CSttItemStateObject;
	pObj->SetItemState(pItem, nDeviceIndex, nReportIndex, nItemIndex, strItemID, nState, pParas);
	m_pTestCtrlCntrMsg->OnItemStateChanged(pObj);

	return 1;
}

long CSttTestCtrlCntrNative::OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	m_pTestCtrlCntrMsg->OnTestFinished();
	return 0;
}

long CSttTestCtrlCntrNative::OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	m_pTestCtrlCntrMsg->OnTestStarted();
	return 0;
}

long CSttTestCtrlCntrNative::OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	m_pTestCtrlCntrMsg->OnTestStoped();
	return 0;
}

long CSttTestCtrlCntrNative::OnTestCreated(const CString &strTestID, CSttParas *pParas)
{
	m_pTestCtrlCntrMsg->OnTestCreated();
	return 0;
}

long CSttTestCtrlCntrNative::OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas)
{
	return 0;
}

long CSttTestCtrlCntrNative::OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs) 
{
	return 0;
}

long CSttTestCtrlCntrNative::OnExportRptEvent(CSttParas *pParas)
{
	return 0;
}

void CSttTestCtrlCntrNative::OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex,
									  long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	CSttParas *pSttParas = (CSttParas*)pParas;
	CSttReports *pSttReports = pSttParas->GetSttReports(FALSE);

	if (pSttReports == NULL)
	{
		return;
	}

	CSttReport *pSttReport = (CSttReport*)pSttReports->GetTail();

	if (pSttReport == NULL)
	{
		return;
	}

	CString strItemID2 = _T("");
	CDvmValue *pValue = pSttReport->FindValueByID(_T("LoopIndex"));

	if (pValue != NULL)
	{
		long nLoopIndex = CString_To_long(pValue->m_strValue);
		strItemID2 = g_theTestCntrFrame->GetMacroEditView()->ProcessItemID (strItemID,nLoopIndex);
	}
	//CSttItemBase *pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemID);

	//20230217 zhangyq ���ݵ�ǰ�ظ��Ĵ�������̬����ID
	
	CSttItemBase *pItem = NULL;

	if (strItemID2.IsEmpty())
	{
		pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemID);
	} 
	else
	{
		pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemID2);
	}

	if (pItem == NULL)
	{
		return;
	}
	
	if ((pItem->m_strID == STT_MACRO_ID_ChMapsConfig)||(pItem->m_strID == STT_MACRO_ID_Iec61850Config)//20230302 zhouhj Ϊ�������Ч��,���⼸�಻������
		||(pItem->m_strID == STT_MACRO_ID_SystemConfig))
	{
		return;
	}

	CSttReports *pItemReports = pItem->SetReports(pSttReports);
	pSttReport = (CSttReport*)pItemReports->GetTail();
	//2022-10-3  LIJUNQING  ����rpt-map-datas
	CSttRptMapDatas *pRptMapDatas = (CSttRptMapDatas*)pSttParas->FindByClassID(STTCMDCLASSID_CSTTRPTMAPDATAS);

	if ((pRptMapDatas != NULL)&&(pSttReport != NULL))
	{
		if (pRptMapDatas->GetCount()>0)
		{
			pSttReport->AddNewChild((CExBaseObject*)pRptMapDatas->Clone());
		}
	}
	
	//������д�������Ϣ
	m_pTestCtrlCntrMsg->OnReport(pItem);
}

void CSttTestCtrlCntrNative::OnReport_ReadDevice(CDataGroup *pDeviceGroup)
{
	if (pDeviceGroup == NULL)
	{
		return;
	}

	m_pTestCtrlCntrMsg->OnReport_ReadDevice(pDeviceGroup);

}

/*
<sys-state name="" id="GenerateTemplate" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="3" unit=""/>
		<guidebook name="" id="" ......>
			......................
		</guidebook >
	</paras>
</sys-state>
<sys-state name="" id="GenerateItems" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="3" unit=""/>
		<data name="" id="ParentItemsPath" data-type="string" value=""/>
		<items name="" id="" tkid="65535" select="1">
			......................
		</items>
	</paras>
</sys-state>
*/
void CSttTestCtrlCntrNative::On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas)
{
	if (strAtsCmd == STT_CMD_TYPE_ATS_GenerateTemplate)
	{
		CSttGuideBook *pSttGuideBook = pParas->GetGuideBook();

		if (pSttGuideBook != NULL)
		{
//			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("CSttTestCtrlCntrNative::On_Ats_Generate++++++++."));
			CAutoSimpleLock oLock(g_theTestCntrFrame->m_oCriticSection_ItemStateList);
			g_theTestCntrFrame->ClearItemStateList();
			m_pSttGuideBook->ClearGuideBook();
			m_pSttGuideBook->AppendEx(*pSttGuideBook);
			pSttGuideBook->RemoveAll();
//			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("CSttTestCtrlCntrNative::On_Ats_Generate------."));
			m_pTestCtrlCntrMsg->OnAtsGenerate();
		}
	}
	else if (strAtsCmd == STT_CMD_TYPE_ATS_GenerateItems)
	{
		CString strParentItemPath;
		pParas->GetDataValue(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
		CSttItems *pItems = pParas->GetItems();

		if (pItems != NULL)
		{
			BOOL bUpdateParent = FALSE;
			m_pSttGuideBook->InsertItems(strParentItemPath, pItems, bUpdateParent);
			pParas->Remove(pItems);

			m_pTestCtrlCntrMsg->OnAtsGenerateItems(pItems, bUpdateParent);
// 			if (bUpdateParent)
// 			{
// 				//�������ʱ����Ҫ�Ӹ��ڵ�ˢ�����οؼ���ʾ
// 				CExBaseObject *pParent = (CExBaseObject *)pItems->GetParent();
// 				m_pTestCtrlCntrMsg->OnAtsGenerateItems(pParent);
// 			}
// 			else
// 			{
// 				m_pTestCtrlCntrMsg->OnAtsGenerateItems(pItems);
// 			}
		}

		CDataGroup *pCmdGrp = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_CommCmd);

		if (pCmdGrp != NULL)
		{
			m_pTestCtrlCntrMsg->OnAtsGenerateItems_CmdWzd(pCmdGrp);
		}
	}
}

void CSttTestCtrlCntrNative::UpdateReportValuesByMacroTestDataType(CSttItems *pItems)
{
	if (pItems == NULL)
	{
		return;
	}

	CExBaseObject *pCurrObj = NULL;
	CSttMacroTest *pSttMacroTest = NULL;
	CSttReports *pSttReports = NULL;
	CSttReport *pReport = NULL;
	POS pos = pItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pItems->GetNext(pos);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			UpdateReportValuesByMacroTestDataType((CSttItems*)pCurrObj);
		}
		else if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pSttMacroTest = (CSttMacroTest*)pCurrObj;
			pSttReports = pSttMacroTest->GetSttReports();

			if (pSttReports != NULL)
			{
				pReport = (CSttReport*)pSttReports->GetTail();
				UpdateReportValuesByMacroTestDataType(pReport,pSttMacroTest->m_strMacroID);
			}
			
		}
	}
}

void CSttTestCtrlCntrNative::UpdateReportValuesByMacroTestDataType(CSttReport *pReport,const CString &strMacroID)
{
	if ((pReport == NULL)||(g_theHtmlRptGenFactory == NULL))
	{
		return;
	}	

	CDvmValues *pValues = (CDvmValues*)pReport->FindByClassID(DTMCLASSID_CDVMVALUES);

	if (pValues == NULL)
	{
		return;
	}

	//�ֶ���״̬���в���ʱ,���⴦��,�����ǰ��ѡֱ�����,�򽫶�Ӧ����λ��Ƶ������Ϊ"--"
	if (strMacroID == STT_ORG_MACRO_ManualTest)
	{
		ModifyReport_ManualTest(pValues);
	}
	else if (strMacroID == STT_ORG_MACRO_StateTest)
	{
		ModifyReport_StateTest(pValues);
	}
	else if (strMacroID == STT_ORG_MACRO_HarmTest)
	{
		ModifyReport_HarmTest(pValues);
	}

	if (g_theHtmlRptGenFactory->m_pDataTypes == NULL)
	{
		return;
	}

	CExBaseObject *pCurrObj = NULL;

	CDvmValue *pValue = NULL;
	CDataType *pDataType = NULL;
	CDataTypeValue *pFindDataTypeValue = NULL;
	POS pos_value = pValues->GetHeadPosition();

	while(pos_value)
	{
		pValue = (CDvmValue*)pValues->GetNext(pos_value);
		pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(pValue->m_strDataType);

		if (pDataType == NULL)
		{
			continue;
		}

		pFindDataTypeValue = pDataType->FindByIndex(pValue->m_strValue);

		if (pFindDataTypeValue != NULL)
		{
			pValue->m_strValue = pFindDataTypeValue->m_strName;
		}
	}
}

void CSttTestCtrlCntrNative::ModifyReport_ManualTest(CDvmValues *pValues)
{
	CDvmValue *pDvmValue = (CDvmValue*)pValues->FindByID(_T("bDC"));
	long nDC = 0;

	if (pDvmValue != NULL)
	{
		nDC = CString_To_long(pDvmValue->m_strValue);
	}

	long nLenth = 0;
	CString strRightText2,strRightText3;
	CSttChMap *pSttChMap = NULL;
	POS pos = pValues->GetHeadPosition();

	while(pos)
	{
		pDvmValue = (CDvmValue *)pValues->GetNext(pos);
		nLenth = pDvmValue->m_strID.GetLength();

		if ((nLenth>=2)&&(nLenth<=4))//��ѹ����ͨ��ID���ȱض���2~4֮��
		{
			pSttChMap = (CSttChMap*)g_oSttTestResourceMngr.m_oChMaps.FindByID(pDvmValue->m_strID);

			if (pSttChMap != NULL)
			{
				pDvmValue->m_strName = pSttChMap->m_strName;//�������Դͨ������,���µ���Ӧ��name������,�Ա���±���
			}
		}

		if ((nDC > 0)&&((nLenth>=3)||(nLenth<=6)))//ͨ����λ��Ƶ�ʵ�ID���ȱض���3~6֮��
		{
			strRightText2 = pDvmValue->m_strID.Mid(nLenth-2);
			strRightText3 = pDvmValue->m_strID.Mid(nLenth-3);

			if ((strRightText2 == _T("Ph"))||(strRightText3 == _T("Fre")))
			{
				pDvmValue->m_strValue = _T("--");
			}
		}
	}
}

void CSttTestCtrlCntrNative::ModifyReport_StateTest(CDvmValues *pValues)
{
	CDvmValue *pDvmValue = NULL;
	long nStringIndex = 0;
	CString strTmp1,strTmp2;
	CSttChMap *pSttChMap = NULL;
	POS pos = pValues->GetHeadPosition();

	while(pos)
	{
		pDvmValue = (CDvmValue *)pValues->GetNext(pos);
		nStringIndex = pDvmValue->m_strID.Find(_T("$mag"));

		if ((nStringIndex>0)&&((nStringIndex + 4) == pDvmValue->m_strID.GetLength()))
		{
			strTmp1 = pDvmValue->m_strID.Left(nStringIndex);
			nStringIndex = strTmp1.ReverseFind('$');

			if (nStringIndex>0)
			{
				strTmp2 = strTmp1.Mid(nStringIndex+1);

				pSttChMap = (CSttChMap*)g_oSttTestResourceMngr.m_oChMaps.FindByID(strTmp2);

				if (pSttChMap != NULL)
				{
					pDvmValue->m_strName = pSttChMap->m_strName;//�������Դͨ������,���µ���Ӧ��name������,�Ա���±���
				}
			}
		}
	}

	//��ѡֱ�����ʱ,�޸Ķ�Ӧ����λ��Ƶ��value
	pDvmValue = (CDvmValue*)pValues->FindByID(_T("StateCount"));

	if (pDvmValue != NULL)
	{
		long nStateCount = CString_To_long(pDvmValue->m_strValue);
		CString strDC_ID,strStateID,strAngID,strFreqID;
		CDvmValue *pDC_Value = NULL;
		long nDC = 0;

		//����״̬������,�ҵ�ÿ��״̬��ֱ�����
		for (int nStateIndex = 0;nStateIndex<nStateCount;nStateIndex++)
		{
			strStateID.Format("state%ld$",nStateIndex);
			strDC_ID = strStateID + _T("bDC");
			pDC_Value = (CDvmValue*)pValues->FindByID(strDC_ID);

			if (pDC_Value != NULL)//�ҵ�ֱ�����
			{
				nDC = CString_To_long(pDC_Value->m_strValue);

				if (nDC > 0)///�����ֱ��,����д���
				{
					pos = pValues->GetHeadPosition();

					while(pos)
					{
						pDvmValue = (CDvmValue *)pValues->GetNext(pos);

						if (pDvmValue->m_strID.Find(strStateID) == 0)//�ȶ�״̬���Ƿ�һ��
						{
							strAngID = pDvmValue->m_strID.Mid(pDvmValue->m_strID.GetLength() - 4);
							strFreqID = pDvmValue->m_strID.Mid(pDvmValue->m_strID.GetLength() - 5);

							if ((strAngID == _T("$ang"))||(strFreqID == _T("$freq")))
							{
								pDvmValue->m_strValue = _T("--");
							}
						}
					}
				}
			}
		}
	}
}

void CSttTestCtrlCntrNative::ModifyReport_HarmTest(CDvmValues *pValues)
{
	CDvmValue *pDvmValue = NULL;
	long nStringIndex = 0;
	CString strTmp;
	CSttChMap *pSttChMap = NULL;
	POS pos = pValues->GetHeadPosition();

	while(pos)
	{
		pDvmValue = (CDvmValue *)pValues->GetNext(pos);

// 		if (pDvmValue->m_strID.Find(_T("$harm"))>0)//20230309 zhouhj г���������ݲ����¸���г������ֵ,ɾ��������,����߱������Ч��
// 		{
// 			pValues->Delete(pDvmValue);
// 			continue;
// 		}

		nStringIndex = pDvmValue->m_strID.Find(_T("$U0Amp"));

		if ((nStringIndex>0)&&((nStringIndex + 6) == pDvmValue->m_strID.GetLength()))
		{
			strTmp = pDvmValue->m_strID.Left(nStringIndex);

			pSttChMap = (CSttChMap*)g_oSttTestResourceMngr.m_oChMaps.FindByID(strTmp);

			if (pSttChMap != NULL)
			{
				pDvmValue->m_strName = pSttChMap->m_strName;//�������Դͨ������,���µ���Ӧ��name������,�Ա���±���
			}
		}
	}
}

CExBaseObject* CSttTestCtrlCntrNative::FindRootItemsByID(const CString &strObjID)
{
	CSttDevice *pSttDevice = m_pSttGuideBook->GetDevice();

	if (pSttDevice== NULL)
	{
		return NULL;
	}

	CExBaseObject *pItems = pSttDevice->FindByID(strObjID);
	return pItems;
}

long CSttTestCtrlCntrNative::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)
{
	CSttItems *pItems = (CSttItems*)FindRootItemsByID(strMacroItemsID);

	if (pItems == NULL)
	{
		return 0;
	}
	
 	CSttItemsEmpty oItems;
	CSttItems *pNewItems = (CSttItems*)pItems->Clone();//20230109 zhouhj ��Ϊ��¡��ʽ,��Ҫ����Reports�е��������͸�������ֵ
 	oItems.AddTail(pNewItems);
	UpdateReportValuesByMacroTestDataType(pNewItems);

	CSttCmdDefineXmlRWKeys::stt_Inc_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::SetOnlyGetItem(TRUE);
//	long nLen = pItems->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, ppszItemsXml, 0, _JSON_TYPE_);
	long nLen = oItems.GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, ppszItemsXml, 0, _JSON_TYPE_);
	CSttCmdDefineXmlRWKeys::SetOnlyGetItem(FALSE);
	CSttCmdDefineXmlRWKeys::stt_Dec_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

//	oItems.RemoveAll();

	return nLen;
}

/*
<group name="IEC_CB" id="IEC_CB" data-type="IEC_CB" value="IEC_CB">
	<data name="" id="Type" data-type="string" value="SMV92"/><!--SMV92,SMV91,FT3,GOOSE -->
	<data name="" id="Port" data-type="string" value="0"/>
	<data name="" id="CRC" data-type="string" value="0xAABB"/>
	<data name="" id="APPID" data-type="hex" value="0x4001"/>
	<data name="" id="PkgDetect"  data-type="string" value="aa124010d89c"/>
</group>
*/
void CSttTestCtrlCntrNative::On_IecDetect(CDataGroup *pIecCb)
{
	CCapDeviceBase *pNew = g_theSmartCapCtrl->m_pXSttCap_61850->m_oCapDeviceAll.AddCapDevice(pIecCb);
	
	if (g_theCapDeviceMngrMsgRcvWnd != NULL)
	{
		if (pNew != NULL)//���ز�Ϊ��,����ӳɹ�,����ӿ��ƿ�  zhouhj20230106 
		{
			g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_ADDCAPDEVICE, (WPARAM)pNew, (LPARAM)pNew);
		} 
		else//����Ϊ��,����¿��ƿ�,��ֹ��ںŸ��µ��������
		{
			pNew = g_theSmartCapCtrl->m_pXSttCap_61850->m_oCapDeviceAll.FindCapDevice(pIecCb);

			if (pNew != NULL)
			{
				g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_UPDATECAPDEVICE, (WPARAM)pNew, (LPARAM)pNew);
			}
		}
	}
}

//2022-04-18  shaolei
void CSttTestCtrlCntrNative::On_Ats_SaveTest(CSttSysState *pSysState)
{
	CString strMsg;
	long nCmdExecState = pSysState->Get_ExecStatus();

	switch (nCmdExecState)
	{
	case STT_CMD_ExecStatus_FAILURE:
		strMsg = "ʧ��";
		break;
	case STT_CMD_ExecStatus_TIMEOUT:
		strMsg = "��ʱ";
		break;
	case STT_CMD_ExecStatus_SUCCESS:
		strMsg = "�ɹ�";
		break;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("���汣��%s."), strMsg.GetString());
}

void CSttTestCtrlCntrNative::On_Ats_SaveTemplate(CSttSysState *pSysState)
{
	CString strMsg;
	long nCmdExecState = pSysState->Get_ExecStatus();

	switch (nCmdExecState)
	{
	case STT_CMD_ExecStatus_FAILURE:
		strMsg = "ʧ��";
		break;
	case STT_CMD_ExecStatus_TIMEOUT:
		strMsg = "��ʱ";
		break;
	case STT_CMD_ExecStatus_SUCCESS:
		strMsg = "�ɹ�";
		break;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("ģ�屣��%s."), strMsg.GetString());
}


//2022-9-13  lijunqing
void CSttTestCtrlCntrNative::On_Ats_QueryItem(CSttSysState *pSysState)
{
	CSttParas *pParas = pSysState->GetSttParas();
	CExBaseObject *pFind = pParas->FindByID(STT_CMD_PARA_ItemParas);
	m_pTestCtrlCntrMsg->OnAtsQueryItem(pFind);
}


/*
<group id="Rtdata" data-type="Rtdata">
	<data id="Time" value="1034094747" />
	<data id="RealTime" value="0" />
	<group id="I1" data-type="channel">
		<data id="mag" value="1" />
		<data id="ang" value="0" />
		<data id="freq" value="50" />
	</group>
	............................
	<group id="U1" data-type="channel">
		<data id="mag" value="57.7350006" />
		<data id="ang" value="0" />
		<data id="freq" value="50" />
	</group>
</group>
*/
/*
<dataset name="���Ȳ�������" id="dsRcdStep6U6I" data-type="" write-mode="0" index="0">
	<data name="Ua1" id="Ua1" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="Ua1Ph" id="Ua1Ph" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	......................
	<data name="Uc2" id="Uc2" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="Uc2Ph" id="Uc2Ph" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="Ia1" id="Ia1" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="Ia1Ph" id="Ia1Ph" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	......................
	<data name="Ic2" id="Ic2" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="Ic2Ph" id="Ic2Ph" data-type="long" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</dataset>
*/
BOOL RtData_To_RcdStep6U6I_Ch(CDataGroup *pRtData, CDvmDataset *pDsRcdStep6U6I
							  , const CString &strRtChID, const CString &strDsChID)
{
	CDataGroup *pRtCh = (CDataGroup*)pRtData->FindByID(strRtChID);
	
	if (pRtCh == NULL)
	{
		return FALSE;
	}

	CDvmData *pRtMag = (CDvmData*)pRtCh->FindByID(_T("mag"));
	CDvmData *pRtAng = (CDvmData*)pRtCh->FindByID(_T("ang"));
	CDvmData *pDsChMag = (CDvmData*)pDsRcdStep6U6I->FindByID(strDsChID);
	CDvmData *pDsChPh = (CDvmData*)pDsRcdStep6U6I->FindByID(strDsChID + _T("Ph"));

	if (pRtMag != NULL && pDsChMag != NULL)
	{
		pDsChMag->m_strValue = pRtMag->m_strValue;
	}

	if (pDsChPh != NULL && pRtAng != NULL)
	{
		pDsChPh->m_strValue = pRtAng->m_strValue;
	}

	return TRUE;
}

long CSttTestCtrlCntrNative::On_RtData(CDataGroup *pRtData)
{//2022-10-6  lijunqing
	CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

	if (pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	CDvmDataset *pDsRcdStep6U6I = pXSttCap_61850->AddDataset_dsRcdStep6U6I();
	
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("U1"), _T("Ua1"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("U2"), _T("Ub1"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("U3"), _T("Uc1"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("U4"), _T("Ua2"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("U5"), _T("Ub2"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("U6"), _T("Uc2"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("I1"), _T("Ia1"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("I2"), _T("Ib1"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("I3"), _T("Ic1"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("I4"), _T("Ia2"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("I5"), _T("Ib2"));
	RtData_To_RcdStep6U6I_Ch(pRtData, pDsRcdStep6U6I, _T("I6"), _T("Ic2"));
	CDvmData *pSrcData = (CDvmData*)pDsRcdStep6U6I->FindByID(_T("Freq"));//zhouhj ����Ƶ��Ĭ��Ϊ50Hz  

	if (pSrcData != NULL)
	{
		pSrcData->m_strValue = _T("50.00");
	}

	pXSttCap_61850->UpdateUI_Paras();
	pXSttCap_61850->ClearMUTestResults();

	return 0;
}

void CSttTestCtrlCntrNative::ConnectAtsServer()
{
	m_oSttAtsClient.ConnectAtsTestServer();
}

void CSttTestCtrlCntrNative::OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	CSttTestCtrlCntrBase::OpenMacroTestUI(pTestMacroUI);

	if (pTestMacroUI == NULL)
	{
		return;
	}

	m_pSttGuideBook->ClearGuideBook();
	CString strFile = stt_ui_GetTestTemplateFile(pTestMacroUI->m_strID);
	m_pSttGuideBook->OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttTestCtrlCntrNative::GetMacroUI_GbItems(CString &strMacroUI_Items)
{
	//��ȡm_pCurrEditMacroItems�ĸ�Ҫ��Ϣ
}

CExBaseList* CSttTestCtrlCntrNative::GetTestGlobalParas()
{
	if (m_oSttAtsClient.m_pXClientEngine == NULL)
	{
		return NULL;
	}

	return m_oSttAtsClient.m_pXClientEngine->GetTestGlobalParas();
}

//ģ��������صĽӿ�
//�������ܵ�ģ������
long CSttTestCtrlCntrNative::Ats_GenerateTemplate()
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin ConnectAtsTestServer");	}
	BOOL bRet = m_oSttAtsClient.ConnectAtsTestServer();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end ConnectAtsTestServer");	}

	if (! bRet)
	{
		return 0;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = g_pTheSttTestApp->m_pTestMacroUI;
	CDataGroup *pCommCmd = NULL;  //ͨѶ�����������ã�
	CSttContents *pContents = NULL;//�������߶���
	CString strDvmFile = _T("");

	if (pTestMacroUI->m_strID == STT_ORG_MACRO_MUAccurAutoTest)//20230227 �ϲ���Ԫ�Զ�����ʱ,��Ҫ���ظ�ģ���ļ�
	{
		strDvmFile = _T("SttIecRecordDetectDvm.xml");
	}

 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && g_theTestCntrFrame->m_pCharacteristics != NULL)
 	{
		g_theTestCntrFrame->UpdateCharScriptByUIParas(&m_oTestMacroUI_Paras);//���ݽ�������������������еĽű���������
		pContents = new CSttContents;
		pContents->m_strID = STT_CMD_PARA_Characteristic;
		g_theTestCntrFrame->m_pCharacteristics->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys, pContents->m_strText);
 	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin Ats_GenerateTemplate");	}
	long nSucc = m_oSttAtsClient.Ats_GenerateTemplate(pTestMacroUI->GetTestMacroUIDataGroup(),
		&m_oTestMacroUI_Paras,pCommCmd, pContents, STT_CMD_PARA_TtRetMode_GBXML, g_oSystemParas.HasDigitalInOrOut(),
		TRUE,NULL,strDvmFile);
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end Ats_GenerateTemplate");	}

	return nSucc;
}

// CDataGroup *pCommCmd;  //ͨѶ�����������ã�
long CSttTestCtrlCntrNative::Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
											   , CDataGroup *pCommCmd, const CString &strDvmFile, const CString strTestClass)
{
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = g_pTheSttTestApp->m_pTestMacroUI;
	CSttContents *pContents = NULL;//�������߶���

	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && g_theTestCntrFrame->m_pCharacteristics != NULL)
	{
		g_theTestCntrFrame->UpdateCharScriptByUIParas(&m_oTestMacroUI_Paras);//���ݽ�������������������еĽű���������
		pContents = new CSttContents;
		pContents->m_strID = STT_CMD_PARA_Characteristic;
		g_theTestCntrFrame->m_pCharacteristics->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys, pContents->m_strText);
	}

	return m_oSttAtsClient.Ats_GenerateItems(strItemParentPath, strItemsName, strItemsID
		, pTestMacroUI->GetTestMacroUIDataGroup(),&m_oTestMacroUI_Paras,pCommCmd, pContents
		, strDvmFile, strTestClass, STT_CMD_PARA_TtRetMode_GBXML, g_oSystemParas.HasDigitalInOrOut()/* || g_oSystemParas.m_nUseDigitalMeas*/);
}

long CSttTestCtrlCntrNative::Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	long nRet = 0;
	CString strContents;
	CDataGroup oItemParas;
	oItemParas.m_strName = STT_CMD_PARA_ItemParas;
	oItemParas.m_strID = STT_CMD_PARA_ItemParas;

	if (strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		++CCfgDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;
		strContents = g_oSttTestResourceMngr.m_oIecDatasMngr.GetXml(CCfgDataMngrXmlRWKeys::g_pXmlKeys);
		--CCfgDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;
		//oIecDataGroup.AddTail(&g_oSttTestResourceMngr.m_oIecDatasMngr);
		nRet = m_oSttAtsClient.Ats_SetItemPara(strItemPath,strMacroID,&oItemParas, TRUE, NULL, strContents);
		oItemParas.RemoveAll();
	}
	else if (strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		strContents = g_oSttTestResourceMngr.m_oChMaps.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		//oIecDataGroup.AddTail(&g_oSttTestResourceMngr.m_oIecDatasMngr);
		nRet = m_oSttAtsClient.Ats_SetItemPara(strItemPath,strMacroID,&oItemParas, TRUE, NULL, strContents);
		oItemParas.RemoveAll();
	}
	else if (strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		//2022-9-19  lijunqing  ͬ���Ĵ��룬�����˺ü����ط�
/*
		CSttMacro *pSysConfigMacro = new CSttMacro;
		CSttParas *pSttParas = new CSttParas;
		pSysConfigMacro->AddNewChild(pSttParas);
		CSttDataGroupSerializeRegister oRegister(pSttParas);
		stt_xml_serialize(&g_oSystemParas, &oRegister);
		//�˴�δ��ɣ���Ҫ��ϵͳ�����Ľṹ�壬ת�ɶ���  shaolei
		CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		strContents = pSysConfigMacro->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		//oIecDataGroup.AddTail(&g_oSttTestResourceMngr.m_oIecDatasMngr);
		delete pSysConfigMacro;
*/
		stt_SystemParas_GetString(strContents);
		nRet = m_oSttAtsClient.Ats_SetItemPara(strItemPath,strMacroID,&oItemParas, TRUE, NULL, strContents);
		oItemParas.RemoveAll();
	}
	else
	{
		nRet = m_oSttAtsClient.Ats_SetItemPara(strItemPath,strMacroID,&m_oTestMacroUI_Paras);
	}

	return nRet;
}

long CSttTestCtrlCntrNative::Ats_SetItemPara_RsltExpr(const CString &strItemPath, const CString& strRlstExpr)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_SetItemPara(strItemPath, _T(""), NULL, TRUE, NULL, _T(""), strRlstExpr);
}

long CSttTestCtrlCntrNative::Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName,
										  const CString &strItemID, const CString &strMacroID, const CString &strItemParas)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_AddMacro(strParentItemPath, strItemName, strItemID, strMacroID, strItemParas);
	return 0;
}

long CSttTestCtrlCntrNative::Ats_UpdateItem(const CString &strItemPath)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_UpdateItem(strItemPath,&m_oTestMacroUI_Paras);
}

long CSttTestCtrlCntrNative::Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_UpdateItem(strItemPath, strItemParas);
}

long CSttTestCtrlCntrNative::Ats_QueryItem(const CString &strItemPath)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_QueryItem(strItemPath);
}

long CSttTestCtrlCntrNative::GetGbItemCount()
{
	if (m_pSttGuideBook == NULL)
	{
		return 0;
	}

	return m_pSttGuideBook->GetGbItemCount();
}

BOOL CSttTestCtrlCntrNative::IsHasTestTask()
{
	if (m_pSttGuideBook == NULL)
	{
		return FALSE;
	}

	CSttDevice *pDevice = m_pSttGuideBook->GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttTestCtrlCntrNative::StartTest(CDataGroup *pCurrentUIParas)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = g_pTheSttTestApp->m_pTestMacroUI;
	CString strDvmFile;
	strDvmFile = _T("");

	if (pTestMacroUI->m_strID == STT_ORG_MACRO_MUAccurAutoTest)//20230227 �ϲ���Ԫ�Զ�����ʱ,��Ҫ���ظ�ģ���ļ�
	{
		strDvmFile = _T("SttIecRecordDetectDvm.xml");
	}

	if (pCurrentUIParas != NULL)
	{
		pCurrentUIParas->SetDataValue(_T("Un"),(double)(g_oSystemParas.m_fVNom/SQRT3),FALSE);//����ϵͳ�����еĶ��ѹ,���µ�������(�غ�բ����� �����ȡ��ѹʹ��)
		//�˴�Ӧ�ñȽϣ��Ƿ���������ı䣬�����ı���·�MacroUI��UIParas
		/*???
		�˴�Ӧ������Ҫ�ж��������߲����Ƿ�༭�����༭�ı䣬Ҳ��Ҫ�·���Ӧ�Ĳ�����
		������жϣ�g_theTestCntrFrame����һ��BOOL�жϣ�
		???*/
		if ((!pCurrentUIParas->IsEqual(&m_oTestMacroUI_Paras))||
			(g_theTestCntrFrame->HasCharChanged()))
		{
			pCurrentUIParas->UpdateChildren(&m_oTestMacroUI_Paras);//zhouhj 20220404 ����·������뵱ǰ������һ��,����µ�ǰ����,���º��·�,�´ο�ʼ����ʱ,��Ҫ����ǰ�������бȽ�

			//�����������ı�ʱ�������������ߵĲ��֣�Ҳ��Ҫ����������ƴ�ӵ�������
			CDataGroup *pCommCmd = NULL;  //ͨѶ�����������ã�
			CSttContents *pContents = NULL;//�������߶���

			if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && g_theTestCntrFrame->m_pCharacteristics != NULL)
			{
				g_theTestCntrFrame->UpdateCharScriptByUIParas(pCurrentUIParas);//���ݽ�������������������еĽű���������
				pContents = new CSttContents;
				pContents->m_strID = STT_CMD_PARA_Characteristic;
				g_theTestCntrFrame->SetCharChanged(false);
				g_theTestCntrFrame->m_pCharacteristics->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys, pContents->m_strText);
			}

			return m_oSttAtsClient.Ats_StartTest(pTestMacroUI->GetTestMacroUIDataGroup(),pCurrentUIParas, pCommCmd, pContents,TRUE,NULL,strDvmFile);
		}
	}
	
	return m_oSttAtsClient.Ats_StartTest(NULL, NULL, NULL, NULL,TRUE,NULL,strDvmFile);
}

BOOL CSttTestCtrlCntrNative::StopTest()
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}

	return m_oSttAtsClient.Ats_StopTest();
}

long CSttTestCtrlCntrNative::SendManuTrigger()
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_ManuTrigger();
}

void CSttTestCtrlCntrNative::GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList)
{
	if (m_pSttGuideBook == NULL)
	{
		return;
	}

	CSttDevice *pDevice = m_pSttGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	pDevice->GetAllItemsByID(strItemID, oItemList);
}


//2022-3-29  lijunqing
//�ɹ�����3
long CSttTestCtrlCntrNative::TestItem(const CString &strItemPath)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_TestItem(strItemPath);
}

long CSttTestCtrlCntrNative::TestFrom(const CString &strItemPath)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	return m_oSttAtsClient.Ats_TestFrom(strItemPath);
}


void CSttTestCtrlCntrNative::FillReport(CSttReports *pSttReports)
{
	
}

CExBaseList* CSttTestCtrlCntrNative::GetReports()
{
	return NULL;
}

//yzj 2022-2-20 û��ʹ������,��ִ����ɺ������oInfoList����Ұָ�����
void CSttTestCtrlCntrNative::GetEventInfo(CExBaseList& oInfoList)
{
	m_oSttAtsClient.GetEventInfo(oInfoList);
}

bool CSttTestCtrlCntrNative::IsTestStarted()
{
	if(m_oSttAtsClient.m_pXClientEngine == NULL)
	{
		return false;
	}

	return m_oSttAtsClient.m_pXClientEngine->m_bTestStarted;
}

bool CSttTestCtrlCntrNative::IsTestAppConnect()
{
	return m_oSttAtsClient.m_bTestAppConnect;
}

//ģ�塢�������ݵ���صĽӿ�  2022-3-14  lijunqing
CString CSttTestCtrlCntrNative::SaveTestFile(const CString &strRealPath, const CString &strTemplateFileName)
{
	if (m_pSttGuideBook == NULL)
	{
		return "";
	}

	CString strFile;
	strFile = _P_GetWorkspacePath();
	
	if (strRealPath .GetLength() > 0)
	{
		strFile += strRealPath;
	}

	ValidatePath(strFile);
	CreateAllDirectories(strFile);

	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	if (strTemplateFileName.GetLength() <= 0)
	{
		strFile.AppendFormat("%d-%d-%d %d-%d-%d.dscxml", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	}
	else
	{
		strFile += strTemplateFileName;
		strFile = ChangeFilePostfix(strFile, "dscxml");
	}

	m_pSttGuideBook->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Save Test File=%s", strFile.GetString());

	return strFile;
}

CString CSttTestCtrlCntrNative::SaveSysTemplateFile(const CString &strTemplateFileName)
{
	if (m_pSttGuideBook == NULL)
	{
		return "";
	}

	CString strFile;

	if (strTemplateFileName.GetLength() <= 0)
	{
		strFile =stt_ui_GetTestTemplateFile(m_pCurrTestMacroUI->m_strID);
	}
	else
	{
		strFile =stt_ui_GetTestTemplateFile(strTemplateFileName);
	}

	m_pSttGuideBook->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Save Test File=%s", strFile.GetString());

	return strFile;
}

CString CSttTestCtrlCntrNative::SaveTemplateFile(const CString &strTemplateFileName)
{
	if (m_pSttGuideBook == NULL)
	{
		return "";
	}

	CString strFile;
	strFile = _P_GetTemplatePath();

	if (strTemplateFileName.GetLength() <= 0)
	{
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		strFile.AppendFormat("%d-%d-%d %d-%d-%d.dscxml", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	}
	else
	{
		strFile += strTemplateFileName;
		strFile = ChangeFilePostfix(strFile, "dscxml");
	}

	m_pSttGuideBook->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Save Template File=%s", strFile.GetString());

	return strFile;
}

BOOL CSttTestCtrlCntrNative::SaveTemplate(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}

	if (pCurrentUIParas == NULL)
	{
		return m_oSttAtsClient.Ats_SaveTemplate(strPath, strFileName);
	}

	//�Ժ������Ҫ���Ͻ����������Ӧ�Խ�������޸ĺ�ֱ�ӵ������ģ�������
	//�˴�Ӧ�ñȽϣ��Ƿ���������ı䣬�����ı���·�MacroUI��UIParas
	if (!pCurrentUIParas->IsEqual(&m_oTestMacroUI_Paras))
	{
		pCurrentUIParas->UpdateChildren(&m_oTestMacroUI_Paras);
		CSttMacroTestUI_TestMacroUI *pTestMacroUI = g_pTheSttTestApp->m_pTestMacroUI;
		return m_oSttAtsClient.Ats_SaveTemplate(strPath, strFileName,pTestMacroUI->GetTestMacroUIDataGroup(),pCurrentUIParas);
	}
	else
	{
		return m_oSttAtsClient.Ats_SaveTemplate(strPath, strFileName);
	}
}

BOOL CSttTestCtrlCntrNative::SaveTest(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}

	if (pCurrentUIParas == NULL)
	{
		return m_oSttAtsClient.Ats_SaveTest(strPath, strFileName);
	}

	//�Ժ������Ҫ���Ͻ����������Ӧ�Խ�������޸ĺ�ֱ�ӵ������ģ�������
	//�˴�Ӧ�ñȽϣ��Ƿ���������ı䣬�����ı���·�MacroUI��UIParas
	if (!pCurrentUIParas->IsEqual(&m_oTestMacroUI_Paras))
	{
		pCurrentUIParas->UpdateChildren(&m_oTestMacroUI_Paras);
		CSttMacroTestUI_TestMacroUI *pTestMacroUI = g_pTheSttTestApp->m_pTestMacroUI;
		return m_oSttAtsClient.Ats_SaveTest(strPath, strFileName,pTestMacroUI->GetTestMacroUIDataGroup(),pCurrentUIParas);
	}
	else
	{
		return m_oSttAtsClient.Ats_SaveTest(strPath, strFileName);
	}
}

BOOL CSttTestCtrlCntrNative::OpenTemplate(const CString &strFileWithPath)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}

	return m_oSttAtsClient.Ats_OpenTemplate(strFileWithPath);
}

void CSttTestCtrlCntrNative::CloseTest()
{
	m_oSttAtsClient.Ats_CloseTest();
}


//2022-4-14 lijunqing
void CSttTestCtrlCntrNative::Ats_IecDetect(long bEnable)
{
	m_oSttAtsClient.Ats_IecDetect(bEnable);
}

void CSttTestCtrlCntrNative::Ats_IecRecord(CDataGroup *pIecRecordParas)
{
	m_oSttAtsClient.Ats_IecRecord(pIecRecordParas);
}

long CSttTestCtrlCntrNative::OnConnectStateChanged(bool bState)
{
	long nRet = 0;

	if (!bState)
	{
		nRet = m_pTestCtrlCntrMsg->OnTestStoped();//���Socket������,���������淵�ص�ֹͣ����״̬
	}

	return nRet;
}

//2022-10-5  lijunqing
void  CSttTestCtrlCntrNative::InitMeasServer()
{
	CSttTestAppCfg* pSttTestAppCfg = m_oSttAtsClient.GetSttTestAppCfg();

	if(!pSttTestAppCfg)
	{
		return;
	}

	CString strIP = pSttTestAppCfg->GetLocalIP();
	CXSmartCapMngr::Create();

	CIotPxEngineServer::Create();
	CSttPpEngineServer::Create(const_cast<char*>(strIP.GetString()), 19821);
	CIotPxEngineServer::RegisterFactory(new CPpSttIotMeasServer);

#ifndef _PSX_QT_LINUX_
	//Ĭ�ϴ��ļ�SttIecRecordDetectDvm.xml������ģ�����
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CString strFile;
	strFile += _P_GetDBPath();
	strFile += _T("SttIecRecordDetectDvm.xml");
	pXSttCap_61850->m_pDvmDevice->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
}

void  CSttTestCtrlCntrNative::ExitMeasServer()
{
	CXSmartCapMngr::Release();
	CIotPxEngineServer::Release();
	CSttPpEngineServer::Release();
}

