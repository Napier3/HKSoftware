#include "LowVolILockItemParaEditWidget.h"
#include "ui_LowVolILockItemParaEditWidget.h"

QLowVolILockItemParaEditWidget::QLowVolILockItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowVolILockItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	m_pTestParaDatas = NULL;
	InitUI();
}

QLowVolILockItemParaEditWidget::~QLowVolILockItemParaEditWidget()
{
	delete m_pParaUI;
}


void QLowVolILockItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QLowVolILockItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowVolILockItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pTestParaDatas != NULL)
	{
		return m_pTestParaDatas;
	}
	return NULL;
}
// CExBaseList * QLowVolILockItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QLowVolILockItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowVolILockItemParaEditWidget::USetModeChange(int nUSetMode)
{
	if (nUSetMode == 0)
	{
		CString strText = /*"相电压滑差(dV/dt):";*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowVol_dVdt + "(dV/dt):";
		m_pParaUI->m_labDvdt->setText(strText);
	}
	else
	{
		CString strText = /*"线电压滑差(dV/dt):"*/g_sLangTxt_linevolt + g_sLangTxt_LowVol_dVdt + "(dV/dt):";
		m_pParaUI->m_labDvdt->setText(strText);
	}
}

void QLowVolILockItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//低电流闭锁值
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VAR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_DVDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RSLTEVAL);
}

void QLowVolILockItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//低电流闭锁值
	if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING)
	{
		//m_pParaUI->m_txtIBlock_IBlockSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IBlockSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_HOlDTIME)
	{
		m_pParaUI->m_txtIBlock_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VAR)
	{
		m_pParaUI->m_cmbIBlock_Var->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR)
	{
		m_pParaUI->m_txtIBlock_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR)
	{
		m_pParaUI->m_txtIBlock_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTART)
	{
		//m_pParaUI->m_txtIBlock_IStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IEND)
	{
		//m_pParaUI->m_txtIBlock_IEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTEP)
	{
		//m_pParaUI->m_txtIBlock_IStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_DVDT)
	{
		//m_pParaUI->m_txtIBlock_dVdt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_dVdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}              
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VEND)
	{
		//m_pParaUI->m_txtIBlock_VEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_VEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_USETMODE)
	{
		int nUSetMode = pData->m_strValue.toFloat();
		USetModeChange(nUSetMode);
	}
}
//低电流闭锁值
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_IBlockSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING, m_pParaUI->m_txtIBlock_IBlockSetting))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IBlockSetting->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IBlockSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING,m_pParaUI->m_txtIBlock_IBlockSetting->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_HoldTime_editingFinished()
{
	m_pParaUI->m_txtIBlock_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_HOlDTIME,m_pParaUI->m_txtIBlock_HoldTime->text());
}
void QLowVolILockItemParaEditWidget::on_m_cmbIBlock_Var_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VAR,strTmp);
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_RelErr_editingFinished()
{
	m_pParaUI->m_txtIBlock_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR,m_pParaUI->m_txtIBlock_RelErr->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_AbsErr_editingFinished()
{
	m_pParaUI->m_txtIBlock_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR,m_pParaUI->m_txtIBlock_AbsErr->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_IStart_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTART, m_pParaUI->m_txtIBlock_IStart))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IStart->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTART,m_pParaUI->m_txtIBlock_IStart->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_IEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IEND, m_pParaUI->m_txtIBlock_IEnd))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IEnd->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IEND,m_pParaUI->m_txtIBlock_IEnd->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_IStep_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTEP, m_pParaUI->m_txtIBlock_IStep))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IStep->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTEP,m_pParaUI->m_txtIBlock_IStep->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_dVdt_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_DVDT, m_pParaUI->m_txtIBlock_dVdt))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_dVdt->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_dVdt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_DVDT,m_pParaUI->m_txtIBlock_dVdt->text());
}
void QLowVolILockItemParaEditWidget::on_m_txtIBlock_VEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VEND, m_pParaUI->m_txtIBlock_VEnd))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_VEnd->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_VEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VEND,m_pParaUI->m_txtIBlock_VEnd->text());
}
void QLowVolILockItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);
	m_pParaUI->m_labIBlockSetting->setText(/*低电流闭锁值(A):*/g_sLangTxt_LowFreq_ILock + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	m_pParaUI->m_labIBlock_Var->setText(/*电流输出相*/g_sLangTxt_Native_CuroutputPhase + ":");
	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(A):");

	m_pParaUI->groupBox_2->setTitle(/*递变参数*/g_sLangTxt_LowFreq_GradientPara);
	m_pParaUI->m_labIStart->setText(/*电流变化始值(A)*/g_sLangTxt_Native_CurrentChangeStartValue + "(A):");
	m_pParaUI->m_labIEnd->setText(/*电流变化终值(A):*/g_sLangTxt_Native_CurrentChangeEndValue + "(A):");
	m_pParaUI->m_labIStep->setText(/*电流变化步长(A))*/g_sLangTxt_Native_CurrentChangeStep + "(A):");
	m_pParaUI->m_labFreqEnd->setText(/*电压变化终值(V))*/g_sLangTxt_Native_FinalVoltChange + "(V):");
}