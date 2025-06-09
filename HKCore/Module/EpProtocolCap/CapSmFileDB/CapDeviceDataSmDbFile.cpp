//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceDataSmDbFile.cpp  CCapDeviceDataSmDbFile


#include "stdafx.h"
#include "CapDeviceDataSmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapDeviceDataSmDbArea::CCapDeviceDataSmDbArea()
{
	
}

CCapDeviceDataSmDbArea::~CCapDeviceDataSmDbArea()
{
	
}

__int64 CCapDeviceDataSmDbArea::Write(EPDEVICEDATASMNGR &oDataMngr)
{
	long nLen = 0;
	long nIndex = 0;
	BYTE *p = m_pEpDeviceDatasBuffer;
	*((long*)p) = oDataMngr.nCount;
	nLen += 4;
	p += 4;
	long nTemp = 0;

	for (nIndex=0; nIndex<oDataMngr.nCount; nIndex++)
	{
		EPDEVICEDATAS oDatas = oDataMngr.oDatas[nIndex];
		memcpy(p, &oDatas.oDataHead, sizeof(EPDEVICEDATAHEAD));
		p += sizeof(EPDEVICEDATAHEAD);

		nTemp = oDatas.oDataHead.nDataCount * sizeof (EPY4DATA);
		memcpy(p, oDatas.pDataBuffer, nTemp);
		nLen += nTemp;
	}

	__int64 n64Pos = SmWrite(m_pEpDeviceDatasBuffer, nLen);
	return n64Pos;
}

void CCapDeviceDataSmDbArea::Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos)
{
	if (posBegin == NULL)
	{
		return;
	}

	POS pos = posBegin;
	CCapCycleMemBuffer *pBuffer = NULL;

	while (TRUE)
	{
		pBuffer = (CCapCycleMemBuffer*)pBufferMngr->GetAt(pos);

		if (pBuffer->Ebs_BeWrited())
		{
			continue;
		}

		EPDEVICEDATASMNGR &oDataMngr = pBuffer->m_DeviceDatasMngr;
		pBuffer->m_n64DeviceDataPos = Write(oDataMngr);
		pBufferMngr->GetNext(pos);

		if (pos == posEnd)
		{
			break;
		}

		if (pos == NULL)
		{
			break;
		}
	}

	oSmDbFilePos.n64DeviceDataBeginPos = m_n64AreaBeginPos;
	oSmDbFilePos.n64DeviceDataCurrPos  = GetCurrPos();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const CString CCapDeviceDataSmDbFile::g_strDeviceDataSmDbFile = _T("EpCapDeviceData.esmdb");
const CString CCapDeviceDataSmDbFile::g_strDeviceDataSmDbID   = _T("_ep_cap_device_data_esmdb");


CCapDeviceDataSmDbFile::CCapDeviceDataSmDbFile()
{
	//初始化属性
	m_strName = g_strDeviceDataSmDbID;
	m_strID = g_strDeviceDataSmDbID;
	m_pDeviceData = NULL;

	//初始化成员变量
}

CCapDeviceDataSmDbFile::~CCapDeviceDataSmDbFile()
{

}

CCapDeviceDataSmDbArea* CCapDeviceDataSmDbFile::CreateDbArea(__int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize)
{
	CCapDeviceDataSmDbArea *pArea = new CCapDeviceDataSmDbArea();
	pArea->CreateArea(m_strID, n64BeginPos, n64Length, dwOnceMapSize);
	AddNewChild(pArea);
	return pArea;
}

void CCapDeviceDataSmDbFile::CreateDeviceDataSmDbServer(__int64 nDataSize, __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strDeviceDataSmDbFile;
	CreateCapSmDbFile(strFile, g_strDeviceDataSmDbID, nDataSize);

	m_pDeviceData = CreateDbArea(0, nDataSize, (DWORD)nDataView);
}

void CCapDeviceDataSmDbFile::LocatePos(__int64 n64BeginPos, __int64 n64CurrPos)
{
	m_pDeviceData->LocatePos(n64BeginPos, n64CurrPos);
}

void CCapDeviceDataSmDbFile::CreateDeviceDataSmDbClient(__int64 nDataSize, __int64 nDataView, const CString &strPath)
{
	CString strFile;
	strFile = strPath;
	strFile += g_strDeviceDataSmDbFile;
	CreateCapSmDbFile(strFile, g_strDeviceDataSmDbID, nDataSize);

	m_pDeviceData = CreateDbArea(0, nDataSize, (DWORD)nDataView);
}

