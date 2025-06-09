/**
 *@file
 *\brief ���ڼ�¼���豸�л�ȡ��ģ�ͼ�¼����
 *���е����ݽṹ���Ǵ�Э���ж�Ӧ������,����
 *���ʻ����޸�����ա���Ե���ؼ��弴�ýӿڼ�Э�顷
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

	//ģ�����豸��Ϣ
	CExBaseList m_devs;

	//ģ�͵��
	CExBaseList m_datas;

public:
	CModelRecord();
	virtual ~CModelRecord();
};

class CAppRecord : public CExBaseList
{
public:
	//Ӧ����Ϣ
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
	//������Ϣ
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
	//Ӧ����Ϣ
	CExBaseList m_apps;

public:
	CContianerRecord();
	virtual ~CContianerRecord();
};

class CTcpEdgeDeviceRecord
{
public:
	//�豸��Ϣ
	QString m_strDevName;
	QString m_strCpuLmt;
	QString m_strMemLmt;
	QString m_strDiskLmt;
	QString m_strTemLow;
	QString m_strTemHigh;

	//������Ϣ
	CExBaseList m_containers;

	//�ļ���Ϣ
	QStringList m_strModelfiles;
	QStringList m_strTopofiles;
	QStringList m_strMessagefiles;

	//���豸��Ϣ
	CExBaseList m_models;

public:
	CTcpEdgeDeviceRecord();
	virtual ~CTcpEdgeDeviceRecord();
	CModelRecord* FindModelByFileName(QString strFileName);
	CModelRecord* FindModelByDeviceId(QString strDeviceId);
};

#endif