//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ParaMap.cpp  CParaMap


#include "stdafx.h"
#include "ParaMap.h"

CParaMap::CParaMap()
{
	//初始化属性
	m_nUse = 1; // 默认使用参数

	//初始化成员变量
}

CParaMap::~CParaMap()
{
}

long CParaMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapNameKey, oNode, m_strMapName);
	xml_GetAttibuteValue(pXmlKeys->m_strMapIDKey, oNode, m_strMapID);
	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	return 0;
}

long CParaMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapNameKey, oElement, m_strMapName);
	xml_SetAttributeValue(pXmlKeys->m_strMapIDKey, oElement, m_strMapID);
	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_nUse);
	return 0;
}

long CParaMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMapName);
		BinarySerializeCalLen(oBinaryBuffer, m_strMapID);
		BinarySerializeCalLen(oBinaryBuffer, m_nUse);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMapName);
		BinarySerializeRead(oBinaryBuffer, m_strMapID);
		BinarySerializeRead(oBinaryBuffer, m_nUse);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMapName);
		BinarySerializeWrite(oBinaryBuffer, m_strMapID);
		BinarySerializeWrite(oBinaryBuffer, m_nUse);
	}
	return 0;
}

void CParaMap::InitAfterRead()
{
}

BOOL CParaMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CParaMap *p = (CParaMap*)pObj;

	if(m_strMapName != p->m_strMapName)
	{
		return FALSE;
	}

	if(m_strMapID != p->m_strMapID)
	{
		return FALSE;
	}

	if(m_nUse != p->m_nUse)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CParaMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CParaMap *p = (CParaMap*)pDest;

	p->m_strMapName = m_strMapName;
	p->m_strMapID = m_strMapID;
	p->m_nUse = m_nUse;
	return TRUE;
}

CBaseObject* CParaMap::Clone()
{
	CParaMap *p = new CParaMap();
	Copy(p);
	return p;
}

BOOL CParaMap::CanPaste(UINT nClassID)
{
	if (nClassID == MPCLASSID_CVALUEMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CParaMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCValueMapKey)
	{
		pNew = new CValueMap();
	}

	return pNew;
}

CExBaseObject* CParaMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MPCLASSID_CVALUEMAP)
	{
		pNew = new CValueMap();
	}

	return pNew;
}

CValueMap* CParaMap::AddNewValueMap()
{
	CValueMap *pNew = new CValueMap();
	AddNewChild(pNew);
	return pNew;
}

BOOL CParaMap::GetMapValue(CString &strValue)
{
	if (!m_nUse)
	{
		return FALSE;
	}

	CValueMap *pFindMapValue = (CValueMap*)FindByID(strValue);

	if (pFindMapValue != NULL)
	{
		strValue = pFindMapValue->m_strMapID;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
