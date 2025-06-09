//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgGlobal.cpp

#include "stdafx.h"
#include "TcpEdgePkgGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CTcpEdgePkgXmlRWKeys

CTcpEdgePkgXmlRWKeys* CTcpEdgePkgXmlRWKeys::g_pXmlKeys = NULL;
long CTcpEdgePkgXmlRWKeys::g_nMngrRef = 0;


CTcpEdgePkgXmlRWKeys::CTcpEdgePkgXmlRWKeys()
{
	m_strCPkg_GetHisEventResp_DeviceKey = L"";
	m_strCPkg_GetHisEventResp_DevicesKey = L"Devices";
	m_strCPkg_GetHisEvent_DeviceKey = L"";
	m_strCPkg_GetHisEvent_DevicesKey = L"Devices";
	m_strCTcpEdgePkgData_GetHisEventRespKey = L"Data";
	m_strCTcpEdgePkgData_GetHisEventKey = L"Data";
	m_strCTcpEdgePkgData_AppSetCfgFileRespKey = L"Data";
	m_strCTcpEdgePkgData_AppSetCfgFileReqKey = L"Data";
	m_strCTcpEdgePkgData_AppGetCfgFileRespKey = L"Data";
	m_strCTcpEdgePkgData_AppGetCfgFileReqKey = L"Data";
	m_strEventDescKey = L"EventDesc";
	m_strResultKey = L"Result";
	m_strDataDescKey = L"DataDesc";
	m_strDZTypeKey = L"DZType";
	m_strDZValKey = L"DZVal";

	m_strCPkg_GetDataSubs_SubSvcsKey = L"Services";
	m_strCPkg_GetDataSubs_SubsKey = L"Subs";
	m_strCPkg_DataReadDevSvcsKey = L"Services";
	m_strCPkg_DataReadDevsKey = L"Devices";
	m_strCTcpEdgePkgData_ModelChangeRespKey = L"Data";
	m_strCTcpEdgePkgData_ModelChangeKey = L"Data";
	m_strCPkg_GetModelResp_ModelKey = L"";
	m_strCPkg_GetModelResp_ModelsKey = L"Models";
	m_strCTcpEdgePkgData_GetModelRespKey = L"Data";
	m_strCTcpEdgePkgData_GetModelKey = L"Data";
	m_strCPkg_AppGetConfigResp_AppCfgKey = L"";
	m_strCPkg_AppGetConfigResp_AppCfgsKey = L"AppCfgs";
	m_strCPkg_AppStatusResp_AppStaProcKey = L"";
	m_strCPkg_AppStatusResp_AppStaProcsKey = L"Process";
	m_strCPkg_AppStatusResp_AppStatuKey = L"";
	m_strCPkg_AppStatusResp_AppStatusKey = L"AppStatus";
	m_strCTcpEdgePkgStringKey = L"";
	m_strCTcpEdgePkgData_AppAlarmKey = L"Data";
	m_strCTcpEdgePkgData_AppSetConfigRespKey = L"Data";
	m_strCTcpEdgePkgData_AppSetConfigReqKey = L"Data";
	m_strCTcpEdgePkgData_AppGetConfigRespKey = L"Data";
	m_strCTcpEdgePkgData_AppGetConfigReqKey = L"Data";
	m_strCTcpEdgePkgData_AppDisableRespKey = L"Data";
	m_strCTcpEdgePkgData_AppDisableReqKey = L"Data";
	m_strCTcpEdgePkgData_AppEnableRespKey = L"Data";
	m_strCTcpEdgePkgData_AppEnableReqKey = L"Data";
	m_strCTcpEdgePkgData_AppRemoveRespKey = L"Data";
	m_strCTcpEdgePkgData_AppRemoveReqKey = L"Data";
	m_strCTcpEdgePkgData_AppStopRespKey = L"Data";
	m_strCTcpEdgePkgData_AppStopReqKey = L"Data";
	m_strCTcpEdgePkgData_AppStartRespKey = L"Data";
	m_strCTcpEdgePkgData_AppStartReqKey = L"Data";
	m_strCTcpEdgePkgData_AppStatusRespKey = L"Data";
	m_strCTcpEdgePkgData_AppStatusReqKey = L"Data";
	m_strCTcpEdgePkgData_AppInstallResultKey = L"Data";
	m_strCTcpEdgePkgData_AppInstallStatusRespKey = L"Data";
	m_strCTcpEdgePkgData_AppInstallStatusReqKey = L"Data";
	m_strCTcpEdgePkgData_AppGetLogRespKey =  L"Data";
	m_strCTcpEdgePkgData_AppInstallRespKey = L"Data";
	m_strCTcpEdgePkgData_AppInstallReqKey = L"Data";
	m_strCPkg_ConGetConfigResp_ContCfgKey = L"";
	m_strCPkg_ConGetConfigResp_ContCfgsKey = L"ContCfgs";
	m_strCPkg_ConStatusResp_ContStatuKey = L"";
	m_strCPkg_ConStatusResp_ContStatusKey = L"ContStatus";
	m_strCPkg_DeviceStatusResp_LinkStateKey = L"";
	m_strCPkg_DeviceStatusResp_LinkStatesKey = L"LinkState";
	m_strCTcpEdgePkgData_ContGetLogRespKey = L"Data";
	m_strCTcpEdgePkgData_ContGetLogReqKey = L"Data";
	m_strCTcpEdgePkgData_ConAlarmKey = L"Data";
	m_strCTcpEdgePkgData_ConSetConfigRespKey = L"Data";
	m_strCTcpEdgePkgData_ConSetConfigReqKey = L"Data";
	m_strCTcpEdgePkgData_ConGetConfigRespKey = L"Data";
	m_strCTcpEdgePkgData_ConGetConfigReqKey = L"Data";
	m_strCTcpEdgePkgData_ConRemoveRespKey = L"Data";
	m_strCTcpEdgePkgData_ConRemoveReqKey = L"Data";
	m_strCTcpEdgePkgData_ConRestartRespKey = L"Data";
	m_strCTcpEdgePkgData_ConRestartReqKey = L"Data";
	m_strCTcpEdgePkgData_ConStopRespKey = L"Data";
	m_strCTcpEdgePkgData_ConStopReqKey = L"Data";
	m_strCTcpEdgePkgData_ConStartRespKey = L"Data";
	m_strCTcpEdgePkgData_ConStartReqKey = L"Data";
	m_strCTcpEdgePkgData_ConStatusRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceInfoResp_LinkKey = L"";
	m_strCTcpEdgePkgData_DeviceInfoResp_LinksKey = L"Links";
	m_strCTcpEdgePkgData_ConStatusReqKey = L"Data";
	m_strCTcpEdgePkgData_ConInstallRespKey = L"Data";
	m_strCTcpEdgePkgData_ConInstallReqKey = L"Data";
	m_strCTcpEdgePkgData_DeviceGetLogRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceGetLogReqKey = L"Data";
	m_strCTcpEdgePkgData_AppGetLogReqKey = L"Data";
	m_strCTcpEdgePkgData_SysAlarmKey = L"Data";
	m_strCTcpEdgePkgData_DeviceConfigRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceConfigReqKey = L"Data";
	m_strCTcpEdgePkgData_DeviceStatusRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceStatusReqKey = L"Data";
	m_strCTcpEdgePkgData_DeviceInfoRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceInfoReqKey = L"Data";
	m_strCTcpEdgePkgData_DeviceCtrlRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceCtrlReqKey = L"Data";
	m_strCTcpEdgePkgData_DeviceUpdateResultKey = L"Data";
	m_strCTcpEdgePkgData_DeviceUpdateStatusRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceUpdateStatusReqKey = L"Data";
	m_strCTcpEdgePkgData_DeviceUpdateRespKey = L"Data";
	m_strCTcpEdgePkgData_DeviceUpdateReqKey = L"Data";
	m_strCTcpEdgePkgData_TimeReadRespKey = L"Data";
	m_strCTcpEdgePkgData_TimeReadReqKey = L"Data";
	m_strCTcpEdgePkgData_TimeSyncRespKey = L"Data";
	m_strCTcpEdgePkgData_TimeSyncReqKey = L"Data";
	m_strCTcpEdgePkgData_FileSendRespKey = L"Data";
	m_strCTcpEdgePkgData_FileSendKey = L"Data";
	m_strCTcpEdgePkgData_FileDataTransRespKey = L"Data";
	m_strCTcpEdgePkgData_FileDataTransKey = L"Data";
	m_strCTcpEdgePkgData_FileGetRespKey = L"Data";
	m_strCTcpEdgePkgData_FileGetKey = L"Data";
	m_strCTcpEdgePkgData_HealthKey = L"Data";
	m_strCTcpEdgePkgDataKey = L"Data";
	m_strCTcpEdgePkgHeadKey = L"Head";
	m_strCTcpEdgePkgKey = L"Data";
	m_strCTcpEdgeAuth_0x03Key = L"Data";
	m_strCTcpEdgeAuth_0x02Key = L"Data";
	m_strCTcpEdgeAuth_0x01Key = L"Data";
	m_strCTcpEdgePkgBaseKey = L"Data";
	m_strCTcpEdgePkgFileKey = L"File";
	m_strCTcpEdgePkgCfgDiskKey = L"CfgDisk";
	m_strCTcpEdgePkgCfgMemKey = L"CfgMem";
	m_strCTcpEdgePkgCfgCpuKey = L"CfgCpu";
	//m_strCTcpEdgePkgMemUsedKey = L"MemUsed";
	m_strCTcpEdgePkgOsKey = L"Os";
	m_strCTcpEdgePkgTemperatureKey = L"Temperature";
	m_strCTcpEdgePkgDiskKey = L"Disk";
	m_strCTcpEdgePkgMemKey = L"Mem";
	m_strCTcpEdgePkgCpuKey = L"Cpu";
	m_strCTcpEdgePkgDevKey = L"Dev";
	m_strCPxPkgDataBaseKey = L"Data";
	m_strDevTypeKey = L"DevType";
	m_strDevNameKey = L"DevName";
	m_strMfgInfoKey = L"MfgInfo";
	m_strHardVersionKey = L"HardVersion";
	m_strCpusKey = L"Cpus";
	m_strFrequencyKey = L"Frequency";
	m_strCacheKey = L"Cache";
	m_strArchKey = L"Arch";
	m_strCpuLmtKey = L"CpuLmt";
	m_strPhyKey = L"Phy";
	m_strVirtKey = L"Virt";
	m_strMemLmtKey = L"MemLmt";
	m_strDiskKey = L"Disk";
	m_strDiskLmtKey = L"DiskLmt";
	m_strTemLowKey = L"TemLow";
	m_strTemHighKey = L"TemHigh";
	m_strDistroKey = L"Distro";
	m_strVersionKey = L"Version";
	m_strKernelKey = L"Kernel";
	m_strSoftVersionKey = L"SoftVersion";
	m_strPatchVersionKey = L"PatchVersion";
	m_strMemoryKey = L"Memory";
	m_strFileTypeKey = L"FileType";
	m_strPathKey = L"Path";
	m_strSizeKey = L"Size";
	m_strFunNameKey = L"FunName";
	m_strCotKey = L"Cot";
	m_strMidKey = L"Mid";
	m_strTimestampKey = L"Timestamp";
	m_strCmdIdKey = L"CmdId";
	m_strFullPathFileNameKey = L"FullPathFileName";
	m_strStartByteKey = L"StartByte";
	m_strStatusKey = L"Status";
	m_strErrorCodeKey = L"ErrorCode";
	m_strNoteKey = L"Note";
	m_strFileCrcKey = L"FileCrc";
	m_strFileSizeKey = L"FileSize";
	m_strModifyTimeKey = L"ModifyTime";
	m_strFileSegNoKey = L"FileSegNo";
	m_strContentKey = L"Content";
	m_strContinueKey = L"Continue";
	m_strTimeKey = L"Time";
	m_strJobIdKey = L"JobId";
	m_strPolicyKey = L"Policy";
	m_strUpgradeTypeKey = L"UpgradeType";
	m_strFileKey = L"File";
	m_strProgressKey = L"Progress";
	m_strStateKey = L"State";
	m_strActionKey = L"Action";
	m_strCpuRateKey = L"CpuRate";
	m_strDiskUsedKey = L"DiskUsed";
	m_strTempValueKey = L"TempValue";
	m_strDevDateTimeKey = L"DevDateTime";
	m_strDevStDateTimeKey = L"DevStDateTime";
	m_strDevRunTimeKey = L"DevRunTime";
	m_strLongitudeKey = L"Longitude";
	m_strLatitudeKey = L"Latitude";
	m_strEventKey = L"Event";
	m_strMsgKey = L"Msg";
	m_strContainerKey = L"Container";
	m_strTypeKey = L"Type";
	m_strIdKey = L"Id";
	m_strMacKey = L"Mac";
	m_strCfgCpuKey = L"CfgCpu";
	m_strCfgMemKey = L"CfgMem";
	m_strCfgDiskKey = L"CfgDisk";
	m_strNameKey = L"Name";
	m_strMemUsedKey = L"MemUsed";
	m_strIpKey = L"Ip";
	m_strCreatedKey = L"Created";
	m_strStartedKey = L"Started";
	m_strLifeTimeKey = L"LifeTime";
	m_strImageKey = L"Image";
	m_strAppKey = L"App";
	m_strEnableKey = L"Enable";
	m_strValueKey = L"Value";
	m_strCPkg_ParaReadSvcsKey = L"Services";
	m_strAppHashKey = L"AppHash";
	m_strSrvNumberKey = L"SrvNumber";
	m_strSrvIndexKey = L"SrvIndex";
	m_strSrvNameKey = L"SrvName";
	m_strSrvEnableKey = L"SrvEnable";
	m_strSrvStatusKey = L"SrvStatus";
	m_strStartTimeKey = L"StartTime";
	m_strModelNameKey = L"ModelName";
	m_strTimeStampKey = L"TimeStamp";

	m_strCPkg_GetTopFileResp_FilesKey = L"FileList";
	m_strCPkg_GetMessageResp_FilesKey = L"FileList";
	m_strCPkg_DataReadDevSvcDLsKey = L"DataList";
	m_strCPkg_DataReadDevSvcsKey = L"Services";
	m_strCPkg_GetDataSubsResp_SubSvcsKey = L"Services";
	m_strCPkg_DataSubsResp_SubSvcsKey = L"Services";
	m_strCPkg_DataSubsResp_SubSvcDevsKey = L"DeviceList";
	m_strCPkg_GetDataSubs_SubSvcsKey = L"Services";
	m_strCPkg_GetDataSubs_SubsKey = L"Subs";
	m_strCPkg_ParaReadSvcsKey = L"Services";
	m_strCPkg_ParaSet_ParaListsKey = L"ParaList";
	m_strCPkg_ParaSet_ParaListKey = L"";
	m_strCPkg_GetModelResp_ModKey = L"";
	m_strCPkg_GetModelResp_ModsKey = L"Models";
	m_strCPkg_ModelChange_ModKey = L"";
	m_strCPkg_ModelChange_ModsKey = L"Models";
	m_strCTcpEdgePkgData_ModelChangeKey = L"Data";
	m_strCPkg_ModelChangeResp_ModKey = L"";
	m_strCPkg_ModelChangeResp_ModsKey = L"Models";
	m_strCTcpEdgePkgData_ModelChangeRespKey = L"Data";
	m_strCPkg_DevAdd_DevKey = L"";
	m_strCPkg_DevAdd_DevsKey = L"Devices";
	m_strCTcpEdgePkgData_DevAddKey = L"Data";
	m_strCPkg_DevAddResp_DevKey = L"";
	m_strCPkg_DevAddResp_DevsKey = L"Devices";
	m_strCTcpEdgePkgData_DevAddRespKey = L"Data";
	m_strCPkg_DevUpdate_DevKey = L"";
	m_strCPkg_DevUpdate_DevsKey = L"Devices";
	m_strCTcpEdgePkgData_DevUpdateKey = L"Data";
	m_strCPkg_DevUpdateResp_DevKey = L"";
	m_strCPkg_DevUpdateResp_DevsKey = L"Devices";
	m_strCTcpEdgePkgData_DevUpdateRespKey = L"Data";
	m_strCPkg_ModelDevRead_ModKey = L"";
	m_strCPkg_ModelDevRead_ModsKey = L"Models";
	m_strCTcpEdgePkgData_ModelDevReadKey = L"Data";
	m_strCPkg_ModelDevReadResp_ModDevKey = L"";
	m_strCPkg_ModelDevReadResp_ModDevsKey = L"Devices";
	m_strCPkg_ModelDevReadResp_ModKey = L"";
	m_strCPkg_ModelDevReadResp_ModsKey = L"Models";
	m_strCTcpEdgePkgData_ModelDevReadRespKey = L"Data";
	m_strCPkg_DataSubs_SubsSvcDLKey = L"";
	m_strCPkg_DataSubs_SubsSvcDLsKey = L"DataList";
	m_strCPkg_DataSubs_SubsSvcDevKey = L"";
	m_strCPkg_DataSubs_SubsSvcDevsKey = L"DeviceList";
	m_strCPkg_DataSubs_SubsSvcKey = L"";
	m_strCPkg_DataSubs_SubsSvcsKey = L"Services";
	m_strCPkg_DatSubs_SubKey = L"";
	m_strCPkg_DatSubs_SubsKey = L"Subs";
	m_strCTcpEdgePkgData_DataSubsKey = L"Data";
	m_strCPkg_DataSubsResp_SubSvcDevKey = L"";
	m_strCPkg_DataSubsResp_SubSvcKey = L"";
	m_strCPkg_DataSubsResp_SubKey = L"";
	m_strCPkg_DataSubsResp_SubsKey = L"Subs";
	m_strCTcpEdgePkgData_DataSubsRespKey = L"Data";
	m_strCPkg_GetDataSubs_SubSvcDevKey = L"";
	m_strCPkg_GetDataSubs_SubSvcDevsKey = L"DeviceList";
	m_strCPkg_GetDataSubs_SubSvcKey = L"";
	m_strCPkg_GetDataSubs_SubKey = L"";
	m_strCTcpEdgePkgData_GetDataSubsKey = L"Data";
	m_strCPkg_GetDataSubsResp_SubSvcDLKey = L"";
	m_strCPkg_GetDataSubsResp_SubSvcDLsKey = L"DataList";
	m_strCPkg_GetDataSubsResp_SubSvcDevKey = L"";
	m_strCPkg_GetDataSubsResp_SubSvcDevsKey = L"DeviceList";
	m_strCPkg_GetDataSubsResp_SubSvcKey = L"";
	m_strCPkg_GetDataSubsResp_SubKey = L"";
	m_strCPkg_GetDataSubsResp_SubsKey = L"Subs";
	m_strCTcpEdgePkgData_GetDataSubsRespKey = L"Data";
	m_strCPkg_DataSpontDevSvcDLKey = L"";
	m_strCPkg_DataSpontDevSvcDLsKey = L"DataList";
	m_strCPkg_DataSpontDevSvcKey = L"";
	m_strCPkg_DataSpontDevSvcsKey = L"Services";
	m_strCPkg_DataSpontDevKey = L"";
	m_strCPkg_DataSpontDevsKey = L"Devices";
	m_strCTcpEdgePkgData_DataSpontKey = L"Data";
	m_strCPkg_DataSpontRespDevKey = L"";
	m_strCPkg_DataSpontRespDevsKey = L"Devices";
	m_strCTcpEdgePkgData_DataSpontRespKey = L"Data";
	m_strCPkg_DataReadDevSvcDLKey = L"";
	m_strCPkg_DataReadDevSvcKey = L"";
	m_strCPkg_DataReadDevKey = L"";
	m_strCTcpEdgePkgData_DataReadKey = L"Data";
	m_strCPkg_DataReadRespDevSvcDLKey = L"";
	m_strCPkg_DataReadRespDevSvcKey = L"";
	m_strCPkg_DataReadRespDevKey = L"";
	m_strCTcpEdgePkgData_DataReadRespKey = L"Data";
	m_strCPkg_ParaReadSvcDLKey = L"";
	m_strCPkg_ParaReadSvcKey = L"";
	m_strCTcpEdgePkgData_ParaReadKey = L"Data";
	m_strCPkg_ParaReadRespSvcDLKey = L"";
	m_strCPkg_ParaReadRespSvcDLsKey = L"DataList";
	m_strCPkg_ParaReadRespSvcKey = L"";
	m_strCPkg_ParaReadRespSvcsKey = L"Services";
	m_strCTcpEdgePkgData_ParaReadRespKey = L"Data";
	m_strCTcpEdgePkgData_GetTopoFileKey = L"Data";
	m_strCPkg_GetTopFileResp_FileKey = L"";
	m_strCTcpEdgePkgData_GetTopoFileRespKey = L"Data";
	m_strCTcpEdgePkgData_GetMessageKey = L"Data";
	m_strCPkg_GetMessageResp_FileKey = L"";
	m_strCTcpEdgePkgData_GetMessageRespKey = L"Data";
	m_strCTcpEdgePkgData_CtrlCmdKey = L"Data";
	m_strCTcpEdgePkgData_CtrlCmdRespKey = L"Data";
	m_strCTcpEdgePkgData_ParaSetKey = L"Data";
	m_strCTcpEdgePkgData_ParaSetRespKey = L"Data";
	m_strCTcpEdgePkgData_ParaActivateKey = L"Data";
	m_strCTcpEdgePkgData_ParaActivateRespKey = L"Data";
	m_strCTcpEdgePkgData_ParaCancelKey = L"Data";
	m_strCTcpEdgePkgData_ParaCancelRespKey = L"Data";
	m_strCPkg_GetHisData_DevSvcKey = L"";
	m_strCPkg_GetHisData_DevSvcsKey = L"Services";
	m_strCPkg_GetHisData_DevKey = L"";
	m_strCPkg_GetHisData_DevsKey = L"Devices";
	m_strCTcpEdgePkgData_GetHisDataKey = L"Data";
	m_strCPkg_GetHisDataResp_DevSvcDLKey = L"";
	m_strCPkg_GetHisDataResp_DevSvcDLsKey = L"DataList";
	m_strCPkg_GetHisDataResp_DevSvcKey = L"";
	m_strCPkg_GetHisDataResp_DevSvcsKey = L"Services";
	m_strCPkg_GetHisDataResp_DevKey = L"";
	m_strCPkg_GetHisDataResp_DevsKey = L"Devices";
	m_strCTcpEdgePkgData_GetHisDataRespKey = L"Data";
	m_strDeviceIdKey = L"DeviceId";
	m_strDeviceDescKey = L"DeviceDesc";
	m_strServiceIdKey = L"ServiceId";
	m_strDataReferKey = L"DataRefer";
	m_strAngleKey = L"Angle";
	m_strQualityKey = L"Quality";
	m_strMaxNumberKey = L"MaxNumber";
	m_strIntervalKey = L"Interval";
	m_strEndTimeKey = L"EndTime";
	m_strStartTimeKey = L"StartTime";
	m_strSetIdKey = L"SetId";
	m_strCtrlTypeKey = L"CtrlType";
	m_strCtrlValKey = L"CtrlVal";
	m_strZipTypeKey = L"ZipType";
	m_strDataAllKey = L"DataAll";
	m_strTransCotKey = L"TransCot";
	m_strModelKey = L"Model";
	m_strSpontKey = L"Spont";
	m_strPeriodKey = L"Period";
	m_strAllDevKey = L"AllDev";
	m_strAllDataKey = L"AllData";
	m_strModelAllKey = L"ModelAll";
	m_strModelNameKey = L"ModelName";
	m_strChangeTypeKey = L"ChangeType";
}

CTcpEdgePkgXmlRWKeys::~CTcpEdgePkgXmlRWKeys()
{
}

CTcpEdgePkgXmlRWKeys* CTcpEdgePkgXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CTcpEdgePkgXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CTcpEdgePkgXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CTcpEdgePkgConstGlobal

long CTcpEdgePkgConstGlobal::g_nGlobalRef = 0;
CTcpEdgePkgConstGlobal* CTcpEdgePkgConstGlobal::g_pGlobal = NULL;


CTcpEdgePkgConstGlobal::CTcpEdgePkgConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CTcpEdgePkgConstGlobal::~CTcpEdgePkgConstGlobal()
{
}

CTcpEdgePkgConstGlobal* CTcpEdgePkgConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CTcpEdgePkgConstGlobal();
	}

	return g_pGlobal;
}

void CTcpEdgePkgConstGlobal::Release()
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
