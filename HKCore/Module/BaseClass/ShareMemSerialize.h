// ShareMemSerialize.h: interface for the CShareMemSerialize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ShareMemSerialize_H__)
#define _ShareMemSerialize_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ShareMem\ShareMemServerEx.h"
// #include "WSerializeBuff.h"
#include "BinarySerialBuffer.h"

class CShareMemSerialize : public CBinarySerialBuffer //CWSerializeBuff  2018-10-12
{
public:
	CShareMemSerialize();
	virtual ~CShareMemSerialize();

public:
	virtual void GetBuffer(wchar_t** pBuffer, long *nBufferLen);
	virtual void GetBuffer(char** pBuffer, long *nBufferLen);
	virtual void AttachBuffer(wchar_t *pBuffer, long nBufferLen);
	virtual void AttachBuffer(char *pBuffer, long nBufferLen);
	virtual void DettachBuffer();
	
	virtual BOOL ReadFromFile(const CString &strFile, long nAddBuf=0);
	virtual BOOL WriteToFile(const CString &strFile);	
	virtual BOOL CreateFile(const CString &strFile);
	virtual BOOL CreateFileEx(const CString &strFile, DWORD dwLen); //2018-10-12  lijq
	//////////////////////////////////////////////////////////////////////////
	//接口定义重载
	
	//缓冲区的长度管理
	virtual void SerializeFree();
	virtual BOOL AllocDefaultBuffer();	
	virtual BOOL AllocBuffer(long lExpandPercent);	
	virtual BOOL SetBufferLength(int nLen);
	virtual int  GetBufferLength()	{	return m_nBufferLength;	}

protected:
	CShareMemServerEx m_oShareMem;
	virtual void FreeBuff();
};

#endif // !defined(_ShareMemSerialize_H__)
