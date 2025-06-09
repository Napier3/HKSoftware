#include "StdAfx.h"

#include "OnllyCfgFileTool.h"

COnllyCfgFileTool::COnllyCfgFileTool(void)
{
}

COnllyCfgFileTool::~COnllyCfgFileTool(void)
{
}

BOOL COnllyCfgFileTool::ReadF66File(const CString &strFile, CIecCfgDatasMngr *pIecCfgFileMngr)
{
	m_pIecCfgFileMngr = pIecCfgFileMngr;
	COnllyF66FileRead oOnllyF66FileRead;
	oOnllyF66FileRead.ReadF66File(strFile);

	ReadSmv(oOnllyF66FileRead.m_downmu, oOnllyF66FileRead.m_mugersetting);
	ReadGin(oOnllyF66FileRead.m_gseui.GseInCfg);
	ReadGout(oOnllyF66FileRead.m_gseui.GseOutCfg);

	return TRUE;
}

void COnllyCfgFileTool::ReadSmv(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting)
{
	int nSize = mu_setting.size();
	vector<MU_SETTING>::iterator itr = mu_setting.begin();

	CIecCfgDatasSMV *pDatasSmv = m_pIecCfgFileMngr->GetSmvMngr();
	CIecCfgDataSmvCommon *pCommon = pDatasSmv->GetCommonData();

	pCommon->m_nSampleRate = m_mugersetting.dSampleRate;
	pCommon->m_nAsduNum = m_mugersetting.nAsduNum;

	switch (m_mugersetting.nSampleType)
	{
	case SAMPLE_TYPE_9_1:
		pDatasSmv->m_strSmvType = g_strSmvType91;
		break;

	case SAMPLE_TYPE_9_2:
		pDatasSmv->m_strSmvType = g_strSmvType92;
		break;

	case SAMPLE_TYPE_9_1_EX:
		break;

	case SAMPLE_TYPE_FT3:
		pCommon->m_nSampleRate = (long)m_mugersetting.dFTSampleRate;
		pDatasSmv->m_strSmvType = g_strSmvType6044;
		break;

	default:
		break;
	}

	for (;itr != mu_setting.end(); itr++)
	{
		switch (m_mugersetting.nSampleType)
		{
		case SAMPLE_TYPE_9_1:
			ReadSmv_91((*itr),m_mugersetting);
			break;
		case SAMPLE_TYPE_9_2:
			ReadSmv_92((*itr),m_mugersetting);
			break;
		case SAMPLE_TYPE_9_1_EX:
			break;
		case SAMPLE_TYPE_FT3:
			ReadSmv_ft3((*itr),m_mugersetting);
			break;
		default:
			break;
		}
	}
}

void COnllyCfgFileTool::ReadSmv(MU_SETTING &mu)
{
	
}

CString _onlly_trans_ch_type(int nType)
{
	// 类型选择 0-电压,1-电流（保护）,2-电流（测量）,3-时间
	switch (nType)
	{
	case 0:
		return iecfg_SmvChDataType_Val_Vol;
		break;

	case 1:
		return iecfg_SmvChDataType_Val_CurrProt;
		break;

	case 2:
		return iecfg_SmvChDataType_Val_CurrMeasure;
		break;

	case 3:
		return iecfg_SmvChDataType_Val_UTCTime;
		break;

	default:
		return iecfg_SmvChDataType_Val_Vol;
		break;

	}
}

CString _onlly_trans_ch_appid(int nChIndex, long nTypeSel)
{
	if (nTypeSel == 2)
	{
		return g_strAppChID_Zero;
	}

	if (nChIndex == 0)
	{
		return g_strAppChID_Zero;
	}

	if (nTypeSel == 1)
	{
		//Ia ~ Itc
		if (nChIndex <= 12)
		{
			static CString strIChs[] = {_T("Ia1"), _T("Ib1"), _T("Ic1"),_T("Ia2"), _T("Ib2"), _T("Ic2"),_T("Ia3"), _T("Ib3"), _T("Ic3"),_T("Ia4"), _T("Ib4"), _T("Ic4") };
			return strIChs[nChIndex-1];
		}

		if (nChIndex <= 16)
		{
			static CString strIChs[] = {_T("I01"), _T("I02"), _T("I03"),_T("I04") };
			return strIChs[nChIndex-13];
		}
	}

	if (nTypeSel == 0)
	{
		if (nChIndex <= 12)
		{
			static CString strUChs[] = {_T("Ua1"), _T("Ub1"), _T("Uc1"),_T("Ua2"), _T("Ub2"), _T("Uc2"),_T("Ua3"), _T("Ub3"), _T("Uc3"),_T("Ua4"), _T("Ub4"), _T("Uc4") };
			return strUChs[nChIndex-1];
		}

		if (nChIndex <= 16)
		{
			static CString strUChs[] = {_T("U01"), _T("U02"), _T("U03"),_T("U04") };
			return strUChs[nChIndex-13];
		}
	}

	return g_strAppChID_Zero;
}

long _onlly_get_fiber_index(UINT nLanNo)
{
	long nIndex = 0;
	UINT nFlag = 1;
	long nIndexFind = 0;

	for (nIndex=0; nIndex<12; nIndex++)
	{
		if ((nLanNo & nFlag) > 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	return nIndexFind;
}

void COnllyCfgFileTool::ReadSmv_92(MU_SETTING &mu, MU_GENERALSETTTING &m_mugersetting)
{
	CIecCfgDatasSMV *pDatasSmv = m_pIecCfgFileMngr->GetSmvMngr();
	CIecCfg92Data *pData92 = (CIecCfg92Data*)pDatasSmv->CreateIecCfgData();
	pData92->OpenCfgDefaultConfigFile();
	pDatasSmv->AddNewChild(pData92);

	//控制块数据
	pData92->m_strDestAddress = mu.strMac;
	pData92->m_strSrcAddress  = mu.SourceMac;
	pData92->m_dwAppID        = mu.AppId;
//	pData92->m_nChannelNum    = mu;
	pData92->m_nPriority      = mu.nTCIPr;
	pData92->m_dwVID          = mu.nTciVid;
	pData92->m_nFiberIndex    = _onlly_get_fiber_index(mu.nLanNo);
	pData92->m_dwVersion      = mu.nVersion;
	pData92->m_nDelay         = mu.CurrentDelay;
	pData92->m_nSyn           = mu.bSyn;
	pData92->m_strSVID        = mu.strSvid;
	//pData92->m_strDataSet     =;

	//通道转换
	long nChCount = mu.pmu_chnset.size();
	pData92->SetChannelNum(nChCount);
	vector<MU_CHNSET> pmu_chnset;
	vector<MU_CHNSET>::iterator itr = mu.pmu_chnset.begin();
	long nIndex = 0;
	CIecCfg92Ch *pCh = NULL;
	CIecCfgChsBase *pChs = pData92->m_pCfgChs;

	for (;itr != mu.pmu_chnset.end(); itr++)
	{
		pCh = (CIecCfg92Ch *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		pCh->m_strID = itr->strChnName;
		pCh->m_strAddrExternal = itr->strChnName;
		pCh->m_nQuality = itr->m_DOWD_Q;
		//pCh->m_nData = itr->strInput;
		pCh->m_strChType = _onlly_trans_ch_type(itr->nTypeSel);
		//pCh->m_fCoef = 1;
		//pCh->m_nUseException = 0;
		pCh->m_nUseFlag = itr->bCheck;
		pCh->m_nIndex = itr->nIndex;
		pCh->m_strAppChID = _onlly_trans_ch_appid(itr->nChnSel, itr->nTypeSel);
		nIndex++;
	}
}

void COnllyCfgFileTool::ReadSmv_91(MU_SETTING &mu, MU_GENERALSETTTING &m_mugersetting)
{
	
}

void COnllyCfgFileTool::ReadSmv_ft3(MU_SETTING &mu, MU_GENERALSETTTING &m_mugersetting)
{

}

void COnllyCfgFileTool::ReadGin(vector<GSECFG>& GseCfg)
{
	int nSize = GseCfg.size();
	vector<GSECFG>::iterator itr = GseCfg.begin();

	for (;itr != GseCfg.end(); itr++)
	{
		ReadGin(*itr);
	}
}


//	int nType;			// 类型:0---单点,1---双点，2---时间，3---品质，4---浮点，5---字符串，6---整型，7---结构
CString _onlly_trans_gse_datatype(long nDataType)
{
	if (nDataType == 0)
	{
		return g_strGooseChType_Single;
	}

	if (nDataType == 1)
	{
		return g_strGooseChType_Double;
	}

	if (nDataType == 2)
	{
		return g_strGooseChType_Time;
	}

	if (nDataType == 3)
	{
		return g_strGooseChType_Quality;
	}

	if (nDataType == 4)
	{
		return g_strGooseChType_Float;
	}

	if (nDataType == 5)
	{
		return g_strGooseChType_String;
	}

	if (nDataType == 6)
	{
		return g_strGooseChType_Integer;
	}

	if (nDataType == 7)
	{
		return g_strGooseChType_Struct;
	}

	return g_strGooseChType_Single;
}

CString _onlly_trans_bin(long nIOIndex)
{
	static CString strBinName[] = {_T("none"), _T("bin1"), _T("bin2"), _T("bin3"), _T("bin4"), _T("bin5"), _T("bin6"), _T("bin7"), _T("bin8")};

	if (nIOIndex<0 || nIOIndex > 8)
	{
		return _T("none");
	}

	return strBinName[nIOIndex];
}

void COnllyCfgFileTool::ReadGin(GSECFG &gsecfg)
{
	CIecCfgGinDatas *pDatasGin = m_pIecCfgFileMngr->GetGinMngr();
	CIecCfgGinData *pDataGin = (CIecCfgGinData*)pDatasGin->CreateIecCfgData();
	pDatasGin->AddNewChild(pDataGin);
	pDataGin->OpenCfgDefaultConfigFile();

	//控制块数据
	pDataGin->m_strDestAddress = gsecfg.MacAddr;
	pDataGin->m_strSrcAddress  =gsecfg.SourceMac;
	pDataGin->m_dwAppID        = gsecfg.AppID;
	//	pData92->m_nChannelNum    = mu;
	pDataGin->m_dwVLandPriority      = gsecfg.Priority;
	pDataGin->m_strgocbRef     = gsecfg.GocbRef;
	pDataGin->m_dwVLandID          = gsecfg.VID;
	pDataGin->m_nFiberIndex    = _onlly_get_fiber_index(gsecfg.LanNo);
	pDataGin->m_dwVersion      = gsecfg.ConfRev;
	pDataGin->m_strGooseId     = gsecfg.GoID;
	pDataGin->m_bNdsCom        = gsecfg.NdsCom;
	pDataGin->m_bTest          = gsecfg.Test;
	pDataGin->m_strDataSet     = gsecfg.DataSet;
	//pDataGin
	//pDataGin->m_nLiveTime      = gsecfg.T0;
	//pData92->m_strDataSet     =;

	//通道转换
	long nChCount = gsecfg.ChnCfg.size();
	pDataGin->SetChannelNum(nChCount);
	vector<GSECHNCFG>::iterator itr = gsecfg.ChnCfg.begin();
	long nIndex = 0;
	CIecCfgGinCh *pCh = NULL;
	CIecCfgChsBase *pChs = pDataGin->m_pCfgChs;

	for (;itr != gsecfg.ChnCfg.end(); itr++)
	{
		pCh = (CIecCfgGinCh *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		pCh->m_strID = itr->strChnName;
		//pCh->m_nData = itr->strInput;
		pCh->m_strDataType = _onlly_trans_gse_datatype(itr->nType);
		//pCh->m_fCoef = 1;
		//pCh->m_nUseException = 0;
		pCh->m_strAppChID = _onlly_trans_bin(itr->nIOIndex);
		nIndex++;
	}
}


void COnllyCfgFileTool::ReadGout(vector<GSECFG>& GseCfg)
{
	int nSize = GseCfg.size();
	vector<GSECFG>::iterator itr = GseCfg.begin();

	for (;itr != GseCfg.end(); itr++)
	{
		ReadGout(*itr);
	}
}


CString _onlly_trans_bout(long nIOIndex)
{
	static CString strBoutName[] = {_T("none"), _T("bout1"), _T("bout2"), _T("bout3"), _T("bout4"), _T("bout5"), _T("bout6"), _T("bout7"), _T("bout8")};

	if (nIOIndex<0 || nIOIndex > 8)
	{
		return _T("none");
	}

	return strBoutName[nIOIndex];
}

void COnllyCfgFileTool::ReadGout(GSECFG &gsecfg)
{
	CIecCfgGoutDatas *pDatasGout = m_pIecCfgFileMngr->GetGoutMngr();
	CIecCfgGoutData *pDataGout = (CIecCfgGoutData*)pDatasGout->CreateIecCfgData();
	pDatasGout->AddNewChild(pDataGout);
	pDataGout->OpenCfgDefaultConfigFile();

	//控制块数据
	pDataGout->m_strDestAddress = gsecfg.MacAddr;
	pDataGout->m_strSrcAddress  =gsecfg.SourceMac;
	pDataGout->m_dwAppID        = gsecfg.AppID;
	//	pData92->m_nChannelNum    = mu;
	pDataGout->m_dwVLandPriority      = gsecfg.Priority;
	pDataGout->m_strgocbRef     = gsecfg.GocbRef;
	pDataGout->m_dwVLandID          = gsecfg.VID;
	pDataGout->m_nFiberIndex    = _onlly_get_fiber_index(gsecfg.LanNo);
	pDataGout->m_dwVersion      = gsecfg.ConfRev;
	pDataGout->m_strGooseId     = gsecfg.GoID;
	pDataGout->m_bNdsCom        = gsecfg.NdsCom;
	pDataGout->m_bTest          = gsecfg.Test;
	pDataGout->m_strDataSet     = gsecfg.DataSet;

	//pDataGin
	//pDataGin->m_nLiveTime      = gsecfg.T0;
	//pData92->m_strDataSet     =;

	//通道转换
	long nChCount = gsecfg.ChnCfg.size();
	pDataGout->SetChannelNum(nChCount);
	vector<GSECHNCFG>::iterator itr = gsecfg.ChnCfg.begin();
	long nIndex = 0;
	CIecCfgGinCh *pCh = NULL;
	CIecCfgChsBase *pChs = pDataGout->m_pCfgChs;

	for (;itr != gsecfg.ChnCfg.end(); itr++)
	{
		pCh = (CIecCfgGinCh *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		pCh->m_strID = itr->strChnName;
		//pCh->m_nData = itr->strInput;
		pCh->m_strDataType = _onlly_trans_gse_datatype(itr->nType);
		//pCh->m_fCoef = 1;
		//pCh->m_nUseException = 0;
		pCh->m_strAppChID = _onlly_trans_bout(itr->nIOIndex);
		nIndex++;
	}
}



//////////////////////////////////////////////////////////////////////////
//

CIecCfgFileTool::CIecCfgFileTool(void)
{
	m_pIecCfgFileMngr = NULL;
}

CIecCfgFileTool::~CIecCfgFileTool(void)
{

}

BOOL CIecCfgFileTool::ReadIecCfgFile(LPCTSTR strPath,MU_GENERALSETTTING& mu_gset, vector<MU_SETTING>& muset, GSEUI& gseui)
{
	// 	if (m_pIecCfgFileMngr != NULL)
	// 	{
	// 		delete m_pIecCfgFileMngr;
	// 	}

	m_pIecCfgFileMngr = new CIecCfgDatasMngr();
	m_pIecCfgFileMngr->OpenIecCfgFile(strPath);


	ReadSmv(muset,mu_gset);
	ReadGin(gseui.GseInCfg);
	ReadGout(gseui.GseOutCfg);

	return TRUE;
}

void CIecCfgFileTool::ReadSmv(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting)
{
	// 	int nSize = mu_setting.size();
	// 	vector<MU_SETTING>::iterator itr = mu_setting.begin();

	CIecCfgDatasSMV *pDatasSmv = m_pIecCfgFileMngr->GetSmvMngr();
	CIecCfgDataSmvCommon *pCommon = pDatasSmv->GetCommonData();

	long nIndex = pDatasSmv->GetMaxCfgDataCount();

	m_mugersetting.dSampleRate = pCommon->m_nSampleRate;
	m_mugersetting.nAsduNum = pCommon->m_nAsduNum;

	UINT nSmvType = pDatasSmv->GetSmvType();
	switch (nSmvType)
	{
	case SMVTYPE_91:
		//pDatasSmv->m_strSmvType = g_strSmvType91;
		break;

	case SMVTYPE_92:
		//pDatasSmv->m_strSmvType = g_strSmvType92;
		break;

	case SMVTYPE_6044:
		//pCommon->m_nSampleRate = (long)m_mugersetting.dFTSampleRate;
		m_mugersetting.dFTSampleRate = (float)pCommon->m_nSampleRate;
		//pDatasSmv->m_strSmvType = g_strSmvType6044;
		break;

	default:
		break;
	}

	for (int i = 0; i < nIndex ; i++)
	{
		switch (nSmvType)
		{
		case SMVTYPE_91:
			ReadSmv_91(mu_setting,m_mugersetting,i);
			break;
		case SMVTYPE_92:
			ReadSmv_92(mu_setting,m_mugersetting,i);
			break;
		case SMVTYPE_6044:
			ReadSmv_ft3(mu_setting,m_mugersetting,i);
			break;
		default:
			break;
		}
	}
}

void CIecCfgFileTool::ReadSmv(MU_SETTING &mu)
{

}

int _onlly_trans_ch_type(CString strType)
{
	// 类型选择 0-电压,1-电流（保护）,2-电流（测量）,3-时间
	CString strSmvType = strType;

	if (strSmvType = iecfg_SmvChDataType_Val_Vol)
	{
		return 0;
	}

	if (strSmvType = iecfg_SmvChDataType_Val_CurrProt)
	{
		return 1;
	}

	if (strSmvType = iecfg_SmvChDataType_Val_CurrMeasure)
	{
		return 2;
	}

	if (strSmvType = iecfg_SmvChDataType_Val_UTCTime)
	{
		return 3;
	}

	return 0;
}
// 
// CString _onlly_trans_ch_appid(int nChIndex, long nTypeSel)
// {
// 	if (nTypeSel == 2)
// 	{
// 		return g_strAppChID_Zero;
// 	}
// 
// 	if (nChIndex == 0)
// 	{
// 		return g_strAppChID_Zero;
// 	}
// 
// 	if (nTypeSel == 1)
// 	{
// 		//Ia ~ Itc
// 		if (nChIndex <= 12)
// 		{
// 			static CString strIChs[] = {_T("Ia1"), _T("Ib1"), _T("Ic1"),_T("Ia2"), _T("Ib2"), _T("Ic2"),_T("Ia3"), _T("Ib3"), _T("Ic3"),_T("Ia4"), _T("Ib4"), _T("Ic4") };
// 			return strIChs[nChIndex-1];
// 		}
// 
// 		if (nChIndex <= 16)
// 		{
// 			static CString strIChs[] = {_T("I01"), _T("I02"), _T("I03"),_T("I04") };
// 			return strIChs[nChIndex-13];
// 		}
// 	}
// 
// 	if (nTypeSel == 0)
// 	{
// 		if (nChIndex <= 12)
// 		{
// 			static CString strUChs[] = {_T("Ua1"), _T("Ub1"), _T("Uc1"),_T("Ua2"), _T("Ub2"), _T("Uc2"),_T("Ua3"), _T("Ub3"), _T("Uc3"),_T("Ua4"), _T("Ub4"), _T("Uc4") };
// 			return strUChs[nChIndex-1];
// 		}
// 
// 		if (nChIndex <= 16)
// 		{
// 			static CString strUChs[] = {_T("U01"), _T("U02"), _T("U03"),_T("U04") };
// 			return strUChs[nChIndex-13];
// 		}
// 	}
// 
// 	return g_strAppChID_Zero;
// }
// 
// long _onlly_get_fiber_index(UINT nLanNo)
// {
// 	long nIndex = 0;
// 	UINT nFlag = 1;
// 	long nIndexFind = 0;
// 
// 	for (nIndex=0; nIndex<12; nIndex++)
// 	{
// 		if ((nLanNo & nFlag) > 0)
// 		{
// 			nIndexFind = nIndex;
// 			break;
// 		}
// 	}
// 
// 	return nIndexFind;
// }

void CIecCfgFileTool::ReadSmv_92(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting, long nIndex)
{
	CIecCfgDatasSMV *pDatasSmv = m_pIecCfgFileMngr->GetSmvMngr();
	pDatasSmv->SetDataUse(1,1);
	CIecCfg92Data *pData92 = (CIecCfg92Data*)pDatasSmv->GetIecCfgData(0);

	POS pos = pDatasSmv->GetHeadPosition();

	while ( pos != NULL)
	{
		CIecCfg92Data *pData92 = (CIecCfg92Data*)pDatasSmv->GetNext(pos);
		if (pData92->GetClassID() == CFGCLASSID_CIECCFG92DATA)
		{
			MU_SETTING mu;
			mu.strMac = pData92->m_strDestAddress;
			mu.SourceMac = pData92->m_strDestAddress;
			mu.AppId = pData92->m_dwAppID;
			mu.nTCIPr = pData92->m_nPriority;
			mu.nTciVid = pData92->m_dwVID;
			mu.nLanNo = _onlly_get_fiber_index(pData92->m_nFiberIndex);
			mu.nVersion = pData92->m_dwVersion;
			mu.CurrentDelay = pData92->m_nDelay;
			mu.bSyn = pData92->m_nSyn;
			mu.strSvid = pData92->m_strSVID;


			//通道转换
			// 	long nChCount = mu.pmu_chnset.size();
			// 	pData92->SetChannelNum(nChCount);
			MU_CHNSET pmu_chnset;
			// 	vector<MU_CHNSET>::iterator itr = mu.pmu_chnset.begin();
			long nChCount = pData92->GetChannelNum();	
			CIecCfgChsBase *pChs = pData92->m_pCfgChs;
			CIecCfg92Ch *pCh = new CIecCfg92Ch();

			POS p = pChs->GetHeadPosition();
			while( p != NULL)
			{
				CIecCfg92Ch *pCh = (CIecCfg92Ch *)pChs->GetNext(p);

				if (pCh->GetClassID() == CFGCLASSID_CIECCFGCHS92)
				{
					pmu_chnset.strChnName = pCh->m_strID;
					pmu_chnset.m_DOWD_Q = pCh->m_nQuality;
					pmu_chnset.nTypeSel = _onlly_trans_ch_type(pCh->m_strChType);
					pmu_chnset.bCheck = pCh->m_nUseFlag;
					pmu_chnset.nIndex = pCh->m_nIndex;

					mu.pmu_chnset.push_back(pmu_chnset);

				}
			}
			mu_setting.push_back(mu);
		}
	}

}

void CIecCfgFileTool::ReadSmv_91(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting, long nIndex)
{

}

void CIecCfgFileTool::ReadSmv_ft3(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting , long nIndex)
{

}

void CIecCfgFileTool::ReadGin(vector<GSECFG>& GseCfg)
{
	// 	int nSize = GseCfg.size();
	// 	vector<GSECFG>::iterator itr = GseCfg.begin();
	// 
	// 	for (;itr != GseCfg.end(); itr++)
	// 	{
	// 		ReadGin(*itr);
	// 	}
	CIecCfgGinDatas *pDatasGin = m_pIecCfgFileMngr->GetGinMngr();
	long nIndex  = pDatasGin->GetMaxCfgDataCount();
	for (int i = 0; i<nIndex; i++)
	{
		ReadGin(GseCfg,nIndex);
	}
}


//	int nType;			// 类型:0---单点,1---双点，2---时间，3---品质，4---浮点，5---字符串，6---整型，7---结构
long _onlly_trans_gse_datatype(CString strDataType)
{
	CString strType = strDataType;
	if (strType == g_strGooseChType_Single)
	{
		return 0;
	}

	if (strType == g_strGooseChType_Double)
	{
		return 1;
	}

	if (strType == g_strGooseChType_Time)
	{
		return 2;
	}

	if (strType == g_strGooseChType_Quality)
	{
		return 3;
	}

	if (strType == g_strGooseChType_Float)
	{
		return 4;
	}

	if (strType == g_strGooseChType_String)
	{
		return 5;
	}

	if (strType == g_strGooseChType_Integer)
	{
		return 6;
	}

	if (strType == g_strGooseChType_Struct)
	{
		return 7;
	}

	return 0;
}

long _onlly_trans_bin(CString strIOIndex)
{
	// 	static CString strBinName[] = {_T("none"), _T("bin1"), _T("bin2"), _T("bin3"), _T("bin4"), _T("bin5"), _T("bin6"), _T("bin7"), _T("bin8")};
	// 
	// 	if (nIOIndex<0 || nIOIndex > 8)
	// 	{
	// 		return _T("none");
	// 	}
	// 
	// 	return strBinName[nIOIndex];

	CString strIndex = strIOIndex;
	if (strIndex == _T("none"))
	{
		return 0;
	}

	if (strIndex == _T("bin1"))
	{
		return 1;
	}

	if (strIndex == _T("bin2"))
	{
		return 2;
	}

	if (strIndex == _T("bin3"))
	{
		return 3;
	}

	if (strIndex == _T("bin4"))
	{
		return 4;
	}

	if (strIndex == _T("bin5"))
	{
		return 5;
	}

	if (strIndex == _T("bin6"))
	{
		return 6;
	}

	if (strIndex == _T("bin7"))
	{
		return 7;
	}

	if (strIndex == _T("bin8"))
	{
		return 8;
	}

	return 0;
}

void CIecCfgFileTool::ReadGin(vector<GSECFG>& GseCfg, long nIndex)
{
	CIecCfgGinDatas *pDatasGin = m_pIecCfgFileMngr->GetGinMngr();
	//CIecCfgGinData *pDataGin = (CIecCfgGinData*)pDatasGin->GetIecCfgData(nIndex);
	POS pos = pDatasGin->GetHeadPosition();

	while(pos != NULL)
	{
		CIecCfgGinData *pDataGin = (CIecCfgGinData*)pDatasGin->GetNext(pos);
		if (pDataGin->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			GSECFG gsecfg;
			//控制块数据
			gsecfg.MacAddr = pDataGin->m_strDestAddress;
			gsecfg.SourceMac = pDataGin->m_strSrcAddress;
			gsecfg.AppID = pDataGin->m_dwAppID;
			gsecfg.Priority = pDataGin->m_dwVLandPriority;
			gsecfg.GocbRef = pDataGin->m_strgocbRef;
			gsecfg.VID = pDataGin->m_dwVLandID;
			gsecfg.LanNo = _onlly_get_fiber_index(pDataGin->m_nFiberIndex);
			gsecfg.ConfRev = pDataGin->m_dwVersion;
			gsecfg.GoID = pDataGin->m_strGooseId;
			gsecfg.NdsCom = pDataGin->m_bNdsCom;
			gsecfg.Test = pDataGin->m_bTest;
			gsecfg.DataSet = pDataGin->m_strDataSet;


			CIecCfgGinCh *pCh = NULL;
			CIecCfgChsBase *pChs = pDataGin->m_pCfgChs;
			long nChCount = pDataGin->GetChannelNum();
			GSECHNCFG Chncfg;
			POS p = pChs->GetHeadPosition();

			while( p != NULL)
			{
				pCh = (CIecCfgGinCh *)pChs->GetNext(p);

				if (pCh->GetClassID() == CFGCLASSID_CIECCFGGINCH)
				{
					Chncfg.strChnName = pCh->m_strID;
					Chncfg.nType = _onlly_trans_gse_datatype(pCh->m_strDataType);
					Chncfg.nIOIndex = _onlly_trans_bin(pCh->m_strAppChID);

					gsecfg.ChnCfg.push_back(Chncfg);			
				}			
			}
			GseCfg.push_back(gsecfg);
		}
	}
}


void CIecCfgFileTool::ReadGout(vector<GSECFG>& GseCfg)
{
	// 	int nSize = GseCfg.size();
	// 	vector<GSECFG>::iterator itr = GseCfg.begin();
	// 
	// 	for (;itr != GseCfg.end(); itr++)
	// 	{
	// 		ReadGout(*itr);
	// 	}

	CIecCfgGoutDatas *pDatasGout = m_pIecCfgFileMngr->GetGoutMngr();
	long nIndex  = pDatasGout->GetMaxCfgDataCount();
	for (int i = 0; i<nIndex; i++)
	{
		ReadGout(GseCfg,nIndex);
	}
}


long _onlly_trans_bout(CString strIOIndex)
{
	// 	static CString strBoutName[] = {_T("none"), _T("bout1"), _T("bout2"), _T("bout3"), _T("bout4"), _T("bout5"), _T("bout6"), _T("bout7"), _T("bout8")};
	// 
	// 	if (nIOIndex<0 || nIOIndex > 8)
	// 	{
	// 		return _T("none");
	// 	}
	// 
	// 	return strBoutName[nIOIndex];

	CString strIndex = strIOIndex;
	if (strIndex == _T("none"))
	{
		return 0;
	}

	if (strIndex == _T("bout1"))
	{
		return 1;
	}

	if (strIndex == _T("bout2"))
	{
		return 2;
	}

	if (strIndex == _T("bout3"))
	{
		return 3;
	}

	if (strIndex == _T("bout4"))
	{
		return 4;
	}

	if (strIndex == _T("bout5"))
	{
		return 5;
	}

	if (strIndex == _T("bout6"))
	{
		return 6;
	}

	if (strIndex == _T("bout7"))
	{
		return 7;
	}

	if (strIndex == _T("bout8"))
	{
		return 8;
	}

	return 0;
}

void CIecCfgFileTool::ReadGout(vector<GSECFG>& GseCfg, long nIndex)
{
	CIecCfgGoutDatas *pDatasGout = m_pIecCfgFileMngr->GetGoutMngr();
	//CIecCfgGinData *pDataGin = (CIecCfgGinData*)pDatasGin->GetIecCfgData(nIndex);
	POS pos = pDatasGout->GetHeadPosition();

	while(pos != NULL)
	{
		CIecCfgGoutData *pDataGout = (CIecCfgGoutData*)pDatasGout->GetNext(pos);
		if (pDataGout->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			GSECFG gsecfg;
			//控制块数据
			gsecfg.MacAddr = pDataGout->m_strDestAddress;
			gsecfg.SourceMac = pDataGout->m_strSrcAddress;
			gsecfg.AppID = pDataGout->m_dwAppID;
			gsecfg.Priority = pDataGout->m_dwVLandPriority;
			gsecfg.GocbRef = pDataGout->m_strgocbRef;
			gsecfg.VID = pDataGout->m_dwVLandID;
			gsecfg.LanNo = _onlly_get_fiber_index(pDataGout->m_nFiberIndex);
			gsecfg.ConfRev = pDataGout->m_dwVersion;
			gsecfg.GoID = pDataGout->m_strGooseId;
			gsecfg.NdsCom = pDataGout->m_bNdsCom;
			gsecfg.Test = pDataGout->m_bTest;
			gsecfg.DataSet = pDataGout->m_strDataSet;


			CIecCfgGinCh *pCh = NULL;
			CIecCfgChsBase *pChs = pDataGout->m_pCfgChs;
			long nChCount = pDataGout->GetChannelNum();
			GSECHNCFG Chncfg;
			POS p = pChs->GetHeadPosition();

			while( p != NULL)
			{
				pCh = (CIecCfgGinCh *)pChs->GetNext(p);

				if (pCh->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
				{
					Chncfg.strChnName = pCh->m_strID;
					Chncfg.nType = _onlly_trans_gse_datatype(pCh->m_strDataType);
					Chncfg.nIOIndex = _onlly_trans_bin(pCh->m_strAppChID);

					gsecfg.ChnCfg.push_back(Chncfg);			
				}			
			}
			GseCfg.push_back(gsecfg);
		}
	}

}
