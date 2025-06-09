#include "SynActFreqItemParaEditWidget.h"
#include "ui_SynActFreqItemParaEditWidget.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSynActFreqItemParaEditWidget::QSynActFreqItemParaEditWidget(QWidget *parent) :
    QItemParaEditWidgetBase(parent),
    ui(new Ui::QSynActFreqItemParaEditWidget)
{
    ui->setupUi(this);
	InitLanuage();
}

QSynActFreqItemParaEditWidget::~QSynActFreqItemParaEditWidget()
{
    delete ui;
}

void QSynActFreqItemParaEditWidget::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(ui->groupBox_2, g_sLangID_State_SettingValue, XLang_Ctrls_QGroupBox);//整定值
	xlang_SetLangStrToWidget(ui->groupBox_3, g_sLangID_PowerDir_TestParas, XLang_Ctrls_QGroupBox);//试验参数
	xlang_GetLangStrByFile(strtemp, g_sLangID_Allow_FreqDifference );//允许频差(Hz):
	strtemp +="(Hz):";
	ui->m_labFzd->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	strtemp += ":";
	ui->m_labRelErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(Hz):
	strtemp += "(Hz):";
	ui->m_labAbsErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V):
	strtemp += "(V):";
	ui->m_labUgStart->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Freq);//待并侧频率(Hz):
	strtemp += "(Hz):";
	ui->m_labFgStart->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_GfreqChangeStep);//待并侧频率变化步长(Hz):
	strtemp += "(Hz):";
	ui->m_labUgFreqStep->setText(strtemp); 
	xlang_GetLangStrByFile(strtemp, g_sLangID_Freq_ReguPeriod);//调频周期(s):
	strtemp += "(s):";
	ui->m_labFgStart->setText(strtemp);
}

void QSynActFreqItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QSynActFreqItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//频率边界值
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGFREQSTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FT);
}

void QSynActFreqItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//频率边界值
	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd)
	{
		//ui->m_lineFzd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFzd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR)
	{
		ui->m_lineAbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_RELERR)
	{
		ui->m_lineRelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART)
	{
		//ui->m_lineUgStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineUgStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART)
	{
		//ui->m_lineFgStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFgStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGFREQSTEP)
	{
		//ui->m_lineUgFreqStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineUgFreqStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FT)
	{
		//ui->m_lineFt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
}

void QSynActFreqItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

void QSynActFreqItemParaEditWidget::on_m_lineFzd_editingFinished()
{
	if (ui->m_lineFzd->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFzd)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineFzd->setText(CheckDataMinMax(ui->m_lineFzd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd,ui->m_lineFzd->text());
}

void QSynActFreqItemParaEditWidget::on_m_lineAbsErr_editingFinished()
{
	ui->m_lineAbsErr->setText(CheckDataMinMax(ui->m_lineAbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR,ui->m_lineAbsErr->text());
}

void QSynActFreqItemParaEditWidget::on_m_lineRelErr_editingFinished()
{
	ui->m_lineRelErr->setText(CheckDataMinMax(ui->m_lineRelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_RELERR,ui->m_lineRelErr->text());
}

void QSynActFreqItemParaEditWidget::on_m_lineUgStart_editingFinished()
{
	if (ui->m_lineUgStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUgStart)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineUgStart->setText(CheckDataMinMax(ui->m_lineUgStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART,ui->m_lineUgStart->text());
}

void QSynActFreqItemParaEditWidget::on_m_lineFgStart_editingFinished()
{
	if (ui->m_lineFgStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFgStart)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineFgStart->setText(CheckDataMinMax(ui->m_lineFgStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART,ui->m_lineFgStart->text());
}

void QSynActFreqItemParaEditWidget::on_m_lineUgFreqStep_editingFinished()
{
	if (ui->m_lineUgFreqStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUgFreqStep)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineUgFreqStep->setText(CheckDataMinMax(ui->m_lineUgFreqStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGFREQSTEP,ui->m_lineUgFreqStep->text());
}

void QSynActFreqItemParaEditWidget::on_m_lineFt_editingFinished()
{
	if (ui->m_lineFt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFt)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineFt->setText(CheckDataMinMax(ui->m_lineFt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FT,ui->m_lineFt->text());
}

CExBaseList * QSynActFreqItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

// CExBaseList * QSynActFreqItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }

void QSynActFreqItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}
