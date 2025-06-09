#include "StdAfx.h"
#include "ProtocolXmlRWKeys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CProtocolXmlRWKeys* CProtocolXmlRWKeys::g_pXmlRWKeys = NULL;
long CProtocolXmlRWKeys::g_nProtocolXmlRWKeysRef = 0;

CProtocolXmlRWKeys* CProtocolXmlRWKeys::Create()
{
	if (g_pXmlRWKeys == NULL)
	{
		g_pXmlRWKeys = new CProtocolXmlRWKeys();
	}

	g_nProtocolXmlRWKeysRef++;

	return g_pXmlRWKeys;
}

void CProtocolXmlRWKeys::Release()
{
	g_nProtocolXmlRWKeysRef--;

	if (g_nProtocolXmlRWKeysRef == 0)
	{
		delete g_pXmlRWKeys;
		g_pXmlRWKeys = NULL;
	}
}

CProtocolXmlRWKeys::CProtocolXmlRWKeys(void)
{
	m_strTypeKey = L"type";

	m_strTemplateKey = L"pp-template";
	m_strPackageMaxLengthKey = L"pkg-max-len";
	m_strPackageMinLengthKey = L"pkg-min-len";
	m_strDeviceModelKey = L"device-mode";
	m_strPackageEncodedKey = L"pkg-encoded";
	m_strPkgEncodedLenKey = L"pkg-encoded-len";
	m_strDefaultChannelKey = L"default-channel";
	m_strVersionKey = L"version";
	m_strDeviceFileForDebugKey = L"device-file-debug";
	m_strCommModeKey = L"comm-mode";
	m_strDeviceModeTypeKey = L"dvm-mode";
	m_strDatasetModeKey = L"ds-mode";
	m_strEngineVersionKey = L"engine-version";
	m_strOnRecvProcedureKey = L"on-recv-procedure";
	m_strSndOptr_GlobalVarKey = L"snd-scpt-gvar";
	m_strSndOptr_OptrKey = L"snd-scpt-optr";
	m_nSndOptr_ValueKey = L"snd-scpt-val";
	m_strScriptTypeKey = L"scpt-type";
	m_strPkgFullRcvJdgIDKey = L"protocol-base-type";
	m_strEncodingKey = L"encoding";
	m_strProtoPkgProcessKey = L"proto-pkg-process";

	m_strCommChannelKey = L"comm-channel";
	m_strChCmmModeKey = L"comm-mode";

	//Packages
	m_strPackageTextKey      = L"pkg-text";
	m_strPackageTextsKey      = L"pkg-texts";
	m_strPackagesKey      = L"packages";
	m_strTPackageKey     = L"t-package";
	//m_strPpackageKey	 = L"package";
	m_strRPackageKey	 = L"r-package";
	m_strWPackageKey	 = L"w-package";
	m_stT_IDKey			 = L"t-id";
	m_strPackageHeadKey= L"head";
	m_strPackageTailKey  = L"tail";
	m_strByteBlockKey     = L"byteblock";
	m_strByteBlocksKey    =L"byteblocks";
	m_strDataTypeKey     = L"datatype";
	m_strIsKeyKey           = L"is-key";
	m_strRangesKey        = L"ranges";
	m_strRangeKey         = L"range";
	m_strValueKey			  =L"value";
	m_strVarialblesKey		  = L"variables";
	m_strVarialbleKey		  = L"variable";
	m_strVariableKey = L"variable";
	m_strScriptKey			  = L"script";
	m_strMatchScriptKey		  = L"match-script";
	m_strDataInterfaceKey	  = L"data-interface";
	m_strOrderKey			  = L"order";
	m_strLengthKey			  = L"length";
	m_strDataSetKey		  = L"dataset";
	m_strDataSetsKey		  = L"datasets";
	m_strMinKey			  = L"min";
	m_strMaxKey			  = L"max";
	m_strDataBlockKey		  = L"data-block";
	m_strDataKey			  = L"data";
	m_strDataBindKey		  = L"bind";
	m_strDataBindsKey		  = L"binds";
	m_strDataAttrIDKey			  = L"dataattr-id";
	m_strDataKey			  = L"data";
	m_strInitScriptKey			  = L"init-script";
	m_strEndScriptKey		  = L"end-script";
	m_strOnDataPakScriptKey	  =L"on-data-pkg-script";

	m_strLoopCountKey = L"loop-count";
	m_strLoopIndexKey = L"loop-index";
	m_strDataCountKey = L"data-count";

	m_strDvDataTypesKey = L"datatypes";
	m_strDvDataTypeKey = L"datatype";

	//Procedures
	m_strPpProceduresKey = L"procedures";
	m_strPpProcedureKey = L"procedure";
	m_strPpNodesKey = L"";
	m_strPpNodeKey = L"node";
	m_strPpJumpsKey = L"jumps";
	m_strPpJumpKey = L"jump";
	m_strPpTimersKey = L"timers";
	m_strPpTimerKey = L"timer";
	m_strTimeKey = L"time";
	m_strJumpToKey = L"jump-to";
	m_strResponseKey = L"response";
	m_strPackageRefKey = L"package";
	m_strPackageRefsKey = L"packages";
	m_strDataMapKey = L"data-map";
	m_strPackageIDKey = L"pkg-id";
	m_strProcessKey = L"process";
	
	m_strVariablesKey = L"variables";
	m_strVariableKindKey = L"variablekind";

	m_strProcessDataMapVarIDKey = L"var-id";
	m_strProcessDataMapPkgIDKey = L"pkg-var";
	m_strUseCmmChannelKey = L"channel";
	m_strPriorityKey = L"priority";

	m_strExclusiveKey = L"exclusive";
	m_strReleaseTKey = L"t-release";

	//初始化过程
	m_strInitProcedureRefsKey = L"init-procedures";
	m_strOnlineProcedureRefsKey = L"online-procedures";
	m_strProcedureRefKey = L"procedure-ref";
	m_strProcedureRefIDKey = L"procedure-id";

	//规约模板常量表示定义
	m_strProcedureEndNodeID = L"END";
};
