#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define VERUPDATEHISCLASSID_BASECLASS      (CLASSID_BASECLASS + 0X00010000)
#define VERUPDATEHISCLASSID_EXLISTCLASS    (CLASSID_EXLISTCLASS + 0X00010000)

#define VERUPDATEHISCLASSID_SYSMNGR       (VERUPDATEHISCLASSID_EXLISTCLASS + 0X00000001)
#define VERUPDATEHISCLASSID_SYSVERS         (VERUPDATEHISCLASSID_EXLISTCLASS + 0X00000002)
#define VERUPDATEHISCLASSID_VER	         (VERUPDATEHISCLASSID_EXLISTCLASS + 0X00000003)

#define DEFAULT_MAXENTRIES		5

// CVerUpdateHisXmlRWKeys ÃüÁîÄ¿±ê

class CVerUpdateHisXmlRWKeys : public CXmlRWKeys
{
public:
	CVerUpdateHisXmlRWKeys();
	virtual ~CVerUpdateHisXmlRWKeys();
	static long g_nVERUPDATEHISXMLRef;

public:
	static CVerUpdateHisXmlRWKeys* g_pXmlKeys;
	static CVerUpdateHisXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strSysMngrKey;		//sys-mngr
	BSTR m_strSysVersionsKey; 	//sys-vers
	BSTR m_strVersionKey; 		//ver
	BSTR m_strDateTimeKey;		//datetime
	BSTR m_strCurrVerKey;		//curr-ver
	BSTR m_strPrevVerKey;		//prev-ver
	BSTR m_strCurrVerIdxKey;	//curr-veridx
	BSTR m_strPrevVerIdxKey;	//prev-veridx
	BSTR m_strMaxEntriesKey;	//max_entries

public:
	static BSTR SysMngrKey()	{    return g_pXmlKeys->m_strSysMngrKey;  	}
	static BSTR SysVersionsKey()    	{    return g_pXmlKeys->m_strSysVersionsKey;  	}
	static BSTR VersionKey()          	{    return g_pXmlKeys->m_strVersionKey;   	}
	static BSTR DateTimeKey()       	{    return g_pXmlKeys->m_strDateTimeKey;	}
	static BSTR CurrVerKey()          	{    return g_pXmlKeys->m_strCurrVerKey;		}
	static BSTR PrevVerKey()         	{    return g_pXmlKeys->m_strPrevVerKey;		}
	static BSTR CurrVerIdxKey()     	{    return g_pXmlKeys->m_strCurrVerIdxKey;	}
	static BSTR PrevVerIdxKey()     	{    return g_pXmlKeys->m_strPrevVerIdxKey;	}
	static BSTR MaxEntriesKey()		{	 return g_pXmlKeys->m_strMaxEntriesKey;	}
};


