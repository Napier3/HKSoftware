#include "PowerDirCommonParasDlg.h"
#include "ui_PowerDirCommonParasDlg.h"
#include "PowerDirCommon.h"
#include "SttMultiMacroPowerDirParasDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../XLangResource_Native.h"
#include <cmath>

extern CFont *g_pSttGlobalFont;

QPowerDirCommonParasDlg::QPowerDirCommonParasDlg(QWidget *parent) :
QDialog(parent),
ui(new Ui::QPowerDirCommonParasDlg)
{
	ui->setupUi(this);
    m_nInputWidgetWidth = 150;
	InitUI();
}

QPowerDirCommonParasDlg::~QPowerDirCommonParasDlg()
{
	delete ui;
}

void QPowerDirCommonParasDlg::InitUI()
{
	this->setFont(*g_pSttGlobalFont);

	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/PowerDirection.png");
#else
    strPngPath =  ":/ctrls/images/PowerDirection.png";
#endif
    this->setWindowTitle(g_sLangTxt_Gradient_CommonParas);
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));

    ui->m_cbbAngleMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbConnectMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbIPhSet->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbUPhSet->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAngleMargin->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editIPre->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreAngle->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPrepareTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editUPre->setFixedWidth(m_nInputWidgetWidth);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PHASESET);
    ui->m_cbbUPhSet->ShowBaseList(pDataType);
    ui->m_cbbIPhSet->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PSUPDANGLEMODE);
    ui->m_cbbAngleMode->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_CONNECTTYPE);
    ui->m_cbbConnectMode->ShowBaseList(pDataType);

    ui->m_labPrepareTime->setText(g_sLangTxt_Gradient_ChangeTime);
    ui->m_labPreFaultTime->setText(g_sLangTxt_Gradient_FailBeforeTime);
    ui->m_labUPre->setText(g_sLangTxt_PowerDir_UPre);
    ui->m_labUPhSet->setText(g_sLangTxt_PowerDir_UPhSet);
    ui->m_labIPre->setText(g_sLangTxt_PowerDir_IPre);
    ui->m_labIPhSet->setText(g_sLangTxt_PowerDir_IPhSet);
    ui->m_labPreAngle->setText(g_sLangTxt_PowerDir_PreAngle);
    ui->m_labAngleMode->setText(g_sLangTxt_PowerDir_AngleMode);
    ui->m_labConnectMode->setText(g_sLangTxt_PowerDir_ConnectMode);
    ui->m_labAngleMargin->setText(g_sLangTxt_PowerDir_AngleMargin);
    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    return;
}

void QPowerDirCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREPARETIME)
	{
		ui->m_editPrepareTime->setText(PowerDirValueCheck(pData->m_strValue, PREPARETIME_MAX, PREPARETIME_MIN, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREFAULTTIME)
	{
		ui->m_editPreFaultTime->setText(PowerDirValueCheck(pData->m_strValue, PREFAULTTIME_MAX, PREFAULTTIME_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPRE)
	{
		ui->m_editUPre->setText(PowerDirValueCheck(pData->m_strValue, UPRE_MAX, UPRE_MIN,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPHSET)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PHASESET);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbUPhSet->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPRE)
	{
		ui->m_editIPre->setText(PowerDirValueCheck(pData->m_strValue, IPRE_MAX, IPRE_MIN,3));
	}
	if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPHSET)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PHASESET);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbIPhSet->SetCurrSelByName(pValue->m_strName);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREANGLE)
	{
        ui->m_editPreAngle->setText(PowerDirValueCheck(pData->m_strValue, PREANGLE_MAX, PREANGLE_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMODE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_PSUPDANGLEMODE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbAngleMode->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CONNECTMODE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_POWERDIR_PARAS_DATATYPE_ID_CONNECTTYPE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbConnectMode->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMARGIN)
	{
        ui->m_editAngleMargin->setText(PowerDirValueCheck(pData->m_strValue, ANGLEMARGIN_MAX, ANGLEMARGIN_MIN, 2));
	}

	return;
}

void QPowerDirCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREPARETIME)
	{
		pData->m_strValue = ui->m_editPrepareTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_editPreFaultTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPRE)
	{
		pData->m_strValue = ui->m_editUPre->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPHSET)
	{ 
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbUPhSet->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPRE)
	{
		pData->m_strValue = ui->m_editIPre->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPHSET)
	{ 
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbIPhSet->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREANGLE)
	{
		pData->m_strValue = ui->m_editPreAngle->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMODE)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbAngleMode->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CONNECTMODE)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbConnectMode->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMARGIN)
	{
		pData->m_strValue = ui->m_editAngleMargin->text();
	}
	return;
}

void QPowerDirCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREPARETIME);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREFAULTTIME);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPRE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPHSET);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPRE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPHSET);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_PREANGLE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMODE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_CONNECTMODE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMARGIN);

	return;
}

void QPowerDirCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QPowerDirCommonParasDlg::SetDatas(CExBaseList *pParas)
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

void QPowerDirCommonParasDlg::UpdateCurrentCommonParas(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;

	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);

	return;
}

void QPowerDirCommonParasDlg::UpdateAllCommonParas(CExBaseList *pAllItems)
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

BOOL QPowerDirCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_UPHSET
                || pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_IPHSET
                || pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ANGLEMODE
                || pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_CONNECTMODE)
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

void QPowerDirCommonParasDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}

void QPowerDirCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QPowerDirCommonParasDlg::on_m_editPrepareTime_editingFinished()
{
	ui->m_editPrepareTime->setText(PowerDirValueCheck(ui->m_editPrepareTime->text(),PREPARETIME_MAX, PREPARETIME_MIN, 3));
    return;
}

void QPowerDirCommonParasDlg::on_m_editPreFaultTime_editingFinished()
{
    ui->m_editPreFaultTime->setText(PowerDirValueCheck(ui->m_editPreFaultTime->text(),PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
    return;
}

void QPowerDirCommonParasDlg::on_m_editUPre_editingFinished()
{
    ui->m_editUPre->setText(PowerDirValueCheck(ui->m_editUPre->text(),UPRE_MAX, UPRE_MIN, 3));
    return;
}

void QPowerDirCommonParasDlg::on_m_editIPre_editingFinished()
{
    ui->m_editIPre->setText(PowerDirValueCheck(ui->m_editIPre->text(),IPRE_MAX, IPRE_MIN, 3));
    return;
}

void QPowerDirCommonParasDlg::on_m_editPreAngle_editingFinished()
{
    ui->m_editPreAngle->setText(PowerDirValueCheck(ui->m_editPreAngle->text(),PREANGLE_MAX, PREANGLE_MIN, 2));
    return;
}

void QPowerDirCommonParasDlg::on_m_editAngleMargin_editingFinished()
{
    ui->m_editAngleMargin->setText(PowerDirValueCheck(ui->m_editAngleMargin->text(),PREANGLE_MAX, PREANGLE_MIN, 2));
    return;
}
