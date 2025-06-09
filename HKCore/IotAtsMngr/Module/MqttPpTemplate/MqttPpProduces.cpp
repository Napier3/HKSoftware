//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpProduces.cpp  CMqttPpProduces


#include "stdafx.h"
#include "MqttPpProduces.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpProduces::CMqttPpProduces()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpProduces::~CMqttPpProduces()
{
}

long CMqttPpProduces::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpProduces::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpProduces::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMqttPpProduces::InitAfterRead()
{
}

BOOL CMqttPpProduces::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpProduces *p = (CMqttPpProduces*)pObj;

	return TRUE;
}

BOOL CMqttPpProduces::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpProduces *p = (CMqttPpProduces*)pDest;

	return TRUE;
}

CBaseObject* CMqttPpProduces::Clone()
{
	CMqttPpProduces *p = new CMqttPpProduces();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpProduces::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpProduces *p = new CMqttPpProduces();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpProduces::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPPRODUCE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpProduces::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpProduceKey)
	{
		pNew = new CMqttPpProduce();
	}

	return pNew;
}

CExBaseObject* CMqttPpProduces::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPPRODUCE)
	{
		pNew = new CMqttPpProduce();
	}

	return pNew;
}
