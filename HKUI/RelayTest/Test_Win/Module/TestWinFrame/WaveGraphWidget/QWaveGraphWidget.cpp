#include "QWaveGraphWidget.h"
#include <QResizeEvent>

#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/ReplayTest/BigComtradeTransPlay.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

#include <QCoreApplication>
#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>

QWaveGraphWidget::QWaveGraphWidget(QWidget *parent) :
    QWidget(parent)
{
	m_pReplayRecordTest = new CRecordTest();
	CRtVariables* pVariables = new CRtVariables();
	m_pReplayRecordTest->m_pVariables = pVariables;
	pVariables->SetParent(m_pReplayRecordTest);
	m_pReplayRecordTest->AddTail(pVariables);
	g_theRecordApp.AddNewChild(m_pReplayRecordTest);
	g_pCurrRecordTest = m_pReplayRecordTest;
	m_dTimeA = -1.0f;
	m_dTimeB = -1.0f;

	m_pDC = new CDC(this);
	m_pWndWaveGraph = new CWnd_WaveGraph();
	m_pWndWaveGraph->m_pWaveGraph = this;
	m_bIsCreateRecordDraw = FALSE;

	initPlot();

 	SetParentWnd(m_pWndWaveGraph);
 	UICreate(m_pWndWaveGraph);
	m_nTotalPoints = 10000;
	m_bMoveCursor = FALSE;

	 AddDrawBtns();

// 	 //禁止整个绘图区重绘,减少闪烁
// 	 setAttribute(Qt::WA_OpaquePaintEvent);


}

QWaveGraphWidget::~QWaveGraphWidget()
{
	//delete m_pReplayRecordTest;

	//lijunqing : 必须首先释放与窗口相关的绘图对象，否则在窗口销毁之后再释放，就会导致系统崩溃
	m_oDrawMemDC->Release();  

	m_pRcdComtradeFile = NULL;
	m_pWndWaveGraph->DestroyWindow();
	delete m_pWndWaveGraph;
    delete m_pDC;
}

void QWaveGraphWidget::UpdateWaveDraws()
{
	CDC oDC(this);
	oDC.begin(this);
	CViewAnalyse::OnDraw(&oDC);

	if (!g_theBigComtradeTransPlay->HasComtradeDataNeedDraw())
	{
		long y = height() / 2;
		long x = width() / 2;
		CRect rc;
		rc.left = x - 100;
		rc.top = y-10;
		rc.bottom = y + 10;
		rc.right = x + 100;

		oDC.SetTextColor(RGB(255, 255, 255));
		oDC.DrawText(/*"请打开COMTRADE波形文件"*/g_sLangTxt_State_POpenCFile, rc, DT_VCENTER|DT_LEFT);

		UpdateButtonEnable(FALSE);
	}
	UpdateButtonEnable(TRUE);

	oDC.end();
	updateGeometry();//zhouhj 20211104 增加用于解决移动垂直线重影的问题
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QWaveGraphWidget::UpdateWaveDraws()"));
}

void QWaveGraphWidget::paintEvent(QPaintEvent *event)
{
	UpdateWaveDraws();
	if(m_bInsertWaveformBackColor)
	{
		UpdateInsertWaveBackColor(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd);
	}
	if(m_bDeleteWaveformBackColor)
	{
		UpdateDeleteWaveBackColor(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd);
	}
}

void QWaveGraphWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QSize oCurSize = pReSizeEvent->size();
	long nX = oCurSize.width();
	long nY = oCurSize.height();

	if (nX<10)
	{
		nX = 400;
	}

	if (nY<10)
	{
		nY = 400;
	}

	CreateRecordDraw(nX, nY);

	UpdateDrawBtns();
}


void QWaveGraphWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentX = event->pos().x();

		if(nCurrentX < MrDraw::g_snNameandAxisRectWidth)//2023-11-13 wuxinyi 修改双击波形图之外，改变位置的中断问题
		{
			return;
		}

		if (event->button() == Qt::LeftButton)
		{
			m_pTimeCursorDraw->SetCursorPosition(nCurrentX,USETIMECURSORA);
		}
		else if (event->button() == Qt::RightButton)
		{
			m_pTimeCursorDraw->SetCursorPosition(nCurrentX,USETIMECURSORB);
		}
	}
	
	//mousePressEvent(event);              
}

void QWaveGraphWidget::SendUpdateTwoCursorTimeValues(BOOL bCompare)
{
	double dTimeA = 0, dTimeB = 0; 
	GetTwoCursorTimeValues(dTimeA,dTimeB);

	if ((bCompare)&&(abs(m_dTimeA-dTimeA)<0.0001)&&(abs(m_dTimeB-dTimeB)<0.0001))
	{
		return;
	}

	m_dTimeA = dTimeA;
	m_dTimeB = dTimeB;

	double dTimeDiff = fabs((dTimeB-dTimeA) * 1000);//秒转换成毫秒

	//点号
	long nAPointCount = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.GetCurrPosByTime(dTimeA);
	long nBPointCount = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.GetCurrPosByTime(dTimeB);
	long nPointDiff = labs(nBPointCount-nAPointCount);

	//修改T1/T2
	CString strTime = FormatTime(dTimeA);
	QString strData = QString("T1光标：[%1]/第%2个点，时差 = %3ms").arg(strTime).arg(nAPointCount).arg(QString::number(dTimeDiff, 'f', 3));
	m_pT1Lable->setText(strData);

	strTime = FormatTime(dTimeB);
	strData = QString("T2光标：[%1]/第%2个点，点差 = %3").arg(strTime).arg(nBPointCount).arg(nPointDiff);
	m_pT2Lable->setText(strData);

	emit sig_UpdateTwoCursorTimeValues(dTimeA,dTimeB);
}

void QWaveGraphWidget::UpdateButtonEnable(BOOL bState)
{
	m_pBtnReset->setEnabled(bState);
	m_pBtnZoomOutTime->setEnabled(bState);
	m_pBtnZoomInTime->setEnabled(bState);
	m_pBtnZoomOutChan->setEnabled(bState);
	m_pBtnZoomInChan->setEnabled(bState);
	m_pBtnMoveLeft->setEnabled(bState);
	m_pBtnMoveRight->setEnabled(bState);
}

void QWaveGraphWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_bIsCreateRecordDraw)
	{
		CPoint oPoint(event->pos().x(),event->pos().y());
		XOnMouseMove(0,oPoint);
		event->ignore();
// 		SendUpdateTwoCursorTimeValues(TRUE);
		ChangeTimeCursorDrawPos(m_dTimeA,m_dTimeB);
	}
	else
		QWidget::mouseMoveEvent(event);

	m_bMoveCursor = true;
//	QWidget::mouseMoveEvent(event);
}

void QWaveGraphWidget::mousePressEvent(QMouseEvent *event)
{
	if (!m_bIsCreateRecordDraw)
	{
		CPoint oPoint(event->pos().x(),event->pos().y());
		//m_pCharacterDrawView->SetAxisInstruct_Point(oPoint);
		XOnLButtonDown(0, oPoint);
		QWidget::mousePressEvent(event);
		SendUpdateTwoCursorTimeValues(TRUE);
	}
	else
	{
		QWidget::mousePressEvent(event);
	}
	
}

void QWaveGraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (!m_bIsCreateRecordDraw)
	{
		CPoint oPoint(event->pos().x(),event->pos().y());
		XOnLButtonUp(0, oPoint);
		QWidget::mouseReleaseEvent(event);
		
		if(m_bMoveCursor)
		{
			//光标改变
			ChangeTimeCursorDrawPos(m_dTimeA,m_dTimeB);
			m_bMoveCursor = false;
		}
		else
		{
		SendUpdateTwoCursorTimeValues(TRUE);
		}


	} 
	else
	{
		QWidget::mouseReleaseEvent(event);
	}
	
}

void QWaveGraphWidget::wheelEvent(QWheelEvent *event)
{
	double dData = event->delta();

// 	if (dData>0)
// 	{
// 		m_pCharacterDrawView->UI_ZoomIn();
// 	} 
// 	else
// 	{
// 		m_pCharacterDrawView->UI_ZoomOut();
// 	}

	event->ignore();
}

void QWaveGraphWidget::initPlot()
{
	m_nAnalogChanAmount = 0;
	ClearSelect();
	m_pReplayRecordTest->m_pVariables->DeleteAll();
}

void QWaveGraphWidget::slot_UpdateDrawWaveGraph()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QWaveGraphWidget::slot_UpdateDrawWaveGraph()"));
	DrawAnalyse();
}


void QWaveGraphWidget::RecordDraw()
{

}

void QWaveGraphWidget::CreateRecordDraw(long cx, long cy)
{
// 	if (! g_theBigComtradeTransPlay->HasComtradeDataNeedDraw())
// 	{//如果没有波形数据，则返回
// 		return;
// 	}

	CViewAnalyse::OnSizeEx(0, cx, cy);
	DrawAnalyse();
}


void QWaveGraphWidget::CreateRecordDrawByComtrade()
{
	if (! g_theBigComtradeTransPlay->HasComtradeDataNeedDraw())
	{//如果没有波形数据，则返回
		return;
	}

	m_bIsCreateRecordDraw = TRUE;
	initPlot();
	
	if (g_theBigComtradeTransPlay->m_bDrawSrcComtrade)
	{
		m_pRcdComtradeFile = g_theBigComtradeTransPlay->GetSrcComtradeFile();
		m_pRecordTest = g_theRecordApp.ReadComtradeFile(m_pRcdComtradeFile);
	}
	else
	{
		m_pRecordTest = m_pReplayRecordTest;
		CreateBySttModulesComtradeBind();
	}

	m_pRecordTest->m_pWaveAnalyseViewRef = this;
	m_pRecordDrawObjcontrol = m_pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl;

	if (g_theBigComtradeTransPlay->m_bDrawSrcComtrade)
	{
		InitFromComtrade();
	}
	else
	{
		InitFromRecordTest(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetDataLength()
			, g_theBigComtradeTransPlay->GetPlaySampleRate());
	}

	//UICreate(m_pWndWaveGraph);
	CViewAnalyse::OnSizeEx(0, width(), height());
	m_bIsCreateRecordDraw = FALSE;
	//DrawAnalyse();

	//update();
}


void QWaveGraphWidget::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	switch (nMsgID)
	{
	case WM_TIME_CHANGED:
		XOnTimeCursorMessage(wParam, lParam);
		break;

	case WM_INVALIDATE_RANGESTATEAXIS:
		XOnInvalidateVertRangeStateAxis(wParam, lParam);
		break;

	case WM_VARIABLE_SIZE_CHANGED:
		XOnVariableSizeChanged(wParam, lParam);
		break;

	case WM_VARIABLE_POS_CHANGED:
		XOnVariablePositionChanged(wParam, lParam);
		break;

	case WM_VARIABLE_SELECT_CHANGED:
		XOnVariableSelectChanged(wParam, lParam);
		break;

	case WM_TIMEAXIS_CHANGED:
		XOnTimeAxisChanged(wParam, lParam);
		break;

	case WM_TIMECURSOR_POS_CHANGE:
		XOnTimeCursorPositionChange(wParam, lParam);
		break;

	case WM_TIMECURSOR_SELECT_CHANGE:
		XOnTimeCursorSelectChange(wParam, lParam);
		break;
	}
}

void QWaveGraphWidget::GetTwoCursorTimeValues(double &dTimeA,double &dTimeB)
{
	long nTimeCursorXA = 0, nTimeCursorXB = 0;
	m_pTimeCursorDraw->GetTwoCursorPosition(nTimeCursorXA, nTimeCursorXB);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nTimeCursorXA, &dTimeA);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nTimeCursorXB, &dTimeB);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("dTimeA=%lf,dTimeB=%lf"),dTimeA,dTimeB);
}

//////////////////////////////////////////////////////////////////////////
void QWaveGraphWidget::CreateBySttModulesComtradeBind()
{
	InitMR1200SysAnalyseMngr(m_pReplayRecordTest->m_oMR1200SysAnalyseMngr);

	CSttModulesComtradeBind *pSttModulesComtradeBind = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind;
	m_pReplayRecordTest->g_nSampleRate = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_dInsertFreq;//zhouhj 20211104 修改为实际采样率

	POS pos = pSttModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while (pos != NULL)
	{
		pModule = (CSttModuleComtradeBind*)pSttModulesComtradeBind->GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
			CreateBySttModulesComtradeBind(pModule);
		}
	}

	CRtVariables* pVariables = m_pReplayRecordTest->m_pVariables;

	if (pVariables->GetCount() > 0)
	{
		pVariables->InitAttrsBuffer(m_nTotalPoints);
		m_pReplayRecordTest->m_oMR1200SysAnalyseMngr.nCurrDrawObjectCount = m_nAnalogChanAmount;

		//先设置模拟量的
		InitMR1200SysAnalyseMngrDrawControl(m_pReplayRecordTest->m_oMR1200SysAnalyseMngr, m_nAnalogChanAmount,0);

		CRtVariable* pRefVariable = (CRtVariable*)pVariables->GetHead();
		pVariables->SetRefVariable(pRefVariable);
		//pVariables->InitDataAttributeCalFunc();
		InitHarmHistogram(m_pReplayRecordTest->m_oMR1200SysAnalyseMngr.oHarmHistogram);
		InitSysAnalyseMngr_AttrSpy(&m_pReplayRecordTest->m_oMR1200SysAnalyseMngr.oAttrSpy);
		InitSysAnalyseMngr_AttrDefault(&m_pReplayRecordTest->m_oMR1200SysAnalyseMngr.oAttrDefault);
	}

	m_pReplayRecordTest->InitDrawControl();
	AttachOnlineRecordExBuffer();
}

void QWaveGraphWidget::CreateBySttModulesComtradeBind(CSttModuleComtradeBind *pModule)
{
	POS pos = pModule->GetHeadPosition();
	CSttModuleChComtradeBind *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind*)pModule->GetNext(pos);
		CreateBySttModulesComtradeBind(pCh);
	}
}

void QWaveGraphWidget::CreateBySttModulesComtradeBind(CSttModuleChComtradeBind *pCh)
{
	CRtSingleVariable* pVariable = NULL;
	
	CreateBySttModulesComtradeBind(pCh, &pVariable);
	m_pReplayRecordTest->m_pVariables->AddTail(pVariable);
	pVariable->SetParent(m_pReplayRecordTest->m_pVariables);
	pVariable->SetVariableUseState(1);

	m_pReplayRecordTest->m_pVariables->SetVariable(pVariable, m_nAnalogChanAmount);

	PRECORDDRAWOBJECTCONTROL pDrawVar = &(m_pReplayRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl[m_nAnalogChanAmount]);
	m_nAnalogChanAmount++;
	pDrawVar->nShow = 1;
	pDrawVar->nUse  = 1;
	pDrawVar->dRange = pVariable->GetRangeEx();
}

void QWaveGraphWidget::CreateBySttModulesComtradeBind(CSttModuleChComtradeBind *pCh, CRtSingleVariable **ppVariable)
{
	CString strID,str;
	CRtSingleVariable* pVariable = new CRtSingleVariable();
	*ppVariable = pVariable;

	pVariable->m_pChannelBuffer = NULL; //不能使用InitBufferMngr函数因为没有BufferID
	pVariable->Set_ChIndex( m_nAnalogChanAmount );
	pVariable->m_strID		= pCh->m_strName;
	pVariable->m_strName    = pCh->m_strName;
	pVariable->m_strPhaseID = pCh->GetModuleChPhase();
	pVariable->m_strUnit = pCh->GetUnit();
	pVariable->m_strDCAC    = g_pszKeyVariableACDC;
	m_pReplayRecordTest->g_pCoefValue[m_nAnalogChanAmount]    = pCh->m_dCoefValue;
	m_pReplayRecordTest->g_pZeroValue[m_nAnalogChanAmount]    = pCh->m_dZeroValue;
	double dRange = pCh->m_fMaxAbs;

	dRange = MrDraw::GetFloatCarryValue2(dRange);
	pVariable->SetRange(dRange);

	if (pCh->IsModuleType_U())
	{
		pVariable->m_nType = RTVARIABLE_TYPE_U;
	}

	if (pCh->IsModuleType_I())
	{
		pVariable->m_nType = RTVARIABLE_TYPE_I;
	}

	//根据相别添加颜色
	pVariable->m_crColor = GetPhaseColorByPhaseID(pVariable->m_strPhaseID, pVariable->m_strID);

	pVariable->CreateStaticAttrs(pCh->m_strName);
	pVariable->m_pRefRecordData = pCh;
}


void QWaveGraphWidget::AttachOnlineRecordExBuffer()
{
	//g_bCalUseRecordBuffer = FALSE;
	CRtVariables *pVariables = m_pReplayRecordTest->m_pVariables;
	CRtVariable  *pVariable = NULL;
	//CMrOnlineRecordEx *pOnlineRecordEx = CMrOnlineRecordEx::g_pMrOnlineRecordEx;
	POS pos = pVariables->GetHeadPosition();
	long nAnalogChIndex = 0;
	long nTotalPoints = 0;
	CSttModuleChComtradeBind *pCh  = NULL;

	//处理模拟量通道
	while (pos != NULL)
	{
		pVariable = (CRtVariable*)pVariables->GetNext(pos);
		pCh = (CSttModuleChComtradeBind *)pVariable->m_pRefRecordData;
		pVariable->Set_ChIndex(nAnalogChIndex);
		nAnalogChIndex++;
		pVariable->m_pAttachRecordBuffer = pCh->m_pReplayBuf;
	}

	pVariables->InitDataAttributeCalFunc(FALSE);
}

void QWaveGraphWidget::AddDrawBtns()
{
	CString strPngPath, strBntIcon;
	strPngPath = _P_GetResourcePath();

	m_pBtnReset=new QPushButton("复归",this);
	connect(m_pBtnReset,SIGNAL(clicked()),this,SLOT(slot_Reset()));

	m_pBtnZoomOutTime=new QPushButton(/*"横放大",*/this);
	strBntIcon = strPngPath + _T("ZoomOutTime.png");
	m_pBtnZoomOutTime->setIcon(QIcon(strBntIcon));
	m_pBtnZoomOutTime->setIconSize(m_pBtnZoomOutTime->size());
	connect(m_pBtnZoomOutTime,SIGNAL(clicked()),this,SLOT(ZoomOutTime()));

	m_pBtnZoomInTime=new QPushButton(/*"横缩小",*/this);
	strBntIcon = strPngPath + _T("ZoomInTime.png");
	m_pBtnZoomInTime->setIcon(QIcon(strBntIcon));
	m_pBtnZoomInTime->setIconSize(m_pBtnZoomInTime->size());
	connect(m_pBtnZoomInTime,SIGNAL(clicked()),this,SLOT(ZoomInTime()));

	m_pBtnZoomOutChan=new QPushButton(/*"纵放大",*/this);
	strBntIcon = strPngPath + _T("ZoomOutChan.png");
	m_pBtnZoomOutChan->setIcon(QIcon(strBntIcon));
	m_pBtnZoomOutChan->setIconSize(m_pBtnZoomOutChan->size());
	connect(m_pBtnZoomOutChan,SIGNAL(clicked()),this,SLOT(ZoomInChan()));

	m_pBtnZoomInChan=new QPushButton(/*"纵缩小",*/this);
	strBntIcon = strPngPath + _T("ZoomInChan.png");
	m_pBtnZoomInChan->setIcon(QIcon(strBntIcon));
	m_pBtnZoomInChan->setIconSize(m_pBtnZoomInChan->size());
	connect(m_pBtnZoomInChan,SIGNAL(clicked()),this,SLOT(ZoomOutChan()));

	m_pBtnMoveLeft=new QPushButton("左移",this);
// 	strBntIcon = strPngPath + _T("moveleft.png");
// 	m_pBtnMoveLeft->setIcon(QIcon(strBntIcon));
	connect(m_pBtnMoveLeft,SIGNAL(clicked()),this,SLOT(MoveLeft()));

	m_pBtnMoveRight=new QPushButton("右移",this);
// 	strBntIcon = strPngPath + _T("moveright.png");
// 	m_pBtnMoveRight->setIcon(QIcon(strBntIcon));
	connect(m_pBtnMoveRight,SIGNAL(clicked()),this,SLOT(MoveRight()));

	m_pT1Lable = new QLabel(this);
	m_pT1Lable->setStyleSheet("color: red;"); // 设置字体颜色为红色

	m_pT2Lable = new QLabel(this);
	m_pT2Lable->setStyleSheet("color: blue;"); // 设置字体颜色为蓝色


}

void QWaveGraphWidget::UpdateDrawBtns()
{
	QRect rc = parentWidget()->rect();
	long nHeight = rc.height();
	long nWidth = rc.width();
	int i = 0;
	nWidth = (nWidth - 7 * 50) / 6;
	m_pBtnZoomOutTime->setGeometry(i++ *(50 + nWidth)+20,rc.height() - STT_ToolBtn_Width , 50, 40);
	m_pBtnZoomInTime->setGeometry(i++ *(50 + nWidth), rc.height() - STT_ToolBtn_Width , 50, 40);
	m_pBtnZoomOutChan->setGeometry(i++ *(50 + nWidth), rc.height() - STT_ToolBtn_Width , 50, 40);
	m_pBtnZoomInChan->setGeometry(i++ *(50 + nWidth), rc.height() - STT_ToolBtn_Width , 50, 40);
	m_pBtnMoveLeft->setGeometry(i++ *(50 + nWidth), rc.height() - STT_ToolBtn_Width , 50, 40);
	m_pBtnMoveRight->setGeometry(i++ *(50 + nWidth), rc.height() - STT_ToolBtn_Width , 50, 40);
	m_pBtnReset->setGeometry(i++ *(50 + nWidth)-20, rc.height() - STT_ToolBtn_Width , 50, 40);

	long nLeft = rc.left();
 	m_pT1Lable->setGeometry(rc.left()+10,rc.height() - 100,rc.width(),30);
 	m_pT2Lable->setGeometry(rc.left()+10,rc.height() - 80,rc.width(),30);

}

void QWaveGraphWidget::MoveLeft()
{
	CViewAnalyse::MoveLeft();
	update();
}

void QWaveGraphWidget::MoveRight()
{
	CViewAnalyse::MoveRight();
	update();
}

void QWaveGraphWidget::ZoomInChan()
{
	CViewAnalyse::ZoomInChan();
	update();
}

void QWaveGraphWidget::ZoomOutChan()
{
	CViewAnalyse::ZoomOutChan();
	update();
}

void QWaveGraphWidget::ZoomInTime()
{
	//缩小
	CViewAnalyse::ZoomInTime(0);

	ChangeTimeCursorDrawPos(m_dTimeA,m_dTimeB);
	
	update();

}

void QWaveGraphWidget::ZoomOutTime()
{
	//放大
	CViewAnalyse::ZoomOutTime(0);

	ChangeTimeCursorDrawPos(m_dTimeA,m_dTimeB);

	update();
}

void QWaveGraphWidget::slot_Reset()
{
	CreateRecordDrawByComtrade();
}	

void QWaveGraphWidget::UpdateInsertWaveBackColor( double nValue1,double nValue2 )
{
	long nXa, nXb;
	m_oTimeAxisDraw.LogicPointToDevicePoint(nValue1,&nXa);
	m_oTimeAxisDraw.LogicPointToDevicePoint(nValue2,&nXb);

	long nHeight=m_oTimeAxisDraw.m_nHeight;
	QRect rect = parentWidget()->rect();
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(QColor(204, 153, 102, 127));
	p.setCompositionMode(QPainter::CompositionMode_Plus);
	p.drawRect(QRect(nXa,rect.top(),labs(nXb-nXa),rect.height()-nHeight-50));
}

void QWaveGraphWidget::UpdateDeleteWaveBackColor( double nValue1,double nValue2 )
{
	long nXa, nXb;
	m_oTimeAxisDraw.LogicPointToDevicePoint(nValue1,&nXa);
	m_oTimeAxisDraw.LogicPointToDevicePoint(nValue2,&nXb);

	long nHeight=m_oTimeAxisDraw.m_nHeight;
	QRect rect = parentWidget()->rect();
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(QColor(100, 100, 100, 200));//灰色
	p.setCompositionMode(QPainter::CompositionMode_Plus);
	p.drawRect(QRect(nXa,rect.top(),labs(nXb-nXa),rect.height()-nHeight-50));

}

CString QWaveGraphWidget::FormatTime( double dSeconds )
{
	int hours = static_cast<int>(dSeconds / 3600);
	int minutes = static_cast<int>((dSeconds - hours * 3600) / 60);
	double secs = dSeconds - hours * 3600 - minutes * 60;

	CString strHours = QString::number(hours);
	CString strMinutes = QString::number(minutes);
	CString strSecs = QString::number(secs);

	CString strRet;
	strRet.Format("%02d:%02d:%05.3f",hours,minutes,secs);

	 return strRet;
}

void QWaveGraphWidget::ChangeTimeCursorDrawPos( double dATime,double dBTime )
{
	//计算新的pos位置
	long nApos = 0,nBpos = 0;//新的位置

	m_oTimeAxisDraw.LogicPointToDevicePoint(dATime,&nApos);
	m_oTimeAxisDraw.LogicPointToDevicePoint(dBTime,&nBpos);

	m_pTimeCursorDraw->SetCursorPosition(nApos,USETIMECURSORA);
	m_pTimeCursorDraw->SetCursorPosition(nBpos,USETIMECURSORB);
}

//////////////////////////////////////////////////////////////////////////
CWnd_WaveGraph::CWnd_WaveGraph()
{
	m_pWaveGraph = NULL;
}

CWnd_WaveGraph::~CWnd_WaveGraph()
{

}

//重载函数OnWndMsg，实现消息处理
void CWnd_WaveGraph::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	m_pWaveGraph->OnWndMsg(nMsgID, wParam, lParam);
}

void CWnd_WaveGraph::OnWndTimer(unsigned int nIDEvent)
{

}

CDC* CWnd_WaveGraph::GetDC()
{
	return m_pWaveGraph->GetDC();
}

void CWnd_WaveGraph::ReleaseDC(CDC *pDC)
{

}

void CWnd_WaveGraph::GetClientRect(CRect &rc)
{
	rc.left = 0;
	rc.top = 0;
	rc.right = m_pWaveGraph->width();
	rc.bottom = m_pWaveGraph->height()-100;
}

void CWnd_WaveGraph::GetClientRect(CRect *pRect)
{
	GetClientRect(*pRect);
}

void CWnd_WaveGraph::InvalidateRect(CRect *pRect, BOOL b)
{
	m_pWaveGraph->QWidget::update(pRect->Get_QRect());
}

void CWnd_WaveGraph::InvalidateRect(CRect &rect, BOOL b)
{
	m_pWaveGraph->QWidget::update(rect.Get_QRect());
}

void CWnd_WaveGraph::Invalidate(BOOL b)
{
	m_pWaveGraph->QWidget::update();
}

