//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_RemoteAddress.cpp  CStkCfg_RemoteAddress


#include "stdafx.h"
#include "StkCfg_RemoteAddress.h"

CStkCfg_RemoteAddress::CStkCfg_RemoteAddress()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_RemoteAddress::~CStkCfg_RemoteAddress()
{
}

long CStkCfg_RemoteAddress::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strAR_NameKey, oNode, m_strAR_Name);
	xml_GetElementText(pXmlKeys->m_strAP_TitleKey, oNode, m_strAP_Title);
	xml_GetElementText(pXmlKeys->m_strAE_QualifierKey, oNode, m_strAE_Qualifier);
	xml_GetElementText(pXmlKeys->m_strPselKey, oNode, m_strPsel);
	xml_GetElementText(pXmlKeys->m_strSselKey, oNode, m_strSsel);
	xml_GetElementText(pXmlKeys->m_strTselKey, oNode, m_strTsel);

	xml_GetElementText(pXmlKeys->m_strEncryptPswKey, oNode, m_strPSW);
	xml_GetElementText(pXmlKeys->m_strEncryptKeyKey, oNode, m_strKey);

	return 0;
}

long CStkCfg_RemoteAddress::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strAR_NameKey, oXMLDoc, oElement, m_strAR_Name);
	xml_SetElementText(pXmlKeys->m_strAP_TitleKey, oXMLDoc, oElement, m_strAP_Title);
	xml_SetElementText(pXmlKeys->m_strAE_QualifierKey, oXMLDoc, oElement, m_strAE_Qualifier);
	xml_SetElementText(pXmlKeys->m_strPselKey, oXMLDoc, oElement, m_strPsel);
	xml_SetElementText(pXmlKeys->m_strSselKey, oXMLDoc, oElement, m_strSsel);
	xml_SetElementText(pXmlKeys->m_strTselKey, oXMLDoc, oElement, m_strTsel);

	xml_SetElementText(pXmlKeys->m_strEncryptPswKey, oXMLDoc, oElement, m_strPSW);
	xml_SetElementText(pXmlKeys->m_strEncryptKeyKey, oXMLDoc, oElement, m_strKey);

	return 0;
}

long CStkCfg_RemoteAddress::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAR_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strAP_Title);
		BinarySerializeCalLen(oBinaryBuffer, m_strAE_Qualifier);
		BinarySerializeCalLen(oBinaryBuffer, m_strPsel);
		BinarySerializeCalLen(oBinaryBuffer, m_strSsel);
		BinarySerializeCalLen(oBinaryBuffer, m_strTsel);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAR_Name);
		BinarySerializeRead(oBinaryBuffer, m_strAP_Title);
		BinarySerializeRead(oBinaryBuffer, m_strAE_Qualifier);
		BinarySerializeRead(oBinaryBuffer, m_strPsel);
		BinarySerializeRead(oBinaryBuffer, m_strSsel);
		BinarySerializeRead(oBinaryBuffer, m_strTsel);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAR_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strAP_Title);
		BinarySerializeWrite(oBinaryBuffer, m_strAE_Qualifier);
		BinarySerializeWrite(oBinaryBuffer, m_strPsel);
		BinarySerializeWrite(oBinaryBuffer, m_strSsel);
		BinarySerializeWrite(oBinaryBuffer, m_strTsel);
	}
	return 0;
}

void CStkCfg_RemoteAddress::InitAfterRead()
{
}

BOOL CStkCfg_RemoteAddress::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_RemoteAddress *p = (CStkCfg_RemoteAddress*)pObj;

	if(m_strAR_Name != p->m_strAR_Name)
	{
		return FALSE;
	}

	if(m_strAP_Title != p->m_strAP_Title)
	{
		return FALSE;
	}

	if(m_strAE_Qualifier != p->m_strAE_Qualifier)
	{
		return FALSE;
	}

	if(m_strPsel != p->m_strPsel)
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

	return TRUE;
}

BOOL CStkCfg_RemoteAddress::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_RemoteAddress *p = (CStkCfg_RemoteAddress*)pDest;

	p->m_strAR_Name = m_strAR_Name;
	p->m_strAP_Title = m_strAP_Title;
	p->m_strAE_Qualifier = m_strAE_Qualifier;
	p->m_strPsel = m_strPsel;
	p->m_strSsel = m_strSsel;
	p->m_strTsel = m_strTsel;
	return TRUE;
}

CBaseObject* CStkCfg_RemoteAddress::Clone()
{
	CStkCfg_RemoteAddress *p = new CStkCfg_RemoteAddress();
	Copy(p);
	return p;
}

CExBaseObject* CStkCfg_RemoteAddress::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStkCfg_NetAddrKey)
	{
		pNew = new CStkCfg_NetAddr();
	}

	return pNew;
}

CExBaseObject* CStkCfg_RemoteAddress::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MMSCLASSID_CSTKCFG_NETADDR)
	{
		pNew = new CStkCfg_NetAddr();
	}

	return pNew;
}

void CStkCfg_RemoteAddress::SetIP(const CString &strIP)
{
	CStkCfg_NetAddr *p = (CStkCfg_NetAddr*)GetHead();

	if (p == NULL)
	{
		return;
	}

	p->m_strNetAddr = strIP;
}

CString CStkCfg_RemoteAddress::GetIP()
{
	CStkCfg_NetAddr *p = (CStkCfg_NetAddr*)GetHead();

	if (p == NULL)
	{
		return _T("192.168.1.100");
	}

	return p->m_strNetAddr;
}

