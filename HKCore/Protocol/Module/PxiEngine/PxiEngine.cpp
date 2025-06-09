// PoEngine.cpp : 实现文件
//

#include "stdafx.h"
#include "../Engine/PpEngineBaseApp.h"
#include "PxiEngine.h"

CPxiEngine *g_thePxiEngine = NULL;
CPxiEngine* CPxiEngine::g_pPxiEngine = NULL;
long CPxiEngine::g_nPxiEngineRef = 0;

//2020-11-09  lijunqing
CPxiDeviceCommCmdMessage *g_thePxiDeviceCommCmdMessage = NULL;

CPxiEngine::CPxiEngine()
{
    g_thePxiEngine = this;
}

CPxiEngine::~CPxiEngine()
{
	m_listDevice.DeleteAll();
}

CPxiEngine* CPxiEngine::Create()
{
    g_nPxiEngineRef++;

    if (g_nPxiEngineRef == 1)
    {
        g_pPxiEngine = new CPxiEngine();
        g_pPxiEngine->InitPpBaseApp();
    }

    return g_pPxiEngine;
}

void CPxiEngine::Release()
{
    g_nPxiEngineRef--;

    if (g_nPxiEngineRef == 0)
    {
        g_pPxiEngine->ExitPpBaseApp();
        delete g_pPxiEngine;
        g_pPxiEngine = NULL;
    }
}

CPxiEngine* CPxiEngine::GetPxiEngine()
{
    return g_pPxiEngine;
}



// CPxiEngine 消息处理程序
CString CPxiEngine::GetVersion(void)
{
	CString strResult;

	// TODO: 在此添加调度处理程序代码

	return strResult;
}

CPxiDevice* CPxiEngine::CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID, CExBaseObject *pPpEngineDevice)
{
	if (g_bLogEngineDebugInfor)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Createdevice:%s ; %s"), strTemplateFile.GetString(), strDeviceFile.GetString());
	}

	CString cstrDeviceID(strDeviceID);
	CPpEngineData *pEngineData = g_pTheEngineApp->FindEngineData(cstrDeviceID);

	if (pEngineData == NULL)
	{
		if (g_bLogEngineDebugInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DeviceID=%s not exist! Create New"), cstrDeviceID.GetString());
		}
		
        pEngineData = g_pTheEngineApp->Create(strTemplateFile.GetString(), strDeviceFile.GetString());
        pEngineData->m_strDeviceID = strDeviceID;
        pEngineData->m_pPxiDeviceCommCmdMessage = g_thePxiDeviceCommCmdMessage;  //2020-11-07 lijunqing
		pEngineData->m_pEngineDeviceBase = pPpEngineDevice;  //shaolei 2023-12-25
		pEngineData->BuildScript();
	}
	else
	{
		if (g_bLogEngineDebugInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DeviceID=%s exist! PpFile=[%s]  DvmFile=[%s]")
                     , cstrDeviceID.GetString(), pEngineData->m_strPpTemplateFile.GetString(), pEngineData->m_strPpDeviceFile.GetString());
		}
	}

	if (pEngineData != NULL)
	{
		CPxiDevice *pDevice = CPxiDevice::_New_CDevice(pEngineData, cstrDeviceID);
        pDevice->Attatch(g_thePxiDeviceCommCmdMessage);  //2020-11-07 lijunqing
		m_listDevice.AddTail(pDevice);
		return pDevice;
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Createdevice Failed"));
		return NULL;
	}
}

long CPxiEngine::GetCount(void)
{
	return 0;
}

CPxiDevice* CPxiEngine::GetItem(long nIndex)
{
	return m_listDevice.GetAtIndex(nIndex);
}

long CPxiEngine::ShowSpyWnd(long nShow)
{
	//g_pTheEngineApp->ShowSpyWnd(nShow);

	return 0;
}

long CPxiEngine::ReleaseDevice(const CString &strDeviceID)
{
	// TODO: 在此添加调度处理程序代码

	return 0;
}

long CPxiEngine::ReleaseAllDevice(void)
{
	//g_pTheEngineApp->ReleaseAllDevice();

	return 0;
}

long CPxiEngine::CreateProject(const CString &strProjectFile)
{
// 	CString strFile;
// 	strFile = strProjectFile;
// 	g_pTheEngineApp->CreatePpEngineDatas(strFile);

	return 0;
}

CPxiDevice* CPxiEngine::FindDevice(const CString &strDeviceID)
{
    POS pos = m_listDevice.GetHeadPosition();
    CPxiDevice *p = NULL;
    CPxiDevice *pFind = NULL;

    while (pos != NULL)
    {
        p = (CPxiDevice*)m_listDevice.GetNext(pos);

        if (p->m_pEngineData->m_strID == strDeviceID)
        {
            pFind = p;
            break;
        }
    }

    return pFind;
}

CPxiDevice* CPxiEngine::GetDeviceByIndex(long nIndex)
{
    CPxiDevice *pFind = NULL;

    if (m_listDevice.GetCount() > 0)
    {
        pFind = (CPxiDevice*)m_listDevice.GetAtIndex(nIndex);
    }

    return pFind;
}

void CPxiEngine::UnloadDevice(CPxiDevice *pDevice)
{
    m_listDevice.Remove(pDevice);
}

void CPxiEngine::SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID)
{


}



//2020-11-24  lijunqing
void CPxiEngine::OnEngineDataDeleted(const CString &strDeviceID)
{
    if (g_thePxiDeviceCommCmdMessage == NULL)
    {
        return;
    }

    g_thePxiDeviceCommCmdMessage->OnEngineDataDeleted(strDeviceID);
}
