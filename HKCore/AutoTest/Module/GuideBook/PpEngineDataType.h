#pragma once

#include "../../../Module/DataMngr/DataType.h"
#include "../../../Module/DataMngr/DvmDataset.h"

static const CString g_strIotEngineProgID = _T("IotEngine.PoEngine");
static const CString g_strPpEngineProgID = _T("PpEngine.PoEngine");
static const CString g_strPpEngineProgIDMmsOld = _T("PpMmsEngine.PpEngine");
static const CString g_strPpEngineProgIDMms = _T("PpMmsEngine.PoEngine");
static const CString g_strPpEngineProgIDDlt = _T("DltEngine.PoEngine");
static const CString g_strPpEngineProgID_None = _T("none");
static const CString g_strPpEngineDataTypeID = _T("PpEngine");
static const CString g_strPpMmsEngineExeName = _T("ppmmsengine.exe");
static const CString g_strPpEngineExeName = _T("ppengine.exe");
static const CString g_strIotEngineExeName = _T("iotengine.exe");

inline CString engine_GetEngineEngineText(const CString &strEngineID)
{
	if (strEngineID == g_strPpEngineProgIDMms)
	{
		return _T("61850MMS");
	}
	else if (strEngineID == g_strPpEngineProgID)
	{
		return g_strPpEngineDataTypeID;
	}
	else
	{
		long nPos = strEngineID.Find('.');

		if (nPos > 0)
		{
			return strEngineID.Left(nPos);
		}
		else
		{
			return strEngineID;
		}
	}
}

class CPpEngineDataType : public CDataType
{
public:
	CPpEngineDataType(void);
	virtual ~CPpEngineDataType(void);

	void InitPpEngineType();
	CDvmDataset* GetDsEngineConfig()	{		return &m_oDsEngineConfig;		}

private:
	CDvmDataset m_oDsEngineConfig;

};
