#include "stdafx.h"
#include "SttNativeTestCtrlCntr.h"
#include "../Engine/SttNativeTestEngine.h"
#include "../../Module/DataMngr/DataMngrTrans.h"

#include "../../../AutoTest/Module/TestControl/SmartTestBaseApp.h"
#include "../../../AutoTest/Module/TestControl/TestControlWnd.h"
#include "../SmartTestInterface/PpSttIotEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString g_strSmartTestRunMode;

CSttNativeTestCltlCntr::CSttNativeTestCltlCntr()
{
    m_pGuideBook->InitAfterRead();
}

CSttNativeTestCltlCntr::~CSttNativeTestCltlCntr()
{

}


//创建通讯规约引擎对象
void CSttNativeTestCltlCntr::CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef)
{
    CString strDeviceID ;

	strDeviceID = m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);

	if (pDevieceRef->m_strID.GetLength() > 0)
	{
		strDeviceID = pDevieceRef->m_strID;
	}

	if (strDeviceID.IsEmpty())
	{
		strDeviceID = GetPathFileNameFromFilePathName(m_pGuideBook->m_strDeviceModelFile);
	}    

    pDevieceRef->m_oPpDevice =  (CXProtocolDevice*)pEngine->CreateDevice(pDevieceRef->m_strPpTemplateFile, pDevieceRef->m_strDeviceModelFile, strDeviceID);

    if (pDevieceRef->m_oPpDevice != NULL )
    {
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		if (pDevieceRef->m_strEngineMode.IsEmpty() || pDevieceRef->m_strEngineMode == STT_CMD_PARA_EngineMode_COM)
		{
			//COM接口，没有SetSttCmdDataFormat
		}
		else
		{
			pDevieceRef->m_oPpDevice->SetSttCmdDataFormat(g_theSmartTestBaseApp->GetXmlRwType());
		}
#endif

#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
#ifndef _PSX_IDE_QT_
		if (m_oCmmConfig.GetCount() > 0)
		{
			CPpsttDevice *pPpsttDevice = (CPpsttDevice*)pDevieceRef->m_oPpDevice;
			pPpsttDevice->m_pPxiDevice->InitCmmConfig(&m_oCmmConfig, FALSE);
		}
#endif
#endif
    }

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CreatePpEngineDevice:%s"), pDevieceRef->m_strID.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("      TemplateFile:%s"), pDevieceRef->m_strPpTemplateFile.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("      DvmFile:%s"), pDevieceRef->m_strDeviceModelFile.GetString());

    //设置录波文件路径
    SetPpEngineRecordFilePath(pDevieceRef->m_oPpDevice);
}

BOOL CSttNativeTestCltlCntr::CreatePpEngineDevice(CCommCmd *pCmd)
{
    if (m_oDeviceRefs.IsAllDeviceConnectSucc())
    {
        return TRUE;
    }

    //如果是多引擎，在此修改  李俊庆-20140918
 /*   CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(m_pGuideBook->m_strPpEngineProgID);

    if (pEngine == NULL)
    {
        //CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoPrtcCpnt/ *L"没有注册规约引擎组件"* /);
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("没有注册规约引擎组件 【%s】"), m_pGuideBook->m_strPpEngineProgID.GetString());
        return FALSE;
    }
*/

    //@@根据设备的ID【IP地址】，创建通讯设备对象
    //strDeviceID : 设备数据模型的ID【IP地址】
	CPpDeviceRef *pPpDeviceRef = NULL;
    pPpDeviceRef = m_oDeviceRefs.GetPpDeviceRefToConnect();
    ASSERT (pPpDeviceRef != NULL);

    CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(pPpDeviceRef->m_strEngineMode, pPpDeviceRef->m_strPpEngineProgID);

    if (pEngine == NULL)
    {
        //CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoPrtcCpnt/*L"没有注册规约引擎组件"*/);
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("没有注册规约引擎组件 【%s】"), pPpDeviceRef->m_strPpEngineProgID.GetString());
        return FALSE;
    }

    try
    {
        if (pPpDeviceRef->m_oPpDevice == NULL)
        {
            //李俊庆  20140918
            CreatePpEngineDevice(pEngine, pPpDeviceRef);
        }
    }
    catch (...)
    {
        return FALSE;
    }

    //if (m_oPpDevice == NULL)
    if (pPpDeviceRef->m_oPpDevice == NULL)
    {
        g_theSmartTestBaseApp->ReleasePpEngine(pPpDeviceRef->m_strPpEngineProgID);//(m_pGuideBook->m_strPpEngineProgID);
        CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CreatPrtcFail/*L"创建规约通讯设备失败"*/);
    }
    else
    {
        try
        {
            ULONG hWnd = (ULONG)m_pTCtrlWnd->GetSafeHwnd();
            pPpDeviceRef->m_oPpDevice->AttachSystemWndMsg(hWnd, WM_ENGINE_SYSTEM_MSG);

            if (pCmd->IsUseConnect())
            {
                DeviceCmmConfig(pPpDeviceRef);
            }
            //Sleep (5000);
        }
        catch(...)
        {
            if (pPpDeviceRef != NULL)
            {
                if (pPpDeviceRef->m_oPpDevice != NULL)
                {
                    pPpDeviceRef->m_oPpDevice = NULL;
                    pPpDeviceRef->SetConnectState(FALSE);
                }
            }
            return FALSE;
        }
    }

	return TRUE;
}

long CSttNativeTestCltlCntr::TestItemSafety(CSafety* pItem)
{
    if (g_nSttLogServerDebugInfor)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, ">> TestItemSafety");
    }

#ifndef _PSX_IDE_QT_
	if (stt_Is_SmartTest_Run_Local())
	{
		return CTestControl::TestItemSafety(pItem);
	}
#endif

    AddReport(pItem, -1, -1);

	//执行初始化脚本
	CString strSyntax;
	pItem->RunInitScriptScript(strSyntax);

    if (pItem->IsSafetyDataModeScript())
    {
        m_pTCtrlWnd->m_pTestItemRef = pItem;
        m_pTCtrlWnd->SetTestTimer(TIMER_EXEC_SAFETY_ITEM, 200);
        return 0;
    }

    CDataGroup oDataGroup;
	//此处Append_Datas，data都是new的，不需要RemoveAll，随着oDataGroup析构释放
    Append_Datas(&oDataGroup, pItem->GetDatas(), FALSE);
	//此处pMsgs直接指向pItem的Msg，指令发送完，需要注意Remove Msgs
    CExBaseList *pMsgs = pItem->GetMsgs();
	CSttMsgs oMsgs;
	oMsgs.AppendEx(*pMsgs, FALSE);

    if (g_nSttLogServerDebugInfor)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, ">> Ats_InputData");
    }

    g_theNativeTestEngine->X_Ats_InputData(NULL, &oDataGroup, &oMsgs);

	return 0;
}

long CSttNativeTestCltlCntr::TestItemSysParaEdit(CSysParaEdit* pItem)
{
#ifndef _PSX_IDE_QT_
	if (stt_Is_SmartTest_Run_Local())
	{
		return CTestControl::TestItemSysParaEdit(pItem);
	}
#endif

	AddReport(pItem, -1, -1); //2017.05.17

    //执行初始化脚本
    CString strSyntax;
    pItem->RunInitScriptScript(strSyntax);

    long nMode = 0;
    pItem->InitDataList(nMode);

    CDataGroup oDataGroup;
    Gb_Append_Datas(&oDataGroup,pItem->GetSysParaEditDataObjList() );
    g_theNativeTestEngine->X_Ats_InputData(NULL, &oDataGroup, NULL);

	return 0;
}

#ifndef _PSX_IDE_QT_
long CSttNativeTestCltlCntr::CreateReportFill(const CString &strRptProgID, BOOL bExportWord)
{
	return CTestControlBase::CreateReportFill(strRptProgID, bExportWord);
}

BOOL CSttNativeTestCltlCntr::OpenWordReportFile(BOOL bExportWord, const CString &strDocFile)
{
	return CTestControlBase::OpenWordReportFile(bExportWord, strDocFile);
}
#endif
