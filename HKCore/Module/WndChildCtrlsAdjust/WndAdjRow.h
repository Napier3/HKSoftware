//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WndAdjRow.h  CWndAdjRow

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"

#include "WndAdjCellList.h"


class CWndAdjRow : public CWndAdjCellList
{
public:
	CWndAdjRow();
	virtual ~CWndAdjRow();


//���غ���
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJROW;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

