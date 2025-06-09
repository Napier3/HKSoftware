#include "CommonValueDialogOfStatus.h"

#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
#include "..\..\CommonMethod\commonMethod.h"
CommonValueDialogOfStatus::CommonValueDialogOfStatus(tmt_StateParas* pSateParas,QWidget *parent): QDialog(parent)
{
	ui.setupUi(this);
	ASSERT(pSateParas != NULL);
	m_pSateParas = pSateParas;
	m_nIsOK = 0;

	init();
	initPara();
        InitLanguage();
	initConnections();

	setWindowIcon (QPixmap( "./images/setCommon.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowTitle(g_sLangTxt_GeneralParameter);
}

CommonValueDialogOfStatus::~CommonValueDialogOfStatus()
{

}

void CommonValueDialogOfStatus::InitLanguage() 
{
  // ui
    xlang_SetLangStrToWidget_Txt(ui.label_14, g_sLangTxt_Native_RefState, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.label_15, g_sLangTxt_Native_DcComp, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.label_16, g_sLangTxt_Native_DecayTime, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.label_17, g_sLangTxt_Native_LoopCount, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Ok, g_sLangTxt_Native_Confirm, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Cancel, g_sLangTxt_Native_Cancel, XLang_Ctrls_QPushButton);
}

void CommonValueDialogOfStatus::initPara()
{
	ui.cmb_JudgeCondition->setCurrentIndex(m_pSateParas->m_nBinTripRef);
	ui.cmb_DCOFFSET->setCurrentIndex(m_pSateParas->m_nPlusDC);
	slot_cmb_DCOFFSETChanged(m_pSateParas->m_nPlusDC);

	ui.lne_Tou->setText(QString::number(m_pSateParas->m_fTao,'f',3));
	ui.lne_RepeatTime->setText(QString("%1").arg(m_pSateParas->m_nRepeatNumbers));

	ui.cmb_JudgeCondition->setToolTip("JudgeCondition");
	ui.cmb_DCOFFSET->setToolTip("DCOFFSET");
	ui.lne_Tou->setToolTip("Tou");
	ui.lne_RepeatTime->setToolTip("RepeatTime");
}

void CommonValueDialogOfStatus::initConnections()
{
	connect(ui.pbn_Ok, SIGNAL(clicked()), this, SLOT(slot_OkClicked()));
	connect(ui.pbn_Cancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(ui.cmb_DCOFFSET, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_DCOFFSETChanged(int)));
	connect(ui.lne_Tou,SIGNAL(editingFinished()),this,SLOT(slot_lne_TouChanged()));
	connect(ui.lne_RepeatTime,SIGNAL(editingFinished()),this,SLOT(slot_lne_RepeatTimeChanged()));
}

void CommonValueDialogOfStatus::slot_OkClicked()
{
	m_pSateParas->m_nBinTripRef = ui.cmb_JudgeCondition->currentIndex();
	m_pSateParas->m_nPlusDC = ui.cmb_DCOFFSET->currentIndex();
	m_pSateParas->m_fTao = ui.lne_Tou->text().toFloat();
	int temp = ui.lne_RepeatTime->text().toInt();

	m_pSateParas->m_nRepeatNumbers = temp; //循环次数
	
	close();
	m_nIsOK = 1;
}

void CommonValueDialogOfStatus::slot_CancelClicked()
{
	close();
	m_nIsOK = 2;
}

void CommonValueDialogOfStatus::init()
{
	ui.pbn_Ok->setIcon (QPixmap( "./images/Check.png"));
	ui.pbn_Cancel->setIcon (QPixmap( "./images/Cancel.png"));

	initMaxPositiveEdit(ui.lne_Tou);
	initMaxPositiveEdit(ui.lne_RepeatTime);
	ui.cmb_JudgeCondition->clear();
	ui.cmb_DCOFFSET->clear();

	m_JudgeConditionList<</*tr("上一个状态")*/g_sLangTxt_State_LastState<</*tr("第一个状态")*/g_sLangTxt_State_FirstState;
	m_DCOFFSETList<</*tr("否")*/g_sLangTxt_State_No<</*tr("是")*/g_sLangTxt_State_Yes;
	ui.cmb_JudgeCondition->addItems(m_JudgeConditionList);
	ui.cmb_DCOFFSET->addItems(m_DCOFFSETList);
}

void CommonValueDialogOfStatus::slot_cmb_DCOFFSETChanged(int index)
{
	if(index == 0) //选择否
	{
		ui.lne_Tou->setDisabled(true);
	}
	else
	{
		ui.lne_Tou->setDisabled(false);
	}
}

void CommonValueDialogOfStatus::slot_lne_TouChanged()
{
	if (ui.lne_Tou->text().isEmpty())
	{
		ui.lne_Tou->setText("0.1");
	}
	QString str = ui.lne_Tou->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}
	float tou= str.toFloat();
	if (tou>0.1)
	{
		tou = 0.1;
	}
	else if (tou<0)
	{
		tou = 0;
	}
	ui.lne_Tou->setText(QString::number(tou,'f',3));
}

void CommonValueDialogOfStatus::slot_lne_RepeatTimeChanged()
{
	if (ui.lne_RepeatTime->text().isEmpty())
	{
		ui.lne_RepeatTime->setText("0");
	}

	QString str = ui.lne_RepeatTime->text();

	float fv = str.toFloat();
	fv = setLimit(0,100000,fv);
	
	ui.lne_RepeatTime->setText(QString::number(fv,'f',0));
}

void CommonValueDialogOfStatus::closeEvent( QCloseEvent *event )
{
	m_nIsOK = 2;
}

void CommonValueDialogOfStatus::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{
		slot_OkClicked();
	}
}

