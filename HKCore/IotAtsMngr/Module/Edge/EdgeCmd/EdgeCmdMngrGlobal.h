//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmdMngrGlobal.h

#pragma once

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"

#define EdgeCmdCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define EdgeCmdCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)
#define EDGECMDCLASSID_CEDGEERRORMNGR	(CLASSID_EXLISTCLASS + 0X00100000)

#define EDGECMDCLASSID_CEDGEPARADATAS       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000000)
#define EDGECMDCLASSID_CEDGEPARADATA       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000001)
#define EDGECMDCLASSID_CEDGEGROUP       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000002)
#define EDGECMDCLASSID_CEDGEPARAM       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000003)
#define EDGECMDCLASSID_CEDGEPARAS       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000004)
#define EDGECMDCLASSID_CEDGEDEV       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000005)
#define EDGECMDCLASSID_CEDGECPU       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000006)
#define EDGECMDCLASSID_CEDGEMEM       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000007)
#define EDGECMDCLASSID_CEDGEDISK       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000008)
#define EDGECMDCLASSID_CEDGEOS       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000009)
#define EDGECMDCLASSID_CEDGEMEMUSED       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X0000000A)
#define EDGECMDCLASSID_CEDGETEMPERATURE       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X0000000B)
#define EDGECMDCLASSID_CEDGEREPPERIOD       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X0000000C)
#define EDGECMDCLASSID_CEDGEFILE       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X0000000D)
#define EDGECMDCLASSID_CEDGEIMAGE       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000000E)
#define EDGECMDCLASSID_CEDGEWITHAPP       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000000F)
#define EDGECMDCLASSID_CEDGECPULMT       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000010)
#define EDGECMDCLASSID_CEDGEMEMLMT       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000011)
#define EDGECMDCLASSID_CEDGEDISKLMT       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000012)
#define EDGECMDCLASSID_CEDGESIGN       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000013)
#define EDGECMDCLASSID_CEDGECFGCPU       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000014)
#define EDGECMDCLASSID_CEDGECFGMEM       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000015)
#define EDGECMDCLASSID_CEDGECFGDISK		(EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000016)
#define EDGECMDCLASSID_CEDGELINK       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000017)
#define EDGECMDCLASSID_CEDGEDEVICEINFOS       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000018)
#define EDGECMDCLASSID_CEDGELINKSTATE       (EDGECMDCLASSID_CEDGEERRORMNGR + 0X00000019)
#define EDGECMDCLASSID_CEDGEDEVICESTATUSES       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000001A)
#define EDGECMDCLASSID_CEDGECONTSTATUS       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000001B)
#define EDGECMDCLASSID_CEDGEPROCESS       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000001C)
#define EDGECMDCLASSID_CEDGEAPPS       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000001D)
#define EDGECMDCLASSID_CEDGEDATA       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000001E)
#define EDGECMDCLASSID_CEDGEPARA       (EdgeCmdCLASSID_EXLISTCLASS + 0X0000001F)
#define EDGECMDCLASSID_CEDGEAPPCFGS       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000020)
#define EDGECMDCLASSID_CEDGEBODY       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000021)
#define EDGECMDCLASSID_CEDGECMD       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000022)
#define EDGECMDCLASSID_CEDGELINKS       (EdgeCmdCLASSID_BASECLASS + 0X00000023)
#define EDGECMDCLASSID_CEDGECONTPARA       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000024)
#define EDGECMDCLASSID_CEDGEDIRRESP       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000025)
#define EDGECMDCLASSID_CEDGEAUTH       (EdgeCmdCLASSID_EXLISTCLASS + 0X00000026)

class CEdgeCmdMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CEdgeCmdMngrXmlRWKeys();
	virtual ~CEdgeCmdMngrXmlRWKeys();
	static long g_nEdgeCmdRef;

public:
	static CEdgeCmdMngrXmlRWKeys* g_pXmlKeys;
	static CEdgeCmdMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEdgeDirRespKey; //DirResp
	BSTR m_strCEdgeContParaKey; //contPara
	BSTR m_strCEdgeLinksKey; //links
	BSTR m_strCEdgeCmdKey; //EdgeCmd
	BSTR m_strCEdgeBodyKey; //body
	BSTR m_strCEdgeAppCfgsKey; //appCfgs
	BSTR m_strCEdgeParaKey; //para
	BSTR m_strCEdgeDataKey; //data
	BSTR m_strCEdgeAppsKey; //apps
	BSTR m_strCEdgeProcessKey; //process
	BSTR m_strCEdgeContStatusKey; //conStatus
	BSTR m_strCEdgeDeviceStatusesKey; //deviceStatuses
	BSTR m_strCEdgeLinkStateKey; //linkState
	BSTR m_strCEdgeDeviceInfosKey; //deviceInfos
	BSTR m_strCEdgeLinkKey; //link
	BSTR m_strCEdgeCfgMemKey; //cfgMem
	BSTR m_strCEdgeCfgCpuKey; //cfgCpu
	BSTR m_strCEdgeCfgDiskKey; //cfgDisk
	BSTR m_strCEdgeSignKey; //sign
	BSTR m_strCEdgeDiskLmtKey; //diskLmt
	BSTR m_strCEdgeMemLmtKey; //memLmt
	BSTR m_strCEdgeCpuLmtKey; //cpuLmt
	BSTR m_strCEdgeWithAppKey; //withApp
	BSTR m_strCEdgeImageKey; //image
	BSTR m_strCEdgeFileKey; //file
	BSTR m_strCEdgeRepPeriodKey; //repPeriod
	BSTR m_strCEdgeTemperatureKey; //temperature
	BSTR m_strCEdgeMemUsedKey; //memUsed
	BSTR m_strCEdgeOsKey; //os
	BSTR m_strCEdgeDiskKey; //disk
	BSTR m_strCEdgeMemKey; //mem
	BSTR m_strCEdgeCpuKey; //cpu
	BSTR m_strCEdgeDevKey; //dev
	BSTR m_strCEdgeParasKey; //paras
	BSTR m_strCEdgeParamKey; //param
	BSTR m_strCEdgeGroupKey; //EdgeGroup
	BSTR m_strCEdgeParaDataKey; //EdgeData
	BSTR m_strCEdgeParaDatasKey; //EdgeDatas
	BSTR m_strCEdgeAuthKey;
	BSTR m_strCEdge_AuthKey;
	BSTR m_strDataTypeKey; //dataType
	BSTR m_strValueKey; //value
	BSTR m_strHardVersionKey; //devSN
	BSTR m_strDevTypeKey; //devType
	BSTR m_strDevNameKey; //devName
	BSTR m_strMfgInfoKey; //mfgInfo
	BSTR m_strDevStatusKey; //devStatus
	BSTR m_strCpusKey; //cpus
	BSTR m_strFrequencyKey; //frequency
	BSTR m_strCacheKey; //cache
	BSTR m_strArchKey; //arch
	BSTR m_strCpuLmtKey; //cpuLmt
	BSTR m_strPhyKey; //phy
	BSTR m_strVirtKey; //virt
	BSTR m_strMemoryKey;
	BSTR m_strMemLmtKey; //memLmt
	BSTR m_strDiskKey; //disk
	BSTR m_strDiskLmtKey; //diskLmt
	BSTR m_strDistroKey; //distro
	BSTR m_strVersionKey; //version
	BSTR m_strKernelKey; //kernel
	BSTR m_strSoftVersionKey; //softVersion
	BSTR m_strPatchVersionKey;
	BSTR m_strTemLowKey; //temLow
	BSTR m_strTemHighKey; //temHigh
	BSTR m_strDevPeriodKey; //devPeriod
	BSTR m_strConPeriodKey; //conPeriod
	BSTR m_strAppPeriodKey; //appPeriod
	BSTR m_strHeartPeriodKey; //heartPeriod
	BSTR m_strUrlKey; //url
	BSTR m_strSizeKey; //size
	BSTR m_strMd5Key; //md5
	BSTR m_strEnableKey; //enable
	BSTR m_strLmtKey; //lmt
	BSTR m_strUnitKey; //unit
	BSTR m_strTypeKey; //type
	BSTR m_strIdKey; //id
	BSTR m_strMacKey; //mac
	BSTR m_strNodeIdKey; //nodeId
	BSTR m_strDescriptionKey; //description
	BSTR m_strModelIdKey; //modelId
	BSTR m_strStatusKey; //status
	BSTR m_strDeviceIdKey; //deviceId
	BSTR m_strDeviceStatusKey; //deviceStatus
	BSTR m_strContainerKey; //container
	BSTR m_strRunKey; //run
	BSTR m_strCpuRateKey; //cpuRate
	BSTR m_strMemUsedKey; //memUsed
	BSTR m_strDiskUsedKey; //diskUsed
	BSTR m_strIpKey; //ip
	BSTR m_strCreatedKey; //created
	BSTR m_strStartedKey; //started
	BSTR m_strLifeTimeKey; //lifeTime
	BSTR m_strImageKey; //image
	BSTR m_strSrvIndexKey; //srvIndex
	BSTR m_strSrvNameKey; //srvName
	BSTR m_strSrvEnableKey; //srvEnable
	BSTR m_strSrvStatusKey; //srvStatus
	BSTR m_strStartTimeKey; //startTime
	BSTR m_strAppKey; //app
	BSTR m_strAppHashKey; //appHash
	BSTR m_strSrvNumberKey; //srvNumber
	BSTR m_strStatusCodeKey; //statusCode
	BSTR m_strStatusDescKey; //statusDesc
	BSTR m_strPortKey; //port
	BSTR m_strFileDirKey; //fileDir
	BSTR m_strFileNameKey; //fileName
	BSTR m_strFileSizeKey; //fileSize
	BSTR m_strContentKey; //content
	BSTR m_strCodeKey; //code
	BSTR m_strMessageKey;
	BSTR m_strMsgKey; //msg
	BSTR m_strSignKey; //sign
	BSTR m_strMidKey; //mid
	BSTR m_strTimestampKey; //timestamp
	BSTR m_strExpireKey; //expire
	BSTR m_strIndexAuthKey; //index_auth
	BSTR m_strIndexDeviceKey; //index_device
	BSTR m_strModelKey; //model
	BSTR m_strSnKey; //sn
	BSTR m_strAuthKey; //auth
	BSTR m_strFileTypeKey;

public:
	static BSTR CEdgeDirRespKey()  {   return g_pXmlKeys->m_strCEdgeDirRespKey;  }
	static BSTR CEdgeContParaKey()  {   return g_pXmlKeys->m_strCEdgeContParaKey;  }
	static BSTR CEdgeLinksKey()  {   return g_pXmlKeys->m_strCEdgeLinksKey;  }
	static BSTR CEdgeCmdKey()  {   return g_pXmlKeys->m_strCEdgeCmdKey;  }
	static BSTR CEdgeBodyKey()  {   return g_pXmlKeys->m_strCEdgeBodyKey;  }
	static BSTR CEdgeAppCfgsKey()  {   return g_pXmlKeys->m_strCEdgeAppCfgsKey;  }
	static BSTR CEdgeParaKey()  {   return g_pXmlKeys->m_strCEdgeParaKey;  }
	static BSTR CEdgeDataKey()  {   return g_pXmlKeys->m_strCEdgeDataKey;  }
	static BSTR CEdgeAppsKey()  {   return g_pXmlKeys->m_strCEdgeAppsKey;  }
	static BSTR CEdgeProcessKey()  {   return g_pXmlKeys->m_strCEdgeProcessKey;  }
	static BSTR CEdgeContStatusKey()  {   return g_pXmlKeys->m_strCEdgeContStatusKey;  }
	static BSTR CEdgeDeviceStatusesKey()  {   return g_pXmlKeys->m_strCEdgeDeviceStatusesKey;  }
	static BSTR CEdgeLinkStateKey()  {   return g_pXmlKeys->m_strCEdgeLinkStateKey;  }
	static BSTR CEdgeDeviceInfosKey()  {   return g_pXmlKeys->m_strCEdgeDeviceInfosKey;  }
	static BSTR CEdgeLinkKey()  {   return g_pXmlKeys->m_strCEdgeLinkKey;  }
	static BSTR CEdgeCfgMemKey()  {   return g_pXmlKeys->m_strCEdgeCfgMemKey;  }
	static BSTR CEdgeCfgCpuKey()  {   return g_pXmlKeys->m_strCEdgeCfgCpuKey;  }
	static BSTR CEdgeCfgDiskKey()  {   return g_pXmlKeys->m_strCEdgeCfgDiskKey;  }
	static BSTR CEdgeSignKey()  {   return g_pXmlKeys->m_strCEdgeSignKey;  }
	static BSTR CEdgeDiskLmtKey()  {   return g_pXmlKeys->m_strCEdgeDiskLmtKey;  }
	static BSTR CEdgeMemLmtKey()  {   return g_pXmlKeys->m_strCEdgeMemLmtKey;  }
	static BSTR CEdgeCpuLmtKey()  {   return g_pXmlKeys->m_strCEdgeCpuLmtKey;  }
	static BSTR CEdgeWithAppKey()  {   return g_pXmlKeys->m_strCEdgeWithAppKey;  }
	static BSTR CEdgeImageKey()  {   return g_pXmlKeys->m_strCEdgeImageKey;  }
	static BSTR CEdgeFileKey()  {   return g_pXmlKeys->m_strCEdgeFileKey;  }
	static BSTR CEdgeRepPeriodKey()  {   return g_pXmlKeys->m_strCEdgeRepPeriodKey;  }
	static BSTR CEdgeTemperatureKey()  {   return g_pXmlKeys->m_strCEdgeTemperatureKey;  }
	static BSTR CEdgeMemUsedKey()  {   return g_pXmlKeys->m_strCEdgeMemUsedKey;  }
	static BSTR CEdgeOsKey()  {   return g_pXmlKeys->m_strCEdgeOsKey;  }
	static BSTR CEdgeDiskKey()  {   return g_pXmlKeys->m_strCEdgeDiskKey;  }
	static BSTR CEdgeMemKey()  {   return g_pXmlKeys->m_strCEdgeMemKey;  }
	static BSTR CEdgeCpuKey()  {   return g_pXmlKeys->m_strCEdgeCpuKey;  }
	static BSTR CEdgeDevKey()  {   return g_pXmlKeys->m_strCEdgeDevKey;  }
	static BSTR CEdgeParasKey()  {   return g_pXmlKeys->m_strCEdgeParasKey;  }
	static BSTR CEdgeParamKey()  {   return g_pXmlKeys->m_strCEdgeParamKey;  }
	static BSTR CEdgeGroupKey()  {   return g_pXmlKeys->m_strCEdgeGroupKey;  }
	static BSTR CEdgeParaDataKey()  {   return g_pXmlKeys->m_strCEdgeParaDataKey;  }
	static BSTR CEdgeParaDatasKey()  {   return g_pXmlKeys->m_strCEdgeParaDatasKey;  }
	static BSTR CEdgeAuthKey()  {   return g_pXmlKeys->m_strCEdgeAuthKey; }
	static BSTR CEdge_AuthKey()  {   return g_pXmlKeys->m_strCEdge_AuthKey; }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR HardVersionKey()  {   return g_pXmlKeys->m_strHardVersionKey;  }
	static BSTR DevTypeKey()  {   return g_pXmlKeys->m_strDevTypeKey;  }
	static BSTR DevNameKey()  {   return g_pXmlKeys->m_strDevNameKey;  }
	static BSTR MfgInfoKey()  {   return g_pXmlKeys->m_strMfgInfoKey;  }
	static BSTR DevStatusKey()  {   return g_pXmlKeys->m_strDevStatusKey;  }
	static BSTR CpusKey()  {   return g_pXmlKeys->m_strCpusKey;  }
	static BSTR FrequencyKey()  {   return g_pXmlKeys->m_strFrequencyKey;  }
	static BSTR CacheKey()  {   return g_pXmlKeys->m_strCacheKey;  }
	static BSTR ArchKey()  {   return g_pXmlKeys->m_strArchKey;  }
	static BSTR CpuLmtKey()  {   return g_pXmlKeys->m_strCpuLmtKey;  }
	static BSTR PhyKey()  {   return g_pXmlKeys->m_strPhyKey;  }
	static BSTR VirtKey()  {   return g_pXmlKeys->m_strVirtKey;  }
	static BSTR MemoryKey()	{   return g_pXmlKeys->m_strMemoryKey;  }
	static BSTR MemLmtKey()  {   return g_pXmlKeys->m_strMemLmtKey;  }
	static BSTR DiskKey()  {   return g_pXmlKeys->m_strDiskKey;  }
	static BSTR DiskLmtKey()  {   return g_pXmlKeys->m_strDiskLmtKey;  }
	static BSTR DistroKey()  {   return g_pXmlKeys->m_strDistroKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR KernelKey()  {   return g_pXmlKeys->m_strKernelKey;  }
	static BSTR SoftVersionKey()  {   return g_pXmlKeys->m_strSoftVersionKey;  }
	static BSTR PatchVersionKey() { return g_pXmlKeys->m_strPatchVersionKey; }
	static BSTR TemLowKey()  {   return g_pXmlKeys->m_strTemLowKey;  }
	static BSTR TemHighKey()  {   return g_pXmlKeys->m_strTemHighKey;  }
	static BSTR DevPeriodKey()  {   return g_pXmlKeys->m_strDevPeriodKey;  }
	static BSTR ConPeriodKey()  {   return g_pXmlKeys->m_strConPeriodKey;  }
	static BSTR AppPeriodKey()  {   return g_pXmlKeys->m_strAppPeriodKey;  }
	static BSTR HeartPeriodKey()  {   return g_pXmlKeys->m_strHeartPeriodKey;  }
	static BSTR UrlKey()  {   return g_pXmlKeys->m_strUrlKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR Md5Key()  {   return g_pXmlKeys->m_strMd5Key;  }
	static BSTR EnableKey()  {   return g_pXmlKeys->m_strEnableKey;  }
	static BSTR LmtKey()  {   return g_pXmlKeys->m_strLmtKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR IdKey()  {   return g_pXmlKeys->m_strIdKey;  }
	static BSTR MacKey()  {   return g_pXmlKeys->m_strMacKey;  }
	static BSTR NodeIdKey()  {   return g_pXmlKeys->m_strNodeIdKey;  }
	static BSTR DescriptionKey()  {   return g_pXmlKeys->m_strDescriptionKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModelKey;  }
	static BSTR ModelIdKey()  {   return g_pXmlKeys->m_strModelIdKey;  }
	static BSTR StatusKey()  {   return g_pXmlKeys->m_strStatusKey;  }
	static BSTR DeviceIdKey()  {   return g_pXmlKeys->m_strDeviceIdKey;  }
	static BSTR DeviceStatusKey()  {   return g_pXmlKeys->m_strDeviceStatusKey;  }
	static BSTR ContainerKey()  {   return g_pXmlKeys->m_strContainerKey;  }
	static BSTR RunKey()  {   return g_pXmlKeys->m_strRunKey;  }
	static BSTR CpuRateKey()  {   return g_pXmlKeys->m_strCpuRateKey;  }
	static BSTR MemUsedKey()  {   return g_pXmlKeys->m_strMemUsedKey;  }
	static BSTR DiskUsedKey()  {   return g_pXmlKeys->m_strDiskUsedKey;  }
	static BSTR IpKey()  {   return g_pXmlKeys->m_strIpKey;  }
	static BSTR CreatedKey()  {   return g_pXmlKeys->m_strCreatedKey;  }
	static BSTR StartedKey()  {   return g_pXmlKeys->m_strStartedKey;  }
	static BSTR LifeTimeKey()  {   return g_pXmlKeys->m_strLifeTimeKey;  }
	static BSTR ImageKey()  {   return g_pXmlKeys->m_strImageKey;  }
	static BSTR SrvIndexKey()  {   return g_pXmlKeys->m_strSrvIndexKey;  }
	static BSTR SrvNameKey()  {   return g_pXmlKeys->m_strSrvNameKey;  }
	static BSTR SrvEnableKey()  {   return g_pXmlKeys->m_strSrvEnableKey;  }
	static BSTR SrvStatusKey()  {   return g_pXmlKeys->m_strSrvStatusKey;  }
	static BSTR StartTimeKey()  {   return g_pXmlKeys->m_strStartTimeKey;  }
	static BSTR AppKey()  {   return g_pXmlKeys->m_strAppKey;  }
	static BSTR AppHashKey()  {   return g_pXmlKeys->m_strAppHashKey;  }
	static BSTR SrvNumberKey()  {   return g_pXmlKeys->m_strSrvNumberKey;  }
	static BSTR StatusCodeKey()  {   return g_pXmlKeys->m_strStatusCodeKey;  }
	static BSTR StatusDescKey()  {   return g_pXmlKeys->m_strStatusDescKey;  }
	static BSTR PortKey()  {   return g_pXmlKeys->m_strPortKey;  }
	static BSTR FileDirKey()  {   return g_pXmlKeys->m_strFileDirKey;  }
	static BSTR FileNameKey()  {   return g_pXmlKeys->m_strFileNameKey;  }
	static BSTR FileSizeKey()  {   return g_pXmlKeys->m_strFileSizeKey;  }
	static BSTR ContentKey()  {   return g_pXmlKeys->m_strContentKey;  }
	static BSTR CodeKey()  {   return g_pXmlKeys->m_strCodeKey;  }
	static BSTR MessageKey()  {   return g_pXmlKeys->m_strMessageKey;  }
	static BSTR MsgKey()  {   return g_pXmlKeys->m_strMsgKey;  }
	static BSTR SignKey()  {   return g_pXmlKeys->m_strSignKey;  }
	static BSTR MidKey()  {   return g_pXmlKeys->m_strMidKey;  }
	static BSTR TimestampKey()  {   return g_pXmlKeys->m_strTimestampKey;  }
	static BSTR ExpireKey()  {   return g_pXmlKeys->m_strExpireKey;  }
	static BSTR IndexAuthKey()  {   return g_pXmlKeys->m_strIndexAuthKey;  }
	static BSTR IndexDeviceKey()  {   return g_pXmlKeys->m_strIndexDeviceKey;  }
	static BSTR ModelKey()  {   return g_pXmlKeys->m_strModelKey;  }
	static BSTR SnKey()  {   return g_pXmlKeys->m_strSnKey;  }
	static BSTR AuthKey()  {   return g_pXmlKeys->m_strAuthKey;  }
	static BSTR FileTypeKey() { return g_pXmlKeys->m_strFileTypeKey; }
};



class CEdgeCmdMngrConstGlobal
{
private:
	CEdgeCmdMngrConstGlobal();
	virtual ~CEdgeCmdMngrConstGlobal();

public:
	static CEdgeCmdMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEdgeCmdMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
