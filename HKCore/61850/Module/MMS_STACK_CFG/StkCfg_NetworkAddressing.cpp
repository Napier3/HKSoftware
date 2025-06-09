//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_NetworkAddressing.cpp  CStkCfg_NetworkAddressing


#include "stdafx.h"
#include "StkCfg_NetworkAddressing.h"

CStkCfg_NetworkAddressing::CStkCfg_NetworkAddressing()
{
	//初始化属性

	//初始化成员变量
	m_pRemoteAddressList = NULL;
}

CStkCfg_NetworkAddressing::~CStkCfg_NetworkAddressing()
{
}

long CStkCfg_NetworkAddressing::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_NetworkAddressing::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_NetworkAddressing::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CStkCfg_NetworkAddressing::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClasID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClasID = p->GetClassID();

		if (nClasID == MMSCLASSID_CSTKCFG_REMOTEADDRESSLIST)
		{
			m_pRemoteAddressList = (CStkCfg_RemoteAddressList *)p;
		}
	}
}

BOOL CStkCfg_NetworkAddressing::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_NetworkAddressing *p = (CStkCfg_NetworkAddressing*)pObj;

	return TRUE;
}

BOOL CStkCfg_NetworkAddressing::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_NetworkAddressing *p = (CStkCfg_NetworkAddressing*)pDest;

	return TRUE;
}

CBaseObject* CStkCfg_NetworkAddressing::Clone()
{
	CStkCfg_NetworkAddressing *p = new CStkCfg_NetworkAddressing();
	Copy(p);
	return p;
}

BOOL CStkCfg_NetworkAddressing::CanPaste(UINT nClassID)
{
	if (nClassID == MMSCLASSID_CSTKCFG_LOCALADDRESSLIST)
	{
		return TRUE;
	}

	if (nClassID == MMSCLASSID_CSTKCFG_REMOTEADDRESSLIST)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStkCfg_NetworkAddressing::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStkCfg_LocalAddressListKey)
	{
		pNew = new CStkCfg_LocalAddressList();
	}
	else if (strClassID == pXmlKeys->m_strCStkCfg_RemoteAddressListKey)
	{
		pNew = new CStkCfg_RemoteAddressList();
	}

	return pNew;
}

CExBaseObject* CStkCfg_NetworkAddressing::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MMSCLASSID_CSTKCFG_LOCALADDRESSLIST)
	{
		pNew = new CStkCfg_LocalAddressList();
	}
	else if (nClassID == MMSCLASSID_CSTKCFG_REMOTEADDRESSLIST)
	{
		pNew = new CStkCfg_RemoteAddressList();
	}

	return pNew;
}
