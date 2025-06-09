#pragma once


#include "../../../Module/MemBuffer/CycleMemBuffer.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#include "DeviceModel/DevcieModel.h"
//#include "DeviceModel/DeviceModelDefine.h"

#include "PpTemplate.h"
#include "PpPackageSendMngr.h"
#include "PpRecordMngr.h"
#include "PpDataInterface.h"
#include "PpProcedureRun.h"
#include "PpEngineDataMngrCntr.h"

#define WM_THREAD_RECEIVE		(WM_USER+100)
#define WM_THREAD_CONNECT	(WM_USER+101)
#define WM_THREAD_DISCONNECT	(WM_USER+102)
#define WM_EXIT_ENGINE_THREAD	(WM_USER+103)
#define WM_DELETE_ALL_RECORD_PACKAGE	(WM_USER+104)
#define WM_THREAD_RECORD_SEND_PKG	(WM_USER+105)

#define WM_SCRIPT_CONNECT_DEVICE       (WM_USER+106)
#define WM_SCRIPT_DISCONNECT_DEVICE  (WM_USER+107)
#define WM_THREAD_CONNECT_FINISHED	(WM_USER+108)
#define WM_THREAD_CONNECT_FAILED	(WM_USER+109)
#define WM_CONNECT_SUCCESS	(WM_USER+110)
#define WM_DISCONNECT_SUCCESS	(WM_USER+111)
#define WM_THREAD_CHANNEL_CLOSE		(WM_USER+112)

#define PPEXIT_STATE_NONE   0
#define PPEXIT_STATE_NORMAL   1
#define PPEXIT_STATE_EXITPRUN   2
#define PPEXIT_STATE_DISCONNECT  3
#define PPEXIT_STATE_EXIT   0XFFFFFFFF

// CPpEngineThread

class CPpEngineThreadBase : public CWinThread
{
protected:
	CPpEngineThreadBase();           // 动态创建所使用的受保护的构造函数
	virtual ~CPpEngineThreadBase();
	BOOL m_bHasPostWmquit;

	BOOL m_bInOnChannelReceive;
	char m_pszPpLogProtocol[10240]; 

public:
	void PostConnectDeviceMsg();
	BOOL IsConnecting();
	void WaitDeviceConnectFinished();
	BOOL IsConnectSuccessful();
	void OnDeviceConnectFinish(BOOL bSucc);
	void OnCmmChannelClose(CCmmChannel *pChannel);

	void Init(CDevcieModel *pDevcieModel, CPpTemplate *pTemplate)
	{
		ASSERT (pTemplate != NULL);
		ASSERT (pDevcieModel != NULL);

		m_pDevcieModel = pDevcieModel;
		m_pDeviceRef = m_pDevcieModel->GetPpDevice();
		m_pDeviceCmmConfigRef = m_pDevcieModel->GetDeviceCmmConfig();
		m_pTemplate = pTemplate;  
		m_pTemplate->SetDevice(m_pDevcieModel->GetPpDevice());
	}

	void SetDeleteEngineDataInExit(BOOL b)	{	m_bDeleteEngineDataInExit = b;	}
//////////////////////////////////////////////////////////////////////////
//引擎数据定义
public:
	
	//CCycleMemBuffer m_oReceiveBuffer;   //接收缓冲区管理对象

	//模型/模板
	CPpDvmDevice *m_pDeviceRef;         //设备点表数据管理对象
	CPpTemplate *m_pTemplate;  //规约模板对象
	CDeviceCmmConfig *m_pDeviceCmmConfigRef;  //设备通讯配置对象
	CDeviceCmmChannel *m_pDeviceCmmChannel;    //关联的设备通讯对象
	CCmmChannel *m_pUsingChannel;
	BOOL m_bIsInThreadParse;
	
	CPpPackageSendMngr *m_pPkgSendMngr;  //报文帧发送管理对象
			
	//接受帧对象管理:过程执行线程从此获取PackageDetail对象进行跳转的判断
	CExBaseList m_listReceivePackage;             //解析出来的帧对象

	CPpEngineData *m_pEngineData;
public:
	CDevcieModel *m_pDevcieModel;
	long m_nCurrPkgLen;
	BOOL m_bDeleteEngineDataInExit;
	BOOL m_bKillProcedure;
	CString m_strKillProcedure;
	BOOL m_bViewProcedure;

	DWORD m_dwReConnectState;
	long m_nReConnectCount;
	CTickCount32  m_oReConnectTick;

	//收到报文、解析报文计数器的互斥操作
	CAutoCriticSection m_oParsePkgCriticSection; 
	long  m_nPkgRcvCounter;

public:
	long GetSendTickLong();
	long GetRecvTickLong();
	void ResetSendTick();
	void ResetRecvTick();

//////////////////////////////////////////////////////////////////////////
//引擎方法定义
public:
	BOOL IsProcedureExist(const CString &strProcedureID); 
	BOOL RunProcedure(const CString &strProcedureID, CExBaseList *pInterface, BOOL bIsInit); //执行过程
	void KillProcedure(const CString &strProcedureID, CExBaseList *pInterface = NULL); //执行过程
	void AddReceivePackageDetail(CPpPackageDetail *pPkg);//添加解析完成的帧对象到临时列表
	void ViewProcedure();
		
	//模板 加载/卸载
	void LoadTemplate(const CString &strTemplageFile);
	void UnLoad();
		
	//设备连接、断开管理
	BOOL ConnectDevice();
	BOOL CmmChannelConfig();
	BOOL UnloadDevice();
	BOOL DisConnectDevice();

	//数据接受,关联的m_pChannel对象收到数据后,通知EngineThread对象
	void OnReceived(CCmmRcvSndTime *pCmmTime);
	void Parse(BOOL &bNeedRunProcedure); //bNeedRunProcedure  2019-5-27

#ifdef _use_CMemBufferList
	void Parse_Buff_List();
#endif

	BOOL EnterParse_FromPpRunThread();
	
	// 缓冲区处理
	void CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos);
	void CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos, CCmmRcvSndTime *pCmmTime);
	void CreateParseBufferPos(CYCLEMEMBUFFERPOS &oBufPos, long nBeginPos, long nEndPos);
	void LogErrorParse(long nBeginPos, long nLength, PACKAGEBUFFERPOS *pBufPos);
	
	//获取通讯通道
	CCmmChannel* GetCmmChannel(const CString &strCmmChannelID);
	CCmmChannel* GetCmmChannel(CPpNode *pNode);

	//添加发送报文对象
	CPpPackageSend* AddPackageSend(CPpProcedureRun *pPpProcedureRun);

	// 设备通讯配置数据管理
	void CopyDeviceCmmConfig(CDeviceCmmConfig *pDes, CDeviceCmmConfig* pSrc);
	CExBaseObject* FindByClassID(UINT nClassID, CExBaseList* pList);

	void SetCurrPkgLen(long nLen)   {    m_nCurrPkgLen = nLen;   }
	BOOL GetDeviceAttribute(const CString &strAttrTag, CString &strAttrValue);
	BOOL SetDeviceAttribute(const CString &strAttrTag, const CString &strAttrValue);

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void ExitEngineThread() ;
	void ExitRunProduceThread();
	BOOL IsThreadExitExtern();
	BOOL IsRunProduceThreadExit();

	//监视报文
	char* GetLogProtocolBuffer()	{	return m_pszPpLogProtocol;	}
	void LogProtocol(CExBaseObject *pDevice, LPVOID pPara, CYCLEMEMBUFFERPOS &oBufPos, BOOL bRecv=TRUE, const CString &strTime=_T(""));
	void LogProtocol(char *pszPpLogProtocol, CYCLEMEMBUFFERPOS &oBufPos, CString &strMsg);
	void RecordSendPackage();

	void OnProcedureExit(CPpProcedureRun *pPpProcedureRun);
	void OnProcedureStart(CPpProcedureRun *pPpProcedureRun);

public:
	BOOL IsThreadExit();
	long m_nThreadExitState;

public:
	//发送接收处理线程
	static UINT PkgSendReceiveThread(LPVOID pParam);

	//////////////////////////////////////////////////////////////////////////
	//规约过程执行相关

	//过程执行线程从此取得过程加入到执行过程列表
	CExBaseList m_listProcedureToRun;	             //过程临时列表,将要执行的过程列表
	CExBaseList m_listRunProcedure;	                 //执行的过程列表
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listProcedureTemp访问的互斥量

	//Engine Thread相关的处理
#ifdef _PSX_QT_LINUX_
    pthread_t m_pProcedureRunThread;
#else
	CWinThread *m_pProcedureRunThread;
#endif

	BOOL m_bExitEngineThread;

	//过程处理线程:死循环，不断遍历
	CPpProcedureRun* FindRunningProcedure(const CString &strProcedureID);

	void InitPackageTime(CPpPackageDetail *pPkg, long nBeginPos);
	void AddTempProcedureToRun();

	void LogAllProcedure();
	void KillProcedure();

	BOOL ReConnectOnFailed();

protected:
    afx_msg void AFX_MSG_CALL OnChannelReceive(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnConnectDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnConnectDeviceFinished(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnConnectDeviceFailed(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnDisConnectDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnExitEngineThread(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnDeleteAllRecordPackage(WPARAM wParam, LPARAM lParam);
};

#ifndef _PSX_IDE_QT_
static UINT Engine_ProcedureRunThread(LPVOID pParam);
#else
static void* Engine_ProcedureRunThread(LPVOID pParam);
#endif

