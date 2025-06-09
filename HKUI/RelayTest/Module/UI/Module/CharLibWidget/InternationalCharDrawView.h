#pragma once
#include "./PsuCharDrawView.h"
//#include "../../../../../Module/XDrawBase/XDrawTestPoint.h"
#include "./InternationalCharactInterface.h"

class CInternationalCharDrawView :public CPsuCharDrawView
{
public:
	CInternationalCharDrawView(void);
    virtual ~CInternationalCharDrawView(void);

	virtual void SetCurTestPoint(CXDrawPoint *pCurrTestPoint, BOOL bUpdateInstruct);
	virtual void ClearSearchPoints(long nPtIndex = -1);

	// 删除测试点 / 线
	void DeleteTestData(const CString &strIDPath);
	//添加距离保护单个测试项对应测试点,参数1传递当前测试项路径,参数2、3对应电阻值、电抗值、参数4对应故障类型，参数5对应区段
	BOOL AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState = -1);
//	void AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, bool nState = -1);
    //20240821 wanmj 添加测试项的测试线到特性曲线图
    void AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState = -1);
	//根据当前选中故障类型显示相同故障类型的测试点/线
	virtual void DrawAxisTestPoints(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	//同期更新允许压差、允许频差参数,更新曲线界面显示
	BOOL UpdateTestUI_Syn(CCharacteristics *pCharacteristics, double dX, double dY);
	CCharacterArea *GetElementLined_Syn(CCharacteristics *pCharacteristics, int nindex);
	//标记是否显示全部特性曲线,如果不是需要根据当前测试项故障类型过滤只显示LN或LL对应的曲线
	//BOOL m_bShowAllCharacts;	//移动到CCharacterDrawView类 用来设置根据曲线是否使用显示曲线或显示全部曲线 20240923 luozibing

    //20240829 wanmj
    virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd, BOOL bViewTestLines, BOOL bCalCharTemp);
	////20240919 luozibing 重载函数 判断曲线是否全部显示
	//virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

    virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

    //20240919 wanmj 鼠标绘制测试线 记录起始/终点坐标
    void SetTestLineBegin(const CPoint &point);
    void SetTestLineEnd(const CPoint &point);
    BOOL GetTestLineBegEndPos(double &dBegX, double &dBegY, double &dEndX, double &dEndY);
    void ClearTestLine();

    //20241011 wanmj 获取/设置坐标轴范围
    void GetAxisMinMax(double &dXmin, double &dYmin, double &dXmax, double &dYmax);
    void SetAxisMinMax(double dXmin, double dYmin, double dXmax, double dYmax);
	
	//add wangtao 20240918 添加差动测试线, 存在 比率制动/谐波制动 特性曲线，根据nDiffTestType选择其中一个曲线添加
	BOOL AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState = -1);
	//add wangtao 20240924	添加差动动作时间测试点, 根据nDiffTestType区分比率制动显示
	BOOL AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);
private:
    //20240919 wanmj 鼠标绘制测试线
    CXDrawLine m_oTestLineFromChar;
    double m_dBegX;
    double m_dBegY;
    double m_dEndX;
    double m_dEndY;

};
