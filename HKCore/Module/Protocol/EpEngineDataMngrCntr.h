#pragma once

#include "EpGlobalDefine.h"
#include "ProtocolBase\EpProtocolBase.h"
#include "Device\EpDevice.h"
#include "CmmChannel\EpDeviceCmmChannel.h"
#include "EpRecordMngr.h"
#include "..\MessageMngr\MsgSendRegister.h"

class CEpEngineData : public CExBaseObject
{
private:
	CEpEngineData(){}

public:
	CEpEngineData(CEpProtocolBase *pProtocol, CEpDevice *pDevice);
	~CEpEngineData();
	BOOL IsEngineDataValid();
	BOOL InitEngineData(CEpProtocolBase *pProtocol, CEpDevice *pDevice);
	BOOL IsConnectSuccessful();

public:
	//ģ��/ģ��
	CEpDevice *m_pDevice;         //�豸������ݹ������Ϊm_pDevice��Ա
	CEpDeviceCmmConfig *m_pDeviceCmmConfig;  //�豸ͨѶ���ö���Ϊm_pDevice��Ա

	CEpProtocolBase *m_pProtocol;  //��Լģ�����
	CEpRecordMngr *m_pEpRecordMngr;         //¼����Լ֡�������
	CWinThread *m_pEngineThread;

	CMessageMngr m_oMessageMngr;
	CMsgSendRegister m_oSystemMsgSendRegister;

public:
	virtual UINT GetClassID() {  return EPCLASSID_ENGINEDATA;    };

	CMsgSendRegister* Register(ULONG nMsgType, ULONG nHWndOrThreadID, ULONG nMessageID, LPARAM lParam, WPARAM wParam, ULONG nItemData)
	{
		return m_oMessageMngr.Register(nMsgType, nHWndOrThreadID, nMessageID, lParam, wParam, nItemData);
	}
	CMsgSendRegister* Find(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
	{
		return m_oMessageMngr.Find(pMsgRegister, dwMask);
	}
	void UnRegister(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
	{
		m_oMessageMngr.UnRegister(pMsgRegister, dwMask);
	}
	void Register(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
	{
		m_oMessageMngr.Register(pMsgRegister, dwMask);
	}

	void OnProcedureEnd(const CString &strProcedureID)
	{
		m_oMessageMngr.PostMessageByID(strProcedureID);
	}

	void OnDeviceConnectFinish(BOOL bConnectSuccessful);

	BOOL IsThreadExit();
	void ExitEngineThread();

	LONG RecordFrame(const CString &strPkgID)
	{
		return m_pEpRecordMngr->RecordFrame(strPkgID);
	}
	LONG UnRecordFrame(const CString &strPkgID)
	{
		return m_pEpRecordMngr->UnRecordFrame(strPkgID);
	}

	void InitNomVarsScript();
};

class CEpEngineDataMngrCntr :	public CExBaseList
{
public:
	CEpEngineDataMngrCntr(void);
	~CEpEngineDataMngrCntr(void);

public:
	CEpEngineData* Create(CEpProtocolBase *pProtocol, CEpDevice *pDevice);
	CEpEngineData* Find(CEpDevice *pDevice);
	CEpEngineData* Find(CEpProtocolBase *pProtocol);
	CEpEngineData* Find(CEpDeviceCmmConfig *pCmmConfig);

	//��ӽڵ�
	void InsertNodeToTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);
};
