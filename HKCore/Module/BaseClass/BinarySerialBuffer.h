// BinarySerialBuffer.h : CBinarySerialBuffer µÄÉùÃ÷

#pragma once

#include "WSerializeBuff.h"
// #include "ShareMemSerialize.h"

// CBinarySerialBuffer
#define FILE_VERSION_FREFIX_LENGTH 20
#define FILE_VERSION_MAX_COUNT     20

#define FILE_VERSION_END    "#VERSION#"

#define  CHAR_SET_ASCII        "ASCII$$"
#define  CHAR_SET_UNICODE   "UNICODE"

#define SERIAL_BUFFER_MODE_WBUFFER     0
#define SERIAL_BUFFER_MODE_SHAREMEM  1

typedef struct _CBinaryVersion_
{
	long m_nPrefixLength;
	char m_chPrefix[FILE_VERSION_FREFIX_LENGTH];
	DWORD m_dwVersion;
	DWORD m_dwVersionID;
}CBinaryVersion;

class CBinarySerialBuffer : public CWSerializeBuff
{
public:
        CBinarySerialBuffer() : CWSerializeBuff()
	{
		//m_pSerialBuffer = new CWSerializeBuff();
		Init();
	}
	CBinarySerialBuffer(UINT nBufferMode);

	virtual ~CBinarySerialBuffer()
	{
		SerializeFree();
		//m_pSerialBuffer->SerializeFree();
		//delete m_pSerialBuffer;
	}

	void Init()
	{
		m_nPrefixLength = 0;
		memset(m_chCharSet, 0, FILE_VERSION_FREFIX_LENGTH);
		memset(m_chPrefix, 0, FILE_VERSION_FREFIX_LENGTH);
		m_dwVersion = 0;
		m_dwCharSetUnicode = 0;
		m_dwVersionFind = 0;
		m_nVersionCount = 0;
                memset(&m_oArrBinaryVersion, 0, sizeof(CBinaryVersion) * FILE_VERSION_MAX_COUNT);
	}

public:
	long m_nPrefixLength;
	long m_nCharSetLength;
	char m_chPrefix[FILE_VERSION_FREFIX_LENGTH];
	char m_chCharSet[FILE_VERSION_FREFIX_LENGTH];
	DWORD m_dwVersion;
	DWORD m_dwCharSetUnicode;
	DWORD m_dwVersionFind;

	void WriteVersion();
	BOOL ReadVersion();

	BOOL AddBinaryVersion(const char *pszPrefix, DWORD dwVersion, DWORD dwVersionID);
	void SetCharSet(char *pszCharSet);

	DWORD SetVersionFind(DWORD dwVersion)
	{
		m_dwVersionFind = dwVersion;
		return m_dwVersionFind;
	}

	DWORD SetVersionFindByID(DWORD dwVersionID)
	{
		m_dwVersionFind = 0;
		long nIndex=0;

		for (nIndex=0; nIndex<FILE_VERSION_MAX_COUNT; nIndex++)
		{
			if (m_oArrBinaryVersion[nIndex].m_dwVersionID == dwVersionID)
			{
				m_dwVersionFind = m_oArrBinaryVersion[nIndex].m_dwVersion;
				break;
			}
		}

		return m_dwVersionFind;
	}

	void ResetVersion()
	{
		long nIndex=0;

		for (nIndex=0; nIndex<FILE_VERSION_MAX_COUNT; nIndex++)
		{
			m_oArrBinaryVersion[nIndex].m_dwVersion = 0;
		}
	}

private:
	//CWSerializeBuff  m_oSerialBuffer;
	//CWSerializeBuff  *m_pSerialBuffer;
	long m_nVersionCount;
	CBinaryVersion m_oArrBinaryVersion[FILE_VERSION_MAX_COUNT];
	
	CBinaryVersion* FindByVersionID(DWORD dwVersionID)
	{
		long nIndex=0;

		for (nIndex=0; nIndex<FILE_VERSION_MAX_COUNT; nIndex++)
		{
			if (m_oArrBinaryVersion[nIndex].m_dwVersionID == dwVersionID)
			{
				return &m_oArrBinaryVersion[nIndex];
			}
		}

		return NULL;
	}


public:
	short GetShort ( );
	void PutShort (short pVal );
	long GetLong ( );
	void PutLong (long pVal );
	DWORD GetDWord ( );
	void PutDWord (DWORD pVal );
	float GetFloat ( );
	void PutFloat (float pVal );
	double GetDouble ( );
	void PutDouble (double pVal );
	CString GetString ( );
	void GetString ( CString &str );
	void PutString (const CString &pVal );
#ifndef _PSX_IDE_QT_
        CURRENCY GetCurrency ( );
	void PutCurrency (const CURRENCY & pVal );
#endif
    SYSTEMTIME GetSystemtime ( );
	void PutSystemtime (const SYSTEMTIME & pVal );
    short GetByte ( );
	void PutByte (short pVal );
	//HRESULT AddBufferLength (long nLen );
	//long SetBufferLength (long nLen );
	//virtual  long AllocBuffer (long lExpandPercent = 0);
	//HRESULT ResetBufferPointer ( );
	//HRESULT SetReadMode ( );
	//HRESULT SetWriteMode ( );
	//HRESULT SetCalSizeMode ( );
	//long IsReadMode ( );
	//long IsWriteMode ( );
	//long IsCalSizeMode ( );
	//virtual BOOL CreateFile(const CString &strFile);
	long SaveToFile (const CString &strFile);
	long OpenFromFile (const CString &strFile, long nAddBuf=0);

	////add by zhougang    2016/06/12
	//void GetBuffer(wchar_t** pBuffer, long *nBufferLen);
	//void GetBuffer(char** pBuffer, long *nBufferLen); 

	//void AttachBuffer(wchar_t *pBuffer, long nBufferLen);
	//void AttachBuffer(char *pBuffer, long nBufferLen);
	//void DettachBuffer();
};
