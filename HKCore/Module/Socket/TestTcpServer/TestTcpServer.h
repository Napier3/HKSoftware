
// TestTcpServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestTcpServerApp:
// �йش����ʵ�֣������ TestTcpServer.cpp
//

class CTestTcpServerApp : public CWinAppEx
{
public:
	CTestTcpServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestTcpServerApp theApp;