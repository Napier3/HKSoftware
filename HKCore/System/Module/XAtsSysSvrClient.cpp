
// XAtsSysSvrClient.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "XAtsSysSvrClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXAtsSysSvrClient* CXAtsSysSvrClient::g_pXAtsSysSvrClient = NULL;
long CXAtsSysSvrClient::g_nXAtsSysSvrClientRef = 0;


// XAtsSysSvrClientBase

CXAtsSysSvrClient::CXAtsSysSvrClient()
{
	
}


CXAtsSysSvrClient::~CXAtsSysSvrClient()
{
	
}


CXAtsSysSvrClient* CXAtsSysSvrClient::Create()
{
	g_nXAtsSysSvrClientRef++;

	if (g_nXAtsSysSvrClientRef == 1)
	{
		g_pXAtsSysSvrClient = new CXAtsSysSvrClient();
		g_pXAtsSysSvrClient->_CreateSysSvrApp();
	}

	return g_pXAtsSysSvrClient;
}

void CXAtsSysSvrClient::Release()
{
	g_nXAtsSysSvrClientRef--;

	if (g_nXAtsSysSvrClientRef == 0)
	{
		delete g_pXAtsSysSvrClient;
		g_pXAtsSysSvrClient = NULL;
	}
}

//程序启动时，向系统注册程序自身信息
BOOL CXAtsSysSvrClient::RegisterModule(const CString &strName, const CString &strID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_RegisterModule(strName, strID, nMsgWnd, nMsgThreadID, nMsgID);
	}

	return FALSE;
}

HWND CXAtsSysSvrClient::GetModuleMainWnd(const CString &strID)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_GetModuleMainWnd(strID);
	}

	return NULL;
}

BOOL CXAtsSysSvrClient::UnRegisterModule(const CString &strID)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_UnRegisterModule(strID);
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::UnRegisterModule()
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_UnRegisterModule();
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::CanOpenExeModule(const CString &strExeModule)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_CanOpenExeModule(strExeModule);
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::OpenExeModule(const CString &strExeModule, const CString &strPara)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenExeModule(strExeModule, strPara);
	}

	return FALSE;
}

void CXAtsSysSvrClient::GetSysMsg(LONG nMsgIndex, AtsSysSvr::CSysMsg &oSysMsg)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_GetSysMsg(nMsgIndex, oSysMsg);
	}
}

BOOL CXAtsSysSvrClient::OpenAutoTest_XTestDB(const CString &strGbrptFile, const CString &strDeviceAttr)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenAutoTest_XTestDB(strGbrptFile, strDeviceAttr);
	}
	else
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::OpenAutoTest_XTestDB()
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenAutoTest_XTestDB();
	}
	else
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CString &strDvmFile, const CString &strIecfgFile)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenAutoTest(strGbxmlFile, strGbrptFile, strPpTemplateFile, strDvmFile, strIecfgFile);
	}
	else
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CStringArray &astrDvmFile, const CString &strIecfgFile)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenAutoTest(strGbxmlFile, strGbrptFile, strPpTemplateFile, astrDvmFile, strIecfgFile);
	}
	else
	{
		return FALSE;
	}
}

//打开测试仪配置程序，传入的参数分别为培值文件、整站SCD数据文件
BOOL CXAtsSysSvrClient::OpenIec61850Config(const CString &strIecfgFile, const CString &strTscdFile, const CString &strOptr)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenIec61850Config(strIecfgFile, strTscdFile, strOptr);
	}
	else
	{
		return FALSE;
	}
}

//打开模型映射程序，传入的参数分别为映射文件、源文件、目标文件
BOOL CXAtsSysSvrClient::OpenDvmMap(const CString &strDvmMapFile, const CString &strDvmSrcFile, const CString &strDvmDestFile)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenDvmMap(strDvmMapFile, strDvmSrcFile, strDvmDestFile);
	}
	else
	{
		return FALSE;
	}
}

//打开模型测试程序，传入的参数分别为源文件、目标文件
BOOL CXAtsSysSvrClient::OpenDvmTest(const CString &strDvmSrcFile, const CString &strDvmDestFile)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenDvmTest(strDvmSrcFile, strDvmDestFile);
	}
	else
	{
		return FALSE;
	}
}

//打开SCL测试程序，传入的参数分别为源文件、目标文件
BOOL CXAtsSysSvrClient::OpenSclFileTest(const CString &strSclFile, const CString &strSclDestFile)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_OpenSclFileTest(strSclFile, strSclDestFile);
	}
	else
	{
		return FALSE;
	}
}


void CXAtsSysSvrClient:: DeleteSysMsg(LONG nMsgIndex)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_DeleteSysMsg(nMsgIndex);
	}
}

void CXAtsSysSvrClient::PostTestStateMsgTo(const CString &strDestModuleID, const CString &strState, const CString &strFile)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_PostTestStateMsgTo(strDestModuleID, strState, strFile);
	}
}


//向模块添加参数，例如测试模板编辑软件打开一个模板文件，则添加一个参数文件
void CXAtsSysSvrClient::AddModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_AddModulePara(strExeModule, strParaID, strParaValue);
	}
}
void CXAtsSysSvrClient::AddModulePara(const CString &strParaID, const CString &strParaValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_AddModulePara(g_pXAtsSysSvrClient->m_strModuleID, strParaID, strParaValue);
	}
}

//删除模块参数，例如测试模板编辑软件关闭一个模板文件，则删除一个参数文件
void CXAtsSysSvrClient::DeleteModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_DeleteModulePara(strExeModule, strParaID, strParaValue);
	}
}
void CXAtsSysSvrClient::DeleteModulePara(const CString &strParaID, const CString &strParaValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		g_pXAtsSysSvrClient->_DeleteModulePara(g_pXAtsSysSvrClient->m_strModuleID, strParaID, strParaValue);
	}
}

//模块参数是否存在，例如测试模板编辑软件打开一个模板文件之前，需要判断报告模板编辑软件是否已经打开此文件
BOOL CXAtsSysSvrClient::IsModuleParaExist(const CString &strExeModule, const CString &strParaID, const CString &strParaValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_IsModuleParaExist(strExeModule, strParaID, strParaValue);
	}
	else
	{
		return FALSE;
	}
}
BOOL CXAtsSysSvrClient::IsModuleParaExist(const CString &strParaID, const CString &strParaValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_IsModuleParaExist(g_pXAtsSysSvrClient->m_strModuleID, strParaID, strParaValue);
	}
	else
	{
		return FALSE;
	}
}


//标志
void CXAtsSysSvrClient::WriteFlag(const CString &strFlagID, const CString &strValue)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_WriteFlag(strFlagID, strValue);
	}
}

CString CXAtsSysSvrClient::GetFlag(const CString &strFlagID)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_GetFlag(strFlagID);
	}

	return _T("");
}

BOOL CXAtsSysSvrClient::GbGetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_GbGetItemPara(strExeModule, strGbXml, strItemPath, bOpenModule);
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::GbSetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, const CString &strItemXml, BOOL bOpenModule)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_GbSetItemPara(strExeModule, strGbXml, strItemPath, strItemXml, bOpenModule);
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::AtsTestItem(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_AtsTestItem(strExeModule, strGbXml, strItemPath, bOpenModule);
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::AtsViewItemReport(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule)
{
	ASSERT (g_pXAtsSysSvrClient != NULL);

	if (g_pXAtsSysSvrClient != NULL)
	{
		return g_pXAtsSysSvrClient->_AtsViewItemReport(strExeModule, strGbXml, strItemPath, bOpenModule);
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL CXAtsSysSvrClient::_RegisterModule(const CString &strName, const CString &strID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	m_strModuleID = strID;

	try
	{
		AtsSysSvr::CExeModule oExeModule = m_oSysSvrApp.RegisterModule(strName, strID, nMsgWnd, nMsgThreadID, nMsgID);
		return (oExeModule != NULL);
	}
	catch (...)
	{
		return FALSE;
	}
}

HWND CXAtsSysSvrClient::_GetModuleMainWnd(const CString &strID)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return NULL;
	}

	try
	{
		AtsSysSvr::CExeModule oExeModule = m_oSysSvrApp.GetModuleByID(strID);

		if (oExeModule == NULL)
		{
			return NULL;
		}

		HWND hWnd = (HWND)oExeModule.GetMsgRcvWnd();
		return hWnd;
	}
	catch (...)
	{
		return NULL;
	}

	return NULL;
}

BOOL CXAtsSysSvrClient::_UnRegisterModule(const CString &strID)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		return m_oSysSvrApp.UnRegisterModule(strID);
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::_UnRegisterModule()
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		return m_oSysSvrApp.UnRegisterModule(m_strModuleID);
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::_CanOpenExeModule(const CString &strExeModule)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	long nRet = 0;

	try
	{
		long nRet = m_oSysSvrApp.FindModule(strExeModule);
	}
	catch (...)
	{
	}

	return (nRet == 0);
}

BOOL CXAtsSysSvrClient::_OpenExeModule(const CString &strExeModule, const CString &strPara)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	long nRet = 0;

	try
	{
		nRet = m_oSysSvrApp.OpenModule(strExeModule, strPara);
	}
	catch (...)
	{
		return FALSE;
	}

	return (nRet > 0);
}


BOOL CXAtsSysSvrClient::_OpenExeModuleEx(const CString &strExeModule, LONG nSysMsgIndex)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	long nRet =0;

	try
	{
		nRet = m_oSysSvrApp.OpenModuleEx(strExeModule, nSysMsgIndex);
	}
	catch (...)
	{
		return FALSE;
	}

	return (nRet > 0);
}


void CXAtsSysSvrClient::_GetSysMsg(LONG nMsgIndex, AtsSysSvr::CSysMsg &oSysMsg)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return;
	}

	try
	{
		oSysMsg = m_oSysSvrApp.GetSysMsg(nMsgIndex);
	}
	catch (...)
	{
	}
}

void CXAtsSysSvrClient::_DeleteSysMsg(LONG nMsgIndex)
{
	_CreateSysSvrApp();

	if (m_oSysSvrApp == NULL)
	{
		return;
	}

	try
	{
		m_oSysSvrApp.DeleteSysMsg(nMsgIndex);
	}
	catch (...)
	{
	}
}

BOOL CXAtsSysSvrClient::_OpenAutoTest_XTestDB()
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_XTESTDB_TASKS, XPARA_ID_XTESTDB_TASKS);

		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_XTESTDB_TASKS, XPARA_ID_XTESTDB_TASKS, XPARA_ID_XTESTDB_TASKS);
		_OpenExeModuleEx(XMODULE_ID_AutoTest, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}


BOOL CXAtsSysSvrClient::_OpenAutoTest_XTestDB(const CString &strGbrptFile, const CString &strDeviceAttr)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_XTESTDB_TASKS, XPARA_ID_XTESTDB_TASKS);

		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, strGbrptFile);
		oSysMsg.AddSysData(XPARA_ID_DEVICE_ATTR, XPARA_ID_DEVICE_ATTR, strDeviceAttr);
		_OpenExeModuleEx(XMODULE_ID_AutoTest, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}


BOOL CXAtsSysSvrClient::_OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CString &strDvmFile, const CString &strIecfgFile)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		if (strGbxmlFile.GetLength() == 0)
		{
			oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE);
		}
		else
		{
			oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE);
		}

		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		if (strGbxmlFile.GetLength() == 0)
		{
			oSysMsg.AddSysData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, strGbrptFile);
		}
		else
		{
			oSysMsg.AddSysData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, strGbxmlFile);
			oSysMsg.AddSysData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, strGbrptFile);
			oSysMsg.AddSysData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE,     strDvmFile);
			oSysMsg.AddSysData(XPARA_ID_PPXMLFILE, XPARA_ID_PPXMLFILE, strPpTemplateFile);
		}

		oSysMsg.AddSysData(XPARA_ID_IecfgFile, XPARA_ID_IecfgFile, strIecfgFile);
		
		_OpenExeModuleEx(XMODULE_ID_AutoTest, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::_OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CStringArray &astrDvmFile, const CString &strIecfgFile)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		if (strGbxmlFile.GetLength() == 0)
		{
			oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE);
		}
		else
		{
			oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE);
		}

		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		if (strGbxmlFile.GetLength() == 0)
		{
			oSysMsg.AddSysData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, strGbrptFile);
		}
		else
		{
			oSysMsg.AddSysData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, strGbxmlFile);
			oSysMsg.AddSysData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, strGbrptFile);
			oSysMsg.AddSysData(XPARA_ID_PPXMLFILE, XPARA_ID_PPXMLFILE, strPpTemplateFile);

			long nCount = astrDvmFile.GetCount();
			CString strTemp;
			strTemp.Format(_T("%d"), nCount);
			long nIndex = 0;

			oSysMsg.AddSysData(XPARA_ID_DVMFILES, XPARA_ID_DVMFILES,     strTemp);

			for (nIndex=0; nIndex<nCount; nIndex++)
			{
				strTemp.Format(_T("%s%d"), XPARA_ID_DVMFILE, nIndex+1);
				oSysMsg.AddSysData(strTemp, strTemp,     astrDvmFile.GetAt(nIndex));
			}
		}

		oSysMsg.AddSysData(XPARA_ID_IecfgFile, XPARA_ID_IecfgFile, strIecfgFile);

		_OpenExeModuleEx(XMODULE_ID_AutoTest, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::_OpenIec61850Config(const CString &strIecfgFile, const CString &strTscdFile, const CString &strOptr)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_IecfgFile, XPARA_ID_IecfgFile);


		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_IecfgFile, XPARA_ID_IecfgFile, strIecfgFile);
		oSysMsg.AddSysData(XPARA_ID_TscdFile, XPARA_ID_TscdFile, strTscdFile);
		oSysMsg.AddSysData(XPARA_ID_TscdFile, XPARA_ID_Optr, strOptr);
		
		_OpenExeModuleEx(XMODULE_ID_Iec61850Config, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::_OpenDvmMap(const CString &strDvmMapFile, const CString &strDvmSrcFile, const CString &strDvmDestFile)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_DvmMapFile, strDvmMapFile);

		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_DvmMapFile, XPARA_ID_IecfgFile, strDvmMapFile);
		oSysMsg.AddSysData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, strDvmSrcFile);
		oSysMsg.AddSysData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, strDvmDestFile);

		_OpenExeModuleEx(XMODULE_ID_DvmMap, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

//打开模型测试程序，传入的参数分别为源文件、目标文件
BOOL CXAtsSysSvrClient::_OpenDvmTest(const CString &strDvmSrcFile, const CString &strDvmDestFile)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	AtsSysSvr::CSysMsg oSysMsg;

	try
	{
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XPARA_ID_DVMFILE, strDvmSrcFile);

		if (oSysMsg == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, strDvmSrcFile);
		oSysMsg.AddSysData(XPARA_ID_DVMFILE_DST, XPARA_ID_DVMFILE_DST, strDvmDestFile);

		_OpenExeModuleEx(XMODULE_ID_DvmTest, oSysMsg.GetMsgIndex());

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CXAtsSysSvrClient::_OpenSclFileTest(const CString &strSclFile, const CString &strSclDestFile)
{
	return TRUE;
}

void CXAtsSysSvrClient::_PostTestStateMsgTo(const CString &strDestModuleID, const CString &strState, const CString &strFile)
{
	if (m_oSysSvrApp == NULL)
	{
		return;
	}

	try
	{
		AtsSysSvr::CSysMsg oSysMsg;
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(strState, strFile);

		if (oSysMsg == NULL)
		{
			return;
		}

		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strDestModuleID);

		if (oModule == NULL)
		{
			return;
		}

		oModule.PostSysMsg(oSysMsg.GetMsgIndex());
	}
	catch (...)
	{
	}
}


//向模块添加参数，例如测试模板编辑软件打开一个模板文件，则添加一个参数文件
void CXAtsSysSvrClient::_AddModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue)
{
	if (m_oSysSvrApp == NULL)
	{
		return;
	}

	try
	{
		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			return;
		}

		oModule.AddPara(strParaID, strParaID, strParaValue);
	}
	catch (...)
	{
	}
}

//删除模块参数，例如测试模板编辑软件关闭一个模板文件，则删除一个参数文件
void CXAtsSysSvrClient::_DeleteModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue)
{
	if (m_oSysSvrApp == NULL)
	{
		return;
	}

	try
	{
		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			return ;
		}

		oModule.DeletePara(strParaID, strParaValue);
	}
	catch (...)
	{
	}
}

//模块参数是否存在，例如测试模板编辑软件打开一个模板文件之前，需要判断报告模板编辑软件是否已经打开此文件
BOOL CXAtsSysSvrClient::_IsModuleParaExist(const CString &strExeModule, const CString &strParaID, const CString &strParaValue)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		AtsSysSvr::CExeModule oModule;
		oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			return FALSE;
		}

		return oModule.IsParaExist(strParaID, strParaValue);
	}
	catch (...)
	{
	}

	return FALSE;
}

//标志
void CXAtsSysSvrClient::_WriteFlag(const CString &strFlagID, const CString &strValue)
{
	if (m_oSysSvrApp == NULL)
	{
		return;
	}

	try
	{
		m_oSysSvrApp.WriteFlag(strFlagID, strValue);
	}
	catch (...)
	{
	}
}

CString CXAtsSysSvrClient::_GetFlag(const CString &strFlagID)
{
	if (m_oSysSvrApp == NULL)
	{
		return _T("");
	}

	try
	{
		return m_oSysSvrApp.GetFlag(strFlagID);
	}
	catch (...)
	{
	}

	return _T("");
}

//获取测试项目参数  lijq 2020-02-03
BOOL CXAtsSysSvrClient::_GbGetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		AtsSysSvr::CSysMsg oSysMsg;
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XMODULE_OPTR_GET_ITEM_PARA, XMODULE_OPTR_GET_ITEM_PARA);

		if (oSysMsg == NULL)
		{
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, strGbXml);
		oSysMsg.AddSysData(XPARA_ID_Item_PATH, XPARA_ID_Item_PATH, strItemPath);

		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			if (bOpenModule)
			{
				m_oSysSvrApp.OpenModuleEx(strExeModule, oSysMsg.GetMsgIndex());
				return TRUE;
			}
		}
		else
		{
			oModule.PostSysMsg(oSysMsg.GetMsgIndex());
			return TRUE;
		}
	}
	catch (...)
	{
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::_GbSetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, const CString &strItemXml, BOOL bOpenModule)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		AtsSysSvr::CSysMsg oSysMsg;
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XMODULE_OPTR_SET_ITEM_PARA, XMODULE_OPTR_SET_ITEM_PARA);

		if (oSysMsg == NULL)
		{
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, strGbXml);
		oSysMsg.AddSysData(XPARA_ID_Item_PATH, XPARA_ID_Item_PATH, strItemPath);
		oSysMsg.AddSysData(XPARA_ID_Item_xml, XPARA_ID_Item_xml, strItemXml);

		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			if (bOpenModule)
			{
				m_oSysSvrApp.OpenModuleEx(strExeModule, oSysMsg.GetMsgIndex());
				return TRUE;
			}
		}
		else
		{
			oModule.PostSysMsg(oSysMsg.GetMsgIndex());
			return TRUE;
		}
	}
	catch (...)
	{
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::_AtsTestItem(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		AtsSysSvr::CSysMsg oSysMsg;
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XMODULE_OPTR_ATS_TEST_ITEM, XMODULE_OPTR_ATS_TEST_ITEM);

		if (oSysMsg == NULL)
		{
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, strGbXml);
		oSysMsg.AddSysData(XPARA_ID_Item_PATH, XPARA_ID_Item_PATH, strItemPath);

		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			if (bOpenModule)
			{
				m_oSysSvrApp.OpenModuleEx(strExeModule, oSysMsg.GetMsgIndex());
				return TRUE;
			}
		}
		else
		{
			oModule.PostSysMsg(oSysMsg.GetMsgIndex());
			return TRUE;
		}
	}
	catch (...)
	{
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::_AtsViewItemReport(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule)
{
	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	try
	{
		AtsSysSvr::CSysMsg oSysMsg;
		oSysMsg = m_oSysSvrApp.CreateNewSysMsg(XMODULE_OPTR_ATS_VIEW_ITEM_REPORT, XMODULE_OPTR_ATS_VIEW_ITEM_REPORT);

		if (oSysMsg == NULL)
		{
			return FALSE;
		}

		oSysMsg.AddSysData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, strGbXml);
		oSysMsg.AddSysData(XPARA_ID_Item_PATH, XPARA_ID_Item_PATH, strItemPath);

		AtsSysSvr::CExeModule oModule = m_oSysSvrApp.GetModuleByID(strExeModule);

		if (oModule == NULL)
		{
			if (bOpenModule)
			{
				m_oSysSvrApp.OpenModuleEx(strExeModule, oSysMsg.GetMsgIndex());
				return TRUE;
			}
		}
		else
		{
			oModule.PostSysMsg(oSysMsg.GetMsgIndex());
			return TRUE;
		}
	}
	catch (...)
	{
	}

	return FALSE;
}

BOOL CXAtsSysSvrClient::_CreateSysSvrApp()
{
	if (m_oSysSvrApp == NULL)
	{
		m_oSysSvrApp.CreateDispatch( _T("AtsSysSvr.SysSvrApp") );
	}

	if (m_oSysSvrApp == NULL)
	{
		return FALSE;
	}

	return TRUE;
}


CString atssys_GetSysName(const CString &strSysName)
{
	static UCHAR g_strAtsSysDefName[20];

	g_strAtsSysDefName[0]=0xD6;
	g_strAtsSysDefName[1]=0xC7;
	g_strAtsSysDefName[2]=0xC4;
	g_strAtsSysDefName[3]=0xDC;
	g_strAtsSysDefName[4]=0xD7;
	g_strAtsSysDefName[5]=0xD4;
	g_strAtsSysDefName[6]=0xB6;
	g_strAtsSysDefName[7]=0xAF;
	g_strAtsSysDefName[8]=0xB2;
	g_strAtsSysDefName[9]=0xE2;
	g_strAtsSysDefName[10]=0xCA;
	g_strAtsSysDefName[11]=0xD4;
	g_strAtsSysDefName[12]=0xCF;
	g_strAtsSysDefName[13]=0xB5;
	g_strAtsSysDefName[14]=0xCD;
	g_strAtsSysDefName[15]=0xB3;
	g_strAtsSysDefName[16]=0x00;
	g_strAtsSysDefName[17]=0x00;
	g_strAtsSysDefName[18]=0x00;

	CString strTemp = strSysName;

	if (strTemp.GetLength() < 5)
	{
		strTemp = (char*)g_strAtsSysDefName;
	}
	
	return strTemp;
}


CString atssys_GetSysName(const CString &strSysName, const CString &strExeName)
{
	CString strTemp = atssys_GetSysName(strSysName);

	strTemp.AppendFormat(_T(":%s"), strExeName);

	return strTemp;
}


BOOL atssys_CreateSingleAppMutex(const CString &pszMutexName, const CString &strModuleID)
{
	if (!CreateSingleAppMutex(pszMutexName))
	{
		HWND hWnd = CXAtsSysSvrClient::GetModuleMainWnd(strModuleID);

		if (hWnd != NULL)
		{
			if (::IsWindow(hWnd))
			{
				UI_BringWndToTop(hWnd);
			}
		}

		return FALSE;
	}
	else
	{
		return TRUE;
	}
}