#ifndef _TimeResponsePlotBase_H
#define _TimeResponsePlotBase_H

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

#include <QTime>
#include <qwt_picker_machine.h>
#include <qwt_scale_widget.h>
#include <QLayout>
#include <QFont>

#include "../SttUIDefine.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTest/Common/tmt_result_def.h"

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotDirectPainter;

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;

#define  SPACE		0.5

#define MAX_BIN_CNT	10
#define MAX_BIN_EX_CNT	128
#define MAX_COLOR_NUM	16

#define STATE_UPDATE_FREE		0x00
#define STATE_UPDATE_TIMER		0x01
#define STATE_UPDATE_CHANGE		0x02

extern QColor g_arrCurveColor[MAX_COLOR_NUM];
extern QString GetCurveStyleSheetString(long nColorIndex);

//自画坐标轴,以字符方式显示所有的通道
class BinBoutYScaleDraw: public QwtScaleDraw        
{
public:
	BinBoutYScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		if(v <= g_nBinCount)
		{
			return QwtText(QString("   %1").arg(QChar('A' - 1 + (int)v)));
		}
		else if(v <= 20)
		{
			return QwtText(QString("   %1").arg((int)v - g_nBinCount));		
		}
		else
		{
			return QwtText(" ");
		}
	}
};

class BinCharYScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	BinCharYScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		double fVal = 0;
		double fabsVal = fabs(v);

		if (fabsVal < 13.9 || fabsVal > (6*MAX_BIN_CNT + 8.1))
		{
			return QwtText("  ");
		}

		for (int i=1; i<=MAX_BIN_CNT; i++)
		{
			fVal = 6*i + 2+6;
			if ((fabsVal-fVal) < EPSINON)
			{
				return QwtText(QString("   %1").arg(QChar('A'+ i-1)));
			}
		}
		return QwtText("  ");
	}
};

class BinNumYScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	BinNumYScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		double fVal = 0;
		double fabsVal = fabs(v);

		if (fabsVal < 13.9 || fabsVal > (6*MAX_BIN_EX_CNT + 8.1))
		{
			return QwtText("  ");
		}

		for (int i=1; i<=MAX_BIN_EX_CNT; i++)
		{
			fVal = 6*i + 2+6;
			if ((fabsVal-fVal) < EPSINON)
			{
				return QwtText(QString("   %1").arg(i));
			}
		}
		return QwtText("  ");
	}
};

class UIYScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	UIYScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		return QwtText(QString::number( v) );
	}
};

class CTimeResponsePlotBase: public QwtPlot
{
	Q_OBJECT
public:
	CTimeResponsePlotBase(QWidget * = NULL );
	virtual ~CTimeResponsePlotBase();

	void updateYScale(float f1,float f2,BOOL bLeft=TRUE);
	void updateXTtile(QString str,long nFontSize=9);
	void updateYTtile(QString str,long nFontSize=9,BOOL bLeft=TRUE);
	void updateXScale(float f1, float f2);
	void clearCurveData();
	void clearCurvePlot();
	void setIntervalLength( double );
	void incrementInterval();

	QwtInterval m_Xinterval;//x轴范围
	QwtInterval m_Yinterval;//y轴范围
	QList<QwtPlotCurve *> m_CurveList;//曲线链表
	QList<QVector<QPointF> > m_CurveDataList;//曲线数据链表

	virtual void initCurve(){};
	virtual void updateCurve(double fv){};
	virtual void reflushDataList(double fLastTime);
	
	virtual void onTimerEvent( QTimerEvent * );
	
public:
	QwtPlotPicker *d_picker;
	bool m_bFirst;

	double m_dLastTime;			//相对时间
};

#endif