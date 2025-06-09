//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceItemRslts.cpp  CIot_DeviceItemRslts


#include "stdafx.h"
#include "Iot_DeviceItemRslts.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceItemRslts::CIot_DeviceItemRslts()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceItemRslts::~CIot_DeviceItemRslts()
{
}

long CIot_DeviceItemRslts::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceItemRslts::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceItemRslts::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceItemRslts::InitAfterRead()
{
}

BOOL CIot_DeviceItemRslts::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceItemRslts *p = (CIot_DeviceItemRslts*)pObj;

	return TRUE;
}

BOOL CIot_DeviceItemRslts::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceItemRslts *p = (CIot_DeviceItemRslts*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceItemRslts::Clone()
{
	CIot_DeviceItemRslts *p = new CIot_DeviceItemRslts();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceItemRslts::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceItemRslts *p = new CIot_DeviceItemRslts();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceItemRslts::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEITEMRSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceItemRslts::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceItemRsltKey)
	{
		pNew = new CIot_DeviceItemRslt();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceItemRslts::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEITEMRSLT)
	{
		pNew = new CIot_DeviceItemRslt();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceItemRslts::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceItemRslt();

	return pNew;
}
