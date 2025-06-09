// CEpCycleMemBuffer.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCycleMemBuffer.h"

CEpCycleMemBuffer::CEpCycleMemBuffer()
{
	m_nCurrPos = 0;
	m_dwState = 0;
}

CEpCycleMemBuffer::~CEpCycleMemBuffer()
{
}

void CEpCycleMemBuffer::OffsetCurrPos(long nLen)
{
	if (nLen == -1)
	{
		m_nCurrPos = m_nDataLength;
	}
	else
	{
		m_nCurrPos += nLen;
	}

	if (m_nCurrPos >= m_nDataLength)
	{
		SetState(EBS_BEPARSED);
	}
	else
	{
		SetState(EBS_SOMEPARSED);
	}
}

void CEpCycleMemBuffer::SetCurrPos(long nPos)
{
	m_nCurrPos = nPos;

	if (m_nCurrPos >= m_nDataLength)
	{
		SetState(EBS_BEPARSED);
	}
	else
	{
		SetState(EBS_SOMEPARSED);
	}
}


void CEpCycleMemBuffer::SetCurrPos(PEPBUFFERPOS pBufferPos)
{
	SetCurrPos(pBufferPos->nIndex);
}

void CEpCycleMemBuffer::CombineBuffer(CEpCycleMemBuffer *pPrev)
{
	long nLen = pPrev->m_nDataLength - pPrev->m_nCurrPos;

	if (nLen <= 0)
	{
		return;
	}

	long nTotalLen = nLen + m_nDataLength;
	BYTE *pPrevBuffer = pPrev->GetBuffer() + pPrev->m_nCurrPos;
	BYTE *pBuffer = new BYTE[nTotalLen+4];

	memcpy(pBuffer, pPrevBuffer, nLen);
	memcpy(pBuffer + nLen, m_pBuffer, m_nDataLength);
	FreeBuffer();
	m_pBuffer = pBuffer;
	m_nBufferLength = nTotalLen + 4;
	m_nDataLength = nTotalLen;
	pPrev->SetState(EBS_BEPARSED);
}

void CEpCycleMemBuffer::GetBufferPos(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->pBuffer = m_pBuffer;      //缓冲区地址
	pBufferPos->dwBufferLen = m_nDataLength;  //缓冲区长度
	pBufferPos->nIndex = m_nCurrPos;        //当前使用的缓冲区位置
	pBufferPos->dwState = m_dwState;      //状态，例如匹配的状态
	pBufferPos->n64ID = 0;        //相关的ID，例如CaptureID
}
