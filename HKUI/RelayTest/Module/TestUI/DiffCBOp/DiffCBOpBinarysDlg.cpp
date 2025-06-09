#include "DiffCBOpBinarysDlg.h"
#include "ui_DiffCBOpBinarysDlg.h"
#include "DiffCBOpCommonParasDlg.h"
#include "../../XLangResource_Native.h"
extern CFont *g_pSttGlobalFont;

QDiffCBOpBinarysDlg::QDiffCBOpBinarysDlg(QWidget *parent) :
QDialog(parent),
ui(new Ui::QDiffCBOpBinarysDlg)
{
    ui->setupUi(this);
    m_pParas = NULL;
    InitUI();
	InitLanuage();
	setWindowTitle(g_sLangTxt_Native_Switch);
}

QDiffCBOpBinarysDlg::~QDiffCBOpBinarysDlg()
{
    delete ui;
}
void QDiffCBOpBinarysDlg::InitUI()
{
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setFont(*g_pSttGlobalFont);
}
void QDiffCBOpBinarysDlg::SetDatas(CExBaseList *pParas)
{
    if(pParas == NULL)
    {
        return;
    }

    m_pParas = pParas;
    CheckAllPresence(m_pParas);
    POS pos = m_pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
        SetValueToPage(pData);
    }
}
void QDiffCBOpBinarysDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
    if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BINLOGIC)
    {
        ui->m_radio_and->setChecked(pData->m_strValue == "1");
        ui->m_radio_or->setChecked(pData->m_strValue != "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_A)
    {
        ui->m_pChkBinA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B)
    {
        ui->m_pChkBinB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_C)
    {
        ui->m_pChkBinC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_D)
    {
        ui->m_pChkBinD->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_E)
    {
        ui->m_pChkBinE->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_F)
    {
        ui->m_pChkBinF->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_G)
    {
        ui->m_pChkBinG->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_H)
    {
        ui->m_pChkBinH->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B01)
    {
        ui->m_pChkBout1->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B02)
    {
        ui->m_pChkBout2->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B03)
    {
        ui->m_pChkBout3->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B04)
    {
        ui->m_pChkBout4->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B05)
    {
        ui->m_pChkBout5->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B06)
    {
        ui->m_pChkBout6->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B07)
    {
        ui->m_pChkBout7->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B08)
    {
        ui->m_pChkBout8->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB01)
    {
        ui->m_pChkFaultBout1->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB02)
    {
        ui->m_pChkFaultBout2->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB03)
    {
        ui->m_pChkFaultBout3->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB04)
    {
        ui->m_pChkFaultBout4->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB05)
    {
        ui->m_pChkFaultBout5->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB06)
    {
        ui->m_pChkFaultBout6->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB07)
    {
        ui->m_pChkFaultBout7->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB08)
    {
        ui->m_pChkFaultBout8->setChecked(pData->m_strValue == "1");
    }
}
void QDiffCBOpBinarysDlg::GetDatas(CExBaseList *pParas)
{
    POS pos = pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
        GetPageToValue(pData);
    }
}
void QDiffCBOpBinarysDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
    bool bState;
    if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BINLOGIC)
    {
        bState = ui->m_radio_and->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_A)
    {
        bState = ui->m_pChkBinA->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B)
    {
        bState = ui->m_pChkBinB->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_C)
    {
        bState = ui->m_pChkBinC->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_D)
    {
        bState = ui->m_pChkBinD->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_E)
    {
        bState = ui->m_pChkBinE->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_F)
    {
        bState = ui->m_pChkBinF->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_G)
    {
        bState = ui->m_pChkBinG->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_H)
    {
        bState = ui->m_pChkBinH->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B01)
    {
        bState = ui->m_pChkBout1->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B02)
    {
        bState = ui->m_pChkBout2->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B03)
    {
        bState = ui->m_pChkBout3->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B04)
    {
        bState = ui->m_pChkBout4->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B05)
    {
        bState = ui->m_pChkBout5->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B06)
    {
        bState = ui->m_pChkBout6->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B07)
    {
        bState = ui->m_pChkBout7->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B08)
    {
        bState = ui->m_pChkBout8->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB01)
    {
        bState = ui->m_pChkFaultBout1->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB02)
    {
        bState = ui->m_pChkFaultBout2->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB03)
    {
        bState = ui->m_pChkFaultBout3->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB04)
    {
        bState = ui->m_pChkFaultBout4->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB05)
    {
        bState = ui->m_pChkFaultBout5->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB06)
    {
        bState = ui->m_pChkFaultBout6->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB07)
    {
        bState = ui->m_pChkFaultBout7->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB08)
    {
        bState = ui->m_pChkFaultBout8->isChecked();
        pData->m_strValue.Format("%d",bState);
    }
}

void QDiffCBOpBinarysDlg::on_m_pBtnOk_clicked()
{
    this->done(Accepted);
}

void QDiffCBOpBinarysDlg::on_m_pBtnCancel_clicked()
{
    this->close();
}


void QDiffCBOpBinarysDlg::CheckForPresence(CExBaseList *pParas,CString strID)
{
    if(pParas == NULL)
        return;
    CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
    if(pData == NULL)
    {
        CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
        pNew->m_strName = strID;
        pNew->m_strID = strID;
        pNew->m_strValue = STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_DEFAULT;
        pParas->AddNewChild(pNew);
    }
}
void QDiffCBOpBinarysDlg::CheckAllPresence(CExBaseList *pParas)
{
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_A);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_C);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_D);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_E);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_F);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_G);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_H);

    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B01);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B02);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B03);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B04);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B05);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B06);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B07);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B08);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB01);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB02);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB03);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB04);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB05);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB06);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB07);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB08);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BINLOGIC);
}
void QDiffCBOpBinarysDlg::UpdataAllBinarys(CExBaseList *pAllParas)
{
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


BOOL QDiffCBOpBinarysDlg::CheckItemsModify(CExBaseList *pItem)
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

void QDiffCBOpBinarysDlg::InitLanuage()
{
	ui->m_pBinBoutGroupBox->setTitle(g_sLangTxt_Native_InputSet);
	ui->m_pBoutGroupBox->setTitle(g_sLangTxt_DiffCBOp_BoutSet);
	ui->m_pFaultBoutGroupBox->setTitle(g_sLangTxt_DiffCBOp_FaultBoutSet);
	ui->m_pChkBinA->setText(g_sLangTxt_Manual_InA);
	ui->m_pChkBinB->setText(g_sLangTxt_Manual_InB);
	ui->m_pChkBinC->setText(g_sLangTxt_Manual_InC);
	ui->m_pChkBinD->setText(g_sLangTxt_Manual_InD);
	ui->m_pChkBinE->setText(g_sLangTxt_Manual_InE);
	ui->m_pChkBinF->setText(g_sLangTxt_Manual_InF);
	ui->m_pChkBinG->setText(g_sLangTxt_Manual_InG);
	ui->m_pChkBinH->setText(g_sLangTxt_Manual_InH);
	ui->m_pChkBout1->setText(g_sLangTxt_Manual_Out1);
	ui->m_pChkBout2->setText(g_sLangTxt_Manual_Out2);
	ui->m_pChkBout3->setText(g_sLangTxt_Manual_Out3);
	ui->m_pChkBout4->setText(g_sLangTxt_Manual_Out4);
	ui->m_pChkBout5->setText(g_sLangTxt_Manual_Out5);
	ui->m_pChkBout6->setText(g_sLangTxt_Manual_Out6);
	ui->m_pChkBout7->setText(g_sLangTxt_Manual_Out7);
	ui->m_pChkBout8->setText(g_sLangTxt_Manual_Out8);
	ui->m_pChkFaultBout1->setText(g_sLangTxt_Manual_Out1);
	ui->m_pChkFaultBout2->setText(g_sLangTxt_Manual_Out2);
	ui->m_pChkFaultBout3->setText(g_sLangTxt_Manual_Out3);
	ui->m_pChkFaultBout4->setText(g_sLangTxt_Manual_Out4);
	ui->m_pChkFaultBout5->setText(g_sLangTxt_Manual_Out5);
	ui->m_pChkFaultBout6->setText(g_sLangTxt_Manual_Out6);
	ui->m_pChkFaultBout7->setText(g_sLangTxt_Manual_Out7);
	ui->m_pChkFaultBout8->setText(g_sLangTxt_Manual_Out8);

	ui->m_radio_and->setText(g_sLangTxt_Native_LogicAnd);
	ui->m_radio_or->setText(g_sLangTxt_Native_LogicOr);

	ui->m_pBtnOk->setText(g_sLangTxt_OK);
	ui->m_pBtnCancel->setText(g_sLangTxt_Cancel);
}
