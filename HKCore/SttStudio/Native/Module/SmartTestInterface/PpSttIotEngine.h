#pragma once

#include "PpXIotEngineBase.h"
#include "../../../Module/MemBuffer/TxRingPtrBuffer.h"
#define STT_PP_IOT_ENGINE_SPY_DATA_MAX_NUM          100//ѭ���������洢��������


class CPpSttIotDevice : public CPpSttIotDeviceBase, public CTestEventBaseInterface
{
public:
	CPpSttIotDevice();
	virtual ~CPpSttIotDevice();

public:

    CPpSttIotClient *m_pSttIotClient;
	//�¼��ӿ�
	virtual void On_SysState_IOT(CSttSysState *pSysState);

public:
	virtual long X_SendIotCmd(CSttIotCmd &oIotCmd);

	virtual BOOL IsConnectIotServerSucc();
	virtual long IsConnectSuccessful();
	virtual BOOL ConnectSttServer();
	virtual void NewSttIotClient();
    virtual void SetSttCmdDataFormat(long nSttCmdForat);
	virtual void DisConnect();
	virtual void DisConnectForClose(BOOL bDelete);  //�Ͽ�����

	BOOL GetRunProcedureRltValue(const CString &strID,long &nValue);//��ȡͨѶ�������н�� zhouhj 2024.3.14

	//zhouhj 2024.1.23 �������ڱ��ļ���
	virtual long Event_OnPkgSpy(CSttParas *pSttParas);
//	CExBaseList m_oPkgSpyList;
	CTxRingPtrBuffer<CExBaseObject> m_oPkgSpyList;
};

class CPpSttIotEngine : public CPpXIotEngineBase
{
public:
	CPpSttIotEngine();
	virtual ~CPpSttIotEngine(void);

public:
	virtual CPpSttIotDeviceBase* CreateNewDevice();

};
