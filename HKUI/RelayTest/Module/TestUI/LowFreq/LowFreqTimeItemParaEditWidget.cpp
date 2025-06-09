#include "LowFreqTimeItemParaEditWidget.h"
#include "ui_LowFreqTimeItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QLowFreqTimeItemParaEditWidget::QLowFreqTimeItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowFreqTimeItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QLowFreqTimeItemParaEditWidget::~QLowFreqTimeItemParaEditWidget()
{
	delete m_pParaUI;
}

void QLowFreqTimeItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QLowFreqTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowFreqTimeItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
// CExBaseList * QLowFreqTimeItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QLowFreqTimeItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowFreqTimeItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//动作时间
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RELERR);
	CheckForPresence(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRPOS);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRNEG);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FREQEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_DFDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RSLTEVAL);
}

void QLowFreqTimeItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
    //动作时间
	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING)
	{
		//m_pParaUI->m_txtActTime_TSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActTime_TSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_CUR)
	{
		m_pParaUI->m_txtActTime_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FSETTING)
	{
		//m_pParaUI->m_txtActTime_FSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActTime_FSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_HOlDTIME)
	{
		m_pParaUI->m_txtActTime_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RELERR)
	{
		m_pParaUI->m_txtActTime_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRPOS)
	{
		m_pParaUI->m_txtActTime_AbsErrPos->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRNEG)
	{
		m_pParaUI->m_txtActTime_AbsErrNeg->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FREQEND)
	{
		m_pParaUI->m_txtActTime_FreqEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_DFDT)
	{
		//m_pParaUI->m_txtActTime_dfdt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActTime_dfdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
}

//动作时间
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_TSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING, m_pParaUI->m_txtActTime_TSetting))
	{
		return;
	}
	m_pParaUI->m_txtActTime_TSetting->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_TSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING,m_pParaUI->m_txtActTime_TSetting->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_Cur_editingFinished()
{
	m_pParaUI->m_txtActTime_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_CUR,m_pParaUI->m_txtActTime_Cur->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_FSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FSETTING, m_pParaUI->m_txtActTime_FSetting))
	{
		return;
	}
	m_pParaUI->m_txtActTime_FSetting->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_FSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FSETTING,m_pParaUI->m_txtActTime_FSetting->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_HoldTime_editingFinished()
{
	m_pParaUI->m_txtActTime_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_HOlDTIME,m_pParaUI->m_txtActTime_HoldTime->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_RelErr_editingFinished()
{
	m_pParaUI->m_txtActTime_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RELERR,m_pParaUI->m_txtActTime_RelErr->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_AbsErrPos_editingFinished()
{
	m_pParaUI->m_txtActTime_AbsErrPos->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_AbsErrPos->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRPOS,m_pParaUI->m_txtActTime_AbsErrPos->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_AbsErrNeg_editingFinished()
{
	m_pParaUI->m_txtActTime_AbsErrNeg->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_AbsErrNeg->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRNEG,m_pParaUI->m_txtActTime_AbsErrNeg->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_FreqEnd_editingFinished()
{
	m_pParaUI->m_txtActTime_FreqEnd->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_FreqEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FREQEND,m_pParaUI->m_txtActTime_FreqEnd->text());
}
void QLowFreqTimeItemParaEditWidget::on_m_txtActTime_dfdt_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_DFDT, m_pParaUI->m_txtActTime_dfdt))
	{
		return;
	}
	m_pParaUI->m_txtActTime_dfdt->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_dfdt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_DFDT,m_pParaUI->m_txtActTime_dfdt->text());
}
void QLowFreqTimeItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);

	m_pParaUI->m_labTSetting->setText(/*动作时间定值(A):*/g_sLangTxt_Native_OpTimeSet + "(s):");
	m_pParaUI->m_labFSetting->setText(/*频率动作值(Hz):*/g_sLangTxt_Gradient_FreAValue + ":");

	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErrPos->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(s)+:");
	m_pParaUI->m_labAbsErrNeg->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(s)-:");

	m_pParaUI->groupBox_2->setTitle(/*频率变化范围及其变化率*/g_sLangTxt_LowFreq_FreqRangeRate);

	m_pParaUI->m_labFreqEnd->setText(/*频率变化终值(Hz))*/g_sLangTxt_Native_FreFinalValue + "(Hz):");
	m_pParaUI->m_labdfdt->setText(/*频率滑差(Hz/s))*/g_sLangTxt_Native_FreqSlip + "(Hz/s):");
	m_pParaUI->m_labCur->setText(/*电流*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");

}