#include "SttTestCntrFrameBase.h"
#include "Module/DeviceInforDlg/QDeviceInforDlg.h"
//2022-12-02 �޸Ĺ���ID���������еĶ�Ҫ���룬Ч�ʵ��£����Դ�ͷ�ļ���ȥ�������κ���Ҫ�����ĵط����а���
#include "SttTestCntrCmdDefine.h" 

#include "State/SttMacroParaEditViewState.h"
#include "State/GooseAbnormal/SttMacroParaEditViewGooseAbnormal.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../SttSystemConfig/SttSystemConfigGlobal.h"
#include "../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttTestCmd.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../SttSystemConfig/SttSystemConfig.h"
#include "Controls/SttFileSaveAsDlg.h"
#include "Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../SttCmd/GuideBook/SttItemStateObject.h"
#include "../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "Manual/SttMacroParaEditViewManual.h"
#include "../Module/UI/Controls/SttCustomSetDlg.h"
#include "Module/ModuleSetDlg/QModuleSetDlg.h"
#include "Controls/FileMngr/SttFileMngrDlg.h"
#include "Module/PopupDialog/SttFileMngrTool.h"
#include "Module/LuminousPower/LuminousPowerDlg.h"
#include "../Module/SttTest/Common/tmt_replay_test.h"
#include "../XLangResource_Native.h"
#include "../RecordTest/UI/SttIecCapDialog.h"
#include "Module/SysParas/QSysParasDlg.h"
#include "../Module/UI/Interface/SttHtmlViewApi.h"

#ifdef _PSX_QT_LINUX_
#include "IEC61850Config/SttIecConfigDialogLinux.h"
#else
#include "IEC61850Config/SttIecConfigDialogWin.h"
#endif

#ifdef _USE_SoftKeyBoard_	
#include "SoftKeyboard/SoftKeyBoard.h"
#endif

#ifndef _NOT_USE_SttTestCntrThread_
#include "SttTestCntrThread.h"
#endif

#include "Module/PopupDialog/SttPopupSaveAsDialog.h"
#include "Module/HardwareSetDlg/QHardwareSetDlg.h"

#ifndef NOT_USE_ASSIST
#include "../Assist/DynEffect/SttAssistWndDynEffExecTool.h"
#endif
#include "Controls/SafetyMsgCfg/SttSafetyMsgCfgGlobal.h"

#include "../UI/Module/CommConfigurationDlg/CommCfg/QSttCommCfgMainDlg.h"
#include "../UI/Module/CommConfigurationDlg/DevComm/QSttCommCfgDeviceDlg.h"
#include "../UI/Module/CommConfigurationDlg/ProtocolTempl/QSttCommCfgProtocolTemplateDlg.h"
#include "../UI/Module/CommConfigurationDlg/PointTblFile/QSttCommCfgPointTblFileImportDlg.h"
#include "Module/CommConfigurationDlg/PkgMonitor/QSttCommCfgPkgMonitorDlg.h"
#include "../RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#include "../RecordTest/UI/MUTest/SttIecRecordCbInterface.h"
//#include "Module/BinReverseConfig/QBinReverseCfgDialog.h"
#include "Module/BinBoutCommMap/QBinBoutCommMapDialog.h"

//#include "../../../AutoTest/Module/XrioRead/XDeviceModel/XDeviceModel.h"
#include "Controls/SettingCtrls/QSettingGlobal.h"

#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include "FA/QSttMacroParaEditViewVolTimeTypeSec.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;
QSttTestCntrFrameBase *g_theTestCntrFrame = NULL;
double g_dUIShowCoef = 1.0f; // ������ʾ���ű���

// bool g_bIsOpenMacroFromMain = FALSE;
CDataGroup *g_pGlobalDatas = NULL;

#ifdef use_sttdebuglogwidget
//2024-9-9 lijunqing 
extern long g_sttdebuglogwidget;
#endif
int g_nUpdateMultiMacroParaEditView = 1;

BOOL QSttTestCntrFrameBase::HasManuTrigerBtn()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = g_pTheSttTestApp->m_pTestMacroUI;

	if (pTestMacroUI->m_strID == STT_ORG_MACRO_StateTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_ORG_MACRO_SmvAbnTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_ORG_MACRO_GseAbnTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_ORG_MACRO_ReplayTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_HTML_MACRO_ZeroTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_HTML_MACRO_DistanceTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_HTML_MACRO_OverCurrentTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_HTML_MACRO_RecloseAccTest)
	{
		return TRUE;
	}
	else if (pTestMacroUI->m_strID == STT_ORG_MACRO_CBOperateTest)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL QSttTestCntrFrameBase::IsManuTriger_HtmlFaultTrigMode()
{
	if (m_pTestMacroUI_Paras == NULL)
	{
		return FALSE;
	}

	CDvmData *pDvmData = (CDvmData*)m_pTestMacroUI_Paras->FindByID("FaultTrigMode");

	if (pDvmData == NULL)
	{
		return FALSE;
	}

	long nFaultTrigMode = CString_To_long(pDvmData->m_strValue);

	if (nFaultTrigMode == 1)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL QSttTestCntrFrameBase::IsMenuBtn(QWidget *pWidget)
{
	if (m_pMenu_FrameButton == NULL)
	{
		if (m_pSttFrameConfig != NULL)
		{
			CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();

			if (pToolBarParas != NULL)
			{
				m_pMenu_FrameButton = pToolBarParas->FindBtnByID(_T("Menu"));
			}
		}
		
		if (m_pMenu_FrameButton == NULL)
		{
			return FALSE;
		}
	}

	return (m_pMenu_FrameButton->m_dwItemData == (DWORD)pWidget);
}

BOOL QSttTestCntrFrameBase::IsMenuWidget(QWidget *pWidget)
{
	return FALSE;
}

BOOL QSttTestCntrFrameBase::SetValues_dsRcdStep6U6I(BOOL bClearResult)
{
// 	if (!g_bSmartCap_RecordNow)
// 	{
// 		return FALSE;
// 	}

	if ((g_pTheSttTestApp->m_pTestMacroUI == NULL)||(m_pMacroEditView == NULL))
	{
		return FALSE;
	}

	if (g_pTheSttTestApp->IsMuTest())
	{
		CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

		if (pXSttCap_61850 == NULL)
		{
			return FALSE;
		}

		CDvmDataset *pDsRcdStep6U6I = pXSttCap_61850->AddDataset_dsRcdStep6U6I();
		BOOL bRet = FALSE;

		if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
		{
			bRet = ((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->SetValues_dsRcdStep6U6I(pDsRcdStep6U6I);
		}
		
		pXSttCap_61850->UpdateUI_Paras(bRet);

		if (bClearResult)
		{
			pXSttCap_61850->ClearMUTestResults();
		}

		return bRet;
	}
	else
	{
		return FALSE;
	}
}


BOOL QSttTestCntrFrameBase::SetValues_dsRcdStep6U6I( CDataGroup *pDataGroup,BOOL bClearResult )
{
// 	if ((g_pTheSttTestApp->m_pTestMacroUI == NULL)||(m_pMacroEditView == NULL) || (pDataGroup ==  NULL))
// 	{
// 		return FALSE;
// 	}
	if (pDataGroup ==  NULL)
	{
		return FALSE;
	}

	if (g_pTheSttTestApp->IsMuTest())
	{
		CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

		if (pXSttCap_61850 == NULL)
		{
			return FALSE;
		}
// 		CDvmDataset *pDsRcdStep6U6I = pXSttCap_61850->AddDataset_dsRcdStep6U6I();
// 		BOOL bRet = FALSE;

		CDvmDataset *pDsRcdStep6U6I = pXSttCap_61850->m_pDataset_RcdStep6U6I;
		BOOL bRet = FALSE;

		if (pDsRcdStep6U6I)
		{
			bRet = TRUE;
		}

		POS pos = pDsRcdStep6U6I->GetHeadPosition();
		CString strSrcID;
		CDvmData *pSrcData = NULL, *pDesData = NULL;

		//������Ի�ȡXML�ļ��е�ֵ��
		while (pos != NULL)
		{
			pSrcData  =  (CDvmData *)pDsRcdStep6U6I->GetNext(pos);
			strSrcID  =  pSrcData->m_strID;
			//	strID = strSrcID.Left(nCnt);
			if (strSrcID == X61850_CapID_ZeroDrift_Un)
			{
				pDesData = (CDvmData *)pDataGroup->FindByID(_T("Unom"));
				if(pDesData)
				{
					pSrcData->m_strValue = /*CString_To_double(*/pDesData->m_strValue;
//                     CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Unom: %s"),pSrcData->m_strValue.GetString());
					continue;
				}
			}
			else if (strSrcID == X61850_CapID_ZeroDrift_In)
			{
				pDesData = (CDvmData *)pDataGroup->FindByID(_T("Inom"));
				if(pDesData)
				{
					pSrcData->m_strValue = /*CString_To_double(*/pDesData->m_strValue/*)*/;
//                     CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Inom: %s"),pSrcData->m_strValue.GetString());
					continue;
				}
			}
		}

// 		pXSttCap_61850->UpdateUI_Paras(bRet);
// 
// 		if (bClearResult)
// 		{
// 			pXSttCap_61850->ClearMUTestResults();
// 		}

		return bRet;
	}
	else
	{
		return FALSE;
	}
}

void QSttTestCntrFrameBase::InitSttIecRecord()
{
}

// void QSttTestCntrFrameBase::InitSttCap_MUTerminal()
// {
// }

void QSttTestCntrFrameBase::InitAfterCreateSttMacroPara()
{
	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

	if(strIDMacroUI == STT_ORG_MACRO_MUTimingAccurTest || strIDMacroUI == STT_ORG_MACRO_MUPunctAccurTest)
	{
		InitSttIecRecord();
		g_bSmartCap_RecordNow = FALSE;//������ӽ���ʱ,ֹͣ���Ľ���
		CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

		if (pXSttCap_61850 != NULL)
		{
			pXSttCap_61850->MUTimeTestRlt_AddDataset();
		}
	}
	else if (strIDMacroUI == STT_ORG_MACRO_RemoteMeasTest || strIDMacroUI == STT_ORG_MACRO_RemoteCtrlTest)
	{
		CreateEngineClientWidget();
	}
}

void QSttTestCntrFrameBase::slot_UpdateHtmlManuTrigerBtn_Testing()
{
	if (HasManuTrigerBtn()&&(g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb()))
	{
		if (IsManuTriger_HtmlFaultTrigMode())
		{
			EnableManualTriggerButton(true);
//			UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true,true);
		} 
		else
		{
			EnableManualTriggerButton(false);
//			UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
		}
	}
}

void QSttTestCntrFrameBase::slot_UpdateSysConfig()
{
	g_oSttTestResourceMngr.m_oIecDatasMngr.UpdateFT3ChsType(g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nIecFormatMeas);
	//�ж��Ƿ��޸�ϵͳ����,��ǰ�Ƿ�����˲��Թ���ģ��,��ǰ���Թ���ģ���Ƿ�Ϊ��ҳ
	if (g_oSttSystemConfig.GetSelSysPata() &&(g_pTheSttTestApp->m_pTestMacroUI != NULL) && (m_pMacroEditView!=NULL))//�жϵ�ǰ�Ƿ�����˲��Թ���ģ��,���жϵ�ǰ���Թ���ģ���Ƿ�Ϊ��ҳ
	{
		if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
		{	
			CSttMacroParaEditViewOriginal* pOriginal = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pOriginal->UpdateSerializeSysParas();
		}
	}

	OnUpdateTestResource(FALSE);
	Cmd_SendChMapsConfig();//20221026 zhouhj �ȷ���ͨ��ӳ��,����ϵͳ����������Ϣ,ϵͳ���º�������µ�ģ�������ļ�,ͬʱ������λ�������������
	Cmd_SendSystemConfig();


	if ((g_dFixFreqCalValue>1.0f)&&(g_oSystemParas.m_fFNom>1.0f))
	{
		g_dFixFreqCalValue = g_oSystemParas.m_fFNom;
	}

	//2024-6-27 wuxinyi ��ײ㷢�����ϵͳ�������ٿ�ʼˢ��ʵʱ����
	g_theTestCntrFrame->m_bUpdateHardCfgFromRealTime = true;

}

void QSttTestCntrFrameBase::slot_UpdatePowerGear()
{
	Cmd_SendSystemConfig();
}

void QSttTestCntrFrameBase::slot_OnItemStateChanged_Frame(CExBaseObject *pItem)
{
	CSttItemStateObject* pObj = (CSttItemStateObject*)pItem;

	CSttItemBase *pSttItem = (CSttItemBase*)pObj->m_pItem;
//	CSttReports *pSttReports = pSttItem->GetSttReports();
	CString strItemID,strBeforeTestString;
	strBeforeTestString.Format(_T("$%s$"),STT_ITEMS_ID_BEFORETEST);
	//strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	CString strParentItemsPath, /*strItemID,*/ strState;
	CExBaseObject *pParent = (CExBaseObject*)pSttItem->GetParent();
	strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	if (strParentItemsPath.IsEmpty() || g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}
	strItemID = pObj->m_pItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	strState = Gb_GetTestStateByID(pSttItem->m_nState);
	//�����״̬��������������id

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		CString strMacroID =  g_pTheSttTestApp->GetCurrTestMacroUI();
		if (strMacroID == STT_MACRO_ID_StateTest)
		{
            if(m_pMacroEditView)
            {
			QSttMacroParaEditViewState *pState = (QSttMacroParaEditViewState *)m_pMacroEditView;
			if (pState->m_nCircle >= 2)
			{
				CExBaseObject *pParent = (CExBaseObject *)pObj->m_pItem->GetParent();
				CString strId;
				strId.Format(_T("StateTest%d"), pState->m_nCircle);
				//״̬����ѭ��ʱ�����һ��Ϊ����״̬������ΪNORMAL

                //if ((pParent->m_strID != strId) && (m_pSttReportViewHtml != NULL))
                //{
                //	m_pSttReportViewHtml->ItemStateChanged(strParentItemsPath, strItemID, TEST_STATE_DESC_NORMAL);
                //	strState = Gb_GetTestStateByID(pSttItem->m_nState);
                //	m_pSttReportViewHtml->ItemStateChanged(strParentItemsPath, strId, strState);
                //	m_bIsUpdateStateTestFirstReportColor = TRUE;
                //}
			}
		}
	}

		//���½��״̬
		if (strMacroID == STT_ORG_MACRO_VolTimeTypeSecTest || 
			strMacroID ==  STT_ORG_MACRO_VolTimeTypeIntTest || 
			strMacroID ==  STT_ORG_MACRO_VolCurTypeSecTest || 
			strMacroID ==  STT_ORG_MACRO_VolCurTypeIntTest || 
			strMacroID ==  STT_ORG_MACRO_AdaptiveTypeSecTest)
		{
			if(m_pMacroEditView)
			{
				QSttMacroParaEditViewVolTimeTypeSec *pVolTimeTypeSec = (QSttMacroParaEditViewVolTimeTypeSec *)m_pMacroEditView;
				if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST && !strItemID.contains(strBeforeTestString))
				{
					pVolTimeTypeSec->UpdateResultState(strItemID,strState);	
				}
			}
		}
	}
	
	if (!m_bIsUpdateStateTestFirstReportColor)
	{
    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->ItemStateChanged(strParentItemsPath, strItemID, strState);
    //}
	}
	
	if (IsAutoTest())
	{
		return;
	}

	if (pSttItem->m_nState == TEST_STATE_TESTING)//zhouhj 20220406 ����ǲ��Թ�����,�����ֶ�������ť
	{
		slot_UpdateHtmlManuTrigerBtn_Testing();  //zhouhj 20220618 slot_OnItemStateChanged_Frame�ۺ����Ѿ������߳������ٷ����ź�,�����߳��з����źŸ����߳̿��ܻ������̷߳��͵��źŻ���
//		emit sig_UpdateHtmlManuTrigerBtn_Testing();
	}

	UINT nClassID = pParent->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
	{
		CSttMacroCharItems *pCharItems = (CSttMacroCharItems *)pParent;
		CSttItems *pCharItemsParent = (CSttItems *)pCharItems->GetParent();
		CString strCharacterId/* = pCharItemsParent->m_strCharacteristicID*/;
		//ItemID����������ID����һ��
		CString strBase64;
		CDataGroup *pSearchLine = (CDataGroup *)pObj->m_pParas->FindByID("SearchLine");

		if(pSearchLine)
		{
			CString strCurItemStateChanged_SearchLineString,strValue;
			CSttCharacteristic* pSttChar = (CSttCharacteristic*)pCharItems->FindByClassID(STTGBXMLCLASSID_CSTTCHARACTERISTIC);
			strCharacterId = pSttChar->m_strID;
			m_pSttCharacterDrawPng->InitCharDrawTest(strCharacterId, CString_To_long(pSttChar->m_strIndex));
			CSttMacroTestUI_TestMacroUI *pTestMacroUI = m_pTestCtrlCntrBase->GetCurrTestMacroUI();
			if (pTestMacroUI->m_strID == STT_ORG_MACRO_CurrInverseTimeTest)
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(CSttCharacterDrawPng::CurrInverseTime);
			}
			else if (pTestMacroUI->m_strID == STT_ORG_MACRO_VolInverseTimeTest)
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(CSttCharacterDrawPng::VolInverseTime);
			}
			else if (pTestMacroUI->m_strID == STT_ORG_MACRO_UFInverseTimeTest)
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(CSttCharacterDrawPng::VolInverseTime);
			}
			else if ((pTestMacroUI->m_strID == STT_ORG_MACRO_DiffCurr6ITest)||(pTestMacroUI->m_strID == STT_ORG_MACRO_LineDiffCurr6ITest)
				||(pTestMacroUI->m_strID == STT_ORG_MACRO_BusDiffCurr6ITest)||(pTestMacroUI->m_strID == STT_ORG_MACRO_ElecRailwayDiffTest))
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(CSttCharacterDrawPng::DiffCurr6I);
			}
			else if ((pTestMacroUI->m_strID == STT_ORG_MACRO_DistanceTest)||(pTestMacroUI->m_strID == STT_ORG_MACRO_DistanceTest_I))
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(CSttCharacterDrawPng::Distance);
			}
			else if ((pTestMacroUI->m_strID == STT_ORG_MACRO_DistanceSearchTest)||(pTestMacroUI->m_strID == STT_ORG_MACRO_DistSearchOneTest))
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(CSttCharacterDrawPng::DistanceSearch);
			}
			else
			{
				m_pSttCharacterDrawPng->InitCharDrawTestAxis(NULL);
			}

			m_pSttCharacterDrawPng->GetSearchingPng(pSearchLine, strBase64);
			CString strCharactPath;
			strCharactPath = strParentItemsPath + _T("Img");

            //if (m_pSttReportViewHtml != NULL)
            //{
            //	m_pSttReportViewHtml->FillReportImg("", strCharactPath, strBase64);//zhouhj 20230213 ���ڲ���ͼƬ
            //}

//  		double dXb = CString_To_double(((CDvmData*)pSearchLine->FindByID("search-x-b"))->m_strValue);
//  		double dXe = CString_To_double(((CDvmData*)pSearchLine->FindByID("search-x-e"))->m_strValue);
//  		double dYb = CString_To_double(((CDvmData*)pSearchLine->FindByID("search-y-b"))->m_strValue);
// 			double dYe = CString_To_double(((CDvmData*)pSearchLine->FindByID("search-y-e"))->m_strValue);
			strCurItemStateChanged_SearchLineString = pObj->m_strItemID;
			pSearchLine->GetDataValue(_T("search-x-c"),strValue);
			strCurItemStateChanged_SearchLineString.AppendFormat(_T("(%s,"),strValue.GetString());
 			double dXc = CString_To_double(strValue);
			pSearchLine->GetDataValue(_T("search-y-c"),strValue);
			strCurItemStateChanged_SearchLineString.AppendFormat(_T("%s)"),strValue.GetString());
 			double dYc = CString_To_double(strValue);

			//zhouhj 2023.8.22 �����ͬ�򲻸���,�����Զ��������͵�ItemChangedʵ�ʶ���������ı����,�˴���ֹ�ظ�����
			if (strCurItemStateChanged_SearchLineString == m_strItemStateChanged_SearchLineString)
			{
				return;
			}

//			m_pSttCharacterDrawPng->ClearSearchPoints_png();
			m_strItemStateChanged_SearchLineString = strCurItemStateChanged_SearchLineString;

//			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("%s__(%lf,%lf)"),pObj->m_strItemID.GetString(),dXc,dYc);

			if ((strCharacterId == _T("PsuDiffHarmTest"))||(strCharacterId == _T("PsuDiffHarmTest")) && (dYc<0.001f))
			{
				dYc =  CString_To_double(((CDvmData*)pSearchLine->FindByID("y-set"))->m_strValue);
			}

			if (m_pCharTestPointsGrid)
			{
				m_pCharTestPointsGrid->UpdateCurrTestPoint(strCharacterId,pSttChar->m_strIndex,dXc,dYc);
			}

			if (m_pCharactWidgetForTest)//window���²��ô˸���,�����ö���
			{
				m_pCharactWidgetForTest->UpdateCurrTestPoint(strCharacterId,pSttChar->m_strIndex,dXc,dYc);
			}
			else//linux����֮ǰ����һ��
			{
				m_pCharLibWidget->m_pImpCharactWidget->m_pCharacterDrawView->UpdateCurrTestPoint(dXc, dYc);
				m_pCharLibWidget->m_pImpCharactWidget->update();
			}
		}
	}
}

void QSttTestCntrFrameBase::slot_OnInputData(CDataGroup *pParas, CExBaseList *pMsgs)
{

}

void QSttTestCntrFrameBase::slot_OnImportDvm(CExBaseList *pListItems)
{

}

void QSttTestCntrFrameBase::slot_BinBoutCommMapDataUpdate( CDataGroup *pDataGroup )
{

}

void QSttTestCntrFrameBase::slot_UpdateFAParasData( CDataGroup *pDataGroup )
{
	if(!g_pTheSttTestApp->m_pTestMacroUI)
	{
		return;
	}
	if (!g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		return;
	}

	CSttMacroParaEditViewOriginal *pMacroEditView = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
	if (pMacroEditView)
	{
		pMacroEditView->UpdateFAParasData(pDataGroup);
	}
}

QSttTestCntrFrameBase::QSttTestCntrFrameBase(QWidget *parent)
: QMainWindow(parent)
{
	//m_bAutoUpdateNameByTestCount = TRUE;
	m_pStartTestBtn = NULL;
	m_pManualTriggerBtn = NULL;
	m_pExitBtn = NULL;
	m_pMenu_FrameButton = NULL;
#ifdef use_sttdebuglogwidget
	if (g_sttdebuglogwidget == 0)
	{
	CLogPrint::Create(this);
	}
#else
	CLogPrint::Create(this);

#endif
	m_pStatusBar = NULL;
	m_pResultBarUI = NULL;
	m_pResultWidget = NULL;
	m_pSttGbTreeView = NULL;
	m_pOutputWidget = NULL;

	m_pCurrEditMacroItems = NULL;
	m_pTestCtrlCntrBase = NULL;
	m_pEngineClientWidget = NULL;
	m_bIsRunningStartStopCmd = FALSE;

//	m_pSttTestResource = NULL;
	m_pVectorWidget = NULL;
	m_pStateMonitorWidget = NULL;
	m_pPowerDiagramWidget=NULL;
	m_pInfoWidget = NULL;
	m_pCharLibWidget = NULL;
	m_pCharactWidgetForTest = NULL;
	m_pCharTestPointsGrid = NULL;
	m_pMacroEditView = NULL;
    //m_pSysParaEditView = NULL;

	m_pActiveWidget = NULL;
	m_pPrevActiveWidget = NULL; 
	m_nActiveWidgetType = ActiveWidgetType_None; 
	m_nPrevActiveWidgetType = ActiveWidgetType_None; 

	//m_bSelMacroShow = true;
    //m_pSttReportViewHtml = NULL;
	m_pSttIecRecordMainWidget = NULL;
	m_bHasClosedUI = FALSE;
	m_bHasUpdateRptStartTestTime = FALSE;
	m_bIsUpdateStateTestFirstReportColor = FALSE;

	m_pRemoteCtrlWidget = NULL;
	m_bUpdateHardCfgFromRealTime = TRUE;
	m_bUpdateOutputPowerFromRealTime = FALSE;
 	m_bIsRtDataUpdateChMaps_System = FALSE;
// 	m_bFirstUpadeIPowerMode = TRUE;
	m_bOutputTypeHasChanged = FALSE;
	m_fUdc = 0.0f;

	m_pCharacteristics = new CCharacteristics();
	m_pSttCharacterDrawPng = new CSttCharacterDrawPng();
	m_pSttCharacterDrawPng->SetCharacteristics(m_pCharacteristics);
	//m_pItemState = NULL;

	m_oItemStateList.AllocBuffer(50);
	m_pSttMulticastClientSocket = NULL;
	m_tagAppState = APPSTATE_NULL;
	m_pSttCommCfgPkgWidget = NULL;
	m_oTimerAtsAutoSave.start(30000);
}

//2022-3-23  ��ȡ�Ĺ�����ܺ�������Win��LINUX����ʵ��
void QSttTestCntrFrameBase::InitFrame(const CString &strFrameCfgFile)
{
//	stt_xml_serialize_write_ReplayTest();
	debug_enter_time_long_log();

	if (!IsAutoTest())
	{
	g_oFileMngrTool.OpenConfigFile();
	}
	debug_time_long_log("InitFrame OpenConfigFile", true);

	InitUI();
	debug_time_long_log("InitFrame InitUI", true);

	InitIcon();
	debug_time_long_log("InitFrame InitIcon", true);

#ifdef _USE_SoftKeyBoard_
	InitPinyinLib();
	CreateKeyBoardWidget();
	//QSoftKeyBoard::AttachObj(this); //20240914 suyang �Ż����룬�˴�ע��
	debug_time_long_log("InitFrame QSoftKeyBoard", true);
#endif

	//2022-2-26  lijunqing  ����ļ������ڣ������ʾ��Ϣ��ʱ�򴰿ڻ�û�����ɹ����������
	//g_oSttTestResourceMngr.LoadDefaultIec61850Config(FILENAME_STTIECCONCFIG);
// 
// 	//��Ŀ�б���ͼ
// 	CSttFrame_GbTree *pTree = m_pSttFrameConfig->GetGbTree();
// 	m_pSttGbTreeView = new QSttGuideBookTreeWidget(NULL, pTree, this);
// 	m_pSttGbTreeView->hide();
// 
// 	g_theTestCntrFrame = this;
// 	CalRectArea();
// 
// 	//�����ͼһֱ����
// 	m_pOutputWidget = new QSttOutPutWidget(this);
// 	m_pOutputWidget->hide();
// 
// 	//��Ϣ��ͼһֱ����
// 	InitInfoWidget();
// 	m_pInfoWidget->hide();

	
//	connect(this,SIGNAL(sig_LogStringResult(long,CString)),this,SLOT(slot_LogStringResult(long,CString)),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_OnViewTestLink(bool)),this,SLOT(slot_OnViewTestLink(bool)),Qt::QueuedConnection);//��ͬ�߳�,�ۺ�����Ҫʹ�ö���ģʽ�����߳�ִ��
	connect(this,SIGNAL(sig_OnViewTestStart()),this,SLOT(slot_OnViewTestStart()),Qt::QueuedConnection);
	connect(this,SIGNAL(sig_OnViewTestStop()),this,SLOT(slot_OnViewTestStop()),Qt::QueuedConnection);
	connect(this,SIGNAL(sig_OnUpdateGpsTime(CDataGroup *)),this,SLOT(slot_OnUpdateRtSyncTime(CDataGroup*)),Qt::QueuedConnection);//��ͬ�߳�,�ۺ�����Ҫʹ�ö���ģʽ�����߳�ִ��
	connect(this,SIGNAL(sig_OnUpdateException()),this,SLOT(slot_OnUpdateException()),Qt::QueuedConnection);
	connect(this,SIGNAL(sig_MenuButtonClick(QString)),this,SLOT(slot_MenuButtonClick(QString)),Qt::QueuedConnection);
	connect(this,SIGNAL(sig_UpdateToolButtons()),this,SLOT(slot_UpdateToolButtons()));
	connect(this,SIGNAL(sig_UpdateEnableState(QString)),this,SLOT(on_UpdateEnableState(QString))/*,Qt::BlockingQueuedConnection*/);
	connect(&m_oTimerAtsTest,SIGNAL(timeout()),this,SLOT(slot_Timer()));
	connect(&m_oTimerHtmlViewReturn,SIGNAL(timeout()),this,SLOT(slot_ReturnPrevActiveWidget()));
	connect(&m_oTimerAtsAutoSave,SIGNAL(timeout()),this,SLOT(slot_Timer_AutoSave()));

	connect(this,SIGNAL(sig_OnItemStateChanged(CExBaseObject *)),m_pSttGbTreeView,SLOT(slot_ItemStateChanged(CExBaseObject *)),Qt::QueuedConnection);
	connect(this,SIGNAL(sig_ShowItems_TreeView(CExBaseList *)),m_pSttGbTreeView,SLOT(slot_ShowItems(CExBaseList *)));
	connect(this, SIGNAL(sig_UpdateTestResource()), this, SLOT(slot_UpdateTestResource()),Qt::QueuedConnection);
	connect(this, SIGNAL(sig_UpdateHtmlManuTrigerBtn_Testing()), this, SLOT(slot_UpdateHtmlManuTrigerBtn_Testing()));

	connect(this, SIGNAL(sig_UpdateSysConfig()), this, SLOT(slot_UpdateSysConfig()),Qt::QueuedConnection);
	connect(this, SIGNAL(sig_UpdatePowerGear()), this, SLOT(slot_UpdatePowerGear()),Qt::QueuedConnection);
	connect(this, SIGNAL(sig_CloseMenu()), this, SLOT(slot_CloseMenu()),Qt::QueuedConnection);
	connect(this, SIGNAL(sig_UpdateRptHtml()), this, SLOT(slot_UpdateRptHtml()),Qt::QueuedConnection);
	connect(this, SIGNAL(sig_FillReportImg(QString)), this, SLOT(slot_FillReportImg(QString)),Qt::QueuedConnection);
//	connect(this, SIGNAL(sig_OnItemStateChanged_Frame(CExBaseObject *)), this, SLOT(slot_OnItemStateChanged_Frame(CExBaseObject *)));
	connect(this, SIGNAL(sig_OnInputData(CDataGroup *, CExBaseList *)), this, SLOT(slot_OnInputData(CDataGroup *, CExBaseList *)));
	connect(this,SIGNAL(sig_OnImportDvm(CExBaseList *)),this,SLOT(slot_OnImportDvm(CExBaseList *)));

	connect(this,SIGNAL(sig_SendChMapsConfig()),this,SLOT(slot_SendChMapsConfig()),Qt::QueuedConnection);

	connect(this, SIGNAL(sig_MsgBox(QString,QString)), this, SLOT(slot_MsgBox(QString,QString)),Qt::QueuedConnection);
	connect(this, SIGNAL(sig_UpdateReportSysState(CDataGroup *)),this,SLOT(slot_UpdateReportSysState(CDataGroup*)),Qt::QueuedConnection);//��ͬ�߳�,�ۺ�����Ҫʹ�ö���ģʽ�����߳�ִ��
	debug_time_long_log("InitFram connecte", true);

	m_bInited = false;

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin TestResourceMngr >>");	}

	if (!IsAutoTest())
	{
	g_oSttTestResourceMngr.SetIecConfigFileName(FILENAME_STTIECCONCFIG);//zhouhj 20220316 ��Ϊ���������ļ����ķ�ʽ
	g_oSttSystemConfig.OpenSystemConfig();
	g_oSttTestResourceMngr.LoadDefaultIec61850Config();
	}

	debug_time_long_log("InitFrame SttTestResourceMng", true);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end TestResourceMngr >>");	}

	//2024-9-15 lijunqing �Ż�ϵͳ����������Ч��
	connect(this,SIGNAL(sig_OpenMacroTest(unsigned long)),this,SLOT(slot_OpenMacroTest(unsigned long)),Qt::QueuedConnection);
}

QSttTestCntrFrameBase::~QSttTestCntrFrameBase()
{
#ifdef _PSX_QT_LINUX_
	ReleaseKeyboardWidget();
#endif
	m_oTimerAtsAutoSave.stop();
	CAutoSimpleLock oLock(m_oCriticSection_AutoSave);
#ifdef use_sttdebuglogwidget
	if (g_sttdebuglogwidget == 0)
	{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
	}
#else
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
#endif
	ReleaseConfig();

// 	if (m_pSttTestResource != NULL)
// 	{
// 		delete m_pSttTestResource;
// 		m_pSttTestResource = NULL;
// 	}

	if (m_pPowerDiagramWidget != NULL)
	{
		delete m_pPowerDiagramWidget;
		m_pPowerDiagramWidget = NULL;
	}
	if (m_pVectorWidget != NULL)
	{
		delete m_pVectorWidget;
		m_pVectorWidget = NULL;
	}

	if (m_pStateMonitorWidget != NULL)
	{
		delete m_pStateMonitorWidget;
		m_pStateMonitorWidget = NULL;
	}

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	delete m_pSttReportViewHtml;
    //	m_pSttReportViewHtml = NULL;
    //}

	if (m_pInfoWidget != NULL)
	{
		delete m_pInfoWidget;
		m_pInfoWidget = NULL;
	}

	if (m_pCharLibWidget != NULL)
	{
		delete m_pCharLibWidget;
		m_pCharLibWidget = NULL;
	}	

	if (m_pCharactWidgetForTest != NULL)
	{
		delete m_pCharactWidgetForTest;
		m_pCharactWidgetForTest = NULL;
	}

	if (m_pCharTestPointsGrid != NULL)
	{
		delete m_pCharTestPointsGrid;
		m_pCharTestPointsGrid = NULL;
	}
	
	if(m_pCharacteristics != NULL)
	{
		delete m_pCharacteristics;
		m_pCharacteristics = NULL;
	}

	if(m_pSttCharacterDrawPng != NULL)
	{
		delete m_pSttCharacterDrawPng;
		m_pSttCharacterDrawPng = NULL;
	}

	if (m_pSttIecRecordMainWidget != NULL)
	{
		delete m_pSttIecRecordMainWidget;
		m_pSttIecRecordMainWidget = NULL;
	}


	if(m_pSttCommCfgPkgWidget != NULL)
	{
		delete m_pSttCommCfgPkgWidget;
		m_pSttCommCfgPkgWidget = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//CSttWndAssistInterface
//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
CSttWndAssistInterface* QSttTestCntrFrameBase::ast_FindWnd(const CString &strWndID)
{
	
	return NULL;
}

//����ִ�нӿ�
bool QSttTestCntrFrameBase::ast_ExecCmd(const CString &strCmdID,const CString &strParas)
{
	if (strCmdID == "MenuCmd")
	{
		slot_MenuButtonClick(strParas);
		return true;
	}

	if (strCmdID == Event_ID_IecSelCb)
	{
		//�����Ի���ѡ����ƿ�

		return true;
	}

	if (strCmdID == STT_CMD_TYPE_ATS_StartDetect)
	{
		
		return true;
	}

	return false;
}

bool QSttTestCntrFrameBase::ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID)
{

	return false;
}

bool QSttTestCntrFrameBase::ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile)
{

	return false;
}

//////////////////////////////////////////////////////////////////////////
void QSttTestCntrFrameBase::InitTestResource()
{	
	long nMergeCurrCoef = 1;

	if (g_oSttTestResourceMngr.GetAnalogCurrentMergeCoef(nMergeCurrCoef))
	{
		g_oLocalSysPara.m_fAC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fAC_CurMin *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMin *= nMergeCurrCoef;
	}
}

void QSttTestCntrFrameBase::OnUpdateTestResource(BOOL bCreateChMaps)
{
    if (m_pMacroEditView == NULL)
    {
		if (!bCreateChMaps)//zhouhj 2024.5.22 �ڵ�λ�л�ʱ,���ºϲ������ͨ��ӳ�书��
		{
			g_oSttTestResourceMngr.ValidHardRsChMaps();
		}

        return;
    }

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">> begin OnUpdateTestResource >>"));
	}

	if (bCreateChMaps)
	{
		g_oSttTestResourceMngr.CreateChMaps();//�򿪱���ͨ��ӳ���ļ�
	}

//	initLocalSysPara();
	g_oSttTestResourceMngr.InitLocalSysPara();
	g_oSttTestResourceMngr.ValidHardRsChMaps();//��֤ͨ��ӳ���ļ���Ӳ����Ϣ�Ƿ���Device�д��ڣ�ɾ�������ڵ�Ӳ����Ϣ����������ڣ������Device��Ϣ������ȱʡ
	g_oSttTestResourceMngr.CreateSoftRsCh();
	g_oSttTestResourceMngr.CreateRtDataMngr();
	g_oSttTestResourceMngr.SaveSystemParasFile();
	long nMergeCurrCoef = 1;

	if (g_oSttTestResourceMngr.GetAnalogCurrentMergeCoef(nMergeCurrCoef))
	{
		g_oLocalSysPara.m_fAC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fAC_CurMin *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMin *= nMergeCurrCoef;
	}

	if (g_pStateMonitorWidget)	//dingxy 20250208 ����״̬ͼ
	{
		g_pStateMonitorWidget->UpdateAxisScale();
	}

	//�������˲��Թ����Ҹù����ǵݱ�ʱ������Ҫ��״̬ͼ�������³�ʼ��
	bool bIsOriginal = false;
	bool bIsGradient = false;

	if ((g_pTheSttTestApp->m_pTestMacroUI != NULL) && (m_pMacroEditView!=NULL))//�жϵ�ǰ�Ƿ�����˲��Թ���ģ��,���жϵ�ǰ���Թ���ģ���Ƿ�Ϊ��ҳ
	{
		if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
		{
			m_pMacroEditView->UpdateTestResource(FALSE);//zhouhj20220319 �ڷ���ҳ�������ʱ,����
			UpdateRptHtml();//zhouhj 20220329 ֻ����ԭ������,�ڸ��������Դӳ���,��Ҫ���±����е�ͨ��
			bIsOriginal = true;
			
			if (g_pTheSttTestApp->GetCurrTestMacroUI() != STT_ORG_MACRO_RemoteCtrlTest)//ң�ز��̳�CSttMacroParaEditViewOriginal
			{
			bIsGradient = (strcmp(((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->GetMacroID(), "GradientTest") == 0);
		}
			
		}
		else
		{
			InitBinaryIn_WebUI(m_pTestMacroUI_Paras);
		}
	}

	if (m_pStateMonitorWidget)
	{
		//����ԭ��̬ģ�������ԭ��̬�����ǵݱ�ģ��ʱ�����Խ���״̬ͼ�����³�ʼ��
		if (!bIsOriginal || (bIsOriginal && !bIsGradient))
		{
			m_pStateMonitorWidget->UpdateStateMonitorChs();
		}
	}

	if(m_pVectorWidget)
	{
		//20231109 suyang ���ݲ�ͬģ�� ʸ��ͼ����Ƿ����ӻ���ֵ��ʾ
		CString strCurrUI_ID = GetCurrentUI_ID();
		int nType;

		if(strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowVolTest)
		{
			nType = STT_LowVolDvdt_VECTOR;
		}
		else if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
		{
			nType = STT_LowFreqDfdt_VECTOR;
		}
		else
		{
			nType = STT_COMMON_VECTOR;
		}

		m_pVectorWidget->setPropertyOfParaSet(GetSttTestResource(),nType);
		m_pVectorWidget->updateData();
	}

	if(m_pPowerDiagramWidget)
	{
		m_pPowerDiagramWidget->setPropertyOfParaSet(GetSttTestResource());
		m_pPowerDiagramWidget->initData();
	}

	if (m_pStateMonitorWidget)
	{
// 		CString strCurrUI_ID = GetCurrentUI_ID();
// 		if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
// 		{
// 			m_pStateMonitorWidget->SetPlotDigitMaxMinValue(fre_type);
// 		}
// 		else
// 			m_pStateMonitorWidget->SetPlotDigitMaxMinValue(amplitude_type);

		//chenling 20250117 ���źŵ���״̬ͼ��ֵ���������
		//SetPlotAcDcMaxMinValue(false,0,130,0,30);
		float fUMax = 130,fIMax = 30;
 		if((g_oSystemParas.m_nHasWeek == 1) && (g_oSystemParas.m_nHasAnalog == 0)&& (g_oSystemParas.m_nHasDigital == 0))
 		{
#ifdef _PSX_OS_CENTOS_
			fUMax = 10.000;
#else
			fUMax = 8.300;
#endif
			fIMax = 21.275;
 		}
		SetPlotAcDcMaxMinValue(false,0,fUMax,0,fIMax);
	}

	//ϵͳ����ҳ�棬δ��ѡ�����֡���Ӧ���ء�IEC���á���ť sf 20220317
	if (!g_oSystemParas.HasDigitalInOrOut())
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,false,false);
	}
 	else//20220810 zhouhj
 	{
 		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,true,true);
 	}

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">> end OnUpdateTestResource >>"));
	}

	UpdateToolButtons();

	if (m_pMacroEditView)
	{
		m_pMacroEditView->UpdatePrimParaSetUI();
	}

}

// void QSttTestCntrFrameBase::initLocalSysPara()
// {
// 	g_oSttTestResourceMngr.InitLocalSysPara();
// }

void QSttTestCntrFrameBase::UpdateReportHead( CDataGroup *pSttReport )
{
    //if (m_pSttReportViewHtml)
    //{
    //	m_pSttReportViewHtml->UpdateReportHead(pSttReport);
    //}
}

void QSttTestCntrFrameBase::GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath)
{
	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();
	CString strMacroID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;

	if(g_pTheSttTestApp->IsTestMacro_CurrVolChAsItem())
	{
		nLen = m_pMacroEditView->GetMacroItemsXml(strMacroID, ppszReport);
	}
	else
	{
		nLen = m_pTestCtrlCntrBase->GetMacroItemsXml(strMacroID, ppszReport,strParentPath);
	}
}

void QSttTestCntrFrameBase::UpdateCustomReport()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	CString strMacroID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;

	if(strMacroID == STT_ORG_MACRO_MUAccuracyTest
		|| strMacroID == STT_ORG_MACRO_MUFirstCycleTest
		|| strMacroID == STT_ORG_MACRO_MUTimingAccurTest
		|| strMacroID == STT_ORG_MACRO_MUPunctAccurTest)
	{
		CExBaseObject *pSel = m_pSttGbTreeView->GetCurrSelectGbItem();
		AddMacroTestReport(g_pTheSttTestApp->m_pTestMacroUI, pSel, "", "");
	}
}

void QSttTestCntrFrameBase::UpdateCharactWidgetForTest(long nPtIndex)
{
	//yzj 2023.10.19
	if(nPtIndex < 0)
	{
		return;
	}
	else if(nPtIndex == 0)
	{
		//�ӵ�0���㿪ʼȫ�����
		if (m_pCharactWidgetForTest != NULL)
		{
			m_pCharactWidgetForTest->slot_UpdateDrawCharacters();
		}

		if (m_pCharTestPointsGrid != NULL)
		{
			m_pCharTestPointsGrid->ClearSearchPoints();
		}

		if(m_pSttCharacterDrawPng)
		{
			m_pSttCharacterDrawPng->ClearSearchPoints_png();
		}

		m_strItemStateChanged_SearchLineString = _T("");
	}
	else
	{
		if (m_pCharactWidgetForTest != NULL)
		{
			m_pCharactWidgetForTest->ClearSearchPointsFrom(nPtIndex);
		}

		if (m_pCharTestPointsGrid != NULL)
		{
			m_pCharTestPointsGrid->ClearSearchPointsFrom(nPtIndex);
		}

		if(m_pSttCharacterDrawPng)
		{
			m_pSttCharacterDrawPng->ClearSearchPointsFrom_png(nPtIndex);
		}
	}
}

void QSttTestCntrFrameBase::UpdateCharactWidgetForCurTest(long nPtIndex)
{
	if (m_pCharactWidgetForTest != NULL)
	{
		m_pCharactWidgetForTest->ClearSearchPoint(nPtIndex);
	}

	if (m_pCharTestPointsGrid != NULL)
	{
		m_pCharTestPointsGrid->ClearSearchPoint(nPtIndex);
	}

	if(m_pSttCharacterDrawPng)
	{
		m_pSttCharacterDrawPng->ClearSearchPoints_png(nPtIndex);
	}
}

void QSttTestCntrFrameBase::UpdateResultWidget(CSttReport *pReport,const CString &strItemName,const CString &strMacroID)
{
	if (pReport == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
	//windows�汾���µ�widgetָ��
	if (m_pResultWidget == NULL)
	{
		return;
	}
#endif

	CDvmValues *pValues = (CDvmValues*)pReport->FindByClassID(DTMCLASSID_CDVMVALUES);

	if (pValues == NULL)
	{
		return;
	}

	/*
	1���ڲ��Խ�����϶���(m_oTestMacroResults)��δ���ҵ��κν����Ϣ�ģ��˱����������壬����չʾ��
	2���ڲ��Խ���в��ҵ���������������δ��������Ϊ����λ����ֵΪ��������ʾ�ܵ�δ���������
	3���ڲ��Խ���в��ҵ��ж����������Ϣ��ֱ����ʾ���������
	*/

	CDvmData *pCurrData = NULL;
	CDvmValue *pResultValue = NULL;
	CString strResultsString = _T("$");
	strResultsString += strItemName;
	strResultsString += "[";
	double dValue = 0;
	BOOL bHasResult = FALSE,bHasActValue = FALSE;
	CString strUint;


	CSttItems* pItems = (CSttItems*)pValues->GetAncestor(STTGBXMLCLASSID_CSTTITEMS);

	if (pItems == NULL)
	{
		return;
	}

	strResultsString = pItems->m_strName + strResultsString;

	if ((strMacroID == STT_MACRO_ID_GradientTest)||(strMacroID == STT_MACRO_ID_GradientMaxAngleTest))
	{
		//�ݱ���ԵĽ�����Ӧ�Ĺ��ϲ������,�˴���������ݱ���Խ��
		bHasResult = GetResultStringGradientTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	} //
	else if (strMacroID == STT_MACRO_ID_LineVolGradientTest)
	{
		//�ݱ���ԵĽ�����Ӧ�Ĺ��ϲ������,�˴���������ݱ���Խ��
		bHasResult = GetResultStringLineVolGradientTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	} //
	else if (strMacroID == STT_MACRO_ID_SequenceGradientTest)
	{
		//�ݱ���ԵĽ�����Ӧ�Ĺ��ϲ������,�˴���������ݱ���Խ��
		bHasResult = GetResultStringSequenceGradientTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	} //
	else if (strMacroID == STT_MACRO_ID_FaultGradientTest)  //2024-01-03 yuanting  ���ϵݱ����
	{

		bHasResult = GetResultStringFaultGradientTest(pValues, bHasActValue, strResultsString, m_oTestMacroResults);
	} //
	else if(strMacroID == STT_ORG_MACRO_SoeTest)
	{

	}
	else if (strMacroID == STT_MACRO_ID_ULockOverCurrent)
	{
		//��ѹ��������ʱ,����ʵ�ʲ���������ʾ���Խ��
		bHasResult = GetResultStringULockOverCurrent(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	else if (strMacroID == STT_MACRO_ID_PowerDirection)
	{
		//���ʷ������ʱ,����ʵ�ʲ���������ʾ���Խ��
		bHasResult = GetResultStringPowerDirection(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	//�ϲ���Ԫ��ʱ��ʱ���Ե�,����Ҫ�жϽ��
	else if ((strMacroID == STT_ORG_MACRO_MUTimingAccurTest)||(strMacroID == STT_ORG_MACRO_MUPunctAccurTest))
	{
	}
	//yzj 2023.12.5 ��ѹ����ֵ���ֽ������Ҫ��ʾ
	else if (strMacroID == STT_MACRO_ID_VoltageActValue)
	{
		bHasResult = GetResultStringVoltageActValue(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	else if (strMacroID == STT_MACRO_ID_CurrentActValue)
	{
		bHasResult = GetResultStringCurrentActValue(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	//yzj 2023.12.26 �����迹�߽�
	else if (strMacroID == "DistanceSearch")
	{
		bHasResult = GetResultStringDistanceSearchTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	//dingxy 20240510 ״̬���ж���ֵ������
	else if (strMacroID == STT_MACRO_ID_StateTest)
	{
		bHasResult = GetResultStringStateTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	else if(strMacroID == STT_MACRO_ID_PsuSwing)
	{
		bHasResult = GetResultStringSwingTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	//xueyangfan 20241219 г�� ֻ���ж���ʱ�����ʱ�����Ա���������ֵһ����Ӧ����ʾδ��������Ϊ��ʾ����
	else if (strMacroID == STT_MACRO_ID_HarmTest)
	{
		bHasResult = GetResultStringHarmTest(pValues,bHasActValue,strResultsString,m_oTestMacroResults);
	}
	else
	{
		POS pos = m_oTestMacroResults.GetHeadPosition();

		while(pos)
		{
			pCurrData = (CDvmData*)m_oTestMacroResults.GetNext(pos);
			pResultValue = (CDvmValue*)pValues->FindByID(pCurrData->m_strID);

			if (pResultValue !=NULL)
			{
				bHasResult = TRUE;

				if (pResultValue->m_strValue != /*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact)
				{
					if (pResultValue->m_strValue == "δ����")
					{
						pResultValue->m_strValue = /*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact;
					}
					else
					{
						dValue = CString_To_double(pResultValue->m_strValue);

						if ((pCurrData->m_strUnit != "��")&&(dValue<= 0.00001))
						{
							pResultValue->m_strValue = /*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact;
						}
						else
						{
							bHasActValue = TRUE;
							strResultsString += pCurrData->m_strName;
							strResultsString += ":";
							long nPrecision = 3;

							if ((dValue>0.000f)&&(dValue<0.001f))
							{
								if (dValue<0.0001f)
								{
									nPrecision = 5;
								}
								else
								{
									nPrecision = 4;
								}
							}

							//strFormat.Format(_T("%%.%dlf"),nPrecision);
							pResultValue->m_strValue = QString::number(dValue,'f',nPrecision);//.Format("%.5lf",dValue);
							strResultsString += pResultValue->m_strValue;
							if ((pCurrData->m_strID == _T("TripValue")) || (pCurrData->m_strID == _T("ActValue")) || (pCurrData->m_strID == _T("ReturnValue")))
							{
								strUint = GetMacroTestResultUnit();
								strResultsString += strUint;
							}
							else
							{
							strResultsString += pCurrData->m_strUnit;
							}

							strResultsString += ";";
						}
					}
					
				}
			}
		}
	}

	if (bHasResult)
	{
		if (!bHasActValue)
		{
			strResultsString += /*_T("δ����")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact;
		}

		strResultsString += "].";
		CLogPrint::LogString(XLOGLEVEL_RESULT,strResultsString);
	}
}

CString QSttTestCntrFrameBase::GetMacroTestResultUnit()
{
	if ((g_pTheSttTestApp->m_pTestMacroUI == NULL)||(m_pMacroEditView == NULL))
	{
		return _T("");
	}

	CString strUnit;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		strUnit = m_pMacroEditView->GetMacroTestResultUnit();
	}
	return strUnit;
}

bool need_connect_app(CString &strCurrDialogID)
{

	if (strCurrDialogID == STT_CNTR_CMD_PpIotEngineClient || strCurrDialogID == STT_CNTR_CMD_CommConfig
		|| strCurrDialogID == STT_CNTR_CMD_PpXmlFileMngr || strCurrDialogID == STT_CNTR_CMD_DvmFileMngr
		|| strCurrDialogID == STT_CNTR_CMD_FileMngr || strCurrDialogID == STT_CNTR_CMD_LangSetting
		|| strCurrDialogID == STT_CNTR_CMD_OutputDebug )
	{
		return false;
	}
	
	return true;
}

void QSttTestCntrFrameBase::OpenDialog(const CString &strDialogID)
{
    CString strCurrDialogID;
    strCurrDialogID = strDialogID;
 //   CXMessageBox::information(NULL,"001","000000" );
	bool bRet = need_connect_app(strCurrDialogID);

	if (!g_oSttTestResourceMngr.HasLoadDevice())
	{
		g_oSttTestResourceMngr.SelectDeviceFromLocalDB();
	}


#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(this); //dingxy 20241008 ����̽��ڶ��δ�iec���ñ��������޸�
#endif
	//��������ʱ,��Ҫ��֤��ǰ�����㹻����,�Ȼ�ȡ��ǰ������Ϣ  20230106 zhouhj
    if ((strCurrDialogID == STT_CNTR_CMD_Liveupdate)||(strCurrDialogID == STT_CNTR_CMD_ULiveupdate)||(strCurrDialogID == STT_CNTR_CMD_BinConfig))
	{
		OpenDialogModal(strCurrDialogID, bRet);
	}
	else if (strCurrDialogID == STT_CNTR_CMD_PpIotEngineClient || strCurrDialogID == STT_CNTR_CMD_CommConfig
		|| strCurrDialogID == STT_CNTR_CMD_PkgMonitor || strCurrDialogID == STT_CNTR_CMD_PpXmlFileMngr
		|| strCurrDialogID == STT_CNTR_CMD_DvmFileMngr || strCurrDialogID == STT_CNTR_CMD_OutputPower
		|| strCurrDialogID == STT_CNTR_CMD_HardConfig || strCurrDialogID == STT_CNTR_CMD_VersionInfo
		|| strCurrDialogID == STT_CNTR_CMD_FileMngr || strCurrDialogID == STT_CNTR_CMD_LumPowerView
		|| strCurrDialogID == STT_CNTR_CMD_LangSetting || strCurrDialogID == STT_CNTR_CMD_IecCapDialog
		|| strCurrDialogID == STT_CNTR_CMD_OutputDebug || strCurrDialogID == STT_CNTR_CMD_LiveupdateDevice
		|| strCurrDialogID == STT_CNTR_CMD_AuxDCOutput || strCurrDialogID == STT_CNTR_CMD_SystemParas
		|| strCurrDialogID == STT_CNTR_CMD_IECConfig|| strCurrDialogID == STT_CNTR_CMD_ChRsMaps)
	{
		OpenDialogModeless(strCurrDialogID, bRet);
	}
#ifdef _PSX_QT_LINUX_	 //Windows�رջᴥ��closeEvent,�����·�����CloseTest
	if (m_pTestCtrlCntrBase != 0)
	{
		m_pTestCtrlCntrBase->CloseTest(STT_CMD_Send_Async);
	}
#endif
//	g_pTheSttTestApp->ExitSttTestApp();
	this->close();
}

void QSttTestCntrFrameBase::OpenDialogModal(const CString &strDialogID, bool bNeedConnect)
{
	show();//������������������ʱ,��ʾ����,������������ڽ�����ʾ��ӡ��Ϣ
	if (bNeedConnect)
	{
		OnCmd_ConnectApp();//���ӷ����
	}
		CTickCount32 oTickCount;
		long nCurrIndex = 0;

		while((m_oDataBtnsMngr.GetBatCapValue()<0)&&(nCurrIndex<500))//�ȴ���ȡ��ǰ��ص���,,���ȴ�5s
		{
			oTickCount.DoEvents(10);
			nCurrIndex++;
		}
		OnCmd_DebugOutPutWidget();

// 	if (!g_oSttTestResourceMngr.HasLoadDevice())
// 	{
// 		g_oSttTestResourceMngr.SelectDeviceFromLocalDB();
// 	}

	if (strDialogID == STT_CNTR_CMD_Liveupdate)
	{
		OnCmd_Liveupdate();
	}
	else if (strDialogID == STT_CNTR_CMD_ULiveupdate)
	{
		OnCmd_ULiveupdate();
	}
	else if (strDialogID == STT_CNTR_CMD_BinConfig)
	{
		OnCmd_BinConfig();
	}
}

void QSttTestCntrFrameBase::OpenDialogModeless(const CString &strDialogID, bool bNeedConnect)
{
	CTickCount32 oTickCount;

	if (bNeedConnect)
	{
		//20250325 suyang ȷ�������Դ��ȫ����ʼ����ɣ���ֹ����ʱ��ȡӲ���źź����ͻ����Ҫ�����߳�δ������߳̿�ʼ�����̵߳ȴ�����
		
		oTickCount.DoEvents(100);

		OnCmd_ConnectApp();//���ӷ����
	}
// 	if (!g_oSttTestResourceMngr.HasLoadDevice())
// 	{
// 		g_oSttTestResourceMngr.SelectDeviceFromLocalDB();
// 	}



	else if (strDialogID == STT_CNTR_CMD_HardConfig || strDialogID == STT_CNTR_CMD_OutputPower)
	{
		
		long nCurrIndex = 0;

		while((g_oLocalSysPara.m_nRTData_Num <= 0) && (nCurrIndex<200))//dingxy 20240614 Ӳ�����ý����״εȴ���ȡ��ǰ���ȵ�λ,���ȴ�2s
		{
			oTickCount.DoEvents(10);
			nCurrIndex++;
		}
	}

	if (strDialogID == STT_CNTR_CMD_PpIotEngineClient)
	{
		OnCmd_PpIotEngineClientDlg();
	}
	else if (strDialogID == STT_CNTR_CMD_CommConfig)
	{
		OnCmd_CommConfiguration();
	}
	else if (strDialogID == STT_CNTR_CMD_PkgMonitor)
	{
		/*OnCmd_PkgMonitor();*/
		OnCmd_PkgMonitorDlg();
	}
	else if (strDialogID == STT_CNTR_CMD_PpXmlFileMngr)
	{
		OnCmd_PpXmlFileMngr();
	}
	else if (strDialogID == STT_CNTR_CMD_DvmFileMngr)
	{
		OnCmd_DvmFileMngr();
	}

	else if (strDialogID == STT_CNTR_CMD_OutputPower)
	{
		OnCmd_OutputPower();
	}
	else if (strDialogID == STT_CNTR_CMD_HardConfig)
	{
		OnCmd_HardConfig();
	}
	else if (strDialogID == STT_CNTR_CMD_VersionInfo)
	{
		OnCmd_VersionInfo();
	}
	else if (strDialogID == STT_CNTR_CMD_FileMngr)
	{
		OnCmd_FileMngr();
	}
	else if (strDialogID == STT_CNTR_CMD_LumPowerView)
	{
		OnCmd_LumPowerView();
	}
	else if (strDialogID == STT_CNTR_CMD_LangSetting)
	{
		OnCmd_LangSettingView();
	}
	else if (strDialogID == STT_CNTR_CMD_IecCapDialog)
	{
		OnCmd_IecCapDialog();
	}
	else if(strDialogID == STT_CNTR_CMD_OutputDebug)
	{
	     OnCmd_OutputDebug();
	}
	else if(strDialogID == STT_CNTR_CMD_LiveupdateDevice)
	{
		OnCmd_LiveupdateDevice();
	}
	else if (strDialogID == STT_CNTR_CMD_SystemParas)  // 2024-12-05 xueyangfan ���ʰ���ֲ
	{
		OnCmd_SystemParas();
	}
	else if (strDialogID == STT_CNTR_CMD_AuxDCOutput)
	{
		OnCmd_AuxDCOutput();
	}
	else if (strDialogID == STT_CNTR_CMD_IECConfig)
	{
		OnCmd_IECConfig();
	}
	else if (strDialogID == STT_CNTR_CMD_ChRsMaps)
	{
		if (g_pTheSttTestApp->m_pTestCtrlCntr)
		{
			g_pTheSttTestApp->m_pTestCtrlCntr->InitDefaultHdRs();//20250110  suyang dialog��ͨ��ӳ����Ҫ��ʼ����Դ
		}

		OnCmd_ChRsMaps();
	}
}


void QSttTestCntrFrameBase::slot_UpdateRptHtml()
{
#ifndef SttTestCntrThread_H
	UpdateRptHtml();
#else
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("slot_UpdateRptHtml[+++]."));
	g_theSttTestCntrThread->PostThreadMessage(12, 0, 0);
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("slot_UpdateRptHtml[---]."));
#endif
	
}

void QSttTestCntrFrameBase::UpdateRptHtml()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	char *strReport = NULL;
	CString strMacroID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
	long nLen = 0;
	
	GetMacroItemsXml(strMacroID,&strReport, nLen,_T(""));

	if (nLen > 0)
	{
		//2022-4-6  lijunqing
        //if (m_pSttReportViewHtml)
        //{
        //	m_pSttReportViewHtml->AddUpdateCmd(g_pTheSttTestApp->m_pTestMacroUI, "", strMacroID, strReport);
        //}
	}
}

long QSttTestCntrFrameBase::OnUpdateSyncTime(CDataGroup *pRtSyncTime)
//GpsTime( long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
//											long nPowerAC, long nBatCap, long nUSB)
{
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("OnUpdateSyncTime"));
	emit sig_OnUpdateGpsTime(pRtSyncTime);
	return 0;
}

long QSttTestCntrFrameBase::OnUpdateException()
{
	emit sig_OnUpdateException();
	return 0;
}

void QSttTestCntrFrameBase::slot_OnUpdateException()
{
	UpdateToolButtons_Light();
}

long QSttTestCntrFrameBase::OnItemStateChanged(CExBaseObject *pItem)
{
	//emit sig_OnItemStateChanged_Frame(pItem);
	//m_pItemState = pItem;
	CAutoSimpleLock oLock(m_oCriticSection_ItemStateList);
	CSttItemStateObject* pObj = (CSttItemStateObject*)pItem;
	m_oItemStateList.Add(pItem);
	return 0;
}

void QSttTestCntrFrameBase::EndBinStateOnStarting()
{
	for (int i=0;i<g_nBinCount/*g_oLocalSysPara.m_nCHBinInNum*/;i++)
		m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinIn[i] = 0;

	for (int i=0;i<g_nBinExCount;i++)
		m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinInEx[i] = 0;

	for (int i=0;i<g_nBoutCount/*g_oLocalSysPara.m_nCHBinOutNum*/;i++)
		m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOut[i] = 0;

	for (int i=0;i<g_nBoutExCount;i++)
		m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOutEx[i] = 0;
}

long QSttTestCntrFrameBase::OnTestFinished()
{
	if (m_bHasClosedUI)//����رհ�ť��,���ٸ��´˴�
	{
		return 0;
	}

	//2022-12-02  lijunqing
	assist_event(Event_ID_OnTestFinished, NULL);

	EndBinStateOnStarting();
	emit sig_UpdateToolButtons();
	UpdateCmdButtonsState(STT_TEST_STATE_TEST_FINISHED);	
	emit sig_OnViewTestStop();   //��ʱ��Stoped������Finished���߼�  shaolei
	UpdateCustomReport();
	return 0;
}

long QSttTestCntrFrameBase::OnTestStarted()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("OnTestStarted[++++]."));
	//2022-12-02  lijunqing
	assist_event(Event_ID_OnTestStarted, NULL);

//	UpdateCmdButtonsState(STT_TEST_STATE_TESTTING);
	emit sig_OnViewTestStart();
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("OnTestStarted[----."));
	return 0;
}

long QSttTestCntrFrameBase::OnTestStoped()
{
	if (m_bHasClosedUI)//����رհ�ť��,���ٸ��´˴�
	{
		return 0;
	}

	EndBinStateOnStarting();
	emit sig_UpdateToolButtons();
	
	UpdateCmdButtonsState(STT_TEST_STATE_TEST_STOPED);	
	emit sig_OnViewTestStop();
	UpdateCustomReport();
	assist_event(Event_ID_OnTestFinished, NULL);
	return 0;
}

void QSttTestCntrFrameBase::slot_UpdateToolButtons()
{
	//dingxy 20250321 ��ֹͣ���ԡ���������ʱ���ѵƵ�״̬�ָ�ΪĬ��ֵ
	CExBaseList *pTestGlobalParas = g_pTheSttTestApp->m_pTestCtrlCntr->GetTestGlobalParas();
	if (pTestGlobalParas != NULL)
	{
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_IBreak, "0");
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_UShort, "0");
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_OverHeat, "0");
	}
	
	UpdateToolButtons();
}

void QSttTestCntrFrameBase::slot_OnViewTestStart()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("slot_OnViewTestStart[++++]."));
	EnableStartStopButton(TRUE);
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[�������]slot_OnViewTestStart(%d)"),(int)m_bInited);

	if(m_bInited)
	{
		//zhouhj 2023.11.2 ��ÿ�ο�ʼ���Ժ�,�������µ����ݸ���,����ʸ��ͼ�ȶ�ʱ��
// 		if ((m_pMacroEditView == NULL)||(g_pTheSttTestApp->m_pTestMacroUI == NULL))
// 		{
// 			return;
// 		}
// 
// 		if(g_pTheSttTestApp->m_pTestMacroUI->m_strID == "SystemConfig")
// 		{
// 			//ϵͳ���������ǵ���������û������ui-file���ᱻ�϶�Ϊԭ��̬ģ���ǿת���ʹ���
// 			return;
// 		}
// 
// 		if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
// 		{
// 			((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->OnViewTestStart();
// 		}
// 		//yzj 2022-2-20 ����ԭ��̬����������ҳ��ͼ��ˢ��
// 		else if(g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
// 		{
// 			QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView;
// 			pSttMacroParaEditViewHtml->OnViewTestStart();
// 		}

		return;
	}

	m_bInited = true;

	CDataGroup dataGroup;
	dataGroup.AddNewData("Run","1");
	m_oDataBtnsMngr.UpdataDataButtons(&dataGroup);

	m_oTimerAtsTest.start(100);
	m_bIsUpdateStateTestFirstReportColor = FALSE;

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{//Winģʽ�»����Զ�����ģʽ�£�û�й��ܽ���
		return;
	}

#ifndef _PSX_QT_LINUX_
	if(g_pTheSttTestApp->m_pTestMacroUI->m_strID == "SystemConfig")
	{
		//win��ϵͳ���������ǵ���������û������ui-file���ᱻ�϶�Ϊԭ��̬ģ���ǿת���ʹ���
		return;
	}
#endif

	if (m_pMacroEditView == NULL)
	{
		return;
	}

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->OnViewTestStart();
	}
	//yzj 2022-2-20 ����ԭ��̬����������ҳ��ͼ��ˢ��
	else if(g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView;
        //pSttMacroParaEditViewHtml->OnViewTestStart();
        //pSttMacroParaEditViewHtml->setEnabled(false);
	}

	//20230827  suyang ���Կ�ʼ����ͼ���ɱ༭
	if (m_pCharLibWidget != NULL)
	{
		m_pCharLibWidget->setEnabled(false);
	}

	//��ջ���ı�������������png
// 	if(m_pSttCharacterDrawPng)  //zhouhj 2023.8.28 �ڶ�Ӧ���InitCharDrawTest�����н������
// 	{
// 		m_pSttCharacterDrawPng->ClearSearchPoints();
// 		m_pSttCharacterDrawPng->ClearPngCache();
// 	}

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("slot_OnViewTestStart[----]."));
}

void QSttTestCntrFrameBase::slot_OnViewTestStop()
{
	EnableStartStopButton(TRUE);
	m_bInited = false;
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[�������]slot_OnViewTestStop."));

	CDataGroup dataGroup;
	dataGroup.AddNewData("Run","0");
	m_oDataBtnsMngr.UpdataDataButtons(&dataGroup);
	m_oTimerAtsTest.stop();
	//yzj 2022-2-26 ��ӡ�رղ���ʱ��δ��ӡ��ɵ���Ϣ
	PrintEventInfo();
	//dingxy 20240704 �����ʱ����ɱ�������Ǳ���״̬û�и��£����±���״̬
	if(m_oItemStateList.CanRead())
	{
		CExBaseObject *pObj = m_oItemStateList.Read();
		CSttItemStateObject* pObject = (CSttItemStateObject*)pObj;
		slot_OnItemStateChanged_Frame(pObj);
		//			emit sig_OnItemStateChanged_Frame(&pObj);
	}
	//zhouhj 2023.11.7 ���²��Խ���ʱ��
    //if (m_pSttReportViewHtml)
    //{
    //	m_pSttReportViewHtml->UpdateReportHead_StartEndTestTime(FALSE,TRUE);
    //}

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_pMacroEditView == NULL)
	{
		return;
	}

// 	CString strTestMacroUI_id = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
// 
// 	if (strTestMacroUI_id == STT_MACRO_ID_ChMapsConfig
// 		|| strTestMacroUI_id == STT_MACRO_ID_Iec61850Config
// 		|| strTestMacroUI_id == STT_MACRO_ID_SystemConfig)
// 	{
// 		return;
// 	}

	if (m_pMacroEditView->GetMacroEditViewType() == MACRO_EDIT_VIEW_TYPE_ORIGINAL)
	{
		((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->OnViewTestStop();
	}
	else if (m_pMacroEditView->GetMacroEditViewType() == MACRO_EDIT_VIEW_TYPE_HTML)
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml *)m_pMacroEditView;
        //pSttMacroParaEditViewHtml->OnViewTestStop();
        //pSttMacroParaEditViewHtml->setEnabled(true);
	}

	//20230827  suyang ���Խ�������ͼ�ָ��༭
	if (m_pCharLibWidget != NULL)
	{
		m_pCharLibWidget->setEnabled(true);
	}
// 	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
// 	{
// 		((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->OnViewTestStop();
// 	}
// 	else if(g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
// 	{
// 		QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml *)m_pMacroEditView;
// 		pSttMacroParaEditViewHtml->OnViewTestStop();
// 		pSttMacroParaEditViewHtml->setEnabled(true);
// 	}
}

void QSttTestCntrFrameBase::slot_OnViewTestLink(bool b)
{
	if(!g_pTheSttTestApp->m_pTestMacroUI)
	{
		return;
	}

	if(!b)
	{
		m_oTimerAtsTest.stop();
		emit sig_OnUpdateGpsTime(NULL);//0,0,0,-1,-1,-1,-1,-1,-1);//�Ͽ����Ӻ�,����ʱ״̬��Ϊδ��ʱ
	}

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->OnViewTestLink(b);
	}
	else if(g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
        //((QSttMacroParaEditViewHtml*)m_pMacroEditView)->OnViewTestLink(b);
	}
}

long QSttTestCntrFrameBase::OnTestCreated()
{
	return 0;
}

void QSttTestCntrFrameBase::OnReport(CExBaseObject *pItem) 
{
	
}

void QSttTestCntrFrameBase::OnReport_ReadDevice(CDataGroup *pDeviceGroup)
{
	if (pDeviceGroup == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("OnReport_ReadDevice������pDeviceGroupΪ��."));
		return;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("OnReport_ReadDevice������ʼִ��."));
	CSttAdjDevice oReadDevice;
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	oReadDevice.AttatchAdjRef(pDeviceGroup);
	oReadDevice.GetAttrs();
	pCurDevice->GetAttrs();
	CString strSysVersion_Read,strSysVersion_Curr;
	strSysVersion_Read = _T("");
	strSysVersion_Curr = _T("");
	pDeviceGroup->GetDataValue(_T("SysVersion"), strSysVersion_Read);

	if (pCurDevice->m_pSttAdjRef == NULL)
	{
		pCurDevice->m_pSttAdjRef = new CDataGroup();
		pCurDevice->m_pSttAdjRef->SetParent(pCurDevice);
	}

	pDeviceGroup->GetDataValue(_T("SysVersion"), strSysVersion_Curr);
	pCurDevice->m_pSttAdjRef->DeleteAll();
	pDeviceGroup->Copy(pCurDevice->m_pSttAdjRef);

	//����ͺŻ���װ��SN��ƥ�䣬����Ҫ���¶�ȡDevice��Ϣ
	if ((oReadDevice.m_strModel != pCurDevice->m_strModel)||(oReadDevice.m_strSN != pCurDevice->m_strSN)
		||((strSysVersion_Read.GetLength()>0)&&(strSysVersion_Read != strSysVersion_Curr))
		||(g_oSttSystemConfig.GetLockMaps() == 0))//wangtao 20240507 �˴���������ӳ���ж�
		//���ϵͳ�汾�Ÿ���,����½��������ʾ,ֻ���ڲ�����������Ż����
	{
		pCurDevice->GetAttrs();
		pCurDevice->SortModules();
		pCurDevice->AddMaxVolCurrValue_VolCurrModule();
		g_oSttTestResourceMngr.SetCurSelDevice(pCurDevice->m_strModel,pCurDevice->m_strSN);
		g_oSttTestResourceMngr.SaveCurDeviceFile();
		g_oSttTestResourceMngr.GetAllModuleTags();

		CString strMergeCurTerminal;
		CDataGroup* pAttrGroup = (CDataGroup *)pCurDevice->GetDeviceAttrs();
		if (pAttrGroup)
		{
			strMergeCurTerminal.Format(_T("%d"), oReadDevice.m_nMergeCurTerminal);
			pAttrGroup->SetDataValue(STT_ADJ_ID_MergeCurTerminal, strMergeCurTerminal);
		}
		

        if (g_oSttSystemConfig.GetLockMaps() == 0)
        {
            CSttChMaps oSttChMaps;
			oSttChMaps.DeleteAll();
			g_oSttTestResourceMngr.m_oChMaps.Copy(&oSttChMaps);
            
			if (!g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&oSttChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_MissingDefaultMappings.GetString()); //ȱ��Ӳ����Դ�ļ�,�޷�����ȱʡͨ��ӳ��
				return;
			}
            oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);
			g_oSttTestResourceMngr.SaveCurChMapsFile();
        }

		m_bIsRtDataUpdateChMaps_System = TRUE;
		emit sig_UpdateTestResource();//�����źŸ��������Դ
	}
	else//��Ҫ����ȡ������ģ��ĵ�����λ����Ϣ���µ�ϵͳ������ȥ?????????????��װ���ͺż������ͬ�������,����������ˢ�½���
	{
		pCurDevice->GetAttrs();
		pCurDevice->SortModules();
		pCurDevice->AddMaxVolCurrValue_VolCurrModule();
		g_oSttTestResourceMngr.InitLocalSysPara();//��ϵͳ�����Ƚ������³�ʼ��,����λ����Ϣ����
		g_oSttTestResourceMngr.SaveCurDeviceFile();
		CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

		if (strIDMacroUI == STT_ORG_MACRO_ReplayTest)//���ϻط�ģ��,��Ҫ���²�����Դ
		{
			emit sig_UpdateTestResource();//�����źŸ��������Դ
		}


	if ((g_oSystemParas.m_nHasAnalog == 1)&&(g_oSystemParas.m_nHasDigital == 0))//ֻ���ڴ�ģ����������Ҫ�ж�С�ź�
	{
		//��-1 ��֧�ֺϲ������0 ���ϲ������ 1  �ϲ�Ϊ1��ͨ�������3 �ϲ�Ϊ3��ͨ�������
		if ((oReadDevice.m_nMergeCurTerminal!= 1)&&(oReadDevice.m_nMergeCurTerminal!= 3))
		{
// 			if ((pCurDevice->m_nMergeCurTerminal == 0)&&(pCurDevice->m_nMergeCurTerminal == -1))
			{
				CSttChMaps oSttChMaps;
				oSttChMaps.DeleteAll();
				g_oSttTestResourceMngr.m_oChMaps.Copy(&oSttChMaps);

				if (!g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&oSttChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_MissingDefaultMappings.GetString()); //ȱ��Ӳ����Դ�ļ�,�޷�����ȱʡͨ��ӳ��
					return;
				}
				oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);
				g_oSttTestResourceMngr.SaveCurChMapsFile();
				
				if (g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nMergeCurTerminal != oReadDevice.m_nMergeCurTerminal)
				{
					g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nMergeCurTerminal = oReadDevice.m_nMergeCurTerminal;
				}
				g_oSttTestResourceMngr.SaveSystemParasFile();
				m_bIsRtDataUpdateChMaps_System = TRUE;
					//emit sig_UpdateTestResource();//�����źŸ��������Դ

			}
		}
	}


	}

	


	oReadDevice.AttatchAdjRef(NULL);
}

void QSttTestCntrFrameBase::OnReport_ReadSystemState(const CString &strMacroID, CDataGroup *pParas)
{
	//�̷߳����źţ��������д������ݣ����⿨��
	CDataGroup* pParasTemp = (CDataGroup*)pParas->Clone();
 	emit sig_UpdateReportSysState(pParasTemp);
}

void QSttTestCntrFrameBase::slot_UpdateReportSysState(CDataGroup* pSystemState)
{
	if(m_bUpdateOutputPowerFromRealTime)//�����������
	{
		OnUpdateRtCurrModules(pSystemState);//dingxy 20250320 RTDATA��CurrModules�ڵ�Ǩ�Ƶ�GetSystemState��
		emit sig_UpdateModulesGearSwitchInfo();
	}
}


void QSttTestCntrFrameBase::slot_UpdateTestResource()
{
	OnUpdateTestResource(TRUE);
	//����ͨ��ӳ��
// 	if (m_bIsRtDataUpdateChMaps_System)
// 	{
// 		if (IsTestStarted())
// 		{
// 			return;
// 		}
//  		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[����ͨ��ӳ��-------Cmd_SendChMapsConfig();"));
// 		Cmd_SendChMapsConfig();
// 		m_bIsRtDataUpdateChMaps_System = FALSE;
// 	}
}

void QSttTestCntrFrameBase::OnAtsGenerate()
{
	if(!m_pMacroEditView)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("��ǰ������Ϊ��.")*/g_sLangTxt_Gradient_EmptyCurTI.GetString()); //lcq
		CSttGuideBook *pSttGuideBook= (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
		emit sig_ShowItems_TreeView((CExBaseList *)pSttGuideBook);//ģ��ˢ�£�Ӧ������Ŀ�б��������
		return;
	}
	//20230213 zhangyq
	CSttGuideBook *pSttGuideBook= (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	m_pMacroEditView->ProcessGbAfterGenTemplate(pSttGuideBook);
	emit sig_ShowItems_TreeView((CExBaseList *)pSttGuideBook);//zhouhj 20220326 ��Ϊ�����źŵķ�ʽ

    //if (m_pSttReportViewHtml)
    //{
    //	m_pMacroEditView->ProcessRptAfterGenTemplate(m_pSttReportViewHtml);
    //}

	//emit sig_ShowItems_TreeView((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());//zhouhj 20220326 ��Ϊ�����źŵķ�ʽ
	emit sig_UpdateRptHtml();
}


void QSttTestCntrFrameBase::OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent)
{
	if (g_nUpdateMultiMacroParaEditView == 1)//����Ҫ�����ڵ�ˢ����ģ���Ǳߴ���
	{
	emit sig_ShowItems_TreeView((CExBaseList *)pItems);
	}	
	UpdateRptHtml();
}

void QSttTestCntrFrameBase::OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp)
{

}

void QSttTestCntrFrameBase::OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList)
{

}

//2022-9-13  lijunqing
void QSttTestCntrFrameBase::OnAtsQueryItem(CExBaseObject *pItemPara)
{

}

void QSttTestCntrFrameBase::OnInputData(CSttParas *pParas,CExBaseList *pMsgs)
{

}

void QSttTestCntrFrameBase::OnTestDisconnected()
{
	QSttTestCntrFrameBase::OnTestStoped();
}

void QSttTestCntrFrameBase::FillReport(CExBaseObject *pItem)
{

}

void QSttTestCntrFrameBase::FillReport()
{

}

void QSttTestCntrFrameBase::FillReport_OnlyHtmlRpt(CExBaseObject *pItem)
{

}

void QSttTestCntrFrameBase::FillReport_HtmlRptData()
{
	CExBaseList *pGuideBook = (CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook();
	FillReport_HtmlRptDataByGuideBook(pGuideBook);
}

void QSttTestCntrFrameBase::FillReport_HtmlRptDataByGuideBook(CExBaseList *pItems)
{
	if (pItems == NULL)
	{
		return;
	}

	POS posDevice = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	while (posDevice)
	{
		p = pItems->GetNext(posDevice);
 		if (p->GetClassID() == STTGBXMLCLASSID_CSTTITEMS
			|| p->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
 		{
 			FillReport_HtmlRptDataByGuideBook((CExBaseList *)p);
 		}

 		CSttItemBase* pSttItemBase = (CSttItemBase*)p;
 		if (pSttItemBase->m_nSelect == 0)
 		{
 			continue;
 		}

		POS pos = ((CExBaseList*)p)->GetHeadPosition();
		CExBaseObject* pObject = NULL;
		while (pos)
		{
			pObject = ((CExBaseList*)p)->GetNext(pos);
			CSttItemBase *pItem = (CSttItemBase*)pObject;
			if (pItem == NULL)
			{
				return;
			}

			if (pItem->m_nSelect == 0)
			{
				continue;
			}

			if ((pItem->m_strID == STT_MACRO_ID_ChMapsConfig)||(pItem->m_strID == STT_MACRO_ID_Iec61850Config)
				||(pItem->m_strID == STT_MACRO_ID_SystemConfig))
			{
				continue;
			}

			if (pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST || pObject->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD
				|| pObject->GetClassID() == STTGBXMLCLASSID_CSTTSAFETY || pObject->GetClassID() == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
			{
				FillReport_OnlyHtmlRpt(pObject);
			}
		}

	}
}

void QSttTestCntrFrameBase::SetTestCtrlCntrBase(CSttTestCtrlCntrBase *pTestCtrlCntrBase)
{
	m_pTestCtrlCntrBase = pTestCtrlCntrBase;
	m_pTestMacroUI_Paras = &pTestCtrlCntrBase->m_oTestMacroUI_Paras;
	m_pTestCtrlCntrBase->SetSttTestCtrlCntrMsgInterface(this);

	if (g_theTestCntrFrame != NULL)
	{
		g_pGlobalDatas = g_theTestCntrFrame->m_pTestMacroUI_Paras;
	}

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->SetGlobalDatas(&m_pTestCtrlCntrBase->m_oTestReportHead);
    //}
}

CSttTestMacroUiParas* QSttTestCntrFrameBase::GetTestMacroUiParas(CSttItems *pRootNodeItems,BOOL bSetMacroTest)
{
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pRootNodeItems->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		return NULL;
	}

	CSttTestMacroUiParas *pUIParas = NULL;

	//chenling 20240808 ���ڸ���ģ���ģ�壬��ȡ����pMacroTest
	pUIParas = pRootNodeItems->GetSttTestMacroUiParas(FALSE);


	if (!pUIParas && pTestMacroUI->IsUIOriginal())
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)pRootNodeItems->FindByID(pTestMacroUI->m_strID);

		if (pMacroTest == NULL)
		{
			return NULL;
		}

		if (bSetMacroTest)
		{
			SetMacroTest_Original(pMacroTest);
		}
		pUIParas = (CSttTestMacroUiParas *)pMacroTest->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);
	}
	else if (pTestMacroUI->IsUIWeb())
	{
		if (bSetMacroTest)
		{
			SetMacroTest_Original(NULL);
		}

		pUIParas = (CSttTestMacroUiParas *)pRootNodeItems->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);
	}

	return pUIParas;
}

void QSttTestCntrFrameBase::AddMacroTestReport()
{//ͨ�������еķ�ʽ��ִ�е����ܲ���
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = m_pTestCtrlCntrBase->GetCurrTestMacroUI();

	if (pTestMacroUI != NULL)
	{
		//AddMacroTestReport(pTestMacroUI, NULL, g_pTheSttTestApp->m_pTestMacroUI->m_strName, g_pTheSttTestApp->m_pTestMacroUI->m_strID);
        //if (m_pSttReportViewHtml == NULL)
        //{
        //	return;
        //}

		char *strReport = NULL;
		long nLen = 0;

		GetMacroItemsXml(pTestMacroUI->m_strID,&strReport, nLen,_T(""));
        //if (m_pSttReportViewHtml)
        //{
        //	m_pSttReportViewHtml->AddInsertCmd(pTestMacroUI, "", pTestMacroUI->m_strID, strReport);
        //	m_pSttReportViewHtml->AddUpdateCmd(pTestMacroUI, "", g_pTheSttTestApp->m_pTestMacroUI->m_strID, strReport);
        //	m_pMacroEditView->ProcessRptAfterGenTemplate(m_pSttReportViewHtml);
        //}
	}
}

void QSttTestCntrFrameBase::AddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID)
{
    //if (m_pSttReportViewHtml == NULL)
    //{//2024-9-12 lijunqing �Ż�
    //	return;
    //}

	char *strReport = NULL;
//	CString strMacroID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
	long nLen = 0;
	CString strParentPath;
	strParentPath = _T("");

	if (pParent != NULL)
	{
		strParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	} 

	GetMacroItemsXml(strItemsID,&strReport, nLen,strParentPath);

    //if (m_pSttReportViewHtml)
    //{
    //	m_pSttReportViewHtml->AddInsertCmd(pTestMacroUI, "", pTestMacroUI->m_strID, strReport);
    //}
}

CSttTestResourceBase* QSttTestCntrFrameBase::GetSttTestResource()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return NULL;
	}

	return m_pTestCtrlCntrBase->m_pSttTestResouce;
}

CSttMacroParaEditInterface* QSttTestCntrFrameBase::GetCurrMacroParaEditInterface()
{
	return m_pMacroEditView;
}

CSttMacroParaEditInterface* QSttTestCntrFrameBase::CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist)
{
	return CSttMacroParaEditViewMngr::CreateSttMacroParaEditView(strMacroID,strGridFile,bUseExist);
}

void QSttTestCntrFrameBase::CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
// 	CString strUi_ID;
// 	strUi_ID = pTestMacroUI->m_strUI_ID;
// 
// 	if (strUi_ID.IsEmpty())//20220806 zhouhj ���ݽ���ID��ui-id�򿪲��Թ��ܽ���,Ϊ����֮ǰ����,�����IDΪ�ղ���ԭ��ID
// 	{
// 		strUi_ID = pTestMacroUI->m_strID;
// 	}

	debug_time_long_log("CreateSttMacroParaEditView >>>>>", true);
	m_pMacroEditView = CreateSttMacroParaEditView(pTestMacroUI->m_strID/*strUi_ID*/,pTestMacroUI->m_strGirdFile);//2023.7.16 �Ը�Ϊ����MacroID��ʽ,��Ϊ��Ӧ�����������������ط�ʹ��ʱ����Ĭ�ϵ���MacroID����

	QWidget *pMacroEditWidget = GetMacroEditWidget();
	pMacroEditWidget->setParent(this);
	pMacroEditWidget->setGeometry(m_rcWorkArea);
	debug_time_long_log("CreateSttMacroParaEditView setGeometry", true);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(this);
#endif
}

void QSttTestCntrFrameBase::InitToolBtnFocusPos(const CString &strBtnID)
{
	CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();

	if (pToolBarParas != NULL)//20230301 zhouhj �򿪲��Թ��ܲ���ʱ,�л���ʾ����
	{
		CSttFrame_Button *pFrameButton = (CSttFrame_Button*)pToolBarParas->FindBtnByID(strBtnID);

		if (pFrameButton != NULL)
		{
			QSttToolButtonBase *pPushBtn = (QSttToolButtonBase*)pFrameButton->m_dwItemData;
			pPushBtn->setFocus();
		}
	}
}

CXDrawLine* QSttTestCntrFrameBase::GetCharLibLeftButtonLine()
{
	if(m_pCharLibWidget)
	{
		return m_pCharLibWidget->m_pImpCharactWidget->GetLeftButtonLine();
	}	

	return NULL;
}

void QSttTestCntrFrameBase::AdjustMacroEditWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{//2022-3-25  ������������
	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pSttGbTreeView->ShowBaseList((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());
	connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	debug_time_long_log("OpenMacroTestUI_Test AdjustMacroEditWidgetToFrame GbTreeView", true);

	QWidget *pMacroEditWidget = GetMacroEditWidget();

	if (pTestMacroUI->IsUIOriginal())
	{
		SetActiveWidget(pMacroEditWidget, ActiveWidgetType_MacroUI_Original);
	}
	else
	{
		SetActiveWidget(pMacroEditWidget, ActiveWidgetType_MacroUI_Html);
	}

	debug_time_long_log("OpenMacroTestUI_Test AdjustMacroEditWidgetToFrame ActiveWidget", true);
}

BOOL QSttTestCntrFrameBase::CreateEngineClientWidget()
{
	return FALSE;
}

void QSttTestCntrFrameBase::InitAllButtonStateByTestMacroUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	if (pTestMacroUI == NULL)
	{
		return;
	}

	if (g_pTheSttTestApp->m_pTestMacroUI->HasCharLib())
	{
		UpdateButtonStateByID(STT_CNTR_CMD_CharDrawView,true,true);
	}
	else
	{
		UpdateButtonStateByID(STT_CNTR_CMD_CharDrawView,false,false);
	}

	//δѡ����Թ���ʱ������ʼ���ԡ���ťʹ��ΪFALSE
	if (pTestMacroUI->m_strID != _T(""))
	{
		UpdateButtonStateByID(STT_CNTR_CMD_StartTest,true,true);
	}
	else
	{
		UpdateButtonStateByID(STT_CNTR_CMD_StartTest,false,true);
	}

	//ϵͳ����ҳ�棬δ��ѡ�����֡���Ӧ���ء�IEC���á���ť sf 20220317
	if (!g_oSystemParas.HasDigitalInOrOut())
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,false,false);
	}
	else 
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,true,true);
	}

	//״̬���в�ʹ���ֶ����������ť���������ã����� sf 20220218
	if (HasManuTrigerBtn()/*pTestMacroUI->m_strID == STT_ORG_MACRO_StateTest*/)
	{
		UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
	}
	else
	{
		UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	}
}

void QSttTestCntrFrameBase::OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
											, long nRepeatTimes, long nRptTitle, long nTitleLevel)
{
	if (pTestMacroUI == NULL)
	{
		return;
	}
	
	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI >>");
	}

	SetActiveWidget(NULL);

	//��һ�������������༭ҳ�桢���ر���htmlҳ��
	m_pTestCtrlCntrBase->OpenMacroTestUI(pTestMacroUI);

	//2022-3-27  lijunqing  ���������༭����
	CreateSttMacroParaEditView(pTestMacroUI);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI 2 >>");	}

	if (pTestMacroUI->IsUIOriginal())
	{//ԭ��̬��ҳ����ȡҳ���������
		if (m_pMacroEditView != NULL)
		{
			m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
		}
	}
	else//��ҳ�����ʸ��ͼ��״̬ͼ����Ϣͼ�ڴ˴�ͳһ��ʼ��,ԭ�������ڸ��Թ��캯���г�ʼ�� zhouhj 20220329
	{
		InitBinaryIn_WebUI(m_pTestMacroUI_Paras);
		g_theTestCntrFrame->InitVectorWidget(NULL,NULL);
        g_theTestCntrFrame->InitPowerWidget(NULL,NULL);
		g_theTestCntrFrame->InitStateMonitor();
		g_theTestCntrFrame->ClearInfoWidget();	
	}

	InitAfterCreateSttMacroPara();

	if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
	{
		g_theTestCntrFrame->InitCharLibWidget();
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
        //pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
	}

	AdjustMacroEditWidgetToFrame(pTestMacroUI);
	InitAllButtonStateByTestMacroUI(pTestMacroUI);//���ݲ��Թ��ܳ�ʼ���������Ȱ�ť

	AdjustToolBarButtons();
	CExBaseObject *pSel = m_pSttGbTreeView->GetCurrSelectGbItem();

	if ((m_pSttGbTreeView!= NULL)&&(pSel != NULL))
	{
		CString strCurrRootNodePath;
		strCurrRootNodePath = pSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		if (strCurrRootNodePath.IsEmpty())
		{
			strCurrRootNodePath = strItemsID;
		} 
		else
		{
			strCurrRootNodePath.AppendFormat(_T("$%s"),strItemsID.GetString());
		}

		m_pSttGbTreeView->m_strCurrSelRootNodePath = strCurrRootNodePath;
	}
	

	//if (! g_bIsOpenMacroFromMain)
	{
		AddMacroTestReport(pTestMacroUI, pSel, strItemsName, strItemsID);
	}

	//�����������ߣ����������߶��壬�ڲ���ģ�����ɺ󣬷��ص�ģ����Ϣ�������������ģ�壬��ʹ��Ĭ�ϲ���ģ��
	CString strFile;
	GetCharacteristicsFile(pTestMacroUI, strFile);
	m_pCharacteristics->DeleteAll();

	if (IsFileExist(strFile))
	{
		m_pCharacteristics->OpenXmlFile(strFile,CCharacteristicXmlRWKeys::CCharacteristicsKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
	}

	//�����������߸ı��¼�
	if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
	{
		m_pCharLibWidget->InitCharacteristicsLib(pTestMacroUI->m_strUI_ID,pTestMacroUI->m_strCharlibFile);
		m_pCharLibWidget->GroupDatasToChar(m_pTestMacroUI_Paras);
		m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);
		m_pCharLibWidget->m_strCharParasFile = strFile;

		if (m_pCharactWidgetForTest != NULL)
		{
			m_pCharactWidgetForTest->InitCharacteristic(pTestMacroUI->m_strID);
		}

		if (m_pCharTestPointsGrid)
		{
			m_pCharTestPointsGrid->InitMacroID(pTestMacroUI->m_strID);
		}
	}

	//2022-3-21 ��� ���������ģ��ָ���֤��ӱ������
    CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin GenerateTemplate >>");

#ifndef SttTestCntrThread_H
	bool bGenSucc = GenerateTemplate(pSel, strItemsName, strItemsID, nRepeatTimes, nRptTitle, nTitleLevel);
#else
	g_theSttTestCntrThread->m_pParentItems = pSel;
	g_theSttTestCntrThread->m_strItemsName = strItemsName;
	g_theSttTestCntrThread->m_strItemsID = strItemsID;
	g_theSttTestCntrThread->PostThreadMessage(10, 0, 0);
#endif
	CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end GenerateTemplate >>");

	if (g_nLogDebugInfor == 1)
    {
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end OpenMacroTestUI >>");
	}

	UpdateToolButtons();
	InitToolBtnFocusPos(STT_CNTR_CMD_TemplateView);
}

void QSttTestCntrFrameBase::OpenMacroTestUI_Test(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
												 , long nRepeatTimes, long nRptTitle)
{
	if (pTestMacroUI == NULL)
	{
		return;
	}

	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI >>");
	}

	SetActiveWidget(NULL);
	debug_time_long_log("OpenMacroTestUI_Test SetActiveWidget(0)", true);

	//��һ�������������༭ҳ�桢���ر���htmlҳ��
	m_pTestCtrlCntrBase->OpenMacroTestUI(pTestMacroUI);
	debug_time_long_log("OpenMacroTestUI_Test OpenMacroTestUI", true);

	//2022-3-27  lijunqing  ���������༭����
	CreateSttMacroParaEditView(pTestMacroUI);
	debug_time_long_log("OpenMacroTestUI_Test CreateSttMacroParaEditView", true);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI 2 >>");	}

	if (pTestMacroUI->IsUIOriginal())
	{//ԭ��̬��ҳ����ȡҳ���������
		if (m_pMacroEditView != NULL)
		{
			m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
			debug_time_long_log("OpenMacroTestUI_Test GetDatas", true);
		}
	}
	else//��ҳ�����ʸ��ͼ��״̬ͼ����Ϣͼ�ڴ˴�ͳһ��ʼ��,ԭ�������ڸ��Թ��캯���г�ʼ�� zhouhj 20220329
	{
		InitBinaryIn_WebUI(m_pTestMacroUI_Paras);
		debug_time_long_log("OpenMacroTestUI_Test InitBinaryIn_WebUI", true);
		g_theTestCntrFrame->InitVectorWidget(NULL,NULL);
		debug_time_long_log("OpenMacroTestUI_Test InitVectorWidget", true);
		g_theTestCntrFrame->InitPowerWidget(NULL,NULL);
		debug_time_long_log("OpenMacroTestUI_Test InitPowerWidget", true);
		g_theTestCntrFrame->InitStateMonitor();
		debug_time_long_log("OpenMacroTestUI_Test InitStateMonitor", true);
		g_theTestCntrFrame->ClearInfoWidget();	
		debug_time_long_log("OpenMacroTestUI_Test ClearInfoWidget", true);
	}

	InitAfterCreateSttMacroPara();
	debug_time_long_log("OpenMacroTestUI_Test InitAfterCreateSttMacroPara", true);

	if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
	{
		g_theTestCntrFrame->InitCharLibWidget();
		debug_time_long_log("OpenMacroTestUI_Test InitCharLibWidget", true);
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
        //pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
		debug_time_long_log("OpenMacroTestUI_Test OpenHtmlFile-UI_File", true);
	}

	AdjustMacroEditWidgetToFrame(pTestMacroUI);
	debug_time_long_log("OpenMacroTestUI_Test AdjustMacroEditWidgetToFrame", true);
	InitAllButtonStateByTestMacroUI(pTestMacroUI);//���ݲ��Թ��ܳ�ʼ���������Ȱ�ť
	debug_time_long_log("OpenMacroTestUI_Test InitAllButtonStateByTestMacroUI", true);

	AdjustToolBarButtons();
	debug_time_long_log("OpenMacroTestUI_Test AdjustToolBarButtons", true);
	CExBaseObject *pSel = m_pSttGbTreeView->GetCurrSelectGbItem();

	if ((m_pSttGbTreeView!= NULL)&&(pSel != NULL))
	{
		CString strCurrRootNodePath;
		strCurrRootNodePath = pSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		if (strCurrRootNodePath.IsEmpty())
		{
			strCurrRootNodePath = strItemsID;
		} 
		else
		{
			strCurrRootNodePath.AppendFormat(_T("$%s"),strItemsID.GetString());
		}

		m_pSttGbTreeView->m_strCurrSelRootNodePath = strCurrRootNodePath;
	}


	//if (! g_bIsOpenMacroFromMain)
	{
		//2024-9-12 lijunqing �Ż�ϵͳ����������Ч��  �ڴ򿪱����ʱ����ʾ����
		//AddMacroTestReport(pTestMacroUI, pSel, strItemsName, strItemsID);
#ifdef _PSX_QT_LINUX_
        //m_pSttReportViewHtml->XAddMacroTestReport(pTestMacroUI, pSel, strItemsName, strItemsID);
#else
		AddMacroTestReport(pTestMacroUI, pSel, strItemsName, strItemsID);
#endif
		debug_time_long_log("OpenMacroTestUI_Test AddMacroTestReport", true);
	}

	//�����������ߣ����������߶��壬�ڲ���ģ�����ɺ󣬷��ص�ģ����Ϣ�������������ģ�壬��ʹ��Ĭ�ϲ���ģ��
	CString strFile;
	GetCharacteristicsFile(pTestMacroUI, strFile);
	m_pCharacteristics->DeleteAll();

	if (IsFileExist(strFile))
	{
		m_pCharacteristics->OpenXmlFile(strFile,CCharacteristicXmlRWKeys::CCharacteristicsKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
		debug_time_long_log("OpenMacroTestUI_Test Characteristics->OpenXmlFile", true);
	}

	//�����������߸ı��¼�
	if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
	{
		m_pCharLibWidget->InitCharacteristicsLib(pTestMacroUI->m_strUI_ID,pTestMacroUI->m_strCharlibFile);
		m_pCharLibWidget->GroupDatasToChar(m_pTestMacroUI_Paras);
		m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);
		m_pCharLibWidget->m_strCharParasFile = strFile;

		if (m_pCharactWidgetForTest != NULL)
		{
			m_pCharactWidgetForTest->InitCharacteristic(pTestMacroUI->m_strID);
		}

		if (m_pCharTestPointsGrid)
		{
			m_pCharTestPointsGrid->InitMacroID(pTestMacroUI->m_strID);
		}
		debug_time_long_log("OpenMacroTestUI_Test CharLibWidget", true);
	}

	//2022-3-21 ��� ���������ģ��ָ���֤��ӱ������
    CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin GenerateTemplate >>");

#ifdef _PSX_OS_CENTOS_
    bool bGenSucc = GenerateTemplate(pSel, strItemsName, strItemsID, nRepeatTimes, nRptTitle);
#else
#ifndef SttTestCntrThread_H
	bool bGenSucc = GenerateTemplate(pSel, strItemsName, strItemsID, nRepeatTimes, nRptTitle);
#else
    g_theSttTestCntrThread->m_pParentItems = pSel;
    g_theSttTestCntrThread->m_strItemsName = strItemsName;
    g_theSttTestCntrThread->m_strItemsID = strItemsID;
    g_theSttTestCntrThread->PostThreadMessage(10, 0, 0);
#endif
#endif
	CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end GenerateTemplate >>");

	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end OpenMacroTestUI >>");
	}

	UpdateToolButtons();
	debug_time_long_log("OpenMacroTestUI_Test UpdateToolButtons", true);
	InitToolBtnFocusPos(STT_CNTR_CMD_TemplateView);
	debug_time_long_log("OpenMacroTestUI_Test InitToolBtnFocusPos", true);
	if (m_pMacroEditView != NULL)
	{
		m_pMacroEditView->UpdatePrimParaSetUI();//20240920 suyang ��ʼ��ʱ����������һ��/���θ��½����ѹ��λ
		//g_oSttTestResourceMngr.SaveSystemParasFile();//��ֹIEC������ϵͳ������һ��ֵ��һ�µ����������
	}
}

void QSttTestCntrFrameBase::UpdateButtonsStateByID(const CString &strButtonID, BOOL bEnable)
{
	CSttFrame_Button *pBtn = m_pSttFrameConfig->FindBtnByID(strButtonID);

	if (pBtn != NULL)
	{
		QSttToolButtonBase *pButton = (QSttToolButtonBase*)pBtn->m_dwItemData;

		if (pButton != NULL)
		{
			pButton->setEnabled(bEnable);
		}
	}
}

void QSttTestCntrFrameBase::AdjustToolBarButtons()
{
}

void QSttTestCntrFrameBase::AdjustStatusBarButtons()
{
}

void QSttTestCntrFrameBase::Before_OnCmd()
{

}

void QSttTestCntrFrameBase::UpdateStartStopButtonByItemCount()
{
	long nCount = m_pTestCtrlCntrBase->GetGbItemCount();
	QSttToolButtonBase *pButton = (QSttToolButtonBase*)m_pStartTestBtn->m_dwItemData;

	if (nCount == 0)
	{
		pButton->setEnabled(FALSE);
	}
	else
	{
		pButton->setEnabled(TRUE);
	}
}

void QSttTestCntrFrameBase::UpdateToolButtons_FloatPanel()
{

}

CSttMacroParaEditInterface* QSttTestCntrFrameBase::GetMacroEditView()
{
	return m_pMacroEditView;
}

QCharTestPointsGrid* QSttTestCntrFrameBase::GetCharTestPointsGrid()
{
	return m_pCharTestPointsGrid;
}

void QSttTestCntrFrameBase::ClearItemStateList()
{
//	CAutoSimpleLock oLock(m_oCriticSection_ItemStateList);
	m_oItemStateList.Clear();
}

BOOL QSttTestCntrFrameBase::MUTestValid()
{
	if (g_bSmartCap_RecordNow)
	{
		return TRUE;
	}

	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

	if ((strIDMacroUI != STT_ORG_MACRO_MUAccuracyTest)&&
		(strIDMacroUI != STT_ORG_MACRO_MUFirstCycleTest)&&
		(strIDMacroUI != STT_ORG_MACRO_MUAccurAutoTest)&&
		(strIDMacroUI != STT_ORG_MACRO_MUAutoTest))
	{
		return TRUE;
	}

	return FALSE;
}

void QSttTestCntrFrameBase::OpenMacroTestUI_OnlyCreate(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	if (pTestMacroUI == NULL)
	{
		return;
	}
	
	//ֱ�Ӵ����µ�ҳ�棬CreateSttMacroParaEditView�ڶ�����������Ϊfalse
	m_pMacroEditView = CreateSttMacroParaEditView(pTestMacroUI->m_strID,pTestMacroUI->m_strGirdFile, FALSE);

	if (pTestMacroUI->IsUIOriginal())
	{//ԭ��̬��ҳ����ȡҳ���������
		m_pMacroEditView->SetDatas(m_pTestMacroUI_Paras);
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
        //pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
	}

	QWidget *pMacroEditWidget = GetMacroEditWidget();
	pMacroEditWidget->setParent(this);
	pMacroEditWidget->setGeometry(m_rcWorkArea);
}

//�๦�ܲ���ģ��༭ģʽ
void QSttTestCntrFrameBase::AddMacroTestReport(const CString &strParentItemsPath, const CString &strItemsID, CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{

}


BOOL QSttTestCntrFrameBase::SwitchMacroViewByCurrSel(CSttItems *pCurrSelRootNode)
{
	return FALSE;
}

void QSttTestCntrFrameBase::OpenMacroTestUI(CSttTestMacroUiParas *pUIParas, CSttMacroTestUI_TestMacroUI *pTestMacroUI
											,CSttTestMacroCharParas *pSttTestMacroCharParas)
{
	if (pUIParas == NULL)
	{
		return;
	}

	if (pTestMacroUI == NULL)
	{
		return;
	}

	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI >>");
	}

	m_pTestCtrlCntrBase->SetCurrTestMacroUI(pTestMacroUI);//2023.3.23 zhouhj
	SetActiveWidget(NULL);

	//2022-3-27  lijunqing  ���������༭����
	CreateSttMacroParaEditView(pTestMacroUI, TRUE);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI 2 >>");	}

	m_pTestMacroUI_Paras->DeleteAll();

	BSTR bstrText = pUIParas->m_strParaText.AllocSysString();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pTestMacroUI_Paras->SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	if (pTestMacroUI->IsUIOriginal())
	{
		if (pTestMacroUI->m_strID != STT_ORG_MACRO_Iec61850Config
			&& pTestMacroUI->m_strID != STT_ORG_MACRO_SystemConfig
			&& pTestMacroUI->m_strID != STT_ORG_MACRO_ChMapsConfig)
		{
			if (m_pMacroEditView != NULL)
			{
				m_pMacroEditView->SetDatas(m_pTestMacroUI_Paras);

				//zhouhj 2023.9.15 ��ʱ�ڴ˴�������ֹ���Թ��ܱ���ģ���,�ṹ���������µĲ���,���º��ڻ�ȡ������������֮ǰ��һ��,
				//ÿ���л����Թ���ʱ,������ʾ��������
				m_pTestMacroUI_Paras->DeleteAll();
				m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
			}
		}
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
        //pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
		//����ˢ����ҳ��ʸ��ͼ��״̬ͼ����Ϣͼ
		g_theTestCntrFrame->InitVectorWidget(NULL,NULL);
		g_theTestCntrFrame->InitPowerWidget(NULL,NULL);
		g_theTestCntrFrame->InitStateMonitor();
		g_theTestCntrFrame->ClearInfoWidget();
        g_theTestCntrFrame->InitFAParasSetDialog();
	}

	AdjustMacroEditWidgetToFrame(pTestMacroUI);

	AdjustToolBarButtons();

	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end OpenMacroTestUI >>");
	}

	if (pTestMacroUI->IsUIOriginal())
	{
		if (m_pMacroEditView != NULL)
		{
			CSttMacroParaEditViewOriginal* pMacro = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pMacro->m_bIsOpenMacroFinished = TRUE;
		}
	}
}

void QSttTestCntrFrameBase::CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI, BOOL bUseExist)
{
	if (pTestMacroUI->m_strID == STT_ORG_MACRO_Iec61850Config
		|| pTestMacroUI->m_strID == STT_ORG_MACRO_SystemConfig
		|| pTestMacroUI->m_strID == STT_ORG_MACRO_ChMapsConfig)
	{
		return;
	}

	m_pMacroEditView = CreateSttMacroParaEditView(pTestMacroUI->m_strID,pTestMacroUI->m_strGirdFile, bUseExist);
	QWidget *pMacroEditWidget = GetMacroEditWidget();
	pMacroEditWidget->setParent(this);
	pMacroEditWidget->setGeometry(m_rcWorkArea);
}

void QSttTestCntrFrameBase::DeleteMacroTestReport(const CString &strParentItemsPath, const CString &strItemsID)
{
    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}
    //
    //m_pSttReportViewHtml->DeleteMacroTestReport(strParentItemsPath, strItemsID);
}

void QSttTestCntrFrameBase::UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath)
{
    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}

	char *strReport = NULL;
	long nLen = 0;

	GetMacroItemsXml(strItemsID, &strReport, nLen,strParentPath);

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(strMacroUI_ID);

	if ((nLen > 0)&& (pTestMacroUI!= NULL))
	{
        //m_pSttReportViewHtml->AddUpdateCmd(pTestMacroUI, strParentPath, strItemsID, strReport);
	}
}

void QSttTestCntrFrameBase::SetMacroTest_Original(CExBaseObject *pMacroTest)
{

}

void QSttTestCntrFrameBase::SelectTestMacro_CmdWzd(const CString &strTestMacroUI, const CString &strItemsName
												   , const CString &strItemsID, CDataGroup *pCommCmd
												   , const CString &strTestClass, const CString &strDvmFile
												   , long nRepeatTimes, long nRptTitle, long nTitleLevel)
{

}

void QSttTestCntrFrameBase::OnDeleteCurr(CExBaseObject *pCurrObj)
{

}

void QSttTestCntrFrameBase::OnSaveCurr(CExBaseObject *pCurrObj)
{

}
//2022-9-11  lijunqing
void QSttTestCntrFrameBase::ViewCmdEditWidget(CExBaseObject *pSelObj)
{

}

//2022-9-13  lijunqing
void QSttTestCntrFrameBase::ViewMacroEditWidget(CExBaseObject *pSelObj)
{
	
}

//2022-9-12 lijunqing
void QSttTestCntrFrameBase::SaveMacroParasToCurrWzd(CDataGroup *pCommCmd)
{

}

BOOL QSttTestCntrFrameBase::OpenSclFile()
{
	return FALSE;
}

CString QSttTestCntrFrameBase::SelIedFromScl()
{
	return _T("");
}

void QSttTestCntrFrameBase::InitConfig(const CString &strFrameCfgFile)
{
	m_pSttFrameConfig = CSttFrameConfig::Create(strFrameCfgFile);
//	CXMessageBox::information(NULL,"Title",m_pSttFrameConfig->m_strFile);

	if (!IsAutoTest())
	{
	CString strTestMacroResultsFilePath,strTestMacroBinSelected, strSafetyMsgCfgs;
	strTestMacroResultsFilePath = _P_GetConfigPath();
	strTestMacroResultsFilePath += _T("SttTestMacroResults.xml");//2023.3.11 zhouhj ���ڲ��Խ���������ʾ��Ҫ�Ĳ��Խ��ID
	strTestMacroBinSelected = _P_GetConfigPath();//2023.3.11 zhouhj ����������ҳ���ܽ��������,��ͬ���Թ��ܿ���ѡ��ID��һ��ʱ,����IDӳ��ʹ��
	strTestMacroBinSelected += _T("SttTestMacroBinSelected.xml");

	//Ԥ�õĽ�����ʾ��Ϣ����
	strSafetyMsgCfgs = _P_GetConfigPath();
	strSafetyMsgCfgs += _T("SttSafetyMsgCfg.xml");

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oTestMacroResults.OpenXmlFile(strTestMacroResultsFilePath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oTestMacroResults, _T("SttTestMacroResults.xml"));
#endif
	m_oBinaryInParas.OpenXmlFile(strTestMacroBinSelected,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
#ifndef _PSX_QT_LINUX_//zhouhj 2024.4.11 ��Linux����ʱ��ʹ�ô˷�ʽ
	m_oSafetyMsgCfgs.OpenXmlFile(strSafetyMsgCfgs, CSttSafetyMsgCfgXmlRWKeys::g_pXmlKeys);
#endif

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	//xlang_TranslateByResourceFile(m_pSttFrameConfig,"TestCntrlFrameConfig.xml");
	g_nLogDebugInfor = m_pSttFrameConfig->m_nLogDebugInfor;
	m_nSelMacroShow = m_pSttFrameConfig->m_nSelMacroShow;
	CVerUpdateCfgXmlRWKeys::Create();
	}

	CSttFrame_Font *pFont = m_pSttFrameConfig->GetFont();
//#ifndef _PSX_QT_WINDOWS_   //chenling 20241224 ��������7.0����̫С�����Ŷ������ļ�
	m_gFont.setFamily(pFont->m_strName);
	m_gFont.setPixelSize(pFont->m_nHeigth);
	m_gFont.setBold(pFont->m_nBold);
//#endif
	g_pSttGlobalFont = &m_gFont;   //2022-9-16  lijunqing

	debug_time_long_log("InitFrame_InitConfig", true);
}

void QSttTestCntrFrameBase::ReleaseConfig()
{
	CVerUpdateCfgXmlRWKeys::Release();
	CSttFrameConfig::Release();
}

void QSttTestCntrFrameBase::GetCharacteristicsFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CString &strFile)
{
	if (pTestMacroUI == NULL)
	{
		return;
	}

	//2022-9-4  lijunqing ȱʡ��Ĭ�ϵ��������ߣ����浽�Ͳ��Բ�����ͬ��·�����ļ�����������_Char
	CString strTitle;
	strTitle = GetFileTitleFromFilePath(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile);
	strTitle += _T("_Char");
	strFile = stt_ui_GetParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile);
	strFile = ChangeFileName(strFile, strTitle);
}

//2022-9-4  lijunqing
void QSttTestCntrFrameBase::InitCharacteristics(CSttContents *pContents)
{
	if (m_pCharacteristics == NULL || pContents == NULL)
	{
		return;
	}

	if (pContents->m_strText.GetLength() <= 20)
	{
		return;
	}

	m_pCharacteristics->DeleteAll();
	BSTR bstrText = pContents->m_strText.AllocSysString();
	m_pCharacteristics->SetXml(bstrText, CCharacteristicXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	//�����������߸ı��¼�
	m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);
}

CSttFrame_Button* QSttTestCntrFrameBase::GetStartTestBtn()
{
	if (m_pStartTestBtn != NULL)
	{
		return m_pStartTestBtn;
	}

	m_pStartTestBtn = m_pSttFrameConfig->FindStartStopBtn();
	return m_pStartTestBtn;
}

CSttFrame_Button* QSttTestCntrFrameBase::GetManualTriggerBtn()
{
	if (m_pManualTriggerBtn != NULL)
	{
		return m_pManualTriggerBtn;
	}

	m_pManualTriggerBtn = m_pSttFrameConfig->FindBtnByID(STT_CNTR_CMD_ManuTriger);
	return m_pManualTriggerBtn;
}

CSttFrame_Button* QSttTestCntrFrameBase::GetExitBtn()
{
	if (m_pExitBtn != NULL)
	{
		return m_pExitBtn;
	}

	m_pExitBtn = m_pSttFrameConfig->FindBtnByID(STT_CNTR_CMD_Exit);
	return m_pExitBtn;
}

void QSttTestCntrFrameBase::InitIcon(const CString& strItemID, const QIcon& icon)
{
	CSttFrame_Button* pTestBtn = NULL;

	if ((strItemID == STT_CNTR_CMD_StartTest)||(strItemID == STT_CNTR_CMD_StopTest))
	{
		pTestBtn = GetStartTestBtn();
	}
	else
	{
		pTestBtn = m_pSttFrameConfig->FindBtnByID(strItemID);
	}
	
	if(pTestBtn)
	{
		QSttToolButtonBase *pButton = (QSttToolButtonBase*)pTestBtn->m_dwItemData;
		QRect rc = pButton->rect();	

		if(pTestBtn->m_strIcon.GetLength())
		{
			//�����û��Զ����ͼƬ����
			QString strPath = _P_GetResourcePath();
			strPath += pTestBtn->m_strIcon;
			QPixmap pixmap = QIcon(strPath).pixmap(QSize(110, 110));
			QIcon tempIcon = QIcon(pixmap.scaled(pButton->width(), pButton->height()));
			pButton->setIcon(tempIcon);
		}
		else
		{
			//�������Ĭ��ͼƬ		
			QPixmap pixmap = icon.pixmap(QSize(110, 110));
			QIcon tempIcon = QIcon(pixmap.scaled(pButton->width(), pButton->height()));
			pButton->setIcon(tempIcon);
		}
		pButton->setIconSize(QSize(pButton->width(), pButton->height()));
		pButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
		pButton->setAutoRaise(true);
	}
}

void QSttTestCntrFrameBase::InitIcon(const CString& strItemID, const CString& strIcon)
{
	CSttFrame_Button* pTestBtn = NULL;

	if ((strItemID == STT_CNTR_CMD_StartTest)||(strItemID == STT_CNTR_CMD_StopTest))
	{
		pTestBtn = GetStartTestBtn();
	}
	else
	{
		pTestBtn = m_pSttFrameConfig->GetToolBar()->FindBtnByID(strItemID);
	}

//	CSttFrame_Button* pTestBtn = m_pSttFrameConfig->GetToolBar()->FindBtnByID(strItemID);
	if(pTestBtn)
	{
		QSttToolButtonBase *pButton = (QSttToolButtonBase*)pTestBtn->m_dwItemData;
#ifdef _PSX_QT_LINUX_
		pButton->setStyleSheet(g_strQToolButtonStyleSheet);
#endif

// 		pButton->setStyleSheet("QToolButton:focus{ "
// 			"border: none; "
// 			"padding: 0px; "
// 			"background-color:rgb(255,0,0);"
// 			"}");
	}
}

void QSttTestCntrFrameBase::InitIcon()
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin InitIcon >>");	}

	//��ʼ����ťͼ��
	CSttFrame_ToolBar* pSttFrameButtons = m_pSttFrameConfig->GetToolBar();
	CSttFrame_Button* pBtnStart = m_pSttFrameConfig->FindStartStopBtn();
	CSttFrame_Button* pBtnTriger = m_pSttFrameConfig->FindBtnByID("ManuTriger");
	
#ifdef _PSX_QT_WINDOWS_
	CString strFilePath = _P_GetResourcePath();

	if (pBtnStart != NULL)
	{
	m_imgStart.addFile(strFilePath + "start.png");
	}

	m_imgStop.addFile(strFilePath + "stop.png");
#else
     CString strFilePath;
	 strFilePath = ":/ctrls/images/";

	if (pBtnStart != NULL)
	{
		m_imgStart.addFile(strFilePath + "start.png");
	}

	m_imgStop.addFile(strFilePath + "stop.png");
#endif

	if(pBtnTriger)
	{
		m_imgTriger.addFile(strFilePath + pBtnTriger->m_strIcon);
	}

	POS pos = pSttFrameButtons->GetHeadPosition();
	while (pos)
	{
		CSttFrame_Panal* pPanal = (CSttFrame_Panal*)pSttFrameButtons->GetNext(pos);
		if(pPanal->m_strID == "static-buttons"
			|| pPanal->m_strID == "float-buttons")
		{
			POS posBtn = pPanal->GetHeadPosition();
			while (posBtn)
			{
				CSttFrame_Button* pBtn = (CSttFrame_Button*)pPanal->GetNext(posBtn);
				InitIcon(pBtn->m_strID, strFilePath + "button_bk.png");
			}
		}
	}

	InitIcon(STT_CNTR_CMD_StartTest, m_imgStart);
	InitIcon(STT_CNTR_CMD_ManuTriger, m_imgTriger);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end InitIcon >>");	}
}

void QSttTestCntrFrameBase::InitPinyinLib()
{

}

//2022-9-16  lijunqing
QFont *g_pSttGlobalFont = NULL;

void QSttTestCntrFrameBase::InitUI()
{
	g_oSttButtonIconMngr.Init();//��ʼ��ͼƬ��Դ sf 20220302
	debug_time_long_log("InitUI-g_oSttButtonIconMngr", true);

// 	CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();
// 	CSttFrame_StatusBar *pStatusBarParas = m_pSttFrameConfig->GetStatusBar();
	GetStartTestBtn();
	GetManualTriggerBtn();
	debug_time_long_log("InitUI-GetButton", true);

// 	m_pToolBar = new QSttBarBase(pToolBarParas, m_oDataBtnsMngr,m_gFont,this);
// 	m_pToolBar->setGeometry(0,0,pToolBarParas->m_nWidth,pToolBarParas->m_nHeight);

	//��ʼ����ʱ�������ֶ�������ť sf 20220222
// 	UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
// 	//�մ򿪵�ʱ�򣬿�ʼ���Բ�ʹ��
// 	UpdateButtonStateByID(STT_CNTR_CMD_StartTest,false,true);
// 
// 	//ϵͳ����ҳ�棬δ��ѡ�����֡���Ӧ���ء�IEC���á���ť sf 20220317
// 	if (g_oSystemParas.m_nHasDigital == 0)
// 	{
// 		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,false,false);
// 	}
// 	else
// 	{
// 		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,true,true);
// 	}
// 
// 	m_pToolBar->AdjustPanels();
// 
// 	m_pStatusBar = new QSttBarBase(pStatusBarParas, m_oDataBtnsMngr,m_gFont,this);
// 	m_pStatusBar->setGeometry(0,m_pSttFrameConfig->m_nHeight - pStatusBarParas->m_nHeight,pStatusBarParas->m_nWidth,pStatusBarParas->m_nHeight);
}

void QSttTestCntrFrameBase::CalRectArea()
{
	CSttFrame_GbTree *pGbTree = m_pSttFrameConfig->GetGbTree();

	CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();
	int nHeight = m_pSttFrameConfig->m_nHeight - pToolBarParas->m_nHeight - pToolBarParas->m_nHeight - 2*SttFrame_Interval;

	if (m_pSttGbTreeView == NULL || m_pSttGbTreeView->isVisible() == false)
	{
		m_rcWorkArea = QRect(0, pToolBarParas->m_nHeight + SttFrame_Interval, m_pSttFrameConfig->m_nWidth,nHeight);
	}
	else
	{
		CSttFrame_Size *pSize = pGbTree->GetSize();

		m_rcGbItemsArea = QRect(0,pToolBarParas->m_nHeight + SttFrame_Interval,pSize->m_nWidth,nHeight);
		m_rcWorkArea = QRect(pSize->m_nWidth, pToolBarParas->m_nHeight + SttFrame_Interval, m_pSttFrameConfig->m_nWidth - pSize->m_nWidth - SttFrame_Interval, nHeight);

		if (m_pSttGbTreeView != NULL)
		{
			m_pSttGbTreeView->setGeometry(m_rcGbItemsArea);
		}
	}

	if (m_pActiveWidget != NULL)
	{
		m_pActiveWidget->setGeometry(m_rcWorkArea);
	}
}

BOOL QSttTestCntrFrameBase::GetDatas()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	if (m_pMacroEditView == NULL)
	{
		return FALSE;
	}

	CDataGroup oRetParas;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
	}

	//������ҳ�ģ���Ҫ������ҳ������ȡ��Щ��������˲���ֱ�Ӵ���һ���յ��β�
	m_pMacroEditView->GetDatas(&oRetParas);

	if (!oRetParas.IsEqual(m_pTestMacroUI_Paras))
	{
		oRetParas.UpdateChildren(m_pTestMacroUI_Paras);
		SaveUIParaFile(m_pTestMacroUI_Paras);
	}

	return TRUE;
}

void QSttTestCntrFrameBase::PromptToSave(CExBaseObject *pSelObj, BOOL bIsItemSame)
{
	//�ĵ�QSttTestCntrFrameWin��ʵ����
}

BOOL QSttTestCntrFrameBase::IsUiParasChanged(BOOL &bChanged, CDataGroup *pParas)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	if (m_pMacroEditView == NULL)
	{
		return FALSE;
	}

	//����ҳ��ȡ��������Ҫ�ȸ�����ҳ��ȡ�Ĳ��ֵĲ���
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		pParas->AppendCloneEx(*m_pTestMacroUI_Paras);
	}

	m_pMacroEditView->GetDatas(pParas);

	//�жϲ����Ƿ����ı�ʱ��ֻ�ж�id��value
	CDataMngrXmlRWKeys::IncIsEqualOwn_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys);

	//�жϲ����Ƿ����ı�ʱ��ֻ�ж�id��value
	CDataMngrXmlRWKeys::IncIsEqualOwn_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys);
	if (!pParas->IsEqualChildren(m_pTestMacroUI_Paras))
	{
		bChanged = TRUE;
		CDataMngrXmlRWKeys::DecIsEqualOwn_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys);
		return TRUE;
	}

	CDataMngrXmlRWKeys::DecIsEqualOwn_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys);

// 	else
// 	{
// 		CSttMacroParaEditViewOriginal* pOriginalView = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
// 		bChanged = pOriginalView->m_bTmtParaChanged;
// 		if(bChanged)
// 			return TRUE;
// 	}

	if (m_pCharLibWidget != NULL)
	{
		bChanged = m_pCharLibWidget->m_bCharChanged;
	}

	return TRUE;
}

//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ
void QSttTestCntrFrameBase::SaveUIParaFile(CDataGroup *pParas)
{
	//shaolei  2023-4-6   ��ʱ����
	return;

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	CString strPath = stt_ui_GetParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile);
	pParas->SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);

//	CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
}

void QSttTestCntrFrameBase::UpdateCmdButtonsState(const CString &strState)
{
	//m_pToolBar->UpdateEnableState(strState);
	//m_pStatusBar->UpdateEnableState(strState);
	//�̵߳��õ�ʱ��ᱼ�����ĳ��źŲ۵���ʽ sf 20220218
	//���������̵߳�������źŲۺ�����������
	//���߳�ֱ�ӵ��÷�������Ҫ�����ź� sf 20220223
	//������һ��˳���Ȼ�ID����ʾ�ٽ��ã���Ȼ���ֹͣҲ���õ�
	emit sig_UpdateEnableState(strState);
	
}

void QSttTestCntrFrameBase::UpdateButtonStateByID( const CString &strID,bool bState,bool bShow )
{
// 	if (m_pToolBar != NULL)
// 	{
// 		for(int i = 0; i<m_pToolBar->m_plistPanel.size();i++)
// 		{
// 			QSttPanelBase* pPanel = m_pToolBar->m_plistPanel.at(i);
// 			for (int j = 0;j < pPanel->m_listCtrls.size(); j++)
// 			{
// 				QSttToolButtonBase* pButton = pPanel->m_listCtrls.at(j);
// 				if (pButton->m_pCfgData->m_strID == strID)
// 				{
// 					pButton->setDisabled(!bState);
// 					pButton->m_bShow = bShow;
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	if (m_pMenuWidget != NULL)
// 	{
// 		for(int i = 0; i < m_pMenuWidget->m_Btnlist.size(); i++)
// 		{
// 			QSttItemButton *pButton = m_pMenuWidget->m_Btnlist.at(i);
// 			if (pButton->m_pItem->m_strID == strID)
// 			{
// 				pButton->setDisabled(bState);
// 				pButton->setVisible(bShow);
// 				break;
// 			}
// 		}
// 	}
}

//ѡ�����Ƿ���ʾ sf 20220318
void QSttTestCntrFrameBase::SetAddMacroEnable( bool bShow )
{
	//m_bSelMacroShow = bShow;
	m_nSelMacroShow = bShow;
	UpdateButtonStateByID(STT_CNTR_CMD_AddMacro,bShow,bShow);
	//m_pToolBar->AdjustPanels();
	AdjustToolBarButtons();
}

void QSttTestCntrFrameBase::UpdateStartStopTestButton(const CString &strState)
{
	if (m_pStartTestBtn == NULL)
	{
		return;
	}

	QSttToolButtonBase *pButton = (QSttToolButtonBase*)m_pStartTestBtn->m_dwItemData;

	CSttFrame_ToolBar* pSttFrameButtons = m_pSttFrameConfig->GetToolBar();

	CString strFilePath = _P_GetResourcePath();
	if (strState == STT_TEST_STATE_TESTTING)
	{
		m_pStartTestBtn->m_strID = STT_CNTR_CMD_StopTest;
		m_pStartTestBtn->m_strName = g_sLangTxt_StopTest;
		InitIcon(STT_CNTR_CMD_StopTest, m_imgStop);
	}
	else
	{
		m_pStartTestBtn->m_strID = STT_CNTR_CMD_StartTest;
		m_pStartTestBtn->m_strName = g_sLangTxt_StartTest;
		InitIcon(STT_CNTR_CMD_StartTest, m_imgStart);
	}

	pButton->setText(m_pStartTestBtn->m_strName);
}

void QSttTestCntrFrameBase::LogString(long nLevel, const CString &strMsg)
{
	if (nLevel == XLOGLEVEL_RESULT)
	{
		LogStringResult(nLevel,strMsg);
		return;
	}
	else if (nLevel == XLOGLEVEL_ASSIST)
	{
#ifndef NOT_USE_ASSIST
        //if (g_oSttSystemConfig.IsAssist())
        //{
        //if (g_theAssistWndDynEffExecTool != NULL)
        //{
        //	g_theAssistWndDynEffExecTool->ShowMsg(strMsg,6000);
        //}
        //}
		
#endif
	}

	if (m_pOutputWidget != NULL)
	{
		m_pOutputWidget->LogString(nLevel, strMsg);
	}
	
	//ui->edtMsgLog->setText(strMsg);
}


void QSttTestCntrFrameBase::LogStringResult(long nLevel, const CString &strMsg)
{
	if (m_pResultWidget != NULL)
	{
		m_pResultWidget->LogString(nLevel,strMsg);
	}
//	slot_LogStringResult(nLevel,strMsg);
//	emit sig_LogStringResult(nLevel,strMsg);
}

void QSttTestCntrFrameBase::ClearAll_ResultUI()
{
	if (m_pResultWidget != NULL)
	{
		m_pResultWidget->ClearAll();
	}
}

void QSttTestCntrFrameBase::CloseIecCapDetect()
{
	if (m_pSttIecRecordMainWidget != NULL)
	{
		m_pSttIecRecordMainWidget->CloseIecCapDetect();
	}
}

void QSttTestCntrFrameBase::LogString(long nLevel, const char *strMsg)
{
	if (nLevel == XLOGLEVEL_RESULT)
	{
		LogStringResult(nLevel,strMsg);
		return;
	}
	else if (nLevel == XLOGLEVEL_ASSIST)
	{
	}

	LogString(nLevel, CString(strMsg));
}
void QSttTestCntrFrameBase::InitPowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent)
{
	if(pParent == NULL)
	{
		pParent  =this;
	}

	if (m_pPowerDiagramWidget == NULL)
	{
		m_pPowerDiagramWidget = new QPowerDiagramWidgetImp(pParent);
		m_pPowerDiagramWidget->setParent(pParent);
	}

	//20230222 ������ͬ�Ļ��಻��ǿ��ת��,��Ŀǰˢ�²��õĶ�ʱ��,�˴�����Ҫ��ֵ  zhouhj
//	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToPower = (CSttRtDataChangeEvent *)m_pPowerDiagramWidget;
	m_pPowerDiagramWidget->setPropertyOfParaSet(GetSttTestResource());

	CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	m_pPowerDiagramWidget->setData(pVOL,pCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);
    
	m_pPowerDiagramWidget->setGeometry(m_rcWorkArea);

	if (m_pActiveWidget != NULL)
	{
		m_pPowerDiagramWidget->hide();
	}
}

void QSttTestCntrFrameBase::UpdatePowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList)
{
	if(m_pPowerDiagramWidget)
	{
#ifndef _PSX_QT_LINUX_
		//windows�˴��ڲ�����ǳ�ʼ����������,������Ҫ��ǰ����һ����Դ����
		m_pPowerDiagramWidget->setPropertyOfParaSet(GetSttTestResource());
#endif
		m_pPowerDiagramWidget->setData(pVOL, pCUR, pVolChList, m_pCurChList);
	}
}

void QSttTestCntrFrameBase::UpdatePowerData()
{
	if((m_pPowerDiagramWidget)&&(!IsTestStarted()))//20230304 zhouhj ���Թ�����,ͨ��ʵʱ���ݸ��²���
	{
		m_pPowerDiagramWidget->initData();
	}
}


void QSttTestCntrFrameBase::InitVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent)
{
// 	if(m_pVectorWidget)
// 	{
// 		if(m_pActiveWidget == m_pVectorWidget)
// 		{
// 			m_pActiveWidget = NULL;
// 		}
// 
// 		delete m_pVectorWidget;
// 		m_pVectorWidget = NULL;
// 	}
	if(pParent == NULL)
	{
		pParent  =this;
	}

	if (m_pVectorWidget == NULL)
	{
		m_pVectorWidget = new QVectorWidget(pParent);
		m_pVectorWidget->setParent(pParent);
	}

	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToVector = m_pVectorWidget;

	//20231109 suyang ���ݲ�ͬģ�� ʸ��ͼ����Ƿ����ӻ���ֵ��ʾ
	CString strCurrUI_ID = GetCurrentUI_ID();
	int nType;

	if(strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowVolTest)
	{
		nType = STT_LowVolDvdt_VECTOR;
	}
	else if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
	{
		nType = STT_LowFreqDfdt_VECTOR;
	}
	else
	{
		nType = STT_COMMON_VECTOR;
	}
	m_pVectorWidget->setPropertyOfParaSet(GetSttTestResource(),nType);

	CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	m_pVectorWidget->setData(pVOL,pCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);

	m_pVectorWidget->setGeometry(m_rcWorkArea);

	if (m_pActiveWidget != m_pVectorWidget)
	{
		m_pVectorWidget->hide();
	}
}

void QSttTestCntrFrameBase::StartVectorWidget()
{
	if(m_pVectorWidget)
	{
		//2023.7.31 zhangyq ��ȡ��ǰMacroID���ж��Ƿ�Ϊ���ʷ���
		CString strCurrUI_ID = GetCurrentUI_ID();
		if(strCurrUI_ID == _T("PowerDirectionTest"))
		{
			CDataGroup oParas;
			oParas.AppendCloneEx(*m_pTestMacroUI_Paras);
			m_pMacroEditView->GetDatas(&oParas);
			m_pVectorWidget->SetVectorMode(VECTOR_POWERWORK,&oParas);
		}
		else
		{
			m_pVectorWidget->SetVectorMode(VECTOR_COMMON, NULL);
		}

		m_pVectorWidget->TimerStart();
	}
}

void QSttTestCntrFrameBase::StartPowerWidget()
{
	if (m_pPowerDiagramWidget)
	{
		m_pPowerDiagramWidget->TimerStart();
	}
}

void QSttTestCntrFrameBase::StopVectorWidget(bool bUpdate)
{
	if(m_pVectorWidget)
	{
		m_pVectorWidget->TimerStop(bUpdate);
	}
}

void QSttTestCntrFrameBase::StopPowerWidget(bool bUpdate)
{
	if(m_pPowerDiagramWidget)
	{
		m_pPowerDiagramWidget->TimerStop(bUpdate);
	}
}

void QSttTestCntrFrameBase::UpdateVectorRange(float fUStart, float fUEnd, float fIStart, float fIEnd)
{
	if(m_pVectorWidget)
	{
		if(fUStart > fUEnd)
		{
			fUEnd = fUStart;
		}
		if(fIStart > fIEnd)
		{
			fIEnd = fIStart;
		}
		m_pVectorWidget->setUIMax(fUEnd, fIEnd);
	}
}

void QSttTestCntrFrameBase::UpdateVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList)
{
	if(m_pVectorWidget)
	{
#ifndef _PSX_QT_LINUX_
		//windows�˴��ڲ�����ǳ�ʼ����������,������Ҫ��ǰ����һ����Դ����
		//20231109 suyang ���ݲ�ͬģ�� ʸ��ͼ����Ƿ����ӻ���ֵ��ʾ
		CString strCurrUI_ID = GetCurrentUI_ID();
		int nType;

		if(strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowVolTest)
		{
			nType = STT_LowVolDvdt_VECTOR;
		}
		else if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
		{
			nType = STT_LowFreqDfdt_VECTOR;
		}
		else
		{
			nType = STT_COMMON_VECTOR;
		}
		m_pVectorWidget->setPropertyOfParaSet(GetSttTestResource(),nType);
#endif
		m_pVectorWidget->setData(pVOL, pCUR, pVolChList, m_pCurChList);
	}
}

void QSttTestCntrFrameBase::UpdateVectorData()
{
	if((m_pVectorWidget)&&(!IsTestStarted()))//20230304 zhouhj ���Թ�����,ͨ��ʵʱ���ݸ��²���
	{
		m_pVectorWidget->updateData();
	}
}

void QSttTestCntrFrameBase::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
{
	CString strCurrUI_ID = GetCurrentUI_ID();
	CString strSearchResultDataID;

	if((strCurrUI_ID != STT_CMD_ATS_MACRO_ID_LowVolTest)&&(strCurrUI_ID != STT_CMD_ATS_MACRO_ID_LowFreqTest))
	{
		return;
	}

	if(pSearchResults == NULL)
	{
		return;
	}

	if(m_pVectorWidget->m_pDiagram == NULL)
	{
		return;
	}

	if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowVolTest)
	{
		strSearchResultDataID = _T("CurrSearchDvdt");
	}
	else
	{
		strSearchResultDataID = _T("CurrSearchDfdt");
	}

	CExBaseList* pSysState = (CExBaseList*)pSearchResults->GetParent()->GetParent();
	CSttMacro* pMacro = (CSttMacro*)pSysState->FindByClassID(STTCMDCLASSID_CSTTMACRO);
	if (pMacro)
	{
		CSttSearchResults* pResults = (CSttSearchResults*)pMacro->GetHead();
		CDvmData* pSearchDfdt = (CDvmData*)pResults->FindByID(/*_T("CurrSearchDfdt")*/strSearchResultDataID);//dingxy 20240702 ��ѹ����du/dt��ֵ�����������޸�
		if (pSearchDfdt)
		{
			CString strValue = pSearchDfdt->m_strValue;
			m_pVectorWidget->m_pDiagram->fCurrSearchValue = atof(strValue.GetString());
			m_pVectorWidget->m_pDiagram->updateDiagram();
			
			//emit sig_updataVectorData();


		}
	}	
}

void QSttTestCntrFrameBase::InitStateMonitor(bool bIsEx, QWidget* pParent)
{
// 	if(m_pStateMonitor)
// 	{
// 		if(m_pActiveWidget == m_pStateMonitor)
// 		{
// 			m_pActiveWidget = NULL;
// 		}
// 
// 		delete m_pStateMonitor;
// 		m_pStateMonitor = NULL;
// 	}
// 
	if (pParent == NULL)
	{
		pParent = this;
	}

	if (m_pStateMonitorWidget == NULL)
	{
		m_pStateMonitorWidget = new QStateMonitorWidgetImp(pParent);
		m_pStateMonitorWidget->setParent(pParent);
	}

// 	CString strCurrUI_ID = GetCurrentUI_ID();
// 	if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
// 	{
// 		m_pStateMonitorWidget->SetPlotDigitMaxMinValue(fre_type);
// 	}
// 	else
// 	{
// 		m_pStateMonitorWidget->SetPlotDigitMaxMinValue(amplitude_type);
// 	}
	float fUMax = 130,fIMax = 30;
	if((g_oSystemParas.m_nHasWeek == 1) && (g_oSystemParas.m_nHasAnalog == 0)&& (g_oSystemParas.m_nHasDigital == 0))
	{
#ifdef _PSX_OS_CENTOS_
		fUMax = 10.000;
#else
		fUMax = 8.300;
#endif
		fIMax = 21.275;
		//SetPlotAcDcMaxMinValue(false,0,fUMax,0,fIMax);
	}
		SetPlotAcDcMaxMinValue(false,0,fUMax,0,fIMax);//20250221  ��ʼ��ʹ�ù̶�ֵ���߼�ģ������������ܴ�
//		SetPlotAcDcMaxMinValue(false,0,(double)g_oLocalSysPara.m_fAC_VolMax,0,(double)g_oLocalSysPara.m_fAC_CurMax);



	m_pStateMonitorWidget->SetSingle(bIsEx);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToProgress = m_pStateMonitorWidget;
	m_pStateMonitorWidget->setGeometry(m_rcWorkArea);

	//dingxiaoya ����رմ��ڱ���
	if (m_pActiveWidget != m_pStateMonitorWidget)
	{
		m_pStateMonitorWidget->hide();
	}
}	

void QSttTestCntrFrameBase::InitInfoWidget(QWidget* pParent)
{
	if (m_pInfoWidget == NULL)
	{
		m_pInfoWidget = new QInfoWidget(pParent);
		m_pInfoWidget->setParent(this);
	}
}

void QSttTestCntrFrameBase::InitFAParasSetDialog(QWidget* pParent)
{
    if(pParent == NULL)
    {
        pParent  =this;
    }

    if (m_pSttFaParasSetDialog == NULL)
    {
        m_pSttFaParasSetDialog = new QSttFAParasSetDialog(pParent);
        m_pSttFaParasSetDialog->setParent(pParent);
    }

    m_pSttFaParasSetDialog->setGeometry(m_rcWorkArea);

    if (m_pActiveWidget != NULL)
    {
        m_pSttFaParasSetDialog->hide();
    }
}

void QSttTestCntrFrameBase::ClearInfoWidget()
{
	if (m_pInfoWidget)
	{
		m_pInfoWidget->clear();
	}
}

void QSttTestCntrFrameBase::InitCharLibWidget(QWidget* pParent)
{
	if (m_pCharLibWidget == NULL)
	{
		//2022-9-3  lijunqing
		m_pCharLibWidget = new QCharEditMainWidget(pParent);   //new QCharLibWidget(pParent);
		m_pCharLibWidget->setParent(this);
	}	
}

void QSttTestCntrFrameBase::InitIecRecordMain()
{
	//IEC����
	if (m_pSttIecRecordMainWidget == NULL)
	{
		m_pSttIecRecordMainWidget = new QSttIecRecordMainWidget(m_gFont, this);
		m_pSttIecRecordMainWidget->setParent(this);
		m_pSttIecRecordMainWidget->hide();
	}
}

void QSttTestCntrFrameBase::InitRemoteCtrl()
{
	if (m_pRemoteCtrlWidget == NULL)
	{
		m_pRemoteCtrlWidget = new QSttMacroParaEditViewRemoteCtrl(this);
		m_pRemoteCtrlWidget->setParent(this);
		m_pRemoteCtrlWidget->hide();
	}
}

void QSttTestCntrFrameBase::UpdateDeviceModelRef()
{
	if (m_pRemoteCtrlWidget != NULL)
	{
		m_pRemoteCtrlWidget->UpdateDeviceModelRef();
		m_pRemoteCtrlWidget->m_nReadCount = 0; //chenling 2024.5.7���µ����Ҫ������������
	} 

	if (m_pEngineClientWidget != NULL)
	{
		m_pEngineClientWidget->m_pCurrSelDvmDataObj = NULL;
	}

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (!g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		return;
	}


	if (g_pTheSttTestApp->GetCurrTestMacroUI() != STT_ORG_MACRO_RemoteCtrlTest)//���ң����������
	{
		if (m_pMacroEditView)
		{
	((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->UpdateDeviceModelRef();
	}
	}

}

void QSttTestCntrFrameBase::InitCommCmdWzdMain(CExBaseList *pParentItem)
{

}

void QSttTestCntrFrameBase::FreeCommCmdWzdMain()
{

}

QWidget* QSttTestCntrFrameBase::GetMacroEditWidget()
{
	if (m_pMacroEditView == NULL)
	{
		return NULL;
	}

	return (QWidget*)m_pMacroEditView->m_pMacroParaEditWnd;
}

CString QSttTestCntrFrameBase::GetMacroEditViewID()
{
	if (m_pMacroEditView == NULL)
	{
		return "";
	}

	if(!m_pMacroEditView->m_pSttItems)
	{
		return "";
	}

	return m_pMacroEditView->m_pSttItems->m_strID;
}

BOOL QSttTestCntrFrameBase::IsHtmlParasEditOpen()
{
    //return (m_pSysParaEditView != NULL);
	//return (m_nActiveWidgetType == ActiveWidgetType_Paras_Html);
}

void QSttTestCntrFrameBase::SetActiveWidget(QWidget *pWidget, ActiveWidgetType nType)
{
	if (m_pActiveWidget==m_pCharLibWidget && m_pActiveWidget!=pWidget)
	{
		CString strFile;

		if(pWidget == NULL)
		{
			strFile = m_pCharLibWidget->m_strCharParasFile;
		}

		SaveCharacteristicsData(strFile);
		TemplateView_Prepare();//zhouhj 2023.7.18 ���뿪�������߽���ʱ,������ͬ������ҳ����
	}

	if (pWidget == NULL)
	{
		if (m_pActiveWidget != NULL)
		{
			m_pActiveWidget->hide();
			m_pActiveWidget = NULL;
		}

		m_nActiveWidgetType = ActiveWidgetType_None;
		m_nPrevActiveWidgetType = ActiveWidgetType_None;
		m_pPrevActiveWidget = NULL;

		return;
	}

	if (m_pActiveWidget != NULL)
	{
		if (m_pActiveWidget == pWidget)
		{
			return;
		}

		m_pActiveWidget->hide();
		pWidget->show();
	}
	else
	{
		m_pActiveWidget = pWidget;
		pWidget->show();
	}

	m_nPrevActiveWidgetType = m_nActiveWidgetType;
	m_pPrevActiveWidget = m_pActiveWidget;
	m_nActiveWidgetType = nType;
	m_pActiveWidget = pWidget;

	m_pActiveWidget->setParent(this);
	m_pActiveWidget->setGeometry(m_rcWorkArea);
	assist_widget_show("", m_pActiveWidget, true);
}

void QSttTestCntrFrameBase::ReturnPrevActiveWidget()
{//�༭Html����ҳ�����������֮ǰ�Ĵ���
	assist_widget_show("", m_pActiveWidget, false);//20220104 zhouhj ��ҳ����ر�ʱ,ȥ������
	m_oTimerHtmlViewReturn.start(50);
}

CString QSttTestCntrFrameBase::GetCharLibWidgetID()
{
	if(m_pCharLibWidget)
	{
		return m_pCharLibWidget->m_strUI_ID;
	}
	return "";
}

void QSttTestCntrFrameBase::slot_SelectTestMacro( CSttMacroTestUI_TestMacroUIRef *pTestMacroUIRef , const CString &strItemsName, const CString &strItemsID)
{
    //if ((g_pTheSttTestApp->m_pTestMacroUI != NULL)&&(m_pSttReportViewHtml!= NULL))//zhouhj 20220219 �ڵڶ��δ�ʱ,ɾ����һ��ѡ��Ĳ��Թ��ܵı���
    //{
    //	m_pSttReportViewHtml->DeleteMacroTestReport("", g_pTheSttTestApp->m_pTestMacroUI->m_strID);
    //}

	g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUIRef->m_strID);
	OpenMacroTestUI(g_pTheSttTestApp->m_pTestMacroUI, strItemsName, strItemsID);

	EndBinStateOnStarting();
	UpdateToolButtons();
	UpdateStartStopButtonByItemCount();
}

//�̵߳��õ�ʱ��ᱼ�����ĳ��źŲ۵���ʽ sf 20220218
void QSttTestCntrFrameBase::on_UpdateEnableState(QString strState)
{
	CString strButtonUpdateState;

	if (strState == STT_TEST_STATE_TEST_FINISHED)//��ť�ĸ���״ֻ̬������,�����кͲ���ֹͣ,ͨ���ȶԵ�ǰ����״̬,���°�ť����ʾ
	{
		strButtonUpdateState = STT_TEST_STATE_TEST_STOPED;
	}
	else
		strButtonUpdateState = strState;

//	CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttTestCntrFrameBase::on_UpdateEnableState errorr......");
	UpdateStartStopTestButton(strButtonUpdateState);

	UpdateEnableState(strButtonUpdateState);
	//������ҳ���ܲ�Ӧʹ���ֶ�����
	if (!HasManuTrigerBtn())
	{
		EnableManualTriggerButton(false);
	}

	if (!g_oSystemParas.HasDigitalInOrOut())//20220805 zhouhj �ڿ�ʼ���ԡ�ֹͣ���Ժ�,��Ҫ�������״̬
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,false,false);
	}
// 	else
// 	{
// 		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,true,true);
// 	}

	if (m_pStatusBar != NULL)
	{
		m_pStatusBar->UpdateEnableState(strButtonUpdateState);
	}
}

void QSttTestCntrFrameBase::UpdateEnableState(const CString &strState)
{

}

void QSttTestCntrFrameBase::slot_MenuButtonClick(QString strID)
{
	if (IsHtmlParasEditOpen())
	{//������˲����༭��ҳ���򲻴����κΰ�ť�����¼�  lijunqing  2022-3-10

		if (strID == STT_CNTR_CMD_Exit)
		{
			CSttFrame_Button *pExitBtn = GetExitBtn();

			if (pExitBtn != NULL)
			{
				QSttToolButtonBase *pButtonUI = (QSttToolButtonBase*)pExitBtn->m_dwItemData;

				if (pButtonUI != NULL)
				{
					pButtonUI->setEnabled(true);
				}
			}
		}

		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,/*_T("���ȹر���ҳ����,����ִ�й�������ť����.")*/g_sLangTxt_Gradient_ClosePerTBF.GetString());//lcq
		return;
	}

	if(strID == STT_CNTR_CMD_Exit)
	{
		m_bHasClosedUI = TRUE;
		SaveCharacteristicsData();
		CloseIecCapDetect();
		setEnabled(false);
		m_pResultWidget->LogString(0, /*"�ȴ����Է���ֹͣ��ر�."*/g_sLangTxt_Gradient_WaitSASD.GetString()); //lcq
		m_pTestCtrlCntrBase->CloseTest(STT_CMD_Send_Async);
		this->close();
        QApplication::setOverrideCursor(Qt::BlankCursor);    // xueyangfan ���������
		return;
	}
	if  (strID ==  STT_CNTR_CMD_Menu)
	{
		OnCmd_Menu();
		return;
	}

	Before_OnCmd();

	if  (strID ==  STT_CNTR_CMD_StartTest)
	{
		OnCmd_StartTest();
	}
	if  (strID ==  STT_CNTR_CMD_TestThis)
	{
		OnCmd_TestThis();
	}
	else if  (strID ==  STT_CNTR_CMD_ManuTriger)
	{
		OnCmd_ManuTriger();
	}
	else if  (strID ==  STT_CNTR_CMD_StopTest)
	{
		OnCmd_StopTest();
	}
	else if  (strID ==  STT_CNTR_CMD_AddMacro)
	{
		OnCmd_AddMacro(TRUE);
	}
	else if  (strID ==  STT_CNTR_CMD_ItemList)
	{
		OnCmd_ItemList();
	}
	else if  (strID ==  STT_CNTR_CMD_TemplateView)
	{
		OnCmd_TemplateView();
	}
	else if  (strID ==  STT_CNTR_CMD_ReportView)
	{
		OnCmd_ReportView();
	}
	else if  (strID ==  STT_CNTR_CMD_HardConfig)
	{
		OnCmd_HardConfig();
	}
	else if  (strID ==  STT_CNTR_CMD_IECConfig)
	{
		OnCmd_IECConfig();
	}
	else if  (strID ==  STT_CNTR_CMD_AinDataMapConfig)
	{
		OnCmd_AinDataMapConfig();
	}
	else if  (strID ==  STT_CNTR_CMD_VectorDrawView)
	{
		OnCmd_VectorDrawView();
	}
	else if  (strID ==  STT_CNTR_CMD_WaveDrawView)
	{
		OnCmd_WaveDrawView();
	}
	else if  (strID ==  STT_CNTR_CMD_StateDrawView)
	{
		OnCmd_StateDrawView();
	}
	else if (strID == STT_CNTR_CMD_PowerDrawView)
	{
		OnCmd_PowerDrawView();
	}
	else if  (strID ==  STT_CNTR_CMD_CharDrawView)
	{
		OnCmd_CharDrawView();
	}
	else if  (strID ==  STT_CNTR_CMD_NewTest)
	{
		OnCmd_NewTest();
	}
	else if  (strID ==  STT_CNTR_CMD_OpenTemplate)
	{
		OnCmd_OpenTemplate();
	}
	else if  (strID ==  STT_CNTR_CMD_OpenTest)
	{
		OnCmd_OpenTest();
	}
	else if  (strID ==  STT_CNTR_CMD_SaveTemplate)
	{
		OnCmd_SaveTemplate();
	}
	else if  (strID ==  STT_CNTR_CMD_SaveAsTemplate)
	{
		OnCmd_SaveAsTemplate();
	}
	else if  (strID ==  STT_CNTR_CMD_SaveTest)
	{
		OnCmd_SaveTest();
	}
	else if  (strID ==  STT_CNTR_CMD_SaveAsTest)
	{
		OnCmd_SaveAsTest();
	}
	else if  (strID ==  STT_CNTR_CMD_SaveAsRpt)
	{
		OnCmd_SaveAsRpt();
	}
	else if (strID == STT_CNTR_CMD_ExportWordRpt)
	{
		OnCmd_ExportWordRpt();
	}
	else if  (strID ==  STT_CNTR_CMD_SystemParas)
	{
		OnCmd_SystemParas();
	}
	else if  (strID ==  STT_CNTR_CMD_GeneralParas)
	{
		OnCmd_GeneralParas();
	}
// 	else if  (strID ==  STT_CNTR_CMD_SwitchSet)
// 	{
// 		8OnCmd_SwitchSet();
// 	}
	else if  (strID ==  STT_CNTR_CMD_DcSet)
	{
		OnCmd_DcSet();
	}
	else if  (strID ==  STT_CNTR_CMD_OutputPower)
	{
		OnCmd_OutputPower();
	}
	else if  (strID ==  STT_CNTR_CMD_DeviceCom)
	{
		OnCmd_DeviceCom();
	}
	else if  (strID ==  STT_CNTR_CMD_ItemListView)
	{
		OnCmd_ItemListView();
	}
	else if  (strID ==  STT_CNTR_CMD_DeviceComView)
	{
		OnCmd_DeviceComView();
	}
	else if  (strID ==  STT_CNTR_CMD_LangSetting)
	{
		OnCmd_LangSettingView();
	}
	else if  (strID ==  STT_CNTR_CMD_ReportSetting)
	{
		OnCmd_ReportSetting();
	}
	else if  (strID ==  STT_CNTR_CMD_ChRsMaps)
	{
		OnCmd_ChRsMaps();
	}
	else if  (strID ==  STT_CNTR_CMD_AuxDCOutput)
	{
		OnCmd_AuxDCOutput();
	}
// 	else if  (strID ==  STT_CNTR_CMD_CharaView)  //20220803 zhouhj �ظ�ɾ��
// 	{
// 		OnCmd_CharaView();
// 	}
	else if  (strID ==  STT_CNTR_CMD_SequenceView)
	{
		OnCmd_SequenceView();
	}
	else if  (strID ==  STT_CNTR_CMD_InfoView)
	{
		OnCmd_InfoView();
	}
	else if  (strID ==  STT_CNTR_CMD_LogView)
	{
		OnCmd_LogView();
	}
	else if  (strID ==  STT_CNTR_CMD_VersionInfo)
	{
		OnCmd_VersionInfo();
	}
	else if (strID ==  STT_CNTR_CMD_AuxIPSet)
	{
		OnCmd_AuxIPSet();
	}
	else if  (strID ==  STT_CNTR_CMD_Liveupdate)
	{
		OnCmd_Liveupdate();
	}
	else if (strID ==  STT_CNTR_CMD_ULiveupdate)
	{
		OnCmd_ULiveupdate();
	}
	else if  (strID ==  STT_CNTR_CMD_LiveupdateDevice)
	{
		OnCmd_LiveupdateDevice();
	}
	else if  (strID ==  STT_CNTR_CMD_CloudConfig)
	{
		OnCmd_CloudConfig();
	}
	else if  (strID ==  STT_CNTR_CMD_UpdateAdjCoef)
	{
		OnCmd_UpdateAdjCoef();
	}
	else if  (strID ==  STT_CNTR_CMD_RegisterRemoteTest)
	{
		OnCmd_RegisterRemoteTest();
	}
	else if  (strID ==  STT_CNTR_CMD_RemoteRegistAssist)
	{
		OnCmd_RemoteRegistAssist();
	}
	else if  (strID ==  STT_CNTR_CMD_DownloadTestTemplate)
	{
		OnCmd_DownloadTestTemplate();
	}
	else if  (strID ==  STT_CNTR_CMD_DownloadPpTemplate)
	{
		OnCmd_DownloadPpTemplate();
	}
	else if  (strID ==  STT_CNTR_CMD_UploadingReport)
	{
		OnCmd_UploadingReport();
	}
	else if  (strID ==  STT_DEBUG_SetDatas)
	{
		OnCmd_DebugSetDatas();
	}
	else if  (strID ==  STT_DEBUG_SetDatasFile1)
	{
		OnCmd_DebugSetDatasFile1();
	}
	else if  (strID ==  STT_DEBUG_SetDatasFile2)
	{
		OnCmd_DebugSetDatasFile2();
	}
	else if  (strID ==  STT_DEBUG_SaveDatasFile)
	{
		OnCmd_DebugSaveDatasFile();
	}
	else if  (strID ==  STT_DEBUG_GetDatas)
	{
		OnCmd_DebugGetDatas();
	}
	else if  (strID ==  STT_DEBUG_UpdateReport)
	{
		OnCmd_DebugUpdateReport();
	}
	else if  (strID ==  STT_DEBUG_FillReport)
	{
		OnCmd_DebugFillReport();
	}
	else if  (strID ==  STT_DEBUG_ItemStateChanged)
	{
		OnCmd_DebugItemStateChanged();
	}
	else if  (strID ==  STT_DEBUG_OutPutWidget)
	{
		OnCmd_DebugOutPutWidget();
	}
	else if  (strID ==  STT_DEBUG_StartTest)
	{
		OnCmd_DebugStartTest();
	}
	else if  (strID ==  STT_DEBUG_StopTest)
	{
		OnCmd_DebugStopTest();
	}
	else if  (strID ==  STT_CNTR_CMD_ConnectApp)
	{
		OnCmd_ConnectApp();
	}
	else if  (strID ==  STT_CNTR_CMD_Debug)
	{
		OnCmd_Debug();
	}
	else if  (strID ==  STT_DEBUG_SaveTest)
	{
		OnCmd_DebugSaveTest();
	}
	else if  (strID ==  STT_DEBUG_GenForDebug)
	{
		OnCmd_DebugGenForDebug();
	}
	else if  (strID ==  STT_DEBUG_GenTemplate)
	{
		OnCmd_DebugGenTemplate();
	}
	else if  (strID ==  STT_DEBUG_SaveAsSysFiles)
	{
		OnCmd_DebugSaveAsSysFiles();
	}
	else if  (strID ==  STT_CNTR_CMD_IecCap)
	{
		OnCmd_IecCap();
	}
	else if  (strID ==  STT_CNTR_CMD_IecCapWriteFile)
	{
		OnCmd_IecCapWriteFile();
	}
	else if  (strID ==  STT_CNTR_CMD_IecCapDebugHead)
	{
		OnCmd_IecCapDebugHead();
	}
	else if  (strID ==  STT_CNTR_CMD_ScreenShot)
	{
		OnCmd_ScreenShot();
	}
	else if (strID == STT_CNTR_CMD_FAParasSetDialog)
	{
		OnCmd_FAParasSetDialog();
	}
	else if (strID == STT_CNTR_CMD_CustomSet)
	{
		OnCmd_CustomSet();
	}
	else if (strID == STT_CNTR_CMD_Assist)
	{//2022-12-02  lijunqing
		OnCmd_Assist();
	}
	else if (strID == STT_CNTR_CMD_SelSCLFile)
	{
		OnCmd_SelSCLFile();
	}
	else if (strID == STT_CNTR_CMD_SaveEdit)
	{
		OnCmd_SaveEdit();
	}
	else if (strID == STT_CNTR_CMD_FileMngr)
	{
		OnCmd_FileMngr();
	}
	else if (strID == STT_CNTR_CMD_LumPowerView)
	{
		OnCmd_LumPowerView();
	}
	else if (strID == STT_CNTR_CMD_PpIotEngineClient)
	{
		OnCmd_PpIotEngineClient();
	}
	else if (strID == STT_CNTR_CMD_CommConfig)
	{
		OnCmd_CommConfiguration();
	}
	else if (strID == STT_CNTR_CMD_PkgMonitor)
	{
		OnCmd_PkgMonitor();
	}
	else if (strID == STT_CNTR_CMD_RemoteCtrl)
	{
		OnCmd_RemoteCtrl();
	}
	else if (strID == STT_CNTR_CMD_PpXmlFileMngr)
	{
		OnCmd_PpXmlFileMngr();
	}
	else if (strID == STT_CNTR_CMD_DvmFileMngr)
	{
		OnCmd_DvmFileMngr();
	}
	else if (strID == STT_CNTR_CMD_NetworkConfig)
	{
		OnCmd_NetworkConfig();
	}
	else if (strID == STT_CNTR_CMD_ClearReportRslts)
	{
		OnCmd_ClearReportRslts();
	}
	else if (strID == STT_CNTR_CMD_TransPcapFile)
	{
		OnCmd_TransPcapFile();
	}
	else if (strID == STT_CNTR_CMD_ImportDvmFile)
	{
		OnCmd_ImportDvmFile();
	}
	else if (strID == STT_CNTR_CMD_OutputDebug)
	{
		OnCmd_OutputDebug();
	}
	else if (strID == STT_CNTR_CMD_Minimize)//2024-2-26 zhouyangyong ���������С��
	{
		OnCmd_Minimize();
	}
	else if (strID == STT_CNTR_CMD_BinConfig)
	{
		OnCmd_BinConfig();
	}
	else if (strID == STT_CNTR_CMD_BinBoutCommMap)
	{
		onCmd_BinBoutCommMap();
	}
}

void QSttTestCntrFrameBase::slot_SendChMapsConfig()
{
	if (IsTestStarted())
	{
		return;
	}
	Cmd_SendChMapsConfig();
	m_bIsRtDataUpdateChMaps_System = FALSE;
// CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("����ͨ��ӳ��."));
	emit sig_UpdateTestResource();//�����źŸ��������Դ

	
}

//yyj 
bool QSttTestCntrFrameBase::GenerateTemplate(CExBaseObject *pParentItems, const CString &strItemsName, const CString &strItemsID
											 , long nRepeatTimes, long nRptTitle, long nTitleLevel)
{
// 	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("�ײ����ģ������."));
	bool bTemplateGened = false;
	long nRet = m_pTestCtrlCntrBase->Ats_GenerateTemplate();
	
	if (m_bHasClosedUI)
	{
		return bTemplateGened;//����رհ�ť��,���ٸ��´˴�
	}

	if (nRet == STT_CMD_ExecStatus_SUCCESS)	//ģ���������
	{
		bTemplateGened = true;
		if (m_bIsRtDataUpdateChMaps_System)
		{
			emit sig_SendChMapsConfig();
		}
// 		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("�ײ����ģ���������."));
	}
	else
	{
#ifdef _PSX_QT_LINUX_
		CString strTitile,strMsg;
		strTitile = g_sLangTxt_Message/*"��ʾ"*/;
		strMsg = g_sLangTxt_Native_LowLevelTmplFail/*"�ײ����ģ������ʧ��."*/;
		sig_MsgBox(strTitile,strMsg);
//		CXMessageBox::information(this, strTitile, strMsg);
#endif
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("�ײ����ģ������ʧ��.")*/g_sLangTxt_Native_LowLevelTmplFail.GetString());
	}

	return bTemplateGened;
}

bool QSttTestCntrFrameBase::IsTestStarted()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return false;
	}

 	return m_pTestCtrlCntrBase->IsTestStarted();
}

bool QSttTestCntrFrameBase::IsStateTest()
{
	if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_StateTest)
	{
		return true;
	}
	else if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_SmvAbnTest)
	{
		return true;
	}
	else if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_GseAbnTest)
	{
		return true;
	}
	else
		return false;
}

bool QSttTestCntrFrameBase::IsUseStateIndex()
{
	if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_StateTest)
	{
		return true;
	}
	else if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_SmvAbnTest)
	{
		return true;
	}
	else if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_GseAbnTest)
	{
		return true;
	}
	else if (CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_VolTimeTypeSecTest || 
		CSttMacroParaEditViewMngr::GetCurMacroID() ==  STT_ORG_MACRO_VolTimeTypeIntTest || 
		CSttMacroParaEditViewMngr::GetCurMacroID() ==  STT_ORG_MACRO_VolCurTypeSecTest || 
		CSttMacroParaEditViewMngr::GetCurMacroID() ==  STT_ORG_MACRO_VolCurTypeIntTest || 
		CSttMacroParaEditViewMngr::GetCurMacroID() ==  STT_ORG_MACRO_AdaptiveTypeSecTest)
	{
		return true;
	}
	else
		return false;
}

bool QSttTestCntrFrameBase::IsMultiTestItems()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return false;
	}

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		if (g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_MUAutoTest)
		{
			return true;
		}

		return false;
	}

	CString strMacroID = g_pTheSttTestApp->GetCurrTestMacroUI();

//	if (strMacroID == STT_HTML_MACRO_CBOperateTest)
//	{
//		return false;
//	}

	return true;
}

bool QSttTestCntrFrameBase::HasCharChanged()
{
	if (m_pCharLibWidget == NULL)
	{
		return false;
	}

	return m_pCharLibWidget->m_bCharChanged;
}

void QSttTestCntrFrameBase::AddTestPoints(double dX, double dY,BOOL bAct)
{
	m_pSttCharacterDrawPng->AddSearchPoint(dX, dY, bAct);
}

void QSttTestCntrFrameBase::SetCharChanged(bool bCharChanged)
{
	if (m_pCharLibWidget == NULL)
	{
		return;
	}

	m_pCharLibWidget->m_bCharChanged = bCharChanged;
}

void QSttTestCntrFrameBase::UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas)
{
	if ((m_pCharLibWidget == NULL) || (pCurrentUIParas == NULL))
	{
		return;
	}

	m_pCharLibWidget->UpdateCharScriptByUIParas(pCurrentUIParas);
}

void QSttTestCntrFrameBase::InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget)
{
	CString strCurrUI_ID = GetCurrentUI_ID();

	if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
	{
		type = fre_type;
	}

	if (m_pStateMonitorWidget)
	{
		m_pStateMonitorWidget->InitStateMonitor(nChannel, type, bStart, pPlotExWidget);
	}
}

void QSttTestCntrFrameBase::StartStateMonitor()
{
	if (m_pStateMonitorWidget)
	{
		m_pStateMonitorWidget->StartStateMonitor();
	}
}

void QSttTestCntrFrameBase::StopStateMonitor()
{
	if (m_pStateMonitorWidget)
	{
		m_pStateMonitorWidget->StopStateMonitor();
	}
}

void QSttTestCntrFrameBase::SetPlotAcDcMaxMinValue( bool bDC,double fUMin,double fUMax,double fIMin,double fIMax )
{
	CString strCurrUI_ID = GetCurrentUI_ID();

	if (m_pStateMonitorWidget)
	{
		
		if(bDC)
		{
			//if (m_pStateMonitorWidget)
			{
				m_pStateMonitorWidget->SetPlotDigitMaxMinValue(amplitude_type,(double)g_oLocalSysPara.m_fDC_VolMin,(double)g_oLocalSysPara.m_fDC_VolMax,
			(double)g_oLocalSysPara.m_fDC_CurMin,(double)g_oLocalSysPara.m_fDC_CurMax);

			}
			
		}
		else
		{
			//if (m_pStateMonitorWidget)
			{
				if (strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest || strCurrUI_ID == STT_ORG_MACRO_FreqOutputTest)//��Ƶ�����Ҫ��ʾƵ��
				{
					m_pStateMonitorWidget->SetPlotDigitMaxMinValue(fre_type,40, 60, 40, 60);
				}
				else
				{
					m_pStateMonitorWidget->SetPlotDigitMaxMinValue(amplitude_type,fUMin,fUMax,fIMin,fIMax);
				}

				
			}
			
		}

	}
}

void QSttTestCntrFrameBase::CloseMenu()
{
	emit sig_CloseMenu();
}

void QSttTestCntrFrameBase::SetVectorGradient(bool bIsGradient)
{
	if (m_pVectorWidget)
	{
		m_pVectorWidget->setAutoChanged(bIsGradient);
	}
}

void QSttTestCntrFrameBase::keyPressEvent(QKeyEvent *event)
{
	keyPressEvent_Exec(event->key());
}

bool QSttTestCntrFrameBase::keyPressEvent_Exec(int nKeyValue)
{
	bool bRet = false;
	
	if(m_pStartTestBtn != NULL)
	{
 	if(nKeyValue == Qt::Key_F2) 
 	{
			if (!IsTestStarted() && m_pStartTestBtn->m_strID == STT_CNTR_CMD_StartTest)
		{
			OnCmd_StartTest();
		}
		
 		bRet = true;
 	} 
 	else if(nKeyValue == Qt::Key_Escape) 
	{
			if (IsTestStarted() && m_pStartTestBtn->m_strID == STT_CNTR_CMD_StopTest)
		{
			OnCmd_StopTest();
		}
 
 		bRet = true;
 	}
 	else if(nKeyValue == Qt::Key_F3) 
 	{

			if (m_pManualTriggerBtn != NULL)
			{
						QSttToolButtonBase *pManualTriggerBtn = (QSttToolButtonBase*)m_pManualTriggerBtn->m_dwItemData;
				if(HasManuTrigerBtn() && pManualTriggerBtn->isEnabled())
		{
 		OnCmd_ManuTriger();
		}
 		
 		bRet = true;
 	}
		}
	}
 	
	return bRet;
}


void QSttTestCntrFrameBase::slot_Timer_AutoSave()
{
	return;
}

void QSttTestCntrFrameBase::slot_Timer()
{
//	return;
	OnEventMsg();
	CAutoSimpleLock oLock(m_oCriticSection_ItemStateList);

	if(m_oItemStateList.CanRead())
	{
		CExBaseObject *pObj = m_oItemStateList.Read();
		slot_OnItemStateChanged_Frame(pObj);
		//			emit sig_OnItemStateChanged_Frame(&pObj);
	}
	//if(m_pItemState)
	//{
	//	emit sig_OnItemStateChanged_Frame(m_pItemState);
	//}

	/*������߳�ͬʱemit��ɵ�����
	if(IsTestAppConnect())
	{
		emit sig_OnViewTestLink(TRUE);
	}
	else
	{
		emit sig_OnViewTestLink(FALSE);
	}
	*/
}

void QSttTestCntrFrameBase::OnViewTestStop_Common(BOOL bItemChanged)
{
	StopStateMonitor();

	if (!bItemChanged)
	{
		StopVectorWidget();
		StopPowerWidget();
	}
}

void QSttTestCntrFrameBase::OnEventMsg()
{
	if(m_pTestCtrlCntrBase == NULL)
	{
		return;
	}

	if(!IsTestStarted())
	{
		return;
	}

	PrintEventInfo();
}

void QSttTestCntrFrameBase::UpdateEventMsg(CEventResult *pEventInfo)
{
	pEventInfo->Copy(&m_pTestCtrlCntrBase->m_oCurrEventResult);

	if (!IsAutoTest())
	{
	if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichInChanged 
		|| m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichOutChanged
		|| m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_RETTYPE_UPDATE)
	{
		SysStateReport_OnSwitchChanged(pEventInfo);
	}

	if(m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichInChanged 
		|| m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichOutChanged
		|| m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_EVENT_OnTestStarted
		|| m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_RETTYPE_UPDATE)
	{
		if(m_pStateMonitorWidget)
		{
			for (int i = 0; i < g_nBinCount; i++)
			{
				m_pStateMonitorWidget->AddBinBoutPoint(i, pEventInfo->m_fTime, pEventInfo->m_BinIn[i]);
			}
			for (int i = 0; i < g_nBoutCount; i++)
			{
				m_pStateMonitorWidget->AddBinBoutPoint(i + g_nBinCount, pEventInfo->m_fTime, pEventInfo->m_BinOut[i]);
			}
		}
	}

	if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichInChanged)
	{
		//2024/1/3 wangjunsheng  ���� ��ѹģ�鲻��ʾ�����λ
		CString strCurrUI_ID = GetCurrentUI_ID();
		if(strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowVolTest || strCurrUI_ID == STT_CMD_ATS_MACRO_ID_LowFreqTest)
		{
			return;
		}
		m_pInfoWidget->ShowBinInResultMsg(&m_pTestCtrlCntrBase->m_oCurrEventResult);
	}
	if (IsUseStateIndex())
	{
		//dingxy 20240523 ������������д��ʽ
	// 		if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_fActTime>0.00001)
	// 	{
	// 			CString strResultMsg;
	// 			strResultMsg.Format(g_sLangTxt_Native_StatusLDActTime.GetString()/*_T("״̬%ld����ʱ��%.4lfs.")*/,
	// 				pEventInfo->m_nCurrStateIndex+1,pEventInfo->m_fActTime);
	// 			CLogPrint::LogString(XLOGLEVEL_RESULT,strResultMsg);
	// 	}

		m_pInfoWidget->InsertSwitchInfoTable(&m_pTestCtrlCntrBase->m_oCurrEventResult,true);
	}
	else
	{
		m_pInfoWidget->InsertSwitchInfoTable(&m_pTestCtrlCntrBase->m_oCurrEventResult);
	}

	if (m_pMacroEditView != NULL)
	{
		m_pMacroEditView->UpdateEventMsg(&m_pTestCtrlCntrBase->m_oCurrEventResult);
	}

	//yzj 2023.11.06 ״̬�����ظ�����Ӧ���л�����һ��״̬
	if(m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnStateChanged
		|| m_pTestCtrlCntrBase->m_oCurrEventResult.m_strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		SysStateReport_OnStateChanged(pEventInfo);
	}
	}

	if(IsTestStarted())
	{
		UpdateToolButtons();
	}
}

void QSttTestCntrFrameBase::PrintEventInfo()
{
	CExBaseList oEventInfoList;
	m_pTestCtrlCntrBase->GetEventInfo(oEventInfoList);
	POS pos = oEventInfoList.GetHeadPosition();
	CEventResult *p = NULL;

	while(pos != NULL)
	{
		p = (CEventResult *)oEventInfoList.GetNext(pos);
		UpdateEventMsg(p);
	}

	oEventInfoList.RemoveAll();
}

bool QSttTestCntrFrameBase::IsTestAppConnect()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return false;
	}

	return m_pTestCtrlCntrBase->IsTestAppConnect();
}

void QSttTestCntrFrameBase::UpdateToolButtons_ParaEdit()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (!g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		return;
	}

	CSttMacroParaEditViewOriginal *pView = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;

	if (pView == NULL)
	{
		return;
	}

	UpdateToolButtons_Bin();
}

void QSttTestCntrFrameBase::UpdateToolButtons_Bin()
{
	QSttToolButtonBase *pButton = NULL;
	BOOL bHasChangedShowState = FALSE;

	//���루���10��)
	for(int i=0; i<MAX_BINARYOUT_COUNT; i++)
	{
		CString str;
		str.Format(_T("Bin%03d"),i+1);
		pButton = m_oDataBtnsMngr.FindButtonByID(str);

		if (pButton == NULL)
		{
			continue;
		} 

		if (i>=g_nBinCount)
		{
			if (pButton->isVisible())
			{
				pButton->ShowBtn(false);
				bHasChangedShowState = TRUE;
			}
		} 
		else if (!pButton->isVisible())
		{
			pButton->ShowBtn(true);
			bHasChangedShowState = TRUE;
		}

		if (m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[i].nSelect)
		{	
			if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinIn[i] != 0 && IsTestStarted())
			{
				pButton->SetPic(3);
			}
			else
			{
				pButton->SetPic(1);
			}
		}
		else
		{
			if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinIn[i] != 0)
			{
				pButton->SetPic(2);
			}
			else
			{
				pButton->SetPic(0);
			}
		}
	}

	if (bHasChangedShowState)
	{
		AdjustStatusBarButtons();
	}
}

void QSttTestCntrFrameBase::InitBinaryIn_WebUI(CDataGroup *pParas)
{
	if (pParas == NULL)
	{
		return;
	}

	CDvmData *pCurrData = (CDvmData*)pParas->FindByID("BinSelect");
	long nTmpValue = 0;

	if (pCurrData != NULL)
	{
		nTmpValue = CString_To_long(pCurrData->m_strValue);

		if (nTmpValue == 0)
		{
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[0].nSelect = 1;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[1].nSelect = 1;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[2].nSelect = 1;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[3].nSelect = 1;

			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[4].nSelect = 0;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[5].nSelect = 0;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[6].nSelect = 0;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[7].nSelect = 0;
		} 
		else
		{
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[0].nSelect = 0;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[1].nSelect = 0;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[2].nSelect = 0;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[3].nSelect = 0;

			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[4].nSelect = 1;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[5].nSelect = 1;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[6].nSelect = 1;
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[7].nSelect = 1;
		}

		return;
	}

	CString strBinID;
	CExBaseList *pBinList = NULL;
	CExBaseObject *pBinValue = NULL;
	POS pos = NULL;
	BOOL bFind = FALSE;

	for(int nIndex = 0;nIndex<8;nIndex++)
	{
		strBinID.Format(_T("Bin%d"),nIndex+1);
		pBinList = (CExBaseList *)m_oBinaryInParas.FindByID(strBinID);

		if (pBinList != NULL)
		{
			pos = pBinList->GetHeadPosition();

			while(pos)
			{
				pBinValue = pBinList->GetNext(pos);
				pCurrData = (CDvmData*)pParas->FindByID(pBinValue->m_strID);

				if (pCurrData != NULL)
				{
					m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[nIndex].nSelect = CString_To_long(pCurrData->m_strValue);
					bFind = TRUE;
					break;
				}
			}
		}
	}

	if (!bFind)
	{
		for(int nIndex = 0;nIndex<g_nBinCount;nIndex++)
		{
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binIn[nIndex].nSelect = 1;
		}
	}
}

void QSttTestCntrFrameBase::UpdateToolButtons_Bout()
{
	QSttToolButtonBase *pButton = NULL;
	BOOL bHasChangedShowState = FALSE;

	for(int i=0; i<MAX_BINARYOUT_COUNT; i++)
	{
		CString str;
		str.Format(_T("Bout%03d"),i+1);
		pButton = m_oDataBtnsMngr.FindButtonByID(str);

		if (pButton == NULL)
		{
			continue;
		}

		if (i>=g_nBoutCount)
		{
			if (pButton->isVisible())
			{
				pButton->ShowBtn(false);
				bHasChangedShowState = TRUE;
			}
		} 
		else if (!pButton->isVisible())
		{
			pButton->ShowBtn(true);
			bHasChangedShowState = TRUE;
		}

		if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOut[i] != 0 && IsTestStarted())
		{
			pButton->SetPic(2);
		}
		else
		{
			pButton->SetPic(0);
		}
	}

	if (bHasChangedShowState)
	{
		AdjustStatusBarButtons();
	}
}

void QSttTestCntrFrameBase::UpdateToolButtons_Light()
{
	if (IsTestStarted())
	{
		m_oDataBtnsMngr.UpdatePicSet("Run",STT_LIGHT_BTN_INDEX_Run);
	}
	else
	{
		m_oDataBtnsMngr.UpdatePicSet("Run",STT_LIGHT_BTN_INDEX_ShutOff);
	}

// 	if (m_pTestCtrlCntrBase->m_oCurrEventResult.m_nUdc != 0)
// 	{
// 		m_oDataBtnsMngr.UpdatePicSet("Udc",STT_LIGHT_BTN_INDEX_Yellow);
// 	}
// 	else
// 	{
// 		m_oDataBtnsMngr.UpdatePicSet("Udc",STT_LIGHT_BTN_INDEX_Red);
// 	}
	//dingxy 20250320 ���ݻ�ȡ��Դ�ı�
	if (m_fUdc != 0)
		m_oDataBtnsMngr.UpdatePicSet("Udc",STT_LIGHT_BTN_INDEX_Yellow);
	else
		m_oDataBtnsMngr.UpdatePicSet("Udc",STT_LIGHT_BTN_INDEX_Red);

	if (g_pTheSttTestApp->m_pTestCtrlCntr == NULL)
	{
		return;
	}

	CExBaseList *pTestGlobalParas = g_pTheSttTestApp->m_pTestCtrlCntr->GetTestGlobalParas();

	if (pTestGlobalParas == NULL)
	{
		return;
	}

	if (/*m_pTestCtrlCntrBase->m_oCurrEventResult.m_nIOverLoad*/stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_IBreak, 0) > 0)
	{
		//m_oDataBtnsMngr.UpdatePicSet("OI",STT_LIGHT_BTN_INDEX_Yellow);
		m_oDataBtnsMngr.UpdatePicSet("OI",STT_LIGHT_BTN_INDEX_Red);
		if (IsTestStarted())
		{
			//CLogPrint::LogString(XLOGLEVEL_RESULT, _T("�����ǵ�����·"));
		}
	}
	else
	{
		m_oDataBtnsMngr.UpdatePicSet("OI",STT_LIGHT_BIN_INDEX_Black);
		//m_oDataBtnsMngr.UpdatePicSet("OI",STT_LIGHT_BTN_INDEX_Red);
	}

	if (/*m_pTestCtrlCntrBase->m_oCurrEventResult.m_nUOverLoad*/stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_UShort, 0) > 0)
	{
		//m_oDataBtnsMngr.UpdatePicSet("U",STT_LIGHT_BTN_INDEX_Yellow);
		m_oDataBtnsMngr.UpdatePicSet("U",STT_LIGHT_BTN_INDEX_Red);
		if (IsTestStarted())
		{
			//CLogPrint::LogString(XLOGLEVEL_RESULT, _T("�����ǵ�ѹ��·"));
		}
	} 
	else
	{
		//m_oDataBtnsMngr.UpdatePicSet("U",STT_LIGHT_BTN_INDEX_Red);
		m_oDataBtnsMngr.UpdatePicSet("U",STT_LIGHT_BIN_INDEX_Black);
	}

	if (/*m_pTestCtrlCntrBase->m_oCurrEventResult.m_nOverHeat*/stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_OverHeat, 0) > 0)
	{
		//m_oDataBtnsMngr.UpdatePicSet("OH",STT_LIGHT_BTN_INDEX_Yellow);
		//dingxy 20241016 ���ղ���Ҫ����ظ澯����ʱ�޸�Ϊ��ɫ
		m_oDataBtnsMngr.UpdatePicSet("OH",STT_LIGHT_BTN_INDEX_Red);
		if (IsTestStarted())
		{
			//CLogPrint::LogString(XLOGLEVEL_RESULT, _T("�������¶ȹ���"));
		}
	} 
	else
	{
		//m_oDataBtnsMngr.UpdatePicSet("OH",STT_LIGHT_BTN_INDEX_Red);
		//���ظ澯����ʱ�޸�Ϊ��ɫ
		m_oDataBtnsMngr.UpdatePicSet("OH",STT_LIGHT_BIN_INDEX_Black);
	}
}

tmt_BinaryConfig* QSttTestCntrFrameBase::GetBinaryConfig()
{
	return &m_pTestCtrlCntrBase->m_oBinaryConfig;
}

//2022-4-3  lijunqing ��ʱ�����ǲ�ʹ�õ����
void QSttTestCntrFrameBase::UpdateToolButtons()
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin UpdateToolButtons -  >>");	}

	//UpdateToolButtons_ParaEdit();
//	QSttToolButtonBase *pButton = m_oDataBtnsMngr.FindButtonByID("Run");
	UpdateToolButtons_FloatPanel();
	UpdateToolButtons_Light();
	UpdateToolButtons_Bin();
	UpdateToolButtons_Bout();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateToolButtons -  >>");	}
}

//m_pTestCtrlCntrBase���Ǹ������Ķ���û�а취�ŷŵ������ �����ٿ��Ƿű�ĵط� sf 20220219
void QSttTestCntrFrameBase::SyncBinOutDatas( BOOL b/*=TRUE*/ )
{
	CSttMacroParaEditViewOriginal *pView = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;

	for(int i = 0;i <  MAX_BINARYOUT_COUNT; i++)
	{
		if(b)		//�ӽṹ�����->��ǰ�¼�����
		{
			m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOut[i] = m_pTestCtrlCntrBase->m_oBinaryConfig.m_binOut[i].nState;
		}
		else
		{
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binOut[i].nState = m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOut[i];
		}
	}

	for (int j = 0;j < MAX_ExBINARY_COUNT;j++)
	{
		if (b)
		{
			m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOutEx[j] = m_pTestCtrlCntrBase->m_oBinaryConfig.m_binOutEx[j].nState;
		}
		else
		{
			m_pTestCtrlCntrBase->m_oBinaryConfig.m_binOutEx[j].nState = m_pTestCtrlCntrBase->m_oCurrEventResult.m_BinOutEx[j];
		}
	}
}

void QSttTestCntrFrameBase::SysStateReport_OnSwitchChanged(CEventResult *pEventInfo)
{
/*UpdateToolButtons()����
	ASSERT(pEventInfo != NULL);

	CDataGroup dataGroup;
	if(g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		pEventInfo->GenEventDataGroup(dataGroup,&((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->m_oBinaryConfig);
	}
	else
	{
		pEventInfo->GenEventDataGroup(dataGroup,NULL);
	}

	m_oDataBtnsMngr.UpdataDataButtons(&dataGroup);
*/
}

void QSttTestCntrFrameBase::Ats_UpdateParameter()
{
	CDataGroup oRetParas;

	m_pMacroEditView->GetDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ

	InitCommonParasByDatas(&oRetParas);
	//�Ƚ�oRetParas �� m_pTestMacroUI_Paras
	if (!m_pTestMacroUI_Paras->IsEqual(&oRetParas))
	{
		oRetParas.CopyChildren(m_pTestMacroUI_Paras);

		if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb()
			|| g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_MUAutoTest)
		{
			m_pTestCtrlCntrBase->Ats_GenerateTemplate();
		}
		else
		{
			CString strItemPath = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
			CString strMacroID = _T("");

			if(g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
			{
				strMacroID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
			}

			strItemPath += "$" + strItemPath;
			if(g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_IntelligentTest
				||g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_RemoteMeasTest)
			{
				//CString strItemPathNodes=strItemPath.Left(strItemPath.Find(_T("Test")));
				CString strID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
				long nIndex = strID.Find(_T("Test"));

				if (nIndex>=0)
				{
					CString strItemPathNodes = strItemPath.Left(nIndex);
				strItemPath+= "$" + strItemPathNodes;
				}

				if(g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_IntelligentTest)
				{
					strMacroID=STT_ORG_MACRO_BinaryManuTest;//�������ֶ�����MarcoID
				}
				else
				{
					strMacroID=STT_ORG_MACRO_ManualTest;
				}		
			}
			m_pTestCtrlCntrBase->Ats_SetItemPara(strItemPath, strMacroID);
			SetValues_dsRcdStep6U6I(TRUE);
		}
	}
}

void QSttTestCntrFrameBase::SysStateReport_OnStateChanged(CEventResult *pEventInfo)
{
	if((CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_StateTest)||(CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_SmvAbnTest)
		||(CSttMacroParaEditViewMngr::GetCurMacroID() == STT_ORG_MACRO_GseAbnTest))
	{
        if(m_pMacroEditView)
        {
		((QSttMacroParaEditViewState*)m_pMacroEditView)->SysStateReport_OnStateChanged(pEventInfo);
	}
	}
    else if((g_pTheSttTestApp->m_pTestMacroUI != NULL) &&g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb()&&HasManuTrigerBtn()&&(pEventInfo->m_nCurrStateIndex == 1))//zhouhj 20220403 ����ҳģ�� ����ڶ���״̬��,����Ҫ���ֶ������ҵ�
	{
		EnableManualTriggerButton(false);
//		UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
	}
}

void QSttTestCntrFrameBase::OnCmd_DebugSetDatas()
{
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
		m_pMacroEditView->SetDatas(m_pTestMacroUI_Paras);
	}
}

void QSttTestCntrFrameBase::OnCmd_DebugGetDatas()
{
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
		m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
	}
}

void QSttTestCntrFrameBase::OnCmd_DebugSetDatasFile(long nFileIndex)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (! g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		return;
	}

	m_pTestCtrlCntrBase->OpenMacroTestUI_ParaFile(nFileIndex);
    //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
	m_pMacroEditView->SetDatas(m_pTestMacroUI_Paras);
}

void QSttTestCntrFrameBase::OnCmd_DebugSetDatasFile1()
{
	OnCmd_DebugSetDatasFile(1);
}

void QSttTestCntrFrameBase::OnCmd_DebugSetDatasFile2()
{
	OnCmd_DebugSetDatasFile(2);
}

void QSttTestCntrFrameBase::OnCmd_DebugSaveDatasFile()
{
	SaveMacroTestUI_ParaFile("_dbug");
}

void QSttTestCntrFrameBase::OnCmd_DebugUpdateReport()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	UpdateRptHtml();
}

#include "../../../Module/QT/Png64/DrawPngBase64.h"

void QSttTestCntrFrameBase::OnCmd_DebugFillReport()
{

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	FillReport();
}

void QSttTestCntrFrameBase::OnCmd_DebugItemStateChanged()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}
    //
    //m_pSttReportViewHtml->ItemStateChanged("DistanceTest$GPDis1", "DistanceTest$GPDis1$A095", "TESTING");
}

void QSttTestCntrFrameBase::OnCmd_DebugOutPutWidget()
{
	//bool bShow = m_pOutputWidget->isVisible();
	//m_pOutputWidget->setVisible(!bShow);
	SetActiveWidget(m_pOutputWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_DebugStartTest()
{
	UpdateCmdButtonsState(STT_TEST_STATE_TESTTING);
}

void QSttTestCntrFrameBase::OnCmd_DebugStopTest()
{
	UpdateCmdButtonsState(STT_TEST_STATE_TEST_STOPED);
}

void QSttTestCntrFrameBase::OnCmd_ConnectApp()
{
	m_pTestCtrlCntrBase->ConnectAtsServer();
}

void QSttTestCntrFrameBase::OnCmd_Debug()
{
	CSttMacroParaEditInterface *pSttMacroParaEditInterface = CSttMacroParaEditViewMngr::GetSttMacroParaEditViewHtml();//��ȡ��ҳ����

	if (pSttMacroParaEditInterface == NULL)
	{
		return;
	}

    //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)pSttMacroParaEditInterface->m_pMacroParaEditWnd;

    //if (pSttMacroParaEditViewHtml == NULL)
    //{
    //	return;
    //}
    //
    //pSttMacroParaEditViewHtml->Debug();
}

void QSttTestCntrFrameBase::OnCmd_DebugSaveTest()
{
	CString strFile = m_pTestCtrlCntrBase->SaveTestFile("", "");

	if (strFile.GetLength() < 5)
	{
		return;
	}

	strFile = ChangeFilePostfix(strFile, "html");

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
    //}
}

extern long g_nAtsGenTemplateForDebug;

void QSttTestCntrFrameBase::OnCmd_DebugGenForDebug()
{
	if (g_nAtsGenTemplateForDebug == 0)
	{
		g_nAtsGenTemplateForDebug = 1;
	}
	else
	{
		g_nAtsGenTemplateForDebug = 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "g_nAtsGenTemplateForDebug == %d", g_nAtsGenTemplateForDebug);
}

void QSttTestCntrFrameBase::OnCmd_DebugGenTemplate()
{
	GenerateTemplate(NULL, "", "");
}

void QSttTestCntrFrameBase::OnCmd_DebugSaveAsSysFiles()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return;
	}

	//����ȱʡ�ļ�
	SaveMacroTestUI_ParaFile("");

	//����ȱʡģ���ļ���������λ������ʾ������Ŀ
	m_pTestCtrlCntrBase->SaveCurrTestMacroUITemplateFile();
}

void QSttTestCntrFrameBase::OnCmd_RemoteCtrl()
{
	SetActiveWidget(m_pRemoteCtrlWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_IecCap()
{
	SetActiveWidget(m_pSttIecRecordMainWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_IecCapWriteFile()
{
	SetActiveWidget(m_pSttIecRecordMainWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_IecCapDebugHead()
{
	SetActiveWidget(m_pSttIecRecordMainWidget, ActiveWidgetType_Other);
}

// #include "../RecordTest/QT/RingMemBufShmDebugWidget.h"
// extern QRingMemBufShmDebugWidget *g_pRingMemBufShmDebugWidget;

void QSttTestCntrFrameBase::OnCmd_ScreenShot()
{
// 	g_pRingMemBufShmDebugWidget->show();
// 	return;
// 	CTickCount32 oTick;
// 	long nIndex = 0;
// 
// 	while(nIndex<50)
// 	{
// 		m_oTimerAtsTest.start(100);
// 		oTick.DoEvents(105);
// 		m_oTimerAtsTest.stop(1);
// 		nIndex++;
// 	}
// 
// 	CString strTmp1,strTmp2,strTmp3;
// 	strTmp1 = "����1%lf����3";
// 	strTmp3 = "����2";
// 	double dValue = 2.33f;
// 	strTmp2.Format(strTmp1/*.GetString()*/,dValue/*strTmp3.GetString()*/);
// 	strTmp3.Format(strTmp1.GetString(),dValue);
//  	return;

	CString strFilePath  = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_PrintScreen);

//�Ƿ�ʹ���Զ����ʱ�����
#ifdef USE_Custom_CDateTime
	int nYear = 1970, nMon = 1, nDay = 1, nHour = 0, nMin = 0, nSec = 0,nMs = 0;
	CDateTime::GetTime(nYear,nMon,nDay,nHour,nMin,nSec,nMs);
	CString strFileName;
	strFileName.Format(_T("%04d_%02d_%02d_%02d_%02d_%02d"),nYear,nMon,nDay,nHour,nMin,nSec);
#else
 	QDateTime tmData = QDateTime::currentDateTime();
 	CString strFileName = tmData.toString("yyyy_MM_dd_hh_mm_ss"); 
#endif
	strFilePath += "/";
//  CreateAllDirectories(strFilePath);
    strFilePath += strFileName;
    QPixmap *pPixMainScreen = new QPixmap();
    *pPixMainScreen = QPixmap::grabWindow(QApplication::desktop()->winId()/*,0,0,1024,768*/);/*QPixmap::grabWindow(QApplication::desktop()->winId())*/;

    if(pPixMainScreen->isNull())
    {
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("�������(%s)(isNull)ʧ��.")*/g_sLangTxt_Gradient_INUnSavescreen.GetString(),strFilePath.GetString()); //lcq
		delete pPixMainScreen;
        return;
    }

	strFilePath += ".png";

	if(false == pPixMainScreen->save(strFilePath,"PNG"))
    {
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("�������(%s)(save)ʧ��.")*/g_sLangTxt_Gradient_UnSavescreen.GetString(),strFilePath.GetString()); //lcq
		delete pPixMainScreen;
        return;
    }

#ifdef CURLINUX
    ::system("sync");
#endif
	//CXMessageBox::information(this,tr("��ʾ"),tr("�����ɹ�."));
	
	CXMessageBox::information(this,g_sLangTxt_Message.GetString(),g_sLangTxt_Gradient_ShotScreenSus.GetString());//lcq
//	pPixMainScreen->toImage();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,/*_T("�������(%s)�ɹ�.")*/g_sLangTxt_Gradient_Savescreen.GetString(),strFilePath.GetString()); //lcq
	delete pPixMainScreen;
}

//2022-12-02  lijunqing
void QSttTestCntrFrameBase::OnCmd_Assist()
{
	assist_show_menu();
}

//2022-12-27  lijunqing
void QSttTestCntrFrameBase::InitIecCapTest(bool bActiveIecCap, bool bStartDetect,bool bShowMenuBtns)
{
	if (!bShowMenuBtns)
	{
		UpdateButtonStateByID(STT_CNTR_CMD_Menu,true);//2023-10-31 suayang �������󿪷Ų˵�ѡ��
		UpdateButtonStateByID(STT_CNTR_CMD_AddMacro,false,false);
		UpdateButtonStateByID(STT_CNTR_CMD_TemplateView,false,false);
		UpdateButtonStateByID(STT_CNTR_CMD_ItemList,false,false);
		UpdateButtonStateByID(STT_CNTR_CMD_ReportView,false,false);
		UpdateButtonStateByID(STT_CNTR_CMD_ChRsMaps,false,false);
		UpdateButtonStateByID(STT_CNTR_CMD_BinBoutCommMap,false,false);

		AdjustToolBarButtons();
	}

	if (bActiveIecCap)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::AttachObj(this); //dingxy 20241008 ����̽��ڶ��δ�iec���ñ��������޸�
#endif
		OnCmd_IecCap();
	}

	if (bStartDetect)
	{
		if (m_pSttIecRecordMainWidget != NULL)
		{
			m_pSttIecRecordMainWidget->StartDetect();
		}
	}
}

void QSttTestCntrFrameBase::InitRemoteCtrlTest(bool bActiveRemoteCtrl, bool bStart,bool bShowMenuBtns)
{
	if (bActiveRemoteCtrl)
	{
		OnCmd_RemoteCtrl();

		if (m_pTestCtrlCntrBase != NULL)//zhouhj 2024.3.19 �ڵ�����ң�ز��Թ���ʱ,���ӵײ�����,��ʾ��ص�������Ϣ
		{
			m_pTestCtrlCntrBase->ConnectAtsServer();
		}
	}

	if (bStart)
	{
		CreateEngineClientWidget();
	}

}

void QSttTestCntrFrameBase::EnableStartStopButton(BOOL bEanble)
{
	if (m_pStartTestBtn != NULL)
	{
		QSttToolButtonBase *pStartStopButton = (QSttToolButtonBase*)m_pStartTestBtn->m_dwItemData;

		if (pStartStopButton != NULL)
		{
			pStartStopButton->setEnabled(bEanble);
		}
	}
}

void QSttTestCntrFrameBase::EnableManualTriggerButton(BOOL bEanble)
{
	if (m_pManualTriggerBtn != NULL)
	{
		QSttToolButtonBase *pButtonUI = (QSttToolButtonBase*)m_pManualTriggerBtn->m_dwItemData;

		if (pButtonUI != NULL)
		{
			pButtonUI->setEnabled(bEanble);
		}
	}
}

void QSttTestCntrFrameBase::OnCmd_Menu()
{
	
}

bool QSttTestCntrFrameBase::PrepStartTest()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return false;
	}

	if (m_pMacroEditView == NULL)
	{
		return false;
	}

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		CSttMacroParaEditViewOriginal *pViewOriginal = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;

		if (!pViewOriginal->PrepStartTest())
		{
			return false;
		}

		if (pViewOriginal->m_bSystemParasChanged)
		{
			pViewOriginal->m_bSystemParasChanged = FALSE;
			Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_SystemConfig);
		}
	}

	if (g_oSystemParas.HasDigitalInOrOut())//zhouhj 20220404 ���������,���ҵ�ǰIEC����Ϊ�յ�����£����ܿ�ʼ����
	{
		if (!g_oSttTestResourceMngr.HasContrlBlockSelected_IecConfig())
		{
            CXMessageBox::information(this,tr("����"),/*tr("��ǰIEC����Ϊ��.")*/g_sLangTxt_NullIEC.GetString()); //lcq
			return false;
		}

		if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal() && ((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->m_bIECGoutMapChanged)
		{
			Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_IECConfig);//���ֶ����顢г��ģ��,����GOOSE�����������ͻ����޸�ͨ��ӳ���,�˴�����IEC�����������
			((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->m_bIECGoutMapChanged = FALSE;
		}
	}

	//��ʼ����ǰ,�����ǰƵ�ʼ���ֵΪ���Զ����㷽ʽ,�����Ϊ�Ƶ��
	if ((g_dFixFreqCalValue>1.0f)&&(g_oSystemParas.m_fFNom>1.0f))
	{
		g_dFixFreqCalValue = g_oSystemParas.m_fFNom;
	}
	

	if (m_pCharLibWidget)
	{
		m_pCharLibWidget->m_pImpCharactWidget->ClearSearchPoints();

		if (m_pCharLibWidget == m_pActiveWidget)//zhouhj 2023.8.8�����ǰ�������Ϊ��������,�ڿ�ʼ����ʱ,��������������ͬ������ҳ
		{
			TemplateView_Prepare();
		}
	}

	if (m_pCharactWidgetForTest != NULL)
	{
		m_pCharactWidgetForTest->ClearSearchPoints();
	} 

	if (m_pSttCharacterDrawPng != NULL)
	{
		m_pSttCharacterDrawPng->ClearSearchPoints_png();
		m_pSttCharacterDrawPng->ClearPngCache();
	}

	return true;
}

void QSttTestCntrFrameBase::InitCommonParasByDatas(CDataGroup *pDataGroup_Paras)
{
	if (pDataGroup_Paras == NULL)
	{
		return;
	}

	g_nMuTimeTest_UseNoPPS = 0;

	if (!pDataGroup_Paras->GetDataValue("PPS_SetType",g_nMuTimeTest_UseNoPPS))
	{
		CExBaseObject *pCurrObj = pDataGroup_Paras->FindByID("MU");

		if (pCurrObj != NULL)
		{
			if (pCurrObj->GetClassID() == DTMCLASSID_CDATAGROUP)
			{
				CDataGroup *pMU_Obj = (CDataGroup*)pCurrObj;
				pMU_Obj->GetDataValue("PPS_SetType",g_nMuTimeTest_UseNoPPS);
			}
		}
	}
}

void QSttTestCntrFrameBase::OnCmd_StartTest()
{
#ifdef _PSX_QT_LINUX_
	if(m_oDataBtnsMngr.IsLowPower())
	{
		CLogPrint::LogString(XLOGLEVEL_ASSIST,/*_T("��ǰ������ʣ���������,���ȳ��!!!")*/g_sLangTxt_Native_LowBatteryLevel);
		//		CXMessageBox::information(this,tr("����"),tr("��ǰ������ʣ���������,���ȳ��!!!"));
		return;
	}
#endif


	//2024/1/3 wangjunsheng ���ڱ���̽�����ʱ����ֹ��ʼ����
	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

	if (strIDMacroUI == "")
	{
		CString strMsgText;

		if (CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID == "RemoteCtrlTest")
		{
			strMsgText = _T("ң�ؽ����޷�ֱ�ӿ�ʼ����.");
		} 
		else
		{
			strMsgText = _T("����̽������޷�ֱ�ӿ�ʼ����.");
		}

		CLogPrint::LogString(XLOGLEVEL_ASSIST,strMsgText);
		return;
	}


	if (!MUTestValid())
	{
		CLogPrint::LogString(XLOGLEVEL_ASSIST,/*_T("�ϲ���Ԫ����,��Ҫ�Ƚ���IEC̽����ӽ���.")*/g_sLangTxt_Native_IecDetection);
		//		CXMessageBox::information(this,tr("����"),tr("�ϲ���Ԫ����,��Ҫ�Ƚ���IEC̽����ӽ���."));
		return;
	}

	if (!PrepStartTest())
	{
		return;
	}

	//2022-12-02  lijunqing �������ֿ�ʼ�����¼����ж��Ƿ���Կ�ʼ����
	if (!assist_event(STT_CNTR_CMD_StartTest, NULL))
	{
		return;
	}

	SaveCharacteristicsData();
	EnableStartStopButton(FALSE);
	on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	EnableManualTriggerButton(FALSE);
	ClearAll_ResultUI();//������Խ����ʾ����
	ClearItemStateList();
//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("��ʼ����"));
	CDataGroup oRetParas;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
		m_pMacroEditView->GetDatas(&oRetParas);
        SetValues_dsRcdStep6U6I(&oRetParas,TRUE);
		InitBinaryIn_WebUI(&oRetParas);//��ҳ������Ҫ���ݻ�ȡ�Ľ����������ѡ��״̬,���¿���ѡ��ͼ��  zhouhj 20220426
	}
	else
	{
		m_pMacroEditView->GetDatas(&oRetParas);
		SetValues_dsRcdStep6U6I(TRUE);
//		oRetParas.SaveXmlFile("D://123456.xml",CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	
	InitCommonParasByDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("�������"));

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("OnCmd_StartTest[++++]."));
	if (m_pTestCtrlCntrBase->StartTest(&oRetParas))
	{
        //if (m_pSttReportViewHtml != NULL)
        //{
        //	m_pSttReportViewHtml->UpdateReportHead_StartEndTestTime(!m_bHasUpdateRptStartTestTime,TRUE);
        //}

		m_bHasUpdateRptStartTestTime = TRUE;
	}
	else
	{
#ifdef _PSX_QT_LINUX_
		CString strTitile,strMsg;
		strTitile = g_sLangTxt_Message/*"��ʾ"*/;
		strMsg = g_sLangTxt_Native_StartTestSendFail/*"��ʼ���������·�ʧ��."*/;
		CXMessageBox::information(this, strTitile, strMsg);
#endif
		EnableStartStopButton(TRUE);
		on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("OnCmd_StartTest[----]."));
}

void QSttTestCntrFrameBase::OnCmd_TestThis()
{

}

void QSttTestCntrFrameBase::OnCmd_ManuTriger()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_pTestCtrlCntrBase->SendManuTrigger() == STT_CMD_ExecStatus_SUCCESS)
	{
		g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false);
	}
}

void QSttTestCntrFrameBase::OnCmd_StopTest()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	EnableStartStopButton(FALSE);

	if (!m_pTestCtrlCntrBase->StopTest())
	{
#ifdef _PSX_QT_LINUX_
		CString strTitile,strMsg;
		strTitile = g_sLangTxt_Message/*"��ʾ"*/;
		strMsg = g_sLangTxt_Native_StopTestSendFail/*"ֹͣ���������·�ʧ��."*/;
		CXMessageBox::information(this, strTitile, strMsg);
#endif
		EnableStartStopButton(TRUE);
	}
}

BOOL QSttTestCntrFrameBase::CanAddTestMacroUI()
{
	return TRUE;
}

void QSttTestCntrFrameBase::closeEvent( QCloseEvent * event )
{

// #ifdef _PSX_QT_LINUX_
// #ifndef _PSX_OS_CENTOS_
	//if(g_pTheSttTestApp->GetCurrTestMacroUI() == STT_ORG_MACRO_MUAccurAutoTest)
	{
		//20241218 suyang ����������ʱ�ȶϿ��Զ�����
		CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
		if (pNative)
		{
			//pNative->m_oSttAtsClient.m_pXClientEngine->System_Logout();
			pNative->m_oSttAtsClient.DisConnectAtsTestServer();
			
		}
	
	}

// #endif
// 
// #endif

	g_pTheSttTestApp->ExitSttTestApp();
#ifndef NOT_USE_ASSIST
	assist_release();
#endif
	QMainWindow::closeEvent(event);
}

void QSttTestCntrFrameBase::OnCmd_AddMacro(BOOL bUseNameID)
{
	if (!CanAddTestMacroUI())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, /*_T("���ڲ�����Ŀ���οؼ���ѡ��Ϸ�����Ŀ����")*/g_sLangTxt_Gradient_Selectleg.GetString()); //lcq
		return;
	}

	QSttAddMacroWidget dlg(m_gFont,this);
	dlg.Use_Name_ID(bUseNameID);  //lijunqing 2022-6-24  lijunqing LINUX ��ʹ��Name
	dlg.m_pCurrentSelGbItem = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();
//	connect(&dlg,SIGNAL(sig_TreeItemSelect(CSttMacroTestUI_TestMacroUIRef *)),this,
//		SLOT(slot_SelectTestMacro(CSttMacroTestUI_TestMacroUIRef *)));
	
	if (dlg.exec() != 1)
	{
		return;
	}

	slot_SelectTestMacro(dlg.m_pCurrUIRef, dlg.m_strItemsName, dlg.m_strItemsID);
}

void QSttTestCntrFrameBase::OnCmd_ItemList()
{
	//�۲�Ч������ʱ����ʾtest-macro-uis�е����ݣ������ĳ�GuideBook��ʾ sf 20220111
	if(m_pSttGbTreeView == NULL)
	{
		return;
	}

	BOOL bIsVisible = ! m_pSttGbTreeView->isVisible();
	m_pSttGbTreeView->setVisible(bIsVisible);
	CalRectArea();
	m_pSttGbTreeView->setGeometry(m_rcGbItemsArea);
}

void QSttTestCntrFrameBase::SendMenuButtonClick(QString strFuncID)
{
#ifndef NOT_USE_ASSIST
	g_theAssistWndDynEffExecTool->Flash(strFuncID,"","",5000);
#endif

	emit sig_MenuButtonClick(strFuncID);
}

CString QSttTestCntrFrameBase::FindNameFromTestMacros(CTestMacros* pTestMacros, CString strMacroID, CString strID)
{
	CTestMacro* pTestMacro = (CTestMacro*)pTestMacros->FindByID(strMacroID);
	if(pTestMacros)
	{
		CShortData* pData = NULL;
		if(pTestMacro->GetFaultParas())
		{
			pData = (CShortData*)pTestMacro->GetFaultParas()->SelectData(strID);
			if(pData)
			{
				return pData->m_strName;
			}
		}

		if(pTestMacro->GetSysParas())
		{
			pData = (CShortData*)pTestMacro->GetSysParas()->SelectData(strID);
			if(pData)
			{
				return pData->m_strName;
			}
		}

		if(pTestMacro->GetResults())
		{
			pData = (CShortData*)pTestMacro->GetResults()->SelectData(strID);
			if(pData)
			{
				return pData->m_strName;
			}
		}

		strID = strID.Mid(strID.indexOf('$') + 1);
		pData = (CShortData*)pTestMacro->m_list_FaultParasEx.SelectData(strID);
		if(pData)
		{
			return pData->m_strName;
		}

		pData = (CShortData*)pTestMacro->m_list_ResultParasEx.SelectData(strID);
		if(pData)
		{
			return pData->m_strName;
		}
	}

	CString strText;
	if(strID.indexOf(g_strTestResultJudgeKey) != -1)
	{
		xlang_GetLangStrByFile(strText, "Native_ResultJudge");
		return strText;
	}
	else if(strID.indexOf(strID == g_strTestResultDescriptKey) != -1)
	{
		xlang_GetLangStrByFile(strText, "Native_ResultDescript");
		return strText;
	}
	else if(strID.indexOf(strID == g_strTestResultTimeKey) != -1)
	{
		xlang_GetLangStrByFile(strText, "Native_ResultTime");
		return strText;
	}
	else if(strID.indexOf(strID == g_strTestResultAbsRsltCal1Key) != -1)
	{
		xlang_GetLangStrByFile(strText, "Native_ResultAbsRsltCal1");
		return strText;
	}
	else if(strID.indexOf(strID == g_strTestResultAbsRsltCal2Key) != -1)
	{				 
		xlang_GetLangStrByFile(strText, "Native_ResultAbsRsltCal2");
		return strText;
	}
	else if(strID.indexOf(strID == g_strTestResultRelRsltCal1Key) != -1)
	{
		xlang_GetLangStrByFile(strText, "Native_ResultRelRsltCal1");
		return strText;
	}
	else if(strID.indexOf(strID == g_strTestResultRelRsltCal2Key) != -1)
	{
		xlang_GetLangStrByFile(strText, "Native_ResultRelRsltCal2");
		return strText;
	}   

	return "";
}

void QSttTestCntrFrameBase::SetErrorValueFromWzd(CDataGroup* pDataGroup)
{
	if(m_pTestCtrlCntrBase->GetCurrTestMacroUI()->m_strID == STT_CMD_ATS_MACRO_ID_StateTest)
	{
		CDataGroup* pParasData = (CDataGroup*)m_pTestMacroUI_Paras->FindByID("rslt_evaluation");
		pParasData->InitDataValues(pDataGroup, FALSE);
// 		for(int i = 0; i < pParasData->GetCount(); i++)
// 		{
// 			CDataGroup* pErrorGroup = (CDataGroup*)pParasData->GetAt(i);
// 			CDvmData* pData = (CDvmData*)pErrorGroup->FindByID("ActT_AbsErr");
// 			CShortData* pShortData = (CShortData*)pDataGroup->GetAt(i);
// 			pData->m_strValue = pShortData->m_strValue;
// 			pData = (CDvmData*)pErrorGroup->FindByID("ActT_RelErr");
// 			pShortData = (CShortData*)pDataGroup->GetAt(i + 10);
// 			pData->m_strValue = pShortData->m_strValue;
// 		}
	}
	else
	{
		POS pos = pDataGroup->GetHeadPosition();
		while (pos)
		{
			CDvmData* pData = (CDvmData*)pDataGroup->GetNext(pos);
			CDvmData* pParasData = (CDvmData*)m_pTestMacroUI_Paras->FindByID(pData->m_strID);
			if(pParasData)
			{
				pParasData->m_strValue = pData->m_strValue;
			}
		}
	}
}

void QSttTestCntrFrameBase::OnCmd_TemplateView()
{
	QWidget *pMacroEditWidget = GetMacroEditWidget();

	if (pMacroEditWidget == NULL)
	{
		return;
	}

	TemplateView_Prepare();//��ģ����ͼʱ,��ǰ׼��,�磺�ͬ���������߽������


	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		SetActiveWidget(pMacroEditWidget, ActiveWidgetType_MacroUI_Original);
	}
	else
	{
		SetActiveWidget(pMacroEditWidget, ActiveWidgetType_MacroUI_Html);
	}
}	

void QSttTestCntrFrameBase::OnCmd_ReportView()
{
    //SetActiveWidget(m_pSttReportViewHtml, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_HardConfig()
{
	QHardwareSetDlg oHardwareSetDlg(this);
	oHardwareSetDlg.setFont(*g_pSttGlobalFont);
	oHardwareSetDlg.initUI(&g_oSystemParas);
	Global_SoftKeyBoardAttachObj(&oHardwareSetDlg);
	m_bUpdateHardCfgFromRealTime = false;

	if (oHardwareSetDlg.exec() == QDialog::Accepted)
	{
		g_oSttTestResourceMngr.SaveSystemParasFile();
		Cmd_SendSystemConfig();
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	m_bUpdateHardCfgFromRealTime = true;

}

void QSttTestCntrFrameBase::OnCmd_IECConfig()
{	
	UpdateButtonsStateByID(STT_CNTR_CMD_IECConfig, FALSE);//2024-6-21 wuxinyi ��IEC���ý���û�ر�֮ǰ���øð�ť

#ifdef _PSX_QT_LINUX_
	QSttIecConfigDialog oIecConfigDlg(&g_oSttTestResourceMngr.m_oIecDatasMngr, this);
#else
	QSttIecConfigDialogWin oIecConfigDlg(&g_oSttTestResourceMngr.m_oIecDatasMngr, this);
#endif
	oIecConfigDlg.InitUI();
	oIecConfigDlg.setWindowModality(Qt::WindowModal);
	oIecConfigDlg.m_pSclStation = &m_pTestCtrlCntrBase->m_oSclStation;
	connect(&oIecConfigDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),SLOT(slot_IecCfgDataMngrUpdate()));

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oIecConfigDlg);
#endif
	oIecConfigDlg.exec();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	disconnect(&oIecConfigDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),this,SLOT(slot_IecCfgDataMngrUpdate()));

	UpdateButtonsStateByID(STT_CNTR_CMD_IECConfig, TRUE);

}

void QSttTestCntrFrameBase::OnCmd_VectorDrawView()
{
	if (m_pVectorWidget != NULL)
	{
		SetActiveWidget(m_pVectorWidget, ActiveWidgetType_Other);

		//2023.7.31 zhangyq ��ȡ��ǰMacroID���ж��Ƿ�Ϊ���ʷ�������ǹ��ʷ��������õ�ǰʸ��ͼ�Ĺ���ģʽ
		CString strCurrUI_ID = GetCurrentUI_ID();
		if(strCurrUI_ID == _T("PowerDirectionTest"))
		{
			CDataGroup oParas;
			oParas.AppendCloneEx(*m_pTestMacroUI_Paras);
			m_pMacroEditView->GetDatas(&oParas);
			m_pVectorWidget->SetVectorMode(VECTOR_POWERWORK,&oParas);
		}
		else
		{
			m_pVectorWidget->SetVectorMode(VECTOR_COMMON, NULL);
		}
	}
}

void QSttTestCntrFrameBase::OnCmd_WaveDrawView()
{

}

void QSttTestCntrFrameBase::OnCmd_StateDrawView()
{
	if (m_pStateMonitorWidget != NULL)
	{
		SetActiveWidget(m_pStateMonitorWidget, ActiveWidgetType_Other);
	}
}
void QSttTestCntrFrameBase::OnCmd_PowerDrawView()
{
	if (m_pPowerDiagramWidget != NULL)
	{
		SetActiveWidget(m_pPowerDiagramWidget, ActiveWidgetType_Other);
		m_pPowerDiagramWidget->cmbVolSetChanged();
		m_pPowerDiagramWidget->cmbCurSetChanged();
                m_pPowerDiagramWidget->updatePowerData();
	}	
}

void QSttTestCntrFrameBase::OnCmd_FAParasSetDialog()
{
	QSttFAParasSetDialog dlg(this);
	connect(&dlg, SIGNAL(sig_UpdatepFAParasData(CDataGroup *)),this,SLOT(slot_UpdateFAParasData(CDataGroup *)));

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::NUMBER);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
	disconnect(&dlg, SIGNAL(sig_UpdatepFAParasData(CDataGroup *)),this,SLOT(slot_UpdateFAParasData(CDataGroup *)));
}

void QSttTestCntrFrameBase::onCmd_BinBoutCommMap()
{
	QBinBoutCommMapDialog dlg(this);
	connect(&dlg, SIGNAL(sig_BinBoutCommMapDataUpdate(CDataGroup *)),this,SLOT(slot_BinBoutCommMapDataUpdate(CDataGroup *)));
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
	disconnect(&dlg, SIGNAL(sig_BinBoutCommMapDataUpdate(CDataGroup *)),this,SLOT(slot_BinBoutCommMapDataUpdate(CDataGroup *)));
}



void QSttTestCntrFrameBase::TemplateView_Prepare()
{
	if ((m_pCharLibWidget == NULL)||(m_pMacroEditView == NULL))
	{
		return;
	}

	CString strMacroID;
	strMacroID = g_pTheSttTestApp->GetCurrTestMacroUI();

	if ((strMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)
		||(strMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_ElecRailwayDiffTest))
	{
		CDataGroup oParas;
		oParas.AppendCloneEx(*m_pTestMacroUI_Paras);
		m_pMacroEditView->GetDatas(&oParas);
		m_pCharLibWidget->CharToGroupDatas(&oParas);
		m_pMacroEditView->SetDatas(&oParas);
	}
}

void QSttTestCntrFrameBase::CharDrawView_Prepare()
{
	if ((m_pCharLibWidget == NULL)||(m_pMacroEditView == NULL))
	{
		return;
	}

	CString strMacroID;
	strMacroID = g_pTheSttTestApp->GetCurrTestMacroUI();

	if ((strMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_CurrInverseTimeTest)
		||(strMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_VolInverseTimeTest)
		||(strMacroID == STT_ORG_MACRO_UFInverseTimeTest)||(strMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)
		||(strMacroID == STT_ORG_MACRO_ElecRailwayDiffTest))
	{
		CDataGroup oParas;
		oParas.AppendCloneEx(*m_pTestMacroUI_Paras);
		m_pMacroEditView->GetDatas(&oParas);
		m_pCharLibWidget->GroupDatasToChar(&oParas);
	}
}

void QSttTestCntrFrameBase::OnCmd_IecCap_Prepare()
{
	if (IsTestStarted())//���Թ�����,������ͬ��
	{
		return;
	}

	if (!g_bSmartCap_RecordNow)//ֻ�ڽ���¼��״̬��,�Ž���ͬ������
	{
		return;
	}

	if (!g_pTheSttTestApp->IsMuTest())//�Ǻϲ���Ԫ���Բ�����ͬ������
	{
		return;
	}

	SetValues_dsRcdStep6U6I(FALSE);
}

void QSttTestCntrFrameBase::OnCmd_CharDrawView()
{
	if(!g_pTheSttTestApp->m_pTestMacroUI)
	{
		return;
	}

	//2022-6-30  lijunqing
	if (! g_pTheSttTestApp->m_pTestMacroUI->HasCharLib())
	{
		return;
	}

    if ((m_pActiveWidget == m_pCharLibWidget)&&(!m_pCharLibWidget->isHidden()))//zhouhj 2023.7.17  �����ǰ����ͼ�Ѿ��Ǽ���,�����ٴ���
	{
		return;
	}

	CharDrawView_Prepare();
	InitCharLibWidget();
	SetActiveWidget(m_pCharLibWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_NewTest()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, /*_T("?????????????? OnCmd_NewTest: �رմ򿪵Ĳ��Թ���ҳ�棬��������ʾ�Ƿ񱣴��޸� ???????????")*/g_sLangTxt_Native_CloseFeatPromptSave.GetString());
	g_pTheSttTestApp->m_pTestCtrlCntr->NewTest(NULL, NULL, NULL);
	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pSttGbTreeView->ShowBaseList((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());
	connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
}

BOOL QSttTestCntrFrameBase::OpenTemplate(CString strFilePath, const CString &strDvmFile)
{
	if (! OpenDscXmlFile(strFilePath))
	{
		return FALSE;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->m_strFile = strFilePath;

	//chenling 20241226 ��ģ��ʱ����ģ��dscxml�и���ͨѶ������TestCtrlCommConfig.xml
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");
	CPpSttCommConfig oCommConfig;
	CSttTestGlobalDatasMngr *pTestGlobalDatasMngr = pGuideBook->m_pTestGlobalDatasMngr;
	if(pTestGlobalDatasMngr)
	{
		CDataGroup* pCommConfigData = pTestGlobalDatasMngr->GetCommConfig(FALSE);
		if (oCommConfig.OpenCommConfigFile(strFile) && pCommConfigData)
		{
			oCommConfig.DeleteAll();
			oCommConfig.AppendCloneEx2(*pCommConfigData);
			oCommConfig.SaveCommConfigFile(strFile);
		}
	}

	if (! AfterOpenDscXmlFile(strFilePath))
	{
		return FALSE;
	}

	m_bHasUpdateRptStartTestTime = FALSE;
	//�򿪱��棺����������ģ���ģʽ�£�������Ӧ��ֻ��_Init_�ı��档
	CSttItems* pRootNode = pGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pRootNode->m_strstxmlFile);

	strFilePath = ChangeFilePostfix(strFilePath, "html");
	CString strFilePath2 = _P_GetDBPath();
	strFilePath2 += _T("ui/");
	strFilePath2 += CXLanguageMngr::g_pXLanguageMngr->m_strCurrLanguage;
	strFilePath2.AppendFormat(_T("/%s.html"), pRootNode->m_strstxmlFile.GetString());
	::X_CopyFile(strFilePath, strFilePath2);//�򿪵ı��棬һ������Ҫ��strFilePath2·����
	strFilePath2 = GetPathFileNameFromFilePathName(strFilePath2, '/');

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->InitReport(strFilePath2);
    //}

	//�·�OpenTemplateָ��
	strFilePath = ChangeFilePostfix(strFilePath, "gbxml");
	return m_pTestCtrlCntrBase->OpenTemplate(strFilePath, strDvmFile);
}

BOOL QSttTestCntrFrameBase::OpenDscXmlFile(CString strFilePath)
{
	//��ģ���ļ�
	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	strFilePath = ChangeFilePostfix(strFilePath, "dscxml");
	pGuideBook->DeleteAll();
	pGuideBook->m_pGlobalDatas = NULL;
//chenling 20250207 ת�ɶ������Ż���ģ��ʱ��
#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile
	BOOL bRet = FALSE;
    CString strFileB = ChangeFilePostfix(strFilePath, _T("bstt"));
    if (IsFileExist(strFileB))
	{
		bRet = dvm_OpenBinaryFile(pGuideBook, strFileB, true);
	}
	else
	{
		CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		bRet = pGuideBook->OpenXmlFile(strFilePath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		dvm_SaveBinaryFile(pGuideBook, strFileB, true);
	}
#else
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = pGuideBook->OpenXmlFile(strFilePath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#endif
	return bRet;
}

//��dscxml�󣬳�ʼ��ҳ��
BOOL QSttTestCntrFrameBase::AfterOpenDscXmlFile(CString strFilePath)
{
	//���ҵ�һ��rootnode
	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	CSttItems* pRootNode = pGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);

	//ˢ�����οؼ���ʾ
	//if (g_nUpdateMultiMacroParaEditView == 1)
	{
	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pSttGbTreeView->ShowBaseList(pGuideBook);
	m_pSttGbTreeView->m_pTreeCtrl->UpdateItemColour();
	connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}
	
	if (pRootNode == NULL)
	{
		//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("ģ������Ҳ���rootnode�ڵ�"));
		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
		return FALSE;
	}

	m_pSttGbTreeView->m_pCurrSelRootNode = pRootNode;
	m_pSttGbTreeView->m_strCurrSelRootNodePath = pRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	//�򿪶�Ӧ�Ĺ�����ͼ
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pRootNode->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, /*_T("ģ������Ҳ���rootnode�ڵ��Ӧ�Ĺ��ܽ��桾%s��")*/g_sLangTxt_Gradient_TemplateErr.GetString(), pRootNode->m_strstxmlFile.GetString()); //lcq
		g_pTheSttTestApp->SetCurrTestMacroUI(NULL);
		return FALSE;
	}

	g_pTheSttTestApp->m_pTestMacroUI = pTestMacroUI;

	if (g_nUpdateMultiMacroParaEditView == 1)
	{
	CSttTestMacroUiParas *pUIParas = GetTestMacroUiParas(pRootNode);

	if (m_pMacroEditView == NULL)
	{
		CreateSttMacroParaEditView(pTestMacroUI);
	}

	CSttTestMacroCharParas *pSttTestMacroCharParas = (CSttTestMacroCharParas *)pRootNode->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS);
	g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUI);
	g_pTheSttTestApp->m_pTestCtrlCntr->stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);
	g_theTestCntrFrame->OpenMacroTestUI(pUIParas, pTestMacroUI,pSttTestMacroCharParas);
	}
	

	return TRUE;
}

BOOL QSttTestCntrFrameBase::FillRptTitle(CExBaseObject *pCurrSelGbItem)
{
    //if ((pCurrSelGbItem == NULL)||(m_pSttReportViewHtml == NULL))
    //{
    //	return FALSE;
    //}

// 	if (pCurrSelGbItem->GetClassID() != STTGBXMLCLASSID_CSTTITEMS)
// 	{
// 		return FALSE;
// 	}

	CSttItems* pRootNode = Stt_GetFirstParentItems(pCurrSelGbItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pRootNode == NULL)
	{
        return FALSE;
	}

	CString strRootItemPath,strCurrItemPath;
    stt_gb_get_itempath_id(pRootNode, strRootItemPath);
	stt_gb_get_itempath_id((CSttItemBase*)pCurrSelGbItem, strCurrItemPath);
	CDataGroup oDataGroup;
	CDvmData *pData = new CDvmData;
	oDataGroup.AddNewChild(pData);
	pData->m_strName = pCurrSelGbItem->m_strName;
	pData->m_strValue = pCurrSelGbItem->m_strName;

	if (strCurrItemPath.GetLength() > strRootItemPath.GetLength())
	{
		pData->m_strID = strCurrItemPath.Mid(strRootItemPath.GetLength());
	} 
	else
	{
		pData->m_strID = _T("$");
	}

    //m_pSttReportViewHtml->FillReportTitle(strRootItemPath,&oDataGroup);
    return true;
}

BOOL QSttTestCntrFrameBase::OpenTest(CString strFilePath, const CString &strDvmFile)
{
	if (! OpenDscXmlFile(strFilePath))
	{
		return FALSE;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->m_strFile_Gbrpt = strFilePath;

	if (! AfterOpenDscXmlFile(strFilePath))
	{
		return FALSE;
	}

	m_bHasUpdateRptStartTestTime = FALSE;
	//�򿪱���
	CSttItems* pRootNode = pGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pRootNode->m_strstxmlFile);

	strFilePath = ChangeFilePostfix(strFilePath, "html");
	CString strFilePath2 = _P_GetDBPath();
	strFilePath2 += _T("ui/");
	strFilePath2 += CXLanguageMngr::g_pXLanguageMngr->m_strCurrLanguage;
	strFilePath2.AppendFormat(_T("/%s.html"), pRootNode->m_strstxmlFile.GetString());
	::X_CopyFile(strFilePath, strFilePath2);//�򿪵ı��棬һ������Ҫ��strFilePath2·����
	strFilePath2 = GetPathFileNameFromFilePathName(strFilePath2, '/');

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->InitReport(strFilePath2);
    //}

	//�·�OpenTestָ��
	strFilePath = ChangeFilePostfix(strFilePath, "gbrpt");
	return m_pTestCtrlCntrBase->OpenTest(strFilePath, strDvmFile);
}

void QSttTestCntrFrameBase::OnCmd_OpenTemplate()
{
	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = _P_GetTemplatePath();
	astrPostfix<<"*.gbxml";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		oOpenDlg.resize(850,500);
		oOpenDlg.setFixedHeight(500);
	}

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	CString strFilePath;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}
	
	OpenTemplate(strFilePath, _T(""));
}

void QSttTestCntrFrameBase::OnCmd_SaveTemplate()
{	
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_pMacroEditView == NULL)
	{
		return;
	}

	CDataGroup oRetParas;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
	}

	m_pMacroEditView->GetDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ

	CString strFileName, strPath;
	strFileName.Format(_T("%s.gbxml"), g_pTheSttTestApp->m_pTestMacroUI->m_strID.GetString());

	if (!Global_GetUsbRootFolderPath(strPath))
	{
		strPath = _P_GetTemplatePath();
	}

	//�˴��������ݵ�ǰ���Բ������βΣ��Ա������չ��
	if (m_pTestCtrlCntrBase->SaveTemplate(strPath, strFileName,&oRetParas))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·��������ģ��(%s%s)����ɹ�."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestTempSusCom.GetString(),strPath.GetString(),strFileName.GetString());  //lcq
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·��������ģ��(%s%s)����ʧ��."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestTempDefCom.GetString(),strPath.GetString(),strFileName.GetString());  //lcq
	}

	//strPath = _P_GetWorkspacePath();
	strFileName = ChangeFilePostfix(strFileName, "html");

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->SaveHtmlReportFile(strPath + strFileName);
    //}

	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("������ҳģ���ļ�(%s%s)�ɹ�."),strPath.GetString(),strFileName.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Gradient_SavePageSus.GetString(),strPath.GetString(),strFileName.GetString());//lcq

// 	if(IsTestStarted())
// 	{
// 		Ats_UpdateParameter();
// 	}

	BOOL bRet = FALSE;
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		bRet = ((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->SaveTestMngrFile(_T(""));
	}
	else if (!g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.IsEmpty())
	{
		CDataGroup  oDataGroup;
		oDataGroup.AppendCloneEx(*m_pTestMacroUI_Paras);
        //((QSttMacroParaEditViewHtml*)m_pMacroEditView)->GetDatas(&oDataGroup);

		if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
		{
			bRet = FALSE;
		}

        CString strPath = stt_ui_GetParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile);
#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile
		CString strPathB = ChangeFilePostfix(strPath, _T("bstt"));
		dvm_SaveBinaryFile(&oDataGroup, strPathB, true);//dingxy 20240913 ��Ϊ�������ļ�
#endif
		oDataGroup.SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	}

	if(bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Native_TempSaveSucc.GetString());
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Native_TempSaveFail.GetString());
	}
}

void QSttTestCntrFrameBase::OnCmd_SaveAsTemplate()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_pMacroEditView == NULL)
	{
		return;
	}

	CString strCfgPath = _P_GetTemplatePath();
	CString fileName;

#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = _P_GetTemplatePath();
	astrPostfix<<"*.gbxml";	
	QSttPopupSaveAsDialog dlg(strFolderPath,astrPostfix, g_pTheSttTestApp->m_pTestMacroUI->m_strID, this);
	dlg.m_bIsCheckExternalPath = FALSE;
	dlg.InitUI();
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::ENGLISH);
#endif
	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
	fileName = dlg.GetFilePath();
//	fileName += dlg.m_strFileName;
#else
	CreateAllDirectories(strCfgPath);

	fileName = QFileDialog::getSaveFileName(0, /*QObject::tr("ģ�����Ϊ")*/g_sLangTxt_Gradient_SaveTemplateAs,
		strCfgPath,"gbxml"); //lcq

	if (fileName.isEmpty())
	{
		return;
	}
	fileName += _T(".gbxml");
#endif
	

	CDataGroup oRetParas;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
	}

	m_pMacroEditView->GetDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ

	CString strFileName, strPath,strCurrFileName;
#ifdef _PSX_QT_LINUX_
    strPath = GetPathFromFilePathName(fileName, '/');
    strCurrFileName = GetPathFileNameFromFilePathName(fileName, '/');
	CreateAllDirectories(strPath);
#else
	strPath = GetPathFromFilePathName(fileName);
	strCurrFileName = GetPathFileNameFromFilePathName(fileName);
#endif
	//20250324 suyang ��Ҫ��ֻȡ . ��ǰ���
	int nIndex = strCurrFileName.Find(".");
	strFileName = strCurrFileName.left(nIndex);

	//�˴��������ݵ�ǰ���Բ������βΣ��Ա������չ��
	if (m_pTestCtrlCntrBase->SaveTemplate(strPath, strFileName, &oRetParas))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·��������ģ��(%s%s)����ɹ�."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestTempSusCom.GetString(),strPath.GetString(),strFileName.GetString());  //lcq
	} 
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·��������ģ��(%s%s)����ʧ��."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestTempDefCom.GetString(),strPath.GetString(),strFileName.GetString());  //lcq
	}

	//strPath = _P_GetWorkspacePath();
	strFileName = ChangeFilePostfix(strFileName, "html");


	//chenling 20250116 false��Ҫ����ģ�壬���򱨸�û����
//#ifdef _PSX_QT_LINUX_
//	if (m_pSttReportViewHtml != NULL && m_pSttReportViewHtml->m_bHasInitFinished == false)
//	{
//		m_pSttReportViewHtml->InitReportView();
//	}
//#endif
//
//	if (m_pSttReportViewHtml != NULL)
//	{
//		m_pSttReportViewHtml->SaveHtmlReportFile(strPath + strFileName);
//	}

	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("������ҳģ���ļ�(%s%s)�ɹ�."),strPath.GetString(),strFileName.GetString());
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Gradient_SavePageSus.GetString(),strPath.GetString(),strFileName.GetString());  //lcq
}

void QSttTestCntrFrameBase::OnCmd_SaveTest()
{
// 	QSttFileSaveAsDlg dlg("", "", this);
// 
// 	if (dlg.exec() != 1)
// 	{
// 		return;
// 	}
// 
// 	CString strFile = m_pTestCtrlCntrBase->SaveTestFile(dlg.m_strFolderName, dlg.m_strFileName);
// 
// 	if (strFile.GetLength() < 5)
// 	{
// 		return;
// 	}

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_pMacroEditView == NULL)
	{
		return;
	}

	CDataGroup oRetParas;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
	}

	m_pMacroEditView->GetDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ

	CString strFileName, strPath;
	strFileName.Format(_T("%s.gbrpt"), g_pTheSttTestApp->m_pTestMacroUI->m_strID.GetString());

	if (!Global_GetUsbRootFolderPath(strPath))//Ĭ�ϴ洢��U�̶�Ӧ��Ŀ¼��,����洢��_P_GetWorkspacePath
	{
		strPath = _P_GetWorkspacePath();
	}
	//�˴��������ݵ�ǰ���Բ������βΣ��Ա������չ��

	if (m_pTestCtrlCntrBase->SaveTest(strPath, strFileName, &oRetParas))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·�������Լ�¼(%s%s)����ɹ�."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestRecordSus.GetString(),strPath.GetString(),strFileName.GetString()); //lcq

	} 
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·�������Լ�¼(%s%s)����ʧ��."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestRecordFai.GetString(),strPath.GetString(),strFileName.GetString()); //lcq
	}

	//strPath = _P_GetWorkspacePath();
	strFileName = ChangeFilePostfix(strFileName, "html");


    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->SaveHtmlReportFile(strPath + strFileName);
    //}
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���汨���ļ�(%s%s)�ɹ�."),strPath.GetString(),strFileName.GetString());
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Gradient_SaveReportSus.GetString(),strPath.GetString(),strFileName.GetString()); //lcq
}

void QSttTestCntrFrameBase::OnCmd_SaveAsRpt()
{
    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}


	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = /*_P_GetLibraryPath()*/g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_Workspace);
	astrPostfix<<"*.html";	
	QSttPopupSaveAsDialog dlg(strFolderPath, astrPostfix,g_pTheSttTestApp->m_pTestMacroUI->m_strID, this);
	dlg.m_bIsCheckExternalPath = FALSE;
	dlg.InitUI();
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::ENGLISH);
	if (dlg.exec() != QDialog::Accepted)
	{
		QSoftKeyBoard::ReAttachObj();
		return;
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (dlg.exec() != QDialog::Accepted)
	{
		return;
	}
#endif
	CString strFilePath;
	strFilePath += dlg.GetFilePath();


	CString strPath;
#ifdef _PSX_QT_LINUX_
	strPath = GetPathFromFilePathName(strFilePath, '/');
#else
	strPath = GetPathFromFilePathName(strFilePath);
#endif

	CreateAllDirectories(strPath);
    //m_pSttReportViewHtml->SaveHtmlReportFile(strFilePath);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ҳ����(%s)����ɹ�."),strFilePath.GetString());

}

void QSttTestCntrFrameBase::OnCmd_ExportWordRpt()
{

}

void QSttTestCntrFrameBase::OnCmd_SaveAsTest()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_pMacroEditView == NULL)
	{
		return;
	}

	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = /*_P_GetLibraryPath()*/g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_Workspace);
	astrPostfix<<"*.html";	
	QSttPopupSaveAsDialog dlg(strFolderPath, astrPostfix,g_pTheSttTestApp->m_pTestMacroUI->m_strID, this);
	dlg.InitUI();
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::ENGLISH);
	if (dlg.exec() != QDialog::Accepted)
	{
		QSoftKeyBoard::ReAttachObj();
		return;
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (dlg.exec() != QDialog::Accepted)
	{
		return;
	}
#endif
	CString strFilePath;
	strFilePath += dlg.GetFilePath();;
//	strFilePath += _T("/");
// 	strFilePath += dlg.m_strFileName;
// 	strFilePath += _T(".html");

// 	CString fileName;
// 	fileName = QFileDialog::getSaveFileName(0, QObject::tr("�������Ϊ"),
// 		strCfgPath,"html");
// 
// 	if (fileName.isEmpty())
// 	{
// 		return;
// 	}

	CDataGroup oRetParas;

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
	}

	m_pMacroEditView->GetDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ

	CString strFileName, strPath;
#ifdef _PSX_QT_LINUX_
    strPath = GetPathFromFilePathName(strFilePath, '/');
    strFileName = GetPathFileNameFromFilePathName(strFilePath, '/');
#else
	strPath = GetPathFromFilePathName(strFilePath);
	strFileName = GetPathFileNameFromFilePathName(strFilePath);
#endif

	CreateAllDirectories(strPath);
	//�˴��������ݵ�ǰ���Բ������βΣ��Ա������չ��

	if (m_pTestCtrlCntrBase->SaveTest(strPath, strFileName, &oRetParas))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·�������Լ�¼(%s%s)����ɹ�."),strPath.GetString(),strFileName.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestRecordSus.GetString(),strPath.GetString(),strFileName.GetString()); //lcq
	} 
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("�·�������Լ�¼(%s%s)����ʧ��."),strPath.GetString(),strFileName.GetString());
        CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_TestRecordFai.GetString(),strPath.GetString(),strFileName.GetString()); //lcq
	}

	//strPath = _P_GetWorkspacePath();
	strFileName = ChangeFilePostfix(strFileName, "html");

    //if (m_pSttReportViewHtml != NULL)
    //{
    //	m_pSttReportViewHtml->SaveHtmlReportFile(strPath + strFileName);
    //}

	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���汨���ļ�(%s%s)�ɹ�."),strPath.GetString(),strFileName.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Gradient_SaveReportSus.GetString(),strPath.GetString(),strFileName.GetString());  //lcq
}

void QSttTestCntrFrameBase::OnCmd_OpenTest()
{

}

void QSttTestCntrFrameBase::OnCmd_SelSCLFile()
{

}

void QSttTestCntrFrameBase::OnCmd_SaveEdit()
{

}

void QSttTestCntrFrameBase::OnCmd_PpIotEngineClient()
{

}

void QSttTestCntrFrameBase::OnCmd_PpIotEngineClientDlg()
{
// 	CString strDevMode;
// 	strDevMode = g_oSttSystemConfig.GetDevModel();
// 	g_pTheSttTestApp->IinitGbWzdAiTool();
// 
// 	if (m_pEngineClientWidget == NULL)
// 	{
// 		CreateEngineClientWidget();
// 	}
// 
// 	QSttCommCfgDeviceDlg oSttComDlg(m_pEngineClientWidget,this);
// 	//oSttComDlg.setParent(this);
// 	//=====================
// #ifdef _USE_SoftKeyBoard_	
// 	QSoftKeyBoard::AttachObj(&oSttComDlg, Keyboard::NUMBER);
// #endif
// 	oSttComDlg.exec();
// #ifdef _USE_SoftKeyBoard_
// 	QSoftKeyBoard::ReAttachObj();
// #endif

// 	if (strDevMode == "PNS331")
// 	{
// 		
// 	}
// 	else
// 	{
// 		QPpSttIotEngineClientWidgetMain oMainWidget(this);
// 		oMainWidget.UpdateTitleAndSize(CString("װ��ͨѶ"),800, 630);
// #ifdef _USE_SoftKeyBoard_	
// 		QSoftKeyBoard::AttachObj(&oMainWidget, Keyboard::NUMBER);
// #endif
// 		//m_pEngineClientWidget = pMainWidget;
// 		//pMainWidget->setParent(this);
// 		//pMainWidget->hide();
// 		//pMainWidget->setGeometry(m_rcWorkArea);
// 
// 		if (g_pTheSttTestApp->m_pDvmDevice != NULL)
// 		{
// 			oMainWidget.ShowDvmDevice( g_pTheSttTestApp->m_pDvmDevice );
// 			oMainWidget.NewPpSttIotDeviceClient(&g_pTheSttTestApp->m_oCommConfig, g_pTheSttTestApp->m_pDvmDevice);
// 		}	
// 
// 		oMainWidget.exec();
// 
// #ifdef _USE_SoftKeyBoard_
// 		QSoftKeyBoard::ReAttachObj();
// #endif
// 	}
}

void QSttTestCntrFrameBase::OnCmd_CommConfiguration()
{
	QSttCommCfgMainDlg oSttCommCfgMainDlg(this);
	//oSttCommCfgMainDlg.exec();
#ifdef _USE_SoftKeyBoard_	
	QSoftKeyBoard::AttachObj(&oSttCommCfgMainDlg, Keyboard::NUMBER);
#endif
	oSttCommCfgMainDlg.exec();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
	UpdateDeviceModelRef();
}
void QSttTestCntrFrameBase::OnCmd_PkgMonitor()
{
// 	QSttCommCfgPkgMonitorDlg oSttCommCfgPkgMnDlg;
// 	oSttCommCfgPkgMnDlg.exec();
	CreateCommCfgPkgMnWidget();
	SetActiveWidget(m_pSttCommCfgPkgWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameBase::OnCmd_PpXmlFileMngr()
{
	QSttCommCfgProtocolTemplateDlg oComCfgProTempDlg;
	oComCfgProTempDlg.exec();

}
void QSttTestCntrFrameBase::OnCmd_DvmFileMngr()
{
	QSttCommCfgPointTblFileImportDlg oComCfgPntImpDlg(this);
	//oComCfgPntImpDlg.exec();

#ifdef _USE_SoftKeyBoard_	
	QSoftKeyBoard::AttachObj(&oComCfgPntImpDlg, Keyboard::NUMBER);
#endif
	oComCfgPntImpDlg.exec();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
}
//////////////////////////////////////////////////

void QSttTestCntrFrameBase::OnCmd_NetworkConfig()
{

}

//2023/8/29 wjs ң������
void QSttTestCntrFrameBase::OnCmd_AinDataMapConfig()
{
// 	QAinDataMapDlg oAinDataMapDlg(this);
// 	oAinDataMapDlg.setWindowTitle("ҡ��ӳ��");
// 	oAinDataMapDlg.exec();
}


// void QSttTestCntrFrameBase::OnCmd_SystemParas()
// {
// 	QSysParasDlg oSysParasDlg(this);
// 	oSysParasDlg.initUI();
// 	oSysParasDlg.setWindowModality(Qt::WindowModal);//ģ̬����
// 
// //#ifdef _PSX_QT_LINUX_
// #ifdef _USE_SoftKeyBoard_
// 	QSoftKeyBoard::AttachObj(&oSysParasDlg,Keyboard::NUMBER);
// 	oSysParasDlg.exec();
// 	QSoftKeyBoard::ReAttachObj();
// #endif
// }

void QSttTestCntrFrameBase::OnCmd_ClearReportRslts()
{

}

void QSttTestCntrFrameBase::OnCmd_ImportDvmFile()
{

}

void QSttTestCntrFrameBase::OnCmd_SystemParas()
{
	if (g_oSttSystemConfig.GetSelSysPata())
	{
		m_oOldSysParasList.DeleteAll();
		m_oOldSysParasList.AddNewData(STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom,g_oSystemParas.m_fVNom/SQRT3);
		m_oOldSysParasList.AddNewData(STT_XML_SERIALIZE_SYS_PARA_ID_OldINom,g_oSystemParas.m_fINom);
		m_oOldSysParasList.AddNewData(STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom,g_oSystemParas.m_fFNom);
	}

//#ifdef _PSX_QT_LINUX_
//	OpenMenuHtmlFile(STT_MACROPARA_HTML_NAME_SYSCONFIG);
//	m_pSysParaEditView->m_nSysConfig_Mode = STT_HTML_SYSCONFIG_MODE_UPDATE;
//#ifdef _USE_SoftKeyBoard_
//	QSoftKeyBoard::AttachObj(this);
//#endif
// #else
 	QSysParasDlg oSysParasDlg(this);
 	oSysParasDlg.initUI();
 #ifdef _USE_SoftKeyBoard_
 	QSoftKeyBoard::AttachObj(&oSysParasDlg,Keyboard::NUMBER);
	if (oSysParasDlg.exec() == QDialog::Accepted)
	{
		g_oSttTestResourceMngr.UpdateSoftKeyboardType();
	}
 	QSoftKeyBoard::ReAttachObj();
#else
 	oSysParasDlg.exec();
#endif
}

void QSttTestCntrFrameBase::OnCmd_GeneralParas()
{

}

void QSttTestCntrFrameBase::OnCmd_DcSet()
{	
}

void QSttTestCntrFrameBase::OnCmd_OutputPower()
{
	QModuleSetDlg oModuleSetDlg(this);
	m_bUpdateOutputPowerFromRealTime = TRUE;
	connect(&oModuleSetDlg, SIGNAL(sig_UpdateModulesGear(BOOL, BOOL)), this, SLOT(slot_UpdateModulesGear(BOOL, BOOL)));
	connect(this, SIGNAL(sig_UpdateModulesGearSwitchInfo()), &oModuleSetDlg, SLOT(slot_UpdateModulesGearSwitchInfo()), Qt::UniqueConnection);
	oModuleSetDlg.setFont(*g_pSttGlobalFont);
	oModuleSetDlg.initUI();
// 	if(m_bFirstUpadeIPowerMode)
// 	{
// 		if (g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode != STT_CurrentMODULE_POWER_LOW)
// 		{
// 			g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode = STT_CurrentMODULE_POWER_LOW;//20240415 suyang ����Ҫ�� ��ʼ��ʱ����Ϊ1��
// 		}
// 		m_bFirstUpadeIPowerMode = false;
// 
// 	}
// 	oModuleSetDlg.InitDatas(&g_oSystemParas);
	m_pTestCtrlCntrBase->Test_GetSystemState();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oModuleSetDlg);
	oModuleSetDlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	oModuleSetDlg.exec();
#endif
	disconnect(&oModuleSetDlg, SIGNAL(sig_UpdateModulesGear(BOOL, BOOL)), this, SLOT(slot_UpdateModulesGear(BOOL, BOOL)));
	disconnect(this, SIGNAL(sig_UpdateModulesGearSwitchInfo()), &oModuleSetDlg, SLOT(slot_UpdateModulesGearSwitchInfo()));
	m_bUpdateOutputPowerFromRealTime = FALSE;

//	OpenMenuHtmlFile(STT_MACROPARA_HTML_NAME_POWERGEAR);
}

void QSttTestCntrFrameBase::slot_UpdateModulesGear(BOOL bMergeCurrHasChanged, BOOL bCurrModulePowerHigh)
{
	if (bMergeCurrHasChanged)
	{
		OnUpdateTestResource(FALSE);

		if (g_oSystemParas.m_nHasAnalog)//zhouhj 2024.2.26 ����ģ�������,����bMergeCurrHasChanged==1,��ͨ��ӳ���Ѿ�����
		{
			Cmd_SendChMapsConfig();
			Cmd_SendSystemConfig();//20241113 suyang ϵͳ����MergeCurTerminal�ı�Ҳ��Ҫ����
		}
	}
	else
	{
		if ((g_pTheSttTestApp->m_pTestMacroUI != NULL) && (m_pMacroEditView!=NULL))//�жϵ�ǰ�Ƿ�����˲��Թ���ģ��,���жϵ�ǰ���Թ���ģ���Ƿ�Ϊ��ҳ
		{
			if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
			{
				m_pMacroEditView->UpdateDCParasByCurrModulePower(bCurrModulePowerHigh);
			}
		}
	}

	//zhouhj 2024.5.23 �������ڵ�λ�л�
	CDataGroup oPowerGear;
	CSttDataGroupSerializeRegister oRegister(&oPowerGear);
	stt_xml_serialize_ModulesGearSwitch(&g_oSystemParas, &oRegister);
	m_pTestCtrlCntrBase->Ats_SetParameter(STT_MACRO_ID_ModulesGearSwitch,&oPowerGear);
//	Cmd_SendSystemConfig();
}

void QSttTestCntrFrameBase::slot_FillReportImg(QString strItemPath)
{
    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}

	CString strImgBase64,strTmp;
	strTmp = strItemPath;
	m_pSttCharacterDrawPng->GetSearchingPng(NULL, strImgBase64);
    //m_pSttReportViewHtml->FillReportImg("", strTmp, strImgBase64);//zhouhj 20230213 ���ڲ���ͼƬ
#ifndef _PSX_QT_LINUX_ //��window��,���Խ�����Զ����ɶ�Ӧ��ͼƬ
	CString strPngFilePath;
	strPngFilePath = _P_GetWorkspacePath();
	strPngFilePath += _T("Img/");
	CreateAllDirectories(strPngFilePath);
	strPngFilePath += strTmp;
	strPngFilePath += _T(".png");

	m_pSttCharacterDrawPng->SavePngFile(strPngFilePath);
#endif
}

void QSttTestCntrFrameBase::slot_MsgBox(QString strTitle,QString strMsg)
{
	BOOL bShowMUTestIecCbSelWidget = FALSE;

	if (g_pSttMUTestIecCbSelWidget != NULL)
	{
		//�ϲ���Ԫ��ز���ʱ,��ֹ���ƿ�ѡ����浲ס��Ӧ����
		if (!g_pSttMUTestIecCbSelWidget->isHidden())
		{
			g_pSttMUTestIecCbSelWidget->hide();
			CTickCount32 oTickCount;
			oTickCount.DoEvents(20);
			bShowMUTestIecCbSelWidget = TRUE;
		}
	}

	CXMessageBox::information(this, strTitle, strMsg);

	if (bShowMUTestIecCbSelWidget)
	{
		g_pSttMUTestIecCbSelWidget->show();
	}
}

//zhouhj 2023.12.6 ��window����������
void QSttTestCntrFrameBase::slot_OnConfigDevice(CDataGroup *pCommCfg)
{
	if (g_pTheSttTestApp->m_pTestCtrlCntr != NULL)
	{
		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_ConfigDevice(pCommCfg);
	}
}

void QSttTestCntrFrameBase::OnCmd_DeviceCom()
{
    //OpenMenuHtmlFile(STT_MACROPARA_HTML_NAME_DEVCOMM);
}

void QSttTestCntrFrameBase::OnCmd_LangSettingView()
{
	QSttLanguageCfgDialog dlg(this);
	dlg.exec();
}

void QSttTestCntrFrameBase::OnCmd_ReportSetting()
{
	QSttReportHeadSetDlg dlg(&m_pTestCtrlCntrBase->m_oTestReportHead, this);
#ifdef _USE_SoftKeyBoard_	
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
#endif
	dlg.exec();

	if (dlg.m_nOkFlag == 1)
	{
		
// 		m_pTestCtrlCntrBase->FillReport(&m_pTestCtrlCntrBase->m_oTestReportHead);//ˢ�±���ͷ

		CDvmData *pData = (CDvmData *)m_pTestCtrlCntrBase->m_oTestReportHead.FindByID("TestAppInfor");
		if ((pData != NULL)&&(pData->m_strValue != _T("0")))
		{
			m_bHasUpdateRptStartTestTime = FALSE;	
		}

		if (!dlg.m_bUpataHeadHtml)//ֻ��ѡ�е�ʱ��Ż����
		{
			InsertReportHead(&m_pTestCtrlCntrBase->m_oTestReportHead);
		}

		UpdateReportHead(&m_pTestCtrlCntrBase->m_oTestReportHead);
		m_pTestCtrlCntrBase->SaveReportHead();
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSttTestCntrFrameBase::InsertReportHead( CDataGroup *pSttReport )
{
	if (pSttReport == NULL)
	{
		return;
	}

	POS pos = pSttReport->GetHeadPosition();
	CDataGroup *p = NULL;
	CString strItemID;

	// 20240510 suyang ���¹�ѡ����Ҫ��ȫ��ɾ�����ٽ������
	while (pos != NULL)
	{
		p = (CDataGroup*)pSttReport->GetNext(pos);

		strItemID = pSttReport->m_strID + "$" + p->m_strID;
        //m_pSttReportViewHtml->DeleteRptHtml("", strItemID);
	}
	

    //m_pSttReportViewHtml->AddInsertHeadCmd(pSttReport->m_strID,"");
	
}



void QSttTestCntrFrameBase::OnCmd_ChRsMaps()
{
	QChMapsDlg oChMapsDlg(this);
	oChMapsDlg.setFont(m_gFont);
	oChMapsDlg.initUI();
//	connect(&oChMapsDlg, SIGNAL(sig_UpdateChRsMaps(BOOL)), this, SLOT(slot_UpdateChRsMaps(BOOL)));
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oChMapsDlg, Keyboard::NUMBER);
	if (oChMapsDlg.exec() == QDialog::Accepted)
	{
		slot_UpdateChRsMaps(oChMapsDlg.m_bSysParasHasChanged);
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (oChMapsDlg.exec() == QDialog::Accepted)
	{
		slot_UpdateChRsMaps(oChMapsDlg.m_bSysParasHasChanged);
#ifdef _USE_SoftKeyBoard_//zhouhj 2023.8.28 ϵͳ�����޸ĺ�,���¼���
		g_oSttTestResourceMngr.UpdateSoftKeyboardType();
#endif
	}
#endif

//	disconnect(&oChMapsDlg, SIGNAL(sig_UpdateChRsMaps(BOOL)), this, SLOT(slot_UpdateChRsMaps(BOOL)));
}

void QSttTestCntrFrameBase::OnCmd_ItemListView()
{

}

void QSttTestCntrFrameBase::OnCmd_DeviceComView()
{

}

void QSttTestCntrFrameBase::OnCmd_SequenceView()
{

}

void QSttTestCntrFrameBase::OnCmd_InfoView()
{
	if(m_pInfoWidget != NULL)
	{
		SetActiveWidget(m_pInfoWidget, ActiveWidgetType_Other);
	}
}

void QSttTestCntrFrameBase::OnCmd_LogView()
{

}

void QSttTestCntrFrameBase::OpenMenuHtmlFile(const CString &strMemuFileName)
{
	if (IsHtmlParasEditOpen())
	{
		return;
	}

    //m_pSysParaEditView = new QSttMacroParaEditViewHtml();
    //m_pSysParaEditView->setParent(this);
    //m_pSysParaEditView->setGeometry(m_rcWorkArea);
    //m_pSysParaEditView->OpenHtmlFile(strMemuFileName);//
    //SetActiveWidget(m_pSysParaEditView, ActiveWidgetType_Paras_Html);
}

void QSttTestCntrFrameBase::OnCmd_VersionInfo()
{
	//OpenMenuHtmlFile(STT_MACROPARA_HTML_NAME_VERSIONINFOR);
	QDeviceInforDlg oDevInforDlg(this);
	oDevInforDlg.setFont(*g_pSttGlobalFont);
	oDevInforDlg.initUI(FALSE);
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		oDevInforDlg.resize(850,500);
		oDevInforDlg.setFixedHeight(500);
	}

	connect(this, SIGNAL(sig_UpdateTestResource()), &oDevInforDlg, SLOT(slot_UpdateTestResource()));

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oDevInforDlg, Keyboard::NUMBER);
	oDevInforDlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	oDevInforDlg.exec();
#endif

	disconnect(this, SIGNAL(sig_UpdateTestResource()), &oDevInforDlg, SLOT(slot_UpdateTestResource()));
}

void QSttTestCntrFrameBase::OnCmd_AuxIPSet()
{
}

void QSttTestCntrFrameBase::OnCmd_Liveupdate()
{
}

void QSttTestCntrFrameBase::OnCmd_ULiveupdate()
{

}

void QSttTestCntrFrameBase::OnCmd_LiveupdateDevice()
{

}

void QSttTestCntrFrameBase::OnCmd_CloudConfig()
{

}

void QSttTestCntrFrameBase::OnCmd_UpdateAdjCoef()
{

}

void QSttTestCntrFrameBase::OnCmd_RegisterRemoteTest()
{

}

void QSttTestCntrFrameBase::OnCmd_RemoteRegistAssist()
{

}

void QSttTestCntrFrameBase::OnCmd_DownloadTestTemplate()
{

}

void QSttTestCntrFrameBase::OnCmd_DownloadPpTemplate()
{

}

void QSttTestCntrFrameBase::OnCmd_UploadingReport()
{

}

void QSttTestCntrFrameBase::slot_OnUpdateRtSyncTime(CDataGroup *pRtSycTime)
//long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
//												 long nPowerAC, long nBatCap,long nUSB )
{
	//0,0,0,-1,-1,-1,-1,-1,-1
	long nSyn = 0, nSecond = 0, nNSecend = 0,nTimeZone = 0, n4G = -1,  nWifi = -1,  nBle = -1;
	long nPowerAC = -1,  nBatCap = -1, nUSB = -1 ;
	float fUdc = 0.0f;

	// 			long nSecond = 0,nNSecend = 0,nSyn = 0;
	// 			stt_GetDataValueByID(pRtDataGroup, _T("Sync"), nSyn);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("Utc_s"), nSecond);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("Utc_ns"), nNSecend);
	// 
	// 			long n4G = 0,nWifi = 0,nBle = 0,nPowerAC = 0,nBatCap = 0, nUSB = 0;
	// 			stt_GetDataValueByID(pRtDataGroup, _T("4G"), n4G);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("Wifi"), nWifi);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("Ble"), nBle);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("PowerAC"), nPowerAC);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("BatCap"), nBatCap);
	// 			stt_GetDataValueByID(pRtDataGroup, _T("USB"), nUSB);

	stt_GetDataValueByID(pRtSycTime, _T("Udc"), fUdc);//dingxy 20250319 ��RTDATA��ʵʱ��ȡUdc
	if (fUdc != m_fUdc)
	{
		m_fUdc = fUdc;
	}

	CString str;
	if (fUdc != 0)
		str.Format("%d", STT_LIGHT_BTN_INDEX_Yellow);
	else
		str.Format("%d", STT_LIGHT_BTN_INDEX_Red);

	stt_SetDataValueByID(pRtSycTime, _T("Udc"), str);//�˴��޸Ķ�ȡ��Udc��ֵ����������Ϊ��ɫ��Ӧֵ������UpdataDataButtons�Ὣ��ɫˢ��ΪĬ��ֵ

	//ͨ��GPS���õľ�ȷʱ����ͬ�������Դ�ڵļ�ʱ��,�����ǻ�ͼ��ʱ��
	if(IsTestStarted() && m_pStateMonitorWidget)
	{
		stt_GetDataValueByID(pRtSycTime, _T("Utc_s"), nSecond);
		stt_GetDataValueByID(pRtSycTime, _T("Utc_ns"), nNSecend);
		stt_GetDataValueByID(pRtSycTime, _T("TimeZone"), nTimeZone);//zhouhj 20230613 ����ʱ����

		double dLocalTime = nSecond + nTimeZone*60*60 + nNSecend * 0.000000001;
		m_pStateMonitorWidget->UpdateLocalTime(dLocalTime);
	}

	if ((m_pMacroEditView != NULL)&&(CXSmartCapMngr::GetSttCap61850_Global() != NULL))
	{
		CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();
		pXSttCap_61850->UpdateMUTimeRlt(pRtSycTime);

// 		if ((g_pTheSttTestApp->GetCurrUI_ID() == STT_ORG_MACRO_ManualTest)&&
// 			pXSttCap_61850->UpdateMUTimeRlt(pRtSycTime))
// 		{
// 			QSttMacroParaEditViewManual *pManualUI = (QSttMacroParaEditViewManual*)m_pMacroEditView;
// //			pManualUI->UpdateMUTimeAccurRlt_PPS();
// //			pManualUI->UpdateMUTimeAccurRlt_PPS(pXSttCap_61850->m_pDataset_MUTimeRlt);
// 		}
 	}

	//2022-6-10  lijunqing ������¶��󣬲�������Ի�ʱ��
	m_oDataBtnsMngr.UpdataDataButtons(pRtSycTime);

	//���ڵ�Դ��Ϣ��һ��group,��Ҫ���⴦��
	m_oDataBtnsMngr.UpdataDataButtons(pRtSycTime, "BatCap");

	//����GPS��һ��group,��Ҫ���⴦��
	m_oDataBtnsMngr.UpdataDataButtons(pRtSycTime, "GPS");
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("GPS"));

	//2022-6-10 yizejun ��Ҫɾ��copy������rtsyctime

	//20230614 zhouhj ���ڱ��������ͼ
// 	if (g_oLocalSysPara.m_nHasSyn)
// 	{
// 		OnCmd_ScreenShot();
// 	}

	//chenling 20230412	
	POS pos=pRtSycTime->GetHeadPosition();
	CDataGroup *pFiberMsgGroup=NULL;
	CExBaseObject *pCurrObj = NULL;
	g_oSttTestResourceMngr.m_oFiberMsgGroup.DeleteAll();

	while (pos)
	{
		pCurrObj = pRtSycTime->GetNext(pos);

		if (pCurrObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pFiberMsgGroup = (CDataGroup *)pCurrObj;
		if (pFiberMsgGroup->m_strDataType=="LightPower")
		{		
			pRtSycTime->Remove(pCurrObj);
			POS pos2 = pFiberMsgGroup->GetHeadPosition();
			CExBaseObject * pData = NULL;

			while(pos2)
			{
				pData = (CExBaseObject *)pFiberMsgGroup->GetNext(pos2);	
				g_oSttTestResourceMngr.m_oFiberMsgGroup.AddNewChild(pData);
			}
			
		}
	}

// 	if(m_bUpdateOutputPowerFromRealTime)//�����������
// 	{
// 		OnUpdateRtCurrModules(pRtSycTime);//dingxy 20250320 RTDATA��CurrModules�ڵ�Ǩ�Ƶ�GetSystemState��
// 	}
	if(m_bUpdateHardCfgFromRealTime)//����Ӳ������
	{
		OnUpdateRtHardConfig(pRtSycTime);
	}

	//20241113 suyang ��RtDate���ݸ��º󱣴�ϵͳ�����Լ�����ͨ��ӳ�����ݲ��·���������
//-------------------------------------------------------
// 	if (m_bIsRtDataUpdateChMaps_System)
// 	{
// 		if ((g_oSystemParas.m_nHasAnalog == 1)&&(g_oSystemParas.m_nHasDigital == 0)&&(g_oSystemParas.m_nHasWeek == 0))
// 		{
// 			m_bIsRtDataUpdateChMaps_System = FALSE;
// 			g_oSttTestResourceMngr.SaveSystemParasFile();
// 			g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&g_oSttTestResourceMngr.m_oChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital);
// 			g_oSttTestResourceMngr.SaveCurChMapsFile();
// 
// 			Cmd_SendChMapsConfig();
// 			Cmd_SendSystemConfig();//20241113 suyang ϵͳ����MergeCurTerminal�ı�Ҳ��Ҫ����
// 		}
// 	
// 	}

//-----------------------------------------------------------------------------------------
	
	g_oLocalSysPara.m_nRTData_Num++;
	OnUpdateRtInputDev(pRtSycTime);


	if (pRtSycTime != NULL)
	{
	delete pRtSycTime;
		pRtSycTime = NULL;
	}

	//�����ܵĸ��²μ�����
	/*
	QSttGpsButton::UpdateState(CDataGroup *pDataGroup)
	QSttBatteryButton::UpdateState(CDataGroup *pDataGroup)
	QSttBlueToothButton::UpdateState(CDataGroup *pDataGroup) //��Ϊ���͵����ݺ������ļ���һ�£��������ص�������
	*/

/*
	QSttToolButtonBase* pButton = m_oDataBtnsMngr.FindButtonByID("GPS");

	if (pButton == NULL)
	{
		return;
	}

	CString strGpsTime;

	if (nSyn != g_oLocalSysPara.m_nHasSyn)
	{
		g_oLocalSysPara.m_nHasSyn = nSyn;

		if (g_oLocalSysPara.m_nHasSyn == 0)
		{
			strGpsTime = tr("δ��ʱ");
		} 
		else
		{
			strGpsTime = QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss")/ *+QString("%1").arg((int)(nNSecend/1000000))* /;
		}
	}
	else if (nSyn > 0 )
	{
		strGpsTime = QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss")/ *+QString("%1").arg((int)(nNSecend/1000000))* /;
	}
	
	if (strGpsTime != _T(""))
	{
		pButton->setText(strGpsTime);
	}

	pButton = m_oDataBtnsMngr.FindButtonByID("4G");
	pButton->SetPic(n4G);

	pButton = m_oDataBtnsMngr.FindButtonByID("Wifi");
	pButton->SetPic(nWifi);

	pButton = m_oDataBtnsMngr.FindButtonByID("BlueTooth");
	pButton->SetPic(nBle);

	pButton = m_oDataBtnsMngr.FindButtonByID("USB");
	pButton->SetPic(nUSB);

	pButton = m_oDataBtnsMngr.FindButtonByID("Battery");
	if(nPowerAC > 0)
	{
		QSttBatteryButton* pBtn = (QSttBatteryButton*)pButton;
		if(pBtn->m_nCurPic == 4)
		{
			pBtn->SetPic(0);
		}
		else
		{
			pBtn->m_nCurPic++;
			pBtn->SetPic(pBtn->m_nCurPic);
		}
	}
	else
	{
		if (nBatCap > 70)
		{
			pButton->SetPic(4);
		}
		else if (nBatCap > 50 && nBatCap <= 70)
		{
			pButton->SetPic(3);
		}
		else if (nBatCap > 30 && nBatCap <= 50)
		{
			pButton->SetPic(2);
		}
		else if (nBatCap > 10 && nBatCap <= 20)
		{
			pButton->SetPic(1);
		}
		else if (nBatCap > 0 && nBatCap <= 5)
		{
			pButton->SetPic(0);
		}
	}
*/

}

void QSttTestCntrFrameBase::OnUpdateRtCurrModules(CDataGroup *pRtSycTime)	//20240530 xueyangfan ��ȡʵʱ���ݸ��µ�ǰ��λ״̬
{
	if (pRtSycTime == NULL)
	{
		return;
	}

	long nValue = 0;								
	CExBaseObject* pFindObj = pRtSycTime->FindByID("CurrModules");

	if (pFindObj == NULL)
	{
		return;
	}

	if (pFindObj->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pCurrModules = (CDataGroup*)pFindObj;
	pFindObj = pCurrModules->FindByID("CurrModuleNum");

	if (pFindObj == NULL)
	{
		return;
	}

	if (pFindObj->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData*)pFindObj;
	long nNumValue = CString_To_long(pDvmData->m_strValue);
	CString strModuleID;
	CExBaseList *pFindList = NULL;

	for (int nIndex = 0; nIndex < nNumValue; nIndex++) 
	{
		strModuleID.Format("CurrModule%d",nIndex);

		pFindList = (CExBaseList*)pCurrModules->FindByID(strModuleID);

		if (pFindList == NULL)
		{
			continue;
		}

		CDvmData *pCurModuleAttr = (CDvmData *)pFindList->FindByID("ModulePos");

		if (pCurModuleAttr != NULL) 
		{
			g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nModulePos = CString_To_long(pCurModuleAttr->m_strValue);
		}

		pCurModuleAttr = (CDvmData *)pFindList->FindByID("CurModuleGear");

		if (pCurModuleAttr != NULL)
		{
			g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nIPowerMode = CString_To_long(pCurModuleAttr->m_strValue);
		}

		pCurModuleAttr = (CDvmData *)pFindList->FindByID("MaxPortVol");

		if (pCurModuleAttr != NULL)
		{
			g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_fVoltSet = CString_To_double(pCurModuleAttr->m_strValue);
		}

		pCurModuleAttr = (CDvmData *)pFindList->FindByID("MergeCurTerminal");

		if (pCurModuleAttr != NULL)
		{
			g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nMergeCurTerminal = CString_To_double(pCurModuleAttr->m_strValue);
		}

		pCurModuleAttr = (CDvmData *)pFindList->FindByID("LargeCurOutTerm");

		if (pCurModuleAttr != NULL)
		{
			g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nLargeCurOutTerm = CString_To_double(pCurModuleAttr->m_strValue);
		}
	}
}

void QSttTestCntrFrameBase::OnUpdateRtInputDev(CDataGroup *pRtSycTime)		//20240530 xueyangfan ��ȡʵʱ���ݸ�������������
{
	if (pRtSycTime ==NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
	CExBaseObject *pFindObj = pRtSycTime->FindByID("InputDev");

	if (pFindObj == NULL)
	{
		return;
	}

	if (pFindObj->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pCurrMouseKeyBoard = (CDataGroup*)pFindObj;

	CDvmData *pVerIdxData = (CDvmData*)pCurrMouseKeyBoard->FindByID("VerIdx");
	CDvmData *pMouseData = (CDvmData*)pCurrMouseKeyBoard->FindByID("Mouse");
	CDvmData *pKeybData = (CDvmData*)pCurrMouseKeyBoard->FindByID("QWS_KEYBOARD");

	if (pVerIdxData != NULL)
	{
		long nValue = CString_To_long(pVerIdxData->m_strValue);

		if (g_oLocalSysPara.m_nTesterVerIdx != nValue)
		{
			g_oLocalSysPara.m_nTesterVerIdx = nValue;

			if (pMouseData != NULL)
			{
                nValue = CString_To_long(pMouseData->m_strValue);
    //            qputenv("Mouse", pMouseData->m_strValue.GetString());

				// 				if (g_oLocalSysPara.m_nTesterHasMouse != nValue)
				// 				{
				// 					g_oLocalSysPara.m_nTesterHasMouse = nValue;
				// 				}
                if(nValue == 0)
				{
                    QApplication::setOverrideCursor(Qt::BlankCursor);
				}
                if(nValue == 1)
				{
                    QApplication::setOverrideCursor(Qt::ArrowCursor);
                }
	
			if (pKeybData != NULL)
			{
                //qputenv("QWS_KEYBOARD", pKeybData->m_strValue.GetString());

				// 				if (g_oLocalSysPara.m_strTesterKeyBoardString != pKeybData->m_strValue)
				// 				{
				// 					g_oLocalSysPara.m_strTesterKeyBoardString = pKeybData->m_strValue;
				// 				}
			}
        }
	}
}
#endif
}

void QSttTestCntrFrameBase::slot_UpdateAuxDCOutput()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return;
	}

	CDataGroup oGroup;
	CSttDataGroupSerializeRegister oRegister(&oGroup);
	stt_xml_serialize_AuxDC(&g_oSystemParas, &oRegister);
	m_pTestCtrlCntrBase->Ats_SetParameter(STT_MACRO_ID_AuxDCOutput,&oGroup);

	if(g_pTheSttTestApp->m_pTestMacroUI)
	{
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		// 	emit sig_UpdateAuxDCEdit();//20240603 suyang L336D���½��渨��ֱ���༭��
	((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->UpdateAuxDCEdit();
	}
		//	Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_SystemConfig);
	}
}

void QSttTestCntrFrameBase::slot_UpdateChRsMaps( BOOL bSysParasHasChanged )
{
	if(g_pTheSttTestApp->m_pTestMacroUI)
	{
		if(g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		CSttMacroParaEditViewOriginal* pOri = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
		pOri->m_bChMapsChanged = TRUE;
		OnUpdateTestResource(FALSE);

			// 		if (bSysParasHasChanged)//2023.7.4 zhouhj �����Ѿ��·�ϵͳ������������,�˴������ٱ��
			// 		{
			// 			pOri->m_bSystemParasChanged = TRUE;
			// //			pOri->m_bIECParasChanged = TRUE;
			// 		}
		}
	}

	if (bSysParasHasChanged)
	{
		Cmd_SendSystemConfig();
	}

	Cmd_SendChMapsConfig();
}


void QSttTestCntrFrameBase::slot_ReturnPrevActiveWidget()
{
	m_oTimerHtmlViewReturn.stop();
	
	m_pActiveWidget = NULL;
    //m_pSysParaEditView->hide();
    //m_pSysParaEditView->stop();
    //m_pSysParaEditView->close();
    //m_pSysParaEditView->deleteLater();
    //m_pSysParaEditView = NULL;

	if (m_nPrevActiveWidgetType == ActiveWidgetType_None)
	{
		SetActiveWidget(NULL, ActiveWidgetType_None);
	}
	else
	{
		SetActiveWidget(m_pPrevActiveWidget, m_nPrevActiveWidgetType);
	}
}

void QSttTestCntrFrameBase::slot_IecCfgDataMngrUpdate()
{
	if (g_pSttIecRecordCbWidget)
	{
		g_pSttIecRecordCbWidget->m_bStopTimerUpdate = TRUE;
	}

	g_oSttTestResourceMngr.SaveDefaultIec61850Config();//����xml

	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_IECConfig);//�·�����
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("��ǰ������Ϊ��.")*/g_sLangTxt_Gradient_EmptyCurTI.GetString()); //lcq

		if (m_pSttIecRecordMainWidget != NULL)
		{
			m_pSttIecRecordMainWidget->UpdateIecfg();
		}
		return;
	}

	Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_IECConfig);//�·�����

	if ((g_pTheSttTestApp->m_pTestMacroUI != NULL)&&(m_pMacroEditView!=NULL))//�жϵ�ǰ�Ƿ�����˲��Թ���ģ��,���жϵ�ǰ���Թ���ģ���Ƿ�Ϊ��ҳ
	{
		if (!g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())//���½���
		{
			CSttMacroParaEditViewOriginal* pOriginal = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pOriginal->UpdateGoutTab(TRUE);//zhouhj20220319 �ڷ���ҳ�������ʱ,����
			pOriginal->UpdateFT3Tab(TRUE);//chenling20230518
		}
	}

	if (m_pSttIecRecordMainWidget != NULL)
	{
		m_pSttIecRecordMainWidget->UpdateIecfg();
	}
	// 	CString strItemPath = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
	// 	CString strMacroID = _T("");
	// 
	// 	strItemPath.Format(_T("%s$%s$%s"),strItemPath.GetString(),STT_ITEMS_ID_BEFORETEST,STT_CMD_TYPE_SYSTEM_IECConfig);
	// 	m_pTestCtrlCntrBase->Ats_SetItemPara(strItemPath, STT_CMD_TYPE_SYSTEM_IECConfig);

	if (m_pMacroEditView)
	{
		int nBeforeParaMode = g_oSystemParas.m_nParaMode;
		m_pMacroEditView->UpdatePrimParaSetUI();
		int nParaMode = g_oSystemParas.m_nParaMode;
		
		if (nBeforeParaMode != nParaMode)
		{
			Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_SystemConfig);

		}
		
	}
}

void QSttTestCntrFrameBase::Cmd_SendChMapsConfig()
{
// 	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ������Ϊ��,�޷��·�ͨ��ӳ���ļ�."));
// 		return;
// 	}

	Ats_SetItemPara(STT_CMD_TYPE_ADJUST_ChMapsConfig);
// 	CString strItemPath = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
// 	strItemPath.Format(_T("%s$%s$%s"),strItemPath.GetString(),STT_ITEMS_ID_BEFORETEST,STT_CMD_TYPE_ADJUST_ChMapsConfig);
// 	m_pTestCtrlCntrBase->Ats_SetItemPara(strItemPath, STT_CMD_TYPE_ADJUST_ChMapsConfig);
}

void QSttTestCntrFrameBase::Cmd_SendSystemConfig()
{
// 	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ������Ϊ��,�޷��·�ϵͳ��������."));
// 		return;
// 	}

	Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_SystemConfig);
// 	CString strItemPath = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
// 	strItemPath.Format(_T("%s$%s$%s"),strItemPath.GetString(),STT_ITEMS_ID_BEFORETEST,STT_CMD_TYPE_SYSTEM_SystemConfig);
// 	m_pTestCtrlCntrBase->Ats_SetItemPara(strItemPath, STT_CMD_TYPE_SYSTEM_SystemConfig);
}

void QSttTestCntrFrameBase::UpdateSysConfig()
{
	emit sig_UpdateSysConfig();
}

void QSttTestCntrFrameBase::UpdatePowerGear()
{
	emit sig_UpdatePowerGear();
}

void QSttTestCntrFrameBase::New_SysConfig()
{

}

void QSttTestCntrFrameBase::SaveMacroTestUI_ParaFile(const CString &strNameAdd)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (! g_pTheSttTestApp->m_pTestMacroUI->IsUIWeb())
	{
		return;
	}

	m_pTestCtrlCntrBase->SaveMacroTestUI_ParaFile(strNameAdd);
}

CEventResult* QSttTestCntrFrameBase::GetCurEventResult()
{
	return &m_pTestCtrlCntrBase->m_oCurrEventResult;
}

void QSttTestCntrFrameBase::Ats_SetItemPara(const CString &strItemID)
{
	if (g_nLogDebugInfor)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">> begin SttTestCntrFrameBase::Ats_SetItemPara(%s) >>"), strItemID.GetString());
	}

	CString strItemPath;
	CExBaseList oList;
	m_pTestCtrlCntrBase->GetAllItemsByID(strItemID, oList);

	POS pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		CSttItemBase *pItemBase = (CSttItemBase *)oList.GetNext(pos);
		stt_gb_get_itempath_id(pItemBase, strItemPath);

		m_pTestCtrlCntrBase->Ats_SetItemPara(strItemPath, strItemID);
	}
	

	if (oList.GetCount() == 0)//���Ϊ��ʱ,��Ϊϵͳ���á�IEC���õ���ֱ���·�
	{
		if ((strItemID == STT_CMD_TYPE_SYSTEM_SystemConfig)||
			(strItemID == STT_CMD_TYPE_SYSTEM_IECConfig)||
			(strItemID == STT_CMD_TYPE_ADJUST_ChMapsConfig))
		{
			m_pTestCtrlCntrBase->Ats_SetItemPara(_T(""), strItemID);
		}
	}

	oList.RemoveAll();

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">> end SttTestCntrFrameBase::Ats_SetItemPara >>"));
	}

}

void QSttTestCntrFrameBase::Ats_SetItemPara_RsltExpr(CExBaseObject *pItem)
{

}

void QSttTestCntrFrameBase::SaveCharacteristicsData(CString strFile)
{
	if (m_pCharLibWidget == NULL)
	{
		return ;
	}

	//2022-9-3  lijunqing
	//2022-9-8 yizejun ���Ѿ���һ�������ļ�ʱ�л����ܻ���Ϊm_pTestMacroUI�л�ȡ�������ƶ������¹��ܵ������ļ�
	//�������л�����ʱ����ɵ��ļ����������ģ�������
	if(!strFile.GetLength())
	{
		GetCharacteristicsFile(g_pTheSttTestApp->m_pTestMacroUI, strFile);
	}
	
	m_pCharacteristics->SaveXmlFile(strFile,CCharacteristicXmlRWKeys::g_pXmlKeys);
}

void QSttTestCntrFrameBase::slot_OnFreeCommCmdWzdWidget()
{

}

void QSttTestCntrFrameBase::slot_CloseMenu()
{
}

BOOL QSttTestCntrFrameBase::IsContinueCreateNew()
{
	return FALSE;
}

long QSttTestCntrFrameBase::GetGbItemCount()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return 0;
	}

	return m_pTestCtrlCntrBase->GetGbItemCount();
}

CString QSttTestCntrFrameBase::GetCurrentUI_ID()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return "";
	}

	if(!m_pTestCtrlCntrBase->GetCurrTestMacroUI())
	{
		return "";
	}

	return m_pTestCtrlCntrBase->GetCurrTestMacroUI()->m_strUI_ID;
}

//����װ�����ͣ����˿ɹ�ѡ��Ĺ���
void QSttTestCntrFrameBase::InitTestMacroUI_by_DeviceType(CSttMacroTestUI_TestMacroUIMngr *pTestMacroUIMngr)
{
	return;
}

CSclStation* QSttTestCntrFrameBase::GetSclStation()
{
	return &m_pTestCtrlCntrBase->m_oSclStation;
}

void QSttTestCntrFrameBase::SetDatas(CDataGroup *pParas)
{
	m_pMacroEditView->SetDatas(pParas);
}

void QSttTestCntrFrameBase::ClearReportRslts_Html()
{

}

BOOL QSttTestCntrFrameBase::IsNeedAddAft()
{
	//Ĭ����Ҫ���
	return TRUE;
}

//��Ŀճ���󣬴�����
void QSttTestCntrFrameBase::ItemPaste_RootNode(CSttItems *pDestItems, CExBaseObject *pCurrentSel)  
{

}

void QSttTestCntrFrameBase::UpdateStatusBar_Btns(const CString &strID, const CString &strValue)
{
	CDataGroup dataGroup;
	dataGroup.AddNewData(strID, strValue);
	m_oDataBtnsMngr.UpdataDataButtons(&dataGroup);
}

// void QSttTestCntrFrameBase::slot_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData)
// {
// 	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_pMacroEditView == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (!IsTestStarted())
// 	{
// 		return;
// 	}
// 
// 	if ((g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_MUTimingAccurTest)||
// 		(g_pTheSttTestApp->m_pTestMacroUI->m_strID == STT_ORG_MACRO_MUPunctAccurTest))
// 	{
// 		QSttMacroParaEditViewManual *pManualUI = (QSttMacroParaEditViewManual*)m_pMacroEditView;
// 		pManualUI->UpdateMUTimeAccurRlt_NOPPS(pSVDelayData);
// 	}
// }

BOOL CharVar_CalScriptValue(CCharInterfaceVariable *pCharVar)
{
	if (g_pGlobalDatas == NULL)
	{
		return FALSE;
	}

	double dValue = 0;

	if (Stt_CalParaExpression(pCharVar->m_strScript, dValue, TRUE))
	{
		pCharVar->m_strValue.Format(_T("%f"), dValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CExBaseObject* CharVar_GetScriptValObj(CCharInterfaceVariable *pCharVar)
{
	if (g_pGlobalDatas == NULL)
	{
		return NULL;
	}

	CExBaseObject* pData = g_pGlobalDatas->FindByID(pCharVar->m_strScript);

	return pData;
}

CString* CharVar_CalScriptValue(CExBaseObject *pData)
{
	ASSERT (pData != NULL);
	CDvmData *pDataObj = (CDvmData*)pData;
	return &pDataObj->m_strValue;
}

void CharVar_CalScriptValue(CExBaseObject *pData, CString &strValue)
{
	ASSERT (pData != NULL);
	CDvmData *pDataObj = (CDvmData*)pData;
	strValue = pDataObj->m_strValue;
}

BOOL Stt_CalParaExpression(const CString &strExpress, double &dValue, BOOL bLogError, CValues *pValues)
{
	CEpExpression oEpExp;

	if (strExpress.GetLength() == 0)
	{
		return FALSE;
	}

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("���ʽ��%s�� ����")*/, strExpress.GetString());
		return FALSE;
	}

	CString strValue;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		if (Stt_CalParaExp_FindValue(pValues, pExpVar->m_strVarID, strValue))
		{
#ifdef _UNICODE
			pExpVar->m_dValue = _wtof(strValue);
#else
			pExpVar->m_dValue = atof(strValue.GetString());
#endif
		}
		else
		{
			if (bLogError)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("���ʽ������%s�� ����")*/, pExpVar->m_strVarID.GetString());
				bTrue = FALSE;
			}
		}
	}

	oEpExp.Value(dValue);

	return bTrue;
}

BOOL Stt_CalParaExp_FindValue(CValues *pValues, const CString &strVarID, CString &strValue)
{
	if (pValues != NULL)
	{
		if (pValues->GetValue(strVarID, strValue))
		{
			return TRUE;
		}
	}

	if (g_pGlobalDatas != NULL)
	{
		if (g_pGlobalDatas->GetDataValue(strVarID, strValue))
		{
			return TRUE;
		}
	}

	return FALSE;
}


void QSttTestCntrFrameBase::OnCmd_CustomSet()
{
	//�Զ�������

	SttCustomSetDlg dlg(this);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::NUMBER);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttTestCntrFrameBase::OnCmd_FileMngr()
{
	QSttFileMngrDlg dlg(this);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttTestCntrFrameBase::OnCmd_LumPowerView()
{
	//zhouhj 2023.11.25 ����330�Ȼ���,�������������⹦�ʲ�����Դ����
	if (m_pTestCtrlCntrBase != NULL)
	{
		CDataGroup oGroup;
		m_pTestCtrlCntrBase->Ats_SetParameter(STT_MACRO_ID_LcPowerTest,&oGroup);
	}

	QLuminousPowerDlg dlg(this);
	CDataGroup *pFiberCopy=(CDataGroup*)(&g_oSttTestResourceMngr.m_oFiberMsgGroup)->Clone();
	dlg.InitData(pFiberCopy);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();	
#endif
}

void QSttTestCntrFrameBase::OnCmd_OutputDebug()
{
//     QOutPutDebug dlg(this);
// 	//dlg.InitUI();
// 
// #ifdef _USE_SoftKeyBoard_
// 	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
// 	dlg.exec();
// 	QSoftKeyBoard::ReAttachObj();
// #else
// 	dlg.exec();	
// #endif
}

void QSttTestCntrFrameBase::OnCmd_Minimize()
{
	this->showMinimized();
}

void QSttTestCntrFrameBase::OnCmd_BinConfig()
{
    //QBinReverseCfgDialog oBinReverseCfgDialog;
    //oBinReverseCfgDialog.exec();
}

void QSttTestCntrFrameBase::OnCmd_AuxDCOutput()
{
	//20240116 suyang ������ʱ������ֹ�Զ����Ի�û�����ײ㣬�ײ���Ի�û����
#ifdef _PSX_QT_LINUX_
	CTickCount32 oTickCount;
	oTickCount.DoEvents(1000);
#endif


	UpDateUdcVal();
	if (!xlang_IsCurrXLanguageChinese()/*g_oSttSystemConfig.GetDevModel() == "L336EXi"*/)
	{
		QAuxDCOutputDlg_L336EXi oAuxDCOutputDlg(this);
		oAuxDCOutputDlg.initUI();
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::AttachObj(&oAuxDCOutputDlg, Keyboard::NUMBER);
		if (oAuxDCOutputDlg.exec() == QDialog::Accepted)
		{
			slot_UpdateAuxDCOutput();
		}
		QSoftKeyBoard::ReAttachObj();
#else
		if (oAuxDCOutputDlg.exec() == QDialog::Accepted)
		{
			slot_UpdateAuxDCOutput();
		}
#endif
	}
	else
	{
	QAuxDCOutputDlg oAuxDCOutputDlg(this);
	oAuxDCOutputDlg.initUI();
#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(&oAuxDCOutputDlg, Keyboard::NUMBER);
	if (oAuxDCOutputDlg.exec() == QDialog::Accepted)
	{
		slot_UpdateAuxDCOutput();
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (oAuxDCOutputDlg.exec() == QDialog::Accepted)
	{
		slot_UpdateAuxDCOutput();
	}
#endif
	}
	//connect(&oAuxDCOutputDlg, SIGNAL(sig_UpdateAuxDCOutput()), this, SLOT(slot_UpdateAuxDCOutput()));

	//disconnect(&oAuxDCOutputDlg, SIGNAL(sig_UpdateAuxDCOutput()), this, SLOT(slot_UpdateAuxDCOutput()));
}

void QSttTestCntrFrameBase::OnCmd_IecCapDialog()
{
	InitSttIecRecord();
	QSttIecCapDialog oSttIecCapDialog(this);
	oSttIecCapDialog.InitUI();
	connect(m_pOutputWidget, SIGNAL(sig_refreshLog(QString)), oSttIecCapDialog.m_pSttOutPutWidget, SLOT(slot_refreshOutput(QString)));
	oSttIecCapDialog.show();

	oSttIecCapDialog.StartDetect(true);
	oSttIecCapDialog.exec();
}

void QSttTestCntrFrameBase::OnCmd_TransPcapFile()
{

}

BOOL QSttTestCntrFrameBase::CreateCommCfgPkgMnWidget()
{
	if(m_pSttCommCfgPkgWidget != NULL)
	{
		return FALSE;
	}

	m_pSttCommCfgPkgWidget = new QSttCommCfgPkgMonitorWidget(this);
	m_pSttCommCfgPkgWidget->setParent(this);
	m_pSttCommCfgPkgWidget->hide();
	m_pSttCommCfgPkgWidget->setGeometry(m_rcWorkArea);
	return TRUE;
}

BOOL QSttTestCntrFrameBase::CreateRemoteCtrlWidget()
{
	if(m_pRemoteCtrlWidget != NULL)
	{
		return FALSE;
	}

	m_pRemoteCtrlWidget = new QSttMacroParaEditViewRemoteCtrl(this);
	m_pRemoteCtrlWidget->setParent(this);
	m_pRemoteCtrlWidget->hide();
	m_pRemoteCtrlWidget->setGeometry(m_rcWorkArea);
	return TRUE;
}


void QSttTestCntrFrameBase::OnCmd_PkgMonitorDlg()
{
	if (m_pSttCommCfgPkgWidget == NULL)
	{
		CreateCommCfgPkgMnWidget();
	}
	QSttCommCfgPkgMonitorDlg oSttCommCfgPkgMnDlg(m_pSttCommCfgPkgWidget,this);
	oSttCommCfgPkgMnDlg.exec();
}

void QSttTestCntrFrameBase::OnUpdateRtHardConfig( CDataGroup *pRtSycTime )
{
	if (pRtSycTime == NULL/* || !m_bUpdateHardCfgFromRealTime*/)
	{
		return;
	}

	POS pos = pRtSycTime->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		p = pRtSycTime->GetNext(pos);
		if(p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			if (p->m_strID == _T("4G"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_oPeripheral.m_b4G = CString_To_long(pFind->m_strValue);
			}
			else if (p->m_strID == _T("Wifi"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_oPeripheral.m_bNetWifi = CString_To_long(pFind->m_strValue);
			}
			else if (p->m_strID == _T("Ble"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_oPeripheral.m_bBle = CString_To_long(pFind->m_strValue);
			}
			else if (p->m_strID == _T("TimeZone"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_nTimeZone = CString_To_long(pFind->m_strValue);
			}
			else if (p->m_strID == _T("WindSpeed"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_nWindSpeed = CString_To_long(pFind->m_strValue);
			}
			//chenling 2024.9.9 ��Ļ���Ⱥͱ���ʱ����ײ��
			else if (p->m_strID == _T("LcdTimes"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_oPeripheral.m_nLcdTimes = CString_To_long(pFind->m_strValue);
			}
			else if (p->m_strID == _T("LcdLight"))
			{
				pFind = (CDvmData *)p;
				g_oSystemParas.m_oPeripheral.m_nLcdLight = CString_To_long(pFind->m_strValue);
			}
		}

	}	
}


//2024-9-10 lijunqing �Ż�ϵͳ����������Ч��

void QSttTestCntrFrameBase::slot_OpenMacroTest(unsigned long nAddrParser)
{

}

void QSttTestCntrFrameBase::emit_OpenMacroTest(unsigned long nAddrParser)
{
	emit sig_OpenMacroTest(nAddrParser);
}

#ifdef _PSX_QT_LINUX_
void QSttTestCntrFrameBase::InitMeasServer()
{
}

void QSttTestCntrFrameBase::ExitMeasServer()
{
}


#endif

void QSttTestCntrFrameBase::ShowItems_TreeView(CExBaseList *pCurTestItems)
{
	emit sig_ShowItems_TreeView(pCurTestItems);
}

//void  Stt_Global_SettingSelect(QObject *parent, const CString &sFormat, const CString &sName)
//{
////	CXDeviceModel *pXDeviceModel = &((CSttTestCtrlCntrNative*)(g_pTheSttTestApp->m_pTestCtrlCntr))->m_oXrioDeviceModel;
////	pXDeviceModel->InitDvmDevice(g_theGbSmartGenWzd->m_pDvmDevice);
////	QDeviceModelDlg_Eng oDeviceModelDlg_Eng(NULL);//��ֵ����ģʽ
////	oDeviceModelDlg_Eng.m_nDlgModeType = _FIXED_VALUE_CORRELATION_TYPE_;//��ֵ����ģʽ
////
////	//20240815 huangliang ����޸Ķ�ֵ����	
////	oDeviceModelDlg_Eng.m_sEpExpressionFormat = sFormat;
////	oDeviceModelDlg_Eng.m_sEpExpressionName = sName;
////
////	oDeviceModelDlg_Eng.InitXrioDeviceModel(pXDeviceModel);
////#ifdef _USE_SoftKeyBoard_	
////	QSoftKeyBoard::AttachObj(/*&oMainWidget*/&oDeviceModelDlg_Eng, Keyboard::NUMBER);
////#endif
////
////	if (oDeviceModelDlg_Eng.exec() == QDialog::Accepted)
////	{
////		if (oDeviceModelDlg_Eng.m_sEpExpressionFormat == "")	//20240815 huangliang //Ϊ�ձ�ʾ�޹���
////		{
////			return;
////		}
////
////		if (oDeviceModelDlg_Eng.m_bHasChangedXrio)
////		{
////			g_theGbSmartGenWzd->m_pDvmDevice->DeleteAll();
////			g_theGbSmartGenWzd->m_pDvmDevice->AppendEx(*pXDeviceModel->m_pDvmDevice_Show);
////			g_theGbSmartGenWzd->m_pDvmDevice->m_strID = pXDeviceModel->m_pDvmDevice_Show->m_strID;
////			pXDeviceModel->m_pDvmDevice_Show->RemoveAll();
////		}
////		else if (oDeviceModelDlg_Eng.m_bHasModifyDevModel)
////		{
////			pXDeviceModel->m_pDvmDevice_Show->UpdateChildren(pXDeviceModel->m_pDvmDevice_Global);
////		}
////
////		if (oDeviceModelDlg_Eng.m_bHasChangedXrio || oDeviceModelDlg_Eng.m_bHasModifyDevModel)//�豸����ģ�ͱ��޸ĺ�,��Ҫ���¸��Զ�����
////		{
////			if (g_pTheSttTestApp->m_pTestCtrlCntr->Ats_ImportDvmFile(g_theGbSmartGenWzd->m_pDvmDevice) == STT_CMD_ExecStatus_SUCCESS)
////			{
////				if (oDeviceModelDlg_Eng.m_bHasChangedXrio)
////				{
////					//ˢ��ģ�����е�����
////					CSttGuideBook *pGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
////					CString strName = GetFileTitleFromFilePath(g_theGbSmartGenWzd->m_pDvmDevice->m_strID, '/');
////					pGuideBook->SetGuideBookName(strName);
////
////					//ˢ����Ŀ���ĸ��ڵ�������ʾ
////					CSttDevice *pDevice = pGuideBook->GetDevice();
////					g_theTestCntrFrame->ShowItems_TreeView((CExBaseList *)pDevice);
////					//emit g_theTestCntrFrame->sig_ShowItems_TreeView((CExBaseList *)pDevice);
////				}
////			}
////			else
////			{
////				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("���²���ģ���ļ�(%s)ʧ��."), pXDeviceModel->m_pDvmDevice_Global->m_strID.GetString());
////			}
////
////			CSttMacroParaEditInterface *pSttMacroParaEditInterface = g_theTestCntrFrame->GetCurrMacroParaEditInterface();
////
////			if ((pSttMacroParaEditInterface != NULL) && (!pSttMacroParaEditInterface->IsHtmlView()))//zhouhj 2024.11.28 
////			{
////				CSttMacroParaEditViewOriginal* pOriginal = (CSttMacroParaEditViewOriginal*)pSttMacroParaEditInterface;
////				pOriginal->UpdateSettingAttachUI();
////			}
////		}
////
////		//20240820 huangliang ȷ��֮�󴫳����ʽ���������溯��
////		((QSettingGlobal*)parent)->SettingSelect(oDeviceModelDlg_Eng.m_sEpExpressionFormat);
////	}
////
////#ifdef _USE_SoftKeyBoard_
////	QSoftKeyBoard::ReAttachObj();
////#endif
//}
//
//20240802 huangliang ���ö�ֵ��صĸ���
void Stt_Global_SettingParent(QWidget *parent)
{
	if (parent == NULL)	//20241018 huangliang �Ƿ�ģ̬�Ի���
	{
		if (g_pQSettingGlobal_Object)//2024-10-29 wuxinyi �޸��ж�
		{
			g_pQSettingGlobal_Object->SetParent(NULL);
		}
		return;
	}	

	if (parent->inherits(STT_SETTING_ORIGINAL_ClassID/*"CSttMacroParaEditViewOriginal"*/))
	{
		//���ü�¼Maps��ϵ�ĵ�ַ
		g_pCurrTestMacroUI_DataMaps = &(((CSttMacroParaEditViewOriginal*)parent)->m_oDvmDataMaps);
	}

	//���ø����ڵ�ַ��ȫ��ȡ��ʱ�����˸����������пؼ�
	if (g_pQSettingGlobal_Object == NULL)
	{
		g_pQSettingGlobal_Object = new QSettingGlobal();
	}
	g_pQSettingGlobal_Object->SetParent(parent);

	//��������ģ���ַ�����㶨ֵ�����в�ѯ����
	//g_pDvmDevice_AttachSetting = g_theGbSmartGenWzd->m_pDvmDevice;
}

void Stt_Global_SettingParent(QWidget *parent, QWidget *pDlgParent)
{
	Stt_Global_SettingParent(parent);

	if (pDlgParent != NULL)
	{
		if (pDlgParent->inherits(STT_SETTING_ORIGINAL_ClassID/*"CSttMacroParaEditViewOriginal"*/))
		{
			//���ü�¼Maps��ϵ�ĵ�ַ
			g_pCurrTestMacroUI_DataMaps = &(((CSttMacroParaEditViewOriginal*)pDlgParent)->m_oDvmDataMaps);
		}
	}
}


void Stt_Global_NoticeUpdateBinBinary()	//20240912 huangliang ����֪ͨ������ˢ����Ϣ,ֻȥ��ֵ�ļ��㣬�����������
{
	if (!g_HL_bFristShow)	//20241106 huangliang ��ӳ�����ȷ����ʹ���¶�λ����ʾ���
		g_HL_bFristShow = true;

	if (g_theTestCntrFrame == NULL)
		return;

	//20241011 huangliang ��ȥ���¶Ի���͵ײ���ť
	////���·�ģ̬�Ի���ģ̬�Ի����ô���
	//g_theTestCntrFrame->UpdateStatusWight_BinBinaryBtns();
	//
	////���µײ���ť
	//g_theTestCntrFrame->UpdateStatusBar_BinBinaryBtns();	

	//����ͼ��
	Stt_Global_GetBinBoutMaxWidth();
	//if (g_pStateMonitorWidget != NULL)
	//	g_pStateMonitorWidget->UpdateAxisScale();

	////��Ϣͼ	20241113 huangliang �Ƶ�ͳһ�ĸ��½ӿڴ�����ȥ
	//g_theTestCntrFrame->UpdateStatusTable_BinBinaryBtns();	//���޸�

	//���棿������»���֪��
}


QString Stt_Global_GetBinBoutNameForIndex(int iBin, int nIndex)	//20240919 huangliang ȡ�����뿪��������
{
	//return g_oSttTestResourceMngr.m_oChMaps.GetBinBoutNameForIndex(iBin, nIndex);	//20241011 huangliang �˴���ΪĬ��ֵ
	CString szBinoutDesc = "";
	switch (iBin)
	{
	case MAPS_BINARY_TYPE_BIN:
		szBinoutDesc.Format("%c", (char)(65 + nIndex));
		break;
	case MAPS_BINARY_TYPE_EXBIN:
		szBinoutDesc.Format("%s%d", MAPS_BINARY_ID_BINEX, nIndex + 1);
		break;
	case MAPS_BINARY_TYPE_BOUT:
		szBinoutDesc.Format("%d", nIndex + 1);
		break;
	case MAPS_BINARY_TYPE_EXBOUT:
		szBinoutDesc.Format("%s%d", MAPS_BINARY_ID_BOUTEX, nIndex + 1);
		break;
	}
	return  szBinoutDesc;
}
QString Stt_Global_GetBinBoutNameForIndex_NoUseDefault(int iBin, int nIndex)	//20241011 huangliang ��ȡӳ���Ŀ��뿪������
{
	return g_oSttTestResourceMngr.m_oChMaps.GetBinBoutNameForIndex(iBin, nIndex);
}
void Stt_Global_GetBinBoutMaxWidth()	//20241012 huangliang ��ȡ���뿪��ӳ���������
{
	QString strWord = "";
	int iWordWidth = 0;
	g_nNewPlotWidth = 0;
	for (int nIndex = 0; nIndex<g_nBinCount; nIndex++)		//����
	{
		strWord = Stt_Global_GetBinBoutNameForIndex_NoUseDefault(MAPS_BINARY_TYPE_BIN, nIndex);
		iWordWidth = strWord.toLocal8Bit().length();
		if (iWordWidth > g_nNewPlotWidth)	
			g_nNewPlotWidth = iWordWidth;
	}
	for (int nIndex = 0; nIndex<g_nBoutCount; nIndex++)	//����
	{
		strWord = Stt_Global_GetBinBoutNameForIndex_NoUseDefault(MAPS_BINARY_TYPE_BOUT, nIndex);
		iWordWidth = strWord.toLocal8Bit().length();
		if (iWordWidth > g_nNewPlotWidth)	
			g_nNewPlotWidth = iWordWidth;
	}

	//	if (g_nNewPlotWidth < g_nUITableWidth)	//��U/Iͼ���п�ȱȽ�
	//		g_nNewPlotWidth = g_nUITableWidth;

	////����ͼ�� 20241113 huangliang �Ƶ�ͳһ�ĸ��½ӿڴ�����ȥ
	//if (g_pStateMonitorWidget != NULL)
	//	g_pStateMonitorWidget->UpdateAxisScale();
}

int Stt_Global_GetdesktopWidgetSizeLevel()	//20241107 huangliang ��ȡ�ֱ��ʵȼ�
{
	int iLevel = 1;
#ifdef _PSX_QT_WINDOWS_	
	//2024-8-1 wuxinyi ��2880*1800�ֱ�����ʾ��ȫ
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	float fWidth = rect.width() * /*GetUIShowCoef()*/g_dUIShowCoef;	

	if (fWidth >= 2880)
	{
		iLevel = 3;
	}
	else if (fWidth >= 2240)	//20241111 huangliang 2280�޸�Ϊ2240
	{
		iLevel = 2;
	}
#endif // _PSX_QT_WINDOWS_

	return iLevel;
}
