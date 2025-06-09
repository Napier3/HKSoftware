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
	int m_nRWFlag; //0=��Ч������д�룻1=д����ɣ����Զ���

public:
	void Init(int nBufLen);
	int ReadData(float *pBuf,int nMaxLen);
	int ReadData (float &fValue);
	void WriteData (float *pSrcBuf,int nSrcLen);
	void WriteData (float fValue);
	void WriteData_Zero(long nFloatNum);//���̶�����д��ֵ,���ε�ֵ1����4���ֽ�,����Ӧ����Float�ĳ���
	BYTE* WriteData(BYTE *pByte,int nLenth);//�������ֻط�д����,����2����Ӧ��Ϊ4��������,������ǻ��Զ���4������������,���㲿�ֲ��� zhouhj 2023.8.17
	BOOL CanRead();
	BOOL CanWrite();
	void SetRWState(int nRWState);
	void ResetReadPos(int nReadPos=0);
	void OffsetReadPos(int nOffset);
	void ResetWritePos(int nWritePos=0);
	int GetRemainSpace();//д֮ǰ��ȡʣ��ռ�
	int GetDataLen();//��֮ǰ��ȡ��Ч���ݳ���
	float *GetCurDataBuf()	{ return (float *)(m_pDataBuffer+m_nPosRead);}
	float *GetBuffer()	{return m_pDataBuffer;	}

	void BufferDatas_WriteFile();//��������д�ļ�,���ҷ��͵�����ֵ�Ƿ���ȷ
};

extern CFile m_oCmtrdSaveFile;
BOOL OpenCmtrdSaveFile(const CString &strFile);
void CloseCmtrdSaveFile();
#endif