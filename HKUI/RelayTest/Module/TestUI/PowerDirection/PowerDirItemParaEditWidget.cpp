#include "PowerDirItemParaEditWidget.h"
#include "ui_PowerDirItemParaEditWidget.h"
#include "PowerDirCommon.h"
#include "../../XLangResource_Native.h"

extern CFont *g_pSttGlobalFont;
static bool bFlag = false;  //配置功能界面时，获取故障相参数之前不update故障相数据，否则会被覆盖
int nTestPhaseToShow[9] = {TESTPHASE_AN_SHOW,TESTPHASE_BN_SHOW,TESTPHASE_CN_SHOW,TESTPHASE_ZEROTEST_SHOW, TESTPHASE_NEGTEST_SHOW, TESTPHASE_AB_SHOW, TESTPHASE_BC_SHOW, TESTPHASE_CA_SHOW, TESTPHASE_ABC_SHOW};
int nTestPhaseToUpdate[9]={TESTPHASE_AN,TESTPHASE_BN,TESTPHASE_CN,TESTPHASE_AB,TESTPHASE_BC,TESTPHASE_CA,TESTPHASE_ABC,TESTPHASE_ZEROTEST,TESTPHASE_NEGTEST};

QPowerDirItemParaEditWidget::QPowerDirItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    ui(new Ui::QPowerDirItemParaEditWidget)
{
    ui->setupUi(this);
    m_nInputWidgetWidth = 250;
    InitUI();
	m_pCurrMacroTest_External = NULL;
}

QPowerDirItemParaEditWidget::~QPowerDirItemParaEditWidget()
{
    delete ui;
}

void QPowerDirItemParaEditWidget::InitUI()
{
	this->setFont(*g_pSttGlobalFont);
    ui->m_cbbTestPhase->insertItem(7, /*零序测试*/g_sLangTxt_PowerDir_TestPhase_Zero);
    ui->m_cbbTestPhase->insertItem(8, /*负序测试*/g_sLangTxt_PowerDir_TestPhase_Neg);

    ui->m_cbbFaultPhase->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbTestPhase->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editActionAreaRange->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultCur->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultVol->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editMTA->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editRelErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editStepValue->setFixedWidth(m_nInputWidgetWidth);

    ui->m_labTestPhase->setText(g_sLangTxt_PowerDir_TestPhase);
    ui->m_labFaultPhase->setText(g_sLangTxt_PowerDir_FaultPhase);
    ui->m_labFaultVol->setText(g_sLangTxt_ActionTime_FaultVol);
    ui->m_labFaultCur->setText(g_sLangTxt_Swing_SCurrent);
    ui->m_labFaultTime->setText(g_sLangTxt_PowerDir_FaultTime);
    ui->m_labMaxSenAng->setText(g_sLangTxt_PowerDir_MaxSenAngle);
    ui->m_labActionAreaRange->setText(g_sLangTxt_PowerDir_ActionAreaRange);
    ui->m_labStepValue->setText(g_sLangTxt_PowerDir_StepValue);
    ui->m_labAbsErr->setText(g_sLangTxt_PowerDir_AbsErr);
    ui->m_labRelErr->setText(g_sLangTxt_ActionTime_RelErr);
}

void QPowerDirItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_TESTPHASE)
	{
		bool bOk = false;
		int index = pData->m_strValue.toInt(&bOk);	
		if(!bOk)
			index = pData->m_strValue.toFloat(&bOk);

		if(pData->m_strValue.toInt() < 9)
		{
			index = nTestPhaseToShow[index];
		}
		ui->m_cbbTestPhase->setCurrentIndex(index);
		SetFaultPhaseComboBox(index);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTPHASE)
	{
		bool bOk = false;
		int index = pData->m_strValue.toInt(&bOk);	
		if(!bOk)
			index = pData->m_strValue.toFloat(&bOk);

		SetFaultPhaseComboBoxIndex(index);
		bFlag = true;
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTVOLT)
	{
		ui->m_editFaultVol->setText(PowerDirValueCheck(pData->m_strValue, FAULTVOLT_MAX, FAULTVOLT_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTCURRENT)
	{
		ui->m_editFaultCur->setText(PowerDirValueCheck(pData->m_strValue, FAULTCUR_MAX, FAULTCUR_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME)
	{
		ui->m_editFaultTime->setText(PowerDirValueCheck(pData->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA)
	{
        //ui->m_editMTA->setText(PowerDirValueCheck(pData->m_strValue, MTA_MAX, MTA_MIN, 2));
        ui->m_editMTA->UpdateObjectText(pData, PowerDirValueCheck(pData->m_strValue, MTA_MAX, MTA_MIN, 2), 2);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE)
	{
        ui->m_editActionAreaRange->setText(PowerDirValueCheck(pData->m_strValue, MTA_MAX, MTA_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE)
	{
        ui->m_editStepValue->setText(PowerDirValueCheck(pData->m_strValue, STEPVALUE_MAX, STEPVALUE_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR)
	{
        ui->m_editAbsErr->setText(PowerDirValueCheck(pData->m_strValue, STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR)
	{
		ui->m_editRelErr->setText(PowerDirValueCheck(pData->m_strValue, STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, 3));
	}

	return;
}

void QPowerDirItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_TESTPHASE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTPHASE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTVOLT);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTCURRENT);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR);
	PowerDirCheckParaExist(pParas, STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR);
}

void QPowerDirItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{
	QItemParaEditWidgetBase::UpdateParas(pSttMacroTest);
	bFlag = false;

	if(m_pCurrMacroTest_External != NULL)
	{
		CSttMacroTestParaDatas *pDstDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
		CheckAllPresence(pDstDatas_External);
	}

	CSttMacroTestParaDatas *pDstDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CheckAllPresence(pDstDatas);
	POS pos = pDstDatas->GetHeadPosition();
	while (pos!= NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->GetNext(pos);
		SetValueToPage(pData);
	}
	
	emit sig_UpdateVectorWidget();

	return;
}

void QPowerDirItemParaEditWidget::UpdatePara(CString strID,CString strValue)
{
	if (m_pSingleMacroRef == NULL)
	{
		return;
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);

	if(m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	}

	if(pDataInner != NULL)
	{
		pDataInner->m_strValue = strValue;
		if(pSttMacroTestParaDatas_External != NULL)
		{
			pSttMacroTestParaDatas_External->SetDataValue(strID,strValue,TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
	}

	return;
}

CExBaseList* QPowerDirItemParaEditWidget::GetMacroTestParaDatas()
{
	if(NULL == m_pCurrMacroTest_External)
		return NULL;

	return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE, "");
}

CExBaseList* QPowerDirItemParaEditWidget::GetInnerMacroTestParaDatas()
{
	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
}

void QPowerDirItemParaEditWidget::DelMacroTestParaDatas()
{

}


void QPowerDirItemParaEditWidget::on_m_cbbTestPhase_currentIndexChanged(int index)
{
	SetFaultPhaseComboBox(index);

	int nUpdateIndex = 0;
	if(index < 9)
	{
		nUpdateIndex = nTestPhaseToUpdate[index];
	}

	CString strIndex;
	strIndex.setNum(nUpdateIndex);
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_TESTPHASE, strIndex);

	return;
}

void QPowerDirItemParaEditWidget::on_m_cbbFaultPhase_currentIndexChanged(const QString &arg1)
{
	if(arg1.isEmpty())
		return;
	if(!bFlag)
		return;

	CString strIndex;
	int nIndex = GetFaultPhaseValue(arg1);
	strIndex.setNum(nIndex);
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTPHASE, strIndex);

	return;
}

void QPowerDirItemParaEditWidget::on_m_editFaultVol_editingFinished()
{
	ui->m_editFaultVol->setText(PowerDirValueCheck(ui->m_editFaultVol->text(), FAULTVOLT_MAX, FAULTVOLT_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTVOLT,ui->m_editFaultVol->text());

	return;
}

void QPowerDirItemParaEditWidget::on_m_editFaultCur_editingFinished()
{
	ui->m_editFaultCur->setText(PowerDirValueCheck(ui->m_editFaultCur->text(), FAULTCUR_MAX, FAULTCUR_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTCURRENT,ui->m_editFaultCur->text());

	return;
}

void QPowerDirItemParaEditWidget::on_m_editFaultTime_editingFinished()
{
    ui->m_editFaultTime->setText(PowerDirValueCheck(ui->m_editFaultTime->text(), FAULTTIME_MAX, FAULTTIME_MIN, 3));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_FAULTTIME,ui->m_editFaultTime->text());

	return;
}

void QPowerDirItemParaEditWidget::on_m_editMTA_editingFinished()
{
//    if(ui->m_editMTA->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
//    {
//        if (((QSettingLineEdit*)ui->m_editMTA)->IsSetting())
//        {
//            return;
//        }
//    }

    if (UpdateParaForLineEdit(STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA, ui->m_editMTA))
    {
        return;
    }

    ui->m_editMTA->setText(PowerDirValueCheck(ui->m_editMTA->text(), MTA_MAX, MTA_MIN, 2));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_MTA,ui->m_editMTA->text());
	emit sig_UpdateVectorWidget();

	return;
}

void QPowerDirItemParaEditWidget::on_m_editActionAreaRange_editingFinished()
{
    ui->m_editActionAreaRange->setText(PowerDirValueCheck(ui->m_editActionAreaRange->text(), MTA_MAX, MTA_MIN, 2));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ACTIONAREARANGE,ui->m_editActionAreaRange->text());
	emit sig_UpdateVectorWidget();

	return;
}

void QPowerDirItemParaEditWidget::on_m_editStepValue_editingFinished()
{
    ui->m_editStepValue->setText(PowerDirValueCheck(ui->m_editStepValue->text(), STEPVALUE_MAX, STEPVALUE_MIN, 2));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_STEPVALUE,ui->m_editStepValue->text());

	return;
}

void QPowerDirItemParaEditWidget::on_m_editAbsErr_editingFinished()
{
    ui->m_editAbsErr->setText(PowerDirValueCheck(ui->m_editAbsErr->text(), STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, 2));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_ABSERR,ui->m_editAbsErr->text());

	return;
}

void QPowerDirItemParaEditWidget::on_m_editRelErr_editingFinished()
{
    ui->m_editRelErr->setText(PowerDirValueCheck(ui->m_editRelErr->text(), STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, 3));
	UpdatePara(STT_MULTI_MACRO_POWERDIR_PARAS_ID_RELERR,ui->m_editRelErr->text());
}

void QPowerDirItemParaEditWidget::SetFaultPhaseComboBox(int index)
{
	ui->m_cbbFaultPhase->clear();
	switch(index)
	{
	case 0:
		{
			ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AN);
			ui->m_cbbFaultPhase->insertItem(1, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AB);
			ui->m_cbbFaultPhase->insertItem(2, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CA);
			ui->m_cbbFaultPhase->insertItem(3, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ABC);
			break;
		}
	case 1:
		{
			ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BN);
			ui->m_cbbFaultPhase->insertItem(1, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AB);
			ui->m_cbbFaultPhase->insertItem(2, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BC);
			ui->m_cbbFaultPhase->insertItem(3, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ABC);
			break;
		}
	case 2:
		{
			ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CN);
			ui->m_cbbFaultPhase->insertItem(1, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BC);
			ui->m_cbbFaultPhase->insertItem(2, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CA);
			ui->m_cbbFaultPhase->insertItem(3, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ABC);
			break;
		}
	case 3:
		{
            ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AB);
			break;
		}
	case 4:
		{
            ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BC);
			break;
		}
	case 5:
		{
            ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CA);
			break;
		}
	case 6:
		{
			ui->m_cbbFaultPhase->insertItem(0, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ABC);
			break;
		}
	case 7:
		{
            ui->m_cbbFaultPhase->insertItem(0, g_sLangTxt_PowerDir_FaultPhase_ZeroCur);
			ui->m_cbbFaultPhase->insertItem(1, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AN);
			ui->m_cbbFaultPhase->insertItem(2, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BN);
			ui->m_cbbFaultPhase->insertItem(3, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CN);
			break;
		}
	case 8:
		{
            ui->m_cbbFaultPhase->insertItem(0, g_sLangTxt_PowerDir_FaultPhase_NegCur);
			ui->m_cbbFaultPhase->insertItem(1, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AN);
			ui->m_cbbFaultPhase->insertItem(2, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BN);
			ui->m_cbbFaultPhase->insertItem(3, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CN);
			ui->m_cbbFaultPhase->insertItem(4, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AB);
			ui->m_cbbFaultPhase->insertItem(5, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BC);
			ui->m_cbbFaultPhase->insertItem(6, STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CA);
			break;
		}
	default:
		break;
	}

	return;
}

int QPowerDirItemParaEditWidget::GetFaultPhaseValue(QString str)
{
	int nValue = 0;
	if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AN)
	{
		nValue = 0;
	}
	else if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BN)
	{
		nValue = 1;
	}
	else if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CN)
	{
		nValue = 2;
	}
	else if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_AB)
	{
		nValue = 3;
	}
	else if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_BC)
	{
		nValue = 4;
	}
	else if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_CA)
	{
		nValue = 5;
	}
	else if(str == STT_MULTI_MACRO_POWERDIR_FAULTPHASE_CBBTEXT_ABC)
	{
		nValue = 6;
	}
    else if(str == g_sLangTxt_PowerDir_FaultPhase_ZeroCur)
	{
		nValue = 7;
	}
    else if(str == g_sLangTxt_PowerDir_FaultPhase_NegCur)
	{
		nValue = 8;
	}

	return nValue;
}

void QPowerDirItemParaEditWidget::SetFaultPhaseComboBoxIndex(int index)
{
	int nTestPhaseIndex = ui->m_cbbTestPhase->currentIndex();
	switch(nTestPhaseIndex)
	{
    case 0: //测试相A相
		{
			switch(index)
			{
			case 0:
                ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相AN
				break;
			case 3:
                ui->m_cbbFaultPhase->setCurrentIndex(1);  //故障相AB
				break;
			case 5:
                ui->m_cbbFaultPhase->setCurrentIndex(2);  //故障相CA
				break;
			case 6:
                ui->m_cbbFaultPhase->setCurrentIndex(3);  //故障相ABC
				break;
			default:
				ui->m_cbbFaultPhase->setCurrentIndex(0);
				break;
			}
			break;
		}
    case 1:  //测试相B相
		{
			switch(index)
			{
			case 1:
                ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相BN
				break;
			case 3:
                ui->m_cbbFaultPhase->setCurrentIndex(1);  //故障相AB
				break;
			case 4:
                ui->m_cbbFaultPhase->setCurrentIndex(2);  //故障相BC
				break;
			case 6:
                ui->m_cbbFaultPhase->setCurrentIndex(3);  //故障相ABC
				break;
			default:
				ui->m_cbbFaultPhase->setCurrentIndex(0);
				break;
			}
			break;
		}
    case 2:  //测试相C相
    {
        switch(index)
        {
        case 2:
            ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相CN
            break;
        case 4:
            ui->m_cbbFaultPhase->setCurrentIndex(1);  //故障相BC
            break;
        case 5:
            ui->m_cbbFaultPhase->setCurrentIndex(2);  //故障相CA
            break;
        case 6:
            ui->m_cbbFaultPhase->setCurrentIndex(3);  //故障相ABC
            break;
        default:
            ui->m_cbbFaultPhase->setCurrentIndex(0);
            break;
        }
        break;
    }
    case 3:  //测试相AB
    {
        ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相AB
        break;
    }
    case 4:  //测试相BC
    {
        ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相BC
        break;
    }
    case 5:  //测试相CA
    {

        ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相CA
        break;
    }
    case 6:  //测试相ABC
    {
        ui->m_cbbFaultPhase->setCurrentIndex(0);  //故障相ABC
        break;
    }
    case 7:  //零序
		{
			switch(index)
			{
			case 7:
                ui->m_cbbFaultPhase->setCurrentIndex(0);  //零序
				break;
			case 0:
                ui->m_cbbFaultPhase->setCurrentIndex(1);  //故障相AN
				break;
			case 1:
                ui->m_cbbFaultPhase->setCurrentIndex(2);  //故障相BN
				break;
			case 2:
                ui->m_cbbFaultPhase->setCurrentIndex(3);  //故障相CN
				break;
			default:
				ui->m_cbbFaultPhase->setCurrentIndex(0);
				break;
			}
			break;
		}
    case 8: //负序
		{
			switch(index)
			{
			case 8:
                ui->m_cbbFaultPhase->setCurrentIndex(0);  //负序
				break;
			case 0:
                ui->m_cbbFaultPhase->setCurrentIndex(1);  //故障相AN
				break;
			case 1:
                ui->m_cbbFaultPhase->setCurrentIndex(2);  //故障相BN
				break;
			case 2:
                ui->m_cbbFaultPhase->setCurrentIndex(3);  //故障相CN
				break;
			case 3:
                ui->m_cbbFaultPhase->setCurrentIndex(4);  //故障相AB
				break;
			case 4:
                ui->m_cbbFaultPhase->setCurrentIndex(5);  //故障相BC
				break;
			case 5:
                ui->m_cbbFaultPhase->setCurrentIndex(6);  //故障相CA
				break;
			default:
				ui->m_cbbFaultPhase->setCurrentIndex(0);
				break;
			}
			break;
		}
	default:
		break;
	}
}
