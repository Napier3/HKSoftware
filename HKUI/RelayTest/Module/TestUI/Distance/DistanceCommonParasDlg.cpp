#include "DistanceCommonParasDlg.h"
#include "ui_DistanceCommonParasDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttUIGlobalDef.h"

extern CFont *g_pSttGlobalFont;

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QDistanceCommonParasDlg::QDistanceCommonParasDlg(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::QDistanceCommonParasDlg)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
    ui->setupUi(this);
	m_pParas = NULL;
	m_nModify = 0;
	InitLanuage();
	InitUI();
}

QDistanceCommonParasDlg::~QDistanceCommonParasDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}
void QDistanceCommonParasDlg::InitUI()
{	//20340617 luozibing 添加页面显示数据
	ui->m_cmbFaultTrig->addItems(QStringList()<<g_sLangTxt_State_Trigger_Time/*("时间触发")*/<<g_sLangTxt_State_Trigger_Manu/*("手动触发")*/<<g_sLangTxt_State_Trigger_Bin/*("开入量触发")*/);
	ui->m_cmbPTPos->addItems(QStringList()<<g_sLangTxt_CBOperate_PTPos/*("母线侧")*/<<g_sLangTxt_CBOperate_TPos/*("线路侧")*/);
	ui->m_cmbCTPos->addItems(QStringList()<<g_sLangTxt_CBOperate_CTPos1/*("指向母线")*/<<g_sLangTxt_CBOperate_TPos1/*("指向线路")*/);
	ui->m_cmbBreaker->addItems(QStringList()<<g_sLangTxt_CBOperate_NotSimulated/*("不模拟")*/<<g_sLangTxt_ChMaps_Analog/*("模拟")*/);
    ui->m_cmbVzDefine->addItems(QStringList()<<_T("0")<<_T("Ua")<<_T("Ub")<<_T("Uc")<<g_sLangTxt_Distance_VzDefine/*("√3×3U0")*/<<_T("3U0")<<_T("-3U0"));
	ui->m_cmbPsuVzRef->addItems(QStringList()<<g_sLangTxt_Native_UaPhase/*("Ua相位")*/<<g_sLangTxt_Native_UbPhase/*("Ub相位")*/<<g_sLangTxt_Native_UcPhase/*("Uc相位")*/<<g_sLangTxt_CBOperate_UabPhase/*("Uab相位")*/<<g_sLangTxt_CBOperate_UbcPhase/*("Ubc相位")*/<<g_sLangTxt_CBOperate_UcaPhase/*("Uca相位")*/);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

#ifndef _PSX_QT_LINUX_
	//20240807 luozibing 根据缩放比例设置lab显示宽度
	int nleng = ui->m_labVzPh->text().length();
    float horizontalDPI = GetDeviceCaps_LOGPIXELSX();
    float verticalDPI = GetDeviceCaps_LOGPIXELSY();
	int dpi = (horizontalDPI + verticalDPI) / 2;
	double dZoomRatio = dpi / 96.0;
	ui->m_labVzPh->setMinimumWidth(nleng * 11 * dZoomRatio);
#endif

	setFont(*g_pSttGlobalFont);
}
void QDistanceCommonParasDlg::InitLanuage()
{
	
	ui->m_labPreFaultTime->setText(GetLangStrByFileAddSuffix(g_sLangID_Native_FaultPreTimeS));//故障前时间(s):
	ui->m_labFaultTime->setText(GetLangStrByFileAddSuffix(g_sLangID_Native_FaultTimeMargin));//故障时间裕度(s):
	xlang_SetLangStrToWidget(ui->m_labMinTime, g_sLangID_Distance_MinTrip, XLang_Ctrls_QLabel);//最小动作时间(s):
	ui->m_labTimeAfter->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_TimeAfterTrigger));//保护动作后持续时间(s):
	xlang_SetLangStrToWidget(ui->m_labLine, g_sLangID_Distance_ZLineSet, XLang_Ctrls_QLabel);//线路阻抗(Ω):
	ui->m_labPTPos->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_PTVPos));//TV安装位置:
	ui->m_labCTPos->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_CTPos));//TA正极性:
	ui->m_labILoad->setText(GetLangStrByFileAddSuffix(g_sLangID_LoadI));//负荷电流(A):
	ui->m_labILoadPh->setText(GetLangStrByFileAddSuffix(g_sLangID_State_LoadAngle));//负荷功角:
	ui->m_labFaultTrig->setText(GetLangStrByFileAddSuffix(g_sLangID_Native_FaultTrigMethod));//故障触发方式:
	ui->m_labBreaker->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_SimulateBreakerDelay));//断路器模拟:
	ui->m_labBreakTime->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_BrkBreakTime));//分闸时间(ms):
	ui->m_labCloseTime->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_BrkCloseTime));//合闸时间(ms):
	ui->m_labVzDefine->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_VzDefine));//抽取电压输出定义:
	ui->m_labPsuVzRef->setText(GetLangStrByFileAddSuffix(g_sLangID_CBOperate_PsuVzRefPhase));//抽取电压参考相定义:

	xlang_SetLangStrToWidget(ui->m_labVzPh, g_sLangID_Distance_VzPh, XLang_Ctrls_QLabel);//抽取电压相角(相对参考相):
	xlang_SetLangStrToWidget(ui->m_btnOK, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnCancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;
	xlang_GetLangStrByFile(strTile, g_sLangID_Gradient_CommonParas);//通用参数设置
	setWindowTitle(strTile);
}
CString QDistanceCommonParasDlg::GetLangStrByFileAddSuffix(CString strID)
{
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, strID);//故障前时间(s):
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	return strtemp;
}
void QDistanceCommonParasDlg::SetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 读取数据转换到界面中
	if(pParas == NULL)
		return;
	m_pParas = pParas;
	CheckAllPresence(m_pParas);
	m_nModify = 0;
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QDistanceCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME)
	{
		ui->m_txtPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME)
	{
		ui->m_txtFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER)
	{
		ui->m_txtTimeAfter->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE)
	{
		ui->m_cmbFaultTrig->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS)
	{
		ui->m_cmbPTPos->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS)
	{
		ui->m_cmbCTPos->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD)
	{
		ui->m_txtILoad->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH)
	{
		ui->m_txtILoadPh->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY)
	{
		ui->m_cmbBreaker->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME)
	{
		ui->m_txtBreakTime->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME)
	{
		ui->m_txtCloseTime->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE)
	{
		ui->m_cmbVzDefine->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE)
	{
		ui->m_cmbPsuVzRef->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH)
	{
		ui->m_txtVzPh->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_MINTRIPTIME)
	{
		//ui->m_txtMinTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_txtMinTime->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));//20240722 huangliang 设置对象地址
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE)
	{//20240814 luozibing 新增线路阻抗参数 判断当前选择项是否为线路长度，如果为线路长度显示线路长度阻抗定值
		/*CSttMacroTestParaDatas *pParent = (CSttMacroTestParaDatas *)pData->GetParent();

		CSttMacroTestParaData *pZSetting = (CSttMacroTestParaData *)pParent->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
		CSttMacroTestParaData *pZoneType = (CSttMacroTestParaData *)pParent->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
		int nZoneType = CString_To_long(pZoneType->m_strValue);
		if (nZoneType == 5)
		{
			pData->m_strValue = pZSetting->m_strValue;
		}*/
		ui->m_txtLine->setText(CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
	}
}
void QDistanceCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 将界面设置参数填到链表
	if (pParas == NULL)
	{
		return;
	}
	CheckAllPresence(pParas);
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QDistanceCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_txtPreFaultTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME)
	{
		pData->m_strValue = ui->m_txtFaultTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER)
	{
		pData->m_strValue = ui->m_txtTimeAfter->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbFaultTrig->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS)
	{
		pData->m_strValue.Format("%d",ui->m_cmbPTPos->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS)
	{
		pData->m_strValue.Format("%d",ui->m_cmbCTPos->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD)
	{
		pData->m_strValue = ui->m_txtILoad->text();
	}
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH)
	{
		pData->m_strValue = ui->m_txtILoadPh->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY)
	{
		pData->m_strValue.Format("%d",ui->m_cmbBreaker->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME)
	{
		pData->m_strValue = ui->m_txtBreakTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME)
	{
		pData->m_strValue = ui->m_txtCloseTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbVzDefine->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbPsuVzRef->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH)
	{
		pData->m_strValue = ui->m_txtVzPh->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_MINTRIPTIME)
	{
		pData->m_strValue = ui->m_txtMinTime->GetText();//20240722 huangliang GetText()替换text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE)
	{//20240814 luozibing 新增线路阻抗参数
		pData->m_strValue = ui->m_txtLine->GetText();
	}
}
void QDistanceCommonParasDlg::on_m_txtPreFaultTime_editingFinished()
{
	ui->m_txtPreFaultTime->setText(CheckDataMinMax(ui->m_txtPreFaultTime->text(),999.999,0,3));
}
void QDistanceCommonParasDlg::on_m_txtFaultTime_editingFinished()
{
	ui->m_txtFaultTime->setText(CheckDataMinMax(ui->m_txtFaultTime->text(),999.999,0,3));
}
void QDistanceCommonParasDlg::on_m_txtTimeAfter_editingFinished()
{
	ui->m_txtTimeAfter->setText(CheckDataMinMax(ui->m_txtTimeAfter->text(),999.999,0,3));
}
void QDistanceCommonParasDlg::on_m_txtMinTime_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (ui->m_txtMinTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtMinTime)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtMinTime->setText(CheckDataMinMax(ui->m_txtMinTime->text(),999.999,0,3));
}
void QDistanceCommonParasDlg::on_m_txtILoad_editingFinished()
{
	ui->m_txtILoad->setText(CheckDataMinMax(ui->m_txtILoad->text(),20,0,3));
}

void QDistanceCommonParasDlg::on_m_txtILoadPh_editingFinished()
{
	ui->m_txtILoadPh->setText(CheckDataMinMax(ui->m_txtILoadPh->text(),360,-360,1));
}

void QDistanceCommonParasDlg::on_m_txtBreakTime_editingFinished()
{
	ui->m_txtBreakTime->setText(CheckDataMinMax(ui->m_txtBreakTime->text(),999999,0,0));
}

void QDistanceCommonParasDlg::on_m_txtCloseTime_editingFinished()
{
	ui->m_txtCloseTime->setText(CheckDataMinMax(ui->m_txtCloseTime->text(),999999,0,0));
}

void QDistanceCommonParasDlg::on_m_txtVzPh_editingFinished()
{	
	ui->m_txtVzPh->setText(CheckDataMinMax(ui->m_txtVzPh->text(),360,-360,1));
}

void QDistanceCommonParasDlg::on_m_cmbBreaker_currentIndexChanged(int index)
{
	if(index == 0)
	{
		ui->m_txtBreakTime->setEnabled(false);
		ui->m_txtCloseTime->setEnabled(false);
	}
	else
	{
		ui->m_txtBreakTime->setEnabled(true);
		ui->m_txtCloseTime->setEnabled(true);
	}
}

void QDistanceCommonParasDlg::on_m_cmbVzDefine_currentIndexChanged(int index)
{
	if(index == 1||index == 2 ||index == 3)
	{
		ui->m_cmbPsuVzRef->setEnabled(true);
		ui->m_txtVzPh->setEnabled(true);
	}
	else
	{
		ui->m_cmbPsuVzRef->setEnabled(false);
		ui->m_txtVzPh->setEnabled(false);
	}
}
void QDistanceCommonParasDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QDistanceCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}
void QDistanceCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	if (pParas == NULL)
	{
		return;
	}
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_MINTRIPTIME);

	//20240814 luozibing 新增线路阻抗参数
	CheckForPresence(pParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
}
void QDistanceCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
{//20240625 luozibing 通用参数修改后，修改表格中所有项数据通用参数
	CSttMacroTest *pSttMacroTest = NULL;
	CExBaseList *pItem = NULL;
	CSttMacroTestParaDatas *pParaDatas = NULL;

	POS pos = pAllItems->GetHeadPosition();

	while (pos!= NULL)
	{
		pItem = (CExBaseList*)pAllItems->GetNext(pos);

		if(pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pSttMacroTest = (CSttMacroTest *)pItem;
			pSttMacroTest->m_nModified = 1;
	
			pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE,"");

			if(pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
}
BOOL QDistanceCommonParasDlg::CheckItemsModify(CExBaseList *pAllItems,CExBaseList *pItem)
{
	if (pItem == NULL)
	{
		return FALSE;
	}
	CSttMacroTestParaDatas paraDatas;
	CheckAllPresence(&paraDatas);
	GetDatas(&paraDatas);

	POS pos = pItem->GetHeadPosition();
	while(pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pItem->GetNext(pos);
		CSttMacroTestParaData *pData_New = (CSttMacroTestParaData *)paraDatas.FindByID(pData->m_strID);
		if (pData_New == NULL)
		{
			continue;
		}
		if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE||pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS||pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE||pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE)
		{
			if (pData->m_strValue != pData_New->m_strValue)
			{
				m_nModify = 1;
				return TRUE;
			}
		}
		else
		{//浮点数判断差值的绝对值
			if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
			{
				m_nModify = 1;
				return TRUE;
			}
		}
		
	}
	//判断线路阻抗值是否被修改
		if (CheckZSetLineItemModify(pItem, &paraDatas))
		{
			return TRUE;
		}
	//CSttMacroTestParaData *pZoneType = (CSttMacroTestParaData *)pItem->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	//int nZoneType = CString_To_long(pZoneType->m_strValue);
	//if (nZoneType == STT_MULTI_MACRO_ZONELine)//20240814 luozibing 当前选中项为线路长度时 判断线路阻抗是否被修改
	//{
	//	if (CheckZSetLineItemModify(pItem, &paraDatas))
	//	{
	//		return TRUE;
	//	}
	//}
	//else
	//{	//20240814 luozibing 当前选中项不为线路长度时 遍历所有测试项中的线路长度测试项
	//	POS pos1 = pAllItems->GetHeadPosition();
	//	while (pos1)
	//	{
	//		CExBaseList *pItem = (CExBaseList*)pAllItems->GetNext(pos1);

	//		if (pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	//		{
	//			CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pItem;
	//			CSttMacroTestParaDatas *pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE, "");
	//			if (CheckZSetLineItemModify(pParaDatas, &paraDatas))
	//			{
	//				return TRUE;
	//			}
	//		}
	//	}
	//}
	return FALSE;
}
bool QDistanceCommonParasDlg::CheckZSetLineItemModify(CExBaseList *pItem, CExBaseList *pCommonItem)
{//20240814 luozibing 当前测试项为线路长度时比较阻抗值 判断是否被修改
	CSttMacroTestParaData *pZSetting_Line = (CSttMacroTestParaData *)pCommonItem->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);

	CSttMacroTestParaData *pZSetting_LineOld = (CSttMacroTestParaData *)pItem->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
	if (fabs(CString_To_double(pZSetting_LineOld->m_strValue) - CString_To_double(pZSetting_Line->m_strValue)) > 0.0001)
	{
		m_nModify = 1;
		return TRUE;
	}
	/*CSttMacroTestParaData *pZSetting = (CSttMacroTestParaData *)pItem->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	CSttMacroTestParaData *pZoneType = (CSttMacroTestParaData *)pItem->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	int nZoneType = CString_To_long(pZoneType->m_strValue);
	if (nZoneType == STT_MULTI_MACRO_ZONELine)
	{
	if (fabs(CString_To_double(pZSetting->m_strValue) - CString_To_double(pZSetting_Line->m_strValue))>0.0001)
		{
			m_nModify = 1;
			return TRUE;
		}
	}*/
	return FALSE;
}
void QDistanceCommonParasDlg::on_m_txtLine_editingFinished()
{
	ui->m_txtLine->setText(CheckDataMinMax(ui->m_txtLine->text(), STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
}
CString CheckDataMinMax(CString strValue, float fMax, float fMin, int nAfterPoint)
{	
	float fValue = strValue.toFloat();
	//double dvalue = CString_To_double(strValue);
	//double dMax = fMax;
	//double dMin = fMin;
	//最大值最小值相等时不判断最大最小值
	if (fMax != fMin)
	{
		if (fValue<fMin)
		{
			fValue = fMin;
		}
		else if (fValue>fMax)
		{
			fValue = fMax;
		}
	}
	//CString strFormat;
	//strFormat.Format(_T("%%.%df"), nAfterPoint);
	//CString strTmp;
	//strTmp.Format(strFormat.GetString(), dvalue);
	//return strTmp;
	return QString::number(fValue, 'f', nAfterPoint);
}
void CheckForPresence(CExBaseList *pParas,CString strID)
{
	//20240624 luozibing检查ID对应数据是否存在、不存在则添加
	if(pParas == NULL)
		return;
	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
	if(pData == NULL)
	{
		CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		pParas->AddNewChild(pNew);
	}
}
void CheckRxValue(CString &strR,CString &strX,CString strZSetting,CString strZAng)
{
	float fR,fX,fZSetting,fZAng;
	fZSetting = strZSetting.toFloat();
	fZAng = strZAng.toFloat();

	if(fZAng<-180.0)
	{
		fZAng+=360.0;
	}
	if(fZAng>360.0)
	{
		fZAng-=360.0;
	}

	fX= fZSetting*sin(fZAng*3.14159/180.0);
	fR= fZSetting*cos(fZAng*3.14159/180.0);
	
	strX.Format("%.3f",fX);
	strR.Format("%.3f",fR);
}
void CheckZSettingAndZAng(CString strR,CString strX,CString &strZSetting,CString &strZAng)
{
	float fR,fX,fZSetting,fZAng;
	fR = strR.toFloat();
	fX = strX.toFloat();
	fZSetting = hypot(fX,fR);
	if(fabs(fR)>0.0001)
	{
		fZAng=atan2(fX,fR)*180.0/3.14159;
	}	
	else 
	{
		fZAng=0.0;
	}
	strZSetting.Format("%.3f",fZSetting);
	strZAng.Format("%.1f",fZAng);
}
