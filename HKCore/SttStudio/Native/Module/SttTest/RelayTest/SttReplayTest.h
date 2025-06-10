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

	//处理中间缓存，大小应该是共享缓存中最大缓存
	float *m_pOnceProcessBuf;
	float *m_pProcessBuf;

	int m_nCurrReqIndex;	//当前需要请求ABBuf Index
	int m_nCurrPlayIndex;	//播放Index
	BOOL m_bTrigger;
	BOOL m_bSendFinish;		//Comtrade文件数据发送完

	int m_nPlayTotalBlockCnt;//写驱动缓存Block计数
	float m_arrLastPoint[100];//每次插值最后一个点数据

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

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();

	bool QueryEmptyDriveABBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt);
	//nBufType:0为LoopBuf,1为ABuf,2为BBuf
	bool QueryDriveBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt,int nBufType);
	//返回TRUE:表示AB已切换
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
