#ifndef _CAxSmartTestApp_H
#define _CAxSmartTestApp_H

#include "../../../Module/Log/LogPrint.h"
#include "../../../AutoTest/Module/TestControl/SmartTestBaseApp.h"
#include "../Engine/SttNativeTestEngine.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../SttTestAppConfig/SttTestAppGateWayCfg.h"

//2020-11-25  lijunqing
class CAxSmartTestMainWnd : public CWnd
{
public:
    CAxSmartTestMainWnd();
    virtual ~CAxSmartTestMainWnd();

public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
    virtual void OnWndTimer(unsigned int nIDEvent);
};

class CAxSmartTestApp : public CLogBase, public CSmartTestBaseApp, public CSttTestMsgViewInterface
{
public:
    CAxSmartTestApp();
    virtual ~CAxSmartTestApp();

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
    CAxSmartTestMainWnd *m_oMainWnd;
    CSttTestAppCfg m_oSttTestAppCfg; //2022-1-3  lijunqing
};
#endif // _CAxSmartTestApp_H
