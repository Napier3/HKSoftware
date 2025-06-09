//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapFrameDbFile.cpp  CCapFrameDbFile


#include "stdafx.h"
#include "CapFrameDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapFrameDbArea::CCapFrameDbArea()
{
	m_nCurrWriteIndex = 0;
}

CCapFrameDbArea::~CCapFrameDbArea()
{
	
}


void CCapFrameDbArea::Write(CFrameMemBufferMngr *pBufferMngr)
{
	long nMaxCount = pBufferMngr->GetMaxCount();
	long nCurrCount = pBufferMngr->GetCurrCount();
	long nCurrIndex = pBufferMngr->GetCurrIndex();

	if (nCurrCount == nMaxCount)
	{
		if (m_nCurrWriteIndex < nCurrIndex)
		{
			Write(pBufferMngr, m_nCurrWriteIndex, nCurrIndex-1);
		}
		else
		{
			Write(pBufferMngr, m_nCurrWriteIndex, nCurrCount-1);
			Write(pBufferMngr, 0, nCurrIndex-1);
		}
	}
	else
	{
		Write(pBufferMngr, m_nCurrWriteIndex, nCurrIndex-1);
	}

	m_nCurrWriteIndex = nCurrIndex;
}

void CCapFrameDbArea::Write(CFrameMemBufferMngr *pBufferMngr,long nBeginIndex, long nEndIndex)
{
	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CFrameMemBuffer *pCapBuffer = (CFrameMemBuffer*)pBufferMngr->GetFrameBuffer(nIndex);
		BYTE *pBuffer = pCapBuffer->GetBuffer();

		if (pBuffer != NULL)
		{
			pCapBuffer->m_n64FrmPos = SmWrite(pCapBuffer->GetBuffer(), pCapBuffer->GetBufferLength());//GetDataLength());
		}

		pCapBuffer->FreeBuffer(TRUE);
	}
}

void CCapFrameDbArea::ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
{
	long nLen = pBuffer->GetBufferLength();//GetDataLength();
	BYTE *pFrmBuffer = (BYTE*)Read(pBuffer->m_n64FrmPos, nLen);

	if (pFrmBuffer != NULL)
	{
		pDestBuffer->SetBuffer(pFrmBuffer, nLen);
	}
}


LPVOID CCapFrameDbArea::Read(__int64 n64BeginPos, DWORD dwLength)
{
	if (m_pSmFileClient == NULL)
	{
		return NULL;
	}

	LPVOID pBuffer = m_pSmFileClient->Read(n64BeginPos, dwLength);

	if (pBuffer == NULL)
	{
		pBuffer = MapView(n64BeginPos, m_dwOnceMapSize, dwLength);
	}

	return pBuffer;
}


void CCapFrameDbArea::LocateAreaPos(volatile __int64 n64CurrPos)
{
	m_pSmFileClient->UnMapView();
	LPVOID pBuffer = MapView(n64CurrPos, m_dwOnceMapSize, 0);

	if (pBuffer == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("���ݿⴴ��û�гɹ�........"));
	}
	else
	{
		m_pSmFileClient->SetCurr64Pos(n64CurrPos);
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define g_strCapFrameDbFile _T("CapFrame.ssmdb")
#define g_strCapFrameDbID   _T("__cap_frame_dv_ssmdb")

CCapFrameDbFile::CCapFrameDbFile()
{
	//��ʼ������
	m_pFrameSmDbArea = NULL;
	m_strName = g_strCapFrameDbID;
	m_strID = g_strCapFrameDbID;

	//��ʼ����Ա����
	m_n64CapFrameBeginPos = 0;
}

CCapFrameDbFile::~CCapFrameDbFile()
{
	
}

void CCapFrameDbFile::Write(CFrameMemBufferMngr *pBufferMngr)
{
	LocatePos(m_n64CapFrameBeginPos);
	m_pFrameSmDbArea->Write(pBufferMngr);
	m_n64CapFrameBeginPos = m_pFrameSmDbArea->GetCurrPos();
	m_pFrameSmDbArea->UnMap();
}

void CCapFrameDbFile::CreateCapFrameDbServer()
{
	__int64 nDataSize = 512 * 1024 * 1024;
	__int64 nDataView = 4 * 1024 * 1024;
	CString strPath;
	strPath = _P_GetBinPath();
	CreateCapFrameDbServer(nDataSize, nDataView, strPath);
}

void CCapFrameDbFile::CreateCapFrameDbClient()
{
	__int64 nDataSize = 512 * 1024 * 1024;
	__int64 nDataView = 4 * 1024 * 1024;
	CString strPath;
	strPath = _P_GetBinPath();
	CreateCapFrameDbClient(nDataSize, nDataView, strPath);
}


void CCapFrameDbFile::CreateCapFrameDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrameDbFile;
	CreateSmDb(strFile, g_strCapFrameDbID, nDataSize);

	m_pFrameSmDbArea = new CCapFrameDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	m_pFrameSmDbArea->UnMap();
	AddNewChild(m_pFrameSmDbArea);
}

void CCapFrameDbFile::CreateCapFrameDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrameDbFile;
	CreateSmDb(strFile, g_strCapFrameDbID, nDataSize);

	m_pFrameSmDbArea = new CCapFrameDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	AddNewChild(m_pFrameSmDbArea);
}

