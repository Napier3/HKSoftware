#include "stdafx.h"
#include "VmSttRelayTest.h"
#include "../SttGlobalDef.h"
#include "../SttTest/Common/tmt_replay_test.h"

CVmSttRelayTest::CVmSttRelayTest()
{
	CBigComtradeTransPlay::Create();
	m_pSttTestEngineClientDataRef = NULL;

#ifndef _PSX_QT_LINUX_
	m_pSendComtradeThread = NULL;
#endif
}

CVmSttRelayTest::~CVmSttRelayTest()
{
	CBigComtradeTransPlay::Release();
}

BOOL CVmSttRelayTest::CreatComtradeSocket()
{
	return g_theBigComtradeTransPlay->CreateSttComtradeSocket();
}

BOOL CVmSttRelayTest::AnalysisComtradeData(CString strComtradeFile,BOOL bInitDefault)
{
	m_strComtradeFile = strComtradeFile;
	return g_theBigComtradeTransPlay->OnOpenComtradeFile(m_strComtradeFile,bInitDefault);
}

long CVmSttRelayTest::Test_TestStart(CDataGroup *pParas)
{
	if (m_pSttTestEngineClientDataRef == NULL)
	{
		return -1;
	}

	return m_pSttTestEngineClientDataRef->Test_StartTest(STT_CMD_ATS_MACRO_ID_ReplayTest,pParas);
}

void CVmSttRelayTest::SendComtradeData()
{
#ifndef _PSX_QT_LINUX_
	m_pSendComtradeThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SendComtradeThread,(LPVOID)this,0,NULL);
	//g_theBigComtradeTransPlay->OnStartTest();
#endif
}

#ifndef _PSX_QT_LINUX_
 UINT CVmSttRelayTest::SendComtradeThread(LPVOID pParam)
{
	CVmSttRelayTest *pRelay = (CVmSttRelayTest*)pParam;
	g_theBigComtradeTransPlay->OnStartTest();
	return 0;
}
#endif

void CVmSttRelayTest::SetSttTestEngineClient(CSttTestEngineClientData *pSttTestEngineClientData)
{
	m_pSttTestEngineClientDataRef = pSttTestEngineClientData;
}

void CVmSttRelayTest::InitReplayConfig(CDataGroup *pParas)
{	
	if (g_theBigComtradeTransPlay == NULL)
	{
		return;
	}

	tmt_replay_test oTmtReplayTest;

	CSttDataGroupSerializeRead oRead(pParas);
	stt_xml_serialize(&(oTmtReplayTest.m_oReplayParas),  &oRead);
	//stt_xml_serialize(&oTmtReplayTest, &oRead);
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.GenerateReplayConfigFromTMT(&oTmtReplayTest.m_oReplayParas,true);
}

long CVmSttRelayTest::ComtradeReplayTestStart(CString strComtradeFile,CDataGroup *pParas)
{
	if (!IsFileExist(strComtradeFile))
	{
		return -1;
	}

	/*
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("test_for_replaytest.xml");
	pParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	*/

	//20230515 zhouhj 自动测试条件下,不采用自动生成通道映射,使用参数映射中的内容
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.SetAutoGenChABMap(FALSE);
	InitReplayConfig(pParas);
	CreatComtradeSocket();
	BOOL bRet = AnalysisComtradeData(strComtradeFile, TRUE);

	if (!bRet)
	{
		return -1;
	}

	SendComtradeData();
	return Test_TestStart(pParas);
}
