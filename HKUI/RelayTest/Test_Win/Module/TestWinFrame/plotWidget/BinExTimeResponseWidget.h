#ifndef _BinExTimeResponseWidget_H
#define _BinExTimeResponseWidget_H

#include <QWidget>
#include "BinTimeResponsePlot.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

class QBinExTimeResponseWidget : public QWidget
{
	Q_OBJECT

public:
	QBinExTimeResponseWidget(QWidget *parent = 0);
	~QBinExTimeResponseWidget();

	void initUI(long *pBinInData,long nBinInNum,long *pBinOutData,long nBinOutNum);
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
	void sig_SwitchUpdateCurve(double,BOOL);

public:
	CBinTimeResponsePlot *m_pBinInTimeResponsePlot;
	CBinTimeResponsePlot *m_pBinOutTimeResponsePlot;
	QVBoxLayout *m_pVLayout;
};

#endif // PLOTWIDGET_H
