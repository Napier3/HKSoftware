#ifndef _PpSttIotEngineClientWidgetBase_H_
#define _PpSttIotEngineClientWidgetBase_H_

#include <QDialog>
#include <QFont>
#include "../../../../Module/API/StringApi.h"

#include "../PpSttIotEngineClientApp.h"
#include "../../../../testNanomsg/testNanomsg/msgqueue/include/msgQueue.h"
#include "../../../../IotProtoClient/Module/NanoCmd/PpNanoMsgCmd.h"
#include "PpSttIotEngineClientAppWnd.h"

#include "PpSttIotEngineClientWidget.h"


class QPpSttIotEngineClientWidgetNano : public QPpSttIotEngineClientWidget
{
    Q_OBJECT

public:
    explicit QPpSttIotEngineClientWidgetNano(QWidget *parent = 0);
    virtual ~QPpSttIotEngineClientWidgetNano();

    CMsgQueue m_msgQueue;
    long m_nCloseCount;

    virtual void OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam);
    virtual void OnEngineSystemMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam);

public:
    void Nano_Cmd_Init(CPpNanoMsgCmd *pCmd);
    void Nano_Cmd_UnInit(CPpNanoMsgCmd *pCmd);
    void Nano_Cmd_GetData(CPpNanoMsgCmd *pCmd);
    void Nano_Cmd_SetData(CPpNanoMsgCmd *pCmd);
    void Nano_Cmd_ShowWnd(CPpNanoMsgCmd *pCmd);
    void Send_NanoCmdRet(CPpNanoMsgCmdRet *pCmdRet);
    void Ret_NanoCmd_Failed(CPpNanoMsgCmd *pCmd, const CString &strDesc);
    void Ret_NanoCmd_Succ(CPpNanoMsgCmd *pCmd, const CString &strDesc);
    void Iot_Init_CmdRet(CPpNanoMsgCmdRet &oCmdRet, CPpSttIotDeviceClient *pDevice, bool bSucc, const CString &strDesc);

    void Iot_OnConnectMsg(CPpSttIotDeviceClient *pDevice, bool bSucc);
    void Iot_OnCmdFinish_Ret(CPpSttIotDeviceClient *pDevice, CDvmDataset *pDataset);
    void Iot_OnEngineSys_Ret(CPpSttIotDeviceClient *pDevice, bool bSucc);

private:
    static void msgRuningProc(char* buf, int nLen, void* context);
    void msgRuning(char* buf, int nLen);

signals:
    void sigRecvDataArrive(char *buf, long nLen);

private slots:
    void slotDataArrive(char *buf, long nLen);
    void closeEvent ( QCloseEvent * e );

};

QPpSttIotEngineClientWidgetNano* CreateEngineClientWidgetNano();
void ReleaseEngineClientWidgetNano();


#endif // _PpSttIotEngineClientWidgetBase_H_
