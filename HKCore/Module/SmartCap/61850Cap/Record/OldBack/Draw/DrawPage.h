// DrawPage.h: interface for the CDrawPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPAGE_H__BD499107_D201_4617_9C3B_F8F51419DAC6__INCLUDED_)
#define AFX_DRAWPAGE_H__BD499107_D201_4617_9C3B_F8F51419DAC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mr1200RecordDrawBase.h"

class CDrawPage : public CDrawMr1200RecordBase  
{
public:
	void GetDrawVariables(CDrawBaseObjectList& oList);//��DrawPage�л�û�ͼͨ��
	void SetDrawVariables(CDrawBaseObjectList& oList);//���ø���Page�Ļ�ͼ����
public:
	CDrawPage();
	virtual ~CDrawPage();
};

#endif // !defined(AFX_DRAWPAGE_H__BD499107_D201_4617_9C3B_F8F51419DAC6__INCLUDED_)
