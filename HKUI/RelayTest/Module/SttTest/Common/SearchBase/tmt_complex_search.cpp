//#include "StdAfx.h"
#include "../../../../../Module/OSInterface/QT/stdafx.h"
#include "tmt_complex_search.h"


tmt_complex_search::tmt_complex_search(void)
{
	m_fScanFromAngle = 0;
	m_fScanToAngle = 0;
	m_fCurrScanValAngle = 0;

	m_fSearchBeginAngle = 0;
	m_fSearchEndAngle = 0;

	m_fAngle = 0;

	SetBinarySearchMode();

	m_fLineAngle = 0;              //ËÑË÷ÏßµÄ½Ç¶È
}

tmt_complex_search::~tmt_complex_search(void)
{
}

void tmt_ComplexSearch::InitSearch()
{
	tmt_SearchBase::InitSearch();

	m_fCurrScanValAngle = m_fScanFromAngle;
	m_fActValueAngle = 0;

	m_fSearchBeginAngle = m_fScanFromAngle;
	m_fSearchEndAngle = m_fScanToAngle;

	Complex_Sub( m_fScanTo, m_fScanToAngle, m_fScanFrom, m_fScanFromAngle,m_fSerchOriginLength, m_fLineAngle);
	m_fSearchArea = (float)m_fSerchOriginLength;
	Complex_Sub( m_fScanTo, m_fScanToAngle, m_fScanFrom, m_fScanFromAngle,m_fSerchOriginLength, m_fLineAngle);
	m_fSearchArea = (float)m_fSerchOriginLength;
}
float tmt_ComplexSearch::GetActValueAngle()		
{	
	if (IsBinarySearch())
	{
		if (m_nTripFirst == m_nTripFlagCurr)
		{
			return m_fActValueAngle;
		}
		else
		{
			if (m_nTripFirst == m_nTripFlagFrom)
			{
				return m_fSearchBeginAngle;
			}
			else
			{
				return m_fSearchEndAngle;
			}
		}
	}
	else
	{
		return m_fActValueAngle;
	}
}

void  tmt_ComplexSearch::GetBinarySearchArea()
{
	CComplexNumber c1(m_fSearchBegin, m_fSearchBeginAngle, COMPLEX_MODE_DEGREE);
	CComplexNumber c2(m_fSearchEnd, m_fSearchEndAngle, COMPLEX_MODE_DEGREE);

	c2 -= c1;
	m_fSearchArea = (float)c2.GetModulus();
}

void tmt_ComplexSearch::CalLineSearchNextPoint()
{
	CComplexNumber c1(m_fScanFrom, m_fScanFromAngle, COMPLEX_MODE_DEGREE);
	double dLen = m_fStep * m_nStepIndex;
	CComplexNumber c2(dLen, m_fLineAngle, COMPLEX_MODE_DEGREE);
	c1 += c2;

	double dValue, dAngle;
	c1.GetValueAngle(dValue, dAngle);
	m_fCurrScanVal = (float)dValue;
	m_fCurrScanValAngle = (float)dAngle;
}

void tmt_ComplexSearch::SearchSetFromAsCurr()
{
	m_fCurrScanVal = m_fScanFrom;
	m_fCurrScanValAngle = m_fScanFromAngle;
}

void tmt_ComplexSearch::SearchSetToAsCurr()
{
	m_fCurrScanVal = m_fScanTo;
	m_fCurrScanValAngle = m_fScanToAngle;
}

void tmt_ComplexSearch::SearchSetCurrAsBegin()
{
	m_fSearchBegin = m_fCurrScanVal;
	m_fSearchBeginAngle = m_fCurrScanValAngle;
}

void tmt_ComplexSearch::SearchSetCurrAsEnd()
{
	m_fSearchEnd = m_fCurrScanVal;
	m_fSearchEndAngle = m_fCurrScanValAngle;
}

void tmt_ComplexSearch::BinarySearchCalCurrByBeginEnd()
{
	CComplexNumber c1(m_fSearchBegin, m_fSearchBeginAngle, COMPLEX_MODE_DEGREE);
	CComplexNumber c2(m_fSearchEnd, m_fSearchEndAngle, COMPLEX_MODE_DEGREE);
	c2 -= c1;
	double dLen = 0;
	double dAngle = 0;
	c2.GetValueAngle(dLen, dAngle);
	dLen /= 2;
	
	CComplexNumber c3(dLen, dAngle, COMPLEX_MODE_DEGREE);
	c1 += c3;

	c1.GetValueAngle(dLen, dAngle);
	m_fCurrScanVal = (float)dLen;
	m_fCurrScanValAngle = (float)dAngle;
}

void tmt_ComplexSearch::SetSearchBeginValAsActVal()
{
	m_fActValue = m_fSearchBegin;
	m_fActValueAngle = m_fSearchBeginAngle;
}

void tmt_ComplexSearch::SetSearchEdnValAsActVal()
{
	m_fActValue = m_fSearchEnd;
	m_fActValueAngle = m_fSearchEndAngle;
}

void tmt_ComplexSearch::SetSearchCurrValAsActVal()
{
	m_fActValue = m_fCurrScanVal;
	m_fActValueAngle = m_fCurrScanValAngle;
}

float tmt_ComplexSearch::CalLenForCurrToFromAndTo()
{
	CComplexNumber c1(m_fCurrScanVal, m_fCurrScanValAngle, COMPLEX_MODE_DEGREE);
	CComplexNumber c2(m_fScanFrom, m_fScanFromAngle, COMPLEX_MODE_DEGREE);
	CComplexNumber c3(m_fScanTo, m_fScanToAngle, COMPLEX_MODE_DEGREE);

	c2 -= c1;
	c3 -= c1;

	float fLen = (float)(c2.GetModulus() + c3.GetModulus());
	return fLen;
}


float tmt_ComplexSearch::CalLenForCurrToEnd()
{
	CComplexNumber c1(m_fCurrScanVal, m_fCurrScanValAngle, COMPLEX_MODE_DEGREE);
	//CComplexNumber c2(m_fScanFrom, m_fScanFromAngle, COMPLEX_MODE_DEGREE);
	CComplexNumber c3(m_fScanTo, m_fScanToAngle, COMPLEX_MODE_DEGREE);

	//c2 -= c1;
	c3 -= c1;

	float fLen = (float)(/*c2.GetModulus() + */c3.GetModulus());
	return fLen;
}

