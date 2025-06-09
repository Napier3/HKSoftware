#pragma once
#include "./XDrawPoint.h"


//移植到CharacteristicGlobal.h并改名
// #define XDRAW_TEST_STATE_SELECT		        	0x100//测试点选中状态
// #define XDRAW_TEST_STATE_NORMAL			            0//测试点初始状态
// #define XDRAW_TEST_STATE_ELIGIBLE	            	1//测试点合格状态
// #define XDRAW_TEST_STATE_INELIGIBLE	                2//测试点不合格状态
// #define XDRAW_TEST_STATE_FINISHED	                3//测试点测试完成状态


class CXDrawTestPoint :public CXDrawPoint
{
public:
	CXDrawTestPoint(void);
	virtual ~CXDrawTestPoint(void);

	virtual UINT GetClassID() { return DWCLASSID_CXDRAWTESTPOINT; }

	void SetTestPoint(float fX, float fY,CString strIDPath, int  nFaultType = -1, int nTestState = -1, int  nZoneType = -1);//设置测试点参数
//	void ReturnSelBrforeState();//返回选择前的状态
	void UpdateColorByTestState();


	int  m_nFaultType;//保存测试项故障类型
	int  m_nZoneType;//保存测试项段号，对应非距离类区段为-1,缺省为-1
	int m_nTestState; //当前测试项的状态   初始/选中/合格/不合格/测试完成
//	int m_nSelBeforeState;//选择前的状态
protected:
	COLORREF  m_crNomal_Color;//初始测试点颜色
	COLORREF  m_crSelect_Color;//选中测试点颜色
	COLORREF  m_crEligible_Color;//合格测试点颜色
	COLORREF  m_crIneligible_Color;//不合格测试点颜色
	COLORREF  m_crFinished_Color;//完成测试点颜色
};
