//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageMngr.h"

//////////////////////////////////////////////////////////////////////////
//CXLangMenuBar
class CXLangMenuBar : public CMFCMenuBar
{
public:
	CXLangMenuBar();

	virtual ~CXLangMenuBar();

//���غ���
public:
	virtual void CreateFromMenu(HMENU hMenu, BOOL bDefaultMenu = FALSE, BOOL bForceUpdate = FALSE);
	static long g_nMenuRootIndex;

//˽�г�Ա����
private:
	void InitXLangByButton(CMFCToolBarMenuButton *pMenuButton);
	void InitXLangText(CMFCToolBarMenuButton *pButton);

//˽�г�Ա�������ʷ���
public:
	void InitXLangButtons();
};

