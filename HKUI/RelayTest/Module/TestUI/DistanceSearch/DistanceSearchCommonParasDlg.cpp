#include "DistanceSearchCommonParasDlg.h"
#include "ui_DistanceSearchCommonParasDlg.h"
#include "DistanceSearchCommon.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../XLangResource_Native.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include <cmath>

extern CFont *g_pSttGlobalFont;

QDistanceSearchCommonParasDlg::QDistanceSearchCommonParasDlg(QWidget *parent) :
QDialog(parent),
ui(new Ui::QDistanceSearchCommonParasDlg)
{
	ui->setupUi(this);
    m_nInputWidgetWidth = 190;
	InitUI();
    m_nModify = 0;
}

QDistanceSearchCommonParasDlg::~QDistanceSearchCommonParasDlg()
{
	delete ui;
}

void QDistanceSearchCommonParasDlg::InitUI()
{
	this->setFont(*g_pSttGlobalFont);

	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/DistanceSearchTest.png");
#else
    strPngPath =  ":/ctrls/images/DistanceSearchTest.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Gradient_CommonParas);

    ui->m_editActionTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAngKx->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editBrkBreakTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editBrkCloseTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultAng->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editILoad->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editILoadPh->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editKlKr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editTimeAfterTrigger->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editZsAng->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editZsMag->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbCalcuMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbCTPos->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbFaultAngMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbFaultId->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbK0Mode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbPTPos->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbSearchMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbSimulateBreakerDelay->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editZl->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editZAng->setFixedWidth(m_nInputWidgetWidth);

    ui->m_labPreTime->setText(g_sLangTxt_Impedance_FailTime);
	ui->m_labTimeAfterTrigger->setText(g_sLangTxt_DistanceSearch_TimeAfterTrigger);
    ui->m_labFaultTime->setText(g_sLangTxt_ActionTime_FaultTime);
    ui->m_labActionTime->setText(g_sLangTxt_DistanceSearch_MinActionTime);
	ui->m_labZl->setText(g_sLangTxt_DistanceSearch_Zl);
	ui->m_labZAng->setText(g_sLangTxt_Gradient_ImpAngle);
	ui->m_labK0Mode->setText(g_sLangTxt_DistanceSearch_K0Mode);
	ui->m_labKlKr_2->setText(g_sLangTxt_State_ZeroCoeff);
	ui->m_labAngKx_2->setText(g_sLangTxt_State_ZeroCoeff);
	ui->m_labSearchMode->setText(g_sLangTxt_Native_search_way);
	ui->m_labILoad->setText(g_sLangTxt_LoadI);
	ui->m_labILoadPh->setText(g_sLangTxt_State_LoadAngle);

	ui->m_labCalMode->setText(g_sLangTxt_State_CalcType);
	ui->m_labZsMag->setText(g_sLangTxt_DistanceSearch_ZsMag);
	ui->m_labZsAng->setText(g_sLangTxt_DistanceSearch_ZsAngle);
	ui->m_labPTPos->setText(g_sLangTxt_DistanceSearch_PTPos);
	ui->m_labCTPos->setText(g_sLangTxt_DistanceSearch_CTPos);
	ui->m_labSimulateBreakerDelay->setText(g_sLangTxt_DistanceSearch_SimulateBreakerDelay);
	ui->m_labBrkBreakTime->setText(g_sLangTxt_DistanceSearch_BrkBreakTime);
	ui->m_labBrkCloseTime->setText(g_sLangTxt_DistanceSearch_BrkCloseTime);
	ui->m_labFaultId->setText(g_sLangTxt_DistanceSearch_FaultId);
	ui->m_labFaultAngMode->setText(g_sLangTxt_DistanceSearch_FaultAngMode);
	ui->m_labFaultAng->setText(g_sLangTxt_DistanceSearch_FaultAng);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_SEARCHMODE);
    ui->m_cbbSearchMode->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_PTPOSITION);
    ui->m_cbbPTPos->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_CTPOS);
    ui->m_cbbCTPos->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_CBSIMULSEL);
    ui->m_cbbSimulateBreakerDelay->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_FAULTANGMODE);
    ui->m_cbbFaultAngMode->ShowBaseList(pDataType);

    ui->m_cbbCalcuMode->addItem(g_sLangTxt_Native_INotChange);
    ui->m_cbbCalcuMode->addItem(g_sLangTxt_Native_UNotChange);
    ui->m_cbbCalcuMode->addItem(g_sLangTxt_Native_ZNotChange);
    ui->m_cbbFaultId->addItem(g_sLangTxt_State_No);
    ui->m_cbbFaultId->addItem(g_sLangID_State_Yes);

    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    return;
}

void QDistanceSearchCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PREFAULTTIME)
	{
		ui->m_editPreFaultTime->setText(DistanceSearchValueCheck(pData->m_strValue, PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TIMEAFTERTRIGGER)
	{
		ui->m_editTimeAfterTrigger->setText(DistanceSearchValueCheck(pData->m_strValue, TIMEAFTERTRIGGER_MAX, TIMEAFTERTRIGGER_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOAD)
	{
		ui->m_editILoad->setText(DistanceSearchValueCheck(pData->m_strValue, ILOAD_MAX, ILOAD_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOADPH)
	{
        ui->m_editILoadPh->setText(DistanceSearchValueCheck(pData->m_strValue, ILOADPH_MAX, ILOADPH_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_K0MODE)
	{
		ui->m_cbbK0Mode->setCurrentIndex(pData->m_strValue.toInt());
		switch(pData->m_strValue.toInt())
		{
		case 0:
			{
				ui->m_labKlKr->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_K0);
				ui->m_labAngKx->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_PHI_K0);
				break;
			}
		case 1:
			{
				ui->m_labKlKr->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_RERL);
				ui->m_labAngKx->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_XEXL);
				break;
			}
		case 2:
			{
				ui->m_labKlKr->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_Z0Z1);
				ui->m_labAngKx->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_PHI_Z0Z1);
				break;
			}
		default:
			break;
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_KLKR)
	{
		ui->m_editKlKr->setText(DistanceSearchValueCheck(pData->m_strValue, KLKR_MAX, KLKR_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANGKX)
	{
		ui->m_editAngKx->setText(DistanceSearchValueCheck(pData->m_strValue, ANGKX_MAX, ANGKX_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SEARCHMODE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_SEARCHMODE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbSearchMode->SetCurrSelByName(pValue->m_strName);
	}
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTIME)
    {
        ui->m_editFaultTime->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ACTIONTIME)
    {
        ui->m_editActionTime->setText(DistanceSearchValueCheck(pData->m_strValue, ACTIONTIME_MAX, ACTIONTIME_MIN,3));
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CALCUMODE)
	{
		ui->m_cbbCalcuMode->setCurrentIndex(pData->m_strValue.toInt());
		if(pData->m_strValue.toInt() == 2)
		{
			ui->m_editZsMag->setEnabled(true);
			ui->m_editZsAng->setEnabled(true);
		}
		else
		{
			ui->m_editZsMag->setEnabled(false);
			ui->m_editZsAng->setEnabled(false);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSMAG)
	{
		ui->m_editZsMag->setText(DistanceSearchValueCheck(pData->m_strValue, ZSMAG_MAX, ZSMAG_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSANG)
	{
        ui->m_editZsAng->setText(DistanceSearchValueCheck(pData->m_strValue, ZSANG_MAX, ZSANG_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PTPOS)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_PTPOSITION);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbPTPos->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CTPOS)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_CTPOS);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbCTPos->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SIMULATEBREAKERDELAY)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_CBSIMULSEL);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbSimulateBreakerDelay->SetCurrSelByName(pValue->m_strName);

		if(pData->m_strValue.toInt() == 1)
		{
			ui->m_editBrkBreakTime->setEnabled(true);
			ui->m_editBrkCloseTime->setEnabled(true);
		}
		else
		{
			ui->m_editBrkBreakTime->setEnabled(false);
			ui->m_editBrkCloseTime->setEnabled(false);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKBREAKTIME)
	{
        ui->m_editBrkBreakTime->setText(DistanceSearchValueCheck(pData->m_strValue, BRKBREAKTIME_MAX, BRKBREAKTIME_MIN,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKCLOSETIME)
	{
        ui->m_editBrkCloseTime->setText(DistanceSearchValueCheck(pData->m_strValue, BRKCLOSETIME_MAX, BRKCLOSETIME_MIN,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTID)
	{
		ui->m_cbbFaultId->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANGMODE)
	{ 
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_FAULTANGMODE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbFaultAngMode->SetCurrSelByName(pValue->m_strName);

		if(pData->m_strValue.toInt() == 1)
			ui->m_editFaultAng->setEnabled(true);
		else
			ui->m_editFaultAng->setEnabled(false);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANG)
	{
        ui->m_editFaultAng->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTANG_MAX, FAULTANG_MIN, 2));
	}
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZL)
    {
        ui->m_editZl->setText(DistanceSearchValueCheck(pData->m_strValue, ZSMAG_MAX, ZSMAG_MIN,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE)
    {
        ui->m_editZAng->setText(DistanceSearchValueCheck(pData->m_strValue, ZSANG_MAX, ZSANG_MIN,2));
    }

	return;
}

void QDistanceSearchCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_editPreFaultTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TIMEAFTERTRIGGER)
	{
		pData->m_strValue = ui->m_editTimeAfterTrigger->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOAD)
    {
        pData->m_strValue = ui->m_editILoad->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOADPH)
    {
        pData->m_strValue = ui->m_editILoadPh->text();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_K0MODE)
	{
		CString strIndex;
		strIndex.setNum(ui->m_cbbK0Mode->currentIndex());
		pData->m_strValue = strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_KLKR)
	{
		pData->m_strValue = ui->m_editKlKr->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANGKX)
	{
		pData->m_strValue = ui->m_editAngKx->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTIME)
    {
        pData->m_strValue = ui->m_editFaultTime->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ACTIONTIME)
    {
        pData->m_strValue = ui->m_editActionTime->text();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SEARCHMODE)
	{ 
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbSearchMode->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CALCUMODE)
	{
		CString strIndex;
		strIndex.setNum(ui->m_cbbCalcuMode->currentIndex());
		pData->m_strValue = strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSMAG)
	{
		pData->m_strValue = ui->m_editZsMag->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSANG)
	{
		pData->m_strValue = ui->m_editZsAng->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PTPOS)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbPTPos->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CTPOS)
	{    
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbCTPos->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SIMULATEBREAKERDELAY)
	{     
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbSimulateBreakerDelay->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKBREAKTIME)
	{
		pData->m_strValue = ui->m_editBrkBreakTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKCLOSETIME)
	{
		pData->m_strValue = ui->m_editBrkCloseTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTID)
	{
		CString strIndex;
		strIndex.setNum(ui->m_cbbFaultId->currentIndex());
		pData->m_strValue = strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANGMODE)
	{  
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultAngMode->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANG)
	{
		pData->m_strValue = ui->m_editFaultAng->text();
	}
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZL)
    {
        pData->m_strValue = ui->m_editZl->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE)
    {
        pData->m_strValue = ui->m_editZAng->text();
    }
	return;
}

void QDistanceSearchCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PREFAULTTIME);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TIMEAFTERTRIGGER);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOAD);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOADPH);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_K0MODE);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_KLKR);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANGKX);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ACTIONTIME);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SEARCHMODE);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CALCUMODE);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSMAG);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSANG);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZL);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE);

//	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FIRSTSECFAULTTIME);
//	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SECONDSECFAULTTIME);
//	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_THIRDSECFAULTTIME);
//	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FOURTHSECFAULTTIME);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PTPOS);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CTPOS);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SIMULATEBREAKERDELAY);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKBREAKTIME);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKCLOSETIME);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTID);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANGMODE);
	DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANG);

	return;
}

void QDistanceSearchCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QDistanceSearchCommonParasDlg::SetDatas(CExBaseList *pParas)
{
	if(pParas == NULL)
		return;
	m_pParas = pParas;
	CheckAllPresence(m_pParas);
    m_nModify = 0;

	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}

	return;
}

void QDistanceSearchCommonParasDlg::UpdateCurrentCommonParas(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;
	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);

	return;
}

void QDistanceSearchCommonParasDlg::UpdateAllCommonParas(CExBaseList *pAllItems)
{
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

	return;
}

BOOL QDistanceSearchCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData_New == NULL)
        {
            continue;
        }
        if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_K0MODE
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SEARCHMODE
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CALCUMODE
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PTPOS
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CTPOS
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SIMULATEBREAKERDELAY
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTID
                || pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANGMODE)
        {
            if(pData->m_strValue != pData_New->m_strValue)
            {
                m_nModify = 1;
                return TRUE;
            }

        }
        else
        {
            if(fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
            {
                m_nModify = 1;
                return TRUE;
            }
        }

    }
    return FALSE;
}

void QDistanceSearchCommonParasDlg::on_m_editPreFaultTime_editingFinished()
{
	ui->m_editPreFaultTime->setText(DistanceSearchValueCheck(ui->m_editPreFaultTime->text(),PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editTimeAfterTrigger_editingFinished()
{
	ui->m_editTimeAfterTrigger->setText(DistanceSearchValueCheck(ui->m_editTimeAfterTrigger->text(), TIMEAFTERTRIGGER_MAX, TIMEAFTERTRIGGER_MIN,3));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editILoad_editingFinished()
{
	ui->m_editILoad->setText(DistanceSearchValueCheck(ui->m_editILoad->text(), ILOAD_MAX, ILOAD_MIN,3));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editILoadPh_editingFinished()
{
    ui->m_editILoadPh->setText(DistanceSearchValueCheck(ui->m_editILoadPh->text(), ILOADPH_MAX, ILOADPH_MIN, 2));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_cbbK0Mode_currentIndexChanged(int index)
{
	ui->m_cbbK0Mode->setCurrentIndex(ui->m_cbbK0Mode->currentIndex());
	
	switch(index)
    {
    case 0:
    {
		ui->m_labKlKr->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_K0);
		ui->m_labAngKx->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_PHI_K0);
        break;
    }
    case 1:
    {
		ui->m_labKlKr->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_RERL);
		ui->m_labAngKx->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_XEXL);
        break;
    }
    case 2:
    {
		ui->m_labKlKr->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_Z0Z1);
		ui->m_labAngKx->setText(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_LAB_PHI_Z0Z1);
        break;
    }
    default:
        break;
    }
}

void QDistanceSearchCommonParasDlg::on_m_editKlKr_editingFinished()
{
	ui->m_editKlKr->setText(DistanceSearchValueCheck(ui->m_editKlKr->text(), KLKR_MAX, KLKR_MIN,3));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editAngKx_editingFinished()
{
	ui->m_editAngKx->setText(DistanceSearchValueCheck(ui->m_editAngKx->text(), ANGKX_MAX, ANGKX_MIN,3));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editZsMag_editingFinished()
{
	ui->m_editZsMag->setText(DistanceSearchValueCheck(ui->m_editZsMag->text(), ZSMAG_MAX, ZSMAG_MIN,3));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editZsAng_editingFinished()
{
    ui->m_editZsAng->setText(DistanceSearchValueCheck(ui->m_editZsAng->text(), ZSANG_MAX, ZSANG_MIN, 2));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editBrkBreakTime_editingFinished()
{
    ui->m_editBrkBreakTime->setText(DistanceSearchValueCheck(ui->m_editBrkBreakTime->text(), BRKBREAKTIME_MAX, BRKBREAKTIME_MIN,0));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editBrkCloseTime_editingFinished()
{
    ui->m_editBrkCloseTime->setText(DistanceSearchValueCheck(ui->m_editBrkCloseTime->text(), BRKCLOSETIME_MAX, BRKCLOSETIME_MIN,0));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_editFaultAng_editingFinished()
{
    ui->m_editFaultAng->setText(DistanceSearchValueCheck(ui->m_editFaultAng->text(), FAULTANG_MAX, FAULTANG_MIN, 2));
	return;
}

void QDistanceSearchCommonParasDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}

void QDistanceSearchCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QDistanceSearchCommonParasDlg::on_m_cbbCalcuMode_currentIndexChanged(int index)
{
    if(index == 2)
    {
        ui->m_editZsMag->setEnabled(true);
        ui->m_editZsAng->setEnabled(true);
    }
    else
    {
        ui->m_editZsMag->setEnabled(false);
        ui->m_editZsAng->setEnabled(false);
    }

    return;
}

void QDistanceSearchCommonParasDlg::on_m_cbbSimulateBreakerDelay_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbSimulateBreakerDelay->GetCurrSelObject();
    if(pValue == NULL)
    {
        return;
    }

    if(CString_To_long(pValue->m_strIndex) == 1)
    {
        ui->m_editBrkBreakTime->setEnabled(true);
        ui->m_editBrkCloseTime->setEnabled(true);
    }
    else
    {
        ui->m_editBrkBreakTime->setEnabled(false);
        ui->m_editBrkCloseTime->setEnabled(false);
    }

    return;
}

void QDistanceSearchCommonParasDlg::on_m_cbbFaultAngMode_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultAngMode->GetCurrSelObject();
    if(pValue == NULL)
    {
        return;
    }

	if(CString_To_long(pValue->m_strIndex) == 1)
        ui->m_editFaultAng->setEnabled(true);
    else
        ui->m_editFaultAng->setEnabled(false);

    return;
}

void QDistanceSearchCommonParasDlg::on_m_editFaultTime_editingFinished()
{
    ui->m_editFaultTime->setText(DistanceSearchValueCheck(ui->m_editFaultTime->text(), FAULTTIME_MAX, FAULTTIME_MIN,3));

    return;
}

void QDistanceSearchCommonParasDlg::on_m_editActionTime_editingFinished()
{
    ui->m_editActionTime->setText(DistanceSearchValueCheck(ui->m_editActionTime->text(), ACTIONTIME_MAX, ACTIONTIME_MIN,3));

    return;
}

void QDistanceSearchCommonParasDlg::on_m_editZl_editingFinished()
{
    ui->m_editZl->setText(DistanceSearchValueCheck(ui->m_editZl->text(), ZSMAG_MAX, ZSMAG_MIN,3));

    return;
}

void QDistanceSearchCommonParasDlg::on_m_editZAng_editingFinished()
{
    ui->m_editZAng->setText(DistanceSearchValueCheck(ui->m_editZAng->text(),  ZSANG_MAX, ZSANG_MIN,2));
}
