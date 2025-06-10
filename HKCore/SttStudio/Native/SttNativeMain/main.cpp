#include "XLangResource_SttNativeMain.h"
#include "SttNativeMainFrameLinux.h"
#include "SttNativeMainApplication.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../Module/API/StringConvertApi.h"
#include <qdebug.h>
#include <QTextCodec>
#include <QSharedMemory>
#include <QMessageBox>
#ifndef _USE_IN_IED_QT5
#include <QWSServer>
#endif
#include<QMainWindow>
#include<QApplication>
#ifdef _PSX_OS_CENTOS_
#include "QX11Info"
#endif

#ifndef _PSX_QT_LINUX_
#include "../../../Module/XMinidmp/XMinidmp.h"
#endif

#ifdef USE_Custom_CDateTime
#include "../../../Module/OSInterface/QT/CDateTime_QT.h"
#endif

int main(int argc, char *argv[])
{
    //唯一对象处理
    QSharedMemory *shareMem = new QSharedMemory(QString("SttNativeMain"));

    volatile short i = 2;
    while (i--)
    {
        if(shareMem->attach(QSharedMemory::ReadOnly))
        {
            shareMem->detach();
        }
    }

    if(! shareMem->create(1))
    {//已经创建，则返回错误
        qDebug() << "Error: Stt_TestCtrlCntr_Native is exist !";
        return 0;
    }

#ifdef USE_Custom_CDateTime
    CDateTime::CreateClientDataTime();
#endif

#ifndef _PSX_QT_LINUX_
    RunCrashHandler();
#endif

#ifdef _PSX_OS_CENTOS_
    Display *pDisplay = QX11Info::display();
    CSttNativeMainApplication oSttNativeMainApplication(pDisplay);
#else
    CSttNativeMainApplication oSttNativeMainApplication(argc,argv);
#endif
    oSttNativeMainApplication.InitSttMainApp(new CXLangResource_SttNativeMain());
    QSttNativeMainFrameLinux oSttNativeMainFrameLinux;
    g_pQSttWgtCmdExecTool->m_oStartTickCount.Enter();

    oSttNativeMainFrameLinux.show();
    //在脱机软件中隐藏光标
 #ifndef _USE_IN_IED_QT5    //xueyangfan 隐藏鼠标光标
 #ifdef _PSX_QT_LINUX_
 #ifndef _PSX_OS_CENTOS_
   QApplication::setOverrideCursor(Qt::BlankCursor);  
 #endif
 #endif
 #endif
    oSttNativeMainApplication.exec();

    if(shareMem->isAttached())
        shareMem->detach();
    delete shareMem;

#ifdef USE_Custom_CDateTime
    CDateTime::ReleaseClientDataTime();
#endif

    return 0;
}
