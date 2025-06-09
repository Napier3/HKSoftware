// SerializeBuff.h: interface for the CWSerializeBuff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WSERIALIZEBUFF_H__)
#define _WSERIALIZEBUFF_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SerializeBufferBase.h"

class CWSerializeBuff : public CSerializeBufferBase
{
protected:
	virtual void FreeBuff();

	BOOL	m_bAttach;

public:
	CWSerializeBuff();
	CWSerializeBuff(int nLen);
	CWSerializeBuff(wchar_t *pBuff,int nLen);
	CWSerializeBuff(char *pBuff,int nLen);
	virtual ~CWSerializeBuff();

	virtual void GetBuffer(wchar_t** pBuffer, long *nBufferLen);
	virtual void GetBuffer(char** pBuffer, long *nBufferLen);
	virtual void AttachBuffer(wchar_t *pBuffer, long nBufferLen);
	virtual void AttachBuffer(char *pBuffer, long nBufferLen);
	virtual void DettachBuffer();
	
	virtual BOOL ReadFromFile(const CString &strFile, long nAddBuf=0);
	virtual BOOL WriteToFile(const CString &strFile);	
	virtual BOOL CreateFile(const CString &strFile);
	//////////////////////////////////////////////////////////////////////////
	//接口定义重载
	
	//缓冲区的长度管理
	virtual void SerializeFree();
	virtual BOOL AllocDefaultBuffer();	
	virtual BOOL AllocBuffer(long lExpandPercent = 0);	
	virtual BOOL SetBufferLength(int nLen);

};

#endif // !defined(_WSERIALIZEBUFF_H__)
