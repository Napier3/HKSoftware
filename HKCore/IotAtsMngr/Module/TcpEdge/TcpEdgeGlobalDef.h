/**
 *@file
 *\brief 用于定义软件配置以及测试过程中所需的各种标签
 */

#ifndef TCPEDGEGLOBALDEF_H
#define TCPEDGEGLOBALDEF_H
#include "SM2/sm2_sign_and_verify.h"
#include "../../TcpEdgeServer/zconf.h"
#include "../../TcpEdgeServer/zlib.h"
#include "../../../Module/xml/JSON/CJSON.h"
#include <QString>

//报文ID兼数据集ID,过程的首个报文ID即是过程ID
#define PkgData_Auth				"Auth"
#define PkgData_UserDefine			"UserDefine"
#define PkgData_ErrorInfo			"ErrorInfo"
#define PkgData_UserEdit			"UserEdit"
#define PkgData_Health				"Health"
#define PkgData_HealthReq			"HealthReq"
#define PkgData_HealthResp			"HealthResp"
#define PkgData_FileGet				"FileGet"
#define PkgData_FileGetResp			"FileGetResp"
#define PkgData_FileDataTrans		"FileDataTrans"
#define PkgData_FileDataTransResp	"FileDataTransResp"
#define PkgData_FileSend			"FileSend"
#define PkgData_FileSendResp		"FileSendResp"
#define PkgData_TimeSyncReq			"TimeSyncReq"
#define PkgData_TimeSyncResp		"TimeSyncResp"
#define PkgData_DeviceGetLogReq		"DeviceGetLogReq"
#define PkgData_DeviceGetLogResp	"DeviceGetLogResp"
#define PkgData_ContGetLogReq		"ContGetLogReq"
#define PkgData_ContGetLogResp		"ContGetLogResp"
#define PkgData_AppGetLogReq		"AppGetLogReq"
#define PkgData_AppGetLogResp		"AppGetLogResp"
#define PkgData_GetModel			"GetModel"
#define PkgData_GetModelResp		"GetModelResp"
#define PkgData_GetTopoFile			"GetTopoFile"
#define PkgData_GetTopoFileResp		"GetTopoFileResp"
#define PkgData_GetMessage			"GetMessage"
#define PkgData_GetMessageResp		"GetMessageResp"

//读装置时间
#define PkgData_TimeReadReq			"TimeReadReq"
#define PkgData_TimeReadResp		"TimeReadResp"
//设备升级
#define PkgData_DeviceUpdateReq     "DeviceUpdateReq"
#define PkgData_DeviceUpdateResp    "DeviceUpdateResp"
#define PkgData_DeviceUpdateStatusReq  "DeviceUpdateStatusReq"
#define PkgData_DeviceUpdateStatusResp "DeviceUpdateStatusResp"
#define PkgData_DeviceUpdateResult   "DeviceUpdateResult"
//设备控制
#define PkgData_DeviceCtrlReq        "DeviceCtrlReq"
#define PkgData_DeviceCtrlResp       "DeviceCtrlResp"
//获取设备基本信息
#define PkgData_DeviceInfoReq	   	 "DeviceInfoReq"
#define PkgData_DeviceInfoResp	   	 "DeviceInfoResp"
//获取设备状态
#define  PkgData_DeviceStatusReq	 "DeviceStatusReq"
#define  PkgData_DeviceStatusResp	 "DeviceStatusResp"
//设备配置参数修改
#define PkgData_DeviceConfigReq		 "DeviceConfigReq"
#define PkgData_DeviceConfigResp	 "DeviceConfigResp"
//设备事件主动上送
#define PkgData_SysAlarm			 "SysAlarm"

//容器安装
#define PkgData_ConInstallReq		 "ConInstallReq"
#define PkgData_ConInstallResp		 "ConInstallResp"
//容器状态查询
#define PkgData_ConStatusReq         "ConStatusReq"
#define PkgData_ConStatusResp		 "ConStatusResp"
//容器启动
#define PkgData_ConStartReq			 "ConStartReq"
#define PkgData_ConStartResp		 "ConStartResp"
//容器停止
#define PkgData_ConStopReq			 "ConStopReq"
#define PkgData_ConStopResp			 "ConStopResp"
//容器重启
#define PkgData_ConRestartReq		 "ConRestartReq"
#define PkgData_ConRestartResp		 "ConRestartResp"
//容器删除
#define PkgData_ConRemoveReq		 "ConRemoveReq"
#define PkgData_ConRemoveResp		 "ConRemoveResp"
//容器配置查询
#define PkgData_ConGetConfigReq		 "ConGetConfigReq"
#define PkgData_ConGetConfigResp	 "ConGetConfigResp"
//容器配置修改
#define PkgData_ConSetConfigReq		 "ConSetConfigReq"
#define PkgData_ConSetConfigResp	 "ConSetConfigResp"
//容器事件主动上送
#define PkgData_ConAlarm			 "ConAlarm"

//模型变化报告
#define PkgData_ModelChange			 "ModelChange"
#define PkgData_ModelChangeResp		 "ModelChangeResp"
//添加子设备
#define PkgData_DevAdd				 "DevAdd"
#define PkgData_DevAddResp			 "DevAddResp"
//更新子设备状态 
#define PkgData_DevUpdate			 "DevUpdate"
#define PkgData_DevUpdateResp		 "DevUpdateResp"
//子设备信息查询
#define PkgData_ModelDevRead		 "ModelDevRead"
#define PkgData_ModelDevReadResp	 "ModelDevReadResp"
//数据订阅
#define PkgData_DataSubs			 "DataSubs"
#define PkgData_DataSubsResp		 "DataSubsResp"
//数据订阅查询
#define PkgData_GetDataSubs			 "GetDataSubs"
#define PkgData_GetDataSubsResp		 "GetDataSubsResp"
//数据主动上报
#define PkgData_DataSpont			 "DataSpont"
#define PkgData_DataSpontResp		 "DataSpontResp"
//数据查询
#define PkgData_DataRead			 "DataRead"
#define PkgData_DataReadResp		 "DataReadResp"
//参数、定值查询 
#define PkgData_ParaRead			 "ParaRead"
#define PkgData_ParaReadResp		 "ParaReadResp"
//撤销参数定值预置
#define PkgData_ParaCancel			"ParaCancel"
#define PkgData_ParaCancelResp		"ParaCancelResp"
//参数定值预置
#define PkgData_ParaSet				"ParaSet"
#define PkgData_ParaSetResp			"ParaSetResp"
//参数、定值激活
#define PkgData_ParaActivate		"ParaActivate"
#define PkgData_ParaActivateResp	"ParaActivateResp"
//遥控、遥调报文定义
#define PkgData_CtrlCmd				"CtrlCmd"
#define PkgData_CtrlCmdResp			"CtrlCmdResp"
//历史数据查询
#define PkgData_GetHisData			"GetHisData"
#define PkgData_GetHisDataResp		"GetHisDataResp"
//应用配置修改
#define PkgData_AppSetConfigReq		"AppSetConfigReq"
#define PkgData_AppSetConfigResp	"AppSetConfigResp"
//应用配置查询
#define PkgData_AppGetConfigReq		"AppGetConfigReq"
#define PkgData_AppGetConfigResp	"AppGetConfigResp"
//应用去使能
#define PkgData_AppDisableReq		"AppDisableReq"
#define PkgData_AppDisableResp		"AppDisableResp"
//应用使能
#define PkgData_AppEnableReq		"AppEnableReq"
#define PkgData_AppEnableResp		"AppEnableResp"
//应用卸载
#define PkgData_AppRemoveReq		"AppRemoveReq"
#define PkgData_AppRemoveResp		"AppRemoveResp"
//应用停止
#define PkgData_AppStopReq			"AppStopReq"
#define PkgData_AppStopResp			"AppStopResp"
//应用启动
#define PkgData_AppStartReq			"AppStartReq"
#define PkgData_AppStartResp		"AppStartResp"
//应用状态查询
#define PkgData_AppStatusReq		"AppStatusReq"
#define PkgData_AppStatusResp		"AppStatusResp"
//应用安装
#define PkgData_AppInstallReq		"AppInstallReq"
#define PkgData_AppInstallResp		"AppInstallResp"
#define PkgData_AppInstallStatusReq		"AppInstallStatusReq"
#define PkgData_AppInstallStatusResp	"AppInstallStatusResp"
#define PkgData_AppInstallResult	"AppInstallResult"
//应用事件主动上送
#define PkgData_AppAlarm			"AppAlarm"

#define PkgData_AppGetCfgFileReq	"AppGetCfgFileReq"
#define PkgData_AppGetCfgFileResp	"AppGetCfgFileResp"
#define PkgData_AppSetCfgFileReq	"AppSetCfgFileReq"
#define PkgData_AppSetCfgFileResp	"AppSetCfgFileResp"
#define PkgData_GetHisEvent			"GetHisEvent"
#define PkgData_GetHisEventResp		"GetHisEventResp"

//报文内部分元素名称
#define PkgData_Node_DevDateTime        "DevDateTime"
#define PkgData_Node_DevStDateTime      "DevStDateTime"
#define PkgData_Node_Progress			"Progress"
#define PkgData_Node_ZipType			"ZipType"
#define PkgData_Node_SrvEnable			"SrvEnable"
#define PkgData_Node_SrvStatus			"SrvStatus"

#define PkgData_Node_PathVersion        "PathVersion"
#define PkgData_Node_PatchVersion       "PatchVersion"
#define PkgData_Node_Note				"Note"
#define PkgData_Node_ErrorCode			"ErrorCode"
#define PkgData_Node_Longitude			"Longitude"
#define PkgData_Node_Latitude			"Latitude"
#define PkgData_Node_LinkState			"LinkState"
#define PkgData_Node_Msg				"Msg"
#define PkgData_Node_ContStatus			"ContStatus"
#define PkgData_Node_CpuRate			"CpuRate"
#define PkgData_Node_MemUsed			"MemUsed"
#define PkgData_Node_DiskUsed			"DiskUsed"
#define PkgData_Node_Ip					"Ip"
#define PkgData_Node_LifeTime			"LifeTime"
#define PkgData_Node_Image				"Image"
#define PkgData_Node_AppStatus			"AppStatus"
#define PkgData_Node_Process			"Process"
#define PkgData_Node_DeviceId			"DeviceId"
#define PkgData_Node_HardVersion		"HardVersion"
#define PkgData_Node_Cpu				"Cpu"
#define PkgData_Node_Cache				"Cache"
#define PkgData_Node_Arch				"Arch"
#define PkgData_Node_Mem				"Mem"
#define PkgData_Node_Virt				"Virt"
#define PkgData_Node_OS					"OS"
#define PkgData_Node_Os					"Os"
#define PkgData_Node_Links				"Links"
#define PkgData_Node_ContCfgs			"ContCfgs"
#define PkgData_Node_AppCfgs			"AppCfgs"

#define PkgData_Node_DZType				"DZType"
#define PkgData_Node_DZVal				"DZVal"

#define PkgData_Node_Continue			"Continue"
#define PkgData_Node_EventDesc			"EventDesc"
#define PkgData_Node_Result				"Result"
#define PkgData_Node_DataDesc			"DataDesc"
#define PkgData_Node_ModelAll			"ModelAll"
#define PkgData_Node_Head				"Head"
#define PkgData_Node_Data				"Data"
#define PkgData_Node_Time				"Time"
#define PkgData_Node_CmdId				"CmdId"
#define PkgData_Node_FullPathFileName	"FullPathFileName"
#define PkgData_Node_StartByte			"StartByte"
#define PkgData_Node_FileCrc			"FileCrc"
#define PkgData_Node_FileSize			"FileSize"
#define PkgData_Node_ModifyTime			"ModifyTime"
#define PkgData_Node_Container			"Container"
#define PkgData_Node_App				"App"
#define PkgData_Node_StartTime			"StartTime"
#define PkgData_Node_EndTime			"EndTime"
#define PkgData_Node_MaxNumber			"MaxNumber"
#define PkgData_Node_FunName			"FunName"
#define PkgData_Node_Cot				"Cot"
#define PkgData_Node_Mid				"Mid"
#define PkgData_Node_Timestamp			"Timestamp"
#define PkgData_Node_JobId				"JobId"
#define PkgData_Node_Policy				"Policy"
#define PkgData_Node_Version			"Version"
#define PkgData_Node_UpgradeType		"UpgradeType"
#define PkgData_Node_Name				"Name"
#define PkgData_Node_FileType			"FileType"
#define PkgData_Node_Path				"Path"
#define PkgData_Node_Size				"Size"
#define PkgData_Node_File				"File"
#define PkgData_Node_Action				"Action"
#define PkgData_Node_Temperature		"Temperature"
#define PkgData_Node_DevName			"DevName"
#define PkgData_Node_CpuLmt				"CpuLmt"
#define PkgData_Node_MemLmt				"MemLmt"
#define PkgData_Node_DiskLmt			"DiskLmt"
#define PkgData_Node_TemLow				"TemLow"
#define PkgData_Node_TemHigh			"TemHigh"
#define PkgData_Node_Port				"Port"
#define PkgData_Node_Dev				"Dev"
#define PkgData_Node_Mount				"Mount"
#define PkgData_Node_CfgCpu				"CfgCpu"
#define PkgData_Node_Cpus				"Cpus"
#define PkgData_Node_CfgMem				"CfgMem"
#define PkgData_Node_CfgDisk			"CfgDisk"
#define PkgData_Node_Disk				"Disk"
#define PkgData_Node_DiskLmt			"DiskLmt"
#define PkgData_Node_Memory				"Memory"
#define PkgData_Node_DeviceID			"DeviceId"//"DeviceID"     //lmy修改, 协议中是DeviceId
#define PkgData_Node_SetId				"SetId"
#define PkgData_Node_Enable				"Enable"
#define PkgData_Node_ModelName			"ModelName"
#define PkgData_Node_ChangeType			"ChangeType"
#define PkgData_Node_Models				"Models"
#define PkgData_Node_Model				"Model"
#define PkgData_Node_Devices			"Devices"
#define PkgData_Node_Device				"Device"
#define PkgData_Node_DeviceDesc			"DeviceDesc"
#define PkgData_Node_Status				"Status"
#define PkgData_Node_Services			"Services"
#define PkgData_Node_Subs				"Subs"
#define PkgData_Node_ServiceId			"ServiceId"
#define PkgData_Node_Interval			"Interval"
#define PkgData_Node_ParaList			"ParaList"
#define PkgData_Node_DataRefer			"DataRefer"
#define PkgData_Node_CtrlType			"CtrlType"
#define PkgData_Node_CtrlVal			"CtrlVal"
#define PkgData_Node_DataAll			"DataAll"
#define PkgData_Node_DataList			"DataList"
#define PkgData_Node_TransCot			"TransCot"
#define PkgData_Node_Value				"Value"
#define PkgData_Node_Angle				"Angle"
#define PkgData_Node_Quality			"Quality"
#define PkgData_Node_AllDev				"AllDev"
#define PkgData_Node_DeviceList			"DeviceList"
#define PkgData_Node_Spont				"Spont"
#define PkgData_Node_Period				"Period"
#define PkgData_Node_AllData			"AllData"
#define PkgData_Node_TimeStamp			"TimeStamp"
//#define PkgData_Node_Device			"Device"
#define PkgData_Node_FileList			"FileList"
#define PkgData_Node_FileSegNo			"FileSegNo"
#define PkgData_Node_Content			"Content"
#define PkgData_Node_ComboBox			"ComboBox"
#define PkgData_Node_services			"services"
#define PkgData_Node_serviceId			"serviceId"
#define PkgData_Node_DOs				"DOs"
#define PkgData_Node_LDname				"LDname"
#define PkgData_Node_LNtype				"LNtype"
#define PkgData_Node_LNinst				"LNinst"
#define PkgData_Node_DOname				"DOname"
#define PkgData_Node_description		"description"
#define PkgData_Value_CotReq		"1"
#define PkgData_Value_CotResp		"2"
#define PkgData_Value_CotConfirm	"5"

//报文参数类型
#define PkgData_Type_String			"string$" //$用以增加注释
#define PkgData_Type_Object			"object"
#define PkgData_Type_Array			"array"

//错误记录
#define TCPEDGE_ERROR_ID_NO_ERROR				"0"
#define TCPEDGE_ERROR_ID_MODEL_NO_EXIST			"1"
#define TCPEDGE_ERROR_ID_DEVICE_NO_EXIST		"2"
#define TCPEDGE_ERROR_ID_DATA_NO_EXIST			"3"
#define TCPEDGE_ERROR_ID_FILE_NO_EXIST			"4"
#define TCPEDGE_ERROR_ID_CONTROL_TYPE_ERROR		"5"
#define TCPEDGE_ERROR_ID_SET_ID_ERROR			"6"
#define TCPEDGE_ERROR_ID_PARSE_CMD_ERROR		"7"
#define TCPEDGE_ERROR_ID_EXEC_CMD_ERROR			"8"
#define TCPEDGE_ERROR_ID_FILE_FORMAT_ERROR		"9"
#define TCPEDGE_ERROR_ID_DATA_FORMAT_ERROR		"10"

#define TCPEDGE_ERROR_NO_ERROR					"无错误"
#define TCPEDGE_ERROR_MODEL_NO_EXIST			"模型不存在"
#define TCPEDGE_ERROR_DEVICE_NO_EXIST			"装置不存在"
#define TCPEDGE_ERROR_DATA_NO_EXIST				"数据不存在"
#define TCPEDGE_ERROR_FILE_NO_EXIST				"文件不存在"
#define TCPEDGE_ERROR_CRC						"CRC校验失败"
#define TCPEDGE_ERROR_CONTROL_TYPE_ERROR		"控制类型错误"
#define TCPEDGE_ERROR_SET_ID_ERROR				"预置id错误"
#define TCPEDGE_ERROR_PARSE_CMD_ERROR			"解析命令失败"
#define TCPEDGE_ERROR_EXEC_CMD_ERROR			"执行命令失败"
#define TCPEDGE_ERROR_FILE_FORMAT_ERROR			"文件格式错误"
#define TCPEDGE_ERROR_DATA_FORMAT_ERROR			"数据格式错误"

//报文解析器
#define TCPEDGE_PKG_HEAD_LEN		32
#define TCPEDGE_PKG_DATA_MAXLEN		65535
#define TCPEDGE_PKG_INDEX_DATALEN	4
#define TCPEDGE_PKG_INDEX_CONTROL	6
#define TCPEDGE_PKG_INDEX_GATEWAYID	8

//配置解析
#define Cfg_TcpServerFunc			"TcpServerFunc"
#define Cfg_ConnectCfg				"ConnectCfg"
#define Cfg_MngrCfg					"MngrCfg"
#define Cfg_Device					"Device"
#define Cfg_Container				"Container"
#define Cfg_App						"App"
#define Cfg_Log						"Log"
#define Cfg_MqttServerIp			"MqttServerIp"
#define Cfg_MqttServerPort			"MqttServerPort"
#define Cfg_TransmitIp				"TransmitIp"
#define Cfg_TransmitPort			"TransmitPort"
#define Cfg_RemoteAPI				"RemoteAPI"
#define Cfg_RemoteIp				"RemoteIp"
#define Cfg_RemotePort				"RemotePort"
#define Cfg_LocalTcpServerIp		"LocalTcpServerIp"
#define Cfg_TcpServerIp				"TcpServerIp"
#define Cfg_TcpServerMngrPort		"TcpServerMngrPort"
#define Cfg_TcpServerDataPort		"TcpServerDataPort"

typedef unsigned char BYTE;

inline bool tcp_edge_pkg_match_head(BYTE *pPkg)
{
	return (*pPkg == 0xEB) && (*(pPkg+1) == 0x90) && (*(pPkg+2) == 0xEB) && (*(pPkg+3) == 0x90);
}

inline long tcp_edge_pkg_get_data_len(BYTE *pPkg)
{
	return (pPkg[TCPEDGE_PKG_INDEX_DATALEN] << 8) + pPkg[TCPEDGE_PKG_INDEX_DATALEN + 1];
}

inline bool tcp_edge_pkg_has_passage(BYTE *pPkg)
{
	if(pPkg[TCPEDGE_PKG_INDEX_CONTROL] & 8)
	{
		//报文拥有后继
		return true;
	}
	return false;
}

inline bool tcp_edge_pkg_has_deflate(BYTE *pPkg)
{
	if(pPkg[TCPEDGE_PKG_INDEX_CONTROL] & 4)
	{
		//报文压缩
		return true;
	}
	return false;
}

inline bool tcp_edge_pkg_has_auth(BYTE *pPkg)
{
	if(pPkg[TCPEDGE_PKG_INDEX_CONTROL] & 2)
	{
		//报文属于鉴权
		return true;
	}
	return false;
}

inline bool tcp_edge_pkg_has_sign(BYTE *pPkg)
{
	if(pPkg[TCPEDGE_PKG_INDEX_CONTROL] & 1)
	{
		//报文存在签名
		return true;
	}
	return false;
}

inline long tcp_edge_pkg_get_passage_id(BYTE *pPkg)
{
	return pPkg[TCPEDGE_PKG_INDEX_CONTROL + 1];
}

inline void tcp_edge_sm2_cal(BYTE* pPkg, long nPkgLen, SM2_SIGNATURE_STRUCT& sm2, BYTE* pSign)
{
	BYTE pPublicKey[65] = {0x04,0x9c,0x43,0xb0,0x6e,0x16,0x8e,0x5b,0xf6,0xe6,0x8e,0x4d,0xf1,0xd7,0x5b,0x54,0x30,0x6b,0xeb,0x82,0x25,0x8a,0xa1,0x4e,0xa0,0x05,0xf2,0xac,0xba,0x5a,0xbf,0xbb,0x08,0xc0,0x7b,0xba,0xbb,0x74,0x88,0x84,0x22,0xd4,0xce,0x26,0x14,0x2e,0xde,0xdd,0x78,0xba,0xa4,0xb6,0x3b,0x7f,0xa2,0x77,0x75,0xf8,0x75,0xc1,0x88,0x34,0xd9,0xb7,0xb7};
	BYTE pPrivateKey[32] = {0x29,0xe1,0x8a,0xf5,0xb3,0x3a,0x9a,0x69,0xf0,0xb8,0xdd,0x2a,0x97,0x14,0x03,0x5d,0xa5,0xdc,0x59,0xca,0x4b,0xcf,0x84,0x44,0x68,0xd5,0xe0,0x67,0x46,0x32,0x6e,0xd0};
	QString strName = "1234567812345678";
	sm2_sign_data(pPkg, nPkgLen, (const unsigned char*)strName.toStdString().c_str(), 16, pPublicKey, pPrivateKey, &sm2);
	memcpy(pSign, sm2.r_coordinate, 32);
	memcpy(pSign + 32, sm2.s_coordinate, 32);
}

inline BYTE* tcp_edge_zlib_cal(uLongf* pDestLen, BYTE* source, long nSourceLen)
{
	*pDestLen = 2 * 1024 * 1024;
	BYTE* pZlib = new BYTE[*pDestLen];
	int nRet = compress(pZlib, pDestLen, source, nSourceLen);
	if(nRet != Z_OK)
	{
		delete pZlib;
		return NULL;
	}
	return pZlib;
}

#endif