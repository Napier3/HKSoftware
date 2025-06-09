#include "LowFreqILockItemParaEditWidget.h"
#include "ui_LowFreqILockItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QLowFreqILockItemParaEditWidget::QLowFreqILockItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowFreqILockItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QLowFreqILockItemParaEditWidget::~QLowFreqILockItemParaEditWidget()
{
	delete m_pParaUI;
}

void QLowFreqILockItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QLowFreqILockItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowFreqILockItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

//CExBaseList * QLowFreqILockItemParaEditWidget::GetMacroTestParaDatas_Inner()
//{
//    if(m_oSttMacroTest_Inner.GetCount() != 0)
//    {
//        return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//    }
//    return NULL;
//}

void QLowFreqILockItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowFreqILockItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//低电流闭锁值
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_VAR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTEP);
	CheckForPresence(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_DFDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_FREQEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RSLTEVAL);
}


void QLowFreqILockItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//低电流闭锁值
	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING)
	{
		//m_pParaUI->m_txtIBlock_IBlockSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IBlockSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_HOlDTIME)
	{
		m_pParaUI->m_txtIBlock_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_VAR)
	{
		m_pParaUI->m_cmbIBlock_Var->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RELERR)
	{
		m_pParaUI->m_txtIBlock_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ABSERR)
	{
		m_pParaUI->m_txtIBlock_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTART)
	{
		//m_pParaUI->m_txtIBlock_IStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IEND)
	{
		//m_pParaUI->m_txtIBlock_IEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTEP)
	{
		//m_pParaUI->m_txtIBlock_IStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_IStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_DFDT)
	{
		//m_pParaUI->m_txtIBlock_dfdt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtIBlock_dfdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}              
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_FREQEND)
	{
		m_pParaUI->m_txtIBlock_FreqEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}

}
//低电流闭锁值
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_IBlockSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING, m_pParaUI->m_txtIBlock_IBlockSetting))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IBlockSetting->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IBlockSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING,m_pParaUI->m_txtIBlock_IBlockSetting->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_HoldTime_editingFinished()
{
	m_pParaUI->m_txtIBlock_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_HOlDTIME,m_pParaUI->m_txtIBlock_HoldTime->text());
}
void QLowFreqILockItemParaEditWidget::on_m_cmbIBlock_Var_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_VAR,strTmp);
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_RelErr_editingFinished()
{
	m_pParaUI->m_txtIBlock_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RELERR,m_pParaUI->m_txtIBlock_RelErr->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_AbsErr_editingFinished()
{
	m_pParaUI->m_txtIBlock_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ABSERR,m_pParaUI->m_txtIBlock_AbsErr->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_IStart_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTART, m_pParaUI->m_txtIBlock_IStart))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IStart->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTART,m_pParaUI->m_txtIBlock_IStart->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_IEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IEND, m_pParaUI->m_txtIBlock_IEnd))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IEnd->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IEND,m_pParaUI->m_txtIBlock_IEnd->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_IStep_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTEP, m_pParaUI->m_txtIBlock_IStep))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_IStep->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_IStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTEP,m_pParaUI->m_txtIBlock_IStep->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_dfdt_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_DFDT, m_pParaUI->m_txtIBlock_dfdt))
	{
		return;
	}
	m_pParaUI->m_txtIBlock_dfdt->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_dfdt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_DFDT, m_pParaUI->m_txtIBlock_dfdt->text());
}
void QLowFreqILockItemParaEditWidget::on_m_txtIBlock_FreqEnd_editingFinished()
{
	m_pParaUI->m_txtIBlock_FreqEnd->setText(CheckDataMinMax(m_pParaUI->m_txtIBlock_FreqEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_FREQEND,m_pParaUI->m_txtIBlock_FreqEnd->text());
}
void QLowFreqILockItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);

	m_pParaUI->m_labIBlockSetting->setText(/*低电流闭锁值(A):*/g_sLangTxt_LowFreq_ILock + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	m_pParaUI->m_labIBlock_Var->setText(/*电流输出相*/g_sLangTxt_Native_CuroutputPhase +":");
	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(A):");

	m_pParaUI->groupBox_2->setTitle(/*递变参数*/g_sLangTxt_LowFreq_GradientPara);

	m_pParaUI->m_labIStart->setText(/*电流变化始值(A)*/g_sLangTxt_Native_CurrentChangeStartValue + "(A):");
	m_pParaUI->m_labIEnd->setText(/*电流变化终值(A):*/g_sLangTxt_Native_CurrentChangeEndValue + "(A):");
	m_pParaUI->m_labIStep->setText(/*电流变化步长(A))*/g_sLangTxt_Native_CurrentChangeStep + "(A):");
	m_pParaUI->m_labdfdt->setText(/*频率滑差(Hz/s))*/g_sLangTxt_Native_FreqSlip + "(Hz/s):");
	m_pParaUI->m_labFreqEnd->setText(/*频率变化终值(Hz))*/g_sLangTxt_Native_FreFinalValue + "(Hz):");
}
