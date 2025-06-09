#include "XDrawTestPoint.h"
//#include "../../SttStudio/Module/UI/Module/CharLibWidget/InternationalCharactInterface.h"
CXDrawTestPoint::CXDrawTestPoint(void)
{
	m_nFaultType = -1;
	m_nZoneType = -1;
	m_nTestState = XDRAW_TEST_STATE_NORMAL;
//	m_nSelBeforeState = XDRAW_TEST_STATE_NORMAL;

	m_dwDrawStyle = 0;	//���Ե�Ĭ��Ϊ +
	m_crNomal_Color = RGB(0, 255, 0);//��ʼ���Ե���ɫ
	m_crSelect_Color = RGB(255, 0, 0);//ѡ�в��Ե���ɫ
	m_crEligible_Color = RGB(0, 0, 255);//�ϸ���Ե���ɫ
	m_crIneligible_Color = RGB(255, 255, 0);//���ϸ���Ե���ɫ
	m_crFinished_Color = RGB(255, 0, 255);//��ɲ��Ե���ɫ
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
	case XDRAW_TEST_STATE_NORMAL://��ʼ״̬
		m_crForeColor = m_crNomal_Color;
		break;

	case XDRAW_TEST_STATE_ELIGIBLE://��������ϸ�״̬
		m_crForeColor = m_crEligible_Color;
		break;
	case XDRAW_TEST_STATE_INELIGIBLE://����������ϸ�״̬
		m_crForeColor = m_crIneligible_Color;
		break;
	case XDRAW_TEST_STATE_FINISHED://����������״̬
		m_crForeColor = m_crFinished_Color;
		break;
	default:
		m_crForeColor = m_crNomal_Color;
		break;
	}
}

void CXDrawTestPoint::SetTestPoint(float fX, float fY, CString strIDPath, int  nFaultType, int nTestState, int  nZoneType)
{//���ò��Ե����
	m_strID = strIDPath;
	m_nZoneType = nZoneType;
	m_nFaultType = nFaultType;

//	if ((fabs(m_fX - fX)>0.0001f) || (fabs(m_fY - fY)>0.0001f))//����������ı�
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
// 	case XDRAW_TEST_STATE_NORMAL://��ʼ״̬
// 		m_crForeColor = m_crNomal_Color;
// 		break;
// 	case XDRAW_TEST_STATE_SELECT://ѡ��״̬
// 		m_crForeColor = m_crSelect_Color;
// 		break;
// 	case XDRAW_TEST_STATE_ELIGIBLE://��������ϸ�״̬
// 		m_crForeColor = m_crEligible_Color;
// 		break;
// 	case XDRAW_TEST_STATE_INELIGIBLE://����������ϸ�״̬
// 		m_crForeColor = m_crIneligible_Color;
// 		break;
// 	case XDRAW_TEST_STATE_FINISHED://����������״̬
// 		m_crForeColor = m_crFinished_Color;
// 		break;
// 	}
// }
