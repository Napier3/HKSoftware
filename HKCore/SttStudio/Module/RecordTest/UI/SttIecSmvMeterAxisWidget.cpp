#include "SttIecSmvMeterAxisWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"

#define STT_MeterAxis_Max_Width  220
#define STT_MeterAxis_Title_Height  40

//////////////////////////////////////////////////////////////////////////
//CSttSttIecSmvMeterAxisDraw
CSttSttIecSmvMeterAxisDraw::CSttSttIecSmvMeterAxisDraw()
{
	m_pAvgValueRef = NULL;
	m_oMeterAxis.SetAngleRange(180, 360);
	m_oMeterAxis.SetRange(-1, 1);
	m_oMeterAxis.SetTicks(3);
	m_oMeterAxis.SetDrawBackground(FALSE);
	//m_oMeterAxis.SetDrawTicks(FALSE);
	//m_oMeterAxis.SetColorTick(FALSE);

	m_oMeterAxis.SetColorTable(0, RGB(0, 255, 0));
	m_oMeterAxis.SetColorTable(1, RGB(255, 201, 14));
	m_oMeterAxis.SetColorTable(2, RGB(128, 0, 64));
	m_bEnable = TRUE;
}

CSttSttIecSmvMeterAxisDraw::~CSttSttIecSmvMeterAxisDraw()
{

}

void CSttSttIecSmvMeterAxisDraw::InitByData(CDvmData *pData)
{
	m_pAvgValueRef = pData->FindByID_MmsAttr(_T("$DC"));//$avg 改为$DC
	m_strChName = pData->m_strName;
}

void CSttSttIecSmvMeterAxisDraw::SetBoder(const CRect &rcBoder)
{
	m_rcMeterAxis = rcBoder;
	m_oMeterAxis.SetBoder(rcBoder);
}

void CSttSttIecSmvMeterAxisDraw::DrawMeter(CDC *pDC, unsigned long crText, unsigned long crBack)
{
	if (!m_bEnable)
	{
		return;
	}

	if (m_strChName.GetLength() > 0)
	{
		CRect rcText = m_rcMeterAxis;
		rcText.bottom = rcText.top + STT_MeterAxis_Title_Height;
		LOGFONT oLogFont;
		oLogFont = InitLogFont ();
		oLogFont.lfHeight = 14;
		CFont oFont;
		oFont.CreateFontIndirect(&oLogFont);
		CFont *pFontOld = pDC->SelectObject(&oFont);

		CmDrawTextRect(pDC, m_strChName, crText, rcText, crBack, oLogFont, TRANSPARENT, DT_TOP | DT_CENTER, 0);

		pDC->SelectObject(oFont);
	}

	m_oMeterAxis.DrawMeterBack(pDC);
}

void CSttSttIecSmvMeterAxisDraw::DrawValue(CDC *pDC)
{
	if (!m_bEnable)
	{
		return;
	}

	if (m_pAvgValueRef == NULL)
	{
		if (fabs(m_oMeterAxis.GetValue())>0.001)
		{
			m_oMeterAxis.SetValue(0);
		}

		return;
	}

	double dValue = CString_To_double(m_pAvgValueRef->m_strValue);

	if (dValue <= -0.1)
	{
		m_oMeterAxis.SetValue(-1);
	}
	else if (dValue < 0.1)
	{
		m_oMeterAxis.SetValue(0);
	}
	else
	{
		m_oMeterAxis.SetValue(1);
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s(%lf)."),m_pAvgValueRef->m_strID.GetString(),dValue);
	m_oMeterAxis.DrawValue(pDC);
}

//////////////////////////////////////////////////////////////////////////
//QSttIecSmvMeterAxisWidget
QSttIecSmvMeterAxisWidget::QSttIecSmvMeterAxisWidget(QWidget *parent)
    : QWidget(parent)
{
	m_pIecRcdFuncWidget = this;
	m_nCurrPageIndex = 0;

	m_pDC = NULL;
	m_crBkColor = RGB(0, 0, 0);
	m_nRows = 0;
	m_nCols = 0;

	m_nHorzGap = 0;
	m_nVertGap = 0;
	m_nHeightDraw = 0;
	m_nWidthDraw = 0;
	m_bIsDrawing = false;

}

QSttIecSmvMeterAxisWidget::~QSttIecSmvMeterAxisWidget()
{
	if (m_pDC != NULL)
	{
		m_pDC->end();
		delete m_pDC;
	}

	m_listPolarDraw.RemoveAll();
}

void QSttIecSmvMeterAxisWidget::CreateDC()
{
	if (m_pDC != NULL)
	{
		return;
	}

	m_pDC = new CDC(this);
	m_pDC->begin(this);
}


void QSttIecSmvMeterAxisWidget::CreateMemDC()
{
	CRect rcClient;
	QRect rc1 = geometry();
	rcClient.bottom = rc1.height();
	rcClient.right = rc1.width();
	rcClient.left = 0;
	rcClient.top = 0;

	CalDrawPages(rcClient);

	BOOL b = m_oMeterDrawDC.Create(m_pDC, rcClient);
	m_oMeterDrawDC->GetDC();

	if (b)
	{
		m_oMeterDrawDC.FillSolidRect(m_crBkColor);
		DrawBackgroud();
	}
}

void QSttIecSmvMeterAxisWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	
	if (pDvmDataset == NULL)
	{
		return;
	}

	m_listPolarDraw.RemoveAll();

	POS pos = pDvmDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CSttSttIecSmvMeterAxisDraw *pPolarDraw = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDvmDataset->GetNext(pos);
		m_listPolarDraw.AddTail(pData);
	}

	m_nCurrPageIndex = 0;

	if (m_oPageDraw.GetCount()>0)
	{
		InitCurrPageDraw();
		DrawBackgroud();
		update();
		m_bIsDrawing = true;
	}
}

void QSttIecSmvMeterAxisWidget::CalDrawPages(const CRect &rcBorder)
{
	long nWidth = rcBorder.Width();
	long nHeight = rcBorder.Height();
	m_nWidthDraw = STT_MeterAxis_Max_Width;
	m_nHeightDraw = (STT_MeterAxis_Max_Width / 2 + STT_MeterAxis_Title_Height);

	double dWidthCoef = nWidth;
	dWidthCoef /= m_nWidthDraw;
	m_nCols = dWidthCoef;
	m_nHorzGap = nWidth - m_nCols * m_nWidthDraw;
	m_nHorzGap = m_nHorzGap / (m_nCols + 1);

	double dHeightCoef = nHeight;
	dHeightCoef /= m_nHeightDraw;
	m_nRows = dHeightCoef;
	m_nVertGap = nHeight - m_nRows * m_nHeightDraw;
	m_nVertGap = m_nVertGap / (m_nRows + 1);

	SetPageDrawCount(m_nRows * m_nCols);
	InitMeterPage();
	InitCurrPageDraw();
}

void QSttIecSmvMeterAxisWidget::SetPageDrawCount(long nNewCount)
{
	long nOldCount = m_oPageDraw.GetCount();

	if (nOldCount == nNewCount)
	{
		return;
	}

	long nCount = 0;
	long nIndex = 0;

	if (nOldCount > nNewCount)
	{
		nCount = nOldCount - nNewCount;
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			m_oPageDraw.DeleteTail();
		}
	}
	else
	{
		nCount = nNewCount - nOldCount;
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			CSttSttIecSmvMeterAxisDraw *pMeter = new CSttSttIecSmvMeterAxisDraw();
			m_oPageDraw.AddTail(pMeter);
		}
	}
}

void QSttIecSmvMeterAxisWidget::InitMeterPage()
{
	CRect rcDraw(0, 0, 0, 0);
	CSttSttIecSmvMeterAxisDraw *pMeter = NULL;
	long nRow=0, nCol=0;
	long nDrawIndex = 0;

	for (nRow=0; nRow<m_nRows; nRow++)
	{
		for (nCol=0; nCol<m_nCols; nCol++)
		{
			pMeter = (CSttSttIecSmvMeterAxisDraw *)m_oPageDraw.GetAtIndex(nDrawIndex);
			nDrawIndex++;

			if (pMeter == NULL)
			{
				break;
			}

			rcDraw.left = m_nHorzGap * (nCol + 1) + STT_MeterAxis_Max_Width * nCol;
			rcDraw.top = m_nVertGap * (nRow + 1) + m_nHeightDraw * nRow;
			rcDraw.right = rcDraw.left + m_nWidthDraw;
			rcDraw.bottom = rcDraw.top + m_nHeightDraw;
			pMeter->SetBoder(rcDraw);
		}

		if (pMeter == NULL)
		{
			break;
		}
	}
}

void QSttIecSmvMeterAxisWidget::InitCurrPageDraw()
{
	long nCount = m_nRows * m_nCols;
	long nIndex = 0;
	long nDrawCount = 0;
	CDvmData *pChData = NULL;
	CSttSttIecSmvMeterAxisDraw *pDraw = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (nDrawCount >= nCount)
		{
			break;
		}

		pChData = (CDvmData *)m_listPolarDraw.GetAtIndex(nIndex + m_nCurrPageIndex);
		pDraw = (CSttSttIecSmvMeterAxisDraw*)m_oPageDraw.GetAtIndex(nIndex);
		nDrawCount++;

		if (pChData == NULL || pDraw == NULL)
		{
			break;
		}

		pDraw->InitByData(pChData);
		pDraw->m_bEnable = TRUE;
	}

	for (; nIndex<nCount; nIndex++)
	{
		pDraw = (CSttSttIecSmvMeterAxisDraw*)m_oPageDraw.GetAtIndex(nIndex);

		if (pDraw == NULL)
		{
			break;
		}

		pDraw->m_bEnable = FALSE;
	}
}

void QSttIecSmvMeterAxisWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	if (m_bIsDrawing)
	{
		return;
	}
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	DrawBackgroud();
	update();
	m_bIsDrawing = true;
}

void QSttIecSmvMeterAxisWidget::Release()
{
	delete this;
}


BOOL QSttIecSmvMeterAxisWidget::NeedNextAndPrev()
{
	return TRUE;
}

void QSttIecSmvMeterAxisWidget::NextPage()
{
	long nPageMaxCount = m_nRows * m_nCols;//当前页面最大容纳个数
	long nPolarDrawTotalCount = m_listPolarDraw.GetCount();
	long nNextIndex = m_nCurrPageIndex + nPageMaxCount;//上一页的起始位置标识加上上一页总数量

	if (nNextIndex >= nPolarDrawTotalCount)//
	{//最后一页，全部元素
		m_nCurrPageIndex = 0;
	}
	else
	{
// 		if (nNextIndex + nPageMaxCount >= nPolarDrawTotalCount)
// 		{
// 			m_nCurrPageIndex = nPolarDrawTotalCount - nPageMaxCount;
// 
// 			if (m_nCurrPageIndex < 0)
// 			{
// 				m_nCurrPageIndex = 0;
// 			}
// 		}
// 		else
		{
			m_nCurrPageIndex = nNextIndex;
		}
	}

	InitCurrPageDraw();
	DrawBackgroud();
	update();
	m_bIsDrawing = true;
}

void QSttIecSmvMeterAxisWidget::PrevPage()
{
	long nCount = m_nRows * m_nCols;
	long nPolarDrawTotalCount = m_listPolarDraw.GetCount();

	if (m_nCurrPageIndex == 0)
	{
		if ((nPolarDrawTotalCount%nCount) == 0)
		{
			m_nCurrPageIndex = nPolarDrawTotalCount - nCount;
		} 
		else
		{
			m_nCurrPageIndex = nPolarDrawTotalCount - (nPolarDrawTotalCount%nCount);
		}

		if (m_nCurrPageIndex < 0)
		{
			m_nCurrPageIndex = 0;
		}
	}
	else
	{
		m_nCurrPageIndex -= m_oPageDraw.GetCount();

		if (m_nCurrPageIndex < 0)
		{
			m_nCurrPageIndex = 0;
		}
	}

	InitCurrPageDraw();
	DrawBackgroud();
	update();
	m_bIsDrawing = true;
}

void QSttIecSmvMeterAxisWidget::paintEvent(QPaintEvent *event)
{
	CDC oDC(this);
	oDC.begin(this);
	
	if (m_oMeterDrawDC->GetBitmap() != NULL)
	{
		m_oMeterDrawDC->Draw(&oDC);
		DrawCurrValues(&oDC);
	}

	oDC.end();
	updateGeometry();
	m_bIsDrawing = false;
}

void QSttIecSmvMeterAxisWidget::DrawBackgroud()
{
	POS pos = m_oPageDraw.GetHeadPosition();
	CSttSttIecSmvMeterAxisDraw *pMeter = NULL;
	m_oMeterDrawDC->FillSolidRect(m_crBkColor);

	while (pos != NULL)
	{
		pMeter = (CSttSttIecSmvMeterAxisDraw *)m_oPageDraw.GetNext(pos);
		pMeter->DrawMeter(m_oMeterDrawDC->GetDC());
	}
}

void QSttIecSmvMeterAxisWidget::DrawCurrValues(CDC *pDC)
{
	POS pos = m_oPageDraw.GetHeadPosition();
	CSttSttIecSmvMeterAxisDraw *pMeter = NULL;

	while (pos != NULL)
	{
		pMeter = (CSttSttIecSmvMeterAxisDraw *)m_oPageDraw.GetNext(pos);
		pMeter->DrawValue(pDC);
	}
}


void QSttIecSmvMeterAxisWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	CreateMemDC();
}
