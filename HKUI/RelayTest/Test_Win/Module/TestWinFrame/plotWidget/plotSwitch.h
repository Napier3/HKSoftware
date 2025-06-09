#ifndef PLOTSWITCH_H
#define PLOTSWITCH_H

#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_system_clock.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_picker.h>
#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_panner.h>
#include <qregexp.h>
#include <qapplication.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_canvas.h>
#include <qwt_painter.h>
#include <qwt_plot_layout.h>
#include <qwt_point_data.h>
#include <qwt_system_clock.h>
#include <qwt_plot_directpainter.h>
#include <qwt_curve_fitter.h>
#include <QVBoxLayout>
#include <QLabel>

#include "../../Define.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTest/Common/tmt_result_def.h"

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotDirectPainter;

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;

#define  LINENUM	18
#define  INPUT		8		
#define  OUTPUT		8
#define  SPACE		3

class PlotSwitch: public QwtPlot
{
	Q_OBJECT
public:
	PlotSwitch(QWidget * = NULL );
	virtual ~PlotSwitch();

	void setData(CEventResult* pEvent);
	void setSwitchInData();
	void setSwitchOutData();

	void updatePlotSwitch();

	void stop();
	void start();
	void updateYScale(float f1,float f2);
	void updateYTtile(QString str);
	void updateXScale(float f1, float f2);
	void clearCurveData();
	
protected:
	virtual void timerEvent( QTimerEvent * );

public Q_SLOTS:
	void setIntervalLength( double );
	
private:
	void initSwitchCurve();
	void updateCurve(double fv);
	void incrementInterval();

	int d_timerId;
	QwtInterval d_interval;
	QwtInterval d_Yinterval;
	QwtInterval d_YRight;

	QwtPlotCurve *d_curveIn[INPUT];
	QVector<QPointF> m_curveDataIn[INPUT];

	QwtPlotCurve *d_curveOut[OUTPUT];
	QVector<QPointF> m_curveDataOut[OUTPUT];

	QList<QwtPlotCurve *> m_CurveList;
	QList<QVector<QPointF>> m_CurveDataList;
	int m_TotCurNum;
	
	QwtPlotPicker *d_picker;
	QwtPlotMarker *d_origin;
	QLabel *m_PlotLabelText;
	QLabel *m_labYellow;
	QLabel *m_labGreen;
	QLabel *m_labRed;
	bool m_bRecevied;
	
//	SwitchStatus* m_pSwitchStatus;
	CEventResult/*tmt_EventResult*/* m_pEvent;

	int m_SwitchIn[INPUT];
	int m_SwitchOut[OUTPUT];
};

#endif