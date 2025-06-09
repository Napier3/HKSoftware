//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDataSmDbFile.cpp  CCapDataSmDbFile


#include "stdafx.h"
#include "CapDataSmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapDataSmDbArea::CCapDataSmDbArea()
{
	m_pEpDeviceDatasBuffer[0] = 0;
}

CCapDataSmDbArea::~CCapDataSmDbArea()
{
	
}


void CCapDataSmDbArea::Write(CCapCycleMemBufferMngr *pBufferMngr,  EPSMDBFILEPOS &oSmDbFilePos)
{
// 	CString strMsg;
// 	strMsg.Format(_T(" n64CapFrmDvCurrPos=%I64d\r\n n64DbIndexCurrPos==%I64d")
// 		, oSmDbFilePos.n64CapFrmDvCurrPos
// 		, oSmDbFilePos.n64DbIndexCurrPos);
// 	AfxMessageBox(strMsg);

	POS pos = pBufferMngr->GetHeadPosition();
//	long nFrameLen = 0;
	long nDeviceDataLen = 0;
	long nIndex = 0;

	while (pos != NULL)
	{
		CCapCycleMemBuffer *pCapBuffer = (CCapCycleMemBuffer*)pBufferMngr->GetAt(pos);

		if (pCapBuffer->Ebs_BeWrited())
		{
			pBufferMngr->GetNext(pos);
			continue;
		}

		nDeviceDataLen = WriteDeviceData(pCapBuffer, 0);//nFrameLen);

		if (nDeviceDataLen > 0)
		{
			pCapBuffer->m_n64DataPos = SmWrite(m_pEpDeviceDatasBuffer, nDeviceDataLen);// nFrameLen + nDeviceDataLen);
			pCapBuffer->m_dwDeviceDataLen = nDeviceDataLen;
		}
		else
		{
			pCapBuffer->m_n64DataPos = m_pSmFile->GetCurr64Pos();
			pCapBuffer->m_dwDeviceDataLen = 0;
		}

		//pCapBuffer->SetState(EBS_HASWRITE);

		pBufferMngr->GetNext(pos);
		nIndex++;
	}

	oSmDbFilePos.n64CapDataBeginPos = m_n64AreaBeginPos;
	oSmDbFilePos.n64CapDataCurrPos  = GetCurrPos();

	if (oSmDbFilePos.dwDbCapFrmDvState == 0)
	{
		if (IsMapCycle())
		{
			oSmDbFilePos.dwDbCapFrmDvState = 1;
		}
	}
}

long CCapDataSmDbArea::WriteDeviceData(CCapCycleMemBuffer *pBuffer, long nWritePos/*, EPSMDBFILEPOS &oSmDbFilePos*/)
{
	long nLen = 0;
	long nIndex = 0;
	long nCount = 0;
	CEpDeviceDatas *pDatas = pBuffer->m_pDeviceDatas;
	BYTE *p = m_pEpDeviceDatasBuffer + nWritePos;

	if (pDatas == NULL)
	{
		return 0;
	}

	nCount = pDatas->GetCount();

	if (nCount == 0)
	{
		return 0;
	}

	long nSize = 0;//sizeof(nCount);
// 	memcpy(p, &nCount, nSize);
// 	nLen += nSize;
// 	p += nSize;
//	
// 	nSize = sizeof(pDatas->m_nDeviceDataType);
// 	memcpy(p, &(pDatas->m_nDeviceDataType), nSize);
// 	nLen += nSize;
// 	p += nSize;

	EPCAPDBDATA oData;
	oData.ipGroup = pBuffer->m_ipGroup;
	oData.tm = pBuffer->m_ts;
	oData.nProtocol = pBuffer->m_nProtocol;  //规约类型

	if (nCount > 0)
	{
		POS pos = pDatas->GetHeadPosition();
		CEpY4Data *pData = NULL;
		long nTemp = 0;

		while (pos != NULL)
		{
			pData = pDatas->GetNext(pos);
			nSize = pData->WriteToData(oData);
			nTemp += sizeof(oData);
			memcpy(p, &oData, sizeof(EPCAPDBDATA));
			p += sizeof(EPCAPDBDATA);
		}

		nLen += nTemp;
	}

	return nLen;
}

// 
// void CCapDataSmDbArea::ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer)
// {
// 	long nLen = pIndex->nFrameLen;// + pIndex->nDeviceDataLen;
// 	BYTE *pFrmBuffer = (BYTE*)Read(pIndex->n64CapDataPos, nLen);
// 
// 	if (pFrmBuffer != NULL)
// 	{
// 		pBuffer->Init(pFrmBuffer, nLen);
// 	}
// }
// 

long CCapDataSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, CEpQueryIndex0Ranges &oIndex0Ranges, CEpDeviceDatasMngr &oQuery)
{
	POS pos = oIndex0Ranges.GetHeadPosition();
	CEpQueryIndex0Range  *pRange = NULL;
	long nReturn = 0;

	while (pos != NULL)
	{
		pRange = oIndex0Ranges.GetNext(pos);

		nReturn = Query(oSearchConfig, pRange->m_pIndex0, pRange->m_pIndex1, oQuery);

		if (nReturn == -1)
		{
			break;
		}
	}

	return nReturn;
}

long CCapDataSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX0EX pIndex1, PEPCAPDBBUFFERINDEX0EX pIndex2, CEpDeviceDatasMngr &oQuery)
{
	if (oQuery.GetCount() >= oSearchConfig.dwMaxQuery)
	{
		return -1;
	}

	long nReturn = 0;

	if (pIndex1->n64DataPos < pIndex2->n64DataPos)
	{
		nReturn = Query(oSearchConfig, pIndex1->n64DataPos, pIndex2->n64DataPos, oQuery); 
	}
	else
	{
		nReturn = Query(oSearchConfig, pIndex1->n64DataPos, m_n64AreaEndPos, oQuery); 

		if (nReturn != -1)
		{
			nReturn = Query(oSearchConfig, m_n64AreaBeginPos, pIndex2->n64DataPos, oQuery); 
		}
	}

	return 0;
}

long CCapDataSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, volatile __int64 &n64BeginPos, volatile __int64 &n64EndPos, CEpDeviceDatasMngr &oQuery)
{
	if (oQuery.GetCount() >= oSearchConfig.dwMaxQuery)
	{
		return -1;
	}

	long dwLength = (DWORD)(n64EndPos - n64BeginPos);
	m_pSmFile->UnMapView();
	BYTE *pBuffer = NULL;
	EPTIME64 tmBegin = oSearchConfig.tmBegin;
	EPTIME64 tmEnd = oSearchConfig.tmEnd;
	long nReturn = 0;

	while (TRUE)
	{
		if (nReturn == -1)
		{
			break;
		}

		if (MapView(n64BeginPos, m_dwOnceMapSize) == NULL)
		{
			break;
		}

		pBuffer = (BYTE*)m_pSmFile->GetCurrPos();
		BYTE *pTemp = pBuffer;
		BYTE *pEnd = pBuffer + m_dwOnceMapSize;

		while (pTemp < pEnd)
		{
			EPCAPDBDATA *pIndex = (EPCAPDBDATA*)pTemp;
			pTemp += sizeof(EPCAPDBDATA);
			nReturn = Query(oSearchConfig, pIndex, oQuery);

			dwLength = dwLength - sizeof(EPCAPDBDATA);

			if (dwLength <= 0)
			{
				break;
			}

			if (nReturn == -1)
			{
				break;
			}
		}

		if (dwLength <= 0)
		{
			break;
		}

		n64BeginPos += m_dwOnceMapSize;
	}

	return nReturn;
}

long CCapDataSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, EPCAPDBDATA *pIndex, CEpDeviceDatasMngr &oQuery)
{
	if (oQuery.GetCount() >= oSearchConfig.dwMaxQuery)
	{
		return -1;
	}

	//时间范围
	if (!Ep_IsTimeIn(oSearchConfig.tmBegin, oSearchConfig.tmEnd, pIndex->tm))
	{
		return 0;
	}

	//规约类型
	if (oSearchConfig.dwUseProtocol)
	{
		if (Ep_GetProtocol_ProtoType_Proto(pIndex->nProtocol) != oSearchConfig.dwProtocol)
		{
			return 0;
		}
	}

	// 
	//搜索类型，不是原始规约报文
	if (Ep_GetProtocol_FrameType(pIndex->nProtocol) == 0)
	{
		return 0;
	}
// 	if (oSearchConfig.dwUseSearchType)
// 	{
// 		if (oSearchConfig.dwSearchType != EP_SEARCH_TYPE_FRAME)
// 		{
// 		}
// 		else
// 		{
// 			if (Ep_GetProtocol_FrameType(pIndex->nProtocol) == 0)
// 			{
// 				return 0;
// 			}
// 		}
// 	}

	//地址
	if (oSearchConfig.dwUseDir)
	{
		if (!QueryAddr(oSearchConfig, pIndex->ipGroup))
		{
			return 0;
		}

		if (oSearchConfig.dwDatasIndexCount != 0)
		{
			if (!Ep_IsDatasIndexIn(oSearchConfig, pIndex->nDataAddr))
			{
				return 0;
			}
		}
	}

	oQuery.AddData(pIndex->tm, pIndex->nProtocol, pIndex->nDataAddr, pIndex->fValue);

	return 0;
}

BOOL CCapDataSmDbArea::QueryAddr(EPCAPSEARCHCONFIG &oSearchConfig, EP_ETHER_CAP_IP_GROUP &ipGroup)
{
	long nIndex = 0;
	long nCount = oSearchConfig.dwAddrDirCount;
	PEPCAPSEARCHADDRDIR pAddrs = oSearchConfig.oAddrDir;
	BOOL bTrue = FALSE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		PEPCAPSEARCHADDRDIR pAddr = pAddrs + nIndex;

		if (pAddr->dwType == EPCAP_SEARCH_ADDR_DIR_TYPE_SERIAL)
		{
			//非Serial
			if (ipGroup.src.ip.s_addr != 0)
			{
				bTrue = FALSE;
				break;
			}

			//Serial 不一致
			if (pAddr->dwSrcAddr == ipGroup.src.port)
			{
				bTrue = TRUE;
				break;
			}
		}
		else
		{
			//非IP
			if (ipGroup.src.ip.s_addr == 0)
			{
				bTrue = FALSE;
				break;

			}

			if (ep_CapSearchAddr_UseSrc( pAddr->dwUse ) && ep_CapSearchAddr_UseDest( pAddr->dwUse ))
			{
				if (ipGroup.src.ip.s_addr == pAddr->dwSrcAddr && ipGroup.dst.ip.s_addr == pAddr->dwDestAddr)
				{
					bTrue = TRUE;
					break;
				}
			}
			else
			{
				if (ep_CapSearchAddr_UseSrc( pAddr->dwUse ))
				{
					if (ipGroup.src.ip.s_addr == pAddr->dwSrcAddr)
					{
						bTrue = TRUE;
						break;
					}
				}
				
				else if (ep_CapSearchAddr_UseDest( pAddr->dwUse ))
				{
					if (ipGroup.dst.ip.s_addr == pAddr->dwDestAddr)
					{
						bTrue = TRUE;
						break;
					}
				}
			}
		}
	}

	return bTrue;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
const CString CCapDataSmDbFile::g_strCapDataSmDbFile = _T("EpCapData.esmdb");
const CString CCapDataSmDbFile::g_strCapDataSmDbID   = _T("_ep_cap_data_esmdb");

CCapDataSmDbFile::CCapDataSmDbFile()
{
	//初始化属性
	m_pFrameSmDbArea = NULL;
	m_strName = g_strCapDataSmDbID;
	m_strID = g_strCapDataSmDbID;

	//初始化成员变量
}

CCapDataSmDbFile::~CCapDataSmDbFile()
{
}

void CCapDataSmDbFile::CreateCapDataSmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapDataSmDbFile;
	CreateCapSmDbFile(strFile, g_strCapDataSmDbID, nDataSize);

	m_pFrameSmDbArea = new CCapDataSmDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	m_pFrameSmDbArea->UnMap();
	AddNewChild(m_pFrameSmDbArea);
}

void CCapDataSmDbFile::LocatePos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos)
{
	m_pFrameSmDbArea->LocateAreaPos(n64BeginPos, n64CurrPos);
}

void CCapDataSmDbFile::CreateCapDataSmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapDataSmDbFile;
	CreateCapSmDbFile(strFile, g_strCapDataSmDbID, nDataSize);

	m_pFrameSmDbArea = new CCapDataSmDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	AddNewChild(m_pFrameSmDbArea);
}

