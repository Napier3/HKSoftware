//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_RemoteAddressList.cpp  CStkCfg_RemoteAddressList


#include "stdafx.h"
#include "StkCfg_RemoteAddressList.h"

CStkCfg_RemoteAddressList::CStkCfg_RemoteAddressList()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_RemoteAddressList::~CStkCfg_RemoteAddressList()
{
}

long CStkCfg_RemoteAddressList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_RemoteAddressList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStkCfg_RemoteAddressList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CStkCfg_RemoteAddressList::InitAfterRead()
{
}

BOOL CStkCfg_RemoteAddressList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_RemoteAddressList *p = (CStkCfg_RemoteAddressList*)pObj;

	return TRUE;
}

BOOL CStkCfg_RemoteAddressList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_RemoteAddressList *p = (CStkCfg_RemoteAddressList*)pDest;

	return TRUE;
}

CBaseObject* CStkCfg_RemoteAddressList::Clone()
{
	CStkCfg_RemoteAddressList *p = new CStkCfg_RemoteAddressList();
	Copy(p);
	return p;
}

BOOL CStkCfg_RemoteAddressList::CanPaste(UINT nClassID)
{
	if (nClassID == MMSCLASSID_CSTKCFG_REMOTEADDRESS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStkCfg_RemoteAddressList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStkCfg_RemoteAddressKey)
	{
		pNew = new CStkCfg_RemoteAddress();
	}

	return pNew;
}

CExBaseObject* CStkCfg_RemoteAddressList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MMSCLASSID_CSTKCFG_REMOTEADDRESS)
	{
		pNew = new CStkCfg_RemoteAddress();
	}

	return pNew;
}

void CStkCfg_RemoteAddressList::SetCount(long nCount)
{
	long nCurrCount = GetCount();

	if (nCurrCount == nCount)
	{
		return;
	}

	CStkCfg_RemoteAddress *pHead = (CStkCfg_RemoteAddress*)GetHead();
	CStkCfg_RemoteAddress *p = NULL;
	long nIndex = 0;
	long nTempCount = 0;

	if (nCount > nCurrCount)
	{
		nTempCount = nCount - nCurrCount;

		for (nIndex=0; nIndex<nTempCount; nIndex++)
		{
			p = (CStkCfg_RemoteAddress*)pHead->Clone();
			AddNewChild(p);
		}
	}
	else
	{
		nTempCount = nCurrCount - nCount;

		for (nIndex=0; nIndex<nTempCount; nIndex++)
		{
			DeleteAt(nCount);
		}
	}
}

