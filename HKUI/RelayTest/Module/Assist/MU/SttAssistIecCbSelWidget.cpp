#include "SttAssistIecCbSelWidget.h"

#include "../../SmartCap/XSmartCapMngr.h"

#include "stdafx.h"
#include "SttAssistWzd_MuTest.h"
#include "../../UI/SttTestCntrCmdDefine.h" 
#include "../../UI/SttTestCntrFrameBase.h" 

//#include "SttAssistIecConfigDialog.h"
#include "../../Module/RecordTest/UI/SttIecRecordDetectWidget.h"
#include "SttAssistIecCbSelWidget.h"
#include "../DynEffect/SttAssistWndDynEffExecTool.h"

extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;

QSttAssistIecCbSelWidget::QSttAssistIecCbSelWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::QSttAssistIecCbSelWidget)
{
	ui->setupUi(this);
	ui->m_btnOk->setEnabled(false);

	//设置为无标题栏图标、黑边框、置顶	
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setFont(*g_pSttGlobalFont);
	resize(900, 400);

	m_pGridIecCb = new CSttIecCbGrid(this);
	m_pGridIecCb->setObjectName("AstSttIecCbGrid");
	m_pGridIecCb->InitGrid();
	ui->m_vlayGrid->insertWidget(0,m_pGridIecCb);
	m_pGridIecCb->AttachDataViewOptrInterface(this);
	ShowAllCapDevice();
	assist_widget_show("AssistIecCbSelWidget", this, true);
}

QSttAssistIecCbSelWidget::~QSttAssistIecCbSelWidget()
{
	delete ui;
}

void QSttAssistIecCbSelWidget::ShowAllCapDevice()
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	if (g_theXSmartCapMngr->m_pX61850Cap == NULL)
	{
		return;
	}

	m_pGridIecCb->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
}

void QSttAssistIecCbSelWidget::InitUI()
{
	
}

void QSttAssistIecCbSelWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	//更新选择
	g_pSttIecRecordDetectWidget->ast_ExecCmd(Event_ID_IecSelCb, "");

	long nSelCount = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetSelectDeviceCount(CPDCLASSID_DEVICE92);

	if (nSelCount>1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("只能选择一个采样值控制块"));
	}

	ui->m_btnOk->setEnabled(nSelCount == 1);
}

void QSttAssistIecCbSelWidget::on_m_btnOk_clicked()
{
	assist_widget_show("AssistIecCbSelWidget", this, false);
	hide();
	g_theAssistWndDynEffExecTool->Stop("AstSttIecCbGrid");//停止该提示的一直显示
	g_theTestCntrFrame->OnCmd_IecCap();
	g_pSttIecRecordDetectWidget->ast_ExecCmd(STT_CMD_TYPE_ATS_BeginRecord, "");
	g_theAssistWndDynEffExecTool->ShowMsgEx("m_btnSysSet", "点击按钮进行变比设置", 10000);
	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_TemplateView,"","",50000);
	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IecCap,"","",50000);
}

void QSttAssistIecCbSelWidget::on_m_btnCancel_clicked()
{
	assist_widget_show("AssistIecCbSelWidget", this, false);
	hide();
// 	g_theAssistWndDynEffExecTool->Stop("AstSttIecCbGrid");//停止该提示的一直显示
// 	g_theTestCntrFrame->OnCmd_IecCap();
// 	g_pSttIecRecordDetectWidget->ast_ExecCmd(STT_CMD_TYPE_ATS_BeginRecord, "");
// 	g_theAssistWndDynEffExecTool->ShowMsgEx("m_btnSysSet", "点击按钮进行变比设置", 10000);
	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_TemplateView,"","",50000);
	g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IecCap,"","",50000);
	g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,_T("点击此按钮,监视报文通道信息."),50000);
//	g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_IecCap,_T("点击此按钮,选择采样值控制块,进行报文监视."),50000);
}

