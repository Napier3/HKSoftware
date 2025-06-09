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
	strTmp = "�����IEC���á������ñ�Ⱥ�ͨ������";
	m_pIecConfig_Label = new QLabel(strTmp,this);

	//���û���
	m_pIecConfig_Label->setWordWrap(true);
	//��������
	m_pIecConfig_Label->setFont(*g_pSttGlobalFont);
	//�Զ�������С
	m_pIecConfig_Label->adjustSize();
	//���þ���
	//m_pIecConfig_Label->setAlignment(Qt::AlignCenter);
}

void QSttAssistShowTips::slot_Timer_CloseDialog()
{
	close();
}

//��̬Ч��ִ�к���
void QSttAssistShowTips::ast_Exec(long nTimeGap)
{
	
}

//ֹͣ��̬Ч��ִ��
void QSttAssistShowTips::ast_Stop()
{
	
}