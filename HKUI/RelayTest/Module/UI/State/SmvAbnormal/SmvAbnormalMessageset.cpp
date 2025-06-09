#include "SmvAbnormalMessageset.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../Module/CommonMethod/commonMethod.h"
//#include "../../SttTestCntrFrameBase.h"

QSmvAbnormalMessageSet::QSmvAbnormalMessageSet(tmt_SmvAbnormalMsg* pSMVMsg,bool RefrTm,QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::SmvAbnormalMessageSet;
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_pSMVMsg = pSMVMsg;
	brefrtm = RefrTm;

	SetSmvAbnormalMessageFont();
	initConnect();
	initData();
        InitLanguage();
	this->setFocus();
}

QSmvAbnormalMessageSet::~QSmvAbnormalMessageSet()
{
	/*if (m_pSMVMsg != NULL)
	{
		delete m_pSMVMsg;
		m_pSMVMsg = NULL;
	}*/
	delete ui;
}
void QSmvAbnormalMessageSet::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui->groupBox, g_sLangTxt_Native_SVOrigMsg, XLang_Ctrls_QGroupBox);
    xlang_SetLangStrToWidget_Txt(ui->label, g_sLangTxt_Native_SrcMAC, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_8, g_sLangTxt_IEC_Synchronously, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_2, g_sLangTxt_Native_DestMAC, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_9, g_sLangTxt_IEC_Version, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_10, g_sLangTxt_Native_SampDelay, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_5, g_sLangTxt_Native_NetID, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->pbn_Ok, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->pbn_Cancle, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}

void QSmvAbnormalMessageSet::SetSmvAbnormalMessageFont()
{
	ui->groupBox->setFont(*g_pSttGlobalFont);
	ui->label->setFont(*g_pSttGlobalFont);
	ui->lne_sourceMac->setFont(*g_pSttGlobalFont);
	ui->label_8->setFont(*g_pSttGlobalFont);
	ui->cmb_synchro->setFont(*g_pSttGlobalFont);
	ui->label_2->setFont(*g_pSttGlobalFont);
	ui->lne_destMAC->setFont(*g_pSttGlobalFont);
	ui->label_9->setFont(*g_pSttGlobalFont);
	ui->lne_version->setFont(*g_pSttGlobalFont);
	ui->label_3->setFont(*g_pSttGlobalFont);
	ui->lne_VIanID->setFont(*g_pSttGlobalFont);
	ui->label_10->setFont(*g_pSttGlobalFont);
	ui->lne_sampledelay->setFont(*g_pSttGlobalFont);
	ui->label_4->setFont(*g_pSttGlobalFont);
	ui->lne_VIanPriority->setFont(*g_pSttGlobalFont);
	ui->label_11->setFont(*g_pSttGlobalFont);
	ui->lne_datset->setFont(*g_pSttGlobalFont);
	ui->label_5->setFont(*g_pSttGlobalFont);
	ui->lne_nettype->setFont(*g_pSttGlobalFont);
	ui->label_12->setFont(*g_pSttGlobalFont);
	ui->lne_RefrTm->setFont(*g_pSttGlobalFont);
	ui->label_6->setFont(*g_pSttGlobalFont);
	ui->lne_APPID->setFont(*g_pSttGlobalFont);
	ui->label_7->setFont(*g_pSttGlobalFont);
	ui->lne_SVID->setFont(*g_pSttGlobalFont);
	ui->pbn_Ok->setFont(*g_pSttGlobalFont);
	ui->pbn_Cancle->setFont(*g_pSttGlobalFont);
}

void QSmvAbnormalMessageSet::initConnect()
{
	connect(ui->pbn_Ok,SIGNAL(clicked()),this,SLOT(slot_pbn_OkClicked()));
	connect(ui->pbn_Cancle,SIGNAL(clicked()),this,SLOT(slot_pbn_Cancle()));

#ifdef _PSX_QT_LINUX_
	connect(ui->lne_sourceMac,SIGNAL(clicked()),this,SLOT(slot_lne_sourceMacKeyBoard()));
	connect(ui->lne_destMAC,SIGNAL(clicked()),this,SLOT(slot_lne_destMACKeyBoard()));
	connect(ui->lne_VIanID,SIGNAL(clicked()),this,SLOT(slot_lne_VIanIDKeyBoard()));
	connect(ui->lne_nettype,SIGNAL(clicked()),this,SLOT(slot_lne_nettypeKeyBoard()));
	connect(ui->lne_APPID,SIGNAL(clicked()),this,SLOT(slot_lne_APPIDKeyBoard()));
	connect(ui->lne_datset,SIGNAL(clicked()),this,SLOT(slot_lne_datsetKeyBoard()));
	connect(ui->lne_SVID,SIGNAL(clicked()),this,SLOT(slot_lne_SVIDKeyBoard()));
#else
	connect(ui->lne_sourceMac,SIGNAL(editingFinished()),this,SLOT(slot_lne_sourceMacKeyBoard()));
	connect(ui->lne_destMAC,SIGNAL(editingFinished()),this,SLOT(slot_lne_destMACKeyBoard()));
	connect(ui->lne_VIanID,SIGNAL(editingFinished()),this,SLOT(slot_lne_VIanIDKeyBoard()));
	connect(ui->lne_nettype,SIGNAL(editingFinished()),this,SLOT(slot_lne_nettypeKeyBoard()));
	connect(ui->lne_APPID,SIGNAL(editingFinished()),this,SLOT(slot_lne_APPIDKeyBoard()));
	connect(ui->lne_datset,SIGNAL(editingFinished()),this,SLOT(slot_lne_datsetKeyBoard()));
	connect(ui->lne_SVID,SIGNAL(editingFinished()),this,SLOT(slot_lne_SVIDKeyBoard()));
#endif

#ifdef _PSX_QT_LINUX_
	connect(ui->lne_version,SIGNAL(clicked()),this,SLOT(slot_lne_versionChanged()));
	connect(ui->lne_VIanPriority,SIGNAL(clicked()),this,SLOT(slot_lne_VIanPriorityChanged()));

#endif
	connect(ui->lne_version,SIGNAL(editingFinished()),this,SLOT(slot_lne_versionKeyBoard()));
	connect(ui->lne_VIanPriority,SIGNAL(editingFinished()),this,SLOT(slot_lne_VIanPriorityKeyBoard()));
}

void QSmvAbnormalMessageSet::initData()
{
// 	ui->lne_sourceMac->setInputMask("HH-HH-HH-HH-HH-HH;_");     //20230406 chenling 关标末尾显示粗
// 	ui->lne_sourceMac->setText(QString(QLatin1String(m_pSMVMsg->m_strMacAddrSrc)));
// 	ui->lne_destMAC->setInputMask("HH-HH-HH-HH-HH-HH;_");
// 	ui->lne_destMAC->setText(QString(QLatin1String(m_pSMVMsg->m_strMacAddrDst)));

    QRegExp regIp("([1-9]|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5])(.(\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5])){3}");	
    ui->lne_sourceMac->setValidator(new QRegExpValidator(regIp,this));
	ui->lne_sourceMac->setText(QString(QLatin1String(m_pSMVMsg->m_strMacAddrSrc)));
	ui->lne_destMAC->setValidator(new QRegExpValidator(regIp,this));
	ui->lne_destMAC->setText(QString(QLatin1String(m_pSMVMsg->m_strMacAddrDst)));

	QRegExp regExp("[a-fA-F0-9]{4}");
	ui->lne_VIanID->setValidator(new QRegExpValidator(regExp, this));
	ui->lne_VIanPriority->setValidator(new QRegExpValidator(regExp, this));

	ui->lne_APPID->setValidator(new QRegExpValidator(regExp, this));
	ui->lne_APPID->setReadOnly(true);

	ui->lne_nettype->setValidator(new QRegExpValidator(regExp, this));
	ui->lne_VIanID->setText(QString::number(m_pSMVMsg->m_nVLanID,16));
	ui->lne_VIanPriority->setText(QString::number(m_pSMVMsg->m_nVLanPriority,10));
	ui->lne_nettype->setText(QString::number(m_pSMVMsg->m_nNetType,16));

	ui->lne_APPID->setText((QString::number(m_pSMVMsg->m_nAppID,16)));
	ui->cmb_synchro->setCurrentIndex(m_pSMVMsg->m_nSyn);
	
	ui->lne_version->setText(QString::number(m_pSMVMsg->m_nVersion,10));
//	ui->lne_sampledelay->setText(QString::number(m_pSMVMsg->m_nSmpDelay,10));
	ui->lne_datset->setText(QString::fromStdString(m_pSMVMsg->m_strDataset));
	ui->lne_RefrTm->setText(QString::number(brefrtm,10));
	ui->lne_SVID->setText(QString::fromStdString(m_pSMVMsg->m_strSVID));
 
  	ui->lne_nettype->setText("88ba");
  	ui->lne_nettype->setEnabled(false);

	ui->lne_sourceMac->setFocusPolicy(Qt::ClickFocus);//20240507 suyang 取消进入界面就有弹键盘，改为点击焦点
}

void QSmvAbnormalMessageSet::slot_pbn_OkClicked()
{
	ExitHideKeyboardWidget();
	QByteArray ba = ui->lne_sourceMac->text().toLatin1();
	char* pc = ba.data();
	strcpy(m_pSMVMsg->m_strMacAddrSrc,pc);

	ba = ui->lne_destMAC->text().toLatin1();
	pc = ba.data();
	strcpy(m_pSMVMsg->m_strMacAddrDst,pc);

	bool ok;
	QString str = ui->lne_VIanID->text();
	m_pSMVMsg->m_nVLanID = str.toInt(&ok,16);
	m_pSMVMsg->m_nVLanPriority = ui->lne_VIanPriority->text().toInt();

	str = ui->lne_APPID->text();
	m_pSMVMsg->m_nAppID = str.toInt(&ok,16);
	m_pSMVMsg->m_nSyn = ui->cmb_synchro->currentIndex();

	m_pSMVMsg->m_nVersion = ui->lne_version->text().toInt();
//	m_pSMVMsg->m_nSmpDelay = ui->lne_sampledelay->text().toInt();
	
	ba = ui->lne_datset->text().toLatin1();
	pc = ba.data();
	strcpy(m_pSMVMsg->m_strDataset,pc);

	ba = ui->lne_SVID->text().toLatin1();
	pc = ba.data();
	strcpy(m_pSMVMsg->m_strSVID,pc);
	
	str = ui->lne_nettype->text();
	m_pSMVMsg->m_nNetType = str.toInt(&ok,16);

	close();
}

void QSmvAbnormalMessageSet::slot_pbn_Cancle()
{
	ExitHideKeyboardWidget();
	close();
}

void QSmvAbnormalMessageSet::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	QString str;
	GetEngWidgetBoard_DigitData(str, this);

	pEditLine->setText(str);
	pEditLine->SetEditFinished();
}

void QSmvAbnormalMessageSet::slot_lne_sourceMacChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_destMACChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_VIanIDChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_VIanPriorityChanged()
{
	QString str = ui->lne_VIanPriority->text();
	GetWidgetBoard_DigitData(4, str,ui->lne_VIanPriority, parentWidget());
}
void QSmvAbnormalMessageSet::slot_lne_nettypeChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_APPIDChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_SVIDChanged()
{

}

void QSmvAbnormalMessageSet::slot_cmb_synchroChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_versionChanged()
{
	QString str = ui->lne_version->text();
	GetWidgetBoard_DigitData(4, str,ui->lne_version, parentWidget());
}
void QSmvAbnormalMessageSet::slot_lne_sampledelayChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_datsetChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_RefrTmChanged()
{

}

void QSmvAbnormalMessageSet::slot_lne_sourceMacKeyBoard()
{
	QString str = ui->lne_sourceMac->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_sourceMac->setText(str);
	//ui->lne_sourceMac->SetEditFinished();
	//this->slot_edit_changed(ui->lne_sourceMac,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_destMACKeyBoard()
{
	QString str = ui->lne_destMAC->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_destMAC->setText(str);
	//ui->lne_destMAC->SetEditFinished();
	//this->slot_edit_changed(ui->lne_destMAC,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_VIanIDKeyBoard()
{
	QString str = ui->lne_VIanID->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_VIanID->setText(str);
	//ui->lne_VIanID->SetEditFinished();
	//this->slot_edit_changed(ui->lne_VIanID,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_VIanPriorityKeyBoard()
{
	QString str = ui->lne_VIanPriority->text();
// 	GetWidgetBoard_DigitData(4, str,ui->lne_VIanPriority, parentWidget());
 	ui->lne_VIanPriority->setText(str);
	//ui->lne_VIanPriority->SetEditFinished();
	//this->slot_edit_changed(ui->lne_VIanPriority,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_nettypeKeyBoard()
{
	QString str = ui->lne_nettype->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_nettype->setText(str);
	//ui->lne_nettype->SetEditFinished();
	//this->slot_edit_changed(ui->lne_nettype,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_APPIDKeyBoard()
{
	QString str = ui->lne_APPID->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_APPID->setText(str);
	//ui->lne_APPID->SetEditFinished();
	//this->slot_edit_changed(ui->lne_APPID,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_versionKeyBoard()
{
	QString str = ui->lne_version->text();
// 	GetWidgetBoard_DigitData(4, str,ui->lne_version, parentWidget());
 	ui->lne_version->setText(str);
	//ui->lne_version->SetEditFinished();
	//this->slot_edit_changed(ui->lne_version,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_datsetKeyBoard()
{
	QString str = ui->lne_datset->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_datset->setText(str);
	//ui->lne_datset->SetEditFinished();
	//this->slot_edit_changed(ui->lne_datset,TRUE);
}

void QSmvAbnormalMessageSet::slot_lne_SVIDKeyBoard()
{
	QString str = ui->lne_SVID->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	ui->lne_SVID->setText(str);
	//ui->lne_SVID->SetEditFinished();
	//this->slot_edit_changed(ui->lne_SVID,TRUE);
}