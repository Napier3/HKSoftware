#include "QSttAssistTipsShowWidget.h"
#include "ui_QSttAssistTipsShowWidget.h"
#include "SttAssistWndDynEffExecTool.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SttStyleSheetGlobalDefine.h"

QSttAssistTipsShowWidget::QSttAssistTipsShowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSttAssistTipsShowWidget)
{
    ui->setupUi(this);

 	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
 	//setAttribute(Qt::WA_TranslucentBackground, true);
	setVisible(false);

	setStyleSheet(STT_StyleSheet_AssistMsgTips);
	setFont(*g_pSttGlobalFont);
}

QSttAssistTipsShowWidget::~QSttAssistTipsShowWidget()
{
    delete ui;
}

QRect QSttAssistTipsShowWidget::CalWidgetRect()
{
	//窗体区域
	QRect rcSrcWnd;
	assist_get_widget_msg_pos("Assist", rcSrcWnd);  //助手图标按钮
	QRect rcFrame = g_theTestCntrFrame->geometry();

	QRect rcWnd = geometry();
	QRect rcTipWnd;
	
	rcTipWnd.setLeft(rcFrame.right() - rcWnd.width() - ASSIST_MSG_WND_GAP);
	rcTipWnd.setTop(rcSrcWnd.top() - rcWnd.height() - ASSIST_MSG_WND_GAP);
	rcTipWnd.setBottom(rcSrcWnd.top() - 1);
	rcTipWnd.setRight(rcFrame.right() - 5);

	return rcTipWnd;
}

//动态效果执行函数
void QSttAssistTipsShowWidget::ast_Exec(long nTimeGap)
{
}

//停止动态效果执行
void QSttAssistTipsShowWidget::ast_Stop()
{
	
}


void QSttAssistTipsShowWidget::on_m_chkShowAtStart_clicked()
{

}

void QSttAssistTipsShowWidget::on_m_btnNext_clicked()
{

}

void QSttAssistTipsShowWidget::on_m_btnPrev_clicked()
{

}

void QSttAssistTipsShowWidget::on_m_btnClose_clicked()
{

}
