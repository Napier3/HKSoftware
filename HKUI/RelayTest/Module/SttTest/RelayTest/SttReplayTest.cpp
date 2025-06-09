#include "stdafx.h"
#include"SttReplayTest.h"
// #include<QtDebug>
#ifdef _PSX_IDE_QT_
#include <unistd.h>
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#endif

CString CSttReplayTest::m_strMacroName = "�����طŲ���";
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

	m_nCurrReqIndex = 0;	//��ǰ��Ҫ����ABBuf Index
	m_nCurrPlayIndex = 1;	//����Index
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
{//���������ӿڣ���ѯ�չ�������Ϣ����ʼλ�ú�������ݿ���
	return true;
}

bool CSttReplayTest::QueryShareLoopBufInfo(BYTE **ppShareBuf,unsigned int &nMaxBlockCnt)
{//���������ӿڣ���ѯ����Loop������Ϣ����ʼλ�ú�������ݿ���
	return true;
}

void CSttReplayTest::SetShareBufValid(BYTE *pShareBuf,unsigned int nBlockCnt)
{//���õ�ǰ��������Ч����������Чģ��������

}

long CSttReplayTest::CalReplayDataValue(long nRawVal)
{//ԭʼֵ����Ϊ��������
	return nRawVal;
}

void CSttReplayTest::UpdateBlockPkgHead(Drv_BlockPkg *pBlockPkg,int nModuleIndex,long nLen)
{//������
	pBlockPkg->num = 0;
	pBlockPkg->module = nModuleIndex;//������Ҫӳ�䵽ģ��λ��
	pBlockPkg->title = 0;
	pBlockPkg->length = nLen;
	pBlockPkg->cmd = 0;	
}

//����ProcessBuf���ݣ�ƴ��Pkgд��ShareBuf�У�ÿ��д����ΪnWriteLen
void CSttReplayTest::WriteShareData(BYTE *pShareBuf,int &nWritePos)
{
	//ÿ��д�����泤��
	int nWriteLen = sizeof(Drv_BlockPkg)*m_nModuleSelCount;

	//ÿ�ν���ProcessBuf�����Ǵ�ͷ��ʼ
	m_nProcessReadPos = 0;

	//ÿ�ν���ComtradeBuf���ݳ���
	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;

	while(m_nProcessWritePos - m_nProcessReadPos >= nOnceProcessLen)
	{
		for (int m=0; m<m_nModuleSelCount; m++)
		{
			//���µ�nModuleIndexģ���֡ͷ��Ϣ
			int nModuleIndex = m_arrSortModuleSel[m];
			UpdateBlockPkgHead(&m_pBlockPkgs[m],nModuleIndex,COMTRADE_REPLAY_PKG_DATALEN);

			//��ʼ��ComtradeBuf������ʼλ��
			int nOffset = m_nProcessReadPos;

			//��ǰģ��ͨ����
			int nChs = m_nModuleChNum[nModuleIndex];

			for (int n=0; n<m; n++)
			{
				nOffset += m_nModuleChNum[m_arrSortModuleSel[n]];
			}

			for (int i=0; i<COMTRADE_REPLAY_PKG_POINTS; i++)
			{
				nOffset += i*m_nChSelCount; 

				//��ԭʼ����ת��Ϊ��������
				for (int j=0; j<6; j++)
				{
					if (j<nChs)
					{
						//����ת����ʽ����
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

	//δ����������ݰ��Ƶ���ͷλ��
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

//д���һ֡����600�����Pkg
void CSttReplayTest::WriteLastShareData(BYTE *pShareBuf,int &nWritePos)
{
	if (m_nProcessWritePos == 0)
	{//ProcessBuf��������
		return;
	}

	//ÿ��д�����泤��
	int nWriteLen = sizeof(Drv_BlockPkg)*m_nModuleSelCount;

	//ÿ�ν���ProcessBuf�����Ǵ�ͷ��ʼ
	m_nProcessReadPos = 0;

	//������ݵ�ͨ������
	int nLastPoints = m_nProcessWritePos / m_nChSelCount;

	for (int m=0; m<m_nModuleSelCount; m++)
	{
		//���µ�nModuleIndexģ���֡ͷ��Ϣ
		int nModuleIndex = m_arrSortModuleSel[m];
		UpdateBlockPkgHead(&m_pBlockPkgs[m],nModuleIndex,nLastPoints*6);

		//��ʼ��ComtradeBuf������ʼλ��
		int nOffset = m_nProcessReadPos;

		//��ǰģ��ͨ����
		int nChs = m_nModuleChNum[nModuleIndex];

		for (int n=0; n<m; n++)
		{
			nOffset += m_nModuleChNum[m_arrSortModuleSel[n]];
		}

		for (int i=0; i<nLastPoints; i++)
		{
			nOffset += i*m_nChSelCount; 

			//��ԭʼ����ת��Ϊ��������
			for (int j=0; j<6; j++)
			{
				if (j<nChs)
				{
					//����ת����ʽ����
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

//�ж��¼��еݹ���ã���ComtradeBuf���ݵ�ShareBuf,����true��ʾAB�л���
bool CSttReplayTest::WriteShareDataFromComtradeBuf(CComtradeDataBuffer* pComtradeBuf,BYTE *pShareBuf,int &nShareWritePos,unsigned int nMaxBlockCnt)
{
	//ÿ�ν���ComtradeBuf���ݳ���
	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;

	//���������Ѿ���BlockCnt
	int nHasBlockCnt = nShareWritePos / sizeof(Drv_BlockPkg);
	//������������ҪComtradeBuf���ݳ���
	int nNeedData = (nMaxBlockCnt-nHasBlockCnt) / m_nModuleSelCount * nOnceProcessLen;
	int nCurrComtradeBufLeftLen = pComtradeBuf->GetDataLen();
	int nReadLen = 0;
	bool bRet = (nCurrComtradeBufLeftLen <= nNeedData);

	if (nNeedData <= nCurrComtradeBufLeftLen)
	{//��ǰComtradeBuf�㹻
		nReadLen = pComtradeBuf->ReadData(m_arrProcessBuf+m_nProcessWritePos,nNeedData);
		m_nProcessWritePos += nReadLen;

		WriteShareData(pShareBuf,nShareWritePos);

		//�����������Ч��־
		SetShareBufValid(pShareBuf,nShareWritePos/sizeof(Drv_BlockPkg));

		if(nNeedData == nCurrComtradeBufLeftLen)
		{
			m_nCurrPlayIndex++;
		}
	}
	else
	{//��ǰComtradeBuf����
		nReadLen = pComtradeBuf->ReadData(m_arrProcessBuf+m_nProcessWritePos,nCurrComtradeBufLeftLen);
		m_nProcessWritePos += nReadLen;

		WriteShareData(pShareBuf,nShareWritePos);

		m_nCurrPlayIndex++;
		pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
		if (!pComtradeBuf->CanRead())
		{
			//д�����600������
			WriteLastShareData(pShareBuf,nShareWritePos);

			//�����������Ч��־
			SetShareBufValid(pShareBuf,nShareWritePos/sizeof(Drv_BlockPkg));
		}
		else
		{
			WriteShareDataFromComtradeBuf(pComtradeBuf,pShareBuf,nShareWritePos,nMaxBlockCnt);
		}	
	}

	return bRet;
}

//��LoopBuf��ShareLoopBuf
void CSttReplayTest::WriteShareLoopData()
{
	CComtradeDataBuffer* pLoopBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(0);
	if (!pLoopBuf->CanRead())
	{
		return;
	}

	BYTE *pShareBuf = NULL;
	unsigned int nMaxBlockCnt = 0;

	//��ѯ�չ�������Ϣ
	if (!QueryShareLoopBufInfo(&pShareBuf,nMaxBlockCnt))
	{
		return;
	}

	//��ʼ��������
	int nShareWritePos = 0;
	m_nProcessWritePos = 0;
	m_nProcessReadPos = 0;

	//ÿ�ν���ComtradeBuf���ݳ���
	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;

	//������������ҪComtradeBuf���ݳ���
	int nNeedData = nMaxBlockCnt / m_nModuleSelCount * nOnceProcessLen;
	int nCurrComtradeBufLeftLen = pLoopBuf->GetDataLen();

	if (nCurrComtradeBufLeftLen > nNeedData)
	{//����
		return;
	}

	int nReadLen = pLoopBuf->ReadData(m_arrProcessBuf,nCurrComtradeBufLeftLen);
	m_nProcessWritePos += nReadLen;

	WriteShareData(pShareBuf,nShareWritePos);

	//�����������Ч��־
	SetShareBufValid(pShareBuf,nShareWritePos/sizeof(Drv_BlockPkg));
}

void CSttReplayTest::EventProcess()
{//�����¼�����
	CComtradeDataBuffer* pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
	if (!pComtradeBuf->CanRead())
	{
		return;
	}

	BYTE *pShareBuf = NULL;
	unsigned int nMaxBlockCnt = 0;

	//��ѯ�չ�������Ϣ
	if (!QueryEmptyShareABBufInfo(&pShareBuf,nMaxBlockCnt))
	{
		return;
	}

	//��ʼ��������
	int nShareWritePos = 0;
	m_nProcessWritePos = 0;
	m_nProcessReadPos = 0;

	if (WriteShareDataFromComtradeBuf(pComtradeBuf,pShareBuf,nShareWritePos,nMaxBlockCnt))
	{//AB���л�
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
{//�յ��ֶ���������
	m_bTrigger = TRUE;

	//֪ͨ�����ֶ�����
}

void CSttReplayTest::OnSendDataFinish(int nIndex,int nSendNum)
{//Comtrade���ݷ����������
	UINT nSendIndex = (UINT)nIndex & 0x7FFFFFFF;
	m_bSendFinish = nIndex & 0x80000000;
	m_nCurrReqIndex++;

	//�������߳����ݰ��Ƶ�ComtradeBuf��
	g_oSttComtradeRcvSocket.MoveToComtradeBuf(nSendIndex,nSendNum);

	CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);

	if (nSendIndex == 0)
	{//֮ǰ�������LoopBuf���ݣ�������ABuf����

		//��LoopBuf�����ݰ��Ƶ�����LoopBuf��
		WriteShareLoopData();

		pServerEngine->Comtrade_SendRequestData(1);
	}
	else if (nSendIndex == 1)
	{//֮ǰ�������ABuf����
		if (!m_bSendFinish)
		{//����δ���꣬��������BBuf����
			pServerEngine->Comtrade_SendRequestData(2);
		}
		else
		{//�����ѷ��꣬
			//֪ͨ������ʼ�ط�
		}
	}
	else if (nSendIndex == 2)
	{//֮ǰ��һ���������BBuf����
		//֪ͨ������ʼ�ط�
	}
}

#define REPLAY_FLAG_WRITE_FINISH        0x01
#define REPLAY_FLAG_TEST_FINISH			0x02
#define REPLAY_FLAG_TEST_TRIP           0x03

void CSttReplayTest::StartTest()
{	
	CSttTestBase::StartTest();
//    qDebug()<<__FUNCTION__<<__LINE__<<__FILE__;

	//������ѡ��ģ�鼯�����飬���ں���ƴ����
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

	//�յ���ʼ��������󣬸������ò�����������
	CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);

	if (IsLoop())
	{//��Ҫѭ������
		m_nCurrReqIndex = 0;
		pServerEngine->Comtrade_SendRequestData(0);
	}
	else
	{//��ѭ������
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


