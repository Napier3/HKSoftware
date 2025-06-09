#include <qmath.h>
#include <qcolor.h>
#include <QMessageBox>

#include "ChlTimeResponsePlotEx.h"
#include "../CommonMethod/commonMethod.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "StateMonitor.h"

QColor CurveColor[4] = {Qt::yellow,Qt::green,Qt::red,Qt::black};

class Background: public QwtPlotItem
{
public:
	Background()
	{
		setZ( 0.0 );
	}

	virtual int rtti() const
	{
		return QwtPlotItem::Rtti_PlotUserItem;
	}

	virtual void draw( QPainter *painter,
		const QwtScaleMap &, const QwtScaleMap &yMap,
		const QRectF &canvasRect ) const
	{
		QColor c( QColor( 167, 183, 165 ) );
		QColor c2( Qt::black);
		QRectF r = canvasRect;
		painter->fillRect( r, c );
	}
};

class VScaleDraw: public QwtScaleDraw        //自画坐标轴
{
public:
	VScaleDraw()
	{
	}
	virtual QwtText label( double v ) const  //重绘坐标轴 刻度值
	{
		if (v>=0 && v<10)
		{
			return QwtText( QString::number( v,'f',3 ) );
		}
		else if (v>=10 && v<100)
		{
			return QwtText( QString::number( v,'f',2 ) );
		}
		else if (v>=100 && v<1000)
		{
			return QwtText( QString::number( v,'f',1 ) );
		}
		else if (v>=1000)
		{
			return QwtText( QString::number( v ) );
		}
		else
		{
			return QwtText( "" );
		}
	}
};

CChlTimeResponsePlotEx::CChlTimeResponsePlotEx( QWidget *parent ):
	CTimeResponsePlotBase( parent )
{
	m_ChangeType =0;
	m_nChannel = -1;

	m_Xinterval.setMinValue(0.0);
	m_Xinterval.setMaxValue(30.0);

	m_Yinterval.setMinValue(0.0);
	m_Yinterval.setMaxValue(120);
	
	this->plotLayout()->setAlignCanvasToScales( true ); 

	enableAxis(QwtPlot::xBottom,true);
	enableAxis(QwtPlot::yRight,true);

	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->setPen( Qt::darkGray, 0.0, Qt::DotLine );
	grid->enableX( true );
	grid->enableY( true );
	grid->attach( this );

	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	setCanvas( canvas );

	Background *bg = new Background();
	bg->attach( this );

	d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		this->canvas() );
	d_picker->setStateMachine( new QwtPickerDragPointMachine() );
	d_picker->setRubberBandPen( QColor( Qt::green ) );
	d_picker->setRubberBand( QwtPicker::CrossRubberBand );
	d_picker->setTrackerPen( QColor( Qt::black ) );

	//color: rgb(85, 255, 0);
	QFont fonttTemp = this->font();
	QFontMetrics fontMetrics = QFontMetrics(fonttTemp);
	int nHeight = fontMetrics.height() + 6;
	m_PlotLabelText = new QLabel(this->canvas());
	m_PlotLabelText->setStyleSheet(" QLabel{  background-color:black;color: rgb(85, 255, 0); }");
	int width = this->canvas()->width()+500;
	m_PlotLabelText->setGeometry(2,1,width,nHeight);
	m_PlotLabelText->setText(tr("   "));

	setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

	QList<double> ticks[QwtScaleDiv::NTickTypes];
	ticks[QwtScaleDiv::MajorTick]<< 0 <<20<<40<<60<<80<<100<<120<<130 ;  //0和10处显示长刻度，坐标轴也只显示0与10 
	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );

	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDraw(QwtPlot::yLeft,new VScaleDraw());

	setAxisScaleDiv(QwtPlot::yRight, scaleDiv);
	setAxisScaleDraw(QwtPlot::yRight,new VScaleDraw());

	QwtScaleWidget *wid = axisWidget( 0 );
	QFont ft;
	ft.setPointSize(12);
	wid->setFont(ft);

	wid = axisWidget(1);
	wid->setFont(ft);

	QwtScaleWidget *widx = axisWidget( 2 );
	QFont ftx;
	ftx.setPointSize(12);
	widx->setFont(ftx);
	
	setAutoReplot( true );

	m_bStart = false;
	m_bInited = false;
}

CChlTimeResponsePlotEx::~CChlTimeResponsePlotEx()
{
	m_oChlUDatasList.RemoveAll();
	m_oChlIDatasList.RemoveAll();

	m_oMacroChannels.RemoveAll();

	clearRtDataList();
}

void CChlTimeResponsePlotEx::clearRtDataList()
{
	for (int i=0;i<m_rtDataList.size();i++)
	{
		delete m_rtDataList[i];
	}

	m_rtDataList.clear();

	m_bInited = false;
}

void CChlTimeResponsePlotEx::setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList)
{
	m_oChlUDatasList.RemoveAll();
	m_oChlIDatasList.RemoveAll();
	m_oMacroChannels.RemoveAll();

	m_oChlUDatasList.Append(oChlUDatasList);
	m_oChlIDatasList.Append(oChlIDatasList);
	m_oMacroChannels.Append(oChlUDatasList);
	m_oMacroChannels.Append(oChlIDatasList);

	initCurve();
}

void CChlTimeResponsePlotEx::setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList
										,double fUMin,double fUMax,double fIMin,double fIMax)
{
	m_oChlUDatasList.RemoveAll();
	m_oChlIDatasList.RemoveAll();
	m_oMacroChannels.RemoveAll();

	m_oChlUDatasList.Append(oChlUDatasList);
	m_oChlIDatasList.Append(oChlIDatasList);
	m_oMacroChannels.Append(oChlUDatasList);
	m_oMacroChannels.Append(oChlIDatasList);

	updateXScale(0,30);
	InitYTick(fUMin,fUMax,fIMin,fIMax);

	initCurve();
}

void CChlTimeResponsePlotEx::InitYTick(double fUMin,double fUMax,double fIMin,double fIMax)
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

	CTimeResponsePlotBase::updateYScale(nUMin,nUMax);

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

	CTimeResponsePlotBase::updateYScale(nIMin,nIMax,FALSE);

	setAxisScaleDraw(QwtPlot::yLeft,new UIYScaleDraw());
	setAxisScale(QwtPlot::yLeft,nUMin,nUMax);

	setAxisScaleDraw(QwtPlot::yRight,new UIYScaleDraw());
	setAxisScale(QwtPlot::yRight,nIMin,nIMax);
}

void CChlTimeResponsePlotEx::slot_UpdateCurveEx()
{

}

void CChlTimeResponsePlotEx::start()
{
	//initCurve();
	m_bFirst = true;
	m_oSignalList.RemoveAll();
	m_bInited = true;

	updateXScale(0,30);

	m_Xinterval.setMinValue(0);
	m_Xinterval.setMaxValue(30);
	setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz   ");

	m_bStart = true;
}

void CChlTimeResponsePlotEx::stop()
{
	m_bStart = false;
	m_bFirst = false;
}

void CChlTimeResponsePlotEx::initCurve()
{
	clearCurvePlot();
	QwtPlotCurve *pCurve = NULL;
	if(g_pStateMonitor->m_bIsPlotEx)
	{
		for (int i=0;i<m_oMacroChannels.GetCount();i++)
		{
			QVector<QPointF> points;
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("Gradient"));
			pCurve->setPen( CurveColor[1], 2 );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			pCurve->setSamples(points);
			m_CurveList.append(pCurve);
			m_CurveDataList.append(points);
		}
	}
	else
	{
		m_PlotLabelText->hide();
		QVector<QPointF> points;
		long nIColorIndex = 0, nVColorIndex = 0;
		QFont fonttTemp = this->font();
		QFontMetrics fontMetrics = QFontMetrics(fonttTemp);
		int nHeight = fontMetrics.height();
		POS pos = m_oChlUDatasList.GetHeadPosition();
		long nIndexV = 0, nIndexI = 0;
		while(pos)
		{
			CSttMacroChannel *pChl = (CSttMacroChannel *)m_oChlUDatasList.GetNext(pos);
			//电压
			nVColorIndex = nIndexV % MAX_COLOR_NUM;
			QLabel *pLabel = new QLabel(this->canvas());
			pLabel->setStyleSheet(GetCurveStyleSheetString(nVColorIndex));
			pLabel->setText("-- " + pChl->m_strName);
			pLabel->setGeometry(10+80*(nIndexV),1,80,nHeight);
			m_vecChlULabel.append(pLabel);

			pCurve = new QwtPlotCurve();
			pCurve->setTitle("V");
			pCurve->setPen( CurveColor[nVColorIndex], 2.5 );
			pCurve->setYAxis(QwtPlot::yLeft);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			pCurve->setSamples(points);
			m_CurveList.append(pCurve);
			m_CurveDataList.append(points);
			nIndexV++;
		}

		pos = m_oChlIDatasList.GetHeadPosition();
		while (pos)
		{
			CSttMacroChannel *pChl = (CSttMacroChannel *)m_oChlIDatasList.GetNext(pos);
			//电流
			nIColorIndex = nIndexI % MAX_COLOR_NUM;
			QLabel *pLabel = new QLabel(this->canvas());
			pLabel->setStyleSheet(GetCurveStyleSheetString(nIColorIndex));
			pLabel->setText("-- " + pChl->m_strName);
			pLabel->setGeometry(nIndexV*80 + 10 +80*(nIndexI),1,80,nHeight);
			m_vecChlULabel.append(pLabel);

			pCurve = new QwtPlotCurve();
			pCurve->setTitle("A");
			pCurve->setPen( CurveColor[nIColorIndex], 1.3 );
			pCurve->setYAxis(QwtPlot::yRight);
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pCurve->attach(this);
			pCurve->setSamples(points);
			m_CurveList.append(pCurve);
			m_CurveDataList.append(points);
			nIndexI++;
		}
	}

	clearRtDataList();

	tmt_RtDataCh *pNewRtData = NULL;
	for (int i=0;i<m_oMacroChannels.GetCount();i++)
	{
		pNewRtData = new tmt_RtDataCh;
		pNewRtData->m_nIndex = 0;
		m_rtDataList.append(pNewRtData);
	}

	m_oSignalList.DeleteAll();

	m_bInited = true;
}

CChlTimeSignal* CChlTimeResponsePlotEx::NewSignal()
{
	return new CChlTimeSignal();
}

void CChlTimeResponsePlotEx::AppendSignalData(CChlTimeSignal* pSignal,double dTime,tmt_RtDataCh* pCh)
{
	if(pCh == NULL || pSignal == NULL)
	{
		return;
	}

	pSignal->m_dLastTime = dTime;

	tmt_RtDataCh* pNew = new tmt_RtDataCh;
	pNew->m_nIndex = 0;
	pNew->m_fMag = pCh->m_fMag;
	pNew->m_fAng = pCh->m_fAng;
	pNew->m_fFreq = pCh->m_fFreq;

	pSignal->m_rtDataList.append(pNew);
}

void CChlTimeResponsePlotEx::AppenSignalInfo(CChlTimeSignal *pSignalInfo)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	m_oSignalList.AddTail(pSignalInfo);
}

void CChlTimeResponsePlotEx::GetSignalInfo(CExBaseList &oSignalInfoList)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	oSignalInfoList.AppendEx(m_oSignalList);
	m_oSignalList.RemoveAll();
}

void CChlTimeResponsePlotEx::onTimerEvent( QTimerEvent * )
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
		CChlTimeSignal *p = NULL;

		while(pos != NULL)
		{
			p = (CChlTimeSignal *)oSignalInfoList.GetNext(pos);
			updateSignal(p);

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

void CChlTimeResponsePlotEx::updateSignal(CChlTimeSignal* pSignalInfo)
{
	ASSERT(pSignalInfo != NULL);

	CSttMacroChannel *pChl = NULL;
	float fy=0;
	long nIndex = 0;
	float fVal = 0;
	QPointF pt;
	tmt_RtDataCh* pRtData = NULL;

	POS pos = m_oMacroChannels.GetHeadPosition();
	while(pos != NULL)
	{
		pChl = (CSttMacroChannel *)m_oMacroChannels.GetNext(pos);
		
		pt.setX(pSignalInfo->m_dLastTime);
		if (m_bFirst && pSignalInfo->m_dLastTime==0)
		{
			pt.setY(0);
		}
		else
		{
			pt.setY(m_CurveDataList[nIndex].last().ry());
		}

		pRtData = pSignalInfo->m_rtDataList[nIndex];
		if (pRtData == NULL)
		{
			continue;
		}

		if(m_ChangeType == amplitude_type)
		{
			fVal = pRtData->m_fMag;
		}
		else if (m_ChangeType == phasor_type)
		{
			if(pRtData->m_fAng<0)	//相位角调整为0~359
			{
				fVal = pRtData->m_fAng+360;
			}
			else
			{
				fVal = pRtData->m_fAng;
			}
		}
		else 
		{
			fVal = pRtData->m_fFreq;
		}

		if ((m_nChannel == iabcAdd_type || m_nChannel == ia2b2c2Add_type) && m_ChangeType == amplitude_type)
		{
			fVal = fVal*3;
		}

		pt.setY(fVal);

		if (m_CurveDataList[nIndex].size()>=4000)
		{
			m_CurveDataList[nIndex].pop_front();
		}

		QPointF LastPoint;
		for(int i = (m_CurveDataList[nIndex].count() - 1);i > 0;i--)
		{
			LastPoint = m_CurveDataList[nIndex].last();
			if((LastPoint.x()-pSignalInfo->m_dLastTime) > 0.0001)
			{
				m_CurveDataList[nIndex].pop_back();
			}
			else
			{
				break;
			}
		}

		//在递变位置添加一个时间相同值不同的点,保证递变位置是垂直的
		if(m_CurveDataList[nIndex].size() > 0)
		{
			LastPoint = m_CurveDataList[nIndex].last();
			LastPoint.setX(pSignalInfo->m_dLastTime);
			if(qAbs(LastPoint.y() - pt.y()) > 0.00001)
			{
				m_CurveDataList[nIndex].append(LastPoint);
			}
		}

		m_CurveDataList[nIndex].append(pt);
		m_CurveList[nIndex]->setSamples(m_CurveDataList[nIndex]);

		nIndex++;
	}

	replot();
}

void CChlTimeResponsePlotEx::updateCurve(double fv)
{
	//QPainter painter(this);
	//QPen  gridPen( Qt::gray, 1 );
	//gridPen.setStyle(Qt::DotLine);
	//painter.setPen(gridPen);

	CSttMacroChannel *pChl = NULL;
	float fy=0;
	long nIndex = 0;
	float fVal = 0;
	QPointF pt;
	tmt_RtDataCh rtData;

	POS pos = m_oMacroChannels.GetHeadPosition();
	while(pos != NULL)
	{
		pChl = (CSttMacroChannel *)m_oMacroChannels.GetNext(pos);

		pt.setX(fv);
		if (m_bFirst && fv==0)
		{
			pt.setY(0);
		}
		else
		{
			pt.setY(m_CurveDataList[nIndex].last().ry());
		}

		if (!pChl->m_oHisDataBuf.GetLastMemVal(rtData))
		{
			return;
		}

		if(m_ChangeType == amplitude_type)
		{
			fVal = rtData.m_fMag;
		}
		else if (m_ChangeType == phasor_type)
		{
			if(rtData.m_fAng<0)
			{
				fVal = rtData.m_fAng+360;
			}
			else
			{
				fVal = rtData.m_fAng;
			}
		}
		else 
		{
			fVal = rtData.m_fFreq;
		}
		
		if ((m_nChannel == iabcAdd_type || m_nChannel == ia2b2c2Add_type) && m_ChangeType == amplitude_type)
		{
			fVal = fVal*3;
		}

		pt.setY(fVal);

		if (m_CurveDataList[nIndex].size()>=4000)
		{
			m_CurveDataList[nIndex].pop_front();
		}

		QPointF LastPoint;
		for(int i = (m_CurveDataList[nIndex].count() - 1);i > 0;i--)
		{
			LastPoint = m_CurveDataList[nIndex].last();
			if((LastPoint.x()-fv) > 0.00001)
			{
				m_CurveDataList[nIndex].pop_back();
			}
			else
			{
				break;
			}
		}

		//在递变位置添加一个时间相同值不同的点,保证递变位置是垂直的
		if(m_CurveDataList[nIndex].size() > 0)
		{
			LastPoint = m_CurveDataList[nIndex].last();
			LastPoint.setX(fv);
			if(qAbs(LastPoint.y() - pt.y()) > 0.00001)
			{
				m_CurveDataList[nIndex].append(LastPoint);
			}
		}

		m_CurveDataList[nIndex].append(pt);
		m_CurveList[nIndex]->setSamples(m_CurveDataList[nIndex]);

		//painter.drawText(pt, QString::number(pt.y()));

		nIndex++;
	}

	replot();
}

void CChlTimeResponsePlotEx::updateYScale(changed_type type,QString str, float f1,float f2 )
{
	if (m_PlotLabelText)
	{
		m_PlotLabelText->setText(str);
		setYLeftRightScale(type,f1,f2,5);
	}
	
	replot();
}

void CChlTimeResponsePlotEx::updateYTtile( QString str)
{
	setAxisTitle( QwtPlot::yLeft, str );
	replot();
}

void CChlTimeResponsePlotEx::setYLeftRightScale(changed_type type,float fstart,float fend,int num)
{
	QList<double> ticks[QwtScaleDiv::NTickTypes];

	if (type == amplitude_type || type == fre_type)
	{
		float fv=0;
		if (fstart > fend)
		{
			fv = fstart/num;
		}
		else
		{
			fv = fend/num;
		}

		QList<float> list;
		list.append(0);
		for (int i=0;i<num;i++)
		{
			list.append((float)((i+1)*fv));
		}
		if (fstart > fend)
		{
			list.append((float)(fstart*FRADIO));
		}
		else
		{
			list.append((float)(fend*FRADIO));
		}

		for (int i=0;i<list.size();i++)
		{
			ticks[QwtScaleDiv::MajorTick].append(list.at(i));
		}

		setAxisScale( QwtPlot::yLeft, fstart, fend );
	}
	else if (type == phasor_type)
	{
		QList<float> list;
		list << 0 << 90 << 180 << 270 << 360 << 390;
		
		for (int i=0;i<list.size();i++)
		{
			ticks[QwtScaleDiv::MajorTick].append(list.at(i));
		}

		setAxisScale( QwtPlot::yLeft, 0, 360 );
	}

	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDiv(QwtPlot::yRight, scaleDiv);
}

void CChlTimeResponsePlotEx::setData( int nChannel,int type, bool bStart)
{
	if (bStart)
	{
		m_ChangeType = type;

		m_nChannel = nChannel;
		GetMacroChannelEx(nChannel);

		m_Xinterval.setMinValue(0);
		m_Xinterval.setMaxValue(30);
		setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

		initCurve();
	}
	else	//没开始实验
	{
		if(m_nChannel != nChannel)
		{
			QPointF pt;
			pt.setX(0);
			pt.setY(0);
			QVector<QPointF> points;
			QList<QVector<QPointF> > tmpCurveDataList;

			for (int i=0;i<m_oMacroChannels.GetCount();i++)
			{
				tmpCurveDataList.append(points);
				tmpCurveDataList[i].append(pt);
				m_CurveList[i]->setSamples(tmpCurveDataList[i]);
			}
		}
		else
		{
			for (int i=0;i<m_oMacroChannels.GetCount();i++)
			{
				m_CurveList[i]->setSamples(m_CurveDataList[i]);
			}

			replot();
		}
	}
}

void CChlTimeResponsePlotEx::setData( CExBaseList &oChlDatasList, int type, bool bStart )
{
	if (bStart)
	{
		m_ChangeType = type;
		m_oMacroChannels.RemoveAll();
		m_oMacroChannels.Append(oChlDatasList);

		m_Xinterval.setMinValue(0);
		m_Xinterval.setMaxValue(30);
		setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

		initCurve();
	}
	else	//没开始实验
	{
		for (int i=0;i<m_oMacroChannels.GetCount();i++)
		{
			m_CurveList[i]->setSamples(m_CurveDataList[i]);
		}

		replot();
	}
}

//根据递变通道取得软件资源通道列表
CSttMacroChannel* CChlTimeResponsePlotEx::GetMacroChannel(int nChannel)	//博电旧模块
{
	CSttMacroChannel* pMacroChannel = NULL;

	if (nChannel == ia1_type || nChannel == iab1_type || nChannel == iabc1_type || nChannel == iabcAdd_type || nChannel == iall_type)//Change_IaAddIbAddIc
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(0);
	}
	else if (nChannel == ib1_type || nChannel == ibc1_type)
	{
		pMacroChannel =(CSttMacroChannel*) g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(1);
	}
	else if (nChannel == ic1_type || nChannel == ica1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(2);
	}
	else if (nChannel == ia2_type || nChannel == iab2_type || nChannel == iabc2_type || nChannel == ia2b2c2Add_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(3);
	}
	else if (nChannel == ib2_type || nChannel == ibc2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(4);
	}
	else if (nChannel == ic2_type || nChannel == ica2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(5);
	}
	else if (nChannel == va1_type || nChannel == vab1_type || nChannel == vabc1_type || nChannel == vall_type || nChannel == vabcAdd_type || nChannel == freAll_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
	}
	else if (nChannel == vb1_type || nChannel == vbc1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(1);
	}
	else if (nChannel == vc1_type || nChannel == vca1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(2);
	}
	else if (nChannel == va2_type || nChannel == vab2_type || nChannel == vabc2_type || nChannel == va2b2c2Add_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(3);
	}
	else if (nChannel == vb2_type || nChannel == vbc2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(4);
	}
	else if (nChannel == vc2_type || nChannel == vca2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(5);
	}
	
	return pMacroChannel;
}

void CChlTimeResponsePlotEx::GetMacroChannelEx(int nChannel)
{
	CSttMacroChannel* pMacroChannel = NULL;
	m_oMacroChannels.RemoveAll();

	if (nChannel == ia1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iab1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);
		
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iabc1_type || nChannel == iabcAdd_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ib1_type)
	{
		pMacroChannel =(CSttMacroChannel*) g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ibc1_type)
	{
		pMacroChannel =(CSttMacroChannel*) g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel =(CSttMacroChannel*) g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ic1_type )
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ica1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ia2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iab2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iabc2_type || nChannel == ia2b2c2Add_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ib2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ibc2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ic2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == ica2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == iall_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oCurChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == va1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vab1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vabc1_type || nChannel == vabcAdd_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vb1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vbc1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vc1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vca1_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == va2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vab2_type )
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vabc2_type || nChannel == va2b2c2Add_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vb2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vbc2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vc2_type )
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vca2_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == vall_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(1);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(2);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(3);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(4);
		m_oMacroChannels.AddTail(pMacroChannel);

		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(5);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
	else if (nChannel == freAll_type)
	{
		pMacroChannel = (CSttMacroChannel*)g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->m_oVolChListRef.GetAtIndex(0);
		m_oMacroChannels.AddTail(pMacroChannel);
	}
}
