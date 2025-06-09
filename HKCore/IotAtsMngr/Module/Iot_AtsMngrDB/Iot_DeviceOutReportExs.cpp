//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceOutReportExs.cpp  CIot_DeviceOutReportExs


#include "stdafx.h"
#include "Iot_DeviceOutReportExs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceOutReportExs::CIot_DeviceOutReportExs()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceOutReportExs::~CIot_DeviceOutReportExs()
{
}

long CIot_DeviceOutReportExs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceOutReportExs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceOutReportExs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceOutReportExs::InitAfterRead()
{
}

BOOL CIot_DeviceOutReportExs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceOutReportExs *p = (CIot_DeviceOutReportExs*)pObj;

	return TRUE;
}

BOOL CIot_DeviceOutReportExs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceOutReportExs *p = (CIot_DeviceOutReportExs*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceOutReportExs::Clone()
{
	CIot_DeviceOutReportExs *p = new CIot_DeviceOutReportExs();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceOutReportExs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceOutReportExs *p = new CIot_DeviceOutReportExs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceOutReportExs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEOUTREPORTEX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceOutReportExs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceOutReportExKey)
	{
		pNew = new CIot_DeviceOutReportEx();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceOutReportExs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEOUTREPORTEX)
	{
		pNew = new CIot_DeviceOutReportEx();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceOutReportExs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceOutReportEx();

	return pNew;
}
