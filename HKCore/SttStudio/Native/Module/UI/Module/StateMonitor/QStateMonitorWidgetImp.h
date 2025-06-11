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

// public:
// 	virtual void showEvent(QShowEvent *);

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
// 	void SetPlotDigitMaxMinValue(int nChangedType);
	void SetPlotDigitMaxMinValue( int nChangedType,double fUMin,double fUMax,double fIMin,double fIMax );//20241030 suyang 设置状态图电压电流大小
	double m_dUMin,m_dUMax,m_dIMin,m_dIMax;
	void SetParaSetSecondValue(int nParaSetSecondValue);
	int m_nParaSetSecondValue;

private:
	void SetSingle();
	void InitStateMonitor();

//2024-9-10 lijunqing 优化系统程序启动的效率
protected:
	bool m_bHasInitFinished;  //是否已经初始化完成，没有初始化，不能进行操作
	virtual void showEvent(QShowEvent *event);
	void InitStateMonitorWidget();

};

#endif // QStateMonitorWidgetImp_H
