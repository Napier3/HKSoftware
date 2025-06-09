#pragma once

#include "PxProtoDeviceBase.h"

class CXProtoSrvrBaseApp
{
public:
	CXProtoSrvrBaseApp();
	virtual ~CXProtoSrvrBaseApp();

	virtual void InitProtoSvrBaseApp();
	virtual void ExitProtoSvrBaseApp();
	virtual BOOL CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);
	virtual CExBaseObject* FindDevice(const CString &strDeviceSN);
	virtual CPxProtoDeviceBase* AddDevice(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);
	virtual void InitGlobalFilePath();

public:
	//装置列表
	CExBaseList m_listDevice;

};

extern CXProtoSrvrBaseApp *g_pProtoSvrBaseApp;

//规约引擎服务模块模型和规约文件管理路径
extern CString g_strDvmFilePath;
extern CString g_strPpxmlFilePath;