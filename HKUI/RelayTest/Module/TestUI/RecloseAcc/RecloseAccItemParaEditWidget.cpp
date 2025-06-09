#include "RecloseAccItemParaEditWidget.h"
#include "ui_RecloseAccItemParaEditWidget.h"
#include "RecloseAccCommon.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../XLangResource_Native.h"
#include <math.h>
#include <qmath.h>

extern CFont *g_pSttGlobalFont;

QRecloseAccItemParaEditWidget::QRecloseAccItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    ui(new Ui::QRecloseAccItemParaEditWidget)
{
    ui->setupUi(this);
	m_pCurrMacroTest_External = NULL;
    m_nInputWidgetWidth = 200;
    InitUI();
}

QRecloseAccItemParaEditWidget::~QRecloseAccItemParaEditWidget()
{
    delete ui;
}

void QRecloseAccItemParaEditWidget::InitUI()
{
	this->setFont(*g_pSttGlobalFont);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_SYSTEMFAULT);
    ui->m_cbbFaultType->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_FAULTCHARACTER);
    ui->m_cbbFaultPermanent->ShowBaseList(pDataType);
    pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_UXMODE);
    ui->m_cbbUxMode->ShowBaseList(pDataType);

    ui->m_cbbFaultPermanent->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbFaultType->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbK0Mode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbUxMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAngKx->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFre->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editISet->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editKlKr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editR->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editRecloseTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editRelErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editTripTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editUxInputAng->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editUxInputFre->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editUxInputMag->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editX->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editZ->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editZAngle->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErr1->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErr2->setFixedWidth(m_nInputWidgetWidth);

    ui->m_labFaultType->setText(g_sLangTxt_Swing_FaultType);
    ui->m_labZ->setText(g_sLangTxt_RecloseAcc_Z);
    ui->m_labZAngle->setText(g_sLangTxt_Gradient_ImpAngle);
    ui->m_labR->setText(g_sLangTxt_RecloseAcc_R);
    ui->m_labX->setText(g_sLangTxt_RecloseAcc_X);
    ui->m_labISet->setText(g_sLangTxt_State_ShortI);
    ui->m_labFre->setText(g_sLangTxt_RecloseAcc_Fre);
    ui->m_labK0Mode->setText(g_sLangTxt_DistanceSearch_K0Mode);
    ui->m_labTripTime->setText(g_sLangTxt_Manual_ActionTime);
    ui->m_labRecloseTime->setText(g_sLangTxt_RecloseAcc_RecloseTime);
    ui->m_labFaultPermanent->setText(g_sLangTxt_Native_FaultProp);
    ui->m_labUxMode->setText(g_sLangTxt_RecloseAcc_UxMode);
    ui->m_labUxInputFre->setText(g_sLangTxt_RecloseAcc_UxInputFre);
    ui->m_labUxInputMag->setText(g_sLangTxt_RecloseAcc_UxInputMag);
    ui->m_labUxInputAng->setText(g_sLangTxt_RecloseAcc_UxInputAng);
    ui->m_labAbsErr1->setText(g_sLangTxt_ActionTime_AbsErrPos);
    ui->m_labAbsErr2->setText(g_sLangTxt_ActionTime_AbsErrNeg);
    ui->m_labRelErr->setText(g_sLangTxt_ActionTime_RelErr);

    return;
}

void QRecloseAccItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	static float fZ, fZPhi;
	static BOOL bZflag = false;
	static BOOL bPhiflag = false;

	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE1)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_SYSTEMFAULT);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbFaultType->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1)
	{
        ui->m_editZ->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, Z1_MAX, Z1_MIN, 3), 3);
        //ui->m_editZ->setText(RecloseAccValueCheck(pData->m_strValue, Z1_MAX, Z1_MIN, 3));
		fZ = pData->m_strValue.toFloat();
		bZflag = true;

        m_dZ = ui->m_editZ->text().toDouble();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH)
	{
        ui->m_editZAngle->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, Z1PH_MAX, Z1PH_MIN, 2), 2);
        //ui->m_editZAngle->setText(RecloseAccValueCheck(pData->m_strValue, Z1PH_MAX, Z1PH_MIN, 3));
		fZPhi = pData->m_strValue.toFloat();
		bPhiflag = true;

        m_dZAng = ui->m_editZAngle->text().toDouble();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET1)
	{
		ui->m_editISet->setText(RecloseAccValueCheck(pData->m_strValue, ISET1_MAX, ISET1_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE)
	{
		ui->m_editFre->setText(RecloseAccValueCheck(pData->m_strValue, FRE_MAX, FRE_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_K0MODE)
	{
		bool bOk = false;
		int index = pData->m_strValue.toInt(&bOk);	
		if(!bOk)
			index = pData->m_strValue.toFloat(&bOk);

		ui->m_cbbK0Mode->setCurrentIndex(index);
        switch(index)
        {
        case 0:
            {
                ui->m_labKlKr->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_K0);
                ui->m_labAngKx->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_PHI_K0);
                break;
            }
        case 1:
            {
                ui->m_labKlKr->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_RERL);
                ui->m_labAngKx->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_XEXL);
                break;
            }
        case 2:
            {
                ui->m_labKlKr->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_Z0Z1);
                ui->m_labAngKx->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_PHI_Z0Z1);
                break;
            }
        default:
            break;
        }
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_KLKR)
	{
        ui->m_editKlKr->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, KLKR_MAX, KLKR_MIN, 3), 3);
        //ui->m_editKlKr->setText(RecloseAccValueCheck(pData->m_strValue, KLKR_MAX, KLKR_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ANGKX)
	{
        ui->m_editAngKx->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, ANGKX_MAX, ANGKX_MIN, 2), 2);
        //ui->m_editAngKx->setText(RecloseAccValueCheck(pData->m_strValue, ANGKX_MAX, ANGKX_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET1)
	{
        ui->m_editTripTime->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, TSET1_MAX, TSET1_MIN, 3), 3);
        //ui->m_editTripTime->setText(RecloseAccValueCheck(pData->m_strValue, TSET1_MAX, TSET1_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RECLOSEACCTIME)
	{
        ui->m_editRecloseTime->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, RECLOSEACCTIME_MAX, RECLOSEACCTIME_MIN, 3), 3);
        //ui->m_editRecloseTime->setText(RecloseAccValueCheck(pData->m_strValue, RECLOSEACCTIME_MAX, RECLOSEACCTIME_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTPERMANENT)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_FAULTCHARACTER);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbFaultPermanent->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXMODE)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_UXMODE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbUxMode->SetCurrSelByName(pValue->m_strName);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTFRE)
	{
        ui->m_editUxInputFre->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, UXINPUTFRE_MAX, UXINPUTFRE_MIN, 3), 3);
        //ui->m_editUxInputFre->setText(RecloseAccValueCheck(pData->m_strValue, UXINPUTFRE_MAX, UXINPUTFRE_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTMAG)
	{
        ui->m_editUxInputMag->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, UXINPUTMAG_MAX, UXINPUTMAG_MIN, 3), 3);
        //ui->m_editUxInputMag->setText(RecloseAccValueCheck(pData->m_strValue, UXINPUTMAG_MAX, UXINPUTMAG_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTANG)
	{
        ui->m_editUxInputAng->UpdateObjectText(pData, RecloseAccValueCheck(pData->m_strValue, UXINPUTANG_MAX, UXINPUTANG_MIN, 2), 2);
        //ui->m_editUxInputAng->setText(RecloseAccValueCheck(pData->m_strValue, UXINPUTANG_MAX, UXINPUTANG_MIN, 2));
	}
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_RELERR)
	{
		ui->m_editRelErr->setText(RecloseAccValueCheck(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, 3));
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RELERR,ui->m_editRelErr->text());
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_RELERR,ui->m_editRelErr->text());
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_RELERR,ui->m_editRelErr->text());
	}
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_POS)
	{
        ui->m_editAbsErr1->setText(RecloseAccValueCheck(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 3));
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_POS,ui->m_editAbsErr1->text());
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_POS,ui->m_editAbsErr1->text());
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ABSERR_POS,ui->m_editAbsErr1->text());
	}
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_NEG)
	{
		ui->m_editAbsErr2->setText(RecloseAccValueCheck(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 3));
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_NEG,ui->m_editAbsErr2->text());
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_NEG,ui->m_editAbsErr2->text());
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ABSERR_NEG,ui->m_editAbsErr2->text());
	}
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ERRTYPE)
    {
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ERRTYPE, pData->m_strValue);
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ERRTYPE, pData->m_strValue);
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ERRTYPE, pData->m_strValue);
    }

	if(bZflag && bPhiflag)
	{
		CString strR, strX;
		strR.setNum(fZ*cos(fZPhi * M_PI / 180.0));
		strX.setNum(fZ*sin(fZPhi * M_PI / 180.0));
        ui->m_editR->setText(RecloseAccValueCheck(strR, R1_MAX, R1_MIN, 3));
        ui->m_editX->setText(RecloseAccValueCheck(strX, X1_MAX, X1_MIN, 3));

        m_dR = ui->m_editR->text().toDouble();
        m_dX = ui->m_editX->text().toDouble();
	}

	return;
}

void QRecloseAccItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE1);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET1);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE2);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2PH);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET2);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_K0MODE);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_KLKR);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ANGKX);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET1);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET2);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RECLOSEACCTIME);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTPERMANENT);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXMODE);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTFRE);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTMAG);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTANG);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RELERR);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_POS);
	RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_NEG);
    RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ERRTYPE);
}

void QRecloseAccItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QRecloseAccItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList* QRecloseAccItemParaEditWidget::GetMacroTestParaDatas()
{
	if(NULL == m_pCurrMacroTest_External)
		return NULL;

	return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE, "");
}

CExBaseList* QRecloseAccItemParaEditWidget::GetInnerMacroTestParaDatas()
{
	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
}

void QRecloseAccItemParaEditWidget::DelMacroTestParaDatas()
{
	
}

void QRecloseAccItemParaEditWidget::on_m_cbbFaultType_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultType->GetCurrSelObject();
    if(pValue != NULL)
    {
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE1, pValue->m_strIndex);
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE2, pValue->m_strIndex);
    }
}

void QRecloseAccItemParaEditWidget::on_m_editZ_editingFinished()
{
//    if(ui->m_editZ->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editZ)->IsSetting())
//        {
//            return;
//        }
//    }
    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1, ui->m_editZ))
    {
        return;
    }

    ui->m_editZ->setText(RecloseAccValueCheck(ui->m_editZ->text(), Z1_MAX, Z1_MIN, 3));
    if(fabs(ui->m_editZ->text().toDouble() - m_dZ) < 0.001)
        return;

	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1,ui->m_editZ->text());
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2,ui->m_editZ->text());

	CString strR, strX;
	float fZ = ui->m_editZ->text().toFloat();
	float fZPhi = ui->m_editZAngle->text().toFloat();

	strR.setNum(fZ*cos(fZPhi * M_PI / 180.0));
	strX.setNum(fZ*sin(fZPhi * M_PI / 180.0));
    ui->m_editR->setText(RecloseAccValueCheck(strR, R1_MAX, R1_MIN, 3));
    ui->m_editX->setText(RecloseAccValueCheck(strX, X1_MAX, X1_MIN, 3));

    m_dZ = ui->m_editZ->text().toDouble();
    m_dR = ui->m_editR->text().toDouble();
    m_dX = ui->m_editX->text().toDouble();

}

void QRecloseAccItemParaEditWidget::on_m_editZAngle_editingFinished()
{
//    if(ui->m_editZAngle->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editZAngle)->IsSetting())
//        {
//            return;
//        }
//    }
    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH, ui->m_editZAngle))
    {
        return;
    }

    ui->m_editZAngle->setText(RecloseAccValueCheck(ui->m_editZAngle->text(), Z1PH_MAX, Z1PH_MIN, 2));
    if(fabs(ui->m_editZAngle->text().toDouble() - m_dZAng) < 0.01)
        return;

	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH,ui->m_editZAngle->text());
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2PH,ui->m_editZAngle->text());

	CString strR, strX;
	float fZ = ui->m_editZ->text().toFloat();
	float fZPhi = ui->m_editZAngle->text().toFloat();

	strR.setNum(fZ*cos(fZPhi * M_PI / 180.0));
	strX.setNum(fZ*sin(fZPhi * M_PI / 180.0));
    ui->m_editR->setText(RecloseAccValueCheck(strR, R1_MAX, R1_MIN, 3));
    ui->m_editX->setText(RecloseAccValueCheck(strX, X1_MAX, X1_MIN, 3));

    m_dZAng = ui->m_editZAngle->text().toDouble();
    m_dR = ui->m_editR->text().toDouble();
    m_dX = ui->m_editX->text().toDouble();
}

void QRecloseAccItemParaEditWidget::on_m_editISet_editingFinished()
{
	ui->m_editISet->setText(RecloseAccValueCheck(ui->m_editISet->text(), ISET1_MAX, ISET1_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET1,ui->m_editISet->text());
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ISET2,ui->m_editISet->text());
}

void QRecloseAccItemParaEditWidget::on_m_editFre_editingFinished()
{
	ui->m_editFre->setText(RecloseAccValueCheck(ui->m_editFre->text(), FRE_MAX, FRE_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE,ui->m_editFre->text());
}

void QRecloseAccItemParaEditWidget::on_m_cbbK0Mode_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        {
            ui->m_labKlKr->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_K0);
            ui->m_labAngKx->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_PHI_K0);
            break;
        }
    case 1:
        {
            ui->m_labKlKr->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_RERL);
            ui->m_labAngKx->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_XEXL);
            break;
        }
    case 2:
        {
            ui->m_labKlKr->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_Z0Z1);
            ui->m_labAngKx->setText(STT_MULTI_MACRO_RECLOSEACC_PARAS_LAB_PHI_Z0Z1);
            break;
        }
    default:
        break;
    }

	CString strIndex;
	strIndex.setNum(index);  
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_K0MODE, strIndex);
}

void QRecloseAccItemParaEditWidget::on_m_editKlKr_editingFinished()
{
//    if(ui->m_editKlKr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editKlKr)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_KLKR, ui->m_editKlKr))
    {
        return;
    }

	ui->m_editKlKr->setText(RecloseAccValueCheck(ui->m_editKlKr->text(), Z1PH_MAX, Z1PH_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_KLKR,ui->m_editKlKr->text());
}

void QRecloseAccItemParaEditWidget::on_m_editAngKx_editingFinished()
{
//    if(ui->m_editAngKx->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editAngKx)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ANGKX, ui->m_editAngKx))
    {
        return;
    }

	ui->m_editAngKx->setText(RecloseAccValueCheck(ui->m_editAngKx->text(), KLKR_MAX, KLKR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ANGKX,ui->m_editAngKx->text());
}

void QRecloseAccItemParaEditWidget::on_m_editTripTime_editingFinished()
{
//    if(ui->m_editTripTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editTripTime)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET1, ui->m_editTripTime))
    {
        return;
    }

	ui->m_editTripTime->setText(RecloseAccValueCheck(ui->m_editTripTime->text(), TSET1_MAX, TSET1_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET1,ui->m_editTripTime->text());
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TSET2,ui->m_editTripTime->text());
}

void QRecloseAccItemParaEditWidget::on_m_editRecloseTime_editingFinished()
{
//    if(ui->m_editRecloseTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editRecloseTime)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RECLOSEACCTIME, ui->m_editRecloseTime))
    {
        return;
    }

	ui->m_editRecloseTime->setText(RecloseAccValueCheck(ui->m_editRecloseTime->text(), RECLOSEACCTIME_MAX, RECLOSEACCTIME_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RECLOSEACCTIME,ui->m_editRecloseTime->text());
}

void QRecloseAccItemParaEditWidget::on_m_cbbFaultPermanent_currentIndexChanged(int index)
{
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbFaultPermanent->GetCurrSelObject();
    if(pValue != NULL)
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTPERMANENT, pValue->m_strIndex);
}

void QRecloseAccItemParaEditWidget::on_m_cbbUxMode_currentIndexChanged(int index)
{ 
    CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbUxMode->GetCurrSelObject();
    if(pValue != NULL)
        UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXMODE, pValue->m_strIndex);
}

void QRecloseAccItemParaEditWidget::on_m_editUxInputFre_editingFinished()
{
//    if(ui->m_editUxInputFre->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editUxInputFre)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTFRE, ui->m_editUxInputFre))
    {
        return;
    }

	ui->m_editUxInputFre->setText(RecloseAccValueCheck(ui->m_editUxInputFre->text(), UXINPUTFRE_MAX, UXINPUTFRE_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTFRE,ui->m_editUxInputFre->text());
}

void QRecloseAccItemParaEditWidget::on_m_editUxInputMag_editingFinished()
{
//    if(ui->m_editUxInputMag->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editUxInputMag)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTMAG, ui->m_editUxInputMag))
    {
        return;
    }

	ui->m_editUxInputMag->setText(RecloseAccValueCheck(ui->m_editUxInputMag->text(), UXINPUTMAG_MAX, UXINPUTMAG_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTMAG,ui->m_editUxInputMag->text());
}

void QRecloseAccItemParaEditWidget::on_m_editUxInputAng_editingFinished()
{
//    if(ui->m_editUxInputAng->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editUxInputAng)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTANG, ui->m_editUxInputAng))
    {
        return;
    }

    ui->m_editUxInputAng->setText(RecloseAccValueCheck(ui->m_editUxInputAng->text(), UXINPUTANG_MAX, UXINPUTANG_MIN, 2));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTANG,ui->m_editUxInputAng->text());
}

void QRecloseAccItemParaEditWidget::on_m_editAbsErr1_editingFinished()
{
	ui->m_editAbsErr1->setText(RecloseAccValueCheck(ui->m_editAbsErr1->text(), STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 3));
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_POS,ui->m_editAbsErr1->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_POS,ui->m_editAbsErr1->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ABSERR_POS,ui->m_editAbsErr1->text());
}

void QRecloseAccItemParaEditWidget::on_m_editAbsErr2_editingFinished()
{
	ui->m_editAbsErr2->setText(RecloseAccValueCheck(ui->m_editAbsErr2->text(), STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 3));
	UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ABSERR_NEG,ui->m_editAbsErr2->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ABSERR_NEG,ui->m_editAbsErr2->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_ABSERR_NEG,ui->m_editAbsErr2->text());
}

void QRecloseAccItemParaEditWidget::on_m_editRelErr_editingFinished()
{
	ui->m_editRelErr->setText(RecloseAccValueCheck(ui->m_editRelErr->text(), STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, 3));
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_RELERR,ui->m_editRelErr->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_RELERR,ui->m_editRelErr->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPACC_RELERR,ui->m_editRelErr->text());
}

void QRecloseAccItemParaEditWidget::on_m_editR_editingFinished()
{
    ui->m_editR->setText(RecloseAccValueCheck(ui->m_editR->text(), R1_MAX, R1_MIN, 3));
    if(fabs(ui->m_editR->text().toDouble() - m_dR) < 0.001)
        return;

	float fR = ui->m_editR->text().toFloat();
	float fX = ui->m_editX->text().toFloat();
	float fZ = sqrt(fR*fR + fX*fX);
    float fZPhi = acos(fR/fZ) * 180 / M_PI;
	CString strZ, strZPhi;
	strZ.setNum(fZ);
	strZPhi.setNum(fZPhi);
    ui->m_editZ->setText(RecloseAccValueCheck(strZ, Z1_MAX, Z1_MIN, 3));
    ui->m_editZAngle->setText(RecloseAccValueCheck(strZPhi, Z1PH_MAX, Z1PH_MIN, 3));

    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1, ui->m_editZ->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2, ui->m_editZ->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH, ui->m_editZAngle->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2PH, ui->m_editZAngle->text());

    m_dR = ui->m_editR->text().toDouble();
    m_dZ = ui->m_editZ->text().toDouble();
    m_dZAng = ui->m_editZAngle->text().toDouble();

	return;
}

void QRecloseAccItemParaEditWidget::on_m_editX_editingFinished()
{
    ui->m_editX->setText(RecloseAccValueCheck(ui->m_editX->text(), X1_MAX, X1_MIN, 3));
    if(fabs(ui->m_editX->text().toDouble() - m_dX) < 0.001)
        return;

	float fR = ui->m_editR->text().toFloat();
	float fX = ui->m_editX->text().toFloat();
	float fZ = sqrt(fR*fR + fX*fX);
    float fZPhi = acos(fR/fZ) * 180 / M_PI;
	CString strZ, strZPhi;
	strZ.setNum(fZ);
	strZPhi.setNum(fZPhi);
    ui->m_editZ->setText(RecloseAccValueCheck(strZ, Z1_MAX, Z1_MIN, 3));
    ui->m_editZAngle->setText(RecloseAccValueCheck(strZPhi, Z1PH_MAX, Z1PH_MIN, 3));

    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1, ui->m_editZ->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2, ui->m_editZ->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z1PH, ui->m_editZAngle->text());
    UpdatePara(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_Z2PH, ui->m_editZAngle->text());

    m_dX = ui->m_editX->text().toDouble();
    m_dZ = ui->m_editZ->text().toDouble();
    m_dZAng = ui->m_editZAngle->text().toDouble();

	return;
}
