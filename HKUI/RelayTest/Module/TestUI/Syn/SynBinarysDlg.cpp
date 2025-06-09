#include "SynBinarysDlg.h"
#include "ui_SynBinarysDlg.h"
#include "../../XLangResource_Native.h"
#include "../../UI/SttTestCntrFrameBase.h"
extern CFont *g_pSttGlobalFont;

QSynBinarysDlg::QSynBinarysDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSynBinarysDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
	InitUI();
	InitLanuage();
}

QSynBinarysDlg::~QSynBinarysDlg()
{
    delete ui;
}

void QSynBinarysDlg::InitUI()
{
    ui->m_cmbKStart->addItems(QStringList()<<g_sLangTxt_without/*"无"*/<<g_sLangTxt_Syn_Pulse/*"脉冲"*/<<g_sLangTxt_Syn_Continuous/*"连续"*/);
	QStringList list_Out;
    list_Out.append(/*"断开"*/g_sLangTxt_SOE_Break);
    list_Out.append(/*"闭合"*/g_sLangTxt_SOE_Shutting);
	ui->m_cmbBout1->addItems(list_Out);
	ui->m_cmbBout2->addItems(list_Out);
	ui->m_cmbBout3->addItems(list_Out);

	ui->m_cmbBinSyn->addItems(QStringList()<<"A"<<"B"<<"C"<<"D");
	ui->m_cmbBinIncV->addItem("E");
	ui->m_cmbBinDecV->addItem("G");
	ui->m_cmbBinIncF->addItem("F");
	ui->m_cmbBinDecF->addItem("H");

	ui->m_cmbBinIncV->setDisabled(true);
	ui->m_cmbBinDecV->setDisabled(true);
	ui->m_cmbBinIncF->setDisabled(true);
	ui->m_cmbBinDecF->setDisabled(true);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
}

void QSynBinarysDlg::InitLanuage()
{
	CString strtemp;
	xlang_SetLangStrToWidget(ui->groupBox, g_sLangID_Native_Bout, XLang_Ctrls_QGroupBox);//开出量
	xlang_SetLangStrToWidget(ui->groupBox_2, g_sLangID_Native_Bin, XLang_Ctrls_QGroupBox);//开入量

	xlang_SetLangStrToWidget(ui->m_labKStart, g_sLangID_Out4_Mode, XLang_Ctrls_QLabel);//开出4输出方式
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_breaker4HoldTime);//开出4保持时间(s)
	strtemp += "(s)";
	ui->m_labCloseTime->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_labBout1, g_sLangID_Out1_Situation, XLang_Ctrls_QLabel);//开出1状态
	xlang_SetLangStrToWidget(ui->m_labBout2, g_sLangID_Out2_Situation, XLang_Ctrls_QLabel);//开出2状态
	xlang_SetLangStrToWidget(ui->m_labBout3, g_sLangID_Out3_Situation, XLang_Ctrls_QLabel);//开出3状态
	
	xlang_SetLangStrToWidget(ui->m_labBinSyn, g_sLangID_Syn_ProOutSignals, XLang_Ctrls_QLabel);//保护出口信号
	xlang_SetLangStrToWidget(ui->m_labBinIncV, g_sLangID_Native_boostSignal, XLang_Ctrls_QLabel);//增压信号
	xlang_SetLangStrToWidget(ui->m_labBinDecV, g_sLangID_Native_reducePresSignal, XLang_Ctrls_QLabel);//减压信号
	xlang_SetLangStrToWidget(ui->m_labBinIncF, g_sLangID_Syn_IncFSignals, XLang_Ctrls_QLabel);//增速信号
	xlang_SetLangStrToWidget(ui->m_labBinDecF, g_sLangID_Syn_DecFSignals, XLang_Ctrls_QLabel);//减速信号

	xlang_SetLangStrToWidget(ui->m_btnOK, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnCancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;//开入、开出量设置
	xlang_GetLangStrByFile(strTile, g_sLangID_Native_SwitchVal);
	setWindowTitle(strTile);
}

void QSynBinarysDlg::SetDatas(CExBaseList *pParas)
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

void QSynBinarysDlg::SetValueToPage(CSttMacroTestParaData *pData)
{

	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_KStart)
	{
		ui->m_cmbKStart->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime)
	{
		ui->m_lineCloseTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout1)
	{
		ui->m_cmbBout1->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout2)
	{
		ui->m_cmbBout2->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout3)
	{
		ui->m_cmbBout3->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinSyn)
	{
		ui->m_cmbBinSyn->setCurrentIndex(pData->m_strValue.toInt());
		nBinSyn = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinIncV)
	{
		//ui->m_cmbBinIncV->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinDecV)
	{
		//ui->m_cmbBinDecV->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinIncF)
	{
		//ui->m_cmbBinIncF->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinDecF)
	{
		//ui->m_cmbBinDecF->setCurrentIndex(pData->m_strValue.toInt());
	}

}

void QSynBinarysDlg::GetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 将界面设置参数填到链表
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QSynBinarysDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_KStart)
	{
		pData->m_strValue.Format("%d",ui->m_cmbKStart->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime)
	{
		pData->m_strValue = ui->m_lineCloseTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout1)
	{
		pData->m_strValue.Format("%d",ui->m_cmbBout1->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout2)
	{
		pData->m_strValue.Format("%d",ui->m_cmbBout2->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout3)
	{
		pData->m_strValue.Format("%d",ui->m_cmbBout3->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinSyn)
	{
		pData->m_strValue.Format("%d",ui->m_cmbBinSyn->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinIncV)
	{
		//pData->m_strValue.Format("%d",ui->m_cmbBinIncV->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinDecV)
	{
		//pData->m_strValue.Format("%d",ui->m_cmbBinDecV->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinIncF)
	{
		//pData->m_strValue.Format("%d",ui->m_cmbBinIncF->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinDecF)
	{
		//pData->m_strValue.Format("%d",ui->m_cmbBinDecF->currentIndex());
	}	
}

void QSynBinarysDlg::on_m_cmbKStart_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_lineCloseTime_editingFinished()
{
	ui->m_lineCloseTime->setText(CheckDataMinMax(ui->m_lineCloseTime->text(),999.999,0,3));
}

void QSynBinarysDlg::on_m_cmbBout1_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBout2_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBout3_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBinSyn_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBinIncV_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBinDecV_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBinIncF_currentIndexChanged(int index)
{

}

void QSynBinarysDlg::on_m_cmbBinDecF_currentIndexChanged(int index)
{

}

//开入开出映射修改 20240930 gongyiping
void QSynBinarysDlg::SetBinBoutName()
{
	ui->m_cmbBinSyn->clear();
	ui->m_cmbBinIncV->clear();
	ui->m_cmbBinDecV->clear();
	ui->m_cmbBinIncF->clear();
	ui->m_cmbBinDecF->clear();

	//开入量
	QString strNameA = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 0);//A
	QString strNameB = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 1);//B
	QString strNameC = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 2);//C
	QString strNameD = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 3);//D
	ui->m_cmbBinSyn->addItems(QStringList() << strNameA << strNameB << strNameC << strNameD);
	ui->m_cmbBinSyn->setCurrentIndex(nBinSyn);
	QString strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 4);//E
	ui->m_cmbBinIncV->addItems(QStringList() << strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 5);//F
	ui->m_cmbBinIncF->addItems(QStringList() << strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 6);//G
	ui->m_cmbBinDecV->addItems(QStringList() << strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 7);//H
	ui->m_cmbBinDecF->addItems(QStringList() << strName);

	//开出量
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 0);
	ui->m_labBout1->setText(strName + g_sLangTxt_Syn_State);//开出1状态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
	ui->m_labBout2->setText(strName + g_sLangTxt_Syn_State);//开出2状态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
	ui->m_labBout3->setText(strName + g_sLangTxt_Syn_State);//开出3状态
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
	ui->m_labKStart->setText(strName + g_sLangTxt_Syn_Mode);//开出4输出方式
	ui->m_labCloseTime->setText(strName + g_sLangTxt_Native_KeepTime);//开出4保持时间

}

void QSynBinarysDlg::on_m_btnOK_clicked()
{
    this->done(Accepted);
}

void QSynBinarysDlg::on_m_btnCancel_clicked()
{
    this->close();
}

void QSynBinarysDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_KStart);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Bout1);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Bout2);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Bout3);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_BinSyn);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_BinIncV);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_BinDecV);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_BinIncF);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_BinDecF);
}

void QSynBinarysDlg::UpdataAllBinarys(CExBaseList *pAllItems)
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
			pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE, "");

			if (pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
}

BOOL QSynBinarysDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime)
        {//浮点数判断差值的绝对值
            if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
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
