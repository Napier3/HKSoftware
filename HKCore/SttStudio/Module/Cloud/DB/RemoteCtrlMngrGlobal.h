//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RemoteCtrlMngrGlobal.h

#pragma once

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSTT_REMOTEREGHISS       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSTT_REMOTEREGHIS       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CSTT_REMOTEUSERHIS       (MngrCLASSID_BASECLASS + 0X00000002)
#define MNGRCLASSID_CSTT_REMOTEREGRTS       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CSTT_REMOTEREGRT       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CSTT_REMOTEUSERRT       (MngrCLASSID_EXLISTCLASS + 0X00000005)

class CRemoteCtrlMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CRemoteCtrlMngrXmlRWKeys();
	virtual ~CRemoteCtrlMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CRemoteCtrlMngrXmlRWKeys* g_pXmlKeys;
	static CRemoteCtrlMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCStt_RemoteUserRTKey; //Stt_RemoteUserRT
	BSTR m_strCStt_RemoteRegRTKey; //Stt_RemoteRegRT
	BSTR m_strCStt_RemoteRegRTsKey; //Stt_RemoteRegRTs
	BSTR m_strCStt_RemoteUserHisKey; //Stt_RemoteUserHis
	BSTR m_strCStt_RemoteRegHisKey; //Stt_RemoteRegHis
	BSTR m_strCStt_RemoteRegHissKey; //Stt_RemoteRegHiss
	BSTR m_strIndex_RegisterKey; //Index_Register
	BSTR m_strSN_TestAppKey; //SN_TestApp
	BSTR m_strModel_TestAppKey; //Model_TestApp
	BSTR m_strModel_DvKey; //Model_Dv
	BSTR m_strName_CopKey; //Name_Cop
	BSTR m_strName_UserKey; //Name_User
	BSTR m_strCode_RegisterKey; //Code_Register
	BSTR m_strTm_RegisterKey; //Tm_Register
	BSTR m_strTm_UnRegisterKey; //Tm_UnRegister
	BSTR m_strMode_RegisterKey; //Mode_Register
	BSTR m_strDescriptionKey; //Description
	BSTR m_strPath_HisFilesKey; //Path_HisFiles
	BSTR m_strIPKey; //IP
	BSTR m_strSocket_RefKey; //Socket_Ref
	BSTR  m_strVer_PpMmsEngineKey; //Ver_PpMmsEngine
	BSTR  m_strVer_PpEngineKey; //Ver_PpEngine
	BSTR  m_strVer_SttTestStudioKey; //Ver_SttTestStudio
	BSTR  m_strVer_SttTestCntrKey; //Ver_SttTestCntr
	BSTR  m_strVer_Iec61850ConfigKey; //Ver_Iec61850Config
	BSTR  m_strVer_DvmTestKey; //Ver_DvmTest
	BSTR  m_strVer_SmartTestKey; //Ver_SmartTest
	BSTR  m_strVer_TestServerKey; //Ver_TestServer
	BSTR m_strIndex_UserKey; //Index_User
	BSTR m_strID_TestKey; //ID_Test
	BSTR m_strID_TerminalKey; //ID_Terminal
	BSTR m_strID_AuthorityKey; //ID_Authority

public:
	static BSTR CStt_RemoteUserRTKey()  {   return g_pXmlKeys->m_strCStt_RemoteUserRTKey;  }
	static BSTR CStt_RemoteRegRTKey()  {   return g_pXmlKeys->m_strCStt_RemoteRegRTKey;  }
	static BSTR CStt_RemoteRegRTsKey()  {   return g_pXmlKeys->m_strCStt_RemoteRegRTsKey;  }
	static BSTR CStt_RemoteUserHisKey()  {   return g_pXmlKeys->m_strCStt_RemoteUserHisKey;  }
	static BSTR CStt_RemoteRegHisKey()  {   return g_pXmlKeys->m_strCStt_RemoteRegHisKey;  }
	static BSTR CStt_RemoteRegHissKey()  {   return g_pXmlKeys->m_strCStt_RemoteRegHissKey;  }
	static BSTR Index_RegisterKey()  {   return g_pXmlKeys->m_strIndex_RegisterKey;  }
	static BSTR SN_TestAppKey()  {   return g_pXmlKeys->m_strSN_TestAppKey;  }
	static BSTR Model_TestAppKey()  {   return g_pXmlKeys->m_strModel_TestAppKey;  }
	static BSTR Model_DvKey()  {   return g_pXmlKeys->m_strModel_DvKey;  }
	static BSTR Name_CopKey()  {   return g_pXmlKeys->m_strName_CopKey;  }
	static BSTR Name_UserKey()  {   return g_pXmlKeys->m_strName_UserKey;  }
	static BSTR Code_RegisterKey()  {   return g_pXmlKeys->m_strCode_RegisterKey;  }
	static BSTR Tm_RegisterKey()  {   return g_pXmlKeys->m_strTm_RegisterKey;  }
	static BSTR Tm_UnRegisterKey()  {   return g_pXmlKeys->m_strTm_UnRegisterKey;  }
	static BSTR Mode_RegisterKey()  {   return g_pXmlKeys->m_strMode_RegisterKey;  }
	static BSTR DescriptionKey()  {   return g_pXmlKeys->m_strDescriptionKey;  }
	static BSTR Path_HisFilesKey()  {   return g_pXmlKeys->m_strPath_HisFilesKey;  }
	static BSTR IPKey()  {   return g_pXmlKeys->m_strIPKey;  }
	static BSTR Socket_RefKey()  {   return g_pXmlKeys->m_strSocket_RefKey;  }

	static BSTR Ver_PpMmsEngineKey()  {   return g_pXmlKeys->m_strVer_PpMmsEngineKey;  }
	static BSTR Ver_PpEngineKey()  {   return g_pXmlKeys->m_strVer_PpEngineKey;  }
	static BSTR Ver_SttTestStudioKey()  {   return g_pXmlKeys->m_strVer_SttTestStudioKey;  }
	static BSTR Ver_SttTestCntrKey()  {   return g_pXmlKeys->m_strVer_SttTestCntrKey;  }
	static BSTR Ver_Iec61850ConfigKey()  {   return g_pXmlKeys->m_strVer_Iec61850ConfigKey;  }
	static BSTR Ver_DvmTestKey()  {   return g_pXmlKeys->m_strVer_DvmTestKey;  }
	static BSTR Ver_SmartTestKey()  {   return g_pXmlKeys->m_strVer_SmartTestKey;  }
	static BSTR Ver_TestServerKey()  {   return g_pXmlKeys->m_strVer_TestServerKey;  }

	static BSTR Index_UserKey()  {   return g_pXmlKeys->m_strIndex_UserKey;  }
	static BSTR ID_TestKey()  {   return g_pXmlKeys->m_strID_TestKey;  }
	static BSTR ID_TerminalKey()  {   return g_pXmlKeys->m_strID_TerminalKey;  }
	static BSTR ID_AuthorityKey()  {   return g_pXmlKeys->m_strID_AuthorityKey;  }
};



class CRemoteCtrlMngrConstGlobal
{
private:
	CRemoteCtrlMngrConstGlobal();
	virtual ~CRemoteCtrlMngrConstGlobal();

public:
	static CRemoteCtrlMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CRemoteCtrlMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
