// SttNativeCfgMnt.cpp : 实现文件
//

#include "stdafx.h"
#include "SttNativeCfgMnt.h"

// CSttNativeCfgMnt

CSttNativeCfgMnt::CSttNativeCfgMnt()
{
	//初始化属性
	m_strRootFiles = _T("");
}

CSttNativeCfgMnt::~CSttNativeCfgMnt()
{
}

long CSttNativeCfgMnt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRootFilesKey, oNode, m_strRootFiles);

	return 0;
}

long CSttNativeCfgMnt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;
	
	xml_SetAttributeValue(pXmlKeys->m_strRootFilesKey, oElement, m_strRootFiles);

	return 0;
}

long CSttNativeCfgMnt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRootFiles);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strRootFiles);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strRootFiles);
	}

	return 0;
}

BOOL CSttNativeCfgMnt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttNativeCfgMnt *p = (CSttNativeCfgMnt*)pObj;

	if(m_strRootFiles != p->m_strRootFiles)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttNativeCfgMnt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttNativeCfgMnt *p = (CSttNativeCfgMnt*)pDest;
	p->m_strRootFiles = m_strRootFiles;

	return TRUE;
}

CBaseObject* CSttNativeCfgMnt::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CSttNativeCfgMnt();

	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}
	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	

	return pNew;
}
