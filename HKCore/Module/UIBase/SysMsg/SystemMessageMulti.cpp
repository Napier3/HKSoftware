// systemmessagemulti.cpp: implementation of the CSystemMessageMulti class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "systemmessagemulti.h"
#include "SystemMessages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CSystemMessageMulti::g_pszKeyMode        = "mode";
const char* CSystemMessageMulti::g_pszKeyMultiSysMsg = "multi-sys-msg";

const char* CSystemMessageMulti::g_pszKeyModeOrder     = "order";
const char* CSystemMessageMulti::g_pszKeyModeAtOneTime = "at-one-time";

CSystemMessageMulti::CSystemMessageMulti()
{
	m_nMode = 0;
}

CSystemMessageMulti::~CSystemMessageMulti()
{
	m_anSingleSysMsg.RemoveAll();
}

long CSystemMessageMulti::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	CSystemMessage::ReadOwnXml(oNode);

	CString strMode;

	if (!xml_GetAttibuteValue(g_pszKeyMode, oNode, strMode))
	{
		debug_trace(".................");
	}
	
	if (stricmp(strMode, g_pszKeyModeOrder) == 0)
	{
		m_nMode = MULTI_SYSMSG_MODE_ORDER;
	}
	else if(stricmp(strMode, g_pszKeyModeAtOneTime) == 0)
	{
		m_nMode = MULTI_SYSMSG_MODE_ATONETIME;
	}
	else
	{
		m_nMode = MULTI_SYSMSG_MODE_ORDER;
	}

	//读取子节点
	MSXML::IXMLDOMNodeListPtr oNodes;
	MSXML::IXMLDOMNodePtr oChild;

	oNodes = oNode->GetchildNodes();
	long nCount = oNodes->Getlength();
	long nIndex = 0;
	m_astrSingleSysMsg.RemoveAll();
	CString strSysMsg;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oChild = oNodes->Getitem(nIndex);

		if (oChild != NULL)
		{
			strSysMsg = (char*)_bstr_t(oChild->GetnodeTypedValue());

			if (strSysMsg.GetLength() > 1)
			{
				m_astrSingleSysMsg.Add(strSysMsg);
			}
		}
	}

	return 0;
}

CSystemMessage* CSystemMessageMulti::Clone()
{
	CSystemMessageMulti *pMsg = new CSystemMessageMulti();
	
	pMsg->m_strName     = m_strName;
	pMsg->m_strID       = m_strID;
	pMsg->m_nID         = m_nID;
	pMsg->m_nIndex      = m_nIndex;
	pMsg->m_dwTickCount = m_dwTickCount;

	pMsg->m_nMode       = m_nMode;

	long nIndex = 0;
	long nCount = m_astrSingleSysMsg.GetSize();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pMsg->m_astrSingleSysMsg.Add(m_astrSingleSysMsg.GetAt(nIndex));
	}
	
	return pMsg;
}

void CSystemMessageMulti::InitMultiSystemMessage(CSystemMessages *pSingleSysMsgs)
{
	long nCount = m_astrSingleSysMsg.GetSize();
	long nIndex = 0;
	CSystemMessage *pFind = NULL;
	m_anSingleSysMsg.RemoveAll();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pFind = (CSystemMessage*)pSingleSysMsgs->FindByName(m_astrSingleSysMsg.GetAt(nIndex));
		
		if (pFind == NULL)
		{
			debug_trace("Error message");
		}
		else
		{
			m_anSingleSysMsg.Add(pFind->m_nID);
		}
	}
}

