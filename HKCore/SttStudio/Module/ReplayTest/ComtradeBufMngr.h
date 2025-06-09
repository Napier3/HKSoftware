#ifndef _CComtradeBufMngr_H_
#define _CComtradeBufMngr_H_

#include "ComtradeDataBuffer.h"

#ifndef _Stt_Cmtrd_Save_File_
#define COMTRADE_LOOPBUF_SIZE	2048000		//Loop�����С2M
#define COMTRADE_ABBUF_SIZE		10240000	//AB�����С��10M
#else
#define COMTRADE_LOOPBUF_SIZE	2048000		//Loop�����С2M
#define COMTRADE_ABBUF_SIZE		10240000	//AB�����С��10M
#endif


class CComtradeBufMngr
{
private:
	CComtradeBufMngr();
	virtual ~CComtradeBufMngr();

public:
	static CComtradeBufMngr *g_pComtradeBufMngr;
	static void Create(int nLoopBufLen,int nABBufLen);
	static void Release();

private:
	CComtradeDataBuffer m_oBufLoop;
	CComtradeDataBuffer m_oBufA;
	CComtradeDataBuffer m_oBufB;

public:
	void AllocBuf(int nLoopBufLen,int nABBufLen);
	void ResetBuf();
	CComtradeDataBuffer* GetBufByIndex(int nIndex);
	CComtradeDataBuffer* GetABBufCanWrite();//��ȡA\B�ջ���:
	int GetABBufIndexCanWrite();//��ȡA\B�ջ���:
	int GetDataLenByIndex(int nIndex);

	// bExchanged:�����л���ΪTRUE,����ʵ�ʶ��ĳ��ȣ�����һ��ȡ2M
	int ReadABDataByIndex(int nIndex,float *pDestBuf,int nMaxLen,BOOL &bExchanged,BOOL &bEmpty);
	int ReadLoopData(float *pDestBuf,int nMaxLen);
	int WriteDataByIndex(int nIndex,float *pSrcBuf,int nSrcLen);
};

#endif