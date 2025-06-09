#include "CommonParasDialog_CB.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

CommonParasDialog_CB::CommonParasDialog_CB(tmt_CBOperateParas *pImpedanceParas, const CString &strMacroID, QWidget *parent) :CommonParasDialog(pImpedanceParas, strMacroID, parent)
{
	m_nTestProcCtrlMode = 0;	   //试验过程控制方式 0-跳合控制 1-时间控制
	m_nRecloseMode  =  0;           // 重合方式：0-综重（单重+三重） 1-三重 2-不重合
	m_fTAfterTrig  =  0;			        // 后加速开关跳开后持续时间
	m_pCBOperateParas  =  pImpedanceParas;
	//init();
	//init_CB();
}

CommonParasDialog_CB::~CommonParasDialog_CB()
{

}

void CommonParasDialog_CB::init_CB()
{
	//initData_CB();// 整组 mym 2021-8-3;
	//initPara_CB();//整组 mym 2021-8-3;
}

void CommonParasDialog_CB::init()
{
	//CommonParasDialog::init();

	int adf = 0;
	initUI();	
	initPara();
	initData();
	initConnect();
}

void  CommonParasDialog_CB:: initUI()
{	
	//CommonParasDialog::initUI();
	m_CmbCalcuMode = new QValueComboBox(this);
	m_CmbCalcuMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CalcuMode")));
	m_CmbCalcuMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editSystemImp = new QFloatLineEdit(this);
	m_editSystemImp->InitCoverage(0,100);
	m_editSystemImp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editSystemImpAng = new QFloatLineEdit(this);
	m_editSystemImpAng->InitCoverage(0,180,0);
	m_editSystemImpAng->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


	//试验过程控制方式
	m_CmbTestCtrlMode = new QValueComboBox(this);
	m_CmbTestCtrlMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("TestProcess")));
	m_CmbTestCtrlMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	
	//重合方式
	m_CmbRecoseMode = new QValueComboBox(this);
	m_CmbRecoseMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("RecloseMode")));
	m_CmbRecoseMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	
	//系统阻抗
	m_editRecloseTime = new QFloatLineEdit(this);
	m_editRecloseTime->InitCoverage(0,100);
	m_editRecloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_28 = new QLabel();
	label_28->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_28->setText(/*QObject::tr("计算方式:")*/g_sLangTxt_State_CalcType);

	label_29 = new QLabel();
	label_29->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_29->setText(/*QObject::tr("系统阻抗(Ω):")*/g_sLangTxt_Native_system_impedance);

	label_30 = new QLabel();
	label_30->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_30->setText(/*QObject::tr("系统阻抗角(°):")*/g_sLangTxt_Native_system_impedance_angle);

	label_31 = new QLabel();
	label_31->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_31->setText(/*QObject::tr("试验过程控制方式:")*/g_sLangTxt_Native_testprocess_control);

	label_32 = new QLabel();
	label_32->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_32->setText(/*QObject::tr("重合方式:")*/g_sLangTxt_Native_coincidence_mode);

	label_33 = new QLabel();
	label_33->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_33->setText(/*QObject::tr("开关跳开后持续时间:")*/g_sLangTxt_Native_duration_afterjump);


	//m_MainLayout->addWidget(label_31, GetCurrentRow() + 1, 0);
	//m_MainLayout->addWidget(label_32, GetCurrentRow() + 2,  0);
	//m_MainLayout->addWidget(label_33, GetCurrentRow() + 3,  0);

	//m_MainLayout->addWidget(m_CmbTestCtrlMode,   GetCurrentRow() + 1, 1);
	//m_MainLayout->addWidget(m_CmbRecoseMode,		 GetCurrentRow() + 2,  1);
	//m_MainLayout->addWidget(m_editRecloseTime,  GetCurrentRow() +  3,  1);


	//m_MainLayout->addWidget(label_28, GetCurrentRow() + 1, 2);
	//m_MainLayout->addWidget(label_29, GetCurrentRow() + 2,  2);
	//m_MainLayout->addWidget(label_30, GetCurrentRow() + 3,  2);

	//m_MainLayout->addWidget(m_CmbCalcuMode,   GetCurrentRow() + 1, 3);
	//m_MainLayout->addWidget(m_editSystemImp,		 GetCurrentRow() + 2,  3);
	//m_MainLayout->addWidget(m_editSystemImpAng,  GetCurrentRow() +  3,  3);


	//setBtn(m_nCurrentRow + 4);
	//m_MainLayout->addWidget(m_BtnOk,m_nCurrentRow + 4,2);
	//m_MainLayout->addWidget(m_BtnCancel,m_nCurrentRow + 4,3);
}


void CommonParasDialog_CB::SetPara()
{	
	//CommonParasDialog::SetPara();
	m_CmbCalcuMode->SetIndex((int*)(&m_ImpedanceParas.m_nCalMode));
	m_ImpedanceParas.m_fPhis = m_editSystemImpAng->text().toFloat();
	m_ImpedanceParas.m_fZs = m_editSystemImp->text().toFloat();

// 		float	m_fTAfterTrig[2];	//故障后延时
// 		int		m_nTestProcCtrlMode;	// 试验过程控制方式 0-跳合控制 1-时间控制
// 		float m_nRecloseMode;// 重合方式：0-综重（单重+三重） 1-三重 2-不重合

	//pParas->m_fTAfterTrig[1];后加速开关跳开后持续时间;
	m_pImpedanceParas->m_nCalMode = m_ImpedanceParas.m_nCalMode;
 	m_pImpedanceParas->m_fZs = m_ImpedanceParas.m_fZs;
 	m_pImpedanceParas->m_fPhis = m_ImpedanceParas.m_fPhis;

	m_pCBOperateParas->m_nTestProcCtrlMode = m_nTestProcCtrlMode;
	m_pCBOperateParas->m_nRecloseMode = m_nRecloseMode;
	//m_pCBOperateParas->m_fTAfterTrig[0]  = m_editRecloseTime->text().toFloat();
}

void CommonParasDialog_CB::initPara()
{
    //CommonParasDialog::initPara();
	m_ImpedanceParas.m_nCalMode = m_pImpedanceParas->m_nCalMode;
	m_ImpedanceParas.m_fZs = m_pImpedanceParas->m_fZs;
	m_ImpedanceParas.m_fPhis = m_pImpedanceParas->m_fPhis;

	// 2021-7-6 add 
	m_nTestProcCtrlMode = m_pCBOperateParas->m_nTestProcCtrlMode;
	m_nRecloseMode = m_pCBOperateParas->m_nRecloseMode;
//	m_fTAfterTrig = m_pCBOperateParas->m_fTAfterTrig[0];
}

void CommonParasDialog_CB::initData()
{	
	//CommonParasDialog::initData();
	m_editSystemImp->setText(QString::number(m_ImpedanceParas.m_fZs, 'f', 3));
	m_editSystemImpAng->setText(QString::number(m_ImpedanceParas.m_fPhis, 'f', 3));
	m_CmbCalcuMode->SetIndex(&m_ImpedanceParas.m_nCalMode);


	m_editRecloseTime->setText(QString::number(m_fTAfterTrig, 'f', 3));
	m_CmbTestCtrlMode->SetIndex(&m_nTestProcCtrlMode);
	m_CmbRecoseMode->SetIndex(&m_nRecloseMode);
}
