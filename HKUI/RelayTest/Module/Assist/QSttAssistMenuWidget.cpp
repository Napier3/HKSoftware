#include "QSttAssistMenuWidget.h"
#include "ui_QSttAssistMenuWidget.h"
#include "DynEffect/SttAssistWndDynEffExecTool.h"
#include "../UI/SttTestCntrFrameBase.h"
#include "../UI/SttTestCntrCmdDefine.h"
#include "DynEffect/SttAssistWndDynEffExecTool.h"
#include "../XLangResource_Native.h"

#include "../../../Module/XLanguage/XLanguageResource.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../UI/Controls/SttCheckBox.h"

#ifdef _PSX_QT_LINUX_
#include "../UI/SttEventFilter/SttEventFilter.h"
extern QSttEventFilter *g_pSttEventFilter;
#endif


QSttAssistMenuWidget::QSttAssistMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSttAssistMenuWidget)
{
    ui->setupUi(this);

 	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
 	//setAttribute(Qt::WA_TranslucentBackground, true);
	setVisible(false);
}

QSttAssistMenuWidget::~QSttAssistMenuWidget()
{
    delete ui;
}

void QSttAssistMenuWidget::ShowMenu()
{
//	//QString strFlashStyle =  "border-radius:6px; border:2px rgb(0,0,0);border-style:outset; ";
//	//setStyleSheet(strFlashStyle);
//	setFont(*g_pSttGlobalFont);
//    xlang_SetLangStrToWidget_Txt(ui->m_btnHelp, g_sLangTxt_Help,XLang_Ctrls_QPushButton); //帮助 lcq
//	xlang_SetLangStrToWidget_Txt(ui->m_btnTestTeach, g_sLangTxt_Gradient_TestTeach,XLang_Ctrls_QPushButton); //测试教学 lcq
//	xlang_SetLangStrToWidget_Txt(ui->m_btnShowTips, g_sLangTxt_PromptMessage,XLang_Ctrls_QPushButton); //提示信息 lcq
//	ui->m_btnHelp->setFont(*g_pSttGlobalFont);
//	ui->m_btnTestTeach->setFont(*g_pSttGlobalFont);
//	ui->m_btnShowTips->setFont(*g_pSttGlobalFont);
//
//	QRect rcWnd = CalWidgetRect();
//	setGeometry(rcWnd);
//	show();
//#ifdef _PSX_QT_LINUX_
//    g_pSttEventFilter->m_pWidgetForHide = this;
//#endif

	// 如果窗口当前是隐藏的，则显示窗口，并设置窗口大小  20240510 xueyangfan 固定博电图标大小
	if (!isVisible()) 
	{
		setFont(*g_pSttGlobalFont);
		xlang_SetLangStrToWidget_Txt(ui->m_btnHelp, g_sLangTxt_Help,XLang_Ctrls_QPushButton); //帮助 lcq
		xlang_SetLangStrToWidget_Txt(ui->m_btnTestTeach, g_sLangTxt_Gradient_TestTeach,XLang_Ctrls_QPushButton); //测试教学 lcq
		xlang_SetLangStrToWidget_Txt(ui->m_ChkShowTips, g_sLangTxt_PromptMessage,XLang_Ctrls_QPushButton); //提示信息 lcq
		ui->m_btnHelp->setFont(*g_pSttGlobalFont);
		ui->m_btnTestTeach->setFont(*g_pSttGlobalFont);
		ui->m_ChkShowTips->setFont(*g_pSttGlobalFont);

		QRect rcWnd = CalWidgetRect();
		setGeometry(rcWnd);
		show();
#ifdef _PSX_QT_LINUX_
		g_pSttEventFilter->m_pWidgetForHide = this;
#endif
	} 
	else 
	{
		// 如果窗口当前是显示的，则隐藏窗口
		hide();
	}
}

QRect QSttAssistMenuWidget::CalWidgetRect()
{
	//窗体区域
	QRect rcSrcWnd;
	assist_get_widget_msg_pos("Assist", rcSrcWnd);  //助手图标按钮
	QRect rcFrame = g_theTestCntrFrame->geometry();

	QRect rcWnd = geometry();
	QRect rcTipWnd;
	

	long nTmp1 = rcFrame.right();
	long nTmp2 = rcWnd.width();
	rcTipWnd.setLeft(rcFrame.right()  - rcWnd.width() - 5);
	rcTipWnd.setTop(rcSrcWnd.top() - rcWnd.height());
	rcTipWnd.setBottom(rcSrcWnd.top() - 1);
	rcTipWnd.setRight(rcFrame.right() - 5);

	return rcTipWnd;
}

void QSttAssistMenuWidget::on_m_btnHelp_clicked()
{
	bool bTipsState = ui->m_ChkShowTips->isChecked(); //20240524 xueyangfan 勾选显示提示信息 不勾选不显示。
	if (bTipsState)
	{
		//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSttAssistEngine::assist_show_menu : not impleted"));
		g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_TemplateView,"","",5000);
		g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_IECConfig,"","",5000);
		g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_ReportView,"","",5000);
		g_theAssistWndDynEffExecTool->Flash(STT_CNTR_CMD_StartTest,"","",5000);

		//g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_ReportView, "报告视图，点击此按钮，查看测试报告",5000);
		g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_ReportView, g_sLangTxt_Reporttest.GetString(),5000);
		//g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_StartTest, "开始测试，点击此按钮，开始测试",5000);
		g_theAssistWndDynEffExecTool->ShowMsgEx(STT_CNTR_CMD_StartTest, g_sLangTxt_starttest.GetString(),5000);
		//g_theAssistWndDynEffExecTool->ShowMsgEx("Exit", "关闭，点击此按钮，关闭测试程序", 0);
		//g_theAssistWndDynEffExecTool->ShowMsgEx("", "通用提示信息，类似于输出栏显示的提示信息，此提示信息可以消失",5000);
		g_theAssistWndDynEffExecTool->ShowMsgEx("", g_sLangTxt_General.GetString(),5000);

		g_theTestCntrFrame->ast_ExecCmd("MenuCmd", STT_CNTR_CMD_ReportView);
	}
	else
	{
		hide();
	}

#ifdef _PSX_QT_LINUX_
    g_pSttEventFilter->m_pWidgetForHide = NULL;
#endif
}

void QSttAssistMenuWidget::on_m_btnTestTeach_clicked()
{
#ifdef _PSX_QT_LINUX_
    g_pSttEventFilter->m_pWidgetForHide = NULL;
#endif
	hide();
}

void QSttAssistMenuWidget::on_m_ChkShowTips_clicked()
{
#ifdef _PSX_QT_LINUX_
    g_pSttEventFilter->m_pWidgetForHide = NULL;
#endif
	hide();
}

bool QSttAssistMenuWidget::event(QEvent *event)
{
	if(QEvent::WindowDeactivate == event->type()) 
	{
		hide(); //这里就是啦！
	}

	return QWidget::event(event);
}

