//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestLineDefine.cpp  CCharTestLineDefine


#include "stdafx.h"
#include "CharTestLineDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharTestLineDefine::CCharTestLineDefine()
{
	//初始化属性

	//初始化成员变量
}

CCharTestLineDefine::~CCharTestLineDefine()
{
}

long CCharTestLineDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strExprAngleKey, oNode, m_strExprAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strExprXKey, oNode, m_strExprX);
	xml_GetAttibuteValue(pXmlKeys->m_strExprYKey, oNode, m_strExprY);
	xml_GetAttibuteValue(pXmlKeys->m_strExprRKey, oNode, m_strExprR);
	return 0;
}

long CCharTestLineDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strExprAngleKey, oElement, m_strExprAngle);
	xml_SetAttributeValue(pXmlKeys->m_strExprXKey, oElement, m_strExprX);
	xml_SetAttributeValue(pXmlKeys->m_strExprYKey, oElement, m_strExprY);
	xml_SetAttributeValue(pXmlKeys->m_strExprRKey, oElement, m_strExprR);
	return 0;
}

BOOL CCharTestLineDefine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharTestLineDefine *p = (CCharTestLineDefine*)pDest;

	p->m_strExprAngle = m_strExprAngle;
	p->m_strExprX = m_strExprX;
	p->m_strExprY = m_strExprY;
	p->m_strExprR = m_strExprR;

	return TRUE;
}

CBaseObject* CCharTestLineDefine::Clone()
{
	CCharTestLineDefine *p = new CCharTestLineDefine();
	Copy(p);
	return p;
}

long CCharTestLineDefine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strExprAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strExprX);
		BinarySerializeCalLen(oBinaryBuffer, m_strExprY);
		BinarySerializeCalLen(oBinaryBuffer, m_strExprR);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strExprAngle);
		BinarySerializeRead(oBinaryBuffer, m_strExprX);
		BinarySerializeRead(oBinaryBuffer, m_strExprY);
		BinarySerializeRead(oBinaryBuffer, m_strExprR);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strExprAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strExprX);
		BinarySerializeWrite(oBinaryBuffer, m_strExprY);
		BinarySerializeWrite(oBinaryBuffer, m_strExprR);
	}
	return 0;
}

