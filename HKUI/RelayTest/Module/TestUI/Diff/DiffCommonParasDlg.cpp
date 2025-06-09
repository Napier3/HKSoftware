#include "DiffCommonParasDlg.h"
#include "ui_DiffCommonParasDlg.h"
#include "../../XLangResource_Native.h"

#define isnan(x) ((x) != (x))     //2024.10.17 zhangyq

extern CFont *g_pSttGlobalFont;
extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QDiffCommonParasDlg::QDiffCommonParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDiffCommonParasDlg)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
    ui->setupUi(this);
	m_pParas = NULL;
    m_nModify = 0;
	m_fKph = 0;
	m_fKpm = 0;
	m_fKpl = 0;

	m_nInSel = 0;
	m_fIbase = 0;
	m_bMinAxis = 0;

	m_nConnectMode = 0;
	m_nPhase = 0;
	InitUI();
}

QDiffCommonParasDlg::~QDiffCommonParasDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}
void QDiffCommonParasDlg::InitUI()
{	//20340617 luozibing ���ҳ����ʾ����
    ui->m_cmbKPSetMode->addItems(QStringList()<</*"�Զ�����"*/g_sLangTxt_Diff_Autocalculation
                                 <</*"�ֶ�����"*/g_sLangTxt_Diff_Manualcalculation);
    ui->m_cmbWindH->addItems(QStringList() << "Y" <</*"��"*/g_sLangTxt_Diff_Variation << "Z");
	ui->m_cmbWindM->addItems(QStringList() << "Y" <</*"��"*/g_sLangTxt_Diff_Variation << "Z");
	ui->m_cmbWindL->addItems(QStringList() << "Y" <</*"��"*/g_sLangTxt_Diff_Variation << "Z");
	//ui->m_cmbPhCorrectMode->addItems(QStringList() <</*"Y��У��"*/"Y" + g_sLangTxt_Diff_sideAdjust
 //                                    <</*"����У��"*/g_sLangTxt_Diff_Variation + g_sLangTxt_Diff_sideAdjust
	//											   <</*"Z��У��"*/"Z" + g_sLangTxt_Diff_sideAdjust);
	ui->m_cmbPhCorrectMode->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("PhCorrectMode")));
	ui->m_cmbPhCorrectMode->setItemText(0, /*��У��*/g_sLangTxt_State_NoAdjust);
	ui->m_cmbPhCorrectMode->setItemText(1, /*����У��*/g_sLangTxt_State_Triangulationcorrection);
	ui->m_cmbPhCorrectMode->setItemText(2, /*Y��У��*/g_sLangTxt_State_YAdjust);
	ui->m_cmbPhCorrectMode->setItemText(3, /*Z��У��*/g_sLangTxt_Diff_ZAdjust);
												   
    ui->m_cmbAdoptWind->addItems(QStringList()<</*"��-��"*/g_sLangTxt_Diff_High + "-" + g_sLangTxt_Diff_Low
                                 <</*"��-��"*/g_sLangTxt_Diff_High + "-" + g_sLangTxt_Diff_Medium
                                 <</*"��-��"*/g_sLangTxt_Diff_Medium + "-" + g_sLangTxt_Diff_Low);
    ui->m_cmbTransGroupMode1->addItems(QStringList()<</*"12��"*/"12" + g_sLangTxt_State_Oclock
                                       <</*"1��"*/"1" + g_sLangTxt_State_Oclock
                                       <</*"2��"*/"2" + g_sLangTxt_State_Oclock
                                       <</*"3��"*/"3" + g_sLangTxt_State_Oclock
                                       <</*"4��"*/"4" + g_sLangTxt_State_Oclock
                                       <</*"5��"*/"5" + g_sLangTxt_State_Oclock
                                       <</*"6��"*/"6" + g_sLangTxt_State_Oclock
                                       <</*"7��"*/"7" + g_sLangTxt_State_Oclock
                                       <</*"8��"*/"8" + g_sLangTxt_State_Oclock
                                       <</*"9��"*/"9" + g_sLangTxt_State_Oclock
                                       <</*"10��"*/"10" + g_sLangTxt_State_Oclock
                                       <</*"11��"*/"11" + g_sLangTxt_State_Oclock);
    ui->m_cmbTransGroupMode2->addItems(QStringList()<</*"12��"*/"12" + g_sLangTxt_State_Oclock
                                       <</*"1��"*/"1" + g_sLangTxt_State_Oclock
                                       <</*"2��"*/"2" + g_sLangTxt_State_Oclock
                                       <</*"3��"*/"3" + g_sLangTxt_State_Oclock
                                       <</*"4��"*/"4" + g_sLangTxt_State_Oclock
                                       <</*"5��"*/"5" + g_sLangTxt_State_Oclock
                                       <</*"6��"*/"6" + g_sLangTxt_State_Oclock
                                       <</*"7��"*/"7" + g_sLangTxt_State_Oclock
                                       <</*"8��"*/"8" + g_sLangTxt_State_Oclock
                                       <</*"9��"*/"9" + g_sLangTxt_State_Oclock
                                       <</*"10��"*/"10" + g_sLangTxt_State_Oclock
                                       <</*"11��"*/"11" + g_sLangTxt_State_Oclock);
    ui->m_cmbJXFactor->addItems(QStringList()<</*"���������������ʽ"*/g_sLangTxt_State_NotconWindconnection
                                <</*"�������������ʽ"*/g_sLangTxt_State_Winding);
    ui->m_cmbSearchMode->addItems(QStringList()<</*"���ַ�"*/g_sLangTxt_Diff_Dichotomy
                                  <</*"�����ƽ���"*/g_sLangTxt_Diff_StepwiseApproach);
    ui->m_cmbCTPoint->addItems(QStringList()<</*"����ָ���ѹ��"*/g_sLangTxt_State_Trans2
                               <</*"һ��ָ���ѹ��"*/g_sLangTxt_State_Trans1);
    ui->m_cmbIrEquation->addItems(QStringList()<</*"Ir=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1"*/g_sLangTxt_Diff_Bequation1
                                  <<"Ir=(|I1|+|I2|*K2)/K1"<<"Ir=max(|I1|,|I2|)"
                                  <<"Ir=(|Id-|I1|-|I2||)/K1"
                                  <</*"Ir=|I2|"<<"Ir=��(K1*I1*I2*Cos(��))"*/g_sLangTxt_Diff_Bequation5);
 //   ui->m_cmbCombinedFeature->addItems(QStringList()<</*"��"*/g_sLangTxt_State_Yes
 //                                      <</*"��"*/g_sLangTxt_State_No);
	//ui->m_cmbZeroSeqElimiType->addItems(QStringList() <</*"��"*/g_sLangTxt_without
	//												  <</*"�ߵ���-�������"*/g_sLangTxt_Diff_LineCur + "-" + g_sLangTxt_PowerDir_FaultPhase_ZeroCur);

	ui->m_cmbEarthing->addItems(QStringList() <</*"��"*/g_sLangTxt_State_Yes <</*"��"*/g_sLangTxt_State_No);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);

	ui->m_labPrepareTime->setText(/*׼��ʱ��(s)*/g_sLangTxt_Diff_PrepareTime);
	if (!ui->m_labPrepareTime->text().contains(":"))
	{
		ui->m_labPrepareTime->setText(ui->m_labPrepareTime->text() + ":");
	}
	ui->m_labPreFaultTime->setText(/*����ǰʱ��(s)*/g_sLangTxt_Native_PreFaultTime);
	if (!ui->m_labPreFaultTime->text().contains(":"))
	{
		ui->m_labPreFaultTime->setText(ui->m_labPreFaultTime->text() + ":");
	}
	ui->m_labFaultTime->setText(/*��������ʱ��(s)*/g_sLangTxt_Adjustment_Time);
	if (!ui->m_labFaultTime->text().contains(":"))
	{
		ui->m_labFaultTime->setText(ui->m_labFaultTime->text() + ":");
	}
	ui->m_labTimeAfter->setText(/*�����󱣳�ʱ��(s)*/g_sLangTxt_Diff_TimeAfter);
	if (!ui->m_labTimeAfter->text().contains(":"))
	{
		ui->m_labTimeAfter->setText(ui->m_labTimeAfter->text() + ":");
	}
	ui->m_labKPSetMode->setText(/*����ƽ��ϵ��*/g_sLangTxt_Diff_KPSetMode);
	if (!ui->m_labKPSetMode->text().contains(":"))
	{
		ui->m_labKPSetMode->setText(ui->m_labKPSetMode->text() + ":");
	}
	ui->m_labSn->setText(/*��ѹ�������*/g_sLangTxt_Native_TransfRatedCapacity);
	if (!ui->m_labSn->text().contains("(MVA)"))
	{
		ui->m_labSn->setText(ui->m_labSn->text() + "(MVA)");
	}
	if (!ui->m_labSn->text().contains(":"))
	{
		ui->m_labSn->setText(ui->m_labSn->text() + ":");
	}
	ui->m_labHUn->setText(/*��ѹ����ѹ*/g_sLangTxt_Native_HighVoltSideRatedVolt);
	if (!ui->m_labHUn->text().contains("(kV)"))
	{
		ui->m_labHUn->setText(ui->m_labHUn->text() + "(kV)");
	}
	if (!ui->m_labHUn->text().contains(":"))
	{
		ui->m_labHUn->setText(ui->m_labHUn->text() + ":");
	}
	ui->m_labMUn->setText(/*��ѹ����ѹ*/g_sLangTxt_Native_MedVoltSideRatedVolt);
	if (!ui->m_labMUn->text().contains("(kV)"))
	{
		ui->m_labMUn->setText(ui->m_labMUn->text() + "(kV)");
	}
	if (!ui->m_labMUn->text().contains(":"))
	{
		ui->m_labMUn->setText(ui->m_labMUn->text() + ":");
	}
	ui->m_labLUn->setText(/*��ѹ����ѹ*/g_sLangTxt_Native_LowVoltSideRatedVolt);
	if (!ui->m_labLUn->text().contains("(kV)"))
	{
		ui->m_labLUn->setText(ui->m_labLUn->text() + "(kV)");
	}
	if (!ui->m_labLUn->text().contains(":"))
	{
		ui->m_labLUn->setText(ui->m_labLUn->text() + ":");
	}

	ui->m_labCTPh->setText(/*��ѹ��CTһ��ֵ*/g_sLangTxt_Native_HVSideCTPrimVal);
	if (!ui->m_labCTPh->text().contains("(A)"))
	{
		ui->m_labCTPh->setText(ui->m_labCTPh->text() + "(A)");
	}
	if (!ui->m_labCTPh->text().contains(":"))
	{
		ui->m_labCTPh->setText(ui->m_labCTPh->text() + ":");
	}
	ui->m_labCTPm->setText(/*��ѹ��CTһ��ֵ*/g_sLangTxt_Native_MVSideCTPrimVal);
	if (!ui->m_labCTPm->text().contains("(A)"))
	{
		ui->m_labCTPm->setText(ui->m_labCTPm->text() + "(A)");
	}
	if (!ui->m_labCTPm->text().contains(":"))
	{
		ui->m_labCTPm->setText(ui->m_labCTPm->text() + ":");
	}
	ui->m_labCTPl->setText(/*��ѹ��CTһ��ֵ*/g_sLangTxt_Native_LVSideCTPrimVal);
	if (!ui->m_labCTPl->text().contains("(A)"))
	{
		ui->m_labCTPl->setText(ui->m_labCTPl->text() + "(A)");
	}
	if (!ui->m_labCTPl->text().contains(":"))
	{
		ui->m_labCTPl->setText(ui->m_labCTPl->text() + ":");
	}

	ui->m_labCTSh->setText(/*��ѹ��CT����ֵ*/g_sLangTxt_Native_HVSide2CTPrimVal);
	if (!ui->m_labCTSh->text().contains("(A)"))
	{
		ui->m_labCTSh->setText(ui->m_labCTSh->text() + "(A)");
	}
	if (!ui->m_labCTSh->text().contains(":"))
	{
		ui->m_labCTSh->setText(ui->m_labCTSh->text() + ":");
	}

	ui->m_labCTSm->setText(/*��ѹ��CT����ֵ*/g_sLangTxt_Native_MVSide2CTPrimVal);
	if (!ui->m_labCTSm->text().contains("(A)"))
	{
		ui->m_labCTSm->setText(ui->m_labCTSm->text() + "(A)");
	}
	if (!ui->m_labCTSm->text().contains(":"))
	{
		ui->m_labCTSm->setText(ui->m_labCTSm->text() + ":");
	}

	ui->m_labCTSl->setText(/*��ѹ��CT����ֵ*/g_sLangTxt_Native_LVSideCTPrimVal);
	if (!ui->m_labCTSl->text().contains("(A)"))
	{
		ui->m_labCTSl->setText(ui->m_labCTSl->text() + "(A)");
	}
	if (!ui->m_labCTSl->text().contains(":"))
	{
		ui->m_labCTSl->setText(ui->m_labCTSl->text() + ":");
	}
	ui->m_labKphSet->setText(/*��ѹ��ƽ��ϵ��*/g_sLangTxt_Diff_KphSet);
	if (!ui->m_labKphSet->text().contains(":"))
	{
		ui->m_labKphSet->setText(ui->m_labKphSet->text() + ":");
	}
	ui->m_labKpmSet->setText(/*��ѹ��ƽ��ϵ��*/g_sLangTxt_Diff_KpmSet);
	if (!ui->m_labKpmSet->text().contains(":"))
	{
		ui->m_labKpmSet->setText(ui->m_labKpmSet->text() + ":");
	}
	ui->m_labKplSet->setText(/*��ѹ��ƽ��ϵ��*/g_sLangTxt_Diff_KplSet);
	if (!ui->m_labKplSet->text().contains(":"))
	{
		ui->m_labKplSet->setText(ui->m_labKplSet->text() + ":");
	}

	ui->m_labWindH->setText(/*��ѹ�����������ʽ*/g_sLangTxt_Native_HighVoltWindingConnType);
	if (!ui->m_labWindH->text().contains(":"))
	{
		ui->m_labWindH->setText(ui->m_labWindH->text() + ":");
	}
	ui->m_labWindM->setText(/*��ѹ�����������ʽ*/g_sLangTxt_Native_MedVoltWindingConnType);
	if (!ui->m_labWindM->text().contains(":"))
	{
		ui->m_labWindM->setText(ui->m_labWindM->text() + ":");
	}
	ui->m_labWindL->setText(/*��ѹ�����������ʽ*/g_sLangTxt_Native_LowVoltWindingConnType);
	if (!ui->m_labWindL->text().contains(":"))
	{
		ui->m_labWindL->setText(ui->m_labWindL->text() + ":");
	}

	ui->m_labPhCorrectMode->setText(/*У��ѡ��*/g_sLangTxt_Diff_PhCorrectMode);
	if (!ui->m_labPhCorrectMode->text().contains(":"))
	{
		ui->m_labPhCorrectMode->setText(ui->m_labPhCorrectMode->text() + ":");
	}

	ui->m_labAdoptWind->setText(/*��������*/g_sLangTxt_Diff_AdoptWind);
	if (!ui->m_labAdoptWind->text().contains(":"))
	{
		ui->m_labAdoptWind->setText(ui->m_labAdoptWind->text() + ":");
	}

	ui->m_labTransGroupMode1->setText(/*��-�������ӵ���*/g_sLangTxt_Diff_TransGroupModeHM);
	if (!ui->m_labTransGroupMode1->text().contains(":"))
	{
		ui->m_labTransGroupMode1->setText(ui->m_labTransGroupMode1->text() + ":");
	}

	ui->m_labTransGroupMode2->setText(/*��-�������ӵ���*/g_sLangTxt_Diff_TransGroupModeHL);
	if (!ui->m_labTransGroupMode2->text().contains(":"))
	{
		ui->m_labTransGroupMode2->setText(ui->m_labTransGroupMode2->text() + ":");
	}

	ui->m_labJXFactor->setText(/*ƽ��ϵ������*/g_sLangTxt_Diff_JXFactor);
	if (!ui->m_labJXFactor->text().contains(":"))
	{
		ui->m_labJXFactor->setText(ui->m_labJXFactor->text() + ":");
	}

	ui->m_labSearchMode->setText(/*��������*/g_sLangTxt_Native_SearchMeth);
	if (!ui->m_labSearchMode->text().contains(":"))
	{
		ui->m_labSearchMode->setText(ui->m_labSearchMode->text() + ":");
	}

	ui->m_labCTPoint->setText(/*��������*/g_sLangTxt_State_CTpolarity);
	if (!ui->m_labCTPoint->text().contains(":"))
	{
		ui->m_labCTPoint->setText(ui->m_labCTPoint->text() + ":");
	}

	ui->m_labIrEquation->setText(/*�ƶ�����*/g_sLangTxt_State_Bequation);
	if (!ui->m_labIrEquation->text().contains(":"))
	{
		ui->m_labIrEquation->setText(ui->m_labIrEquation->text() + ":");
	}

	ui->m_labEarthing->setText(/*�ӵ�*/g_sLangTxt_Diff_Earthing);
	if (!ui->m_labEarthing->text().contains(":"))
	{
		ui->m_labEarthing->setText(ui->m_labEarthing->text() + ":");
	}

	ui->m_labStep->setText(/*���Ծ���*/g_sLangTxt_Native_TestPrecision);
	if (!ui->m_labStep->text().contains(":"))
	{
		ui->m_labStep->setText(ui->m_labStep->text() + ":");
	}
	ui->m_btnOK->setText(/*ȷ��*/g_sLangTxt_OK);
	ui->m_btnCancel->setText(/*ȡ��*/g_sLangTxt_Cancel);
	setWindowTitle(g_sLangTxt_Diff_CommonPara);
}
void QDiffCommonParasDlg::SetDatas(CExBaseList *pParas)
{
	//20240617 luozibing ��ȡ����ת����������
	if(pParas == NULL)
		return;
	m_pParas = pParas;
	CheckAllPresence(m_pParas);
    m_nModify = 0;
	DisConnectAutoCalcKpx_SigSlot();
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
	ConnectAutoCalcKpx_SigSlot();
	AutoCalcKpx();
}
void QDiffCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PREPARETIME)
	{
		ui->m_txtPrepareTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));       //׼��ʱ��(s)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PREFAULTTIME)
	{
		ui->m_txtPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));		//����ǰʱ��(s)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SETTINGTIME)
	{
		ui->m_txtFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));		//��������ʱ��(s)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIMEAFTER)
	{
		//ui->m_txtTimeAfter->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));         //���������ʱ��(s)
		ui->m_txtTimeAfter->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE)
	{
		ui->m_cmbKPSetMode->setCurrentIndex(pData->m_strValue.toInt());						//����ƽ��ϵ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SN)
	{
		//ui->m_txtSn->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ�������(MVA)
		ui->m_txtSn->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HUN)
	{ 					
		//ui->m_txtHUn->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ����ѹ(kV)
		ui->m_txtHUn->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_MUN)
	{ 					
		//ui->m_txtMUn->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ����ѹ(kV)
		ui->m_txtMUn->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_LUN)
	{ 					
		//ui->m_txtLUn->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ����ѹ(kV)
		ui->m_txtLUn->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH)
	{ 					
		//ui->m_txtCTPh->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ��CTһ��ֵ(A)
		ui->m_txtCTPh->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM)
	{ 					
		//ui->m_txtCTPm->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ��CTһ��ֵ(A)
		ui->m_txtCTPm->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL)
	{ 					
		//ui->m_txtCTPl->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ��CTһ��ֵ(A)
		ui->m_txtCTPl->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH)
	{ 					
		//ui->m_txtCTSh->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ��CT����ֵ(A)
		ui->m_txtCTSh->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM)
	{ 					
		//ui->m_txtCTSm->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ��CT����ֵ(A)
		ui->m_txtCTSm->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL)
	{ 					
		//ui->m_txtCTSl->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//��ѹ��CT����ֵ(A)
		ui->m_txtCTSl->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET)
	{ 				
		//ui->m_txtKphSet->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));			//��ѹ��ƽ��ϵ��
		ui->m_txtKphSet->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET)
	{
		//ui->m_txtKpmSet->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));			//��ѹ��ƽ��ϵ��
		ui->m_txtKpmSet->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET)
	{ 				
		//ui->m_txtKplSet->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));			//��ѹ��ƽ��ϵ��
		ui->m_txtKplSet->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH)
	{ 					
		ui->m_cmbWindH->setCurrentIndex(pData->m_strValue.toInt());				//��ѹ�����������ʽ
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM)
	{ 					
		ui->m_cmbWindM->setCurrentIndex(pData->m_strValue.toInt());				//��ѹ�����������ʽ
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL)
	{ 					
		ui->m_cmbWindL->setCurrentIndex(pData->m_strValue.toInt());				//��ѹ�����������ʽ
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE)
	{ 			
		ui->m_cmbPhCorrectMode->SetSelByIndex(pData->m_strValue.toInt());		//У��ѡ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND)
	{ 				
		ui->m_cmbAdoptWind->setCurrentIndex(pData->m_strValue.toInt());			//��������
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE1)
	{ 		
		ui->m_cmbTransGroupMode1->setCurrentIndex(pData->m_strValue.toInt());	//��-�������ӵ���
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE2)
	{ 		
		ui->m_cmbTransGroupMode2->setCurrentIndex(pData->m_strValue.toInt());	//��-�������ӵ���
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR)
	{ 				
		ui->m_cmbJXFactor->setCurrentIndex(pData->m_strValue.toInt());			//ƽ��ϵ������
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE)
	{ 			
		ui->m_cmbSearchMode->setCurrentIndex(pData->m_strValue.toInt());		//��������
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT)
	{ 				
		ui->m_cmbCTPoint->setCurrentIndex(pData->m_strValue.toInt());			//CT����
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION)
	{ 			
		ui->m_cmbIrEquation->setCurrentIndex(pData->m_strValue.toInt());		//�ƶ�����
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K)
	{ 						
		ui->m_txtK->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));	//K1
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K2)
	{ 					
		ui->m_txtK2->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));	//K2
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE)
	//{ 		
	//	ui->m_cmbCombinedFeature->setCurrentIndex(pData->m_strValue.toInt());	//�������
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE)
	//{
	//	ui->m_cmbZeroSeqElimiType->setCurrentIndex(pData->m_strValue.toInt());	//�������
	//}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING)
	{ 				
		ui->m_cmbEarthing->setCurrentIndex(pData->m_strValue.toInt());			//�ӵ�
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_STEP)
	{ 					
		ui->m_txtStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));				//���Ծ���
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_VG1)
	{ 					
		ui->m_txtVg1->setText(CheckDataMinMax(pData->m_strValue,120,0,3));				//Ua��Ub��Uc(V)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_VG2)
	{ 					
		ui->m_txtVg2->setText(CheckDataMinMax(pData->m_strValue,120,0,3));				//Ua2��Ub2��Uc2(V)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE)
	{
		m_nPhase = CheckDataMinMax(pData->m_strValue, 120, 0, 3).toInt();				//�������
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_INSEL)
	{
		m_nInSel = pData->m_strValue.toInt();         //��׼����ѡ��
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_INSET)
	{ 
		m_fIbase = pData->m_strValue.toFloat();				//��׼�����趨ֵ
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_MINAXIS)
	{ 
		m_bMinAxis = pData->m_strValue.toInt();			//��ֵ������ʽ 
	}
}
void QDiffCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	//20240617 luozibing ���������ò��������
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QDiffCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{

	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PREPARETIME)
	{
		pData->m_strValue = ui->m_txtPrepareTime->text();       //׼��ʱ��(s)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_txtPreFaultTime->text();		//����ǰʱ��(s)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SETTINGTIME)
	{
		pData->m_strValue = ui->m_txtFaultTime->text();		//��������ʱ��(s)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIMEAFTER)
	{
		pData->m_strValue = ui->m_txtTimeAfter->GetText();         //���������ʱ��(s)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbKPSetMode->currentIndex());						//����ƽ��ϵ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SN)
	{
		pData->m_strValue = ui->m_txtSn->GetText();				//��ѹ�������(MVA)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HUN)
	{ 					
		pData->m_strValue = ui->m_txtHUn->GetText();				//��ѹ����ѹ(kV)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_MUN)
	{ 					
		pData->m_strValue = ui->m_txtMUn->GetText();				//��ѹ����ѹ(kV)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_LUN)
	{ 					
		pData->m_strValue = ui->m_txtLUn->GetText();				//��ѹ����ѹ(kV)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH)
	{ 					
		pData->m_strValue = ui->m_txtCTPh->GetText();				//��ѹ��CTһ��ֵ(A)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM)
	{ 					
		pData->m_strValue = ui->m_txtCTPm->GetText();				//��ѹ��CTһ��ֵ(A)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL)
	{ 					
		pData->m_strValue = ui->m_txtCTPl->GetText();				//��ѹ��CTһ��ֵ(A)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH)
	{ 					
		pData->m_strValue = ui->m_txtCTSh->GetText();				//��ѹ��CT����ֵ(A)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM)
	{ 					
		pData->m_strValue = ui->m_txtCTSm->GetText();				//��ѹ��CT����ֵ(A)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL)
	{ 					
		pData->m_strValue = ui->m_txtCTSl->GetText();				//��ѹ��CT����ֵ(A)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET)
	{ 				
		pData->m_strValue = ui->m_txtKphSet->GetText();			//��ѹ��ƽ��ϵ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET)
	{
		pData->m_strValue = ui->m_txtKpmSet->GetText();			//��ѹ��ƽ��ϵ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET)
	{ 				
		pData->m_strValue = ui->m_txtKplSet->GetText();			//��ѹ��ƽ��ϵ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH)
	{ 					
		pData->m_strValue.Format("%d",ui->m_cmbWindH->currentIndex());				//��ѹ�����������ʽ
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM)
	{ 					
		pData->m_strValue.Format("%d",ui->m_cmbWindM->currentIndex());				//��ѹ�����������ʽ
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL)
	{ 					
		pData->m_strValue.Format("%d",ui->m_cmbWindL->currentIndex());				//��ѹ�����������ʽ
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE)
	{ 			
		pData->m_strValue.Format("%d", ui->m_cmbPhCorrectMode->GetSelectIndex2());		//У��ѡ��
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND)
	{ 				
		pData->m_strValue.Format("%d",ui->m_cmbAdoptWind->currentIndex());			//��������
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE1)
	{ 		
		pData->m_strValue.Format("%d",ui->m_cmbTransGroupMode1->currentIndex());	//��-�������ӵ���
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE2)
	{ 		
		pData->m_strValue.Format("%d",ui->m_cmbTransGroupMode2->currentIndex());	//��-�������ӵ���
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE)//���ݲ������� + ��-�� + ��-�ͼ����������֮��ǲ�(�ӵ���)
	{ 		
		m_nConnectMode = 0;
		switch (ui->m_cmbAdoptWind->currentIndex())
		{
		case 0://0-��-��
			m_nConnectMode = ui->m_cmbTransGroupMode2->currentIndex();
			break;
		case 1://1-��-��
			m_nConnectMode = ui->m_cmbTransGroupMode1->currentIndex();
			break;
		case 2://2-��-��
			m_nConnectMode = ui->m_cmbTransGroupMode1->currentIndex() - ui->m_cmbTransGroupMode2->currentIndex();
			if (m_nConnectMode <= 0)
			{
				m_nConnectMode += 12;
			}
			break;
		}
		pData->m_strValue.Format("%d", m_nConnectMode);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR)
	{ 				
		pData->m_strValue.Format("%d",ui->m_cmbJXFactor->currentIndex());			//ƽ��ϵ������
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE)
	{ 			
		pData->m_strValue.Format("%d",ui->m_cmbSearchMode->currentIndex());		//��������
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT)
	{ 				
		pData->m_strValue.Format("%d",ui->m_cmbCTPoint->currentIndex());			//CT����
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION)
	{ 			
		pData->m_strValue.Format("%d",ui->m_cmbIrEquation->currentIndex());		//�ƶ�����
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K)
	{ 						
		pData->m_strValue = ui->m_txtK->text();	//K1
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K2)
	{ 					
		pData->m_strValue = ui->m_txtK2->text();	//K2
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE)
	//{ 		
	//	pData->m_strValue.Format("%d",ui->m_cmbCombinedFeature->currentIndex());	//�������
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE)
	//{
	//	pData->m_strValue.Format("%d", ui->m_cmbCombinedFeature->currentIndex());	//����������ʽ
	//}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING)
	{ 				
		pData->m_strValue.Format("%d",ui->m_cmbEarthing->currentIndex());			//�ӵ�
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_STEP)
	{ 					
		pData->m_strValue = ui->m_txtStep->text();				//���Ծ���
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_VG1)
	{ 					
		pData->m_strValue = ui->m_txtVg1->text();				//Ua��Ub��Uc(V)
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_VG2)
	{ 					
		pData->m_strValue = ui->m_txtVg2->text();				//Ua2��Ub2��Uc2(V)
	}
}

void QDiffCommonParasDlg::on_m_txtPrepareTime_editingFinished()
{
	ui->m_txtPrepareTime->setText(CheckDataMinMax(ui->m_txtPrepareTime->text(),999.999,0,3));       //׼��ʱ��(s)
}
void QDiffCommonParasDlg::on_m_txtPreFaultTime_editingFinished()
{
	ui->m_txtPreFaultTime->setText(CheckDataMinMax(ui->m_txtPreFaultTime->text(),999.999,0,3));		//����ǰʱ��(s)
}
void QDiffCommonParasDlg::on_m_txtFaultTime_editingFinished()
{
	ui->m_txtFaultTime->setText(CheckDataMinMax(ui->m_txtFaultTime->text(),999.999,0,3));		//����ʱ��ԣ��(s)
}
void QDiffCommonParasDlg::on_m_txtTimeAfter_editingFinished()
{
	if (ui->m_txtTimeAfter->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtTimeAfter)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtTimeAfter->setText(CheckDataMinMax(ui->m_txtTimeAfter->text(),999.999,0,3));         //���������ʱ��(s)
}
void QDiffCommonParasDlg::on_m_cmbKPSetMode_currentIndexChanged(int index)
{
	ui->m_txtSn->setEnabled(!index);
	ui->m_txtHUn->setEnabled(!index);
	ui->m_txtMUn->setEnabled(!index);
	ui->m_txtLUn->setEnabled(!index);
	ui->m_txtHUn->setEnabled(!index);
	ui->m_txtMUn->setEnabled(!index);
	ui->m_txtLUn->setEnabled(!index);
	ui->m_txtCTPh->setEnabled(!index);
	ui->m_txtCTPm->setEnabled(!index);
	ui->m_txtCTPl->setEnabled(!index);
	ui->m_txtCTSh->setEnabled(!index);
	ui->m_txtCTSm->setEnabled(!index);
	ui->m_txtCTSl->setEnabled(!index);

	ui->m_txtKphSet->setEnabled(index);
	ui->m_txtKpmSet->setEnabled(index);
	ui->m_txtKplSet->setEnabled(index);
	//ui->m_cmbKPSetMode->setCurrentIndex(ui->m_strValue.toInt());						//����ƽ��ϵ��
}
void QDiffCommonParasDlg::slot_m_txtSn_editingFinished()
{
	if (ui->m_txtSn->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtSn)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtSn->setText(CheckDataMinMax(ui->m_txtSn->text(),999999,0,3));				//��ѹ�������(MVA)	
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtHUn_editingFinished()
{
	if (ui->m_txtHUn->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtHUn)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtHUn->setText(CheckDataMinMax(ui->m_txtHUn->text(),999999,0,3));				//��ѹ����ѹ(kV)	
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtMUn_editingFinished()
{
	if (ui->m_txtMUn->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtMUn)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtMUn->setText(CheckDataMinMax(ui->m_txtMUn->text(),999999,0,3));				//��ѹ����ѹ(kV)
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtLUn_editingFinished()
{
	if (ui->m_txtLUn->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtLUn)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtLUn->setText(CheckDataMinMax(ui->m_txtLUn->text(),999999,0,3));				//��ѹ����ѹ(kV)
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtCTPh_editingFinished()
{
	if (ui->m_txtCTPh->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtCTPh)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtCTPh->setText(CheckDataMinMax(ui->m_txtCTPh->text(),999999,0,3));				//��ѹ��CTһ��ֵ(A)		
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtCTPm_editingFinished()
{
	if (ui->m_txtCTPm->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtCTPm)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtCTPm->setText(CheckDataMinMax(ui->m_txtCTPm->text(),999999,0,3));				//��ѹ��CTһ��ֵ(A)	
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtCTPl_editingFinished()
{
	if (ui->m_txtCTPl->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtCTPl)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtCTPl->setText(CheckDataMinMax(ui->m_txtCTPl->text(),999999,0,3));				//��ѹ��CTһ��ֵ(A) 
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtCTSh_editingFinished()
{
	if (ui->m_txtCTSh->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtCTSh)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtCTSh->setText(CheckDataMinMax(ui->m_txtCTSh->text(),999999,0,3));				//��ѹ��CT����ֵ(A)
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtCTSm_editingFinished()
{
	if (ui->m_txtCTSm->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtCTSm)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtCTSm->setText(CheckDataMinMax(ui->m_txtCTSm->text(),999999,0,3));//��ѹ��CT����ֵ(A)	
	AutoCalcKpx();
}
void QDiffCommonParasDlg::slot_m_txtCTSl_editingFinished()
{
	if (ui->m_txtCTSl->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtCTSl)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtCTSl->setText(CheckDataMinMax(ui->m_txtCTSl->text(),999999,0,3));				//��ѹ��CT����ֵ(A)	
	AutoCalcKpx();
}
void QDiffCommonParasDlg::on_m_txtKphSet_editingFinished()
{
	if (ui->m_txtKphSet->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtKphSet)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtKphSet->setText(CheckDataMinMax(ui->m_txtKphSet->text(),999.999,0,3));			//��ѹ��ƽ��ϵ��
}
void QDiffCommonParasDlg::on_m_txtKpmSet_editingFinished()
{
	if (ui->m_txtKpmSet->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtKpmSet)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtKpmSet->setText(CheckDataMinMax(ui->m_txtKpmSet->text(),999.999,0,3));			//��ѹ��ƽ��ϵ��				
}
void QDiffCommonParasDlg::on_m_txtKplSet_editingFinished()
{
	if (ui->m_txtKplSet->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtKplSet)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtKplSet->setText(CheckDataMinMax(ui->m_txtKplSet->text(),999.999,0,3));			//��ѹ��ƽ��ϵ��				
}
void QDiffCommonParasDlg::slot_m_cmbWindH_currentIndexChanged(int index)
{
	AutoCalcKpx();
	//ui->m_cmbWindH->setCurrentIndex(ui->m_strValue.toInt());				//��ѹ�����������ʽ					
}
void QDiffCommonParasDlg::slot_m_cmbWindM_currentIndexChanged(int index)
{
	//ui->m_cmbWindM->setCurrentIndex(ui->m_strValue.toInt());				//��ѹ�����������ʽ						
}
void QDiffCommonParasDlg::slot_m_cmbWindL_currentIndexChanged(int index)
{
	AutoCalcKpx();
	//ui->m_cmbWindL->setCurrentIndex(ui->m_strValue.toInt());				//��ѹ�����������ʽ
}
void QDiffCommonParasDlg::slot_m_cmbPhCorrectMode_currentIndexChanged(int index)
{
	AutoCalcKpx();
	//ui->m_cmbPhCorrectMode->setCurrentIndex(ui->m_strValue.toInt());		//У��ѡ��				
}
void QDiffCommonParasDlg::slot_m_cmbAdoptWind_currentIndexChanged(int index)
{
	AutoCalcKpx();
	//ui->m_cmbAdoptWind->setCurrentIndex(ui->m_strValue.toInt());			//��������	
}
void QDiffCommonParasDlg::on_m_cmbTransGroupMode1_currentIndexChanged(int index)
{
	//ui->m_cmbTransGroupMode1->setCurrentIndex(ui->m_strValue.toInt());	//��-�������ӵ���		
}
void QDiffCommonParasDlg::on_m_cmbTransGroupMode2_currentIndexChanged(int index)
{
	//ui->m_cmbTransGroupMode2->setCurrentIndex(ui->m_strValue.toInt());	//��-�������ӵ���				
}
void QDiffCommonParasDlg::slot_m_cmbJXFactor_currentIndexChanged(int index)
{
	AutoCalcKpx();
	//ui->m_cmbJXFactor->setCurrentIndex(ui->m_strValue.toInt());			//ƽ��ϵ������			
}
void QDiffCommonParasDlg::on_m_cmbSearchMode_currentIndexChanged(int index)
{
	//ui->m_cmbSearchMode->setCurrentIndex(ui->m_strValue.toInt());		//��������				
}
void QDiffCommonParasDlg::on_m_cmbCTPoint_currentIndexChanged(int index)
{
	//ui->m_cmbCTPoint->setCurrentIndex(ui->m_strValue.toInt());			//CT����			
}
void QDiffCommonParasDlg::on_m_cmbIrEquation_currentIndexChanged(int index)
{
	//ui->m_cmbIrEquation->setCurrentIndex(ui->m_strValue.toInt());		//�ƶ�����					
}
void QDiffCommonParasDlg::on_m_txtK_editingFinished()
{
	ui->m_txtK->setText(CheckDataMinMax(ui->m_txtK->text(),999.999,0,3));	//K1				
}
void QDiffCommonParasDlg::on_m_txtK2_editingFinished()
{
	ui->m_txtK2->setText(CheckDataMinMax(ui->m_txtK2->text(),999.999,0,3));	//K2	
}
//void QDiffCommonParasDlg::on_m_cmbCombinedFeature_currentIndexChanged(int index)
//{
//	//ui->m_cmbCombinedFeature->setCurrentIndex(ui->m_strValue.toInt());	//�������				
//}
void QDiffCommonParasDlg::on_m_cmbEarthing_currentIndexChanged(int index)
{
	//ui->m_cmbEarthing->setCurrentIndex(ui->m_strValue.toInt());			//�ӵ�					
}
void QDiffCommonParasDlg::on_m_txtStep_editingFinished()
{
	ui->m_txtStep->setText(CheckDataMinMax(ui->m_txtStep->text(),999.999,0,3));				//���Ծ���				
}
void QDiffCommonParasDlg::on_m_txtVg1_editingFinished()
{
	ui->m_txtVg1->setText(CheckDataMinMax(ui->m_txtVg1->text(),120,0,3));				//Ua��Ub��Uc(V)			
}
void QDiffCommonParasDlg::on_m_txtVg2_editingFinished()
{
	ui->m_txtVg2->setText(CheckDataMinMax(ui->m_txtVg2->text(),120,0,3));				//Ua2��Ub2��Uc2(V)
}
void QDiffCommonParasDlg::on_m_btnOK_clicked()
{
	this->done(Accepted); 
}

void QDiffCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}
void QDiffCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_PREPARETIME);       //׼��ʱ��(s)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_PREFAULTTIME);		//����ǰʱ��(s)
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFF_PARAS_ID_SETTINGTIME);			//��������ʱ��(s)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIMEAFTER);         //���������ʱ��(s)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE);			//����ƽ��ϵ��
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_SN);				//��ѹ�������(MVA)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HUN);				//��ѹ����ѹ(kV)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_MUN);				//��ѹ����ѹ(kV)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_LUN);				//��ѹ����ѹ(kV)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH);				//��ѹ��CTһ��ֵ(A)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM);				//��ѹ��CTһ��ֵ(A)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL);				//��ѹ��CTһ��ֵ(A)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH);				//��ѹ��CT����ֵ(A)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM);				//��ѹ��CT����ֵ(A)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL);				//��ѹ��CT����ֵ(A)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET);			//��ѹ��ƽ��ϵ��
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET);			//��ѹ��ƽ��ϵ��
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET);			//��ѹ��ƽ��ϵ��
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH);				//��ѹ�����������ʽ
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM);				//��ѹ�����������ʽ
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL);				//��ѹ�����������ʽ
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE);		//У��ѡ��
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND);			//��������
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE1);	//��-�������ӵ���
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE2);	//��-�������ӵ���
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE);	//��������֮��ǲ�(�ӵ���)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR);			//ƽ��ϵ������
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE);		//��������
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT);			//CT����
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION);		//�ƶ�����
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_K);					//K1
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_K2);				//K2
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE);	//�������
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE);	//����������ʽ
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING);			//�ӵ�
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_STEP);				//���Ծ���
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_VG1);				//Ua��Ub��Uc(V)
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_VG2);				//Ua2��Ub2��Uc2(V)
}
void QDiffCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
{//20240625 luozibing ͨ�ò����޸ĺ��޸ı��������������ͨ�ò���
	CSttMacroTest *pSttMacroTest = NULL;
	CExBaseList *pItem = NULL;
	CSttMacroTestParaDatas *pParaDatas = NULL;

	POS pos = pAllItems->GetHeadPosition();

	while (pos!= NULL)
	{
		pItem = (CExBaseList*)pAllItems->GetNext(pos);

		if(pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pSttMacroTest = (CSttMacroTest *)pItem;
			pSttMacroTest->m_nModified = 1;
			pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE,"");

			if(pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
}
BOOL QDiffCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
{
    if (pItem == NULL)
    {
        return FALSE;
    }
    CSttMacroTestParaDatas paraDatas;
    CheckAllPresence(&paraDatas);
    GetDatas(&paraDatas);
    POS pos = pItem->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pItem->GetNext(pos);
        CSttMacroTestParaData *pData_New = (CSttMacroTestParaData *)paraDatas.FindByID(pData->m_strID);
        if (pData_New == NULL)
        {
            continue;
        }
        if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE1
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE2
				|| pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE
				|| pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE
                || pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING)
        {
            if (pData->m_strValue != pData_New->m_strValue)
            {
                m_nModify = 1;
                return TRUE;
            }
        }
        else
        {//�������жϲ�ֵ�ľ���ֵ
            if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
            {
                m_nModify = 1;
                return TRUE;
            }
        }

    }
    return FALSE;
}

void QDiffCommonParasDlg::AutoCalcKpx()
{
	if (ui->m_cmbKPSetMode->currentIndex() == 0)//�Զ�����ƽ��ϵ��
	{
		float fValue = 0.000f;
		m_oDiffCalTool.Init();

		//if (g_oSystemParas.m_nHasAnalog)
		//{
		//	m_oDiffCalTool.InitSysParas(20, g_oSystemParas.m_fFNom);
		//}
		//else
		//{
		//	m_oDiffCalTool.InitSysParas(100, g_oSystemParas.m_fFNom);
		//}
		if (ui->m_cmbAdoptWind->currentIndex() == 0)
		{
			fValue = ui->m_txtKpmSet->GetText().toFloat();
		}
		else if (ui->m_cmbAdoptWind->currentIndex() == 1)
		{
			fValue = ui->m_txtKplSet->GetText().toFloat();
		}
		else if (ui->m_cmbAdoptWind->currentIndex() == 2)
		{
			fValue = ui->m_txtKphSet->GetText().toFloat();
		}

		m_oDiffCalTool.InitParas6I(m_nInSel,m_fIbase, ui->m_cmbSearchMode->currentIndex(),
			m_bMinAxis, ui->m_cmbPhCorrectMode->GetSelectIndex2(), ui->m_cmbIrEquation->currentIndex(),
			ui->m_cmbWindH->currentIndex(), ui->m_cmbWindM->currentIndex(), ui->m_cmbWindL->currentIndex(), ui->m_cmbAdoptWind->currentIndex(),
			ui->m_txtK->text().toFloat(), ui->m_txtK2->text().toFloat(), m_nConnectMode,
			m_nPhase, ui->m_cmbCTPoint->currentIndex(),ui->m_cmbJXFactor->currentIndex());


		m_oDiffCalTool.InitParas_AutoCalBalanceFactors(ui->m_txtSn->text().toFloat(), ui->m_txtHUn->text().toFloat(), ui->m_txtMUn->text().toFloat(),
			ui->m_txtLUn->text().toFloat(), ui->m_txtCTPh->text().toFloat(), ui->m_txtCTSh->text().toFloat(), ui->m_txtCTPm->text().toFloat(),
			ui->m_txtCTSm->text().toFloat(), ui->m_txtCTPl->text().toFloat(), ui->m_txtCTSl->text().toFloat());
		m_oDiffCalTool.GetKps(m_fKph, m_fKpm, m_fKpl);

		//��������	0-��-��  1-��-��    2-��-�� 
		//2023-11-18 suyang �ڸ� �У��е�ʱ������ֵ���ԣ����¸�ֵ 
		if (ui->m_cmbAdoptWind->currentIndex() == 0)
		{
			if (fValue != m_fKpm)
			{
				m_fKpm = fValue;
			}
		}

		else if (ui->m_cmbAdoptWind->currentIndex() == 1)
		{
			m_fKpm = m_fKpl;

			if (fValue != m_fKpl)
			{
				m_fKpl = fValue;
			}
		}
		else if (ui->m_cmbAdoptWind->currentIndex() == 2)
		{
			m_fKpm = m_fKph;

			if (m_fKph != fValue)
			{
				m_fKph = fValue;
			}
		}
		if (!isnan(m_fKph) && !isinf(m_fKph))//�ж��Ƿ�Ϊ��Ч����
		{
			ui->m_txtKphSet->setText(CheckDataMinMax(QString::number(m_fKph), 999.999, 0, 3));			//��ѹ��ƽ��ϵ��
		} 
		else
		{
			ui->m_txtKphSet->setText("0.000");
		}

		if (!isnan(m_fKpm) && !isinf(m_fKpm))//�ж��Ƿ�Ϊ��Ч����
		{
			ui->m_txtKphSet->setText(CheckDataMinMax(QString::number(m_fKpm), 999.999, 0, 3));			//��ѹ��ƽ��ϵ��
		}
		else
		{
			ui->m_txtKphSet->setText("0.000");
		}

		if (!isnan(m_fKpl) && !isinf(m_fKpl))//�ж��Ƿ�Ϊ��Ч����
		{
			ui->m_txtKphSet->setText(CheckDataMinMax(QString::number(m_fKpl), 999.999, 0, 3));			//��ѹ��ƽ��ϵ��
		}
		else
		{
			ui->m_txtKphSet->setText("0.000");
		}
	}
}
void QDiffCommonParasDlg::ConnectAutoCalcKpx_SigSlot()
{
	connect(ui->m_txtSn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtSn_editingFinished()));				//��ѹ�������(MVA)					
	connect(ui->m_txtHUn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtHUn_editingFinished()));				//��ѹ����ѹ(kV)					
	connect(ui->m_txtMUn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtMUn_editingFinished()));				//��ѹ����ѹ(kV)				
	connect(ui->m_txtLUn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtLUn_editingFinished()));				//��ѹ����ѹ(kV)					
	connect(ui->m_txtCTPh, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTPh_editingFinished()));				//��ѹ��CTһ��ֵ(A)					
	connect(ui->m_txtCTPm, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTPm_editingFinished()));				//��ѹ��CTһ��ֵ(A)					
	connect(ui->m_txtCTPl, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTPl_editingFinished()));				//��ѹ��CTһ��ֵ(A) 					
	connect(ui->m_txtCTSh, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTSh_editingFinished()));				//��ѹ��CT����ֵ(A)					
	connect(ui->m_txtCTSm, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTSm_editingFinished()));				//��ѹ��CT����ֵ(A)				
	connect(ui->m_txtCTSl, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTSl_editingFinished()));				//��ѹ��CT����ֵ(A)		

	connect(ui->m_cmbWindH, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbWindH_currentIndexChanged(int)));				//��ѹ�����������ʽ					
	connect(ui->m_cmbWindM, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbWindM_currentIndexChanged(int)));				//��ѹ�����������ʽ						
	connect(ui->m_cmbWindL, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbWindL_currentIndexChanged(int)));				//��ѹ�����������ʽ
	connect(ui->m_cmbPhCorrectMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbPhCorrectMode_currentIndexChanged(int)));		//У��ѡ��				
	connect(ui->m_cmbAdoptWind, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbAdoptWind_currentIndexChanged(int)));			//��������	
	connect(ui->m_cmbJXFactor, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbJXFactor_currentIndexChanged(int)));			//ƽ��ϵ������	
}
void QDiffCommonParasDlg::DisConnectAutoCalcKpx_SigSlot()
{
	disconnect(ui->m_txtSn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtSn_editingFinished()));				//��ѹ�������(MVA)					
	disconnect(ui->m_txtHUn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtHUn_editingFinished()));				//��ѹ����ѹ(kV)					
	disconnect(ui->m_txtMUn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtMUn_editingFinished()));				//��ѹ����ѹ(kV)				
	disconnect(ui->m_txtLUn, SIGNAL(editingFinished()), this, SLOT(slot_m_txtLUn_editingFinished()));				//��ѹ����ѹ(kV)					
	disconnect(ui->m_txtCTPh, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTPh_editingFinished()));				//��ѹ��CTһ��ֵ(A)					
	disconnect(ui->m_txtCTPm, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTPm_editingFinished()));				//��ѹ��CTһ��ֵ(A)					
	disconnect(ui->m_txtCTPl, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTPl_editingFinished()));				//��ѹ��CTһ��ֵ(A) 					
	disconnect(ui->m_txtCTSh, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTSh_editingFinished()));				//��ѹ��CT����ֵ(A)					
	disconnect(ui->m_txtCTSm, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTSm_editingFinished()));				//��ѹ��CT����ֵ(A)				
	disconnect(ui->m_txtCTSl, SIGNAL(editingFinished()), this, SLOT(slot_m_txtCTSl_editingFinished()));				//��ѹ��CT����ֵ(A)		

	disconnect(ui->m_cmbWindH, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbWindH_currentIndexChanged(int)));				//��ѹ�����������ʽ					
	disconnect(ui->m_cmbWindM, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbWindM_currentIndexChanged(int)));				//��ѹ�����������ʽ						
	disconnect(ui->m_cmbWindL, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbWindL_currentIndexChanged(int)));				//��ѹ�����������ʽ
	disconnect(ui->m_cmbPhCorrectMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbPhCorrectMode_currentIndexChanged(int)));		//У��ѡ��				
	disconnect(ui->m_cmbAdoptWind, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbAdoptWind_currentIndexChanged(int)));			//��������	
	disconnect(ui->m_cmbJXFactor, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cmbJXFactor_currentIndexChanged(int)));			//ƽ��ϵ������	
}

		