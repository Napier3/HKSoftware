#include "SttAssistShowTips.h"

#include "../SttAssistEngine.h"
#include "SttAssistWndDynEffExecTool.h"

QSttAssistShowTips::QSttAssistShowTips(QWidget *parent)
	: QDialog(parent)
{
	InitUI();

	connect(&m_oTimerCloseDialog,   SIGNAL(timeout()),    this,   SLOT(slot_Timer_CloseDialog()));
	m_oTimerCloseDialog.start(10000);
}

QSttAssistShowTips::~QSttAssistShowTips()
{

}

void QSttAssistShowTips::InitUI()
{
	//setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
	//resize(300,40);

	QWidget *pFind = assist_find_widget("IECConfig");
	QRect rcPos = pFind->geometry();
	//QPoint pt = rcPos.topLeft();//, rcPos.bottomLeft)
	QPoint pt = rcPos.bottomLeft();
	pt.setX(pt.x() - rcPos.width() / 2);
	pt = pFind->mapToGlobal(pt);
	move(pt);
	//move(400,50);

	CString strTmp;
	strTmp = "点击“IEC配置”，配置变比和通道参数";
	m_pIecConfig_Label = new QLabel(strTmp,this);

	//设置换行
	m_pIecConfig_Label->setWordWrap(true);
	//设置字体
	m_pIecConfig_Label->setFont(*g_pSttGlobalFont);
	//自动调整大小
	m_pIecConfig_Label->adjustSize();
	//设置居中
	//m_pIecConfig_Label->setAlignment(Qt::AlignCenter);
}

void QSttAssistShowTips::slot_Timer_CloseDialog()
{
	close();
}

//动态效果执行函数
void QSttAssistShowTips::ast_Exec(long nTimeGap)
{
	
}

//停止动态效果执行
void QSttAssistShowTips::ast_Stop()
{
	
}