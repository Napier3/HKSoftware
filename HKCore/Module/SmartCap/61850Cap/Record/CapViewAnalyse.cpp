// CapViewAnalyse.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CapViewAnalyse.h"
#include "../../XSmartCapMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCapViewAnalyse::CCapViewAnalyse()
{
	m_pCapDeviceChRecordMngr = NULL;
}

CCapViewAnalyse::~CCapViewAnalyse()
{


}

void CCapViewAnalyse::SetCapDeviceChRecordMngr(CCapDeviceChRecordMngr *p)	
{
	if (p == NULL)
	{
		return;
	}

	m_pRecordTest = p->m_pRecordTest;
	m_pCapDeviceChRecordMngr = p;
	m_pRecordTest->m_pWaveAnalyseViewRef = this;
	m_pRecordDrawObjcontrol = m_pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl;
}


// 
// CDrawVariable* CCapViewAnalyse::CreateVariable(CCapDeviceChRecord *pVariable, long &nCurrentChans, long &nAnalogChanAmount, long &nBinaryChanAmount)
// {
// 	UINT nClassID = pVariable->GetClassID();
// 	CMemBuffer_UShort* pSpyBufferPre = NULL;
// 	CMemBuffer_UShort* pHoldBufferPre = NULL;
// 	CDrawVariable *pDrawVariable = NULL;
// 
// 	if(nClassID == CPDCLASSID_SMVCH)//开关通道
// 	{
// 		pDrawVariable = CreateAnalogVar((CCapDeviceSmvChRecord*)pVariable,nCurrentChans);
// 		nAnalogChanAmount++;
// 		nCurrentChans++;
// 	}
// 	else if (nClassID == CPDCLASSID_GOOSECH) //单信号通道
// 	{
// 		pDrawVariable = CreateBinaryVar((CCapDeviceGooseChRecord*)pVariable,nCurrentChans);
// 		nCurrentChans++;
// 		nBinaryChanAmount++;
// 	}
// 	else 
// 	{
// 	}
// 
// 	return pDrawVariable;
// }
// 
// 
// CDrawVariable* CCapViewAnalyse::CreateAnalogVar(CCapDeviceSmvChRecord* pSingle,long nIndex)
// {
// 	CMemBuffer_Long* pSpyBuffer = pSingle->GetRecordBuffer();
// 	CDrawAnalogVariable *pDrawVariable = new CDrawAnalogVariable();
// 	//pDrawVariable->m_nVariableIndex = nIndex;
// 
// 	pDrawVariable->m_crColor = pSingle->m_crColor;
// 	pDrawVariable->m_pptAttachBuffer = m_pPointBuffer;//关联绘图缓存
// 	pDrawVariable->SetAdjustValue(NULL, pSingle->GetChRate());
// 	pDrawVariable->m_strName = pSingle->GetName();//模拟量名称
// 
// 	m_ppSpyBuffer[nIndex] = pSpyBuffer;
// 	pDrawVariable->m_pnAttachBuffer = pSpyBuffer;//初始化数据缓存
// 	PDRAWVAR pVar = &(g_oStSysAnalyseMngr.oDrawVars[nIndex]);
// 	pVar->nShow = pSingle->m_pRecfCh->m_nSelect;
// 	pVar->nUse = pSingle->m_pRecfCh->m_nSelect;
// 	pVar->m_pnMaxValue = &pSingle->m_nMaxValue;
// 	pVar->m_pnMinValue = &pSingle->m_nMinValue;
// 
// 	m_oVariableMngr.AddTail(pDrawVariable);	
// 	//pDrawVariable->SetSelect(TRUE);
// 	pDrawVariable->SetShow(pVar->nShow);
// 	pDrawVariable->SetUse(pVar->nShow);
// 
// 	UINT nChType = pSingle->GetChType();
// 	pDrawVariable->m_strName.Format(_T("通道%d"), nIndex+1);
// 	pDrawVariable->m_strID = pDrawVariable->m_strName;
// 
// #ifdef _SHOW_PARA			
// 	pDrawVariable->AddPara(0);
// #endif
// 
// 	pDrawVariable->SetAttachStruct(pVar);
// 
// 	return pDrawVariable;
// }
// 
// CDrawVariable* CCapViewAnalyse::CreateBinaryVar(CCapDeviceGooseChRecord* pBinary,long nIndex)
// {
// 	CMemBuffer_UShort* pSpyBuffer = pBinary->GetRecordBuffer();
// 
// 	CDrawBinaryVariable* pDrawVariable = new CDrawBinaryVariable();//创建开关量绘图对象
// 
// 	pDrawVariable->m_crColor = pBinary->m_crColor; 
// 	pDrawVariable->m_strName = pBinary->GetName();//开关量名称
// 	pDrawVariable->m_pptAttachBuffer = m_pPointBuffer;//关联绘图缓存
// 	pDrawVariable->m_nChanIndex = 0;//pBinary->m_nIndex;//索引				
// 	m_ppSpyBuffer[nIndex] = pSpyBuffer;   
// 	pDrawVariable->m_pnAttachBuffer = pSpyBuffer;//初始化数据缓存
// 
// 	PDRAWVAR pVar = &(g_oStSysAnalyseMngr.oDrawVars[nIndex]);
// 	pVar->nShow = 1;
// 	pVar->nUse = 1;
// 
// 	pDrawVariable->SetUse(1);
// 	pDrawVariable->SetShow(pVar->nShow);
// 	pDrawVariable->SetSelect(TRUE);
// 
// 	m_oVariableMngr.AddTail(pDrawVariable);	
// 	pDrawVariable->SetAttachStruct(pVar);
// 	return pDrawVariable;
// }

void CCapViewAnalyse::ShowAllRecordCh()
{
	CAutoSimpleLock oLock(g_oCapDeviceChRecordCriticSection);
	m_pRecordTest->AdjustRefVariable();
	InitDrawVariablesByRecordTest();
	//InitDrawVariableShow();
	InitCapViewDraw();
	OnSizeEx(0, 0, 0);
}

void CCapViewAnalyse::InitDrawVariableShow()
{
	POS  pos = m_oVariableMngr.GetHeadPosition();
	CDrawVariable *pVariable = NULL;
	long nIndex = 0;
	long nUse = 0;
	
	while (pos != NULL)
	{
		pVariable = (CDrawVariable*)m_oVariableMngr.GetNext(pos);
		nUse = pVariable->GetUse();
		pVariable->SetShow(nUse);
		m_pRecordDrawObjcontrol[nIndex].nShow = nUse;
		m_pRecordDrawObjcontrol[nIndex].nUse = nUse;
	}
}

void CCapViewAnalyse::InitCapViewDraw()
{
	if (m_pCapDeviceChRecordMngr == NULL) 
	{
		return;
	}

	long nDataLen = 8000;   //CAP_RECORD_POINTS;  //最多两秒钟  lijunqing 2022-04024
	m_nSamRateForDraw = 4000; //周波点数为80
	double dMax = 0,dMin =0;
	dMax = nDataLen;
	dMax /=  m_nSamRateForDraw;

	SetRecordDataTimeLength(dMax);
	m_dMinTimeInOneSreen = (double)g_dwOscillographMinTime / 1000;
	m_oTimeAxisDraw.SetOldMaxMinTime(m_dRecordDataTimeLength,0);
	SetMaxShowOneSreen(dMax);
	m_oTimeAxisDraw.SetMaxMinTime(m_dMaxTimeInOneSreen,dMin);

	MrDraw::ClearDrawBuffBeginEndPos(&m_oOscillographBufferPos);

	int nAnalogs = 0;
	int nBinarys = 0;
	m_dOscillographTimeLong = dMax;

	m_pRefBuffer = GetDefaultRefBuffer();

	if (nAnalogs > 0 || nBinarys > 0)//初始化第一个为选中通道
	{
		POS  pos = m_oVariableMngr.GetHeadPosition();
		m_pCurrDrawVariable = (CDrawVariable*)m_oVariableMngr.GetAt(pos);
		m_pCurrDrawVariable->SetSelect(TRUE);
	}


	//初始化当前绘图的变量，包括设置当前选中变量
	AdjustAllDrawObjectsPos();

	AdjustDrawVariablePosition();
	ReCompositor();

	//初始化MEMDC，初始化CDrawMr1200RecordBase区域
	InitByBorder();

	//调整各变量绘图的位置
	CRecordTestDrawBase::AdjustDrawVariablePosition();
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetLockHead(FALSE);
	CalXPosByTimeAxis();
	CalParaRect();
}

void CCapViewAnalyse::ShowRecordCh(CCapDeviceChRecord* pRecord)
{
	
}

void CCapViewAnalyse::HideRecordCh(CCapDeviceChRecord* pRecord)
{

}

