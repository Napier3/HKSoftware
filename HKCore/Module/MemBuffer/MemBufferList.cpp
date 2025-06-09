// MemBufferList.cpp: implementation of the CMemBufferList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemBufferList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBufferList::CMemBufferList()
{
	write_index = 0;
	read_index = 0;
	ZeroMemory(buff, sizeof(PIPE_MSG_BUF) * MAX_PIPE_MSG_BUFS);
}

CMemBufferList::~CMemBufferList()
{
	free_pipe_msg_bufs();
}


void CMemBufferList::set_pipe_msg_buf_len(PIPE_MSG_BUF *pBuf, long len)
{
	if (len == 0)
	{
		len = 10;
	}

	len += 5;

	if (pBuf->capacity < len)
	{
		free_pipe_msg_buf(pBuf);
		pBuf->buff = (BYTE*)malloc (len);
		pBuf->capacity = len;
	}
}

void CMemBufferList::set_pipe_msg(CMemBufferList::PIPE_MSG_BUF *pBuf, long tpkt_len, BYTE *tpkt_ptr)
{
	set_pipe_msg_buf_len(pBuf, tpkt_len);
	memcpy(pBuf->buff, tpkt_ptr, tpkt_len);
	pBuf->buff[tpkt_len] = 0;
	pBuf->len = tpkt_len;
	pBuf->parse_flag = 1;
}

BOOL CMemBufferList::add_pipe_msg(long tpkt_len, BYTE *tpkt_ptr, PCYCLEMEMBUFFERPOS pBufPos)
{
	PIPE_MSG_BUF *pBuf = &buff[write_index];

	//0:空的  //1:还未解析	//2:已经解析
	if (pBuf->parse_flag == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("add_pipe_msg error...... buffer is full......") );
		return 0;
	}

	set_pipe_msg(pBuf, tpkt_len, tpkt_ptr);
	write_index = write_index + 1;

	if (pBufPos != NULL)
	{
		pBufPos->nBuf1BeginPos = 0;
		pBufPos->nBuf1EndPos = pBuf->len;
		pBufPos->nBufLength = pBuf->len;
		pBufPos->pBuffer = pBuf->buff;
	}

	if (write_index >= MAX_PIPE_MSG_BUFS)
	{
		write_index = 0;
	}

	return TRUE;
}

BOOL CMemBufferList::has_pipe_msg()
{
	long index = 0;
	PIPE_MSG_BUF *pBuf = &buff[read_index];

	//0:空的  //1:还未解析	//2:已经解析
	if (pBuf->parse_flag == 0 || pBuf->parse_flag == 2)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMemBufferList::get_pipe_msg(CYCLEMEMBUFFERPOS &oBufPos)
{
	long index = 0;
	PIPE_MSG_BUF *pBuf = &buff[read_index];

	//0:空的  //1:还未解析	//2:已经解析
	if (pBuf->parse_flag == 0 || pBuf->parse_flag == 2)
	{
		return FALSE;
	}

	ZeroMemory(&oBufPos, sizeof(oBufPos));
	oBufPos.pBuffer = pBuf->buff;
	oBufPos.nBuf1EndPos = pBuf->len;
	oBufPos.nBuf1BeginPos = 0;

	if (read_index >= MAX_PIPE_MSG_BUFS)
	{
		read_index = 0;
	}

	return TRUE;
}


void CMemBufferList::free_pipe_msg_buf(PIPE_MSG_BUF *pBuf)
{
	if (pBuf->buff != NULL)
	{
		free(pBuf->buff);
		pBuf->buff = NULL;
	}

	pBuf->capacity = 0;
	pBuf->len = 0;
}

void CMemBufferList::free_pipe_msg_bufs()
{
	long nIndex = 0;
	PIPE_MSG_BUF *pBuf = NULL;

	for (nIndex=0; nIndex<MAX_PIPE_MSG_BUFS; nIndex++)
	{
		pBuf = &buff[nIndex];
		free_pipe_msg_buf(pBuf);
	}
}

BOOL CMemBufferList::read_pipe_msg(CYCLEMEMBUFFERPOS &oBufPos)
{
	PIPE_MSG_BUF *pBuf = &buff[read_index];

	//0:空的  //1:还未解析	//2:已经解析
	if (pBuf->parse_flag == 0 || pBuf->parse_flag == 2)
	{
		return FALSE;
	}

	oBufPos.pBuffer = pBuf->buff;
	oBufPos.nBuf1BeginPos = 0;
	oBufPos.nBuf1EndPos = pBuf->len;
	oBufPos.nBufLength = pBuf->len;
	set_buf_parse(pBuf);

	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("MemBufferList::read_index=%d buf-len=%d"), read_index, pBuf->len);

	read_index++;

	if (read_index >= MAX_PIPE_MSG_BUFS)
	{
		read_index = 0;
	}

	return TRUE;
}

long CMemBufferList::GetBufferPos(long nBeginPos, long nLen, CYCLEMEMBUFFERPOS &oBufPos)
{
	if (!has_pipe_msg())
	{
		return 0;
	}

	return read_pipe_msg(oBufPos);
}
