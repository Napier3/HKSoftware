#include "stdafx.h"
#include "ComtradeDataBuffer.h"
#include "../../../Module/API/GlobalConfigApi.h"

CFile m_oCmtrdSaveFile;

CComtradeDataBuffer::CComtradeDataBuffer()
{
	m_pDataBuffer = NULL;
	m_nMaxLength = 0;

	Init(COMTRADE_DATABUF_DEFAULT_SIZE);
}

CComtradeDataBuffer::~CComtradeDataBuffer()
{
	if (m_pDataBuffer != NULL)
	{
		delete m_pDataBuffer;
		m_pDataBuffer = NULL;
	}
}

void CComtradeDataBuffer::Init(int nBufLen)
{
	ASSERT(nBufLen > 0);

	if (m_pDataBuffer != NULL)
	{
		delete m_pDataBuffer;
	}

	m_pDataBuffer = new float[nBufLen];
	m_nMaxLength = nBufLen;
	m_nPosRead = 0;
	m_nPosWrite = 0;
	m_nRWFlag = COMTRADE_DATABUF_MODE_WRITE;
}

int CComtradeDataBuffer::ReadData(float *pBuf,int nMaxLen)
{
	if (!CanRead())
	{
		return 0;
	}

	int nDataLen = m_nPosWrite - m_nPosRead;
	int nReadLen = min(nDataLen,nMaxLen);
	memcpy(pBuf,m_pDataBuffer+m_nPosRead,nReadLen*sizeof(float));
	m_nPosRead += nReadLen;

	if (nDataLen <= nMaxLen)
	{
		SetRWState(COMTRADE_DATABUF_MODE_WRITE);
	}
	return nReadLen;
}

int CComtradeDataBuffer::ReadData (float &fValue)
{
	if (!CanRead())
	{
		return 0;
	}

	int nDataLen = m_nPosWrite - m_nPosRead;
	fValue = m_pDataBuffer[m_nPosRead++];

	if (nDataLen <= 1)
	{
		SetRWState(COMTRADE_DATABUF_MODE_WRITE);
	}
	return 1;
}

void CComtradeDataBuffer::WriteData (float *pSrcBuf,int nSrcLen)
{
	ASSERT(m_nMaxLength - m_nPosWrite >= nSrcLen + 10);

	memcpy(m_pDataBuffer+m_nPosWrite, pSrcBuf, nSrcLen*sizeof(float));
	m_nPosWrite += nSrcLen;
}

BYTE* CComtradeDataBuffer::WriteData(BYTE *pByte,int nLenth)
{
	int nFloatNum = nLenth/4;
	ASSERT(m_nMaxLength - m_nPosWrite >= nFloatNum + 10);

	BYTE *pCurrPos = (BYTE*)(m_pDataBuffer+m_nPosWrite);
	memcpy(pCurrPos, pByte, nLenth);

	if ((nLenth%4)>0)//自动按4的整数倍处理,不足部分补零
	{
		nFloatNum++;
		memset(pCurrPos + nLenth,0,nLenth%4);
//		memcpy(pCurrPos + nFloatNum*4, pByte + nFloatNum*4, nLenth%4);
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("写数据长度(%d)必须为4的整数倍."),nLenth);
	}

	m_nPosWrite += nFloatNum;
	return pCurrPos;
}

void CComtradeDataBuffer::WriteData_Zero(long nFloatNum)
{
	if (nFloatNum<=0)
	{
		return;
	}

	ASSERT(m_nMaxLength - m_nPosWrite >= nFloatNum + 10);
	BYTE *pCurrPos = (BYTE*)(m_pDataBuffer+m_nPosWrite);
	memset(pCurrPos,0,nFloatNum*4);
	m_nPosWrite += nFloatNum;
}

void CComtradeDataBuffer::WriteData (float fValue)
{
	ASSERT(m_nMaxLength - m_nPosWrite >= 1 + 10);
	m_pDataBuffer[m_nPosWrite++] = fValue;
}

BOOL CComtradeDataBuffer::CanRead()
{
	return (COMTRADE_DATABUF_MODE_READ == m_nRWFlag);
}

BOOL CComtradeDataBuffer::CanWrite()
{
	return (COMTRADE_DATABUF_MODE_WRITE == m_nRWFlag);
}

void CComtradeDataBuffer::SetRWState(int nRWState)
{
	if (COMTRADE_DATABUF_MODE_WRITE == nRWState)
	{//设置写有效，说明数据无效
		m_nPosRead = 0;
		m_nPosWrite = 0;
	}
	else
	{//设置读有效
		m_nPosRead = 0;
	}

	m_nRWFlag = nRWState;
}

void CComtradeDataBuffer::ResetReadPos(int nReadPos)
{
	m_nPosRead = nReadPos;
}

void CComtradeDataBuffer::OffsetReadPos(int nOffset)
{
	m_nPosRead += nOffset;
}

void CComtradeDataBuffer::ResetWritePos(int nWritePos)
{
	m_nPosWrite = nWritePos;
}

int CComtradeDataBuffer::GetRemainSpace()
{//保证剩余10B空缓存
	return (m_nMaxLength - m_nPosWrite - 10);
}

int CComtradeDataBuffer::GetDataLen()
{
	return (m_nPosWrite - m_nPosRead);
}

void CComtradeDataBuffer::BufferDatas_WriteFile()
{
	if (m_pDataBuffer == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("BufferDatas_WriteFile,m_pDataBuffer==NULL."));
		return;
	}

#ifndef _PSX_QT_LINUX_
	CString strFile;
	strFile = _P_GetLibraryPath();
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	strFile.AppendFormat(_T("ComtradeDataBuffer-%04d.%02d.%02d_%02d-%02d-%02d-%03d.txt"),
		tm.wYear,tm.wMonth,tm.wDay, tm.wHour, tm.wMinute, tm.wSecond ,tm.wMilliseconds);
	CFile oFile;

	if (! oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		return;
	}

	long nTmpValue = 0;
	CString strTmp;

	for (long nIndex = 0;nIndex<m_nPosWrite;nIndex++)
	{
		strTmp.Format(_T("%f\r\n"),m_pDataBuffer[nIndex]);
		oFile.Write(strTmp.GetString(), strTmp.GetLength());
	}

	oFile.Close();
#endif
}

BOOL OpenCmtrdSaveFile(const CString &strFile)
{
	UINT nMode = CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;
#ifdef _PSX_IDE_QT_
	nMode |= CFile::Truncate;
#endif
	BOOL bRet = m_oCmtrdSaveFile.Open(strFile, nMode);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]创建写文件失败"),strFile.GetString());
	}

	return bRet;
}

void CloseCmtrdSaveFile()
{
#ifdef _PSX_IDE_QT_
	if (m_oCmtrdSaveFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
	if (m_oCmtrdSaveFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
	{
		m_oCmtrdSaveFile.Close();
	}
}