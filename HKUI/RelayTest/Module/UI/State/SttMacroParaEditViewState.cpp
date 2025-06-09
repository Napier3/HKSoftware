#include "SttMacroParaEditViewState.h"
#include "../../Module/XLangResource_Native.h"
#include "../../Module/SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/UI/State/ShortCalcuDig.h"
#include "../../Module/UI/State/CommonValueDialogState.h"
#include "../../Module/UI/State/Gradient/GradientSetDlg.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../SttGlobalDef.h"
#include "../Controls/SttCheckBox.h"
#include "StateBinarySetDlg.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
#include "../SttTestCntrCmdDefine.h" 
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "StateEditDlg.h"
#include "StateEstimateDlg.h"
#include "StateSettingValueDlg.h"
#include <QDesktopWidget>
#include <QApplication>
#include "../SttTestCntrFrameBase.h"

QSttMacroParaEditViewState* g_pStateTest = NULL;

QSttMacroParaEditViewState::QSttMacroParaEditViewState(bool bHorizontal,QWidget *parent)
    :CSttMacroParaEditViewOriginal(parent)
{
	////20240705 huangliang	切换到那个模块就需要更新地址
	//g_pCurrTestMacroUI_DataMaps = &m_oDvmDataMaps;//20240802 huangliang 在基类CSttMacroParaEditViewOriginal中以使用，删除此处代码

	g_pStateTest = this;
	/*m_bHorizontal = bHorizontal;
	if (m_bHorizontal)
	{
		m_pMainLayout = new QHBoxLayout;
	}
	else
	{
		m_pMainLayout = new QVBoxLayout;
	}*/
	
	m_bHorizontal = bHorizontal;
	m_pParaTab = NULL;
	m_pCommonPara = NULL;
	m_pSettingValue = NULL;
	m_pEstimate = NULL;
        m_pBinarySet=NULL;
	m_pShortCalc = NULL;
	m_pDiffCurrCalcBtn = NULL;
	m_pGradientSet = NULL;
	//m_pFreLabel = NULL;
	//m_pFreEdit = NULL;
	m_pDC = NULL;
	m_pDCPlus = NULL;
	m_pTao = NULL;
	m_pLabelTao = NULL;
	m_pStatePara = NULL;
	m_pCopyStatePara = NULL;
	m_pCopyGoutDatas = NULL;
	m_pCopyFT3Datas = NULL;
	m_pSVParaSet = NULL;
        m_pTrigerWidget = NULL;
	m_nCurStateIndex = 0;
	m_bTmtParaChanged = FALSE;
	m_nRepeatNum_GenerateRpt = 0;

    
//	m_bAbnormal = bAbnormal;
//	if (m_bAbnormal)
//	{
//		strcpy(m_oStateTest.m_pszMacroID, STT_ORG_MACRO_SmvAbnTest);
//	}
//
//	m_strParaFileTitle = tr("状态序列模板文件");
//	m_strParaFilePostfix = tr("project(*.sttxml)");
//	m_strDefaultParaFile = _P_GetConfigPath();
//	m_strDefaultParaFile.append("StateTest.sttxml");
//
//	initUI();
//	initConnections();
//
//	m_pOriginalSttTestResource = stt_GetSttTestResource();
////	CreateTestResource();
//	stt_Frame_InitTestResource();
//	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
//
//	initTestParas();
}

QSttMacroParaEditViewState::~QSttMacroParaEditViewState()
{
	if (m_pCopyStatePara != NULL)
	{
		delete m_pCopyStatePara;
		m_pCopyStatePara = NULL;
	}

	if (m_pCopyGoutDatas != NULL)
	{
		delete m_pCopyGoutDatas;
		m_pCopyGoutDatas = NULL;
	}

	if (m_pCopyFT3Datas != NULL)
	{
		delete m_pCopyFT3Datas;
		m_pCopyFT3Datas = NULL;
	}
}

void QSttMacroParaEditViewState::ResetStateSerialize()
{
	for (int i = 0; i < m_oStateTest.m_oStateParas.m_nStateNumbers; i++)
	{
		m_oStateTest.m_oStateParas.m_paraState[i].m_bSelected = 1;
	}

	SaveTestMngrFile("");

// 	CDataGroup  oDataGroup;
// 	CSttDataGroupSerializeRegister oRegister(&oDataGroup);
// 	PTMT_PARAS_HEAD pCurrTmtPara = GetTestParas();
// 	SerializeTestParas(&oRegister, pCurrTmtPara,g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(),g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
// 		g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);
// 
// 	CString strPath;
// 	strPath = _P_GetDBPath();
// 	strPath += "atsgen/State_Paras.xml";;
// 	oDataGroup.SaveXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
}

CSttTestResourceBase* QSttMacroParaEditViewState::CreateTestResource()
{
// 	if (m_pOriginalSttTestResource == NULL)
// 	{
// 		m_pOriginalSttTestResource = new CSttTestResource_Sync();
// 	}

// 	g_theTestCntrFrame->m_pSttTestResource = m_pOriginalSttTestResource;
// 	g_oSttTestResourceMngr.m_pTestResouce = m_pOriginalSttTestResource;
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return stt_GetSttTestResource();
}

void QSttMacroParaEditViewState::initUI_Paras(bool bSmvAbnormal)
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin initUI_Paras -  >>");	}

	if (m_bHorizontal)
	{
		m_pMainLayout = new QHBoxLayout;
	}
	else
	{
		m_pMainLayout = new QVBoxLayout;
	}

	m_bSmvAbnormal = bSmvAbnormal;
	if (m_bSmvAbnormal)
	{
		strcpy(m_oStateTest.m_pszMacroID, STT_ORG_MACRO_SmvAbnTest);
	}

	//m_strParaFileTitle = tr("状态序列模板文件");
	m_strParaFileTitle = g_sLangTxt_State_StateSequencefile ; //状态序列模板文件 lcq 3.14
	m_strParaFilePostfix = tr("project(*.sttxml)");
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("StateTest.sttxml");

	initUI();
	initConnections();

	m_pOriginalSttTestResource = stt_GetSttTestResource();

	//	CreateTestResource();
	stt_Frame_InitTestResource();
	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);

	initTestParas();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end initUI_Paras -  >>");	}

}

void QSttMacroParaEditViewState::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
/*
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	CString strTmpPath = _P_GetLibraryPath();
	strTmpPath.AppendFormat(_T("StateTestParas%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
		, tm.wHour, tm.wMinute, tm.wSecond);
	pParas->SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);*/
}

//#include "../SttTestCntrThread.h"

void QSttMacroParaEditViewState::SetDatas(CDataGroup *pDataset)
{
	if (m_pParaTab == NULL)
	{
		return;
	}

	if (pDataset != NULL)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-1");	}
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(&m_oStateTest.m_oStateParas, &oRead);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-1");	}
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}

	//初始化按钮栏
	if (m_pBtnWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-2");	}
		m_pBtnWidget->m_pnCurStateIndex = &m_nCurStateIndex; //状态指针关联
		m_pBtnWidget->setData(&m_oStateTest);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-2");	}
	}

	if (m_pTrigerWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-3");	}
		m_pTrigerWidget->SetData(m_pStatePara);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-3");	}
	}

	m_pStatePara = &(m_oStateTest.m_oStateParas.m_paraState[0]);

	if (m_pParaTab->m_pUIParaWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-4  UIParaWidget");	}
		disconnect(m_pParaTab->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()));
		m_pParaTab->m_pUIParaWidget->setMacroType(MACROTYPE_State);
		m_pParaTab->m_pUIParaWidget->setPropertyOfParaSet(P_Common,stt_GetSttTestResource(),m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
		connect(m_pParaTab->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()),Qt::UniqueConnection);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-4  UIParaWidget");	}
	}

	if (m_pParaTab->m_pHarmParaWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-5   HarmParaWidget");	}
		disconnect(m_pParaTab->m_pHarmParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()));
		m_pParaTab->m_pHarmParaWidget->setPropertyOfParaSet(P_Harm,stt_GetSttTestResource(),m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pHarmParaWidget->setMaxMinAndEDVal();
		connect(m_pParaTab->m_pHarmParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()),Qt::UniqueConnection);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "end State::SetDatas-5   HarmParaWidget");	}
	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-6   InitVectorWidget");	}
	stt_Frame_InitVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-6   InitPowerWidget");	}
	stt_Frame_InitPowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "end State::SetDatas-6   InitVectorWidget");	}

#ifndef SttTestCntrThread_H
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-7  InitStateMonitor");	}
	stt_Frame_InitStateMonitor();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-7   InitStateMonitor");	}

	stt_Frame_ClearInfoWidget();	
#else
	//不能使用这种模式，因为需要new widget，在线程中 new 会崩溃
	CSttMacroParaEditInterface *pMacroParaEditInterface = (CSttMacroParaEditInterface*)this;
	g_theSttTestCntrThread->PostThreadMessage(11, (unsigned long)pMacroParaEditInterface, (unsigned long)pMacroParaEditInterface);
#endif

	UpdateStateParas();
}

//2023-2-4  lijunqing 提高程序界面初始化打开的速度，将矢量图、状态图等的初始化放到线程
void QSttMacroParaEditViewState::InitSpyToolWidget()	
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-6   InitVectorWidget");	}
	stt_Frame_InitVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-6   InitPowerWidget");	}
	stt_Frame_InitPowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-6   InitVectorWidget");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-7  InitStateMonitor");	}
	stt_Frame_InitStateMonitor();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-7   InitStateMonitor");	}

	stt_Frame_ClearInfoWidget();	
}


void QSttMacroParaEditViewState::slot_UpdateVecterViews()
{
	stt_Frame_UpdateVectorData();
	stt_Frame_UpdatePowerData();
}

void QSttMacroParaEditViewState::slot_updateParas()
{
	if (m_pParaTab->m_pUIParaWidget)
	{
		((QBasicTestParaSet*)m_pParaTab->m_pUIParaWidget)->UpdateTables();
	}

	if(m_pParaTab->m_pHarmParaWidget)
	{
		((QBasicTestParaSet*)m_pParaTab->m_pHarmParaWidget)->UpdateTables();
	}

	slot_UpdateVecterViews();
	m_bTmtParaChanged = TRUE;
}

void QSttMacroParaEditViewState::AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize)
{
	(*ppBtn) = new QPushButton(strName);
	QFont font = (*ppBtn)->font();
	font.setPixelSize(nFontSize);
	(*ppBtn)->setFont(font);
}

void QSttMacroParaEditViewState::AddCheckBox(QCheckBox** ppChk,QString strName,int nFontSize)
{
	(*ppChk) = new QSttCheckBox(strName);
	QFont font = (*ppChk)->font();
	font.setPixelSize(nFontSize);
	(*ppChk)->setFont(font);
}

void QSttMacroParaEditViewState::AddLabel(QLabel** ppLabel,QString strName,int nFontSize)
{
	(*ppLabel) = new QLabel(strName);
	QFont font = (*ppLabel)->font();
	font.setPixelSize(nFontSize);
	(*ppLabel)->setFont(font);
}

void QSttMacroParaEditViewState::AddLineEdit(QLineEdit** ppLabel, int nFontSize)
{
    (*ppLabel) = new QSettingLineEdit();//new QLineEdit();    //20240718 huangliang
	QFont font = (*ppLabel)->font();
	font.setPixelSize(nFontSize);
	(*ppLabel)->setFont(font);
}

void QSttMacroParaEditViewState::initUI_TabBase()
{
	CString strText;

	//strText = _T("频率:");
	//AddLabel(&m_pFreLabel,strText,18);
	//m_pFreEdit = new QSttLineEdit(this);
	//m_pFreEdit->setFixedWidth(80);
	//m_pFreEdit->setText("50.000");
	//strText = _T("直流");
	//xlang_SetLangStrToWidget_Txt(m_pDC,g_sLangTxt_Native_DC, XLang_Ctrls_QCheckBox);// 直流-LCQ
	AddCheckBox(&m_pDC,g_sLangTxt_Native_DC,18);
	AddCheckBox(&m_pDCPlus,g_sLangTxt_State_DCOffSet,18);
	AddLabel(&m_pLabelTao, g_sLangTxt_State_Tou, 18);
	AddLineEdit(&m_pTao, 18);
	

	//strText = _T("整定值");
	AddPushButton(&m_pSettingValue,g_sLangTxt_State_SettingValue,18);
	//strText = _T("整定及结果评估");
	AddPushButton(&m_pEstimate, g_sLangTxt_StateEstimate_ResultEstimate, 18);

	//strText = _T("开关量设置");
	//xlang_SetLangStrToWidget_Txt(m_pBinarySet, g_sLangTxt_State_SwitchSet,XLang_Ctrls_QPushButton);//开关量设置-LCQ
	AddPushButton(&m_pBinarySet,g_sLangTxt_Native_Switch,18);

	//strText = _T("通用参数");
	//xlang_SetLangStrToWidget_Txt(m_pCommonPara, g_sLangTxt_GeneralParameter, XLang_Ctrls_QPushButton);//通用参数-LCQ
	AddPushButton(&m_pCommonPara,g_sLangTxt_GeneralParameter,18);

	//strText = _T("短路计算");
	//xlang_SetLangStrToWidget_Txt(m_pShortCalc, g_sLangTxt_State_ShortCalc, XLang_Ctrls_QPushButton); //短路计算-LCQ
	AddPushButton(&m_pShortCalc,g_sLangTxt_State_ShortCalc,18);
	//strText = _T("差流计算");
	//xlang_SetLangStrToWidget_Txt(m_pDiffCurrCalcBtn,g_sLangTxt_State_Difflowcalculation,XLang_Ctrls_QPushButton);//差流计算-LCQ
	AddPushButton(&m_pDiffCurrCalcBtn,g_sLangTxt_State_Difflowcalculation,16);

	//strText = _T("递变设置");
	AddPushButton(&m_pGradientSet, g_sLangTxt_State_GradientSet, 18);
	xlang_SetLangStrToWidget(m_pGradientSet, "State_GradientSet", XLang_Ctrls_QPushButton);

	//2024-8-23 wuxy 叠加衰减直流显示不全
#ifdef _PSX_QT_WINDOWS_
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	float fWidth = rect.width() * g_dUIShowCoef;

	if (fWidth >= 2280)//1920*125%
	{
		int nWidth =85;
		m_pDCPlus->setMinimumWidth(300);
		m_pCommonPara->setFixedWidth(nWidth);
		m_pShortCalc->setFixedWidth(nWidth);
		m_pDiffCurrCalcBtn->setFixedWidth(nWidth);
		m_pBinarySet->setFixedWidth(nWidth+10);
		m_pEstimate->setFixedWidth(nWidth);
		m_pGradientSet->setFixedWidth(nWidth);
	}		
	
	int nFixHeight = 25;
	m_pDC->setMinimumHeight(nFixHeight);
	m_pLabelTao->setMinimumHeight(nFixHeight);
	m_pTao->setMinimumHeight(nFixHeight);
	m_pDCPlus->setMinimumHeight(nFixHeight);
	m_pCommonPara->setMinimumHeight(nFixHeight);
	m_pShortCalc->setMinimumHeight(nFixHeight);
	m_pDiffCurrCalcBtn->setMinimumHeight(nFixHeight);
	m_pBinarySet->setMinimumHeight(nFixHeight);
	m_pEstimate->setMinimumHeight(nFixHeight);
	m_pGradientSet->setMinimumHeight(nFixHeight);
#endif // _PSX_QT_WINDOWS_


	//strText = _T("");
	//xlang_GetLangStrByFile(strText, "Native_Freq");
	//strText += "(Hz):";
	//m_pFreLabel->setText(strText);
	//xlang_SetLangStrToWidget(m_pDC, "Native_DC", XLang_Ctrls_QCheckBox);
    //xlang_SetLangStrToWidget(m_pBinarySet,"Native_VolSet",XLang_Ctrls_QPushButton);
	//xlang_SetLangStrToWidget(m_pCommonPara, "Native_CommonPara", XLang_Ctrls_QPushButton);	
	//xlang_SetLangStrToWidget(m_pShortCalc, "State_ShortCalc", XLang_Ctrls_QPushButton);

	m_pSettingValue->hide();
	m_pTao->setEnabled(false);
	m_pLabelTao->setEnabled(false);
	if(xlang_GetCurrLanguageID() == CURRLANGUAGE_RUSSIAN)
	{
		m_pLabelTao->hide();
	}
}

void QSttMacroParaEditViewState::initUI_LayoutBase(bool bGradientSet)
{
	if (m_bHorizontal)
	{
		QVBoxLayout *pVLeft = new QVBoxLayout;
		pVLeft->addWidget(m_pParaTab);

		QHBoxLayout* pVLeftBottom = new QHBoxLayout;
		//pVLeftBottom->addWidget(m_pFreLabel);
		//pVLeftBottom->addWidget(m_pFreEdit);
		pVLeftBottom->addWidget(m_pDC);
		pVLeftBottom->addWidget(m_pDCPlus);
		pVLeftBottom->addWidget(m_pLabelTao);
		pVLeftBottom->addWidget(m_pTao);
		pVLeftBottom->addSpacerItem(new QSpacerItem(500,20,QSizePolicy::Expanding));
		pVLeftBottom->addWidget(m_pSettingValue);
		pVLeftBottom->addWidget(m_pEstimate);
        pVLeftBottom->addWidget(m_pBinarySet);
		pVLeftBottom->addWidget(m_pCommonPara);
		pVLeftBottom->addWidget(m_pShortCalc);
		pVLeftBottom->addWidget(m_pDiffCurrCalcBtn);

		if(xlang_GetCurrLanguageID() == CURRLANGUAGE_RUSSIAN)
		{
			pVLeftBottom->setSpacing(5);
		}

		if (bGradientSet)
		{
			pVLeftBottom->addWidget(m_pGradientSet);
		}

		pVLeft->addLayout(pVLeftBottom);

		QVBoxLayout *pVRight = new QVBoxLayout;
		pVRight->addWidget(m_pBtnWidget);

		m_pMainLayout->addLayout(pVRight);	 
		m_pMainLayout->addLayout(pVLeft );
	}
	else
	{
	        QVBoxLayout *pVDownTab = new QVBoxLayout;
		pVDownTab->addWidget(m_pParaTab);
		QVBoxLayout *pVDown = new QVBoxLayout;
		QHBoxLayout* pVDownBottom = new QHBoxLayout;
		//pVDownBottom->addWidget(m_pFreLabel);
		//pVDownBottom->addWidget(m_pFreEdit);
        m_pTao->setFixedWidth(55);
		pVDownBottom->addWidget(m_pDC);
		pVDownBottom->addWidget(m_pDCPlus);
		pVDownBottom->addWidget(m_pLabelTao);
		pVDownBottom->addWidget(m_pTao);
		pVDownBottom->addSpacerItem(new QSpacerItem(600,20,QSizePolicy::Expanding));
		pVDownBottom->addWidget(m_pSettingValue);

// 		pVDownBottom->addWidget(m_pEstimate);
//      pVDownBottom->addWidget(m_pBinarySet);
		pVDownBottom->addWidget(m_pCommonPara);
		pVDownBottom->addWidget(m_pShortCalc);
		pVDownBottom->addWidget(m_pDiffCurrCalcBtn);

        pVDownBottom->setSpacing(4);
		if (bGradientSet)
		{
			pVDownBottom->addWidget(m_pGradientSet);
		}
		if(xlang_GetCurrLanguageID() == CURRLANGUAGE_RUSSIAN)
		{
			pVDownBottom->setSpacing(5);
		}
		pVDownBottom->addWidget(m_pBinarySet); //2024-7-30 wuxinyi 按需求调整按钮顺序
		pVDownBottom->addWidget(m_pEstimate);


		pVDown->addLayout(pVDownBottom);
		m_pMainLayout->addWidget(m_pBtnWidget );
		m_pMainLayout->addLayout(pVDownTab);
		m_pMainLayout->addWidget(m_pTrigerWidget);
		m_pMainLayout->addLayout(pVDown);	
	}
	setLayout(m_pMainLayout);
}


void QSttMacroParaEditViewState::initUI()
{
	//创建各部件
	//QFont font;
	m_pParaTab = new QStateParaTab(&m_bTmtParaChanged,this);
	CString strText;

	if(m_bSmvAbnormal)
	{
		m_pSVParaSet = new QSmvAbnormalParaset;
		//m_pParaTab->m_tabWidget->insertTab(0,m_pSVParaSet,strText);
		m_pParaTab->m_tabWidget->insertTab(0,m_pSVParaSet,g_sLangTxt_State_SVexceptionSimulation);//SV异常模拟 lcq 3.14 
		m_pParaTab->m_pSVParaSet = m_pSVParaSet;
	}
	m_pParaTab->m_tabWidget->setCurrentIndex(0);

	m_pBtnWidget = new QStateButtonWidget(!m_bHorizontal,this);
    m_pTrigerWidget = new QStateTrigerWidget(&m_bTmtParaChanged,this);
	m_pBtnWidget->m_pnCurStateIndex = &m_nCurStateIndex; //状态指针关联


	initUI_TabBase();

	initUI_LayoutBase(true);
	SetStateFont();
	m_pBtnWidget->EnableButtons();

	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewState::SetStateFont()
{
	m_pSettingValue->setFont(*g_pSttGlobalFont);
    m_pBinarySet->setFont(*g_pSttGlobalFont);

	m_pCommonPara->setFont(*g_pSttGlobalFont);
	m_pEstimate->setFont(*g_pSttGlobalFont);
	m_pShortCalc->setFont(*g_pSttGlobalFont);
	m_pDiffCurrCalcBtn->setFont(*g_pSttGlobalFont);
	m_pGradientSet->setFont(*g_pSttGlobalFont);
	//m_pFreLabel->setFont(*g_pSttGlobalFont);
	//m_pFreEdit->setFont(*g_pSttGlobalFont);
	m_pDC->setFont(*g_pSttGlobalFont);
	m_pDCPlus->setFont(*g_pSttGlobalFont);
	m_pLabelTao->setFont(*g_pSttGlobalFont);
	m_pTao->setFont(*g_pSttGlobalFont);

}

void QSttMacroParaEditViewState::initConnection_Base()
{
	//connect(m_pBtnWidget->m_pPasteStateBF,SIGNAL(clicked()),this,SLOT(slot_PasteStateBF()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pPreviosState,SIGNAL(clicked()),this,SLOT(slot_PreviosState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pNextState,SIGNAL(clicked()),this,SLOT(slot_NextState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pInsertStateBF,SIGNAL(clicked()),this,SLOT(slot_InsertStateBF()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pInsertStateAF,SIGNAL(clicked()),this,SLOT(slot_InsertStateAF()),Qt::UniqueConnection);
	//connect(m_pBtnWidget->m_pPasteStateAF,SIGNAL(clicked()),this,SLOT(slot_PasteStateAF()),Qt::UniqueConnection);
	//connect(m_pBtnWidget->m_pCopyState,SIGNAL(clicked()),this,SLOT(slot_CopyState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pDeleteState,SIGNAL(clicked()),this,SLOT(slot_DeleteState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)),Qt::UniqueConnection);
	connect(m_pParaTab->m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
	connect(m_pBtnWidget->m_pBtnEditState, SIGNAL(clicked()), this, SLOT(slot_EditState()));

	//connect(m_pParaTab->m_pStateParaWidget,SIGNAL(sig_SwitchStateChanged()),this,SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

	//connect(m_pFreEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_FreChangedKeyBoard()));
	connect(m_pDC,SIGNAL(stateChanged (int)), this, SLOT(slot_chb_DcStateChanged(int)),Qt::UniqueConnection);
    connect(m_pBinarySet,SIGNAL(clicked()),this,SLOT(slot_BinarySet()),Qt::UniqueConnection);
	connect(m_pSettingValue,SIGNAL(clicked()),this,SLOT(slot_SettingValue()),Qt::UniqueConnection);
	connect(m_pEstimate,SIGNAL(clicked()),this,SLOT(slot_Estimate()),Qt::UniqueConnection);
	connect(m_pCommonPara,SIGNAL(clicked()),this,SLOT(slot_CommonPara()),Qt::UniqueConnection);
	connect(m_pShortCalc,SIGNAL(clicked()),this,SLOT(slot_ShortClac()),Qt::UniqueConnection);
	connect(m_pDiffCurrCalcBtn,SIGNAL(clicked()),this,SLOT(slot_DiffCurrCalcBtnClicked()),Qt::UniqueConnection);
	connect(m_pDCPlus,SIGNAL(stateChanged(int)),this,SLOT(slot_chb_DcPlusStateChanged(int)),Qt::UniqueConnection);
	connect(m_pTao,SIGNAL(editingFinished()),this,SLOT(slot_lne_TaoChanged()),Qt::UniqueConnection);

//  	connect(g_theTestCntrFrame, SIGNAL(sig_UpdateAuxDCEdit()), this, SLOT(slot_UpdateAuxDcEnabled()));

//#ifdef _PSX_QT_LINUX_
//	connect(m_pFreEdit, SIGNAL(clicked()), this, SLOT(slot_lne_FreChanged()));
//#endif
}

void  QSttMacroParaEditViewState::UpdateAuxDCEdit()
{
	if (m_pTrigerWidget == NULL)
	{
		return;
	}

	m_pTrigerWidget->UpdateAuxDcEnabled();

}

void QSttMacroParaEditViewState::initConnections()
{
	initConnection_Base();
	connect(m_pGradientSet,SIGNAL(clicked()),this,SLOT(slot_GradientSet()),Qt::UniqueConnection);

	connect(m_pTrigerWidget, SIGNAL(sig_UpdateToolButtons()), this, SLOT(slot_UpdateToolButtons()), Qt::UniqueConnection);
}

// void QSttMacroParaEditViewState::slot_UpdateAuxDcEnabled()
// {
// 	if (m_pTrigerWidget == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pTrigerWidget->UpdateAuxDcEnabled();
// 
// }

void QSttMacroParaEditViewState::InitGoosePubDataGroups()
{
	m_listGoosePub.clear();
	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;

	for (int i=0;i<m_oStateTest.m_oStateParas.m_nStateNumbers;i++)
	{
		pIecCfgGoutDatas = (CIecCfgGoutDatas*)pSourceGoutDatas->Clone();
		m_listGoosePub.append(pIecCfgGoutDatas);
	}
}

void QSttMacroParaEditViewState::InitFT3PubDataGroups()
{
	m_listFT3Pub.clear();
	CIecCfgDatasSMV *pSourceDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgDatasSMV *pIecCfgDatasSMV = NULL;

	for (int i=0;i<m_oStateTest.m_oStateParas.m_nStateNumbers;i++)
	{
		pIecCfgDatasSMV = (CIecCfgDatasSMV*)pSourceDatasSMV->Clone();
		m_listFT3Pub.append(pIecCfgDatasSMV);
	}
}
void QSttMacroParaEditViewState::UpdateTestResource(BOOL bCreateChMaps)
{
// 	ASSERT(g_theTestCntrFrame->m_pSttTestResource);
// 	g_theTestCntrFrame->OnUpdateTestResource(bCreateChMaps);

	if (m_pParaTab->m_pUIParaWidget)
	{
		m_pParaTab->m_pUIParaWidget->initUI(stt_GetSttTestResource());
		m_pParaTab->m_pUIParaWidget->initData();
		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
	}
	
	if (m_pParaTab->m_pHarmParaWidget)
	{
		m_pParaTab->m_pHarmParaWidget->initUI(stt_GetSttTestResource());
		m_pParaTab->m_pHarmParaWidget->initData();
		m_pParaTab->m_pHarmParaWidget->setMaxMinAndEDVal();
	}

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	//m_pParaTab->m_pStateParaWidget->UpdateInput();
	//m_pParaTab->m_pStateParaWidget->UpdateOutPut();

// 	if(g_nBoutCount == 8)
// 	{
// 		m_pParaTab->m_pStateParaWidget->m_pBout_9->setChecked(false);
// 		m_pParaTab->m_pStateParaWidget->m_pBout_10->setChecked(false);
// 		m_pParaTab->m_pStateParaWidget->m_pBout_9->setEnabled(false);
// 		m_pParaTab->m_pStateParaWidget->m_pBout_10->setEnabled(false);
// 	}
// 	else
// 	{
// 		m_pParaTab->m_pStateParaWidget->m_pBout_9->setChecked(m_pStatePara->m_binOut[8].nState);
// 		m_pParaTab->m_pStateParaWidget->m_pBout_10->setChecked(m_pStatePara->m_binOut[9].nState);
// 		m_pParaTab->m_pStateParaWidget->m_pBout_9->setEnabled(true);
// 		m_pParaTab->m_pStateParaWidget->m_pBout_10->setEnabled(true);
// 	}
// 
// 	if (g_nBinCount == 8)
// 	{
// 		m_pParaTab->m_pStateParaWidget->m_pBin_I->setChecked(false);
// 		m_pParaTab->m_pStateParaWidget->m_pBin_J->setChecked(false);
// 		m_pParaTab->m_pStateParaWidget->m_pBin_I->setEnabled(false);
// 		m_pParaTab->m_pStateParaWidget->m_pBin_J->setEnabled(false);
// 	}
// 	else
// 	{
// 		m_pParaTab->m_pStateParaWidget->m_pBin_I->setChecked(m_pStatePara->m_binIn[8].nSelect);
// 		m_pParaTab->m_pStateParaWidget->m_pBin_J->setChecked(m_pStatePara->m_binIn[9].nSelect);
// 		m_pParaTab->m_pStateParaWidget->m_pBin_I->setEnabled(true);
// 		m_pParaTab->m_pStateParaWidget->m_pBin_J->setEnabled(true);
// 	}
}

char* QSttMacroParaEditViewState::GetMacroID()
{
	if (m_bSmvAbnormal)
	{
		return STT_MACRO_ID_SmvAbnTest;
	} 
	else
	{
		return STT_MACRO_ID_StateTest;
	}
}

void QSttMacroParaEditViewState::SerializeTestParas_Base(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
													long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub, BOOL bSmvAbnormal,BOOL bGooseAbnormal)
{
	tmt_state_test *pTmtStateTest = (tmt_state_test *)pParas;

// 	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
// 	{
// 		stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,FALSE,g_oLocalSysPara.m_nMaxHarmCount,bSmvAbnormal, bGooseAbnormal);
// 	}
// 	else
// 	{
// 		stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,TRUE,g_oLocalSysPara.m_nMaxHarmCount,bSmvAbnormal, bGooseAbnormal);
// 	}

	stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,FALSE,g_oLocalSysPara.m_nMaxHarmCount,bSmvAbnormal, bGooseAbnormal);

	//	/*CSttXmlSerializeBase *pXmlParas = */stt_xml_serialize(&pTmtStateTest->m_oStateParas/*(tmt_state_test*)pParas*/, pMacroParas,nVolRsNum,nCurRsNum,g_oLocalSysPara.m_nMaxHarmCount,m_bSmvAbnormal,false);
	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;
	CIecCfgDatasSMV *pIecCfgDatasSMV = NULL;

	CSttXmlSerializeBase *pXmlChild = NULL;
	CString strTmp1,strTmp2;

	if (stt_xml_serialize_is_read(pMacroParas))
	{
		InitGoosePubDataGroups();	//从SttIecGooseCfg.ixml文件获取初始值，每个状态对应一个CDataGroup,需要克隆Gouts控制块,再打开模板,将模板中的数据值赋值到控制块中
		InitFT3PubDataGroups();
	}

	int nType ,nNetType;
	CString strNet1,strNet2;
	

	for (int nIndex=0;nIndex<m_oStateTest.m_oStateParas.m_nStateNumbers;nIndex++)
	{
		pIecCfgGoutDatas = GetGoutDatas(nIndex);

		if ((pIecCfgGoutDatas != NULL)&&(bHasGoosePub))
		{
			nType = 0x88b8;
			strNet1.Format("%04X",nType);
			nNetType = m_oStateTest.m_oStateParas.m_paraState[nIndex].m_oAbnormalGOOSE.m_nNetType;
			
			if( nNetType != nType)
			{
				strNet2.Format("%04X",nNetType);

				CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("当前状态%d : 网络标识(0x%s)与原网络标识(0x%s)不一致"),nIndex+1,strNet2.GetString(),strNet1.GetString());
			}
			
			strTmp1.Format(_T("state%ld"),nIndex);
			pXmlChild = (CSttXmlSerializeBase*)pMacroParas->FindByID(strTmp1);
			SerializeGoosePubs(pXmlChild,pIecCfgGoutDatas);
		}

		pIecCfgDatasSMV=GetFT3Datas(nIndex);
		if ((pIecCfgDatasSMV != NULL)&&(bHasGoosePub))
		{
			//sv 的网络标识不可编辑
// 			nType = 0x88ba;
// 			strNet1.Format("%04X",nType);
// 			nNetType = m_oStateTest.m_oStateParas.m_paraState[nIndex].m_oAbnormalSMV.m_oSmvMsg.m_nNetType;
// 
// 			if( nNetType != nType)
// 			{
// 				strNet2.Format("%04X",nNetType);
// 
// 				CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("当前状态%d的网络标识(0x%s)与原网络标识(0x%s)不一致"),nIndex+1,strNet2.GetString(),strNet1.GetString());
// 			}

			strTmp2.Format(_T("state%ld"),nIndex);
			pXmlChild = (CSttXmlSerializeBase*)pMacroParas->FindByID(strTmp2);
			SerializeFT3Pubs(pXmlChild,pIecCfgDatasSMV);
		}
	}
}

void QSttMacroParaEditViewState::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
										   long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	SerializeTestParas_Base(pMacroParas,pParas,nVolRsNum,nCurRsNum,nBinExNum,nBoutExNum,bHasGoosePub,m_bSmvAbnormal,false);
//	tmt_state_test *pTmtStateTest = (tmt_state_test *)pParas;
//
//	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
//	{
//		stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,FALSE,g_oLocalSysPara.m_nMaxHarmCount,m_bSmvAbnormal, false);
//	}
//	else
//	{
//		stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,TRUE,g_oLocalSysPara.m_nMaxHarmCount,m_bSmvAbnormal, false);
//	}
//
////	/*CSttXmlSerializeBase *pXmlParas = */stt_xml_serialize(&pTmtStateTest->m_oStateParas/*(tmt_state_test*)pParas*/, pMacroParas,nVolRsNum,nCurRsNum,g_oLocalSysPara.m_nMaxHarmCount,m_bSmvAbnormal,false);
//	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;
//	CSttXmlSerializeBase *pXmlChild = NULL;
//	CString strTmp;
//
//	if (stt_xml_serialize_is_read(pMacroParas))
//	{
//		InitGoosePubDataGroups();	//从SttIecGooseCfg.ixml文件获取初始值，每个状态对应一个CDataGroup,需要克隆Gouts控制块,再打开模板,将模板中的数据值赋值到控制块中
//	}
//
//	for (int nIndex=0;nIndex<m_oStateTest.m_oStateParas.m_nStateNumbers;nIndex++)
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

CString QSttMacroParaEditViewState::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();

	if (m_bSmvAbnormal)
	{
		strFile += STT_MACRO_ID_SmvAbnTest;
	} 
	else
	{
		strFile += STT_MACRO_ID_StateTest;
	}

	strFile += _T(".");
	strFile += POSTFIX_STATETEST;

	return strFile;
}

bool QSttMacroParaEditViewState::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_STATETEST)
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewState::initTestParas()
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin initTestParas -  >>");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenTestTestMngrFile -  >>");	}
	BOOL bRet = OpenTestTestMngrFile(_T(""));
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end OpenTestTestMngrFile -  >>");	}

	if (!bRet)
	{
		m_oStateTest.m_oStateParas.init(2);
		InitGoosePubDataGroups();
		InitFT3PubDataGroups();
	}

	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();
	SetDatas(NULL);
	setDcoffsetEnable();

	m_pBtnWidget->EnableButtons();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end initTestParas -  >>");	}
}

void QSttMacroParaEditViewState::InitUI_OpenParas()
{
	if (m_pParaTab == NULL)
	{
		return;
	}

	//初始化按钮栏
	if (m_pBtnWidget)
	{
		m_pBtnWidget->setData(&m_oStateTest);
	}
	if (m_pTrigerWidget)
	{
		m_pTrigerWidget->SetData(m_pStatePara);
	}

	m_pStatePara = &(m_oStateTest.m_oStateParas.m_paraState[0]);
	if (m_pParaTab->m_pUIParaWidget)
	{
		m_pParaTab->m_pUIParaWidget->setMacroType(MACROTYPE_State);
		m_pParaTab->m_pUIParaWidget->setPropertyOfParaSet(P_Common,stt_GetSttTestResource(),m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
	}

	if (m_pParaTab->m_pHarmParaWidget)
	{
		m_pParaTab->m_pHarmParaWidget->setPropertyOfParaSet(P_Harm,stt_GetSttTestResource(),m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pHarmParaWidget->setMaxMinAndEDVal();
		connect(m_pParaTab->m_pHarmParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()),Qt::UniqueConnection);
	}

	UpdateStateParas();
}

void QSttMacroParaEditViewState::UpdateStateParas_Base()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (m_pParaTab->m_pUIParaWidget)
	{
		m_pParaTab->m_pUIParaWidget->setData(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pUIParaWidget->initData();
	}

	if(m_pParaTab->m_pHarmParaWidget)
	{
		m_pParaTab->m_pHarmParaWidget->setData(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		((QBasicTestParaSet*)m_pParaTab->m_pHarmParaWidget)->DCStateChanged(P_Harm,m_pStatePara->m_bDC);
		m_pParaTab->m_pHarmParaWidget->initData();
	}

// 	if(m_pParaTab->m_pStateParaWidget)
// 	{
// 		m_pParaTab->m_pStateParaWidget->setData(m_pStatePara);
// 	}

	m_pDC->setChecked(m_pStatePara->m_bDC);
	if (m_pStatePara->m_bPlusDC)
	{
		m_pDCPlus->setChecked(true);
	}
	else
	{
		m_pDCPlus->setChecked(false);
	}

	//20240718 huangliang
	//m_pTao->setText(QString::number(m_pStatePara->m_fTao,'f',3));
    ((QSettingLineEdit*)m_pTao)->UpdateStructText(CVariantDataAddress(&m_pStatePara->m_fTao), 3);

	m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
	m_pParaTab->m_pUIParaWidget->DCStateChanged(P_Common,m_pStatePara->m_bDC);

	m_pParaTab->m_pHarmParaWidget->setMaxMinAndEDVal();
	m_pParaTab->m_pHarmParaWidget->DCStateChanged(P_Harm,m_pStatePara->m_bDC);

	UpdateBinBoutExTab();
	if(m_pParaTab->ExistExBinParaWidget())
	{
		m_pParaTab->m_pExBinParaWidget->setData(m_pStatePara->m_binInEx,NULL);
	}

	if(m_pParaTab->ExistExBoutParaWidget())
	{
		m_pParaTab->m_pExBoutParaWidget->setData(NULL,m_pStatePara->m_binOutEx);
	}

	if(m_bSmvAbnormal && m_pSVParaSet)
	{
		m_pSVParaSet->setData(&m_pStatePara->m_oAbnormalSMV,&m_oStateTest.m_oStateParas);
	}
}

void QSttMacroParaEditViewState::UpdateStateParas()
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateStateParas");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateStateParas_Base");	}
	UpdateStateParas_Base();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateStateParas_Base");	}

	if(m_bSmvAbnormal && m_pSVParaSet)
	{
		m_pSVParaSet->setData(&m_pStatePara->m_oAbnormalSMV,&m_oStateTest.m_oStateParas);
	}

      m_pTrigerWidget->SetData(m_pStatePara);

	  if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateGoutTab");	}
	UpdateGoutTab();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateGoutTab");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateFT3Tab");	}
	UpdateFT3Tab();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateFT3Tab");	}


	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateVectorObject");	}
	UpdateVectorObject();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateVectorObject");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateStateParas");	}
}

void QSttMacroParaEditViewState::CopyBinaryConfig(BOOL b)
{
	tmt_StatePara* pStatePara = &m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex];
	if(!pStatePara)
	{
		return;
	}

	if(b)
	{
		stt_GetBinaryConfig()->m_nBinLogic = pStatePara->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			stt_GetBinaryConfig()->m_binIn[i].nSelect = pStatePara->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			stt_GetBinaryConfig()->m_binOut[i].nState = pStatePara->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binInEx[i].nSelect = pStatePara->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binOutEx[i].nState = pStatePara->m_binOutEx[i].nState;
		}
	}
	else
	{
		pStatePara->m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			pStatePara->m_binIn[i].nSelect = stt_GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			pStatePara->m_binOut[i].nState = stt_GetBinaryConfig()->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			pStatePara->m_binInEx[i].nSelect = stt_GetBinaryConfig()->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			pStatePara->m_binOutEx[i].nState = stt_GetBinaryConfig()->m_binOutEx[i].nState;
		}
	}
}

bool QSttMacroParaEditViewState::HasHarmParaset(tmt_StatePara* pStatePara)
{
	ASSERT(pStatePara != NULL);
	tmt_channel* pChannel = NULL;

	if (pStatePara)
	{
		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
		{
			pChannel = &pStatePara->m_uiVOL[j];
			for (int nIndex=2;nIndex<MAX_HARM_COUNT;nIndex++)
			{
				if (pChannel->Harm[nIndex].m_bSelect)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void QSttMacroParaEditViewState::ClearHarmParaset(tmt_StatePara* pStatePara)
{
	ASSERT(pStatePara != NULL);

	for (int i=0;i<MAX_VOLTAGE_COUNT;i++)
	{
		for (int j=1;j<=MAX_HARM_COUNT;j++)
		{
			pStatePara->m_uiVOL[i].Harm[j].m_bSelect = false;
		}
	}

	for (int i=0;i<MAX_CURRENT_COUNT;i++)
	{
		for (int j=1;j<=MAX_HARM_COUNT;j++)
		{
			pStatePara->m_uiCUR[i].Harm[j].m_bSelect = false;
		}
	}
}

void QSttMacroParaEditViewState::UpdateBinBoutExTab()
{
	if ((m_pParaTab->m_pExBinParaWidget == NULL)&&(g_oLocalSysPara.m_nCHBinInExNum>0))
	{
		m_pParaTab->AddExBinParaWidget();
		m_pParaTab->m_pExBinParaWidget->setData(m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex].m_binInEx,NULL);
		connect(m_pParaTab->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);
	}
	else if ((m_pParaTab->m_pExBinParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinInExNum == 0))
	{
		disconnect(m_pParaTab->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pParaTab->RemoveExBinParaWidget();
	}
	else if ((m_pParaTab->m_pExBinParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinInExNum>0))
	{
		disconnect(m_pParaTab->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pParaTab->m_pExBinParaWidget->setData(m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex].m_binInEx,NULL);
		connect(m_pParaTab->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		m_pParaTab->EnableBinParaWidget(true);
	}

	if ((m_pParaTab->m_pExBoutParaWidget == NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum>0))
	{
		m_pParaTab->AddExBoutParaWidget();
		m_pParaTab->m_pExBoutParaWidget->setData(NULL,m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex].m_binOutEx);
		connect(m_pParaTab->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);
	}
	else if ((m_pParaTab->m_pExBoutParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum == 0))
	{
		disconnect(m_pParaTab->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pParaTab->RemoveExBoutParaWidget();
	}
	else if ((m_pParaTab->m_pExBoutParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum>0))
	{
		disconnect(m_pParaTab->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pParaTab->m_pExBoutParaWidget->setData(NULL,m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex].m_binOutEx);
		connect(m_pParaTab->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		m_pParaTab->EnableBoutParaWidget(true);
	}
}

void QSttMacroParaEditViewState::UpdateGoutTab(BOOL bUpdateList)
{
	if (bUpdateList)
	{
		InitGoosePubDataGroups();

		if (m_bSmvAbnormal)
		{
			InitSvAbnormalTmt();
			m_pSVParaSet->setData(&m_pStatePara->m_oAbnormalSMV,&m_oStateTest.m_oStateParas);
		}
	}

	CIecCfgGoutDatas *pGoutDatas = GetGoutDatas(m_nCurStateIndex);

	if (pGoutDatas)
	{
		UpdateGoutTab_UI(pGoutDatas);
	}
}

void QSttMacroParaEditViewState::UpdateFT3Tab_UI(CIecCfgDatasSMV *pIecCfgDatasSMV)
{
	int nFT3Block = 0;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		CIecCfgDataBase* pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasSMV->GetNext(pos);
		if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA && pIecCfgDataBase->m_nUseFlag)
		{
			nFT3Block ++;
		}
	}

	if ((m_pParaTab->m_pFT3OutParaWidget == NULL)&&(g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0) && (nFT3Block > 0))
	{
		m_pParaTab->AddFT3OutParaWidget(pIecCfgDatasSMV);

		connect(m_pParaTab->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
	else if ((m_pParaTab->m_pFT3OutParaWidget != NULL)&&(!g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pParaTab->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));

		m_pParaTab->RemoveFT3OutParaWidget();
	}
	else if ((m_pParaTab->m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0))
	{
		if(nFT3Block > 0)
	{
		disconnect(m_pParaTab->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pParaTab->m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
		connect(m_pParaTab->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
		else
		{
			disconnect(m_pParaTab->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
			m_pParaTab->RemoveFT3OutParaWidget();
		}

	}
}

void QSttMacroParaEditViewState::UpdateFT3Tab(BOOL bUpdateList)
{
	if (bUpdateList)
	{
		InitFT3PubDataGroups();

		if (m_bSmvAbnormal)
		{
			InitSvAbnormalTmt();
			m_pSVParaSet->setData(&m_pStatePara->m_oAbnormalSMV,&m_oStateTest.m_oStateParas);
		}
	}

	CIecCfgDatasSMV *pDatasSMV= GetFT3Datas(m_nCurStateIndex);

	if (pDatasSMV)
	{
		UpdateFT3Tab_UI(pDatasSMV);
	}
}

void QSttMacroParaEditViewState::InitSvAbnormalTmt()//用IEC中Sv发布的数据初始化状态序列tmt结构体中内容
{
	tmt_StatePara* pStatePara = NULL;

	for(int i=0;i<m_oStateTest.m_oStateParas.m_nStateNumbers;i++)
	{
		pStatePara = &m_oStateTest.m_oStateParas.m_paraState[i];
		
		CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
		CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
		POS pos = pIecCfgDatasSMV->GetHeadPosition();
		long nSelGroupIndex = 0;

		while (pos)
		{
			pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);

			if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
			{
				continue;
			}

			if (pIecCfgSmvData->m_nUseFlag == 0)
			{
				continue;
			}

			if (nSelGroupIndex == pStatePara->m_oAbnormalSMV.m_nGroupIndex)
			{
				CIecCfg92Data* p92Data = (CIecCfg92Data*)pIecCfgSmvData;
				Global_SetSvAbnormalData(p92Data,pStatePara);
				break;
			}

			nSelGroupIndex++;
		}
	}
}

void QSttMacroParaEditViewState::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas )
{
	if ((m_pParaTab->m_pGooseParaWidget == NULL)&&(g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		m_pParaTab->AddGooseParaWidget(pCfgGoutDatas);

		connect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}
	else if ((m_pParaTab->m_pGooseParaWidget != NULL)&&(!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));

		m_pParaTab->RemoveGooseParaWidget();
	}
	else if ((m_pParaTab->m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		m_pParaTab->m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}	
	else if ((m_pParaTab->m_pGooseParaWidget != NULL)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
		disconnect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pParaTab->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));

		m_pParaTab->RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewState::ClearResult(PTMT_PARAS_HEAD pHead)
{
	((tmt_StateTest*)pHead)->m_oStateResults.init(g_nStateCount);	
}

void QSttMacroParaEditViewState::EnableButtons()
{

	if(m_nCurStateIndex < 0 || m_nCurStateIndex >= m_oStateTest.m_oStateParas.m_nStateNumbers)
	{
		m_pBtnWidget->m_pDeleteState->setDisabled(true);
	}
	else
	{
		m_pBtnWidget->m_pDeleteState->setDisabled(false);
	}
}

void QSttMacroParaEditViewState::setDcoffsetEnable()
{
	if ((m_oStateTest.m_oStateParas.m_nPlusDC == 2) && !stt_Frame_IsTestStarted())
	{
		m_pDCPlus->setEnabled(true);
		if (m_pStatePara->m_bPlusDC)
		{
			m_pLabelTao->setEnabled(true);
			m_pTao->setEnabled(true);
		}
		else
		{
			m_pLabelTao->setEnabled(false);
			m_pTao->setEnabled(false);
		}
	}
	else
	{
		m_pDCPlus->setEnabled(false);
		m_pLabelTao->setEnabled(false);
		m_pTao->setEnabled(false);
	}

}

void QSttMacroParaEditViewState::UpdateActValue(CEventResult *pEventInfo)
{
	m_aStrActValue.clear();
	int nCurrStateIndex = pEventInfo->m_nCurrStateIndex;
	GetActValue(pEventInfo->m_nCurrStepIndex, nCurrStateIndex);
	CString strStateActMsg;
	for (size_t i = 0; i < m_aStrActValue.size(); i++)
	{
		if (i > 0)
		{
			strStateActMsg += " ";
		}
		strStateActMsg += m_aStrActValue[i];
	}

	if (!strStateActMsg.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,strStateActMsg);
	}
}

void QSttMacroParaEditViewState::GetActValue( int nCurStepIndex, int nIndex)
{
	tmt_StatePara* pStatePara = &(m_oStateTest.m_oStateParas.m_paraState[nIndex]);
	tmt_channel* pChVData = pStatePara->m_uiVOL;
	tmt_channel* pChCData = pStatePara->m_uiCUR;
	CExBaseList* pListChVData =&g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef;
	CExBaseList *pListChCData = &g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef;
	long nChIndex = 0;
	int nGradientType = GRADIENT_TYPE_None;
	if(pStatePara->m_nRampTimeGrad > 1)
	{
		nGradientType = GRADIENT_TYPE_Step;
	}
	else
	{
		nGradientType = GRADIENT_TYPE_Linear;
	}

	POS pos = pListChVData->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	CString strChName;
	float nActValue = 0.00f;
	CString strMsgDesc;
	while(pos)
	{
		pCh = pListChVData->GetNext(pos);
		strChName = pCh->m_strName;
		if (nGradientType == GRADIENT_TYPE_Linear )
		{
			if(pChVData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fAmp > pChVData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp - nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue < pChVData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChVData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if(pChVData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fFreq > pChVData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);
					if (nActValue < pChVData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChVData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);

					if (nActValue > pChVData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		else if (nGradientType == GRADIENT_TYPE_Step)
		{
			if(pChVData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fAmp > pChVData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp -nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue <pChVData[nChIndex].Ramp[0].fEnd )
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd; 
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChVData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if(pChVData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fFreq > pChVData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);
					if ( pChVData[nChIndex].Ramp[2].fEnd > nActValue)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChVData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);
					if (nActValue > pChVData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		nChIndex++;
	}


	POS pos2 = pListChCData->GetHeadPosition();
	nChIndex = 0;
	while(pos2)
	{
		pCh = pListChCData->GetNext(pos2);
		strChName = pCh->m_strName;
		if (nGradientType == GRADIENT_TYPE_Linear)
		{
			if(pChCData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fAmp > pChCData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp - nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if (pChCData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fFreq > pChCData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChCData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		else if (nGradientType == GRADIENT_TYPE_Step)
		{
			if(pChCData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fAmp > pChCData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp - nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if(pChCData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fFreq > pChCData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f  HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChCData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue/*.GetString()*/;
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		nChIndex++;
	}

}

void QSttMacroParaEditViewState::UpdateVectorObject()
{
	ASSERT(m_pStatePara != NULL);
	CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
    stt_Frame_UpdateVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);
    stt_Frame_UpdatePowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);
}

void QSttMacroParaEditViewState::slot_PreviosState()//切换上一状态
{

	long  nCurrStateIndex = m_pBtnWidget->m_pStatesComBox->currentIndex();

	if (nCurrStateIndex >0)
	{
		nCurrStateIndex--;
		m_pBtnWidget->m_pStatesComBox->setCurrentIndex(nCurrStateIndex);
	}	
	
	m_pBtnWidget->EnableButtons();
}

void QSttMacroParaEditViewState::slot_NextState()//切换下一状态
{
	long  nCurrStateIndex = m_pBtnWidget->m_pStatesComBox->currentIndex();
	long  nMaxState = m_pBtnWidget->m_pStatesComBox->count();

	if (nCurrStateIndex + 1 < nMaxState)
	{
		nCurrStateIndex++;
		m_pBtnWidget->m_pStatesComBox->setCurrentIndex(nCurrStateIndex);
	}
	
	m_pBtnWidget->EnableButtons();
}

void QSttMacroParaEditViewState::slot_GooseDataChanged()
{
	g_pStateTest->m_bTmtParaChanged = TRUE;
}

void QSttMacroParaEditViewState::slot_FT3DataChanged()
{
	g_pStateTest->m_bTmtParaChanged = TRUE;
}
// void QSttMacroParaEditViewState::slot_RepairDataChanged()
// {
// 	g_pStateTest->m_bTmtParaChanged = TRUE;
// }

/*void QSttMacroParaEditViewState::slot_PasteStateBF()
{
	if (m_nCurStateIndex < 0 && m_nCurStateIndex >= m_oStateTest.m_oStateParas.m_nStateNumbers)
	{
		return;
	}

	if (m_pCopyStatePara == NULL)
	{
		return;
	}

	if(m_pBtnWidget->m_pStatesComBox->count() == g_nStateCount)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("状态数目不能超过%d"), g_nStateCount);
		return;
	}

	stt_state_paras_insert_before(&m_oStateTest.m_oStateParas, m_pCopyStatePara, m_nCurStateIndex);
	InsertGoutDatas(m_pCopyGoutDatas,m_nCurStateIndex);

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox();
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	EnableButtons();
}*/


void QSttMacroParaEditViewState::slot_InsertStateBF()
{
	if (m_pCopyStatePara == NULL)
	{
		m_pCopyStatePara = new tmt_StatePara;
	}
	if(m_pStatePara == NULL)
	{
		return;
	}

	if (g_oSystemParas.m_nHasDigital)
	{
		if (m_pCopyGoutDatas != NULL)
		{
			delete m_pCopyGoutDatas;
			m_pCopyGoutDatas = NULL;
		}
		CIecCfgGoutDatas *pCurrGoutDatas = GetGoutDatas(m_nCurStateIndex);
		
		if (pCurrGoutDatas != NULL)
		{
			m_pCopyGoutDatas = (CIecCfgGoutDatas*)pCurrGoutDatas->Clone();
		}
		else
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前状态(%d)的GOOSE发布数据为空(出现异常)."),m_nCurStateIndex+1); 
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_GOOSEreleaseDataStatusIsempty.GetString(),m_nCurStateIndex+1);//当前状态(%d)的GOOSE发布数据为空(出现异常). lcq 3.14
		}

       /* chenling 20230518
		if (m_pCopyFT3Datas != NULL)
		{
			delete m_pCopyFT3Datas;
			m_pCopyFT3Datas =NULL;
		}
		CIecCfgDatasSMV *pCurrDatasSMV=GetFT3Datas(m_nCurStateIndex);
		if (pCurrDatasSMV != NULL)
		{
			m_pCopyFT3Datas=(CIecCfgDatasSMV*)pCurrDatasSMV->Clone();
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前状态(%d)的FT3发布数据为空(出现异常)."),m_nCurStateIndex+1); 
		}*/
		}
	CopyDatasSMV();

	memcpy(m_pCopyStatePara,m_pStatePara,sizeof(tmt_StatePara));


	if(m_pBtnWidget->m_pStatesComBox->count() == g_nStateCount)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("状态数目不能超过%d"), g_nStateCount);
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_State_NumnotExceed.GetString(), g_nStateCount);
		return;
	}	
	
// 	stt_state_paras_insert_before(&m_oStateTest.m_oStateParas, NULL, m_nCurStateIndex);
// 	InsertGoutDatas(GetGoutDatas(m_nCurStateIndex),m_nCurStateIndex);
	stt_state_paras_insert_before(&m_oStateTest.m_oStateParas, m_pCopyStatePara, m_nCurStateIndex);
	InsertGoutDatas(m_pCopyGoutDatas,m_nCurStateIndex);
	InsertFT3Datas(m_pCopyFT3Datas,m_nCurStateIndex);

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox();
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pStateTest->m_bTmtParaChanged = TRUE;
	//EnableButtons();
}

void QSttMacroParaEditViewState::CopyDatasSMV()
{
	if (g_oSystemParas.m_nHasDigital)
	{
		if (m_pCopyFT3Datas != NULL)
		{
			delete m_pCopyFT3Datas;
			m_pCopyFT3Datas =NULL;
		}
		CIecCfgDatasSMV *pCurrDatasSMV=GetFT3Datas(m_nCurStateIndex);
		if (pCurrDatasSMV != NULL)
		{
			m_pCopyFT3Datas=(CIecCfgDatasSMV*)pCurrDatasSMV->Clone();
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前状态(%d)的FT3发布数据为空(出现异常).")*/g_sLangTxt_Gradient_FRelCurempty.GetString(),m_nCurStateIndex+1);  //lcq
		}
	}
}

void QSttMacroParaEditViewState::slot_InsertStateAF()
{
	if (m_pCopyStatePara == NULL)
	{
		m_pCopyStatePara = new tmt_StatePara;
	}
	if(m_pStatePara == NULL)
	{
		return;
	}

	if (g_oSystemParas.m_nHasDigital)
	{
		if (m_pCopyGoutDatas != NULL)
		{
			delete m_pCopyGoutDatas;
			m_pCopyGoutDatas = NULL;
		}

		CIecCfgGoutDatas *pCurrGoutDatas = GetGoutDatas(m_nCurStateIndex);

		if (pCurrGoutDatas != NULL)
		{
			m_pCopyGoutDatas = (CIecCfgGoutDatas*)pCurrGoutDatas->Clone();
		}
		else
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前状态(%d)的GOOSE发布数据为空(出现异常)."),m_nCurStateIndex+1);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_GOOSEreleaseDataStatusIsempty.GetString(),m_nCurStateIndex+1); //lcq 3.140-----
		}

		/*if (m_pCopyFT3Datas != NULL)
		{
			delete m_pCopyFT3Datas;
			m_pCopyFT3Datas =NULL;
		}
		CIecCfgDatasSMV *pCurrDatasSMV=GetFT3Datas(m_nCurStateIndex);
		if (pCurrDatasSMV != NULL)
		{
			m_pCopyFT3Datas=(CIecCfgDatasSMV*)pCurrDatasSMV->Clone();
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前状态(%d)的FT3发布数据为空(出现异常)."),m_nCurStateIndex+1); 
		}*/
	}

	CopyDatasSMV();
	memcpy(m_pCopyStatePara,m_pStatePara,sizeof(tmt_StatePara));

	if(m_pBtnWidget->m_pStatesComBox->count() == g_nStateCount)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("状态数目不能超过%d"), g_nStateCount);
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_State_NumnotExceed.GetString(), g_nStateCount);//lcq 3.14
		return;
	}	
	
// 	stt_state_paras_insert_after(&m_oStateTest.m_oStateParas, NULL, m_nCurStateIndex);
// 	InsertGoutDatas(GetGoutDatas(m_nCurStateIndex),m_nCurStateIndex+1);

 	stt_state_paras_insert_after(&m_oStateTest.m_oStateParas, m_pCopyStatePara, m_nCurStateIndex);
 	InsertGoutDatas(m_pCopyGoutDatas,m_nCurStateIndex+1);
	InsertFT3Datas(m_pCopyFT3Datas,m_nCurStateIndex+1);

	m_nCurStateIndex++;
	//m_pBtnWidget->m_nCurStateIndex = m_nCurStateIndex;

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox();
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pStateTest->m_bTmtParaChanged = TRUE;
	EnableButtons();
}
	
/*void QSttMacroParaEditViewState::slot_PasteStateAF()
{
	if (m_nCurStateIndex < 0 && m_nCurStateIndex >= m_oStateTest.m_oStateParas.m_nStateNumbers)
	{
		return;
	}

	if (m_pCopyStatePara == NULL)
	{
		return;
	}

	if(m_pBtnWidget->m_pStatesComBox->count() == g_nStateCount)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("状态数目不能超过%d"), g_nStateCount);
		return;
	}

	stt_state_paras_insert_after(&m_oStateTest.m_oStateParas, m_pCopyStatePara, m_nCurStateIndex);
	InsertGoutDatas(m_pCopyGoutDatas,m_nCurStateIndex+1);

	m_nCurStateIndex++;
	m_pBtnWidget->m_nCurStateIndex = m_nCurStateIndex;

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox();
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pStateTest->m_bTmtParaChanged = TRUE;
	EnableButtons();
}*/

void QSttMacroParaEditViewState::InsertGoutDatas(CIecCfgGoutDatas *pIecCfgGoutDatas,long nInsertStateIndex)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		if (pIecCfgGoutDatas)
		{
			CIecCfgGoutDatas *pNewIecCfgGoutDatas = (CIecCfgGoutDatas*)pIecCfgGoutDatas->Clone();
			m_listGoosePub.insert(nInsertStateIndex,pNewIecCfgGoutDatas);//在当前状态后插入
		}
	}
}
	
void QSttMacroParaEditViewState::InsertFT3Datas(CIecCfgDatasSMV *pIecCfgDatasSMV,long nInsertStateIndex)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		if (pIecCfgDatasSMV)
		{
			CIecCfgDatasSMV *pNewIecCfgDatasSMV = (CIecCfgDatasSMV*)pIecCfgDatasSMV->Clone();
			m_listFT3Pub.insert(nInsertStateIndex,pNewIecCfgDatasSMV);
		}
	}
}
//void QSttMacroParaEditViewState::slot_CopyState()
//{
//	if (m_pCopyStatePara == NULL)
//	{
//		m_pCopyStatePara = new tmt_StatePara;
//	}
//
//	if(m_pStatePara == NULL)
//	{
//		return;
//	}
//
//	if (g_oSystemParas.m_nHasDigital)
//	{
//		if (m_pCopyGoutDatas != NULL)
//		{
//			delete m_pCopyGoutDatas;
//			m_pCopyGoutDatas = NULL;
//		}
//
//		CIecCfgGoutDatas *pCurrGoutDatas = GetGoutDatas(m_nCurStateIndex);
//
//		if (pCurrGoutDatas != NULL)
//		{
//			m_pCopyGoutDatas = (CIecCfgGoutDatas*)pCurrGoutDatas->Clone();
//		}
//		else
//		{
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前状态(%d)的GOOSE发布数据为空(出现异常)."),m_nCurStateIndex+1);
//		}
//	}
//	
//	memcpy(m_pCopyStatePara,m_pStatePara,sizeof(tmt_StatePara));
//	EnableButtons();
//}
	
void QSttMacroParaEditViewState::slot_DeleteState()
{
	if(m_oStateTest.m_oStateParas.m_nStateNumbers <= 1)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("至少保留一个状态."));
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Gradient_MaintainatLeastOneState.GetString()); //至少保留一个状态 lcq 3.14
		return;	//必须至少一个状态
	}

	stt_state_paras_delete(&m_oStateTest.m_oStateParas,m_nCurStateIndex);

	if (g_oSystemParas.m_nHasDigital)
	{
		m_listGoosePub.removeAt(m_nCurStateIndex);
		m_listFT3Pub.removeAt(m_nCurStateIndex);
	}

	m_nCurStateIndex--;

	if(m_nCurStateIndex < 0)
	{
		m_nCurStateIndex = 0;
	}
	//m_pBtnWidget->m_nCurStateIndex = m_nCurStateIndex;

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox();
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pStateTest->m_bTmtParaChanged = TRUE;
	EnableButtons();
}

void QSttMacroParaEditViewState::slot_EditState()
{
	CExBaseList oList;
	
	for (int i = 0; i < m_oStateTest.m_oStateParas.m_nStateNumbers; i++)
	{
		tmt_StatePara pPara = m_oStateTest.m_oStateParas.m_paraState[i];
		CExBaseObject* pObj = new CExBaseObject;
		CString strText = g_sLangTxt_State, strNum;
		strNum.Format("%d", i + 1);
		strText += strNum;
		CString strName = pPara.m_strName;
		if(!strName.GetLength())
		{
			strcpy(pPara.m_strName, strText.GetString());
		}
		pObj->m_strName = pPara.m_strName;
		pObj->m_strID = strText;
		pObj->m_dwItemData = pPara.m_bSelected;
		oList.AddNewChild(pObj);
	}
	
	QStateEditDlg dlg(this);
	dlg.m_pEditGrid->ShowDatas(&oList);
	if(dlg.exec() == QDialog::Accepted)
	{
		m_SelStateList.clear();

		POS pos = oList.GetHeadPosition();
		long nIndex = 0;
		while (pos)
		{
			CExBaseObject* pObj = oList.GetNext(pos);
			strcpy(m_oStateTest.m_oStateParas.m_paraState[nIndex].m_strName, pObj->m_strName.GetString());
			m_oStateTest.m_oStateParas.m_paraState[nIndex].m_bSelected = pObj->m_dwItemData;

			if (m_oStateTest.m_oStateParas.m_paraState[nIndex].m_bSelected)
			{
				m_SelStateList.append(nIndex);
			}
			nIndex++;
		}
	}

	m_pBtnWidget->UpdateStateCombox();
}
	
void QSttMacroParaEditViewState::slot_StatesIndexChanged(int nIndex)
{
	if (nIndex < 0)
	{
		return;
	}
	if (! m_pBtnWidget->m_bEnable_slot_StatesIndexChanged)
	{
		return;
	}

	if(m_pBtnWidget->m_pStatesComBox->IsScrolling())
	{
		return;
	}

	CString strCurStateName = m_pBtnWidget->m_pStatesComBox->currentText();
// 	int nCurIndex = 0;
// 	int nCurStateIndex = 0;

// 	for (nCurIndex = 0; nCurIndex < m_oStateTest.m_oStateParas.m_nStateNumbers; nCurIndex++)
// 	{
// 		if (m_oStateTest.m_oStateParas.m_paraState[nCurIndex].m_bSelected)
// 		{
// 			tmt_StatePara* pPara = &m_oStateTest.m_oStateParas.m_paraState[nCurIndex];
// 			CString strName = pPara->m_strName;
// 			if (strCurStateName == strName)
// 			{
// 				nCurStateIndex = nCurIndex;
// 				break;
// 			}
// 		}
// 	}

	if (nIndex < 0 || nIndex >= m_oStateTest.m_oStateParas.m_nStateNumbers)
	{
		return;
	}
	
	if (nIndex > m_SelStateList.count())
	{
		return;
	}
	
	m_nCurStateIndex = m_SelStateList.at(nIndex);
	m_pStatePara = &m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex];

	//m_pBtnWidget->m_nCurStateIndex = nIndex;
// 	m_pStatePara = &m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex];
	m_pBtnWidget->EnableButtons();
	
	UpdateStateParas();
	setDcoffsetEnable();
}

void QSttMacroParaEditViewState::slot_BinarySet()
{
	QStateBinarySetDlg dlg(this);
	dlg.setData(m_pStatePara);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
#endif

	if (dlg.exec() == QDialog::Accepted)
	{
		//2024-8-1 wuxinyi 新增更新开入量状态灯
		CopyBinaryConfig(TRUE);
		stt_Frame_UpdateToolButtons();
	}
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif


}
	
void QSttMacroParaEditViewState::slot_CommonPara()
{
	CommonValueDialogState dlg(&m_oStateTest.m_oStateParas, this);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif

	if (dlg.m_nIsOK==1)
	{
		g_pStateTest->m_bTmtParaChanged = TRUE;
	}
}

void QSttMacroParaEditViewState::slot_ShortClac()
{
	ShortCalcuDig dig(g_oSttTestResourceMngr.m_pTestResouce,m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR,m_ShortCalcuPara,this);
	dig.setWindowModality(Qt::WindowModal);
	connect(&dig,SIGNAL(sig_ShortCalcuOk(ShortCalcuPara &)),this,SLOT(slot_ShortCalcuOk(ShortCalcuPara &)));

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dig);
	dig.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dig.exec();
#endif
}

void QSttMacroParaEditViewState::slot_Estimate()
{
	StateEstimateDlg dlg(&m_oStateTest.m_oStateParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewState::slot_SettingValue()
{
	StateSettingValueDlg dlg(&m_oStateTest.m_oStateParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewState::slot_DiffCurrCalcBtnClicked()
{
	SttDiffCurrCalDlg dig(this);
	dig.setFont(*g_pSttGlobalFont);
	dig.setWindowModality(Qt::WindowModal);
	dig.InitUI(&m_oDiffCurrCalParas);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dig);
#endif

	if (dig.exec() == QDialog::Accepted)
	{
		long nHeightBeginIndex = dig.m_nHeightUsedIndex*3;
		long nLowerBeginIndex = dig.m_nLowerUsedIndex*3;

		if (nHeightBeginIndex >= 0 && nLowerBeginIndex >= 0)
		{
		ChannelUI_Diff* pChannelUI_Diff = dig.m_oDiffCalTool.GetChannelCurrents();
		m_pStatePara->m_uiCUR[nHeightBeginIndex].Harm[1].fAmp = pChannelUI_Diff[0].famptitude;
		m_pStatePara->m_uiCUR[nHeightBeginIndex].Harm[1].fAngle = pChannelUI_Diff[0].fphase;
		m_pStatePara->m_uiCUR[nHeightBeginIndex+1].Harm[1].fAmp = pChannelUI_Diff[1].famptitude;
		m_pStatePara->m_uiCUR[nHeightBeginIndex+1].Harm[1].fAngle = pChannelUI_Diff[1].fphase;
		m_pStatePara->m_uiCUR[nHeightBeginIndex+2].Harm[1].fAmp = pChannelUI_Diff[2].famptitude;
		m_pStatePara->m_uiCUR[nHeightBeginIndex+2].Harm[1].fAngle = pChannelUI_Diff[2].fphase;
		m_pStatePara->m_uiCUR[nLowerBeginIndex].Harm[1].fAmp = pChannelUI_Diff[3].famptitude;
		m_pStatePara->m_uiCUR[nLowerBeginIndex].Harm[1].fAngle = pChannelUI_Diff[3].fphase;
		m_pStatePara->m_uiCUR[nLowerBeginIndex+1].Harm[1].fAmp = pChannelUI_Diff[4].famptitude;
		m_pStatePara->m_uiCUR[nLowerBeginIndex+1].Harm[1].fAngle = pChannelUI_Diff[4].fphase;
		m_pStatePara->m_uiCUR[nLowerBeginIndex+2].Harm[1].fAmp = pChannelUI_Diff[5].famptitude;
		m_pStatePara->m_uiCUR[nLowerBeginIndex+2].Harm[1].fAngle = pChannelUI_Diff[5].fphase;
		UpdateStateParas();
	}
		
	}
#ifdef _USE_SoftKeyBoard_	
	QSoftKeyBoard::ReAttachObj();
#endif
}	

void QSttMacroParaEditViewState::slot_GradientSet()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	GradientSetDlg dlg(this);
	dlg.setWindowModality(Qt::WindowModal);
	dlg.setData(g_oSttTestResourceMngr.m_pTestResouce,m_pStatePara);

	//336D 分辨率800x600 dlg显示不全
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
#endif
	dlg.exec();
	if (dlg.m_nIsOK==1)
	{
		g_pStateTest->m_bTmtParaChanged = TRUE;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	m_pParaTab->m_pUIParaWidget->initData();
}

void QSttMacroParaEditViewState::slot_ShortCalcuOk(ShortCalcuPara &para)
{
	if (!m_ShortCalcuPara.isSame(para))
	{
		m_ShortCalcuPara = para;
		g_pStateTest->m_bTmtParaChanged = TRUE;
	}
	
	UpdateStateParas();
}

void QSttMacroParaEditViewState::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	BOOL bVisibleBottomCtrlsGoose = (m_pParaTab->m_tabWidget->currentWidget() == m_pParaTab->m_pGooseParaWidget );
	BOOL bVisibleBottomCtrlsFT3 = (m_pParaTab->m_tabWidget->currentWidget() == m_pParaTab->m_pFT3OutParaWidget );
	BOOL bVisibleBottomCtrls=!(bVisibleBottomCtrlsGoose || bVisibleBottomCtrlsFT3);
	m_pTrigerWidget->setVisible(bVisibleBottomCtrls);
	m_pBinarySet->setVisible(bVisibleBottomCtrls);
	//m_pSettingValue->setVisible(bVisibleBottomCtrls);
	m_pEstimate->setVisible(bVisibleBottomCtrls);
	m_pCommonPara->setVisible(bVisibleBottomCtrls);
	m_pShortCalc->setVisible(bVisibleBottomCtrls);
	m_pDiffCurrCalcBtn->setVisible(bVisibleBottomCtrls);
	if(m_pGradientSet)
	{
		m_pGradientSet->setVisible(bVisibleBottomCtrls);
	}
	m_pDC->setVisible(bVisibleBottomCtrls);
	m_pDCPlus->setVisible(bVisibleBottomCtrls);
	if(xlang_GetCurrLanguageID() != CURRLANGUAGE_RUSSIAN)
	{
	m_pLabelTao->setVisible(bVisibleBottomCtrls);
	}
	m_pTao->setVisible(bVisibleBottomCtrls);

}

void QSttMacroParaEditViewState::slot_UpdateToolButtons()
{
	//2024-8-1 wuxinyi 新增更新开入量状态灯
	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

//void QSttMacroParaEditViewState::slot_lne_FreChanged()
//{
//	QString str = m_pFreEdit->text();
//	GetWidgetBoard_DigitData(4,str,m_pFreEdit,this);

// 	float fv = str.toFloat();
// 	fv = setLimit(0.0f/*0.001*/,MAXHZ,fv);//20220816 各通道频率可以设置为0 此处也改为0
// 	m_pFreEdit->setText(QString::number(fv,'f',3));
// 
// 	bool bChanged = FALSE;
// 	for (int i = 0;i<MAX_VOLTAGE_COUNT;i++)
// 	{
// 		if (m_pStatePara->m_uiVOL[i].Harm[1].fFreq != fv)
// 		{
// 			bChanged = TRUE;
// 			m_pStatePara->m_uiVOL[i].Harm[1].fFreq = fv;
// 		}
// 	}
// 
// 	for (int j = 0;j<MAX_CURRENT_COUNT;j++)
// 	{
// 		if (m_pStatePara->m_uiCUR[j].Harm[1].fFreq != fv)
// 		{
// 			bChanged = TRUE;
// 			m_pStatePara->m_uiCUR[j].Harm[1].fFreq = fv;
// 		}
// 	}
// 
// 	if (bChanged)
// 	{
// 		g_pStateTest->m_bTmtParaChanged = TRUE;
// 	}
// 
// 	UpdateStateParas();
//}


// void QSttMacroParaEditViewState::slot_lne_FreChangedKeyBoard()
// {
// 	QString str = m_pFreEdit->text();
// 	// 	GetWidgetBoard_DigitData(4,str,this);
// 
// 	float fv = str.toFloat();
// 	fv = setLimit(0.0f/*0.001*/,MAXHZ,fv);//20220816 各通道频率可以设置为0 此处也改为0
// 	m_pFreEdit->setText(QString::number(fv,'f',3));
// 
// 	bool bChanged = FALSE;
// 	for (int i = 0;i<MAX_VOLTAGE_COUNT;i++)
// 	{
// 		if (m_pStatePara->m_uiVOL[i].Harm[1].fFreq != fv)
// 		{
// 			bChanged = TRUE;
// 			m_pStatePara->m_uiVOL[i].Harm[1].fFreq = fv;
// 		}
// 	}
// 
// 	for (int j = 0;j<MAX_CURRENT_COUNT;j++)
// 	{
// 		if (m_pStatePara->m_uiCUR[j].Harm[1].fFreq != fv)
// 		{
// 			bChanged = TRUE;
// 			m_pStatePara->m_uiCUR[j].Harm[1].fFreq = fv;
// 		}
// 	}
// 
// 	if (bChanged)
// 	{
// 		g_pStateTest->m_bTmtParaChanged = TRUE;
// 	}
// 
// 	UpdateStateParas();
// }



void QSttMacroParaEditViewState::slot_chb_DcStateChanged(int)
{	
	bool b;
	if (m_pDC->isChecked())
	{
		b = true;
		m_pShortCalc->setDisabled(true);
		m_pDiffCurrCalcBtn->setDisabled(true);
		//m_pFreEdit->setDisabled(true);
	}
	else 
	{
		b = false;
		m_pShortCalc->setDisabled(false);
		m_pDiffCurrCalcBtn->setDisabled(false);
       
		//m_pFreEdit->setDisabled(false);
	}

	if(m_pStatePara->m_bDC != b)
	{
		m_pStatePara->setDC(b,true);
		g_pStateTest->m_bTmtParaChanged = TRUE;

		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
		m_pParaTab->m_pUIParaWidget->DCStateChanged(P_Common,b);

		if (m_pParaTab->ExistHarmParaset())
		{
			m_pParaTab->m_pHarmParaWidget->setMaxMinAndEDVal();
			m_pParaTab->m_pHarmParaWidget->DCStateChanged(P_Harm,b);
		}
	}
}

void QSttMacroParaEditViewState::slot_chb_DcPlusStateChanged(int)
{
	bool b;
	if (m_pDCPlus->isChecked())
	{
		b = true;
		m_pTao->setDisabled(false);
		m_pLabelTao->setDisabled(false);
	}
	else 
	{
		b = false;
		m_pTao->setDisabled(true);
		m_pLabelTao->setDisabled(true);
	}

	if(m_pStatePara->m_bPlusDC != b)
	{
		m_pStatePara->m_bPlusDC = b;
		g_pStateTest->m_bTmtParaChanged = TRUE;
	}

}

void QSttMacroParaEditViewState::slot_lne_TaoChanged()
{
	//20240718 huangliang 
	if (m_pTao->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pTao)->IsSetting())
		{
			return;
		}
	}

	if (m_pTao->text().isEmpty())
	{
		m_pTao->setText("0.100");
	}

	QString str = m_pTao->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv = str.toFloat();
	fv = setLimit(0,999.999,fv);

	m_pTao->setText(QString::number(fv,'f',3));

	if (m_pStatePara != NULL)
	{
		m_pStatePara->m_fTao = fv;
		g_pStateTest->m_bTmtParaChanged = TRUE;
	}
}

void QSttMacroParaEditViewState::slot_DcCoffsetStateChanged()
{
	tmt_StatePara pStatePara = m_oStateTest.m_oStateParas.m_paraState[m_nCurStateIndex];
	setDcoffsetEnable();
}

void QSttMacroParaEditViewState::slot_SwitchStateChanged()
{
	if(stt_Frame_IsTestStarted())
	{
		stt_Frame_UpdateToolButtons();
	}
}

void QSttMacroParaEditViewState::OnViewTestLink(BOOL b)
{
	if(!b)
	{
		OnViewTestStop();
	}
}

void QSttMacroParaEditViewState::OnViewTestStart()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]OnViewTestStart_StateTest."));
	//切换到状态1, 并初始化循环计数器
	m_nCircle = 0;
	m_pBtnWidget->m_pStatesComBox->setCurrentIndex(0);

	//m_pFreEdit->setDisabled(true);
	m_pDC->setDisabled(true);
	m_pDCPlus->setDisabled(true);
	m_pLabelTao->setDisabled(true);
	m_pTao->setDisabled(true);
    m_pBinarySet->setDisabled(true);
	//m_pSettingValue->setVisible(true);
	m_pEstimate->setDisabled(true);
	m_pCommonPara->setDisabled(true);
	m_pShortCalc->setDisabled(true);
	m_pDiffCurrCalcBtn->setDisabled(true);

	if (m_pGradientSet != NULL)
	{
		m_pGradientSet->setDisabled(true);
	}

	m_pBtnWidget->startInit();
	m_pBtnWidget->EnableButtons(); //2023-1-13

	m_pTrigerWidget->startInit();//2023-1-12

	InitManuTrigerButton();
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pParaTab->startInit();

	if(m_pParaTab->m_pGooseParaWidget)
	{
		m_pParaTab->m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pParaTab->m_pFT3OutParaWidget)
	{
		m_pParaTab->m_pFT3OutParaWidget->setDisabled(true);
	}
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	m_mapState.clear();
	CString strStateName;

	for(int i = 0; i < m_oStateTest.m_oStateParas.m_nStateNumbers; i++)
	{
		if(m_oStateTest.m_oStateParas.m_paraState[i].m_bSelected)
		{
			strStateName = m_oStateTest.m_oStateParas.m_paraState[i].m_strName;

			if (strStateName.IsEmpty())
			{
				strStateName = g_sLangTxt_State;
				strStateName.AppendFormat(_T("%ld"),i+1);
			}
			m_mapState.insert(m_mapState.size(),strStateName );
		}
	}
}

void QSttMacroParaEditViewState::OnViewTestStop()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]OnViewTestStop_StateTest."));
	m_pTrigerWidget->stopInit();//2023-1-12
	m_pDC->setDisabled(false);
	m_pDCPlus->setDisabled(false);
	m_pLabelTao->setDisabled(false);
	m_pTao->setDisabled(false);
	m_pBinarySet->setDisabled(false);
	//m_pSettingValue->setVisible(false);
	m_pEstimate->setDisabled(false);
	m_pCommonPara->setDisabled(false);
	m_pShortCalc->setDisabled(false);
	m_pDiffCurrCalcBtn->setDisabled(false);

	if (m_pGradientSet != NULL)
	{
		m_pGradientSet->setDisabled(false);
	}

	m_pBtnWidget->stopInit(m_pCopyStatePara != NULL);

	m_pParaTab->stopInit();
	if(m_pParaTab->m_pGooseParaWidget)
	{
		m_pParaTab->m_pGooseParaWidget->setDisabled(false);
	}
	if(m_pParaTab->m_pFT3OutParaWidget)
	{
		m_pParaTab->m_pFT3OutParaWidget->setDisabled(false);
	}
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget();
	stt_Frame_StopPowerWidget();
	setDcoffsetEnable();
}

void QSttMacroParaEditViewState::InitManuTrigerButton()
{
	if (m_oStateTest.m_oStateParas.m_paraState[0].m_nTriggerCondition == TMT_MDSTATE_MEARSURETRIGGER)
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true);
	}
	else
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false);
	}
}

void QSttMacroParaEditViewState::SysStateReport_OnStateChanged(CEventResult *pEventInfo)
{	
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]SysStateReport_OnStateChanged(%ld)."),pEventInfo->m_nCurrStateIndex);
	ASSERT(pEventInfo != NULL);
	int nStateIndex = -1;
	if (pEventInfo->m_nCurrStateIndex>=0)
	{
		if(pEventInfo->m_nCurrStateIndex == 0)
		{
			m_nCircle++;
		}

		CString strStateMsg, strLoopNum, strInState, strStateNum;
		//strStateMsg.Format(_T("当前循环%d, 进入状态%ld."), m_nCircle, pEventInfo->m_nCurrStateIndex+1);

		//strStateMsg = _T("当前循环");
		strStateMsg = g_sLangTxt_State_TheCurrentLoop; //当前循环 lcq 3.14
		strLoopNum.Format("%d", m_nCircle);
#ifndef _PSX_QT_LINUX_
		//strInState = _T("进入");
		strInState = g_sLangTxt_State_Enter; //进入 lcq 3.14
		strInState += m_mapState[pEventInfo->m_nCurrStateIndex];
#else
		strInState = /*_T("进入状态")*/g_sLangTxt_State_InState;
		strStateNum.Format("%ld", pEventInfo->m_nCurrStateIndex+1);
#endif
		strStateMsg = strStateMsg + strLoopNum + strInState + strStateNum;
		CLogPrint::LogString(XLOGLEVEL_RESULT, strStateMsg);
		
		//2024-9-2 wuxinyi 更新切换状态序号
		//m_pBtnWidget->m_pStatesComBox->setCurrentIndex(pEventInfo->m_nCurrStateIndex);
		//tmt_StatePara* pStatePara = &(m_oStateTest.m_oStateParas.m_paraState[pEventInfo->m_nCurrStateIndex]);

		for (int nIndex = 0; nIndex < m_SelStateList.count(); nIndex++)
		{
			int nCurIndex = m_SelStateList.at(nIndex);
			if (pEventInfo->m_nCurrStateIndex == nCurIndex)
			{
				nStateIndex = nIndex;
				//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[问题查找]nStateIndex(%ld)."), nStateIndex);
				break;
			}
		}

		m_pBtnWidget->m_pStatesComBox->setCurrentIndex(nStateIndex);
		tmt_StatePara* pStatePara = &(m_oStateTest.m_oStateParas.m_paraState[m_SelStateList.at(nStateIndex)]);

		if (pStatePara->m_nTriggerCondition == TMT_MDSTATE_MEARSURETRIGGER)
		{
			//手动触发按钮变亮
			stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true);
		}
		else
		{
			//手动触发按钮变暗
			stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false);
		}
	}
}

void QSttMacroParaEditViewState::UpdateEventMsg( CEventResult *pCurrEventResult )
{
	if (pCurrEventResult == NULL)
	{
		return;
	}

	if (pCurrEventResult->m_fActTime > 0.00001)
	{
		CString strResultMsg;
//2024-8-17 wuxinyi 打印信息乱码
#ifdef _PSX_QT_WINDOWS_
		//strResultMsg.Format(g_sLangTxt_Native_StateD, pCurrEventResult->m_nCurrStateIndex + 1);
		strResultMsg += g_sLangTxt_State;
		strResultMsg.AppendFormat(_T("%d"), pCurrEventResult->m_nCurrStateIndex + 1);
		strResultMsg += g_sLangTxt_Gradient_ActionTime;
		strResultMsg.AppendFormat(_T("%.4lfs"), pCurrEventResult->m_fActTime);
#else		
		strResultMsg.Format(g_sLangTxt_Native_StatusLDActTime.GetString()/*_T("状态%ld动作时间%.4lfs.")*/,
			 pCurrEventResult->m_fActTime);
#endif 

		CLogPrint::LogString(XLOGLEVEL_RESULT, strResultMsg);
		if (strcmp(m_oStateTest.m_pszMacroID, STT_ORG_MACRO_StateTest) == 0)
		{
			UpdateActValue(pCurrEventResult);
		}
	}
}

//void QSttMacroParaEditViewState::GetSMVDataAppIDs(QList<int> &olistAppIDs)
//{
//	olistAppIDs.clear();
//	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
//	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
//	POS pos = pIecCfgDatasSMV->GetHeadPosition();
////	long nFindIndex = 0;
//
//	while(pos)
//	{
//		pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);
//
//		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
//		{
//			continue;
//		}
//		olistAppIDs.append(((CIecCfg92Data*)pIecCfgSmvData)->m_dwAppID);
//	}
//
//// 	for (int i=0;i<pIecCfgDatasSMV->GetCount();i++)
//// 	{
//// 		pIecCfgSmvData = (CIecCfgSmvDataBase*)pIecCfgDatasSMV->GetAtIndex(i);
//// 		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
//// 		{
//// 			continue;
//// 		}
//// 
//// 		m_olistAppIDs.append(((CIecCfg92Data*)pIecCfgSmvData)->m_dwAppID);
//// 	}
//}

//void QSttMacroParaEditViewState::GetSMVDataAppID(int nIndex)
//{
//	long nFindIndex = 0;
//
//	GetSMVDataAppIDs(nIndex);
//
//	if (nFindIndex == nIndex)
//	{
//		return;
//	}
//	else
//	{
//		nFindIndex++;
//	}
//}

long QSttMacroParaEditViewState::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)
{
	return CSttMacroParaEditViewOriginal::GetMacroItemsXml(strMacroItemsID,ppszItemsXml);
}

void QSttMacroParaEditViewState::GetMacroItemsXml(CSttItems &oRootItems)
{
	CSttItems* pRoot = new CSttItems;
	pRoot->m_strID = GetMacroID();
	pRoot->m_nTkID = 65535;
	oRootItems.AddNewChild(pRoot);

	CSttItems* pItems = new CSttItems;
	pItems->m_strID = GetMacroID();
	pItems->m_nTkID = 65535;
	pRoot->AddNewChild(pItems);

	for (int i = 0; i < m_oStateTest.m_oStateParas.m_nStateNumbers; i++)
	{
		CSttItems* pStateItems = new CSttItems;
		pStateItems->m_strID = "state" + QString::number(i);
		pStateItems->m_nTkID = 65535;
		pItems->AddNewChild(pStateItems);

		GetMacroItemsXml_Chs(pStateItems);
	}
}

void QSttMacroParaEditViewState::ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook)
{
	CString strMacroID;
	strMacroID = GetMacroID();
	CSttDevice *pDevice = pSttGuideBook->GetDevice();
	CSttItems* pRootItems=( CSttItems*)pDevice->FindByID (strMacroID/*_T("StateTest")*/);

	if (pRootItems ==NULL)
	{
		return;
	}

	CSttItemBase *pMacroTestState = (CSttItemBase *)pRootItems-> FindByID(strMacroID/*_T("StateTest")*/);
	CSttItems *pNewRootItems = NULL;
	int nRepeatNumbers = m_oStateTest.m_oStateParas.m_nRepeatNumbers;  
#ifdef USE_STT_STATE_EX_REPORT
	if ((nRepeatNumbers > STT_STATE_REPORT_MAX_REPEAT_COUNT)
		&& stt_Frame_IsTestStarted())
	{
		nRepeatNumbers = STT_STATE_REPORT_MAX_REPEAT_COUNT; //dingxy 20240606 循环次数过多时生成模板速度慢导致界面卡，循环次数多时暂时不更新报告
	}
#endif
	for (long k = 1; k <= nRepeatNumbers; k++)
	{
		pNewRootItems = (CSttItems*)pRootItems->CloneEx();
		pNewRootItems->m_strID.AppendFormat(_T("%d"), k+1);  
		pNewRootItems->m_strName.AppendFormat(_T("%d"), k+1);  
		pDevice->AddNewChild(pNewRootItems);

		CSttItemBase *pCurrItem = (CSttItemBase *) pMacroTestState ->Clone();  //克隆Item
		pNewRootItems->AddNewChild(pCurrItem);
	}
}

void QSttMacroParaEditViewState::UpdateReportFile()
{
#ifdef USE_STT_STATE_EX_REPORT
	CString strFileName,strExFileName,strPath;
	strFileName = stt_Frame_TestMacroUI()->m_strReportFile;
	
	if (strFileName.Find("Ex_Report.html")>0)
	{
		strExFileName = strFileName;
		strFileName.Replace("Ex_Report.html","_Report.html");
	}
	else
	{
		strExFileName = strFileName;
		strExFileName.Replace("_Report.html","Ex_Report.html");
	}

	strPath = _P_GetDBPath();
	strPath += "ui/";
#ifdef NOT_USE_XLANGUAGE  //zhouhj 20220401 如果未使用多语言,固定用中文
	strPath += _T("chinese");
#else
	strPath += xlang_GetCurrLanguageID();
#endif
	strPath += "/";
	strPath += strExFileName;

	if (!IsFileExist(strPath))
	{
		stt_Frame_TestMacroUI()->m_strReportFile = strFileName;
		return;
	}

	int nRepeatNumbers = m_oStateTest.m_oStateParas.m_nRepeatNumbers;  //循环次数参数
	int nStateCount = m_oStateTest.m_oStateParas.m_nStateNumbers;

	if (((nStateCount > STT_SINGLE_STATE_MAX_REPORT_COUNT)
		|| (nStateCount * nRepeatNumbers > STT_STATE_REPORT_TOTAL_STATE_NUM))
		&& stt_Frame_IsTestStarted())
	{
		stt_Frame_TestMacroUI()->m_strReportFile = strExFileName;
	}
	else
	{
		stt_Frame_TestMacroUI()->m_strReportFile = strFileName;
	}

#endif
}

void QSttMacroParaEditViewState::ProcessRptAfterGenTemplate(QSttReportViewHtml *pSttReportViewHtml)
{
	//获得项目的报告数据strReport【初始化的时候，每个数据都是一样的】
	char *strReport = NULL,*strNewReport = NULL;
	long nLen = 0;
	CString strMacroID = stt_Frame_TestMacroUI()->m_strID;
	nLen = GetMacroItemsXml(strMacroID, &strReport);
	///*g_theTestCntrFrame->*/GetMacroItemsXml(&strReport, nLen);

	CString strItemID;
	int nRepeatNumbers = m_oStateTest.m_oStateParas.m_nRepeatNumbers;  //循环次数参数
	long nRepeatIndex = 0;

	UpdateReportFile();

#ifdef USE_STT_STATE_EX_REPORT
	if ((nRepeatNumbers > STT_STATE_REPORT_MAX_REPEAT_COUNT)
		&& stt_Frame_IsTestStarted())
	{
		nRepeatNumbers = STT_STATE_REPORT_MAX_REPEAT_COUNT;
	}
#endif

	for (nRepeatIndex = 0; nRepeatIndex< nRepeatNumbers;nRepeatIndex++)
	{
		strItemID.Format("StateTest%d", nRepeatIndex+2); 
		//pSttReportViewHtml->OpenRptFileData(stt_Frame_TestMacroUI()->m_strReportFile,"",strItemID);
		strNewReport = new char[nLen+20];
		memset(strNewReport,0,nLen+20);
		memcpy(strNewReport,strReport,nLen);
		pSttReportViewHtml->AddInsertCmd(stt_Frame_TestMacroUI(),"", strItemID, strNewReport, FALSE);
		//pSttReportViewHtml->InsertRptHtml("", strItemID, strNewReport);

		strNewReport = new char[nLen+20];
		memset(strNewReport,0,nLen+20);
		memcpy(strNewReport,strReport,nLen);
		//根据报告数据更新每个状态序列的状态数【报告模板，默认状态数是20个，需要根据设置的状态数删除多余的状态报告】
		pSttReportViewHtml->AddUpdateCmd(stt_Frame_TestMacroUI(), "", strItemID, strNewReport, FALSE);
		//pSttReportViewHtml->UpdateMacroTestReport("", strItemID,strNewReport);
	}

	for (;nRepeatIndex < m_nRepeatNum_GenerateRpt;nRepeatIndex++)
	{
		strItemID.Format("StateTest%d", nRepeatIndex+2); 
		pSttReportViewHtml->DeleteRptHtml("",strItemID);
	}

	m_nRepeatNum_GenerateRpt = nRepeatNumbers;

	delete strReport;

	//pSttReportViewHtml->ExcuteNextCmd();
}

CString QSttMacroParaEditViewState::ProcessItemID(const CString & strItemID,long nLoopIndex)
{
	//strItemID：根据当前重复的次数，动态更新ID，与模板调整的ID一致的
	CString strNewID;

	if(nLoopIndex <= 0)
	{
		if (strItemID.IsEmpty())
		{
			strNewID = _T("StateTest$StateTest");
		} 
		else
		{
		strNewID = strItemID;
	}
	}
	else
	{
		strNewID.Format(_T("StateTest%d$StateTest"), nLoopIndex+1);
	}

	return strNewID;
}

BOOL Global_SetSvAbnormalData(CIecCfg92Data* pIecCfgSmvData,tmt_StatePara *pStatePara)
{
	return Global_SetSvAbnormalData(pIecCfgSmvData,&pStatePara->m_oAbnormalSMV);
}

BOOL Global_SetSvAbnormalData(long nGroupIndex,tmt_StateParas *pStateParas)
{
	CIecCfg92Data* pIecCfgSmvData = Global_GetSMVDataByIndex(nGroupIndex);

	if(pIecCfgSmvData == NULL)
	{
		return FALSE;
	}

	for (int nIndex = 0;nIndex<pStateParas->m_nStateNumbers;nIndex++)
	{
		pStateParas->m_paraState[nIndex].m_oAbnormalSMV.m_nGroupIndex = nGroupIndex;
		Global_SetSvAbnormalData(pIecCfgSmvData,&pStateParas->m_paraState[nIndex].m_oAbnormalSMV);
	}

	return TRUE;
}

BOOL Global_SetSvAbnormalData(CIecCfg92Data* pIecCfgSmvData,tmt_StateAbnormalSMV *pAbnormalSMV)
{
	if(pIecCfgSmvData == NULL)
	{
		return FALSE;
	}

	CString_to_char(pIecCfgSmvData->m_strDestAddress, pAbnormalSMV->m_oSmvMsg.m_strMacAddrDst);
	CString_to_char(pIecCfgSmvData->m_strSrcAddress, pAbnormalSMV->m_oSmvMsg.m_strMacAddrSrc);
	 pAbnormalSMV->m_oSmvMsg.m_nAppID = pIecCfgSmvData->m_dwAppID;
	 pAbnormalSMV->m_oSmvMsg.m_nVLanID = pIecCfgSmvData->m_dwVID;
	 pAbnormalSMV->m_oSmvMsg.m_nVLanPriority = pIecCfgSmvData->m_nPriority;
	 pAbnormalSMV->m_oSmvMsg.m_nVersion = pIecCfgSmvData->m_dwVersion;
	CString_to_char(pIecCfgSmvData->m_strSVID,  pAbnormalSMV->m_oSmvMsg.m_strSVID);
	CString_to_char(pIecCfgSmvData->m_strDataSet,  pAbnormalSMV->m_oSmvMsg.m_strDataset);
	 pAbnormalSMV->m_oSmvMsg.m_nSyn = pIecCfgSmvData->m_nSyn;
	return TRUE;
}

void Global_SetSvAbnormalTmtValues_ByIecConfig(tmt_StateAbnormalSMV *pAbnormalSMV,BOOL bJudgeMacEmpty)
{
	if (pAbnormalSMV == NULL)
	{
		return;
	}

	if (bJudgeMacEmpty &&(strlen(pAbnormalSMV->m_oSmvMsg.m_strMacAddrDst) >= 12))
	{
		return;
	}

	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	long nSelGroupIndex = 0;

	while (pos)
	{
		pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);

		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		if (pIecCfgSmvData->m_nUseFlag == 0)
		{
			continue;
		}

		if (nSelGroupIndex == pAbnormalSMV->m_nGroupIndex)
		{
			CIecCfg92Data* p92Data = (CIecCfg92Data*)pIecCfgSmvData;
			Global_SetSvAbnormalData(p92Data,pAbnormalSMV);
			break;
		}

		nSelGroupIndex++;
	}
}

CIecCfg92Data* Global_GetSMVDataByIndex(int nGroupIndex)
{
	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	long nCurrIndex = 0;

	while(pos)
	{
		pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);

		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		if (pIecCfgSmvData->m_nUseFlag == 0)
		{
			continue;
		}

		if (nCurrIndex == nGroupIndex)
		{
			CIecCfg92Data* p92Data = (CIecCfg92Data*)pIecCfgSmvData;
			return p92Data;
		}

		nCurrIndex++;
	}

	return NULL;
}

// 
// long QSttMacroParaEditViewState::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)
// {
// 	CSttItemsEmpty oItems;
// 
// 	CSttCmdDefineXmlRWKeys::SetOnlyGetItem(TRUE);
// 	CSttItems* pRoot = new CSttItems;
// 	pRoot->m_strID = GetMacroID();
// 	pRoot->m_nTkID = 65535;
// 	oItems.AddNewChild(pRoot);
// 
// 	CSttItems* pItems = new CSttItems;
// 	pItems->m_strID = GetMacroID();
// 	pItems->m_nTkID = 65535;
// 	pRoot->AddNewChild(pItems);
// 
// 	for (int i = 0; i < m_oStateTest.m_oStateParas.m_nStateNumbers; i++)
// 	{
// 		CSttItems* pChileItems = new CSttItems;
// 		pChileItems->m_strID = "state" + QString::number(i);
// 		pChileItems->m_nTkID = 65535;
// 
// 		if (g_oSttTestResourceMngr.m_pTestResouce)
// 		{
// 			//更新当前电压电流通道
// 			POS pos = g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetHeadPosition();
// 			while (pos)
// 			{
// 				CExBaseList* pChild = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetNext(pos);
// 				CSttItemBase* pMacroTest = new CSttItemBase;
// 				pMacroTest->m_strID = pChild->m_strID;
// 				pMacroTest->m_nTkID = 65535;
// 				pChileItems->AddNewChild(pMacroTest);
// 			}
// 
// 			pos = g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetHeadPosition();
// 			while (pos)
// 			{
// 				CExBaseList* pChild = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetNext(pos);
// 				CSttItemBase* pMacroTest = new CSttItemBase;
// 				pMacroTest->m_strID = pChild->m_strID;
// 				pMacroTest->m_nTkID = 65535;
// 				pChileItems->AddNewChild(pMacroTest);
// 			}
// 		}
// 
// 		pItems->AddNewChild(pChileItems);
// 	}
// 
// 	long nLen = oItems.GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, ppszItemsXml, 0, _JSON_TYPE_);
// 
// 	CSttCmdDefineXmlRWKeys::SetOnlyGetItem(FALSE);
// 
// 	oItems.DeleteAll();
// 	oItems.RemoveAll();
// 
// 	return nLen;
// }

