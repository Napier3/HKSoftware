#pragma once

#include "../../Module/mysqlapp/mysqlbaseapp.h"
#include "AtsMngrDB/Ats_HisTasks.h"
#include "SensorPpCfg/SensorPpConfig.h"

class CIotAtsMngrBaseApp : public CMySqlBaseApp
{
public:
	CIotAtsMngrBaseApp();
	virtual ~CIotAtsMngrBaseApp();

public:
	virtual void InitIotAtsMngrBaseApp();
	virtual void ExitIotAtsMngrBaseApp();

	CAts_HisTasks m_oHisTasks;				//��ʷ�����¼
	CAts_RTTask *m_pCurTask;				//��ǰ��ͼ��ʵʱ����ʷ����
	CSensorPpConfig m_oSensorPkgPpCfg;			//���������Ĺ�Լ����

	CDvmData m_oFragIndList;
	CDvmData m_oPacketTypeList;
	CDvmData m_oCtrlTypeList;
	CDvmData m_oRequestSetFlagList;
	CDvmData m_oAckStatusList;

public:
	void InitSensorProtocolList();
	BOOL OpenSensorPkgCfgFile();
	void SaveSensorPkgCfgFile();
	BOOL ImportDeviceExcelFile(const CString &strFile,const CString &strDeviceType,CExBaseList &oList);
	void ReleaseCurTask();
	BOOL QueryHisTasks(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd);
	BOOL IsCurRTTask();
	BOOL CreateRTTask(const CString &strName);
};

extern CIotAtsMngrBaseApp *g_theIotAtsMngrBaseApp;