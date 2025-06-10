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

	QToolButton m_oBatteryBtn;//zhouyangyong 用于电池电量显示
	bool m_bConnected;//2024-1-3 zhouyangyong 是否联机
	long m_nBatCapValue;
	long m_nPowerAC;
	CString m_strCurrStyleString;
	CString m_strBatCapString;//用于更新电池电量
	QTimer m_oTimerForConnect;//用于处理可能存在联机冲突
	int m_nConnectCnt;//尝试联机十次
	void InitBatteryBtn();//初始化电量显示
	void UpdateBatteryState(int nState);//更新电量显示
	virtual long OnRtData(CSttParas *pParas);
	virtual long OnDisConnect();

	long m_nTesterVerIdx; //xueyangfan 20240622 实时数据VerIdx值 更新鼠标光标显示
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
