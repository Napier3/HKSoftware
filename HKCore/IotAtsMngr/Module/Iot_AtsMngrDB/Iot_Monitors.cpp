//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Monitors.cpp  CIot_Monitors


#include "stdafx.h"
#include "Iot_Monitors.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Monitors::CIot_Monitors()
{
	//初始化属性

	//初始化成员变量
}

CIot_Monitors::~CIot_Monitors()
{
}

long CIot_Monitors::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Monitors::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Monitors::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Monitors::InitAfterRead()
{
}

BOOL CIot_Monitors::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Monitors *p = (CIot_Monitors*)pObj;

	return TRUE;
}

BOOL CIot_Monitors::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Monitors *p = (CIot_Monitors*)pDest;

	return TRUE;
}

CBaseObject* CIot_Monitors::Clone()
{
	CIot_Monitors *p = new CIot_Monitors();
	Copy(p);
	return p;
}

CBaseObject* CIot_Monitors::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Monitors *p = new CIot_Monitors();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Monitors::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_MONITOR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Monitors::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_MonitorKey)
	{
		pNew = new CIot_Monitor();
	}

	return pNew;
}

CExBaseObject* CIot_Monitors::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_MONITOR)
	{
		pNew = new CIot_Monitor();
	}

	return pNew;
}
CExBaseObject* CIot_Monitors::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Monitor();

	return pNew;
}

BOOL CIot_Monitors::QueryMonitorssByIndexDevice(CXDbBaseLib *pXDbLib,long nIndex_Device)
{
	CString strMonitorTable;
	CString strIndex_Device, strSql;

	strMonitorTable = CIot_AtsMngrXmlRWKeys::CIot_MonitorKey();
	strIndex_Device = CIot_AtsMngrXmlRWKeys::Index_DeviceKey();

	strSql.Format(_T("select * from %s where %s=%d"),
		strMonitorTable, strIndex_Device, nIndex_Device);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}