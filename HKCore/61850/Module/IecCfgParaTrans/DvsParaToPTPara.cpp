#include "StdAfx.h"
#include "DvsParaToPTPara.h"
#include "..\..\..\Module\API\FileApi.h"

CDvsParaToPTPara::CDvsParaToPTPara(void)
{
	m_pIECPara = NULL;
}

CDvsParaToPTPara::~CDvsParaToPTPara(void)
{

}

void CDvsParaToPTPara::InitPara()
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
void CDvsParaToPTPara::TransToPTPara(CString strPtParaPath)
{
	if (m_pIECPara == NULL)
	{
		return;
	}

	if (!GetFileData(strPtParaPath))
	{
		return;
	}

	InitPara();

// 	int nSmvCount = pDatasMngr->GetSMVCount();
// 	int nGinCount = pDatasMngr->GetGINCount();
// 	int nGoutCount = pDatasMngr->GetGOUTCount();
// 	int nSmvType = pDatasMngr->GetSmvType();

	TransToPTPara_SMV();
	TransToPTPara_Gin();
	TransToPTPara_Gout();
}

void CDvsParaToPTPara::TransToPTPara_SMV()
{

	switch (m_pIECPara->m_nSmvType)
	{
	case SMVTYPE_91:
		TransToPTPara_SMV_91();
		break;
	case SMVTYPE_92:
		TransToPTPara_SMV_92();
		break;
	case SMVTYPE_6044:
		TransToPTPara_SMV_60448();
		break;
	}

}

void CDvsParaToPTPara::TransToPTPara_SMV_91()
{
	int nInsertPos = 0;
	nInsertPos = GetSubPara1(_T("<MU>"),_T("</MU>"));

	if (nInsertPos < 0)
	{
		return;
	}

	m_strPtPara.Delete(nInsertPos, m_strSubPara1.GetLength());

	for (int i=0;i<IEC_92_GROUPCOUNT;i++)
	{
		TransToPTPara_SMV_91_Sub(i);
	}

	m_strPtPara.Insert(nInsertPos, m_strSubPara1);

}

void CDvsParaToPTPara::TransToPTPara_SMV_92()
{
	int nInsertPos = 0;
	nInsertPos = GetSubPara1(_T("<IEC61850-9-2>"), _T("</IEC61850-9-2>"));

	if (nInsertPos < 0)
	{
		return;
	}
	m_strPtPara.Delete(nInsertPos, m_strSubPara1.GetLength());

	CString strTemp,strID;
	strTemp.Format(_T("%d"), m_pIECPara->m_sv_SmpRate);
	ReplaceSubPara(_T("SmpRate"), strTemp);
	strTemp.Format(_T("%d"), m_pIECPara->m_sv_ASDUNumber);
	ReplaceSubPara(_T("NoASDU"), strTemp);
	strTemp.Format(_T("%d"), m_pIECPara->m_sv_QualityCancel);
	ReplaceSubPara(_T("CancelQuality"), strTemp);

	for (int i=0;i<8;i++)
	{
		strID.Format(_T("Vscale%s"), 65+i);
		strTemp.Format(_T("%.3f"), m_pIECPara->m_sv_Vscale[i]);
		ReplaceSubPara(strID, strTemp);
		strID.Format(_T("Iscale%s"), 65+i);
		strTemp.Format(_T("%.3f"), m_pIECPara->m_sv_Iscale[i]);
		ReplaceSubPara(strID, strTemp);
	}

	strTemp.Format(_T("%d"), m_pIECPara->m_sv_Security);
	ReplaceSubPara(_T("Security"), strTemp);
	strTemp.Format(_T("%d"), m_pIECPara->m_sv_DatSet);
	ReplaceSubPara(_T("DatSet"), strTemp);
	strTemp.Format(_T("%d"), m_pIECPara->m_sv_RefrTm);
	ReplaceSubPara(_T("RefrTm"), strTemp);
	strTemp.Format(_T("%d"), m_pIECPara->m_sv_SmpRateCheck);
	ReplaceSubPara(_T("SmpRateCheck"), strTemp);

	for (int i=0;i<IEC_92_GROUPCOUNT;i++)
	{
		TransToPTPara_SMV_92_Sub(i);
	}

	m_strPtPara.Insert(nInsertPos, m_strSubPara1);

}

void CDvsParaToPTPara::TransToPTPara_SMV_60448()
{
	int nInsertPos = 0;
	nInsertPos = GetSubPara1(_T("<IEC60044-7>"), _T("</IEC60044-7>"));

	if (nInsertPos < 0)
	{
		return;
	}
	m_strPtPara.Delete(nInsertPos, m_strSubPara1.GetLength());

	for (int i=0;i<IEC_92_GROUPCOUNT;i++)
	{
		TransToPTPara_SMV_60448_Sub(i);
	}

	m_strPtPara.Insert(nInsertPos, m_strSubPara1);

}

void CDvsParaToPTPara::TransToPTPara_Gin()
{
	for (int i=0;i<IEC_GOOSESUB_GROUPCOUNT;i++)
	{
// 		GetSubPara1();
		TransToPTPara_Gin_Sub(i);
	}
}

void CDvsParaToPTPara::TransToPTPara_Gout()
{
	for (int i=0;i<IEC_GOOSEPUB_GROUPCOUNT;i++)
	{
		TransToPTPara_Gout_Sub(i);
	}
}

void CDvsParaToPTPara::TransToPTPara_SMV_91_Sub(int nIndex)
{
	m_nSmvIndex++;
}

void CDvsParaToPTPara::TransToPTPara_SMV_92_Sub(int nIndex)
{
	CString strBegin,strEnd,strTemp;
	strBegin.Format(_T("<Channel%s>"),65+nIndex);
	strEnd.Format(_T("</Channel%s>"),65+nIndex);

	int nInsertPos = GetSubPara2(strBegin, strEnd);

	if (nInsertPos < 0)
	{
		return;
	}

	m_strSubPara1.Delete(nInsertPos, m_strSubPara2.GetLength());
	m_strReplace = m_strSubPara2;

	PARA_SMV *pSmv = &m_pIECPara->m_paraSmv[nIndex];
	ReplaceSubPara(_T("Addr"), pSmv->m_strMacAddressDst);
	ReplaceSubPara(_T("Addrs"), pSmv->m_strMacAddressSrc);
	ReplaceSubPara(_T("SvID"), pSmv->m_tchSvID);
	strTemp.Format(_T("%04x"),pSmv->m_nAppid);
	ReplaceSubPara(_T("Appid"), strTemp);
	strTemp.Format(_T("%04x"),pSmv->m_nTCI);
	ReplaceSubPara(_T("Tci"), strTemp);
	strTemp.Format(_T("%d"),pSmv->m_nChannelCount);
	ReplaceSubPara(_T("Num"), strTemp);
	strTemp.Format(_T("%d"),pSmv->m_nSmpDelay);
	ReplaceSubPara(_T("DelayTime"), strTemp);
	strTemp.Format(_T("%d"),pSmv->m_nNetDelay);
	ReplaceSubPara(_T("NetWorkDelayTime"), strTemp);
	strTemp.Format(_T("%d"),pSmv->m_nSMVVersion);
	ReplaceSubPara(_T("CnfRev"), strTemp);
	strTemp.Format(_T("%d"),pSmv->m_nSyn);
	ReplaceSubPara(_T("Syn"), strTemp);
	ReplaceSubPara(_T("DatSet"), pSmv->m_tchDatSet);
	strTemp.Format(_T("%d"),pSmv->m_nSendPort+1);
	ReplaceSubPara(_T("PNFSendMode"), strTemp);

	CString strChannel;
	int nPos = GetSubPara(_T("<ChannelDef>"),_T("</ChannelDef>"),m_strSubPara2,strChannel);
	m_strSubPara2.Delete(nPos,strChannel.GetLength());
	strChannel = _T("<ChannelDef>");

	for (UINT i=1;i<=pSmv->m_nChannelCount;i++)
	{
		strTemp.Format(_T("C%d=%d;CQH%d=%04x;CQL%d=%04x;Name%d=保护电流%d;Unit%d=%d;"), i,pSmv->m_smvChsData[i-1].m_nMapIndex
				,i,pSmv->m_smvChsData[i-1].m_nQualityH,i,pSmv->m_smvChsData[i-1].m_nQualityL,i,i,i,pSmv->m_smvChsData[i-1].m_nUnit);
		strChannel += strTemp;
	}
// 	strChannel = _T("</ChannelDef>");

	m_strSubPara2.Insert(nPos, strChannel);
	m_strSubPara1.Insert(nInsertPos, m_strSubPara2);


	m_nSmvIndex++;
}

void CDvsParaToPTPara::TransToPTPara_SMV_60448_Sub(int nIndex)
{
	m_nSmvIndex++;
}

void CDvsParaToPTPara::TransToPTPara_Gin_Sub(int nIndex)
{
	CString strBegin,strEnd,strTemp;
	int nSub = (nIndex<8) ? nIndex+6:nIndex-7;
	strBegin.Format(_T("<Subscribe%d>"),nSub);
	strEnd.Format(_T("</Subscribe%d>"),nSub);

	int nInsertPos = GetSubPara1(strBegin, strEnd);

	if (nInsertPos < 0)
	{
		return;
	}

	m_strPtPara.Delete(nInsertPos, m_strSubPara1.GetLength());
	m_strReplace = m_strSubPara1;

	PARA_GOOSESUB *pGss = &m_pIECPara->m_paraGooseSub[nIndex];
	strTemp.Format(_T("%d"),!pGss->m_bSendSub);
	ReplaceSubPara(_T("GOOSECancel"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_bFilterMode);
	ReplaceSubPara(_T("FilterFlag"), strTemp);
	ReplaceSubPara(_T("GOOSEID"), pGss->m_tchGooseID);
	ReplaceSubPara(_T("MAC-Address"), pGss->m_strMacAddress);
	ReplaceSubPara(_T("gocbRef"), pGss->m_tchGocbRef);
	strTemp.Format(_T("%d"),pGss->m_nCnfRev);
	ReplaceSubPara(_T("CnfRev"), strTemp);
	ReplaceSubPara(_T("DatSet"), pGss->m_tchDataSet);
	strTemp.Format(_T("%d"),pGss->m_nLiveTime);
	ReplaceSubPara(_T("Hold"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_bNdsCom);
	ReplaceSubPara(_T("NdsCom"), strTemp);
	strTemp.Format(_T("%04x"),pGss->m_nAppid);
	ReplaceSubPara(_T("APPID"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_nSendPort+1);
	ReplaceSubPara(_T("SubPort"), strTemp);

	strTemp.Format(_T("%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d"), pGss->m_nInMap[0],pGss->m_nInMap[1],pGss->m_nInMap[2]
		,pGss->m_nInMap[3],pGss->m_nInMap[4],pGss->m_nInMap[5],pGss->m_nInMap[6],pGss->m_nInMap[7]);
	ReplaceSubPara(_T("InMap"), strTemp);
	strTemp.Format(_T("%d,%d,%d,%d,%d,%d,%d,%d"), pGss->m_nBitInMap[0],pGss->m_nBitInMap[1],pGss->m_nBitInMap[2]
		,pGss->m_nBitInMap[3],pGss->m_nBitInMap[4],pGss->m_nBitInMap[5],pGss->m_nBitInMap[6],pGss->m_nBitInMap[7]);
	ReplaceSubPara(_T("BitInMap"), strTemp);

	m_strPtPara.Insert(nInsertPos, m_strSubPara1);

	m_nGinIndex++;
}

void CDvsParaToPTPara::TransToPTPara_Gout_Sub(int nIndex)
{
	CString strBegin,strEnd,strTemp;
	strBegin.Format(_T("<GOOSESIM%d>"),65+nIndex);
	strEnd.Format(_T("</GOOSESIM%d>"),65+nIndex);

	int nInsertPos = GetSubPara1(strBegin, strEnd);

	if (nInsertPos < 0)
	{
		return;
	}

	m_strPtPara.Delete(nInsertPos, m_strSubPara1.GetLength());
	m_strReplace = m_strSubPara1;

	PARA_GOOSEPUB *pGss = &m_pIECPara->m_paraGoosePub[nIndex];
	ReplaceSubPara(_T("GcRef"), pGss->m_tchGocbRef);
	ReplaceSubPara(_T("GoID"), pGss->m_tchGooseID);
	ReplaceSubPara(_T("MAC"), pGss->m_strMacAddressDst);
	ReplaceSubPara(_T("MAC-Address"), pGss->m_strMacAddressDst);
	ReplaceSubPara(_T("SOURCEMAC"), pGss->m_strMacAddressSrc);
	strTemp.Format(_T("%d"),pGss->m_nLiveTime);
	ReplaceSubPara(_T("Hold"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_nCnfRev);
	ReplaceSubPara(_T("CnfRev"), strTemp);
	ReplaceSubPara(_T("DatSet"), pGss->m_tchDataSet);
	strTemp.Format(_T("%d"),pGss->m_bTestMode);
	ReplaceSubPara(_T("Test"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_bNdsCom);
	ReplaceSubPara(_T("NdsCom"), strTemp);
	strTemp.Format(_T("%04x"),pGss->m_nTCI);
	ReplaceSubPara(_T("TCI_SIM"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_bSendPub);
	ReplaceSubPara(_T("Cancel"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_nSendPort);
	ReplaceSubPara(_T("SubPort"), strTemp);
	strTemp.Format(_T("%04x"),pGss->m_nAppid);
	ReplaceSubPara(_T("APPID"), strTemp);

	strTemp.Format(_T("%d"),pGss->m_nT1);
	ReplaceSubPara(_T("T1"), strTemp);
	strTemp.Format(_T("%d"),pGss->m_nT0);
	ReplaceSubPara(_T("T0"), strTemp);
	ReplaceSubPara(_T("tQuality"), pGss->m_strTQuality);
	strTemp.Format(_T("%d"),pGss->m_nGroupDelay);
	ReplaceSubPara(_T("NetworkDelay"), strTemp);


	CString strChannel;
	int nPos = GetSubPara(_T("<Dataset>{"),_T("}</Dataset>"),m_strSubPara1,strChannel);
	m_strSubPara1.Delete(nPos,strChannel.GetLength());
	strChannel = _T("<Dataset>{N:");
	strChannel += pGss->m_tchGoosePubData;
	strChannel.Delete(strChannel.GetLength()-1);
	strChannel.Replace(_T(","), _T(",N:"));
	m_strSubPara1.Insert(nPos, strChannel);

	m_strPtPara.Insert(nInsertPos, m_strSubPara1);

	m_nGoutIndex++;
}

//////////////////////////////////////////////////////////////////////////
//通道数据转换

//////////////////////////////////////////////////////////////////////////
BOOL CDvsParaToPTPara::GetFileData(CString strPath)
{
	BOOL bReturn = FALSE;

	if (IsFileExist(strPath))
	{
		CFile file;
		if (file.Open(strPath,CFile::modeRead))
		{
			UINT iLen = (UINT)file.GetLength();
			TCHAR *cBuff = new TCHAR [iLen+1];
			file.Read(cBuff,iLen);
			file.Close();
			cBuff[iLen]=0;
			m_strPtPara = cBuff;
			delete []cBuff;
			bReturn = TRUE;
		}
	}

	return bReturn;
}

int CDvsParaToPTPara::GetSubPara1(CString strBegin, CString strEnd)
{
	return GetSubPara(strBegin,strEnd,m_strPtPara,m_strSubPara1);
}

int CDvsParaToPTPara::GetSubPara2(CString strBegin, CString strEnd)
{
	return GetSubPara(strBegin,strEnd,m_strSubPara1,m_strSubPara2);
}

int  CDvsParaToPTPara::GetSubPara(CString strBegin, CString strEnd, CString strBasePara, CString &strSubPara)
{
	int nBegin = strBasePara.Find(strBegin, 0);
	int nEnd = strBasePara.Find(strEnd, nBegin);

	if (nEnd>nBegin && nBegin>=0)
	{
		strSubPara = strBasePara.Mid(nBegin, nEnd-nBegin);
	}

	return nBegin;
}

int  CDvsParaToPTPara::ReplaceSubPara(CString strID, CString strNew)
{
	CString strFind = strID + _T("=");
	int		nBegin = m_strReplace.Find(strFind,0);
	int		nEnd = m_strReplace.Find(_T(";"),nBegin);

	if (nEnd>nBegin && nBegin>=0)
	{
		CString strOld = m_strReplace.Mid(nBegin, nEnd-nBegin);
		CString strReplace = strFind+strNew;
		m_strReplace.Replace(strOld, strReplace);
		return 0;
	}

	return -1;
}
