//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageMngr.h"

class CXLangToolBar : public CMFCToolBar
{
public:
	CXLangToolBar();

	virtual ~CXLangToolBar();

//���غ���
public:
	virtual void AdjustLocations();
	void UpdateTooltipsEx();


//˽�г�Ա����
private:
	CString m_strToolTipTxt;

//˽�г�Ա�������ʷ���
public:
};

