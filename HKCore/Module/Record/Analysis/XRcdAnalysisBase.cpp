// XRcdAnalysisBase.cpp: implementation of the CXRcdAnalysisBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRcdAnalysisBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CRcdCalFilterConfig::CRcdCalFilterConfig()
{
	m_nPointsMode = 0;  //0=ֱ�����ã� 1=�����ʵİٷֱȣ�1~20��
	m_nPrevPoints = 0;
	m_nNextPoints = 0;
	m_nPointsEx = 5; //ǰ�����ݵ����չ
}

CRcdCalFilterConfig::~CRcdCalFilterConfig()
{
	
}

void CRcdCalFilterConfig::InitBySampleRate(long nSampleRate)
{
	m_nPointsEx = nSampleRate / 400;
	m_nPointsEx = max(m_nPointsEx, 5);
}

//////////////////////////////////////////////////////////////////////////
//CXRcdAnalysisBase
CXRcdAnalysisBase::CXRcdAnalysisBase()
{
	m_pComtradeFile = NULL;
	m_bNewComtradeFile = FALSE;  //�Ƿ���������������Ķ���
	m_pRespConfig = NULL;
}

CXRcdAnalysisBase::~CXRcdAnalysisBase()
{
	FreeAnalysis();
}

void CXRcdAnalysisBase::FreeAnalysis()
{
	if (m_bNewComtradeFile)
	{
		CRcdComtradeFileMngr::CloseComtradeFile(m_pComtradeFile);
	}

	m_bNewComtradeFile = FALSE;
}

void CXRcdAnalysisBase::SetRcdComtradeFile(const CString &strComtradeFile)
{
	FreeAnalysis();

	m_pComtradeFile = CRcdComtradeFileMngr::OpenComtradeFile(strComtradeFile);
	m_bNewComtradeFile = TRUE;
}

void CXRcdAnalysisBase::SetRcdComtradeFile(CRcdComtradeFile *pComtradeFile)
{
	FreeAnalysis();
	m_pComtradeFile = pComtradeFile;
}


BOOL CXRcdAnalysisBase::Analysis()
{
	return FALSE;
}

