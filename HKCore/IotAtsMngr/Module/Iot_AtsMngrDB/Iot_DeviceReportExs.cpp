//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceReportExs.cpp  CIot_DeviceReportExs


#include "stdafx.h"
#include "Iot_DeviceReportExs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceReportExs::CIot_DeviceReportExs()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceReportExs::~CIot_DeviceReportExs()
{
}

long CIot_DeviceReportExs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceReportExs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceReportExs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceReportExs::InitAfterRead()
{
}

BOOL CIot_DeviceReportExs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceReportExs *p = (CIot_DeviceReportExs*)pObj;

	return TRUE;
}

BOOL CIot_DeviceReportExs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceReportExs *p = (CIot_DeviceReportExs*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceReportExs::Clone()
{
	CIot_DeviceReportExs *p = new CIot_DeviceReportExs();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceReportExs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceReportExs *p = new CIot_DeviceReportExs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceReportExs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEREPORTEX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceReportExs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceReportExKey)
	{
		pNew = new CIot_DeviceReportEx();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceReportExs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEREPORTEX)
	{
		pNew = new CIot_DeviceReportEx();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceReportExs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceReportEx();

	return pNew;
}
