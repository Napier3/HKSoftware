// ShareMemClient.h: interface for the CShareMemClient class.
//
//////////////////////////////////////////////////////////////////////
//���	2004��1��9��

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
	HANDLE	m_hFileMap;//�ڴ�ӳ����ļ����
	LPVOID	m_lpFileMapBuffer;//�ļ�ӳ��Ļ����׵�ַ
	char	*m_pMapName;
	int		m_iOpenFlag;//�����ļ��򿪵ı�ʶ

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
