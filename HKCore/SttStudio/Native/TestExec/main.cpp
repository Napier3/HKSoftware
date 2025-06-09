#include "../Module/SttNativeTestMainApp.h"


#include "QTimer"
#include <QDebug>

#include "XTestTimer.h"
#include "signal.h"

static unsigned int Test_WinThreadFuncProc(void *pParam)
{
    while (true)
    {
        qDebug()<<"******** Test_WinThreadFuncProc *****************";
        usleep(1000000);
    }

/*

    //2020-11-29  lijunqing  监视所有命令报文
    if (g_nSttLogServerSpyAllCmd)
    {

    }

    //2020-11-29  lijunqing  监视所有命令报文
    if (g_nSttLogServerSpyAllCmd)
    {
        if (nCmdType != STT_CMD_TYPE_DEBUG)
        {
            SendToAllUser(STT_SOFT_ID_DEBUG, pBuf, nLen);
        }
    }

    */
}

#include "../../../Module/XfileMngrBase/XFileFindEx.h"
#include "../../../AutoTest/Module/XLanguageResourceAts.h"
#include <QSharedMemory>
//CSttNativeTestMainApp* g_MainApp = NULL;
int main(int argc, char *argv[])
{
    QSharedMemory *shareMem = new QSharedMemory(QString("Stt_TestMainCore"));

        volatile short i = 2;
        while (i--)
        {
            if(shareMem->attach(QSharedMemory::ReadOnly))
            {
                shareMem->detach();
            }
        }

        if(! shareMem->create(1))
        {//
    //		qDebug() << "Error: Stt_TestCtrlCntr_Native is exist !";
            if(shareMem->isAttached())
               shareMem->detach();
            delete shareMem;
            return 0;
        }

//        system("nohup  /mnt/Stt/Bin/SttTestMainCore >/dev/null  1>/mnt/Stt/Bin/log.txt &");
    //ignor SIGPIPE (send error after socket disconnect)
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGPIPE);
    sigaddset(&set,SIGSTOP);
    sigprocmask(SIG_BLOCK,&set,NULL);

    CSttNativeTestMainApp  a(argc, argv);

//#ifdef _PSX_OS_CENTOS_
//   system("systemctl stop firewalld");  //关闭防火墙
//#endif

    //g_MainApp->m_otime = (int)clock();
    a.InitSttTestServerBaseApp();
#ifndef _USE_NO_GUI_
    a.setQuitOnLastWindowClosed(false);
   a.setDesktopSettingsAware(false);
#endif


    //2022-3-25  lijunqing  测试语言资源是否正确
    CString str1 = g_sLangTxt_IgnoreAbnormal;
    CString str2 = _T("忽略异常");


    long nTick = GetTickCount();
    nTick = GetTickCount();

    //测试时钟
    //CTestTimerEx oCTestTimerEx;

    //测试函数线程
    //CWinThread *pThread = AfxBeginThread(Test_WinThreadFuncProc, NULL);
    //pThread->ResumeThread();

    //2020-12-2  lijunqing Test CXFileFindEx
/*    CString strPath, strFile, strFilePath, strTitle;
    strPath = _P_GetTemplatePath();
    CXFileFindEx oFind;

    oFind.AddFileFilter("*.gbexe");
    oFind.FindFile(strPath);

    while (oFind.FindNextFile())
    {
        strFile = oFind.GetFileName();
        strFilePath = oFind.GetFilePath();
        strTitle = oFind.GetFileTitle();
    }
*/
    int nRet = a.exec();
    a.ExitSttTestServerBaseApp();

    if(shareMem->isAttached())
       shareMem->detach();
    delete shareMem;

           /* CString strText;
            strText = "abc测试中文123";
            char pszText[32], pszText2[32], pszText3[32];
            QByteArray data = strText.toAscii();
            char *pTemp = data.data();
            strcpy(pszText, pTemp);

            QByteArray data2 = strText.toLatin1();
            char *pTemp2 = data2.data();
             strcpy(pszText2, pTemp2);

             std::string str = strText.toStdString();
             const char *pTemp3 = str.c_str();
              strcpy(pszText3, pTemp3);

              CString_to_char(strText, pszText3);
              */

    return nRet;
}

