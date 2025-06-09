#ifndef _SingleChlTimeResponsePlot_H
#define _SingleChlTimeResponsePlot_H

#include "TimeResponsePlotBase.h"

#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../Module/SttTestResourceMngr/RtDataMngr/SttMacroChannels.h"

#define NANOSECOND 1.0e9

class CSingleChlTimeResponsePlot: public CTimeResponsePlotBase
{
public:
	CSingleChlTimeResponsePlot(QWidget * = NULL );
	virtual ~CSingleChlTimeResponsePlot();

	void setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList);

	virtual void start();
	virtual void stop();
	virtual void initCurve();
	virtual void updateCurve(double fv,BOOL bChanged);
	
	void updatePlot();

	void updateXScale(float f1, float f2);
	void updateYScale(changed_type type,QString str,float f1,float f2);
	void updateYTtile(QString str);
	void setYLeftRightScale(changed_type type,float fstart,float fend,int num);

	void setData( int nChannel, int type, unsigned int nSecond, unsigned int nNanoSecond, bool bStart);
	CSttMacroChannel* GetMacroChannel(int nChannel);
protected:
	virtual void timerEvent( QTimerEvent * );
	
private:
	CExBaseList m_oChlUDatasList;
	CExBaseList m_oChlIDatasList;
	CSttMacroChannel* m_pCurMacroChannel;

	int m_nChannel;
	int m_ChangeType;

	volatile bool m_bGet;
	bool m_bGradient;
	int d_timerId;

	QwtSystemClock d_clock;

	QwtPlotPicker *d_picker;
	QwtPlotMarker *d_origin;
	QLabel *m_PlotLabelText;

	QwtPlotCurve *m_pCurve;

	unsigned int m_nStartSecond;
	unsigned int m_nStartNanoSecond;

	bool m_bStart;
};

#endif