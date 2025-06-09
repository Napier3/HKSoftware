// ShareMemServer.h: interface for the CShareMemServer class.
//
//////////////////////////////////////////////////////////////////////
//李俊庆	2004年1月9日

#if !defined(_SHAREMEMSERVER_H__)
#define _SHAREMEMSERVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShareMemServer  
{
public:
	virtual ~CShareMemServer();
	CShareMemServer(const char *szFileName, const char *szMapName, DWORD dwSize);

private:
	CShareMemServer()
	{
		_Init();
	}

protected:
	HANDLE	m_hFile;
	HANDLE	m_hFileMap;
	LPVOID	m_lpFileMapBuffer;
	char	*m_pFileName;
	char	*m_pMapName;
	DWORD	m_dwSize;
	BOOL	m_bCreateFlag;

private:
	void _Init();
	void _Destory();

public:
	void Create(const char *szFileName, const char *szMapName, DWORD dwSize);
	LPVOID GetBuffer();
	DWORD GetSize();
	void ResetBuffer(unsigned char ucData,DWORD nLen = 0);
	BOOL IsValid()   {   return m_bCreateFlag;   }
};

#endif // !defined(_SHAREMEMSERVER_H__)
