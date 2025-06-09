//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpPrases.cpp  CMqttPpPrases


#include "stdafx.h"
#include "MqttPpPrases.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpPrases::CMqttPpPrases()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpPrases::~CMqttPpPrases()
{
}

long CMqttPpPrases::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpPrases::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpPrases::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CMqttPpPrases::InitAfterRead()
{
}

BOOL CMqttPpPrases::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpPrases *p = (CMqttPpPrases*)pObj;

	return TRUE;
}

BOOL CMqttPpPrases::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpPrases *p = (CMqttPpPrases*)pDest;

	return TRUE;
}

CBaseObject* CMqttPpPrases::Clone()
{
	CMqttPpPrases *p = new CMqttPpPrases();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpPrases::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpPrases *p = new CMqttPpPrases();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpPrases::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPPRASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpPrases::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpPraseKey)
	{
		pNew = new CMqttPpPrase();
	}

	return pNew;
}

CExBaseObject* CMqttPpPrases::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPPRASE)
	{
		pNew = new CMqttPpPrase();
	}

	return pNew;
}
