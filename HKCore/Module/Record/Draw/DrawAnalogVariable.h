// DrawAnalogVariable.h: interface for the CDrawAnalogVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWANALOGVARIABLE_H__)
#define _DRAWANALOGVARIABLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawVariable.h"

class CDrawAnalogVariable : public CDrawVariable  
{
public:
	CDrawAnalogVariable();
	virtual ~CDrawAnalogVariable();

public:
	double* m_dCoefValue;//short到实际值
	double* m_dZeroValue;//实际零值 **V/A
	CString m_strUnit;
	CString m_strPhaseID;

	//关联的通道属性
	//CExBaseObject *m_pRefRtVariable;
	//CXDrawElements m_oAttrsDraw;

public:
//	virtual void SetBorder(const CRect &rect, BOOL bSavePos);
	virtual void SetBorder(const CRect &rect);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	virtual void SetParentWnd(CWnd* pParentWnd)	 ;
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void Zoom(double dRate) ;
	virtual void ZoomY(double dRate) ;
	virtual BOOL CanZoomY()		{	return TRUE;	}
	virtual BOOL CanZoomX()		{	return TRUE;	}
	virtual UINT GetClassID()	{	return CMTRDCLASSID_ANALOGVARIABLE ;		}
	virtual void GetVaraibleInterface(double& dCoef,long& nOffSetY);
	virtual void InitAxis(long nAxisRight);
	virtual void SetClipRect(const CRect &rcClip);
	virtual void SetAttachStruct(PRECORDDRAWOBJECTCONTROL pDrawStruct);
	virtual void DrawChanName(CDC* pDC, BOOL bDrawCarryGrid);
	void SetRange(double dRange) ;
	double GetRange()			{	return m_dRange;	}
	void SetUnit(const CString& strUnit);
	void SetAdjustValue(double *dZero,double *dCoef);
	void GetTimeCursorPos(long nCursorPos, long MR1200_DFT_CAL_LEN);
	void SetParaRect(CRect rcPara);

	//参数
	void AddPara(UINT nID);
	void DeletePara(UINT nID);
	void DeleteAllPara();

	virtual void DrawAttrs(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag, MrDraw::DRAWMEMBUFFERPOS &oBufPos);

private:
	double m_dRange;
	double m_dCarryPerGrid;

//////////////////////////////////////////////////////////////////////////
//综合属性绘图
public:
	virtual void AddAttrsDraw(CRtVariable *pRtVariable);
};

#endif // !defined(_DRAWANALOGVARIABLE_H__)
