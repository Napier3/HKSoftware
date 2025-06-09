#include "LowFreqULockItemParaEditWidget.h"
#include "ui_LowFreqULockItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QLowFreqULockItemParaEditWidget::QLowFreqULockItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowFreqULockItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QLowFreqULockItemParaEditWidget::~QLowFreqULockItemParaEditWidget()
{
	delete m_pParaUI;
}

void QLowFreqULockItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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
	//SetDatas(pSttMacroTest);
}

void QLowFreqULockItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowFreqULockItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
// CExBaseList * QLowFreqULockItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QLowFreqULockItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}
void QLowFreqULockItemParaEditWidget::USetModeChange(int nUSetMode)
{
	if (nUSetMode == 0)
	{
		CString strText = /*相电压变化始值(V):*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowFreq_BeginVal + "(V):";
		m_pParaUI->m_labVBegin->setText(strText);
		strText = /*相电压变化终值(V):*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowFreq_EndVal + "(V):";
		m_pParaUI->m_labVEnd->setText(strText);
		strText = /*相电压变化步长(V):*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_Diff_Step + "(V):";
		m_pParaUI->m_labVStep->setText(strText);
	}
	else
	{
		CString strText = /*线电压变化始值(V):*/g_sLangTxt_linevolt + g_sLangTxt_LowFreq_BeginVal + "(V) : ";
		m_pParaUI->m_labVBegin->setText(strText);
		strText = /*线电压变化终值(V):*/g_sLangTxt_linevolt + g_sLangTxt_LowFreq_EndVal + "(V) : ";
		m_pParaUI->m_labVEnd->setText(strText);
		strText = /*线电压变化步长(V):*/g_sLangTxt_linevolt + g_sLangTxt_Diff_Step + "(V) : ";
		m_pParaUI->m_labVStep->setText(strText);
	}
}
void QLowFreqULockItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//低电压闭锁值
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VAR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTEP);
	CheckForPresence(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_DFDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_FREQEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RSLTEVAL);
}

void QLowFreqULockItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//低电压闭锁值
	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING)
	{
		//m_pParaUI->m_txtVBlock_VBlockSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtVBlock_VBlockSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_CUR)
	{
		m_pParaUI->m_txtVBlock_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_HOlDTIME)
	{
		m_pParaUI->m_txtVBlock_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VAR)
	{
		m_pParaUI->m_cmbVBlock_Var->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RELERR)
	{
		m_pParaUI->m_txtVBlock_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_ABSERR)
	{
		m_pParaUI->m_txtVBlock_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTART)
	{
		//m_pParaUI->m_txtVBlock_VStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtVBlock_VStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VEND)
	{
		//m_pParaUI->m_txtVBlock_VEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtVBlock_VEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTEP)
	{
		//m_pParaUI->m_txtVBlock_VStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtVBlock_VStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_DFDT)
	{
		//m_pParaUI->m_txtVBlock_dvdf->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtVBlock_dfdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_FREQEND)
	{
		m_pParaUI->m_txtVBlock_FreqEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE)
	{
		int nUSetMode = pData->m_strValue.toFloat();
		USetModeChange(nUSetMode);
	}
}

//低电压闭锁值
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_VBlockSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING, m_pParaUI->m_txtVBlock_VBlockSetting))
	{
		return;
	}
	m_pParaUI->m_txtVBlock_VBlockSetting->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_VBlockSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING,m_pParaUI->m_txtVBlock_VBlockSetting->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_Cur_editingFinished()
{
	m_pParaUI->m_txtVBlock_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_CUR,m_pParaUI->m_txtVBlock_Cur->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_HoldTime_editingFinished()
{
	m_pParaUI->m_txtVBlock_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_HOlDTIME,m_pParaUI->m_txtVBlock_HoldTime->text());
}
void QLowFreqULockItemParaEditWidget::on_m_cmbVBlock_Var_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VAR,strTmp);
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_RelErr_editingFinished()
{
	m_pParaUI->m_txtVBlock_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RELERR,m_pParaUI->m_txtVBlock_RelErr->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_AbsErr_editingFinished()
{
	m_pParaUI->m_txtVBlock_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_ABSERR,m_pParaUI->m_txtVBlock_AbsErr->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_VStart_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTART, m_pParaUI->m_txtVBlock_VStart))
	{
		return;
	}
	m_pParaUI->m_txtVBlock_VStart->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_VStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTART,m_pParaUI->m_txtVBlock_VStart->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_VEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VEND, m_pParaUI->m_txtVBlock_VEnd))
	{
		return;
	}
	m_pParaUI->m_txtVBlock_VEnd->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_VEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VEND,m_pParaUI->m_txtVBlock_VEnd->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_VStep_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTEP, m_pParaUI->m_txtVBlock_VStep))
	{
		return;
	}
	m_pParaUI->m_txtVBlock_VStep->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_VStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTEP,m_pParaUI->m_txtVBlock_VStep->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_dfdt_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_DFDT, m_pParaUI->m_txtVBlock_dfdt))
	{
		return;
	}
	m_pParaUI->m_txtVBlock_dfdt->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_dfdt->text(), 999.999, 0, 3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_DFDT, m_pParaUI->m_txtVBlock_dfdt->text());
}
void QLowFreqULockItemParaEditWidget::on_m_txtVBlock_FreqEnd_editingFinished()
{
	m_pParaUI->m_txtVBlock_FreqEnd->setText(CheckDataMinMax(m_pParaUI->m_txtVBlock_FreqEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_FREQEND,m_pParaUI->m_txtVBlock_FreqEnd->text());
}
void QLowFreqULockItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);
	m_pParaUI->m_labVBlockSetting->setText(/*低电压闭锁值(V):*/g_sLangTxt_LowFreq_ULock + "(V):");
	m_pParaUI->m_labCur->setText(/*电流*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	m_pParaUI->m_labVBlock_Var->setText(/*电压变化量:*/g_sLangTxt_Native_VoltChangeAmt + ":");
	m_pParaUI->m_cmbVBlock_Var->addItems(QStringList() <</*低电压*/g_sLangTxt_LowFreq_LowVoltage
														<</*负序电压*/g_sLangTxt_Native_NegVol
														<</*零序电压*/g_sLangTxt_ActionTime_ZeroVol);
	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(V):");
	m_pParaUI->groupBox_2->setTitle(/*递变参数*/g_sLangTxt_LowFreq_GradientPara);
	m_pParaUI->m_labdfdt->setText(/*频率滑差(Hz/s))*/g_sLangTxt_Native_FreqSlip + "(Hz/s):");
	m_pParaUI->m_labFreqEnd->setText(/*频率变化终值(Hz))*/g_sLangTxt_Native_FreFinalValue + "(Hz):");

}