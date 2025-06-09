#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "BinTimeResponsePlot.h"
#include "ChlTimeResponsePlot.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

class PlotWidget : public QWidget
{
	Q_OBJECT

public:
	PlotWidget(QWidget *parent = 0);
	~PlotWidget();

	void initUI(CSttMacroChannels *pChls,double fUMin,double fUMax
		,double fIMin,double fIMax
		,long *pBinInData,long nBinInNum
		,long *pBinOutData,long nBinOutNum);
	void Free();

	int d_timerId;
	void stop();
	void start();
protected:
	virtual void timerEvent( QTimerEvent * );

public:
	virtual void OnRtDataChanged();
	virtual void OnRtSwitchChanged(double fLastTime);

signals:
	void sig_ChlUpdateCurve(double,BOOL);
	void sig_SwitchUpdateCurve(double,BOOL);

public:
	CExBaseList m_oUChls;
	CExBaseList m_oIChls;
	QList<CChlTimeResponsePlot *> m_oChlTimePlotList;
	CBinTimeResponsePlot *m_pBinInTimeResponsePlot;
	CBinTimeResponsePlot *m_pBinOutTimeResponsePlot;
	QVBoxLayout *m_pVLayout;
};

#endif // PLOTWIDGET_H
