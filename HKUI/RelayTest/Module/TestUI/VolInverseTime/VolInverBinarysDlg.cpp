#include "VolInverBinarysDlg.h"
#include "ui_VolInverBinarysDlg.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "../../UI/SttTestCntrFrameBase.h"
extern CFont *g_pSttGlobalFont;

QVolInverBinarysDlg::QVolInverBinarysDlg(/*CDataGroup *pPara,*/QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QVolInverBinarysDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
	m_nModify= 0;
	InitUI();
	InitLanuage();
	//m_pVolDataGroup = pPara;
	
	//SetDatas(m_pVolDataGroup);
}

QVolInverBinarysDlg::~QVolInverBinarysDlg()
{
    delete ui;
}

void QVolInverBinarysDlg::InitUI()
{
 /*   ui->tabWidget->setTabText(0, g_sLangTxt_InputValue);
    ui->tabWidget->setTabText(1, g_sLangTxt_OutputValue);*/
	ui->m_tabWidget->setCurrentIndex(0);
	ui->m_tabWidget->setFont(*g_pSttGlobalFont);
	ui->pushButton->setFont(*g_pSttGlobalFont);
	ui->pushButton_2->setFont(*g_pSttGlobalFont);

	return;
}

void QVolInverBinarysDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->radioButton_1, g_sLangID_Native_LogicOr, XLang_Ctrls_QRadioButton);//逻辑或
	xlang_SetLangStrToWidget(ui->radioButton_2, g_sLangID_Native_LogicAnd, XLang_Ctrls_QRadioButton);//逻辑与

	xlang_SetLangStrToWidget(ui->tab, g_sLangID_Native_Bin, XLang_Ctrls_QTabWidget);//开入量
	xlang_SetLangStrToWidget(ui->tab_2, g_sLangID_Native_Bout, XLang_Ctrls_QTabWidget);//开出量

	xlang_SetLangStrToWidget(ui->groupBox, g_sLangID_Gradient_Norm, XLang_Ctrls_QGroupBox);//常态
	xlang_SetLangStrToWidget(ui->groupBox_2, g_sLangID_Gradient_Failure, XLang_Ctrls_QGroupBox);//故障态

	xlang_SetLangStrToWidget(ui->pushButton, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->pushButton_2, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;//开入、开出量设置
	xlang_GetLangStrByFile(strTile, g_sLangID_Native_SwitchVal);
	setWindowTitle(strTile);
}

void QVolInverBinarysDlg::SetDatas(/*CDataGroup *pParas*/CExBaseList *pParas)
{

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
void QVolInverBinarysDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_AndOr);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_A);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_B);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_C);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_D);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_E);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_F);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_G);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_H);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B01);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B02);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B03);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B04);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B05);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B06);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B07);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B08);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B1);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B2);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B3);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B4);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B5);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B6);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B7);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID__B8);

}

void QVolInverBinarysDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_AndOr)
	{
		ui->radioButton_1->setChecked(pData->m_strValue == "1");
		ui->radioButton_2->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_A)
	{
		ui->checkBox_4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_B)
	{
		ui->checkBox_3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_C)
	{
		ui->checkBox_2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_D)
	{
		ui->checkBox_1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_E)
	{
		ui->checkBox_5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_F)
	{
		ui->checkBox_6->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_G)
	{
		ui->checkBox_7->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_H)
	{
		ui->checkBox_8->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B01)
	{
		ui->checkBox_9->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B02)
	{
		ui->checkBox_10->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B03)
	{
		ui->checkBox_11->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B04)
	{
		ui->checkBox_12->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B05)
	{
		ui->checkBox_13->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B06)
	{
		ui->checkBox_14->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B07)
	{
		ui->checkBox_15->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B08)
	{
		ui->checkBox_16->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B1)
	{
		ui->checkBox_17->setChecked(pData->m_strValue == "1");
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B2)
	{
		ui->checkBox_18->setChecked(pData->m_strValue == "1");
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B3)
	{
		ui->checkBox_19->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B4)
	{
		ui->checkBox_20->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B5)
	{
		ui->checkBox_21->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B6)
	{
		ui->checkBox_22->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B7)
	{
		ui->checkBox_23->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B8)
	{
		ui->checkBox_24->setChecked(pData->m_strValue == "1");
	}
}

BOOL QVolInverBinarysDlg::CheckItemsModify(CExBaseList *pItem)
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

		if (pData->m_strValue != pData_New->m_strValue)
		{
			m_nModify = 1;
			return TRUE;
		}
	}
	return FALSE;
}
void QVolInverBinarysDlg::UpdataAllBinarys(CExBaseList *pAllParas)
{
	//通用参数修改后，修改表格中所有项数据开入开出量设置
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

void QVolInverBinarysDlg::GetDatas(/*CDataGroup *pParas*/CExBaseList *pParas)
{
	//pParas->SetDataValue("_BinSelectA", (long)ui->checkBox_4->isChecked(), true);
	//pParas->SetDataValue("_BinSelectB", (long)ui->checkBox_3->isChecked(), true);
	//pParas->SetDataValue("_BinSelectC", (long)ui->checkBox_2->isChecked(), true);
	//pParas->SetDataValue("_BinSelectD", (long)ui->checkBox_1->isChecked(), true);
	//pParas->SetDataValue("_BinSelectE", (long)ui->checkBox_5->isChecked(), true);
	//pParas->SetDataValue("_BinSelectF", (long)ui->checkBox_6->isChecked(), true);
	//pParas->SetDataValue("_BinSelectG", (long)ui->checkBox_7->isChecked(), true);
	//pParas->SetDataValue("_BinSelectH", (long)ui->checkBox_8->isChecked(), true);
	//pParas->SetDataValue("_AndOr", (long)ui->radioButton_1->isChecked(), true);

	//pParas->SetDataValue("_Bout01", (long)ui->checkBox_9->isChecked(), true);
	//pParas->SetDataValue("_Bout02", (long)ui->checkBox_10->isChecked(), true);
	//pParas->SetDataValue("_Bout03", (long)ui->checkBox_11->isChecked(), true);
	//pParas->SetDataValue("_Bout04", (long)ui->checkBox_12->isChecked(), true);
	//pParas->SetDataValue("_Bout05", (long)ui->checkBox_13->isChecked(), true);
	//pParas->SetDataValue("_Bout06", (long)ui->checkBox_14->isChecked(), true);
	//pParas->SetDataValue("_Bout07", (long)ui->checkBox_15->isChecked(), true);
	//pParas->SetDataValue("_Bout08", (long)ui->checkBox_16->isChecked(), true);

	//pParas->SetDataValue("_Bout1", (long)ui->checkBox_17->isChecked(), true);
	//pParas->SetDataValue("_Bout2", (long)ui->checkBox_18->isChecked(), true);
	//pParas->SetDataValue("_Bout3", (long)ui->checkBox_19->isChecked(), true);
	//pParas->SetDataValue("_Bout4", (long)ui->checkBox_20->isChecked(), true);
	//pParas->SetDataValue("_Bout5", (long)ui->checkBox_21->isChecked(), true);
	//pParas->SetDataValue("_Bout6", (long)ui->checkBox_22->isChecked(), true);
	//pParas->SetDataValue("_Bout7", (long)ui->checkBox_23->isChecked(), true);
	//pParas->SetDataValue("_Bout8", (long)ui->checkBox_24->isChecked(), true);

	//return;
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QVolInverBinarysDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	bool bvalue;
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_AndOr)
	{
		bvalue = ui->radioButton_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_A)
	{
		bvalue = ui->checkBox_4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_B)
	{
		bvalue = ui->checkBox_3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_C)
	{
		bvalue = ui->checkBox_2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_D)
	{
		bvalue = ui->checkBox_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_E)
	{
		bvalue = ui->checkBox_5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_F)
	{
		bvalue = ui->checkBox_6->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_G)
	{
		bvalue = ui->checkBox_7->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_H)
	{
		bvalue = ui->checkBox_8->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B01)
	{
		bvalue = ui->checkBox_9->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B02)
	{
		bvalue = ui->checkBox_10->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B03)
	{
		bvalue = ui->checkBox_11->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B04)
	{
		bvalue = ui->checkBox_12->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B05)
	{
		bvalue = ui->checkBox_13->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B06)
	{
		bvalue = ui->checkBox_14->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B07)
	{
		bvalue = ui->checkBox_15->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B08)
	{
		bvalue = ui->checkBox_16->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B1)
	{
		bvalue = ui->checkBox_17->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B2)
	{
		bvalue = ui->checkBox_18->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B3)
	{
		bvalue = ui->checkBox_19->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B4)
	{
		bvalue = ui->checkBox_20->isChecked();
		pData->m_strValue.setNum(bvalue);
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B5)
	{
		bvalue = ui->checkBox_21->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B6)
	{
		bvalue = ui->checkBox_22->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B7)
	{
		bvalue = ui->checkBox_23->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B8)
	{
		bvalue = ui->checkBox_24->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
}

//开入开出映射修改 20240930 gongyiping
void QVolInverBinarysDlg::SetBinBoutName()
{
	//开入量
	QString strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 0);//A
	ui->checkBox_4->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 1);//B
	ui->checkBox_3->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 2);//C
	ui->checkBox_2->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 3);//D
	ui->checkBox_1->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 4);//E
	ui->checkBox_5->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 5);//F
	ui->checkBox_6->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 6);//G
	ui->checkBox_7->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 7);//H
	ui->checkBox_8->setText(strName);
	//开出量
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 0);
	ui->checkBox_9->setText(strName);//常态
	ui->checkBox_17->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
	ui->checkBox_10->setText(strName);//常态
	ui->checkBox_18->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
	ui->checkBox_11->setText(strName);//常态
	ui->checkBox_19->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
	ui->checkBox_12->setText(strName);//常态
	ui->checkBox_20->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 4);
	ui->checkBox_13->setText(strName);//常态
	ui->checkBox_21->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 5);
	ui->checkBox_14->setText(strName);//常态
	ui->checkBox_22->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 6);
	ui->checkBox_15->setText(strName);//常态
	ui->checkBox_23->setText(strName);//故障态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 7);
	ui->checkBox_16->setText(strName);//常态
	ui->checkBox_24->setText(strName);//故障态
}
//确认按钮
void QVolInverBinarysDlg::on_pushButton_clicked()
{
	//GetDatas(m_pVolDataGroup);
	accept();
}


//取消按钮
void QVolInverBinarysDlg::on_pushButton_2_clicked()
{
	reject();
}
