// PowerDrawGrpahList.h: interface for the CPowerDrawGrpahList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWGRPAHLIST_H__14D10736_7470_11D5_A3F9_00E04CE17719__INCLUDED_)
#define AFX_POWERDRAWGRPAHLIST_H__14D10736_7470_11D5_A3F9_00E04CE17719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDBaseObject.h"
#include "PowerDrawBaseClass.h"

class CPowerDrawGrpahList : public CPDBaseObject
{
public:
	CPDBaseObjectList odDrawGrpahList;
	CPowerDrawGrpahList();
	virtual ~CPowerDrawGrpahList();

	BOOL ContinueInitIt(CAxisReference *axisReference);
	CString GetOneDrawString(CString strDraw);

	CPowerDrawBaseClass*PickIt(CPoint point,BOOL &bPicked);
	CPowerDrawBaseClass*PickIt(CPoint point,BOOL &bPicked,int &iIndex);
	CPowerDrawBaseClass*PickIt(int iIndex);
	BOOL RemoveUnit(int iIndex);

	void InitDrawGraphData(CString strGraph);
//	void InitDrawGraphData2(CString strGraph);
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual void  BeforePrinting(double fMMValue);
	virtual BOOL PickIt(CPoint point);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
	/////////////求取直线与图形的交点
	//入口参数：直线方程//返回参数：直线与图形的交点指针、交点的个数
	BOOL GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	virtual void OnColorChanged(COLORREF color);	//绘制图元的颜色改变
};

#endif // !defined(AFX_POWERDRAWGRPAHLIST_H__14D10736_7470_11D5_A3F9_00E04CE17719__INCLUDED_)
