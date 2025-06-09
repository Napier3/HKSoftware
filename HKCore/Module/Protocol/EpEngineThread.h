#pragma once


#include "EpGlobalDefine.h"
#include "ProtocolBase\EpProtocolBase.h"
#include "EpEngineDataMngrCntr.h"

extern CLogBase *g_pLogPkgReceivePrint;

// CEpEngineThread

class CEpEngineThread : public CWinThread
{
	DECLARE_DYNCREATE(CEpEngineThread)

protected:
	CEpEngineThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CEpEngineThread();

	BOOL m_bHasPostWmquit;


public:
	void PostConnectDeviceMsg();
	BOOL IsConnecting();
	BOOL IsConnectSuccessful();
	void OnDeviceConnectFinish(BOOL bSucc);

	static CEpEngineThread* CreateEngineThread(CEpEngineData *pEngineData)
	{
		CEpEngineThread *pThread = (CEpEngineThread*)AfxBeginThread(RUNTIME_CLASS(CEpEngineThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		pThread->m_pEngineData = pEngineData;
		pThread->Init(pEngineData->m_pDevice, pEngineData->m_pProtocol);
		pThread->ResumeThread();
		pEngineData->m_pEngineThread = pThread;
		return pThread;
	}

	void Init(CEpDevice *pDevcie, CEpProtocolBase *pTemplate)
	{
		ASSERT (pTemplate != NULL);
		ASSERT (pDevcie != NULL);

		m_pDevice = pDevcie;
		m_pDeviceCmmConfig = NULL;
		m_pProtocol = pTemplate;  
		//m_pProtocol->SetDevice(m_pDevice);
	}

//////////////////////////////////////////////////////////////////////////
//引擎数据定义
public:
	
	//CCycleMemBuffer m_oReceiveBuffer;   //接收缓冲区管理对象

	//模型/模板
	CEpDevice *m_pDevice;         //设备点表数据管理对象
	CEpProtocolBase *m_pProtocol;  //规约模板对象
	CEpDeviceCmmConfig *m_pDeviceCmmConfig;  //设备通讯配置对象
	CEpDeviceCmmChannel *m_pDeviceCmmChannel;    //关联的设备通讯对象
	CEpCmmChannel *m_pUsingChannel;
	
	CEpFrameSendMngr *m_pPkgSendMngr;  //报文帧发送管理对象
			
	//接受帧对象管理:过程执行线程从此获取FrameDetail对象进行跳转的判断
	CExBaseList m_listReceiveFrame;             //解析出来的帧对象

private:
	CEpEngineData *m_pEngineData;
	long m_nCurrPkgLen;

//////////////////////////////////////////////////////////////////////////
//引擎方法定义
public:
	void RunProcedure(const CString &strProcedureID, CExBaseList *pInterface); //执行过程
	void RunProcedure(UINT nClassID); //执行过程
	void RunProcedure(CEpProcedure *pProcedure); //执行过程
	void AddReceiveFrameDetail(CEpFrameBase *pPkg);//添加解析完成的帧对象到临时列表
		
	//模板 加载/卸载
	void LoadTemplate(const CString &strTemplageFile);
	void UnLoad();
		
	//设备连接、断开管理
	BOOL ConnectDevice();
	BOOL CmmChannelConfig();
	BOOL DisConnectDevice();

	//数据接受,关联的m_pChannel对象收到数据后,通知EngineThread对象
	void OnReceived(CEpCmmRcvSndTime *pCmmTime);
	
	// 缓冲区处理
	void CreateParseBufferPos(EPBUFFERPOS &oBufPos);
	
	//获取通讯通道
	CEpCmmChannel* GetCmmChannel(const CString &strCmmChannelID);
	CEpCmmChannel* GetCmmChannel(CEpNode *pNode);

	//添加发送报文对象
	CEpFrameBase* AddFrameSend(CEpProcedure *pEpProcedureRun);

	// 设备通讯配置数据管理
	void CopyDeviceCmmConfig(CEpDeviceCmmConfig *pDes, CEpDeviceCmmConfig* pSrc);
	CExBaseObject* FindByClassID(UINT nClassID, CExBaseList* pList);

	void SetCurrPkgLen(long nLen)   {    m_nCurrPkgLen = nLen;   }

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void ExitEngineThread() ;
	BOOL IsThreadExitExtern();

	//监视报文
	void LogProtocol(CExBaseObject *pDevice, LPVOID pPara, EPBUFFERPOS &oBufPos);
	void RecordSendFrame();

private:
	BOOL IsThreadExit();
	long m_nThreadExitState;

private:
	//发送接收处理线程
	static UINT PkgSendReceiveThread(LPVOID pParam);

	//////////////////////////////////////////////////////////////////////////
	//规约过程执行相关

	//过程执行线程从此取得过程加入到执行过程列表
	CExBaseList m_listProcedureToRun;	             //过程临时列表,将要执行的过程列表
	CExBaseList m_listRunProcedure;	                 //执行的过程列表
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listProcedureTemp访问的互斥量

	//Engine Thread相关的处理
	CWinThread *m_pProcedureRunThread;
	BOOL m_bExitEngineThread;

	//过程处理线程:死循环，不断遍历
	static UINT ProcedureRunThread(LPVOID pParam);
	CEpProcedure* FindRunningProcedure(const CString &strProcedureID);

//	void InitFrameTime(CEpFrameDetail *pPkg, CEpCmmRcvSndTime *pTm);
	void AddTempProcedureToRun();


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void AFX_MSG_CALL OnChannelReceive(WPARAM wParam, LPARAM lParam); 
	afx_msg void AFX_MSG_CALL OnConnectDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnDisConnectDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnExitEngineThread(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnDeleteAllRecordFrame(WPARAM wParam, LPARAM lParam);
};


