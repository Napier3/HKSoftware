#include "SttIecSmvWaveWidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#ifdef _PSX_QT_LINUX_
#include "MUTest/SttIecRecordCbInterface.h"
#endif

QSttIecSmvWaveWidget::QSttIecSmvWaveWidget(QWidget *parent)
#ifdef QT_Wnd_USE_QWIDGET
: CWnd(parent)
#else
: QWidget(parent)
#endif
{
	m_pIecRcdFuncWidget = this;//20250123  suyang ע���ᵼ���ڼ��̴�����
	m_pWidgetRef = this;
	m_nCurrRcdChIndex = 0;
	m_bInitTimeAxis = TRUE;
	m_nUpdateCount = 0;

	m_bUpdateFlag = TRUE;
}

QSttIecSmvWaveWidget::~QSttIecSmvWaveWidget()
{

}

//���غ���OnWndMsg��ʵ����Ϣ����
void QSttIecSmvWaveWidget::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{

}

void QSttIecSmvWaveWidget::OnWndTimer(unsigned int nIDEvent) 
{

}

void QSttIecSmvWaveWidget::IecRcdInitFromRecordTest()
{
	if(GetDefaultRefBuffer() == NULL)
	{
		return;
	}
	//��ʼ��m_oDrawBufferPos
	//InitFromRecordTest();
	InitDrawBufferPos();  

	//���ݽṹ�����õ�ͨ��λ�õ���ͨ��λ��
	InitDrawVarRect();
	//����¼�����ݻ����������ݳ��ȣ������õ�ǰ��ʾ�Ĳ��εĳ���
	//ͬʱ����ʱ������ķ�Χ
	InitTimeAxis();

	//�����ͼ������CPoint��Xλ��
	CalXPosByTimeAxis();

	//#ifdef _USE_ANALYSE_
	//���������ʾ����
	CalParaRect();
//	setAttribute(Qt::WA_OpaquePaintEvent);
}

////2022-6-12  lijunqing ��ǰCapDevice��¼��ͨ��
void QSttIecSmvWaveWidget::GetCurrDeviceAllRcdVariables()
{
	m_pRecordTest = g_theXSmartCapMngr->GetRecordTest();

	if (m_pRecordTest == NULL)
	{
		return;
	}

	m_listRcdVariable.RemoveAll();
	CCapDeviceChBase *pCh = NULL;
	CRtVariables *pVariables = m_pRecordTest->m_pVariables;
	CRtVariable* pVariable =NULL;
	POS pos = pVariables->GetHeadPosition();
	CCapDeviceChRecord *pCapChRcd = NULL;

	while (pos != NULL)
	{
		pVariable = (CRtVariable*)pVariables->GetNext(pos);
		pCapChRcd = (CCapDeviceChRecord *)pVariable->m_pRefRecordData;

		if (pCapChRcd == NULL)
		{
			continue;;
		}

		if (pCapChRcd->m_pRecfCh == NULL)
		{
			continue;
		}

		if (pCapChRcd->m_pRecfCh->GetParent() == m_pCapDevice)
		{
			m_listRcdVariable.AddTail(pVariable);
		}
	}
}

void QSttIecSmvWaveWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (m_pCapDevice == NULL)
	{
		ClearSelect();
		SetParentWnd(this);
		return;
	}

	ClearSelect();

	SetParentWnd(this);
	SetCapDeviceChRecordMngr(g_theXSmartCapMngr->GetCapDeviceChRecordMngr());
	UICreate(this);
	CViewAnalyse::OnSizeEx(0, 0, 0);

	GetCurrDeviceAllRcdVariables(); //2022-6-12  lijunqing
	OnVariableAddRemoved(0, 0);
	IecRcdInitFromRecordTest();

	g_theXSmartCapMngr->AdjustRecordChRange();
	g_theRecordApp.InitDrawControlByRecordTest(m_pRecordTest);
	AdjustAxisRange();
	SetDrawVariablesRange();
	DrawAnalyse();
}

void QSttIecSmvWaveWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	if (!m_bUpdateFlag)
	{
		return;
	}

	if (m_pCapDevice == NULL)
	{
		return;
	}

	m_nUpdateCount++;
	//��linux��ֻ����2�ı�����ʱ��ˢ��
	if ((m_nUpdateCount%2) != 0)
	{
		return;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("IecRcdFuncUpdate"));
	UpdateDrawVariablesRange();

	double dMax,dMin;
	m_oTimeAxisDraw.GetMaxMinTime(dMax,dMin);
	CalScrollDrawDataPos(dMax,dMin);

	//CalValues();
	//CalParaRect();

	DrawAnalyse();
	//Invalidate(FALSE);
#ifdef _PSX_QT_LINUX_
	if (!g_pSttIecRecordCbWidget->IsTabUI_Mode())
	{
		update();
	}
#else
	update();
#endif
}

void QSttIecSmvWaveWidget::Release()
{
	m_listRcdVariable.RemoveAll();
	m_pRecordTest = NULL;
	DestroyWindow();
	//delete this;
}

void QSttIecSmvWaveWidget::ReleaseUI()
{
	m_listRcdVariable.RemoveAll();
	m_pRecordTest = NULL;
	m_pCapDeviceChRecordMngr = NULL;

	RemoveAll();
	m_oVariableMngr.DeleteAll();
	m_bInitTimeAxis = TRUE;
	m_nUpdateCount = 0;
//	DestroyWindow();
}


BOOL QSttIecSmvWaveWidget::NeedNextAndPrev()
{
	return TRUE;
}

void QSttIecSmvWaveWidget::NextPage()
{
	ClearSelect();
	CalIndex_NextPage();
	OnVariableAddRemoved(0, 0);
}

void QSttIecSmvWaveWidget::PrevPage()
{
	ClearSelect();
	CalIndex_PrevPage();
	OnVariableAddRemoved(0, 0);
}

void QSttIecSmvWaveWidget::CalIndex_NextPage()
{
	long nBinarys = 0;
	long nAnalogs = 0;
	long nChsCount = 0;
	BOOL bNeedAdjust = FALSE;

	CDrawVariable *pDrawVariable = NULL;
	//CRtVariables *pVariables = m_pRecordTest->m_pVariables;  //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
	CRtVariable* pVariable =NULL;
	long nAnalogChanAmount = 0;
	long nCurrentChans = 0;
	long nIndex = m_nCurrRcdChIndex;

	for (nIndex=m_nCurrRcdChIndex; ; nIndex++)
	{
		//pVariable = (CRtVariable*)pVariables->GetAtIndex(nIndex);  //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
		pVariable = (CRtVariable*)m_listRcdVariable.GetAtIndex(nIndex);

		if (pVariable == NULL)
		{
			break;
		}

		if (! pVariable->CanCal())
		{
			continue;
		}

		nAnalogChanAmount++;
		nCurrentChans++;

		if (nCurrentChans >= STT_IECRCD_WAVE_CHS_PAGE)
		{
			break;
		}
	}

	//if (nIndex >= pVariables->GetCount()) //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
	if (nIndex >= m_listRcdVariable.GetCount())
	{
		m_nCurrRcdChIndex = 0;
	}
	else
	{
		m_nCurrRcdChIndex = nIndex;
	}
}

void QSttIecSmvWaveWidget::CalIndex_PrevPage()
{
	long nBinarys = 0;
	long nAnalogs = 0;
	long nChsCount = 0;
	BOOL bNeedAdjust = FALSE;

	CDrawVariable *pDrawVariable = NULL;
	//CRtVariables *pVariables = m_pRecordTest->m_pVariables;  //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
	CRtVariable* pVariable =NULL;
	long nAnalogChanAmount = 0;
	long nCurrentChans = 0;
	long nIndex = 0;

	if (m_nCurrRcdChIndex == 0)
	{
		//nIndex = pVariables->GetCount()-1;  //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
		nIndex = m_listRcdVariable.GetCount()-1;
	}
	else
	{
		nIndex = m_nCurrRcdChIndex;
	}

	while (TRUE)
	{
		//pVariable = (CRtVariable*)pVariables->GetAtIndex(nIndex);  //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
		pVariable = (CRtVariable*)m_listRcdVariable.GetAtIndex(nIndex);

		if (pVariable == NULL)
		{
			break;
		}

		if (! pVariable->CanCal())
		{
			continue;
		}

		nAnalogChanAmount++;
		nCurrentChans++;

		if (nCurrentChans >= STT_IECRCD_WAVE_CHS_PAGE)
		{
			break;
		}

		nIndex--;
	}

	if (nIndex <= 0)
	{
		m_nCurrRcdChIndex = 0;
	}
	else
	{
		m_nCurrRcdChIndex = nIndex;
	}
}

void QSttIecSmvWaveWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	CPoint point(event->pos().x(),event->pos().y());

	if (event->button() == Qt::LeftButton)
	{
		XOnLButtonDblClk(0, point);
	}
	else if (event->button() == Qt::RightButton)
	{
		XOnRButtonDblClk(0, point);
	}
// 	UpdateDrawCharacters();
// 	mousePressEvent(event);   
// 
// 	emit sig_UpdatePointLocation(m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX,m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY);
}

void QSttIecSmvWaveWidget::mouseMoveEvent(QMouseEvent *event)
{
 	CPoint point(event->pos().x(),event->pos().y());
	XOnMouseMove(0, point);

	event->ignore();
}

void QSttIecSmvWaveWidget::mousePressEvent(QMouseEvent *event)
{
	CPoint point(event->pos().x(),event->pos().y());

	if (event->button() == Qt::LeftButton)
	{
		XOnLButtonDown(0, point);
	}
	else if (event->button() == Qt::RightButton)
	{
		XOnRButtonDown(0, point);
	}

	QWidget::mousePressEvent(event);
}

void QSttIecSmvWaveWidget::mouseReleaseEvent(QMouseEvent *event)
{
	CPoint point(event->pos().x(),event->pos().y());

	if (event->button() == Qt::LeftButton)
	{
		XOnLButtonUp(0, point);
	}
	else if (event->button() == Qt::RightButton)
	{
		XOnRButtonUp(0, point);
	}

	QWidget::mouseReleaseEvent(event);
}

void QSttIecSmvWaveWidget::wheelEvent(QWheelEvent *event)
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


void QSttIecSmvWaveWidget::paintEvent(QPaintEvent *event)
{
	CDC oDC(this);
	oDC.begin(this);
	CViewAnalyse::OnDraw(&oDC);
	oDC.end();
#ifdef _PSX_QT_LINUX_
	if (!g_pSttIecRecordCbWidget->IsTabUI_Mode())
	{
		updateGeometry();
	} 
#else
	updateGeometry();
#endif
}


void QSttIecSmvWaveWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
 	UICreate(this);
 	CViewAnalyse::OnSizeEx(0, 0, 0);
 	DrawAnalyse();
}

LRESULT QSttIecSmvWaveWidget::OnVariableAddRemoved(WPARAM wParam, LPARAM lParam)
{
	m_pRecordTest = g_theXSmartCapMngr->GetRecordTest();

	if (m_pRecordTest == NULL)
	{
		return 0;
	}

	SetCapDeviceChRecordMngr(g_theXSmartCapMngr->GetCapDeviceChRecordMngr());

	long nBinarys = 0;
	long nAnalogs = 0;
	long nChsCount = 0;
	BOOL bNeedAdjust = FALSE;

	RemoveAll();
	m_oVariableMngr.DeleteAll();
	CDrawVariable *pDrawVariable = NULL;
	CCapDeviceChBase *pCh = NULL;
	//CRtVariables *pVariables = m_pRecordTest->m_pVariables;  //2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
	CRtVariable* pVariable =NULL;
	long nAnalogChanAmount = 0;
	long nCurrentChans = 0;
	long nIndex = m_nCurrRcdChIndex;

	for (nIndex=m_nCurrRcdChIndex; ; nIndex++)
	{
		//pVariable = (CRtVariable*)pVariables->GetAtIndex(nIndex);//2022-6-12  lijunqing  ֻ��ʾ��ǰCapDevice��ͨ��
		pVariable = (CRtVariable*)m_listRcdVariable.GetAtIndex(nIndex);

		if (pVariable == NULL)
		{
			break;
		}

		if (! pVariable->CanCal())
		{
			continue;
		}

		pDrawVariable = AddAnalogDrawVariable(pVariable, nCurrentChans, nAnalogChanAmount);

		if (NULL == pDrawVariable)
		{
			continue;
		}

		pDrawVariable->m_strName = pVariable->m_strID;
		pDrawVariable->m_strID = pVariable->m_strID;
		nAnalogChanAmount++;
		nCurrentChans++;

		if (nCurrentChans >= STT_IECRCD_WAVE_CHS_PAGE)
		{
			break;
		}
	}

	pDrawVariable = (CDrawVariable *)GetHead();
	bNeedAdjust = TRUE;

	//InitCapViewDraw();
	//OnSizeEx(0, 0, 0);
	InitTimeAxis();

	return 0;
}

void QSttIecSmvWaveWidget::UpdateDrawVariablesRange()
{
	POS pos = m_oVariableMngr.GetHeadPosition();
	CDrawAnalogVariable *pDrawVariable = NULL;
	CRtSingleVariable* pSingle = NULL;
	double dCurrVal = 0;
	double dRange = 0;
	
	while (pos != NULL)
	{
		pDrawVariable = (CDrawAnalogVariable *)m_oVariableMngr.GetNext(pos);
		pSingle = (CRtSingleVariable*)pDrawVariable->m_pXDrawDataRef;
		dCurrVal = pSingle->m_oCurrValue.dEffecValue;
		dRange = pDrawVariable->GetRange();

		if (dCurrVal > dRange)
		{
			pDrawVariable->SetRange(dCurrVal);
		}
		else if (dRange > (2*dCurrVal))//20220625 zhouhj �����ǰ��Чֵ����2�����������ֵʱ,�����̽��е���
		{
			pDrawVariable->SetRange(dCurrVal*1.2);
		}
	}
}

void QSttIecSmvWaveWidget::SetDrawVariablesRange()
{
	POS pos = m_oVariableMngr.GetHeadPosition();
	CDrawAnalogVariable *pDrawVariable = NULL;
	CRtSingleVariable* pSingle = NULL;
	double dCurrVal = 0;

	while (pos != NULL)
	{
		pDrawVariable = (CDrawAnalogVariable *)m_oVariableMngr.GetNext(pos);
		pSingle = (CRtSingleVariable*)pDrawVariable->m_pXDrawDataRef;
		dCurrVal = pSingle->m_oCurrValue.dEffecValue;
		pDrawVariable->SetRange(dCurrVal);
	}
}

//����¼�����ݻ����������ݳ��ȣ������õ�ǰ��ʾ�Ĳ��εĳ���
//ͬʱ����ʱ������ķ�Χ
void QSttIecSmvWaveWidget::InitTimeAxis()
{
	m_nSamRateForDraw = m_pRecordTest->g_nSampleRate;

	if (m_pRefBuffer == NULL)
	{
		return ;
	}

	double d1, d2;

	if (! m_bInitTimeAxis)
	{
		m_oTimeAxisDraw.TimeGetAxisRange(d1, d2);
	}

	double dMax = 0;
	double dMin = 0;
//for debug====  8000 �޸���ʾ���ε��ܳ���
    long nDataLen = 8000; //m_pRefBuffer->GetDataLength();  //2022-4-24  lijunqing �ù̶�ʱ�䳤��
	dMax = nDataLen;
	dMax /=  m_nSamRateForDraw;

	MrDraw::ClearDrawBuffBeginEndPos(&m_oOscillographBufferPos);

	if (m_dMaxTimeInOneSreen > dMax) 
	{
		m_dMaxTimeInOneSreen = dMax;
	}

	//if (m_bInitTimeAxis)
	{
		m_dMaxTimeInOneSreen = dMax;
		SetRecordDataTimeLength(dMax);
		m_dMinTimeInOneSreen = (double)g_dwOscillographMinTime / 1000;
		m_oTimeAxisDraw.SetOldMaxMinTime(m_dRecordDataTimeLength,0);
		m_oTimeAxisDraw.SetMaxMinTime(dMax,0);
	}

	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.FrozenCenter(TRUE);
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.FrozenHead1(TRUE);

	//��ʼ����ǰ��ͼ�ı������������õ�ǰѡ�б���
	AdjustAllDrawObjectsPos();

	AdjustDrawVariablePosition();
	ReCompositor();

	//��ʼ��MEMDC����ʼ��CDrawMr1200RecordBase����
	InitByBorder();


	//������������ͼ��λ��
	CRecordTestDrawBase::AdjustDrawVariablePosition();
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetLockHead(FALSE);

	if (! m_bInitTimeAxis)
	{
		m_oTimeAxisDraw.TimeSetAxisRange(d1, d2);
		m_oTimeAxisDraw.SetAxisRange(d1, d2);
		CalXPosByTimeAxis(d1, d2);
	}
	else
	{
		CalXPosByTimeAxis();
	}
	
	CalParaRect();
	m_bInitTimeAxis = FALSE;
}

void QSttIecSmvWaveWidget::MoveLeft()
{
	CViewAnalyse::MoveLeft();
	update();
}

void QSttIecSmvWaveWidget::MoveRight()
{
	CViewAnalyse::MoveRight();
	update();
}

void QSttIecSmvWaveWidget::ZoomInChan()
{
	CViewAnalyse::ZoomInChan();
	update();
}

void QSttIecSmvWaveWidget::ZoomOutChan()
{
	CViewAnalyse::ZoomOutChan();
	update();
}

void QSttIecSmvWaveWidget::ZoomInTime()
{
	CViewAnalyse::ZoomInTime(0);
	update();
}

void QSttIecSmvWaveWidget::ZoomOutTime()
{
	CViewAnalyse::ZoomOutTime(1);
	update();
}

void QSttIecSmvWaveWidget::slot_Reset()
{
	m_bUpdateFlag = FALSE;
	IecRcdFunc((CCapDeviceBase *)m_pCapDevice);
	m_bUpdateFlag = TRUE;
}	
