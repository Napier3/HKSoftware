//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttDataObj.cpp  CSttDataObj


#include "stdafx.h"
#include "SttDataObj.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttDataObj::CSttDataObj()
{
	//初始化属性
	m_fMinVal = 0;
	m_fMaxVal = 0;
	m_fStepVal = 0;
	m_nDataIndex = 0;

	//初始化成员变量
}

CSttDataObj::~CSttDataObj()
{
}

long CSttDataObj::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strDefaultValueKey, oNode, m_strDefaultValue);
	xml_GetAttibuteValue(pXmlKeys->m_strMinValKey, oNode, m_fMinVal);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxValKey, oNode, m_fMaxVal);
	xml_GetAttibuteValue(pXmlKeys->m_strStepKey, oNode, m_fStepVal);
	xml_GetAttibuteValue(pXmlKeys->m_strDataIndexKey, oNode, m_nDataIndex);
	return 0;
}

long CSttDataObj::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strDefaultValueKey, oElement, m_strDefaultValue);
	xml_SetAttributeValue(pXmlKeys->m_strMinValKey, oElement, m_fMinVal);
	xml_SetAttributeValue(pXmlKeys->m_strMaxValKey, oElement, m_fMaxVal);
	xml_SetAttributeValue(pXmlKeys->m_strStepKey, oElement, m_fStepVal);
	xml_SetAttributeValue(pXmlKeys->m_strDataIndexKey, oElement, m_nDataIndex);
	return 0;
}

long CSttDataObj::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fMinVal);
		BinarySerializeCalLen(oBinaryBuffer, m_fMaxVal);
		BinarySerializeCalLen(oBinaryBuffer, m_fStepVal);
		BinarySerializeCalLen(oBinaryBuffer, m_nDataIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeRead(oBinaryBuffer, m_fMinVal);
		BinarySerializeRead(oBinaryBuffer, m_fMaxVal);
		BinarySerializeRead(oBinaryBuffer, m_fStepVal);
		BinarySerializeRead(oBinaryBuffer, m_nDataIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeWrite(oBinaryBuffer, m_fMinVal);
		BinarySerializeWrite(oBinaryBuffer, m_fMaxVal);
		BinarySerializeWrite(oBinaryBuffer, m_fStepVal);
		BinarySerializeWrite(oBinaryBuffer, m_nDataIndex);
	}
	return 0;
}

void CSttDataObj::InitAfterRead()
{
}

BOOL CSttDataObj::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttDataObj *p = (CSttDataObj*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strDefaultValue != p->m_strDefaultValue)
	{
		return FALSE;
	}

	if(m_fMinVal != p->m_fMinVal)
	{
		return FALSE;
	}

	if(m_fMaxVal != p->m_fMaxVal)
	{
		return FALSE;
	}

	if(m_fStepVal != p->m_fStepVal)
	{
		return FALSE;
	}

	if(m_nDataIndex != p->m_nDataIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttDataObj::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttDataObj *p = (CSttDataObj*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strUnit = m_strUnit;
	p->m_strValue = m_strValue;
	p->m_strDefaultValue = m_strDefaultValue;
	p->m_fMinVal = m_fMinVal;
	p->m_fMaxVal = m_fMaxVal;
	p->m_fStepVal = m_fStepVal;
	p->m_nDataIndex = m_nDataIndex;
	return TRUE;
}

CBaseObject* CSttDataObj::Clone()
{
	CSttDataObj *p = new CSttDataObj();
	Copy(p);
	return p;
}

CBaseObject* CSttDataObj::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttDataObj *p = new CSttDataObj();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttDataObj::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttDataObj::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttDataObj::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
