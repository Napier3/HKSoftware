// RtBinaryVariable.cpp: implementation of the CRtBinaryVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtBinaryVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CRtBinaryVariable::g_pszKeyBinaryVariable = "binary-variable";
const char *CRtBinaryVariable::g_pszKeyIndex = "index";

const char* CRtBinaryVariable::g_pszKeyBinaryRaise = "BinaryRaise";
const char* CRtBinaryVariable::g_pszKeyBinaryFall  = "BinaryFall";

CRtBinaryVariable::CRtBinaryVariable()
{
}

CRtBinaryVariable::~CRtBinaryVariable()
{
}


void CRtBinaryVariable::InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr)
{
	m_pChannelBuffer = pRtMemBufferMngr->AddMR1200BinaryChannel(m_nIndex, m_nRecordBufferUse, m_strRecordBufferID, m_nSpyBufferUse, m_strSpyBufferID);
}

BOOL CRtBinaryVariable::InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer)
{
	if (m_pDataAttrs == NULL)
	{
		return FALSE;
	}
	
	if (!(m_pDataAttrs->InitDataAttributeCalFunc(bCalUseRecordBuffer)))
	{
		debug_trace("CRtVariable Initialize DataAttributeCalFunc failed!");
	}
		
	return TRUE;
}

BOOL CRtBinaryVariable::GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer)
{
	nAttrID =GetVariableAttributeID(strAttrID.GetString());
	
	*ppdValue = NULL;
	*ppdMutationValue = NULL;
	*ppCalFunc = NULL;

	memset(&oRtCalFuncPara, 0, sizeof(RTCALFUNCPARA));
	oRtCalFuncPara.pRtChAttrVal = NULL;
	oRtCalFuncPara.nBinaryBitIndex = m_nIndex;

	if (IsRecordBufferNull(bCalUseRecordBuffer))
	{
		return FALSE;
	}

	if (m_pChannelBuffer == NULL)
	{//²»·ÖÅäspy¡¢record»º³åÇø
		return TRUE;
	}
	else
	{
	}
	
	CMemBufferInterface *pBuffer = NULL;
	CMemBuffer_Float *pfBuffer = NULL;


	if (bCalUseRecordBuffer)
	{
		if (g_wBufferState == 0)
		{
#ifdef _USE_RECORD_BUFFER_TO_CAL
			pBuffer = m_pChannelBuffer->GetRecordMemBuffer();
#else
			pBuffer = m_pChannelBuffer->GetSpyMemBuffer();
#endif
		} 
		else if (g_wBufferState == 1)
		{
			pBuffer = m_pChannelBuffer->GetRecordMemBuffer();
		}
		else
		{
		}
	}
	else
	{
		pBuffer = m_pAttachRecordBuffer;
	}

	oRtCalFuncPara.pnBuffer = pBuffer->GetBuffer();
	oRtCalFuncPara.pnBuffer_long = pBuffer->GetBuffer_long();

	return TRUE;
}

long CRtBinaryVariable::RTUpdateOwnByAutofit(HDINFO &oHDInfo)
{
	CString strTemp;
	long nIndex = oHDInfo.nTranBinaryChCount * oHDInfo.nTranIndex + oHDInfo.nTranChIndex;

	//Index
	m_nIndex = nIndex % 16;

	//ID
	strTemp.Format(m_strID, nIndex + 1);
	m_strID = strTemp;
	
	//Name
	m_strName = strTemp;
			
	//Variable Use
	m_nVariableUse = 0;
	return 0;
}


