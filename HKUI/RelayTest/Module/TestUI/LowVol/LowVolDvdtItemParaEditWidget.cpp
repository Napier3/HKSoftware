#include "LowVolDvdtItemParaEditWidget.h"
#include "ui_LowVolDvdtItemParaEditWidget.h"

QLowVolDvdtItemParaEditWidget::QLowVolDvdtItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowVolDvdtItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	m_pTestParaDatas = NULL;
	InitUI();
}

QLowVolDvdtItemParaEditWidget::~QLowVolDvdtItemParaEditWidget()
{
	delete m_pParaUI;
}


void QLowVolDvdtItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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
}

void QLowVolDvdtItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowVolDvdtItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pTestParaDatas != NULL)
	{
		return m_pTestParaDatas;
	}
	return NULL;
}

// CExBaseList * QLowVolDvdtItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }

void QLowVolDvdtItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowVolDvdtItemParaEditWidget::USetModeChange(int nUSetMode)
{
	if (nUSetMode == 0)
	{
		CString strText = /*相电压变化终值(V):*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowFreq_EndVal + "(V):";
		m_pParaUI->m_labVEnd->setText(strText);
	}
	else
	{
		CString strText = /*线电压变化终值(V):*/g_sLangTxt_linevolt + g_sLangTxt_LowFreq_EndVal + "(V) : ";
		m_pParaUI->m_labVEnd->setText(strText);
	}
}

void QLowVolDvdtItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//滑差闭锁值
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RSLTEVAL);
}

void QLowVolDvdtItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//滑差闭锁值
	if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_CUR)
	{
		//m_pParaUI->m_txtSlipTrip_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_Cur->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_HOlDTIME)
	{
		m_pParaUI->m_txtSlipTrip_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR)
	{
		m_pParaUI->m_txtSlipTrip_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR)
	{
		m_pParaUI->m_txtSlipTrip_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VEND)
	{
		//m_pParaUI->m_txtSlipTrip_VEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_VEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP)
	{
		//m_pParaUI->m_txtSlipTrip_VStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_VStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_USETMODE)
	{
		int nUSetMode = pData->m_strValue.toFloat();
		USetModeChange(nUSetMode);
	}
}

//滑差闭锁值
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_dfdtSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING, m_pParaUI->m_txtSlipTrip_dfdtSetting))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtSetting->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING,m_pParaUI->m_txtSlipTrip_dfdtSetting->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_Cur_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_CUR, m_pParaUI->m_txtSlipTrip_Cur))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_CUR,m_pParaUI->m_txtSlipTrip_Cur->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_HoldTime_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_HOlDTIME,m_pParaUI->m_txtSlipTrip_HoldTime->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_RelErr_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR,m_pParaUI->m_txtSlipTrip_RelErr->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_AbsErr_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR,m_pParaUI->m_txtSlipTrip_AbsErr->text());

}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_VEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VEND, m_pParaUI->m_txtSlipTrip_VEnd))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_VEnd->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_VEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VEND,m_pParaUI->m_txtSlipTrip_VEnd->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_VStep_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP, m_pParaUI->m_txtSlipTrip_VStep))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_VStep->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_VStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP,m_pParaUI->m_txtSlipTrip_VStep->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_dfdtStart_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART, m_pParaUI->m_txtSlipTrip_dfdtStart))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtStart->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART,m_pParaUI->m_txtSlipTrip_dfdtStart->text());
}
void QLowVolDvdtItemParaEditWidget::on_m_txtSlipTrip_dfdtEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND, m_pParaUI->m_txtSlipTrip_dfdtEnd))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtEnd->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND,m_pParaUI->m_txtSlipTrip_dfdtEnd->text());
}
void QLowVolDvdtItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);
	m_pParaUI->m_labActValue->setText(/*滑差定值dV/dt(V/s):*/g_sLangTxt_LowFreq_dfdtSetting + "dV/dt(V/s):");
	m_pParaUI->m_labCur->setText(/*电流*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(V/s):");
	m_pParaUI->m_labVStep->setText(/*滑差变化步长(V/s):*/g_sLangTxt_LowFreq_dfdtStep + "(V/s):");
	m_pParaUI->m_labdfdtStart->setText(/*滑差变化始值(Hz/s)*/g_sLangTxt_LowFreq_dfdtBegin + "(V/s):");
	m_pParaUI->m_labdfdtEnd->setText(/*滑差变化终值(Hz/s))*/g_sLangTxt_LowFreq_dfdtEnd + "(V/s):");
	m_pParaUI->groupBox_2->setTitle(/*递变参数*/g_sLangTxt_LowFreq_GradientPara);
}