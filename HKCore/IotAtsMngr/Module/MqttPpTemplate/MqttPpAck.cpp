//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpAck.cpp  CMqttPpAck


#include "stdafx.h"
#include "MqttPpAck.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpAck::CMqttPpAck()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpAck::~CMqttPpAck()
{
}

long CMqttPpAck::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPp_PkgKey, oNode, m_strPp_Pkg);
	xml_GetAttibuteValue(pXmlKeys->m_strJump_ToKey, oNode, m_strJump_To);
	return 0;
}

long CMqttPpAck::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPp_PkgKey, oElement, m_strPp_Pkg);
	xml_SetAttributeValue(pXmlKeys->m_strJump_ToKey, oElement, m_strJump_To);
	return 0;
}

long CMqttPpAck::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPp_Pkg);
		BinarySerializeCalLen(oBinaryBuffer, m_strJump_To);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPp_Pkg);
		BinarySerializeRead(oBinaryBuffer, m_strJump_To);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPp_Pkg);
		BinarySerializeWrite(oBinaryBuffer, m_strJump_To);
	}
	return 0;
}

void CMqttPpAck::InitAfterRead()
{
}

BOOL CMqttPpAck::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpAck *p = (CMqttPpAck*)pObj;

	if(m_strPp_Pkg != p->m_strPp_Pkg)
	{
		return FALSE;
	}

	if(m_strJump_To != p->m_strJump_To)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMqttPpAck::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpAck *p = (CMqttPpAck*)pDest;

	p->m_strPp_Pkg = m_strPp_Pkg;
	p->m_strJump_To = m_strJump_To;
	return TRUE;
}

CBaseObject* CMqttPpAck::Clone()
{
	CMqttPpAck *p = new CMqttPpAck();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpAck::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpAck *p = new CMqttPpAck();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

