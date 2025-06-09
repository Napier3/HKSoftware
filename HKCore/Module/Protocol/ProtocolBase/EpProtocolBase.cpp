// EpProtocolBas.cpp: implementation of the CEpProtocolBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpProtocolBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpProtocolBase::CEpProtocolBase()
{ 
	m_pParseFrames = new CEpFrameGroup();
	m_pProduceFrames = new CEpFrameGroup();
//	m_pEpProcedures = new CEpProcedures();
	m_pFrameGroups = new CEpFrameGroups();

	AddNewChild(m_pParseFrames);
	AddNewChild(m_pProduceFrames);
//	AddNewChild(m_pEpProcedures);
	AddNewChild(m_pFrameGroups);
// 	m_pCmmConfig = new CEpDeviceCmmConfig();
// 	AddNewChild(m_pCmmConfig);

	m_nFrameMaxLength = 255;
	m_nFrameMinLength = 1;
	m_pDevice = NULL;
	m_dwPrototcol = 0;
}

CEpProtocolBase::~CEpProtocolBase()
{

}

void CEpProtocolBase::AddParseFrame(CEpFrameBase *pFrame)
{
	m_pParseFrames->AddNewChild(pFrame);
}

void CEpProtocolBase::AddProduceFrame(CEpFrameBase *pFrame)
{
	m_pProduceFrames->AddNewChild(pFrame);
}

void CEpProtocolBase::AddFrameGroup(CEpFrameGroup *pGroup)
{
	m_pFrameGroups->AddNewChild(pGroup);
}

// void CEpProtocolBase::AddProcedure(CEpProcedure *pProcedure)
// {
// 	m_pEpProcedures->AddNewChild(pProcedure);
// }

CEpFrameBase* CEpProtocolBase::Match(PEPBUFFERPOS pBufferPos)
{
	CEpFrameBase *pMatch = m_pParseFrames->Match(pBufferPos);

	if (pMatch != NULL)
	{
		return pMatch;
	}

	pMatch = m_pFrameGroups->Match(pBufferPos);

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

CEpFrameBase* CEpProtocolBase::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	pBufferPos->nProtocol = m_dwPrototcol; //规约类型
	pBufferPos->nYxAddr = m_nYxAddr;
	pBufferPos->nYcAddr = m_nYcAddr;
	pBufferPos->nYtAddr = m_nYtAddr;
	pBufferPos->nODDRLen = m_nODDRLen;

	CEpFrameBase *pMath = NULL;

	while (TRUE)
	{
		EPBUFFERPOS oEpBufPos;
		Ep_BackBufferPos(*pBufferPos, oEpBufPos);
		pMath = Match(pBufferPos);

		//规约类型
		Ep_SetProtocol_ProtoType(pBufferPos->nProtocol, 0x0FF);

		if (Ep_IsMatchStateMatch(pBufferPos))
		{
			Ep_BackBufferPos(oEpBufPos, *pBufferPos);
			pMath->Parse(pBufferPos, pDetailList);

			//报文类型
			Ep_SetProtocol_FrameType(pBufferPos->nProtocol, pMath->GetClassID() & 0x0FF);

			//规约类型
			Ep_SetProtocol_ProtoType_Proto(pBufferPos->nProtocol, m_dwPrototcol & 0x0FF);

			if (pBufferPos->pDatas != NULL)
			{
				if (pBufferPos->pDatas->GetCount() > 0)
				{
					Ep_SetProtocol_ProtoType_Type(pBufferPos->nProtocol, pBufferPos->pDatas->m_nDeviceDataType & 0x0FF);
				}
			}

			if (Ep_EpBufferLeave(pBufferPos) < 6)
			{
				break;
			}
		}
		else
		{
			Ep_BackBufferPos(oEpBufPos, *pBufferPos);
			//报文类型
			Ep_SetProtocol_FrameType(pBufferPos->nProtocol, 0);
		}

	}

	return pMath;
}

CEpFrameBase* CEpProtocolBase::FindFrameByID(DWORD dwClassID)
{
	CEpFrameBase *pFrame = (CEpFrameBase*)m_pParseFrames->FindByClassID(dwClassID);

	if (pFrame != NULL)
	{
		return pFrame;
	}

	pFrame = (CEpFrameBase *)m_pProduceFrames->FindByClassID(dwClassID);

	if (pFrame != NULL)
	{
		return pFrame;
	}

	pFrame = (CEpFrameBase *)m_pFrameGroups->FindByClassID(dwClassID);

	if (pFrame != NULL)
	{
		return pFrame;
	}

	return NULL;
}

void CEpProtocolBase::AttachDevice(CEpDevice *pDevice)
{
	m_pDevice = pDevice;
}

// void CEpProtocolBase::AttachDeviceCmmChannel(CEpDeviceCmmChannel *pChannel)
// {
// 	m_pDeviceCmmChannel = pChannel;
// 	ASSERT (m_pDeviceCmmChannel != NULL);
// }

// CEpCmmChannel* CEpProtocolBase::FindCmmChannel(const CString &strChannelID)
// {
// 	return m_pDeviceCmmChannel->FindCmmChannel(strChannelID);
// }
// 
// CEpCmmChannel* Ep_FindCmmChannel(CExBaseObject *pObj, const CString &strChannelID)
// {
// 	CEpProtocolBase *pProtocol = (CEpProtocolBase*)pObj->GetAncestor(EPCLASSID_PROTOCOL);
// 	ASSERT (pProtocol != NULL);
// 
// 	return pProtocol->FindCmmChannel(strChannelID);
// }

