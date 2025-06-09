#pragma once

#include "tmt_search_base.h"
#include "../../../SttTestBase/SttComplexCalApi.h"

//tmt_complex_search��AngleΪ�Ƕȵ�λ
typedef struct tmt_complex_search : public tmt_SearchBase
{
public:
	float m_fScanFromAngle;		 //��������ʼֵ����ֵֹ  ԭʼ����
	float m_fScanToAngle;
	float m_fCurrScanValAngle;
	float m_fSearchBeginAngle;  //�����м�ֵ����ʼֵ����ֵֹ
	float m_fSearchEndAngle;
	float m_fActValueAngle;		//����ֵ
	float m_fAngle;
//	BOOL  m_bCurrSearchSwitch;	//��ǰ����������ʼֵ������ֵֹ,�ò���δ�õ�,ɾ��	

	//2021-9-16  lijunqing
	double m_fScanFromR, m_fScanFromX;
	double m_fScanToR, m_fScanToX;
	double m_fCurrR, m_fCurrX;
	double m_fSearchBeginR, m_fSearchBeginX;
	double m_fSearchEndR, m_fSearchEndX;

	void CalRX(double dLen, double dAngle, double &dR, double &dX)
	{
		double dTemp =dAngle * 3.14159 / 180;
		dR = dLen * cos(dTemp);
		dX = dLen * sin(dTemp);
	}

	void CalRX_All()
	{
		CalRX(m_fScanFrom, m_fScanFromAngle, m_fScanFromR, m_fScanFromX);
		CalRX(m_fScanTo, m_fScanToAngle, m_fScanToR, m_fScanToX);
		CalRX(m_fCurrScanVal, m_fCurrScanValAngle, m_fCurrR, m_fCurrX);
		CalRX(m_fSearchBegin, m_fSearchBeginAngle, m_fSearchBeginR, m_fSearchBeginX);
		CalRX(m_fSearchEnd, m_fSearchEndAngle, m_fSearchEndR, m_fSearchEndX);
	}

public:
	tmt_complex_search(void);
	virtual ~tmt_complex_search(void);


public:
	virtual void InitSearch();
	float GetActValueAngle();

private:
	virtual float CalLenForCurrToFromAndTo();
	virtual float CalLenForCurrToEnd();
	virtual void  GetBinarySearchArea();
	virtual void CalLineSearchNextPoint();

	virtual void SearchSetFromAsCurr();
	virtual void SearchSetToAsCurr();
	virtual void SearchSetCurrAsBegin();
	virtual void SearchSetCurrAsEnd();
	virtual void BinarySearchCalCurrByBeginEnd();

	virtual void SetSearchBeginValAsActVal();
	virtual void SetSearchEdnValAsActVal();
	virtual void SetSearchCurrValAsActVal();

private:
	double  m_fLineAngle;              //�����ߵĽǶ�
}tmt_ComplexSearch;
