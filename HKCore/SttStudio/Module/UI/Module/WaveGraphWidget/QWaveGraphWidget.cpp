#include "QWaveGraphWidget.h"
#include <QResizeEvent>
#include "../../../Module/XLangResource_Native.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/ReplayTest/BigComtradeTransPlay.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QCoreApplication>
#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>
#include "../../../SttTestSysGlobalPara.h"

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

	m_nPageCount = 0;
	m_nCurrPageIndex=0;
	m_nMaxChannels = 5;

	m_pDC = new CDC(this);
	m_pWndWaveGraph = new CWnd_WaveGraph();
	m_pWndWaveGraph->m_pWaveGraph = this;

	initPlot();
	AddDrawOptrBtns();
 	
	SetParentWnd(m_pWndWaveGraph);
 	UICreate(m_pWndWaveGraph);
	m_nTotalPoints = 10000;
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
	update();
// 	CDC oDC(this);
// 	oDC.begin(this);
// 	CViewAnalyse::OnDraw(&oDC);
// 
// 	if (!g_oBigComtradeTransPlay.HasComtradeDataNeedDraw())
// 	{
// 		long y = height() / 2;
// 		long x = width() / 2;
// 		CRect rc;
// 		rc.left = x - 100;
// 		rc.top = y-10;
// 		rc.bottom = y + 10;
// 		rc.right = x + 100;
// 
// 		oDC.SetTextColor(RGB(255, 255, 255));
// 		oDC.DrawText("请打开COMTRADE波形文件", rc, DT_VCENTER|DT_LEFT);
// 	}
// 
// 	oDC.end();
// 	updateGeometry();//zhouhj 20211104 增加用于解决移动垂直线重影的问题
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QWaveGraphWidget::UpdateWaveDraws()"));
}
void QWaveGraphWidget::UpdateButtonEnable(BOOL bState)
{
#ifdef _PSX_QT_WINDOWS_
// 	m_pBtnReset->setEnabled(bState);
// 	m_pBtnZoomOutTime->setEnabled(bState);
// 	m_pBtnZoomInTime->setEnabled(bState);
// 	m_pBtnZoomOutChan->setEnabled(bState);
// 	m_pBtnZoomInChan->setEnabled(bState);
// 	m_pBtnMoveLeft->setEnabled(bState);
// 	m_pBtnMoveRight->setEnabled(bState);
// 	m_pBtn_PrevPage->setEnabled(bState);
// 	m_pBtn_NextPage->setEnabled(bState);
#else
	m_pBtn_PrevPage->setEnabled(bState);
	m_pBtn_NextPage->setEnabled(bState);
#endif // _PSX_QT_WINDOWS_

}

void QWaveGraphWidget::paintEvent(QPaintEvent *event)
{
	CDC oDC(this);
	oDC.begin(this);
	CViewAnalyse::OnDraw(&oDC);
	//新增判断，避免波形复归时也有"请打开COMTRADE波形文件"提示
	if (!g_theBigComtradeTransPlay->HasComtradeDataNeedDraw() && (g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.m_strComtradeFile.IsEmpty()))
	{
		long y = height() / 2;
		long x = width() / 2;
		CRect rc;
		rc.left = x - 100;
		rc.top = y-10;
		rc.bottom = y + 10;
		rc.right = x + 100;

		oDC.SetTextColor(RGB(255, 255, 255));
		//oDC.DrawText("请打开COMTRADE波形文件", rc, DT_VCENTER|DT_LEFT);
		oDC.DrawText(g_sLangTxt_State_POpenCFile.GetString(), rc, DT_VCENTER|DT_LEFT);  //请打开COMTRADE波形文件 lcq 3.15

		UpdateButtonEnable(FALSE);
		SendUpdateTwoCursorTimeValues(TRUE);
	}
	else
	{
		UpdateButtonEnable(TRUE);
	}

	if(m_bInsertWaveformBackColor)
	{
		UpdateInsertWaveBackColor(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd);
	}
	if(m_bDeleteWaveformBackColor)
	{
		UpdateDeleteWaveBackColor(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd);
	}

	oDC.end();
}
void QWaveGraphWidget::AddDrawOptrBtns()
{
	//CString str;
	//str = _T("上一页");
    xlang_GetLangStrByFile(g_sLangTxt_Smv_PrevPage,"Smv_PrevPage");
	m_pBtn_PrevPage = new QPushButton(g_sLangTxt_Smv_PrevPage,this); //上一页 LCQ
	connect(m_pBtn_PrevPage,SIGNAL(clicked()),this,SLOT(slotDrawOptr_PrevPage()));

	//str = _T("下一页");
	xlang_GetLangStrByFile(g_sLangTxt_Smv_NextPage,"Smv_NextPage");
	m_pBtn_NextPage= new QPushButton(g_sLangTxt_Smv_NextPage,this);//下一页 LCQ
	connect(m_pBtn_NextPage,SIGNAL(clicked()),this,SLOT(slotDrawOptr_NextPage()));


}
void QWaveGraphWidget::slotDrawOptr_PrevPage()
{
	if(m_nPageCount < 0)
	{
		return;
	}

	initPlot();
	if (m_nCurrPageIndex > 0)
	{
		m_nCurrPageIndex--;
		m_pBtn_NextPage->setEnabled(TRUE); // 返回时总是启用下一页按钮

		if (m_nCurrPageIndex == 0)
		{
			m_pBtn_PrevPage->setEnabled(FALSE); // 如果是第一页，禁用上一页按钮
		}
	}
	CreateBySttModulesComtradeBind(m_nCurrPageIndex);

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
}

void QWaveGraphWidget::slotDrawOptr_NextPage()
{
	if(m_nPageCount < 0)
	{
		return;
	}

	initPlot();
	if (m_nCurrPageIndex < m_nPageCount - 1)
	{
		m_nCurrPageIndex++;
		m_pBtn_PrevPage->setEnabled(TRUE);

		// 检查如果已经是最后一页，则禁用下一页按钮
		if (m_nCurrPageIndex == m_nPageCount - 1)
		{
			m_pBtn_NextPage->setEnabled(FALSE);
		}
	}
	else
	{
		m_pBtn_NextPage->setEnabled(FALSE);
	}
	CreateBySttModulesComtradeBind(m_nCurrPageIndex);

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
}

void QWaveGraphWidget::UpdateDrawOptrBtns()
{
	QRect rc = parentWidget()->rect();
	long nHeight = rc.height();
	nHeight = (nHeight - 7 * 50 - 60) / 6;
	m_pBtn_PrevPage->setGeometry(rc.right() - 60,nHeight-6,60,40);
	m_pBtn_NextPage->setGeometry(rc.right() - 60,40 + nHeight,60,40);

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
	UpdateDrawOptrBtns();
}


void QWaveGraphWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentX = event->pos().x();

		if(nCurrentX < MrDraw::g_snNameandAxisRectWidth)//2023-11-13 wuxinyi 修改USETIMECURSORA在波形图之外，找不到通道会中断问题
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

		UpdateWaveDraws();
	}
	
	mousePressEvent(event);              
}

void QWaveGraphWidget::SendUpdateTwoCursorTimeValues(BOOL bCompare)
{
	double dTimeA = 0, dTimeB = 0; 
	GetTwoCursorTimeValues(dTimeA,dTimeB);

	if ((bCompare)&&(fabs(m_dTimeA-dTimeA)<0.0001)&&(fabs(m_dTimeB-dTimeB)<0.0001))
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("m_dTimeA=%lf,dTimeA=%lf,m_dTimeB=%lf,dTimeB=%lf."),m_dTimeA,dTimeA,m_dTimeB,dTimeB);
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("两个时间坐标位置未改变,不更新坐标值."));
		return;
	}

	m_dTimeA = dTimeA;
	m_dTimeB = dTimeB;
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发送更新坐标信号,sig_UpdateTwoCursorTimeValues."));
	emit sig_UpdateTwoCursorTimeValues(dTimeA,dTimeB);
}

void QWaveGraphWidget::mouseMoveEvent(QMouseEvent *event)
{
	CPoint oPoint(event->pos().x(),event->pos().y());
	XOnMouseMove(0,oPoint);
	event->ignore();
	SendUpdateTwoCursorTimeValues(TRUE);
//	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("mouseMoveEvent"));
//	QWidget::mouseMoveEvent(event);
}

void QWaveGraphWidget::mousePressEvent(QMouseEvent *event)
{
	CPoint oPoint(event->pos().x(),event->pos().y());
	//m_pCharacterDrawView->SetAxisInstruct_Point(oPoint);
	XOnLButtonDown(0, oPoint);
	QWidget::mousePressEvent(event);
	SendUpdateTwoCursorTimeValues(TRUE);
//	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("mousePressEvent"));
}

void QWaveGraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
	CPoint oPoint(event->pos().x(),event->pos().y());
	XOnLButtonUp(0, oPoint);
	QWidget::mouseReleaseEvent(event);
	SendUpdateTwoCursorTimeValues(TRUE);
//	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("mouseReleaseEvent"));
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
	m_pReplayRecordTest->m_pVariables->DeleteAll();
	ClearSelect();
}

void QWaveGraphWidget::slot_UpdateDrawWaveGraph()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QWaveGraphWidget::slot_UpdateDrawWaveGraph()"));
	DrawAnalyse();
//	UpdateWaveDraws();
}


void QWaveGraphWidget::RecordDraw()
{

}

void QWaveGraphWidget::CreateRecordDraw(long cx, long cy)
{
// 	if (! g_oBigComtradeTransPlay.HasComtradeDataNeedDraw())
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

	if(m_nPageCount <= 0)//当前没有可绘制波形图
	{
		return;
	}

	initPlot();
	
	if (g_theBigComtradeTransPlay->m_bDrawSrcComtrade)
	{
		m_pRcdComtradeFile = g_theBigComtradeTransPlay->GetSrcComtradeFile();
		m_pRecordTest = g_theRecordApp.ReadComtradeFile(m_pRcdComtradeFile);
	}
	else
	{
		m_pRecordTest = m_pReplayRecordTest;
		CreateBySttModulesComtradeBind(m_nCurrPageIndex);
		//CreateBySttModulesComtradeBind(m_nCurrPageIndex);
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

	UpdateWaveDraws();
}

void QWaveGraphWidget::GetTwoCursorTimeValues(double &dTimeA,double &dTimeB)
{
	long nTimeCursorXA = 0, nTimeCursorXB = 0;
	m_pTimeCursorDraw->GetTwoCursorPosition(nTimeCursorXA, nTimeCursorXB);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nTimeCursorXA, &dTimeA);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nTimeCursorXB, &dTimeB);
// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("dTimeA=%lf,dTimeB=%lf"),dTimeA,dTimeB);
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


void QWaveGraphWidget::CreateBySttModulesComtradeBind(int nPageIndex)
{
	if (m_nPageCount == 1) //20231012cl通道只有一个上一页下一页都应不可点，否则闪退
	{
		m_pBtn_PrevPage->setEnabled(FALSE);
		m_pBtn_NextPage->setEnabled(FALSE);
	}

	InitMR1200SysAnalyseMngr(m_pReplayRecordTest->m_oMR1200SysAnalyseMngr);

	CSttModulesComtradeBind *pSttModulesComtradeBind = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind;
	m_pReplayRecordTest->g_nSampleRate = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_dInsertFreq;//zhouhj 20211104 修改为实际采样率

// 	POS pos = pSttModulesComtradeBind->GetHeadPosition();
// 	CSttModuleComtradeBind *pModule = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pModule = (CSttModuleComtradeBind*)pSttModulesComtradeBind->GetNext(pos);
// 		if(!pModule->IsBinaryTypeModule())
// 		{
// 			CreateBySttModulesComtradeBind(pModule);
// 		}
// 	}

	//创建当前页数通道
	CSttModuleComtradeBind *pModuleComtradeBind = m_oModuleMap.value(nPageIndex);
	if(!pModuleComtradeBind)
	{
		return;
	}
	CreateBySttModulesComtradeBind(pModuleComtradeBind);

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
	CString strChName = pCh->m_strName;
	if (!xlang_IsCurrXLanguageChinese())//dingxy 20250121 英文环境下修改通道映射名称
	{
		if (strChName.Find(_T("U")) >= 0)
		{
			strChName.Replace(_T("U"), _T("V"));
		}
	}
	
	pVariable->m_strName = strChName;
	//pVariable->m_strName    = pCh->m_strName;
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
	p.drawRect(QRect(nXa,rect.top(),labs(nXb-nXa),rect.height()));
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
	p.drawRect(QRect(nXa,rect.top(),labs(nXb-nXa),rect.height()));
}

void QWaveGraphWidget::initModuleMap()
{
	m_oModuleMap.clear();
	CSttModulesComtradeBind *pSttModulesComtradeBind = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind;
	CSttModuleComtradeBind *pModule = NULL;
	int nChIndex = 0;
	int nPageIndex = 0;
	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = pSttModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pTemModule = NULL;
	while(pos)
	{
		CSttModuleComtradeBind* pModule = (CSttModuleComtradeBind*)pSttModulesComtradeBind->GetNext(pos);
		if((pModule->IsAnalogTypeModule() && g_oSystemParas.m_nHasAnalog)||
			(pModule->IsWeekTypeModule() && g_oSystemParas.m_nHasWeek))
		{
			POS posCh = pModule->GetHeadPosition();
			while(posCh)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

				if (!pTemModule)
				{
					pTemModule = new CSttModuleComtradeBind;
				}

				pTemModule->AddNewChild(pCh);
				nChIndex++;

				if (nChIndex >= m_nMaxChannels)
				{
					m_oModuleMap.insert(nPageIndex, pTemModule);
					nChIndex = 0;
					nPageIndex++;
					pTemModule = NULL;  // Reset the temporary module pointer
				}

			}

		}	
	}
	if (nChIndex > 0 && pTemModule != NULL)
	{
		m_oModuleMap.insert(nPageIndex, pTemModule);
	}

	// 重置pos以再次遍历链表
	pos = pSttModulesComtradeBind->GetHeadPosition();

	// 创建数字量模块
	while (pos != NULL)
	{
		CSttModuleComtradeBind* pModule = (CSttModuleComtradeBind*)pSttModulesComtradeBind->GetNext(pos);
		if(pModule->IsDigitalTypeModule() && g_oSystemParas.m_nHasDigital)
		{
			POS posCh = pModule->GetHeadPosition();
			while(posCh)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

				if (!pTemModule)
				{
					pTemModule = new CSttModuleComtradeBind;
				}

				pTemModule->AddNewChild(pCh);
				nChIndex++;

				if (nChIndex >= m_nMaxChannels)
				{
					m_oModuleMap.insert(nPageIndex, pTemModule);
					nChIndex = 0;
					nPageIndex++;
					pTemModule = NULL;  // Reset the temporary module pointer
				}

			}

		}
	}
	if (nChIndex > 0 && pTemModule != NULL)
	{
		m_oModuleMap.insert(nPageIndex, pTemModule);
	}

}

void QWaveGraphWidget::InitWaveGraph()
{
	m_nCurrPageIndex = 0;
	initModuleMap();
	m_nPageCount = m_oModuleMap.size();

	if(m_nPageCount == 0 || !g_theBigComtradeTransPlay->HasComtradeDataNeedDraw())
	{
		m_pBtn_NextPage->setEnabled(FALSE);
		m_pBtn_PrevPage->setEnabled(FALSE);
	}
	else
	{
		m_pBtn_PrevPage->setEnabled(FALSE);
	}
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
	rc.bottom = m_pWaveGraph->height();
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

