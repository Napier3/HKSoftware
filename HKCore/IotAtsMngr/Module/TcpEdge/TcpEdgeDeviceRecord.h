/**
 *@file
 *\brief 用于记录从设备中获取的模型记录数据
 *所有的数据结构都是从协议中对应过来的,如有
 *疑问或者修改请参照《边缘网关即插即用接口及协议》
 */

#ifndef TCPEDGEDEVICERECORD_H
#define TCPEDGEDEVICERECORD_H

#include "../../../Module/BaseClass/ExBaseList.h"

class CModelDeviceRecord : public CExBaseList
{
public:
	QString m_strDeviceId;
	QString m_strDeviceDesc;
	QString m_strStatus;

public:
	CModelDeviceRecord();
	virtual ~CModelDeviceRecord();
};

class CModelRecord : public CExBaseList
{
public:
	QString m_strModelName;
	QString m_strModifyTime;
	QString m_strFullPathFileName;
	QString m_strFileCrc;

	//模块子设备信息
	CExBaseList m_devs;

	//模型点表
	CExBaseList m_datas;

public:
	CModelRecord();
	virtual ~CModelRecord();
};

class CAppRecord : public CExBaseList
{
public:
	//应用信息
	QString m_strApp;
	QString m_strCpus;
	QString m_strCpuLmt;
	QString m_strMemory;
	QString m_strMemLmt;

public:
	CAppRecord();
	virtual ~CAppRecord();
};

class CContianerRecord : public CExBaseList
{
public:
	//容器信息
	QString m_strContainer;
	QString m_strCpus;
	QString m_strCpuLmt;
	QString m_strMemory;
	QString m_strMemLmt;
	QString m_strDisk;
	QString m_strDiskLmt;
	QStringList m_strMounts;
	QStringList m_strPorts;
	QStringList m_strDevs;
	//应用信息
	CExBaseList m_apps;

public:
	CContianerRecord();
	virtual ~CContianerRecord();
};

class CTcpEdgeDeviceRecord
{
public:
	//设备信息
	QString m_strDevName;
	QString m_strCpuLmt;
	QString m_strMemLmt;
	QString m_strDiskLmt;
	QString m_strTemLow;
	QString m_strTemHigh;

	//容器信息
	CExBaseList m_containers;

	//文件信息
	QStringList m_strModelfiles;
	QStringList m_strTopofiles;
	QStringList m_strMessagefiles;

	//子设备信息
	CExBaseList m_models;

public:
	CTcpEdgeDeviceRecord();
	virtual ~CTcpEdgeDeviceRecord();
	CModelRecord* FindModelByFileName(QString strFileName);
	CModelRecord* FindModelByDeviceId(QString strDeviceId);
};

#endif