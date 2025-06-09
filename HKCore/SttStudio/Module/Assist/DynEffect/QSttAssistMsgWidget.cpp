#include "QSttAssistMsgWidget.h"
#include "ui_QSttAssistMsgWidget.h"
#include "SttAssistWndDynEffExecTool.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SttStyleSheetGlobalDefine.h"

QSttAssistMsgWidget::QSttAssistMsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSttAssistMsgWidget)
{
    ui->setupUi(this);

 	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
 	setAttribute(Qt::WA_TranslucentBackground, true);
	setVisible(false);

	ui->m_txtMsg->setStyleSheet(STT_StyleSheet_AssistMsgTips);
	ui->m_txtMsg->setFont(*g_pSttGlobalFont);
}

QSttAssistMsgWidget::~QSttAssistMsgWidget()
{
    delete ui;
}

void QSttAssistMsgWidget::ShowMsg(const CString &strMsg, long nShowTimeLong)
{
	ShowMsgEx("", strMsg, nShowTimeLong);
}

QRect QSttAssistMsgWidget::CalTextRect(const CString &strWndID, const CString &strMsg)
{
	//文字区域
	QFontMetrics fm(ui->m_txtMsg->font());
	QRect rcText = fm.boundingRect(strMsg);

	//窗体区域
	QRect rcSrcWnd;
	assist_get_widget_msg_pos(strWndID, rcSrcWnd);
	QRect rcFrame = g_theTestCntrFrame->geometry();
	long nMaxLen = 200;  //后面开放到全局设置里面
	long nTextHeight = rcText.height();

	if (rcText.width() < nMaxLen)
	{
		nMaxLen = rcText.width() + ASSIST_MSG_WND_GAP;
	}
	else
	{
		nTextHeight = rcText.width() / nMaxLen + 1;
		nTextHeight *= rcText.height();
	}

	QRect rcMsgWnd;
	
	if (rcSrcWnd.left() + nMaxLen > rcFrame.right())
	{
		rcMsgWnd.setLeft(rcFrame.right() - nMaxLen - ASSIST_MSG_WND_GAP); //
	}
	else
	{
		rcMsgWnd.setLeft(rcSrcWnd.left());
	}

	if (rcSrcWnd.bottom() + nTextHeight > rcFrame.bottom())
	{
		rcMsgWnd.setTop(rcSrcWnd.top() - nTextHeight - ASSIST_MSG_WND_GAP);
	}
	else
	{
		rcMsgWnd.setTop(rcSrcWnd.bottom());
	}

	rcMsgWnd.setHeight(nTextHeight + ASSIST_MSG_WND_GAP);
	rcMsgWnd.setWidth(nMaxLen + ASSIST_MSG_WND_GAP);

	return rcMsgWnd;
}

void QSttAssistMsgWidget::ShowMsgEx(const CString &strWndID, const CString &strMsg, long nShowTimeLong)
{
	QString strText = strMsg;
	int AntoIndex = 0;
	long nMaxLen = 200;
	QFont font = ui->m_txtMsg->font();
	QFontMetrics fm(font);

	if (!strText.isEmpty())//dingxiaoya 20240131 解决保存模板提示文字显示不全
	{
		int  nStrlen, nStrlenAll = 0;
		for (int i = 1; i < strText.size() + 1; i++)
		{
			nStrlenAll = fm.width(strText.left(i));
			nStrlen = nStrlenAll - AntoIndex * (nMaxLen + ASSIST_MSG_WND_GAP - 20);
            if (nStrlen >= (nMaxLen + ASSIST_MSG_WND_GAP - 20)) //当strText宽度大于最大宽度的时候添加换行符，20为距离边界距离可以调整
			{
				int nFm = fm.width(strText.left(i));
				AntoIndex++;
				strText.insert(i - 1, "\n");	
			}
		}
	}

	ui->m_txtMsg->setText(strText);
	//ui->m_txtMsg->setText(strMsg);
	m_nTimeLong = nShowTimeLong;
	QRect rcWnd = CalTextRect(strWndID, strText);
	show();
	setGeometry(rcWnd);
}

//动态效果执行函数
void QSttAssistMsgWidget::ast_Exec(long nTimeGap)
{
	CSttAssistWndDynEffectBase::ast_Exec(nTimeGap);

	QRect rcWnd = geometry();
	QObject *pParent = parent();

	if (m_bIsStoped)
	{
		hide();
	}

}

//停止动态效果执行
void QSttAssistMsgWidget::ast_Stop()
{
	m_bIsStoped = true;
}

