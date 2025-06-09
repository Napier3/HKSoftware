#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/GpsPcTime/GpsPcTime.h"

#define SDVT_GPSTIME             0
#define SDVT_PCTIME               1
#define SDVT_GPSPCTIMEMAP    2
#define SDVT_VALUE                 3

class CScriptDataVariable : public CExBaseObject
{
public:
	CScriptDataVariable(UINT nType, const CString &strVar, LPVOID pValue);
	~CScriptDataVariable();

	BOOL IsTime()
	{
		return (m_nType == SDVT_GPSTIME || m_nType == SDVT_PCTIME);
	}

	void SetValue(LPVOID pValue)
	{
		if (m_pVariableValue != NULL)
		{
			if (m_nType == SDVT_GPSTIME)
			{
				PGPSTIME ptm = (PGPSTIME)m_pVariableValue;
				free(ptm);
			}

			if (m_nType == SDVT_PCTIME)
			{
				PPCTIME ptm = (PPCTIME)m_pVariableValue;
				free(ptm);
			}
		}
		m_pVariableValue = NULL;

		m_pVariableValue = pValue;
	}

	CGpsPcTime* GetGpsPcTime()
	{
		CGpsPcTime *pTime = NULL;

		if (m_nType == SDVT_GPSTIME)
		{
			pTime = new CGpsPcTime(* ((PGPSTIME)m_pVariableValue));
		}
		else if (m_nType == SDVT_PCTIME)
		{
			pTime = new CGpsPcTime(*((PPCTIME)m_pVariableValue));
		}
		else
		{
		}

		return pTime;
	}

public:
	UINT m_nType;
	LPVOID m_pVariableValue;

private:
	CScriptDataVariable(){}
};


class CScriptDataVariables : public CExBaseList
{
public:
	CScriptDataVariables();
	~CScriptDataVariables(void);

public:
	void AddScriptDataVariable(UINT nType, const CString &strVar, LPVOID pValue);

};