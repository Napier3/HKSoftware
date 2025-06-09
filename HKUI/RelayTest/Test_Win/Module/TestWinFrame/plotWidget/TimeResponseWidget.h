#ifndef _TimeResponseWidget_H
#define _TimeResponseWidget_H

#include <QWidget>
#include <QTableWidget>
#include "BinTimeResponsePlot.h"
#include "ChlTimeResponsePlot.h"
#ifdef _GRADIENT_PLOT_
#include "ChlTimeResponsePlotEx.h"
#endif
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#define MODE_COMMON		0x01
#define MODE_GRADIENT	0x02
#define MODE_STATE		0x03

class QTimeResponseWidget : public QWidget, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	QTimeResponseWidget(QWidget *parent = 0);
	~QTimeResponseWidget();

	void initUI(CSttMacroChannels *pChls,double fUMin,double fUMax
		,double fIMin,double fIMax
		,long *pBinInData,long nBinInNum
		,long *pBinOutData,long nBinOutNum,int type = 0);//20210908 sf 兼容幅值相位频率
	void Free();

	int d_timerId;
	void stop();
	void start();

	bool m_bInitSync;
	bool isSyncInit(){	 return m_bInitSync;  }
	void SetUseTesterTime(BOOL bUse){m_bUseTesterTime = bUse;}
	BOOL IsUseTesterTime(){return m_bUseTesterTime;}

protected:
	virtual void timerEvent( QTimerEvent * );

private://2023.6.13 zhouhj  新增
	double m_dLocalTime;//测试仪底层上送的实时绝对时间
	double m_dRealTime; //测试过程监视图实时解析的各数据的绝对时间
	BOOL m_bUseTesterTime;//是否使用测试仪内部时间 

public:
	virtual void OnRtDataChanged();
	virtual void OnRtSwitchChanged(double fLastTime);
	virtual void UpdateLocalTime(double dLocalTime);

	void ChangeListType(int type,double fUMin,double fUMax,double fIMin,double fIMax);//修改电压电流多通道显示类型

	virtual void AddBinPoint(long nIndex, double x, double y);
	virtual void AddBoutPoint(long nIndex, double x, double y);

signals:
	void sig_ChlUpdateCurve();
	void sig_RtUpdata();

#ifdef _GRADIENT_PLOT_
	void sig_ChlUpdateCurveEx();
#endif

	void sig_SwitchInUpdateCurve();
	void sig_SwitchOutUpdateCurve();

public slots:
#ifdef _GRADIENT_PLOT_
	void slot_UpdateCurveData();
#endif
	void slot_RtDataChanged();


public:
	CExBaseList m_oUChls;
	CExBaseList m_oIChls;
	QList<CChlTimeResponsePlot *> m_oChlTimePlotList;	//电压、电流左右分布分组显示曲线列表
#ifdef _GRADIENT_PLOT_
	CChlTimeResponsePlotEx *m_pChlTimePlotEx;			//单多通道切换显示曲线
#endif
	CBinTimeResponsePlot *m_pBinInTimeResponsePlot;
	CBinTimeResponsePlot *m_pBinOutTimeResponsePlot;
	QVBoxLayout *m_pVLayout;
	QTabWidget *m_tabWidget;
};

#endif // PLOTWIDGET_H
