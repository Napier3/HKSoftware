//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawLine.h  CXDrawLine_Ex

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawLine_Ex : public CXDrawBase, public CXDrawData_Line_Ex
{
public:
	CXDrawLine_Ex();
	CXDrawLine_Ex(double *xb, double *yb, double *xe, double *ye);
	virtual ~CXDrawLine_Ex();

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWLINE_EX;   }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual void SetBeginPoint(double *x, double *y)		{	CXDrawData_Line_Ex::SetBeginPoint(x, y);	};
	virtual void SetEndPoint(double *x, double *y)		{	CXDrawData_Line_Ex::SetEndPoint(x, y);	};
	virtual void SetBeginPoint(double x, double y)	{	ASSERT (FALSE);	}
	virtual void SetEndPoint(double x, double y)	{	ASSERT (FALSE);	}

//˽�г�Ա����
private:
	/////////��ͼ�ж�Ӧ�ĵ�����
	CPoint	m_pointBegin;
	CPoint	m_pointEnd;

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};
