#include "SynAddMultDlg.h"
#include "ui_SynAddMultDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "SttMultiMacroSynParasDefine.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "SynResultEstimateDlg.h"
//#include "SynBinarysDlg.h"
//#include "SynCommonParasDlg.h"

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang

QSynAddMultDlg::QSynAddMultDlg(QWidget *parent ): 
    QDialog(parent),
	ui(new Ui::QSynAddMultDlg)
{
    Stt_Global_SettingParent(this);	//20240802 huangliang
	ui->setupUi(this);

	/*CString strText;
	strText = _T("添加系列");*/
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);

	/*OpenXmlFile();
	SetDatas(&m_oDataGroup);*/
	m_pDataGroup = NULL;

	init();
	initConnections();

}
QSynAddMultDlg::~QSynAddMultDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
}

void QSynAddMultDlg::SetParasFont()
{
	ui->gridGroupBox->setFont(*g_pSttGlobalFont);
	ui->m_pAllowFreEdit->setFont(*g_pSttGlobalFont);
	ui->m_pAllowFreLabel->setFont(*g_pSttGlobalFont);
	ui->m_pAllowPressureEdit->setFont(*g_pSttGlobalFont);
	ui->m_pAllowPressureLabel->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFEdit->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFEdit_2->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFEdit_3->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFEdit_4->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFEdit_5->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFEdit_6->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFLabel->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFLabel_2->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFLabel_3->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFLabel_4->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFLabel_5->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingFLabel_6->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVEdit->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVEdit_2->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVEdit_3->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVEdit_4->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVEdit_5->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVEdit_6->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVLabel_2->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVLabel_3->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVLabel_4->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVLabel_5->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVLabel_6->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingLabel->setFont(*g_pSttGlobalFont);
	ui->m_pDescalingVLabel->setFont(*g_pSttGlobalFont);
	ui->m_pFreChangeStepEdit->setFont(*g_pSttGlobalFont);
	ui->m_pFreChangeStepLabel->setFont(*g_pSttGlobalFont);
	ui->m_pFreEdit->setFont(*g_pSttGlobalFont);
	ui->m_pFreLabel->setFont(*g_pSttGlobalFont);
	ui->m_pLeadAEdit->setFont(*g_pSttGlobalFont);
	ui->m_pLeadALabel->setFont(*g_pSttGlobalFont);
	ui->m_pLeadTLabel->setFont(*g_pSttGlobalFont);
	ui->m_pLeadTEdit->setFont(*g_pSttGlobalFont);
	ui->m_pPressureEdit->setFont(*g_pSttGlobalFont);
	ui->m_pPressureLabel->setFont(*g_pSttGlobalFont);
	ui->m_pSetValueLabel->setFont(*g_pSttGlobalFont);
	ui->m_pTestItemsLabel->setFont(*g_pSttGlobalFont);
	ui->m_pVolChangeStepEdit->setFont(*g_pSttGlobalFont);
	ui->m_pVolChangeStepLabel->setFont(*g_pSttGlobalFont);
	ui->m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	ui->m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	
}


void QSynAddMultDlg::OpenXmlFile()
{
	CString strPath = stt_ui_GetParasFile("Syn_Paras.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pDataGroup->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QSynAddMultDlg::SaveSynFile(CDataGroup *pParas)
{
	CString strPath = stt_ui_GetParasFile("Syn_Paras_Debug.xml");
	pParas->SaveXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void QSynAddMultDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_VolBordValue_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FreqBordValue_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_Ut_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_Ft_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LAngle);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_LTime);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UT);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_Ft);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART0);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART0);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART1);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART1);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGSTART2);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_FGSTART2);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGSTART3);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_FGSTART3);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UGSTART4);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_FGSTART4);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART5);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART5);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGMAGSTEP);
}

void QSynAddMultDlg::CheckForPresence(CString strID)
{
	//20240624 luozibing检查ID对应数据是否存在、不存在则添加
	if(m_pDataGroup == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pDataGroup->FindByID(strID);
	if(pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_SYN_PARAS_ID_DEFAULT;
		m_pDataGroup->AddNewChild(pNew);
	}
}

void QSynAddMultDlg::SetDatas(CDataGroup *pDataset)
{
	if (pDataset == NULL)
		return;
	m_pDataGroup = pDataset;

	CheckAllPresence();

	POS pos = pDataset->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pDataset->GetNext(pos);
		SetValueToPage(pData);
	}

	slot_chb_VolBoundTest_Click();
	slot_chb_FreBoundTest_Click();
	slot_chb_LeadTest_Click();
	slot_chb_SelfAdjustTest_Click();
	slot_chb_PressureTest_Click();
	slot_chb_FreTest_Click();

}
void QSynAddMultDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;
	
	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd)
	{
		//ui->m_pAllowPressureEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pAllowPressureEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd)
	{
		//ui->m_pAllowFreEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pAllowFreEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LAngle)
	{
		//ui->m_pLeadAEdit->setText(CheckDataMinMax(pData->m_strValue,-360,360,1));
		ui->m_pLeadAEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, -360, 360, 1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_LTime)
	{
		//ui->m_pLeadTEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pLeadTEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UT)
	{
		//ui->m_pPressureEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pPressureEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_Ft)
	{
		//ui->m_pFreEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pFreEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_VolBordValue_CHECK)
	{
		ui->m_pVolBoundTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FreqBordValue_CHECK)
	{
		ui->m_pFreBoundTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK)
	{
		ui->m_pLeadTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK)
	{
		ui->m_pSelfAdjustTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_Ut_CHECK)
	{
		ui->m_pPressureTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_Ft_CHECK)
	{
		ui->m_pFreTest_CheckBox->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART0)
	{
		//ui->m_pDescalingVEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingVEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART0)
	{
		//ui->m_pDescalingFEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingFEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART1)
	{
		//ui->m_pDescalingVEdit_2->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingVEdit_2->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART1)
	{
		//ui->m_pDescalingFEdit_2->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingFEdit_2->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGSTART2)
	{
		//ui->m_pDescalingVEdit_3->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingVEdit_3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_FGSTART2)
	{
		//ui->m_pDescalingFEdit_3->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingFEdit_3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGSTART3)
	{
		//ui->m_pDescalingVEdit_4->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingVEdit_4->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_FGSTART3)
	{
		//ui->m_pDescalingFEdit_4->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingFEdit_4->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UGSTART4)
	{
		//ui->m_pDescalingVEdit_5->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingVEdit_5->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_FGSTART4)
	{
		//ui->m_pDescalingFEdit_5->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingFEdit_5->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART5)
	{
		//ui->m_pDescalingVEdit_6->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingVEdit_6->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART5)
	{
		//ui->m_pDescalingFEdit_6->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pDescalingFEdit_6->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP)
	{
		//ui->m_pVolChangeStepEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pVolChangeStepEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGMAGSTEP)
	{
		//ui->m_pFreChangeStepEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
		ui->m_pFreChangeStepEdit->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}	
}


void QSynAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;
	
	CheckAllPresence();
	//20240614 luozibing 将界面中的参数保存到链表中
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}

	SaveSynFile(pParas);

}


void QSynAddMultDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd)
	{
		//pData->m_strValue = ui->m_pAllowPressureEdit->text();
		pData->m_strValue = ui->m_pAllowPressureEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd)
	{
		//pData->m_strValue = ui->m_pAllowFreEdit->text();
		pData->m_strValue = ui->m_pAllowFreEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LAngle)
	{
		//pData->m_strValue = ui->m_pLeadAEdit->text();
		pData->m_strValue = ui->m_pLeadAEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_LTime)
	{
		//pData->m_strValue = ui->m_pLeadTEdit->text();
		pData->m_strValue = ui->m_pLeadTEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UT)
	{
		//pData->m_strValue = ui->m_pPressureEdit->text();
		pData->m_strValue = ui->m_pPressureEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_Ft)
	{
		//pData->m_strValue = ui->m_pFreEdit->text();
		pData->m_strValue = ui->m_pFreEdit->GetText();
	}	
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_VolBordValue_CHECK)
	{
		bvalue = ui->m_pVolBoundTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FreqBordValue_CHECK)
	{
		bvalue = ui->m_pFreBoundTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK)
	{
		bvalue = ui->m_pLeadTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK)
	{
		bvalue = ui->m_pSelfAdjustTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_Ut_CHECK)
	{
		bvalue = ui->m_pPressureTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_Ft_CHECK)
	{
		bvalue = ui->m_pFreTest_CheckBox->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGSTART0)
	{
		//pData->m_strValue = ui->m_pDescalingVEdit->text();
		pData->m_strValue = ui->m_pDescalingVEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGSTART0)
	{
		//pData->m_strValue = ui->m_pDescalingFEdit->text();
		pData->m_strValue = ui->m_pDescalingFEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_UGSTART1)
	{
		//pData->m_strValue = ui->m_pDescalingVEdit_2->text();
		pData->m_strValue = ui->m_pDescalingVEdit_2->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FGSTART1)
	{
		//pData->m_strValue = ui->m_pDescalingFEdit_2->text();
		pData->m_strValue = ui->m_pDescalingFEdit_2->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_UGSTART2)
	{
		//pData->m_strValue = ui->m_pDescalingVEdit_3->text();
		pData->m_strValue = ui->m_pDescalingVEdit_3->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_FGSTART2)
	{
		//pData->m_strValue = ui->m_pDescalingFEdit_3->text();
		pData->m_strValue = ui->m_pDescalingFEdit_3->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_UGSTART3)
	{
		//pData->m_strValue = ui->m_pDescalingVEdit_4->text();
		pData->m_strValue = ui->m_pDescalingVEdit_4->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_FGSTART3)
	{
		//pData->m_strValue = ui->m_pDescalingFEdit_4->text();
		pData->m_strValue = ui->m_pDescalingFEdit_4->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_UGSTART4)
	{
		//pData->m_strValue = ui->m_pDescalingVEdit_5->text();
		pData->m_strValue = ui->m_pDescalingVEdit_5->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_FGSTART4)
	{
		//pData->m_strValue = ui->m_pDescalingFEdit_5->text();
		pData->m_strValue = ui->m_pDescalingFEdit_5->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_UGSTART5)
	{
		//pData->m_strValue = ui->m_pDescalingVEdit_6->text();
		pData->m_strValue = ui->m_pDescalingVEdit_6->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_FGSTART5)
	{
		//pData->m_strValue = ui->m_pDescalingFEdit_6->text();
		pData->m_strValue = ui->m_pDescalingFEdit_6->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_UGMAGSTEP)
	{
		//pData->m_strValue = ui->m_pVolChangeStepEdit->text();
		pData->m_strValue = ui->m_pVolChangeStepEdit->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_FGMAGSTEP)
	{
		//pData->m_strValue = ui->m_pFreChangeStepEdit->text();
		pData->m_strValue = ui->m_pFreChangeStepEdit->GetText();
	}
}

void QSynAddMultDlg::initData()
{
#ifdef _PSX_QT_WINDOWS_
	ui->m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));
	ui->m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));
#else
	ui->m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/check.png"));
	ui->m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif

	slot_chb_TestItemsClicked();

}

void QSynAddMultDlg::init()
{
	initData();
	SetParasFont();
	InitLanuage();
	
} 

void QSynAddMultDlg::initConnections()
{
	connect(ui->m_pAllowPressureEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAllowPressure_editingFinished()));
	connect(ui->m_pAllowFreEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAllowFre_editingFinished()));
	connect(ui->m_pLeadAEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneLeadAnglet_editingFinished()));
	connect(ui->m_pLeadTEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneLeadTime_editingFinished()));
	connect(ui->m_pPressureEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePressure_editingFinished()));
	connect(ui->m_pFreEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFre_editingFinished()));

	connect(ui->m_pDescalingVEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingV_editingFinished()));
	connect(ui->m_pDescalingVEdit_2,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingV2_editingFinished()));
	connect(ui->m_pDescalingVEdit_3,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingV3_editingFinished()));
	connect(ui->m_pDescalingVEdit_4,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingV4_editingFinished()));
	connect(ui->m_pDescalingVEdit_5,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingV5_editingFinished()));
	connect(ui->m_pDescalingVEdit_6,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingV6_editingFinished()));

	connect(ui->m_pDescalingFEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingF_editingFinished()));
	connect(ui->m_pDescalingFEdit_2,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingF2_editingFinished()));
	connect(ui->m_pDescalingFEdit_3,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingF3_editingFinished()));
	connect(ui->m_pDescalingFEdit_4,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingF4_editingFinished()));
	connect(ui->m_pDescalingFEdit_5,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingF5_editingFinished()));
	connect(ui->m_pDescalingFEdit_6,SIGNAL(editingFinished()),this,SLOT(slot_lneDescalingF6_editingFinished()));
	
	connect(ui->m_pVolChangeStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneVolChangeStep_editingFinished()));
	connect(ui->m_pFreChangeStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFreChangeStep_editingFinished()));

	connect(ui->m_pResults_pushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_ResultsClicked()));
	connect(ui->m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_OKClick()));
	connect(ui->m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_CancelClick()));

	connect(ui->m_pVolBoundTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_VolBoundTest_Click()));
	connect(ui->m_pFreBoundTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_FreBoundTest_Click()));
	connect(ui->m_pLeadTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_LeadTest_Click()));
	connect(ui->m_pSelfAdjustTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_SelfAdjustTest_Click()));
	connect(ui->m_pPressureTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_PressureTest_Click()));
	connect(ui->m_pFreTest_CheckBox,SIGNAL(clicked()), this, SLOT(slot_chb_FreTest_Click()));

}

void QSynAddMultDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->m_pTestItemsLabel, g_sLangID_TestItem, XLang_Ctrls_QLabel);//测试项目
	xlang_SetLangStrToWidget(ui->m_pSetValueLabel, g_sLangID_State_SettingValue, XLang_Ctrls_QLabel);//整定值
	xlang_SetLangStrToWidget(ui->m_pDescalingLabel, g_sLangID_LowFreq_GradientPara, XLang_Ctrls_QLabel);//递变参数

	xlang_SetLangStrToWidget(ui->m_pVolBoundTest_CheckBox, g_sLangID_Syn_ActVoltageTest, XLang_Ctrls_QCheckBox);//电压边界值测试
	xlang_SetLangStrToWidget(ui->m_pFreBoundTest_CheckBox, g_sLangID_Syn_ActFreqTest, XLang_Ctrls_QCheckBox);//频率边界值测试
	xlang_SetLangStrToWidget(ui->m_pLeadTest_CheckBox, g_sLangID_Syn_LeadAngTest, XLang_Ctrls_QCheckBox);//导前角及导前时间
	xlang_SetLangStrToWidget(ui->m_pSelfAdjustTest_CheckBox, g_sLangID_Syn_AutoAdjTest, XLang_Ctrls_QCheckBox);//自调整试验
	xlang_SetLangStrToWidget(ui->m_pPressureTest_CheckBox, g_sLangID_Syn_AdjVolTest, XLang_Ctrls_QCheckBox);//调压周期测试
	xlang_SetLangStrToWidget(ui->m_pFreTest_CheckBox, g_sLangID_Syn_AdjFreqTest, XLang_Ctrls_QCheckBox);//调频周期测试

	CString strtemp;
	xlang_GetLangStrByFile(strtemp, g_sLangID_Allow_VolDifference);//允许压差(V)
	strtemp += "(V)";
	ui->m_pAllowPressureLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Allow_FreqDifference);//允许频差(Hz)
	strtemp += "(Hz)";
	ui->m_pAllowFreLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_LeadingAngle);//导前角(°)
	//strtemp += QString::fromLocal8Bit("(°)");
	ui->m_pLeadALabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_LeadingTime);//导前时间(s)
	strtemp += "(s)";
	ui->m_pLeadTLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Vol_ReguPeriod);//调压周期(s)
	strtemp += "(s)";
	ui->m_pPressureLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Freq_ReguPeriod);//调频周期(s)
	strtemp += "(s)";
	ui->m_pFreLabel->setText(strtemp);

	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V)
	strtemp += "(V)";
	ui->m_pDescalingVLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V)
	strtemp += "(V)";
	ui->m_pDescalingVLabel_2->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V)
	strtemp += "(V)";
	ui->m_pDescalingVLabel_3->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V)
	strtemp += "(V)";
	ui->m_pDescalingVLabel_4->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V)
	strtemp += "(V)";
	ui->m_pDescalingVLabel_5->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_Grid_Vol);//待并侧电压(V)
	strtemp += "(V)";
	ui->m_pDescalingVLabel_6->setText(strtemp);

	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_VoltChangeStep);//电压变化步长(V)
	strtemp += "(V)";
	ui->m_pVolChangeStepLabel->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_FreChangeStep);//频率变化步长(Hz)
	strtemp += "(Hz)";
	ui->m_pFreChangeStepLabel->setText(strtemp);

	xlang_SetLangStrToWidget(ui->m_pResults_pushButton, g_sLangID_StateEstimate_ResultEstimate, XLang_Ctrls_QPushButton);//结果评估
	xlang_SetLangStrToWidget(ui->m_pOK_PushButton, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_pCancel_PushButton, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

}


float QSynAddMultDlg::slot_lne_Changed(QLineEdit* pLineEdit)
{
	if (pLineEdit->text().isEmpty())
	{
		pLineEdit->setText("0.000");
	}

	QString strValue = pLineEdit->text();
	if (strValue.right(1).contains("."))
	{
		strValue.append("000");
	}
	float fv = strValue.toFloat();
	fv = setLimit(0,1000.000,fv);
	return fv;
}

void QSynAddMultDlg::slot_lneAllowPressure_editingFinished()
{
	if (ui->m_pAllowPressureEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pAllowPressureEdit)->IsSetting())
		{
			return;
		}
	}

	float fv = slot_lne_Changed(ui->m_pAllowPressureEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pAllowPressureEdit->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneAllowFre_editingFinished()
{
	if (ui->m_pAllowFreEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pAllowFreEdit)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pAllowFreEdit);
	ui->m_pAllowFreEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lnePressure_editingFinished()
{
	if (ui->m_pPressureEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pPressureEdit)->IsSetting())
		{
			return;
		}
	}

	float fv = slot_lne_Changed(ui->m_pPressureEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pPressureEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneFre_editingFinished()
{
	if (ui->m_pFreEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pFreEdit)->IsSetting())
		{
			return;
		}
	}

	float fv = slot_lne_Changed(ui->m_pFreEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pFreEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneDescalingV_editingFinished()
{
	if (ui->m_pDescalingVEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingVEdit)->IsSetting())
		{
			return;
		}
	}

	float fv = slot_lne_Changed(ui->m_pDescalingVEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pDescalingVEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneDescalingV2_editingFinished()
{
	if (ui->m_pDescalingVEdit_2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingVEdit_2)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingVEdit_2);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pDescalingVEdit_2->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneDescalingV3_editingFinished()
{
	if (ui->m_pDescalingVEdit_3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingVEdit_3)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingVEdit_3);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pDescalingVEdit_3->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingV4_editingFinished()
{
	if (ui->m_pDescalingVEdit_4->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingVEdit_4)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingVEdit_4);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pDescalingVEdit_4->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingV5_editingFinished()
{
	if (ui->m_pDescalingVEdit_5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingVEdit_5)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingVEdit_5);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pDescalingVEdit_5->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingV6_editingFinished()
{
	if (ui->m_pDescalingVEdit_6->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingVEdit_6)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingVEdit_6);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pDescalingVEdit_6->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingF_editingFinished()
{
	if (ui->m_pDescalingFEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingFEdit)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingFEdit);
	ui->m_pDescalingFEdit->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingF2_editingFinished()
{
	if (ui->m_pDescalingFEdit_2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingFEdit_2)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingFEdit_2);
	ui->m_pDescalingFEdit_2->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneDescalingF3_editingFinished()
{
	if (ui->m_pDescalingFEdit_3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingFEdit_3)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingFEdit_3);
	ui->m_pDescalingFEdit_3->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingF4_editingFinished()
{
	if (ui->m_pDescalingFEdit_4->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingFEdit_4)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingFEdit_4);
	ui->m_pDescalingFEdit_4->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingF5_editingFinished()
{
	if (ui->m_pDescalingFEdit_5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingFEdit_5)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingFEdit_5);
	ui->m_pDescalingFEdit_5->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneDescalingF6_editingFinished()
{
	if (ui->m_pDescalingFEdit_6->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pDescalingFEdit_6)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pDescalingFEdit_6);
	ui->m_pDescalingFEdit_6->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneLeadAnglet_editingFinished()
{
	if (ui->m_pLeadAEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pLeadAEdit)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pLeadAEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pLeadAEdit->setText(QString::number(fv,'f',3));
}
void QSynAddMultDlg::slot_lneLeadTime_editingFinished()
{
	if (ui->m_pLeadTEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pLeadTEdit)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pLeadTEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pLeadTEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneVolChangeStep_editingFinished()
{
	if (ui->m_pVolChangeStepEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pVolChangeStepEdit)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pVolChangeStepEdit);
	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->m_pVolChangeStepEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultDlg::slot_lneFreChangeStep_editingFinished()
{
	if (ui->m_pFreChangeStepEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pFreChangeStepEdit)->IsSetting())
		{
			return;
		}
	}

	float fv  = slot_lne_Changed(ui->m_pFreChangeStepEdit);
	ui->m_pFreChangeStepEdit->setText(QString::number(fv,'f',3));
}


void QSynAddMultDlg::slot_chb_TestItemsClicked()
{
	if (ui->m_pVolBoundTest_CheckBox->isChecked()||ui->m_pFreBoundTest_CheckBox->isChecked()||
		ui->m_pLeadTest_CheckBox->isChecked()||ui->m_pSelfAdjustTest_CheckBox->isChecked()||
		ui->m_pPressureTest_CheckBox->isChecked()||ui->m_pFreTest_CheckBox->isChecked())
	{
		ui->m_pOK_PushButton->setDisabled(false);
	}
	else
	{
		ui->m_pOK_PushButton->setDisabled(true);
	}
}



void QSynAddMultDlg::slot_chb_VolBoundTest_Click()
{
	if (ui->m_pVolBoundTest_CheckBox->isChecked())
	{
		ui->m_pAllowPressureEdit->setDisabled(false);
		ui->m_pDescalingVEdit->setDisabled(false);
		ui->m_pDescalingFEdit->setDisabled(false);
	}
	else
	{
		ui->m_pAllowPressureEdit->setDisabled(true);
		ui->m_pDescalingVEdit->setDisabled(true);
		ui->m_pDescalingFEdit->setDisabled(true);
	}
	slot_chb_TestItemsClicked();
}

void QSynAddMultDlg::slot_chb_FreBoundTest_Click()
{
	if (ui->m_pFreBoundTest_CheckBox->isChecked())
	{
		ui->m_pAllowFreEdit->setDisabled(false);
		ui->m_pDescalingVEdit_2->setDisabled(false);
		ui->m_pDescalingFEdit_2->setDisabled(false);
	}
	else
	{
		ui->m_pAllowFreEdit->setDisabled(true);
		ui->m_pDescalingVEdit_2->setDisabled(true);
		ui->m_pDescalingFEdit_2->setDisabled(true);
	}
	slot_chb_TestItemsClicked();
}

void QSynAddMultDlg::slot_chb_LeadTest_Click()
{
	if (ui->m_pLeadTest_CheckBox->isChecked())
	{
		ui->m_pLeadAEdit->setDisabled(false);
		ui->m_pDescalingVEdit_3->setDisabled(false);
		ui->m_pDescalingFEdit_3->setDisabled(false);
	}
	else
	{
		ui->m_pLeadAEdit->setDisabled(true);
		ui->m_pDescalingVEdit_3->setDisabled(true);
		ui->m_pDescalingFEdit_3->setDisabled(true);
	}
	slot_chb_TestItemsClicked();
}

void QSynAddMultDlg::slot_chb_SelfAdjustTest_Click()
{
	if (ui->m_pSelfAdjustTest_CheckBox->isChecked())
	{
		ui->m_pLeadTEdit->setDisabled(false);
		ui->m_pDescalingVEdit_4->setDisabled(false);
		ui->m_pDescalingFEdit_4->setDisabled(false);
	}
	else
	{
		ui->m_pLeadTEdit->setDisabled(true);
		ui->m_pDescalingVEdit_4->setDisabled(true);
		ui->m_pDescalingFEdit_4->setDisabled(true);
	}
	slot_chb_TestItemsClicked();
}

void QSynAddMultDlg::slot_chb_PressureTest_Click()
{
	if (ui->m_pPressureTest_CheckBox->isChecked())
	{
		ui->m_pPressureEdit->setDisabled(false);
		ui->m_pDescalingVEdit_5->setDisabled(false);
		ui->m_pDescalingFEdit_5->setDisabled(false);
	}
	else
	{
		ui->m_pPressureEdit->setDisabled(true);
		ui->m_pDescalingVEdit_5->setDisabled(true);
		ui->m_pDescalingFEdit_5->setDisabled(true);
	}
	slot_chb_TestItemsClicked();
}

void QSynAddMultDlg::slot_chb_FreTest_Click()
{
	if (ui->m_pFreTest_CheckBox->isChecked())
	{
		ui->m_pFreEdit->setDisabled(false);
		ui->m_pDescalingVEdit_6->setDisabled(false);
		ui->m_pDescalingFEdit_6->setDisabled(false);
	}
	else
	{
		ui->m_pFreEdit->setDisabled(true);
		ui->m_pDescalingVEdit_6->setDisabled(true);
		ui->m_pDescalingFEdit_6->setDisabled(true);
	}
	slot_chb_TestItemsClicked();
}
void QSynAddMultDlg::slot_pbn_OKClick()
{
	GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
	this->done(Accepted);
}

void QSynAddMultDlg::slot_pbn_CancelClick()
{
	this->close();
}
//void QSynAddMultDlg::slot_pbn_BinaryConfigClicked()
//{
//	QSynBinarysDlg dlg(&m_oDataGroup,this);
//	dlg.setWindowModality(Qt::WindowModal);
//	dlg.exec();
//}
//
void QSynAddMultDlg::slot_pbn_ResultsClicked()
{
	POS pos = m_pDataGroup->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)m_pDataGroup->GetNext(pos);
		GetPageToValue(pData);
	}

	QSynResultEstimateDlg oResultDlg;
	oResultDlg.SetDatas(m_pDataGroup);
	if(oResultDlg.exec() == QDialog::Accepted)
	{
		oResultDlg.GetDatas(m_pDataGroup);
	}

}
