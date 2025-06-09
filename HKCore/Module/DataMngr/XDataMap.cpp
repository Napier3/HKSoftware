//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDataMap.cpp  CXDataMap


#include "stdafx.h"
#include "XDataMap.h"

CXDataMap::CXDataMap()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXDataMap::~CXDataMap()
{
}

long CXDataMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMap_IdKey, oNode, m_strMapID);
	return 0;
}

long CXDataMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMap_IdKey, oElement, m_strMapID);
	return 0;
}

long CXDataMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMapID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMapID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMapID);
	}
	return 0;
}

BOOL CXDataMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXDataMap *p = (CXDataMap*)pObj;

	if(m_strMapID != p->m_strMapID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDataMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CXDataMap *p = (CXDataMap*)pDest;

	p->m_strMapID = m_strMapID;
	p->m_varDataAddr = m_varDataAddr;
	return TRUE;
}

CBaseObject* CXDataMap::Clone()
{
	CXDataMap *p = new CXDataMap();
	Copy(p);
	return p;
}
