#if !defined(_BINARYTEXTCONVERT_H__)
#define _BINARYTEXTCONVERT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferBase.h"



class CBinaryTextConvert  
{
public:
	CBinaryTextConvert();
	virtual ~CBinaryTextConvert();

	void SetText(const char *strText);
	void SetText(const CString &strText);
	
	void SetBinary(BYTE *pBuffer, long nLength);
	
	BOOL GetString(CString &strText);
	BOOL GetString(char *pString, long &nLength);
	BOOL GetString(char **ppString, long &nLength);

	BOOL GetBinary(BYTE *pBuffer, long &nLength);
	BOOL GetBinary(BYTE **ppBuffer, long &nLength);
	BOOL GetBinaryRef(BYTE **ppBuffer, long &nLength);

	BOOL ConvertBinaryToText();
	BOOL ConvertTextToBinary(BOOL bHasSpaceGap=TRUE);

	void SetHexMode()		{	m_nMode = MODE_HEX;		}
	void SetOctalMode()	{	m_nMode = MODE_OCTAL;	}

public:
	static const char g_tabHexCharacters[16];

	static BOOL IsCharHex(BYTE ch)
	{
		return ( ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F') );
	}

	static BOOL IsCharOctal(BYTE ch)
	{
		return ( ('0' <= ch && ch <= '7') );
	}

	static BYTE CharToBinary_Hex(BYTE ch)
	{
		if ('0' <= ch && ch <= '9')
		{
			return ch - '0';
		}
		else if ('a' <= ch && ch <= 'f')
		{
			return ch - 'a';
		}
		else if ('A' <= ch && ch <= 'F')
		{
			return ch - 'A';
		}
		else
		{
			return 0;
		}
	}

	static BYTE CharToValue_Hex(BYTE ch)
	{
		if ('0' <= ch && ch <= '9')
		{
			return ch - '0';
		}
		else if ('a' <= ch && ch <= 'f')
		{
			return ch - 'a' + 10;
		}
		else if ('A' <= ch && ch <= 'F')
		{
			return ch - 'A' + 10;
		}
		else
		{
			return 0;
		}
	}

	static BYTE ValueToChar_Hex(BYTE ch)
	{
		ASSERT (0 <= ch && ch <= 15);
		return g_tabHexCharacters[ch];
	}

	static BYTE CharToValue(BYTE chH, BYTE chL)
	{
		return CharToValue_Hex(chH) * 16 + CharToValue_Hex(chL);
	}

	static void ValueToString_Hex(BYTE ch, BYTE *pBuffer)
	{
		*pBuffer = g_tabHexCharacters[ (ch & 0xF0) >> 4];
		*(pBuffer+1) =  g_tabHexCharacters[ (ch & 0x0F)];
		*(pBuffer+2) =  VK_SPACE;
	}

	static BOOL StringToValue_Hex(BYTE *pBuffer, BYTE &ch, BOOL bHasSpaceGap=TRUE)
	{
		BYTE ch1 = *pBuffer;
		BYTE ch2 = *(pBuffer+1);
		BYTE ch3 = *(pBuffer+2);

		if (bHasSpaceGap)
		{
			if (! IsSpace(ch3) )
			{
				return FALSE;
			}
		}

		if ( IsCharHex(ch1) && IsCharHex(ch2) )
		{
			ch = CharToValue_Hex(ch1);
			ch = ch << 4;
			ch = ch + CharToValue_Hex(ch2);
			return TRUE;
		}
		else
		{
			ch = 0;
			return FALSE;
		}
	}

	static BOOL IsSpace(BYTE ch)
	{
		return (ch == '\r' || ch == '\n' || ch == VK_SPACE);
	}

protected:
	CBufferBase m_oBufferBinary;
	CBufferBase m_oBufferText;

	enum SerializeBufferBaseMode
	{
		MODE_HEX,
		MODE_OCTAL,
		MODE_BINARY,
		MODE_DCIMAL
	};

	UINT m_nMode;
	BYTE* GetNextChar(BYTE *pCurr, BYTE *pEnd, BOOL bHasSpaceGap);
};

#endif // !defined(_BINARYTEXTCONVERT_H__)
