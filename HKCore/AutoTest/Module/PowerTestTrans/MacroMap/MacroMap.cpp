//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroMap.cpp  CMacroMap


#include "stdafx.h"
#include "MacroMap.h"

CMacroMap::CMacroMap()
{
	//初始化属性

	//初始化成员变量
}

CMacroMap::~CMacroMap()
{
}

long CMacroMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapNameKey, oNode, m_strMapName);
	xml_GetAttibuteValue(pXmlKeys->m_strMapIDKey, oNode, m_strMapID);
	return 0;
}

long CMacroMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapNameKey, oElement, m_strMapName);
	xml_SetAttributeValue(pXmlKeys->m_strMapIDKey, oElement, m_strMapID);
	return 0;
}

long CMacroMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMapName);
		BinarySerializeCalLen(oBinaryBuffer, m_strMapID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMapName);
		BinarySerializeRead(oBinaryBuffer, m_strMapID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMapName);
		BinarySerializeWrite(oBinaryBuffer, m_strMapID);
	}
	return 0;
}

void CMacroMap::InitAfterRead()
{
}

BOOL CMacroMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMacroMap *p = (CMacroMap*)pObj;

	if(m_strMapName != p->m_strMapName)
	{
		return FALSE;
	}

	if(m_strMapID != p->m_strMapID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMacroMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMacroMap *p = (CMacroMap*)pDest;

	p->m_strMapName = m_strMapName;
	p->m_strMapID = m_strMapID;
	return TRUE;
}

CBaseObject* CMacroMap::Clone()
{
	CMacroMap *p = new CMacroMap();
	Copy(p);
	return p;
}

BOOL CMacroMap::CanPaste(UINT nClassID)
{
	if (nClassID == MPCLASSID_CPARAMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMacroMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCParaMapKey)
	{
		pNew = new CParaMap();
	}

	if (strClassID == pXmlKeys->m_strCParaMapExprKey)
	{
		pNew = new CParaMapExpr();
	}

	return pNew;
}

CExBaseObject* CMacroMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MPCLASSID_CPARAMAP)
	{
		pNew = new CParaMap();
	}

	if (nClassID == MPCLASSID_CPARAMAPEXPR)
	{
		pNew = new CParaMapExpr();
	}

	return pNew;
}

BOOL CMacroMap::MapPara(const CString &strPttParaID, const CString &strPttParaValue, CString &strAtsParaID, CString &strAtsValue)
{
	CParaMap *pParaMap = (CParaMap*)FindByID(strPttParaID);

	if (pParaMap == NULL)
	{
		return FALSE;
	}

	if (pParaMap->m_strMapName == _T(""))   //参数没有映射
	{
		return FALSE;
	}

	if (pParaMap->m_nUse == 0)
	{
		return FALSE;
	}

	strAtsParaID = pParaMap->m_strMapID;
	CValueMap *pValueMap = (CValueMap*)pParaMap->FindByID(strPttParaValue);

	if (pValueMap == NULL)
	{
		strAtsValue = strPttParaValue;
	}
	else
	{
		strAtsValue = pValueMap->m_strMapID;
	}

	return TRUE;
}


BOOL CMacroMap::MapPara(const CString &strPttParaID, CString &strAtsParaID)
{
	CParaMap *pParaMap = (CParaMap*)FindByID(strPttParaID);

	if (pParaMap == NULL)
	{
		return FALSE;
	}

	if (pParaMap->m_strMapName == _T(""))   //参数没有映射
	{
		return FALSE;
	}

	if (pParaMap->m_nUse == 0)
	{
		return FALSE;
	}

	strAtsParaID = pParaMap->m_strMapID;

	return TRUE;
}

CParaMapExpr* CMacroMap::AddNewParaMapExpr()
{
	CParaMapExpr *pNew = new CParaMapExpr();
	AddNewChild(pNew);
	return pNew;
}