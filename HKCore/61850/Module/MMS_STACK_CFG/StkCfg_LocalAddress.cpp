//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_LocalAddress.cpp  CStkCfg_LocalAddress


#include "stdafx.h"
#include "StkCfg_LocalAddress.h"

CStkCfg_LocalAddress::CStkCfg_LocalAddress()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_LocalAddress::~CStkCfg_LocalAddress()
{
}

long CStkCfg_LocalAddress::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strAR_NameKey, oNode, m_strAR_Name);
	xml_GetElementText(pXmlKeys->m_strAP_TitleKey, oNode, m_strAP_Title);
	xml_GetElementText(pXmlKeys->m_strPselKey, oNode, m_strPsel);
	xml_GetElementText(pXmlKeys->m_strAE_QualifierKey, oNode, m_strAE_Qualifier);
	xml_GetElementText(pXmlKeys->m_strSselKey, oNode, m_strSsel);
	xml_GetElementText(pXmlKeys->m_strTselKey, oNode, m_strTsel);
	xml_GetElementText(pXmlKeys->m_strTransportTypeKey, oNode, m_strTransportType);

	return 0;
}

long CStkCfg_LocalAddress::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strAR_NameKey, oXMLDoc, oElement, m_strAR_Name);
	xml_SetElementText(pXmlKeys->m_strAP_TitleKey, oXMLDoc, oElement, m_strAP_Title);
	xml_SetElementText(pXmlKeys->m_strPselKey, oXMLDoc, oElement, m_strPsel);
	xml_SetElementText(pXmlKeys->m_strAE_QualifierKey, oXMLDoc, oElement, m_strAE_Qualifier);
	xml_SetElementText(pXmlKeys->m_strSselKey, oXMLDoc, oElement, m_strSsel);
	xml_SetElementText(pXmlKeys->m_strTselKey, oXMLDoc, oElement, m_strTsel);
	xml_SetElementText(pXmlKeys->m_strTransportTypeKey, oXMLDoc, oElement, m_strTransportType);

	return 0;
}

long CStkCfg_LocalAddress::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAR_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strAP_Title);
		BinarySerializeCalLen(oBinaryBuffer, m_strPsel);
		BinarySerializeCalLen(oBinaryBuffer, m_strAE_Qualifier);
		BinarySerializeCalLen(oBinaryBuffer, m_strSsel);
		BinarySerializeCalLen(oBinaryBuffer, m_strTsel);
		BinarySerializeCalLen(oBinaryBuffer, m_strTransportType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAR_Name);
		BinarySerializeRead(oBinaryBuffer, m_strAP_Title);
		BinarySerializeRead(oBinaryBuffer, m_strPsel);
		BinarySerializeRead(oBinaryBuffer, m_strAE_Qualifier);
		BinarySerializeRead(oBinaryBuffer, m_strSsel);
		BinarySerializeRead(oBinaryBuffer, m_strTsel);
		BinarySerializeRead(oBinaryBuffer, m_strTransportType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAR_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strAP_Title);
		BinarySerializeWrite(oBinaryBuffer, m_strPsel);
		BinarySerializeWrite(oBinaryBuffer, m_strAE_Qualifier);
		BinarySerializeWrite(oBinaryBuffer, m_strSsel);
		BinarySerializeWrite(oBinaryBuffer, m_strTsel);
		BinarySerializeWrite(oBinaryBuffer, m_strTransportType);
	}
	return 0;
}

void CStkCfg_LocalAddress::InitAfterRead()
{
}

BOOL CStkCfg_LocalAddress::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_LocalAddress *p = (CStkCfg_LocalAddress*)pObj;

	if(m_strAR_Name != p->m_strAR_Name)
	{
		return FALSE;
	}

	if(m_strAP_Title != p->m_strAP_Title)
	{
		return FALSE;
	}

	if(m_strPsel != p->m_strPsel)
	{
		return FALSE;
	}

	if(m_strAE_Qualifier != p->m_strAE_Qualifier)
	{
		return FALSE;
	}

	if(m_strSsel != p->m_strSsel)
	{
		return FALSE;
	}

	if(m_strTsel != p->m_strTsel)
	{
		return FALSE;
	}

	if(m_strTransportType != p->m_strTransportType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStkCfg_LocalAddress::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_LocalAddress *p = (CStkCfg_LocalAddress*)pDest;

	p->m_strAR_Name = m_strAR_Name;
	p->m_strAP_Title = m_strAP_Title;
	p->m_strPsel = m_strPsel;
	p->m_strAE_Qualifier = m_strAE_Qualifier;
	p->m_strSsel = m_strSsel;
	p->m_strTsel = m_strTsel;
	p->m_strTransportType = m_strTransportType;
	return TRUE;
}

CBaseObject* CStkCfg_LocalAddress::Clone()
{
	CStkCfg_LocalAddress *p = new CStkCfg_LocalAddress();
	Copy(p);
	return p;
}

