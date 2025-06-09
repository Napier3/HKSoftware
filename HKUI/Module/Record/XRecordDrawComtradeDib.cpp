//XRecordDrawComtradeDib.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRecordDrawComtradeDib.h"
#include "../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXRecordDrawComtradeDib::CXRecordDrawComtradeDib()
{
	CXRecordDrawBase::g_bDibDrawUseChannelColor = TRUE;
	MrDraw::g_snWaveDrawAreaGap = 1;
	ZeroMemory(&m_oDrawControl, sizeof(RECORDDRAWOBJECTCONTROL) * MAX_DRAW_VARIABLE);
	m_pRecordDrawObjcontrol = m_oDrawControl;
	m_pPointBuffer = NULL;
	InitDrawPoints(AnalyseWnd_MaxDrawlength);
	m_pRcdComtradeFile = NULL;
}

CXRecordDrawComtradeDib::~CXRecordDrawComtradeDib()
{
	m_oDibDraw.FreeDraw();
}

void CXRecordDrawComtradeDib::ComtradeDib(CWnd *pWnd)
{
	ComtradeDib();
	m_oDibDraw.CopyToClipboard(pWnd->m_hWnd);
}

void CXRecordDrawComtradeDib::ComtradeDib()
{
	long nTotalPoints = m_pRcdComtradeFile->GetTotalPoints();

	MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
	m_oDrawBufferPos.nGap = nTotalPoints / AnalyseWnd_MaxDrawlength;

	if (m_oDrawBufferPos.nGap * AnalyseWnd_MaxDrawlength < nTotalPoints)
	{
		m_oDrawBufferPos.nGap++;
	}

	m_oDrawBufferPos.nBufLength = nTotalPoints;
	SetDrawDataRange(0,nTotalPoints  - 1);
	CalXPos(nTotalPoints);

	DibDraw(m_oDibDraw, 0X0000000F);
}

void CXRecordDrawComtradeDib::CopyToClipboard(CWnd *pWnd)
{
	m_oDibDraw.CopyToClipboard(pWnd->m_hWnd);
}

void CXRecordDrawComtradeDib::WriteBmpFile(const CString &strBmpFile)
{
	m_oDibDraw.WriteToFile(strBmpFile);
}

CDrawBinaryVariable* CXRecordDrawComtradeDib::AddDrawVariable_Binary(CComtradeBinaryData* pBinary, long &nCurrentChans, PRECORDDRAWOBJECTCONTROL pDrawControl)
{
	CDrawVariable* pDrawVariable = NULL;
	CMemBuffer_UShort* pRecordBuffer = pBinary->GetMemBuffer_UShort();
	ASSERT (pRecordBuffer != NULL);

	if (pRecordBuffer == NULL)
	{
		return NULL;
	}

	pDrawVariable = new CDrawBinaryVariable();//创建开关量绘图对象
	CDrawBinaryVariable* pDrawBinary = (CDrawBinaryVariable*)pDrawVariable;	

	pDrawBinary->m_crForeColor = RGB(0, 0, 0); 
	pDrawBinary->m_strName = pBinary->m_strName;//开关量名称
	pDrawBinary->m_strID = pBinary->m_strName;//开关量名称
	pDrawBinary->m_pptAttachDrawBuffer = m_pPointBuffer;//关联绘图缓存
	pDrawBinary->m_nChanIndex = nCurrentChans;//索引				
	pDrawBinary->m_pnAttachBuffer = pRecordBuffer;//初始化数据缓存	
	pDrawBinary->SetUse(1);
	pDrawBinary->m_nShow = 1;
	pDrawBinary->SetParentWnd(m_pParentWnd);
	//m_oVariableMngr.AddTail(pDrawVariable);
	pDrawBinary->SetSelect(FALSE);
	AddTail(pDrawBinary);

	return pDrawBinary;
}

CDrawAnalogVariable* CXRecordDrawComtradeDib::AddDrawVariable_Analog(CComtradeAnalogData* pAnalogData, long &nCurrentChans, PRECORDDRAWOBJECTCONTROL pDrawControl)
{
	CMemBuffer_UShort* pRecordBuffer = pAnalogData->GetMemBuffer_UShort();
	CDrawAnalogVariable* pAnalog = new CDrawAnalogVariable();
	ASSERT (pRecordBuffer != NULL);
	double dRange = pAnalogData->GetRange();
	dRange = MrDraw::GetFloatCarryValue2(dRange);

	pAnalog->m_strPhaseID = pAnalogData->m_strPhaseID;
	pAnalog->m_strUnit = pAnalogData->m_strUnit;

	pDrawControl->dRange = dRange;
	pAnalog->m_nShow = 1;
	pAnalog->SetRange(dRange);	
	pAnalog->SetUse(1);
	pAnalog->m_crForeColor = RGB(255, 0, 0);//GetPhaseColorByPhaseID(pAnalogData->m_strPhaseID, pAnalogData->m_strID);
	pAnalog->m_pptAttachDrawBuffer = m_pPointBuffer;//关联绘图缓存
	pAnalog->SetAdjustValue(&pAnalogData->m_dZeroValue, &pAnalogData->m_dCoefValue);
	pAnalog->m_strName = pAnalogData->m_strName;//模拟量名称
	pAnalog->m_strID = pAnalogData->m_strName;//模拟量名称
	pAnalog->m_pnAttachBuffer = pRecordBuffer;//初始化数据缓存
	pAnalog->SetParentWnd(m_pParentWnd);
	pAnalog->SetSelect(FALSE);
	AddTail(pAnalog);

	return pAnalog;
}

void CXRecordDrawComtradeDib::InitByComtrade(CRcdComtradeFile *pComtradeFile, long nWidth, long nHeight, BOOL bUseBinary)
{
	m_oDibDraw.CreateDraw(nWidth, nHeight);
	m_pRcdComtradeFile = pComtradeFile;

	InitVariablesByComtrade(pComtradeFile, bUseBinary);
	InitRecordDraw(nWidth, nHeight);
}

//2021-1-16  lijunqing
void CXRecordDrawComtradeDib::InitByRcdDrawFile(const CString &strRcdDrawFile, long nWidth, long nHeight, BOOL bUseBinary)
{
	m_oXRcdAnalysisDrawMngr.DeleteAll();
	BOOL bRet = m_oXRcdAnalysisDrawMngr.OpenXmlFile(strRcdDrawFile, CXDrawXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		return;
	}

	CString strComtradeFile = m_oXRcdAnalysisDrawMngr.m_strID;

	if (! IsFileExist(strComtradeFile))
	{
		strComtradeFile = GetFileNameFromFilePath(strComtradeFile);
		strComtradeFile = GetPathFromFilePathName(strRcdDrawFile) + strComtradeFile;

		if (! IsFileExist(strComtradeFile))
		{
			return;
		}
	}

	CRcdComtradeFile *pComtradeFile = CRcdComtradeFileMngr::OpenComtradeFile(m_oXRcdAnalysisDrawMngr.m_strID);
	InitByComtrade(pComtradeFile, nWidth, nHeight, bUseBinary);

	//初始化各绘图Variable的绘图元素
	AdjustRcdAnalysisDrawMngr();
}

//调整绘图对象  2021-2-19  lijunqing
void CXRecordDrawComtradeDib::AdjustRcdAnalysisDrawMngr()
{
	POS pos = GetHeadPosition();
	CDrawVariable *pVariable = NULL;
	CXDrawList *pDrawList = NULL;

	while (pos != NULL)
	{
		pVariable = (CDrawVariable *)GetNext(pos);
		pDrawList = (CXDrawList*)m_oXRcdAnalysisDrawMngr.FindByID(pVariable->m_strID);
		pVariable->SetDrawList(pDrawList);

		if (pDrawList != NULL)
		{
			m_oXRcdAnalysisDrawMngr.Remove(pDrawList);
		}
	}
}

void CXRecordDrawComtradeDib::InitVariablesByComtrade(CRcdComtradeFile *pComtradeFile, BOOL bUseBinary)
{
	POS pos = pComtradeFile->GetHeadPosition();
	long nAnalogChanAmount = 0;
	long nBinaryChanAmount = 0;
	long iIndex = 0;
	CComtradeDataBase* pComtradeData = NULL;
	CDrawVariable *pDrawVariable = NULL;
	long nVariableIndex = 0;
	PRECORDDRAWOBJECTCONTROL p = NULL;

	while (pos != NULL)
	{
		pComtradeData = (CComtradeDataBase*)pComtradeFile->GetNext(pos);
		p = &(m_pRecordDrawObjcontrol[nVariableIndex]);
		p->nUse = 1;
		p->nShow = 1;
		pDrawVariable = NULL;

		if (pComtradeData->IsAnalogData())
		{		
			pDrawVariable = AddDrawVariable_Analog((CComtradeAnalogData*)pComtradeData, nAnalogChanAmount, p);
			nAnalogChanAmount++;
		}
		else
		{
			if (bUseBinary)
			{
				pDrawVariable = AddDrawVariable_Binary((CComtradeBinaryData*)pComtradeData, nBinaryChanAmount, p);
				nBinaryChanAmount++;
			}
		}

		if (pDrawVariable != NULL)
		{
			pDrawVariable->SetAttachStruct(p);
			nVariableIndex++;
		}
	}

	InitSysAnalyseMngrDrawControl(m_pRecordDrawObjcontrol, nAnalogChanAmount, nBinaryChanAmount);

	//2021-1-16  lijunqing
	AttatchAxisX();

	m_oTimeAxisDraw.m_oTimeAxis.m_strRulerName = _T("S");
}

void CXRecordDrawComtradeDib::InitRecordDraw(long nWidth, long nHeight)
{
	long nDataLen = m_pRcdComtradeFile->m_pnDataPoints[0];
	m_nSamRateForDraw = (long)(m_pRcdComtradeFile->m_pdSamRate[0]);
	double dMax = 0,dMin =0;
	dMax = nDataLen;
	dMax /=  m_nSamRateForDraw;
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);

	//初始化MEMDC，初始化CDrawMr1200RecordBase区域
	InitByBorder(nWidth, nHeight);

}


//创建MemDC，设置绘图区域
void CXRecordDrawComtradeDib::InitByBorder(long nWidth, long nHeight)
{
	CRect rc(0, 0, nWidth, nHeight);
	//InitRecordDrawObjectPosByControl();

	CDC oDC;
	HDC hdc = m_oDibDraw.GetDrawDC();
	oDC.Attach(hdc);
	SetBorder(&oDC, rc);
	oDC.Detach();

	if (m_pTimeCursorDraw)
	{
		m_pTimeCursorDraw->SetBorder(m_rcWaveDraw);
	}

}
