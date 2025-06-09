#pragma once

#define SEARCHMODE_BINARY_SEARCH   0
#define SEARCHMODE_LINER_SEARCH    1

//�������
#define ACTFLAG_NORMAL    0  //δ����/δ����
#define ACTFLAG_ACT       1  //����/����
#define ACTFLAG_FINISH    2  //δ����/����

#include "../../../Module/API/MathApi.h"

class CSttTestBaseSearch
{
public:
    CSttTestBaseSearch(void);
    virtual ~CSttTestBaseSearch(void);

	BOOL IsLinerSearch()	{	return (m_nSearchMode == SEARCHMODE_LINER_SEARCH); }
	BOOL IsBinarySearch()	{	return (m_nSearchMode == SEARCHMODE_BINARY_SEARCH); }
	void SetLinerSearchMode()	{	m_nSearchMode = SEARCHMODE_LINER_SEARCH;	}
	void SetBinarySearchMode()	{	m_nSearchMode = SEARCHMODE_BINARY_SEARCH;	}

	BOOL IsAct()				{	return (m_nActFlag == ACTFLAG_ACT);	}
	BOOL IsFinished()		{	return (m_nActFlag != ACTFLAG_NORMAL);	}
	float GetActValue()	;

protected:
	float m_fScanFrom;   //��������ʼֵ����ֵֹ  ԭʼ����
	float m_fScanTo;
	float m_fStep;
	long  m_nStepIndex;
	float m_fCurrScanVal;
	
	float m_fSearchBegin;  //�����м�ֵ����ʼֵ����ֵֹ
	float m_fSearchEnd;
	float m_fSearchArea;  //ʣ�µĳ���

	int m_nTripFlagFrom;
	int m_nTripFlagTo;
	int m_nTripFlagCurr;
	int m_nTripFirst;   //��һ����Ķ���״̬

	int m_nActFlag; // �Ƿ����ı��
	float m_fActValue;  //����ֵ
	
	long m_nSearchMode;  //����ģʽ

	double  m_fSerchOriginLength;  //�����ߵ��ܳ���

public:
	virtual void InitSearch();
	virtual BOOL IsSearchFinished(int nTripFlag);
	virtual BOOL SearchNext();
	virtual float GetSteps();

private:
	//��������
	virtual BOOL SearchNext_LinerSearch();
	virtual BOOL SearchNext_BinarySearch();

	virtual BOOL IsSearchFinished_LinerSearch(int nTripFlag);
	virtual BOOL IsSearchFinished_BinarySearch(int nTripFlag);
	virtual float GetSteps_LinerSearch();
	virtual float GetSteps_BinarySearch();

	virtual BOOL IsLinerSearchReachEnd();
	virtual BOOL IsLinerSearchOutEnd();

	//����������Ҫʵ�ֵĺ���
	virtual float CalCountByStep();      //�����������Ȱ����Ĳ�������
	virtual void  GetBinarySearchArea();
	virtual void CalLineSearchNextPoint();
	virtual float CalLenForCurrToFromAndTo();
	virtual float CalLenForCurrToEnd();

	virtual void SearchSetFromAsCurr();
	virtual void SearchSetToAsCurr();
	virtual void SearchSetCurrAsBegin();
	virtual void SearchSetCurrAsEnd();
	virtual void BinarySearchCalCurrByBeginEnd();

	virtual void SetSearchBeginValAsActVal();
	virtual void SetSearchEdnValAsActVal();
	virtual void SetSearchCurrValAsActVal();
};
