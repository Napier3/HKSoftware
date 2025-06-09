#include "XDrawTestPoint.h"
//#include "../../SttStudio/Module/UI/Module/CharLibWidget/InternationalCharactInterface.h"
CXDrawTestPoint::CXDrawTestPoint(void)
{
	m_nFaultType = -1;
	m_nZoneType = -1;
	m_nTestState = XDRAW_TEST_STATE_NORMAL;
//	m_nSelBeforeState = XDRAW_TEST_STATE_NORMAL;

	m_dwDrawStyle = 0;	//测试点默认为 +
	m_crNomal_Color = RGB(0, 255, 0);//初始测试点颜色
	m_crSelect_Color = RGB(255, 0, 0);//选中测试点颜色
	m_crEligible_Color = RGB(0, 0, 255);//合格测试点颜色
	m_crIneligible_Color = RGB(255, 255, 0);//不合格测试点颜色
	m_crFinished_Color = RGB(255, 0, 255);//完成测试点颜色
}

CXDrawTestPoint::~CXDrawTestPoint(void)
{
}

void CXDrawTestPoint::UpdateColorByTestState()
{
	if (m_nTestState&&XDRAW_TEST_STATE_SELECT)
	{
		m_crForeColor = m_crSelect_Color;
		return;
	}

	switch (m_nTestState)
	{
	case XDRAW_TEST_STATE_NORMAL://初始状态
		m_crForeColor = m_crNomal_Color;
		break;

	case XDRAW_TEST_STATE_ELIGIBLE://试验结束合格状态
		m_crForeColor = m_crEligible_Color;
		break;
	case XDRAW_TEST_STATE_INELIGIBLE://试验结束不合格状态
		m_crForeColor = m_crIneligible_Color;
		break;
	case XDRAW_TEST_STATE_FINISHED://试验结束完成状态
		m_crForeColor = m_crFinished_Color;
		break;
	default:
		m_crForeColor = m_crNomal_Color;
		break;
	}
}

void CXDrawTestPoint::SetTestPoint(float fX, float fY, CString strIDPath, int  nFaultType, int nTestState, int  nZoneType)
{//设置测试点参数
	m_strID = strIDPath;
	m_nZoneType = nZoneType;
	m_nFaultType = nFaultType;

//	if ((fabs(m_fX - fX)>0.0001f) || (fabs(m_fY - fY)>0.0001f))//测试项坐标改变
	{
		m_fX = fX;
		m_fY = fY;
	}

// 	if (nTestState == -1)
// 	{
// 		return;
// 	}
	m_nTestState = nTestState;
	UpdateColorByTestState();
}
// void CXDrawTestPoint::ReturnSelBrforeState()
// {
// 	if (m_nTestState > XDRAW_TEST_STATE_SELECT)
// 	{
// 		m_nTestState &= 0xff;
// 	}
// 	
// 	switch (m_nTestState)
// 	{
// 	case XDRAW_TEST_STATE_NORMAL://初始状态
// 		m_crForeColor = m_crNomal_Color;
// 		break;
// 	case XDRAW_TEST_STATE_SELECT://选中状态
// 		m_crForeColor = m_crSelect_Color;
// 		break;
// 	case XDRAW_TEST_STATE_ELIGIBLE://试验结束合格状态
// 		m_crForeColor = m_crEligible_Color;
// 		break;
// 	case XDRAW_TEST_STATE_INELIGIBLE://试验结束不合格状态
// 		m_crForeColor = m_crIneligible_Color;
// 		break;
// 	case XDRAW_TEST_STATE_FINISHED://试验结束完成状态
// 		m_crForeColor = m_crFinished_Color;
// 		break;
// 	}
// }
