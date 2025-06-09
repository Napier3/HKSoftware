#include "stdafx.h"
#include "BigComtradeFileRead.h"
#include "../../../Module/API/FileApi.h"



CBigComtradeFileRead::CBigComtradeFileRead()
{
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	m_pComtradePlayConfigRef = NULL;
#endif
	m_pdSamRate		 = NULL;
	m_pnDataPoints	 = NULL;
	m_nSamAmount = 0;

	m_pFileReadBuffer = NULL;
	m_nFileReadBufLen = 0;
	m_nReplayBuffMaxLenth = FILE_READBUF_SIZE;
	m_nReadBufDataLen = 0;			
//	m_nReadBufReadPos = 0;

	m_bReadFileFinish = FALSE;				
	m_bAnalysisFinish = FALSE;				
	m_dInsertFreq = 10000;	//zhouhj 20210922 从25000改为10000
	m_fReplayStartTime = 0;	
	m_fRawStartTime = 0;
#ifdef USE_InsertComtradeFile_Mode
	m_pInsertComtradeFile = NULL;
#else
	m_nInsertTotalPoints = 0;
	m_dInsertOffsetTime = 0;
#endif
//	m_dInsertOffsetTime = 0;
//	m_bHasOpenDataFile = FALSE; 
	m_oSrcComtradeFile.SetCreateBuffer(FALSE);
	m_bIsBinaryMode = TRUE;
	m_bAutoGenChABMap = TRUE;
}

CBigComtradeFileRead::~CBigComtradeFileRead()
{
	ClearTotalBuff();
	CloseReadFile();
}

void CBigComtradeFileRead::CloseReadFile()
{
#ifdef _PSX_IDE_QT_
	if (m_oFileRead.handle() != (int)INVALID_HANDLE_VALUE)
#else
	if (m_oFileRead.m_hFile != INVALID_HANDLE_VALUE)
#endif
	{
		m_oFileRead.Close();
	}
}

long CBigComtradeFileRead::CalSrcMaxSmpRateIntervalPoints()
{
	double dMaxSmpRate = 0;

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)
		{
			continue;
		}

		if (m_pdSamRate[nIndex]>dMaxSmpRate)
		{
			dMaxSmpRate = m_pdSamRate[nIndex];
		}
	}

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	long nChMaxCnt = m_pComtradePlayConfigRef->GetTotalChannelNum();
#else	
	long nChMaxCnt = 6;
#endif	

	if (nChMaxCnt <= 0)
	{
		nChMaxCnt = 1;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前模块总通道数为0"));
	}

	long nChMaxPoints = m_nReplayBuffMaxLenth / (nChMaxCnt * sizeof(float));
	double dMaxTime = nChMaxPoints/m_dInsertFreq;
	long nMaxPoints = dMaxTime*dMaxSmpRate;
	nMaxPoints++;//防止有余数，多加一个点
	return nMaxPoints;
}

void CBigComtradeFileRead::InitFileReadBuf(long nOnceReadFileLen)
{
	if (nOnceReadFileLen <= 0)
	{
		nOnceReadFileLen = FILE_READBUF_SIZE;
	}

	if (m_pFileReadBuffer != NULL)
	{
		delete m_pFileReadBuffer;
	}

	m_nCurSrcBeginPointIndex = 0;
	m_nReplayBuffMaxLenth = nOnceReadFileLen;
	m_nFileReadBufLen = CalSrcMaxSmpRateIntervalPoints()*m_oSrcComtradeFile.GetBinarySinglePointLength();

	m_pFileReadBuffer = new BYTE[m_nFileReadBufLen];
	m_nReadBufDataLen = 0;			
}

//读Comtrade cfg文件
BOOL CBigComtradeFileRead::OpenBigComtradeCfgFile(const CString &strComtradeFile,long nOnceReadFileLen)
{
	m_oSrcComtradeFile.Init();
	m_oSrcComtradeFile.SetCreateBuffer(FALSE);

	if (!m_oSrcComtradeFile.ReadCFGFile(strComtradeFile))
	{
		return FALSE;
	}

	m_oSrcComtradeFile.m_strComtradeFile = strComtradeFile;

	ClearTotalBuff();
	SetBigFileTotalSmpRates();
	InitFileReadBuf(nOnceReadFileLen);
	return TRUE;
}

void CBigComtradeFileRead::ClearComtradeCfgFile()
{
	ResetDataBuf();

	if(m_pComtradePlayConfigRef == NULL)
	{
		return;
	}

	POS pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModuleInfo = NULL;

	while(pos != NULL)
	{
		pModuleInfo = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModuleInfo->IsBinaryTypeModule())
		{

		POS posCh = pModuleInfo->GetHeadPosition();
		CSttModuleChComtradeBind *pCh = NULL;
		CString strValue;

		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModuleInfo->GetNext(posCh);

			pCh->m_fMomentaryVal = 0;
		}
	}

	}
}

//读完cfg文件后，初始化A\B\K映射关系
void CBigComtradeFileRead::InitChMapConfig()
{
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	CExBaseList *pAnalogList = m_oSrcComtradeFile.GetAnalogs();
	CExBaseList *pBinaryList = m_oSrcComtradeFile.GetBinarys();
	CExBaseList oUList,oIList;
	CExBaseList oBinaryList;

	POS pos = pAnalogList->GetHeadPosition();
	CComtradeAnalogData *pData = NULL;

	while(pos != NULL)
	{
		pData = (CComtradeAnalogData *)pAnalogList->GetNext(pos);

		if (pData->IsAnalogUData())
		{
			oUList.AddTail(pData);
		}
		else
		{
			oIList.AddTail(pData);
		}
	}

	pos = pBinaryList->GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;

	while(pos != NULL)
	{
		pBinaryData = (CComtradeBinaryData *)pBinaryList->GetNext(pos);
		oBinaryList.AddTail(pBinaryData);
	}

	//模拟量
	int nUAnalogyNum = oUList.GetCount();
	int nIAnalogyNum = oIList.GetCount();

	pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	POS posCh = NULL;
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	int nUChIndex = 0,nIChIndex = 0;
	int nModulesChCount = 0;

	//开出量
	int nBinaryNum = oBinaryList.GetCount();
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;
	int nBinaryChIndex = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetNext(pos);
		nModulesChCount = 0;

		if(!pModule->IsBinaryTypeModule())
		{
			nUChIndex = 0,nIChIndex = 0;
		posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

			if (m_bAutoGenChABMap)
			{
				int nASel = 0;
//				CString strName = _T("");

				if (pCh->IsModuleType_U())
				{
					if (nUAnalogyNum != 0)
					{
						pData = (CComtradeAnalogData *)oUList.GetAt(nUChIndex % nUAnalogyNum);
						nASel = pData->m_nChannelIndex;
						pCh->m_nChA_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-初始化通道选择
// 						pCh->m_nChB_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-初始化通道选择
					}
					nUChIndex++;
				}
				else
				{
					if (nIAnalogyNum != 0)
					{
						pData = (CComtradeAnalogData *)oIList.GetAt(nIChIndex % nIAnalogyNum);
						nASel = pData->m_nChannelIndex;
//						strName = pData->m_strName;
						pCh->m_nChA_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-初始化通道选择
// 						pCh->m_nChB_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-初始化通道选择

					}
					nIChIndex++;
				}

					//2024-4-15 wuxinyi 新需求：默勾选第一个插件的第一条通道
					if(nModulesChCount < 1)//20230914 wxy 总模块通道数超过12，默认不勾选
				{
					pCh->m_nChSelected = 1;
					//默认勾选  20220519 去除默认勾选,勾选的通道数量统一进行初始化,防止通道数量太多影响数据发送

				}
				else
				{
					pCh->m_nChSelected = 0;

				}

				if (nASel == 0)
				{
					pCh->InitCh_A(NULL);
				} 
				else
				{
					pCh->InitCh_A(pData);
				}

				pCh->InitCh_B(NULL);//20231025 wxy 添加B通道初始化
				pCh->m_nChB_Index = 0;
				//pCh->m_dK = 1; //dxy 20240204 按需求变比和通道初一的数值重新打开文件后不初始化
				pCh->m_fMomentaryVal = 0;
					
				} 
				else
				{
					if (pCh->IsModuleType_U())
					{
						pCh->InitCh_A((CComtradeAnalogData *)oUList.GetAt(pCh->m_nChA_Index - 1));
						pCh->InitCh_B((CComtradeAnalogData *)oUList.GetAt(pCh->m_nChB_Index - 1));
					}
					else
					{
						pCh->InitCh_A((CComtradeAnalogData *)oIList.GetAt(pCh->m_nChA_Index - 1));
						pCh->InitCh_B((CComtradeAnalogData *)oIList.GetAt(pCh->m_nChB_Index - 1));
					}

					pCh->m_fMomentaryVal = 0;
				}
				nModulesChCount++;
			}
		}
		else
		{
			if(nBinaryNum < 0)
			{
				continue;
			}
			posCh = pModule->GetHeadPosition();
			while(posCh != NULL)
			{
				pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
				pBinaryCh->InitBinaryCh((CComtradeBinaryData *)oBinaryList.GetAt(pBinaryCh->m_nBinaryCh_Index - 1));
			}

		}
	}

	//主板开出量
	pModule = m_pComtradePlayConfigRef->GetBinaryModule();
	if(pModule)
	{
		posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
			pBinaryCh->InitBinaryCh((CComtradeBinaryData *)oBinaryList.GetAt(pBinaryCh->m_nBinaryCh_Index - 1));
		}

	}


	oUList.RemoveAll();
	oIList.RemoveAll();
	oBinaryList.RemoveAll();
#endif
}


void CBigComtradeFileRead::RefreshChMapConfig()
{
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	CExBaseList *pAnalogList = m_oSrcComtradeFile.GetAnalogs();
	CExBaseList *pBinaryList = m_oSrcComtradeFile.GetBinarys();
	CExBaseList oUList,oIList;
	CExBaseList oBinaryList;

	POS pos = pAnalogList->GetHeadPosition();
	CComtradeAnalogData *pData = NULL;

	while(pos != NULL)
	{
		pData = (CComtradeAnalogData *)pAnalogList->GetNext(pos);

		if (pData->IsAnalogUData())
		{
			oUList.AddTail(pData);
		}
		else
		{
			oIList.AddTail(pData);
		}
	}

	pos = pBinaryList->GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;

	while(pos != NULL)
	{
		pBinaryData = (CComtradeBinaryData *)pBinaryList->GetNext(pos);
		oBinaryList.AddTail(pBinaryData);
	}

	//模拟量
	int nUAnalogyNum = oUList.GetCount();
	int nIAnalogyNum = oIList.GetCount();

	pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	POS posCh = NULL;
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	int nUChIndex = 0,nIChIndex = 0;
	int nModulesChCount = 0;

	//开出量
	int nBinaryNum = oBinaryList.GetCount();
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;
	int nBinaryChIndex = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetNext(pos);

		if(!pModule->IsBinaryTypeModule())
		{
			posCh = pModule->GetHeadPosition();
			while(posCh != NULL)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

				if (m_bAutoGenChABMap)
				{
					int nASel = 0;
					//				CString strName = _T("");

					if (pCh->IsModuleType_U())
					{
						if (nUAnalogyNum != 0)
						{
							pData = (CComtradeAnalogData *)oUList.GetAt(nUChIndex % nUAnalogyNum);
							nASel = pData->m_nChannelIndex;
							pCh->m_nChA_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-初始化通道选择
							// 						pCh->m_nChB_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-初始化通道选择
						}
						nUChIndex++;
					}
					else
					{
						if (nIAnalogyNum != 0)
						{
							pData = (CComtradeAnalogData *)oIList.GetAt(nIChIndex % nIAnalogyNum);
							nASel = pData->m_nChannelIndex;
							//						strName = pData->m_strName;
							pCh->m_nChA_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-初始化通道选择
							// 						pCh->m_nChB_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-初始化通道选择

						}
						nIChIndex++;
					}

// 					//2024-4-15 wuxinyi 新需求：默勾选第一个插件的第一条通道
// 					if(nModulesChCount < 1)//20230914 wxy 总模块通道数超过12，默认不勾选
// 					{
// 						pCh->m_nChSelected = 1;
// 						//默认勾选  20220519 去除默认勾选,勾选的通道数量统一进行初始化,防止通道数量太多影响数据发送
// 
// 					}
// 					else
// 					{
// 						pCh->m_nChSelected = 0;
// 
// 					}

					if (nASel == 0)
					{
						pCh->InitCh_A(NULL);
					} 
					else
					{
						pCh->InitCh_A(pData);
					}

					pCh->InitCh_B(NULL);//20231025 wxy 添加B通道初始化
					pCh->m_nChB_Index = 0;
					//pCh->m_dK = 1; //dxy 20240204 按需求变比和通道初一的数值重新打开文件后不初始化
					pCh->m_fMomentaryVal = 0;

			} 
			else
			{
				if (pCh->IsModuleType_U())
				{
					pCh->InitCh_A((CComtradeAnalogData *)oUList.GetAt(pCh->m_nChA_Index - 1));
					pCh->InitCh_B((CComtradeAnalogData *)oUList.GetAt(pCh->m_nChB_Index - 1));
				}
				else
				{
					pCh->InitCh_A((CComtradeAnalogData *)oIList.GetAt(pCh->m_nChA_Index - 1));
					pCh->InitCh_B((CComtradeAnalogData *)oIList.GetAt(pCh->m_nChB_Index - 1));
				}

				pCh->m_fMomentaryVal = 0;
			}
				nModulesChCount++;
		}
	}
		else
		{
			if(nBinaryNum < 0)
			{
				continue;
			}
			posCh = pModule->GetHeadPosition();
			while(posCh != NULL)
			{
				pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
				pBinaryCh->InitBinaryCh((CComtradeBinaryData *)oBinaryList.GetAt(pBinaryCh->m_nBinaryCh_Index - 1));
			}

		}
	}

	//主板开出量
	pModule = m_pComtradePlayConfigRef->GetBinaryModule();
	if(pModule)
	{
		posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
			pBinaryCh->InitBinaryCh((CComtradeBinaryData *)oBinaryList.GetAt(pBinaryCh->m_nBinaryCh_Index - 1));
		}

	}


	oUList.RemoveAll();
	oIList.RemoveAll();
	oBinaryList.RemoveAll();
#endif
}

void CBigComtradeFileRead::UpdateChMapConfig()
{
	if(!m_pComtradePlayConfigRef)
	{
		return;
	}
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	CExBaseList *pAnalogList = m_oSrcComtradeFile.GetAnalogs();
	CExBaseList *pBinaryList = m_oSrcComtradeFile.GetBinarys();

	CExBaseList oUList,oIList;
	CExBaseList oBinaryList;

	POS pos = pAnalogList->GetHeadPosition();
	CComtradeAnalogData *pData = NULL;
	CComtradeBinaryData *pBinaryData = NULL;

	while(pos != NULL)
	{
		pData = (CComtradeAnalogData *)pAnalogList->GetNext(pos);

		if (pData->IsAnalogUData())
		{
			oUList.AddTail(pData);
		}
		else
		{
			oIList.AddTail(pData);
		}
	}

	pos = pBinaryList->GetHeadPosition();
	while(pos != NULL)
	{
		pBinaryData = (CComtradeBinaryData *)pBinaryList->GetNext(pos);
		oBinaryList.AddTail(pBinaryData);
	}

	int nUAnalogyNum = oUList.GetCount();
	int nIAnalogyNum = oIList.GetCount();
	int nBinaryNum = oBinaryList.GetCount();

	pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	POS posCh = NULL;
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;
	int nUChIndex = 0,nIChIndex = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetNext(pos);
		if(pModule->IsBinaryTypeModule())
		{
			posCh = pModule->GetHeadPosition();
			pModule->InitReplayBufBinary(m_pInsertComtradeFile->m_nTotalPoints);
			while(posCh != NULL)
			{
				pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
				pBinaryCh->InitBinaryCh((CComtradeBinaryData *)oBinaryList.GetAt(pBinaryCh->m_nBinaryCh_Index - 1));
			}				
			UpdateBinaryChReplayBuf(pModule);
		}
		else
		{
		posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);
 
			if (pCh->IsModuleType_U())
			{
				pCh->InitCh_A((CComtradeAnalogData *)oUList.GetAt(pCh->m_nChA_Index - 1));
				pCh->InitCh_B((CComtradeAnalogData *)oUList.GetAt(pCh->m_nChB_Index - 1));
			}
			else
			{
				pCh->InitCh_A((CComtradeAnalogData *)oIList.GetAt(pCh->m_nChA_Index - 1));
				pCh->InitCh_B((CComtradeAnalogData *)oIList.GetAt(pCh->m_nChB_Index - 1));
			}

			pCh->m_fMomentaryVal = 0;

				UpdateChReplayBuf(pCh,pModule,FALSE);
		}
	}

	}

	//主板开出量模块	
	pModule = m_pComtradePlayConfigRef->GetBinaryModule();
	if(pModule)
	{
		posCh = pModule->GetHeadPosition();
		pModule->InitReplayBufBinary(m_pInsertComtradeFile->m_nTotalPoints);
		while(posCh != NULL)
		{
			pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
			pBinaryCh->InitBinaryCh((CComtradeBinaryData *)oBinaryList.GetAt(pBinaryCh->m_nBinaryCh_Index - 1));
		}				
		UpdateBinaryChReplayBuf(pModule);
	}

	oUList.RemoveAll();
	oIList.RemoveAll();
	oBinaryList.RemoveAll();
#endif
}

void CBigComtradeFileRead::InitSrcAnalogsBeginAng_SpecialSmpRate()
{
	double nCalTotalPoints = 80;
	int nIndex = 0;
	BOOL bHasSpecialSmpRate = FALSE;
	double dCurFreq = m_oSrcComtradeFile.m_dFreq;

	for (nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)
		{
			continue;
		}

		if ((fabs(dCurFreq*2-m_pdSamRate[nIndex])<0.0001)||(fabs(dCurFreq-m_pdSamRate[nIndex])<0.0001))
		{
			bHasSpecialSmpRate = TRUE;
		}
	}

	if (!bHasSpecialSmpRate)//首先判断是否存在特殊采样频率
	{
		return;
	}

	long nCurIntervalEndPtIndex = m_nCurSrcBeginPointIndex + m_oSrcComtradeFile.m_nTotalPoints - 1;
	long nSmpRateBeginIndex = 0;
	long nSmpRateEndIndex = 0;
	long nSingleLoopPts = 0;//单个周波的点数
	BOOL bFirst = TRUE;

	for (nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)
		{
			continue;
		}

		if (bFirst)
		{
			nSmpRateEndIndex += (m_pnDataPoints[nIndex]-1);
			bFirst = FALSE;
		}
		else
		{
			nSmpRateEndIndex += (m_pnDataPoints[nIndex]);
		}

		nSingleLoopPts = m_pdSamRate[nIndex]/dCurFreq;

		if ((m_nCurSrcBeginPointIndex<nSmpRateEndIndex)&&(nCurIntervalEndPtIndex>nSmpRateBeginIndex))//确保读取的数据点在该段采样频率下
		{
			if ((m_nCurSrcBeginPointIndex>=nSmpRateBeginIndex)&&(fabs(dCurFreq*2-m_pdSamRate[nIndex])<0.0001))//如果当前频率为2*50Hz 并且当前段第一个采样频率即为此，需要计算出是否同相位
			{
				BOOL bInPhase_SpecialSmpRate = (((m_nCurSrcBeginPointIndex-nSmpRateBeginIndex)%2) == 0);
				m_oSrcComtradeFile.SetInPhase_SpecialSmpRate(bInPhase_SpecialSmpRate);
			}
			else if ((nCurIntervalEndPtIndex<= nSmpRateEndIndex)
				&&((nCurIntervalEndPtIndex-nSmpRateBeginIndex)>(nSingleLoopPts+3))
				&&(m_pdSamRate[nIndex]>4*dCurFreq))//如果当前采样频率为当前段的最后一个采样频率,并且在当前段的总采样点数大于一个周波+3的点数，并且每周波采样点数大于4的情况下
				//，计算出当前采样频率下最后一个点的相位
			{
				m_oSrcComtradeFile.InitBeginAng_SpecialSmpRate(m_oSrcComtradeFile.m_nTotalPoints-1,(nSmpRateEndIndex-nCurIntervalEndPtIndex)/m_pdSamRate[nIndex],dCurFreq);
			}
		}

		nSmpRateBeginIndex = nSmpRateEndIndex;
	}
}

BOOL CBigComtradeFileRead::CheckComtradeFile(const CString &strComtradeFile)
{
	CloseReadFile();
	CRcdComtradeFile oComtradeFile;
	oComtradeFile.Init();
	oComtradeFile.SetCreateBuffer(FALSE);
	CloseReadFile();

	if (!oComtradeFile.ReadCFGFile(strComtradeFile))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CBigComtradeFileRead::OpenComtradeFile(const CString &strComtradeFile,long nOnceReadFileLen,BOOL bInitDefault)
{
	//初始化缓存
	BOOL bRet = OpenBigComtradeCfgFile(strComtradeFile,nOnceReadFileLen);

	if (bRet)
	{
		//读完配置文件后，初始化config映射
		if (bInitDefault)
		{//若是打开测试记录，则不需要初始化赋值
			InitChMapConfig();
		}
		else
		{
			RefreshChMapConfig();//波形复归重新打开波形文件，但不更新通道
		}
		
		//读20M数据，解析到AnalogData
		bRet = ReadBigComtradeDataFile(strComtradeFile);

		if (!bRet)
		{
			return bRet;
		}

		//需要注意的是，如果是故障回放之前，由AnalogData，生成ReplayBuf始终从AnalogData开始位置解析
		//由AnalogData，生成ReplayBuf
		GenerateReplayBufFromRawData(/*TRUE*/);
	}

	return bRet;
}

//根据m_pFileReadBuffer缓存剩余数据，读文件填充满,并解析到AnalogData中
BOOL CBigComtradeFileRead::ReadBigComtradeDataFile(const CString &strComtradeFile)
{
	BOOL bRet = FALSE;

	if (m_oSrcComtradeFile.m_nDataFileType == 0)
	{
		m_bIsBinaryMode = FALSE;
		bRet = ReadBigDataAsASIIMode(strComtradeFile);
	}
	else
	{
		m_bIsBinaryMode = TRUE;
		bRet = ReadBigDataAsBINARYMode(strComtradeFile);
	}

	return bRet;
}

void CBigComtradeFileRead::GenerateComtradeChDatas(BOOL bSeekToBegin)
{
	GenerateComtradeChDataFromDataFile(bSeekToBegin);
	GenerateReplayBufFromRawData(/*FALSE*/);
}

//根据配置参数，定位文件读数据，并解析到AnalogData中
BOOL CBigComtradeFileRead::ReadLoopRawDataFile()
{
	GenerateComtradeChDataFromDataFile(TRUE);
	return TRUE;
}

double CBigComtradeFileRead::CalCurRawStartTime()
{
	long nBeginPosPointIndex = 0;
	long nEndPosPointIndex = 0;
	BOOL bFirstSmpRate = TRUE;
	m_fRawStartTime = 0;

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)//采样点数小于等于0的采样率无效，直接跳过
		{
			continue;
		}

		if (bFirstSmpRate)//如果是第一个采样率，其结束点索引为当前总点数 减去1
		{
			nEndPosPointIndex += (m_pnDataPoints[nIndex]-1);
			bFirstSmpRate = FALSE;
		}
		else//第二个采样率以后的情况，直接加上采样总点数，因为默认起始点为上一个采样率的结束点
		{
			nEndPosPointIndex += (m_pnDataPoints[nIndex]);
		}

		if ((m_nCurSrcBeginPointIndex<=nEndPosPointIndex)&&(m_nCurSrcBeginPointIndex>=nBeginPosPointIndex))//如果当前位置在该采样率区间内
		{
			m_fRawStartTime += (m_nCurSrcBeginPointIndex-nBeginPosPointIndex)/m_pdSamRate[nIndex];
			break;
		} 
		else
		{
			m_fRawStartTime += ((nEndPosPointIndex-nBeginPosPointIndex)/m_pdSamRate[nIndex]);
		}

		nBeginPosPointIndex = nEndPosPointIndex;
	}

	return m_fRawStartTime;
}

//由AnalogData原始数据填充满ReplayBuf
BOOL CBigComtradeFileRead::GenerateReplayBufFromRawData(UINT nUpdateMask)
{
	//ReplayBuf缓存填充满返回TRUE,AnalogData解析完而ReplayBuf缓存未填满返回FALSE
	m_fReplayStartTime = m_nCurInsertBeginPointIndex/(m_dInsertFreq);
	CalCurRawStartTime();

	//遍历每个通道，调用UpdateReplayBuf，依次更新
	BOOL bRet = FALSE;
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	POS pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;

	BOOL bSave = TRUE;
	POS posCh = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetNext(pos);

		if(pModule->IsBinaryTypeModule())
		{
			pModule->InitReplayBufBinary(m_pInsertComtradeFile->m_nTotalPoints);
                       //2023-03-18 wuxinyi 修改开出量通道映射被初始化为空问题
			posCh = pModule->GetHeadPosition();
			while(posCh != NULL)
			{
				pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
				pBinaryCh->InitBinaryCh((CComtradeBinaryData *)m_oSrcComtradeFile.GetBinaryDataByIndex(pBinaryCh->m_nBinaryCh_Index - 1));
			}	
			bRet = UpdateBinaryChReplayBuf(pModule);
		}
		else
		{
		POS posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

			if (pCh->IsModuleType_U())
		{
			if (nUpdateMask & CMTRD_UPDATE_RAWTOREPLAY_U == 0)
			{
				continue;
			}
		}
			else if (pCh->IsModuleType_I())
		{
			if (nUpdateMask & CMTRD_UPDATE_RAWTOREPLAY_I == 0)
			{
				continue;
			}
		}	

				bRet = UpdateChReplayBuf(pCh,pModule,bSave);
			bSave = FALSE;
		}
	}

	}
	
	//支持开出量触发时才更新开出通道
	if(m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.m_nUseBinaryModuleWidget)
	{
		pModule = m_pComtradePlayConfigRef->GetBinaryModule();

	posCh = pModule->GetHeadPosition();
	pModule->InitReplayBufBinary(m_pInsertComtradeFile->m_nTotalPoints);
	while(posCh != NULL)
	{
		pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
		pBinaryCh->InitBinaryCh((CComtradeBinaryData *)m_oSrcComtradeFile.GetBinaryDataByIndex(pBinaryCh->m_nBinaryCh_Index - 1));
	}	

		bRet = UpdateBinaryChReplayBuf(pModule);
	}

#endif
	return bRet;
}

//由回放缓存ReplayBuf填充AB缓存
BOOL CBigComtradeFileRead::GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf)
{
	//AB缓存填充满返回TRUE,ReplayBuf解析完而AB缓存未填满返回FALSE
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	//获取pABBuf当前空余的总长度,根据总通道数量计算出每个采样点占用的总长度，进而计算出当前缓存下能存放的总点数
	long nABBuffRemainSpace = pABBuf->GetRemainSpace();
	long nChs = m_pComtradePlayConfigRef->GetTotalChs_SelectedModule();
	if(nChs <= 0)
	{
		return FALSE;
	}

	long nABBuffRemainPts = nABBuffRemainSpace/nChs;

	//如果当前ReplayBuf里面剩余的总点数大于等于放满pABBuf需要的总点数,则放满缓存，并改变ReplayBuf中的m_nDataFillBeginPos位置  返回TRUE
#ifdef USE_InsertComtradeFile_Mode
	long nCurIntervalRemainPts = m_pInsertComtradeFile->m_nTotalPoints - m_nCurIntervalDeliverPos;//当前段解析的插值后点数
#else
	long nCurIntervalRemainPts = m_nInsertTotalPoints - m_nCurIntervalDeliverPos;//当前段解析的插值后点数
#endif

	BOOL bRet = FALSE;
	long nCurFillPoints = 0;

	if (nCurIntervalRemainPts >= nABBuffRemainPts)
	{
		nCurFillPoints = nABBuffRemainPts;
		bRet = TRUE;
	} 
	else//如果ReplayBuf里面的剩余总点数小于放满pABBuf需要的总点数,则将剩余点数全部放入pABBuf,并改变ReplayBuf中的m_nDataFillBeginPos位置，返回FALSE
	{
		nCurFillPoints = nCurIntervalRemainPts;
		bRet = FALSE;
	}
	
	ASSERT(nChs>0);
	float** ppChValue = new float*[nChs];
	long nChIndex = 0;
	m_pComtradePlayConfigRef->GetTotalChs_SelectedModule(&ppChValue);

	static double fPreVal = ppChValue[0][0];
	CString strTemp = _T("");

	for (int nPtIndex = 0;nPtIndex<nCurFillPoints;nPtIndex++)
	{
		for (nChIndex = 0;nChIndex<nChs;nChIndex++)
		{
			if (nChIndex == 0)
			{
// 				if (fabs(ppChValue[nChIndex][m_nCurIntervalDeliverPos+nPtIndex]-fPreVal) > 5)
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("_______Test delta>5:pre[%.3f],cur[%.3f]"),fPreVal,ppChValue[nChIndex][m_nCurIntervalDeliverPos+nPtIndex]);
// 				}
				fPreVal = ppChValue[nChIndex][m_nCurIntervalDeliverPos+nPtIndex];

				strTemp.AppendFormat(_T("%.3f\r\n"),ppChValue[nChIndex][m_nCurIntervalDeliverPos+nPtIndex]);
			}

			if (ppChValue[nChIndex] != NULL)
			{
				pABBuf->WriteData(ppChValue[nChIndex][m_nCurIntervalDeliverPos+nPtIndex]);
			}
			else
			{
				pABBuf->WriteData(0);
			}
		}
	}

// #ifdef _Stt_Cmtrd_Save_File_
// //	static int nSaveCnt = 0;
// 	m_oCmtrdSaveFile.Write(strTemp.GetString(),strTemp.GetLength());
// //	nSaveCnt++;
// 
// // 	if (nSaveCnt > 3)
// // 	{
// // 		CloseCmtrdSaveFile();
// // 	}
// #endif

	m_nCurIntervalDeliverPos += nCurFillPoints;
	delete ppChValue;
	return bRet;
#else
	return 0;
#endif
}

//原始数据、回放数据清空
void CBigComtradeFileRead::ResetDataBuf()
{
// #ifdef _PSX_IDE_QT_
// 	if (m_oFileRead.handle() != (int)INVALID_HANDLE_VALUE)
// #else
// 	if (m_oFileRead.m_hFile != INVALID_HANDLE_VALUE)
// #endif
// 	{
// 		m_oFileRead.SeekToBegin();
// 	}

	m_nReadBufDataLen = 0;
//	m_nReadBufReadPos = 0;
	m_bReadFileFinish = FALSE;
	m_bAnalysisFinish = FALSE;
	m_fReplayStartTime = 0;
	m_fRawStartTime = 0;
	m_oSrcComtradeFile.ResetDataBuffer();

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	if (m_pComtradePlayConfigRef != NULL)
	{
		m_pComtradePlayConfigRef->ResetReplayBuf();
	}
#endif
}

void CBigComtradeFileRead::ClearTotalBuff()
{
	if (m_pFileReadBuffer != NULL)
	{
		delete m_pFileReadBuffer;
		m_pFileReadBuffer = NULL;
	}

	if (m_pdSamRate != NULL)
	{
		delete m_pdSamRate;
		m_pdSamRate = NULL;
	}

	if (m_pnDataPoints != NULL)
	{
		delete m_pnDataPoints;
		m_pnDataPoints = NULL;
	}

#ifdef USE_InsertComtradeFile_Mode
	if (m_pInsertComtradeFile != NULL)
	{
		delete m_pInsertComtradeFile;
		m_pInsertComtradeFile = NULL;
	}
#else
	m_nInsertTotalPoints = 0;
	m_dInsertOffsetTime = 0;
#endif
}

//定位文件，一次性填充LoopBuf数据
BOOL CBigComtradeFileRead::GenerateLoopBuf()
{
	CComtradeDataBuffer *pLoopBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(0);
	pLoopBuf->ResetWritePos();

	//第一步：根据配置参数，定位文件读数据，并解析到AnalogData中
//	ReadLoopRawDataFile();

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	long nChs = m_pComtradePlayConfigRef->GetTotalChs_SelectedModule();
	ASSERT(nChs>0);
	float** ppChValue = new float*[nChs];
	long nTotalPoints = m_dInsertFreq/m_oSrcComtradeFile.m_dFreq;
	long nChIndex = 0;
	 m_pComtradePlayConfigRef->GetTotalChs_SelectedModule(&ppChValue);

	for (int nPtIndex = 0;nPtIndex<nTotalPoints;nPtIndex++)
	{
		for (nChIndex = 0;nChIndex<nChs;nChIndex++)
		{
			if (ppChValue[nChIndex] != NULL)
			{
				pLoopBuf->WriteData(ppChValue[nChIndex][nPtIndex]);
			}
			else
			{
				pLoopBuf->WriteData(0);
			}
		}
	}
	
//	pLoopBuf->BufferDatas_WriteFile();//20220519 将第一个周波数据写入文件 
	delete ppChValue;
#endif

// 	BOOL bExitFlag = FALSE;
// 	while(TRUE)
// 	{
// 		//第一步：由ReplayBuf数据填充满LoopBuf
// 		if (GenerateABBufFromReplayBuf(pLoopBuf))
// 		{
// 			break;
// 		}
// 
// 		//说明LoopBuf未填满，ReplayBuf空了
// 		if (bExitFlag)
// 		{
// 			break;
// 		}
// 
// 		while(TRUE)
// 		{
// 			//第二步：由AnalogData原始数据填充满ReplayBuf
// 			if (GenerateReplayBufFromRawData(FALSE))
// 			{
// 				break;
// 			}
// 
// 			//说明ReplayBuf未填满，AnalogData空了
// 			bExitFlag = TRUE;
// 			break;
// 		}
// 	}
// 
// 	//第四步：清除缓存
// 	ResetDataBuf();
	
	pLoopBuf->SetRWState(COMTRADE_DATABUF_MODE_READ);

	return TRUE;
}

//填充ABBuf数据
BOOL CBigComtradeFileRead::GenerateABBuf(int nIndex)
{
	CComtradeDataBuffer *pABBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nIndex);
	pABBuf->ResetWritePos();

	while(TRUE)
	{
		//第一步：由ReplayBuf原始数据填充满pABBuf
		if(GenerateABBufFromReplayBuf(pABBuf))
		{//说明完成或最后数据
			break;
		}

		//说明pABBuf未填满，ReplayBuf空了
		if (m_bReadFileFinish)
		{
			m_bAnalysisFinish = TRUE;
			break;
		}

#ifndef USE_Debug_BIG_ComtradeRead_Mode
		GenerateComtradeChDataFromDataFile(FALSE);
		GenerateReplayBufFromRawData(/*FALSE*/);
		m_pComtradePlayConfigRef->CalcReplayChMaxValue();

// 		while(TRUE)
// 		{
// 			//第二步：由原始数据AnalogData生成ReplayBuf，更新回放起始时间
// 			if (GenerateReplayBufFromRawData(/*FALSE*/))
// 			{
// 				//说明ReplayBuf已填满，需重新计算UI最大值,通知界面刷新回放波形
// 				m_pComtradePlayConfigRef->CalcReplayChMaxValue();
// 				break;
// 			}
// 
// 			//说明ReplayBuf未填满，AnalogData空了
// 			if (m_bReadFileFinish)
// 			{
// 				//说明ReplayBuf未填满，且最后一帧，需重新计算UI最大值,通知界面刷新回放波形
// 				m_pComtradePlayConfigRef->CalcReplayChMaxValue();
// 				break;
// 			}
// 
// 			//第三步：由读文件生成AnalogData，更新原始波形起始时间
// 			GenerateComtradeChDataFromDataFile(FALSE);
// 
// 			//说明AnalogData已填满或最后一帧，通知界面刷新原始波形
// 		}
#endif
	}

	pABBuf->SetRWState(COMTRADE_DATABUF_MODE_READ);

	return TRUE;
}

//开始测试之前，初始化Loop\A\B缓存
void CBigComtradeFileRead::BeginGenerateComtradeBuf(BOOL bResetCoef)
{
	//清除缓存
	ResetDataBuf();
	//文件重新定位
//	m_oFileRead.SeekToBegin();

	//每次开始测试前，重新从文件头开始读数据
	GenerateComtradeChDataFromDataFile(TRUE,bResetCoef);
	GenerateReplayBufFromRawData(/*FALSE*/);
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	m_pComtradePlayConfigRef->CalcReplayChMaxValue();

	if (m_pComtradePlayConfigRef->HasLoopData())
	{
		GenerateLoopBuf();
	}
#endif

	//填充A缓存
	GenerateABBuf(1);

	if (!m_bAnalysisFinish)
	{
		//填充B缓存
		GenerateABBuf(2);
	}
}

BOOL CBigComtradeFileRead::InsertCyclePointsByRelTime(double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex)
{
	// 确保开始和结束时间在合理范围内
	if (dBeginTime < 0 || dEndTime > m_pInsertComtradeFile->CalComtradeFileSumTime() || dBeginTime > dEndTime)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("插入时间不符合合理时间段，请重新检查后再次输入！"));

		return FALSE;
	}

	m_oSrcComtradeFile.InsertCyclePointsByRelTime(dBeginTime, dEndTime, dInsertTime, nCycleIndex);
	m_nCurSrcIntervalPoints = m_oSrcComtradeFile.m_nTotalPoints;
	m_nTotalPointsNum = m_oSrcComtradeFile.m_nTotalPoints;
	SetBigFileTotalSmpRates();

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq);
	GenerateReplayBufFromRawData();

// 	while(m_bReadFileFinish)
// 	{
// 		CString strWaveDataFile = _P_GetConfigPath();
// 		strWaveDataFile += _T("temp_WaveformData");
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("wuwuwu--- strWaveDataFile += temp_WaveformData::g_theplay : %d"), this);
// 		m_oSrcComtradeFile.SaveComtradeFile(strWaveDataFile);
// 		break;
// 	}
	return TRUE;
}

BOOL CBigComtradeFileRead::InsertCyclePointsByPoint( long nBeginPoint, long nEndPoint, long nInserPoint, int nCycleIndex )
{
	// 确保开始和结束时间在合理范围内
	if (nBeginPoint < 0 || nEndPoint > m_nTotalPointsNum || nBeginPoint > nEndPoint)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("插入时间不符合合理时间段，请重新检查后再次输入！"));

		return FALSE;
	}

	m_oSrcComtradeFile.InsertCyclePointsByPoint(nBeginPoint, nEndPoint, nInserPoint, nCycleIndex);
	m_nCurSrcIntervalPoints = m_oSrcComtradeFile.m_nTotalPoints;
	m_nTotalPointsNum = m_oSrcComtradeFile.m_nTotalPoints;
	SetBigFileTotalSmpRates();

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq);
	GenerateReplayBufFromRawData();

// 	while(m_bReadFileFinish)
// 	{
// 		CString strWaveDataFile = _P_GetConfigPath();
// 		strWaveDataFile += _T("temp_WaveformData");
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("wuwuwu--- strWaveDataFile += temp_WaveformData::g_theplay : %d"), this);
// 		m_oSrcComtradeFile.SaveComtradeFile(strWaveDataFile);
// 		break;
// 	}
	return TRUE;
}

BOOL CBigComtradeFileRead::InsertNormalCyclePoints( double dVolValue,double dCurrentValue,double dTime_Second )
{
	if(dVolValue < 0 || dCurrentValue < 0 )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("输入的电压/电流不允许小于0，请重新修改！"));
		return FALSE;
	}
	else if(dTime_Second < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("输出时间不允许小于0，请重新修改！"));
		return FALSE;
	}
	if(!m_oSrcComtradeFile.InsertNormalCyclePoints(dVolValue,dCurrentValue,dTime_Second))
	{
		return FALSE;
	}
	m_nCurSrcIntervalPoints = m_oSrcComtradeFile.m_nTotalPoints;
	m_nTotalPointsNum = m_oSrcComtradeFile.m_nTotalPoints;
	SetBigFileTotalSmpRates();

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq);
	GenerateReplayBufFromRawData();

// 	while(m_bReadFileFinish)
// 	{
// 		CString strWaveDataFile = _P_GetConfigPath();
// 		strWaveDataFile += _T("temp_WaveformData");
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("wuwuwu--- strWaveDataFile += temp_WaveformData::g_theplay : %d"), this);
// 		m_oSrcComtradeFile.SaveComtradeFile(strWaveDataFile);
// 		break;
// 	}

	return TRUE;


}


BOOL CBigComtradeFileRead::DeletePointsByRelTime(double dBeginTime, double dEndTime )
{
	// 确保开始和结束时间在合理范围内
	if (dBeginTime < 0  || dBeginTime > dEndTime)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("删除时间不符合合理时间段，请重新检查后再次输入！"));
		return FALSE;
	}
	else if(dEndTime > m_pInsertComtradeFile->CalComtradeFileSumTime() || dBeginTime > m_pInsertComtradeFile->CalComtradeFileSumTime() )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("删除/插入的时间点超过波形总时间段，请重新检查后再次输入！"));
		return FALSE;
	}
	m_oSrcComtradeFile.DeletePointsByRelTime(dBeginTime, dEndTime);
	m_nCurSrcIntervalPoints = m_oSrcComtradeFile.m_nTotalPoints;

	m_nTotalPointsNum = m_oSrcComtradeFile.m_nTotalPoints;
	SetBigFileTotalSmpRates();

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq);
	GenerateReplayBufFromRawData();

	//2024-1-24 wuxinyi 保存文件
// 	while(m_bReadFileFinish)
// 	{
// 		CString strWaveDataFile = _P_GetConfigPath();
// 		strWaveDataFile += _T("temp_WaveformData");
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("wuwuwu--- strWaveDataFile += temp_WaveformData::g_theplay : %d"), this);
// 		m_oSrcComtradeFile.SaveComtradeFile(strWaveDataFile);
// 		break;
// 	}

	return TRUE;
}


#ifndef USE_Debug_BIG_ComtradeRead_Mode
//界面(A-B)/K和是否勾选改变，对应ReplayBuf也要更新，更新完再重新计算最大值，更新最大值
BOOL CBigComtradeFileRead::UpdateChReplayBuf(CSttModuleChComtradeBind *pCh, CSttModuleComtradeBind *pModule, BOOL bSave)
{//ReplayBuf缓存填充满返回TRUE,AnalogData解析完而ReplayBuf缓存未填满返回FALSE
#ifdef USE_InsertComtradeFile_Mode
	ASSERT(m_pInsertComtradeFile);
//	ASSERT(pCh->GetMaxPoints()>0);
	//获取当前通道ReplayBuff大小，如果小于插值后波形点数的大小，则重新初始化
	if (pCh->GetMaxPoints()<m_pInsertComtradeFile->m_nTotalPoints)
	{
		pCh->InitChReplayBuf(m_pInsertComtradeFile->m_nTotalPoints + 5);//多预留5个点，避免频繁重新初始化缓存
	}

	//zhouhj 2023.9.11 此处获取对应的通道,直接使用对应的指针,不再通过nIndexChA获取
// 	long nIndexChA = pCh->GetValue_DataA();
// 	long nIndexChB = pCh->GetValue_DataB();
	double dCoefK = pCh->GetValue_DataK();
	double dRatio = 1;
	double dChA_UnitRadio = 1;
	double dChB_UnitRadio = 1;

	CComtradeAnalogData *pAnalogDataA_Src =pCh->m_pCh_A;
	CComtradeAnalogData *pAnalogDataB_Src = pCh->m_pCh_B;
	CComtradeAnalogData *pAnalogDataA = NULL;
	CComtradeAnalogData *pAnalogDataB = NULL;

	if (pAnalogDataA_Src != NULL)
	{
		pAnalogDataA = m_pInsertComtradeFile->FindAnalogDataByChID(pAnalogDataA_Src->m_strID);
	}

	if (pAnalogDataB_Src != NULL)
	{
		pAnalogDataB = m_pInsertComtradeFile->FindAnalogDataByChID(pAnalogDataB_Src->m_strID);
	}

// 	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind *)pCh->GetParent();

// 	if(pCh->m_strID.Find(_T("Digital")) != 0)//数字量无法设置CT、PT变比
// 	{
		if(pModule->IsAnalogTypeModule())
	{
			if (pCh->IsModuleType_U())
			{
					// 		pAnalogDataA = m_pInsertComtradeFile->GetAnalogDataByChIndex(nIndexChA,TRUE);
					// 		pAnalogDataB = m_pInsertComtradeFile->GetAnalogDataByChIndex(nIndexChB,TRUE);
		dRatio = m_pComtradePlayConfigRef->m_fPTRatio[1]/m_pComtradePlayConfigRef->m_fPTRatio[0];
	} 
	else
	{
					// 		pAnalogDataA = m_pInsertComtradeFile->GetAnalogDataByChIndex(nIndexChA,FALSE);
					// 		pAnalogDataB = m_pInsertComtradeFile->GetAnalogDataByChIndex(nIndexChB,FALSE);
		dRatio = m_pComtradePlayConfigRef->m_fCTRatio[1]/m_pComtradePlayConfigRef->m_fCTRatio[0];
	}
		}
		else if(pModule->IsWeekTypeModule())
		{
			int nWeekChType = pCh->GetEleTypeIndex();
			if (nWeekChType == 0/*REPLAY_WEEK_CH_ELETYPE_VOL*/)
			{
				dRatio = pModule->m_fPTRatio[1]/pModule->m_fPTRatio[0];
			} 
			else
			{
				dRatio = pModule->m_fCTRatio[1]/pModule->m_fCTRatio[0];
			}
		}

// 	}

// 	if ((pAnalogDataA == NULL)&&(pAnalogDataB == NULL))//如果A、B都未设置，则直接返回
// 	{
// 		return FALSE;
// 	}

	if (pAnalogDataA != NULL)
	{
		dChA_UnitRadio = pAnalogDataA->GetUnitRadio();
	}

	if (pAnalogDataB != NULL)
	{
		dChB_UnitRadio = pAnalogDataB->GetUnitRadio();
	}

	float* pdDataA = pCh->m_pReplayBuf->GetBuffer_float();

	for (long nPtIndex = 0;nPtIndex<m_pInsertComtradeFile->m_nTotalPoints;nPtIndex++)
	{
		if ((pCh->m_nChSelected == 0)||((pAnalogDataA == NULL)&&(pAnalogDataB == NULL)))//zhouhj 20211105 如果未选择或者通道A\B都为空,则输出为0
		{
			pdDataA[nPtIndex] = 0;
			continue;
		}

		if (pAnalogDataA != NULL && pAnalogDataB != NULL)
		{
			pdDataA[nPtIndex] = dRatio*(dChA_UnitRadio*pAnalogDataA->GetUShortPointValueDouble(nPtIndex)-dChB_UnitRadio*pAnalogDataB->GetUShortPointValueDouble(nPtIndex))/dCoefK;
		}
		else
		{
			if (pAnalogDataA != NULL)
			{
				pdDataA[nPtIndex] = dChA_UnitRadio*dRatio*pAnalogDataA->GetUShortPointValueDouble(nPtIndex)/dCoefK;
			}
			else// if (pAnalogDataB != NULL)
			{
				pdDataA[nPtIndex] = -dChB_UnitRadio*dRatio*pAnalogDataB->GetUShortPointValueDouble(nPtIndex)/dCoefK;
			}
		}
	}

	pCh->m_pReplayBuf->SetDataLength(m_pInsertComtradeFile->m_nTotalPoints);

// #ifdef _Stt_Cmtrd_Save_File_
// 	if (bSave)
// 	{
// #ifdef _PSX_IDE_QT_
// 		if (m_oCmtrdSaveFile.handle() != (int)INVALID_HANDLE_VALUE)
// #else
// 		if (m_oCmtrdSaveFile.m_hFile != INVALID_HANDLE_VALUE)
// #endif
// 		{
// //			static int nSaveCnt = 0;
// 
// 			pAnalogDataA = m_pInsertComtradeFile->GetAnalogDataByChIndex(nIndexChA,TRUE);
// 		
// 
// 			int nTotalCnt = pAnalogDataA->m_nTotalPoints;
// 	//		int nTotalCnt = m_pInsertComtradeFile->m_nTotalPoints;
// 			CString strTemp;
// 			int nWritePos = 0;
// 			int nOnceWrite = 1000;
// 			double*  pTemp = (double*)pCh->m_pReplayBuf->GetBuffer();
// 			while (nTotalCnt > nWritePos)
// 			{
// 				strTemp = _T("");
// 				nOnceWrite = min(1000,nTotalCnt-nWritePos);
// 				for (int i=0; i<nOnceWrite; i++)
// 				{
// 					strTemp.AppendFormat(_T("%d\r\n"),(short)pAnalogDataA->m_pnAttachBuffer[nWritePos+i]);
// 	//				strTemp.AppendFormat(_T("%.3f ; %d\r\n"),pTemp[nWritePos+i],pAnalogDataA->m_pnAttachBuffer[nWritePos+i]);
// 				}
// 				m_oCmtrdSaveFile.Write(strTemp.GetString(),strTemp.GetLength());
// 				nWritePos += nOnceWrite;
// 			}
// 
// //			nSaveCnt++;
// // 			if (nSaveCnt > 100)
// // 			{
// // 				CloseCmtrdSaveFile();
// // 			}
// 		}
// 		
// 	}		
// #endif

#else
	ASSERT(m_nInsertTotalPoints>0);
	//获取当前通道ReplayBuff大小，如果小于插值后波形点数的大小，则重新初始化
	if (pCh->GetMaxPoints()<m_nInsertTotalPoints)
	{
		pCh->InitChReplayBuf(m_nInsertTotalPoints + 5);//多预留5个点，避免频繁重新初始化缓存
	}

	long nIndexChA = pCh->GetValue_DataA();
	long nIndexChB = pCh->GetValue_DataB();
	double dCoefK = pCh->GetValue_DataK();
	double dRatio = 1;
	double dChA_UnitRadio = 1;
	double dChB_UnitRadio = 1;

	CComtradeAnalogData *pAnalogDataA =NULL;
	CComtradeAnalogData *pAnalogDataB = NULL;
	CMemBuffer_Double oDoubleBuffA;
	CMemBuffer_Double oDoubleBuffB;
	double *pdDataA = NULL;
	double *pdDataB = NULL;
	long nCh_Points = 0;

	if (pCh->m_strID.Find(_T("U")) == 0)
	{
		pAnalogDataA = m_oSrcComtradeFile.GetAnalogDataByChIndex(nIndexChA,TRUE);
		pAnalogDataB = m_oSrcComtradeFile.GetAnalogDataByChIndex(nIndexChB,TRUE);
		dRatio = m_pComtradePlayConfigRef->m_fPTRatio[1]/m_pComtradePlayConfigRef->m_fPTRatio[0];
	} 
	else
	{
		pAnalogDataA = m_oSrcComtradeFile.GetAnalogDataByChIndex(nIndexChA,FALSE);
		pAnalogDataB = m_oSrcComtradeFile.GetAnalogDataByChIndex(nIndexChB,FALSE);
		dRatio = m_pComtradePlayConfigRef->m_fCTRatio[1]/m_pComtradePlayConfigRef->m_fCTRatio[0];
	}

	if ((pAnalogDataA == NULL)&&(pAnalogDataB == NULL))//如果A、B都未设置，则直接返回
	{
		return FALSE;
	}

	if (pAnalogDataA != NULL)
	{
		dChA_UnitRadio = pAnalogDataA->GetUnitRadio();
		oDoubleBuffA.SetBufferLength(m_nInsertTotalPoints + 5);
		nCh_Points = pAnalogDataA->InsertBySampleRate_DoubleBuff(oDoubleBuffA,m_oSrcComtradeFile.m_pdSamRate,m_oSrcComtradeFile.m_pnDataPoints,
			m_oSrcComtradeFile.m_nSamAmount,m_dInsertFreq,m_dInsertOffsetTime);
		pdDataA = oDoubleBuffA.GetBuffer();
		ASSERT(m_nInsertTotalPoints>=nCh_Points);

// 		if (bSave)
// 		{
// 			oDoubleBuffA.WriteLogTxt();
// 		}
	}

	if (pAnalogDataB != NULL)
	{
		dChB_UnitRadio = pAnalogDataB->GetUnitRadio();
		oDoubleBuffB.SetBufferLength(m_nInsertTotalPoints + 5);
		nCh_Points = pAnalogDataB->InsertBySampleRate_DoubleBuff(oDoubleBuffB,m_oSrcComtradeFile.m_pdSamRate,m_oSrcComtradeFile.m_pnDataPoints,
			m_oSrcComtradeFile.m_nSamAmount,m_dInsertFreq,m_dInsertOffsetTime);
		pdDataB = oDoubleBuffB.GetBuffer();
		ASSERT(m_nInsertTotalPoints>=nCh_Points);
	}

	double* pdData = pCh->m_pReplayBuf->GetBuffer();

	for (long nPtIndex = 0;nPtIndex<m_nInsertTotalPoints;nPtIndex++)
	{
		if (pAnalogDataA == NULL)
		{
			pdData[nPtIndex] = -dChB_UnitRadio*dRatio*pdDataB[nPtIndex]/dCoefK;
		}
		else if (pAnalogDataB == NULL)
		{
			pdData[nPtIndex] = dChA_UnitRadio*dRatio*pdDataA[nPtIndex]/dCoefK;
		}
		else
		{
			pdData[nPtIndex] = dRatio*(dChA_UnitRadio*pdDataA[nPtIndex]-dChB_UnitRadio*pdDataB[nPtIndex])/dCoefK;
		}
	}

	pCh->m_pReplayBuf->SetDataLength(m_nInsertTotalPoints);
#endif

	return (!m_bReadFileFinish);//如果文件解析完了，则缓存未满，如果文件未解析完，则缓存填满
}

//界面(A-B)/K和是否勾选改变，对应ReplayBuf也要更新，更新完再重新计算最大值，更新最大值
BOOL CBigComtradeFileRead::UpdateChReplayBuf(int nModuleIndex,int nChIndex/*,BOOL bFromStart*/)
{//ReplayBuf缓存填充满返回TRUE,AnalogData解析完而ReplayBuf缓存未填满返回FALSE
	ASSERT((nModuleIndex >= 0) && (nChIndex>= 0));

	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetAt(nModuleIndex);
	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)pModule->GetAt(nChIndex);

	//根据配置信息，定位到AB通道选择，K,重新有AnalogData生成指定pCh->ReplayBuf
	return UpdateChReplayBuf(pCh, pModule/*,bFromStart*/);
}
#endif

BOOL CBigComtradeFileRead::UpdateBinaryChReplayBuf( CSttModuleComtradeBind *pModule )
{
	if(!m_pInsertComtradeFile || !pModule)
	{
		return FALSE;
	}

	CComplexMemBuffer_Float* pReplayBufBinary1 = pModule->m_pReplayBufBinary1; // 低位
	CComplexMemBuffer_Float* pReplayBufBinary2 = pModule->m_pReplayBufBinary2; // 高位

	if (pReplayBufBinary1 == NULL || pReplayBufBinary2 == NULL)
	{
		return FALSE;
	}

	long* pdData1 = (long *)pReplayBufBinary1->GetBuffer_float();
	long* pdData2 = (long *)pReplayBufBinary2->GetBuffer_float();

	int nTotalPoints = m_pInsertComtradeFile->m_nTotalPoints;

	memset(pdData1, 0, nTotalPoints * sizeof(long));
	memset(pdData2, 0, nTotalPoints * sizeof(long));

	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;

	for (int nPtIndex = 0; nPtIndex < nTotalPoints; ++nPtIndex)
	{
#ifdef _PSX_IDE_QT_
			quint64  nBoutData = 0;	
			quint64 nChIndex = 0;
#else	
			ULONGLONG  nBoutData = 0;	
			ULONGLONG  nChIndex = 0;	
#endif
		
		POS pos = pModule->GetHeadPosition();
		while(pos)
		{
			pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(pos);
			if(pBinaryCh->m_nChState == 1)
			{
				//当前每个点数的开出量位置的全部置为1
				nBoutData |= (1ULL << nChIndex);
			}
			else
			{
				if(pBinaryCh->m_nBinaryCh_Index != 0)
				{
// 					CComtradeBinaryData * pSelectData = m_pInsertComtradeFile->FindBinaryDataByChID(pBinaryCh->m_strComtradeBinaryCh);
					CComtradeBinaryData * pSelectData_Src = pBinaryCh->m_pBinaryCh;
					CComtradeBinaryData * pSelectData = NULL;
// 					CComtradeBinaryData * pSelectData = pBinaryCh->m_pBinaryCh;
					if(pSelectData_Src != NULL)
					{
						pSelectData = m_pInsertComtradeFile->FindBinaryDataByChID(pSelectData_Src->m_strID);
					}
					if(!pSelectData)
					{
// 						CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前映射通道【%s】未找到！"),pBinaryCh->m_strComtradeBinaryCh);
						nBoutData &= ~(1ULL << nChIndex);//置为0
					}
					else
					{
						unsigned short* pBuffer = (unsigned short*)pSelectData->GetBuffer();
						if(pBuffer)
						{
// 							int nBufferIndex = (pBinaryCh->m_nBinaryCh_Index) /16;
							long nBitValue = pBuffer[nPtIndex] >> pSelectData->m_nDataIndex & 0x01;
							nBoutData |= (nBitValue ? 1ULL << nChIndex : 0ULL);
						}
						else
						{
							nBoutData &= ~(1ULL << nChIndex);//置为0
						}
					}
				}
				else
				{
					nBoutData &= ~(1ULL << nChIndex);//置为0
				}
			}
			++nChIndex;
		}
	
		while (nChIndex < 64)
		{
			nBoutData &= ~(1ULL << nChIndex);//置为0
			++nChIndex;
		}

		// 将二进制数据存入对应的回放缓存位置
		if (pdData1 != NULL)
		{
			pdData1[nPtIndex] = (long)(nBoutData & 0xFFFFFFFF); // 低 32 位
		}
		if (pdData2 != NULL)
		{
			pdData2[nPtIndex] = (long)((nBoutData >> 32) & 0xFFFFFFFF); // 高 32 位
		}
	}

	// 设置回放缓存的数据长度
	pReplayBufBinary1->SetDataLength(nTotalPoints);
	pReplayBufBinary2->SetDataLength(nTotalPoints);

	return TRUE;
}

void CBigComtradeFileRead::SetBigFileTotalSmpRates()
{
	if (m_pnDataPoints != NULL)
	{
		delete m_pnDataPoints;
	}

	if (m_pdSamRate != NULL)
	{
		delete m_pdSamRate;
	}

	m_nSamAmount = m_oSrcComtradeFile.m_nSamAmount;
	m_pnDataPoints = new long[m_nSamAmount];
	m_pdSamRate    = new float[m_nSamAmount];

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		m_pnDataPoints[nIndex] = m_oSrcComtradeFile.m_pnDataPoints[nIndex];
		m_pdSamRate[nIndex] = m_oSrcComtradeFile.m_pdSamRate[nIndex];
	}
}

void CBigComtradeFileRead::SetCurIntervalSmpRates()
{
	long nSmpRatesNum = 0;
	long nCurSmpRateBeginPt = 0;
	long nCurSmpRateEndPt = 0;
	const long nCurTntervalEndPt = m_nCurSrcBeginPointIndex + m_nCurSrcIntervalPoints - 1;
	BOOL bFirstPt = TRUE;

	//在该循环中获取需要用到的总的采样率数量
	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)
		{
			continue;
		}

		nCurSmpRateBeginPt = nCurSmpRateEndPt;

		if (bFirstPt)
		{
			nCurSmpRateEndPt = (m_pnDataPoints[nIndex]-1);
			bFirstPt = FALSE;
		} 
		else
		{
			nCurSmpRateEndPt += m_pnDataPoints[nIndex];
		}
		
		//只要保证当前解析段的开始点在当前采样率结束点的前面，并且当前解析段结束点在当前采样率的开始点之后，说明在范围内
		if ((m_nCurSrcBeginPointIndex<nCurSmpRateEndPt)&&(nCurTntervalEndPt>nCurSmpRateBeginPt))
		{
			nSmpRatesNum++;
		}
	}

	m_oSrcComtradeFile.SetSamAmount(nSmpRatesNum);
	long nCurIntervalIndex = 0;
	nCurSmpRateEndPt = 0;
	long nOffset = 1;
	bFirstPt = TRUE;

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)
		{
			continue;
		}

		nCurSmpRateBeginPt = nCurSmpRateEndPt;

		if (bFirstPt)
		{
			nCurSmpRateEndPt = (m_pnDataPoints[nIndex]-1);
			bFirstPt = FALSE;
		} 
		else
		{
			nCurSmpRateEndPt += m_pnDataPoints[nIndex];
		}

		//只要保证当前解析段的开始点在当前采样率结束点的前面，并且当前解析段结束点在当前采样率的开始点之后，说明在范围内
		if ((m_nCurSrcBeginPointIndex<nCurSmpRateEndPt)&&(nCurTntervalEndPt>nCurSmpRateBeginPt))
		{
			if (nCurIntervalIndex == 0)//对于第一段采样频率下的总点数需要加上第一个点，第二个以后的采样频率 其第一个点为上一个采样频率的最后一个点
			{
				nOffset = 1;
			} 
			else
			{
				nOffset = 0;
			}

			m_oSrcComtradeFile.m_pdSamRate[nCurIntervalIndex] = m_pdSamRate[nIndex];

			if ((m_nCurSrcBeginPointIndex>nCurSmpRateBeginPt)&&(nCurTntervalEndPt<nCurSmpRateEndPt))
			{
				m_oSrcComtradeFile.m_pnDataPoints[nCurIntervalIndex] = (nCurTntervalEndPt-m_nCurSrcBeginPointIndex + nOffset);
			}
			else if ((m_nCurSrcBeginPointIndex>nCurSmpRateBeginPt)&&(nCurTntervalEndPt>=nCurSmpRateEndPt))
			{
				m_oSrcComtradeFile.m_pnDataPoints[nCurIntervalIndex] = (nCurSmpRateEndPt-m_nCurSrcBeginPointIndex + nOffset);
			}
			else if (nCurTntervalEndPt<nCurSmpRateEndPt)
			{
				m_oSrcComtradeFile.m_pnDataPoints[nCurIntervalIndex] = (nCurTntervalEndPt-nCurSmpRateBeginPt + nOffset);
			}
			else
			{
				m_oSrcComtradeFile.m_pnDataPoints[nCurIntervalIndex] = nCurSmpRateEndPt - nCurSmpRateBeginPt + nOffset;
			}

			nCurIntervalIndex++;
		}
	}

	m_oSrcComtradeFile.UpdateSmpRatesList();
}

BOOL CBigComtradeFileRead::ReadBigDataAsASIIMode(const CString& strComtradeFile)
{
	CString strTemp = CString(m_oSrcComtradeFile.g_pszKeyDat);
	CString strDatFilePath = ChangeFilePostfix(strComtradeFile, strTemp);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strDatFilePath))
	{
		strTemp = _T("dat");
		strDatFilePath = ChangeFilePostfix(strComtradeFile, strTemp);
		if(!IsFileExist(strDatFilePath))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("打开dat文件(%s)失败."), strDatFilePath.GetString());

			return FALSE;
		}
	}
#endif

	CloseReadFile();
	ResetDataBuf();

	if (!m_oASII_ModeBuffer.ReadFromFile(strDatFilePath))
	{
		return FALSE;
	}

	m_oASII_ModeBuffer.FormatBuffer('\r');
	m_oASII_ModeBuffer.FormatBuffer('\n');
	m_nReadBufDataLen = 0;
	m_nTotalPointsNum = m_oSrcComtradeFile.GetTotalPoints();
	m_nCurSrcBeginPointIndex = 0;
	m_nCurInsertBeginPointIndex = 0;
	m_nCurSrcIntervalPoints = 0;
	char *sString = NULL;
	long nIndex = 0;

	for (nIndex = 0; nIndex < m_nTotalPointsNum; nIndex++)
	{
		sString = m_oASII_ModeBuffer.GetString();

		if (!m_oASII_ModeBuffer.IsPoiterInBuffer(sString))
		{
			break;
		}

		sString = m_oASII_ModeBuffer.NextString();
	}

	if (nIndex<m_nTotalPointsNum)
	{
		CString strSmpRateString;
		m_oSrcComtradeFile.GetSmpRateString(strSmpRateString);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前CFG文件中标识的总点数%ld(%s),与DAT文件中实际总点数%ld不一致,请修改CFG文件."), m_nTotalPointsNum,strSmpRateString.GetString(), nIndex);
		m_nTotalPointsNum = nIndex;
	}

	m_oASII_ModeBuffer.ResetPointer();
	GenerateComtradeChDataFromDataFile(TRUE,FALSE);
	return TRUE;
}

BOOL CBigComtradeFileRead::ReadBigDataAsBINARYMode(const CString& strComtradeFile)
{
	CString strTemp = CString(m_oSrcComtradeFile.g_pszKeyDat);
	CString strDatFilePath = ChangeFilePostfix(strComtradeFile, strTemp);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strDatFilePath))
	{
		strTemp = _T("dat");
		strDatFilePath = ChangeFilePostfix(strComtradeFile, strTemp);
		if(!IsFileExist(strDatFilePath))
		{
			return FALSE;
		}
	}
#endif

	CloseReadFile();
	ResetDataBuf();

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strDatFilePath,&pOldTextCodec);//将编码变为utf-8
#endif

	if (!m_oFileRead.Open(strDatFilePath,CFile::modeRead))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("打开dat文件(%s)失败."), strDatFilePath.GetString());
		return FALSE;
	}

#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);
	system("sync");//20220616 写文件后需要同步
#endif

	m_nReadBufDataLen = 0;
	m_nTotalPointsNum = m_oSrcComtradeFile.GetTotalPoints();
	long nSinglePointLength = m_oSrcComtradeFile.GetBinarySinglePointLength();
	long nActTotalPointsNum = m_oFileRead.GetLength()/nSinglePointLength;

	if (nActTotalPointsNum<m_nTotalPointsNum)
	{
		CString strSmpRateString;
		m_oSrcComtradeFile.GetSmpRateString(strSmpRateString);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前CFG文件中标识的总点数%ld(%s),与DAT文件中的实际总点数%ld不一致,请修改CFG文件."), m_nTotalPointsNum,strSmpRateString.GetString(), nActTotalPointsNum);
		m_nTotalPointsNum = nActTotalPointsNum;

		if (nActTotalPointsNum == 0)
		{
			return FALSE;
		}
	}

	m_nCurSrcBeginPointIndex = 0;
	m_nCurInsertBeginPointIndex = 0;
	m_nCurSrcIntervalPoints = 0;
	GenerateComtradeChDataFromDataFile(TRUE,FALSE);
	return TRUE;
}

double CBigComtradeFileRead::CalInsertOffsetTime()
{
	double dSrcBeginTime = CalCurRawStartTime();
	double dInsertOffsetTime = ((m_nCurInsertBeginPointIndex/m_dInsertFreq) - dSrcBeginTime);
	return dInsertOffsetTime;
}

//从原始数据文件中读取原始数据
BOOL CBigComtradeFileRead::GenerateComtradeChDataFromDataFile(BOOL bSeekToBegin,BOOL bResetCoef)
{
	//2021-9-20  lijunqing
	BOOL bRet = FALSE;

	if (bResetCoef)
	{
		m_oSrcComtradeFile.ResetCoefZeroValue();//2023.5.19 zhouhj
	}

	if (m_bIsBinaryMode)
	{
		bRet = GenerateComtradeChDataFromDataFile_BinaryMode(bSeekToBegin);
	} 
	else
	{
		bRet = GenerateComtradeChDataFromDataFile_ASIIMode(bSeekToBegin);
	}
	
	//2021-9-20  lijunqing
	m_oSrcComtradeFile.	CalMinMaxValue();

	return bRet;
}

BOOL CBigComtradeFileRead::GenerateComtradeChDataFromDataFile_ASIIMode(BOOL bSeekToBegin)
{
	if (m_oASII_ModeBuffer.GetLength()<=0)
	{
		return FALSE;
	}

	if (bSeekToBegin
		&& (m_nCurSrcBeginPointIndex == 0) 
		&& (m_nCurSrcIntervalPoints > 0) 
#ifdef USE_InsertComtradeFile_Mode
		&& (m_pInsertComtradeFile != NULL))//如果之前解析过，插值之后的数据还在，并且开始点为0，则无需重新解析
#else
		&& (m_nInsertTotalPoints>0))//如果之前解析过，插值之后的数据还在，并且开始点为0，则无需重新解析
#endif
	{
		m_nCurIntervalDeliverPos = 0;
		m_nCurInsertBeginPointIndex = 0;

		if ((m_nCurSrcBeginPointIndex+m_nCurSrcIntervalPoints)>=m_nTotalPointsNum)
		{
			m_bReadFileFinish = TRUE;
		}

		return TRUE;
	}

	if (bSeekToBegin ||(m_nCurSrcIntervalPoints<=0))
	{
		m_nCurSrcBeginPointIndex = 0;
		m_nCurInsertBeginPointIndex = 0;
		m_nCurSrcIntervalPoints = 0;
		m_oASII_ModeBuffer.ResetPointer();
// 		m_oASII_ModeBuffer.FormatBuffer('\r');
// 		m_oASII_ModeBuffer.FormatBuffer('\n');
	}
	else
	{
		m_nCurSrcBeginPointIndex += (m_nCurSrcIntervalPoints-1);//源数据从从上一段的最后一个点开始

#ifdef USE_InsertComtradeFile_Mode
		m_nCurInsertBeginPointIndex += m_pInsertComtradeFile->m_nTotalPoints;//插值后数据从上一段依次往后，不能重复
#else
		m_nCurInsertBeginPointIndex += m_nInsertTotalPoints;//插值后数据从上一段依次往后，不能重复
#endif
	}

	double dInsertOffsetTime = CalInsertOffsetTime();
	long nCurReadPointsNum = GetCurReadComtradePointsNum(dInsertOffsetTime);
	long nCurTotalReadLength = m_oSrcComtradeFile.GetBinarySinglePointLength()*nCurReadPointsNum;

	if (m_nCurSrcBeginPointIndex == 0)
	{
		m_nCurSrcIntervalPoints = nCurReadPointsNum;//对于第一段，实际总点数为读取的总点数
	} 
	else//否则为实际总点数+1
	{
		m_nCurSrcIntervalPoints = nCurReadPointsNum+1;
	}

	m_oSrcComtradeFile.m_nTotalPoints = m_nCurSrcIntervalPoints;
	SetCurIntervalSmpRates();
	m_oSrcComtradeFile.BigComtrade_InitChsAllocBufferNext();
	unsigned short* pnBuffer = NULL;
	unsigned short* pnTemp = NULL;
	CComtradeDataBase* pObj = NULL;
	long nBinaryIndex = 0;
	long nAnalogIndex = 0;
	unsigned short* pBuffer = NULL;
	char *sString = NULL;
	long nIndex = 0;

	if (m_nCurSrcBeginPointIndex > 0)//如果不是第一段读取，第一个点为上一段的最后一个点
	{
		nIndex = 1;
	}

	for (; nIndex < m_nCurSrcIntervalPoints; nIndex++)
	{
		sString = m_oASII_ModeBuffer.GetString();

		if (!m_oASII_ModeBuffer.IsPoiterInBuffer(sString))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CFG文件中总点数与DADA文件中实际总点数不一致,当前段计划总点数%ld,实际文件中只包含总点数%ld."),m_nCurSrcIntervalPoints, (nIndex+1));
			m_nCurSrcIntervalPoints = nIndex;
			m_oSrcComtradeFile.m_nTotalPoints = m_nCurSrcIntervalPoints;
			m_nTotalPointsNum = m_nCurSrcBeginPointIndex + m_nCurSrcIntervalPoints;
			break;
		}

		m_oSrcComtradeFile.ReadDataAsASIIMode(sString,nIndex);
		sString = m_oASII_ModeBuffer.NextString();
	}

	m_oSrcComtradeFile.UpdateAllChsTotalPointsNum();
	InitSrcAnalogsBeginAng_SpecialSmpRate();

#ifdef USE_InsertComtradeFile_Mode
	if (m_pInsertComtradeFile != NULL)
	{
		delete m_pInsertComtradeFile;
	}

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq ,dInsertOffsetTime);
#else
	m_dInsertOffsetTime = dInsertOffsetTime;
	m_nInsertTotalPoints = m_oSrcComtradeFile.CalTotalPoints_InsertWithSingleSmpRate(m_dInsertFreq ,dInsertOffsetTime);
#endif
	m_nCurIntervalDeliverPos = 0;

	if ((m_nCurSrcBeginPointIndex+m_nCurSrcIntervalPoints)>=m_nTotalPointsNum)
	{
		m_bReadFileFinish = TRUE;
	}

	CComtradeAnalogData *pSaveCh = m_oSrcComtradeFile.GetAnalogDataByChIndex(1,TRUE);

	if (pSaveCh != NULL)
	{
		pSaveCh->WriteAnalogDatas(_T("Src"));
		pSaveCh = m_pInsertComtradeFile->GetAnalogDataByChIndex(1,TRUE);
		pSaveCh->WriteAnalogDatas(_T("Insert"));
	}

	return TRUE;
}

BOOL CBigComtradeFileRead::GenerateComtradeChDataFromDataFile_BinaryMode(BOOL bSeekToBegin)
{
#ifdef _PSX_IDE_QT_
	if (m_oFileRead.handle() == (int)INVALID_HANDLE_VALUE)
#else
	if (m_oFileRead.m_hFile == INVALID_HANDLE_VALUE)
#endif
	{
		return FALSE;
	}

	if (bSeekToBegin
		&& (m_nCurSrcBeginPointIndex == 0) 
		&& (m_nCurSrcIntervalPoints > 0) 
#ifdef USE_InsertComtradeFile_Mode
		&& (m_pInsertComtradeFile != NULL))//如果之前解析过，插值之后的数据还在，并且开始点为0，则无需重新解析
#else
		&& (m_nInsertTotalPoints>0))//如果之前解析过，插值之后的数据还在，并且开始点为0，则无需重新解析
#endif
	{
		m_nCurIntervalDeliverPos = 0;
		m_nCurInsertBeginPointIndex = 0;

		if ((m_nCurSrcBeginPointIndex+m_nCurSrcIntervalPoints)>=m_nTotalPointsNum)
		{
			m_bReadFileFinish = TRUE;
		}

		return TRUE;
	}

	if (bSeekToBegin ||(m_nCurSrcIntervalPoints<=0))
	{
		m_nCurSrcBeginPointIndex = 0;
		m_nCurInsertBeginPointIndex = 0;
		m_nCurSrcIntervalPoints = 0;
//		m_dInsertOffsetTime = 0;
		m_oFileRead.SeekToBegin();
	}
	else
	{
		m_nCurSrcBeginPointIndex += (m_nCurSrcIntervalPoints-1);//源数据从从上一段的最后一个点开始
#ifdef USE_InsertComtradeFile_Mode
		m_nCurInsertBeginPointIndex += m_pInsertComtradeFile->m_nTotalPoints;//插值后数据从上一段依次往后，不能重复
#else
		m_nCurInsertBeginPointIndex += m_nInsertTotalPoints;//插值后数据从上一段依次往后，不能重复
#endif
	}

	double dInsertOffsetTime = CalInsertOffsetTime();
	long nCurReadPointsNum = GetCurReadComtradePointsNum(dInsertOffsetTime);
	long nCurTotalReadLength = m_oSrcComtradeFile.GetBinarySinglePointLength()*nCurReadPointsNum;

	if (m_nCurSrcBeginPointIndex == 0)
	{
		m_nCurSrcIntervalPoints = nCurReadPointsNum;//对于第一段，实际总点数为读取的总点数
	} 
	else//否则为实际总点数+1
	{
		m_nCurSrcIntervalPoints = nCurReadPointsNum+1;
	}

	m_oSrcComtradeFile.m_nTotalPoints = m_nCurSrcIntervalPoints;
	SetCurIntervalSmpRates();
	m_oSrcComtradeFile.BigComtrade_InitChsAllocBufferNext();

	if (m_pFileReadBuffer == NULL)
	{
		m_nFileReadBufLen = CalSrcMaxSmpRateIntervalPoints()*m_oSrcComtradeFile.GetBinarySinglePointLength();

		if (m_nFileReadBufLen<nCurTotalReadLength)
		{
			m_nFileReadBufLen = nCurTotalReadLength;
		}

		m_pFileReadBuffer = new BYTE[m_nFileReadBufLen];
	}
	else if (nCurTotalReadLength>m_nFileReadBufLen)
	{
		delete m_pFileReadBuffer;
		m_nFileReadBufLen = nCurTotalReadLength;
		m_pFileReadBuffer = new BYTE[m_nFileReadBufLen];
	}

	memset(m_pFileReadBuffer,0,m_nFileReadBufLen);
	long nReadLenth = m_oFileRead.Read(m_pFileReadBuffer,nCurTotalReadLength);

	if (nReadLenth<0)
	{
		m_nReadBufDataLen = 0;
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("读取指定长度的大文件内容失败."));
		return FALSE;
	}
	else if (nReadLenth != nCurTotalReadLength)
	{
		m_nReadBufDataLen = nReadLenth;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("nReadLenth=%ld;nCurTotalLength=%ld;(nReadLenth != nCurTotalReadLength)"), nReadLenth,nCurTotalReadLength);
		return FALSE;
	}

	m_nReadBufDataLen = nReadLenth;
	unsigned short* pnBuffer = NULL;
	unsigned short* pnTemp = NULL;
	int  nSize = (int)(ceil(m_oSrcComtradeFile.m_nBinarys / 16.0));
	nSize += (2 + 2 + m_oSrcComtradeFile.m_nAnalogs);
	pnBuffer = (unsigned short*)m_pFileReadBuffer;
	CComtradeDataBase* pObj = NULL;
	long nBinaryIndex = 0;
	long nAnalogIndex = 0;
	unsigned short* pBuffer = NULL;
	long nIndex = 0;

	if (m_nCurSrcBeginPointIndex > 0)//如果不是第一段读取，第一个点为上一段的最后一个点
	{
		nIndex = 1;
	}

	for (; nIndex < m_nCurSrcIntervalPoints; nIndex++)
	{
		pnTemp = pnBuffer + 4;//4是时间和索引所占的4个字
		POS pos = m_oSrcComtradeFile.GetHeadPosition();
		nBinaryIndex = 0;
		nAnalogIndex = 0;

		while (pos != NULL)
		{
			pObj = (CComtradeDataBase*)m_oSrcComtradeFile.GetNext(pos);
			pBuffer = pObj->GetBuffer();

			if (pObj->IsAnalogData())
			{			
				pBuffer[nIndex] = *pnTemp;
				pnTemp++;			
				nAnalogIndex++;
			}
			else if(pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}
			else 
			{
				if (nBinaryIndex % 16 == 0)//每16个状态一个short
				{
					pBuffer[nIndex] = *pnTemp;
					pnTemp++;
				}

				nBinaryIndex++;
			}
		}

		pnBuffer += nSize;
	}

	m_oSrcComtradeFile.UpdateAllChsTotalPointsNum();
	InitSrcAnalogsBeginAng_SpecialSmpRate();

#ifdef USE_InsertComtradeFile_Mode
	if (m_pInsertComtradeFile != NULL)
	{
		delete m_pInsertComtradeFile;
	}

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq ,dInsertOffsetTime);
#else
	m_dInsertOffsetTime = dInsertOffsetTime;
	m_nInsertTotalPoints = m_oSrcComtradeFile.CalTotalPoints_InsertWithSingleSmpRate(m_dInsertFreq ,dInsertOffsetTime);
#endif

	m_nCurIntervalDeliverPos = 0;

	if ((m_nCurSrcBeginPointIndex+m_nCurSrcIntervalPoints)>=m_nTotalPointsNum)
	{
		m_bReadFileFinish = TRUE;
	}

// 	CComtradeAnalogData *pSaveCh = m_oSrcComtradeFile.GetAnalogDataByChIndex(1,FALSE);
// 
// 	if (pSaveCh != NULL)
// 	{
// 		pSaveCh->WriteAnalogDatas(_T("Src"));
// 		pSaveCh = m_pInsertComtradeFile->GetAnalogDataByChIndex(1,FALSE);
// 		pSaveCh->WriteAnalogDatas(_T("Insert"));
// 	}
	
	return TRUE;
}

long CBigComtradeFileRead::GetCurReadComtradePointsNum(double dInsertOffsetTime)
{
	if (m_nReplayBuffMaxLenth <= 0)
	{
		m_nReplayBuffMaxLenth = FILE_READBUF_SIZE;
	}

	long nReadSrcComtradePointsNum = 0;

	if (m_nCurSrcBeginPointIndex == 0)//对于第一段，需要包含第一个点
	{
		nReadSrcComtradePointsNum = 1;
	}

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	long nChMaxCnt = m_pComtradePlayConfigRef->GetTotalChannelNum();
#else
	long nChMaxCnt = 8;
#endif
	long nMaxInsertPoints = m_nReplayBuffMaxLenth / (nChMaxCnt * sizeof(float));//获取最大采样点数
	double dSrcMaxTime = 0;
	
//首先计算出，插值后需要用到的总点数占用的时间
	ASSERT(nMaxInsertPoints>1);
	dSrcMaxTime =(nMaxInsertPoints-1)/m_dInsertFreq;//无论是否第一段都去除第一个点，后面需要加上 offset时间
	dSrcMaxTime += dInsertOffsetTime;//m_dInsertOffsetTime为Src数据第一个点到插值后数据第一个点的时间差
	double dRemainTime = dSrcMaxTime;//根据插值后数据总时间长度换算出插值前数据需要的总点数
	long nSrcSmpRateBeginPosPointIndex = 0;
	long nSrcSmpRateEndPosPointIndex = 0;
	BOOL bFirstSmpRate = TRUE;
	long nTmp = 0 ,nTmpBeginIndex = 0;

//根据插值后数据总时间长度换算出插值前数据需要的总点数
//源数据第一个点的位置已知，源数据起始点到插值后数据最后一个点的时长可求出
	//求出在该时间段里源数据需要解析的总点数
//第一步：遍历源数据的全部采样频率
//第二步：计算出当前采样率下，源数据开始点索引和结束点索引
//第三步：
	//如果当前解析段的源数据开始位置大于当前采样率下的结束点位置时，则本段区间已经采集完
	//如果当前解析段的源数据开始位置大于当前采样率下的开始点位置时，从当前解析段的源数据开始位置为起始点算总点数，否则从当前采样率下的开始点位置算总点数
	//以当前采样率下的结束点位置为终点，算出相对于起始点的总时间差，如果小于剩余总时间差，则当前采样率下的剩余点全部算入需要解析的点数，当前剩余的时间，减去本次用掉的时间，继续循环
	//否则根据当前剩余时间及当前采样率，计算出需要解析的点数，退出循环

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)//采样点数小于等于0的采样率无效，直接跳过
		{
			continue;
		}

		if (bFirstSmpRate)//如果是第一个采样率，其结束点索引为当前总点数 减去1
		{
			nSrcSmpRateEndPosPointIndex += (m_pnDataPoints[nIndex]-1);
			bFirstSmpRate = FALSE;
		}
		else//第二个采样率以后的情况，直接加上采样总点数，因为默认起始点为上一个采样率的结束点
		{
			nSrcSmpRateEndPosPointIndex += (m_pnDataPoints[nIndex]);
		}

		if (m_nCurSrcBeginPointIndex>nSrcSmpRateEndPosPointIndex)//如果当前开始位置大于本段的结束位置，则本段区间已经采集完
		{
			nSrcSmpRateBeginPosPointIndex = nSrcSmpRateEndPosPointIndex;
			continue;
		} 

		if (m_nCurSrcBeginPointIndex>nSrcSmpRateBeginPosPointIndex)//如果当前开始位置大于本段的开始位置，则本段区间开始位置开始即计算时间
		{
			nTmpBeginIndex = m_nCurSrcBeginPointIndex;
		}
		else
		{
			nTmpBeginIndex = nSrcSmpRateBeginPosPointIndex;
		}

		nTmp = nSrcSmpRateEndPosPointIndex-nTmpBeginIndex;

		if ((((double)nTmp)/m_pdSamRate[nIndex])<dRemainTime)
		{
			nReadSrcComtradePointsNum += nTmp;
			dRemainTime -= (((double)nTmp)/m_pdSamRate[nIndex]);
		} 
		else
		{
			nReadSrcComtradePointsNum += (dRemainTime*m_pdSamRate[nIndex]);
			break;
		}

		nSrcSmpRateBeginPosPointIndex = nSrcSmpRateEndPosPointIndex;
	}

	//为保险考虑，增加判断，解析总点数，不可能超过总的采样点位置
	if ((m_nCurSrcBeginPointIndex + nReadSrcComtradePointsNum) > m_nTotalPointsNum)
	{
		ASSERT(m_nTotalPointsNum>=m_nCurSrcBeginPointIndex);
		nReadSrcComtradePointsNum = m_nTotalPointsNum-m_nCurSrcBeginPointIndex;
	}

	return nReadSrcComtradePointsNum;

	m_nCurSrcBeginPointIndex = 0;

// 	if (m_nFileReadBufLen <= 0)
// 	{
// 		m_nFileReadBufLen = FILE_READBUF_SIZE;
// 	}

// 	long nSinglePointLength = m_oSrcComtradeFile.GetBinarySinglePointLength();
// 
// 	if ((m_nTotalPointsNum-m_nCurSrcBeginPointIndex)*nSinglePointLength<m_nFileReadBufLen)
// 	{
// 		return m_nTotalPointsNum-m_nCurSrcBeginPointIndex;
// 	}
// 
// 	return m_nFileReadBufLen/nSinglePointLength;
}

//变比变化后，更新ReplayBuf和最大值
void CBigComtradeFileRead::OnPTChanged()
{
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	GenerateReplayBufFromRawData(CMTRD_UPDATE_RAWTOREPLAY_U);
	m_pComtradePlayConfigRef->CalcReplayChUMaxValue();
#endif
}

void CBigComtradeFileRead::OnCTChanged()
{
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	GenerateReplayBufFromRawData(CMTRD_UPDATE_RAWTOREPLAY_I);
	m_pComtradePlayConfigRef->CalcReplayChIMaxValue();
#endif
}
long CBigComtradeFileRead::GetTotalPointsNum()
{
	return m_nTotalPointsNum;
}

