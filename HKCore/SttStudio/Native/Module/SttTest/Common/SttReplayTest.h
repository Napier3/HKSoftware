#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"tmt_replay_test.h"

#ifdef _PSX_QT_LINUX_
#include"../../SttDevice/SttDeviceBase.h"
#endif
#include "../../ReplayTest/SttComtradeRcvSocket.h"
#include "../../ReplayTest/ComtradeBufMngr.h"
#include "../../Engine/SttTestServerBase.h"


class CSttReplayTest : public CSttTestBase, public tmt_ReplayParas
{
public:
    CSttReplayTest();
    virtual ~CSttReplayTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttReplayTest();
	}
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	int m_nModuleSelCount;
	int m_nChSelCount;


	//�����м仺�棬��СӦ���ǹ���������󻺴�
	float *m_pOnceProcessBuf;
	float *m_pProcessBuf;

	int m_nCurrReqIndex;	//��ǰ��Ҫ����ABBuf Index
	int m_nCurrPlayIndex;	//����Index

	BOOL m_bSendFinish;		//Comtrade�ļ����ݷ�����

    float m_arrLastPoint[80];//ÿ�β�ֵ���һ��������,��80·�ط�ͨ��Ԥ����ʵ���ܴ������ƻ���

#ifndef _SttTestServer_For_Debug_
	drv_LtReplayCoef m_ReplayConf;
	drv_structLtBuffer *m_pStructLtBuffer;
#endif

public:
	virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Init();
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual BOOL EventProcess();
	virtual void Stop();

	virtual void Triger();
	virtual void OnSendDataFinish(int nIndex,int nSendNum);
	virtual void OnSendDataStart(int nIndex,int nSendNum);
	virtual void OnAfterMoveToComtradeBuf(int nIndex,int nDataLen);

	virtual bool NeedCheckHeartbeat()	{	return false;		}
    //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    virtual void TtmToDrv();

	//nBufType:0ΪLoopBuf,1ΪABuf,2ΪBBuf
	bool QueryDriveBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt,int nBufType);
	//����TRUE:��ʾAB���л�
	bool WriteComtradeDataToDrive1(CComtradeDataBuffer* pComtradeBuf,BYTE *pDriveBuf,int &nDriveWritePos,unsigned int nMaxBlockCnt,int nPreComtradeLeftLen=0);

	void OnceWriteProcessDataToDrive1(BYTE *pDriveBuf,int &nWritePos,int nPointNum);
	void WriteLoopDataToDrive();
	bool WriteABDataToDrive();
	void SetDriveBufValid(BYTE *pDriveBuf,unsigned int nBlockCnt);

    void StartEventThread();
#ifdef _SttTestServer_For_Debug_
	BYTE *m_pDriverBuf;
	int m_nMaxBlockCnt;

	BOOL m_bReplayStarted;
	HANDLE m_pEventThread;
	static UINT SttEventThread(LPVOID pParam);

	void StopEventThread();
	int GetModuleChPos(int nModulePos,const char *pszChID);
	long CalReplayDataValue(int nModulePos,const char *pszChID, float fRawVal);
#endif

};
