#if !defined(_MacAddrBuffer_H__)
#define _MacAddrBuffer_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferBase.h"
#include "..\API\GlobalApi.h"


class CMacAddrBuffer  : public CBufferBase
{
public:
	CMacAddrBuffer();
	virtual ~CMacAddrBuffer();

	BOOL SetMacAddr(const CString &strMacAddr);
	BOOL SetMacAddr(BYTE b6, BYTE b5, BYTE b4, BYTE b3, BYTE b2, BYTE b1);
	BOOL SetMacAddr(BYTE *pMacAddr);
	
	CString GetMacAddr();
	BOOL GetMacAddr(BYTE &b6, BYTE &b5, BYTE &b4, BYTE &b3, BYTE &b2, BYTE &b1);
	BOOL GetMacAddr(BYTE *pMacAddr);

protected:
	CString m_strMacAddr;
	BYTE m_byteMacAddr[6];

	void AppendMacAddr(BYTE bVal, BOOL bAddDot=TRUE);
};

#endif // !defined(_MacAddrBuffer_H__)
