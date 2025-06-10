#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../Module/Main/SttXMainFrameBase.h"
#include "../../Module/TestClient/SttMacroTestInterface.h"
#include <QToolButton>

class QSttNativeMainFrameLinux : public QSttXMainFrameBase, CTestEventBaseInterface
{
    Q_OBJECT

public:
    explicit QSttNativeMainFrameLinux(QWidget *parent = 0);
    virtual ~QSttNativeMainFrameLinux();

	QToolButton m_oBatteryBtn;//zhouyangyong ���ڵ�ص�����ʾ
	bool m_bConnected;//2024-1-3 zhouyangyong �Ƿ�����
	long m_nBatCapValue;
	long m_nPowerAC;
	CString m_strCurrStyleString;
	CString m_strBatCapString;//���ڸ��µ�ص���
	QTimer m_oTimerForConnect;//���ڴ�����ܴ���������ͻ
	int m_nConnectCnt;//��������ʮ��
	void InitBatteryBtn();//��ʼ��������ʾ
	void UpdateBatteryState(int nState);//���µ�����ʾ
	virtual long OnRtData(CSttParas *pParas);
	virtual long OnDisConnect();

	long m_nTesterVerIdx; //xueyangfan 20240622 ʵʱ����VerIdxֵ �����������ʾ
#ifdef USE_IN_Astra_LINUX
	bool eventFilter(QObject *, QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
#endif
private:
	bool m_bLeftPressed;
	QPoint m_ptStart;

signals:
	void sig_UpdateBatteryState();

public slots:
	void slot_UpdateBatteryState();
	void slot_SttConnect();

};

#endif // MAINWINDOW_H
