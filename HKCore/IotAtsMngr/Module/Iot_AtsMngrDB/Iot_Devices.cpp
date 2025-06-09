//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Devices.cpp  CIot_Devices


#include "stdafx.h"
#include "Iot_Devices.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Devices::CIot_Devices()
{
	//初始化属性

	//初始化成员变量
}

CIot_Devices::~CIot_Devices()
{
}

long CIot_Devices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Devices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Devices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Devices::InitAfterRead()
{
}

BOOL CIot_Devices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Devices *p = (CIot_Devices*)pObj;

	return TRUE;
}

BOOL CIot_Devices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Devices *p = (CIot_Devices*)pDest;

	return TRUE;
}

CBaseObject* CIot_Devices::Clone()
{
	CIot_Devices *p = new CIot_Devices();
	Copy(p);
	return p;
}

CBaseObject* CIot_Devices::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Devices *p = new CIot_Devices();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Devices::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Devices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceKey)
	{
		pNew = new CIot_Device();
	}

	return pNew;
}

CExBaseObject* CIot_Devices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		pNew = new CIot_Device();
	}

	return pNew;
}
CExBaseObject* CIot_Devices::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Device();

	return pNew;
}

BOOL CIot_Devices::QueryDevicesByIndexTask(CXDbBaseLib *pXDbLib,long nIndex_TestTask)
{
	CString strDeviceTable,strBenchDeviceTable;
	CString strIndex_TestTaskKey,strIndex_DeviceKey,strSql;

	strDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();
	strBenchDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();
	strIndex_TestTaskKey = CIot_AtsMngrXmlRWKeys::Index_Test_TaskKey();
	strIndex_DeviceKey = CIot_AtsMngrXmlRWKeys::Index_DeviceKey();

	//select * from iot_device where index_device in (select index_device from iot_test_task_device where index_test_task=117);
	strSql.Format(_T("select * from %s where %s in (select %s from %s where %s=%d)"),
		strDeviceTable, strIndex_DeviceKey,strIndex_DeviceKey, strBenchDeviceTable,strIndex_TestTaskKey, nIndex_TestTask);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

BOOL CIot_Devices::QueryDevicesByIndexDeviceClassify(CXDbBaseLib *pXDbLib, long nIndex_Device_Classify)
{
	CString strDeviceTable;
	CString strIndex_Device_Classify, strSql;

	strDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();
	strIndex_Device_Classify = CIot_AtsMngrXmlRWKeys::Index_Device_ClassifyKey();
	
	strSql.Format(_T("select * from %s where %s=%d"),
		strDeviceTable, strIndex_Device_Classify, nIndex_Device_Classify);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

BOOL CIot_Devices::UpdateDeviceState(CXDbBaseLib *pXDbLib,long nTest_State)
{
	POS pos = GetHeadPosition();
	CIot_Device* pIotDevice = NULL;
	while (pos != NULL)
	{
		pIotDevice = (CIot_Device*)GetNext(pos);
		pIotDevice->m_nTest_State = nTest_State;

		pIotDevice->DB_Update(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return TRUE;
}

void CIot_Devices::DeleteRTDeviceRpt(const CString &strRoot)
{
	POS pos = GetHeadPosition();
	CIot_Device* pIotDevice = NULL;
	CString strFolder;

	while (pos != NULL)
	{
		pIotDevice = (CIot_Device*)GetNext(pos);
		
		strFolder.Format(_T("%s%d\\"),strRoot,pIotDevice->m_nIndex_Device);

		DeleteAllDirectorys(strFolder);
	}
}