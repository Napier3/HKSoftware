//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapFrameSmDbFile.cpp  CCapFrameSmDbFile


#include "stdafx.h"
#include "CapFrameSmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapFrameSmDbArea::CCapFrameSmDbArea()
{
	
}

CCapFrameSmDbArea::~CCapFrameSmDbArea()
{
	
}


void CCapFrameSmDbArea::Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos)
{
	POS pos = posBegin;

	while (TRUE)
	{
		CCapCycleMemBuffer *pBuffer = (CCapCycleMemBuffer*)pBufferMngr->GetAt(pos);

		if (pBuffer->Ebs_BeWrited())
		{
			continue;
		}

		pBuffer->m_n64CapBufferPos = SmWrite(pBuffer->GetBuffer(), pBuffer->GetDataLength());

		if (oSmDbFilePos.n64MaxCapID < pBuffer->m_n64CapID)
		{
			oSmDbFilePos.n64MaxCapID = pBuffer->m_n64CapID;
		}

		pBufferMngr->GetNext(pos);

		if (pos == posEnd || pos == NULL)
		{
			break;
		}
	}

	oSmDbFilePos.n64CapFrameBeginPos = m_n64AreaBeginPos;
	oSmDbFilePos.n64CapFrameCurrPos  = GetCurrPos();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
const CString CCapFrameSmDbFile::g_strCapFrameSmDbFile = _T("EpCapFrame.esmdb");
const CString CCapFrameSmDbFile::g_strCapFrameSmDbID   = _T("_ep_cap_frame_esmdb");

CCapFrameSmDbFile::CCapFrameSmDbFile()
{
	//初始化属性
	m_pFrameSmDbArea = NULL;
	m_strName = g_strCapFrameSmDbID;
	m_strID = g_strCapFrameSmDbID;

	//初始化成员变量
}

CCapFrameSmDbFile::~CCapFrameSmDbFile()
{
}

void CCapFrameSmDbFile::CreateCapFrameSmDbServer(__int64 nDataSize, __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrameSmDbFile;
	CreateCapSmDbFile(strFile, g_strCapFrameSmDbID, nDataSize);

	m_pFrameSmDbArea = new CCapFrameSmDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	AddNewChild(m_pFrameSmDbArea);
}



void CCapFrameSmDbFile::LocatePos(__int64 n64BeginPos, __int64 n64CurrPos)
{
	m_pFrameSmDbArea->LocatePos(n64BeginPos, n64CurrPos);
}

void CCapFrameSmDbFile::CreateCapFrameSmDbClient(__int64 nDataSize, __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrameSmDbFile;
	CreateCapSmDbFile(strFile, g_strCapFrameSmDbID, nDataSize);

	m_pFrameSmDbArea = new CCapFrameSmDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	AddNewChild(m_pFrameSmDbArea);
}

