#include "SttMacroParaEditViewManualBase.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include"../Module/XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewManualBase::QSttMacroParaEditViewManualBase(QWidget *parent) :
   CSttMacroParaEditViewOriginal(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);

#ifdef _PSX_QT_WINDOWS_
	setMaximumSize(QSize(5000, 5000));
#endif
	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;
	m_pManualParas = NULL;

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();

	SetDatas(NULL);
	debug_time_long_log("MacroParaEditViewManual SetDatas", true);

}


QSttMacroParaEditViewManualBase::~QSttMacroParaEditViewManualBase()
{

}

void QSttMacroParaEditViewManualBase::SendUpdateParameter()
{
	g_theTestCntrFrame->Ats_UpdateParameter();
}

void QSttMacroParaEditViewManualBase::CopyBinaryConfig(BOOL b)
{
	if(m_pManualParas == NULL)
	{
		return;
	}
	if(b)
	{
		g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic = m_pManualParas->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect = m_pManualParas->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState = m_pManualParas->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect = m_pManualParas->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOutEx[i].nState = m_pManualParas->m_binOutEx[i].nState;
		}
	}
	else
	{
		m_pManualParas->m_nBinLogic = g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			m_pManualParas->m_binIn[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			m_pManualParas->m_binOut[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualParas->m_binInEx[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualParas->m_binOutEx[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOutEx[i].nState;
		}
	}
}

void QSttMacroParaEditViewManualBase::InitConnect()
{
	connect(&m_oParas, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas())); 
}

void QSttMacroParaEditViewManualBase::slot_currentChangedTabWidget(int nCurrIndex)
{

}
void QSttMacroParaEditViewManualBase::on_m_editIintVal_editingFinished()
{
	m_oParas.slot_lne_startChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewManualBase::on_m_editFinishVal_editingFinished()
{
	m_oParas.slot_lne_endChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewManualBase::on_m_editTime_editingFinished()
{
	m_oParas.slot_lne_steptimeChanged();
	SetParaChanged();
}


void QSttMacroParaEditViewManualBase::on_m_editStep_editingFinished()
{
	m_oParas.slot_lne_stepChanged();
	SetParaChanged();
}



CSttTestResourceBase* QSttMacroParaEditViewManualBase::CreateTestResource()
{
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewManualBase::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!g_theTestCntrFrame->IsTestStarted())
	{
		m_pManualParas->m_bBinStop = FALSE;
	}

	tmt_manual_test *pTmtManualTest = (tmt_manual_test *)pParas;

	/*CSttXmlSerializeBase *pXmlParas = */stt_xml_serialize(&pTmtManualTest->m_oManuParas, pMacroParas,nVolRsNum,nCurRsNum);

	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = NULL;
		pGoutDatas = m_listGoosePub.at(0);

		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);
	}

	if (bHasGoosePub)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
		ASSERT(pIecCfgDatasSMV);
		SerializeFT3Pubs(pMacroParas,pIecCfgDatasSMV);
	}
}

void QSttMacroParaEditViewManualBase::OnTestResults(CDataGroup *pResults)
{

}

void QSttMacroParaEditViewManualBase::InitBinaryInBinaryOutUI()
{
	//开入量设置
	/*Global_CheckBinSelect(m_pManualParas->m_binIn,g_nBinCount);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInA,m_pManualParas->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInB,m_pManualParas->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInC,m_pManualParas->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInD,m_pManualParas->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInE,m_pManualParas->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInF,m_pManualParas->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInG,m_pManualParas->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInH,m_pManualParas->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInI,m_pManualParas->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInJ,m_pManualParas->m_binIn,9);*/

	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut1,m_pManualParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut2,m_pManualParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut3,m_pManualParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut4,m_pManualParas->m_binOut,3);
	/*GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut5,m_pManualParas->m_binOut,4);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut6,m_pManualParas->m_binOut,5);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut7,m_pManualParas->m_binOut,6);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut8,m_pManualParas->m_binOut,7);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut9,m_pManualParas->m_binOut,8);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut10,m_pManualParas->m_binOut,9);*/
}

void QSttMacroParaEditViewManualBase::SetManualOtherParasFont()
{

}

void QSttMacroParaEditViewManualBase::InitOtherParasUI()
{
	SetManualOtherParasFont();
}

void QSttMacroParaEditViewManualBase::UpdateTestResource(BOOL bCreateChMaps)
{

}

void QSttMacroParaEditViewManualBase::slot_BinBoutStateChanged()
{
	if(g_theTestCntrFrame->IsTestStarted())
	{
		g_theTestCntrFrame->UpdateToolButtons();
	}
}

void QSttMacroParaEditViewManualBase::UpdateManualParas(bool bUpdateParasData)
{

}

void QSttMacroParaEditViewManualBase::ClearResult(PTMT_PARAS_HEAD pHead)
{

}

void QSttMacroParaEditViewManualBase::InitStyle()
{


}

void QSttMacroParaEditViewManualBase::InitIVView()
{  
	setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewManualBase::slot_SwitchStateChanged()
{
	//UpdateToolButtons();将开出量传给框架
	m_oParas.UpdateData();//更新开出量状态

	if (g_theTestCntrFrame->IsTestStarted() && !m_pManualParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewManualBase::InitBinStateOnStarting()
{
	/*初始化开出
	for (int i=0;i<g_oLocalSysPara.m_nCHBinOutNum;i++)
		m_oCurrEventResult.m_BinOut[i] = m_pManualParas->m_binOut[i].nState;

	for (int i=0;i<g_nBoutExCount;i++)
		m_oCurrEventResult.m_BinOutEx[i] = m_pManualParas->m_binOutEx[i].nState;

	UpdateToolButtons();
	*/
}


void QSttMacroParaEditViewManualBase::OnViewTestLink(BOOL b)
{

}

bool QSttMacroParaEditViewManualBase::PrepStartTest()
{
	m_bSystemParasChanged = FALSE;
	return true;
}

void QSttMacroParaEditViewManualBase::OnViewTestStart()
{
	InitBinStateOnStarting();
	BOOL bEnableState = TRUE;

	m_oIV.m_pUIParaWidget->startInit(bEnableState);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	g_theTestCntrFrame->ClearInfoWidget();
	m_oParas.StartInit();
	//m_oParas.UpdateResult(0,0,0,0);

// 	m_pManualTest_UI->m_checkBoxHarm->setEnabled(false);
// 	m_pManualTest_UI->m_comboBoxHarm->setEnabled(m_pManualParas->m_nSelHarm);
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();

	g_theTestCntrFrame->EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewManualBase::OnViewTestStop()
{
	m_oIV.m_pUIParaWidget->startInit();
// 	m_pManualTest_UI->m_checkBoxHarm->setEnabled(true);
// 	m_pManualTest_UI->m_comboBoxHarm->setEnabled(true);
	m_oParas.StopInit();

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);//20220628 zhouhj 暂时改为不更新界面参数,防止界面参数被修改为0
	g_theTestCntrFrame->StopPowerWidget();
	m_oIV.m_pUIParaWidget->UpdateTables();

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->startInit();
		m_oIV.m_pHarmUIParaWidget->UpdateTables();
	}

}

void QSttMacroParaEditViewManualBase::slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_bIsChanging = TRUE;

	//20240919 suyang 幅值  电压时，步长需要进行转换 一次值
	if (!IsUseSecondParaSet() &&  (valueFlag == amplitude_type))
	{
		if (str.contains("U"))
		{
			fstep = fstep/1000;
		}
	}
	
	m_oIV.m_pUIParaWidget->setChannelTableItemValue(str, fstep, valueFlag, AddOrMinus, bDC);
	m_bIsChanging = FALSE;
}

void QSttMacroParaEditViewManualBase::slot_updateParas()
{
	if (g_theTestCntrFrame == NULL)
	{
		return;
	}

	if (g_theTestCntrFrame->IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}

	g_theTestCntrFrame->UpdateVectorData();
	g_theTestCntrFrame->UpdatePowerData();

	SetPlotAcDcMaxMinValue();

	SetParaChanged();
}

void QSttMacroParaEditViewManualBase::ShowReport(CDvmValues *pValues)
{
	CDvmValue* pActValueData = (CDvmValue*)pValues->FindByID("ActValue");
	CDvmValue* pActTimeData = (CDvmValue*)pValues->FindByID("TripTime");
	CDvmValue* pActReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pActReturnTimeData = (CDvmValue*)pValues->FindByID("ReturnTime");

	float fActValue = 0, fActTime = 0, fReturnValue = 0, fReturnTime = 0;

	if (pActValueData != NULL)
	{
		fActValue = GlobalSetResultValue(pActValueData,3);
		//		pActValueData->m_strValue = QString::number(fActValue,'f',3);
	}

// 	if (pActTimeData != NULL)// zhouhj 2024.1.19 不能在此处修约,后续还要用到该数据
// 	{
// 		fActTime = GlobalSetResultValue(pActTimeData,4);
// 		//		pActTimeData->m_strValue = QString::number(fActTime,'f',4);
// 	}

	if (pActReturnData != NULL)
	{
		fReturnValue = GlobalSetResultValue(pActReturnData,3);
		//		pActReturnData->m_strValue = QString::number(fReturnValue,'f',3);
	}

// 	if (pActReturnTimeData != NULL)// zhouhj 2024.1.19 不能在此处修约,后续还要用到该数据
// 	{
// 		fReturnTime = GlobalSetResultValue(pActReturnTimeData,4);
// 		//		pActReturnTimeData->m_strValue = QString::number(fReturnTime,'f',4);
// 	}


	//m_oParas.UpdateResult(fActValue, fActTime, fReturnValue, fReturnTime);
}

void QSttMacroParaEditViewManualBase::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewManualBase::SetDatas(CDataGroup *pDataset)
{
	if(m_pManualParas == NULL)
	{
		return;
	}
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pManualParas, &oRead);
		debug_time_long_log("SetDatas stt_xml_serialize", true);
	}

	g_theTestCntrFrame->InitVectorWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
	debug_time_long_log("SetDatas InitVectorWidget", true);

	g_theTestCntrFrame->InitPowerWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
	debug_time_long_log("SetDatas InitPowerWidget", true);


    g_theTestCntrFrame->InitStateMonitor();
	debug_time_long_log("SetDatas InitStateMonitor", true);

    g_theTestCntrFrame->ClearInfoWidget();
	debug_time_long_log("SetDatas ClearInfoWidget", true);

    UpdateManualParas(FALSE);
	debug_time_long_log("SetDatas UpdateManualParas", true);

}

BOOL QSttMacroParaEditViewManualBase::SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I)
{
	if ((m_pManualParas == NULL)||(pDsRcdStep6U6I == NULL))
	{
		return FALSE;
	}

	CDvmData *pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID("Freq");

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[0].Harm[1].fFreq);
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_IsZeroDriftTest);

	if (pCurrData != NULL)
	{
		if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUFirstCycleWave)
		{
			pCurrData->m_strValue = _T("1");
		} 
		else
		{
			pCurrData->m_strValue = _T("0");
		}
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_ZeroDrift_Un);

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_oMuParas.fUn);
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_ZeroDrift_In);

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_oMuParas.fIn);
	}

//  	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_DelayCompens_NoPPS);
//  
//  	if (pCurrData != NULL)
//  	{
//  		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_oMuParas.fDelayCompens_NoPPS);
//  	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID("IsSuperHarm");

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%d"),m_pManualParas->m_nSelHarm);
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID("HarmCount");

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%d"),m_pManualParas->m_nHarmIndex);
	}

	for (int nIndex = 0;nIndex<6;nIndex++)
	{
/////////////////////////////////////////////////电压幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelName[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[1].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelPh[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[1].fAngle);
		}

/////////////////////////////////////////////////电流幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelName[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[1].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelPh[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[1].fAngle);
		}

/////////////////////////////////////////////////电压谐波幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarm[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarmPh[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAngle);
		}

/////////////////////////////////////////////////电流谐波幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarm[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarmPh[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAngle);
		}
	}

	return TRUE;
}



CString QSttMacroParaEditViewManualBase::GetMacroTestResultUnit()
{
	long nChType = m_oParas.GetChanneType();
	long nUnitType = m_oParas.GetCbbSelect();

	CString strUnit;

	switch (nUnitType)
	{
	case amplitude_type:
		switch (nChType)
		{
		case 0:
			if (!IsUseSecondParaSet())
			{
				strUnit = _T("kV");

			}
			else
			{
			strUnit = _T("V");

			}
			break;
		case 1:
			strUnit = _T("A");
			break;
		default:
			break;
		}
		break;
	case phasor_type:
		strUnit = _T("°");
		break;
	case fre_type:
		strUnit = _T("Hz");
		break;
	default:
		strUnit = _T("");
		break;
	}
	return strUnit;
}

// void QSttMacroParaEditViewManualBase::slot_UpdateUdcEditEnabled()
// {
// 	m_oParas.slot_UpdateUdcEditEnabled();
// }
