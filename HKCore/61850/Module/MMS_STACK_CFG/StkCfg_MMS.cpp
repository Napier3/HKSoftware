//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_MMS.cpp  CStkCfg_MMS


#include "stdafx.h"
#include "StkCfg_MMS.h"

CStkCfg_MMS::CStkCfg_MMS()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_MMS::~CStkCfg_MMS()
{
}

long CStkCfg_MMS::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strMax_Mms_Pdu_LengthKey, oNode, m_strMax_Mms_Pdu_Length);
	xml_GetElementText(pXmlKeys->m_strMax_Calling_ConnectionsKey, oNode, m_strMax_Calling_Connections);
	xml_GetElementText(pXmlKeys->m_strMax_Called_ConnectionsKey, oNode, m_strMax_Called_Connections);
	return 0;
}

long CStkCfg_MMS::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strMax_Mms_Pdu_LengthKey, oXMLDoc, oElement, m_strMax_Mms_Pdu_Length);
	xml_SetElementText(pXmlKeys->m_strMax_Calling_ConnectionsKey, oXMLDoc, oElement, m_strMax_Calling_Connections);
	xml_SetElementText(pXmlKeys->m_strMax_Called_ConnectionsKey, oXMLDoc, oElement, m_strMax_Called_Connections);
	return 0;
}

long CStkCfg_MMS::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMax_Mms_Pdu_Length);
		BinarySerializeCalLen(oBinaryBuffer, m_strMax_Calling_Connections);
		BinarySerializeCalLen(oBinaryBuffer, m_strMax_Called_Connections);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMax_Mms_Pdu_Length);
		BinarySerializeRead(oBinaryBuffer, m_strMax_Calling_Connections);
		BinarySerializeRead(oBinaryBuffer, m_strMax_Called_Connections);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMax_Mms_Pdu_Length);
		BinarySerializeWrite(oBinaryBuffer, m_strMax_Calling_Connections);
		BinarySerializeWrite(oBinaryBuffer, m_strMax_Called_Connections);
	}
	return 0;
}

void CStkCfg_MMS::InitAfterRead()
{
}

BOOL CStkCfg_MMS::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_MMS *p = (CStkCfg_MMS*)pObj;

	if(m_strMax_Mms_Pdu_Length != p->m_strMax_Mms_Pdu_Length)
	{
		return FALSE;
	}

	if(m_strMax_Calling_Connections != p->m_strMax_Calling_Connections)
	{
		return FALSE;
	}

	if(m_strMax_Called_Connections != p->m_strMax_Called_Connections)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStkCfg_MMS::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_MMS *p = (CStkCfg_MMS*)pDest;

	p->m_strMax_Mms_Pdu_Length = m_strMax_Mms_Pdu_Length;
	p->m_strMax_Calling_Connections = m_strMax_Calling_Connections;
	p->m_strMax_Called_Connections = m_strMax_Called_Connections;
	return TRUE;
}

CBaseObject* CStkCfg_MMS::Clone()
{
	CStkCfg_MMS *p = new CStkCfg_MMS();
	Copy(p);
	return p;
}

