#include "RecloseAccCommonParasDlg.h"
#include "ui_RecloseAccCommonParasDlg.h"
#include "RecloseAccCommon.h"
#include "SttMultiMacroRecloseAccParasDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../XLangResource_Native.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include <cmath>

extern CFont *g_pSttGlobalFont;

QRecloseAccCommonParasDlg::QRecloseAccCommonParasDlg(QWidget *parent) :
QDialog(parent),
ui(new Ui::QRecloseAccCommonParasDlg)
{
	ui->setupUi(this);
    m_nInputWidgetWidth = 150;
	InitUI();
    m_nModify = 0;
}

QRecloseAccCommonParasDlg::~QRecloseAccCommonParasDlg()
{
	delete ui;
}

void QRecloseAccCommonParasDlg::InitUI()
{
	this->setFont(*g_pSttGlobalFont);

	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/Reclose.png");
#else
    strPngPath =  ":/ctrls/images/Reclose.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Gradient_CommonParas);

    ui->m_cbbCTPos->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbFaultTrigMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbPTPos->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbSimulateBreakerDelay->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editActionTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editBrkBreakTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editBrkCloseTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editILoad->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editILoadPh->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreFaultTime->setFixedWidth(m_nInputWidgetWidth);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_FAULTTRIGMODEPNV);
    ui->m_cbbFaultTrigMode->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_PTPOSITION);
    ui->m_cbbPTPos->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_CTPOS);
    ui->m_cbbCTPos->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_CBSIMULSEL);
    ui->m_cbbSimulateBreakerDelay->ShowBaseList(pDataType);

    ui->m_labPreFaultTime->setText(g_sLangTxt_Impedance_FailTime);
    ui->m_labFaultTime->setText(g_sLangTxt_ActionTime_FaultTime);
    ui->m_labActionTime->setText(g_sLangTxt_DistanceSearch_MinActionTime);
    ui->m_labFaultTrigMode->setText(g_sLangTxt_RecloseAcc_FaultTrigMode);
    ui->m_labPTPos->setText(g_sLangTxt_DistanceSearch_PTPos);
    ui->m_labCTPos->setText(g_sLangTxt_DistanceSearch_CTPos);
    ui->m_labILoad->setText(g_sLangTxt_LoadI);
    ui->m_labILoadPh->setText(g_sLangTxt_State_LoadAngle);
    ui->m_labSimulateBreakerDelay->setText(g_sLangTxt_DistanceSearch_SimulateBreakerDelay);
    ui->m_labBrkBreakTime->setText(g_sLangTxt_DistanceSearch_BrkBreakTime);
    ui->m_labBrkCloseTime->setText(g_sLangTxt_DistanceSearch_BrkCloseTime);
    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);
}

void QRecloseAccCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME)
	{
		ui->m_editPreFaultTime->setText(RecloseAccValueCheck(pData->m_strValue, PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME)
	{
		ui->m_editFaultTime->setText(RecloseAccValueCheck(pData->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN, 3));
	}
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ACTIONTIME)
    {
        //ui->m_editActionTime->setText(RecloseAccValueCheck(pData->m_strValue, ACTIONTIME_MAX, ACTIONTIME_MIN, 3));
        ui->m_editActionTime->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, ACTIONTIME_MAX, ACTIONTIME_MIN, 3), 3);
    }
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_FAULTTRIGMODEPNV);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbFaultTrigMode->SetCurrSelByName(pValue->m_strName);

        on_m_cbbFaultTrigMode_currentIndexChanged(CString_To_long(pValue->m_strIndex));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_PTPOSITION);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbPTPos->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_CTPOS);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbCTPos->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD)
	{
		ui->m_editILoad->setText(RecloseAccValueCheck(pData->m_strValue, ILOAD_MAX, ILOAD_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH)
	{
        ui->m_editILoadPh->setText(RecloseAccValueCheck(pData->m_strValue, ILOADPH_MAX, ILOADPH_MIN,2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_CBSIMULSEL);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbSimulateBreakerDelay->SetCurrSelByName(pValue->m_strName);

        on_m_cbbSimulateBreakerDelay_currentIndexChanged(CString_To_long(pValue->m_strIndex));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME)
	{
        //20240820 wanmj xml数据单位是s 界面单位是ms
        float fBreakTime = pData->m_strValue.toFloat()*1000;
        CString strBreakTime;
        strBreakTime.setNum(fBreakTime);
        ui->m_editBrkBreakTime->setText(RecloseAccValueCheck(strBreakTime, BRKBREAKTIME_MAX, BRKBREAKTIME_MIN,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME)
	{
        //20240820 wanmj xml数据单位是s 界面单位是ms
        float fRecloseTime = pData->m_strValue.toFloat()*1000;
        CString strRecloseTime;
        strRecloseTime.setNum(fRecloseTime);
        ui->m_editBrkCloseTime->setText(RecloseAccValueCheck(strRecloseTime, BRKCLOSETIME_MAX, BRKCLOSETIME_MIN,0));
	}

	return;
}

void QRecloseAccCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_editPreFaultTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME)
	{
		pData->m_strValue = ui->m_editFaultTime->text();
	}
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ACTIONTIME)
    {
        //pData->m_strValue = ui->m_editActionTime->text();
        pData->m_strValue = ui->m_editActionTime->GetText();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultTrigMode->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbPTPos->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbCTPos->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD)
	{
		pData->m_strValue = ui->m_editILoad->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH)
	{
		pData->m_strValue = ui->m_editILoadPh->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbSimulateBreakerDelay->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME)
	{
        //20240820 wanmj xml数据单位是s 界面单位是ms
        CString strBreakTime = ui->m_editBrkBreakTime->text();
        float fBreakTime = strBreakTime.toFloat()/1000;
        strBreakTime.setNum(fBreakTime);
        pData->m_strValue = strBreakTime;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME)
	{
        //20240820 wanmj xml数据单位是s 界面单位是ms
        CString strCloseTime = ui->m_editBrkCloseTime->text();
        float fCloseTime = strCloseTime.toFloat()/1000;
        strCloseTime.setNum(fCloseTime);
        pData->m_strValue = strCloseTime;
	}

	return;
}

void QRecloseAccCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME);

	return;
}

void QRecloseAccCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QRecloseAccCommonParasDlg::SetDatas(CExBaseList *pParas)
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

void QRecloseAccCommonParasDlg::UpdateCurrentCommonParas(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;

	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);

	return;
}

void QRecloseAccCommonParasDlg::UpdateAllCommonParas(CExBaseList *pAllItems)
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

BOOL QRecloseAccCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE
                || pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS
                || pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS
                || pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY)
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

void QRecloseAccCommonParasDlg::on_m_editPreFaultTime_editingFinished()
{
	ui->m_editPreFaultTime->setText(RecloseAccValueCheck(ui->m_editPreFaultTime->text(),PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	return;
}


void QRecloseAccCommonParasDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}

void QRecloseAccCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QRecloseAccCommonParasDlg::on_m_editFaultTime_editingFinished()
{
	ui->m_editFaultTime->setText(RecloseAccValueCheck(ui->m_editFaultTime->text(), FAULTTIME_MAX, FAULTTIME_MIN,3));
	return;
}

void QRecloseAccCommonParasDlg::on_m_cbbFaultTrigMode_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultTrigMode->GetCurrSelObject();
    if(pValue == NULL)
       return;

    if(CString_To_long(pValue->m_strIndex) == 0)
		ui->m_editPreFaultTime->setEnabled(true);
	else
		ui->m_editPreFaultTime->setEnabled(false);

	return;
}

void QRecloseAccCommonParasDlg::on_m_editILoad_editingFinished()
{
	ui->m_editILoad->setText(RecloseAccValueCheck(ui->m_editILoad->text(), ILOAD_MAX, ILOAD_MIN,3));
	return;
}

void QRecloseAccCommonParasDlg::on_m_editILoadPh_editingFinished()
{
    ui->m_editILoadPh->setText(RecloseAccValueCheck(ui->m_editILoadPh->text(), ILOADPH_MAX, ILOADPH_MIN,2));
	return;
}

void QRecloseAccCommonParasDlg::on_m_cbbSimulateBreakerDelay_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbSimulateBreakerDelay->GetCurrSelObject();
    if(pValue == NULL)
        return;

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

void QRecloseAccCommonParasDlg::on_m_editBrkBreakTime_editingFinished()
{
    ui->m_editBrkBreakTime->setText(RecloseAccValueCheck(ui->m_editBrkBreakTime->text(), BRKBREAKTIME_MAX, BRKBREAKTIME_MIN,0));
	return;
}

void QRecloseAccCommonParasDlg::on_m_editBrkCloseTime_editingFinished()
{
    ui->m_editBrkCloseTime->setText(RecloseAccValueCheck(ui->m_editBrkCloseTime->text(), BRKCLOSETIME_MAX, BRKCLOSETIME_MIN,0));
	return;
}

void QRecloseAccCommonParasDlg::on_m_editActionTime_editingFinished()
{
    if(ui->m_editActionTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_editActionTime)->IsSetting())
        {
            return;
        }
    }

    ui->m_editActionTime->setText(RecloseAccValueCheck(ui->m_editActionTime->text(), ACTIONTIME_MAX, ACTIONTIME_MIN,3));
    return;
}
