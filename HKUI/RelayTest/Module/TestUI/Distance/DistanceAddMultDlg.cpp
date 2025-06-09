#include "DistanceAddMultDlg.h"
#include "ui_DistanceAddMultDlg.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"
QDistanceAddMultDlg::QDistanceAddMultDlg(QWidget *parent) :
    m_pAddMult_UI(new Ui::QDistanceAddMultDlg)
{
    m_pAddMult_UI->setupUi(this);
	InitUI();
	InitLanuage();
}

QDistanceAddMultDlg::~QDistanceAddMultDlg()
{
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

	QButtonGroup *pZoneN5 = new QButtonGroup(this);
	pZoneN5->addButton(m_pAddMult_UI->m_btnDirectionN5_1,0);
	pZoneN5->addButton(m_pAddMult_UI->m_btnDirectionN5_0,1);

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

	QButtonGroup *pZoneL5 = new QButtonGroup(this);
	pZoneL5->addButton(m_pAddMult_UI->m_btnDirectionL5_1,0);
	pZoneL5->addButton(m_pAddMult_UI->m_btnDirectionL5_0,1);


	m_pAddMult_UI->m_cmbK0Mode->addItems(QStringList() << _T("|K0|,Phi(K0)") << _T("RERL,XEXL") << _T("|Z0/Z1|,Phi(Z0/Z1)"));

	m_pAddMult_UI->m_labTips->setVisible(false);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	InitFont();
	HideFaulType_ABC();
	//暂时隐藏所有区段对应控件
	UpdateAddMultPageShow_Zone1(true, false);
	UpdateAddMultPageShow_Zone2(true, false);
	UpdateAddMultPageShow_Zone3(true, false);
	UpdateAddMultPageShow_Zone4(true, false);
	UpdateAddMultPageShow_Zone5(true, false);
	UpdateAddMultPageShow_Zone1(false, false);
	UpdateAddMultPageShow_Zone2(false, false);
	UpdateAddMultPageShow_Zone3(false, false);
	UpdateAddMultPageShow_Zone4(false, false);
	UpdateAddMultPageShow_Zone5(false, false);

	//设置曲线相关参数不允许编辑
	SetAllZTSetingEnabled(false);
	//SetAllZAngEnabled(true);
}
void QDistanceAddMultDlg::InitLanuage()
{
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, g_sLangID_Distance_AddMultZone);//区段
	strtemp.Replace(":", "");
	m_pAddMult_UI->m_labZone->setText(strtemp);

	xlang_GetLangStrByFile(strtemp, g_sLangID_Distance_ZImpValue);//阻抗(Ω)
	strtemp.Replace(":", "");
	m_pAddMult_UI->m_labZSeting->setText(strtemp);

	xlang_SetLangStrToWidget(m_pAddMult_UI->m_labZAng, g_sLangID_Distance_AddMultZAng, XLang_Ctrls_QLabel);//角阻抗(°)
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_labTSeting, g_sLangID_Native_ActionTime, XLang_Ctrls_QLabel);//动作时间(s)

	xlang_GetLangStrByFile(strtemp, g_sLangID_State_FaultType);//故障类型
	strtemp.Replace(":", "");
	m_pAddMult_UI->m_labErrType->setText(strtemp);

	xlang_SetLangStrToWidget(m_pAddMult_UI->m_lab_ErrorDirc, g_sLangID_State_Direction, XLang_Ctrls_QLabel);//方向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_labLN, g_sLangID_Distance_FaultLN, XLang_Ctrls_QLabel);//接地故障
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_labLL, g_sLangID_Distance_FaultLL, XLang_Ctrls_QLabel);//相间故障

	xlang_GetLangStrByFile(strtemp, g_sLangID_Distance_Percent);//百分比(%):
	strtemp.Replace(":", "");
	m_pAddMult_UI->groupBox->setTitle(strtemp);
	xlang_SetLangStrToWidget(m_pAddMult_UI->groupBox_3, g_sLangID_State_ZeroCoeff, XLang_Ctrls_QGroupBox);//零序补偿系数
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_labK0Mode, g_sLangID_Swing_K0CalMode, XLang_Ctrls_QLabel);//表达方式:
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_labFaultCur, g_sLangID_State_ShortI, XLang_Ctrls_QLabel);//短路电流(A):

	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN1_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN2_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN3_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN4_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN5_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL1_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL2_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL3_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL4_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL5_1, g_sLangID_CBOperate_Positive, XLang_Ctrls_QRadioButton);//正向

	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN1_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN2_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN3_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN4_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionN5_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL1_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL2_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL3_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL4_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnDirectionL5_0, g_sLangID_CBOperate_Reverse, XLang_Ctrls_QRadioButton);//反向

	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnSave, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(m_pAddMult_UI->m_btnClose, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;//添加系列
	xlang_GetLangStrByFile(strTile, g_sLangID_Distance_AddMultTile);
	setWindowTitle(strTile);

}
void QDistanceAddMultDlg::InitFont()
{
	setFont(*g_pSttGlobalFont);
	//m_pAddMult_UI->m_labTips->setFont(*g_pSttGlobalFont);
	//m_pAddMult_UI->m_labFaultCur->setFont(*g_pSttGlobalFont);
	//m_pAddMult_UI->m_txtFaultCur->setFont(*g_pSttGlobalFont);
	//m_pAddMult_UI->m_btnResEvaluat->setFont(*g_pSttGlobalFont);
	//m_pAddMult_UI->m_cmbK0Mode->setFont(*g_pSttGlobalFont);

	//int nsize = g_pSttGlobalFont->pixelSize();
	//if(nsize == -1)
	//{
	//	nsize = m_pAddMult_UI->m_txtFaultCur->font().pointSize();
	//	nsize+=4;
	//}
	//CString strFont;
	//strFont.Format("font-size:%dpx;",nsize);
	//m_pAddMult_UI->m_group->setStyleSheet(strFont);
	////m_pAddMult_UI->m_group1->setStyleSheet(strFont);
	//CString strTmp;
	//strFont.Format("QGroupBox{border:2px groove black;border-radius:10px;font:%dpx;}QCheckBox{font:%dpx;}QLineEdit{font:%dpx;}QLabel{font:%dpx;}"\
	//			  ,nsize,nsize ,nsize,nsize);
	//m_pAddMult_UI->groupBox->setStyleSheet(strFont);
	//m_pAddMult_UI->groupBox_3->setStyleSheet(strFont);
}
void QDistanceAddMultDlg::SetPageFont(CFont oPageFont)
{//20240807 luozibing 测试字体使用
	setFont(oPageFont);
	CString strfamily;
	int nsize = oPageFont.pointSize();
	strfamily = oPageFont.family();
	if (nsize == -1)
	{
		nsize = m_pAddMult_UI->m_txtFaultCur->font().pointSize();
		nsize += 4;
	}
	CString strFont,strFont1;
	strFont.Format("font:%dpt ", nsize);
	strFont += strfamily;
	strFont += ";";
	m_pAddMult_UI->m_group->setStyleSheet(strFont);
	m_pAddMult_UI->m_labFaultCur->setStyleSheet(strFont);
	m_pAddMult_UI->m_txtFaultCur->setStyleSheet(strFont);
	m_pAddMult_UI->m_labTips->setStyleSheet(strFont);
	//m_pAddMult_UI->m_btnResEvaluat->setStyleSheet(strFont);//Microsoft YaHei UI
	//m_pAddMult_UI->m_group1->setStyleSheet(strFont);
    strFont1 = QString("QGroupBox{border:2px groove black;border-radius:10px;%1}\
                       QCheckBox{%1}\
                       QLineEdit{%1}\
                       QLabel{%1}\
                       QComboBox{%1}").arg(strFont, strFont, strFont, strFont, strFont);
//    strFont1.Format("QGroupBox{border:2px groove black;border-radius:10px;%s}\
//				   QCheckBox{%s}\
//				   QLineEdit{%s}\
//				   QLabel{%s}\
//				   QComboBox{%s}"
//                   , strFont, strFont, strFont, strFont, strFont);
	m_pAddMult_UI->groupBox->setStyleSheet(strFont);
	m_pAddMult_UI->groupBox_3->setStyleSheet(strFont);
	m_pAddMult_UI->m_cmbK0Mode->setFont(oPageFont);

	CString strF = m_pAddMult_UI->m_cmbK0Mode->font().family();
	int nSize = m_pAddMult_UI->m_cmbK0Mode->font().pointSize();
}
void QDistanceAddMultDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLNZone1->isChecked() || m_pAddMult_UI->m_checkLNZone1->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLNZone2->isChecked() || m_pAddMult_UI->m_checkLNZone2->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLNZone3->isChecked() || m_pAddMult_UI->m_checkLNZone3->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLNZone4->isChecked() || m_pAddMult_UI->m_checkLNZone4->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLNZone5->isChecked() || m_pAddMult_UI->m_checkLNZone5->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLLZone1->isChecked() || m_pAddMult_UI->m_checkLLZone1->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLLZone2->isChecked() || m_pAddMult_UI->m_checkLLZone2->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLLZone3->isChecked() || m_pAddMult_UI->m_checkLLZone3->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLLZone4->isChecked() || m_pAddMult_UI->m_checkLLZone4->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK)
	{
		if (!m_pAddMult_UI->m_checkLLZone5->isChecked() || m_pAddMult_UI->m_checkLLZone5->isHidden())
		{
			pData->m_strValue.setNum(0);
		}
		else
		{
			pData->m_strValue.setNum(1);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN1_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN2_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN3_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN4_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionN5_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL1_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL2_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL3_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL4_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5)
	{
		bvalue = m_pAddMult_UI->m_btnDirectionL5_1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_N5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_N5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_N5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L1->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L2->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L3->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L4->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeA_L5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeB_L5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeC_L5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkFaultTypeABC_L5->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkRate_095->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkRate_105->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkRate_070->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK)
	{
		bvalue = m_pAddMult_UI->m_checkRate_100->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100)
	{
		CString strTmp;
		strTmp.setNum(CString_To_double(m_pAddMult_UI->m_txtRate_100->text()) / 100);
		pData->m_strValue = CheckDataMinMax(strTmp, 0, 0, 3);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtFaultCur->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		pData->m_strValue.setNum(m_pAddMult_UI->m_cmbK0Mode->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtK0->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtPhi->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN1->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN2->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN3->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN4->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLN5->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLL1->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLL2->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLL3->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLL4->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZAngLL5->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN1->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN2->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN3->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN4->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLN5->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL1->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL2->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL3->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL4->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtZSetingLL5->GetText();//20240723 huangliang GetText()替换text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN1->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN2->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN3->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN4->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLN5->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL1->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL2->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL3->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL4->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtTSetingLL5->text();
	}

}
void QDistanceAddMultDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK)
	{
		m_pAddMult_UI->m_checkLNZone1->setChecked(pData->m_strValue == "1");
		setLNZone1(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK)
	{
		m_pAddMult_UI->m_checkLNZone2->setChecked(pData->m_strValue == "1");
		setLNZone2(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK)
	{
		m_pAddMult_UI->m_checkLNZone3->setChecked(pData->m_strValue == "1");
		setLNZone3(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK)
	{
		m_pAddMult_UI->m_checkLNZone4->setChecked(pData->m_strValue == "1");
		setLNZone4(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK)
	{
		m_pAddMult_UI->m_checkLNZone5->setChecked(pData->m_strValue == "1");
		setLNZone5(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK)
	{
		m_pAddMult_UI->m_checkLLZone1->setChecked(pData->m_strValue == "1");
		setLLZone1(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK)
	{
		m_pAddMult_UI->m_checkLLZone2->setChecked(pData->m_strValue == "1");
		setLLZone2(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK)
	{
		m_pAddMult_UI->m_checkLLZone3->setChecked(pData->m_strValue == "1");
		setLLZone3(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK)
	{
		m_pAddMult_UI->m_checkLLZone4->setChecked(pData->m_strValue == "1");
		setLLZone4(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK)
	{
		m_pAddMult_UI->m_checkLLZone5->setChecked(pData->m_strValue == "1");
		setLLZone5(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1)
	{
		m_pAddMult_UI->m_btnDirectionN1_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN1_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2)
	{
		m_pAddMult_UI->m_btnDirectionN2_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN2_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3)
	{
		m_pAddMult_UI->m_btnDirectionN3_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN3_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4)
	{
		m_pAddMult_UI->m_btnDirectionN4_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN4_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5)
	{
		m_pAddMult_UI->m_btnDirectionN5_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionN5_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1)
	{
		m_pAddMult_UI->m_btnDirectionL1_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL1_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2)
	{
		m_pAddMult_UI->m_btnDirectionL2_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL2_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3)
	{
		m_pAddMult_UI->m_btnDirectionL3_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL3_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4)
	{
		m_pAddMult_UI->m_btnDirectionL4_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL4_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5)
	{
		m_pAddMult_UI->m_btnDirectionL5_1->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_btnDirectionL5_0->setChecked(pData->m_strValue != "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_N1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_N2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_N3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_N4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_N5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_N5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_N5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L1->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L2->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L3->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L4->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeA_L5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeB_L5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeC_L5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK)
	{
		m_pAddMult_UI->m_checkFaultTypeABC_L5->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK)
	{
		m_pAddMult_UI->m_checkRate_095->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK)
	{
		m_pAddMult_UI->m_checkRate_105->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK)
	{
		m_pAddMult_UI->m_checkRate_070->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK)
	{
		m_pAddMult_UI->m_checkRate_100->setChecked(pData->m_strValue == "1");
		m_pAddMult_UI->m_txtRate_100->setEnabled(pData->m_strValue == "1");
		CDvmData *pData100 = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100);
		if(pData100 != NULL)
		{
			
			double nrate = CString_To_double(pData100->m_strValue);
			CString strTmp;
			strTmp.setNum(nrate*100);
			m_pAddMult_UI->m_txtRate_100->setText(CheckDataMinMax(strTmp,0,0,1));
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
	{
		m_pAddMult_UI->m_txtFaultCur->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		m_pAddMult_UI->m_cmbK0Mode->setCurrentIndex(CString_To_long(pData->m_strValue));
		SetModeText(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{
		//m_pAddMult_UI->m_txtK0->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pAddMult_UI->m_txtK0->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));//20240723 huangliang 设置对象地址
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		//m_pAddMult_UI->m_txtPhi->setText(CheckDataMinMax(pData->m_strValue,360,0,3));
		m_pAddMult_UI->m_txtPhi->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, 0, 3));//20240723 huangliang 设置对象地址
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1)
	{
		//m_pAddMult_UI->m_txtZAngLN1->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLN1->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN1->text(), STT_MULTI_MACRO_ZONE1, CHAR_DISTANCE_FAULT_TYPE_LN);
		m_pAddMult_UI->m_txtZSetingLN1->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2)
	{
		//m_pAddMult_UI->m_txtZAngLN2->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLN2->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN2->text(), STT_MULTI_MACRO_ZONE2, CHAR_DISTANCE_FAULT_TYPE_LN);
		m_pAddMult_UI->m_txtZSetingLN2->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3)
	{    
		//m_pAddMult_UI->m_txtZAngLN3->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLN3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN3->text(), STT_MULTI_MACRO_ZONE3, CHAR_DISTANCE_FAULT_TYPE_LN);
		m_pAddMult_UI->m_txtZSetingLN3->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4)
	{
		//m_pAddMult_UI->m_txtZAngLN4->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLN4->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN4->text(), STT_MULTI_MACRO_ZONE4, CHAR_DISTANCE_FAULT_TYPE_LN);
		m_pAddMult_UI->m_txtZSetingLN4->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5)
	{
		//m_pAddMult_UI->m_txtZAngLN5->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLN5->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN5->text(), STT_MULTI_MACRO_ZONE5, CHAR_DISTANCE_FAULT_TYPE_LN);
		m_pAddMult_UI->m_txtZSetingLN5->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1)
	{
		//m_pAddMult_UI->m_txtZAngLL1->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLL1->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL1->text(), STT_MULTI_MACRO_ZONE1, CHAR_DISTANCE_FAULT_TYPE_LL);
		m_pAddMult_UI->m_txtZSetingLL1->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2)
	{
		//m_pAddMult_UI->m_txtZAngLL2->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLL2->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL2->text(), STT_MULTI_MACRO_ZONE2, CHAR_DISTANCE_FAULT_TYPE_LL);
		m_pAddMult_UI->m_txtZSetingLL2->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3)
	{
		//m_pAddMult_UI->m_txtZAngLL3->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLL3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL3->text(), STT_MULTI_MACRO_ZONE3, CHAR_DISTANCE_FAULT_TYPE_LL);
		m_pAddMult_UI->m_txtZSetingLL3->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4)
	{
		//m_pAddMult_UI->m_txtZAngLL4->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLL4->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL4->text(), STT_MULTI_MACRO_ZONE4, CHAR_DISTANCE_FAULT_TYPE_LL);
		m_pAddMult_UI->m_txtZSetingLL4->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5)
	{
		//m_pAddMult_UI->m_txtZAngLL5->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
		m_pAddMult_UI->m_txtZAngLL5->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES), STT_MULTI_MACRO_ANGPLACES);//20240723 huangliang 设置对象地址
		CDvmData *pDataZSet = (CDvmData *)m_pDistanceparas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5);
		pDataZSet->m_strValue = GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL5->text(), STT_MULTI_MACRO_ZONE5, CHAR_DISTANCE_FAULT_TYPE_LL);
		m_pAddMult_UI->m_txtZSetingLL5->UpdateObjectText(pDataZSet, CheckDataMinMax(pDataZSet->m_strValue, 999.999, 0.001, 3));
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLN1->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLN1->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLN2->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLN2->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLN3->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLN3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLN4->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLN4->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLN5->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLN5->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLL1->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLL1->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLL2->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLL2->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLL3->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLL3->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLL4->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLL4->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	//else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5)
	//{
	//	//m_pAddMult_UI->m_txtZSetingLL5->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	//	//m_pAddMult_UI->m_txtZSetingLL5->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0.001, 3));//20240723 huangliang 设置对象地址
	//}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1)
	{
		m_pAddMult_UI->m_txtTSetingLN1->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2)
	{
		m_pAddMult_UI->m_txtTSetingLN2->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3)
	{
		m_pAddMult_UI->m_txtTSetingLN3->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4)
	{
		m_pAddMult_UI->m_txtTSetingLN4->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5)
	{
		m_pAddMult_UI->m_txtTSetingLN5->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1)
	{
		m_pAddMult_UI->m_txtTSetingLL1->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2)
	{
		m_pAddMult_UI->m_txtTSetingLL2->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3)
	{
		m_pAddMult_UI->m_txtTSetingLL3->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4)
	{
		m_pAddMult_UI->m_txtTSetingLL4->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5)
	{
		m_pAddMult_UI->m_txtTSetingLL5->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
}
void QDistanceAddMultDlg::SetModeText(int nIndex)
{
	if(m_pDistanceparas == NULL)
		return;
	CString strTmp = m_pAddMult_UI->m_cmbK0Mode->itemText(nIndex);
	QStringList words = strTmp.split(",");
	CString strTemp;

	CString strShow = words[0];
	strShow += ":";
	m_pAddMult_UI->m_labMode1->setText(strShow);
	strShow = words[1];
	strShow += ":";
	m_pAddMult_UI->m_labMode2->setText(strShow);
}

void QDistanceAddMultDlg::on_m_txtZSetingLN1_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLN1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLN1)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLN1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN1->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1,999.999,0.001,3));
}
void QDistanceAddMultDlg::on_m_txtZSetingLN2_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLN2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLN2)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLN2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN2->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2,999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLN3_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLN3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLN3)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLN3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN3->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3,999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLN4_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLN4->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLN4)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLN4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN4->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4,999.999,0.001,3));
}
void QDistanceAddMultDlg::on_m_txtZSetingLN5_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLN5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLN5)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLN5->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLN5->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5,999.999,0.001,3));
}
void QDistanceAddMultDlg::on_m_txtZSetingLL1_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLL1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLL1)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLL1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL1->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1,999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL2_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLL2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLL2)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLL2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL2->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2,999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL3_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLL3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLL3)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLL3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL3->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3,999.999,0.001,3));
}

void QDistanceAddMultDlg::on_m_txtZSetingLL4_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLL4->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLL4)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLL4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL4->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4,999.999,0.001,3));
}
void QDistanceAddMultDlg::on_m_txtZSetingLL5_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZSetingLL5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZSetingLL5)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZSetingLL5->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZSetingLL5->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5,999.999,0.001,3));
}
void QDistanceAddMultDlg::on_m_txtTSetingLN1_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN1->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1,999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN2_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN2->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2,999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN3_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN3->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3,999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLN4_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLN4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN4->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4,999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtTSetingLN5_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtTSetingLN5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtTSetingLN5)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtTSetingLN5->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLN5->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5,999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtTSetingLL1_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL1->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1,999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL2_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL2->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2,999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL3_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL3->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3,999.999,0,3));
}

void QDistanceAddMultDlg::on_m_txtTSetingLL4_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL4->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4,999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtTSetingLL5_editingFinished()
{
	m_pAddMult_UI->m_txtTSetingLL5->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTSetingLL5->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5,999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtFaultCur_editingFinished()
{
	m_pAddMult_UI->m_txtFaultCur->setText(CheckDataMinMax(m_pAddMult_UI->m_txtFaultCur->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT,20,0,3));
}
void QDistanceAddMultDlg::on_m_txtRate_100_editingFinished()
{
	CString strRate = m_pAddMult_UI->m_txtRate_100->text();
	double dPercentage = CString_To_double(strRate);
	double dRate = dPercentage / 100;
	strRate.Format("%f", dRate);
	strRate = CheckDataMinMax(strRate, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100, 0, 0, 3);
	dRate = CString_To_double(strRate);
	dPercentage = dRate * 100;
	strRate.Format("%.1f", dPercentage);
	m_pAddMult_UI->m_txtRate_100->setText(strRate);
}
void QDistanceAddMultDlg::on_m_cmbK0Mode_currentIndexChanged(int index)
{
	SetModeText(index);
}
void QDistanceAddMultDlg::on_m_txtK0_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtK0->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtK0)->IsSetting())
		{
			return;
		}
	}
	int nIndex = m_pAddMult_UI->m_cmbK0Mode->currentIndex();
	m_pAddMult_UI->m_txtK0->setText(CheckDataMinMax(m_pAddMult_UI->m_txtK0->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR,999.999,0,3));
}
void QDistanceAddMultDlg::on_m_txtPhi_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtPhi->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtPhi)->IsSetting())
		{
			return;
		}
	}
	int nIndex = m_pAddMult_UI->m_cmbK0Mode->currentIndex();
	m_pAddMult_UI->m_txtPhi->setText(CheckDataMinMax(m_pAddMult_UI->m_txtPhi->text(),STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX,360,0,3));
}
void QDistanceAddMultDlg::setLNZone1(bool bState)//20240613 luozibing 勾选对应区段后，才可对其参数进行设置
{
	//m_pAddMult_UI->m_txtZSetingLN1->setEnabled(bState);
	//m_pAddMult_UI->m_txtTSetingLN1->setEnabled(bState);
	m_pAddMult_UI->m_txtZAngLN1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN1_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN1_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone2(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLN2->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN2->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLN2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N2->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN2_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN2_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone3(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLN3->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN3->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLN3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N3->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN3_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN3_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone4(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLN4->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN4->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLN4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N4->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN4_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN4_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLNZone5(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLN5->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLN5->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLN5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_N5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_N5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_N5->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN5_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionN5_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone1(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLL1->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL1->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLL1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L1->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL1_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL1_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone2(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLL2->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL2->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLL2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L2->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L2->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL2_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL2_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone3(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLL3->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL3->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLL3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L3->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L3->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL3_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL3_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone4(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLL4->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL4->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLL4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L4->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L4->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL4_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL4_0->setEnabled(bState);
}
void QDistanceAddMultDlg::setLLZone5(bool bState)
{
	/*m_pAddMult_UI->m_txtZSetingLL5->setEnabled(bState);
	m_pAddMult_UI->m_txtTSetingLL5->setEnabled(bState);*/
	m_pAddMult_UI->m_txtZAngLL5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeA_L5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeB_L5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeC_L5->setEnabled(bState);
	m_pAddMult_UI->m_checkFaultTypeABC_L5->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL5_1->setEnabled(bState);
	m_pAddMult_UI->m_btnDirectionL5_0->setEnabled(bState);
}
bool QDistanceAddMultDlg::CheckSectionState(bool bShoeTips)//20240613 luozibing 最少选择一个故障区段
{//检查所有显示check是否被点击
	bool zone1 = (!m_pAddMult_UI->m_checkLNZone1->isChecked() || m_pAddMult_UI->m_checkLNZone1->isHidden());
	bool zone2 = (!m_pAddMult_UI->m_checkLNZone2->isChecked() || m_pAddMult_UI->m_checkLNZone2->isHidden());
	bool zone3 = (!m_pAddMult_UI->m_checkLNZone3->isChecked() || m_pAddMult_UI->m_checkLNZone3->isHidden());
	bool zone4 = (!m_pAddMult_UI->m_checkLNZone4->isChecked() || m_pAddMult_UI->m_checkLNZone4->isHidden());
	bool zone5 = (!m_pAddMult_UI->m_checkLNZone5->isChecked() || m_pAddMult_UI->m_checkLNZone5->isHidden());
	bool zone6 = (!m_pAddMult_UI->m_checkLLZone1->isChecked() || m_pAddMult_UI->m_checkLLZone1->isHidden());
	bool zone7 = (!m_pAddMult_UI->m_checkLLZone2->isChecked() || m_pAddMult_UI->m_checkLLZone2->isHidden());
	bool zone8 = (!m_pAddMult_UI->m_checkLLZone3->isChecked() || m_pAddMult_UI->m_checkLLZone3->isHidden());
	bool zone9 = (!m_pAddMult_UI->m_checkLLZone4->isChecked() || m_pAddMult_UI->m_checkLLZone4->isHidden());
	bool zone0 = (!m_pAddMult_UI->m_checkLLZone5->isChecked() || m_pAddMult_UI->m_checkLLZone5->isHidden());


	if ((!m_pAddMult_UI->m_checkLNZone1->isChecked() || m_pAddMult_UI->m_checkLNZone1->isHidden()) && \
		(!m_pAddMult_UI->m_checkLNZone2->isChecked() || m_pAddMult_UI->m_checkLNZone2->isHidden()) && \
		(!m_pAddMult_UI->m_checkLNZone3->isChecked() || m_pAddMult_UI->m_checkLNZone3->isHidden()) && \
		(!m_pAddMult_UI->m_checkLNZone4->isChecked() || m_pAddMult_UI->m_checkLNZone4->isHidden()) && \
		(!m_pAddMult_UI->m_checkLNZone5->isChecked() || m_pAddMult_UI->m_checkLNZone5->isHidden()) && \
		(!m_pAddMult_UI->m_checkLLZone1->isChecked() || m_pAddMult_UI->m_checkLLZone1->isHidden()) && \
		(!m_pAddMult_UI->m_checkLLZone2->isChecked() || m_pAddMult_UI->m_checkLLZone2->isHidden()) && \
		(!m_pAddMult_UI->m_checkLLZone3->isChecked() || m_pAddMult_UI->m_checkLLZone3->isHidden()) && \
		(!m_pAddMult_UI->m_checkLLZone4->isChecked() || m_pAddMult_UI->m_checkLLZone4->isHidden()) && \
		(!m_pAddMult_UI->m_checkLLZone5->isChecked() || m_pAddMult_UI->m_checkLLZone5->isHidden()))
	{
		bool bChecked = false;
		if (!m_pAddMult_UI->m_checkLNZone1->isHidden())
		{
			m_pAddMult_UI->m_checkLNZone1->setChecked(true);
			setLNZone1(true);
		}
		else if (!m_pAddMult_UI->m_checkLNZone2->isHidden())
		{
			m_pAddMult_UI->m_checkLNZone2->setChecked(true);
			setLNZone2(true);
		}
		else if (!m_pAddMult_UI->m_checkLNZone3->isHidden())
		{
			m_pAddMult_UI->m_checkLNZone3->setChecked(true);
			setLNZone3(true);
		}
		else if (!m_pAddMult_UI->m_checkLNZone4->isHidden())
		{
			m_pAddMult_UI->m_checkLNZone4->setChecked(true);
			setLNZone4(true);
		}
		else if (!m_pAddMult_UI->m_checkLNZone5->isHidden())
		{
			m_pAddMult_UI->m_checkLNZone5->setChecked(true);
			setLNZone5(true);
		}
		else if (!m_pAddMult_UI->m_checkLLZone1->isHidden())
		{
			m_pAddMult_UI->m_checkLLZone1->setChecked(true);
			setLLZone1(true);
		}
		else if (!m_pAddMult_UI->m_checkLLZone2->isHidden())
		{
			m_pAddMult_UI->m_checkLLZone2->setChecked(true);
			setLLZone2(true);
		}
		else if (!m_pAddMult_UI->m_checkLLZone3->isHidden())
		{
			m_pAddMult_UI->m_checkLLZone3->setChecked(true);
			setLLZone3(true);
		}
		else if (!m_pAddMult_UI->m_checkLLZone4->isHidden())
		{
			m_pAddMult_UI->m_checkLLZone4->setChecked(true);
			setLLZone4(true);
		}
		else if (!m_pAddMult_UI->m_checkLLZone5->isHidden())
		{
			m_pAddMult_UI->m_checkLLZone5->setChecked(true);
			setLLZone5(true);
		}
		
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneFault/*_T("请至少勾选一个故障区段")*/);
		}
		return true;
	}

	return false;
}
void QDistanceAddMultDlg::on_m_checkLNZone1_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	setLNZone1(checked);
}
void QDistanceAddMultDlg::on_m_checkLNZone2_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLNZone2(checked);
}

void QDistanceAddMultDlg::on_m_checkLNZone3_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLNZone3(checked);
}

void QDistanceAddMultDlg::on_m_checkLNZone4_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLNZone4(checked);
}
void QDistanceAddMultDlg::on_m_checkLNZone5_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLNZone5(checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone1_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLLZone1(checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone2_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLLZone2(checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone3_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLLZone3(checked);
}

void QDistanceAddMultDlg::on_m_checkLLZone4_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLLZone4(checked);
}
void QDistanceAddMultDlg::on_m_checkLLZone5_clicked(bool checked)
{
	if (CheckSectionState())
	{
		return;
	}
	setLLZone5(checked);
}
void QDistanceAddMultDlg::CheckFaultTypeN1(bool bShoeTips)//最少选择一个故障类别
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N1->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N1->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN2(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N2->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N2->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN3(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N3->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N3->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN4(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N4->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N4->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeN5(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_N5->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_N5->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_N5->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_N5->setChecked(true);
        if (bShoeTips)
        {
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
	}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL1(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L1->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L1->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_L1->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL2(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L2->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L2->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_L2->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL3(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L3->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L3->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_L3->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL4(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L4->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L4->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_L4->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::CheckFaultTypeL5(bool bShoeTips)
{
	if (!m_pAddMult_UI->m_checkFaultTypeA_L5->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeB_L5->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeC_L5->isChecked()&&\
		!m_pAddMult_UI->m_checkFaultTypeABC_L5->isChecked())
	{
		m_pAddMult_UI->m_checkFaultTypeA_L5->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneErrorType/*("请至少勾选一个故障类别"*/);
		}
	}
}
void QDistanceAddMultDlg::MinCheckLeastOne()
{
	QDistanceAddMultBase::MinCheckLeastOne();

	CheckSelMultipleState(false);
	CheckSectionState(false);

	CheckFaultTypeN1(false);
	CheckFaultTypeN2(false);
	CheckFaultTypeN3(false);
	CheckFaultTypeN4(false);
	CheckFaultTypeN5(false);
	CheckFaultTypeL1(false);
	CheckFaultTypeL2(false);
	CheckFaultTypeL3(false);
	CheckFaultTypeL4(false);
	CheckFaultTypeL5(false);

	if (m_pAddMult_UI->m_checkLNZone1->isHidden() && m_pAddMult_UI->m_checkLNZone2->isHidden() && m_pAddMult_UI->m_checkLNZone3->isHidden() && \
		m_pAddMult_UI->m_checkLNZone4->isHidden() && m_pAddMult_UI->m_checkLNZone5->isHidden())
	{//不存在任一LN类型区段
		m_pAddMult_UI->m_labLN->setVisible(false);
		m_pAddMult_UI->m_labLN->setMaximumHeight(0);
		m_pAddMult_UI->m_labLN->setMinimumHeight(0);
		m_pAddMult_UI->line->setVisible(false);
		m_pAddMult_UI->line->setMaximumHeight(0);
	}
	if (m_pAddMult_UI->m_checkLLZone1->isHidden() && m_pAddMult_UI->m_checkLLZone2->isHidden() && m_pAddMult_UI->m_checkLLZone3->isHidden() && \
		m_pAddMult_UI->m_checkLLZone4->isHidden() && m_pAddMult_UI->m_checkLLZone5->isHidden())
	{//不存在任一LL类型区段
		m_pAddMult_UI->m_labLL->setVisible(false);
		m_pAddMult_UI->m_labLL->setMaximumHeight(0);
		m_pAddMult_UI->m_labLL->setMinimumHeight(0);
		m_pAddMult_UI->line->setVisible(false);
		m_pAddMult_UI->line->setMaximumHeight(0);
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
void QDistanceAddMultDlg::on_m_checkFaultTypeA_N5_clicked(bool checked)
{
	CheckFaultTypeN5();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_N5_stateChanged(int arg1)
{
	CheckFaultTypeN5();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_N5_stateChanged(int arg1)
{
	CheckFaultTypeN5();
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
void QDistanceAddMultDlg::on_m_checkFaultTypeA_L5_clicked(bool checked)
{
	CheckFaultTypeL5();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeB_L5_stateChanged(int arg1)
{
	CheckFaultTypeL5();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeC_L5_stateChanged(int arg1)
{
	CheckFaultTypeL5();
}

void QDistanceAddMultDlg::on_m_checkFaultTypeABC_L5_stateChanged(int arg1)
{
	CheckFaultTypeL5();
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
bool QDistanceAddMultDlg::CheckSelMultipleState(bool bShoeTips)//至少勾选一个倍数
{
	if (!m_pAddMult_UI->m_checkRate_105->isChecked()&&\
		!m_pAddMult_UI->m_checkRate_095->isChecked()&&\
		!m_pAddMult_UI->m_checkRate_070->isChecked()&&\
		!m_pAddMult_UI->m_checkRate_100->isChecked())
	{
		m_pAddMult_UI->m_checkRate_105->setChecked(true);
		if (bShoeTips)
		{
			SetApplyTips(g_sLangTxt_MaintainatLeastOneRate/*("请至少勾选一个倍数")*/);
		}
		return true;
	}

	return false;
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
//void QDistanceAddMultDlg::on_m_btnResEvaluat_clicked()
//{
//	POS pos = m_pDistanceparas->GetHeadPosition();
//	while(pos!=NULL)
//	{
//		CDvmData *pData = (CDvmData*)m_pDistanceparas->GetNext(pos);
//		GetPageToValue(pData);
//	}
//	//结果评估
//	QDistanceResultEstimateDlg oResultDlg;
//	oResultDlg.SetDatas(m_pDistanceparas);
//	if(oResultDlg.exec() == QDialog::Accepted)
//	{
//		oResultDlg.GetDatas(m_pDistanceparas);
//	}
//}
void QDistanceAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if (pParas == NULL)
	{
		return;
	}
	//GetResultEstimateDatas(pParas);
	QDistanceAddMultBase::GetDatas(pParas);
}
//20240808 luozibing 获取结果评估设置参数[未使用]
void QDistanceAddMultDlg::GetResultEstimateDatas(CDataGroup *pParas)
{
	POS pos = m_pDistanceparas->GetHeadPosition();
	while (pos)
	{
		CDvmData *pData_New = NULL;
		CDvmData *pData = (CDvmData *)m_pDistanceparas->GetNext(pos);
		if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3 || STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5||\
			pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5 || pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5)
		{
			pData_New = (CDvmData *)pParas->FindByID(pData->m_strID);
			if (pData_New == NULL)
			{
				pParas->AddTail((CDvmData *)pData->Clone());
			}
			else
			{
				pData_New->m_strValue = pData->m_strValue;
			}
		}
	}
}
void QDistanceAddMultDlg::on_m_txtZAngLN1_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLN1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLN1)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLN1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN1->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLN1->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN1->text(), STT_MULTI_MACRO_ZONE1, CHAR_DISTANCE_FAULT_TYPE_LN), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLN2_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLN2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLN2)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLN2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN2->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLN2->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN2->text(), STT_MULTI_MACRO_ZONE2, CHAR_DISTANCE_FAULT_TYPE_LN), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLN3_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLN3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLN3)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLN3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN3->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLN3->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN3->text(), STT_MULTI_MACRO_ZONE3, CHAR_DISTANCE_FAULT_TYPE_LN), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLN4_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLN4->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLN4)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLN4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN4->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLN4->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN4->text(), STT_MULTI_MACRO_ZONE4, CHAR_DISTANCE_FAULT_TYPE_LN), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLN5_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLN5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLN5)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLN5->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLN5->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLN5->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLN5->text(), STT_MULTI_MACRO_ZONE5, CHAR_DISTANCE_FAULT_TYPE_LN), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLL1_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLL1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLL1)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLL1->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL1->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLL1->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL1->text(), STT_MULTI_MACRO_ZONE1, CHAR_DISTANCE_FAULT_TYPE_LL), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLL2_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLL2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLL2)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLL2->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL2->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLL2->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL2->text(), STT_MULTI_MACRO_ZONE2, CHAR_DISTANCE_FAULT_TYPE_LL), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLL3_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLL3->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLL3)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLL3->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL3->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLL3->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL3->text(), STT_MULTI_MACRO_ZONE3, CHAR_DISTANCE_FAULT_TYPE_LL), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLL4_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLL4->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLL4)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLL4->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL4->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLL4->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL4->text(), STT_MULTI_MACRO_ZONE4, CHAR_DISTANCE_FAULT_TYPE_LL), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::on_m_txtZAngLL5_editingFinished()
{
	//20240722 huangliang 判断是否为定值，是定值就不需要处理
	if (m_pAddMult_UI->m_txtZAngLL5->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pAddMult_UI->m_txtZAngLL5)->IsSetting())
		{
			return;
		}
	}
	m_pAddMult_UI->m_txtZAngLL5->setText(CheckDataMinMax(m_pAddMult_UI->m_txtZAngLL5->text(), STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	m_pAddMult_UI->m_txtZSetingLL5->setText(CheckDataMinMax(GetZsetByZAng(m_pAddMult_UI->m_txtZAngLL5->text(), STT_MULTI_MACRO_ZONE5, CHAR_DISTANCE_FAULT_TYPE_LL), \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5, 999.999, 0.001, 3));
}
void QDistanceAddMultDlg::CheckAllPresence()
{
	//20240624 luozibing 检查ID是否存在
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4);
	CheckForPresence(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5);
}
void QDistanceAddMultDlg::HideFaulType_ABC()
{
	m_pAddMult_UI->m_checkFaultTypeABC_L1->setVisible(false);
	m_pAddMult_UI->m_checkFaultTypeABC_L1->setMaximumWidth(0);
	m_pAddMult_UI->m_checkFaultTypeABC_L2->setVisible(false);
	m_pAddMult_UI->m_checkFaultTypeABC_L2->setMaximumWidth(0);
	m_pAddMult_UI->m_checkFaultTypeABC_L3->setVisible(false);
	m_pAddMult_UI->m_checkFaultTypeABC_L3->setMaximumWidth(0);
	m_pAddMult_UI->m_checkFaultTypeABC_L4->setVisible(false);
	m_pAddMult_UI->m_checkFaultTypeABC_L4->setMaximumWidth(0);
	m_pAddMult_UI->m_checkFaultTypeABC_L5->setVisible(false);
	m_pAddMult_UI->m_checkFaultTypeABC_L5->setMaximumWidth(0);
}
void QDistanceAddMultDlg::ShowZonesByCharIndex()
{
}
void QDistanceAddMultDlg::UpdateAddMultPageShow(int nZone, bool bLN)
{
	switch (nZone)
	{
	case STT_MULTI_MACRO_ZONE1:
		UpdateAddMultPageShow_Zone1(bLN, true);
		break;
	case STT_MULTI_MACRO_ZONE2:
		UpdateAddMultPageShow_Zone2(bLN, true);
		break;
	case STT_MULTI_MACRO_ZONE3:
		UpdateAddMultPageShow_Zone3(bLN, true);
		break;
	case STT_MULTI_MACRO_ZONE4:
		UpdateAddMultPageShow_Zone4(bLN, true);
		break;
	case STT_MULTI_MACRO_ZONE5:
		UpdateAddMultPageShow_Zone5(bLN, true);
		break;
	}
}
void QDistanceAddMultDlg::UpdateAddMultPageShow_Zone1(bool bLN,bool bshow)
{
	if (bLN)
	{
		m_pAddMult_UI->m_checkLNZone1->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLN1->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLN1->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLN1->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_N1->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_N1->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_N1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN1_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN1_0->setVisible(bshow);

		if (bshow)
		{
			m_pAddMult_UI->m_checkLNZone1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLNZone1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN1_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN1_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN1_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN1_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLNZone1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLNZone1->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN1->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN1->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLN1->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLN1->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN1->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN1->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N1->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N1->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN1_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN1_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN1_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN1_0->setMinimumHeight(0);
		}
	}
	else
	{
		m_pAddMult_UI->m_checkLLZone1->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLL1->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLL1->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLL1->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_L1->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_L1->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_L1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL1_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL1_0->setVisible(bshow);
		if (bshow)
		{
			m_pAddMult_UI->m_checkLLZone1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLLZone1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL1_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL1_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL1_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL1_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLLZone1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLLZone1->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL1->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL1->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLL1->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLL1->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL1->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL1->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L1->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L1->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L1->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL1_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL1_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL1_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL1_0->setMinimumHeight(0);
		}
	}
}
void QDistanceAddMultDlg::UpdateAddMultPageShow_Zone2(bool bLN, bool bshow)
{
	if (bLN)
	{
		m_pAddMult_UI->m_checkLNZone2->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLN2->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLN2->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLN2->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_N2->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_N2->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_N2->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN2_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN2_0->setVisible(bshow);

		if (bshow)
		{
			m_pAddMult_UI->m_checkLNZone2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLNZone2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN2_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN2_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN2_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN2_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLNZone2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLNZone2->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN2->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN2->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLN2->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLN2->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN2->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN2->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N2->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N2->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N2->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN2_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN2_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN2_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN2_0->setMinimumHeight(0);
		}
	}
	else
	{
		m_pAddMult_UI->m_checkLLZone2->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLL2->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLL2->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLL2->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_L2->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_L2->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_L2->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL2_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL2_0->setVisible(bshow);
		if (bshow)
		{
			m_pAddMult_UI->m_checkLLZone2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLLZone2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L2->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L2->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL2_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL2_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL2_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL2_0->setMinimumHeight(18);
		}
		else
		{
			m_pAddMult_UI->m_checkLLZone2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLLZone2->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL2->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL2->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLL2->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLL2->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL2->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL2->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L2->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L2->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L2->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L2->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL2_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL2_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL2_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL2_0->setMinimumHeight(0);
		}
	}
}
void QDistanceAddMultDlg::UpdateAddMultPageShow_Zone3(bool bLN, bool bshow)
{
	if (bLN)
	{
		m_pAddMult_UI->m_checkLNZone3->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLN3->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLN3->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLN3->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_N3->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_N3->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_N3->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN3_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN3_0->setVisible(bshow);

		if (bshow)
		{
			m_pAddMult_UI->m_checkLNZone3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLNZone3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN3_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN3_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN3_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN3_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLNZone3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLNZone3->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN3->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN3->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLN3->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLN3->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN3->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN3->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N3->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N3->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N3->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN3_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN3_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN3_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN3_0->setMinimumHeight(0);
		}
	}
	else
	{
		m_pAddMult_UI->m_checkLLZone3->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLL3->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLL3->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLL3->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_L3->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_L3->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_L3->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL3_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL3_0->setVisible(bshow);
		if (bshow)
		{
			m_pAddMult_UI->m_checkLLZone3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLLZone3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L3->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L3->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL3_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL3_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL3_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL3_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLLZone3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLLZone3->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL3->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL3->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLL3->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLL3->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL3->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL3->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L3->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L3->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L3->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L3->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL3_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL3_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL3_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL3_0->setMinimumHeight(0);
		}
	}
}
void QDistanceAddMultDlg::UpdateAddMultPageShow_Zone4(bool bLN, bool bshow)
{
	if (bLN)
	{
		m_pAddMult_UI->m_checkLNZone4->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLN4->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLN4->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLN4->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_N4->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_N4->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_N4->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN4_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN4_0->setVisible(bshow);

		if (bshow)
		{
			m_pAddMult_UI->m_checkLNZone4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLNZone4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN4_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN4_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN4_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN4_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLNZone4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLNZone4->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN4->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN4->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLN4->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLN4->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN4->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN4->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N4->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N4->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N4->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN4_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN4_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN4_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN4_0->setMinimumHeight(0);
		}
	}
	else
	{
		m_pAddMult_UI->m_checkLLZone4->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLL4->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLL4->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLL4->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_L4->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_L4->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_L4->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL4_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL4_0->setVisible(bshow);
		if (bshow)
		{
			m_pAddMult_UI->m_checkLLZone4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLLZone4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L4->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L4->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL4_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL4_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL4_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL4_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLLZone4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLLZone4->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL4->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL4->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLL4->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLL4->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL4->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL4->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L4->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L4->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L4->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L4->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL4_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL4_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL4_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL4_0->setMinimumHeight(0);
		}
	}
}
void QDistanceAddMultDlg::UpdateAddMultPageShow_Zone5(bool bLN, bool bshow)
{
	if (bLN)
	{
		m_pAddMult_UI->m_checkLNZone5->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLN5->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLN5->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLN5->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_N5->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_N5->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_N5->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN5_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionN5_0->setVisible(bshow);

		if (bshow)
		{
			m_pAddMult_UI->m_checkLNZone5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLNZone5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLN5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLN5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLN5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_N5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_N5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_N5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN5_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN5_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN5_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionN5_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLNZone5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLNZone5->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN5->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLN5->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLN5->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLN5->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN5->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLN5->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_N5->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_N5->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_N5->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN5_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN5_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionN5_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionN5_0->setMinimumHeight(0);
		}
	}
	else
	{
		m_pAddMult_UI->m_checkLLZone5->setVisible(bshow);
		m_pAddMult_UI->m_txtZSetingLL5->setVisible(bshow);
		m_pAddMult_UI->m_txtZAngLL5->setVisible(bshow);
		m_pAddMult_UI->m_txtTSetingLL5->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeA_L5->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeB_L5->setVisible(bshow);
		m_pAddMult_UI->m_checkFaultTypeC_L5->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL5_1->setVisible(bshow);
		m_pAddMult_UI->m_btnDirectionL5_0->setVisible(bshow);
		if (bshow)
		{
			m_pAddMult_UI->m_checkLLZone5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkLLZone5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZSetingLL5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtZAngLL5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_txtTSetingLL5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeA_L5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeB_L5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L5->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_checkFaultTypeC_L5->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL5_1->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL5_1->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL5_0->setMaximumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
			m_pAddMult_UI->m_btnDirectionL5_0->setMinimumHeight(ADDMULT_PAGESHOWITEM_HEIGHT);
		}
		else
		{
			m_pAddMult_UI->m_checkLLZone5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkLLZone5->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL5->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZSetingLL5->setMinimumHeight(0);
			m_pAddMult_UI->m_txtZAngLL5->setMaximumHeight(0);
			m_pAddMult_UI->m_txtZAngLL5->setMinimumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL5->setMaximumHeight(0);
			m_pAddMult_UI->m_txtTSetingLL5->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeA_L5->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeB_L5->setMinimumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L5->setMaximumHeight(0);
			m_pAddMult_UI->m_checkFaultTypeC_L5->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL5_1->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL5_1->setMinimumHeight(0);
			m_pAddMult_UI->m_btnDirectionL5_0->setMaximumHeight(0);
			m_pAddMult_UI->m_btnDirectionL5_0->setMinimumHeight(0);
		}
	}
}
void QDistanceAddMultDlg::SetAllZTSetingEnabled(bool bEnable)
{//设置所有阻抗定值 时间定值使能
	m_pAddMult_UI->m_txtZSetingLN1->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLN2->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLN3->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLN4->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLN5->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLL1->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLL2->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLL3->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLL4->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZSetingLL5->setEnabled(bEnable);

	m_pAddMult_UI->m_txtTSetingLN1->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLN2->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLN3->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLN4->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLN5->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLL1->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLL2->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLL3->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLL4->setEnabled(bEnable);
	m_pAddMult_UI->m_txtTSetingLL5->setEnabled(bEnable);
}
void QDistanceAddMultDlg::SetAllZAngEnabled(bool bEnable)
{//设置所有角阻抗使能
	m_pAddMult_UI->m_txtZAngLN1->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLN2->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLN3->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLN4->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLN5->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLL1->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLL2->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLL3->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLL4->setEnabled(bEnable);
	m_pAddMult_UI->m_txtZAngLL5->setEnabled(bEnable);
}