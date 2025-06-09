#include "DistanceSearchBinarySignalDlg.h"
#include "ui_DistanceSearchBinarySignalDlg.h"
#include "DistanceSearchCommon.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"

extern CFont *g_pSttGlobalFont;

QDistanceSearchBinarySignalDlg::QDistanceSearchBinarySignalDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceSearchBinarySignalDlg)
{
    ui->setupUi(this);
    m_nInputWidgetWidth = 150;
    InitUI();
    m_nModify = 0;
}

QDistanceSearchBinarySignalDlg::~QDistanceSearchBinarySignalDlg()
{
    delete ui;
}

void QDistanceSearchBinarySignalDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/DistanceSearchTest.png");
#else
	strPngPath =  ":/ctrls/images/DistanceSearchTest.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Native_SwitchVal);

	ui->m_tabWidget->setCurrentIndex(0);
	ui->m_tabWidget->setFont(*g_pSttGlobalFont);
	ui->m_btnOk->setFont(*g_pSttGlobalFont);
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);

    ui->m_cbbB01->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB02->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB03->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB04->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB05->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB06->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB07->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbB08->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbOutputSwitchMode->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editOutputDelayTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editOutputKeepTime->setFixedWidth(m_nInputWidgetWidth);

    ui->m_tabWidget->setTabText(0, g_sLangTxt_Native_Bin);
    ui->m_tabWidget->setTabText(1, g_sLangTxt_Native_Bout);
    ui->m_rbAnd->setText(g_sLangTxt_Native_LogicAnd);
    ui->m_rbOr->setText(g_sLangTxt_Native_LogicOr);
    ui->m_labOutputSwitchMode->setText(g_sLangTxt_CBOperate_OutputSwitchMode);
    ui->m_labOutputKeepTime->setText(g_sLangTxt_Native_OutputHoldTimeS);
    ui->m_labOutputDelayTime->setText(g_sLangTxt_CBOperate_OutputDelayTime);
    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    ui->m_cbbB01->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB01->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB02->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB02->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB03->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB03->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB04->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB04->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB05->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB05->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB06->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB06->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB07->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB07->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbB08->addItem(g_sLangTxt_SOE_Break);
    ui->m_cbbB08->addItem(g_sLangTxt_SOE_Shutting);
    ui->m_cbbOutputSwitchMode->addItem(g_sLangTxt_CBOperate_StartTime);
    ui->m_cbbOutputSwitchMode->addItem(g_sLangTxt_CBOperate_BinStart);

    SetBinBoutName();

	return;
}

void QDistanceSearchBinarySignalDlg::SetBinBoutName()
{
    //开入开出映射修改
    //开入量
    QString strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 0);
    ui->m_cbBinSelectA->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 1);
    ui->m_cbBinSelectB->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 2);
    ui->m_cbBinSelectC->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 3);
    ui->m_cbBinSelectD->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 4);
    ui->m_cbBinSelectE->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 5);
    ui->m_cbBinSelectF->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 6);
    ui->m_cbBinSelectG->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 7);
    ui->m_cbBinSelectH->setText(strName);

    //开出量
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 0);
    ui->m_labBout1->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
    ui->m_labBout2->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
    ui->m_labBout3->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
    ui->m_labBout4->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 4);
    ui->m_labBout5->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 5);
    ui->m_labBout6->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 6);
    ui->m_labBout7->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 7);
    ui->m_labBout8->setText(strName);
}

void QDistanceSearchBinarySignalDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	Qt::CheckState state;
	if(0 == pData->m_strValue.toInt())
		state = Qt::Unchecked;
	else
		state = Qt::Checked;

	if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_A)
	{
		ui->m_cbBinSelectA->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B)
	{
		ui->m_cbBinSelectB->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_C)
	{
		ui->m_cbBinSelectC->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_D)
	{
		ui->m_cbBinSelectD->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_E)
	{
		ui->m_cbBinSelectE->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_F)
	{
		ui->m_cbBinSelectF->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_G)
	{
		ui->m_cbBinSelectG->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_H)
	{
		ui->m_cbBinSelectH->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANDOR)
	{
		ui->m_rbAnd->setChecked(pData->m_strValue.toInt());
		ui->m_rbOr->setChecked(!pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B01)
	{
		ui->m_cbbB01->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B02)
	{
		ui->m_cbbB02->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B03)
	{
		ui->m_cbbB03->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B04)
	{
		ui->m_cbbB04->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B05)
	{
		ui->m_cbbB05->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B06)
	{
		ui->m_cbbB06->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B07)
	{
		ui->m_cbbB07->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B08)
	{
		ui->m_cbbB08->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTSWITCHMODE)
	{
		ui->m_cbbOutputSwitchMode->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTKEEPTIME)
	{
        ui->m_editOutputKeepTime->setText(DistanceSearchValueCheck(pData->m_strValue, OUTPUTKEEPTIME_MAX, OUTPUTKEEPTIME_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTDELAYTIME)
	{
        ui->m_editOutputDelayTime->setText(DistanceSearchValueCheck(pData->m_strValue, OUTPUTDELAYTIME_MAX, OUTPUTDELAYTIME_MIN, 3));
	}

	return;
}

void QDistanceSearchBinarySignalDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_A)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectA->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectB->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_C)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectC->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_D)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectD->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_E)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectE->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_F)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectF->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_G)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectG->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_H)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectH->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANDOR)
	{
		CString strTmp;
		strTmp.setNum(ui->m_rbAnd->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B01)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB01->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B02)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB02->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B03)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB03->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B04)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB04->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B05)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB05->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B06)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB06->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B07)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB07->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B08)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbB08->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTSWITCHMODE)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbbOutputSwitchMode->currentIndex());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTKEEPTIME)
	{
		pData->m_strValue = ui->m_editOutputKeepTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTDELAYTIME)
	{
		pData->m_strValue = ui->m_editOutputDelayTime->text();
	}

	return;
}

void QDistanceSearchBinarySignalDlg::CheckAllPresence(CExBaseList *pParas)
{
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_A);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_C);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_D);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_E);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_F);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_G);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_H);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANDOR);

	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B01);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B02);	
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B03);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B04);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B05);	
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B06);	
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B07);	
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B08);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTSWITCHMODE);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTKEEPTIME);
	DistanceSearchCheckParaExist(pParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTDELAYTIME);

	return;
}

void QDistanceSearchBinarySignalDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QDistanceSearchBinarySignalDlg::SetDatas(CExBaseList *pParas)
{
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

	return;
}

void QDistanceSearchBinarySignalDlg::UpdateCurrentBinarys(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;
	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);

	return;
}

void QDistanceSearchBinarySignalDlg::UpdateAllBinarys(CExBaseList *pAllItems)
{
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

	return;
}

void QDistanceSearchBinarySignalDlg::on_m_editOutputKeepTime_editingFinished()
{
    ui->m_editOutputKeepTime->setText(DistanceSearchValueCheck(ui->m_editOutputKeepTime->text(), OUTPUTKEEPTIME_MAX, OUTPUTKEEPTIME_MIN,3));
	return;
}

void QDistanceSearchBinarySignalDlg::on_m_editOutputDelayTime_editingFinished()
{
    ui->m_editOutputDelayTime->setText(DistanceSearchValueCheck(ui->m_editOutputDelayTime->text(), OUTPUTDELAYTIME_MAX, OUTPUTDELAYTIME_MIN,3));
	return;
}

BOOL QDistanceSearchBinarySignalDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTKEEPTIME
                ||pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTDELAYTIME)
        {
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

//确认按钮
void QDistanceSearchBinarySignalDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}


//取消按钮
void QDistanceSearchBinarySignalDlg::on_m_btnCancel_clicked()
{
	this->close();
}
