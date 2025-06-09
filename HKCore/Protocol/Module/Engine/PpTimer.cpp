#include "StdAfx.h"
#include "PpTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpTimer::CPpTimer(void)
{
	m_pJumpToNode = NULL;
	m_nTimeLong = 0;
	m_bTimerBegin = FALSE;
	m_dwTimerBegin = 0;
	m_pScript = NULL;
}

CPpTimer::~CPpTimer(void)
{
}

long CPpTimer::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strTypeKey, oNode, m_strType);
	//此处增加把strType转换为nType的代码

	xml_GetAttibuteValue(pKey->m_strJumpToKey, oNode, m_strJumpTo);

	xml_GetAttibuteValue(pKey->m_strTimeKey, oNode, m_nTimeLong);
	

	return 0;
}

long CPpTimer::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKey->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pKey->m_strJumpToKey, oElement, m_strJumpTo);

	xml_SetAttributeValue(pKey->m_strTimeKey, oElement, m_nTimeLong);

	return 0;
}

long CPpTimer::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}


CExBaseObject* CPpTimer::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpNodeKey)
	{
		return new CPpNode(PPNODE_TYPE_PRODUCE);
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
	{
#ifdef UNICODE
		return new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		return new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
	}

	return NULL;
}

CExBaseObject* CPpTimer::CreateNewChild(long nClassID)
{
	if (nClassID == PPCLASSID_PPNODE)
	{
		return new CPpNode(PPNODE_TYPE_PRODUCE);
	}

	if (nClassID == PPCLASSID_PPSCRIPT)
	{
#ifdef UNICODE
		return new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		return new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
	}

	return NULL;
}
void CPpTimer::InitAfterRead()
{
	//初始化m_pDataInterface等子对象指针
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);

		UINT nClassID = p->GetClassID();

		switch (nClassID)
		{
		case PPCLASSID_PPNODE:
			{
				m_pJumpToNode = (CPpNode*)p;
			}
			break;
		case PPCLASSID_PPSCRIPT:
			{
				m_pScript = (CPpScript*)p;
			}
			break;

		default:
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpTimer::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strType != ((CPpTimer*)pObj)->m_strType)
	{
		return FALSE;
	}

	if (m_nType != ((CPpTimer*)pObj)->m_nType)
	{
		return FALSE;
	}

	if (m_nTimeLong != ((CPpTimer*)pObj)->m_nTimeLong)
	{
		return FALSE;
	}

	if (m_strJumpTo != ((CPpTimer*)pObj)->m_strJumpTo)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpTimer::Clone()
{
	CPpTimer* pNew = new CPpTimer();
	Copy(pNew);
	return pNew;
}

BOOL CPpTimer::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpTimer*)pDest)->m_strType = m_strType;
	((CPpTimer*)pDest)->m_nType = m_nType;
	((CPpTimer*)pDest)->m_nTimeLong = m_nTimeLong;
	((CPpTimer*)pDest)->m_strJumpTo = m_strJumpTo;

	return CExBaseObject::CopyOwn(pDest);
}

void CPpTimer::BeginTimer(DWORD dwCurrTick)
{
	m_bTimerBegin = TRUE;
	m_dwTimerBegin = dwCurrTick;
}

void CPpTimer::ResetTimer(DWORD dwCurrTick)
{
	m_dwTimerBegin = dwCurrTick;
}

void CPpTimer::KillTimer()
{
	m_bTimerBegin = FALSE;
	m_dwTimerBegin = 0;
}

BOOL CPpTimer::IsTimeOut(DWORD dwCurrTick)
{
	long nTimer = dwCurrTick - m_dwTimerBegin;

	if (nTimer > m_nTimeLong)
	{
		return TRUE;
	}
	else
	{
		if (nTimer < 0)
		{
			m_dwTimerBegin = 0;
			return ((long)dwCurrTick > m_nTimeLong);
		}
		else
		{
			return FALSE;
		}
	}
}

CPpScript* CPpTimer::GetScript()
{
	if (m_pScript == NULL)
	{
#ifdef UNICODE
		m_pScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		m_pScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
		AddTail(m_pScript);
		m_pScript->SetParent(this);
	}

	return m_pScript;
}