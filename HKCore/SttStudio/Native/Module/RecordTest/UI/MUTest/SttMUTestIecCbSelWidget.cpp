#include "stdafx.h"
#include "SttMUTestIecCbSelWidget.h"
#include "../../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../UI/SttTestCntrCmdDefine.h" 
#include "../../../UI/SttTestCntrFrameBase.h" 
#include "../SttIecRecordDetectWidget.h"
#include "../../../XLangResource_Native.h"



extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;
QSttMUTestIecCbSelWidget *g_pSttMUTestIecCbSelWidget;

QSttMUTestIecCbSelWidget::QSttMUTestIecCbSelWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pGridIecCb_CBSel = NULL;

	InitUI();
//	ShowAllCapDevice();//zhouhj 2023.11.8 �ڴ����ö����,�����ˢ�º�������ˢ����ʾ���
	assist_widget_show("AssistIecCbSelWidget", this, true);
}

QSttMUTestIecCbSelWidget::~QSttMUTestIecCbSelWidget()
{
}

void QSttMUTestIecCbSelWidget::ShowAllCapDevice()
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	if (g_theXSmartCapMngr->m_pX61850Cap == NULL)
	{
		return;
	}

	m_pGridIecCb_CBSel->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
	m_oTickCount_CBSel.Enter();

// 	if (isHidden())
// 	{
// 		show();
// 		m_oTickCount_CBSel.DoEvents(5);
// 	}
}

void QSttMUTestIecCbSelWidget::InitUI()
{
	//20240701Xuzt ����Qt::X11BypassWindowManagerHint��ʾ��X11���ö�
	//����Ϊ�ޱ�����ͼ�ꡢ�ڱ߿��ö�
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::X11BypassWindowManagerHint);
	setFont(*g_pSttGlobalFont);
	resize(950*g_dUIShowCoef, 400*g_dUIShowCoef);

	CString strTemp;
	strTemp = /*_T("��ѡ����ƿ�")*/g_sLangTxt_Gradient_ControlB; //lcq
	setWindowTitle(strTemp);


	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setEnabled(false);
	//m_pOK_PushButton->setText(tr("ȷ��"));
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);
	//m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	//m_pCancel_PushButton->setText(tr("ȡ��"));
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);
	//m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));
	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
	m_pOK_CancelHLayout->addSpacing(20);
	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);
	//main

	m_pMain_VLayout = new QVBoxLayout(this);

	m_pGridIecCb_CBSel = new CSttIecCbGrid(this);
	m_pGridIecCb_CBSel->setObjectName("AstSttIecCbGrid");
	m_pGridIecCb_CBSel->InitGrid();
	m_pGridIecCb_CBSel->AttachDataViewOptrInterface(this);

	m_pMain_VLayout->addWidget(m_pGridIecCb_CBSel);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(&m_oTimer_MUTest,SIGNAL(timeout()),this,SLOT(slot_Timer()));
}

void QSttMUTestIecCbSelWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	//����ѡ��
	g_pSttIecRecordDetectWidget->ast_ExecCmd(Event_ID_IecSelCb, "");

	long nPkgType = CPDCLASSID_DEVICE92;

	if (m_pGridIecCb_CBSel->m_bViewFT3)
	{
		nPkgType = CPDCLASSID_DEVICE6044;
	}

	long nSelCount = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetSelectDeviceCount(nPkgType);

	if (nSelCount>1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,/*_T("ֻ��ѡ��һ������ֵ���ƿ�")*/g_sLangTxt_Onlyselect.GetString()); //lcq
	}

	m_pOK_PushButton->setEnabled(nSelCount == 1);
}

BOOL QSttMUTestIecCbSelWidget::IsFT3MUTest()
{
	return m_pGridIecCb_CBSel->m_bViewFT3;
}

void QSttMUTestIecCbSelWidget::Refresh_MUTest()
{
	BOOL bIsHidden = isHidden();

	if (bIsHidden)
	{
		m_pGridIecCb_CBSel->ShowDatas(NULL);
//		m_oTickCount_CBSel.DoEvents(10);
		show();
	}

	m_oTimer_MUTest.stop();

// 	if (g_pSttIecRecordCbWidget->IsTabUI_Mode())
// 	{
// 		g_pSttIecRecordCbWidget->
// 	}

	if (g_theSttIecRecordMainWidget != NULL)
	{
		g_theSttIecRecordMainWidget->ClearAll_StartDetect();
	}

	m_oTickCount_CBSel.Enter();

	if (bIsHidden)
	{
		m_pGridIecCb_CBSel->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
//		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("bIsHidden==1"));
	}

	m_oTimer_MUTest.start(500);
}

void QSttMUTestIecCbSelWidget::slot_OKClicked()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMUTestIecCbSelWidget::slot_OKClicked()"));
	m_pOK_PushButton->setEnabled(false);
//	assist_widget_show("AssistIecCbSelWidget", this, false);
	hide();
	m_oTickCount_CBSel.DoEvents(10);
//	g_theAssistWndDynEffExecTool->Stop("AstSttIecCbGrid");//ֹͣ����ʾ��һֱ��ʾ
//	g_theTestCntrFrame->OnCmd_IecCap();
	g_pSttIecRecordDetectWidget->ast_ExecCmd(STT_CMD_TYPE_ATS_BeginRecord, "");
// 	g_theAssistWndDynEffExecTool->ShowMsgEx("m_btnSysSet", "�����ť���б������", 10000);
// 	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_TemplateView,"","",50000);
// 	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IecCap,"","",50000);
}

void QSttMUTestIecCbSelWidget::slot_CancelClicked()
{
//	assist_widget_show("AssistIecCbSelWidget", this, false);
	hide();
// 	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_TemplateView,"","",50000);
// 	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IecCap,"","",50000);
// 	g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,_T("����˰�ť,ѡ�����ֵ���ƿ�,���б��ļ���."),50000);
}

void QSttMUTestIecCbSelWidget::slot_Timer()
{
	if (isHidden())
	{
		return;
	}

	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	if (g_theXSmartCapMngr->m_pX61850Cap == NULL)
	{
		return;
	}

	long nPkgType = CPDCLASSID_DEVICE92;

	if (m_pGridIecCb_CBSel->m_bViewFT3)
	{
		nPkgType = CPDCLASSID_DEVICE6044;
	}

	long nDetectDevCount = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetDeviceCount(nPkgType);

	if (nDetectDevCount != 1)
	{
		return;
	}

	long nCurrTime = m_oTickCount_CBSel.GetTickCountLong(FALSE);

	if (nCurrTime>1000)//�������¿��ƿ���������1s,ֻ��һ��9-2���ƿ�,�򽫸ÿ��ƿ�����Ϊ�ϲ���Ԫ����ʹ�ÿ��ƿ�
	{
		CCapDeviceBase *pCapDevice = 
			(CCapDeviceBase*)g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.FindByClassID(nPkgType);
		pCapDevice->m_bSelect = 1;
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMUTestIecCbSelWidget::slot_Timer()"));
		disconnect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
		hide();//zhouhj 2024.3.25 ������,��ֹFT3ʱ,������ʾ���ĳ��Ȳ�һ��,������ʾ
		m_oTickCount_CBSel.DoEvents(10);

		if (g_pSttIecRecordDetectWidget->ast_ExecCmd(STT_CMD_TYPE_ATS_BeginRecord, ""))
		{
			m_oTimer_MUTest.stop();

		}
		else
		{
			show();
		}
		
		connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	}
}

