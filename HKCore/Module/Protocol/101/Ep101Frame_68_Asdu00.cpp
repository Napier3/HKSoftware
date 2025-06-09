#include "StdAfx.h"

#include "Ep101Frame_68_Asdu00.h"
#include "EpProtocol101.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_68_Asdu00::CEp101Frame_68_Asdu00(CEpFrameBase *pHead, CEpFrameBase *pTail)
		:CEp101Frame_68_AsduBase(pHead, pTail)
{
	m_strID = _T("101_ASDU_00");
	m_strName = m_strID;
}

CEp101Frame_68_Asdu00::~CEp101Frame_68_Asdu00()
{

}

DWORD CEp101Frame_68_Asdu00::ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	CEp101Frame_68_AsduBase::ParseOwn(pBufferPos, pDetailList);

	if(m_pHead != NULL)
	{
		return Ep_OffsetEpBufferCurr(pBufferPos, m_pHead->m_nLength);
	}
	else
	{
		return Ep_OffsetEpBufferCurr(pBufferPos, 0);
	}
}

BOOL CEp101Frame_68_Asdu00::Match(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	return TRUE;
}

DWORD CEp101Frame_68_Asdu00::Produce(PEPBUFFERPOS pBufferPos)
{
	return 0;
}
