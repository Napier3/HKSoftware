#pragma once
#include "../ReplayTest/BigComtradeTransPlay.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../Engine/SttTestEngineClientData.h"

class CVmSttRelayTest
{
public:
	CVmSttRelayTest(void);
	virtual ~CVmSttRelayTest(void);

	long ComtradeReplayTestStart(CString strComtradeFile,CDataGroup *pParas);
	//������ǽ���¼��ͨ�� 19813��¼����¼
	BOOL CreatComtradeSocket();

	//����Comtrade�ļ������뻺��(�����̣߳�
	BOOL AnalysisComtradeData(CString strComtradeFile,BOOL bInitDefault=TRUE);

	//�·�Test_Startָ��
	long Test_TestStart( CDataGroup *pParas);

	//¼��ͨ���յ��ط�������Զ����߳��·��طŲ�������
	void SendComtradeData();

#ifndef _PSX_QT_LINUX_
	HANDLE m_pSendComtradeThread;
	static UINT SendComtradeThread(LPVOID pParam);
#endif

	void SetSttTestEngineClient(CSttTestEngineClientData *pSttTestEngineClientData);
	void InitReplayConfig(CDataGroup *pParas);

protected:
	CString m_strComtradeFile;
	CSttTestEngineClientData *m_pSttTestEngineClientDataRef;
	
};
