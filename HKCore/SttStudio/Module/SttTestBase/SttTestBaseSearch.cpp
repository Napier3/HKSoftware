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

	//�������յ�, ��������
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

	//��ǰ�㵽��ʼ�㡢�յ�ĳ��Ⱥͣ�������㵽�յ�ĳ���
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
	//������һ��������
	CalLineSearchNextPoint();

	if(IsLinerSearchOutEnd())//�����յ㣬���ص�����Ϊ��ǰ������
	{
		SearchSetToAsCurr();
	}

	return TRUE;
}

BOOL CSttTestBaseSearch::SearchNext_BinarySearch()
{
	//*Begin*---------*Curr*-------*end*

	//��ɵ�һ�������������һ����Ϊ*end*
	if (m_nTripFlagTo == -1)
	{
		SearchSetToAsCurr();
		return TRUE;
	}

	//�������㼰�Ժ�Ĳ��Ե㣬�۰�����

	if (m_nTripFlagCurr == m_nTripFlagFrom)
	{//��ǰ������ʼ��Ķ������һ�£�*Begin*=��ǰ��
		SearchSetCurrAsBegin();
	}
	else
	{//��ǰ������ʼ��Ķ��������һ�£�*end*=��ǰ��
		SearchSetCurrAsEnd();
	}

	BinarySearchCalCurrByBeginEnd();
	GetBinarySearchArea();

	return TRUE;
}

BOOL CSttTestBaseSearch::IsSearchFinished_LinerSearch(int nTripFlag)
{
	BOOL bEndFlag = FALSE;

	//�ж��Ƿ�����һ����
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

	if (m_nTripFlagFrom == -1)  //��һ�����Ե�
	{
		m_nTripFlagFrom = nTripFlag;
		m_nTripFirst = nTripFlag;  //��¼��һ����Ķ���״̬
		return bEndFlag;
	}

	if (m_nTripFlagTo == -1) //�ڶ������Ե�
	{
		m_nTripFlagTo = nTripFlag;

		if (m_nTripFlagFrom == m_nTripFlagTo)//���������յ�Ķ��������ͬ����������
		{
			m_nActFlag = ACTFLAG_FINISH; //����/δ����
			bEndFlag = TRUE;
			return bEndFlag;
		}
	}

	//�����������ĳ���
	GetBinarySearchArea();

	if (m_fSearchArea > m_fStep)
	{
		bEndFlag = FALSE;
		return bEndFlag;
	}

	//*Begin*---------*Curr*-------*end*
	//j���㶯��ֵ
	m_nActFlag = ACTFLAG_ACT;

	if (m_nStepIndex % 2 == 0)
	{//*Begin*==>>*Curr*
		if (m_nTripFlagCurr == m_nTripFlagFrom)
		{//��ǰ��Ķ����������ʼ��Ķ������һ�£���¼����ֵΪ*end*
			SetSearchEdnValAsActVal();
		}
		else
		{//��ǰ��Ķ����������ʼ��Ķ��������һ�£���¼����ֵΪ*curr*
			SetSearchCurrValAsActVal();
		}		
	}
	else
	{//*end*==>>*Curr*
		if (m_nTripFlagCurr == m_nTripFlagTo)
		{//��ǰ��Ķ����������ʼ��Ķ������һ�£���¼����ֵΪ*end*
			SetSearchCurrValAsActVal();
		}
		else
		{//��ǰ��Ķ����������ʼ��Ķ��������һ�£���¼����ֵΪ*curr*
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

	fSteps += 2;  //�����յ�������

	return fSteps;
}



//////////////////////////////////////////////////////////////////////////
//����������Ҫʵ�ֵĺ���

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
