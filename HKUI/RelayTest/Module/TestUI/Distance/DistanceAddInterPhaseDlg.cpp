#include "DistanceAddInterPhaseDlg.h"
#include "ui_DistanceAddInterPhaseDlg.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameBase.h"

QDistanceAddInterPhaseDlg::QDistanceAddInterPhaseDlg(QWidget *parent) :
    QDistanceAddMultBase(parent),
    ui(new Ui::QDistanceAddInterPhaseDlg)
{
    ui->setupUi(this);
	InitLanuage();
	InitUI();
}

QDistanceAddInterPhaseDlg::~QDistanceAddInterPhaseDlg()
{
    delete ui;
}
void QDistanceAddInterPhaseDlg::InitUI()
{
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);

	//ui->m_cmbZoneType->addItems(QStringList()<<g_sLangTxt_Distance_Zone1/*("Ⅰ段")*/<<g_sLangTxt_Distance_Zone2/*("Ⅱ段")*/<<g_sLangTxt_Distance_Zone3/*("Ⅲ段")*/<<g_sLangTxt_Distance_Zone4/*("Ⅳ段")*/\
	//	<<g_sLangTxt_Distance_Zone5/*("Ⅴ段")*/<<g_sLangTxt_Distance_ZoneLine/*("线路长度")*/<<g_sLangTxt_Distance_ZoneAllarea/*("所有区域")*/);
	//ui->m_cmb->addItems(QStringList() << g_sLangTxt_StateEstimate_AbsError/*绝对误差*/ << g_sLangTxt_StateEstimate_RelError/*相对误差*/ << g_sLangTxt_Distance_ErrorRelorAbs/*相对误差或绝对误差*/\
	//	<< g_sLangTxt_Distance_ErrorRelAndAbs/*相对误差与绝对误差*/ << g_sLangTxt_StateEstimate_CombinationError/*组合误差*/ << g_sLangTxt_Distance_ErrorNot/*不评估*/);
	//20240924 luozibing 界面下拉框显示由特性曲线相关数据得出
	//ui->m_cmbZoneType->SetBaseList(m_pDataTypeLL);
	CExBaseList  *pListTemp = (CExBaseList  *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_Time);//显示动作时误差类型
	ui->m_cmb->SetBaseList(pListTemp);
	QButtonGroup *pZoneN1 = new QButtonGroup(this);
	pZoneN1->addButton(ui->m_checkForward,0);
	pZoneN1->addButton(ui->m_checkReverse,1);
    ui->m_labTips->raise();
	ui->m_labTips->setVisible(false);
	ui->m_labTips->setFont(*g_pSttGlobalFont);

	//英文版程序显示不全20241021 luozibing
	if (g_sLangTxt_Distance_ErrorRelAndAbs.GetLength() * 7 > ui->m_cmb->minimumWidth())
	{
		ui->m_cmb->setMinimumWidth(g_sLangTxt_Distance_ErrorRelAndAbs.GetLength() * 7);
		ui->m_txtPlus_3->setMinimumWidth(g_sLangTxt_Distance_ErrorRelAndAbs.GetLength() * 7);
	}
}
void QDistanceAddInterPhaseDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->m_labZSetting, g_sLangID_Distance_ZImpValue, XLang_Ctrls_QLabel);//阻抗(Ω):
	xlang_SetLangStrToWidget(ui->m_labZAng, g_sLangID_Gradient_ImpAngle, XLang_Ctrls_QLabel);//阻抗角(°):
	xlang_SetLangStrToWidget(ui->m_labTSetting, g_sLangID_Distance_SetActionTime, XLang_Ctrls_QLabel);//整定动作时间(s):
	xlang_SetLangStrToWidget(ui->m_labFaultCurrent, g_sLangID_State_ShortI, XLang_Ctrls_QLabel);//短路电流(A):
	xlang_SetLangStrToWidget(ui->m_labZoneType, g_sLangID_Distance_AddMultZone, XLang_Ctrls_QLabel);//区段:

	xlang_SetLangStrToWidget(ui->m_labFaultType, g_sLangID_Distance_FaultTypeSel, XLang_Ctrls_QLabel);//故障类型选择:
	xlang_SetLangStrToWidget(ui->m_labFaultDirection, g_sLangID_Distance_FailDirectSel, XLang_Ctrls_QLabel);//故障方向选择:
	xlang_SetLangStrToWidget(ui->m_labRate, g_sLangID_Distance_Percent, XLang_Ctrls_QLabel);//百分比(%):

	xlang_SetLangStrToWidget(ui->groupBox, g_sLangID_StateEstimate_ResultEstimate, XLang_Ctrls_QGroupBox);//结果评估
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_ErrorType);//误差类型:
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	ui->m_labType_2->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	ui->m_labRel_2->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_labPlus_3, g_sLangID_ActionTime_AbsErrPos, XLang_Ctrls_QLabel);//绝对误差(s)+:
	xlang_SetLangStrToWidget(ui->m_labMinus_3, g_sLangID_ActionTime_AbsErrNeg, XLang_Ctrls_QLabel);//绝对误差(s)-:

	xlang_SetLangStrToWidget(ui->m_checkForward, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(ui->m_checkReverse, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(ui->m_btnSave, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnclose, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消
	
		
	CString strTile;//添加相间接地故障
	xlang_GetLangStrByFile(strTile, g_sLangID_Distance_AddOneTileLL);
	setWindowTitle(strTile);
}
void QDistanceAddInterPhaseDlg::slot_ZoneTypeCurrentIndexChanged(int index)
{
	UpadatePageByZoneType();//区段选择更新参数显示 20240924 luozibing
	UpdateBtnEnable(ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);
}
void QDistanceAddInterPhaseDlg::UpdateBtnEnable(BOOL bEnable)
{
	ui->m_txtTSetting->setEnabled(bEnable);
	ui->m_txtPlus_3->setEnabled(bEnable);
	ui->m_txtMinus_3->setEnabled(bEnable);
	ui->m_txtRel->setEnabled(bEnable);
	//ui->m_cmb->setEnabled(bEnable);

	//20240923 luozibing 设置部分控件不可编辑
	ui->m_txtZSetting->setEnabled(false);
	ui->m_txtTSetting->setEnabled(bEnable);
	ui->m_txtR->setEnabled(false);
	ui->m_txtX->setEnabled(false);
	//ui->m_txtZAng->setEnabled(bEnable);
}
void QDistanceAddInterPhaseDlg::on_m_checkAB_clicked(bool checked)
{
	CheckFaultTypeState();
}

void QDistanceAddInterPhaseDlg::on_m_checkBC_stateChanged(int arg1)
{
	CheckFaultTypeState();
}

void QDistanceAddInterPhaseDlg::on_m_checkCA_stateChanged(int arg1)
{
	CheckFaultTypeState();
}
void QDistanceAddInterPhaseDlg::CheckFaultTypeState(BOOL bShow)
{
	if (!ui->m_checkAB->isChecked()&&\
		!ui->m_checkBC->isChecked()&&\
		!ui->m_checkCA->isChecked())
	{
		ui->m_checkAB->setChecked(true);
		if (bShow)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类型")*/);
		}
		
	}
}
void QDistanceAddInterPhaseDlg::on_m_checkForward_clicked(bool checked)
{
	CheckFaultDirectionState();
}

void QDistanceAddInterPhaseDlg::on_m_checkReverse_stateChanged(int arg1)
{
	CheckFaultDirectionState();
}
void QDistanceAddInterPhaseDlg::CheckFaultDirectionState(BOOL bShow)
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
void QDistanceAddInterPhaseDlg::on_m_checkRate_105_clicked(bool checked)
{
	CheckRateState();
}

void QDistanceAddInterPhaseDlg::on_m_checkRate_095_stateChanged(int arg1)
{
	CheckRateState();
}

void QDistanceAddInterPhaseDlg::on_m_checkRate_070_stateChanged(int arg1)
{
	CheckRateState();
}

void QDistanceAddInterPhaseDlg::on_m_checkRate_101_clicked(bool checked)
{
	CheckRateState();
	ui->m_txtRate_101->setEnabled(checked);
}
void QDistanceAddInterPhaseDlg::CheckRateState(BOOL bShow)
{
	if (!ui->m_checkRate_105->isChecked()&&\
		!ui->m_checkRate_095->isChecked()&&\
		!ui->m_checkRate_070->isChecked()&&\
		!ui->m_checkRate_101->isChecked())
	{
		ui->m_checkRate_105->setChecked(true);
		if (bShow)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneRate/*("请至少勾选一个倍数")*/);
		}
	}
}
void QDistanceAddInterPhaseDlg::on_m_btnSave_clicked()
{
	this->done(Accepted);
}

void QDistanceAddInterPhaseDlg::on_m_btnclose_clicked()
{
	this->close();
}
//void QDistanceAddInterPhaseDlg::on_m_txtZSetting_editingFinished()
//{
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

void QDistanceAddInterPhaseDlg::on_m_txtZAng_editingFinished()
{
	////20240722 huangliang 判断是否为定值，是定值就不需要处理
	//if (ui->m_txtZAng->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtZAng)->IsSetting())
	//	{
	//		return;
	//	}
	//}
	//根据区段设置不同id的阻抗角值
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	CString strZAng;
	//根据区段设置不同id的阻抗定值及其对应R X值

	//20241024 luozibing 区段下拉框显示数据 是根据配置文件中信息得出 通过区段值判断区段
	if (nZoneValue == STT_MULTI_MACRO_ZONE1 || nZoneValue == STT_MULTI_MACRO_ZONE2 || \
		nZoneValue == STT_MULTI_MACRO_ZONE3 || nZoneValue == STT_MULTI_MACRO_ZONE4 || \
		nZoneValue == STT_MULTI_MACRO_ZONE5 || nZoneValue == STT_MULTI_MACRO_ZONELine)
	{
		strZAng = GetZAngIDByZoneValue(nZoneValue, CHAR_DISTANCE_FAULT_TYPE_LL);
		if (strZAng != "")
		{
			ui->m_txtZAng->setText(CheckDataMinMax(ui->m_txtZAng->text(), strZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
			SetZRXValueByZAng(nZoneValue);
		}
	}
	else if (nZoneValue == STT_MULTI_MACRO_ZONEAll)
	{
		CDataTypeValue *pDataValue = (CDataTypeValue *)m_pDataTypeLL->GetHead();
		int nZone = pDataValue->m_strIndex.toInt();
		strZAng = GetZAngIDByZoneValue(nZone, CHAR_DISTANCE_FAULT_TYPE_LL);
		if (strZAng != "")
		{
			ui->m_txtZAng->setText(CheckDataMinMax(ui->m_txtZAng->text(), strZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
			SetZRXValueByZAng(nZone);
		}
	}
	else
	{
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
		ui->m_txtZAng->setText(CheckDataMinMax(ui->m_txtZAng->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE6, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	}
}
//void QDistanceAddInterPhaseDlg::on_m_txtR_editingFinished()
//{
//	ui->m_txtR->setText(CheckDataMinMax(ui->m_txtR->text(), STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
//	CString strNewZSetting,StrNewZAng;
//	CheckZSettingAndZAng(ui->m_txtR->text(),ui->m_txtX->text(),strNewZSetting,StrNewZAng);
//	ui->m_txtZSetting->setText(CheckDataMinMax(strNewZSetting, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
//	ui->m_txtZAng->setText(CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
//}
//void QDistanceAddInterPhaseDlg::on_m_txtX_editingFinished()
//{
//	ui->m_txtX->setText(CheckDataMinMax(ui->m_txtX->text(), STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
//	CString strNewZSetting,StrNewZAng;
//	CheckZSettingAndZAng(ui->m_txtR->text(),ui->m_txtX->text(),strNewZSetting,StrNewZAng);
//	ui->m_txtZSetting->setText(CheckDataMinMax(strNewZSetting, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
//	ui->m_txtZAng->setText(CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
//}
void QDistanceAddInterPhaseDlg::on_m_txtTSetting_editingFinished()
{
	ui->m_txtTSetting->setText(CheckDataMinMax(ui->m_txtTSetting->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE6,STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddInterPhaseDlg::on_m_txtRel_editingFinished()
{
	ui->m_txtRel->setText(CheckDataMinMax(ui->m_txtRel->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddInterPhaseDlg::on_m_txtPlus_3_editingFinished()
{
	ui->m_txtPlus_3->setText(CheckDataMinMax(ui->m_txtPlus_3->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddInterPhaseDlg::on_m_txtMinus_3_editingFinished()
{
	ui->m_txtMinus_3->setText(CheckDataMinMax(ui->m_txtMinus_3->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddInterPhaseDlg::on_m_txtFaultCurrent_editingFinished()
{
	ui->m_txtFaultCurrent->setText(CheckDataMinMax(ui->m_txtFaultCurrent->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT, STT_MULTI_MACRO_CURR_MAX, STT_MULTI_MACRO_CURR_MIN, STT_MULTI_MACRO_PLACES_3));
}
void QDistanceAddInterPhaseDlg::on_m_txtRate_101_editingFinished()
{
	ui->m_txtRate_101->setText(CheckDataMinMax(ui->m_txtRate_101->text(),0,0,1));
}
void QDistanceAddInterPhaseDlg::SetApplyTips(CString strTips)
{
	ui->m_labTips->setText(strTips);
	ui->m_labTips->setVisible(true);
	m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}
void QDistanceAddInterPhaseDlg::timerEvent(QTimerEvent* ev)
{
	if(ev->timerId() == m_nTipsTime){
		ui->m_labTips->setVisible(false);
	}
}
void QDistanceAddInterPhaseDlg::on_m_cmb_currentIndexChanged(int index)
{
	CExBaseList *pZoneType = ui->m_cmbZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	int nZoneValue = CString_To_long(pZoneType->GetAt(ui->m_cmbZoneType->currentIndex())->m_strID);
	UpdateErrorLogicValue(index, nZoneValue);
}
void QDistanceAddInterPhaseDlg::SetValueToPage(CDvmData *pData)
{
	//20240822 luozibing 当前添加相间类型测试项 设置单项接地区段类型为0
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
		pData->m_strValue.setNum(0);
	}

	//if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
	//{//默认选择LL1
	//	ui->m_cmbZoneType->setCurrentIndex(0);
	//	UpdateBtnEnable(ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);
	//}
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
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
		ui->m_checkRate_101->setChecked(pData->m_strValue == "1");
		ui->m_txtRate_101->setEnabled(pData->m_strValue == "1");
		CDvmData *pData100 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100);
		if(pData100 != NULL)
		{
			double nrate = CString_To_double(pData100->m_strValue);
			CString strTmp;
			strTmp.setNum(nrate*100);
			ui->m_txtRate_101->setText(CheckDataMinMax(strTmp,0,0,1));
		}
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
	{//20240924 luozibing 根据当前区段下拉框显示数据设置 所有区域 界面显示下拉框首个区段数据
		CDataTypeValue *pDataValue = (CDataTypeValue *)m_pDataTypeLL->GetHead();
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
void QDistanceAddInterPhaseDlg::UpadateValueToPage_Zone1(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1)
	{
		ui->m_txtPlus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1)
	{
		ui->m_txtMinus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1)
	{
		ui->m_txtRel->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1)
	{
		//ui->m_cmb->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
				ui->m_cmb->setCurrentIndex(pType->FindIndex(pDataValue));
			}
		}
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE1);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	/*else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE1)
	{
		ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE1)
	{
		ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}*/
}
void QDistanceAddInterPhaseDlg::SetValueToPage__Zone1(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK)
	{
		ui->m_checkAB->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK)
	{
		ui->m_checkBC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK)
	{
		ui->m_checkCA->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK)
	{
		//ui->m_checkABC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
	UpadateValueToPage_Zone1(pData);
}
void QDistanceAddInterPhaseDlg::UpadateValueToPage_Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2)
	{
		ui->m_txtPlus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2)
	{
		ui->m_txtMinus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2)
	{
		ui->m_txtRel->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2)
	{
		//ui->m_cmb->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
				ui->m_cmb->setCurrentIndex(pType->FindIndex(pDataValue));
			}
		}
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));

		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE2);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	/*else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE2)
	{
	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE2)
	{
	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}*/
}
void QDistanceAddInterPhaseDlg::SetValueToPage__Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK)
	{
		ui->m_checkAB->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK)
	{
		ui->m_checkBC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK)
	{
		ui->m_checkCA->setChecked(pData->m_strValue == "1");
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK)
	//{
	//	ui->m_checkABC->setChecked(pData->m_strValue == "1");
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
	UpadateValueToPage_Zone2(pData);
}
void QDistanceAddInterPhaseDlg::UpadateValueToPage_Zone3(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3)
	{
		ui->m_txtPlus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3)
	{
		ui->m_txtMinus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3)
	{
		ui->m_txtRel->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3)
	{
		//ui->m_cmb->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
				ui->m_cmb->setCurrentIndex(pType->FindIndex(pDataValue));
			}
		}
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));

		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE3);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE3)
	//{
	//	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE3)
	//{
	//	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	//}
}
void QDistanceAddInterPhaseDlg::SetValueToPage__Zone3(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK)
	{
		ui->m_checkAB->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK)
	{
		ui->m_checkBC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK)
	{
		ui->m_checkCA->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK)
	{
		//ui->m_checkABC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
	UpadateValueToPage_Zone3(pData);
}
void QDistanceAddInterPhaseDlg::UpadateValueToPage_Zone4(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4)
	{
		ui->m_txtPlus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4)
	{
		ui->m_txtMinus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4)
	{
		ui->m_txtRel->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4)
	{
		//ui->m_cmb->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
				ui->m_cmb->setCurrentIndex(pType->FindIndex(pDataValue));
			}
		}
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));

		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE4);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE4)
	//{
	//	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE4)
	//{
	//	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	//}
}
void QDistanceAddInterPhaseDlg::SetValueToPage__Zone4(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK)
	{
		ui->m_checkAB->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK)
	{
		ui->m_checkBC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK)
	{
		ui->m_checkCA->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK)
	{
		//ui->m_checkABC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
	UpadateValueToPage_Zone4(pData);
}
void QDistanceAddInterPhaseDlg::UpadateValueToPage_Zone5(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else  if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5)
	{
		ui->m_txtPlus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5)
	{
		ui->m_txtMinus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5)
	{
		ui->m_txtRel->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5)
	{
		//ui->m_cmb->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
				ui->m_cmb->setCurrentIndex(pType->FindIndex(pDataValue));
			}
		}
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5)
	//{
	//	ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
	//	//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		SetZRXValueByZAng(STT_MULTI_MACRO_ZONE5);
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	/*else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE5)
	{
	ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE5)
	{
	ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}*/
}
void QDistanceAddInterPhaseDlg::SetValueToPage__Zone5(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK)
	{
		ui->m_checkAB->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK)
	{
		ui->m_checkBC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK)
	{
		ui->m_checkCA->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK)
	{
		//ui->m_checkABC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
	UpadateValueToPage_Zone5(pData);
}
void QDistanceAddInterPhaseDlg::UpadateValueToPage_Zone6(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE6)
	{
		ui->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6)
	{
		ui->m_txtPlus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6)
	{
		ui->m_txtMinus_3->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6)
	{
		ui->m_txtRel->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6)
	{
		//ui->m_cmb->setCurrentIndex(CString_To_long(pData->m_strValue));
		CDataType *pType = (CDataType *)ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->FindByIndex(pData->m_strValue);
			if (pDataValue != NULL)
			{
				ui->m_cmb->setCurrentIndex(pType->FindIndex(pDataValue));
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6)
	{
		ui->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
		//ui->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));//20240723 huangliang 设置对象地址
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE6)
	{
		ui->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
		//ui->m_txtZAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1), 1);//20240723 huangliang 设置对象地址
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE6)
	{
		ui->m_txtR->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE6)
	{
		ui->m_txtX->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	}
}
void QDistanceAddInterPhaseDlg::SetValueToPage__Zone6(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB6_CHECK)
	{
		ui->m_checkAB->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC6_CHECK)
	{
		ui->m_checkBC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA6_CHECK)
	{
		ui->m_checkCA->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC6_CHECK)
	{
		//ui->m_checkABC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L6)
	{
		ui->m_checkForward->setChecked(pData->m_strValue == "1");
		ui->m_checkReverse->setChecked(pData->m_strValue != "1");
	}
	UpadateValueToPage_Zone6(pData);
}
void QDistanceAddInterPhaseDlg::GetPageToValue(CDvmData *pData)
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
		pData->m_strValue.setNum((int)ui->m_checkRate_101->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100)
	{
		
		CString strTmp;
		strTmp.setNum(CString_To_double(ui->m_txtRate_101->text())/ 100);
		pData->m_strValue = CheckDataMinMax(strTmp,0,0,3);
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
void QDistanceAddInterPhaseDlg::GetPageToInitValue_Zone1(CDvmData *pData)
{//20240821 luozibing 设置区段对应参数值 
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1)
	{
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToValue_Zone1(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
	{
		pData->m_strValue.setNum(1);
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
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1)
	{
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE1)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToInitValue_Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2)
	{
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE2)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE2)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToValue_Zone2(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK)
	{
		pData->m_strValue.setNum(1);
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
	GetPageToInitValue_Zone2(pData);
}
void QDistanceAddInterPhaseDlg::GetPageToInitValue_Zone3(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3)
	{
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE3)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE3)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToValue_Zone3(CDvmData *pData)
{
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
		pData->m_strValue.setNum(1);
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
	GetPageToInitValue_Zone3(pData);
}
void QDistanceAddInterPhaseDlg::GetPageToInitValue_Zone4(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4)
	{
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE4)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE4)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToValue_Zone4(CDvmData *pData)
{
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
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone4(pData);
}
void QDistanceAddInterPhaseDlg::GetPageToInitValue_Zone5(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5)
	{
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE5)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE5)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToValue_Zone5(CDvmData *pData)
{
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
		pData->m_strValue.setNum(1);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
	GetPageToInitValue_Zone5(pData);
}
void QDistanceAddInterPhaseDlg::GetPageToInitValue_Zone6(CDvmData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE6)
	{
		pData->m_strValue = ui->m_txtTSetting->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB6_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkAB->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC6_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkBC->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA6_CHECK)
	{
		pData->m_strValue.setNum((int)ui->m_checkCA->isChecked());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC6_CHECK)
	//{
	//	pData->m_strValue.setNum((int)ui->m_checkABC->isChecked());
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L6)
	{
		pData->m_strValue.setNum((int)ui->m_checkForward->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6)
	{
		pData->m_strValue = ui->m_txtPlus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6)
	{
		pData->m_strValue = ui->m_txtMinus_3->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6)
	{
		pData->m_strValue = ui->m_txtRel->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6)
	{
		//pData->m_strValue.setNum(ui->m_cmb->currentIndex());
		CExBaseList *pType = ui->m_cmb->GetBaseList();
		if (pType != NULL)
		{
			CDataTypeValue *pDataValue = (CDataTypeValue *)pType->GetAt(ui->m_cmb->currentIndex());
			if (pDataValue != NULL)
			{
				pData->m_strValue = pDataValue->m_strIndex;
			}
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6)
	{
		pData->m_strValue = ui->m_txtZSetting->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE6)
	{
		pData->m_strValue = ui->m_txtZAng->GetText();//20240723 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE6)
	{
		pData->m_strValue = ui->m_txtR->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE6)
	{
		pData->m_strValue = ui->m_txtX->text();
	}
}
void QDistanceAddInterPhaseDlg::GetPageToValue_Zone6(CDvmData *pData)
{
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
		pData->m_strValue.setNum(1);
	}
	GetPageToInitValue_Zone6(pData);
}
void QDistanceAddInterPhaseDlg::GetPageToValue_ZoneALL(CDvmData *pData)
{
	if (m_pDataTypeLL->FindByIndex(STT_MULTI_MACRO_ZONE1) != NULL)
	{
		GetPageToInitValue_Zone1(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}

	if (m_pDataTypeLL->FindByIndex(STT_MULTI_MACRO_ZONE2) != NULL)
	{
		GetPageToInitValue_Zone2(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLL->FindByIndex(STT_MULTI_MACRO_ZONE3) != NULL)
	{
		GetPageToInitValue_Zone3(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLL->FindByIndex(STT_MULTI_MACRO_ZONE4) != NULL)
	{
		GetPageToInitValue_Zone4(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (m_pDataTypeLL->FindByIndex(STT_MULTI_MACRO_ZONE5) != NULL)
	{
		GetPageToInitValue_Zone5(pData);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK)
		{
			pData->m_strValue.setNum(1);
		}
	}
	else
	{
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK)
		{
			pData->m_strValue.setNum(0);
		}
	}
	if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK)
	{
		pData->m_strValue.setNum(0);
	}
}
void QDistanceAddInterPhaseDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100);
	CheckAllPresence_Zone1();
	CheckAllPresence_Zone2();
	CheckAllPresence_Zone3();
	CheckAllPresence_Zone4();
	CheckAllPresence_Zone5();
	CheckAllPresence_Zone6();
}
void QDistanceAddInterPhaseDlg::CheckAllPresence_Zone1()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1);
}
void QDistanceAddInterPhaseDlg::CheckAllPresence_Zone2()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2);
}
void QDistanceAddInterPhaseDlg::CheckAllPresence_Zone3()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3);
}
void QDistanceAddInterPhaseDlg::CheckAllPresence_Zone4()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4);
}
void QDistanceAddInterPhaseDlg::CheckAllPresence_Zone5()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5);
}
void QDistanceAddInterPhaseDlg::CheckAllPresence_Zone6()
{
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC6_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6);
}
void QDistanceAddInterPhaseDlg::MinCheckLeastOne()
{
	QDistanceAddMultBase::MinCheckLeastOne();
	CheckFaultTypeState(FALSE);
	CheckFaultDirectionState(FALSE);
	CheckRateState(FALSE);
}
void QDistanceAddInterPhaseDlg::InitPageShowByParas()
{
	QDistanceAddMultBase::InitPageShowByParas();
	DisConnectAll_SigSlot();
	ui->m_cmbZoneType->SetBaseList(m_pDataTypeLL);
	ConnectAll_SigSlot();

	//20240821 luozibing 根据上次设置数据设置区段类型
	CDvmData *pZone1 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK);
	CDvmData *pZone2 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK);
	CDvmData *pZone3 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK);
	CDvmData *pZone4 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK);
	CDvmData *pZone5 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK);
	CDvmData *pZone6 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK);
	if (pZone1 == NULL || pZone2 == NULL || pZone3 == NULL || pZone4 == NULL || pZone5 == NULL || pZone6 == NULL)
	{
		return;
	}

	CString strTypeID;
	if (pZone1->m_strValue == "1"\
		&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段1
		strTypeID.setNum(STT_MULTI_MACRO_ZONE1);
		if (ui->m_cmbZoneType->SetSelByID(strTypeID) == NULL)
		{
			strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
			ui->m_cmbZoneType->SetSelByID(strTypeID);
		}
	}
	else if (pZone2->m_strValue == "1"\
		&&pZone3->m_strValue != "1"&&pZone1->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段2
		strTypeID.setNum(STT_MULTI_MACRO_ZONE2);
		if (ui->m_cmbZoneType->SetSelByID(strTypeID) == NULL)
		{
			strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
			ui->m_cmbZoneType->SetSelByID(strTypeID);
		}
	}
	else if (pZone3->m_strValue == "1"\
		&&pZone2->m_strValue != "1"&&pZone1->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段3
		strTypeID.setNum(STT_MULTI_MACRO_ZONE3);
		if (ui->m_cmbZoneType->SetSelByID(strTypeID) == NULL)
		{
			strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
			ui->m_cmbZoneType->SetSelByID(strTypeID);
		}
	}
	else if (pZone4->m_strValue == "1"\
		&&pZone1->m_strValue != "1"&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone5->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段4
		strTypeID.setNum(STT_MULTI_MACRO_ZONE4);
		if (ui->m_cmbZoneType->SetSelByID(strTypeID) == NULL)
		{
			strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
			ui->m_cmbZoneType->SetSelByID(strTypeID);
		}
	}
	else if (pZone5->m_strValue == "1"\
		&&pZone1->m_strValue != "1"&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone6->m_strValue != "1")
	{//区段5
		strTypeID.setNum(STT_MULTI_MACRO_ZONE5);
		if (ui->m_cmbZoneType->SetSelByID(strTypeID) == NULL)
		{
			strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
			ui->m_cmbZoneType->SetSelByID(strTypeID);
		}
	}
	else if (pZone6->m_strValue != "1"&&\
		(pZone1->m_strValue == "1" || m_pDataTypeLL->FindByID("2") == NULL) && \
		(pZone2->m_strValue == "1" || m_pDataTypeLL->FindByID("3") == NULL) && \
		(pZone3->m_strValue == "1" || m_pDataTypeLL->FindByID("4") == NULL) && \
		(pZone4->m_strValue == "1" || m_pDataTypeLL->FindByID("5") == NULL) && \
		(pZone5->m_strValue == "1" || m_pDataTypeLL->FindByID("6") == NULL))
	{//全部区段
		strTypeID.setNum(STT_MULTI_MACRO_ZONEAll);
		if (ui->m_cmbZoneType->SetSelByID(strTypeID) == NULL)
		{
			strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
			ui->m_cmbZoneType->SetSelByID(strTypeID);
		}
	}
	else if (pZone6->m_strValue == "1"&&\
		pZone1->m_strValue != "1"&&pZone2->m_strValue != "1"&&pZone3->m_strValue != "1"\
		&&pZone4->m_strValue != "1"&&pZone5->m_strValue != "1")
	{//线路长度
		strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
		ui->m_cmbZoneType->SetSelByID(strTypeID);
	}
	else
	{
		pZone1->m_strValue.setNum(0);
		pZone2->m_strValue.setNum(0);
		pZone3->m_strValue.setNum(0);
		pZone4->m_strValue.setNum(0);
		pZone5->m_strValue.setNum(0);
		pZone6->m_strValue.setNum(1);
		strTypeID.setNum(STT_MULTI_MACRO_ZONELine);
		ui->m_cmbZoneType->SetSelByID(strTypeID);
	}
	UpdateBtnEnable(ui->m_cmbZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);
}
void QDistanceAddInterPhaseDlg::UpadatePageByZoneType()
{
	POS pos = m_pDistanceparas->GetHeadPosition();
	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pDistanceparas->GetNext(pos);
		UpadateValueToPage(pData);
	}
}
void QDistanceAddInterPhaseDlg::UpadateValueToPage(CDvmData *pData)
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
		CDataTypeValue *pDataValue = (CDataTypeValue *)m_pDataTypeLL->GetHead();
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
void QDistanceAddInterPhaseDlg::ConnectAll_SigSlot()
{
	connect(ui->m_cmbZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ZoneTypeCurrentIndexChanged(int)));
}
void QDistanceAddInterPhaseDlg::DisConnectAll_SigSlot()
{
	disconnect(ui->m_cmbZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ZoneTypeCurrentIndexChanged(int)));
}
void QDistanceAddInterPhaseDlg::SetZRXValueByZAng(int nZoneValue)
{
	CString strR, strX, strZone;
	switch (nZoneValue)
	{
	case STT_MULTI_MACRO_ZONE1:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE1;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE1;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1;
		break;
	case STT_MULTI_MACRO_ZONE2:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE2;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE2;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2;
		break;
	case STT_MULTI_MACRO_ZONE3:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE3;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE3;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3;
		break;
	case STT_MULTI_MACRO_ZONE4:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE4;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE4;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4;
		break;
	case STT_MULTI_MACRO_ZONE5:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE5;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE5;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5;
		break;
	case STT_MULTI_MACRO_ZONELine:
		strR = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE6;
		strX = STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE6;
		strZone = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6;
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
		CString strTemp = GetZsetByZAng(ui->m_txtZAng->text(), nZoneValue, CHAR_DISTANCE_FAULT_TYPE_LL);
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
