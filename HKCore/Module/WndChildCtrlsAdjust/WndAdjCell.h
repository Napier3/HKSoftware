//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WndAdjCell.h  CWndAdjCell

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"



class CWndAdjCell : public CBaseObject
{
public:
	CWndAdjCell();
	virtual ~CWndAdjCell();


	long  m_nFixedWidth;
	long  m_nFixedHeight;
	long  m_nOriginLeft;
	long  m_nOriginTop;
	long  m_nOriginWidth;
	long  m_nOriginHeight;
//���غ���
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJCELL;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

