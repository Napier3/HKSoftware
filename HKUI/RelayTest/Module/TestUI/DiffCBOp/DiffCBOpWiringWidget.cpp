#include "DiffCBOpWiringWidget.h"
#include <qmath.h>
#include "../../XLangResource_Native.h"
QDiffCBOpWiringWidget::QDiffCBOpWiringWidget(QWidget *parent)
: QWidget(parent)
{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	nKph = 0;
	m_fKph = 0;
	m_fKpm = 0;
	m_fKpl = 0;
	m_nInSel = 0;
	m_fIbase = 0;
	m_bMinAxis = 0;
	m_nConnectMode = 0;
	m_nPhase = 0;
	m_nAdoptWind = 0;
	m_nPhCorrectMode = 0;
	m_nIbiasCal = 0;
	m_nWindH = 0;
	m_nWindM = 0;
	m_nWindL = 0;
	m_nK1 = 0;
	m_nK2 = 0;
	m_nBalanceterms = 0;
	m_nCT = 0;
	m_nKcal = 0;

	initTableData();
	initTable();
}

QDiffCBOpWiringWidget::~QDiffCBOpWiringWidget()
{

}

void QDiffCBOpWiringWidget::setCommonData(CExBaseList* pCommonParaTest)
{
	ASSERT(pCommonParaTest != NULL);

	m_pCommonParaTest = pCommonParaTest;
	POS pos = m_pCommonParaTest->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pCommonParaTest->GetNext(pos);
		SetValueToPage(pData);
	}

	m_oDiffCBOpCalTool.Init();

	m_oDiffCBOpCalTool.InitParas6I(m_nInSel, m_fIbase, NULL, m_bMinAxis, m_nPhCorrectMode, m_nIbiasCal,
		m_nWindH, m_nWindM, m_nWindL, m_nAdoptWind, m_nK1, m_nK2, m_nConnectMode, m_nPhase, m_nCT, m_nBalanceterms);

	/*m_oDiffCBOpCalTool.InitParas_AutoCalBalanceFactors(m_fHvKVA,m_fHvVol, m_fMvVol,m_fLvVol,
		m_fHvCT,1.0f, m_fMvCT, 1.0f, m_fLvCT, 1.0f);*/
	m_oDiffCBOpCalTool.GetKps(m_fKph, m_fKpm, m_fKpl);
}
void QDiffCBOpWiringWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	
	if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKVA)
	{
		m_fHvKVA = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CURENT)
	{
		m_fCur = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKPH)
	{
		m_fKph = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVVOL)
	{
		m_fHvVol = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCUR)
	{
		m_fHvCur = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCT)
	{
		m_fHvCT = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVVOL)
	{
		m_fMvVol = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCUR)
	{
		m_fMvCur = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCT)
	{
		m_fMvCT = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVVOL)
	{
		m_fLvVol = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCUR)
	{
		m_fLvCur = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCT)
	{
		m_fLvCT = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVKPM)
	{
		m_fKpm = CString_To_double(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVKPL)
	{
		m_fKpl = CString_To_double(pData->m_strValue);
	}
	if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND)
	{
		m_nAdoptWind = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSEL)
	{
		m_nInSel = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSET)
	{
		m_fIbase = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE)
	{
		m_bMinAxis = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE)
	{
		m_nPhCorrectMode = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH)
	{
		m_nIbiasCal = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH)
	{
		m_nWindH = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM)
	{
		m_nWindM = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL)
	{
		m_nWindL = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1)
	{
		m_nK1 = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2)
	{
		m_nK2 = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSGROUPMODE)
	{
		m_nConnectMode = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE)
	{
		m_nPhase = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT)
	{
		m_nCT = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS)
	{
		m_nBalanceterms = CString_To_long(pData->m_strValue);
	}
}

void QDiffCBOpWiringWidget::initTable()
{
	m_TabelData = new QTableWidget(this);
	m_TabelData->setStyleSheet(QString::fromUtf8("background-color: rgb(167,183,181);"));
	QHeaderView* pTop = m_TabelData->horizontalHeader();
	
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	pTop->setSectionsClickable(false);
	pTop->setSectionsMovable(false);
#endif
	
	QHeaderView* pLeft = m_TabelData->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	m_TabelData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif
	m_TabelData->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TabelData->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TabelData->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_TabelData->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(171,167,176);}"); //设置表头背景色
	m_TabelData->setColumnCount(2);

	QFontMetrics fontMetrics = QFontMetrics(font());

	int nLabelWidth1 = fontMetrics.width(tr("IR(A)")) + 10;
	int nLabelWidth2 = fontMetrics.width(tr("900.000")) + 80;
	//int nLabelWidth3 = fontMetrics.width(/*tr("单位")*/g_sLangTxt_Unit) + 20;

	QStringList headers;
	headers <</*tr("名称")*/g_sLangTxt_Name <</*tr("幅值")*/g_sLangTxt_Native_Amplitude;
	m_TabelData->setHorizontalHeaderLabels(headers);
	m_TabelData->setColumnWidth(0, nLabelWidth1);
	m_TabelData->setColumnWidth(1, nLabelWidth2);
	//m_TabelData->setColumnWidth(2, nLabelWidth3);
	//m_TabelData->setColumnWidth(3, nLabelWidth2);
	//m_TabelData->setColumnWidth(4, 70);

	QStringList list;
	//QStringList listUnit;


	list << tr("IR") << tr("Id");
	//	<< tr("IR(C)") << ("Id(A)") << tr("Id(B)") << tr("Id(C)");
	//listUnit << tr(" ") << tr(" ") << tr(" ") << tr("A") << tr("A") << tr("A") << tr("A") << tr("A");

	for (int i = 0; i < 2; i++)
	{
		CString strText = "1";
		QTableWidgetItem *item1 = new QTableWidgetItem(list.at(i));
		item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		QTableWidgetItem *item2 = new QTableWidgetItem("0.000");
		item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//		QTableWidgetItem *item3 = new QTableWidgetItem(listUnit.at(i));
//		item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//		QTableWidgetItem *item4 = new QTableWidgetItem("");
//		item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//		QTableWidgetItem *item5 = new QTableWidgetItem("");
//	    item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

		int rowCount = m_TabelData->rowCount();
		m_TabelData->insertRow(rowCount);
		m_TabelData->setRowHeight(rowCount, 15);
		m_TabelData->setItem(rowCount, 0, item1);
		m_TabelData->setItem(rowCount, 1, item2);
//		m_TabelData->setItem(rowCount, 2, item3);
//		m_TabelData->setItem(rowCount, 3, item4);
//		m_TabelData->setItem(rowCount, 4, item5);
	}
}

void QDiffCBOpWiringWidget::resizeEvent(QResizeEvent* e)
{
	repaint();
}

void QDiffCBOpWiringWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);
	drawBackground(&painter);
	drawWiring(&painter);

	QRect rectTop(rect().left(), rect().top(), rect().width(), rect().height() / 2);
	QRect rectButtom(rect().left(), rectTop.bottom(), rect().width(), rect().height() / 2);
	m_TabelData->setGeometry(rectButtom);
	updateTableRowHightSize(rectButtom.height());
}

void QDiffCBOpWiringWidget::drawWiring(QPainter *painter)
{
	QPen pen;
	QFont font;
	pen.setWidth(1);
	font.setUnderline(true);
	font.setPointSize(15);
	font.setBold(true);
	painter->setPen(pen);
	painter->setFont(font);
	QFontMetrics fontMetrics = QFontMetrics(font);
	float fHMargin = 25;
	float fVMargin = 5;
	float fRectHeight = fontMetrics.height() * 3 + 5;

	float fRectWidth = rect().width() - 2 * fHMargin;
	float fpointsWidth = (fRectWidth - 20) / 8;
	float fpointsWidth2 = (fRectWidth - 20) / 3;
	float fCircleR = 4;
	QPointF testDevicepoints[8];
	QPointF protectDevicepoints1[8];
	QPointF protectDevicepoints2[4];

	QStringList nameList1;
	QStringList nameList2;
	QStringList nameList3;
	nameList1 << tr("A") << tr("B") << tr("C") << tr("N") << tr("a") << tr("b") << tr("c") << tr("n");
	nameList2 << tr("IA") << tr("IB") << tr("IC") << tr("IN") << tr("Ia'") << tr("Ib'") << tr("Ic'") << tr("In'");
	nameList3 << tr("IA") << tr("IB") << tr("IC") << tr("IN"); 
		QString strHSide = /*CString("   高压侧   ")*/ tr("   ") + g_sLangTxt_Diff_HighVoltSide + tr("   ");
		QString strMSide = /*CString("   中压侧   ")*/ tr("   ") + g_sLangTxt_Diff_MedVoltSide + tr("   ");
		QString strLSide = /*CString("   低压侧   ")*/ tr("   ") + g_sLangTxt_Diff_LowVoltSide + tr("   ");
		QString strDiff =/* CString("差动保护电流端子")*/ g_sLangTxt_Diff_DiffProtCurrTerm;
		QString strProtect = /*CString("继电保护测试仪")*/ g_sLangTxt_Diff_RelayTest;

	for (int i = 0; i < 8; i++)
	{
		if (i < 4)
		{
			testDevicepoints[i].setX(rect().left() + fHMargin + 10 + i*fpointsWidth);
			testDevicepoints[i].setY(rect().top() + fVMargin + fRectHeight - 5 - fCircleR);
			protectDevicepoints1[i].setX(rect().left() + fHMargin + 10 + i*fpointsWidth);
			protectDevicepoints1[i].setY(rect().height() / 2 - fVMargin - fRectHeight + 5 + fCircleR);
		}
		else
		{
			testDevicepoints[i].setX(rect().left() + fHMargin + 10 + (i + 1)*fpointsWidth);
			testDevicepoints[i].setY(rect().top() + fVMargin + fRectHeight - 5 - fCircleR);
			protectDevicepoints1[i].setX(rect().left() + fHMargin + 10 + (i + 1)*fpointsWidth);
			protectDevicepoints1[i].setY(rect().height() / 2 - fVMargin - fRectHeight + 5 + fCircleR);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		protectDevicepoints2[i].setX(rect().left() + fHMargin + 10 + i*fpointsWidth2);
		protectDevicepoints2[i].setY(rect().height() / 2 - fVMargin - fRectHeight + 5 + fCircleR);
	}

	int nLabelHeight = fontMetrics.height() + 5;
	QRectF rect1(testDevicepoints[0].x(), rect().top() + fVMargin + 5, testDevicepoints[3].x() - testDevicepoints[0].x(), nLabelHeight);
	QRectF rect2(testDevicepoints[4].x(), rect().top() + fVMargin + 5, testDevicepoints[7].x() - testDevicepoints[4].x(), nLabelHeight);
	QRectF rect4(testDevicepoints[0].x(), rect().top() + fVMargin + 5, testDevicepoints[7].x() - testDevicepoints[0].x(), nLabelHeight);
	QRectF rect3(rect().left() + fHMargin, rect().height() / 2 - fVMargin - 5 - 20, fRectWidth, nLabelHeight);

	//绘制上方矩形
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter->setPen(pen);
	painter->setBrush(Qt::gray);
	painter->drawRect(rect().left() + fHMargin, rect().top() + fVMargin, fRectWidth, fRectHeight);
	//if (m_nDisType == 0)
	//{
		if (m_nAdoptWind == TestWind_HightToLow)		//高-低
		{
			painter->drawText(rect1, Qt::AlignCenter, strHSide);
			painter->drawText(rect2, Qt::AlignCenter, strLSide);
		}
		else if (m_nAdoptWind == TestWind_HightToMin)	//高-中
		{
			painter->drawText(rect1, Qt::AlignCenter, strHSide);
			painter->drawText(rect2, Qt::AlignCenter, strMSide);
		}
		else if (m_nAdoptWind == TestWind_MinToLow)	//中-低
		{
			painter->drawText(rect1, Qt::AlignCenter, strMSide);
			painter->drawText(rect2, Qt::AlignCenter, strLSide);
		}
	//}
	//else
	//{
	//	//painter->drawText(rect4, Qt::AlignCenter, strDiff);
	//}

	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::white);
	QList<QColor> colors;
	colors << QColor(Qt::yellow) << QColor(Qt::green) << QColor(Qt::red) << QColor(Qt::blue);
	int nWind1PointCount = 0;
	int nWind2PointCount = 0;
	if (m_nAdoptWind == TestWind_HightToLow)
	{
		//		if(m_pCommonParaTest->m_oDiffCurrParas.m_nWindH == StarType) //0-Y 1-△   //2023.7.11 zhouhj 改为恒定4相接线方式
		{
			nWind1PointCount = 4;
		}
		// 		else
		// 		{
		// 			nWind1PointCount = 3;
		// 		}

		//		if(m_pCommonParaTest->m_oDiffCurrParas.m_nWindL == StarType)
		{
		nWind2PointCount = 4;
	}
		// 		else
		// 		{
		// 			nWind2PointCount = 3;
		// 		}
	}
	else if (m_nAdoptWind == TestWind_HightToMin)
	{
		if (m_nWindH == StarType)
		{
			nWind1PointCount = 4;
		}
		else
		{
			nWind1PointCount = 3;
		}

		if (m_nWindM == StarType)
		{
			nWind2PointCount = 4;
		}
		else
		{
			nWind2PointCount = 3;
		}
	}
	else if (m_nAdoptWind == TestWind_MinToLow)
	{
		if (m_nWindM == StarType)
		{
			nWind1PointCount = 4;
		}
		else
		{
			nWind1PointCount = 3;
		}

		if (m_nWindL == StarType)
		{
			nWind2PointCount = 4;
		}
		else
		{
			nWind2PointCount = 3;
		}
	}

	//if (m_nDisType == 0)
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		drawCTPoint(painter, testDevicepoints[i], nameList1.at(i), colors.at(i % 4), false);
	//	}
	//}
	//else
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		drawCTPoint(painter, testDevicepoints[i], nameList1.at(i), colors.at(i % 4), false);
	//	}
	//}

	//绘制下方矩形
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter->setPen(pen);
	painter->setBrush(Qt::gray);
	painter->drawRect(rect().left() + fHMargin, rect().height() / 2 - fVMargin - fRectHeight, fRectWidth, fRectHeight);

	painter->setFont(font);
	painter->drawText(rect3, Qt::AlignCenter, strProtect);

	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::white);


	for (int i = 0; i < 8; i++)
	{
		drawCTPoint(painter, protectDevicepoints1[i], nameList2.at(i), colors.at(i % 4), true);
	}
	

	//绘制连接线
	if (m_nDisType == 0)
	{
		for (int i = 0; i < nWind1PointCount; i++)
		{
			drawLine(painter, testDevicepoints[i], protectDevicepoints1[i], colors.at(i % 4));
		}

		for (int i = 0; i < nWind2PointCount; i++)
		{
			drawLine(painter, testDevicepoints[i + 4], protectDevicepoints1[i + 4], colors.at(i % 4));
		}
	}
	else
	{
		//TestPhasor_type{APhase = 0,BPhase,CPhase,ABCPhase,ABPhase,BCPhase,CAPhase};
		switch (m_nPhase)
		{
		case TestPhasor_type::APhase: //A
			drawLine(painter, testDevicepoints[0], protectDevicepoints2[0], colors.at(0));
			break;
		case TestPhasor_type::BPhase: //B
			drawLine(painter, testDevicepoints[1], protectDevicepoints2[1], colors.at(1));
			break;
		case TestPhasor_type::CPhase: //C
			drawLine(painter, testDevicepoints[2], protectDevicepoints2[2], colors.at(2));
			break;
		case TestPhasor_type::ABCPhase: //ABC
			drawLine(painter, testDevicepoints[0], protectDevicepoints2[0], colors.at(0));
			drawLine(painter, testDevicepoints[1], protectDevicepoints2[1], colors.at(1));
			drawLine(painter, testDevicepoints[2], protectDevicepoints2[2], colors.at(2));
			break;
		case TestPhasor_type::ABPhase:
			drawLine(painter, testDevicepoints[0], protectDevicepoints2[0], colors.at(0));
			drawLine(painter, testDevicepoints[1], protectDevicepoints2[1], colors.at(1));
			break;
		case TestPhasor_type::BCPhase:
			drawLine(painter, testDevicepoints[1], protectDevicepoints2[1], colors.at(1));
			drawLine(painter, testDevicepoints[2], protectDevicepoints2[2], colors.at(2));
			break;
		case TestPhasor_type::CAPhase:
			drawLine(painter, testDevicepoints[2], protectDevicepoints2[2], colors.at(2));
			drawLine(painter, testDevicepoints[0], protectDevicepoints2[0], colors.at(0));
			break;
		default:
			break;
		}
		drawLine(painter, testDevicepoints[3], protectDevicepoints2[3], colors.at(3));
	}
}

void QDiffCBOpWiringWidget::drawCTPoint(QPainter *painter, QPointF pointf, QString strText, QColor color, bool bBellow)
{
	QFont font;
	font.setUnderline(false);
	font.setPointSize(10);
	font.setBold(true);
	QPen pen;
	pen.setColor(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);
	painter->setFont(font);
	painter->setBrush(color);

	painter->drawEllipse(pointf, 5, 5);
	QFontMetrics fontMetrics = QFontMetrics(font);
	int nHeight = fontMetrics.height();

	QRectF rect;
	if (bBellow)
	{
		rect.setX(pointf.x() - 12);
		rect.setY(pointf.y() + 10);
	}
	else
	{
		rect.setX(pointf.x() - 12);
		rect.setY(pointf.y() - 10 - nHeight);
	}
	rect.setWidth(24);
	rect.setHeight(nHeight);

	painter->drawText(rect, Qt::AlignCenter, strText);
}

void QDiffCBOpWiringWidget::drawLine(QPainter *painter, QPointF point1, QPointF point2, QColor color)
{
	QPen pen;
	pen.setWidth(2);
	pen.setColor(color);
	QPointF points[4];
	points[0] = point1;
	points[1].setX(point1.x());
	points[1].setY((point1.y() + point2.y()) / 2);
	points[2].setX(point2.x());
	points[2].setY((point1.y() + point2.y()) / 2);
	points[3] = point2;

	painter->setPen(pen);
	painter->drawPolyline(points, 4);
}

void QDiffCBOpWiringWidget::drawBackground(QPainter *painter)
{
	QRect rectTop(rect().left(), rect().top(), rect().width(), rect().height() / 2);
	QRect rectButtom(rect().left(), rectTop.bottom(), rect().width(), rect().height() / 2);
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::white);
	painter->drawRect(rectTop);

	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::blue);
	painter->drawRect(rectButtom);
	painter->restore();
}

void QDiffCBOpWiringWidget::updateTableRowHightSize(int height)
{
	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelHeight = fontMetrics.height() + 10;
	m_TabelData->horizontalHeader()->setFixedHeight(nLabelHeight);
	int H = height - 30;
	for (int i = 0; i < m_TabelData->rowCount(); i++)
	{
		m_TabelData->setRowHeight(i, H / m_TabelData->rowCount());
	}
}

void QDiffCBOpWiringWidget::updateTable(CString strMacroID)
{
	if (strMacroID == "")
	{
		return;
	}

	QStringList list;
	QStringList listUnit;
	QStringList headers;

	//if ((strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE) || (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME))
	//{
	list << tr("IR") << tr("Id");
			//<< tr("IR(C)") << ("Id(A)") << tr("Id(B)") << tr("Id(C)");
		//listUnit << tr(" ") << tr(" ") << tr(" ") << tr("A") << tr("A") << tr("A") << tr("A") << tr("A");
	headers <</*tr("名称")*/g_sLangTxt_Name <</*tr("幅值")*/g_sLangTxt_Native_Amplitude <</*tr("单位")*/g_sLangTxt_Unit << /*CString("标幺值")*/ g_sLangTxt_DiffCBOp_StandardValue << CString("接线系数")/*g_sLangTxt_Native_WiringCoeff*/;
		m_nDisType = 0;


	initTableData();
	//	calCoefs(pParaTest);

	getTableRealData(strMacroID);

	m_TabelData->setHorizontalHeaderLabels(headers);
	int  colN = m_TabelData->columnCount();
	for (int i = 0; i < 2; i++)
	{
		m_TabelData->item(i, 0)->setText(list.at(i));
		m_TabelData->item(i, 1)->setText(m_strBanlanceCoefs[i]);
	}

	repaint();
}

void QDiffCBOpWiringWidget::updateTableData(CString strMacroID)
{
	if (strMacroID == "")
	{
		return;
	}

	initTableData();
	getTableRealData(strMacroID);

	int colN = m_TabelData->columnCount();
	for (int i = 0; i < 2; i++)
	{
		m_TabelData->item(i, 1)->setText(m_strBanlanceCoefs[i]);
		//m_TabelData->item(i, 3)->setText(m_strAxis[i]);
		//m_TabelData->item(i, 4)->setText(m_strWiringCoefs[i]);
	}

	repaint();
}

void QDiffCBOpWiringWidget::initTableData()   //把表格数值都初始化为零
{
	for (int i = 0; i < 2;  i++)
	{
		m_strBanlanceCoefs[i] = tr("  ");
		//m_strAxis[i] = tr("  ");
		//m_strWiringCoefs[i] = tr("  ");
	}
}

void QDiffCBOpWiringWidget::getTableRealData(CString strMacroID)
{
	if (strMacroID == "")
	{
		return;
	}
	float Ka, Kb, Kc;
	//计算I1和I2（6路电流）
	//m_oDiffCalTool.CurrentCal(&m_fIdiff, m_fIbias);

	//取得接线系数
	//m_oDiffCalTool.GetKjx(m_fKjxh, m_fKjxl);

	switch (m_nPhase)
	{
	case APhase:
		Ka = 1;
		Kb = 0.5;
		Kc = 0.5;
		break;
	case BPhase:
		Ka = 0.5;
		Kb = 1;
		Kc = 0.5;
		break;
	case CPhase:
		Ka = 0.5;
		Kb = 0.5;
		Kc = 1;
		break;
	case ABCPhase:
		Ka = 1;
		Kb = 1;
		Kc = 1;
		break;
	case ABPhase:
		Ka = 1;
		Kb = 0.5;
		Kc = 0.5;
		break;
	case BCPhase:
		Ka = 1;
		Kb = 0.5;
		Kc = 0.5;
		break;
	case CAPhase:
		Ka = 1;
		Kb = 0.5;
		Kc = 0.5;
		break;
	default:
		break;
	}

	if (m_nAdoptWind == TestWind_HightToLow)
	{
		float fKph = m_fCur * m_fKph;
		//float fKpm = (m_fCur * m_fKph) / 2;
		m_strBanlanceCoefs[0] = QString::number(fKph* Ka, 'f', 3);
		//m_strBanlanceCoefs[1] = QString::number(fKph * Kb, 'f', 3);
		//m_strBanlanceCoefs[2] = QString::number(fKph* Kc, 'f', 3);
		//if (strMacroID != STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
		//{
		//m_strWiringCoefs[0] = QString::number(m_fKjxh, 'f', 3);
		//m_strWiringCoefs[2] = QString::number(m_fKjxl, 'f', 3);
		//}
	}
	else if (m_nAdoptWind == TestWind_HightToMin)
	{
		m_strBanlanceCoefs[0] = QString::number(m_fKph, 'f', 3);
		//m_strBanlanceCoefs[1] = QString::number(m_fKpm, 'f', 3);
		//m_strBanlanceCoefs[2] = QString::number(m_fKpl, 'f', 3);
		/*if (strMacroID != STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
		{
		m_strWiringCoefs[0] = QString::number(m_fKjxh, 'f', 3);
		m_strWiringCoefs[1] = QString::number(m_fKjxl, 'f', 3);
		}*/
	}
	else if (m_nAdoptWind == TestWind_MinToLow)
	{
		m_strBanlanceCoefs[0] = QString::number(m_fKph, 'f', 3);
		//m_strBanlanceCoefs[1] = QString::number(m_fKpm, 'f', 3);
		//m_strBanlanceCoefs[2] = QString::number(m_fKpl, 'f', 3);
		/*if (strMacroID != STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
		{
		m_strWiringCoefs[1] = QString::number(m_fKjxh, 'f', 3);
		m_strWiringCoefs[2] = QString::number(m_fKjxl, 'f', 3);
		}*/
	}

	m_strBanlanceCoefs[1] = QString::number(m_fKph, 'f', 3);
	//m_strBanlanceCoefs[4] = QString::number(m_fKpm, 'f', 3);
	//m_strBanlanceCoefs[5] = QString::number(m_fKpl, 'f', 3);
	// 	if (m_bMinAxis == MarkValue_Type && m_nInSel == SettingValue)
	// 	{
	// 		m_fIe = m_fIbase;
	// 	}
	// 	else
	// 	{
	// 		m_oDiffCalTool.GetIet(m_fIe);
	// 	}

	//m_strBanlanceCoefs[3] = QString::number(m_fIe, 'f', 3);

	//ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

	/*switch (m_nPhase)
	{
	case TestPhasor_type::APhase:
	m_fIh = pChCurrents[0].famptitude;
	m_fIl = pChCurrents[3].famptitude;
	break;
	case TestPhasor_type::BPhase:
	m_fIh = pChCurrents[1].famptitude;
	m_fIl = pChCurrents[4].famptitude;
	break;
	case TestPhasor_type::CPhase:
	m_fIh = pChCurrents[2].famptitude;
	m_fIl = pChCurrents[5].famptitude;
	break;
	case TestPhasor_type::ABCPhase:
	case TestPhasor_type::ABPhase:
	case TestPhasor_type::BCPhase:
	case TestPhasor_type::CAPhase:
	m_fIh = pChCurrents[0].famptitude;
	m_fIl = pChCurrents[3].famptitude;
	break;
	default:
	break;
	}*/

	//取得Id、Ir
	//if (strcmp(strMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pParaTest->strMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0)
	//{
	//	m_fId = pParaTest->m_oDiffCurrParas.m_fIdiff;
	//	m_fIr = pParaTest->m_oDiffCurrParas.m_fIbias;
	//}
	//if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE)
	//{
	//	m_fId = m_fIdiff;
	//	m_fIr = m_fIbias;
	//}
	//else if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
	//{
	//	m_fId = m_fIdiff;
	//	m_fIr = 0;
	//}
	//else if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME)
	//{
	//	m_fId = m_fIdiff;
	//	m_fIr = m_fIbias;
	//}

	//	if (m_fIh < 0 || m_fIh > 100)
	//	{
	//	m_strBanlanceCoefs[4] = tr("——");
	//	}
	//	else
	//	{
	//		m_strBanlanceCoefs[4] = QString::number(m_fIh, 'f', 3);
	//	}

	//	if (m_fIl < 0 || m_fIl > 100)
	//	{
	//		m_strBanlanceCoefs[5] = tr("——");
	//	}
	//	else
	//	{
	//		m_strBanlanceCoefs[5] = QString::number(m_fIl, 'f', 3);
	//	}

	//	m_strBanlanceCoefs[6] = QString::number(m_fId, 'f', 3);
	//	m_strBanlanceCoefs[7] = QString::number(m_fIr, 'f', 3);

	//if (m_strBanlanceCoefs[4] == tr("——"))
	//{
	//	m_strAxis[4] = tr("——");
	//}
	//else
	//{
	//		m_strAxis[4] = QString::number(m_fIh / m_fIe, 'f', 3);
	//}

	/*if (m_strBanlanceCoefs[5] == tr("——"))
	{
	m_strAxis[5] = tr("——");
	}*/
	//	else
	//	{
	//		m_strAxis[5] = QString::number(m_fIl / m_fIe, 'f', 3);
	//	}

	//if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
	//{
	//	m_strAxis[6] = QString::number(m_fId / m_fIe, 'f', 3);
	//	//m_strAxis[7] = tr(" ");
	//}
	//else
	//{
	//	m_strAxis[6] = QString::number(m_fId / m_fIe, 'f', 3);
	//	//m_strAxis[7] = QString::number(m_fIr / m_fIe, 'f', 3);
	//}
}