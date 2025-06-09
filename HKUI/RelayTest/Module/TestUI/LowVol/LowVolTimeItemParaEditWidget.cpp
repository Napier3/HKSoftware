#include "LowVolTimeItemParaEditWidget.h"
#include "ui_LowVolTimeItemParaEditWidget.h"

QLowVolTimeItemParaEditWidget::QLowVolTimeItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QLowVolTimeItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	m_pTestParaDatas = NULL;
	InitUI();
}

QLowVolTimeItemParaEditWidget::~QLowVolTimeItemParaEditWidget()
{
	delete m_pParaUI;
}


void QLowVolTimeItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QLowVolTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QLowVolTimeItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pTestParaDatas != NULL)
	{
		return m_pTestParaDatas;
	}
	return NULL;
}
// CExBaseList * QLowVolTimeItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QLowVolTimeItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QLowVolTimeItemParaEditWidget::USetModeChange(int nUSetMode)
{
	if (nUSetMode == 0)
	{
		CString strText = /*相电压变化终值(V):*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowFreq_EndVal + "(V):";
		m_pParaUI->m_labVEnd->setText(strText);
		strText = /*"相电压滑差(V/s):";*/g_sLangTxt_LowFreq_PhaseV + g_sLangTxt_LowVol_dVdt + "(V/s):";
		m_pParaUI->m_labDvdt->setText(strText);
	}
	else
	{
		CString strText = /*线电压变化终值(V):*/g_sLangTxt_linevolt + g_sLangTxt_LowFreq_EndVal + "(V) : ";
		m_pParaUI->m_labVEnd->setText(strText);
		strText = /*"相电压滑差(V/s):";*/g_sLangTxt_linevolt + g_sLangTxt_LowVol_dVdt + "(V/s):";
		m_pParaUI->m_labDvdt->setText(strText);
	}
}
void QLowVolTimeItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//动作时间
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_TSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_CUR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_FSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_HOlDTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_VEND);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_DVDT);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RSLTEVAL);
}

void QLowVolTimeItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
    //动作时间
	if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_TSETTING)
	{
		m_pParaUI->m_txtActTime_TSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_CUR)
	{
		m_pParaUI->m_txtActTime_Cur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_FSETTING)
	{
		m_pParaUI->m_txtActTime_FSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_HOlDTIME)
	{
		m_pParaUI->m_txtActTime_HoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR)
	{
		m_pParaUI->m_txtActTime_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS)
	{
		m_pParaUI->m_txtActTime_AbsErrPos->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG)
	{
		m_pParaUI->m_txtActTime_AbsErrNeg->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_VEND)
	{
		m_pParaUI->m_txtActTime_VEnd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_DVDT)
	{
		m_pParaUI->m_txtActTime_dVdt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_USETMODE)
	{
		int nUSetMode = pData->m_strValue.toFloat();
		USetModeChange(nUSetMode);
	}
}

//动作时间
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_TSetting_editingFinished()
{
	m_pParaUI->m_txtActTime_TSetting->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_TSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_TSETTING,m_pParaUI->m_txtActTime_TSetting->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_Cur_editingFinished()
{
	m_pParaUI->m_txtActTime_Cur->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_Cur->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_CUR,m_pParaUI->m_txtActTime_Cur->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_FSetting_editingFinished()
{
	m_pParaUI->m_txtActTime_FSetting->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_FSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_FSETTING,m_pParaUI->m_txtActTime_FSetting->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_HoldTime_editingFinished()
{
	m_pParaUI->m_txtActTime_HoldTime->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_HoldTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_HOlDTIME,m_pParaUI->m_txtActTime_HoldTime->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_RelErr_editingFinished()
{
	m_pParaUI->m_txtActTime_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR,m_pParaUI->m_txtActTime_RelErr->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_AbsErrPos_editingFinished()
{
	m_pParaUI->m_txtActTime_AbsErrPos->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_AbsErrPos->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS, m_pParaUI->m_txtActTime_AbsErrPos->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_AbsErrNeg_editingFinished()
{
	m_pParaUI->m_txtActTime_AbsErrNeg->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_AbsErrNeg->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG,m_pParaUI->m_txtActTime_AbsErrNeg->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_VEnd_editingFinished()
{
	m_pParaUI->m_txtActTime_VEnd->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_VEnd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_VEND,m_pParaUI->m_txtActTime_VEnd->text());
}
void QLowVolTimeItemParaEditWidget::on_m_txtActTime_dVdt_editingFinished()
{
	m_pParaUI->m_txtActTime_dVdt->setText(CheckDataMinMax(m_pParaUI->m_txtActTime_dVdt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_DVDT,m_pParaUI->m_txtActTime_dVdt->text());
}
void QLowVolTimeItemParaEditWidget::InitUI()
{
	m_pParaUI->groupBox->setTitle(/*整定值*/g_sLangTxt_State_SettingValue);
	m_pParaUI->m_labTSetting->setText(/*动作时间定值(A):*/g_sLangTxt_Native_OpTimeSet + "(s):");
	m_pParaUI->m_labVSetting->setText(/*电压动作值(V):*/g_sLangTxt_Gradient_VActionValue + ":");
	m_pParaUI->m_labRelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent + ":");
	m_pParaUI->m_labAbsErrPos->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(s)+:");
	m_pParaUI->m_labAbsErrNeg->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(s)-:");
	m_pParaUI->groupBox_2->setTitle(/*电压变化范围及其变化率*/g_sLangTxt_LowVol_FreqRangeRate);
	m_pParaUI->m_labCur->setText(/*电流*/g_sLangTxt_Current + "(A):");
	m_pParaUI->m_labHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
}