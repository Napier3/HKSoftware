#include "stdafx.h"
#include "IotAtsMngrBaseApp.h"
#include "IotTestControlBase.h"
#include "../../Module/GpsPcTime/LunarSolarTransforTool.h"
#include "..\..\Module\office\ExcelReadWriteEx.h"

CIotAtsMngrBaseApp *g_theIotAtsMngrBaseApp = NULL;

CIotAtsMngrBaseApp::CIotAtsMngrBaseApp()
{
	g_theIotAtsMngrBaseApp = this;
	m_pCurTask = NULL;
}

CIotAtsMngrBaseApp::~CIotAtsMngrBaseApp()
{
	ReleaseCurTask();
}

void CIotAtsMngrBaseApp::InitIotAtsMngrBaseApp()
{
	CDataMngrXmlRWKeys::Create();
	CATSMNGRXmlRWKeys::Create();
	CPpCfgXmlRWKeys::Create();

//	InitMySqlApp(*this);

	InitSensorProtocolList();
	OpenSensorPkgCfgFile();
}

void CIotAtsMngrBaseApp::ExitIotAtsMngrBaseApp()
{
	SaveSensorPkgCfgFile();

	CPpCfgXmlRWKeys::Release();
	CATSMNGRXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();

	DisconnectDB();
}

void CIotAtsMngrBaseApp::InitSensorProtocolList()
{
	m_oFragIndList.AddValue(_T("未分片"),_T("0"),0);
	m_oFragIndList.AddValue(_T("分片"),_T("1"),1);

	m_oPacketTypeList.AddValue(_T("监控数据报文"),_T("0"),0);
	m_oPacketTypeList.AddValue(_T("监控数据响应报文"),_T("1"),1);
	m_oPacketTypeList.AddValue(_T("告警数据报文"),_T("2"),2);
	m_oPacketTypeList.AddValue(_T("告警数据响应报文"),_T("3"),3);
	m_oPacketTypeList.AddValue(_T("控制报文"),_T("4"),4);
	m_oPacketTypeList.AddValue(_T("控制响应报文"),_T("5"),5);
	m_oPacketTypeList.AddValue(_T("分片数据应答报文"),_T("6"),6);

	m_oCtrlTypeList.AddValue(_T(""),_T("0"),0);
	m_oCtrlTypeList.AddValue(_T("传感器通用参数查询/设置"),_T("1"),1);
	m_oCtrlTypeList.AddValue(_T("传感器监测数据查询报文"),_T("2"),2);
	m_oCtrlTypeList.AddValue(_T("传感器告警参数查询/设置"),_T("3"),3);
	m_oCtrlTypeList.AddValue(_T("传感器时间参数查询/设置"),_T("4"),4);
	m_oCtrlTypeList.AddValue(_T("传感器ID查询/设置"),_T("5"),5);
	m_oCtrlTypeList.AddValue(_T("传感器复位设置"),_T("6"),6);
	m_oCtrlTypeList.AddValue(_T("传感器请求校时"),_T("7"),7);

	m_oRequestSetFlagList.AddValue(_T(""),_T("0"),0);
	m_oRequestSetFlagList.AddValue(_T("查询"),_T("0"),0);
	m_oRequestSetFlagList.AddValue(_T("设置"),_T("1"),1);

	m_oAckStatusList.AddValue(_T(""),_T("0"),_T("0"));
	m_oAckStatusList.AddValue(_T("Data_Status"),_T("Data_Status"),_T("Data_Status"));
	m_oAckStatusList.AddValue(_T("SendStatus"),_T("SendStatus"),_T("SendStatus"));
	m_oAckStatusList.AddValue(_T("CommandStatus"),_T("CommandStatus"),_T("CommandStatus"));
}

BOOL CIotAtsMngrBaseApp::OpenSensorPkgCfgFile()
{
	CString strFile = _P_GetLibraryPath();
	strFile += _T("MQTT_Pkg_Sys_Config.xml");
	return m_oSensorPkgPpCfg.OpenXmlFile(strFile,CPpCfgXmlRWKeys::g_pXmlKeys);
}

void CIotAtsMngrBaseApp::SaveSensorPkgCfgFile()
{
	CString strFile = _P_GetLibraryPath();
	strFile += _T("MQTT_Pkg_Sys_Config.xml");
	m_oSensorPkgPpCfg.SaveXmlFile(strFile,CPpCfgXmlRWKeys::g_pXmlKeys);
}

BOOL CIotAtsMngrBaseApp::ImportDeviceExcelFile(const CString &strFile,const CString &strDeviceType,CExBaseList &oList)
{
	//创建新的xls文件
	CExcelReadWriteEx m_ExcelRW;
	m_ExcelRW.InitExcel();
	m_ExcelRW.ShowInExcel(TRUE);

	if (!m_ExcelRW.OpenExcelFile(strFile))
	{
		return FALSE;
	}

	if (!m_ExcelRW.LoadSheet(1,TRUE))
	{
		return FALSE;
	}

	CString strTypeID = _T("");
	CString strDeviceID = _T("");
	long nRowIndex = 1;
	long nRowCount = m_ExcelRW.GetRowCount();
	while(TRUE)
	{
		nRowIndex++;
		if (nRowIndex > nRowCount)
		{
			break;
		}

		strTypeID = m_ExcelRW.GetCellString(nRowIndex, 2);
		strDeviceID = m_ExcelRW.GetCellString(nRowIndex, 3);

		if (strTypeID.IsEmpty() || strDeviceID.IsEmpty())
		{
			break;
		}
		if (strDeviceType != strTypeID)
		{
			continue;
		}

		CAts_RTDevice *pNew = new CAts_RTDevice;
		pNew->m_strID = strDeviceID;
		oList.AddNewChild(pNew);
	}

	return TRUE;
}

void CIotAtsMngrBaseApp::ReleaseCurTask()
{
	if (m_pCurTask == NULL)
	{
		return;
	}

	if (IsCurRTTask())
	{//实时测试任务
		delete m_pCurTask;
	}

	m_pCurTask = NULL;
}

BOOL CIotAtsMngrBaseApp::QueryHisTasks(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd)
{
	CString strTmPK,strTable,strFilter_Date,strSql;
	strTmPK = CATSMNGRXmlRWKeys::StartTimeKey();
	strTable = CATSMNGRXmlRWKeys::CAts_HisTaskKey();

	ModifyQueryEndTime(tmEnd);
	if(!CheckTimeIsRight(tmStart,tmEnd,strTmPK,strFilter_Date))
	{
		return FALSE;
	}

	m_oHisTasks.DeleteAll();

	strSql.Format(_T("select * from %s where %s"),strTable,strFilter_Date);
	return m_oHisTasks.DB_SelectSqlEx(this,CATSMNGRXmlRWKeys::g_pXmlKeys,strSql);
}

BOOL CIotAtsMngrBaseApp::IsCurRTTask()
{
	ASSERT(m_pCurTask != NULL);
	return (m_pCurTask->GetClassID() == ATSCLASSID_CATS_RTTASK);
}

BOOL CIotAtsMngrBaseApp::CreateRTTask(const CString &strName)
{
	CString strPath = _P_GetDBPath();

	CAts_RTTask *pNew = new CAts_RTTask;
	pNew->m_strName = strName;
	pNew->m_strID = strName;
	pNew->m_strPacketPath.Format(_T("%sPacketFolder\\%s_%04d%02d%02d%02d%02d%02d\\")
		,strPath,strName,pNew->m_tmStartTime.wYear,pNew->m_tmStartTime.wMonth
		,pNew->m_tmStartTime.wDay,pNew->m_tmStartTime.wHour,pNew->m_tmStartTime.wMinute
		,pNew->m_tmStartTime.wSecond);
	BOOL bRet = pNew->DB_Insert_Own(this,NULL,CATSMNGRXmlRWKeys::g_pXmlKeys,NULL);
	
	if (!bRet)
	{
		delete pNew;
		pNew = NULL;
	}
	else
	{
		m_pCurTask = pNew;
		CreateAllDirectories(pNew->m_strPacketPath);
	}
	
	return bRet;
}