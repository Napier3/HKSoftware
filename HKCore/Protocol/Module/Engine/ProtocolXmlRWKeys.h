#pragma once

#include "PpGlobalDefine.h"

class CProtocolXmlRWKeys :	public CXmlRWKeys
{
public:
	CProtocolXmlRWKeys(void);

	virtual ~CProtocolXmlRWKeys(void){};

public:
	static CProtocolXmlRWKeys* g_pXmlRWKeys;
	static CProtocolXmlRWKeys* Create();
	static void Release();
	static long g_nProtocolXmlRWKeysRef;

public:
	BSTR m_strValueKey;
	BSTR m_strTypeKey;
	BSTR m_strVariableKindKey;	//变量类型 系统变量，帧变量等

	BSTR m_strTemplateKey;
	BSTR m_strPackageMaxLengthKey;
	BSTR m_strPackageMinLengthKey;
	BSTR m_strDeviceModelKey;
	BSTR m_strPackageEncodedKey;
	BSTR m_strPkgEncodedLenKey;
	BSTR m_strDefaultChannelKey;
	BSTR m_strVersionKey;
	BSTR m_strDeviceFileForDebugKey;
	BSTR m_strCommModeKey;
	BSTR m_strDeviceModeTypeKey;
	BSTR m_strDatasetModeKey;
	BSTR m_strEngineVersionKey;
	BSTR m_strOnRecvProcedureKey;
	BSTR m_strSndOptr_GlobalVarKey;
	BSTR m_strSndOptr_OptrKey;
	BSTR m_nSndOptr_ValueKey;
	BSTR m_strScriptTypeKey;
	BSTR m_strPkgFullRcvJdgIDKey;
	BSTR m_strEncodingKey;  //2021-12-30  lijunqing 
	BSTR m_strProtoPkgProcessKey;  //2023-1-27  lijunqing 

	//通讯配置
	BSTR m_strCommChannelKey;
	BSTR m_strSerialKey;

	BSTR m_strNetKey;
	BSTR m_strTcpServerKey;
	BSTR m_strTcpClientKey;
	BSTR m_strUdpServerKey;
	BSTR m_strUdpClientKey;

	//Variables
	BSTR m_strVariablesKey;
	BSTR m_strVariableKey;

	//DataTypes
	BSTR m_strDvDataTypesKey;
	BSTR m_strDvDataTypeKey;
	
	//Packages
	BSTR m_strPackagesKey;
	BSTR m_strPackageTextKey;
	BSTR m_strPackageTextsKey;
	BSTR m_strTPackageKey;
	BSTR m_strPackageHeadKey;
	BSTR m_strPackageTailKey;
//	BSTR m_strPpackageKey;
	BSTR m_strRPackageKey;
	BSTR m_strWPackageKey;
	BSTR m_stT_IDKey;
	BSTR m_strOnDataPakScriptKey;
	BSTR m_strPackageRefKey;
	BSTR m_strPackageRefsKey;
	BSTR m_strPackageIDKey;

	BSTR m_strByteBlockKey;
	BSTR m_strByteBlocksKey;
	BSTR m_strDataTypeKey;
	BSTR m_strIsKeyKey;
	BSTR m_strOrderKey;
	BSTR m_strLengthKey;

	BSTR m_strRangesKey;
	BSTR m_strRangeKey;

	BSTR m_strVarialblesKey;
	BSTR m_strVarialbleKey;
	BSTR m_strDataInterfaceKey;

	BSTR m_strScriptKey;
	BSTR m_strMatchScriptKey;
	BSTR m_strInitScriptKey;
	BSTR m_strEndScriptKey;

	BSTR m_strDataSetKey;
	BSTR m_strDataSetsKey;
	BSTR m_strMinKey;
	BSTR m_strMaxKey;
	
	BSTR m_strDataBlockKey;

	BSTR m_strDataKey;
	BSTR m_strLoopCountKey;
	BSTR m_strLoopIndexKey;
	BSTR m_strDataCountKey;

	BSTR m_strDataBindKey;
	BSTR m_strDataBindsKey;
	BSTR m_strDataAttrIDKey;

	//Procedures
	BSTR m_strPpProceduresKey;
	BSTR m_strPpProcedureKey;
	BSTR m_strPpNodesKey;
	BSTR m_strPpNodeKey;
	BSTR m_strPpJumpsKey;
	BSTR m_strPpJumpKey;
	BSTR m_strPpTimersKey;
	BSTR m_strPpTimerKey;
	BSTR m_strTimeKey;
	BSTR m_strJumpToKey;
	BSTR m_strResponseKey;
	BSTR m_strProcessKey;
	BSTR m_strDataMapKey;
	BSTR m_strProcessDataMapVarIDKey;
	BSTR m_strProcessDataMapPkgIDKey;
	BSTR m_strUseCmmChannelKey;    //过程、节点使用的通讯通道关键字
	BSTR m_strPriorityKey;     //过程的优先级
	BSTR m_strChCmmModeKey;
	BSTR m_strExclusiveKey;
	BSTR m_strReleaseTKey;

	//初始化与在线过程
	BSTR m_strProcedureRefKey;
	BSTR m_strInitProcedureRefsKey;
	BSTR m_strOnlineProcedureRefsKey;
	BSTR m_strProcedureRefIDKey;

	//规约模板常量表示定义
	BSTR m_strProcedureEndNodeID;
	
};
