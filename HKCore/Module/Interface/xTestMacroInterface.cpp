#include "stdafx.h"
#include "TestMacroInterface.h"
#include "..\API\GlobalConfigApi.h"

class _CTM_TestMacros_Creator
{
private:
	_CTM_TestMacros_Creator()
	{
		CString strPath;
		strPath.Format(L"%s%s", CString(_P_GetConfigPath()), g_strTestMacrosFile);
		TestMacroLib::ITestMacroAppPtr oApp;
		oApp.CreateInstance(__uuidof(TestMacroLib::TestMacroApp));
		ASSERT (oApp != NULL);
		m_oTestMacros = NULL;
		m_oTestMacros = oApp->GetTestMacros(_bstr_t(strPath), NULL);
		ASSERT (m_oTestMacros != NULL);
	}

	virtual ~_CTM_TestMacros_Creator()
	{
		m_oTestMacros = NULL;
	}

	static long g_nTestMacrosCreatorRef;
	TestMacroLib::ITestMacrosPtr m_oTestMacros;

public:
	static _CTM_TestMacros_Creator* g_pTestMacrosCreator;
	static const CString g_strTestMacrosFile;

	static _CTM_TestMacros_Creator* Create()
	{
		g_nTestMacrosCreatorRef++;

		if (g_nTestMacrosCreatorRef == 1)
		{
			g_pTestMacrosCreator = new _CTM_TestMacros_Creator();
		}

		return g_pTestMacrosCreator;
	}

	static void Release()
	{
		g_nTestMacrosCreatorRef--;

		if (g_nTestMacrosCreatorRef == 0)
		{
			delete g_pTestMacrosCreator;
			g_pTestMacrosCreator = NULL;
		}
	}

	static TestMacroLib::ITestMacrosPtr GetTestMacros()
	{
		ASSERT (g_pTestMacrosCreator != NULL);

		if (g_pTestMacrosCreator == NULL)
		{
			return NULL;
		}
		else
		{
			return g_pTestMacrosCreator->m_oTestMacros;
		}
	}
};

long _CTM_TestMacros_Creator::g_nTestMacrosCreatorRef = 0;
_CTM_TestMacros_Creator* _CTM_TestMacros_Creator::g_pTestMacrosCreator = NULL;
const CString _CTM_TestMacros_Creator::g_strTestMacrosFile = L"TestMacro.xml";

CString g_strFormatMacroNotExist = L"测试功能\"%s\"不存在";

void TM_GetTestMacroParasValues(const CString &strMacroID, SystemTool::IValuesPtr &oValues)
{
	ASSERT (_CTM_TestMacros_Creator::g_pTestMacrosCreator != NULL);

	TestMacroLib::ITestMacrosPtr oTestMacros = _CTM_TestMacros_Creator::g_pTestMacrosCreator->GetTestMacros();

	TestMacroLib::ITestMacroPtr oMacro = NULL;
	oMacro = oTestMacros->FindByID(_bstr_t(strMacroID));
	//ASSERT (oMacro != NULL);

	if (oMacro == NULL)
	{
//		CLogPrint::LogFormatLevel(LOGLEVEL_ERROR);
//		CLogPrint::LogFormatString(g_strFormatMacroNotExist, strMacroID);
	}
	else
	{
		TM_GetTestMacroParasValues(oMacro,oValues);
	}
}

void TM_GetTestMacroParasShortDatas(const CString &strMacroID, CShortDatas  &oDatas)
{
	ASSERT (_CTM_TestMacros_Creator::g_pTestMacrosCreator != NULL);

	TestMacroLib::ITestMacrosPtr oTestMacros = _CTM_TestMacros_Creator::g_pTestMacrosCreator->GetTestMacros();

	TestMacroLib::ITestMacroPtr oMacro = NULL;
	oMacro = oTestMacros->FindByID(_bstr_t(strMacroID));
	//ASSERT (oMacro != NULL);

	if (oMacro == NULL)
	{
		//		CLogPrint::LogFormatLevel(LOGLEVEL_ERROR);
		//		CLogPrint::LogFormatString(g_strFormatMacroNotExist, strMacroID);
	}
	else
	{
		TM_GetTestMacroParasShortDatas(oMacro,oDatas);
	}
}

void TM_GetTestMacroParasValues(TestMacroLib::ITestMacroPtr &oMacro, SystemTool::IValuesPtr &oValues)
{
	ASSERT (oMacro != NULL);
	ASSERT (oValues != NULL);

	if (oMacro == NULL || oValues == NULL)
	{
		return;
	}

	oValues->DeleteAll();//清空oValues；

	CShortDatas  oDatas = NULL;
	SystemTool::IValuesPtr oValsTemp = NULL;

	oDatas = oMacro->GetFaultParas();
	oValsTemp = oDatas->GetValues();
	oValues->Append(oValsTemp);

	oDatas = oMacro->GetSysParas();
	oValsTemp = oDatas->GetValues();
	oValues->Append(oValsTemp);
}

void TM_GetTestMacroParasShortDatas(TestMacroLib::ITestMacroPtr &oMacro, CShortDatas  &oDesDatas)
{
	ASSERT (oMacro != NULL);
	ASSERT (oDesDatas != NULL);

	if (oMacro == NULL || oDesDatas == NULL)
	{
		return;
	}

	oDesDatas->DeleteAll();//清空oValues；

	CShortDatas  oDatas = NULL;
	CShortDatas  oDatasTemp = NULL;
	SystemTool::IValuesPtr oValsTemp = NULL;

	oDatas = oMacro->GetFaultParas();
	oDatasTemp = oDatas->Clone();
	oDesDatas->Append(oDatasTemp);

	oDatas = oMacro->GetSysParas();
	oValsTemp = oDatas->Clone();
	oDesDatas->Append(oDatasTemp);
}

TestMacroLib::ITestMacrosPtr TM_CreateTestMacros()
{
	_CTM_TestMacros_Creator::Create();
	return _CTM_TestMacros_Creator::GetTestMacros();
}

void TM_ReleaseTestMacros()
{
	_CTM_TestMacros_Creator::Release();
}

//查找功能数据接口对象
TestMacroLib::ITestMacroPtr  TM_FindTestMacro(const CString &strMacroID)
{
	ASSERT (_CTM_TestMacros_Creator::g_pTestMacrosCreator != NULL);

	TestMacroLib::ITestMacrosPtr oTestMacros = _CTM_TestMacros_Creator::g_pTestMacrosCreator->GetTestMacros();

	TestMacroLib::ITestMacroPtr oMacro = NULL;
	oMacro = oTestMacros->FindByID(_bstr_t(strMacroID));
	//ASSERT (oMacro != NULL);

	if (oMacro == NULL)
	{

	}

	return oMacro;
}
