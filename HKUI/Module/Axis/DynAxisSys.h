#if !defined(_DYNAXISSYS_H_)
#define _DYNAXISSYS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DynAxisSys.h : header file

#include "RulerLogAxis.h"
#include "RulerAxis.h"

/////////////////////////////////////////////////////////////////////////////
// CDynAxisSys command target

#define RULER_TYPE_DESCARTES   1
#define RULER_TYPE_LOG         2

#define RULER_TYPE_ID_DESCARTES   "DESCARTES"
#define RULER_TYPE_ID_LOG                "LOG"


#define RULER_ID_X   1
#define RULER_ID_Y   2

#define DYN_AREA				0x0001


#define DYN_ALL				    0x07fffffff
#define DYN_XAXIS				0x0002
#define DYN_XAXIS_LINE			0x00010000
#define DYN_XAXIS_TEXT			0x00020000
#define DYN_XAXIS_SAWTOOTH1	    0x00040000
#define DYN_XAXIS_SAWTOOTH2	    0x00080000
#define DYN_XAXIS_ALL			0x000F0002

#define DYN_YAXIS				0x0004
#define DYN_YAXIS_LINE			0x00100000
#define DYN_YAXIS_TEXT			0x00200000
#define DYN_YAXIS_SAWTOOTH1	    0x00400000
#define DYN_YAXIS_SAWTOOTH2	    0x00800000
#define DYN_YAXIS_ALL			0x00F00004

#define DYN_BACK				0x0008
#define DYN_AXISCENTER			0X00000100


class CDynAxis : public CAxisInterface
{
public:
    CDynAxis();
    virtual ~CDynAxis();

public://CAxisInterface
    virtual void LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex=0);
    virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0) ;
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex);
    virtual void GetAxisDrawArea(CRect &rcArea);
    virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
    virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
    virtual CRect GetWorkArea() ;
    virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

	//lijunqing 2024-6-20
	virtual void LogicPointToDevicePoint(double *pfBuff, CPoint *pPointBuf, long nDatasCount, long nAxisIndex);


private:
    long m_nAxisID;  //X or Y
    long m_nAxisType;  //Ruler or RulerLog

    CRulerLogAxis *m_pRulerLog;
    CRulerAxis *m_pRuler;

    double m_fAxisMin, m_fAxisMax;
public:
    void SetAxisID_X();
    void SetAxisID_Y();

    void SetAxisType_Ruler();
    void SetAxisType_RulerLog();
    void SetAxisType(long nAxisType);

    void SetBorder(CRect &rcBorder);

    void DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset);
	CAxisScaleDataList* GetAxisScaleDataList();

public://属性参数设置函数
	void SetAxisBKColor(COLORREF cr);
	void SetAxisSize(long nSize);
};

class CDynAxisSys : public CAxisInterface
{
public:
	CDynAxisSys();           // protected constructor used by dynamic creation
	virtual ~CDynAxisSys();

    CDynAxis m_oAxisX;
    CDynAxis m_oAxisY;

    CRect m_rcBoder;
	CRect m_rcWorkArea;

	//属性参数
	COLORREF	m_crAxisGrid;				//坐标的网格		
	COLORREF	m_crAxisCenter;				//坐标的中心轴颜色
	COLORREF	m_crAxisBK;					//坐标的背景
	COLORREF	m_crViewBK;					//视图底色
	long        m_nAxisGridStyle;

	long        m_nYAxisWidth, m_nXAxisHeight;

	unsigned long  m_nDrawStyle;

// Operations
public://CAxisInterface
	virtual void LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex=0);	//将逻辑坐标转化为实际坐标
	virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);//从实际坐标获取实际坐标所代表的值
	virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex=0);
	virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex=0);
	virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 增加用于设置坐标轴名称等
    virtual CRect GetWorkArea();
    virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

public:
    void SetAxisType_X(const CString &strAxisType);
    void SetAxisType_Y(const CString &strAxisType);
    void SetAxisType_X_Descartes();
    void SetAxisType_Y_Descartes();
    void SetAxisType_X_Log();
    void SetAxisType_Y_Log();

    void SetBorder(CRect &rcBorder);
    void DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset);

protected:
    void ValidateBoder();
	void DrawXAxisLine(CDC *pDC,float fZoomRatio,long xOffset,long yOffset);
	void DrawYAxisLine(CDC *pDC,float fZoomRatio,long xOffset,long yOffset);
	void DrawRulerBack(CDC *pDC);
};

inline char* axis_GetRulerAxisTypeID(long nAxisType)
{
    if (nAxisType == RULER_TYPE_DESCARTES)
    {
        return RULER_TYPE_ID_DESCARTES;
    }
    else
    {
        return RULER_TYPE_ID_LOG;
    }
}

inline long axis_GetRulerAxisTypeByID(char *pszAxisType)
{
    if ( stricmp(pszAxisType, RULER_TYPE_ID_DESCARTES) == 0)
    {
        return RULER_TYPE_DESCARTES;
    }
    else
    {
        return RULER_TYPE_LOG;
    }
}

inline long axis_GetRulerAxisTypeByID(const CString &strAxisType)
{
    if ( strAxisType == RULER_TYPE_ID_DESCARTES)
    {
        return RULER_TYPE_DESCARTES;
    }
    else
    {
        return RULER_TYPE_LOG;
    }
}

#endif // !defined(_DYNAXISSYS_H_)
