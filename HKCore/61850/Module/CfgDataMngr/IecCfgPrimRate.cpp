//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgPrimRate.cpp  CIecCfgPrimRate


#include "stdafx.h"
#include "IecCfgPrimRate.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgPrimRate::CIecCfgPrimRate()
{
	//初始化属性
	m_fPrimValue = 1;
	m_fSecondValue = 1;

	//初始化成员变量
}

CIecCfgPrimRate::~CIecCfgPrimRate()
{
}

long CIecCfgPrimRate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPrim_ValueKey, oNode, m_fPrimValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSecond_ValueKey, oNode, m_fSecondValue);
	return 0;
}

long CIecCfgPrimRate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPrim_ValueKey, oElement, m_fPrimValue);
	xml_SetAttributeValue(pXmlKeys->m_strSecond_ValueKey, oElement, m_fSecondValue);
	return 0;
}

long CIecCfgPrimRate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fPrimValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fSecondValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fPrimValue);
		BinarySerializeRead(oBinaryBuffer, m_fSecondValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fPrimValue);
		BinarySerializeWrite(oBinaryBuffer, m_fSecondValue);
	}
	return 0;
}

void CIecCfgPrimRate::InitAfterRead()
{
}

BOOL CIecCfgPrimRate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgPrimRate *p = (CIecCfgPrimRate*)pObj;

	if(m_fPrimValue != p->m_fPrimValue)
	{
		return FALSE;
	}

	if(m_fSecondValue != p->m_fSecondValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgPrimRate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgPrimRate *p = (CIecCfgPrimRate*)pDest;

	p->m_fPrimValue = m_fPrimValue;
	p->m_fSecondValue = m_fSecondValue;
	return TRUE;
}

CBaseObject* CIecCfgPrimRate::Clone()
{
	CIecCfgPrimRate *p = new CIecCfgPrimRate();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgPrimRate::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgPrimRate *p = new CIecCfgPrimRate();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

