#include "SttMacroParaEditViewGooseAbnormal.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/State/CommonValueDialogState.h"
#include "../../../UI/State/Gradient/GradientSetDlg.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../../SttGlobalDef.h"

#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewGooseAbnormal* g_pGooseTest = NULL;

QSttMacroParaEditViewGooseAbnormal::QSttMacroParaEditViewGooseAbnormal(bool bHorizontal,QWidget *parent, Qt::WFlags flags)
:QSttMacroParaEditViewState(bHorizontal,parent,flags)
{
	g_pGooseTest = this;
	/*m_bHorizontal = bHorizontal;
	if (m_bHorizontal)
	{
		m_pMainLayout = new QHBoxLayout;
	}
	else
	{
		m_pMainLayout = new QVBoxLayout;
	}*/

	m_pParaTab = NULL;
	m_pCommonPara = NULL;
	m_pShortCalc = NULL;
	//m_pGradientSet = NULL;
	//m_pFreLabel = NULL;
	//m_pFreEdit = NULL;
	m_pDC = NULL; 
	m_pStatePara = NULL;
	m_pCopyStatePara = NULL;
	m_pCopyGoutDatas = NULL;
	m_pGooseAbnParaWidget = NULL;
	m_nCurStateIndex = 0;
    m_pTrigerWidget = NULL;
	m_bTmtParaChanged = FALSE;

	//m_strParaFileTitle = tr("״̬����ģ���ļ�");
	//m_strParaFilePostfix = tr("project(*.sttxml)");
	//m_strDefaultParaFile = _P_GetConfigPath();
	//m_strDefaultParaFile.append("StateTest.sttxml");

	//initUI();
	//initConnections();

	//m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	//CreateTestResource();
	//g_theTestCntrFrame->InitTestResource();
	//g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);

	//initTestParas();
}

QSttMacroParaEditViewGooseAbnormal::~QSttMacroParaEditViewGooseAbnormal()
{
}

void QSttMacroParaEditViewGooseAbnormal::initUI_Paras(bool bHorizontal, bool bAbnormal)
{
	m_bHorizontal = bHorizontal;
	if (m_bHorizontal)
	{
		m_pMainLayout = new QHBoxLayout;
	}
	else
	{
		m_pMainLayout = new QVBoxLayout;
	}

	//m_strParaFileTitle = tr("Goose�쳣ģ��ģ���ļ�");
	m_strParaFileTitle = g_sLangTxt_State_Gooseexfile;  // Goose�쳣ģ��ģ���ļ� lcq 3.14
	m_strParaFilePostfix = tr("project(*.gatxml)");
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("GooseAbnormalTest.gatxml");

	initUI();
	//initConnections();
	initConnection_Base();

	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	//	CreateTestResource();
	g_theTestCntrFrame->InitTestResource();
	g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);

	initTestParas();
	SetMacroParaEditViewGooseAbnormalFont();
}

void QSttMacroParaEditViewGooseAbnormal::SetMacroParaEditViewGooseAbnormalFont()
{
	//m_pFreLabel->setFont(*g_pSttGlobalFont);
	//m_pFreEdit->setFont(*g_pSttGlobalFont);
	m_pDC->setFont(*g_pSttGlobalFont);
	m_pCommonPara->setFont(*g_pSttGlobalFont);
	m_pShortCalc->setFont(*g_pSttGlobalFont);
	m_pDiffCurrCalcBtn->setFont(*g_pSttGlobalFont);
	m_pEstimate->setFont(*g_pSttGlobalFont);
	m_pBinarySet->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewGooseAbnormal::UpdateEventMsg( CEventResult *pCurrEventResult )
{
	if (pCurrEventResult == NULL)
	{
		return;
	}

	if (pCurrEventResult->m_fActTime > 0.00001)
	{
		CString strResultMsg;
		strResultMsg.Format(g_sLangTxt_Native_StatusLDActTime.GetString()/*_T("״̬%ld����ʱ��%.4lfs.")*/,
			pCurrEventResult->m_nCurrStateIndex + 1, pCurrEventResult->m_fActTime);
		CLogPrint::LogString(XLOGLEVEL_RESULT, strResultMsg);
	}
}

void QSttMacroParaEditViewGooseAbnormal::initUI()
{
	//����������
	//QFont font;
	m_pParaTab = new QStateParaTab(&m_bTmtParaChanged,this);

	//CString strText;
	//strText = _T("GOOSE���Ĳ���");
	m_pGooseAbnParaWidget = new QGooseAbnormalParaSet;
	m_pParaTab->m_tabWidget->insertTab(0,m_pGooseAbnParaWidget,g_sLangTxt_State_GOOSEmessageparameters);
	m_pParaTab->m_tabWidget->setCurrentIndex(0);
	m_pParaTab->m_pGooseAbnParaWidget = m_pGooseAbnParaWidget;

	m_pBtnWidget = new QStateButtonWidget(!m_bHorizontal,this);
    m_pTrigerWidget = new QStateTrigerWidget(&m_bTmtParaChanged,this);
	initUI_TabBase();

	initUI_LayoutBase(false);
}

void QSttMacroParaEditViewGooseAbnormal::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
															long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	SerializeTestParas_Base(pMacroParas,pParas,nVolRsNum,nCurRsNum,nBinExNum,nBoutExNum,bHasGoosePub,false,true);
//	tmt_state_test *pTmtStateTest = (tmt_state_test *)pParas;
//
//	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
//	{
//		stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,FALSE,g_oLocalSysPara.m_nMaxHarmCount,false, true);
//	}
//	else
//	{
//		stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,TRUE,g_oLocalSysPara.m_nMaxHarmCount,false, true);
//	}
//
////	CSttXmlSerializeBase *pXmlParas = stt_xml_serialize((tmt_state_test*)pParas, pMacroParas,nVolRsNum,nCurRsNum,g_oLocalSysPara.m_nMaxHarmCount, false, true);
//	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;
//	CSttXmlSerializeBase *pXmlChild = NULL;
//	CString strTmp;
//
//	if (stt_xml_serialize_is_read(pMacroParas))
//	{
//		InitGoosePubDataGroups();	//��SttIecGooseCfg.ixml�ļ���ȡ��ʼֵ��ÿ��״̬��Ӧһ��CDataGroup,��Ҫ��¡Gouts���ƿ�,�ٴ�ģ��,��ģ���е�����ֵ��ֵ�����ƿ���
//	}
//
//	for (int nIndex=0;nIndex<m_oStateTest->m_oStateParas.m_nStateNumbers;nIndex++)
//	{
//		pIecCfgGoutDatas = GetGoutDatas(nIndex);
//
//		if ((pIecCfgGoutDatas != NULL)&&(bHasGoosePub))
//		{
//			strTmp.Format(_T("state%ld"),nIndex);
//			pXmlChild = (CSttXmlSerializeBase*)pMacroParas->FindByID(strTmp);
//			SerializeGoosePubs(pXmlChild,pIecCfgGoutDatas);
//		}
//	}
}

CString QSttMacroParaEditViewGooseAbnormal::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_GOOSEABNORMALTEST;
	strFile += _T(".");
	strFile += POSTFIX_GOOSEABNORMALTEST;

	return strFile;
}

void QSttMacroParaEditViewGooseAbnormal::UpdateStateParas()
{
	UpdateStateParas_Base();

	if (/*m_pParaTab->*/m_pGooseAbnParaWidget != NULL)
	{
		/*m_pParaTab->*/m_pGooseAbnParaWidget->setData(m_pStatePara,&m_oStateTest->m_oStateParas);
		m_pGooseAbnParaWidget->UpdateStateTimeUI();
	}

     if (m_pTrigerWidget != NULL)
     {
 		m_pTrigerWidget->SetData(m_pStatePara);
     }
    
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateVectorObject();
}

void QSttMacroParaEditViewGooseAbnormal::UpdateGoutTab(BOOL bUpdateList)
{
	if (bUpdateList)
	{
		InitGoosePubDataGroups();
		InitGooseAbnormalTmt();
		m_pGooseAbnParaWidget->setData(m_pStatePara,&m_oStateTest->m_oStateParas); 
		
		m_pTrigerWidget->SetData(m_pStatePara);
	}
   
	CIecCfgGoutDatas *pGoutDatas = GetGoutDatas(m_nCurStateIndex);

	if (pGoutDatas)
	{
		UpdateGoutTab_UI(pGoutDatas);

		if (m_pParaTab->m_pGooseParaWidget != NULL)
		{
			m_pParaTab->m_pGooseParaWidget->SetTestCheckBox_Visible(FALSE);
		}
	}
}

void QSttMacroParaEditViewGooseAbnormal::UpdateFT3Tab(BOOL bUpdateList)
{
	if (bUpdateList)
	{
		InitFT3PubDataGroups();
		InitGooseAbnormalTmt();
		m_pGooseAbnParaWidget->setData(m_pStatePara,&m_oStateTest->m_oStateParas); 

		m_pTrigerWidget->SetData(m_pStatePara);
	}

	CIecCfgDatasSMV *pDatasSMV=GetFT3Datas(m_nCurStateIndex);
	
	if (pDatasSMV)
	{
		UpdateFT3Tab_UI(pDatasSMV);
	}
}

void QSttMacroParaEditViewGooseAbnormal::InitGooseAbnormalTmt()//��IEC��GOOSE���������ݳ�ʼ��״̬����tmt�ṹ��������
{
	//m_listGoosePub.clear();//1������״̬���У�ÿ��״̬�е�GOOSE�쳣ģ��ṹ�壻2�����ݵ�ǰGroupIndex����IEC��ָ��ѡ��Ŀ��ƿ鸳ֵ��
	tmt_StatePara* pStatePara = NULL;

	for(int i=0;i<m_oStateTest->m_oStateParas.m_nStateNumbers;i++)
	{
		pStatePara = &m_oStateTest->m_oStateParas.m_paraState[i];
		
		CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();

		CIecCfgGooseDataBase *pIecCfgGooseData = NULL;	
		POS pos = pSourceGoutDatas->GetHeadPosition();
		long nSelGroupIndex = 0;

		while (pos)
		{
			pIecCfgGooseData = (CIecCfgGooseDataBase *)pSourceGoutDatas->GetNext(pos);	

			if (pIecCfgGooseData->m_nUseFlag == 0)
			{
				continue;
			}

			if (nSelGroupIndex == pStatePara->m_oAbnormalGOOSE.m_nGroupIndex)
			{
				Global_SetGooseAbnormalData(pIecCfgGooseData,pStatePara);
				break;
			}

			nSelGroupIndex++;
		}
	}

	/*CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;
	for (int i=0;i<m_oStateTest->m_oStateParas.m_nStateNumbers;i++)
	{
		pIecCfgGoutDatas = (CIecCfgGoutDatas*)pSourceGoutDatas->Clone();
		m_listGoosePub.append(pIecCfgGoutDatas);
	}*/
}

void QSttMacroParaEditViewGooseAbnormal::OnViewTestStart()
{
	QSttMacroParaEditViewState::OnViewTestStart();
	g_pGooseTest->m_pGooseAbnParaWidget->setDisabled(true);

	//�л���״̬1
//	m_pBtnWidget->m_pStatesComBox->setCurrentIndex(0);
//
//	m_pFreEdit->setDisabled(true);
//	m_pDC->setDisabled(true);
//	m_pCommonPara->setDisabled(true);
//	m_pShortCalc->setDisabled(true);
//	m_pGooseAbnParaWidget->setDisabled(true);
//	//m_pGradientSet->setDisabled(true);
//
//	m_pBtnWidget->startInit();
//// 	m_pBtnWidget->m_pInsertStateAF->setDisabled(true);
//// 	m_pBtnWidget->m_pInsertStateBF->setDisabled(true);
//// 	m_pBtnWidget->m_pPasteStateAF->setDisabled(true);
//// 	m_pBtnWidget->m_pPasteStateBF->setDisabled(true);
//// 	m_pBtnWidget->m_pCopyState->setDisabled(true);
//// 	m_pBtnWidget->m_pDeleteState->setDisabled(true);
//// 	m_pBtnWidget->m_pStatesComBox->setDisabled(true);
//
//	InitManuTrigerButton();
//
//	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
//	g_theTestCntrFrame->ClearInfoWidget();
//
//	m_pParaTab->startInit();
//	if(m_pParaTab->m_pGooseParaWidget)
//	{
//		m_pParaTab->m_pGooseParaWidget->setDisabled(true);
//	}
//	g_theTestCntrFrame->StartStateMonitor();
//	g_theTestCntrFrame->StartVectorWidget();

}

void QSttMacroParaEditViewGooseAbnormal::OnViewTestStop()
{
	QSttMacroParaEditViewState::OnViewTestStop();

	m_pGooseAbnParaWidget->setDisabled(false);
//	m_pFreEdit->setDisabled(false);
//	m_pDC->setDisabled(false);
//	m_pCommonPara->setDisabled(false);
//	m_pShortCalc->setDisabled(false);
//	m_pGooseAbnParaWidget->setDisabled(false);
//
//	//m_pGradientSet->setDisabled(false);
//
//	m_pBtnWidget->stopInit(m_pCopyStatePara != NULL);
//// 	m_pBtnWidget->m_pInsertStateAF->setDisabled(false);
//// 	m_pBtnWidget->m_pInsertStateBF->setDisabled(false);
//// 	m_pBtnWidget->m_pPasteStateAF->setDisabled(false);
//// 	m_pBtnWidget->m_pPasteStateBF->setDisabled(false);
//// 	m_pBtnWidget->m_pCopyState->setDisabled(false);
//// 	m_pBtnWidget->m_pDeleteState->setDisabled(false);
//// 	m_pBtnWidget->m_pStatesComBox->setDisabled(false);
//
//	m_pParaTab->stopInit();
//	if(m_pParaTab->m_pGooseParaWidget)
//	{
//		m_pParaTab->m_pGooseParaWidget->setDisabled(false);
//	}
//	g_theTestCntrFrame->StopStateMonitor();
//	g_theTestCntrFrame->StopVectorWidget();
}

BOOL Global_SetGooseAbnormalData(CIecCfgGooseDataBase *pIecCfgGooseData,tmt_StatePara *pStatePara)
{
	return Global_SetGooseAbnormalData(pIecCfgGooseData,&pStatePara->m_oAbnormalGOOSE);
}

BOOL Global_SetGooseAbnormalData(long nGroupIndex,tmt_StateParas *pStateParas)
{
	CIecCfgGooseDataBase *pIecCfgGooseData = Gloabal_GetGooseAbnDataByIndex(nGroupIndex);

	if(pIecCfgGooseData == NULL)
	{
		return FALSE;
	}

	for (int nIndex = 0;nIndex<pStateParas->m_nStateNumbers;nIndex++)
	{
		pStateParas->m_paraState[nIndex].m_oAbnormalGOOSE.m_nGroupIndex = nGroupIndex;
		Global_SetGooseAbnormalData(pIecCfgGooseData,&pStateParas->m_paraState[nIndex].m_oAbnormalGOOSE);
	}

	return TRUE;
}

BOOL Global_SetGooseAbnormalData(CIecCfgGooseDataBase *pIecCfgGooseData,tmt_StateAbnormalGOOSE *pAbnormalGoose)
{
	if(pIecCfgGooseData == NULL)
	{
		return FALSE;
	}

	CString_to_char(pIecCfgGooseData->m_strSrcAddress,pAbnormalGoose->m_strSrcMac);
	CString_to_char(pIecCfgGooseData->m_strDestAddress,pAbnormalGoose->m_strDestMac);
	CString_to_char(pIecCfgGooseData->m_strgocbRef,pAbnormalGoose->m_strGocbRef);
	CString_to_char(pIecCfgGooseData->m_strGooseId,pAbnormalGoose->m_strGoID);
	CString_to_char(pIecCfgGooseData->m_strDataSet,pAbnormalGoose->m_strDataSet);
	pAbnormalGoose->m_nAppID = pIecCfgGooseData->m_dwAppID;
	pAbnormalGoose->m_nConfRecv = pIecCfgGooseData->m_dwVersion;
	pAbnormalGoose->m_nTestFlag = pIecCfgGooseData->m_bTest;
	pAbnormalGoose->m_nNdsCom = pIecCfgGooseData->m_bNdsCom;
	pAbnormalGoose->m_nVlanID = pIecCfgGooseData->m_dwVLandID;
	pAbnormalGoose->m_nVLanPriority = pIecCfgGooseData->m_dwVLandPriority;

	//pAbnormalGoose->m_nTimequality = CString_To_long(pIecCfgGooseData->m_strTQuality);//ת����������

	bool ok;
	pAbnormalGoose->m_nTimequality = pIecCfgGooseData->m_strTQuality.toInt(&ok,16); //cl20230905Ĭ����IECʱ��Ʒ��һ��

	return TRUE;
}

void Global_SetGooseAbnormalTmtValues_ByIecConfig(tmt_StateAbnormalGOOSE *pAbnormalGoose,BOOL bJudgeMacEmpty)
{
	if (pAbnormalGoose == NULL)
	{
		return;
	}

	if (bJudgeMacEmpty &&(strlen(pAbnormalGoose->m_strDestMac) >= 12))
	{
		return;
	}

	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGooseDataBase *pIecCfgGooseData = NULL;	
	POS pos = pSourceGoutDatas->GetHeadPosition();
	long nSelGroupIndex = 0;
	while (pos)
	{
		pIecCfgGooseData = (CIecCfgGooseDataBase *)pSourceGoutDatas->GetNext(pos);	
		if (pIecCfgGooseData->m_nUseFlag == 0)
		{
			continue;
		}
		if (nSelGroupIndex == pAbnormalGoose->m_nGroupIndex)
		{
			Global_SetGooseAbnormalData(pIecCfgGooseData,pAbnormalGoose);
			break;
		}
		nSelGroupIndex++;
	}
}

CIecCfgGooseDataBase* Gloabal_GetGooseAbnDataByIndex(int nGroupIndex)
{
	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGooseDataBase *pIecCfgGooseData = NULL;	
	POS pos = pSourceGoutDatas->GetHeadPosition();
	long nCurrIndex = 0;

	while(pos)
	{
		pIecCfgGooseData = (CIecCfgGooseDataBase *)pSourceGoutDatas->GetNext(pos);

		if (pIecCfgGooseData->m_nUseFlag == 0)
		{
			continue;
		}

		if (nCurrIndex == nGroupIndex)
		{
			return pIecCfgGooseData;
		}

		nCurrIndex++;
	}

	return NULL;
}
