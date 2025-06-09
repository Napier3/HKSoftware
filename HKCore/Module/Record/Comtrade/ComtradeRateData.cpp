//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ComtradeRateData.cpp  CComtradeRateData


#include "stdafx.h"
#include "ComtradeRateData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CComtradeRateData::CComtradeRateData()
{
	//初始化属性
	m_nSamprate = 0;
	m_nEndsamp = 0;

	//初始化成员变量
}

CComtradeRateData::~CComtradeRateData()
{
}

long CComtradeRateData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nChannelIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strSamprateKey, oNode, m_nSamprate);
	xml_GetAttibuteValue(pXmlKeys->m_strEndsampKey, oNode, m_nEndsamp);
	return 0;
}

long CComtradeRateData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nChannelIndex);
	xml_SetAttributeValue(pXmlKeys->m_strSamprateKey, oElement, m_nSamprate);
	xml_SetAttributeValue(pXmlKeys->m_strEndsampKey, oElement, m_nEndsamp);
	return 0;
}

long CComtradeRateData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSamprate);
		BinarySerializeCalLen(oBinaryBuffer, m_nEndsamp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSamprate);
		BinarySerializeRead(oBinaryBuffer, m_nEndsamp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSamprate);
		BinarySerializeWrite(oBinaryBuffer, m_nEndsamp);
	}
	return 0;
}

void CComtradeRateData::InitAfterRead()
{
}

BOOL CComtradeRateData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CComtradeRateData *p = (CComtradeRateData*)pObj;

	if(m_nSamprate != p->m_nSamprate)
	{
		return FALSE;
	}

	if(m_nEndsamp != p->m_nEndsamp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CComtradeRateData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CComtradeRateData *p = (CComtradeRateData*)pDest;

	p->m_nSamprate = m_nSamprate;
	p->m_nEndsamp = m_nEndsamp;
	return TRUE;
}

CBaseObject* CComtradeRateData::Clone()
{
	CComtradeRateData *p = new CComtradeRateData();
	Copy(p);
	return p;
}

CBaseObject* CComtradeRateData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CComtradeRateData *p = new CComtradeRateData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

