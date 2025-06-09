#include "QLowVolAddMultDlg.h"
#include <QLabel>
#include "../../UI/SoftKeyboard/SoftKeyBoard.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../OSInterface/QT/XMessageBox.h"

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QLowVolAddMultDlg::QLowVolAddMultDlg(QWidget *parent /*= 0*/) : QDialog(parent),
ui(new Ui::QLowVolAddMultDlg)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
	ui->setupUi(this);
	//OpenXmlFile();
	InitUI();
	InitFont();
	InitConnects();
}

QLowVolAddMultDlg::~QLowVolAddMultDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
	delete ui;
}

void QLowVolAddMultDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
    ui->m_CmbUSetMode->addItem(/*"相电压"*/g_sLangTxt_Native_VolSetTypeLN.remove("(Y)"));
    ui->m_CmbUSetMode->addItem(/*"线电压"*/g_sLangTxt_Native_VolSetTypeLL.remove("(D)"));

	ui->m_EditBeginVal->setEnabled(false);
	ui->m_EditEndVal->setEnabled(false);
	ui->m_EditStep->setEnabled(false);
	ui->m_EditVend2->setEnabled(false);

	ui->m_EditIAtresiaStart->setEnabled(false);
	ui->m_EditIAtresiaEnd->setEnabled(false);
	ui->m_EditIAtresiaStep->setEnabled(false);
	ui->m_EditIAtresiaVend2->setEnabled(false);
	ui->m_EditStep->setEnabled(false);
	ui->m_EditVend2->setEnabled(false);
	ui->m_labTips->setVisible(false);

	ui->m_LabTestItem->setText(/*测试项目*/g_sLangTxt_LowFreq_TestItem);
	ui->m_LabSetValue->setText(/*整定值*/g_sLangTxt_State_SettingValue);
	ui->m_LabStart->setText(/*始值*/g_sLangTxt_State_BeginVal);
	ui->m_LabEnd->setText(/*终值*/g_sLangTxt_State_EndVal);
	ui->m_LabStep->setText(/*变化步长*/g_sLangTxt_Gradient_Step);
	ui->m_LabParas->setText(/*递变参数*/g_sLangTxt_LowFreq_GradientPara);
	ui->m_TripVolCheck->setText(/*低压减载动作值(V)*/g_sLangTxt_Native_LowVoltUnderloadTripSet);
	ui->m_UActTimeCheck->setText(/*动作时间(s)*/g_sLangTxt_Native_ActionTime);
	ui->m_DvdtCloseCheck->setText(/*电压滑差动作值(V/s)*/g_sLangTxt_Native_VoltSlipAct + "(V/s)");
	ui->m_IAtresiacheck->setText(/*低电流闭锁值(A)*/g_sLangTxt_LowFreq_ILock + "(A)");
	ui->m_LabdvdtRate->setText(/*电压滑差倍数*/g_sLangTxt_LowVol_dVdtRate);
	ui->m_LabVend2->setText(/*电压结束值(V)*/g_sLangTxt_LowVol_VolEnd);
	ui->m_Labdvdt1Rate->setText(/*电压滑差倍数*/g_sLangTxt_LowVol_dVdtRate);
	ui->m_LabVend1->setText(/*电压结束值(V)*/g_sLangTxt_LowVol_VolEnd);
	ui->m_LabVend3->setText(/*电压滑差(V/s)*/g_sLangTxt_Native_VoltSlip + "(V/s)");
	ui->m_groupBox7_3->setTitle(/*时间参数*/g_sLangTxt_LowFreq_TimePara);
	ui->m_LabHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	ui->m_groupBox8->setTitle(/*其他参数*/g_sLangTxt_LowVol_OtherPara);
	ui->m_LabUSetMode->setText(/*闭锁电压定义*/g_sLangTxt_Native_LockVoltDef);
	ui->m_LabIPreTime->setText(/*稳态电流(A)*/g_sLangTxt_LowVol_SteadyCur);
	ui->m_groupBox9->setTitle(/*电压变化量*/g_sLangTxt_Native_VoltChangeAmt);
	ui->m_LabExegesis->setText(/*注:" 低压减载动作值"测试项使用*/g_sLangTxt_LowVol_Exegesis);
	ui->m_BtnResultAssess->setText(/*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate);
	ui->m_BtnOk->setText(/*确定*/g_sLangTxt_OK);
	ui->m_BtnExit->setText(/*取消*/g_sLangTxt_Cancel);
	setWindowTitle(/*添加系列*/g_sLangTxt_Distance_AddMultTile);
	//ui->m_EditUAct->setFixedWidth(110);
	//ui->m_EditVstart->setFixedWidth(110);
	//ui->m_EditVend->setFixedWidth(110);
	//ui->m_EditVstep->setFixedWidth(110);
	//ui->m_EditdvdtRate->setFixedWidth(110);
	//ui->m_EditUActTime->setFixedWidth(110);
	//ui->m_EditVend1->setFixedWidth(110);
	//ui->m_Editdvdt1Rate->setFixedWidth(110);
	//ui->m_EditDvdtClose->setFixedWidth(110);
	//ui->m_EditBeginVal->setFixedWidth(110);
	//ui->m_EditEndVal->setFixedWidth(110);
	//ui->m_EditStep->setFixedWidth(110);
	//ui->m_EditVend2->setFixedWidth(110);
	//ui->m_EditIAtresiaValue->setFixedWidth(110);
	//ui->m_EditIAtresiaStart->setFixedWidth(110);
	//ui->m_EditIAtresiaEnd->setFixedWidth(110);
	//ui->m_EditIAtresiaStep->setFixedWidth(110);
	//ui->m_EditIAtresiaVend2->setFixedWidth(110);
	//ui->m_EditHoldTime->setFixedWidth(110);
	//ui->m_CmbUSetMode->setFixedWidth(110);
	//ui->m_EditIPreTime->setFixedWidth(110);
}

void QLowVolAddMultDlg::InitFont()
{
//	ui->m_TripVolCheck->setFont(*g_pSttGlobalFont);
//	ui->m_UActTimeCheck->setFont(*g_pSttGlobalFont);
//	ui->m_DvdtCloseCheck->setFont(*g_pSttGlobalFont);
//	ui->m_EditUAct->setFont(*g_pSttGlobalFont);
//	ui->m_EditUActTime->setFont(*g_pSttGlobalFont);
//	ui->m_EditDvdtClose->setFont(*g_pSttGlobalFont);
//	ui->m_groupBox3->setFont(*g_pSttGlobalFont);
//	ui->m_EditVstart->setFont(*g_pSttGlobalFont);
//	ui->m_Lab1->setFont(*g_pSttGlobalFont);
//	ui->m_EditBeginVal->setFont(*g_pSttGlobalFont);
//	ui->m_groupBox4->setFont(*g_pSttGlobalFont);
//	ui->m_EditVend->setFont(*g_pSttGlobalFont);
//	ui->m_Lab2->setFont(*g_pSttGlobalFont);
//	ui->m_EditEndVal->setFont(*g_pSttGlobalFont);
//	ui->m_groupBox5->setFont(*g_pSttGlobalFont);
//	ui->m_EditVstep->setFont(*g_pSttGlobalFont);
//	ui->m_Lab3->setFont(*g_pSttGlobalFont);
//	ui->m_EditStep->setFont(*g_pSttGlobalFont);
//	ui->m_EditdvdtRate->setFont(*g_pSttGlobalFont);
//	ui->m_LabdvdtRate->setFont(*g_pSttGlobalFont);
//	ui->m_EditVend1->setFont(*g_pSttGlobalFont);
//	ui->m_LabVend1->setFont(*g_pSttGlobalFont);
//	ui->m_Editdvdt1Rate->setFont(*g_pSttGlobalFont);
//	ui->m_Labdvdt1Rate->setFont(*g_pSttGlobalFont);
//	ui->m_EditVend2->setFont(*g_pSttGlobalFont);
//	ui->m_LabVend2->setFont(*g_pSttGlobalFont);
//	ui->m_groupBox7_3->setFont(*g_pSttGlobalFont);
//	ui->m_LabHoldTime->setFont(*g_pSttGlobalFont);
//	ui->m_EditHoldTime->setFont(*g_pSttGlobalFont);
//	ui->m_groupBox8->setFont(*g_pSttGlobalFont);
//	ui->m_LabUSetMode->setFont(*g_pSttGlobalFont);
//	ui->m_CmbUSetMode->setFont(*g_pSttGlobalFont);
//	ui->m_LabIPreTime->setFont(*g_pSttGlobalFont);
//	ui->m_EditIPreTime->setFont(*g_pSttGlobalFont);
//	ui->m_groupBox9->setFont(*g_pSttGlobalFont);
//	ui->m_UaCheck->setFont(*g_pSttGlobalFont);
//	ui->m_UbCheck->setFont(*g_pSttGlobalFont);
//	ui->m_UcCheck->setFont(*g_pSttGlobalFont);
//	ui->m_UabcCheck->setFont(*g_pSttGlobalFont);
//	ui->m_LabExegesis->setFont(*g_pSttGlobalFont);
//	ui->m_BtnResultAssess->setFont(*g_pSttGlobalFont);
//	ui->m_BtnExit->setFont(*g_pSttGlobalFont);
//	ui->m_IAtresiacheck->setFont(*g_pSttGlobalFont);
//	ui->m_LabTestItem->setFont(*g_pSttGlobalFont);
//	ui->m_LabSetValue->setFont(*g_pSttGlobalFont);
//	ui->m_LabStart->setFont(*g_pSttGlobalFont);
//	ui->m_LabEnd->setFont(*g_pSttGlobalFont);
//	ui->m_LabStep->setFont(*g_pSttGlobalFont);
//	ui->m_LabParas->setFont(*g_pSttGlobalFont);
//	ui->m_LabVend3->setFont(*g_pSttGlobalFont);
//	ui->m_BtnOk->setFont(*g_pSttGlobalFont);
//	ui->m_EditIAtresiaValue->setFont(*g_pSttGlobalFont);
//	ui->m_EditIAtresiaStart->setFont(*g_pSttGlobalFont);
//	ui->m_EditIAtresiaEnd->setFont(*g_pSttGlobalFont);
//	ui->m_EditIAtresiaStep->setFont(*g_pSttGlobalFont);
//	ui->m_EditIAtresiaVend2->setFont(*g_pSttGlobalFont);
}

void QLowVolAddMultDlg::InitConnects()
{

	connect(ui->m_TripVolCheck, SIGNAL(clicked()), this, SLOT(slot_TripVolCheck()));
	connect(ui->m_UActTimeCheck, SIGNAL(clicked(bool)), this, SLOT(slot_UActTimeCheck(bool)));
	connect(ui->m_DvdtCloseCheck, SIGNAL(clicked(bool)), this, SLOT(slot_DvdtCloseCheck(bool)));
	connect(ui->m_IAtresiacheck, SIGNAL(clicked(bool)), this, SLOT(slot_IAtresiacheck(bool)));
	connect(ui->m_BtnExit,SIGNAL(clicked()),this,SLOT(slot_Exit()));
	connect(ui->m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_Ok()));
	connect(ui->m_BtnResultAssess, SIGNAL(clicked()), this, SLOT(slot_BtnResultAssess()));
	connect(ui->m_EditUAct, SIGNAL(editingFinished()), this, SLOT(slot_EditUAct()));
	connect(ui->m_EditUActTime, SIGNAL(editingFinished()), this, SLOT(slot_EditUActTime()));
	connect(ui->m_EditDvdtClose, SIGNAL(editingFinished()), this, SLOT(slot_EditDvdtClose()));
	connect(ui->m_CmbUSetMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbUSetMode(int)));

	connect(ui->m_EditIAtresiaValue, SIGNAL(editingFinished()), this, SLOT(slot_EditIAtresiaValue()));
	connect(ui->m_EditIAtresiaStart, SIGNAL(editingFinished()), this, SLOT(slot_EditIAtresiaStart()));
	connect(ui->m_EditIAtresiaEnd, SIGNAL(editingFinished()), this, SLOT(slot_EditIAtresiaEnd()));
	connect(ui->m_EditIAtresiaStep, SIGNAL(editingFinished()), this, SLOT(slot_EditIAtresiaStep()));
	connect(ui->m_EditIAtresiaVend2, SIGNAL(editingFinished()), this, SLOT(slot_EditIAtresiaVend2()));

	connect(ui->m_EditVstart, SIGNAL(editingFinished()), this, SLOT(slot_EditVstart()));
	connect(ui->m_EditVend, SIGNAL(editingFinished()), this, SLOT(slot_EditVend()));
	connect(ui->m_EditVstep, SIGNAL(editingFinished()), this, SLOT(slot_EditVstep()));
	connect(ui->m_EditdvdtRate, SIGNAL(editingFinished()), this, SLOT(slot_EditUdvdtRate()));
	connect(ui->m_EditVend1, SIGNAL(editingFinished()), this, SLOT(slot_EditVend1()));
	connect(ui->m_EditIPreTime, SIGNAL(editingFinished()), this, SLOT(slot_EditPreTime()));
	connect(ui->m_Editdvdt1Rate, SIGNAL(editingFinished()), this, SLOT(slot_Editdvdt1Rate()));
	connect(ui->m_EditVend2, SIGNAL(editingFinished()), this, SLOT(slot_EditVend2()));
	connect(ui->m_EditBeginVal, SIGNAL(editingFinished()), this, SLOT(slot_EditBeginVal()));
	connect(ui->m_EditEndVal, SIGNAL(editingFinished()), this, SLOT(slot_EditEndVal()));
	connect(ui->m_EditStep, SIGNAL(editingFinished()), this, SLOT(slot_EditStep()));
	connect(ui->m_EditHoldTime, SIGNAL(editingFinished()), this, SLOT(slot_EditHoldTime()));

}

void QLowVolAddMultDlg::slot_BtnResultAssess()
{
	QLowVolAssessDlg dlg(&m_oLowVolDataGroup,this);
    dlg.setWindowTitle(g_sLangTxt_StateEstimate_ResultEstimate);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}


void QLowVolAddMultDlg::OpenXmlFile()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/LowVolI_Paras.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oLowVolDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QLowVolAddMultDlg::InitDatas()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("TripVol_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_TripVolCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("UActTime_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_UActTimeCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("DvdtClose_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_DvdtCloseCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("TripILock_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_IAtresiacheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ub_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_UbCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uc_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_UcCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uabc");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_UabcCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ua_Check");

	if (ui->m_TripVolCheck->isChecked() &&
		!ui->m_UbCheck->isChecked() &&
		!ui->m_UcCheck->isChecked() &&
		!ui->m_UabcCheck->isChecked())
	{
		ui->m_UaCheck->setChecked(TRUE);
	}
	else if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_UaCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("USetMode");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_CmbUSetMode->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("UAct");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditUAct->setText(QString::number(fValue, 'f', 3));
		ui->m_EditUAct->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vstart");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditVstart->setText(QString::number(fValue, 'f', 3));
		ui->m_EditVstart->UpdateObjectText(pData, pData->m_strValue);
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditVend->setText(QString::number(fValue, 'f', 3));
		ui->m_EditVend->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vstep");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditVstep->setText(QString::number(fValue, 'f', 3));
		ui->m_EditVstep->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("DvdtClose");//mod wangtao 20241028 移到前面，计算电压滑差倍数
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditDvdtClose->setText(QString::number(fValue, 'f', 3));
		ui->m_EditDvdtClose->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("dvdtRate");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditdvdtRate->setText(QString::number(fValue / ui->m_EditDvdtClose->GetText().toDouble(), 'f', 3));
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("UActTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditUActTime->setText(QString::number(fValue, 'f', 3));
		ui->m_EditUActTime->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditVend1->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("dvdt1Rate");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_Editdvdt1Rate->setText(QString::number(fValue / ui->m_EditDvdtClose->GetText().toDouble(), 'f', 3));
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("BeginVal");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		///ui->m_EditBeginVal->setText(QString::number(fValue, 'f', 3));
		ui->m_EditBeginVal->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("EndVal");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditEndVal->setText(QString::number(fValue, 'f', 3));
		ui->m_EditEndVal->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Step");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditStep->setText(QString::number(fValue, 'f', 3));
		ui->m_EditStep->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend2");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditVend2->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("HoldTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditHoldTime->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("IAct");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditIPreTime->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("ISetValue");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditIAtresiaValue->setText(QString::number(fValue, 'f', 3));
		ui->m_EditIAtresiaValue->UpdateObjectText(pData, pData->m_strValue);
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("BeginI");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditIAtresiaStart->setText(QString::number(fValue, 'f', 3));
		ui->m_EditIAtresiaStart->UpdateObjectText(pData, pData->m_strValue);
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("EndI");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditIAtresiaEnd->setText(QString::number(fValue, 'f', 3));
		ui->m_EditIAtresiaEnd->UpdateObjectText(pData, pData->m_strValue);
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("IStep");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditIAtresiaStep->setText(QString::number(fValue, 'f', 3));
		ui->m_EditIAtresiaStep->UpdateObjectText(pData, pData->m_strValue);
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend3");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditIAtresiaVend2->setText(QString::number(fValue, 'f', 3));
	}
}

void QLowVolAddMultDlg::slot_Ok()
{
	
	CDvmData *pData;
	long nTripVol = ui->m_TripVolCheck->isChecked();
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("TripVol_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTripVol);
		ui->m_TripVolCheck->setChecked(nTripVol);
	}

	long nUActTime = ui->m_UActTimeCheck->isChecked();
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("UActTime_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nUActTime);
		ui->m_UActTimeCheck->setChecked(nUActTime);
	}

	long nDvdtClose = ui->m_DvdtCloseCheck->isChecked();
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("DvdtClose_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nDvdtClose);
		ui->m_DvdtCloseCheck->setChecked(nDvdtClose);
	}

	long nIAtresia = ui->m_IAtresiacheck->isChecked();
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("TripILock_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nIAtresia);
		ui->m_IAtresiacheck->setChecked(nIAtresia);
	}

	long nUSetMode = ui->m_CmbUSetMode->currentIndex();
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("USetMode");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nUSetMode);
	}

	if (nUSetMode == 0)
	{
		long nUa = ui->m_UaCheck->isChecked();
		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ua_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(nUa);
			ui->m_UaCheck->setChecked(nUa);
		}

		long nUb = ui->m_UbCheck->isChecked();
		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ub_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(nUb);
			ui->m_UbCheck->setChecked(nUb);
		}

		long nUc = ui->m_UcCheck->isChecked();
		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uc_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(nUc);
			ui->m_UcCheck->setChecked(nUc);
		}

		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uab_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(0);
		}

		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ubc_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(0);
		}

		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uca_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(0);
		}
	}
	if (nUSetMode == 1)
	{
		long nUa = ui->m_UaCheck->isChecked();
		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uab_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(nUa);
			ui->m_UaCheck->setChecked(nUa);
		}

		long nUb = ui->m_UbCheck->isChecked();
		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ubc_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(nUb);
			ui->m_UbCheck->setChecked(nUb);
		}

		long nUc = ui->m_UcCheck->isChecked();
		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uca_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(nUc);
			ui->m_UcCheck->setChecked(nUc);
		}

		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ua_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(0);
		}

		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Ub_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(0);
		}

		pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uc_Check");
		if (pData != NULL)
		{
			pData->m_strValue = QString::number(0);
		}
	}

	long nUab = ui->m_UabcCheck->isChecked();
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Uabc_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nUab);
		ui->m_UabcCheck->setChecked(nUab);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("UAct");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditUAct->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vstart");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditVstart->GetText();
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditVend->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vstep");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditVstep->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("dvdtRate");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(ui->m_EditdvdtRate->text().toFloat() * ui->m_EditDvdtClose->GetText().toFloat(),'f',3);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("UActTime");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditUActTime->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend1");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditVend1->text();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("dvdt1Rate");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(ui->m_Editdvdt1Rate->text().toFloat() * ui->m_EditDvdtClose->GetText().toFloat(), 'f', 3);
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("DvdtClose");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditDvdtClose->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("BeginVal");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditBeginVal->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("EndVal");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditEndVal->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Step");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditStep->GetText();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend2");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditVend2->text();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("HoldTime");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditHoldTime->text();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("IAct");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditIPreTime->text();
	}

	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("ISetValue");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditIAtresiaValue->GetText();
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("BeginI");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditIAtresiaStart->GetText();
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("EndI");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditIAtresiaEnd->GetText();
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("IStep");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditIAtresiaStep->GetText();
	}
	pData = (CDvmData *)m_oLowVolDataGroup.FindByID("Vend3");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditIAtresiaVend2->text();
	}
	accept();
}


void QLowVolAddMultDlg::slot_Exit()
{
	this->close();
}

void QLowVolAddMultDlg::slot_TripVolCheck()
{
	bool state = ui->m_TripVolCheck->isChecked();

	ui->m_EditVstart->setEnabled(state);
	ui->m_EditVend->setEnabled(state);
	ui->m_EditVstep->setEnabled(state);
	ui->m_EditdvdtRate->setEnabled(state);

	ShowOneChecked(ui->m_TripVolCheck, state);
	CheckErrorState();
}
void QLowVolAddMultDlg::slot_UActTimeCheck(bool state)
{
	ShowOneChecked(ui->m_UActTimeCheck, state);

	ui->m_EditVend1->setEnabled(state);
	ui->m_Editdvdt1Rate->setEnabled(state);
}

void QLowVolAddMultDlg::slot_DvdtCloseCheck(bool state)
{
	ShowOneChecked(ui->m_DvdtCloseCheck, state);

	ui->m_EditBeginVal->setEnabled(state);
	ui->m_EditEndVal->setEnabled(state);
	ui->m_EditStep->setEnabled(state);
	ui->m_EditVend2->setEnabled(state);
}

void QLowVolAddMultDlg::slot_IAtresiacheck(bool state)
{
	ShowOneChecked(ui->m_IAtresiacheck, state);

	ui->m_EditIAtresiaStart->setEnabled(state);
	ui->m_EditIAtresiaEnd->setEnabled(state);
	ui->m_EditIAtresiaStep->setEnabled(state);
	ui->m_EditIAtresiaVend2->setEnabled(state);
}


void QLowVolAddMultDlg::ShowOneChecked(QCheckBox* pCurrentCheckBox, bool state) 
{
	if (!state&&
		!ui->m_TripVolCheck->isChecked() &&
		!ui->m_UActTimeCheck->isChecked() &&
		!ui->m_DvdtCloseCheck->isChecked() &&
		!ui->m_IAtresiacheck->isChecked())
		{
			ui->m_TripVolCheck->setChecked(true);
			ui->m_EditVstart->setEnabled(true);
			ui->m_EditVend->setEnabled(true);
			ui->m_EditVstep->setEnabled(true);
			ui->m_EditdvdtRate->setEnabled(true);
			SetApplyTips(/*_T("请至少勾选一个测试项！")*/g_sLangTxt_MaintainatLeastOneItem);
		}
}

void QLowVolAddMultDlg::slot_EditUAct()
{
	
	if (ui->m_EditUAct->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditUAct)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditUAct->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditUAct->setText(QString::number(fv, 'f', 3));

	float fVstart = fv * 1.1;
	ui->m_EditVstart->setText(QString::number(fVstart, 'f', 3));

	float fVend = fv * 0.5;
	ui->m_EditVend->setText(QString::number(fVend, 'f', 3));

	float fVstep = fv * 0.02;
	ui->m_EditVstep->setText(QString::number(fVstep, 'f', 3));

	float fVend1 = fv * 0.5;
	ui->m_EditVend1->setText(QString::number(fVend1, 'f', 3));

}
void QLowVolAddMultDlg::slot_EditUActTime()
{
	
	if (ui->m_EditUActTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditUActTime)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditUActTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_EditUActTime->setText(QString::number(fv, 'f', 3));

	float fHoldTime = fv * 1.2;
	ui->m_EditHoldTime->setText(QString::number(fHoldTime, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditDvdtClose()
{
	
	if (ui->m_EditDvdtClose->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditDvdtClose)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditDvdtClose->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditDvdtClose->setText(QString::number(fv, 'f', 3));

	float fHoldTime = fv * 1.1;
	ui->m_EditBeginVal->setText(QString::number(fHoldTime, 'f', 3));

	float fEndVal = fv * 0.85;
	ui->m_EditEndVal->setText(QString::number(fEndVal, 'f', 3));

	float fStep = fv * 0.02;
	ui->m_EditStep->setText(QString::number(fStep, 'f', 3));

	float fVend2 = fv * 0.5;
	ui->m_EditVend2->setText(QString::number(fVend2, 'f', 3));
}

void QLowVolAddMultDlg::slot_CmbUSetMode(int nIndex)
{
	if (nIndex == 0)
	{
		ui->m_UaCheck->setText("Ua");
		ui->m_UbCheck->setText("Ub");
		ui->m_UcCheck->setText("Uc");
	}
	if (nIndex == 1)
	{
		ui->m_UaCheck->setText("Uab");
		ui->m_UbCheck->setText("Ubc");
		ui->m_UcCheck->setText("Uca");
	}
}

void QLowVolAddMultDlg::slot_EditVstart()
{
	
	if (ui->m_EditVstart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditVstart)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditVstart->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditVstart->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditVend()
{
	
	if (ui->m_EditVend->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditVend)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditVend->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditVend->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditVstep()
{
	
	if (ui->m_EditVstep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditVstep)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditVstep->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditVstep->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditUdvdtRate()
{
	float fv = ui->m_EditdvdtRate->text().toFloat();
	fv = setLimit(0,22.00,fv);
	ui->m_EditdvdtRate->setText(QString::number(fv, 'f', 2));
}
void QLowVolAddMultDlg::slot_EditVend1()
{
	float fv = ui->m_EditVend1->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditVend1->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditPreTime()
{
	float fv = ui->m_EditIPreTime->text().toFloat();
	fv = setLimit(0,20.00,fv);
	ui->m_EditIPreTime->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_Editdvdt1Rate()
{
	float fv = ui->m_Editdvdt1Rate->text().toFloat();
	fv = setLimit(0,22.00,fv);
	ui->m_Editdvdt1Rate->setText(QString::number(fv, 'f', 2));
}
void QLowVolAddMultDlg::slot_EditVend2()
{
	float fv = ui->m_EditVend2->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditVend2->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditBeginVal()
{
	
	if (ui->m_EditBeginVal->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditBeginVal)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditBeginVal->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditBeginVal->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditEndVal()
{
	
	if (ui->m_EditEndVal->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditEndVal)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditEndVal->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditEndVal->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditStep()
{
	
	if (ui->m_EditStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditStep)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditStep->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditStep->setText(QString::number(fv, 'f', 3));
}

void QLowVolAddMultDlg::slot_EditHoldTime()
{
	float fv = ui->m_EditHoldTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_EditHoldTime->setText(QString::number(fv, 'f', 3));
}

void QLowVolAddMultDlg::slot_EditIAtresiaValue()
{
	
	if (ui->m_EditIAtresiaValue->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditIAtresiaValue)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditIAtresiaValue->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditIAtresiaValue->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditIAtresiaStart()
{
	
	if (ui->m_EditIAtresiaStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditIAtresiaStart)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditIAtresiaStart->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditIAtresiaStart->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditIAtresiaEnd()
{
	
	if (ui->m_EditIAtresiaEnd->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditIAtresiaEnd)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditIAtresiaEnd->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditIAtresiaEnd->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditIAtresiaStep()
{
	
	if (ui->m_EditIAtresiaStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditIAtresiaStep)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditIAtresiaStep->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditIAtresiaStep->setText(QString::number(fv, 'f', 3));
}
void QLowVolAddMultDlg::slot_EditIAtresiaVend2()
{
	float fv = ui->m_EditIAtresiaVend2->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditIAtresiaVend2->setText(QString::number(fv, 'f', 3));
}

bool QLowVolAddMultDlg::CheckErrorState()//至少选择一个故障类别
{
	if (!ui->m_TripVolCheck->isChecked())
	{
		return false;
	}
	if (!ui->m_UaCheck->isChecked() && \
		!ui->m_UbCheck->isChecked() && \
		!ui->m_UcCheck->isChecked() && \
		!ui->m_UabcCheck->isChecked())
	{
		ui->m_UaCheck->setChecked(true);
		SetApplyTips(/*_T("请至少勾选一个故障类别！")*/g_sLangTxt_MaintainatLeastOneErrorType);
		return true;
	}

	return false;
}

void QLowVolAddMultDlg::SetApplyTips(CString strTips)
{
	ui->m_labTips->setText(strTips);
	ui->m_labTips->setVisible(true);
	m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}
void QLowVolAddMultDlg::timerEvent(QTimerEvent* ev)
{
	if (ev->timerId() == m_nTipsTime){
		ui->m_labTips->setVisible(false);
	}
}
void QLowVolAddMultDlg::on_m_UaCheck_clicked(bool checked)
{
	CheckErrorState();
}
void QLowVolAddMultDlg::on_m_UbCheck_clicked(bool checked)
{
	CheckErrorState();
}
void QLowVolAddMultDlg::on_m_UcCheck_clicked(bool checked)
{
	CheckErrorState();
}
void QLowVolAddMultDlg::on_m_UabcCheck_clicked(bool checked)
{
	CheckErrorState();
}
void QLowVolAddMultDlg::GetBinarysParas(CExBaseList *pParas)
{
	if (pParas == NULL)
		return;

	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_A, "A");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_B, "B");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_C, "C");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_D, "R");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_E, "E");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_F, "F");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_G, "G");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_H, "H");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID_AndOr, "_AndOr");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B01, "_B01");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B02, "_B02");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B03, "_B03");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B04, "_B04");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B05, "_B05");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B06, "_B06");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B07, "_B07");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWVOL_PARAS_ID__B08, "_B08");
}
void QLowVolAddMultDlg::CheckForBinarys(CExBaseList *pParas, CString strMapID, CString strID)
{
	//检查开关量对应数据是否存在，存在则更新数据，不存在则添加
	if (pParas == NULL)
		return;
	CDvmData *pDvmData;
	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strMapID);
	if (pData != NULL)
	{
		pDvmData = (CDvmData *)m_oLowVolDataGroup.FindByID(strID);
		if (pDvmData != NULL)
		{
			pDvmData->m_strValue = pData->m_strValue;
		}
	}
}