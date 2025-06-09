#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define STTNATIVECFGCLASSID_BASECLASS      (CLASSID_BASECLASS + 0X00030000)
#define STTNATIVECFGCLASSID_EXLISTCLASS    (CLASSID_EXLISTCLASS + 0X00030000)

#define STTNATIVECFGCLASSID_MNGR	       (STTNATIVECFGCLASSID_EXLISTCLASS + 0X00000001)
#define STTNATIVECFGCLASSID_YUN	           (STTNATIVECFGCLASSID_EXLISTCLASS + 0X00000002)
#define STTNATIVECFGCLASSID_LIVEUPDATE	   (STTNATIVECFGCLASSID_EXLISTCLASS + 0X00000003)
#define STTNATIVECFGCLASSID_HISVER		   (STTNATIVECFGCLASSID_EXLISTCLASS + 0X00000004)
#define STTNATIVECFGCLASSID_MNT		(STTNATIVECFGCLASSID_EXLISTCLASS + 0X00000005)
#include "../UpdateHistory/VerUpdateHisMngrGlobal.h"

// CSttNativeCfgXmlRWKeys����Ŀ��

class CSttNativeCfgXmlRWKeys : public CVerUpdateHisXmlRWKeys
{
public:
	CSttNativeCfgXmlRWKeys();
	virtual ~CSttNativeCfgXmlRWKeys();
	static long g_nSTTNATIVECFGXMLRef;

public:
	static CSttNativeCfgXmlRWKeys* g_pXmlKeys;
	static CSttNativeCfgXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strSttNativeCfgKey; 	//SttNativeCfg
	BSTR m_strLiveUpdateKey;	//liveupdate
	BSTR m_strHisVerKey;	//hisver
	BSTR m_strYunKey;		//yun
	BSTR m_strMntKey;		//mnt
	BSTR m_strIPKey;		//ip����CVerUpdateCfgXmlRWKeysͬ����
	BSTR m_strPortKey;		//port����CVerUpdateCfgXmlRWKeysͬ����
	BSTR m_strFtpPortKey;	//ftpport����CVerUpdateCfgXmlRWKeysͬ����
	BSTR m_strID_SystemKey;	//ID_System����CPowerSky_OAXmlRWKeysͬ����
	BSTR m_strIndex_SystemKey;	//Index_System����CPowerSky_OAXmlRWKeysͬ����
	BSTR m_strRootFilesKey;	//rootfiles
	BSTR m_strUpdateDeviceXml;//UpdateDeviceXml
public:
	static BSTR SttNativeCfgKey(){    return g_pXmlKeys->m_strSttNativeCfgKey;  }
	static BSTR LiveUpdateKey()	 {    return g_pXmlKeys->m_strLiveUpdateKey;	}
	static BSTR HisVerKey()		 {	  return g_pXmlKeys->m_strHisVerKey;		}
	static BSTR YunKey()     	 {    return g_pXmlKeys->m_strYunKey;   		}
	static BSTR MntKey()		 {    return g_pXmlKeys->m_strMntKey;			}
	static BSTR IPKey()   		 {    return g_pXmlKeys->m_strIPKey;			}
	static BSTR PortKey()	 	 {    return g_pXmlKeys->m_strPortKey; 			}
	static BSTR FtpPortKey()	 {    return g_pXmlKeys->m_strFtpPortKey; 		}
	static BSTR ID_SystemKey()	 {	  return g_pXmlKeys->m_strID_SystemKey;		}
	static BSTR Index_SystemKey(){	  return g_pXmlKeys->m_strIndex_SystemKey;	}
	static BSTR RootFilesKey()	 {    return g_pXmlKeys->m_strRootFilesKey;		}
	static BSTR UpdateDeviceXmlKey(){	return g_pXmlKeys->m_strUpdateDeviceXml;	}
};


