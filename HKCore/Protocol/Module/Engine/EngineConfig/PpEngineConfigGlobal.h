//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpEngineConfigGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define MSCFGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MSCFGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MSCFGCLASSID_CPPENGINECONFIG       (MSCFGCLASSID_EXLISTCLASS + 0X00000000)
#define MSCFGCLASSID_CPPENGINEDSCFG       (MSCFGCLASSID_BASECLASS + 0X00000001)

class CPpEngineConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CPpEngineConfigXmlRWKeys();
	virtual ~CPpEngineConfigXmlRWKeys();
	static long g_nPpEngineCfgRef;

public:
	static CPpEngineConfigXmlRWKeys* g_pPpEngineCfgXmlKeys;
	static CPpEngineConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCPpEngineConfigKey; //Pp-engine-config
	BSTR m_strDebugModeKey;
	BSTR m_strLogDataBindKey;
	BSTR m_strPkgDataInforKey;
	BSTR m_strLogPkgKey;
	BSTR m_strLogDebugInforKey;
	BSTR m_strNoChangeWhenSameKey;
	BSTR m_strOnlyWriteLogFileKey;

public:
	static BSTR CPpEngineConfigKey()  {   return g_pPpEngineCfgXmlKeys->m_strCPpEngineConfigKey;  }
};

