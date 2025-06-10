#include "stdafx.h"
#include"SttReplayTest.h"
// #include<QtDebug>
#ifdef _PSX_IDE_QT_
#include <unistd.h>
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
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

	m_pOnceProcessBuf = NULL;
	m_pProcessBuf = NULL;

    Init();

	m_nPlayTotalBlockCnt = 0;
#ifdef _SttTestServer_For_Debug_
	m_pDriverBuf = new BYTE[sizeof(Drv_BlockPkg)*LT_REPLAY_MAX_A_PKG_CNT+10];
	memset(m_pDriverBuf,0,sizeof(Drv_BlockPkg)*LT_REPLAY_MAX_A_PKG_CNT+10);

	m_bReplayStarted = FALSE;
	m_pEventThread = NULL;
#endif
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
	if (m_pBlockPkgs != NULL)
	{
		free (m_pBlockPkgs);
	}
	if (m_pOnceProcessBuf != NULL)
	{
		delete m_pOnceProcessBuf;
		m_pOnceProcessBuf = NULL;
	}

#ifdef _SttTestServer_For_Debug_
	if (m_pDriverBuf != NULL)
	{
		delete m_pDriverBuf;
		m_pDriverBuf = NULL;
	}
#endif
}

void CSttReplayTest::AfterSetParameter()
{
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

bool CSttReplayTest::QueryEmptyDriveABBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt)
{//���������ӿڣ���ѯ�չ�������Ϣ����ʼλ�ú�������ݿ���
#ifdef _SttTestServer_For_Debug_
	*ppDriveBuf = m_pDriverBuf;
	nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
#else
    if(!CSttDriverOper::getLtReplayBufferAFlag())
    {
        *ppDriveBuf = (BYTE *)(m_pStructLtBuffer->bufferA);
        nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
    } else if (!CSttDriverOper::getLtReplayBufferBFlag())
    {
        *ppDriveBuf = (BYTE *)(m_pStructLtBuffer->bufferB);
        nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
    } else {
        *ppDriveBuf = NULL;
        return false;
    }
#endif
	return true;
}

//nBufType:0ΪLoopBuf,1ΪABuf,2ΪBBuf
bool CSttReplayTest::QueryDriveBufInfo(BYTE **ppDriveBuf,unsigned int &nMaxBlockCnt,int nBufType)
{//���������ӿڣ���ѯ����Loop������Ϣ����ʼλ�ú�������ݿ���
#ifdef _SttTestServer_For_Debug_
	*ppDriveBuf = m_pDriverBuf;
	nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
#else
    if (nBufType == 0)
    {
        *ppDriveBuf = (BYTE *)(m_pStructLtBuffer->bufferLoop);
        nMaxBlockCnt = LT_REPLAY_MAX_LOOP_PKG_CNT;
    }
    else if (nBufType == 1)
    {
        *ppDriveBuf = (BYTE *)(m_pStructLtBuffer->bufferA);
        nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
    }
    else if (nBufType == 2)
    {
        *ppDriveBuf = (BYTE *)(m_pStructLtBuffer->bufferB);
        nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
    }
#endif
	return true;
}

void CSttReplayTest::SetDriveBufValid(BYTE *pDriveBuf,unsigned int nBlockCnt)
{//���õ�ǰ��������Ч����������Чģ��������
#ifdef _SttTestServer_For_Debug_
#else
    if(pDriveBuf == (BYTE *)(m_pStructLtBuffer->bufferA))
    {
//        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("===========SetDriveBufValidA %d "), nBlockCnt);
        m_pStructLtBuffer->buffer_A_curr_block = nBlockCnt;
        CSttDriverOper::setLtReplayBufferAFlag();
    } else if (pDriveBuf == (BYTE *)(m_pStructLtBuffer->bufferB)){
 //       CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("===========SetDriveBufValidB %d"), nBlockCnt);
        m_pStructLtBuffer->buffer_B_curr_block = nBlockCnt;
        CSttDriverOper::setLtReplayBufferBFlag();
    } else if (pDriveBuf == (BYTE *)(m_pStructLtBuffer->bufferLoop))
    {
 //       CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("===========SetDriveBufValidLoop %d"), nBlockCnt);
        m_pStructLtBuffer->loop_cur_block = nBlockCnt;
        CSttDriverOper::setLtReplayBufferLoopFlag();
    }
#endif
	m_nPlayTotalBlockCnt += nBlockCnt;
//    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SetDriveBufValid:%d[%d] *pDriveBuf = 0x%x"),nBlockCnt,m_nPlayTotalBlockCnt, pDriveBuf);
}

void CSttReplayTest::UpdateBlockPkgHead(Drv_BlockPkg *pBlockPkg,int nModulePos,long nLen)
{//������
	pBlockPkg->num = 0;
    pBlockPkg->module = (1<<nModulePos)<<16;
    pBlockPkg->title = 0x05640564;
    pBlockPkg->length = nLen + 1;
    pBlockPkg->cmd = 0x4002;
}

//����ProcessBuf���ݣ�ƴ��Pkgд��ShareBuf�У�ÿ��д����ΪnWriteLen
// void CSttReplayTest::OnceWriteProcessDataToDrive(BYTE *pDriveBuf,int &nWritePos,int nPointNum)
// {
// 	//ÿ��д�����泤��
// 	int nWriteLen = sizeof(Drv_BlockPkg)*m_nModuleSelCount;
// 
// 	//����0
// 	memset(m_pBlockPkgs,0,nWriteLen);
// 
// 	long nCurrModuleIndex = 0;
// 	Drv_BlockPkg *pDrv_BlockPkg = NULL;
// 
// 	for (int m=0; m<m_nModuleCount; m++)
// 	{
// 		if (m_oModule[m].m_nSel == 0)
// 		{
// 			continue;
// 		}
// 
// 		pDrv_BlockPkg = &m_pBlockPkgs[nCurrModuleIndex];
// 		nCurrModuleIndex++;
// 
// 		//���µ�nModuleIndexģ���֡ͷ��Ϣ
// 		int nModulePos = m_oModule[m].m_nIndex;
// 		UpdateBlockPkgHead(pDrv_BlockPkg,nModulePos,nPointNum*6);
// 
// 		//��ʼ��ComtradeBuf������ʼλ��
// 		int nOffset = m_nProcessReadPos;
// 
// 		//��ǰģ��ͨ����
// 		int nChs = m_oModule[m].m_nChUseCount;
// 
// 		for (int n=0; n<m; n++)
// 		{
// 			if (m_oModule[n].m_nSel == 0)
// 			{
// 				continue;
// 			}
// 			nOffset += m_oModule[n].m_nChUseCount;
// 		}
// 
// 		for (int i=0; i<nPointNum; i++)
// 		{
// 			int nOffset1 = nOffset + i*m_nChSelCount; 
// 			long nPointIndex = 6 * i;
// 
// 			//��ԭʼ����ת��Ϊ��������
// 			for (int j=0; j<6; j++)
// 			{
// 				if (j<nChs)
// 				{
// 					int ChPos = GetModuleChPos(nModulePos,m_oModule[m].m_oChMap[j].m_strChID);
// 
// 					//����ת����ʽ���㣬ChPos�����Ŵ�1��ʼ����-1
// 					pDrv_BlockPkg->data[nPointIndex+ChPos] = CalReplayDataValue(nModulePos, m_oModule[m].m_oChMap[j].m_strChID, m_pProcessBuf[nOffset1+j]);
// 				}
// 			}
// 		}
// 	}
// 
// 	memcpy(pDriveBuf+nWritePos,m_pBlockPkgs,nWriteLen);
// 	nWritePos += nWriteLen;
// }

void CSttReplayTest::OnceWriteProcessDataToDrive1(BYTE *pDriveBuf,int &nWritePos,int nPointNum)
{//nPointNumĬ��Ϊ300
	//ÿ��д�����泤��
	int nWriteLen = sizeof(Drv_BlockPkg)*m_nModuleSelCount;
	double fInsertVal = 0;
	int nOffset1 = 0; 
	long nPointIndex = 0;
	long nPointIndex2 = 0;

	//����0
	memset(m_pBlockPkgs,0,nWriteLen);

	long nCurrModuleIndex = 0;
	Drv_BlockPkg *pDrv_BlockPkg = NULL;
#ifndef _SttTestServer_For_Debug_
    drv_LtReplayCoefItem *pCoefItem = NULL;
#endif
	for (int m=0; m<m_nModuleCount; m++)
	{
		if (m_oModule[m].m_nSel == 0)
		{
			continue;
		}

		pDrv_BlockPkg = &m_pBlockPkgs[nCurrModuleIndex];
		nCurrModuleIndex++;

		//���µ�nModuleIndexģ���֡ͷ��Ϣ
		int nModulePos = m_oModule[m].m_nIndex;
		UpdateBlockPkgHead(pDrv_BlockPkg,nModulePos,2*nPointNum*6);

		//��ʼ��ComtradeBuf������ʼλ��
		int nOffset = 0;

		//��ǰģ��ͨ����
		int nChs = m_oModule[m].m_nChUseCount;

		for (int n=0; n<m; n++)
		{
			if (m_oModule[n].m_nSel == 0)
			{
				continue;
			}
			nOffset += m_oModule[n].m_nChUseCount;
		}

#ifdef _SttTestServer_For_Debug_
		for (int i=0; i<nPointNum; i++)
		{
			nOffset1 = nOffset + i*m_nChSelCount; 
			nPointIndex = 2 * 6 * i;
			nPointIndex2 = nPointIndex-6;

			//��ԭʼ����ת��Ϊ��������
			for (int j=0; j<6; j++)
			{
				if (j<nChs)
				{
					int ChPos = GetModuleChPos(nModulePos,m_oModule[m].m_oChMap[j].m_strChID);

					//����ת����ʽ���㣬ChPos�����Ŵ�1��ʼ����-1

					if (i > 0)
					{
						fInsertVal = (m_pProcessBuf[nOffset1+j] + m_pProcessBuf[nOffset1+j - m_nChSelCount]) * 0.5;
						pDrv_BlockPkg->data[nPointIndex2+ChPos] = CalReplayDataValue(nModulePos, m_oModule[m].m_oChMap[j].m_strChID, fInsertVal);
						pDrv_BlockPkg->data[nPointIndex+ChPos] = CalReplayDataValue(nModulePos, m_oModule[m].m_oChMap[j].m_strChID, m_pProcessBuf[nOffset1+j]);
					}
					else if (i == 0)
					{
						pDrv_BlockPkg->data[ChPos] = CalReplayDataValue(nModulePos, m_oModule[m].m_oChMap[j].m_strChID, m_pProcessBuf[nOffset1+j]);
					}
				}
			}
		}

		//�������һ����
		nOffset1 = nOffset + (nPointNum-1)*m_nChSelCount; 
		nPointIndex = 2 * 6 * (nPointNum-1) + 6;
		for (int j=0; j<6; j++)
		{
			if (j<nChs)
			{
				int ChPos = GetModuleChPos(nModulePos,m_oModule[m].m_oChMap[j].m_strChID);

				fInsertVal = (m_pProcessBuf[nOffset1+j] + m_arrLastPoint[nOffset+j]) * 0.5;
				pDrv_BlockPkg->data[nPointIndex+ChPos] = CalReplayDataValue(nModulePos, m_oModule[m].m_oChMap[j].m_strChID, fInsertVal);
			}

		}

#else
		for (int i=0; i<nPointNum; i++)
		{
			nOffset1 = nOffset + i*m_nChSelCount; 
			nPointIndex = 2 * 6 * i;
			nPointIndex2 = nPointIndex-6;

			//��ԭʼ����ת��Ϊ��������
			for (int j=0; j<6; j++)
			{
                pCoefItem = &m_ReplayConf.Item[nModulePos][j];
				if (j<nChs)
				{
					//����ת����ʽ���㣬ChPos�����Ŵ�1��ʼ����-1

					if (i > 0)
					{
						fInsertVal = (m_pProcessBuf[nOffset1+j] + m_pProcessBuf[nOffset1+j - m_nChSelCount]) * 0.5;
                        pDrv_BlockPkg->data[nPointIndex2 + pCoefItem->nCh] \
                                = 2147483648/pCoefItem->fMaxValue*(fInsertVal * pCoefItem->fCoef + pCoefItem->fZero)*pCoefItem->fReverse;
                        pDrv_BlockPkg->data[nPointIndex + pCoefItem->nCh] \
                                = 2147483648/pCoefItem->fMaxValue*(m_pProcessBuf[nOffset1 + j] * pCoefItem->fCoef + pCoefItem->fZero)*pCoefItem->fReverse;
                    }
					else if (i == 0)
                    {
                        pDrv_BlockPkg->data[nPointIndex + pCoefItem->nCh] \
                                = 2147483648/pCoefItem->fMaxValue*(m_pProcessBuf[nOffset1 + j] * pCoefItem->fCoef + pCoefItem->fZero)*pCoefItem->fReverse;
                    }
                }
			}
		}

		//�������һ����
		nOffset1 = nOffset + (nPointNum-1)*m_nChSelCount; 
		nPointIndex = 2 * 6 * (nPointNum-1) + 6;
		for (int j=0; j<6; j++)
		{
            pCoefItem = &m_ReplayConf.Item[nModulePos][j];
			if (j<nChs)
            {
				fInsertVal = (m_pProcessBuf[nOffset1+j] + m_arrLastPoint[nOffset+j]) * 0.5;
                pDrv_BlockPkg->data[nPointIndex + pCoefItem->nCh] \
                        = 2147483648/pCoefItem->fMaxValue*(fInsertVal * pCoefItem->fCoef + pCoefItem->fZero)*pCoefItem->fReverse;
            }
		}
#endif
	}

#ifdef _Stt_Cmtrd_Save_File_	
	CString strTemp;
	for (int i=0; i<COMTRADE_REPLAY_PKG_POINTS; i++)
	{
		strTemp.AppendFormat(_T("%.3f\r\n"),m_pBlockPkgs[0].data[6*i]*0.001);
	}
	m_oCmtrdSaveFile.Write(strTemp,strTemp.GetLength());
#endif

	memcpy(pDriveBuf+nWritePos,m_pBlockPkgs,nWriteLen);
	nWritePos += nWriteLen;
}

//����ProcessBuf���ݣ�ƴ��Pkgд��ShareBuf�У�ÿ��д����ΪnWriteLen
// void CSttReplayTest::WriteProcessDataToDrive(BYTE *pDriveBuf,int &nWritePos)
// {
// 	//ÿ�ν���ProcessBuf�����Ǵ�ͷ��ʼ
// 	m_nProcessReadPos = 0;
// 
// 	//ÿ�ν���ComtradeBuf���ݳ���
// 	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;
// 
// 
// 	while(m_nProcessWritePos - m_nProcessReadPos >= nOnceProcessLen)
// 	{
// 		OnceWriteProcessDataToDrive(pDriveBuf,nWritePos,COMTRADE_REPLAY_PKG_POINTS);
// 		m_nProcessReadPos += nOnceProcessLen;
// 	}
// 
// 	//δ����������ݰ��Ƶ���ͷλ��
// 	if (m_nProcessWritePos != m_nProcessReadPos)
// 	{
// 		m_nProcessWritePos = m_nProcessWritePos-m_nProcessReadPos;
// 		memcpy(m_pProcessBuf,m_pProcessBuf+m_nProcessReadPos,m_nProcessWritePos*sizeof(float));
// 	}
// 	else
// 	{
// 		m_nProcessWritePos = 0;
// 	}
// 	m_nProcessReadPos = 0;
// }

//д���һ֡����600�����Pkg
// void CSttReplayTest::WriteLastProcessDataToDrive(BYTE *pDriveBuf,int &nWritePos)
// {
// 	if (m_nProcessWritePos == 0)
// 	{//ProcessBuf��������
// 		return;
// 	}
// 
// 	//ÿ�ν���ProcessBuf�����Ǵ�ͷ��ʼ
// 	m_nProcessReadPos = 0;
// 	//������ݵ�ͨ������
// 	int nLastPoints = m_nProcessWritePos / m_nChSelCount;
// 
// 	OnceWriteProcessDataToDrive(pDriveBuf,nWritePos,nLastPoints);
// 
// 	m_nProcessWritePos = 0;
// 	m_nProcessReadPos = 0;
// }

bool CSttReplayTest::WriteComtradeDataToDrive1(CComtradeDataBuffer* pComtradeBuf,BYTE *pDriveBuf,int &nDriveWritePos,unsigned int nMaxBlockCnt,int nPreComtradeLeftLen)
{
	//ÿ�ν���ComtradeBuf���ݳ���
	int nReplayPoints = COMTRADE_REPLAY_PKG_POINTS / 2;
	int nLastPointSize = m_nChSelCount*sizeof(float);
	int nOnceProcessLen = m_nChSelCount * nReplayPoints;
	//���������Ѿ���BlockCnt
	int nHasBlockCnt = nDriveWritePos / sizeof(Drv_BlockPkg);
	int nNeedBlockCnt = nMaxBlockCnt / m_nModuleSelCount * m_nModuleSelCount - nHasBlockCnt;
	int nCurrComtradeBufLeftLen = 0;
	long nReadLen = 0;
	bool bABChanged = false;

	if (nPreComtradeLeftLen > 0)
	{
		nReadLen = pComtradeBuf->ReadData(m_pOnceProcessBuf+nPreComtradeLeftLen,nOnceProcessLen-nPreComtradeLeftLen);

		int nPoints = (nPreComtradeLeftLen+nReadLen) / m_nChSelCount;
		m_pProcessBuf = m_pOnceProcessBuf;

		//�������ڲ�ֵ��m_arrLastPoint
		if (nReadLen < nOnceProcessLen-nPreComtradeLeftLen)
		{//���һ����ʱ��������������һ������ͬ
			memcpy(m_arrLastPoint,m_pProcessBuf+nPreComtradeLeftLen+nReadLen-m_nChSelCount,nLastPointSize);
		}
		else
		{
			if (pComtradeBuf->GetDataLen() > 0)
			{
				memcpy(m_arrLastPoint,pComtradeBuf->GetCurDataBuf(),nLastPointSize);
			}
			else
			{//�鿴��һ��ComtradeBuf,
				CComtradeDataBuffer* pComtradeBuf1 = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex+1);
				if (pComtradeBuf1->CanRead())
				{
					memcpy(m_arrLastPoint,pComtradeBuf1->GetCurDataBuf(),nLastPointSize);
				}
				else
				{//���һ����ʱ��������������һ������ͬ
					memcpy(m_arrLastPoint,m_pProcessBuf+nPreComtradeLeftLen+nReadLen-m_nChSelCount,nLastPointSize);
				}
			}
		}

		OnceWriteProcessDataToDrive1(pDriveBuf,nDriveWritePos,nPoints);
		nNeedBlockCnt -= m_nModuleSelCount;

		if (nReadLen < nOnceProcessLen-nPreComtradeLeftLen)
		{//���һ֡����
			bABChanged = true;
			m_nCurrPlayIndex++;
			//�����������Ч��־
			SetDriveBufValid(pDriveBuf,nDriveWritePos/sizeof(Drv_BlockPkg));

            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WriteLastProcessDataToDrive1��BlockCnt[%d][%d]"),nDriveWritePos/sizeof(Drv_BlockPkg),m_nPlayTotalBlockCnt);

			return bABChanged;
		}
	}

	while(nNeedBlockCnt > 0)
	{
		nCurrComtradeBufLeftLen = pComtradeBuf->GetDataLen();
		if (nCurrComtradeBufLeftLen < nOnceProcessLen)
		{
			break;
		}

		m_pProcessBuf = pComtradeBuf->GetCurDataBuf();

		//�������ڲ�ֵ��m_arrLastPoint
		if (nCurrComtradeBufLeftLen > nOnceProcessLen)
		{
			memcpy(m_arrLastPoint,m_pProcessBuf + nOnceProcessLen,nLastPointSize);
		}
		else
		{//�鿴��һ��ComtradeBuf,
			CComtradeDataBuffer* pComtradeBuf1 = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex+1);
			if (pComtradeBuf1->CanRead())
			{
				memcpy(m_arrLastPoint,pComtradeBuf1->GetCurDataBuf(),nLastPointSize);
			}
			else
			{//���һ����ʱ��������������һ������ͬ
				memcpy(m_arrLastPoint,m_pProcessBuf + nOnceProcessLen-m_nChSelCount,nLastPointSize);
			}
		}

		OnceWriteProcessDataToDrive1(pDriveBuf,nDriveWritePos,COMTRADE_REPLAY_PKG_POINTS/2);
		//����ComtradeBuf��λ��
		pComtradeBuf->OffsetReadPos(nOnceProcessLen);
		nNeedBlockCnt -= m_nModuleSelCount;
	}

	if (nNeedBlockCnt == 0)
	{
		//�����������Ч��־
		SetDriveBufValid(pDriveBuf,nDriveWritePos/sizeof(Drv_BlockPkg));

		if (pComtradeBuf->GetDataLen() == 0)
		{
			m_nCurrPlayIndex++;
			bABChanged = true;
		}
	}
	else
	{//AB�л�
		bABChanged = true;
		nReadLen = 0;

		if (nCurrComtradeBufLeftLen > 0)
		{
			nReadLen = pComtradeBuf->ReadData(m_pOnceProcessBuf,nCurrComtradeBufLeftLen);
		}

		m_nCurrPlayIndex++;
		pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
		if (!pComtradeBuf->CanRead())
		{
			if (nReadLen > 0)
			{
				int nPoints = nReadLen / m_nChSelCount;
				m_pProcessBuf = m_pOnceProcessBuf;

				//�������ڲ�ֵ��m_arrLastPoint
				//���һ����ʱ��������������һ������ͬ
				memcpy(m_arrLastPoint,m_pProcessBuf+nReadLen-m_nChSelCount,nLastPointSize);

				OnceWriteProcessDataToDrive1(pDriveBuf,nDriveWritePos,nPoints);
				nNeedBlockCnt -= m_nModuleSelCount;
			}
  
			//�����������Ч��־
			SetDriveBufValid(pDriveBuf,nDriveWritePos/sizeof(Drv_BlockPkg));

			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WriteLastProcessDataToDrive2��BlockCnt[%d][%d]"),nDriveWritePos/sizeof(Drv_BlockPkg),m_nPlayTotalBlockCnt);

		}
		else
		{
			WriteComtradeDataToDrive1(pComtradeBuf,pDriveBuf,nDriveWritePos,nMaxBlockCnt,nReadLen);
		}
	}

	return bABChanged;
}

//�ж��¼��еݹ���ã���ComtradeBuf���ݵ�ShareBuf,����true��ʾAB�л���
// bool CSttReplayTest::WriteComtradeDataToDrive(CComtradeDataBuffer* pComtradeBuf,BYTE *pDriveBuf,int &nDriveWritePos,unsigned int nMaxBlockCnt)
// {
// 	//ÿ�ν���ComtradeBuf���ݳ���
// 	int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS;
// 
// 	//���������Ѿ���BlockCnt
// 	int nHasBlockCnt = nDriveWritePos / sizeof(Drv_BlockPkg);
// 	//������������ҪComtradeBuf���ݳ���
// 	int nNeedData = (nMaxBlockCnt-nHasBlockCnt) / m_nModuleSelCount * nOnceProcessLen - m_nProcessWritePos;
// 	int nCurrComtradeBufLeftLen = pComtradeBuf->GetDataLen();
// 	int nReadLen = 0;
// 	bool bRet = (nCurrComtradeBufLeftLen <= nNeedData);
// 
// 	if (nNeedData <= nCurrComtradeBufLeftLen)
// 	{//��ǰComtradeBuf�㹻
// 		nReadLen = pComtradeBuf->ReadData(m_pProcessBuf+m_nProcessWritePos,nNeedData);
// 		m_nProcessWritePos += nReadLen;
// 
// 		WriteProcessDataToDrive(pDriveBuf,nDriveWritePos);
// 
// 		//�����������Ч��־
// 		SetDriveBufValid(pDriveBuf,nDriveWritePos/sizeof(Drv_BlockPkg));
// 
// 		if(nNeedData == nCurrComtradeBufLeftLen)
// 		{
// 			m_nCurrPlayIndex++;
// 		}
// 	}
// 	else
// 	{//��ǰComtradeBuf����
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���ݲ�����m_nProcessWritePos[%d],nCurrComtradeBufLeftLen[%d]"),m_nProcessWritePos,nCurrComtradeBufLeftLen);
// 
// 		nReadLen = pComtradeBuf->ReadData(m_pProcessBuf+m_nProcessWritePos,nCurrComtradeBufLeftLen);
// 		m_nProcessWritePos += nReadLen;
// 
// 		WriteProcessDataToDrive(pDriveBuf,nDriveWritePos);
// 
// 		m_nCurrPlayIndex++;
// 		pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
// 		if (!pComtradeBuf->CanRead())
// 		{
// 			//д�����600������
// 			WriteLastProcessDataToDrive(pDriveBuf,nDriveWritePos);
// 
// 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WriteLastProcessDataToDrive��BlockCnt[%d]"),nDriveWritePos/sizeof(Drv_BlockPkg));
// 
// 			//�����������Ч��־
// 			SetDriveBufValid(pDriveBuf,nDriveWritePos/sizeof(Drv_BlockPkg));
// 		}
// 		else
// 		{
// 			WriteComtradeDataToDrive(pComtradeBuf,pDriveBuf,nDriveWritePos,nMaxBlockCnt);
// 		}	
// 	}
// 
// 	return bRet;
// }

//��LoopBuf��ShareLoopBuf
void CSttReplayTest::WriteLoopDataToDrive()
{
	CComtradeDataBuffer* pLoopBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(0);
	if (!pLoopBuf->CanRead())
	{
		return;
	}

	BYTE *pDriveBuf = NULL;
	unsigned int nMaxBlockCnt = 0;
	int nDriveWritePos = 0;

	//��ѯ�չ�������Ϣ
	if (!QueryDriveBufInfo(&pDriveBuf,nMaxBlockCnt,0))
	{
		return;
	}

	//ÿ�ν���ComtradeBuf���ݳ���
	int nReplayPoints = COMTRADE_REPLAY_PKG_POINTS / 2;
	int nLastPointSize = m_nChSelCount*sizeof(float);
	int nOnceProcessLen = m_nChSelCount * nReplayPoints;
	//���������Ѿ���BlockCnt
	int nNeedBlockCnt = nMaxBlockCnt / m_nModuleSelCount * m_nModuleSelCount;
	int nCurrComtradeBufLeftLen = 0;
	long nReadLen = 0;

	while(nNeedBlockCnt > 0)
	{
		nCurrComtradeBufLeftLen = pLoopBuf->GetDataLen();
		if (nCurrComtradeBufLeftLen < nOnceProcessLen)
		{
			break;
		}

		m_pProcessBuf = pLoopBuf->GetCurDataBuf();

		//�������ڲ�ֵ��m_arrLastPoint
		if (nCurrComtradeBufLeftLen > nOnceProcessLen)
		{
			memcpy(m_arrLastPoint,m_pProcessBuf + nOnceProcessLen,nLastPointSize);
		}
		else
		{//�������
			memcpy(m_arrLastPoint,m_pProcessBuf + nOnceProcessLen-m_nChSelCount,nLastPointSize);
		}

		OnceWriteProcessDataToDrive1(pDriveBuf,nDriveWritePos,nReplayPoints);
		//����ComtradeBuf��λ��
		pLoopBuf->OffsetReadPos(nOnceProcessLen);
		nNeedBlockCnt -= m_nModuleSelCount;
	}

	if ((nNeedBlockCnt > 0) && (nCurrComtradeBufLeftLen > 0))
	{
		nReadLen = pLoopBuf->ReadData(m_pOnceProcessBuf,nCurrComtradeBufLeftLen);

		int nPoints = nReadLen / m_nChSelCount;
		m_pProcessBuf = m_pOnceProcessBuf;

		//�������ڲ�ֵ��m_arrLastPoint
		//���һ����ʱ��������������һ������ͬ
		memcpy(m_arrLastPoint,m_pProcessBuf+nReadLen-m_nChSelCount,nLastPointSize);

		OnceWriteProcessDataToDrive1(pDriveBuf,nDriveWritePos,nPoints);
		nNeedBlockCnt -= m_nModuleSelCount;
	}

	//�����������Ч��־
	SetDriveBufValid(pDriveBuf,nDriveWritePos/sizeof(Drv_BlockPkg));
}

bool CSttReplayTest::WriteABDataToDrive()
{
	CComtradeDataBuffer* pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);
	if (!pComtradeBuf->CanRead())
	{
		return false;
	}

	BYTE *pDriveBuf = NULL;
	unsigned int nMaxBlockCnt = 0;

	//��ѯ�չ�������Ϣ
	if (!QueryEmptyDriveABBufInfo(&pDriveBuf,nMaxBlockCnt))
	{
		return false;
	}

	//��ʼ��������
	int nDriveWritePos = 0;

	if (WriteComtradeDataToDrive1(pComtradeBuf,pDriveBuf,nDriveWritePos,nMaxBlockCnt,0))
	{//AB���л�
		if(!m_bSendFinish)
		{
			CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
			ASSERT(pServerEngine != NULL);
			pServerEngine->Comtrade_SendRequestData(m_nCurrReqIndex);
		}
	}

	return true;
}

void CSttReplayTest::EventProcess()
{//�����¼�����
//    CLogPrint::g_pLogPrint->LogFormatString(XLOGLEVEL_INFOR, "Enter eventProcess");
	WriteABDataToDrive();
//    CLogPrint::g_pLogPrint->LogFormatString(XLOGLEVEL_INFOR, "Exit eventProcess");
}

void CSttReplayTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);

	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttReplayTest::Stop()
{	
//	m_Start=false;
    CSttTestBase::Stop();

#ifdef _SttTestServer_For_Debug_
	StopEventThread();
#endif

#ifdef _Stt_Cmtrd_Save_File_
	CloseCmtrdSaveFile();
#endif
}

void CSttReplayTest::Triger()
{//�յ��ֶ���������
	m_bTrigger = TRUE;
#ifndef _SttTestServer_For_Debug_
    CSttDriverOper::setStateTrigerManual();
#endif
	//֪ͨ�����ֶ�����
}

void CSttReplayTest::OnSendDataFinish(int nIndex,int nSendNum)
{//Comtrade���ݷ����������
	UINT nSendIndex = (UINT)nIndex & 0x7FFFFFFF;
	if (nSendIndex != 0)
	{
		m_bSendFinish = ((UINT)nIndex) >> 31;
	}
	
	m_nCurrReqIndex++;

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendDataFinish:nIndex=%d,nSendNum=%d,m_nCurrReqIndex=%d"),nSendIndex,nSendNum,m_nCurrReqIndex);

	//֪ͨ�����߳������ѷ������
	g_oSttComtradeRcvSocket.OnSendDataFinish(nSendIndex,nSendNum);
}

void CSttReplayTest::OnSendDataStart(int nIndex,int nSendNum)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendDataStart:nIndex=%d,nSendNum=%d"),nIndex,nSendNum);

	//֪ͨ�����߳������ѷ������
	g_oSttComtradeRcvSocket.OnSendDataStart(nIndex,nSendNum);
}

void CSttReplayTest::OnAfterMoveToComtradeBuf(int nIndex,int nDataLen)
{
	CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);

	if (nIndex == 0)
	{//֮ǰ�������LoopBuf���ݣ�������ABuf����

		//��LoopBuf�����ݰ��Ƶ�����LoopBuf��
		WriteLoopDataToDrive();

		pServerEngine->Comtrade_SendRequestData(1);
	}
	else if (nIndex == 1)
	{//֮ǰ�������ABuf����
		if (!m_bSendFinish)
		{//����δ���꣬��������BBuf����
			pServerEngine->Comtrade_SendRequestData(2);
		}
		else
		{//�����ѷ��꣬
            //֪ͨ������ʼ�ط�
			StartEventThread();
		}
	}
	else if (nIndex == 2)
	{//֮ǰ��һ���������BBuf����
        //֪ͨ������ʼ�ط�
		StartEventThread();
	}
}

#define REPLAY_FLAG_WRITE_FINISH        0x01
#define REPLAY_FLAG_TEST_FINISH			0x02
#define REPLAY_FLAG_TEST_TRIP           0x03

void CSttReplayTest::StartTest()
{	
    CSttTestBase::StartTest();

	//���³�ʼ��AB����
	CComtradeBufMngr::g_pComtradeBufMngr->ResetBuf();
	g_oSttComtradeRcvSocket.ResetRcvLen();
	m_nCurrReqIndex = 0;
	m_nCurrPlayIndex = 1;
	m_nPlayTotalBlockCnt = 0;

	m_nChSelCount = GetChSelCount();
	m_nModuleSelCount = GetModuleSelCount();
	if (m_nModuleCount == 0 || m_nModuleSelCount==0)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("error m_nModuleCount/m_nModuleSelCount == 0"));
		return;
	}
	if (m_pBlockPkgs != NULL)
	{
		free (m_pBlockPkgs);
	}

	m_pBlockPkgs = (Drv_BlockPkg*)malloc(sizeof(Drv_BlockPkg)*m_nModuleSelCount);

	if (m_pOnceProcessBuf != NULL)
	{
		delete m_pOnceProcessBuf;
	}
	m_pOnceProcessBuf = new float[m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS / 2 + 10];

#ifdef _Stt_Cmtrd_Save_File_

	CString strFile = g_strFtpRootFile + _T("sttComtrade.txt");
	OpenCmtrdSaveFile(strFile);

#endif

    TtmToDrv();
#ifndef _SttTestServer_For_Debug_
    CSttDevice::g_pSttDevice->SetTestPara(ReplayTestCfg, (char*)&m_oDrvLtReplayParam, sizeof(m_oDrvLtReplayParam));
    m_pStructLtBuffer = (drv_structLtBuffer *)CSttDriverOper::getMmapBuffer();
    memset(m_pStructLtBuffer, 0, sizeof(drv_structLtBuffer));
    m_pStructLtBuffer->offset_loop = sizeof(drv_structLtBuffer) - sizeof(Drv_BlockPkg)*(LT_REPLAY_MAX_LOOP_PKG_CNT + LT_REPLAY_MAX_A_PKG_CNT + LT_REPLAY_MAX_B_PKG_CNT);
    m_pStructLtBuffer->offset_bufferA = m_pStructLtBuffer->offset_loop + sizeof(Drv_BlockPkg)*LT_REPLAY_MAX_LOOP_PKG_CNT;
    m_pStructLtBuffer->offset_bufferB = m_pStructLtBuffer->offset_loop + sizeof(Drv_BlockPkg)*(LT_REPLAY_MAX_LOOP_PKG_CNT + LT_REPLAY_MAX_A_PKG_CNT);
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("bufferLoop = 0x%x"), m_pStructLtBuffer->bufferLoop);
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("bufferA = 0x%x"), m_pStructLtBuffer->bufferA);
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("bufferB = 0x%x"), m_pStructLtBuffer->bufferB);
    CSttDriverOper::IoCtrl(0x134, 0); // �����־
#endif

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
   tmt_to_drv(this,  &m_oDrvLtReplayParam, &m_ReplayConf);
#endif
}

void CSttReplayTest::StartEventThread()
{
	//�����ABuf
	if (WriteABDataToDrive())
	{
		//�����BBuf
		WriteABDataToDrive();
	}
#ifdef _SttTestServer_For_Debug_
	Sleep(1000);
	m_pEventThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttEventThread,(LPVOID)this,0,NULL);
#else
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("StartEventThread  ReplayTest"));
    CSttDevice::g_pSttDevice->SetTestStart(ReplayTest);
#endif
}
#ifdef _SttTestServer_For_Debug_
void CSttReplayTest::StopEventThread()
{
	m_bReplayStarted = FALSE;
}

UINT CSttReplayTest::SttEventThread(LPVOID pParam)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("===========SttEventThread enter"));
	CSttReplayTest *pReplayTest = (CSttReplayTest*)pParam;
	pReplayTest->m_bReplayStarted = TRUE;

	while(pReplayTest->m_bReplayStarted)
	{
		pReplayTest->EventProcess();
		Sleep(700);
	}

	pReplayTest->m_pEventThread = NULL;
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("===========SttEventThread exit"));
	return 0;
}

int CSttReplayTest::GetModuleChPos(int nModulePos,const char *pszChID)
{
	if (strcmp(pszChID,"Ua") == 0 || strcmp(pszChID,"Ia") == 0)
	{
		return 0;
	}
	else if (strcmp(pszChID,"Ub") == 0 || strcmp(pszChID,"Ib") == 0)
	{
		return 1;
	}
	else if (strcmp(pszChID,"Uc") == 0 || strcmp(pszChID,"Ic") == 0)
	{
		return 2;
	}
	else if (strcmp(pszChID,"Uz") == 0 || strcmp(pszChID,"I0") == 0)
	{
		return 3;
	}

	return 0;
}

long CSttReplayTest::CalReplayDataValue(int nModulePos,const char *pszChID, float fRawVal)
{//ԭʼֵ����Ϊ��������
	return (long)(fRawVal * 1000);
}
#endif
