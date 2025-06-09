#include "stdafx.h"
#include"VmMacroTest.h"

#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#ifdef _USE_SMARTTEST_INTERFACE_COM_

CVmMacroTest::CVmMacroTest()
{

}


CVmMacroTest::~CVmMacroTest(void)
{
}

long CVmMacroTest::SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
{
	return m_oMacroTest.SetWndMsg(hMainWnd, nMsgID);
}

CString CVmMacroTest::GetConfig()
{
	return m_oMacroTest.GetConfig();
}

long CVmMacroTest::SetConfig(const CString & bstrConfig)
{
	return m_oMacroTest.SetConfig(bstrConfig);
}

long CVmMacroTest::Test(const CString & strMacroID, const CString & strParameter)
{
	return m_oMacroTest.Test(strMacroID, strParameter);
}

CString CVmMacroTest::GetReport()
{
	return m_oMacroTest.GetReport();
}

long CVmMacroTest::StopTest()
{
	return m_oMacroTest.StopTest();
}

long CVmMacroTest::CloseDevice()
{
	return m_oMacroTest.CloseDevice();
}

CString CVmMacroTest::GetSearchReport()
{
	return m_oMacroTest.GetSearchReport();
}

long CVmMacroTest::FinishTest(long nState)
{
	return m_oMacroTest.FinishTest(nState);
}

long CVmMacroTest::ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter)
{
	return m_oMacroTest.ExcuteCmd(strCmdID, strCmdParameter);
}

unsigned long CVmMacroTest::GetExternMsgRcvWnd()
{
	return m_oMacroTest.GetExternMsgRcvWnd();
}

unsigned long CVmMacroTest::GetExternMsgID()
{
	return m_oMacroTest.GetExternMsgID();
}

unsigned long CVmMacroTest::StopDevice(void)
{
	return m_oMacroTest.StopDevice();
}

//////////////////////////////////////////////////////////////////////////
//CVmMacroTestEngine
CVmMacroTestEngine::CVmMacroTestEngine()
{
	m_oMacroTestEngine = NULL;
}

CVmMacroTestEngine::~CVmMacroTestEngine(void)
{
	try
	{
		m_oMacroTestEngine = NULL;
	}
	catch (...)
	{
		
	}
}

CMacroTestInterface* CVmMacroTestEngine::CreateMacroTest(const CString &bstrConfig)
{
	return NULL;
}

long CVmMacroTestEngine::ExitEngine()
{
	return 0;
}

long CVmMacroTestEngine::ExcuteCmd(const CString &strCmdID, const CString &strCmdParameter)
{
	return 0;
}

long CVmMacroTestEngine::ShowSpyWnd(long nShow) 
{
	return 0;
}

long CVmMacroTestEngine::ConfigEngine()
{
	try
	{
		m_oMacroTestEngine.ConfigEngine();
	}
	catch (...)
	{

	}
	return 0;
}


long CVmMacroTestEngine::AttatchLogWnd(unsigned long hWnd)
{
	try
	{
		m_oMacroTestEngine.AttatchLogWnd(hWnd);
	}
	catch (...)
	{

	}
	return 0;
}



//////////////////////////////////////////////////////////////////////////
//
CVmMacroTestCreator::CVmMacroTestCreator()
{

}

CVmMacroTestCreator::~CVmMacroTestCreator()
{

}


CMacroTestEngineInterface* CVmMacroTestCreator::CreateMacroTestEngine(const CString &strMacroFile)
{
	m_oMacroTestEngineCreateMngr.m_hLogWnd = m_hLogWnd;

	//开启控制接口程序
	try
	{
		CString strActiveProgID;

		//2020-12-22  lijunqing
		//简化版本开发，增加配置选项，传入ProgID创建引擎，兼容测试功能文件、测试功能标识、ProgID三种模式
		long nPos = strMacroFile.Find('.');

		if (nPos > 0)
		{
			CString strTemp = strMacroFile.Mid(nPos+1);
			strTemp.MakeLower();

			if (strTemp == "xml")
			{
				strActiveProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, g_strDefaultMacroType);
			}
			else
			{
				strActiveProgID = strMacroFile;
			}
		}
		else
		{
			strActiveProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, g_strDefaultMacroType);
		}

		m_oMacroTestEngineCreateMngr.GetMacroTestEngine(strActiveProgID);
	}
	catch(...)
	{
	}

	return NULL;
}

CMacroTestEngineInterface* CVmMacroTestCreator::GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile)
{
	m_oMacroTestEngineCreateMngr.m_hLogWnd = m_hLogWnd;

	CString strActiveMacroTestEngineProgID;
	strActiveMacroTestEngineProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, strType);
	ASSERT (strActiveMacroTestEngineProgID == strProgID);

	CVmMacroTestEngine *pNew = NULL;

	pNew = (CVmMacroTestEngine *)SttFindByID(strActiveMacroTestEngineProgID);

	if (pNew == NULL)
	{
		pNew = new CVmMacroTestEngine();
		pNew->m_oMacroTestEngine = m_oMacroTestEngineCreateMngr.GetMacroTestEngine(strActiveMacroTestEngineProgID);
		AddNewChild(pNew);
	}

	return pNew;
}

CMacroTestInterface* CVmMacroTestCreator::GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	CString strActiveMacroTestEngineProgID;

	//for debug   
	//此处总是使用当前Active的ProgID，是不合理的。
	//当使用COM接口调用时，测试仪由CreateTest指令指定，需要先修改当前Active的ProgID
	strActiveMacroTestEngineProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, strType);
	//ASSERT (strActiveMacroTestEngineProgID == strProgID);

	CString strID;
	strID = strActiveMacroTestEngineProgID;// + strTestAppGroup;
	CVmMacroTest *pMacroTest = (CVmMacroTest*)SttFindByID(strID);

	if (pMacroTest == NULL)
	{
		pMacroTest = new CVmMacroTest();
		BOOL bFirstCreate = FALSE;
		pMacroTest->m_oMacroTest = m_oMacroTestEngineCreateMngr.GetMacroTest(strActiveMacroTestEngineProgID, pTestApps, bFirstCreate);
		AddNewChild(pMacroTest);
		pMacroTest->m_strID = strID;   //shaolei 20200928
	}

	return pMacroTest;
}

void CVmMacroTestCreator::ReleaseMacroTestEngine()
{
	DeleteAll();
	m_oMacroTestEngineCreateMngr.ReleaseMacroTestEngine();
}


void CVmMacroTestCreator::InitMacroTestEngineShowSpyWnd()
{
	try
	{
		m_oMacroTestEngineCreateMngr.ShowSpyWnd();
	}
	catch (...)
	{

	}
}

void CVmMacroTestCreator::ReleaseMacroTestEngine(const CString &strProgID)
{

}

void CVmMacroTestCreator::ShowSpyWnd()
{

}

void CVmMacroTestCreator::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{

}

long CVmMacroTestCreator::ConfigEngine(const CString &strProgID, const CString &strIP)
{
	m_oMacroTestEngineCreateMngr.ConfigEngine(strProgID, strIP);
	return 0;
}

long CVmMacroTestCreator::AttatchLogWnd(unsigned long hWnd)
{
	m_oMacroTestEngineCreateMngr.AttatchLogWnd(hWnd);
	return 0;
}

#endif
