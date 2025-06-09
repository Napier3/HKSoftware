#pragma once

#include "PxProtoEventInterface.h"
#include "../../../SttStudio/Module/CmmInterface/SttCmmInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CPxProtoDeviceBase;

class CPxProtocolBase// : public CExBaseList
{//m_strID:DeviceSN
public:
	CPxProtocolBase();
	virtual ~CPxProtocolBase();

	CString m_strDeviceID;

public:
	CExBaseList m_listRecvPkg;	//���ձ����ܱ�
	CExBaseList m_listSendPkg;	//���ͱ����ܱ�
	CExBaseList m_listPrcdr;	//ִ�й����ܱ�
	CExBaseList m_listTempPrcdr;	//��ʱ��������
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listTmpPrcdr���ʵĻ�����

	BOOL m_bDvmDeviceAttach;	//FALSE:����ģ�ͣ�TRUE:�ⲿϵͳָ��ģ��
	CDvmDevice *m_pDvmDevice;	//����ģ��
	CString m_strPpxmlFile;
	CString m_strCmmCfgFile;
	CDataGroup *m_pCfgGroup;
	
//	CPxCmmInterface *m_pPxCmmInterface;	//���ڱ��ķ���
	CPxProtoEventInterface *m_pProtoEventInterface;	//����Э���¼�����

	void AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface);
	void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);
	CDvmDataset *UpdateDataset(CDvmDataset *pSrcDataset);
	virtual void UpdateDataset(CDvmDataset* pDataset, const CString &strID, const CString &strPkgData)	{};

	//��ȡ����δ����ı��ģ����ڹ��̴���
	void GetNotProcessedPkgs(CExBaseList &oList);
	void DeleteUnvalidPkgs();

public:
	virtual CPxPrcdrBase* FindProcedure(const CString &strProcedureID);
	void AddProcedureRun(CPxProtoDeviceBase *pProtoDevice, CPxPrcdrBase *pProcedure
		, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode);

public:
	void OnRunProcedure();
	virtual void StartEngineThread();
	virtual void ExitEngineThread();
	BOOL m_bExitEngineThread;
	CWinThread *m_pProcedureRunThread;
	static UINT Engine_ProcedureRunThread(LPVOID pParam);
};

