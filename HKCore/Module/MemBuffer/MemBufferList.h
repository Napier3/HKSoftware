// MemBufferList.h: interface for the CMemBufferList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MemBufferList_h__)
#define _MemBufferList_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CycleMemBuffer.h"

class CMemBufferList
{
public:	
	CMemBufferList();
	virtual ~CMemBufferList();

	CString m_strBufferID;   //缓冲区的标示，整个系统中，此标示唯一

	long Get_read_index()	{	return read_index;	}
	long Get_write_index()	{	return write_index;	}

protected:
#define  MAX_PIPE_MSG_BUFS    2000

	typedef struct 
	{
		long len;
		long capacity;
		long parse_flag;  
		BYTE *buff;
	}PIPE_MSG_BUF;

	long read_index;
	long write_index;
	PIPE_MSG_BUF buff[MAX_PIPE_MSG_BUFS];

public:
	static BOOL is_buf_empty(PIPE_MSG_BUF *pBuf)
	{
		return (pBuf->parse_flag == 0) ;
	}
	static BOOL is_buf_write(PIPE_MSG_BUF *pBuf)
	{
		return (pBuf->parse_flag == 1) ;
	}
	static BOOL is_buf_parse(PIPE_MSG_BUF *pBuf)
	{
		return (pBuf->parse_flag == 2) ;
	}
	static void set_buf_empty(PIPE_MSG_BUF *pBuf)
	{
		pBuf->parse_flag = 0 ;
	}
	static void set_buf_write(PIPE_MSG_BUF *pBuf)
	{
		pBuf->parse_flag = 1;
	}
	static void set_buf_parse(PIPE_MSG_BUF *pBuf)
	{
		pBuf->parse_flag = 2;
	}

	void set_pipe_msg(PIPE_MSG_BUF *pBuf, long tpkt_len, BYTE *tpkt_ptr);
	BOOL add_pipe_msg(long tpkt_len, BYTE *tpkt_ptr, PCYCLEMEMBUFFERPOS pBufPos);
	BOOL has_pipe_msg();
	BOOL get_pipe_msg(CYCLEMEMBUFFERPOS &oBufPos);

	void set_pipe_msg_buf_len(PIPE_MSG_BUF *pBuf, long len);
	void free_pipe_msg_buf(PIPE_MSG_BUF *pBuf);
	void free_pipe_msg_bufs();

	BOOL read_pipe_msg(CYCLEMEMBUFFERPOS &oBufPos);

	virtual long GetBufferPos(long nBeginPos, long nLen, CYCLEMEMBUFFERPOS &oBufPos);
};


#endif // !defined(_MemBufferList_h__)
