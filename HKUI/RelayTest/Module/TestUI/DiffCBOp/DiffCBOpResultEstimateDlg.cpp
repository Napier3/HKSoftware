#include "DiffCBOpResultEstimateDlg.h"
#include "ui_DiffCBOpResultEstimateDlg.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include <QString>
QDiffCBOpResultEstimateDlg::QDiffCBOpResultEstimateDlg(QWidget *parent) :
QDialog(parent),ui(new Ui::DiffCBOpResultEstimateDlg)
{

    ui->setupUi(this);
    m_nModify = 0;
    setWindowTitle(/*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

QDiffCBOpResultEstimateDlg::~QDiffCBOpResultEstimateDlg()
{
    delete ui;
}


void QDiffCBOpResultEstimateDlg::InitUI()
{
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setFont(*g_pSttGlobalFont);
    ui->m_cmbFluatType->addItems(QStringList()
        << g_sLangTxt_StateEstimate_AbsError
        << g_sLangTxt_StateEstimate_RelError
		<< g_sLangTxt_StateEstimate_AbsError + "or" + g_sLangTxt_StateEstimate_RelError
		<< g_sLangTxt_StateEstimate_AbsError + "&" + g_sLangTxt_StateEstimate_RelError
		//<< g_sLangTxt_CBOperate_CombError
		<< g_sLangTxt_Distance_ErrorNot);

	ui->m_labName->setText(g_sLangTxt_AttrID_Name);
	ui->m_labSetting->setText(g_sLangTxt_SetValue);
	ui->m_labType->setText(g_sLangTxt_StateEstimate_ErrorType);
	ui->m_labRel->setText(g_sLangTxt_StateEstimate_RelError + "(%)");
	ui->m_labAbs->setText(g_sLangTxt_StateEstimate_AbsError);
	ui->m_labAbs_2->setText(g_sLangTxt_StateEstimate_AbsError + "(-)");
	ui->m_labActionTime->setText(g_sLangTxt_Gradient_ActionTime);
	ui->m_btnOK->setText(g_sLangTxt_OK);
	ui->m_btnCancel->setText(g_sLangTxt_Cancel);
}


void QDiffCBOpResultEstimateDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR)
    {
		
		ui->m_txtRel3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM)
    {
		ui->m_txtPlus_3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE)
    {
		ui->m_txtMinus_3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100, 0, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE)
    {
		if (pData->m_strValue.toInt() == 5)
		{
			ui->m_cmbFluatType->setCurrentIndex(4);
		}
		else
		{
        ui->m_cmbFluatType->setCurrentIndex(pData->m_strValue.toInt());
    }
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SETTING)
	{
		ui->m_EditSetting->setText(CheckDataMinMax(pData->m_strValue, 100, 0, 3));
	}
}

void QDiffCBOpResultEstimateDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE)
    {
		if (ui->m_cmbFluatType->currentIndex() == 4)
		{
			pData->m_strValue.Format("%d", 5);
		}
		else
		{
			pData->m_strValue.Format("%d", ui->m_cmbFluatType->currentIndex());
		}
        
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR)
    {
        pData->m_strValue = ui->m_txtRel3->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM)
    {
        pData->m_strValue = ui->m_txtPlus_3->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE)
    {
        pData->m_strValue = ui->m_txtMinus_3->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SETTING)
	{
		pData->m_strValue = ui->m_EditSetting->text();
	}

}


void QDiffCBOpResultEstimateDlg::SetDatas(CExBaseList *pParas)
{
    //Set将读取数据转换到界面
    if (pParas == NULL)
    {
        return;
    }
    m_pParas = pParas;

	long nValue = 0;
	CSttMacroTestParaData *pDvmData = (CSttMacroTestParaData *)pParas->FindByID("ErrorType");
	if (pDvmData != NULL)
	{
		nValue = CString_To_long(pDvmData->m_strValue);
	}
	on_m_cmbFluatType_currentIndexChanged(nValue);
    InitUI();

    CheckAllPresence(m_pParas);

    POS pos = m_pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
        SetValueToPage(pData);
    }
}

void QDiffCBOpResultEstimateDlg::GetDatas(CExBaseList *pParas)
{
    //Get将界面设置参数填到链表
    if(pParas == NULL)
        return;
    m_pParas = pParas;

    CheckAllPresence(m_pParas);

    POS pos = m_pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
        GetPageToValue(pData);
    }
}

void QDiffCBOpResultEstimateDlg::on_m_btnOK_clicked()
{
    this->done(Accepted);
}

void QDiffCBOpResultEstimateDlg::on_m_btnCancel_clicked()
{
    this->close();
}

void QDiffCBOpResultEstimateDlg::on_m_cmbFluatType_currentIndexChanged(int nIndex)
{
	bool bSettingEnabled = (nIndex != 5);
	bool bRrelEnabled = (nIndex != 5) && (nIndex != 0) && (nIndex != 4);
	bool bPlusEnabled = (nIndex != 5) && (nIndex != 1) && (nIndex != 4);
	bool bMinusEnabled = bPlusEnabled;

	ui->m_EditSetting->setEnabled(bSettingEnabled);
	ui->m_txtRel3->setEnabled(bRrelEnabled);
	ui->m_txtPlus_3->setEnabled(bPlusEnabled);
	ui->m_txtMinus_3->setEnabled(bMinusEnabled);

}

void QDiffCBOpResultEstimateDlg::on_m_txtRel3_editingFinished()
{
	if (ui->m_txtRel3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtRel3)->IsSetting())
		{
			return;
		}
	}
	ui->m_txtRel3->setText(CheckDataMinMax(ui->m_txtRel3->text(), 100.000, 0, 3));

	return;
}

void QDiffCBOpResultEstimateDlg::on_m_txtPlus_3_editingFinished()
{
	if (ui->m_txtRel3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtRel3)->IsSetting())
		{
			return;
		}
	}
    ui->m_txtPlus_3->setText(CheckDataMinMax(ui->m_txtPlus_3->text(),100,0,3));

	return;
}

void QDiffCBOpResultEstimateDlg::on_m_txtMinus_3_editingFinished()
{
	if (ui->m_txtRel3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtRel3)->IsSetting())
		{
			return;
		}
	}
    ui->m_txtMinus_3->setText(CheckDataMinMax(ui->m_txtMinus_3->text(),100,0,3));

	return;
}

void QDiffCBOpResultEstimateDlg::on_m_EditSetting_editingFinished()
{
	ui->m_EditSetting->setText(CheckDataMinMax(ui->m_EditSetting->text(), 100, 0, 3));
}

CString QDiffCBOpResultEstimateDlg::CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint)
{
    if (strValue.toFloat()<nMin)
    {
        strValue.setNum(nMin);
    }
    if(strValue.toFloat()>nMax && nMin != nMax)
    {
        strValue.setNum(nMax);
    }
    int num = 0;
    int nPoint = strValue.indexOf(".");
    if(nPoint == -1)
    {
        if (strValue == "")
        {
            strValue = "0";
        }
        if(nAfterPoint>0)
            strValue += ".";
    }
    else
    {
        num = strValue.length()-nPoint-1;
        if (num>nAfterPoint)
        {
            if(nAfterPoint >0)
                strValue = strValue.left(nPoint+1+nAfterPoint);
            else
                strValue = strValue.left(nPoint+nAfterPoint);
            num = nAfterPoint;
        }
    }
    for (int i=num;i<nAfterPoint;i++)
    {
        strValue+="0";
    }
    return strValue;
}

void QDiffCBOpResultEstimateDlg::CheckAllPresence(CExBaseList *pParas)
{
	
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SETTING);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE);

}
void QDiffCBOpResultEstimateDlg::CheckForPresence(CExBaseList *pParas,CString strID)
{
    if(pParas == NULL)
    {
        return;
    }
    CDvmData *pData = (CDvmData *)pParas->FindByID(strID);
    if(pData == NULL)
    {
        CDvmData *pNew = new CDvmData();
        pNew->m_strName = strID;
        pNew->m_strID = strID;
        pNew->m_strValue = STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_DEFAULT;
        pParas->AddNewChild(pNew);
    }
}

void QDiffCBOpResultEstimateDlg::UpdataAllResult(CExBaseList *pAllParas)
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
                CDataGroup* pDataGroup = (CDataGroup*)pParaDatas;
                GetDatas(pDataGroup);
            }
        }
    }
}


BOOL QDiffCBOpResultEstimateDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE)
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
    return FALSE;
}

void QDiffCBOpResultEstimateDlg::UpdataAllResults(CExBaseList *pAllItems)
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
}
