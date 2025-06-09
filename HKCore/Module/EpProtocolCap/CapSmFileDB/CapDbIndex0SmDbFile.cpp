//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDbIndex0SmDbFile.cpp  CCapDbIndex0SmDbFile


#include "stdafx.h"
#include "CapDbIndex0SmDbFile.h"


//////////////////////////////////////////////////////////////////////////
//EPTIME64
//YEAR=D63-D52  MONTH=D51-D48 DAY=D47-D43  HOUR=D42-D38  MINUTE=D37-D32  SECOND-MS-US=D31-D0
//一个小时
// #define INDEX0_TIME_GAP  16777216
//static volatile __int64 INDEX0_TIME_GAP = 0x4000000000;

//1分钟
// static volatile __int64 INDEX0_TIME_GAP = 0x100000000;
//20分钟
static volatile __int64 INDEX0_TIME_GAP = 0x1400000000;
//static volatile __int64 INDEX0_TIME_GAP = 0x300000000;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapDbIndex0SmDbArea::CCapDbIndex0SmDbArea()
{
	m_nPosIndex0Mngr = 0;
	ZeroMemory(&m_oCapIndexHead, sizeof(EPCAPDBINDEXHEAD));
	m_bIndex0Changed = FALSE;
	m_bServer = TRUE;
	m_bIsNewCreate = FALSE;

	m_oIndex0Mngr.nCurrIndex = 0;
	m_oIndex0Mngr.nIndexCount = 0;
	m_oIndex0Mngr.nIndexMaxCount = 0;
	m_oIndex0Mngr.pIndex0s = NULL;
	m_pLastIndex0 = NULL;
}

CCapDbIndex0SmDbArea::~CCapDbIndex0SmDbArea()
{
	if (m_oIndex0Mngr.pIndex0s != NULL)
	{
		free(m_oIndex0Mngr.pIndex0s);
		m_oIndex0Mngr.pIndex0s = NULL;
	}
}

void CCapDbIndex0SmDbArea::AddIndex0(volatile __int64 &n64Pos, volatile __int64 &n64DataPos, EPTIME64 &tm, BOOL bWriteTail)
{
	if (m_oIndex0Mngr.nIndexCount == 0)
	{
		//第一个
		AddIndex0(n64Pos, n64DataPos, tm, 0, TRUE);
		AddIndex0(n64Pos, n64DataPos, tm, 1, TRUE);
		return;
	}

	long nEndIndex = m_oIndex0Mngr.nCurrIndex;
	long nEndIndexTail = m_oIndex0Mngr.nCurrIndex;

	//最新的数据索引
	nEndIndex -= 2;

	if (nEndIndex < 0)
	{
		nEndIndex = m_oIndex0Mngr.nIndexCount + nEndIndex;
	}

	//最后一个索引，最新的时间
	nEndIndexTail--;
	if (nEndIndexTail < 0)
	{
		nEndIndexTail = m_oIndex0Mngr.nIndexCount + nEndIndexTail;
	}

	PEPCAPDBBUFFERINDEX0EX pIndex0 = GetIndex0(nEndIndex);

	volatile __int64 n64TmGap = tm.n64Time - pIndex0->tm.n64Time;

	//16777216 = 8byte第四个字节=1
	if (n64TmGap >= INDEX0_TIME_GAP)//16777216)
	{
		AddIndex0(n64Pos, n64DataPos, tm, nEndIndexTail, FALSE);
		AddIndex0(n64Pos, n64DataPos, tm, m_oIndex0Mngr.nCurrIndex, TRUE);
	}
	else
	{
		if (bWriteTail)
		{
			//更新最后一个数据的时间
			AddIndex0(n64Pos, n64DataPos, tm, nEndIndexTail, FALSE);
		}
	}
}

void CCapDbIndex0SmDbArea::AddIndex0(volatile __int64 &n64Pos, volatile __int64 &n64DataPos, EPTIME64 &tm, long nIndex, BOOL bAddIndex)
{
	ASSERT (m_oIndex0Mngr.pIndex0s != NULL);

	PEPCAPDBBUFFERINDEX0EX pIndex0 = m_oIndex0Mngr.pIndex0s + nIndex;
	pIndex0->tm = tm;
	pIndex0->n64CapFrameIndexPos = n64Pos;
	pIndex0->n64DataPos = n64DataPos;

	if (!bAddIndex)
	{
		return;
	}

	m_oIndex0Mngr.nCurrIndex++;

	if (m_oIndex0Mngr.nCurrIndex >= m_oIndex0Mngr.nIndexMaxCount)
	{
		m_oIndex0Mngr.nCurrIndex = 0;
	}

	if (m_oIndex0Mngr.nIndexCount < m_oIndex0Mngr.nIndexMaxCount)
	{
		m_oIndex0Mngr.nIndexCount++;
	}
}
// 
// void CCapDbIndex0SmDbArea::WriteIndex0(volatile __int64 &n64Pos, EPTIME64 &tm, long nIndex, BOOL bAddIndex)
// {
// 	PEPCAPDBBUFFERINDEX0 pIndex0 = ReadIndex0(nIndex);
// 	pIndex0->tm = tm;
// 	pIndex0->n64CapDataIndexPos = n64Pos;
// 
// 	if (!bAddIndex)
// 	{
// 		return;
// 	}
// 
// 	m_oIndex0Mngr.nCurrIndex++;
// 
// 	if (m_oIndex0Mngr.nCurrIndex >= m_oIndex0Mngr.nIndexMaxCount)
// 	{
// 		m_oIndex0Mngr.nCurrIndex = 0;
// 	}
// 
// 	if (m_oIndex0Mngr.nIndexCount < m_oIndex0Mngr.nIndexMaxCount)
// 	{
// 		m_oIndex0Mngr.nIndexCount++;
// 	}
// }

void CCapDbIndex0SmDbArea::SetSmDbFilePos(EPSMDBFILEPOS &oSmDbFilePos)
{
	m_oCapIndexHead.oDbFilePos = oSmDbFilePos;
// 	m_pSmFile->FlushView();
}

BYTE* CCapDbIndex0SmDbArea::MapAreaView()
{
	ASSERT (m_pSmFile != NULL);

	if (m_pSmFile == NULL)
	{
		return NULL;
	}

	m_pSmFile->UnMapView();
	DWORD dwMapLength = (DWORD)m_n64Length;
	BYTE *pBuffer = (BYTE*)m_pSmFile->MapView(m_n64AreaBeginPos, dwMapLength);

	ASSERT(pBuffer != NULL);

	if (pBuffer != NULL)
	{
		m_pSmFile->LocatePos(0);
	}

	return pBuffer;
}

void CCapDbIndex0SmDbArea::OpenIndexoMngr()
{
	BYTE *pBuffer = MapAreaView();
	if (pBuffer == NULL)
	{
		return;
	}
	
	m_nPosIndex0Mngr = sizeof(EPCAPDBINDEXHEAD);
	memcpy(&m_oCapIndexHead, pBuffer, m_nPosIndex0Mngr);
	m_bIsNewCreate = TRUE;

	if (memcmp(g_strCapDbIndexHead, m_oCapIndexHead.strHead, CAPDB_HEAD_STRING_SIZE) == 0)
	{
		m_bIsNewCreate = FALSE;
	}
	else
	{
		if (!m_bServer)
		{//不是服务器端，则表示创建失败，退出
			return;
		}
	}

	if (m_bIsNewCreate)
	{
		strcpy((char*)m_oCapIndexHead.strHead, g_strCapDbIndexHead);
		m_oCapIndexHead.dwVersion = g_dwCurrCapDbVersion;

		long nCount = (DWORD)m_n64Length;
		nCount = nCount - sizeof(EPCAPDBINDEXHEAD) - 20; //20=EPCAPDBBUFFERINDEX0MNGR的额外数据长度
		nCount = nCount / sizeof(EPCAPDBBUFFERINDEX0EX) - 10;
		m_oIndex0Mngr.nIndexMaxCount = nCount;
		InitIndex0Mngr();
		WriteIndexoMngr();
	}
	else
	{
		if (m_oCapIndexHead.dwVersion != g_dwCurrCapDbVersion)
		{
			g_dwCapDbVersionError = 0xFFFFFFFF;
			return;
		}

		ReadIndex0Mngr();
		InitIndex0Mngr();
		g_nCaptureID = m_oCapIndexHead.oDbFilePos.n64MaxCapID;
	}

	m_pSmFile->UnMapView();
}

BYTE* CCapDbIndex0SmDbArea::MapView(volatile __int64 n64BeginPos, DWORD dwLen, DWORD dwMinLen)
{
	return MapAreaView();
}

//从文件读取Index0
void CCapDbIndex0SmDbArea::ReadIndex0Mngr()
{
	m_pSmFile->LocatePos(m_nPosIndex0Mngr);
	*m_pSmFile >> m_oIndex0Mngr.nCurrIndex;  //当前的有效索引
	*m_pSmFile >> m_oIndex0Mngr.nIndexCount;  //有效索引的个数
	*m_pSmFile >> m_oIndex0Mngr.nIndexMaxCount;  //最大索引数量
	
// 	BYTE* pBuffer = (BYTE*)m_pSmFile->GetCurrPos();
// 	long nSize = GetIndex0Size();
// 	ASSERT (m_oIndex0Mngr.pIndex0s != NULL);
// 	memcpy(m_oIndex0Mngr.pIndex0s, pBuffer, nSize);
}

void CCapDbIndex0SmDbArea::InitIndex0Mngr()
{
	long nSize = GetIndex0Size();

	if (m_oIndex0Mngr.pIndex0s == NULL)
	{
		m_oIndex0Mngr.pIndex0s = (PEPCAPDBBUFFERINDEX0EX)malloc(nSize);
	}
	
	long nPos = GetIndex0BeginPos();
	m_pSmFile->LocatePos(nPos);

	BYTE* pBuffer = (BYTE*)m_pSmFile->GetCurrPos();
	memcpy(m_oIndex0Mngr.pIndex0s, pBuffer, nSize);
}

long CCapDbIndex0SmDbArea::GetIndex0Size()
{
	long nSize = m_oIndex0Mngr.nIndexMaxCount*sizeof(EPCAPDBBUFFERINDEX0EX);
	return nSize;
}

long CCapDbIndex0SmDbArea::GetIndex0BeginPos()
{
	long nPos = m_nPosIndex0Mngr + sizeof(m_oIndex0Mngr.nCurrIndex)
		+  sizeof(m_oIndex0Mngr.nIndexCount) + sizeof(m_oIndex0Mngr.nIndexMaxCount);
	return nPos;
}


void CCapDbIndex0SmDbArea::SaveIndexoMngr()
{
	MapAreaView();
	WriteIndexoMngrEx();
	m_pSmFile->UnMapView();
}

void CCapDbIndex0SmDbArea::WriteIndexoMngr()
{
	LPVOID pBuffer = m_pSmFile->LocatePos(0);
	SmWrite(&m_oCapIndexHead, m_nPosIndex0Mngr);

	*m_pSmFile << m_oIndex0Mngr.nCurrIndex;  //当前的有效索引
	*m_pSmFile << m_oIndex0Mngr.nIndexCount;  //有效索引的个数
	*m_pSmFile << m_oIndex0Mngr.nIndexMaxCount;  //最大索引数量
}

void CCapDbIndex0SmDbArea::WriteIndexoMngrEx()
{
	LPVOID pBuffer = m_pSmFile->LocatePos(0);
	SmWrite(&m_oCapIndexHead, m_nPosIndex0Mngr);

	m_pSmFile->LocatePos(m_nPosIndex0Mngr);

	*m_pSmFile << m_oIndex0Mngr.nCurrIndex;  //当前的有效索引
	*m_pSmFile << m_oIndex0Mngr.nIndexCount;  //有效索引的个数
	*m_pSmFile << m_oIndex0Mngr.nIndexMaxCount;  //最大索引数量

	long nSize = m_oIndex0Mngr.nIndexCount*sizeof(EPCAPDBBUFFERINDEX0EX);
	m_pSmFile->WriteBuffer(m_oIndex0Mngr.pIndex0s, nSize);
}

//******************************************************************************************************
//客户端，查找
void CCapDbIndex0SmDbArea::Query(EPTIME64 &tmBegin, EPTIME64 tmEnd, CEpQueryIndex0Ranges &oIndex0Ranges)
{
	OpenIndexoMngr();

	if (IsCapDbVersionError())
	{
		return;
	}

	GetIndex0ValidRage(oIndex0Ranges);
	QueryIndex0ValidRage(tmBegin, tmEnd, oIndex0Ranges);
}

void CCapDbIndex0SmDbArea::GetIndex0ValidRage(CEpQueryIndex0Ranges &oIndex0Ranges)
{
	m_nPosChangeCount = 0;
	long nCurrIndex = m_oIndex0Mngr.nCurrIndex;
	long nIndexCount = m_oIndex0Mngr.nIndexCount;
	long nIndexMax = m_oIndex0Mngr.nIndexMaxCount;

	if (nIndexCount == nIndexMax)
	{
		if (nCurrIndex == 0)
		{
			m_pLastIndex0 = GetIndex0(nIndexCount-1);
		}
		else
		{
			m_pLastIndex0 = GetIndex0(nCurrIndex-1);
		}

		GetIndex0ValidRage(oIndex0Ranges.m_oIndex0Ranges.range1, 0, nCurrIndex-1);
		GetIndex0ValidRage(oIndex0Ranges.m_oIndex0Ranges.range0, nCurrIndex+1, nIndexMax-1);
	}
	else
	{
		m_pLastIndex0 = GetIndex0(nCurrIndex-1);
		GetIndex0ValidRage(oIndex0Ranges.m_oIndex0Ranges.range0, 0, nCurrIndex-1);
	}
}

void CCapDbIndex0SmDbArea::GetIndex0ValidRage(PEPQUERYRANGE pRange, long nBeginIndex, long nEndIndex)
{
	long nIndex = 0;
	PEPCAPDBBUFFERINDEX0EX pCurr = NULL;
	pRange->nBeginIndex = nBeginIndex;

	for (nIndex=nEndIndex; nIndex>=nBeginIndex; nIndex--)
	{
		pCurr = GetIndex0(nIndex);

		if (m_nPosChangeCount == 0)
		{
			if (pCurr->n64CapFrameIndexPos > m_pLastIndex0->n64CapFrameIndexPos)
			{
				m_nPosChangeCount = 1;
			}
		}
		else
		{
			if (pCurr->n64CapFrameIndexPos < m_pLastIndex0->n64CapFrameIndexPos)
			{
				pRange->nBeginIndex = nIndex + 1;
				break;
			}
		}
	}

	pRange->nEndIndex = nEndIndex;

}

void CCapDbIndex0SmDbArea::QueryIndex0ValidRage(EPTIME64 &tmBegin, EPTIME64 tmEnd, CEpQueryIndex0Ranges &oIndex0Ranges)
{
	PEPCAPDBBUFFERINDEX0EX pIndex1 = NULL;
	PEPCAPDBBUFFERINDEX0EX pIndex2 = NULL;

	long nIndex = 0;
	long nBeginIndex1 = oIndex0Ranges.m_oIndex0Ranges.range0.nBeginIndex;
	long nEndIndex1 = oIndex0Ranges.m_oIndex0Ranges.range0.nEndIndex;
	long nBeginIndex2 = oIndex0Ranges.m_oIndex0Ranges.range1.nBeginIndex;
	long nEndIndex2 = oIndex0Ranges.m_oIndex0Ranges.range1.nEndIndex;

	for (nIndex=nBeginIndex1; nIndex<=nEndIndex1; nIndex++)
	{
		pIndex2 = GetIndex0(nIndex);

		if (pIndex1 == NULL)
		{
			pIndex1 = pIndex2;
		}
		else
		{
			if (Ep_IsTimeAreaIn(tmBegin, tmEnd, pIndex1->tm, pIndex2->tm))
			{
				oIndex0Ranges.AddIndex0Range(pIndex1, pIndex2);
			}
			else
			{
			}

			pIndex1 = pIndex2;
		}
	}

	if (nBeginIndex2 < 0)
	{
		return;
	}
	for (nIndex=nBeginIndex2; nIndex<=nEndIndex2; nIndex++)
	{
		pIndex2 = GetIndex0(nIndex);

		if (pIndex1 == NULL)
		{
			pIndex1 = pIndex2;
		}
		else
		{
			if (Ep_IsTimeAreaIn(tmBegin, tmEnd, pIndex1->tm, pIndex2->tm))
			{
				oIndex0Ranges.AddIndex0Range(pIndex1, pIndex2);
			}
			else
			{
			}

			pIndex1 = pIndex2;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const CString CCapDbIndex0SmDbFile::g_strCapSmDbIndex0File = _T("EpCapDbIndex0.esmdb");
const CString CCapDbIndex0SmDbFile::g_strCapSmDbIndex0ID   = _T("_ep_cap_db_index0_esmdb");


CCapDbIndex0SmDbFile::CCapDbIndex0SmDbFile()
{
	//初始化属性
	m_strName = g_strCapSmDbIndex0ID;
	m_strID = g_strCapSmDbIndex0ID;
	m_pDbIndexHead = NULL;

	//初始化成员变量
}

CCapDbIndex0SmDbFile::~CCapDbIndex0SmDbFile()
{

}

void CCapDbIndex0SmDbFile::CreateCapDbIndex0SmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapSmDbIndex0File;
	CreateCapSmDbFile(strFile, g_strCapSmDbIndex0ID, nDataSize);

	m_pDbIndexHead = new CCapDbIndex0SmDbArea();
	m_pDbIndexHead->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);

	//读取索引
	m_pDbIndexHead->OpenIndexoMngr();

	AddNewChild(m_pDbIndexHead);
}

void CCapDbIndex0SmDbFile::CreateCapDbIndex0SmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapSmDbIndex0File;
	CreateCapSmDbFile(strFile, g_strCapSmDbIndex0ID, nDataSize);

	m_pDbIndexHead = new CCapDbIndex0SmDbArea();
	m_pDbIndexHead->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	//读取索引
	m_pDbIndexHead->OpenIndexoMngr();
	AddNewChild(m_pDbIndexHead);
}
