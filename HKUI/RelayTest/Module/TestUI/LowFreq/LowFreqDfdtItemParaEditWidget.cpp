#include "LowFreqDfdtItemParaEditWidget.h"
#include "ui_LowFreqDfdtItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QLowFreqDfdtItemParaEditWidget::QLowFreqDfdtItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowFreqDfdtItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QLowFreqDfdtItemParaEditWidget::~QLowFreqDfdtItemParaEditWidget()
{
	delete m_pParaUI;
}

void QLowFreqDfdtItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{//20240620 luozibing �������� �������������ݸ��µ�ҳ��
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

void QLowFreqDfdtItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowFreqDfdtItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

//CExBaseList * QLowFreqDfdtItemParaEditWidget::GetMacroTestParaDatas_Inner()
//{
//    if(m_oSttMacroTest_Inner.GetCount() != 0)
//    {
//        return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//    }
//    return NULL;
//}

void QLowFreqDfdtItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowFreqDfdtItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//�������ֵ
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_FREQEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RSLTEVAL);
}

void QLowFreqDfdtItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//�������ֵ
	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_CUR)
	{
		m_pParaUI->m_txtSlipTrip_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_HOlDTIME)
	{
		m_pParaUI->m_txtSlipTrip_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RELERR)
	{
		m_pParaUI->m_txtSlipTrip_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_ABSERR)
	{
		m_pParaUI->m_txtSlipTrip_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_FREQEND)
	{
		//m_pParaUI->m_txtSlipTrip_FreqEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_FreqEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtEnd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP)
	{
		//m_pParaUI->m_txtSlipTrip_dfdtStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtSlipTrip_dfdtStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
}

//�������ֵ
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_dfdtSetting_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING, m_pParaUI->m_txtSlipTrip_dfdtSetting))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtSetting->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING,m_pParaUI->m_txtSlipTrip_dfdtSetting->text());
}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_Cur_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_CUR,m_pParaUI->m_txtSlipTrip_Cur->text());

}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_HoldTime_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_HOlDTIME,m_pParaUI->m_txtSlipTrip_HoldTime->text());
}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_RelErr_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RELERR,m_pParaUI->m_txtSlipTrip_RelErr->text());
}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_AbsErr_editingFinished()
{
	m_pParaUI->m_txtSlipTrip_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_ABSERR,m_pParaUI->m_txtSlipTrip_AbsErr->text());

}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_FreqEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_FREQEND, m_pParaUI->m_txtSlipTrip_FreqEnd))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_FreqEnd->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_FreqEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_FREQEND,m_pParaUI->m_txtSlipTrip_FreqEnd->text());
}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_dfdtStart_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART, m_pParaUI->m_txtSlipTrip_dfdtStart))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtStart->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART,m_pParaUI->m_txtSlipTrip_dfdtStart->text());
}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_dfdtEnd_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND, m_pParaUI->m_txtSlipTrip_dfdtEnd))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtEnd->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND,m_pParaUI->m_txtSlipTrip_dfdtEnd->text());
}
void QLowFreqDfdtItemParaEditWidget::on_m_txtSlipTrip_dfdtStep_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP, m_pParaUI->m_txtSlipTrip_dfdtStep))
	{
		return;
	}
	m_pParaUI->m_txtSlipTrip_dfdtStep->setText(CheckDataMinMax(m_pParaUI->m_txtSlipTrip_dfdtStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP,m_pParaUI->m_txtSlipTrip_dfdtStep->text());
}
void QLowFreqDfdtItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*����ֵ*/g_sLangTxt_State_SettingValue);
	m_pParaUI->m_labdfdtSetting->setText(/*����ֵ*/g_sLangTxt_LowFreq_dfdtSetting + "(Hz/s):");
	m_pParaUI->m_labCur->setText(/*����*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*����ʱ��*/g_sLangTxt_Native_KeepTime + "(s):");
	m_pParaUI->m_labRelErr->setText(/*������(%)*/g_sLangTxt_StateEstimate_RelError_Percent+":");
	m_pParaUI->m_labAbsErr->setText(/*�������*/g_sLangTxt_StateEstimate_AbsError + "(Hz/s):");
	m_pParaUI->groupBox_2->setTitle(/*�ݱ����*/g_sLangTxt_LowFreq_GradientPara);
	m_pParaUI->m_labFreqEnd->setText(/*Ƶ�ʱ仯��ֵ(Hz)*/g_sLangTxt_Native_FreFinalValue + "(Hz):");
	m_pParaUI->m_labdfdtStart->setText(/*����仯ʼֵ(Hz/s)*/g_sLangTxt_LowFreq_dfdtBegin + "(Hz/s):");
	m_pParaUI->m_labdfdtEnd->setText(/*����仯��ֵ(Hz/s))*/g_sLangTxt_LowFreq_dfdtEnd + "(Hz/s):");
	m_pParaUI->m_labdfdtStep->setText(/*����仯����(Hz/s))*/g_sLangTxt_LowFreq_dfdtStep + "(Hz/s):");
}