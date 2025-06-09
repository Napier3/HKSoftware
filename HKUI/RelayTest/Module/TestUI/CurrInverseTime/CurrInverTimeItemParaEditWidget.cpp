#include "CurrInverTimeItemParaEditWidget.h"
#include "ui_CurrInverTimeItemParaEditWidget.h"
#include "../../XLangResource_Native.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QCurrInverTimeItemParaEditWidget::QCurrInverTimeItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    m_pParaUI(new Ui::QCurrInverTimeItemParaEditWidget)
{
    m_pParaUI->setupUi(this);
	//m_pTestParaDatas = NULL;

	InitUI();
	initConnections();
	InitLanuage();
}

QCurrInverTimeItemParaEditWidget::~QCurrInverTimeItemParaEditWidget()
{
    delete m_pParaUI;
}

void QCurrInverTimeItemParaEditWidget::InitUI()
{
	m_pParaUI->m_cmb_ErrorType->addItems(QStringList()<<g_sLangTxt_Native_GndA/*"A相接地"*/<<g_sLangTxt_Native_GndB/*"B相接地"*/<<g_sLangTxt_Native_GndC/*"C相接地"*/<<g_sLangTxt_Native_ShortAB/*"AB相间"*/\
		<<g_sLangTxt_Native_ShortBC/*"BC相间"*/<<g_sLangTxt_Native_ShortCA/*"CA相间"*/<<g_sLangTxt_Native_ShortABC/*"三相短路"*/<<"3I0"<<"I2"<<"Ia+Ib+Ic"<<"Ua,Ia"<<"Va,Vb"<<"A"<<"B"<<"C");
	m_pParaUI->m_cmbFaultVolt->addItems(QStringList()<<g_sLangTxt_Native_ShortCircuitV/*"短路电压"*/<<"3U0");
}

void QCurrInverTimeItemParaEditWidget::initConnections()
{
	connect(m_pParaUI->m_cmb_ErrorType, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_ErrorType_currentIndexChanged(int)));
	connect(m_pParaUI->m_cmbFaultVolt, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_FaultVolt_Changed(int)));

	connect(m_pParaUI->m_txtFaultVolt,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultVolt_editingFinished()));
	connect(m_pParaUI->m_txtCurrent,SIGNAL(editingFinished()), this, SLOT(slot_lne_Current_editingFinished()));
	connect(m_pParaUI->m_txtAng,SIGNAL(editingFinished()), this, SLOT(slot_lne_Ang_editingFinished()));
	connect(m_pParaUI->m_txtHz,SIGNAL(editingFinished()), this, SLOT(slot_lne_Hz_editingFinished()));
	connect(m_pParaUI->m_txtTSetting,SIGNAL(editingFinished()), this, SLOT(slot_lne_TSetting_editingFinished()));
	connect(m_pParaUI->m_txtPlus,SIGNAL(editingFinished()), this, SLOT(slot_m_txtPlus_editingFinished()));
	connect(m_pParaUI->m_txtMinus,SIGNAL(editingFinished()), this, SLOT(slot_m_txtMinus_editingFinished()));
	connect(m_pParaUI->m_txtRelErr,SIGNAL(editingFinished()), this, SLOT(slot_lne_RelErr_editingFinished()));
}

void QCurrInverTimeItemParaEditWidget::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(m_pParaUI->groupBox, g_sLangID_Vol_FaultOutput, XLang_Ctrls_QGroupBox);//故障态输出
	xlang_SetLangStrToWidget(m_pParaUI->m_labErrType, g_sLangID_State_FaultType, XLang_Ctrls_QLabel);//故障类型:
	xlang_GetLangStrByFile(strtemp, g_sLangID_Current);//电流(I*):
	strtemp += "(I*):";
	m_pParaUI->m_labCurrent->setText(strtemp);
	xlang_SetLangStrToWidget(m_pParaUI->m_labFaultVolt, g_sLangID_State_ShortU, XLang_Ctrls_QLabel);//短路电压(V):
	xlang_GetLangStrByFile(strtemp, g_sLangID_Gradient_Phase);//相位差(°):
	strtemp += QString::fromLocal8Bit("(°):");
	m_pParaUI->m_labAng->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Frequency);//频率(Hz):
	strtemp += ":";
	m_pParaUI->m_labHz->setText(strtemp);
	xlang_SetLangStrToWidget(m_pParaUI->m_lablne_TSetting, g_sLangID_Manual_ActionTime, XLang_Ctrls_QLabel); //动作时间(s) :
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	strtemp += ":";
	m_pParaUI->m_labRelErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):";
	m_pParaUI->m_labAbsErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):";
	m_pParaUI->m_labAbsErr_2->setText(strtemp);
}
void QCurrInverTimeItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE)
	{
		m_pParaUI->m_cmb_ErrorType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt)
	{
		m_pParaUI->m_txtFaultVolt->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		//m_pParaUI->m_txtFaultVolt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 120, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT)
	{
		m_pParaUI->m_txtCurrent->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		//m_pParaUI->m_txtCurrent->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG)
	{
		m_pParaUI->m_txtAng->setText(CheckDataMinMax(pData->m_strValue,360,-360,2));
		//m_pParaUI->m_txtAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre)
	{
		m_pParaUI->m_txtHz->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//m_pParaUI->m_txtHz->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING)
	{
		m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,-1,3));
		//m_pParaUI->m_txtTSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS)
	{
		m_pParaUI->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//m_pParaUI->m_txtPlus->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS)
	{
		m_pParaUI->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//m_pParaUI->m_txtMinus->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr)
	{
		m_pParaUI->m_txtRelErr->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
		//m_pParaUI->m_txtRelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CMBFAULTVolt)
	{
		m_pParaUI->m_cmbFaultVolt->setCurrentIndex(pData->m_strValue.toInt());
	}
	
}

void QCurrInverTimeItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{//更新数据 将最新链表数据更新到页面
	QItemParaEditWidgetBase::UpdateParas(pSttMacroTest);

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}

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

	if (m_pCurrMacroTest_External == NULL)
	{
		return;
	}
	//emit sig_UpdateCurrPoint(m_pCurrMacroTest_External);

}

void QCurrInverTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
{
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}
	if(m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);

	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);
	//CSttMacroTestParaData *pDataExternal = (CSttMacroTestParaData *)pSttMacroTestParaDatas_External->FindByID(strID);

	if(pDataInner != NULL)
	{
		pDataInner->m_strValue = strValue;
		if(pSttMacroTestParaDatas_External != NULL)
		{
			pSttMacroTestParaDatas_External->SetDataValue(strID,strValue,TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
	}
}

void QCurrInverTimeItemParaEditWidget::slot_cmb_ErrorType_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE,strTmp);
}

void QCurrInverTimeItemParaEditWidget::slot_cmb_FaultVolt_Changed(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CMBFAULTVolt,strTmp);
}

void QCurrInverTimeItemParaEditWidget::slot_lne_Hz_editingFinished()
{
	//if (m_pParaUI->m_txtHz->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtHz)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtHz->setText(CheckDataMinMax(m_pParaUI->m_txtHz->text(),999.999,0,3));
    float fv = m_pParaUI->m_txtHz->text().toFloat();
    fv = setLimit(0,999.999,fv);
    m_pParaUI->m_txtHz->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre,m_pParaUI->m_txtHz->text());
}

void QCurrInverTimeItemParaEditWidget::slot_lne_Ang_editingFinished()
{
	//if (m_pParaUI->m_txtAng->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtAng)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtAng->setText(CheckDataMinMax(m_pParaUI->m_txtAng->text(),360,-360,1));
    float fv = m_pParaUI->m_txtAng->text().toFloat();
    fv = setLimit(-360,360,fv);
    m_pParaUI->m_txtAng->setText(QString::number(fv,'f',2));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG,m_pParaUI->m_txtAng->text());
}

void QCurrInverTimeItemParaEditWidget::slot_lne_Current_editingFinished()
{
	//if (m_pParaUI->m_txtCurrent->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtCurrent)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtCurrent->setText(CheckDataMinMax(m_pParaUI->m_txtCurrent->text(),20,0,3));
    float fv = m_pParaUI->m_txtCurrent->text().toFloat();
    fv = setLimit(0,20,fv);
    m_pParaUI->m_txtCurrent->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT,m_pParaUI->m_txtCurrent->text());
	//emit sig_UpdateCurrPoint(m_pCurrMacroTest_External);
}

void QCurrInverTimeItemParaEditWidget::slot_lne_FaultVolt_editingFinished()
{
	//if (m_pParaUI->m_txtFaultVolt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtFaultVolt)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtFaultVolt->setText(CheckDataMinMax(m_pParaUI->m_txtFaultVolt->text(),120,0,3));
    float fv = m_pParaUI->m_txtFaultVolt->text().toFloat();
    fv = setLimit(0,120,fv);
    m_pParaUI->m_txtFaultVolt->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt,m_pParaUI->m_txtFaultVolt->text());
}

void QCurrInverTimeItemParaEditWidget::slot_lne_TSetting_editingFinished()
{
	//if (m_pParaUI->m_txtTSetting->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtTSetting)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(m_pParaUI->m_txtTSetting->text(),999.999,0,3));
    float fv = m_pParaUI->m_txtTSetting->text().toFloat();
    fv = setLimit(0,999.999,fv);
    m_pParaUI->m_txtTSetting->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING,m_pParaUI->m_txtTSetting->text());
	//emit sig_UpdateCurrPoint(m_pCurrMacroTest_External);
}

void QCurrInverTimeItemParaEditWidget::slot_m_txtPlus_editingFinished()
{
	//if (m_pParaUI->m_txtPlus->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtPlus)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtPlus->setText(CheckDataMinMax(m_pParaUI->m_txtPlus->text(),999.999,0,3));
    float fv = m_pParaUI->m_txtPlus->text().toFloat();
    fv = setLimit(0,999.999,fv);
    m_pParaUI->m_txtPlus->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS,m_pParaUI->m_txtPlus->text());
}

void QCurrInverTimeItemParaEditWidget::slot_m_txtMinus_editingFinished()
{
	//if (m_pParaUI->m_txtMinus->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtMinus)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtMinus->setText(CheckDataMinMax(m_pParaUI->m_txtMinus->text(),999.999,0,3));
    float fv = m_pParaUI->m_txtMinus->text().toFloat();
    fv = setLimit(0,999.999,fv);
    m_pParaUI->m_txtMinus->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS,m_pParaUI->m_txtMinus->text());
}

void QCurrInverTimeItemParaEditWidget::slot_lne_RelErr_editingFinished()
{
	//if (m_pParaUI->m_txtRelErr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtRelErr)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //m_pParaUI->m_txtRelErr->setText(CheckDataMinMax(m_pParaUI->m_txtRelErr->text(),999.999,0,3));
    float fv = m_pParaUI->m_txtRelErr->text().toFloat();
    fv = setLimit(0,999.999,fv);
    m_pParaUI->m_txtRelErr->setText(QString::number(fv,'f',3));

	UpdatePara(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr,m_pParaUI->m_txtRelErr->text());
}

void QCurrInverTimeItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CMBFAULTVolt);
}

CExBaseList * QCurrInverTimeItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

//CExBaseList* QCurrInverTimeItemParaEditWidget::GetInnerMacroTestParaDatas()
//{
//	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
//}

// CExBaseList * QCurrInverTimeItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
