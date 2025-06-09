#ifndef QStateMonitorWidgetImp_H
#define QStateMonitorWidgetImp_H

#include "StateMonitorWidget.h"
#include "../../QSttInfWidgetBase.h"

class QStateMonitorWidgetImp : public QSttInfWidgetBase, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	explicit QStateMonitorWidgetImp(QWidget *parent=0);
	~QStateMonitorWidgetImp();

public:
	virtual void showEvent(QShowEvent *);

protected:
	QStateMonitorWidget *m_pStateMonitor;

	bool m_bModeIsSingle; //true-单通道,false-多通道
	int m_nChannel;
	int m_nType;
	bool m_bStart;
	QWidget* m_pConnectWidget;

//////////////////////////////////////////////////////////////////////////
public://CSttRtDataChangeEvent
	virtual void OnRtDataChanged();//抽象虚函数,实现收到实时数据后的处理

public:
	virtual void InitStateMonitor(int nChannel, int nType, bool bStart, QWidget* pConnectWidget = NULL);
	virtual void AddBinBoutPoint(long nIndex, double x, double y);

	virtual void StopStateMonitor();
	virtual void StartStateMonitor();
	virtual void UpdateLocalTime(double dLocalTime);
	virtual void UpdateStateMonitorChs();
	void SetSingle(bool bSingle);
	void UpdatePlotYType(int nType);//mod wangtao 20240910 新增参数,区分多通道模块下，低周和其他模块的Y轴显示文本

private:
	void SetSingle();
	void InitStateMonitor();

};

#endif // QStateMonitorWidgetImp_H
