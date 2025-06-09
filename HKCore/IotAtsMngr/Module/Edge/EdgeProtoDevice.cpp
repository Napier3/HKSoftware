#include "stdafx.h"
#include "EdgeProtoDevice.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../IotEngineGlobalDef.h"

#include "IotEngineToEdgeV4.h"
#include "IotEngineToEdgeV5.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CEdgeProtoDevice::CEdgeProtoDevice()
{
	m_pDatasetView = NULL;
	m_bIsOnline = FALSE;
	m_pLinkupReport = new CDataGroup;
	m_pReportFile = NULL;
	m_bIsTest = 0;
}

CEdgeProtoDevice::~CEdgeProtoDevice()
{
	m_pLinkupReport->DeleteAll();
	delete m_pLinkupReport;
	m_pLinkupReport = NULL;
	fclose(m_pReportFile);
}

long CEdgeProtoDevice::ConfigDevice(const CString &strConfig)
{
	return 0;
}

long CEdgeProtoDevice::CloseDevice()
{
	//将转换接口模块指针清0
	m_pProtoEventInterface = NULL;

	//设置删除标志，在主线程开始位置统一删除
	m_bCanDelete = TRUE;
	m_pDatasetView = NULL;

	return 0;
}

//初始化协议服务模块接口
void CEdgeProtoDevice::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
				  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	if (m_pPxProtocol != NULL)
	{
		if (m_pPxProtocol->m_strPpxmlFile != strPpxmlFile)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("EdgeProtocoDevice::InitProtocol : Device(%s) [%s] != [%s] ")
				, m_strID, m_pPxProtocol->m_strPpxmlFile, strPpxmlFile);
		}
		return;
	}

	m_strID = strDeviceID;
	m_strDvmFile = strDvmFile;

	m_oDvmDevice.DeleteAll();
	if(strDvmFile.Find(_T("\\")) == -1)
	{
		m_strDvmFile = _P_GetInstallPath();
		m_strDvmFile += _T("e-Protocol\\Library\\");
		m_strDvmFile += strDvmFile;
	}
	m_oDvmDevice.OpenXmlFile(m_strDvmFile,CDataMngrXmlRWKeys::g_pXmlKeys);
	m_oDvmDevice.m_strID = strDvmFile;

	if (strPpxmlFile == ENGINE_TO_PX_EDGEV4)
	{
		m_pPxProtocol = new CIotEdgeProtoServerV4();
		m_pPxProtocol->m_strPpxmlFile = strPpxmlFile;
	}
	else if (strPpxmlFile == ENGINE_TO_PX_EDGEV5)
	{
		m_pPxProtocol = new CIotEdgeProtoServerV5();
		m_pPxProtocol->m_strPpxmlFile = strPpxmlFile;
	}
}

//处理传感器业务报文逻辑
void CEdgeProtoDevice::ProcessPkg(char *pBuf,long nLen)
{
}
