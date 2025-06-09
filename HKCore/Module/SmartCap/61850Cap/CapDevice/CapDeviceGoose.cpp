//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceGoose.cpp  CCapDeviceGoose


#include "stdafx.h"
#include "CapDeviceGoose.h"
#include "../../../System/VariantData.h"

CCapDeviceGoose::CCapDeviceGoose()
{
	//��ʼ������
	m_dwVID = 0;
	m_dwVersion = 0;
	m_nTest = 0;
	m_dwTimeAllowToAlive = 0;
	m_dwStNum = 0;
	m_dwSqNum = 0;
	m_dwNdsCom = 0;
	m_dTime = 0;

	//��ʼ����Ա����
	m_pXWndInterface = NULL;
}

CCapDeviceGoose::~CCapDeviceGoose()
{
}

void CCapDeviceGoose::InitDevice(CIecCfgDataBase *pIecCfgData)
{
	m_pIecCfgData = pIecCfgData;

	if(pIecCfgData == NULL)
	{
		return;
	}

	CIecCfgGooseDataBase* pCfgGoose = (CIecCfgGooseDataBase*)pIecCfgData;

	m_nType = PROTOCOL_61850_TYPE_GOOSE;
	m_strGooseId = pCfgGoose->m_strGooseId;
	m_dwAppID = pCfgGoose->m_dwAppID;
	m_strDestAddress = pCfgGoose->m_strDestAddress;
	m_strSrcAddress = pCfgGoose->m_strSrcAddress;
	m_strDataSet = pCfgGoose->m_strDataSet;

	CCapDeviceBase::InitDevice(pIecCfgData);
}

void CCapDeviceGoose::GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas)
{
	CCapDeviceGooseCh *pGSCh = NULL;
	EPCAPPARSEDATA pParseData;

	for (int nIndex = 0;nIndex<GetCount();nIndex++)
	{
		pGSCh = (CCapDeviceGooseCh *)GetAtIndex(nIndex);
		pParseData = pParseDatas->pDatas[nIndex];

		switch (pParseData.wChType)
		{
		case 0x83://����
			pGSCh->m_oVar = (unsigned char)pParseData.dwValue;
			break;
		case 0x85://ö��
			pGSCh->m_oVar = (int)pParseData.dwValue;
			break;
		case 0x86://UINT
			pGSCh->m_oVar = (int)pParseData.dwValue;
			break;
		case 0x91://ʱ��
			pGSCh->m_oVar = (long)pParseData.dwValue;
			break;
		case 0x87://����
		case 0x8A:
			pGSCh->m_oVar = (float)pParseData.dwValue;
			break;
		case 0x84://˫��
		default:
			pGSCh->m_oVar = (DWORD)pParseData.dwValue;
			break;
		}
	}
}

void CCapDeviceGoose::AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead,long nBufferLenth)
{
	if (m_oPrevDatas.dwDatas == 0)
	{
		return;
	}

	long nIndex = 0;
	CCapDeviceGooseCh *pCh = NULL;
	PEP_GOOSE_BINARY_TURN pNew = NULL;
	PEPCAPPARSEDATA pPreChData = NULL,pCurrChData = NULL;

	for (nIndex=0;   nIndex  <  pDatas->dwDatas; nIndex++)
	{
		pPreChData = &m_oPrevDatas.pDatas[nIndex];
		pCurrChData = &pDatas->pDatas[nIndex];
			
		//ֻ���ǵ��㡢˫��
		if (pCurrChData->wChType != 0x83 && pCurrChData->wChType != 0x84)
		{
			continue;
		}

		if ( pPreChData->dwValue != pCurrChData->dwValue )
		{
			pNew = m_oBinaryTurns.New();
			pCh = (CCapDeviceGooseCh *)GetAtIndex(nIndex);

			pNew->pChRef = pCh;
			pNew->n64Time = pDatas->n64Time;
			pNew->nChIndex = nIndex;
			pNew->nChType = pCurrChData->wChType;
			pNew->nChLenth = pCurrChData->wLength;
			pNew->nValue = pCurrChData->dwValue;
		}
	}

	if (m_pXWndInterface != NULL)
	{
		m_pXWndInterface->PostMessage(WM_UPDATE_GOOSE_SPY, (unsigned long)pDatas, (unsigned long)pDatas);
	}
}

//2022-5-31  ���δ˺������˺���Ч�ʺܵͣ�ʵʱ��������
//2020-6-20  lijunqing  ����ͻ����߱仯��
/*
void CCapDeviceGoose::AnalysisData(PEPCAPPARSEDATAS pDatas)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GOOSE������AnalysisData %d") , 111111);
	long nIndex = 0;
	CCapDeviceGooseCh *pCh = NULL;

	if (m_oPrevDatas.dwDatas == 0)
	{
		return;
	}

	for (nIndex=0;   nIndex  <  pDatas->dwDatas; nIndex++)
	{

		if ( m_oPrevDatas.pDatas[nIndex].dwValue != pDatas->pDatas[nIndex].dwValue )
		{

			if ( pDatas->pDatas[nIndex].wChType == 0x83 || pDatas->pDatas[nIndex].wChType == 0x84)
			{

				pCh = (CCapDeviceGooseCh *)GetAtIndex(nIndex);

				if (pCh->m_pRefDvmData == NULL)
				{
					continue;
				}

				CDvmData *pData = (CDvmData *)pCh->m_pRefDvmData;

				CDvmValue *pValue = pData->FindByID_MmsAttr(_T("$stVal"));
				if (pValue != NULL)
				{
					if (pDatas->pDatas[nIndex].wChType == 0x84)
					{
						short nTemp = pDatas->pDatas[nIndex].dwValue;

						CString strMy;
						CString strMyTemp;
						int  nSubLen   =  (nTemp  & 0xff00)>>8;
						int  nLength =  (nTemp & 0x00ff); // �������˲�ֵ��������͵���nDeltValueλ��Ҫ�ˣ�Ĩȥ��
						BYTE byTemp[80] = {0};
						::memcpy(byTemp, &nTemp, 2);
						byTemp[0] = nLength;
						byTemp[1] = nSubLen;

						for (int i = 0 ;i < 1;i++)
						{
							strMyTemp.Format(_T("%.2X"), byTemp[0]);
							strMy += strMyTemp;
						}
						CString str_Bin = HexToBin(strMy);
						int t_RL = str_Bin.GetLength();
						int nValueLength = nLength;
						nValueLength = 2;
						for (int i = t_RL; i < (nValueLength - 1) * 8; i++)
							str_Bin.Insert(0, '0');

						CString strResult;
						strResult = str_Bin.Mid(0, str_Bin.GetLength() - nSubLen);
						int adf = 0;

						if (strResult=="01")
							pValue->m_strValue  = "0";
						else if (strResult=="10")
							pValue->m_strValue  = "1";
						//pValue->m_strValue  = "[ " + strResult + " ]";

						//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("˫���λ %s")  ,pValue->m_strValue);

					}				
					else
						pValue->m_strValue.Format(_T("%d"),  pDatas->pDatas[nIndex].dwValue);
				}


				pValue = pData->FindByID_MmsAttr(_T("$t"));
				if (pValue != NULL)
				{
					ep_cap_timeval_to_string_ns(pDatas->n64Time, pValue->m_strValue);
				}

				g_pSmartCapSoeCycleArray->AddExBaseObject(pData);
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("AddExBaseObject ˫���λ %d") , 111111);
			}
		}
	}
}
*/

//���ݽ��ܳ�ʱ
BOOL CCapDeviceGoose::IsDataRcvOverTime()
{
	return m_oTickCount.GetTickCountLong(FALSE) > 30000; 
}

void CCapDeviceGoose::UpdateDvmDeviceDatasType(UINT nType, UINT nLen,CString&strValue)
{
	CString strDataType;
	strDataType = _T("����");

	switch (nType)
	{
	case 0x83://����
		strDataType = _T("����");
		break;
	case 0x84://˫��
		// 		if (nLen == 2)//20220623 zhouhj �����ֽڳ����޷��ж�˫�㡢Ʒ�ʵ���Ϣ
		// 		{
		// 			return _T("˫��");
		// 		}
		// 		else if(nLen == 3)//13λ�̶�ΪƷ��,����Ϊλ��  20220613 zhouhj
		// 		{
		// 			return _T("Ʒ��");
		// 		}
		// 		else
		{
			strDataType = _T("λ��");
		}
		break;
	case 0x85://ö��
		if (nLen == 2)
		{
			strDataType = _T("ö��");
		} 
		else
		{
			strDataType =  _T("INT");
		}
		break;
	case 0x86://UINT
		strDataType =  _T("UINT");
		break;
	case 0x91://ʱ��
		strDataType =  _T("ʱ��");
		break;
	case 0x87://����
		strDataType =  _T("����");
		break;
	case 0xA2://�ṹ��  20220615 zhouhj
		strDataType =  _T("�ṹ");
		break;
	default:
		strDataType = _T("����");
		break;
	}

	if (strDataType != strValue)
	{
		strValue = strDataType;
	}

}
void CCapDeviceGoose::UpdateDvmDeviceDatas()
{
	if (m_pRefDvmDataset == NULL)
	{
		return;
	}

	POS pos = m_pRefDvmDataset->GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pRefDvmDataset->GetNext(pos);
		ep_get_CapParseData_value(m_oPrevDatas.pDatas[nIndex], pData->m_strValue);
		UpdateDvmDeviceDatasType(m_oPrevDatas.pDatas[nIndex].wChType,m_oPrevDatas.pDatas[nIndex].wLength,pData->m_strDataType);//20240704 suyang ���Ӷ������жϣ�����ͨ����������
/*
		EPCAPPARSEDATA pchData = m_oPrevDatas.pDatas[nIndex];
		
		switch(pchData.wChType)
		{
		case 0x83:   //����
			pData->m_strValue.Format(_T("%d"), pchData.dwValue);
			break;
		case 0x85://ö��
			pData->m_strValue.Format(_T("%d"), pchData.dwValue);
			break;
		case 0x86://UINT
			pData->m_strValue.Format(_T("%d"), pchData.dwValue);
			break;
		case 0x91://ʱ��
			struct timeval ts;
			EPTIME64EX tm;
			ts.tv_sec = pchData.dwValue;   //��
			ts.tv_usec = pchData.dwValue2 / 1000;  //ns ==>> us
			ep_cap_timeval_to_64timeex(ts, tm);
			Ep_EPTIME64Ex_To_String(tm, pData->m_strValue);
			break;
		case 0x87://����
		case 0x8A:
			pData->m_strValue.Format(_T("%.3f"), pchData.dwValue);
			break;
		case 0x84://˫��
			if (pchData.dwValue == 0)
			{
				pData->m_strValue = _T("00");
			}
			else if (pchData.dwValue == 1)
			{
				pData->m_strValue = _T("01");
			}
			else if (pchData.dwValue == 2)
			{
				pData->m_strValue = _T("10");
			}
			else
			{
				pData->m_strValue = _T("11");
			}
			break;
		default:
			pData->m_strValue.Format(_T("%d"), pchData.dwValue);
			break;
		}
*/

		nIndex++;
	}
}

void CCapDeviceGoose::Reset()
{
	CCapDeviceBase::Reset();
	m_oBinaryTurns.Reset();
}

void CCapDeviceGoose::ClearAnalysisResultErrors()
{
	for (int nIndex = 0;nIndex<PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM;nIndex++)
	{
		m_oAnalysisResults.rslt_gs.nErrorType[nIndex] = 0;
	}

	m_oAnalysisResults.nPkgNum = 0;
}

void CCapDeviceGoose::SetIecCfgGin_ByCapDevice(CIecCfgGinData* pIecCfgGinData)
{
// 	char destOut[20] = {0};
// 	ByteToHexStr(	(unsigned char*) m_oPrevDatas.destMAC, destOut, 6);
// 	destOut[12] = '\0';
	m_strDestAddress = GetMacStringFromByte((unsigned char *)m_oPrevDatas.destMAC);
// 	ByteToHexStr(	(unsigned char*) m_oPrevDatas.srcMAC, destOut, 6);
// 	destOut[12] = '\0';
	m_strSrcAddress = GetMacStringFromByte((unsigned char *)m_oPrevDatas.srcMAC);
	m_strGooseId = m_oPrevDatas.oDataGs.GOID;
    m_strDataSet = m_oPrevDatas.oDataGs.GODataSet;//wangtao ����̽������DataSet�ȶ� 20240509 ��ͬ
//	m_strDataSet = m_oPrevDatas.oDataGs.GORef;
	m_strgocbRef = m_oPrevDatas.oDataGs.GORef;

	pIecCfgGinData->m_nUseFlag = 1;
	pIecCfgGinData->m_nFiberIndex = m_nFiberIndex;
	pIecCfgGinData->m_strDestAddress = m_strDestAddress;
	pIecCfgGinData->m_strSrcAddress = m_strSrcAddress;
	pIecCfgGinData->m_dwVLandID = m_dwVID;
	pIecCfgGinData->m_dwVersion = m_dwVersion;
	pIecCfgGinData->m_strGooseId = m_strGooseId;
	pIecCfgGinData->m_strDataSet = m_strDataSet;
	pIecCfgGinData->m_strgocbRef = m_strgocbRef;
	pIecCfgGinData->m_bNdsCom = m_dwNdsCom;
	pIecCfgGinData->m_dwAppID = m_dwAppID;

//		pIecCfgGinData->m_dwVLandPriority = pCapDeviceGs->m_pristrSrcAddress;
	pIecCfgGinData->SetChannelNum(GetCount());
	CIecCfgChsBase* pCfgChs = pIecCfgGinData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CCapDeviceGooseCh *pCapDeviceGooseCh = NULL;
	CIecCfgDataGooseChBase *pIecCfgGsCh = NULL;
	long nChIndex = 0;

	while(pos)
	{
		pCapDeviceGooseCh = (CCapDeviceGooseCh*)GetNext(pos);
		pIecCfgGsCh = (CIecCfgDataGooseChBase*)pCfgChs->GetAt(nChIndex);

		if (pIecCfgGsCh != NULL)
		{
			pIecCfgGsCh->m_strDataType = pCapDeviceGooseCh->GetIecCfgChDataType();
		}

		nChIndex++;
	}
}

void CCapDeviceGoose::SetIecCfgGout_ByCapDevice(CIecCfgGoutData* pIecCfgGoutData)
{
	m_strDestAddress = GetMacStringFromByte((unsigned char *)m_oPrevDatas.destMAC);
	m_strSrcAddress = GetMacStringFromByte((unsigned char *)m_oPrevDatas.srcMAC);
	m_strGooseId = m_oPrevDatas.oDataGs.GOID;
    m_strDataSet = m_oPrevDatas.oDataGs.GODataSet;
	m_strgocbRef = m_oPrevDatas.oDataGs.GORef;

	pIecCfgGoutData->m_nUseFlag = 1;
	pIecCfgGoutData->m_nFiberIndex = m_nFiberIndex;
	pIecCfgGoutData->m_strDestAddress = m_strDestAddress;
	pIecCfgGoutData->m_strSrcAddress = m_strSrcAddress;
	pIecCfgGoutData->m_dwVLandID = m_dwVID;
	pIecCfgGoutData->m_dwVersion = m_dwVersion;
	pIecCfgGoutData->m_strGooseId = m_strGooseId;
	pIecCfgGoutData->m_strDataSet = m_strDataSet;
	pIecCfgGoutData->m_strgocbRef = m_strgocbRef;
	pIecCfgGoutData->m_bNdsCom = m_dwNdsCom;
	pIecCfgGoutData->m_dwAppID = m_dwAppID;
//		pIecCfgGinData->m_dwVLandPriority = pCapDeviceGs->m_pristrSrcAddress;
	pIecCfgGoutData->SetChannelNum(GetCount());

	CIecCfgChsBase* pCfgChs = pIecCfgGoutData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CCapDeviceGooseCh *pCapDeviceGooseCh = NULL;
	CIecCfgDataGooseChBase *pIecCfgGsCh = NULL;
	long nChIndex = 0;

	while(pos)
	{
		pCapDeviceGooseCh = (CCapDeviceGooseCh*)GetNext(pos);
		pIecCfgGsCh = (CIecCfgDataGooseChBase*)pCfgChs->GetAt(nChIndex);

		if (pIecCfgGsCh != NULL)
		{
			pIecCfgGsCh->m_strDataType = pCapDeviceGooseCh->GetIecCfgChDataType();
		}

		nChIndex++;
	}
}