//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapFrmDvSmDbFile.cpp  CCapFrmDvSmDbFile


#include "stdafx.h"
#include "CapFrmDvSmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapFrmDvSmDbArea::CCapFrmDvSmDbArea()
{
	m_pEpDeviceDatasBuffer[0] = 0;
}

CCapFrmDvSmDbArea::~CCapFrmDvSmDbArea()
{
	
}


void CCapFrmDvSmDbArea::Write(CCapCycleMemBufferMngr *pBufferMngr,  EPSMDBFILEPOS &oSmDbFilePos)
{
// 	CString strMsg;
// 	strMsg.Format(_T(" n64CapFrmDvCurrPos=%I64d\r\n n64DbIndexCurrPos==%I64d")
// 		, oSmDbFilePos.n64CapFrmDvCurrPos
// 		, oSmDbFilePos.n64DbIndexCurrPos);
// 	AfxMessageBox(strMsg);

	POS pos = pBufferMngr->GetHeadPosition();
	long nFrameLen = 0;
//	long nDeviceDataLen = 0;
	long nIndex = 0;

	while (pos != NULL)
	{
		CCapCycleMemBuffer *pCapBuffer = (CCapCycleMemBuffer*)pBufferMngr->GetAt(pos);

		if (pCapBuffer->Ebs_BeWrited())
		{
			pBufferMngr->GetNext(pos);
			continue;
		}

/*		nFrameLen = WriteFrame(pCapBuffer, 0);
//		nDeviceDataLen = WriteDeviceData(pCapBuffer, nFrameLen);
		pCapBuffer->m_n64FrmDvPos = SmWrite(m_pEpDeviceDatasBuffer, nFrameLen);// + nDeviceDataLen);
		pCapBuffer->m_dwFrameLen = nFrameLen;
*/
		//2013-12-9修改
		nFrameLen = pCapBuffer->GetDataLength();
		pCapBuffer->m_n64FrmDvPos = SmWrite(pCapBuffer->GetBuffer(), nFrameLen);
		pCapBuffer->m_dwFrameLen = nFrameLen;
		//pCapBuffer->SetState(EBS_HASWRITE);

		if (oSmDbFilePos.n64MaxCapID < pCapBuffer->m_n64CapID)
		{
			__int64 n64MaxCapID = pCapBuffer->m_n64CapID;
		}

		pBufferMngr->GetNext(pos);
		nIndex++;
	}

	oSmDbFilePos.n64CapFrmDvBeginPos = m_n64AreaBeginPos;
	oSmDbFilePos.n64CapFrmDvCurrPos  = GetCurrPos();

	if (oSmDbFilePos.dwDbCapFrmDvState == 0)
	{
		if (IsMapCycle())
		{
			oSmDbFilePos.dwDbCapFrmDvState = 1;
		}
	}
}

long CCapFrmDvSmDbArea::WriteFrame(CCapCycleMemBuffer *pBuffer, long nWritePos/*, EPSMDBFILEPOS &oSmDbFilePos*/)
{
	BYTE *p = m_pEpDeviceDatasBuffer + nWritePos;
	long nLen = pBuffer->GetDataLength();
	memcpy(p, pBuffer->GetBuffer(), nLen);

	return nLen;
}

// 
// long CCapFrmDvSmDbArea::WriteDeviceData(CCapCycleMemBuffer *pBuffer, long nWritePos/*, EPSMDBFILEPOS &oSmDbFilePos*/)
// {
// 	long nLen = 0;
// 	long nIndex = 0;
// 	long nCount = 0;
// 	CEpDeviceDatas *pDatas = pBuffer->m_pDeviceDatas;
// 	BYTE *p = m_pEpDeviceDatasBuffer + nWritePos;
// 
// 	nCount = pDatas->GetCount();
// 
// 	long nSize = sizeof(nCount);
// 	memcpy(p, &nCount, nSize);
// 	nLen += nSize;
// 	p += nSize;
// 	
// 	nSize = sizeof(pDatas->m_nDeviceDataType);
// 	memcpy(p, &(pDatas->m_nDeviceDataType), nSize);
// 	nLen += nSize;
// 	p += nSize;
// 
// 	if (nCount > 0)
// 	{
// 		POS pos = pDatas->GetHeadPosition();
// 		CEpY4Data *pData = NULL;
// 		long nTemp = 0;
// 
// 		while (pos != NULL)
// 		{
// 			pData = pDatas->GetNext(pos);
// 			nSize = pData->WriteToBuffer(p);
// 			p += nSize;
// 			nTemp += nSize;
// 		}
// 
// 		nLen += nTemp;
// 	}
// 
// 	return nLen;
// }


void CCapFrmDvSmDbArea::ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer)
{
	long nLen = pIndex->nFrameLen;// + pIndex->nDeviceDataLen;
	BYTE *pFrmBuffer = (BYTE*)Read(pIndex->n64CapFramePos, nLen);

	if (pFrmBuffer != NULL)
	{
		pBuffer->Init(pFrmBuffer, nLen);
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
const CString CCapFrmDvSmDbFile::g_strCapFrmDvSmDbFile = _T("EpCapFrmDv.esmdb");
const CString CCapFrmDvSmDbFile::g_strCapFrmDvSmDbID   = _T("_ep_cap_frame_dv_esmdb");

CCapFrmDvSmDbFile::CCapFrmDvSmDbFile()
{
	//初始化属性
	m_pFrameSmDbArea = NULL;
	m_strName = g_strCapFrmDvSmDbID;
	m_strID = g_strCapFrmDvSmDbID;

	//初始化成员变量
}

CCapFrmDvSmDbFile::~CCapFrmDvSmDbFile()
{
}

void CCapFrmDvSmDbFile::CreateCapFrmDvSmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrmDvSmDbFile;
	CreateCapSmDbFile(strFile, g_strCapFrmDvSmDbID, nDataSize);

	m_pFrameSmDbArea = new CCapFrmDvSmDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	m_pFrameSmDbArea->UnMap();
	AddNewChild(m_pFrameSmDbArea);
}

void CCapFrmDvSmDbFile::LocatePos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos)
{
	m_pFrameSmDbArea->LocateAreaPos(n64BeginPos, n64CurrPos);
}

void CCapFrmDvSmDbFile::CreateCapFrmDvSmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strCapFrmDvSmDbFile;
	CreateCapSmDbFile(strFile, g_strCapFrmDvSmDbID, nDataSize);

	m_pFrameSmDbArea = new CCapFrmDvSmDbArea();
	m_pFrameSmDbArea->CreateArea(m_strID, 0, nDataSize, (DWORD)nDataView);
	AddNewChild(m_pFrameSmDbArea);
}

