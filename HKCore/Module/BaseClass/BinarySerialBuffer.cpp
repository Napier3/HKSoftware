// BinarySerialBuffer.cpp : CBinarySerialBuffer 的实现

#include "stdafx.h"
#include "BinarySerialBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CBinarySerialBuffer
CBinarySerialBuffer::CBinarySerialBuffer(UINT nBufferMode)
{
// 	if (nBufferMode == SERIAL_BUFFER_MODE_SHAREMEM)
// 	{
// #ifdef _use_CShareMemSerialize
// 		m_pSerialBuffer = new CShareMemSerialize();
// #else
// 		m_pSerialBuffer = new CWSerializeBuff();
// #endif
// 	}
// 	else
// 	{
// 		m_pSerialBuffer = new CWSerializeBuff();
// 	}

	Init();
}

void CBinarySerialBuffer::WriteVersion()
{
	m_nPrefixLength = strlen(m_chPrefix);
	m_nCharSetLength = strlen(m_chCharSet);
	long nIndex = 0;
	CBinaryVersion *pVersion = NULL;

	if (IsCalSizeMode())
	{
		/*m_pSerialBuffer->*/AddBufferLength(m_nPrefixLength+4);

		if (m_nCharSetLength > 0)
		{
			/*m_pSerialBuffer->*/AddBufferLength(m_nCharSetLength+4);
		}

		for (nIndex=0; nIndex<m_nVersionCount; nIndex++)
		{
			/*m_pSerialBuffer->*/AddBufferLength(m_oArrBinaryVersion[nIndex].m_nPrefixLength+4);
		}

		/*m_pSerialBuffer->*/AddBufferLength(strlen(FILE_VERSION_END));

		return;
	}

	if (IsWriteMode())
	{
		if (m_nCharSetLength > 0)
		{
			/*m_pSerialBuffer->*/WriteBuffer(m_chCharSet, m_nCharSetLength);
		}

		/*m_pSerialBuffer->*/WriteBuffer(m_chPrefix, m_nPrefixLength);
		/*m_pSerialBuffer->*/DWord(m_dwVersion);
	
		if (m_nVersionCount == 0)
		{
			return;
		}

		for (nIndex=0; nIndex<m_nVersionCount; nIndex++)
		{
			pVersion = &m_oArrBinaryVersion[nIndex];
			/*m_pSerialBuffer->*/WriteBuffer(pVersion->m_chPrefix, pVersion->m_nPrefixLength);
			/*m_pSerialBuffer->*/DWord(pVersion->m_dwVersion);
		}

        WriteBuffer((LPVOID)FILE_VERSION_END, strlen(FILE_VERSION_END));

		return;
	}
}

BOOL CBinarySerialBuffer::ReadVersion()
{
	m_nPrefixLength = strlen(m_chPrefix);
	m_nCharSetLength = strlen(CHAR_SET_UNICODE);

	if (m_nPrefixLength <= 0)
	{
		m_dwVersion = 0;
		return FALSE;
	}

	if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)CHAR_SET_UNICODE, m_nCharSetLength) )
	{
		m_dwCharSetUnicode = 1;
		/*m_pSerialBuffer->*/SetCharSetUnicode();
		/*m_pSerialBuffer->*/Offset(m_nCharSetLength);
	}
	else if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)CHAR_SET_ASCII, m_nCharSetLength) )
	{
		m_dwCharSetUnicode = 0;
		/*m_pSerialBuffer->*/SetCharSetAscii();
		/*m_pSerialBuffer->*/Offset(m_nCharSetLength);
	}
	else
	{
		/*m_pSerialBuffer->*/SetCharSetUnicode();
		m_dwCharSetUnicode = 1;
	}

	if (!/*m_pSerialBuffer->*/CmpBuffer((BYTE*)m_chPrefix, m_nPrefixLength))
	{
		m_dwVersion = 0;
		return FALSE;
	}

	/*m_pSerialBuffer->*/Offset(m_nPrefixLength);
	/*m_pSerialBuffer->*/DWord(&m_dwVersion);
	long nVersionEndLen = strlen(FILE_VERSION_END);;

	if (m_nVersionCount == 0)
	{
		return TRUE;
	}

	//版本标记结束
	if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)FILE_VERSION_END, nVersionEndLen))
	{
		/*m_pSerialBuffer->*/Offset(nVersionEndLen);
		return TRUE;
	}
	else
	{
	}

	//扩展Version
	long nIndex = 0;
	CBinaryVersion *pVersion = NULL;
	BOOL bIsVersionEnd = FALSE;
	BOOL bVersionFind = FALSE;

	while (!bIsVersionEnd)
	{
		bVersionFind = FALSE;

		for (nIndex=0; nIndex<m_nVersionCount; nIndex++)
		{
			pVersion = &m_oArrBinaryVersion[nIndex];

			if (pVersion->m_dwVersionID == 0)
			{
				break;
			}

			//找到一个匹配的版本标记
			if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)pVersion->m_chPrefix, pVersion->m_nPrefixLength))
			{
				/*m_pSerialBuffer->*/Offset(pVersion->m_nPrefixLength);
				/*m_pSerialBuffer->*/DWord(&pVersion->m_dwVersion);
				bVersionFind = TRUE;
				continue;
			}

			//版本标记结束
			if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)FILE_VERSION_END, nVersionEndLen))
			{
				/*m_pSerialBuffer->*/Offset(nVersionEndLen);
				bIsVersionEnd = TRUE;
				break;
			}
		}

		if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)FILE_VERSION_END, nVersionEndLen))
		{
			/*m_pSerialBuffer->*/Offset(nVersionEndLen);
			bIsVersionEnd = TRUE;
			break;
		}

		if (!bVersionFind)
		{
			break;
		}
	}

	if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)FILE_VERSION_END, nVersionEndLen))
	{
		/*m_pSerialBuffer->*/Offset(nVersionEndLen);
	}

	return TRUE;
}

BOOL CBinarySerialBuffer::AddBinaryVersion(const char *pszPrefix, DWORD dwVersion, DWORD dwVersionID)
{
	CBinaryVersion *pFind = NULL;
	pFind = FindByVersionID(dwVersionID);

	if (pFind != NULL)
	{
		return TRUE;
	}

	ASSERT(FILE_VERSION_MAX_COUNT >= m_nVersionCount);

	if (m_nVersionCount >= FILE_VERSION_MAX_COUNT)
	{
		return FALSE;
	}

	strcpy(m_oArrBinaryVersion[m_nVersionCount].m_chPrefix, pszPrefix);
	m_oArrBinaryVersion[m_nVersionCount].m_dwVersion   = dwVersion;
	m_oArrBinaryVersion[m_nVersionCount].m_dwVersionID = dwVersionID;
	m_oArrBinaryVersion[m_nVersionCount].m_nPrefixLength   = strlen(pszPrefix);
	m_nVersionCount++;

	return TRUE;
}

void CBinarySerialBuffer::SetCharSet(char *pszCharSet)
{
	strcpy(m_chCharSet, pszCharSet);
	m_nCharSetLength = strlen(pszCharSet);

	if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)CHAR_SET_UNICODE, m_nCharSetLength) )
	{
		m_dwCharSetUnicode = 1;
		/*m_pSerialBuffer->*/SetCharSetUnicode();
	}
	else if (/*m_pSerialBuffer->*/CmpBuffer((BYTE*)CHAR_SET_ASCII, m_nCharSetLength) )
	{
		m_dwCharSetUnicode = 0;
		/*m_pSerialBuffer->*/SetCharSetAscii();
	}
	else
	{
		if (memcmp(m_chCharSet, (BYTE*)CHAR_SET_UNICODE, m_nCharSetLength) == 0)
		{
			m_dwCharSetUnicode = 1;
			/*m_pSerialBuffer->*/SetCharSetUnicode();
		}
		else if ( memcmp(m_chCharSet, (BYTE*)CHAR_SET_UNICODE, m_nCharSetLength) == 0 )
		{
			m_dwCharSetUnicode = 0;
			/*m_pSerialBuffer->*/SetCharSetAscii();
		}
	}
}

short CBinarySerialBuffer::GetShort ( )
{
	short val;
	/*m_pSerialBuffer->*/Short(&val);
	return val;
}

void CBinarySerialBuffer::PutShort (short pVal )
{
	/*m_pSerialBuffer->*/Short(pVal);
}

long CBinarySerialBuffer::GetLong ( )
{
    LONG val;
	/*m_pSerialBuffer->*/Long(&val);
	return val;
}

void CBinarySerialBuffer::PutLong (long pVal )
{
	/*m_pSerialBuffer->*/Long(pVal);
}

DWORD CBinarySerialBuffer::GetDWord ( )
{
	DWORD val;
	DWord(&val);
	return val;
}

void CBinarySerialBuffer::PutDWord (DWORD pVal )
{
	DWord(pVal);
}

float CBinarySerialBuffer::GetFloat ( )
{
	float val;
	/*m_pSerialBuffer->*/Float(&val);
	return val;
}

void CBinarySerialBuffer::PutFloat (float pVal )
{
	/*m_pSerialBuffer->*/Float(pVal);
}

double CBinarySerialBuffer::GetDouble ( )
{
	double val;
	/*m_pSerialBuffer->*/Double(&val);
	return val;
}

void CBinarySerialBuffer::PutDouble (double pVal )
{
	/*m_pSerialBuffer->*/Double(pVal);
}

CString CBinarySerialBuffer::GetString ( )
{
	CString val;
	/*m_pSerialBuffer->*/String(&val);
	return val;
}

void CBinarySerialBuffer::GetString ( CString &str )
{
	/*m_pSerialBuffer->*/String(&str);
}

void CBinarySerialBuffer::PutString (const CString &pVal )
{
	/*m_pSerialBuffer->*/String(pVal);
}

#ifndef _PSX_IDE_QT_
CURRENCY CBinarySerialBuffer::GetCurrency ( )
{
	CURRENCY val;
	/*m_pSerialBuffer->*/Currency(&val);
	return val;
}

void CBinarySerialBuffer::PutCurrency (const CURRENCY & pVal )
{
	/*m_pSerialBuffer->*/Currency(pVal);
}
#endif

SYSTEMTIME CBinarySerialBuffer::GetSystemtime ( )
{
	SYSTEMTIME val;
	/*m_pSerialBuffer->*/Systemtime(&val);
	return val;
}

void CBinarySerialBuffer::PutSystemtime (const SYSTEMTIME & pVal )
{
	/*m_pSerialBuffer->*/Systemtime(pVal);
}

short CBinarySerialBuffer::GetByte ( )
{
	BYTE val;
	/*m_pSerialBuffer->*/Byte(&val);
	return val;
}

void CBinarySerialBuffer::PutByte (short pVal )
{
	/*m_pSerialBuffer->*/Byte((BYTE)pVal);
}

// HRESULT CBinarySerialBuffer::AddBufferLength (long nLen )
// {
// 	return /*m_pSerialBuffer->*/AddBufferLength(nLen);
// }
// 
// long CBinarySerialBuffer::SetBufferLength (long nLen )
// {
// 	return /*m_pSerialBuffer->*/SetBufferLength(nLen);
// }
// 
// long CBinarySerialBuffer::AllocBuffer (long lExpandPercent )
// {
// 	return /*m_pSerialBuffer->*/AllocBuffer(lExpandPercent);
// }
// 
// HRESULT CBinarySerialBuffer::ResetBufferPointer ( )
// {
// 	/*m_pSerialBuffer->*/ResetBufferPointer();
// 	return 0;
// }
// 
// HRESULT CBinarySerialBuffer::SetReadMode ( )
// {
// 	/*m_pSerialBuffer->*/SetReadMode();
// 	return 0;
// }
// 
// HRESULT CBinarySerialBuffer::SetWriteMode ( )
// {
// 	/*m_pSerialBuffer->*/SetWriteMode();
// 	return 0;
// }
// 
// HRESULT CBinarySerialBuffer::SetCalSizeMode ( )
// {
// 	/*m_pSerialBuffer->*/SetCalSizeMode();
// 	return 0;
// }
// 
// long CBinarySerialBuffer::IsReadMode ( )
// {
// 	return /*m_pSerialBuffer->*/IsReadMode();
// }
// 
// long CBinarySerialBuffer::IsWriteMode ( )
// {
// 	return /*m_pSerialBuffer->*/IsWriteMode();
// }
// 
// long CBinarySerialBuffer::IsCalSizeMode ( )
// {
// 	return /*m_pSerialBuffer->*/IsCalSizeMode();
// }
// 
// BOOL CBinarySerialBuffer::CreateFile(const CString &strFile)
// {
// 	return /*m_pSerialBuffer->*/CreateFile(strFile);
// }
// 
long CBinarySerialBuffer::SaveToFile (const CString &strFile)
{
	return /*m_pSerialBuffer->*/WriteToFile(strFile);
}

long CBinarySerialBuffer::OpenFromFile (const CString &strFile, long nAddBuf)
{
	return /*m_pSerialBuffer->*/ReadFromFile(strFile, nAddBuf);
}
// void CBinarySerialBuffer::GetBuffer(wchar_t** pBuffer, long *nBufferLen)
// {
// 	/*m_pSerialBuffer->*/GetBuffer(pBuffer,nBufferLen);
// }
// void CBinarySerialBuffer::GetBuffer(char** pBuffer, long *nBufferLen)
// {
// 	/*m_pSerialBuffer->*/GetBuffer(pBuffer,nBufferLen);
// }
// void CBinarySerialBuffer::AttachBuffer(wchar_t *pBuffer, long nBufferLen)
// {
// 	/*m_pSerialBuffer->*/AttachBuffer(pBuffer,nBufferLen);
// }
// void CBinarySerialBuffer::AttachBuffer(char *pBuffer, long nBufferLen)
// {
// 	/*m_pSerialBuffer->*/AttachBuffer(pBuffer,nBufferLen);
// }
// 
// void CBinarySerialBuffer::DettachBuffer()
// {
// 	/*m_pSerialBuffer->*/DettachBuffer();
// }
