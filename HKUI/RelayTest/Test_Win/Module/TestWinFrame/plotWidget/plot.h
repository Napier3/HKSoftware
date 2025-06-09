#ifndef PLOT_H
#define PLOT_H

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
#include <qwt_plot_renderer.h>
#include <QLabel>

#include "../../Define.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotDirectPainter;

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;

#define  LINENUM	18
#define  INPUT		10			
#define  OUTPUT		8
#define  SPACE		3

class Plot: public QwtPlot
{
	Q_OBJECT
public:
	Plot(QWidget * = NULL );
	virtual ~Plot();
	void stop();
	void start();
	void initCurve();
	void updateYScale(float f1,float f2);
	void updateYTtile(QString str);
	void updateXScale(float f1, float f2);
	void clearCurveData();
	void setPropertyofPlot(plugin_type type,int UModuleNum,int IModuleNum,QList<int> UModultChannelNumList,QList<int> IModultChannelNumList);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR);

protected:
	virtual void timerEvent( QTimerEvent * );

public Q_SLOTS:
	void setIntervalLength( double );
	
private:
	void updateCurve(double fv);
	void incrementInterval();

	int d_timerId;
	QwtSystemClock d_clock;
	QwtInterval d_interval;
	QwtInterval d_Yinterval;
	QwtInterval d_YRight;

	QList<QwtPlotCurve *> m_CurveList;
	QList<QVector<QPointF>> m_CurveDataList;

	int m_nUCHNum;
	int m_nICHNum;

	QwtPlotPicker *d_picker;
	QwtPlotMarker *d_origin;
	QLabel *m_PlotLabelText;

	QLabel *m_labYellow;
	QLabel *m_labGreen;
	QLabel *m_labRed;
	QLabel *m_labPurple;
	QLabel *m_labWhite;

	bool m_bRecevied;
	bool bYScaleFlag;

	tmt_channel* m_pVOL;	
	tmt_channel* m_pCUR;
	
	plugin_type m_type;//模拟、数字、小信号

	int m_nUModuleNum;//电压模块数
	int m_nIModuleNum;//电流模块数
	QList<int> m_UModultChannelNumList;//各电压模块的通道数
	QList<int> m_IModultChannelNumList;//各电流模块的通道数
};

#endif