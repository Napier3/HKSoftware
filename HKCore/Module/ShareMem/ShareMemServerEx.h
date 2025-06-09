// ShareMemServerEx.h: interface for the CShareMemServerEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SHAREMEMSERVEREX_H__)
#define _SHAREMEMSERVEREX_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShareMemServerEx  
{
public:
	virtual ~CShareMemServerEx();
	CShareMemServerEx();
	CShareMemServerEx(const CString &szFileName, const CString &szMapName, DWORD dwSizeHigh, DWORD dwSizeLow);
	CShareMemServerEx(const CString &szFileName, const CString &szMapName, volatile __int64 n64Size);

	void CreateShareMem(const CString &szFileName, const CString &szMapName, DWORD dwSizeHigh, DWORD dwSizeLow);
	void CreateShareMem(const CString &szFileName, const CString &szMapName, volatile __int64 n64Size);
	void DestoryShareMem()	{	_Destory();		}
	void FlushViewFile();

protected:
	HANDLE	m_hFile;
	HANDLE	m_hFileMap;
	LPVOID	m_lpFileMapBuffer;
	CString m_strFileName;
	CString m_strMapName;
	volatile __int64	m_n64Size;
	DWORD   m_dwSize;
	BOOL	m_bCreateFlag;

private:
	void _Init();
	void _Destory();
	
	void Create(const CString &szFileName, const CString &szMapName, DWORD dwSizeHigh, DWORD dwSizeLow);
	void Create(const CString &szFileName, const CString &szMapName, volatile __int64 n64Size);

public:
	LPVOID MapView(DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow,DWORD dwNumberOfBytesToMap);
	LPVOID MapView(volatile __int64 n64Offset,DWORD dwNumberOfBytesToMap);
	void ResetBuffer(unsigned char ucData,long nLen = -1);
	LPVOID GetBuffer()    {     return m_lpFileMapBuffer;    }
	DWORD GetSize()       {     return m_dwSize;             }
	BOOL IsValid()        {     return m_hFileMap != NULL && m_bCreateFlag;      }
	__int64 GetFileSize()	{	return m_n64Size;	}
};

#endif // !defined(_SHAREMEMSERVEREX_H__)
