
#include "stdafx.h"
#include "DiffCharCal.h"
#include <math.h>
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDiffCharCal::CDiffCharCal()
{
	m_fIsd=5;
	m_fIcdqd=0.5;

	m_nKneePoints = 1;
	m_fIp1 = 1.0f;
	m_fIp2 = 2.5f;
	m_fIp3 = 3.0f;
	m_fKid0 = 0.0f;
	m_fKid1 = 0.7f;
	m_fKid2 = 0.4f;
	m_fKid3 = 0.4f;

	m_fHarmCoef = 0.15f;

	m_fAxisMaxCoef = 1.4;
	m_nSelectSd = 1;
	m_nMinAxis = 0;
	m_fInSet = 1.0f;
	m_nInsel = 0;
	m_nHarmIndex = 0;
	m_fYMax = 8.0f;
	m_bFixYMax = FALSE;

	for (int nIndex = 0;nIndex<5;nIndex++)
	{
		m_nPointNum[nIndex] = 4;
		m_fErrorBand[nIndex] = 0.2f;
	}
}

CDiffCharCal::~CDiffCharCal()
{
	
}


// void CDifferCharacPlot::generateErrorRangeData( QVector<QPointF> &points,QVector<QwtIntervalSample> &rangeData,float fe )
// {
// 	for (int i=0;i<points.size();i++)
// 	{
// 		QPointF p = points.at(i);
// 		rangeData.append( QwtIntervalSample( double( p.x() ),QwtInterval( p.y()*(1+fe/100), p.y()*(1-fe/100) ) ));
// 	}
// }

void CDiffCharCal::Cal()
{
	m_oPoints.DeleteAll();

	if (m_nSelectSd)
	{
		m_fYMax = m_fIsd*m_fAxisMaxCoef;

		switch(m_nKneePoints)
		{
		case 1:
			{
				float y1 = m_fIp1*m_fKid0 + m_fIcdqd;
				float xIsd = m_fIp1+(m_fIsd-y1)/m_fKid1;
				m_fXMax = xIsd*m_fAxisMaxCoef;

				m_oPoints.AddTail(new CXDrawData_Point(0.0, m_fIcdqd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp1, y1));
				m_oPoints.AddTail(new CXDrawData_Point(xIsd, m_fIsd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fIsd));

				//m_curvePoints << QPointF( 0.0, m_fIcdqd ) << QPointF( m_fIp1, y1 )
				//	<< QPointF(xIsd, m_fIsd)<<QPointF(m_CurXScale, m_fIsd);

				//generateErrorRangeData(m_curvePoints,rangeData,5); //5可取系统参数中的相对误差值
				//setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale);
			}
			break;
		case 2:
			{
				float y1 = m_fIp1*m_fKid0 + m_fIcdqd;
				float y2 = y1 + (m_fIp2-m_fIp1)*m_fKid1; //拐点2的Y坐标
				float xIsd = (m_fIsd-y2)/m_fKid2+m_fIp2;
				m_fXMax = xIsd*m_fAxisMaxCoef;

				m_oPoints.AddTail(new CXDrawData_Point(0.0, m_fIcdqd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp1, y1));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp2, y2));
				m_oPoints.AddTail(new CXDrawData_Point(xIsd, m_fIsd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fIsd));

				// 			m_curvePoints << QPointF( 0.0, m_fIcdqd ) << QPointF( m_fIp1, y1 )\
				// 				<< QPointF( m_fIp2, y2 )<< QPointF(xIsd, m_fIsd)\
				// 				<<QPointF(m_CurXScale, m_fIsd);
				// 
				// 			generateErrorRangeData(m_curvePoints,rangeData,5);
				// 			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
			}
			break;
		case 3:
			{
				float y1 = m_fIp1*m_fKid0 + m_fIcdqd;
				float y2 = y1 + (m_fIp2-m_fIp1)*m_fKid1; //拐点2的Y坐标
				float y3 = y2+(m_fIp3-m_fIp2)*m_fKid2; //拐点3的Y坐标
				float xIsd = m_fIp3+(m_fIsd-y3)/m_fKid3; 
				m_fXMax = xIsd*m_fAxisMaxCoef;

				m_oPoints.AddTail(new CXDrawData_Point(0.0, m_fIcdqd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp1, y1));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp2, y2));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp3, y3));
				m_oPoints.AddTail(new CXDrawData_Point(xIsd, m_fIsd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fIsd));

				// 			m_curvePoints << QPointF( 0.0, m_fIcdqd ) << QPointF( m_fIp1, y1)
				// 				<< QPointF(m_fIp2, y2 )<<QPointF(m_fIp3 , y3 )
				// 				<<QPointF(xIsd, m_fIsd)<<QPointF(m_CurXScale, m_fIsd);
				// 
				// 			generateErrorRangeData(m_curvePoints,rangeData,6);
				// 			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
			}
			break;
		default:
			break;
		}
	} 
	else
	{
		switch(m_nKneePoints)
		{
		case 1:
			{
				float y1 = m_fIcdqd + m_fIp1*m_fKid0;

				if (m_bFixYMax && (m_fKid1>0.0001f))
				{
					if (m_fYMax<y1)
					{
						m_fYMax = y1*1.4;
					}

					m_fXMax = m_fIp1 + (m_fYMax - y1)/m_fKid1;
				} 
				else
				{
					m_fXMax = (m_fIp1+m_fIp1)*m_fAxisMaxCoef;//默认两个拐点1的长度,再加上裕度为制动电流坐标轴长度
					m_fYMax = y1 + (m_fXMax-m_fIp1)*m_fKid1;
				}

				m_oPoints.AddTail(new CXDrawData_Point(0.0, m_fIcdqd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp1, y1));
				m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fYMax));
			}
			break;
		case 2:
			{
				float y1 = m_fIp1*m_fKid0 + m_fIcdqd;
				float y2 = y1 + (m_fIp2-m_fIp1)*m_fKid1; //拐点2的Y坐标

				if (m_bFixYMax && (m_fKid2>0.0001f))
				{
					if (m_fYMax<y2)
					{
						m_fYMax = y2*1.4;
					}

					m_fXMax = m_fIp2 + (m_fYMax - y2)/m_fKid2;
				} 
				else
				{
					m_fXMax = (m_fIp2+m_fIp2 - m_fIp1)*m_fAxisMaxCoef;//默认最后一段横坐标长度和前一段比率制动横坐标长度保持一致,再加上裕度为制动电流坐标轴长度
					m_fYMax = y2 + (m_fXMax-m_fIp2)*m_fKid2;
				}
				
				m_oPoints.AddTail(new CXDrawData_Point(0.0, m_fIcdqd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp1, y1));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp2, y2));
				m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fYMax));
			}
			break;
		case 3:
			{
				float y1 = m_fIp1*m_fKid0 + m_fIcdqd;
				float y2 = y1 + (m_fIp2-m_fIp1)*m_fKid1; //拐点2的Y坐标
				float y3 = y2+(m_fIp3-m_fIp2)*m_fKid2; //拐点3的Y坐标
				m_fXMax = (m_fIp3+m_fIp3 - m_fIp2)*m_fAxisMaxCoef;//默认最后一段横坐标长度和前一段比率制动横坐标长度保持一致,再加上裕度为制动电流坐标轴长度
				m_fYMax = y3 + (m_fXMax-m_fIp3)*m_fKid3;

				m_oPoints.AddTail(new CXDrawData_Point(0.0, m_fIcdqd));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp1, y1));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp2, y2));
				m_oPoints.AddTail(new CXDrawData_Point(m_fIp3, y3));
				m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fYMax));

			}
			break;
		default:
			break;
		}
	}
}

void CDiffCharCal::CalHarm()
{
	m_oPoints.DeleteAll();

	float y1 = /*m_fIp1*m_fKid0 + */m_fIcdqd;
	float xIsd = m_fIp1+(m_fIsd-y1)/m_fKid1;
	m_fXMax = m_fHarmCoef*100*m_fAxisMaxCoef;

	m_fYMax = m_fIsd*m_fAxisMaxCoef;//20230706-wxy

	m_oPoints.AddTail(new CXDrawData_Point(0.0, y1));
	m_oPoints.AddTail(new CXDrawData_Point(m_fHarmCoef * 100, y1));
	m_oPoints.AddTail(new CXDrawData_Point(m_fHarmCoef * 100, m_fIsd));
	m_oPoints.AddTail(new CXDrawData_Point(m_fXMax, m_fIsd));
}