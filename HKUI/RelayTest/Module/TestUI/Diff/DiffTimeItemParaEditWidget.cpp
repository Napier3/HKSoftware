#include "DiffTimeItemParaEditWidget.h"
#include "ui_DiffTimeItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"

QDiffTimeItemParaEditWidget::QDiffTimeItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QDiffTimeItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QDiffTimeItemParaEditWidget::~QDiffTimeItemParaEditWidget()
{
	delete m_pParaUI;
}

void QDiffTimeItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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
	emit sig_UpdateId(m_pParaUI->m_txtTime_Ir->text().toDouble());
	emit sig_UpdateDiffWiringWidget();
	//SetDatas(pSttMacroTest);
}

void QDiffTimeItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QDiffTimeItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
// CExBaseList * QDiffTimeItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QDiffTimeItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QDiffTimeItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTYPE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRPOS);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRNEG);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FREQ);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTIME);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RSLTEVAL);
}

void QDiffTimeItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTYPE)
	{
		m_pParaUI->m_cmbTime_FaultType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR)
	{
		m_pParaUI->m_txtTime_Ir->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID)
	{
		m_pParaUI->m_txtTime_Id->setText(CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//UpdateId(pData->m_strValue.toDouble());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRPOS)
	{
		m_pParaUI->m_txtTime_AbsErrPos->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtTime_AbsErrPos->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRNEG)
	{
		m_pParaUI->m_txtTime_AbsErrNeg->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtTime_AbsErrNeg->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RELERR)
	{
		m_pParaUI->m_txtTime_RelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtTime_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FREQ)
	{
		m_pParaUI->m_txtTime_Freq->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTIME)
	{
		m_pParaUI->m_txtTime_FaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
}
//动作时间
void QDiffTimeItemParaEditWidget::on_m_cmbTime_FaultType_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTYPE,strTmp);
	emit sig_UpdateDiffWiringWidget();
}
void QDiffTimeItemParaEditWidget::on_m_txtTime_Ir_editingFinished()
{
	m_pParaUI->m_txtTime_Ir->setText(CheckDataMinMax(m_pParaUI->m_txtTime_Ir->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR,m_pParaUI->m_txtTime_Ir->text());
	emit sig_UpdateDiffWiringWidget();
	emit sig_UpdateId(m_pParaUI->m_txtTime_Ir->text().toDouble());
}

void QDiffTimeItemParaEditWidget::UpdateId(double dId)
{
	m_pParaUI->m_txtTime_Id->setText(CheckDataMinMax(QString::number(dId), 999.999, 0, 3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID, m_pParaUI->m_txtTime_Id->text());
}

void QDiffTimeItemParaEditWidget::on_m_txtTime_AbsErrPos_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRPOS, m_pParaUI->m_txtTime_AbsErrPos))
	{
		return;
	}
	m_pParaUI->m_txtTime_AbsErrPos->setText(CheckDataMinMax(m_pParaUI->m_txtTime_AbsErrPos->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRPOS,m_pParaUI->m_txtTime_AbsErrPos->text());
}
void QDiffTimeItemParaEditWidget::on_m_txtTime_AbsErrNeg_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRNEG, m_pParaUI->m_txtTime_AbsErrNeg))
	{
		return;
	}
	m_pParaUI->m_txtTime_AbsErrNeg->setText(CheckDataMinMax(m_pParaUI->m_txtTime_AbsErrNeg->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ABSERRNEG,m_pParaUI->m_txtTime_AbsErrNeg->text());
}
void QDiffTimeItemParaEditWidget::on_m_txtTime_RelErr_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RELERR, m_pParaUI->m_txtTime_RelErr))
	{
		return;
	}
	m_pParaUI->m_txtTime_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtTime_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RELERR,m_pParaUI->m_txtTime_RelErr->text());
}
void QDiffTimeItemParaEditWidget::on_m_txtTime_Freq_editingFinished()
{
	m_pParaUI->m_txtTime_Freq->setText(CheckDataMinMax(m_pParaUI->m_txtTime_Freq->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FREQ,m_pParaUI->m_txtTime_Freq->text());
}
void QDiffTimeItemParaEditWidget::on_m_txtTime_FaultTime_editingFinished()
{
	m_pParaUI->m_txtTime_FaultTime->setText(CheckDataMinMax(m_pParaUI->m_txtTime_FaultTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTIME,m_pParaUI->m_txtTime_FaultTime->text());
}
void QDiffTimeItemParaEditWidget::UpdateMinaxis(int nMinaxis)//0:有名值(A) 1:标幺值(In)
{
	if (nMinaxis)
	{
		m_pParaUI->m_labTime_Ir->setText(/*制动电流*/g_sLangTxt_Native_ControlCurrent + "Ir(Ie):");
		m_pParaUI->m_labTime_Id->setText(/*差动电流*/g_sLangTxt_State_DifferentCur + "Id(Ie):");
	}
	else
	{
		m_pParaUI->m_labTime_Ir->setText(/*制动电流*/g_sLangTxt_Native_ControlCurrent + "Ir(A):");
		m_pParaUI->m_labTime_Id->setText(/*差动电流*/g_sLangTxt_State_DifferentCur + "Id(A):");
	}
}
void QDiffTimeItemParaEditWidget::InitUI()
{
	m_pParaUI->m_labTime_FaultType->setText(/*故障相别*/g_sLangTxt_Diff_FaultType);
	if (!m_pParaUI->m_labTime_FaultType->text().contains(":"))
	{
		m_pParaUI->m_labTime_FaultType->setText(m_pParaUI->m_labTime_FaultType->text() + ":");
	}
	m_pParaUI->m_labTime_Freq->setText(/*频率(Hz)*/g_sLangTxt_Frequency);
	if (!m_pParaUI->m_labTime_Freq->text().contains(":"))
	{
		m_pParaUI->m_labTime_Freq->setText(m_pParaUI->m_labTime_Freq->text() + ":");
	}
	m_pParaUI->m_labTime_FaultTime->setText(/*最大故障时间(s)*/g_sLangTxt_Diff_FaultTime);
	if (!m_pParaUI->m_labTime_FaultTime->text().contains(":"))
	{
		m_pParaUI->m_labTime_FaultTime->setText(m_pParaUI->m_labTime_FaultTime->text() + ":");
	}
	m_pParaUI->m_labTime_AbsErr->setText(/*绝对误差(%)*/g_sLangTxt_StateEstimate_AbsError + "(s)+:");
	m_pParaUI->m_labTime_AbsErr_2->setText(/*绝对误差(%)*/g_sLangTxt_StateEstimate_AbsError + "(s)-:");
	m_pParaUI->m_labTime_RelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent);
	if (!m_pParaUI->m_labTime_RelErr->text().contains(":"))
	{
		m_pParaUI->m_labTime_RelErr->setText(m_pParaUI->m_labTime_RelErr->text() + ":");
	}
}