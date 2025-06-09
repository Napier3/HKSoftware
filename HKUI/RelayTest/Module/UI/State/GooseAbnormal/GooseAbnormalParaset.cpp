#include "GooseAbnormalParaset.h"
#include <QMessageBox>
#include <QRegExp>
#include "SttMacroParaEditViewGooseAbnormal.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

//2023/10/26 wjs
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyBoard/SoftKeyBoard.h"
#endif

QGooseAbnormalParaSet::QGooseAbnormalParaSet(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pAbnormalGOOSE = NULL;
	m_pCurrStatePara = NULL;
	init();

	initConnect();
    InitLanguage();

	setFont(*g_pSttGlobalFont);
	SetGooseAbnormalFont();
}

QGooseAbnormalParaSet::~QGooseAbnormalParaSet()
{
	
}

void QGooseAbnormalParaSet::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.label_5, g_sLangTxt_State_ChGroup, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.groupBox, g_sLangTxt_Native_GOOSEOrigMsg, XLang_Ctrls_QGroupBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_YMAC, g_sLangTxt_Native_SrcMAC, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_MMAC, g_sLangTxt_Native_DestMAC, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_SetVerion, g_sLangTxt_IEC_ConfigVersion, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_WT, g_sLangTxt_Native_delegate, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_Net, g_sLangTxt_Native_networkId, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.label_3, g_sLangTxt_IEC_VlanPri, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.label_4, g_sLangTxt_IEC_TimeQuality, XLang_Ctrls_QLabel);
}

void QGooseAbnormalParaSet::setData(tmt_StatePara *pStatePara, tmt_StateParas *pStateParas)
{
	if(pStatePara)
	{
		m_pAbnormalGOOSE = &(pStatePara->m_oAbnormalGOOSE);

		m_pCurrStatePara = pStatePara;
		m_pStateParas = pStateParas;
		initData();
	}
}

void QGooseAbnormalParaSet::setName(QString strName)
{
	//ui.lne_StateName->setText(strName);
}

void QGooseAbnormalParaSet::setStateTime(float fvalue)
{
	//ui.lne_StateTime->setText(QString::number(fvalue, 'f', 3));
}

void QGooseAbnormalParaSet::init()
{
// 	ui.label_2->setVisible(true);
// 	ui.lne_StateTime->setVisible(true);
	
	/*ui.label_5->setVisible(false);
	ui.comboBox_GroupIndex->setVisible(false);*/

	ui.lne_APPID->setEnabled(FALSE);

	m_strList<<tr("FALSE")<<tr("TRUE");
	ui.cb_WT->addItems(m_strList);
	ui.cb_Test->addItems(m_strList);

	QFont font = ui.lne_APPID->font();
	ui.cb_WT->setFont(font);
	ui.cb_Test->setFont(font);
	ui.comboBox_GroupIndex->setFont(font);

	//cl20230830默认勾选√
	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QCheckBox::indicator:checked {image: url(:/ctrls/images/checked.png);} QCheckBox::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	ui.ck_YMAC->setStyleSheet(strStyleSheet);
	ui.ck_MMAC->setStyleSheet(strStyleSheet);
	ui.ck_GcRef->setStyleSheet(strStyleSheet);
	ui.ck_GoID->setStyleSheet(strStyleSheet);
	ui.ck_DataSet->setStyleSheet(strStyleSheet);
	ui.ck_SetVerion->setStyleSheet(strStyleSheet);
	ui.ck_St->setStyleSheet(strStyleSheet);
	ui.ck_Sq->setStyleSheet(strStyleSheet);
	ui.ck_TTL->setStyleSheet(strStyleSheet);
	ui.ck_APPID->setStyleSheet(strStyleSheet);
	ui.ck_WT->setStyleSheet(strStyleSheet);
	ui.ck_Test->setStyleSheet(strStyleSheet);
	ui.ck_Vlan->setStyleSheet(strStyleSheet);
	ui.ck_Net->setStyleSheet(strStyleSheet);

	ui.comboBox_GroupIndex->setFixedWidth_All(150,150);
}

void QGooseAbnormalParaSet::SetGooseAbnormalFont()
{
	ui.label_5->setFont(*g_pSttGlobalFont);
	ui.comboBox_GroupIndex->setFont(*g_pSttGlobalFont);
	ui.ck_YMAC->setFont(*g_pSttGlobalFont);
	ui.lne_YMAC->setFont(*g_pSttGlobalFont);
	ui.ck_TTL->setFont(*g_pSttGlobalFont);
	ui.lne_TTL->setFont(*g_pSttGlobalFont);
	ui.ck_MMAC->setFont(*g_pSttGlobalFont);
	ui.lne_MMAC->setFont(*g_pSttGlobalFont);
	ui.ck_APPID->setFont(*g_pSttGlobalFont);
	ui.lne_APPID->setFont(*g_pSttGlobalFont);
	ui.ck_GcRef->setFont(*g_pSttGlobalFont);
	ui.lne_GcRef->setFont(*g_pSttGlobalFont);
	ui.ck_WT->setFont(*g_pSttGlobalFont);
	ui.cb_WT->setFont(*g_pSttGlobalFont);
	ui.ck_GoID->setFont(*g_pSttGlobalFont);
	ui.lne_GoID->setFont(*g_pSttGlobalFont);
	ui.ck_Test->setFont(*g_pSttGlobalFont);
	ui.cb_Test->setFont(*g_pSttGlobalFont);
	ui.ck_DataSet->setFont(*g_pSttGlobalFont);
	ui.lne_DataSet->setFont(*g_pSttGlobalFont);
	ui.ck_Vlan->setFont(*g_pSttGlobalFont);
	ui.lne_Vlan->setFont(*g_pSttGlobalFont);
	ui.ck_SetVerion->setFont(*g_pSttGlobalFont);
	ui.lne_SetVerion->setFont(*g_pSttGlobalFont);
	ui.ck_Net->setFont(*g_pSttGlobalFont);
	ui.lne_Net->setFont(*g_pSttGlobalFont);
	ui.ck_St->setFont(*g_pSttGlobalFont);
	ui.lne_St->setFont(*g_pSttGlobalFont);
	ui.label_3->setFont(*g_pSttGlobalFont);
	ui.lne_VlanPriority->setFont(*g_pSttGlobalFont);
	ui.ck_Sq->setFont(*g_pSttGlobalFont);
	ui.lne_Sq->setFont(*g_pSttGlobalFont);
	ui.label_4->setFont(*g_pSttGlobalFont);
	ui.lne_TimeQuality->setFont(*g_pSttGlobalFont);
	ui.label_6->setFont(*g_pSttGlobalFont);
	ui.label_7->setFont(*g_pSttGlobalFont);
	ui.label_8->setFont(*g_pSttGlobalFont);
	ui.label_9->setFont(*g_pSttGlobalFont);
}

void QGooseAbnormalParaSet::initConnect()
{
	connect(ui.ck_YMAC,SIGNAL(clicked(bool)),this,SLOT(slot_ckYMAC_clicked(bool)));
	connect(ui.ck_MMAC,SIGNAL(clicked(bool)),this,SLOT(slot_ckMMAC_clicked(bool)));
	connect(ui.ck_GcRef,SIGNAL(clicked(bool)),this,SLOT(slot_ckGcRef_clicked(bool)));
	connect(ui.ck_GoID,SIGNAL(clicked(bool)),this,SLOT(slot_ckGoID_clicked(bool)));
	connect(ui.ck_DataSet,SIGNAL(clicked(bool)),this,SLOT(slot_ckDataSet_clicked(bool)));
	connect(ui.ck_SetVerion,SIGNAL(clicked(bool)),this,SLOT(slot_ckSetVerion_clicked(bool)));
	connect(ui.ck_St,SIGNAL(clicked(bool)),this,SLOT(slot_ckSt_clicked(bool)));
	connect(ui.ck_Sq,SIGNAL(clicked(bool)),this,SLOT(slot_ckSq_clicked(bool)));
	connect(ui.ck_TTL,SIGNAL(clicked(bool)),this,SLOT(slot_ckTTl_clicked(bool)));
	connect(ui.ck_APPID,SIGNAL(clicked(bool)),this,SLOT(slot_ckAPPID_clicked(bool)));
	connect(ui.ck_WT,SIGNAL(clicked(bool)),this,SLOT(slot_ckWT_clicked(bool)));
	connect(ui.ck_Test,SIGNAL(clicked(bool)),this,SLOT(slot_ckTest_clicked(bool)));
	connect(ui.ck_Vlan,SIGNAL(clicked(bool)),this,SLOT(slot_ckVlan_clicked(bool)));
	connect(ui.ck_Net,SIGNAL(clicked(bool)),this,SLOT(slot_ckNet_clicked(bool)));
	
	connect(ui.cb_WT,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cbWT_currentIndexChanged(int)));
	connect(ui.cb_Test,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cbTest_currentIndexChanged(int)));

#ifdef _PSX_QT_LINUX_

	connect(ui.lne_YMAC,SIGNAL(clicked()),this,SLOT(slot_lneYMAC_editingFinished()));
	connect(ui.lne_MMAC,SIGNAL(clicked()),this,SLOT(slot_lneMMAC_editingFinished()));
	connect(ui.lne_GcRef,SIGNAL(clicked()),this,SLOT(slot_lneGcRef_editingFinished()));
	connect(ui.lne_GoID,SIGNAL(clicked()),this,SLOT(slot_lneGoID_editingFinished()));
	connect(ui.lne_DataSet,SIGNAL(clicked()),this,SLOT(slot_lneDataSet_editingFinished()));
	connect(ui.lne_APPID,SIGNAL(clicked()),this,SLOT(slot_lneAPPID_editingFinished()));
	connect(ui.lne_Vlan,SIGNAL(clicked()),this,SLOT(slot_lneVlan_editingFinished()));
	connect(ui.lne_Net,SIGNAL(clicked()),this,SLOT(slot_lneNet_editingFinished()));
	connect(ui.lne_TimeQuality,SIGNAL(clicked()),this,SLOT(slot_lneTimeQuality_editingFinished()));
#endif

	connect(ui.lne_YMAC,SIGNAL(editingFinished()),this,SLOT(slot_lneYMAC_clickedKeyBoard()));
	connect(ui.lne_MMAC,SIGNAL(editingFinished()),this,SLOT(slot_lneMMAC_clickedKeyBoard()));
	connect(ui.lne_GcRef,SIGNAL(editingFinished()),this,SLOT(slot_lneGcRef_clickedKeyBoard()));
	connect(ui.lne_GoID,SIGNAL(editingFinished()),this,SLOT(slot_lneGoID_clickedKeyBoard()));
	connect(ui.lne_DataSet,SIGNAL(editingFinished()),this,SLOT(slot_lneDataSet_clickedKeyBoard()));

	connect(ui.lne_APPID,SIGNAL(editingFinished()),this,SLOT(slot_lneAPPID_clickedKeyBoard()));
	connect(ui.lne_Vlan,SIGNAL(editingFinished()),this,SLOT(slot_lneVlan_clickedKeyBoard()));
	connect(ui.lne_Net,SIGNAL(editingFinished()),this,SLOT(slot_lneNet_clickedKeyBoard()));
	connect(ui.lne_TimeQuality,SIGNAL(editingFinished()),this,SLOT(slot_lneTimeQuality_clickedKeyBoard()));

//已修改
#ifdef _PSX_QT_LINUX_
	//connect(ui.lne_StateTime,SIGNAL(clicked()),this,SLOT(slot_lneStateTime_editingFinished()));
	connect(ui.lne_SetVerion,SIGNAL(clicked()),this,SLOT(slot_lneSetVerion_editingFinished()));
	connect(ui.lne_St,SIGNAL(clicked()),this,SLOT(slot_lneSt_editingFinished()));
	connect(ui.lne_Sq,SIGNAL(clicked()),this,SLOT(slot_lneSq_editingFinished()));
	connect(ui.lne_TTL,SIGNAL(clicked()),this,SLOT(slot_lneTTl_editingFinished()));
	connect(ui.lne_VlanPriority,SIGNAL(clicked()),this,SLOT(slot_lneVlanPriority_editingFinished()));

#endif

	//connect(ui.lne_StateTime,SIGNAL(editingFinished()),this,SLOT(slot_lneStateTime_clickedKeyBoard()));
	connect(ui.lne_SetVerion,SIGNAL(editingFinished()),this,SLOT(slot_lneSetVerion_clickedKeyBoard()),Qt::UniqueConnection);
	connect(ui.lne_St,SIGNAL(editingFinished()),this,SLOT(slot_lneSt_clickedKeyBoard()));
	connect(ui.lne_Sq,SIGNAL(editingFinished()),this,SLOT(slot_lneSq_clickedKeyBoard()));
	connect(ui.lne_TTL,SIGNAL(editingFinished()),this,SLOT(slot_lneTTl_clickedKeyBoard()));
	connect(ui.lne_VlanPriority,SIGNAL(editingFinished()),this,SLOT(slot_lneVlanPriority_clickedKeyBoard()));



}

void QGooseAbnormalParaSet::initData()
{
	if (m_pAbnormalGOOSE == NULL)
	{
		return;
	}

	CString strTmp;
	strTmp = m_pCurrStatePara->m_strName;
	//ui.lne_StateName->setText(strTmp);
	//ui.lne_StateTime->setText(QString::number(m_pCurrStatePara->m_fTimeState, 'f', 3));

	if ((m_pCurrStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMETRIGGER)||(m_pCurrStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMEBINTRIGGER))
	{
		//ui.lne_StateTime->setDisabled(false);
	}
	else
	{
		//ui.lne_StateTime->setDisabled(true);
	}

	initGooseOrigPkg();

	//QString str;
	////HH:HH:HH:HH:HH:HH;_
	//ui.lne_YMAC->setInputMask("HH-HH-HH-HH-HH-HH;_");
	//ui.ck_YMAC->setChecked(m_pAbnormalGOOSE->m_bSrcMac_Sel);
	//ui.lne_YMAC->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strSrcMac));
	//ui.lne_MMAC->setInputMask("HH-HH-HH-HH-HH-HH;_");
	//ui.ck_MMAC->setChecked(m_pAbnormalGOOSE->m_bDestMac_Sel);
	//ui.lne_MMAC->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strDestMac));
	//ui.ck_GcRef->setChecked(m_pAbnormalGOOSE->m_bGocbRef_Sel);
	//ui.lne_GcRef->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strGocbRef));
	//ui.ck_GoID->setChecked(m_pAbnormalGOOSE->m_bGoID_Sel);
	//ui.lne_GoID->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strGoID));
	//ui.ck_DataSet->setChecked(m_pAbnormalGOOSE->m_bDataSet_Sel);
	//ui.lne_DataSet->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strDataSet));
	//ui.ck_SetVerion->setChecked(m_pAbnormalGOOSE->m_bConfRecvSet_Sel);
	//ui.lne_SetVerion->setText(QString::number(m_pAbnormalGOOSE->m_nConfRecv));
	//ui.ck_St->setChecked(m_pAbnormalGOOSE->m_bStNumSet_Sel);

	//ui.lne_St->setText(QString::number(m_pAbnormalGOOSE->m_nStNum));
	//ui.ck_Sq->setChecked(m_pAbnormalGOOSE->m_bSqNumSet_Sel);
	//ui.lne_Sq->setText(QString::number(m_pAbnormalGOOSE->m_nSqNum));
	//ui.ck_TTL->setChecked(m_pAbnormalGOOSE->m_bTtlSet_Sel);
	//ui.lne_TTL->setText(QString::number(m_pAbnormalGOOSE->m_nTimeAllowToLive));
	//ui.ck_APPID->setChecked(m_pAbnormalGOOSE->m_bAppID_Sel);

	//QRegExp regExp("[a-fA-F0-9]{4}");
	//ui.lne_APPID->setValidator(new QRegExpValidator(regExp, this));
	//strTmp.Format("%04X",m_pAbnormalGOOSE->m_nAppID);
	//ui.lne_APPID->setText(strTmp);

	//ui.ck_WT->setChecked(m_pAbnormalGOOSE->m_bNdsCom_Sel);
	//ui.cb_WT->setCurrentIndex(m_pAbnormalGOOSE->m_nNdsCom);
	//ui.ck_Test->setChecked(m_pAbnormalGOOSE->m_bTestFlag_Sel);
	//ui.cb_Test->setCurrentIndex(m_pAbnormalGOOSE->m_nTestFlag);
	//
	//ui.ck_Vlan->setChecked(m_pAbnormalGOOSE->m_bVlanSet_Sel);

	//ui.lne_Vlan->setValidator(new QRegExpValidator(regExp, this));

	//strTmp.Format("%04X",m_pAbnormalGOOSE->m_nVlanID);
	//ui.lne_Vlan->setText(strTmp);
	//ui.ck_Net->setChecked(m_pAbnormalGOOSE->m_bNetTypeSet_Sel);
	//ui.lne_Net->setValidator(new QRegExpValidator(regExp, this));
	//strTmp.Format("%04X",m_pAbnormalGOOSE->m_nNetType);
	//ui.lne_Net->setText(strTmp);
	//ui.lne_VlanPriority->setText(QString::number(m_pAbnormalGOOSE->m_nVLanPriority));

	//QRegExp regExp2("[a-fA-F0-9]{2}");
	//ui.lne_TimeQuality->setValidator(new QRegExpValidator(regExp2, this));
	//strTmp.Format("%04X",m_pAbnormalGOOSE->m_nTimequality);
	//ui.lne_TimeQuality->setText(strTmp);

	initcmb_APPIDbyBlock();

//	ui.lne_GroupNum->setText(QString::number(m_pData->ngroup()));
}

void QGooseAbnormalParaSet::initGooseOrigPkg()
{
	CString strTmp;
	strTmp = m_pCurrStatePara->m_strName;

	QString str;
	//HH:HH:HH:HH:HH:HH;_
	ui.lne_YMAC->setInputMask("HH-HH-HH-HH-HH-HH;_");
	ui.ck_YMAC->setChecked(m_pAbnormalGOOSE->m_bSrcMac_Sel);
	ui.lne_YMAC->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strSrcMac));
	ui.lne_MMAC->setInputMask("HH-HH-HH-HH-HH-HH;_");
	ui.ck_MMAC->setChecked(m_pAbnormalGOOSE->m_bDestMac_Sel);
	ui.lne_MMAC->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strDestMac));
	ui.ck_GcRef->setChecked(m_pAbnormalGOOSE->m_bGocbRef_Sel);
	ui.lne_GcRef->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strGocbRef));
	ui.ck_GoID->setChecked(m_pAbnormalGOOSE->m_bGoID_Sel);
	ui.lne_GoID->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strGoID));
	ui.ck_DataSet->setChecked(m_pAbnormalGOOSE->m_bDataSet_Sel);
	ui.lne_DataSet->setText(QString::fromStdString(m_pAbnormalGOOSE->m_strDataSet));
	ui.ck_SetVerion->setChecked(m_pAbnormalGOOSE->m_bConfRecvSet_Sel);
	ui.lne_SetVerion->setText(QString::number(m_pAbnormalGOOSE->m_nConfRecv));
	ui.ck_St->setChecked(m_pAbnormalGOOSE->m_bStNumSet_Sel);

	ui.lne_St->setText(QString::number(m_pAbnormalGOOSE->m_nStNum));
	ui.ck_Sq->setChecked(m_pAbnormalGOOSE->m_bSqNumSet_Sel);
	ui.lne_Sq->setText(QString::number(m_pAbnormalGOOSE->m_nSqNum));
	ui.ck_TTL->setChecked(m_pAbnormalGOOSE->m_bTtlSet_Sel);
	ui.lne_TTL->setText(QString::number(m_pAbnormalGOOSE->m_nTimeAllowToLive));
	ui.ck_APPID->setChecked(m_pAbnormalGOOSE->m_bAppID_Sel);

	QRegExp regExp("[a-fA-F0-9]{4}");
	ui.lne_APPID->setValidator(new QRegExpValidator(regExp, this));
	strTmp.Format("%04X",m_pAbnormalGOOSE->m_nAppID);
	ui.lne_APPID->setText(strTmp);

	ui.ck_WT->setChecked(m_pAbnormalGOOSE->m_bNdsCom_Sel);
	ui.cb_WT->setCurrentIndex(m_pAbnormalGOOSE->m_nNdsCom);
	ui.ck_Test->setChecked(m_pAbnormalGOOSE->m_bTestFlag_Sel);
	ui.cb_Test->setCurrentIndex(m_pAbnormalGOOSE->m_nTestFlag);

	ui.ck_Vlan->setChecked(m_pAbnormalGOOSE->m_bVlanSet_Sel);

	ui.lne_Vlan->setValidator(new QRegExpValidator(regExp, this));

	strTmp.Format("%04X",m_pAbnormalGOOSE->m_nVlanID);
	ui.lne_Vlan->setText(strTmp);
	ui.ck_Net->setChecked(m_pAbnormalGOOSE->m_bNetTypeSet_Sel);
	ui.lne_Net->setValidator(new QRegExpValidator(regExp, this));
	strTmp.Format("%04X",m_pAbnormalGOOSE->m_nNetType);
	ui.lne_Net->setText(strTmp);
	ui.lne_VlanPriority->setText(QString::number(m_pAbnormalGOOSE->m_nVLanPriority));

	//QRegExp regExp2("[a-fA-F0-9]{2}");
	//ui.lne_TimeQuality->setValidator(new QRegExpValidator(regExp2, this));

	strTmp.Format("%02X",m_pAbnormalGOOSE->m_nTimequality);
	ui.lne_TimeQuality->setText(strTmp);
}

void QGooseAbnormalParaSet::slot_ckYMAC_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bSrcMac_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

//void QGooseAbnormalParaSet::slot_ckYMAC_clickedKeyBoard(  )
//{
//	this->slot_edit_changed(ui.lne_YMAC, TRUE);
//
//}

//void QGooseAbnormalParaSet::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
//{
//	QString str;
//	GetEngWidgetBoard_DigitData(str, this);
//
//	pEditLine->setText(str);
//	pEditLine->SetEditFinished();
//}

void QGooseAbnormalParaSet::slot_lneYMAC_editingFinished()
{
	QString str = ui.lne_YMAC->text();

	GetEngWidgetBoard_DigitData(str, this);

}

void QGooseAbnormalParaSet::slot_lneYMAC_clickedKeyBoard()
{
	QString str = ui.lne_YMAC->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	ui.lne_YMAC->setText(str);

	CString_to_char(str,m_pAbnormalGOOSE->m_strSrcMac);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_ckMMAC_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bDestMac_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneMMAC_clickedKeyBoard()
{
	//	this->slot_edit_changed(ui.lne_MMAC, TRUE);

	QString str = ui.lne_MMAC->text();

	// 	GetEngWidgetBoard_DigitData(str, this);
// 	ui.lne_MMAC->setText(str);

	CString_to_char(str,m_pAbnormalGOOSE->m_strDestMac);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneMMAC_editingFinished()
{
	QString str = ui.lne_MMAC->text();

	GetEngWidgetBoard_DigitData(str, this);

}


void QGooseAbnormalParaSet::slot_ckGcRef_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bGocbRef_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneGcRef_clickedKeyBoard()
{
	/*this->slot_edit_changed(ui.lne_GcRef, TRUE);*/
	QString str = ui.lne_GcRef->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	ui.lne_GcRef->setText(str);

	CString_to_char(str,m_pAbnormalGOOSE->m_strGocbRef);
	g_pGooseTest->m_bTmtParaChanged = TRUE;

}

void QGooseAbnormalParaSet::slot_lneGcRef_editingFinished()
{
	QString str = ui.lne_GcRef->text();

	GetEngWidgetBoard_DigitData(str, this);

}

void QGooseAbnormalParaSet::slot_ckGoID_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bGoID_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneGoID_clickedKeyBoard()
{
// 	this->slot_edit_changed(ui.lne_GoID,TRUE);	
	QString str = ui.lne_GoID->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	ui.lne_GoID->setText(str);

	CString_to_char(str,m_pAbnormalGOOSE->m_strGoID);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneGoID_editingFinished()
{
	QString str = ui.lne_GoID->text();

	GetEngWidgetBoard_DigitData(str, this);
}

void QGooseAbnormalParaSet::slot_ckDataSet_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bDataSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneDataSet_clickedKeyBoard()
{
	// 	this->slot_edit_changed(ui.lne_DataSet,TRUE);
	QString str = ui.lne_DataSet->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	ui.lne_DataSet->setText(str);

	CString_to_char(str,m_pAbnormalGOOSE->m_strDataSet);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneDataSet_editingFinished()
{
	QString str = ui.lne_DataSet->text();

 	GetEngWidgetBoard_DigitData(str, this);

}

void QGooseAbnormalParaSet::slot_ckSetVerion_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bConfRecvSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneSetVerion_clickedKeyBoard()
{
	//this->slot_edit_changed(ui.lne_SetVerion,TRUE);
	CString str = ui.lne_SetVerion->text();

// 	GetWidgetBoard_DigitData(4,str, this);
	//ui.lne_SetVerion->setText(str);

	qulonglong fv = str.toULongLong();
	if (fv<=0)
	{
		fv = 0;
	}
	else if (fv>0xFFFF)
	{
		fv = 0xFFFF;
	}
	m_pAbnormalGOOSE->m_nConfRecv = fv;
	ui.lne_SetVerion->setText(QString::number((uint)fv,10));
	//str.Format("%d",m_pAbnormalGOOSE->m_nConfRecv);
	//ui.lne_SetVerion->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneSetVerion_editingFinished()
{
	CString str = ui.lne_SetVerion->text();

	//2023/10/26 wjs 将使用数字键盘的初始化为数字键盘
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::SetDefaultKeyboard();
#endif
	//GetWidgetBoard_DigitData(4,str,ui.lne_SetVerion, this);
	//ui.lne_SetVerion->setText(str);

// 	qulonglong fv = str.toULongLong();
// 	if (fv<=0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>0xFFFF)
// 	{
// 		fv = 0xFFFF;
// 	}
// 	m_pAbnormalGOOSE->m_nConfRecv = fv;
// 	ui.lne_SetVerion->setText(QString::number((uint)fv,10));
// 	//str.Format("%d",m_pAbnormalGOOSE->m_nConfRecv);
// 	//ui.lne_SetVerion->setText(str);
// 	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_ckSt_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bStNumSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneSt_clickedKeyBoard()
{
	//this->slot_edit_changed(ui.lne_St,TRUE);
	QString str = ui.lne_St->text();

// 	GetWidgetBoard_DigitData(4,str, this);
	//ui.lne_St->setText(str);

	qulonglong fv = str.toULongLong();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>0xFFFF)
	{
		fv = 0xFFFF;
	}

	m_pAbnormalGOOSE->m_nStNum = fv;
	ui.lne_St->setText(QString::number((uint)fv,10));
	g_pGooseTest->m_bTmtParaChanged = TRUE;
	emit sig_NameChanged(true);
}

void QGooseAbnormalParaSet::slot_lneSt_editingFinished()
{
	QString str = ui.lne_St->text();

	//2023/10/26 wjs 将使用数字键盘的初始化为数字键盘
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::SetDefaultKeyboard();
#endif
	//GetWidgetBoard_DigitData(4,str,ui.lne_St, this);
	//ui.lne_St->setText(str);

// 	qulonglong fv = str.toULongLong();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>0xFFFF)
// 	{
// 		fv = 0xFFFF;
// 	}
// 
// 	m_pAbnormalGOOSE->m_nStNum = fv;
// 	ui.lne_St->setText(QString::number((uint)fv,10));
// 	g_pGooseTest->m_bTmtParaChanged = TRUE;
// 	emit sig_NameChanged(true);
}

void QGooseAbnormalParaSet::slot_ckSq_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bSqNumSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneSq_clickedKeyBoard()
{
	//this->slot_edit_changed(ui.lne_Sq,TRUE);
	QString str = ui.lne_Sq->text();

// 	GetWidgetBoard_DigitData(4,str, this);
	//ui.lne_Sq->setText(str);

	qulonglong fv = str.toULongLong();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>0xFFFF)
	{
		fv = 0xFFFF;
	}

	m_pAbnormalGOOSE->m_nSqNum = fv;
	ui.lne_Sq->setText(QString::number((uint)fv,10));
	g_pGooseTest->m_bTmtParaChanged = TRUE;
	emit sig_NameChanged(true);
}

void QGooseAbnormalParaSet::slot_lneSq_editingFinished()
{
	QString str = ui.lne_Sq->text();

	//2023/10/26 wjs 将使用数字键盘的初始化为数字键盘
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::SetDefaultKeyboard();
#endif
	//GetWidgetBoard_DigitData(4,str,ui.lne_Sq, this);
	//ui.lne_Sq->setText(str);
// 
// 	qulonglong fv = str.toULongLong();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>0xFFFF)
// 	{
// 		fv = 0xFFFF;
// 	}
// 
// 	m_pAbnormalGOOSE->m_nSqNum = fv;
// 	ui.lne_Sq->setText(QString::number((uint)fv,10));
// 	g_pGooseTest->m_bTmtParaChanged = TRUE;
// 	emit sig_NameChanged(true);
}

void QGooseAbnormalParaSet::slot_ckTTl_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bTtlSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneTTl_clickedKeyBoard()
{
	//this->slot_edit_changed(ui.lne_TTL,TRUE);
	CString str = ui.lne_TTL->text();

// 	GetWidgetBoard_DigitData(4,str, this);
	//ui.lne_TTL->setText(str);

	m_pAbnormalGOOSE->m_nTimeAllowToLive = str.toInt();
	str.Format("%d",m_pAbnormalGOOSE->m_nTimeAllowToLive);
	ui.lne_TTL->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneTTl_editingFinished()
{
	CString str = ui.lne_TTL->text();
	//2023/10/26 wjs 将使用数字键盘的初始化为数字键盘
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::SetDefaultKeyboard();
#endif
	//GetEngWidgetBoard_DigitData(str, this);
	//GetWidgetBoard_DigitData(4,str,ui.lne_TTL, this);
	//ui.lne_TTL->setText(str);

// 	m_pAbnormalGOOSE->m_nTimeAllowToLive = str.toInt();
// 	str.Format("%d",m_pAbnormalGOOSE->m_nTimeAllowToLive);
// 	ui.lne_TTL->setText(str);
// 	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_ckAPPID_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bAppID_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneAPPID_clickedKeyBoard()
{
// 	this->slot_edit_changed(ui.lne_APPID,TRUE);
	
	CString str = ui.lne_APPID->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	//ui.lne_APPID->setText(str);
	//m_pAbnormalGOOSE->m_nAppID = CString_To_long(str);

	long nAppID = 0x0;
	HexToLong(str.GetString(),nAppID);
	str.Format("%04X",nAppID);
	m_pAbnormalGOOSE->m_nAppID = nAppID;
	ui.lne_APPID->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneAPPID_editingFinished()
{
	CString str = ui.lne_APPID->text();

	GetEngWidgetBoard_DigitData(str, this);

}

void QGooseAbnormalParaSet::slot_ckWT_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bNdsCom_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_cbWT_currentIndexChanged(int index)
{
	m_pAbnormalGOOSE->m_nNdsCom = index;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_ckTest_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bTestFlag_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_cbTest_currentIndexChanged(int index)
{
	m_pAbnormalGOOSE->m_nTestFlag = index;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_ckVlan_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bVlanSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneVlan_clickedKeyBoard()
{
// 	this->slot_edit_changed(ui.lne_Vlan,TRUE);
	CString str = ui.lne_Vlan->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	//ui.lne_Vlan->setText(str);

	//m_pAbnormalGOOSE->m_nVlanID = CString_To_long(str);

	long nVlanID = 0x0;
	HexToLong(str.GetString(),nVlanID);
	str.Format("%04X",nVlanID);
	m_pAbnormalGOOSE->m_nVlanID = nVlanID;
	ui.lne_Vlan->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneVlan_editingFinished()
{
	CString str = ui.lne_Vlan->text();

	GetEngWidgetBoard_DigitData(str, this);

}

void QGooseAbnormalParaSet::slot_ckNet_clicked(bool b)
{
	m_pAbnormalGOOSE->m_bNetTypeSet_Sel = b;
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneNet_clickedKeyBoard()
{
// 	this->slot_edit_changed(ui.lne_Net,TRUE);
	CString str = ui.lne_Net->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	//ui.lne_Net->setText(str);

	//m_pAbnormalGOOSE->m_nNetType = CString_To_long(str);

	long nNetType = 0x0;
	HexToLong(str.GetString(),nNetType);
	str.Format("%04X",nNetType);
	m_pAbnormalGOOSE->m_nNetType = nNetType;
	ui.lne_Net->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneNet_editingFinished()
{
	CString str = ui.lne_Net->text();

	GetEngWidgetBoard_DigitData(str, this);

}

void QGooseAbnormalParaSet::slot_lneVlanPriority_clickedKeyBoard()
{
	//this->slot_edit_changed(ui.lne_VlanPriority,TRUE);
	CString str = ui.lne_VlanPriority->text();

// 	GetWidgetBoard_DigitData(4,str, this);
	//ui.lne_VlanPriority->setText(str);

	m_pAbnormalGOOSE->m_nVLanPriority = CString_To_long(str);

	if (m_pAbnormalGOOSE->m_nVLanPriority>7)
	{
		m_pAbnormalGOOSE->m_nVLanPriority = 7;
	}

	if (m_pAbnormalGOOSE->m_nVLanPriority<0)
	{
		m_pAbnormalGOOSE->m_nVLanPriority = 0;
	}

	str.Format("%d",m_pAbnormalGOOSE->m_nVLanPriority);
	ui.lne_VlanPriority->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneVlanPriority_editingFinished()
{
	CString str = ui.lne_VlanPriority->text();

	//2023/10/26 wjs 将使用数字键盘的初始化为数字键盘
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::SetDefaultKeyboard();
#endif
	//GetWidgetBoard_DigitData(4,str,ui.lne_VlanPriority, this);
	//ui.lne_VlanPriority->setText(str);
// 
// 	m_pAbnormalGOOSE->m_nVLanPriority = CString_To_long(str);
// 
// 	if (m_pAbnormalGOOSE->m_nVLanPriority>7)
// 	{
// 		m_pAbnormalGOOSE->m_nVLanPriority = 7;
// 	}
// 
// 	if (m_pAbnormalGOOSE->m_nVLanPriority<0)
// 	{
// 		m_pAbnormalGOOSE->m_nVLanPriority = 0;
// 	}
// 
// 	str.Format("%d",m_pAbnormalGOOSE->m_nVLanPriority);
// 	ui.lne_VlanPriority->setText(str);
// 	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneTimeQuality_clickedKeyBoard()
{
// 	this->slot_edit_changed(ui.lne_TimeQuality,TRUE);
	CString str = ui.lne_TimeQuality->text();

// 	GetEngWidgetBoard_DigitData(str, this);
	//ui.lne_TimeQuality->setText(str);

	//m_pAbnormalGOOSE->m_nTimequality = CString_To_long(str);

	/*if (m_pAbnormalGOOSE->m_nTimequality>0xFF)
	{
		m_pAbnormalGOOSE->m_nTimequality = 0xFF;
	}

	if (m_pAbnormalGOOSE->m_nTimequality<0)
	{
		m_pAbnormalGOOSE->m_nTimequality = 0;
	}*/
	
	long nTimequality = 0x0;
	HexToLong(str.GetString(),nTimequality);

	if (nTimequality > 0xFF)
	{
		nTimequality = 0xFF;
	}
	if (nTimequality < 0)
	{
		nTimequality = 0;
	}

	str.Format("%02X",nTimequality);
	m_pAbnormalGOOSE->m_nTimequality = nTimequality;
	ui.lne_TimeQuality->setText(str);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneTimeQuality_editingFinished()
{
	CString str = ui.lne_TimeQuality->text();

	GetEngWidgetBoard_DigitData(str, this);
}

void QGooseAbnormalParaSet::slot_ComboxSelChanged_GroupIndex(int nCurIndex)
{
//	QString str = ui.comboBox_GroupIndex->text();
	if (nCurIndex<0)
	{
		return;
	}

	m_pAbnormalGOOSE->m_nGroupIndex= nCurIndex;
	Global_SetGooseAbnormalData(nCurIndex,m_pStateParas);
	//SetAbnGooseMessage(pGooseData);
	initGooseOrigPkg();
}

//CIecCfgGooseDataBase* QGooseAbnormalParaSet::GetGooseAbnDataByIndex(int nFindIndex)
//{
//	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
//	CIecCfgGooseDataBase *pIecCfgGooseData = NULL;	
//	POS pos = pSourceGoutDatas->GetHeadPosition();
//	long nCurrIndex = 0;
//
//	while(pos)
//	{
//		pIecCfgGooseData = (CIecCfgGooseDataBase *)pSourceGoutDatas->GetNext(pos);
//
//		if (pIecCfgGooseData->m_nUseFlag == 0)
//		{
//			continue;
//		}
//
//		if (nCurrIndex == nFindIndex)
//		{
//			return pIecCfgGooseData;
//		}
//
//		nCurrIndex++;
//	}
//
//	return NULL;
//}

//BOOL QGooseAbnormalParaSet::SetAbnGooseMessage(CIecCfgGooseDataBase *pIecCfgGooseData)
//{
//	if (pIecCfgGooseData == NULL)
//	{
//		return FALSE;
//	}
//
//	CString_to_char(pIecCfgGooseData->m_strSrcAddress,m_pAbnormalGOOSE->m_strSrcMac);
//	CString_to_char(pIecCfgGooseData->m_strDestAddress,m_pAbnormalGOOSE->m_strDestMac);
//	CString_to_char(pIecCfgGooseData->m_strgocbRef,m_pAbnormalGOOSE->m_strGocbRef);
//	CString_to_char(pIecCfgGooseData->m_strGooseId,m_pAbnormalGOOSE->m_strGoID);
//	CString_to_char(pIecCfgGooseData->m_strDataSet,m_pAbnormalGOOSE->m_strDataSet);
//	m_pAbnormalGOOSE->m_nAppID = pIecCfgGooseData->m_dwAppID;
//	m_pAbnormalGOOSE->m_nConfRecv = pIecCfgGooseData->m_dwVersion;
//	m_pAbnormalGOOSE->m_nTestFlag = pIecCfgGooseData->m_bTest;
//	m_pAbnormalGOOSE->m_nNdsCom = pIecCfgGooseData->m_bNdsCom;
//	m_pAbnormalGOOSE->m_nVlanID = pIecCfgGooseData->m_dwVLandID;
//	m_pAbnormalGOOSE->m_nVLanPriority = pIecCfgGooseData->m_dwVLandPriority;
//	m_pAbnormalGOOSE->m_nTimequality = CString_To_long(pIecCfgGooseData->m_strTQuality);
//
//	return TRUE;
//}

void QGooseAbnormalParaSet::initcmb_APPIDbyBlock()
{
	//	m_olistAppIDs.clear();
	//	g_pStateTest->GetSMVDataAppIDs(m_olistAppIDs);
	//	int pos = 0;

	disconnect(ui.comboBox_GroupIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ComboxSelChanged_GroupIndex(int)));
	ui.comboBox_GroupIndex->clear();

	//	m_olistAppIDs.clear();
	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGooseDataBase *pIecCfgGooseData = NULL;	
	POS pos = pSourceGoutDatas->GetHeadPosition();
	long nFindIndex = 0,nCtrlBlockIndex = 0;
	CString strTmp;

	while(pos)
	{
		pIecCfgGooseData = (CIecCfgGooseDataBase *)pSourceGoutDatas->GetNext(pos);

		if (pIecCfgGooseData->m_nUseFlag == 0)
		{
			continue;
		}
		strTmp.Format(_T("%ld_0x%04X"),nCtrlBlockIndex+1,pIecCfgGooseData->m_dwAppID);

//		QString appidstr = QString::number(nCtrlBlockIndex+1,10) + strTmp/*tr("_0x")+QString::number(,16)*/;
		ui.comboBox_GroupIndex->addItem(strTmp);

		if(m_pAbnormalGOOSE->m_nGroupIndex== pIecCfgGooseData->m_dwAppID)
		{
			nFindIndex = nCtrlBlockIndex;
		}

		nCtrlBlockIndex++;
	}

	ui.comboBox_GroupIndex->setCurrentIndex(m_pAbnormalGOOSE->m_nGroupIndex);
		ui.comboBox_GroupIndex->setDisabled(false);
	//initGooseOrigPkg();

	connect(ui.comboBox_GroupIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ComboxSelChanged_GroupIndex(int)));
}

void QGooseAbnormalParaSet::slot_lneStateTime_editingFinished()
{
	//m_pCurrStatePara->m_fTimeState = ui.lne_StateTime->text().toFloat();
// 	QString strTmp = ui.lne_StateTime->text();
// 	GetWidgetBoard_DigitData(4,strTmp,ui.lne_StateTime, this);
// 	bool bRet = TRUE;
// 	m_pCurrStatePara->m_fTimeState = strTmp.toFloat(&bRet);
// 
// 	if(m_pCurrStatePara->m_fTimeState < 0.0f)
// 	{
// 		m_pCurrStatePara->m_fTimeState = 0.0;
// 	}
// 
// 	CString strValue;
// 	strValue.Format(_T("%.03f"),m_pCurrStatePara->m_fTimeState);
// 	ui.lne_StateTime->setText(strValue);
// 	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneStateTime_clickedKeyBoard()
{
	//m_pCurrStatePara->m_fTimeState = ui.lne_StateTime->text().toFloat();
	//QString strTmp = ui.lne_StateTime->text();
// 	GetWidgetBoard_DigitData(4,strTmp, this);
	bool bRet = TRUE;
//	m_pCurrStatePara->m_fTimeState = strTmp.toFloat(&bRet);

	if(m_pCurrStatePara->m_fTimeState < 0.0f)
	{
		m_pCurrStatePara->m_fTimeState = 0.0;
	}

	CString strValue;
	strValue.Format(_T("%.03f"),m_pCurrStatePara->m_fTimeState);
	//ui.lne_StateTime->setText(strValue);
	g_pGooseTest->m_bTmtParaChanged = TRUE;
}

void QGooseAbnormalParaSet::slot_lneStateName_editingFinished()
{
	/*CString str = ui.lne_StateName->text();
	strcpy(m_pCurrStatePara->m_strName, str.GetString());
	g_pGooseTest->m_bTmtParaChanged = TRUE;
	emit sig_NameChanged(false);*/
}

void QGooseAbnormalParaSet::slot_btnAdd_clicked()
{
	emit sig_add();
}

void QGooseAbnormalParaSet::slot_btnDelete_clicked()
{
	emit sig_delete();
}

void QGooseAbnormalParaSet::slot_btnClear_clicked()
{
	emit sig_clearResult();
}

void QGooseAbnormalParaSet::UpdateStateTimeUI()
{
	if (m_pCurrStatePara == NULL)
	{
		return;
	}

	//ui.lne_StateTime->setText(QString::number(m_pCurrStatePara->m_fTimeState,'f',3));	//输出时间

	if ((m_pCurrStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMETRIGGER)||(m_pCurrStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMEBINTRIGGER))
	{
		//ui.lne_StateTime->setDisabled(false);
	}
	else
	{
		//ui.lne_StateTime->setDisabled(true);
	}
}

void QGooseAbnormalParaSet::UpdateStateNameUI()
{
	/*if (m_pCurrStatePara == NULL)
	{
		return;
	}

	CString strTmp;
	strTmp = m_pCurrStatePara->m_strName;
	ui.lne_StateName->setText(strTmp);*/
}
