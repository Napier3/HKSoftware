//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpAcks.cpp  CMqttPpAcks


#include "stdafx.h"
#include "MqttPpAcks.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpAcks::CMqttPpAcks()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpAcks::~CMqttPpAcks()
{
}

long CMqttPpAcks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpAcks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpAcks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMqttPpAcks::InitAfterRead()
{
}

BOOL CMqttPpAcks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpAcks *p = (CMqttPpAcks*)pObj;

	return TRUE;
}

BOOL CMqttPpAcks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpAcks *p = (CMqttPpAcks*)pDest;

	return TRUE;
}

CBaseObject* CMqttPpAcks::Clone()
{
	CMqttPpAcks *p = new CMqttPpAcks();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpAcks::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpAcks *p = new CMqttPpAcks();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpAcks::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPACK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpAcks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpAckKey)
	{
		pNew = new CMqttPpAck();
	}

	return pNew;
}

CExBaseObject* CMqttPpAcks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPACK)
	{
		pNew = new CMqttPpAck();
	}

	return pNew;
}
