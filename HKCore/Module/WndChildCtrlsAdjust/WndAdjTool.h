//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WndAdjTool.h  CWndAdjTool

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"

#include "WndAdjCellList.h"


class CWndAdjTool : public CWndAdjCellList
{
public:
	CWndAdjTool();
	virtual ~CWndAdjTool();


//���غ���
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJTOOL;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

