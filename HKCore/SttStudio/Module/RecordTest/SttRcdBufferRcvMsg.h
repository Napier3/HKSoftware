#ifndef _CSttRcdBufferRcvMsg_h__
#define _CSttRcdBufferRcvMsg_h__

class CSttRcdBufferRcvMsg
{
public:
	virtual void OnRcdBufRcv(BYTE *pBuffer, long nLen) = 0;
	virtual long OnRcdRcvClosed() = 0;
};

#endif // _CSttRcdBufferRcvMsg_h__
