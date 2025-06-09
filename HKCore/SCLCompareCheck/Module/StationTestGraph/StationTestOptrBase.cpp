
// StationTestOptrBase.cpp : CStationTestOptrBase 类的实现
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"

#include "StationTestOptrBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStationTestOptrBase 构造/析构

CStationTestOptrBase::CStationTestOptrBase()
{
	// TODO: 在此处添加构造代码

}

CStationTestOptrBase::~CStationTestOptrBase()
{

}

BOOL CStationTestOptrBase::IsIedNeedTest(CString &strIedId)
{
	if (m_pXScdDrawViewRef->m_pActiveElement == NULL)
	{
		return FALSE;
	}

	CStationTest *pStationTest = theApp.GetCurrStationTest();

	ASSERT( pStationTest != NULL );

	if (pStationTest == NULL)
	{
		return FALSE;
	}

	strIedId = m_pXScdDrawViewRef->m_pActiveElement->m_strID;

	return pStationTest->IsIedNeedTest(strIedId);
}

CStationIedTest* CStationTestOptrBase::GetCurrIedTest()
{
	CString strIedID;

	if (! IsIedNeedTest(strIedID))
	{
		return NULL;
	}

	CStationTest *pStationTest = theApp.GetCurrStationTest();
	CStationIedTest *pIedTest = pStationTest->SetCurrIedTest(strIedID);

	ASSERT(pIedTest != NULL);

	return pIedTest;
}

void CStationTestOptrBase::Optr_OnStationTest_Iec61850Config()
{
	CStationIedTest *pIedTest = GetCurrIedTest();

	if (pIedTest == NULL)
	{
		return;
	}

	pIedTest->Iec61850Config();
}

void CStationTestOptrBase::Optr_OnStationTest_DvmTest()
{
	CStationIedTest *pIedTest = GetCurrIedTest();

	if (pIedTest == NULL)
	{
		return;
	}

	pIedTest->DvmTest();

}

void CStationTestOptrBase::Optr_OnStationTest_VTermTest()
{
	CStationIedTest *pIedTest = GetCurrIedTest();

	if (pIedTest == NULL)
	{
		return;
	}

	pIedTest->VTerminalTest();
}

void CStationTestOptrBase::Optr_OnStationTest_ProtTest()
{
	CStationIedTest *pIedTest = GetCurrIedTest();

	if (pIedTest == NULL)
	{
		return;
	}

	pIedTest->ProtTest();
}

void CStationTestOptrBase::Optr_OnStationTest_LinkTest()
{
	CStationIedTest *pIedTest = GetCurrIedTest();

	if (pIedTest == NULL)
	{
		return;
	}

	pIedTest->LockTest();
}

void CStationTestOptrBase::Optr_OnStationTest_ExportRpt()
{
	
}

void CStationTestOptrBase::Optr_OnStationTest_UploadRpt()
{
	
}

