#ifndef STATEMONITOR_H
#define STATEMONITOR_H

#include <QWidget>
#include <QTabWidget>
#include "TimeResponseWidget.h"
#include "QReadWriteLock"

class QStateMonitor : public QWidget
{
	Q_OBJECT

public:
	QStateMonitor(bool bIsEx = false ,QWidget *parent = 0);
	virtual ~QStateMonitor();
	void UpdateStateMonitorChs();//zhouhj 20220321  更新软件资源后,重新更新此视图

private:
	virtual void initUI();

public:
	QReadWriteLock lock;

	QGridLayout* m_pLay;
	QTimeResponseWidget* m_pTimeResponseWidget;
	bool m_bIsPlotEx;//是否是单通道模式	
	bool m_bIsGradient;//如果是递变类型,则需要按照dLastTime来更新图表
	void UpdateCurChannal(int nChannel, int type, bool bStart);
	void UpdateCurveData();
	void UpdateCurveData(CChlTimeResponsePlotEx* pChlTimePlotEx, double dLastTime);
	void SetModeGradient(bool bIsGradient);
	void InitConnection(QWidget* parent);

	void UpdateStateMonitor(bool bIsPlotEx);

private slots:
	void slot_YChanged(changed_type type, QString str,float down,float up);
};

extern QStateMonitor* g_pStateMonitor; 

#endif //!STATEMONITOR_H