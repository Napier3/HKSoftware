//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ServerUser.h  CServerUserListCtrl

#pragma once

#include "..\BaseClass\ExBaseListListCtrl.h"



class CServerUserListCtrl : public CExBaseListListCtrl
{
public:
	CServerUserListCtrl();
	virtual ~CServerUserListCtrl();

	virtual void InitCollumns();

//���غ���
public:
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);
	virtual void UpdateListCtrl(CExBaseObject *pObj);


//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

