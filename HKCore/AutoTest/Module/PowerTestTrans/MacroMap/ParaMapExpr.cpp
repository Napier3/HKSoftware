//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ParaMapExpr.cpp  CParaMapExpr


#include "stdafx.h"
#include "ParaMapExpr.h"

CParaMapCal::CParaMapCal()
{
	//初始化属性

	//初始化成员变量
}

CParaMapCal::~CParaMapCal()
{
}

long CParaMapCal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMapNameKey, oNode, m_strMapName);
	xml_GetAttibuteValue(pXmlKeys->m_strMapIDKey, oNode, m_strMapID);
	xml_GetAttibuteValue(pXmlKeys->m_strCalScriptKey, oNode, m_strScript);

	return 0;
}

long CParaMapCal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMapNameKey, oElement, m_strMapName);
	xml_SetAttributeValue(pXmlKeys->m_strMapIDKey, oElement, m_strMapID);
	xml_SetAttributeValue(pXmlKeys->m_strCalScriptKey, oElement, m_strScript);

	return 0;
}

long CParaMapCal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMapName);
		BinarySerializeCalLen(oBinaryBuffer, m_strMapID);
		BinarySerializeCalLen(oBinaryBuffer, m_strScript);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMapName);
		BinarySerializeRead(oBinaryBuffer, m_strMapID);
		BinarySerializeRead(oBinaryBuffer, m_strScript);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMapName);
		BinarySerializeWrite(oBinaryBuffer, m_strMapID);
		BinarySerializeWrite(oBinaryBuffer, m_strScript);
	}
	return 0;
}

void CParaMapCal::InitAfterRead()
{
}

BOOL CParaMapCal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CParaMapCal *p = (CParaMapCal*)pObj;

	if(m_strMapName != p->m_strMapName)
	{
		return FALSE;
	}

	if(m_strMapID != p->m_strMapID)
	{
		return FALSE;
	}

	if(m_strScript != p->m_strScript)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CParaMapCal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CParaMapCal *p = (CParaMapCal*)pDest;

	p->m_strMapName = m_strMapName;
	p->m_strMapID = m_strMapID;
	p->m_strScript = m_strScript;

	return TRUE;
}

CBaseObject* CParaMapCal::Clone()
{
	CParaMapCal *p = new CParaMapCal();
	Copy(p);
	return p;
}

//////////////////////////////////////////////////////////////////////////////
//CParaMapExpr
CParaMapExpr::CParaMapExpr()
{
	//初始化属性

	//初始化成员变量
}

CParaMapExpr::~CParaMapExpr()
{
}

long CParaMapExpr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strExprKey, oNode, m_strExpr);
	return 0;
}

long CParaMapExpr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strExprKey, oElement, m_strExpr);

	return 0;
}

long CParaMapExpr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strExpr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strExpr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strExpr);
	}
	return 0;
}

void CParaMapExpr::InitAfterRead()
{
}

BOOL CParaMapExpr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CParaMapExpr *p = (CParaMapExpr*)pObj;

	if(m_strExpr != p->m_strExpr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CParaMapExpr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CParaMapExpr *p = (CParaMapExpr*)pDest;
	p->m_strExpr = m_strExpr;
	
	return TRUE;
}

CBaseObject* CParaMapExpr::Clone()
{
	CParaMapExpr *p = new CParaMapExpr();
	Copy(p);
	return p;
}

BOOL CParaMapExpr::CanPaste(UINT nClassID)
{
	if (nClassID == MPCLASSID_CVALUEMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CParaMapExpr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCParaMapCalKey)
	{
		pNew = new CParaMapCal();
	}

	return pNew;
}

CExBaseObject* CParaMapExpr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MPCLASSID_CPARAMAPCAL)
	{
		pNew = new CParaMapCal();
	}

	return pNew;
}

CParaMapCal* CParaMapExpr::AddNewParaMapCal()
{
	CParaMapCal *pNew = new CParaMapCal();
	AddNewChild(pNew);
	return pNew;
}
