#include "stdafx.h"
#include"SttReplayTest.h"

#ifdef _PSX_IDE_QT_
    #include <unistd.h>
    #include "../../../../SttDevice/SttDeviceBase.h"
	#include<QtDebug>
#endif

CString CSttReplayTest::m_strMacroName = "故障重放测试";
CString CSttReplayTest::m_strMacroID = STT_MACRO_ID_ReplayTest;
CString CSttReplayTest::m_strFilePostFix = "replaytst";
CString CSttReplayTest::m_strMacroVer = "1.0";

CSttReplayTest::CSttReplayTest() : CSttTestBase()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    m_nCurrReqIndex = 0;	//当前需要请求ABBuf Index
    m_nCurrPlayIndex = 1;	//播放Index
    m_nChSelCount = 0;
    m_nModuleSelCount = 0;
#ifndef _SttTestServer_For_Debug_
    m_pOnceProcessBuf = CSttDeviceBase::g_pSttDeviceBase->m_pReplayChsBuf;
#endif
    m_pProcessBuf = NULL;
#ifdef _SttTestServer_For_Debug_
    m_pDriverBuf = new BYTE[sizeof(Drv_BlockPkg)*LT_REPLAY_MAX_A_PKG_CNT + 10];
    memset(m_pDriverBuf, 0, sizeof(Drv_BlockPkg)*LT_REPLAY_MAX_A_PKG_CNT + 10);
    m_bReplayStarted = FALSE;
    m_pEventThread = NULL;
#endif
    m_pLtReplayBuffer = (Drv_LtReplayBuffer *)stt_test_get_drvparas_buff();
}

void CSttReplayTest::Init()
{
    tmt_ReplayParas::init();
    CSttTestBase::Init();
    m_oReplayResult.init();
	bTestFinishNormal = TRUE;
}

long CSttReplayTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return 0;
}

CSttReplayTest::~CSttReplayTest(void)
{
#ifdef _SttTestServer_For_Debug_

    if(m_pDriverBuf != NULL)
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

//nBufType:0为LoopBuf,1为ABuf、BBuf
bool CSttReplayTest::QueryDriveBufInfo(BYTE **ppDriveBuf, unsigned int &nMaxBlockCnt, int nBufType)
{
    //调用驱动接口，查询共享Loop缓存信息：起始位置和最大数据块数
#ifdef _SttTestServer_For_Debug_
    *ppDriveBuf = m_pDriverBuf;
    nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
#else

    if(nBufType == 0)
    {
        *ppDriveBuf = (BYTE *)(m_pLtReplayBuffer->bufferLoop);
        nMaxBlockCnt = LT_REPLAY_MAX_LOOP_PKG_CNT;
    }
    else
    {
		int nFlag = CSttDeviceBase::g_pSttDeviceBase->getLtReplayBufferFlag();
		if(!CSttDeviceBase::g_pSttDeviceBase->CheckBufferA(nFlag))
        {
            *ppDriveBuf = (BYTE *)(m_pLtReplayBuffer->bufferA);
            nMaxBlockCnt = LT_REPLAY_MAX_A_PKG_CNT;
        }
		else if(!CSttDeviceBase::g_pSttDeviceBase->CheckBufferB(nFlag))
        {
            *ppDriveBuf = (BYTE *)(m_pLtReplayBuffer->bufferB);
            nMaxBlockCnt = LT_REPLAY_MAX_B_PKG_CNT;
        }
        else
        {
            *ppDriveBuf = NULL;
            return false;
        }
    }

#endif
    return true;
}

void CSttReplayTest::SetDriveBufValid(BYTE *pDriveBuf, unsigned int nBlockCnt)
{
    //设置当前共享缓存有效，并设置有效模块数长度
#ifdef _SttTestServer_For_Debug_
#else

    if(pDriveBuf == (BYTE *)(m_pLtReplayBuffer->bufferA))
    {
		// CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("===========SetDriveBufValidA %d "), nBlockCnt);
        CSttDeviceBase::g_pSttDeviceBase->setLtReplayBufferABLoop(nBlockCnt * sizeof(Drv_BlockPkg), (char *)pDriveBuf, 1);
    }
    else if(pDriveBuf == (BYTE *)(m_pLtReplayBuffer->bufferB))
    {
		// CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("===========SetDriveBufValidB %d"), nBlockCnt);
        CSttDeviceBase::g_pSttDeviceBase->setLtReplayBufferABLoop(nBlockCnt * sizeof(Drv_BlockPkg), (char *)pDriveBuf, 2);
    }
    else if(pDriveBuf == (BYTE *)(m_pLtReplayBuffer->bufferLoop))
    {
		// CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("===========SetDriveBufValidLoop %d"), nBlockCnt);
        CSttDeviceBase::g_pSttDeviceBase->setLtReplayBufferABLoop(nBlockCnt * sizeof(Drv_BlockPkg), (char *)pDriveBuf, 0);
    }

#endif
}

void ProBinaryModuleReplay(SwitchInfo *pSwitchInfo, unsigned int *pReplayData, long *pDrvData)
{
	long nBoIndex = 0;
	unsigned int nBoBit;
	for(int j = 0; j < 64; j++)
	{
		if(pSwitchInfo->m_bBoPos[j] == FALSE)
		{
			continue;
		}

		nBoBit = pReplayData[nBoIndex] > 0 ? 0 : 1;

		if(j < 32)
		{
			*pDrvData |= nBoBit << j;
		}
		else
		{
			*(pDrvData + 1) |= nBoBit << (j - 32);
		}

		nBoIndex++;
	}
}

void Trans_8ChanTo5Code(unsigned int *nCode, long *nData)
{
	unsigned int nTemp[8];
	memcpy(nTemp,nData,32);

	nCode[0] = nTemp[0];
	nCode[0] |= nTemp[1]>>20;
	nCode[1] = nTemp[1]<<12;
	nCode[1] = nCode[1]&0xFF000000;
	nCode[1] |= nTemp[2]>>8;
	nCode[1] |= nTemp[3]>>28;
	nCode[2] = nTemp[3]<<4;
	nCode[2] = nCode[2]&0xFFFF0000;
	nCode[2] |= nTemp[4]>>16;
	nCode[3] = nTemp[4]<<16;
	nCode[3] = nCode[3]&0xF0000000;
	nCode[3] |= nTemp[5]>>4;
	nCode[3] |= nTemp[6]>>24;
	nCode[4] = nTemp[6]<<8;
	nCode[4] = nCode[4]&0xFFF00000;
	nCode[4] |= nTemp[7]>>12;
}

//解析ProcessBuf数据，拼成Pkg写到ShareBuf中，每次写长度为nWriteLen
void CSttReplayTest::OnceWriteProcessDataToDrive1(BYTE *pDriveBuf, int &nWritePos, int nPointNum)
{
#ifndef _SttTestServer_For_Debug_     //20220520 zhouhj  通道数量已修改,解决编译问题,暂时注释
    //nPointNum默认为300,通过插值产生600点
    //每次写共享缓存长度
    int nWriteLen = sizeof(Drv_BlockPkg) * m_nModuleSelCount;
	float fInsertVal = 0;
    int nOffset1 = 0;
    long nPointIndex = 0;
    long nPointIndex2 = 0;
#ifndef _SttTestServer_For_Debug_
    Drv_ReplayCoefItems *pCoefItems = NULL;
    //先清0
    Drv_BlockPkg *pDrv_BlockPkgs = CSttDeviceBase::g_pSttDeviceBase->m_pReplayModulesBuf;
    memset(pDrv_BlockPkgs, 0, nWriteLen);
#endif
    long nDrvModuleIndex = 0;
    Drv_BlockPkg *pDrv_BlockPkg = NULL;

    for(int nModuleIndex = 0; nModuleIndex < m_nModuleCount; nModuleIndex++)
    {
        if(m_oModule[nModuleIndex].m_nSel == 0)
        {
            continue;
        }

        pDrv_BlockPkg = &pDrv_BlockPkgs[nDrvModuleIndex++];
        //更新第nModuleIndex模块的帧头信息
        int nModulePos = m_oModule[nModuleIndex].m_nIndex - 1;
		//初始化ComtradeBuf解析起始位置
		int nOffset = 0;

		for(int n = 0; n < nModuleIndex; n++)
		{
			if(m_oModule[n].m_nSel)
			{
				if(m_oModule[n].m_nModuleType == REPLAY_MODULE_TYPE_BINARY)
				{
					nOffset += 2;//开关量固定占用2个通道64bits
				}
				else
				{
					for(int j = 0; j < m_oModule[n].m_nChUseCount; j++)
					{
						if(m_oModule[n].m_oChMap[j].m_nChSel)
						{
							nOffset++;
						}
					}
				}
			}
		}

		if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_BINARY)
		{
			//开关量
			SwitchInfo *pSwitchInfo = NULL;
			SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
			for(int j = 0; j < oSwitchModules.m_nModulesCount; j++)
			{
				if(oSwitchModules.oSWITCHINFO[j].m_nModulePos == m_oModule[nModuleIndex].m_nIndex)
				{
					pSwitchInfo = &oSwitchModules.oSWITCHINFO[j];
					break;
				}
			}

			if(pSwitchInfo == NULL)
			{
				continue;
			}

			int nReplayDataLen = 2;//FPGA播放通道长度
			pDrv_BlockPkg->module = (1 << (nModulePos)) << 16;
			pDrv_BlockPkg->title = 0x05640564;
			pDrv_BlockPkg->length = 2 * nPointNum * nReplayDataLen + 1;
			pDrv_BlockPkg->cmd = 0x4002;
			unsigned int nBOValue = 0;
			unsigned int nBOState[64];

			for(int i = 0; i < nPointNum; i++)
			{
				nOffset1 = i * m_nChSelCount + nOffset;
				nPointIndex = 2 * nReplayDataLen * i;

				if(i == 0)
				{
					memcpy(&nBOValue,&m_pProcessBuf[nOffset1],4);//K32~k1
					for(int j = 0; j < 32; j++)
					{
						nBOState[j] = (nBOValue>>j)&0x1;
					}
					memcpy(&nBOValue,&m_pProcessBuf[nOffset1 + 1],4);//K64~k33
					for(int j = 0; j < 32; j++)
					{
						nBOState[j+32] = (nBOValue>>j)&0x1;
					}

					ProBinaryModuleReplay(pSwitchInfo,nBOState,&pDrv_BlockPkg->data[nPointIndex]);
				}
				else
				{
					memcpy(&nBOValue,&m_pProcessBuf[nOffset1],4);//K32~k1
					for(int j = 0; j < 32; j++)
					{
						nBOState[j] = (nBOValue>>j)&0x1;
					}
					memcpy(&nBOValue,&m_pProcessBuf[nOffset1 + 1],4);//K64~k33
					for(int j = 0; j < 32; j++)
					{
						nBOState[j+32] = (nBOValue>>j)&0x1;
					}

					ProBinaryModuleReplay(pSwitchInfo,nBOState,&pDrv_BlockPkg->data[nPointIndex]);
					nPointIndex2 = nPointIndex - nReplayDataLen;
					pDrv_BlockPkg->data[nPointIndex2] = pDrv_BlockPkg->data[nPointIndex];
					pDrv_BlockPkg->data[nPointIndex2 + 1] = pDrv_BlockPkg->data[nPointIndex + 1];
				}
			}

			//插入最后一个点
			nOffset1 = nOffset + (nPointNum - 1) * m_nChSelCount;
			nPointIndex = 2 * nReplayDataLen * (nPointNum - 1) + nReplayDataLen;
			memcpy(&nBOValue,&m_pProcessBuf[nOffset1],4);//K32~k1
			for(int j = 0; j < 32; j++)
			{
				nBOState[j] = (nBOValue>>j)&0x1;
			}
			memcpy(&nBOValue,&m_pProcessBuf[nOffset1 + 1],4);//K64~k33
			for(int j = 0; j < 32; j++)
			{
				nBOState[j+32] = (nBOValue>>j)&0x1;
			}
			ProBinaryModuleReplay(pSwitchInfo,nBOState,&pDrv_BlockPkg->data[nPointIndex]);
		}
		else
		{
			//电气量
			pCoefItems = &m_oReplayConf.Items[nModulePos];
			int nReplayDataLen = 6;//FPGA播放通道长度
			pDrv_BlockPkg->module = (1 << (nModulePos)) << 16;
			pDrv_BlockPkg->title = 0x05640564;
			pDrv_BlockPkg->cmd = 0x4002;

			if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
					|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
			{
			if(pCoefItems->nCode == 16)
			{
				nReplayDataLen = pCoefItems->nChCnt / 2;
			}
				else if(pCoefItems->nCode == 32)
				{
					nReplayDataLen = pCoefItems->nChCnt;
				}
				else if(pCoefItems->nCode == 20)
				{
					nReplayDataLen = 5;//ADMU，5*32 = 20*8
				}
			pDrv_BlockPkg->length = 2 * nPointNum * nReplayDataLen + 1;
			}
			else
			{
				nReplayDataLen = pCoefItems->nChCnt;
				pDrv_BlockPkg->length = nPointNum * nReplayDataLen + 1;
			}

	#ifdef _SttTestServer_For_Debug_

			for(int i = 0; i < nPointNum; i++)
			{
				nOffset1 = nOffset + i * m_nChSelCount;
				nPointIndex = 2 * 6 * i;
				nPointIndex2 = nPointIndex - 6;

				//由原始数据转换为播放数据
				for(int j = 0; j < 6; j++)
				{
					if(j < nChs)
					{
						int ChPos = GetModuleChPos(nModulePos, m_oModule[nModuleIndex].m_oChMap[j].m_strChID);

						//需由转换公式计算，ChPos如果编号从1开始则需-1

						if(i > 0)
						{
							fInsertVal = (m_pProcessBuf[nOffset1 + j] + m_pProcessBuf[nOffset1 + j - m_nChSelCount]) * 0.5;
							pDrv_BlockPkg->data[nPointIndex2 + ChPos] = CalReplayDataValue(nModulePos, m_oModule[nModuleIndex].m_oChMap[j].m_strChID, fInsertVal);
							pDrv_BlockPkg->data[nPointIndex + ChPos] = CalReplayDataValue(nModulePos, m_oModule[nModuleIndex].m_oChMap[j].m_strChID, m_pProcessBuf[nOffset1 + j]);
						}
						else if(i == 0)
						{
							pDrv_BlockPkg->data[ChPos] = CalReplayDataValue(nModulePos, m_oModule[nModuleIndex].m_oChMap[j].m_strChID, m_pProcessBuf[nOffset1 + j]);
						}
					}
				}
			}

			//插入最后一个点
			nOffset1 = nOffset + (nPointNum - 1) * m_nChSelCount;
			nPointIndex = 2 * 6 * (nPointNum - 1) + 6;

			for(int j = 0; j < 6; j++)
			{
				if(j < nChs)
				{
					int ChPos = GetModuleChPos(nModulePos, m_oModule[nModuleIndex].m_oChMap[j].m_strChID);
					fInsertVal = (m_pProcessBuf[nOffset1 + j] + m_arrLastPoint[nOffset + j]) * 0.5;
					pDrv_BlockPkg->data[nPointIndex + ChPos] = CalReplayDataValue(nModulePos, m_oModule[nModuleIndex].m_oChMap[j].m_strChID, fInsertVal);
				}
			}

	#else
			float fvalue = 0.0;
			int nCode = 0x7fffffff;
			long nChReplayData1[48], nChReplayData2[48];

			if(pCoefItems->nCode == 16)
			{
				nCode = 0x7fff;
			}

			for(int i = 0; i < nPointNum; i++)
			{
				nOffset1 = i * m_nChSelCount + nOffset;
				memset(nChReplayData1, 0, 48 * sizeof(long));
				memset(nChReplayData2, 0, 48 * sizeof(long));//插值点
				int nChanIdx = 0;

				//由原始数据转换为播放数据
				for(int j = 0; j < m_oModule[nModuleIndex].m_nChUseCount; j++)
				{
					if(m_oModule[nModuleIndex].m_oChMap[j].m_nChSel == 0)
					{
						continue;
					}

					if(i == 0)
					{
						fvalue = m_pProcessBuf[nOffset1 + nChanIdx];
						fvalue = fvalue * pCoefItems->Item[j].fTmtCoef; //变比
						fvalue = fvalue * pCoefItems->Item[j].fCoef + pCoefItems->Item[j].fZero;
						fvalue = fvalue / pCoefItems->Item[j].fMaxValue;
						fvalue = fvalue * pCoefItems->Item[j].fReverse;

						if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
								|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
						{
						if(fabs(fvalue) > 0.999999) //限制幅值
						{
							if(fvalue > 0)
							{
								fvalue = 0.999999;
							}
							else
							{
								fvalue = -0.999999;
							}
						}

						nChReplayData1[pCoefItems->Item[j].nCh] = nCode * fvalue;
					}
					else
					{
							if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_61850_92)
							{
								nChReplayData1[pCoefItems->Item[j].nCh] = fvalue;
							}
							else
							{
								long nValue = fvalue;
								//FT3
								int nFT3Offset = (4 - pCoefItems->Item[j].nSampleLen) * 8;
								switch(pCoefItems->Item[j].nSampleLen)
								{
								case 1:
									if(nValue > 0xFF)
									{
										nValue = 0xFF;
									}
									break;
								case 2:
									if(nValue > 0xFFFF)
									{
										nValue = 0xFFFF;
									}
									break;
								case 3:
									if(nValue > 0xFFFFFF)
						{
										nValue = 0xFFFFFF;
									}
									break;
						}

								nChReplayData1[pCoefItems->Item[j].nCh] = nValue << nFT3Offset;
							}
						}
					}
					else
					{
						if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
								|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
						{
							fInsertVal = (m_pProcessBuf[nOffset1 + nChanIdx] + m_pProcessBuf[nOffset1 + nChanIdx - m_nChSelCount]) * 0.5;
							fvalue = fInsertVal;
							fvalue = fvalue * pCoefItems->Item[j].fTmtCoef; //变比
						fvalue = fvalue * pCoefItems->Item[j].fCoef + pCoefItems->Item[j].fZero;
						fvalue = fvalue / pCoefItems->Item[j].fMaxValue;
							fvalue = fvalue * pCoefItems->Item[j].fReverse;

						if(fabs(fvalue) > 0.999999) //限制幅值
						{
							if(fvalue > 0)
							{
								fvalue = 0.999999;
							}
							else
							{
								fvalue = -0.999999;
							}
						}

						nChReplayData2[pCoefItems->Item[j].nCh] = nCode * fvalue;
						}

						fvalue = m_pProcessBuf[nOffset1 + nChanIdx];
						fvalue = fvalue * pCoefItems->Item[j].fTmtCoef; //变比
						fvalue = fvalue * pCoefItems->Item[j].fCoef + pCoefItems->Item[j].fZero;
						fvalue = fvalue / pCoefItems->Item[j].fMaxValue;
						fvalue = fvalue * pCoefItems->Item[j].fReverse;

						if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
								|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
						{
						if(fabs(fvalue) > 0.999999) //限制幅值
						{
							if(fvalue > 0)
							{
								fvalue = 0.999999;
							}
							else
							{
								fvalue = -0.999999;
							}
						}

						nChReplayData1[pCoefItems->Item[j].nCh] = nCode * fvalue;
					}
						else
						{
							if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_61850_92)
							{
								nChReplayData1[pCoefItems->Item[j].nCh] = fvalue;
							}
							else
							{
								long nValue = fvalue;
								//FT3
								int nFT3Offset = (4 - pCoefItems->Item[j].nSampleLen) * 8;
								switch(pCoefItems->Item[j].nSampleLen)
								{
								case 1:
									if(nValue > 0xFF)
									{
										nValue = 0xFF;
									}
									break;
								case 2:
									if(nValue > 0xFFFF)
									{
										nValue = 0xFFFF;
									}
									break;
								case 3:
									if(nValue > 0xFFFFFF)
									{
										nValue = 0xFFFFFF;
									}
									break;
								}

								nChReplayData1[pCoefItems->Item[j].nCh] = nValue << nFT3Offset;
							}
						}
					}

					nChanIdx++;
				}

				if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
						|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
				{
				nPointIndex = 2 * nReplayDataLen * i;
				nPointIndex2 = nPointIndex - nReplayDataLen;
				}
				else
				{
					nPointIndex = nReplayDataLen * i;
				}

				if(i == 0)
				{
					if(pCoefItems->nCode == 32)
					{
						//6路回放通道
						long nCount = pCoefItems->nChCnt;

						for(int j = 0; j < nCount; j++)
						{
							pDrv_BlockPkg->data[nPointIndex + j] = nChReplayData1[j];
						}
					}
					else if(pCoefItems->nCode == 16)
					{
						//12路、8路回放通道
						long nCount = pCoefItems->nChCnt / 2;
						long nTemp;

						for(int j = 0; j < nCount; j++)
						{
							nTemp = nChReplayData1[j * 2];

							if(nTemp < 0)
							{
								nTemp = nTemp * (-1);
								nTemp = nTemp << 16;
								nTemp = nTemp * (-1);
							}
							else
							{
								nTemp = nTemp << 16;
							}

							nTemp &= 0xffff0000;
							pDrv_BlockPkg->data[nPointIndex + j] |= nTemp;
							nTemp = nChReplayData1[j * 2 + 1];

							if(nTemp < 0)
							{
								nTemp = nTemp * (-1);
								nTemp = nTemp << 16;
								nTemp = nTemp * (-1);
								nTemp = nTemp >> 16;
							}

							nTemp &= 0xffff;
							pDrv_BlockPkg->data[nPointIndex + j] |= nTemp;
						}
					}
					else if(pCoefItems->nCode == 20)
					{
						unsigned int nData[5];
						Trans_8ChanTo5Code(nData,nChReplayData1);

						for(int j = 0;j < 5;j++)
						{
							pDrv_BlockPkg->data[nPointIndex + j] = nData[j];
						}

						// std::bitset<160> nbits;
						// //8路回放通道
						// unsigned int nBit;
						// long nCount = 0;

						// for(int j = 0; j < 8; j++)
						// {
						// 	for(int m = 0; m < 20; m++)
						// 	{
						// 		nBit = 1<<(31-m);
						// 		nBit = nBit & nChReplayData1[j];
						// 		if(nBit == 0)
						// 		{
						// 			nbits[nCount++] = 0;
						// 		}
						// 		else
						// 		{
						// 			nbits[nCount++] = 1;
						// 		}
						// 	}
						// }

						// for(int m = 0; m < 5; m++)
						// {
						// 	for(int n = 0; n < 32; n++)
						// 	{
						// 		pDrv_BlockPkg->data[nPointIndex + m] |= nbits[m*32 + n]<<(31 - n);
						// 	}
						// }
					}
				}
				else
				{
					if(pCoefItems->nCode == 32)
					{
						//6路回放通道
						long nCount = pCoefItems->nChCnt;

						for(int j = 0; j < nCount; j++)
						{
							pDrv_BlockPkg->data[nPointIndex + j] = nChReplayData1[j];

							if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
									|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
							{
							pDrv_BlockPkg->data[nPointIndex2 + j] = nChReplayData2[j];
						}
					}
					}
					else if(pCoefItems->nCode == 16)
					{
						//12路、8路回放通道
						long nCount = pCoefItems->nChCnt / 2;
						long nTemp;

						for(int j = 0; j < nCount; j++)
						{
							nTemp = nChReplayData1[j * 2];

							if(nTemp < 0)
							{
								nTemp = nTemp * (-1);
								nTemp = nTemp << 16;
								nTemp = nTemp * (-1);
							}
							else
							{
								nTemp = nTemp << 16;
							}

							nTemp &= 0xffff0000;
							pDrv_BlockPkg->data[nPointIndex + j] |= nTemp;
							nTemp = nChReplayData1[j * 2 + 1];

							if(nTemp < 0)
							{
								nTemp = nTemp * (-1);
								nTemp = nTemp << 16;
								nTemp = nTemp * (-1);
								nTemp = nTemp >> 16;
							}

							nTemp &= 0xffff;
							pDrv_BlockPkg->data[nPointIndex + j] |= nTemp;

							if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
									|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
							{
							nTemp = nChReplayData2[j * 2];

							if(nTemp < 0)
							{
								nTemp = nTemp * (-1);
								nTemp = nTemp << 16;
								nTemp = nTemp * (-1);
							}
							else
							{
								nTemp = nTemp << 16;
							}

							nTemp &= 0xffff0000;
							pDrv_BlockPkg->data[nPointIndex2 + j] |= nTemp;
							nTemp = nChReplayData2[j * 2 + 1];

							if(nTemp < 0)
							{
								nTemp = nTemp * (-1);
								nTemp = nTemp << 16;
								nTemp = nTemp * (-1);
								nTemp = nTemp >> 16;
							}

							nTemp &= 0xffff;
							pDrv_BlockPkg->data[nPointIndex2 + j] |= nTemp;
						}
					}
				}
					else if(pCoefItems->nCode == 20)
					{
						unsigned int nData[5];
						Trans_8ChanTo5Code(nData,nChReplayData1);

						for(int j = 0;j < 5;j++)
						{
							pDrv_BlockPkg->data[nPointIndex + j] = nData[j];
			}

						Trans_8ChanTo5Code(nData,nChReplayData2);

						for(int j = 0;j < 5;j++)
						{
							pDrv_BlockPkg->data[nPointIndex2 + j] = nData[j];
						}

						// std::bitset<160> nbits;
						//8路回放通道
						// unsigned int nBit;
						// long nCount = 0;

						// for(int j = 0; j < 8; j++)
						// {
						// 	for(int m = 0; m < 20; m++)
						// 	{
						// 		nBit = 1<<(31-m);
						// 		nBit = nBit & nChReplayData1[j];
						// 		if(nBit == 0)
						// 		{
						// 			nbits[nCount++] = 0;
						// 		}
						// 		else
						// 		{
						// 			nbits[nCount++] = 1;
						// 		}
						// 	}
						// }

						// for(int m = 0; m < 5; m++)
						// {
						// 	for(int n = 0; n < 32; n++)
						// 	{
						// 		pDrv_BlockPkg->data[nPointIndex + m] |= nbits[m*32 + n]<<(31 - n);
						// 	}
						// }

						// nCount = 0;
						// for(int j = 0; j < 8; j++)
						// {
						// 	for(int m = 0; m < 20; m++)
						// 	{
						// 		nBit = 1<<(31-m);
						// 		nBit = nBit & nChReplayData2[j];
						// 		if(nBit == 0)
						// 		{
						// 			nbits[nCount++] = 0;
						// 		}
						// 		else
						// 		{
						// 			nbits[nCount++] = 1;
						// 		}
						// 	}
						// }

						// for(int m = 0; m < 5; m++)
						// {
						// 	for(int n = 0; n < 32; n++)
						// 	{
						// 		pDrv_BlockPkg->data[nPointIndex2 + m] |= nbits[m*32 + n]<<(31 - n);
						// 	}
						// }
					}
				}
			}

			if(m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG
					|| m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
			{
			memset(nChReplayData1, 0, 48 * sizeof(long));
			//插入最后一个点
			nOffset1 = nOffset + (nPointNum - 1) * m_nChSelCount;
			int nChanIdx = 0;

			for(int j = 0; j < m_oModule[nModuleIndex].m_nChUseCount; j++)
			{
				if(m_oModule[nModuleIndex].m_oChMap[j].m_nChSel == 0)
				{
					continue;
				}

				fInsertVal = (m_pProcessBuf[nOffset1 + nChanIdx] + m_arrLastPoint[nOffset + nChanIdx]) * 0.5;
				fvalue = fInsertVal;
					fvalue = fvalue * pCoefItems->Item[j].fTmtCoef; //变比
				fvalue = fvalue * pCoefItems->Item[j].fCoef + pCoefItems->Item[j].fZero;
				fvalue = fvalue / pCoefItems->Item[j].fMaxValue;
					fvalue = fvalue * pCoefItems->Item[j].fReverse;

				if(fabs(fvalue) > 0.999999) //限制幅值
				{
					if(fvalue > 0)
					{
						fvalue = 0.999999;
					}
					else
					{
						fvalue = -0.999999;
					}
				}

				nChReplayData1[pCoefItems->Item[j].nCh] = nCode * fvalue;
				nChanIdx++;
			}

			nPointIndex = 2 * nReplayDataLen * (nPointNum - 1) + nReplayDataLen;

			if(pCoefItems->nCode == 32)
			{
				//6路回放通道
				long nCount = pCoefItems->nChCnt;

				for(int j = 0; j < nCount; j++)
				{
					pDrv_BlockPkg->data[nPointIndex + j] = nChReplayData1[j];
				}
			}
			else if(pCoefItems->nCode == 16)
			{
				//12路、8路回放通道
				long nCount = pCoefItems->nChCnt / 2;
				long nTemp;

				for(int j = 0; j < nCount; j++)
				{
					nTemp = nChReplayData1[j * 2];

					if(nTemp < 0)
					{
						nTemp = nTemp * (-1);
						nTemp = nTemp << 16;
						nTemp = nTemp * (-1);
					}
					else
					{
						nTemp = nTemp << 16;
					}

					nTemp &= 0xffff0000;
					pDrv_BlockPkg->data[nPointIndex + j] |= nTemp;
					nTemp = nChReplayData1[j * 2 + 1];

					if(nTemp < 0)
					{
						nTemp = nTemp * (-1);
						nTemp = nTemp << 16;
						nTemp = nTemp * (-1);
						nTemp = nTemp >> 16;
					}

					nTemp &= 0xffff;
					pDrv_BlockPkg->data[nPointIndex + j] |= nTemp;
				}
			}
				else if(pCoefItems->nCode == 20)
				{
					unsigned int nData[5];
					Trans_8ChanTo5Code(nData,nChReplayData1);

					for(int j = 0;j < 5;j++)
					{
						pDrv_BlockPkg->data[nPointIndex + j] = nData[j];
					}

					// std::bitset<160> nbits;
					// //8路回放通道
					// unsigned int nBit;
					// long nCount = 0;

					// for(int j = 0; j < 8; j++)
					// {
					// 	for(int m = 0; m < 20; m++)
					// 	{
					// 		nBit = 1<<(31-m);
					// 		nBit = nBit & nChReplayData1[j];
					// 		if(nBit == 0)
					// 		{
					// 			nbits[nCount++] = 0;
					// 		}
					// 		else
					// 		{
					// 			nbits[nCount++] = 1;
					// 		}
					// 	}
					// }

					// for(int m = 0; m < 5; m++)
					// {
					// 	for(int n = 0; n < 32; n++)
					// 	{
					// 		pDrv_BlockPkg->data[nPointIndex + m] |= nbits[m*32 + n]<<(31 - n);
					// 	}
					// }
				}
			}
	#endif
		}
    }

	if(m_bUseBinaryModule)
	{
		//主板开出量回放
		int nReplayDataLen = 2;//FPGA播放通道长度
		// pDrv_BlockPkg->module = (1 << (nModulePos)) << 16;
		pDrv_BlockPkg->title = 0x05640564;
		pDrv_BlockPkg->length = 2 * nPointNum * nReplayDataLen + 1;
		pDrv_BlockPkg->cmd = 0x4002;
		unsigned int nBOValue = 0;
		unsigned int nBOState[64];
		int nOffset = m_nChSelCount - 2;

		for(int i = 0; i < nPointNum; i++)
		{
			nOffset1 = i * m_nChSelCount + nOffset;
			nPointIndex = 2 * nReplayDataLen * i;

			if(i == 0)
			{
				memcpy(&pDrv_BlockPkg->data[nPointIndex],&m_pProcessBuf[nOffset1],4);//K32~k1
			}
			else
			{
				memcpy(&pDrv_BlockPkg->data[nPointIndex],&m_pProcessBuf[nOffset1],4);//K32~k1
				nPointIndex2 = nPointIndex - nReplayDataLen;
				pDrv_BlockPkg->data[nPointIndex2] = pDrv_BlockPkg->data[nPointIndex];
				pDrv_BlockPkg->data[nPointIndex2 + 1] = pDrv_BlockPkg->data[nPointIndex + 1];
			}
		}

		//插入最后一个点
		nOffset1 = nOffset + (nPointNum - 1) * m_nChSelCount;
		nPointIndex = 2 * nReplayDataLen * (nPointNum - 1) + nReplayDataLen;
		memcpy(&pDrv_BlockPkg->data[nPointIndex],&m_pProcessBuf[nOffset1],4);//K32~k1
	}

#ifdef _Stt_Cmtrd_Save_File_
    CString strTemp;

    for(int i = 0; i < COMTRADE_REPLAY_PKG_POINTS; i++)
    {
        strTemp.AppendFormat(_T("%.3f\r\n"), pDrv_BlockPkgs[0].data[6 * i] * 0.001);
    }

    m_oCmtrdSaveFile.Write(strTemp, strTemp.GetLength());
#endif
    memcpy(pDriveBuf + nWritePos, pDrv_BlockPkgs, nWriteLen);
    nWritePos += nWriteLen;
#endif
}

bool CSttReplayTest::WriteComtradeDataToDrive1(CComtradeDataBuffer *pComtradeBuf, BYTE *pDriveBuf, int &nDriveWritePos, unsigned int nMaxBlockCnt, int nPreComtradeLeftLen)
{	
    //每次解析ComtradeBuf数据长度
    int nLastPointSize = m_nChSelCount * sizeof(float);
    int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS / 2;
    //共享缓存中已经有BlockCnt
    int nHasBlockCnt = nDriveWritePos / sizeof(Drv_BlockPkg);
    int nNeedBlockCnt = nMaxBlockCnt - nHasBlockCnt;
    int nCurrComtradeBufLeftLen = 0;
    long nReadLen = 0;
    bool bABChanged = false;

    if(nPreComtradeLeftLen > 0)
    {
        nReadLen = pComtradeBuf->ReadData(m_pOnceProcessBuf + nPreComtradeLeftLen, nOnceProcessLen - nPreComtradeLeftLen);
        int nPoints = (nPreComtradeLeftLen + nReadLen) / m_nChSelCount;
        m_pProcessBuf = m_pOnceProcessBuf;

        //更新用于插值的m_arrLastPoint
        if(nReadLen < nOnceProcessLen - nPreComtradeLeftLen)
        {
            //最后一个点时，最后插入点与最后一个点相同
            memcpy(m_arrLastPoint, m_pProcessBuf + nPreComtradeLeftLen + nReadLen - m_nChSelCount, nLastPointSize);
        }
        else
        {
            if(pComtradeBuf->GetDataLen() > 0)
            {
                memcpy(m_arrLastPoint, pComtradeBuf->GetCurDataBuf(), nLastPointSize);
            }
            else
            {
                //查看下一个ComtradeBuf,
                CComtradeDataBuffer *pComtradeBuf1 = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex + 1);

                if(pComtradeBuf1->CanRead())
                {
                    memcpy(m_arrLastPoint, pComtradeBuf1->GetCurDataBuf(), nLastPointSize);
                }
                else
                {
                    //最后一个点时，最后插入点与最后一个点相同
                    memcpy(m_arrLastPoint, m_pProcessBuf + nPreComtradeLeftLen + nReadLen - m_nChSelCount, nLastPointSize);
                }
            }
        }

        OnceWriteProcessDataToDrive1(pDriveBuf, nDriveWritePos, nPoints);
        nNeedBlockCnt -= m_nModuleSelCount;

        if(nReadLen < nOnceProcessLen - nPreComtradeLeftLen)
        {
            //最后一帧数据
            bABChanged = true;
            m_nCurrPlayIndex++;
            //填完后设置有效标志
            SetDriveBufValid(pDriveBuf, nDriveWritePos / sizeof(Drv_BlockPkg));
            return bABChanged;
        }
    }

    while(nNeedBlockCnt > 0)
    {
        nCurrComtradeBufLeftLen = pComtradeBuf->GetDataLen();

        if(nCurrComtradeBufLeftLen < nOnceProcessLen)
        {
            break;
        }

        m_pProcessBuf = pComtradeBuf->GetCurDataBuf();

        //更新用于插值的m_arrLastPoint
        if(nCurrComtradeBufLeftLen > nOnceProcessLen)
        {
            memcpy(m_arrLastPoint, m_pProcessBuf + nOnceProcessLen, nLastPointSize);
        }
        else
        {
            //查看下一个ComtradeBuf,
            CComtradeDataBuffer *pComtradeBuf1 = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex + 1);

            if(pComtradeBuf1->CanRead())
            {
                memcpy(m_arrLastPoint, pComtradeBuf1->GetCurDataBuf(), nLastPointSize);
            }
            else
            {
                //最后一个点时，最后插入点与最后一个点相同
                memcpy(m_arrLastPoint, m_pProcessBuf + nOnceProcessLen - m_nChSelCount, nLastPointSize);
            }
        }

        OnceWriteProcessDataToDrive1(pDriveBuf, nDriveWritePos, COMTRADE_REPLAY_PKG_POINTS / 2);
        //更新ComtradeBuf读位置
        pComtradeBuf->OffsetReadPos(nOnceProcessLen);
        nNeedBlockCnt -= m_nModuleSelCount;
    }

    if(nNeedBlockCnt == 0)
    {
        //填完后设置有效标志
        SetDriveBufValid(pDriveBuf, nDriveWritePos / sizeof(Drv_BlockPkg));

        if(pComtradeBuf->GetDataLen() == 0)
        {
            m_nCurrPlayIndex++;
            bABChanged = true;
        }
    }
    else
    {
        //AB切换
        bABChanged = true;
        nReadLen = 0;

        if(nCurrComtradeBufLeftLen > 0)
        {
            nReadLen = pComtradeBuf->ReadData(m_pOnceProcessBuf, nCurrComtradeBufLeftLen);
        }

        m_nCurrPlayIndex++;
        pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);

        if(!pComtradeBuf->CanRead())
        {
            if(nReadLen > 0)
            {
                int nPoints = nReadLen / m_nChSelCount;
                m_pProcessBuf = m_pOnceProcessBuf;
                //更新用于插值的m_arrLastPoint
                //最后一个点时，最后插入点与最后一个点相同
                memcpy(m_arrLastPoint, m_pProcessBuf + nReadLen - m_nChSelCount, nLastPointSize);
                OnceWriteProcessDataToDrive1(pDriveBuf, nDriveWritePos, nPoints);
                nNeedBlockCnt -= m_nModuleSelCount;
            }

            //填完后设置有效标志
            SetDriveBufValid(pDriveBuf, nDriveWritePos / sizeof(Drv_BlockPkg));			
        }
        else
        {
            WriteComtradeDataToDrive1(pComtradeBuf, pDriveBuf, nDriveWritePos, nMaxBlockCnt, nReadLen);
        }
    }

    return bABChanged;
}

//由LoopBuf到ShareLoopBuf
void CSttReplayTest::WriteLoopDataToDrive()
{
    CComtradeDataBuffer *pLoopBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(0);

    if(!pLoopBuf->CanRead())
    {
        return;
    }

    BYTE *pDriveBuf = NULL;
    unsigned int nMaxBlockCnt = 0;
    int nDriveWritePos = 0;

    //查询空共享缓存信息
    if(!QueryDriveBufInfo(&pDriveBuf, nMaxBlockCnt, 0))
    {
        return;
    }

    //每次解析ComtradeBuf数据长度
    int nLastPointSize = m_nChSelCount * sizeof(float);
    int nOnceProcessLen = m_nChSelCount * COMTRADE_REPLAY_PKG_POINTS / 2;
    //共享缓存中已经有BlockCnt
    int nNeedBlockCnt = nMaxBlockCnt;
    int nCurrComtradeBufLeftLen = 0;
    long nReadLen = 0;

    while(nNeedBlockCnt > 0)
    {
        nCurrComtradeBufLeftLen = pLoopBuf->GetDataLen();

        if(nCurrComtradeBufLeftLen < nOnceProcessLen)
        {
            break;
        }

        m_pProcessBuf = pLoopBuf->GetCurDataBuf();

        //更新用于插值的m_arrLastPoint
        if(nCurrComtradeBufLeftLen > nOnceProcessLen)
        {
            memcpy(m_arrLastPoint, m_pProcessBuf + nOnceProcessLen, nLastPointSize);
        }
        else
        {
            //最后数据
            memcpy(m_arrLastPoint, m_pProcessBuf + nOnceProcessLen - m_nChSelCount, nLastPointSize);
        }

        OnceWriteProcessDataToDrive1(pDriveBuf, nDriveWritePos, COMTRADE_REPLAY_PKG_POINTS / 2);
        //更新ComtradeBuf读位置
        pLoopBuf->OffsetReadPos(nOnceProcessLen);
        nNeedBlockCnt -= m_nModuleSelCount;
    }

    if((nNeedBlockCnt > 0) && (nCurrComtradeBufLeftLen > 0))
    {
        nReadLen = pLoopBuf->ReadData(m_pOnceProcessBuf, nCurrComtradeBufLeftLen);
        int nPoints = nReadLen / m_nChSelCount;
        m_pProcessBuf = m_pOnceProcessBuf;
        //更新用于插值的m_arrLastPoint
        //最后一个点时，最后插入点与最后一个点相同
        memcpy(m_arrLastPoint, m_pProcessBuf + nReadLen - m_nChSelCount, nLastPointSize);
        OnceWriteProcessDataToDrive1(pDriveBuf, nDriveWritePos, nPoints);
        nNeedBlockCnt -= m_nModuleSelCount;
    }

    //填完后设置有效标志
    SetDriveBufValid(pDriveBuf, nDriveWritePos / sizeof(Drv_BlockPkg));
}

bool CSttReplayTest::WriteABDataToDrive()
{
    CComtradeDataBuffer *pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(m_nCurrPlayIndex);

    if(!pComtradeBuf->CanRead())
    {
        return false;
    }

    BYTE *pDriveBuf = NULL;
    unsigned int nMaxBlockCnt = 0;

    //查询空共享缓存信息
    if(!QueryDriveBufInfo(&pDriveBuf, nMaxBlockCnt, 1))
    {
        return false;
    }

    //初始化处理缓存
    int nDriveWritePos = 0;
	CLogPrint::LogString(XLOGLEVEL_TRACE,_T("WriteComtradeDataToDrive1"));
    if(WriteComtradeDataToDrive1(pComtradeBuf, pDriveBuf, nDriveWritePos, nMaxBlockCnt, 0))
    {
        //AB已切换
        if(!m_bSendFinish)
        {
            CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
            ASSERT(pServerEngine != NULL);
            pServerEngine->Comtrade_SendRequestData(m_nCurrReqIndex);
        }
    }

    return true;
}

BOOL CSttReplayTest::EventProcess()
{
    BOOL bTestFinished = FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished, m_oTestFinishedTime);
	if(bTestFinished && m_oTestFinishedTime.dTime < 0.001)
	{
		bTestFinishNormal = FALSE;
	}
#endif
    return bTestFinished;
}

BOOL CSttReplayTest::EventProcessEx()
{
	//驱动事件处理
	WriteABDataToDrive();
	return TRUE;
}

void CSttReplayTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(this, pXmlSerialize);

    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttReplayTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oReplayResult.m_fTestInTime = oRampRestCom.m_fTripTime;
    int nrBinSwitchCount, nrBinExSwitchCount;

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
        m_oReplayResult.m_nrBinSwitchCount[i] = nrBinSwitchCount;

        for(int j = 0; j < nrBinSwitchCount; j++)
        {
            m_oReplayResult.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
        m_oReplayResult.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount; j++)
        {
            m_oReplayResult.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

#endif
    stt_xml_serialize(&m_oReplayResult, pXmlSerialize);
}

void CSttReplayTest::Stop()
{
    SetTestStarting(FALSE);
    CSttTestBase::Stop();
#ifdef _SttTestServer_For_Debug_
    StopEventThread();
#endif
#ifdef _Stt_Cmtrd_Save_File_
    CloseCmtrdSaveFile();
#endif
}

void CSttReplayTest::Triger()
{
    //收到手动触发命令
#ifndef _SttTestServer_For_Debug_
    CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
    //通知驱动手动触发
}

void CSttReplayTest::OnSendDataFinish(int nIndex, int nSendNum)
{
    //Comtrade数据发送完成命令
    UINT nSendIndex = (UINT)nIndex & 0x7FFFFFFF;

    if(nSendIndex != 0)
    {
        m_bSendFinish = ((UINT)nIndex) >> 31;
    }

    m_nCurrReqIndex++;
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("OnSendDataFinish:nIndex=%d,nSendNum=%d,m_nCurrReqIndex=%d"), nSendIndex, nSendNum, m_nCurrReqIndex);
    //通知接收线程数据已发送完成
    g_oSttComtradeRcvSocket.OnSendDataFinish(nSendIndex, nSendNum);
}

void CSttReplayTest::OnSendDataStart(int nIndex, int nSendNum)
{
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("OnSendDataStart:nIndex=%d,nSendNum=%d"), nIndex, nSendNum);
    //通知接收线程数据已发送完成
    g_oSttComtradeRcvSocket.OnSendDataStart(nIndex, nSendNum);
}

void CSttReplayTest::OnAfterMoveToComtradeBuf(int nIndex, int nDataLen)
{
    CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
    ASSERT(pServerEngine != NULL);

    if(nIndex == 0)
    {
        //之前请求的是LoopBuf数据，再请求ABuf数据
        //将LoopBuf中数据搬移到共享LoopBuf中
        WriteLoopDataToDrive();
        pServerEngine->Comtrade_SendRequestData(1);
    }
    else if(nIndex == 1)
    {
        //之前请求的是ABuf数据
        if(!m_bSendFinish)
        {
            //数据未发完，继续请求BBuf数据
            pServerEngine->Comtrade_SendRequestData(2);
        }
        else
        {
            //数据已发完，
            //通知驱动开始回放
            StartEventThread();
        }
    }
    else if(nIndex == 2)
    {
        //之前第一次请求的是BBuf数据
        //通知驱动开始回放
        StartEventThread();
    }
}

#define REPLAY_FLAG_WRITE_FINISH        0x01
#define REPLAY_FLAG_TEST_FINISH			0x02
#define REPLAY_FLAG_TEST_TRIP           0x03

void CSttReplayTest::StartTest()
{
    if(GetTestStarting())
    {
        return;
    }

    SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
if(!CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting = TRUE;
		pthread_mutex_unlock(&g_oTestResultMutex);
	}
    CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
    CSttTestBase::StartTest();
    //重新初始化AB缓存
    CComtradeBufMngr::g_pComtradeBufMngr->ResetBuf();
    g_oSttComtradeRcvSocket.ResetRcvLen();
    m_nCurrReqIndex = 0;
    m_nCurrPlayIndex = 1;
    m_nChSelCount = GetChSelCount();
    m_nModuleSelCount = GetModuleSelCount();
#ifdef _Stt_Cmtrd_Save_File_
    CString strFile = g_strFtpRootFile + _T("sttComtrade.txt");
    OpenCmtrdSaveFile(strFile);
#endif
    TtmToDrv();
#ifndef _SttTestServer_For_Debug_
    memset(m_pLtReplayBuffer, 0, sizeof(Drv_LtReplayBuffer));
#endif
    //收到开始测试命令后，根据配置参数请求数据
    CSttTestServerBase *pServerEngine = CSttTestServerBase::GetServerEngine();
    ASSERT(pServerEngine != NULL);

    if(IsLoop())
    {
        //需要循环数据
        m_nCurrReqIndex = 0;
        pServerEngine->Comtrade_SendRequestData(0);
    }
    else
    {
        //无循环数据
        m_nCurrReqIndex = 1;
        pServerEngine->Comtrade_SendRequestData(1);
    }
}

void CSttReplayTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_LtReplay(this, (char *)&m_oReplayConf);
#endif
}

void CSttReplayTest::StartEventThread()
{
    //先填充ABuf
    if(WriteABDataToDrive())
    {
        //再填充BBuf
        WriteABDataToDrive();
    }

#ifdef _SttTestServer_For_Debug_
    Sleep(1000);
    m_pEventThread =  CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SttEventThread, (LPVOID)this, 0, NULL);
#else
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("StartEventThread  LtReplayTest"));
	SetTestStarting(TRUE);
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(LtReplayTest);
#endif
}
#ifdef _SttTestServer_For_Debug_
void CSttReplayTest::StopEventThread()
{
    m_bReplayStarted = FALSE;
}

UINT CSttReplayTest::SttEventThread(LPVOID pParam)
{
    CLogPrint::LogString(XLOGLEVEL_INFOR, _T("===========SttEventThread enter"));
    CSttReplayTest *pReplayTest = (CSttReplayTest *)pParam;
    pReplayTest->m_bReplayStarted = TRUE;

    while(pReplayTest->m_bReplayStarted)
    {
        pReplayTest->EventProcess();
        Sleep(700);
    }

    pReplayTest->m_pEventThread = NULL;
    CLogPrint::LogString(XLOGLEVEL_INFOR, _T("===========SttEventThread exit"));
    return 0;
}

int CSttReplayTest::GetModuleChPos(int nModulePos, const char *pszChID)
{
    if(strcmp(pszChID, "Ua") == 0 || strcmp(pszChID, "Ia") == 0)
    {
        return 0;
    }
    else if(strcmp(pszChID, "Ub") == 0 || strcmp(pszChID, "Ib") == 0)
    {
        return 1;
    }
    else if(strcmp(pszChID, "Uc") == 0 || strcmp(pszChID, "Ic") == 0)
    {
        return 2;
    }
    else if(strcmp(pszChID, "Uz") == 0 || strcmp(pszChID, "I0") == 0)
    {
        return 3;
    }

    return 0;
}

long CSttReplayTest::CalReplayDataValue(int nModulePos, const char *pszChID, float fRawVal)
{
    //原始值计算为播放数据
    return (long)(fRawVal * 1000);
}
#endif
