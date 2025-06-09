#include "RecloseAccBinarySignalDlg.h"
#include "ui_RecloseAccBinarySignalDlg.h"
#include "RecloseAccCommon.h"
#include "SttMultiMacroRecloseAccParasDefine.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"

extern CFont *g_pSttGlobalFont;

QRecloseAccBinarySignalDlg::QRecloseAccBinarySignalDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRecloseAccBinarySignalDlg)
{
    ui->setupUi(this);
    m_nInputWidgetWidth = 150;
    InitUI();
    m_nModify = 0;
}

QRecloseAccBinarySignalDlg::~QRecloseAccBinarySignalDlg()
{
    delete ui;
}

void QRecloseAccBinarySignalDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/Reclose.png");
#else
	strPngPath =  ":/ctrls/images/Reclose.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Native_SwitchVal);

	ui->m_tabWidget->setCurrentIndex(0);
	ui->m_tabWidget->setFont(*g_pSttGlobalFont);
	ui->m_btnOk->setFont(*g_pSttGlobalFont);
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);

    ui->m_cbbB01->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB02->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB03->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB04->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB05->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB06->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB07->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB08->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbBinSelect->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputA->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputB->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputC->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputD->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputE->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputF->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputG->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbInputH->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbOutputSwitchMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editOutputDelayTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editOutputKeepTime->setFixedWidth(m_nInputWidgetWidth);

    CDataType* pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
    ui->m_cbbInputA->ShowBaseList(pDataType);
    ui->m_cbbInputB->ShowBaseList(pDataType);
    ui->m_cbbInputC->ShowBaseList(pDataType);
    ui->m_cbbInputD->ShowBaseList(pDataType);
    ui->m_cbbInputE->ShowBaseList(pDataType);
    ui->m_cbbInputF->ShowBaseList(pDataType);
    ui->m_cbbInputG->ShowBaseList(pDataType);
    ui->m_cbbInputH->ShowBaseList(pDataType);

    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
    ui->m_cbbB01->ShowBaseList(pDataType);
    ui->m_cbbB02->ShowBaseList(pDataType);
    ui->m_cbbB03->ShowBaseList(pDataType);
    ui->m_cbbB04->ShowBaseList(pDataType);
    ui->m_cbbB05->ShowBaseList(pDataType);
    ui->m_cbbB06->ShowBaseList(pDataType);
    ui->m_cbbB07->ShowBaseList(pDataType);
    ui->m_cbbB08->ShowBaseList(pDataType);

    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOutStartMode);
    ui->m_cbbOutputSwitchMode->ShowBaseList(pDataType);

    ui->m_tabWidget->setTabText(0, g_sLangTxt_RecloseAcc_Input);
    ui->m_tabWidget->setTabText(1, g_sLangTxt_RecloseAcc_Output);
    ui->m_labBinSelect->setText(g_sLangTxt_RecloseAcc_BinSelect);
    ui->m_labOutputSwitchMode->setText(g_sLangTxt_RecloseAcc_OutputSwitchMode);
    ui->m_labOutputKeepTime->setText(g_sLangTxt_RecloseAcc_OutputKeepTime);
    ui->m_labOutputDelayTime->setText(g_sLangTxt_RecloseAcc_OutputDelayTime);

    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);
    SetBinBoutName();

	return;
}

void QRecloseAccBinarySignalDlg::SetBinBoutName()
{
    //开入开出映射修改
    //开入量
    QString strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 0);
    ui->m_labBinA->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 1);
    ui->m_labBinB->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 2);
    ui->m_labBinC->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 3);
    ui->m_labBinD->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 4);
    ui->m_labBinE->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 5);
    ui->m_labBinF->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 6);
    ui->m_labBinG->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 7);
    ui->m_labBinH->setText(strName);

    ui->m_cbbBinSelect->clear();
    strName = ui->m_labBinA->text() + "-" + ui->m_labBinB->text() + "-" + ui->m_labBinC->text() + "-" + ui->m_labBinD->text();
    ui->m_cbbBinSelect->addItem(strName);
    strName = ui->m_labBinE->text() + "-" + ui->m_labBinF->text() + "-" + ui->m_labBinG->text() + "-" + ui->m_labBinH->text();
    ui->m_cbbBinSelect->addItem(strName);

    //开出量
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 0);
    ui->m_labBout1->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
    ui->m_labBout2->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
    ui->m_labBout3->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
    ui->m_labBout4->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 4);
    ui->m_labBout5->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 5);
    ui->m_labBout6->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 6);
    ui->m_labBout7->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 7);
    ui->m_labBout8->setText(strName);

}

void QRecloseAccBinarySignalDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT)
	{
        ui->m_cbbBinSelect->setCurrentIndex(CString_To_long(pData->m_strValue));
        on_m_cbbBinSelect_currentIndexChanged(CString_To_long(pData->m_strValue));
	}
	if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputA->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputB->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputC->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputD->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputE->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputF->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputG->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DINPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbInputH->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB01->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB02->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB03->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB04->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB05->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB06->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB07->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOUTPUTSTATE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbB08->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_DOutStartMode);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbOutputSwitchMode->SetCurrSelByName(pValue->m_strName);

        on_m_cbbOutputSwitchMode_currentIndexChanged(CString_To_long(pValue->m_strIndex));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME)
	{
        ui->m_editOutputKeepTime->setText(RecloseAccValueCheck(pData->m_strValue, OUTPUTKEEPTIME_MAX, OUTPUTKEEPTIME_MIN, 3));
    }
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME)
	{
        ui->m_editOutputDelayTime->setText(RecloseAccValueCheck(pData->m_strValue, OUTPUTDELAYTIME_MAX, OUTPUTDELAYTIME_MIN, 3));
    }

	return;
}

void QRecloseAccBinarySignalDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
    if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT)
    {
        CString strTmp;
        strTmp.setNum(ui->m_cbbBinSelect->currentIndex());
        pData->m_strValue = strTmp;
    }
    if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputA->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputB->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }

    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputC->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputD->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputE->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputF->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputG->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbInputH->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB01->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB02->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB03->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB04->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB05->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB06->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB07->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbB08->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbOutputSwitchMode->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME)
    {
        pData->m_strValue = ui->m_editOutputKeepTime->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME)
    {
        pData->m_strValue = ui->m_editOutputDelayTime->text();
    }

	return;
}

void QRecloseAccBinarySignalDlg::CheckAllPresence(CExBaseList *pParas)
{
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H);
	

	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02);	
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05);	
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06);	
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07);	
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME);
	RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME);

	return;
}

void QRecloseAccBinarySignalDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QRecloseAccBinarySignalDlg::SetDatas(CExBaseList *pParas)
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

void QRecloseAccBinarySignalDlg::UpdateCurrentBinarys(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;
	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);
}

void QRecloseAccBinarySignalDlg::UpdateAllBinarys(CExBaseList *pAllItems)
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

BOOL QRecloseAccBinarySignalDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME
                ||pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME)
        {
            if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
            {
                m_nModify = 1;
                return TRUE;
            }

        }
        else
        {
            if (pData->m_strValue != pData_New->m_strValue)
            {
                m_nModify = 1;
                return TRUE;
            }
        }
    }
    return FALSE;
}

//确认按钮
void QRecloseAccBinarySignalDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}


//取消按钮
void QRecloseAccBinarySignalDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QRecloseAccBinarySignalDlg::on_m_cbbBinSelect_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->m_cbbInputA->setEnabled(true);
        ui->m_cbbInputB->setEnabled(true);
        ui->m_cbbInputC->setEnabled(true);
        ui->m_cbbInputD->setEnabled(true);
        ui->m_cbbInputE->setEnabled(false);
        ui->m_cbbInputF->setEnabled(false);
        ui->m_cbbInputG->setEnabled(false);
        ui->m_cbbInputH->setEnabled(false);
    }
    else
    {
        ui->m_cbbInputA->setEnabled(false);
        ui->m_cbbInputB->setEnabled(false);
        ui->m_cbbInputC->setEnabled(false);
        ui->m_cbbInputD->setEnabled(false);
        ui->m_cbbInputE->setEnabled(true);
        ui->m_cbbInputF->setEnabled(true);
        ui->m_cbbInputG->setEnabled(true);
        ui->m_cbbInputH->setEnabled(true);
    }
}

void QRecloseAccBinarySignalDlg::on_m_cbbOutputSwitchMode_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbOutputSwitchMode->GetCurrSelObject();
    if(pValue == NULL)
        return;

    if(CString_To_long(pValue->m_strIndex) == 0)
        ui->m_editOutputDelayTime->setEnabled(true);
    else
        ui->m_editOutputDelayTime->setEnabled(false);
}


void QRecloseAccBinarySignalDlg::on_m_editOutputKeepTime_editingFinished()
{
    ui->m_editOutputKeepTime->setText(RecloseAccValueCheck(ui->m_editOutputKeepTime->text(), OUTPUTKEEPTIME_MAX, OUTPUTKEEPTIME_MIN, 3));
    return;
}

void QRecloseAccBinarySignalDlg::on_m_editOutputDelayTime_editingFinished()
{
    ui->m_editOutputDelayTime->setText(RecloseAccValueCheck(ui->m_editOutputDelayTime->text(), OUTPUTDELAYTIME_MAX, OUTPUTDELAYTIME_MIN, 3));
    return;
}
