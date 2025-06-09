//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_LocalAddressList.cpp  CStkCfg_LocalAddressList


#include "stdafx.h"
#include "StkCfg_LocalAddressList.h"

CStkCfg_LocalAddressList::CStkCfg_LocalAddressList()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_LocalAddressList::~CStkCfg_LocalAddressList()
{
}

long CStkCfg_LocalAddressList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_LocalAddressList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_LocalAddressList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CStkCfg_LocalAddressList::InitAfterRead()
{
}

BOOL CStkCfg_LocalAddressList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_LocalAddressList *p = (CStkCfg_LocalAddressList*)pObj;

	return TRUE;
}

BOOL CStkCfg_LocalAddressList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_LocalAddressList *p = (CStkCfg_LocalAddressList*)pDest;

	return TRUE;
}

CBaseObject* CStkCfg_LocalAddressList::Clone()
{
	CStkCfg_LocalAddressList *p = new CStkCfg_LocalAddressList();
	Copy(p);
	return p;
}

BOOL CStkCfg_LocalAddressList::CanPaste(UINT nClassID)
{
	if (nClassID == MMSCLASSID_CSTKCFG_LOCALADDRESS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStkCfg_LocalAddressList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStkCfg_LocalAddressKey)
	{
		pNew = new CStkCfg_LocalAddress();
	}

	return pNew;
}

CExBaseObject* CStkCfg_LocalAddressList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MMSCLASSID_CSTKCFG_LOCALADDRESS)
	{
		pNew = new CStkCfg_LocalAddress();
	}

	return pNew;
}
