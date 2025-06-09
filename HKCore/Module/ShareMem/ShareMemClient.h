// ShareMemClient.h: interface for the CShareMemClient class.
//
//////////////////////////////////////////////////////////////////////
//李俊庆	2004年1月9日

#if !defined(_SHAREMEMCLIENT_H__)
#define _SHAREMEMCLIENT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShareMemClient  
{
public:
	virtual ~CShareMemClient();
	CShareMemClient(DWORD dwAccess, const char *szMapName);

private:
	CShareMemClient()
	{
		_Init();
	}

protected:
	HANDLE	m_hFileMap;//内存映射的文件句柄
	LPVOID	m_lpFileMapBuffer;//文件映射的缓存首地址
	char	*m_pMapName;
	int		m_iOpenFlag;//共享文件打开的标识

private:
	void _Init();
	void _Destory();

public:
	void Open(DWORD dwAccess, const char *szMapName);
	LPVOID GetBuffer();
	DWORD GetSize();
	BOOL IsValid()   {   return m_hFileMap != NULL && m_lpFileMapBuffer != NULL;   }
};

#endif // !defined(_SHAREMEMCLIENT_H__)
