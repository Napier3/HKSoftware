
// TestGridVs2008.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestGridVs2008App:
// �йش����ʵ�֣������ TestGridVs2008.cpp
//

class CTestGridVs2008App : public CWinAppEx
{
public:
	CTestGridVs2008App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestGridVs2008App theApp;