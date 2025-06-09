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
	CPpChnTestThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
//�������ݶ���
public:
	CDeviceCmmConfig *m_pDeviceCmmConfig;  //�豸ͨѶ���ö���
	CDeviceCmmChannel *m_pDeviceCmmChannel;    //�������豸ͨѶ����
	CCmmChannel *m_pUsingChannel;

	CPpPackageSendMngr *m_pPkgSendMngr;  //����֡���͹������
			
	//����֡�������:����ִ���̴߳Ӵ˻�ȡPackageDetail���������ת���ж�
	CExBaseList m_listReceivePackage;       //����������֡����
	CPpRecordMngr *m_pPpRecordMngr;         //¼����Լ֡�������
	
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
//���淽������
public:
	//�豸���ӡ��Ͽ�����
	BOOL ConnectDevice();
	BOOL CmmChannelConfig();
	BOOL DisConnectDevice();

	//���ݽ���,������m_pChannel�����յ����ݺ�,֪ͨEngineThread����
	void OnReceived(CCmmRcvSndTime *pCmmTime);
	
	// ����������
	void CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos);
	void CreateParseBufferPos(CYCLEMEMBUFFERPOS &oBufPos, long nBeginPos, long nEndPos);
	void LogErrorParse(long nBeginPos, long nLength);
	
	//��ȡͨѶͨ��
	CCmmChannel* GetCmmChannel(const CString &strCmmChannelID);

	//��ӷ��ͱ��Ķ���
	CPpPackageSend* AddPackageSend();
	void DeleteAllPackageSend();

	// �豸ͨѶ�������ݹ���
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

	//���ӱ���
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


