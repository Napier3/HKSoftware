//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WndAdjCol.h  CWndAdjCol

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"

#include "WndAdjCellList.h"


class CWndAdjCol : public CWndAdjCellList
{
public:
	CWndAdjCol();
	virtual ~CWndAdjCol();


//���غ���
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJCOL;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

