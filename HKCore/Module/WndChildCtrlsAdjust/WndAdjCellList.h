//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WndAdjCellList.h  CWndAdjCellList

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"

#include "WndAdjCell.h"


class CWndAdjCellList : public CWndAdjCell
{
public:
	CWndAdjCellList();
	virtual ~CWndAdjCellList();


//���غ���
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJCELLLIST;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CWndAdjCell* CreateCell(CWnd *pWnd, BOOL bFixedWidth, BOOL bFixedHeight);
};

