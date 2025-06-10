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

// CLiveUpdateBaseApp ����Ŀ��

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
	CAts_System*			m_pNativeSys;		//�����Ǹ�����

//VerUpdateHis
	CVerUpdateHisSysMngr	m_oVerUpdateHisSysMngr;
	CVerUpdateHisVer* 		m_pVerUpdateHisVer;
	
//AtsVerdata
	CAts_Systems	m_oAts_Systems;		//��ͻ���ص�����ϵͳ

	CAts_Systems    m_oAts_MainSystems;	//��ͻ���ص���ϵͳ
	CAts_System*	m_pAts_MainSystem;	//��ǰ��ϵͳ
	CAts_Systems    m_oAts_SubSystems;	//��ǰ��ϵͳ�������������ϵͳ���ͻ���POWER-SKY���ͻ��ǵ�¼�ͻ�����ϵͳID=��Ȩ�Ĳ��Թ��ܻ���Թ�����ģ�

	CAts_System*	m_pAts_System;		//��ǰ����ϵͳ
	CAts_Version*	m_pAts_Version;		//��ǰ����Ŀ��汾
	
	CAts_Systems	m_oAts_TestAppSys;	//Ƕ��ʽϵͳ�б�
	
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
	//����ƽ̨��Socket
	CSttClientTestEngine  m_oSttClientEngine;
	CSttSocketFileTransferProgress* m_pProgress;
	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress){ m_pProgress = pProgress; };

	//����ƽ̨��FTP
	CXMiniFtpClient m_oXMiniFtpClient;
	
	BOOL IsTestAppExist();
	void ReConnectServer();

	CSttMulticastClientSocket* m_pSttMulticastClientSocket;
#endif

//TestApp
	CString m_strServerIP;				//��ƽ̨IP
	int     m_nServerPort;				//��ƽ̨�˿�
	int     m_nServerFtpPort;			//��ƽ̨�ļ�����˿�
	CString m_strTestAppIP;				//������IP
	int     m_nTestAppPort;				//�����ǿ��Ʒ���˿�

	CString m_strTestAppSN;				//���������к�
	CString m_strTestAppModel;			//�������ͺ�

	BOOL    m_bLocalTestApp;			//����/Զ�̣�ȡ�Բ����������ļ�SttTestAppCfg.xml��
	BOOL	m_bSttServerLink;			//������ǿ��Ʒ�������״̬
	BOOL    m_bSttLiveupdateLink;		//������Ǹ��·�������״̬
	BOOL    m_bEnableLiveUpdate;		//��ǰ�Ƿ��������
	BOOL    m_bEnableSendParas;
	BOOL    m_bEnableSendFile;
	
	CStringArray m_arrTestAppProgressID;//�����ǽ���ID����
	CString m_strTestAppSysID;			//�����ǵ�ǰϵͳID
	int     m_nTestAppSysIdx;			//�����ǵ�ǰϵͳ������
	CString m_strTestAppLocalVer;		//�����ǵ�ǰ�汾��
	int     m_nTestAppLocalVer;			//�����ǵ�ǰ�汾����
	CString m_strTestAppLocalVerPrev;	//������ǰ�汾��
	int     m_nTestAppLocalVerPrev;		//������ǰ�汾����
	CString m_strVertempPath;			//�����ǰ汾���·��
	CString m_strUnzipPath;				//�����ǰ汾��ѹ·��
	CString m_strVerBkPath;				//�����ǰ汾����·��
	STATE_UPDATE m_nUpdateState;		//���¹���״̬
	BOOL	m_bReply;
	BOOL    m_bRecvUpdateInfo;			//���յ��ײ������Ϣ��־
	BOOL    m_bEndUpdate;				//���յ��ײ������ɱ�־
	CString m_strOffLineFilePath;		        //��������������·��    20240607 xueyangfan
	CSttLiveUpdateEngine  m_oSttConnectSvrEngine;	//���Ӳ����ǵײ���Կ��Ʒ���
	CSttLiveUpdateEngine  m_oSttLiveUpdateEngine;	//���ӵײ�汾���·��񣻵ײ�汾����������ƽ̨����

#ifdef _PSX_IDE_QT_
	int		m_nUpdateStyle;				//���·�ʽ
	int		m_nIdxSys;					//����ϵͳ����
	int		m_nIdxVer;					//���°汾����
	CString m_strIDSys;					//����ϵͳID
	CString m_strIDVer;					//���°汾��
	BOOL    m_bParasRecvSuc;
	BOOL    m_bFileRecvOver;
	BOOL    m_bInitDriver;				
	BOOL    m_bStopUpdate;				//ֹͣ�ײ���±�־
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
	//������������ѯ��ʷ�汾�Ͱ汾����
	void GetVer(const CString& strFilter);
	void GetVerDeatil(const CString &strFilter);
	void GetNewestUpdateVer(CAts_System* pAts_System);
	void GetNewestUpdateVer(CAts_Systems& oAts_Systems);
	void UpdateMainSysNewestVer();
	BOOL IsValidDateTime(SYSTEMTIME tmBegin,SYSTEMTIME tmEnd);

	//���²�����
#ifndef _PSX_IDE_QT_
	BOOL UpdateTestApp_Connect(const CString &strIPServer,long nPort=STTTESTSERVER_PORT);
	BOOL UpdateTestApp_ConnectLiveUpdate(const CString &strIPServer,long nPort=LIVEUPDATE_PORT,long nTimeOut=100);
	BOOL UpdateTestApp_ConnectOfflineUpdate(const CString &strIPServer,long nPort=LIVEUPDATE_PORT,long nTimeOut=100); //�������� ���ӵײ� 20240607 xueyangfan
	BOOL UpdateTestApp_SendCmd_Request();
	BOOL UpdateTestApp_SendFile();
	BOOL UpdateTestApp_SendFileOffline();           //�������� �´����°��ļ��������� 20240607 xueyangfan
	BOOL UpdateTestApp_SendFileOver();
	BOOL UpdateTestApp_SendFileOverOffline();       //�������� �������� 20240607 xueyangfan
	BOOL UpdateTestApp_SendCmd_Local();
	BOOL UpdateTestApp_SendCmd_Cloud();	
	BOOL UpdateTeatApp_SendCmd_Stop();
	BOOL UpdateTestApp_SendCmd_Rollback();
	void UpdateTestApp_Disconnect();
	void UpdateTestApp_DisconnectLiveUpdate();
	BOOL SendCmd_Local();
	BOOL SendCmd_Local(const CString &strOffLineFilePath);	//�������� �������� 20240607 xueyangfan
	BOOL SendCmd_Cloud();
	BOOL SendCmd_Rollback();
	void ExitSttLiveupdateMulticastSocket();
	BOOL MulticastStartSttLiveUpdate();
	void InitUpdateState();
#endif

	//��ʼ����ָ���汾
	BOOL VerUpdateRpc_BeginUpdate(int nLocalIdxVer,int nDestIdxVer,int nIdxSystem,CString& strSvrZipFile);

	//��ɸ���ָ���汾
	BOOL VerUpdateRpc_FinishUpdate(int nLocalIdxVer,int nDestIdxVer,int nIdxSystem);

	//���ذ汾�ļ�
	BOOL DownloadSvrZipFile(const CString& strSvrZipFile,const CString& strLocalPath);

	//���ظ���
	BOOL UpdateInstall(const CString& strLocalZipFile,const CString& strLocalVerPath);
	BOOL UnzipUpdateFiles(const CString& strLocalZipFile,const CString& strLocalVerPath,CStringArray& arrUnzipFiles);
	void CopyAllFiles(const CStringArray &strFilePaths);
	virtual bool IsFPGAFile(const CString& strFPGAFile){return false;};
	virtual bool IsMntSysFile(const CString &strSysFile){return false;};
	virtual bool UpdateFPGAFile(const CString& strFPGAFile){return true;};
	virtual bool UpdateMntSysFile(const CString& strSysFile){return true;};

    //ָ��Ŀ¼�ĸ��°������н�ѹ
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
