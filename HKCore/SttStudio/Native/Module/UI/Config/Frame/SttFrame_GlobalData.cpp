//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSttFrame_GlobalData.cpp  CSttFrame_GlobalData


#include "stdafx.h"
#include "SttFrame_GlobalData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttFrame_GlobalData::CSttFrame_GlobalData()
{
	//初始化属性
	m_strValue = _T("");

	//初始化成员变量
}

CSttFrame_GlobalData::~CSttFrame_GlobalData()
{
}

long CSttFrame_GlobalData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CSttFrame_GlobalData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CSttFrame_GlobalData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CSttFrame_GlobalData::InitAfterRead()
{
}

BOOL CSttFrame_GlobalData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttFrame_GlobalData *p = (CSttFrame_GlobalData*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_GlobalData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttFrame_GlobalData *p = (CSttFrame_GlobalData*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CSttFrame_GlobalData::Clone()
{
	CSttFrame_GlobalData *p = new CSttFrame_GlobalData();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_GlobalData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_GlobalData *p = new CSttFrame_GlobalData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}
