//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapFrameDbFile.cpp  CCapFrameDbFile


#include "stdafx.h"
#include "CapDbSttIndexFrameDbFile.h"
#include "../../../System/TickCount32.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapFrameIndexDbArea::CCapFrameIndexDbArea()
{
	m_pSST_PKT_SM_INDEX = NULL;
}

CCapFrameIndexDbArea::~CCapFrameIndexDbArea()
{
	
}

void CCapFrameIndexDbArea::InitSttPktSmIndex()
{
	m_pSST_PKT_SM_INDEX = (SST_PKT_SM_INDEX*)LocateAreaPos(0);
}

void CCapFrameIndexDbArea::NewTest()
{
	memcpy(m_pSST_PKT_SM_INDEX->Version, "stt_idx_", 8);
	memset(m_pSST_PKT_SM_INDEX + 8, 0, 2048);
}

//nBeginPos��nEndPos��¼����Ҫ��ı���д�빲��������ļ�λ��
void CCapFrameIndexDbArea::QueryCapFrameDbPos(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos)
{
	CTime tmB(tmBegin);
	CTime tmE(tmEnd);

	if(m_pSST_PKT_SM_INDEX == NULL || tmB >= tmE)
	{
		nBeginPos = 0;
		nEndPos = 0;
		return;
	}

	SST_PKT_INDEX *pIndexHead = &(m_pSST_PKT_SM_INDEX->oIndex);
	__int64 nCount = m_pSST_PKT_SM_INDEX->n64IndexCount; //�ṹ�������нṹ��ָ��ĸ���
	SST_PKT_INDEX *pIndex = NULL;

	if(nCount == 0)
	{
		nBeginPos = 0;
		nEndPos = 0;
		return;
	}

	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	ZeroMemory(&tm, sizeof(SYSTEMTIME));

	for(__int64 i = 0; i < nCount; i++)
	{
		pIndex = pIndexHead + i; 

		CCapDbSttIndexSmDbFile::EP_ETHER_CAP_TIME2SYSTEMTIME(pIndex->time, tm);

		CTime tmTmp(tm);

		if(tmTmp <= tmB)
		{
			nBeginPos = pIndex->pos;
		}

		if(tmTmp <= tmE)
		{
			nEndPos = pIndex->pos;
		}

		if(tmTmp > tmE)
		{
			nEndPos = pIndex->pos;
			return;
		}
	}
}

void CCapFrameIndexDbArea::QueryCapFrameDbPos(EP_ETHER_CAP_TIME tmBegin, EP_ETHER_CAP_TIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos)
{
	SYSTEMTIME tmB, tmE;
	::GetLocalTime(&tmB);
	::GetLocalTime(&tmE);
	ZeroMemory(&tmB, sizeof(SYSTEMTIME));
	ZeroMemory(&tmE, sizeof(SYSTEMTIME));

	CCapDbSttIndexSmDbFile::EP_ETHER_CAP_TIME2SYSTEMTIME(tmBegin, tmB);
	CCapDbSttIndexSmDbFile::EP_ETHER_CAP_TIME2SYSTEMTIME(tmEnd, tmE);

	QueryCapFrameDbPos(tmB, tmE, nBeginPos, nEndPos);
}

//ȱ��tmBegin��Ĭ�ϴ�����ͷ����ʼ
void CCapFrameIndexDbArea::QueryCapFrameDbPos(EP_ETHER_CAP_TIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos)
{
	SYSTEMTIME tmE;
	::GetLocalTime(&tmE);
	ZeroMemory(&tmE, sizeof(SYSTEMTIME));

	CCapDbSttIndexSmDbFile::EP_ETHER_CAP_TIME2SYSTEMTIME(tmEnd, tmE);

	QueryCapFrameDbPos(tmE, nBeginPos, nEndPos);
}

void CCapFrameIndexDbArea::QueryCapFrameDbPos(SYSTEMTIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos)
{
	ASSERT(m_pSST_PKT_SM_INDEX != NULL);
	SST_PKT_INDEX *pIndex = &(m_pSST_PKT_SM_INDEX->oIndex);

	SYSTEMTIME tmBegin;
	::GetLocalTime(&tmBegin);
	ZeroMemory(&tmBegin, sizeof(SYSTEMTIME));

	CCapDbSttIndexSmDbFile::EP_ETHER_CAP_TIME2SYSTEMTIME(pIndex->time, tmBegin);

	QueryCapFrameDbPos(tmBegin, tmEnd, nBeginPos, nEndPos);
}

//////////////////////////////////////////////////////////////////////////
//xujinqiang20200612add�����������ļ��ڴ�
//////////////////////////////////////////////////////////////////////////
#define g_strCapFrameDbSttIndexFile _T("CapFrameIndex.ssmdb")
#define g_strCapFrameDbSttIndexID   _T("__cap_frame_index_ssmdb")

CCapDbSttIndexSmDbFile::CCapDbSttIndexSmDbFile()
{
	//��ʼ������
	m_strName = g_strCapFrameDbSttIndexFile;
	m_strID = g_strCapFrameDbSttIndexID;

	//��ʼ����Ա����
}

CCapDbSttIndexSmDbFile::~CCapDbSttIndexSmDbFile()
{

}

//2020-06-12  �������ʿͻ���CCapFrameIndexDbArea
CCapFrameIndexDbArea* CCapDbSttIndexSmDbFile::CreateCapFrameIndexDbArea()
{
	CCapFrameIndexDbArea *pNew = new CCapFrameIndexDbArea();
	CreateCapFrameIndexDbArea(*pNew);

	return pNew;
}

void CCapDbSttIndexSmDbFile::CreateCapFrameIndexDbArea(CCapFrameIndexDbArea &oCapArea)
{
	if (g_pCapSmDbConfig == NULL)
	{
		return;
	}

	CSmDbFileCfg *pSmDbFileCfg = g_pCapSmDbConfig->FindFileCfg(g_strCapFrameDbSttIndexFile);
	if (pSmDbFileCfg == NULL)
		return;
	__int64 nDataSize = pSmDbFileCfg->m_nSize * 1024 * 1024;
	__int64 nDataView = pSmDbFileCfg->m_nView * 1024 * 1024;

	oCapArea.CreateArea(g_strCapFrameDbSttIndexID, 0, nDataSize, nDataView);
	oCapArea.InitSttPktSmIndex();
}

//void CCapDbSttIndexSmDbFile::Write(CFrameMemBufferMngr *pBufferMngr)
//{
//	LocatePos(m_n64BeginPos);
//	m_pSmDbArea->Write(pBufferMngr);
//	m_n64BeginPos = m_pSmDbArea->GetCurrPos();
//	m_pSmDbArea->UnMap();
//}
//
//void CCapDbSttIndexSmDbFile::Write(BYTE *pBuffer, long nLen)
//{
//	LocatePos(m_n64BeginPos);
//	m_pSmDbArea->SmWrite(pBuffer, nLen);
//	m_n64BeginPos = m_pSmDbArea->GetCurrPos();
//	m_pSmDbArea->UnMap();
//}

void CCapDbSttIndexSmDbFile::CreateSttIndexCapFrameDbServer()
{
	CSmDbFileCfg *pSmDbFileCfg = g_pCapSmDbConfig->FindFileCfg(g_strCapFrameDbSttIndexFile);	
	if (pSmDbFileCfg == NULL)
		return;
	__int64 nDataSize = pSmDbFileCfg->m_nSize * 1024 * 1024;
	__int64 nDataView = pSmDbFileCfg->m_nView * 1024 * 1024;

	CString strPath;
	strPath = _P_GetBinPath();
	CreateSttIndexCapFrameDbServer(nDataSize, nDataView, strPath);
}

void CCapDbSttIndexSmDbFile::CreateSttIndexCapFrameDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrameDbSttIndexFile;
	CreateSmDb(strFile, g_strCapFrameDbSttIndexID, nDataSize);

	CCapFrameIndexDbArea *pNew = new CCapFrameIndexDbArea();
	m_pSmDbArea = pNew;
	m_pSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	m_pSmDbArea->UnMap();
	AddNewChild(m_pSmDbArea);

	pNew->InitSttPktSmIndex();
	m_pSST_PKT_SM_INDEX = pNew->m_pSST_PKT_SM_INDEX;
}

SST_PKT_SM_INDEX* CCapDbSttIndexSmDbFile::CreateServer()
{
	CreateSttIndexCapFrameDbServer();

	if (memcmp(m_pSST_PKT_SM_INDEX->Version, "stt_idx_", 8) != 0)
	{
		memcpy(m_pSST_PKT_SM_INDEX->Version, "stt_idx_", 8);
		memset(m_pSST_PKT_SM_INDEX+8, 0, 1024);
	}

	return m_pSST_PKT_SM_INDEX;
}

void CCapDbSttIndexSmDbFile::WriteSttIndex(__int64 nBeginPos)
{
	ASSERT(m_pSST_PKT_SM_INDEX != NULL);
	if(m_pSST_PKT_SM_INDEX == NULL )
	{
		return;
	}

	SST_PKT_INDEX *pIndexHead = &(m_pSST_PKT_SM_INDEX->oIndex);
	SST_PKT_INDEX *pIndex = pIndexHead + m_pSST_PKT_SM_INDEX->n64IndexCount;
	pIndex->pos = nBeginPos;

	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	pIndex->time.year = tm.wYear;
	pIndex->time.month = tm.wMonth;
	pIndex->time.day = tm.wDay;
	pIndex->time.hour = tm.wHour;
	pIndex->time.minute = tm.wMinute;
	pIndex->time.second = tm.wSecond;
	pIndex->time.usec = tm.wMilliseconds*1000;

	m_pSST_PKT_SM_INDEX->n64SmWritePos = nBeginPos; //�����ļ�д��λ��
	//pSttPktSmIndex->n64SmWriteLen += ; //�����ļ���ǰ�ۼ�д�볤��
	//pSttPktSmIndex->n64SmMaxLen = pBufferMngr->GetMaxCount(); //�����ļ��������
	//pSttPktSmIndex->n64SmParsePos = pBufferMngr->GetCurrParseIndex(); //�����ļ���ǰ����λ��
	m_pSST_PKT_SM_INDEX->n64IndexCount++;

	//ˢ��
	CSmDbAreaBase *pArea = GetSmDbArea();
	pArea->FlushView(pIndex, sizeof(SST_PKT_INDEX));
	pArea->FlushView(m_pSST_PKT_SM_INDEX, sizeof(SST_PKT_SM_INDEX));
}

void CCapDbSttIndexSmDbFile::EP_ETHER_CAP_TIME2SYSTEMTIME(EP_ETHER_CAP_TIME tmSource, SYSTEMTIME &tmDest)
{
	tmDest.wYear = tmSource.year;
	tmDest.wMonth = tmSource.month;
	tmDest.wDay = tmSource.day;
	tmDest.wHour = tmSource.hour;
	tmDest.wMinute = tmSource.minute;
	tmDest.wSecond = tmSource.second;
	tmDest.wMilliseconds = tmSource.usec/1000;
}

