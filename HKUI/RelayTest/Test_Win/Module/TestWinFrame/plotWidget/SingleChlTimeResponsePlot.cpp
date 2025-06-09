#include <qmath.h>
#include <qcolor>
#include <QMessageBox>

#include "SingleChlTimeResponsePlot.h"
#include "../../CommonMethod/commonMethod.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"

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

CSingleChlTimeResponsePlot::CSingleChlTimeResponsePlot( QWidget *parent ):
	CTimeResponsePlotBase( parent )
{
	m_bGet = false;
	m_ChangeType =0;

	m_pCurMacroChannel = NULL;
	m_pCurve = NULL;

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
	ft.setPointSize(7);
	wid->setFont(ft);

	wid = axisWidget(1);
	wid->setFont(ft);

	QwtScaleWidget *widx = axisWidget( 2 );
	QFont ftx;
	ftx.setPointSize(1);
	widx->setFont(ftx);
	
	setAutoReplot( true );
	m_nStartSecond = 0;
	m_nStartNanoSecond = 0;
	m_bStart = false;
}

CSingleChlTimeResponsePlot::~CSingleChlTimeResponsePlot()
{
	m_oChlUDatasList.RemoveAll();
	m_oChlIDatasList.RemoveAll();
}

void CSingleChlTimeResponsePlot::setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList)
{
	m_oChlUDatasList.RemoveAll();
	m_oChlIDatasList.RemoveAll();

	m_oChlUDatasList.Append(oChlUDatasList);
	m_oChlIDatasList.Append(oChlIDatasList);

	initCurve();
}

void CSingleChlTimeResponsePlot::start()
{
	clearCurveData();
	m_bFirst = true;

	QVector<QPointF> points;
	m_CurveDataList.append(points);

//	QPointF pt(0,0);
//	m_CurveDataList[0].append(pt);

	updateXScale(0,30);

	m_Xinterval.setMinValue(0);
	m_Xinterval.setMaxValue(30);
	setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz   ");

	m_bStart = true;
}

void CSingleChlTimeResponsePlot::stop()
{
	killTimer(d_timerId);
	d_timerId = -1;

	m_bStart = false;
	m_bFirst = false;
}

void CSingleChlTimeResponsePlot::initCurve()
{
	clearCurvePlot();
	m_pCurve = NULL;

	QVector<QPointF> points;
	m_pCurve = new QwtPlotCurve();
	m_pCurve->setTitle(tr("Gradient"));
	m_pCurve->setPen( CurveColor[1], 2 );
	m_pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	m_pCurve->setSamples(points);
	m_pCurve->attach(this);
	m_CurveList.append(m_pCurve);
	m_CurveDataList.append(points);
}

void CSingleChlTimeResponsePlot::updateCurve(double fv,BOOL bChanged)
{
	if(m_pCurMacroChannel == NULL)
	{
		return;
	}

	float fy=0;
	float fVal = 0;
	QPointF pt(fv,fy);

	pt.setX(fv);
	if (m_bFirst && fv==0)
	{
		pt.setY(0);
	}
	else
	{
		pt.setY(m_CurveDataList[0].last().ry());
	}

	if (bChanged)
	{
		//yyj delete 2021-08-25
//		if (!m_pCurMacroChannel->m_oHisMagBuf.GetLastMemVal(fVal))
//		{
//			return;
//		}

		//yyj add 2021-08-25
		tmt_rtdata_ch rtData;
		if (!m_pCurMacroChannel->m_oHisDataBuf.GetLastMemVal(rtData))
		{
			return;
		}

		if(m_ChangeType == amplitude_type)
		{
			fVal = rtData.m_fMag;
		}
		else if (m_ChangeType == phasor_type)
		{
			fVal = rtData.m_fAng;
		}
		else 
		{
			fVal = rtData.m_fFreq;
		}

		if ((m_nChannel == Change_IaAddIbAddIc || m_nChannel == Change_Ia2AddIb2AddIc2) && m_ChangeType == amplitude_type)
		{
			fVal = fVal*3;
		}

		pt.setY(fVal);
	}

	if (m_CurveDataList[0].size()>=4000)
	{
		m_CurveDataList[0].pop_front();
	}
	
	QPointF LastPoint;
	for(int i = (m_CurveDataList[0].count() - 1);i > 0;i--)
	{
		LastPoint = m_CurveDataList[0].last();
		if((LastPoint.x()-fv) > 0.0001)
		{
			m_CurveDataList[0].pop_back();
		}
		else
		{
			break;
		}
	}

	//在递变位置添加一个时间相同值不同的点,保证递变位置是垂直的
	if(m_CurveDataList[0].size() > 0)
	{
		LastPoint = m_CurveDataList[0].last();
		LastPoint.setX(fv);
		if(qAbs(LastPoint.y() - pt.y()) > 0.00001)
		{
			m_CurveDataList[0].append(LastPoint);
		}
	}

	m_CurveDataList[0].append(pt);
	m_CurveList[0]->setSamples(m_CurveDataList[0]);

	replot();
}

void CSingleChlTimeResponsePlot::updatePlot()
{
	clearCurveData();
	m_pCurve->setSamples(m_CurveDataList[0]);
	replot();
}

void CSingleChlTimeResponsePlot::updateXScale( float f1, float f2 )
{
	setAxisScale( QwtPlot::xBottom, f1, f2 );
	replot();
}

void CSingleChlTimeResponsePlot::updateYScale(changed_type type,QString str, float f1,float f2 )
{
	if (m_PlotLabelText)
	{
		m_PlotLabelText->setText(str);
		setYLeftRightScale(type,f1,f2,5);
	}
	
	replot();
}

void CSingleChlTimeResponsePlot::updateYTtile( QString str)
{
	setAxisTitle( QwtPlot::yLeft, str );
	replot();
}

void CSingleChlTimeResponsePlot::setYLeftRightScale(changed_type type,float fstart,float fend,int num)
{
	QList<double> ticks[QwtScaleDiv::NTickTypes];

	if (type == amplitude_type || fre_type)
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
	}
	else if (type == phasor_type)
	{
		QList<float> list;
		list << 0 << 90 << 180 << 270 << 360 << 390;
		for (int i=0;i<list.size();i++)
		{
			ticks[QwtScaleDiv::MajorTick].append(list.at(i));
		}
	}

	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDiv(QwtPlot::yRight, scaleDiv);
}

void CSingleChlTimeResponsePlot::timerEvent( QTimerEvent *event )
{
	if(m_bStart)
	{
		if ( event->timerId() == d_timerId && m_bGet==false)
		{
			if(m_CurveDataList[0].count() > 0)
			{
				QPointF point = m_CurveDataList[0].last();
				updateCurve(point.x() + 0.5,false);
				if ( (point.x() + 0.5) > m_Xinterval.maxValue() )
					incrementInterval();
			}
			return;
		}
	}
	else
	{
		killTimer(d_timerId);
		d_timerId = -1;
	}
	
	QwtPlot::timerEvent( event );
}

void CSingleChlTimeResponsePlot::setData( int nChannel,int type,unsigned int nSecond,unsigned int nNanoSecond, bool bStart)
{
	m_nChannel = nChannel;
	m_pCurMacroChannel = GetMacroChannel(nChannel);
	if(m_pCurMacroChannel == NULL)
	{
		return;
	}

	m_Xinterval.setMinValue(0);
	m_Xinterval.setMaxValue(30);
	setAxisScale( QwtPlot::xBottom, m_Xinterval.minValue(), m_Xinterval.maxValue() );

	//刷新标题电压、电流
	QString strTitle;
	if (type == amplitude_type)
	{
		if (m_pCurMacroChannel->m_nChannelType == STT_MACRO_CH_TYPE_VOL)
		{
			strTitle = /*tr("电压(V)")*/g_sLangTxt_Native_Voltage+"(V)";
		}
		else if (m_pCurMacroChannel->m_nChannelType == STT_MACRO_CH_TYPE_CUR)
		{
			strTitle = /*tr("电流(A)")*/g_sLangTxt_Native_Current+"(A)";
		}
	}
	else if (type == phasor_type)
	{
		strTitle = /*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase;
	}
	else
	{
		strTitle = /*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz;
	}

//	updateYTtile(strTitle);

	if (bStart)
	{
		killTimer(d_timerId);
		d_timerId = -1;

		m_ChangeType= type;
		m_bGet = true;
		double fTimeTemp = 0;
		int nSecondTemp = 0;
		int nNanoSecondTemp = 0;
		if(m_CurveDataList[0].size() == 0)
		{
			fTimeTemp = 0;
			m_nStartSecond = nSecond;
			m_nStartNanoSecond = nNanoSecond;
		}
		else
		{
			nSecondTemp = nSecond - m_nStartSecond;
			nNanoSecondTemp = nNanoSecond - m_nStartNanoSecond;
			fTimeTemp = (float)nSecondTemp + (float)nNanoSecondTemp/NANOSECOND;
		}

		updateCurve(fTimeTemp,false);
//		d_timerId = startTimer(500);

		if ( fTimeTemp > m_Xinterval.maxValue() )
		{
			incrementInterval();
		}

		m_bGet = false;
	}
	else	//没开始实验
	{
		m_pCurve->setSamples(m_CurveDataList[0]);
	}

	replot();
}

CSttMacroChannel* CSingleChlTimeResponsePlot::GetMacroChannel(int nChannel)
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