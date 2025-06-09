#ifndef _CComtradeBufMngr_H_
#define _CComtradeBufMngr_H_

#include "ComtradeDataBuffer.h"

#ifndef _Stt_Cmtrd_Save_File_
#define COMTRADE_LOOPBUF_SIZE	2048000		//Loop缓存大小2M
#define COMTRADE_ABBUF_SIZE		10240000	//AB缓存大小各10M
#else
#define COMTRADE_LOOPBUF_SIZE	2048000		//Loop缓存大小2M
#define COMTRADE_ABBUF_SIZE		10240000	//AB缓存大小各10M
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
	CComtradeDataBuffer* GetABBufCanWrite();//获取A\B空缓存:
	int GetABBufIndexCanWrite();//获取A\B空缓存:
	int GetDataLenByIndex(int nIndex);

	// bExchanged:缓存切换置为TRUE,返回实际读的长度，比如一次取2M
	int ReadABDataByIndex(int nIndex,float *pDestBuf,int nMaxLen,BOOL &bExchanged,BOOL &bEmpty);
	int ReadLoopData(float *pDestBuf,int nMaxLen);
	int WriteDataByIndex(int nIndex,float *pSrcBuf,int nSrcLen);
};

#endif