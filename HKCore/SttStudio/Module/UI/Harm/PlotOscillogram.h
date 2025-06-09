#ifndef PLOT_WAVE_H
#define PLOT_WAVE_H

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
#include "../Module/SttUIDefine.h"

enum SttHarmTableType{TYPE_V=0,TYPE_I};


class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotDirectPainter;

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;

class PlotOscillogram: public QwtPlot
{
	Q_OBJECT
public:
	PlotOscillogram(SttHarmTableType type, QWidget * = NULL );
	virtual ~PlotOscillogram();

	void insertCurve( const QString& title, QVector<double> &values,  QColor color, bool show = true);
	bool existCurve(const QString& title);
	void clearCurve();
	void UpdateYInterval(float fv);
	QString exportPlot(QString name);
protected:
	virtual void showEvent( QShowEvent * );
	virtual void resizeEvent( QResizeEvent * );

	public Q_SLOTS:
		void showCurve(const QString& title, bool on);
		void showCurve(QwtPlotItem *, bool on);
private:

	QVector<QwtPlotCurve *> d_curves;
	QwtPlotMarker *d_mrk1;
	QwtPlotMarker *d_mrk2;

	QwtPlotPicker *d_picker;
	QwtPlotPanner *d_panner;
	QwtPlotZoomer *d_zoomer[2];

	QwtPlotMarker *d_origin;
	QwtPlotDirectPainter *d_directPainter;

	QwtInterval d_interval;
	int d_timerId;

	QwtSystemClock d_clock;
	bool m_bstart;

};

#endif