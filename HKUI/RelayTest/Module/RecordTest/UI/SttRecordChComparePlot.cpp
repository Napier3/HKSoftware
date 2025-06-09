#include "SttRecordChComparePlot.h"
#include <QDir>
#include<QMessageBox>
#include <qwt_plot_magnifier.h>
#include <QString>
#include <QRect>
#include <QPainter>

QSttRecordChComparePlot::QSttRecordChComparePlot(SttRecordChType type,QWidget *parent)
{
	d_interval = QwtInterval(0,40);//区间范围
	m_pPainter = new QPainter(this);
	m_pPainter->setPen(QPen(Qt::red,6,Qt::SolidLine,Qt::RoundCap));
	setAutoReplot(false);
	plotLayout()->setAlignCanvasToScales(true);
	enableAxis(QwtPlot::yLeft, true);
	enableAxis(QwtPlot::yRight, false);
	enableAxis(QwtPlot::xTop, false);
	enableAxis(QwtPlot::xBottom, true);
	setAxisScale(QwtPlot::xBottom, d_interval.minValue(),d_interval.maxValue(), 5);
	setAxisTitle(QwtPlot::xBottom, "t/ms");
	QwtText t;
	QFont font;
	font.setBold(true);//粗体
	font.setPointSize(11);
	t.setFont(font);//设置字体

	if(type==STT_RECORD_CH_TYPE_I)
	{
		setAxisScale(QwtPlot::yLeft, -11.0, 11.0, 2);
		t.setText("I(A)");
	}
	else if(type==STT_RECORD_CH_TYPE_U)
	{
		setAxisScale(QwtPlot::yLeft, -250.0, 250.0, 50 );
		t.setText("U(V)");

	}
// 	else
// 	{
// 		setAxisScale(QwtPlot::yLeft, -250.0, 250.0, 50 );
// 		t.setText("U(V)");
// 	}
	setAxisTitle(QwtPlot::yLeft,t);


	QwtPlotGrid *pGrid = new QwtPlotGrid;//背景网格
	pGrid->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
	pGrid->attach(this);

	d_origin = new QwtPlotMarker();//标记线(此处为水平轴线)
	d_origin->setLineStyle(QwtPlotMarker::HLine);
	d_origin->setValue(d_interval.minValue()+d_interval.width()/2.0, 0.0 );
	d_origin->setLinePen(Qt::gray,0.0,Qt::SolidLine);
	d_origin->attach(this);

	m_pLeftRangeLine= new QwtPlotMarker();//左范围线(此处为竖直轴线)
	m_pLeftRangeLine->setLineStyle(QwtPlotMarker::VLine);
	m_pLeftRangeLine->setValue(d_interval.minValue()+d_interval.width()/4.0, 0.0 );
	m_pLeftRangeLine->setLinePen(Qt::green,0.0,Qt::SolidLine);
	m_pLeftRangeLine->attach(this);

	m_pRightRangeLine= new QwtPlotMarker();//右范围线(此处为竖直轴线)
	m_pRightRangeLine->setLineStyle(QwtPlotMarker::VLine);
	m_pRightRangeLine->setValue(d_interval.maxValue()-d_interval.width()/4.0, 0.0 );
	m_pRightRangeLine->setLinePen(Qt::green,0.0,Qt::SolidLine);
	m_pRightRangeLine->attach(this);

	d_setTipText1 = new QwtTextLabel(this);//显示左上角时间提示
	d_setTipText1->setFont(QFont("Microsoft YaHei", 10, QFont::Bold));
//	d_setTipText1->drawText(m_pPainter,this->rect());
	d_setTipText1->setGeometry(30,0,180,100);

	d_setTipText2  = new QwtTextLabel(this);//显示右上角曲线提示
	d_setTipText2->setFont(QFont("Microsoft YaHei", 10, QFont::Bold));
	QString strfirstLine = QString::fromLocal8Bit(("红线：合并单元输出"));
	strfirstLine = QString("<font color = red>%1</font> <br>").arg(strfirstLine);
	QString strsecondtLine = QString::fromLocal8Bit(("蓝线：合并单元输入"));
	strsecondtLine = QString("<font color = blue>%1</font> <br>").arg(strsecondtLine);
	m_strTipText2 = QString(strfirstLine + strsecondtLine);
	qwtText2.setText(m_strTipText2);
	d_setTipText2->setText(qwtText2);
//	d_setTipText2->drawText(m_pPainter,this->rect());
	d_setTipText2->setGeometry(700,0,180,100);


	d_picker=new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas());
	//拾取光标所在位置信息
	d_picker->setRubberBandPen(QColor(Qt::blue));
	d_picker->setRubberBand(QwtPicker::CrossRubberBand);
	d_picker->setTrackerPen(QColor(Qt::blue));
	
// 	QwtPlotMagnifier* magnifier= new QwtPlotMagnifier(this->canvas());//滚轮放缩
// 	magnifier->setAxisEnabled(QwtPlot::yLeft,false);

	m_pLocationPoints = new QwtPlotCurve;//定位点初始化
	m_pLocationPoints->setStyle(QwtPlotCurve::Dots);
	QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush( Qt::green ), QPen( Qt::green, 2 ), QSize( 4, 4 ) );
	m_pLocationPoints->setSymbol(symbol);
	m_oLPoints[0] = QPointF(10,0);
	m_oLPoints[1] = QPointF(30,0);
 	UpdateLocationPoints();
	UpdateTips();

	m_BtnMagnify = new QPushButton(this);
	m_BtnMagnify->setText(QString::fromLocal8Bit("放大"));
	m_BtnMagnify->setEnabled(true);
	m_BtnMagnify->setGeometry(910,5,180,100);
	m_BtnMagnify->resize(60,30);

	m_BtnResize = new QPushButton(this);
	m_BtnResize->setText(QString::fromLocal8Bit("复位"));
	m_BtnResize->setEnabled(true);
	m_BtnResize->setGeometry(910,37,60,30);

	connect(m_BtnMagnify,SIGNAL(clicked()),this,SLOT(on_m_BtnMagnify_Clicked()));
	connect(m_BtnResize,SIGNAL(clicked()),this,SLOT(on_m_BtnResize_Clicked()));

	setAutoReplot(true);


}
QSttRecordChComparePlot::~QSttRecordChComparePlot()
{
	delete d_picker;
	d_picker = NULL;
	delete d_origin;
	d_origin = NULL;
	delete d_setTipText1;
	d_setTipText1 = NULL;
	delete d_setTipText2;
	d_setTipText2 = NULL;
	delete m_pPainter;
	m_pPainter = NULL;
	delete m_pLocationPoints;
	m_pLocationPoints = NULL;

}

void QSttRecordChComparePlot::insertCurve(QVector<double> &values, QColor color, bool show )//插入波形曲线
{
	QVector<QPointF>samples(values.size());
	int j = 0;
	for(int i=0;i<values.size();i++)
	{
		samples[j++] = QPointF(double(i*0.05),values[i]);//800个点记录40ms
	}

	QwtPlotCurve *curve = new QwtPlotCurve(/*title*/);
	curve->setRenderHint(QwtPlotItem::RenderAntialiased);//反走样渲染
    curve->setStyle(QwtPlotCurve::Lines);
	curve->setCurveAttribute(QwtPlotCurve::Fitted, true);//曲线平滑
	curve->setLegendAttribute(QwtPlotCurve::LegendShowLine,true);//图例属性
	curve->setPen(QPen(color));
	curve->setSamples(samples);
	curve->attach(this);
	d_curves.append(curve);
	showCurve(curve,show);
	replot();

}

void QSttRecordChComparePlot::insertInputCurve(QVector<double> &values, bool show )
{
	insertCurve(values, Qt::blue, show);
}

void QSttRecordChComparePlot::insertInputCurve(double *pValues,int nPoints, bool show )
{
	QVector<double>tempvalues;

	for (int i = 0; i < nPoints; i++)
	{
		if (pValues != NULL)
		{
			tempvalues.push_back(pValues[i]);
		} 
		else
		{
			tempvalues.push_back(0);
		}
	}

	insertInputCurve(tempvalues, show);

}

void QSttRecordChComparePlot::insertOutputCurve(QVector<double> &values, bool show )
{
	insertCurve(values, Qt::red, show);

}

void QSttRecordChComparePlot::insertOutputCurve(double *pdValues,int nPoints, bool show )
{
	QVector<double>tempvalues;
	for (int i = 0; i < nPoints; i++)
	{
		tempvalues.push_back(pdValues[i]);
	}
	insertOutputCurve(tempvalues, show);

}

void QSttRecordChComparePlot::showCurve(QwtPlotItem *item, bool on)//显示曲线
{
	item->setVisible(on);
	replot();
}

void QSttRecordChComparePlot::showCurve( const QString& title, bool on )
{
	for(int i = 0; i<d_curves.size(); i++ )
	{
		if(d_curves.at(i)->title() == title)
		{
			showCurve(d_curves.at(i), on);
			return;
		}
	}
}

bool QSttRecordChComparePlot::existCurve( const QString& title)
{
	for(int i = 0;i<d_curves.size();i++ )
	{
		if(d_curves.at(i)->title()== title)
		{
			return true;
		}
	}
	return false;
}

void QSttRecordChComparePlot::clearCurve()//清除所有曲线
{
	qDeleteAll(d_curves);
	d_curves.clear();
	replot();
}


void QSttRecordChComparePlot::showEvent( QShowEvent * )
{
	replot();
}

void QSttRecordChComparePlot::UpdateYInterval(float fv)
{
	setAxisScale(QwtPlot::yLeft,-fv,fv);
	replot();
}

void QSttRecordChComparePlot::UpdateTips()
{
	m_dt1 = m_oLPoints[0].rx();
	m_dt2 = m_oLPoints[1].rx();
	if (m_dt2 < m_dt1)
	{
		double temp = m_dt1;
		m_dt1 = m_dt2;
		m_dt2 = temp;
	}
	m_dinterval = m_dt2 - m_dt1;
	QString strfirstLine = QString("T1 = %1ms").arg(m_dt1);
	strfirstLine = QString("<font color = brown>%1</font> <br>").arg(strfirstLine);
	QString strsecondtLine = QString("T2 = %1ms").arg(m_dt2);
	strsecondtLine = QString("<font color = green>%1</font> <br>").arg(strsecondtLine);
	QString strthirdLine = QString::fromLocal8Bit(("ΔT = %1ms")).arg(m_dinterval);
	strthirdLine = QString("<font color = black>%1</font> <br>").arg(strthirdLine);
	m_strTipText1 = strfirstLine + strsecondtLine +strthirdLine;
	qwtText1.setText(m_strTipText1);
	d_setTipText1->setText(qwtText1);
}

void QSttRecordChComparePlot::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_oLPoints[0] = d_picker->trackerPosition();
		QwtScaleMap xMap = canvasMap(QwtPlot::xBottom);
//		QwtScaleMap yMap = canvasMap(QwtPlot::yLeft);
		m_oLPoints[0] = QPointF(xMap.invTransform(m_oLPoints[0].x()),0);
		UpdateLocationPoints();
		UpdateTips();
	}
	else if(event->button() == Qt::RightButton)
	{
		m_oLPoints[1] = d_picker->trackerPosition();
		QwtScaleMap xMap = canvasMap(QwtPlot::xBottom);
//		QwtScaleMap yMap = canvasMap(QwtPlot::yLeft);
		m_oLPoints[1] = QPointF(xMap.invTransform(m_oLPoints[1].x()),0);
		UpdateLocationPoints();
		UpdateTips();
	}

}

void QSttRecordChComparePlot::UpdateLocationPoints()
{
	QVector<QPointF>samples(2);
	samples[0] = m_oLPoints[0];
	samples[1] = m_oLPoints[1];
	m_pLocationPoints->setSamples(samples);
	m_pLocationPoints->attach(this);
	showCurve(m_pLocationPoints,true);
	m_pLeftRangeLine->setValue(m_oLPoints[0].rx(), 0.0 );
	m_pRightRangeLine->setValue(m_oLPoints[1].rx(), 0.0);
	replot();

}

void QSttRecordChComparePlot::mouse_event()
{

}

void QSttRecordChComparePlot::on_m_BtnMagnify_Clicked()
{
	setAxisScale(QwtPlot::xBottom, m_oLPoints[0].rx(),m_oLPoints[1].rx());
	replot();
}

void QSttRecordChComparePlot::on_m_BtnResize_Clicked()
{
	setAxisScale(QwtPlot::xBottom, d_interval.minValue(),d_interval.maxValue(), 5);
	replot();
}
