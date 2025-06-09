//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpProcedure.cpp  CMqttPpProcedure


#include "stdafx.h"
#include "MqttPpProcedure.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpProcedure::CMqttPpProcedure()
{
	//初始化属性

	//初始化成员变量
	m_pAcks = NULL;
	m_pOvertime = NULL;
}

CMqttPpProcedure::~CMqttPpProcedure()
{
}

long CMqttPpProcedure::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPp_PkgKey, oNode, m_strPp_Pkg);
	return 0;
}

long CMqttPpProcedure::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPp_PkgKey, oElement, m_strPp_Pkg);
	return 0;
}

long CMqttPpProcedure::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPp_Pkg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPp_Pkg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPp_Pkg);
	}
	return 0;
}

void CMqttPpProcedure::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MQTTCLASSID_CMQTTPPACKS)
		{
			m_pAcks = (CMqttPpAcks*)p;
		}
		else if (nClassID == MQTTCLASSID_CMQTTPPOVERTIME)
		{
			m_pOvertime = (CMqttPpOverTime*)p;
		}
	}

	if (m_pAcks == NULL)
	{
		m_pAcks = (CMqttPpAcks*)AddNewChild(new CMqttPpAcks());
	}

	if (m_pOvertime == NULL)
	{
		m_pOvertime = (CMqttPpOverTime*)AddNewChild(new CMqttPpOverTime());
	}

}

BOOL CMqttPpProcedure::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpProcedure *p = (CMqttPpProcedure*)pObj;

	if(m_strPp_Pkg != p->m_strPp_Pkg)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMqttPpProcedure::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpProcedure *p = (CMqttPpProcedure*)pDest;

	p->m_strPp_Pkg = m_strPp_Pkg;
	return TRUE;
}

CBaseObject* CMqttPpProcedure::Clone()
{
	CMqttPpProcedure *p = new CMqttPpProcedure();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpProcedure::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpProcedure *p = new CMqttPpProcedure();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpProcedure::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPACKS)
	{
		return TRUE;
	}

	if (nClassID == MQTTCLASSID_CMQTTPPOVERTIME)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpProcedure::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpAcksKey)
	{
		pNew = new CMqttPpAcks();
	}
	else if (strClassID == pXmlKeys->m_strCMqttPpOverTimeKey)
	{
		pNew = new CMqttPpOverTime();
	}

	return pNew;
}

CExBaseObject* CMqttPpProcedure::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPACKS)
	{
		pNew = new CMqttPpAcks();
	}
	else if (nClassID == MQTTCLASSID_CMQTTPPOVERTIME)
	{
		pNew = new CMqttPpOverTime();
	}

	return pNew;
}

CMqttPpAck *CMqttPpProcedure::FindAck(const CString &strID)
{
	if (m_pAcks == NULL)
	{
		return NULL;
	}

	return (CMqttPpAck *)m_pAcks->FindByID(strID);
}