#include "SttCharacterDrawPng.h"

#include "../../../Module/API/Base64.h"
#include <qbuffer.h>
#include <qpainter.h>

CSttCharacterDrawPng::CSttCharacterDrawPng()
{

}

CSttCharacterDrawPng::~CSttCharacterDrawPng()
{
	m_oCurSearchView.DeleteAll();
	m_oSearchPoints.DeleteAll();
}

double CSttCharacterDrawPng::GetValueByID(CDataGroup* pSearchLine, const CString& strID)
{
	CDvmData* pData = (CDvmData*)pSearchLine->FindByID(strID);
	if (pData)
	{
		return CString_To_double(pData->m_strValue);
	}
	return 0;
}

void CSttCharacterDrawPng::DrawCurTestPoint(CDC *pDC, CDataGroup* pSearchLine)
{
	//画当前检测点
	double nCXb = GetValueByID(pSearchLine, "search-x-c");
	double nCXe = GetValueByID(pSearchLine, "search-y-c");
	m_pCharDrawView->UpdateCurrTestPoint(nCXb, nCXe);
//	m_pCharDrawView->FreeCurrTestPoint();
}

void CSttCharacterDrawPng::DrawCurLine(CDC *pDC, CDataGroup* pSearchLine)
{
	//画当前线
	double dXb = GetValueByID(pSearchLine, "x-b");
	double dXe = GetValueByID(pSearchLine, "x-e");
	double dYb = GetValueByID(pSearchLine, "y-b");
	double dYe = GetValueByID(pSearchLine, "y-e");

	CXDrawLine* pLine = new CXDrawLine;
	pLine->SetBeginPoint(dXb, dYb);
	pLine->SetEndPoint(dXe, dYe);
	m_oCurSearchView.AddNewChild(pLine);
}

void CSttCharacterDrawPng::DrawCurTestLine(CDC *pDC, CDataGroup* pSearchLine)
{
	//画当前检测线
	double dXb = GetValueByID(pSearchLine, "search-x-b");
	double dXe = GetValueByID(pSearchLine, "search-x-e");
	double dYb = GetValueByID(pSearchLine, "search-y-b");
	double dYe = GetValueByID(pSearchLine, "search-y-e");

	CXDrawLine* pLine = new CXDrawLine;
	pLine->SetBeginPoint(dXb, dYb);
	pLine->SetEndPoint(dXe, dYe);
	m_oCurSearchView.AddNewChild(pLine);
}

void CSttCharacterDrawPng::DrawCurSearchView(CDC *pDC)
{
	CAxisInterface* pAxis = NULL;
	m_oCurSearchView.InitDrawLineColor(RGB(0,255,0));
	m_pCharDrawView->GetAxisInterface(&pAxis);
	m_oCurSearchView.LogicPointToDevicePoint(pAxis);
	m_oCurSearchView.Draw(pDC, 1, CPoint(0,0));
}

void CSttCharacterDrawPng::DrawSearchPoints(CDC *pDC)
{
	CAxisInterface* pAxis = NULL;
//	m_oSearchPoints.InitDrawLineColor(RGB(255,0,0));//20230816 suyang 根据动作或未动作来区别测试点颜色，会直接影响测试点颜色，所以注销
	m_pCharDrawView->GetAxisInterface(&pAxis);
	m_oSearchPoints.LogicPointToDevicePoint(pAxis);
	m_oSearchPoints.Draw(pDC, 1, CPoint(0,0));
}

void CSttCharacterDrawPng::AddSearchPoint(double dx, double dy,BOOL bAct)
{
	if (m_pCharDrawView != NULL)
	{
		m_pCharDrawView->FreeCurrTestPoint();
	}

	CXDrawPoint* pt = m_oSearchPoints.AddPoint(dx, dy);
	
	if (bAct)
	{
		pt->m_crForeColor = RGB(0, 255, 0);//20240202 suyang 报告里点修改为绿色
	} 
	else
	{
		pt->m_crForeColor = RGB(255, 0, 0);
	}

	pt->m_dwDrawStyle = 1; //x	
}

void CSttCharacterDrawPng::ClearSearchPoints_png(long nPtIndex)
{
	if(nPtIndex == -1)
	{
		m_oSearchPoints.DeleteAll();
	}
	else
	{
		if(m_oSearchPoints.GetCount() > nPtIndex)
		{
			m_oSearchPoints.DeleteAt(nPtIndex);
		}
	}
}

void CSttCharacterDrawPng::ClearSearchPointsFrom_png(long nPtIndex)
{
	long nCount = m_oSearchPoints.GetCount();
	for (int i = nCount - 1; i >= nPtIndex; i--)
	{
		ClearSearchPoints_png(i);
	}
}

void CSttCharacterDrawPng::GetSearchPointsPng(CString& strBase64)
{
	m_pCharDrawView->GetXDrawMngr_Axis()->AdjustAxis(TRUE);

	ReleasePngDraw();
	CreatePngDraw(300, 300);

// 	QByteArray ba;
// 	QString format("png");
// 	QBuffer* buffer = new QBuffer(&ba);
// 	buffer->open(QIODevice::WriteOnly);
// 	QImage image(300, 300, QImage::Format_RGB32);

	CDC oDC;
	oDC.begin(m_pImage);
	OnPaint(&oDC);
	DrawSearchPoints(&oDC);
	oDC.end();

	//image.save(buffer, "png", -1);
	//QString strTemp = ba.toBase64();
	strBase64 = m_strPngBase64;
	m_oSearchPoints.DeleteAll();
	//delete buffer;
}

void CSttCharacterDrawPng::GetSearchingPng(CDataGroup* pSearchLine, CString& strBase64)
{
	if (m_pCharDrawView == NULL)
	{
		return;
	}

//	m_pCharDrawView->FreeCurrTestPoint();
	m_pCharDrawView->GetXDrawMngr_Axis()->AdjustAxis(TRUE);

	ReleasePngDraw();
	CRect rc = m_pCharDrawView->GetBorder();
	CreatePngDraw(rc.Width(), rc.Height());

// 	QByteArray ba;
// 	QString format("png");
// 	QBuffer* buffer = new QBuffer(&ba);
// 	buffer->open(QIODevice::WriteOnly);
// 	QImage image(300, 300, QImage::Format_RGB32);

	CDC oDC;
	oDC.begin(m_pImage);

	if (pSearchLine != NULL)
	{
		DrawCurTestPoint(&oDC, pSearchLine);
		DrawCurTestLine(&oDC, pSearchLine);
		DrawCurLine(&oDC, pSearchLine);
	}

	OnPaint(&oDC);
	DrawCurSearchView(&oDC);
	DrawSearchPoints(&oDC);
	oDC.end();

	//image.save(buffer, "png", -1);
	//QString strTemp = ba.toBase64();
	GetPngBase64();
	strBase64 = m_strPngBase64;

	//清空当前报文对应数据
	m_oCurSearchView.DeleteAll();
	m_pCharDrawView->FreeCurrTestPoint();

// 	if (pSearchLine == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("pSearchLine == NULL"));
// 		CString strPath;
// 		strPath = _P_GetBinPath();
// 		strPath += _T("001.png");
// 		m_pImage->save(strPath);
// 	} 
// 	else
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("pSearchLine != NULL"));
// 	}

	//delete buffer;
}

bool CSttCharacterDrawPng::SavePngFile(const CString &strFilePath)
{
	if (m_pImage == NULL)
	{
		return false;
	}

	m_pImage->save(strFilePath);
	return true;
}

void CSttCharacterDrawPng::InitCharDrawTest(const CString &strCharID, long nIndex)
{
	CCharacteristic *pFind = NULL;
	POS pos = m_pCharacteristics->GetHeadPosition();
	while (pos)
	{
		CCharacteristic *pTemp = (CCharacteristic*)m_pCharacteristics->GetNext(pos);
		if(CString_To_long(pTemp->m_strIndex) == nIndex && pTemp->m_strID == strCharID)
		{
			pFind = pTemp;
			break;
		}
	}

	if (pFind == NULL)
	{
		delete m_pCharDrawView;
		m_pCharDrawView = NULL;
		return;
	}

	//zhouhj 2023.9.16 测试点数量小于0时,更新下曲线图,防止测试参数已经修改
	if ((m_pCharacteristic == pFind)&&(m_oSearchPoints.GetCount()>0))
	{
		return;
	}

	//每次初始化时,都需要清空测试点结果
	ClearSearchPoints_png();
	ClearPngCache();
	BOOL bShowLine = TRUE;

	if (m_nType == Distance)
	{
		bShowLine = FALSE;
	}

	InitCharacterDrawView(pFind,bShowLine);
	m_pCharacteristic = pFind;

	CAxisInterface *pAxisInterface = NULL;
	m_pCharDrawView->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		CDataGroup oAxisConfig;
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_WorkAreaBkColor,(long)RGB(0, 0, 128));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisGridLineColor,(long)RGB(192, 192, 192));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisGridLineColor,(long)RGB(192, 192, 192));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterLineWidth,(long)2);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterColor,(long)RGB(172, 172, 172));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisScaleFont,(long)12);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisNameFont,(long)14);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisTopGap,(long)26);
		pAxisInterface->SetAxisConfig(&oAxisConfig);
	}

	CXDrawMngr* pXDrawMngr = m_pCharDrawView->GetXDrawMngr_Axis();
	pXDrawMngr->InitDrawLineColor(RGB(0, 255, 0));
}