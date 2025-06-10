//SttLiveUpdateCoreBaseApp.cpp

#include "stdafx.h"
#include "SttLiveUpdateCoreBaseApp.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/System/StringTokenizer.h"
//#include "../Module/SttDevice/SttDriverOper.h"
#include "../Module/SttTest/Common/tmt_adjust_sys_parameter.h"
#include "SttLiveUpdateServerEngine.h"
#ifndef _USE_NO_GUI_
#include "../OSInterface/QT/XMessageBox.h"
#endif

#ifndef NOT_USE_XLANGUAGE
#include "../Module/SttTest/Common/tmt_adjust_sys_para_trans.h"
#include "../../../AutoTest/Module/XLanguageResourceAts.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#endif

#ifdef DEBUG_MODE
#include <QDebug>
#endif

#include "QDir"
#include "QEventLoop"
#include "QTimer"
#include "QTextCodec"

#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>		//SIGIO
#include <QStringList>

char g_strDebug[512];

CSttLiveUpdateCoreBaseApp* g_theCoreBaseApp = NULL;
Drv_BoardVersion g_oBoardinfo;
int g_nFlag = 0; //0开始 -1失败 1成功
int g_count = 0;
CString g_strFPGAFile;
int g_fd;

void fasync_handler(int num)
{
	CString strInfo;
	int nRet = ioctl(g_fd,0x502,0);
	if(nRet == SPI_FLAG_EREASE_FINISH)
	{
		qDebug()<<"the FPGA CLEAR";

		strInfo = _T("FPGA存储器已清除");
		g_theCoreBaseApp->SendUpdateInfo(strInfo);
	}
	else if(nRet == SPI_FLAG_EREASE_FAILED)
	{
		qDebug()<<"the FPGA CLEAR failed";

		strInfo = _T("FPGA存储器清除失败");
		g_theCoreBaseApp->SendUpdateInfo(strInfo);
		g_nFlag = -1;
	}
	else if(nRet == SPI_FLAG_IN_WRITING )
	{
		qDebug()<<"the FPGA is writing";

		g_count++;
		if(g_count>=5)   //每5秒读一次百分比状态
		{
            int nPercent = ioctl(g_fd,0x505,0);
			if(nPercent<100)
			{
				strInfo.Format(_T("测试仪更新：FPGA文件[%s]已写入%d%"),g_strFPGAFile.GetString(),nPercent);
				g_theCoreBaseApp->SendUpdateInfo(strInfo);
				g_count = 0;
			}
		}
	}
	else if(nRet == SPI_FLAG_IN_WRITING_FAILED)
	{
		qDebug()<<"the FPGA write error";

		strInfo.Format(_T("测试仪更新：FPGA文件[%s]写入错误"),g_strFPGAFile.GetString());
		g_theCoreBaseApp->SendUpdateInfo(strInfo);
		g_nFlag = -1;
	}
	else if(nRet == SPI_FLAG_WRITE_FINISH)
	{
		qDebug()<<"the FPGA update success";

		strInfo.Format(_T("测试仪更新：FPGA文件[%s]写入100%,更新完成"),g_strFPGAFile.GetString());
		g_theCoreBaseApp->SendUpdateInfo(strInfo);
		g_nFlag = 1;
	}
}

void setSigIO(int tfd)
{
	int oflags;
	signal(SIGIO,fasync_handler);
	fcntl(tfd, F_SETOWN, getpid());
	oflags=fcntl(tfd, F_GETFL);
	fcntl(tfd, F_SETFL, oflags | FASYNC);
}

#ifdef _USE_NO_GUI_
CSttLiveUpdateCoreBaseApp::CSttLiveUpdateCoreBaseApp(int &argc, char **argv):QCoreApplication(argc, argv)
  #else
CSttLiveUpdateCoreBaseApp::CSttLiveUpdateCoreBaseApp(int &argc, char **argv):QApplication(argc, argv)
#endif

{
	g_theCoreBaseApp = this;
	m_pLiveUpdateExceThread = NULL;
	m_nHasExceFinished = FALSE;

#ifdef _USE_NO_GUI_
	CLogPrint::Create(this);
#endif

	QTextCodec* codec = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	_P_InitSystemPath();

#ifndef NOT_USE_XLANGUAGE
	CXLanguageResourceBase *pLanguage = new CXLanguageResourceAtsBase();
	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(pLanguage, TRUE);
	((CSttAdjSysParaDataTypes*)g_pSttAdjSysParaDataTypes)->InitAdjSysParaDataTypes();
#endif
	CSttCmdDefineXmlRWKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CSttCmdOverTimeTool::Create();
	CSttFileToolMngr::Create();
	CSttNativeCfgXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CMacroXmlKeys::Create();


	m_strVertempPath = _P_GetSystemPath();
	m_strVertempPath.append(LIVEUPDATE_PATH_TEMP);

	m_strVerBkPath = _P_GetSystemPath();
	m_strVerBkPath.append(LIVEUPDATE_PATH_BK);

	m_oNativeCfgMngr.DeleteAll();
	if(!m_oNativeCfgMngr.Open())
	{
		m_oNativeCfgMngr.InitAfterRead();
		m_oNativeCfgMngr.Save();
	}

	g_strFtpRootFile = STTNATIVE_PATH_ROOT;
	g_nSttCmdOverTimeEnable = 0;

#ifdef _USE_NO_GUI_
	//启动侦听服务
	CString strLocalIP = GetLocalIP();
	CSttLiveUpdateServerEngine::Create(strLocalIP.toLatin1().data(),LIVEUPDATE_PORT);
	CSttTestServerBase* pServerBase = CSttTestServerBase::GetServerEngine();
	m_pServerSocket = pServerBase->GetServerSocketDataBase();
#else
	connect(&m_oTimerThreadRun,SIGNAL(timeout()),this,SLOT(slot_TimerThreadRun()));
#endif
}

void CSttLiveUpdateCoreBaseApp::StartServerSocket()
{
    //启动侦听服务
    CString strLocalIP = GetLocalIP();
    CSttLiveUpdateServerEngine::Create(strLocalIP.toLatin1().data(),LIVEUPDATE_PORT);
    CSttTestServerBase* pServerBase = CSttTestServerBase::GetServerEngine();
    m_pServerSocket = pServerBase->GetServerSocketDataBase();
}


CSttLiveUpdateCoreBaseApp::~CSttLiveUpdateCoreBaseApp()
{
}

CString CSttLiveUpdateCoreBaseApp::GetLocalIP()
{
	CString ip;
	foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
	{
		QString name=interface.name();
		if(QString::compare(name,"eth0")==0)
		{
			ip=interface.addressEntries().at(0).ip().toString();
			break;
		}
	}

	return ip;
}

void CSttLiveUpdateCoreBaseApp::ExecSttLiveUpdate()
{
	CString strInfo;
	bool bRet = false;
#ifndef _USE_NO_GUI_
long nTimeIndex = 0;
#endif

	while(1)
	{
#ifdef _USE_NO_GUI_
		qsleep(100);
#else
        if((nTimeIndex%100)==0)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ExecSttLiveUpdate-Heart."));
        }
        nTimeIndex++;
        m_oLiveUpdateTickCount.DoEvents(1000);
#endif
		m_bInitDriver = false;

		while(m_pServerSocket->GetCount()>=1)
		{
			if(m_bStopUpdate)
			{
				return;
			}

            //zhouhj 2023.11.30
            if(!m_bInitDriver)
            {
                SendInitRet();//zhouhj 2023.12.5
                m_bInitDriver = 1;
//				m_bInitDriver = InitDriverOper();
//				if(!m_bInitDriver)
//				{
//					return;
//				}
            }

			if(!m_bParasRecvSuc)
			{
				if(!WaitForParas())
				{
					continue;
				}
			}

			if(m_nUpdateStyle == UPDATESTYLE_NONE)
				continue;
			//按更新类型分别处理
			if(m_nUpdateStyle == UPDATESTYLE_LOCAL)
			{
				//等待压缩文件传递完成
				if(!m_bFileRecvOver)
				{
					if(!WaitForFileRecv())
					{
						continue;
					}
				}
			}
			if(m_nUpdateStyle == UPDATESTYLE_REMOTE || m_nUpdateStyle == UPDATESTYLE_MOBILE)
			{
				CSttNativeCfgYun* pCfgYun = m_oNativeCfgMngr.GetCfgYun();
				CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
				CSttNativeCfgHisVer* pCfgHisVer = pLiveUpdate->GetCfgHisVer();
				if(m_strServerIP.IsEmpty())
				{
					m_strServerIP = pCfgYun->GetIP();
				}
				else
				{
					pCfgYun->SetIP(m_strServerIP);
				}

				if(m_nServerPort == 0)
				{
					m_nServerPort = pCfgYun->GetPort();
				}
				else
				{
					pCfgYun->SetPort(m_nServerPort);
				}

				if(m_nServerFtpPort == 0)
				{
					m_nServerFtpPort = pCfgYun->GetFtpPort();
				}
				else
                {
					pCfgYun->SetFtpPort(m_nServerFtpPort);
				}

				CDBOptrClientBaseApp::InitRpcClient(m_strServerIP, m_nServerPort);

				CString strSvrZipFile;
				CSttNativeCfgMngr oUpdateSys;
				oUpdateSys.Open();
				m_nIdxSys = oUpdateSys.GetCfgLiveUpdate()->m_nIndex_System;
				m_nIdxVer = LIVEUPDATE_NEWEST_VERINDEX;
#ifdef NOT_USE_XLANGUAGE
				if(!VerUpdateRpc_BeginUpdate(pCfgHisVer->m_nCurrVerIdx, m_nIdxVer, m_nIdxSys, strSvrZipFile))
				{
                    strInfo.Format(_T("测试仪更新:查询[系统标识:%d,版本标识:%d]更新信息失败!"),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
                    strInfo.Format(_T("测试仪更新:查询信息完成，开始下载文件，请稍后...[系统标识:%d,版本标识:%d]"),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
                }

				if(!DownloadSvrZipFile(strSvrZipFile,m_strVertempPath))
				{
					CString strZipFileName = GetFileNameFromFilePath(strSvrZipFile);
					strInfo.Format(_T("测试仪更新:下载版本文件[%s]失败!"),strZipFileName.GetString());
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
					CString strZipFileName = GetFileNameFromFilePath(strSvrZipFile);
                    strInfo.Format(_T("测试仪更新:下载版本文件[%s]完成,准备解压缩!"),strZipFileName.GetString());
					SendUpdateInfo(strInfo);
				}

				if(!VerUpdateRpc_FinishUpdate(pCfgHisVer->m_nCurrVerIdx, m_nIdxVer, m_nIdxSys))
				{
                    strInfo.Format(_T("测试仪更新:查询[系统标识:%d,版本标识:%d]更新信息失败!"),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
                    strInfo.Format(_T("测试仪更新:已结束与云平台交互,开始解压缩更新包并进行本地升级!"));
					SendUpdateInfo(strInfo);
#ifdef _USE_NO_GUI_
                    strInfo.Format(_T("测试仪更新:升级成功后,将自动重启测试仪,请稍等......"));
#else
					strInfo.Format(_T("测试仪更新:升级成功后,需将测试仪重启,请稍等......"));
#endif
                    SendUpdateInfo(strInfo);
#else
				if(!VerUpdateRpc_BeginUpdate(pCfgHisVer->m_nCurrVerIdx, m_nIdxVer, m_nIdxSys, strSvrZipFile))
				{
                    strInfo.Format(g_sLangTxt_UpdataFail.GetString(),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
                    strInfo.Format(g_sLangTxt_DownloadFile.GetString(),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
                }

				if(!DownloadSvrZipFile(strSvrZipFile,m_strVertempPath))
				{
					CString strZipFileName = GetFileNameFromFilePath(strSvrZipFile);
                    strInfo.Format(g_sLangTxt_DownloadFail.GetString(),strZipFileName.GetString());
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
					CString strZipFileName = GetFileNameFromFilePath(strSvrZipFile);
                    strInfo.Format(g_sLangTxt_DownloadCompress.GetString(),strZipFileName.GetString());
					SendUpdateInfo(strInfo);
				}

				if(!VerUpdateRpc_FinishUpdate(pCfgHisVer->m_nCurrVerIdx, m_nIdxVer, m_nIdxSys))
				{
                    strInfo.Format(g_sLangTxt_UpdataFail.GetString(),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
                    strInfo.Format(g_sLangTxt_LocalUpgrades.GetString());
					SendUpdateInfo(strInfo);
	#ifdef _USE_NO_GUI_
	                    strInfo.Format(g_sLangTxt_Reboot.GetString());
	#else
	                    strInfo.Format(g_sLangTxt_Reboot.GetString());
	#endif
	                    SendUpdateInfo(strInfo);
#endif
				}
			}

			if(m_nUpdateStyle == UPDATESTYLE_ROLLBACK)
			{
				if(RollbackInstall())
				{
					WriteRollbackLog();
					SendUpdateResult(true);
				}
                else
				{
					SendUpdateResult(false);
				}
			}
			else
			{
				//本地更新调用
#ifdef _PSX_QT_LINUX_
                KillRunningProgram();
    //			system("pkill -9 TestCtrlCntrLinux");
#endif
				if(UpdateInstall(m_strLocalZipFile,m_strUnzipPath))
				{
					WriteUpdateLog();
					SendUpdateResult(true);
#ifdef _PSX_QT_LINUX_
					system("sync");
#ifdef _USE_NO_GUI_
					system("reboot");
#else
//					MessageBoxReboot();
					//CString strTip = _T("提示");
					//CString strText = _T("程序升级成功，请手动重启仪器");
					//CXMessageBox::information(NULL, strTip, strText);
#endif
#endif
				}
				else
				{
					SendUpdateResult(false);
				}
			}

#ifdef _PSX_IDE_QT_
			InitFlags();
#endif
			qsleep(100);
		}
	}
}

void CSttLiveUpdateCoreBaseApp::ExecSttLiveUpdate_OnLine()
{
	CString strInfo;
	bool bRet = false;
#ifndef _USE_NO_GUI_
	long nTimeIndex = 0;
#endif

	while(1)
	{
#ifdef _USE_NO_GUI_
		qsleep(100);
#else
		if((nTimeIndex%100)==0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ExecSttLiveUpdate-Heart."));
		}
		nTimeIndex++;
		m_oLiveUpdateTickCount.DoEvents(1000);
#endif
		m_bInitDriver = false;

		while(m_pServerSocket->GetCount()>=1)
		{
			if(m_bStopUpdate)
			{
				return;
			}

			//zhouhj 2023.11.30
			if(!m_bInitDriver)
			{
				SendInitRet();//zhouhj 2023.12.5
				m_bInitDriver = 1;
			}

			if(!m_bParasRecvSuc)
			{
				if(!WaitForParas())
				{
					continue;
				}
			}

			if(m_nUpdateStyle == UPDATESTYLE_NONE)
				continue;
			//按更新类型分别处理
			if(m_nUpdateStyle == UPDATESTYLE_LOCAL)
			{
				//等待压缩文件传递完成
				if(!m_bFileRecvOver)
				{
					if(!WaitForFileRecv())
					{
						continue;
					}
				}
			}
			if(m_nUpdateStyle == UPDATESTYLE_REMOTE || m_nUpdateStyle == UPDATESTYLE_MOBILE)
			{
				CSttNativeCfgYun* pCfgYun = m_oNativeCfgMngr.GetCfgYun();
				CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
				CSttNativeCfgHisVer* pCfgHisVer = pLiveUpdate->GetCfgHisVer();
				if(m_strServerIP.IsEmpty())
				{
					m_strServerIP = pCfgYun->GetIP();
				}
				else
				{
					pCfgYun->SetIP(m_strServerIP);
				}

				if(m_nServerPort == 0)
				{
					m_nServerPort = pCfgYun->GetPort();
				}
				else
				{
					pCfgYun->SetPort(m_nServerPort);
				}

				if(m_nServerFtpPort == 0)
				{
					m_nServerFtpPort = pCfgYun->GetFtpPort();
				}
				else
				{
					pCfgYun->SetFtpPort(m_nServerFtpPort);
				}

				CDBOptrClientBaseApp::InitRpcClient(m_strServerIP, m_nServerPort);

				CString strSvrZipFile;
				CSttNativeCfgMngr oUpdateSys;
				oUpdateSys.Open();
				m_nIdxSys = oUpdateSys.GetCfgLiveUpdate()->m_nIndex_System;
				m_nIdxVer = LIVEUPDATE_NEWEST_VERINDEX;
				if(!VerUpdateRpc_BeginUpdate(pCfgHisVer->m_nCurrVerIdx, m_nIdxVer, m_nIdxSys, strSvrZipFile))
				{
					strInfo.Format(_T("测试仪更新:查询[系统标识:%d,版本标识:%d]更新信息失败!"),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
					strInfo.Format(_T("测试仪更新:查询信息完成，开始下载文件，请稍后...[系统标识:%d,版本标识:%d]"),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
				}

				if(!DownloadSvrZipFile(strSvrZipFile,m_strVertempPath))
				{
					CString strZipFileName = GetFileNameFromFilePath(strSvrZipFile);
					strInfo.Format(_T("测试仪更新:下载版本文件[%s]失败!"),strZipFileName.GetString());
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
					CString strZipFileName = GetFileNameFromFilePath(strSvrZipFile);
					strInfo.Format(_T("测试仪更新:下载版本文件[%s]完成,准备解压缩!"),strZipFileName.GetString());
					SendUpdateInfo(strInfo);
				}

				if(!VerUpdateRpc_FinishUpdate(pCfgHisVer->m_nCurrVerIdx, m_nIdxVer, m_nIdxSys))
				{
					strInfo.Format(_T("测试仪更新:查询[系统标识:%d,版本标识:%d]更新信息失败!"),m_nIdxSys,m_nIdxVer);
					SendUpdateInfo(strInfo);
					SendUpdateResult(false);
					InitFlags();
					continue;
				}
				else
				{
					strInfo.Format(_T("测试仪更新:已结束与云平台交互,开始解压缩更新包并进行本地升级!"));
					SendUpdateInfo(strInfo);
#ifdef _USE_NO_GUI_
					strInfo.Format(_T("测试仪更新:升级成功后,将自动重启测试仪,请稍等......"));
#else
					strInfo.Format(_T("测试仪更新:升级成功后,需将测试仪重启,请稍等......"));
#endif
					SendUpdateInfo(strInfo);
				}
			}

			CSttLiveUpdateServerEngine::Release();
			m_pServerSocket = NULL;
			StartLiveUpdateByThr();
			return;
		}
	}
}

void CSttLiveUpdateCoreBaseApp::ExecSttLiveUpdate_Debug()
{
	m_strLocalZipFile = _P_GetInstallPath();
    m_strLocalZipFile += "Stt/";
	m_strUnzipPath = m_strLocalZipFile;
	m_strLocalZipFile += "PNS330M_20231129.zip";
	m_strUnzipPath += LIVEUPDATE_PATH_UNZIP;
    CString strInfo;
    bool bRet = false;
#ifndef _USE_NO_GUI_
long nTimeIndex = 0;
#endif
CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("(%s)(%s)"),
                                              m_strLocalZipFile.GetString(),m_strUnzipPath.GetString());
m_oLiveUpdateTickCount.DoEvents(1000);

//        m_bInitDriver = false;

//        if(!m_bInitDriver)
//        {
//            m_bInitDriver = InitDriverOper();
//            if(!m_bInitDriver)
//            {
//                return;
//            }
//        }

        //本地更新调用
#ifdef _PSX_QT_LINUX_
        KillRunningProgram();
//			system("pkill -9 TestCtrlCntrLinux");
#endif
        if(UpdateInstall(m_strLocalZipFile,m_strUnzipPath))
        {
            WriteUpdateLog();
            SendUpdateResult(true);
#ifdef _PSX_QT_LINUX_
            system("sync");
#ifdef _USE_NO_GUI_
			system("reboot");
#else
			MessageBoxReboot();
// 			CString strTip = _T("提示");
// 			CString strText = _T("程序升级成功，请手动重启仪器");
// 			CXMessageBox::information(NULL, strTip, strText);
#endif
#endif
        }
        else
        {
            SendUpdateResult(false);
        }
#ifdef _PSX_IDE_QT_
        InitFlags();
#endif
        qsleep(100);
}

void CSttLiveUpdateCoreBaseApp::ExecSttLiveUpdate_OffLine()
{
	CString strInfo;
	bool bRet = false;
#ifndef _USE_NO_GUI_
	long nTimeIndex = 0;
#endif
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("(%s)(%s)"),
		m_strLocalZipFile.GetString(),m_strUnzipPath.GetString());
	m_oLiveUpdateTickCount.DoEvents(1000);

	//本地更新调用
#ifdef _PSX_QT_LINUX_
//	KillRunningProgram();
#endif
	if(UpdateInstall(m_strLocalZipFile,m_strUnzipPath))
	{
		WriteUpdateLog();
//		SendUpdateResult(true);
#ifdef _PSX_QT_LINUX_
		system("sync");
#ifdef _USE_NO_GUI_
		system("reboot");		
#else
//		MessageBoxReboot();
// 		CString strTip = _T("提示");
// 		CString strText = _T("程序升级成功，请手动重启仪器");
// 		CXMessageBox::information(NULL, strTip, strText);

#endif
#endif
	}
	else
	{
		SendUpdateResult(false);
	}
#ifdef _PSX_IDE_QT_
	InitFlags();
#endif
	qsleep(100);

}

void CSttLiveUpdateCoreBaseApp::ExecSttLiveUpdate_RollBack()
{
	if(RollbackInstall())
	{
		WriteRollbackLog();
		SendUpdateResult(true);
	}
	else
	{
		SendUpdateResult(false);
	}
}

void CSttLiveUpdateCoreBaseApp::ExitSttLiveUpdate()
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入退出升级函数(ExitSttLiveUpdate())."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

	ExitDriverOper();
#ifndef NOT_USE_XLANGUAGE
	CXLanguageXmlRWKeys::Release();
	CXLanguageMngr::Release();
#endif
	CSttLiveUpdateServerEngine::Release();
	CSttNativeCfgXmlRWKeys::Release();
	CSttFileToolMngr::Release();
	CSttCmdOverTimeTool::Release();
	CDataMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CMacroXmlKeys::Release();

	//向底层程序管理进程SttTestMngr发送退出消息以重启测试控制服务和本机测试管理程序
    system("sync");
    system("sleep 1");
    system("sync");

#ifdef _USE_NO_GUI_
	system("reboot");
#else
//	MessageBoxReboot();
#endif
	qsleep(1000);
}

#ifndef _USE_NO_GUI_
void CSttLiveUpdateCoreBaseApp::MessageBoxReboot()
{
    //2024.4.17 Xuzt
#ifndef NOT_USE_XLANGUAGE
    CString strTip = /*_T("提示")*/g_sLangTxt_Message;
    CString strText = /*_T("程序升级成功，请手动重启仪器")*/g_sLangTxt_Update_UpdateSuccess;
#else
	CString strTip = _T("提示");
	CString strText = _T("程序升级成功，请手动重启仪器");
#endif
	while(1)
	{

        QMessageBox messageBox(QMessageBox::NoIcon, strTip, strText);
        messageBox.setStandardButtons(QMessageBox::NoButton);
        messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        messageBox.exec();
        //CXMessageBox::information(NULL, strTip, strText, QMessageBox::NoButton);
	}
}
#endif

void CSttLiveUpdateCoreBaseApp::SendExitInfo(const char *pBuf, long nLen)
{	
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入发送推出信息函数(SendExitInfo())."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

#ifdef  _PSX_QT_LINUX_
    QFile fileout;
    fileout.open(stdout, QIODevice::WriteOnly);
    fileout.write(pBuf, nLen); // write to stderr退出
#endif
}

bool CSttLiveUpdateCoreBaseApp::InitDriverOper()
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入打开驱动操作函数(InitDriverOper())."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

	CString strInfo;
    CString devPath;
	if(g_fd<=0)
	{
        devPath = GetDriverDevPath();
        if(!devPath.IsEmpty())
        {
            g_fd = open(devPath.toLatin1().data(), O_RDWR);	// 驱动文件句柄
            if(g_fd <= 0)
            {
                qDebug()<<devPath <<(" open failed \n");
                strInfo = _T(devPath + "测试仪驱动文件打开失败,更新服务退出.");
                SendUpdateInfo(strInfo);
                SendUpdateRet(false);
                SendUpdateResult(false);
                return false;
            }

            setSigIO(g_fd);
        } else{
            strInfo = _T(devPath + "测试仪驱动路径获取失败,更新服务退出.");
            SendUpdateInfo(strInfo);
            SendUpdateRet(false);
            SendUpdateResult(false);
            return false;
        }
	}

	memset(&g_oBoardinfo,0,sizeof(Drv_BoardVersion));
    read(g_fd,(char*)&g_oBoardinfo,0x209);
//	CSttDriverOper::readFlashData((char*)&g_oBoardinfo,0,0);

	bool bRet = stt_open_adjust_file("DeviceSystemParas.xml");
	if(!bRet)
	{
		strInfo = _T("DeviceSystemParas.xml测试仪设备配置文件打开失败,更新服务退出.");
		SendUpdateInfo(strInfo);
		SendUpdateRet(false);
		SendUpdateResult(false);
		return false;
	}

    strInfo = _T(devPath + "测试仪驱动文件打开成功,DeviceSystemParas.xml测试仪设备配置文件打开成功.");
	SendUpdateInfo(strInfo);
	SendInitRet();

	return true;
}

void CSttLiveUpdateCoreBaseApp::ExitDriverOper()
{

}

CString CSttLiveUpdateCoreBaseApp::TransVersion(unsigned int nVal)
{
	CString strBoardVer=_T("V");
	strBoardVer+=CString::number((nVal>>16)&0xff);
	strBoardVer+=CString::number((nVal>>8)&0xff);
	strBoardVer+=CString::number(nVal&0xff);
	return strBoardVer;
}

bool CSttLiveUpdateCoreBaseApp::WaitForFPGA()
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入等待FPGA函数(WaitForFPGA())."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (1)
	{
		nCount++;

		if(g_nFlag==1)
		{
			return TRUE;
		}
		else if(g_nFlag==-1)
		{
			return FALSE;
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}
}

bool CSttLiveUpdateCoreBaseApp::IsFPGAFile(const CString& strFPGAFile)
{
	//判断扩展名是否bin或Bin
	CString strPostfix = ParseFilePostfix(strFPGAFile);
	if(strPostfix.CompareNoCase(_T("bin")))
	{
		return false;
	}

	//判断文件名前缀是否在strPofixs中
	CStringTokenizer token;
	token.Init(strFPGAFile,_T('_'));
	CString strFPGAType = token.GetToken(1);
	if(!strFPGAType.CompareNoCase(_T("V")) || !strFPGAType.CompareNoCase(_T("C"))
		||!strFPGAType.CompareNoCase(_T("DC")) || !strFPGAType.CompareNoCase(_T("KIO"))
		||!strFPGAType.CompareNoCase(_T("0G8M")) ||!strFPGAType.CompareNoCase(_T("2G6M"))
		||!strFPGAType.CompareNoCase(_T("4G4M")))
	{
		return true;
	}

	return false;
}

bool CSttLiveUpdateCoreBaseApp::UpdateFPGAFile(const CString& strFPGAFile)
{
#ifdef _PSX_IDE_QT_
	g_strFPGAFile = strFPGAFile;
	UpdateFPGAData(strFPGAFile);
#endif
}

bool CSttLiveUpdateCoreBaseApp::IsMntSysFile(const CString& strSysFile)
{
	CString strFileNameEx = GetPathFileNameFromFilePathName(strSysFile);
	CSttNativeCfgMnt* pCfgMnt = m_oNativeCfgMngr.GetCfgMnt();
	if(pCfgMnt->m_strRootFiles.Find(strFileNameEx)>=0)
	{
		return true;
	}

	return false;
}

bool CSttLiveUpdateCoreBaseApp::UpdateMntSysFile(const CString& strSysFile)
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("进入更新系统文件函数(UpdateMntSysFile(%s))."),strSysFile.GetString());
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

#ifdef _PSX_IDE_QT_
	CString strFileNameEx = GetPathFileNameFromFilePathName(strSysFile);
	CString strMntPath = _T("/mnt/");
	strMntPath.append(strFileNameEx);
	QFile::remove(strMntPath);
	if(QFile::copy(strSysFile,strMntPath))
	{
		QFile::remove(strSysFile);
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
		return true;
	}
	else
	{
		return false;
	}
#endif
}

void CSttLiveUpdateCoreBaseApp::GetFPGAPosition(const CString& strModType,CString& strModTypeDes,CByteArray& nPosArray)
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入获取FPGA位置函数(GetFPGAPosition())."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

	STT_MODULE stt_module;
	ST_MODULE_ATTR stt_moduleAttr;
	for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount;i++)
	{
		stt_module = g_theDeviceSystemParameter->m_oModules[i];
		switch(stt_module.m_oModuleAttr.m_nModuleType)
		{
		case STT_MODULE_TYPE_VOLT:   	    //0
			if(strModType==_T("V"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("交流电压板");
			}
			break;
		case STT_MODULE_TYPE_CURRENT:	 //1
			if(strModType==_T("C"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("交流电流板");
			}
			break;
        case STT_MODULE_TYPE_DIGITAL_0G8M:	 //2
			if(strModType==_T("0G8M"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("8百兆光口数字板");
			}
            break;
        case STT_MODULE_TYPE_DIGITAL_2G6M:	 //2
            if(strModType==_T("2G6M"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("2千兆6百兆光口数字板");
			}
            break;
        case STT_MODULE_TYPE_DIGITAL_4G4M:	 //2
            if(strModType==_T("4G4M"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("4千兆4百兆光口数字板");
			}
			break;
		case STT_MODULE_TYPE_DCCURRENT:  //3
		case STT_MODULE_TYPE_DCVOLT:	 //4
			if(strModType==_T("DC"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("直流板");
			}
			break;
		case STT_MODULE_TYPE_SWITCH:     //5
			if(strModType==_T("KIO"))
			{
				nPosArray.Add(stt_module.m_oModuleAttr.m_nModuleIndex);
				strModTypeDes = _T("开关量板");
			}
			break;
		default:
			break;
		}
	}
}

void CSttLiveUpdateCoreBaseApp::KillRunningProgram()
{
    CString strLabel, strVal,strExcString;
    QFile fileini(_P_GetBinPath()+QString("SttTestMngr.ini"));

    if(fileini.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString strData;
        while(!fileini.atEnd())
        {
            strData=fileini.readLine();

            if(strData.contains("="))
            {
                strLabel=strData.split("=")[0].replace(" ","");
                strVal=strData.split("=")[1].replace(" ","");
                strVal=strVal.left(strVal.length()-1);

                if((strLabel=="TestServer")||(strLabel=="TestMainCore"))
                {
                    strExcString = "pkill -9 ";
                    strExcString += strVal;

#ifdef _PSX_QT_LINUX_
                system(strExcString.GetString());
#endif
                 CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("kill %s "),strVal.GetString());
                }
            }
        }
        fileini.close();
    }
    else
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("open file SttTestMngr.ini failed"));
    }

#ifdef _PSX_QT_LINUX_
                system("pkill -9 SttNativeMain");
                system("pkill -9 TestCtrlCntrLinux");
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Kill SttNativeMain,TestCtrlCntrLinux"));
#endif

				if (m_nLogUpdateString)
				{
                    m_oLiveUpdateTickCount.DoEvents(1000);
				}
}

void CSttLiveUpdateCoreBaseApp::KillRunningProgram_OffLine()
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Begin[KillRunningProgram_OffLine]."));
	m_oLiveUpdateTickCount.DoEvents(20);
	CString strLabel, strVal,strExcString;
	QFile fileini(_P_GetBinPath()+QString("SttTestMngr.ini"));
	QStringList astrProcess;

	if(fileini.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QString strData;
		while(!fileini.atEnd())
		{
			strData=fileini.readLine();

			if(strData.contains("="))
			{
				strLabel=strData.split("=")[0].replace(" ","");
				strVal=strData.split("=")[1].replace(" ","");
				strVal=strVal.left(strVal.length()-1);

				if((strLabel=="TestServer")||(strLabel=="TestMainCore"))
				{
					if (!astrProcess.contains(strData))
					{
						astrProcess.append(strVal);
						strExcString = "pkill -9 ";
						strExcString += strVal;

#ifdef _PSX_QT_LINUX_
						system(strExcString.GetString());
#endif
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("kill %s "),strVal.GetString());
					}
				}
			}
		}
		fileini.close();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("open file SttTestMngr.ini failed"));
	}

#ifdef _PSX_QT_LINUX_
//	system("pkill -9 SttNativeMain");
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("pkill -9 SttNativeMain"));
//	m_oLiveUpdateTickCount.DoEvents(20);
	system("pkill -9 TestCtrlCntrLinux");
	m_oLiveUpdateTickCount.DoEvents(20);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Kill SttNativeMain,TestCtrlCntrLinux"));
#endif

	if (m_nLogUpdateString)
	{
		m_oLiveUpdateTickCount.DoEvents(1000);
	}
}

CString CSttLiveUpdateCoreBaseApp::GetDriverDevPath()
{
    CString strDriverDevName;
    CString strDriverDevPath;
    CString strLabel,strVal;
    int nLabelType=0;//1=boot 2=STT 3=Driver 4=LiveUpdate
    QFile fileini(_P_GetBinPath()+QString("SttTestMngr.ini"));
    if(fileini.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString strData;
        while(!fileini.atEnd())
        {
            strData=fileini.readLine();
            if(strData.contains("[boot]"))
            {
                nLabelType=1;
            }
            else if(strData.contains("[App]"))
            {
                nLabelType=2;
            }
            else if(strData.contains("[Driver]"))
            {
                nLabelType=3;
            }
            else if(strData.contains("[LiveUpdate]"))
            {
                nLabelType=4;
            }
            else if(strData.contains("="))
            {
                strLabel=strData.split("=")[0].replace(" ","");
                strVal=strData.split("=")[1].replace(" ","");
                strVal=strVal.left(strVal.length()-1);

                if(strLabel.isEmpty()||strVal.isEmpty())
                    continue;

                switch(nLabelType)
                {
                    case 4:
                    {
                        strDriverDevName = strVal;
                    }
                    break;
                }
            }
        }
        fileini.close();
    }
    if(!strDriverDevName.IsEmpty())
    {
        strDriverDevPath = CString("/dev/") + strDriverDevName;
    }

    if(m_nLogUpdateString)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("获取驱动路径函数(GetDriverDevPath(%s))."),strDriverDevPath.GetString());
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

    return strDriverDevPath;
}

bool CSttLiveUpdateCoreBaseApp::UpdateFPGAData(const CString& strFPGAFile)
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("进入FGPA升级函数(UpdateFPGAData(%s))."),strFPGAFile.GetString());
        m_oLiveUpdateTickCount.DoEvents(100);
	}
	QFile fpgafile;
	fpgafile.setFileName(strFPGAFile);
	bool ret = fpgafile.open(QFile::ReadOnly);

	CString strInfo;
	if(ret == false)
	{
		qDebug()<<("FPGA file open failed \n");

		strInfo.Format(_T("测试仪更新：FPGA文件【%s】打开失败，无法更新"),strFPGAFile.GetString());
		SendUpdateInfo(strInfo);
		return false;
	}

	CByteArray nPosArray;
	CString strModel;
	CString strFPGAType;
	CString strNewVer;
	CString strModTypeDes;

	CStringTokenizer token;
	CString strFileName = ParseFileName(strFPGAFile);
	token.Init(strFileName,_T('_'));

	strModel = token.GetToken(0);
	strFPGAType = token.GetToken(1);
	strNewVer = token.GetToken(2);
	GetFPGAPosition(strFPGAType,strModTypeDes,nPosArray);

	for(int i=0;i<nPosArray.GetSize();i++)
	{
		g_nFlag = 0;

		//读取nPosition位置的模块版本号
		CString strOldVer = TransVersion(g_oBoardinfo.version[nPosArray.GetAt(i)]);

		//比较旧版本和新版本
		if(strNewVer==strOldVer)
		{
			strInfo.Format(_T("测试仪更新：FPGA文件【%s】版本【%s】与现有版本相同，更新略过"),strFPGAFile.GetString(),strOldVer.GetString());
			SendUpdateInfo(strInfo);
			continue;
		}

		QByteArray fpgadata = fpgafile.readAll();
		qDebug()<<fpgadata.size();

        ioctl(g_fd,0x30F,0x01<<((int)nPosArray.GetAt(i) - 1));
        write(g_fd,fpgadata.data(),fpgadata.length());
//		CSttDriverOper::updateFpga(fpgadata.data(),fpgadata.length(),0x01<<((int)nPosArray.GetAt(i) - 1));

		//等待数据写入完成的信号
		ret = WaitForFPGA();
        ioctl(g_fd,0x30F,0);
//		CSttDriverOper::sendUpdateFpgaOver();
	}

	return true;
}

void CSttLiveUpdateCoreBaseApp::WriteUpdateLog()
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入写升级Log函数(WriteUpdateLog)."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

	CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
	QDateTime dateTime;
	CString m_strDateTime = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    if(m_nIdxSys>0)//20230113 zhouhj
    {
        pLiveUpdate->UpdateHisVer(m_strDateTime,m_nIdxSys,m_nIdxVer,m_strIDVer);
    }

	m_oNativeCfgMngr.Save();
}

void CSttLiveUpdateCoreBaseApp::WriteRollbackLog()
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入写回滚Log函数(WriteRollbackLog)."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

	CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
	QDateTime dateTime;
	CString m_strDateTime = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

	CSttNativeCfgHisVer* pCfgHisVer = pLiveUpdate->GetCfgHisVer();
	int nRollVerIdx = pCfgHisVer->m_nPrevVerIdx;
	CString strRollIDVer = pCfgHisVer->m_strPrevVer;
	pLiveUpdate->UpdateHisVer(m_strDateTime,pLiveUpdate->m_nIndex_System,nRollVerIdx,strRollIDVer);
	m_oNativeCfgMngr.Save();
}

bool CSttLiveUpdateCoreBaseApp::SelectFiles(const CString& strDir,CStringArray& arrFiles)
{
	arrFiles.RemoveAll();

	QDir dir(strDir);
	if (!dir.exists())
	{
		return false;
	}

	dir.setFilter(QDir::Dirs|QDir::Files);
	dir.setSorting(QDir::DirsFirst);
	QFileInfoList list = dir.entryInfoList();
	int i=0;

	do{
		QFileInfo fileInfo = list.at(i);
		if(fileInfo.fileName()=="."|fileInfo.fileName()=="..")
		{
			i++;
			continue;
		}

		bool bisDir=fileInfo.isDir();
		if(bisDir)
		{
			SelectFiles(fileInfo.filePath(),arrFiles);
		}
		else{
			arrFiles.Add(fileInfo.filePath());
		}
		i++;
	}while(i<list.size());

	if(arrFiles.GetCount()>0)
	{
		return true;
	}

	return false;
}

bool CSttLiveUpdateCoreBaseApp::RollbackInstall()
{
    if(m_nLogUpdateString)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("进入回滚函数(RollbackInstall)."));
        m_oLiveUpdateTickCount.DoEvents(1000);
	}

	CString strInfo;

	//从LiveUpdate/verbk/检索所有的文件
	CStringArray arrFiles;
	if(!SelectFiles(m_strVerBkPath, arrFiles))
	{
		strInfo.Format(_T("测试仪回滚:测试仪备份路径[%s]不存在或为空！"),m_strVerBkPath.GetString());
		SendUpdateInfo(strInfo);
		return false;
	}

	//遍历文件夹
	CString strBkFilePath,strRelative,strDestFilePath,strTmp;
	CString strSystemPath = _P_GetSystemPath();
	bool bRet;
	for (long nCount = 0;nCount<arrFiles.GetSize();nCount++)
	{
		strBkFilePath = arrFiles.GetAt(nCount);
		if (IsFileExist(strBkFilePath))
		{
			strRelative = strBkFilePath.Right(strBkFilePath.GetLength() - m_strVerBkPath.GetLength());
			strDestFilePath = GetModuleProcessPath(strSystemPath,strRelative);
			strTmp = GetFileNameFromFilePath(strBkFilePath,_T('//'));

			ClearFileReadOnlyAttr(strDestFilePath);
			bRet = X_CopyFile(strBkFilePath,strDestFilePath);

			if(bRet)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("测试仪回滚：文件【%s】拷贝成功!"),strDestFilePath.GetString());

				if (m_nLogUpdateString)
				{
                    m_oLiveUpdateTickCount.DoEvents(1000);
				}
//				strInfo.Format(_T("测试仪回滚：文件【%s】拷贝成功!"),strDestFilePath.GetString());
//				SendUpdateInfo(strInfo);//20220630 zhouhj 发送消息耗时太长

				if(strTmp.CompareNoCase(LIVEUPDATE_CFG_NATIVE)==0)
				{
					m_oNativeCfgMngr.DeleteAll();
					m_oNativeCfgMngr.Open();
					continue;
				}

				if(IsFPGAFile(strDestFilePath))
				{
//					UpdateFPGAFile(strDestFilePath);//2023.7.11 zhouhj
				}
				else if(IsMntSysFile(strDestFilePath))
				{
					UpdateMntSysFile(strDestFilePath);
				}
			}
			else
			{
				strInfo.Format(_T("测试仪回滚：文件【%s】拷贝失败!"),strDestFilePath.GetString());
				SendUpdateInfo(strInfo);
			}
		}
	}

	return true;
}

void CSttLiveUpdateCoreBaseApp::StartLiveUpdateByThr()
{
#ifdef _PSX_IDE_QT_
#ifndef _USE_NO_GUI_
	FreeLiveUpdateExceThread();
	m_nHasExceFinished = FALSE;
	m_oLiveUpdateTickCount.DoEvents(500);
	KillRunningProgram_OffLine();
#ifdef NOT_USE_XLANGUAGE
    CLogPrint::LogFormatString(XLOGLEVEL_RESULT,"正在准备升级文件，请稍后...");
#else
	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,g_sLangTxt_Escalating.GetString());
#endif
    m_oLiveUpdateTickCount.DoEvents(500);
	m_pLiveUpdateExceThread = new CWinThread(LiveUpdateExceThread, this);
	m_pLiveUpdateExceThread->m_bAutoDelete = FALSE;
	m_pLiveUpdateExceThread->ResumeThread();
	m_oTimerThreadRun.start(1000);

//	CTickCount32 oTickCount;

//	while(!m_nHasExceFinished)
//	{
//        oTickCount.DoEvents(200);
//	}
#endif
#endif

}

void CSttLiveUpdateCoreBaseApp::FreeLiveUpdateExceThread()
{
#ifdef _PSX_IDE_QT_
#ifndef _USE_NO_GUI_
	if (m_pLiveUpdateExceThread != NULL)
	{
		m_pLiveUpdateExceThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pLiveUpdateExceThread->wait();
		m_pLiveUpdateExceThread = NULL;
	}
#endif
#endif
}

UINT CSttLiveUpdateCoreBaseApp::LiveUpdateExceThread(LPVOID pParam)
{
	CSttLiveUpdateCoreBaseApp *pSttLiveUpdateCoreBaseApp = (CSttLiveUpdateCoreBaseApp *)pParam;

	if(pSttLiveUpdateCoreBaseApp->m_nUpdateStyle == UPDATESTYLE_ROLLBACK)
	{
		pSttLiveUpdateCoreBaseApp->ExecSttLiveUpdate_RollBack();
	}
	else
	{
		pSttLiveUpdateCoreBaseApp->ExecSttLiveUpdate_OffLine();
	}

	pSttLiveUpdateCoreBaseApp->ExitSttLiveUpdate();
	pSttLiveUpdateCoreBaseApp->m_nHasExceFinished = TRUE;
}

#ifndef _USE_NO_GUI_
void CSttLiveUpdateCoreBaseApp::slot_TimerThreadRun()
{
	if (m_nHasExceFinished)
	{
		MessageBoxReboot();
	}
}
#endif


