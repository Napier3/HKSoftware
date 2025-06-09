#include "StdAfx.h"
#include "EpCmmNetConfig.h"

CEpCmmNetConfig::CEpCmmNetConfig(void)
{
}

CEpCmmNetConfig::~CEpCmmNetConfig(void)
{
}

//��������
void CEpCmmNetConfig::Init()
{

}

long CEpCmmNetConfig::InitAfterSerialize()
{
	return 0;
}

//���л�
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


//�༭
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


//�����Ӷ���
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

