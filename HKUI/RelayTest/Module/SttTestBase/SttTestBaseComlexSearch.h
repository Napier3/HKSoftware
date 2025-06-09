#pragma once

#include "SttTestBaseSearch.h"
#include "SttComplexCalApi.h"

//CSttTestBaseComlexSearch��AngleΪ�Ƕȵ�λ
class CSttTestBaseComlexSearch : public CSttTestBaseSearch
{
public:
	CSttTestBaseComlexSearch(void);
	virtual ~CSttTestBaseComlexSearch(void);

protected:
	float m_fScanFromAngle;   //��������ʼֵ����ֵֹ  ԭʼ����
	float m_fScanToAngle;
	float m_fCurrScanValAngle;
	float m_fSearchBeginAngle;  //�����м�ֵ����ʼֵ����ֵֹ
	float m_fSearchEndAngle;
	float m_fActValueAngle;  //����ֵ
	BOOL m_bCurrSearchSwitch;		//��ǰ����������ʼֵ������ֵֹ	

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
};
