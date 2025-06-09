#include "StateMonitorBinBout.h"

QStateMonitorBinBout::QStateMonitorBinBout(QWidget* parent)
{
	UpdateYTtile(tr(" "), TRUE);
	UpdateYTtile(tr(" "), FALSE);
	UpdateXScale(0,30);
	UpdateYScale(-80,120);

	m_pBinData = NULL;
	m_pBoutData = NULL;
}

QStateMonitorBinBout::~QStateMonitorBinBout()
{

}

void QStateMonitorBinBout::AddBinBoutPoint(long nIndex, double x, double y)
{
	if(m_dRealTime)
	{
		m_dLastTime = x - m_dRealTime;
	}
	else
	{
		m_dLastTime = 0;
	}

	QPointF pt;
	pt.setX(m_dLastTime);

	if (y == 1)
	{
		if(m_arrBinBout[nIndex] == 0)
		{
			QPointF mid;
			mid.setX(m_dLastTime);

// 			if (m_dLastTime>1000)
// 			{
// 				m_dLastTime++;
// 			}

			mid.setY(SwitchYTick[nIndex]);
			m_oPreUpdateList[nIndex].append(mid);
		}

		pt.setY(SwitchYTick[nIndex] - SPACE);
	}
	else
	{
		if(m_arrBinBout[nIndex] == 1)
		{
			QPointF mid;
			mid.setX(m_dLastTime);

// 			if (m_dLastTime>1000)
// 			{
// 				m_dLastTime++;
// 			}

			mid.setY(SwitchYTick[nIndex] - SPACE);
			m_oPreUpdateList[nIndex].append(mid);
		}

		pt.setY(SwitchYTick[nIndex]);
	}
	m_oPreUpdateList[nIndex].append(pt);
	m_arrBinBout[nIndex] = y;
}

void QStateMonitorBinBout::InitBinBoutPoint(double fTime)
{
	if((m_pBinData == NULL && m_pBoutData == NULL) || (m_nBinNum <= 0 && m_nBoutNum <= 0))
	{
		return;
	}

	for(int i = 0; i < m_nBinNum; i++)			
	{
		QPointF pt;		
		pt.setX(fTime);

// 		if (fTime>1000)
// 		{
// 			fTime++;
// 		}

		if (m_pBinData[i] == 1)
		{
			pt.setY(SwitchYTick[i] - SPACE);
		}
		else
		{
			pt.setY(SwitchYTick[i]);
		}
		m_arrBinBout[i] = m_pBinData[i];
		m_oPreUpdateList[i].append(pt);
	}

	for(int i = 0; i < m_nBoutNum; i++)			
	{
		QPointF pt;				
		pt.setX(fTime);	

// 		if (fTime>1000)
// 		{
// 			fTime++;
// 		}

		if (m_pBoutData[i] == 1)
		{
			pt.setY(SwitchYTick[m_nBinNum + i] - SPACE);
		}
		else
		{
			pt.setY(SwitchYTick[m_nBinNum + i]);
		}
		m_arrBinBout[m_nBinNum + i] = m_pBoutData[i];
		m_oPreUpdateList[m_nBinNum + i].append(pt);
	}
}

void QStateMonitorBinBout::setBinBoutData(long *pBinData, long nBinNum, long *pBoutData, long nBoutNum)
{
	m_pBinData = pBinData;
	m_nBinNum = nBinNum;
	m_pBoutData = pBoutData;
	m_nBoutNum = nBoutNum;

	for (int i = 0; i < nBoutNum + nBinNum; i++)
	{
		SwitchYTick[i] = i + 1;
	}

	for (int i = nBoutNum + nBinNum; i < 20; i++)
	{
		SwitchYTick[i] = 0;
	}

	UpdateXScale(0,30);
	UpdateYScale(-80, 120);

	enableAxis(QwtPlot::yRight,true);

	QList<double> ticks[QwtScaleDiv::NTickTypes];
	QList<double>&majorTicks = ticks[QwtScaleDiv::MajorTick];

	for (int i = 1; i <= m_nBinNum; i++)
	{
		majorTicks += i;
	}

	for (int i = 1; i <= m_nBoutNum; i++)
	{
		majorTicks += i + m_nBinNum;
	}

	QwtScaleDiv scaleDiv(m_nBinNum + m_nBoutNum + 1, 0, ticks);
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDiv(QwtPlot::yRight, scaleDiv);
	setAxisScaleDraw(QwtPlot::yLeft,new BinBoutYScaleDraw(true));
	setAxisScaleDraw(QwtPlot::yRight,new BinBoutYScaleDraw(false));

	InitCurve();

	//2024-10-22 wuxinyi 重新绘制坐标轴
	replot();

}

void QStateMonitorBinBout::InitCurve()
{
	QVector<QPointF> points;
	QwtPlotCurve *pCurve = NULL;
	for (int i = 0; i < m_nBinNum; i++)
	{
		pCurve = new QwtPlotCurve();
		pCurve->setStyle( QwtPlotCurve::Steps );
		pCurve->setPen( Qt::red, 2);
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pCurve->setLegendIconSize( QSize( 6, 1.5) );

		QPointF pt(0,SwitchYTick[i]);
		m_oPreUpdateList.append(points);
		m_oUpdateList.append(points);
		m_oPreUpdateList[i].append(pt);

		CurveData* pData = new CurveData;
		pCurve->setData(pData);
		//pCurve->setSamples(points);
		pCurve->attach(this);
		m_oCurveList.append(pCurve);
	}

	for (int i = 0; i < m_nBoutNum; i++)
	{
		pCurve = new QwtPlotCurve();
		pCurve->setStyle( QwtPlotCurve::Steps );
		pCurve->setPen( Qt::blue, 2);
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pCurve->setLegendIconSize( QSize( 6, 1.5) );

		QPointF pt(0,SwitchYTick[i + m_nBinNum]);
		m_oPreUpdateList.append(points);
		m_oUpdateList.append(points);
		m_oPreUpdateList[i + m_nBinNum].append(pt);

		CurveData* pData = new CurveData;
		pCurve->setData(pData);
		//pCurve->setSamples(points);
		pCurve->attach(this);
		m_oCurveList.append(pCurve);
	}
}

void QStateMonitorBinBout::UpdateCurve(long nIndex, const QVector<QPointF>& points)
{
	QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
	CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());

	long nFrom = (long)pCurvePoints->size();
	if(points.size())
	{
		for (int i = 0; i < points.size(); i++)
		{
			QPointF pt = points.at(i);
			pCurvePoints->append(pt);
		}
	}
	else
	{
		long nSize = pCurvePoints->size() - 1;
		if(nSize < 0)
		{
			return;
		}
		QPointF pt = pCurvePoints->sample(nSize);
		//避免连续测试时starttest的绝对时间超过gps对时
		if(pt.x() < m_dLastTime)
		{
			pt.setX(m_dLastTime);
			pCurvePoints->append(pt);
		}
	}

	//增量绘图的drawSeries存在350ms的延迟
	//按照全图重绘的方式反而能够胜任划差递变
	//if(nFrom != pCurvePoints->size())
	//{
	//	m_oPainter.drawSeries(pCurve, nFrom - 1, pCurvePoints->size() - 1);
	//}

	if(pCurvePoints->maxx > m_oXinterval.maxValue())
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("pCurvePoints->maxx=%lf;m_oXinterval.maxValue()=%lf;m_oXinterval.minValue()=%lf"),
// 			pCurvePoints->maxx,m_oXinterval.maxValue(),m_oXinterval.minValue());
		m_oXinterval.setMinValue(m_oXinterval.minValue() + 30);
		m_oXinterval.setMaxValue(m_oXinterval.maxValue() + 30);
		setAxisScale(QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue());
	}
}
