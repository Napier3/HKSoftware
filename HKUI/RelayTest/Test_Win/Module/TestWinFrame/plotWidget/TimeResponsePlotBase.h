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

#include "../../Define.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTest/Common/tmt_result_def.h"

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotDirectPainter;

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;

#define  SPACE		3

#define MAX_BIN_CNT	10
#define MAX_BIN_EX_CNT	128
#define MAX_COLOR_NUM	16

#define STATE_UPDATE_FREE		0x00
#define STATE_UPDATE_TIMER		0x01
#define STATE_UPDATE_CHANGE		0x02

extern QColor g_arrCurveColor[MAX_COLOR_NUM];
extern QString GetCurveStyleSheetString(long nColorIndex);

class CurveData: public QwtArraySeriesData<QPointF>
{
public:
	CurveData()
	{
		miny = 0;
		maxy = 1;
		minx = 0;
		maxx = 1;
		d_samples.reserve(6000);
	}

	virtual QRectF boundingRect() const
	{
		if ( d_boundingRect.width() < 0.0 )
			d_boundingRect = qwtBoundingRect( *this );

		return d_boundingRect;
	}

	void append( const QPointF &point );

	void clear()
	{
		d_samples.clear();
		d_samples.squeeze();
		d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
	}

	void setPoint(long nIndex, double x, double y)
	{
		if(nIndex < d_samples.size())
		{
			d_samples[nIndex].setX(x);
			d_samples[nIndex].setY(y);
		}
	}

	size_t size(){
		return d_samples.size();
	}

public:
	double miny;
	double maxy;
	double minx;
	double maxx;

};


//add wangtao 20240506 带参数的自画坐标轴 通过传参统一三幅图的大小
class BinCharYScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	int m_nWordlength;//根据参数设置文字前的空格长度
    bool m_isWordOnRight;//false代表文字在左边Y轴,true在右边Y轴 防止右边字体远离Y轴
	BinCharYScaleDraw(int nWordlength = 3,bool isWordOnRight = false)
	{
		m_nWordlength = nWordlength;
        m_isWordOnRight = isWordOnRight;
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
				QString str_QwtText = "";

				if(m_isWordOnRight)
				{
                    str_QwtText = QString("%1").arg(QChar('A'+ i-1));
					for (int n=0; n<m_nWordlength; n++)
					{
						str_QwtText.append(" ");
					}

					return QwtText(str_QwtText);
				}
				else
				{
					for (int n=0; n<m_nWordlength; n++)
					{
						str_QwtText.append(" ");
					}
					return QwtText(str_QwtText.append("%1").arg(QChar('A'+ i-1)));
				}
				
			}
		}
		return QwtText("  ");
	}
};

class BinNumYScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	int m_nWordlength;
    bool m_isWordOnRight;
	BinNumYScaleDraw(int nWordlength = 3,bool isWordOnRight = false)
	{
		m_nWordlength = nWordlength;
		m_isWordOnRight = isWordOnRight;
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
				QString str_QwtText = "";

				if(m_isWordOnRight)
				{
					str_QwtText = QString("%1").arg(i);
					for (int n=0; n<m_nWordlength; n++)
					{
						str_QwtText.append(" ");
					}

					return QwtText(str_QwtText);
				}
				else
				{
					for (int n=0; n<m_nWordlength; n++)
					{
						str_QwtText.append(" ");
					}
					return QwtText(str_QwtText.append("%1").arg(i));
				}
			}
		}
		return QwtText("  ");
	}
};
//end
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
//	void updateXScale(float f1, float f2);  改为使用UpdateXScale
	void clearCurveData();
	void clearCurvePlot();
	void setIntervalLength( double );
	void incrementInterval();

	QwtInterval m_oXinterval;//x轴范围
	QwtInterval m_oYinterval;//y轴范围
	QList<QwtPlotCurve *> m_oCurveList;//曲线链表
	QList<QVector<QPointF> > m_oPreUpdateList;//准备更新的曲线数据链表
	QList<QVector<QPointF>> m_oUpdateList;//需要更新的曲线数据链表


	virtual void initCurve(){};
	virtual void updateCurve(double fv){};
	virtual void reflushDataList(double fLastTime);
	
	virtual void onTimerEvent( QTimerEvent * );
	virtual void UpdateCurves();
	virtual void UpdateCurve(long nIndex, const QVector<QPointF>& points);//更新每个QwtPlotCurve
	virtual void UpdateXScale(float f1, float f2);
	virtual void AddStopPoint();//添加绘图中止点
	virtual void SetInit(bool bInit) { m_bNeedInit = bInit; };
	
public:
	QwtPlotPicker *d_picker;
	bool m_bFirst;

	double m_dLastTime;			//相对时间
	double m_dRealTime;//测试启动的绝对时间  2023.6.13 zhouhj 新增
	BOOL m_bUseTesterTime;//是否使用测试仪内部时间 

protected:
	bool m_bNeedInit;
};

#endif