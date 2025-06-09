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
	CPpEngineThreadBase();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
//�������ݶ���
public:
	
	//CCycleMemBuffer m_oReceiveBuffer;   //���ջ������������

	//ģ��/ģ��
	CPpDvmDevice *m_pDeviceRef;         //�豸������ݹ������
	CPpTemplate *m_pTemplate;  //��Լģ�����
	CDeviceCmmConfig *m_pDeviceCmmConfigRef;  //�豸ͨѶ���ö���
	CDeviceCmmChannel *m_pDeviceCmmChannel;    //�������豸ͨѶ����
	CCmmChannel *m_pUsingChannel;
	BOOL m_bIsInThreadParse;
	
	CPpPackageSendMngr *m_pPkgSendMngr;  //����֡���͹������
			
	//����֡�������:����ִ���̴߳Ӵ˻�ȡPackageDetail���������ת���ж�
	CExBaseList m_listReceivePackage;             //����������֡����

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

	//�յ����ġ��������ļ������Ļ������
	CAutoCriticSection m_oParsePkgCriticSection; 
	long  m_nPkgRcvCounter;

public:
	long GetSendTickLong();
	long GetRecvTickLong();
	void ResetSendTick();
	void ResetRecvTick();

//////////////////////////////////////////////////////////////////////////
//���淽������
public:
	BOOL IsProcedureExist(const CString &strProcedureID); 
	BOOL RunProcedure(const CString &strProcedureID, CExBaseList *pInterface, BOOL bIsInit); //ִ�й���
	void KillProcedure(const CString &strProcedureID, CExBaseList *pInterface = NULL); //ִ�й���
	void AddReceivePackageDetail(CPpPackageDetail *pPkg);//��ӽ�����ɵ�֡������ʱ�б�
	void ViewProcedure();
		
	//ģ�� ����/ж��
	void LoadTemplate(const CString &strTemplageFile);
	void UnLoad();
		
	//�豸���ӡ��Ͽ�����
	BOOL ConnectDevice();
	BOOL CmmChannelConfig();
	BOOL UnloadDevice();
	BOOL DisConnectDevice();

	//���ݽ���,������m_pChannel�����յ����ݺ�,֪ͨEngineThread����
	void OnReceived(CCmmRcvSndTime *pCmmTime);
	void Parse(BOOL &bNeedRunProcedure); //bNeedRunProcedure  2019-5-27

#ifdef _use_CMemBufferList
	void Parse_Buff_List();
#endif

	BOOL EnterParse_FromPpRunThread();
	
	// ����������
	void CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos);
	void CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos, CCmmRcvSndTime *pCmmTime);
	void CreateParseBufferPos(CYCLEMEMBUFFERPOS &oBufPos, long nBeginPos, long nEndPos);
	void LogErrorParse(long nBeginPos, long nLength, PACKAGEBUFFERPOS *pBufPos);
	
	//��ȡͨѶͨ��
	CCmmChannel* GetCmmChannel(const CString &strCmmChannelID);
	CCmmChannel* GetCmmChannel(CPpNode *pNode);

	//��ӷ��ͱ��Ķ���
	CPpPackageSend* AddPackageSend(CPpProcedureRun *pPpProcedureRun);

	// �豸ͨѶ�������ݹ���
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

	//���ӱ���
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
	//���ͽ��մ����߳�
	static UINT PkgSendReceiveThread(LPVOID pParam);

	//////////////////////////////////////////////////////////////////////////
	//��Լ����ִ�����

	//����ִ���̴߳Ӵ�ȡ�ù��̼��뵽ִ�й����б�
	CExBaseList m_listProcedureToRun;	             //������ʱ�б�,��Ҫִ�еĹ����б�
	CExBaseList m_listRunProcedure;	                 //ִ�еĹ����б�
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listProcedureTemp���ʵĻ�����

	//Engine Thread��صĴ���
#ifdef _PSX_QT_LINUX_
    pthread_t m_pProcedureRunThread;
#else
	CWinThread *m_pProcedureRunThread;
#endif

	BOOL m_bExitEngineThread;

	//���̴����߳�:��ѭ�������ϱ���
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

