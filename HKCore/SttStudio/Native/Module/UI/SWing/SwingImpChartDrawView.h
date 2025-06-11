#pragma once
#include "../../../AutoTest/Module/Characteristic/CharacterDrawView.h"
#include"../../../AutoTest/Module/Characteristic/CharElementLined.h"
#include "../../../Module/XDrawBase/XDrawLineVector.h"
#include "../../SttTestBase/SttComplexp.h"
#include "../../SttTest/Common/Swing/tmt_swing_test.h"

class CSwingImpChartDrawView :public CCharacterDrawView
{
public:
	CSwingImpChartDrawView(void);
	virtual ~CSwingImpChartDrawView(void);

public:
	virtual void UI_OnMouseMove(UINT nFlags, CPoint point);
	virtual void UI_OnLButtonDblClk(UINT nFlags, CPoint point);
	void SetAxisInstruct_Point(const CPoint &point);//更新当前点的界面显示
	void GetAxisInterface(CAxisInterface **ppAxisInterface);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	void SetXYUnitShow(CString strUnitMag,CString strUnitAng);
	void SetCharacterDatas();  //2024.6.18 配置阻抗图数据
	void SetTestPoint(double dX, double dY);  //2024.6.20 设置测试点

protected:
	void DrawAxisInstruction(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));//zhouhj 20210203 绘制指示说明
	void DrawSwingImpCharacter(CDC *pDC,float fZoomRatio,CPoint ptOffset);  //2024.6.18 绘制阻抗图

public:
	//2021-9-15  lijunqing
	float m_fZoomCoef;
	XDRAWDATA_POINT m_oAxisInstruct_Point;//坐标轴上显示的坐标值    //sf 外部访问 20211028
	tmt_SwingTest *m_pCurTest;

private:
	//坐标轴上说明类文字颜色,字体
	LOGFONT   m_lfAxisInstruct_Font;		////说明类文字字体
	COLORREF  m_crAxisInstructPoint_FontColor;//说明:当前指示点文字颜色

	CString m_strUnitMag;//显示的单位 20211027 sf
	CString m_strUnitAng;

	double	m_dInstructLeftGap;//说明文字,与工作区左侧的距离
	double	m_dInstructTopGap;//说明文字,与工作区顶部的距离
	double	m_dInstructSpaceGap;//说明文字,相互间的垂直间距

	Complex m_oZs;  //系统侧阻抗
	Complex m_oZt;  //变压器阻抗
	Complex m_oXd;  //发电机暂态电抗
	CXDrawLineVector m_oZsLine;
	CXDrawLineVector m_oZtLine;
	CXDrawLineVector m_oImpTsLine;
	COLORREF m_oLineFontColor;
	COLORREF m_oImpCirFontColor;
	CPoint m_oTestPoint;  //测试点
	COLORREF m_oTestPointColor;
	CXDrawLine m_oZLine;  //75°阻抗角的直线
};
