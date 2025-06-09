#pragma once

#include "SttGlobalSensorDef.h"
#include <vector>
#include "SensorFragMngr.h"
#include "../../../Module/DataMngr/DvmDataset.h"

#define PP_PRASE_SUCCESS					0
#define PP_PRASE_ErrType_FRAG				1
#define PP_PRASE_ErrType_CRCERR				2
#define PP_PRASE_ErrType_NOTFINDPRASE		3
#define PP_PRASE_ErrType_NOTACK				4
#define PP_PRASE_ErrType_PARANOTMATCH		5
#define PP_PRASE_ErrType_PARALENERR			6
#define PP_PRASE_ErrType_NOPKG				7
#define PP_PRASE_ErrType_NOPROCEDURE		8

class CSensorProtocalEngine
{
public:
	CSensorProtocalEngine();
	virtual ~CSensorProtocalEngine();

public:
	
	//解析之前，CRC校验
	static BOOL CheckPkgCRC(BYTE *pBuf,long nLen);
	//解析报文头，判断是否是分包报文
	static long PraseSensorPkgInfoHead(BYTE *pBuf,long nLen, SensorPkgInfo &oSensorPkgInfo);
	//将报文缓存解析为结构体
	static long PraseSensorPkgInfo(char *pBuf,long nLen,SensorPkgInfo &oSensorPkgInfo);

//	static BOOL GenerateSensorPacket(CMqttPpProduce *pProduce,char **ppBuf,long &nLen);
//	static long CalcSensorCtrlPacketLength(CMqttPpProduce *pProduce);
	void UpdateSensorAppPacket(__int64 n64SensorID,char *pBuf,long nLen);
};

long sensor_pkt_get_paraData(BYTE *pPkg,long nOffset,SensorParaData *pParaData);
long sensor_pkt_get_paraDatas(BYTE *pPkgDataBegin,BYTE *pPkgDataEnd,SensorPkgInfo &oSensorPkgInfo);
//long UpdatePraseValue(SensorPkgInfo &oSensorPkgInfo,CMqttPpPrase *pPrase);
//void UpdateDatasByPrase(CExBaseList &oDvmDatas,CMqttPpPrase *pPrase,BOOL bAddIfNotExist=FALSE);

//根据报文结构体更新数据集
long UpdateDatasetValue(SensorPkgInfo &oSensorPkgInfo,CDvmDataset *pDataset);