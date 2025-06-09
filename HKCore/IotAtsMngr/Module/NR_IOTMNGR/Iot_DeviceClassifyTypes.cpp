//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceClassifyTypes.cpp  CIot_DeviceClassifyTypes


#include "stdafx.h"
#include "Iot_DeviceClassifyTypes.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceClassifyTypes::CIot_DeviceClassifyTypes()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceClassifyTypes::~CIot_DeviceClassifyTypes()
{
}

long CIot_DeviceClassifyTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceClassifyTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceClassifyTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceClassifyTypes::InitAfterRead()
{
}

BOOL CIot_DeviceClassifyTypes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceClassifyTypes *p = (CIot_DeviceClassifyTypes*)pObj;

	return TRUE;
}

BOOL CIot_DeviceClassifyTypes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceClassifyTypes *p = (CIot_DeviceClassifyTypes*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceClassifyTypes::Clone()
{
	CIot_DeviceClassifyTypes *p = new CIot_DeviceClassifyTypes();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceClassifyTypes::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceClassifyTypes *p = new CIot_DeviceClassifyTypes();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceClassifyTypes::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICECLASSIFYTYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceClassifyTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceClassifyTypeKey)
	{
		pNew = new CIot_DeviceClassifyType();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceClassifyTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICECLASSIFYTYPE)
	{
		pNew = new CIot_DeviceClassifyType();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceClassifyTypes::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceClassifyType();

	return pNew;
}
