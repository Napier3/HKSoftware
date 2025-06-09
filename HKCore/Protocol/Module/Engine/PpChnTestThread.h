#pragma once


#include "../../../Module/MemBuffer/CycleMemBuffer.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#include "DeviceModel/DevcieModel.h"
#include "CmmChannel/DeviceCmmChannel.h"

#include "PpPackageSendMngr.h"
#include "PpRecordMngr.h"
#include "PpDataInterface.h"
#include "PpEngineDataMngrCntr.h"


extern CString g_strChnTestCmd_Serial;     // = _T("port-test-serial");
extern CString g_strChnTestCmd_UdpClient;  // = _T("port-test-udp-client");
extern CString g_strChnTestCmd_UdpServer;  // = _T("port-test-udp-server");
extern CString g_strChnTestCmd_TcpClient;  // = _T("port-test-tcp-client");
extern CString g_strChnTestCmd_TcpServer;  // = _T("port-test-tcp-server");
extern CString g_strChnTestCmd_Exit;       // = _T("port-test-exit");

// CPpChnTestThread

class CPpChnTestThread;

class CChnTestThreadWnd : public CWnd
{
	DECLARE_DYNAMIC(CChnTestThreadWnd)

public:
	CChnTestThreadWnd();
	virtual ~CChnTestThreadWnd();
	BOOL CreateTestControlWnd();
	CPpChnTestThread *m_pPpChnTestThread;

	void SetTestTimer(UINT nTimerID, UINT nTimerLong)
	{
		SetTimer(nTimerID, nTimerLong, NULL);
	}

	void KillTestTimer(UINT nTimerID)
	{
		KillTimer(nTimerID);
	}

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


class CPpChnTestThread : public CWinThread
{
	DECLARE_DYNCREATE(CPpChnTestThread)

protected:
	CPpChnTestThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CPpChnTestThread();
	BOOL m_bHasPostWmquit;


public:
	void PostConnectDeviceMsg();
	BOOL IsConnecting();
	BOOL IsConnectSuccessful();
	void OnDeviceConnectFinish(BOOL bSucc);

	static CPpChnTestThread* CreateEngineThread()
	{
		CPpChnTestThread *pThread = (CPpChnTestThread*)AfxBeginThread(RUNTIME_CLASS(CPpChnTestThread));
		pThread->m_bAutoDelete = TRUE;
		pThread->ResumeThread();
		return pThread;
	}

	void SetDeleteEngineDataInExit(BOOL b)	{	m_bDeleteEngineDataInExit = b;	}
	void ChnTest(const CString &strChnTestID, CDeviceCmmConfig *pDeviceCmmConfig, long nMaxTimeLong);
	void ChnTest();

	CPoDeviceProcedureInterface *m_pPoDeviceProcedureInterface;

//////////////////////////////////////////////////////////////////////////
//引擎数据定义
public:
	CDeviceCmmConfig *m_pDeviceCmmConfig;  //设备通讯配置对象
	CDeviceCmmChannel *m_pDeviceCmmChannel;    //关联的设备通讯对象
	CCmmChannel *m_pUsingChannel;

	CPpPackageSendMngr *m_pPkgSendMngr;  //报文帧发送管理对象
			
	//接受帧对象管理:过程执行线程从此获取PackageDetail对象进行跳转的判断
	CExBaseList m_listReceivePackage;       //解析出来的帧对象
	CPpRecordMngr *m_pPpRecordMngr;         //录波规约帧管理对象
	
private:
	UINT   m_nChnTestOverTimerID;
	UINT   m_nChnTestTimerID;
	long   m_nMaxTestTimeLong;
	long   m_nChnTestTimeCount;
	CString m_strChnTestID;
	BOOL   m_bHasPostFinishMsg;

private:
	BOOL m_bDeleteEngineDataInExit;
	BOOL m_bExitEngineThread;

	CChnTestThreadWnd *m_pChnTestThreadWnd;

//////////////////////////////////////////////////////////////////////////
//引擎方法定义
public:
	//设备连接、断开管理
	BOOL ConnectDevice();
	BOOL CmmChannelConfig();
	BOOL DisConnectDevice();

	//数据接受,关联的m_pChannel对象收到数据后,通知EngineThread对象
	void OnReceived(CCmmRcvSndTime *pCmmTime);
	
	// 缓冲区处理
	void CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos);
	void CreateParseBufferPos(CYCLEMEMBUFFERPOS &oBufPos, long nBeginPos, long nEndPos);
	void LogErrorParse(long nBeginPos, long nLength);
	
	//获取通讯通道
	CCmmChannel* GetCmmChannel(const CString &strCmmChannelID);

	//添加发送报文对象
	CPpPackageSend* AddPackageSend();
	void DeleteAllPackageSend();

	// 设备通讯配置数据管理
	CExBaseObject* FindByClassID(UINT nClassID, CExBaseList* pList);

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
	void LogProtocol(CExBaseObject *pDevice, LPVOID pPara, CYCLEMEMBUFFERPOS &oBufPos, BOOL bRecv=TRUE, const CString &strTime=_T(""));
	void LogProtocol(CYCLEMEMBUFFERPOS &oBufPos, CString &strMsg);
	void RecordSendPackage();

	void OnTimer(UINT nIDEvent, LPARAM param);	

private:
	BOOL IsThreadExit();
	long m_nThreadExitState;

private:
	void InitPackageTime(CPpPackageDetail *pPkg, long nBeginPos);
	void AddTempProcedureToRun();

	void LogAllProcedure();
	void KillProcedure();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void AFX_MSG_CALL OnChannelReceive(WPARAM wParam, LPARAM lParam); 
	afx_msg void AFX_MSG_CALL OnExitEngineThread(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnConnectDeviceFinished(WPARAM wParam, LPARAM lParam);
	afx_msg void AFX_MSG_CALL OnDeleteAllRecordPackage(WPARAM wParam, LPARAM lParam);
};


