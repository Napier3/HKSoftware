//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawMngrDescartes.h  CXDrawMngrDescartes

#pragma once

#include "XDrawMngr.h"
#include "../../Module/Axis/DescartesAxis.h"

class CXDrawMngrDescartes : public CXDrawMngr
{
public:
	CXDrawMngrDescartes();
	virtual ~CXDrawMngrDescartes();

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWMNGRDESCARTES;   }

protected:
	CDescartesAxis m_oAxis;

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

	long GetDrawsCount();//zhouhj 20210203 ��ȡ������������
};

