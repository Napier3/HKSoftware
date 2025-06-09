#pragma once

#include "../ProtocolBase/PxProtoDeviceBase.h"
#include "IotEdgeProtoServerBase.h"

#define ENGINE_TO_PX_EDGEV4	_T("EDGEV4")
#define ENGINE_TO_PX_EDGEV5	_T("EDGEV5")

#define CLASSID_EDGEPROTOCOLDEVICE  (CLASSID_LISTCLASS + 0X01000000)

class CEdgeProtoDevice: public CPxProtoDeviceBase
{//m_strID:DeviceID
public:
	CEdgeProtoDevice();
	virtual ~CEdgeProtoDevice();

	CString m_strDvmFile;
	CExBaseList m_listTopoDevice;
	CString m_strTopoID;//当前测试的端设备
	CExBaseList m_listLib;//当前设备生效的上报报文数据集
	BOOL m_bIsOnline;//设备是否已经通过认证
	long m_bIsTest;//是否是被选中测试的设备
	CDataGroup* m_pLinkupReport;

	FILE* m_pReportFile; //存放报文的文件

public:
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();

	//初始化协议服务模块
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);

	
	//处理传感器业务报文逻辑
	void ProcessPkg(char *pBuf,long nLen);

	virtual UINT GetClassID()	{	return CLASSID_EDGEPROTOCOLDEVICE;	}

	
};
