#include "stdafx.h"
#include "DLT860Api.h"
//#include "../61850ClientAPI/61850ClientGlobal.h"
#include "../61850ClientConfig/61850ClientConfig.h"   //ok

#include "../../../Module/System/TickCount32.h"  //ok
#include "../../../Module/GpsPcTime/GpsPcTime.h"   //ok
#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"   //ok
#include "../../../Module/API/FileApi.h"   //ok
#include "DLT860Engine.h"

#include "../MmsApi.h"  //ok
#include "../MmsGlobal.h"  //ok

CDLT860Api *g_oDLT860Api = NULL;
// BOOL g_bMmsEnumLDAfterReadXml = FALSE;
// BOOL g_bMmsEngineDebugMode = FALSE;
int  g_nLogGspDebugString = 1;

#ifdef _PSX_IDE_QT_
#else
#define g_lenLogGloalDest_GSP   1024000
wchar_t g_strLogGloalDestGSP[g_lenLogGloalDest_GSP];
char g_strLogGloalDest_CharGSP[g_lenLogGloalDest_GSP];
#endif

void Global_LogString( const char *strFormat, ...)
{
    if (!g_o61850ClientConfig.m_nUseGspLog)
    {
        return;
    }

#ifdef _PSX_IDE_QT_
    CString strMsg;
    va_list argList;
    va_start( argList, strFormat );
    str_formart_v(strFormat, argList, strMsg);
    va_end( argList );
    CLogPrint::LogString(XLOGLEVEL_INFOR,strMsg);
#else
    memset(g_strLogGloalDest_CharGSP, 0, sizeof(char)*g_lenLogGloalDest_GSP);

    va_list argList;
    va_start( argList, strFormat );
    vsprintf_s( g_strLogGloalDest_CharGSP, g_lenLogGloalDest_GSP, strFormat, argList );
    va_end( argList );
    unsigned char* pTmpStringGBK = NULL;
    int nLenth = 0;
    utf8_to_gbk_r((const unsigned char*)g_strLogGloalDest_CharGSP,strlen(g_strLogGloalDest_CharGSP),&pTmpStringGBK,&nLenth);

    if (nLenth>0)
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,(const char*)pTmpStringGBK);
    }
    else
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,g_strLogGloalDest_CharGSP);
    }

    if (pTmpStringGBK != NULL)
    {
        delete pTmpStringGBK;
    }
#endif




}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _PSX_QT_LINUX_
void* MMSCallBackProc_Data(void* lpParameter)
#else
static DWORD WINAPI MMSCallBackProc_Data(void* lpParameter)
#endif
{
    CFuncParamEx * pFuncParaEx =( CFuncParamEx *)lpParameter;
    g_oDLT860Api->MmsAcsiServerThread_DataProc(pFuncParaEx);

    return(0);
}


/*
void WriteDataAfterWait(CThreadProgressInterface *pThread, long nWaiteTime, const CString &strWriteTitle, const CString &strText)
{
    if (nWaiteTime == 0)
    {
        return;
    }

    if (pThread != NULL)
    {
        CString strWait;
        strWait.Format(_T("%s:%s:等待%d毫秒")
            ,strWriteTitle, strText, nWaiteTime);
        pThread->ShowMsg(strWait);
        pThread->StartTimer(nWaiteTime);
    }

    Sleep(nWaiteTime);

    // 	CGpsPcTimeTickCount oTickCount;
    //
    // 	while (oTickCount.GetTickCountLong(FALSE) <= nWaiteTime)
    // 	{
    // 		Sleep(50);
    // 	}
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CDLT860Api::CDLT860Api(void)
{
    m_pRemoteDevs = NULL;
    m_bExitServeACSIServer = FALSE;
    m_bOnlyReadValue = FALSE;
    m_nLdIndexBack = 0;
    m_bIsAinMinMax = FALSE;
    m_pMmsMsgRcvWnd = NULL;
}

CDLT860Api::~CDLT860Api(void)
{
}

BOOL CDLT860Api::HasUnit(char *pszDsId)
{
    if (strstr(pszDsId, dsParameter) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsAin) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsSetting) != NULL)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL CDLT860Api::HasMinMax(char *pszDsId)
{
    m_bIsAinMinMax = FALSE;

    if (strstr(pszDsId, dsParameter) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsSetting) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsSetGrpNum) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsRelayAin) != NULL)
    {
        m_bIsAinMinMax = TRUE;
        return TRUE;
    }

    if (strstr(pszDsId, dsAin) != NULL)
    {
        m_bIsAinMinMax = TRUE;
        return TRUE;
    }

    return FALSE;
}

BOOL CDLT860Api::HasStepSize(char *pszDsId)
{
    if (strstr(pszDsId, dsParameter) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsSetting) != NULL)
    {
        return TRUE;
    }

    if (strstr(pszDsId, dsSetGrpNum) != NULL)
    {
        return TRUE;
    }

    return FALSE;
}

CRemoteDev* CDLT860Api::GetRemoteDev(const long nDevIndex)
{
    if (m_pRemoteDevs == NULL)
    {
        m_pRemoteDevs = g_o61850ClientConfig.GetRemoteDevs();
    }

    return (CRemoteDev*)m_pRemoteDevs->GetAtIndex(nDevIndex);
}

long CDLT860Api::Client61850_DataOpeProc(CFuncParamEx *pFuncParaEx)
{
    ST_INT i;

    if (!pFuncParaEx->Chck_DevIndex())
        return -1;

    if (pFuncParaEx->m_bHasPostMsg)
    {
        return -1;
    }

    i = pFuncParaEx->get_DevIndex();
    ST_INT nFuncID = pFuncParaEx->get_FuncID();
    ST_RET nRet = SD_SUCCESS;

// 	SOCK_INFO *sock_info = &sock_info_table[pFuncParaEx->get_DevIndex()];
//
// 	if (sock_info != NULL)
// 	{
// 		sock_info->send_error = 0;
// 	}

    switch(nFuncID)
    {
    case FuncID_Link:
        nRet = Client61850_LinkDev(pFuncParaEx);
        break;
    case FuncID_UnLink:
        nRet = Client61850_UnLinkDev(pFuncParaEx);
        break;
    case FuncID_EnumLD:
        nRet = Client61850_EnumLDDir(pFuncParaEx);

        if (nRet == SD_SUCCESS)
        {
            nRet = Client61850_EnumLNDir(pFuncParaEx);
        }

        break;

    case FuncID_EnumLN:
        nRet = Client61850_EnumLNDir(pFuncParaEx);
        break;

    case FuncID_Write:
        nRet = Client61850_WriteData(pFuncParaEx);
        break;
    case FuncID_WriteSingle:
        nRet = Client61850_WriteDataSingle(pFuncParaEx);
        break;
    case FuncID_Read:
        nRet = Client61850_ReadData(pFuncParaEx);
        break;
    case FuncID_ReadOne:
        nRet = Client61850_ReadOneData(pFuncParaEx);
        break;
    case FuncID_Read_SET:
        nRet = Client61850_ReadDataSetting(pFuncParaEx);
        break;

    case FuncID_ReadDir:
        nRet = Client61850_ReadDir(pFuncParaEx);
        break;
    case FuncID_ReadRPC:
        nRet = Client61850_ReadRPC(pFuncParaEx);
        break;

    case FuncID_RpcCall:
        nRet = Client61850_RpcCall(pFuncParaEx);
        break;

    case FuncID_ReadFile:
        nRet = Client61850_ReadFile(pFuncParaEx);
        break;

    case FuncID_StartRpt:
        nRet = Client61850_StartDevRpt(pFuncParaEx);
        break;
    case FuncID_StopRpt:
        nRet = Client61850_StopDevRpt(pFuncParaEx);
        break;
    case FuncID_SetSGNum:
        nRet = Client61850_SetActiveSG(pFuncParaEx);
        break;
    case FuncID_GetSGNum:
        m_nLdIndexBack = pFuncParaEx->get_LDvIndex();

        while (TRUE)
        {
            nRet = Client61850_GetActiveSG(pFuncParaEx);

            if (nRet == SD_SUCCESS)
            {
                break;
            }

            if (!Client61850_GetNextLdZonePara(pFuncParaEx))
            {
                break;
            }
        }

        break;
    case FuncID_SetSENum:
        nRet = Client61850_SetEditSG(pFuncParaEx);
        break;
    case FuncID_CnfSetSE:
        nRet = Client61850_CnfEditSG(pFuncParaEx);
        break;
    case FuncID_CtrlWrite:
        nRet = Client61850_CtrlWrite(pFuncParaEx);
        break;
    case FuncID_CtrlWriteOne:
        nRet = Client61850_CtrlWriteOne(pFuncParaEx);
        break;
    case FuncID_Reset:
        nRet = Client61850_ResetDev(pFuncParaEx);
        break;
// 	case FuncID_ReadJournalCount:
// 		//mms_log_error_infor = 1;
// 		acsi_ctrl_table[i].idleCount = 0;
// 		nRet = MMS_ReadJournalCount(pFuncParaEx);
// 		break;
    case FuncID_ReadJournal:
        nRet = Client61850_ReadJournal(pFuncParaEx);
        break;
    case FuncID_TestProc:
        //mms_log_error_infor = 0;
        nRet = SD_SUCCESS;
        break;
    case FuncID_UploadFile:
        nRet = Client61850_UploadFile(pFuncParaEx);
        break;
    case FuncID_ReadDevice:
        nRet = Client61850__ReadDevice(pFuncParaEx);
        break;

    default:
        nRet = -1;
        break;
    }

    return nRet;
}

/* 装置联机 */
ST_RET CDLT860Api::Client61850_LinkDev(CFuncParamEx *pFuncParaEx)
{
    ST_INT iDvIndex;
    ST_RET ret = SD_FAILURE;
    ACSI_NODE *pDevice;
    char passwd[NAMESIZE];
    memset(passwd, 0, NAMESIZE);

    if (!pFuncParaEx->Chck_DevIndex())
        return ret;

    iDvIndex = pFuncParaEx->get_DevIndex();
    CRemoteDev *pRemoteDev = GetRemoteDev(iDvIndex);

    if (pRemoteDev == NULL)
    {
        return ret;
    }

    pDevice = pRemoteDev->GetAcsiNode();
    mms_ResetRptIndex(pDevice);

    if (g_bMmsEngineDebugMode)
    {
        pDevice->bConnect = TRUE;
        return SD_SUCCESS;
    }

    if (!pRemoteDev->LinkDev())
    {
        return SD_FAILURE;
    }
    else
    {
        pDevice->bConnect = TRUE;
        return SD_SUCCESS;
    }
}

/*   装置断开链接 */
ST_RET CDLT860Api::Client61850_UnLinkDev(CFuncParamEx *pFuncParaEx)
{
    ST_INT iDeviceIndex;//, nMsgIndex;

    if (!pFuncParaEx->Chck_DevIndex())
        return SD_FAILURE;

    iDeviceIndex = pFuncParaEx->get_DevIndex();
    CRemoteDev *pRemoteDev = GetRemoteDev(iDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    if (!pRemoteDev->UnLinkDev())
    {
        return SD_FAILURE;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    pDevice->bConnect = FALSE;
    mms_ResetRptIndex(pDevice);
    return SD_SUCCESS;
}

//装置链接创建的时候调用此线程
ST_RET CDLT860Api::CreateDataProcThread(const long &nDevIndex)
{
    if (m_oFuncParamEx[nDevIndex].m_hThread_Proc_Data==NULL)
    {
        CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDevIndex];

#ifdef _PSX_QT_LINUX_
        pthread_create(&pFuncParaEx->m_hThread_Proc_Data, 0, MMSCallBackProc_Data, (void*)pFuncParaEx);
#else
        HANDLE h = CreateThread(NULL,1024, MMSCallBackProc_Data, pFuncParaEx, 0,NULL);
        pFuncParaEx->m_hThread_Proc_Data = h;
#endif

        //HANDLE h = CreateThread(NULL,1024, MMSCallBackProc_Data, &m_oFuncParamEx[nDevIndex], 0,NULL);
        //m_oFuncParamEx[nDevIndex].m_hThread_Proc_Data = h;

        if (m_oFuncParamEx[nDevIndex].m_hThread_Proc_Data==NULL)
            return SD_FAILURE;
    }

    return SD_SUCCESS;
}

ST_VOID CDLT860Api::MmsAcsiServerThread_DataProc(CFuncParamEx *pFuncParaEx)
{
    ST_INT  nServeACSI0 = 0;
    ST_INT  nServeACSI1 = 0;

    while (TRUE)
    {
        if (m_bExitServeACSIServer)
        {
            break;
        }

        Client61850_DataOpeProc(pFuncParaEx);
        pFuncParaEx->ClearExitFunc();

        Sleep(100);
    }
}

ACSI_NODE* CDLT860Api::GetAcsiNode(const long nDevIndex)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(nDevIndex);

    if (pRemoteDev == NULL)
    {
        return NULL;
    }

    return pRemoteDev->GetAcsiNode();
}

//自动测试模式下，联机之后，枚举设备的逻辑设备，在枚举逻辑设备成功之后，在枚举逻辑设备的其他参数
void CDLT860Api::InitLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bOnlyLink)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return;
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_Link, dsType_NULL, WM_Notify_Msg);
    pParam->set_ServerCmd();

    if (bOnlyLink)
    {
        return;
    }
    else
    {
        m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
    }

    pDevice->nSetRunSGIndexState = 1;

    if (!pDevice->bCanReConnect)
    {
        set_OnlyReadValue(FALSE);
        InitEnumLDFuncPara(nDeviceIndex, FALSE);
    }
}

void CDLT860Api::InitLinkDeviceFuncPara_AutoTest(ST_INT nDeviceIndex, BOOL bOnlyLink)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return;
    }

    if (m_oFuncParamEx[nDeviceIndex].m_hThread_Proc_Data == NULL)
    {
        CreateDataProcThread(nDeviceIndex);
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_Link, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    pParam->set_ClientCmd();

    //此种方式，只有在通讯命令Connect的时候被调用
    if (bOnlyLink)
    {
        return;
    }
    else
    {
        m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
    }

    pDevice->nSetRunSGIndexState = 1;

    if (!pDevice->bCanReConnect)
    {
        set_OnlyReadValue(SD_FALSE);
        InitEnumLDFuncPara(nDeviceIndex, FALSE);
    }
}

void CDLT860Api::InitEnumLDFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    set_OnlyReadValue(SD_FALSE);

    if (bFreeFuncParas)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    if (pDevice->nHasDeviceModel != 1)
    {
        m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLD,   dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    }
    else
    {
        if (g_bMmsEnumLDAfterReadXml)
        {
            m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLD,   dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
        }
    }

    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, FuncID_GetSGNum, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

//控制，压板、遥控、......
void CDLT860Api::InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDaTypeID)
{
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nDsDaTypeID, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}


void CDLT860Api::InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);;
    LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    ST_INT nIndex = 0;
    LD_DATASET_INFO			*pDataInfo = pLD_NODE->DataInfo;

    for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
    {
        if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitCtrlWriteFuncParas(%d, %d, %s)"), nDeviceIndex, nLDIndex, pDataInfo[nIndex].DataSetID);
            CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nIndex,/* m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
        }
    }

    // 	DeleteAllFuncParas();
    // 	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
    //
    // 	CFuncParam *pFuncPara = m_oFuncParams.AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nDsDaTypeID, m_pMainWnd->m_hWnd, WM_Notify_Msg);
}

void CDLT860Api::InitCtrlWriteFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bDeleteAll)
{
    if (bDeleteAll)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nDsIndex, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitWriteFuncParasSingle(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    CFuncParam *pFuncPara = NULL;
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_WriteSingle, nDsIndex, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}


BOOL CDLT860Api::CallFirstFunc(long nDeviceIndex)
{
    CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];
    pFuncParaEx->m_posCurrFuncPara = pFuncParaEx->GetHeadPosition();
    return CallCurrFunc(nDeviceIndex);
}

void CDLT860Api::FireCmdMsg(CFuncParamEx *pFuncParaEx,UINT nCmdID, UINT nCmdIndex)
{
    mms_FireCmdMsg(pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), 0
        ,nCmdID, nCmdIndex);
}

void CDLT860Api::FireCmdMsg_CtrlWrite(DWORD dwFuncParaEx, UINT nCmdIndex)
{
    CFuncParamEx *pFuncParaEx = (CFuncParamEx*)dwFuncParaEx;
    mms_FireCmdMsg(pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), 0
        ,FuncID_CtrlWrite, nCmdIndex);
}

BOOL CDLT860Api::CallCurrFunc(long nDeviceIndex)
{
    CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

    if (pFuncParaEx->m_posCurrFuncPara == NULL)
    {
        pFuncParaEx->set_FuncID(FuncID_TestProc);
        return FALSE;
    }

    CFuncParam *pParam = (CFuncParam*)m_oFuncParamEx[nDeviceIndex].GetAt(pFuncParaEx->m_posCurrFuncPara);

    ValidateCurrFunc(nDeviceIndex);
    m_oFuncParamEx[nDeviceIndex].InitPara(pParam);//memcpy(&m_FuncParam, pParam, sizeof(m_FuncParam));
    pFuncParaEx->set_FuncID(pParam->get_FuncID());
    m_oFuncParamEx[nDeviceIndex].BeginExecDataProc(0);
    return TRUE;
}

BOOL CDLT860Api::CallNextFunc(long nDeviceIndex)
{
    CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

    if (pFuncParaEx->m_posCurrFuncPara == NULL)
    {
        pFuncParaEx->set_FuncID(FuncID_TestProc);
        return FALSE;
    }

    pFuncParaEx->GetNext(pFuncParaEx->m_posCurrFuncPara);
    return CallCurrFunc(nDeviceIndex);
}

void CDLT860Api::ValidateCurrFunc(long nDeviceIndex)
{
    CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

    if (pFuncParaEx->m_posCurrFuncPara == NULL)
    {
        return;
    }

    CFuncParam *pParam = (CFuncParam*)m_oFuncParamEx[nDeviceIndex].GetAt(pFuncParaEx->m_posCurrFuncPara);

    if (pParam->get_FuncID() == FuncID_GetSGNum || pParam->get_FuncID() == FuncID_SetSGNum)
    {
        ValidateCurrFunc_ReadZone(pParam);
    }
}

void CDLT860Api::ValidateCurrFunc_ReadZone(CFuncParam *pParam)
{
    ST_INT nDvIndex = pParam->get_DevIndex();
    ST_INT nLdIndex = pParam->get_LDvIndex();

    if (nLdIndex != -1)
    {//验证当前的数据集是不是保护
        ACSI_NODE *pDevice = GetAcsiNode(nDvIndex);
        ASSERT(pDevice != NULL);
        LD_NODE   *pLD = &(pDevice->LD[nLdIndex]);

        if (pLD != NULL)
        {
            if (mms_IsSettingsDS(pLD/*->LDName*/))
            {
                return;
            }
        }
    }

    nLdIndex = -1;
    ACSI_NODE *pDevice = GetAcsiNode(nDvIndex);

    if (pDevice != NULL)
    {
        ST_INT nIndex = 0;

        for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
        {
            if (mms_IsSettingsDS(&pDevice->LD[nIndex]/*.LDName*/))
            {
                nLdIndex = nIndex;
                break;
            }
        }
    }

    if (nLdIndex == -1)
    {
        nLdIndex = mms_FindLDeviceIndex(nDvIndex, "prot");//zhowTest20180111

        if (nLdIndex == -1)
        {
            nLdIndex = mms_FindLDeviceIndex(nDvIndex, "pqld");//zhowTest20180111
        }

        if (nLdIndex == -1)
        {
            nLdIndex =  mms_FindLDeviceIndex(nDvIndex, "rcd");
        }
    }

    pParam->set_LDvIndex(nLdIndex);
}

/*  销毁网络监控线程 */
ST_RET CDLT860Api::DestroyDataProcThread()
{
    m_bExitServeACSIServer = TRUE;

// 	CTickCount32 oTickCount;
// 	oTickCount.DoEvents(5000);

    for (int nIndex = 0;nIndex<MAX_DEVICE;nIndex++)
    {
        if (m_oFuncParamEx[nIndex].m_hThread_Proc_Data)
        {
#ifndef _PSX_QT_LINUX_
            CloseHandle(m_oFuncParamEx[nIndex].m_hThread_Proc_Data);
#endif

            m_oFuncParamEx[nIndex].m_hThread_Proc_Data = NULL;
        }
    }

    return SD_SUCCESS;
}

BOOL CDLT860Api::IsInFuncsCallState(long nDeviceIndex)
{
    CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

    return (pFuncParaEx->m_posCurrFuncPara != NULL);
}

/*  枚举所有装置的逻辑节点目录 */
ST_RET CDLT860Api::Client61850_EnumLDDir(CFuncParamEx *pFuncParaEx)
{
    ST_INT ret;
    ST_INT i;
    ST_INT j;
    ST_INT k;
    ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    if (!pRemoteDev->GetServerDirectory())
    {
        return SD_FAILURE;
    }

    if (!pRemoteDev->GetAllDatasets())
    {
        return SD_FAILURE;
    }

    return SD_SUCCESS;
}

ST_RET CDLT860Api::Client61850_EnumLNDir(CFuncParamEx *pFuncParaEx)
{
    ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    if (!pRemoteDev->GetLogicDeviceDirectory())
    {
        return SD_FAILURE;
    }

//	if (!g_bMultDevModel)
// 	{
// 		Get_Nodes_Detail(nDeviceIndex);
// 	}

    CLogPrint::LogString(XLOGLEVEL_TRACE, "EnumLNDir  Finished");

    return SD_SUCCESS;
}

/*  获取当前定值运行区&定值区数 */
ST_RET CDLT860Api::Client61850_GetActiveSG(CFuncParamEx *pFuncParaEx)
{
    ST_INT nSGID = 0;
    ST_INT nSGNum = 0;
    ST_INT ret = SD_FAILURE;

    ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
    ST_INT nLdIndex = pFuncParaEx->get_LDvIndex();
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if ((nLdIndex == -1)||(pRemoteDev == NULL))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("*****************没有定值区相关的逻辑设备*****************"));//_T("*****************没有定值区相关的逻辑设备*****************"));
        return SD_SUCCESS;
    }

    if (!pFuncParaEx->Chck_DevIndex())
        return SD_FAILURE;

    if (pRemoteDev->GetActiveSG(nLdIndex))
    {
        ACSI_NODE *pAcsiNode = pRemoteDev->GetAcsiNode();
        pFuncParaEx->set_SGID(pAcsiNode->nRunSGIndex);
        pFuncParaEx->set_SGNum(pAcsiNode->nSGNum);
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前运行定值区(%d),获取到的定值区总数(%d)."),pAcsiNode->nRunSGIndex,pAcsiNode->nSGNum);
        ret = SD_SUCCESS;
    }

    return ret;
}

ST_RET CDLT860Api::Client61850_SetActiveSG(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("设置当前激活定制区失败,请确认数据集路径是否正确."));
        return SD_FAILURE;
    }

    ST_INT ret = SD_FAILURE;
    ST_INT nLdIndex = pFuncParaEx->get_LDvIndex();
    ST_INT nSG = pFuncParaEx->get_SGID();

    if (!mms_IsSettingsDS(pLD/*->LDName*/))
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("逻辑设备【%s】无定值区号."),pLD->LDName);
        return ret;
    }



    if (pDevice->nEditSGIndex != 0)
    {
        if (!pRemoteDev->SetEditSG(pFuncParaEx->get_LDvIndex(),0))
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                ,_T("切换编辑区到0区失败."));
        }
        else
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , _T("切换编辑区到0区成功"));
        }

        pDevice->nEditSGIndex = 0;
        Sleep(1000);
    }

    FireCmdMsg(pFuncParaEx,FuncID_SetSGNum, 0);
    CGpsPcTimeTickCount  oTickCount32;

    if (pRemoteDev->SetActiveSG(nLdIndex,nSG))
    {
        ret = SD_SUCCESS;
    }

    pDevice->tmSetSG = oTickCount32.GetTickCountLong();
    pDevice->tmTotal += pDevice->tmSetSG;
    FireCmdMsg(pFuncParaEx,FuncID_SetSGNum, 1);

    return ret;
}

ST_RET CDLT860Api::Client61850_StartDevRpt(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("启动报告失败,请确认报告数据集路径是否正确."));//_T("启动报告失败，请确认装置规约是否正确"));
        return SD_FAILURE;
    }

    ST_CHAR rcbItem[NAMESIZE];
    ST_INT nDsIndex, nRCB_Index;
    *rcbItem = 0;

    nDsIndex = pFuncParaEx->get_DSID();

    if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("启动报告失败，请确认装置规约是否正确"));//_T("启动报告失败，请确认装置规约是否正确"));
        return SD_FAILURE;
    }

    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

    if (pLD_INFO->numRcb <= 0)
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("启动报告：不存在报告控制块"));//_T("启动报告：不存在报告控制块"));
        return SD_SUCCESS;
    }

    if (0 < pLD_INFO->curRcbIndex && pLD_INFO->curRcbIndex <= pLD_INFO->numRcb)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("启动报告：报告控制块【%s】已经启动"),pLD_INFO->RCB[pLD_INFO->curRcbIndex-1].rcbName);
        return SD_SUCCESS;
    }

    pLD_INFO->curRcbIndex = 0;

    ST_BOOLEAN bStartRpt = SD_FALSE;
    int nBrcbIndex = pFuncParaEx->get_BrcbIndex();

    if ((nBrcbIndex<0)||(nBrcbIndex>=pLD_INFO->numRcb))
    {
        nBrcbIndex = pFuncParaEx->m_nConnDevIndex;

        if ((nBrcbIndex<0)||(nBrcbIndex>=pLD_INFO->numRcb))
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告控制块号【%d】越限."),nBrcbIndex);//
            return SD_FAILURE;
        }
    }

    BOOL bRptEna=SD_FALSE;
    CString strRptName;

    for (int i=nBrcbIndex; i<pLD_INFO->numRcb; i++)
    {
        strRptName = GlobalGetRptLogCBString_GSP(pLD_INFO->RCB[i].rcbName);
        strcpy(rcbItem,strRptName.GetString());

        if (pRemoteDev->GetRCBEnableState(pLD->LDName,rcbItem, bRptEna))//判断该报告号是否已经被启动过
        {
            if (!bRptEna)
            {
                nRCB_Index = i;
                bStartRpt = SD_TRUE;
                break;
            }
        }

        Sleep(100);
    }

    BOOL bRet = FALSE;

    // 启动报告
    if (bStartRpt==SD_TRUE)
    {
        CRemoteDevs *pRemoteDevs = g_o61850ClientConfig.GetRemoteDevs();
        BOOL bBufferReport = ((strstr(rcbItem,"$BR$")!=NULL)||(strstr(rcbItem,".brcb")!=NULL));

        if (bBufferReport)
        {
            bRet = pRemoteDev->SetBRCBValues(&pLD_INFO->RCB[nRCB_Index],pLD->LDName,rcbItem,pRemoteDevs->m_nOptFlds_BR,pRemoteDevs->m_nTrgOps_UI,pFuncParaEx->get_RptGI(),
                pRemoteDevs->m_nUseEntryidUpdate);
        }
        else
        {
            bRet = pRemoteDev->SetURCBValues(&pLD_INFO->RCB[nRCB_Index],pLD->LDName,rcbItem,pRemoteDevs->m_nOptFlds_RP,pRemoteDevs->m_nTrgOps_UI,pFuncParaEx->get_RptGI());
        }

        if (bRet)
        {
            pLD_INFO->curRcbIndex = nRCB_Index + 1;
        }
    }

    CString str_rcbItem;
    str_rcbItem = (char*)rcbItem;

    if (bStartRpt)
    {
        if (bRet)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("启动报告[%s]完成"), str_rcbItem.GetString());
            mms_UpdateDatasetState(pLD_INFO);
        }
        else
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("启动报告[%s]失败"), str_rcbItem.GetString());
        }
    }
    else
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("启动报告[%s]失败"), str_rcbItem.GetString());
    }

    if (bRet)
        return SD_SUCCESS;
    else
        return SD_FAILURE;
}

ST_RET CDLT860Api::Client61850_StopDevRpt(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("停止报告失败,请确认报告数据集路径是否正确."));
        return SD_FAILURE;
    }

    ST_INT ret = SD_FAILURE;
    ST_CHAR rcbItem[NAMESIZE];
    ST_INT nDsIndex = pFuncParaEx->get_DSID();

    if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
        return SD_FAILURE;

    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

    if (pLD_INFO->numRcb < 0)
        return SD_SUCCESS;

    ST_BOOLEAN bStartRpt = SD_FALSE;
    CString strRptName;

    if (pLD_INFO->curRcbIndex <= pLD_INFO->numRcb && pLD_INFO->curRcbIndex > 0)
    {
        strRptName = GlobalGetRptLogCBString_GSP(pLD_INFO->RCB[pLD_INFO->curRcbIndex-1].rcbName);
        strcpy(rcbItem,strRptName.GetString());
    }
    else
    {
        pLD_INFO->curRcbIndex = 0;
        return SD_SUCCESS;
    }

    if (pRemoteDev->StopReport(pLD->LDName,rcbItem))
    {
        pLD_INFO->curRcbIndex = 0;
        ret = SD_SUCCESS;
    }

    mms_UpdateDatasetState(pLD_INFO);
    return ret;
}

ST_INT CDLT860Api::get_DataSetNum(LD_NODE *pLD, ST_INT nDsIndex)
{
    ST_INT nDataSetNum = 0;

    if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
        return nDataSetNum;

    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

    return pLD_INFO->numData;
}

ST_RET CDLT860Api::Client61850_ResetDev(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("当前设备编号%d不存在,装置复归失败."),pFuncParaEx->get_DevIndex());
        return SD_FAILURE;
    }

    if (!pRemoteDev->ResetDev())
    {
        return SD_FAILURE;
    }

    return SD_SUCCESS;
}

ST_RET CDLT860Api::Client61850_ReadJournal(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("当前设备编号%d不存在,读取日志失败."),pFuncParaEx->get_DevIndex());
        return SD_FAILURE;
    }

    long long int nStartEntry = pFuncParaEx->get_start_entry();
    DWORD dw_start_entry = 0;
    ST_CHAR sz_vmd_spec[NAMESIZE], *pszLogRef = NULL;
    ST_UCHAR start_entry[10] = {""},entry_id[10] = {""};
    tagEVENTTIME tmEvent;
    ST_UCHAR *pRptData = NULL;
    tagDA *pDA = NULL,*pNewDA =NULL;


    char *pszItemID = pFuncParaEx->get_journal_ref();
    long nldIndex = pFuncParaEx->get_LDvIndex();

    if (!pRemoteDev->ReadJournal(nStartEntry,pszItemID,nldIndex))
    {
        return SD_FAILURE;
    }

    return SD_SUCCESS;
}

ST_RET CDLT860Api::Client61850__ReadDevice(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("当前设备编号%d不存在,ReadDevice失败."),pFuncParaEx->get_DevIndex());
        return SD_FAILURE;
    }

    ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
    ACSI_NODE* pDevice =  pRemoteDev->GetAcsiNode();
    LD_DATASET_INFO *pLD_INFO = NULL;
    CString strTitle;
    long nLDIndex = 0;
    long nLdCount = pDevice->numLD;
    BOOL bHasMinMax = FALSE;
    ST_INT ret = SD_SUCCESS;
    ST_INT nDaNum = 0;
    tagDA *pDA=NULL;

    for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
    {
        LD_NODE *pLD = &pDevice->LD[nLDIndex];

        for (int i=0;i<pLD->numDaSet;i++)
        {
            pLD_INFO = &pLD->DataInfo[i];
            nDaNum = pLD_INFO->numData;

            if ((m_pProgressInterface != NULL))
            {
                strTitle.Format(_T("设备%d - 逻辑设备%d - %s - 第%d个数据集, 共%d个")
                    ,nDeviceIndex + 1, nLDIndex + 1, _T("读数据"),i+1,pLD->numDaSet);
                m_pProgressInterface->SetTitle(strTitle);
                m_pProgressInterface->SetMaxRange(nDaNum);
            }

            for (ST_INT k=0; k<nDaNum; k++)
            {
                if ((m_pProgressInterface != NULL))
                {
                    m_pProgressInterface->StepIt();
                    CString strMsg;
                    strMsg.Format(_T("第%d个  共%d个"), k+1, nDaNum);//
                    m_pProgressInterface->ShowMsg(strMsg);
                }

                bHasMinMax = HasMinMax(pLD_INFO->DataSetID);
                pDA = get_MMStagDAObj(pLD_INFO,k);

                if (pDA == NULL)
                    continue;

                if (node_get_tagDAData(pLD, pDA)!=SD_SUCCESS)
                {
                    continue;
                }

                pRemoteDev->node_get_DataDescInfo(pLD, pDA);

                if ((strstr(pLD_INFO->DataSetID,_T("Setting"))!=NULL)||(strstr(pLD_INFO->DataSetID,_T("Ena"))!=NULL))//对于定值或压板数据集,去读取实际结果数据
                {
                    if (!pRemoteDev->ReadValue(pLD->LDName, pDA))
                    {
                        continue;
                    }
                }

                if (bHasMinMax)
                {
                    pRemoteDev->node_get_DataLimitValInfoAll(pLD, pDA);
                }
            }

            pLD_INFO->bHasEnum = TRUE;
        }

        pRemoteDev->InitRptLogCB_Struct(pLD);
        pRemoteDev->GetRptLogCB_GetAllCBValues(pLD,GSP_ACSIClass_brcb);
        pRemoteDev->GetRptLogCB_GetAllCBValues(pLD,GSP_ACSIClass_urcb);
        pRemoteDev->GetRptLogCB_GetAllCBValues(pLD,GSP_ACSIClass_lcb);
    }

    return SD_SUCCESS;
}

ST_RET CDLT860Api::Client61850_UploadFile(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("当前设备编号%d不存在,下装文件失败."),pFuncParaEx->get_DevIndex());
        return SD_FAILURE;
    }

    CString strDevPath,strLocalFile;
    strDevPath = pFuncParaEx->get_Path();
    strLocalFile = pFuncParaEx->get_FileName();

    if (!IsFileExist(strLocalFile))
    {
        CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "文件路径 %s 不存在;",strLocalFile.GetString());
        return SD_FAILURE;
    }

    if (!pRemoteDev->SetFile(strLocalFile,strDevPath))
    {
        return SD_FAILURE;
    }

    return SD_SUCCESS;
}

ST_RET CDLT860Api::Client61850_CtrlWriteOne(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pAcsiNode = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pAcsiNode,&pLD))
    {
        if (pRemoteDev != NULL)
        {
            ACSI_NODE* pDevice = pRemoteDev->GetAcsiNode();
            sprintf(pDevice->InfoSel
                , _T("修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】")
                , pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
            sprintf(pDevice->InfoExec
                , _T("修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】")
                , pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex2());
        }

        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CtrlWrite失败,查找逻辑设备失败."));
        return SD_FAILURE;
    }

    ST_INT nDsIndex=0, nDaIndex1=0, nDaIndex2=0;
    tagDA *pDA, *pDA2;
    ST_INT nRet = 0;
    ST_INT nACSI;
    int i = 0;
    int nWriteCount = 0;
    CString strText;
    int nWriteIndex = 0;

    nACSI = pFuncParaEx->get_DevIndex();
    nDsIndex = pFuncParaEx->get_DSID();
    nDaIndex1 = pFuncParaEx->get_DaIndex1();
    nDaIndex2 = pFuncParaEx->get_DaIndex2();

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->SetMaxRange(1);
    }

    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    pDA = get_MMStagDAObj(pLD_INFO, nDaIndex1);
    pDA2 = get_MMStagDAObj(pLD_INFO, nDaIndex2);

    long nCtrlType = g_o61850ClientConfig.GetCtrlType();
    ST_INT iValue, iValue2, nTDelayAfterSel;
    iValue = pFuncParaEx->get_DaValue1();
    iValue2 = pFuncParaEx->get_DaValue2();
    nTDelayAfterSel = pFuncParaEx->get_TDelayAfterSel();

    nRet = pRemoteDev->CtrlWriteDA_SWV_Oper(pLD->LDName,pDA,pDA2,iValue,iValue2,nTDelayAfterSel,FireCmdMsg_CtrlWrite,(DWORD)pFuncParaEx);

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->StepIt();
    }

    if (nRet == 0)
    {
        return SD_FAILURE;
    }

    return SD_SUCCESS;
}
ST_RET CDLT860Api::Client61850_CtrlWrite(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pAcsiNode = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pAcsiNode,&pLD))
    {
        if (pRemoteDev != NULL)
        {
            ACSI_NODE* pDevice = pRemoteDev->GetAcsiNode();
            sprintf(pDevice->InfoSel
                , _T("修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】")
                , pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
            sprintf(pDevice->InfoExec
                , _T("修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】")
                , pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex2());
        }

        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CtrlWrite失败,查找逻辑设备失败."));
        return SD_FAILURE;
    }

    ST_INT nDataNum = 0;
    ST_INT nDsIndex;
    tagDA *pDA;
    tagDA tagData;
    ST_INT nRet = 0;
    ST_INT nACSI;
    int i = 0;
    int nWriteCount = 0;
    CString strText;
    int nWriteIndex = 0;
    long nWriteFailedCount = 0;
    CGpsPcTimeTickCount  oTickCount32;
    CString strValue;
    CString strName;
    ZeroMemory(&tagData, sizeof(tagData));
    nACSI = pFuncParaEx->get_DevIndex();
    nDsIndex = pFuncParaEx->get_DSID();
    nDataNum = get_DataSetNum(pLD,nDsIndex);
    pAcsiNode->nWriteErrorCount = 0;

    for ( i=0; i<nDataNum; i++)
    {
        LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
        pDA = get_MMStagDAObj(pLD_INFO,i);

        if (!pDA->bModify)
            continue;

        nWriteCount++;
    }

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->SetMaxRange(nWriteCount);
    }

    for ( i=0; i<nDataNum; i++)
    {
        if (pFuncParaEx->NeedExitFunc())
        {
            break;
        }

        LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
        pDA = get_MMStagDAObj(pLD_INFO,i);

        if (!pDA->bModify)
            continue;

        strValue = mms_GetDAValue(pDA);
        strName=mms_GetDADesc(pDA);

        if (strName.GetLength() < 2)
        {
#ifdef _use_mms_string
            strName = mms_string(&pDA->DAValue.mmsName);
#else
            strName = pDA->DAValue.mmsName;
#endif
        }
#ifdef _mms_api_rw_use_critic_section_
        CAutoSimpleLock oLock(m_oMmsRWCriticSection);
#endif

        if (m_pProgressInterface != NULL)
        {
            strText.Format(_T("第%d，共%d 【%s】=【%s】")
                , nWriteIndex + 1, nWriteCount, strName.GetString(), strValue.GetString());
            m_pProgressInterface->ShowMsg(strText);
        }

        nWriteIndex++;

        if (g_o61850ClientConfig.m_nEnaReadBeforeWrite == 1)
        {//读取压板的状态数值
            mms_ReleaseData(&tagData);
            mms_CopyData(pDA, &tagData, FALSE);

            CString strDataSetName;
            strDataSetName = pLD_INFO->DataSetID;

            // 2012-12-17  读取装置数据进行比较
            if (strDataSetName.Find("$dsDout") != -1)//zhouhj 20190107 对于控制类的信号做特殊处理
            {
            }
            else if (pRemoteDev->ReadValue(pLD->LDName, &tagData))
            {
                if (CompareData(pDA, &tagData)==SD_TRUE)
                {
                    mms_ReleaseData(&tagData);

                    pDA->bModify = SD_FALSE;

                    if (m_pProgressInterface != NULL)
                    {
                        m_pProgressInterface->StepIt();
                    }

#ifdef _mms_api_rw_use_critic_section_
                    oLock.Free();
#endif

                    continue;
                }
            }

            mms_ReleaseData(&tagData);
        }


        // 控制写数据
        oTickCount32.Enter();
        long nCtrlType = g_o61850ClientConfig.GetCtrlType();

        if (nCtrlType == DLT_WRITE_CTRL_TYPE_DIRECT)
        {
            nRet = pRemoteDev->CtrlWriteDA_Direct(pLD->LDName,pDA);
        }
        else if (nCtrlType == DLT_WRITE_CTRL_TYPE_SBO)
        {
            nRet = pRemoteDev->CtrlWriteDA_SBO_Oper(pLD->LDName,pDA,FireCmdMsg_CtrlWrite,(DWORD)pFuncParaEx);
        }
        else
            nRet = pRemoteDev->CtrlWriteDA_SWV_Oper(pLD->LDName,pDA,FireCmdMsg_CtrlWrite,(DWORD)pFuncParaEx);


        if (nRet)
        {
            pDA->bModify = SD_FALSE;

            if (m_pProgressInterface != NULL)
            {
                m_pProgressInterface->StepIt();
            }
        }
        else
        {
            pDA->bModify = SD_FALSE;
            pAcsiNode->nWriteErrorCount++;
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , "压板操作【%s】【%s】=【%s】失败. "
                , pLD->LDName, strName.GetString(), strValue.GetString());
            nWriteFailedCount++;
        }

#ifdef _mms_api_rw_use_critic_section_
        oLock.Free();
#endif


        WriteDataAfterWait(m_pProgressInterface, g_o61850ClientConfig.m_nWriteDataWaitMs, strText, _T("下一个压板修改前："));//_T("下一个压板修改前："));
        // 读装置的数据进行比较
    }

    if (nWriteFailedCount == 0)
    {
        return SD_SUCCESS;
    }
    else
    {
        return SD_FAILURE;
    }
}

ST_RET CDLT860Api::Client61850_CnfEditSG(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        return SD_FAILURE;
    }

    ST_BOOLEAN bCnf = SD_TRUE;
    ST_RET ret = SD_FAILURE;

    if (!pFuncParaEx->Chck_DevIndex())
        return ret;

    CGpsPcTimeTickCount  oTickCount32;
    FireCmdMsg(pFuncParaEx,FuncID_CnfSetSE, 0);

    if (!pRemoteDev->ConfirmEditSGValues(pLD->LDName))
    {
        sprintf(pDevice->InfoExec, _T("固化定值区【%d】失败."), pFuncParaEx->get_SEID());
        CLogPrint::LogString(XLOGLEVEL_TRACE, pDevice->InfoExec);
        ret = SD_FAILURE;
    }
    else
    {
        sprintf(pDevice->InfoExec, _T("固化定值区【%d】成功"),pFuncParaEx->get_SEID());
        ret = SD_SUCCESS;
    }

    pDevice->tmExec = oTickCount32.GetTickCountLong(TRUE);
    FireCmdMsg(pFuncParaEx,FuncID_CnfSetSE, 1);
    pDevice->tmTotal += pDevice->tmExec;
    return ret;
}

ST_RET CDLT860Api::Client61850_SetEditSG(CFuncParamEx *pFuncParaEx)
{
    ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
    ST_INT ret = SD_FAILURE;
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if ((!pFuncParaEx->Chck_DevIndex())||(pRemoteDev == NULL))
        return ret;

    ST_INT nLdIndex = pFuncParaEx->get_LDvIndex();
    ST_INT nSE = pFuncParaEx->get_SEID();

    if (!pRemoteDev->HasReadSettingZone())
    {
        long nLdIndex = pFuncParaEx->get_LDvIndex();
        pRemoteDev->GetActiveSG(nLdIndex);
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    LD_NODE   *pLD = &(pDevice->LD[nLdIndex]);

    if (!mms_IsSettingsDS(pLD/*->LDName*/))
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("逻辑设备【%s】无定值区号."),pLD->LDName);
        return ret;
    }

    FireCmdMsg(pFuncParaEx,FuncID_SetSENum, 0);
    CGpsPcTimeTickCount  oTickCount32;

    if (pRemoteDev->SetEditSG(nLdIndex,nSE))
    {
        ret = SD_SUCCESS;
    }

    pDevice->tmSetSG = oTickCount32.GetTickCountLong();
    pDevice->tmTotal += pDevice->tmSetSG;
    FireCmdMsg(pFuncParaEx,FuncID_SetSENum, 1);
    return ret;
}

tagDA* CDLT860Api::get_MMStagDAObj(LD_DATASET_INFO *pLD_INFO,ST_INT index)
{
    if (pLD_INFO == NULL)
    {
        return NULL;
    }

    if ((pLD_INFO->numData <= index)||(index<0))
    {
        return NULL;
    }

    return &pLD_INFO->DataSet[index];
}

BOOL CDLT860Api::CheckCurSelIsSetting(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return FALSE;
    }

    LD_NODE *pLD = pRemoteDev->GetLdNode(nLDIndex);

    if (pLD == NULL)
    {
        return FALSE;
    }

    if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
        return FALSE;

    CStringA strText(pLD->LDName);
    //if (strText.Find(_T("PROT"))!=-1)

    //兼容测控Ctrl下有定值：2017-11-2
    //if (mms_IsSettingsDS(strText))
    {
        LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
        CStringA str(pLD_INFO->DataSetID);

        if (str.Find("Setting")!=-1)
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CDLT860Api::CheckCurSelIsParameter(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return FALSE;
    }

    LD_NODE *pLD = pRemoteDev->GetLdNode(nLDIndex);

    if (pLD == NULL)
    {
        return FALSE;
    }

    if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
        return FALSE;

    CStringA strText(pLD->LDName);
    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    CStringA str(pLD_INFO->DataSetID);

    if (str.Find("Parameter")!=-1)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL CDLT860Api::CheckCurSelIsDout(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return FALSE;
    }

    LD_NODE *pLD = pRemoteDev->GetLdNode(nLDIndex);

    if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
        return FALSE;

    CStringA strText(pLD->LDName);

    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    CStringA str(pLD_INFO->DataSetID);

    if (str.Find(key_dsDout) != -1)
    {
        return TRUE;
    }

    str.MakeUpper();
    if (str.Find(key_dsGOOSE) != -1)
    {
        return TRUE;
    }

    return FALSE;
}

ST_RET CDLT860Api::Client61850_ReadFile(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    CGpsPcTimeTickCount  oTickCount32;
    oTickCount32.Enter();

    if (!pRemoteDev->ReadFile(pFuncParaEx->get_FileName(),pFuncParaEx->get_Path()))
    {
        return SD_FAILURE;
    }

    pDevice->tmTotal = oTickCount32.GetTickCountLong();
    return SD_SUCCESS;
}

ST_RET CDLT860Api::Client61850_ReadDir(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    CGpsPcTimeTickCount  oTickCount32;
    oTickCount32.Enter();

    if (pRemoteDev->GetAllDir(pFuncParaEx->get_Path(),pFuncParaEx->get_DaIndex2()))
    {
        pDevice->tmTotal = oTickCount32.GetTickCountLong();
        return SD_SUCCESS;
    }
    else
    {
        return SD_FAILURE;
    }
}

ST_RET CDLT860Api::Client61850_ReadRPC(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    CGpsPcTimeTickCount  oTickCount32;
    oTickCount32.Enter();

    if (pRemoteDev->GetRpcInterfaceDirectory())
    {
        pDevice->tmTotal = oTickCount32.GetTickCountLong();
        return SD_SUCCESS;
    }
    else
    {
        return SD_FAILURE;
    }
}

ST_RET CDLT860Api::Client61850_RpcCall(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (pRemoteDev == NULL)
    {
        return SD_FAILURE;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    CString strParaFunction,strParaCallName,strParaCallID;
    strParaFunction = pFuncParaEx->get_Path();
    strParaCallName = pFuncParaEx->get_FileName();
    strParaCallID = pFuncParaEx->get_vmd_spec();
    long nVersion = pFuncParaEx->get_DaIndex1();
    long nTimeout = pFuncParaEx->get_DaIndex2();
    long nRequestType = pFuncParaEx->get_DaValue1();
    long nResponseType = pFuncParaEx->get_DaValue2();
    CGpsPcTimeTickCount  oTickCount32;
    oTickCount32.Enter();

    if (pRemoteDev->RpcCall(strParaFunction,strParaCallName,strParaCallID,nVersion,nTimeout,nRequestType,nResponseType))
    {
        pDevice->tmTotal = oTickCount32.GetTickCountLong();
        return SD_SUCCESS;
    }
    else
    {
        return SD_FAILURE;
    }
}

ST_RET CDLT860Api::Client61850_ReadDataSetting(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("读取当前定值数据集失败,请确认数据集路径是否正确."));
        return SD_FAILURE;
    }

    if (!pRemoteDev->HasReadSettingZone())
    {
        long nLdIndex = pFuncParaEx->get_LDvIndex();
        pRemoteDev->GetActiveSG(nLdIndex);
    }

    ST_INT ret = SD_SUCCESS;
    ST_INT nDaNum = 0;
    tagDA *pDA=NULL;
    ST_INT nDsIndex;
    CGpsPcTimeTickCount  oTickCount32;
//	CTickCount32 oTickCountUse;
    nDsIndex = pFuncParaEx->get_DSID();
    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    nDaNum = pLD_INFO->numData;

    //不是定值数据集
    //if (_stricmp(dsSetting, pLD_INFO->DataSetID) != 0)
    if (strstr(pLD_INFO->DataSetID, dsSetting) == NULL)
        return SD_FAILURE;

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->SetMaxRange(nDaNum);
    }

    ST_INT nSG = pFuncParaEx->get_SGID();
    ST_INT nSE = pFuncParaEx->get_SEID();

    if (nSE == 0)
    {
        nSE = nSG;
    }

    if (pDevice->nEditSGIndex != nSE)
    {
        if (!pRemoteDev->SetEditSG(pFuncParaEx->get_LDvIndex(),nSE))
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                ,_T("读定值区%d时，切换编辑区失败【运行区=%d】")
                , nSE, nSG);
        }
        else
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , _T("读定值区%d时，切换编辑区【运行区=%d】")
                , nSE, nSG);
//			bSE = TRUE;
        }

        if (m_pProgressInterface != NULL)
        {
            m_pProgressInterface->ShowMsg(_T("Wait 1000 ms"));
            m_pProgressInterface->StartTimer(1000);
        }

        Sleep(1000);
    }

    for (int nDataIndex=0; nDataIndex<nDaNum; nDataIndex++)
    {
        if (pFuncParaEx->NeedExitFunc())
        {
            break;
        }

        if (m_pProgressInterface != NULL)
        {
            m_pProgressInterface->StepIt();
            CString strMsg;
            strMsg.Format(_T("第%d个  共%d个"), nDataIndex+1, nDaNum);
            m_pProgressInterface->ShowMsg(strMsg);
        }

        pDA = get_MMStagDAObj(pLD_INFO,nDataIndex);

        if (pDA == NULL)
            continue;

        oTickCount32.Enter();

        if (!pRemoteDev->ReadSEValue(pLD->LDName, pDA))
        {
            ret = SD_FAILURE;
        }

        pDevice->tmTotal += oTickCount32.GetTickCountLong(TRUE);
//		oTickCountUse.DoEvents(100);

        if (ret != SD_SUCCESS)
        {
            break;
        }
    }

    return ret;
}

BOOL CDLT860Api::GetAcsiiLD_Node(CFuncParamEx *pFuncParaEx,CRemoteDev **ppRemoteDev,ACSI_NODE **ppDevice,LD_NODE **ppLD)
{
    *ppRemoteDev = GetRemoteDev(pFuncParaEx->get_DevIndex());

    if (*ppRemoteDev == NULL)
    {
        return FALSE;
    }

    *ppLD = (*ppRemoteDev)->GetLdNode(pFuncParaEx->get_LDvIndex());

    if (*ppLD == NULL)
    {
        return FALSE;
    }

    *ppDevice = (*ppRemoteDev)->GetAcsiNode();
    return TRUE;
}

ST_RET CDLT860Api::Client61850_WriteData(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        return SD_FAILURE;
    }

    ST_INT k;
    ST_INT nDaNum = 0;
    ST_INT nDsIndex;
    ST_RET ret = SD_FAILURE;
    tagDA *pDA;
    ST_INT nError = 0;

    CGpsPcTimeTickCount  oTickCount32;
    oTickCount32.Enter();
    Sleep(50);
    nDsIndex = pFuncParaEx->get_DSID();
    pDevice->nWriteErrorCount = 0;
    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    nDaNum = pLD_INFO->numData;
    pDevice->InfoWriteData[0] = 0;

    for (k=0; k<nDaNum; k++)
    {
        if (pFuncParaEx->NeedExitFunc())
        {
            break;
        }

        pDA = get_MMStagDAObj(pLD_INFO,k);

        if (pDA==NULL)
            continue;

        if (!pDA->bModify)
            continue;

        if (!pRemoteDev->WriteSEValue(pLD->LDName,pDA))
        {
            nError++;
            CString strInfor;
            long nCurrLen = strlen(pDevice->InfoWriteData);
            strInfor.Format(_T("写数据【%s】【%s】=【%s】失败."), mms_GetDADesc(pDA).GetString(), mms_string(&pDA->DAValue.mmsName), mms_GetDAValue(pDA).GetString());

            if (strInfor.GetLength() + nCurrLen < INFOR_BUFFER_WRITEDATA_LEN)
            {
                strcat(pDevice->InfoWriteData, strInfor.GetString());
            }

            CLogPrint::LogString(XLOGLEVEL_TRACE, strInfor);
        }

        pDA->bModify = SD_FALSE;
    }

    if (nError == 0)
    {
        ret = SD_SUCCESS;
        strcpy(pDevice->InfoWriteData, _T("写数据成功"));//"写数据成功");
    }

    pDevice->nWriteErrorCount = nError;
    pDevice->tmTotal = oTickCount32.GetTickCountLong();

    return ret;
}

ST_RET CDLT860Api::Client61850_WriteDataSingle(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        return SD_FAILURE;
    }

    ST_INT k;
    ST_INT nDaNum = 0;
    ST_INT nDsIndex;
    ST_RET ret = SD_FAILURE;
    tagDA *pDA;
    ST_INT nError = 0;

    CGpsPcTimeTickCount  oTickCount32;
    oTickCount32.Enter();
    Sleep(50);
    nDsIndex = pFuncParaEx->get_DSID();
    pDevice->nWriteErrorCount = 0;
    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    nDaNum = pLD_INFO->numData;
    pDevice->InfoWriteData[0] = 0;

    for (k=0; k<nDaNum; k++)
    {
        if (pFuncParaEx->NeedExitFunc())
        {
            break;
        }

        pDA = get_MMStagDAObj(pLD_INFO,k);

        if (pDA==NULL)
            continue;

        if (!pDA->bModify)
            continue;

        if (!pRemoteDev->WriteValue(pLD->LDName,pDA))
        {
            nError++;
            CString strInfor;
            long nCurrLen = strlen(pDevice->InfoWriteData);
            strInfor.Format(_T("写数据【%s】【%s】=【%s】失败."), mms_GetDADesc(pDA).GetString(), mms_string(&pDA->DAValue.mmsName), mms_GetDAValue(pDA).GetString());

            if (strInfor.GetLength() + nCurrLen < INFOR_BUFFER_WRITEDATA_LEN)
            {
                strcat(pDevice->InfoWriteData, strInfor.GetString());
            }

            CLogPrint::LogString(XLOGLEVEL_TRACE, strInfor);
        }

        pDA->bModify = SD_FALSE;
    }

    if (nError == 0)
    {
        ret = SD_SUCCESS;
        strcpy(pDevice->InfoWriteData, _T("写数据成功"));//"写数据成功");
    }

    pDevice->nWriteErrorCount = nError;
    pDevice->tmTotal = oTickCount32.GetTickCountLong();
    return ret;
}

ST_RET CDLT860Api::Client61850_ReadOneData(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("读取当前数据失败,请确认数据集路径是否正确."));
        return SD_FAILURE;
    }

    ST_INT ret = SD_SUCCESS;
    ST_INT k;
    ST_INT nDaNum = 0;
    ST_INT Type_id = 0;
    ST_INT i = 0;
    tagDA *pDA=NULL;
    ST_INT nDsIndex;
    ST_INT nDataIndex;
    BOOL bHasUnit = FALSE;
    BOOL bHasMinMax = FALSE;
    BOOL bHasStepSize = FALSE;

    nDsIndex = pFuncParaEx->get_DSID();
    nDataIndex = pFuncParaEx->get_DaIndex1();

    if (!pFuncParaEx->Chck_DevIndex())
        return SD_FAILURE;

    if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
        return SD_FAILURE;

    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    nDaNum = pLD_INFO->numData;
    CStringA strText(pLD_INFO->DataSetID);

    bHasUnit = HasUnit(pLD_INFO->DataSetID);
    bHasMinMax = HasMinMax(pLD_INFO->DataSetID);
    bHasStepSize = HasStepSize(pLD_INFO->DataSetID);

    nDaNum = 1;

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->SetMaxRange(nDaNum);
    }

    Type_id = 0;
    k = 0;

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->StepIt();
        CString strMsg;
        strMsg.Format(_T("第%d个  共%d个"), k+1, nDaNum);//_T("第%d个  共%d个")
        m_pProgressInterface->ShowMsg(strMsg);
    }

    pDA = get_MMStagDAObj(pLD_INFO, nDataIndex);

    if (pDA == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadOneData:DV=%d  LD=%d DS=%d DA=%d  Error")
            , pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
        return SD_FAILURE;
    }

    if (!pRemoteDev->ReadValue(pLD->LDName, pDA))
    {
        ret = SD_FAILURE;
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadOneData[%s]:DV=%d  LD=%d DS=%d DA=%d  Error")
            , pDA->DAValue.mmsName, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
    }

    return ret;
}

ST_RET CDLT860Api::Client61850_ReadData(CFuncParamEx *pFuncParaEx)
{
    CRemoteDev *pRemoteDev = NULL;
    ACSI_NODE *pDevice = NULL;
    LD_NODE *pLD = NULL;

    if (!GetAcsiiLD_Node(pFuncParaEx,&pRemoteDev,&pDevice,&pLD))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("读取当前数据失败,请确认数据集路径是否正确."));
        return SD_FAILURE;
    }

    ST_INT k;
    ST_INT nDaNum = 0;
    ST_INT Type_id = 0;
    ST_INT nLen;
    ST_INT i = 0;
    tagDA *pDA=NULL;
    ST_INT nDsIndex;
    BOOL bHasUnit = FALSE;
    BOOL bHasMinMax = FALSE;
    BOOL bHasStepSize = FALSE;
    long nDeviceIndex = pFuncParaEx->get_DevIndex();
    nDsIndex = pFuncParaEx->get_DSID();
    LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
    nDaNum = pLD_INFO->numData;
    CStringA strText(pLD_INFO->DataSetID);

    if ((strText == dsDout)&&(!g_o61850ClientConfig.m_nUseDsDout))
    {
        return SD_SUCCESS;  //zhouhj20180606 解决dsDout中读取数据失败的问题
    }

    bHasUnit = HasUnit(pLD_INFO->DataSetID);
    bHasMinMax = HasMinMax(pLD_INFO->DataSetID);
    bHasStepSize = HasStepSize(pLD_INFO->DataSetID);

    if (m_pProgressInterface != NULL)
    {
        m_pProgressInterface->SetMaxRange(nDaNum);
    }

    for (k=0; k<nDaNum; k++)
    {
        if (pFuncParaEx->NeedExitFunc())
        {
            break;
        }

        Type_id = 0;

        if (m_pProgressInterface != NULL)
        {
            m_pProgressInterface->StepIt();
            CString strMsg;
            strMsg.Format(_T("第%d个  共%d个"), k+1, nDaNum);//_T("第%d个  共%d个")
            m_pProgressInterface->ShowMsg(strMsg);
        }

        pDA = get_MMStagDAObj(pLD_INFO, k);

        if (pDA == NULL)
            continue;

        // 读取数值读取装置数据
        //////////////////////////////////////////////////////////////////////////
#ifdef _use_mms_string
        nLen = mms_str_length(&pDA->DAValue.mmsName);
#else
        nLen = strlen(pDA->DAValue.mmsName);
#endif

        if (!pRemoteDev->ReadValue(pLD->LDName, pDA))
        {
            continue;
        }

        if (m_bOnlyReadValue)
        {
            continue;
        }

// 		// 读取描述
// 		//////////////////////////////////////////////////////////////////////////
// 		ret = SD_FAILURE;
// #ifdef _MVL_TYPE_CTRL_use_one_device_
// 		ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl, VAR_DESC_NAME_KIND_FULL);
// #else
// 		ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_FULL);
// #endif
//
// 		if (ret!=SD_SUCCESS)
// 		{
// #ifdef _MVL_TYPE_CTRL_use_one_device_
// 			ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl, VAR_DESC_NAME_KIND_REMOVE_VALID);
// #else
// 			ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_REMOVE_VALID);
// #endif
// 		}
//
// 		// 读取单位
// 		//////////////////////////////////////////////////////////////////////////
// 		//if (pDA->bUnite==SD_FALSE)
// 		if (bHasUnit)
// 		{
// 			ret = SD_FAILURE;
// #ifdef _MVL_TYPE_CTRL_use_one_device_
// 			ret = get_DataUniteInfo(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl, VAR_DESC_NAME_KIND_REMOVE_VALID);
// #else
// 			ret = get_DataUniteInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_REMOVE_VALID);
// #endif
//
// 			if (ret!=SD_SUCCESS)
// 			{
// 				ret = get_DataUniteInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_FULL);
// 			}
// 		}
//
// 		// 2013-4-16  读取最大值、最小值、步长
// 		//////////////////////////////////////////////////////////////////////////
// 		if (bHasMinMax)
// 		{
// #ifdef _MVL_TYPE_CTRL_use_one_device_
// 			ret = get_DataLimitValInfoAll(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl);
// #else
// 			ret = get_DataLimitValInfoAll(netInfo, pLD->LDName, nLen, pDA);
// #endif
// 		}
//
// 		if (bHasStepSize)
// 		{
// 			ret = get_DataStepSizeInfo(netInfo, pLD->LDName, nLen, pDA);
// 		}
    }

    pLD_INFO->bHasEnum = SD_TRUE;
    return SD_SUCCESS;
}

BOOL CDLT860Api::Client61850_GetNextLdZonePara(CFuncParamEx *pFuncParaEx)
{
    ST_INT nLdIndex = pFuncParaEx->get_LDvIndex();
    ST_INT nDvIndex = pFuncParaEx->get_DevIndex();
    ST_INT nLdIndexCurr = nLdIndex;
    nLdIndex++;
    LD_NODE *pLD = NULL;
    ACSI_NODE *pDvNode = GetAcsiNode(nDvIndex);

    while (nLdIndex < pDvNode->numLD)
    {
        if (mms_IsSettingsDS(&pDvNode->LD[nLdIndex]/*.LDName*/) && m_nLdIndexBack != nLdIndex)
        {
            pLD = &pDvNode->LD[nLdIndex];
            pFuncParaEx->set_LDvIndex(nLdIndex);
            break;
        }

        nLdIndex++;
    }

    if (pLD == NULL)
    {
        nLdIndex = 0;

        while (nLdIndex < m_nLdIndexBack)
        {
            if (mms_IsSettingsDS(&pDvNode->LD[nLdIndex]/*.LDName*/))
            {
                pLD = &pDvNode->LD[nLdIndex];
                pFuncParaEx->set_LDvIndex(nLdIndex);
                break;
            }

            nLdIndex++;
        }

    }

    if (pLD != NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
            , _T("获取下一个逻辑设备读取定值区:%d, %d")
            , pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex());
    }

    return (pLD != NULL);
}

void CDLT860Api::InitUnLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bAutoTest, BOOL bOnlyLink)
{
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();

    if (nFuncID != FuncID_TestProc)
    {
        ExitAllConnFunc(nDeviceIndex);
    }

    CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_UnLink, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);

    if (bAutoTest)
    {
        pParam->set_ClientCmd();
    }
    else
    {
        pParam->set_ServerCmd();
    }

    if (!bOnlyLink)
    {
        m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
    }
}

void CDLT860Api::ExitAllConnFunc(ST_INT nDeviceIndex)
{
    CTickCount32 oTickCount;
    m_oFuncParamEx[nDeviceIndex].m_bExitFunc = TRUE;
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    m_oFuncParamEx[nDeviceIndex].m_posCurrFuncPara = NULL;
    long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();
    long nIndex = 0;

    while((nFuncID != FuncID_TestProc)&&(nIndex<10))
    {
        oTickCount.DoEvents(500);
        nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();
        nIndex++;
    }

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"结束装置%d全部通讯命令完成",nDeviceIndex);

    m_oFuncParamEx[nDeviceIndex].m_bExitFunc = FALSE;
}

BOOL CDLT860Api::InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
    ACSI_NODE *pDvNode = GetAcsiNode(nDeviceIndex);

    if (pDvNode == NULL)
    {
        return FALSE;
    }

    if (nDeviceIndex<0)
        return FALSE;

    long nLDIndex = 0;
    long nLDCount = pDvNode->numLD;

    if (bFreeFuncParas)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    for (nLDIndex=0; nLDIndex<nLDCount; nLDIndex++)
    {
        LD_NODE *pLD = &(pDvNode->LD[nLDIndex]);
        for (int i=0; i<pLD->numDaSet; i++)
        {
            // 2013-4-8  如果是定值无需停止
            if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,i))
                InitStopReportFuncParas(nDeviceIndex, nLDIndex, i);
        }
    }

    return TRUE;
}

BOOL CDLT860Api::InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
    if (!mms_HasEnumDataSet(nDeviceIndex, nLDIndex, nDsIndex))
    {
        return FALSE;
    }

    if (mms_GetDsDaDatasNum(nDeviceIndex, nLDIndex, nDsIndex)<=0)
    {
        return FALSE;
    }

    CFuncParam *pFuncPara = NULL;
    BOOL bIsReport = mms_GetReportFlag(nDeviceIndex, nLDIndex, nDsIndex);
    BOOL bIsReportRet = mms_GetReportRet(nDeviceIndex, nLDIndex, nDsIndex);

    if (!(bIsReportRet && bIsReport))
    {
        //return;
    }

    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StopRpt, dsType_NULL,/* hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_DSID(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
    return TRUE;
}

void CDLT860Api::InitReadOneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDataIndex, BOOL bDeleteAll)
{
    if (bDeleteAll)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(FuncID_ReadOne, nDeviceIndex, nLDIndex, nDsIndex, nDataIndex, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::ResetDevice(ST_INT nDeviceIndex, ST_INT nLDIndex)
{
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Reset, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitCtrlWriteOneFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDAIndex1, ST_INT nDAIndex2, ST_INT nDAValue1, ST_INT nDAValue2, ST_INT nTDelayAfterSel)
{
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWriteOne, nDsIndex, nDAIndex1, nDAIndex2, nDAValue1, nDAValue2, nTDelayAfterSel, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitReadJournal(ST_INT nDeviceIndex, ST_INT nLDeviceIndex, const CString &strJournalName
                                      , ST_INT bStart, ST_INT nStartType, CTime &tmStart, long long nStartEntry
                                      , ST_INT bEnd, ST_INT nEndType, CTime &tmEnd, ST_INT nEntryNum)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return;
    }

    LD_LOG_INFO *pszLogInfo = pDevice->LD[nLDeviceIndex].JournalCtrls.LogInfo;
    int nNum = pDevice->LD[nLDeviceIndex].JournalCtrls.numData;
    CString strLogRef;

    if (pszLogInfo == NULL)
    {
        return;
    }

    for (int nLen = 0;nLen<nNum;nLen++)
    {
        if (strcmp(mms_string(&pszLogInfo[nLen].Name),strJournalName.GetString()) == 0)
        {
            strLogRef = mms_string(&pszLogInfo[nLen].logRef);
            break;
        }
    }

    if (strLogRef.IsEmpty())
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("初始化读日志数目出错,对应日志索引未查找到,nDeviceIndex=%ld;nLDeviceIndex=%ld;strJournalName=%s;")
                                   ,nDeviceIndex,nLDeviceIndex,strJournalName.GetString());
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    CFuncParam *pFuncPara = NULL;
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDeviceIndex, strJournalName,bStart ,nStartType ,tmStart ,nStartEntry ,bEnd ,nEndType ,tmEnd, nEntryNum, FuncID_ReadJournal, -1, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_journal_ref(strLogRef);
}

void CDLT860Api::InitGetFile(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    ::CreateAllDirectories(strPath);

    CString strPostFix;
    CFuncParam *pFuncPara = NULL;
    strPostFix = ParseFilePostfix(strFileName);

    if (strPostFix == RECORD_FILE_POSTFIX_CFG || strPostFix == RECORD_FILE_POSTFIX_HDR
        || strPostFix == RECORD_FILE_POSTFIX_DAT || strPostFix == RECORD_FILE_POSTFIX_MID
        || strPostFix == RECORD_FILE_POSTFIX_DES)
    {
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_CFG);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_HDR);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DAT);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_MID);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DES);
    }
    else if (strPostFix == RECORD_FILE_POSTFIX_CFG_UPPER || strPostFix == RECORD_FILE_POSTFIX_HDR_UPPER
        || strPostFix == RECORD_FILE_POSTFIX_DAT_UPPER || strPostFix == RECORD_FILE_POSTFIX_MID_UPPER
        || strPostFix == RECORD_FILE_POSTFIX_DES_UPPER)
    {
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_CFG_UPPER);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_HDR_UPPER);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DAT_UPPER);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_MID_UPPER);
        InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DES_UPPER);
    }
    else
        m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1,strPath,strFileName , FuncID_ReadFile, -1,/* m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);//zhow:20180108
}

void CDLT860Api::InitUploadFile(ST_INT nDeviceIndex, const CString &strLocalFilePath,const CString &strDevPath) //参数2表示上传文件在电脑中的路径，装置内的路径固定为'/UPLOAD/'文件夹下
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前nDeviceIndex=%ld;不存在"),nDeviceIndex);
        return;
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1,strDevPath, strLocalFilePath ,FuncID_UploadFile, -1,/*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitGetFilePara(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName, const CString &strPostfix)
{
    CString strNewFileDevicePath;
    strNewFileDevicePath = ChangeFilePostfix(strFileName, strPostfix);

    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1,strPath,strNewFileDevicePath , FuncID_ReadFile, -1, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);//zhow:20180108

}

//tagDA数据操作
CString CDLT860Api::mms_GetDAName(tagDA *pDA)
{
    CString strText;
#ifdef _use_mms_string
    strText = mms_string(&pDA->DADescri.Value.string);//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#else
    strText = pDA->DADescri.Value.string;//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#endif
    return strText;
}

//读定值区号
void CDLT860Api::InitReadLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    if (nLDIndex > pDevice->numLD - 1)
    {
        return;
    }

    CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_GetSGNum, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    ValidateCurrFunc_ReadZone(pFuncPara);
}

//写定值区号
void CDLT860Api::InitWriteLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nZone)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSGNum, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_SGID(nZone);
}

void CDLT860Api::InitReadLDeviceValuesFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDAType)
{
    set_OnlyReadValue(TRUE);
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    if (nLDIndex > pDevice->numLD - 1)
    {
        return;
    }

    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDsDAType,/* m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitReadFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
    CFuncParam *pFuncPara = NULL;
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDsIndex, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitReadFuncPara_Set(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nZone, ST_INT nRunSG, BOOL bDeleteAll)
{
    if (bDeleteAll)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    CFuncParam *pFuncPara = NULL;
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read_SET, nDsIndex, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);

    pFuncPara->set_SEID(nZone);
    pFuncPara->set_SGID(nRunSG);
}

void CDLT860Api::InitReadDevice(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
//	ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (bFreeFuncParas)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1 ,FuncID_ReadDevice, -1,/* m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

ST_INT CDLT860Api::GetDsIndex(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return -1;
    }

    LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    ST_INT nIndex = 0;
    LD_DATASET_INFO	*pDataInfo = pLD_NODE->DataInfo;

    for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
    {
        if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
        {
            return nIndex;
        }
    }

    return -1;
}

void CDLT860Api::InitWriteCurrSetsFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, long nZone, BOOL bDeleteAll)
{
    if (nDsIndex < 0)
    {
        nDsIndex = GetDsIndex(nDeviceIndex, nLDIndex, dsID_Setting);
    }

    if (bDeleteAll)
    {
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    }

    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
    ST_INT nSEIndex = pDevice->nRunSGIndex;
    ST_INT nCurrSGIndex = pDevice->nRunSGIndex; //编辑当前运行的区
    //	HWND hWnd = m_pMainWnd->m_hWnd;
    CFuncParam *pFuncPara=NULL;

    if (nZone > 0)
    {
        nSEIndex = nZone;
    }

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("监视【%d】 RunSGIndex=【%08x】"),nDeviceIndex, pDevice->nRunSGIndex);

    //如果两个数据一致，表示正常，否则表示固化定值后没有切换回来，或者其他情况
    //运行区与编辑区相同，则切换运行区
    BOOL bChangeZone = FALSE;

    if ((g_o61850ClientConfig.m_nCanWriteActiveSG==0)&&(nCurrSGIndex == nSEIndex))//zhouhj  在不能改运行区，并且当前运行区与需要修改的定值区相同的情况下，才做切区的操作
    {
        //		if (nCurrSGIndex == nSEIndex)
        {
            nCurrSGIndex++;
        }

        if (nCurrSGIndex >= pDevice->nSGNum)
        {
            nCurrSGIndex = 1;
        }

        pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSGNum, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
        pFuncPara->set_SGID(nCurrSGIndex);

        bChangeZone = TRUE;
    }


    //切换定值编辑区
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSENum, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_SEID(nSEIndex);

    //修改定值
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Write, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_SEID(nSEIndex);

    //定值固化
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CnfSetSE, nDsIndex, /*hWnd, */WM_Notify_Msg);
    pFuncPara->set_SEID(nSEIndex);

    //设置当前定值区
    if (bChangeZone)
    {
        pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSGNum, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
        pFuncPara->set_SGID(nSEIndex);
    }
}

// 报告
BOOL CDLT860Api::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, BOOL bFreeFuncParas)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return FALSE;
    }

    LD_NODE *pLD = pRemoteDev->GetLdNode(nLDIndex);

    if (pLD == NULL)
    {
        return FALSE;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    long nLdCount = pDevice->numLD;

    if (bFreeFuncParas)
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();


    // 2013-4-8  注意定值无相应的报告
    if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,nDsIndex))
        InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDsIndex, bStart);

    return TRUE;
}

void CDLT860Api::InitCallReportFlagDefault(ST_INT nDeviceIndex)
{
    CRemoteDev *pRemoteDev = GetRemoteDev(nDeviceIndex);

    if (pRemoteDev == NULL)
    {
        return;
    }

    ACSI_NODE *pDevice = pRemoteDev->GetAcsiNode();
    long nLDIndex = 0;
    long nLdCount = pDevice->numLD;

    for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
    {
        LD_NODE *pLD = &pDevice->LD[nLDIndex];

        for (int i=0; i<pLD->numDaSet; i++)
        {
            // 2013-4-8  注意定值无相应的报告
            if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,i))
                mms_SetReportFlag(nDeviceIndex, nLDIndex, i, TRUE);
        }
    }
}

void CDLT860Api::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart)
{
    //定值，则返回
    if (CheckCurSelIsSetting(nDeviceIndex,nLDIndex,nDsIndex))
    {
        return;
    }

    if ((!bStart) && (!mms_HasEnumDataSet(nDeviceIndex, nLDIndex, nDsIndex)))
    {
        return;
    }

    if (mms_GetDsDaDatasNum(nDeviceIndex, nLDIndex, nDsIndex) <= 0)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【%d-%d-%d】没有枚举数据集"), nDeviceIndex, nLDIndex, nDsIndex);
        return;
    }

    CFuncParam *pFuncPara = NULL;
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StartRpt, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_DSID(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
}


BOOL CDLT860Api::InitCallReportFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, UINT nBrcbIndex, BOOL bFreeFuncParas)
{
    //定值，则返回
    if (CheckCurSelIsSetting(nDeviceIndex,nLDIndex,nDsIndex))
    {
        return FALSE;
    }

    if (!mms_HasEnumDataSet(nDeviceIndex, nLDIndex, nDsIndex))
    {
        return FALSE;
    }

    if (mms_GetDsDaDatasNum(nDeviceIndex, nLDIndex, nDsIndex) <= 0)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【%d-%d-%d】没有枚举数据集"), nDeviceIndex, nLDIndex, nDsIndex);
        return FALSE;
    }

    if (bFreeFuncParas)
        m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

    CFuncParam *pFuncPara = NULL;
    pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StartRpt, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
    pFuncPara->set_DSID(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
    pFuncPara->set_BrcbIndex(nBrcbIndex);
    return TRUE;
}

void CDLT860Api::InitGetFileDir(ST_INT nDeviceIndex, const CString &strPath,BOOL bOnlyReadCfg)//参数2指装置内的目录，为空表示读根目录下的所有文件及文件夹
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return;
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    pDevice->FileDir.nType = 1;
    pDevice->FileDir.bIsNew = 1;

    long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();

    if (nFuncID != FuncID_TestProc)
    {
        ExitAllConnFunc(nDeviceIndex);
    }

    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, strPath ,FuncID_ReadDir, -1,bOnlyReadCfg, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CDLT860Api::InitReadDeviceRPC_FuncParas(ST_INT nDeviceIndex)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return;
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();

    if (nFuncID != FuncID_TestProc)
    {
        ExitAllConnFunc(nDeviceIndex);
    }

    m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex ,FuncID_ReadRPC, WM_Notify_Msg);
}

void CDLT860Api::InitRpcCall(ST_INT nDeviceIndex,const CString &strParaFunction,const CString &strParaCallName,const CString &strParaCallID,
                             long nVersion,long nTimeout,long nRequestType,long nResponseType)
{
    ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

    if (pDevice == NULL)
    {
        return;
    }

    m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
    long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();

    if (nFuncID != FuncID_TestProc)
    {
        ExitAllConnFunc(nDeviceIndex);
    }

    m_oFuncParamEx[nDeviceIndex].AddFuncParaRpcCall(nDeviceIndex ,FuncID_RpcCall,strParaFunction,strParaCallName,strParaCallID,nVersion,
        nTimeout,nRequestType,nResponseType,WM_Notify_Msg);
}

/*
tagDA* mms_new_tagda()
{
    tagDA* pNewDA = (tagDA*)malloc(sizeof(tagDA));//new tagDA();
    ZeroMemory(pNewDA, sizeof(tagDA));
    return pNewDA;
}

tagDA* mms_new_tagda(long nCount)
{
    int nSize = nCount * sizeof (tagDA);
    tagDA* pNewDA = (tagDA*)malloc(nSize);//new tagDA();
    ZeroMemory(pNewDA, nSize);
    return pNewDA;
}
*/

ST_RET CDLT860Api::node_get_tagDAData(LD_NODE *pLD, tagDA *pDA)
{
    MMS_DATA_NODE *pHead_LN_NODE = pLD->mms_data_node;
    MMS_DATA_NODE *pLN_NODE = pHead_LN_NODE;
    MMS_DATA_NODE *pNode_Data = NULL;
    ST_INT nLen;
    CString strTmp,strLNName,strFC;
    strTmp = mms_string(&pDA->DAValue.mmsName);
    nLen = strTmp.Find('$');

    if ((nLen == -1)||(pLN_NODE == NULL))
    {
        return SD_FAILURE;
    }

    strLNName = strTmp.Left(nLen);
    strTmp = strTmp.Mid(nLen+1);
    nLen = strTmp.Find('$');
    strFC = strTmp.Left(nLen);
    strTmp = strTmp.Mid(nLen+1);

    do
    {
        if (strLNName == mms_string(&pLN_NODE->name) )
        {
            MMS_DATA_NODE *FC_node = pLN_NODE->pFirstChild;
            MMS_DATA_NODE *Head_FC_node = FC_node;

            if (FC_node == NULL)
            {
                return SD_FAILURE;
            }

            do
            {
                if (strFC == mms_string(&FC_node->name) )
                {
                    pNode_Data = find_node_by_name(FC_node,strTmp);

                    if (pNode_Data == NULL)
                        return SD_FAILURE;

                    init_tagDA_datatype(pDA,pNode_Data);
                    add_child_tagDA(pDA,pNode_Data);
                    MMS_DATA_NODE *Find_node = node_find_child(pLN_NODE,_T("DC"));

                    if (Find_node != NULL)
                        node_get_desc_path(pDA,Find_node);

                    Find_node = node_find_child(pLN_NODE,_T("CF"));

                    if (Find_node != NULL)
                    {
                        node_get_LimitVal_path(pDA,Find_node);
                    }

                    return SD_SUCCESS;
                }

                FC_node = FC_node->pNext;
            } while((FC_node != Head_FC_node)&&(FC_node != NULL));
        }

        pLN_NODE = pLN_NODE->pNext;
    } while ((pLN_NODE != pHead_LN_NODE)&&(pLN_NODE != NULL));

    return SD_FAILURE;
}

MMS_DATA_NODE* CDLT860Api::find_node_by_name(MMS_DATA_NODE *FC_node,const CString&strDescPath)
{
    if ((FC_node == NULL)||(strDescPath.IsEmpty()))
        return NULL;

    if (FC_node->pFirstChild == NULL)
        return NULL;

    CString strNodeName,strTmp;
    ST_INT nLen = strDescPath.Find('$');

    if (nLen == -1)
        strNodeName = strDescPath;
    else
    {
        strNodeName = strDescPath.Left(nLen);
        strTmp = strDescPath.Mid(nLen+1);
    }

    MMS_DATA_NODE *pNode_Data = FC_node->pFirstChild;
    MMS_DATA_NODE *pHead_Node_Data = FC_node->pFirstChild;

    do
    {
        if (strNodeName == mms_string(&pNode_Data->name) )
        {
            if (strTmp.IsEmpty())
                return pNode_Data;
            else
                return find_node_by_name(pNode_Data,strTmp);
        }

        pNode_Data = pNode_Data->pNext;
    } while((pNode_Data != pHead_Node_Data)&&(pNode_Data != NULL));

    return NULL;
}

void CDLT860Api::init_tagDA_datatype(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child)
{
    CString strDataType = pNode_Child->DataType;

    if (strDataType.IsEmpty())
        strcpy(pNewDA->DataType,_T("STRUCT"));
    else if(strDataType == _T("BVSTRING13"))
        strcpy(pNewDA->DataType,_T("BIT_STR"));
    else if(strDataType == _T("UTF8VSTRING255"))
        strcpy(pNewDA->DataType,_T("UTF8_STR"));
    else if(strDataType == _T("VSTRING255"))
        strcpy(pNewDA->DataType,_T("V_STR"));
    else if(strDataType == _T("BSTRING2"))
        strcpy(pNewDA->DataType,_T("BIT_STR"));
    else if(strDataType == _T("OVSTRING64"))
        strcpy(pNewDA->DataType,_T("OCT_STR"));
    else if(strDataType == _T("VSTRING65"))
        strcpy(pNewDA->DataType,_T("V_STR"));
    else if(strDataType == _T("BVSTRING2"))
        strcpy(pNewDA->DataType,_T("BIT_STR"));
    else if(strDataType == _T("UBYTE"))
        strcpy(pNewDA->DataType,_T("UINT"));
    else if(strDataType == _T("BVSTRING2"))
        strcpy(pNewDA->DataType,_T("BIT_STR"));
    else if(strDataType == _T("LONG"))
        strcpy(pNewDA->DataType,_T("INT"));
    else if(strDataType == _T("BYTE"))
        strcpy(pNewDA->DataType,_T("INT"));
    else if(strDataType == _T("UTCTIME"))
        strcpy(pNewDA->DataType,_T("UTC_TIME"));
    else
        strcpy(pNewDA->DataType,strDataType.GetString());

    mms_InitDA_DataType(pNewDA);
}

void CDLT860Api::add_child_tagDA(tagDA *pDA,MMS_DATA_NODE *pNode_Data)
{
    if (pNode_Data->pFirstChild == NULL)
    {
        pDA->nSubDANum = 0;
        pDA->pSubDA = NULL;
    }
    else
    {
        ST_INT nSubNum = 0;
        get_node_numbers(pNode_Data,nSubNum);

        if (pDA->pSubDA != NULL)
        {
            for (int i=0;i<pDA->nSubDANum;i++)
            {
                mms_ReleaseData(&pDA->pSubDA[i]);
            }

            pDA->nSubDANum = 0;
            free(pDA->pSubDA);
            pDA->pSubDA = NULL;
        }

        pDA->nSubDANum = nSubNum;
        pDA->pSubDA = mms_new_tagda(pDA->nSubDANum);
        mms_InitDatas(pDA->pSubDA, pDA->nSubDANum);
        MMS_DATA_NODE *pNode_Child = pNode_Data->pFirstChild;
        MMS_DATA_NODE *pNode_Head_Child = pNode_Child;
        tagDA *pNewDA = pDA->pSubDA;

        do
        {
            init_tagDA_data(pNewDA,pNode_Child,mms_string(&pDA->DAValue.mmsName));
            get_node_tagDA(&pNewDA,pNode_Child);
            pNode_Child = pNode_Child->pNext;
        } while ((pNode_Child!=pNode_Head_Child)&&(pNode_Child != NULL));
    }
}

void CDLT860Api::init_tagDA_data(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child,ST_CHAR *pValuePath)
{
    CString strNewPath;
    init_tagDA_datatype(pNewDA,pNode_Child);

    strNewPath.Format(_T("%s$%s"),pValuePath,mms_string(&pNode_Child->name));
    strNewPath.Replace("$$","$");
    mms_str_set(&pNewDA->DAValue.mmsName, strNewPath.GetString());
}

MMS_DATA_NODE* CDLT860Api::node_find_child(MMS_DATA_NODE *pLN_NODE,const CString &strTmp)
{
    MMS_DATA_NODE *Child_node = pLN_NODE->pFirstChild;
    MMS_DATA_NODE *Head_FC_node = pLN_NODE->pFirstChild;

    if (Child_node == NULL)
        return NULL;

    do
    {
        if (strTmp == mms_string(&Child_node->name) )
        {

            return Child_node;
        }

        Child_node = Child_node->pNext;
    } while((Child_node != Head_FC_node)&&(Child_node != NULL));

    return NULL;
}

void CDLT860Api::node_get_desc_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE)
{
    CString strDescPath,strTmp;
    int nIndex = -1;
    strDescPath = mms_string(&pDA->DAValue.mmsName);
    nIndex = strDescPath.Find("$");
    strTmp = strDescPath.Left(nIndex);
    strTmp += ("$DC$");
    strDescPath = strDescPath.Mid(nIndex+4);

    //	if ((pDA->nDataType != DA_DATATYE_UTC_TIME)&&(pDA->nDataType != DA_DATATYE_BIT_STR)&&(pDA->nDataType != DA_DATATYE_ARRAY))
    {
        node_find_dU(pDA,pLN_NODE,strTmp,strDescPath);
    }
}

void CDLT860Api::node_find_dU(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail)
{
    int nIndex = strPathTail.Find("$");
    CString strTmp1;
    MMS_DATA_NODE *Find_node = NULL;

    if (nIndex != -1)
    {
        strTmp1 = strPathTail.Left(nIndex);
        strPathTail = strPathTail.Mid(nIndex+1);
    }
    else
        strTmp1 = strPathTail;

    Find_node = node_find_child(FC_node,strTmp1);

    if (Find_node != NULL)
    {
        MMS_DATA_NODE *FindChild_node = NULL;
        FindChild_node = node_find_child(Find_node,_T("dU"));
        strPathHead += (strTmp1);

        if (FindChild_node != NULL)
        {
            //			strPathHead.Append(_T("$dU"));
            mms_str_set(&pDA->DADescri.mmsName, strPathHead.GetString());
            mms_str_cat(&pDA->DADescri.mmsName, _T("$dU"));
        }

        if (nIndex != -1)
        {
            strPathHead += ("$");
            node_find_dU(pDA,Find_node,strPathHead,strPathTail);
        }
    }
}

void CDLT860Api::get_node_tagDA(tagDA **ppDA,MMS_DATA_NODE *pNode_Data)
{
    char szTmp[NAMESIZE] = {0};
    strcpy(szTmp,mms_string(&(*ppDA)->DAValue.mmsName));

    if (pNode_Data->pFirstChild == NULL)
    {
        (*ppDA)->nSubDANum = 0;
        (*ppDA)->pSubDA = NULL;
        (*ppDA)++;
    }
    else if (strcmp((*ppDA)->DataType,_T("ARRAY")) == 0)
    {
        strcpy((*ppDA)->DataType,_T("STRUCT"));
        mms_InitDA_DataType(*ppDA);
        (*ppDA)->nSubDANum = 1;
        (*ppDA)->pSubDA = mms_new_tagda();
        mms_InitDatas((*ppDA)->pSubDA, 1);
        tagDA *pNewDA = (*ppDA)->pSubDA;
        strcpy(pNewDA->DataType,_T("ARRAY"));
        mms_InitDA_DataType(pNewDA);
        mms_str_set(&pNewDA->DAValue.mmsName, szTmp);
        mms_str_cat(&pNewDA->DAValue.mmsName, "$");
        add_node_tagDA_ARRAY(pNewDA,pNode_Data);

        (*ppDA)++;
    }
    else
    {
        MMS_DATA_NODE *pNode_Child = pNode_Data->pFirstChild;
        MMS_DATA_NODE *pNode_Head_Child = pNode_Child;

        do
        {
            init_tagDA_data(*ppDA,pNode_Child,szTmp);
            get_node_tagDA(ppDA,pNode_Child);
            pNode_Child = pNode_Child->pNext;

        } while((pNode_Child!=pNode_Head_Child)&&(pNode_Child != NULL));
    }
}

void CDLT860Api::add_node_tagDA_ARRAY(tagDA *pDA,MMS_DATA_NODE *pNode_Data)
{
    ST_INT nSubNum = 0,nArrNum = pNode_Data->data.valLong;

    pDA->nSubDANum = nArrNum;
    pDA->pSubDA = mms_new_tagda(nArrNum);
    mms_InitDatas(pDA->pSubDA, nArrNum);
    tagDA *pFirstSub = pDA->pSubDA;

    mms_str_set(&pFirstSub->DAValue.mmsName, mms_string(&pDA->DAValue.mmsName));
    get_node_numbers(pNode_Data,nSubNum);

    if (nSubNum == 1)
    {
        pFirstSub->nSubDANum = 0;
        pFirstSub->pSubDA = NULL;
        get_node_tagDA(&pFirstSub,pNode_Data);
        pFirstSub--;
    }
    else if (nSubNum > 1)
    {
        strcpy(pFirstSub->DataType,_T("STRUCT"));
        mms_InitDA_DataType(pFirstSub);
        pFirstSub->nSubDANum = nSubNum;
        pFirstSub->pSubDA = mms_new_tagda(nSubNum);
        mms_InitDatas(pFirstSub->pSubDA, nSubNum);
        tagDA *pNewDA = pFirstSub->pSubDA;
        mms_str_set(&pNewDA->DAValue.mmsName, mms_string(&pDA->DAValue.mmsName));
        get_node_tagDA(&pNewDA,pNode_Data);
    }

    ST_CHAR DAName[NAMESIZE];
    memset(DAName, 0, NAMESIZE);

    for (int k=1; k<pDA->nSubDANum; k++)
    {
        mms_CopyData(pFirstSub, &pDA->pSubDA[k], FALSE);
        sprintf(DAName, "%d", k);
        My_PareVarType_Array_MmsName(&pDA->pSubDA[k], DAName);
    }
}

void CDLT860Api::get_node_numbers(MMS_DATA_NODE *pNode_Data,ST_INT &nSubNum)
{
    if (pNode_Data->pFirstChild == NULL)
    {
        nSubNum++;
        return;
    }

    MMS_DATA_NODE *pNode_Child = pNode_Data->pFirstChild;

    do
    {
        if (strcmp(pNode_Child->DataType,_T("ARRAY")) == 0)
            nSubNum++;
        else
            get_node_numbers(pNode_Child,nSubNum);

        pNode_Child = pNode_Child->pNext;
    }
    while((pNode_Child != pNode_Data->pFirstChild)&&(pNode_Child!=NULL));
}

ST_VOID CDLT860Api::My_PareVarType_Array_MmsName(tagDA *pDA, ST_CHAR *pArrayIndex)
{
    if (strcmp(pDA->DataType, "STRUCT") != 0)
    {
#ifdef _use_mms_string
        mms_str_append(&pDA->DAValue.mmsName, pArrayIndex);
#else
        strcat(pDA->DAValue.mmsName, pArrayIndex);
#endif
    }
    else
    {

    }

    if (pDA->nSubDANum == 0)
    {
        return;
    }

    long nIndex = 0;

    for (nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
    {
        My_PareVarType_Array_MmsName(&pDA->pSubDA[nIndex], pArrayIndex);
    }
}

void CDLT860Api::node_get_LimitVal_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE)
{
    CString strDescPath,strPathHead,strPathTail,strTmp1,strTmp2;
    int nIndex = -1;
    strDescPath = mms_string(&pDA->DAValue.mmsName);
    nIndex = strDescPath.Find("$");
    strPathHead = strDescPath.Left(nIndex);
    strPathHead += ("$CF$");
    strPathTail = strDescPath.Mid(nIndex+4);
    strTmp1 = strPathHead;
    strTmp2 = strPathTail;

    node_find_MinMaxStepUnit(pDA,pLN_NODE,strPathHead,strPathTail,0);
    strPathHead = strTmp1;
    strPathTail = strTmp2;
    node_find_MinMaxStepUnit(pDA,pLN_NODE,strTmp1,strTmp2,1);
    strTmp1 = strPathHead;
    strTmp2 = strPathTail;
    node_find_MinMaxStepUnit(pDA,pLN_NODE,strPathHead,strPathTail,2);
    node_find_MinMaxStepUnit(pDA,pLN_NODE,strTmp1,strTmp2,3);
}

void CDLT860Api::node_find_MinMaxStepUnit(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail,ST_INT nLimitKind)
{                                                   //zhouhj nLimitKind=0代表最小值, nLimitKind=1代表最大值, nLimitKind=2代表步长, nLimitKind=3代表单位
    int nIndex = strPathTail.Find("$");
    CString strTmp1;
    MMS_DATA_NODE *Find_node = NULL;

    if (nIndex != -1)
    {
        strTmp1 = strPathTail.Left(nIndex);
        strPathTail = strPathTail.Mid(nIndex+1);
    }
    else
        strTmp1 = strPathTail;

    Find_node = node_find_child(FC_node,strTmp1);

    if (Find_node != NULL)
    {
        strPathHead += (strTmp1);
        MMS_DATA_NODE *FindChild_node = NULL;

        if (nLimitKind == 0)
            FindChild_node = node_find_child(Find_node,_T("minVal"));
        else if (nLimitKind == 1)
            FindChild_node = node_find_child(Find_node,_T("maxVal"));
        else if (nLimitKind == 2)
            FindChild_node = node_find_child(Find_node,_T("stepSize"));
        else if (nLimitKind == 3)
            FindChild_node = node_find_child(Find_node,_T("units"));

        if (FindChild_node != NULL)
        {
            CString strVal;
            strVal.Format("$%s",mms_string(&FindChild_node->name));
            strPathHead += (strVal);

            if (FindChild_node->pFirstChild!=NULL)
            {
                strVal.Format("$%s",mms_string(&FindChild_node->pFirstChild->name));
                strPathHead += (strVal);
            }

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
            if (nLimitKind == 0)
                mms_str_set(&pDA->MinVal.mmsName, strPathHead.GetString());
            else if (nLimitKind == 1)
                mms_str_set(&pDA->MaxVal.mmsName, strPathHead.GetString());
            else if (nLimitKind == 2)
                mms_str_set(&pDA->StepSize.mmsName, strPathHead.GetString());
            else if (nLimitKind == 3)
                mms_str_set(&pDA->DAUnite.mmsName, strPathHead.GetString());
// 			else
// 			{
// 				strPathHead.Replace("$SIUnit","");
// 				strPathHead.Replace("$multiplier","");
// 				mms_str_set(&pDA->DAUnite.mmsName, strPathHead);
// 			}
#endif
        }
        else if (nIndex != -1)
        {
            strPathHead += "$";
            node_find_MinMaxStepUnit(pDA,Find_node,strPathHead,strPathTail,nLimitKind);
        }
    }
}








