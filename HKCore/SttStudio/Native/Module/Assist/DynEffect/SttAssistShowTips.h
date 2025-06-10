#ifndef STTASSISTSHOWTIPS_H
#define STTASSISTSHOWTIPS_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QFont>

#include "SttAssistWndDynEffectBase.h"

class QSttAssistShowTips : public QDialog, public CSttAssistWndDynEffectBase
{
	Q_OBJECT

public:
	QSttAssistShowTips(QWidget *parent = NULL);
	~QSttAssistShowTips();

private:
	QLabel *m_pIecConfig_Label;
	QTimer m_oTimerCloseDialog;

public:
	void InitUI();

	//��̬Ч��ִ�к���
	virtual void ast_Exec(long nTimeGap);

	//ֹͣ��̬Ч��ִ��
	virtual void ast_Stop();

private slots:
	void slot_Timer_CloseDialog();
	
};

#endif // STTASSISTIECCONFIGDIALOG_H
