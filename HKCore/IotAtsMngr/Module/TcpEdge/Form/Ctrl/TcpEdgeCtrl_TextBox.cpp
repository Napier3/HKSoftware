#include "stdafx.h"
#include "TcpEdgeCtrl_TextBox.h"

CTcpEdgeCtrl_TextBox::CTcpEdgeCtrl_TextBox(QWidget *parent)
{
	m_bStop = false;
	m_pClearAction = NULL;
	m_pStopAction = NULL;
	m_pContinueAction = NULL;

	setContextMenuPolicy(Qt::CustomContextMenu);

	QAction* pAction = m_oMenu.addAction("复制(&C)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuCopy(bool)));
	pAction = m_oMenu.addAction("全选(&A)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuSelectAll(bool)));
	m_pClearAction = m_oMenu.addAction("清空(&D)");
	connect(m_pClearAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuClear(bool)));
	m_oMenu.addSeparator();
	m_pStopAction = m_oMenu.addAction("暂停打印(&P)");
	connect(m_pStopAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuStop(bool)));
	m_pContinueAction = m_oMenu.addAction("继续打印(&O)");
	connect(m_pContinueAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuContinue(bool)));
	m_pContinueAction->setEnabled(false);

	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slot_showMenu(const QPoint&)));
}

CTcpEdgeCtrl_TextBox::~CTcpEdgeCtrl_TextBox()
{

}

QString CTcpEdgeCtrl_TextBox::LogString(long nLevel, const char *strMsg)
{
	if(nLevel < XLOGLEVEL_EDGE_INFO || m_bStop)
	{
		return "";
	}

	CString strTemp;
	strTemp = strMsg;
	return LogString(nLevel, strTemp);
}

QString CTcpEdgeCtrl_TextBox::LogString(long nLevel, const QString &strMsg)
{
	if(nLevel < XLOGLEVEL_EDGE_INFO || m_bStop)
	{
		return "";
	}

	UINT nMaxLen = document()->lineCount();

	if (nMaxLen > 100000)
	{
		clear();
	}

	QString strLog;
	QDateTime date = QDateTime::currentDateTime();
	QString strTime = date.toString("yyyy年MM月dd日 HH时mm分ss秒z毫秒");

	switch(nLevel)
	{
	case XLOGLEVEL_EDGE_PKG_UP:
		strLog = QString(_T("【%1】【上行报文】\n%2\n")).arg(strTime).arg(strMsg);
		break;
	case XLOGLEVEL_EDGE_PKG_DOWN:
		strLog = QString(_T("【%1】【下行报文】\n%2\n")).arg(strTime).arg(strMsg);
		break;
	case XLOGLEVEL_EDGE_PKG_RSLT:
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XLOGLEVEL_EDGE_INFO:
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XLOGLEVEL_EDGE_ERR:
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XLOGLEVEL_EDGE_DEBUG:
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XERRTYPE_LACKNECESSITY://必需项缺失
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XERRTYPE_RETURNFALSE://执行失败报文里返回的错误信息
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XERRTYPE_TIMEOUT://超时
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XERRTYPE_NECESSITYERR://必需项错误（格式错误
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	case XERRTYPE_RANGEOUT://返回值超范围
		strLog = QString(_T("【%1】%2\n")).arg(strTime).arg(strMsg);
		break;
	default:
		break;
	}

	append(strLog);
	return strLog;
}

void CTcpEdgeCtrl_TextBox::UsePkgAction(bool bUse)
{
	m_pClearAction->setVisible(bUse);
	m_pContinueAction->setVisible(bUse);
	m_pStopAction->setVisible(bUse);
}

void CTcpEdgeCtrl_TextBox::slot_showMenu(const QPoint& pt)
{
	m_oMenu.move(cursor().pos());
	m_oMenu.show();
}

void CTcpEdgeCtrl_TextBox::slot_menuCopy(bool checked)
{
	copy();
}

void CTcpEdgeCtrl_TextBox::slot_menuSelectAll(bool checked)
{
	selectAll();
}

void CTcpEdgeCtrl_TextBox::slot_menuClear(bool checked)
{
	clear();
}

void CTcpEdgeCtrl_TextBox::slot_menuStop(bool checked)
{
	m_pStopAction->setEnabled(false);
	m_pContinueAction->setEnabled(true);
	m_bStop = true;
}

void CTcpEdgeCtrl_TextBox::slot_menuContinue(bool checked)
{
	m_pStopAction->setEnabled(true);
	m_pContinueAction->setEnabled(false);
	m_bStop = false;
}