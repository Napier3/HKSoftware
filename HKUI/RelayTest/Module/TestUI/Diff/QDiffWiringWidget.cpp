#include "QDiffWiringWidget.h"
#include <qmath.h>

QDiffWiringWidget::QDiffWiringWidget(QWidget *parent)
	: QWidget(parent)
{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_nDisType = 0;
	m_fKph=0;
	m_fKpm = 0;
	m_fKpl=0;
	m_fKjxl=0;
	m_fKjxh=0;
	m_fIe = 0;
	m_fIh = 0;
	m_fIl = 0;
	m_fId = 0;
	m_fIr = 0;
	m_pCommonParaTest = NULL;
	m_nWindSide = 0;	
	m_nWindH = 0;		
	m_nWindM = 0;		
	m_nWindL = 0;		
	m_nPhase = 0;		
	m_bMinAxis = 0;		
	m_nInSel = 0;		
	m_fIbase = 0;		
	m_fIdiff = 0;		
	m_fIbias = 0;		
	m_nSearchMode = 0;
	m_nAngleMode = 0;
	m_nIbiasCal = 0;
	m_fFactor1 = 0;
	m_fFactor2 = 0;
	m_nConnectMode = 0;
	m_bCTStarPoint = 0;
	m_nJXFactor = 0;
	m_fSN = 0; 
	m_fHUn = 0; 
	m_fMUn = 0; 
	m_fLUn = 0; 
	m_fCTPh = 0; 
	m_fCTSh = 0;
	m_fCTPm = 0;
	m_fCTSm = 0;
	m_fCTPl = 0;
	m_fCTSl = 0;
	initTableData();
	initTable();
}

QDiffWiringWidget::~QDiffWiringWidget()
{

}

void QDiffWiringWidget::setCommonData(CExBaseList* pCommonParaTest)
{
	ASSERT(pCommonParaTest != NULL);

	m_pCommonParaTest = pCommonParaTest;
	POS pos = m_pCommonParaTest->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pCommonParaTest->GetNext(pos);
		SetValueToPage(pData);
	}

	m_oDiffCalTool.Init();

	m_oDiffCalTool.InitParas6I(m_nInSel, m_fIbase, m_nSearchMode,m_bMinAxis, m_nAngleMode, m_nIbiasCal,
		m_nWindH, m_nWindM, m_nWindL, m_nWindSide,m_fFactor1, m_fFactor2, m_nConnectMode,
		m_nPhase, m_bCTStarPoint,m_nJXFactor);

	m_oDiffCalTool.InitParas_AutoCalBalanceFactors(m_fSN, m_fHUn, m_fMUn,
		m_fLUn, m_fCTPh, m_fCTSh, m_fCTPm, m_fCTSm, m_fCTPl, m_fCTSl);

}
void QDiffWiringWidget::SetValueToPage(CSttMacroTestParaData *pData)
{

	if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET)
	{
		m_fKph = pData->m_strValue.toFloat();       //高压侧差动平衡系数
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET)
	{
		m_fKpm = pData->m_strValue.toFloat();   	//中压侧差动平衡系数
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET)
	{
		m_fKpl = pData->m_strValue.toFloat();		//低压侧差动平衡系数
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND)
	{
		m_nWindSide = pData->m_strValue.toInt();	//测试绕组	0-高-低  1-高-中    2-中-低    2	用以计算KPH、KPL
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH)
	{
		m_nWindH = pData->m_strValue.toInt();		//高压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM)
	{
		m_nWindM = pData->m_strValue.toInt();		//中压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL)
	{
		m_nWindL = pData->m_strValue.toInt();		//低压侧绕组接线形式 0-Y 1-△ 1 用以计算KPL
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE)
	{
		m_nPhase = pData->m_strValue.toInt();		//故障相别
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_MINAXIS)
	{
		m_bMinAxis = pData->m_strValue.toInt();	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_INSEL)
	{
		m_nInSel = pData->m_strValue.toInt();	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流	平台模板没有，恒为0 用以计算INOM
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_INSET)
	{
		m_fIbase = pData->m_strValue.toFloat();	//基准电流设定值
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING)
	{
		m_fIdiff = pData->m_strValue.toFloat();	//差动电流
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID)
	{
		m_fIdiff = pData->m_strValue.toFloat();	//差动电流 两个id不一样
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR)
	{
		m_fIbias = pData->m_strValue.toFloat();	//制动电流 谐波没有制动电流，使用默认值0
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE)
	{
		m_nSearchMode = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE)
	{
		m_nAngleMode = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION)
	{
		m_nIbiasCal = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K)
	{
		m_fFactor1 = pData->m_strValue.toFloat();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K2)
	{
		m_fFactor2 = pData->m_strValue.toFloat();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE)
	{
		m_nConnectMode = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT)
	{
		m_bCTStarPoint = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR)
	{
		m_nJXFactor = pData->m_strValue.toInt();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SN)
	{
		m_fSN = pData->m_strValue.toFloat();				//变压器额定容量(MVA)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HUN)
	{
		m_fHUn = pData->m_strValue.toFloat();				//高压侧额定电压(kV)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_MUN)
	{
		m_fMUn = pData->m_strValue.toFloat();				//中压侧额定电压(kV)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_LUN)
	{
		m_fLUn = pData->m_strValue.toFloat();				//低压侧额定电压(kV)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH)
	{
		m_fCTPh = pData->m_strValue.toFloat();				//高压侧CT一次值(A)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH)
	{
		m_fCTSh = pData->m_strValue.toFloat();			//高压侧CT二次值(A)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM)
	{
		m_fCTPm = pData->m_strValue.toFloat();				//中压侧CT一次值(A)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM)
	{
		m_fCTSm = pData->m_strValue.toFloat();				//中压侧CT二次值(A)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL)
	{
		m_fCTPl = pData->m_strValue.toFloat();			//低压侧CT一次值(A)
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL)
	{
		m_fCTSl = pData->m_strValue.toFloat();				//低压侧CT二次值(A)
	}
}

void QDiffWiringWidget::initTable()
{
	m_TabelData = new QTableWidget(this);
	m_TabelData->setStyleSheet(QString::fromUtf8("background-color: rgb(167,183,181);"));
	QHeaderView* pTop = m_TabelData->horizontalHeader();
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	pTop->setSectionsClickable(false);
	pTop->setSectionsMovable(false);
#else
	pTop->setClickable(false);
	pTop->setMovable(false);
#endif

	QHeaderView* pLeft = m_TabelData->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	m_TabelData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	m_TabelData->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

	m_TabelData->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TabelData->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TabelData->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_TabelData->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(171,167,176);}"); //设置表头背景色
	m_TabelData->setColumnCount(5);

	QFontMetrics fontMetrics = QFontMetrics(font());

	int nLabelWidth1 = fontMetrics.width(/*Ⅰ侧平衡系数*/g_sLangTxt_Diff_SglSideBalCoeff) + 10;
	int nLabelWidth2 = fontMetrics.width(tr("900.000")) + 80;
	int nLabelWidth3 = fontMetrics.width(/*tr("单位")*/g_sLangTxt_Unit) + 20;

	QStringList headers;
	headers <</*tr("名称")*/g_sLangTxt_Name <</*tr("幅值")*/g_sLangTxt_Native_Amplitude <</*tr("单位")*/g_sLangTxt_Unit 
		<< /*标幺值*/g_sLangTxt_Diff_PerUnitVal <</*接线系数*/g_sLangTxt_Diff_WiringCoeff;
	m_TabelData->setHorizontalHeaderLabels(headers);
	m_TabelData->setColumnWidth(0,nLabelWidth1);
	m_TabelData->setColumnWidth(1,nLabelWidth2);
	m_TabelData->setColumnWidth(2,nLabelWidth3);
	m_TabelData->setColumnWidth(3,nLabelWidth2);
	m_TabelData->setColumnWidth(4,70);

	QStringList list;
	QStringList listUnit;
	if(m_nDisType == 0)
	{
		list << /*Ⅰ侧平衡系数*/g_sLangTxt_Diff_SglSideBalCoeff << /*Ⅱ侧平衡系数*/g_sLangTxt_Diff_TwoSideBalCoeff << /*Ⅲ侧平衡系数*/g_sLangTxt_Diff_ThreeSideBalCoeff << /*基准电流*/ g_sLangTxt_Diff_RefCurrentSel << tr("I1") << tr("I2") << tr("Ir") << tr("Id");
		listUnit<<tr(" ")<<tr(" ")<<tr(" ")<<tr("A")<<tr("A")<<tr("A")<<tr("A")<<tr("A");
	}
	else
	{
		list << /*Ⅰ侧平衡系数*/g_sLangTxt_Diff_SglSideBalCoeff << /*Ⅱ侧平衡系数*/g_sLangTxt_Diff_TwoSideBalCoeff << /*Ⅲ侧平衡系数*/g_sLangTxt_Diff_ThreeSideBalCoeff << /*基准电流*/ g_sLangTxt_Diff_RefCurrentSel << tr("I1") << tr("I2") << tr("Ir") << tr("Kxb");
		listUnit<<tr(" ")<<tr(" ")<<tr(" ")<<tr("A")<<tr("A")<<tr("A")<<tr("A")<<tr(" ");
	}
	
	for (int i=0; i< 8;i++)
	{
		QTableWidgetItem *item1 = new QTableWidgetItem(list.at(i));
		item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item2 = new QTableWidgetItem("0.000");
		item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item3 = new QTableWidgetItem(listUnit.at(i));
		item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item4 = new QTableWidgetItem("");
		item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item5 = new QTableWidgetItem("");
		item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		int rowCount = m_TabelData->rowCount();
		m_TabelData->insertRow(rowCount);
		m_TabelData->setRowHeight(rowCount,15);
		m_TabelData->setItem(rowCount, 0, item1);   	
		m_TabelData->setItem(rowCount, 1, item2);  
		m_TabelData->setItem(rowCount, 2, item3); 
		m_TabelData->setItem(rowCount, 3, item4);
		m_TabelData->setItem(rowCount, 4, item5);
	}
}

void QDiffWiringWidget::resizeEvent(QResizeEvent* e)
{
	repaint();
}

void QDiffWiringWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);
	drawBackground(&painter);
	drawWiring(&painter);

	QRect rectTop(rect().left(),rect().top(),rect().width(),rect().height()/2);
	QRect rectButtom(rect().left(),rectTop.bottom(),rect().width(),rect().height()/2);
	m_TabelData->setGeometry(rectButtom);
	updateTableRowHightSize(rectButtom.height());
}

void QDiffWiringWidget::drawWiring(QPainter *painter)
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
	float fVMargin = 15;
	float fRectHeight = fontMetrics.height()*3 + 5;
	
	float fRectWidth = rect().width()-2*fHMargin;
	float fpointsWidth = (fRectWidth-20)/8;
	float fpointsWidth2 = (fRectWidth-20)/3;
	float fCircleR = 4;
	QPointF testDevicepoints[8];
	QPointF protectDevicepoints1[8];
	QPointF protectDevicepoints2[4];

	QStringList nameList1;
	QStringList nameList2;
	QStringList nameList3;
	nameList1<<tr("A")<<tr("B")<<tr("C")<<tr("N")<<tr("a")<<tr("b")<<tr("c")<<tr("n");
	nameList2<<tr("IA")<<tr("IB")<<tr("IC")<<tr("IN")<<tr("Ia'")<<tr("Ib'")<<tr("Ic'")<<tr("In'");
	nameList3<<tr("IA")<<tr("IB")<<tr("IC")<<tr("IN");
	QString strHSide = /*   高压侧   */ tr("   ") + g_sLangTxt_Diff_HighVoltSide + tr("   ");
	QString strMSide = /*   中压侧   */	tr("   ") + g_sLangTxt_Diff_MedVoltSide + tr("   ") ;
	QString strLSide = /*   低压侧   */ tr("   ") + g_sLangTxt_Diff_LowVoltSide + tr("   ");
	QString strDiff = /*差动保护电流端子*/ g_sLangTxt_Diff_DiffProtCurrTerm;
	QString strProtect = /*继电保护测试仪*/g_sLangTxt_Diff_RelayTest;

	for(int i = 0;i < 8;i++)
	{
		if(i < 4)
		{
			testDevicepoints[i].setX(rect().left() + fHMargin + 10 + i*fpointsWidth);
			testDevicepoints[i].setY(rect().top() + fVMargin + fRectHeight - 5 - fCircleR); 
			protectDevicepoints1[i].setX(rect().left() + fHMargin + 10 + i*fpointsWidth);
			protectDevicepoints1[i].setY(rect().height()/2-fVMargin-fRectHeight + 5 + fCircleR);
		}
		else
		{
			testDevicepoints[i].setX(rect().left() + fHMargin + 10 + (i + 1)*fpointsWidth);
			testDevicepoints[i].setY(rect().top() + fVMargin + fRectHeight - 5 - fCircleR); 
			protectDevicepoints1[i].setX(rect().left() + fHMargin + 10 + (i + 1)*fpointsWidth);
			protectDevicepoints1[i].setY(rect().height()/2-fVMargin-fRectHeight + 5 + fCircleR);
		}
	}

	for(int i = 0;i < 4;i++)
	{
		protectDevicepoints2[i].setX(rect().left() + fHMargin + 10 + i*fpointsWidth2);
		protectDevicepoints2[i].setY(rect().height()/2-fVMargin-fRectHeight + 5 + fCircleR);
	}

	int nLabelHeight = fontMetrics.height() + 5;
	QRectF rect1(testDevicepoints[0].x(),rect().top()+fVMargin+5,testDevicepoints[3].x() - testDevicepoints[0].x(),nLabelHeight);
	QRectF rect2(testDevicepoints[4].x(),rect().top()+fVMargin+5,testDevicepoints[7].x() - testDevicepoints[4].x(),nLabelHeight);
	QRectF rect4(testDevicepoints[0].x(),rect().top()+fVMargin+5,testDevicepoints[7].x() - testDevicepoints[0].x(),nLabelHeight);
	QRectF rect3(rect().left() + fHMargin, rect().height() / 2 - fVMargin - 5 - fontMetrics.height(), fRectWidth, nLabelHeight);

	//绘制上方矩形
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter->setPen(pen);
	painter->setBrush(Qt::gray);
	painter->drawRect(rect().left()+fHMargin,rect().top()+fVMargin,fRectWidth,fRectHeight);
	if(m_nDisType == 0)
	{
		if(m_nWindSide == TestWind_HightToLow)		//高-低
		{
			painter->drawText(rect1,Qt::AlignCenter,strHSide);
			painter->drawText(rect2,Qt::AlignCenter,strLSide);
		}
		else if(m_nWindSide == TestWind_HightToMin)	//高-中
		{
			painter->drawText(rect1,Qt::AlignCenter,strHSide);
			painter->drawText(rect2,Qt::AlignCenter,strMSide);
		}
		else if(m_nWindSide == TestWind_MinToLow)	//中-低
		{
			painter->drawText(rect1,Qt::AlignCenter,strMSide);
			painter->drawText(rect2,Qt::AlignCenter,strLSide);
		}
	}
	else
	{
		painter->drawText(rect4,Qt::AlignCenter,strDiff);
	}
	
	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::white);
	QList<QColor> colors;
	colors<<QColor(Qt::yellow)<<QColor(Qt::green)<<QColor(Qt::red)<<QColor(Qt::blue);
	int nWind1PointCount = 0;
	int nWind2PointCount = 0;
	if(m_nWindSide == TestWind_HightToLow)
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
	else if(m_nWindSide == TestWind_HightToMin)
	{
		if(m_nWindH == StarType)
		{
			nWind1PointCount = 4;
		}
		else
		{
			nWind1PointCount = 3;
		}

		if(m_nWindM == StarType)
		{
			nWind2PointCount = 4;
		}
		else
		{
			nWind2PointCount = 3;
		}
	}
	else if(m_nWindSide == TestWind_MinToLow)
	{
		if(m_nWindM == StarType)
		{
			nWind1PointCount = 4;
		}
		else
		{
			nWind1PointCount = 3;
		}

		if(m_nWindL == StarType)
		{
			nWind2PointCount = 4;
		}
		else
		{
			nWind2PointCount = 3;
		}
	}

	if(m_nDisType == 0)
	{
		for(int i = 0;i < 8;i++)
		{
			drawCTPoint(painter,testDevicepoints[i],nameList1.at(i),colors.at(i%4),false);
		}
	}
	else
	{
		for(int i = 0;i < 8;i++)
		{
			drawCTPoint(painter,testDevicepoints[i],nameList1.at(i),colors.at(i%4),false);
		}
	}

	//绘制下方矩形
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter->setPen(pen);
	painter->setBrush(Qt::gray);
	painter->drawRect(rect().left()+fHMargin,rect().height()/2-fVMargin-fRectHeight,fRectWidth,fRectHeight);

	painter->setFont(font);
	painter->drawText(rect3,Qt::AlignCenter,strProtect);

	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::white);
	
	if(m_nDisType == 0)
	{
		for(int i = 0;i < 8;i++)
		{
			drawCTPoint(painter,protectDevicepoints1[i],nameList2.at(i),colors.at(i%4),true);
		}
	}
	else
	{
		//谐波的时候保护测只有四个接线点
		for(int i = 0;i < 4;i++)
		{
			drawCTPoint(painter,protectDevicepoints2[i],nameList3.at(i),colors.at(i%4),true);
		}
	}

	//绘制连接线
	if(m_nDisType == 0)
	{
		for(int i = 0;i < nWind1PointCount;i++)
		{
			drawLine(painter,testDevicepoints[i],protectDevicepoints1[i],colors.at(i%4));
		}

		for(int i = 0;i < nWind2PointCount;i++)
		{
			drawLine(painter,testDevicepoints[i+4],protectDevicepoints1[i+4],colors.at(i%4));
		}
	}
	else
	{
		//TestPhasor_type{APhase = 0,BPhase,CPhase,ABCPhase,ABPhase,BCPhase,CAPhase};
		switch(m_nPhase)
		{
            case /*TestPhasor_type::*/APhase: //A
				drawLine(painter,testDevicepoints[0],protectDevicepoints2[0],colors.at(0));
				break;
            case /*TestPhasor_type::*/BPhase: //B
				drawLine(painter,testDevicepoints[1],protectDevicepoints2[1],colors.at(1));
				break;
            case /*TestPhasor_type::*/CPhase: //C
				drawLine(painter,testDevicepoints[2],protectDevicepoints2[2],colors.at(2));
				break;
            case /*TestPhasor_type::*/ABCPhase: //ABC
				drawLine(painter,testDevicepoints[0],protectDevicepoints2[0],colors.at(0));
				drawLine(painter,testDevicepoints[1],protectDevicepoints2[1],colors.at(1));
				drawLine(painter,testDevicepoints[2],protectDevicepoints2[2],colors.at(2));
				break;
            case /*TestPhasor_type::*/ABPhase:
				drawLine(painter,testDevicepoints[0],protectDevicepoints2[0],colors.at(0));
				drawLine(painter,testDevicepoints[1],protectDevicepoints2[1],colors.at(1));
				break;
            case /*TestPhasor_type::*/BCPhase:
				drawLine(painter,testDevicepoints[1],protectDevicepoints2[1],colors.at(1));
				drawLine(painter,testDevicepoints[2],protectDevicepoints2[2],colors.at(2));
				break;
            case /*TestPhasor_type::*/CAPhase:
				drawLine(painter,testDevicepoints[2],protectDevicepoints2[2],colors.at(2));
				drawLine(painter,testDevicepoints[0],protectDevicepoints2[0],colors.at(0));
				break;
			default:
				break;
		}
		drawLine(painter,testDevicepoints[3],protectDevicepoints2[3],colors.at(3));
	}
}

void QDiffWiringWidget::drawCTPoint(QPainter *painter,QPointF pointf,QString strText,QColor color,bool bBellow)
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

	painter->drawEllipse(pointf,5,5);
	QFontMetrics fontMetrics = QFontMetrics(font);
	int nHeight = fontMetrics.height();

	QRectF rect;
	if(bBellow)
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

	painter->drawText(rect,Qt::AlignCenter,strText);
}

void QDiffWiringWidget::drawLine(QPainter *painter,QPointF point1,QPointF point2,QColor color)
{
	QPen pen;
	pen.setWidth(2);
	pen.setColor(color);
	QPointF points[4];
	points[0] = point1;
	points[1].setX(point1.x());
	points[1].setY((point1.y() + point2.y())/2);
	points[2].setX(point2.x());
	points[2].setY((point1.y() + point2.y())/2);
	points[3] = point2;

	painter->setPen(pen);
	painter->drawPolyline(points,4);
}

void QDiffWiringWidget::drawBackground(QPainter *painter)
{
	QRect rectTop(rect().left(),rect().top(),rect().width(),rect().height()/2);
	QRect rectButtom(rect().left(),rectTop.bottom(),rect().width(),rect().height()/2);
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

void QDiffWiringWidget::updateTableRowHightSize(int height)
{
	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelHeight = fontMetrics.height() + 10;
	m_TabelData->horizontalHeader()->setFixedHeight(nLabelHeight);
	int H = height-30;
	for (int i=0; i< m_TabelData->rowCount();i++)
	{
		m_TabelData->setRowHeight(i,H/m_TabelData->rowCount());
	}
}

void QDiffWiringWidget::updateTable(CString strMacroID)
{
	if (strMacroID == "")
	{
		return;
	}

	QStringList list;
	QStringList listUnit;
	QStringList headers;

	if ((strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE)  || (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME))
	{
		list << /*Ⅰ侧平衡系数*/g_sLangTxt_Diff_SglSideBalCoeff << /*Ⅱ侧平衡系数*/g_sLangTxt_Diff_TwoSideBalCoeff << /*Ⅲ侧平衡系数*/g_sLangTxt_Diff_ThreeSideBalCoeff << /*基准电流*/ g_sLangTxt_Diff_RefCurrentSel << tr("I1") << tr("I2") << tr("Ir") << tr("Id");

		list << /*Ⅰ侧平衡系数*/g_sLangTxt_Diff_SglSideBalCoeff << /*Ⅱ侧平衡系数*/g_sLangTxt_Diff_TwoSideBalCoeff << /*Ⅲ侧平衡系数*/g_sLangTxt_Diff_ThreeSideBalCoeff
			<<	/*基准电流*/ g_sLangTxt_Diff_RefCurrentSel << tr("I1") << tr("I2") << tr("Id") << tr("Ir");
		listUnit<<tr(" ")<<tr(" ")<<tr(" ")<<tr("A")<<tr("A")<<tr("A")<<tr("A")<<tr("A");
		headers <</*tr("名称")*/g_sLangTxt_Name <</*tr("幅值")*/g_sLangTxt_Native_Amplitude <</*tr("单位")*/g_sLangTxt_Unit << /*标幺值*/g_sLangTxt_Diff_PerUnitVal <</*接线系数*/g_sLangTxt_Diff_WiringCoeff;
		m_nDisType = 0;
	}
	else if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
	{
		list << /*Ⅰ侧平衡系数*/g_sLangTxt_Diff_SglSideBalCoeff << /*Ⅱ侧平衡系数*/g_sLangTxt_Diff_TwoSideBalCoeff << /*Ⅲ侧平衡系数*/g_sLangTxt_Diff_ThreeSideBalCoeff
			<< /*基准电流*/ g_sLangTxt_Diff_RefCurrentSel << tr("I1") << tr("I2") << tr("Id") << tr("Kxb");
		listUnit<<tr(" ")<<tr(" ")<<tr(" ")<<tr("A")<<tr("A")<<tr("A")<<tr("A")<<tr(" ");
		headers <</*tr("名称")*/g_sLangTxt_Name <</*tr("幅值")*/g_sLangTxt_Native_Amplitude <</*tr("单位")*/g_sLangTxt_Unit << /*标幺值*/g_sLangTxt_Diff_PerUnitVal << tr(" ");
		m_nDisType = 1;
	}

	initTableData();
//	calCoefs(pParaTest);

	getTableRealData(strMacroID);

	m_TabelData->setHorizontalHeaderLabels(headers);
	int  colN = m_TabelData->columnCount();
	for(int i = 0;i < 8;i++)
	{
		m_TabelData->item(i,0)->setText(list.at(i));
		m_TabelData->item(i,1)->setText(m_strBanlanceCoefs[i]);
		m_TabelData->item(i,2)->setText(listUnit.at(i));
		m_TabelData->item(i,3)->setText(m_strAxis[i]);
		m_TabelData->item(i,4)->setText(m_strWiringCoefs[i]);
	}

	repaint();
}

void QDiffWiringWidget::updateTableData(CString strMacroID)
{
	if (strMacroID == "")
	{
		return;
	}

	initTableData();
	getTableRealData(strMacroID);

	int colN = m_TabelData->columnCount();
	for(int i = 0;i < 8;i++)
	{
		m_TabelData->item(i,1)->setText(m_strBanlanceCoefs[i]);
		m_TabelData->item(i,3)->setText(m_strAxis[i]);
		m_TabelData->item(i,4)->setText(m_strWiringCoefs[i]);
	}

	repaint();
}

void QDiffWiringWidget::initTableData()   //把表格数值都初始化为零
{
	for(int i = 0;i < 8;i++)
	{
		m_strBanlanceCoefs[i] = tr("  ");
		m_strAxis[i] = tr("  ");
		m_strWiringCoefs[i] = tr("  ");
	}
}

void QDiffWiringWidget::getTableRealData(CString strMacroID)
{
	if (strMacroID == "")
	{
		return;
	}

	//计算I1和I2（6路电流）
	m_oDiffCalTool.CurrentCal(&m_fIdiff, m_fIbias);

	//取得接线系数
	m_oDiffCalTool.GetKjx(m_fKjxh, m_fKjxl);

	if(m_nWindSide == TestWind_HightToLow)
	{
		m_strBanlanceCoefs[0] = QString::number(m_fKph, 'f', 3);
		m_strBanlanceCoefs[2] = QString::number(m_fKpl, 'f', 3);
		if (strMacroID != STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
		{
			m_strWiringCoefs[0] = QString::number(m_fKjxh, 'f', 3);
			m_strWiringCoefs[2] = QString::number(m_fKjxl, 'f', 3);
		}
	}
	else if(m_nWindSide == TestWind_HightToMin)
	{
		m_strBanlanceCoefs[0] = QString::number(m_fKph, 'f', 3);
		m_strBanlanceCoefs[1] = QString::number(m_fKpm, 'f', 3);
		if (strMacroID != STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
		{
			m_strWiringCoefs[0] = QString::number(m_fKjxh, 'f', 3);
			m_strWiringCoefs[1] = QString::number(m_fKjxl, 'f', 3);
		}
	}
	else if(m_nWindSide == TestWind_MinToLow)
	{
		m_strBanlanceCoefs[1] = QString::number(m_fKpm, 'f', 3);
		m_strBanlanceCoefs[2] = QString::number(m_fKpl, 'f', 3);
		if (strMacroID != STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
		{
			m_strWiringCoefs[1] = QString::number(m_fKjxh, 'f', 3);
			m_strWiringCoefs[2] = QString::number(m_fKjxl, 'f', 3);
		}
	}

	//取得基准电流
	if (m_bMinAxis == MarkValue_Type && m_nInSel == SettingValue)
	{
		m_fIe = m_fIbase;
	}
	else
	{
		m_oDiffCalTool.GetIet(m_fIe);
	}

	m_strBanlanceCoefs[3] = QString::number(m_fIe, 'f', 3);

	//取得I1、I2
	ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

	switch(m_nPhase)
	{
    case /*TestPhasor_type::*/APhase:
		m_fIh = pChCurrents[0].famptitude;
		m_fIl = pChCurrents[3].famptitude;
		break;
    case /*TestPhasor_type::*/BPhase:
		m_fIh = pChCurrents[1].famptitude;
		m_fIl = pChCurrents[4].famptitude;
		break;
    case /*TestPhasor_type::*/CPhase:
		m_fIh = pChCurrents[2].famptitude;
		m_fIl = pChCurrents[5].famptitude;
		break;
    case /*TestPhasor_type::*/ABCPhase:
    case /*TestPhasor_type::*/ABPhase:
    case /*TestPhasor_type::*/BCPhase:
    case /*TestPhasor_type::*/CAPhase:
		m_fIh = pChCurrents[0].famptitude;
		m_fIl = pChCurrents[3].famptitude;
		break;
	default:
		break;
	}

	//取得Id、Ir
	//if (strcmp(strMacroID,STT_MACRO_ID_PsuDiffTCurrTest)==0 || strcmp(pParaTest->strMacroID,STT_MACRO_ID_PsuDiffQuickTest)==0)
	//{
	//	m_fId = pParaTest->m_oDiffCurrParas.m_fIdiff;
	//	m_fIr = pParaTest->m_oDiffCurrParas.m_fIbias;
	//}
	if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE)
	{
		m_fId = m_fIdiff;
		m_fIr = m_fIbias;
	}
	else if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
	{
		m_fId = m_fIdiff;
		m_fIr = 0;
	}
	else if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME)
	{
		m_fId = m_fIdiff;
		m_fIr = m_fIbias;
	}

	if(m_fIh < 0 || m_fIh > 100)
	{
		m_strBanlanceCoefs[4] = tr("——");
	}
	else
	{
		m_strBanlanceCoefs[4] = QString::number(m_fIh, 'f', 3);
	}

	if(m_fIl < 0 || m_fIl > 100)
	{
		m_strBanlanceCoefs[5] = tr("——");
	}
	else
	{
		m_strBanlanceCoefs[5] = QString::number(m_fIl, 'f', 3);
	}
	
	m_strBanlanceCoefs[6] = QString::number(m_fId, 'f', 3);
	m_strBanlanceCoefs[7] = QString::number(m_fIr, 'f', 3);

	if (m_strBanlanceCoefs[4] == tr("——"))
	{
		m_strAxis[4] = tr("——");
	}
	else
	{
		m_strAxis[4] = QString::number(m_fIh/m_fIe, 'f', 3);
	}
	
	if (m_strBanlanceCoefs[5] == tr("——"))
	{
		m_strAxis[5] = tr("——");
	}
	else
	{
		m_strAxis[5] = QString::number(m_fIl/m_fIe, 'f', 3);
	}

	if (strMacroID == STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM)
	{
		m_strAxis[6] = QString::number(m_fId/m_fIe, 'f', 3);
		m_strAxis[7] = tr(" ");
	}
	else
	{
		m_strAxis[6] = QString::number(m_fId/m_fIe, 'f', 3);
		m_strAxis[7] = QString::number(m_fIr/m_fIe, 'f', 3);
	} 
}
void QDiffWiringWidget::GetCurrentCal(double *dId, double fIr)
{
	float fId = *dId;
	m_oDiffCalTool.CurrentCal(&fId, fIr);
	*dId = fId;
}
