#ifndef CSttNativeTestSvrRemoteApp_H
#define CSttNativeTestSvrRemoteApp_H

#include <QCoreApplication>
#include"../../../Module/Log/LogPrint.h"
#include "../../Module/Engine/SttNativeTestEngine.h"

//2020-11-25  lijunqing
class CSttNativeTestMainWnd : public CWnd
{
public:
    CSttNativeTestMainWnd();
    virtual ~CSttNativeTestMainWnd();

public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
    virtual void OnWndTimer(unsigned int nIDEvent);
};

class CSttNativeTestSvrRemoteApp : public QCoreApplication ,public CLogBase
{
public:
	CSttNativeTestSvrRemoteApp(int &argc, char **argv);
    virtual ~CSttNativeTestSvrRemoteApp();

    virtual BOOL ats_IsRegisterTrue(BOOL bShowMsg, BOOL bFromTest=FALSE)
    {
        return true;
    }

    virtual void FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError);
    virtual void FireTestFinishMessage(BOOL bMttTaskFinish=FALSE);
    virtual void CreateReportApp();

public:
	virtual void InitSttTestServerBaseApp();
	virtual void ExitSttTestServerBaseApp();

public:
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);

signals:

public slots:


//2020-11-25  lijunqing
public:
    CSttNativeTestMainWnd m_oMainWnd;
};

#endif // CSttNativeTestSvrRemoteApp_H
