//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XSclFileObj.cpp  CXSclFileObj


#include "stdafx.h"
#include "XSclFileObj.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXSclFileObj::CXSclFileObj()
{
	//初始化属性
	m_nSize = 0;
	m_nUse = 0;

	//初始化成员变量
}

CXSclFileObj::~CXSclFileObj()
{
}

long CXSclFileObj::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclFileMngrXmlRWKeys *pXmlKeys = (CSclFileMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCurr_Sel_IedKey, oNode, m_strCurrSelIED);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	xml_GetAttibuteValue(pXmlKeys->m_strSscl_PathKey, oNode, m_strSsclPath);
	xml_GetAttibuteValue(pXmlKeys->m_strScl_PathKey, oNode, m_strSclPath);
	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	return 0;
}

long CXSclFileObj::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclFileMngrXmlRWKeys *pXmlKeys = (CSclFileMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCurr_Sel_IedKey, oElement, m_strCurrSelIED);
	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	xml_SetAttributeValue(pXmlKeys->m_strSscl_PathKey, oElement, m_strSsclPath);
	xml_SetAttributeValue(pXmlKeys->m_strScl_PathKey, oElement, m_strSclPath);
	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_nUse);
	return 0;
}

long CXSclFileObj::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCurrSelIED);
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
		BinarySerializeCalLen(oBinaryBuffer, m_strSsclPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strSclPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nUse);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCurrSelIED);
		BinarySerializeRead(oBinaryBuffer, m_nSize);
		BinarySerializeRead(oBinaryBuffer, m_strSsclPath);
		BinarySerializeRead(oBinaryBuffer, m_strSclPath);
		BinarySerializeRead(oBinaryBuffer, m_nUse);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCurrSelIED);
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
		BinarySerializeWrite(oBinaryBuffer, m_strSsclPath);
		BinarySerializeWrite(oBinaryBuffer, m_strSclPath);
		BinarySerializeWrite(oBinaryBuffer, m_nUse);
	}
	return 0;
}

void CXSclFileObj::InitAfterRead()
{
}

BOOL CXSclFileObj::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXSclFileObj *p = (CXSclFileObj*)pObj;

	if(m_strCurrSelIED != p->m_strCurrSelIED)
	{
		return FALSE;
	}

	if(m_nSize != p->m_nSize)
	{
		return FALSE;
	}

	if(m_strSsclPath != p->m_strSsclPath)
	{
		return FALSE;
	}

	if(m_strSclPath != p->m_strSclPath)
	{
		return FALSE;
	}

	if(m_nUse != p->m_nUse)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXSclFileObj::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXSclFileObj *p = (CXSclFileObj*)pDest;

	p->m_strCurrSelIED = m_strCurrSelIED;
	p->m_nSize = m_nSize;
	p->m_strSsclPath = m_strSsclPath;
	p->m_strSclPath = m_strSclPath;
	p->m_nUse = m_nUse;
	return TRUE;
}

CBaseObject* CXSclFileObj::Clone()
{
	CXSclFileObj *p = new CXSclFileObj();
	Copy(p);
	return p;
}

CBaseObject* CXSclFileObj::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CXSclFileObj *p = new CXSclFileObj();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

