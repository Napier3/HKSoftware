// AxisInterface.h: interface for the AxisInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_AXISINTERFACE_H__)
#define _AXISINTERFACE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef USE_AXIS_CONFIG
#include "../DataMngr/DataGroup.h"
#else
#include "../BaseClass/TLinkList.h"
#endif

#include "../OSInterface/OSInterface.h"

#define SCCALE_TYPE_HALF     1
#define SCCALE_TYPE_TENTH    0

#define AXIS_TYPE_NORMAL     0
#define AXIS_TYPE_TIME       1
#define AXIS_CAL_MIN_VALUE   0.000000001

#define AXIS_TYPE_ID_CARTES     _T("cartes")
#define AXIS_TYPE_ID_POLAR      _T("polar")
#define AXIS_TYPE_ID_LOGARITHM  _T("logarithm")
#define AXIS_TYPE_INDEX_CARTES     0
#define AXIS_TYPE_INDEX_POLAR      1
#define AXIS_TYPE_INDEX_LOGARITHM  2

#ifdef USE_AXIS_CONFIG  //zhouhj 20211026 用于设置坐标轴属性
#define AXIS_CONFIG_ID_WorkAreaBkColor                       _T("WorkAreaBkColor")
#define AXIS_CONFIG_ID_XAxisGridLineColor                    _T("XAxisGridLineColor")
#define AXIS_CONFIG_ID_YAxisGridLineColor                    _T("YAxisGridLineColor")
#define AXIS_CONFIG_ID_AxisCenterLineWidth                   _T("AxisCenterLineWidth")
#define AXIS_CONFIG_ID_AxisCenterColor                       _T("AxisCenterColor")

#define AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom            _T("XAxisWorkAreaBackColorFrom")
#define AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom            _T("YAxisWorkAreaBackColorFrom")
#define AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo              _T("XAxisWorkAreaBackColorTo")
#define AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo              _T("YAxisWorkAreaBackColorTo")

#define AXIS_CONFIG_ID_AxisScaleFont                        _T("AxisScaleFont")
#define AXIS_CONFIG_ID_AxisNameFont                         _T("AxisNameFont")

#define AXIS_CONFIG_ID_AxisTopGap                           _T("AxisTopGap")


#endif

class CAxisInterface 
{
public:
	virtual void LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex=0) = 0;
	virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0) = 0;
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex) = 0;
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex) = 0;
    virtual void GetAxisDrawArea(CRect &rcArea) = 0;
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax) =  0;
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 增加用于设置坐标轴名称等
	virtual CRect GetWorkArea() =  0;
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig) = 0;
	virtual void GetAxisConfig(CDataGroup *pAxisConfig) = 0;
#endif

    virtual void LogicPointToDevicePoint(double fVal, int *nVal, long nAxisIndex)
    {
        long val = 0;
        LogicPointToDevicePoint(fVal, &val, nAxisIndex);
        *nVal = val;
    }

};



class CAxisScaleData
{
public:
	double m_dAxisScaleVal;
	CPoint m_ptAxisScale;
	
	CAxisScaleData();
	~CAxisScaleData();
	void FillIt(double dVal, CPoint &point);
    void FillIt(double dVal, const CPoint &point);
    void FillIt(double dVal, long x, long y);

	CAxisScaleData* Clone()
	{
		CAxisScaleData *pNew = new CAxisScaleData();
		pNew->m_dAxisScaleVal = m_dAxisScaleVal;
		pNew->m_ptAxisScale = m_ptAxisScale;
		return pNew;
	}
};

typedef CTLinkList<CAxisScaleData> CAxisScaleDataList;

long FloatValToInt(double dVal, bool bCarry = true);
// void  _ChopFloatString(CString &strValue, long nDecimal = -1);
char* _ChopFloatString(char* pszBuffer, long nDecimal = -1);
char* _ChopFloatString(double dValue, char* pszBuffer, long nDecimal = -1);
void _ChopFloatString(CString &strBuffer, long nDecimal = -1);


UINT axis_GetAxisIndex(const CString &strAxisID);
CString axis_GetAxisID(UINT nAxisIndex);


#endif // !defined(_AXISINTERFACE_H__)
