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
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceItemRslts::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

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
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


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

BOOL CIot_DeviceItemRslts::QueryDeviceItemRslts(CXDbBaseLib *pXDbLib,long nIndex_Device,long nIndex_TestTask)
{
	CString strDeviceItemRsltTable;
	CString strIndex_TestTaskKey,strIndex_DeviceKey,strSql;

	strDeviceItemRsltTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceItemRsltKey();
	strIndex_TestTaskKey = CIot_AtsMngrXmlRWKeys::Index_Test_TaskKey();
	strIndex_DeviceKey = CIot_AtsMngrXmlRWKeys::Index_DeviceKey();

	strSql.Format(_T("select * from %s where %s=%d and %s=%d"),
		strDeviceItemRsltTable, strIndex_DeviceKey,nIndex_Device, strIndex_TestTaskKey, nIndex_TestTask);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

long CIot_DeviceItemRslts::GetDeviceReportResult(CXDbBaseLib *pXDbLib,long nIndex_Device,long nIndex_TestTask)
{
	QueryDeviceItemRslts(pXDbLib,nIndex_Device,nIndex_TestTask);

	POS pos = GetHeadPosition();
	CIot_DeviceItemRslt *p = NULL;

	while (pos != NULL)
	{
		p = (CIot_DeviceItemRslt *)GetNext(pos);

		if (p->m_nRsltjdg == 0)
		{
			return 0;
		}
	}

	return 1;
}