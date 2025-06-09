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
	BSTR m_strVariableKindKey;	//�������� ϵͳ������֡������

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

	//ͨѶ����
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
	BSTR m_strUseCmmChannelKey;    //���̡��ڵ�ʹ�õ�ͨѶͨ���ؼ���
	BSTR m_strPriorityKey;     //���̵����ȼ�
	BSTR m_strChCmmModeKey;
	BSTR m_strExclusiveKey;
	BSTR m_strReleaseTKey;

	//��ʼ�������߹���
	BSTR m_strProcedureRefKey;
	BSTR m_strInitProcedureRefsKey;
	BSTR m_strOnlineProcedureRefsKey;
	BSTR m_strProcedureRefIDKey;

	//��Լģ�峣����ʾ����
	BSTR m_strProcedureEndNodeID;
	
};
