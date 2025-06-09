//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpOverTime.cpp  CMqttPpOverTime


#include "stdafx.h"
#include "MqttPpOverTime.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpOverTime::CMqttPpOverTime()
{
	//��ʼ������
	m_nValue = 0;

	//��ʼ����Ա����
}

CMqttPpOverTime::~CMqttPpOverTime()
{
}

long CMqttPpOverTime::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_nValue);
	return 0;
}

long CMqttPpOverTime::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_nValue);
	return 0;
}

long CMqttPpOverTime::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nValue);
	}
	return 0;
}

void CMqttPpOverTime::InitAfterRead()
{
}

BOOL CMqttPpOverTime::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpOverTime *p = (CMqttPpOverTime*)pObj;

	if(m_nValue != p->m_nValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMqttPpOverTime::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpOverTime *p = (CMqttPpOverTime*)pDest;

	p->m_nValue = m_nValue;
	return TRUE;
}

CBaseObject* CMqttPpOverTime::Clone()
{
	CMqttPpOverTime *p = new CMqttPpOverTime();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpOverTime::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpOverTime *p = new CMqttPpOverTime();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

