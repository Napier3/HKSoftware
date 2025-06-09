//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ATSMNGRGlobal.cpp

#include "stdafx.h"
#include "ATSMNGRGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CATSMNGRXmlRWKeys

CATSMNGRXmlRWKeys* CATSMNGRXmlRWKeys::g_pXmlKeys = NULL;
long CATSMNGRXmlRWKeys::g_nATSRef = 0;


CATSMNGRXmlRWKeys::CATSMNGRXmlRWKeys()
{
	m_strCAts_RTReportsKey = L"Ats_RTReports";
	m_strCAts_RTReportKey = L"Ats_RTReport";
	m_strCAts_HisReportKey = L"Ats_HisReport";
	m_strCAts_HisReportsKey = L"Ats_HisReports";
	m_strCAts_RTDeviceKey = L"Ats_RTDevice";
	m_strCAts_HisDeviceKey = L"Ats_HisDevice";
	m_strCAts_RTTaskBatchKey = L"Ats_RTTaskBatch";
	m_strCAts_HisTaskBatchKey = L"Ats_HisTaskBatch";
	m_strCAts_RTTaskKey = L"Ats_RTTask";
	m_strCAts_HisTaskKey = L"Ats_HisTask";
	m_strCAts_HisTasksKey = L"Ats_HisTasks";
	m_strIndex_TaskKey = L"Index_Task";
	m_strStartTimeKey = L"StartTime";
	m_strEndTimeKey = L"EndTime";
	m_strStateKey = L"State";
	m_strPacketPathKey = L"PacketPath";
	m_strTaskNameKey = L"TaskName";
	m_strIndex_TaskBatchKey = L"Index_TaskBatch";
	m_strDeviceTypeNameKey = L"DeviceTypeName";
	m_strDeviceTypeIDKey = L"DeviceTypeID";
	m_strDvmFileKey = L"DvmFile";
	m_strGbxmlFileKey = L"GbxmlFile";
	m_strReportPkgFileKey = L"ReportPkgFile";
	m_strEngineRawPkgFileKey = L"EngineRawPkgFile";
	m_strVmRawPkgFileKey = L"VmRawPkgFile";
	m_strIndex_DeviceKey = L"Index_Device";
	m_strDeviceIDKey = L"DeviceID";
	m_strTestBatchKey = L"TestBatch";
	m_strIndex_ReportKey = L"Index_Report";
	m_strItemPathIDKey = L"ItemPathID";
	m_strUpdateTimeKey = L"UpdateTime";
	m_strDataLenKey = L"DataLen";
	m_strDataPosOfFileKey = L"DataPosOfFile";
}

CATSMNGRXmlRWKeys::~CATSMNGRXmlRWKeys()
{
}

CATSMNGRXmlRWKeys* CATSMNGRXmlRWKeys::Create()
{
	g_nATSRef++;

	if (g_nATSRef == 1)
	{
		g_pXmlKeys = new CATSMNGRXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CATSMNGRXmlRWKeys::Release()
{
	g_nATSRef--;

	if (g_nATSRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CATSMNGRConstGlobal

long CATSMNGRConstGlobal::g_nGlobalRef = 0;
CATSMNGRConstGlobal* CATSMNGRConstGlobal::g_pGlobal = NULL;


CATSMNGRConstGlobal::CATSMNGRConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CATSMNGRConstGlobal::~CATSMNGRConstGlobal()
{
}

CATSMNGRConstGlobal* CATSMNGRConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CATSMNGRConstGlobal();
	}

	return g_pGlobal;
}

void CATSMNGRConstGlobal::Release()
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
