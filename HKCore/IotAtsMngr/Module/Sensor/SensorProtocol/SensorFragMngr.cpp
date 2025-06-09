#include "stdafx.h"
#include "SensorFragMngr.h"
#include "../../../Module/System/TickCount32.h"


///////////////////////////////////////////////////

CSensorFragMngr *CSensorFragMngr::g_pSensorFragMngr = NULL;
long CSensorFragMngr::g_nSensorFragMngrRef = 0;

CSensorFragMngr::CSensorFragMngr()
{
	m_vecSensorFragSDU.clear();
}

CSensorFragMngr::~CSensorFragMngr()
{
	for (vector<SensorFragSDU *>::iterator it = m_vecSensorFragSDU.begin(); it != m_vecSensorFragSDU.end(); it++)
	{
		if (NULL != *it)
		{
			delete *it;
			*it = NULL;
		}
	}
	m_vecSensorFragSDU.clear();
}

CSensorFragMngr *CSensorFragMngr::Create()
{
	g_pSensorFragMngr++;

	if (g_nSensorFragMngrRef == 1)
	{
		g_pSensorFragMngr = new CSensorFragMngr();

		HANDLE handle =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)CheckFragSDUThread,NULL,0,NULL);
		CloseHandle(handle);
	}

	return g_pSensorFragMngr;
}

void CSensorFragMngr::Release()
{
	g_nSensorFragMngrRef--;

	if (g_nSensorFragMngrRef == 0)
	{
		delete g_pSensorFragMngr;
		g_pSensorFragMngr = NULL;
	}
}

//���Ҷ�Ӧ��SDU
SensorFragSDU *CSensorFragMngr::FindSensorFragSDU(__int64 n64SensorID,int nSDUSeq)
{
	SensorFragSDU *pFragSDU = NULL;
	for (vector<SensorFragSDU *>::iterator it = m_vecSensorFragSDU.begin(); it != m_vecSensorFragSDU.end(); it++)
	{
		pFragSDU = *it;
		if (pFragSDU->m_n64SensorID == n64SensorID && pFragSDU->m_nSDUSeq == nSDUSeq)
		{
			return pFragSDU;
		}
	}
	return NULL;
}

//ɾ��ָ����SDU
void CSensorFragMngr::DeleteSensorFragSDU(SensorFragSDU *pFragSDU)
{
	CAutoSimpleLock oLock(m_oSensorFragSDUCriticSection);

	for (vector<SensorFragSDU *>::iterator it = m_vecSensorFragSDU.begin(); it != m_vecSensorFragSDU.end(); it++)
	{
		if (*it == pFragSDU)
		{
			m_vecSensorFragSDU.erase(it);
			break;
		}
	}
}

//���PDU��ƥ���SDU�����У�û�����ȴ���SDU�������򷵻�������SDU
SensorFragSDU *CSensorFragMngr::AddFragPDU(BYTE *pBuf,long nLen,__int64 n64SensorID,int nPkgType,int nParaCnt,int nTimeOut)
{
	//��Ƭͷ+��Ƭ�������ݴӵ�8���ֽڿ�ʼ
	BYTE *pPkgData = pBuf + SENSOR_PKG_INDEX_DATA;
	SensorFragHead oFragHead;
	sensor_pkg_get_fraghead(pPkgData,oFragHead);

	//����ƥ���SDU�Ƿ����
	SensorFragSDU *pFind = FindSensorFragSDU(n64SensorID,oFragHead.m_nSDUSeq);
	if (pFind == NULL)
	{//�����ڣ��򴴽�
		pFind = new SensorFragSDU;
		pFind->m_n64SensorID = n64SensorID;
		pFind->m_nParaCnt = nParaCnt;
		pFind->m_nPkgType = nPkgType;
		pFind->m_nTimeOut = nTimeOut;
		pFind->m_nSDUSeq = oFragHead.m_nSDUSeq;
	}

	//���Ҹ÷�Ƭ�����Ƿ��Ѿ��յ�����ֹ�ظ��յ���������
	SensorFragPDU *pFindPDU = pFind->FindSensorFragPDU(oFragHead.m_nPDUSeq);
	if (pFindPDU == NULL)
	{
		pFindPDU = new SensorFragPDU;
		pFindPDU->m_nPDUSeq = oFragHead.m_nPDUSeq;
		//PDU�����ݳ��ȣ�Ϊɶ��ȡ��Ƭͷ��SIZE���ԣ���oFragHead.m_nSize��
		pFindPDU->m_nDataLen = nLen - SENSOR_PKG_INDEX_FRAGDATA - 2;  // - 2 �Ǽ�ȥУ��λ�����𣿣�У��λ�����ֽڣ�

		//���¿����ڴ�
		pFindPDU->m_pPDUData = new BYTE[pFindPDU->m_nDataLen + 2];
		memcpy(pFindPDU->m_pPDUData,pBuf + SENSOR_PKG_INDEX_FRAGDATA,pFindPDU->m_nDataLen);
		pFindPDU->m_pPDUData[pFindPDU->m_nDataLen] = 0;
		pFindPDU->m_pPDUData[pFindPDU->m_nDataLen+1] = 0;

		pFind->m_listPDU.push_back(pFindPDU);
		pFind->m_dwTimeStart = GetTickCount();
		
		if (oFragHead.IsEndFrag())
		{
			pFind->m_nLastPDUSeq = oFragHead.m_nPDUSeq;
		}
	}

	//��Ƭ����������
	if (pFind->m_listPDU.size() == pFind->m_nLastPDUSeq);
	{
		DeleteSensorFragSDU(pFind);
		return pFind;
	}

	return NULL;
}

void CSensorFragMngr::AnalysisWholeSDU(SensorFragSDU *pFragSDU,SensorPkgInfo &oSensorPkgInfo)
{
	//PDU����:��С����
	pFragSDU->m_listPDU.sort();

	int nSDUDataLen = pFragSDU->GetSDUDataLen();
	oSensorPkgInfo.m_nFragSDUBufLen = nSDUDataLen;
	oSensorPkgInfo.m_pFragSDUBuf = new BYTE[nSDUDataLen + 2];
	int nOffset = 0;
	BOOL bFirstSDU = TRUE;

	for (list<SensorFragPDU *>::iterator it = pFragSDU->m_listPDU.begin(); it != pFragSDU->m_listPDU.end(); it++)
	{
		SensorFragPDU *pFragPDU = *it;
		if (bFirstSDU)
		{
			bFirstSDU = FALSE;

			if (IsPacketCtrlType(pFragSDU->m_nPkgType))
			{//���Ʊ��ģ�ȥ��CtrlType,RequestSetFlag
				memcpy(oSensorPkgInfo.m_pFragSDUBuf,pFragPDU->m_pPDUData+1,pFragPDU->m_nDataLen-1);
				nOffset += (pFragPDU->m_nDataLen-1);
				nSDUDataLen -= 1;
				continue;
			}
		}
		memcpy(oSensorPkgInfo.m_pFragSDUBuf+nOffset,pFragPDU->m_pPDUData,pFragPDU->m_nDataLen);
		nOffset += pFragPDU->m_nDataLen;
	}
}

BOOL CSensorFragMngr::CheckWholeFragSDU(SensorPkgInfo &oSensorPkgInfo,BYTE *pBuf,long nLen,__int64 n64SensorID
					   ,int nPkgType,int nParaCnt,int nTimeOut)
{
	SensorFragSDU *pFragSDU = g_pSensorFragMngr->AddFragPDU(pBuf,nLen,n64SensorID,nPkgType,nParaCnt,nTimeOut);

	if (pFragSDU == NULL)
	{
		return FALSE;
	}

	g_pSensorFragMngr->AnalysisWholeSDU(pFragSDU,oSensorPkgInfo);
	delete pFragSDU;

	return TRUE;
}

void CSensorFragMngr::ProcessTimeOut(DWORD dwCurTime)
{
	CAutoSimpleLock oLock(g_pSensorFragMngr->m_oSensorFragSDUCriticSection);

	for (vector<SensorFragSDU *>::iterator it = g_pSensorFragMngr->m_vecSensorFragSDU.begin(); it != g_pSensorFragMngr->m_vecSensorFragSDU.end(); it++)
	{
		SensorFragSDU *pFragSDU = *it;
		if (pFragSDU->IsTimeOut(dwCurTime))
		{
			g_pSensorFragMngr->m_vecSensorFragSDU.erase(it);
		}
	}
}

//��鳬ʱ�̣߳���ʱ����
void *CheckFragSDUThread(LPVOID lParam)
{
	while(TRUE)
	{
		if (CSensorFragMngr::g_pSensorFragMngr == NULL)
		{
			break;
		}

		CSensorFragMngr::ProcessTimeOut(GetTickCount());
		Sleep(100);
	}

	return (void *)0;
}