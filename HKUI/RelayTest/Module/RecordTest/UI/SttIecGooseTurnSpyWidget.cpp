#include "SttIecGooseTurnSpyWidget.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGoose.h"

//////////////////////////////////////////////////////////////////////////
QSttIecGooseTurnSpyWidget::QSttIecGooseTurnSpyWidget(QWidget* parent)
#ifdef QT_Wnd_USE_QWIDGET
: CWnd(parent)
#else
: QWidget(parent)
#endif
{
	m_pIecRcdFuncWidget = this;
	m_pWidgetRef = this;

	g_nXBinaryDrawSize = X_BINARY_DRAW_SIZE_LARGE; 
	g_nBinaryDrawMode = BIANRY_DRAW_MODE_CARD_ALLID; 
	g_nBinaryDrawColsCalUseHex_16 = 0;

	m_bIsDrawing = false;
//	m_oGsCapRingDatas.AllocBuffer(GOOSE_TURNSPY_MAX_DATAS_NUM);
}

QSttIecGooseTurnSpyWidget::~QSttIecGooseTurnSpyWidget()
{
//	m_oGsCapRingDatas.FreeBuffer();
}

//重载函数OnWndMsg，实现消息处理
void QSttIecGooseTurnSpyWidget::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	if (WM_UPDATE_GOOSE_SPY == nMsgID)
	{
		//如果goose报文太过频繁，可能会导致绘图卡顿，后续在考虑
		//如果绘图过程中，则丢弃此消息，或者记录消息，如果消息没有被处理，则在定时器中绘制

// 		if (m_pCapDevice == NULL)
// 		{
// 			return;
// 		}
// 
// 		PEPCAPPARSEDATAS pDatas = (PEPCAPPARSEDATAS)wParam;
// 
// 		if (pDatas->APPID != ((CCapDeviceGoose*)m_pCapDevice)->m_dwAppID)
// 		{
// 			return;
// 		}
// 
// 		long nWritePos = m_oGsCapRingDatas.GetWritePos();
// 		m_oGsDatas[nWritePos] = *pDatas;
// 		m_oGsCapRingDatas.Add(&m_oGsDatas[nWritePos]);
	}
}


void QSttIecGooseTurnSpyWidget::OnWndTimer(unsigned int nIDEvent) 
{

}




void QSttIecGooseTurnSpyWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	if (m_pCapDevice != NULL)
	{
		((CCapDeviceGoose*)m_pCapDevice)->AttachXWndInterface(NULL);
	}

	m_pCapDevice = pCapDevice;
	((CCapDeviceGoose*)m_pCapDevice)->AttachXWndInterface(this);
	m_oDatas.oDataGs.nChCnt = 0;
//	m_oGsCapRingDatas.Clear();
	CCapDeviceGoose *pGsDevice = (CCapDeviceGoose*)m_pCapDevice;
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前AppID=0x%04X,总通道数(%ld)."),pGsDevice->m_dwAppID,pGsDevice->GetCount());
	m_oSttIecGsBinaryDrawView.XCreateElement(pCapDevice->GetCount(), &m_oDatas, this);

	if (!DrawTurnSpy())
	{
		repaint();
	}
}

void QSttIecGooseTurnSpyWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CCapDeviceGoose *pGsDevice = (CCapDeviceGoose*)m_pCapDevice;
// 	long nChNum = pGsDevice->GetCount();
// 
// 	if (nChNum>STCAPPARSE_DATA_MAX_COUNT)
// 	{
// 		nChNum = STCAPPARSE_DATA_MAX_COUNT;
// 	}

	m_oDatas = pGsDevice->m_oPrevDatas;

//	memcpy(m_oDatas.oDataGs.chData,pGsDevice->m_oPrevDatas.oDataGs.chData,sizeof(EPGOOSECHDATA)*nChNum);
	DrawTurnSpy();
/* //测试绘图用的代码：此监视部分，是通过消息进行刷新的，收到一个goose报文，就刷新一次
	CCapDeviceGoose *pGsDevice = (CCapDeviceGoose*)m_pCapDevice;
	long nCount = pGsDevice->GetCount();
	long nIndex = 0;
	EPCAPPARSEDATA *pDatas = m_oDatas.pDatas;
	long nTypeArr[4] = { 0x83, 0x84, 0x85, 0x87};
	long nTemp;


	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		nTemp = rand() % 4;
		nTemp = nTypeArr[nTemp];

		pDatas[nIndex].wChType = nTemp;

		if (nTemp == 0x83)
		{
			pDatas[nIndex].dwValue = rand() % 2;
		}
		else if (nTemp == 0x84)
		{
			pDatas[nIndex].dwValue = rand() % 4;
		}
		else
		{
			pDatas[nIndex].dwValue = rand();
		}
	}

	DrawTurnSpy();
*/
}

void QSttIecGooseTurnSpyWidget::Release()
{
	if (m_pCapDevice != NULL)
	{
		((CCapDeviceGoose*)m_pCapDevice)->AttachXWndInterface(NULL);
		m_pCapDevice = NULL;
	}

	DestroyWindow();

	delete this;
}

void QSttIecGooseTurnSpyWidget::paintEvent(QPaintEvent *event)
{
	CDC oDC(this);
	oDC.begin(this);
	
	m_oSttIecGsBinaryDrawView.Draw(&oDC, 1, CPoint(0, 0), 0xFFFFFFFF);

	oDC.end();
	updateGeometry();
	m_bIsDrawing = false;
}

void QSttIecGooseTurnSpyWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = 	geometry();

	m_oSttIecGsBinaryDrawView.OnSize(rc.width(), rc.height());
	DrawTurnSpy();
}

BOOL QSttIecGooseTurnSpyWidget::DrawTurnSpy()
{
	if(m_bIsDrawing)
	{
		return FALSE;
	}

	m_bIsDrawing = true;
	repaint();
	return TRUE;

// 	EPCAPPARSEDATAS *pCurrCapDatas = NULL;
// 	EPCAPPARSEDATAS *pFindCapDatas = NULL;
// 
// 	while(m_oGsCapRingDatas.CanRead())
// 	{
// 		pCurrCapDatas = m_oGsCapRingDatas.Read();
// 
// 		for (int nIndex = 0; nIndex< pCurrCapDatas->oDataGs.nChCnt; nIndex++)
// 		{
// 			if ((pCurrCapDatas->oDataGs.chData[nIndex].wChType != 0x83)&&(pCurrCapDatas->oDataGs.chData[nIndex].wChType != 0x84))//20220627 zhouhj 只比较单点和双点数据类型
// 			{
// 				continue;
// 			}
// 
// 			if (m_oDatas.oDataGs.chData[nIndex].wChType != pCurrCapDatas->oDataGs.chData[nIndex].wChType
// 				|| m_oDatas.oDataGs.chData[nIndex].dwValue != pCurrCapDatas->oDataGs.chData[nIndex].dwValue)
// 			{
// 				pFindCapDatas = pCurrCapDatas;
// 				break;
// 			}
// 		}
// 
// 		if (pFindCapDatas)
// 		{
// 			break;
// 		}
// 	}
// 
// 	if(pFindCapDatas)
// 	{
// 		m_bIsDrawing = true;
// 		m_oDatas = *pFindCapDatas;
// 		repaint();
// 	}
// 
// 	return (pFindCapDatas != NULL);
}

