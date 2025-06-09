#include "DistanceBinarysDlg.h"
#include "ui_DistanceBinarysDlg.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../SttUIGlobalDef.h"

extern CFont *g_pSttGlobalFont;

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QDistanceBinarysDlg::QDistanceBinarysDlg(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::QDistanceBinarysDlg)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
    ui->setupUi(this);
	m_pParas = NULL;
	m_nModify= 0;
    m_bDefault = FALSE;
	InitLanuage();
	InitUI();
}

QDistanceBinarysDlg::~QDistanceBinarysDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}
void QDistanceBinarysDlg::InitUI()
{	//20340617 luozibing 添加页面显示数据
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
	QStringList list_Out;
	list_Out.append(g_sLangTxt_SOE_Break/*("断开")*/);
	list_Out.append(g_sLangTxt_SOE_Shutting/*("闭合")*/);
	ui->m_cmb_B01->addItems(list_Out);
	ui->m_cmb_B02->addItems(list_Out);
	ui->m_cmb_B03->addItems(list_Out);
	ui->m_cmb_B04->addItems(list_Out);
	ui->m_cmb_B05->addItems(list_Out);
	ui->m_cmb_B06->addItems(list_Out);
	ui->m_cmb_B07->addItems(list_Out);
	ui->m_cmb_B08->addItems(list_Out);
	ui->m_cmb_SwitchMode->addItems(QStringList()<<g_sLangTxt_CBOperate_StartTime/*("时间启动")*/<<g_sLangTxt_CBOperate_BinStart/*("开入量启动")*/);

	ui->m_tabIn_Out->setCurrentIndex(0);

#ifndef _PSX_QT_LINUX_
//20240807 luozibing 根据缩放比例设置lab显示宽度
	int nleng = ui->m_lab_SwitchMode->text().length();
    float horizontalDPI = GetDeviceCaps_LOGPIXELSX();
    float verticalDPI = GetDeviceCaps_LOGPIXELSY();
	int dpi = (horizontalDPI + verticalDPI) / 2;
	double dZoomRatio = dpi / 96.0;
	ui->m_lab_SwitchMode->setMinimumWidth(nleng * 12 * dZoomRatio);	
#endif
}
void QDistanceBinarysDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->m_radio_or, g_sLangID_Native_LogicOr, XLang_Ctrls_QRadioButton);//逻辑或
	xlang_SetLangStrToWidget(ui->m_radio_and, g_sLangID_Native_LogicAnd, XLang_Ctrls_QRadioButton);//逻辑与
	xlang_SetLangStrToWidget(ui->m_lab_SwitchMode, g_sLangID_CBOperate_OutputSwitchMode, XLang_Ctrls_QLabel);//开出翻转启动方式
	xlang_SetLangStrToWidget(ui->m_labDelayTime, g_sLangID_Distance_OutputHoldTimeS, XLang_Ctrls_QLabel);//开出保持时间(s)
	xlang_SetLangStrToWidget(ui->m_labKeepTime, g_sLangID_Distance_OutputDelayTime, XLang_Ctrls_QLabel);//开出翻转时刻(s)

	xlang_SetLangStrToWidget(ui->m_tabInput, g_sLangID_Native_Bin, XLang_Ctrls_QTabWidget);//开入量
	xlang_SetLangStrToWidget(ui->m_tabOutput, g_sLangID_Native_Bout, XLang_Ctrls_QTabWidget);//开出量
	xlang_SetLangStrToWidget(ui->m_btnOK, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnCancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;//开入、开出量设置
	xlang_GetLangStrByFile(strTile, g_sLangID_Native_SwitchVal);
	setWindowTitle(strTile);
}
void QDistanceBinarysDlg::SetPageFont(CFont oPageFont)
{//20240807 luozibing 测试字体使用
	//QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	setFont(oPageFont);
	int nsize = oPageFont.pixelSize();
	CString strFont;
	strFont.Format("font-size:%dpx;", nsize);
	ui->m_radio_and->setStyleSheet(strFont);
	ui->m_radio_or->setStyleSheet(strFont);
	int dlength = ui->m_lab_SwitchMode->text().length();
}
void QDistanceBinarysDlg::SetDisplayedByDefault(BOOL bDefault)
{//初次进入开入量界面 默认开入量全选
    m_bDefault = bDefault;
}
void QDistanceBinarysDlg::SetBinBoutName()
{//开入开出映射修改 20240925 luozibing
	//开入量
	QString strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 0);
	ui->m_checkA->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 1);
	ui->m_checkB->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 2);
	ui->m_checkC->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 3);
	ui->m_checkD->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 4);
	ui->m_checkE->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 5);
	ui->m_checkF->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 6);
	ui->m_checkG->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 7);
	ui->m_checkH->setText(strName);
	//开出量
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 0);
	ui->m_lab_B01->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
	ui->m_lab_B02->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
	ui->m_lab_B03->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
	ui->m_lab_B04->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 4);
	ui->m_lab_B05->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 5);
	ui->m_lab_B06->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 6);
	ui->m_lab_B07->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 7);
	ui->m_lab_B08->setText(strName);
}
void QDistanceBinarysDlg::SetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 读取数据转换到界面中
	if(pParas == NULL)
		return;

	m_pParas = pParas;
	CheckAllPresence(m_pParas);
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
	SetBinBoutName();
}
void QDistanceBinarysDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT)
	{
		ui->m_radio_and->setChecked(pData->m_strValue == "1");
		ui->m_radio_or->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_A)
    {//20240731 luozbing 未修改时,默认开入量全勾选
        if(m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkA->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_B)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkB->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_C)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkC->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_D)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkD->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_E)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkE->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_F)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkF->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_G)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkG->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_H)
	{
		if (m_bDefault)
        {
			pData->m_strValue.setNum(1);
        }
		ui->m_checkH->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01)
	{
		ui->m_cmb_B01->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02)
	{
		ui->m_cmb_B02->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03)
	{
		ui->m_cmb_B03->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04)
	{
		ui->m_cmb_B04->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05)
	{
		ui->m_cmb_B05->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06)
	{
		ui->m_cmb_B06->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07)
	{
		ui->m_cmb_B07->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08)
	{
		ui->m_cmb_B08->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE)
	{
		ui->m_cmb_SwitchMode->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME)
	{
		ui->m_txtKeepTime->setText(CheckDataMinMax(pData->m_strValue,100000,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME)
	{
		ui->m_txtDelayTime->setText(CheckDataMinMax(pData->m_strValue,100000,0,3));
	}
}
void QDistanceBinarysDlg::GetDatas(CExBaseList *pParas)
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
void QDistanceBinarysDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	bool bState;
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT)
	{
		bState = ui->m_radio_and->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_A)
	{
		bState = ui->m_checkA->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_B)
	{
		bState = ui->m_checkB->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_C)
	{
		bState = ui->m_checkC->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_D)
	{
		bState = ui->m_checkD->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_E)
	{
		bState = ui->m_checkE->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_F)
	{
		bState = ui->m_checkF->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_G)
	{
		bState = ui->m_checkG->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_H)
	{
		bState = ui->m_checkH->isChecked();
		pData->m_strValue.Format("%d",bState);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B01->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B02->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B03->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B04->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B05->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B06->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B07->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B08->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_SwitchMode->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME)
	{
		pData->m_strValue = ui->m_txtKeepTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME)
	{
		pData->m_strValue = ui->m_txtDelayTime->text();
	}
	
}
void QDistanceBinarysDlg::on_m_cmb_SwitchMode_currentIndexChanged(int index)
{
	if (index == 0)
	{
		ui->m_txtKeepTime->setEnabled(true);
	} 
	else
	{
		ui->m_txtKeepTime->setEnabled(false);
	}
}
void QDistanceBinarysDlg::on_m_txtDelayTime_editingFinished()
{
	ui->m_txtDelayTime->setText(CheckDataMinMax(ui->m_txtDelayTime->text(),100000,0,3));
}

void QDistanceBinarysDlg::on_m_txtKeepTime_editingFinished()
{
	ui->m_txtKeepTime->setText(CheckDataMinMax(ui->m_txtKeepTime->text(),100000,0,3));
}
void QDistanceBinarysDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QDistanceBinarysDlg::on_m_btnCancel_clicked()
{
	this->close();
}
void QDistanceBinarysDlg::CheckAllPresence(CExBaseList *pParas)
{
	if (pParas == NULL)
	{
		return;
	}
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_A);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_B);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_C);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_D);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_E);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_F);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_G);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_H);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME);
}
void QDistanceBinarysDlg::UpdataAllBinarys(CExBaseList *pAllParas)
{
	//20240626 luozibing 通用参数修改后，修改表格中所有项数据开入开出量设置
	CSttMacroTest *pSttMacroTest = NULL;
	CExBaseList *pItem = NULL;
	CSttMacroTestParaDatas *pParaDatas = NULL;
	POS pos = pAllParas->GetHeadPosition();

	while (pos!= NULL)
	{
		pItem = (CExBaseList*)pAllParas->GetNext(pos);

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
BOOL QDistanceBinarysDlg::CheckItemsModify(CExBaseList *pItem)
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
		if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME||pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME)
		{
			//浮点数判断差值的绝对值
			if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.001)
			{
				m_nModify = 1;
				return TRUE;
			}

		}
		else
		{
			if (pData->m_strValue != pData_New->m_strValue)
			{
				m_nModify = 1;
				return TRUE;
			}
		}
	}
	return FALSE;
}
