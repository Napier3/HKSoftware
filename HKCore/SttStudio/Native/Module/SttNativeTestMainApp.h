#ifndef CSttNativeTestMainApp_H
#define CSttNativeTestMainApp_H

#ifndef _USE_NO_GUI_
#include <QApplication>
#else
#include <QCoreApplication>
#endif
#include"../../Module/Log/LogPrint.h"
#include "../Module/Engine/SttNativeTestEngine.h"
#include "../../../AutoTest/Module/TestControl/SmartTestBaseApp.h"
#include "../Module/SttTestAppConfig/SttTestAppCfg.h"
#include "../Module/SttTestAppConfig/SttTestAppGateWayCfg.h"
#include "../../Module/OSInterface/QT/CXCtrl_QT_CWnd.h"
class CWnd;
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

//QCoreApplication
#ifndef _USE_NO_GUI_
class CSttNativeTestMainApp : public QApplication ,public CLogBase, public CSmartTestBaseApp, public CSttTestMsgViewInterface
#else
class CSttNativeTestMainApp : public QCoreApplication ,public CLogBase, public CSmartTestBaseApp, public CSttTestMsgViewInterface
#endif
{
public:
	CSttNativeTestMainApp(int &argc, char **argv);
    virtual ~CSttNativeTestMainApp();
    //qint64 m_otime;

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
    void Register();

public:
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);

signals:

public slots:


//2020-11-25  lijunqing
public:
    CSttNativeTestMainWnd m_oMainWnd;
    CSttTestAppCfg m_oSttTestAppCfg; //2022-1-3  lijunqing
};

//extern CSttNativeTestMainApp* g_MainApp;
#endif // CSttNativeTestMainApp_H
