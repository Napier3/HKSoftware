// EpGlobalApi.h
//////////////////////////////////////////////////////////////////////

#if !defined(_EPGLOBALAPI_H__)
#define _EPGLOBALAPI_H__


inline BOOL Ep_InitWinSocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1);

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return FALSE;
	}

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return FALSE;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return FALSE; 
	}

	return TRUE;

}

inline DWORD Ep_CalSum(BYTE *pBuffer, long nLen)
{
	BYTE *pEnd = pBuffer + nLen;
	DWORD dwSum = 0;

	while (pBuffer < pEnd)
	{
		dwSum += *pBuffer;
		pBuffer++;
	}

	return dwSum;
}

inline BYTE Ep_AsciiToHex(BYTE byteValue)
{
	if ('0' <= byteValue && byteValue <= '9')
	{
		return byteValue - '0';
	}

	if ('a' <= byteValue && byteValue <= 'f')
	{
		return byteValue - 'a';
	}

	if ('A' <= byteValue && byteValue <= 'F')
	{
		return byteValue - 'A';
	}

	return 0;
}


inline BYTE Ep_HexToAscii(BYTE byteValue)
{
	if (0 <= byteValue && byteValue <= 9)
	{
		return byteValue + '0';
	}

	if (10 <= byteValue && byteValue <= 15)
	{
		return byteValue + 'A';
	}

	return '0';
}

inline BYTE Ep_LRC(const BYTE *pBuffer, long nLen)//获得校验码
{
	BYTE byLrc = 0;
	BYTE byteData = 0;
	const BYTE *pEnd = pBuffer + nLen;
	const BYTE *pCurr = pBuffer;

	while(pCurr < pEnd)
	{
		//每两个需要发送的ASCII码转化为一个十六进制数
		byteData = (*pCurr) * 16 + *(pCurr+1);
		pCurr += 2;
		byLrc += byteData;
	}

	byLrc = ~ byLrc;
	byLrc ++;

	return byLrc;
}

inline WORD Ep_CRC(const BYTE *pBuffer, long nLen)//获得校验码
{
	WORD wCrc = WORD(0xFFFF);
	const BYTE *pEnd = pBuffer + nLen;
	const BYTE *pCurr = pBuffer;

	while(pCurr < pEnd)
	{
		wCrc ^= WORD(*pCurr);

		for(int j=0; j<8; j++)
		{
			if(wCrc & 1)
			{
				wCrc >>= 1;
				wCrc ^= 0xA001;
			}
			else
			{
				wCrc >>= 1;
			}
		}

		pCurr++;
	}

	return wCrc;
}

#endif // !defined(_EPGLOBALAPI_H__)
