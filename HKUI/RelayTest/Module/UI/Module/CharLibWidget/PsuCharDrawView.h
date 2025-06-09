﻿#pragma once
#include "../../../../../AutoTest/Module/Characteristic/CharacterDrawView.h"



class CPsuCharDrawView :public CCharacterDrawView
{
public:
	CPsuCharDrawView(void);
	virtual ~CPsuCharDrawView(void);

public:
	virtual void UI_OnMouseMove(UINT nFlags, CPoint point);
	virtual void UI_OnLButtonDblClk(UINT nFlags, CPoint point);

	void SetAxisInstruct_Point(const CPoint &point);//更新当前点的界面显示

	void UI_ZoomIn();
	void UI_ZoomOut();

	virtual void SetCurTestPoint(CXDrawPoint *pCurrTestPoint,BOOL bUpdateInstruct);
//	void SetTestPointLine(const double &dValueR,const double &dValueX);//创建经过测试点的直线

	CXDrawPoint* CreateNewTestPoint(const double &dR,const double &dX);//创建一个新的测试点
	void DeleteTestPoint(CXDrawPoint *pTestPoint);
	void GetAxisInterface(CAxisInterface **ppAxisInterface);

	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	virtual void AddTestResultPoint(double dX, double dY,BOOL bAct = TRUE);//添加测试结果点,参数3标记是否动作,动作和未动作采用不同的颜色标记
	virtual void ClearSearchPoints(long nPtIndex = -1);
	virtual long GetSearchPointsCount();
	virtual void CalVertHorzLine(long nIndex = 0, CString strType = CHAR_TESTLINE_MODE_ID_VERT);
	virtual void CalLinesPoints(long nIndex, CXDrawDatas* pDatas, CString strType);
    virtual void CalAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);

	virtual void DrawAxisTestPoints(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));//20240712 luozibing绘制m_oTestPoints中的测试点

	void SetXYUnitShow(CString strUnitMag,CString strUnitAng);
	void SetIsShowText(bool bIsShowText);
	void SetIsShowAng(bool bIsShowAng);
	void UpdateAxisType(const CString& strAxis,BOOL bLockXY);
	CXDrawLine* GetLeftButtonLine();

	void InitDrawLineColor(const COLORREF &oColor);

	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd, BOOL bViewTestLines, BOOL bCalCharTemp);
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

//    virtual void UpdateCurCharact(CXDrawList *pDrawList);   //20241025 wanmj 更新当前选中特性曲线drawlist
//    virtual void SetCurDrawList(CXDrawList *pDrawListRef){ m_pDrawListRef = pDrawListRef; }
//    virtual CXDrawList* GetCurDrawList(){ return m_pDrawListRef; }  //20241026 wanmj 获取当前选中特性曲线的drawlist

protected:
	virtual void InitCharDrawView(CCharacteristic *pCharTemp, CWnd *pParentWnd);
	//20230314 参数2标记是否初始化测试线颜色,测试线区分,系统和用户,创建时,设置其颜色
	//void InitDrawLineColor(const COLORREF &oColor);
	BOOL IsShowCharacteristic(CCharacteristic *pCharTemp);
	void InitDrawLineColor(const COLORREF &oLinesColor,const COLORREF &oTestLineColor_sys,const COLORREF &oTestLineColor_User);

//	virtual void SetAxisInstruct(const CString &strAxisInstruct1, const CString &strAxisInstruct2);//zhouhj 20210130 增加用于设置坐标轴说明类文字
	void DrawAxisInstruction(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));//zhouhj 20210203 绘制指示说明
	void DrawCurrTestPointLine(CDC *pDC,float fZoomRatio,CPoint ptOffset);//绘制经过坐标原点及当前测试点的直线

	//zhouhj 2024.10.10 所有特性曲线的绘图对象都创建,防止特性曲线计算交点时需要使用,对于隐藏不显示的部分,存入此链表
	CExBaseList m_oHidingDrawList;
//	CXDrawList *m_pDrawListNoShow;
//	CXDrawLine *m_pCurrTestPointLine;

public:
	//2021-9-15  lijunqing
	//CXDrawList *m_pOtherDrawList;

	float m_fZoomCoef;
	XDRAWDATA_POINT m_oAxisInstruct_Point;//坐标轴上显示的坐标值    //sf 外部访问 20211028
    int m_nFaultType;   //20240829 wanmj 保存当前选中测试项故障类型
    BOOL m_bShowCurrCharactColor; //20241025 wanmj 是否突出显示当前选中特性曲线的颜色

private:
	//坐标轴上说明类文字颜色,字体
	LOGFONT   m_lfAxisInstruct_Font;		////说明类文字字体
	COLORREF  m_crAxisInstructPoint_FontColor;//说明:当前指示点文字颜色

	CString m_strUnitMag;//显示的单位 20211027 sf
	CString m_strUnitAng;
	bool m_bIsShowText;//测试点是否显示标志 20211027 sf
	bool m_bIsShowAng;//是否要将笛卡尔坐标换算成幅值、相位来显示
// 	CString m_strInstruct1Text;
// 	CString m_strInstruct2Text;
	CString m_strInstructInit_Text;
	CString m_strInstructSelect_Text;
	CString m_strInstructEnd_Text;

	double	m_dInstructLeftGap;//说明文字,与工作区左侧的距离
	double	m_dInstructTopGap;//说明文字,与工作区顶部的距离
	double	m_dInstructSpaceGap;//说明文字,相互间的垂直间距

	CXDrawList m_oCharDrawList;//特性曲线相关的测试点、测试线绘图对象
	CXDrawLine m_oLeftButtonLine; //yizejun 2023-2-24 鼠标左键对应的竖线
//    CXDrawList *m_pDrawListRef;   //20241025 wanmj 当前特性曲线drawlist

protected:
	CXDrawList m_oTestPoints;//yizejun 2023-02-21 动作点集合
	COLORREF  m_crAxisInstructInit_FontColor;//说明:初始测试点文字颜色
	COLORREF  m_crAxisInstructSelect_FontColor;//说明:选中测试点文字颜色
	COLORREF  m_crAxisInstructEnd_FontColor;//说明:试验结束测试点文字颜色
};
