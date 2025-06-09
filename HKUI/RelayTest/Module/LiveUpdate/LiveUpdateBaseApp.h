#pragma once

#include "../../../Module/OSInterface/OSInterface.h"

#ifndef _PSX_IDE_QT_
#include "../../../Module/EpotoInterface/EpotoInterface.h"
#include "../../../Module/Encrypt/EncryptTool.h"
#include "../../../Module/FTP/XMiniFtpClient.h"
#include "../SttSocket/Multicast/SttMulticastClientSocket.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "UpdateInstall/LiveUpdateThread.h"
#include "../../../Module/XfileMngrBase/XFileMngr.h"
#include "../../../Module/XfileMngrBase/XFileFindEx.h"
#include "../../../Module/XfileMngrBase/XFolder.h"
#include ".././SttTestAppConfig/SttTestAppCfg.h"
#endif

#include "../SttSocket/SttSocketDataBase_File.h"
#include "../SttFileToolMngr.h"
#include "SttLiveUpdateEngine.h"

#ifdef _PSX_IDE_QT_
#include <QDateTime>
#include "../SttSocket/TestServer/VC/SttTestServerSocket.h"
#include "../SttSocket/TestServer/VC/SttServerClientSocket.h"
#include "SttNativeConfig/SttNativeCfgMngr.h"
#endif

#include "../../../Module/Socket/XPing.h"
#include "../../../Module/XmlRpc/XmlRpc.h"
#include "../../../Module/XmlRpc/XmlRpcApi_MFC.h"

#include "../../../Module/BaseClass/DBOptrClientBaseApp.h"
#include "UpdateInstall/LiveUpdateInstall.h"

#include "../../../Module/BaseClass/ExBaseOptrInterface.h"

#include "../../../OA/Module/OAMngrSvrMethodID.h"
#include "../../../OA/Module/OA_DB/VersionMngr/Ats_Systems.h"
#include "../../../OA/Module/OA_DB/PowerSky_OAGlobal.h"

#include "../../../Module/System/TickCount32.h"
#include "../../../Module/zlib-1.2.8/FilesZipApi.h"

#include "UpdateConfig/VerUpdateCfgMngr.h"
#include "UpdateHistory/VerUpdateHisSysMngr.h"

#include "SttLiveUpdateDef.h"

class CSttLiveUpdateServerSocket;

// CLiveUpdateBaseApp 命令目标

class CLiveUpdateBaseApp : public CDBOptrClientBaseApp
{
public:
	CLiveUpdateBaseApp();
	virtual ~CLiveUpdateBaseApp();

public:
	BOOL InitLiveUpdateBaseApp();
	void ExitLiveUpdateBaseApp();

//SoftDog
	CString m_strSN_Client;
	BOOL IsPowerSky()		{	return m_strSN_Client.CompareNoCase(_T("POWER-SKY"))==0;	}
	BOOL IsValidSoftDog()	{	m_strSN_Client.Trim(); return m_strSN_Client != _T("");		}
	BOOL IsIncludeSys(CAts_System* pAts_System);
	
	long m_nLogUpdateString;
	CTickCount32 m_oLiveUpdateTickCount;

//Start Mode
	UINT m_nStartMode;
	CString m_strSysID;
	CString m_strShellFullPath;
	CString m_strVerID;
	long    m_nVerIdx;

	BOOL InitCommandLine(const CString& strCommandLine);
	BOOL InitShellSystem();

//VerUpdateCfg
	CVerUpdateCfgMngr		m_oVerUpdateCfgMngr;

//NativeSysCfg
	CAts_Systems			m_oNativeSysMngr;
	CAts_System*			m_pNativeSys;		//测试仪更新项

//VerUpdateHis
	CVerUpdateHisSysMngr	m_oVerUpdateHisSysMngr;
	CVerUpdateHisVer* 		m_pVerUpdateHisVer;
	
//AtsVerdata
	CAts_Systems	m_oAts_Systems;		//与客户相关的所有系统

	CAts_Systems    m_oAts_MainSystems;	//与客户相关的主系统
	CAts_System*	m_pAts_MainSystem;	//当前主系统
	CAts_Systems    m_oAts_SubSystems;	//当前主系统的所有满足的子系统（客户是POWER-SKY、客户是登录客户并且系统ID=授权的测试功能或测试功能外的）

	CAts_System*	m_pAts_System;		//当前更新系统
	CAts_Version*	m_pAts_Version;		//当前更新目标版本
	
	CAts_Systems	m_oAts_TestAppSys;	//嵌入式系统列表
	
	BOOL m_bUpdateToPath;
	CString m_strUpdateToPath;

	BOOL m_bInConnect;
	BOOL IsInConnect(){		return m_bInConnect;	}

	void InitCurrDataObj();
	void InitLiveUpdateSys();
	void InitLiveUpdateTestAppSys();

	void SaveLocalSysCfg();
	void GetTopSystems(CAts_Systems& listSys);
	void GetSubSystems(CAts_System* pAts_MainSystem,CAts_Systems& listSys);

	int  GetSystemLocalVer(CAts_System* pAts_System);
	void ShowSystemLocalVerInfo();

#ifndef _PSX_IDE_QT_
	//与云平台：Socket
	CSttClientTestEngine  m_oSttClientEngine;
	CSttSocketFileTransferProgress* m_pProgress;
	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress){ m_pProgress = pProgress; };

	//与云平台：FTP
	CXMiniFtpClient m_oXMiniFtpClient;
	
	BOOL IsTestAppExist();
	void ReConnectServer();

	CSttMulticastClientSocket* m_pSttMulticastClientSocket;
#endif

//TestApp
	CString m_strServerIP;				//云平台IP
	int     m_nServerPort;				//云平台端口
	int     m_nServerFtpPort;			//云平台文件传输端口
	CString m_strTestAppIP;				//测试仪IP
	int     m_nTestAppPort;				//测试仪控制服务端口

	CString m_strTestAppSN;				//测试仪序列号
	CString m_strTestAppModel;			//测试仪型号

	BOOL    m_bLocalTestApp;			//本地/远程（取自测试仪配置文件SttTestAppCfg.xml）
	BOOL	m_bSttServerLink;			//与测试仪控制服务连接状态
	BOOL    m_bSttLiveupdateLink;		//与测试仪更新服务连接状态
	BOOL    m_bEnableLiveUpdate;		//当前是否允许更新
	BOOL    m_bEnableSendParas;
	BOOL    m_bEnableSendFile;
	
	CStringArray m_arrTestAppProgressID;//测试仪进程ID数组
	CString m_strTestAppSysID;			//测试仪当前系统ID
	int     m_nTestAppSysIdx;			//测试仪当前系统的索引
	CString m_strTestAppLocalVer;		//测试仪当前版本号
	int     m_nTestAppLocalVer;			//测试仪当前版本索引
	CString m_strTestAppLocalVerPrev;	//测试仪前版本号
	int     m_nTestAppLocalVerPrev;		//测试仪前版本索引
	CString m_strVertempPath;			//测试仪版本存放路径
	CString m_strUnzipPath;				//测试仪版本解压路径
	CString m_strVerBkPath;				//测试仪版本备份路径
	STATE_UPDATE m_nUpdateState;		//更新过程状态
	BOOL	m_bReply;
	BOOL    m_bRecvUpdateInfo;			//接收到底层更新信息标志
	BOOL    m_bEndUpdate;				//接收到底层更新完成标志

	CSttLiveUpdateEngine  m_oSttConnectSvrEngine;	//连接测试仪底层测试控制服务
	CSttLiveUpdateEngine  m_oSttLiveUpdateEngine;	//连接底层版本更新服务；底层版本更新连接云平台下载

#ifdef _PSX_IDE_QT_
	int		m_nUpdateStyle;				//更新方式
	int		m_nIdxSys;					//更新系统索引
	int		m_nIdxVer;					//更新版本索引
	CString m_strIDSys;					//更新系统ID
	CString m_strIDVer;					//更新版本号
	BOOL    m_bParasRecvSuc;
	BOOL    m_bFileRecvOver;
	BOOL    m_bInitDriver;				
	BOOL    m_bStopUpdate;				//停止底层更新标志
	CSttNativeCfgMngr m_oNativeCfgMngr;
	CSttServerSocketDataBase* m_pServerSocket;
	void SendUpdateRet(BOOL bRet);
	void SendUpdateInfo(const CString& strInfo);
	void SendInitRet();
	void SendUpdateResult(BOOL bResult);
	BOOL WaitForParas(int nTimeOut=100);
	BOOL WaitForFileRecv(int nTimeOut=500);
	void InitFlags();
	void qsleep(int msec);
#endif
	BOOL IsSttServerLink()	{	return m_bSttServerLink;	}
	void SetReply(BOOL bReply) { m_bReply = bReply; }
	BOOL GetReply()	{	return m_bReply;	}
	BOOL WaitForReply(int nTimeOut=500);
	BOOL WaitForXftp(const CString& strFilePath,int nTimeOut=5000);
	BOOL WaitForUpdateInfo(int nTimeOut=600);  
	void WaitForExit(int nTimeOut=50);
	void ResetWaitFlags();
#ifndef _PSX_IDE_QT_
	CWnd* m_pMsgWnd,* m_pMsgView;
	void SetMessageWnd(CWnd* pMsgWnd){	m_pMsgWnd = pMsgWnd;}
	void SetMessageView(CWnd* pMsgView) { m_pMsgView = pMsgView; }
#endif
	
public:
	//按过滤条件查询历史版本和版本详情
	void GetVer(const CString& strFilter);
	void GetVerDeatil(const CString &strFilter);
	void GetNewestUpdateVer(CAts_System* pAts_System);
	void GetNewestUpdateVer(CAts_Systems& oAts_Systems);
	void UpdateMainSysNewestVer();
	BOOL IsValidDateTime(SYSTEMTIME tmBegin,SYSTEMTIME tmEnd);

	//更新测试仪
#ifndef _PSX_IDE_QT_
	BOOL UpdateTestApp_Connect(const CString &strIPServer,long nPort=STTTESTSERVER_PORT);
	BOOL UpdateTestApp_ConnectLiveUpdate(const CString &strIPServer,long nPort=LIVEUPDATE_PORT,long nTimeOut=100);
	BOOL UpdateTestApp_SendCmd_Request();
	BOOL UpdateTestApp_SendFile();
	BOOL UpdateTestApp_SendFileOver();
	BOOL UpdateTestApp_SendCmd_Local();
	BOOL UpdateTestApp_SendCmd_Cloud();	
	BOOL UpdateTeatApp_SendCmd_Stop();
	BOOL UpdateTestApp_SendCmd_Rollback();
	void UpdateTestApp_Disconnect();
	void UpdateTestApp_DisconnectLiveUpdate();
	BOOL SendCmd_Local();
	BOOL SendCmd_Cloud();
	BOOL SendCmd_Rollback();
	void ExitSttLiveupdateMulticastSocket();
	BOOL MulticastStartSttLiveUpdate();
	void InitUpdateState();
#endif

	//开始更新指定版本
	BOOL VerUpdateRpc_BeginUpdate(int nLocalIdxVer,int nDestIdxVer,int nIdxSystem,CString& strSvrZipFile);

	//完成更新指定版本
	BOOL VerUpdateRpc_FinishUpdate(int nLocalIdxVer,int nDestIdxVer,int nIdxSystem);

	//下载版本文件
	BOOL DownloadSvrZipFile(const CString& strSvrZipFile,const CString& strLocalPath);

	//本地更新
	BOOL UpdateInstall(const CString& strLocalZipFile,const CString& strLocalVerPath);
	BOOL UnzipUpdateFiles(const CString& strLocalZipFile,const CString& strLocalVerPath,CStringArray& arrUnzipFiles);
	void CopyAllFiles(const CStringArray &strFilePaths);
	virtual bool IsFPGAFile(const CString& strFPGAFile){return false;};
	virtual bool IsMntSysFile(const CString &strSysFile){return false;};
	virtual bool UpdateFPGAFile(const CString& strFPGAFile){return true;};
	virtual bool UpdateMntSysFile(const CString& strSysFile){return true;};

    //指定目录的更新包，进行解压
    BOOL UnzipSpecPathUpdate(const CString& strLocalZipFile,const CString& strLocalVerPath);
    BOOL UnzipSpecPathUpdateFiles(const CString& strLocalZipFile,const CString& strLocalVerPath,CStringArray& arrZipFiles);

#ifndef _PSX_IDE_QT_
	void GetAllFilePaths(CXFolder *pXFolder,CStringArray &strFilePaths,CStringArray &strProcessPaths);
	void GetSelectFilePaths(CXFileMngr& oXFileMngr);
	BOOL ExitExeDllProcess(CStringArray& strAllProcessPaths);
	BOOL UpdateFiles(const CString& strLocalVerPath);
	void UpdateVerHistory();
	void DownloadModifyDoc(const CString& strRemoteDoc,const CString& strLocalPath,BOOL bOpen);
#endif

	CString m_strLocalZipFile;
	CString GetModuleProcessPath(const CString& strSystemPath,const CString& strRelativePath);
	
	BOOL m_bUpdateRet;
	void SetUpdateRet(BOOL bRet){	m_bUpdateRet = bRet;	}
	BOOL GetUpdateRet(){	return m_bUpdateRet; }
	
	BOOL m_bInUpdate,m_bStopFlag;
	void SetInUpdate(BOOL bInUpdate){	 m_bInUpdate = bInUpdate; }
	BOOL IsInUpdate(){	return m_bInUpdate;	}

	void StopUpdate() {  m_bStopFlag = TRUE; }
	void ResetUpdate() {  m_bStopFlag = FALSE; }

	BOOL m_bInTestappUpdate;
	void SetInTestappUpdate(BOOL bInUpdate){	m_bInTestappUpdate = bInUpdate;  }
	BOOL IsInTestappUpdate(){  return m_bInTestappUpdate;  } 

#ifdef _PSX_QT_LINUX_
	bool CopyDirectory(const CString &strDstPath,const CString &strSrcFolderPath,  bool bCoverFileExist = false);
#endif
};

#ifndef _PSX_IDE_QT_
extern CSttTestAppCfg g_SttTestAppCfg;
#endif

extern CLiveUpdateBaseApp* g_theLiveUpdateBaseApp;
