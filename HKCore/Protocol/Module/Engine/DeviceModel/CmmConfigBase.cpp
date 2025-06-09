#include "StdAfx.h"
#include "CmmConfigBase.h"
#include "CmmOnConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmConfigBase::CCmmConfigBase(void)
{
	m_nReceiveTimeout = 1000;
	m_nSendTimeout = 1000;
}

CCmmConfigBase::~CCmmConfigBase(void)
{
}

//´®ÐÐ»¯
long CCmmConfigBase::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmConfigBase::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSendTimeout,oNode,m_nSendTimeout);
	xml_GetAttibuteValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strReceiveTimeout,oNode,m_nReceiveTimeout);

	return 0;
}

long CCmmConfigBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSendTimeout,oElement,m_nSendTimeout);
	xml_SetAttributeValue(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strReceiveTimeout,oElement,m_nReceiveTimeout);

	return 0;
}


//±à¼­
BOOL CCmmConfigBase::IsEqualOwn(CBaseObject* pObj)
{ 
	return TRUE;
}

BOOL CCmmConfigBase::CopyOwn(CBaseObject* pDest)
{
	((CCmmConfigBase*)pDest)->m_nSendTimeout = m_nSendTimeout;
	((CCmmConfigBase*)pDest)->m_nReceiveTimeout = m_nReceiveTimeout;

	return TRUE;
}

CBaseObject* CCmmConfigBase::Clone()
{
	ASSERT (FALSE);
	return NULL;
}

CExBaseObject* CCmmConfigBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if(nClassID == DMCLASSID_CMM_ONCONNECT)
	{
		return new CCmmConfigBase;
	}

	return NULL;
}

CExBaseObject* CCmmConfigBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strOnConnectKey)
	{
		return new CCmmOnConnect;
	}

	return NULL;
}

//2023-4-18 lijunqing
void CCmmConfigBase::SetPort(long nPort)
{

}


UINT CmmCfg_GetPort(long nPort)
{
    static CUIntArray g_nArrCmmCfgPort;

	if (nPort > 0)
	{
		return nPort;
	}

	srand(time(0));
	UINT nRandPort = 0;

	while (TRUE)
	{
		nRandPort = rand();
		nRandPort = nRandPort % 16000;
		nRandPort += 8000;

		long  nCount = g_nArrCmmCfgPort.GetCount();
		long nIndex = 0;
		BOOL bExist = FALSE;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			if (g_nArrCmmCfgPort.ElementAt(nIndex) == nRandPort)
			{
				bExist = TRUE;
				break;
			}
		}

		if (!bExist)
		{
			break;
		}
	}

	g_nArrCmmCfgPort.Add(nRandPort);

	return nRandPort;
}
