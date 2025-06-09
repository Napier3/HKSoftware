#ifndef _ComtradeDataBuffer_H_
#define _ComtradeDataBuffer_H_

#include "../../../Module/OSInterface/OSInterface.h"

//#define _Stt_Cmtrd_Save_File_

#define COMTRADE_DATABUF_DEFAULT_SIZE	2048
#define COMTRADE_DATABUF_MODE_WRITE		0
#define COMTRADE_DATABUF_MODE_READ		1

class CComtradeDataBuffer
{
public:
	CComtradeDataBuffer();
	virtual ~CComtradeDataBuffer();

private:
	float *m_pDataBuffer;
	int m_nMaxLength;
	int m_nPosRead;
	int m_nPosWrite;
	int m_nRWFlag; //0=无效，可以写入；1=写入完成，可以读；

public:
	void Init(int nBufLen);
	int ReadData(float *pBuf,int nMaxLen);
	int ReadData (float &fValue);
	void WriteData (float *pSrcBuf,int nSrcLen);
	void WriteData (float fValue);
	void WriteData_Zero(long nFloatNum);//按固定长度写零值,传参的值1代表4个字节,即对应几个Float的长度
	BYTE* WriteData(BYTE *pByte,int nLenth);//用于数字回放写数据,参数2正常应该为4的整数倍,如果不是会自动按4的整数倍处理,不足部分补零 zhouhj 2023.8.17
	BOOL CanRead();
	BOOL CanWrite();
	void SetRWState(int nRWState);
	void ResetReadPos(int nReadPos=0);
	void OffsetReadPos(int nOffset);
	void ResetWritePos(int nWritePos=0);
	int GetRemainSpace();//写之前获取剩余空间
	int GetDataLen();//读之前获取有效数据长度
	float *GetCurDataBuf()	{ return (float *)(m_pDataBuffer+m_nPosRead);}
	float *GetBuffer()	{return m_pDataBuffer;	}

	void BufferDatas_WriteFile();//增加用于写文件,查找发送的数据值是否正确
};

extern CFile m_oCmtrdSaveFile;
BOOL OpenCmtrdSaveFile(const CString &strFile);
void CloseCmtrdSaveFile();
#endif