#ifndef QSTTRECORD_CH_COMPARE_PLOT_H
#define QSTTRECORD_CH_COMPARE_PLOT_H

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
#include <qwt_text_label.h>
#include <QPushButton>
#include <QMouseEvent>
#include "../../UI/Module/SttUIDefine.h"

enum SttRecordChType{STT_RECORD_CH_TYPE_I=0,STT_RECORD_CH_TYPE_U};

class QSttRecordChComparePlot: public QwtPlot
{
	Q_OBJECT
public:
	QSttRecordChComparePlot(SttRecordChType type, QWidget * = NULL );
	virtual ~QSttRecordChComparePlot();

	void insertCurve(QVector<double> &values, QColor color, bool show = true);
	void insertInputCurve(QVector<double> &values, bool show = true);
	void insertInputCurve(double *pValues,int nPoints, bool show = true);
	void insertOutputCurve(QVector<double> &values, bool show = true);
	void insertOutputCurve(double *pdValues, int nPoints,bool show = true);
	void UpdateLocationPoints();
	bool existCurve(const QString& title);
	void clearCurve();
	void UpdateYInterval(float fv);
	void UpdateTips();

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouse_event();
protected:
	virtual void showEvent( QShowEvent * );

	public Q_SLOTS:
		void showCurve(const QString& title, bool on);
		void showCurve(QwtPlotItem *, bool on);
private:
	double m_dt1; 
	double m_dt2;
	double m_dinterval;

	QVector<QwtPlotCurve *> d_curves;
	QwtPlotCurve *m_pLocationPoints;//定位点(这里用不显示线段的折线图绘制)
	QPointF m_oLPoints[2];//定位点信息

	QwtPlotPicker *d_picker;//显示鼠标当前坐标

	QwtPlotMarker *d_origin;//x轴标注线
	QwtPlotMarker *m_pLeftRangeLine;//左定位线
	QwtPlotMarker *m_pRightRangeLine;//右定位线
	QwtTextLabel *d_setTipText1;
	QwtTextLabel *d_setTipText2;
	QwtText qwtText1;
	QwtText qwtText2;
	QString m_strTipText1;
	QString m_strTipText2;
	QPainter *m_pPainter;
	QPushButton *m_BtnMagnify;
	QPushButton *m_BtnResize;
	QwtInterval d_interval;//x轴刻度范围

private slots:
	void on_m_BtnMagnify_Clicked();
	void on_m_BtnResize_Clicked();
};

#endif