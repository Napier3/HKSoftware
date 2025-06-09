#ifndef _TimeResponseWidget_H
#define _TimeResponseWidget_H

#include <QWidget>
#include <QTableWidget>
#include "ChlTimeResponsePlotEx.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "BinBoutTimeResponsePlot.h"

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
		,double fIMin,double fIMax,long *pBinInData,long *pBinOutData,int type = 0);//20210908 sf 兼容幅值相位频率
	void UpdateUI(CSttMacroChannels *pChls,double fUMin,double fUMax
		,double fIMin,double fIMax,long *pBinInData,long *pBinOutData,int type = 0);
	void Free();

	int d_timerId;
	void stop();
	void start();

	bool m_bInitSync;
	bool isSyncInit(){	 return m_bInitSync;  }

protected:
	virtual void timerEvent( QTimerEvent * );

public:
	virtual void OnRtDataChanged();

signals:
	void sig_ChlUpdateCurveEx();

public:
	CExBaseList m_oUChls;
	CExBaseList m_oIChls;
	QList<CChlTimeResponsePlotEx *> m_oChlTimePlotList;	//电压、电流左右分布分组显示曲线列表
	CChlTimeResponsePlotEx* m_pChlTimePlotEx;//单通道使用
	QGridLayout *m_pLayout;

	QTabWidget *m_tabWidget;

	CBinBoutTimeResponsePlot* m_pBinBoutInTimeResponsePlot;

};

#endif // PLOTWIDGET_H
