
// TestEan13.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestEan13App:
// �йش����ʵ�֣������ TestEan13.cpp
//

class CTestEan13App : public CWinAppEx
{
public:
	CTestEan13App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestEan13App theApp;