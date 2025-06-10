//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RemoteCtrlMngrGlobal.cpp

#include "stdafx.h"
#include "RemoteCtrlMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CRemoteCtrlMngrXmlRWKeys

CRemoteCtrlMngrXmlRWKeys* CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys = NULL;
long CRemoteCtrlMngrXmlRWKeys::g_nMngrRef = 0;


CRemoteCtrlMngrXmlRWKeys::CRemoteCtrlMngrXmlRWKeys()
{
	m_strCStt_RemoteUserRTKey = L"Stt_RemoteUserRT";
	m_strCStt_RemoteRegRTKey = L"Stt_RemoteRegRT";
	m_strCStt_RemoteRegRTsKey = L"Stt_RemoteRegRTs";
	m_strCStt_RemoteUserHisKey = L"Stt_RemoteUserHis";
	m_strCStt_RemoteRegHisKey = L"Stt_RemoteRegHis";
	m_strCStt_RemoteRegHissKey = L"Stt_RemoteRegHiss";
	m_strIndex_RegisterKey = L"Index_Register";
	m_strSN_TestAppKey = L"SN_TestApp";
	m_strModel_TestAppKey = L"Model_TestApp";
	m_strModel_DvKey = L"Model_Dv";
	m_strName_CopKey = L"Name_Cop";
	m_strName_UserKey = L"Name_User";
	m_strCode_RegisterKey = L"Code_Register";
	m_strTm_RegisterKey = L"Tm_Register";
	m_strTm_UnRegisterKey = L"Tm_UnRegister";
	m_strMode_RegisterKey = L"Mode_Register";
	m_strDescriptionKey = L"Description";
	m_strPath_HisFilesKey = L"Path_HisFiles";
	m_strIPKey = L"IP";
	m_strSocket_RefKey = L"Socket_Ref";

	m_strVer_PpMmsEngineKey = L"Ver_PpMmsEngine";
	m_strVer_PpEngineKey = L"Ver_PpEngine";
	m_strVer_SttTestStudioKey = L"Ver_SttTestStudio";
	m_strVer_SttTestCntrKey = L"Ver_SttTestCntr";
	m_strVer_Iec61850ConfigKey = L"Ver_Iec61850Config";
	m_strVer_DvmTestKey = L"Ver_DvmTest";
	m_strVer_SmartTestKey = L"Ver_SmartTest";
	m_strVer_TestServerKey = L"Ver_TestServer";

	m_strIndex_UserKey = L"Index_User";
	m_strID_TestKey = L"ID_Test";
	m_strID_TerminalKey = L"ID_Terminal";
	m_strID_AuthorityKey = L"ID_Authority";
}

CRemoteCtrlMngrXmlRWKeys::~CRemoteCtrlMngrXmlRWKeys()
{
}

CRemoteCtrlMngrXmlRWKeys* CRemoteCtrlMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CRemoteCtrlMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CRemoteCtrlMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CRemoteCtrlMngrConstGlobal

long CRemoteCtrlMngrConstGlobal::g_nGlobalRef = 0;
CRemoteCtrlMngrConstGlobal* CRemoteCtrlMngrConstGlobal::g_pGlobal = NULL;


CRemoteCtrlMngrConstGlobal::CRemoteCtrlMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CRemoteCtrlMngrConstGlobal::~CRemoteCtrlMngrConstGlobal()
{
}

CRemoteCtrlMngrConstGlobal* CRemoteCtrlMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CRemoteCtrlMngrConstGlobal();
	}

	return g_pGlobal;
}

void CRemoteCtrlMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
