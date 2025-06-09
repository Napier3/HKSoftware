//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ATSMNGRGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define ATSCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define ATSCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define ATSCLASSID_CATS_HISTASKS       (ATSCLASSID_EXLISTCLASS + 0X00000000)
#define ATSCLASSID_CATS_HISTASK       (ATSCLASSID_EXLISTCLASS + 0X00000001)
#define ATSCLASSID_CATS_RTTASK       (ATSCLASSID_EXLISTCLASS + 0X00000002)
#define ATSCLASSID_CATS_HISTASKBATCH       (ATSCLASSID_EXLISTCLASS + 0X00000003)
#define ATSCLASSID_CATS_RTTASKBATCH       (ATSCLASSID_EXLISTCLASS + 0X00000004)
#define ATSCLASSID_CATS_HISDEVICE       (ATSCLASSID_EXLISTCLASS + 0X00000005)
#define ATSCLASSID_CATS_RTDEVICE       (ATSCLASSID_EXLISTCLASS + 0X00000006)
#define ATSCLASSID_CATS_HISREPORTS       (ATSCLASSID_EXLISTCLASS + 0X00000007)
#define ATSCLASSID_CATS_HISREPORT       (ATSCLASSID_EXLISTCLASS + 0X00000008)
#define ATSCLASSID_CATS_RTREPORT       (ATSCLASSID_BASECLASS + 0X00000009)
#define ATSCLASSID_CATS_RTREPORTS       (ATSCLASSID_EXLISTCLASS + 0X0000000A)

class CATSMNGRXmlRWKeys : public CXmlRWKeys
{
protected:
	CATSMNGRXmlRWKeys();
	virtual ~CATSMNGRXmlRWKeys();
	static long g_nATSRef;

public:
	static CATSMNGRXmlRWKeys* g_pXmlKeys;
	static CATSMNGRXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCAts_RTReportsKey; //Ats_RTReports
	BSTR m_strCAts_RTReportKey; //Ats_RTReport
	BSTR m_strCAts_HisReportKey; //Ats_HisReport
	BSTR m_strCAts_HisReportsKey; //Ats_HisReports
	BSTR m_strCAts_RTDeviceKey; //Ats_RTDevice
	BSTR m_strCAts_HisDeviceKey; //Ats_HisDevice
	BSTR m_strCAts_RTTaskBatchKey; //Ats_RTTaskBatch
	BSTR m_strCAts_HisTaskBatchKey; //Ats_HisTaskBatch
	BSTR m_strCAts_RTTaskKey; //Ats_RTTask
	BSTR m_strCAts_HisTaskKey; //Ats_HisTask
	BSTR m_strCAts_HisTasksKey; //Ats_HisTasks
	BSTR m_strIndex_TaskKey; //Index_Task
	BSTR m_strStartTimeKey; //StartTime
	BSTR m_strEndTimeKey; //EndTime
	BSTR m_strStateKey; //State
	BSTR m_strPacketPathKey; //PacketPath
	BSTR m_strTaskNameKey; //TaskName
	BSTR m_strIndex_TaskBatchKey; //Index_TaskBatch
	BSTR m_strDeviceTypeNameKey; //DeviceTypeName
	BSTR m_strDeviceTypeIDKey; //DeviceTypeID
	BSTR m_strDvmFileKey; //DvmFile
	BSTR m_strGbxmlFileKey; //GbxmlFile
	BSTR m_strReportPkgFileKey; //ReportPkgFile
	BSTR m_strEngineRawPkgFileKey; //EngineRawPkgFile
	BSTR m_strVmRawPkgFileKey; //VmRawPkgFile
	BSTR m_strIndex_DeviceKey; //Index_Device
	BSTR m_strDeviceIDKey; //DeviceID
	BSTR m_strTestBatchKey; //TestBatch
	BSTR m_strIndex_ReportKey; //Index_Report
	BSTR m_strItemPathIDKey; //ItemPathID
	BSTR m_strUpdateTimeKey; //UpdateTime
	BSTR m_strDataLenKey; //DataLen
	BSTR m_strDataPosOfFileKey; //DataPosOfFile

public:
	static BSTR CAts_RTReportsKey()  {   return g_pXmlKeys->m_strCAts_RTReportsKey;  }
	static BSTR CAts_RTReportKey()  {   return g_pXmlKeys->m_strCAts_RTReportKey;  }
	static BSTR CAts_HisReportKey()  {   return g_pXmlKeys->m_strCAts_HisReportKey;  }
	static BSTR CAts_HisReportsKey()  {   return g_pXmlKeys->m_strCAts_HisReportsKey;  }
	static BSTR CAts_RTDeviceKey()  {   return g_pXmlKeys->m_strCAts_RTDeviceKey;  }
	static BSTR CAts_HisDeviceKey()  {   return g_pXmlKeys->m_strCAts_HisDeviceKey;  }
	static BSTR CAts_RTTaskBatchKey()  {   return g_pXmlKeys->m_strCAts_RTTaskBatchKey;  }
	static BSTR CAts_HisTaskBatchKey()  {   return g_pXmlKeys->m_strCAts_HisTaskBatchKey;  }
	static BSTR CAts_RTTaskKey()  {   return g_pXmlKeys->m_strCAts_RTTaskKey;  }
	static BSTR CAts_HisTaskKey()  {   return g_pXmlKeys->m_strCAts_HisTaskKey;  }
	static BSTR CAts_HisTasksKey()  {   return g_pXmlKeys->m_strCAts_HisTasksKey;  }
	static BSTR Index_TaskKey()  {   return g_pXmlKeys->m_strIndex_TaskKey;  }
	static BSTR StartTimeKey()  {   return g_pXmlKeys->m_strStartTimeKey;  }
	static BSTR EndTimeKey()  {   return g_pXmlKeys->m_strEndTimeKey;  }
	static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }
	static BSTR PacketPathKey()  {   return g_pXmlKeys->m_strPacketPathKey;  }
	static BSTR TaskNameKey()  {   return g_pXmlKeys->m_strTaskNameKey;  }
	static BSTR Index_TaskBatchKey()  {   return g_pXmlKeys->m_strIndex_TaskBatchKey;  }
	static BSTR DeviceTypeNameKey()  {   return g_pXmlKeys->m_strDeviceTypeNameKey;  }
	static BSTR DeviceTypeIDKey()  {   return g_pXmlKeys->m_strDeviceTypeIDKey;  }
	static BSTR DvmFileKey()  {   return g_pXmlKeys->m_strDvmFileKey;  }
	static BSTR GbxmlFileKey()  {   return g_pXmlKeys->m_strGbxmlFileKey;  }
	static BSTR ReportPkgFileKey()  {   return g_pXmlKeys->m_strReportPkgFileKey;  }
	static BSTR EngineRawPkgFileKey()  {   return g_pXmlKeys->m_strEngineRawPkgFileKey;  }
	static BSTR VmRawPkgFileKey()  {   return g_pXmlKeys->m_strVmRawPkgFileKey;  }
	static BSTR Index_DeviceKey()  {   return g_pXmlKeys->m_strIndex_DeviceKey;  }
	static BSTR DeviceIDKey()  {   return g_pXmlKeys->m_strDeviceIDKey;  }
	static BSTR TestBatchKey()  {   return g_pXmlKeys->m_strTestBatchKey;  }
	static BSTR Index_ReportKey()  {   return g_pXmlKeys->m_strIndex_ReportKey;  }
	static BSTR ItemPathIDKey()  {   return g_pXmlKeys->m_strItemPathIDKey;  }
	static BSTR UpdateTimeKey()  {   return g_pXmlKeys->m_strUpdateTimeKey;  }
	static BSTR DataLenKey()  {   return g_pXmlKeys->m_strDataLenKey;  }
	static BSTR DataPosOfFileKey()  {   return g_pXmlKeys->m_strDataPosOfFileKey;  }
};



class CATSMNGRConstGlobal
{
private:
	CATSMNGRConstGlobal();
	virtual ~CATSMNGRConstGlobal();

public:
	static CATSMNGRConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CATSMNGRConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
