#include "stdafx.h"
#include "ComtradePlayConfig.h"
#include "BigComtradeTransPlay.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
//#include "../Engine/SttPowerTestEngineBase.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"


BOOL FindInCStringArry(const CStringArray& strList, const CString & strName)
{
	long nIndex = 0;
	long nCount = strList.GetCount();
	BOOL bFind = FALSE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (strName == strList.GetAt(nIndex))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CComtradePlayConfig::CComtradePlayConfig(void)
{
	InitDefault();
	m_nReplayBufFlush = CMTRD_FLUSH_TYPE_NoFlush;
}

CComtradePlayConfig::~CComtradePlayConfig(void)
{
}

void CComtradePlayConfig::InitDefault(BOOL bInitNotModuleParas)
{
#ifdef _PSX_IDE_QT_
	m_tGps.init();
#endif
// 	m_nTrigTimeS = 0;
// 	m_nTrigTimeNS = 0;

	m_nStartCycleNum = 0;
#ifdef _PSX_IDE_QT_
	m_nTrigAfterMode = COMTRADE_TRIGGRE_AFTER_TYPE_Immediately;
#endif

	if (bInitNotModuleParas)
	{
		m_fPTRatio[0] = m_fPTRatio[1] = 1;
		m_fCTRatio[0] = m_fCTRatio[1] = 1;//dxy 20240204 按需求PT CT变比重新打开文件后不初始化

#ifdef _PSX_IDE_QT_
		m_nTriggerType = COMTRADE_TRIGGRE_TYPE_No;
		m_oBinaryConfig.init();
		m_oWaveEditParas.init();
#endif
	}

}

long CComtradePlayConfig::GetTotalChannelNum()
{
	long nNum = 0;

	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(pModule->IsBinaryTypeModule())
		{
			nNum += 2;
		}
		else
		{
		nNum += pModule->GetCount();
	}
	}
	if(m_oSttModulesComtradeBind.IsBinaryModuleSelected())
	{
		nNum += 2;
	}

	return nNum;
}

long CComtradePlayConfig::GetTotalUChannelNum()
{
	long nNum = 0;

	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
		nNum += pModule->GetCount_U();
	}
	}

	return nNum;
}

long CComtradePlayConfig::GetTotalIChannelNum()
{
	long nNum = 0;

	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
		nNum += pModule->GetCount_I();
	}
	}

	return nNum;
}

//根据配置参数、缓存大小计算缓存中能存的最大点数,分配回放用数据缓存
void CComtradePlayConfig::InitReplayBuf(long nABBufLen)
{
	long nChMaxCnt = GetTotalChannelNum();
	if (nChMaxCnt <= 0)
	{
		return;
	}
	long nChMaxPoints = nABBufLen / (nChMaxCnt * sizeof(float));

	m_oSttModulesComtradeBind.InitModuleReplayBuf(nChMaxPoints);
}

//清空回放缓存数据
void CComtradePlayConfig::ResetReplayBuf()
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
		pModule->ResetModuleReplayBuf();
	}
		else
		{
			pModule->ResetReplayBufBinaryBuf();
		}
	}

	pModule = GetBinaryModule();
	if(pModule)
	{
		pModule->ResetReplayBufBinaryBuf();
	}
}

#ifdef _PSX_IDE_QT_
//更新回放缓存数据后调用，用于界面显示
void CComtradePlayConfig::GetReplayChMaxValue(double &fUMax,double &fIMax,int nModuleType)
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	double fValue = 0;
	fUMax = 0;
	fIMax = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if((pModule->IsAnalogTypeModule() && nModuleType == REPLAY_MODULE_TYPE_ANALOG) || 
			(pModule->IsDigitalTypeModule() && nModuleType == REPLAY_MODULE_TYPE_DIGITAL) ||
			(pModule->IsWeekTypeModule() && nModuleType == REPLAY_MODULE_TYPE_WEEK))
		{
		if (!pModule->IsModuleSelected())
		{
			continue;
		}

		fValue = pModule->GetModuleMaxValue_U();

			if (fValue > fUMax)
			{
				fUMax = fValue;
			}

		fValue = pModule->GetModuleMaxValue_I();

			if (fValue >fIMax)
			{
				fIMax = fValue;
			}
		}
	}

}
#endif

// void CComtradePlayConfig::GetWeekChMaxValue( double &fUMax,double &fIMax,int nRealModuleIndex )
// {
// 	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
// 	CSttModuleComtradeBind *pModule = NULL;
// 	CSttModuleChComtradeBind *pCh = NULL;
// }


void CComtradePlayConfig::GetDigitalChMaxValue( double &fUMax,double &fIMax )
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;

 	CString strRateName, strPrimRate;
 	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
 	CIecCfgDatasSMV *pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
 	CIecCfgSysParas *pIecCfgSysParas = pIecCfgDatasMngr->GetSysParasMngr();
 	CIecCfgSmvRates *pIecCfgDatasSMVRates = pIecCfgDatasSMV->GetIecCfgSmvRates();
 	CIecCfgPrimRates *pIecCfgPrimRates = (CIecCfgPrimRates *)pIecCfgSysParas->GetPrimRates();

	fUMax = 0;
	fIMax = 0;

	double fValue = 0;
	int nChIndex = 0, nGroupIndex = 0;
	bool bIsUCh = false;
	//2024-7-13 wuxinyi 当是二次值时，才需要通过变比计算
// 	bool bIsSecond = (g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel() == 0)? TRUE:FALSE;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(pModule->IsDigitalTypeModule())
		{
			POS pos1 = pModule->GetHeadPosition();
			while(pos1)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(pos1);
				if (!pCh->IsChannelSelected())
				{
					continue;
				}

				bIsUCh = pCh->IsModuleType_U()?TRUE:FALSE;
				//电压电流数组
				nGroupIndex = (nChIndex < 3) ? DIGITAL_CH_MAP_FRIST_GROUP : DIGITAL_CH_MAP_SECOND_GROUP;

				if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_61850_92)
				{	
					if(nGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
					{	
						strRateName = bIsUCh ? _T("Uabcz") : _T("Iabc");
						strPrimRate = bIsUCh ? _T("U1-abc") : _T("I1-abc");
					}
					else
					{
						strRateName = bIsUCh ? _T("Up-abcz") : _T("Ip-abc");
						strPrimRate = bIsUCh ? _T("U2-abc") : _T("I1-abc");
					}

		 			//比例因子
		 			float fRate = pIecCfgDatasSMVRates->GetSmvRate(strRateName);
			 
		 			//一次值和二次值关系
					CIecCfgPrimRate *pIecCfgPrimRate = (CIecCfgPrimRate *)pIecCfgPrimRates->FindByID(strPrimRate);

		 			float fPrimValue = bIsUCh ? pIecCfgPrimRate->m_fPrimValue*1000 : pIecCfgPrimRate->m_fPrimValue;
		 			float fSecondValue = pIecCfgPrimRate->m_fSecondValue;

					if(bIsUCh)
					{
						fValue = pCh->CalcChannelMaxValue();
						fValue = fValue*(fPrimValue/fSecondValue)/fRate;

						if (fValue > fUMax)
						{
							fUMax = fValue;
						}
					}
					else
					{
						fValue = pCh->CalcChannelMaxValue();
						fValue = fValue*(fPrimValue/fSecondValue)/fRate;

						if (fValue >fIMax)
						{
							fIMax = fValue;
						}
					}
				
				}
// 				else if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
// 				{
// 					if(bIsUCh)
// 					{
// 						fValue = pCh->CalcChannelMaxValue();
// // 						fValue = fValue*(fPrimValue/fSecondValue)/fRate;
// 
// 						if (fValue > fUMax)
// 						{
// 							fUMax = fValue;
// 						}
// 					}
// 					else
// 					{
// 						fValue = pCh->CalcChannelMaxValue();
// // 						fValue = fValue*(fPrimValue/fSecondValue)/fRate;
// 
// 						if (fValue >fIMax)
// 						{
// 							fIMax = fValue;
// 						}
// 					}
// 				}
// 				else if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
// 				{
// 					if(bIsUCh)
// 					{
// 						fValue = pCh->CalcChannelMaxValue();
// 						// 						fValue = fValue*(fPrimValue/fSecondValue)/fRate;
// 
// 						if (fValue > fUMax)
// 						{
// 							fUMax = fValue;
// 						}
// 					}
// 					else
// 					{
// 						fValue = pCh->CalcChannelMaxValue();
// 						// 						fValue = fValue*(fPrimValue/fSecondValue)/fRate;
// 
// 						if (fValue >fIMax)
// 						{
// 							fIMax = fValue;
// 						}
// 					}
// 				}

				nChIndex++;
			}

		}
	}

}

void CComtradePlayConfig::CalcReplayChMaxValue()
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	double fValue = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);

		if(!pModule->IsBinaryTypeModule())
		{
		if (!pModule->IsModuleSelected())
		{
			continue;
		}
		pModule->CalcChMaxValueByIndex(-1);
	}
	}

	//界面定时器检查标记，刷新界面和波形
	m_nReplayBufFlush = CMTRD_FLUSH_TYPE_FlushAll;
}

void CComtradePlayConfig::CalcReplayChUMaxValue()
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	double fValue = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
		if (!pModule->IsModuleSelected())
		{
			continue;
		}

		pModule->CalcChMaxValueByIndex(-1);
	}
	}

	m_nReplayBufFlush = CMTRD_FLUSH_TYPE_FlushUModule;
}

void CComtradePlayConfig::CalcReplayChIMaxValue()
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
		if (!pModule->IsModuleSelected())
		{
			continue;
		}

		pModule->CalcChMaxValueByIndex(-1);
	}
	}

	m_nReplayBufFlush = CMTRD_FLUSH_TYPE_FlushIModule;
}

void CComtradePlayConfig::CalcReplayChMaxValue(int nModuleIndex,int nChIndex)
{
	ASSERT(nModuleIndex >= 0);
	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetAt(nModuleIndex);
	if(!pModule->IsBinaryTypeModule())
	{
	pModule->CalcChMaxValueByIndex(nChIndex);
	}
}

long CComtradePlayConfig::GetReplayBufPoints()
{
	CSttModuleComtradeBind *pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetHead();

	if (pModule == NULL)
	{
		return 0;
	}

	if(pModule->IsBinaryTypeModule())
	{
		return pModule->m_pReplayBufBinary1->GetDataLength();
	}
	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)pModule->GetHead();

	if (pCh == NULL)
	{
		return 0;
	}

	return pCh->m_pReplayBuf->GetDataLength();
}

//获取指定时间点各通道瞬时值
void CComtradePlayConfig::GetReplayBufFixedMomentaryVal(double fStartTime,double fFixTime,double fSampleFreq)
{
	int nPointIndex = (int)((fFixTime - fStartTime) * fSampleFreq);

	if (GetReplayBufPoints() <= nPointIndex)
	{//异常
		return;
	}

	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	float *pBuf = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
		if(!pModule->IsBinaryTypeModule())
		{
		POS posCh = pModule->GetHeadPosition();

		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

			if (pCh->m_pReplayBuf == NULL)
			{
				return;
			}

			pBuf = pCh->m_pReplayBuf->GetBuffer_float();
			pCh->m_fMomentaryVal = pBuf[nPointIndex];
		}
	}

	}
}

BOOL CComtradePlayConfig::HasLoopData()
{
	BOOL bRet = TRUE;

#ifdef _PSX_IDE_QT_
	if (m_nTriggerType == COMTRADE_TRIGGRE_TYPE_No)
	{
		if (m_nStartCycleNum == 0)
		{
			bRet = FALSE;
		}
	}
#endif

	return bRet;
}

#ifdef _PSX_IDE_QT_
//由配置对象生成tmt结构体
void CComtradePlayConfig::GenerateReplayTestParas(tmt_ReplayParas &oReplayParas,long nSampleFreq)
{
	oReplayParas.init();

	oReplayParas.m_nSampleFreq = nSampleFreq;
	oReplayParas.m_nTripType = m_nTriggerType;
	oReplayParas.m_tGps = m_tGps;
// 	oReplayParas.m_nTrigTimeS = m_nTrigTimeS;
// 	oReplayParas.m_nTrigTimeNS = m_nTrigTimeNS;
	oReplayParas.m_nStartCycleNum = m_nStartCycleNum;
	oReplayParas.m_nTrigAfterMode = m_nTrigAfterMode;

	//chenling20230531
	oReplayParas.m_fCT_Prim=m_fCTRatio[0];
	oReplayParas.m_fCT_Second=m_fCTRatio[1] ;
	oReplayParas.m_fPT_Prim=m_fPTRatio[0] ;
	oReplayParas.m_fPT_Second=m_fPTRatio[1];

	memcpy(oReplayParas.m_binIn,m_oBinaryConfig.m_binIn,sizeof(tmt_BinaryIn)*MAX_BINARYIN_COUNT);
	memcpy(oReplayParas.m_binInEx,m_oBinaryConfig.m_binInEx,sizeof(tmt_BinaryIn)*MAX_ExBINARY_COUNT);
	oReplayParas.m_nBinLogic = m_oBinaryConfig.m_nBinLogic; 

	oReplayParas.m_nModuleCount = m_oSttModulesComtradeBind.GetCount();

	CString_to_char(g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.m_strComtradeFile,
		oReplayParas.m_pszComtradeFilePath);

	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;
	int nModuleIndex = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);

		oReplayParas.m_oModule[nModuleIndex].m_nIndex = pModule->m_nModulePos;
		oReplayParas.m_oModule[nModuleIndex].m_nChUseCount = pModule->GetCount();

		if(pModule->IsBinaryTypeModule())
		{
			POS posCh = pModule->GetHeadPosition();
			int nChIndex = 0;				
			oReplayParas.m_oModule[nModuleIndex].m_nModuleType = REPLAY_MODULE_TYPE_BINARY;
			while(posCh)
			{
				pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
				oReplayParas.m_oModule[nModuleIndex].m_oBinaryChMap[nChIndex].m_nBinaryChSel = pBinaryCh->m_nChState;
				oReplayParas.m_oModule[nModuleIndex].m_oBinaryChMap[nChIndex].m_nBinaryCh_Index = pBinaryCh->m_nBinaryCh_Index;

				//2024-3-28 wuxinyi 当开出量有通道映射时，该模块才需要下发
				if(pBinaryCh->m_nBinaryCh_Index > 0)
				{
					oReplayParas.m_oModule[nModuleIndex].m_nSel = 1;
				}
				nChIndex++;
			}
		}
		else if(pModule->IsDigitalTypeModule())
		{
			if (pModule->IsModuleSelected())
			{
				oReplayParas.m_oModule[nModuleIndex].m_nSel = 1;
			}
			else
			{
				oReplayParas.m_oModule[nModuleIndex].m_nSel = 0;
			}
			int nChUseCount = 0;
			oReplayParas.m_oModule[nModuleIndex].m_nModuleType = REPLAY_MODULE_TYPE_DIGITAL;
			POS posCh = pModule->GetHeadPosition();
			while(posCh != NULL)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);
				CString_to_char(pCh->m_strID,oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_strChID);
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nChSel = pCh->m_nChSelected;
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nChA_Index = pCh->m_nChA_Index/*m_nComtradeChID_A*/;
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nChB_Index = pCh->m_nChB_Index/*m_nComtradeChID_B*/;
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_fChRate = pCh->m_dK;

				//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ID=%s;Name=%s;ComtradeChID_A=%s"),pCh->m_strID.GetString(),pCh->m_strName.GetString(),pCh->m_strComtradeChID_A.GetString());
				nChUseCount++;
			}
			oReplayParas.m_oModule[nModuleIndex].m_nChUseCount = nChUseCount;
		}
		else if(pModule->IsWeekTypeModule())
		{
			if (pModule->IsModuleSelected())
			{
				oReplayParas.m_oModule[nModuleIndex].m_nSel = 1;
			}
			else
			{
				oReplayParas.m_oModule[nModuleIndex].m_nSel = 0;
			}
			int nChUseCount = 0;
			oReplayParas.m_oModule[nModuleIndex].m_nModuleType = REPLAY_MODULE_TYPE_WEEK;
			POS posCh = pModule->GetHeadPosition();

			//弱信号变比
			oReplayParas.m_oModule[nModuleIndex].m_fCT_Prim = pModule->m_fCTRatio[0];
			oReplayParas.m_oModule[nModuleIndex].m_fCT_Second = pModule->m_fCTRatio[1] ;
			oReplayParas.m_oModule[nModuleIndex].m_fPT_Prim = pModule->m_fPTRatio[0] ;
			oReplayParas.m_oModule[nModuleIndex].m_fPT_Second = pModule->m_fPTRatio[1];

			while(posCh != NULL)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);
				CString_to_char(pCh->m_strID,oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_strChID);
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nChSel = pCh->m_nChSelected;
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nChA_Index = pCh->m_nChA_Index/*m_nComtradeChID_A*/;
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nChB_Index = pCh->m_nChB_Index/*m_nComtradeChID_B*/;
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_fChRate = pCh->m_dK;

				int nEleType = pCh->GetEleTypeIndex();
				oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChUseCount].m_nEeType = nEleType;
				nChUseCount++;
			}
			oReplayParas.m_oModule[nModuleIndex].m_nChUseCount = nChUseCount;


		}
		else
		{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("GenerateReplayTestParas(nModuleIndex=%d,Pos=%ld,m_nChUseCount=%ld,m_nSel=%d)"),
// 			nModuleIndex,pModule->m_nModulePos,oReplayParas.m_oModule[nModuleIndex].m_nChUseCount,oReplayParas.m_oModule[nModuleIndex].m_nSel);
			if (pModule->IsModuleSelected())
			{
				oReplayParas.m_oModule[nModuleIndex].m_nSel = 1;
			}
			else
			{
				oReplayParas.m_oModule[nModuleIndex].m_nSel = 0;
			}
			POS posCh = pModule->GetHeadPosition();
			int nChIndex = 0;			
			oReplayParas.m_oModule[nModuleIndex].m_nModuleType = REPLAY_MODULE_TYPE_ANALOG;

		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);
			CString_to_char(pCh->m_strID,oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChIndex].m_strChID);
			oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChSel = pCh->m_nChSelected;
	                oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChA_Index = pCh->m_nChA_Index/*m_nComtradeChID_A*/;
			oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChB_Index = pCh->m_nChB_Index/*m_nComtradeChID_B*/;
			oReplayParas.m_oModule[nModuleIndex].m_oChMap[nChIndex].m_fChRate = pCh->m_dK;

	//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ID=%s;Name=%s;ComtradeChID_A=%s"),pCh->m_strID.GetString(),pCh->m_strName.GetString(),pCh->m_strComtradeChID_A.GetString());
			nChIndex++;
		}
		}
		nModuleIndex++;
	}
	//2024-01-19 wuxinyi 波形编辑数据
	m_oWaveEditParas.CloneOwn(&oReplayParas.m_oWaveEditPara);

	//主板开出量
	pModule = GetBinaryModule();
	if(pModule)
	{
		oReplayParas.m_bUseBinaryModule = m_oSttModulesComtradeBind.m_nUseBinaryModule;
		oReplayParas.m_oBinaryModule.m_nChUseCount = m_oSttModulesComtradeBind.m_pBinaryModuleComtradeBind->GetCount();
		POS posCh = m_oSttModulesComtradeBind.m_pBinaryModuleComtradeBind->GetHeadPosition();
		int nChIndex = 0;				
		while(posCh)
		{
			pBinaryCh = (CSttModuleBinaryChComtradeBind *)pModule->GetNext(posCh);
			oReplayParas.m_oBinaryModule.m_oChMap[nChIndex].m_nBinaryCh_Index = pBinaryCh->m_nBinaryCh_Index;
			oReplayParas.m_oBinaryModule.m_oChMap[nChIndex].m_nBinaryChSel = pBinaryCh->m_nChState;
			nChIndex++;
		}
	}

// 	m_oBinaryModuleParas.CloneOwn(&oReplayParas.m_oBinaryModule);

}

void CComtradePlayConfig::GenerateReplayConfigFromTMT(tmt_ReplayParas *pReplayParas,BOOL bUpdateChMapConfig)
{
	InitDefault();
	m_nTriggerType = pReplayParas->m_nTripType;
	m_tGps = pReplayParas->m_tGps;
// 	m_nTrigTimeS = pReplayParas->m_nTrigTimeS;
// 	m_nTrigTimeNS = pReplayParas->m_nTrigTimeNS;
	m_nStartCycleNum = pReplayParas->m_nStartCycleNum;
	m_nTrigAfterMode = pReplayParas->m_nTrigAfterMode;

	memcpy(m_oBinaryConfig.m_binIn,pReplayParas->m_binIn,sizeof(tmt_BinaryIn)*MAX_BINARYIN_COUNT);
	memcpy(m_oBinaryConfig.m_binInEx,pReplayParas->m_binInEx,sizeof(tmt_BinaryIn)*MAX_ExBINARY_COUNT);
	m_oBinaryConfig.m_nBinLogic = pReplayParas->m_nBinLogic; 

	m_fCTRatio[0] = pReplayParas->m_fCT_Prim;
	m_fCTRatio[1] = pReplayParas->m_fCT_Second;
	m_fPTRatio[0] = pReplayParas->m_fPT_Prim;
	m_fPTRatio[1] = pReplayParas->m_fPT_Second;
	
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_oSrcComtradeFile.m_strComtradeFile
		= pReplayParas->m_pszComtradeFilePath;

	if (bUpdateChMapConfig)
	{
	m_oSttModulesComtradeBind.DeleteAll();
	}

	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	CSttModuleBinaryChComtradeBind *pBinaryCh = NULL;

	CDvmData *pDvmData = NULL;
	CString strModuleID,strChID;
	int nBinaryModuleIndex = 0, nAnlogModuleIndex = 0,nDigitalModuleIndex = 0, nWeekModuleIndex = 0;

	for (int nModuleIndex = 0;nModuleIndex<pReplayParas->m_nModuleCount;nModuleIndex++)
	{
		if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG)
		{
		strModuleID.Format(_T("Module%ld"),nAnlogModuleIndex++);
		pModule = (CSttModuleComtradeBind*)m_oSttModulesComtradeBind.FindByModuleID(strModuleID);

			if(pModule == NULL)
			{
				pModule = new CSttModuleComtradeBind;
				pModule->m_strName.Format(_T("模块%ld"),nAnlogModuleIndex);
				pModule->m_strID.Format(_T("Module%ld"),nAnlogModuleIndex);
				m_oSttModulesComtradeBind.AddNewChild(pModule);
			}
		}
		else if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_BINARY)
		{
			strModuleID.Format(_T("BinaryModuleEx%ld"),nBinaryModuleIndex++);
			pModule = (CSttModuleComtradeBind*)m_oSttModulesComtradeBind.FindByModuleID(strModuleID);

		if(pModule == NULL)
		{
		pModule = new CSttModuleComtradeBind;
				pModule->m_strName.Format(_T("开出模块%ld"),nBinaryModuleIndex);
				pModule->m_strID.Format(_T("BinaryModuleEx%ld"),nBinaryModuleIndex);
			m_oSttModulesComtradeBind.AddNewChild(pModule);
		}
		}
		else if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_DIGITAL)
		{
			strModuleID.Format(_T("DigitalModule%ld"),nDigitalModuleIndex++);
			pModule = (CSttModuleComtradeBind*)m_oSttModulesComtradeBind.FindByModuleID(strModuleID);

			if(pModule == NULL)
			{
				pModule = new CSttModuleComtradeBind;
				pModule->m_strName.Format(_T("数字量模块%ld"),nDigitalModuleIndex);
				pModule->m_strID.Format(_T("DigitalModule%ld"),nDigitalModuleIndex);
				m_oSttModulesComtradeBind.AddNewChild(pModule);
			}
		}
		else if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
		{
			strModuleID.Format(_T("WeekModule%d"),++nWeekModuleIndex);
			pModule = (CSttModuleComtradeBind*)m_oSttModulesComtradeBind.FindByModuleID(strModuleID);

			if(pModule == NULL)
			{
				pModule = new CSttModuleComtradeBind;
				pModule->m_strName.Format(_T("弱信号模块%d"),nWeekModuleIndex);
				pModule->m_strID.Format(_T("WeekModule%d"),nWeekModuleIndex);
				m_oSttModulesComtradeBind.AddNewChild(pModule);
			}
		}

// 		if(pModule == NULL)
// 		{
// 			pModule = new CSttModuleComtradeBind;
// 			pModule->m_strName.Format(_T("模块%ld"),nModuleIndex);
// 			pModule->m_strID.Format(_T("Module%ld"),nModuleIndex);
// 			m_oSttModulesComtradeBind.AddNewChild(pModule);
// 		}

		pModule->m_nModulePos = pReplayParas->m_oModule[nModuleIndex].m_nIndex;

		//ASSERT (FALSE);
// 		if (pReplayParas->m_oModule[nModuleIndex].m_oChMap[0].m_strChID[0] == 'U')
// 		{
// 			pModule->m_strDataType = _T("U");
// 		} 
// 		else
// 		{
// 			pModule->m_strDataType = _T("I");
// 		}
		if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_BINARY)
		{
			for (int nChIndex = 0;nChIndex<pReplayParas->m_oModule[nModuleIndex].m_nChUseCount;nChIndex++)
			{
				strChID.Format(_T("BinaryExCh%d"),nChIndex);
				pBinaryCh = (CSttModuleBinaryChComtradeBind*)pModule->FindByID(strChID);
				if (pBinaryCh == NULL)
				{
					pBinaryCh = new CSttModuleBinaryChComtradeBind;
					pBinaryCh->m_strName.Format(_T("开出通道%d"),nChIndex+1);
					pBinaryCh->m_strID.Format(_T("BinaryExCh%d"),nChIndex+1);
					pModule->AddNewChild(pBinaryCh);
				}
				pBinaryCh->m_nBinaryCh_Index = pReplayParas->m_oModule[nModuleIndex].m_oBinaryChMap[nChIndex].m_nBinaryCh_Index;
				pBinaryCh->m_nChState = pReplayParas->m_oModule[nModuleIndex].m_oBinaryChMap[nChIndex].m_nBinaryChSel;
			}
		}
		else if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_DIGITAL)
		{
			int nDigitalChNum = 0;
			char strChIDName[3] = {'a','b','c'};
			int nGroupNum = 1;

			for(int nChIndex = 0;nChIndex < REPLAY_DIGITAL_MODULE_CH_NUM;nChIndex++ )
			{
				strChID.Format(_T("DigitalCh%d"),nChIndex);
				pCh = (CSttModuleChComtradeBind*)pModule->FindByID(strChID);
				if (pCh == NULL)
				{
					pCh = new CSttModuleChComtradeBind;
					if(nChIndex <6)
					{
						if(nChIndex < 3)
						{
							pCh->m_strName.Format(_T("U%c%d"), strChIDName[nChIndex%3] ,nGroupNum);
						}
						else
						{
							pCh->m_strName.Format(_T("I%c%d"), strChIDName[nChIndex%3] ,nGroupNum);
						}
					}
					else if(nChIndex >= 6 && nChIndex <12)//第二组
					{
						if(nChIndex < 9)
						{
							pCh->m_strName.Format(_T("U%c%d"), strChIDName[nChIndex%3] ,nGroupNum+1);
						}
						else
						{
							pCh->m_strName.Format(_T("I%c%d"), strChIDName[nChIndex%3] ,nGroupNum+1);
						}
					}
					pCh->m_strID = strChID;
					pModule->AddNewChild(pCh);
				}

				pCh->m_nChSelected = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChSel;
				pCh->m_nChA_Index = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChA_Index;
				pCh->m_nChB_Index = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChB_Index;
				pCh->m_dK = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_fChRate;
			
			}
		}
		else
		{
			if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
			{
				//弱信号变比
				pModule->m_fCTRatio[0] = pReplayParas->m_oModule[nModuleIndex].m_fCT_Prim;
				pModule->m_fCTRatio[1] = pReplayParas->m_oModule[nModuleIndex].m_fCT_Second ;
				pModule->m_fPTRatio[0] = pReplayParas->m_oModule[nModuleIndex].m_fPT_Prim ;
				pModule->m_fPTRatio[1] = pReplayParas->m_oModule[nModuleIndex].m_fPT_Second;
			}

		for (int nChIndex = 0;nChIndex<pReplayParas->m_oModule[nModuleIndex].m_nChUseCount;nChIndex++)
		{
			strChID = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_strChID;
			pCh = (CSttModuleChComtradeBind*)pModule->FindByID(strChID);

			if (pCh == NULL)
			{
			pCh = new CSttModuleChComtradeBind;
			pCh->m_strName.Format(_T("通道%d"),nChIndex+1);
			pCh->m_strID.Format(_T("%s"),pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_strChID);
				pModule->AddNewChild(pCh);
			}

			pCh->m_nChSelected = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChSel;
			pCh->m_nChA_Index = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChA_Index;
			pCh->m_nChB_Index = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nChB_Index;
			pCh->m_dK = pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_fChRate;

				//弱信号通道类型可变再赋值
				if(pReplayParas->m_oModule[nModuleIndex].m_nModuleType == REPLAY_MODULE_TYPE_WEEK && pModule->IsWeekChTypeChg())
				{
// 					CString strValue = (pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nEeType == REPLAY_WEEK_CH_ELETYPE_VOL) ? 
// 											STT_REPLAY_WEEK_MODULE_CH_EeType_VOL : STT_REPLAY_WEEK_MODULE_CH_EeType_Curr;
// 					pCh->m_pHdChRef->SetDataValue(_T("EeType"),strValue);
					pCh->SetEleType(pReplayParas->m_oModule[nModuleIndex].m_oChMap[nChIndex].m_nEeType);
				}
	/*
			pCh->m_strValue = _T("1");
			pDvmData = new CDvmData;
			pDvmData->m_strID = _T("A");
			pDvmData->m_strValue = _T("1");
			pCh->AddNewChild(pDvmData);
			pDvmData = new CDvmData;
			pDvmData->m_strID = _T("B");
			pDvmData->m_strValue = _T("0");
			pCh->AddNewChild(pDvmData);
			pDvmData = new CDvmData;
			pDvmData->m_strID = _T("计算系数");
			pDvmData->m_strID = _T("K");
			pDvmData->m_strValue = _T("1.0");
			pCh->AddNewChild(pDvmData);
			pDvmData = new CDvmData;
			pDvmData->m_strID = _T("瞬时值");
			pDvmData->m_strID = _T("MomentaryVal");
			pDvmData->m_strValue = _T("0");
			pCh->AddNewChild(pDvmData);
	*/
		}
	}

	}

	//2024-01-19 wuxinyi 波形编辑数据
	pReplayParas->m_oWaveEditPara.CloneOwn(&m_oWaveEditParas);	

	//主板开出模块
	m_oSttModulesComtradeBind.m_nUseBinaryModule = pReplayParas->m_bUseBinaryModule;
	pModule = GetBinaryModule();
	if(pModule == NULL)
	{
		pModule = new CSttModuleComtradeBind;
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.m_pBinaryModuleComtradeBind = pModule;
	}		

		pModule->m_strName = _T("主板开出模块");
	pModule->m_strModuleID = _T("BinaryModule");
	if(pModule->m_pReplayBufBinary1 == NULL || pModule->m_pReplayBufBinary2 == NULL)
	{
		pModule->m_pReplayBufBinary1 = new CComplexMemBuffer_Float();
		pModule->m_pReplayBufBinary2 = new CComplexMemBuffer_Float();
	}

	for(int nChIndex = 0; nChIndex < pReplayParas->m_oBinaryModule.m_nChUseCount; nChIndex++)
	{
		strChID.Format(_T("BinaryCh%d"),nChIndex);
		pBinaryCh = (CSttModuleBinaryChComtradeBind*)pModule->FindByID(strChID);
		if (pBinaryCh == NULL)
		{
			pBinaryCh = new CSttModuleBinaryChComtradeBind;
			pBinaryCh->m_strName.Format(_T("开出通道%d"),nChIndex);
			pBinaryCh->m_strID.Format(_T("BinaryCh%d"),nChIndex);
			pModule->AddNewChild(pBinaryCh);
		}
		pBinaryCh->m_nBinaryCh_Index = pReplayParas->m_oBinaryModule.m_oChMap[nChIndex].m_nBinaryCh_Index;
		pBinaryCh->m_nChState = pReplayParas->m_oBinaryModule.m_oChMap[nChIndex].m_nBinaryChSel;

	}

}
#endif

long CComtradePlayConfig::GetTotalChs_SelectedModule()
{
#ifdef _PSX_IDE_QT_
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	long nChs = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);

		if (!pModule->IsModuleSelected())
		{
			continue;
		}

		if(/*!pModule->IsBinaryTypeModule()*/
			(pModule->IsAnalogTypeModule() && g_oSystemParas.m_nHasAnalog)||
			(pModule->IsDigitalTypeModule() && g_oSystemParas.m_nHasDigital)||
			(pModule->IsWeekTypeModule() && g_oSystemParas.m_nHasWeek))
		{			
		POS posCh = pModule->GetHeadPosition();

		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

			if (pCh->m_nChSelected)
			{
				nChs++;
			}
		}
	}
		else if(pModule->IsBinaryTypeModule())
		{
			//开出量回放缓存通道目前只有两条
			nChs += 2;
		}
	}
	if(/*m_oSttModulesComtradeBind.m_nUseBinaryModule == 1*/m_oSttModulesComtradeBind.IsBinaryModuleSelected())//主板开出通道
	{
		nChs += 2;
	}

	return nChs;
#else
	return -1;
#endif
}

// void CComtradePlayConfig::GetTotalChs_SelectedModule(CExBaseList &oModuleChsRef)
// {
// 	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
// 	CSttModuleComtradeBind *pModule = NULL;
// 	CSttModuleChComtradeBind *pCh = NULL;
// 
// 	while(pos != NULL)
// 	{
// 		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);
// 
// 		if (!pModule->IsModuleSelected())
// 		{
// 			continue;
// 		}
// 
// 		POS posCh = pModule->GetHeadPosition();
// 
// 		while(posCh != NULL)
// 		{
// 			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);
// 			oModuleChsRef.AddTail(pCh);
// 		}
// 	}
// }

void CComtradePlayConfig::GetTotalChs_SelectedModule(float ***pppdChValue)  //zhouhj 20211105 修改为全部通道都获取,不仅仅选择的通道
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	int nChIndex = 0;

	float **ppPre = *pppdChValue;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);

		if (!pModule->IsModuleSelected())
		{
			continue;
		}

		if(/*!pModule->IsBinaryTypeModule()*/
			(pModule->IsAnalogTypeModule() && g_oSystemParas.m_nHasAnalog)||
			(pModule->IsDigitalTypeModule() && g_oSystemParas.m_nHasDigital)||
			(pModule->IsWeekTypeModule() && g_oSystemParas.m_nHasWeek))
		{
		POS posCh = pModule->GetHeadPosition();

		while(posCh != NULL)
		{
			pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);

			if (pCh->IsChannelSelected())
			{
				**pppdChValue = pCh->m_pReplayBuf->GetBuffer_float();
				(*pppdChValue)++;
			}
// 			else
// 			{
// 				**pppdChValue = NULL;
// 			}
			
		}
	}
		else if(pModule->IsBinaryTypeModule())
		{
			**pppdChValue = pModule->m_pReplayBufBinary1->GetBuffer_float();
			(*pppdChValue)++;
			**pppdChValue = pModule->m_pReplayBufBinary2->GetBuffer_float();
			(*pppdChValue)++;
		}
	}
	if(/*m_oSttModulesComtradeBind.m_nUseBinaryModule == 1*/m_oSttModulesComtradeBind.IsBinaryModuleSelected())
	{
		CSttModuleComtradeBind *pModule = GetBinaryModule();
		**pppdChValue = pModule->m_pReplayBufBinary1->GetBuffer_float();
		(*pppdChValue)++;
		**pppdChValue = pModule->m_pReplayBufBinary2->GetBuffer_float();
		(*pppdChValue)++;

	}

	*pppdChValue = ppPre;
}

/////////////////////////
BOOL CComtradePlayConfig::CopyOwn(CBaseObject* pDest)
{
	CExBaseObject::CopyOwn(pDest);

	CComtradePlayConfig *p = (CComtradePlayConfig*)pDest;

	 p->m_nTriggerType =m_nTriggerType;
	 p->m_tGps = m_tGps;
// 	 p->m_nTrigTimeS = m_nTrigTimeS;
// 	 p->m_nTrigTimeNS = m_nTrigTimeNS;
	 p->m_nStartCycleNum = m_nStartCycleNum;
	 p->m_nTrigAfterMode = m_nTrigAfterMode;
	 p->m_fPTRatio[0] = m_fPTRatio[0];
	 p->m_fPTRatio[1] = m_fPTRatio[1];
	 p->m_fCTRatio[0] = m_fCTRatio[0];
	 p->m_fCTRatio[1] = m_fCTRatio[1];

	p->m_oBinaryConfig.m_nBinLogic = m_oBinaryConfig.m_nBinLogic;

	CString strID;
	CDataGroup *pGroup = (CDataGroup *)FindByID(_T("Bin"));
	if (pGroup != NULL)
	{
		char pszBInName[MAX_BINARYIN_COUNT+1]="ABCDEFGHIJKLMNOPQRST";
		for (int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			p->m_oBinaryConfig.m_binIn[i].nSelect = m_oBinaryConfig.m_binIn[i].nSelect;
		}
	}

	return TRUE;
}

CBaseObject* CComtradePlayConfig::Clone()
{
	CComtradePlayConfig *p = new CComtradePlayConfig();
	Copy(p);
	return p;
}

CBaseObject* CComtradePlayConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CComtradePlayConfig *p = new CComtradePlayConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CComtradePlayConfig::CanPaste(UINT nClassID)
{
	return FALSE;
}


long CComtradePlayConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CComtradePlayConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}


CExBaseObject* CComtradePlayConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmtrdCfgDefineXmlRWKeys *pXmlKeys = (CSttCmtrdCfgDefineXmlRWKeys*)pXmlRWKeys;

// 	if (strClassID == pXmlKeys->m_strCSttMapGroupKey)
// 	{
// 		return new CSttComtradeGroup();
// 	}
// 	else
// 	{
// 		return CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlKeys);
// 	}
	return NULL;
}

CExBaseObject* CComtradePlayConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
// 	if (nClassID == MNGRCLASSID_CSTTMAPGROUP)
// 	{
// 		return new CSttComtradeGroup();
// 	}
// 	else
// 	{
// 		return CDataGroup::CreateNewChild(nClassID);
// 	}
	return NULL;
}

BOOL CComtradePlayConfig::Open(const CString &strFile, double &fSampleFreq)
{
	++CSttCmtrdCfgDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = OpenXmlFile(strFile,CSttCmtrdCfgDefineXmlRWKeys::g_pXmlKeys,_PUGI_XML_TYPE_);
	--CSttCmtrdCfgDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	if (!bRet)
	{
		return FALSE;
	}

	CopyOwn(this);

	return TRUE;
}

BOOL CComtradePlayConfig::Save(const CString &strFile, double fSampleFreq)
{
	m_fSampleFreq = fSampleFreq;

// 	CString strID;
// 	CDataGroup *pGroup = (CDataGroup *)FindByID(_T("Bin"));
// 	if (pGroup != NULL)
// 	{
// 		char pszBInName[MAX_BINARYIN_COUNT+1]="ABCDEFGHIJKLMNOPQRST";
// 		for (int i=0; i<MAX_BINARYIN_COUNT; i++)
// 		{
// 			strID.Format(_T("Bin%c"),pszBInName[i]);
// 			Stt_SetDataAttr(pGroup,strID, m_oBinaryConfig.m_binIn[i].nSelect);
// 		}
// 	}

	return SaveXmlFile(strFile,CSttCmtrdCfgDefineXmlRWKeys::g_pXmlKeys,_PUGI_XML_TYPE_);
}

CSttModuleComtradeBind * CComtradePlayConfig::GetBinaryModule()
{
	return m_oSttModulesComtradeBind.GetBinaryModule();
}


int CComtradePlayConfig::GetFT3MaxCodeValue( int nChannelGroupIndex, CSttModuleChComtradeBind *pCh )
{
	if(!pCh)
	{
		return -1;
	}
	int nMaxCode = -1;

	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV* pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgSmvRates* pIecCfgDatasSMVRates = pIecCfgDatasSMV->GetIecCfgSmvRates();

	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	int nCodeValue = 0;

	CStringArray ChNameList;
	CString strCodeName;

	if (nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP) 
	{
		ChNameList.Add( _T("Ia1"));
		ChNameList.Add( _T("Ib1"));
		ChNameList.Add( _T("Ic1"));
		ChNameList.Add( _T("Ua1"));
		ChNameList.Add( _T("Ub1"));
		ChNameList.Add( _T("Uc1"));
		strCodeName = (pCh->IsModuleType_U()) ? _T("Uabcz") : _T("Iabc");
	} 
	else 
	{
		ChNameList.Add(_T("Ia2"));
		ChNameList.Add(_T("Ib2"));
		ChNameList.Add(_T("Ic2"));
		ChNameList.Add(_T("Ua2"));
		ChNameList.Add(_T("Ub2"));
		ChNameList.Add(_T("Uc2"));
		strCodeName = (pCh->IsModuleType_U()) ? _T("Up-abcz") : _T("Ip-abc");
	}
	

	CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate *)pIecCfgDatasSMVRates->FindByID(strCodeName);
	if(!pIecCfgSmvRate)
	{
		return -1 ;
	}

	CExBaseObject *pCurObj = NULL;

	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCurObj;
			if(pIecCfg6044CommonData->m_nUseFlag == 0)
			{
				continue;
			}

			POS pos1 = pIecCfg6044CommonData->m_pCfgChs->GetHeadPosition();
			while(pos1)
			{
				CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pIecCfg6044CommonData->m_pCfgChs->GetNext(pos1);

				if(!FindInCStringArry(ChNameList,pIecCfg6044CommonCh->m_strAppChID))
				{
					continue;
				}
				if(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol && (pCh->IsModuleType_U()))
				{		
					nCodeValue = pIecCfgSmvRate->m_nCodeValue;//保护码值
					nMaxCode = max(nCodeValue,nMaxCode);
				}
				else if(pCh->IsModuleType_I())
				{
					if(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
					{		
						nCodeValue = pIecCfgSmvRate->m_nMeasCurrCodeValue;//测量码值
						nMaxCode = max(nCodeValue,nMaxCode);
					}
					else if(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr || pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrProt)
					{
						nCodeValue = pIecCfgSmvRate->m_nCodeValue;//保护码值
						nMaxCode = max(nCodeValue,nMaxCode);
					}
				}
			}
		}
	}
	return nMaxCode;
}

bool CComtradePlayConfig::CalDigitalChMaxValue( CSttModuleChComtradeBind *pCh, int nChannelGroupIndex )
{
	if(!pCh || nChannelGroupIndex <0)
	{
		return false;
	}

	bool bRes = true;
	unsigned long nMaxValue = 0x0000;
	bool bIsUCh = pCh->IsModuleType_U()?TRUE:FALSE;
	double fMax = pCh->CalcChannelMaxValue();

	CString strRateName, strPrimRate;
	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV *pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgSysParas *pIecCfgSysParas = pIecCfgDatasMngr->GetSysParasMngr();
	CIecCfgSmvRates *pIecCfgDatasSMVRates = pIecCfgDatasSMV->GetIecCfgSmvRates();
	CIecCfgPrimRates *pIecCfgPrimRates = (CIecCfgPrimRates *)pIecCfgSysParas->GetPrimRates();

// 	if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_61850_92)
// 	{	
// 		if(nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
// 		{	
// 			strRateName = bIsUCh ? _T("Uabcz") : _T("Iabc");
// 			strPrimRate = bIsUCh ? _T("U1-abc") : _T("I1-abc");
// 		}
// 		else
// 		{
// 			strRateName = bIsUCh ? _T("Up-abcz") : _T("Ip-abc");
// 			strPrimRate = bIsUCh ? _T("U2-abc") : _T("I2-abc");
// 		}
// 		//比例因子
// 		float fRate = pIecCfgDatasSMVRates->GetSmvRate(strRateName);
// 
// 		//一次值和二次值关系
// 		CIecCfgPrimRate *pIecCfgPrimRate = (CIecCfgPrimRate *)pIecCfgPrimRates->FindByID(strPrimRate);
// 		float fPrimValue = bIsUCh ? pIecCfgPrimRate->m_fPrimValue*1000 : pIecCfgPrimRate->m_fPrimValue;
// 		float fSecondValue = pIecCfgPrimRate->m_fSecondValue;
// 
// 		//最大值
// 		nMaxValue = fMax*(fPrimValue/fSecondValue)/fRate;
// 
// 		//9-2限制四个字节
// 		unsigned long n92MaxValue = 0x7FFFFFFF;
// 		if(nMaxValue > n92MaxValue)
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前9-2通道【%s】的实际输出值为【%x】,已超出最大输出值【%x】,请重新设置之后开始测试"),pCh->m_strName.GetString(),nMaxValue,n92MaxValue);
// 			return false;
// 		}
// 
// 	}
// 	else if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
	if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
		{

		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("wuwuwu---当前格式：FT3"));

		if(nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
		{
			strRateName = bIsUCh ? _T("Uabcz") : _T("Iabc");
		}
		else
		{
			strRateName = bIsUCh ? _T("Up-abcz") : _T("Ip-abc");
		}	

		//最小位宽
		int nMinSampLen = 3;
		POS pos = pIecCfgDatasSMV->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;
		CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;

		while (pos)
		{
			pCurObj=pIecCfgDatasSMV->GetNext(pos);
			if (pCurObj->GetClassID()==CFGCLASSID_CIECCFG6044COMMONDATA)
			{
				pIecCfg6044CommonData=(CIecCfg6044CommonData*)pCurObj;
				if (pIecCfg6044CommonData->m_nUseFlag == 1)
				{
                    int nSmpDataLen = pIecCfg6044CommonData->m_nSmpDataLen;
                    nMinSampLen = min(nSmpDataLen,nMinSampLen);
				}
			}
		}

		long n6044MaxValue = 0;
		switch (nMinSampLen) 
		{
		case 1:
			n6044MaxValue = 0x7F;
			break;
		case 2:
			n6044MaxValue = 0x7FFF;
			break;
		default:
			n6044MaxValue = 0x7FFFFF;
			break;
		}

		CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate *)pIecCfgDatasSMVRates->FindByID(strRateName);
		float fRateValue = bIsUCh ? pIecCfgSmvRate->m_fPrimValue*1000 : pIecCfgSmvRate->m_fPrimValue;//额定值
		int nMaxCodeValue = GetFT3MaxCodeValue(nChannelGroupIndex,pCh);//最大码值
		nMaxValue = fMax * nMaxCodeValue /fRateValue;//最大值

		if(nMaxValue > n6044MaxValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前FT3通道【%s】的实际输出值为【%x】,已超出最大输出值【%x】,请重新设置之后开始测试"),pCh->m_strName.GetString(),nMaxValue,n6044MaxValue);
			return false;
		}

	}
	else if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		if(nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
		{
			strRateName = bIsUCh ? _T("Us-abcz") : _T("I5-abc");
		}
		else
		{
			strRateName = bIsUCh ? _T("Ut-abcz") : _T("I6-abc");
		}			
		CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate *)pIecCfgDatasSMVRates->FindByID(strRateName);
		int nCodeValue = pIecCfgSmvRate->m_nCodeValue;//码值
		float fRateValue = bIsUCh ? pIecCfgSmvRate->m_fPrimValue*1000 : pIecCfgSmvRate->m_fPrimValue;//额定值
		nMaxValue = fMax * nCodeValue /fRateValue;//最大值

		//柔直FT3限制
		int nMinSampLen = 3;
		POS pos = pIecCfgDatasSMV->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;
		CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;

		while (pos)
		{
			pCurObj=pIecCfgDatasSMV->GetNext(pos);
			if (pCurObj->GetClassID()==CFGCLASSID_CIECCFG6044COMMONDATA)
			{
				pIecCfg6044CommonData=(CIecCfg6044CommonData*)pCurObj;
				if (pIecCfg6044CommonData->m_nUseFlag == 1)
				{
                    int nSmpDataLen = pIecCfg6044CommonData->m_nSmpDataLen;
                    nMinSampLen = min(nSmpDataLen,nMinSampLen);
				}
			}
		}
		long n6044MaxValue = 0;
		switch (nMinSampLen) 
		{
		case 1:
			n6044MaxValue = 0x7F;
			break;
		case 2:
			n6044MaxValue = 0x7FFF;
			break;
		default:
			n6044MaxValue = 0x7FFFFF;
			break;
		}

		if(nMaxValue > n6044MaxValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前柔直FT3通道【%s】的实际输出值为【%x】,已超出最大输出值【%x】,请重新设置之后开始测试"),pCh->m_strName.GetString(),nMaxValue,n6044MaxValue);
			return false;
		}
	}

	return bRes;
}

bool CComtradePlayConfig::VaildDigitalChMaxValue( CSttModuleComtradeBind *pModule )
{
	if(!pModule)
	{
		return false;
	}

	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = pModule->GetHeadPosition();
	int nChIndex = 0;

	while(pos)
	{	
		pCh = (CSttModuleChComtradeBind *)pModule->GetNext(pos);
		if (pCh->IsChannelSelected()) 
		{
			int nGroupIndex = (nChIndex < 6) ? DIGITAL_CH_MAP_FRIST_GROUP : DIGITAL_CH_MAP_SECOND_GROUP;
			if (!CalDigitalChMaxValue(pCh, nGroupIndex)) 
			{
				return false;
			}
		}
		nChIndex++;
	}
	return true;
}

bool CComtradePlayConfig::VaildDigitalChMaxValue()
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);

		if(pModule->IsModuleSelected() && pModule->IsDigitalTypeModule())
		{
			if(!VaildDigitalChMaxValue(pModule))
			{
				return false;
			}
		}
	}

	return true;
}


bool CComtradePlayConfig::VaildWeekChMaxValue()
{
	POS pos = m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	float fMax = 0.0f;
	float fValue = 0.0f;
	bool bRes = true;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_oSttModulesComtradeBind.GetNext(pos);

		if(pModule->IsModuleSelected() && pModule->IsWeekTypeModule())
		{
			POS posCh = pModule->GetHeadPosition();
			while(posCh)
			{
				pCh = (CSttModuleChComtradeBind *)pModule->GetNext(posCh);
				
				if(pCh->IsChannelSelected())
				{
					fMax = pCh->CalcChannelMaxValue();
					fValue = pCh->GetChDCMaxValue();

					if((fValue-fMax) < 0.00001f)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前通道【%s】的实际输出值为【%.03f】,已超出最大输出值【%.03f】,请重新设置之后开始测试"),pCh->m_strName.GetString(),fMax,fValue);
						bRes = false;
					}
				}
			}
		}
	}

	return bRes;
}

bool CComtradePlayConfig::HasFT3ChMap()
{
	CStringArray ChNameList;
	ChNameList.Add(_T("Ia1"));
	ChNameList.Add(_T("Ib1"));
	ChNameList.Add(_T("Ic1"));
	ChNameList.Add(_T("Ua1"));
	ChNameList.Add(_T("Ub1"));
	ChNameList.Add(_T("Uc1"));
	ChNameList.Add(_T("Ia2"));
	ChNameList.Add(_T("Ib2"));
	ChNameList.Add(_T("Ic2"));
	ChNameList.Add(_T("Ua2"));
	ChNameList.Add(_T("Ub2"));
	ChNameList.Add(_T("Uc2"));

	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV* pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfg6044CommonCh *pIecCfg6044CommonCh = NULL;
	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	CExBaseObject *pCurObj = NULL;

	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCurObj;

			if (pIecCfg6044CommonData->m_nUseFlag == 1)
			{
				POS pos1 = pIecCfg6044CommonData->m_pCfgChs->GetHeadPosition();
				while(pos1)
				{
					pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pIecCfg6044CommonData->m_pCfgChs->GetNext(pos1);
					if(FindInCStringArry(ChNameList,pIecCfg6044CommonCh->m_strAppChID))
					{
						return true;
					}
				}
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前未配置相应FT3通道，请从IEC配置中重新设置！"));
	return false;
}


