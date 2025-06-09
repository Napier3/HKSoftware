//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDraw.cpp  CCharMacroDraw


#include "stdafx.h"
#include "CharMacroDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharMacroDraw::CCharMacroDraw()
{
	//初始化属性

	//初始化成员变量
}

CCharMacroDraw::~CCharMacroDraw()
{
}

long CCharMacroDraw::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacroIDKey, oNode, m_strMacroID);
	return 0;
}

long CCharMacroDraw::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacroIDKey, oElement, m_strMacroID);
	return 0;
}

BOOL CCharMacroDraw::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharMacroDraw *p = (CCharMacroDraw*)pObj;

	if(m_strMacroID != p->m_strMacroID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharMacroDraw::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharMacroDraw *p = (CCharMacroDraw*)pDest;

	p->m_strMacroID = m_strMacroID;
	return TRUE;
}

CBaseObject* CCharMacroDraw::Clone()
{
	CCharMacroDraw *p = new CCharMacroDraw();
	Copy(p);
	return p;
}

CExBaseObject* CCharMacroDraw::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CCharMacroDraw::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CCharMacroDraw::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
	}
	return 0;
}

