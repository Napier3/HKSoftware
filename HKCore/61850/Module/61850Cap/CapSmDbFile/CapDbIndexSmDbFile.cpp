//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDbIndexSmDbFile.cpp  CCapDbIndexSmDbFile


#include "stdafx.h"
#include "CapDbIndexSmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapDbIndexSmDbArea::CCapDbIndexSmDbArea()
{
	m_nCurrWriteIndex = 0;
}

CCapDbIndexSmDbArea::~CCapDbIndexSmDbArea()
{
	
}

void CCapDbIndexSmDbArea::CreateArea(const CString &strID, volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize)
{
	CSmDbAreaBase::CreateArea(strID, n64BeginPos, n64Length, dwOnceMapSize);
	m_n64MaxIndexCount = n64Length;
	m_n64MaxIndexCount /= sizeof(EPCAPDBBUFFERINDEX);
}

long CCapDbIndexSmDbArea::Write(CFrameMemBufferMngr *pBufferMngr,  CCapDbIndex0SmDbFile *pIndexSmDbFile, EPSMDBFILEPOS &oSmDbFilePos, long nBeginIndex, long nEndIndex, EPCAPDBBUFFERINDEX &oIndex)
{
	long nIndex = 0;
	long nCapIndexCounter = 0;
	//EPCAPDBBUFFERINDEX oIndex;
	__int64 n64IndexPos = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CFrameMemBuffer *pBuffer = (CFrameMemBuffer*)pBufferMngr->GetFrameBuffer(nIndex);
	
		if (pBuffer->Ebs_BeWrited())
		{
			//pBufferMngr->GetNext(pos);
			nIndex++;
			continue;
		}

		pBuffer->GetCapDbIndex(oIndex);

		if (oSmDbFilePos.n64MaxCapID < oIndex.n64CapID)
		{
			oSmDbFilePos.n64MaxCapID = oIndex.n64CapID;
		}

		n64IndexPos = Write(oIndex);
		pIndexSmDbFile->AddIndex0(n64IndexPos, pBuffer->m_n64DataPos, oIndex.tm, FALSE);
//		tm = oIndex.tm;
		nCapIndexCounter++;
		nIndex++;
	}

	return nCapIndexCounter;
}


void CCapDbIndexSmDbArea::Write(CFrameMemBufferMngr *pBufferMngr,  CCapDbIndex0SmDbFile *pIndexSmDbFile, EPSMDBFILEPOS &oSmDbFilePos)
{
// 	CString strMsg;
// 	strMsg.Format(_T(" n64CapFrmDvCurrPos=%I64d\r\n n64DbIndexCurrPos==%I64d")
// 		, oSmDbFilePos.n64DbIndexBeginPos
// 		, oSmDbFilePos.n64DbIndexCurrPos);
// 	AfxMessageBox(strMsg);

	LocateAreaPos(oSmDbFilePos.n64DbIndexBeginPos, oSmDbFilePos.n64DbIndexCurrPos);

// 	strMsg.Format(_T(" n64CapFrmDvCurrPos=%I64d\r\n n64DbIndexCurrPos==%I64d")
// 		, oSmDbFilePos.n64CapFrmDvCurrPos
// 		, oSmDbFilePos.n64DbIndexCurrPos);
// 	AfxMessageBox(strMsg);

	EPCAPDBBUFFERINDEX oIndex;
	long nCapIndexCounter = 0;
	CFrameMemBuffer *pBuffer = NULL;
// 	EPTIME64 tm; //cap的时间
	long nIndex = 0;

	long nMaxCount = pBufferMngr->GetMaxCount();
	long nCurrCount = pBufferMngr->GetCurrCount();
	long nCurrIndex = pBufferMngr->GetCurrIndex();

	if (nCurrCount == nMaxCount)
	{
		if (m_nCurrWriteIndex < nCurrIndex)
		{
			nCapIndexCounter = Write(pBufferMngr, pIndexSmDbFile, oSmDbFilePos, m_nCurrWriteIndex, nCurrIndex-1, oIndex);
		}
		else
		{
			nCapIndexCounter = Write(pBufferMngr, pIndexSmDbFile, oSmDbFilePos, m_nCurrWriteIndex, nCurrCount-1, oIndex);
			nCapIndexCounter += Write(pBufferMngr, pIndexSmDbFile, oSmDbFilePos, 0, nCurrIndex-1, oIndex);
		}
	}
	else
	{
		nCapIndexCounter = Write(pBufferMngr, pIndexSmDbFile, oSmDbFilePos, m_nCurrWriteIndex, nCurrIndex-1, oIndex);
	}

/*
	//写Index
	while (pos != NULL)
	{
		pBuffer = (CFrameMemBuffer*)pBufferMngr->GetAt(pos);

		if (pBuffer->Ebs_BeWrited())
		{
			pBufferMngr->GetNext(pos);
			continue;
		}

		pBuffer->GetCapDbIndex(oIndex);

		if (oSmDbFilePos.n64MaxCapID < oIndex.n64CapID)
		{
			oSmDbFilePos.n64MaxCapID = oIndex.n64CapID;
		}

		pBuffer->m_n64IndexPos = Write(oIndex);
		pIndexSmDbFile->AddIndex0(pBuffer->m_n64IndexPos, pBuffer->m_n64DataPos, oIndex.tm, FALSE);
		tm = oIndex.tm;
		nCapIndexCounter++;

		pBufferMngr->GetNext(pos);
		nIndex++;
	}
*/

	if (nCapIndexCounter <= 0)
	{
		return;
	}

	//pIndexSmDbFile->AddIndex0(pBuffer->m_n64IndexPos, pBuffer->m_n64DataPos, oIndex.tm, TRUE);

	oSmDbFilePos.n64DbIndexBeginPos = GetBeginPos();
	oSmDbFilePos.n64DbIndexCurrPos = GetCurrPos();
	oSmDbFilePos.tmCurr = oIndex.tm;

	if (oSmDbFilePos.n64DbIndexCount == oSmDbFilePos.n64DbIndexMax)
	{
	}
	else
	{
		oSmDbFilePos.n64DbIndexCount += nCapIndexCounter;

		if (oSmDbFilePos.n64DbIndexCount >= oSmDbFilePos.n64DbIndexMax)
		{
			oSmDbFilePos.n64DbIndexCount = oSmDbFilePos.n64DbIndexMax;
		}
	}

	oSmDbFilePos.n64DbIndexCurrIndex += nCapIndexCounter;

	if (oSmDbFilePos.n64DbIndexCurrIndex >= oSmDbFilePos.n64DbIndexMax)
	{
		oSmDbFilePos.n64DbIndexCurrIndex -= oSmDbFilePos.n64DbIndexMax;
	}
}


volatile __int64 CCapDbIndexSmDbArea::Write(EPCAPDBBUFFERINDEX &oIndex)
{
	return SmWrite(&oIndex, sizeof(EPCAPDBBUFFERINDEX));
}

long CCapDbIndexSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, CEpQueryIndex0Ranges &oIndex0Ranges, CEpQueryEpCapDbBufferIndex &oQuery)
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

long CCapDbIndexSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX0EX pIndex1, PEPCAPDBBUFFERINDEX0EX pIndex2, CEpQueryEpCapDbBufferIndex &oQuery)
{
	if (oQuery.GetCount() >= oSearchConfig.dwMaxQuery)
	{
		return -1;
	}

	long nReturn = 0;

	if (pIndex1->n64CapFrameIndexPos < pIndex2->n64CapFrameIndexPos)
	{
		nReturn = Query(oSearchConfig, pIndex1->n64CapFrameIndexPos, pIndex2->n64CapFrameIndexPos, oQuery); 
	}
	else
	{
		nReturn = Query(oSearchConfig, pIndex1->n64CapFrameIndexPos, m_n64AreaEndPos, oQuery); 
		
		if (nReturn != -1)
		{
			nReturn = Query(oSearchConfig, m_n64AreaBeginPos, pIndex2->n64CapFrameIndexPos, oQuery); 
		}
	}

	return 0;
}

long CCapDbIndexSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, volatile __int64 &n64BeginPos, volatile __int64 &n64EndPos, CEpQueryEpCapDbBufferIndex &oQuery)
{
	if (oQuery.GetCount() >= oSearchConfig.dwMaxQuery)
	{
		return -1;
	}

	long dwLength = (DWORD)(n64EndPos - n64BeginPos);
	m_pSmFileClient->UnMapView();
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

		pBuffer = (BYTE*)m_pSmFileClient->GetCurrPos();
		BYTE *pTemp = pBuffer;
		BYTE *pEnd = pBuffer + m_dwOnceMapSize;

		while (pTemp < pEnd)
		{
			PEPCAPDBBUFFERINDEX pIndex = (PEPCAPDBBUFFERINDEX)pTemp;
			pTemp += sizeof(EPCAPDBBUFFERINDEX);
			nReturn = Query(oSearchConfig, pIndex, oQuery);

			dwLength = dwLength - sizeof(EPCAPDBBUFFERINDEX);

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

long CCapDbIndexSmDbArea::Query(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX pIndex, CEpQueryEpCapDbBufferIndex &oQuery)
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
// 	if (oSearchConfig.dwUseProtocol)
// 	{
// 		if (Ep_GetProtocol_ProtoType_Proto(pIndex->nProtocol) != oSearchConfig.dwProtocol)
// 		{
// 			return 0;
// 		}
// 	}

// 
/*	//搜索类型，不是原始规约报文
	if (oSearchConfig.dwUseSearchType)
	{
		if (oSearchConfig.dwSearchType != EP_SEARCH_TYPE_FRAME)
		{
// 			if ( (oSearchConfig.dwSearchType == pIndex->oDataHead.nDeviceDataType)
// 				|| (oSearchConfig.dwSearchType2 == pIndex->oDataHead.nDeviceDataType))
// 			{
// 			}
// 			else
// 			{
// 				return 0;
// 			}
		}
		else
		{
			if (Ep_GetProtocol_FrameType(pIndex->nProtocol) == 0)
			{
				return 0;
			}
		}
	}
*/
// 	if (Ep_GetProtocol_FrameType(pIndex->nProtocol) == 0)
// 	{
// 		return 0;
// 	}

	//地址
	if (oSearchConfig.dwUseDir)
	{
		if (!QueryAddr(oSearchConfig, pIndex->cap_addr))
		{
			return 0;
		}
	}

	oQuery.AddCapBufferIndex(pIndex);

	return 0;
}

BOOL CCapDbIndexSmDbArea::QueryAddr(EPCAPSEARCHCONFIG &oSearchConfig, EP_CAP_ADDR &cap_addr)
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
			if (cap_addr.addr_tradition.src.ip.s_addr != 0)
			{
				bTrue = FALSE;
				break;
			}

			//Serial 不一致
			if (pAddr->dwSrcAddr == cap_addr.addr_tradition.src.port)
			{
				bTrue = TRUE;
				break;
			}
		}
		else
		{
			//非IP
			if (cap_addr.addr_tradition.src.ip.s_addr == 0)
			{
				bTrue = FALSE;
				break;

			}
			
			if (ep_CapSearchAddr_UseSrc( pAddr->dwUse ) && ep_CapSearchAddr_UseDest( pAddr->dwUse ))
			{
				if (cap_addr.addr_tradition.src.ip.s_addr == pAddr->dwSrcAddr && cap_addr.addr_tradition.dst.ip.s_addr == pAddr->dwDestAddr)
				{
					bTrue = TRUE;
					break;
				}
			}
			else
			{
				if (ep_CapSearchAddr_UseSrc( pAddr->dwUse ))
				{
					if (cap_addr.addr_tradition.src.ip.s_addr == pAddr->dwSrcAddr)
					{
						bTrue = TRUE;
						break;
					}
				}
				else
				{
					if (ep_CapSearchAddr_UseDest( pAddr->dwUse ))
					{
						if (cap_addr.addr_tradition.dst.ip.s_addr == pAddr->dwDestAddr)
						{
							bTrue = TRUE;
							break;
						}
					}
				}
			}
		}
	}

	return bTrue;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const CString CCapDbIndexSmDbFile::g_strCapSmDbIndexFile = _T("EpCapDbIndex.esmdb");
const CString CCapDbIndexSmDbFile::g_strCapSmDbIndexID   = _T("_ep_cap_db_index_esmdb");


CCapDbIndexSmDbFile::CCapDbIndexSmDbFile()
{
	//初始化属性
	m_strName = g_strCapSmDbIndexID;
	m_strID = g_strCapSmDbIndexID;
	m_pDbIndex = NULL;

	//初始化成员变量
}

CCapDbIndexSmDbFile::~CCapDbIndexSmDbFile()
{

}

void CCapDbIndexSmDbFile::CreateCapDbIndexSmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapSmDbIndexFile;
	CreateSmDb(strFile, g_strCapSmDbIndexID, nDataSize);

	m_n64MaxIndexCount = nDataSize;
	m_n64MaxIndexCount /= sizeof(EPCAPDBBUFFERINDEX);

	m_pDbIndex = new CCapDbIndexSmDbArea();
	m_pDbIndex->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	m_pDbIndex->UnMap();
	AddNewChild(m_pDbIndex);
}

void CCapDbIndexSmDbFile::CreateCapDbIndexSmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapSmDbIndexFile;
	CreateSmDb(strFile, g_strCapSmDbIndexID, nDataSize);

	m_n64MaxIndexCount = nDataSize;
	m_n64MaxIndexCount /= sizeof(EPCAPDBBUFFERINDEX);

	m_pDbIndex = new CCapDbIndexSmDbArea();
	m_pDbIndex->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	AddNewChild(m_pDbIndex);
}


void CCapDbIndexSmDbFile::LocatePos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos)
{
	m_pDbIndex->LocateAreaPos(n64BeginPos, n64CurrPos);
}
