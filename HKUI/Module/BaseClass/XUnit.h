#pragma once

#define  _XUNITS_MAX_COUNT_  80

class CXUnit
{
public:
	CXUnit();

	~CXUnit()
	{

	}

	static CString g_strXUnit[_XUNITS_MAX_COUNT_];

public:
	CString GetXUnite(int nEnumType)
	{
		if (nEnumType>0&&nEnumType<=_XUNITS_MAX_COUNT_)
		{
			return g_strXUnit[nEnumType-1];
		}
		return "";
	}

	int GetXUniteIndex(CString strUnite)
	{
		for (int i=0;i<_XUNITS_MAX_COUNT_;i++)
		{
			if (strUnite==g_strXUnit[i])
				return i+1;
		}

		return 65535;
	}
	
	BOOL IsUnit(const CString &strText)
	{
		for (int i=0;i<_XUNITS_MAX_COUNT_;i++)
		{
			if (strText==g_strXUnit[i])
				return TRUE;
		}
		
		return FALSE;
	}
};
