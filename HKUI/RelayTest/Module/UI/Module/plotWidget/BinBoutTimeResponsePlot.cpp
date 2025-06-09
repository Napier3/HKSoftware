#include "BinBoutTimeResponsePlot.h"

CBinBoutTimeResponsePlot::CBinBoutTimeResponsePlot( QWidget *parent ):
CTimeResponsePlotBase( parent )
{
	updateYTtile(tr(" "),5,TRUE);
	updateYTtile(tr(" "),5,FALSE);
	updateXScale(0,30);
	updateYScale(-80,120);
}

CBinBoutTimeResponsePlot::~CBinBoutTimeResponsePlot()
{
	
}

void CBinBoutTimeResponsePlot::setBinBoutData(long *pBinData, long nBinNum, long *pBoutData, long nBoutNum)
{
	m_pBinData = pBinData;
	m_nBinNum = nBinNum;
	m_pBoutData = pBoutData;
	m_nBoutNum = nBoutNum;
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("m_nBinNum=%ld;m_nBoutNum=%ld;"),m_nBinNum,m_nBoutNum);

	for (int i = 0; i < nBoutNum + nBinNum; i++)
	{
		SwitchYTick[i] = i + 1;
	}

	for (int i = nBoutNum + nBinNum; i < 20; i++)
	{
		SwitchYTick[i] = 0;
	}

	updateXScale(0,30);

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
	setAxisScaleDraw(QwtPlot::yLeft,new BinBoutYScaleDraw());
	setAxisScaleDraw(QwtPlot::yRight,new BinBoutYScaleDraw());

	initCurve();
}

void CBinBoutTimeResponsePlot::initCurve()
{
	clearCurvePlot();

	long nSize = 0;
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
		m_CurveDataList.append(points);
		m_CurveDataList[i].append(pt);

		pCurve->setSamples(points);
		pCurve->attach( this );
		m_CurveList.append(pCurve);
	}

	for (int i = 0; i < m_nBoutNum; i++)
	{
		pCurve = new QwtPlotCurve();
		pCurve->setStyle( QwtPlotCurve::Steps );
		pCurve->setPen( Qt::blue, 2);
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pCurve->setLegendIconSize( QSize( 6, 1.5) );

		QPointF pt(0,SwitchYTick[i + m_nBinNum]);
		m_CurveDataList.append(points);
		m_CurveDataList[i + m_nBinNum].append(pt);

		pCurve->setSamples(points);
		pCurve->attach( this );
		m_CurveList.append(pCurve);
	}
}

void CBinBoutTimeResponsePlot::slot_UpdateBinCurve()
{
/*
	CBinTimeSignal* pNew = new CBinTimeSignal;
	pNew->m_dLastTime = m_dLastTime;

	AppenSignalInfo(pNew);
*/
}

void CBinBoutTimeResponsePlot::AppendSignalData(double dTime)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	CBinTimeSignal *pNewSignal = new CBinTimeSignal();
	pNewSignal->m_dLastTime = dTime;

	m_oSignalList.AddTail(pNewSignal);
}

void CBinBoutTimeResponsePlot::AppenSignalInfo(CBinTimeSignal *pSignalInfo)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	m_oSignalList.AddTail(pSignalInfo);
}

void CBinBoutTimeResponsePlot::GetSignalInfo(CExBaseList &oSignalInfoList)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	oSignalInfoList.AppendEx(m_oSignalList);
	m_oSignalList.RemoveAll();
}

void CBinBoutTimeResponsePlot::onTimerEvent( QTimerEvent * )
{
	if(m_CurveDataList.size()==0)
	{
		return;
	}

	CExBaseList oSignalInfoList;
	GetSignalInfo(oSignalInfoList);

	if(oSignalInfoList.GetCount()>0)
	{
		POS pos = oSignalInfoList.GetHeadPosition();
		CBinTimeSignal *p = NULL;

		while(pos != NULL)
		{
			p = (CBinTimeSignal *)oSignalInfoList.GetNext(pos);
			updateCurve(p->m_dLastTime);

			if(p->m_dLastTime > m_Xinterval.maxValue())
			{
				incrementInterval();
			}
		}

		oSignalInfoList.RemoveAll();
	}
	else
	{
		QPointF point(0,0);
		if (m_CurveDataList[0].size() > 0)
		{
			point = m_CurveDataList[0].last();
		}

		if (m_bFirst)
		{
			updateCurve(0);
			m_bFirst = false;
		}
		else
		{
			updateCurve(point.x() + 0.2);
		}

		if ((point.x() + 0.2) > m_Xinterval.maxValue())
		{
			incrementInterval();
		}
	}
}

void CBinBoutTimeResponsePlot::updateCurve(double fv)
{
	if((m_pBinData == NULL && m_pBoutData == NULL) || (m_nBinNum <= 0 && m_nBoutNum <= 0))
	{
		return;
	}

	for(int i = 0; i < m_nBinNum; i++)			
	{
		QPointF pt;		
		if (m_CurveDataList[i].size()>=4000)
		{
			m_CurveDataList[i].pop_front();
			m_CurveDataList[i].pop_front();
		}

		pt.setX(fv);
		if (m_bFirst && fv==0)
		{
			pt.setY(0);
		}
		else
		{
			pt.setY(m_CurveDataList[i].last().ry());
		}

		if (m_pBinData[i] == 1)
		{
			pt.setY(SwitchYTick[i] + SPACE);
		}
		else
		{
			pt.setY(SwitchYTick[i]);
		}

		QPointF LastPoint;
		for(int j = (m_CurveDataList[i].count() - 1);j > 0;j--)
		{
			LastPoint = m_CurveDataList[i].last();
			if((LastPoint.x()-fv) > 0.0001)
			{
				m_CurveDataList[i].pop_back();
	}
			else
	{
				break;
			}
	}

		m_CurveDataList[i].append(pt);
		m_CurveList[i]->setSamples(m_CurveDataList[i]);
	}

	for(int i = 0; i < m_nBoutNum; i++)			
	{
		QPointF pt;		
		if (m_CurveDataList[m_nBinNum + i].size()>=4000)
		{
			m_CurveDataList[m_nBinNum + i].pop_front();
			m_CurveDataList[m_nBinNum + i].pop_front();
		}

		pt.setX(fv);
		if (m_bFirst && fv==0)
		{
			pt.setY(0);
		}
		else
		{
			pt.setY(m_CurveDataList[m_nBinNum + i].last().ry());
		}

		if (m_pBoutData[i] == 1)
		{
			pt.setY(SwitchYTick[m_nBinNum + i] + SPACE);
		}
		else
		{
			pt.setY(SwitchYTick[m_nBinNum + i]);
		}

		QPointF LastPoint;
		for(int j = (m_CurveDataList[m_nBinNum + i].count() - 1);j > 0;j--)
		{
			LastPoint = m_CurveDataList[m_nBinNum + i].last();
			if((LastPoint.x()-fv) > 0.0001)
			{
				m_CurveDataList[m_nBinNum + i].pop_back();
			}
			else
			{
				break;
			}
		}

		m_CurveDataList[m_nBinNum + i].append(pt);
		m_CurveList[m_nBinNum + i]->setSamples(m_CurveDataList[m_nBinNum + i]);
	}

	replot();
}

void CBinBoutTimeResponsePlot::start()
{
	clearCurveData();
	m_bFirst = true;

	QVector<QPointF> points;
	for (int i = 0; i < m_nBinNum + m_nBoutNum; i++)
	{
		QPointF pt(0,SwitchYTick[i]);
		m_CurveDataList.append(points);
	}

	m_oSignalList.DeleteAll();
	updateXScale(0,30);
}


