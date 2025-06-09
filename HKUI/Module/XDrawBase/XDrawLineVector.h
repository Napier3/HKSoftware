#pragma once
#include "XDrawLine.h"

class CXDrawLineVector :
	public CXDrawLine
{
public:
	CXDrawLineVector(void);
	~CXDrawLineVector(void);
	void Draw(CAxisInterface *pAxis, CDC *pDC, COLORREF lineColor, double fZoomRatio,const CPoint &ptOffset);

public:
	CString m_strTag;  //矢量名称
	LOGFONT m_lfTextFont; //矢量名称文字字体
	COLORREF m_oTagColor;  //矢量名称字体颜色
	double m_dInstructLeftGap;  //矢量名称左侧和顶点间距
	double m_dInstructTopGap;//矢量名称与工作区顶部的距离
	double m_dInstructSpaceGap;//矢量名称相互间的垂直间距

private:
	CPoint m_triPoints[3];  //矢量箭头的顶点
	
};
