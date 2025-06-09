#include "ChlTimeResponsePlot.h"
#include <qmath.h>
#include "../../CommonMethod/commonMethod.h"
#include "../../../../../Module/API/MathApi.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"

CChlTimeResponsePlot::CChlTimeResponsePlot( QWidget *parent ):
CTimeResponsePlotBase( parent )
{
	UpdateXScale(0,30);
	InitYTick(0,300,0,24);
	updateYTtile(/*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)",9,TRUE);
	updateYTtile(/*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)",9,FALSE);

	m_pLastPoints = new CExBaseList; 
}

CChlTimeResponsePlot::~CChlTimeResponsePlot()
{
	FreeChlDatasList();

	if(m_pLastPoints)
	{
		delete m_pLastPoints;
		m_pLastPoints = NULL;
	}
}

void CChlTimeResponsePlot::FreeChlDatasList()
{
	m_oChlUDatasList.RemoveAll();
	m_oChlIDatasList.RemoveAll();

	int nCnt = m_vecChlULabel.size();
	for(int i=0; i<nCnt; i++)
	{
		QLabel *p = m_vecChlULabel.at(i);
		delete p;
	}
	m_vecChlULabel.clear();

	nCnt = m_vecChlILabel.size();
	for(int i=0; i<nCnt; i++)
	{
		QLabel *p = m_vecChlILabel.at(i);
		delete p;
	}
	m_vecChlILabel.clear();
}

void CChlTimeResponsePlot::setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList
									  ,double fUMin,double fUMax
									  ,double fIMin,double fIMax , int type)
{
	FreeChlDatasList();

	m_oChlUDatasList.Append(oChlUDatasList);
	m_oChlIDatasList.Append(oChlIDatasList);

	m_nType = type;

	clearCurveData();
	UpdateXScale(0,30);
	InitYTick(fUMin,fUMax,fIMin,fIMax);

	initCurve();
}

void CChlTimeResponsePlot::updateCurve(double fv)
{
	if (m_bUseTesterTime)
	{
		return;
	}

	POS pos = NULL;
	CSttMacroChannel *pChl = NULL;
	float fy=0;
	long nIndex = 0;
	float fVal = 0;
	QPointF pt;
	tmt_RtDataCh rtData;

	pos = m_oChlUDatasList.GetHeadPosition();
	while(pos != NULL)
	{
		pChl = (CSttMacroChannel *)m_oChlUDatasList.GetNext(pos);

		pt.setX(fv);

// 		if (m_bFirst && fv==0)
// 		{
// 			pt.setY(0);
// 		}
// 		else
// 		{
// 			pt.setY(m_oUpdateList[nIndex].last().ry());
// 		}
		
		//yyj add 2021-08-25
		if (!pChl->m_oHisDataBuf.GetLastMemVal(rtData))
		{
		if (m_bFirst && fv==0)
		{
			pt.setY(0);
		}
		else
		{
				QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
				CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());
		
				if (m_oUpdateList[nIndex].size())
		{
					
					pt = m_oUpdateList[nIndex].last();
				}
				else
				{
					long nSize = pCurvePoints->size() - 1;
					if(nSize < 0)
					{
						pt.setY(0);
						//break;
					}
					else
					{
						pt = pCurvePoints->sample(nSize);
						pt.setY(pt.ry());
					}
					

				}
				

				//pt.setY(m_oUpdateList[nIndex].last().ry());
			}
//   			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取最新测试点数据失1111败"));
			//return;
		}

		if(m_nType == 0)		//20210908 sf 兼容幅值相位频率
		{
			fVal = rtData.m_fMag;
		}
		else if (m_nType == 1)	//20211031 sf 范围限制
		{
			fVal = rtData.m_fAng;

			if (rtData.m_fAng > 180)
			{
				fVal = rtData.m_fAng - 360;
			}
			if (rtData.m_fAng < -180)
			{
				fVal = rtData.m_fAng + 360;
			}
		}
		else
		{
			fVal = rtData.m_fFreq;
		}

		pt.setY(fVal);

		if (m_oUpdateList[nIndex].size()>=4000)//大于4000点之后,删除第一个点
		{
			m_oUpdateList[nIndex].pop_front();
			m_oUpdateList[nIndex].pop_front();
		}

		m_oUpdateList[nIndex].append(pt);
		m_oCurveList[nIndex]->setSamples(m_oUpdateList[nIndex]);

		nIndex++;
	}

	pos = m_oChlIDatasList.GetHeadPosition();
	while(pos != NULL)
	{
		pChl = (CSttMacroChannel *)m_oChlIDatasList.GetNext(pos);

		pt.setX(fv);
		//202404018 suyang 注销多余代码
// 		if (m_bFirst && fv==0)
// 		{
// 			pt.setY(0);
// 		}
// 		else
// 		{
// 			pt.setY(m_oUpdateList[nIndex].last().ry());
// 		}
  
		if (!pChl->m_oHisDataBuf.GetLastMemVal(rtData))
		{	
		if (m_bFirst && fv==0)
		{
			pt.setY(0);
		}
		else
		{
				QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
				CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());

				if (m_oUpdateList[nIndex].size())
		{

					pt = m_oUpdateList[nIndex].last();
				}
				else
				{
					long nSize = pCurvePoints->size() - 1;
					if(nSize < 0)
					{
						pt.setY(0);
						//break;
					}
					else
					{
						pt = pCurvePoints->sample(nSize);
						pt.setY(pt.ry());
					}
					

				}
				//pt.setY(m_oUpdateList[nIndex].last().ry());
			}
//    			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取最新测试点数据失败"));
			//return;
		}

		if(m_nType == 0)   //20210908 sf 兼容幅值相位频率
		{
			fVal = rtData.m_fMag;
		}
		else if (m_nType == 1)//20211031 sf 范围限制
		{
			fVal = rtData.m_fAng;

			if (rtData.m_fAng > 180)
			{
				fVal = rtData.m_fAng - 360;
			}
			if (rtData.m_fAng < -180)
			{
				fVal = rtData.m_fAng + 360;
			}
		}
		else
		{
			fVal = rtData.m_fFreq;
		}

		pt.setY(fVal);

		if (m_oUpdateList[nIndex].size()>=4000)//大于4000点之后,删除第一个点
		{
			m_oUpdateList[nIndex].pop_front();
			m_oUpdateList[nIndex].pop_front();
		}

		m_oUpdateList[nIndex].append(pt);
		m_oCurveList[nIndex]->setSamples(m_oUpdateList[nIndex]);

		nIndex++;
	}

	replot();
}

void CChlTimeResponsePlot::InitYTick(double fUMin,double fUMax,double fIMin,double fIMax)
{
	enableAxis(QwtPlot::yRight,true);

	//取整10
	int nUMin = ((int)fUMin%10==0) ? (int)fUMin:((int)fUMin/10-1)*10;
	int nUMax = ((int)fUMax%10==0) ? (int)fUMax:((int)fUMax/10+1)*10;
	if (nUMax <= 0)
	{
		nUMax = g_oSystemParas.m_fVNom;
	}

	if (m_nType == amplitude_type)//zhouhj 20211031  对于相位和频率递变,不需要在最大值的基础上增加40
	{
		nUMax += 20;	
	}

	updateYScale(nUMin,nUMax);

	//取整5
	int nIMin = ((int)fIMin%5==0) ? (int)fIMin:((int)fIMin/5-1)*5;
	int nIMax = ((int)fIMax%5==0) ? (int)fIMax:((int)fIMax/5+1)*5;
	if (nIMax <= 0)
	{
		nIMax = g_oSystemParas.m_fINom;
	}

	if (m_nType == amplitude_type)//zhouhj 20211031  对于相位和频率递变,不需要在最大值的基础上增加20
	{
		nIMax += 10;	
	}
	
	updateYScale(nIMin,nIMax,FALSE);

	setAxisScaleDraw(QwtPlot::yLeft,new UIYScaleDraw());
	setAxisScale(QwtPlot::yLeft,nUMin,nUMax);

	setAxisScaleDraw(QwtPlot::yRight,new UIYScaleDraw());
	setAxisScale(QwtPlot::yRight,nIMin,nIMax);
}

void CChlTimeResponsePlot::initCurve()
{
	clearCurvePlot();

	POS pos = m_oChlUDatasList.GetHeadPosition();
	CSttMacroChannel *pChl = NULL;
	long nIndex = 0;
	QFont fonttTemp = this->font();
	QFontMetrics fontMetrics = QFontMetrics(fonttTemp);
	int nHeight = fontMetrics.height();
	long nColorIndex = 0;
	QVector<QPointF> points;
	QwtPlotCurve *pCurve = NULL;
	long nIColorIndex = 0, nVColorIndex = 0;

	while(pos != NULL)
	{
		pChl = (CSttMacroChannel *)m_oChlUDatasList.GetNext(pos);
		nColorIndex = nIndex % MAX_COLOR_NUM;

		QLabel *pLabel = new QLabel(this->canvas());
		pLabel->setStyleSheet(GetCurveStyleSheetString(nColorIndex));
		//pLabel->setText("-- " + pChl->m_strName);
		//pLabel->setGeometry(10+80*nIndex,1,80,nHeight);
		pLabel->setText("--" + pChl->m_strName);
		pLabel->setGeometry(10+40*nIndex,1,80,nHeight);
		m_vecChlULabel.append(pLabel);

		if (m_bUseTesterTime)
		{
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("V"));
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			CurveData* pData = new CurveData;
			pCurve->setData(pData);
			//pCurve->setSamples(points);
			m_oCurveList.append(pCurve);
			m_oPreUpdateList.append(points);
			m_oUpdateList.append(points);

			nVColorIndex = nIndex % MAX_COLOR_NUM;
			pCurve->setPen( g_arrCurveColor[nVColorIndex], 2.5 );
			pCurve->setYAxis(QwtPlot::yLeft);
		} 
		else
		{
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("V"));
			pCurve->setStyle( QwtPlotCurve::Steps );
			pCurve->setPen(g_arrCurveColor[nColorIndex],2.5);

			pCurve->setYAxis(QwtPlot::yLeft);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->setSamples( points );
			pCurve->attach( this );
			m_oCurveList.append(pCurve);
			m_oUpdateList.append(points);
		}

		nIndex++;
	}

	pos = m_oChlIDatasList.GetHeadPosition();
	long nTemp = nIndex;
	nIndex = 0;
	
	while(pos != NULL)
	{
		pChl = (CSttMacroChannel *)m_oChlIDatasList.GetNext(pos);
		nColorIndex = nIndex % MAX_COLOR_NUM;

		QLabel *pLabel = new QLabel(this->canvas());
		pLabel->setStyleSheet(GetCurveStyleSheetString(nColorIndex));
		//pLabel->setText("-- " + pChl->m_strName);
		//pLabel->setGeometry(10+80*(nIndex+nTemp),1,80,nHeight);
		pLabel->setText("--" + pChl->m_strName);
		pLabel->setGeometry(10+40*(nIndex+nTemp),1,80,nHeight);
		m_vecChlULabel.append(pLabel);


		if (m_bUseTesterTime)
		{
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("A"));
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			CurveData* pData = new CurveData;
			pCurve->setData(pData);
			//pCurve->setSamples(points);
			m_oCurveList.append(pCurve);
			m_oPreUpdateList.append(points);
			m_oUpdateList.append(points);

			nIColorIndex = nIndex % MAX_COLOR_NUM;
			pCurve->setPen( g_arrCurveColor[nIColorIndex], 1.3 );
			pCurve->setYAxis(QwtPlot::yRight);
		} 
		else
		{
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("A"));
			pCurve->setStyle( QwtPlotCurve::Steps );
			pCurve->setPen(g_arrCurveColor[nColorIndex],1.3);

			pCurve->setYAxis(QwtPlot::yRight);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->setSamples( points);
			pCurve->attach( this );
			m_oCurveList.append(pCurve);
			m_oUpdateList.append(points);		
		}


		nIndex++;
	}

	if (m_nType == 0)   //20210908 sf 兼容幅值相位频率
	{
		updateYTtile(/*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)",9,TRUE);
		updateYTtile(/*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)",9,FALSE);
	}
	else if (m_nType == 1)
	{
		updateYTtile(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase,9,TRUE);
		updateYTtile(tr(""),9,FALSE);
	}
	else
	{
		updateYTtile(/*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz,9,TRUE);
		updateYTtile(tr(""),9,FALSE);
	}

	if (m_bUseTesterTime)
	{
		UpdateXScale(0,30);
	}
}

void CChlTimeResponsePlot::slot_UpdateCurve()
{
	if(m_dLastTime > m_oXinterval.maxValue())
	{
		incrementInterval();
	}

	updateCurve(m_dLastTime);
}

void CChlTimeResponsePlot::start()
{
	clearCurveData();

	if (m_bUseTesterTime && (m_pLastPoints))//20230615 zhouhj 去除第二次开始测试后,一开始会有一条竖线的问题
	{
		m_pLastPoints->DeleteAll();
	}

	m_bFirst = true;

	int nNum = m_oChlUDatasList.GetCount() + m_oChlIDatasList.GetCount();
	QVector<QPointF> points;

	if (!m_bUseTesterTime)
	{
		for (int i=0;i<nNum;i++)
		{
			m_oUpdateList.append(points);
		}
	}

	UpdateXScale(0,30);
	replot();
}

void CChlTimeResponsePlot::ChangeType( int nType )
{
	m_nType = nType;

	if (m_nType == 0)   //20210908 sf 兼容幅值相位频率
	{
		updateYTtile(/*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)",9,TRUE);
		updateYTtile(/*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)",9,FALSE);
	}
	else if (m_nType == 1)
	{
		updateYTtile(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase,9,TRUE);
		updateYTtile(tr(""),9,FALSE);
	}
	else
	{
		updateYTtile(/*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz,9,TRUE);
		updateYTtile(tr(""),9,FALSE);
	}
}

void CChlTimeResponsePlot::AddPoint(CSttMacroChannels* pMacroChs)
{
	long nIndex = 0;
	POS pos = pMacroChs->GetHeadPosition();
	while(pos)
	{
		CSttMacroChannel* pMacroCh = (CSttMacroChannel*)pMacroChs->GetNext(pos);

		if((!m_oChlIDatasList.FindByID(pMacroCh->m_strID))&&
			(!m_oChlUDatasList.FindByID(pMacroCh->m_strID)))
		{
			continue;
		}

		QPointF pt;
		pt.setX(m_dLastTime);
		float fVal = 0;
		switch(m_nType)
		{
		case amplitude_type:
			fVal = pMacroCh->m_oRtDataCh.m_fMag; break;
		case phasor_type:

			fVal = pMacroCh->m_oRtDataCh.m_fAng;
			MakeAngleTo180(fVal);

// 			if(pMacroCh->m_oRtDataCh.m_fAng < 0)
// 			{
// 				fVal = pMacroCh->m_oRtDataCh.m_fAng + 360; 
// 			}
// 			else
// 			{
// 				fVal = pMacroCh->m_oRtDataCh.m_fAng; 
// 			}

			break;
		case fre_type:
			fVal = pMacroCh->m_oRtDataCh.m_fFreq; break;
		default:
			break;
		}

// 		if ((m_nChannel == iabcAdd_type || m_nChannel == ia2b2c2Add_type) && m_nType == amplitude_type)
// 		{
// 			fVal = fVal * 3;
// 		}

		pt.setY(fVal);

		QStateMonitorData* pLastPoint = (QStateMonitorData*)m_pLastPoints->FindByID(pMacroCh->m_strID);
		if(pLastPoint)
		{
			//存在上一节点则从上一节点开始继续绘图
			QPointF ptLast = pLastPoint->m_oPoint;
			QPointF ptMid = QPointF(pt.x(), ptLast.y());
//			QPointF ptMid = QPointF(pt.x(), pt.y());
			m_oPreUpdateList[nIndex].push_back(ptMid);
			m_oPreUpdateList[nIndex].push_back(pt);
			//更新上一节点
			pLastPoint->m_oPoint = pt;
		}
		else
		{
			//不存在上一节点则添加
			QStateMonitorData* pPoint = new QStateMonitorData;
			pPoint->m_strID = pMacroCh->m_strID;
			pPoint->m_oPoint = pt;
			m_pLastPoints->AddNewChild(pPoint);
			m_oPreUpdateList[nIndex].push_back(pt);
		}

		nIndex++;
	}
}

void CChlTimeResponsePlot::UpdateValueText()
{
	//暂不更新文本内容 zhouhj
// 	long nIndex = 0;
// 	POS pos = m_oChlUDatasList.GetHeadPosition();
// 
// 	while (pos)
// 	{
// 		CSttMacroChannel* pMacroCh = (CSttMacroChannel*)m_oChlUDatasList.GetNext(pos);
// 		QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
// 		CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());
// 		if(pCurvePoints->size())
// 		{
// 			CString strText = "[";
// 			strText += QString::number(pCurvePoints->samples().last().y());
// 			if(pMacroCh->m_strID.contains("I"))
// 			{
// 				strText += "A]";
// 			}
// 			else
// 			{
// 				strText += "V]";
// 			}
// 
// 			if(m_vecChlValue.size())//
// 			{		
// 				m_vecChlValue[nIndex]->setText(strText);
// 			}
// 			else
// 			{
// 				m_labelValue.setText(strText);
// 			}
// 		}
// 
// 		nIndex++;
// 	}
// 
// 	pos = m_oChlIDatasList.GetHeadPosition();
// 
// 	while (pos)
// 	{
// 		CSttMacroChannel* pMacroCh = (CSttMacroChannel*)m_oChlIDatasList.GetNext(pos);
// 		QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
// 		CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());
// 		if(pCurvePoints->size())
// 		{
// 			CString strText = "[";
// 			strText += QString::number(pCurvePoints->samples().last().y());
// 			if(pMacroCh->m_strID.contains("I"))
// 			{
// 				strText += "A]";
// 			}
// 			else
// 			{
// 				strText += "V]";
// 			}
// 
// 			if(m_vecChlValue.size())//
// 			{		
// 				m_vecChlValue[nIndex]->setText(strText);
// 			}
// 			else
// 			{
// 				m_labelValue.setText(strText);
// 			}
// 		}
// 
// 		nIndex++;
// 	}
}
