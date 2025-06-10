#pragma once

#include "ComtradeBufMngr.h"
#include "BigComtradeFileRead.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"
#include "ComtradeSendSocket.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
//#include "../Engine/SttTestEngineBase.h"


class CBigComtradeTransPlay : /*public CSttTestMsgViewInterface,*/public CTestEventBaseInterface
{
//2022-11-13  lijunqing
private:
	static CBigComtradeTransPlay *g_pBigComtradeTransPlay;
	static long g_nBigComtradeTransPlay;

public:
	static void Create();
	static void Create(CSttTestAppCfg *pSttTestAppCfg);
	static void Release();

public:
	CBigComtradeTransPlay(void);
	virtual ~CBigComtradeTransPlay(void);
	long GetPlaySampleRate();

	//20221028 zhouhj ¼��ͨ���ӿ�
	virtual long Event_OnProcessComtradeRequstData(long nIndex);
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex);
	void FreeClientEngine();

	BOOL m_bDrawSrcComtrade;  //2021-11-2  lijuniqing true������ԭʼcomtrade����ͼ��false������ͨ������ͼ
	CBigComtradeFileRead m_oBigComtradeFileRead;	//Comtrade�ļ���������
	CComtradePlayConfig m_oComtradePlayConfig;		//�ط����ö���

private:
	BOOL ComtradeControl_ConnServer(const CString &strIP);
	//���ϻطŵ�¼socket,��Ϊ���ݷ���socket��
	CSttClientSocket m_oComtradeClientSocket;
	CComtradeSendSocket m_oComtradeSendSocket;
	CSttTestEngineClientData *m_pTestEngineClientData;

	BOOL m_bExitThread;
	BOOL m_bUseExternSttTestAppCfg;//����Ƿ�ʹ���ⲿCSttTestAppCfg����,δʹ���ⲿ����,������������,��Ҫ�����ڲ�����
	void WaitForThreadExit();

public:
	//����Ӳ�������ļ���ʼ�����ö���
	BOOL UpdateChMapConfig();
	BOOL SaveComtradeReplayConfig(const CString &strFile);

	//��Comtrade�ļ��¼�����ӿ�
	BOOL OnOpenComtradeFile(const CString &strComtradeFile,BOOL bInitDefault=TRUE);
	BOOL HasComtradeDataNeedDraw(); //2021-9-19  lijunqing  �Ƿ��в���������Ҫ��ͼ
	CRcdComtradeFile* GetSrcComtradeFile(); //2021-9-20  lijunqing
	CRcdComtradeFile* GetPlayComtradeFile(); //2021-9-20  lijunqing
	void GenerateComtradeChDatas(BOOL bSeekToBegin);

	//��ʼ�����¼�����ӿ�
	void OnStartTest();
	void OnStopTest();

	//�յ�������������
	long OnProcessComtradeRequstData(long nIndex);
	long OnProcessComtradeSendDataStartAck(long nIndex);

	//���Ӳ����Ǻ󴴽����ϻط�ͨ��
	BOOL CreateSttComtradeSocket();

	CExBaseList *GetAnalogs();
	CExBaseList *GetRates();
	CExBaseList *GetBinarys();

	//20230425 zhouhj ��Ϊ¼���ļ������򿪶�Ӧ�����ļ���ʽ
	CSttTestAppCfg *m_pSttTestAppCfg;

	//comtrade�ļ������߳�
	HANDLE m_pSttComtradeFileReadThread;
#ifdef _PSX_QT_LINUX_
    static void* SttComtradeFileReadThread(LPVOID pParam);
#else
	static UINT SttComtradeFileReadThread(LPVOID pParam);	
#endif
};

extern CBigComtradeTransPlay *g_theBigComtradeTransPlay;
extern CSttTestAppCfg g_oSttTestAppCfg;



