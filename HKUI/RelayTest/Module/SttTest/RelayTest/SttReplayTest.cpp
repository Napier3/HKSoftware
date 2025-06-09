#include "stdafx.h"
#include"SttReplayTest.h"
// #include<QtDebug>
#ifdef _PSX_IDE_QT_
#include <unistd.h>
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#endif

CString CSttReplayTest::m_strMacroName = "故障重放测试";
CString CSttReplayTest::m_strMacroID = ("SttReplayTest");
CString CSttReplayTest::m_strFilePostFix = "sttreplaytst";
CString CSttReplayTest::m_strMacroVer ="1.0";

CSttReplayTest::CSttReplayTest() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;

	m_nCurrReqIndex = 0;	//当前需要请求ABBuf Index
	m_nCurrPlayIndex = 1;	//播放Index
	m_bTrigger = FALSE;

	m_pBlockPkgs = NULL;
	m_nChSelCount = 0;
	m_nModuleSelCount = 0;
	memset(m_arrSortModuleSel,0,sizeof(int)*MAX_MODULE_COUNT);

	m_nProcessWritePos = 0;
	m_nProcessReadPos = 0;
	memset(m_arrProcessBuf,0,sizeof(int)*COMTRADE_PROCESS_BUF_SIZE);

    Init();
}

void CSttReplayTest::Init()
{ 
    tmt_ReplayTest::init();
	CSttTestBase::Init();
}

long CSttReplayTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttReplayTest::~CSttReplayTest(void)
{
}

void CSttReplayTest::AfterSetParameter()
{
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;

}

bool CSttReplayTest::QueryEmptyShareABBufInfo(BYTE **ppShareBuf,unsigned int &nMaxBlockCnt)
{//调用驱动接口，查询空共享缓存信息：起始位置和最大数据块数
	return true;
}

bool CSttReplayTest::QueryShareLoopBufInfo(BYTE **ppShareBuf,unsigned int &nMaxBlockCnt)
{//调用驱动接口，查询共享Loop缓存信息：起始位置和最大数据块数
	return true;
}

void CSttReplayTest::SetShareBufValid(BYTE *pShareBuf,unsigned int nBlockCnt)
{//设置当前共享缓存有效，并设置有效模块数长度

}

long CSttReplayTest::CalReplayDataValue(long nRawVal)
{//原始值计算为播放数据
	return nRawVal;
}

void CSttReplayTest::UpdateBlockPkgHead(Drv_BlockPkg *pBlockPkg,int nModuleIndex,long nLen)
{//待完善
	pBlockPkg->num = 0;
	pBlockPkg->module = nModuleIndex;//可能需要映射到模块位置
	pBlockPkg->title = 0;
	pBlockPkg->length = nLen;
	pBlockPkg->cmd = 0;	
}

//解析ProcessBuf数据，拼成Pkg写到ShareBuf中，每次写长度为nWriteLen
void CSttReplayTest::WriteShareData(BYTE *pShareBuf,int &nWritePos)
{
	//每次写共享缓存长度
	int nWriteLen = sizeof(Drv_BlockPkg)*m_nModuleSelCount;

	//每次解析ProcessBuf，都是从头开始
	m_nProcessReadPos = 0;

	//每次解析ComtradeBuf数据长度
	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;

	while(m_nProcessWritePos - m_nProcessReadPos >= nOnceProcessLen)
	{
		for (int m=0; m<m_nModuleSelCount; m++)
		{
			//更新第nModuleIndex模块的帧头信息
			int nModuleIndex = m_arrSortModuleSel[m];
			UpdateBlockPkgHead(&m_pBlockPkgs[m],nModuleIndex,COMTRADE_REPLAY_PKG_DATALEN);

			//初始化ComtradeBuf解析起始位置
			int nOffset = m_nProcessReadPos;

			//当前模块通道数
			int nChs = m_nModuleChNum[nModuleIndex];

			for (int n=0; n<m; n++)
			{
				nOffset += m_nModuleChNum[m_arrSortModuleSel[n]];
			}

			for (int i=0; i<COMTRADE_REPLAY_PKG_POINTS; i++)
			{
				nOffset += i*m_nChSelCount; 

				//由原始数据转换为播放数据
				for (int j=0; j<6; j++)
				{
					if (j<nChs)
					{
						//需由转换公式计算
						m_pBlockPkgs[m].data[6*i+j] = CalReplayDataValue(m_arrProcessBuf[nOffset+j]);
					}
					else
					{
						m_pBlockPkgs[m].data[6*i+j] = 0;
					}
				}
			}
		}

		m_nProcessReadPos += nOnceProcessLen;
		memcpy(pShareBuf+nWritePos,m_pBlockPkgs,nWriteLen);
		nWritePos += nWriteLen;
	}

	//未处理完的数据搬移到开头位置
	if (m_nProcessWritePos != m_nProcessReadPos)
	{
		m_nProcessWritePos = m_nProcessWritePos-m_nProcessReadPos;
		memcpy(m_arrProcessBuf,m_arrProcessBuf+m_nProcessReadPos,m_nProcessWritePos*sizeof(int));
	}
	else
	{
		m_nProcessWritePos = 0;
	}
	m_nProcessReadPos = 0;
}

//写最后一帧不满600个点的Pkg
void CSttReplayTest::WriteLastShareData(BYTE *pShareBuf,int &nWritePos)
{
	if (m_nProcessWritePos == 0)
	{//ProcessBuf中无数据
		return;
	}

	//每次写共享缓存长度
	int nWriteLen = sizeof(Drv_BlockPkg)*m_nModuleSelCount;

	//每次解析ProcessBuf，都是从头开始
	m_nProcessReadPos = 0;

	//最后数据的通道点数
	int nLastPoints = m_nProcessWritePos / m_nChSelCount;

	for (int m=0; m<m_nModuleSelCount; m++)
	{
		//更新第nModuleIndex模块的帧头信息
		int nModuleIndex = m_arrSortModuleSel[m];
		UpdateBlockPkgHead(&m_pBlockPkgs[m],nModuleIndex,nLastPoints*6);

		//初始化ComtradeBuf解析起始位置
		int nOffset = m_nProcessReadPos;

		//当前模块通道数
		int nChs = m_nModuleChNum[nModuleIndex];

		for (int n=0; n<m; n++)
		{
			nOffset += m_nModuleChNum[m_arrSortModuleSel[n]];
		}

		for (int i=0; i<nLastPoints; i++)
		{
			nOffset += i*m_nChSelCount; 

			//由原始数据转换为播放数据
			for (int j=0; j<6; j++)
			{
				if (j<nChs)
				{
					//需由转换公式计算
					m_pBlockPkgs[m].data[6*i+j] = CalReplayDataValue(m_arrProcessBuf[nOffset+j]);
				}
				else
				{
					m_pBlockPkgs[m].data[6*i+j] = 0;
				}
			}
		}
	}

	memcpy(pShareBuf+nWritePos,m_pBlockPkgs,nWriteLen);
	nWritePos += nWriteLen;

	m_nProcessWritePos = 0;
	m_nProcessReadPos = 0;
}

//中断事件中递归调用，由ComtradeBuf数据到ShareBuf,返回true表示AB切换了
bool CSttReplayTest::WriteShareDataFromComtradeBuf(CComtradeDataBuffer* pComtradeBuf,BYTE *pShareBuf,int &nShareWritePos,unsigned int nMaxBlockCnt)
{
	//每次解析ComtradeBuf数据长度
	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;

	//共享缓存中已经有BlockCnt
	int nHasBlockCnt = nShareWritePos / sizeof(Drv_BlockPkg);
	//共享缓存填满需要ComtradeBuf数据长度
	int nNeedData = (nMaxBlockCnt-nHasBlockCnt) / m_nModuleSelCount * nOnceProcessLen;
	int nCurrComtradeBufLeftLen = pComtradeBuf->GetDataLen();
	int nReadLen = 0;
	bool bRet = (nCurrComtradeBufLeftLen <= nNeedData);

	if (nNeedData <= nCurrComtradeBufLeftLen)
	{//当前ComtradeBuf足够
		nReadLen = pComtradeBuf->ReadData(m_arrProcessBuf+m_nProcessWritePos,nNeedData);
		m_nProcessWritePos += nReadLen;

		WriteShareData(pShareBuf,nShareWritePos);

		//填完后设置有效标志
		SetShareBufValid(pShareBuf,nShareWritePos/sizeof(Drv_BlockPkg));

		if(nNeedData == nCurrComtradeBufLeftLen)
		{
			m_nCurrPlayIndex++;
		}
	}
	else
	{//当前ComtradeBuf不够
		nReadLen = pComtradeBuf->ReadData(m_arrProcessBuf+m_nProcessWritePos,nCurrComtradeBufLeftLen);
		m_nProcessWritePos += nReadLen;

		WriteShareData(pShareBuf,nShareWritePos);

		m_nCurrPlayIndex++;
		pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
		if (!pComtradeBuf->CanRead())
		{
			//写最后不足600点数据
			WriteLastShareData(pShareBuf,nShareWritePos);

			//填完后设置有效标志
			SetShareBufValid(pShareBuf,nShareWritePos/sizeof(Drv_BlockPkg));
		}
		else
		{
			WriteShareDataFromComtradeBuf(pComtradeBuf,pShareBuf,nShareWritePos,nMaxBlockCnt);
		}	
	}

	return bRet;
}

//由LoopBuf到ShareLoopBuf
void CSttReplayTest::WriteShareLoopData()
{
	CComtradeDataBuffer* pLoopBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(0);
	if (!pLoopBuf->CanRead())
	{
		return;
	}

	BYTE *pShareBuf = NULL;
	unsigned int nMaxBlockCnt = 0;

	//查询空共享缓存信息
	if (!QueryShareLoopBufInfo(&pShareBuf,nMaxBlockCnt))
	{
		return;
	}

	//初始化处理缓存
	int nShareWritePos = 0;
	m_nProcessWritePos = 0;
	m_nProcessReadPos = 0;

	//每次解析ComtradeBuf数据长度
	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;

	//共享缓存填满需要ComtradeBuf数据长度
	int nNeedData = nMaxBlockCnt / m_nModuleSelCount * nOnceProcessLen;
	int nCurrComtradeBufLeftLen = pLoopBuf->GetDataLen();

	if (nCurrComtradeBufLeftLen > nNeedData)
	{//出错
		return;
	}

	int nReadLen = pLoopBuf->ReadData(m_arrProcessBuf,nCurrComtradeBufLeftLen);
	m_nProcessWritePos += nReadLen;

	WriteShareData(pShareBuf,nShareWritePos);

	//填完后设置有效标志
	SetShareBufValid(pShareBuf,nShareWritePos/sizeof(Drv_BlockPkg));
}

void CSttReplayTest::EventProcess()
{//驱动事件处理
	CComtradeDataBuffer* pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
	if (!pComtradeBuf->CanRead())
	{
		return;
	}

	BYTE *pShareBuf = NULL;
	unsigned int nMaxBlockCnt = 0;

	//查询空共享缓存信息
	if (!QueryEmptyShareABBufInfo(&pShareBuf,nMaxBlockCnt))
	{
		return;
	}

	//初始化处理缓存
	int nShareWritePos = 0;
	m_nProcessWritePos = 0;
	m_nProcessReadPos = 0;

	if (WriteShareDataFromComtradeBuf(pComtradeBuf,pShareBuf,nShareWritePos,nMaxBlockCnt))
	{//AB已切换
		if(!m_bSendFinish)
		{
			CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
			ASSERT(pServerEngine != NULL);
			pServerEngine->Comtrade_SendRequestData(m_nCurrReqIndex);
		}
	}
}

void CSttReplayTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttReplayTest::Stop()
{	
//	m_Start=false;
    CSttTestBase::Stop();
}

void CSttReplayTest::Triger()
{//收到手动触发命令
	m_bTrigger = TRUE;

	//通知驱动手动触发
}

void CSttReplayTest::OnSendDataFinish(int nIndex,int nSendNum)
{//Comtrade数据发送完成命令
	UINT nSendIndex = (UINT)nIndex & 0x7FFFFFFF;
	m_bSendFinish = nIndex & 0x80000000;
	m_nCurrReqIndex++;

	//将接收线程数据搬移到ComtradeBuf中
	g_oSttComtradeRcvSocket.MoveToComtradeBuf(nSendIndex,nSendNum);

	CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);

	if (nSendIndex == 0)
	{//之前请求的是LoopBuf数据，再请求ABuf数据

		//将LoopBuf中数据搬移到共享LoopBuf中
		WriteShareLoopData();

		pServerEngine->Comtrade_SendRequestData(1);
	}
	else if (nSendIndex == 1)
	{//之前请求的是ABuf数据
		if (!m_bSendFinish)
		{//数据未发完，继续请求BBuf数据
			pServerEngine->Comtrade_SendRequestData(2);
		}
		else
		{//数据已发完，
			//通知驱动开始回放
		}
	}
	else if (nSendIndex == 2)
	{//之前第一次请求的是BBuf数据
		//通知驱动开始回放
	}
}

#define REPLAY_FLAG_WRITE_FINISH        0x01
#define REPLAY_FLAG_TEST_FINISH			0x02
#define REPLAY_FLAG_TEST_TRIP           0x03

void CSttReplayTest::StartTest()
{	
	CSttTestBase::StartTest();
//    qDebug()<<__FUNCTION__<<__LINE__<<__FILE__;

	//更新已选择模块集中数组，便于后面拼数据
	SortModuleSelArray(m_arrSortModuleSel,m_nModuleSelCount,m_nChSelCount);
	if (m_nModuleSelCount == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("error m_nModuleCount == 0"));
		return;
	}
	if (m_pBlockPkgs != NULL)
	{
		delete m_pBlockPkgs;
	}
	m_pBlockPkgs = new Drv_BlockPkg[m_nModuleSelCount];

    TtmToDrv();

// #ifdef _PSX_IDE_QT_
//     CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ReplayTestCfg, (char*)&m_oDrvReplayParam, sizeof(m_oDrvReplayParam));
//     for(int i=0;i<12;i++)
//     {
//         int nSend = selectChannel(i, &this->m_oReplayPara);
//         if(nSend == 1)
//         {
//             break;
//         }
//     }
//     while(true)
//     {
//         sleep(1);
//         switch(CSttDriverOper::readReplayIrp())
//         {
//         case REPLAY_FLAG_WRITE_FINISH:
//             qDebug()<<"REPLAY_FLAG_WRITE_FINISH"<<endl;
//             CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ReplayTest);
//             qDebug()<<"Start Replay";
//             break;
//         case REPLAY_FLAG_TEST_FINISH:
//             qDebug()<<"REPLAY_FLAG_TEST_FINISH"<<endl;
//             return;
//             break;
//         case REPLAY_FLAG_TEST_TRIP:
//             qDebug()<<"REPLAY_FLAG_TEST_TRIP"<<endl;
//             return;
//             break;
//         }
// 
//     }
// 
//     qDebug()<<__FUNCTION__<<__LINE__<<__FILE__;
// #endif	
//	m_Start=true;

	//收到开始测试命令后，根据配置参数请求数据
	CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);

	if (IsLoop())
	{//需要循环数据
		m_nCurrReqIndex = 0;
		pServerEngine->Comtrade_SendRequestData(0);
	}
	else
	{//无循环数据
		m_nCurrReqIndex = 1;
		pServerEngine->Comtrade_SendRequestData(1);
	}
}

void CSttReplayTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
 //   tmt_to_drv(&this->m_oReplayPara,  &m_oDrvReplayParam, &m_oDrvReplayData);
#endif
}


