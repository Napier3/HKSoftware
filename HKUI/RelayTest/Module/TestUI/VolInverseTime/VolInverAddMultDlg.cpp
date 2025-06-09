#include "VolInverAddMultDlg.h"
#include "ui_VolInverAddMultDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SoftKeyboard/SoftKeyBoard.h"

#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "VolInverResultEstimateDlg.h"
#include "VolInverBinarysDlg.h"
#include "../Distance/DistanceCommonParasDlg.h"

extern void  Stt_Global_SettingParent(QWidget *parent);	

QVolInverAddMultDlg::QVolInverAddMultDlg(QWidget *parent ):
    QDialog(parent),
    ui(new Ui::QVolInverAddMultDlg)
{
    ui->setupUi(this);

	/*CString strText;
	strText = _T(“添加系列");*/
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);
	
	m_pDataGroup = NULL;

	SetParasFont();
	InitLanuage();
	/*OpenXmlFile();
	SetDatas(&m_oDataGroup);*/
	init();
	initConnections();
 
}


QVolInverAddMultDlg::~QVolInverAddMultDlg()
{
    delete ui;
}

void QVolInverAddMultDlg::SetParasFont()
{
    ui->groupBox_AddTestPoint->setFont(*g_pSttGlobalFont);
    ui->groupBox_FaultTypeChoose->setFont(*g_pSttGlobalFont);
   /* ui->m_pCTLabel->setFont(*g_pSttGlobalFont);
    ui->m_pCmb_CT->setFont(*g_pSttGlobalFont);*/
    ui->m_pErrorTypeLabel->setFont(*g_pSttGlobalFont);
    ui->m_pCmb_ErrorType->setFont(*g_pSttGlobalFont);
    ui->m_pFPhaseDiffLabel->setFont(*g_pSttGlobalFont);
    ui->m_pFPhaseDiffEdit->setFont(*g_pSttGlobalFont);
    ui->m_pDLCurrentLabel->setFont(*g_pSttGlobalFont);
    ui->m_pDLCurrentEdit->setFont(*g_pSttGlobalFont);
    ui->m_pFreLabel->setFont(*g_pSttGlobalFont);
    ui->m_pFreEdit->setFont(*g_pSttGlobalFont);
    ui->m_pRelativeLabel->setFont(*g_pSttGlobalFont);
    ui->m_pRelativeEdit->setFont(*g_pSttGlobalFont);
    ui->m_pAbsAddLabel->setFont(*g_pSttGlobalFont);
    ui->m_pAbsAddEdit->setFont(*g_pSttGlobalFont);
    ui->m_pAbsDownLabel->setFont(*g_pSttGlobalFont);
    ui->m_pAbsDownEdit->setFont(*g_pSttGlobalFont);
    ui->m_pOK_PushButton->setFont(*g_pSttGlobalFont);
    ui->m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
}


void QVolInverAddMultDlg::OpenXmlFile()
{
	CString strPath = stt_ui_GetParasFile("VolInverseTime_Paras.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pDataGroup->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QVolInverAddMultDlg::SaveVolInverFile(CDataGroup *pParas)
{
	CString strPath = stt_ui_GetParasFile("VolInverseTime_Paras_Debug.xml");
	pParas->SaveXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void QVolInverAddMultDlg::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(ui->groupBox_AddTestPoint, g_sLangID_Vol_TestPointsAdd, XLang_Ctrls_QGroupBox);//测试点添加
	xlang_SetLangStrToWidget(ui->groupBox_FaultTypeChoose, g_sLangID_Vol_FaultTypeSelect, XLang_Ctrls_QGroupBox);//故障类别选择
	xlang_SetLangStrToWidget(ui->gridGroupBox, g_sLangID_StateEstimate_ResultEstimate, XLang_Ctrls_QGroupBox);//结果评估
	
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_InitVoltChange);//电压变化始值(V):
	strtemp += "(V):";
	ui->m_pVChangeStartLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_FinalVoltChange);//电压变化终值(V):
	strtemp += "(V):";
	ui->m_pVChangeEndLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_VoltChangeStep);//电压变化步长(V):
	strtemp += "(V):";
	ui->m_pVChangeStepLabel->setText(strtemp);

	xlang_SetLangStrToWidget(ui->m_pAB_CheckBox, g_sLangID_Native_ShortAB, XLang_Ctrls_QCheckBox);//AB短路
	xlang_SetLangStrToWidget(ui->m_pBC_CheckBox, g_sLangID_Native_ShortBC, XLang_Ctrls_QCheckBox);//BC短路
	xlang_SetLangStrToWidget(ui->m_pCA_CheckBox, g_sLangID_Native_ShortCA, XLang_Ctrls_QCheckBox);//CA短路
	xlang_SetLangStrToWidget(ui->m_pABC_CheckBox, g_sLangID_Native_ShortABC, XLang_Ctrls_QCheckBox);//三相短路

	xlang_SetLangStrToWidget(ui->m_pDLCurrentLabel, g_sLangID_Impedance_ShortCurr, XLang_Ctrls_QLabel);//短路电流(A):
	xlang_GetLangStrByFile(strtemp, g_sLangID_Gradient_Phase);//相位差(°):
	strtemp += QString::fromLocal8Bit("(°):");
	ui->m_pFPhaseDiffLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Frequency);//频率(Hz):
	strtemp += ":";
	ui->m_pFreLabel->setText(strtemp);

	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_ErrorType);//误差类型:
	strtemp += ":";
	ui->m_pErrorTypeLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	strtemp += ":";
	ui->m_pRelativeLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):+";
	ui->m_pAbsAddLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):-";
	ui->m_pAbsDownLabel->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_pOK_PushButton, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_pCancel_PushButton, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

}

void QVolInverAddMultDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas == NULL)
		return;
	m_pDataGroup = pParas;

	CheckAllPresence();

	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		SetValueToPage(pData);
	}
	
}

void QVolInverAddMultDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG)
	{
        ui->m_pFPhaseDiffEdit->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		//ui->m_pFPhaseDiffEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ)
	{
		ui->m_pFreEdit->setText(CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//ui->m_pFreEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
	//{
 //       ui->m_pCmb_CT->setCurrentIndex(pData->m_strValue.toInt());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ErrorLogic)
	{
        ui->m_pCmb_ErrorType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStart)
	{
        ui->m_pVChangeStartEdit->setText(CheckDataMinMax(pData->m_strValue,g_oLocalSysPara.m_fAC_VolMax,0,3));
		//ui->m_pVChangeStartEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeFinal)
	{
        ui->m_pVChangeEndEdit->setText(CheckDataMinMax(pData->m_strValue,g_oLocalSysPara.m_fAC_VolMax,0,3));
		//ui->m_pVChangeEndEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStep)
	{
        ui->m_pVChangeStepEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		//ui->m_pVChangeStepEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR)
	{
        ui->m_pDLCurrentEdit->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		//ui->m_pDLCurrentEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 120, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS)
	{
        ui->m_pAbsAddEdit->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//ui->m_pAbsAddEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS)
	{
        ui->m_pAbsDownEdit->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//ui->m_pAbsDownEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr)
	{
        ui->m_pRelativeEdit->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
		//ui->m_pRelativeEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_A_CHECK)
	{
        ui->m_pAN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_B_CHECK)
	{
        ui->m_pBN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_C_CHECK)
	{
        ui->m_pCN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_AB_CHECK)
	{
        ui->m_pAB_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_BC_CHECK)
	{
        ui->m_pBC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CA_CHECK)
	{
        ui->m_pCA_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_3U0_CHECK)
	{
        ui->m_p3U0_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_U2_CHECK)
	{
        ui->m_pU2_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABC_CHECK)
	{
        ui->m_pABC_CheckBox->setChecked(pData->m_strValue == "1");
	}

	if (ui->m_pAN_CheckBox->isChecked() || ui->m_pBN_CheckBox->isChecked() || ui->m_pCN_CheckBox->isChecked() ||
		ui->m_pAB_CheckBox->isChecked() || ui->m_pBC_CheckBox->isChecked() || ui->m_pCA_CheckBox->isChecked() ||
		ui->m_pABC_CheckBox->isChecked() || ui->m_p3U0_CheckBox->isChecked() || ui->m_pU2_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}
void QVolInverAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;
	CheckAllPresence();
	//20240614 luozibing 将界面中的参数保存到链表中
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}

	SaveVolInverFile(pParas);
}

void QVolInverAddMultDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG)
	{
        pData->m_strValue = ui->m_pFPhaseDiffEdit->text();
		//pData->m_strValue = ui->m_pFPhaseDiffEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ)
	{
        pData->m_strValue = ui->m_pFreEdit->text();
		//pData->m_strValue = ui->m_pFreEdit->GetText();
	}
	/*else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
	{
        pData->m_strValue.setNum(ui->m_pCmb_CT->currentIndex());
	}*/
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ErrorLogic)
	{
        pData->m_strValue.setNum(ui->m_pCmb_ErrorType->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStart)
	{
        pData->m_strValue = ui->m_pVChangeStartEdit->text();
		//pData->m_strValue = ui->m_pVChangeStartEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeFinal)
	{
        pData->m_strValue = ui->m_pVChangeEndEdit->text();
		//pData->m_strValue = ui->m_pVChangeEndEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStep)
	{
        pData->m_strValue = ui->m_pVChangeStepEdit->text();
		//pData->m_strValue = ui->m_pVChangeStepEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR)
	{
        pData->m_strValue = ui->m_pDLCurrentEdit->text();
		//pData->m_strValue = ui->m_pDLCurrentEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS)
	{
        pData->m_strValue = ui->m_pAbsAddEdit->text();
		//pData->m_strValue = ui->m_pAbsAddEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS)
	{
        pData->m_strValue = ui->m_pAbsDownEdit->text();
		//pData->m_strValue = ui->m_pAbsDownEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr)
	{
        pData->m_strValue = ui->m_pRelativeEdit->text();
		//pData->m_strValue = ui->m_pRelativeEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_A_CHECK)
	{
        bvalue = ui->m_pAN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_B_CHECK)
	{
        bvalue = ui->m_pBN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_C_CHECK)
	{
        bvalue = ui->m_pCN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_AB_CHECK)
	{
        bvalue = ui->m_pAB_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_BC_CHECK)
	{
        bvalue = ui->m_pBC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CA_CHECK)
	{
        bvalue = ui->m_pCA_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_3U0_CHECK)
	{
        bvalue = ui->m_p3U0_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_U2_CHECK)
	{
        bvalue = ui->m_pU2_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABC_CHECK)
	{
        bvalue = ui->m_pABC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
}

void QVolInverAddMultDlg::initData()
{
#ifdef _PSX_QT_WINDOWS_
    ui->m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));
    ui->m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));
#else
    ui->m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/check.png"));
    ui->m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif
	

}
void QVolInverAddMultDlg::initBaseData()
{
	//ui->m_pCmb_CT->addItems(QStringList()<<g_sLangTxt_CBOperate_CTPos1/*("指向母线")*/<<g_sLangTxt_CBOperate_TPos1/*("指向线路")*/);
	//ui->m_pCmb_CT->setCurrentIndex(nCTPos);

	ui->m_pCmb_ErrorType->addItem(g_sLangTxt_StateEstimate_AbsError/*("绝对误差")*/);
	ui->m_pCmb_ErrorType->addItem(g_sLangTxt_StateEstimate_RelError/*("相对误差")*/);
	ui->m_pCmb_ErrorType->addItem(g_sLangTxt_StateEstimate_AbsError + "or" + g_sLangTxt_StateEstimate_RelError/*("相对误差or绝对误差")*/);
	ui->m_pCmb_ErrorType->addItem(g_sLangTxt_StateEstimate_AbsError + "&" + g_sLangTxt_StateEstimate_RelError/*("相对误差&绝对误差")*/);
	ui->m_pCmb_ErrorType->addItem(g_sLangTxt_StateEstimate_CombinationError/*("组合误差")*/);
	ui->m_pCmb_ErrorType->addItem(g_sLangTxt_Distance_ErrorNot/*("不评估")*/);
	ui->m_pCmb_ErrorType->setCurrentIndex(0);

}

void QVolInverAddMultDlg::init()
{
	initBaseData();
	initData();
	SetParasFont();
}

void QVolInverAddMultDlg::initConnections()
{
    /*connect(ui->m_pPreFTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePreFTime_editingFinished()));
    connect(ui->m_pFTimeMarginEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFTimeMargin_editingFinished()));
    connect(ui->m_pVoltageEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneVoltage_editingFinished()));
    connect(ui->m_pCurrentEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneCurrent_editingFinished()));
    connect(ui->m_pPhaseDiffEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePhaseDiff_editingFinished()));*/

    connect(ui->m_pVChangeStartEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneVChangeStart_editingFinished()));
    connect(ui->m_pVChangeEndEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneVChangeEnd_editingFinished()));
    connect(ui->m_pVChangeStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneVChangeStep_editingFinished()));
    connect(ui->m_pDLCurrentEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLCurrent_editingFinished()));
    connect(ui->m_pFPhaseDiffEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFPhaseDiff_editingFinished()));
    connect(ui->m_pFreEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFre_editingFinished()));
    connect(ui->m_pRelativeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneRelative_editingFinished()));
    connect(ui->m_pAbsAddEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAbsAdd_editingFinished()));
    connect(ui->m_pAbsDownEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAbsDown_editingFinished()));


    //connect(ui->m_pCmb_CT, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_CT_Changed(int)));
    connect(ui->m_pCmb_ErrorType, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_ErrorType_Changed(int)));

    connect(ui->m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_OKClick()));
    connect(ui->m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_CancelClick()));
    //connect(ui->m_pCommonParas_PushButton, SIGNAL(clicked ()), this, SLOT(slot_pbn_CommonParasClicked()));
    //connect(ui->m_pResults_pushButton, SIGNAL(clicked ()), this, SLOT(slot_pbn_ResultsClicked()));

    connect(ui->m_pAN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pBN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pCN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pAB_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pBC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pCA_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pABC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_p3U0_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));
    connect(ui->m_pU2_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_faultTypeClicked()));

	

}

void QVolInverAddMultDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ErrorLogic);
	//CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStart);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeFinal);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_CurrentChangeStep);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS);
	CheckForPresence(STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr);
}

void QVolInverAddMultDlg::CheckForPresence(CString strID)
{
	//20240624 luozibing检查ID对应数据是否存在、不存在则添加
	if(m_pDataGroup == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pDataGroup->FindByID(strID);
	if(pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_VolInverTime_PARAS_ID_DEFAULT;
		m_pDataGroup->AddNewChild(pNew);
	}
}


float QVolInverAddMultDlg::slot_lne_Changed(QLineEdit* pLineEdit)
{
	if (pLineEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)pLineEdit)->IsSetting())
		{
			return NULL;
		}
	}

	if (pLineEdit->text().isEmpty())
	{
		pLineEdit->setText("0.000");
	}

	QString strValue = pLineEdit->text();
	if (strValue.right(1).contains("."))
	{
		strValue.append("000");
	}
	float fv = strValue.toFloat();
	fv = setLimit(0,999.999,fv);
	return fv;
}

void QVolInverAddMultDlg::slot_lneVChangeStart_editingFinished()
{
    float fv  = slot_lne_Changed(ui->m_pVChangeStartEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
    ui->m_pVChangeStartEdit->setText(QString::number(fv,'f',3));
    ui->m_pVChangeStartEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneVChangeEnd_editingFinished()
{
    float fv  = slot_lne_Changed(ui->m_pVChangeEndEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
    ui->m_pVChangeEndEdit->setText(QString::number(fv,'f',3));
    ui->m_pVChangeEndEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneVChangeStep_editingFinished()
{
    float fv = slot_lne_Changed(ui->m_pVChangeStepEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
    ui->m_pVChangeStepEdit->setText(QString::number(fv,'f',3));
    ui->m_pVChangeStepEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneDLCurrent_editingFinished()
{
    float fv = slot_lne_Changed(ui->m_pDLCurrentEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,fv);
    ui->m_pDLCurrentEdit->setText(QString::number(fv,'f',3));
    ui->m_pDLCurrentEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneFPhaseDiff_editingFinished()
{
    float fv  = slot_lne_Changed(ui->m_pFPhaseDiffEdit);
	fv = setAngleLimitEx(fv);
    ui->m_pFPhaseDiffEdit->setText(QString::number(fv,'f',3));
    ui->m_pFPhaseDiffEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneFre_editingFinished()
{
    float fv  = slot_lne_Changed(ui->m_pFreEdit);
    ui->m_pFreEdit->setText(QString::number(fv,'f',3));
    ui->m_pFreEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneRelative_editingFinished()
{
    float fv = slot_lne_Changed(ui->m_pRelativeEdit);
    ui->m_pRelativeEdit->setText(QString::number(fv,'f',3));
    ui->m_pRelativeEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneAbsAdd_editingFinished()
{
    float fv  = slot_lne_Changed(ui->m_pAbsAddEdit);
    ui->m_pAbsAddEdit->setText(QString::number(fv,'f',3));
    ui->m_pAbsAddEdit->setCursorPosition(0);
}

void QVolInverAddMultDlg::slot_lneAbsDown_editingFinished()
{
    float fv  = slot_lne_Changed(ui->m_pAbsDownEdit);
    ui->m_pAbsDownEdit->setText(QString::number(fv,'f',3));
    ui->m_pAbsDownEdit->setCursorPosition(0);
}

//void QVolInverAddMultDlg::slot_cmb_CT_Changed( int nIndex)
//{
//	//nCTPos = nIndex;
//}

void QVolInverAddMultDlg::slot_cmb_ErrorType_Changed( int nIndex)
{
	//nCTPos = nIndex;
}

void QVolInverAddMultDlg::slot_chb_faultTypeClicked()
{
    if (ui->m_pAN_CheckBox->isChecked()||ui->m_pBN_CheckBox->isChecked()||ui->m_pCN_CheckBox->isChecked()||
        ui->m_pAB_CheckBox->isChecked()||ui->m_pBC_CheckBox->isChecked()||ui->m_pCA_CheckBox->isChecked()||
        ui->m_pABC_CheckBox->isChecked()||ui->m_p3U0_CheckBox->isChecked()||ui->m_pU2_CheckBox->isChecked())
	{
        ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
        ui->m_pOK_PushButton->setDisabled(true);
	}
}
void QVolInverAddMultDlg::slot_pbn_OKClick()
{
	accept();
}

void QVolInverAddMultDlg::slot_pbn_CancelClick()
{
	close();
}

