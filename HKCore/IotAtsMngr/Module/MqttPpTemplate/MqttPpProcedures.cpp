//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpProcedures.cpp  CMqttPpProcedures


#include "stdafx.h"
#include "MqttPpProcedures.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpProcedures::CMqttPpProcedures()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpProcedures::~CMqttPpProcedures()
{
}

long CMqttPpProcedures::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpProcedures::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMqttPpProcedures::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMqttPpProcedures::InitAfterRead()
{
}

BOOL CMqttPpProcedures::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpProcedures *p = (CMqttPpProcedures*)pObj;

	return TRUE;
}

BOOL CMqttPpProcedures::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpProcedures *p = (CMqttPpProcedures*)pDest;

	return TRUE;
}

CBaseObject* CMqttPpProcedures::Clone()
{
	CMqttPpProcedures *p = new CMqttPpProcedures();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpProcedures::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpProcedures *p = new CMqttPpProcedures();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpProcedures::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPPROCEDURE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpProcedures::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpProcedureKey)
	{
		pNew = new CMqttPpProcedure();
	}

	return pNew;
}

CExBaseObject* CMqttPpProcedures::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPPROCEDURE)
	{
		pNew = new CMqttPpProcedure();
	}

	return pNew;
}
