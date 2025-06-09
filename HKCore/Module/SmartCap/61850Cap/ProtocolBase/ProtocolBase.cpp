// ProtocolBas.cpp: implementation of the CProtocolBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProtocolBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocolBase::CProtocolBase()
{ 
	m_pParseFrames = NULL;
	m_nFrameMaxLength = 255;
	m_nFrameMinLength = 1;
	m_pDevice = NULL;
	m_dwPrototcol = 0;
	ZeroMemory(&m_oCapParseDatas, sizeof(EPCAPPARSEDATAS));
}

CProtocolBase::~CProtocolBase()
{

}

void CProtocolBase::AddParseFrame(CFrameBase *pFrame)
{
	m_pParseFrames->AddNewChild(pFrame);
}

CFrameBase* CProtocolBase::Match(PEPBUFFERPOS pBufferPos)
{
	CFrameBase *pMatch = m_pParseFrames->Match(pBufferPos);

	if (pMatch != NULL)
	{
		return pMatch;
	}

	if (Ep_IsMatchStateNotFull(pBufferPos))
	{
	}
	else
	{
		Ep_SetMatchStateNone(pBufferPos);
	}

	return pMatch;
}

CFrameBase* CProtocolBase::Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	pBufferPos->nProtocol = m_dwPrototcol; //规约类型

	EPBUFFERPOS oStBufPos;
	Ep_BackBufferPos(*pBufferPos, oStBufPos);
	CFrameBase *pMath = Match(pBufferPos);

	if (Ep_IsMatchStateMatch(pBufferPos))
	{
		Ep_BackBufferPos(oStBufPos, *pBufferPos);
		pMath->Parse(pBufferPos, pDetailList);

	}
	else
	{
		Ep_BackBufferPos(oStBufPos, *pBufferPos);
	}

	return pMath;
}

CFrameBase* CProtocolBase::Parse(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->nProtocol = m_dwPrototcol; //规约类型

	EPBUFFERPOS oStBufPos;
	Ep_BackBufferPos(*pBufferPos, oStBufPos);
	CFrameBase *pMath = Match(pBufferPos);

	if (Ep_IsMatchStateMatch(pBufferPos))
	{
		Ep_BackBufferPos(oStBufPos, *pBufferPos);
		pMath->Parse(pBufferPos);

	}
	else
	{
		Ep_BackBufferPos(oStBufPos, *pBufferPos);
	}

	return pMath;
}

CFrameBase* CProtocolBase::FindFrameByID(DWORD dwClassID)
{
	CFrameBase *pFrame = (CFrameBase*)m_pParseFrames->FindByClassID(dwClassID);

	if (pFrame != NULL)
	{
		return pFrame;
	}

	return NULL;
}

