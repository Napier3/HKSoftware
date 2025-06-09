#include "BinTimeResponsePlot.h"

int g_nSwitchYTick[MAX_BIN_EX_CNT] = {0};//标识开入开出在Y轴的位置,每个占用6像素

void InitSwitchY()
{
	for (int i=0; i<MAX_BIN_EX_CNT; i++)
	{
		g_nSwitchYTick[i] = -14 - 6*i;
	}
}


CBinTimeResponsePlot::CBinTimeResponsePlot( QWidget *parent ):
CTimeResponsePlotBase( parent )
{
	for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
	{
		m_arrBinBout[nIndex] = 0;
	}

	if (g_nSwitchYTick[0] == 0)//0代表还未初始化,对其进行初始化
	{
		InitSwitchY();
	}
	
	updateYTtile(tr(" "),5,TRUE);
	updateYTtile(tr(" "),5,FALSE);
	UpdateXScale(0,30);
	updateYScale(-80,120);
}

CBinTimeResponsePlot::~CBinTimeResponsePlot()
{
	
}

void CBinTimeResponsePlot::setBinData(long *pBinData,long nBinNum,long nBinChlType)
{
	m_pBinData = pBinData;
	m_nBinNum = nBinNum;
	m_nBinChlType = nBinChlType;

	UpdateXScale(0,30);

	enableAxis(QwtPlot::yRight,true);

	QList<double> ticks[QwtScaleDiv::NTickTypes];
	for (int i=m_nBinNum+1; i>0; i--)
	{
		ticks[QwtScaleDiv::MajorTick] << (-6*i - 2);
	}

	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDiv(QwtPlot::yRight, scaleDiv);
	if (m_nBinChlType == 1)
	{//数字
		setAxisScaleDraw(QwtPlot::yLeft,new BinNumYScaleDraw());
		setAxisScaleDraw(QwtPlot::yRight,new BinNumYScaleDraw());
	}
	else
	{
		setAxisScaleDraw(QwtPlot::yLeft,new BinCharYScaleDraw());
		setAxisScaleDraw(QwtPlot::yRight,new BinCharYScaleDraw());
	}

	initCurve();
}

void CBinTimeResponsePlot::initCurve()
{
	clearCurvePlot();

	long nSize = 0;
	QVector<QPointF> points;

	QwtPlotCurve *pCurve = NULL;
	for (int i=0;i<m_nBinNum;i++)
	{
		pCurve = new QwtPlotCurve();
		pCurve->setStyle( QwtPlotCurve::Steps );
		pCurve->setPen( Qt::red, 2);
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pCurve->setLegendIconSize( QSize( 6, 1.5) );

		if (m_bUseTesterTime)
		{
			QPointF pt(0,g_nSwitchYTick[i]);
			m_oPreUpdateList.append(points);
			m_oUpdateList.append(points);
			m_oPreUpdateList[i].append(pt);

			CurveData* pData = new CurveData;
			pCurve->setData(pData);
			//pCurve->setSamples(points);
			pCurve->attach(this);
			m_oCurveList.append(pCurve);
		} 
		else
		{
			QPointF pt(0,g_nSwitchYTick[i]);
			m_oUpdateList.append(points);
			m_oUpdateList[i].append(pt);

			pCurve->setSamples(points);
			pCurve->attach( this );
			m_oCurveList.append(pCurve);
		}
		
	}

	if (m_bUseTesterTime)
	{
		UpdateXScale(0,30);
	}
}

void CBinTimeResponsePlot::slot_UpdateBinCurve()
{
/*
	CBinTimeSignal* pNew = new CBinTimeSignal;
	pNew->m_dLastTime = m_dLastTime;

	AppenSignalInfo(pNew);
*/
}

void CBinTimeResponsePlot::AppendSignalData(double dTime)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	CBinTimeSignal *pNewSignal = new CBinTimeSignal();
	pNewSignal->m_dLastTime = dTime;

	m_oSignalList.AddTail(pNewSignal);
}

void CBinTimeResponsePlot::AppenSignalInfo(CBinTimeSignal *pSignalInfo)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	m_oSignalList.AddTail(pSignalInfo);
}

void CBinTimeResponsePlot::GetSignalInfo(CExBaseList &oSignalInfoList)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	oSignalInfoList.AppendEx(m_oSignalList);
	m_oSignalList.RemoveAll();
}

void CBinTimeResponsePlot::onTimerEvent( QTimerEvent * )
{
	if (m_bUseTesterTime)
	{
		return;
	}

	if(m_oUpdateList.size()==0)
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

			if(p->m_dLastTime > m_oXinterval.maxValue())
			{
				incrementInterval();
			}
		}

		oSignalInfoList.RemoveAll();
	}
	else
	{
		QPointF point(0,0);
		if (m_oUpdateList[0].size() > 0)
		{
			point = m_oUpdateList[0].last();
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

		if ((point.x() + 0.2) > m_oXinterval.maxValue())
		{
			incrementInterval();
		}
	}
}

void CBinTimeResponsePlot::updateCurve(double fTimeValue)
{
	if (m_bUseTesterTime)
	{
		return;
	}

	if(m_pBinData == NULL || m_nBinNum<=0)
	{
		return;
	}

	for(int i=0;i<m_nBinNum;i++)			
	{
		QPointF pt;		
		if (m_oUpdateList[i].size()>=4000)
		{
			m_oUpdateList[i].pop_front();
			m_oUpdateList[i].pop_front();
		}

		pt.setX(fTimeValue);

		//删除无效代码  2023.6.13 zhouhj
// 		if (m_bFirst && (fabs(fTimeValue) <=0.000001f))
// 		{
// 			pt.setY(0);
// 		}
// 		else
// 		{
// 			pt.setY(m_oUpdateList[i].last().ry());
// 		}

		if (m_pBinData[i]==1)
		{
			pt.setY(g_nSwitchYTick[i]+SPACE);
		}
		else
		{
			pt.setY(g_nSwitchYTick[i]);
		}

		QPointF LastPoint;

		for(int j = (m_oUpdateList[i].count() - 1);j > 0;j--)
		{
			LastPoint = m_oUpdateList[i].last();
			if((LastPoint.x()-fTimeValue) > 0.0001)
			{
				m_oUpdateList[i].pop_back();
			}
			else
			{
				break;
			}
		}

// 		if ((i== 0)&&(m_nBinNum == 10)&&(fTimeValue<0.5f))
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("updateCurve开入1[%ld]"),m_pBinData[0]);
// 		}

		m_oUpdateList[i].append(pt);
		m_oCurveList[i]->setSamples(m_oUpdateList[i]);
	}

	replot();
}

void CBinTimeResponsePlot::start()
{
	clearCurveData();
	m_bFirst = true;

	if (m_bUseTesterTime)
	{
		InitBinBoutPoint(0);
	}
	else
	{
		QVector<QPointF> points;
		for (int i=0;i<m_nBinNum;i++)
		{
			//		QPointF pt(0,SwitchYTick[i]);实际未用到
			m_oUpdateList.append(points);
		}
	}

	m_oSignalList.DeleteAll();
	UpdateXScale(0,30);
	replot();
}

void CBinTimeResponsePlot::InitBinBoutPoint(double fTime)
{
	if((m_pBinData == NULL) || (m_nBinNum <= 0))
	{
		return;
	}

	for(int i = 0; i < m_nBinNum; i++)			
	{
		QPointF pt;		
		pt.setX(fTime);

		if (m_pBinData[i] == 1)
		{
			pt.setY(g_nSwitchYTick[i] + SPACE);
		}
		else
		{
			pt.setY(g_nSwitchYTick[i]);
		}
		m_arrBinBout[i] = m_pBinData[i];
		m_oPreUpdateList[i].append(pt);
	}
}

void CBinTimeResponsePlot::AddBinBoutPoint(long nIndex, double x, double y)
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

			mid.setY(g_nSwitchYTick[nIndex]);
			m_oPreUpdateList[nIndex].append(mid);
		}

		pt.setY(g_nSwitchYTick[nIndex] + SPACE);
	}
	else
	{
		if(m_arrBinBout[nIndex] == 1)
		{
			QPointF mid;
			mid.setX(m_dLastTime);

			mid.setY(g_nSwitchYTick[nIndex] + SPACE);
			m_oPreUpdateList[nIndex].append(mid);
		}

		pt.setY(g_nSwitchYTick[nIndex]);
	}
	m_oPreUpdateList[nIndex].append(pt);
	m_arrBinBout[nIndex] = y;
}

void CBinTimeResponsePlot::UpdateCurve(long nIndex, const QVector<QPointF>& points)
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

	if(pCurvePoints->maxx > m_oXinterval.maxValue())
	{
		m_oXinterval.setMinValue(m_oXinterval.minValue() + 30);
		m_oXinterval.setMaxValue(m_oXinterval.maxValue() + 30);
		setAxisScale(QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue());
	}
}

void CBinTimeResponsePlot::UpdateCurves()
{
	//开始绘制
	for (int i = 0; i < m_oPreUpdateList.size(); i++)
	{
		m_oUpdateList[i] += m_oPreUpdateList[i];
	}

	QVector<QPointF> oQPointF_Vector;
	//完成绘制后删除更新列表
	for(int i = 0; i < m_oUpdateList.size(); i++)
	{
		oQPointF_Vector = m_oUpdateList.at(i);
		UpdateCurve(i, oQPointF_Vector);
		m_oUpdateList[i].clear();
	}

	replot();

	for (int i = 0; i < m_oPreUpdateList.size(); i++)
	{
		while(m_oPreUpdateList[i].size())
		{
			m_oPreUpdateList[i].pop_back();
		}
	}
}

