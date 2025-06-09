#include "DistanceAddSinglePhaseDlg.h"
#include "ui_DistanceAddSinglePhaseDlg.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameBase.h"

QDistanceAddSinglePhaseDlg::QDistanceAddSinglePhaseDlg(QWidget *parent) :
    QDistanceAddMultBase(parent),
    ui(new Ui::QDistanceAddSinglePhaseDlg)
{
    ui->setupUi(this);
	InitLanuage();
	InitUI();
}

QDistanceAddSinglePhaseDlg::~QDistanceAddSinglePhaseDlg()
{
    delete ui;
}
void QDistanceAddSinglePhaseDlg::InitUI()
{
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);

	//ui->m_cmbZoneType->addItems(QStringList()<<g_sLangTxt_Distance_Zone1/*("Ⅰ段")*/<<g_sLangTxt_Distance_Zone2/*("Ⅱ段")*/<<g_sLangTxt_Distance_Zone3/*("Ⅲ段")*/<<g_sLangTxt_Distance_Zone4/*("Ⅳ段")*/\
	//	<<g_sLangTxt_Distance_Zone5/*("Ⅴ段")*/<<g_sLangTxt_Distance_ZoneLine/*("线路长度")*/<<g_sLangTxt_Distance_ZoneAllarea/*("所有区域")*/);
	ui->m_cmbK0Mode->addItems(QStringList()<<_T("|K0|,Phi(K0)")<<_T("RERL,XEXL")<<_T("|Z0/Z1|,Phi(Z0/Z1)"));
	//ui->m_cmb1->addItems(QStringList() << g_sLangTxt_StateEstimate_AbsError/*绝对误差*/ << g_sLangTxt_StateEstimate_RelError/*相对误差*/ << g_sLangTxt_Distance_ErrorRelorAbs/*相对误差或绝对误差*/\
	//	<< g_sLangTxt_Distance_ErrorRelAndAbs/*相对误差与绝对误差*/ << g_sLangTxt_StateEstimate_CombinationError/*组合误差*/ << g_sLangTxt_Distance_ErrorNot/*不评估*/);
	//20240924 luozibing 界面下拉框显示由特性曲线相关参数得出
	//ui->m_cmbZoneType->SetBaseList(m_pDataTypeLN);
	CExBaseList *pListTemp = (CExBaseList  *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_Time);//显示动作时误差类型
	ui->m_cmb1->SetBaseList(pListTemp);
	QButtonGroup *pZoneN1 = new QButtonGroup(this);
	pZoneN1->addButton(ui->m_checkForward,0);
	pZoneN1->addButton(ui->m_checkReverse,1);

    ui->m_labTips->raise();
	ui->m_labTips->setVisible(false);
	ui->m_labTips->setFont(*g_pSttGlobalFont);

	//英文版程序显示不全20241021 luozibing
	if (g_sLangTxt_Distance_ErrorRelAndAbs.GetLength() * 7 > ui->m_cmb1->minimumWidth())
	{
		ui->m_cmb1->setMinimumWidth(g_sLangTxt_Distance_ErrorRelAndAbs.GetLength() * 7);
		ui->m_txtPlus->setMinimumWidth(g_sLangTxt_Distance_ErrorRelAndAbs.GetLength() * 7);
	}
}
void QDistanceAddSinglePhaseDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->m_labZSetting, g_sLangID_Distance_ZImpValue, XLang_Ctrls_QLabel);//阻抗(Ω):
	xlang_SetLangStrToWidget(ui->m_labZAng, g_sLangID_Gradient_ImpAngle, XLang_Ctrls_QLabel);//阻抗角(°):
	xlang_SetLangStrToWidget(ui->m_labTSetting, g_sLangID_Distance_SetActionTime, XLang_Ctrls_QLabel);//整定动作时间(s):
	xlang_SetLangStrToWidget(ui->m_labFaultCurrent, g_sLangID_State_ShortI, XLang_Ctrls_QLabel);//短路电流(A):
	xlang_SetLangStrToWidget(ui->m_labZoneType, g_sLangID_Distance_AddMultZone, XLang_Ctrls_QLabel);//区段:

	xlang_SetLangStrToWidget(ui->m_labFaultType, g_sLangID_Distance_FaultTypeSel, XLang_Ctrls_QLabel);//故障类型选择:
	xlang_SetLangStrToWidget(ui->m_labFaultDirection, g_sLangID_Distance_FailDirectSel, XLang_Ctrls_QLabel);//故障方向选择:
	xlang_SetLangStrToWidget(ui->m_labRate, g_sLangID_Distance_Percent, XLang_Ctrls_QLabel);//百分比(%):
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, g_sLangID_State_ZeroCoeff);//零序补偿系数:
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	ui->m_labK0Mode->setText(strtemp);
	
	xlang_SetLangStrToWidget(ui->groupBox, g_sLangID_StateEstimate_ResultEstimate, XLang_Ctrls_QGroupBox);//结果评估
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_ErrorType);//误差类型:
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	ui->m_labType->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	ui->m_labRel->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_labPlus, g_sLangID_ActionTime_AbsErrPos, XLang_Ctrls_QLabel);//绝对误差(s)+:
	xlang_SetLangStrToWidget(ui->m_labMinus, g_sLangID_ActionTime_AbsErrNeg, XLang_Ctrls_QLabel);//绝对误差(s)-:

	xlang_SetLangStrToWidget(ui->m_checkForward, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(ui->m_checkReverse, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(ui->m_btnSave, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnclose, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;//添加单相接地故障
	xlang_GetLangStrByFile(strTile, g_sLangID_Distance_AddOneTileLN);
	setWindowTitle(strTile);
}
void QDistanceAddSinglePhaseDlg::SetPageFont(CFont oPageFont)
{//luozibing 测试使用
	setFont(oPageFont);

	CString strF = this->font().family();
	int nSize = this->font().pointSize();
}
void QDistanceAddSinglePhaseDlg::slot_ZoneTypeCurrentIndexChanged(int index)
{
	UpadatePageByZoneType();//区段选择更新参数显示 20240924 luozibing
	UpdateBtnEnable(ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);
}
void QDistanceAddSinglePhaseDlg::UpdateBtnEnable(BOOL bEnable)
{
	ui->m_txtTSetting->setEnabled(bEnable);
	ui->m_txtPlus->setEnabled(bEnable);
	ui->m_txtMinus->setEnabled(bEnable);
	ui->m_txtRel1->setEnabled(bEnable);
	//ui->m_cmb1->setEnabled(bEnable);

	//20240923 luozibing 设置部分控件不可编辑
	ui->m_txtZSetting->setEnabled(false);
	ui->m_txtTSetting->setEnabled(bEnable);
	ui->m_txtR->setEnabled(false);
	ui->m_txtX->setEnabled(false);
	//ui->m_txtZAng->setEnabled(bEnable);
}
void QDistanceAddSinglePhaseDlg::on_m_checkAN_clicked(bool checked)
{
	CheckFaultTypeState();
}

void QDistanceAddSinglePhaseDlg::on_m_checkBN_stateChanged(int arg1)
{
	CheckFaultTypeState();
}

void QDistanceAddSinglePhaseDlg::on_m_checkCN_stateChanged(int arg1)
{
	CheckFaultTypeState();
}
void QDistanceAddSinglePhaseDlg::CheckFaultTypeState(BOOL bShow)
{
	if (!ui->m_checkAN->isChecked()&&\
		!ui->m_checkBN->isChecked()&&\
		!ui->m_checkCN->isChecked())
	{
		ui->m_checkAN->setChecked(true);
		if (bShow)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类型")*/);
		}
	}
}
void QDistanceAddSinglePhaseDlg::on_m_checkForward_stateChanged(int arg1)
{
	CheckFaultDirectionState();
}

void QDistanceAddSinglePhaseDlg::on_m_checkReverse_stateChanged(int arg1)
{
	CheckFaultDirectionState();
}
void QDistanceAddSinglePhaseDlg::CheckFaultDirectionState(BOOL bShow)
{
	if (!ui->m_checkForward->isChecked()&&\
		!ui->m_checkReverse->isChecked())
	{
		ui->m_checkForward->setChecked(true);
		if (bShow)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneDirection/*("请至少勾选一个故障方向")*/);
		}
	}
}
void QDistanceAddSinglePhaseDlg::on_m_checkRate_105_clicked(bool checked)
{
	CheckRateState();
}

void QDistanceAddSinglePhaseDlg::on_m_checkRate_095_stateChanged(int arg1)
{
	CheckRateState();
}

void QDistanceAddSinglePhaseDlg::on_m_checkRate_070_stateChanged(int arg1)
{
	CheckRateState();
}

void QDistanceAddSinglePhaseDlg::on_m_checkRate_100_clicked(bool checked)
{
	CheckRateState();
	ui->m_txtRate_100->setEnabled(checked);
}
void QDistanceAddSinglePhaseDlg::CheckRateState(BOOL bShow)
{
	if (!ui->m_checkRate_105->isChecked()&&\
		!ui->m_checkRate_095->isChecked()&&\
		!ui->m_checkRate_070->isChecked()&&\
		!ui->m_checkRate_100->isChecked())
	{
		ui->m_checkRate_105->setChecked(true);
		if (bShow)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneRate/*("请至少勾选一个倍数")*/);
		}
	}
}
void QDistanceAddSinglePhaseDlg::on_m_cmbK0Mode_currentIndexChanged(int index)
{
	SetModeText(index);
	CString strTmp;
	strTmp.setNum(index);
}
void QDistanceAddSinglePhaseDlg::SetModeText(int nIndex)
{
	if(m_pDistanceparas == NULL)
		return;

	CString strTmp = ui->m_cmbK0Mode->itemText(nIndex);
	if(strTmp == "")
		return;
	QStringList words = strTmp.split(",");

	CString strShow = words[0];
	strShow += ":";
	ui->m_labKlKr->setText(strShow);
	strShow = words[1];
	strShow += ":";
	ui->m_labAngKx->setText(strShow);
}
void QDistanceAddSinglePhaseDlg::on_m_btnSave_clicked()
{
	this->done(Accepted);
}

void QDistanceAddSinglePhaseDlg::on_m_btnclose_clicked()
{
	this->close();
}
void QDistanceAddSinglePhaseDlg::on_m_cmb_currentIndexChanged(int index)
{
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	UpdateErrorLogicValue(index, nZoneValue);
}
//void QDistanceAddSinglePhaseDlg::on_m_txtRel1_editingFinished()
//{
//	if (ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine)
//	{
//		ui->m_txtRel1->setText(CheckDataMinMax(ui->m_txtRel1->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6, 100, 0, 3));
//	}
//	else
//	{
//		ui->m_txtRel1->setText(CheckDataMinMax(ui->m_txtRel1->text(), 100, 0, 3));
//	}
//}
//
//void QDistanceAddSinglePhaseDlg::on_m_txtPlus_editingFinished()
//{
//	if (ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine)
//	{
//		ui->m_txtPlus->setText(CheckDataMinMax(ui->m_txtPlus->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6, 200, 0, 3));
//	}
//	else
//	{
//		ui->m_txtPlus->setText(CheckDataMinMax(ui->m_txtPlus->text(), 200, 0, 3));
//	}
//}
//void QDistanceAddSinglePhaseDlg::on_m_txtMinus_editingFinished()
//{
//	if (ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine)
//	{
//		ui->m_txtMinus->setText(CheckDataMinMax(ui->m_txtMinus->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6, 200, 0, 3));
//	}
//	else
//	{
//		ui->m_txtMinus->setText(CheckDataMinMax(ui->m_txtMinus->text(), 200, 0, 3));
//	}
//}

void QDistanceAddSinglePhaseDlg::on_m_txtRate_100_editingFinished()
{
	ui->m_txtRate_100->setText(CheckDataMinMax(ui->m_txtRate_100->text(),0,0,1));
}
//void QDistanceAddSinglePhaseDlg::on_m_txtZSetting_editingFinished()
//{
//	//20240806 huangliang 因此值涉及R和X变更，暂时不做定值处理
//	////20240722 huangliang 判断是否为定值，是定值就不需要处理
//	//if (ui->m_txtZSetting->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
//	//{
//	//	if (((QSettingLineEdit*)ui->m_txtZSetting)->IsSetting())
//	//	{
//	//		return;
//	//	}
//	//}
//	ui->m_txtZSetting->setText(CheckDataMinMax(ui->m_txtZSetting->text(), STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
//
//	CString strNewR,StrNewX;
//	CheckRxValue(strNewR,StrNewX,ui->m_txtZSetting->text(),ui->m_txtZAng->text());
//	ui->m_txtR->setText(CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
//	ui->m_txtX->setText(CheckDataMinMax(StrNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
//}

void QDistanceAddSinglePhaseDlg::on_m_txtZAng_editingFinished()
{
	//20240806 huangliang 因此值涉及R和X变更，暂时不做定值处理
	////20240722 huangliang 判断是否为定值，是定值就不需要处理
	//if (ui->m_txtZAng->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtZAng)->IsSetting())
	//	{
	//		return;
	//	}
	//}
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	CString strZAng;

	if (nZoneValue == STT_MULTI_MACRO_ZONE1 || nZoneValue == STT_MULTI_MACRO_ZONE2 || \
		nZoneValue == STT_MULTI_MACRO_ZONE3 || nZoneValue == STT_MULTI_MACRO_ZONE4 || \
		nZoneValue == STT_MULTI_MACRO_ZONE5 || nZoneValue == STT_MULTI_MACRO_ZONELine)
	{
		strZAng = GetZAngIDByZoneValue(nZoneValue, CHAR_DISTANCE_FAULT_TYPE_LN);
		if (strZAng != "")
	{
			ui->m_txtZAng->setText(CheckDataMinMax(ui->m_txtZAng->text(), strZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
			SetZRXValueByZAng(nZoneValue);
	}
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONEAll)
	{
		CDataTypeValue *pDataValue = (CDataTypeValue *)m_pDataTypeLN->GetHead();
		int nZone = pDataValue->m_strIndex.toInt();
		strZAng = GetZAngIDByZoneValue(nZone, CHAR_DISTANCE_FAULT_TYPE_LN);
		if (strZAng != "")
		{
			ui->m_txtZAng->setText(CheckDataMinMax(ui->m_txtZAng->text(), strZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
			SetZRXValueByZAng(nZone);
		}
	}
	else
	{//未选中区段 默认选择线路长度
		CString strLine;
		strLine.setNum(STT_MULTI_MACRO_ZONELine);
		CExBaseObject *pData = pZoneType->FindByID(strLine);
		if (pData == NULL)
		{
			return;
		}
		strLine = pData->m_strName;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		ui->m_cmbZoneType->setCurrentText(strLine);
#else
		Stt_Global_SetComboBoxIndexByText(ui->m_cmbZoneType, strLine);
#endif
		//ui->m_cmbZoneType->setCurrentText(g_sLangTxt_Distance_ZoneLine);
		ui->m_txtZAng->setText(CheckDataMinMax(ui->m_txtZAng->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE6, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	}
}
//void QDistanceAddSinglePhaseDlg::on_m_txtR_editingFinished()
//{
//	ui->m_txtR->setText(CheckDataMinMax(ui->m_txtR->text(), STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
//	CString strNewZSetting,StrNewZAng;
//	CheckZSettingAndZAng(ui->m_txtR->text(),ui->m_txtX->text(),strNewZSetting,StrNewZAng);
//	ui->m_txtZSetting->setText(CheckDataMinMax(strNewZSetting, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
//	ui->m_txtZAng->setText(CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
//}
//void QDistanceAddSinglePhaseDlg::on_m_txtX_editingFinished()
//{
//	ui->m_txtX->setText(CheckDataMinMax(ui->m_txtX->text(), STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
//	CString strNewZSetting,StrNewZAng;
//	CheckZSettingAndZAng(ui->m_txtR->text(),ui->m_txtX->text(),strNewZSetting,StrNewZAng);
//	ui->m_txtZSetting->setText(CheckDataMinMax(strNewZSetting, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
//	ui->m_txtZAng->setText(CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
//}

void QDistanceAddSinglePhaseDlg::on_m_txtTSetting_editingFinished()
{
	ui->m_txtTSetting->setText(CheckDataMinMax(ui->m_txtTSetting->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE6,STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddSinglePhaseDlg::on_m_txtRel1_editingFinished()
{
	ui->m_txtRel1->setText(CheckDataMinMax(ui->m_txtRel1->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
}

void QDistanceAddSinglePhaseDlg::on_m_txtPlus_editingFinished()
{
	ui->m_txtPlus->setText(CheckDataMinMax(ui->m_txtPlus->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
}

void QDistanceAddSinglePhaseDlg::on_m_txtMinus_editingFinished()
{
	ui->m_txtMinus->setText(CheckDataMinMax(ui->m_txtMinus->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddSinglePhaseDlg::on_m_txtFaultCurrent_editingFinished()
{
	//ui->m_txtFaultCurrent->setText(CheckDataMinMax(ui->m_txtFaultCurrent->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT,20,0,3));
	ui->m_txtFaultCurrent->setText(CheckDataMinMax(ui->m_txtFaultCurrent->text(),STT_MULTI_MACRO_CURR_MAX, STT_MULTI_MACRO_CURR_MIN, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddSinglePhaseDlg::on_m_txtKlKr_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (ui->m_txtKlKr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtKlKr)->IsSetting())
		{
			return;
		}
	}
	//ui->m_txtKlKr->setText(CheckDataMinMax(ui->m_txtKlKr->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR,999.999,0,2));
	ui->m_txtKlKr->setText(CheckDataMinMax(ui->m_txtKlKr->text(), 999.999, 0, 2));
}

void QDistanceAddSinglePhaseDlg::on_m_txtAngKx_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (ui->m_txtAngKx->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtAngKx)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtAngKx->setText(CheckDataMinMax(ui->m_txtAngKx->text(), 999.999, 0, 2));
	//ui->m_txtAngKx->setText(CheckDataMinMax(ui->m_txtAngKx->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX,999.999,0,2));
}
void QDistanceAddSinglePhaseDlg::SetApplyTips(CString strTips)
{
	ui->m_labTips->setText(strTips);
	ui->m_labTips->setVisible(true);
	m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}
void QDistanceAddSinglePhaseDlg::timerEvent(QTimerEvent* ev)
{
	if(ev->timerId() == m_nTipsTime){
		ui->m_labTips->setVisible(false);
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage(CDvmData *pData)
{
	//20240822 luozibing 当前添加接地类型测试项 设置相间类型测试项为0
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}

	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)//
	{
		ui->m_txtFaultCurrent->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_CURR_MAX, STT_MULTI_MACRO_CURR_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK)
	{
		ui->m_checkRate_095->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK)
	{
		ui->m_checkRate_105->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK)
	{
		ui->m_checkRate_070->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK)
	{
		ui->m_checkRate_100->setChecked(pData->m_strValue == "1");
		ui->m_txtRate_100->setEnabled(pData->m_strValue == "1");
		CDvmData *pData100 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100);
		if(pData100 != NULL)
		{
			double nrate = CString_To_double(pData100->m_strValue);
			CString strTmp;
			strTmp.setNum(nrate*100);
			ui->m_txtRate_100->setText(CheckDataMinMax(strTmp,0,0,1));
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		ui->m_cmbK0Mode->setCurrentIndex(CString_To_long(pData->m_strValue));
		SetModeText(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{
		//ui->m_txtKlKr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,2));
		ui->m_txtKlKr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 2), 2);//20240723 huangliang 设置对象地址
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		//ui->m_txtAngKx->setText(CheckDataMinMax(pData->m_strValue,999.999,0,2));
		ui->m_txtAngKx->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 2), 2);//20240723 huangliang 设置对象地址
	}
	//20240924 luozibing 根据区段选择更新界面显示
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	if (nZoneValue == STT_MULTI_MACRO_ZONE1)
	{
		SetValueToPage__Zone1(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE2)
	{
		SetValueToPage__Zone2(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE3)
	{
		SetValueToPage__Zone3(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE4)
	{
		SetValueToPage__Zone4(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE5)
	{
		SetValueToPage__Zone5(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONELine)
	{
		SetValueToPage__Zone6(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONEAll)
	{//20240924 luozibing 根据当前区段下拉框显示数据设置所有区域界面显示数据
		CDataTypeValue *pDataValue = (CDataTypeValue *)m_pDataTypeLN->GetHead();
		int nZone = pDataValue->m_strIndex.toInt();
		switch (nZone)
		{
		case STT_MULTI_MACRO_ZONE1:
			SetValueToPage__Zone1(pData);
			break;
		case STT_MULTI_MACRO_ZONE2:
			SetValueToPage__Zone2(pData);
			break;
		case STT_MULTI_MACRO_ZONE3:
			SetValueToPage__Zone3(pData);
			break;
		case STT_MULTI_MACRO_ZONE4:
			SetValueToPage__Zone4(pData);
			break;
		case STT_MULTI_MACRO_ZONE5:
			SetValueToPage__Zone5(pData);
			break;
		}
	}
	else
	{
		SetValueToPage__Zone1(pData);
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage_Zone1(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE1);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE1)
	//{
	//	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE1)
	//{
	//	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1)
	{
		ui->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1)
	{
		ui->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1)
	{
		ui->m_txtRel1->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1)
	{
		CDataType *pType = (CDataType *)ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
			ui->m_cmb1->setCurrentIndex(pType->FindIndex(pDataValue));
		}
	}
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage__Zone1(CDvmData *pData)
{
	UpadateValueToPage_Zone1(pData);
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK)
	{
		ui->m_checkAN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK)
	{
		ui->m_checkBN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK)
	{
		ui->m_checkCN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage_Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE2);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE2)
	//{
	//	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE2)
	//{
	//	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2)
	{
		ui->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2)
	{
		ui->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2)
	{
		ui->m_txtRel1->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2)
	{
		//ui->m_cmb1->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
			ui->m_cmb1->setCurrentIndex(pType->FindIndex(pDataValue));
		}
	}
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage__Zone2(CDvmData *pData)
{
	UpadateValueToPage_Zone2(pData);
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK)
	{
		ui->m_checkAN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK)
	{
		ui->m_checkBN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK)
	{
		ui->m_checkCN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage_Zone3(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE3);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE3)
	//{
	//	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE3)
	//{
	//	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3)
	{
		ui->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3)
	{
		ui->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3)
	{
		ui->m_txtRel1->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3)
	{
		//ui->m_cmb1->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
			ui->m_cmb1->setCurrentIndex(pType->FindIndex(pDataValue));
		}
	}
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage__Zone3(CDvmData *pData)
{
	UpadateValueToPage_Zone3(pData);
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK)
	{
		ui->m_checkAN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK)
	{
		ui->m_checkBN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK)
	{
		ui->m_checkCN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage_Zone4(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE4);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE4)
	{
		ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE4)
	{
		ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4)
	{
		ui->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4)
	{
		ui->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4)
	{
		ui->m_txtRel1->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4)
	{
		//ui->m_cmb1->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
			ui->m_cmb1->setCurrentIndex(pType->FindIndex(pDataValue));
		}
	}
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage__Zone4(CDvmData *pData)
{
	UpadateValueToPage_Zone4(pData);
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK)
	{
		ui->m_checkAN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK)
	{
		ui->m_checkBN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK)
	{
		ui->m_checkCN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage_Zone5(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE5);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE5)
	//{
	//	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE5)
	//{
	//	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_ANGPLACES));
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5)
	{
		ui->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5)
	{
		ui->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5)
	{
		ui->m_txtRel1->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5)
	{
		//ui->m_cmb1->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
			ui->m_cmb1->setCurrentIndex(pType->FindIndex(pDataValue));
		}
	}
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage__Zone5(CDvmData *pData)
{
	UpadateValueToPage_Zone5(pData);
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK)
	{
		ui->m_checkAN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK)
	{
		ui->m_checkBN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK)
	{
		ui->m_checkCN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage_Zone6(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE6)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6)
	{
		ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
		//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE6)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE6)
	{
		ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE6)
	{
		ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6)
	{
		ui->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6)
	{
		ui->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6)
	{
		ui->m_txtRel1->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6)
	{
		//ui->m_cmb1->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
			ui->m_cmb1->setCurrentIndex(pType->FindIndex(pDataValue));
		}
	}
	}
}
void QDistanceAddSinglePhaseDlg::SetValueToPage__Zone6(CDvmData *pData)
{
	UpadateValueToPage_Zone6(pData);
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE6_CHECK)
	{
		ui->m_checkAN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE6_CHECK)
	{
		ui->m_checkBN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE6_CHECK)
	{
		ui->m_checkCN->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N6)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
	{
		pData->m_strValue = ui->m_txtFaultCurrent->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkRate_095->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkRate_105->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkRate_070->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkRate_100->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100)
	{
		CString strTmp;
		strTmp.setNum(ui->m_txtRate_100->text().toDouble()/100);
		pData->m_strValue = CheckDataMinMax(strTmp,0,0,3);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		pData->m_strValue.setNum(ui->m_cmbK0Mode->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{
		pData->m_strValue = ui->m_txtKlKr->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		pData->m_strValue = ui->m_txtAngKx->GetText();//20240723 huangliang GetText()替换text();
	}
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	if (nZoneValue == STT_MULTI_MACRO_ZONE1)
	{
		GetPageToValue_Zone1(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE2)
	{
		GetPageToValue_Zone2(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE3)
	{
		GetPageToValue_Zone3(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE4)
	{
		GetPageToValue_Zone4(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE5)
	{
		GetPageToValue_Zone5(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONELine)
	{
		GetPageToValue_Zone6(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONEAll)
	{
		GetPageToValue_ZoneALL(pData);
	}
	else
	{
		GetPageToValue_Zone1(pData);
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToInitValue_Zone1(CDvmData *pData)
{//20240924 luozibing 设置区段对应参数值 
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1)
	{
		pData->m_strValue = ui->m_txtPlus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1)
	{
		pData->m_strValue = ui->m_txtMinus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1)
	{
		pData->m_strValue = ui->m_txtRel1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1)
	{
		//pData->m_strValue.setNum(ui->m_cmb1->currentIndex());
		CExBaseList *pType = ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb1->currentIndex());
			pData->m_strValue = pDataValue->m_strIndex;
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE1)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE1)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_Zone1(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone1(pData);
}
void QDistanceAddSinglePhaseDlg::GetPageToInitValue_Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2)
	{
		pData->m_strValue = ui->m_txtPlus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2)
	{
		pData->m_strValue = ui->m_txtMinus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2)
	{
		pData->m_strValue = ui->m_txtRel1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2)
	{
		//pData->m_strValue.setNum(ui->m_cmb1->currentIndex());
		CExBaseList *pType = ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb1->currentIndex());
			pData->m_strValue = pDataValue->m_strIndex;
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE2)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE2)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone2(pData);
}
void QDistanceAddSinglePhaseDlg::GetPageToInitValue_Zone3(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3)
	{
		pData->m_strValue = ui->m_txtPlus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3)
	{
		pData->m_strValue = ui->m_txtMinus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3)
	{
		pData->m_strValue = ui->m_txtRel1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3)
	{
		//pData->m_strValue.setNum(ui->m_cmb1->currentIndex());
		CExBaseList *pType = ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb1->currentIndex());
			pData->m_strValue = pDataValue->m_strIndex;
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE3)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE3)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_Zone3(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone3(pData);
}
void QDistanceAddSinglePhaseDlg::GetPageToInitValue_Zone4(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4)
	{
		pData->m_strValue = ui->m_txtPlus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4)
	{
		pData->m_strValue = ui->m_txtMinus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4)
	{
		pData->m_strValue = ui->m_txtRel1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4)
	{
		//pData->m_strValue.setNum(ui->m_cmb1->currentIndex());
		CExBaseList *pType = ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb1->currentIndex());
			pData->m_strValue = pDataValue->m_strIndex;
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE4)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE4)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_Zone4(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone4(pData);
}
void QDistanceAddSinglePhaseDlg::GetPageToInitValue_Zone5(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5)
	{
		pData->m_strValue = ui->m_txtPlus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5)
	{
		pData->m_strValue = ui->m_txtMinus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5)
	{
		pData->m_strValue = ui->m_txtRel1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5)
	{
		//pData->m_strValue.setNum(ui->m_cmb1->currentIndex());
		CExBaseList *pType = ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb1->currentIndex());
			pData->m_strValue = pDataValue->m_strIndex;
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE5)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE5)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_Zone5(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone5(pData);
}
void QDistanceAddSinglePhaseDlg::GetPageToInitValue_Zone6(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE6)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE6_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE6_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE6_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCN->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N6)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6)
	{
		pData->m_strValue = ui->m_txtPlus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6)
	{
		pData->m_strValue = ui->m_txtMinus->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6)
	{
		pData->m_strValue = ui->m_txtRel1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6)
	{
		//pData->m_strValue.setNum(ui->m_cmb1->currentIndex());
		CExBaseList *pType = ui->m_cmb1->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb1->currentIndex());
			pData->m_strValue = pDataValue->m_strIndex;
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE6)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE6)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE6)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_Zone6(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(1);
	}
	GetPageToInitValue_Zone6(pData);
}
void QDistanceAddSinglePhaseDlg::GetPageToValue_ZoneALL(CDvmData *pData)
{
	if (m_pDataTypeLN->FindByIndex(STT_MULTI_MACRO_ZONE1) != NULL)
	{
		GetPageToInitValue_Zone1(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLN->FindByIndex(STT_MULTI_MACRO_ZONE2) != NULL)
	{
		GetPageToInitValue_Zone2(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLN->FindByIndex(STT_MULTI_MACRO_ZONE3) != NULL)
	{
		GetPageToInitValue_Zone3(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLN->FindByIndex(STT_MULTI_MACRO_ZONE4) != NULL)
	{
		GetPageToInitValue_Zone4(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLN->FindByIndex(STT_MULTI_MACRO_ZONE5) != NULL)
	{
		GetPageToInitValue_Zone5(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
		
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence()
{
	//20240624 luozibing 检查ID是否存在
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX);
	CheckAllPresence_Zone1();
	CheckAllPresence_Zone2();
	CheckAllPresence_Zone3();
	CheckAllPresence_Zone4();
	CheckAllPresence_Zone5();
	CheckAllPresence_Zone6();
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence_Zone1()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1);
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence_Zone2()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2);
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence_Zone3()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3);
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence_Zone4()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4);
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence_Zone5()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5);
}
void QDistanceAddSinglePhaseDlg::CheckAllPresence_Zone6()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6);
}
void QDistanceAddSinglePhaseDlg::MinCheckLeastOne()
{
	QDistanceAddMultBase::MinCheckLeastOne();

	CheckFaultTypeState(FALSE);
	CheckFaultDirectionState(FALSE);
	CheckRateState(FALSE);

}
void QDistanceAddSinglePhaseDlg::InitPageShowByParas()
{
	QDistanceAddMultBase::InitPageShowByParas();
	DisConnectAll_SigSlot();
	ui->m_cmbZoneType->SetBaseList(m_pDataTypeLN);
	ConnectAll_SigSlot();

	//20240821 luozibing 根据上次设置数据设置区段类型
	CDvmData *pZone1 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK);
	CDvmData *pZone2 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK);
	CDvmData *pZone3 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK);
	CDvmData *pZone4 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK);
	CDvmData *pZone5 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK);
	CDvmData *pZone6 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK);

	if (pZone1 == NULL || pZone2 == NULL || pZone3 == NULL || pZone4 == NULL || pZone5 == NULL || pZone6 == NULL)
	{
		return;
	}

	CString strTypeID;
	if (pZone1->m_strValue == "1"\
		&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段1
		//ui->m_cmbZoneType->setCurrentIndex(0);
		if (ui->m_cmbZoneType->SetSelByID("2") == NULL)
		{
			ui->m_cmbZoneType->SetSelByID("0");
		}
	}
	else if (pZone2->m_strValue == "1"\
		&&pZone3->m_strValue != "1"&&pZone1->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段2
		//ui->m_cmbZoneType->setCurrentIndex(1);
		if (ui->m_cmbZoneType->SetSelByID("3") == NULL)
		{
			ui->m_cmbZoneType->SetSelByID("0");
		}
	}
	else if (pZone3->m_strValue == "1"\
		&&pZone2->m_strValue != "1"&&pZone1->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段3
		//ui->m_cmbZoneType->setCurrentIndex(2);
		if (ui->m_cmbZoneType->SetSelByID("4") == NULL)
		{
			ui->m_cmbZoneType->SetSelByID("0");
		}
	}
	else if (pZone4->m_strValue == "1"\
		&&pZone1->m_strValue != "1"&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段4
		//ui->m_cmbZoneType->setCurrentIndex(3);
		if (ui->m_cmbZoneType->SetSelByID("5") == NULL)
		{
			ui->m_cmbZoneType->SetSelByID("0");
		}
	}
	else if (pZone5->m_strValue == "1"\
		&&pZone1->m_strValue != "1"&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段5
		//ui->m_cmbZoneType->setCurrentIndex(4);
		if (ui->m_cmbZoneType->SetSelByID("6") == NULL)
		{
			ui->m_cmbZoneType->SetSelByID("0");
		}
	}
	else if (pZone6->m_strValue != "1"&&\
		(pZone1->m_strValue == "1" || m_pDataTypeLN->FindByID("2") == NULL) && \
		(pZone2->m_strValue == "1" || m_pDataTypeLN->FindByID("3") == NULL) &&\
		(pZone3->m_strValue == "1" || m_pDataTypeLN->FindByID("4") == NULL) && \
		(pZone4->m_strValue == "1" || m_pDataTypeLN->FindByID("5") == NULL) && \
		(pZone5->m_strValue == "1" || m_pDataTypeLN->FindByID("6") == NULL))
	{//全部区段
		//ui->m_cmbZoneType->setCurrentIndex(6);
		ui->m_cmbZoneType->SetSelByID("1");
	}
	else if (pZone6->m_strValue == "1"&&\
		pZone1->m_strValue != "1"&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1")
	{//线路长度
		//ui->m_cmbZoneType->setCurrentIndex(5);
		ui->m_cmbZoneType->SetSelByID("0");
	}
	else
	{
		pZone1->m_strValue.setNum(0);
		pZone2->m_strValue.setNum(0);
		pZone3->m_strValue.setNum(0);
		pZone4->m_strValue.setNum(0);
		pZone5->m_strValue.setNum(0);
		pZone6->m_strValue.setNum(1);
		//ui->m_cmbZoneType->setCurrentIndex(0);
		ui->m_cmbZoneType->SetSelByID("0");
	}
	UpdateBtnEnable(ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);
}
void QDistanceAddSinglePhaseDlg::UpadatePageByZoneType()
{
	POS pos = m_pDistanceparas->GetHeadPosition();
	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pDistanceparas->GetNext(pos);
		UpadateValueToPage(pData);
	}
}
void QDistanceAddSinglePhaseDlg::UpadateValueToPage(CDvmData *pData)
{
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	//20240924 luozibing 根据区段选择更新界面显示
	if (nZoneValue == STT_MULTI_MACRO_ZONE1)
	{
		UpadateValueToPage_Zone1(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE2)
	{
		UpadateValueToPage_Zone2(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE3)
	{
		UpadateValueToPage_Zone3(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE4)
	{
		UpadateValueToPage_Zone4(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONE5)
	{
		UpadateValueToPage_Zone5(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONELine)
	{
		UpadateValueToPage_Zone6(pData);
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONEAll)
	{//20240924 luozibing 根据当前区段下拉框显示数据设置所有区域界面显示数据
		CDataTypeValue *pDataValue = (CDataTypeValue *)m_pDataTypeLN->GetHead();
		int nZone = pDataValue->m_strIndex.toInt();
		switch (nZone)
		{
		case STT_MULTI_MACRO_ZONE1:
			UpadateValueToPage_Zone1(pData);
			break;
		case STT_MULTI_MACRO_ZONE2:
			UpadateValueToPage_Zone2(pData);
			break;
		case STT_MULTI_MACRO_ZONE3:
			UpadateValueToPage_Zone3(pData);
			break;
		case STT_MULTI_MACRO_ZONE4:
			UpadateValueToPage_Zone4(pData);
			break;
		case STT_MULTI_MACRO_ZONE5:
			UpadateValueToPage_Zone5(pData);
			break;
		}
	}
}
void QDistanceAddSinglePhaseDlg::ConnectAll_SigSlot()
{
	connect(ui->m_cmbZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ZoneTypeCurrentIndexChanged(int)));
}
void QDistanceAddSinglePhaseDlg::DisConnectAll_SigSlot()
{
	disconnect(ui->m_cmbZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ZoneTypeCurrentIndexChanged(int)));
}
void QDistanceAddSinglePhaseDlg::SetZRXValueByZAng(int nZoneValue)
{
	CString strR, strX, strZone;
	switch (nZoneValue)
	{
	case STT_MULTI_MACRO_ZONE1:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE1;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE1;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1;
		break;
	case STT_MULTI_MACRO_ZONE2:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE2;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE2;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2;
		break;
	case STT_MULTI_MACRO_ZONE3:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE3;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE3;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3;
		break;
	case STT_MULTI_MACRO_ZONE4:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE4;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE4;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4;
		break;
	case STT_MULTI_MACRO_ZONE5:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE5;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE5;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5;
		break;
	case STT_MULTI_MACRO_ZONELine:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE6;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE6;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6;
		break;
	}
	//20241024 luozibing 根据阻抗角设置阻抗定值 R X值
	CDvmData *pDataR = (CDvmData *)m_pDistanceparas->FindByID(strR);
	CDvmData *pDataX = (CDvmData *)m_pDistanceparas->FindByID(strX);
	CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(strZone);
	if (pDataR == NULL || pDataX == NULL || pDataZSet == NULL)
	{
		return;
	}
	if (nZoneValue != STT_MULTI_MACRO_ZONELine)
	{
		CString strTemp = GetZsetByZAng(ui->m_txtZAng->text(), nZoneValue, CHAR_DISTANCE_FAULT_TYPE_LN);
		if (strTemp != "")
		{
			pDataZSet->m_strValue = strTemp;
		}
	}
	CheckRxValue(pDataR->m_strValue, pDataX->m_strValue, pDataZSet->m_strValue, ui->m_txtZAng->text());
	ui->m_txtZSetting->setText(pDataZSet->m_strValue);
	ui->m_txtR->setText(CheckDataMinMax(pDataR->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	ui->m_txtX->setText(CheckDataMinMax(pDataX->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
}