//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapFrameDbFile.cpp  CCapFrameDbFile


#include "stdafx.h"
#include "CapFrameDbFile.h"
#include "../../../System/TickCount32.h"


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapFrameDbArea::CCapFrameDbArea()
{
	//m_nCurrWriteIndex = 0;
}

CCapFrameDbArea::~CCapFrameDbArea()
{

}

void CCapFrameDbArea::ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
{
	return ReadBuffer(pBuffer, pDestBuffer);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define g_strCapFrameDbFile _T("CapFrame.ssmdb")
#define g_strCapFrameDbID   _T("__cap_frame_dv_ssmdb")

CCapFrameDbFile::CCapFrameDbFile()
{
	//初始化属性
	m_strName = g_strCapFrameDbID;
	m_strID = g_strCapFrameDbID;

	//初始化成员变量
	m_n64BeginPos = 0;
}

CCapFrameDbFile::~CCapFrameDbFile()
{
	m_oIndexFileSever.DeleteAll();
}

//2020-06-12  创建访问客户端CCapFrameDbArea
CCapFrameDbArea* CCapFrameDbFile::CreateCapFrameArea()
{
	CCapFrameDbArea *pNew = new CCapFrameDbArea();
	CreateCapFrameArea(*pNew);

	return pNew;
}

void CCapFrameDbFile::CreateCapFrameArea(CCapFrameDbArea &oCapArea)
{
	CSmDbFileCfg *pSmDbFileCfg = g_pCapSmDbConfig->FindFileCfg(g_strCapFrameDbFile);
	if (pSmDbFileCfg == NULL)
		return;

	__int64 nDataSize = pSmDbFileCfg->m_nSize;
	nDataSize *= 1024*1024;

	__int64 nDataView = pSmDbFileCfg->m_nView * 1024 * 1024;

	oCapArea.CreateArea(g_strCapFrameDbID, 0, nDataSize, nDataView);
}

long CCapFrameDbFile::Write(CXSmMemBufferMngr *pBufferMngr)
{
	if (m_pSmDbArea == NULL)
		return 0;

	if (m_pSmDbArea->GetWriteCount(pBufferMngr) == 0)
	{//没有报文，不写文件
		return 0;
	}

	if(m_oIndexTick.GetTickCountLong(FALSE) > 1000) //写索引间隔（写报文的时间间隔为1000ms）
	{
		m_oIndexTick.Enter();
		m_oIndexFileSever.WriteSttIndex(m_n64BeginPos);
	}

	LocatePos(m_n64BeginPos);
	long nCount = m_pSmDbArea->Write(pBufferMngr);
	m_n64BeginPos = m_pSmDbArea->GetCurrPos();
	m_pSmDbArea->UnMap();

	return nCount;
}

void CCapFrameDbFile::Write(BYTE *pBuffer, long nLen)
{
	LocatePos(m_n64BeginPos);	
	if (m_pSmDbArea == NULL)
		return;
	m_pSmDbArea->SmWrite(pBuffer, nLen);
	m_n64BeginPos = m_pSmDbArea->GetCurrPos();
	m_pSmDbArea->UnMap();
}

void CCapFrameDbFile::CreateCapFrameDbServer()
{
	CSmDbFileCfg *pSmDbFileCfg = g_pCapSmDbConfig->FindFileCfg(g_strCapFrameDbFile);
	if (pSmDbFileCfg==NULL)
		return;

	__int64 nDataSize = pSmDbFileCfg->m_nSize;
	nDataSize *= 1024*1024;

	__int64 nDataView = pSmDbFileCfg->m_nView * 1024 * 1024;

	CString strPath;
	strPath = _P_GetBinPath();
	CreateCapFrameDbServer(nDataSize, nDataView, strPath);
}

void CCapFrameDbFile::CreateCapFrameDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrameDbFile;
	CreateSmDb(strFile, g_strCapFrameDbID, nDataSize);

	m_pSmDbArea = new CCapFrameDbArea();
	m_pSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	m_pSmDbArea->UnMap();
	AddNewChild(m_pSmDbArea);

	m_oIndexFileSever.CreateServer();

	m_oIndexTick.Enter();
}
