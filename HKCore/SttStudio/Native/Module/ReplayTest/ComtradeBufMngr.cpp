#include "stdafx.h"
#include "ComtradeBufMngr.h"

CComtradeBufMngr *CComtradeBufMngr::g_pComtradeBufMngr = NULL;

CComtradeBufMngr::CComtradeBufMngr()
{

}

CComtradeBufMngr::~CComtradeBufMngr()
{

}

void CComtradeBufMngr::Create(int nLoopBufLen,int nABBufLen)
{
	if (g_pComtradeBufMngr == NULL)
	{
		g_pComtradeBufMngr = new CComtradeBufMngr;
		g_pComtradeBufMngr->AllocBuf(nLoopBufLen/sizeof(float),nABBufLen/sizeof(float));
	}
}

void CComtradeBufMngr::Release()
{
	if (g_pComtradeBufMngr != NULL)
	{
		delete g_pComtradeBufMngr;
		g_pComtradeBufMngr = NULL;
	}
}

void CComtradeBufMngr::AllocBuf(int nLoopBufLen,int nABBufLen)
{
	m_oBufLoop.Init(nLoopBufLen);
	m_oBufA.Init(nABBufLen);
	m_oBufB.Init(nABBufLen);
}

void CComtradeBufMngr::ResetBuf()
{
	m_oBufLoop.SetRWState(COMTRADE_DATABUF_MODE_WRITE);
	m_oBufA.SetRWState(COMTRADE_DATABUF_MODE_WRITE);
	m_oBufB.SetRWState(COMTRADE_DATABUF_MODE_WRITE);
}

CComtradeDataBuffer* CComtradeBufMngr::GetBufByIndex(int nIndex)
{
	if (nIndex == 0)
	{
		return &m_oBufLoop;
	}

	if ((nIndex % 2) == 1)
	{
		return &m_oBufA;
	}
	else
	{
		return &m_oBufB;
	}
}

int CComtradeBufMngr::GetDataLenByIndex(int nIndex)
{
	CComtradeDataBuffer* pBuf = GetBufByIndex(nIndex);
	return pBuf->GetDataLen();
}

//��ȡA\B�ջ���:
CComtradeDataBuffer* CComtradeBufMngr::GetABBufCanWrite()
{
	if(m_oBufA.CanWrite())
	{
		return &m_oBufA;
	}
	if (m_oBufB.CanWrite())
	{
		return &m_oBufB;
	}

	return NULL;
}

int CComtradeBufMngr::GetABBufIndexCanWrite()
{
	if(m_oBufA.CanWrite())
	{
		return 1;
	}
	if (m_oBufB.CanWrite())
	{
		return 2;
	}

	return -1;
}

int CComtradeBufMngr::ReadLoopData(float *pDestBuf,int nMaxLen)
{
	if (!m_oBufLoop.CanRead())
	{
		return 0;
	}

	return m_oBufLoop.ReadData(pDestBuf,nMaxLen);
}

// bExchanged:�����л���ΪTRUE,����ʵ�ʶ��ĳ��ȣ�����һ��ȡ2M
int CComtradeBufMngr::ReadABDataByIndex(int nIndex,float *pDestBuf,int nMaxLen,BOOL &bExchanged,BOOL &bEmpty)
{
	bExchanged = FALSE;
	bEmpty = FALSE;

	CComtradeDataBuffer *pABBuf = GetBufByIndex(nIndex);
	if (!pABBuf->CanRead())
	{
		bEmpty = TRUE;
		return 0;
	}

	int nLeftLen = pABBuf->GetDataLen();
	if (nLeftLen >= nMaxLen)
	{
		pABBuf->ReadData(pDestBuf,nMaxLen);

		if (nLeftLen == nMaxLen)
		{
			bExchanged = TRUE;
		}

		return nMaxLen;
	}

	//�������ݲ��������л������

	//�ȶ��յ�ǰ����
	pABBuf->ReadData(pDestBuf,nLeftLen);

	//�л���һ������,������
	int nReadLen = ReadABDataByIndex(nIndex+1,pDestBuf+nLeftLen,nMaxLen-nLeftLen,bExchanged,bEmpty);

	bExchanged = TRUE;
	return (nReadLen + nLeftLen);
}

//д֮ǰ���ж��Ƿ��д�����д�������ÿɶ����
int CComtradeBufMngr::WriteDataByIndex(int nIndex,float *pSrcBuf,int nSrcLen)
{
	CComtradeDataBuffer *pBuf = GetBufByIndex(nIndex);
	if (!pBuf->CanWrite())
	{
		return 0;
	}

	ASSERT(pBuf->GetRemainSpace() >= nSrcLen);
	pBuf->WriteData(pSrcBuf,nSrcLen);

	return nSrcLen;
}