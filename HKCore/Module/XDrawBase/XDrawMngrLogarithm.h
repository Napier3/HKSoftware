//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawMngrLogarithm.h  CXDrawMngrLogarithm

#pragma once

#include "XDrawMngr.h"
#include "../../Module/Axis/LogarithmAxis.h"

class CXDrawMngrLogarithm : public CXDrawMngr
{
public:
	CXDrawMngrLogarithm();
	virtual ~CXDrawMngrLogarithm();

//重载函数
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

//zhouhj 2023.7.13  改为参数可配方式,便于调整系数显示刻度值
extern float g_fLogarithmMinXCoef/* = 0.5f*/;
extern float g_fLogarithmMaxXCoef/* = 1.1f*/;
extern float g_fLogarithmMinYCoef/* = 0.5f*/;
extern float g_fLogarithmMaxYCoef/* = 1.1f*/;

