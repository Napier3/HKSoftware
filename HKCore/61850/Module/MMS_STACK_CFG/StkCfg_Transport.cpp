//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StkCfg_Transport.cpp  CStkCfg_Transport


#include "stdafx.h"
#include "StkCfg_Transport.h"

CStkCfg_Transport::CStkCfg_Transport()
{
	//��ʼ������

	//��ʼ����Ա����
}

CStkCfg_Transport::~CStkCfg_Transport()
{
}

long CStkCfg_Transport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_Transport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_Transport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CStkCfg_Transport::InitAfterRead()
{
}

BOOL CStkCfg_Transport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_Transport *p = (CStkCfg_Transport*)pObj;

	return TRUE;
}

BOOL CStkCfg_Transport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_Transport *p = (CStkCfg_Transport*)pDest;

	return TRUE;
}

CBaseObject* CStkCfg_Transport::Clone()
{
	CStkCfg_Transport *p = new CStkCfg_Transport();
	Copy(p);
	return p;
}

CExBaseObject* CStkCfg_Transport::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStkCfg_TransportTcpKey)
	{
		pNew = new CStkCfg_TransportTcp();
	}

	return pNew;
}

CExBaseObject* CStkCfg_Transport::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MMSCLASSID_CSTKCFG_TRANSPORTTCP)
	{
		pNew = new CStkCfg_TransportTcp();
	}

	return pNew;
}
