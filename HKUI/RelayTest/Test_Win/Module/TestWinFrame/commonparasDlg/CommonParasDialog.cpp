#include "CommonParasDialog.h"
#include "..\Module\SttXTestMngrBaseApp.h"
#include "..\Module\CommonMethod\commonMethod.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../testwinbase.h"

extern CSttXTestMngrBaseApp* g_theSttXTestMngrBaseApp;

CommonParasDialog::CommonParasDialog(tmt_ImpedanceParas *pImpedanceParas,const CString &strMacroID,QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(/*QObject::tr("通用参数设置")*/g_sLangTxt_Native_GenParamSet);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |Qt::WindowCloseButtonHint);

	m_pImpedanceParas = pImpedanceParas;
	m_pCBOperateParas = (tmt_CBOperateParas*)pImpedanceParas;
	m_pRecloseAccParas = (tmt_RecloseAccParasEx*)pImpedanceParas;
	m_pDCOverCurrentParas = (tmt_DCOverCurrentParas *)pImpedanceParas;
	m_nIsOK = 0;
	//m_bPostFaultTime = bPostFaultTime;
	
	m_strMacroID = strMacroID;
	resize(300,  300); //20240223 suyang resize(800 *g_dUIShowCoef,  320)会对其他模块有影响，移动到搜索阻抗边界，还原之前数据
	init(strMacroID);
}

CommonParasDialog::CommonParasDialog(tmt_VolInverseTimeParasEx *pVolInverseTimeParas, const CString &strMacroID, QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(/*QObject::tr("通用参数设置")*/g_sLangTxt_Native_GenParamSet);

	m_pVolInverseTimeParas  =  pVolInverseTimeParas;
	m_nInitFlag = 0;
	m_nIsOK = 0; 

	resize(300,  100);  
	init(strMacroID);

}


CommonParasDialog::~CommonParasDialog()
{

}

void CommonParasDialog::init(const CString &strMacroID)
{
	//当模块是整组模块的时候; 调用如下的函数，和其他函数不搭噶；2021-8-4 add mym
	m_MainLayout = new QVBoxLayout;

	if (strMacroID == STT_MACRO_ID_PsuCBOperate)
	{
		m_nInitFlag = 1;
		initUI_CB();		
		initBtn();

		initPara_CB();
		initData_CB();
		initConnect_CB();
		m_nInitFlag = 2;

	}
	else if(strMacroID == STT_MACRO_ID_DistanceSearch)
	{
		m_pDSParas = (tmt_DistanceSearchParas*)m_pImpedanceParas;
		initUI_DS();
		initBtn();
		CopyPartForDS(*m_pDSParas,m_DSParas);
		initData_DS();
		initConnect_DS();
	}
	else if(strMacroID == STT_MACRO_ID_OverCurrent || strMacroID == STT_MACRO_ID_StateI0Current 
		|| strMacroID == STT_MACRO_ID_Distance || strMacroID == STT_MACRO_ID_OverVoltageTest)
	{
		initUI_Base();
		initBtn();

		CopyPartForImpedance(*m_pImpedanceParas,m_ImpedanceParas);
		initData();
		initConnect();
	}
	else if(strMacroID == STT_MACRO_ID_DCOverCurrentTest)
	{
		initUI_DC();
		initBtn();

		CopyPartForDCOverCurrent(*m_pDCOverCurrentParas,m_oDCOverCurrentParas);
		initData_DC();
		initConnect_DC();
	}
	else if (strMacroID == STT_MACRO_ID_RecloseAcc)
	{
		m_nInitFlag = 1;
		initUI_Re();		
		initBtn();

		m_BtnOk->setFixedWidth(100);
		m_BtnCancel->setFixedWidth(100);

		initPara_Re();
		initData_Re();
		initConnect_Re();
		m_nInitFlag = 2;
	}
	else if (strMacroID == STT_MACRO_ID_VoltageInverseTime)
	{
		m_nInitFlag = 1;
		initUI_Voltage();		
		initBtn();

		m_BtnOk->setFixedWidth(100);
		m_BtnCancel->setFixedWidth(100);

		initPara_Voltage();
		initData_Voltage();
		initConnect_Voltage();
		m_nInitFlag = 2;
	}

	m_MainLayout->addLayout(m_TopLayout);
	m_MainLayout->addLayout(m_BottomLayout);

	setLayout(m_MainLayout);
}

void CommonParasDialog::initData()
{
	m_editPreFaultTime->setText(QString::number(m_ImpedanceParas.m_fPreFaultTime, 'f', 3));
	m_editFaultTime->setText(QString::number(m_ImpedanceParas.m_fMarginTime, 'f', 3));
	m_editPostFaultTime->setText(QString::number(m_ImpedanceParas.m_fPostFaultTime, 'f', 3));
	m_CmbFaultTrigMode->SetIndex(&m_ImpedanceParas.m_nFaultTrigMode);

	m_CmbPTPoint->SetIndex((int*)(&m_ImpedanceParas.m_nPTPoint));
	m_CmbCTPoint->SetIndex(&m_ImpedanceParas.m_nCTPoint);

	m_editIfh->setText(QString::number(m_ImpedanceParas.m_fIfh, 'f', 3));
	m_editPowerAngle->setText(QString::number(m_ImpedanceParas.m_fPowerAngle, 'f', 3));

	m_CmbCBSimulation->SetIndex(&m_ImpedanceParas.m_bCBSimulation);
	m_editCBTripTime->setText(QString::number(m_ImpedanceParas.m_fCBTripTime * 1000, 'f', 3));
	m_editCBCloseTime->setText(QString::number(m_ImpedanceParas.m_fCBCloseTime * 1000, 'f', 3));

	m_CmbVzDefine->SetIndex(&m_ImpedanceParas.m_nVzDefine);
	m_CmbVzPhDefine->SetIndex(&m_ImpedanceParas.m_nVzPhDefine);
	m_editVzPh->setText(QString::number(m_ImpedanceParas.m_fUxInput_Ang, 'f', 3));
	
	slot_FaultTrigModeChange(0);
	slot_CBSimulationChange(0);
	slot_VzDefineChange(0);
}

void CommonParasDialog::initUI_Base()
{
	CTestDataTypeMngrConstGlobal::Create();

	m_TopLayout = new QGridLayout();

	label_PreFaultTime = new QLabel();
	label_PreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PreFaultTime->setText(/*QObject::tr("故障前时间(s):")*/g_sLangTxt_Native_PreFaultTimes);
	m_TopLayout->addWidget(label_PreFaultTime,0,0);
	m_editPreFaultTime = new QFloatLineEdit(this);
	m_editPreFaultTime->InitCoverage(0,999.999);
	m_editPreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPreFaultTime,0,1);

	label_FaultTime = new QLabel();
	label_FaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_FaultTime->setText(/*QObject::tr("故障时间裕度(s):")*/g_sLangTxt_Native_faultTimeMargin);
	m_TopLayout->addWidget(label_FaultTime,1,0);
	m_editFaultTime = new QLineEdit(this);
	//m_editFaultTime->InitCoverage(0.001,999.999);
	m_editFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	connect(m_editFaultTime , SIGNAL(editingFinished()),this,SLOT(slot_FaultTimeChange()));
	m_TopLayout->addWidget(m_editFaultTime,1,1);

	label_PostFaultTime = new QLabel();
	label_PostFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PostFaultTime->setText(/*QObject::tr("保护动作后持续时间(s):")*/g_sLangTxt_Native_DurProtTrip+tr("(s):"));
	m_TopLayout->addWidget(label_PostFaultTime,2,0);
	m_editPostFaultTime = new QFloatLineEdit(this);
	m_editPostFaultTime->InitCoverage(0,999.999);
	m_editPostFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPostFaultTime,2,1);

	label_FaultTrigMode = new QLabel();
	label_FaultTrigMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_FaultTrigMode->setText(/*QObject::tr("故障触发方式:")*/g_sLangTxt_Native_FaultTrigMethod);
	m_TopLayout->addWidget(label_FaultTrigMode,3,0);
	m_CmbFaultTrigMode = new QValueComboBox(this);
	m_CmbFaultTrigMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultTrigMode")));
	m_CmbFaultTrigMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbFaultTrigMode,3,1);

	label_PTPoint = new QLabel();
	label_PTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PTPoint->setText(/*QObject::tr("TV安装位置:")*/g_sLangTxt_Native_TVInstLoc+tr(":"));
	m_TopLayout->addWidget(label_PTPoint,4,0);
	m_CmbPTPoint = new QValueComboBox(this);
	m_CmbPTPoint->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PTPosition")));
	m_CmbPTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbPTPoint,4,1);

	label_CTPoint = new QLabel();
	label_CTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CTPoint->setText(/*QObject::tr("TA正极性:")*/g_sLangTxt_Native_PosPolTA+tr(":"));
	m_TopLayout->addWidget(label_CTPoint,5,0);
	m_CmbCTPoint = new QValueComboBox(this);
	m_CmbCTPoint->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CTPos")));
	m_CmbCTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbCTPoint,5,1);

	label_Ifh = new QLabel();
	label_Ifh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Ifh->setText(/*QObject::tr("负荷电流(A):")*/g_sLangTxt_LoadI);
	m_TopLayout->addWidget(label_Ifh,6,0);
	m_editIfh = new QFloatLineEdit(this);
	m_editIfh->InitCoverage(0,20);
	m_editIfh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editIfh,6,1);

	label_PowerAngle = new QLabel();
	label_PowerAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PowerAngle->setText(/*QObject::tr("负荷功角(°):")*/g_sLangTxt_State_LoadAngle);
	m_TopLayout->addWidget(label_PowerAngle,7,0);
	m_editPowerAngle = new QFloatLineEdit(this);
	m_editPowerAngle->InitCoverage(0,360);
	m_editPowerAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPowerAngle,7,1);


	label_CBSimulation = new QLabel();
	label_CBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBSimulation->setText(/*QObject::tr("断路器模拟:")*/g_sLangTxt_Native_CBsim);
	m_TopLayout->addWidget(label_CBSimulation,8,0);
	m_CmbCBSimulation = new QValueComboBox(this);
	m_CmbCBSimulation->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CBSimulation")));
	m_CmbCBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbCBSimulation,8,1);

	label_CBTripTime = new QLabel();
	label_CBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBTripTime->setText(/*QObject::tr("分闸时间(ms):")*/g_sLangTxt_Native_TripTime+tr("(ms):"));
	m_TopLayout->addWidget(label_CBTripTime,9,0);
	m_editCBTripTime = new QFloatLineEdit(this);
	m_editCBTripTime->InitCoverage(0,999999);
	m_editCBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editCBTripTime,9,1);

	label_CBCloseTime = new QLabel();
	label_CBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBCloseTime->setText(/*QObject::tr("合闸时间(ms):")*/g_sLangTxt_Native_CloseTime+tr("(ms):"));
	m_TopLayout->addWidget(label_CBCloseTime,10,0);
	m_editCBCloseTime = new QFloatLineEdit(this);
	m_editCBCloseTime->InitCoverage(0,999999);
	m_editCBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editCBCloseTime,10,1);

	label_VzDefine = new QLabel();
	label_VzDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_VzDefine->setText(/*QObject::tr("抽取电压输出定义:")*/g_sLangTxt_Native_extractvol_outputdef);
	m_TopLayout->addWidget(label_VzDefine,11,0);
	m_CmbVzDefine = new QValueComboBox(this);
	m_CmbVzDefine->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PsuVzDefine")));
	m_CmbVzDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbVzDefine,11,1);

	label_VzPhDefine = new QLabel();
	label_VzPhDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_VzPhDefine->setText(/*QObject::tr("抽取电压参考相定义:")*/g_sLangTxt_Native_extractvol_refphasedef);
	m_TopLayout->addWidget(label_VzPhDefine,12,0);
	m_CmbVzPhDefine = new QValueComboBox(this);
	m_CmbVzPhDefine->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PsuVzRefPhase")));
	m_CmbVzPhDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbVzPhDefine,12,1);

	label_VzPh = new QLabel();
	label_VzPh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_VzPh->setText(/*QObject::tr("抽取电压相角(相对参考相):")*/g_sLangTxt_Native_extractvol_phaseangle);
	m_TopLayout->addWidget(label_VzPh,13,0);
	m_editVzPh = new QFloatLineEdit(this);
	m_editVzPh->InitCoverage(0,360.0);
	m_editVzPh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editVzPh,13,1);
}


void CommonParasDialog::slot_FaultTimeChange()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strTemp = m_editFaultTime->text();
	float fvalue = strTemp.toFloat();

	fvalue = setLimit(0.001,999.999,fvalue);

	m_editFaultTime->setText(QString::number(fvalue, 'f', 3));
}

void CommonParasDialog::slot_FaultTimeChange_DC()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strTemp = m_editFaultTime->text();
	float fvalue = strTemp.toFloat();
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		fvalue = setLimit(0.001,3000.00,fvalue);
	}
	else
	{
		fvalue = setLimit(0.001,999.999,fvalue);
	}

	//fvalue = setLimit(0.001,999.999,fvalue);

	m_editFaultTime->setText(QString::number(fvalue, 'f', 3));
}

void CommonParasDialog::initBtn()
{
	m_BottomLayout = new QHBoxLayout;

	m_BtnOk = new QPushButton(this);
	m_BtnOk->setText(/*QObject::tr("确认")*/g_sLangTxt_Native_Confm);
	m_BtnOk->setFixedWidth(100);

	m_BtnOk->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_BtnOk->setIcon (QPixmap( "./images/Check.png"));
	m_BottomLayout->addWidget(m_BtnOk);

	m_BtnCancel = new QPushButton(this);
	m_BtnCancel->setText(/*QObject::tr("取消")*/g_sLangTxt_Cancel);
	m_BtnCancel->setFixedWidth(100);
	m_BtnCancel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_BtnCancel->setIcon (QPixmap( "./images/Cancel.png"));
	m_BottomLayout->addWidget(m_BtnCancel);
}

void CommonParasDialog::slot_ClickOk()
{
	JudgeModifyPara(m_ImpedanceParas.m_fMarginTime,m_editFaultTime->text().toFloat());
	m_ImpedanceParas.m_fMarginTime = m_editFaultTime->text().toFloat();
	JudgeModifyPara(m_ImpedanceParas.m_fPreFaultTime,m_editPreFaultTime->text().toFloat());
	m_ImpedanceParas.m_fPreFaultTime = m_editPreFaultTime->text().toFloat();
	JudgeModifyPara(m_ImpedanceParas.m_fPostFaultTime,m_editPostFaultTime->text().toFloat());
	m_ImpedanceParas.m_fPostFaultTime = m_editPostFaultTime->text().toFloat();	

	JudgeModifyPara(m_ImpedanceParas.m_fIfh,m_editIfh->text().toFloat());
	m_ImpedanceParas.m_fIfh = m_editIfh->text().toFloat();
	JudgeModifyPara(m_ImpedanceParas.m_fPowerAngle,m_editPowerAngle->text().toFloat());
	m_ImpedanceParas.m_fPowerAngle = m_editPowerAngle->text().toFloat();

	JudgeModifyPara(m_ImpedanceParas.m_fCBTripTime,m_editCBTripTime->text().toFloat() / 1000);
	m_ImpedanceParas.m_fCBTripTime = m_editCBTripTime->text().toFloat();
	m_ImpedanceParas.m_fCBTripTime = m_ImpedanceParas.m_fCBTripTime / 1000.0;
	JudgeModifyPara(m_ImpedanceParas.m_fCBCloseTime,m_editCBCloseTime->text().toFloat() / 1000);
	m_ImpedanceParas.m_fCBCloseTime = m_editCBCloseTime->text().toFloat();
	m_ImpedanceParas.m_fCBCloseTime = m_ImpedanceParas.m_fCBCloseTime / 1000.0;

	JudgeModifyPara(m_ImpedanceParas.m_fUxInput_Ang,m_editVzPh->text().toFloat());
	m_ImpedanceParas.m_fUxInput_Ang = m_editVzPh->text().toFloat();

	CopyPartForImpedance(m_ImpedanceParas,*m_pImpedanceParas);

	emit sig_ClickOk();
	close();
	m_nIsOK = 1;
}

void CommonParasDialog::slot_ClickCancel()
{
	close();
	m_nIsOK = 2;
}

void CommonParasDialog::closeEvent( QCloseEvent *event )
{
	m_nIsOK = 2;
}


void CommonParasDialog::CopyPartForImpedance( tmt_ImpedanceParas &Para_A,tmt_ImpedanceParas &Para_B )
{
	Para_B.m_fMarginTime = Para_A.m_fMarginTime;
	Para_B.m_fPreFaultTime = Para_A.m_fPreFaultTime;
	Para_B.m_fPostFaultTime = Para_A.m_fPostFaultTime;
	Para_B.m_nFaultTrigMode = Para_A.m_nFaultTrigMode;

	Para_B.m_nPTPoint = Para_A.m_nPTPoint;
	Para_B.m_nCTPoint = Para_A.m_nCTPoint;
	Para_B.m_fIfh = Para_A.m_fIfh;
	Para_B.m_fPowerAngle = Para_A.m_fPowerAngle;

	Para_B.m_bCBSimulation = Para_A.m_bCBSimulation;
	Para_B.m_fCBTripTime = Para_A.m_fCBTripTime;
	Para_B.m_fCBCloseTime = Para_A.m_fCBCloseTime;

	Para_B.m_nVzDefine = Para_A.m_nVzDefine;
	Para_B.m_nVzPhDefine = Para_A.m_nVzPhDefine;
	Para_B.m_fUxInput_Ang = Para_A.m_fUxInput_Ang;
}
void CommonParasDialog::JudgeModifyPara(float a,float b)
{
	if (abs(a - b) > 0.00001)
	{
		g_theSttXTestMngrBaseApp->SetModifyPara();
	}
}
void CommonParasDialog::JudgeModifyPara(int a,int b)
{
	if (a != b)
	{
		g_theSttXTestMngrBaseApp->SetModifyPara();
	}
}

void CommonParasDialog::JudgeModifyPara(long a,long b)
{
	if (a != b)
	{
		g_theSttXTestMngrBaseApp->SetModifyPara();
	}
}
void CommonParasDialog::initConnect()
{
	connect(m_CmbFaultTrigMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTrigModeChange(int)));
	connect(m_CmbCBSimulation,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CBSimulationChange(int)));
	connect(m_CmbVzDefine,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_VzDefineChange(int)));

	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel()));
}

void CommonParasDialog::slot_FaultTrigModeChange( int )
{
	int index = m_CmbFaultTrigMode->currentIndex();
	switch (index)
	{
	case 0:
		{
			m_editPreFaultTime->setEnabled(true);
		}break;
	case 1:
		{
			m_editPreFaultTime->setEnabled(false);
		}break;
	case 2:
		{
			m_editPreFaultTime->setEnabled(false);
		}break;
	case 3:
		{
			m_editPreFaultTime->setEnabled(false);
		}break;
	}
}


void CommonParasDialog::slot_CBSimulationChange( int )
{
	int index = m_CmbCBSimulation->currentIndex();
	if (index == 0)
	{
		m_editCBTripTime->setEnabled(false);
		m_editCBCloseTime->setEnabled(false);
	}
	else
	{
		m_editCBTripTime->setEnabled(true);
		m_editCBCloseTime->setEnabled(true);
	}
}


void CommonParasDialog::slot_VzDefineChange( int )
{
	int index = m_CmbVzDefine->currentIndex();
	switch (index)
	{
	case 1:
	case 2:
	case 3:
		{
			m_CmbVzPhDefine->setEnabled(true);
			m_editVzPh->setEnabled(true);
		}break;
	case 0:
	case 4:
	case 5:
	case 6:
	case 7:
		{
			m_CmbVzPhDefine->setEnabled(false);
			m_editVzPh->setEnabled(false);
		}break;
	}
}

//整组 mym 2021-8-3
void CommonParasDialog::initUI_CB()
{
	CTestDataTypeMngrConstGlobal::Create();

	m_TopLayout = new QGridLayout();

	label_CB[0] = new QLabel();
	label_CB[0]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[0]->setText(/*QObject::tr("故障前时间(s):")*/g_sLangTxt_Native_PreFaultTimes);
	m_TopLayout->addWidget(label_CB[0],  0,  0);
	m_pEditCB[0] = new QFloatLineEdit(this);
	m_pEditCB[0] ->InitCoverage(0,100000);
	m_pEditCB[0] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[0] ,  0,  1);

	label_CB[1] = new QLabel();
	label_CB[1]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[1]->setText(/*QObject::tr("保护动作后持续时间(s):")*/g_sLangTxt_Native_DurProtTrip+tr("(s):"));
	m_TopLayout->addWidget(label_CB[1],   1,  0);
	m_pEditCB[1] = new QFloatLineEdit(this);
	m_pEditCB[1] ->InitCoverage(0,  100000);
	m_pEditCB[1] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[1] ,   1,  1);

	label_CB[2] = new QLabel();
	label_CB[2]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[2]->setText(/*QObject::tr("故障触发方式:")*/g_sLangTxt_Native_FaultTrigMethod+tr(":"));
	m_TopLayout->addWidget(label_CB[2],    2,  0);
	m_pCmbCB[0] = new QValueComboBox(this);
	m_pCmbCB[0]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultTrigMode")));//好了
	m_pCmbCB[0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[0],   2,  1);

	label_CB[3] = new QLabel();
	label_CB[3]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	label_CB[3]->setText(/*QObject::tr("TV 安装位置:")*/g_sLangTxt_Native_TVInstLoc+tr(":"));
	m_TopLayout->addWidget(label_CB[3],    3,  0);
	m_pCmbCB[1] = new QValueComboBox(this);
	m_pCmbCB[1]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PTPosition")));//好了
	m_pCmbCB[1]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[1],   3,  1);

	label_CB[4] = new QLabel();
	label_CB[4]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[4]->setText(/*QObject::tr("TA 正极性:")*/g_sLangTxt_Native_PosPolTA+tr(":"));
	m_TopLayout->addWidget(label_CB[4],   4,  0);
	m_pCmbCB[2] = new QValueComboBox(this);
	m_pCmbCB[2]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CTPos")));//好了
	m_pCmbCB[2]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[2],  4, 1);

	label_CB[5] = new QLabel();
	label_CB[5]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[5]->setText(/*QObject::tr("试验过程:")*/g_sLangTxt_Native_test_process);
	m_TopLayout->addWidget(label_CB[5],  5,  0);
	m_pCmbCB[3] = new QValueComboBox(this);
	m_pCmbCB[3]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("TestProcess")));//好了
	m_pCmbCB[3]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[3],  5, 1);

	label_CB[6] = new QLabel();
	label_CB[6]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[6]->setText(/*QObject::tr("重合方式:")*/g_sLangTxt_Native_coincidence_mode);
	m_TopLayout->addWidget(label_CB[6],   6,  0);
	m_pCmbCB[4] = new QValueComboBox(this);
	m_pCmbCB[4]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("RecloseMode")));//好了
	m_pCmbCB[4]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[4],  6, 1);

	label_CB[7] = new QLabel();
	label_CB[7]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[7]->setText(/*QObject::tr("开关跳后持续时间(s):")*/g_sLangTxt_Native_duration_afterjump);
	m_TopLayout->addWidget(label_CB[7],    7,  0);
	m_pEditCB[2] = new QFloatLineEdit(this);
	m_pEditCB[2] ->InitCoverage(0,  100000);
	m_pEditCB[2] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[2] ,   7,  1);

	label_CB[8] = new QLabel();
	label_CB[8]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[8]->setText(/*QObject::tr("重合持续时间(s):")*/g_sLangTxt_Native_duration_coincidence);
	m_TopLayout->addWidget(label_CB[8],   8,  0);
	m_pEditCB[3] = new QFloatLineEdit(this);
	m_pEditCB[3] ->InitCoverage(0,  100000);
	m_pEditCB[3] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[3] ,   8,  1);

	label_CB[9] = new QLabel();
	label_CB[9]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[9]->setText(/*QObject::tr("后加速开关跳开后持续时间(s):")*/g_sLangTxt_Native_postaccelerat_duration);
	m_TopLayout->addWidget(label_CB[9],   9,  0);
	m_pEditCB[4] = new QFloatLineEdit(this);
	m_pEditCB[4] ->InitCoverage(0,  100000);
	m_pEditCB[4] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[4] ,   9,  1);


	label_CB[10] = new QLabel();
	label_CB[10]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[10]->setText(/*QObject::tr("阻抗参考方式:")*/g_sLangTxt_Native_impedance_refmode);
	m_TopLayout->addWidget(label_CB[10],   10,  0);
	m_pCmbCB[5] = new QValueComboBox(this);
	m_pCmbCB[5]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("RXSelect")));//阻抗参考方式
	m_pCmbCB[5]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[5],  10, 1);

	label_CB[11] = new QLabel();
	label_CB[11]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[11]->setText(/*QObject::tr("零序补偿系数计算方式:")*/g_sLangTxt_Native_zeroseq_comp_calculat);
	m_TopLayout->addWidget(label_CB[11],   11,  0);

	m_pCmbCB[6] = new QValueComboBox(this);
	//零序补偿系数计算方式 1  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
	m_pCmbCB[6]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("K0Mode")));// 好了
	m_pCmbCB[6]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[6],  11, 1);


	label_CB[12] = new QLabel();
	label_CB[12]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[12]->setText(/*QObject::tr("零序补偿系数(|K0 | KR |Z0/Z1|):")*/g_sLangTxt_State_ZeroCoeff+tr("(|K0 | KR |Z0/Z1|):"));
	m_TopLayout->addWidget(label_CB[12],   12,  0);
	m_pEditCB[5] = new QFloatLineEdit(this);
	m_pEditCB[5] ->InitCoverage(0,  100000);
	m_pEditCB[5] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[5] ,   12,  1);


	label_CB[13] = new QLabel();
	label_CB[13]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[13]->setText(/*QObject::tr("零序补偿系数(Phi(K0) KX Phi(Z0/Z1)):")*/g_sLangTxt_State_ZeroCoeff+tr("(Phi(K0) KX Phi(Z0/Z1)):"));
	m_TopLayout->addWidget(label_CB[13],   13,  0);
	m_pEditCB[6] = new QFloatLineEdit(this);
	m_pEditCB[6] ->InitCoverage(0,  100000);
	m_pEditCB[6] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[6] ,   13,  1);


	// 计算方式
	label_CB[12] = new QLabel();
	label_CB[12]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[12]->setText(/*QObject::tr("计算方式:")*/g_sLangTxt_State_CalcType);
	m_TopLayout->addWidget(label_CB[12],   0,  2);
	m_pCmbCB[7] = new QValueComboBox(this);
	m_pCmbCB[7]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CalcuMode")));//好了
	m_pCmbCB[7]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[7],  0,  3);

	label_CB[13] = new QLabel();
	label_CB[13]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[13]->setText(/*QObject::tr("系统阻抗(Ω):")*/g_sLangTxt_Native_system_impedance);
	m_TopLayout->addWidget(label_CB[13],   1,  2);
	m_pEditCB[7] = new QFloatLineEdit(this);
	m_pEditCB[7] ->InitCoverage(0,  10000);
	m_pEditCB[7] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[7] ,   1,  3);

	label_CB[14] = new QLabel();
	label_CB[14]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[14]->setText(/*QObject::tr("系统阻抗角(°):")*/g_sLangTxt_Native_system_impedance_angle);
	m_TopLayout->addWidget(label_CB[14],   2,  2);
	m_pEditCB[8] = new QFloatLineEdit(this);
	m_pEditCB[8] ->InitCoverage(-360,  360);
	m_pEditCB[8] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[8] ,   2,  3);

	label_CB[15] = new QLabel();
	label_CB[15]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[15]->setText(/*QObject::tr("断路器模拟:")*/g_sLangTxt_Native_CBsim+tr(":"));
	m_TopLayout->addWidget(label_CB[15],   3,  2);
	m_pCmbCB[8] = new QValueComboBox(this);
	m_pCmbCB[8]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CBSimulation")));//好了
	m_pCmbCB[8]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[8],  3,  3);


	label_CB[16] = new QLabel();
	label_CB[16]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[16]->setText(/*QObject::tr("分闸时间(ms):")*/g_sLangTxt_Native_TripTime+tr("(ms):"));
	m_TopLayout->addWidget(label_CB[16],   4,  2);
	m_pEditCB[9] = new QFloatLineEdit(this);
	m_pEditCB[9] ->InitCoverage(0,  99999);
	m_pEditCB[9] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[9] ,   4,  3);

	label_CB[17] = new QLabel();
	label_CB[17]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[17]->setText(/*QObject::tr("合闸时间(ms):")*/g_sLangTxt_Native_CloseTime+tr("(ms):"));
	m_TopLayout->addWidget(label_CB[17],   5,  2);
	m_pEditCB[10] = new QFloatLineEdit(this);
	m_pEditCB[10] ->InitCoverage(0,  99999);
	m_pEditCB[10] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[10] ,   5,  3);


	label_CB[18] = new QLabel();
	label_CB[18]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[18]->setText(/*QObject::tr("合闸角选择:")*/g_sLangTxt_Native_closingangle_select);
	m_TopLayout->addWidget(label_CB[18],   6,  2);
	m_pCmbCB[9] = new QValueComboBox(this);
	m_pCmbCB[9]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultAngMode")));//好了
	m_pCmbCB[9]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[9],  6,  3);


	label_CB[19] = new QLabel();
	label_CB[19]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[19]->setText(/*QObject::tr("合闸角(°):")*/g_sLangTxt_Native_closingangle);
	m_TopLayout->addWidget(label_CB[19],   7,  2);
	m_pEditCB[11] = new QFloatLineEdit(this);
	m_pEditCB[11] ->InitCoverage(-360,  360);
	m_pEditCB[11] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[11] ,   7,  3);

	label_CB[19] = new QLabel();
	label_CB[19]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[19]->setText(/*QObject::tr("叠加非周期分量(°):")*/g_sLangTxt_Native_superimposed_nonperiodic);
	m_TopLayout->addWidget(label_CB[19],   8,  2);
	m_pCmbCB[10] = new QValueComboBox(this);
	m_pCmbCB[10]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultId")));//好了
	m_pCmbCB[10]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[10],  8,  3);

	label_CB[20] = new QLabel();
	label_CB[20]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[20]->setText(/*QObject::tr("抽取电压输出定义:")*/g_sLangTxt_Native_extractvol_outputdef);
	m_TopLayout->addWidget(label_CB[20],   9,  2);
	m_pCmbCB[11] = new QValueComboBox(this);
	m_pCmbCB[11]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PsuVzDefine")));////Uz输出定义 S1=0,S2=√3×3Vo,S3=-√3×3Vo,S4=3Vo,S5=-3Vo,S6=抽取电压
	m_pCmbCB[11]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[11],  9,  3);

	label_CB[21] = new QLabel();
	label_CB[21]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[21]->setText(/*QObject::tr("抽取电压参考相定义:")*/g_sLangTxt_Native_extractvol_refphasedef);
	m_TopLayout->addWidget(label_CB[21],   10,  2);
	m_pCmbCB[12] = new QValueComboBox(this);
	m_pCmbCB[12]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PsuVzRefPhase")));////S1=Va相位,S2=Vb相位,S3=Vc相位,S4=Vab相位,S5=Vbc相位,S6=Vca相位
	m_pCmbCB[12]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbCB[12],  10,  3);


	label_CB[22] = new QLabel();
	label_CB[22]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CB[22]->setText(/*QObject::tr("抽取电压相角(相对参考相)(°):")*/g_sLangTxt_Native_extractvol_phaseangle);
	m_TopLayout->addWidget(label_CB[22],   11,  2);
	m_pEditCB[12] = new QFloatLineEdit(this);
	m_pEditCB[12] ->InitCoverage(-360,  360);
	m_pEditCB[12] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditCB[12] ,   11,  3);
}

//整组 mym 2021-8-3
void CommonParasDialog::initData_CB()
{
	int  nComboCnt = 13;
	m_pCmbCB[0]->SetIndex(&m_oCBOperateParas.m_nFaultTrigMode);
	m_pCmbCB[1]->SetIndex(&m_oCBOperateParas.m_nPTPoint);
	m_pCmbCB[2]->SetIndex(&m_oCBOperateParas.m_nCTPoint);
	m_pCmbCB[3]->SetIndex(&m_oCBOperateParas.m_nTestProcCtrlMode);
	m_pCmbCB[4]->SetIndex(&m_oCBOperateParas.m_nRecloseMode);
	m_pCmbCB[5]->SetIndex(&m_oCBOperateParas.m_nRXSelect);
	m_pCmbCB[6]->SetIndex(&m_oCBOperateParas.m_nK0CalMode);
	m_pCmbCB[7]->SetIndex(&m_oCBOperateParas.m_nCalMode);
	m_pCmbCB[8]->SetIndex(&m_oCBOperateParas.m_bCBSimulation);
	m_pCmbCB[9]->SetIndex(&m_oCBOperateParas.m_nFaultIncMode);
	m_pCmbCB[10]->SetIndex((int*)&m_oCBOperateParas.m_bIPlusDC);         //叠加非周期分量
	m_pCmbCB[11]->SetIndex(&m_oCBOperateParas.m_nVzDefine);        //Uz输出定义
	m_pCmbCB[12]->SetIndex(&m_oCBOperateParas.m_nVzPhDefine);   //Uz参考定义

	int  nEditCnt = 13;

	m_pEditCB[0]->setText(QString::number(m_oCBOperateParas.m_fPreFaultTime, 'f', 3));
	m_pEditCB[1]->setText(QString::number(m_oCBOperateParas.m_fPostFaultTime, 'f', 3));
	m_pEditCB[2]->setText(QString::number(m_oCBOperateParas.m_fPostFaultTime, 'f', 3));
	m_pEditCB[3]->setText(QString::number(m_oCBOperateParas.m_fRecloseTime, 'f', 3));
	m_pEditCB[4]->setText(QString::number(m_oCBOperateParas.m_fTAfterAccTrig, 'f', 3));
	m_pEditCB[5]->setText(QString::number(m_oCBOperateParas.m_fK0Amp, 'f', 3));
	m_pEditCB[6]->setText(QString::number(m_oCBOperateParas.m_fK0Angle, 'f', 3));
	m_pEditCB[7]->setText(QString::number(m_oCBOperateParas.m_fZs, 'f', 3));
	m_pEditCB[8]->setText(QString::number(m_oCBOperateParas.m_fPhis, 'f', 3));
	m_pEditCB[9]->setText(QString::number(m_oCBOperateParas.m_fCBTripTime * 1000 , 'f', 3));//分闸时间
	m_pEditCB[10]->setText(QString::number(m_oCBOperateParas.m_fCBCloseTime * 1000, 'f', 3));//合闸时间
	m_pEditCB[11]->setText(QString::number(m_oCBOperateParas.m_fFaultAngle, 'f', 3));//合闸角
	m_pEditCB[12]->setText(QString::number(m_oCBOperateParas.m_fUxInput_Ang, 'f', 3));//Uz相角(相对参考相)


	//连接起来 槽
	for (int i  =  0;  i  < nEditCnt;  i++)
	{
		connect(m_pEditCB[i],	SIGNAL(/*textChanged(QString )*/editingFinished()),  this , SLOT(slot_EditValueChanged_CB( )));//2023-11-06 suyang 触发信号改为editingFinished()
	}

	for (int i  =  0;  i  < nComboCnt;  i++)
	{
		if (m_pCmbRe[i])
			connect(m_pCmbCB[i],	  SIGNAL(currentIndexChanged(int)),    this ,  SLOT(slot_Cmb_Changed_CB(int)));
	}


	slot_FaultTrigModeChange_CB(m_oCBOperateParas.m_nFaultTrigMode);
	slot_TestProcessChange_CB(m_oCBOperateParas.m_nTestProcCtrlMode);
	slot_CBSimulationChange_CB(m_oCBOperateParas.m_bCBSimulation);
	slot_CalcuModeChange_CB(m_oCBOperateParas.m_nCalMode);
	slot_PsuVzDefineChange_CB(m_oCBOperateParas.m_nVzDefine);
	slot_FaultAngleChange_CB(m_oCBOperateParas.m_nFaultIncMode);
}

//把外面的结构赋值过来
void CommonParasDialog::initPara_CB()
{
	m_oCBOperateParas.m_fMarginTime = m_pCBOperateParas->m_fMarginTime;
	m_oCBOperateParas.m_fPreFaultTime = m_pCBOperateParas->m_fPreFaultTime;
	m_oCBOperateParas.m_fPostFaultTime = m_pCBOperateParas->m_fPostFaultTime;
	m_oCBOperateParas.m_nFaultTrigMode = m_pCBOperateParas->m_nFaultTrigMode;
	m_oCBOperateParas.m_fTAfterAccTrig = m_pCBOperateParas->m_fTAfterAccTrig;
// 	m_oCBOperateParas.m_tGps.nHour = m_pCBOperateParas->m_tGps.nHour;
// 	m_oCBOperateParas.m_tGps.nMinutes = m_pCBOperateParas->m_tGps.nMinutes;
// 	m_oCBOperateParas.m_tGps.nSeconds = m_pCBOperateParas->m_tGps.nSeconds;
	m_oCBOperateParas.m_nK0CalMode = m_pCBOperateParas->m_nK0CalMode;
	m_oCBOperateParas.m_fK0Amp = m_pCBOperateParas->m_fK0Amp;
	m_oCBOperateParas.m_fK0Angle = m_pCBOperateParas->m_fK0Angle;
	m_oCBOperateParas.m_fIfh = m_pCBOperateParas->m_fIfh;
	m_oCBOperateParas.m_fPowerAngle = m_pCBOperateParas->m_fPowerAngle;
	m_oCBOperateParas.m_fRecloseTime = m_pCBOperateParas->m_fRecloseTime;
	m_oCBOperateParas.m_fAfterAcceTime = m_pCBOperateParas->m_fAfterAcceTime;
	m_oCBOperateParas.m_nPTPoint = m_pCBOperateParas->m_nPTPoint;
	m_oCBOperateParas.m_nCTPoint = m_pCBOperateParas->m_nCTPoint;
	m_oCBOperateParas.m_bCBSimulation = m_pCBOperateParas->m_bCBSimulation;
	m_oCBOperateParas.m_fCBTripTime = m_pCBOperateParas->m_fCBTripTime;
	m_oCBOperateParas.m_fCBCloseTime = m_pCBOperateParas->m_fCBCloseTime;
	m_oCBOperateParas.m_bIPlusDC = m_pCBOperateParas->m_bIPlusDC;
	m_oCBOperateParas.m_nFaultIncMode = m_pCBOperateParas->m_nFaultIncMode;
	m_oCBOperateParas.m_fFaultAngle = m_pCBOperateParas->m_fFaultAngle;
	m_oCBOperateParas.m_fFaultAng_0 = m_pCBOperateParas->m_fFaultAng_0;
	m_oCBOperateParas.m_nVzDefine = m_pCBOperateParas->m_nVzDefine;
	m_oCBOperateParas.m_fUxInput_Mag = m_pCBOperateParas->m_fUxInput_Mag;
	m_oCBOperateParas.m_fUxInput_Ang = m_pCBOperateParas->m_fUxInput_Ang;
	m_oCBOperateParas.m_fUxHigh = m_pCBOperateParas->m_fUxHigh;
	m_oCBOperateParas.m_fUxLow = m_pCBOperateParas->m_fUxLow;
	m_oCBOperateParas.m_fZs = m_pCBOperateParas->m_fZs;
	m_oCBOperateParas.m_fPhis = m_pCBOperateParas->m_fPhis;
	m_oCBOperateParas.m_nTestProcCtrlMode = m_pCBOperateParas->m_nTestProcCtrlMode;
	m_oCBOperateParas.m_nRXSelect  = m_pCBOperateParas->m_nRXSelect;
	m_oCBOperateParas.m_nCalMode = m_pCBOperateParas->m_nCalMode ;
	m_oCBOperateParas.m_nRecloseMode = m_pCBOperateParas->m_nRecloseMode ;	
	m_oCBOperateParas.m_nVzPhDefine = m_pCBOperateParas->m_nVzPhDefine;
}

// mym  2021-9-15 add
void CommonParasDialog::slot_EditValueChanged_CB()   
{
	QFloatLineEdit * pFloatLineEdit    =   qobject_cast<QFloatLineEdit*>(sender());

	// 2023-12-06 suyang 修改后保留三位小数
	float fValue =  pFloatLineEdit->text().toFloat();
	CString strText;
	strText.Format(_T("%.3f"),fValue);
	pFloatLineEdit->setText(strText);

	if (m_nInitFlag==2)
	{
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
	}
}

// mym  2021-9-15  add
void CommonParasDialog::slot_Cmb_Changed_CB(int nIndex)                    
{
	QValueComboBox * pValueComboBox    =  qobject_cast<QValueComboBox*>(sender());
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged  =  true;
}

void CommonParasDialog::initConnect_CB()
 {
	 connect(m_pCmbCB[0] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_FaultTrigModeChange_CB(int)));
	 connect(m_pCmbCB[3] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_TestProcessChange_CB(int)));
	 connect(m_pCmbCB[7] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_CalcuModeChange_CB(int)));
	 connect(m_pCmbCB[8] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_CBSimulationChange_CB(int)));
	 connect(m_pCmbCB[9] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_FaultAngleChange_CB(int)));
	 connect(m_pCmbCB[11] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_PsuVzDefineChange_CB(int)));

	connect(m_BtnOk, SIGNAL(clicked()),  this,  SLOT(slot_ClickOk_CB()));
	connect(m_BtnCancel, SIGNAL(clicked()),  this,  SLOT(slot_ClickCancel_CB()));
}

void CommonParasDialog::slot_ClickOk_CB()
{
	m_oCBOperateParas.m_fPreFaultTime = m_pEditCB[0]->text().toFloat();
	m_oCBOperateParas.m_fPostFaultTime = m_pEditCB[1]->text().toFloat();
	m_oCBOperateParas.m_fPostFaultTime = m_pEditCB[2]->text().toFloat();
	m_oCBOperateParas.m_fRecloseTime = m_pEditCB[3]->text().toFloat();
	m_oCBOperateParas.m_fTAfterAccTrig = m_pEditCB[4]->text().toFloat();
	m_oCBOperateParas.m_fK0Amp = m_pEditCB[5]->text().toFloat();
	m_oCBOperateParas.m_fK0Angle = m_pEditCB[6]->text().toFloat();
	m_oCBOperateParas.m_fZs = m_pEditCB[7]->text().toFloat();
	m_oCBOperateParas.m_fPhis = m_pEditCB[8]->text().toFloat();
	m_oCBOperateParas.m_fCBTripTime = m_pEditCB[9]->text().toFloat();//分.0时间
	m_oCBOperateParas.m_fCBTripTime = m_oCBOperateParas.m_fCBTripTime / 1000.0;
	m_oCBOperateParas.m_fCBCloseTime = m_pEditCB[10]->text().toFloat();//合闸时间
	m_oCBOperateParas.m_fCBCloseTime = m_oCBOperateParas.m_fCBCloseTime /1000.0;
	m_oCBOperateParas.m_fFaultAngle = m_pEditCB[11]->text().toFloat();//合闸角
	m_oCBOperateParas.m_fUxInput_Ang = m_pEditCB[12]->text().toFloat();//Uz相角(相对参考相)

	SetPara_CB();

	emit sig_ClickOk();
	close();
	m_nIsOK = 1;
}

void CommonParasDialog::slot_ClickCancel_CB()
{
	close();
	m_nIsOK = 2;
}


void CommonParasDialog::SetPara_CB()
{
	m_pCBOperateParas->m_fMarginTime = m_oCBOperateParas.m_fMarginTime;
	m_pCBOperateParas->m_fPreFaultTime = m_oCBOperateParas.m_fPreFaultTime;
	m_pCBOperateParas->m_fPostFaultTime = m_oCBOperateParas.m_fPostFaultTime;
	m_pCBOperateParas->m_nFaultTrigMode = m_oCBOperateParas.m_nFaultTrigMode;
	m_pCBOperateParas->m_fTAfterAccTrig = m_oCBOperateParas.m_fTAfterAccTrig;

// 	m_pCBOperateParas->m_tGps.nHour = m_oCBOperateParas.m_tGps.nHour;
// 	m_pCBOperateParas->m_tGps.nMinutes = m_oCBOperateParas.m_tGps.nMinutes;
// 	m_pCBOperateParas->m_tGps.nSeconds = m_oCBOperateParas.m_tGps.nSeconds;
	m_pCBOperateParas->m_nK0CalMode = m_oCBOperateParas.m_nK0CalMode;
	m_pCBOperateParas->m_fK0Amp = m_oCBOperateParas.m_fK0Amp;
	m_pCBOperateParas->m_fK0Angle = m_oCBOperateParas.m_fK0Angle;
	m_pCBOperateParas->m_fIfh = m_oCBOperateParas.m_fIfh;
	m_pCBOperateParas->m_fPowerAngle = m_oCBOperateParas.m_fPowerAngle;
	m_pCBOperateParas->m_fRecloseTime = m_oCBOperateParas.m_fRecloseTime;
	m_pCBOperateParas->m_fAfterAcceTime = m_oCBOperateParas.m_fAfterAcceTime;
	m_pCBOperateParas->m_nPTPoint = m_oCBOperateParas.m_nPTPoint;
	m_pCBOperateParas->m_nCTPoint = m_oCBOperateParas.m_nCTPoint;
	m_pCBOperateParas->m_bCBSimulation = m_oCBOperateParas.m_bCBSimulation;
	m_pCBOperateParas->m_fCBTripTime = m_oCBOperateParas.m_fCBTripTime;
	m_pCBOperateParas->m_fCBCloseTime = m_oCBOperateParas.m_fCBCloseTime;
	m_pCBOperateParas->m_bIPlusDC = m_oCBOperateParas.m_bIPlusDC;
	m_pCBOperateParas->m_nFaultIncMode = m_oCBOperateParas.m_nFaultIncMode;
	m_pCBOperateParas->m_fFaultAngle = m_oCBOperateParas.m_fFaultAngle;
	m_pCBOperateParas->m_fFaultAng_0 = m_oCBOperateParas.m_fFaultAng_0;
	m_pCBOperateParas->m_nVzDefine = m_oCBOperateParas.m_nVzDefine;
	m_pCBOperateParas->m_fUxInput_Mag = m_oCBOperateParas.m_fUxInput_Mag;
	m_pCBOperateParas->m_fUxInput_Ang = m_oCBOperateParas.m_fUxInput_Ang;
	m_pCBOperateParas->m_fUxHigh = m_oCBOperateParas.m_fUxHigh;
	m_pCBOperateParas->m_fUxLow = m_oCBOperateParas.m_fUxLow;
	m_pCBOperateParas->m_nRXSelect  = m_oCBOperateParas.m_nRXSelect;
	m_pCBOperateParas->m_fZs = m_oCBOperateParas.m_fZs;
	m_pCBOperateParas->m_fPhis = m_oCBOperateParas.m_fPhis;
	m_pCBOperateParas->m_nCalMode = m_oCBOperateParas.m_nCalMode;
	m_pCBOperateParas->m_nVzPhDefine = m_oCBOperateParas.m_nVzPhDefine;
	m_pCBOperateParas->m_nTestProcCtrlMode = m_oCBOperateParas.m_nTestProcCtrlMode;

	//两个值共用一个变量，这里进行区分；
	if (m_oCBOperateParas.m_nTestProcCtrlMode==0)
		m_pCBOperateParas->m_fPostFaultTime = m_pEditCB[1]->text().toFloat();
	else if (m_oCBOperateParas.m_nTestProcCtrlMode==1)
		m_pCBOperateParas->m_fPostFaultTime = m_pEditCB[2]->text().toFloat();

	m_pCBOperateParas->m_nRecloseMode = m_oCBOperateParas.m_nRecloseMode;
}


//搜索阻抗边界
void CommonParasDialog::initUI_DS()
{
	CTestDataTypeMngrConstGlobal::Create();

	m_TopLayout = new QGridLayout();

	label_PreFaultTime = new QLabel();
	label_PreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PreFaultTime->setText(/*QObject::tr("故障前时间(s):")*/g_sLangTxt_Native_PreFaultTime);
	m_TopLayout->addWidget(label_PreFaultTime,0,0);
	m_editPreFaultTime = new QFloatLineEdit(this);
	m_editPreFaultTime->InitCoverage(0,100);
	m_editPreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPreFaultTime,0,1);

	label_PostFaultTime = new QLabel();
	label_PostFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PostFaultTime->setText(/*QObject::tr("保护动作后持续时间(s):")*/g_sLangTxt_Native_DurProtTrip+tr("(s):"));
	m_TopLayout->addWidget(label_PostFaultTime,1,0);
	m_editPostFaultTime = new QFloatLineEdit(this);
	m_editPostFaultTime->InitCoverage(0,100);
	m_editPostFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPostFaultTime,1,1);

	label_Ifh = new QLabel();
	label_Ifh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Ifh->setText(/*QObject::tr("负荷电流(A):")*/g_sLangTxt_LoadI);
	m_TopLayout->addWidget(label_Ifh,2,0);
	m_editIfh = new QFloatLineEdit(this);
	m_editIfh->InitCoverage(0,999);
	m_editIfh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editIfh,2,1);

	label_PowerAngle = new QLabel();
	label_PowerAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PowerAngle->setText(/*QObject::tr("负荷功角(°):")*/g_sLangTxt_State_LoadAngle);
	m_TopLayout->addWidget(label_PowerAngle,3,0);
	m_editPowerAngle = new QFloatLineEdit(this);
	m_editPowerAngle->InitCoverage(0,360);
	m_editPowerAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPowerAngle,3,1);

	label_K0CalMode = new QLabel();
	label_K0CalMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_K0CalMode->setText(/*QObject::tr("零序补偿系数计算方式:")*/g_sLangTxt_Native_zeroseq_comp_calculat);
	m_TopLayout->addWidget(label_K0CalMode,4,0);
	m_CmbK0CalMode = new QValueComboBox(this);
	m_CmbK0CalMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("K0Mode")));
	m_CmbK0CalMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbK0CalMode,4,1);

	label_K0Amp = new QLabel();
	label_K0Amp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_K0Amp->setText(/*QObject::tr("零序补偿系数RE/RL:")*/g_sLangTxt_State_ZeroCoeff+tr("RE/RL:"));
	m_TopLayout->addWidget(label_K0Amp,5,0);
	m_editK0Amp = new QFloatLineEdit(this);
	m_editK0Amp->InitCoverage(0,999);
	m_editK0Amp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editK0Amp,5,1);

	label_K0Angle = new QLabel();
	label_K0Angle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_K0Angle->setText(/*QObject::tr("零序补偿系数XE/XL:")*/g_sLangTxt_State_ZeroCoeff+tr("XE/XL:"));
	m_TopLayout->addWidget(label_K0Angle,6,0);
	m_editK0Angle = new QFloatLineEdit(this);
	m_editK0Angle->InitCoverage(0,360);
	m_editK0Angle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editK0Angle,6,1);

	label_SearchMode = new QLabel();
	label_SearchMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_SearchMode->setText(/*QObject::tr("搜索方式:")*/g_sLangTxt_Native_search_mode);
	m_TopLayout->addWidget(label_SearchMode,7,0);
	m_CmbSearchMode = new QValueComboBox(this);
	m_CmbSearchMode->insertItem(0,/*QObject::tr("二分法")*/g_sLangTxt_Native_BinSearch);
	m_CmbSearchMode->insertItem(1,/*QObject::tr("单步逼近")*/g_sLangTxt_Native_StepApprox);
	m_CmbSearchMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbSearchMode,7,1);

	label_CalMode = new QLabel();
	label_CalMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CalMode->setText(/*QObject::tr("计算方式:")*/g_sLangTxt_State_CalcType);
	m_TopLayout->addWidget(label_CalMode,8,0);
	m_CmbCalMode = new QValueComboBox(this);
	m_CmbCalMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CalcuMode")));
	m_CmbCalMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbCalMode,8,1);

	label_Setting0 = new QLabel();
	label_Setting0->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Setting0->setText(/*QObject::tr("系统阻抗(Ω):")*/g_sLangTxt_Native_system_impedance);
	m_TopLayout->addWidget(label_Setting0,9,0);
	m_editSetting0 = new QFloatLineEdit(this);
	m_editSetting0->InitCoverage(0,100);
	m_editSetting0->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editSetting0,9,1);

	label_Setting1 = new QLabel();
	label_Setting1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Setting1->setText(/*QObject::tr("系统阻抗角(°):")*/g_sLangTxt_Native_system_impedance_angle);
	m_TopLayout->addWidget(label_Setting1,10,0);
	m_editSetting1 = new QFloatLineEdit(this);
	m_editSetting1->InitCoverage(0,360);
	m_editSetting1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editSetting1,10,1);

	label_PTPoint = new QLabel();
	label_PTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PTPoint->setText(/*QObject::tr("TV安装位置:")*/g_sLangTxt_Native_TVInstLoc);
	m_TopLayout->addWidget(label_PTPoint,0,2);
	m_CmbPTPoint = new QValueComboBox(this);
	m_CmbPTPoint->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PTPosition")));
	m_CmbPTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbPTPoint,0,3);

	label_CTPoint = new QLabel();
	label_CTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CTPoint->setText(/*QObject::tr("TA正极性:")*/g_sLangTxt_Native_PosPolTA);
	m_TopLayout->addWidget(label_CTPoint,1,2);
	m_CmbCTPoint = new QValueComboBox(this);
	m_CmbCTPoint->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CTPos")));
	m_CmbCTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbCTPoint,1,3);

	label_CBSimulation = new QLabel();
	label_CBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBSimulation->setText(/*QObject::tr("断路器模拟:")*/g_sLangTxt_Native_CBsim+tr(":"));
	m_TopLayout->addWidget(label_CBSimulation,2,2);
	m_CmbCBSimulation = new QValueComboBox(this);
	m_CmbCBSimulation->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CBSimulation")));
	m_CmbCBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbCBSimulation,2,3);

	label_CBTripTime = new QLabel();
	label_CBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBTripTime->setText(/*QObject::tr("分闸时间(ms):")*/g_sLangTxt_Native_TripTime+tr("(ms):"));
	m_TopLayout->addWidget(label_CBTripTime,3,2);
	m_editCBTripTime = new QFloatLineEdit(this);
	m_editCBTripTime->InitCoverage(0,999999);
	m_editCBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editCBTripTime,3,3);

	label_CBCloseTime = new QLabel();
	label_CBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBCloseTime->setText(/*QObject::tr("分闸时间(ms):")*/g_sLangTxt_Native_CloseTime+tr("(ms):"));
	m_TopLayout->addWidget(label_CBCloseTime,4,2);
	m_editCBCloseTime = new QFloatLineEdit(this);
	m_editCBCloseTime->InitCoverage(0,999999);
	m_editCBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editCBCloseTime,4,3);

	label_IPlusDC = new QLabel();
	label_IPlusDC->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_IPlusDC->setText(/*QObject::tr("是否叠加非周期分量:")*/g_sLangTxt_Native_superimpose_ornot);
	m_TopLayout->addWidget(label_IPlusDC,5,2);
	m_CmbIPlusDC = new QValueComboBox(this);
	m_CmbIPlusDC->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultId")));
	m_CmbIPlusDC->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbIPlusDC,5,3);

	label_FaultIncMode = new QLabel();
	label_FaultIncMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_FaultIncMode->setText(/*QObject::tr("合闸角方式:")*/g_sLangTxt_Native_closingangle_way);
	m_TopLayout->addWidget(label_FaultIncMode,6,2);
	m_CmbFaultIncMode = new QValueComboBox(this);
	m_CmbFaultIncMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultAngMode")));
	m_CmbFaultIncMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbFaultIncMode,6,3);

	label_FaultAngle = new QLabel();
	label_FaultAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_FaultAngle->setText(/*QObject::tr("合闸角(°):")*/g_sLangTxt_Native_closingangle);
	m_TopLayout->addWidget(label_FaultAngle,7,2);
	m_editFaultAngle = new QFloatLineEdit(this);
	m_editFaultAngle->InitCoverage(-360,360);
	m_editFaultAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editFaultAngle,7,3);

	label_VzDefine = new QLabel();
	label_VzDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_VzDefine->setText(/*QObject::tr("抽取电压输出定义:")*/g_sLangTxt_Native_extractvol_outputdef);
	m_TopLayout->addWidget(label_VzDefine,8,2);
	m_CmbVzDefine = new QValueComboBox(this);
	m_CmbVzDefine->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PsuVzDefine")));
	m_CmbVzDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbVzDefine,8,3);

	label_VzPhDefine = new QLabel();
	label_VzPhDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_VzPhDefine->setText(/*QObject::tr("抽取电压参考相定义:")*/g_sLangTxt_Native_extractvol_refphasedef);
	m_TopLayout->addWidget(label_VzPhDefine,9,2);
	m_CmbVzPhDefine = new QValueComboBox(this);
	m_CmbVzPhDefine->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PsuVzRefPhase")));
	m_CmbVzPhDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbVzPhDefine,9,3);

	label_VzPh = new QLabel();
	label_VzPh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_VzPh->setText(/*QObject::tr("抽取电压相角(相对参考相):")*/g_sLangTxt_Native_extractvol_phaseangle);
	m_TopLayout->addWidget(label_VzPh,10,2);
	m_editVzPh = new QFloatLineEdit(this);
	m_editVzPh->InitCoverage(0,360);
	m_editVzPh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editVzPh,10,3);


	resize(800 *g_dUIShowCoef,  320); //切换零序补偿系数计算方式时，窗口大小会发生变化，将该窗口适当变大一些
	
}

void CommonParasDialog::CopyPartForDS( tmt_DistanceSearchParas &Para_A,tmt_DistanceSearchParas &Para_B )
{
	Para_B.m_fPreFaultTime = Para_A.m_fPreFaultTime;
	Para_B.m_fPostFaultTime = Para_A.m_fPostFaultTime;

	Para_B.m_fIfh = Para_A.m_fIfh;
	Para_B.m_fPowerAngle = Para_A.m_fPowerAngle;

	Para_B.m_nK0CalMode = Para_A.m_nK0CalMode;
	Para_B.m_fK0Amp = Para_A.m_fK0Amp;
	Para_B.m_fK0Angle = Para_A.m_fK0Angle;

	Para_B.m_nSearchMode = Para_A.m_nSearchMode;
	Para_B.m_nCalMode = Para_A.m_nCalMode;

	Para_B.m_fSetting[0] = Para_A.m_fSetting[0];
	Para_B.m_fSetting[1] = Para_A.m_fSetting[1];

	Para_B.m_nPTPoint = Para_A.m_nPTPoint;
	Para_B.m_nCTPoint = Para_A.m_nCTPoint;
	
	Para_B.m_bCBSimulation = Para_A.m_bCBSimulation;
	Para_B.m_fCBTripTime = Para_A.m_fCBTripTime;
	Para_B.m_fCBCloseTime = Para_A.m_fCBCloseTime;

	Para_B.m_bIPlusDC = Para_A.m_bIPlusDC;
	Para_B.m_nFaultIncMode = Para_A.m_nFaultIncMode;
	Para_B.m_fFaultAngle = Para_A.m_fFaultAngle;

	Para_B.m_nVzDefine = Para_A.m_nVzDefine;
	Para_B.m_nVzPhDefine = Para_A.m_nVzPhDefine;
	Para_B.m_fUxInput_Ang = Para_A.m_fUxInput_Ang;
}

void CommonParasDialog::initData_DS()
{
	m_editPreFaultTime->setText(QString::number(m_DSParas.m_fPreFaultTime, 'f', 3));
	m_editPostFaultTime->setText(QString::number(m_DSParas.m_fPostFaultTime, 'f', 3));
	m_editIfh->setText(QString::number(m_DSParas.m_fIfh, 'f', 3));
	m_editPowerAngle->setText(QString::number(m_DSParas.m_fPowerAngle, 'f', 3));

	m_CmbK0CalMode->SetIndex(&m_DSParas.m_nK0CalMode);
	m_editK0Amp->setText(QString::number(m_DSParas.m_fK0Amp, 'f', 3));
	m_editK0Angle->setText(QString::number(m_DSParas.m_fK0Angle, 'f', 3));

	m_CmbSearchMode->SetIndex((int*)(&m_DSParas.m_nSearchMode));
	m_CmbCalMode->SetIndex((int*)(&m_DSParas.m_nCalMode));

	m_editSetting0->setText(QString::number(m_DSParas.m_fSetting[0], 'f', 3));
	m_editSetting1->setText(QString::number(m_DSParas.m_fSetting[1], 'f', 3));

	m_CmbPTPoint->SetIndex((int*)(&m_DSParas.m_nPTPoint));
	m_CmbCTPoint->SetIndex(&m_DSParas.m_nCTPoint);

	m_CmbCBSimulation->SetIndex(&m_DSParas.m_bCBSimulation);
	m_editCBTripTime->setText(QString::number(m_DSParas.m_fCBTripTime * 1000, 'f', 3));
	m_editCBCloseTime->setText(QString::number(m_DSParas.m_fCBCloseTime * 1000, 'f', 3));

	m_CmbIPlusDC->SetIndex((int*)(&m_DSParas.m_bIPlusDC));
	m_CmbFaultIncMode->SetIndex(&m_DSParas.m_nFaultIncMode);
	m_editFaultAngle->setText(QString::number(m_DSParas.m_fFaultAngle, 'f', 3));

	m_CmbVzDefine->SetIndex(&m_DSParas.m_nVzDefine);
	m_CmbVzPhDefine->SetIndex(&m_DSParas.m_nVzPhDefine);
	m_editVzPh->setText(QString::number(m_DSParas.m_fUxInput_Ang, 'f', 3));

	slot_VzDefineChange(0);
	slot_CBSimulationChange(0);
	slot_FaultIncModeChange(0);
	slot_CalModeChange(0);
}

void CommonParasDialog::initConnect_DS()
{
	connect(m_CmbCBSimulation,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CBSimulationChange(int)));
	connect(m_CmbVzDefine,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_VzDefineChange(int)));
	connect(m_CmbFaultIncMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultIncModeChange(int)));
	connect(m_CmbCalMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CalModeChange(int)));
	connect(m_CmbK0CalMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_K0CalModeChange(int)));

	  	//2023-11-08 suyang add 保留三位小数
	connect( m_editPreFaultTime,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editPostFaultTime,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editIfh,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editPowerAngle,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editK0Amp,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editK0Angle,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editSetting0,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editSetting1,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editCBCloseTime,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editFaultAngle,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editVzPh,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editCBTripTime,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));

	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk_DS()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel()));
}

void CommonParasDialog::slot_EditValueChanged_DS()
{
	QFloatLineEdit * pFloatLineEdit = qobject_cast<QFloatLineEdit*>(sender());
	// 2023-12-08 suyang 修改后保留三位小数
	float fValue =  pFloatLineEdit->text().toFloat();
	CString strText;
	strText.Format(_T("%.3f"),fValue);
	pFloatLineEdit->setText(strText);

}

void CommonParasDialog::slot_ClickOk_DS()
{
	JudgeModifyPara(m_DSParas.m_fPreFaultTime,m_editPreFaultTime->text().toFloat());
	m_DSParas.m_fPreFaultTime = m_editPreFaultTime->text().toFloat();
	JudgeModifyPara(m_DSParas.m_fPostFaultTime,m_editPostFaultTime->text().toFloat());
	m_DSParas.m_fPostFaultTime = m_editPostFaultTime->text().toFloat();	

	JudgeModifyPara(m_DSParas.m_fIfh,m_editIfh->text().toFloat());
	m_DSParas.m_fIfh = m_editIfh->text().toFloat();
	JudgeModifyPara(m_DSParas.m_fPowerAngle,m_editPowerAngle->text().toFloat());
	m_DSParas.m_fPowerAngle = m_editPowerAngle->text().toFloat();

	JudgeModifyPara(m_DSParas.m_fK0Amp,m_editK0Amp->text().toFloat());
	m_DSParas.m_fK0Amp = m_editK0Amp->text().toFloat();
	JudgeModifyPara(m_DSParas.m_fK0Angle,m_editK0Angle->text().toFloat());
	m_DSParas.m_fK0Angle = m_editK0Angle->text().toFloat();

	JudgeModifyPara(m_DSParas.m_fSetting[0],m_editSetting0->text().toFloat());
	m_DSParas.m_fSetting[0] = m_editSetting0->text().toFloat();
	JudgeModifyPara(m_DSParas.m_fSetting[1],m_editSetting1->text().toFloat());
	m_DSParas.m_fSetting[1] = m_editSetting1->text().toFloat();

	JudgeModifyPara(m_DSParas.m_fCBTripTime,m_editCBTripTime->text().toFloat() / 1000.0);
	m_DSParas.m_fCBTripTime = m_editCBTripTime->text().toFloat();
	m_DSParas.m_fCBTripTime = m_DSParas.m_fCBTripTime / 1000.0;
	JudgeModifyPara(m_DSParas.m_fCBCloseTime,m_editCBCloseTime->text().toFloat() / 1000.0);
	m_DSParas.m_fCBCloseTime = m_editCBCloseTime->text().toFloat();
	m_DSParas.m_fCBCloseTime = m_DSParas.m_fCBCloseTime / 1000.0;

	JudgeModifyPara(m_DSParas.m_fFaultAngle,m_editFaultAngle->text().toFloat());
	m_DSParas.m_fFaultAngle = m_editFaultAngle->text().toFloat();

	JudgeModifyPara(m_DSParas.m_fUxInput_Ang,m_editVzPh->text().toFloat());
	m_DSParas.m_fUxInput_Ang = m_editVzPh->text().toFloat();

	CopyPartForDS(m_DSParas,*m_pDSParas);

	emit sig_ClickOk();
	close();
	m_nIsOK = 1;
}

void CommonParasDialog::slot_FaultIncModeChange( int )
{
	int index = m_CmbFaultIncMode->currentIndex();
	if (index == 0)
	{
		m_editFaultAngle->setEnabled(false);
	}
	else
	{
		m_editFaultAngle->setEnabled(true);
	}
}


void CommonParasDialog::slot_CalModeChange( int )
{
	int index = m_CmbCalMode->currentIndex();
	if (index != 2)
	{
		m_editSetting1->setEnabled(false);
		m_editSetting0->setEnabled(false);
	}
	else
	{
		m_editSetting1->setEnabled(true);
		m_editSetting0->setEnabled(true);
	}
}

void CommonParasDialog::slot_K0CalModeChange( int )
{
	int index = m_CmbK0CalMode->currentIndex();
	if (index == 0)
	{
		label_K0Amp->setText(/*QObject::tr("零序补偿系数|K0|:")*/g_sLangTxt_State_ZeroCoeff+tr("|K0|:"));
		label_K0Angle->setText(/*QObject::tr("零序补偿系数|Phi(K0)|:")*/g_sLangTxt_State_ZeroCoeff+tr("|Phi(K0)|:"));
	}
	else if (index == 1)
	{
		label_K0Amp->setText(/*QObject::tr("零序补偿系数RE/RL:")*/g_sLangTxt_State_ZeroCoeff+tr("RE/RL:"));
		label_K0Angle->setText(/*QObject::tr("零序补偿系数XE/XL:")*/g_sLangTxt_State_ZeroCoeff+tr("XE/XL:"));
	}
	else
	{
		label_K0Amp->setText(/*QObject::tr("零序补偿系数|Z0/Z1|:")*/g_sLangTxt_State_ZeroCoeff+tr("|Z0/Z1|:"));
		label_K0Angle->setText(/*QObject::tr("零序补偿系数|Phi(Z0/Z1)|:")*/g_sLangTxt_State_ZeroCoeff+tr("|Phi(Z0/Z1)|:"));
	}
}


void stt_copy_commparas_cb(tmt_CBOperateParas &Para_A,  tmt_CBOperateParas &Para_B)
{
	Para_A.m_fMarginTime = Para_B.m_fMarginTime;
	Para_A.m_fPreFaultTime = Para_B.m_fPreFaultTime;
	Para_A.m_fPostFaultTime = Para_B.m_fPostFaultTime;
	Para_A.m_nFaultTrigMode = Para_B.m_nFaultTrigMode;
	Para_A.m_fTAfterAccTrig = Para_B.m_fTAfterAccTrig;

	Para_A.m_tGps.nHour = Para_B.m_tGps.nHour;
	Para_A.m_tGps.nMinutes = Para_B.m_tGps.nMinutes;
	Para_A.m_tGps.nSeconds = Para_B.m_tGps.nSeconds;
	Para_A.m_nK0CalMode = Para_B.m_nK0CalMode;
	Para_A.m_fK0Amp = Para_B.m_fK0Amp;
	Para_A.m_fK0Angle = Para_B.m_fK0Angle;
	Para_A.m_fIfh = Para_B.m_fIfh;
	Para_A.m_fPowerAngle = Para_B.m_fPowerAngle;
	Para_A.m_fRecloseTime = Para_B.m_fRecloseTime;
	Para_A.m_fAfterAcceTime = Para_B.m_fAfterAcceTime;
	Para_A.m_nPTPoint = Para_B.m_nPTPoint;
	Para_A.m_nCTPoint = Para_B.m_nCTPoint;
	Para_A.m_bCBSimulation = Para_B.m_bCBSimulation;
	Para_A.m_fCBTripTime = Para_B.m_fCBTripTime;
	Para_A.m_fCBCloseTime = Para_B.m_fCBCloseTime;
	Para_A.m_bIPlusDC = Para_B.m_bIPlusDC;
	Para_A.m_nFaultIncMode = Para_B.m_nFaultIncMode;
	Para_A.m_fFaultAngle = Para_B.m_fFaultAngle;
	Para_A.m_fFaultAng_0 = Para_B.m_fFaultAng_0;
	Para_A.m_nVzDefine = Para_B.m_nVzDefine;
	Para_A.m_fUxInput_Mag = Para_B.m_fUxInput_Mag;
	Para_A.m_fUxInput_Ang = Para_B.m_fUxInput_Ang;
	Para_A.m_fUxHigh = Para_B.m_fUxHigh;
	Para_A.m_fUxLow = Para_B.m_fUxLow;
	Para_A.m_nRXSelect  = Para_B.m_nRXSelect;
	Para_A.m_fZs = Para_B.m_fZs;
	Para_A.m_fPhis = Para_B.m_fPhis;
	Para_A.m_nCalMode = Para_B.m_nCalMode;
	Para_A.m_nVzPhDefine = Para_B.m_nVzPhDefine;
	Para_A.m_nTestProcCtrlMode = Para_B.m_nTestProcCtrlMode;
	Para_A.m_nRecloseMode = Para_B.m_nRecloseMode;
}

void stt_copy_commparas_re(tmt_RecloseAccParasEx &Para_A, tmt_RecloseAccParasEx &Para_B)
{
	Para_A.m_bSelected = Para_B.m_bSelected;
	Para_A.m_fTAfterTrig[0] = Para_B.m_fTAfterTrig[0];
	Para_A.m_fTAfterTrig[1] = Para_B.m_fTAfterTrig[1];
	Para_A.m_fTSetting[0] = Para_B.m_fTSetting[0];
	Para_A.m_fTSetting[1] = Para_B.m_fTSetting[1];

	Para_A.m_fMarginTime = Para_B.m_fMarginTime;
	Para_A.m_fPreFaultTime = Para_B.m_fPreFaultTime;
	Para_A.m_fPostFaultTime = Para_B.m_fPostFaultTime;
	Para_A.m_nFaultTrigMode = Para_B.m_nFaultTrigMode;
	//Para_A.m_fTAfterAccTrig = Para_B.m_fTAfterAccTrig;

	Para_A.m_tGps.nHour = Para_B.m_tGps.nHour;
	Para_A.m_tGps.nMinutes = Para_B.m_tGps.nMinutes;
	Para_A.m_tGps.nSeconds = Para_B.m_tGps.nSeconds;
	Para_A.m_nK0CalMode = Para_B.m_nK0CalMode;
	Para_A.m_fK0Amp = Para_B.m_fK0Amp;
	Para_A.m_fK0Angle = Para_B.m_fK0Angle;
	Para_A.m_fIfh = Para_B.m_fIfh;
	Para_A.m_fPowerAngle = Para_B.m_fPowerAngle;
	Para_A.m_fRecloseTime = Para_B.m_fRecloseTime;
	Para_A.m_fAfterAcceTime = Para_B.m_fAfterAcceTime;
	Para_A.m_nPTPoint = Para_B.m_nPTPoint;
	Para_A.m_nCTPoint = Para_B.m_nCTPoint;
	Para_A.m_bCBSimulation = Para_B.m_bCBSimulation;
	Para_A.m_fCBTripTime = Para_B.m_fCBTripTime;
	Para_A.m_fCBCloseTime = Para_B.m_fCBCloseTime;
	Para_A.m_bIPlusDC = Para_B.m_bIPlusDC;
	Para_A.m_nFaultIncMode = Para_B.m_nFaultIncMode;
	Para_A.m_fFaultAngle = Para_B.m_fFaultAngle;
	Para_A.m_fFaultAng_0 = Para_B.m_fFaultAng_0;
	Para_A.m_nVzDefine = Para_B.m_nVzDefine;
	Para_A.m_fUxInput_Mag = Para_B.m_fUxInput_Mag;
	Para_A.m_fUxInput_Ang = Para_B.m_fUxInput_Ang;
	Para_A.m_fUxHigh = Para_B.m_fUxHigh;
	Para_A.m_fUxLow = Para_B.m_fUxLow;
	Para_A.m_nRXSelect  = Para_B.m_nRXSelect;
	Para_A.m_fZs = Para_B.m_fZs;
	Para_A.m_fPhis = Para_B.m_fPhis;
	Para_A.m_nCalMode = Para_B.m_nCalMode;
	Para_A.m_nVzPhDefine = Para_B.m_nVzPhDefine;
	//Para_A.m_nTestProcCtrlMode = Para_B.m_nTestProcCtrlMode;
	//Para_A.m_nRecloseMode = Para_B.m_nRecloseMode;
}

void stt_copy_commparas_volt(tmt_VolInverseTimeParasEx &Para_A,  tmt_VolInverseTimeParasEx &Para_B)
{
	memcpy(	Para_A.m_pszFaultVol , Para_B.m_pszFaultVol, PARAS_RSLT_EXPR_LEN);

// 	 Para_A.m_oSetting.m_fVp = Para_B.m_oSetting.m_fVp;
// 	 Para_A.m_oSetting.m_fD = Para_B.m_oSetting.m_fD;
// 	 Para_A.m_oSetting.m_fK = Para_B.m_oSetting.m_fK;
// 	 Para_A.m_oSetting.m_fA_Td = Para_B.m_oSetting.m_fA_Td;
// 	 Para_A.m_oSetting.m_fB = Para_B.m_oSetting.m_fB;
// 	 Para_A.m_oSetting.m_fC = Para_B.m_oSetting.m_fC;
// 	 Para_A.m_oSetting.m_fE = Para_B.m_oSetting.m_fE;
// 	 Para_A.m_oSetting.m_fP = Para_B.m_oSetting.m_fP;
// 	 Para_A.m_oSetting.m_fM = Para_B.m_oSetting.m_fM;

	//通用参数
	Para_A. m_fPreFaultTime = Para_B.m_fPreFaultTime;//故障前时间
	Para_A. m_nCTPoint   = Para_B.m_nCTPoint;
	Para_A. m_nFaultType = Para_B.m_nFaultType;

	//界面参数
	Para_A. m_fPreFaultVol = Para_B.m_fPreFaultVol;//故障前电压
	Para_A. m_fPreFaultCur = Para_B.m_fPreFaultCur;//故障前电流
	Para_A. m_fPreFaultAngle = Para_B.m_fPreFaultAngle;//故障前角差

	Para_A. m_fFaultVol = Para_B.m_fFaultVol;//故障电压
	Para_A. m_fFaultCur = Para_B.m_fFaultCur;//故障电流
	Para_A. m_fFaultAngle = Para_B.m_fFaultAngle;//故障角差

	Para_A. m_fSettingFaultTime = Para_B.m_fSettingFaultTime;//整定动作时间
	Para_A. m_fFaultTimeMargin = Para_B.m_fFaultTimeMargin;//故障时间裕度

	//开关量
	::memcpy(Para_A.m_binIn,  Para_B.m_binIn, sizeof(tmt_BinaryIn) * MAX_BINARYIN_COUNT);
	::memcpy(Para_A.m_binInEx,  Para_B.m_binInEx, sizeof(tmt_BinaryIn) * MAX_ExBINARY_COUNT);
	::memcpy(Para_A.m_binOut,  Para_B.m_binOut, sizeof(tmt_BinaryOut) * 2 *  MAX_BINARYOUT_COUNT);
	::memcpy(Para_A.m_binOutEx,  Para_B.m_binOutEx, sizeof(tmt_BinaryOut) * 2 * MAX_ExBINARY_COUNT);

	Para_A.m_nBinLogic = Para_B.m_nBinLogic;			//0-或 1-与
}

void CommonParasDialog::initUI_Re() //重合闸 mym 2021-8-11;
{
	CTestDataTypeMngrConstGlobal::Create();

	m_TopLayout = new QGridLayout();

	label_Re[0] = new QLabel();
	label_Re[0]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[0]->setText(/*QObject::tr("故障前时间(s):")*/g_sLangTxt_Native_PreFaultTimes);
	m_TopLayout->addWidget(label_Re[0],  0,  0);
	m_pEditRe[0] = new QFloatLineEdit(this);
	m_pEditRe[0] ->InitCoverage(0,100);
	m_pEditRe[0] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[0] ,  0,  1);

	label_Re[1] = new QLabel();
	label_Re[1]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[1]->setText(/*QObject::tr("故障时间裕度(s):")*/g_sLangTxt_Native_faultTimeMargin);
	m_TopLayout->addWidget(label_Re[1],   1,  0);
	m_pEditRe[1] = new QFloatLineEdit(this);
	m_pEditRe[1] ->InitCoverage(0,  100);
	m_pEditRe[1] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[1] ,   1,  1);


	label_Re[2] = new QLabel();
	label_Re[2]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[2]->setText(/*QObject::tr("保护动作后持续时间(s):")*/g_sLangTxt_Native_DurProtTrip+tr("(s):"));
	m_TopLayout->addWidget(label_Re[2],    2,  0);
	m_pEditRe[2] = new QFloatLineEdit(this);
	m_pEditRe[2] ->InitCoverage(0,  100);
	m_pEditRe[2] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[2] ,   2,  1);

	label_Re[3] = new QLabel();
	label_Re[3]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[3]->setText(/*QObject::tr("故障触发方式:")*/g_sLangTxt_Native_FaultTrigMethod+tr(":"));
	m_TopLayout->addWidget(label_Re[3],    3,  0);
	m_pCmbRe[0] = new QValueComboBox(this);
	m_pCmbRe[0]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultTrigMode")));//好了
	m_pCmbRe[0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbRe[0],   3,  1);

	m_pCmbRe[1] = NULL;
/*
	label_Re[4] = new QLabel();
	label_Re[4]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[4]->setText(QObject::tr("开入量触发通道:"));
	m_TopLayout->addWidget(label_Re[4],   4,  0);
	m_pCmbRe[1] = new QValueComboBox(this);
	m_pCmbRe[1]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("InputChannel")));//好了
	m_pCmbRe[1]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbRe[1],  4, 1);
*/

	label_Re[5] = new QLabel();
	label_Re[5]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	label_Re[5]->setText(/*QObject::tr("TV 安装位置:")*/g_sLangTxt_Native_TVInstLoc+tr(":"));
	m_TopLayout->addWidget(label_Re[5],    5,  0);
	m_pCmbRe[2] = new QValueComboBox(this);
	m_pCmbRe[2]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PTPosition")));//好了
	m_pCmbRe[2]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbRe[2],   5,  1);

	label_Re[6] = new QLabel();
	label_Re[6]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[6]->setText(/*QObject::tr("TA 正极性:")*/g_sLangTxt_Native_PosPolTA+tr(":"));
	m_TopLayout->addWidget(label_Re[6],   6,  0);
	m_pCmbRe[3] = new QValueComboBox(this);
	m_pCmbRe[3]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CTPos")));//好了
	m_pCmbRe[3]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbRe[3],  6, 1);


	label_Re[7] = new QLabel();
	label_Re[7]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[7]->setText(/*QObject::tr("负荷电流(A):")*/g_sLangTxt_LoadI);
	m_TopLayout->addWidget(label_Re[7],   7,  0);
	m_pEditRe[3] = new QFloatLineEdit(this);
	m_pEditRe[3] ->InitCoverage(0,  1);
	m_pEditRe[3] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[3] ,   7,  1);

	label_Re[8] = new QLabel();
	label_Re[8]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[8]->setText(/*QObject::tr("负荷功角(°):")*/g_sLangTxt_State_LoadAngle);
	m_TopLayout->addWidget(label_Re[8],   8,  0);
	m_pEditRe[4] = new QFloatLineEdit(this);
	m_pEditRe[4] ->InitCoverage(0,  100);
	m_pEditRe[4] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[4] ,   8,  1);

	label_Re[9] = new QLabel();
	label_Re[9]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[9]->setText(/*QObject::tr("断路器模拟:")*/g_sLangTxt_Native_CBsim+tr(":"));
	m_TopLayout->addWidget(label_Re[9],   9,  0);
	m_pCmbRe[4] = new QValueComboBox(this);
	m_pCmbRe[4]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CBSimulation")));//好了
	m_pCmbRe[4]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbRe[4],  9,  1);

	label_Re[10] = new QLabel();
	label_Re[10]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[10]->setText(/*QObject::tr("分闸时间(ms):")*/g_sLangTxt_Native_TripTime+tr("(ms):"));
	m_TopLayout->addWidget(label_Re[10],   10,  0);
	m_pEditRe[5] = new QFloatLineEdit(this);
	m_pEditRe[5] ->InitCoverage(0,  100);
	m_pEditRe[5] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[5] ,   10,  1);

	label_Re[11] = new QLabel();
	label_Re[11]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Re[11]->setText(/*QObject::tr("分闸时间(ms):")*/g_sLangTxt_Native_CloseTime+tr("(ms):"));
	m_TopLayout->addWidget(label_Re[11],   11,  0);
	m_pEditRe[6] = new QFloatLineEdit(this);
	m_pEditRe[6] ->InitCoverage(0,  100);
	m_pEditRe[6] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditRe[6] ,   11,  1);

}

void CommonParasDialog::initData_Re()// 重合闸 mym 2021-8-11;
{
	int nComboCnt = 5;
	m_pCmbRe[0]->SetIndex(&m_oRecloseAccParas.m_nFaultTrigMode);
	//m_pCmbRe[1]->SetIndex(&m_oRecloseAccParas.m_nPTPoint);//这里少个开入量触发通道；
	m_pCmbRe[2]->SetIndex(&m_oRecloseAccParas.m_nPTPoint);
	m_pCmbRe[3]->SetIndex(&m_oRecloseAccParas.m_nCTPoint);
	m_pCmbRe[4]->SetIndex(&m_oRecloseAccParas.m_bCBSimulation);


	slot_CBSimulationChange_Re((int)m_oRecloseAccParas.m_bCBSimulation);
	slot_FaultTrigModeChange_Re(m_oRecloseAccParas.m_nFaultTrigMode);

	int nEditCnt  = 7;
	label_Re[2]->setVisible(false);//重合闸后加速,删除此参数
	m_pEditRe[2]->setVisible(false);//重合闸后加速,删除此参数
	m_pEditRe[0]->setText(QString::number(m_oRecloseAccParas.m_fPreFaultTime, 'f', 3));
	m_pEditRe[1]->setText(QString::number(m_oRecloseAccParas.m_fMarginTime, 'f', 3));
//	m_pEditRe[2]->setText(QString::number(m_oRecloseAccParas.m_fTAfterTrig[0], 'f', 3));
	m_pEditRe[3]->setText(QString::number(m_oRecloseAccParas.m_fIfh, 'f', 3));
	m_pEditRe[4]->setText(QString::number(m_oRecloseAccParas.m_fPowerAngle, 'f', 3));
	m_pEditRe[5]->setText(QString::number(m_oRecloseAccParas.m_fCBTripTime * 1000, 'f', 3));
	m_pEditRe[6]->setText(QString::number(m_oRecloseAccParas.m_fCBCloseTime * 1000, 'f', 3));


	//连接起来 槽
	for (int i = 0;  i < nEditCnt;  i++)
		connect(m_pEditRe[i],	SIGNAL(/*textChanged(QString )*/editingFinished()),  this , SLOT(slot_EditValueChanged_Re(/*QString*/ )));//名称//2023-11-08 suyang 触发信号改为editingFinished()
	
	for (int i = 0;  i  < nComboCnt;  i++)
	{
		if (m_pCmbRe[i])
			connect(m_pCmbRe[i],	 SIGNAL(currentIndexChanged(int)),   this ,SLOT(slot_Cmb_Changed_Re(int)));//故障类型
	}
}

void CommonParasDialog::slot_EditValueChanged_Re(/*QString strValue*/)
{
	QFloatLineEdit * pFloatLineEdit = qobject_cast<QFloatLineEdit*>(sender());
	// 2023-12-08 suyang 修改后保留三位小数
	float fValue =  pFloatLineEdit->text().toFloat();
	CString strText;
	strText.Format(_T("%.3f"),fValue);
	pFloatLineEdit->setText(strText);

	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}

void CommonParasDialog::slot_Cmb_Changed_Re(int nIndex)
{
	QValueComboBox * pValueComboBox = qobject_cast<QValueComboBox*>(sender());
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}

void CommonParasDialog::initPara_Re()//重合闸 mym 2021-8-11;
{
	m_oRecloseAccParas.m_fPreFaultTime = m_pRecloseAccParas->m_fPreFaultTime;      //故障前时间
	m_oRecloseAccParas.m_fMarginTime = m_pRecloseAccParas->m_fMarginTime;            //故障时间裕度
	m_oRecloseAccParas.m_fTAfterTrig[0] = m_pRecloseAccParas->m_fTAfterTrig[0];  //保护动作后持续时间
	m_oRecloseAccParas.m_fTAfterTrig[1] = m_pRecloseAccParas->m_fTAfterTrig[1];  //保护动作后持续时间
	m_oRecloseAccParas.m_nFaultTrigMode = m_pRecloseAccParas->m_nFaultTrigMode; //故障触发方式

	//开入量触发通道
	m_oRecloseAccParas.m_nPTPoint = m_pRecloseAccParas->m_nPTPoint;                      //TV安装位置
	m_oRecloseAccParas.m_nCTPoint = m_pRecloseAccParas->m_nCTPoint;                      // TA正极性
	m_oRecloseAccParas.m_fIfh = m_pRecloseAccParas->m_fIfh;                                          //负荷电流
	m_oRecloseAccParas.m_fPowerAngle = m_pRecloseAccParas->m_fPowerAngle;          //负荷功角
	m_oRecloseAccParas.m_bCBSimulation = m_pRecloseAccParas->m_bCBSimulation;    //断路器模拟
	m_oRecloseAccParas.m_fCBTripTime = m_pRecloseAccParas->m_fCBTripTime;            //分闸时间
	m_oRecloseAccParas.m_fCBCloseTime = m_pRecloseAccParas->m_fCBCloseTime;     //合闸时间
}

void CommonParasDialog::initConnect_Re()
{
	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk_Re()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel_Re()));

	connect(m_pCmbRe[4], SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CBSimulationChange_Re(int)));
	connect(m_pCmbRe[0], SIGNAL(currentIndexChanged(int)), this, SLOT(slot_FaultTrigModeChange_Re(int)));
}

void CommonParasDialog::SetPara_Re()
{
	m_pRecloseAccParas->m_fPreFaultTime  = m_oRecloseAccParas.m_fPreFaultTime;      //故障前时间
	m_pRecloseAccParas->m_fMarginTime  = m_oRecloseAccParas.m_fMarginTime;            //故障时间裕度
	m_pRecloseAccParas->m_fTAfterTrig[0]  = m_oRecloseAccParas.m_fTAfterTrig[0];  //保护动作后持续时间
	m_pRecloseAccParas->m_fTAfterTrig[1]  = m_oRecloseAccParas.m_fTAfterTrig[1];  //保护动作后持续时间
	m_pRecloseAccParas->m_nFaultTrigMode  = m_oRecloseAccParas.m_nFaultTrigMode; //故障触发方式

	//开入量触发通道???
	m_pRecloseAccParas->m_nPTPoint  = m_oRecloseAccParas.m_nPTPoint;                      //TV安装位置
	m_pRecloseAccParas->m_nCTPoint = m_oRecloseAccParas.m_nCTPoint;                      // TA正极性
	m_pRecloseAccParas->m_fIfh = m_oRecloseAccParas.m_fIfh;                                          //负荷电流
	m_pRecloseAccParas->m_fPowerAngle = m_oRecloseAccParas.m_fPowerAngle ;          //负荷功角
	m_pRecloseAccParas->m_bCBSimulation = m_oRecloseAccParas.m_bCBSimulation;    //断路器模拟
	m_pRecloseAccParas->m_fCBTripTime = 	m_oRecloseAccParas.m_fCBTripTime;            //分闸时间
	m_pRecloseAccParas->m_fCBCloseTime = 	m_oRecloseAccParas.m_fCBCloseTime;     //合闸时间
}

void CommonParasDialog::slot_ClickOk_Re()//重合闸
{
	m_oRecloseAccParas.m_fPreFaultTime = m_pEditRe[0]->text().toFloat();
	m_oRecloseAccParas.m_fMarginTime = m_pEditRe[1]->text().toFloat();
	m_oRecloseAccParas.m_fTAfterTrig[0] = m_pEditRe[2]->text().toFloat();
	m_oRecloseAccParas.m_fTAfterTrig[1] = m_pEditRe[2]->text().toFloat();

	m_oRecloseAccParas.m_fIfh = m_pEditRe[3]->text().toFloat();
	m_oRecloseAccParas.m_fPowerAngle = m_pEditRe[4]->text().toFloat();
	m_oRecloseAccParas.m_fCBTripTime = m_pEditRe[5]->text().toFloat();//分.0时间
	m_oRecloseAccParas.m_fCBTripTime = m_oRecloseAccParas.m_fCBTripTime / 1000.0;
	m_oRecloseAccParas.m_fCBCloseTime = m_pEditRe[6]->text().toFloat();//合闸时间
	m_oRecloseAccParas.m_fCBCloseTime = m_oRecloseAccParas.m_fCBCloseTime /1000.0;

	SetPara_Re();

	emit sig_ClickOk();
	close();
	m_nIsOK = 1;
}

void CommonParasDialog::slot_ClickCancel_Re()
{
	close();
	m_nIsOK = 2;
}

void CommonParasDialog::slot_FaultTrigModeChange_CB(int nIndex)
{
	if (nIndex!=0)
	{
		label_CB[0]->setDisabled(true);
		m_pEditCB[0]->setDisabled(true);
	}
	else 
	{
		label_CB[0]->setDisabled(false);
		m_pEditCB[0]->setDisabled(false);
	}
}

void CommonParasDialog::slot_TestProcessChange_CB(int nIndex)
{
	if (nIndex==0)
	{
		label_CB[6]->setDisabled(true);
		m_pCmbCB[4]->setDisabled(true);

		label_CB[7]->setDisabled(true);
		m_pEditCB[2]->setDisabled(true);

		label_CB[8]->setDisabled(true);
		m_pEditCB[3]->setDisabled(true);

		label_CB[9]->setDisabled(true);
		m_pEditCB[4]->setDisabled(true);

		label_CB[1]->setDisabled(false);
		m_pEditCB[1]->setDisabled(false);
	}
	else if (nIndex==1)
	{
		label_CB[6]->setDisabled(false);
		m_pCmbCB[4]->setDisabled(false);

		label_CB[7]->setDisabled(false);
		m_pEditCB[2]->setDisabled(false);

		label_CB[8]->setDisabled(false);
		m_pEditCB[3]->setDisabled(false);

		label_CB[9]->setDisabled(false);
		m_pEditCB[4]->setDisabled(false);

		label_CB[1]->setDisabled(true);
		m_pEditCB[1]->setDisabled(true);
	}
}

void CommonParasDialog::slot_CalcuModeChange_CB(int nIndex)
{
	if (nIndex==2)
	{
		label_CB[13]->setDisabled(false);
		m_pEditCB[7]->setDisabled(false);

		label_CB[14]->setDisabled(false);
		m_pEditCB[8]->setDisabled(false);
	}
	else 
	{
		label_CB[13]->setDisabled(true);
		m_pEditCB[7]->setDisabled(true);

		label_CB[14]->setDisabled(true);
		m_pEditCB[8]->setDisabled(true);
	}
}


void CommonParasDialog::slot_CBSimulationChange_CB(int nIndex)
{
	if (nIndex==0)
	{
		label_CB[16]->setDisabled(true);
		m_pEditCB[9]->setDisabled(true);

		label_CB[17]->setDisabled(true);
		m_pEditCB[10]->setDisabled(true);
	}
	else 
	{
		label_CB[16]->setDisabled(false);
		m_pEditCB[9]->setDisabled(false);

		label_CB[17]->setDisabled(false);
		m_pEditCB[10]->setDisabled(false);
	}
}

void CommonParasDialog::slot_FaultAngleChange_CB(int nIndex)
{
	if (nIndex==0)
	{
		m_pEditCB[11]->setDisabled(true);
	}
	else if (nIndex==1)
	{
		m_pEditCB[11]->setDisabled(false);
	}
}

void CommonParasDialog::slot_PsuVzDefineChange_CB(int nIndex)
{
    if (nIndex >= 1 && nIndex <= 3)
	{
		label_CB[21]->setDisabled(false);
		m_pCmbCB[12]->setDisabled(false);

		label_CB[22]->setDisabled(false);
		m_pEditCB[12]->setDisabled(false);
	}
	else// if (nIndex==5)
	{
		label_CB[21]->setDisabled(true);
		m_pCmbCB[12]->setDisabled(true);

		label_CB[22]->setDisabled(true);
		m_pEditCB[12]->setDisabled(true);
	}
}


void CommonParasDialog::initUI_Voltage()
{
	CTestDataTypeMngrConstGlobal::Create();

	m_TopLayout = new QGridLayout();

	label_Volt[0] = new QLabel();
	label_Volt[0]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Volt[0]->setText(/*QObject::tr("故障前时间(s):")*/g_sLangTxt_Native_PreFaultTimes);
	m_TopLayout->addWidget(label_Volt[0],  0,  0);
	m_pEditVolt[0] = new QFloatLineEdit(this);
	m_pEditVolt[0] ->InitCoverage(0,100);
	m_pEditVolt[0] ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pEditVolt[0] ,  0,  1);

	label_Volt[1] = new QLabel();
	label_Volt[1]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Volt[1]->setText(/*QObject::tr("CT正极性定义:")*/g_sLangTxt_Native_ctPolarityDef);
	m_TopLayout->addWidget(label_Volt[1],    1,  0);
	m_pCmbVolt[0] = new QValueComboBox(this);
	m_pCmbVolt[0]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CTPos")));//好了
	m_pCmbVolt[0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbVolt[0],   1,  1);

	label_Volt[2] = new QLabel();
	label_Volt[2]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_Volt[2]->setText(/*QObject::tr("故障相定义:")*/g_sLangTxt_Native_faultphase_definition);
	m_TopLayout->addWidget(label_Volt[2],   2,  0);
	m_pCmbVolt[1] = new QValueComboBox(this);
	m_pCmbVolt[1]->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultType")));//好了
	m_pCmbVolt[1]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_pCmbVolt[1],  2, 1);
}

void CommonParasDialog::initPara_Voltage()
{
	m_oVolInverseTimeParas.m_fPreFaultTime = m_pVolInverseTimeParas->m_fPreFaultTime;
	m_oVolInverseTimeParas.m_nCTPoint = m_pVolInverseTimeParas->m_nCTPoint;
	m_oVolInverseTimeParas.m_nFaultType = m_pVolInverseTimeParas->m_nFaultType;
}

void CommonParasDialog::initData_Voltage()
{
	m_pCmbVolt[0]->SetIndex((int *)&m_oVolInverseTimeParas.m_nCTPoint);
	m_pCmbVolt[1]->SetIndex((int *)&m_oVolInverseTimeParas.m_nFaultType);

	m_pEditVolt[0]->setText(QString::number(m_oVolInverseTimeParas.m_fPreFaultTime, 'f', 3));
}

void CommonParasDialog::initConnect_Voltage()
{
	connect(m_pCmbVolt[0] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_CTPointChange_Voltage(int)));
	connect(m_pCmbVolt[1] , SIGNAL(currentIndexChanged(int)),  this,  SLOT(slot_FaultTypeChange_Voltage(int)));
	connect(m_pEditVolt[0],	SIGNAL(textChanged(QString )),  this , SLOT(slot_EditValueChanged_Voltage(QString )));


	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk_Voltage()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel_Voltage()));
}

void CommonParasDialog::slot_EditValueChanged_Voltage(QString strValue)    // mym 2021-9-15 add
{
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}

void CommonParasDialog::SetPara_Voltage()
{
	m_pVolInverseTimeParas->m_nCTPoint = m_oVolInverseTimeParas.m_nCTPoint;
	m_pVolInverseTimeParas->m_nFaultType = m_oVolInverseTimeParas.m_nFaultType;
	m_pVolInverseTimeParas->m_fPreFaultTime = m_oVolInverseTimeParas.m_fPreFaultTime;
}

void CommonParasDialog::slot_ClickOk_Voltage()
{
 	m_oVolInverseTimeParas.m_fPreFaultTime = m_pEditVolt[0]->text().toFloat();

	SetPara_Voltage();

	emit sig_ClickOk();
	close();
	m_nIsOK = 1;
}

void CommonParasDialog::slot_ClickCancel_Voltage()
{
	close();
	m_nIsOK = 2;
}

void CommonParasDialog::slot_CTPointChange_Voltage(int nIndex)
{
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}

void CommonParasDialog::slot_FaultTypeChange_Voltage(int nIndex)
{
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}

void CommonParasDialog::slot_CBSimulationChange_Re(int nIndex)
{
	if (m_pEditRe[5]==NULL||m_pEditRe[6]==NULL)
		return;

	if (nIndex==1)
	{
		m_pEditRe[5]->setDisabled(false);
		m_pEditRe[6]->setDisabled(false);
	}
	else 
	{
		m_pEditRe[5]->setDisabled(true);
		m_pEditRe[6]->setDisabled(true);
	}
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}

void CommonParasDialog::slot_FaultTrigModeChange_Re(int nIndex)
{
	if (nIndex==0)
		m_pEditRe[0]->setDisabled(false);
	else 
		m_pEditRe[0]->setDisabled(true);
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->m_bTmtParaChanged = true;
}
void CommonParasDialog::initUI_DC()
{
	CTestDataTypeMngrConstGlobal::Create();

	m_TopLayout = new QGridLayout();
	m_TopLayout->setSpacing(10);

	m_pPreFaultOutput_GroupBox = new QGroupBox(this);
	m_TopLayout->addWidget(m_pPreFaultOutput_GroupBox,0,0,1,-1);
	m_pPreFaultOutput_GroupBox->setTitle(tr("故障前输出"));
	m_pPreFaultOutput_GridLayout = new QGridLayout(m_pPreFaultOutput_GroupBox);
	m_pPreFaultOutput_GridLayout->setSpacing(10);

	label_PreFaultTime = new QLabel();
	label_PreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PreFaultTime->setText(QObject::tr("故障前时间(s):"));
	m_pPreFaultOutput_GridLayout->addWidget(label_PreFaultTime, 0, 0, 1, 1);
	m_editPreFaultTime = new QFloatLineEdit(this);
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		m_editPreFaultTime->InitCoverage(0, 3000.000);
	}
	else
	{
		m_editPreFaultTime->InitCoverage(0, 999.999);
	}

	m_editPreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_pPreFaultOutput_GridLayout->addWidget(m_editPreFaultTime, 0, 1, 1, 1);

	label_PreFaultCur = new QLabel(m_pPreFaultOutput_GroupBox);
	label_PreFaultCur->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PreFaultCur->setText(tr("故障前电流(A):"));
	m_pPreFaultOutput_GridLayout->addWidget(label_PreFaultCur, 1, 0);
	m_editPreFaultCur = new QFloatLineEdit(m_pPreFaultOutput_GroupBox);
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		m_editPreFaultCur->InitCoverage(0, 10000.000);
	}
	else
	{
		m_editPreFaultCur->InitCoverage(0,999.999);
	}
	m_editPreFaultCur->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_pPreFaultOutput_GridLayout->addWidget(m_editPreFaultCur, 1, 1);

	label_PreFaultVol = new QLabel(m_pPreFaultOutput_GroupBox);
 	label_PreFaultVol->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
 	label_PreFaultVol->setText(tr("一次额定电压(kV):"));
 	m_TopLayout->addWidget(label_PreFaultVol,1,0);
 	m_editPreFaultVol = new QFloatLineEdit(m_pPreFaultOutput_GroupBox);
//  	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
//  	{
//  		m_editPreFaultVol->InitCoverage(0,750000.000);
//  	}
//  	else
//  	{
//  		m_editPreFaultVol->InitCoverage(0,999.999);
//  	}
	m_editPreFaultVol->InitCoverage(0,1000.0);
 
	
 	m_editPreFaultVol->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPreFaultVol,1,1);

	label_FaultTime = new QLabel();
	label_FaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_FaultTime->setText(QObject::tr("故障时间裕度(s):"));
	m_TopLayout->addWidget(label_FaultTime,2,0);
	m_editFaultTime = new QLineEdit(this);
	//m_editFaultTime->InitCoverage(0.001,999.999);
	m_editFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	connect(m_editFaultTime , SIGNAL(editingFinished()),this,SLOT(slot_FaultTimeChange_DC()));
	m_TopLayout->addWidget(m_editFaultTime,2,1);

	label_PostFaultTime = new QLabel();
	label_PostFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_PostFaultTime->setText(QObject::tr("保护动作后持续时间(s):"));
	m_TopLayout->addWidget(label_PostFaultTime,3,0);
	m_editPostFaultTime = new QFloatLineEdit(this);
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		m_editPreFaultTime->InitCoverage(0, 3000.000);
	}
	else
	{
		m_editPreFaultTime->InitCoverage(0, 999.999);
	}
	m_editPostFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editPostFaultTime,3,1);

	label_FaultTrigMode = new QLabel();
	label_FaultTrigMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_FaultTrigMode->setText(QObject::tr("故障触发方式:"));
	m_TopLayout->addWidget(label_FaultTrigMode,4,0);
	m_CmbFaultTrigMode = new QValueComboBox(this);
	m_CmbFaultTrigMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultTrigMode")));
	m_CmbFaultTrigMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbFaultTrigMode,4,1);

	label_CBSimulation = new QLabel();
	label_CBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBSimulation->setText(QObject::tr("断路器模拟:"));
	m_TopLayout->addWidget(label_CBSimulation,5,0);
	m_CmbCBSimulation = new QValueComboBox(this);
	m_CmbCBSimulation->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CBSimulation")));
	m_CmbCBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_CmbCBSimulation,5,1);

	label_CBTripTime = new QLabel();
	label_CBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBTripTime->setText(QObject::tr("分闸时间(ms):"));
	m_TopLayout->addWidget(label_CBTripTime,6,0);
	m_editCBTripTime = new QFloatLineEdit(this);
	m_editCBTripTime->InitCoverage(0,999999);
	m_editCBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editCBTripTime,6,1);

	label_CBCloseTime = new QLabel();
	label_CBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_CBCloseTime->setText(QObject::tr("合闸时间(ms):"));
	m_TopLayout->addWidget(label_CBCloseTime,7,0);
	m_editCBCloseTime = new QFloatLineEdit(this);
	m_editCBCloseTime->InitCoverage(0,999999);
	m_editCBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_TopLayout->addWidget(m_editCBCloseTime,7,1);

	resize(400 *g_dUIShowCoef,  320);
}

void CommonParasDialog::CopyPartForDCOverCurrent(tmt_DCOverCurrentParas &Para_A,tmt_DCOverCurrentParas &Para_B )
{
	Para_B.m_fPreFaultVol = Para_A.m_fPreFaultVol;
	Para_B.m_fPreFaultCur = Para_A.m_fPreFaultCur;

	Para_B.m_fMarginTime = Para_A.m_fMarginTime;
	Para_B.m_fPreFaultTime = Para_A.m_fPreFaultTime;
	Para_B.m_fAfterTriggerFaultTime = Para_A.m_fAfterTriggerFaultTime;
	Para_B.m_nFaultTrigMode = Para_A.m_nFaultTrigMode;

	Para_B.m_bCBSimulation = Para_A.m_bCBSimulation;
	Para_B.m_fCBTripTime = Para_A.m_fCBTripTime;
	Para_B.m_fCBCloseTime = Para_A.m_fCBCloseTime;
}

void CommonParasDialog::initData_DC()
{
	m_editPreFaultVol->setText(QString::number(m_oDCOverCurrentParas.m_fPreFaultVol, 'f', 3));
	m_editPreFaultCur->setText(QString::number(m_oDCOverCurrentParas.m_fPreFaultCur, 'f', 3));

	m_editPreFaultTime->setText(QString::number(m_oDCOverCurrentParas.m_fPreFaultTime, 'f', 3));
	m_editFaultTime->setText(QString::number(m_oDCOverCurrentParas.m_fMarginTime, 'f', 3));
	m_editPostFaultTime->setText(QString::number(m_oDCOverCurrentParas.m_fAfterTriggerFaultTime, 'f', 3));
	m_CmbFaultTrigMode->SetIndex(&m_oDCOverCurrentParas.m_nFaultTrigMode);

	m_CmbCBSimulation->SetIndex(&m_oDCOverCurrentParas.m_bCBSimulation);
	m_editCBTripTime->setText(QString::number(m_oDCOverCurrentParas.m_fCBTripTime * 1000, 'f', 3));
	m_editCBCloseTime->setText(QString::number(m_oDCOverCurrentParas.m_fCBCloseTime * 1000, 'f', 3));

	slot_FaultTrigModeChange(0);
	slot_CBSimulationChange(0);
}

void CommonParasDialog::initConnect_DC()
{
	connect(m_CmbFaultTrigMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTrigModeChange(int)));
	connect(m_CmbCBSimulation,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CBSimulationChange(int)));

	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk_DC()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel()));

	connect(m_editPreFaultVol , SIGNAL(editingFinished()),this,SLOT(slot_PreFaultVolChange_DC()));
	connect(m_editPreFaultCur , SIGNAL(editingFinished()),this,SLOT(slot_PreFaultCurChange_DC()));
	connect(m_editPreFaultTime , SIGNAL(editingFinished()),this,SLOT(slot_PreFaultTimeChange_DC()));
	connect(m_editPostFaultTime , SIGNAL(editingFinished()),this,SLOT(slot_PostFaultTimeChange_DC()));

	connect( m_editCBTripTime,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));
	connect( m_editCBCloseTime,SIGNAL(editingFinished()),  this , SLOT(slot_EditValueChanged_DS()));

}

void CommonParasDialog::slot_ClickOk_DC()
{
	JudgeModifyPara(m_oDCOverCurrentParas.m_fPreFaultVol,m_editPreFaultVol->text().toFloat());
	m_oDCOverCurrentParas.m_fPreFaultVol = m_editPreFaultVol->text().toFloat();
	JudgeModifyPara(m_oDCOverCurrentParas.m_fPreFaultCur,m_editPreFaultCur->text().toFloat());
	m_oDCOverCurrentParas.m_fPreFaultCur = m_editPreFaultCur->text().toFloat();

	JudgeModifyPara(m_oDCOverCurrentParas.m_fMarginTime,m_editFaultTime->text().toFloat());
	m_oDCOverCurrentParas.m_fMarginTime = m_editFaultTime->text().toFloat();
	JudgeModifyPara(m_oDCOverCurrentParas.m_fPreFaultTime,m_editPreFaultTime->text().toFloat());
	m_oDCOverCurrentParas.m_fPreFaultTime = m_editPreFaultTime->text().toFloat();
	JudgeModifyPara(m_oDCOverCurrentParas.m_fAfterTriggerFaultTime,m_editPostFaultTime->text().toFloat());
	m_oDCOverCurrentParas.m_fAfterTriggerFaultTime = m_editPostFaultTime->text().toFloat();	

	JudgeModifyPara(m_oDCOverCurrentParas.m_fCBTripTime,m_editCBTripTime->text().toFloat() / 1000);
	m_oDCOverCurrentParas.m_fCBTripTime = m_editCBTripTime->text().toFloat();
	m_oDCOverCurrentParas.m_fCBTripTime = m_oDCOverCurrentParas.m_fCBTripTime / 1000.0;
	JudgeModifyPara(m_oDCOverCurrentParas.m_fCBCloseTime,m_editCBCloseTime->text().toFloat() / 1000);
	m_oDCOverCurrentParas.m_fCBCloseTime = m_editCBCloseTime->text().toFloat();
	m_oDCOverCurrentParas.m_fCBCloseTime = m_oDCOverCurrentParas.m_fCBCloseTime / 1000.0;

	CopyPartForDCOverCurrent(m_oDCOverCurrentParas,*m_pDCOverCurrentParas);

	emit sig_ClickOk();
	close();
	m_nIsOK = 1;
}
void CommonParasDialog::slot_PreFaultVolChange_DC()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strTemp = m_editPreFaultVol->text();
	float fvalue = strTemp.toFloat();

	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		fvalue = setLimit(0.001,750000,fvalue);
	}
	else
	{
	fvalue = setLimit(0.001,999.999,fvalue);

	}

	m_editPreFaultVol->setText(QString::number(fvalue, 'f', 3));
}

void CommonParasDialog::slot_PreFaultCurChange_DC()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strTemp = m_editPreFaultCur->text();
	float fvalue = strTemp.toFloat();
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		if (m_strMacroID == STT_MACRO_ID_DCOverCurrentTest)
		{
			fvalue = setLimit(0,10000.00,fvalue);
		}
		else
		{
		fvalue = setLimit(0.001,10000.00,fvalue);
	}
	}
	else
	{
		if (m_strMacroID == STT_MACRO_ID_DCOverCurrentTest)
		{
			fvalue = setLimit(0,999.999,fvalue);
		}
	else
	{
			fvalue = setLimit(0.001,999.999,fvalue);
		}
	}

	//fvalue = setLimit(0.001,999.999,fvalue);

	m_editPreFaultCur->setText(QString::number(fvalue, 'f', 3));
}

void CommonParasDialog::slot_PreFaultTimeChange_DC()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strTemp = m_editPreFaultTime->text();
	float fvalue = strTemp.toFloat();
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		fvalue = setLimit(0.001,3000.00,fvalue);
	}
	else
	{
		fvalue = setLimit(0.001,999.999,fvalue);
	}

	//fvalue = setLimit(0.001,999.999,fvalue);

	m_editPreFaultTime->setText(QString::number(fvalue, 'f', 3));
}
void CommonParasDialog::slot_PostFaultTimeChange_DC()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strTemp = m_editPostFaultTime->text();
	float fvalue = strTemp.toFloat();
	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1) &&(g_oSystemParas.m_nHasWeek == 0) && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
	{
		fvalue = setLimit(0.001,3000.00,fvalue);
	}
	else
	{
		fvalue = setLimit(0.001,999.999,fvalue);
	}

	//fvalue = setLimit(0.001,999.999,fvalue);

	m_editPostFaultTime->setText(QString::number(fvalue, 'f', 3));
}
