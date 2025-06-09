//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmdMngrGlobal.cpp

#include "stdafx.h"
#include "EdgeCmdMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CEdgeCmdMngrXmlRWKeys

CEdgeCmdMngrXmlRWKeys* CEdgeCmdMngrXmlRWKeys::g_pXmlKeys = NULL;
long CEdgeCmdMngrXmlRWKeys::g_nEdgeCmdRef = 0;


CEdgeCmdMngrXmlRWKeys::CEdgeCmdMngrXmlRWKeys()
{
	m_strCEdgeDirRespKey = L"DirResp";
	m_strCEdgeContParaKey = L"contPara";
	m_strCEdgeLinksKey = L"links";
	m_strCEdgeCmdKey = L"EdgeCmd";
	m_strCEdgeBodyKey = L"body";
	m_strCEdgeAppCfgsKey = L"appCfgs";
	m_strCEdgeParaKey = L"para";
	m_strCEdgeDataKey = L"data";
	m_strCEdgeAppsKey = L"apps";
	m_strCEdgeProcessKey = L"process";
	m_strCEdgeContStatusKey = L"contStatus";
	m_strCEdgeDeviceStatusesKey = L"deviceStatuses";
	m_strCEdgeLinkStateKey = L"linkState";
	m_strCEdgeDeviceInfosKey = L"deviceInfos";
	m_strCEdgeLinkKey = L"link";
	m_strCEdgeCfgMemKey = L"cfgMem";
	m_strCEdgeCfgCpuKey = L"cfgCpu";
	m_strCEdgeCfgDiskKey = L"cfgDisk";
	m_strCEdgeSignKey = L"sign";
	m_strCEdgeDiskLmtKey = L"cfgDisk";
	m_strCEdgeMemLmtKey = L"cfgMem";
	m_strCEdgeCpuLmtKey = L"cfgCpu";
	m_strCEdgeWithAppKey = L"withAPP";
	m_strCEdgeImageKey = L"image";
	m_strCEdgeFileKey = L"file";
	m_strCEdgeRepPeriodKey = L"repPeriod";
	m_strCEdgeTemperatureKey = L"temperature";
	m_strCEdgeMemUsedKey = L"memUsed";
	m_strCEdgeOsKey = L"os";
	m_strCEdgeDiskKey = L"disk";
	m_strCEdgeMemKey = L"mem";
	m_strCEdgeCpuKey = L"cpu";
	m_strCEdgeDevKey = L"dev";
	m_strCEdgeParasKey = L"paras";
	m_strCEdgeParamKey = L"param";
	m_strCEdgeGroupKey = L"EdgeGroup";
	m_strCEdgeParaDataKey = L"EdgeParaData";
	m_strCEdgeParaDatasKey = L"EdgeParaDatas";
	m_strDataTypeKey = L"dataType";
	m_strValueKey = L"value";
	//yzj 第5部分中dev的SN被取消了,取而代之的是hardVersion标志
	//定义为:终端硬件版本号
	//m_strHardVersionKey = L"devSN";
	m_strHardVersionKey = L"hardVersion";
	m_strDevTypeKey = L"devType";
	m_strDevNameKey = L"devName";
	m_strMfgInfoKey = L"mfgInfo";
	m_strDevStatusKey = L"devStatus";
	m_strCpusKey = L"cpus";
	m_strFrequencyKey = L"frequency";
	m_strCacheKey = L"cache";
	m_strArchKey = L"arch";
	m_strCpuLmtKey = L"cpuLmt";
	m_strPhyKey = L"phy";
	m_strVirtKey = L"virt";
	m_strMemoryKey = L"memory";
	m_strMemLmtKey = L"memLmt";
	m_strDiskKey = L"disk";
	m_strDiskLmtKey = L"diskLmt";
	m_strDistroKey = L"distro";
	m_strVersionKey = L"version";
	m_strKernelKey = L"kernel";
	m_strSoftVersionKey = L"softVersion";
	m_strPatchVersionKey = L"patchVersion";
	m_strTemLowKey = L"temLow";
	m_strTemHighKey = L"temHigh";
	m_strDevPeriodKey = L"devPeriod";
	m_strConPeriodKey = L"conPeriod";
	m_strAppPeriodKey = L"appPeriod";
	m_strHeartPeriodKey = L"heartPeriod";
	m_strUrlKey = L"url";
	m_strSizeKey = L"size";
	m_strMd5Key = L"md5";
	m_strEnableKey = L"enable";
	m_strLmtKey = L"Lmt";
	m_strUnitKey = L"unit";
	m_strTypeKey = L"type";
	m_strIdKey = L"id";
	m_strMacKey = L"mac";
	m_strNodeIdKey = L"nodeId";
	m_strDescriptionKey = L"description";
	m_strModelIdKey = L"modelId";
	m_strStatusKey = L"status";
	m_strDeviceIdKey = L"deviceId";
	m_strDeviceStatusKey = L"deviceStatus";
	m_strContainerKey = L"container";
	m_strRunKey = L"run";
	m_strCpuRateKey = L"cpuRate";
	m_strMemUsedKey = L"memUsed";
	m_strDiskUsedKey = L"diskUsed";
	m_strIpKey = L"ip";
	m_strCreatedKey = L"created";
	m_strStartedKey = L"started";
	m_strLifeTimeKey = L"lifeTime";
	m_strImageKey = L"image";
	m_strSrvIndexKey = L"srvIndex";
	m_strSrvNameKey = L"srvName";
	m_strSrvEnableKey = L"srvEnable";
	m_strSrvStatusKey = L"srvStatus";
	m_strStartTimeKey = L"startTime";
	m_strAppKey = L"app";
	m_strAppHashKey = L"appHash";
	m_strSrvNumberKey = L"srvNumber";
	m_strStatusCodeKey = L"statusCode";
	m_strStatusDescKey = L"statusDesc";
	m_strPortKey = L"port";
	m_strFileDirKey = L"fileDir";
	m_strFileNameKey = L"fileName";
	m_strFileSizeKey = L"fileSize";
	m_strContentKey = L"Content";
	m_strCodeKey = L"code";
	m_strMsgKey = L"msg";
	m_strSignKey = L"sign";
	m_strMidKey = L"mid";
	m_strTimestampKey = L"timestamp";
	m_strExpireKey = L"expire";
	m_strCEdge_AuthKey = L"edge_auth";
	m_strCEdgeAuthKey = L"edgeAuth";
	m_strIndexAuthKey = L"index_auth";
	m_strIndexDeviceKey = L"index_device";
	m_strModelKey = L"model";
	m_strSnKey = L"sn";
	m_strAuthKey = L"auth";
	m_strFileTypeKey = L"fileType";
	m_strMessageKey = L"message";
}

CEdgeCmdMngrXmlRWKeys::~CEdgeCmdMngrXmlRWKeys()
{
}

CEdgeCmdMngrXmlRWKeys* CEdgeCmdMngrXmlRWKeys::Create()
{
	g_nEdgeCmdRef++;

	if (g_nEdgeCmdRef == 1)
	{
		g_pXmlKeys = new CEdgeCmdMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEdgeCmdMngrXmlRWKeys::Release()
{
	g_nEdgeCmdRef--;

	if (g_nEdgeCmdRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEdgeCmdMngrConstGlobal

long CEdgeCmdMngrConstGlobal::g_nGlobalRef = 0;
CEdgeCmdMngrConstGlobal* CEdgeCmdMngrConstGlobal::g_pGlobal = NULL;


CEdgeCmdMngrConstGlobal::CEdgeCmdMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CEdgeCmdMngrConstGlobal::~CEdgeCmdMngrConstGlobal()
{
}

CEdgeCmdMngrConstGlobal* CEdgeCmdMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEdgeCmdMngrConstGlobal();
	}

	return g_pGlobal;
}

void CEdgeCmdMngrConstGlobal::Release()
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