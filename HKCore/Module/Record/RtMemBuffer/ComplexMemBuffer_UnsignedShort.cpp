// ComplexMemBuffer_UnsignedShort.cpp: implementation of the CMemBuffer_UnsignedShort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComplexMemBuffer_UnsignedShort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CComplexMemBuffer_UnsignedShort::CComplexMemBuffer_UnsignedShort()
{
	m_pScript = NULL;
	m_nSrcMemBufferCount = 0;
	long nIndex = 0;

	for (nIndex=0; nIndex<COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT; nIndex++)
	{
		m_pSrcBuffer[nIndex] = NULL;
	}

	m_pScript = new CRtComplexBufUShortScript();
}

CComplexMemBuffer_UnsignedShort::~CComplexMemBuffer_UnsignedShort()
{
	if (m_pScript != NULL)
	{
		delete m_pScript;
		m_pScript = NULL;
	}
}

BOOL CComplexMemBuffer_UnsignedShort::ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)
{
	short nVal = 0;
	long nIndex = 0;

	for (nIndex=nPos1Begin; nIndex<nPos1End; nIndex++)
	{
		m_pScript->m_nIndex = nIndex;
		m_pScript->RunExpression();
		//m_pBuffer[nIndex] = nVal;
	}

	for (nIndex=nPos2Begin; nIndex<nPos2End; nIndex++)
	{
		m_pScript->m_nIndex = nIndex;
		m_pScript->RunExpression();
		//m_pBuffer[nIndex] = nVal;
	}
	
	return TRUE;
}


#ifdef _debug_complex_channel
void CComplexMemBuffer_UnsignedShort::CreateScript()
{
	CRtScriptBase::PEXPNODE pNode = NULL;
	CRtScriptBase::PEXPNODE pLeft = NULL;
	CRtScriptBase::PEXPNODE pRight = NULL;

	//root
	pNode = m_pScript->NewExpNode();
	m_pScript->m_pExpRoot = pNode;
	pNode->nOptrID = RTSCRIPT_OPTRID_ADD;
	pNode->m_nIsRefValue = TRUE;
	pNode->pValue = m_pBuffer;

	pLeft = m_pScript->NewExpNode();
	pLeft->m_nIsRefValue = TRUE;
	pLeft->pValue = m_pSrcBuffer[0]->GetBuffer();
	pLeft->nOptrID = RTSCRIPT_OPTRID_REFVALUE;

	pRight = m_pScript->NewExpNode();
	pRight->m_nIsRefValue = TRUE;
	pRight->pValue = m_pSrcBuffer[1]->GetBuffer();
	pRight->nOptrID = RTSCRIPT_OPTRID_REFVALUE;

	pNode->pLeft = pLeft;
	pNode->pRight = pRight;
}

#endif
