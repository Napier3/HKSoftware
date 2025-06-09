#include "DiffCBOpCommonParasDlg.h"
#include "ui_DiffCBOpCommonParasDlg.h"
#include "../QSttMultiMacroParaEditViewBase.h"

extern CFont *g_pSttGlobalFont;

QDiffCBOpCommonParasDlg::QDiffCBOpCommonParasDlg(QWidget *parent) :
QDialog(parent),ui(new Ui::QDiffCBOpCommonParasDlg)
{
    ui->setupUi(this);
    m_pParas = NULL;
    m_nModify = 0;
    InitUI();
	InitLanuage();
	setWindowTitle(g_sLangTxt_GeneralParameter);
}

QDiffCBOpCommonParasDlg::~QDiffCBOpCommonParasDlg()
{
    delete ui;
}
void QDiffCBOpCommonParasDlg::InitUI()
{
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
	long nCBSValue = ui->m_pCmbCBSimulation->currentIndex();
	on_m_pCmbCBSimulation_currentIndexChanged(nCBSValue);
	long nInselValue = ui->m_pCmbInsel->currentIndex();
	on_m_pCmbInsel_currentIndexChanged(nInselValue);
}
void QDiffCBOpCommonParasDlg::SetDatas(CExBaseList *pParas)
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
}
void QDiffCBOpCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
    if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREPARETIME)
    {
        ui->m_pEditPrepareTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREFAULTTIME)
    {
        ui->m_pEditPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIMEMARGIN)
    {
        ui->m_pEditFaultTimeMargin->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ACTIONHOLDTIME)
    {
		ui->m_pEditActionHoldTime->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
       // ui->m_pEditActionHoldTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHM)
    {
        ui->m_pCmbAroundClockNumHM->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHL)
    {
        ui->m_pCmbAroundClockNumHL->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS)
    {
        ui->m_pCmbBalanceTerms->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT)
    {
		ui->m_pCmbCTStarPoint->setCurrentIndex(pData->m_strValue.toInt());
		int nValue = pData->m_strValue.toInt();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH)
    {
        ui->m_pCmbIbiasCal->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1)
    {
        ui->m_pEditFactor1->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2)
    {
        ui->m_pEditFactor2->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COMBINEFEATURE)
    {
        ui->m_pCmbComBineFeature->setCurrentIndex(pData->m_strValue.toInt());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ZEROSEQELIMITYPE)
	{
		ui->m_pCmbZeroSeqElimiType->setCurrentIndex(pData->m_strValue.toInt());
	}
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_EARTHING)
    {
        ui->m_pCmbEarthing->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBSIMULATION)
    {
        ui->m_pCmbCBSimulation->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBTRIPTIME)
    {
        ui->m_pEditCBTripTime->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBCLOSETIME)
    {
        ui->m_pEditCBCloseTime->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE)
    {
        ui->m_pCmbCoordinate->setCurrentIndex(pData->m_strValue.toInt());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH)
	{
		ui->m_pCmbWindH->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM)
	{
		ui->m_pCmbWindM->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL)
	{
		ui->m_pCmbWindL->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE)
	{
		ui->m_pCmbPhCorrectMode->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND)
	{
		ui->m_pCmbAdoptWind->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIME)
	{
		ui->m_pEditFaultTime->setText(CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STEP)
	{
		ui->m_pEditStep->setText(CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG1)
	{
		ui->m_pEditVg1->setText(CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG2)
	{
		ui->m_pEditVg2->setText(CheckDataMinMax(pData->m_strValue, 999999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSET)
	{
		ui->m_pEditInSet->setText(CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSEL)
	{
		ui->m_pCmbInsel->setCurrentIndex(pData->m_strValue.toInt());
	}
}
void QDiffCBOpCommonParasDlg::GetDatas(CExBaseList *pParas)
{
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
void QDiffCBOpCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREPARETIME)
    {
        pData->m_strValue = ui->m_pEditPrepareTime->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREFAULTTIME)
    {
        pData->m_strValue = ui->m_pEditPreFaultTime->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIMEMARGIN)
    {
        pData->m_strValue = ui->m_pEditFaultTimeMargin->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ACTIONHOLDTIME)
    {
		pData->m_strValue = ui->m_pEditActionHoldTime->GetText();//text()
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHM)
    {
        pData->m_strValue.Format("%d",ui->m_pCmbAroundClockNumHM->currentIndex());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHL)
    {
        pData->m_strValue.Format("%d",ui->m_pCmbAroundClockNumHL->currentIndex());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSGROUPMODE)
	{
		m_nConnectMode = 0;
		switch (ui->m_pCmbAdoptWind->currentIndex())
		{
		case 0://0-ï¿?ï¿?
			m_nConnectMode = ui->m_pCmbAroundClockNumHL->currentIndex();
			break;
		case 1://1-ï¿?ï¿?
			m_nConnectMode = ui->m_pCmbAroundClockNumHM->currentIndex();
			break;
		case 2://2-ï¿?ï¿?
			m_nConnectMode = ui->m_pCmbAroundClockNumHM->currentIndex() - ui->m_pCmbAroundClockNumHL->currentIndex();
			if (m_nConnectMode <= 0)
			{
				m_nConnectMode += 12;
			}
			break;
		}
		pData->m_strValue.Format("%d", m_nConnectMode);
	}
	
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS)
    {
        pData->m_strValue.Format("%d",ui->m_pCmbBalanceTerms->currentIndex());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT)
    {
		pData->m_strValue.Format("%d", ui->m_pCmbCTStarPoint->currentIndex());
		CString strText = pData->m_strValue;
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH)
    {
		pData->m_strValue.Format("%d", ui->m_pCmbIbiasCal->currentIndex());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1)
    {
        pData->m_strValue = ui->m_pEditFactor1->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2)
    {
        pData->m_strValue = ui->m_pEditFactor2->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COMBINEFEATURE)
    {
        pData->m_strValue.Format("%d",ui->m_pCmbComBineFeature->currentIndex());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ZEROSEQELIMITYPE)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbZeroSeqElimiType->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_EARTHING)
    {
        pData->m_strValue.Format("%d",ui->m_pCmbEarthing->currentIndex());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBSIMULATION)
    {
        pData->m_strValue.Format("%d",ui->m_pCmbCBSimulation->currentIndex());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBTRIPTIME)
    {
		pData->m_strValue = ui->m_pEditCBTripTime->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBCLOSETIME)
    {
		pData->m_strValue = ui->m_pEditCBCloseTime->text();
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE)
    {
		pData->m_strValue.Format("%d", ui->m_pCmbCoordinate->currentIndex());
    }
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbWindH->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbWindM->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbWindL->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbPhCorrectMode->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbAdoptWind->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIME)
	{
		pData->m_strValue = ui->m_pEditFaultTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STEP)
	{
		pData->m_strValue = ui->m_pEditStep->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG1)
	{
		pData->m_strValue = ui->m_pEditVg1->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG2)
	{
		pData->m_strValue = ui->m_pEditVg2->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSET)
	{
		pData->m_strValue = ui->m_pEditInSet->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSEL)
	{
		pData->m_strValue.Format("%d", ui->m_pCmbInsel->currentIndex());
	}

}
void QDiffCBOpCommonParasDlg::on_m_pEditPrepareTime_editingFinished()
{
    ui->m_pEditPrepareTime->setText(CheckDataMinMax(ui->m_pEditPrepareTime->text(),999.999,0,3));
}
void QDiffCBOpCommonParasDlg::on_m_pEditPreFaultTime_editingFinished()
{
    ui->m_pEditPreFaultTime->setText(CheckDataMinMax(ui->m_pEditPreFaultTime->text(),999.999,0,3));
}

void QDiffCBOpCommonParasDlg::on_m_pEditFaultTimeMargin_editingFinished()
{
    ui->m_pEditFaultTimeMargin->setText(CheckDataMinMax(ui->m_pEditFaultTimeMargin->text(),999.999,0,3));
}

void QDiffCBOpCommonParasDlg::on_m_pEditActionHoldTime_editingFinished()
{
	if (ui->m_pEditActionHoldTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pEditActionHoldTime)->IsSetting())
		{
			return;
		}
	}
    ui->m_pEditActionHoldTime->setText(CheckDataMinMax(ui->m_pEditActionHoldTime->text(),999.999,0,3));

	return;
}

void QDiffCBOpCommonParasDlg::on_m_pEditFactor1_editingFinished()
{
    ui->m_pEditFactor1->setText(CheckDataMinMax(ui->m_pEditFactor1->text(),999999,0,3));
}

void QDiffCBOpCommonParasDlg::on_m_pEditFactor2_editingFinished()
{
    ui->m_pEditFactor2->setText(CheckDataMinMax(ui->m_pEditFactor2->text(),999999,0,3));
}

void QDiffCBOpCommonParasDlg::on_m_pEditCBTripTime_editingFinished()
{
    ui->m_pEditCBTripTime->setText(CheckDataMinMax(ui->m_pEditCBTripTime->text(),999999,0,3));
}

void QDiffCBOpCommonParasDlg::on_m_pEditCBCloseTime_editingFinished()
{
    ui->m_pEditCBCloseTime->setText(CheckDataMinMax(ui->m_pEditCBCloseTime->text(),999999,0,3));
}

void QDiffCBOpCommonParasDlg::on_m_pEditFaultTime_editingFinished()
{
	ui->m_pEditFaultTime->setText(CheckDataMinMax(ui->m_pEditFaultTime->text(), 999999, 0, 3));
}
void QDiffCBOpCommonParasDlg::on_m_pEditStep_editingFinished()
{
	ui->m_pEditStep->setText(CheckDataMinMax(ui->m_pEditStep->text(), 999999, 0, 3));
}
void QDiffCBOpCommonParasDlg::on_m_pEditVg1_editingFinished()
{
	ui->m_pEditVg1->setText(CheckDataMinMax(ui->m_pEditVg1->text(), 999999, 0, 3));
}
void QDiffCBOpCommonParasDlg::on_m_pEditVg2_editingFinished()
{
	ui->m_pEditVg2->setText(CheckDataMinMax(ui->m_pEditVg2->text(), 999999, 0, 3));
}

void QDiffCBOpCommonParasDlg::on_m_pCmbCBSimulation_currentIndexChanged(int nIndex)
{
	if (nIndex == 0)
    {
        ui->m_pEditCBTripTime->setEnabled(false);
        ui->m_pEditCBCloseTime->setEnabled(false);
    }
	else if (nIndex == 1)
    {
        ui->m_pEditCBTripTime->setEnabled(true);
        ui->m_pEditCBCloseTime->setEnabled(true);
    }
}

void QDiffCBOpCommonParasDlg::on_m_pCmbInsel_currentIndexChanged(int nIndex)
{
	if (nIndex == 0)
	{
		ui->m_pEditInSet->setEnabled(false);
	}
	else if (nIndex == 1)
	{
		ui->m_pEditInSet->setEnabled(true);
	}
	else if (nIndex == 2)
	{
		ui->m_pEditInSet->setEnabled(false);
	}
}

void QDiffCBOpCommonParasDlg::on_m_pCmbCoordinate_currentIndexChanged(int nIndex)
{
	m_nCoordinate = nIndex;
}

void QDiffCBOpCommonParasDlg::on_m_pCmbAdoptWind_currentIndexChanged(int nIndex)
{
	m_nAdoptWind = nIndex;
}

void QDiffCBOpCommonParasDlg::on_m_pBtnOk_clicked()
{
    this->done(Accepted);
}

void QDiffCBOpCommonParasDlg::on_m_pBtnCancel_clicked()
{
    this->close();
}
void QDiffCBOpCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREPARETIME);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREFAULTTIME);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIMEMARGIN);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ACTIONHOLDTIME);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHM);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHL);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COMBINEFEATURE);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ZEROSEQELIMITYPE);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_EARTHING);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBSIMULATION);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBTRIPTIME);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBCLOSETIME);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIME);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STEP);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG1);
	CheckForPresence(pParas, STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG2);
}
void QDiffCBOpCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
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
CString QDiffCBOpCommonParasDlg::CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint)
{
	float fvalue = strValue.toFloat();

	if (fvalue<nMin)
	{
		fvalue = nMin;
	}
	else if (fvalue>nMax)
	{
		fvalue = nMax;
	}
	return QString::number(fvalue, 'f', nAfterPoint);
}
void QDiffCBOpCommonParasDlg::CheckForPresence(CExBaseList *pParas,CString strID)
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
//void QDiffCBOpCommonParasDlg::CheckRxValue(CString &strR,CString &strX,CString strZSetting,CString strZAng)
//{
//    float fR,fX,fZSetting,fZAng;
//    fZSetting = strZSetting.toFloat();
//    fZAng = strZAng.toFloat();

//    if(fZAng<-180.0)
//    {
//        fZAng+=360.0;
//    }
//    if(fZAng>360.0)
//    {
//        fZAng-=360.0;
//    }

//    fX= fZSetting*sin(fZAng*3.14159/180.0);
//    fR= fZSetting*cos(fZAng*3.14159/180.0);

//    strX.Format("%.3f",fX);
//    strR.Format("%.3f",fR);
//}
//void QDiffCBOpCommonParasDlg::CheckZSettingAndZAng(CString strR,CString strX,CString &strZSetting,CString &strZAng)
//{
//    float fR,fX,fZSetting,fZAng;
//    fR = strR.toFloat();
//    fX = strX.toFloat();
//    fZSetting = hypot(fX,fR);
//    if(fabs(fR)>0.0001)
//    {
//        fZAng=atan2(fX,fR)*180.0/3.14159;
//    }
//    else
//    {
//        fZAng=0.0;
//    }
//    strZSetting.Format("%.3f",fZSetting);
//    strZAng.Format("%.1f",fZAng);
//}


BOOL QDiffCBOpCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
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
        if( pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHM ||pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHL||\
            pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS ||pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT||\
            pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH ||pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COMBINEFEATURE||\
			pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ZEROSEQELIMITYPE || pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_EARTHING || \
			pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBSIMULATION || pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE)
        {
            if (pData->m_strValue != pData_New->m_strValue)
            {
                m_nModify = 1;
                return TRUE;
            }

        }
        else
        {//æµ®ç‚¹æ•°åˆ¤æ–­å·®å€¼çš„ç»å¯¹ï¿?
            if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
            {
                m_nModify = 1;
                return TRUE;
            }
        }

    }
    return FALSE;
}

void QDiffCBOpCommonParasDlg::InitLanuage()
{
	ui->m_pBtnOk->setText(g_sLangTxt_OK);
	ui->m_pBtnCancel->setText(g_sLangTxt_Cancel);
	ui->m_pLabPrepareTime->setText(g_sLangTxt_Diff_PrepareTime);
	ui->m_pLabPreFaultTime->setText(g_sLangTxt_Native_PreFaultTime);
	ui->m_pLabFaultTime->setText(g_sLangTxt_Gradient_Time);
	ui->m_pLabFaultTimeMargin->setText(g_sLangTxt_Native_FaultTimeMargin);
	ui->m_pLabActionHoldTime->setText(g_sLangTxt_Diff_TimeAfter);
	ui->m_pLabWindH->setText(g_sLangTxt_Native_HighVoltWindingConnType);
	ui->m_pLabWindM->setText(g_sLangTxt_Native_MedVoltWindingConnType);
	ui->m_pLabWindL->setText(g_sLangTxt_Native_LowVoltWindingConnType);
	ui->m_pLabPhCorrectMode->setText(g_sLangTxt_Diff_PhCorrectMode);
	ui->m_pLabAdoptWind->setText(g_sLangTxt_Diff_AdoptWind);
	ui->m_pLabInsel->setText(g_sLangTxt_Native_DifCurChoose);
	ui->m_pLabInSet->setText(g_sLangTxt_Native_BaseCurrSet);
	ui->m_pLabAroundClockNumHM->setText(g_sLangTxt_Diff_TransGroupModeHM);
	ui->m_pLabAroundClockNumHL->setText(g_sLangTxt_Diff_TransGroupModeHL);
	ui->m_pLabBalanceTerms->setText(g_sLangTxt_Diff_JXFactor);
	ui->m_pLabCTStarPoint->setText(g_sLangTxt_State_CTpolarity);
	ui->m_pLabIbiasCal->setText(g_sLangTxt_State_Bequation);
	ui->m_pLabComBineFeature->setText(g_sLangTxt_DiffCBOp_ComBineFeature);
	ui->m_pLabZeroSeqElimiType->setText(g_sLangTxt_DiffCBOp_ZeroSeqElimiType);
	ui->m_pLabEarthing->setText(g_sLangTxt_DiffCBOp_Earthing);
	ui->m_pLabStep->setText(g_sLangTxt_Native_TestPrecision);
	ui->m_pLabCBSimulation->setText(g_sLangTxt_CBOperate_SimulateBreakerDelay);
	ui->m_pLabCBTripTime->setText(g_sLangTxt_CBOperate_BrkBreakTime);
	ui->m_pLabCBCloseTime->setText(g_sLangTxt_CBOperate_BrkCloseTime);
	ui->m_pLabCoordinate->setText(g_sLangTxt_DiffCBOp_Coordinate);

	ui->m_pCmbPhCorrectMode->addItems(QStringList() << g_sLangTxt_State_NoAdjust << g_sLangTxt_State_Triangulationcorrection << g_sLangTxt_State_YAdjust << "Z" + g_sLangTxt_Diff_sideAdjust);
	ui->m_pCmbAdoptWind->addItems(QStringList() << g_sLangTxt_Diff_High + "-" + g_sLangTxt_Diff_Low << g_sLangTxt_Diff_High + "-" + g_sLangTxt_Diff_Medium << g_sLangTxt_Diff_Medium + "-" + g_sLangTxt_Diff_Low);
	ui->m_pCmbInsel->addItems(QStringList() << g_sLangTxt_DiffCBOp_HSecondCur << g_sLangTxt_DiffCBOp_SetValue << g_sLangTxt_DiffCBOp_AllSecondCur);
	ui->m_pCmbAroundClockNumHM->addItems(QStringList() << "12" + g_sLangTxt_State_Oclock << "1" + g_sLangTxt_State_Oclock << "2" + g_sLangTxt_State_Oclock << "3" + g_sLangTxt_State_Oclock << "4" + g_sLangTxt_State_Oclock << "5" + g_sLangTxt_State_Oclock
		<< "6" + g_sLangTxt_State_Oclock << "7" + g_sLangTxt_State_Oclock << "8" + g_sLangTxt_State_Oclock << "9" + g_sLangTxt_State_Oclock << "10" + g_sLangTxt_State_Oclock << "11" + g_sLangTxt_State_Oclock );
	ui->m_pCmbAroundClockNumHL->addItems(QStringList() << "12" + g_sLangTxt_State_Oclock << "1" + g_sLangTxt_State_Oclock << "2" + g_sLangTxt_State_Oclock << "3" + g_sLangTxt_State_Oclock << "4" + g_sLangTxt_State_Oclock << "5" + g_sLangTxt_State_Oclock
		<< "6" + g_sLangTxt_State_Oclock << "7" + g_sLangTxt_State_Oclock << "8" + g_sLangTxt_State_Oclock << "9" + g_sLangTxt_State_Oclock << "10" + g_sLangTxt_State_Oclock << "11" + g_sLangTxt_State_Oclock );

	ui->m_pCmbBalanceTerms->addItems(QStringList() << g_sLangTxt_State_NotconWindconnection << g_sLangTxt_State_Winding);
	ui->m_pCmbCTStarPoint->addItems(QStringList() << g_sLangTxt_State_Trans2 << g_sLangTxt_State_Trans1);
	ui->m_pCmbIbiasCal->addItems(QStringList() <</*"Ir=(|I1-I2|)/K1»òIr=(|I1+I2|)/K1"*/g_sLangTxt_Diff_Bequation1
		<< "Ir=(|I1|+|I2|*K2)/K1" << "Ir=max(|I1|,|I2|)"
		<< "Ir=(|Id-|I1|-|I2||)/K1"
		<</*"Ir=|I2|"<<"Ir=¡Ì(K1*I1*I2*Cos(¦Ä))"*/g_sLangTxt_Diff_Bequation5);
	ui->m_pCmbComBineFeature->addItems(QStringList() << g_sLangTxt_State_Yes << g_sLangTxt_State_No); 
	ui->m_pCmbZeroSeqElimiType->addItems(QStringList() << g_sLangTxt_without << g_sLangTxt_Diff_LineCur + "-" + g_sLangTxt_PowerDir_FaultPhase_ZeroCur << g_sLangTxt_DiffCBOp_Auxiliary);
	ui->m_pCmbEarthing->addItems(QStringList() << g_sLangTxt_State_Yes << g_sLangTxt_State_No/*<< g_sLangTxt_Diff_LineCur + "-" + g_sLangTxt_PowerDir_FaultPhase_ZeroCur << "YD" << g_sLangTxt_without*/);
	ui->m_pCmbCBSimulation->addItems(QStringList() << g_sLangTxt_CBOperate_NotSimulated << g_sLangTxt_ChMaps_Analog);
	ui->m_pCmbCoordinate->addItems(QStringList() <<  g_sLangTxt_DiffCBOp_FamousValue << g_sLangTxt_DiffCBOp_StandardValue);
}
