#include "DistanceSearchItemParaEditWidget.h"
#include "ui_DistanceSearchItemParaEditWidget.h"
#include "DistanceSearchCommon.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"

extern CFont *g_pSttGlobalFont;

QDistanceSearchItemParaEditWidget::QDistanceSearchItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    ui(new Ui::QDistanceSearchItemParaEditWidget)
{
    ui->setupUi(this);
	m_pCurrMacroTest_External = NULL;
    m_nInputWidgetWidth = 250;
    m_dBegZ = 0;
    m_dBegZAng = 0;
    m_dEndZ = 0;
    m_dEndZAng = 0;
    m_nFaultType = 0;
    m_nZoneType = 0;

    InitUI();
    ConnectAll_SigSlot();
}

QDistanceSearchItemParaEditWidget::~QDistanceSearchItemParaEditWidget()
{
    delete ui;
}

void QDistanceSearchItemParaEditWidget::InitUI()
{
	this->setFont(*g_pSttGlobalFont);

    ui->m_cbbFaultType->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbZoneType->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editBeginVal->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editBeginValAng->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editEndVal->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editEndValAng->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultIf->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultVf->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editRelErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editStep->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editTSetting->setFixedWidth(m_nInputWidgetWidth);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_SYSTEMFAULT);
    ui->m_cbbFaultType->ShowBaseList(pDataType);

    ui->m_labFaultType->setText(g_sLangTxt_Swing_FaultType);
    ui->m_labZoneType->setText(g_sLangTxt_DistanceSearch_ZoneType);
    ui->m_labBegZ->setText(g_sLangTxt_DistanceSearch_BeginZ);
    ui->m_labBegZAng->setText(g_sLangTxt_DistanceSearch_BeginZAngle);
    ui->m_labEndZ->setText(g_sLangTxt_DistanceSearch_EndZ);
    ui->m_labEndZAng->setText(g_sLangTxt_DistanceSearch_EndZAngle);
    ui->m_labStep->setText(g_sLangTxt_DistanceSearch_Step);
    ui->m_labFaultCur->setText(g_sLangTxt_State_ShortI);
    ui->m_labFaultVol->setText(g_sLangTxt_State_ShortU);
    ui->m_labTSetting->setText(g_sLangTxt_DistanceSearch_TSetting);
    ui->m_labAbsErr->setText(g_sLangTxt_DistanceSearch_AbsErr);
    ui->m_labRelErr->setText(g_sLangTxt_ActionTime_RelErr);

}

void QDistanceSearchItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_SYSTEMFAULT);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbFaultType->SetCurrSelByName(pValue->m_strName);

        UpdZoneTypeCmbParas(pData,CString_To_long(pData->m_strValue));
        m_nFaultType = CString_To_long(pData->m_strValue);
	}
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE)
	{
//        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone);
//        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(pData->m_strValue.toInt());
//        if(pValue != NULL)
//            ui->m_cbbZoneType->SetCurrSelByName(pValue->m_strName);

//        if(ui->m_cbbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine)
//        {
//            ui->m_editTSetting->setEnabled(true);
//            ui->m_editAbsErr->setEnabled(true);
//            ui->m_editRelErr->setEnabled(true);
//        }
//        else
//        {
//            ui->m_editTSetting->setEnabled(false);
//            ui->m_editAbsErr->setEnabled(false);
//            ui->m_editRelErr->setEnabled(false);
//        }
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_STEP)
	{
        ui->m_editStep->setText(DistanceSearchValueCheck(pData->m_strValue, STEP_MAX, STEP_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTIF)
	{
		ui->m_editFaultIf->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTIF_MAX, FAULTIF_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL)
	{
        ui->m_editBeginVal->setText(DistanceSearchValueCheck(pData->m_strValue, BEGINVAL_MAX, BEGINVAL_MIN, 3));
        m_dBegZ = ui->m_editBeginVal->text().toDouble();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTVF)
	{
		ui->m_editFaultVf->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTVF_MAX, FAULTVF_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG)
	{
        ui->m_editBeginValAng->setText(DistanceSearchValueCheck(pData->m_strValue, BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
        m_dBegZAng = ui->m_editBeginValAng->text().toDouble();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING)
	{
        ui->m_editTSetting->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL)
	{
        ui->m_editEndVal->setText(DistanceSearchValueCheck(pData->m_strValue, ENDVAL_MAX, ENDVAL_MIN, 3));
        m_dEndZ = ui->m_editEndVal->text().toDouble();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG)
	{
        ui->m_editEndValAng->setText(DistanceSearchValueCheck(pData->m_strValue, ENDVALANG_MAX, ENDVALANG_MIN, 2));
        m_dEndZAng = ui->m_editEndValAng->text().toDouble();
    }
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR)
	{
        ui->m_editAbsErr->setText(DistanceSearchValueCheck(pData->m_strValue, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR)
	{
		ui->m_editRelErr->setText(DistanceSearchValueCheck(pData->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	}

	return;
}

void QDistanceSearchItemParaEditWidget::SetValueToPageFromCharact(CSttMacroTestParaData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING)
    {
        ui->m_editTSetting->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR)
    {
        ui->m_editAbsErr->setText(DistanceSearchValueCheck(pData->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR)
    {
        ui->m_editRelErr->setText(DistanceSearchValueCheck(pData->m_strValue, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
    }

    return;
}

void QDistanceSearchItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_STEP);
	//区段
    DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTIF);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTVF);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
    DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_VALSETTING);
    DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_VALSETTINGANG);
}

void QDistanceSearchItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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
	
    UpdateValueSetting();

	return;
}

void QDistanceSearchItemParaEditWidget::UpdateCharactParas(CSttMacroTest *pSttMacroTest)
{
    QItemParaEditWidgetBase::UpdateParas(pSttMacroTest);

    if(m_pSingleMacroRef == NULL)
        return;

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
        SetValueToPageFromCharact(pData);
    }

    return;
}

void QDistanceSearchItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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
            pSttMacroTestParaDatas_External->SetDataValue(strID, pDataInner->m_strValue, TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
	}

	return;
}

void QDistanceSearchItemParaEditWidget::ConnectAll_SigSlot()
{
    connect(ui->m_cbbZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cbbZoneType_currentIndexChanged(int)));
}

void QDistanceSearchItemParaEditWidget::DisConnectAll_SigSlot()
{
    disconnect(ui->m_cbbZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_m_cbbZoneType_currentIndexChanged(int)));
}

void QDistanceSearchItemParaEditWidget::UpdateValueSetting()
{
    if(m_dBegZ == 0 && m_dBegZAng == 0 && m_dEndZ == 0 && m_dEndZAng == 0)
        return;

    if(m_nZoneType == 0)  //线路长度
    {
        CExBaseList* pInnerMacroTest = GetInnerMacroTestParaDatas();
        CSttMacroTestParaData *pZData = (CSttMacroTestParaData*)pInnerMacroTest->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZL);
        CSttMacroTestParaData *pZAngData = (CSttMacroTestParaData*)pInnerMacroTest->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE);

        if(pZData == NULL || pZAngData == NULL)
            return;

        UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_VALSETTING, pZData->m_strValue);
        UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_VALSETTINGANG, pZAngData->m_strValue);

        return;
    }

    double dValSetting = 0, dValSettingAng = 0;
    BOOL bExist = CalDistanceSearchValSetting(m_nFaultType, m_nZoneType, m_dBegZ, m_dBegZAng,
                                m_dEndZ, m_dEndZAng, dValSetting, dValSettingAng);
    if(bExist)
    {
        CString strValue;
        strValue.setNum(dValSetting);
        UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_VALSETTING, strValue);
        strValue.setNum(dValSettingAng);
        UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_VALSETTINGANG, strValue);
    }
}

CExBaseList* QDistanceSearchItemParaEditWidget::GetMacroTestParaDatas()
{
	if(NULL == m_pCurrMacroTest_External)
		return NULL;

	return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE, "");
}

CExBaseList* QDistanceSearchItemParaEditWidget::GetInnerMacroTestParaDatas()
{
	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
}

void QDistanceSearchItemParaEditWidget::DelMacroTestParaDatas()
{

}

//据故障类型值得到最新区段显示下拉框数据
void QDistanceSearchItemParaEditWidget::UpdZoneTypeCmbParas(CSttMacroTestParaData *pData,int nFaultType)
{
    CString strFaultType;
    strFaultType = Global_GetCharFaultTypeStringByFaultType(nFaultType);//20240906 luozibing 使用新增全局函数

    CString strTypeId = STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone;
    strTypeId += "_";
    strTypeId += strFaultType;
    CDataType *pDataType = (CDataType *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(strTypeId);
    if (pDataType == NULL)
    {
        return;
    }

    CString strZoneValue;
    CExBaseList *pParas = (CExBaseList *)pData->GetParent();
    CSttMacroTestParaData *pDataZone = (CSttMacroTestParaData *)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
    CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByID(pDataZone->m_strValue);

    if (pValue == NULL)
    {
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(0);//未找到对应区段设置为线路长度
        if (pValue != NULL)
        {
            pDataZone->m_strValue = pValue->m_strID;
            UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE, pDataZone->m_strValue);
        }
    }
    strZoneValue = pDataZone->m_strValue;
    DisConnectAll_SigSlot();
    ui->m_cbbZoneType->SetBaseList(pDataType);
    ConnectAll_SigSlot();
    if (pValue != NULL)
    {
        ui->m_cbbZoneType->SetSelByID(strZoneValue);
        if(ui->m_cbbZoneType->currentIndex() == 0)
        {
            slot_m_cbbZoneType_currentIndexChanged(0);
        }
    }

}

void QDistanceSearchItemParaEditWidget::on_m_cbbFaultType_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultType->GetCurrSelObject();
    if(pValue == NULL)
    {
        return;
    }

    UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE, pValue->m_strIndex);
    m_nFaultType = CString_To_long(pValue->m_strIndex);
    UpdateValueSetting();

    //故障类型修改同步区段下拉框内容修改
    if (m_pSingleMacroRef == NULL)
    {
        return;
    }
    CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
    if (pSttMacroTestParaDatas_Inner == NULL)
    {
        return;
    }
    CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
    UpdZoneTypeCmbParas(pDataInner, CString_To_long(pDataInner->m_strValue));	
}

void QDistanceSearchItemParaEditWidget::on_m_editStep_editingFinished()
{
	ui->m_editStep->setText(DistanceSearchValueCheck(ui->m_editStep->text(), STEP_MAX, STEP_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_STEP,ui->m_editStep->text());
}

void QDistanceSearchItemParaEditWidget::slot_m_cbbZoneType_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbZoneType->GetCurrSelObject();
    if(pValue != NULL)
    {
        UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE, pValue->m_strIndex);
        m_nZoneType = CString_To_long(pValue->m_strIndex);
    }

    if(ui->m_cbbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine)
    {
        ui->m_editTSetting->setEnabled(true);
        ui->m_editAbsErr->setEnabled(true);
        ui->m_editRelErr->setEnabled(true);
    }
    else
    {
        ui->m_editTSetting->setEnabled(false);
        ui->m_editAbsErr->setEnabled(false);
        ui->m_editRelErr->setEnabled(false);

        if(m_pCurrMacroTest_External == NULL)
            UpdateCharactParas(&m_oSttMacroTest_Inner);
        else
            UpdateCharactParas(m_pCurrMacroTest_External);
    }
    UpdateValueSetting();
}

void QDistanceSearchItemParaEditWidget::on_m_editFaultIf_editingFinished()
{
	ui->m_editFaultIf->setText(DistanceSearchValueCheck(ui->m_editFaultIf->text(), FAULTIF_MAX, FAULTIF_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTIF,ui->m_editFaultIf->text());
}

void QDistanceSearchItemParaEditWidget::on_m_editBeginVal_editingFinished()
{
	ui->m_editBeginVal->setText(DistanceSearchValueCheck(ui->m_editBeginVal->text(), BEGINVAL_MAX, BEGINVAL_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL,ui->m_editBeginVal->text());
    m_dBegZ = ui->m_editBeginVal->text().toDouble();
    UpdateValueSetting();
}

void QDistanceSearchItemParaEditWidget::on_m_editFaultVf_editingFinished()
{
	ui->m_editFaultVf->setText(DistanceSearchValueCheck(ui->m_editFaultVf->text(), FAULTVF_MAX, FAULTVF_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTVF,ui->m_editFaultVf->text());
}

void QDistanceSearchItemParaEditWidget::on_m_editBeginValAng_editingFinished()
{
	ui->m_editBeginValAng->setText(DistanceSearchValueCheck(ui->m_editBeginValAng->text(), BEGINVALANG_MAX, BEGINVALANG_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG,ui->m_editBeginValAng->text());
    m_dBegZAng = ui->m_editBeginValAng->text().toDouble();
    UpdateValueSetting();
}

void QDistanceSearchItemParaEditWidget::on_m_editTSetting_editingFinished()
{
    ui->m_editTSetting->setText(DistanceSearchValueCheck(ui->m_editTSetting->text(), FAULTTIME_MAX, FAULTTIME_MIN, 3));
    UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING,ui->m_editTSetting->text());
}

void QDistanceSearchItemParaEditWidget::on_m_editEndVal_editingFinished()
{
	ui->m_editEndVal->setText(DistanceSearchValueCheck(ui->m_editEndVal->text(), ENDVAL_MAX, ENDVAL_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL,ui->m_editEndVal->text());
    m_dEndZ = ui->m_editEndVal->text().toDouble();
    UpdateValueSetting();
}

void QDistanceSearchItemParaEditWidget::on_m_editEndValAng_editingFinished()
{
	ui->m_editEndValAng->setText(DistanceSearchValueCheck(ui->m_editEndValAng->text(), ENDVALANG_MAX, ENDVALANG_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG,ui->m_editEndValAng->text());
    m_dEndZAng = ui->m_editEndValAng->text().toDouble();
    UpdateValueSetting();
}

void QDistanceSearchItemParaEditWidget::on_m_editAbsErr_editingFinished()
{
	ui->m_editAbsErr->setText(DistanceSearchValueCheck(ui->m_editAbsErr->text(), TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR,ui->m_editAbsErr->text());
}

void QDistanceSearchItemParaEditWidget::on_m_editRelErr_editingFinished()
{
	ui->m_editRelErr->setText(DistanceSearchValueCheck(ui->m_editRelErr->text(), TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR,ui->m_editRelErr->text());
}
