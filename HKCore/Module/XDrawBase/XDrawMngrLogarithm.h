//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawMngrLogarithm.h  CXDrawMngrLogarithm

#pragma once

#include "XDrawMngr.h"
#include "../../Module/Axis/LogarithmAxis.h"

class CXDrawMngrLogarithm : public CXDrawMngr
{
public:
	CXDrawMngrLogarithm();
	virtual ~CXDrawMngrLogarithm();

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWMNGRLOGARITHM;   }

protected:
	CLogarithmAxis m_oAxis;

public:
	virtual void InitAxis();
	virtual void AdjustAxis(BOOL bUseMngrAxisRange);
	virtual void ResetAxis();
	virtual void SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void GetAxisInterface(CAxisInterface **ppAxisInterface);

	virtual void DevicePointToLogicPoint(const CPoint &point, double &dX, double &dY)
	{
		m_oAxis.DevicePointToLogicPoint(point, &dX, &dY, 0);
	}

	virtual void DevicePointToLogicPoint(const CPoint &point, double *dX, double *dY)
	{
		m_oAxis.DevicePointToLogicPoint(point, dX, dY, 0);
	}

	virtual void DrawAxis(CDC *pDC);

public:
	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
	void SetAxisMaxUnitCount(long nXAxisUnitCount, long nYAxisUnitCount);
	void SetAxisXYUnitLock(BOOL bUnLock);
};

//zhouhj 2023.7.13  ��Ϊ�������䷽ʽ,���ڵ���ϵ����ʾ�̶�ֵ
extern float g_fLogarithmMinXCoef/* = 0.5f*/;
extern float g_fLogarithmMaxXCoef/* = 1.1f*/;
extern float g_fLogarithmMinYCoef/* = 0.5f*/;
extern float g_fLogarithmMaxYCoef/* = 1.1f*/;

