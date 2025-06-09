#include "QSttMUTimeTestWidget.h"
#include "../../../../Module/OSInterface/OSInterface.h"
#include "../../../../Module/SmartCap/X61850CapBase.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../Module/CommonMethod/commonMethod.h"
#include <QPixmap>
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckBox.h"
#include "../SttTestCntrCmdDefine.h"
#include "../../../Module/XLangResource_Native.h"

#ifndef NOT_USE_ASSIST
#include "../../Assist/DynEffect/SttAssistWndDynEffExecTool.h"
#endif

#include <QDesktopWidget>
#include <QApplication>

QSttMUTimeTestWidget::QSttMUTimeTestWidget(BOOL *pbTmtParaChanged,QWidget *parent)
	: QWidget(parent)
{
	m_pbTmtParaChanged = pbTmtParaChanged;
	m_pManualParas = NULL;
	m_pManualTest = NULL;
	m_pMuTimeRlt = NULL;
//	setFocusPolicy(Qt::NoFocus);//为
	InitUI();
}

QSttMUTimeTestWidget::~QSttMUTimeTestWidget()
{

}

void QSttMUTimeTestWidget::InitUI()
{
	CString strTemp;
	/////////////////////////////////////////左侧-第一行：PPS设置//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//strTemp = "上升沿有效";
	m_pRisingEdgeRadio = new QRadioButton(g_sLangTxt_State_Risingedgeeffective);//上升沿有效 lcq 3.13
	//strTemp = "下降沿有效";
	m_pFallingEdgeRadio = new QRadioButton(g_sLangTxt_State_Downedgeeffective);//下降沿有效 lcq 3.13
	//strTemp = "无PPS";
	m_pNoPPSEdgeRadio = new QRadioButton(g_sLangTxt_State_NOPPS);//无PPS lcq 3.13
	m_pRisingEdgeRadio->setFont(*g_pSttGlobalFont);
	m_pFallingEdgeRadio->setFont(*g_pSttGlobalFont);
	m_pNoPPSEdgeRadio->setFont(*g_pSttGlobalFont);
	m_pPPS_SetVBoxLayout = new QVBoxLayout;
	m_pPPS_ChildHBoxLayout = new QHBoxLayout;
	m_pPPS_ChildHBoxLayout->addWidget(m_pRisingEdgeRadio);
	m_pPPS_ChildHBoxLayout->addWidget(m_pFallingEdgeRadio);
	m_pPPS_ChildHBoxLayout->addWidget(m_pNoPPSEdgeRadio);

//	m_pDelayComp_ChildHBoxLayout = new QHBoxLayout;
	//strTemp = "无PPS延时补偿(μs)";
// 	m_pDelayComp_Label = new QLabel(g_sLangTxt_State_UsNoPPSdelaycompensation);  //无PPS延时补偿(μs) lcq 3.13
// 	m_pDelayComp_FloatLineEdit = new QFloatLineEdit;
// 
// 	m_pDelayComp_ChildHBoxLayout->addWidget(m_pDelayComp_Label);
// 	m_pDelayComp_ChildHBoxLayout->addWidget(m_pDelayComp_FloatLineEdit);
// 	m_pDelayComp_FloatLineEdit->setFixedWidth(150);
// 	m_pDelayComp_ChildHBoxLayout->addStretch();

	m_pPPS_SetVBoxLayout->addLayout(m_pPPS_ChildHBoxLayout);
//	m_pPPS_SetVBoxLayout->addLayout(m_pDelayComp_ChildHBoxLayout);
	//strTemp = "PPS设置";
	m_pPPS_SetGroupBox = new QSttGroupBox(g_sLangTxt_State_PPSsettings);//PPS设置 lcq 3.13
	m_pPPS_SetGroupBox->setLayout(m_pPPS_SetVBoxLayout);
//	m_pDelayComp_FloatLineEdit->setFont(*g_pSttGlobalFont);
	m_pPPS_SetGroupBox->setFont(*g_pSttGlobalFont);

	/////////////////////////////////////////左侧-第二行：开出设置//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pOutSetGridLayout = new QGridLayout;
	CString strOutDesc;
	xlang_GetLangStrByFile(strOutDesc, "Native_BoutX");

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		strTemp = strOutDesc;
		strTemp.AppendFormat("%d",nIndex+1);
		m_pOutCheckBox[nIndex] = new QSttCheckBox(strTemp);
		m_pOutSetGridLayout->addWidget(m_pOutCheckBox[nIndex], nIndex/5, nIndex%5, 1, 1);
	}

	//strTemp = "开出设置";
	m_pOutSetGroupBox = new QSttGroupBox(g_sLangTxt_Manual_OutSetting);//开出设置 lcq 3.13
	m_pOutSetGroupBox->setFont(*g_pSttGlobalFont);
	m_pOutSetGroupBox->setLayout(m_pOutSetGridLayout);

	/////////////////////////////////////////第三行：测试结果设置//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//strTemp = "同步时长(s):";
	m_pTimeLong_Label = new QLabel(g_sLangTxt_State_SSyncduration);//同步时长(s): lcq 3.13
	m_pTimeLong_Label->setFont(*g_pSttGlobalFont);
	m_pTimeLong_FloatLineEdit = new QFloatLineEdit;
	//strTemp = "当前误差(μs):";
	m_pCurrError_Label = new QLabel(g_sLangTxt_State_UsCurrenterror);//当前误差(μs): lcq 3.13
	m_pCurrError_Label->setFont(*g_pSttGlobalFont);
	m_pCurrError_FloatLineEdit = new QFloatLineEdit;
	//strTemp = "最大误差(μs):";
	m_pMaxError_Label = new QLabel(g_sLangTxt_State_UsMaximumerror);//最大误差(μs): lcq 3.13
	m_pMaxError_Label->setFont(*g_pSttGlobalFont);
	m_pMaxError_FloatLineEdit = new QFloatLineEdit;
	//strTemp = "最小误差(μs):";
	m_pMinError_Label = new QLabel(g_sLangTxt_State_UsMinimumerror);//最小误差(μs): lcq 3.13
	m_pMinError_Label->setFont(*g_pSttGlobalFont);

	m_pMinError_FloatLineEdit = new QFloatLineEdit;
	m_pTestResultsGridLayout = new QGridLayout;

	m_pTimeLong_FloatLineEdit->setReadOnly(true);
	m_pCurrError_FloatLineEdit->setReadOnly(true);
	m_pMaxError_FloatLineEdit->setReadOnly(true);
	m_pMinError_FloatLineEdit->setReadOnly(true);

	m_pTimeLong_FloatLineEdit->setFocusPolicy(Qt::NoFocus);
	m_pCurrError_FloatLineEdit->setFocusPolicy(Qt::NoFocus);
	m_pMaxError_FloatLineEdit->setFocusPolicy(Qt::NoFocus);
	m_pMinError_FloatLineEdit->setFocusPolicy(Qt::NoFocus);

	m_pTimeLong_FloatLineEdit->setText("--");
	m_pCurrError_FloatLineEdit->setText("--");
	m_pMaxError_FloatLineEdit->setText("--");
	m_pMinError_FloatLineEdit->setText("--");

	m_pTimeLong_FloatLineEdit->setAlignment(Qt::AlignHCenter);
	m_pCurrError_FloatLineEdit->setAlignment(Qt::AlignHCenter);
	m_pMaxError_FloatLineEdit->setAlignment(Qt::AlignHCenter);
	m_pMinError_FloatLineEdit->setAlignment(Qt::AlignHCenter);

	m_pTestResultsGridLayout->addWidget(m_pTimeLong_Label, 0, 0, 1, 1);
	m_pTestResultsGridLayout->addWidget(m_pTimeLong_FloatLineEdit, 0, 1, 1, 1);
	m_pTestResultsGridLayout->addWidget(m_pCurrError_Label, 0, 2, 1, 1);
	m_pTestResultsGridLayout->addWidget(m_pCurrError_FloatLineEdit, 0, 3, 1, 1);

	m_pTestResultsGridLayout->addWidget(m_pMaxError_Label, 1, 0, 1, 1);
	m_pTestResultsGridLayout->addWidget(m_pMaxError_FloatLineEdit, 1, 1, 1, 1);
	m_pTestResultsGridLayout->addWidget(m_pMinError_Label, 1, 2, 1, 1);
	m_pTestResultsGridLayout->addWidget(m_pMinError_FloatLineEdit, 1, 3, 1, 1);

	//strTemp = "测试结果";
	m_pTestResultsGroupBox = new QSttGroupBox(g_sLangTxt_Gradient_TestResult); //测试结果 lcq 3.13
	m_pTestResultsGroupBox->setLayout(m_pTestResultsGridLayout);

	m_pStdSting_Label = new QLabel(this);
	m_pStdSting_Label->setWordWrap(true);

	//2022-10-24 sy 采用g_pSttGlobalFont
// 	QFont font = this->font();
// 	font.setPointSize(16);
// 	m_pStdSting_Label->setFont(font);
	m_pStdSting_Label->setFont(*g_pSttGlobalFont);
	//strTemp = "备注:";
	m_pStdSting_Label->setText(g_sLangTxt_State_Remark); //备注 lcq 3.13


	m_pLeftVBoxLayout = new QVBoxLayout;
	m_pLeftVBoxLayout->addWidget(m_pPPS_SetGroupBox);
	m_pLeftVBoxLayout->addWidget(m_pOutSetGroupBox);
	m_pLeftVBoxLayout->addWidget(m_pTestResultsGroupBox);
	m_pLeftVBoxLayout->addWidget(m_pStdSting_Label);

	strTemp = "";
	m_pRightPic_Label = new QLabel(strTemp);
	m_pRightPic_Label->setFixedWidth(400);
	m_pRightPic_Label->setAlignment(Qt::AlignCenter);

// 	QPixmap pixmap = QIcon(strTemp).pixmap(QSize(110, 110));
// 	QIcon tempIcon = QIcon(pixmap.scaled(m_pRightPic_Label->width(), m_pRightPic_Label->height()));
// 	m_pRightPic_Label->setIcon(tempIcon);

	m_pMainHBoxLayout = new QHBoxLayout(this);
	m_pMainHBoxLayout->addLayout(m_pLeftVBoxLayout);
	m_pMainHBoxLayout->addWidget(m_pRightPic_Label);
	setLayout(m_pMainHBoxLayout);

#ifdef _PSX_QT_WINDOWS_
	//20230712 suyang 适配6.4合并单元分辨率 1024X768
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前屏幕宽度(%ld),高度(%ld)."),
// 		rect.width(),rect.height());

	if(rect.width() <= 1366)//2040225 suyang 在6.4分辨率1366*768下 图片显示不全
	{
		 SetWinMuTestFont_1024_768();
	}
#endif	
}

//20230724 suyang add
void QSttMUTimeTestWidget::SetWinMuTestFont_1024_768()
{
 	m_pRightPic_Label->setFixedWidth(230);
	m_pRightPic_Label->setFixedHeight(230);
	
	QFont oFont;
	oFont.setPixelSize(12);
	m_pRisingEdgeRadio->setFont(oFont);
	m_pFallingEdgeRadio->setFont(oFont);
	m_pNoPPSEdgeRadio->setFont(oFont);
//	m_pDelayComp_FloatLineEdit->setFont(oFont);
	m_pPPS_SetGroupBox->setFont(oFont);
	m_pOutSetGroupBox->setFont(oFont);
	m_pTimeLong_Label->setFont(oFont);
	m_pCurrError_Label->setFont(oFont);
	m_pMaxError_Label->setFont(oFont);

	m_pMinError_Label->setFont(oFont);

	m_pTimeLong_FloatLineEdit->setFont(oFont);
	m_pCurrError_FloatLineEdit->setFont(oFont);
	m_pMaxError_FloatLineEdit->setFont(oFont);
	m_pMinError_FloatLineEdit->setFont(oFont);
	m_pTestResultsGroupBox->setFont(oFont);
	m_pStdSting_Label->setFont(oFont);


	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setFont(oFont);
	}
}

void QSttMUTimeTestWidget::UpdateUI()
{
	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setVisible(g_nBoutCount>nIndex);
	}

	UpdateResultsDesc();
}

void QSttMUTimeTestWidget::InitData(tmt_manual_test *pManualTest)
{
	if (pManualTest == NULL)
	{
		return;
	}

	CString strTemp;
	m_pManualTest = pManualTest;
	m_pManualParas = &pManualTest->m_oManuParas;
	m_pMuTimeRlt = &pManualTest->m_oManuResult.m_oMuTimeRlt;

	//20230712 suyang 适配6.4合并单元分辨率 1024X768
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	

	if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUTimingAccur)
	{
		m_strRightPicName = "MUTimingAccur.png";

#ifdef _PSX_QT_WINDOWS_
		if (rect.width() <= 1366)//2040223 suyang 在6.4分辨率1366*768下 图片显示不全
		{
			m_strRightPicName = "MUTimingAccur_Small.png";
		}
#endif
		strTemp =  g_sLangTxt_Gradient_NoteThepthanoneus; //备注:规程要求测试时间1分钟，最大对时误差不大于1μs.lcq 3.21
		//xlang_GetLangStrByFile(strTemp,"Gradient_NoteTheprooneminutemaximumtimingErrorisnotmorethanoneus"); //lcq 3.13

	} 
	else
	{
		m_strRightPicName = "MUPunctAccur.png";

#ifdef _PSX_QT_WINDOWS_
		if (rect.width() <= 1366)//2040223 suyang 在6.4分辨率1366*768下 图片显示不全
		{
			m_strRightPicName = "MUPunctAccur_Small.png";
		}
#endif
		strTemp = g_sLangTxt_Gradient_NoteThepthanfourus; //备注:规程要求测试时间10分钟，最大守时误差不大于4μs. //lcq 3.21
		//xlang_GetLangStrByFile(strTemp,"Gradient_NoteTheprooneminutemaximumtimingErrorisnotmorethanoneus"); //lcq 3.13
	}

	SetRightPicLabel(m_strRightPicName);
	m_pStdSting_Label->setText(strTemp);
	DisConnectAllSigSlot();
	m_pRisingEdgeRadio->setChecked(m_pManualParas->m_oMuParas.nPPS_SetType == 0);
	m_pFallingEdgeRadio->setChecked(m_pManualParas->m_oMuParas.nPPS_SetType == 1);
	m_pNoPPSEdgeRadio->setChecked(m_pManualParas->m_oMuParas.nPPS_SetType == 2);

// 	if (m_pManualParas->m_oMuParas.nPPS_SetType == 2)
// 	{
// 		m_pDelayComp_Label->setEnabled(true);
// 		m_pDelayComp_FloatLineEdit->setEnabled(true);
// 	} 
// 	else
// 	{
// 		m_pDelayComp_Label->setEnabled(false);
// 		m_pDelayComp_FloatLineEdit->setEnabled(false);
// 	}

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setChecked(m_pManualParas->m_binOut[nIndex].nState);
		m_pOutCheckBox[nIndex]->setVisible(g_nBoutCount>nIndex);
	}

//	m_pDelayComp_FloatLineEdit->InitCoverage(-1000,1000,3);
//	m_pDelayComp_FloatLineEdit->SetValue(&m_pManualParas->m_oMuParas.fDelayCompens_NoPPS);

	UpdateResultsDesc();
	ConnectAllSigSlot();

	if (m_pManualParas->m_oMuParas.nPPS_SetType == 2)
	{
		m_oAssistTimer.start(500);

	}
}

void QSttMUTimeTestWidget::SetRightPicLabel(const CString &strPicName)
{
	CString strTemp;
#ifdef _PSX_QT_WINDOWS_
	strTemp = _P_GetResourcePath();
#else
    strTemp = ":/ctrls/images/";
#endif
	strTemp += strPicName;
	QImage oPicMuTime(strTemp);
	oPicMuTime = oPicMuTime.scaled(m_pRightPic_Label->width(), m_pRightPic_Label->height());
	m_pRightPic_Label->setPixmap(QPixmap::fromImage(oPicMuTime));
}

void QSttMUTimeTestWidget::UpdateResultsDesc()
{
	if (m_pManualParas == NULL)
	{
		return;
	}

	CString strDesc;

	if (m_pManualParas->m_nFuncType  == TMT_MANU_FUNC_TYPE_MUTimingAccur)
	{
		strDesc = "同步时长(s):";
        xlang_GetLangStrByFile(strDesc,"State_SSyncduration"); //lcq 3.13
	} 
	else if (m_pManualParas->m_nFuncType  == TMT_MANU_FUNC_TYPE_MUPunctAccur)
	{
		strDesc = "守时时长(s):";
		xlang_GetLangStrByFile(strDesc,"State_SPunctuality");  //lcq 3.13
	} 

	if (!strDesc.IsEmpty())
	{
		m_pTimeLong_Label->setText(strDesc);
	}
}

void QSttMUTimeTestWidget::ConnectAllSigSlot()
{
	connect(m_pRisingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	connect(m_pFallingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	connect(m_pNoPPSEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
//	connect(m_pDelayComp_FloatLineEdit, SIGNAL(clicked()), this, SLOT(slot_OnDelayCompEditChanged()));

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		connect(m_pOutCheckBox[nIndex], SIGNAL(clicked()), this, SLOT(slot_OnOutCheckChanged()));
	}

	connect(&m_oAssistTimer,SIGNAL(timeout()),this,SLOT(slot_AssistTimer()));
	connect(&m_oResultUpdateTimer,SIGNAL(timeout()),this,SLOT(slot_ResultUpdateTimer()));
}

void QSttMUTimeTestWidget::DisConnectAllSigSlot()
{
	disconnect(m_pRisingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	disconnect(m_pFallingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	disconnect(m_pNoPPSEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
//	disconnect(m_pDelayComp_FloatLineEdit, SIGNAL(clicked()), this, SLOT(slot_OnDelayCompEditChanged()));

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		disconnect(m_pOutCheckBox[nIndex], SIGNAL(clicked()), this, SLOT(slot_OnOutCheckChanged()));
	}

	disconnect(&m_oAssistTimer,SIGNAL(timeout()),this,SLOT(slot_AssistTimer()));
	disconnect(&m_oResultUpdateTimer,SIGNAL(timeout()),this,SLOT(slot_ResultUpdateTimer()));
}

void QSttMUTimeTestWidget::slot_AssistTimer()
{
#ifdef NOT_USE_ASSIST
	m_oAssistTimer.stop();
#else	
	if (m_pManualParas->m_oMuParas.nPPS_SetType != 2)
	{
		m_oAssistTimer.stop();
	}

	else if (g_theAssistWndDynEffExecTool != NULL)//在初始化参数后,增加助手提示信息,防止助手还未创建,在此处增加判断
	{
		g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IecCap,"","",20000);
		//g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,_T("无PPS模式下,需要先进行报文探测,选择对应采样值控制块."),20000);
	    g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,g_sLangTxt_Gradient_InPPSfreemodevaluecontrolblock.GetString(),20000); //无PPS模式下,需要先进行报文探测,选择对应采样值控制块.lcq 3.13
		m_oAssistTimer.stop();
	}
#endif 	
}

void QSttMUTimeTestWidget::slot_ResultUpdateTimer()
{
#ifdef use_CSmartCapCtrl
    CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

	if (pXSttCap_61850 == NULL)
	{
		return;
	}

	if (pXSttCap_61850->m_pDataset_MUTimeRlt == NULL)
	{
		return;
	}

	CDvmDataset *pTimeRltDataset = pXSttCap_61850->m_pDataset_MUTimeRlt;
	CDvmData *pHasUsingTime = (CDvmData*)pTimeRltDataset->FindByID(STT_MUTEST_HasUsingTime);
	CDvmData *pMaxErrTime = (CDvmData*)pTimeRltDataset->FindByID(STT_MUTEST_MaxErrTime);
	CDvmData *pMinErrTime = (CDvmData*)pTimeRltDataset->FindByID(STT_MUTEST_MinErrTime);
	CDvmData *pCurrErrTime = (CDvmData*)pTimeRltDataset->FindByID(STT_MUTEST_CurrErrTime);
	CDvmData *pAverageErrTime = (CDvmData*)pTimeRltDataset->FindByID(STT_MUTEST_AverageErrTime);
	CDvmData *pMUTimeResult = (CDvmData*)pTimeRltDataset->FindByID(STT_MUTEST_MUTimeResult);

	if((pHasUsingTime == NULL)||(pMaxErrTime == NULL)||(pMinErrTime == NULL)
		||(pCurrErrTime == NULL)||(pAverageErrTime == NULL)||(pMUTimeResult == NULL))
		return;

	m_pMuTimeRlt->m_fCurrErrTime = CString_To_double(pCurrErrTime->m_strValue);
	m_pMuTimeRlt->m_fMaxErrTime = CString_To_double(pMaxErrTime->m_strValue);
	m_pMuTimeRlt->m_fMinErrTime = CString_To_double(pMinErrTime->m_strValue);
	m_pMuTimeRlt->m_fAverageErrTime = CString_To_double(pAverageErrTime->m_strValue);
	m_pMuTimeRlt->m_fHasUsingTime = CString_To_long(pHasUsingTime->m_strValue);

	if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUTimingAccur)
	{
		m_pMuTimeRlt->m_nTimeTestResult = ((fabs(m_pMuTimeRlt->m_fMinErrTime)<1.0f)&&(fabs(m_pMuTimeRlt->m_fMaxErrTime)<1.0f));
	} 
	else
	{
		m_pMuTimeRlt->m_nTimeTestResult = ((fabs(m_pMuTimeRlt->m_fMinErrTime)<4.0f)&&(fabs(m_pMuTimeRlt->m_fMaxErrTime)<4.0f));
	}

	pMUTimeResult->m_strValue.Format(_T("%ld"),m_pMuTimeRlt->m_nTimeTestResult);
	m_pCurrError_FloatLineEdit->setText(pCurrErrTime->m_strValue);
	m_pMaxError_FloatLineEdit->setText(pMaxErrTime->m_strValue);
	m_pMinError_FloatLineEdit->setText(pMinErrTime->m_strValue);
	m_pTimeLong_FloatLineEdit->setText(pHasUsingTime->m_strValue);
#endif
}

void QSttMUTimeTestWidget::slot_OnDelayCompEditChanged()
{
// 	CString strValue;
// 	float fValue = m_pDelayComp_FloatLineEdit->GetValue();
// 	strValue.Format("%.03f",fValue);
// 
// 	GetWidgetBoard_DigitData(4,strValue,m_pDelayComp_FloatLineEdit,this);
// 	fValue = CString_To_double(strValue);
// 	m_pDelayComp_FloatLineEdit->SetValue(fValue);
// 	m_pDelayComp_FloatLineEdit->SetEditFinished();

// 	m_pManualParas->m_oMuParas.fDelayCompens_NoPPS = fValue;
	*m_pbTmtParaChanged = TRUE;
}

void QSttMUTimeTestWidget::slot_OnPPSSetRadioChanged(bool bValue)
{
	if (!bValue)
	{
		return;
	}

	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());

	if (pRadioBtn == m_pRisingEdgeRadio)
	{
		m_pManualParas->m_oMuParas.nPPS_SetType = 0;
	}
	else if (pRadioBtn == m_pFallingEdgeRadio)
	{
		m_pManualParas->m_oMuParas.nPPS_SetType = 1;
	}
	else if (pRadioBtn == m_pNoPPSEdgeRadio)
	{
		m_pManualParas->m_oMuParas.nPPS_SetType = 2;
#ifndef NOT_USE_ASSIST
		g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IecCap,"","",20000);
		//g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,_T("无PPS模式下,需要先进行报文探测,选择对应采样值控制块."),20000);
		g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,g_sLangTxt_Gradient_InPPSfreemodevaluecontrolblock.GetString(),20000); //无PPS模式下,需要先进行报文探测,选择对应采样值控制块.lcq 3.13
#endif
	}

// 	if (m_pManualParas->m_oMuParas.nPPS_SetType == 2)
// 	{
// 		m_pDelayComp_Label->setEnabled(true);
// 		m_pDelayComp_FloatLineEdit->setEnabled(true);
// 	} 
// 	else
// 	{
// 		m_pDelayComp_Label->setEnabled(false);
// 		m_pDelayComp_FloatLineEdit->setEnabled(false);
// 	}

	*m_pbTmtParaChanged = TRUE;
	emit sig_updataParas();
}

void QSttMUTimeTestWidget::slot_OnOutCheckChanged()
{
	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender());

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		if (pCheckBox == m_pOutCheckBox[nIndex])
		{
			m_pManualParas->m_binOut[nIndex].nState = pCheckBox->isChecked();
			*m_pbTmtParaChanged = TRUE;
			emit sig_updataParas();
			break;
		}
	}
}

void QSttMUTimeTestWidget::ShowReport(CDvmValues *pValues)
{
	if (m_pMuTimeRlt == NULL)
	{
		return;
	}

	CDvmValue* pTimeLongValueData = (CDvmValue*)pValues->FindByID("MuTime$HasUsingTime");
	CDvmValue* pCurrTimeData = (CDvmValue*)pValues->FindByID("MuTime$CurrErrTime");
	CDvmValue* pMaxTimeData = (CDvmValue*)pValues->FindByID("MuTime$MaxErrTime");
	CDvmValue* pMinTimeData = (CDvmValue*)pValues->FindByID("MuTime$MinErrTime");
	CDvmValue* pAverageTimeData = (CDvmValue*)pValues->FindByID("MuTime$AverageErrTime");
//	float fValue = 0;

	if (pTimeLongValueData != NULL)
	{
		m_pMuTimeRlt->m_fHasUsingTime = CString_To_double(pTimeLongValueData->m_strValue);
		m_pTimeLong_FloatLineEdit->SetValue(m_pMuTimeRlt->m_fHasUsingTime);
	}

	if (pCurrTimeData != NULL)
	{
		m_pMuTimeRlt->m_fCurrErrTime = CString_To_double(pCurrTimeData->m_strValue);
		m_pCurrError_FloatLineEdit->SetValue(m_pMuTimeRlt->m_fCurrErrTime);
	}

	if (pMaxTimeData != NULL)
	{
		m_pMuTimeRlt->m_fMaxErrTime = CString_To_double(pMaxTimeData->m_strValue);
		m_pMaxError_FloatLineEdit->SetValue(m_pMuTimeRlt->m_fMaxErrTime);
	}

	if (pMinTimeData != NULL)
	{
		m_pMuTimeRlt->m_fMinErrTime = CString_To_double(pMinTimeData->m_strValue);
		m_pMinError_FloatLineEdit->SetValue(m_pMuTimeRlt->m_fMinErrTime);
	}

	if (pAverageTimeData != NULL)
	{
		m_pMuTimeRlt->m_fAverageErrTime = CString_To_double(pAverageTimeData->m_strValue);
	}
}

void QSttMUTimeTestWidget::TestStartInit()
{
	ClearResults();
	m_pRisingEdgeRadio->setEnabled(false);
	m_pFallingEdgeRadio->setEnabled(false);
	m_pNoPPSEdgeRadio->setEnabled(false);
	m_oResultUpdateTimer.stop();
	m_oResultUpdateTimer.start(500);
//	EnableEditCtrls(FALSE);
//	setEnabled(false);

// 	if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUPunctAccur)
// 	{
// 		m_strRightPicName = "MUTimingAccur.png";
// 		SetRightPicLabel(m_strRightPicName);
// 	}
}

void QSttMUTimeTestWidget::EnableEditCtrls(BOOL bEnable)
{
	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setEnabled(bEnable);
	}

	m_pRisingEdgeRadio->setEnabled(bEnable);
	m_pFallingEdgeRadio->setEnabled(bEnable);
	m_pNoPPSEdgeRadio->setEnabled(bEnable);
// 	m_pDelayComp_FloatLineEdit->setEnabled(bEnable);
// 
// 	if (bEnable && (m_pManualParas->m_oMuParas.nPPS_SetType == 2))
// 	{
// 		m_pDelayComp_FloatLineEdit->setEnabled(bEnable);
// 	}
// 	else
// 	{
// 		m_pDelayComp_FloatLineEdit->setEnabled(false);
// 	}
}

void QSttMUTimeTestWidget::TestStopInit()
{
//	setEnabled(true);
	m_pRisingEdgeRadio->setEnabled(true);
	m_pFallingEdgeRadio->setEnabled(true);
	m_pNoPPSEdgeRadio->setEnabled(true);
	m_oResultUpdateTimer.stop();
//	EnableEditCtrls(TRUE);

// 	if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUPunctAccur)
// 	{
// 		m_strRightPicName = "MUTimingAccur.png";
// 		SetRightPicLabel(m_strRightPicName);
// 	}
}

void QSttMUTimeTestWidget::ClearResults()
{
	m_pTimeLong_FloatLineEdit->setText("--");
	m_pCurrError_FloatLineEdit->setText("--");
	m_pMaxError_FloatLineEdit->setText("--");
	m_pMinError_FloatLineEdit->setText("--");
}

void QSttMUTimeTestWidget::UpdateMUTimeAccurRlt(CDataGroup *pRtSycTime)
{
	if ((pRtSycTime == NULL)||(m_pManualParas == NULL))
	{
		return;
	}

	if (m_pManualParas->m_oMuParas.nPPS_SetType == 2)
	{
		return;
	}

	CDvmData *pPpsIndexData = (CDvmData*)pRtSycTime->FindByID("PPSIndex");
	CDvmData *pPpsValueData = (CDvmData*)pRtSycTime->FindByID("PPSValue");

	if ((pPpsIndexData == NULL)||(pPpsValueData == NULL))
	{
		return;
	}

	long nPpsIndex = CString_To_long(pPpsIndexData->m_strValue);
	m_pMuTimeRlt->m_fHasUsingTime/*double dTimeLong*/ = nPpsIndex + 1;

// 	if ((m_pMuTimeRlt->m_fHasUsingTime<1.5)&&(m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUPunctAccur))
// 	{
// 		m_strRightPicName = "MUPunctAccur.png";
// 		SetRightPicLabel(m_strRightPicName);
// 	}

	m_pMuTimeRlt->m_fCurrErrTime = CString_To_double(pPpsValueData->m_strValue)/1000;
	CString strTempValue,strCurrErrorValue;
	strTempValue.Format("%.03lf",m_pMuTimeRlt->m_fHasUsingTime);
	m_pTimeLong_FloatLineEdit->setText(strTempValue);
	strTempValue = m_pCurrError_FloatLineEdit->text();
	strCurrErrorValue.Format("%.03lf",m_pMuTimeRlt->m_fCurrErrTime);
	m_pCurrError_FloatLineEdit->setText(strCurrErrorValue);

	if (strTempValue.IsEmpty() || (strTempValue == "--"))
	{
		m_pMuTimeRlt->m_fMaxErrTime = m_pMuTimeRlt->m_fCurrErrTime;
		m_pMuTimeRlt->m_fMinErrTime = m_pMuTimeRlt->m_fCurrErrTime;
		m_pMuTimeRlt->m_fAverageErrTime = m_pMuTimeRlt->m_fCurrErrTime;
		m_pMaxError_FloatLineEdit->setText(strCurrErrorValue);
		m_pMinError_FloatLineEdit->setText(strCurrErrorValue);
	} 
	else
	{
// 		double dMaxErrorValue = m_pMaxError_FloatLineEdit->text().toDouble();
// 		double dMinErrorValue = m_pMinError_FloatLineEdit->text().toDouble();

		if (m_pMuTimeRlt->m_fMaxErrTime<m_pMuTimeRlt->m_fCurrErrTime)
		{
			m_pMuTimeRlt->m_fMaxErrTime = m_pMuTimeRlt->m_fCurrErrTime;
			m_pCurrError_FloatLineEdit->setText(strCurrErrorValue);
		}

		if (m_pMuTimeRlt->m_fMinErrTime>m_pMuTimeRlt->m_fCurrErrTime)
		{
			m_pMuTimeRlt->m_fMinErrTime = m_pMuTimeRlt->m_fCurrErrTime;
			m_pCurrError_FloatLineEdit->setText(strCurrErrorValue);
		}

		m_pMuTimeRlt->m_fAverageErrTime = (m_pMuTimeRlt->m_fAverageErrTime*nPpsIndex + m_pMuTimeRlt->m_fCurrErrTime)/(nPpsIndex+1);
	}

	if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUTimingAccur)
	{
		m_pMuTimeRlt->m_nTimeTestResult = ((fabs(m_pMuTimeRlt->m_fMinErrTime)<1.0f)&&(fabs(m_pMuTimeRlt->m_fMaxErrTime)<1.0f));
	} 
	else
	{
		m_pMuTimeRlt->m_nTimeTestResult = ((fabs(m_pMuTimeRlt->m_fMinErrTime)<4.0f)&&(fabs(m_pMuTimeRlt->m_fMaxErrTime)<4.0f));
	}
}
