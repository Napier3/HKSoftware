
// TestTcpClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestTcpClientApp:
// �йش����ʵ�֣������ TestTcpClient.cpp
//

class CTestTcpClientApp : public CWinAppEx
{
public:
	CTestTcpClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestTcpClientApp theApp;