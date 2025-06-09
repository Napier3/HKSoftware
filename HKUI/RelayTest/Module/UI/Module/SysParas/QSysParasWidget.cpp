#include "QSysParasWidget.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../../Module/SttSystemConfig/SttSystemConfig.h"
#include <QButtonGroup>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSysParasWidget::QSysParasWidget(QWidget *parent)
	: QWidget(parent)
{
//	m_nCurModuleNum = 0;
	m_pSysParas = NULL;
	m_pOverLoadDelay_Label = NULL;
	m_pOverLoadDelay_LineEdit = NULL;
}

QSysParasWidget::~QSysParasWidget()
{
	ReleaseUI();
}

void QSysParasWidget::initUI(STT_SystemParas *pSysParas)
{
	ReleaseUI();
	CString strTemp;

	CSttDevConfig* pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();
	m_pSysParas = pSysParas;
	m_pTotal_VBoxLayout = new QVBoxLayout(this);//整个系统参数设置

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pOutputSel_GroupBox = new QGroupBox(this);//第一行所有控件，放入该Group下
	xlang_GetLangStrByFile(strTemp,"ChMaps_OutputSel");//输出类型选择
	m_pOutputSel_GroupBox->setTitle(strTemp);
	m_pOutputSel_HBoxLayout = new QHBoxLayout(m_pOutputSel_GroupBox);//在Group内部增加表格布局，表格布局中包含第一行全部控件

	m_pAnalogSel_CheckBox = new QCheckBox(m_pOutputSel_GroupBox);
	xlang_GetLangStrByFile(strTemp,"ChMaps_Analog");//模拟
	m_pAnalogSel_CheckBox->setText(strTemp);
	m_pOutputSel_HBoxLayout->addWidget(m_pAnalogSel_CheckBox);

	m_pOutputSel_HBoxLayout->addSpacing(20);

	m_pDigitalSel_CheckBox = new QCheckBox(m_pOutputSel_GroupBox);
	xlang_GetLangStrByFile(strTemp,"ChMaps_Digital");//数字
	m_pDigitalSel_CheckBox->setText(strTemp);
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalSel_CheckBox);

	m_pOutputSel_HBoxLayout->addSpacing(20);

	m_pWeakSel_CheckBox = new QCheckBox(m_pOutputSel_GroupBox);
	xlang_GetLangStrByFile(strTemp,"ChMaps_Week");//弱信号
	m_pWeakSel_CheckBox->setText(strTemp);
	m_pOutputSel_HBoxLayout->addWidget(m_pWeakSel_CheckBox);

	m_pOutputSel_HBoxLayout->addStretch();

	m_pDigitalType_Label = new QLabel(m_pOutputSel_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sSystemPara");//数字报文类型
	m_pDigitalType_Label->setText(strTemp + _T(":"));
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalType_Label);

	m_pDigitalType_Combobox = new QComboBox(m_pOutputSel_GroupBox);
	//	m_pDigitalType_Combobox->setObjectName(QString::fromUtf8("comboBoxIset"));
// 	sizePolicy.setHeightForWidth(m_pDigitalType_Combobox->sizePolicy().hasHeightForWidth());
	// 	m_pDigitalType_Combobox->setSizePolicy(sizePolicy);
	m_pDigitalType_Combobox->insertItem(0,_T("IEC61850-9-2"));
	m_pDigitalType_Combobox->insertItem(1,_T("IEC60044-8(FT3)"));
	xlang_GetLangStrByFile(strTemp,"State_FThreeStraight");//柔直(FT3)
	m_pDigitalType_Combobox->insertItem(2,strTemp);
	// 	m_pDigitalType_Combobox->insertItem(3,tr("采集器输出(国网)"));
	// 	m_pDigitalType_Combobox->insertItem(4,tr("采集器输出(许继)"));
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalType_Combobox);
	m_pTotal_VBoxLayout->addWidget(m_pOutputSel_GroupBox);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 20240109 suayng add 采集类型选择

	m_pMeasSel_GroupBox = new QGroupBox(this);//第一行所有控件，放入该Group下
	m_pMeasSel_GroupBox->setTitle(/*tr("采集类型选择")*/g_sLangTxt_ChMaps_MeasSel);
	m_pMeasSel_HBoxLayout = new QHBoxLayout(m_pMeasSel_GroupBox);//在Group内部增加表格布局，表格布局中包含第一行全部控件

	m_pAnalogMeasSel_CheckBox = new QCheckBox(m_pMeasSel_GroupBox);
	m_pAnalogMeasSel_CheckBox->setText(/*tr("模拟")*/g_sLangTxt_ChMaps_Analog);
	m_pMeasSel_HBoxLayout->addWidget(m_pAnalogMeasSel_CheckBox);

	m_pMeasSel_HBoxLayout->addSpacing(20);

	m_pDigitalMeasSel_CheckBox = new QCheckBox(m_pMeasSel_GroupBox);
	m_pDigitalMeasSel_CheckBox->setText(/*tr("数字")*/g_sLangTxt_ChMaps_Digital);
	m_pMeasSel_HBoxLayout->addWidget(m_pDigitalMeasSel_CheckBox);

	m_pMeasSel_HBoxLayout->addSpacing(20);

// 	m_pWeakMeasSel_CheckBox = new QCheckBox(m_pMeasSel_GroupBox);
// 	m_pWeakMeasSel_CheckBox->setText(/*tr("弱信号")*/g_sLangTxt_ChMaps_Week);
// 	m_pMeasSel_HBoxLayout->addWidget(m_pWeakMeasSel_CheckBox);

	m_pMeasSel_HBoxLayout->addStretch();

	m_pDigitalMeasType_Label = new QLabel(m_pMeasSel_GroupBox);
	m_pDigitalMeasType_Label->setText(/*tr("采集报文类型:")*/g_sLangTxt_ChMaps_DigitalMeasType + _T(":"));
	m_pMeasSel_HBoxLayout->addWidget(m_pDigitalMeasType_Label);

	m_pDigitalMeasType_Combobox = new QComboBox(m_pMeasSel_GroupBox);

	m_pDigitalMeasType_Combobox->insertItem(0,tr("IEC61850-9-2"));
	m_pDigitalMeasType_Combobox->insertItem(1,tr("IEC60044-8(FT3)"));
	m_pDigitalMeasType_Combobox->insertItem(2,/*tr("柔直(FT3)")*/g_sLangTxt_State_FThreeStraight);
	m_pMeasSel_HBoxLayout->addWidget(m_pDigitalMeasType_Combobox);

	m_pAnalogMeasSel_CheckBox->setEnabled(false);
	m_pTotal_VBoxLayout->addWidget(m_pMeasSel_GroupBox);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pStdValues_GroupBox = new QGroupBox(this);//第一行所有控件，放入该Group下
	m_pTotal_VBoxLayout->addWidget(m_pStdValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_GlobalParam");//全局参数设置
	m_pStdValues_GroupBox->setTitle(strTemp);
	m_pStdValues_GridLayout = new QGridLayout(m_pStdValues_GroupBox);//在Group内部增加表格布局，表格布局中包含第一行全部控件
	m_pStdValues_GridLayout->setSpacing(10);//设置行间距

	m_pStdVol_Label = new QLabel(m_pStdValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Report_Vnom");//额定电压
	m_pStdVol_Label->setText(strTemp + _T("(V):"));
	m_pStdValues_GridLayout->addWidget(m_pStdVol_Label, 0, 0, 1, 1);

	m_pStdVol_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
	m_pStdVol_LineEdit->InitCoverage(0,1000);
	m_pStdValues_GridLayout->addWidget(m_pStdVol_LineEdit, 0, 1, 1, 1);

	m_pStdCur_Label = new QLabel(m_pStdValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Native_EDCurrent");//额定电流
	m_pStdCur_Label->setText(strTemp + _T("(A):"));
	m_pStdValues_GridLayout->addWidget(m_pStdCur_Label, 0, 2, 1, 1);

	m_pStdCur_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
	m_pStdCur_LineEdit->InitCoverage(0,100);
	m_pStdValues_GridLayout->addWidget(m_pStdCur_LineEdit, 0, 3, 1, 1);
	
	int nRow = 1;

	//chenling 2024.4.29
	if(g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{
		m_pZeroStdVol_Label = new QLabel(m_pStdValues_GroupBox);
		strTemp = _T("额定零序电压(V):");
		m_pZeroStdVol_Label->setText(strTemp);
		m_pStdValues_GridLayout->addWidget(m_pZeroStdVol_Label, nRow, 0, 1, 1);

		m_pZeroStdVol_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
		m_pZeroStdVol_LineEdit->InitCoverage(0,1000);
		m_pStdValues_GridLayout->addWidget(m_pZeroStdVol_LineEdit, nRow, 1, 1, 1);

		m_pZeroStdCur_Label = new QLabel(m_pStdValues_GroupBox);
		strTemp = _T("额定零序电流(A):");
		m_pZeroStdCur_Label->setText(strTemp);
		m_pStdValues_GridLayout->addWidget(m_pZeroStdCur_Label, nRow, 2, 1, 1);

		m_pZeroStdCur_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
		m_pZeroStdCur_LineEdit->InitCoverage(0,1000);
		m_pStdValues_GridLayout->addWidget(m_pZeroStdCur_LineEdit, nRow, 3, 1, 1);
		
		nRow ++;
	}

	m_pStdFre_Label = new QLabel(m_pStdValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Report_Fnom");//额定频率
	m_pStdFre_Label->setText(strTemp + _T("(Hz):"));
	m_pStdValues_GridLayout->addWidget(m_pStdFre_Label, nRow, 0, 1, 1);

	m_pStdFre_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
	m_pStdFre_LineEdit->InitCoverage(0,3000);
	m_pStdValues_GridLayout->addWidget(m_pStdFre_LineEdit, nRow, 1, 1, 1);

	m_pAntiShakeTime_Label = new QLabel(m_pStdValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Report_AntiShakeTime");//防抖时间
	m_pAntiShakeTime_Label->setText(strTemp + _T("(ms):"));
	m_pStdValues_GridLayout->addWidget(m_pAntiShakeTime_Label, nRow, 2, 1, 1);

	m_pAntiShakeTime_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
	m_pAntiShakeTime_LineEdit->InitCoverage(0,60000,0);
	m_pStdValues_GridLayout->addWidget(m_pAntiShakeTime_LineEdit, nRow, 3, 1, 1);


	if (pSttDevConfig->m_nOverloadDelay)
	{
		m_pOverLoadDelay_Label = new QLabel(m_pStdValues_GroupBox);
		xlang_GetLangStrByFile(strTemp,"IEC_StartDelay");//开始过载延时(s):
		m_pOverLoadDelay_Label->setText(strTemp);
		m_pStdValues_GridLayout->addWidget(m_pOverLoadDelay_Label, 2, 0, 1, 1);

		m_pOverLoadDelay_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
		m_pOverLoadDelay_LineEdit->InitCoverage(0,300);
		m_pStdValues_GridLayout->addWidget(m_pOverLoadDelay_LineEdit, 2, 1, 1, 1);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pSynSet_GroupBox = new QGroupBox(this);
	m_pTotal_VBoxLayout->addWidget(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_SyncSet");//同步设置
	m_pSynSet_GroupBox->setTitle(strTemp);
	m_pSynSet_GridLayout = new QGridLayout(m_pSynSet_GroupBox);

	m_pSecondSynSet_Label = new QLabel(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_SecSyncStatus");//秒同步状态
	m_pSecondSynSet_Label->setText(strTemp + _T(":"));
	m_pSynSet_GridLayout->addWidget(m_pSecondSynSet_Label, 0, 0, 1, 1);
	m_pSecondSynSet_ComboBox = new QComboBox(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_CloseSecSync");//关闭秒同步
	m_pSecondSynSet_ComboBox->insertItem(0,strTemp);
	xlang_GetLangStrByFile(strTemp,"Manual_OpenSecSync");//开启秒同步
	m_pSecondSynSet_ComboBox->insertItem(1,strTemp);
	m_pSynSet_GridLayout->addWidget(m_pSecondSynSet_ComboBox, 0, 1, 1, 1);
	m_pBCodeLogic_Label = new QLabel(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_BCode");//B码输出逻辑
	m_pBCodeLogic_Label->setText(strTemp + _T(":"));
	m_pSynSet_GridLayout->addWidget(m_pBCodeLogic_Label, 1, 0, 1, 1);
	m_pBCodePositiveLogic_RadioBtn = new QRadioButton(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_PositiveLogic");//正逻辑
	m_pBCodePositiveLogic_RadioBtn->setText(strTemp);
	m_pSynSet_GridLayout->addWidget(m_pBCodePositiveLogic_RadioBtn, 1, 1, 1, 1);
	m_pBCodeNegtiveLogic_RadioBtn = new QRadioButton(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_NegativeLogic");//负逻辑
	m_pBCodeNegtiveLogic_RadioBtn->setText(strTemp);
	m_pSynSet_GridLayout->addWidget(m_pBCodeNegtiveLogic_RadioBtn, 1, 2, 1, 1);

	QButtonGroup *pBCodeBtnGroup = new QButtonGroup(this);
	pBCodeBtnGroup->addButton(m_pBCodePositiveLogic_RadioBtn);
	pBCodeBtnGroup->addButton(m_pBCodeNegtiveLogic_RadioBtn);

	m_p1588Syn_Label = new QLabel(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_IEC1588Sync");//IEC1588同步机制
	m_p1588Syn_Label->setText(strTemp);
	m_pSynSet_GridLayout->addWidget(m_p1588Syn_Label, 2, 0, 1, 1);
	m_p1588PeerDelay_RadioBtn = new QRadioButton(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_PeerDelay");//对等延时
	m_p1588PeerDelay_RadioBtn->setText(strTemp);
	m_pSynSet_GridLayout->addWidget(m_p1588PeerDelay_RadioBtn, 2, 1, 1, 1);
	m_p1588ReqResp_RadioBtn = new QRadioButton(m_pSynSet_GroupBox);
	xlang_GetLangStrByFile(strTemp,"Manual_DelayRequestReply");//延时请求-响应
	m_p1588ReqResp_RadioBtn->setText(strTemp);
	m_pSynSet_GridLayout->addWidget(m_p1588ReqResp_RadioBtn, 2, 2, 1, 1);

	QButtonGroup *p1588BtnGroup = new QButtonGroup(this);
	p1588BtnGroup->addButton(m_p1588PeerDelay_RadioBtn);
	p1588BtnGroup->addButton(m_p1588ReqResp_RadioBtn);

	//20240910 wanmj 系统参数误差部分去掉
#if 0
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pSetErrorValues_GroupBox = new QGroupBox(this);
	m_pTotal_VBoxLayout->addWidget(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sSystemPara");//误差值设置
	m_pSetErrorValues_GroupBox->setTitle(strTemp);
	m_pSetErrorValues_GridLayout = new QGridLayout(m_pSetErrorValues_GroupBox);

	m_pCurAbsError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sCurAbsError");//电流动作值绝对误差(A):
	m_pCurAbsError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pCurAbsError_Label, 0, 0, 1, 1);

	m_pCurAbsError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pCurAbsError_LineEdit->InitCoverage(0,10);
	m_pSetErrorValues_GridLayout->addWidget(m_pCurAbsError_LineEdit, 0, 1, 1, 1);

	m_pCurRelError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sCurRelError");//电流动作值相对误差(%):
	m_pCurRelError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pCurRelError_Label, 0, 2, 1, 1);

	m_pCurRelError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pCurRelError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pCurRelError_LineEdit, 0, 3, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pVolAbsError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sVolAbsError");//电压动作值绝对误差(V):
	m_pVolAbsError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pVolAbsError_Label, 1, 0, 1, 1);

	m_pVolAbsError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pVolAbsError_LineEdit->InitCoverage(0,10);
	m_pSetErrorValues_GridLayout->addWidget(m_pVolAbsError_LineEdit, 1, 1, 1, 1);

	m_pVolRelError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sVolRelError");//电压动作值相对误差(%):
	m_pVolRelError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pVolRelError_Label, 1, 2, 1, 1);

	m_pVolRelError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pVolRelError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pVolRelError_LineEdit, 1, 3, 1, 1);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pImpAbsError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sImpAbsError");//阻抗动作值绝对误差(Ω):
	m_pImpAbsError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pImpAbsError_Label, 2, 0, 1, 1);

	m_pImpAbsError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pImpAbsError_LineEdit->InitCoverage(0,10);
	m_pSetErrorValues_GridLayout->addWidget(m_pImpAbsError_LineEdit, 2, 1, 1, 1);

	m_pImpRelError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sImpRelError");//阻抗动作值相对误差(%):
	m_pImpRelError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pImpRelError_Label, 2, 2, 1, 1);

	m_pImpRelError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pImpRelError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pImpRelError_LineEdit, 2, 3, 1, 1);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pTimeAbsError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sTimeAbsError");//动作时间绝对误差(s):
	m_pTimeAbsError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pTimeAbsError_Label, 3, 0, 1, 1);

	m_pTimeAbsError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pTimeAbsError_LineEdit->InitCoverage(0,10);
	m_pSetErrorValues_GridLayout->addWidget(m_pTimeAbsError_LineEdit, 3, 1, 1, 1);

	m_pTimeRelError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sTimeRelError");//动作时间相对误差(%):
	m_pTimeRelError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pTimeRelError_Label, 3, 2, 1, 1);

	m_pTimeRelError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pTimeRelError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pTimeRelError_LineEdit, 3, 3, 1, 1);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pAngError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sAngError");//相位误差值(°):
	m_pAngError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pAngError_Label, 4, 0, 1, 1);

	m_pAngError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pAngError_LineEdit->InitCoverage(0,10);
	m_pSetErrorValues_GridLayout->addWidget(m_pAngError_LineEdit, 4, 1, 1, 1);

	m_pFreqError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sFreqError");//频率误差值(Hz):
	m_pFreqError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pFreqError_Label, 4, 2, 1, 1);

	m_pFreqError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pFreqError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pFreqError_LineEdit, 4, 3, 1, 1);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pDvDtError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sDvDtError");//电压滑差误差值(V/s):
	m_pDvDtError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pDvDtError_Label, 5, 0, 1, 1);

	m_pDvDtError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pDvDtError_LineEdit->InitCoverage(0,10);
	m_pSetErrorValues_GridLayout->addWidget(m_pDvDtError_LineEdit, 5, 1, 1, 1);

	m_pDfDtError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sDfDtError");//频率滑差误差值(Hz/s):
	m_pDfDtError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pDfDtError_Label, 5, 2, 1, 1);

	m_pDfDtError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pDfDtError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pDfDtError_LineEdit, 5, 3, 1, 1);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pDiffRateCoefAbsError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sDiffRateCoefAbsError");//差动比率制动系数绝对误差:
	m_pDiffRateCoefAbsError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffRateCoefAbsError_Label, 6, 0, 1, 1);

	m_pDiffRateCoefAbsError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pDiffRateCoefAbsError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffRateCoefAbsError_LineEdit, 6, 1, 1, 1);

	m_pDiffRateCoefRelError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sDiffRateCoefRelError");//差动比率制动系数相对误差(%):
	m_pDiffRateCoefRelError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffRateCoefRelError_Label, 6, 2, 1, 1);

	m_pDiffRateCoefRelError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pDiffRateCoefRelError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffRateCoefRelError_LineEdit, 6, 3, 1, 1);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pDiffHarmCoefAbsError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sDiffHarmCoefAbsError");//差动谐波制动系数绝对误差:
	m_pDiffHarmCoefAbsError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffHarmCoefAbsError_Label, 7, 0, 1, 1);

	m_pDiffHarmCoefAbsError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pDiffHarmCoefAbsError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffHarmCoefAbsError_LineEdit, 7, 1, 1, 1);

	m_pDiffHarmCoefRelError_Label = new QLabel(m_pSetErrorValues_GroupBox);
	xlang_GetLangStrByFile(strTemp,"sDiffHarmCoefRelError");//差动谐波制动系数相对误差(%):
	m_pDiffHarmCoefRelError_Label->setText(strTemp);
	m_pSetErrorValues_GridLayout->setSpacing(10);//设置行间距
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffHarmCoefRelError_Label, 7, 2, 1, 1);

	m_pDiffHarmCoefRelError_LineEdit = new QFloatLineEdit(m_pSetErrorValues_GroupBox);
	m_pDiffHarmCoefRelError_LineEdit->InitCoverage(0,100);
	m_pSetErrorValues_GridLayout->addWidget(m_pDiffHarmCoefRelError_LineEdit, 7, 3, 1, 1);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
	InitDatas();
	InitConnect();


	m_pStdValues_GroupBox->raise();
    //m_pSetErrorValues_GroupBox->raise();  //20240910 wanmj 系统参数误差部分去掉
	m_pTotal_VBoxLayout->addStretch();
// 	m_pModuleSet_GridLayout->setRowStretch(0,1);//设置第一行的占比
// 	m_pModuleSet_GridLayout->setRowStretch(1,2);//设置第二行的占比
}

void QSysParasWidget::InitConnect()
{

	connect(m_pSecondSynSet_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeSecondSyn(int)));
	connect(m_pDigitalType_Combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeDigitalType(int)));

	connect(m_pDigitalMeasType_Combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeDigitalMeasType(int)));

	connect(m_pBCodePositiveLogic_RadioBtn, SIGNAL(toggled(bool )), this, SLOT(slot_radio_BCodePositiveLogicChanged(bool)));
	connect(m_pBCodeNegtiveLogic_RadioBtn, SIGNAL(toggled(bool )), this, SLOT(slot_radio_BCodeNegtiveLogicChanged(bool)));

	connect(m_p1588PeerDelay_RadioBtn, SIGNAL(toggled(bool )), this, SLOT(slot_radio_1588PeerDelayChanged(bool)));
	connect(m_p1588ReqResp_RadioBtn, SIGNAL(toggled(bool )), this, SLOT(slot_radio_1588ReqRespChanged(bool)));

	connect(m_pDigitalSel_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_DigitalCheck_stateChanged(int)));
	connect(m_pDigitalMeasSel_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_DigitalCheck_stateChanged(int)));

	if(g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{
		connect(m_pWeakSel_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_WeakSelCheck_stateChanged(int)));
	}

	//2023/7/24 -wjs
#ifdef _USE_SoftKeyBoard_
	//connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)),Qt::UniqueConnection);
	//connect(m_pManualTest_UI->m_editTime, SIGNAL(clicked()), this, SLOT(on_m_editTimeChanged()));
	connect(m_pStdVol_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	connect(m_pStdCur_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	connect(m_pStdFre_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	connect(m_pAntiShakeTime_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	connect(m_pOverLoadDelay_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//系统参数误差部分
	//connect(m_pCurAbsError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pCurRelError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pVolAbsError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pVolRelError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pImpAbsError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pImpRelError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pTimeAbsError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pTimeRelError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pAngError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pFreqError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pDvDtError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pDfDtError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pDiffRateCoefAbsError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pDiffRateCoefRelError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pDiffHarmCoefAbsError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
	//connect(m_pDiffHarmCoefRelError_LineEdit,SIGNAL(clicked()),this,SLOT(slot_OnLineEditClicked()));
#endif
}

void QSysParasWidget::DisEnableDigitalUI()
{
	m_pDigitalSel_CheckBox->setDisabled(true);
	m_pDigitalType_Label->setDisabled(true);
	m_pDigitalType_Combobox->setDisabled(true);
	m_pDigitalMeasType_Combobox->setDisabled(true);
}

void QSysParasWidget::DisEnableWeekUI()
{
	m_pWeakSel_CheckBox->setDisabled(true);
}


void QSysParasWidget::slot_changeSecondSyn(int nIndex)
{
	m_pSysParas->m_bSyncSecond = nIndex;
}

void QSysParasWidget::slot_changeDigitalType(int nIndex)
{
	m_pSysParas->m_nIecFormat = nIndex;

	if (nIndex == STT_IEC_FORMAT_60044_8)
	{
	}
	else if (nIndex == STT_IEC_FORMAT_60044_8DC)
	{
	}
	else
	{

	}
}

void QSysParasWidget::slot_changeDigitalMeasType(int nIndex)
{
	m_pSysParas->m_nIecFormatMeas = nIndex;

}

void QSysParasWidget::slot_DigitalCheck_stateChanged(int nState)
{
	if (m_pDigitalSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pDigitalType_Combobox->setDisabled(FALSE);
	}
	else
	{
		m_pDigitalType_Combobox->setDisabled(TRUE);
	}

	if (m_pDigitalMeasSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pDigitalMeasType_Combobox->setDisabled(FALSE);
	}
	else
	{
		m_pDigitalMeasType_Combobox->setDisabled(TRUE);
	}


}

void QSysParasWidget::slot_radio_BCodePositiveLogicChanged(bool bSel)
{
	if (bSel)
	{
		m_pSysParas->m_nBCodeMode = 0;
	} 
	else
	{
		m_pSysParas->m_nBCodeMode = 1;
	}
}

void QSysParasWidget::slot_radio_BCodeNegtiveLogicChanged(bool bSel)
{
	if (bSel)
	{
		m_pSysParas->m_nBCodeMode = 1;
	} 
	else
	{
		m_pSysParas->m_nBCodeMode = 0;
	}
}

void QSysParasWidget::slot_radio_1588PeerDelayChanged(bool bSel)
{
	if (bSel)
	{
		m_pSysParas->m_n588Syn = 1;
	} 
	else
	{
		m_pSysParas->m_n588Syn = 0;
	}
}

void QSysParasWidget::slot_radio_1588ReqRespChanged(bool bSel)
{
	if (bSel)
	{
		m_pSysParas->m_n588Syn = 0;
	} 
	else
	{
		m_pSysParas->m_n588Syn = 1;
	}
}

void QSysParasWidget::ReleaseUI()
{

}

void QSysParasWidget::InitDatas()
{
	if (m_pSysParas->m_nHasAnalog)
	{
		m_pAnalogSel_CheckBox->setCheckState(Qt::Checked);
	} 
	else
	{
		m_pAnalogSel_CheckBox->setCheckState(Qt::Unchecked);
	}

	if (m_pSysParas->m_nHasDigital)
	{
		m_pDigitalSel_CheckBox->setCheckState(Qt::Checked);
		m_pDigitalType_Combobox->setDisabled(FALSE);
	} 
	else
	{
		m_pDigitalSel_CheckBox->setCheckState(Qt::Unchecked);
		m_pDigitalType_Combobox->setDisabled(TRUE);
	}

	if (m_pSysParas->m_nHasWeek)
	{
		m_pWeakSel_CheckBox->setCheckState(Qt::Checked);
	} 
	else
	{
		m_pWeakSel_CheckBox->setCheckState(Qt::Unchecked);
	}

	if (g_oLocalSysPara.m_nSupportAnalogOutput == 0)
	{
		m_pAnalogSel_CheckBox->setDisabled(true);
	}

	if (g_oLocalSysPara.m_nSupportDigitalOutput == 0)
	{
		m_pDigitalSel_CheckBox->setDisabled(true);
		m_pDigitalType_Combobox->setDisabled(true);
	}

	if (g_oLocalSysPara.m_nSupportWeakOutput == 0)
	{
		m_pWeakSel_CheckBox->setDisabled(true);
	}

	m_pDigitalType_Combobox->setCurrentIndex(m_pSysParas->m_nIecFormat);

	if (m_pSysParas->m_nUseAnalogMeas)
	{
		m_pAnalogMeasSel_CheckBox->setCheckState(Qt::Checked);
	} 
	else
	{
		m_pAnalogMeasSel_CheckBox->setCheckState(Qt::Unchecked);
	}

	if (m_pSysParas->m_nUseDigitalMeas)
	{
		m_pDigitalMeasSel_CheckBox->setCheckState(Qt::Checked);
		m_pDigitalMeasType_Combobox->setDisabled(FALSE);
	} 
	else
	{
		m_pDigitalMeasSel_CheckBox->setCheckState(Qt::Unchecked);
		m_pDigitalMeasType_Combobox->setDisabled(TRUE);
	}

// 	if (m_pSysParas->m_nUseWeekMeas)
// 	{
// 		m_pWeakMeasSel_CheckBox->setCheckState(Qt::Checked);
// 	} 
// 	else
// 	{
// 		m_pWeakMeasSel_CheckBox->setCheckState(Qt::Unchecked);
// 	}

	m_pDigitalMeasType_Combobox->setCurrentIndex(m_pSysParas->m_nIecFormatMeas);


	m_pStdVol_LineEdit->SetValue(m_pSysParas->m_fVNom);
	m_pStdCur_LineEdit->SetValue(m_pSysParas->m_fINom);
	m_pStdFre_LineEdit->SetValue(m_pSysParas->m_fFNom);
	

	if(g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{
		m_pZeroStdVol_LineEdit->SetValue(m_pSysParas->m_fU0_Std);
		m_pZeroStdCur_LineEdit->SetValue(m_pSysParas->m_fI0_Std);
	}

	m_pAntiShakeTime_LineEdit->SetValue(m_pSysParas->m_fStabTime*1000);

	if (m_pOverLoadDelay_LineEdit != NULL)
	{
		m_pOverLoadDelay_LineEdit->SetValue(m_pSysParas->m_fOverLoadDelay);
	}

    //20240910 wanmj 系统参数误差部分去掉
#if 0
	m_pCurAbsError_LineEdit->SetValue(m_pSysParas->m_fCurValue_AbsError);
	m_pCurRelError_LineEdit->SetValue(m_pSysParas->m_fCurValue_RelError*100);

	m_pVolAbsError_LineEdit->SetValue(m_pSysParas->m_fVolValue_AbsError);
	m_pVolRelError_LineEdit->SetValue(m_pSysParas->m_fVolValue_RelError*100);

	m_pImpAbsError_LineEdit->SetValue(m_pSysParas->m_fImpValue_AbsError);
	m_pImpRelError_LineEdit->SetValue(m_pSysParas->m_fImpValue_RelError*100);

	m_pTimeAbsError_LineEdit->SetValue(m_pSysParas->m_fTimeValue_AbsError);
	m_pTimeRelError_LineEdit->SetValue(m_pSysParas->m_fTimeValue_RelError*100);

	m_pAngError_LineEdit->SetValue(m_pSysParas->m_fAngValue_AbsError);
	m_pFreqError_LineEdit->SetValue(m_pSysParas->m_fFreValue_AbsError);

	m_pDvDtError_LineEdit->SetValue(m_pSysParas->m_fdvdtValue_AbsError);
	m_pDfDtError_LineEdit->SetValue(m_pSysParas->m_fdfdtValue_AbsError);

	m_pDiffHarmCoefAbsError_LineEdit->SetValue(m_pSysParas->m_fDiffHarmCoef_AbsError);
	m_pDiffHarmCoefRelError_LineEdit->SetValue(m_pSysParas->m_fDiffHarmCoef_RelError*100);
	m_pDiffRateCoefAbsError_LineEdit->SetValue(m_pSysParas->m_fDiffRateCoef_AbsError);
	m_pDiffRateCoefRelError_LineEdit->SetValue(m_pSysParas->m_fDiffRateCoef_RelError*100);
#endif
	m_pSecondSynSet_ComboBox->setCurrentIndex(m_pSysParas->m_bSyncSecond);

	if(m_pSysParas->m_nBCodeMode == 0)
	{
		m_pBCodePositiveLogic_RadioBtn->setChecked(true);
		m_pBCodeNegtiveLogic_RadioBtn->setChecked(false);
	}
	else
	{
		m_pBCodePositiveLogic_RadioBtn->setChecked(false);
		m_pBCodeNegtiveLogic_RadioBtn->setChecked(true);
	}

	if(m_pSysParas->m_n588Syn == 0)
	{
		m_p1588PeerDelay_RadioBtn->setChecked(false);
		m_p1588ReqResp_RadioBtn->setChecked(true);
	}
	else
	{
		m_p1588PeerDelay_RadioBtn->setChecked(true);
		m_p1588ReqResp_RadioBtn->setChecked(false);
	}
}

void QSysParasWidget::SaveDatas()
{
	if (m_pAnalogSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pSysParas->m_nHasAnalog = 1;
	}
	else
	{
		m_pSysParas->m_nHasAnalog = 0;
	}

	if (m_pDigitalSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pSysParas->m_nHasDigital = 1;
	}
	else
	{
		m_pSysParas->m_nHasDigital = 0;
	}

	if (m_pWeakSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pSysParas->m_nHasWeek = 1;
	}
	else
	{
		m_pSysParas->m_nHasWeek = 0;
	}

	m_pSysParas->m_nIecFormat = m_pDigitalType_Combobox->currentIndex();

	if (m_pAnalogMeasSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pSysParas->m_nUseAnalogMeas = 1;
	}
	else
	{
		m_pSysParas->m_nUseAnalogMeas = 0;
	}

	if (m_pDigitalMeasSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pSysParas->m_nUseDigitalMeas = 1;
	}
	else
	{
		m_pSysParas->m_nUseDigitalMeas = 0;
	}

// 	if (m_pWeakMeasSel_CheckBox->checkState() == Qt::Checked)
// 	{
// 		m_pSysParas->m_nUseWeekMeas = 1;
// 	}
// 	else
// 	{
// 		m_pSysParas->m_nUseWeekMeas = 0;
// 	}

	m_pSysParas->m_nIecFormatMeas = m_pDigitalType_Combobox->currentIndex();


	m_pSysParas->m_fVNom = m_pStdVol_LineEdit->GetValue();
	m_pSysParas->m_fINom = m_pStdCur_LineEdit->GetValue();
	m_pSysParas->m_fFNom = m_pStdFre_LineEdit->GetValue();


	if(g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{
		m_pSysParas->m_fU0_Std = m_pZeroStdVol_LineEdit->GetValue();
		m_pSysParas->m_fI0_Std = m_pZeroStdCur_LineEdit->GetValue();
	}

	m_pSysParas->m_fStabTime = m_pAntiShakeTime_LineEdit->GetValue()/1000;

	if (m_pOverLoadDelay_LineEdit != NULL)
	{
		m_pSysParas->m_fOverLoadDelay = m_pOverLoadDelay_LineEdit->GetValue();
	}


    //20240910 wanmj 系统参数误差部分去掉
#if 0
	m_pSysParas->m_fCurValue_AbsError = m_pCurAbsError_LineEdit->GetValue();
	m_pSysParas->m_fCurValue_RelError = m_pCurRelError_LineEdit->GetValue()/100;

	m_pSysParas->m_fVolValue_AbsError = m_pVolAbsError_LineEdit->GetValue();
	m_pSysParas->m_fVolValue_RelError = m_pVolRelError_LineEdit->GetValue()/100;

	m_pSysParas->m_fImpValue_AbsError = m_pImpAbsError_LineEdit->GetValue();
	m_pSysParas->m_fImpValue_RelError = m_pImpRelError_LineEdit->GetValue()/100;

	m_pSysParas->m_fTimeValue_AbsError = m_pTimeAbsError_LineEdit->GetValue();
	m_pSysParas->m_fTimeValue_RelError = m_pTimeRelError_LineEdit->GetValue()/100;

	m_pSysParas->m_fAngValue_AbsError = m_pAngError_LineEdit->GetValue();
	m_pSysParas->m_fFreValue_AbsError = m_pFreqError_LineEdit->GetValue();

	m_pSysParas->m_fdvdtValue_AbsError = m_pDvDtError_LineEdit->GetValue();
	m_pSysParas->m_fdfdtValue_AbsError = m_pDfDtError_LineEdit->GetValue();

	m_pSysParas->m_fDiffRateCoef_RelError = m_pDiffRateCoefRelError_LineEdit->GetValue()/100;
	m_pSysParas->m_fDiffRateCoef_AbsError = m_pDiffRateCoefAbsError_LineEdit->GetValue();
	m_pSysParas->m_fDiffHarmCoef_RelError = m_pDiffHarmCoefRelError_LineEdit->GetValue()/100;
	m_pSysParas->m_fDiffHarmCoef_AbsError = m_pDiffHarmCoefAbsError_LineEdit->GetValue();
#endif

}


void QSysParasWidget::slot_OnLineEditClicked()
{
#ifdef _USE_SoftKeyBoard_

	QSoftKeyBoard::DisableUserFunc();

#endif

//	GetWidgetBoard_DigitData(4,strValue,m_pMUTestTime_Edit,this);
//#ifdef _USE_SoftKeyBoard_
//	//QSoftKeyBoard::Attach330Channel(this, 4);
//	QSoftKeyBoard::AttachObj(this);
//	QSoftKeyBoard::ReAttachObj();
//#endif
}

void QSysParasWidget::slot_WeakSelCheck_stateChanged( int nState )
{
	if (nState == Qt::Checked)
	{
		m_pZeroStdVol_LineEdit->setDisabled(FALSE);
		m_pZeroStdCur_LineEdit->setDisabled(FALSE);
	}
	else
	{
		m_pZeroStdVol_LineEdit->setDisabled(TRUE);
		m_pZeroStdCur_LineEdit->setDisabled(TRUE);
	}
}


