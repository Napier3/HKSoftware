#include "SmvAbnormalParaset.h"
#include "SmvAbnormalPointset.h"
#include "SmvAbnormalChannelSelect.h"
#include "SmvAbnormalMessageset.h"
#include "SmvAbnormalQualityset.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../Module/UI/State/SttMacroParaEditViewState.h"

#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif


QSmvAbnormalParaset::QSmvAbnormalParaset(QWidget *parent):
	/*QWidget(parent),*/ui(new Ui::QSmvAbnormalParaset)
{
	ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_nCurIndex = 0;
	m_pAbnormalSMV = NULL;
	
	m_sendtype.clear();
	m_sendtype << g_sLangTxt_Native_SendByWave << g_sLangTxt_Native_SendBySec;
	ui->cmb_sendtype->addItems(m_sendtype);

	SetSmvAbnormalParasetFont();
	InitUI_BySendType();
	initConnect();
    InitLanguage();
	setFont(*g_pSttGlobalFont);
	
}

QSmvAbnormalParaset::~QSmvAbnormalParaset()
{

}

void QSmvAbnormalParaset::InitLanguage()
{

    xlang_SetLangStrToWidget_Txt(ui->radio_no, g_sLangTxt_State_No, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->radio_lost, g_sLangTxt_Native_FrameDrop, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->radio_flypoint, g_sLangTxt_Native_FlyDot, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->label_6, g_sLangTxt_Native_AbnVolt, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_7, g_sLangTxt_Native_AbnCurr, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->radio_jitter, g_sLangTxt_Native_JitterTest, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->label_8, g_sLangTxt_Native_JitterVal, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->radio_errcmpt, g_sLangTxt_Native_ErrSeqTest, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->label_9, g_sLangTxt_Native_JumpVal, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->radio_delayoffset, g_sLangTxt_Native_DelayDev, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->label_11, g_sLangTxt_Native_DevTime, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->radio_delaymodify, g_sLangTxt_Native_DelayVar, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->label_12, g_sLangTxt_Native_DelayTime, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->radio_indexerr, g_sLangTxt_Native_SeqDev, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->label_18, g_sLangTxt_Native_DevVal, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->radio_qualityinvalid, g_sLangTxt_Native_QltyExcp, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget_Txt(ui->pbn_ChannelSelect, g_sLangTxt_Native_ChannelSelect, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->pbn_qualitySet, g_sLangTxt_IEC_QualityParaSet, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->pbn_set, g_sLangTxt_Native_AbnPointSet, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->pbn_MessageSet, g_sLangTxt_Native_MsgSet, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->checkBox_SelOrgPkgSet, g_sLangTxt_Native_OrigMsgSet, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui->label_16, g_sLangTxt_Native_MsgSel, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_1, g_sLangTxt_Native_AbnData, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_3, g_sLangTxt_Native_SndFreq, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_2, g_sLangTxt_Native_SndFreqPS, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_4, g_sLangTxt_Native_SndTimeS, XLang_Ctrls_QLabel);

    //m_sendtype.clear();
    //m_sendtype << g_sLangTxt_Native_SendByWave << g_sLangTxt_Native_SendBySec;
    //ui->cmb_sendtype->addItems(m_sendtype);
}

void QSmvAbnormalParaset::InitUI_BySendType()
{
	if (ui->cmb_sendtype->currentIndex())
	{
		ui->lne_sendcircle->setDisabled(true);
		ui->lne_circlepersecond->setDisabled(false);
		ui->lne_sendtime->setDisabled(false);
	}
	else
	{
		ui->lne_sendcircle->setDisabled(false);
		ui->lne_circlepersecond->setDisabled(true);
		ui->lne_sendtime->setDisabled(true);
	}
}

void QSmvAbnormalParaset::SetSmvAbnormalParasetFont()
{
	ui->radio_no->setFont(*g_pSttGlobalFont);
	ui->radio_lost->setFont(*g_pSttGlobalFont);
	ui->radio_flypoint->setFont(*g_pSttGlobalFont);
	ui->radio_jitter->setFont(*g_pSttGlobalFont);
	ui->radio_errcmpt->setFont(*g_pSttGlobalFont);
	ui->radio_delayoffset->setFont(*g_pSttGlobalFont);
	ui->radio_delaymodify->setFont(*g_pSttGlobalFont);
	ui->radio_indexerr->setFont(*g_pSttGlobalFont);
	ui->radio_qualityinvalid->setFont(*g_pSttGlobalFont);
//	ui->label_5->setFont(*g_pSttGlobalFont);
	ui->label_6->setFont(*g_pSttGlobalFont);
	ui->label_7->setFont(*g_pSttGlobalFont);
	ui->label_8->setFont(*g_pSttGlobalFont);
	ui->label_9->setFont(*g_pSttGlobalFont);
	ui->label_11->setFont(*g_pSttGlobalFont);
	ui->label_12->setFont(*g_pSttGlobalFont);
	ui->label_13->setFont(*g_pSttGlobalFont);
	ui->label_14->setFont(*g_pSttGlobalFont);
	ui->label_15->setFont(*g_pSttGlobalFont);
	ui->label_18->setFont(*g_pSttGlobalFont);
	ui->label_1->setFont(*g_pSttGlobalFont);
	ui->label_2->setFont(*g_pSttGlobalFont);
	ui->label_3->setFont(*g_pSttGlobalFont);
	ui->label_4->setFont(*g_pSttGlobalFont);
	ui->label_16->setFont(*g_pSttGlobalFont);
//	ui->label->setFont(*g_pSttGlobalFont);
	ui->ck_Ua->setFont(*g_pSttGlobalFont);
	ui->ck_Ub->setFont(*g_pSttGlobalFont);
	ui->ck_Uc->setFont(*g_pSttGlobalFont);
	ui->ck_Ia->setFont(*g_pSttGlobalFont);
	ui->ck_Ib->setFont(*g_pSttGlobalFont);
	ui->ck_Ic->setFont(*g_pSttGlobalFont);
	ui->pbn_set->setFont(*g_pSttGlobalFont);
	ui->pbn_ChannelSelect->setFont(*g_pSttGlobalFont);
	ui->pbn_qualitySet->setFont(*g_pSttGlobalFont);
	ui->pbn_MessageSet->setFont(*g_pSttGlobalFont);
	ui->checkBox_SelOrgPkgSet->setFont(*g_pSttGlobalFont);
	ui->lne_sendcircle->setFont(*g_pSttGlobalFont);
	ui->lne_circlepersecond->setFont(*g_pSttGlobalFont);
	ui->lne_sendtime->setFont(*g_pSttGlobalFont);
	ui->lne_flypointvolt->setFont(*g_pSttGlobalFont);
	ui->lne_flypoitcurrent->setFont(*g_pSttGlobalFont);
	ui->lne_jitter->setFont(*g_pSttGlobalFont);
	ui->lne_errcmpt->setFont(*g_pSttGlobalFont);
	ui->lne_offsettime->setFont(*g_pSttGlobalFont);
	ui->lne_modifytime->setFont(*g_pSttGlobalFont);
	ui->lne_indexerr->setFont(*g_pSttGlobalFont);
	ui->cmb_APPID->setFont(*g_pSttGlobalFont);	
	ui->cmb_sendtype->setFont(*g_pSttGlobalFont);
    ui->lne_sendcircle->setFont(*g_pSttGlobalFont);
	ui->lne_circlepersecond->setFont(*g_pSttGlobalFont);
	ui->lne_sendtime->setFont(*g_pSttGlobalFont);
}

void QSmvAbnormalParaset::initConnect()
{
	connect(ui->pbn_set,SIGNAL(clicked()),this,SLOT(slot_pbn_AbnomalPointSet()));
	connect(ui->pbn_ChannelSelect,SIGNAL(clicked()),this,SLOT(slot_ptn_ChannelSelect()));
	connect(ui->pbn_qualitySet,SIGNAL(clicked()),this,SLOT(slot_pbn_qualitySet()));
	connect(ui->pbn_MessageSet,SIGNAL(clicked()),this,SLOT(slot_pbn_MessageSet()));
	connect(ui->checkBox_SelOrgPkgSet,SIGNAL(stateChanged (int)),this,SLOT(slot_checkBox_SelOrgPkgSet_changed(int)));
	connect(ui->cmb_sendtype,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_sendtypeChanged(int)));
	
	connect(ui->radio_lost,SIGNAL(toggled(bool)),this,SLOT(slot_radio_lostClicked()));
	connect(ui->radio_flypoint,SIGNAL(toggled(bool)),this,SLOT(slot_radio_flypointClicked()));
	connect(ui->radio_jitter,SIGNAL(toggled(bool)),this,SLOT(slot_radio_jitterClicked()));
	connect(ui->radio_errcmpt,SIGNAL(toggled(bool)),this,SLOT(slot_radio_errcmptClicked()));
	connect(ui->radio_delayoffset,SIGNAL(toggled(bool)),this,SLOT(slot_radio_delayoffsetClicked()));
	connect(ui->radio_delaymodify,SIGNAL(toggled(bool)),this,SLOT(slot_radio_delaymodifyClicked()));
	connect(ui->radio_indexerr,SIGNAL(toggled(bool)),this,SLOT(slot_radio_indexerrClicked()));
	connect(ui->radio_qualityinvalid,SIGNAL(toggled(bool)),this,SLOT(slot_radio_qualityinvalidChanged()));

	connect(ui->ck_Ua,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ub,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Uc,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ia,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ib,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ic,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));

	connect(ui->radio_no,SIGNAL(toggled(bool)),this,SLOT(slot_radio_noClicked()));

#ifdef _PSX_QT_LINUX_
	connect(ui->lne_sendcircle,SIGNAL(clicked()),this,SLOT(slot_lne_sendcircleChanged()));
	connect(ui->lne_circlepersecond,SIGNAL(clicked()),this,SLOT(slot_lne_circlepersecondChanged()));
	connect(ui->lne_sendtime,SIGNAL(clicked()),this,SLOT(slot_lne_sendtimeChanged()));
	connect(ui->lne_flypointvolt,SIGNAL(clicked()),this,SLOT(slot_lne_flypointvoltChanged()));
	connect(ui->lne_flypoitcurrent,SIGNAL(clicked()),this,SLOT(slot_lne_flypoitcurrentChanged()));
	connect(ui->lne_jitter,SIGNAL(clicked()),this,SLOT(slot_lne_jitterChanged()));
	connect(ui->lne_errcmpt,SIGNAL(clicked()),this,SLOT(slot_lne_errcmptChanged()));
	connect(ui->lne_offsettime,SIGNAL(clicked()),this,SLOT(slot_lne_offsettimeChanged()));
	connect(ui->lne_modifytime,SIGNAL(clicked()),this,SLOT(slot_lne_modifytimeChanged()));
	connect(ui->lne_indexerr,SIGNAL(clicked()),this,SLOT(slot_lne_indexerrChanged()));
#endif
	connect(ui->lne_sendcircle,SIGNAL(editingFinished()),this,SLOT(slot_lne_sendcircleKeyBoard()));
	connect(ui->lne_circlepersecond,SIGNAL(editingFinished()),this,SLOT(slot_lne_circlepersecondKeyBoard()));
	connect(ui->lne_sendtime,SIGNAL(editingFinished()),this,SLOT(slot_lne_sendtimeKeyBoard()));
	connect(ui->lne_flypointvolt,SIGNAL(editingFinished()),this,SLOT(slot_lne_flypointvoltKeyBoard()));
	connect(ui->lne_flypoitcurrent,SIGNAL(editingFinished()),this,SLOT(slot_lne_flypointcurrentKeyBoard()));
	connect(ui->lne_jitter,SIGNAL(editingFinished()),this,SLOT(slot_lne_jitterKeyBoard()));
	connect(ui->lne_errcmpt,SIGNAL(editingFinished()),this,SLOT(slot_lne_errcmptKeyBoard()));
	connect(ui->lne_offsettime,SIGNAL(editingFinished()),this,SLOT(slot_lne_offsettingKeyBoard()));
	connect(ui->lne_modifytime,SIGNAL(editingFinished()),this,SLOT(slot_lne_modifytimeKeyBoard()));
	connect(ui->lne_indexerr,SIGNAL(editingFinished()),this,SLOT(slot_lne_indexerrKeyBoard()));

}

void QSmvAbnormalParaset::initData()
{
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);

	if (m_pAbnormalSMV->m_nAbnormalType == 0)
	{
		ui->radio_no->setChecked(true);
	}
	else
	{
		if (m_pAbnormalSMV->m_nAbnormalType == 1)//丢帧
		{
			ui->radio_lost->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 3)//飞点
		{
			ui->radio_flypoint->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 2)//抖动
		{
			ui->radio_jitter->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 4)//错序
		{
			ui->radio_errcmpt->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 5)//延时偏差
		{
			ui->radio_delayoffset->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 6)//延时变化
		{
			ui->radio_delaymodify->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 7)//序号偏差
		{
			ui->radio_indexerr->setChecked(true);
		}
		else if (m_pAbnormalSMV->m_nAbnormalType == 8)//品质异常
		{
			ui->radio_qualityinvalid->setChecked(true);
			ui->pbn_ChannelSelect->setDisabled(false);
			ui->pbn_qualitySet->setDisabled(false);
		}
	}

	m_oabnomalPointEnabled.clear();
	for (int i=0;i<80;i++)
	{
		m_oabnomalPointEnabled.append(m_pAbnormalSMV->m_nAbnormalPoint[i]);
	}

	m_olistQualityParas.clear();
	for (int i=0;i<12;i++)
	{
		m_olistQualityParas.append(m_pAbnormalSMV->m_nQualityBit[i]);
	}

	ui->lne_flypointvolt->setText(QString::number(m_pAbnormalSMV->m_fFlyPointVolt,'f',3));
	ui->lne_flypoitcurrent->setText(QString::number(m_pAbnormalSMV->m_fFlyPointCurrent,'f',3));

	disconnect(ui->ck_Ua,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	disconnect(ui->ck_Ub,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	disconnect(ui->ck_Uc,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	disconnect(ui->ck_Ia,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	disconnect(ui->ck_Ib,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	disconnect(ui->ck_Ic,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));

	if (m_pAbnormalSMV->m_nVolChEnable[0]==1)
	{
		ui->ck_Ua->setCheckState(Qt::Checked);
	}
	else
	{
		ui->ck_Ua->setCheckState(Qt::Unchecked);
	}

	if (m_pAbnormalSMV->m_nVolChEnable[1]==1)
	{
		ui->ck_Ub->setCheckState(Qt::Checked);
	}
	else
	{
		ui->ck_Ub->setCheckState(Qt::Unchecked);
	}

	if (m_pAbnormalSMV->m_nVolChEnable[2]==1)
	{
		ui->ck_Uc->setCheckState(Qt::Checked);
	}
	else
	{
		ui->ck_Uc->setCheckState(Qt::Unchecked);
	}

	if (m_pAbnormalSMV->m_nCurChEnable[0]==1)
	{
		ui->ck_Ia->setCheckState(Qt::Checked);
	}
	else
	{
		ui->ck_Ia->setCheckState(Qt::Unchecked);
	}

	if (m_pAbnormalSMV->m_nCurChEnable[1]==1)
	{
		ui->ck_Ib->setCheckState(Qt::Checked);
	}
	else
	{
		ui->ck_Ib->setCheckState(Qt::Unchecked);
	}

	if (m_pAbnormalSMV->m_nCurChEnable[2]==1)
	{
		ui->ck_Ic->setCheckState(Qt::Checked);
	}
	else
	{
		ui->ck_Ic->setCheckState(Qt::Unchecked);
	}

	if (m_pAbnormalSMV->m_oSmvMsg.m_nUseOrigPkgSet)
	{
		ui->checkBox_SelOrgPkgSet->setCheckState(Qt::Checked);
	} 
	else
	{
		ui->checkBox_SelOrgPkgSet->setCheckState(Qt::Unchecked);
	}

	ui->pbn_MessageSet->setEnabled(m_pAbnormalSMV->m_oSmvMsg.m_nUseOrigPkgSet>0);
	connect(ui->ck_Ua,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ub,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Uc,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ia,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ib,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));
	connect(ui->ck_Ic,SIGNAL(stateChanged (int)),this,SLOT(slot_CkUabcIabcClicked()));

	ui->lne_jitter->setText(QString::number(m_pAbnormalSMV->m_uFrampShakingValue,10));
	ui->lne_errcmpt->setText(QString::number(m_pAbnormalSMV->m_nOutOfOrderValue,10));
	ui->lne_offsettime->setText(QString::number((int)m_pAbnormalSMV->m_nDelayDeviation,10));
	ui->lne_modifytime->setText(QString::number((int)m_pAbnormalSMV->m_nDelayChangeValue,10));
	
// 	m_ochannelNum.clear();
// 	for(int i=0;i<50;i++)
// 	{
// 		m_ochannelNum.append(m_pAbnormalSMV->m_nInvalidChanel[i]); //无效通道初值
// 	}

	initcmb_APPIDbyBlockData();
	ui->lne_sendcircle->setText(QString::number(m_pAbnormalSMV->m_nCircleNum_TypeCircle,10));
	ui->lne_circlepersecond->setText(QString::number(m_pAbnormalSMV->m_nCircleNum_TypeSecond,10));
	ui->lne_sendtime->setText(QString::number(m_pAbnormalSMV->m_nSendTime_TypeSecond,10));
	ui->lne_indexerr->setText(QString::number(m_pAbnormalSMV->m_nSeqNumDevtValue,10));
	ui->cmb_sendtype->setCurrentIndex(m_pAbnormalSMV->m_nSendMode);
}

void QSmvAbnormalParaset::setData(tmt_StateAbnormalSMV *pSMV,tmt_StateParas *pStateParas)
{
	m_pAbnormalSMV = pSMV;
	m_pStateParas = pStateParas;
	initData();
}

void QSmvAbnormalParaset::startInit()
{
	ui->pbn_set->setDisabled(true);
	ui->pbn_ChannelSelect->setDisabled(true);

	ui->cmb_APPID->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);

	ui->pbn_MessageSet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(true);
	ui->lne_sendcircle->setDisabled(true);
	ui->lne_circlepersecond->setDisabled(true);
	ui->lne_sendtime->setDisabled(true);

	ui->lne_flypointvolt->setDisabled(true);
	ui->lne_flypoitcurrent->setDisabled(true);
	ui->lne_jitter->setDisabled(true);
	ui->lne_errcmpt->setDisabled(true);
	ui->lne_offsettime->setDisabled(true);
	ui->lne_modifytime->setDisabled(true);

	ui->radio_lost->setDisabled(true);
	ui->radio_flypoint->setDisabled(true);
	ui->radio_jitter->setDisabled(true);
	ui->radio_errcmpt->setDisabled(true);
	ui->radio_delayoffset->setDisabled(true);
	ui->radio_delaymodify->setDisabled(true);
	ui->radio_indexerr->setDisabled(true);
	ui->radio_qualityinvalid->setDisabled(true);

	ui->ck_Ua->setDisabled(true);
	ui->ck_Ub->setDisabled(true);
	ui->ck_Uc->setDisabled(true);
	ui->ck_Ia->setDisabled(true);
	ui->ck_Ib->setDisabled(true);
	ui->ck_Ic->setDisabled(true);

	ui->radio_no->setDisabled(true);
	ui->lne_indexerr->setDisabled(true);

	ui->checkBox_SelOrgPkgSet->setEnabled(false);
//	ui->pbn_MessageSet->setEnabled(false);
}

void QSmvAbnormalParaset::stopInit()
{
	ui->pbn_set->setDisabled(false);
	ui->pbn_ChannelSelect->setDisabled(false);

	ui->cmb_APPID->setDisabled(false);
	ui->pbn_qualitySet->setDisabled(false);

//	ui->pbn_MessageSet->setDisabled(false);
	ui->cmb_sendtype->setDisabled(false);
	if (m_pAbnormalSMV->m_nSendMode) //按秒
	{
		ui->lne_sendcircle->setDisabled(true);
		ui->lne_circlepersecond->setDisabled(false);
		ui->lne_sendtime->setDisabled(false);
	}
	else       //按周波
	{ 
		ui->lne_sendcircle->setDisabled(false);
		ui->lne_circlepersecond->setDisabled(true);
		ui->lne_sendtime->setDisabled(true);
	}

	ui->lne_flypointvolt->setDisabled(false);
	ui->lne_flypoitcurrent->setDisabled(false);
	ui->lne_jitter->setDisabled(false);
	ui->lne_errcmpt->setDisabled(false);
	ui->lne_offsettime->setDisabled(false);
	ui->lne_modifytime->setDisabled(false);

	ui->radio_lost->setDisabled(false);
	ui->radio_flypoint->setDisabled(false);
	ui->radio_jitter->setDisabled(false);
	ui->radio_errcmpt->setDisabled(false);
	ui->radio_delayoffset->setDisabled(false);
	ui->radio_delaymodify->setDisabled(false);
	ui->radio_indexerr->setDisabled(false);
	ui->radio_qualityinvalid->setDisabled(false);

	ui->ck_Ua->setDisabled(false);
	ui->ck_Ub->setDisabled(false);
	ui->ck_Uc->setDisabled(false);
	ui->ck_Ia->setDisabled(false);
	ui->ck_Ib->setDisabled(false);
	ui->ck_Ic->setDisabled(false);

	ui->radio_no->setDisabled(false);
	ui->lne_indexerr->setDisabled(false);

	ui->checkBox_SelOrgPkgSet->setEnabled(true);
	ui->pbn_MessageSet->setEnabled(m_pAbnormalSMV->m_oSmvMsg.m_nUseOrigPkgSet>0);
}

void QSmvAbnormalParaset::slot_cmb_sendtypeChanged(int index)
{
	ui->cmb_sendtype->setCurrentIndex(index);
	if (index) //按秒
	{
		m_pAbnormalSMV->m_nSendMode = 1;
		ui->lne_sendcircle->setDisabled(true);
		ui->lne_circlepersecond->setDisabled(false);
		ui->lne_sendtime->setDisabled(false);
	}
	else       //按周波
	{ 
		m_pAbnormalSMV->m_nSendMode = 0;
		ui->lne_sendcircle->setDisabled(false);
		ui->lne_circlepersecond->setDisabled(true);
		ui->lne_sendtime->setDisabled(true);
	}
}

void QSmvAbnormalParaset::slot_lne_sendcircleChanged()
{
	QString str = ui->lne_sendcircle->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_sendcircle,this);

// 	int fv = str.toInt();
// 	if (fv<=0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>=255)
// 	{
// 		fv = 255;
// 	}
// 
// 	ui->lne_sendcircle->setText(QString::number(fv,10));
// 	m_pAbnormalSMV->m_nCircleNum_TypeCircle = fv;
}

void QSmvAbnormalParaset::slot_lne_sendcircleKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_sendcircle, TRUE);
	QString str = ui->lne_sendcircle->text();

	int fv = str.toInt();
	if (fv<=0)
	{
		fv = 0;
	}
	else if (fv>=255)
	{
		fv = 255;
	}

	ui->lne_sendcircle->setText(QString::number(fv,10));
	m_pAbnormalSMV->m_nCircleNum_TypeCircle = fv;
}

void QSmvAbnormalParaset::slot_lne_circlepersecondChanged()
{
	QString str = ui->lne_circlepersecond->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_circlepersecond,this);

// 	int fv = str.toInt();
// 	if (fv<=0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>=50)
// 	{
// 		fv = 50;
// 	}
// 
// 	ui->lne_circlepersecond->setText(QString::number(fv,10));
// 	m_pAbnormalSMV->m_nCircleNum_TypeSecond = fv;
}

void QSmvAbnormalParaset::slot_lne_circlepersecondKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_circlepersecond, TRUE);
	QString str = ui->lne_circlepersecond->text();

	int fv = str.toInt();
	if (fv<=0)
	{
		fv = 0;
	}
	else if (fv>=50)
	{
		fv = 50;
	}

	ui->lne_circlepersecond->setText(QString::number(fv,10));
	m_pAbnormalSMV->m_nCircleNum_TypeSecond = fv;
}

void QSmvAbnormalParaset::slot_lne_sendtimeChanged()
{
	QString str = ui->lne_sendtime->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_sendtime,this);

// 	int fv = str.toFloat();
// 	if (fv<=0)
// 	{
// 		fv = 0;
// 	}
// 
// 	fv = setLimit(0,999999,fv);
// 	ui->lne_sendtime->setText(QString::number(fv,10));
// 	m_pAbnormalSMV->m_nSendTime_TypeSecond = fv;
}

void QSmvAbnormalParaset::slot_lne_sendtimeKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_sendtime, TRUE);

	QString str = ui->lne_sendtime->text();

	int fv = str.toFloat();
	if (fv<=0)
	{
		fv = 0;
	}

	fv = setLimit(0,999999,fv);
	ui->lne_sendtime->setText(QString::number(fv,10));
	m_pAbnormalSMV->m_nSendTime_TypeSecond = fv;
}

void QSmvAbnormalParaset::slot_ck_losestepChanged(int state)
{
	
}

void QSmvAbnormalParaset::slot_radio_qualityinvalidChanged()
{
	if (ui->radio_qualityinvalid->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 8;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(false);
	ui->pbn_ChannelSelect->setDisabled(false);
	ui->pbn_qualitySet->setDisabled(false);
	ui->cmb_sendtype->setDisabled(true);
	ui->lne_sendcircle->setDisabled(true);
}

void QSmvAbnormalParaset::slot_pbn_AbnomalPointSet()
{
	int headflag;
	if (ui->radio_lost->isChecked())				//丢帧
	{
		headflag = 1;
	}
	else if (ui->radio_flypoint->isChecked())	//飞点
	{
		headflag = 2;
	}
	else if (ui->radio_jitter->isChecked())		//抖动
	{
		headflag = 3;
	}
	else if (ui->radio_errcmpt->isChecked())		//错序
	{
		headflag = 4;
	}

	QSmvAbnormalPointSet dig(headflag,m_oabnomalPointEnabled);
	dig.setFont(*g_pSttGlobalFont);
	connect(&dig,SIGNAL(sig_validPoint(QList<bool> &)),this,SLOT(slot_ValidPoint(QList<bool> &)));
	dig.exec();
}

void QSmvAbnormalParaset::slot_ptn_ChannelSelect()
{
	QSmvAbnormalChannelSelect dlg(m_pAbnormalSMV);
	dlg.setFont(*g_pSttGlobalFont);
//	connect(&dlg,SIGNAL(sig_ChannelOkClicked(QList<int> &)),this,SLOT(slot_ChannelNumOk(QList<int> &)));
	dlg.exec();
}

void QSmvAbnormalParaset::slot_pbn_MessageSet()
{
	QSmvAbnormalMessageSet dlg(&m_pAbnormalSMV->m_oSmvMsg,true,this);
	dlg.setWindowModality(Qt::WindowModal);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
#endif
	dlg.exec();

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSmvAbnormalParaset::slot_checkBox_SelOrgPkgSet_changed(int nState)
{
	if (m_pAbnormalSMV == NULL)
	{
		return;
	}

	m_pAbnormalSMV->m_oSmvMsg.m_nUseOrigPkgSet = (nState>0);
	ui->pbn_MessageSet->setEnabled(nState>0);
}

void QSmvAbnormalParaset::slot_pbn_qualitySet()
{
	QSmvAbnormalQualitySet dlg(m_olistQualityParas,this);
	dlg.setFont(*g_pSttGlobalFont);
	connect(&dlg,SIGNAL(sig_QualityPara(QList<int> &)),this,SLOT(slot_QualityParaChanged(QList<int> &)));
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
#endif
	dlg.exec();

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSmvAbnormalParaset::slot_QualityParaChanged(QList<int> &listQuality)
{
	for (int i=0;i<listQuality.size();i++)
	{
		m_pAbnormalSMV->m_nQualityBit[i] = listQuality.at(i);
		m_olistQualityParas[i] = listQuality.at(i);
	}
}

// void QSmvAbnormalParaset::slot_ChannelNumOk(QList<int> &channelnum)
// {
// // 	m_ochannelNum.clear();
// // 	if (channelnum.size()>0)
// // 	{
// // 		for (int i=0;i<channelnum.size();i++)
// // 		{
// // 			m_ochannelNum.append(channelnum.at(i));
// // 			m_pAbnormalSMV->m_nInvalidChanel[i] = channelnum.at(i);
// // 		}
// // 	}
// // 	else
// // 	{
// // 		m_ochannelNum.clear();
// // 	}
// }

void QSmvAbnormalParaset::slot_ValidPoint(QList<bool> &pointlist)
{
	m_oabnomalPointEnabled.clear();
	for (int i = 0;i<pointlist.size();i++)
	{
		m_oabnomalPointEnabled.append(pointlist.at(i));
		m_pAbnormalSMV->m_nAbnormalPoint[i] = pointlist.at(i);
	}
}

void QSmvAbnormalParaset::slot_lne_flypointvoltChanged()
{
	QString str = ui->lne_flypointvolt->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_flypointvolt,this);

// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 
// 	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
// 	ui->lne_flypointvolt->setText(QString::number(fv,'f',3));
// 	m_pAbnormalSMV->m_fFlyPointVolt = fv;
}
void QSmvAbnormalParaset::slot_lne_flypointvoltKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_flypointvolt, TRUE);
// 	QSttLineEdit* pEditLine = ui->lne_flypointvolt;
// 	QString str;
// 	GetWidgetBoard_DigitData(0,str,g_theTestCntrFrame);
// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();

	QString str = ui->lne_flypointvolt->text();

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,fv);
	ui->lne_flypointvolt->setText(QString::number(fv,'f',3));
	m_pAbnormalSMV->m_fFlyPointVolt = fv;
}


//void QSmvAbnormalParaset::slot_edit_Engchanged(QSttLineEdit* pEditLine, bool bIsNor)
//{
//	QString str;
//	GetEngWidgetBoard_DigitData(str, this);
//	pEditLine->setText(str);
//	pEditLine->SetEditFinished();
//}

//void QSmvAbnormalParaset::slot_edit_Digchanged(QSttLineEdit* pEditLine, bool bIsNor)
//{
//	QString str;
//	GetWidgetBoard_DigitData(4,str, this);
//	pEditLine->setText(str);
//	pEditLine->SetEditFinished();
//}



void QSmvAbnormalParaset::slot_lne_flypoitcurrentChanged()
{
	QString str = ui->lne_flypoitcurrent->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_flypoitcurrent,this);

// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 		
// 	fv = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,fv);
// 	ui->lne_flypoitcurrent->setText(QString::number(fv,'f',3));
// 	m_pAbnormalSMV->m_fFlyPointCurrent = fv;
}

void QSmvAbnormalParaset::slot_lne_flypointcurrentKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_flypoitcurrent, TRUE);
// 	QSttLineEdit* pEditLine = ui->lne_flypoitcurrent;
// 	QString str;
// 	GetWidgetBoard_DigitData(1,str,this);
// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();

	QString str = ui->lne_flypoitcurrent->text();

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,fv);
	ui->lne_flypoitcurrent->setText(QString::number(fv,'f',3));
	m_pAbnormalSMV->m_fFlyPointCurrent = fv;
}

void QSmvAbnormalParaset::slot_lne_jitterChanged()
{
	QString str = ui->lne_jitter->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_jitter,this);
// 
// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 		
// 	fv = setLimit(0,999999,fv);
// 	ui->lne_jitter->setText(QString::number((int)fv,10));
// 	m_pAbnormalSMV->m_uFrampShakingValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_jitterKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_jitter, TRUE);
	QString str = ui->lne_jitter->text();

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,999999,fv);
	ui->lne_jitter->setText(QString::number((int)fv,10));
	m_pAbnormalSMV->m_uFrampShakingValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_errcmptChanged()
{
	QString str = ui->lne_errcmpt->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_errcmpt,this);
	
// 	int fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 		
// 	fv = setLimit(0,999.999,fv);
// 	ui->lne_errcmpt->setText(QString::number((int)fv,10));
// 	m_pAbnormalSMV->m_nOutOfOrderValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_errcmptKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_errcmpt, TRUE);
	QString str = ui->lne_errcmpt->text();

	int fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,999.999,fv);
	ui->lne_errcmpt->setText(QString::number((int)fv,10));
	m_pAbnormalSMV->m_nOutOfOrderValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_offsettimeChanged()
{
	QString str = ui->lne_offsettime->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_offsettime,this);

// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 
// 	fv = setLimit(0,999999,fv);
// 	ui->lne_offsettime->setText(QString::number((int)fv,10));
// 	m_pAbnormalSMV->m_nDelayDeviation = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_offsettingKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_offsettime, TRUE);

	QString str = ui->lne_offsettime->text();

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,999999,fv);
	ui->lne_offsettime->setText(QString::number((int)fv,10));
	m_pAbnormalSMV->m_nDelayDeviation = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_modifytimeChanged()
{
	QString str = ui->lne_modifytime->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_modifytime,this);
	
// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{u
// 		fv = 0;
// 	}
// 
// 	fv = setLimit(0,999999,fv);
// 	ui->lne_modifytime->setText(QString::number((int)fv,10));
// 	m_pAbnormalSMV->m_nDelayChangeValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_modifytimeKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_modifytime, TRUE);
	QString str = ui->lne_modifytime->text();

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,999999,fv);
	ui->lne_modifytime->setText(QString::number((int)fv,10));
	m_pAbnormalSMV->m_nDelayChangeValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_indexerrChanged()
{
	QString str = ui->lne_indexerr->text();

	GetWidgetBoard_DigitData(4,str,ui->lne_indexerr,this);
	
// 	int fv = str.toInt();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 
// 	fv = setLimit(0,999.999,fv);
// 	ui->lne_indexerr->setText(QString::number(fv,10));
// 	m_pAbnormalSMV->m_nSeqNumDevtValue = (int)fv;
}

void QSmvAbnormalParaset::slot_lne_indexerrKeyBoard()
{
	//this->slot_edit_Digchanged(ui->lne_indexerr, TRUE);

	QString str = ui->lne_indexerr->text();

	int fv = str.toInt();
	if (fv<0)
	{
		fv = 0;
	}

	fv = setLimit(0,999.999,fv);
	ui->lne_indexerr->setText(QString::number(fv,10));
	m_pAbnormalSMV->m_nSeqNumDevtValue = (int)fv;
}

void QSmvAbnormalParaset::slot_radio_lostClicked()
{
	if (ui->radio_lost->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 1;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(true);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);
	InitUI_BySendType();
}

void QSmvAbnormalParaset::slot_radio_flypointClicked()
{
	if (ui->radio_flypoint->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 3;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(true);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);
	InitUI_BySendType();
}

void QSmvAbnormalParaset::slot_radio_jitterClicked()
{
	if (ui->radio_jitter->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 2;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(true);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);
	InitUI_BySendType();
}

void QSmvAbnormalParaset::slot_radio_errcmptClicked()
{
	if (ui->radio_errcmpt->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 4;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(true);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);
	InitUI_BySendType();
}

void QSmvAbnormalParaset::slot_radio_delayoffsetClicked()
{
	if (ui->radio_delayoffset->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 5;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(false);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);

	ui->cmb_sendtype->setDisabled(true);
	ui->lne_sendcircle->setDisabled(true);
	ui->lne_circlepersecond->setDisabled(true);
	ui->lne_sendtime->setDisabled(true);
// 	InitUI_BySendType();
}

void QSmvAbnormalParaset::slot_radio_delaymodifyClicked()
{
	if (ui->radio_delaymodify->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 6;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(false);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);

	ui->cmb_sendtype->setDisabled(true);
	ui->lne_sendcircle->setDisabled(true);
	ui->lne_circlepersecond->setDisabled(true);
	ui->lne_sendtime->setDisabled(true);

// 	InitUI_BySendType();

}

void QSmvAbnormalParaset::slot_radio_indexerrClicked()
{
	if (ui->radio_indexerr->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 7;
	}

	Global_SetSvAbnormalTmtValues_ByIecConfig(m_pAbnormalSMV,true);
	ui->pbn_set->setEnabled(false);
	ui->pbn_ChannelSelect->setDisabled(true);
	ui->pbn_qualitySet->setDisabled(true);
	ui->cmb_sendtype->setDisabled(false);

	ui->cmb_sendtype->setDisabled(true);
	ui->lne_sendcircle->setDisabled(true);
	ui->lne_circlepersecond->setDisabled(true);
	ui->lne_sendtime->setDisabled(true);

// 	InitUI_BySendType();
}

void QSmvAbnormalParaset::slot_CkUabcIabcClicked()
{
	if (ui->ck_Ua->isChecked())
	{
		m_pAbnormalSMV->m_nVolChEnable[0] = 1;
	}
	else
	{
		m_pAbnormalSMV->m_nVolChEnable[0] = 0;
	}

	if (ui->ck_Ub->isChecked())
	{
		m_pAbnormalSMV->m_nVolChEnable[1] = 1;
	}
	else
	{
		m_pAbnormalSMV->m_nVolChEnable[1] = 0;
	}

	if (ui->ck_Uc->isChecked())
	{
		m_pAbnormalSMV->m_nVolChEnable[2] = 1;
	}
	else
	{
		m_pAbnormalSMV->m_nVolChEnable[2] = 0;
	}

	if (ui->ck_Ia->isChecked())
	{
		m_pAbnormalSMV->m_nCurChEnable[0] = 1;
	}
	else
	{
		m_pAbnormalSMV->m_nCurChEnable[0] = 0;
	}

	if (ui->ck_Ib->isChecked())
	{
		m_pAbnormalSMV->m_nCurChEnable[1] = 1;
	}
	else
	{
		m_pAbnormalSMV->m_nCurChEnable[1] = 0;
	}

	if (ui->ck_Ic->isChecked())
	{
		m_pAbnormalSMV->m_nCurChEnable[2] = 1;
	}
	else
	{
		m_pAbnormalSMV->m_nCurChEnable[2] = 0;
	}
}

void QSmvAbnormalParaset::slot_cmb_APPIDChanged(int index)
{
	if (index<0)
	{
		return;
	}

	//m_pAbnormalSMV->m_oSmvMsg.m_nAppID = m_olistAppIDs.at(index);
		m_pAbnormalSMV->m_nGroupIndex = index;
	Global_SetSvAbnormalData(index,m_pStateParas);
	//SetAbnSmvMessage(p92Data);
	//g_pStateTest->m_bTmtParaChanged = TRUE;
	
}

// CIecCfg92Data* QSmvAbnormalParaset::GetSMVDataByIndex(int nFindIndex)
// {
// 	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
// 	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
// 	POS pos = pIecCfgDatasSMV->GetHeadPosition();
// 	long nCurrIndex = 0;
// 
// 	while(pos)
// 	{
// 		pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);
// 
// 		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
// 		{
// 			continue;
// 		}
// 
// 		if (pIecCfgSmvData->m_nUseFlag == 0)
// 	{
// 			continue;
// 	}
// 
// 		if (nCurrIndex == nFindIndex)
// 	{
// 			CIecCfg92Data* p92Data = (CIecCfg92Data*)pIecCfgSmvData;
// 			return p92Data;
// 		}
// 
// 		nCurrIndex++;
// 	}
// 
// 	return NULL;
// // 	long nFindIndex = 0;
// // 
// // 	g_pStateTest->GetSMVDataAppIDs(m_olistAppIDs);
// // 
// // 	if (nFindIndex == nIndex)
// // 	{
// // 		return;
// // 	}
// // 	else
// // 	{
// // 		nFindIndex++;
// // 	}
// 	}

//BOOL QSmvAbnormalParaset::SetAbnSmvMessage(CIecCfg92Data* pIecCfgSmvData)
//{
//	if (pIecCfgSmvData == NULL)
//	{
//		return FALSE;
//	}
//
//	CString_to_char(pIecCfgSmvData->m_strDestAddress, m_pAbnormalSMV->m_oSmvMsg.m_strMacAddrDst);
//	CString_to_char(pIecCfgSmvData->m_strSrcAddress, m_pAbnormalSMV->m_oSmvMsg.m_strMacAddrSrc);
//	m_pAbnormalSMV->m_oSmvMsg.m_nAppID = pIecCfgSmvData->m_dwAppID;
//	m_pAbnormalSMV->m_oSmvMsg.m_nVLanID = pIecCfgSmvData->m_dwVID;
//	m_pAbnormalSMV->m_oSmvMsg.m_nVLanPriority = pIecCfgSmvData->m_nPriority;
//	m_pAbnormalSMV->m_oSmvMsg.m_nVersion = pIecCfgSmvData->m_dwVersion;
//	CString_to_char(pIecCfgSmvData->m_strSVID, m_pAbnormalSMV->m_oSmvMsg.m_strSVID);
//	CString_to_char(pIecCfgSmvData->m_strDataSet, m_pAbnormalSMV->m_oSmvMsg.m_strDataset);
//	m_pAbnormalSMV->m_oSmvMsg.m_nSyn = pIecCfgSmvData->m_nSyn;
//	return TRUE;
//}

void QSmvAbnormalParaset::initcmb_APPIDbyBlockData()
{
	disconnect(ui->cmb_APPID,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_APPIDChanged(int)));
	ui->cmb_APPID->clear();

	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
	CIecCfg92Data *p92Data = NULL;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	long nFindIndex = 0,nCtrlBlockIndex = 0;

	while(pos)
	{
		pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);

		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		if (pIecCfgSmvData->m_nUseFlag == 0)
		{
			continue;
		}

		p92Data = (CIecCfg92Data*)pIecCfgSmvData;

		QString appidstr = QString::number(nCtrlBlockIndex+1,10) + tr("_0x")+QString::number(p92Data->m_dwAppID,16);
			ui->cmb_APPID->addItem(appidstr);

		if(m_pAbnormalSMV->m_nGroupIndex == p92Data->m_dwAppID)
		{
			nFindIndex = nCtrlBlockIndex;
		}

		nCtrlBlockIndex++;
	}

	ui->cmb_APPID->setCurrentIndex(m_pAbnormalSMV->m_nGroupIndex);
	ui->cmb_APPID->setDisabled(false);
//	ui->pbn_MessageSet->setDisabled(false);
	connect(ui->cmb_APPID,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_APPIDChanged(int)));
}

void QSmvAbnormalParaset::slot_radio_noClicked()
{
	if (ui->radio_no->isChecked())
	{
		m_pAbnormalSMV->m_nAbnormalType = 0;
		ui->left_group->setEnabled(false);
	}
	else
	{
		ui->left_group->setEnabled(true);
	}
}
