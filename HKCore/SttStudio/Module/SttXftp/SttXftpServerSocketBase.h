#pragma once

#include "../SttSocket/SttServerSocketDataBase.h"

class CSttXftpServerSocketBase : public CSttServerSocketDataBase
{
public:
	CSttXftpServerSocketBase();
	virtual ~CSttXftpServerSocketBase();

	static BOOL g_bUseRelRootPath;	//相对路径标志

	void Set_DEFAULT_HOME_DIR(char *pszRootPath)	{	strcpy(DEFAULT_HOME_DIR, pszRootPath);	}
	char* Get_DEFAULT_HOME_DIR()		{	return DEFAULT_HOME_DIR;	}

protected:
	char FTP_USER[MAX_PATH];
	char FTP_PASS[MAX_PATH];
	char DEFAULT_HOME_DIR[MAX_PATH];

public:
	
};

