#include "stdafx.h"
#include "IotVmDevice.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../IotEngineGlobalDef.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotVmDevice::CIotVmDevice()
{
	
}

CIotVmDevice::~CIotVmDevice()
{
}

long CIotVmDevice::ConfigDevice(const CString &strConfig)
{
	return 0;
}

long CIotVmDevice::CloseDevice()
{
	//将转换接口模块指针清0
	m_pProtoEventInterface = NULL;

	//设置删除标志，在主线程开始位置统一删除
	m_bCanDelete = TRUE;

	return 0;
}

//初始化协议服务模块接口
void CIotVmDevice::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
				  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	if (m_pPxProtocol != NULL)
	{
		if (m_pPxProtocol->m_strPpxmlFile != strPpxmlFile)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("IotVmcoDevice::InitProtocol : Device(%s) [%s] != [%s] ")
				, m_strID, m_pPxProtocol->m_strPpxmlFile, strPpxmlFile);
		}
		return;
	}

	m_strID = strDeviceID;

	m_oDvmDevice.DeleteAll();
	m_oDvmDevice.m_strID = strDvmFile;
	m_oDvmDevice.OpenXmlFile(strDvmFile,CDataMngrXmlRWKeys::g_pXmlKeys);

	ASSERT (FALSE);
}
