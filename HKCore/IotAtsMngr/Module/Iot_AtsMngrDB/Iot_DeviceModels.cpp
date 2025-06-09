//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceModels.cpp  CIot_DeviceModels


#include "stdafx.h"
#include "Iot_DeviceModels.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceModels::CIot_DeviceModels()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceModels::~CIot_DeviceModels()
{
}

long CIot_DeviceModels::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceModels::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceModels::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceModels::InitAfterRead()
{
}

BOOL CIot_DeviceModels::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceModels *p = (CIot_DeviceModels*)pObj;

	return TRUE;
}

BOOL CIot_DeviceModels::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceModels *p = (CIot_DeviceModels*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceModels::Clone()
{
	CIot_DeviceModels *p = new CIot_DeviceModels();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceModels::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceModels *p = new CIot_DeviceModels();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceModels::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEMODEL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceModels::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceModelKey)
	{
		pNew = new CIot_DeviceModel();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceModels::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEMODEL)
	{
		pNew = new CIot_DeviceModel();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceModels::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceModel();

	return pNew;
}
