//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceModelDirs.cpp  CIot_DeviceModelDirs


#include "stdafx.h"
#include "Iot_DeviceModelDirs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceModelDirs::CIot_DeviceModelDirs()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceModelDirs::~CIot_DeviceModelDirs()
{
}

long CIot_DeviceModelDirs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceModelDirs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceModelDirs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceModelDirs::InitAfterRead()
{
}

BOOL CIot_DeviceModelDirs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceModelDirs *p = (CIot_DeviceModelDirs*)pObj;

	return TRUE;
}

BOOL CIot_DeviceModelDirs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceModelDirs *p = (CIot_DeviceModelDirs*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceModelDirs::Clone()
{
	CIot_DeviceModelDirs *p = new CIot_DeviceModelDirs();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceModelDirs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceModelDirs *p = new CIot_DeviceModelDirs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceModelDirs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEMODELDIR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceModelDirs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceModelDirKey)
	{
		pNew = new CIot_DeviceModelDir();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceModelDirs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEMODELDIR)
	{
		pNew = new CIot_DeviceModelDir();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceModelDirs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceModelDir();

	return pNew;
}
