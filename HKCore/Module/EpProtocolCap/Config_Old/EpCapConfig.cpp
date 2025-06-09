//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapConfig.cpp  CEpCapConfig


#include "stdafx.h"
#include "EpCapConfig.h"

CEpCapConfig::CEpCapConfig()
{
	//初始化属性

	//初始化成员变量
	m_pNetConfig = NULL;
	m_pSerialConfig = NULL;
}

CEpCapConfig::~CEpCapConfig()
{
}

long CEpCapConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strFile);
	return 0;
}

long CEpCapConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strFile);
	return 0;
}

long CEpCapConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFile);
	}
	return 0;
}

void CEpCapConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ECCLASSID_CEPCAPNETCONFIG)
		{
			m_pNetConfig = (CEpCapNetConfig*)p;
		}
		else if (nClassID == ECCLASSID_CEPCAPSERIALCONFIG)
		{
			m_pSerialConfig = (CEpCapSerialConfig*)p;
		}
	}

	if (m_pNetConfig == NULL)
	{
		m_pNetConfig = (CEpCapNetConfig*)AddNewChild(new CEpCapNetConfig());
	}

	if (m_pSerialConfig == NULL)
	{
		m_pSerialConfig = (CEpCapSerialConfig*)AddNewChild(new CEpCapSerialConfig());
	}

}

BOOL CEpCapConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapConfig *p = (CEpCapConfig*)pObj;

	if(m_strFile != p->m_strFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapConfig *p = (CEpCapConfig*)pDest;

	p->m_strFile = m_strFile;
	return TRUE;
}

CBaseObject* CEpCapConfig::Clone()
{
	CEpCapConfig *p = new CEpCapConfig();
	Copy(p);
	return p;
}

BOOL CEpCapConfig::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETCONFIG)
	{
		return TRUE;
	}

	if (nClassID == ECCLASSID_CEPCAPSERIALCONFIG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetConfigKey)
	{
		pNew = new CEpCapNetConfig();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapSerialConfigKey)
	{
		pNew = new CEpCapSerialConfig();
	}

	return pNew;
}

CExBaseObject* CEpCapConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETCONFIG)
	{
		pNew = new CEpCapNetConfig();
	}
	else if (nClassID == ECCLASSID_CEPCAPSERIALCONFIG)
	{
		pNew = new CEpCapSerialConfig();
	}

	return pNew;
}
