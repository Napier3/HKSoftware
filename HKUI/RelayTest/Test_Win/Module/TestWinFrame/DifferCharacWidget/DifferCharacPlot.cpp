#include <float.h>
#include "DifferCharacPlot.h"
#include <QDir>
#include <QMessageBox>
#include <QFont>
#include <QFontMetrics>
#include "../../Module/SttTest/Common/tmt_rtdata_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "../../../DifferTest/differtest.h"

#if QT_VERSION < 0x040601
#define qExp(x) ::exp(x)
#define qAtan2(y, x) ::atan2(y, x)
#endif

#define RADIO 1.5
CDifferCharacPlot::CDifferCharacPlot( QWidget *parent ):
    QwtPlot( parent )
{
	init();
    setAutoReplot( true );

	m_pCommonParaTest = NULL;
	m_popupMenu = NULL;
	m_addAction = NULL;
	m_fPointX = 0;
	m_fPointY = 0;
}

void CDifferCharacPlot::setData(TMT_PARAS_MNGR* pTmtTestMngr)
{
	ASSERT(pTmtTestMngr);
	m_pTmtTestMngr = pTmtTestMngr;

	m_pCommonParaTest = (tmt_DiffCurrThrTest*)pTmtTestMngr->m_pParasBuffer[0];

	initPlot();
	creatMaker();
}

void CDifferCharacPlot::init()
{
	bstartFlag = false;
	d_intervalCurve =  NULL;
	m_CurPos = NULL;

	setTitle( /*tr("特征曲线图")*/g_sLangTxt_Native_CurveGraph);
	setCanvasBackground( Qt::white );

	setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
	setAxisTitle( QwtPlot::yLeft, "Id(A)" );

	for ( int i = 0; i < this->axisCnt; i++ )  
	{  
		QwtScaleWidget *poScaleWidget = this->axisWidget( i);  
		if (poScaleWidget)  
		{  
			poScaleWidget->setMargin( 0 );  
		}  

		QwtScaleDraw *poScaleDraw = this->axisScaleDraw( i );  
	}  
	this->plotLayout()->setAlignCanvasToScales( true ); 

	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->setMajorPen( Qt::black, 0.2, Qt::DotLine );
	grid->attach( this);

	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	setCanvas( canvas );

	d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		this->canvas() );
	d_picker->setStateMachine( new QwtPickerDragPointMachine() );
	d_picker->setRubberBandPen( QColor( Qt::green ) );
	d_picker->setRubberBand( QwtPicker::CrossRubberBand );
	d_picker->setTrackerPen( QColor( Qt::black ) );

	QString str1 =  QString::number(2, 'f', 3);
	QString str2 =  QString::number(2, 'f', 3);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nHeight = fontMetrics.height()*5 ;
	int nLabelWidth = fontMetrics.width(tr("IR=00.000A")) + 5;
	m_PlotLabelText = new QLabel(this->canvas());
	
	m_PlotLabelText->setStyleSheet(" QLabel{  background-color:darkGray;color: blue }");
	m_PlotLabelText->setGeometry(20,5,nLabelWidth,nHeight);

	m_curve = new QwtPlotCurve();
	m_curve->setTitle( "Some Points" );
	m_curve->setPen( Qt::blue, 2 );
	m_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

	QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 2, 2 ) );
	m_curve->setSymbol( symbol );
	m_curve->attach( this );
}

void CDifferCharacPlot::initPlot()
{
	ASSERT(m_pCommonParaTest != NULL);
	if (m_pCommonParaTest == NULL)
	{
		return;
	}

	QString str1 =  QString::number(2, 'f', 3);
	QString str2 =  QString::number(2, 'f', 3);

	if (m_pCommonParaTest->m_oDiffCurrParas.m_bMinAxis == 0)  //有名值
	{
		if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 0) //高-低
		{
			m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
				+ QString("IH=%1A").arg(0)+ "\n" + QString("IL=%1A").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 1)	//高-中
		{
			m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
				+ QString("IH=%1A").arg(0)+ "\n" + QString("IM=%1A").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 2)  //中-低
		{
			m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
				+ QString("IM=%1A").arg(0)+ "\n" + QString("IL=%1A").arg(0));
		}
	}
	else
	{
		if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 0)
		{
			m_PlotLabelText->setText(QString("Ir=%1In").arg(str1) + "\n" + QString("Id=%1In").arg(str2)+ "\n"\
				+ QString("IH=%1In").arg(0)+ "\n" + QString("IL=%1In").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 1)
		{
			m_PlotLabelText->setText(QString("Ir=%1In").arg(str1) + "\n" + QString("Id=%1In").arg(str2)+ "\n"\
				+ QString("IH=%1In").arg(0)+ "\n" + QString("IM=%1In").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 2)
		{
			m_PlotLabelText->setText(QString("Ir=%1In").arg(str1) + "\n" + QString("Id=%1In").arg(str2)+ "\n"\
				+ QString("IM=%1In").arg(0)+ "\n" + QString("IL=%1In").arg(0));
		}
	}

	setAxisScale( QwtPlot::yLeft, 0.0, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd*RADIO );
	m_CurYScale = m_pCommonParaTest->m_oDiffCurrParas.m_fIsd*RADIO;
	m_curvePoints.clear();
	QVector<QwtIntervalSample> rangeData;
	
	switch(m_pCommonParaTest->m_oDiffCurrParas.m_nKneePoints)
	{
	case 1:
		{
			float y1 = m_pCommonParaTest->m_oDiffCurrParas.m_fIp1*m_pCommonParaTest->m_oDiffCurrParas.m_fKid0 + m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd;
			float xIsd = m_pCommonParaTest->m_oDiffCurrParas.m_fIp1+(m_pCommonParaTest->m_oDiffCurrParas.m_fIsd-y1)/m_pCommonParaTest->m_oDiffCurrParas.m_fKid1;
			m_CurXScale = xIsd*RADIO;
			m_curvePoints << QPointF( 0.0, m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd ) << QPointF( m_pCommonParaTest->m_oDiffCurrParas.m_fIp1, y1 )
				<< QPointF(xIsd, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd)<<QPointF(m_CurXScale, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd);

			generateErrorRangeData(m_curvePoints,rangeData,5); //5可取系统参数中的相对误差值
			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale);
		}
		break;
	case 2:
		{
			float y1 = m_pCommonParaTest->m_oDiffCurrParas.m_fIp1*m_pCommonParaTest->m_oDiffCurrParas.m_fKid0 + m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd;
			float y2 = y1 + (m_pCommonParaTest->m_oDiffCurrParas.m_fIp2-m_pCommonParaTest->m_oDiffCurrParas.m_fIp1)*m_pCommonParaTest->m_oDiffCurrParas.m_fKid1; //拐点2的Y坐标
			float xIsd = (m_pCommonParaTest->m_oDiffCurrParas.m_fIsd-y2)/m_pCommonParaTest->m_oDiffCurrParas.m_fKid2+m_pCommonParaTest->m_oDiffCurrParas.m_fIp2;
			m_CurXScale = xIsd*RADIO;
			m_curvePoints << QPointF( 0.0, m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd ) << QPointF( m_pCommonParaTest->m_oDiffCurrParas.m_fIp1, y1 )\
				<< QPointF( m_pCommonParaTest->m_oDiffCurrParas.m_fIp2, y2 )<< QPointF(xIsd, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd)\
				<<QPointF(m_CurXScale, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd);

			generateErrorRangeData(m_curvePoints,rangeData,5);
			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
		}
		break;
	case 3:
		{
			float y1 = m_pCommonParaTest->m_oDiffCurrParas.m_fIp1*m_pCommonParaTest->m_oDiffCurrParas.m_fKid0 + m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd;
			float y2 = y1 + (m_pCommonParaTest->m_oDiffCurrParas.m_fIp2-m_pCommonParaTest->m_oDiffCurrParas.m_fIp1)*m_pCommonParaTest->m_oDiffCurrParas.m_fKid1; //拐点2的Y坐标
			float y3 = y2+(m_pCommonParaTest->m_oDiffCurrParas.m_fIp3-m_pCommonParaTest->m_oDiffCurrParas.m_fIp2)*m_pCommonParaTest->m_oDiffCurrParas.m_fKid2; //拐点3的Y坐标
			float xIsd = m_pCommonParaTest->m_oDiffCurrParas.m_fIp3+(m_pCommonParaTest->m_oDiffCurrParas.m_fIsd-y3)/m_pCommonParaTest->m_oDiffCurrParas.m_fKid3; 
			m_CurXScale = xIsd*RADIO;

			m_curvePoints << QPointF( 0.0, m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd ) << QPointF( m_pCommonParaTest->m_oDiffCurrParas.m_fIp1, y1)
				<< QPointF(m_pCommonParaTest->m_oDiffCurrParas.m_fIp2, y2 )<<QPointF(m_pCommonParaTest->m_oDiffCurrParas.m_fIp3 , y3 )
				<<QPointF(xIsd, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd)<<QPointF(m_CurXScale, m_pCommonParaTest->m_oDiffCurrParas.m_fIsd);

			generateErrorRangeData(m_curvePoints,rangeData,6);
			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
		}
		break;
	default:
		break;
	}

	m_curve->setSamples( m_curvePoints );

	insertErrorBars( "Range", rangeData, Qt::blue );
}

void CDifferCharacPlot::creatMaker()
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker[i].PlotMaker->hide();
		delete m_PlotMarker[i].PlotMaker;
		delete m_PlotMarker[i].PlotCurve;
		m_PlotMarker[i].PlotMaker = NULL;
		m_PlotMarker[i].PlotCurve = NULL;
	}
	m_PlotMarker.clear();

	if (m_CurPos)
	{
		delete m_CurPos;
		m_CurPos = NULL;
	}

	QwtPlotCurve  *pCurve = NULL;
	QwtPlotMarker *pMaker = NULL;
	PTMT_PARAS_HEAD pHead = NULL;

	for (int i=0;i<m_pTmtTestMngr->m_nCount;i++)
	{
		pHead = m_pTmtTestMngr->m_pParasBuffer[i];
		if(strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0)
		{
			tmt_DiffCurrThrTest* pThrTest = (tmt_DiffCurrThrTest*)pHead;

			MakerLine maker;
			maker.m_pCurrThrTest = pThrTest;

			pCurve = new QwtPlotCurve();
			if (pThrTest->m_nThrType == TEST_QD) //启动电流
			{
				pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
			}
			else	//动作特性曲线
			{
				QString str1 = QString::number(pThrTest->m_oDiffCurrParas.m_fIbias,'f',3);	
				QString strTitle;
				strTitle = /*tr("动作特性曲线 ")*/g_sLangTxt_Native_CharactCurve+"Ir="+str1+"*"+"A";

				pCurve->setTitle(strTitle);
			}
			pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDiffCurrParas.m_fIbias, pThrTest->m_oDiffCurrParas.m_fScanTo) 
						<< QPointF( pThrTest->m_oDiffCurrParas.m_fIbias, pThrTest->m_oDiffCurrParas.m_fScanFrom);
			pCurve->setSamples( curvePoints );
			pCurve->attach(this);

			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );

			maker.PlotCurve = pCurve;
			maker.PlotMaker = pMaker;
			m_PlotMarker.append(maker);
		}
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
		{
			tmt_DiffCurrRateTest* pRateTest = (tmt_DiffCurrRateTest*)pHead;

			MakerLine maker;
			maker.m_pCurrThrTest = pRateTest;

			pCurve = new QwtPlotCurve();
			if(pRateTest->m_nRateType == TEST_ZD1 || pRateTest->m_nRateType == TEST_ZD1_2)
			{
				pCurve->setTitle(tr("ZD1 Ir"));
			}
			else if (pRateTest->m_nRateType == TEST_ZD2 || pRateTest->m_nRateType == TEST_ZD2_2)
			{
				pCurve->setTitle(tr("ZD2 Ir"));
			}
			else if (pRateTest->m_nRateType == TEST_ZD3 || pRateTest->m_nRateType == TEST_ZD3_2)
			{
				pCurve->setTitle(tr("ZD3 Ir"));
			}
			else if (pRateTest->m_nRateType == TEST_ZD4 || pRateTest->m_nRateType == TEST_ZD4_2)
			{
				pCurve->setTitle(tr("ZD4 Ir"));
			}

			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pRateTest->m_oDiffCurrParas.m_fIbias, pRateTest->m_oDiffCurrParas.m_fScanTo) 
						<< QPointF( pRateTest->m_oDiffCurrParas.m_fIbias, pRateTest->m_oDiffCurrParas.m_fScanFrom);
			pCurve->setSamples( curvePoints );
			pCurve->attach(this);

			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );

			maker.PlotCurve = pCurve;
			maker.PlotMaker = pMaker;
			m_PlotMarker.append(maker);
		}
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
		{
			tmt_DiffCurrQuickTest* pQuickTest = (tmt_DiffCurrQuickTest*)pHead;

			MakerLine maker;
			maker.m_pCurrThrTest = pQuickTest;

			pCurve = new QwtPlotCurve();
			pCurve->setTitle(/*tr("速断 Ir")*/g_sLangTxt_Native_BreakoffIr);
			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pQuickTest->m_oDiffCurrParas.m_fIbias, pQuickTest->m_oDiffCurrParas.m_fScanTo) 
						<< QPointF( pQuickTest->m_oDiffCurrParas.m_fIbias, pQuickTest->m_oDiffCurrParas.m_fScanFrom);
			pCurve->setSamples( curvePoints );
			pCurve->attach(this);

			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );

			maker.PlotCurve = pCurve;
			maker.PlotMaker = pMaker;
			m_PlotMarker.append(maker);
		}
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
		{
			tmt_DiffCurrHarmTest* pHarmTest = (tmt_DiffCurrHarmTest*)pHead;

			MakerLine maker;
			maker.m_pCurrThrTest = pHarmTest;
/*
			pMaker = new QwtPlotMarker();
			switch(pHarmTest->m_oDiffCurrParas.m_nHarmIndex)
			{
			case 0:
				{
					pMaker->setLabel(tr("2次谐波 Id"));
				}
				break;
			case 1:
				{
					pMaker->setLabel(tr("3次谐波 Id"));
				}
				break;
			case 2:
				{
					pMaker->setLabel(tr("5次谐波 Id"));
				}
				break;
			default:
				break;
			}
			pMaker->setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
			pMaker->setLabelOrientation( Qt::Horizontal );
			pMaker->setLineStyle( QwtPlotMarker::HLine );
			pMaker->setLinePen( Qt::red, 0, Qt::DashDotLine );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush, QPen(Qt::cyan,2), QSize(6, 6) ) );

			pMaker->setValue( QPointF( -1000, -1000 ) );
			pMaker->setYValue( pHarmTest->m_oDiffCurrParas.m_fIdiff ); //差动设定值
			pMaker->attach( this );
*/
			pCurve = new QwtPlotCurve();
			switch(pHarmTest->m_oDiffCurrParas.m_nHarmIndex)
			{
			case 0:
				{
					pCurve->setTitle(/*tr("2次谐波Id")*/g_sLangTxt_Native_HarmCountId2);
				}
				break;
			case 1:
				{
					pCurve->setTitle(/*tr("3次谐波Id")*/g_sLangTxt_Native_HarmCountId3);
				}
				break;
			case 2:
				{
					pCurve->setTitle(/*tr("5次谐波Id")*/g_sLangTxt_Native_HarmCountId5);
				}
			}

			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pHarmTest->m_oDiffCurrParas.m_fScanFrom, pHarmTest->m_oDiffCurrParas.m_fIdiff) 
				<< QPointF( pHarmTest->m_oDiffCurrParas.m_fScanTo, pHarmTest->m_oDiffCurrParas.m_fIdiff);
			pCurve->setSamples( curvePoints );
			pCurve->attach(this);

			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );

			maker.PlotCurve = pCurve;
			maker.PlotMaker = pMaker;
			m_PlotMarker.append(maker);
		}
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
		{
			tmt_DiffActTimeTest* pTimeTest = (tmt_DiffActTimeTest*)pHead;

			MakerLine maker;
			maker.m_pCurrThrTest = pTimeTest;

			pMaker = new QwtPlotMarker();
			pMaker->setLineStyle( QwtPlotMarker::NoLine );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::darkCyan,2), QSize(6, 6) ) );

			pMaker->setXValue(pTimeTest->m_oDiffCurrParas.m_fIbias);
			pMaker->setYValue(pTimeTest->m_oDiffCurrParas.m_fIdiff);

			pMaker->attach( this );

			maker.PlotMaker = pMaker;
			m_PlotMarker.append(maker);
		}
	}

	m_CurPos = new QwtPlotMarker();
	m_CurPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	m_CurPos->setItemAttribute( QwtPlotItem::Legend, true );
	m_CurPos->setSymbol(new QwtSymbol(QwtSymbol::Cross, Qt::NoBrush,  
		QPen(Qt::red,2), QSize(8, 8) ) );
	m_CurPos->setValue( QPointF( 0, 4 ) );
	m_CurPos->attach( this );
}

bool CDifferCharacPlot::eventFilter( QObject *object, QEvent *e )
{
	if (!bstartFlag)
	{
		float fX = this->invTransform(QwtPlot::xBottom,((QMouseEvent*)e)->pos().x());
		float fY = this->invTransform(QwtPlot::yLeft,((QMouseEvent*)e)->pos().y());

		if ( (e->type() == QEvent::MouseMove))
		{	
			MouseMoved(fX,fY);
		}

		if ( (e->type() == QEvent::MouseButtonDblClick))
		{	
			PlotDoubleClicked(fX,fY);	
			return true;
		}

		if ( (e->type() == QEvent::MouseButtonPress))
		{	
			if (((QMouseEvent*)e)->button() == Qt::RightButton)
			{
				PlotRightClicked(fX,fY);
			}
				
			return true;
		}
	}

	return QObject::eventFilter( object, e );
}

void CDifferCharacPlot::clearResultAll()
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker[i].PlotMaker->setYValue(-1000);
	}
	
	replot();
}

void CDifferCharacPlot::clearSymbolPos(tmt_DiffCurrThrTest* pCurrThrTest)
{
	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	if(pMaker)
	{
		pMaker->setYValue(-1000);
	}
}

void CDifferCharacPlot::updateLabelTest(tmt_DiffCurrThrTest* pCurrThrTest)
{
	if (pCurrThrTest == NULL)
	{
		return;
	}

	//取得实时库的6I值
	tmt_RtDataCh rtData;

	float fIh,fIl,fIhe,fIle;
	fIh = pCurrThrTest->m_oDiffCurrResults.m_fI1;
	fIl = pCurrThrTest->m_oDiffCurrResults.m_fI2;
	fIhe = pCurrThrTest->m_oDiffCurrResults.m_fI1Ie;
	fIle = pCurrThrTest->m_oDiffCurrResults.m_fI2Ie;

	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 ||
	   strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0)
	{
		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
		{
			if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 0)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 1)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 2)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
		}
		else
		{
			if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 0)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 1)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 2)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));

				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));

				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0)
	{
		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
		{
			if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 0)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 1)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 2)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
		}
		else
		{
			if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 0)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 1)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 2)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest)==0)
	{
		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0) //有名值
		{
			if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 0)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 1)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 2)
			{
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
		}
		else
		{
			if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 0)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 1)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IM=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IH=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IM=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
			else if (pCurrThrTest->m_oDiffCurrParas.m_nWindSide == 2)
			{
/*标幺值
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1In").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1In").arg(QString::number(fIhe,'f',3))+ "\n" + QString("IL=%1In").arg(QString::number(fIle,'f',3)));
				}
*/
				if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 0)		//A相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 1)  //B相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 2)  //C相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else if (pCurrThrTest->m_oDiffCurrParas.m_nPhase == 3)  //ABC三相
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
				else
				{
					m_PlotLabelText->setText(QString("Ir=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3)) + "\n" + QString("Id=%1A").arg(QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIdiff,'f',3))+ "\n"\
						+ QString("IM=%1A").arg(QString::number(fIh,'f',3))+ "\n" + QString("IL=%1A").arg(QString::number(fIl,'f',3)));
				}
			}
		}
	}
}

QwtPlotMarker* CDifferCharacPlot::getMarkerByTestInfo(tmt_DiffCurrThrTest* pCurrThrTest)
{
	QwtPlotMarker *pCur = NULL;
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		if (m_PlotMarker.at(i).m_pCurrThrTest == pCurrThrTest)
		{
			pCur = m_PlotMarker.at(i).PlotMaker;
			break;
		}
	}

	return pCur;
}

QwtPlotCurve* CDifferCharacPlot::getCurveByTestInfo(tmt_DiffCurrThrTest* pCurrThrTest)
{
	QwtPlotCurve *pCur = NULL;
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		if (m_PlotMarker.at(i).m_pCurrThrTest == pCurrThrTest)
		{
			pCur = m_PlotMarker.at(i).PlotCurve;
			break;
		}
	}

	return pCur;
}

QString CDifferCharacPlot::getValueByMarker(MakerLine info)
{
	tmt_DiffCurrThrTest* pCurrThrTest = info.m_pCurrThrTest;

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 ||
		strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0 ||
		strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0)
	{
		return QString("%1").arg(pCurrThrTest->m_oDiffCurrParas.m_fIbias);		//制动设定值
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest)==0
		|| strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest)==0)
	{
		return QString("%1").arg(pCurrThrTest->m_oDiffCurrParas.m_fIdiff);		//差动设定值
	}

	return "";
}

void CDifferCharacPlot::updatePlot()
{
	initPlot();
	tmt_DiffCurrThrTest* pThrTest = NULL;

	for (int i=0;i<m_PlotMarker.size();i++)
	{
		MakerLine p = m_PlotMarker.at(i);
		pThrTest = p.m_pCurrThrTest;

		if(strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 ||
		   strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0)
		{
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDiffCurrParas.m_fIbias, pThrTest->m_oDiffCurrParas.m_fScanTo ) 
						<< QPointF( pThrTest->m_oDiffCurrParas.m_fIbias, pThrTest->m_oDiffCurrParas.m_fScanFrom );	
			if (m_PlotMarker.at(i).PlotCurve)
			{
				m_PlotMarker.at(i).PlotCurve->setSamples( curvePoints );
			}
		}
		else if (strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0)
		{
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDiffCurrParas.m_fIbias, pThrTest->m_oDiffCurrParas.m_fScanTo ) 
						<< QPointF( pThrTest->m_oDiffCurrParas.m_fIbias, pThrTest->m_oDiffCurrParas.m_fScanFrom );		
			if (m_PlotMarker.at(i).PlotCurve)
			{
				m_PlotMarker.at(i).PlotCurve->setSamples( curvePoints );
			}
		}
		else if (strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest)==0 || strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest)==0)
		{
			QString str = getValueByMarker(p);
			p.PlotMaker->setYValue(str.toFloat());
		}
	}

	replot();
}

void CDifferCharacPlot::updatePlotPos(tmt_DiffCurrThrTest* pCurrThrTest)
{
	if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
	{
		setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
		setAxisTitle( QwtPlot::yLeft, "Id(A)" );
	}
	else
	{
		setAxisTitle( QwtPlot::xBottom, "Ir(In)" );
		setAxisTitle( QwtPlot::yLeft, "Id(In)" );
	}

	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker.at(i).PlotMaker->hide();
		if (m_PlotMarker.at(i).PlotCurve)
		{
			m_PlotMarker.at(i).PlotCurve->hide();
		}
	}

	m_curve->hide();
	d_intervalCurve->hide();

	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	QwtPlotCurve *pCurve = getCurveByTestInfo(pCurrThrTest);
	QString str = g_DifferTestMain->getValueByTestInfo(pCurrThrTest);
	float fValue = str.toFloat();

	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 ||
	   strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0)
	{
		float fe = 5;//getErrorRangeByTestInfo(info); //取得误差范围

		int nCount = m_curvePoints.count();
		QPointF point0 = m_curvePoints[nCount-1];

		if (fValue > m_CurXScale)
		{
			//m_CurXScale = fValue*1.1;
			setAxisScale( QwtPlot::xBottom, 0.0, fValue*1.1 );
			m_curvePoints[nCount-1].setX(fValue*1.1);
		}
		else
		{
			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
			m_curvePoints[nCount-1].setX(m_CurXScale);
		}
		m_curve->setSamples( m_curvePoints );

		updateErrorBars(fe);
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );

		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
		{
			setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
			setAxisTitle( QwtPlot::yLeft, "Id(A)" );
		}
		else
		{
			setAxisTitle( QwtPlot::xBottom, "Ir(In)" );
			setAxisTitle( QwtPlot::yLeft, "Id(In)" );
		}
		m_curve->show();
		d_intervalCurve->show();

		float fd = str.toFloat();
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanTo ) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);	
		if (pCurve)
		{
			pCurve->show();
			pCurve->setSamples( curvePoints );
		}
		
		for (int i=0;i<m_PlotMarker.size();i++)
		{
			switch(pCurrThrTest->m_oDiffCurrParas.m_nKneePoints)
			{
			case 1:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || 
					   strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0 ||
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0) && 
					   (((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1_2 || 
					   ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++) 
						{
							if ((tmt_DiffCurrThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
							{
								if (m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
								{
									m_PlotMarker.at(i).PlotCurve->show();
								}
								else
								{
									m_PlotMarker.at(i).PlotCurve->hide();
									m_PlotMarker.at(i).PlotMaker->hide();
								}
							}
						}
					}
				}
				break;
			case 2:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0  || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 ||
					   strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0 ||
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0) && 
					   (((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1 || 
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DiffCurrThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
							{
								if (m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
								{
									m_PlotMarker.at(i).PlotCurve->show();
								}
								else
								{
									m_PlotMarker.at(i).PlotCurve->hide();
									m_PlotMarker.at(i).PlotMaker->hide();
								}
							}
						}
					}
				}
				break;
			case 3:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || 
					   strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0 ||
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 ||strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0) && (((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1 || 
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD4 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD4_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DiffCurrThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
							{
								if (m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
								{
									m_PlotMarker.at(i).PlotCurve->show();
								}
								else
								{
									m_PlotMarker.at(i).PlotCurve->hide();
									m_PlotMarker.at(i).PlotMaker->hide();
								}
							}
						}
					}

					for (int k=0;k<m_PlotMarker.size();k++)
					{
						if (m_PlotMarker.at(k).PlotCurve)
						{
							if (m_PlotMarker.at(k).PlotCurve->isVisible())
							{
								printf("%d\n",k);
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}

		m_CurPos->setXValue(fd);
		m_CurPos->setYValue(0.05);
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0)
	{
		float fe = 5;//GETINSTANCE->getErrorRangeByTestInfo(info); //误差
		updateErrorBars(fe);
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
		{
			setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
			setAxisTitle( QwtPlot::yLeft, "Id(A)" );
		}
		else
		{
			setAxisTitle( QwtPlot::xBottom, "Ir(In)" );
			setAxisTitle( QwtPlot::yLeft, "Id(In)" );
		}
		m_curve->show();
		d_intervalCurve->show();

		float fd = str.toFloat();
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanTo ) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);	
		if (pCurve)
		{
			pCurve->show();
			pCurve->setSamples( curvePoints );
		}
		
		for (int i=0;i<m_PlotMarker.size();i++)
		{
			switch(pCurrThrTest->m_oDiffCurrParas.m_nKneePoints)
			{
			case 1:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || 
					   strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0 ||
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0) && (((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1 || 
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DiffCurrThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
							{
								if (m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
								{
									m_PlotMarker.at(i).PlotCurve->show();
								}
								else
								{
									m_PlotMarker.at(i).PlotCurve->hide();
									m_PlotMarker.at(i).PlotMaker->hide();
								}
							}
						}
					}
				}
				break;
			case 2:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 ||
						strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0 ||
						(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0) && (((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1 || 
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DiffCurrThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
							{
								if (m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
								{
									m_PlotMarker.at(i).PlotCurve->show();
								}
								else
								{
									m_PlotMarker.at(i).PlotCurve->hide();
									m_PlotMarker.at(i).PlotMaker->hide();
								}
							}
						}
					}
				}
				break;
			case 3:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || 
						strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0 ||
						(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0) && (((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1 || 
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD1_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD2_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD3_2 || ((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD4 ||
						((tmt_DiffCurrRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_ZD4_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DiffCurrThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
							{
								if (m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
								{
									m_PlotMarker.at(i).PlotCurve->show();
								}
								else
								{
									m_PlotMarker.at(i).PlotCurve->hide();
									m_PlotMarker.at(i).PlotMaker->hide();
								}
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}

		m_CurPos->setXValue(fd);
		m_CurPos->setYValue(0.05);
	}
	else if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest)==0)
	{
		float fr = str.toFloat();

		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fScanFrom, pCurrThrTest->m_oDiffCurrParas.m_fIdiff) 
			<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fScanTo, pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
		if (pCurve)
		{
			pCurve->show();
			pCurve->setSamples( curvePoints );
		}
/*
		if (pMaker)
		{
			pMaker->setLabel(stt_get_test_item_name(pCurrThrTest));
			pMaker->show();
			pMaker->setYValue(fr);
		}
*/
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
//		setAxisScale(2,pCurrThrTest->m_oDiffCurrParas.m_fScanFrom/100,pCurrThrTest->m_oDiffCurrParas.m_fScanTo/100);
		setAxisScale(2,pCurrThrTest->m_oDiffCurrParas.m_fScanFrom,pCurrThrTest->m_oDiffCurrParas.m_fScanTo);

		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
		{
			setAxisTitle( QwtPlot::xBottom, "Kr" );
			setAxisTitle( QwtPlot::yLeft, "Id(A)" );
		}
		else
		{
			setAxisTitle( QwtPlot::xBottom, "Kr" );
			setAxisTitle( QwtPlot::yLeft, "Id(In)" );
		}

		if (pMaker)
		{
			pMaker->show();
			double fIrCoef = pCurrThrTest->m_oDiffCurrResults.m_fIrCoef * 100;
			pMaker->setXValue(fIrCoef);
			pMaker->setYValue(pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
		}

		m_CurPos->setXValue(0);
		m_CurPos->setYValue(fr);
	}
	else if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest)==0)
	{
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
		if (pCurrThrTest->m_oDiffCurrParas.m_bMinAxis == 0)
		{
			setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
			setAxisTitle( QwtPlot::yLeft, "Id(A)" );
		}
		else
		{
			setAxisTitle( QwtPlot::xBottom, "Ir(In)" );
			setAxisTitle( QwtPlot::yLeft, "Id(In)" );
		}

		m_curve->show();
		d_intervalCurve->show();

		for (int i=0;i<m_PlotMarker.size();i++)
		{
			if (m_PlotMarker.at(i).m_pCurrThrTest == pCurrThrTest)
			{
				m_PlotMarker[i].PlotMaker->show();
			}
		}
		if (str.contains("~"))
		{
			int pos = str.indexOf("~");
			float fId = str.left(pos).toFloat();
			float fIr = str.mid(pos+1).toFloat();

			if (pMaker)
			{
				pMaker->show();
				pMaker->setXValue(fIr);
				pMaker->setYValue(fId);
			}
			m_CurPos->setXValue(fIr);
			m_CurPos->setYValue(fId);
		}
		else
		{
			if (pMaker)
			{
				pMaker->show();
			}
		}
	}

	m_CurPos->setZ(-10);	
	replot();
}

void CDifferCharacPlot::updateSymbolPos(tmt_DiffCurrThrTest* pCurrThrTest,bool bEnd)
{
	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 ||
	   strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0)
	{
		if (pMaker)
		{
			if (bEnd)
			{
				int v = _finite(pCurrThrTest->m_oDiffCurrResults.m_fIdiffActValue);
				if (v != 0)
				{
					pMaker->show();
					pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias,pCurrThrTest->m_oDiffCurrResults.m_fIdiffActValue);
				}
			}
			else
			{
				int v = _finite(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
				if (v != 0)
				{
					pMaker->show();
					pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias,pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
				}
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0)
	{
		if (bEnd)
		{
			int v = _finite(pCurrThrTest->m_oDiffCurrResults.m_fIdiffActValue);
			if (v != 0)
			{
				pMaker->show();
				pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias,pCurrThrTest->m_oDiffCurrResults.m_fIdiffActValue);
			}
		}
		else
		{
			int v = _finite(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
			if (v != 0)
			{
				pMaker->show();
				pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias,pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest)==0)
	{
		int v = _finite(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
		if (v != 0)
		{
			pMaker->show(); 
			pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest)==0)
	{
		if (pMaker)
		{
			pMaker->show();
			pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias,pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
			QString str = QString("%1").arg(pCurrThrTest->m_oDiffCurrParas.m_fIbias) + QString("   %1").arg(pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
			m_CurPos->setXValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias);
			m_CurPos->setYValue(pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
		}
	}
	
	updateLabelTest(pCurrThrTest);
}

void CDifferCharacPlot::insertErrorBars( const QString &title,const QVector<QwtIntervalSample> &samples,const QColor &color )
{
	if (d_intervalCurve == NULL)
	{
		d_intervalCurve = new QwtPlotIntervalCurve( title );
		d_intervalCurve->setRenderHint( QwtPlotItem::RenderAntialiased );
		d_intervalCurve->setPen( Qt::white );
		QColor bg( color );
		bg.setAlpha( 80 );
		d_intervalCurve->setBrush( QBrush( bg ) );
		d_intervalCurve->setStyle( QwtPlotIntervalCurve::Tube );
	}

	d_intervalCurve->setSamples( samples );
	d_intervalCurve->attach( this );
}

void CDifferCharacPlot::updateErrorBars(float fe)
{
	QVector<QwtIntervalSample> rangeData;
	generateErrorRangeData(m_curvePoints,rangeData,fe);

	d_intervalCurve->setSamples( rangeData );
}

void CDifferCharacPlot::PlotDoubleClicked( float fx,float fy )
{
	emit sig_PlotDoubleClicked(fx,fy);
}

void CDifferCharacPlot::PlotRightClicked(float fx,float fy)
{
	m_popupMenu = new QMenu(this);
	m_addAction = new QAction(/*tr("添加测试点")*/g_sLangTxt_Native_AddTestPoint,this);
	m_addAction->setIcon (QPixmap( "./images/Add.png"));
	m_popupMenu->addAction(m_addAction);
	connect(m_addAction, SIGNAL(triggered()), this, SLOT(slot_AddTestItem()));

	m_fPointX = fx;
	m_fPointY = fy;
	m_popupMenu->exec(QCursor::pos());
}

void CDifferCharacPlot::slot_AddTestItem()
{
	emit sig_PlotRightClicked(m_fPointX,m_fPointY);
}

void CDifferCharacPlot::MouseMoved(float x,float y)
{
	ASSERT(m_pCommonParaTest != NULL);

	QString str1 =  QString::number(x, 'f', 3);
	QString str2 =  QString::number(y, 'f', 3);

	if (m_pCommonParaTest->m_oDiffCurrParas.m_bMinAxis == 0)
	{
		if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 0)
		{
			m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
				+ QString("IH=%1A").arg(0)+ "\n" + QString("IL=%1A").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 1)
		{
			m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
				+ QString("IH=%1A").arg(0)+ "\n" + QString("IM=%1A").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 2)
		{
			m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
				+ QString("IM=%1A").arg(0)+ "\n" + QString("IL=%1A").arg(0));
		}
	}
	else
	{
		if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 0)
		{
			m_PlotLabelText->setText(QString("Ir=%1In").arg(str1) + "\n" + QString("Id=%1In").arg(str2)+ "\n"\
				+ QString("IH=%1In").arg(0)+ "\n" + QString("IL=%1In").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 1)
		{
			m_PlotLabelText->setText(QString("Ir=%1In").arg(str1) + "\n" + QString("Id=%1In").arg(str2)+ "\n"\
				+ QString("IH=%1In").arg(0)+ "\n" + QString("IM=%1In").arg(0));
		}
		else if (m_pCommonParaTest->m_oDiffCurrParas.m_nWindSide == 2)
		{
			m_PlotLabelText->setText(QString("Ir=%1In").arg(str1) + "\n" + QString("Id=%1In").arg(str2)+ "\n"\
				+ QString("IM=%1In").arg(0)+ "\n" + QString("IL=%1In").arg(0));
		}
	}
}

void CDifferCharacPlot::generateErrorRangeData( QVector<QPointF> &points,QVector<QwtIntervalSample> &rangeData,float fe )
{
	for (int i=0;i<points.size();i++)
	{
		QPointF p = points.at(i);
		rangeData.append( QwtIntervalSample( double( p.x() ),QwtInterval( p.y()*(1+fe/100), p.y()*(1-fe/100) ) ));
	}
}

void CDifferCharacPlot::slot_AddOneTest( tmt_DiffCurrThrTest* pCurrThrTest )
{
	ASSERT(pCurrThrTest != NULL);

	MakerLine maker;
	maker.m_pCurrThrTest = pCurrThrTest;
	
	QwtPlotCurve *pCurve = NULL;
	QwtPlotMarker *pMaker = NULL;

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
	{
		pCurve = new QwtPlotCurve();
		if (((tmt_DiffCurrThrTest*)pCurrThrTest)->m_nThrType == TEST_QD) //0-启动电流；1-动作特性曲线
		{
			pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
		}
		else
		{
			QString str1 = QString::number(pCurrThrTest->m_oDiffCurrParas.m_fIbias,'f',3);	
			QString strTitle;
			strTitle = /*tr("动作特性曲线 ")*/g_sLangTxt_Native_CharactCurve+"Ir="+str1+"*"+"A";

			pCurve->setTitle(strTitle);
		}

		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

		QVector<QPointF> curvePoints;
//		curvePoints << QPointF( data.fIr, data.fUp) << QPointF( data.fIr, data.fDown);
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanTo) 
			        << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);
		pCurve->setSamples( curvePoints );
		pCurve->attach(this);

		pMaker = new QwtPlotMarker();
		pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pMaker->setItemAttribute( QwtPlotItem::Legend, true );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
			QPen(Qt::cyan,2), QSize(6, 6) ) );
		pMaker->setValue(QPointF( -1000, -1000 )  );
		pMaker->attach( this );

		maker.PlotCurve = pCurve;
		maker.PlotMaker = pMaker;
		m_PlotMarker.append(maker);
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
	{
		tmt_DiffCurrRateTest* pRateTest = (tmt_DiffCurrRateTest*)pCurrThrTest;

		pCurve = new QwtPlotCurve();
		if(pRateTest->m_nRateType == TEST_ZD1 || pRateTest->m_nRateType == TEST_ZD1_2)
		{
			pCurve->setTitle(tr("ZD1 Ir"));
		}
		else if (pRateTest->m_nRateType == TEST_ZD2 || pRateTest->m_nRateType == TEST_ZD2_2)
		{
			pCurve->setTitle(tr("ZD2 Ir"));
		}
		else if (pRateTest->m_nRateType == TEST_ZD3 || pRateTest->m_nRateType == TEST_ZD3_2)
		{
			pCurve->setTitle(tr("ZD3 Ir"));
		}
		else if (pRateTest->m_nRateType == TEST_ZD4 || pRateTest->m_nRateType == TEST_ZD4_2)
		{
			pCurve->setTitle(tr("ZD4 Ir"));
		}

		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanTo) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);
		pCurve->setSamples( curvePoints );
		pCurve->attach(this);

		pMaker = new QwtPlotMarker();
		pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pMaker->setItemAttribute( QwtPlotItem::Legend, true );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
			QPen(Qt::cyan,2), QSize(6, 6) ) );
		pMaker->setValue(QPointF( -1000, -1000 )  );
		pMaker->attach( this );

		maker.PlotCurve = pCurve;
		maker.PlotMaker = pMaker;
		m_PlotMarker.append(maker);
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
	{
		pCurve = new QwtPlotCurve();
		pCurve->setTitle(/*tr("速断 Ir")*/g_sLangTxt_Native_BreakoffIr);
		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanTo) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);
		pCurve->setSamples( curvePoints );
		pCurve->attach(this);

		pMaker = new QwtPlotMarker();
		pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pMaker->setItemAttribute( QwtPlotItem::Legend, true );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
			QPen(Qt::cyan,2), QSize(6, 6) ) );
		pMaker->setValue(QPointF( -1000, -1000 )  );
		pMaker->attach( this );

		maker.PlotCurve = pCurve;
		maker.PlotMaker = pMaker;
		m_PlotMarker.append(maker);
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
	{
		pMaker = new QwtPlotMarker();
		pCurve = new QwtPlotCurve();

		switch(pCurrThrTest->m_oDiffCurrParas.m_nHarmIndex)
		{
		case 0:
			{
				pMaker->setLabel(/*tr("2次谐波 Id")*/g_sLangTxt_Native_HarmCountId2);
			}
			break;
		case 1:
			{
				pMaker->setLabel(/*tr("3次谐波 Id")*/g_sLangTxt_Native_HarmCountId3);
			}
			break;
		case 2:
			{
				pMaker->setLabel(/*tr("5次谐波 Id")*/g_sLangTxt_Native_HarmCountId5);
			}
			break;
		default:
			break;
		}

		pMaker->setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
		pMaker->setLabelOrientation( Qt::Horizontal );
		pMaker->setLineStyle( QwtPlotMarker::HLine );
		pMaker->setLinePen( Qt::red, 0, Qt::DashDotLine );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush, QPen(Qt::cyan,2), QSize(6, 6) ) );

		pMaker->setValue( QPointF( -1000, -1000 ) );
		pMaker->setYValue( pCurrThrTest->m_oDiffCurrParas.m_fIdiff );
		pMaker->attach( this );

		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fScanFrom, pCurrThrTest->m_oDiffCurrParas.m_fIdiff) 
			<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fScanTo, pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
	
		pCurve->setSamples( curvePoints );
		pCurve->attach(this);

		maker.PlotCurve = pCurve;
		maker.PlotMaker = pMaker;
		m_PlotMarker.append(maker);
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
	{
		pMaker = new QwtPlotMarker();
		pMaker->setLineStyle( QwtPlotMarker::NoLine );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::darkCyan,2), QSize(6, 6) ) );

		pMaker->setXValue(pCurrThrTest->m_oDiffCurrParas.m_fIbias);
		pMaker->setYValue(pCurrThrTest->m_oDiffCurrParas.m_fIdiff);

		pMaker->attach( this );

		maker.PlotMaker = pMaker;
		m_PlotMarker.append(maker);
	}

	m_CurPos->attach(this);

	updatePlotPos(pCurrThrTest);
}

void CDifferCharacPlot::slot_DelOneTest(tmt_DiffCurrThrTest* pCurrThrTest)
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		MakerLine pMakerLine = m_PlotMarker.at(i);
		if (pMakerLine.m_pCurrThrTest == pCurrThrTest)
		{
			delete m_PlotMarker.at(i).PlotMaker;
			delete m_PlotMarker.at(i).PlotCurve;
			m_PlotMarker[i].PlotMaker = NULL;
			m_PlotMarker[i].PlotCurve = NULL;
			m_PlotMarker.removeAt(i);
		}
	}

	replot();
}

void CDifferCharacPlot::slot_DelAllTest(tmt_DiffCurrThrTest* pCurrThrTest)
{
	creatMaker();
	updatePlot();
	updatePlotPos(pCurrThrTest);
	replot();
}

void CDifferCharacPlot::setValueByInfo(tmt_DiffCurrThrTest* pCurrThrTest, float fx, float fy)
{
	float fUp=0;
	float fDown=0;
	g_DifferTestMain->calcuRangeByInfoAndX(fx,fUp,fDown);

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest)==0 ||
		strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest)==0 ||
		strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest)==0)
	{
		pCurrThrTest->m_oDiffCurrParas.m_fIbias = fx;
		pCurrThrTest->m_oDiffCurrParas.m_fScanFrom = fDown;
		pCurrThrTest->m_oDiffCurrParas.m_fScanTo = fUp;
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest)==0)
	{
		pCurrThrTest->m_oDiffCurrParas.m_fIdiff = fy;
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest)==0)
	{
		pCurrThrTest->m_oDiffCurrParas.m_fIbias = fx;
		pCurrThrTest->m_oDiffCurrParas.m_fIdiff = fy;
	}
}
// 2022.5.13 caoxc
float CDifferCharacPlot::calcId(float fIr)
{
	float fId = 0.0;
	int nCount = m_curvePoints.count();
	for(int i=0;i<nCount-1;i++)
	{
		QPointF point0 = m_curvePoints[i];
		QPointF point1 = m_curvePoints[i+1];
		if(fIr<point1.x())
		{
			fId = point0.y() + (fIr-point0.x())*(point1.y()-point0.y())/(point1.x()-point0.x());
			break;
		}
	}
	return fId;
}

//void CDifferCharacPlot::SavePng(CString strPath)
//{
//	QPixmap pix = QPixmap::grabWidget(this); 
//	//QPixmap pixmap (700,500); 
//	QPixmap pixmap (this->width(), this->height()); 
//	QPainter * painter=new QPainter(&pixmap); 
//
//	QwtPlotRenderer rend; 
//
//	rend.render(this,painter,this->geometry()); 
//	QPixmap Pmap = pixmap.scaled(500,500,Qt::KeepAspectRatio);
//	Pmap.save(strPath);  
//}

QPixmap CDifferCharacPlot::SavePng()
{
	QPixmap pix = QPixmap::grabWidget(this); 
	//QPixmap pixmap (700,500); 
	QPixmap pixmap (this->width(), this->height()); 
	QPainter * painter = new QPainter(&pixmap); 

	QwtPlotRenderer rend; 

	rend.render(this, painter, this->geometry()); 
	QPixmap Pmap = pixmap.scaled(500,500,Qt::KeepAspectRatio,Qt::SmoothTransformation);
	return Pmap;
}

void CDifferCharacPlot::GetSearchingPng(CString& strBase64)
{
	QByteArray ba;
	QBuffer* buffer = new QBuffer(&ba);
	buffer->open(QIODevice::WriteOnly);
	long nCurrWidth = this->width();
	long nCurrHeight = this->height();
	resize(600,600);
	QPixmap pixmap (this->width(), this->height()); 
	QPainter * painter = new QPainter(&pixmap); 
	QwtPlotRenderer rend; 
	rend.render(this, painter, this->geometry()); 
	QPixmap Pmap = pixmap.scaled(this->width(), this->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
	QImage image = Pmap.toImage();
	image.save(buffer, "png", -1);
	QString strPngBase64 = ba.toBase64();
	strBase64 = strPngBase64;
	resize(nCurrWidth,nCurrHeight);

	delete painter;
	delete buffer;
}