//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"
#include "XScdDrawLineBase.h"


class CXScdDrawIedBase : public CXDrawElements
{
public:
	CXScdDrawIedBase();
	virtual ~CXScdDrawIedBase();

//���غ���
public:
 	virtual void AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow);

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

	virtual void GetAllLines(CXDrawElements &oScdLines);
	virtual void CreateCtrlLines();
	virtual void OnOnlyShowUsedChsChanged(CXScdDrawLines *pLines);
	virtual void RemoveErrorLines();

};

