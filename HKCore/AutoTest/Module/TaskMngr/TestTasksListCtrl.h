//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestTasksListCtrl.h  CTestTasksListCtrl

#pragma once

#include "..\..\..\Module\BaseClass\ExBaseListListCtrl.h"
#include "TestTask.h"



class CTestTasksListCtrl : public CExBaseListListCtrl
{
public:
	CTestTasksListCtrl();
	virtual ~CTestTasksListCtrl();

	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

	//���غ���
public: 


	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

