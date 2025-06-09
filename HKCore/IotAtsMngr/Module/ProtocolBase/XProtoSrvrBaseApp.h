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
	//װ���б�
	CExBaseList m_listDevice;

};

extern CXProtoSrvrBaseApp *g_pProtoSvrBaseApp;

//��Լ�������ģ��ģ�ͺ͹�Լ�ļ�����·��
extern CString g_strDvmFilePath;
extern CString g_strPpxmlFilePath;