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
	m_dInsertFreq = 10000;	//zhouhj 20210922 ��25000��Ϊ10000
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰģ����ͨ����Ϊ0"));
	}

	long nChMaxPoints = m_nReplayBuffMaxLenth / (nChMaxCnt * sizeof(float));
	double dMaxTime = nChMaxPoints/m_dInsertFreq;
	long nMaxPoints = dMaxTime*dMaxSmpRate;
	nMaxPoints++;//��ֹ�����������һ����
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

//��Comtrade cfg�ļ�
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

//����cfg�ļ��󣬳�ʼ��A\B\Kӳ���ϵ
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

	//ģ����
	int nUAnalogyNum = oUList.GetCount();
	int nIAnalogyNum = oIList.GetCount();

	pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	POS posCh = NULL;
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	int nUChIndex = 0,nIChIndex = 0;
	int nModulesChCount = 0;

	//������
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
						pCh->m_nChA_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��
// 						pCh->m_nChB_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��
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
						pCh->m_nChA_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��
// 						pCh->m_nChB_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��

					}
					nIChIndex++;
				}

					//2024-4-15 wuxinyi ������Ĭ��ѡ��һ������ĵ�һ��ͨ��
					if(nModulesChCount < 1)//20230914 wxy ��ģ��ͨ��������12��Ĭ�ϲ���ѡ
				{
					pCh->m_nChSelected = 1;
					//Ĭ�Ϲ�ѡ  20220519 ȥ��Ĭ�Ϲ�ѡ,��ѡ��ͨ������ͳһ���г�ʼ��,��ֹͨ������̫��Ӱ�����ݷ���

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

				pCh->InitCh_B(NULL);//20231025 wxy ���Bͨ����ʼ��
				pCh->m_nChB_Index = 0;
				//pCh->m_dK = 1; //dxy 20240204 �������Ⱥ�ͨ����һ����ֵ���´��ļ��󲻳�ʼ��
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

	//���忪����
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

	//ģ����
	int nUAnalogyNum = oUList.GetCount();
	int nIAnalogyNum = oIList.GetCount();

	pos = m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetHeadPosition();
	POS posCh = NULL;
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	int nUChIndex = 0,nIChIndex = 0;
	int nModulesChCount = 0;

	//������
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
							pCh->m_nChA_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��
							// 						pCh->m_nChB_Index = nUChIndex % nUAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��
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
							pCh->m_nChA_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��
							// 						pCh->m_nChB_Index = nIChIndex % nIAnalogyNum;//20230821-wxy-��ʼ��ͨ��ѡ��

						}
						nIChIndex++;
					}

// 					//2024-4-15 wuxinyi ������Ĭ��ѡ��һ������ĵ�һ��ͨ��
// 					if(nModulesChCount < 1)//20230914 wxy ��ģ��ͨ��������12��Ĭ�ϲ���ѡ
// 					{
// 						pCh->m_nChSelected = 1;
// 						//Ĭ�Ϲ�ѡ  20220519 ȥ��Ĭ�Ϲ�ѡ,��ѡ��ͨ������ͳһ���г�ʼ��,��ֹͨ������̫��Ӱ�����ݷ���
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

					pCh->InitCh_B(NULL);//20231025 wxy ���Bͨ����ʼ��
					pCh->m_nChB_Index = 0;
					//pCh->m_dK = 1; //dxy 20240204 �������Ⱥ�ͨ����һ����ֵ���´��ļ��󲻳�ʼ��
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

	//���忪����
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

	//���忪����ģ��	
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

	if (!bHasSpecialSmpRate)//�����ж��Ƿ�����������Ƶ��
	{
		return;
	}

	long nCurIntervalEndPtIndex = m_nCurSrcBeginPointIndex + m_oSrcComtradeFile.m_nTotalPoints - 1;
	long nSmpRateBeginIndex = 0;
	long nSmpRateEndIndex = 0;
	long nSingleLoopPts = 0;//�����ܲ��ĵ���
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

		if ((m_nCurSrcBeginPointIndex<nSmpRateEndIndex)&&(nCurIntervalEndPtIndex>nSmpRateBeginIndex))//ȷ����ȡ�����ݵ��ڸöβ���Ƶ����
		{
			if ((m_nCurSrcBeginPointIndex>=nSmpRateBeginIndex)&&(fabs(dCurFreq*2-m_pdSamRate[nIndex])<0.0001))//�����ǰƵ��Ϊ2*50Hz ���ҵ�ǰ�ε�һ������Ƶ�ʼ�Ϊ�ˣ���Ҫ������Ƿ�ͬ��λ
			{
				BOOL bInPhase_SpecialSmpRate = (((m_nCurSrcBeginPointIndex-nSmpRateBeginIndex)%2) == 0);
				m_oSrcComtradeFile.SetInPhase_SpecialSmpRate(bInPhase_SpecialSmpRate);
			}
			else if ((nCurIntervalEndPtIndex<= nSmpRateEndIndex)
				&&((nCurIntervalEndPtIndex-nSmpRateBeginIndex)>(nSingleLoopPts+3))
				&&(m_pdSamRate[nIndex]>4*dCurFreq))//�����ǰ����Ƶ��Ϊ��ǰ�ε����һ������Ƶ��,�����ڵ�ǰ�ε��ܲ�����������һ���ܲ�+3�ĵ���������ÿ�ܲ�������������4�������
				//���������ǰ����Ƶ�������һ�������λ
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
	//��ʼ������
	BOOL bRet = OpenBigComtradeCfgFile(strComtradeFile,nOnceReadFileLen);

	if (bRet)
	{
		//���������ļ��󣬳�ʼ��configӳ��
		if (bInitDefault)
		{//���Ǵ򿪲��Լ�¼������Ҫ��ʼ����ֵ
			InitChMapConfig();
		}
		else
		{
			RefreshChMapConfig();//���θ������´򿪲����ļ�����������ͨ��
		}
		
		//��20M���ݣ�������AnalogData
		bRet = ReadBigComtradeDataFile(strComtradeFile);

		if (!bRet)
		{
			return bRet;
		}

		//��Ҫע����ǣ�����ǹ��ϻط�֮ǰ����AnalogData������ReplayBufʼ�մ�AnalogData��ʼλ�ý���
		//��AnalogData������ReplayBuf
		GenerateReplayBufFromRawData(/*TRUE*/);
	}

	return bRet;
}

//����m_pFileReadBuffer����ʣ�����ݣ����ļ������,��������AnalogData��
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

//�������ò�������λ�ļ������ݣ���������AnalogData��
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
		if (m_pnDataPoints[nIndex]<=0)//��������С�ڵ���0�Ĳ�������Ч��ֱ������
		{
			continue;
		}

		if (bFirstSmpRate)//����ǵ�һ�������ʣ������������Ϊ��ǰ�ܵ��� ��ȥ1
		{
			nEndPosPointIndex += (m_pnDataPoints[nIndex]-1);
			bFirstSmpRate = FALSE;
		}
		else//�ڶ����������Ժ�������ֱ�Ӽ��ϲ����ܵ�������ΪĬ����ʼ��Ϊ��һ�������ʵĽ�����
		{
			nEndPosPointIndex += (m_pnDataPoints[nIndex]);
		}

		if ((m_nCurSrcBeginPointIndex<=nEndPosPointIndex)&&(m_nCurSrcBeginPointIndex>=nBeginPosPointIndex))//�����ǰλ���ڸò�����������
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

//��AnalogDataԭʼ���������ReplayBuf
BOOL CBigComtradeFileRead::GenerateReplayBufFromRawData(UINT nUpdateMask)
{
	//ReplayBuf�������������TRUE,AnalogData�������ReplayBuf����δ��������FALSE
	m_fReplayStartTime = m_nCurInsertBeginPointIndex/(m_dInsertFreq);
	CalCurRawStartTime();

	//����ÿ��ͨ��������UpdateReplayBuf�����θ���
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
                       //2023-03-18 wuxinyi �޸Ŀ�����ͨ��ӳ�䱻��ʼ��Ϊ������
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
	
	//֧�ֿ���������ʱ�Ÿ��¿���ͨ��
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

//�ɻطŻ���ReplayBuf���AB����
BOOL CBigComtradeFileRead::GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf)
{
	//AB�������������TRUE,ReplayBuf�������AB����δ��������FALSE
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	//��ȡpABBuf��ǰ������ܳ���,������ͨ�����������ÿ��������ռ�õ��ܳ��ȣ������������ǰ�������ܴ�ŵ��ܵ���
	long nABBuffRemainSpace = pABBuf->GetRemainSpace();
	long nChs = m_pComtradePlayConfigRef->GetTotalChs_SelectedModule();
	if(nChs <= 0)
	{
		return FALSE;
	}

	long nABBuffRemainPts = nABBuffRemainSpace/nChs;

	//�����ǰReplayBuf����ʣ����ܵ������ڵ��ڷ���pABBuf��Ҫ���ܵ���,��������棬���ı�ReplayBuf�е�m_nDataFillBeginPosλ��  ����TRUE
#ifdef USE_InsertComtradeFile_Mode
	long nCurIntervalRemainPts = m_pInsertComtradeFile->m_nTotalPoints - m_nCurIntervalDeliverPos;//��ǰ�ν����Ĳ�ֵ�����
#else
	long nCurIntervalRemainPts = m_nInsertTotalPoints - m_nCurIntervalDeliverPos;//��ǰ�ν����Ĳ�ֵ�����
#endif

	BOOL bRet = FALSE;
	long nCurFillPoints = 0;

	if (nCurIntervalRemainPts >= nABBuffRemainPts)
	{
		nCurFillPoints = nABBuffRemainPts;
		bRet = TRUE;
	} 
	else//���ReplayBuf�����ʣ���ܵ���С�ڷ���pABBuf��Ҫ���ܵ���,��ʣ�����ȫ������pABBuf,���ı�ReplayBuf�е�m_nDataFillBeginPosλ�ã�����FALSE
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

//ԭʼ���ݡ��ط��������
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

//��λ�ļ���һ�������LoopBuf����
BOOL CBigComtradeFileRead::GenerateLoopBuf()
{
	CComtradeDataBuffer *pLoopBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(0);
	pLoopBuf->ResetWritePos();

	//��һ�����������ò�������λ�ļ������ݣ���������AnalogData��
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
	
//	pLoopBuf->BufferDatas_WriteFile();//20220519 ����һ���ܲ�����д���ļ� 
	delete ppChValue;
#endif

// 	BOOL bExitFlag = FALSE;
// 	while(TRUE)
// 	{
// 		//��һ������ReplayBuf���������LoopBuf
// 		if (GenerateABBufFromReplayBuf(pLoopBuf))
// 		{
// 			break;
// 		}
// 
// 		//˵��LoopBufδ������ReplayBuf����
// 		if (bExitFlag)
// 		{
// 			break;
// 		}
// 
// 		while(TRUE)
// 		{
// 			//�ڶ�������AnalogDataԭʼ���������ReplayBuf
// 			if (GenerateReplayBufFromRawData(FALSE))
// 			{
// 				break;
// 			}
// 
// 			//˵��ReplayBufδ������AnalogData����
// 			bExitFlag = TRUE;
// 			break;
// 		}
// 	}
// 
// 	//���Ĳ����������
// 	ResetDataBuf();
	
	pLoopBuf->SetRWState(COMTRADE_DATABUF_MODE_READ);

	return TRUE;
}

//���ABBuf����
BOOL CBigComtradeFileRead::GenerateABBuf(int nIndex)
{
	CComtradeDataBuffer *pABBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nIndex);
	pABBuf->ResetWritePos();

	while(TRUE)
	{
		//��һ������ReplayBufԭʼ���������pABBuf
		if(GenerateABBufFromReplayBuf(pABBuf))
		{//˵����ɻ��������
			break;
		}

		//˵��pABBufδ������ReplayBuf����
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
// 			//�ڶ�������ԭʼ����AnalogData����ReplayBuf�����»ط���ʼʱ��
// 			if (GenerateReplayBufFromRawData(/*FALSE*/))
// 			{
// 				//˵��ReplayBuf�������������¼���UI���ֵ,֪ͨ����ˢ�»طŲ���
// 				m_pComtradePlayConfigRef->CalcReplayChMaxValue();
// 				break;
// 			}
// 
// 			//˵��ReplayBufδ������AnalogData����
// 			if (m_bReadFileFinish)
// 			{
// 				//˵��ReplayBufδ�����������һ֡�������¼���UI���ֵ,֪ͨ����ˢ�»طŲ���
// 				m_pComtradePlayConfigRef->CalcReplayChMaxValue();
// 				break;
// 			}
// 
// 			//���������ɶ��ļ�����AnalogData������ԭʼ������ʼʱ��
// 			GenerateComtradeChDataFromDataFile(FALSE);
// 
// 			//˵��AnalogData�����������һ֡��֪ͨ����ˢ��ԭʼ����
// 		}
#endif
	}

	pABBuf->SetRWState(COMTRADE_DATABUF_MODE_READ);

	return TRUE;
}

//��ʼ����֮ǰ����ʼ��Loop\A\B����
void CBigComtradeFileRead::BeginGenerateComtradeBuf(BOOL bResetCoef)
{
	//�������
	ResetDataBuf();
	//�ļ����¶�λ
//	m_oFileRead.SeekToBegin();

	//ÿ�ο�ʼ����ǰ�����´��ļ�ͷ��ʼ������
	GenerateComtradeChDataFromDataFile(TRUE,bResetCoef);
	GenerateReplayBufFromRawData(/*FALSE*/);
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	m_pComtradePlayConfigRef->CalcReplayChMaxValue();

	if (m_pComtradePlayConfigRef->HasLoopData())
	{
		GenerateLoopBuf();
	}
#endif

	//���A����
	GenerateABBuf(1);

	if (!m_bAnalysisFinish)
	{
		//���B����
		GenerateABBuf(2);
	}
}

BOOL CBigComtradeFileRead::InsertCyclePointsByRelTime(double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex)
{
	// ȷ����ʼ�ͽ���ʱ���ں���Χ��
	if (dBeginTime < 0 || dEndTime > m_pInsertComtradeFile->CalComtradeFileSumTime() || dBeginTime > dEndTime)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����ʱ�䲻���Ϻ���ʱ��Σ������¼����ٴ����룡"));

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
	// ȷ����ʼ�ͽ���ʱ���ں���Χ��
	if (nBeginPoint < 0 || nEndPoint > m_nTotalPointsNum || nBeginPoint > nEndPoint)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����ʱ�䲻���Ϻ���ʱ��Σ������¼����ٴ����룡"));

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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����ĵ�ѹ/����������С��0���������޸ģ�"));
		return FALSE;
	}
	else if(dTime_Second < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("���ʱ�䲻����С��0���������޸ģ�"));
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
	// ȷ����ʼ�ͽ���ʱ���ں���Χ��
	if (dBeginTime < 0  || dBeginTime > dEndTime)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ɾ��ʱ�䲻���Ϻ���ʱ��Σ������¼����ٴ����룡"));
		return FALSE;
	}
	else if(dEndTime > m_pInsertComtradeFile->CalComtradeFileSumTime() || dBeginTime > m_pInsertComtradeFile->CalComtradeFileSumTime() )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ɾ��/�����ʱ��㳬��������ʱ��Σ������¼����ٴ����룡"));
		return FALSE;
	}
	m_oSrcComtradeFile.DeletePointsByRelTime(dBeginTime, dEndTime);
	m_nCurSrcIntervalPoints = m_oSrcComtradeFile.m_nTotalPoints;

	m_nTotalPointsNum = m_oSrcComtradeFile.m_nTotalPoints;
	SetBigFileTotalSmpRates();

	m_pInsertComtradeFile = m_oSrcComtradeFile.CloneComtradeWithSingleSmpRate(m_dInsertFreq);
	GenerateReplayBufFromRawData();

	//2024-1-24 wuxinyi �����ļ�
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
//����(A-B)/K���Ƿ�ѡ�ı䣬��ӦReplayBufҲҪ���£������������¼������ֵ���������ֵ
BOOL CBigComtradeFileRead::UpdateChReplayBuf(CSttModuleChComtradeBind *pCh, CSttModuleComtradeBind *pModule, BOOL bSave)
{//ReplayBuf�������������TRUE,AnalogData�������ReplayBuf����δ��������FALSE
#ifdef USE_InsertComtradeFile_Mode
	ASSERT(m_pInsertComtradeFile);
//	ASSERT(pCh->GetMaxPoints()>0);
	//��ȡ��ǰͨ��ReplayBuff��С�����С�ڲ�ֵ���ε����Ĵ�С�������³�ʼ��
	if (pCh->GetMaxPoints()<m_pInsertComtradeFile->m_nTotalPoints)
	{
		pCh->InitChReplayBuf(m_pInsertComtradeFile->m_nTotalPoints + 5);//��Ԥ��5���㣬����Ƶ�����³�ʼ������
	}

	//zhouhj 2023.9.11 �˴���ȡ��Ӧ��ͨ��,ֱ��ʹ�ö�Ӧ��ָ��,����ͨ��nIndexChA��ȡ
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

// 	if(pCh->m_strID.Find(_T("Digital")) != 0)//�������޷�����CT��PT���
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

// 	if ((pAnalogDataA == NULL)&&(pAnalogDataB == NULL))//���A��B��δ���ã���ֱ�ӷ���
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
		if ((pCh->m_nChSelected == 0)||((pAnalogDataA == NULL)&&(pAnalogDataB == NULL)))//zhouhj 20211105 ���δѡ�����ͨ��A\B��Ϊ��,�����Ϊ0
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
	//��ȡ��ǰͨ��ReplayBuff��С�����С�ڲ�ֵ���ε����Ĵ�С�������³�ʼ��
	if (pCh->GetMaxPoints()<m_nInsertTotalPoints)
	{
		pCh->InitChReplayBuf(m_nInsertTotalPoints + 5);//��Ԥ��5���㣬����Ƶ�����³�ʼ������
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

	if ((pAnalogDataA == NULL)&&(pAnalogDataB == NULL))//���A��B��δ���ã���ֱ�ӷ���
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

	return (!m_bReadFileFinish);//����ļ��������ˣ��򻺴�δ��������ļ�δ�����꣬�򻺴�����
}

//����(A-B)/K���Ƿ�ѡ�ı䣬��ӦReplayBufҲҪ���£������������¼������ֵ���������ֵ
BOOL CBigComtradeFileRead::UpdateChReplayBuf(int nModuleIndex,int nChIndex/*,BOOL bFromStart*/)
{//ReplayBuf�������������TRUE,AnalogData�������ReplayBuf����δ��������FALSE
	ASSERT((nModuleIndex >= 0) && (nChIndex>= 0));

	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind *)m_pComtradePlayConfigRef->m_oSttModulesComtradeBind.GetAt(nModuleIndex);
	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)pModule->GetAt(nChIndex);

	//����������Ϣ����λ��ABͨ��ѡ��K,������AnalogData����ָ��pCh->ReplayBuf
	return UpdateChReplayBuf(pCh, pModule/*,bFromStart*/);
}
#endif

BOOL CBigComtradeFileRead::UpdateBinaryChReplayBuf( CSttModuleComtradeBind *pModule )
{
	if(!m_pInsertComtradeFile || !pModule)
	{
		return FALSE;
	}

	CComplexMemBuffer_Float* pReplayBufBinary1 = pModule->m_pReplayBufBinary1; // ��λ
	CComplexMemBuffer_Float* pReplayBufBinary2 = pModule->m_pReplayBufBinary2; // ��λ

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
				//��ǰÿ�������Ŀ�����λ�õ�ȫ����Ϊ1
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
// 						CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰӳ��ͨ����%s��δ�ҵ���"),pBinaryCh->m_strComtradeBinaryCh);
						nBoutData &= ~(1ULL << nChIndex);//��Ϊ0
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
							nBoutData &= ~(1ULL << nChIndex);//��Ϊ0
						}
					}
				}
				else
				{
					nBoutData &= ~(1ULL << nChIndex);//��Ϊ0
				}
			}
			++nChIndex;
		}
	
		while (nChIndex < 64)
		{
			nBoutData &= ~(1ULL << nChIndex);//��Ϊ0
			++nChIndex;
		}

		// �����������ݴ����Ӧ�ĻطŻ���λ��
		if (pdData1 != NULL)
		{
			pdData1[nPtIndex] = (long)(nBoutData & 0xFFFFFFFF); // �� 32 λ
		}
		if (pdData2 != NULL)
		{
			pdData2[nPtIndex] = (long)((nBoutData >> 32) & 0xFFFFFFFF); // �� 32 λ
		}
	}

	// ���ûطŻ�������ݳ���
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

	//�ڸ�ѭ���л�ȡ��Ҫ�õ����ܵĲ���������
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
		
		//ֻҪ��֤��ǰ�����εĿ�ʼ���ڵ�ǰ�����ʽ������ǰ�棬���ҵ�ǰ�����ν������ڵ�ǰ�����ʵĿ�ʼ��֮��˵���ڷ�Χ��
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

		//ֻҪ��֤��ǰ�����εĿ�ʼ���ڵ�ǰ�����ʽ������ǰ�棬���ҵ�ǰ�����ν������ڵ�ǰ�����ʵĿ�ʼ��֮��˵���ڷ�Χ��
		if ((m_nCurSrcBeginPointIndex<nCurSmpRateEndPt)&&(nCurTntervalEndPt>nCurSmpRateBeginPt))
		{
			if (nCurIntervalIndex == 0)//���ڵ�һ�β���Ƶ���µ��ܵ�����Ҫ���ϵ�һ���㣬�ڶ����Ժ�Ĳ���Ƶ�� ���һ����Ϊ��һ������Ƶ�ʵ����һ����
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��dat�ļ�(%s)ʧ��."), strDatFilePath.GetString());

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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰCFG�ļ��б�ʶ���ܵ���%ld(%s),��DAT�ļ���ʵ���ܵ���%ld��һ��,���޸�CFG�ļ�."), m_nTotalPointsNum,strSmpRateString.GetString(), nIndex);
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
    InitLocalCodec_BeforeReadWrite(strDatFilePath,&pOldTextCodec);//�������Ϊutf-8
#endif

	if (!m_oFileRead.Open(strDatFilePath,CFile::modeRead))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��dat�ļ�(%s)ʧ��."), strDatFilePath.GetString());
		return FALSE;
	}

#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);
	system("sync");//20220616 д�ļ�����Ҫͬ��
#endif

	m_nReadBufDataLen = 0;
	m_nTotalPointsNum = m_oSrcComtradeFile.GetTotalPoints();
	long nSinglePointLength = m_oSrcComtradeFile.GetBinarySinglePointLength();
	long nActTotalPointsNum = m_oFileRead.GetLength()/nSinglePointLength;

	if (nActTotalPointsNum<m_nTotalPointsNum)
	{
		CString strSmpRateString;
		m_oSrcComtradeFile.GetSmpRateString(strSmpRateString);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰCFG�ļ��б�ʶ���ܵ���%ld(%s),��DAT�ļ��е�ʵ���ܵ���%ld��һ��,���޸�CFG�ļ�."), m_nTotalPointsNum,strSmpRateString.GetString(), nActTotalPointsNum);
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

//��ԭʼ�����ļ��ж�ȡԭʼ����
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
		&& (m_pInsertComtradeFile != NULL))//���֮ǰ����������ֵ֮������ݻ��ڣ����ҿ�ʼ��Ϊ0�����������½���
#else
		&& (m_nInsertTotalPoints>0))//���֮ǰ����������ֵ֮������ݻ��ڣ����ҿ�ʼ��Ϊ0�����������½���
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
		m_nCurSrcBeginPointIndex += (m_nCurSrcIntervalPoints-1);//Դ���ݴӴ���һ�ε����һ���㿪ʼ

#ifdef USE_InsertComtradeFile_Mode
		m_nCurInsertBeginPointIndex += m_pInsertComtradeFile->m_nTotalPoints;//��ֵ�����ݴ���һ���������󣬲����ظ�
#else
		m_nCurInsertBeginPointIndex += m_nInsertTotalPoints;//��ֵ�����ݴ���һ���������󣬲����ظ�
#endif
	}

	double dInsertOffsetTime = CalInsertOffsetTime();
	long nCurReadPointsNum = GetCurReadComtradePointsNum(dInsertOffsetTime);
	long nCurTotalReadLength = m_oSrcComtradeFile.GetBinarySinglePointLength()*nCurReadPointsNum;

	if (m_nCurSrcBeginPointIndex == 0)
	{
		m_nCurSrcIntervalPoints = nCurReadPointsNum;//���ڵ�һ�Σ�ʵ���ܵ���Ϊ��ȡ���ܵ���
	} 
	else//����Ϊʵ���ܵ���+1
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

	if (m_nCurSrcBeginPointIndex > 0)//������ǵ�һ�ζ�ȡ����һ����Ϊ��һ�ε����һ����
	{
		nIndex = 1;
	}

	for (; nIndex < m_nCurSrcIntervalPoints; nIndex++)
	{
		sString = m_oASII_ModeBuffer.GetString();

		if (!m_oASII_ModeBuffer.IsPoiterInBuffer(sString))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CFG�ļ����ܵ�����DADA�ļ���ʵ���ܵ�����һ��,��ǰ�μƻ��ܵ���%ld,ʵ���ļ���ֻ�����ܵ���%ld."),m_nCurSrcIntervalPoints, (nIndex+1));
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
		&& (m_pInsertComtradeFile != NULL))//���֮ǰ����������ֵ֮������ݻ��ڣ����ҿ�ʼ��Ϊ0�����������½���
#else
		&& (m_nInsertTotalPoints>0))//���֮ǰ����������ֵ֮������ݻ��ڣ����ҿ�ʼ��Ϊ0�����������½���
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
		m_nCurSrcBeginPointIndex += (m_nCurSrcIntervalPoints-1);//Դ���ݴӴ���һ�ε����һ���㿪ʼ
#ifdef USE_InsertComtradeFile_Mode
		m_nCurInsertBeginPointIndex += m_pInsertComtradeFile->m_nTotalPoints;//��ֵ�����ݴ���һ���������󣬲����ظ�
#else
		m_nCurInsertBeginPointIndex += m_nInsertTotalPoints;//��ֵ�����ݴ���һ���������󣬲����ظ�
#endif
	}

	double dInsertOffsetTime = CalInsertOffsetTime();
	long nCurReadPointsNum = GetCurReadComtradePointsNum(dInsertOffsetTime);
	long nCurTotalReadLength = m_oSrcComtradeFile.GetBinarySinglePointLength()*nCurReadPointsNum;

	if (m_nCurSrcBeginPointIndex == 0)
	{
		m_nCurSrcIntervalPoints = nCurReadPointsNum;//���ڵ�һ�Σ�ʵ���ܵ���Ϊ��ȡ���ܵ���
	} 
	else//����Ϊʵ���ܵ���+1
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
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("��ȡָ�����ȵĴ��ļ�����ʧ��."));
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

	if (m_nCurSrcBeginPointIndex > 0)//������ǵ�һ�ζ�ȡ����һ����Ϊ��һ�ε����һ����
	{
		nIndex = 1;
	}

	for (; nIndex < m_nCurSrcIntervalPoints; nIndex++)
	{
		pnTemp = pnBuffer + 4;//4��ʱ���������ռ��4����
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
				if (nBinaryIndex % 16 == 0)//ÿ16��״̬һ��short
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

	if (m_nCurSrcBeginPointIndex == 0)//���ڵ�һ�Σ���Ҫ������һ����
	{
		nReadSrcComtradePointsNum = 1;
	}

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	long nChMaxCnt = m_pComtradePlayConfigRef->GetTotalChannelNum();
#else
	long nChMaxCnt = 8;
#endif
	long nMaxInsertPoints = m_nReplayBuffMaxLenth / (nChMaxCnt * sizeof(float));//��ȡ����������
	double dSrcMaxTime = 0;
	
//���ȼ��������ֵ����Ҫ�õ����ܵ���ռ�õ�ʱ��
	ASSERT(nMaxInsertPoints>1);
	dSrcMaxTime =(nMaxInsertPoints-1)/m_dInsertFreq;//�����Ƿ��һ�ζ�ȥ����һ���㣬������Ҫ���� offsetʱ��
	dSrcMaxTime += dInsertOffsetTime;//m_dInsertOffsetTimeΪSrc���ݵ�һ���㵽��ֵ�����ݵ�һ�����ʱ���
	double dRemainTime = dSrcMaxTime;//���ݲ�ֵ��������ʱ�䳤�Ȼ������ֵǰ������Ҫ���ܵ���
	long nSrcSmpRateBeginPosPointIndex = 0;
	long nSrcSmpRateEndPosPointIndex = 0;
	BOOL bFirstSmpRate = TRUE;
	long nTmp = 0 ,nTmpBeginIndex = 0;

//���ݲ�ֵ��������ʱ�䳤�Ȼ������ֵǰ������Ҫ���ܵ���
//Դ���ݵ�һ�����λ����֪��Դ������ʼ�㵽��ֵ���������һ�����ʱ�������
	//����ڸ�ʱ�����Դ������Ҫ�������ܵ���
//��һ��������Դ���ݵ�ȫ������Ƶ��
//�ڶ������������ǰ�������£�Դ���ݿ�ʼ�������ͽ���������
//��������
	//�����ǰ�����ε�Դ���ݿ�ʼλ�ô��ڵ�ǰ�������µĽ�����λ��ʱ���򱾶������Ѿ��ɼ���
	//�����ǰ�����ε�Դ���ݿ�ʼλ�ô��ڵ�ǰ�������µĿ�ʼ��λ��ʱ���ӵ�ǰ�����ε�Դ���ݿ�ʼλ��Ϊ��ʼ�����ܵ���������ӵ�ǰ�������µĿ�ʼ��λ�����ܵ���
	//�Ե�ǰ�������µĽ�����λ��Ϊ�յ㣬����������ʼ�����ʱ�����С��ʣ����ʱ����ǰ�������µ�ʣ���ȫ��������Ҫ�����ĵ�������ǰʣ���ʱ�䣬��ȥ�����õ���ʱ�䣬����ѭ��
	//������ݵ�ǰʣ��ʱ�估��ǰ�����ʣ��������Ҫ�����ĵ������˳�ѭ��

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)//��������С�ڵ���0�Ĳ�������Ч��ֱ������
		{
			continue;
		}

		if (bFirstSmpRate)//����ǵ�һ�������ʣ������������Ϊ��ǰ�ܵ��� ��ȥ1
		{
			nSrcSmpRateEndPosPointIndex += (m_pnDataPoints[nIndex]-1);
			bFirstSmpRate = FALSE;
		}
		else//�ڶ����������Ժ�������ֱ�Ӽ��ϲ����ܵ�������ΪĬ����ʼ��Ϊ��һ�������ʵĽ�����
		{
			nSrcSmpRateEndPosPointIndex += (m_pnDataPoints[nIndex]);
		}

		if (m_nCurSrcBeginPointIndex>nSrcSmpRateEndPosPointIndex)//�����ǰ��ʼλ�ô��ڱ��εĽ���λ�ã��򱾶������Ѿ��ɼ���
		{
			nSrcSmpRateBeginPosPointIndex = nSrcSmpRateEndPosPointIndex;
			continue;
		} 

		if (m_nCurSrcBeginPointIndex>nSrcSmpRateBeginPosPointIndex)//�����ǰ��ʼλ�ô��ڱ��εĿ�ʼλ�ã��򱾶����俪ʼλ�ÿ�ʼ������ʱ��
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

	//Ϊ���տ��ǣ������жϣ������ܵ����������ܳ����ܵĲ�����λ��
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

//��ȱ仯�󣬸���ReplayBuf�����ֵ
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

