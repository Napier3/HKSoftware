//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageMngr.h"

class CXLangMenu : public CMenu
{
public:
	CXLangMenu();

	virtual ~CXLangMenu();

//���غ���
public:
	BOOL LoadMenu(UINT nIDResource);


//˽�г�Ա����
private:
	void InitMenuXLang(CMenu *pMenu, long &nNewXLangStrCount);

//˽�г�Ա�������ʷ���
public:
};

