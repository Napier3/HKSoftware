#include "SynActVoltageItemParaEditWidget.h"
#include "ui_SynActVoltageItemParaEditWidget.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSynActVoltageItemParaEditWidget::QSynActVoltageItemParaEditWidget(QWidget *parent) :
    QItemParaEditWidgetBase(parent),
    ui(new Ui::QSynActVoltageItemParaEditWidget)
{
    ui->setupUi(this);
	InitLanuage();
}

QSynActVoltageItemParaEditWidget::~QSynActVoltageItemParaEditWidget()
{
    delete ui;
}

void QSynActVoltageItemParaEditWidget::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(ui->groupBox_2, g_sLangID_State_SettingValue, XLang_Ctrls_QGroupBox);//整定值
	xlang_SetLangStrToWidget(ui->groupBox_3, g_sLangID_PowerDir_TestParas, XLang_Ctrls_QGroupBox);//试验参数
	xlang_GetLangStrByFile(strtemp, g_sLangID_Allow_VolDifference);//允许压差(V):
	strtemp += "(V):";
	ui->m_labRelErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	strtemp += ":";
	ui->m_labRelErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差(Hz):
	strtemp += "(V):";
	ui->m_labAbsErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V):
	strtemp += "(V):";
	ui->m_labUgStart->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Freq);//待并侧频率(Hz):
	strtemp += "(Hz):";
	ui->m_labFgStart->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_GvolChangeStep);//待并侧电压变化步长(V):
	strtemp += "(Hz):";
	ui->m_labUgMagStep->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Vol_ReguPeriod);//调压周期(s):
	strtemp += "(s):";
	ui->m_labUt->setText(strtemp);
}

void QSynActVoltageItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
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

void QSynActVoltageItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	//电压边界值
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UT);
}

void QSynActVoltageItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	//动作值
	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd)
	{
		//ui->m_lineVzd->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineVzd->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR)
	{
		ui->m_lineAbsErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR)
	{
		ui->m_lineRelErr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART)
	{
		//ui->m_lineUgStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineUgStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART)
	{
		//ui->m_lineFgStart->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFgStart->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP)
	{
		//ui->m_lineUgMagStep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineUgMagStep->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UT)
	{
		//ui->m_lineUt->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineUt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
}

void QSynActVoltageItemParaEditWidget::UpdatePara(CString strID,CString strValue)
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

//电压边界值
void QSynActVoltageItemParaEditWidget::on_m_lineVzd_editingFinished()
{
	if (ui->m_lineVzd->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineVzd)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineVzd->setText(CheckDataMinMax(ui->m_lineVzd->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd,ui->m_lineVzd->text());
}

void QSynActVoltageItemParaEditWidget::on_m_lineAbsErr_editingFinished()
{
	ui->m_lineAbsErr->setText(CheckDataMinMax(ui->m_lineAbsErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR,ui->m_lineAbsErr->text());
}

void QSynActVoltageItemParaEditWidget::on_m_lineRelErr_editingFinished()
{
	ui->m_lineRelErr->setText(CheckDataMinMax(ui->m_lineRelErr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR,ui->m_lineRelErr->text());
}

void QSynActVoltageItemParaEditWidget::on_m_lineUgStart_editingFinished()
{
	if (ui->m_lineUgStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUgStart)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineUgStart->setText(CheckDataMinMax(ui->m_lineUgStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART,ui->m_lineUgStart->text());
}

void QSynActVoltageItemParaEditWidget::on_m_lineFgStart_editingFinished()
{
	if (ui->m_lineFgStart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFgStart)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineFgStart->setText(CheckDataMinMax(ui->m_lineFgStart->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART,ui->m_lineFgStart->text());
}

void QSynActVoltageItemParaEditWidget::on_m_lineUgMagStep_editingFinished()
{
	if (ui->m_lineUgMagStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUgMagStep)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineUgMagStep->setText(CheckDataMinMax(ui->m_lineUgMagStep->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP,ui->m_lineUgMagStep->text());
}

void QSynActVoltageItemParaEditWidget::on_m_lineUt_editingFinished()
{
	if (ui->m_lineUt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUt)->IsSetting())
		{
			return;
		}
	}

	ui->m_lineUt->setText(CheckDataMinMax(ui->m_lineUt->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UT,ui->m_lineUt->text());
}

//void QSynActVoltageItemParaEditWidget::slot_MultiTab_clicked(int index)
//{
//	ui->stackedWidget->setCurrentIndex(index);
//}

CExBaseList * QSynActVoltageItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}

// CExBaseList * QSynActVoltageItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }

void QSynActVoltageItemParaEditWidget::DelMacroTestParaDatas()
{
	m_pCurrMacroTest_External = NULL;
}
