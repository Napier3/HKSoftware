//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpProtocolConfig.cpp  CEpProtocolConfig


#include "stdafx.h"
#include "EpProtocolConfig.h"

CEpProtocolConfig::CEpProtocolConfig()
{
	//初始化属性

	//初始化成员变量
	m_p101Config = NULL;
	m_p104Config = NULL;
}

CEpProtocolConfig::~CEpProtocolConfig()
{
}

long CEpProtocolConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpProtocolConfigXmlRWKeys *pXmlKeys = (CEpProtocolConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpProtocolConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpProtocolConfigXmlRWKeys *pXmlKeys = (CEpProtocolConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpProtocolConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CEpProtocolConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EPCCLASSID_CEP101CONFIG)
		{
			m_p101Config = (CEp101Config*)p;
		}
		else if (nClassID == EPCCLASSID_CEP104CONFIG)
		{
			m_p104Config = (CEp104Config*)p;
		}
	}

	if (m_p101Config == NULL)
	{
		m_p101Config = (CEp101Config*)AddNewChild(new CEp101Config());
	}

	if (m_p104Config == NULL)
	{
		m_p104Config = (CEp104Config*)AddNewChild(new CEp104Config());
	}

}

BOOL CEpProtocolConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpProtocolConfig *p = (CEpProtocolConfig*)pObj;

	return TRUE;
}

BOOL CEpProtocolConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpProtocolConfig *p = (CEpProtocolConfig*)pDest;

	return TRUE;
}

CBaseObject* CEpProtocolConfig::Clone()
{
	CEpProtocolConfig *p = new CEpProtocolConfig();
	Copy(p);
	return p;
}

BOOL CEpProtocolConfig::CanPaste(UINT nClassID)
{
	if (nClassID == EPCCLASSID_CEP101CONFIG)
	{
		return TRUE;
	}

	if (nClassID == EPCCLASSID_CEP104CONFIG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpProtocolConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpProtocolConfigXmlRWKeys *pXmlKeys = (CEpProtocolConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEp101ConfigKey)
	{
		pNew = new CEp101Config();
	}
	else if (strClassID == pXmlKeys->m_strCEp104ConfigKey)
	{
		pNew = new CEp104Config();
	}

	return pNew;
}

CExBaseObject* CEpProtocolConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPCCLASSID_CEP101CONFIG)
	{
		pNew = new CEp101Config();
	}
	else if (nClassID == EPCCLASSID_CEP104CONFIG)
	{
		pNew = new CEp104Config();
	}

	return pNew;
}
