#include "StdAfx.h"
#include "SttTestBaseSearch.h"

CSttTestBaseSearch::CSttTestBaseSearch(void)
{
	m_nTripFirst = -1;
	m_fScanFrom = 0;
	m_fScanTo = 0;
	m_fStep = 0;
	m_nStepIndex = 0;
	m_fCurrScanVal = 0;
	m_nTripFlagFrom = -1;
	m_nTripFlagTo = -1;
	m_nActFlag = FALSE;

	m_fSearchBegin = 0;
	m_fSearchEnd = 0;
	m_fSearchArea = 0;
	m_fSerchOriginLength = 0;

	SetBinarySearchMode();
}

CSttTestBaseSearch::~CSttTestBaseSearch(void)
{
}

float CSttTestBaseSearch::GetActValue()
{	
	if (IsBinarySearch())
	{
		if (m_nTripFirst == m_nTripFlagCurr)
		{
			return m_fActValue;
		}
		else
		{
			if (m_nTripFirst == m_nTripFlagFrom)
			{
				return m_fSearchBegin;
			}
			else
			{
				return m_fSearchEnd;
			}
		}
	}
	else 
	{
		return m_fActValue;
	}
}

void CSttTestBaseSearch::InitSearch()
{
	m_fCurrScanVal = m_fScanFrom;
	m_nStepIndex = 0;
	m_nActFlag = ACTFLAG_NORMAL;
	m_nTripFlagFrom = -1;
	m_nTripFlagTo = -1;
	m_fActValue = 0;

	m_fStep = fabs(m_fStep);
	m_fSearchBegin = m_fScanFrom;
	m_fSearchEnd = m_fScanTo;
	m_fSearchArea = fabs(m_fScanFrom - m_fScanTo);
	m_fSerchOriginLength = fabs(m_fScanTo - m_fScanFrom);
}

BOOL CSttTestBaseSearch::IsSearchFinished(int nTripFlag)
{
	if (IsFinished())
	{
		return TRUE;
	}

	if (IsLinerSearch())
	{
		return IsSearchFinished_LinerSearch(nTripFlag);
	}

	if (IsBinarySearch())
	{
		return IsSearchFinished_BinarySearch(nTripFlag);
	}

	return IsSearchFinished_LinerSearch(nTripFlag);
}

BOOL CSttTestBaseSearch::SearchNext()
{
	m_nStepIndex++;

	if (IsLinerSearch())
	{
		return SearchNext_LinerSearch();
	}

	if(IsBinarySearch())
	{
		return SearchNext_BinarySearch();
	}

	return SearchNext_LinerSearch();
}

BOOL CSttTestBaseSearch::IsLinerSearchReachEnd()
{
	float fLen = CalLenForCurrToEnd();

	if (fLen < 0.000001)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	//搜索到终点, 结束试验
	if(fabs( fLen - m_fSerchOriginLength) < 0.0001)
	{
		return FALSE;
	}	
	else
	{
		return TRUE;
	}
}

BOOL CSttTestBaseSearch::IsLinerSearchOutEnd()
{
	float fLen = CalLenForCurrToFromAndTo();

	//当前点到起始点、终点的长度和，大于起点到终点的长度
	if (fLen - m_fSerchOriginLength > PRECISION_COMPARE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

float CSttTestBaseSearch::CalCountByStep()
{
	return (float)(m_fSerchOriginLength / m_fStep);
}


BOOL CSttTestBaseSearch::SearchNext_LinerSearch()
{
	//计算下一个搜索点
	CalLineSearchNextPoint();

	if(IsLinerSearchOutEnd())//超过终点，将重点设置为当前搜索点
	{
		SearchSetToAsCurr();
	}

	return TRUE;
}

BOOL CSttTestBaseSearch::SearchNext_BinarySearch()
{
	//*Begin*---------*Curr*-------*end*

	//完成第一个点的搜索，下一个点为*end*
	if (m_nTripFlagTo == -1)
	{
		SearchSetToAsCurr();
		return TRUE;
	}

	//第三个点及以后的测试点，折半搜索

	if (m_nTripFlagCurr == m_nTripFlagFrom)
	{//当前点与起始点的动作情况一致，*Begin*=当前点
		SearchSetCurrAsBegin();
	}
	else
	{//当前点与起始点的动作情况不一致，*end*=当前点
		SearchSetCurrAsEnd();
	}

	BinarySearchCalCurrByBeginEnd();
	GetBinarySearchArea();

	return TRUE;
}

BOOL CSttTestBaseSearch::IsSearchFinished_LinerSearch(int nTripFlag)
{
	BOOL bEndFlag = FALSE;

	//判断是否发送下一个点
	if ((1 == nTripFlag && m_nTripFlagFrom == 0) 
		|| (0 == nTripFlag && m_nTripFlagFrom == 1))
	{
		bEndFlag = TRUE;
		m_nActFlag = ACTFLAG_ACT;
		m_fActValue = m_fCurrScanVal;
	}
	else
	{
		bEndFlag = IsLinerSearchReachEnd();
	}

	m_nTripFlagFrom = nTripFlag;

	return bEndFlag;
}

BOOL CSttTestBaseSearch::IsSearchFinished_BinarySearch(int nTripFlag)
{
	BOOL bEndFlag = FALSE;
	m_nTripFlagCurr = nTripFlag;

	if (m_nTripFlagFrom == -1)  //第一个测试点
	{
		m_nTripFlagFrom = nTripFlag;
		m_nTripFirst = nTripFlag;  //记录第一个点的动作状态
		return bEndFlag;
	}

	if (m_nTripFlagTo == -1) //第二个测试点
	{
		m_nTripFlagTo = nTripFlag;

		if (m_nTripFlagFrom == m_nTripFlagTo)//搜索起点和终点的动作情况相同，搜索结束
		{
			m_nActFlag = ACTFLAG_FINISH; //结束/未动作
			bEndFlag = TRUE;
			return bEndFlag;
		}
	}

	//获得搜索区域的长度
	GetBinarySearchArea();

	if (m_fSearchArea > m_fStep)
	{
		bEndFlag = FALSE;
		return bEndFlag;
	}

	//*Begin*---------*Curr*-------*end*
	//j计算动作值
	m_nActFlag = ACTFLAG_ACT;

	if (m_nStepIndex % 2 == 0)
	{//*Begin*==>>*Curr*
		if (m_nTripFlagCurr == m_nTripFlagFrom)
		{//当前点的动作情况与起始点的动作情况一致，记录动作值为*end*
			SetSearchEdnValAsActVal();
		}
		else
		{//当前点的动作情况与起始点的动作情况不一致，记录动作值为*curr*
			SetSearchCurrValAsActVal();
		}		
	}
	else
	{//*end*==>>*Curr*
		if (m_nTripFlagCurr == m_nTripFlagTo)
		{//当前点的动作情况与起始点的动作情况一致，记录动作值为*end*
			SetSearchCurrValAsActVal();
		}
		else
		{//当前点的动作情况与起始点的动作情况不一致，记录动作值为*curr*
			SetSearchBeginValAsActVal();
		}
	}

	bEndFlag = TRUE;

	return bEndFlag;
}

float CSttTestBaseSearch::GetSteps()
{
	if (IsLinerSearch())
	{
		return GetSteps_LinerSearch();
	}

	if (IsBinarySearch())
	{
		return GetSteps_BinarySearch();
	}

	return GetSteps_LinerSearch();
}

float CSttTestBaseSearch::GetSteps_LinerSearch()
{
	if (fabs(m_fStep) < 0.0001)
	{
		return 1;
	}

	float nCount = CalCountByStep();
	return nCount+1;
}

float CSttTestBaseSearch::GetSteps_BinarySearch()
{
	if (fabs(m_fStep) < 0.0001)
	{
		return 1;
	}

	float fCounts = GetSteps_LinerSearch();
	float fSteps = 2;

	if (fCounts <= 2)
	{
		return fSteps;
	}

	while (TRUE)
	{
		if (fCounts < 1)
		{
			break;
		}

		fSteps++;
		fCounts /= 2;
	}

	fSteps += 2;  //起点和终点两个点

	return fSteps;
}



//////////////////////////////////////////////////////////////////////////
//各派生类需要实现的函数

void CSttTestBaseSearch::GetBinarySearchArea()
{
	m_fSearchArea = fabs(m_fSearchBegin - m_fSearchEnd);
}

void CSttTestBaseSearch::CalLineSearchNextPoint()
{
	if(m_fScanFrom >= m_fScanTo)
	{
		m_fCurrScanVal = m_fScanFrom - m_fStep * m_nStepIndex;
	}
	else
	{
		m_fCurrScanVal = m_fScanFrom + m_fStep * m_nStepIndex;
	}
}

float CSttTestBaseSearch::CalLenForCurrToFromAndTo()
{
	float fLen = fabs(m_fCurrScanVal - m_fScanTo) + fabs(m_fCurrScanVal - m_fScanFrom);

	return fLen;
}

float CSttTestBaseSearch::CalLenForCurrToEnd()
{
	float fLen = fabs(m_fCurrScanVal - m_fScanTo);// + fabs(m_fCurrScanVal - m_fScanFrom);
	return fLen;
}

void CSttTestBaseSearch::SearchSetFromAsCurr()
{
	m_fCurrScanVal = m_fScanFrom;
}

void CSttTestBaseSearch::SearchSetToAsCurr()
{
	m_fCurrScanVal = m_fScanTo;
}

void CSttTestBaseSearch::SearchSetCurrAsBegin()
{
	m_fSearchBegin = m_fCurrScanVal;
}

void CSttTestBaseSearch::SearchSetCurrAsEnd()
{
	m_fSearchEnd = m_fCurrScanVal;
}

void CSttTestBaseSearch::BinarySearchCalCurrByBeginEnd()
{
	m_fCurrScanVal = (m_fSearchBegin +m_fSearchEnd) / 2;
}


void CSttTestBaseSearch::SetSearchBeginValAsActVal()
{
	m_fActValue = m_fSearchBegin;
}

void CSttTestBaseSearch::SetSearchEdnValAsActVal()
{
	m_fActValue = m_fSearchEnd;
}

void CSttTestBaseSearch::SetSearchCurrValAsActVal()
{
	m_fActValue = m_fCurrScanVal;
}
