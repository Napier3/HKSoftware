#include "QPowerDirAddMultDlg.h"
#include "ui_QPowerDirAddMultDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SoftKeyboard/SoftKeyBoard.h"
//#include "PowerDirResultEstimateDlg.h"
#include "PowerDirCommonParasDlg.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "SttMultiMacroPowerDirParasDefine.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../XLangResource_Native.h"

QPowerDirAddMultDlg::QPowerDirAddMultDlg(QWidget *parent ):
	QDialog(parent),
	ui(new Ui::QPowerDirAddMultDlg)
{
	ui->setupUi(this);

    InitUI();
	initData();
	SetParasFont();
	initConnections();

    IsConnect = true;   //20240725 wanmj 默认90度接线 90度接线1 0度接线0

}

QPowerDirAddMultDlg::~QPowerDirAddMultDlg()
{
	delete ui;
}

void QPowerDirAddMultDlg::SetParasFont()
{
	ui->m_groupBox->setFont(*g_pSttGlobalFont);
	ui->m_groupBox_AngleParas->setFont(*g_pSttGlobalFont);
	ui->m_groupBox_FaultParas->setFont(*g_pSttGlobalFont);
	ui->m_groupBox_Results->setFont(*g_pSttGlobalFont);
	ui->m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	ui->m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
}


void QPowerDirAddMultDlg::OpenXmlFile()
{
	CString strPath = stt_ui_GetParasFile("PowerDirection_Paras.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pDataGroup->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QPowerDirAddMultDlg::SavePowerDirFile(CDataGroup *pParas)
{
	CString strPath = stt_ui_GetParasFile("PowerDirection_Paras_Debug.xml");
	pParas->SaveXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void QPowerDirAddMultDlg::SetDatas(/*CDataGroup *pParas*/CExBaseList *pParas)
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

	slot_chb_ATestClicked();
	slot_chb_BTestClicked();
	slot_chb_CTestClicked();
	slot_chb_ABTestClicked();
	slot_chb_BCTestClicked();
	slot_chb_CATestClicked();
	slot_chb_ZeroSeqTestClicked();
	slot_chb_NegativeSeqTestClicked();
}

void QPowerDirAddMultDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA)
	{
        //ui->m_pMaxSensitAngleEdit->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
        ui->m_pMaxSensitAngleEdit->UpdateObjectText(pData,CheckDataMinMax(pData->m_strValue,360,-360,2), 2);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE)
	{
		ui->m_pActRangeEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE)
	{
		ui->m_pStepEdit->setText(CheckDataMinMax(pData->m_strValue,360,0,1));
	}
    else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_FAULTVOL)
	{
		ui->m_pFaultVEdit->setText(CheckDataMinMax(pData->m_strValue,g_oLocalSysPara.m_fAC_VolMax,0,3));
	}
    else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_FAULTCUR)
	{
		ui->m_pFaultIEdit->setText(CheckDataMinMax(pData->m_strValue,g_oLocalSysPara.m_fAC_CurMax,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME)
	{
		ui->m_pFaultTimeEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANTest_CHECK)
	{
		ui->m_pATest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNTest_CHECK)
	{
		ui->m_pBTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNTest_CHECK)
	{
		ui->m_pCTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABTest_CHECK)
	{
		ui->m_pABTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCTest_CHECK)
	{
		ui->m_pBCTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CATest_CHECK)
	{
		ui->m_pCATest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZeroTest_CHECK)
	{
		ui->m_pZeroSeqTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegTest_CHECK)
	{
		ui->m_pNegativeSeqTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeA_CHECK)
	{
		ui->m_pAAN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeAB_CHECK)
	{
		ui->m_pAAB_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeCA_CHECK)
	{
		ui->m_pACA_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeABC_CHECK)
	{
		ui->m_pAABC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeB_CHECK)
	{
		ui->m_pBBN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeAB_CHECK)
	{
		ui->m_pBAB_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeBC_CHECK)
	{
		ui->m_pBBC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeABC_CHECK)
	{
		ui->m_pBABC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeC_CHECK)
	{
		ui->m_pCCN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeBC_CHECK)
	{
		ui->m_pCBC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeCA_CHECK)
	{
		ui->m_pCCA_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeABC_CHECK)
	{
		ui->m_pCABC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABFaultTypeAB_CHECK)
	{
		ui->m_pABAB_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCFaultTypeBC_CHECK)
	{
		ui->m_pBCBC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CAFaultTypeCA_CHECK)
	{
		ui->m_pCACA_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeZero_CHECK)
	{
		ui->m_pZeroSeq_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeA_CHECK)
	{
		ui->m_pZeroAN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeB_CHECK)
	{
		ui->m_pZeroBN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeC_CHECK)
	{
		ui->m_pZeroCN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeNegative_CHECK)
	{
		ui->m_pNegativeSeq_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeA_Check_CHECK)
	{
		ui->m_pNegativeAN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeB_CHECK)
	{
		ui->m_pNegativeBN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeC_CHECK)
	{
		ui->m_pNegativeCN_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeAB_CHECK)
	{
		ui->m_pNegativeAB_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeBC_CHECK)
	{
		ui->m_pNegativeBC_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeCA_CHECK)
	{
		ui->m_pNegativeCA_CheckBox->setChecked(pData->m_strValue == "1");
	}
    else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_ERRTYPE)    //20240806 wanmj
    {
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_ERRORTYPE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_pCmb_ErrorType->SetCurrSelByName(pValue->m_strName);
    }
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR)
	{
		ui->m_pAbsErrorEdit->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR)
	{
		ui->m_pRelErrorEdit->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, 3));
	}
}
void QPowerDirAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;

	/*QPowerDirResultEstimateDlg oResultDlg;
	oResultDlg.SetDatas(m_pDataGroup);
	oResultDlg.GetDatas(pParas);*/

	CheckAllPresence();

	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
	SavePowerDirFile(pParas);
}

void QPowerDirAddMultDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA)
	{
        //pData->m_strValue = ui->m_pMaxSensitAngleEdit->text();
        pData->m_strValue = ui->m_pMaxSensitAngleEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE)
	{
		pData->m_strValue = ui->m_pActRangeEdit->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE)
	{
		pData->m_strValue = ui->m_pStepEdit->text();
	}
    else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_FAULTVOL)
	{
		pData->m_strValue = ui->m_pFaultVEdit->text();
	}
    else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_FAULTCUR)
	{
		pData->m_strValue = ui->m_pFaultIEdit->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME)
	{
		pData->m_strValue = ui->m_pFaultTimeEdit->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANTest_CHECK)
	{
		bvalue = ui->m_pATest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNTest_CHECK)
	{
		bvalue = ui->m_pBTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNTest_CHECK)
	{
		bvalue = ui->m_pCTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABTest_CHECK)
	{
		bvalue = ui->m_pABTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCTest_CHECK)
	{
		bvalue = ui->m_pBCTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CATest_CHECK)
	{
		bvalue = ui->m_pCATest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZeroTest_CHECK)
	{
		bvalue = ui->m_pZeroSeqTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegTest_CHECK)
	{
		bvalue = ui->m_pNegativeSeqTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeA_CHECK)
	{
		bvalue = ui->m_pAAN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeAB_CHECK)
	{
		bvalue = ui->m_pAAB_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeCA_CHECK)
	{
		bvalue = ui->m_pACA_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeABC_CHECK)
	{
		bvalue = ui->m_pAABC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
		else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeB_CHECK)
	{
		bvalue = ui->m_pBBN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeAB_CHECK)
	{
		bvalue = ui->m_pBAB_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeBC_CHECK)
	{
		bvalue = ui->m_pBBC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeABC_CHECK)
	{
		bvalue = ui->m_pBABC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeC_CHECK)
	{
		bvalue = ui->m_pCCN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeBC_CHECK)
	{
		bvalue = ui->m_pCBC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeCA_CHECK)
	{
		bvalue = ui->m_pCCA_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeABC_CHECK)
	{
		bvalue = ui->m_pCABC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABFaultTypeAB_CHECK)
	{
		bvalue = ui->m_pABAB_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCFaultTypeBC_CHECK)
	{
		bvalue = ui->m_pBCBC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CAFaultTypeCA_CHECK)
	{
		bvalue = ui->m_pCACA_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeZero_CHECK)
	{
		bvalue = ui->m_pZeroSeq_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeA_CHECK)
	{
		bvalue = ui->m_pZeroAN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeB_CHECK)
	{
		bvalue = ui->m_pZeroBN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeC_CHECK)
	{
		bvalue = ui->m_pZeroCN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeNegative_CHECK)
	{
		bvalue = ui->m_pNegativeSeq_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeA_Check_CHECK)
	{
		bvalue = ui->m_pNegativeAN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeB_CHECK)
	{
		bvalue = ui->m_pNegativeBN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeC_CHECK)
	{
		bvalue = ui->m_pNegativeCN_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeAB_CHECK)
	{
		bvalue = ui->m_pNegativeAB_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeBC_CHECK)
	{
		bvalue = ui->m_pNegativeBC_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeCA_CHECK)
	{
		bvalue = ui->m_pNegativeCA_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
    else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ADDMULT_ERRTYPE)    //20240806 wanmj
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_pCmb_ErrorType->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR)
	{
		pData->m_strValue = ui->m_pAbsErrorEdit->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR)
	{
		pData->m_strValue = ui->m_pRelErrorEdit->text();
	}
}

//20241024 wanmj
void QPowerDirAddMultDlg::InitUI()
{
    CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/PowerDirection.png");
#else
    strPngPath =  ":/ctrls/images/PowerDirection.png";
#endif

    this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_ERRORTYPE);
    ui->m_pCmb_ErrorType->ShowBaseList(pDataType);

    ui->m_pTestItemsLabel->setText(g_sLangTxt_ActionTime_TestItem);
    ui->m_pFaultDiffLabel->setText(g_sLangTxt_ActionTime_FaultPhase);
    ui->m_pATest_CheckBox->setText(g_sLangTxt_PowerDir_APhaseTest);
    ui->m_pBTest_CheckBox->setText(g_sLangTxt_PowerDir_BPhaseTest);
    ui->m_pCTest_CheckBox->setText(g_sLangTxt_PowerDir_CPhaseTest);
    ui->m_pABTest_CheckBox->setText(g_sLangTxt_PowerDir_ABPhaseTest);
    ui->m_pBCTest_CheckBox->setText(g_sLangTxt_PowerDir_BCPhaseTest);
    ui->m_pCATest_CheckBox->setText(g_sLangTxt_PowerDir_CAPhaseTest);
    ui->m_pZeroSeqTest_CheckBox->setText(g_sLangTxt_PowerDir_TestPhase_Zero);
    ui->m_pNegativeSeqTest_CheckBox->setText(g_sLangTxt_PowerDir_TestPhase_Neg);
    ui->m_pZeroSeq_CheckBox->setText(g_sLangTxt_Native_ZeroSeq);
    ui->m_pNegativeSeq_CheckBox->setText(g_sLangTxt_Native_NegativeSeq);

    ui->m_groupBox_FaultParas->setTitle(g_sLangTxt_PowerDir_FaultParas);
    ui->m_groupBox_AngleParas->setTitle(g_sLangTxt_PowerDir_TestParas);
    ui->m_groupBox_Results->setTitle(g_sLangTxt_StateEstimate_ResultEstimate);
    ui->m_pFaultVLabel->setText(g_sLangTxt_ActionTime_FaultVol);
    ui->m_pFaultILabel->setText(g_sLangTxt_Swing_SCurrent);
    ui->m_pFaultTimeLabel->setText(g_sLangTxt_PowerDir_FaultTime);
    ui->m_pMaxSensitAngleLabel->setText(g_sLangTxt_PowerDir_MaxSenAngle);
    ui->m_pActRangeLabel->setText(g_sLangTxt_PowerDir_ActionAreaRange);
    ui->m_pStepLabel->setText(g_sLangTxt_PowerDir_StepValue);
    ui->m_pErrorTypeLabel->setText(g_sLangTxt_ActionTime_ErrType);
    ui->m_pRelErrorLabel->setText(g_sLangTxt_ActionTime_RelErr);
    ui->m_pAbsErrorLabel->setText(g_sLangTxt_PowerDir_AbsErr);
    ui->m_pOK_PushButton->setText(g_sLangTxt_OK);
    ui->m_pCancel_PushButton->setText(g_sLangTxt_Cancel);

}

void QPowerDirAddMultDlg::initData()
{
#ifdef _PSX_QT_WINDOWS_
	ui->m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));
	ui->m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));
#else
	ui->m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/check.png"));
	ui->m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif
	slot_chb_ATestClicked();
	slot_chb_BTestClicked();
	slot_chb_CTestClicked();
	slot_chb_ABTestClicked();
	slot_chb_BCTestClicked();
	slot_chb_CATestClicked();
	slot_chb_ZeroSeqTestClicked();
	slot_chb_NegativeSeqTestClicked();
}


void QPowerDirAddMultDlg::initConnections()
{
	connect(ui->m_pStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneStep_editingFinished()));
	connect(ui->m_pMaxSensitAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneMaxSensitAngle_editingFinished()));
	connect(ui->m_pActRangeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneActRange_editingFinished()));
	connect(ui->m_pFaultVEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFaultV_editingFinished()));
	connect(ui->m_pFaultIEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFaultI_editingFinished()));
	connect(ui->m_pFaultTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFaultTime_editingFinished()));
	connect(ui->m_pAbsErrorEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAbsError_editingFinished()));
	connect(ui->m_pRelErrorEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneRelError_editingFinished()));

	connect(ui->m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_OKClick()));
	connect(ui->m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_CancelClick()));
	//connect(ui->m_pResults_pushButton, SIGNAL(clicked ()), this, SLOT(slot_pbn_ResultsClicked()));

	connect(ui->m_pATest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ATestClicked()));
	connect(ui->m_pBTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BTestClicked()));
	connect(ui->m_pCTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CTestClicked()));
	connect(ui->m_pABTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ABTestClicked()));
	connect(ui->m_pBCTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BCTestClicked()));
	connect(ui->m_pCATest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CATestClicked()));
	connect(ui->m_pZeroSeqTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ZeroSeqTestClicked()));
	connect(ui->m_pNegativeSeqTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeSeqTestClicked()));

	connect(ui->m_pAAN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ATypeClicked()));
	connect(ui->m_pAAB_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ATypeClicked()));
	connect(ui->m_pACA_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ATypeClicked()));
	connect(ui->m_pAABC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ATypeClicked()));

	connect(ui->m_pBBN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BTypeClicked()));
	connect(ui->m_pBAB_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BTypeClicked()));
	connect(ui->m_pBBC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BTypeClicked()));
	connect(ui->m_pBABC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BTypeClicked()));

	connect(ui->m_pCCN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CTypeClicked()));
	connect(ui->m_pCBC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CTypeClicked()));
	connect(ui->m_pCCA_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CTypeClicked()));
	connect(ui->m_pCABC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CTypeClicked()));

	connect(ui->m_pABAB_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ABTypeClicked()));
	connect(ui->m_pBCBC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_BCTypeClicked()));
	connect(ui->m_pCACA_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_CATypeClicked()));

	connect(ui->m_pZeroSeq_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ZeroTypeClicked()));
	connect(ui->m_pZeroAN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ZeroTypeClicked()));
	connect(ui->m_pZeroBN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ZeroTypeClicked()));
	connect(ui->m_pZeroCN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_ZeroTypeClicked()));

	connect(ui->m_pNegativeSeq_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));
	connect(ui->m_pNegativeAN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));
	connect(ui->m_pNegativeBN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));
	connect(ui->m_pNegativeCN_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));
	connect(ui->m_pNegativeAB_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));
	connect(ui->m_pNegativeBC_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));
	connect(ui->m_pNegativeCA_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_NegativeTypeClicked()));

}

void QPowerDirAddMultDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTVOLT);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTCURRENT);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CATest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZeroTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegTest_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeAB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeCA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANFaultTypeABC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeAB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeBC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BNFaultTypeABC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeBC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeCA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CNFaultTypeABC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABFaultTypeAB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_BCFaultTypeBC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CAFaultTypeCA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeZero_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ZerFaultTypeC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeNegative_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeA_Check_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeAB_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeBC_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_NegFaultTypeCA_CHECK);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_CONNECTMODE);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR);
	CheckForPresence(STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR);
	
}
void QPowerDirAddMultDlg::CheckForPresence(CString strID)
{
	if(m_pDataGroup == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pDataGroup->FindByID(strID);
	if(pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_POWERDIR_PARAS_ID_DEFAULT;
		m_pDataGroup->AddNewChild(pNew);
	}
}

float QPowerDirAddMultDlg::slot_lne_Changed(QSttLineEdit* pLineEdit)
{
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
	//fv = setLimit(0,999.999,fv);
	return fv;
}

void QPowerDirAddMultDlg::slot_lneStep_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pStepEdit);
	fv = setLimit(0,360.0,fv);
	ui->m_pStepEdit->setText(QString::number(fv,'f',3));
	ui->m_pStepEdit->setCursorPosition(0);
}

void QPowerDirAddMultDlg::slot_lneMaxSensitAngle_editingFinished()
{
    if(ui->m_pMaxSensitAngleEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pMaxSensitAngleEdit)->IsSetting())
        {
            return;
        }
    }

	float fv = slot_lne_Changed(ui->m_pMaxSensitAngleEdit);
	fv = setLimit(0,360.0,fv);
	ui->m_pMaxSensitAngleEdit->setText(QString::number(fv,'f',3));
	ui->m_pMaxSensitAngleEdit->setCursorPosition(0);
}

void QPowerDirAddMultDlg::slot_lneActRange_editingFinished()
{
	float fv  = slot_lne_Changed(ui->m_pActRangeEdit);
	fv = setLimit(0,360.0,fv);
	ui->m_pActRangeEdit->setText(QString::number(fv,'f',3));
	ui->m_pActRangeEdit->setCursorPosition(0);
}


void QPowerDirAddMultDlg::slot_lneFaultV_editingFinished()
{
	float fv  = slot_lne_Changed(ui->m_pFaultVEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pFaultVEdit->setText(QString::number(fv,'f',3));
	ui->m_pFaultVEdit->setCursorPosition(0);
}

void QPowerDirAddMultDlg::slot_lneFaultI_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pFaultIEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,fv);
	ui->m_pFaultIEdit->setText(QString::number(fv,'f',3));
	ui->m_pFaultIEdit->setCursorPosition(0);
}

void QPowerDirAddMultDlg::slot_lneFaultTime_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pFaultTimeEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pFaultTimeEdit->setText(QString::number(fv,'f',3));
	ui->m_pFaultTimeEdit->setCursorPosition(0);
}

void QPowerDirAddMultDlg::slot_lneAbsError_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pAbsErrorEdit);
	fv = setLimit(STT_MULTI_MACRO_PARAS_AbsErrorMinValue,STT_MULTI_MACRO_PARAS_AbsErrorMaxValue,fv);
	ui->m_pAbsErrorEdit->setText(QString::number(fv,'f',3));
	ui->m_pAbsErrorEdit->setCursorPosition(0);
}

void QPowerDirAddMultDlg::slot_lneRelError_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pRelErrorEdit);
	fv = setLimit(STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue,fv);
	ui->m_pRelErrorEdit->setText(QString::number(fv,'f',3));
	ui->m_pRelErrorEdit->setCursorPosition(0);
}


void QPowerDirAddMultDlg::slot_chb_TestTypeClicked()
{
	if (ui->m_pATest_CheckBox->isChecked()||ui->m_pBTest_CheckBox->isChecked()||ui->m_pCTest_CheckBox->isChecked()||
		ui->m_pABTest_CheckBox->isChecked()||ui->m_pBCTest_CheckBox->isChecked()||ui->m_pCATest_CheckBox->isChecked()||
		ui->m_pZeroSeqTest_CheckBox->isChecked()||ui->m_pNegativeSeqTest_CheckBox->isChecked())
	{
		slot_chb_ATypeClicked();
		slot_chb_BTypeClicked();
		slot_chb_CTypeClicked();
		slot_chb_ABTypeClicked();
		slot_chb_BCTypeClicked();
		slot_chb_CATypeClicked();
		slot_chb_ZeroTypeClicked();
		slot_chb_NegativeTypeClicked();
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_ATestClicked()
{
	if (ui->m_pATest_CheckBox->isChecked())
	{
		ui->m_pAAN_CheckBox->setDisabled(false);
		ui->m_pAAB_CheckBox->setDisabled(false);
		ui->m_pACA_CheckBox->setDisabled(false);
		ui->m_pAABC_CheckBox->setDisabled(false);
	}
	else
	{
		ui->m_pAAN_CheckBox->setDisabled(true);
		ui->m_pAAB_CheckBox->setDisabled(true);
		ui->m_pACA_CheckBox->setDisabled(true);
		ui->m_pAABC_CheckBox->setDisabled(true);
	}
	slot_chb_TestTypeClicked();
}

void QPowerDirAddMultDlg::slot_chb_BTestClicked()
{
	if (ui->m_pBTest_CheckBox->isChecked())
	{
		ui->m_pBBN_CheckBox->setDisabled(false);
		ui->m_pBAB_CheckBox->setDisabled(false);
		ui->m_pBBC_CheckBox->setDisabled(false);
		ui->m_pBABC_CheckBox->setDisabled(false);
	}
	else
	{
		ui->m_pBBN_CheckBox->setDisabled(true);
		ui->m_pBAB_CheckBox->setDisabled(true);
		ui->m_pBBC_CheckBox->setDisabled(true);
		ui->m_pBABC_CheckBox->setDisabled(true);
	}
	slot_chb_TestTypeClicked();
}

void QPowerDirAddMultDlg::slot_chb_CTestClicked()
{
	if (ui->m_pCTest_CheckBox->isChecked())
	{
		ui->m_pCCN_CheckBox->setDisabled(false);
		ui->m_pCBC_CheckBox->setDisabled(false);
		ui->m_pCCA_CheckBox->setDisabled(false);
		ui->m_pCABC_CheckBox->setDisabled(false);
	}
	else
	{
		ui->m_pCCN_CheckBox->setDisabled(true);
		ui->m_pCBC_CheckBox->setDisabled(true);
		ui->m_pCCA_CheckBox->setDisabled(true);
		ui->m_pCABC_CheckBox->setDisabled(true);
	}
	slot_chb_TestTypeClicked();
}

void QPowerDirAddMultDlg::slot_chb_ABTestClicked()
{
    if (IsConnect == true)      //  20240725 wanmj 90度接线可以设置相间故障
	{
		ui->m_pABTest_CheckBox->setDisabled(false);
		ui->m_pABAB_CheckBox->setDisabled(false);
		if (ui->m_pABTest_CheckBox->isChecked())
		{
			ui->m_pABAB_CheckBox->setDisabled(false);
		}
		else
		{
			ui->m_pABAB_CheckBox->setDisabled(true);
		}
		slot_chb_TestTypeClicked();
	}
	else
	{
		ui->m_pABTest_CheckBox->setDisabled(true);
		ui->m_pABAB_CheckBox->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_BCTestClicked()
{
    if (IsConnect == true)      //  20240725 wanmj 90度接线可以设置相间故障
	{
		ui->m_pBCTest_CheckBox->setDisabled(false);
		ui->m_pBCBC_CheckBox->setDisabled(false);
		if (ui->m_pBCTest_CheckBox->isChecked())
		{
			ui->m_pBCBC_CheckBox->setDisabled(false);
		}
		else
		{
			ui->m_pBCBC_CheckBox->setDisabled(true);
		}
		slot_chb_TestTypeClicked();
	}
	else
	{
		ui->m_pBCTest_CheckBox->setDisabled(true);
		ui->m_pBCBC_CheckBox->setDisabled(true);
	}
	
}
void QPowerDirAddMultDlg::slot_chb_CATestClicked()
{
    if (IsConnect == true)      //  20240725 wanmj 90度接线可以设置相间故障
	{
		ui->m_pCATest_CheckBox->setDisabled(false);
		ui->m_pCACA_CheckBox->setDisabled(false);
		if (ui->m_pCATest_CheckBox->isChecked())
		{
			ui->m_pCACA_CheckBox->setDisabled(false);
		}
		else
		{
			ui->m_pCACA_CheckBox->setDisabled(true);
		}
		slot_chb_TestTypeClicked();
	}
	else
	{
		ui->m_pCATest_CheckBox->setDisabled(true);
		ui->m_pCACA_CheckBox->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_ZeroSeqTestClicked()
{
	if (ui->m_pZeroSeqTest_CheckBox->isChecked())
	{
		ui->m_pZeroSeq_CheckBox->setDisabled(false);
		ui->m_pZeroAN_CheckBox->setDisabled(false);
		ui->m_pZeroBN_CheckBox->setDisabled(false);
		ui->m_pZeroCN_CheckBox->setDisabled(false);
	}
	else
	{
		ui->m_pZeroSeq_CheckBox->setDisabled(true);
		ui->m_pZeroAN_CheckBox->setDisabled(true);
		ui->m_pZeroBN_CheckBox->setDisabled(true);
		ui->m_pZeroCN_CheckBox->setDisabled(true);
	}
	slot_chb_TestTypeClicked();
}

void QPowerDirAddMultDlg::slot_chb_NegativeSeqTestClicked()
{
	if (ui->m_pNegativeSeqTest_CheckBox->isChecked())
	{
		ui->m_pNegativeSeq_CheckBox->setDisabled(false);
		ui->m_pNegativeAN_CheckBox->setDisabled(false);
		ui->m_pNegativeBN_CheckBox->setDisabled(false);
		ui->m_pNegativeCN_CheckBox->setDisabled(false);
		ui->m_pNegativeAB_CheckBox->setDisabled(false);
		ui->m_pNegativeBC_CheckBox->setDisabled(false);
		ui->m_pNegativeCA_CheckBox->setDisabled(false);
	}
	else
	{
		ui->m_pNegativeSeq_CheckBox->setDisabled(true);
		ui->m_pNegativeAN_CheckBox->setDisabled(true);
		ui->m_pNegativeBN_CheckBox->setDisabled(true);
		ui->m_pNegativeCN_CheckBox->setDisabled(true);
		ui->m_pNegativeAB_CheckBox->setDisabled(true);
		ui->m_pNegativeBC_CheckBox->setDisabled(true);
		ui->m_pNegativeCA_CheckBox->setDisabled(true);
	}
	slot_chb_TestTypeClicked();
}

void QPowerDirAddMultDlg::slot_chb_ATypeClicked()
{
	if (ui->m_pAAN_CheckBox->isChecked()||ui->m_pAAB_CheckBox->isChecked()||
		ui->m_pACA_CheckBox->isChecked()||ui->m_pAABC_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_BTypeClicked()
{
	if (ui->m_pBBN_CheckBox->isChecked()||ui->m_pBAB_CheckBox->isChecked()||
		ui->m_pBBC_CheckBox->isChecked()||ui->m_pBABC_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_CTypeClicked()
{
	if (ui->m_pCCN_CheckBox->isChecked()||ui->m_pCBC_CheckBox->isChecked()||
		ui->m_pCCA_CheckBox->isChecked()||ui->m_pCABC_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_ABTypeClicked()
{
	if (ui->m_pABAB_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_BCTypeClicked()
{
	if (ui->m_pBCBC_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_CATypeClicked()
{
	if (ui->m_pCACA_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}


void QPowerDirAddMultDlg::slot_chb_ZeroTypeClicked()
{
	if (ui->m_pZeroSeq_CheckBox->isChecked()||ui->m_pZeroAN_CheckBox->isChecked()||
		ui->m_pZeroAN_CheckBox->isChecked()||ui->m_pZeroCN_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}

void QPowerDirAddMultDlg::slot_chb_NegativeTypeClicked()
{
	if (ui->m_pNegativeSeq_CheckBox->isChecked()||ui->m_pNegativeAN_CheckBox->isChecked()||
		ui->m_pNegativeBN_CheckBox->isChecked()||ui->m_pNegativeCN_CheckBox->isChecked()||
		ui->m_pNegativeAB_CheckBox->isChecked()||ui->m_pNegativeBC_CheckBox->isChecked()||
		ui->m_pNegativeCA_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}
void QPowerDirAddMultDlg::slot_cmb_EerrorType_Changed()
{
	
}
void QPowerDirAddMultDlg::slot_pbn_OKClick()
{
    //20240725 wanmj
    GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
    this->done(Accepted);
}

void QPowerDirAddMultDlg::slot_pbn_CancelClick()
{
	 this->close();
}



//void QPowerDirAddMultDlg::slot_pbn_ResultsClicked()
//{
//	POS pos = m_pDataGroup->GetHeadPosition();
//	while(pos!=NULL)
//	{
//		CDvmData *pData = (CDvmData*)m_pDataGroup->GetNext(pos);
//		GetPageToValue(pData);
//	}
//	//缁撴灉璇勪及
//	QPowerDirResultEstimateDlg oResultDlg;
//	oResultDlg.SetDatas(m_pDataGroup);
//	if(oResultDlg.exec() == QDialog::Accepted)
//	{
//		oResultDlg.GetDatas(m_pDataGroup);
//	}
//}
