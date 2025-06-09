#include "DistanceAddMultDlg.h"
#include "ui_DistanceAddMultDlg.h"

QDistanceAddMultDlg::QDistanceAddMultDlg(QWidget *parent) :
    m_pAddMult_UI(new Ui::QDistanceAddMultDlg)
{
    m_pAddMult_UI->setupUi(this);

    m_pDistanceparas = NULL;

	InitUI();
}

QDistanceAddMultDlg::~QDistanceAddMultDlg()
{
    if(m_pDistanceparas != NULL)
    {
        m_pDistanceparas->DeleteAll();
        delete m_pDistanceparas;
        m_pDistanceparas = NULL;
    }
    delete m_pAddMult_UI;
}
void QDistanceAddMultDlg::on_m_btnSave_clicked()
{
	this->done(Accepted);
}

void QDistanceAddMultDlg::on_m_btnClose_clicked()
{
    this->close();
}
void QDistanceAddMultDlg::InitUI()
{
	QButtonGroup *pZoneN1 = new QButtonGroup(this);
	pZoneN1->addButton(m_pAddMult_UI->m_btnDirectionN1_1,0);
	pZoneN1->addButton(m_pAddMult_UI->m_btnDirectionN1_0,1);

	QButtonGroup *pZoneN2 = new QButtonGroup(this);
	pZoneN2->addButton(m_pAddMult_UI->m_btnDirectionN2_1,0);
	pZoneN2->addButton(m_pAddMult_UI->m_btnDirectionN2_0,1);

	QButtonGroup *pZoneN3 = new QButtonGroup(this);
	pZoneN3->addButton(m_pAddMult_UI->m_btnDirectionN3_1,0);
	pZoneN3->addButton(m_pAddMult_UI->m_btnDirectionN3_0,1);

	QButtonGroup *pZoneN4 = new QButtonGroup(this);
	pZoneN4->addButton(m_pAddMult_UI->m_btnDirectionN4_1,0);
	pZoneN4->addButton(m_pAddMult_UI->m_btnDirectionN4_0,1);

	QButtonGroup *pZoneL1 = new QButtonGroup(this);
	pZoneL1->addButton(m_pAddMult_UI->m_btnDirectionL1_1,0);
	pZoneL1->addButton(m_pAddMult_UI->m_btnDirectionL1_0,1);

	QButtonGroup *pZoneL2 = new QButtonGroup(this);
	pZoneL2->addButton(m_pAddMult_UI->m_btnDirectionL2_1,0);
	pZoneL2->addButton(m_pAddMult_UI->m_btnDirectionL2_0,1);

	QButtonGroup *pZoneL3 = new QButtonGroup(this);
	pZoneL3->addButton(m_pAddMult_UI->m_btnDirectionL3_1,0);
	pZoneL3->addButton(m_pAddMult_UI->m_btnDirectionL3_0,1);

	QButtonGroup *pZoneL4 = new QButtonGroup(this);
	pZoneL4->addButton(m_pAddMult_UI->m_btnDirectionL4_1,0);
	pZoneL4->addButton(m_pAddMult_UI->m_btnDirectionL4_0,1);

	m_pAddMult_UI->m_cmbK0Mode->addItem("|K0|,Phi(K0)");
	m_pAddMult_UI->m_cmbK0Mode->addItem("RERL,XEXL");
	m_pAddMult_UI->m_cmbK0Mode->addItem("|Z0/Z1|,Phi(Z0/Z1)");

	m_pAddMult_UI->m_cmb_RSC->addItems(QStringList()<<"Z-Phi"<<"R-X");

	m_pAddMult_UI->m_labTips->setVisible(false);
	InitFont();
}
void QDistanceAddMultDlg::InitFont()
{
	
	CString strFont;
	strFont.Format("font-size:%dpx;",g_pSttGlobalFont->pixelSize());
	m_pAddMult_UI->m_group->setStyleSheet(strFont);
	m_pAddMult_UI->m_group1->setStyleSheet(strFont);
	CString strTmp;
	strFont.Format("QGroupBox{border:2px groove black;border-radius:10px;font-size:%dpx;}QCheckBox{font-size:%dpx;}QLineEdit{font-size:%dpx;}QLabel{font-size:%dpx;}"\
				  ,g_pSttGlobalFont->pixelSize(),g_pSttGlobalFont->pixelSize() ,g_pSttGlobalFont->pixelSize(),g_pSttGlobalFont->pixelSize());
	m_pAddMult_UI->groupBox->setStyleSheet(strFont);
	m_pAddMult_UI->groupBox_2->setStyleSheet(strFont);
	m_pAddMult_UI->groupBox_3->setStyleSheet(strFont);
}
CDataGroup* QDistanceAddMultDlg::OpenDisTanceParasFile(const CString& strParasFile)
{
	if(m_pDistanceparas != NULL)
	{
		m_pDistanceparas->DeleteAll();
		delete m_pDistanceparas;
		m_pDistanceparas = NULL;
	}
	m_pDistanceparas = new CDataGroup();
	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::IncXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys::g_pXmlKeys);
	m_pDistanceparas->OpenXmlFile(stt_ui_GetParasFile(strParasFile), CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::DecXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	return m_pDistanceparas;
}
void QDistanceAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;
	//20240614 luozibing 将界面中的参数保存到链表中
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}

	//20240614 luozibing 将页面数据保存到配置文件中
	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys, 0x1FFFF);
	pParas->SaveXmlFile(stt_ui_GetParasFile(_T("Distance_Paras_Debug.xml")), CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys, 0x1FFFF);
	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
}
void QDistanceAddMultDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if(pData->m_strID == "LNZone1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLNZone1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LNZone2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLNZone2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LNZone3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLNZone3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LNZone4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLNZone4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LLZone1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLLZone1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LLZone2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLLZone2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LLZone3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLLZone3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "LLZone4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkLLZone4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "ZSetingLN_Zone1")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN1->text();
	}
	else if(pData->m_strID == "ZSetingLN_Zone2")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN2->text();
	}
	else if(pData->m_strID == "ZSetingLN_Zone3")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN3->text();
	}
	else if(pData->m_strID == "ZSetingLN_Zone4")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN4->text();
	}
	else if(pData->m_strID == "TSetingLN_Zone1")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN1->text();
	}
	else if(pData->m_strID == "TSetingLN_Zone2")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN2->text();
	}
	else if(pData->m_strID == "TSetingLN_Zone3")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN3->text();
	}
	else if(pData->m_strID == "TSetingLN_Zone4")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN4->text();
	}
	else if(pData->m_strID == "ZSetingLL_Zone1")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL1->text();
	}
	else if(pData->m_strID == "ZSetingLL_Zone2")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL2->text();
	}
	else if(pData->m_strID == "ZSetingLL_Zone3")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL3->text();
	}
	else if(pData->m_strID == "ZSetingLL_Zone4")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL4->text();
	}
	else if(pData->m_strID == "TSetingLL_Zone1")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL1->text();
	}
	else if(pData->m_strID == "TSetingLL_Zone2")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL2->text();
	}
	else if(pData->m_strID == "TSetingLL_Zone3")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL3->text();
	}
	else if(pData->m_strID == "TSetingLL_Zone4")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL4->text();
	}
	else if(pData->m_strID == "Direction_Radio_N1")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN1_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_N2")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN2_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_N3")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN3_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_N4")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN4_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_L1")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL1_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_L2")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL2_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_L3")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL3_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Direction_Radio_L4")
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL4_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAE1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBE1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCE1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABCE1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAE2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBE2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCE2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABCE2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAE3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBE3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCE3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABCE3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAE4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBE4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCE4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABCE4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAB1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBC1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCA1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABC1_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAB2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBC2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCA2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABC2_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAB3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBC3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCA3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABC3_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeAB4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeBC4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeCA4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "FaultTypeABC4_Check")
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Rate_095_Check")
	{
		bvalue = m_pAddMult_UI->m_checkRate_095->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Rate_105_Check")
	{
		bvalue = m_pAddMult_UI->m_checkRate_105->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Rate_070_Check")
	{
		bvalue = m_pAddMult_UI->m_checkRate_070->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == "Rate_100_Check")
	{
		bvalue = m_pAddMult_UI->m_checkRate_100->isChecked();
		pData->m_strValue.setNum(bvalue);
		CDvmData *pData100 = (CDvmData *)m_pDistanceparas->FindByID("Rate_100");
		if(pData100 != NULL)
		{
			pData100->m_strValue = m_pAddMult_UI->m_txtRate_100->text();
			CString strTemp = pData100->m_strValue;
		}
	}
	else if(pData->m_strID == "PreFaultTime")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtPreFaultTime->text();
	}
	else if(pData->m_strID == "FaultTime")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtFaultTime->text();
	}
	else if(pData->m_strID == "FaultAngle")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtFaultAngle->text();
	}
	else if(pData->m_strID == "FaultCurrent")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtFaultCur->text();
	}
	else if(pData->m_strID == "K0Mode")
	{
		pData->m_strValue.setNum(m_pAddMult_UI->m_cmbK0Mode->currentIndex());
	}
	else if(pData->m_strID == "KlKr")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtK0->text();
	}
	else if(pData->m_strID == "AngKx")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtPhi->text();
	}
	else if(pData->m_strID == "ZAngLN_Zone1")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN1->text();
	}
	else if(pData->m_strID == "ZAngLN_Zone2")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN2->text();
	}
	else if(pData->m_strID == "ZAngLN_Zone3")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN3->text();
	}
	else if(pData->m_strID == "ZAngLN_Zone4")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN4->text();
	}
	else if(pData->m_strID == "ZAngLL_Zone1")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN1->text();
	}
	else if(pData->m_strID == "ZAngLL_Zone2")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN2->text();
	}
	else if(pData->m_strID == "ZAngLL_Zone3")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN3->text();
	}
	else if(pData->m_strID == "ZAngLL_Zone4")
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN4->text();
	}

}

void QDistanceAddMultDlg::SetDatas(CDataGroup *pDataset)
{//240612 luozibing 从Distance_Paras.xml中获取数据并显示
	if (pDataset == NULL)
		return;
	m_pDistanceparas = pDataset;
	POS pos = pDataset->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pDataset->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QDistanceAddMultDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == "LNZone1_Check")
	{
		m_pAddMult_UI->m_checkLNZone1->setChecked(pData->m_strValue == "1");
		setLNZone1(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LNZone2_Check")
	{
		m_pAddMult_UI->m_checkLNZone2->setChecked(pData->m_strValue == "1");
		setLNZone2(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LNZone3_Check")
	{
		m_pAddMult_UI->m_checkLNZone3->setChecked(pData->m_strValue == "1");
		setLNZone3(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LNZone4_Check")
	{
		m_pAddMult_UI->m_checkLNZone4->setChecked(pData->m_strValue == "1");
		setLNZone4(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LLZone1_Check")
	{
		m_pAddMult_UI->m_checkLLZone1->setChecked(pData->m_strValue == "1");
		setLLZone1(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LLZone2_Check")
	{
		m_pAddMult_UI->m_checkLLZone2->setChecked(pData->m_strValue == "1");
		setLLZone2(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LLZone3_Check")
	{
		m_pAddMult_UI->m_checkLLZone3->setChecked(pData->m_strValue == "1");
		setLLZone3(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "LLZone4_Check")
	{
		m_pAddMult_UI->m_checkLLZone4->setChecked(pData->m_strValue == "1");
		setLLZone4(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "ZSetingLN_Zone1")
	{
		m_pAddMult_UI->m_txtZSetingLN1->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "ZSetingLN_Zone2")
	{
		m_pAddMult_UI->m_txtZSetingLN2->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "ZSetingLN_Zone3")
	{
		m_pAddMult_UI->m_txtZSetingLN3->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "ZSetingLN_Zone4")
	{
		m_pAddMult_UI->m_txtZSetingLN4->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "TSetingLN_Zone1")
	{
		m_pAddMult_UI->m_txtTSetingLN1->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "TSetingLN_Zone2")
	{
		m_pAddMult_UI->m_txtTSetingLN2->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "TSetingLN_Zone3")
	{
		m_pAddMult_UI->m_txtTSetingLN3->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "TSetingLN_Zone4")
	{
		m_pAddMult_UI->m_txtTSetingLN4->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "ZSetingLL_Zone1")
	{
		m_pAddMult_UI->m_txtZSetingLL1->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "ZSetingLL_Zone2")
	{
		m_pAddMult_UI->m_txtZSetingLL2->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "ZSetingLL_Zone3")
	{
		m_pAddMult_UI->m_txtZSetingLL3->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "ZSetingLL_Zone4")
	{
		m_pAddMult_UI->m_txtZSetingLL4->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == "TSetingLL_Zone1")
	{
		m_pAddMult_UI->m_txtTSetingLL1->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "TSetingLL_Zone2")
	{
		m_pAddMult_UI->m_txtTSetingLL2->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "TSetingLL_Zone3")
	{
		m_pAddMult_UI->m_txtTSetingLL3->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "TSetingLL_Zone4")
	{
		m_pAddMult_UI->m_txtTSetingLL4->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "Direction_Radio_N1")
	{
		m_pAddMult_UI->m_btnDirectionN1_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN1_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_N2")
	{
		m_pAddMult_UI->m_btnDirectionN2_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN2_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_N3")
	{
		m_pAddMult_UI->m_btnDirectionN3_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN3_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_N4")
	{
		m_pAddMult_UI->m_btnDirectionN4_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN4_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_L1")
	{
		m_pAddMult_UI->m_btnDirectionL1_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL1_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_L2")
	{
		m_pAddMult_UI->m_btnDirectionL2_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL2_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_L3")
	{
		m_pAddMult_UI->m_btnDirectionL3_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL3_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "Direction_Radio_L4")
	{
		m_pAddMult_UI->m_btnDirectionL4_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL4_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == "FaultTypeAE1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBE1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCE1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABCE1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAE2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBE2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCE2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABCE2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAE3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBE3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCE3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABCE3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAE4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBE4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCE4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABCE4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAB1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBC1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCA1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABC1_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAB2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBC2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCA2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABC2_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAB3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBC3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCA3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABC3_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeAB4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeA_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeBC4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeB_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeCA4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeC_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "FaultTypeABC4_Check")
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "Rate_095_Check")
	{
		m_pAddMult_UI->m_checkRate_095->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "Rate_105_Check")
	{
		m_pAddMult_UI->m_checkRate_105->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "Rate_070_Check")
	{
		m_pAddMult_UI->m_checkRate_070->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == "Rate_100_Check")
	{
		m_pAddMult_UI->m_checkRate_100->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_txtRate_100->setEnabled(pData->m_strValue == "1");
		CDvmData *pData100 = (CDvmData *)m_pDistanceparas->FindByID("Rate_100");
		if(pData100 != NULL)
		{
			m_pAddMult_UI->m_txtRate_100->setText(CheckDataMinMax(pData100->m_strValue,10,0.01,2));
		}
	}
	else if(pData->m_strID == "PreFaultTime")
	{
		m_pAddMult_UI->m_txtPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "FaultTime")
	{
		m_pAddMult_UI->m_txtFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == "FaultAngle")
	{
		m_pAddMult_UI->m_txtFaultAngle->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "FaultCurrent")
	{
		m_pAddMult_UI->m_txtFaultCur->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	else if(pData->m_strID == "K0Mode")
	{
		m_pAddMult_UI->m_cmbK0Mode->setCurrentIndex(pData->m_strValue.toInt());
		SetModeText(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == "KlKr")
	{
		m_pAddMult_UI->m_txtK0->setText(CheckDataMinMax(pData->m_strValue,999.999,0,2));
	}
	else if(pData->m_strID == "AngKx")
	{
		m_pAddMult_UI->m_txtPhi->setText(CheckDataMinMax(pData->m_strValue,360,0,2));
	}
	else if(pData->m_strID == "ZAngLN_Zone1")
	{
		m_pAddMult_UI->m_txtZAngLN1->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLN_Zone2")
	{
		m_pAddMult_UI->m_txtZAngLN2->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLN_Zone3")
	{
		m_pAddMult_UI->m_txtZAngLN3->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLN_Zone4")
	{
		m_pAddMult_UI->m_txtZAngLN4->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLL_Zone1")
	{
		m_pAddMult_UI->m_txtZAngLL1->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLL_Zone2")
	{
		m_pAddMult_UI->m_txtZAngLL2->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLL_Zone3")
	{
		m_pAddMult_UI->m_txtZAngLL3->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == "ZAngLL_Zone4")
	{
		m_pAddMult_UI->m_txtZAngLL4->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
}
void QDistanceAddMultDlg::SetModeText(int nIndex)
{
	CString strTmp = m_pAddMult_UI->m_cmbK0Mode->itemText(nIndex);
	QStringList words = strTmp.split(",");
	m_pAddMult_UI->m_labMode1->setText(words[0]);
	m_pAddMult_UI->m_labMode2->setText(words[1]);
}

CString QDistanceAddMultDlg::CheckDataMinMax(CString strValue,CString strID,float nMax,float nMin,int nAfterPoint)
{//20240613 luozibing 通过最大值 最小值 小数位数 检查输入框值是否格式正确
	CDvmData *pData = (CDvmData *)m_pDistanceparas->FindByID(strID);
	if(pData == NULL)
		return "";
	if (strValue == "")//输入框值为空时，值不改变
	{
		strValue = pData->m_strValue;
	}
	pData->m_strValue = CheckDataMinMax(strValue,nMax,nMin,nAfterPoint);
	return pData->m_strValue;
}
CString QDistanceAddMultDlg::CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint)
{	
	if (strValue.toFloat()<nMin)
	{
		strValue.setNum(nMin);
	}
	if(strValue.toFloat()>nMax)
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
		{
			strValue += ".";
		}
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
void QDistanceAddMultDlg::on_m_txtZSetingLN1_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLN1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN1->text(),"ZSetingLN_Zone1",999.999,0.001,3));
}
void QDistanceAddMultDlg::on_m_txtZSetingLN2_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLN2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN2->text(),"ZSetingLN_Zone2",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLN3_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLN3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN3->text(),"ZSetingLN_Zone3",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLN4_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLN4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN4->text(),"ZSetingLN_Zone4",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL1_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLL1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL1->text(),"ZSetingLL_Zone1",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL2_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLL2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL2->text(),"ZSetingLL_Zone2",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL3_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLL3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL3->text(),"ZSetingLL_Zone3",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL4_editingFinished()
{
	m_pAddMult_UI->m_txtZSetingLL4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL4->text(),"ZSetingLL_Zone4",999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN1_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN1->text(),"TSetingLN_Zone1",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN2_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN2->text(),"TSetingLN_Zone2",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN3_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN3->text(),"TSetingLN_Zone3",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN4_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN4->text(),"TSetingLN_Zone4",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL1_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL1->text(),"TSetingLL_Zone1",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL2_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL2->text(),"TSetingLL_Zone2",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL3_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL3->text(),"TSetingLL_Zone3",999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL4_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL4->text(),"TSetingLL_Zone4",999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtPreFaultTime_editingFinished()
{
	m_pAddMult_UI->m_txtPreFaultTime->setText(CheckDataMinMax(m_pAddMult_UI->m_txtPreFaultTime->text(),"PreFaultTime",999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtFaultTime_editingFinished()
{
	m_pAddMult_UI->m_txtFaultTime->setText(CheckDataMinMax(m_pAddMult_UI->m_txtFaultTime->text(),"FaultTime",999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtFaultAngle_editingFinished()
{
	m_pAddMult_UI->m_txtFaultAngle->setText(CheckDataMinMax(m_pAddMult_UI->m_txtFaultAngle->text(),"FaultAngle",360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtFaultCur_editingFinished()
{
	m_pAddMult_UI->m_txtFaultCur->setText(CheckDataMinMax(m_pAddMult_UI->m_txtFaultCur->text(),"FaultCurrent",20,0,3));
}
void QDistanceAddMultDlg::on_m_txtRate_100_editingFinished()
{
	m_pAddMult_UI->m_txtRate_100->setText(CheckDataMinMax(m_pAddMult_UI->m_txtRate_100->text(),"Rate_100",10,0.01,2));
}
void QDistanceAddMultDlg::on_m_cmbK0Mode_currentIndexChanged(int index)
{
	SetModeText(index);
}
void QDistanceAddMultDlg::on_m_txtK0_editingFinished()
{
	m_pAddMult_UI->m_txtK0->setText(CheckDataMinMax(m_pAddMult_UI->m_txtK0->text(),"KlKr",999.999,0,2));
}
void QDistanceAddMultDlg::on_m_txtPhi_editingFinished()
{
	m_pAddMult_UI->m_txtPhi->setText(CheckDataMinMax(m_pAddMult_UI->m_txtPhi->text(),"AngKx",360,0,2));
}
void QDistanceAddMultDlg::setLNZone1(bool bState)//20240613 luozibing 勾选对应区段后，才可对其参数进行设置
{
	m_pAddMult_UI->m_txtZSetingLN1->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLN1->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_N1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN1_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN1_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone2(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLN2->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLN2->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_N2->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN2_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN2_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone3(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLN3->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLN3->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_N3->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN3_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN3_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone4(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLN4->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLN4->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_N4->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN4_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN4_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone1(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLL1->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLL1->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL1_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL1_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone2(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLL2->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLL2->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L2->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL2_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL2_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone3(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLL3->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLL3->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L3->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL3_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL3_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone4(bool bState)
{
	m_pAddMult_UI->m_txtZSetingLL4->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLL4->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L4->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL4_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL4_0->setEnabled(bState);
}
bool QDistanceAddMultDlg::CheckSectionState()//20240613 luozibing 最少选择一个故障区段
{
	if (!m_pAddMult_UI->m_checkLNZone1->isChecked()&&\
		!m_pAddMult_UI->m_checkLNZone2->isChecked()&&\
		!m_pAddMult_UI->m_checkLNZone3->isChecked()&&\
		!m_pAddMult_UI->m_checkLNZone4->isChecked()&&\
		!m_pAddMult_UI->m_checkLLZone1->isChecked()&&\
		!m_pAddMult_UI->m_checkLLZone2->isChecked()&&\
		!m_pAddMult_UI->m_checkLLZone3->isChecked()&&\
		!m_pAddMult_UI->m_checkLLZone4->isChecked())
	{
		m_pAddMult_UI->m_checkLNZone1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障区段"));
		return true;
	}
}
void QDistanceAddMultDlg::on_m_checkLNZone1_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	setLNZone1(checked);
}
void QDistanceAddMultDlg::on_m_checkLNZone2_stateChanged(int arg1)
{
	CheckSectionState();
	setLNZone2(arg1==Qt::Checked);
}

void QDistanceAddMultDlg::on_m_checkLNZone3_stateChanged(int arg1)
{
	CheckSectionState();
	setLNZone3(arg1==Qt::Checked);
}

void QDistanceAddMultDlg::on_m_checkLNZone4_stateChanged(int arg1)
{
	CheckSectionState();
	setLNZone4(arg1==Qt::Checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone1_stateChanged(int arg1)
{
	CheckSectionState();
	setLLZone1(arg1==Qt::Checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone2_stateChanged(int arg1)
{
	CheckSectionState();
	setLLZone2(arg1==Qt::Checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone3_stateChanged(int arg1)
{
	CheckSectionState();
	setLLZone3(arg1==Qt::Checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone4_stateChanged(int arg1)
{
	CheckSectionState();
	setLLZone4(arg1==Qt::Checked);
}
void QDistanceAddMultDlg::CheckFaultTypeN1()//最少选择一个故障类别
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_N1->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN2()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_N2->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN3()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_N3->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN4()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_N4->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL1()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L1->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL2()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L2->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL3()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L3->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL4()
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L4->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_L1->setChecked(true);
		SetApplyTips(_T("请至少勾选一个故障类别"));
	}
}
void QDistanceAddMultDlg::on_m_checkFaultTypeA_N1_clicked(bool checked)
{
	CheckFaultTypeN1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_N1_stateChanged(int arg1)
{
	CheckFaultTypeN1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_N1_stateChanged(int arg1)
{
	CheckFaultTypeN1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_N1_stateChanged(int arg1)
{
	CheckFaultTypeN1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_N2_clicked(bool checked)
{
	CheckFaultTypeN2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_N2_stateChanged(int arg1)
{
	CheckFaultTypeN2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_N2_stateChanged(int arg1)
{
	CheckFaultTypeN2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_N2_stateChanged(int arg1)
{
	CheckFaultTypeN2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_N3_clicked(bool checked)
{
	CheckFaultTypeN3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_N3_stateChanged(int arg1)
{
	CheckFaultTypeN3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_N3_stateChanged(int arg1)
{
	CheckFaultTypeN3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_N3_stateChanged(int arg1)
{
	CheckFaultTypeN3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_N4_clicked(bool checked)
{
	CheckFaultTypeN4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_N4_stateChanged(int arg1)
{
	CheckFaultTypeN4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_N4_stateChanged(int arg1)
{
	CheckFaultTypeN4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_N4_stateChanged(int arg1)
{
	CheckFaultTypeN4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_L1_clicked(bool checked)
{
	CheckFaultTypeL1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_L1_stateChanged(int arg1)
{
	CheckFaultTypeL1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_L1_stateChanged(int arg1)
{
	CheckFaultTypeL1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_L1_stateChanged(int arg1)
{
	CheckFaultTypeL1();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_L2_clicked(bool checked)
{
	CheckFaultTypeL2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_L2_stateChanged(int arg1)
{
	CheckFaultTypeL2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_L2_stateChanged(int arg1)
{
	CheckFaultTypeL2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_L2_stateChanged(int arg1)
{
	CheckFaultTypeL2();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_L3_clicked(bool checked)
{
	CheckFaultTypeL3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_L3_stateChanged(int arg1)
{
	CheckFaultTypeL3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_L3_stateChanged(int arg1)
{
	CheckFaultTypeL3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_L3_stateChanged(int arg1)
{
	CheckFaultTypeL3();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeA_L4_clicked(bool checked)
{
	CheckFaultTypeL4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_L4_stateChanged(int arg1)
{
	CheckFaultTypeL4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_L4_stateChanged(int arg1)
{
	CheckFaultTypeL4();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_L4_stateChanged(int arg1)
{
	CheckFaultTypeL4();
}
void QDistanceAddMultDlg::SetApplyTips(CString strTips)
{//20240613 luozibing 页面提示
	m_pAddMult_UI->m_labTips->setText(strTips);
	m_pAddMult_UI->m_labTips->setVisible(true);
	m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}

void QDistanceAddMultDlg::timerEvent(QTimerEvent* ev)
{
	if(ev->timerId() == m_nTipsTime){
		m_pAddMult_UI->m_labTips->setVisible(false);
	}
}
bool QDistanceAddMultDlg::CheckSelMultipleState()//至少勾选一个倍数
{
	if (!m_pAddMult_UI->m_checkRate_105->isChecked()&&\
		!m_pAddMult_UI->m_checkRate_095->isChecked()&&\
		!m_pAddMult_UI->m_checkRate_070->isChecked()&&\
		!m_pAddMult_UI->m_checkRate_100->isChecked())
	{
		m_pAddMult_UI->m_checkRate_105->setChecked(true);
		SetApplyTips(_T("请至少勾选一个倍数"));
		return true;
	}
}
void QDistanceAddMultDlg::on_m_checkRate_105_clicked(bool checked)
{
	CheckSelMultipleState();
}

void QDistanceAddMultDlg::on_m_checkRate_095_stateChanged(int arg1)
{
	CheckSelMultipleState();
}

void QDistanceAddMultDlg::on_m_checkRate_070_stateChanged(int arg1)
{
	CheckSelMultipleState();
}
void QDistanceAddMultDlg::on_m_checkRate_100_stateChanged(int arg1)
{
	m_pAddMult_UI->m_txtRate_100->setEnabled(arg1 == Qt::Checked);
	CheckSelMultipleState();
}
void QDistanceAddMultDlg::on_m_btnResEvaluat_clicked()
{
	POS pos = m_pDistanceparas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)m_pDistanceparas->GetNext(pos);
		GetPageToValue(pData);
	}
	//结果评估
	QDistanceResultEstimateDlg *pResultDlg = new QDistanceResultEstimateDlg(this);
	pResultDlg->SetDatas(m_pDistanceparas);
	if(pResultDlg->exec() == QDialog::Accepted)
	{
		pResultDlg->GetDatas(m_pDistanceparas);
	}
}
void QDistanceAddMultDlg::on_m_cmb_RSC_currentIndexChanged(int index)
{
	if(index == IMPREFTYPE_Z_PHI)//Z
	{
		m_pAddMult_UI->m_labZSeting->setText("整定阻抗(Ω)");
		m_pAddMult_UI->m_labTSeting->setText("整定动作时间(s)");
		m_pAddMult_UI->m_labZAng->setVisible(true);
		m_pAddMult_UI->m_txtZAngLN1->setVisible(true);
		m_pAddMult_UI->m_txtZAngLN2->setVisible(true);
		m_pAddMult_UI->m_txtZAngLN3->setVisible(true);
		m_pAddMult_UI->m_txtZAngLN4->setVisible(true);
		m_pAddMult_UI->m_txtZAngLL1->setVisible(true);
		m_pAddMult_UI->m_txtZAngLL2->setVisible(true);
		m_pAddMult_UI->m_txtZAngLL3->setVisible(true);
		m_pAddMult_UI->m_txtZAngLL4->setVisible(true);
	}
	else
	{
		m_pAddMult_UI->m_labZSeting->setText("整定电阻(Ω)");
		m_pAddMult_UI->m_labTSeting->setText("整定电抗(Ω)");
		m_pAddMult_UI->m_labZAng->setVisible(false);
		m_pAddMult_UI->m_txtZAngLN1->setVisible(false);
		m_pAddMult_UI->m_txtZAngLN2->setVisible(false);
		m_pAddMult_UI->m_txtZAngLN3->setVisible(false);
		m_pAddMult_UI->m_txtZAngLN4->setVisible(false);
		m_pAddMult_UI->m_txtZAngLL1->setVisible(false);
		m_pAddMult_UI->m_txtZAngLL2->setVisible(false);
		m_pAddMult_UI->m_txtZAngLL3->setVisible(false);
		m_pAddMult_UI->m_txtZAngLL4->setVisible(false);
	}
}
void QDistanceAddMultDlg::on_m_txtZAngLN1_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLN1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN1->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLN2_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLN2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN2->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLN3_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLN3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN3->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLN4_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLN4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN4->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLL1_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLL1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL1->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLL2_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLL2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL2->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLL3_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLL3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL3->text(),360,-360,1));
}
void QDistanceAddMultDlg::on_m_txtZAngLL4_editingFinished()
{
	m_pAddMult_UI->m_txtZAngLL4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL4->text(),360,-360,1));
}