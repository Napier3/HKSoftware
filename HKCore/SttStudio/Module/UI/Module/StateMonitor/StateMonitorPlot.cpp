#include "StateMonitorPlot.h"
#include "StateMonitorWidget.h"
#include "time.h"

int g_nNewPlotWidth = 0;	//20241012 huangliang 记录开入开出最大字符长度
int g_nUITableWidth_Left = 0;	//20241018 huangliang 记录开始时U/I图表刻度的宽度
int g_nUITableWidth_Right = 0;	//20241104 huangliang 不知道为什么，UI的右标尺最小变为9了

bool g_HL_bFristShow = false;	//20241106 huangliang 第一次显示时，右边标尺会靠最右边。
bool g_HL_bSingle = false;		//20241107 huangliang 是否单通道

extern double g_dUIShowCoef; // 界面显示缩放比例

//20241012 huangliang 依据最大宽度获取最新字符串，iMaxLen为最大宽度
QString Stt_Global_CreateNewString(const QString &strValue, bool bLeft, int iMaxLen)
{
	int iMLen = iMaxLen;
	QString strNewValue = strValue;
	int iWordWidth = strValue.toLocal8Bit().length();
	if (iWordWidth < iMLen)
	{
		QString strSpace = "";
		for (int nIndex = iWordWidth; nIndex < iMLen; nIndex++)	//开出
		{
			strSpace += " ";
		}

		if (bLeft)	//左边显示，则空格加在字符串前
		{
			strNewValue = strSpace;
			strNewValue += strValue;
		}
		else //右边显示，则空格加在字符串后
		{
			strNewValue = strValue;
			strNewValue += strSpace;
		}
	}
	return strNewValue;
}

QString Stt_Global_GetBinBoutNewString(const QString &strValue, bool bLeft)	//20241012 huangliang 依据最大宽度获取最新字符串
{
	int iLen_Left = 0;
	int iLen_Right = 0;

//#ifdef _PSX_QT_LINUX_
//	iLen_Right = 10;
//#endif
// 	if (g_HL_bFristShow)
// 	{
// 		iLen_Left = 0;
// 		iLen_Right = 3;
// 	}
// 	else
//	if (g_HL_bSingle)
//	{
//		iLen_Left = 0;
//		iLen_Right = 1;
//	}

	if (bLeft)
	{
		int iSrcWidth = g_nUITableWidth_Left > g_nNewPlotWidth ? g_nUITableWidth_Left : g_nNewPlotWidth;
		int iMaxLen = iSrcWidth + iLen_Left;
		return Stt_Global_CreateNewString(strValue, bLeft, iMaxLen);
	}
	else
	{
		int iSrcWidth = g_nUITableWidth_Right > g_nNewPlotWidth ? g_nUITableWidth_Right : g_nNewPlotWidth;
		int iMaxLen = iSrcWidth + iLen_Right;
		return Stt_Global_CreateNewString(strValue, bLeft, iMaxLen);
	}
}
QString Stt_Global_GetUINewString(const QString &strValue, bool bLeft)	//20241030 huangliang 依据最大宽度获取最新字符串
{	
	int iLen_Left = 0;
	int iLen_Right = -4;
// 	if (g_HL_bFristShow)
// 	{
// 		iLen_Left = 0;
// 		iLen_Right = -6;
		if (g_HL_bSingle)	//20241107 huangliang  单通道时，U/I宽了，标尺再增加4个
		{
		iLen_Right += 3;
	}
	/*}*/

	if (bLeft)
	{
		int iSrcWidth = g_nUITableWidth_Left > g_nNewPlotWidth ? g_nUITableWidth_Left : g_nNewPlotWidth;
		int iMaxLen = iSrcWidth + iLen_Left;
		return Stt_Global_CreateNewString(strValue, bLeft, iMaxLen);
	}
	else
	{
		int iSrcWidth = g_nUITableWidth_Right > g_nNewPlotWidth ? g_nUITableWidth_Right : g_nNewPlotWidth;
		int iMaxLen = iSrcWidth + iLen_Right;
		return Stt_Global_CreateNewString(strValue, bLeft, iMaxLen);
	}
}

int Stt_Global_GetNewPosition(int iFontWith)	//20241028 huangliang 计算状态图上文字信息
{
	if (g_nUITableWidth_Left >= g_nNewPlotWidth)	//标尺未改变，文字位置也就不用再改变
		return 0;
	return (g_nNewPlotWidth - g_nUITableWidth_Left)*iFontWith;
}

QColor g_arrColor[MAX_COLOR_NUM]=
{
	Qt::yellow,Qt::green,Qt::red,Qt::magenta
	,Qt::blue,Qt::black,Qt::darkGray,Qt::cyan
	,Qt::white,Qt::darkRed,Qt::darkGreen,Qt::darkCyan
	,Qt::darkBlue,Qt::darkMagenta,Qt::darkYellow,Qt::gray
};

QString GetCurveStyleSheet(long nColorIndex)
{
	QString strRet = " QLabel{  background-color:black;color: yellow; }";

	if (xlang_IsCurrXLanguageChinese())
	{
	switch (nColorIndex)
	{
	case 0:
		strRet = " QLabel{ color: yellow; }"; // background-color:black;
		break;
	case 1:
		strRet = " QLabel{ color: green; }";
		break;
	case 2:
		strRet = " QLabel{ color: red; }";
		break;
	case 3:
		strRet = " QLabel{ color: magenta; }";
		break;
	case 4:
		strRet = " QLabel{ color: blue; }";
		break;
	case 5:
		strRet = " QLabel{ color: black; }";
		break;
	case 6:
		strRet = " QLabel{ color: darkGray; }";
		break;
	case 7:
		strRet = " QLabel{ color: cyan; }";
		break;
	case 8:
		strRet = " QLabel{ color: white; }";
		break;
	case 9:
		strRet = " QLabel{ color: darkRed; }";
		break;
	case 10:
		strRet = " QLabel{ color: darkGreen; }";
		break;
	case 11:
		strRet = " QLabel{ color: darkCyan; }";
		break;
	case 12:
		strRet = " QLabel{ color: darkBlue; }";
		break;
	case 13:
		strRet = " QLabel{ color: darkMagenta; }";
		break;
	case 14:
		strRet = " QLabel{ color: darkYellow; }";
		break;
	case 15:
		strRet = " QLabel{ color: gray; }";
		break;
	default:
		break;
	}
	} 
	else
	{
		switch (nColorIndex)
		{
		case 0:
			strRet = " QLabel{ color: red; }"; // background-color:black;
			break;
		case 1:
			strRet = " QLabel{ color: yellow; }";
			break;
		case 2:
			strRet = " QLabel{ color: blue; }";
			break;
		case 3:
			strRet = " QLabel{ color: magenta; }";
			break;
		case 4:
			strRet = " QLabel{ color: green; }";
			break;
		case 5:
			strRet = " QLabel{ color: black; }";
			break;
		case 6:
			strRet = " QLabel{ color: darkGray; }";
			break;
		case 7:
			strRet = " QLabel{ color: cyan; }";
			break;
		case 8:
			strRet = " QLabel{ color: white; }";
			break;
		case 9:
			strRet = " QLabel{ color: darkRed; }";
			break;
		case 10:
			strRet = " QLabel{ color: darkGreen; }";
			break;
		case 11:
			strRet = " QLabel{ color: darkCyan; }";
			break;
		case 12:
			strRet = " QLabel{ color: darkBlue; }";
			break;
		case 13:
			strRet = " QLabel{ color: darkMagenta; }";
			break;
		case 14:
			strRet = " QLabel{ color: darkYellow; }";
			break;
		case 15:
			strRet = " QLabel{ color: gray; }";
			break;
		default:
			break;
		}
	}

	return strRet;
}

void CurveData::append( const QPointF &point )
{

	// 	if (point.x()>1000)
	// 	{
	// 		maxx++;
	// 	}

	d_samples.append(point);
	if(point.y()<=miny) miny = point.y();
	if(point.y()>=maxy) maxy = point.y();
	if(point.x()<=minx) minx = point.x();
	if(point.x()>=maxx) maxx = point.x();
}


QStateMonitorPlot::QStateMonitorPlot(QWidget* parent) : QwtPlot(parent)
{
	m_pLastPoints = new CExBaseList;
	m_bNeedInit = false;
	m_dLastTime = 0;
	m_dRealTime = 0;
	m_pCursorPicker = 0;
	//m_oPainter.setAttribute(QwtPlotDirectPainter::FullRepaint, true);
	InitUI();
}

QStateMonitorPlot::~QStateMonitorPlot()
{
	for (int i = 0; i < m_oCurveList.size(); i++)
	{
		delete m_oCurveList[i];
	}
	m_oCurveList.clear();

	if(m_pCursorPicker)
	{
		delete m_pCursorPicker;
		m_pCursorPicker = NULL;
	}

	if(m_pLastPoints)
	{
		delete m_pLastPoints;
		m_pLastPoints = NULL;
	}

	if(m_pGrid)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if(m_pScaleWidget)
	{
		delete m_pScaleWidget;
		m_pScaleWidget = NULL;
	}
}

void QStateMonitorPlot::InitUI()
{
	InitGrid();
}

void QStateMonitorPlot::UpdateYTtile(QString strTitle,long nFontSize, bool bLeft)
{
	//QwtText strText = strTitle;
	QwtText strText(strTitle);
	QFont font;
	font.setPointSize(nFontSize);
	strText.setFont(font);

	if (bLeft)
	{
		setAxisTitle( QwtPlot::yLeft, strText);
	}
	else
	{
		setAxisTitle( QwtPlot::yRight, strText);
	}
}

void QStateMonitorPlot::UpdateYScale(float f1, float f2, bool bLeft)
{
	if (bLeft)
	{
		m_oYinterval.setMinValue(f1);
		m_oYinterval.setMaxValue(f2);
		setAxisScale( QwtPlot::yLeft, f1, f2 );
	}
	else
	{
		setAxisScale( QwtPlot::yRight, f1, f2 );
	}
}

void QStateMonitorPlot::UpdateXTtile(QString strTitle)
{
	QwtText strText = strTitle;
	setAxisTitle(QwtPlot::xBottom, strText);
}

void QStateMonitorPlot::UpdateXScale(float f1, float f2)
{
	m_oXinterval.setMinValue(f1);
	m_oXinterval.setMaxValue(f2);
	setAxisScale( QwtPlot::xBottom, f1, f2 );
}

void QStateMonitorPlot::UpdateYLeftRightScale(changed_type tagType, float fDown, float fUp)
{
	long nSpacing = 5;
	QList<double> ticks[QwtScaleDiv::NTickTypes];

	double fTop, fBottom;
	if (tagType == amplitude_type || tagType == fre_type)
	{
		if(fUp > fDown)
		{
			//正向递变
			fTop = fUp;
			fBottom = fDown;
		}
		else
		{
			//反向递变
			fTop = fDown;
			fBottom = fUp;
		}
		ticks[QwtScaleDiv::MajorTick] << 0;

		if (fTop - fBottom<20)//add wangtao 20240912 如果差值过小会导致显示不全
		{
			fTop = 20;
			fBottom = 0;
		}

		for (int i = 0; i <= nSpacing; i++)
		{
			ticks[QwtScaleDiv::MajorTick] << i * (int)(fTop - fBottom) / 5;
		}

		ticks[QwtScaleDiv::MajorTick] << (int)fTop * FRADIO;
		setAxisScale(QwtPlot::yLeft, (int)fBottom, (int)fTop + 1);	//20241113 huangliang 最大最小值取整
		setAxisScale(QwtPlot::yRight, (int)fBottom, (int)fTop + 1);	//20241105 huangliang 为保存宽度一致，添加右标尺
	}
	else if (tagType == phasor_type)
	{
		fBottom = 360;
		ticks[QwtScaleDiv::MajorTick] << 0 << 90 << 180 << 270 << 360 << 390;
		setAxisScale( QwtPlot::yLeft, 0, 360 );
		setAxisScale(QwtPlot::yRight, 0, 360);	//20241105 huangliang 为保存宽度一致，添加右标尺
	}

	QwtScaleDiv scaleDiv(ticks[QwtScaleDiv::MajorTick].first(),ticks[QwtScaleDiv::MajorTick].last(),ticks );
	setAxisScaleDiv(QwtPlot::yLeft, scaleDiv);
	setAxisScaleDiv(QwtPlot::yRight, scaleDiv);

	int iWith = QString::number((int)fBottom).toLocal8Bit().length();	//20241105 huangliang 记录最大宽度
	if (g_nUITableWidth_Left < iWith)
		g_nUITableWidth_Left = iWith;
	iWith = QString::number((int)fBottom).toLocal8Bit().length();
	if (g_nUITableWidth_Right < iWith)
		g_nUITableWidth_Right = iWith;	
	if (g_nUITableWidth_Right < 9)
		g_nUITableWidth_Right = 9;
}

void QStateMonitorPlot::UpdateCurve(long nIndex, const QVector<QPointF>& points)
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

	//增量绘图的drawSeries存在350ms的延迟
	//按照全图重绘的方式反而能够胜任划差递变
	//if(nFrom != pCurvePoints->size())
	//{
	//	m_oPainter.drawSeries(pCurve, nFrom - 1, pCurvePoints->size() - 1);
	//}

	if(pCurvePoints->maxx > m_oXinterval.maxValue())
	{
		m_oXinterval.setMinValue(m_oXinterval.minValue() + 30);
		m_oXinterval.setMaxValue(m_oXinterval.maxValue() + 30);
		setAxisScale(QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue());
	}
}

void QStateMonitorPlot::UpdateCurves()
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

void QStateMonitorPlot::ClearCurves()
{
	if(m_bNeedInit)
	{
		for(int i = 0; i < m_oUpdateList.size(); i++)
		{
			m_oPreUpdateList[i].clear();
			m_oUpdateList[i].clear();
		}

		for (int i = 0; i < m_oCurveList.size(); i++)
		{
			//CurveData内都是QPointF对象而非指针,可直接clear
			CurveData* pData = static_cast<CurveData*>(m_oCurveList[i]->data());
			pData->maxx = pData->maxy = pData->minx = pData->miny = 0;
			pData->clear();
		}
		m_pLastPoints->RemoveAll();
		m_dLastTime = 0;
		m_dRealTime = 0;
		m_oXinterval.setMinValue(0);
		m_oXinterval.setMaxValue(30);
		setAxisScale(QwtPlot::xBottom, m_oXinterval.minValue(), m_oXinterval.maxValue());

		replot();
	}
}

void QStateMonitorPlot::AddStopPoint()
{
	for (int i = 0; i < m_oPreUpdateList.size(); i++)
	{
		QwtPlotCurve* pCurve = m_oCurveList.at(i);
		CurveData* pCurvePoints = static_cast<CurveData*>(pCurve->data());
		QPointF pt;
		if(m_oPreUpdateList[i].size())
		{
			pt = m_oPreUpdateList[i].last();
		}
		else
		{
			long nSize = pCurvePoints->size() - 1;
			if(nSize < 0)
			{
				continue;
			}
			pt = pCurvePoints->sample(nSize);
		}
		pt.setX(m_dLastTime);
		m_oPreUpdateList[i].append(pt);
	}
}

void QStateMonitorPlot::InitGrid()
{
	plotLayout()->setAlignCanvasToScales(true); //为所有轴线设置排列画布到轴线比例尺
	enableAxis( QwtPlot::xBottom,true);//允许自定义刻度

	QwtPlotCanvas *pCanvas = new QwtPlotCanvas();
	setCanvas(pCanvas);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#else
	pCanvas->setAttribute(Qt::WA_PaintOutsidePaintEvent, true);
#endif

	m_pGrid = new QwtPlotGrid();
	m_pGrid->setPen(Qt::gray, 0.0, Qt::DotLine);
	m_pGrid->enableX(true);
	m_pGrid->enableY(true);
	m_pGrid->attach(this);

	Background *pBk = new Background();
	pBk->attach(this);

	//设置坐标指示器
	m_pCursorPicker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas());
	m_pCursorPicker->setStateMachine(new QwtPickerDragPointMachine());
	m_pCursorPicker->setRubberBandPen(QColor( Qt::green));
	m_pCursorPicker->setRubberBand(QwtPicker::CrossRubberBand);
	m_pCursorPicker->setTrackerPen(QColor( Qt::black));

	m_pScaleWidget = axisWidget(0);
	QFont oFont;
	oFont.setPointSize(7);
	m_pScaleWidget->setFont(oFont);
	m_pScaleWidget = axisWidget(1);
	m_pScaleWidget->setFont(oFont);

	UpdateYScale(0, 130);
	UpdateXScale(0,30);

	//增加左侧标尺范围以显示全部数据
	axisWidget(QwtPlot::yLeft)->setTitle (" ");
}
