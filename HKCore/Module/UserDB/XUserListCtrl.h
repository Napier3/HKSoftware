//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StationTest.h  CXUserListCtrl

#pragma once

#include "..\..\Module\BaseClass\ExBaseListListCtrl.h"

#define XUSER_COL_INDEX      0
#define XUSER_COL_NAME       1
#define XUSER_COL_ID         2
#define XUSER_COL_CURRTOOL   3



class CXUserListCtrl : public CExBaseListListCtrl
{
public:
	CXUserListCtrl();
	virtual ~CXUserListCtrl();

	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);
	
//���غ���
public:


//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

