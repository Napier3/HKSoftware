#include "stdafx.h"
#include "SttTestEngineServerData.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../RecordTest/SttRcdSendSocket.h"
#include "../ReplayTest/SttComtradeRcvSocket.h"
#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../LiveUpdate/SttLiveUpdateApi.h"
#endif
// #include "SttTestServerBase.h"
// #include "../SttDevice/SttDeviceBase.h"

//2020-10-27  lijunqing
#include "../API/NetworkInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//2020-10-19  lijunqing  Server只有一个，所以定义一个全局变量，方便访问
CSttTestEngineServerData *g_theSttTestEngineServer = NULL;
CSttSocketDataBase *g_pReplayTestSocket = NULL;
long g_nCheckAuthority = 0;

//////////////////////////////////////////////////////////////////////////
//
CSttTestEngineServerData::CSttTestEngineServerData()
{
    //2020-10-19  lijunqing  Server只有一个，所以定义一个全局变量，方便访问
    g_theSttTestEngineServer = this;
    m_pServerSocket = NULL;
	m_pReplaySocket = NULL;
    m_pSttTestClientUserMngr = NULL;
}

CSttTestEngineServerData::~CSttTestEngineServerData()
{
    ASSERT (m_pServerSocket == NULL);
}

//2022-2-12  lijunqing
void CSttTestEngineServerData::DispatchMsg(unsigned char *pBuf, long nLen)
{
    CSttTestClientUser *pUser = NULL;
    POS pos = m_pSttTestClientUserMngr->GetHeadPosition();

    while(pos != NULL)
    {
        pUser = (CSttTestClientUser *)m_pSttTestClientUserMngr->GetNext(pos);

        //        if (! pUser->HasAuthority(KEY_AUTHORITY_MODULE_Ats))
        //        {
        //            continue;
        //        }

        if (pUser->m_pRefSttSckt != NULL)
        {
            pUser->m_pRefSttSckt->SendBuffer(pBuf,nLen);
        }
    }
}

void CSttTestEngineServerData::OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket)
{
    //退出登录或断链，检查是否停止测试
    CheckStopTestAfterRelease(pSocket);

    BOOL bRet = m_pSttTestClientUserMngr->DeleteUserByRefSocket(pSocket);

    // 	CSttTestServerBase  *pCSttTestServerBase=CSttTestServerBase::GetServerEngine();
    // 	if(pCSttTestServerBase->m_oSttTestCmd.GetRefSocketData()==pSocket)
    // 	{
    // 		pCSttTestServerBase->m_oSttTestCmd.SetRefSocketData(NULL);
    // 		CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
    // 		if (pCurrTest != NULL)
    // 		{
    // 			pCurrTest->Stop();
    // 		}
    // 		if(CSttDeviceBase::g_pSttDeviceBase != NULL)
    // 		{
    // 			CSttDeviceBase::g_pSttDeviceBase->CloseDevice();
    // 		}
    // 	}

    if (bRet)
    {
        //生成应答命令返回
        CSttSysState oSysState;
        ReturnBroadcastUserMngr(oSysState);
    }

    //20210123 xxy 必须最后一行，防止软件关闭时，执行了该行之后delete ServerEngine,而这个函数还没执行完
    //参考CSttServerSocketDataBase::CloseSttServer()
    m_pServerSocket->CSttServerSocketDataBase::OnSttScktClose(pSocket, bDeleteSocket);
}

long CSttTestEngineServerData::IsCanAuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest)
{//0:不可授权，1：已授权，2、可授权但未授权
    CSttParas *pParas = oSysCmd.GetSttParas();
    POS pos = pParas->GetHeadPosition();
    CDvmData *pData = NULL;
	CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindByIDTest(oSysCmd.m_nIDTester,oSysCmd.m_strTestor);

    if (pUser == NULL)
    {//返回异常错误SysCmd，对应的用户不存在了
        return 0;
    }

    long nSingleRet = 0;
    long nRet = 1;
    while (pos != NULL)
    {
        pData = (CDvmData*)pParas->GetNext(pos);

        nSingleRet = IsCanAuthorityToUser(pUser, pData,bRequest);
        if (nSingleRet == 0)
        {
            return 0;
        }
        else if (nSingleRet == 2)
        {
            nRet = 2;
        }
    }

    return nRet;
}

long CSttTestEngineServerData::IsCanAuthorityToUser(CSttTestClientUser *pUser, CDvmData *pData,BOOL bRequest)
{//0:不可授权，1：已授权，2、可授权但未授权
    long nAuthority = CString_To_long(pData->m_strValue);

    if (nAuthority == 0)
    {//取消权限，直接取消
        if (pUser->HasAuthority(pData->m_strID))
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    //授权，需要判断是否有用户拥有相同的权限
    CSttTestClientUser *pFind = m_pSttTestClientUserMngr->FindHasAuthority(pData->m_strID);

    if (pFind == NULL)
    {
        return 2;
    }
    else if (pUser == pFind)
    {
        return 1;
    }
    else
    {//权限被占用
        //如果正在测试，则授权失败

        //否则，高优先级打断底优先级
        if((bRequest) && (pUser->CompareUserPriority(pFind) > 0))
        {//若是授权
            return 2;
        }
    }

    return 0;
}

long CSttTestEngineServerData::AuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest,BOOL bBroadcastWhenSuccess)
{
    //0:不可授权，1：已授权，2、可授权但未授权
    long nRet = IsCanAuthorityToUser(oSysCmd,bRequest);
    //20220715 zhoulei
    if(nRet == 1)
    {
        return 1;
    }

    if(g_nCheckAuthority)
    {
        if (nRet == 0)
        {
            return 0;
        }
    }
    else
    {
        nRet = 2;
    }

    CSttParas *pParas = oSysCmd.GetSttParas();
	CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindByIDTest(oSysCmd.m_nIDTester,oSysCmd.m_strTestor);

    if(pUser == NULL)
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] User no Login"));
        return 0;
    }

    pUser->SetAuthoritys(pParas);
    m_pSttTestClientUserMngr->ClearOtherAuthoritys(pParas, pUser);

    if (bBroadcastWhenSuccess && nRet == 2)
    {
        CSttSysState oSysState;
        ReturnBroadcastUserMngr(oSysState);
    }

    return nRet;
}

//登录
CSttTestClientUser* CSttTestEngineServerData::User_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{//脱机软件或测试服务程序登录
    CSttTestClientUser *pUser = NULL;
    CString strIDTerminal, strSoftID;
    DWORD nIDTester = 0;
    oSysCmd.GetParasDataValueByID(ID_STT_USER_ATTR_ID_Terminal, strIDTerminal);
    oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);
    oSysCmd.GetParasDataValueByID(ID_STT_USER_ATTR_id_soft, strSoftID);

    CSttSocketDataBase *pPrevSocket = NULL;

    //2020-11-29   lijunqing
    //严重逻辑错误，测试端，如果同时使用Debug和测试端，就会导致之前的连接被断开
    //正确逻辑：nIDTester + strSoftID  唯一
    pUser = m_pSttTestClientUserMngr->FindByIDTest(nIDTester, strSoftID);

    if (pUser == NULL)
    {
        pUser = new CSttTestClientUser();
        m_pSttTestClientUserMngr->AddNewChild(pUser);
    }
    else if (pUser->m_pRefSttSckt != pClientSocket)
    {
        pPrevSocket = pUser->m_pRefSttSckt;
        pUser->m_pRefSttSckt = pClientSocket;
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Ats,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
    }

    //重复登录不改变用户的权限
    pUser->AnalysisLoginUser(oSysCmd);
    pClientSocket->m_nIDTester = nIDTester;
    pUser->m_pRefSttSckt = pClientSocket;
    pUser->m_pRefSttSckt->SetUser(pUser);

    if (strIDTerminal != STT_TERMINAL_TYPE_REMOTE)
    {
        if (pUser->IsTerminalType_Local())
        {
            pClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);
        }
        else
        {
            pClientSocket->SetSocketType(STT_SOCKET_TYPE_OWN);
        }
    }
    else
    {
        pClientSocket->SetSocketType(STT_SOCKET_TYPE_REMOTE);
    }

    if (pPrevSocket != NULL)
    {
        pPrevSocket->CloseSocket();

        if (CanSendLog())
        {
            CString strInfo;
            strInfo.Format(_T("User_Login [%u] repeat"),nIDTester);
            LogDebugInfor(strInfo);
        }
    }

    return pUser;
}

long CSttTestEngineServerData::ReturnSysStateToChildren(CSttSocketDataBase *pExceptSocket,CSttSysState *pSysState)
{
    long nSendLen = 0;
    BYTE *pSendBuf = NULL;

	if (pExceptSocket != NULL)
	{
		stt_InitRetSendBuf(&pSendBuf,nSendLen,pSysState, FALSE, pExceptSocket->m_nSttCmdDataFormat);
	}
	else
	{
		stt_InitRetSendBuf(&pSendBuf,nSendLen,pSysState, FALSE, _PUGI_XML_TYPE_);
	}

    BOOL bRet = SendBufferToChildren(pExceptSocket,pSendBuf,nSendLen);
    delete pSendBuf;

    return bRet;
}

BOOL CSttTestEngineServerData::SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen)
{
    CSttTestClientUser *pUser = NULL;
    POS pos = m_pSttTestClientUserMngr->GetHeadPosition();

    while(pos != NULL)
    {
        pUser = (CSttTestClientUser *)m_pSttTestClientUserMngr->GetNext(pos);

        if(pUser != NULL)
        {
            if ((pUser->m_pRefSttSckt != NULL) && (pUser->m_pRefSttSckt != pExceptSocket))
            {
                pUser->m_pRefSttSckt->SendBuffer(pBuf,nLen);
            }
        }
    }

    return TRUE;
}

long CSttTestEngineServerData::ReturnBroadcastUserMngr(CSttSysState &oSysState)
{
    //广播所有用户
    oSysState.m_strRetType = SYS_STATE_RETTYPE_USERMNGR;
    m_pSttTestClientUserMngr->GenerateSysState(oSysState);
    return ReturnSysStateToChildren(NULL,&oSysState);
}

long CSttTestEngineServerData::ReturnGetSocketConnect(CSttSysState &oSysState)
{
    CSttSysState oOwnSysState;
    m_pSttTestClientUserMngr->GenerateSysState(oOwnSysState);
    oSysState.m_strID = STT_CMD_TYPE_DEBUG_GetSocketConnect;
    oOwnSysState.Set_ExecStatus_Success();

    oSysState.AppendParas(oOwnSysState);
    return SendSysState(&oSysState);
}

CSttSocketDataBase *CSttTestEngineServerData::FindSocketByAuthority(const CString &strAuthorityID)
{
    ASSERT(m_pSttTestClientUserMngr != NULL);

    CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindHasAuthority(strAuthorityID);
    if (pUser == NULL)
    {
        return NULL;
    }

    return pUser->m_pRefSttSckt;
}

#ifdef _PSX_QT_LINUX_
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#endif

//TestServer登录
long CSttTestEngineServerData::Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{//登录失败，则点对点返回，成功则广播
#ifndef _STT_NOT_IN_TEST_SERVER_
    if (oSysCmd.m_strTestor == STT_SOFT_ID_RECORD)
    {//录波登录
        m_pSttTestClientUserMngr->DeleteUserByRefSocket(pClientSocket);
        g_oSttRcdSendSocket.AttatchSocketDatabase(pClientSocket);
        g_oSttRcdSendSocket.CreateRcdSendThread();
        return 0;
    }
    if (oSysCmd.m_strTestor == STT_SOFT_ID_COMTRADE)
    {//故障回放登录
        m_pSttTestClientUserMngr->DeleteUserByRefSocket(pClientSocket);
        g_oSttComtradeRcvSocket.AttatchSocketDatabase(pClientSocket);
        return 0;
    }
    if (oSysCmd.m_strTestor == STT_SOFT_ID_COMTRADECONTRL)
    {//故障回放控制登录
        if(g_pReplayTestSocket != NULL)
        {
            g_pReplayTestSocket->Close();
        }
        g_pReplayTestSocket = pClientSocket;

        CSttSysState oSysState;
        oSysState.UpdateSysStateHead(&oSysCmd);
        oSysState.Set_ExecStatus_Success();
        pClientSocket->SendSysState(&oSysState);
        return 0;
    }
#endif

    CSttTestClientUser *pUser = User_Login(pClientSocket, oSysCmd);

    //生成应答命令返回
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);

    if(pUser != NULL)
    {
        oSysState.Set_ExecStatus_Success();
        oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, pUser->GetIDTest());
#ifdef _PSX_QT_LINUX_

        CDataGroup oDevAttrsGroup;
        oDevAttrsGroup.m_strName=_T("装置属性");
        oDevAttrsGroup.m_strID=_T("DeviceAttrs");
        oDevAttrsGroup.m_strValue=_T("");
        STT_DEVICE_ATTRS oDeviceAttrs=g_theDeviceSystemParameter->m_oDeviceAttrs;
        oDevAttrsGroup.AddNewData(_T("型号"),_T("Model"),_T("string"),oDeviceAttrs.m_strDeviceName);
        oDevAttrsGroup.AddNewData(_T("序列号"),_T("SN"),_T("string"),oDeviceAttrs.m_strSN);
        CString strFre;
        strFre.AppendFormat(_T("%.3f"),oDeviceAttrs.m_fBaseFre);
        oDevAttrsGroup.AddNewData(_T("额定频率"),_T("Fnom"),_T("float"),strFre);
        oDevAttrsGroup.AddNewData(_T("生产厂家"),_T("Factory"),_T("Factory"),oDeviceAttrs.m_strFactory);
        oDevAttrsGroup.AddNewData(_T("生产日期"),_T("DateFac"),_T("DateProduce"),oDeviceAttrs.m_strDateProduce);
        oDevAttrsGroup.AddNewData(_T("TestServer名称"),_T("AppName"),_T("AppName"),oDeviceAttrs.m_strAppName);
        oDevAttrsGroup.AddNewData(_T("驱动名称"),_T("DriverName"),_T("DriverName"),oDeviceAttrs.m_strDriverName);
        oDevAttrsGroup.AddNewData(_T("TestServer版本"),_T("AppVer"),_T("AppVersion"),oDeviceAttrs.m_strAppVer);
        oDevAttrsGroup.AddNewData(_T("主板版本"),_T("FpgaVer"),_T("FPGAVersion"),oDeviceAttrs.m_strFPGAVer);
        oDevAttrsGroup.AddNewData(_T("驱动版本"),_T("DriverVer"),_T("DriverVersion"),oDeviceAttrs.m_strDriverVer);
        oSysState.AddNewParas(&oDevAttrsGroup);
#endif
    }
    else
    {
        oSysState.Set_ExecStatus_Failure();
    }

    pClientSocket->SendSysState(&oSysState);	//应答自身登录信息

    if (pUser != NULL)
    {
        ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttTestEngineServerData::Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //更新用户链表
    DWORD nIDTester = 0;
	CString strSoftID;
    oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);
	oSysCmd.GetParasDataValueByID(ID_STT_USER_ATTR_id_soft, strSoftID);
	m_pSttTestClientUserMngr->DeleteUserByIDTest(nIDTester,strSoftID);
    //生成应答命令返回
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, nIDTester);
    pClientSocket->SendSysState(&oSysState);	//应答自身登录信息

    ReturnBroadcastUserMngr(oSysState);

    //客户端保证，发送Logout之前权限都已释放
    //退出登录或断链，检查是否停止测试
    //	CheckStopTestAfterRelease(pClientSocket);

    return 1;
}

long CSttTestEngineServerData::Process_Cmd_System_Request(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    long nRet = AuthorityToUser(oSysCmd,TRUE,FALSE);
    if (nRet == 0)
    {
        return pClientSocket->RetFailureSysState(&oSysCmd);
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AppendParas(oSysCmd);
    pClientSocket->SendSysState(&oSysState);

    if (nRet == 2)
    {
        ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttTestEngineServerData::Process_Cmd_System_Authority(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    long nRet = AuthorityToUser(oSysCmd,FALSE,FALSE);
    if (nRet == 0)
    {
        return pClientSocket->RetFailureSysState(&oSysCmd);
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AppendParas(oSysCmd);
    pClientSocket->SendSysState(&oSysState);

    if (nRet == 2)
    {
        ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttTestEngineServerData::Process_Cmd_System_LiveUpdate(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
    CSttParas *pParas = oSysCmd.GetSttParas();

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.m_strRetType = SYS_STATE_RETTYPE_REPLY;

    //2020-10-31  lijunqing 将更新部分的代码集中到liveupdate模块下面
    //避免liveupdate模块修改对基础模块的修改
    BOOL bRet = stt_validate_cmd_liveupdate(pParas);
    if (bRet)
    {
        oSysState.Set_IsSuccess(TRUE);
    }
    else
    {
        oSysState.Set_IsSuccess(FALSE);
    }

    //return cmd
    pClientSocket->SendCmd(&oSysState);

    if (bRet)
    {
        stt_process_cmd_liveupdate(pParas);
    }

#endif

    return 1;
}

//2020-12-05  lijunqing add
BOOL CSttTestEngineServerData::Cmd_System_GetFilePath(CSttSystemCmd &oSysCmd, CString &strFullPath, CString &strRelPath)
{
    CSttParas *pSttParas = oSysCmd.GetSttParas();
    CString strFileName, strFilePath;

    if (pSttParas->GetDataValue(XPARA_ID_Path, strRelPath))
    {
        strFullPath = _P_GetSystemPath();
        strFullPath += strRelPath;
        return TRUE;
    }

    BOOL b1 = pSttParas->GetDataValue(STT_CMD_PARA_FILE_NAME, strFileName);
    BOOL b2 = pSttParas->GetDataValue(STT_CMD_PARA_FILE_PATH, strFilePath);

    if (b1 && b2)
    {
        CString strChar = strFilePath.Left(1);

        if (strChar == _T("/") || strChar == _T("\\"))
        {
            strRelPath = strFilePath + strFileName;
        }
        else
        {
            strRelPath.Format(_T("%s/%s"), strFilePath .GetString(),  strFileName.GetString());
        }

        strFullPath = _P_GetSystemPath();
        strFullPath += strRelPath;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

long CSttTestEngineServerData::Process_Cmd_System_DownFile(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CString strSrcFilePath, srtRelPath;
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.m_strRetType = SYS_STATE_RETTYPE_REPLY;

    if (!Cmd_System_GetFilePath(oSysCmd, strSrcFilePath, srtRelPath))
    {
        oSysState.Set_IsSuccess(FALSE);
        oSysState.Set_ExecStatus_Failure();
        oSysState.Set_ErrCmd(TRUE);
        m_pSttTestClientUserMngr->SendSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

        return 0;
    }

    if (!IsFileExist(strSrcFilePath))
    {
        oSysState.Set_ExecStatus_Failure();
        oSysState.Set_DataNotExist(srtRelPath);
        m_pSttTestClientUserMngr->SendSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
        return 0;
    }

    oSysState.Set_ExecStatus_Success();
    m_pSttTestClientUserMngr->SendSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    pClientSocket->SendFile(strSrcFilePath,srtRelPath,g_nFileCmdTimeOut,NULL);

    return 0;
}

//设置参数
/*
<sys-cmd name="" id="SetSysConfig" testor="TEST$LOCAL" >
    <paras>
        <data id="use-zip" value="0" />【数据传输时，是否使用压缩】
        <data id="ver-zip" value="zip 1.0" />【压缩工具的版本】
        【当有多个不同的GateWay时，请设置Metric节点[1,100]。否则，可以没有此节点】 20220526 zhoulei
        <group name="SubIP1" id="SubIP1" data-type="SubIP" >【设置子网IP】
            <data id="IP" value="192.168.1.100" />
            <data id="mask" value="255.255.255.0" />
            <data id="GateWay" value="192.168.1.1" />
            <data id="Metric" value="1" />【需要上网的Metric值要最小，可以是'1'。'0'预留给DHCP】
        </group>
    </paras>
</sys-cmd>
*/
long CSttTestEngineServerData::ProcessCmd_SetSysConfig(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
    CSttParas* pParas = oSysCmd.GetSttParas();
    long nRet = 0 ;

    //2021-01-08 zhoulei
    CExBaseList listGroup;
    pParas->SelectAllGroups(listGroup, STT_SYS_DATA_ID_SubIP);

    if (listGroup.GetCount() > 0)
    {
        POS pos = listGroup.GetHeadPosition();
        CDataGroup *p = NULL;
        CStringArray astrIP, astrMask, astrGateWay;
        CString strIP, strMask,strGateWay;
        long nMetric[20];
        long nCount = 0;
        BOOL bRet;

        while (pos != NULL)
        {
            p = (CDataGroup*)listGroup.GetNext(pos);

            if (!p->GetDataValue(STT_SYS_DATA_ID_IP, strIP))
            {
                continue;
            }

            p->GetDataValue(STT_SYS_DATA_ID_mask, strMask);
            p->GetDataValue(STT_SYS_DATA_ID_GateWay, strGateWay);
            bRet = p->GetDataValue(STT_SYS_DATA_ID_Metric, nMetric[nCount]);
            if(!bRet)
                nMetric[nCount] = -1;
            astrIP.Add(strIP);
            astrMask.Add(strMask);
            astrGateWay.Add(strGateWay);
            nCount++;
        }

        listGroup.RemoveAll();

        if (nCount > 0)
        {
            stt_net_set_ip(astrIP, astrMask,2);//20220526 zhoulei '1'预留给DHCP功能了  stt_net_dhcp();
            stt_net_set_gateway(astrGateWay,nMetric);
        }

        nRet = nCount;
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);

    if (nRet == 0)
    {
        oSysState.Set_ExecStatus_Failure();
    }
    else
    {
        oSysState.Set_ExecStatus_Success();
    }

    return pClientSocket->SendSysState(&oSysState);
#else
	return 0;
#endif
}

//查询，返回信息
/*
<sys-state name="" id="GetSysConfig" mater-host="">
    <paras name="" id="">
        <data id="use-zip" value="0" />【数据传输时，是否使用压缩】
        <data id="ver-zip" value="zip 1.0" />【压缩工具的版本】
        <group name="DeviceIP" id="DeviceIP" data-type="DeviceIP" >【测试仪装置IP】
            <data id="IP" value="192.168.1.100" />
            <data id="mask" value="255.255.255.0" />
        </group>
        <group name="SubIP1" id="SubIP1" data-type="SubIP" >【子网IP】
            <data id="IP" value="192.168.1.100" />
            <data id="mask" value="255.255.255.0" />
        </group>
    </paras>
<sys-state>
*/
long CSttTestEngineServerData::ProcessCmd_GetSysConfig(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    CSttParas* pParas = oSysState.GetSttParas();

    //2021-01-08  zhoulei
    //	stt_net_get_ip(pParas);

    oSysState.Set_ExecStatus_Success();
    return pClientSocket->SendSysState(&oSysState);
}

/*
<sys-cmd name="" id="GetDirs" testor="" >
    <paras name="" id="">
        <data id="RootPath" value="" />  【目标路径】
        <data id="GetSubDirs" value="1" />  【是否获取子文件夹】
        <data id="GetFiles" value="1" />  【是否获取文件】
        <data id="FilesDef" value="1" >  【查询文件类型】
            <value id="file-type" value="gbxml" />  【文件后缀】
        </data id>
    </paras>
</sys-cmd>
*/
// 	//2022-3-23  lijunqing
// #define STT_CMD_PARA_FILE_RootPath             _T("RootPath")
// #define STT_CMD_PARA_FILE_GetSubDirs             _T("GetSubDirs")
// #define STT_CMD_PARA_FILE_GetFiles             _T("GetFiles")
// #define STT_CMD_PARA_FILE_FileTypes            _T("FileTypes")
// #define STT_CMD_PARA_FILE_FileType            _T("FileType")
long CSttTestEngineServerData::Process_Cmd_System_GetDirs(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    CSttParas* pParas = oSysCmd.GetSttParas();

    CString strRootPath, strFileType;
    long nGetSubDirs=0, nGetFiles=0;

    stt_GetDataValueByID(pParas, STT_CMD_PARA_FILE_RootPath, strRootPath);
    stt_GetDataValueByID(pParas, STT_CMD_PARA_FILE_GetSubDirs, nGetSubDirs);
    stt_GetDataValueByID(pParas, STT_CMD_PARA_FILE_GetFiles, nGetFiles);
    stt_GetDataValueByID(pParas, STT_CMD_PARA_FILE_FileType, strFileType);

    if (strRootPath.GetLength() == 0)
    {
        oSysState.Set_ExecStatus_Failure();
        return pClientSocket->SendSysState(&oSysState);
    }

    CString strPath = _P_GetSystemPath();
    strPath += strRootPath;

    pParas = oSysState.GetSttParas();
    pParas->SearchFiles(strPath, nGetSubDirs, nGetFiles, strFileType);

    oSysState.Set_ExecStatus_Success();
    return pClientSocket->SendSysState(&oSysState);
}

void CSttTestEngineServerData::LogDebugInfor(const CString &strInfor)
{
    if (m_pSttTestClientUserMngr == NULL)
    {
        return;
    }

    CSttSysState oSysState;
    oSysState.m_strRetType = SYS_STATE_RETTYPE_LOG;
    CSttMsgs *pMsgs = oSysState.GetSttMsgs();
    pMsgs->AddMsg(SYS_STATE_RETTYPE_LOG, strInfor);
    ReturnSysStateToChildren(NULL, &oSysState);
}


long CSttTestEngineServerData::Process_Debug_ConfigDebug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd)
{
    //兼容 两个设置关键字 2020-10-18  lijunqing
    oDebugCmd.GetParasDataValueByID(STT_CMD_PARA_LogServerDebugInfor,  g_nSttLogServerDebugInfor);
    oDebugCmd.GetParasDataValueByID(STT_CMD_PARA_LogDebugInfor,  g_nSttLogServerDebugInfor);
    oDebugCmd.GetParasDataValueByID(STT_CMD_PARA_LogServerSpyAllCmd,  g_nSttLogServerSpyAllCmd);

    return 0;
}

