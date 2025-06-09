#include "CurrInverAddMultDlg.h"
#include "ui_CurrInverAddMultDlg.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QCurrInverAddMultDlg::QCurrInverAddMultDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCurrInverAddMultDlg)
{
    ui->setupUi(this);
	m_pDataGroup = NULL;

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);

	InitUI();
	initConnections();
}

QCurrInverAddMultDlg::~QCurrInverAddMultDlg()
{
    delete ui;
}

void QCurrInverAddMultDlg::InitUI()
{
#ifdef _PSX_QT_WINDOWS_
	ui->pbn_Ok->setIcon (QPixmap( ":/image/check.png"));
	ui->pbn_Cancel->setIcon (QPixmap( ":/image/Cancel.png"));
#else
	ui->pbn_Ok->setIcon (QPixmap( ":/ctrls/images/check.png"));
	ui->pbn_Cancel->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif

	if (ui->chb_AN->isChecked()||ui->chb_BN->isChecked()||ui->chb_CN->isChecked()||
		ui->chb_AB->isChecked()||ui->chb_BC->isChecked()||ui->chb_CA->isChecked()||
		ui->chb_ABC->isChecked()||ui->chb_3I0->isChecked()||ui->chb_I2->isChecked()||
		ui->chb_IaIbIc->isChecked()||ui->chb_A->isChecked()||ui->chb_B->isChecked()||ui->chb_C->isChecked())
	{
		ui->pbn_Ok->setDisabled(false);
	}
	else
	{
		ui->pbn_Ok->setDisabled(true);
	}

	ui->m_cmbSelect->addItems(QStringList()<<g_sLangTxt_CrrInverTime_IAmp/*"电流幅值"*/<<g_sLangTxt_CrrInverTime_IPh/*"电流相位"*/);
	ui->m_cmbErrorLogic->addItems(QStringList() << g_sLangTxt_StateEstimate_AbsError/*"绝对误差"*/ << g_sLangTxt_StateEstimate_RelError/*"相对误差"*/ << \
		g_sLangTxt_StateEstimate_AbsError + "or" + g_sLangTxt_StateEstimate_RelError/*("相对误差or绝对误差")*/ << \
		g_sLangTxt_StateEstimate_AbsError + "&" + g_sLangTxt_StateEstimate_RelError/*("相对误差&绝对误差")*/ << \
		g_sLangTxt_StateEstimate_CombinationError/*"组合误差"*/ << g_sLangTxt_Distance_ErrorNot/*"不评估"*/);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	InitFont();
	InitLanuage();
}

void QCurrInverAddMultDlg::InitFont()
{
	ui->groupBox->setFont(*g_pSttGlobalFont);
	ui->groupBox_2->setFont(*g_pSttGlobalFont);
	ui->groupBox_3->setFont(*g_pSttGlobalFont);
	ui->groupBox_4->setFont(*g_pSttGlobalFont);

	ui->m_labSelect->setFont(*g_pSttGlobalFont);
	ui->m_labFaultVolt->setFont(*g_pSttGlobalFont);
	ui->m_labFaultAngle->setFont(*g_pSttGlobalFont);
	ui->m_labHz->setFont(*g_pSttGlobalFont);
	ui->m_labChangeStart->setFont(*g_pSttGlobalFont);
	ui->m_labChangeFinal->setFont(*g_pSttGlobalFont);
	ui->m_labChangeStep->setFont(*g_pSttGlobalFont);

	ui->m_cmbSelect->setFont(*g_pSttGlobalFont);
	ui->m_lineFaultVolt->setFont(*g_pSttGlobalFont);
	ui->m_lineFaultAngle->setFont(*g_pSttGlobalFont);
	ui->m_lineHz->setFont(*g_pSttGlobalFont);
	ui->m_lineChangeStart->setFont(*g_pSttGlobalFont);
	ui->m_lineChangeFinal->setFont(*g_pSttGlobalFont);
	ui->m_lineChangeStep->setFont(*g_pSttGlobalFont);

	ui->chb_AN->setFont(*g_pSttGlobalFont);
	ui->chb_BN->setFont(*g_pSttGlobalFont);
	ui->chb_CN->setFont(*g_pSttGlobalFont);
	ui->chb_AB->setFont(*g_pSttGlobalFont);
	ui->chb_BC->setFont(*g_pSttGlobalFont);
	ui->chb_CA->setFont(*g_pSttGlobalFont);
	ui->chb_ABC->setFont(*g_pSttGlobalFont);
	ui->chb_IaIbIc->setFont(*g_pSttGlobalFont);
	ui->chb_3I0->setFont(*g_pSttGlobalFont);
	ui->chb_I2->setFont(*g_pSttGlobalFont);
	ui->chb_A->setFont(*g_pSttGlobalFont);
	ui->chb_B->setFont(*g_pSttGlobalFont);
	ui->chb_C->setFont(*g_pSttGlobalFont);

	ui->m_labErrorLogic->setFont(*g_pSttGlobalFont);
	ui->m_cmbErrorLogic->setFont(*g_pSttGlobalFont);
	ui->m_labRelErr->setFont(*g_pSttGlobalFont);
	ui->m_lineRelErr->setFont(*g_pSttGlobalFont);
	ui->m_labAbsErr->setFont(*g_pSttGlobalFont);
	ui->m_labPlus->setFont(*g_pSttGlobalFont);
	ui->m_linePlus->setFont(*g_pSttGlobalFont);
	ui->m_labAbsErr_2->setFont(*g_pSttGlobalFont);
	ui->m_labMinus->setFont(*g_pSttGlobalFont);
	ui->m_lineMinus->setFont(*g_pSttGlobalFont);

	ui->pbn_Ok->setFont(*g_pSttGlobalFont);
	ui->pbn_Cancel->setFont(*g_pSttGlobalFont);
}

void QCurrInverAddMultDlg::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(ui->groupBox, g_sLangID_Gradient_Failure, XLang_Ctrls_QGroupBox);//故障态
	xlang_SetLangStrToWidget(ui->groupBox_2, g_sLangID_Vol_TestPointsAdd, XLang_Ctrls_QGroupBox);//测试点添加
	xlang_SetLangStrToWidget(ui->groupBox_3, g_sLangID_Swing_FaultType, XLang_Ctrls_QGroupBox);//故障类型
	xlang_SetLangStrToWidget(ui->groupBox_4, g_sLangID_StateEstimate_ResultEstimate, XLang_Ctrls_QGroupBox);//结果评估

	xlang_SetLangStrToWidget(ui->m_labSelect, g_sLangID_Impedance_VarChoose, XLang_Ctrls_QLabel);//变量选择:
	xlang_SetLangStrToWidget(ui->m_labFaultVolt, g_sLangID_State_ShortU, XLang_Ctrls_QLabel);//短路电压(V):
	xlang_SetLangStrToWidget(ui->m_labFaultAngle, g_sLangID_Swing_Phase, XLang_Ctrls_QLabel);//相位(°):
	xlang_GetLangStrByFile(strtemp, g_sLangID_Frequency);//频率(Hz):
	strtemp += ":";
	ui->m_labHz->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_labChangeStart, g_sLangID_Gradient_Init, XLang_Ctrls_QLabel);//变化始值(A):
	xlang_SetLangStrToWidget(ui->m_labChangeFinal, g_sLangID_Gradient_Finish, XLang_Ctrls_QLabel);//变化终值(A):
	xlang_SetLangStrToWidget(ui->m_labChangeStep, g_sLangID_Gradient_Step, XLang_Ctrls_QLabel);//变化步长(A):
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_ErrorType);//误差类型:
	strtemp += ":";
	ui->m_labErrorLogic->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	strtemp += ":";
	ui->m_labRelErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s)+:
	strtemp += "(s):";
	ui->m_labAbsErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s)-:
	strtemp += "(s):";
	ui->m_labAbsErr_2->setText(strtemp);
	xlang_SetLangStrToWidget(ui->pbn_Ok, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->pbn_Cancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

}

void QCurrInverAddMultDlg::initConnections()
{
	connect(ui->chb_AN,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_BN,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_CN,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_AB,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_BC,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_CA,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_ABC,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_3I0,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_I2,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_IaIbIc,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_A,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_B,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
	connect(ui->chb_C,SIGNAL(stateChanged(int)), this, SLOT(slot_chb_faultTypeClicked()));
}

void QCurrInverAddMultDlg::OpenXmlFile()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/CurrInverseTime_Paras.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pDataGroup->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QCurrInverAddMultDlg::SaveCurInverFile(CDataGroup *pParas)
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/CurrInverseTime_debugFile.xml");
	pParas->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void QCurrInverAddMultDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStart);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeFinal);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStep);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AN_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BN_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CN_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IaIbIc_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_3I0_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_I2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C_CHECK);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ErrorLogic);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS);
}

void QCurrInverAddMultDlg::CheckForPresence(CString strID)
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
		pNew->m_strValue = STT_MULTI_MACRO_CurrInverTime_PARAS_ID_DEFAULT;
		m_pDataGroup->AddNewChild(pNew);
	}
}

void QCurrInverAddMultDlg::SetDatas(CDataGroup *pDataset)
{//240612 luozibing 从Distance_Paras.xml中获取数据并显示
	if (pDataset == NULL)
		return;
	m_pDataGroup = pDataset;

	CheckAllPresence();

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	while(pos!=NULL)
	{
		pData = (CDvmData*)pDataset->GetNext(pos);
		SetValueToPage(pData);
	}
	pData = (CDvmData*)pDataset->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select);
	on_m_cmbSelect_currentIndexChanged(pData->m_strValue.toInt());
}

void QCurrInverAddMultDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select)
	{
		ui->m_cmbSelect->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt)
	{
		ui->m_lineFaultVolt->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		//ui->m_lineFaultVolt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 120, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG)
	{
		ui->m_lineFaultAngle->setText(CheckDataMinMax(pData->m_strValue,360,-360,2));
		//ui->m_lineFaultAngle->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre)
	{
		ui->m_lineHz->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//ui->m_lineHz->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStart)
	{
		ui->m_lineChangeStart->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		//ui->m_lineChangeStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeFinal)
	{
		ui->m_lineChangeFinal->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		//ui->m_lineChangeFinal->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStep)
	{
		ui->m_lineChangeStep->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		//ui->m_lineChangeStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AN_CHECK)
	{
		ui->chb_AN->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BN_CHECK)
	{
		ui->chb_BN->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CN_CHECK)
	{
		ui->chb_CN->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AB_CHECK)
	{
		ui->chb_AB->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BC_CHECK)
	{
		ui->chb_BC->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CA_CHECK)
	{
		ui->chb_CA->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_3I0_CHECK)
	{
		ui->chb_3I0->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_I2_CHECK)
	{
		ui->chb_I2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IaIbIc_CHECK)
	{
		ui->chb_IaIbIc->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABC_CHECK)
	{
		ui->chb_ABC->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A_CHECK)
	{
		ui->chb_A->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B_CHECK)
	{
		ui->chb_B->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C_CHECK)
	{
		ui->chb_C->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ErrorLogic)
	{
		ui->m_cmbErrorLogic->setCurrentIndex(pData->m_strValue.toInt());
	}
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr)
	{
		ui->m_lineRelErr->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
		//ui->m_lineRelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS)
	{
		ui->m_linePlus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//ui->m_linePlus->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS)
	{
		ui->m_lineMinus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//ui->m_lineMinus->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}	
}

void QCurrInverAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;
	m_pDataGroup = pParas;
	CheckAllPresence();
	//20240614 luozibing 将界面中的参数保存到链表中
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
	GetPageFromSelect(); //zhangyq 将界面中变量选择不同时，相同编辑框的数据保存到链表中不同的id中
	SaveCurInverFile(pParas);
}

void QCurrInverAddMultDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select)
	{
		pData->m_strValue.setNum(ui->m_cmbSelect->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt)
	{
		pData->m_strValue = ui->m_lineFaultVolt->text();
		//pData->m_strValue = ui->m_lineFaultVolt->GetText();
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG)
	//{
	//	pData->m_strValue = ui->m_lineFaultAngle->text();
	//}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre)
	{
		pData->m_strValue = ui->m_lineHz->text();
		//pData->m_strValue = ui->m_lineHz->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStart)
	{
		pData->m_strValue = ui->m_lineChangeStart->text();
		//pData->m_strValue = ui->m_lineChangeStart->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeFinal)
	{
		pData->m_strValue = ui->m_lineChangeFinal->text();
		///pData->m_strValue = ui->m_lineChangeFinal->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStep)
	{
		pData->m_strValue = ui->m_lineChangeStep->text();
		//pData->m_strValue = ui->m_lineChangeStep->GetText();
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AN_CHECK)
	{
		bvalue = ui->chb_AN->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BN_CHECK)
	{
		bvalue = ui->chb_BN->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CN_CHECK)
	{
		bvalue = ui->chb_CN->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AB_CHECK)
	{
		bvalue = ui->chb_AB->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BC_CHECK)
	{
		bvalue = ui->chb_BC->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CA_CHECK)
	{
		bvalue = ui->chb_CA->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_3I0_CHECK)
	{
		bvalue = ui->chb_3I0->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_I2_CHECK)
	{
		bvalue = ui->chb_I2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IaIbIc_CHECK)
	{
		bvalue = ui->chb_IaIbIc->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABC_CHECK)
	{
		bvalue = ui->chb_ABC->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A_CHECK)
	{
		bvalue = ui->chb_A->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B_CHECK)
	{
		bvalue = ui->chb_B->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C_CHECK)
	{
		bvalue = ui->chb_C->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ErrorLogic)
	{
		pData->m_strValue.setNum(ui->m_cmbErrorLogic->currentIndex());
	}
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr)
	{
		pData->m_strValue = ui->m_lineRelErr->text();
		//pData->m_strValue = ui->m_lineRelErr->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS)
	{
		pData->m_strValue = ui->m_linePlus->text();
		//pData->m_strValue = ui->m_linePlus->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS)
	{
		pData->m_strValue = ui->m_lineMinus->text();
		//pData->m_strValue = ui->m_lineMinus->GetText();
	}
}

void QCurrInverAddMultDlg::on_m_cmbSelect_currentIndexChanged(int index)
{
	QString strStart,strEnd,strStep;
	strStart=/*"变化始值"*/g_sLangTxt_Gradient_Init;
	strEnd=/*"变化终值"*/g_sLangTxt_Gradient_Finish;
	strStep=/*"变化步长"*/g_sLangTxt_Gradient_Step;

	if (ui->m_cmbSelect->currentText()==/*"电流幅值"*/g_sLangTxt_CrrInverTime_IAmp)//变换单位为A
	{
		ui->m_labChangeStart->setText(strStart+"(A):");	
		ui->m_labChangeFinal->setText(strEnd+"(A):");	
		ui->m_labChangeStep->setText(strStep+"(A):");

		ui->m_labFaultAngle->setText(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase + ":");
		GetValueFromSelect(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);

		ui->chb_3I0->setVisible(true);
		ui->chb_I2->setVisible(true);
		ui->chb_A->setVisible(true);
		ui->chb_B->setVisible(true);
		ui->chb_C->setVisible(true);
	}
	else if (ui->m_cmbSelect->currentText()==/*"电流相位"*/g_sLangTxt_CrrInverTime_IPh)//变换单位为°
	{
		ui->m_labChangeStart->setText(/*strStart + "(°)"*/g_sLangTxt_CrrInverTime_ChangeStart + ":");
		ui->m_labChangeFinal->setText(/*strEnd+"(°)"*/g_sLangTxt_CrrInverTime_ChangeFinish + ":");
		ui->m_labChangeStep->setText(/*strStep+"(°)"*/g_sLangTxt_CrrInverTime_ChangeStep + ":");

		ui->m_labFaultAngle->setText(/*tr("短路电流(A)")*/g_sLangTxt_Impedance_ShortCurr /*+ ":"*/);
		GetValueFromSelect(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);

		ui->chb_3I0->setVisible(false);
		ui->chb_I2->setVisible(false);
		ui->chb_A->setVisible(false);
		ui->chb_B->setVisible(false);
		ui->chb_C->setVisible(false);
	}
}

void QCurrInverAddMultDlg::GetValueFromSelect(CString strID)
{
	if(m_pDataGroup == NULL)
		return;

	CDvmData *pData = NULL;

	CheckForPresence(strID);
	pData = (CDvmData *)m_pDataGroup->FindByID(strID);
	if (pData != NULL)
	{
		float fValue;
		fValue = CString_To_double(pData->m_strValue);
		if (ui->m_cmbSelect->currentText()==/*"电流幅值"*/g_sLangTxt_CrrInverTime_IAmp )
		{
			ui->m_lineFaultAngle->setText(QString::number(fValue, 'f', 2));
		}
		else
		{
			ui->m_lineFaultAngle->setText(QString::number(fValue, 'f', 3));
		}
	}
}

void QCurrInverAddMultDlg::on_m_lineFaultVolt_editingFinished()
{
	//if (ui->m_lineFaultVolt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineFaultVolt)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineFaultVolt->text().toFloat();
	float fmax = g_oLocalSysPara.m_fAC_VolMax;//不知道电压最大值是多少,先写999.999
	fv = setLimit(0,fmax,fv);
	ui->m_lineFaultVolt->setText(QString::number(fv, 'f', 3));
}

void QCurrInverAddMultDlg::on_m_lineFaultAngle_editingFinished()
{
	//if (ui->m_lineFaultAngle->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineFaultAngle)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineFaultAngle->text().toFloat();
	if (ui->m_cmbSelect->currentText()==/*"电流幅值"*/g_sLangTxt_CrrInverTime_IAmp )
	{
		fv = setAngleLimitEx(fv);
		ui->m_lineFaultAngle->setText(QString::number(fv,'f',2));
	}
	else
	{
		ui->m_lineFaultAngle->setText(QString::number(fv,'f',3));
	}
}

void QCurrInverAddMultDlg::GetPageFromSelect()
{
	if(m_pDataGroup == NULL)
		return;

	CDvmData *pData = NULL;

	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);
	CheckForPresence(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);

	if (ui->m_cmbSelect->currentText()==/*"电流幅值"*/g_sLangTxt_CrrInverTime_IAmp)
	{
		pData = (CDvmData *)m_pDataGroup->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);
		if (pData != NULL)
		{
			pData->m_strValue = ui->m_lineFaultAngle->text();
		}
	}
	else
	{
		pData = (CDvmData *)m_pDataGroup->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);
		if (pData != NULL)
		{
			pData->m_strValue = ui->m_lineFaultAngle->text();
		}	
	}
}

void QCurrInverAddMultDlg::on_m_lineHz_editingFinished()
{
	//if (ui->m_lineHz->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineHz)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineHz->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_lineHz->setText(QString::number(fv, 'f', 3));
}

void QCurrInverAddMultDlg::on_m_lineChangeStart_editingFinished()
{
	//if (ui->m_lineChangeStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineChangeStart)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineChangeStart->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_lineChangeStart->setText(QString::number(fv,'f',3));
}

void QCurrInverAddMultDlg::on_m_lineChangeFinal_editingFinished()
{
	//if (ui->m_lineChangeFinal->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineChangeFinal)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineChangeFinal->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_lineChangeFinal->setText(QString::number(fv,'f',3));
}

void QCurrInverAddMultDlg::on_m_lineChangeStep_editingFinished()
{
	//if (ui->m_lineChangeStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineChangeStep)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineChangeStep->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_lineChangeStep->setText(QString::number(fv,'f',3));

}

void QCurrInverAddMultDlg::on_m_cmbErrorLogic_currentIndexChanged(int index)
{

}

void QCurrInverAddMultDlg::on_m_lineRelErr_editingFinished()
{
	//if (ui->m_lineRelErr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineRelErr)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineRelErr->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_lineRelErr->setText(QString::number(fv, 'f', 3));
}

void QCurrInverAddMultDlg::on_m_linePlus_editingFinished()
{
	//if (ui->m_linePlus->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_linePlus)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_linePlus->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_linePlus->setText(QString::number(fv, 'f', 3));
}

void QCurrInverAddMultDlg::on_m_lineMinus_editingFinished()
{
	//if (ui->m_lineMinus->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_lineMinus)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	float fv = ui->m_lineMinus->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_lineMinus->setText(QString::number(fv, 'f', 3));
}

void QCurrInverAddMultDlg::slot_chb_faultTypeClicked()
{
	if (ui->chb_AN->isChecked()||ui->chb_BN->isChecked()||ui->chb_CN->isChecked()||
		ui->chb_AB->isChecked()||ui->chb_BC->isChecked()||ui->chb_CA->isChecked()||
		ui->chb_ABC->isChecked()||ui->chb_3I0->isChecked()||ui->chb_I2->isChecked()||
		ui->chb_IaIbIc->isChecked()||ui->chb_A->isChecked()||ui->chb_B->isChecked()||ui->chb_C->isChecked())
	{
		ui->pbn_Ok->setDisabled(false);
	}
	else
	{
		ui->pbn_Ok->setDisabled(true);
	}
}

void QCurrInverAddMultDlg::on_pbn_Ok_clicked()
{
	GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
    this->done(Accepted);
}

void QCurrInverAddMultDlg::on_pbn_Cancel_clicked()
{
    this->close();
}

//void QCurrInverAddMultDlg::slot_ResultEstimateClick()
//{
//	POS pos = m_pDataGroup->GetHeadPosition();
//	while(pos!=NULL)
//	{
//		CDvmData *pData = (CDvmData*)m_pDataGroup->GetNext(pos);
//		GetPageToValue(pData);
//	}
//	//结果评估
//	QCurrInverResultEstimateDlg oResultDlg;
//	oResultDlg.SetDatas(m_pDataGroup);
//	if(oResultDlg.exec() == QDialog::Accepted)
//	{
//		oResultDlg.GetDatas(m_pDataGroup);
//	}
//}

//void QCurrInverAddMultDlg::slot_CommonValueClick()
//{
//	QCurrInverBinarysDlg dlg(&m_oDataGroup,this);
//	dlg.setWindowModality(Qt::WindowModal);
//#ifdef _USE_SoftKeyBoard_
//	QSoftKeyBoard::AttachObj(&dlg);
//	dlg.exec();
//	QSoftKeyBoard::ReAttachObj();
//#else
//	dlg.exec();
//#endif
//}