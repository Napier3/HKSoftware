//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdDefineGlobal.h

#pragma once

#include "../../../Module/DataMngr/DataMngrGlobal.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSTTCMTRDPLAYCFG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSTTMAPGROUP       (MngrCLASSID_EXLISTCLASS + 0X00000001)


class CSttCmtrdCfgDefineXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CSttCmtrdCfgDefineXmlRWKeys();
	virtual ~CSttCmtrdCfgDefineXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSttCmtrdCfgDefineXmlRWKeys* g_pXmlKeys;
	static CSttCmtrdCfgDefineXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttCmtrdReplayCfgKey; //cmtrd-replay-cfg
	BSTR m_strCSttMapGroupKey; //map-group

public:
	static BSTR CSttCmtrdReplayCfgKey()  {   return g_pXmlKeys->m_strCSttCmtrdReplayCfgKey;  }
	static BSTR CSttMapGroupKey()  {   return g_pXmlKeys->m_strCSttMapGroupKey;  }
};
