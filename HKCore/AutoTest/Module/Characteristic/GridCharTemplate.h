//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GridCharTemplate.h  CGridCharTemplate

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARTEMPLATE_COL_INDEX        0
#define CHARTEMPLATE_COL_NAME         1
#define CHARTEMPLATE_COL_ID           2
#define CHARTEMPLATE_COL_AXIS         3


#define CHARTEMPLATE_COLS             4


class CGridCharTemplate : public CExBaseListGrid
{
public:
	CGridCharTemplate();
	virtual ~CGridCharTemplate();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//���غ���
public: 
	
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

};

