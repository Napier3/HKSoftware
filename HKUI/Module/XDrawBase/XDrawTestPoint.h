#pragma once
#include "./XDrawPoint.h"


//��ֲ��CharacteristicGlobal.h������
// #define XDRAW_TEST_STATE_SELECT		        	0x100//���Ե�ѡ��״̬
// #define XDRAW_TEST_STATE_NORMAL			            0//���Ե��ʼ״̬
// #define XDRAW_TEST_STATE_ELIGIBLE	            	1//���Ե�ϸ�״̬
// #define XDRAW_TEST_STATE_INELIGIBLE	                2//���Ե㲻�ϸ�״̬
// #define XDRAW_TEST_STATE_FINISHED	                3//���Ե�������״̬


class CXDrawTestPoint :public CXDrawPoint
{
public:
	CXDrawTestPoint(void);
	virtual ~CXDrawTestPoint(void);

	virtual UINT GetClassID() { return DWCLASSID_CXDRAWTESTPOINT; }

	void SetTestPoint(float fX, float fY,CString strIDPath, int  nFaultType = -1, int nTestState = -1, int  nZoneType = -1);//���ò��Ե����
//	void ReturnSelBrforeState();//����ѡ��ǰ��״̬
	void UpdateColorByTestState();


	int  m_nFaultType;//����������������
	int  m_nZoneType;//���������κţ���Ӧ�Ǿ���������Ϊ-1,ȱʡΪ-1
	int m_nTestState; //��ǰ�������״̬   ��ʼ/ѡ��/�ϸ�/���ϸ�/�������
//	int m_nSelBeforeState;//ѡ��ǰ��״̬
protected:
	COLORREF  m_crNomal_Color;//��ʼ���Ե���ɫ
	COLORREF  m_crSelect_Color;//ѡ�в��Ե���ɫ
	COLORREF  m_crEligible_Color;//�ϸ���Ե���ɫ
	COLORREF  m_crIneligible_Color;//���ϸ���Ե���ɫ
	COLORREF  m_crFinished_Color;//��ɲ��Ե���ɫ
};
