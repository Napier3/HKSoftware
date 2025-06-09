#pragma once

#define SEARCHMODE_BINARY_SEARCH   0
#define SEARCHMODE_LINER_SEARCH    1

//动作标记
#define ACTFLAG_NORMAL    0  //未动作/未结束
#define ACTFLAG_ACT       1  //动作/结束
#define ACTFLAG_FINISH    2  //未动作/结束

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
	float m_fScanFrom;   //搜索的起始值、终止值  原始数据
	float m_fScanTo;
	float m_fStep;
	long  m_nStepIndex;
	float m_fCurrScanVal;
	
	float m_fSearchBegin;  //搜索中间值，起始值、终止值
	float m_fSearchEnd;
	float m_fSearchArea;  //剩下的长度

	int m_nTripFlagFrom;
	int m_nTripFlagTo;
	int m_nTripFlagCurr;
	int m_nTripFirst;   //第一个点的动作状态

	int m_nActFlag; // 是否动作的标记
	float m_fActValue;  //动作值
	
	long m_nSearchMode;  //搜索模式

	double  m_fSerchOriginLength;  //搜索线的总长度

public:
	virtual void InitSearch();
	virtual BOOL IsSearchFinished(int nTripFlag);
	virtual BOOL SearchNext();
	virtual float GetSteps();

private:
	//基本函数
	virtual BOOL SearchNext_LinerSearch();
	virtual BOOL SearchNext_BinarySearch();

	virtual BOOL IsSearchFinished_LinerSearch(int nTripFlag);
	virtual BOOL IsSearchFinished_BinarySearch(int nTripFlag);
	virtual float GetSteps_LinerSearch();
	virtual float GetSteps_BinarySearch();

	virtual BOOL IsLinerSearchReachEnd();
	virtual BOOL IsLinerSearchOutEnd();

	//各派生类需要实现的函数
	virtual float CalCountByStep();      //计算搜索长度包含的步长数量
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
