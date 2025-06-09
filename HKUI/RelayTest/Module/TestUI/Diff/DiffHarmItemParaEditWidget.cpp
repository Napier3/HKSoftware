#include "DiffHarmItemParaEditWidget.h"
#include "ui_DiffHarmItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"
QDiffHarmItemParaEditWidget::QDiffHarmItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),
m_pParaUI(new Ui::QDiffHarmItemParaEditWidget)
{
	m_pParaUI->setupUi(this);
	InitUI();
}

QDiffHarmItemParaEditWidget::~QDiffHarmItemParaEditWidget()
{
	delete m_pParaUI;
}

void QDiffHarmItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

	CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RATEHARMSET);
	SetValueToPage(pData);

	while (pos!= NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->GetNext(pos);
		SetValueToPage(pData);
	}
	emit sig_UpdateDiffWiringWidget();
	//SetDatas(pSttMacroTest);
}

void QDiffHarmItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

CExBaseList * QDiffHarmItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
// CExBaseList * QDiffHarmItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }
void QDiffHarmItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}

void QDiffHarmItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTYPE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_STEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_OUTSIDE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRPOS);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRNEG);
	CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RELERR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RSLTEVAL);
}


void QDiffHarmItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
    //动作时间
	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTYPE)
	{
		m_pParaUI->m_cmbHarm_FaultType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX)
	{
		if (pData->m_strValue.toInt() < 4)
		{
			m_pParaUI->m_cmbHarm_HarmIndex->setCurrentIndex(pData->m_strValue.toInt());
			m_pParaUI->m_txtHarm_CustomHarmIndex->setEnabled(false);
		}
		else
		{
			m_pParaUI->m_cmbHarm_HarmIndex->setCurrentIndex(m_pParaUI->m_cmbHarm_HarmIndex->count()-1);
			m_pParaUI->m_txtHarm_CustomHarmIndex->setEnabled(true);
		}
		m_pParaUI->m_txtHarm_CustomHarmIndex->setText(QString::number(pData->m_strValue.toInt() + 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID)
	{
		m_pParaUI->m_txtHarm_Id->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL)
	{
		m_pParaUI->m_txtHarm_BeginVal->setText(CheckDataMinMax(QString::number(pData->m_strValue.toDouble() / m_fHarmCoef), 100, 0, 1));
		//m_pParaUI->m_txtHarm_BeginVal->setText(CheckDataMinMax(pData->m_strValue, 100, 0, 1));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL)
	{
		m_pParaUI->m_txtHarm_EndVal->setText(CheckDataMinMax(QString::number(pData->m_strValue.toDouble() / m_fHarmCoef), 200, 100, 1));
		//m_pParaUI->m_txtHarm_EndVal->setText(CheckDataMinMax(pData->m_strValue, 100, 0, 1));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_STEP)
	{
		m_pParaUI->m_txtHarm_Step->setText(CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_OUTSIDE)
	{
		m_pParaUI->m_cmbHarm_OutSide->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTIME)
	{
		m_pParaUI->m_txtHarm_FaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRPOS)
	{
		m_pParaUI->m_txtHarm_AbsErrPos->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtHarm_AbsErrPos->setText(CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRNEG)
	{
		m_pParaUI->m_txtHarm_AbsErrNeg->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtHarm_AbsErrNeg->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RELERR)
	{
		m_pParaUI->m_txtHarm_RelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
		//m_pParaUI->m_txtHarm_RelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RATEHARMSET)
	{
		m_fHarmCoef = pData->m_strValue.toFloat();
	}
}
//谐波制动搜索
void QDiffHarmItemParaEditWidget::on_m_cmbHarm_FaultType_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTYPE,strTmp);
	emit sig_UpdateDiffWiringWidget();
}
void QDiffHarmItemParaEditWidget::on_m_cmbHarm_HarmIndex_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX,strTmp);

	if (index < 4)
	{
		m_pParaUI->m_txtHarm_CustomHarmIndex->setEnabled(false);
	}
	else
	{
		m_pParaUI->m_txtHarm_CustomHarmIndex->setEnabled(true);
	}
	m_pParaUI->m_txtHarm_CustomHarmIndex->setText(QString::number(index+2));
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_Id_editingFinished()
{
	m_pParaUI->m_txtHarm_Id->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_Id->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID,m_pParaUI->m_txtHarm_Id->text());
	emit sig_UpdateDiffWiringWidget();
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_BeginVal_editingFinished()
{
	m_pParaUI->m_txtHarm_BeginVal->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_BeginVal->text(), 100, 0, 1));
	double dBeginVal = m_pParaUI->m_txtHarm_BeginVal->text().toDouble()*m_fHarmCoef ;
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL, QString::number(dBeginVal));
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_EndVal_editingFinished()
{
	m_pParaUI->m_txtHarm_EndVal->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_EndVal->text(), 200,100, 1));
	double dEndVal = m_pParaUI->m_txtHarm_EndVal->text().toDouble()*m_fHarmCoef;
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL, QString::number(dEndVal));
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_Step_editingFinished()
{
	m_pParaUI->m_txtHarm_Step->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_Step->text(), 999.999, 0, 3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_STEP, m_pParaUI->m_txtHarm_Step->text());
}
void QDiffHarmItemParaEditWidget::on_m_cmbHarm_OutSide_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_OUTSIDE,strTmp);
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_FaultTime_editingFinished()
{
	m_pParaUI->m_txtHarm_FaultTime->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_FaultTime->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_FAULTTIME,m_pParaUI->m_txtHarm_FaultTime->text());
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_AbsErrPos_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRPOS, m_pParaUI->m_txtHarm_AbsErrPos))
	{
		return;
	}
	m_pParaUI->m_txtHarm_AbsErrPos->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_AbsErrPos->text(), 999.999, 0, 3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRPOS, m_pParaUI->m_txtHarm_AbsErrPos->text());
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_AbsErrNeg_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRNEG, m_pParaUI->m_txtHarm_AbsErrNeg))
	{
		return;
	}
	m_pParaUI->m_txtHarm_AbsErrNeg->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_AbsErrNeg->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ABSERRNEG, m_pParaUI->m_txtHarm_AbsErrNeg->text());
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_RelErr_editingFinished()
{
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RELERR, m_pParaUI->m_txtHarm_RelErr))
	{
		return;
	}
	m_pParaUI->m_txtHarm_RelErr->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_RelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RELERR,m_pParaUI->m_txtHarm_RelErr->text());
}
void QDiffHarmItemParaEditWidget::on_m_txtHarm_CustomHarmIndex_editingFinished()
{
	m_pParaUI->m_txtHarm_CustomHarmIndex->setText(CheckDataMinMax(m_pParaUI->m_txtHarm_CustomHarmIndex->text(), 10, 2, 0));
	UpdatePara(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX, QString::number(m_pParaUI->m_txtHarm_CustomHarmIndex->text().toInt()-2));
}
void QDiffHarmItemParaEditWidget::UpdateMinaxis(int nMinaxis)//0:有名值(A) 1:标幺值(In)
{
	if (nMinaxis)
	{
		m_pParaUI->m_labHarm_Id->setText(/*差动电流*/g_sLangTxt_State_DifferentCur + "(Ie):");
	}
	else
	{
		m_pParaUI->m_labHarm_Id->setText(/*差动电流*/g_sLangTxt_State_DifferentCur + "(A):");
	}
}
void QDiffHarmItemParaEditWidget::InitUI()
{
	m_pParaUI->m_labHarm_FaultType->setText(/*故障相别*/g_sLangTxt_Diff_FaultType);
	if (!m_pParaUI->m_labHarm_FaultType->text().contains(":"))
	{
		m_pParaUI->m_labHarm_FaultType->setText(m_pParaUI->m_labHarm_FaultType->text() + ":");
	}
	m_pParaUI->m_labHarm_HarmIndex->setText(/*谐波次数*/g_sLangTxt_Native_harmonicOrder);
	if (!m_pParaUI->m_labHarm_HarmIndex->text().contains(":"))
	{
		m_pParaUI->m_labHarm_HarmIndex->setText(m_pParaUI->m_labHarm_HarmIndex->text() + ":");
	}
	m_pParaUI->m_cmbHarm_HarmIndex->addItems(QStringList() << "2" << "3" << "4" << "5" <</*自定义*/g_sLangTxt_Diff_Custom);
	m_pParaUI->m_labHarm_HarmIndex_2->setText(/*自定义谐波次数*/g_sLangTxt_Diff_CustomHarmIndex);
	if (!m_pParaUI->m_labHarm_HarmIndex_2->text().contains(":"))
	{
		m_pParaUI->m_labHarm_HarmIndex_2->setText(m_pParaUI->m_labHarm_HarmIndex_2->text() + ":");
	}
	m_pParaUI->m_labHarm_BeginVal->setText(/*搜索始值*/g_sLangTxt_Diff_BeginVal);
	if (!m_pParaUI->m_labHarm_BeginVal->text().contains("(%)"))
	{
		m_pParaUI->m_labHarm_BeginVal->setText(m_pParaUI->m_labHarm_BeginVal->text() + "(%)");
	}
	if (!m_pParaUI->m_labHarm_BeginVal->text().contains(":"))
	{
		m_pParaUI->m_labHarm_BeginVal->setText(m_pParaUI->m_labHarm_BeginVal->text() + ":");
	}
	m_pParaUI->m_labHarm_EndVal->setText(/*搜索终值*/g_sLangTxt_Diff_EndVal);
	if (!m_pParaUI->m_labHarm_EndVal->text().contains("(%)"))
	{
		m_pParaUI->m_labHarm_EndVal->setText(m_pParaUI->m_labHarm_EndVal->text() + "(%)");
	}
	if (!m_pParaUI->m_labHarm_EndVal->text().contains(":"))
	{
		m_pParaUI->m_labHarm_EndVal->setText(m_pParaUI->m_labHarm_EndVal->text() + ":");
	}
	m_pParaUI->m_labHarm_Step->setText(/*测试精度*/g_sLangTxt_Native_TestPrecision);
	if (!m_pParaUI->m_labHarm_Step->text().contains("(Ixf/Id)"))
	{
		m_pParaUI->m_labHarm_Step->setText(m_pParaUI->m_labHarm_Step->text() + "(Ixf/Id)");
	}
	if (!m_pParaUI->m_labHarm_Step->text().contains(":"))
	{
		m_pParaUI->m_labHarm_Step->setText(m_pParaUI->m_labHarm_Step->text() + ":");
	}
	m_pParaUI->m_labHarm_OutSide->setText(/*谐波输出侧*/g_sLangTxt_Diff_HarmOutSide);
	if (!m_pParaUI->m_labHarm_OutSide->text().contains(":"))
	{
		m_pParaUI->m_labHarm_OutSide->setText(m_pParaUI->m_labHarm_OutSide->text() + ":");
	}
	m_pParaUI->m_labHarm_FaultTime->setText(/*最大故障时间(s)*/g_sLangTxt_Diff_FaultTime);
	if (!m_pParaUI->m_labHarm_FaultTime->text().contains(":"))
	{
		m_pParaUI->m_labHarm_FaultTime->setText(m_pParaUI->m_labHarm_FaultTime->text() + ":");
	}
	m_pParaUI->m_labHarm_AbsErr->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(s)+:");
	m_pParaUI->m_labHarm_AbsErrNeg->setText(/*绝对误差*/g_sLangTxt_StateEstimate_AbsError + "(s)-:");
	m_pParaUI->m_labHarm_RelErr->setText(/*相对误差(%)*/g_sLangTxt_StateEstimate_RelError_Percent);
	if (!m_pParaUI->m_labHarm_RelErr->text().contains(":"))
	{
		m_pParaUI->m_labHarm_RelErr->setText(m_pParaUI->m_labHarm_RelErr->text() + ":");
	}
}