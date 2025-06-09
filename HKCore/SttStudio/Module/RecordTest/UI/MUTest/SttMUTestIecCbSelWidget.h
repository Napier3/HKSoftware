#ifndef STTMUTESTIECCBSELWIDGET_H
#define STTMUTESTIECCBSELWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

#include "../SttIecCbGrid.h"

class QSttMUTestIecCbSelWidget : public QWidget, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttMUTestIecCbSelWidget(QWidget *parent = 0);
	virtual ~QSttMUTestIecCbSelWidget();

	void ShowAllCapDevice();

public:
	CSttIecCbGrid *m_pGridIecCb_CBSel;
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOK_CancelHLayout;
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;
	QTimer m_oTimer_MUTest;
	CTickCount32 m_oTickCount_CBSel;

public:
	void InitUI();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	void Refresh_MUTest();//ˢ�ºϲ���Ԫ����,���¿�ʼ̽��
	BOOL IsFT3MUTest();//�Ƿ�ΪADMU����

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();//20230214 zhouhj ���ݱ������Է���,����ʾ����֧��"ȡ��",ȡ�������"����̽��"��ťһֱ��˸��ʾ,����ͨ���ý���ѡ����ƿ�
	void slot_Timer();
};

extern QSttMUTestIecCbSelWidget *g_pSttMUTestIecCbSelWidget;

#endif // STTMUTESTIECCBSELWIDGET_H
