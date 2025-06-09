#include "ActionTimeItemParaEditWidget.h"
#include "ui_ActionTimeItemParaEditWidget.h"
#include "ActionTimeCommon.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"

extern CFont *g_pSttGlobalFont;

QActionTimeItemParaEditWidget::QActionTimeItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    ui(new Ui::QActionTimeItemParaEditWidget)
{   
    ui->setupUi(this);
	m_pCurrMacroTest_External = NULL;
    m_nInputWidgetWidth = 250;
    InitUI();
}

QActionTimeItemParaEditWidget::~QActionTimeItemParaEditWidget()
{
    delete ui;
}

void QActionTimeItemParaEditWidget::InitUI()
{
	this->setFont(*g_pSttGlobalFont);
    ui->m_cbbFaultType->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbFaultVolType->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultCurrent->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editSettingTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreAngle->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreFre->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editRelErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErr1->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErr2->setFixedWidth(m_nInputWidgetWidth);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_ACTIONTIME_PARAS_DATATYPE_ID_FAULTTYPE);
    ui->m_cbbFaultType->ShowBaseList(pDataType);

    ui->m_labFaultType->setText(g_sLangTxt_State_FaultType);
    ui->m_labFaultVolType->setText(g_sLangTxt_ActionTime_FaultVolType);
    ui->m_labSettingTime->setText(g_sLangTxt_ActionTime_SettingTime);
    ui->m_labFaultVol->setText(g_sLangTxt_ActionTime_FaultVol);
    ui->m_labFaultCur->setText(g_sLangTxt_Swing_SCurrent);
    ui->m_labFaultAngle->setText(g_sLangTxt_ActionTime_FaultAngle);
    ui->m_labFaultFre->setText(g_sLangTxt_ActionTime_FaultFre);
    ui->m_labRelErr->setText(g_sLangTxt_ActionTime_RelErr);
    ui->m_labAbsErrPos->setText(g_sLangTxt_ActionTime_AbsErrPos);
    ui->m_labAbsErrNeg->setText(g_sLangTxt_ActionTime_AbsErrNeg);

    ui->m_cbbFaultVolType->addItem(g_sLangTxt_ActionTime_ShortVol);
    ui->m_cbbFaultVolType->addItem(g_sLangTxt_ActionTime_ZeroVol);
    ui->m_cbbFaultVolType->addItem(g_sLangTxt_ActionTime_NegVol);
}

void QActionTimeItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTYPE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_ACTIONTIME_PARAS_DATATYPE_ID_FAULTTYPE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbFaultType->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLTYPE)
	{
		bool bOk = false;
		int index = pData->m_strValue.toInt(&bOk);	
		if(!bOk)
			index = pData->m_strValue.toFloat(&bOk);
		//零序电压是3
		if(index == 3)
			ui->m_cbbFaultVolType->setCurrentIndex(1);
		else
			ui->m_cbbFaultVolType->setCurrentIndex(index);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_SETTINGTIME)
	{
        //ui->m_editSettingTime->setText(ActTimeValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
        ui->m_editSettingTime->UpdateObjectText(pData, ActTimeValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3), 3);
	}
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLT)
    {
        ui->m_editFaultVolt->setText(ActTimeValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTCURRENT)
	{
		ui->m_editFaultCurrent->setText(ActTimeValueCheck(pData->m_strValue, FAULTCUR_MAX, FAULTCUR_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTANGLE)
	{
        ui->m_editPreAngle->setText(ActTimeValueCheck(pData->m_strValue, FAULTANGLE_MAX, FAULTANGLE_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTFRE)
	{
		ui->m_editPreFre->setText(ActTimeValueCheck(pData->m_strValue, FAULTFRE_MAX, FAULTFRE_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_RELERR)
	{
		ui->m_editRelErr->setText(ActTimeValueCheck(pData->m_strValue, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_NEG)
	{
		ui->m_editAbsErr1->setText(ActTimeValueCheck(pData->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_POS)
	{
		ui->m_editAbsErr2->setText(ActTimeValueCheck(pData->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	}

	return;
}

void QActionTimeItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTYPE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLTYPE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_SETTINGTIME);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLT);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTCURRENT);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTANGLE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTFRE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_RELERR);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_POS);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_NEG);
}

void QActionTimeItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{
	QItemParaEditWidgetBase::UpdateParas(pSttMacroTest);

	if(m_pCurrMacroTest_External != NULL)
	{
		CSttMacroTestParaDatas *pDstDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
		CheckAllPresence(pDstDatas_External);
	}

	CSttMacroTestParaDatas *pDstDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CheckAllPresence(pDstDatas);
	POS pos = pDstDatas->GetHeadPosition();
	while (pos!= NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->GetNext(pos);
		SetValueToPage(pData);
	}
	
	return;
}

void QActionTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
{
	if (m_pSingleMacroRef == NULL)
	{
		return;
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);

	if(m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	}

	if(pDataInner != NULL)
	{
		pDataInner->m_strValue = strValue;
		if(pSttMacroTestParaDatas_External != NULL)
		{
			pSttMacroTestParaDatas_External->SetDataValue(strID,strValue,TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
	}

	return;
}

CExBaseList* QActionTimeItemParaEditWidget::GetMacroTestParaDatas()
{
	if(NULL == m_pCurrMacroTest_External)
		return NULL;

	return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE, "");
}

CExBaseList* QActionTimeItemParaEditWidget::GetInnerMacroTestParaDatas()
{
	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
}

void QActionTimeItemParaEditWidget::DelMacroTestParaDatas()
{

}

void QActionTimeItemParaEditWidget::on_m_editSettingTime_editingFinished()
{
//    if(ui->m_editSettingTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editSettingTime)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_SETTINGTIME, ui->m_editSettingTime))
    {
        return;
    }

    ui->m_editSettingTime->setText(ActTimeValueCheck(ui->m_editSettingTime->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_SETTINGTIME,ui->m_editSettingTime->text());
}

void QActionTimeItemParaEditWidget::on_m_editFaultCurrent_editingFinished()
{
    ui->m_editFaultCurrent->setText(ActTimeValueCheck(ui->m_editFaultCurrent->text(), FAULTCUR_MAX, FAULTCUR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTCURRENT,ui->m_editFaultCurrent->text());
}

void QActionTimeItemParaEditWidget::on_m_editPreAngle_editingFinished()
{
    ui->m_editPreAngle->setText(ActTimeValueCheck(ui->m_editPreAngle->text(), FAULTANGLE_MAX, FAULTANGLE_MIN, 2));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTANGLE,ui->m_editPreAngle->text());
}

void QActionTimeItemParaEditWidget::on_m_editPreFre_editingFinished()
{
    ui->m_editPreFre->setText(ActTimeValueCheck(ui->m_editPreFre->text(), FAULTFRE_MAX, FAULTFRE_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTFRE,ui->m_editPreFre->text());
}

void QActionTimeItemParaEditWidget::on_m_editRelErr_editingFinished()
{
    ui->m_editRelErr->setText(ActTimeValueCheck(ui->m_editRelErr->text(), TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_RELERR,ui->m_editRelErr->text());
}

void QActionTimeItemParaEditWidget::on_m_editAbsErr1_editingFinished()
{
    ui->m_editAbsErr1->setText(ActTimeValueCheck(ui->m_editAbsErr1->text(), TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_POS,ui->m_editAbsErr1->text());
}

void QActionTimeItemParaEditWidget::on_m_editAbsErr2_editingFinished()
{
    ui->m_editAbsErr2->setText(ActTimeValueCheck(ui->m_editAbsErr2->text(), TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_TTRIP_ABSERR_NEG,ui->m_editAbsErr2->text());
}

void QActionTimeItemParaEditWidget::on_m_cbbFaultType_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultType->GetCurrSelObject();
    if(pValue != NULL)
        UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTYPE, pValue->m_strIndex);
}

void QActionTimeItemParaEditWidget::on_m_cbbFaultVolType_currentIndexChanged(int index)
{
	CString strIndex;
	if(index == 1)
		strIndex.setNum(3);
	else
		strIndex.setNum(index);
	UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLTYPE, strIndex);
}

void QActionTimeItemParaEditWidget::on_m_editFaultVolt_editingFinished()
{
    ui->m_editFaultVolt->setText(ActTimeValueCheck(ui->m_editFaultVolt->text(), FAULTVOL_MAX, FAULTVOL_MIN, 3));
    UpdatePara(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTVOLT,ui->m_editFaultVolt->text());
}
