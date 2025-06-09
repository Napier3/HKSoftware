#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"tmt_replay_test.h"
#ifdef _PSX_IDE_QT_
#include"drv_replay_test.h"
#include "drv_abnormal_test.h"
#include "../../SttDevice/RelayTest/SttDevice.h"
#endif
#include "../../SttDevice/RelayTest/drv_define.h"

#include "../../ReplayTest/SttComtradeRcvSocket.h"
#include "../../ReplayTest/ComtradeBufMngr.h"
#include "../../Engine/SttTestServerBase.h"

#define COMTRADE_PROCESS_BUF_SIZE	2048000	
#define COMTRADE_REPLAY_PKG_POINTS	600
#define COMTRADE_REPLAY_PKG_DATALEN	3600

typedef struct drv_block_pkg
{
	//ģ�����ݿ�
	unsigned int num;
	unsigned int module;
	unsigned int title;
	unsigned int length;
	unsigned int cmd;
	long data[COMTRADE_REPLAY_PKG_DATALEN]; //3600
}Drv_BlockPkg;

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
		CComtradeBufMngr::Create(COMTRADE_LOOPBUF_SIZE,COMTRADE_ABBUF_SIZE);
        return new CSttReplayTest();
	}
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	//��ѡ��ģ�鼯������
	int m_arrSortModuleSel[MAX_MODULE_COUNT];
	int m_nModuleSelCount;
	int m_nChSelCount;
	Drv_BlockPkg *m_pBlockPkgs;

	//�����м仺�棬��СӦ���ǹ���������󻺴�
	int m_arrProcessBuf[COMTRADE_PROCESS_BUF_SIZE];
	int m_nProcessWritePos;
	int m_nProcessReadPos;

	int m_nCurrReqIndex;	//��ǰ��Ҫ����ABBuf Index
	int m_nCurrPlayIndex;	//����Index
	BOOL m_bTrigger;
	BOOL m_bSendFinish;		//Comtrade�ļ����ݷ�����

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

    //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    virtual void TtmToDrv();

	bool QueryEmptyShareABBufInfo(BYTE **ppShareBuf,unsigned int &nMaxBlockCnt);
	bool QueryShareLoopBufInfo(BYTE **ppShareBuf,unsigned int &nMaxBlockCnt);
	//����TRUE:��ʾAB���л�
	bool WriteShareDataFromComtradeBuf(CComtradeDataBuffer* pComtradeBuf,BYTE *pShareBuf,int &nShareWritePos,unsigned int nMaxBlockCnt);
	long CalReplayDataValue(long nRawVal);
	void UpdateBlockPkgHead(Drv_BlockPkg *pBlockPkg,int nModuleIndex,long nLen);
	void WriteShareData(BYTE *pShareBuf,int &nWritePos);
	void WriteLastShareData(BYTE *pShareBuf,int &nWritePos);
	void WriteShareLoopData();
	void SetShareBufValid(BYTE *pShareBuf,unsigned int nBlockCnt);
};
