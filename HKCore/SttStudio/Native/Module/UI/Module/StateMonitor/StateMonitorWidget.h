#ifndef STATEMONITORWIDGET_H
#define STATEMONITORWIDGET_H

#include <QTabWidget>
#include <QGridLayout>
#include "StateMonitorVoltCur.h"
#include "StateMonitorBinBout.h"
#include "../../../SttTestResourceMngr/RtDataMngr/SttGlobalRtDataMngr.h"

class QStateMonitorWidget : public QWidget, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	QStateMonitorWidget(QWidget *parent = 0);
	virtual ~QStateMonitorWidget();

protected:
	virtual void timerEvent(QTimerEvent* event);

public:
	virtual void InitStateMonitor(int nChannel, int nType, bool bStart, QWidget* pConnectWidget = NULL);
	virtual void StopStateMonitor();
	virtual void StartStateMonitor();
	virtual void ClearStateMonitor();
	virtual void UpdateStateMonitorChs();
	virtual void OnRtDataChanged();
	virtual void UpdateLocalTime(double dLocalTime);
	virtual void AddBinBoutPoint(long nIndex, double x, double y);
	bool IsSingle() { return m_bModeIsSingle; }
	void SetSingle(bool bSingle);

	void ChangeListType(int type,double fUMin,double fUMax,double fIMin,double fIMax);//修改电压电流多通道显示类型

private:
	QTabWidget m_tabWidget;
	QGridLayout m_oLayout; //电压电流通道和开入开出
	long m_nTimerID;
	bool m_bModeIsSingle; //true-单通道,false-多通道

	CExBaseList m_oUChls;
	CExBaseList m_oIChls;

	double m_dLocalTime;
	double m_dRealTime;

	QStateMonitorVoltCur* m_pSingle;
	QList<QStateMonitorVoltCur*> m_oVoltCurList;
	QStateMonitorBinBout* m_pBinBout;

private:
	virtual void InitUI();
	virtual void InitCurve(CSttMacroChannels *pChls,double fUMin,double fUMax
		,double fIMin,double fIMax,long *pBinInData,long *pBinOutData);
	void UpdateCurve();

private slots:
	void slot_YRangeChanged(changed_type tagType, QString strText, float fDown, float fUp);
};

extern QStateMonitorWidget* g_pStateMonitorWidget; 

#endif //!STATEMONITORWIDGET_H