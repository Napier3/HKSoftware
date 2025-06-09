// VerUpdateCfgMap.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgMap.h"

// CVerUpdateCfgMap

CVerUpdateCfgMap::CVerUpdateCfgMap()
{
	//初始化属性
}

CVerUpdateCfgMap::~CVerUpdateCfgMap()
{
}

long CVerUpdateCfgMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strShellPathKey, oNode, m_strShellPath);
	xml_GetAttibuteValue(pXmlKeys->m_strIdxSysKey, oNode, m_idxSys);

	return 0;
}

long CVerUpdateCfgMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strShellPathKey, oElement, m_strShellPath);
	xml_SetAttributeValue(pXmlKeys->m_strIdxSysKey, oElement, m_idxSys);

	return 0;
}

long CVerUpdateCfgMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strShellPath);
		BinarySerializeCalLen(oBinaryBuffer, m_idxSys);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strShellPath);
		BinarySerializeRead(oBinaryBuffer, m_idxSys);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strShellPath);
		BinarySerializeWrite(oBinaryBuffer, m_idxSys);
	}

	return 0;
}
