//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsDevice.cpp  CMmsDevice


#include "stdafx.h"
#include "MmsDevice.h"

CMmsDevice::CMmsDevice()
{
	//初始化属性

	//初始化成员变量
}

CMmsDevice::~CMmsDevice()
{
}

long CMmsDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMmsDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMmsDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CMmsDevice::InitAfterRead()
{
}

BOOL CMmsDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMmsDevice *p = (CMmsDevice*)pObj;

	return TRUE;
}

BOOL CMmsDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMmsDevice *p = (CMmsDevice*)pDest;

	return TRUE;
}

CBaseObject* CMmsDevice::Clone()
{
	CMmsDevice *p = new CMmsDevice();
	Copy(p);
	return p;
}

BOOL CMmsDevice::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRCDDIR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMmsDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRcdDirKey)
	{
		pNew = new CRcdDir();
	}

	return pNew;
}

CExBaseObject* CMmsDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRCDDIR)
	{
		pNew = new CRcdDir();
	}

	return pNew;
}
