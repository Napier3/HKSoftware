#include "PpSttIotEngineClientWidgetNano.h"

#include <QMessageBox>

#include "../../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "logoutputwidget.h"

extern CPpSttIotEngineClientApp *g_theIotEngineApp;
QLogOutputWidget *g_pOutputWidget = NULL;
/*
CONFIG += debug_and_release
CONFIG(debug, debug|release){
    LIBS *= -L$$PWD/libs/msgqueue/lib/x64/debug -lmsgQueue
}else{
    LIBS *= -L$$PWD/libs/msgqueue/lib/x64/release -lmsgQueue
}

INCLUDEPATH += \
    $$PWD/libs/msgqueue/include \
 * */


class CPpSttIotDeviceClientNano : public CPpSttIotDeviceClient
{
public:
    CPpSttIotDeviceClientNano()
    {
        m_pCurrNanoCmd = NULL;
    }
    virtual ~CPpSttIotDeviceClientNano()
    {
        m_oEngineMsgWnd.DestroyWindow();
        FreeNanoCmd();
    }

    void FreeNanoCmd()
    {
        if (m_pCurrNanoCmd != NULL)
        {
            delete m_pCurrNanoCmd;
            m_pCurrNanoCmd = NULL;
        }
    }

public:
    CPpNanoMsgCmd *m_pCurrNanoCmd;
    QPpSttIotEngineClientWidgetWnd m_oEngineMsgWnd;

    void ExecNanoCmd(CPpNanoMsgCmd *pCmd)
    {
        FreeNanoCmd();

        m_pCurrNanoCmd = pCmd;

        //if (pCmd->m_strfunCode == )
    }
};

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineClientWidgetNano
QPpSttIotEngineClientWidgetNano::QPpSttIotEngineClientWidgetNano(QWidget *parent) :
    QPpSttIotEngineClientWidget(parent)
{
    m_nCloseCount = 0;
    connect(this, SIGNAL(sigRecvDataArrive(char*, long)), this, SLOT(slotDataArrive(char*, long)));

    int ret;
    QString strChnFlag = "uiEngineCtrl";
    ret = m_msgQueue.CreateMsgQueue(MSG_MODE_CLIENT
                  , strChnFlag.isEmpty() ? nullptr : strChnFlag.toStdString().c_str()
                  ,1000, msgRuningProc, this);

    Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    if (ret)
    {

    }

    g_pOutputWidget = new QLogOutputWidget(this);
    g_pOutputWidget->show();
}

QPpSttIotEngineClientWidgetNano::~QPpSttIotEngineClientWidgetNano()
{
    m_msgQueue.DestroyMsgQueue();
    g_pOutputWidget->deleteLater();
}


void QPpSttIotEngineClientWidgetNano::OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam)
{
    if (lParam == engineCommError)
    {
            CLogPrint::LogString(XLOGLEVEL_TRACE, "engineCommError....");
    }
    else  //lParam == engineCommFinish
    {//执行成功，显示相关联的数据集
        SaveDatasToLocalDvm(pIotDevice);
        CDvmDataset *pDataset = pIotDevice->GetCurrDataset();
        Iot_OnCmdFinish_Ret(pIotDevice, pDataset);
    }
}

void QPpSttIotEngineClientWidgetNano::OnEngineSystemMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam)
{
    if (pIotDevice == NULL)
    {
        return;
    }

    switch (lParam)
    {
    case engineConnectDeviceFailed:
        Iot_OnEngineSys_Ret(pIotDevice, false);
        pIotDevice->DisConnectForClose(NULL);
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Connect Device Failed"));
        break;

    case engineConnectDeviceSuccessful:
        Iot_OnEngineSys_Ret(pIotDevice, true);
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Connect Device Successful"));
        break;

    case engineCommError:
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommError"));
        break;

    case engineException:
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Exception"));
        break;

    default:
        break;
    }

    EnableBtns();
}

void QPpSttIotEngineClientWidgetNano::msgRuningProc(char* buf, int nLen, void* context)
{
    QPpSttIotEngineClientWidgetNano* pThis = (QPpSttIotEngineClientWidgetNano*)context;
    char *pNewBuffer = new char [nLen + 1];
    memcpy(pNewBuffer, buf, nLen);
    pNewBuffer[nLen] = 0;
    pThis->msgRuning(pNewBuffer, nLen);
}

void QPpSttIotEngineClientWidgetNano::msgRuning(char* buf, int nLen)
{
    //requestResponse* rr = (requestResponse*)buf;
    //QString strDat = QString::fromStdString(std::string(buf, nLen));
    emit sigRecvDataArrive(buf, nLen);
}


void QPpSttIotEngineClientWidgetNano::slotDataArrive(char *buf, long nLen)
{
    CPpNanoMsgCmd *pCmd = new CPpNanoMsgCmd();

    pCmd->SetXml_UTF8(buf, nLen, CPpNanoMsgConfigXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
    delete buf;

    if (pCmd->m_strfunCode == NANO_CMD_Init)
    {
        Nano_Cmd_Init(pCmd);
    }
    else if (pCmd->m_strfunCode == NANO_CMD_GetData)
    {
        Nano_Cmd_GetData(pCmd);
    }
    else if (pCmd->m_strfunCode == NANO_CMD_SetData)
    {
        Nano_Cmd_SetData(pCmd);
    }
    else if (pCmd->m_strfunCode == NANO_CMD_UnInit)
    {
        Nano_Cmd_UnInit(pCmd);
    }
    else if (pCmd->m_strfunCode == NANO_CMD_ShowWnd)
    {
        Nano_Cmd_ShowWnd(pCmd);
    }
    else
    {
        delete pCmd;
    }
}
void QPpSttIotEngineClientWidgetNano::Nano_Cmd_Init(CPpNanoMsgCmd *pCmd)
{
    CString strDeviceSN = pCmd->GetDeviceSN();

    if (strDeviceSN.GetLength() == 0)
    {
        CPpNanoMsgCmdRet oCmdRet;
        pCmd->InitCmdRet(oCmdRet);
        oCmdRet.m_strresult = "0";
        Send_NanoCmdRet(&oCmdRet);
    }
    else
    {
        CPpSttIotDeviceClientNano *pNewDevice = NULL;
        pNewDevice = (CPpSttIotDeviceClientNano*)g_theIotEngineApp->FindDeviceClient(strDeviceSN);
        CPpSttCommConfig oCommConfig;
        pCmd->m_pPara->GetPpSttCommConfig(oCommConfig);

        if (pNewDevice == NULL)
        {
            pNewDevice = new CPpSttIotDeviceClientNano();
            pNewDevice->m_strDeviceID = strDeviceSN;
            g_theIotEngineApp->CreateDevice(pNewDevice, (PSX_OBJ_ADDR)&pNewDevice->m_oEngineMsgWnd);
            pNewDevice->m_oEngineMsgWnd.m_pMainWidget = this;
            pNewDevice->m_oEngineMsgWnd.m_pIotDevice = pNewDevice;
        }

        char *pszBuffer = NULL;
        CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
        long nLen = oCommConfig.GetXml_UTF8(CDataMngrXmlRWKeys::g_pXmlKeys, &pszBuffer);
        CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

        if (nLen > 0)
        {
            g_pOutputWidget->LogString(XLOGLEVEL_DEBUG, pszBuffer);
            delete pszBuffer;
        }

        pNewDevice->InitCommConfig(&oCommConfig);
        pNewDevice->ConnectDevice();
        pNewDevice->ExecNanoCmd(pCmd);
    }
}

void QPpSttIotEngineClientWidgetNano::Nano_Cmd_UnInit(CPpNanoMsgCmd *pCmd)
{
    CString strDeviceSN = pCmd->GetDeviceSN();
    CPpSttIotDeviceClientNano *pDevice = (CPpSttIotDeviceClientNano*)g_theIotEngineApp->FindDeviceClient(strDeviceSN);

    if (pDevice == NULL)
    {
        Ret_NanoCmd_Failed(pCmd, "Device not exiset : " +strDeviceSN);
    }
    else
    {
        g_theIotEngineApp->CloseDevice(pDevice);
        Ret_NanoCmd_Succ(pCmd, "");
        DeleteIotDevice(pDevice);
    }

    delete pCmd;
}

void QPpSttIotEngineClientWidgetNano::Nano_Cmd_GetData(CPpNanoMsgCmd *pCmd)
{
    CString strDeviceSN = pCmd->GetDeviceSN();
    CString strDatasetPath = pCmd->GetDatasetPath();
    CPpSttIotDeviceClientNano *pDevice = (CPpSttIotDeviceClientNano*)g_theIotEngineApp->FindDeviceClient(strDeviceSN);

    if (pDevice == NULL)
    {
        Ret_NanoCmd_Failed(pCmd, "Device not exiset : " +strDeviceSN);
        delete pCmd;
    }
    else
    {
        pDevice->ExecNanoCmd(pCmd);
        pDevice->ReadDataset(strDatasetPath);
    }
}

void QPpSttIotEngineClientWidgetNano::Nano_Cmd_SetData(CPpNanoMsgCmd *pCmd)
{
    CString strDeviceSN = pCmd->GetDeviceSN();
    CString strDatasetPath = pCmd->GetDatasetPath();
    CDvmDataset *pDataset = pCmd->GetDataset();
    CPpSttIotDeviceClientNano *pDevice = (CPpSttIotDeviceClientNano*)g_theIotEngineApp->FindDeviceClient(strDeviceSN);

    if (pDevice == NULL)
    {
        Ret_NanoCmd_Failed(pCmd, "Device not exiset : " +strDeviceSN);
        delete pCmd;
    }
    else
    {
        if (pDataset == NULL)
        {
            Ret_NanoCmd_Failed(pCmd, "Dataset not exiset : " +strDatasetPath);
            delete pCmd;
        }
        else
        {
             pDevice->ExecNanoCmd(pCmd);
             pDevice->WriteDataset(pDataset);
        }
    }
}

void QPpSttIotEngineClientWidgetNano::Nano_Cmd_ShowWnd(CPpNanoMsgCmd *pCmd)
{
    CString strDeviceSN = pCmd->GetDeviceSN();
    CPpSttIotDeviceClientNano *pDevice = (CPpSttIotDeviceClientNano*)g_theIotEngineApp->FindDeviceClient(strDeviceSN);
    m_pPpDeviceClient = pDevice;

    if (pCmd->m_nShow == 1)
    {
        show();
    }
    else
    {
        hide();
    }

    delete pCmd;
    EnableBtns();
}

void QPpSttIotEngineClientWidgetNano::Iot_OnConnectMsg(CPpSttIotDeviceClient *pDevice, bool bSucc)
{
    CPpSttIotDeviceClientNano *pNanoDevice = (CPpSttIotDeviceClientNano*)pDevice;
    CPpNanoMsgCmdRet oCmdRet;
    pNanoDevice->m_pCurrNanoCmd->InitCmdRet(oCmdRet);

    if (bSucc)
    {
        oCmdRet.m_strresult = "1";
    }
    else
    {
        oCmdRet.m_strresult = "0";
    }

    Send_NanoCmdRet(&oCmdRet);
}

void QPpSttIotEngineClientWidgetNano::Iot_OnCmdFinish_Ret(CPpSttIotDeviceClient *pDevice, CDvmDataset *pDataset)
{
    CPpSttIotDeviceClientNano *pNanoDevice = (CPpSttIotDeviceClientNano*)pDevice;

    CPpNanoMsgCmdRet oCmdRet;

    if (pNanoDevice->m_pCurrNanoCmd != NULL)
    {
        pNanoDevice->m_pCurrNanoCmd->InitCmdRet(oCmdRet);
    }

    if (pDataset != NULL)
    {
        oCmdRet.SetDvmDataset(pDataset);
    }

    Send_NanoCmdRet(&oCmdRet);
}

void QPpSttIotEngineClientWidgetNano::Iot_OnEngineSys_Ret(CPpSttIotDeviceClient *pDevice, bool bSucc)
{
    CPpSttIotDeviceClientNano *pNanoDevice = (CPpSttIotDeviceClientNano*)pDevice;

    CPpNanoMsgCmdRet oCmdRet;

    if (pNanoDevice->m_pCurrNanoCmd != NULL)
    {
        pNanoDevice->m_pCurrNanoCmd->InitCmdRet(oCmdRet);
        Iot_Init_CmdRet(oCmdRet, NULL, bSucc, "");
    }
    else
    {
        Iot_Init_CmdRet(oCmdRet, pDevice, bSucc, "");
    }

    Send_NanoCmdRet(&oCmdRet);
}
void QPpSttIotEngineClientWidgetNano::Send_NanoCmdRet(CPpNanoMsgCmdRet *pCmdRet)
{
    char *buf = NULL;
    long nLen = 0;

    CPpNanoMsgConfigXmlRWKeys::IncXmlOnlyWrite_Id_Value(CPpNanoMsgConfigXmlRWKeys::g_pXmlKeys);
    nLen = pCmdRet->GetXml_UTF8(CPpNanoMsgConfigXmlRWKeys::g_pXmlKeys, &buf, 0, _JSON_TYPE_);
    CPpNanoMsgConfigXmlRWKeys::DecXmlOnlyWrite_Id_Value(CPpNanoMsgConfigXmlRWKeys::g_pXmlKeys);

    if (nLen > 0)
    {
        m_msgQueue.SendMsg(buf, nLen);
        delete buf;
    }
}

void QPpSttIotEngineClientWidgetNano::Ret_NanoCmd_Failed(CPpNanoMsgCmd *pCmd, const CString &strDesc)
{
    CPpNanoMsgCmdRet oCmdRet;
    pCmd->InitCmdRet(oCmdRet);
    oCmdRet.m_strresult = "0";
    oCmdRet.m_strdesc = strDesc;
    Send_NanoCmdRet(&oCmdRet);
}

void QPpSttIotEngineClientWidgetNano::Ret_NanoCmd_Succ(CPpNanoMsgCmd *pCmd, const CString &strDesc)
{
    CPpNanoMsgCmdRet oCmdRet;
    pCmd->InitCmdRet(oCmdRet);
    oCmdRet.m_strresult = "1";
    oCmdRet.m_strdesc = strDesc;
    Send_NanoCmdRet(&oCmdRet);
}

void QPpSttIotEngineClientWidgetNano::Iot_Init_CmdRet(CPpNanoMsgCmdRet &oCmdRet, CPpSttIotDeviceClient *pDevice, bool bSucc, const CString &strDesc)
{
    if (bSucc)
    {
        oCmdRet.m_strresult = "1";
    }
    else
    {
        oCmdRet.m_strresult = "0";
    }

    if (pDevice != NULL)
    {
        oCmdRet.SetDeviceDN(pDevice->m_strDeviceID);
    }

    oCmdRet.m_strdesc = strDesc;
}

void QPpSttIotEngineClientWidgetNano::closeEvent ( QCloseEvent * e )
{
    m_nCloseCount++;

    if( m_nCloseCount > 3)
    {
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

QPpSttIotEngineClientWidgetNano *g_theEngineClientWidgetNano= NULL;

QPpSttIotEngineClientWidgetNano* CreateEngineClientWidgetNano()
{
    if (g_theEngineClientWidgetNano != NULL)
    {
        return g_theEngineClientWidgetNano;
    }

    g_theEngineClientWidgetNano = new QPpSttIotEngineClientWidgetNano();
    g_theEngineClientWidgetNano->show();
    return g_theEngineClientWidgetNano;
}

void ReleaseEngineClientWidgetNano()
{
    if (g_theEngineClientWidgetNano == NULL)
    {
        return;
    }

    delete g_theEngineClientWidgetNano;
    g_theEngineClientWidgetNano = NULL;
}
