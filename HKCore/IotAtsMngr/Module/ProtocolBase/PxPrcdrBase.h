#pragma once

#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../SttStudio/Module/CmmInterface/SttCmmInterface.h"
#include "PxPkgBase.h"

#define PrcdrState_Step_NULL	0
#define PrcdrState_Step_1		1
#define PrcdrState_Step_2		2
#define PrcdrState_Step_3		3
#define PrcdrState_Step_4		4
#define PrcdrState_Step_End		0xff

class CPxProtocolBase;

class CPxPrcdrBase:public CExBaseList
{//�Ӷ���Ϊ���ͺͽ��ձ��Ķ���
public:
	CPxPrcdrBase();
	virtual ~CPxPrcdrBase();

public:
	//m_strID:ProcedureID
	CString m_strDeviceID;			//��ǰ��������װ��
	CString m_strResultEvent;		//���̽����:0:
	long m_nProcedureState;			//����״̬����0xFF:���̽���
	CString m_strRecordMode;		//¼��ģʽ

	CExBaseList m_listRecvPkg;	//���̽��ձ�������
	CExBaseList m_listSendPkg;	//���̷��ͱ�������

	SYSTEMTIME m_tmBeginTime;//��ʼʱ�䣬���ڼ�ⱨ���Ƿ��ʱ
	DWORD m_dwBeginTime;
	long m_nOverTimeLong;	//��ʱ����,���ݾ����״̬�ж��Ƿ�ʱ

	CDvmDataset *m_pRefDataset;	//�������ݼ�
	CDvmData m_oDataInterface;//�����б�
	CSttCmmOptrInterface *m_pPxCmmInterface;//���ڷ��ͱ���
	CPxProtocolBase *m_pPxProtocolRef;		//����Э�����

public:
	//ѭ��ִ�У��жϳ�ʱ���ͱ��ģ����̽�������TRUE
	virtual BOOL Run();
	void DeletePkgList();	//����ɾ����־�������������

	BOOL IsProcedureEnd()	{return m_nProcedureState == PrcdrState_Step_End;}
	CString GetResultEvent(){return m_strResultEvent;}
	void SetResultEvent(const CString &strEventID){m_strResultEvent = strEventID;}
	void InitProcedure(const CString &strDeviceID,const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode);
	void ResetTimer();
	void KillTimer();
	BOOL IsTimerOut(DWORD dwCurTime);
	void SetProcedureState(long nState){m_nProcedureState = nState;}
	void SetPxProtocol(CPxProtocolBase *pPxProtocol){m_pPxProtocolRef = pPxProtocol;}
	void SetPxCmmOptrInterface(CSttCmmOptrInterface *pPxCmmInterface){m_pPxCmmInterface = pPxCmmInterface;}

	//���Ĵ���ӿ�
public:
	//�������б�,����ǰӦ���ģ�����TRUE,���򷵻�FALSE
	BOOL ProcessRecvPkgs();
	//�������߼�������Ӧ�𣬴���Ӧ�𣬷���TRUE,���򷵻�FALSE
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail){return FALSE;}
	//����Ӧ�����߼�
	virtual BOOL ProcessPackageAck(CPxPkgBase *pPkgDetail){return FALSE;}

	virtual CDvmData* GetDataInterface()	{	return &m_oDataInterface;		}
	
	virtual void UpdateNodeTimers(CDvmDataset *pAttrs){};
};
