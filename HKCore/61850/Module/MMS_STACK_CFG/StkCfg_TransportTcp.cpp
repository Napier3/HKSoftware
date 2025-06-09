//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_TransportTcp.cpp  CStkCfg_TransportTcp


#include "stdafx.h"
#include "StkCfg_TransportTcp.h"

CStkCfg_TransportTcp::CStkCfg_TransportTcp()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_TransportTcp::~CStkCfg_TransportTcp()
{
}

long CStkCfg_TransportTcp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strRfc1006_Max_Tpdu_LenKey, oNode, m_strRfc1006_Max_Tpdu_Len);
	xml_GetElementText(pXmlKeys->m_strRfc1006_Max_Num_ConnsKey, oNode, m_strRfc1006_Max_Num_Conns);
	xml_GetElementText(pXmlKeys->m_strRfc1006_Max_Spdu_OutstandingKey, oNode, m_strRfc1006_Max_Spdu_Outstanding);
	return 0;
}

long CStkCfg_TransportTcp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strRfc1006_Max_Tpdu_LenKey, oXMLDoc, oElement, m_strRfc1006_Max_Tpdu_Len);
	xml_SetElementText(pXmlKeys->m_strRfc1006_Max_Num_ConnsKey, oXMLDoc, oElement, m_strRfc1006_Max_Num_Conns);
	xml_SetElementText(pXmlKeys->m_strRfc1006_Max_Spdu_OutstandingKey, oXMLDoc, oElement, m_strRfc1006_Max_Spdu_Outstanding);
	return 0;
}

long CStkCfg_TransportTcp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRfc1006_Max_Tpdu_Len);
		BinarySerializeCalLen(oBinaryBuffer, m_strRfc1006_Max_Num_Conns);
		BinarySerializeCalLen(oBinaryBuffer, m_strRfc1006_Max_Spdu_Outstanding);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strRfc1006_Max_Tpdu_Len);
		BinarySerializeRead(oBinaryBuffer, m_strRfc1006_Max_Num_Conns);
		BinarySerializeRead(oBinaryBuffer, m_strRfc1006_Max_Spdu_Outstanding);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strRfc1006_Max_Tpdu_Len);
		BinarySerializeWrite(oBinaryBuffer, m_strRfc1006_Max_Num_Conns);
		BinarySerializeWrite(oBinaryBuffer, m_strRfc1006_Max_Spdu_Outstanding);
	}
	return 0;
}

void CStkCfg_TransportTcp::InitAfterRead()
{
}

BOOL CStkCfg_TransportTcp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_TransportTcp *p = (CStkCfg_TransportTcp*)pObj;

	if(m_strRfc1006_Max_Tpdu_Len != p->m_strRfc1006_Max_Tpdu_Len)
	{
		return FALSE;
	}

	if(m_strRfc1006_Max_Num_Conns != p->m_strRfc1006_Max_Num_Conns)
	{
		return FALSE;
	}

	if(m_strRfc1006_Max_Spdu_Outstanding != p->m_strRfc1006_Max_Spdu_Outstanding)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStkCfg_TransportTcp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_TransportTcp *p = (CStkCfg_TransportTcp*)pDest;

	p->m_strRfc1006_Max_Tpdu_Len = m_strRfc1006_Max_Tpdu_Len;
	p->m_strRfc1006_Max_Num_Conns = m_strRfc1006_Max_Num_Conns;
	p->m_strRfc1006_Max_Spdu_Outstanding = m_strRfc1006_Max_Spdu_Outstanding;
	return TRUE;
}

CBaseObject* CStkCfg_TransportTcp::Clone()
{
	CStkCfg_TransportTcp *p = new CStkCfg_TransportTcp();
	Copy(p);
	return p;
}

