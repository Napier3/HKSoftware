#include "stdafx.h"
#include "XDbSQLXFilter.h"
#include "XDbSQLFieldObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CXDbSQLXFilter::CXDbSQLXFilter()
{
	m_nFilterType = XFILTERTYPE_EQUAL_LONG;
	m_nAndFlg = XFILTER_AND;
}

CXDbSQLXFilter::CXDbSQLXFilter(const CString &strID, long nValue
							   ,long nFilterType,UINT nAnd)
{
	m_strID = strID;
	m_nAndFlg = nAnd;
	m_nFilterType = nFilterType;

	oMySQLFilterValue.nValue = nValue;

    m_strFilterTxt.Format(_T("%s=%d"),m_strID.GetString(),oMySQLFilterValue.nValue);
}

CXDbSQLXFilter::CXDbSQLXFilter(const CString &strID, const CString &strValue
							   ,long nFilterType,UINT nAnd)
{
	m_strID = strID;
	m_nAndFlg = nAnd;
	m_nFilterType = nFilterType;

	oMySQLFilterValue.pString = (CString*)(&strValue);

	if (m_nFilterType == XFILTERTYPE_EQUAL_STRING)
	{
        m_strFilterTxt.Format(_T("%s=\"%s\""),m_strID.GetString(),strValue.GetString());
	}
	else
	{
        m_strFilterTxt.Format(_T("%s LIKE \"%%%s%%\""),m_strID.GetString(),strValue.GetString());
	}
}

CXDbSQLXFilter::CXDbSQLXFilter(const CString &strID, SYSTEMTIME tmBegin, SYSTEMTIME tmEnd
							   ,long nFilterType,UINT nAnd)
{
	m_strID = strID;
	m_nAndFlg = nAnd;
	m_nFilterType = XFILTERTYPE_TIME;

	oMySQLFilterValue.oXFilterTime.tmBegin = tmBegin;
	oMySQLFilterValue.oXFilterTime.tmEnd = tmEnd;

	GetDuringDateString(tmBegin,tmEnd,m_strID,m_strFilterTxt);
}

CXDbSQLXFilter::CXDbSQLXFilter(const CString &strID, long nMin, long nMax
							   ,long nFilterType,UINT nAnd)
{
	m_strID = strID;
	m_nAndFlg = nAnd;
	m_nFilterType = nFilterType;

	if (m_nFilterType == XFILTERTYPE_LONG)
	{
		oMySQLFilterValue.oXFilterLong.nMin = nMin;
		oMySQLFilterValue.oXFilterLong.nMax = nMax;

        m_strFilterTxt.Format(_T("(%s>=%d and %s<=%d)"),m_strID.GetString(),nMin,nMax);
	}
	else
	{
		oMySQLFilterValue.oXFilterLimit.nBeginOffset = nMin;
		oMySQLFilterValue.oXFilterLimit.nCount = nMax;

        m_strFilterTxt.Format(_T("Limit %d,%d"),m_strID.GetString(),nMin,nMax);
	}
}

CXDbSQLXFilter::CXDbSQLXFilter(const CString &strID, double fMin, double fMax
							   ,long nFilterType,UINT nAnd)
{
	m_strID = strID;
	m_nAndFlg = nAnd;
	m_nFilterType = XFILTERTYPE_DOUBLE;

	oMySQLFilterValue.oXFilterDouble.fMin = fMin;
	oMySQLFilterValue.oXFilterDouble.fMax = fMax;

    m_strFilterTxt.Format(_T("(%s>=%f and %s<=%f)"),m_strID.GetString(),fMin,fMax);
}

CXDbSQLXFilter::~CXDbSQLXFilter()
{

}
