
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
	m_nIsCharRaised = -1;
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
double CDiffCharCal::CalculateId(double dIr)
{ 
	float fIcdqd, fIp1, fIp2, fIp3;

	if (m_nIsCharRaised == 1)
	{
		fIcdqd = m_fIcdqd / 2;
		fIp1 = m_fIp1 / 2;
		fIp2 = m_fIp2 / 2;
		fIp3 = m_fIp3 / 2;
	}
	else if (m_nIsCharRaised == 0)
	{
		fIcdqd = m_fIcdqd * 2;
		fIp1 = m_fIp1 * 2;
		fIp2 = m_fIp2 * 2;
		fIp3 = m_fIp3 * 2;
	}
	else
	{
		fIcdqd = m_fIcdqd;
		fIp1 = m_fIp1;
		fIp2 = m_fIp2;
		fIp3 = m_fIp3;
	}
	switch (m_nKneePoints)
	{
	case 1:
	{
		if (dIr < 0.0)
		{
			return fIcdqd;
		}
		else if (dIr <= fIp1)//当前点在启动段,小于拐点1
		{
			//门槛值 + 当前点在启动段的X轴长度 乘 启动电流斜率
			return fIcdqd + dIr*m_fKid0;
		}
		else
		{
			float fY = fIcdqd + fIp1*m_fKid0 + (dIr - fIp1)*m_fKid1;
			if (fY < m_fIsd)
			{
				return fY;
			}
			else
			{
				return m_fIsd;
			}
		}
	}
		break;
	case 2:
	{
		if (dIr < 0.0)
		{
			return fIcdqd;
		}
		else if (dIr <= fIp1)//当前点在启动段,小于拐点1
		{
			//门槛值 + 当前点在启动段的X轴长度 乘 启动电流斜率
			return fIcdqd + dIr*m_fKid0;
		}
		else if (dIr <= fIp2)//当前点在第一段,小于拐点2
		{
			//拐点1的Y坐标 + 当前点在第一段的X轴长度 乘 斜率
			return fIcdqd + fIp1*m_fKid0 + (dIr - fIp1)*m_fKid1;
		}
			  else
		{
			float fY = fIcdqd + fIp1*m_fKid0 + fIp2*m_fKid1 + (dIr - fIp2)*m_fKid2;;
			if (fY < m_fIsd)
			{
				return fY;
			}
			else
			{
				return m_fIsd;
			}
		}
	}
		break;
	case 3:
	{
		if (dIr < 0.0)
		{
			return fIcdqd;
		}
		else if (dIr <= fIp1)//当前点在启动段,小于拐点1
		{
			//门槛值 + 当前点在启动段的X轴长度 乘 启动电流斜率
			return fIcdqd + dIr*m_fKid0;
		}
		else if (dIr <= fIp2)//当前点在第一段,小于拐点2
		{
			//拐点1的Y坐标 + 当前点在第一段的X轴长度 乘 斜率
			return fIcdqd + fIp1*m_fKid0 + (dIr - fIp1)*m_fKid1;
		}
		else if (dIr <= fIp3)//当前点在第二段,小于拐点3
		{
			//拐点2的Y坐标 + 当前点在第二段的X轴长度 乘 斜率
			return fIcdqd + fIp1*m_fKid0 + fIp2*m_fKid1 + (dIr - fIp2)*m_fKid2;
		}
		else if (dIr > fIp3)//当前点在第三段或者速断,大于拐点3
		{
			float fY = fIcdqd + fIp1*m_fKid0 + fIp2*m_fKid1 + fIp3*m_fKid2 + (dIr - fIp3)*m_fKid3;
			if (fY < m_fIsd)
			{
				return fY;
			}
			else
			{
				return m_fIsd;
			}
		}
	}
		break;
	default:
		break;
	}
}
BOOL CDiffCharCal::CalculateId_Custom(double dIr, double &dId)
{
	POS pos = m_oPoints.GetHeadPosition();
	CString strFX, strFY;
	long nLineIndex = 0;

	while (pos)
	{
		CXDrawData_Point* pt = (CXDrawData_Point*)m_oPoints.GetNext(pos);

		if (dIr < pt->m_fX)
		{
			if (nLineIndex == 0)
			{
				dId = pt->m_fY;
			}
			else
			{	
				CXDrawData_Point* lastpt = (CXDrawData_Point*)m_oPoints.GetAt(nLineIndex - 1);
				dId = lastpt->m_fY + ((pt->m_fY - lastpt->m_fY) / (pt->m_fX - lastpt->m_fX)) * (dIr - lastpt->m_fX);
				break;
			}
			
		}
		nLineIndex++;
	}
	if (nLineIndex == m_oPoints.GetCount())
	{
		dId = ((CXDrawData_Point*)m_oPoints.GetTail())->m_fY;
	}

	return TRUE;
	//TODO
}
BOOL CDiffCharCal::CalCharIsRaised(int nComBineFeature, int nZeroSeqElimiType, int nClock, int nFaultType)
{
	if (nComBineFeature == 0)
	{
		return 0;
	}

	if (nZeroSeqElimiType == 2)// 2-YD辅助CT
	{
		if (nClock % 2 == 0)//	Y/Y，D/D 接线方式
		{
			if (nFaultType > DiffCharCal_Fault_ABCPhase)//单相故障需要处理
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (nFaultType < DiffCharCal_Fault_ABCPhase)//单相故障需要处理
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (nFaultType < DiffCharCal_Fault_ABCPhase)//单相故障需要处理
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
BOOL CDiffCharCal::CalCombinedFeature(int nComBineFeature, int nZeroSeqElimiType, int nClock, int nFaultType,BOOL bIsUpdateCharRaise)
{
	long nCalRlt = CalCharIsRaised(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType);

	if (nCalRlt == m_nIsCharRaised)
	{
			return FALSE;
		}
	if (bIsUpdateCharRaise)
	{
		if (nCalRlt == 1)
		{
			m_fIcdqd *= 2;
			m_fIp1 *= 2;
			m_fIp2 *= 2;
			m_fIp3 *= 2;
			m_nIsCharRaised = nCalRlt;
	}
		else if (m_nIsCharRaised != -1 && nCalRlt == 0)
		{
			m_fIcdqd /= 2;
			m_fIp1 /= 2;
			m_fIp2 /= 2;
			m_fIp3 /= 2;
			m_nIsCharRaised = nCalRlt;
		}
		else if (m_nIsCharRaised == -1 && nCalRlt == 0)
		{
			m_nIsCharRaised = nCalRlt;
			return FALSE;
		}
		Cal();
	}
	return TRUE;
}
