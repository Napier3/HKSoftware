#include "LowFreqActItemParaEditWidget.h"
#include "ui_LowFreqActItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QLowFreqActItemParaEditWidget::QLowFreqActItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowFreqActItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QLowFreqActItemParaEditWidget::~QLowFreqActItemParaEditWidget()
{
	delete m_pParaUI;
}

void QLowFreqActItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QLowFreqActItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowFreqActItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
//CExBaseList * QLowFreqActItemParaEditWidget::GetMacroTestParaDatas_Inner()
//{
//    if(m_oSttMacroTest_Inner.GetCount() != 0)
//    {
//        return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//    }
//    return NULL;
//}
void QLowFreqActItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowFreqActItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//动作值
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_DVDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RSLTEVAL);
}


void QLowFreqActItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
    //动作值
	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE)
	{
		//m_pParaUI->m_txtActValue_ActValue->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_ActValue->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_CUR)
	{
		//m_pParaUI->m_txtActValue_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_Cur->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_HOlDTIME)
	{
		m_pParaUI->m_txtActValue_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RELERR)
	{
		m_pParaUI->m_txtActValue_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ABSERR)
	{
		m_pParaUI->m_txtActValue_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART)
	{
		//m_pParaUI->m_txtActValue_FreqStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_FreqStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND)
	{
		//m_pParaUI->m_txtActValue_FreqEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_FreqEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP)
	{
		//m_pParaUI->m_txtActValue_FreqStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_FreqStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_DVDT)
	{
		//m_pParaUI->m_txtActValue_dvdt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtActValue_dvdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
}

void QLowFreqActItemParaEditWidget::on_m_txtActValue_ActValue_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE, m_pParaUI->m_txtActValue_ActValue))
	{
		return;
	}
	m_pParaUI->m_txtActValue_ActValue->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_ActValue->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE,m_pParaUI->m_txtActValue_ActValue->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_Cur_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_CUR, m_pParaUI->m_txtActValue_Cur))
	{
		return;
	}
	m_pParaUI->m_txtActValue_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_CUR,m_pParaUI->m_txtActValue_Cur->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_HoldTime_editingFinished()
{
	m_pParaUI->m_txtActValue_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_HOlDTIME,m_pParaUI->m_txtActValue_HoldTime->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_RelErr_editingFinished()
{
	m_pParaUI->m_txtActValue_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RELERR,m_pParaUI->m_txtActValue_RelErr->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_AbsErr_editingFinished()		
{
	m_pParaUI->m_txtActValue_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ABSERR,m_pParaUI->m_txtActValue_AbsErr->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_FreqStart_editingFinished()	
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART, m_pParaUI->m_txtActValue_FreqStart))
	{
		return;
	}
	m_pParaUI->m_txtActValue_FreqStart->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_FreqStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART,m_pParaUI->m_txtActValue_FreqStart->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_FreqEnd_editingFinished()		
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND, m_pParaUI->m_txtActValue_FreqEnd))
	{
		return;
	}
	m_pParaUI->m_txtActValue_FreqEnd->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_FreqEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND,m_pParaUI->m_txtActValue_FreqEnd->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_FreqStep_editingFinished()		
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP, m_pParaUI->m_txtActValue_FreqStep))
	{
		return;
	}
	m_pParaUI->m_txtActValue_FreqStep->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_FreqStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP,m_pParaUI->m_txtActValue_FreqStep->text());
}
void QLowFreqActItemParaEditWidget::on_m_txtActValue_dvdt_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_DVDT, m_pParaUI->m_txtActValue_dvdt))
	{
		return;
	}
	m_pParaUI->m_txtActValue_dvdt->setText(CheckDataMinMax(m_pParaUI->m_txtActValue_dvdt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_DVDT,m_pParaUI->m_txtActValue_dvdt->text());
}
void QLowFreqActItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);

	m_pParaUI->m_labActValue->setText(/*动作值*/g_sLangTxt_State_ActionValue + "(Hz):");
	m_pParaUI->m_labCur->setText(/*电流*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");

	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent);
	if (!m_pParaUI->m_labRelErr->text().contains(":"))
	{
		m_pParaUI->m_labRelErr->setText(m_pParaUI->m_labRelErr->text() + ":");
	}
	m_pParaUI->m_labAbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(Hz):");

	m_pParaUI->groupBox_2->setTitle(/*频率变化范围及其变化率*/g_sLangTxt_LowFreq_FreqRangeRate);

	m_pParaUI->m_labFreqStart->setText(/*频率起始值(Hz)*/g_sLangTxt_LowFreq_FreqBegin + ":");
	m_pParaUI->m_labFreqEnd->setText(/*频率结束值(Hz)*/g_sLangTxt_LowFreq_FreqEnd + ":");
	m_pParaUI->m_labFreqStep->setText(/*频率变化步长(Hz)*/g_sLangTxt_Native_FreChangeStep + "(Hz):");
	m_pParaUI->m_labdvdt->setText(/*频率滑差(Hz/s))*/g_sLangTxt_Native_FreqSlip + "(Hz/s):");
}