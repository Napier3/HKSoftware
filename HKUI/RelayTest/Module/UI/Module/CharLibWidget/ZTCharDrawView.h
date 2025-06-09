#pragma once
#include "../../../../../AutoTest/Module/Characteristic/CharacterDrawView.h"
//#include "../../../../../Module/XDrawBase/XDrawTestPoint.h"

#define PRECISION 0.000001
#define ZTVIEW_MAXIMUM_VERTICAL_LINE	"maxV"
#define ZTVIEW_MINIMUM_VERTICAL_LINE	"minV"

class CZTCharDrawView :public CCharacterDrawView
{
public:
	CZTCharDrawView(void);
	virtual ~CZTCharDrawView(void);

public:
	virtual void UI_OnMouseMove(UINT nFlags, CPoint point);

	//设置 角度和故障类型
	void SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype); 
	void SetAxisInstruct_Point(const CPoint &point);//更新当前点的界面显示
	//设置当前选中测试点
	void SetCurTestPoint(double dX,double dY,BOOL bWithin);
	//鼠标单击显示在测试线上的测试点
	void LeftButtonDown();
	CXDrawLine* CheckCurrentTestPoint();
	void UI_ZoomIn();
	void UI_ZoomOut();
	//清空测试线
	void ClearTestLines();
	virtual void ClearSearchPoints(long nPtIndex = -1);
	//添加测试点
	CXDrawPoint* AddOneTestPoint(const double &dR,const double &dX);
	CXDrawPoint* AddOneTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY);
	//删除测试点
	void DeleteTestPoint(const CString &strIDPath);
	//更新测试点
	bool UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, BOOL bSelPonit);
	//添加测试线
	CXDrawLine* AddOneTestLine(const CString &strIDPath,double dXMin,double dYMIn,double dXMax,double dYMax,double dPlus = 0,double dMinus = 0);
	void GetAxisInterface(CAxisInterface **ppAxisInterface);

	virtual void DrawActiveElement(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	void SetXYUnitShow(CString strUnitMag,CString strUnitAng);

	virtual void ZoomIn(double dCoef=2.0);
	virtual void ZoomOut(double dCoef=2.0);
    virtual void ZoomReset(double dCoef=2.0);
    virtual void ZoomAxisReset(double dMinY);
    virtual void ZoomAxisPointInCenter(double dX,double dY);
protected:
 	void InitDrawLineColor(const COLORREF &oColor);
	//说明文字
	void DrawAxisInstruction(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));

    double m_dMax_XAxis;
    double m_dMax_YAxis;
    double m_dMin_XAxis;
    double m_dMin_YAxis;

    double m_dReSetMax_X;
    double m_dReSetMax_Y;
    double m_dReSetMin_X;
    double m_dReSetMin_Y;
public:
	BOOL m_ImpSearch;//横线显示误差范围(TRUE)或竖线显示误差范围(FALSE)
	
	XDRAWDATA_POINT m_oAxisInstruct_Point;

protected:

	LOGFONT   m_lfAxisInstruct_Font;		////说明类文字字体
	COLORREF  m_crAxisInstructPoint_FontColor;//说明文字颜色
	COLORREF  m_crAxisInstructInit_PointColor;//测试点颜色
	COLORREF  m_crAxisInstructInit_LineColor;//测试线颜色
	
	CString m_strAngle;
	CString m_strFaultype;//故障类型
	CString m_strUnitMag;//显示的单位 20211027 sf
	CString m_strUnitAng;
	bool m_bIsShowAng;//是否要将笛卡尔坐标换算成幅值、相位来显示

	double	m_dInstructLeftGap;//说明文字,与工作区左侧的距离
	double	m_dInstructTopGap;//说明文字,与工作区顶部的距离
	double	m_dInstructSpaceGap;//说明文字,相互间的垂直间距

	CXDrawList m_oCharDrawList;//ZT视图对应曲线
	CXDrawList m_oCharPlusDrawList;//ZT视图正误差对应曲线
	CXDrawList m_oCharMinusDrawList;//ZT视图负误差对应曲线
	CXDrawList m_oTestPoints;//测试点集合

	CXDrawPoint m_oMouseClick;//鼠标左键点击坐标
};
