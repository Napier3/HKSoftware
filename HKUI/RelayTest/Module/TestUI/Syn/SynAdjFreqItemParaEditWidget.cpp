#include "SynAdjFreqItemParaEditWidget.h"
#include "ui_SynAdjFreqItemParaEditWidget.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSynAdjFreqItemParaEditWidget::QSynAdjFreqItemParaEditWidget(QWidget *parent) :
    QItemParaEditWidgetBase(parent),
    ui(new Ui::QSynAdjFreqItemParaEditWidget)
{
    ui->setupUi(this);
	InitLanuage();
}

QSynAdjFreqItemParaEditWidget::~QSynAdjFreqItemParaEditWidget()
{
    delete ui;
}

void QSynAdjFreqItemParaEditWidget::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(ui->groupBox_2, g_sLangID_State_SettingValue, XLang_Ctrls_QGroupBox);//整定值
	xlang_SetLangStrToWidget(ui->groupBox_3, g_sLangID_PowerDir_TestParas, XLang_Ctrls_QGroupBox);//试验参数
	xlang_GetLangStrByFile(strtemp, g_sLangID_Freq_ReguPeriod);//调频周期(s):
	strtemp += "(s):";
	ui->m_labFt->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V):
	strtemp += "(V):";
	ui->m_labUgStart->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Freq);//待并侧频率(Hz):
	strtemp += "(Hz):";
	ui->m_labFgStart->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	strtemp += ":";
	ui->m_labRelErr->setText(strtemp);
	//xlang_GetLangStrByFile(strtemp, g_sLangID_Distance_AbsErrPlus);//绝对误差(s)+:
	//strtemp += ":";
	//ui->m_labAbsErr->setText(strtemp);
	//xlang_GetLangStrByFile(strtemp, g_sLangID_Distance_AbsErrMinus);//绝对误差(s)-:
	//strtemp += ":";
	//ui->m_labAbsErr_2->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):+";
	ui->m_labAbsErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(s):
	strtemp += "(s):-";
	ui->m_labAbsErr_2->setText(strtemp);
}

void QSynAdjFreqItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QSynAdjFreqItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//调频周期
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FT);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART);
	//CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGFREQSTEP);
}

void QSynAdjFreqItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//调频周期
	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FT)
	{
		//ui->m_lineFt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS)
	{
		ui->m_linePlus->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS)
	{
		ui->m_lineMinus->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR)
	{
		ui->m_lineRelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART)
	{
		//ui->m_lineUgStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineUgStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART)
	{
		//ui->m_lineFgStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFgStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGFREQSTEP)
	//{
	//	ui->m_lineUgFreqStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	//}
}

void QSynAdjFreqItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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
	//CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);

	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);
	//CSttMacroTestParaData *pDataExternal = (CSttMacroTestParaData *)pSttMacroTestParaDatas_External->FindByID(strID);

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

void QSynAdjFreqItemParaEditWidget::on_m_lineFt_editingFinished()
{
	if (ui->m_lineFt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFt)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineFt->setText(CheckDataMinMax(ui->m_lineFt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FT,ui->m_lineFt->text());
}

void QSynAdjFreqItemParaEditWidget::on_m_linePlus_editingFinished()
{
	ui->m_linePlus->setText(CheckDataMinMax(ui->m_linePlus->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS,ui->m_linePlus->text());
}

void QSynAdjFreqItemParaEditWidget::on_m_lineMinus_editingFinished()
{
	ui->m_lineMinus->setText(CheckDataMinMax(ui->m_lineMinus->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS,ui->m_lineMinus->text());
}

void QSynAdjFreqItemParaEditWidget::on_m_lineRelErr_editingFinished()
{
	ui->m_lineRelErr->setText(CheckDataMinMax(ui->m_lineRelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR,ui->m_lineRelErr->text());
}

void QSynAdjFreqItemParaEditWidget::on_m_lineUgStart_editingFinished()
{
	if (ui->m_lineUgStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUgStart)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineUgStart->setText(CheckDataMinMax(ui->m_lineUgStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART,ui->m_lineUgStart->text());
}

void QSynAdjFreqItemParaEditWidget::on_m_lineFgStart_editingFinished()
{
	if (ui->m_lineFgStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFgStart)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineFgStart->setText(CheckDataMinMax(ui->m_lineFgStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART,ui->m_lineFgStart->text());

}

//void QSynAdjFreqItemParaEditWidget::on_m_lineUgFreqStep_editingFinished()
//{
//	ui->m_lineUgFreqStep->setText(CheckDataMinMax(ui->m_lineUgFreqStep->text(),999.999,0,3));
//	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGFREQSTEP,ui->m_lineUgFreqStep->text());
//}

CExBaseList * QSynAdjFreqItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

// CExBaseList * QSynAdjFreqItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }

void QSynAdjFreqItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}
