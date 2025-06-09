#include "DiffRateItemParaEditWidget.h"
#include "ui_DiffRateItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QDiffRateItemParaEditWidget::QDiffRateItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QDiffRateItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	m_dBeginVal = 0;
	m_dEndVal = 0;
	InitUI();
}

QDiffRateItemParaEditWidget::~QDiffRateItemParaEditWidget()
{
	delete m_pParaUI;
}

void QDiffRateItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

	CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
	SetValueToPage(pData);

	while (pos!= NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->GetNext(pos);
		SetValueToPage(pData);
	}
	emit sig_UpdateId(m_pParaUI->m_txtRate_Ir->text().toDouble());
	emit sig_UpdateDiffWiringWidget();
	//SetDatas(pSttMacroTest);
}

void QDiffRateItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QDiffRateItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
// CExBaseList * QDiffRateItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QDiffRateItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QDiffRateItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_STEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FREQ);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RELERR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RSLTEVAL);

}
void QDiffRateItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE)
	{
		m_pParaUI->m_cmbRate_FaultType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL)
	{
		m_dBeginVal = pData->m_strValue.toDouble();
		m_pParaUI->m_txtRate_BeginVal->setText(CheckDataMinMax(QString::number(pData->m_strValue.toDouble() / m_pParaUI->m_txtRate_IdSetting->text().toDouble() * 100), 200, 100, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL)
	{
		m_dEndVal = pData->m_strValue.toDouble();
		m_pParaUI->m_txtRate_EndVal->setText(CheckDataMinMax(QString::number(pData->m_strValue.toDouble() / m_pParaUI->m_txtRate_IdSetting->text().toDouble() * 100), 100, 0, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_STEP)
	{
		m_pParaUI->m_txtRate_Step->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FREQ)
	{
		m_pParaUI->m_txtRate_Freq->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR)
	{
		m_pParaUI->m_txtRate_Ir->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING)
	{
		//UpdateId(pData->m_strValue.toDouble());
		m_pParaUI->m_txtRate_IdSetting->setText(CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING, m_pParaUI->m_txtRate_IdSetting->text());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME)
	{
		m_pParaUI->m_txtRate_FaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ABSERR)
	{
		m_pParaUI->m_txtRate_AbsErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtRate_AbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RELERR)
	{
		m_pParaUI->m_txtRate_RelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtRate_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
}

void QDiffRateItemParaEditWidget::on_m_cmbRate_FaultType_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE,strTmp);
	emit sig_UpdateDiffWiringWidget();
}
void QDiffRateItemParaEditWidget::on_m_txtRate_BeginVal_editingFinished()
{
	m_pParaUI->m_txtRate_BeginVal->setText(CheckDataMinMax(m_pParaUI->m_txtRate_BeginVal->text(),200,100,1));
	m_dBeginVal = m_pParaUI->m_txtRate_BeginVal->text().toDouble() * m_pParaUI->m_txtRate_IdSetting->text().toDouble() / 100;
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL, QString::number(m_dBeginVal));
}
void QDiffRateItemParaEditWidget::on_m_txtRate_EndVal_editingFinished()
{
	m_pParaUI->m_txtRate_EndVal->setText(CheckDataMinMax(m_pParaUI->m_txtRate_EndVal->text(),100,0,1));
	m_dEndVal = m_pParaUI->m_txtRate_EndVal->text().toDouble() * m_pParaUI->m_txtRate_IdSetting->text().toDouble() / 100;
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL, QString::number(m_dEndVal));
}
void QDiffRateItemParaEditWidget::on_m_txtRate_Step_editingFinished()
{
	m_pParaUI->m_txtRate_Step->setText(CheckDataMinMax(m_pParaUI->m_txtRate_Step->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_STEP,m_pParaUI->m_txtRate_Step->text());
}
void QDiffRateItemParaEditWidget::on_m_txtRate_Freq_editingFinished()
{
	m_pParaUI->m_txtRate_Freq->setText(CheckDataMinMax(m_pParaUI->m_txtRate_Freq->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FREQ,m_pParaUI->m_txtRate_Freq->text());
}
void QDiffRateItemParaEditWidget::on_m_txtRate_Ir_editingFinished()
{
	m_pParaUI->m_txtRate_Ir->setText(CheckDataMinMax(m_pParaUI->m_txtRate_Ir->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR,m_pParaUI->m_txtRate_Ir->text());
	emit sig_UpdateId(m_pParaUI->m_txtRate_Ir->text().toDouble());
	emit sig_UpdateDiffWiringWidget();
}

void QDiffRateItemParaEditWidget::UpdateId(double dId, double dMaxdId)
{
	m_pParaUI->m_txtRate_IdSetting->setText(CheckDataMinMax(QString::number(dId), 999.999, 0, 3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING, m_pParaUI->m_txtRate_IdSetting->text());
	if (m_dBeginVal > dMaxdId)
	{
		m_dBeginVal = dMaxdId;
		UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL, QString::number(m_dBeginVal));
	}
	m_pParaUI->m_txtRate_BeginVal->setText(CheckDataMinMax(QString::number(m_dBeginVal / m_pParaUI->m_txtRate_IdSetting->text().toDouble() * 100), 200, 100, 1));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL, QString::number(m_pParaUI->m_txtRate_BeginVal->text().toDouble() / 100 * m_pParaUI->m_txtRate_IdSetting->text().toDouble()));
	m_pParaUI->m_txtRate_EndVal->setText(CheckDataMinMax(QString::number(m_dEndVal / m_pParaUI->m_txtRate_IdSetting->text().toDouble() * 100), 100, 0, 1));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL, QString::number(m_pParaUI->m_txtRate_EndVal->text().toDouble()/100 * m_pParaUI->m_txtRate_IdSetting->text().toDouble()));
}
void QDiffRateItemParaEditWidget::on_m_txtRate_FaultTime_editingFinished()
{
	m_pParaUI->m_txtRate_FaultTime->setText(CheckDataMinMax(m_pParaUI->m_txtRate_FaultTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME,m_pParaUI->m_txtRate_FaultTime->text());
}
void QDiffRateItemParaEditWidget::on_m_txtRate_AbsErr_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ABSERR, m_pParaUI->m_txtRate_AbsErr))
	{
		return;
	}
	m_pParaUI->m_txtRate_AbsErr->setText(CheckDataMinMax(m_pParaUI->m_txtRate_AbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ABSERR,m_pParaUI->m_txtRate_AbsErr->text());
}
void QDiffRateItemParaEditWidget::on_m_txtRate_RelErr_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RELERR, m_pParaUI->m_txtRate_RelErr))
	{
		return;
	}
	m_pParaUI->m_txtRate_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtRate_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RELERR,m_pParaUI->m_txtRate_RelErr->text());
}
void QDiffRateItemParaEditWidget::UpdateMinaxis(int nMinaxis)//0:有名值(A) 1:标幺值(In)
{
	if (nMinaxis)
	{
		m_pParaUI->m_labRate_Step->setText(/*测试精度*/g_sLangTxt_Native_TestPrecision + "(Ie):");
		m_pParaUI->m_labRate_Ir->setText(/*制动电流*/g_sLangTxt_Native_ControlCurrent + "Ir(Ie):");
		m_pParaUI->m_labRate_IdSetting->setText(/*差动理论值*/g_sLangTxt_Diff_IdSetting + "Id(Ie):");
		m_pParaUI->m_labRate_AbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError+"(Ie):");
	}
	else
	{
		m_pParaUI->m_labRate_Step->setText(/*测试精度*/g_sLangTxt_Native_TestPrecision + "(A):");
		m_pParaUI->m_labRate_Ir->setText(/*制动电流*/g_sLangTxt_Native_ControlCurrent + "Ir(A):");
		m_pParaUI->m_labRate_IdSetting->setText(/*差动理论值*/g_sLangTxt_Diff_IdSetting + "Id(A):");
		m_pParaUI->m_labRate_AbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(A):");
	}
}
double QDiffRateItemParaEditWidget::GetBeginValText()
{
	return m_pParaUI->m_txtRate_BeginVal->text().toDouble();
}
void QDiffRateItemParaEditWidget::InitUI()
{
	m_pParaUI->m_labRate_FaultType->setText(/*故障相别*/g_sLangTxt_Diff_FaultType);
	if (!m_pParaUI->m_labRate_FaultType->text().contains(":"))
	{
		m_pParaUI->m_labRate_FaultType->setText(m_pParaUI->m_labRate_FaultType->text() + ":");
	}

	m_pParaUI->m_labRate_BeginVal->setText(/*搜索上限*/g_sLangTxt_Diff_UpperLimit);
	if (!m_pParaUI->m_labRate_BeginVal->text().contains("(%)"))
	{
		m_pParaUI->m_labRate_BeginVal->setText(m_pParaUI->m_labRate_BeginVal->text() + "(%)");
	}
	if (!m_pParaUI->m_labRate_BeginVal->text().contains(":"))
	{
		m_pParaUI->m_labRate_BeginVal->setText(m_pParaUI->m_labRate_BeginVal->text() + ":");
	}
	m_pParaUI->m_labRate_EndVal->setText(/*搜索下限*/g_sLangTxt_Diff_LowLimit);
	if (!m_pParaUI->m_labRate_EndVal->text().contains("(%)"))
	{
		m_pParaUI->m_labRate_EndVal->setText(m_pParaUI->m_labRate_EndVal->text() + "(%)");
	}
	if (!m_pParaUI->m_labRate_EndVal->text().contains(":"))
	{
		m_pParaUI->m_labRate_EndVal->setText(m_pParaUI->m_labRate_EndVal->text() + ":");
	}
	m_pParaUI->m_labRate_Freq->setText(/*频率(Hz)*/g_sLangTxt_Frequency);
	if (!m_pParaUI->m_labRate_Freq->text().contains(":"))
	{
		m_pParaUI->m_labRate_Freq->setText(m_pParaUI->m_labRate_Freq->text() + ":");
	}
	m_pParaUI->m_labRate_FaultTime->setText(/*最大故障时间(s)*/g_sLangTxt_Diff_FaultTime);
	if (!m_pParaUI->m_labRate_FaultTime->text().contains(":"))
	{
		m_pParaUI->m_labRate_FaultTime->setText(m_pParaUI->m_labRate_FaultTime->text() + ":");
	}
	m_pParaUI->m_labRate_RelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent);
	if (!m_pParaUI->m_labRate_RelErr->text().contains(":"))
	{
		m_pParaUI->m_labRate_RelErr->setText(m_pParaUI->m_labRate_RelErr->text() + ":");
	}
}