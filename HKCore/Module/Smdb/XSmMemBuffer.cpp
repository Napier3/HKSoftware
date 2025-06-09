// CXSmMemBuffer.cpp : 实现文件
//

#include "stdafx.h"
#include "XSmMemBuffer.h"

CXSmMemBuffer::CXSmMemBuffer()
{
	m_dwState = 0;
	m_n64Pos = 0;
	m_n64TimeSnamp = 0;
	m_nFiberAndPkgType = 0;
}

CXSmMemBuffer::~CXSmMemBuffer()
{
	FreeBuffer();
}

// void CXSmMemBuffer::FreeBuffer(BOOL bOnlyDeleteBuffer)
// {
// 	if (m_pBuffer!= NULL)
// 	{
// 		delete m_pBuffer;
// 		m_pBuffer = NULL;
// 	}
// }

// 
// void CXSmMemBuffer::GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex)
// {
// 	ZeroMemory(&oIndex, sizeof(EPCAPDBBUFFERINDEX));
// 	oIndex.n64CapID = m_n64FrameID;   //cap id
// 	oIndex.cap_addr = m_oCapBufferItem; //ip或者端口
// 	oIndex.nProtocol = m_oCapBufferItem.nProtocol;  //规约类型
// 	oIndex.tm.n64Time = *((__int64*)&m_oCapBufferItem.Time); //cap的时间
// 	oIndex.nFrameLen = (WORD)m_nBufferLength;//m_nDataLength;  //cap的长度
// 	//	oIndex.nDeviceDataLen = (WORD)m_dwDeviceDataLen;
// 	oIndex.n64CapFramePos = m_n64FrmPos;
// 	oIndex.n64CapDataPos = m_n64DataPos;
// 	//	oIndex.oDataHead.nDataCount = 0;
// 	//	oIndex.oDataHead.nDeviceDataType = m_pDeviceDatas->m_nDeviceDataType;
// }