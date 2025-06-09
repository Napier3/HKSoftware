#include "ActionTimeBinarySignalDlg.h"
#include "ui_ActionTimeBinarySignalDlg.h"
#include "ActionTimeCommon.h"
#include "SttMultiMacroActionTimeParasDefine.h"
#include "../../UI/SttTestCntrFrameBase.h"

extern CFont *g_pSttGlobalFont;

QActionTimeBinarySignalDlg::QActionTimeBinarySignalDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QActionTimeBinarySignalDlg)
{
    ui->setupUi(this);
    InitUI();
    m_nModify= 0;

}

QActionTimeBinarySignalDlg::~QActionTimeBinarySignalDlg()
{
    delete ui;
}

void QActionTimeBinarySignalDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/ActionTimeTest.png");
#else
	strPngPath =  ":/ctrls/images/ActionTimeTest.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));

	ui->m_tabWidget->setCurrentIndex(0);
	ui->m_tabWidget->setFont(*g_pSttGlobalFont);
	ui->m_btnOk->setFont(*g_pSttGlobalFont);
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);

    this->setWindowTitle(g_sLangTxt_Native_SwitchVal);
    ui->m_tabWidget->setTabText(0, g_sLangTxt_Native_Bin);
    ui->m_tabWidget->setTabText(1, g_sLangTxt_Native_Bout);
    ui->m_rbAnd->setText(g_sLangTxt_Native_LogicAnd);
    ui->m_rbOr->setText(g_sLangTxt_Native_LogicOr);
    ui->m_gbNormal->setTitle(g_sLangTxt_Gradient_Norm);
    ui->m_gbFault->setTitle(g_sLangTxt_Gradient_Failure);
    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);
    SetBinBoutName();

	return;
}

void QActionTimeBinarySignalDlg::SetBinBoutName()
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
    ui->m_cbBout01->setText(strName);
    ui->m_cbBout1->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
    ui->m_cbBout02->setText(strName);
    ui->m_cbBout2->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
    ui->m_cbBout03->setText(strName);
    ui->m_cbBout3->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
    ui->m_cbBout04->setText(strName);
    ui->m_cbBout4->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 4);
    ui->m_cbBout05->setText(strName);
    ui->m_cbBout5->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 5);
    ui->m_cbBout06->setText(strName);
    ui->m_cbBout6->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 6);
    ui->m_cbBout07->setText(strName);
    ui->m_cbBout7->setText(strName);
    strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 7);
    ui->m_cbBout08->setText(strName);
    ui->m_cbBout8->setText(strName);
}

void QActionTimeBinarySignalDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_A)
	{
		ui->m_cbBinSelectA->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B)
	{
		ui->m_cbBinSelectB->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_C)
	{
		ui->m_cbBinSelectC->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_D)
	{
		ui->m_cbBinSelectD->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_E)
	{
		ui->m_cbBinSelectE->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_F)
	{
		ui->m_cbBinSelectF->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_G)
	{
		ui->m_cbBinSelectG->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_H)
	{
		ui->m_cbBinSelectH->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B01)
	{
		ui->m_cbBout01->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B02)
	{
		ui->m_cbBout02->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B03)
	{
		ui->m_cbBout03->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B04)
	{
		ui->m_cbBout04->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B05)
	{
		ui->m_cbBout05->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B06)
	{
		ui->m_cbBout06->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B07)
	{
		ui->m_cbBout07->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B08)
	{
		ui->m_cbBout08->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B1)
	{
		ui->m_cbBout1->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B2)
	{
		ui->m_cbBout2->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B3)
	{
		ui->m_cbBout3->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B4)
	{
		ui->m_cbBout4->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B5)
	{
		ui->m_cbBout5->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B6)
	{
		ui->m_cbBout6->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B7)
	{
		ui->m_cbBout7->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B8)
	{
		ui->m_cbBout8->setChecked(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_ANDOR)
	{
		ui->m_rbAnd->setChecked(pData->m_strValue.toInt());
		ui->m_rbOr->setChecked(!pData->m_strValue.toInt());
	}

	return;
}

void QActionTimeBinarySignalDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_A)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectA->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectB->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_C)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectC->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_D)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectD->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_E)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectE->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_F)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectF->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_G)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectG->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_H)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBinSelectH->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B01)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout01->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B02)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout02->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B03)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout03->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B04)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout04->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B05)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout05->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B06)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout06->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B07)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout07->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B08)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout08->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B1)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout1->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B2)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout2->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B3)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout3->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B4)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout4->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B5)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout5->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B6)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout6->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B7)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout7->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B8)
	{
		CString strTmp;
		strTmp.setNum(ui->m_cbBout8->isChecked());
		pData->m_strValue = strTmp;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_ANDOR)
	{
		CString strTmp;
		strTmp.setNum(ui->m_rbAnd->isChecked());
		pData->m_strValue = strTmp;
	}

	return;
}

void QActionTimeBinarySignalDlg::CheckAllPresence(CExBaseList *pParas)
{
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_A);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_C);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_D);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_E);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_F);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_G);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_H);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_ANDOR);

	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B01);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B02);	
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B03);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B04);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B05);	
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B06);	
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B07);	
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B08);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B1);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B2);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B3);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B4);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B5);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B6);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B7);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B8);

	return;
}

void QActionTimeBinarySignalDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QActionTimeBinarySignalDlg::SetDatas(CExBaseList *pParas)
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

void QActionTimeBinarySignalDlg::UpdateCurrentBinarys(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;
	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);
}

void QActionTimeBinarySignalDlg::UpdateAllBinarys(CExBaseList *pAllItems)
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

BOOL QActionTimeBinarySignalDlg::CheckItemsModify(CExBaseList *pItem)
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

//确认按钮
void QActionTimeBinarySignalDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}


//取消按钮
void QActionTimeBinarySignalDlg::on_m_btnCancel_clicked()
{
	this->close();
}
