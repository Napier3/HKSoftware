#include "StateMonitorVoltCur.h"
#include "../../../SttTestResourceMngr/RtDataMngr/SttMacroChannels.h"
#include "StateMonitorWidget.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"

QColor CurveColor[4] = {Qt::yellow,Qt::green,Qt::red,Qt::magenta};

QStateMonitorVoltCur::QStateMonitorVoltCur(QWidget* parent)
{
	m_nChannel = -1;
	m_ChangeType = 0;
	m_labelText.setParent(this->canvas());
	m_labelText.setStyleSheet(" QLabel{  background-color:black;color: rgb(85, 255, 0); }");
	m_labelValue.setParent(this->canvas());
	m_labelValue.setStyleSheet(" QLabel{  background-color:black;color: rgb(85, 255, 0); }");
	long nWidth = this->canvas()->width() + 500;
	long nHeight = this->font().pointSize() + 6;
	m_labelText.setGeometry(2, 1, nWidth, nHeight);
	m_labelValue.setGeometry(2 + 60, 1, nWidth, nHeight);
}

QStateMonitorVoltCur::~QStateMonitorVoltCur()
{
	for (int i = 0; i < m_vecChlLabel.size(); i++)
	{
		delete m_vecChlLabel[i];
	}
	m_vecChlLabel.clear();

	for (int i = 0; i < m_vecChlValue.size(); i++)
	{
		delete m_vecChlValue[i];
	}
	m_vecChlValue.clear();
}

void QStateMonitorVoltCur::SetSingleTitle(const CString& strTitle)
{
	m_labelText.setText(strTitle);
}

void QStateMonitorVoltCur::InitCurve(CExBaseList* pChlUDatasList, CExBaseList* pChlIDatasList)
{
	QwtPlotCurve *pCurve = NULL;
	QVector<QPointF> points;
	if(g_pStateMonitorWidget->IsSingle())
	{
		m_labelText.show();
		m_labelValue.show();
		for (int i = 0; i < m_oMacroChannels.GetCount(); i++)
		{
			//初始化单通道图形
			pCurve = new QwtPlotCurve();
			pCurve->setTitle("Gradient");
			pCurve->setPen(CurveColor[1], 2);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			CurveData* pData = new CurveData;
			pCurve->setData(pData);
			//pCurve->setSamples(points);
			m_oCurveList.append(pCurve);
			m_oPreUpdateList.append(points);
			m_oUpdateList.append(points);
		}

		for (int i = 0; i < m_vecChlLabel.size(); i++)
		{
			m_vecChlLabel[i]->hide();
			m_vecChlValue[i]->hide();
		}

		setContentsMargins(0, 0, 50, 0);
	}
	else
	{
		m_labelText.hide();
		m_labelValue.hide();
		m_oMacroChannels.Append(pChlUDatasList);
		m_oMacroChannels.Append(pChlIDatasList);
		//初始化多通道图形
		for (int i = 0; i < m_oMacroChannels.GetCount(); i++)
		{
			pCurve = new QwtPlotCurve();
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			CurveData* pData = new CurveData;
			pCurve->setData(pData);
			//pCurve->setSamples(points);
			m_oCurveList.append(pCurve);
			m_oPreUpdateList.append(points);
			m_oUpdateList.append(points);

			QLabel* pLabel = new QLabel(this);
			m_vecChlLabel.append(pLabel);
			pLabel = new QLabel(this);
			m_vecChlValue.append(pLabel);
		}

		long nIColorIndex = 0, nVColorIndex = 0;
		POS pos = pChlUDatasList->GetHeadPosition();
		long nIndexV = 0, nIndexI = 0;
		QFont oFont = this->font();
		long nHeight = oFont.pointSize() + 6;
		oFont.setBold(true);
		while(pos)
		{
			CSttMacroChannel *pChl = (CSttMacroChannel *)pChlUDatasList->GetNext(pos);
			//电压
			QwtPlotCurve *pCurveV = m_oCurveList[nIndexV];
			nVColorIndex = nIndexV % MAX_COLOR_NUM;
			pCurveV->setTitle("V");
			pCurveV->setPen( CurveColor[nVColorIndex], 2.5 );
			pCurveV->setYAxis(QwtPlot::yLeft);

			m_vecChlLabel[nIndexV]->setStyleSheet(GetCurveStyleSheet(nVColorIndex));
			m_vecChlLabel[nIndexV]->setText(pChl->m_strName);
			m_vecChlLabel[nIndexV]->setGeometry(60 + 120 * nIndexV, 8, 30, nHeight);
			m_vecChlLabel[nIndexV]->setFont(oFont);

			m_vecChlValue[nIndexV]->setStyleSheet(GetCurveStyleSheet(nVColorIndex));
			m_vecChlValue[nIndexV]->setGeometry(90 + 120 * nIndexV, 8, 90, nHeight);
			m_vecChlValue[nIndexV]->setFont(oFont);

			nIndexV++;
		}

		pos = pChlIDatasList->GetHeadPosition();
		while (pos)
		{
			CSttMacroChannel *pChl = (CSttMacroChannel *)pChlIDatasList->GetNext(pos);
			//电流
			QwtPlotCurve *pCurveI = m_oCurveList[nIndexV + nIndexI];
			nIColorIndex = nIndexI % MAX_COLOR_NUM;
			pCurveI->setTitle("A");
			pCurveI->setPen( CurveColor[nIColorIndex], 1.3 );
			pCurveI->setYAxis(QwtPlot::yRight);

			m_vecChlLabel[nIndexV + nIndexI]->setStyleSheet(GetCurveStyleSheet(nIColorIndex));
			m_vecChlLabel[nIndexV + nIndexI]->setText(pChl->m_strName);
			m_vecChlLabel[nIndexV + nIndexI]->setGeometry(nIndexV * 120 + 60 + 120 * nIndexI, 8, 30, nHeight);

			m_vecChlValue[nIndexV + nIndexI]->setStyleSheet(GetCurveStyleSheet(nIColorIndex));
			m_vecChlValue[nIndexV + nIndexI]->setGeometry(nIndexV * 120 + 90 + 120 * nIndexI, 8, 90, nHeight);

			nIndexI++;
		}

		for (int i = 0; i < nIndexI + nIndexV; i++)
		{
			m_vecChlLabel[i]->show();
			m_vecChlValue[i]->show();
		}

		for (int i = nIndexI + nIndexV; i < m_vecChlLabel.size(); i++)
		{
			m_vecChlLabel[i]->hide();
			m_vecChlValue[i]->hide();
		}

		setContentsMargins(0, 0, 25, 0);
	}

	if (m_ChangeType == 0)   //20210908 sf 兼容幅值相位频率
	{
		UpdateYTtile(/*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)",9,TRUE);
		UpdateYTtile(/*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)",9,FALSE);
	}
	else if (m_ChangeType == 1)
	{
		UpdateYTtile(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase,9,TRUE);
		UpdateYTtile(tr(""),FALSE);
	}
	else
	{
		UpdateYTtile(/*tr("频率(Hz)")*/g_sLangTxt_Frequency ,9,TRUE);
		UpdateYTtile(tr(""),9,FALSE);
	}
}


void QStateMonitorVoltCur::InitYTick(double fUMin, double fUMax, double fIMin, double fIMax)
{
	enableAxis(QwtPlot::yRight,true);

	//取整10
	int nUMin = ((int)fUMin%10==0) ? (int)fUMin:((int)fUMin/10-1)*10;
	int nUMax = ((int)fUMax%10==0) ? (int)fUMax:((int)fUMax/10+1)*10;
	if (nUMax <= 0)
	{
		nUMax = g_oSystemParas.m_fVNom;
	}

	if (m_ChangeType == amplitude_type)//zhouhj 20211031  对于相位和频率递变,不需要在最大值的基础上增加40
	{
		nUMax += 20;	
	}

	UpdateYScale(nUMin,nUMax);

	//取整5
	int nIMin = ((int)fIMin%5==0) ? (int)fIMin:((int)fIMin/5-1)*5;
	int nIMax = ((int)fIMax%5==0) ? (int)fIMax:((int)fIMax/5+1)*5;
	if (nIMax <= 0)
	{
		nIMax = g_oSystemParas.m_fINom;
	}

	if (m_ChangeType == amplitude_type)//zhouhj 20211031  对于相位和频率递变,不需要在最大值的基础上增加20
	{
		nIMax += 10;	
	}

	UpdateYScale(nIMin,nIMax,FALSE);

	setAxisScaleDraw(QwtPlot::yLeft,new UIYScaleDraw());
	setAxisScale(QwtPlot::yLeft,nUMin,nUMax);

	setAxisScaleDraw(QwtPlot::yRight,new UIYScaleDraw());
	setAxisScale(QwtPlot::yRight,nIMin,nIMax);
}

void QStateMonitorVoltCur::AddPoint(CSttMacroChannels* pMacroChs)
{
	long nIndex = 0;
	POS pos = pMacroChs->GetHeadPosition();
	while(pos)
	{
		CSttMacroChannel* pMacroCh = (CSttMacroChannel*)pMacroChs->GetNext(pos);

		if(!m_oMacroChannels.FindByID(pMacroCh->m_strID))
		{
			continue;
		}

		QPointF pt;
		pt.setX(m_dLastTime);
		float fVal = 0;
		switch(m_ChangeType)
		{
		case amplitude_type:
			fVal = pMacroCh->m_oRtDataCh.m_fMag; break;
		case phasor_type:
			if(pMacroCh->m_oRtDataCh.m_fAng < 0)
			{
				fVal = pMacroCh->m_oRtDataCh.m_fAng + 360; 
			}
			else
			{
				fVal = pMacroCh->m_oRtDataCh.m_fAng; 
			}
			break;
		case fre_type:
			fVal = pMacroCh->m_oRtDataCh.m_fFreq; break;
		default:
			break;
		}

		if ((m_nChannel == iabcAdd_type || m_nChannel == ia2b2c2Add_type) && m_ChangeType == amplitude_type)
		{
			fVal = fVal * 3;
		}

		pt.setY(fVal);

		QStateMonitorData* pLastPoint = (QStateMonitorData*)m_pLastPoints->FindByID(pMacroCh->m_strID);
		if(pLastPoint)
		{
			//存在上一节点则从上一节点开始继续绘图
			QPointF ptLast = pLastPoint->m_oPoint;
			QPointF ptMid = QPointF(pt.x(), ptLast.y());
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

void QStateMonitorVoltCur::UpdateSingleChannel(int nChannel, int nType, bool bStart)
{
	m_ChangeType = nType;
	m_nChannel = nChannel;
	ChangeType(nType);
	GetMacroChannel(nChannel);
	//单通道状态图是切换的而不是创建的,所以初始化时其通道为0,需要重新初始化通道
	InitCurve(0, 0);
}

CSttMacroChannel* QStateMonitorVoltCur::GetCurMacroChannelClone(int nChannel)
{
	CSttMacroChannel* pChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(nChannel);
	return (CSttMacroChannel*)pChannel->Clone();
}

CSttMacroChannel* QStateMonitorVoltCur::GetVoltMacroChannelClone(int nChannel)
{
	CSttMacroChannel* pChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(nChannel);
	return (CSttMacroChannel*)pChannel->Clone();
}

void QStateMonitorVoltCur::UpdateValueText()
{
	long nIndex = 0;
	POS pos = m_oMacroChannels.GetHeadPosition();
	while (pos)
	{
		CSttMacroChannel* pMacroCh = (CSttMacroChannel*)m_oMacroChannels.GetNext(pos);
		QwtPlotCurve* pCurve = m_oCurveList.at(nIndex);
		CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());
		if(pCurvePoints->size())
		{
			CString strText = "[";
			strText += QString::number(pCurvePoints->samples().last().y());
			if(pMacroCh->m_strID.contains("I"))
			{
				strText += "A]";
			}
			else
			{
				strText += "V]";
			}

			if(m_vecChlValue.size())
			{		
				m_vecChlValue[nIndex]->setText(strText);
			}
			else
			{
				m_labelValue.setText(strText);
			}
		}
		nIndex++;
	}
}

void QStateMonitorVoltCur::GetMacroChannel(int nChannel)
{
	CSttMacroChannel* pMacroChannel = NULL;
	m_oMacroChannels.DeleteAll();

	if (nChannel == ia1_type)
	{
		pMacroChannel = GetCurMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iab1_type)
	{
		pMacroChannel = GetCurMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iabc1_type || nChannel == iabcAdd_type)
	{
		pMacroChannel = GetCurMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ib1_type)
	{
		pMacroChannel = GetCurMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ibc1_type)
	{
		pMacroChannel = GetCurMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ic1_type )
	{
		pMacroChannel = GetCurMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ica1_type)
	{
		pMacroChannel = GetCurMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ia2_type)
	{
		pMacroChannel = GetCurMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iab2_type)
	{
		pMacroChannel = GetCurMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iabc2_type || nChannel == ia2b2c2Add_type)
	{
		pMacroChannel = GetCurMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ib2_type)
	{
		pMacroChannel = GetCurMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ibc2_type)
	{
		pMacroChannel = GetCurMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ic2_type)
	{
		pMacroChannel = GetCurMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ica2_type)
	{
		pMacroChannel = GetCurMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iall_type)
	{
		pMacroChannel = GetCurMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetCurMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == va1_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vab1_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vabc1_type || nChannel == vabcAdd_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vb1_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vbc1_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vc1_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vca1_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == va2_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vab2_type )
	{
		pMacroChannel = GetVoltMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vabc2_type || nChannel == va2b2c2Add_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vb2_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vbc2_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vc2_type )
	{
		pMacroChannel = GetVoltMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vca2_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vall_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(2);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = GetVoltMacroChannelClone(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == freAll_type)
	{
		pMacroChannel = GetVoltMacroChannelClone(0);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
}

void QStateMonitorVoltCur::ChangeType(int type)
{
	m_ChangeType = type;

	if (m_ChangeType == 0)   //20210908 sf 兼容幅值相位频率
	{
		UpdateYTtile(/*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)",9,TRUE);
		UpdateYTtile(/*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)",9,FALSE);
	}
	else if (m_ChangeType == 1)
	{
		UpdateYTtile(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase,9,TRUE);
		UpdateYTtile(tr(""),FALSE);
	}
	else
	{
		UpdateYTtile(/*tr("频率(Hz)")*/g_sLangTxt_Frequency ,9,TRUE);
		UpdateYTtile(tr(""),9,FALSE);
	}
}