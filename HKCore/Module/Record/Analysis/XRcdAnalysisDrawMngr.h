// XRcdAnalysisDrawMngr.h: interface for the CXRcdAnalysisDrawMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdAnalysisDrawMngr_H__)
#define _XRcdAnalysisDrawMngr_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../XDrawBase/XDrawMngr.h"

class CXRcdAnalysisDrawMngr : public CXDrawMngr
{
public:
	CXRcdAnalysisDrawMngr();
	virtual ~CXRcdAnalysisDrawMngr();

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	virtual void InitAxis();
	virtual void AdjustAxis(BOOL bUseMngrAxisRange);
	virtual void ResetAxis();
	virtual void SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void GetAxisInterface(CAxisInterface **ppAxisInterface);

	virtual void DevicePointToLogicPoint(const CPoint &point, double &dX, double &dY);
	virtual void DevicePointToLogicPoint(const CPoint &point, double *dX, double *dY);
	virtual void DrawAxis(CDC *pDC);

};

#endif // !defined(_XRcdAnalysisDrawMngr_H__)
