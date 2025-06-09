#include "StdAfx.h"
#include "PpTimers.h"
#include "PpNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpTimers::CPpTimers(void)
{
}

CPpTimers::~CPpTimers(void)
{
}

CExBaseObject* CPpTimers::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpTimerKey)
	{
		return new CPpTimer();
	}

	return NULL;
}

CExBaseObject* CPpTimers::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpTimers::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpTimers::Clone()
{
	CPpTimers* pNew = new CPpTimers();
	Copy(pNew);
	return pNew;
}

BOOL CPpTimers::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}

void CPpTimers::BeginTimer()
{
	DWORD dwTick = ::GetTickCount();
	POS pos = GetHeadPosition();
	CPpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CPpTimer*)GetNext(pos);
		pTimer->BeginTimer(dwTick);
	}
}

void CPpTimers::ResetTimer()
{
	DWORD dwTick = ::GetTickCount();
	POS pos = GetHeadPosition();
	CPpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CPpTimer*)GetNext(pos);
		pTimer->ResetTimer(dwTick);
	}
}

void CPpTimers::KillTimer()
{
	POS pos = GetHeadPosition();
	CPpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CPpTimer*)GetNext(pos);
		pTimer->KillTimer();
	}
}

CPpNode* CPpTimers::RunTimer(DWORD dwCurrTick)
{
	CPpNode *pNodeToRun = NULL;
	POS pos = GetHeadPosition();
	CPpTimer *pTimer = NULL;
	CPpNode *pCurrNode = (CPpNode*)GetAncestor(PPCLASSID_PPNODE);

	if (pCurrNode == NULL)
	{
		return NULL;
	}

	while (pos != NULL)
	{
		pTimer = (CPpTimer*)GetNext(pos);

		if (pTimer->IsTimeOut(dwCurrTick) )
		{
			if (pCurrNode->m_strID == _T("WSets1"))
			{
				int i = 0;
			}

			CPpScript *pScript = pTimer->GetScript();
			BOOL bRet = FALSE;

			if (pScript->m_strScript.GetLength() <= 5)
			{
				bRet = TRUE;
			}
			else
			{
				pCurrNode->RunNodeScript(pScript, NULL);
				bRet = pScript->IsReturnValueTrue();
			}

			if (bRet)
			{
				pNodeToRun = PpGetJumpToNode(pTimer->m_strJumpTo, pTimer->m_pJumpToNode, pTimer);

				if (pNodeToRun != NULL)
				{
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Timer[%s] ==>> %s", m_strID, pNodeToRun->m_strID);
				}
				else
				{
					pNodeToRun = g_pPpEndNode;
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Timer[%s] jump error {to end}", m_strID.GetString());
				}
			}

			pTimer->ResetTimer(dwCurrTick);
		}

		if (pNodeToRun != NULL)
		{
			break;
		}
	}

	return pNodeToRun;
}

