#include "stdafx.h"
#include "MacroTestEngineCreateMngr.h"
#include "XLanguageResourceAts.h"
#include "TCtrlCntrConfig.h"
#include "../../SttStudio/Module/SmartTestInterface/MacroTestInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//
CMacroTestEngineCreate::CMacroTestEngineCreate()
{
	m_pMacroTestEngine = NULL;
	m_hLogWnd = 0;
}

CMacroTestEngineCreate::~CMacroTestEngineCreate()
{

}

MacroTest::IMacroTestEngine CMacroTestEngineCreate::GetMacroTestEngine(const CString &strProgID)
{
	if (m_pMacroTestEngine != NULL)
	{
		return m_pMacroTestEngine;
	}

	//m_pMacroTestEngine.CreateDispatch(strProgID);
	m_pMacroTestEngine.CreateDispatch(strProgID);
	//m_pMacroTestEngine.CreateDispatch(_T("IotVm.TestEngine"));

	if (m_pMacroTestEngine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("MacroTestEngine [%s] Create failed...."), strProgID);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CreateCpntFail/*L"创建测试组件失败"*/);
	}
	else
	{
		m_pMacroTestEngine.ShowSpyWnd(g_bShowTestWndTop);

		try
		{
			m_pMacroTestEngine.AttatchLogWnd(m_hLogWnd);
		}
		catch (...)
		{
		}
	}

	return m_pMacroTestEngine;
}

 //lijq 2019-1-14
MacroTest::IMacroTest CMacroTestEngineCreate::GetMacroTest(const CString &strProgID, CDataGroup *pTestApps, BOOL &bFirstCreate)
{
	if (m_oMacroTest != NULL)
	{
		bFirstCreate = FALSE;
		return m_oMacroTest;
	}

	bFirstCreate = TRUE;

	if (m_pMacroTestEngine == NULL)
	{
		m_pMacroTestEngine.CreateDispatch(strProgID);
		//m_pMacroTestEngine.CreateDispatch(_T("IotVm.TestEngine"));

		try
		{
			m_pMacroTestEngine.ShowSpyWnd(g_bShowTestWndTop);
		}
		catch (...)
		{
		}

		try
		{
			m_pMacroTestEngine.AttatchLogWnd(m_hLogWnd);
		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s : has no interface [AttatchLogWnd]"), strProgID);
		}
	}

	if (m_pMacroTestEngine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("MacroTestEngine [%s] Create failed...."), strProgID);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CreateCpntFail/*L"创建测试组件失败"*/);
		return m_oMacroTest;
	}

	CString strConfig;

	if (pTestApps != NULL)
	{
		CDvmDataset oApps;
		TestApp_InitTestApps(&oApps, pTestApps);
		oApps.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strConfig);
	}

	try
	{
		m_oMacroTest = m_pMacroTestEngine.CreateMacroTest(strConfig); //lijq 2019-1-14
	}
	catch (...)
	{
	}

	return m_oMacroTest;
}

void CMacroTestEngineCreate::ReleaseMacroTestEngine()
{
	if (m_oMacroTest != NULL)
	{
		try
		{
			m_oMacroTest.CloseDevice();
			m_oMacroTest = NULL;
		}
		catch (...)
		{
		}
	}
	if (m_pMacroTestEngine != NULL)
	{
		try
		{
			m_pMacroTestEngine.ExitEngine();
		}
		catch (...)
		{

		}

		try
		{
			m_pMacroTestEngine = NULL;
		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_RlsPrtlEgnFail/*_T("释放规约引擎[%s]失败")*/, m_strID);
		}
	}

	m_oMacroTest = NULL;
	m_pMacroTestEngine = NULL;
}

void CMacroTestEngineCreate::ReleaseAllDevice()
{
	if (m_pMacroTestEngine != NULL)
	{
		try
		{
			
		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_RlsPrtlEgnFail/*_T("释放规约引擎[%s]失败")*/, m_strID);
		}
	}
}

void CMacroTestEngineCreate::ShowSpyWnd()
{
	if (m_pMacroTestEngine == NULL)
	{
		return;
	}

	if (CTCtrlCntrConfig::IsShowTestSpyWnd())
	{
		m_pMacroTestEngine.ShowSpyWnd(g_bShowTestWndTop);
	}
	else
	{
		m_pMacroTestEngine.ShowSpyWnd(0);
	}
}


void CMacroTestEngineCreate::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{
	if (m_pMacroTestEngine == NULL)
	{
		return;
	}

	m_pMacroTestEngine.ExcuteCmd(_bstr_t(strCmdID), _bstr_t(strCmdPara));
}

void CMacroTestEngineCreate::ConfigEngine(const CString &strIP)
{
	if (m_pMacroTestEngine == NULL)
	{
		return;
	}

	try
	{
		if (strIP.GetLength() > 7)
		{
			CString strXml;
			MacroTest::IMacroTest oMacroTest = m_pMacroTestEngine.CreateMacroTest(_T(""));
			mt_GetIP_ConfigString(strIP, strXml);
			oMacroTest.SetConfig(strXml);
		}
		
	}
	catch(...)
	{
	}

	try
	{
		m_pMacroTestEngine.ConfigEngine();
	}
	catch(...)
	{
	}
}

long CMacroTestEngineCreate::AttatchLogWnd(unsigned long hWnd)
{
	if (m_pMacroTestEngine == NULL)
	{
		return 0;
	}

	try
	{
		m_pMacroTestEngine.AttatchLogWnd(hWnd);
	}
	catch(...)
	{
	}

	return 0;
}

//shaolei  2023-8-24
//此处修改是因为GetMacroTest时，需要按照固定格式传测试仪信息。兼容之前g_pAtsNewTestTool的设计
//将传递过来的测试仪定义，每一个测试仪转成一个CDvmData。存放到pDestApps指针
//测试仪的定义每个参数，例如：DeviceSN、remote-ip等，作为一个CDvmValue存放。
//将pTestApps中的测试仪，转换格式后，存到pDestGrp
/*pTestApps：
<group name="" id="test-apps" data-type="test-apps" value="">
	<group name="" id="test-app" data-type="test-app" value="">
		<data name="" id="DeviceSN" data-type="" default-value="" value="PAL_E-SP.0014" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="" id="ProtocolID" data-type="" default-value="" value="IotVm.SPCSXT" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="" id="EngineProgID" data-type="" default-value="" value="IotVm.TestEngine" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="" id="dvm-file" data-type="" default-value="" value="SensorTestMacro.xml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="" id="dvm-file_s" data-type="" default-value="" value="/profile/upload/2021/12/22/0c6edb0942ad4d03953123404fe0ab8d.xml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="" id="remote-ip" data-type="" default-value="" value="192.168.1.1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="" id="remote-port" data-type="" default-value="" value="1024" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
</group>
*/

/*pDestApps：
<dataset>
	<data id="" name="" value="">      
		<value id="DeviceSN" name="" value="YRQ010101"/>
		<value id="EngineProgID" name="" value="IotVm.TestEngine"/>
		<value id="dvm-file" name="" value="SensorTestMacro.xml"/>
		<value id="dvm-file_s" name="" value="/profile/upload/2021/07/31/3de40090da2d47cc9737158ce5e66bde.xml"/>
		<value id="remote-ip" name="" value="192.168.134.112"/>
		<value id="remote-port" name="" value="2049"/>
		<value id="MacroFile" name="" value="D:\Program Files\EPOTO\e-Report\Config\SensorTest\SensorTestMacro.xml"/>
	</data>
</dataset>
*/
void CMacroTestEngineCreate::TestApp_InitTestApps(CDvmDataset *pDestApps, CDataGroup *pTestApps)
{
	POS pos = pTestApps->GetHeadPosition();
	CDataGroup *pTestApp = NULL;

	while (pos != NULL)
	{
		pTestApp = (CDataGroup*)pTestApps->GetNext(pos);
		CDvmData *pDataApp = pDestApps->AddNewData(pTestApp->m_strID, pTestApp->m_strID, pTestApp->m_strDataType, pTestApp->m_strValue);
		POS posChild = pTestApp->GetHeadPosition();

		while (posChild != NULL)
		{
			CDvmData *pData = (CDvmData *)pTestApp->GetNext(posChild);
			pDataApp->AddValue(pData->m_strName, pData->m_strID, pData->m_strValue);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
CMacroTestEngineCreateMngr::CMacroTestEngineCreateMngr()
{
	m_hLogWnd = 0;
}

CMacroTestEngineCreateMngr::~CMacroTestEngineCreateMngr()
{
	
}

MacroTest::IMacroTestEngine CMacroTestEngineCreateMngr::GetMacroTestEngine(const CString &strProgID)
{
	g_strActiveTestMacroProgID = strProgID;

	CMacroTestEngineCreate *pFind = (CMacroTestEngineCreate*)FindByID(strProgID);

	if (pFind == NULL)
	{
		pFind = new CMacroTestEngineCreate();
		pFind->m_hLogWnd = m_hLogWnd;
		pFind->m_strName = strProgID;
		pFind->m_strID = strProgID;
		AddNewChild(pFind);
	}

	return pFind->GetMacroTestEngine(strProgID);
}

MacroTest::IMacroTest CMacroTestEngineCreateMngr::GetMacroTest(const CString &strProgID, CDataGroup *pTestApps, BOOL &bFirstCreate)
{
	g_strActiveTestMacroProgID = strProgID;

	CMacroTestEngineCreate *pFind = (CMacroTestEngineCreate*)FindByID(strProgID);

	if (pFind == NULL)
	{
		pFind = new CMacroTestEngineCreate();
		pFind->m_hLogWnd = m_hLogWnd;
		pFind->m_strName = strProgID;
		pFind->m_strID = strProgID;
		AddNewChild(pFind);
	}

	return pFind->GetMacroTest(strProgID, pTestApps, bFirstCreate);
}

void CMacroTestEngineCreateMngr::ReleaseMacroTestEngine()
{
	POS pos = GetHeadPosition();
	CMacroTestEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CMacroTestEngineCreate *)GetNext(pos);
		p->ReleaseMacroTestEngine();
	}

	DeleteAll();
}

void CMacroTestEngineCreateMngr::ReleaseMacroTestEngine(const CString &strProgID)
{
	CMacroTestEngineCreate *pFind = (CMacroTestEngineCreate*)FindByID(strProgID);

	if (pFind != NULL)
	{
		pFind->ReleaseMacroTestEngine();
	}
}

void CMacroTestEngineCreateMngr::ShowSpyWnd()
{
	POS pos = GetHeadPosition();
	CMacroTestEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CMacroTestEngineCreate *)GetNext(pos);
		p->ShowSpyWnd();
	}
}

void CMacroTestEngineCreateMngr::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{
	POS pos = GetHeadPosition();
	CMacroTestEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CMacroTestEngineCreate *)GetNext(pos);
		p->ExecuteMtCmd(strCmdPara, strCmdPara);
	}
}


void CMacroTestEngineCreateMngr::ConfigEngine(const CString &strProgID, const CString &strIP)
{
	CMacroTestEngineCreate *pFind = (CMacroTestEngineCreate*)FindByID(strProgID);

	if (pFind == NULL)
	{
		GetMacroTestEngine(strProgID);
		pFind = (CMacroTestEngineCreate*)FindByID(strProgID);
	}

	if (pFind != NULL)
	{
		pFind->ConfigEngine(strIP);
	}
}

long CMacroTestEngineCreateMngr::AttatchLogWnd(unsigned long hWnd)
{
	POS pos = GetHeadPosition();
	CMacroTestEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CMacroTestEngineCreate *)GetNext(pos);
		p->AttatchLogWnd(hWnd);
	}

	m_hLogWnd = hWnd;

	return 0;
}
