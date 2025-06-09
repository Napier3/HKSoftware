#include "StdAfx.h"
#include "EpCmmNetConfig.h"

CEpCmmNetConfig::CEpCmmNetConfig(void)
{
}

CEpCmmNetConfig::~CEpCmmNetConfig(void)
{
}

//基本方法
void CEpCmmNetConfig::Init()
{

}

long CEpCmmNetConfig::InitAfterSerialize()
{
	return 0;
}

//串行化
long CEpCmmNetConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CEpCmmNetConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


long CEpCmmNetConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


//编辑
BOOL CEpCmmNetConfig::IsEqualOwn(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CEpCmmNetConfig::CopyOwn(CBaseObject* pDest)
{
	return FALSE;
}

CBaseObject* CEpCmmNetConfig::Clone()
{
	return NULL;
}


//创建子对象
CExBaseObject* CEpCmmNetConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject* CEpCmmNetConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if (strClassID == CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strTcpServerKey)
	{
		pNew = new CEpCmmTcpServerConfig();
	}
	else if (strClassID == CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strTcpClientKey)
	{
		pNew = new CEpCmmTcpClientConfig();
	}
	else if (strClassID == CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strUdpServerKey)
	{
		pNew = new CEpCmmUdpConfig();
	}
	else if (strClassID == CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strUdpClientKey)
	{
		pNew = new CEpCmmUdpConfig();
	}
	else
	{

	}


	if (pNew != NULL)
	{
		pNew->m_strName = strClassID;
		pNew->m_strID = strClassID;
	}


	return pNew;
}


CExBaseObject* CEpCmmNetConfig::GetChildByClassID(UINT nClassID)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
	UINT nID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		nID = p->GetClassID();

		if (nClassID == nID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

