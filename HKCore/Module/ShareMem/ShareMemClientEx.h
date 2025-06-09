// ShareMemClientEx.h: interface for the CShareMemClientEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SHAREMEMCLIENTEX_H__)
#define _SHAREMEMCLIENT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BaseClass/SerializeBufferBase.h"

class CShareMemClientEx  : public CSerializeBufferBase
{
public:
	virtual ~CShareMemClientEx();
	CShareMemClientEx(DWORD dwAccess, const CString &szMapName);

private:
	CShareMemClientEx()
	{
		_Init();
	}

protected:
	HANDLE  m_hFileMap;
	CString    m_strMapName;
	BOOL    m_bOpen;
	DWORD   m_dwSize;
	DWORD   m_dwAccess;
	volatile __int64 m_n64MapBeginPos;

private:
	void _Init();
	void _Destory();
	void Open(DWORD dwAccess, const CString &szMapName);

public:
	BOOL   ReOpen();
	void   Close();
	void UnMapView();
	LPVOID MapView(DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow,DWORD dwNumberOfBytesToMap);
	LPVOID MapView(volatile __int64 n64Offset,DWORD dwNumberOfBytesToMap);
	void   FlushView()    {     FlushViewOfFile(m_pchData, m_dwSize);                }
	void   FlushView(LPVOID pBuffer, DWORD dwSize)    {     FlushViewOfFile(pBuffer, dwSize);                }
	LPVOID GetBuffer()    {     return m_pchData;    }
	DWORD GetSize()       {     return m_dwSize;             }
	BOOL IsValid()        {     return m_hFileMap != NULL && m_pchData != NULL;      }
	LPVOID GetCurrPos()   {     return m_lpBufCur;                                          }
	void ReSetCurrPos()	  {		m_lpBufCur = NULL;    }
	LPVOID LocatePos(DWORD dwOffSet);
	BOOL CanWriteLen(DWORD dwLen)    {     return (m_lpBufCur + dwLen < m_lpBufMax);  }
	DWORD GetWriteLen()	{	return (m_lpBufCur - m_pchData);	}
	volatile __int64 GetMapOffset()	{	return m_n64MapBeginPos;	}
	volatile __int64 GetCurr64Pos();
	volatile __int64 SetCurr64Pos(volatile __int64 n64Pos);
	LPVOID Read(__int64 n64BeginPos, DWORD dwLength);
};

#endif // !defined(_SHAREMEMCLIENTEX_H__)
