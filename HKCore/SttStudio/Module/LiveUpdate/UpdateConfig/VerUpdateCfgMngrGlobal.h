#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define VERUPDATECFGCLASSID_BASECLASS      (CLASSID_BASECLASS + 0X00020000)
#define VERUPDATECFGCLASSID_EXLISTCLASS    (CLASSID_EXLISTCLASS + 0X00020000)

#define VERUPDATECFGCLASSID_MNGR	       (VERUPDATECFGCLASSID_EXLISTCLASS + 0X00000001)
#define VERUPDATECFGCLASSID_YUN	           (VERUPDATECFGCLASSID_EXLISTCLASS + 0X00000002)
#define VERUPDATECFGCLASSID_SYSES	       (VERUPDATECFGCLASSID_EXLISTCLASS + 0X00000003)
#define VERUPDATECFGCLASSID_SYS	           (VERUPDATECFGCLASSID_EXLISTCLASS + 0X00000004)
#define VERUPDATECFGCLASSID_LOCAL	       (VERUPDATECFGCLASSID_EXLISTCLASS + 0X00000005)

#define SYSTYPE_DESKTOP	_T("desktop")
#define SYSTYPE_EMBED	_T("embed")

// CVerUpdateCfgXmlRWKeys ÃüÁîÄ¿±ê

class CVerUpdateCfgXmlRWKeys : public CXmlRWKeys
{
public:
	CVerUpdateCfgXmlRWKeys();
	virtual ~CVerUpdateCfgXmlRWKeys();
	static long g_nVERUPDATECFGXMLRef;

public:
	static CVerUpdateCfgXmlRWKeys* g_pXmlKeys;
	static CVerUpdateCfgXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strVerUpdateCfgKey; 	//ver-update-cfg
	BSTR m_strYunKey; 			//yun
	BSTR m_strIPKey;			//ip
	BSTR m_strPortKey;			//port
	BSTR m_strFtpPortKey;		//ftpport
	BSTR m_strSysesKey;			//syses
	BSTR m_strSysKey;			//sys
	BSTR m_strIdxSysKey;		//idx
	BSTR m_strTypeKey;			//type
	BSTR m_strRunPathKey;		//run_path
	BSTR m_strVerPathKey;		//ver_path
	BSTR m_strBackupPathKey;	//bk_path
	BSTR m_strTimeOutKey;		//time_out
	BSTR m_strShellPathKey;		//shell_path
	BSTR m_strLocalKey;			//local

public:
	static BSTR VerUpdateCfgKey(){    return g_pXmlKeys->m_strVerUpdateCfgKey;  	}
	static BSTR YunKey()     	 {    return g_pXmlKeys->m_strYunKey;   	}
	static BSTR IPKey()   		 {    return g_pXmlKeys->m_strIPKey;		}
	static BSTR PortKey()	 	 {    return g_pXmlKeys->m_strPortKey; 		}
	static BSTR FtpPortKey()	 {	  return g_pXmlKeys->m_strFtpPortKey;	}
	static BSTR SysesKey()		 {    return g_pXmlKeys->m_strSysesKey;		}
	static BSTR SysKey()     	 {    return g_pXmlKeys->m_strSysKey;		}
	static BSTR IdxSysKey()		 {	  return g_pXmlKeys->m_strIdxSysKey;	}
	static BSTR TypeKey()		 {    return g_pXmlKeys->m_strTypeKey;		}
	static BSTR RunPathKey()	 {    return g_pXmlKeys->m_strRunPathKey;	}
	static BSTR VerPathKey()  	 {    return g_pXmlKeys->m_strVerPathKey;	}
	static BSTR BkPathKey()		 {	  return g_pXmlKeys->m_strBackupPathKey;}
	static BSTR TimeOutKey()	 {	  return g_pXmlKeys->m_strTimeOutKey;	}
	static BSTR ShellPathKey()	 {	  return g_pXmlKeys->m_strShellPathKey; }
	static BSTR LocalKey()		 {	  return g_pXmlKeys->m_strLocalKey;		}
};


