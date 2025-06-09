#include "StdAfx.h"
#include "IecCfgToDvsPara.h"


CIecCfgToDvsPara::CIecCfgToDvsPara(void)
{
	m_pIECPara = NULL;
}

CIecCfgToDvsPara::~CIecCfgToDvsPara(void)
{

}

void CIecCfgToDvsPara::InitPara()
{
	m_nSmvIndex = 0;
	m_nSmvChIndex = 0;
	m_nGinIndex = 0;
	m_nGinChIndex = 0;
	m_nGoutIndex = 0;
	m_nGoutChIndex = 0;

	m_pIECPara->m_paraSmv[0].m_bSendSmv = TRUE;
	m_pIECPara->m_paraSmv[0].m_nSendPort = 1;
	m_pIECPara->m_paraGooseSub[0].m_bSendSub = TRUE;
	m_pIECPara->m_paraGooseSub[0].m_nSendPort = 1;
	m_pIECPara->m_paraGoosePub[0].m_bSendPub = TRUE;
	m_pIECPara->m_paraGoosePub[0].m_nSendPort = 1;
}

//////////////////////////////////////////////////////////////////////////
//外部接口部分
void CIecCfgToDvsPara::TransToIecPara(CExBaseObject *pIecCfgDatasMngr)
{
	if (m_pIECPara == NULL || pIecCfgDatasMngr == NULL)
	{
		return;
	}

	InitPara();
// 	CIecCfgFile *pFile = NULL;
// 
// 	if (pIecCfgFile == NULL)
// 	{
// 		CIecCfgFiles *pFiles = CIecCfgTool::GetIecCfgFiles();
// 		POS pos = pFiles->GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			pFile = (CIecCfgFile *)pFiles->GetNext(pos);
// 		}
// 		return;
// 	}
// 	else
// 	{
// 		ASSERT (pIecCfgFile->GetClassID() == IFTCLASSID_CIECCFGFILE);
// 		pFile = (CIecCfgFile*)pIecCfgFile;
// 	}

	CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr *)pIecCfgDatasMngr;
	TransToIecPara(pDatasMngr);
}

//////////////////////////////////////////////////////////////////////////

void CIecCfgToDvsPara::TransToIecPara(CIecCfgDatasMngr  *pIecCfgDatasMngr)
{
	CIecCfgDatasMngr *pDatasMngr = pIecCfgDatasMngr;//pIecCfgFile->m_pIecCfgDatasMngr;
	CIecCfgDataBase	 *pCfgDataBase = NULL;
	int nSmvCount = pDatasMngr->GetSMVCount();
	int nGinCount = pDatasMngr->GetGINCount();
	int nGoutCount = pDatasMngr->GetGOUTCount();
	m_pIECPara->m_nSmvType = pDatasMngr->GetSmvType();

	for (int i=0;i<nSmvCount;i++)
	{
		pCfgDataBase = pDatasMngr->GetSmvCfgData(i);
		if (pCfgDataBase)
		{
			switch (m_pIECPara->m_nSmvType)
			{
			case SMVTYPE_91:
				TransToIecPara_SMV_91((CIecCfg91Data*)pCfgDataBase);
				break;
			case SMVTYPE_92:
				TransToIecPara_SMV_92((CIecCfg92Data*)pCfgDataBase);
				break;
			case SMVTYPE_6044:
				TransToIecPara_SMV_60448((CIecCfg6044Data*)pCfgDataBase);
				break;
			}
		}
	}

	for (int i=0;i<nGinCount;i++)
	{
		pCfgDataBase = pDatasMngr->GetGinCfgData(i);
		if (pCfgDataBase)
		{
			TransToIecPara_Gin((CIecCfgGinData*)pCfgDataBase);
		}
	}

	for (int i=0;i<nGoutCount;i++)
	{
		pCfgDataBase = pDatasMngr->GetGoutCfgData(i);
		if (pCfgDataBase)
		{
			TransToIecPara_Gout((CIecCfgGoutData*)pCfgDataBase);
		}
	}

}

void CIecCfgToDvsPara::TransToIecPara_SMV_91(CIecCfg91Data *pCfgSmv)
{
	POS pos = pCfgSmv->m_pCfgChs->GetHeadPosition();

	while (pos != NULL)
	{
		TransToIecPara_SMV_91_Ch((CIecCfg91Ch *)pCfgSmv->m_pCfgChs->GetNext(pos));
	}

	m_nSmvIndex++;
}

void CIecCfgToDvsPara::TransToIecPara_SMV_92(CIecCfg92Data *pCfgSmv)
{
	if (!pCfgSmv->m_nUseFlag)
	{
		return;
	}

	m_pIECPara->m_paraSmv[m_nSmvIndex].m_bSendSmv = pCfgSmv->m_nUseFlag;
// 	GetCfg_Mac(pCfgSmv->m_strDestAddress, m_pIECPara->m_paraSmv[m_nSmvIndex].m_nMacAddressDst);
// 	GetCfg_Mac(pCfgSmv->m_strSrcAddress, m_pIECPara->m_paraSmv[m_nSmvIndex].m_nMacAddressSrc);
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_strMacAddressDst = pCfgSmv->m_strDestAddress;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_strMacAddressSrc = pCfgSmv->m_strSrcAddress;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nAppid = pCfgSmv->m_dwAppID;
	GetCfg_Tci(pCfgSmv->m_dwVID, pCfgSmv->m_nPriority, &m_pIECPara->m_paraSmv[m_nSmvIndex].m_nTCI);
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nSendPort = pCfgSmv->m_nFiberIndex;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nSMVVersion = pCfgSmv->m_dwVersion;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nSmpDelay = pCfgSmv->m_nDelay;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nNetDelay = 0;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nSyn = pCfgSmv->m_nSyn;
	ZeroMemory(m_pIECPara->m_paraSmv[m_nSmvIndex].m_tchSvID, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraSmv[m_nSmvIndex].m_tchSvID, MAX_PATH, pCfgSmv->m_strSVID);
	ZeroMemory(m_pIECPara->m_paraSmv[m_nSmvIndex].m_tchDatSet, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraSmv[m_nSmvIndex].m_tchDatSet, MAX_PATH, pCfgSmv->m_strDataSet);
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_nChannelCount = pCfgSmv->m_nChannelNum;

	POS pos = pCfgSmv->m_pCfgChs->GetHeadPosition();

	while (pos != NULL)
	{
		TransToIecPara_SMV_92_Ch((CIecCfg92Ch *)pCfgSmv->m_pCfgChs->GetNext(pos));
	}

	m_nSmvIndex++;
}

void CIecCfgToDvsPara::TransToIecPara_SMV_60448(CIecCfg6044Data *pCfgSmv)
{
	POS pos = pCfgSmv->m_pCfgChs->GetHeadPosition();

	while (pos != NULL)
	{
		TransToIecPara_SMV_60448_Ch((CIecCfg6044Ch *)pCfgSmv->m_pCfgChs->GetNext(pos));
	}

	m_nSmvIndex++;
}

void CIecCfgToDvsPara::TransToIecPara_Gin(CIecCfgGinData *pCfgGin)
{
	if (!pCfgGin->m_nUseFlag)
	{
		return;
	}

	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_bSendSub = pCfgGin->m_nUseFlag;
// 	GetCfg_Mac(pCfgGin->m_strDestAddress, m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nMacAddress);
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_strMacAddress = pCfgGin->m_strDestAddress;
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nAppid = pCfgGin->m_dwAppID;
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nSendPort = pCfgGin->m_nFiberIndex;
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nCnfRev = pCfgGin->m_dwVersion;
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_bTestMode = pCfgGin->m_nTest;
	ZeroMemory(m_pIECPara->m_paraGooseSub[m_nGinIndex].m_tchGocbRef, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraGooseSub[m_nGinIndex].m_tchGocbRef, MAX_PATH, pCfgGin->m_strgocbRef);
	ZeroMemory(m_pIECPara->m_paraGooseSub[m_nGinIndex].m_tchDataSet, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraGooseSub[m_nGinIndex].m_tchDataSet, MAX_PATH, pCfgGin->m_strDataSet);
	ZeroMemory(m_pIECPara->m_paraGooseSub[m_nGinIndex].m_tchGooseID, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraGooseSub[m_nGinIndex].m_tchGooseID, MAX_PATH, pCfgGin->m_strGooseId);
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_bNdsCom = pCfgGin->m_nNdsCom;
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nLiveTime = pCfgGin->m_nLiveTime;
	m_pIECPara->m_paraGooseSub[m_nGinIndex].m_bFilterMode = pCfgGin->m_nAnalyze;

	for (int i=0;i<8;i++)	//初始化绑定数据
	{
		m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nInMap[i] = m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nBitInMap[i] = 0;
	}

	POS pos = pCfgGin->m_pCfgChs->GetHeadPosition();

	while (pos != NULL)
	{
		TransToIecPara_Gin_Ch((CIecCfgGinCh *)pCfgGin->m_pCfgChs->GetNext(pos));
	}

	m_nGinIndex++;
}

void CIecCfgToDvsPara::TransToIecPara_Gout(CIecCfgGoutData *pCfgGout)
{
	if (!pCfgGout->m_nUseFlag)
	{
		return;
	}

	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_bSendPub = pCfgGout->m_nUseFlag;
// 	GetCfg_Mac(pCfgGout->m_strDestAddress, m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nMacAddressDst);
// 	GetCfg_Mac(pCfgGout->m_strSrcAddress, m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nMacAddressSrc);
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_strMacAddressDst = pCfgGout->m_strDestAddress;
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_strMacAddressSrc = pCfgGout->m_strSrcAddress;
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nAppid = pCfgGout->m_dwAppID;
	GetCfg_Tci(pCfgGout->m_dwVID, pCfgGout->m_nPriority, &m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nTCI);
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nSendPort = pCfgGout->m_nFiberIndex;
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nCnfRev = pCfgGout->m_dwVersion;
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_bTestMode = pCfgGout->m_nTest;
	ZeroMemory(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchGocbRef, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchGocbRef, MAX_PATH, pCfgGout->m_strgocbRef);
	ZeroMemory(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchDataSet, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchDataSet, MAX_PATH, pCfgGout->m_strDataSet);
	ZeroMemory(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchGooseID, MAX_PATH);
	_tcscpy_s(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchGooseID, MAX_PATH, pCfgGout->m_strGooseId);
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_bNdsCom = pCfgGout->m_nNdsCom;
	m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_nLiveTime = pCfgGout->m_nLiveTime;

	POS pos = pCfgGout->m_pCfgChs->GetHeadPosition();

	while (pos != NULL)
	{
		TransToIecPara_Gout_Ch((CIecCfgGoutCh *)pCfgGout->m_pCfgChs->GetNext(pos));
	}

	m_nGoutIndex++;
}

//////////////////////////////////////////////////////////////////////////
//通道数据转换
void CIecCfgToDvsPara::TransToIecPara_SMV_91_Ch(CIecCfg91Ch *pCh)
{
	m_nSmvChIndex++;	
}

void CIecCfgToDvsPara::TransToIecPara_SMV_92_Ch(CIecCfg92Ch *pCh)
{
	if (m_nSmvChIndex>59/* || pCh->m_nUseFlag*/)
	{
		return;
	}

	m_pIECPara->m_paraSmv[m_nSmvIndex].m_smvChsData[m_nSmvChIndex].m_nIndex = pCh->m_nIndex;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_smvChsData[m_nSmvChIndex].m_nUnit = _wtoi(pCh->m_strChType);
	GetCfg_Map(pCh->m_strAppChID, &m_pIECPara->m_paraSmv[m_nSmvIndex].m_smvChsData[m_nSmvChIndex].m_nMapIndex);
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_smvChsData[m_nSmvChIndex].m_nQualityH = (pCh->m_nQuality>>16)&0xFFFF;
	m_pIECPara->m_paraSmv[m_nSmvIndex].m_smvChsData[m_nSmvChIndex].m_nQualityL = pCh->m_nQuality&0xFFFF;

	m_nSmvChIndex++;	
}

void CIecCfgToDvsPara::TransToIecPara_SMV_60448_Ch(CIecCfg6044Ch *pCh)
{
	m_nSmvChIndex++;	
}

void CIecCfgToDvsPara::TransToIecPara_Gin_Ch(CIecCfgGinCh *pCh)
{
	int nMap=0;

	if (pCh->m_strAppChID.Find(_T("无"),0) < 0)
	{
		GetCfg_Map(pCh->m_strAppChID, &nMap);
		CString strTemp;
		strTemp.Format(_T("%02d0%02d"), pCh->m_nColIndex,m_nGinChIndex);
		m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nInMap[nMap] = _wtoi(strTemp);
		m_pIECPara->m_paraGooseSub[m_nGinIndex].m_nBitInMap[nMap] = (pCh->m_nPos>0) ? pow(2.0f,(pCh->m_nPos-1)):0;
	}

	m_nGinChIndex++;	
}

void CIecCfgToDvsPara::TransToIecPara_Gout_Ch(CIecCfgGoutCh *pCh)
{
	int nMap;
	CString strData;

	GetCfg_Map_Pub(pCh->m_strDataType, pCh->m_strAppChID, &nMap, strData);
	_tcscat_s(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchGoosePubData,strData);
	_tcscat_s(m_pIECPara->m_paraGoosePub[m_nGoutIndex].m_tchGoosePubData,_T(","));

	m_nGoutChIndex++;	
}


//////////////////////////////////////////////////////////////////////////
//根据数据类型获取数据
void  CIecCfgToDvsPara::GetCfg_Mac(const CString &strMac, BYTE *bytMac)
{
	CString strM = strMac;
	strM.Replace(_T("-"),_T(""));

	for (int i=0;i<6;i++)
	{
		bytMac[i] = (BYTE)_tcstoul(strM.Mid(i*2,2), NULL,16);
	}
}

void  CIecCfgToDvsPara::GetCfg_Tci(const DWORD &dwTci_V, const DWORD &dwTci_P, DWORD *dwTCI)
{
	CString VLanID,VLanP;
	VLanID.Format(_T("%03x"), dwTci_V);
	VLanP.Format(_T("%03x"), dwTci_P);
	VLanID = HexToBin(VLanID);
	VLanP = HexToBin(VLanP);
	if (VLanID.GetLength()>=12)
		VLanID = VLanID.Mid(0,12);
	else
	{
		while(VLanID.GetLength()!=12)
		{
			VLanID.Insert(0,'0');
		}
	}

	DWORD nDec;
	nDec = _wtoi(BinToDec(VLanP+_T("0")+VLanID));		//修改后计算TCI未验证
	VLanID.Format(_T("%04X"),nDec);
	VLanID = VLanID.Left(2)+VLanID.Right(2);
	nDec = _wtoi(HexToDec(VLanID));
	DWORD nVID0 = nDec & 0xFFF;
	DWORD nPriority0 = ((nDec&0xF000)/0x1000)>>1;
	nVID0 += nPriority0<<13;
	VLanID.Format(_T("%04X"),nVID0);
	nDec = _wtoi(HexToDec(VLanID));
	*dwTCI = nDec;

}

void  CIecCfgToDvsPara::GetCfg_Map(const CString &strMap, int *nMap, TCHAR *pchMapData)
{
	CString strSmvMap[] = {_T("0"), _T("Ua1"), _T("Ub1"), _T("Uc1"), _T("U01"), _T("Ua2"), _T("Ub2"), _T("Uc2"), _T("U02")
		, _T("Uz1"), _T("Ia1"), _T("Ib1"), _T("Ic1"), _T("I01"), _T("Ia2"), _T("Ib2"), _T("Ic2"), _T("I02"), _T("延时")
		, _T("Ua3"), _T("Ub3"), _T("Uc3"), _T("U03"), _T("Ua4"), _T("Ub4"), _T("Uc4"), _T("U04"), _T("Ia3"), _T("Ib3")
		, _T("Ic3"), _T("I03"), _T("Ia4"), _T("Ib4"), _T("Ic4"), _T("I04"), _T("Uz2"), _T("Uz3"), _T("Uz4"), _T("Uab"), _T("Ubc") , _T("Uca")  };

	for (int i=0;i<41;i++)
	{
		if (!_tcscmp(strSmvMap[i], strMap))
		{
			*nMap = i;
			return;
		}
	}

	CString strGinMap[] = {_T("开入1"), _T("开入2"), _T("开入3"), _T("开入4"), _T("开入5"), _T("开入6"), _T("开入7"), _T("开入8")  };

	for (int i=0;i<8;i++)
	{
		if (!_tcscmp(strGinMap[i], strMap))
		{
			*nMap = i;
			return;
		}
	}

}

void  CIecCfgToDvsPara::GetCfg_Map_Pub(const CString &strMap1, const CString &strMap2, int *nMap, CString &strMapData)
{
// 	CString strGSMap[] = {_T("单点"), _T("双点"), _T("时间"), _T("品质"), _T("浮点"), _T("字符串"), _T("结构"), _T("INT32") };
	CString strGSMap1[] = {_T("0"), _T("1"), _T("00"), _T("01"), _T("10"), _T("11"), _T("UTCTime"), _T("float") };
	CString strGSMap2[] = {_T("FALSE"), _T("TRUE"), _T("[00]"), _T("[01]"), _T("[10]"), _T("[11]"), _T("UTCTime"), _T("0.0f") };

	if ( strMap2.Find(_T("开出"),0)>=0 )
	{
		strMapData = strMap2;
		if (strMap1 == g_strGooseChType_Single)
		{
			strMapData.Replace(_T("开出"),_T("Out"));
		}
		else
		{
			strMapData.Replace(_T("开出"),_T("OUT"));
			strMapData += _T("_DBPOS");
		}
		return;
	}
	else 
	{
		for (int i=0;i<8;i++)
		{
			if (!_tcscmp(strMap2, strGSMap1[i]))
			{
				*nMap = i;
				strMapData = strGSMap2[i];
				return;
			}
		}
	}
	strMapData = _T("0");
}
