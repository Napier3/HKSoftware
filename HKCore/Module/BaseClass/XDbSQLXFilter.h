#ifndef _XDbSQLXFilter_H__
#define _XDbSQLXFilter_H__ 

#include "ExBaseObject.h"

#define XFILTERTYPE_EQUAL_LONG		0
#define XFILTERTYPE_EQUAL_STRING	1
#define XFILTERTYPE_KEY_STRING		2
#define XFILTERTYPE_TIME	3
#define XFILTERTYPE_LONG	4
#define XFILTERTYPE_DOUBLE	5
#define XFILTERTYPE_LIMIT	6

#define XFILTER_AND	0
#define XFILTER_OR	1

struct XFilterTime
{
	SYSTEMTIME tmBegin;
	SYSTEMTIME tmEnd;
};

struct XFilterLong
{
	long nMin;
	long nMax;
};

struct XFilterDouble
{
	double fMin;
	double fMax;
};

struct XFilterLimit
{
	long nBeginOffset;
	long nCount;
};

union UNION_FILTERVALUE
{
	long nValue;
	CString *pString;
	XFilterTime oXFilterTime;
	XFilterLong oXFilterLong;
	XFilterDouble oXFilterDouble;
	XFilterLimit oXFilterLimit;
};
#define XFILTERTYPE_EQUAL_LONG		0
#define XFILTERTYPE_EQUAL_STRING	1
#define XFILTERTYPE_KEY_STRING		2
#define XFILTERTYPE_TIME	3
#define XFILTERTYPE_LONG	4
#define XFILTERTYPE_DOUBLE	5
#define XFILTERTYPE_LIMIT	6

#define XFILTER_AND	0
#define XFILTER_OR	1
class CXDbSQLXFilter : public CExBaseObject
{
public:
	CXDbSQLXFilter();	
	CXDbSQLXFilter(const CString &strID, long nValue
		,long nFilterType = XFILTERTYPE_EQUAL_LONG,UINT nAnd = XFILTER_AND);
	CXDbSQLXFilter(const CString &strID, const CString &strValue
		,long nFilterType = XFILTERTYPE_EQUAL_STRING,UINT nAnd = XFILTER_AND);
	CXDbSQLXFilter(const CString &strID, SYSTEMTIME tmBegin, SYSTEMTIME tmEnd
		,long nFilterType = XFILTERTYPE_TIME,UINT nAnd = XFILTER_AND);
	CXDbSQLXFilter(const CString &strID, long nMin, long nMax
		,long nFilterType = XFILTERTYPE_LONG,UINT nAnd = XFILTER_AND);
	CXDbSQLXFilter(const CString &strID, double fMin, double fMax
		,long nFilterType = XFILTERTYPE_DOUBLE,UINT nAnd = XFILTER_AND);

	virtual ~CXDbSQLXFilter();

public:
	UNION_FILTERVALUE oMySQLFilterValue;
	long m_nFilterType;
	UINT m_nAndFlg;

	CString m_strFilterTxt;
};


#endif
