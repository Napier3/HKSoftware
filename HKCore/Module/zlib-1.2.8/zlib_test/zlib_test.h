
// zlib_test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Czlib_testApp:
// �йش����ʵ�֣������ zlib_test.cpp
//

class Czlib_testApp : public CWinAppEx
{
public:
	Czlib_testApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Czlib_testApp theApp;