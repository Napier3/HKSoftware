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
	void Refresh_MUTest();//刷新合并单元测试,重新开始探测
	BOOL IsFT3MUTest();//是否为ADMU测试

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();//20230214 zhouhj 根据北京测试反馈,该提示助手支持"取消",取消后可在"报文探测"按钮一直闪烁提示,后续通过该界面选择控制块
	void slot_Timer();
};

extern QSttMUTestIecCbSelWidget *g_pSttMUTestIecCbSelWidget;

#endif // STTMUTESTIECCBSELWIDGET_H
