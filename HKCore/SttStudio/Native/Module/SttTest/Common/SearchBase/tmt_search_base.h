#pragma once

#define SEARCHMODE_BINARY_SEARCH   0  //二分法
#define SEARCHMODE_LINER_SEARCH    1  //单步逼近

//动作标记
#define ACTFLAG_NORMAL    0  //未动作/未结束
#define ACTFLAG_ACT       1  //动作/结束
#define ACTFLAG_FINISH    2  //未动作/结束

typedef struct tmt_search_base
{
public:
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
	tmt_search_base(void);
	virtual ~tmt_search_base(void);

	BOOL IsLinerSearch()	{	return (m_nSearchMode == SEARCHMODE_LINER_SEARCH); }
	BOOL IsBinarySearch()	{	return (m_nSearchMode == SEARCHMODE_BINARY_SEARCH); }
	void SetLinerSearchMode()	{	m_nSearchMode = SEARCHMODE_LINER_SEARCH;	}
	void SetBinarySearchMode()	{	m_nSearchMode = SEARCHMODE_BINARY_SEARCH;	}

	BOOL IsAct()				{	return (m_nActFlag == ACTFLAG_ACT);	}
	BOOL IsFinished()		{	return (m_nActFlag != ACTFLAG_NORMAL);	}
	float GetActValue()	;



public:
	virtual void InitSearch();
	virtual BOOL IsSearchFinished(int nTripFlag);
	virtual BOOL SearchNext();
	virtual float GetSteps();

	void CopyOwnSearchBase(tmt_search_base *pDest)
	{
		pDest->m_fScanFrom = m_fScanFrom;
		pDest->m_fScanTo = m_fScanTo;
		pDest->m_fStep = m_fStep;
		pDest->m_nStepIndex = m_nStepIndex;
		pDest->m_fCurrScanVal = m_fCurrScanVal;
		pDest->m_fSearchBegin = m_fSearchBegin;
		pDest->m_fSearchEnd = m_fSearchEnd;
		pDest->m_fSearchArea = m_fSearchArea;
		pDest->m_nTripFlagFrom = m_nTripFlagFrom;
		pDest->m_nTripFlagTo = m_nTripFlagTo;
		pDest->m_nTripFlagCurr = m_nTripFlagCurr;
		pDest->m_nTripFirst = m_nTripFirst;
		pDest->m_nActFlag = m_nActFlag;
		pDest->m_fActValue = m_fActValue;
		pDest->m_nSearchMode = m_nSearchMode;
		pDest->m_fSerchOriginLength = m_fSerchOriginLength;
	}

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
}tmt_SearchBase;
