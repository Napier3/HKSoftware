#include "LowVolActItemParaEditWidget.h"
#include "ui_LowVolActItemParaEditWidget.h"

QLowVolActItemParaEditWidget::QLowVolActItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowVolActItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	m_pTestParaDatas = NULL;
	//connect(m_pParaUI->m_cmbActValue_Var, &QComboBox::currentTextChanged, this, &QLowVolActItemParaEditWidget::slot_m_cmbActValue_Var_currentTextChanged);
	connect(m_pParaUI->m_cmbActValue_Var, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_m_cmbActValue_Var_currentTextChanged(const QString &)));
	m_nFaultType = -1;
	InitUI();
}

QLowVolActItemParaEditWidget::~QLowVolActItemParaEditWidget()
{
	delete m_pParaUI;
}


void QLowVolActItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{//20240620 luozibing 更新数据 将最新链表数据更新到页面
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

void QLowVolActItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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
	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);

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

CExBaseList * QLowVolActItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pTestParaDatas != NULL)
	{
		return m_pTestParaDatas;
	}
	return NULL;
}
// CExBaseList * QLowVolActItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QLowVolActItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowVolActItemParaEditWidget::USetModeChange(int nUSetMode)
{
	if (nUSetMode == 0)
	{
		CString strText = /*"相电压变化起始值(V):"*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowVol_BeginVal + "(V):";
		m_pParaUI->m_labVBegin->setText(strText);
		strText = /*"相电压变化结束值(V):"*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowVol_EndVal + "(V):";
		m_pParaUI->m_labVEnd->setText(strText);
		strText = /*"相电压变化步长(V):"*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_Diff_Step + "(V):";
		m_pParaUI->m_labVStep->setText(strText);
		strText = /*"相电压变化量:"*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowVol_Var + "(V):";
		m_pParaUI->m_labVar->setText(strText);
		//disconnect(m_pParaUI->m_cmbActValue_Var, &QComboBox::currentTextChanged, this, &QLowVolActItemParaEditWidget::slot_m_cmbActValue_Var_currentTextChanged);
		disconnect(m_pParaUI->m_cmbActValue_Var, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_m_cmbActValue_Var_currentTextChanged(const QString &)));
		m_pParaUI->m_cmbActValue_Var->clear();
		m_pParaUI->m_cmbActValue_Var->addItems(QStringList() << "Ua" << "Ub" << "Uc" << "Uabc");
		//connect(m_pParaUI->m_cmbActValue_Var, &QComboBox::currentTextChanged, this, &QLowVolActItemParaEditWidget::slot_m_cmbActValue_Var_currentTextChanged);
		connect(m_pParaUI->m_cmbActValue_Var, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_m_cmbActValue_Var_currentTextChanged(const QString &)));

		UpdateFaultTypeCmb();
	}
	else
	{
		CString strText = /*"线电压变化起始值(V):"*/g_sLangTxt_linevolt + g_sLangTxt_LowVol_BeginVal + "(V):";
		m_pParaUI->m_labVBegin->setText(strText);
		strText = /*"线电压变化结束值(V):"*/g_sLangTxt_linevolt + g_sLangTxt_LowVol_EndVal + "(V):";
		m_pParaUI->m_labVEnd->setText(strText);
		strText = /*"线电压变化步长(V):"*/g_sLangTxt_linevolt + g_sLangTxt_Diff_Step + "(V):";
		m_pParaUI->m_labVStep->setText(strText);
		strText = /*"线电压变化量:"*/g_sLangTxt_linevolt + g_sLangTxt_LowVol_Var + "(V):";
		m_pParaUI->m_labVar->setText(strText);
		//disconnect(m_pParaUI->m_cmbActValue_Var, &QComboBox::currentTextChanged, this, &QLowVolActItemParaEditWidget::slot_m_cmbActValue_Var_currentTextChanged);
		disconnect(m_pParaUI->m_cmbActValue_Var, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_m_cmbActValue_Var_currentTextChanged(const QString &)));
		m_pParaUI->m_cmbActValue_Var->clear();
		m_pParaUI->m_cmbActValue_Var->addItems(QStringList() << "Uab" << "Ubc" << "Uca" << "Uabc");
		//connect(m_pParaUI->m_cmbActValue_Var, &QComboBox::currentTextChanged, this, &QLowVolActItemParaEditWidget::slot_m_cmbActValue_Var_currentTextChanged);
		connect(m_pParaUI->m_cmbActValue_Var, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_m_cmbActValue_Var_currentTextChanged(const QString &)));

		UpdateFaultTypeCmb();
	}
}

void QLowVolActItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//动作值
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_DVDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VAR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RSLTEVAL);
}

void QLowVolActItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{

    //动作值
	if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE)
	{
		//m_pParaUI->m_txtActValue_ActValue->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_ActValue->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_CUR)
	{
		m_pParaUI->m_txtActValue_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_HOlDTIME)
	{
		m_pParaUI->m_txtActValue_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR)
	{
		m_pParaUI->m_txtActValue_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR)
	{
		m_pParaUI->m_txtActValue_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART)
	{
		//m_pParaUI->m_txtActValue_VStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_VStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND)
	{
		//m_pParaUI->m_txtActValue_VEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_VEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP)
	{
		//m_pParaUI->m_txtActValue_VStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_VStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_DVDT)
	{
		//m_pParaUI->m_txtActValue_dVdt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_dVdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VAR)
	{
		m_nFaultType = pData->m_strValue.toFloat();
		UpdateFaultTypeCmb();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_USETMODE)
	{
		int nUSetMode = pData->m_strValue.toFloat();
		USetModeChange(nUSetMode);
	}
}

void QLowVolActItemParaEditWidget::on_m_txtActValue_ActValue_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE, m_pParaUI->m_txtActValue_ActValue))
	{
		return;
	}
	m_pParaUI->m_txtActValue_ActValue->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_ActValue->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE,m_pParaUI->m_txtActValue_ActValue->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_Cur_editingFinished()
{
	m_pParaUI->m_txtActValue_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_CUR,m_pParaUI->m_txtActValue_Cur->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_HoldTime_editingFinished()
{
	m_pParaUI->m_txtActValue_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_HOlDTIME,m_pParaUI->m_txtActValue_HoldTime->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_RelErr_editingFinished()
{
	m_pParaUI->m_txtActValue_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR,m_pParaUI->m_txtActValue_RelErr->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_AbsErr_editingFinished()		
{
	m_pParaUI->m_txtActValue_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR,m_pParaUI->m_txtActValue_AbsErr->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_VStart_editingFinished()	
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART, m_pParaUI->m_txtActValue_VStart))
	{
		return;
	}
	m_pParaUI->m_txtActValue_VStart->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_VStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART,m_pParaUI->m_txtActValue_VStart->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_VEnd_editingFinished()		
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND, m_pParaUI->m_txtActValue_VEnd))
	{
		return;
	}
	m_pParaUI->m_txtActValue_VEnd->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_VEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND,m_pParaUI->m_txtActValue_VEnd->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_VStep_editingFinished()		
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP, m_pParaUI->m_txtActValue_VStep))
	{
		return;
	}
	m_pParaUI->m_txtActValue_VStep->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_VStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP,m_pParaUI->m_txtActValue_VStep->text());
}
void QLowVolActItemParaEditWidget::on_m_txtActValue_dVdt_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_DVDT, m_pParaUI->m_txtActValue_dVdt))
	{
		return;
	}
	m_pParaUI->m_txtActValue_dVdt->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_dVdt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_DVDT,m_pParaUI->m_txtActValue_dVdt->text());
}
void QLowVolActItemParaEditWidget::slot_m_cmbActValue_Var_currentTextChanged(const QString &strText)
{
	CString strTmp; 
	
	if (0 == strText.compare("Ua"))
	{
		m_nFaultType = 0;
	}
	else if (0 == strText.compare("Ub"))
	{
		m_nFaultType = 1;
	}
	else if (0 == strText.compare("Uc"))
	{
		m_nFaultType = 2;
	}
	else if (0 == strText.compare("Uab"))
	{
		m_nFaultType = 3;
	}
	else if (0 == strText.compare("Ubc"))
	{
		m_nFaultType = 4;
	}
	else if (0 == strText.compare("Uca"))
	{
		m_nFaultType = 5;
	}
	else if (0 == strText.compare("Uabc"))
	{
		m_nFaultType = 6;
	}
	strTmp.setNum(m_nFaultType);
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VAR, strTmp);
}
void QLowVolActItemParaEditWidget::UpdateFaultTypeCmb()
{
	switch (m_nFaultType)
	{
	case 0://Ua
	case 3://Uab
		m_pParaUI->m_cmbActValue_Var->setCurrentIndex(0);
		break;
	case 1://Ub
	case 4://Ubc
		m_pParaUI->m_cmbActValue_Var->setCurrentIndex(1);
		break;
	case 2://Uc
	case 5://Uca
		m_pParaUI->m_cmbActValue_Var->setCurrentIndex(2);
		break;
	default://Uabc
		m_pParaUI->m_cmbActValue_Var->setCurrentIndex(3);
		break;
	}
}
void QLowVolActItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);
	m_pParaUI->m_labActValue->setText(/*动作值*/g_sLangTxt_State_ActionValue + "(Hz):");
	m_pParaUI->m_labCur->setText(/*电流*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(V):");
	m_pParaUI->m_labdvdt->setText(/*电压滑差(V/s))*/g_sLangTxt_Native_VoltSlip + "(V/s):");
	m_pParaUI->groupBox_2->setTitle(/*电压变化范围及其变化率*/g_sLangTxt_LowVol_FreqRangeRate);
}