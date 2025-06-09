//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RcdFile.cpp  CRcdFile


#include "stdafx.h"
#include "RcdFile.h"

CRcdFile::CRcdFile()
{
	//初始化属性
	m_nFileSize = 0;
	m_fFileTime = 0;

	//初始化成员变量
}

CRcdFile::~CRcdFile()
{
}

long CRcdFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFilesizeKey, oNode, m_nFileSize);
	xml_GetAttibuteValue(pXmlKeys->m_strFiletimeKey, oNode, m_fFileTime);
	return 0;
}

long CRcdFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFilesizeKey, oElement, m_nFileSize);
	xml_SetAttributeValue(pXmlKeys->m_strFiletimeKey, oElement, m_fFileTime);
	return 0;
}

long CRcdFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nFileSize);
		BinarySerializeCalLen(oBinaryBuffer, m_fFileTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nFileSize);
		BinarySerializeRead(oBinaryBuffer, m_fFileTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nFileSize);
		BinarySerializeWrite(oBinaryBuffer, m_fFileTime);
	}
	return 0;
}

void CRcdFile::InitAfterRead()
{
}

BOOL CRcdFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRcdFile *p = (CRcdFile*)pObj;

	if(m_nFileSize != p->m_nFileSize)
	{
		return FALSE;
	}

	if(m_fFileTime != p->m_fFileTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRcdFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRcdFile *p = (CRcdFile*)pDest;

	p->m_nFileSize = m_nFileSize;
	p->m_fFileTime = m_fFileTime;
	return TRUE;
}

CBaseObject* CRcdFile::Clone()
{
	CRcdFile *p = new CRcdFile();
	Copy(p);
	return p;
}
