//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenAnalog.cpp  CUibGenAnalog


#include "stdafx.h"
#include "UibGenAnalog.h"

CUibGenAnalog::CUibGenAnalog()
{
	//初始化属性
	m_fZero = 0;
	m_fCoef = 0;
	m_nRand = 0;
	m_fPrimary = 1;
	m_fSecondary = 1;

	//初始化成员变量
	m_dCoef_FreqAngleT = 0;
}

CUibGenAnalog::~CUibGenAnalog()
{
}

long CUibGenAnalog::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strZeroKey, oNode, m_fZero);
	xml_GetAttibuteValue(pXmlKeys->m_strCoefKey, oNode, m_fCoef);
	xml_GetAttibuteValue(pXmlKeys->m_strChIDKey, oNode, m_strChID);
	xml_GetAttibuteValue(pXmlKeys->m_strRandKey, oNode, m_nRand);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strPrimaryKey, oNode, m_fPrimary);
	xml_GetAttibuteValue(pXmlKeys->m_strSecondaryKey, oNode, m_fSecondary);
	return 0;
}

long CUibGenAnalog::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strZeroKey, oElement, m_fZero);
	xml_SetAttributeValue(pXmlKeys->m_strCoefKey, oElement, m_fCoef);
	xml_SetAttributeValue(pXmlKeys->m_strChIDKey, oElement, m_strChID);
	xml_SetAttributeValue(pXmlKeys->m_strRandKey, oElement, m_nRand);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strPrimaryKey, oElement, m_fPrimary);
	xml_SetAttributeValue(pXmlKeys->m_strSecondaryKey, oElement, m_fSecondary);
	return 0;
}

long CUibGenAnalog::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fZero);
		BinarySerializeCalLen(oBinaryBuffer, m_fCoef);
		BinarySerializeCalLen(oBinaryBuffer, m_strChID);
		BinarySerializeCalLen(oBinaryBuffer, m_nRand);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_fPrimary);
		BinarySerializeCalLen(oBinaryBuffer, m_fSecondary);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fZero);
		BinarySerializeRead(oBinaryBuffer, m_fCoef);
		BinarySerializeRead(oBinaryBuffer, m_strChID);
		BinarySerializeRead(oBinaryBuffer, m_nRand);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_fPrimary);
		BinarySerializeRead(oBinaryBuffer, m_fSecondary);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fZero);
		BinarySerializeWrite(oBinaryBuffer, m_fCoef);
		BinarySerializeWrite(oBinaryBuffer, m_strChID);
		BinarySerializeWrite(oBinaryBuffer, m_nRand);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_fPrimary);
		BinarySerializeWrite(oBinaryBuffer, m_fSecondary);
	}
	return 0;
}

void CUibGenAnalog::InitAfterRead()
{
}

BOOL CUibGenAnalog::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUibGenAnalog *p = (CUibGenAnalog*)pObj;

	if(m_fZero != p->m_fZero)
	{
		return FALSE;
	}

	if(m_fCoef != p->m_fCoef)
	{
		return FALSE;
	}

	if(m_strChID != p->m_strChID)
	{
		return FALSE;
	}

	if(m_nRand != p->m_nRand)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_fPrimary != p->m_fPrimary)
	{
		return FALSE;
	}

	if(m_fSecondary != p->m_fSecondary)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUibGenAnalog::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUibGenAnalog *p = (CUibGenAnalog*)pDest;

	p->m_fZero = m_fZero;
	p->m_fCoef = m_fCoef;
	p->m_strChID = m_strChID;
	p->m_nRand = m_nRand;
	p->m_strUnit = m_strUnit;
	p->m_fPrimary = m_fPrimary;
	p->m_fSecondary = m_fSecondary;
	return TRUE;
}

CBaseObject* CUibGenAnalog::Clone()
{
	CUibGenAnalog *p = new CUibGenAnalog();
	Copy(p);
	return p;
}

BOOL CUibGenAnalog::CanPaste(UINT nClassID)
{
	if (nClassID == UIBGCLASSID_CUIBGENHARM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUibGenAnalog::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUibGenHarmKey)
	{
		pNew = new CUibGenHarm();
	}

	return pNew;
}

CExBaseObject* CUibGenAnalog::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UIBGCLASSID_CUIBGENHARM)
	{
		pNew = new CUibGenHarm();
	}

	return pNew;
}

void CUibGenAnalog::Generate(long &nUibGenIndex, long &nCalIndex)
{
	double dValue = 0;
	POS pos = GetHeadPosition();
	CUibGenHarm *pHarm = NULL;

	if (nCalIndex == 100)
	{
		nCalIndex = 100;
	}

	while (pos != NULL)
	{
		pHarm = (CUibGenHarm *)GetNext(pos);
		pHarm->Generate(nCalIndex, m_dCoef_FreqAngleT, dValue);
	}

	dValue -= m_fZero;
	dValue /= m_fCoef;

	if (m_nRand > 0)
	{
		dValue += rand() % m_nRand - m_nRand;
	}

	m_pnAttachBuffer[nUibGenIndex] = (unsigned short)dValue;
}

void CUibGenAnalog::InitGenerate(double dCoef_FreqAngleT)
{
	m_dCoef_FreqAngleT = dCoef_FreqAngleT;
}


