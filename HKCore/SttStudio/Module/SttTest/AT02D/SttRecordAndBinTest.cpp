#include "SttRecordAndBinTest.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#include "../../Engine/SttTestServerBase.h"
#endif

CString CSttRecordAndBinTest::m_strMacroName = "开入量及GOOSE录波测试";
CString CSttRecordAndBinTest::m_strMacroID = ("RecordAndBinTest");
CString CSttRecordAndBinTest::m_strFilePostFix = "stttst";
CString CSttRecordAndBinTest::m_strMacroVer ="1.0";

CSttRecordAndBinTest::CSttRecordAndBinTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	tmt_RecordParas::init();
}

CSttRecordAndBinTest::~CSttRecordAndBinTest()
{
	if(GetTestStarting())
	{
		Stop();
	}
}

void CSttRecordAndBinTest::Init()
{
	CSttTestBase::Init();
	m_nSubNumber = 0;
}

void CSttRecordAndBinTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);
}

void CSttRecordAndBinTest::StartTest()
{
	if(GetTestStarting())
	{
		Stop();
		Sleep(100);
	}

#ifdef _PSX_QT_LINUX_
	TtmToDrv();
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	CSttDeviceBase::g_pSttDeviceBase->m_nIsIecMode = 2;
	if(!g_oSttRcdSendSocket.m_bRunning)
	{
		g_oSttRcdSendSocket.m_bRunning = TRUE;
		pthread_mutex_unlock(&g_oSttRcdSendMutex);
	}
	if(!bIecRecordRun)
	{
		bIecRecordRun = TRUE;
		pthread_mutex_unlock(&g_oIecRecordMutex);
	}

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x126, 0);//关闭FPGA DMA缓存
	ioctl(nFd, 0x103, 0x15);//硬接点采集
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
	SetTestStarting(TRUE);
}

void CSttRecordAndBinTest::Stop()
{
#ifdef _PSX_QT_LINUX_
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	CSttDeviceBase::g_pSttDeviceBase->m_nIsIecMode = 0;
	if(g_oSttRcdSendSocket.m_bRunning)
	{
		pthread_mutex_lock(&g_oSttRcdSendMutex);
		g_oSttRcdSendSocket.m_bRunning = FALSE;
	}
	if(bIecRecordRun)
	{
		pthread_mutex_lock(&g_oIecRecordMutex);
		bIecRecordRun = FALSE;
	}

	if(CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting)
	{
		pthread_mutex_lock(&g_oTestResultMutex);
		CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting = FALSE;
	}

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x103, 0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
	SetTestStarting(FALSE);
}

BOOL CSttRecordAndBinTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

#ifdef _PSX_QT_LINUX_
	BOOL bTestFinished;
	STT_TIME oTestFinishedTime;
	CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished,oTestFinishedTime);
#endif
	return FALSE;
}

void CSttRecordAndBinTest::TtmToDrv()
{
	char *pszBuf = stt_test_get_drvparas_buff();
	IecRecvCfg *pDrv = (IecRecvCfg *)pszBuf;
	memset(pDrv, 0, sizeof(IecRecvCfg));
	pDrv->ncount = m_nSubNumber;

	if(m_nSubNumber > 0)
	{
		pDrv->nType = 4;

		for(int index = 0; index < m_nSubNumber; index++)
		{
			tmt_RecordPara *pPara = &m_paras[index];
			CString strType = pPara->ntype;
			CString strAppID = pPara->appid;
			strAppID = strAppID.replace("0x", "");
			int nType = 2;
			if(strType == XPARA_ID_TYPE_SMV92)
			{
				nType = 1;
			}
			pDrv->oIecSub[index].CRC = CalCRC(strAppID, pPara->dest_mac,
											  pPara->port.toInt(), nType);
		}
	}
	else
	{
		pDrv->nType = 0;
	}

#ifdef _PSX_QT_LINUX_
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x30C, 1);
	write(nFd, pszBuf, sizeof(IecRecvCfg));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
}
