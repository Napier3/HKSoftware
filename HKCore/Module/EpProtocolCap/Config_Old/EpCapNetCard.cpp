//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetCard.cpp  CEpCapNetCard


#include "stdafx.h"
#include "EpCapNetCard.h"

CEpCapNetCard::CEpCapNetCard()
{
	//初始化属性
	m_nTcp = 0;
	m_nUdp = 0;

	//初始化成员变量
	m_pNetGroup = NULL;
	m_pDirs = NULL;
}

CEpCapNetCard::~CEpCapNetCard()
{
}

long CEpCapNetCard::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTcpKey, oNode, m_nTcp);
	xml_GetAttibuteValue(pXmlKeys->m_strUdpKey, oNode, m_nUdp);
	return 0;
}

long CEpCapNetCard::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTcpKey, oElement, m_nTcp);
	xml_SetAttributeValue(pXmlKeys->m_strUdpKey, oElement, m_nUdp);
	return 0;
}

long CEpCapNetCard::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nTcp);
		BinarySerializeCalLen(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nTcp);
		BinarySerializeRead(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nTcp);
		BinarySerializeWrite(oBinaryBuffer, m_nUdp);
	}
	return 0;
}

void CEpCapNetCard::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ECCLASSID_CEPCAPNETGROUP)
		{
			m_pNetGroup = (CEpCapNetGroup*)p;
		}
		else if (nClassID == ECCLASSID_CEPCAPDIRS)
		{
			m_pDirs = (CEpCapDirs*)p;
		}
	}

	if (m_pNetGroup == NULL)
	{
		m_pNetGroup = (CEpCapNetGroup*)AddNewChild(new CEpCapNetGroup());
	}

	if (m_pDirs == NULL)
	{
		m_pDirs = (CEpCapDirs*)AddNewChild(new CEpCapDirs());
	}

}

BOOL CEpCapNetCard::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetCard *p = (CEpCapNetCard*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nTcp != p->m_nTcp)
	{
		return FALSE;
	}

	if(m_nUdp != p->m_nUdp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapNetCard::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetCard *p = (CEpCapNetCard*)pDest;

	p->m_strName = m_strName;
	p->m_nTcp = m_nTcp;
	p->m_nUdp = m_nUdp;
	return TRUE;
}

CBaseObject* CEpCapNetCard::Clone()
{
	CEpCapNetCard *p = new CEpCapNetCard();
	Copy(p);
	return p;
}

BOOL CEpCapNetCard::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETGROUP)
	{
		return TRUE;
	}

	if (nClassID == ECCLASSID_CEPCAPDIRS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapNetCard::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetGroupKey)
	{
		pNew = new CEpCapNetGroup();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapDirsKey)
	{
		pNew = new CEpCapDirs();
	}

	return pNew;
}

CExBaseObject* CEpCapNetCard::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETGROUP)
	{
		pNew = new CEpCapNetGroup();
	}
	else if (nClassID == ECCLASSID_CEPCAPDIRS)
	{
		pNew = new CEpCapDirs();
	}

	return pNew;
}
