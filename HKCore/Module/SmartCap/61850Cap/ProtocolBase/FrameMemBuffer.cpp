// CFrameMemBuffer.cpp : 实现文件
//

#include "stdafx.h"
#include "FrameMemBuffer.h"

CFrameMemBuffer::CFrameMemBuffer()
{
	m_dwState = 0;

	ZeroMemory(&m_oCapBufferItem, sizeof(EPCAPBUFFERITEM));
	m_n64Pos = 0;
	m_n64FrameID = 0;
	m_n64DataPos = 0;
	m_dwReserved = NULL;
}

CFrameMemBuffer::~CFrameMemBuffer()
{
}

void CFrameMemBuffer::GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex)
{
	ZeroMemory(&oIndex, sizeof(EPCAPDBBUFFERINDEX));
	oIndex.n64CapID = m_n64FrameID;   //cap id
	oIndex.cap_addr = m_oCapBufferItem; //ip或者端口
	oIndex.nProtocol = m_oCapBufferItem.nProtocol;  //规约类型
	oIndex.tm.n64Time = *((__int64*)&m_oCapBufferItem.Time); //cap的时间
	oIndex.nFrameLen = (WORD)m_nBufferLength;//m_nDataLength;  //cap的长度
	//	oIndex.nDeviceDataLen = (WORD)m_dwDeviceDataLen;
	oIndex.n64CapFramePos = m_n64Pos;
	oIndex.n64CapDataPos = m_n64DataPos;
	//	oIndex.oDataHead.nDataCount = 0;
	//	oIndex.oDataHead.nDeviceDataType = m_pDeviceDatas->m_nDeviceDataType;
}

long CFrameMemBuffer::GetPkgChNum()
{
	long nChNum = 0;
	WORD wValue = 0;

	//跳过前面MAC等内容,开始查找时间同步信号
	for (int nIndex = 40; nIndex<m_nBufferLength;nIndex++)
	{
		wValue = Ep_BufferGetWord(&m_pBuffer[nIndex]);

		//找到时间同步信号
		if (wValue == 0x8501)
		{
			wValue = Ep_BufferGetWord(&m_pBuffer[nIndex + 3]);

			//紧跟着采样通道数量
			if (wValue == 0x8781)//多通道模式
			{
				nChNum = m_pBuffer[nIndex + 5];
				nChNum /=8;
				break;
			}
			else if ((wValue | 0xFF) == 0x87FF)
			{
				nChNum = m_pBuffer[nIndex + 4];
				nChNum /=8;
				break;
			}
		}
	}

	return nChNum;
}

long CFrameMemBuffer::GetAsduNum()
{
	long nAsduNum = 1;
	WORD wValue = 0;

	//跳过前面MAC等内容,开始查找时间同步信号
	for (int nIndex = 25; nIndex<m_nBufferLength;nIndex++)
	{
		wValue = Ep_BufferGetWord(&m_pBuffer[nIndex]);

		//找到时间同步信号
		if (wValue == 0x8001)
		{
			nAsduNum = m_pBuffer[nIndex + 2];
			break;
		}
	}

	if (nAsduNum>10)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取到的ASDU数目(%ld)大于10,强制设置为1."),nAsduNum);
		nAsduNum = 1;
	}

	return nAsduNum;
}

long CFrameMemBuffer::GetSmpCount()
{
	long nChNum = 0;
	WORD wValue = 0;
	long nSmpCount = -1;

	//跳过前面MAC等内容,开始查找时间同步信号
	for (int nIndex = 30; nIndex<m_nBufferLength;nIndex++)
	{
		wValue = Ep_BufferGetWord(&m_pBuffer[nIndex]);

		//找到采样计数器
		if (wValue == 0x8202)
		{
			nSmpCount = Ep_BufferGetWord(&m_pBuffer[nIndex + 2]);
		}
	}

	return nSmpCount;
}