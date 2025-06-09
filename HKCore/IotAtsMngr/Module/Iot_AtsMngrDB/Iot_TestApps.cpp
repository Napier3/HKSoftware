//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestApps.cpp  CIot_TestApps


#include "stdafx.h"
#include "Iot_TestApps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestApps::CIot_TestApps()
{
	//初始化属性

	//初始化成员变量
}

CIot_TestApps::~CIot_TestApps()
{
}

long CIot_TestApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestApps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TestApps::InitAfterRead()
{
}

BOOL CIot_TestApps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestApps *p = (CIot_TestApps*)pObj;

	return TRUE;
}

BOOL CIot_TestApps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestApps *p = (CIot_TestApps*)pDest;

	return TRUE;
}

CBaseObject* CIot_TestApps::Clone()
{
	CIot_TestApps *p = new CIot_TestApps();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestApps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestApps *p = new CIot_TestApps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TestApps::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TESTAPP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TestApps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TestAppKey)
	{
		pNew = new CIot_TestApp();
	}

	return pNew;
}

CExBaseObject* CIot_TestApps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TESTAPP)
	{
		pNew = new CIot_TestApp();
	}

	return pNew;
}
CExBaseObject* CIot_TestApps::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_TestApp();

	return pNew;
}

BOOL CIot_TestApps::QueryTestAppsByIndexTask(CXDbBaseLib *pXDbLib,long nIndex_TestTask)
{
	CString strTestAppTable;
	CString strIndex_TestTaskKey,strIndex_TestAppKey,strSql;

	strTestAppTable = CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();
	strIndex_TestTaskKey = CIot_AtsMngrXmlRWKeys::Index_Test_TaskKey();
	strIndex_TestAppKey = CIot_AtsMngrXmlRWKeys::Index_TestappKey();

	strSql.Format(_T("select * from %s where %s in (select %s from iot_test_task_testapp where %s=%d)"),
		strTestAppTable, strIndex_TestAppKey,strIndex_TestAppKey, strIndex_TestTaskKey, nIndex_TestTask);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

BOOL CIot_TestApps::UpdateTestAppState(CXDbBaseLib *pXDbLib,long nTest_State)
{
	POS pos = GetHeadPosition();
	CIot_TestApp* pIotTestApp = NULL;

	while (pos != NULL)
	{
		pIotTestApp = (CIot_TestApp*)GetNext(pos);

		pIotTestApp->m_nTest_State = nTest_State;

		pIotTestApp->DB_Update(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return TRUE;
}
BOOL CIot_TestApps::QueryTestApps(CXDbBaseLib *pXDbLib)
{
	CString strTestAppTable, strSql;

	strTestAppTable = CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();

	strSql.Format(_T("select * from %s"), strTestAppTable);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

void CIot_TestApps::ResetIsUpdate(CXDbBaseLib *pXDbLib, BOOL bRetUseDays)
{
	POS pos = GetHeadPosition();
	CIot_TestApp *pTestApp = NULL;

	while (pos != NULL)
	{
		pTestApp = (CIot_TestApp *)GetNext(pos);

		pTestApp->m_nIsUpdate = 0;

		if (bRetUseDays)
		{
			pTestApp->m_nUseDays = 0;
		}

		pTestApp->DB_Update(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
}