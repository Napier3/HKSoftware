#include <float.h>
#include "BPDifferCharacPlot.h"
#include <QDir>
#include <QMessageBox>
#include <QFont>
#include <QFontMetrics>
#include "../../Module/SttTest/Common/tmt_rtdata_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "../../../BPDifferTest/BPDifferTest.h"

#if QT_VERSION < 0x040601
#define qExp(x) ::exp(x)
#define qAtan2(y, x) ::atan2(y, x)
#endif

#define RADIO 1.5
CBPDifferCharacPlot::CBPDifferCharacPlot( QWidget *parent ):
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

void CBPDifferCharacPlot::setData(TMT_PARAS_MNGR* pTmtTestMngr)
{
	ASSERT(pTmtTestMngr);
	m_pTmtTestMngr = pTmtTestMngr;

	m_pCommonParaTest = (tmt_BP2DiffThrTest*)pTmtTestMngr->m_pParasBuffer[0];

	initPlot();
	creatMaker();
}

void CBPDifferCharacPlot::init()
{
	bstartFlag = false;
	d_intervalCurve =  NULL;
	m_CurPos = NULL;

	setTitle(/*tr("特征曲线图")*/g_sLangTxt_Native_CurveGraph);
	setCanvasBackground( Qt::white );

	setAxisTitle( QwtPlot::xBottom, "Ir-Id(A)" );
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

	canvas = new QwtPlotCanvas();
	setCanvas( canvas );

	d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		canvas/*this->canvas()*/ );
	d_picker->setStateMachine( new QwtPickerDragPointMachine() );
	d_picker->setRubberBandPen( QColor( Qt::green ) );
	d_picker->setRubberBand( QwtPicker::CrossRubberBand );
	d_picker->setTrackerPen( QColor( Qt::black ) );

	QString str1 =  QString::number(2, 'f', 3);
	QString str2 =  QString::number(2, 'f', 3);

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nHeight = fontMetrics.height()*4;
	int nLabelWidth = fontMetrics.width(tr("IR=00.000A")) + 15;
	m_PlotLabelText = new QLabel(canvas);
	
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

void CBPDifferCharacPlot::initPlot()
{
	ASSERT(m_pCommonParaTest != NULL);
	if (m_pCommonParaTest == NULL)
	{
		return;
	}

	QString str1 =  QString::number(2, 'f', 3);
	QString str2 =  QString::number(2, 'f', 3);

	CString str;
	CString strTmp;
	strTmp.Format(_T("Ir-Id=%.3fA\n"),str1.toFloat());
	str += strTmp;
	strTmp.Format(_T("Id=%.3fA\n"),str2.toFloat());
	str += strTmp;
	m_PlotLabelText->setText(str.GetString());

	float fKid;
	if (m_pCommonParaTest->m_oDiffCurrParas.m_nKAType == 1)
	{
		fKid = m_pCommonParaTest->m_oDiffCurrParas.m_fCompoundKh;
	}
	else
	{
		fKid = m_pCommonParaTest->m_oDiffCurrParas.m_fCompoundKl;
	}

	//启动段斜率=0、拐点数固定=1
	float y1 = m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd;
	float x1 = m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd/fKid;
	float x2 = x1*XRADIO;
	float y2 = y1 + (x2-x1)*fKid;

	m_CurYScale = y2*YRADIO;
	setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );

	m_CurXScale = x2;
	setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );

	m_curvePoints.clear();
	QVector<QwtIntervalSample> rangeData;

	m_curvePoints << QPointF( 0.0, m_pCommonParaTest->m_oDiffCurrParas.m_fIcdqd ) << QPointF( x1, y1 )\
				  << QPointF( x2, y2 );

	generateErrorRangeData(m_curvePoints,rangeData,4);
	m_curve->setSamples( m_curvePoints );

	insertErrorBars( "Range", rangeData, Qt::blue );
}

void CBPDifferCharacPlot::creatMaker()
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker[i].PlotMaker->hide();
		delete m_PlotMarker[i].PlotMaker;
		m_PlotMarker[i].PlotMaker = NULL;

		delete m_PlotMarker[i].PlotCurve;
		m_PlotMarker[i].PlotCurve = NULL;

		if (m_PlotMarker[i].PlotMakerEx)
		{
			m_PlotMarker[i].PlotMakerEx->hide();
			delete m_PlotMarker[i].PlotMakerEx;
			m_PlotMarker[i].PlotMakerEx = NULL;
		}
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
		if(strcmp(pHead->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0)
		{
			tmt_BP2DiffThrTest* pThrTest = (tmt_BP2DiffThrTest*)pHead;

			MakerLine maker;
			maker.pCurrThrTest = pThrTest;

			pCurve = new QwtPlotCurve();	//启动电流
			pCurve->setTitle(/*tr("启动Ir")*/g_sLangTxt_Native_StartIr);
			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDiffCurrParas.m_fIr_Id, pThrTest->m_oDiffCurrParas.m_fScanTo) 
						<< QPointF( pThrTest->m_oDiffCurrParas.m_fIr_Id, pThrTest->m_oDiffCurrParas.m_fScanFrom);
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
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
		{
			tmt_BP2DiffRateTest* pRateTest = (tmt_BP2DiffRateTest*)pHead;

			MakerLine maker;
			maker.pCurrThrTest = pRateTest;

			pCurve = new QwtPlotCurve();
			pCurve->setTitle(/*tr("比率系数")*/g_sLangTxt_Native_RatioCoefficient);

			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pRateTest->m_oDiffCurrParas.m_fIr_Id, pRateTest->m_oDiffCurrParas.m_fScanTo) 
						<< QPointF( pRateTest->m_oDiffCurrParas.m_fIr_Id, pRateTest->m_oDiffCurrParas.m_fScanFrom);
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
		else if (strcmp(pHead->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
		{
			tmt_BP2CBOperateTest* pCBTest = (tmt_BP2CBOperateTest*)pHead;

			MakerLine maker;
			maker.pCurrThrTest = pCBTest;
/*
			pCurve = new QwtPlotCurve();
			pCurve->setTitle(tr("整组Ir-Id"));
			pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
			pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pCBTest->m_oDiffCurrParas.m_fIr_Id, pCBTest->m_oDiffCurrParas.m_fScanTo) 
						<< QPointF( pCBTest->m_oDiffCurrParas.m_fIr_Id, pCBTest->m_oDiffCurrParas.m_fScanFrom);
			pCurve->setSamples( curvePoints );
			pCurve->attach(this);
			maker.PlotCurve = pCurve;
*/
			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::Cross, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );	
			maker.PlotMaker = pMaker;

			pMaker = new QwtPlotMarker();
			pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			pMaker->setItemAttribute( QwtPlotItem::Legend, true );
			pMaker->setSymbol(new QwtSymbol(QwtSymbol::Rect, Qt::NoBrush,  
				QPen(Qt::cyan,2), QSize(6, 6) ) );
			pMaker->setValue(QPointF( -1000, -1000 )  );
			pMaker->attach( this );
			maker.PlotMakerEx = pMaker;

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

bool CBPDifferCharacPlot::eventFilter( QObject *object, QEvent *e )
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

void CBPDifferCharacPlot::clearResultAll()
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker[i].PlotMaker->setYValue(-1000);
	}
	
	replot();
}

void CBPDifferCharacPlot::clearSymbolPos(tmt_BP2DiffThrTest* pCurrThrTest)
{
	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	if(pMaker)
	{
		pMaker->setYValue(-1000);
	}
}

void CBPDifferCharacPlot::updateLabelTest(tmt_BP2DiffThrTest* pCurrThrTest)
{
	if (pCurrThrTest == NULL)
	{
		return;
	}

	fIrId = pCurrThrTest->m_oDiffCurrParas.m_fIr_Id;
	
	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest)==0)
	{
		fId = pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal;
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest)==0)
	{
		fId = pCurrThrTest->m_oDiffCurrParas.m_fIdiff;
	}

	strIrId.Format(_T("Ir-Id=%.3fA\n"),fIrId);
	strId.Format(_T("Id=%.3fA\n"),fId);

	strLabel = strIrId + strId;

	m_PlotLabelText->setText(strLabel.GetString());
}

QwtPlotMarker* CBPDifferCharacPlot::getMarkerByTestInfo(tmt_BP2DiffThrTest* pCurrThrTest)
{
	QwtPlotMarker *pCur = NULL;
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		if (m_PlotMarker.at(i).pCurrThrTest == pCurrThrTest)
		{
			pCur = m_PlotMarker.at(i).PlotMaker;
			break;
		}
	}

	return pCur;
}

QwtPlotCurve* CBPDifferCharacPlot::getCurveByTestInfo(tmt_BP2DiffThrTest* pCurrThrTest)
{
	QwtPlotCurve *pCur = NULL;
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		if (m_PlotMarker.at(i).pCurrThrTest == pCurrThrTest)
		{
			pCur = m_PlotMarker.at(i).PlotCurve;
			break;
		}
	}

	return pCur;
}

void CBPDifferCharacPlot::updatePlot()
{
	initPlot();
	tmt_BP2DiffThrTest* pThrTest = NULL;

	for (int i=0;i<m_PlotMarker.size();i++)
	{
		MakerLine p = m_PlotMarker.at(i);
		pThrTest = p.pCurrThrTest;

		if(strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0 || strcmp(pThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest)==0)
		{
			QVector<QPointF> curvePoints;
			curvePoints << QPointF( pThrTest->m_oDiffCurrParas.m_fIr_Id, pThrTest->m_oDiffCurrParas.m_fScanTo ) 
						<< QPointF( pThrTest->m_oDiffCurrParas.m_fIr_Id, pThrTest->m_oDiffCurrParas.m_fScanFrom );	
			if (m_PlotMarker.at(i).PlotCurve)
			{
				m_PlotMarker.at(i).PlotCurve->setSamples( curvePoints );
			}
		}
	}

	replot();
}

void CBPDifferCharacPlot::updatePlotPos(tmt_BP2DiffThrTest* pCurrThrTest)
{
	setAxisTitle( QwtPlot::xBottom, "Ir-Id(A)" );
	setAxisTitle( QwtPlot::yLeft, "Id(A)" );

	for (int i=0;i<m_PlotMarker.size();i++)
	{
		m_PlotMarker.at(i).PlotMaker->hide();

		if (m_PlotMarker.at(i).PlotCurve)
		{
			m_PlotMarker.at(i).PlotCurve->hide();
		}

		if(m_PlotMarker.at(i).PlotMakerEx)
		{
			m_PlotMarker.at(i).PlotMakerEx->hide();
		}
	}

	m_curve->hide();
	d_intervalCurve->hide();

	if(m_pCommonParaTest != pCurrThrTest)
	{
		m_pCommonParaTest = pCurrThrTest;
		initPlot();
	}

	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	QwtPlotCurve *pCurve = getCurveByTestInfo(pCurrThrTest);
	QString str = g_BPDifferTestMain->getValueByTestInfo(pCurrThrTest);

	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest)==0)
	{
		float fe = 5;//取得误差范围
		updateErrorBars(fe);
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );

		setAxisTitle( QwtPlot::xBottom, "Ir-Id(A)" );
		setAxisTitle( QwtPlot::yLeft, "Id(A)" );
		
		m_curve->show();
		d_intervalCurve->show();

		float fd = str.toFloat();
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIr_Id, pCurrThrTest->m_oDiffCurrParas.m_fScanTo ) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIr_Id, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);	
		if (pCurve)
		{
			pCurve->show();
			pCurve->setSamples( curvePoints );
		}
		
		for (int i=0;i<m_PlotMarker.size();i++)
		{
			if(strcmp(m_PlotMarker.at(i).pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0
				|| strcmp(m_PlotMarker.at(i).pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest)==0)
			{
				m_PlotMarker.at(i).PlotMaker->show();

				for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
				{
					if ((tmt_BP2DiffThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).pCurrThrTest)
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

		m_CurPos->setXValue(fd);
		m_CurPos->setYValue(0.05);
	}
	else if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest)==0)
	{
		float fe = 5;//取得误差范围
		updateErrorBars(fe);
		setAxisScale( QwtPlot::yLeft, 0.0, m_CurYScale );
		setAxisScale( QwtPlot::xBottom, 0.0, m_CurXScale );

		setAxisTitle( QwtPlot::xBottom, "Ir-Id(A)" );
		setAxisTitle( QwtPlot::yLeft, "Id(A)" );

		m_curve->show();
		d_intervalCurve->show();

		int pos = str.indexOf(",");
		
		float fIrId = str.mid(0,pos).toFloat();
		float fId = str.mid(pos+1).toFloat();

		for (int i=0;i<m_PlotMarker.size();i++)
		{
			if(strcmp(m_PlotMarker.at(i).pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest)==0)
			{
				for (int j = 0;j<m_pTmtTestMngr->m_nCount;j++)
				{
					if ((tmt_BP2DiffThrTest*)m_pTmtTestMngr->m_pParasBuffer[j] == m_PlotMarker.at(i).pCurrThrTest
						&& m_pTmtTestMngr->m_pParasBuffer[j]->m_nSelected)
					{
						m_PlotMarker.at(i).PlotMaker->show();
						m_PlotMarker.at(i).PlotMakerEx->show();
					}
					else
					{
						m_PlotMarker.at(i).PlotMaker->hide();
						m_PlotMarker.at(i).PlotMakerEx->hide();
					}
				}
			}
		}
	}

	m_CurPos->setZ(-10);	
	replot();
}

void CBPDifferCharacPlot::updateSymbolPos(tmt_BP2DiffThrTest* pCurrThrTest,bool bEnd)
{
	QwtPlotMarker *pMaker = getMarkerByTestInfo(pCurrThrTest);
	if(strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest)==0)
	{
		if (pMaker)
		{
			if (bEnd)
			{
				int v = _finite(pCurrThrTest->m_oDiffCurrResults.m_fIdiffActValue);
				if (v != 0)
				{
					pMaker->show();
					pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIr_Id,pCurrThrTest->m_oDiffCurrResults.m_fIdiffActValue);
				}
			}
			else
			{
				int v = _finite(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
				if (v != 0)
				{
					pMaker->show();
					pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fIr_Id,pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
				}
			}
		}
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest)==0)
	{
/*
		int v = _finite(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal);
		if (v != 0)
		{
			pMaker->show(); 
			pMaker->setValue(pCurrThrTest->m_oDiffCurrParas.m_fCurrScanVal,pCurrThrTest->m_oDiffCurrParas.m_fIdiff);
		}
*/
	}
	
	updateLabelTest(pCurrThrTest);
}

void CBPDifferCharacPlot::insertErrorBars( const QString &title,const QVector<QwtIntervalSample> &samples,const QColor &color )
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

void CBPDifferCharacPlot::updateErrorBars(float fe)
{
	QVector<QwtIntervalSample> rangeData;
	generateErrorRangeData(m_curvePoints,rangeData,fe);

	d_intervalCurve->setSamples( rangeData );
}

void CBPDifferCharacPlot::PlotDoubleClicked( float fx,float fy )
{
	if (g_BPDifferTestMain->m_bViewTestStarted)
	{
		return;
	}

	emit sig_PlotDoubleClicked(fx,fy);
}

void CBPDifferCharacPlot::PlotRightClicked(float fx,float fy)
{
	if (g_BPDifferTestMain->m_bViewTestStarted)
	{
		return;
	}

	m_popupMenu = new QMenu(this);
	m_addAction = new QAction(/*tr("添加测试点")*/g_sLangTxt_Native_AddTestPoint,this);
	m_addAction->setIcon (QPixmap( "./images/Add.png"));
	m_popupMenu->addAction(m_addAction);
	connect(m_addAction, SIGNAL(triggered()), this, SLOT(slot_AddTestItem()));

	m_fPointX = fx;
	m_fPointY = fy;
	m_popupMenu->exec(QCursor::pos());
}

void CBPDifferCharacPlot::slot_AddTestItem()
{
	emit sig_PlotRightClicked(m_fPointX,m_fPointY);
}

void CBPDifferCharacPlot::MouseMoved(float x,float y)
{
	if (g_BPDifferTestMain->m_bViewTestStarted)
	{
		return;
	}

	ASSERT(m_pCommonParaTest != NULL);

	QString str1 =  QString::number(x, 'f', 3);
	QString str2 =  QString::number(y, 'f', 3);

	CString str;
	CString strTmp;
	strTmp.Format(_T("Ir-Id=%.3fA\n"),str1.toFloat());
	str += strTmp;
	strTmp.Format(_T("Id=%.3fA"),str2.toFloat());
	str += strTmp;
	m_PlotLabelText->setText(QString::fromLocal8Bit(str.GetString()));
}

void CBPDifferCharacPlot::generateErrorRangeData( QVector<QPointF> &points,QVector<QwtIntervalSample> &rangeData,float fe )
{
	for (int i=0;i<points.size();i++)
	{
		QPointF p = points.at(i);
		rangeData.append( QwtIntervalSample( double( p.x() ),QwtInterval( p.y()*(1+fe/100), p.y()*(1-fe/100) ) ));
	}
}

void CBPDifferCharacPlot::slot_AddOneTest( tmt_BP2DiffThrTest* pCurrThrTest )
{
	ASSERT(pCurrThrTest != NULL);

	MakerLine maker;
	maker.pCurrThrTest = pCurrThrTest;
	
	QwtPlotCurve *pCurve = NULL;
	QwtPlotMarker *pMaker = NULL;

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
	{
		pCurve = new QwtPlotCurve();
		pCurve->setTitle(/*tr("启动电流")*/g_sLangTxt_Gradient_StartCur);

		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIr_Id, pCurrThrTest->m_oDiffCurrParas.m_fScanTo) 
			        << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIr_Id, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);
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
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
	{
		tmt_BP2DiffRateTest* pRateTest = (tmt_BP2DiffRateTest*)pCurrThrTest;

		pCurve = new QwtPlotCurve();
		pCurve->setTitle(/*tr("比率制动系数")*/g_sLangTxt_Native_RatioBrakeCoefficient);

		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIr_Id, pCurrThrTest->m_oDiffCurrParas.m_fScanTo) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIr_Id, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);
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
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
	{
/*
		pCurve = new QwtPlotCurve();
		pCurve->setTitle(tr("整组试验"));
		pCurve->setPen( Qt::red, 0, Qt::DashDotLine );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		QVector<QPointF> curvePoints;
		curvePoints << QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanTo) 
					<< QPointF( pCurrThrTest->m_oDiffCurrParas.m_fIbias, pCurrThrTest->m_oDiffCurrParas.m_fScanFrom);

		pCurve->setSamples( curvePoints );
		pCurve->attach(this);
		maker.PlotCurve = pCurve;
*/
		pMaker = new QwtPlotMarker();
		pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pMaker->setItemAttribute( QwtPlotItem::Legend, true );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush,  
			QPen(Qt::cyan,2), QSize(6, 6) ) );
		pMaker->setValue(QPointF( -1000, -1000 )  );
		pMaker->attach( this );	
		maker.PlotMaker = pMaker;

		pMaker = new QwtPlotMarker();
		pMaker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		pMaker->setItemAttribute( QwtPlotItem::Legend, true );
		pMaker->setSymbol(new QwtSymbol(QwtSymbol::Rect, Qt::NoBrush,  
			QPen(Qt::cyan,2), QSize(6, 6) ) );
		pMaker->setValue(QPointF( -1000, -1000 )  );
		pMaker->attach( this );
		maker.PlotMakerEx = pMaker;

		m_PlotMarker.append(maker);
	}

	m_CurPos->attach(this);

	updatePlotPos(pCurrThrTest);
}

void CBPDifferCharacPlot::slot_DelOneTest(tmt_BP2DiffThrTest* pCurrThrTest)
{
	for (int i=0;i<m_PlotMarker.size();i++)
	{
		MakerLine pMakerLine = m_PlotMarker.at(i);
		if (pMakerLine.pCurrThrTest == pCurrThrTest)
		{
			delete m_PlotMarker[i].PlotMaker;
			delete m_PlotMarker[i].PlotCurve;
			m_PlotMarker[i].PlotMaker = NULL;
			m_PlotMarker[i].PlotCurve = NULL;
			if(m_PlotMarker[i].PlotMakerEx)
			{
				delete m_PlotMarker[i].PlotMakerEx;
				m_PlotMarker[i].PlotMakerEx = NULL;
			}
			m_PlotMarker.removeAt(i);
		}
	}

	replot();
}

void CBPDifferCharacPlot::slot_DelAllTest(tmt_BP2DiffThrTest* pCurrThrTest)
{
	creatMaker();
	updatePlot();
	updatePlotPos(pCurrThrTest);
	replot();
}

void CBPDifferCharacPlot::setValueByInfo(tmt_BP2DiffThrTest* pCurrThrTest, float fx, float fy)
{
	float fUp=0;
	float fDown=0;
	g_BPDifferTestMain->calcuRangeByInfoAndX(fx,fUp,fDown);

	if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest)==0 || strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest)==0)
	{
		pCurrThrTest->m_oDiffCurrParas.m_fIr_Id = fx;
		pCurrThrTest->m_oDiffCurrParas.m_fScanFrom = fDown;
		pCurrThrTest->m_oDiffCurrParas.m_fScanTo = fUp;
	}
	else if (strcmp(pCurrThrTest->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest)==0)
	{
		pCurrThrTest->m_oDiffCurrParas.m_fIr_Id = fx;
		pCurrThrTest->m_oDiffCurrParas.m_fIdiff = fy;
	}
}