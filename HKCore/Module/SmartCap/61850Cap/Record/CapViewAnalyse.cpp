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
// 	if(nClassID == CPDCLASSID_SMVCH)//����ͨ��
// 	{
// 		pDrawVariable = CreateAnalogVar((CCapDeviceSmvChRecord*)pVariable,nCurrentChans);
// 		nAnalogChanAmount++;
// 		nCurrentChans++;
// 	}
// 	else if (nClassID == CPDCLASSID_GOOSECH) //���ź�ͨ��
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
// 	pDrawVariable->m_pptAttachBuffer = m_pPointBuffer;//������ͼ����
// 	pDrawVariable->SetAdjustValue(NULL, pSingle->GetChRate());
// 	pDrawVariable->m_strName = pSingle->GetName();//ģ��������
// 
// 	m_ppSpyBuffer[nIndex] = pSpyBuffer;
// 	pDrawVariable->m_pnAttachBuffer = pSpyBuffer;//��ʼ�����ݻ���
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
// 	pDrawVariable->m_strName.Format(_T("ͨ��%d"), nIndex+1);
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
// 	CDrawBinaryVariable* pDrawVariable = new CDrawBinaryVariable();//������������ͼ����
// 
// 	pDrawVariable->m_crColor = pBinary->m_crColor; 
// 	pDrawVariable->m_strName = pBinary->GetName();//����������
// 	pDrawVariable->m_pptAttachBuffer = m_pPointBuffer;//������ͼ����
// 	pDrawVariable->m_nChanIndex = 0;//pBinary->m_nIndex;//����				
// 	m_ppSpyBuffer[nIndex] = pSpyBuffer;   
// 	pDrawVariable->m_pnAttachBuffer = pSpyBuffer;//��ʼ�����ݻ���
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

	long nDataLen = 8000;   //CAP_RECORD_POINTS;  //���������  lijunqing 2022-04024
	m_nSamRateForDraw = 4000; //�ܲ�����Ϊ80
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

	if (nAnalogs > 0 || nBinarys > 0)//��ʼ����һ��Ϊѡ��ͨ��
	{
		POS  pos = m_oVariableMngr.GetHeadPosition();
		m_pCurrDrawVariable = (CDrawVariable*)m_oVariableMngr.GetAt(pos);
		m_pCurrDrawVariable->SetSelect(TRUE);
	}


	//��ʼ����ǰ��ͼ�ı������������õ�ǰѡ�б���
	AdjustAllDrawObjectsPos();

	AdjustDrawVariablePosition();
	ReCompositor();

	//��ʼ��MEMDC����ʼ��CDrawMr1200RecordBase����
	InitByBorder();

	//������������ͼ��λ��
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

