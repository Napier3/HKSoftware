#include "VolInverTimeItemParaEditWidget.h"
#include "ui_VolInverTimeItemParaEditWidget.h"
#include "../../XLangResource_Native.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QVolInverTimeItemParaEditWidget::QVolInverTimeItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    m_pParaUI(new Ui::QVolInverTimeItemParaEditWidget)
{
    m_pParaUI->setupUi(this);
	//m_pTestParaDatas = NULL;

	InitUI();
	InitLanuage();
	initConnections();
}

QVolInverTimeItemParaEditWidget::~QVolInverTimeItemParaEditWidget()
{
    delete m_pParaUI;
}

void QVolInverTimeItemParaEditWidget::InitUI()
{
	m_pParaUI->m_cmb_ErrorType->addItems(QStringList()<<g_sLangTxt_Native_GndA/*"A相接地"*/<<g_sLangTxt_Native_GndB/*"B相接地"*/\
		<<g_sLangTxt_Native_GndC/*"C相接地"*/<<g_sLangTxt_Native_ShortAB/*"AB相间"*/<<g_sLangTxt_Native_ShortBC/*"BC相间"*/\
		<<g_sLangTxt_Native_ShortCA/*"CA相间"*/<<g_sLangTxt_Native_ShortABC/*"三相短路"*/<<"3U0"<<"U2");
}

void QVolInverTimeItemParaEditWidget::initConnections()
{
	connect(m_pParaUI->m_cmb_ErrorType, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_ErrorType_currentIndexChanged(int)));

	connect(m_pParaUI->m_txtVolt,SIGNAL(editingFinished()), this, SLOT(slot_lne_Volt_editingFinished()));
	connect(m_pParaUI->m_txtFaultCurr,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultCurrent_editingFinished()));
	connect(m_pParaUI->m_txtAng,SIGNAL(editingFinished()), this, SLOT(slot_lne_Ang_editingFinished()));
	connect(m_pParaUI->m_txtHz,SIGNAL(editingFinished()), this, SLOT(slot_lne_Hz_editingFinished()));
	connect(m_pParaUI->m_txtTSetting,SIGNAL(editingFinished()), this, SLOT(slot_lne_TSetting_editingFinished()));
	connect(m_pParaUI->m_txtPlus,SIGNAL(editingFinished()), this, SLOT(slot_m_txtPlus_editingFinished()));
	connect(m_pParaUI->m_txtMinus,SIGNAL(editingFinished()), this, SLOT(slot_m_txtMinus_editingFinished()));
	connect(m_pParaUI->m_txtRelErr,SIGNAL(editingFinished()), this, SLOT(slot_lne_RelErr_editingFinished()));
}

void QVolInverTimeItemParaEditWidget::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(m_pParaUI->groupBox, g_sLangID_Vol_FaultOutput, XLang_Ctrls_QGroupBox);//故障态输出
	xlang_SetLangStrToWidget(m_pParaUI->m_labErrType, g_sLangID_State_FaultType, XLang_Ctrls_QLabel);//故障类型:
	xlang_GetLangStrByFile(strtemp, g_sLangID_Voltage);//电压(V):
	strtemp += ":";
	m_pParaUI->m_labVolt->setText(strtemp);
	xlang_SetLangStrToWidget(m_pParaUI->m_labFaultCurr, g_sLangID_State_ShortI, XLang_Ctrls_QLabel);//短路电流(A):
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
	strtemp += "(s):+";
	m_pParaUI->m_labAbsErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):-";
	m_pParaUI->m_labMinus->setText(strtemp);
}

//void QVolInverTimeItemParaEditWidget::SetDatas(CExBaseList *pParas)
//{//将读取数据转换到界面
//	if(pParas == NULL)
//		return;
//
//	CExBaseList  *pTestParaDatas = NULL;
//	CExBaseList *pCurrParas = ((CSttMacroTest *)pParas)->GetSttMacroTestPara();
//	if(pCurrParas == NULL)
//		return;
//	pTestParaDatas = (CExBaseList *)pCurrParas->GetHead();
//	if(pTestParaDatas == NULL)
//		return;
//
//	//m_pCurrMacroTest = (CSttMacroTest *)pParas;
//	m_pTestParaDatas = pTestParaDatas;
//	CheckAllPresence(m_pTestParaDatas);
//	POS pos = m_pTestParaDatas->GetHeadPosition();
//	while (pos!= NULL)
//	{
//		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pTestParaDatas->GetNext(pos);
//		SetValueToPage(pData);
//	}
//}

void QVolInverTimeItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE)
	{
		m_pParaUI->m_cmb_ErrorType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE)
	{
		m_pParaUI->m_txtVolt->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		//m_pParaUI->m_txtVolt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 120, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR)
	{
		m_pParaUI->m_txtFaultCurr->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		//m_pParaUI->m_txtFaultCurr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG)
	{
		m_pParaUI->m_txtAng->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		//m_pParaUI->m_txtAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ)
	{
		m_pParaUI->m_txtHz->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//m_pParaUI->m_txtHz->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING)
	{
		m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//m_pParaUI->m_txtTSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS)
	{
		m_pParaUI->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//m_pParaUI->m_txtPlus->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS)
	{
		m_pParaUI->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
		//m_pParaUI->m_txtMinus->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr)
	{
		m_pParaUI->m_txtRelErr->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
		//m_pParaUI->m_txtRelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
	}
	
}

void QVolInverTimeItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{//更新数据 将最新链表数据更新到页面
	//SetDatas(pSttMacroTest);
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
}

//void QVolInverTimeItemParaEditWidget::GetDatas(CExBaseList *pParas)
//{//将界面设置参数填到链表
	//POS pos = m_pCurrMacroTest->GetHeadPosition();
	//while (pos!= NULL)
	//{
	//	CShortData *pData = (CShortData*)m_pCurrMacroTest->GetNext(pos);
	//	GetPageToValue(pData);
	//}
//}

//void QVolInverTimeItemParaEditWidget::GetPageToValue(CShortData *pData)
//{
//	if(pData == NULL)
//		return;
//	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CMBFAULTVolt)
//	{
//		pData->m_strValue.setNum(m_pParaUI->m_cmbFaultVolt->currentIndex());
//	}
//	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE)
//	{
//		pData->m_strValue.setNum(m_pParaUI->m_cmb_ErrorType->currentIndex());
//	}
//	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR)
//	{
//		pData->m_strValue = m_pParaUI->m_txtFaultCurr->text();
//	}
//	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE)
//	{
//		pData->m_strValue = m_pParaUI->m_txtVolt->text();
//	}
//	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG)
//	{
//		pData->m_strValue = m_pParaUI->m_txtAng->text();
//	}
//	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_HZ)
//	{
//		pData->m_strValue = m_pParaUI->m_txtHz->text();
//	}
//	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING)
//	{
//		pData->m_strValue = m_pParaUI->m_txtTSetting->text();
//	}
//	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_AbsErr)
//	{
//		pData->m_strValue = m_pParaUI->m_txtAbsErr->text();
//	}	
//	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr)
//	{
//		pData->m_strValue = m_pParaUI->m_txtRelErr->text();
//	}
//
//}

void QVolInverTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

void QVolInverTimeItemParaEditWidget::slot_cmb_ErrorType_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE,strTmp);
}


//void QVolInverTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
//{
	//if(m_pCurrMacroTest == NULL)
	//	return;
	//CShortData *pData = (CShortData *)m_pCurrMacroTest->FindByID(strID);
	//if(pData != NULL)
	//{
	//	pData->m_strValue = strValue;
	//}
//}

void QVolInverTimeItemParaEditWidget::slot_lne_Hz_editingFinished()
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
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ,m_pParaUI->m_txtHz->text());
}

void QVolInverTimeItemParaEditWidget::slot_lne_Ang_editingFinished()
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
	fv = setAngleLimitEx(fv);
	m_pParaUI->m_txtAng->setText(QString::number(fv,'f',1));
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG,m_pParaUI->m_txtAng->text());
}

void QVolInverTimeItemParaEditWidget::slot_lne_Volt_editingFinished()
{
	//if (m_pParaUI->m_txtVolt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtVolt)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	//m_pParaUI->m_txtVolt->setText(CheckDataMinMax(m_pParaUI->m_txtVolt->text(),120,0,3));
	float fv = m_pParaUI->m_txtVolt->text().toFloat();
	fv = setLimit(0,120,fv);
	m_pParaUI->m_txtVolt->setText(QString::number(fv,'f',3));
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE,m_pParaUI->m_txtVolt->text());
}

void QVolInverTimeItemParaEditWidget::slot_lne_FaultCurrent_editingFinished()
{
	//if (m_pParaUI->m_txtFaultCurr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtFaultCurr)->IsSetting())
	//	{
	//		return;
	//	}
	//}

	//m_pParaUI->m_txtFaultCurr->setText(CheckDataMinMax(m_pParaUI->m_txtFaultCurr->text(),20,0,3));
	float fv = m_pParaUI->m_txtFaultCurr->text().toFloat();
	fv = setLimit(0,20,fv);
	m_pParaUI->m_txtFaultCurr->setText(QString::number(fv,'f',3));
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR,m_pParaUI->m_txtFaultCurr->text());
}

void QVolInverTimeItemParaEditWidget::slot_lne_TSetting_editingFinished()
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
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING,m_pParaUI->m_txtTSetting->text());
}

void QVolInverTimeItemParaEditWidget::slot_m_txtPlus_editingFinished()
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
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS,m_pParaUI->m_txtPlus->text());
}

void QVolInverTimeItemParaEditWidget::slot_m_txtMinus_editingFinished()
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
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS,m_pParaUI->m_txtMinus->text());
}

void QVolInverTimeItemParaEditWidget::slot_lne_RelErr_editingFinished()
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
	UpdatePara(STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr,m_pParaUI->m_txtRelErr->text());
}

void QVolInverTimeItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTCURR);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_ANG);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultHZ);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_PLUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_ABSERR_MINUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_RelErr);
}

CExBaseList * QVolInverTimeItemParaEditWidget::GetMacroTestParaDatas()
{
	//return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

//CExBaseList* QVolInverTimeItemParaEditWidget::GetInnerMacroTestParaDatas()
//{
//	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
//}


//void QVolInverTimeItemParaEditWidget::DelMacroTestParaDatas()
//{
//	m_pCurrMacroTest_External = NULL;
//}

// CExBaseList * QVolInverTimeItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
// 	if(m_oSttMacroTest_Inner.GetCount() != 0)
// 	{
// 		return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
// 	}
// 	return NULL;
// }
