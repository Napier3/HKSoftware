#include <float.h>
#include "DCDifferCharacPlot.h"
#include <QDir>
#include <QMessageBox>
#include <QFont>
#include <QFontMetrics>
#include "../../Module/SttTest/Common/tmt_rtdata_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "../../../DCDifferTest/dcdiffertest.h"

#if QT_VERSION < 0x040601
#define qExp(x) ::exp(x)
#define qAtan2(y, x) ::atan2(y, x)
#endif

#define RADIO 1.5
DCDifferCharacPlot::DCDifferCharacPlot( QWidget *parent ):
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

void DCDifferCharacPlot::setData(TMT_PARAS_MNGR* pTmtTestMngr)
{
	ASSERT(pTmtTestMngr);
	m_pTmtTestMngr = pTmtTestMngr;

	m_pCommonParaTest = (tmt_DcDifferCurTest*)pTmtTestMngr->m_pParasBuffer[0];

	initPlot();
	creatMaker();
}

void DCDifferCharacPlot::init()
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
	m_PlotLabelText->setGeometry(20,5,nLabelWidth,nHeight);//标签显示位置

	m_curve = new QwtPlotCurve();
	m_curve->setTitle( "Some Points" );
	m_curve->setPen( Qt::blue, 2 );
	m_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

	QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 2, 2 ) );
	m_curve->setSymbol( symbol );
	m_curve->attach( this );
}

void DCDifferCharacPlot::initPlot()
{
	ASSERT(m_pCommonParaTest != NULL);
	if (m_pCommonParaTest == NULL)
	{
		return;
	}

	QString str1 =  QString::number(2, 'f', 3);
	QString str2 =  QString::number(2, 'f', 3);
	float fx, fy;
	
	m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
		+ QString("IH=%1A").arg(0)+ "\n" + QString("IL=%1A").arg(0));
		
	fx = g_DCDifferTestMain->getMaxIrByAllTestItem(fx);
	fy = g_DCDifferTestMain->getMaxFromByAllTestItem(fy);

	if (fx < 6)
	{
		fx = 6;
	}

	if (fy < 6)
	{
		fy = 6;
	}
	setAxisScale( QwtPlot::yLeft, 0.0,  fy* RADIO );
	m_CurYScale = fy * RADIO;
	m_curvePoints.clear();
	QVector<QwtIntervalSample> rangeData;
	
	switch(m_pCommonParaTest->m_oDcDifferCurParas.m_nKneePoints)
	{
	case 1:
		{
			m_pCommonParaTest->m_oDcDifferCurParas.m_fKid0 = 0;
			float y1 = m_pCommonParaTest->m_oDcDifferCurParas.m_fIp1 * m_pCommonParaTest->m_oDcDifferCurParas.m_fKid0 + m_pCommonParaTest->m_oDcDifferCurParas.m_fIStart;
			float xIsd = m_pCommonParaTest->m_oDcDifferCurParas.m_fIp1 + (100 - y1) / m_pCommonParaTest->m_oDcDifferCurParas.m_fKRation1;
			m_CurXScale = fx * RADIO;
			m_curvePoints << QPointF( 0.0, m_pCommonParaTest->m_oDcDifferCurParas.m_fIStart ) << QPointF( m_pCommonParaTest->m_oDcDifferCurParas.m_fIp1, y1 )
				<< QPointF(xIsd, 100) << QPointF(m_CurXScale, 100);

			generateErrorRangeData(m_curvePoints,rangeData,5); //5可取系统参数中的相对误差值
			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale);
		}
		break;
	case 2:
		{
			float y1 = m_pCommonParaTest->m_oDcDifferCurParas.m_fIp1 * m_pCommonParaTest->m_oDcDifferCurParas.m_fKid0 + m_pCommonParaTest->m_oDcDifferCurParas.m_fIStart;
			float y2 = y1 + (m_pCommonParaTest->m_oDcDifferCurParas.m_fIp2-m_pCommonParaTest->m_oDcDifferCurParas.m_fIp1)*m_pCommonParaTest->m_oDcDifferCurParas.m_fKRation1; //拐点2的Y坐标
			float xIsd = (100 - y2)/m_pCommonParaTest->m_oDcDifferCurParas.m_fKRation2+m_pCommonParaTest->m_oDcDifferCurParas.m_fIp2;
			m_CurXScale = fx * RADIO;
			m_curvePoints << QPointF( 0.0, m_pCommonParaTest->m_oDcDifferCurParas.m_fIStart ) << QPointF( m_pCommonParaTest->m_oDcDifferCurParas.m_fIp1, y1 )\
				<< QPointF( m_pCommonParaTest->m_oDcDifferCurParas.m_fIp2, y2 )<< QPointF(xIsd, 100)\
				<<QPointF(m_CurXScale, 100);

			generateErrorRangeData(m_curvePoints,rangeData,5);
			setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );
		}
		break;

	default:
		break;
	}

	m_curve->setSamples( m_curvePoints );

	insertErrorBars( "Range", rangeData, Qt::blue );
}

void DCDifferCharacPlot::creatMaker()
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
		if(strcmp(pHead->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest) == 0)
		{
			tmt_DcDifferCurTest* pThrTest = (tmt_DcDifferCurTest*)pHead;

			DCMakerLine maker;
			maker.m_pCurrThrTest = pThrTest;

			pCurve = new QwtPlotCurve();
			if (pThrTest->m_nThrType == TEST_DIFF_QD) //启动电流
			{
				pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
			}
			else	//动作特性曲线
			{
				QString str1 = QString::number(pThrTest->m_oDcDifferCurParas.m_fIbias,'f',3);	
				QString strTitle;
				strTitle = /*tr("动作特性曲线 ")*/g_sLangTxt_Native_CharactCurve+"Ir="+str1+"*"+"A";

				pCurve->setTitle(strTitle);
			}
			pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDcDifferCurParas.m_fIbias, pThrTest->m_oDcDifferCurParas.m_fScanTo) 
						<< QPointF( pThrTest->m_oDcDifferCurParas.m_fIbias, pThrTest->m_oDcDifferCurParas.m_fScanFrom);
			pCurve->setSamples( curvePoints );
			pCurve->attach(this);

			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );//设置曲线渲染模式
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );//显示图例
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );

			maker.PlotCurve = pCurve;
			maker.PlotMaker = pMaker;
			m_PlotMarker.append(maker);
		}
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest) == 0)
		{
			tmt_DcDifferCurRateTest* pRateTest = (tmt_DcDifferCurRateTest*)pHead;

			DCMakerLine maker;
			maker.m_pCurrThrTest = pRateTest;

			pCurve = new QwtPlotCurve();
			if(pRateTest->m_nRateType == TEST_DIFF_ZD2 || pRateTest->m_nRateType == TEST_DIFF_ZD2_2)
			{
				pCurve->setTitle(tr("ZD2 Ir"));
			}
		
			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pRateTest->m_oDcDifferCurParas.m_fIbias, pRateTest->m_oDcDifferCurParas.m_fScanTo) 
						<< QPointF( pRateTest->m_oDcDifferCurParas.m_fIbias, pRateTest->m_oDcDifferCurParas.m_fScanFrom);
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
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_DCDifferTimeTest) == 0)
		{
			tmt_DcDifferActTimeTest* pTimeTest = (tmt_DcDifferActTimeTest*)pHead;

			DCMakerLine maker;
			maker.m_pCurrThrTest = pTimeTest;

			pMaker = new QwtPlotMarker();
			pMaker->setLineStyle( QwtPlotMarker::NoLine );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::darkCyan,2), QSize(6, 6) ) );

			pMaker->setXValue(pTimeTest->m_oDcDifferCurParas.m_fIbias);
			pMaker->setYValue(pTimeTest->m_oDcDifferCurParas.m_fIdiff);

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

bool DCDifferCharacPlot::eventFilter( QObject *object, QEvent *e )
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

void DCDifferCharacPlot::clearResultAll()
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker[i].PlotMaker->setYValue(-1000);
	}
	
	replot();
}

void DCDifferCharacPlot::clearSymbolPos(tmt_DcDifferCurTest* pCurrThrTest)
{
	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	if(pMaker)
	{
		pMaker->setYValue(-1000);
	}
}

void DCDifferCharacPlot::updateLabelTest(tmt_DcDifferCurTest* pCurrThrTest)
{

}

QwtPlotMarker* DCDifferCharacPlot::getMarkerByTestInfo(tmt_DcDifferCurTest* pCurrThrTest)
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

QwtPlotCurve* DCDifferCharacPlot::getCurveByTestInfo(tmt_DcDifferCurTest* pCurrThrTest)
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

QString DCDifferCharacPlot::getValueByMarker(DCMakerLine info)
{
	tmt_DcDifferCurTest* pCurrThrTest = info.m_pCurrThrTest;

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest) == 0 ||
		strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest) == 0)
	{
		return QString("%1").arg(pCurrThrTest->m_oDcDifferCurParas.m_fIbias);		//制动设定值
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferTimeTest) == 0)
	{
		return QString("%1").arg(pCurrThrTest->m_oDcDifferCurParas.m_fIdiff);		//差动设定值
	}

	return "";
}

void DCDifferCharacPlot::updatePlot()
{
	initPlot();
	tmt_DcDifferCurTest* pThrTest = NULL;

	for (int i=0;i<m_PlotMarker.size();i++)
	{
		DCMakerLine p = m_PlotMarker.at(i);
		pThrTest = p.m_pCurrThrTest;

		if(strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest) == 0)
		{
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDcDifferCurParas.m_fIbias, pThrTest->m_oDcDifferCurParas.m_fScanTo ) 
						<< QPointF( pThrTest->m_oDcDifferCurParas.m_fIbias, pThrTest->m_oDcDifferCurParas.m_fScanFrom );	
			if (m_PlotMarker.at(i).PlotCurve)
			{
				m_PlotMarker.at(i).PlotCurve->setSamples( curvePoints );
			}
		}
		else if (strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest) == 0)
		{
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDcDifferCurParas.m_fIbias, pThrTest->m_oDcDifferCurParas.m_fScanTo ) 
						<< QPointF( pThrTest->m_oDcDifferCurParas.m_fIbias, pThrTest->m_oDcDifferCurParas.m_fScanFrom );		
			if (m_PlotMarker.at(i).PlotCurve)
			{
				m_PlotMarker.at(i).PlotCurve->setSamples( curvePoints );
			}
		}
	}

	replot();
}

void DCDifferCharacPlot::updatePlotPos(tmt_DcDifferCurTest* pCurrThrTest)
{

	setAxisTitle( QwtPlot::xBottom, "Ir(In)" );
	setAxisTitle( QwtPlot::yLeft, "Id(In)" );

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
	QString str = g_DCDifferTestMain->getValueByTestInfo(pCurrThrTest);

	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest) == 0)
	{
		float fe = 5;//getErrorRangeByTestInfo(info); //取得误差范围
		updateErrorBars(fe);
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );

		setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
		setAxisTitle( QwtPlot::yLeft, "Id(A)" );

		m_curve->show();
		d_intervalCurve->show();

		float fd = str.toFloat();
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanTo ) 
					<< QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanFrom);	
		if (pCurve)
		{
			pCurve->show();
			pCurve->setSamples( curvePoints );
		}
		
		for (int i=0;i<m_PlotMarker.size();i++)
		{
			switch(pCurrThrTest->m_oDcDifferCurParas.m_nKneePoints)
			{
			case 1:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest)==0 || 
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest)==0) && 
					   (((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2 || 
					   ((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2_2 ))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++) 
						{
							if ((tmt_DcDifferCurTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
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
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest)==0 ||
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest)==0 ) && 
					   (((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2 ||
						((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2_2 ||
						((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD3 ||
						((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD3_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DcDifferCurTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
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
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest)==0)
	{
		float fe = 5;//GETINSTANCE->getErrorRangeByTestInfo(info); //误差
		updateErrorBars(fe);
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );

		setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
		setAxisTitle( QwtPlot::yLeft, "Id(A)" );
		m_curve->show();
		d_intervalCurve->show();

		float fd = str.toFloat();
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanTo ) 
					<< QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanFrom);	
		if (pCurve)
		{
			pCurve->show();
			pCurve->setSamples( curvePoints );
		}
		
		for (int i=0;i<m_PlotMarker.size();i++)
		{
			switch(pCurrThrTest->m_oDcDifferCurParas.m_nKneePoints)
			{
			case 1:
				{
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest)==0  || 
					   (strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest)==0 ) && 
					   (((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2 || 
					   ((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DcDifferCurTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
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
					if(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest)==0 ||
						(strcmp(m_PlotMarker.at(i).m_pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest)==0 ) && 
						(((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2 || 
						((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD2_2 ||
						((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD3 ||
						((tmt_DcDifferCurRateTest*)m_PlotMarker.at(i).m_pCurrThrTest)->m_nRateType == TEST_DIFF_ZD3_2))
					{
						m_PlotMarker.at(i).PlotMaker->show();

						for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
						{
							if ((tmt_DcDifferCurTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).m_pCurrThrTest)
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
	else if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferTimeTest)==0)
	{
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );

		setAxisTitle( QwtPlot::xBottom, "Ir(A)" );
		setAxisTitle( QwtPlot::yLeft, "Id(A)" );

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

void DCDifferCharacPlot::updateSymbolPos(tmt_DcDifferCurTest* pCurrThrTest,bool bEnd)
{
	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest) == 0)
	{
		if (pMaker)
		{
			if (bEnd)
			{
				int v = _finite(pCurrThrTest->m_oDcDifferCurResults.m_fIdiffActValue);
				if (v != 0)
				{
					pMaker->show();
					pMaker->setValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias,pCurrThrTest->m_oDcDifferCurResults.m_fIdiffActValue);
				}
			}
			else
			{
				int v = _finite(pCurrThrTest->m_oDcDifferCurParas.m_fCurrScanVal);
				if (v != 0)
				{
					pMaker->show();
					pMaker->setValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias,pCurrThrTest->m_oDcDifferCurParas.m_fCurrScanVal);
				}
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest) == 0)
	{
		if (bEnd)
		{
			int v = _finite(pCurrThrTest->m_oDcDifferCurResults.m_fIdiffActValue);
			if (v != 0)
			{
				pMaker->show();
				pMaker->setValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias,pCurrThrTest->m_oDcDifferCurResults.m_fIdiffActValue);
			}
		}
		else
		{
			int v = _finite(pCurrThrTest->m_oDcDifferCurParas.m_fCurrScanVal);
			if (v != 0)
			{
				pMaker->show();
				pMaker->setValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias,pCurrThrTest->m_oDcDifferCurParas.m_fCurrScanVal);
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferTimeTest) == 0)
	{
		if (pMaker)
		{
			pMaker->show();
			pMaker->setValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias,pCurrThrTest->m_oDcDifferCurParas.m_fIdiff);
			QString str = QString("%1").arg(pCurrThrTest->m_oDcDifferCurParas.m_fIbias) + QString("   %1").arg(pCurrThrTest->m_oDcDifferCurParas.m_fIdiff);
			m_CurPos->setXValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias);
			m_CurPos->setYValue(pCurrThrTest->m_oDcDifferCurParas.m_fIdiff);
		}
	}
	
	updateLabelTest(pCurrThrTest);
}

void DCDifferCharacPlot::insertErrorBars( const QString &title,const QVector<QwtIntervalSample> &samples,const QColor &color )
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

void DCDifferCharacPlot::updateErrorBars(float fe)
{
	QVector<QwtIntervalSample> rangeData;
	generateErrorRangeData(m_curvePoints,rangeData,fe);

	d_intervalCurve->setSamples( rangeData );
}

void DCDifferCharacPlot::PlotDoubleClicked( float fx,float fy )
{
	emit sig_PlotDoubleClicked(fx,fy);
}

void DCDifferCharacPlot::PlotRightClicked(float fx,float fy)
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

void DCDifferCharacPlot::slot_AddTestItem()
{
	emit sig_PlotRightClicked(m_fPointX,m_fPointY);
}

void DCDifferCharacPlot::MouseMoved(float x,float y)
{
	ASSERT(m_pCommonParaTest != NULL);

	QString str1 =  QString::number(x, 'f', 3);
	QString str2 =  QString::number(y, 'f', 3);

	m_PlotLabelText->setText(QString("Ir=%1A").arg(str1) + "\n" + QString("Id=%1A").arg(str2)+ "\n"\
		+ QString("IH=%1A").arg(0)+ "\n" + QString("IL=%1A").arg(0));
}

void DCDifferCharacPlot::generateErrorRangeData( QVector<QPointF> &points,QVector<QwtIntervalSample> &rangeData,float fe )
{
	for (int i=0;i<points.size();i++)
	{
		QPointF p = points.at(i);
		rangeData.append( QwtIntervalSample( double( p.x() ),QwtInterval( p.y()*(1+fe/100), p.y()*(1-fe/100) ) ));
	}
}

void DCDifferCharacPlot::slot_AddOneTest( tmt_DcDifferCurTest* pCurrThrTest )
{
	ASSERT(pCurrThrTest != NULL);

	DCMakerLine maker;
	maker.m_pCurrThrTest = pCurrThrTest;
	
	QwtPlotCurve *pCurve = NULL;
	QwtPlotMarker *pMaker = NULL;

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest) == 0)
	{
		pCurve = new QwtPlotCurve();
		if (((tmt_DcDifferCurTest*)pCurrThrTest)->m_nThrType == TEST_DIFF_QD) //0-启动电流；1-动作特性曲线
		{
			pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
		}
		else
		{
			QString str1 = QString::number(pCurrThrTest->m_oDcDifferCurParas.m_fIbias,'f',3);	
			QString strTitle;
			strTitle = /*tr("动作特性曲线 ")*/g_sLangTxt_Native_CharactCurve+"Ir="+str1+"*"+"A";

			pCurve->setTitle(strTitle);
		}

		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanTo) 
			        << QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanFrom);
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
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest) == 0)
	{
		tmt_DcDifferCurRateTest* pRateTest = (tmt_DcDifferCurRateTest*)pCurrThrTest;

		pCurve = new QwtPlotCurve();
		if (pRateTest->m_nRateType == TEST_DIFF_ZD2 || pRateTest->m_nRateType == TEST_DIFF_ZD2_2)
		{
			pCurve->setTitle(tr("ZD2 Ir"));
		}
		else if (pRateTest->m_nRateType == TEST_DIFF_ZD3 || pRateTest->m_nRateType == TEST_DIFF_ZD3_2)
		{
			pCurve->setTitle(tr("ZD3 Ir"));
		}

		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanTo) 
					<< QPointF( pCurrThrTest->m_oDcDifferCurParas.m_fIbias, pCurrThrTest->m_oDcDifferCurParas.m_fScanFrom);
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
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferTimeTest) == 0)
	{
		pMaker = new QwtPlotMarker();
		pMaker->setLineStyle( QwtPlotMarker::NoLine );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::darkCyan,2), QSize(6, 6) ) );

		pMaker->setXValue(pCurrThrTest->m_oDcDifferCurParas.m_fIbias);
		pMaker->setYValue(pCurrThrTest->m_oDcDifferCurParas.m_fIdiff);

		pMaker->attach( this );

		maker.PlotMaker = pMaker;
		m_PlotMarker.append(maker);
	}

	m_CurPos->attach(this);

	updatePlotPos(pCurrThrTest);
}

void DCDifferCharacPlot::slot_DelOneTest(tmt_DcDifferCurTest* pCurrThrTest)
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		DCMakerLine pMakerLine = m_PlotMarker.at(i);
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

void DCDifferCharacPlot::slot_DelAllTest(tmt_DcDifferCurTest* pCurrThrTest)
{
	creatMaker();
	updatePlot();
	updatePlotPos(pCurrThrTest);
	replot();
}

void DCDifferCharacPlot::setValueByInfo(tmt_DcDifferCurTest* pCurrThrTest, float fx, float fy)
{
	float fUp = 0;
	float fDown = 0;
	g_DCDifferTestMain->calcuRangeByInfoAndX(fx, fUp, fDown);

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferCurrTest)==0 ||
		strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferRateTest)==0)
	{
		pCurrThrTest->m_oDcDifferCurParas.m_fIbias = fx;
		pCurrThrTest->m_oDcDifferCurParas.m_fScanFrom = fDown;
		pCurrThrTest->m_oDcDifferCurParas.m_fScanTo = fUp;
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_DCDifferTimeTest)==0)
	{
		pCurrThrTest->m_oDcDifferCurParas.m_fIbias = fx;
		pCurrThrTest->m_oDcDifferCurParas.m_fIdiff = fy;
	}
}
// 2022.5.13 caoxc
float DCDifferCharacPlot::calcId(float fIr)
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

//void DCDifferCharacPlot::SavePng(CString strPath)
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

QPixmap DCDifferCharacPlot::SavePng()
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

void DCDifferCharacPlot::GetSearchingPng(CString& strBase64)
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