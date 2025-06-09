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
	CEpEngineThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
//�������ݶ���
public:
	
	//CCycleMemBuffer m_oReceiveBuffer;   //���ջ������������

	//ģ��/ģ��
	CEpDevice *m_pDevice;         //�豸������ݹ������
	CEpProtocolBase *m_pProtocol;  //��Լģ�����
	CEpDeviceCmmConfig *m_pDeviceCmmConfig;  //�豸ͨѶ���ö���
	CEpDeviceCmmChannel *m_pDeviceCmmChannel;    //�������豸ͨѶ����
	CEpCmmChannel *m_pUsingChannel;
	
	CEpFrameSendMngr *m_pPkgSendMngr;  //����֡���͹������
			
	//����֡�������:����ִ���̴߳Ӵ˻�ȡFrameDetail���������ת���ж�
	CExBaseList m_listReceiveFrame;             //����������֡����

private:
	CEpEngineData *m_pEngineData;
	long m_nCurrPkgLen;

//////////////////////////////////////////////////////////////////////////
//���淽������
public:
	void RunProcedure(const CString &strProcedureID, CExBaseList *pInterface); //ִ�й���
	void RunProcedure(UINT nClassID); //ִ�й���
	void RunProcedure(CEpProcedure *pProcedure); //ִ�й���
	void AddReceiveFrameDetail(CEpFrameBase *pPkg);//��ӽ�����ɵ�֡������ʱ�б�
		
	//ģ�� ����/ж��
	void LoadTemplate(const CString &strTemplageFile);
	void UnLoad();
		
	//�豸���ӡ��Ͽ�����
	BOOL ConnectDevice();
	BOOL CmmChannelConfig();
	BOOL DisConnectDevice();

	//���ݽ���,������m_pChannel�����յ����ݺ�,֪ͨEngineThread����
	void OnReceived(CEpCmmRcvSndTime *pCmmTime);
	
	// ����������
	void CreateParseBufferPos(EPBUFFERPOS &oBufPos);
	
	//��ȡͨѶͨ��
	CEpCmmChannel* GetCmmChannel(const CString &strCmmChannelID);
	CEpCmmChannel* GetCmmChannel(CEpNode *pNode);

	//��ӷ��ͱ��Ķ���
	CEpFrameBase* AddFrameSend(CEpProcedure *pEpProcedureRun);

	// �豸ͨѶ�������ݹ���
	void CopyDeviceCmmConfig(CEpDeviceCmmConfig *pDes, CEpDeviceCmmConfig* pSrc);
	CExBaseObject* FindByClassID(UINT nClassID, CExBaseList* pList);

	void SetCurrPkgLen(long nLen)   {    m_nCurrPkgLen = nLen;   }

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void ExitEngineThread() ;
	BOOL IsThreadExitExtern();

	//���ӱ���
	void LogProtocol(CExBaseObject *pDevice, LPVOID pPara, EPBUFFERPOS &oBufPos);
	void RecordSendFrame();

private:
	BOOL IsThreadExit();
	long m_nThreadExitState;

private:
	//���ͽ��մ����߳�
	static UINT PkgSendReceiveThread(LPVOID pParam);

	//////////////////////////////////////////////////////////////////////////
	//��Լ����ִ�����

	//����ִ���̴߳Ӵ�ȡ�ù��̼��뵽ִ�й����б�
	CExBaseList m_listProcedureToRun;	             //������ʱ�б�,��Ҫִ�еĹ����б�
	CExBaseList m_listRunProcedure;	                 //ִ�еĹ����б�
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listProcedureTemp���ʵĻ�����

	//Engine Thread��صĴ���
	CWinThread *m_pProcedureRunThread;
	BOOL m_bExitEngineThread;

	//���̴����߳�:��ѭ�������ϱ���
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


