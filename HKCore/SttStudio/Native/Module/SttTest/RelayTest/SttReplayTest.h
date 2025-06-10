#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"tmt_replay_test.h"
#include"drv_replay_test.h"
#include "../../ReplayTest/SttComtradeRcvSocket.h"
#include "../../ReplayTest/ComtradeBufMngr.h"
#include "../../Engine/SttTestServerBase.h"


class CSttReplayTest : public CSttTestBase, public tmt_ReplayTest
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
	Drv_BlockPkg *m_pBlockPkgs;

	//�����м仺�棬��СӦ���ǹ���������󻺴�
	float *m_pOnceProcessBuf;
	float *m_pProcessBuf;

	int m_nCurrReqIndex;	//��ǰ��Ҫ����ABBuf Index
	int m_nCurrPlayIndex;	//����Index
	BOOL m_bTrigger;
	BOOL m_bSendFinish;		//Comtrade�ļ����ݷ�����

	int m_nPlayTotalBlockCnt;//д��������Block����
	float m_arrLastPoint[100];//ÿ�β�ֵ���һ��������

#ifdef _PSX_IDE_QT_
    drv_LtReplayCoef m_ReplayConf;
    drv_structLtBuffer *m_pStructLtBuffer;
    drv_structLtReplayParam m_oDrvLtReplayParam;
#endif

public:
	virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Init();
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void EventProcess();
	virtual void Stop();

	virtual void Triger();
	virtual void OnSendDataFinish(int nIndex,int nSendNum);
	virtual void OnSendDataStart(int nIndex,int nSendNum);
	virtual void OnAfterMoveToComtradeBuf(int nIndex,int nDataLen);

    //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    virtual void TtmToDrv();

	bool QueryEmptyDriveABBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt);
	//nBufType:0ΪLoopBuf,1ΪABuf,2ΪBBuf
	bool QueryDriveBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt,int nBufType);
	//����TRUE:��ʾAB���л�
	bool WriteComtradeDataToDrive1(CComtradeDataBuffer* pComtradeBuf,BYTE *pDriveBuf,int &nDriveWritePos,unsigned int nMaxBlockCnt,int nPreComtradeLeftLen=0);
//	bool WriteComtradeDataToDrive(CComtradeDataBuffer* pComtradeBuf,BYTE *pDriveBuf,int &nShareWritePos,unsigned int nMaxBlockCnt);
	void UpdateBlockPkgHead(Drv_BlockPkg *pBlockPkg,int nModulePos,long nLen);

	void OnceWriteProcessDataToDrive1(BYTE *pDriveBuf,int &nWritePos,int nPointNum);
//	void OnceWriteProcessDataToDrive(BYTE *pDriveBuf,int &nWritePos,int nPointNum);
//	void WriteProcessDataToDrive(BYTE *pDirveBuf,int &nWritePos);
//	void WriteLastProcessDataToDrive(BYTE *pDriveBuf,int &nWritePos);
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
