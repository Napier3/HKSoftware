// EncryptWriteTool.h: interface for the CEncryptWriteTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EncryptWriteTool_H__)
#define _EncryptWriteTool_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EncryptBase.h"

class CEncryptWriteTool : public CEncryptBase
{
public:
	CEncryptWriteTool();
	virtual ~CEncryptWriteTool();

// Ù–‘∂®“Â
private:
	CFile m_oFile;
	char *m_pBufferRead;
	long m_nCurrPos;
	long m_nBeginPos;
	long m_nEndPos;

protected:
	BOOL SeekToEncryptBuffer();
	BOOL Register(const CString &strExeFile, const CString &strRegCode);

	void WriteEncrypt(long nID, CString &strText);
	void WriteEncrypt(long nID, long &nValue);

public:
	BOOL CanRunRegister();
	BOOL Register(const CString &strRegCode);
};

extern CEncryptWriteTool g_oEncryptWriteTool;

#endif // !defined(_EncryptWriteTool_H__)
