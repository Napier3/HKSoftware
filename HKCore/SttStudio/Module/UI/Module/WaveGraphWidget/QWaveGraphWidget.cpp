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

	//lijunqing : ���������ͷ��봰����صĻ�ͼ���󣬷����ڴ�������֮�����ͷţ��ͻᵼ��ϵͳ����
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
// 		oDC.DrawText("���COMTRADE�����ļ�", rc, DT_VCENTER|DT_LEFT);
// 	}
// 
// 	oDC.end();
// 	updateGeometry();//zhouhj 20211104 �������ڽ���ƶ���ֱ����Ӱ������
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
	//�����жϣ����Ⲩ�θ���ʱҲ��"���COMTRADE�����ļ�"��ʾ
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
		//oDC.DrawText("���COMTRADE�����ļ�", rc, DT_VCENTER|DT_LEFT);
		oDC.DrawText(g_sLangTxt_State_POpenCFile.GetString(), rc, DT_VCENTER|DT_LEFT);  //���COMTRADE�����ļ� lcq 3.15

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
	//str = _T("��һҳ");
    xlang_GetLangStrByFile(g_sLangTxt_Smv_PrevPage,"Smv_PrevPage");
	m_pBtn_PrevPage = new QPushButton(g_sLangTxt_Smv_PrevPage,this); //��һҳ LCQ
	connect(m_pBtn_PrevPage,SIGNAL(clicked()),this,SLOT(slotDrawOptr_PrevPage()));

	//str = _T("��һҳ");
	xlang_GetLangStrByFile(g_sLangTxt_Smv_NextPage,"Smv_NextPage");
	m_pBtn_NextPage= new QPushButton(g_sLangTxt_Smv_NextPage,this);//��һҳ LCQ
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
		m_pBtn_NextPage->setEnabled(TRUE); // ����ʱ����������һҳ��ť

		if (m_nCurrPageIndex == 0)
		{
			m_pBtn_PrevPage->setEnabled(FALSE); // ����ǵ�һҳ��������һҳ��ť
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

		// �������Ѿ������һҳ���������һҳ��ť
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

		if(nCurrentX < MrDraw::g_snNameandAxisRectWidth)//2023-11-13 wuxinyi �޸�USETIMECURSORA�ڲ���ͼ֮�⣬�Ҳ���ͨ�����ж�����
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
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����ʱ������λ��δ�ı�,����������ֵ."));
		return;
	}

	m_dTimeA = dTimeA;
	m_dTimeB = dTimeB;
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���͸��������ź�,sig_UpdateTwoCursorTimeValues."));
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
// 	{//���û�в������ݣ��򷵻�
// 		return;
// 	}

	CViewAnalyse::OnSizeEx(0, cx, cy);
	DrawAnalyse();
}


void QWaveGraphWidget::CreateRecordDrawByComtrade()
{
	if (! g_theBigComtradeTransPlay->HasComtradeDataNeedDraw())
	{//���û�в������ݣ��򷵻�
		return;
	}

	if(m_nPageCount <= 0)//��ǰû�пɻ��Ʋ���ͼ
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
	m_pReplayRecordTest->g_nSampleRate = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_dInsertFreq;//zhouhj 20211104 �޸�Ϊʵ�ʲ�����

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

		//������ģ������
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
	if (m_nPageCount == 1) //20231012clͨ��ֻ��һ����һҳ��һҳ��Ӧ���ɵ㣬��������
	{
		m_pBtn_PrevPage->setEnabled(FALSE);
		m_pBtn_NextPage->setEnabled(FALSE);
	}

	InitMR1200SysAnalyseMngr(m_pReplayRecordTest->m_oMR1200SysAnalyseMngr);

	CSttModulesComtradeBind *pSttModulesComtradeBind = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind;
	m_pReplayRecordTest->g_nSampleRate = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_dInsertFreq;//zhouhj 20211104 �޸�Ϊʵ�ʲ�����

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

	//������ǰҳ��ͨ��
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

		//������ģ������
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

	pVariable->m_pChannelBuffer = NULL; //����ʹ��InitBufferMngr������Ϊû��BufferID
	pVariable->Set_ChIndex( m_nAnalogChanAmount );
	pVariable->m_strID		= pCh->m_strName;
	CString strChName = pCh->m_strName;
	if (!xlang_IsCurrXLanguageChinese())//dingxy 20250121 Ӣ�Ļ������޸�ͨ��ӳ������
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

	//������������ɫ
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

	//����ģ����ͨ��
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
	p.setBrush(QColor(100, 100, 100, 200));//��ɫ
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

	// ����pos���ٴα�������
	pos = pSttModulesComtradeBind->GetHeadPosition();

	// ����������ģ��
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

//���غ���OnWndMsg��ʵ����Ϣ����
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

