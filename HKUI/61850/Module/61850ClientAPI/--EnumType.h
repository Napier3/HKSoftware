#pragma once

//////////////////////////////////////////////////////////////////////////
enum tag_Mod
{
	Mod_On = 1,
	Mod_Blocked,
	Mod_Test,
	Mod_Test_Blocked,
	Mod_Off
};

class CMod
{
public:
	CMod()
	{
		strMod[0] = "on";
		strMod[1] = "blocked";
		strMod[2] = "test";
		strMod[3] = "test/blocked";
		strMod[4] = "off";
	}
	~CMod()
	{

	}

	CString strMod[5];

public:
	CString GetCR_ModUnite(int nEnumType)
	{
		if (nEnumType>=0&&nEnumType<5)
			return strMod[nEnumType];

		return "";
	}
};

//////////////////////////////////////////////////////////////////////////
class CctlModel
{
public:
	CctlModel()
	{
		strctlModel[0] = "status-only";
		strctlModel[1] = "direct-with-normal-security";
		strctlModel[2] = "sbo-with-normal-security";
		strctlModel[3] = "irect-with-enhanced-security";
		strctlModel[4] = "sbo-with-enhanced-security";
	}
	~CctlModel()
	{

	}

	CString strctlModel[5];

public:
	CString GetctlModelUnite(int nEnumType)
	{
		if (nEnumType>=0&&nEnumType<5)
			return strctlModel[nEnumType];

		return "";
	}
};

//////////////////////////////////////////////////////////////////////////
class CBeh
{
public:
	CBeh()
	{
		strBeh[0] = "on";
		strBeh[1] = "blocked";
		strBeh[2] = "test";
		strBeh[3] = "test/blocked";
		strBeh[4] = "off";
	}
	~CBeh()
	{

	}

	CString strBeh[5];

public:
	CString GetBehUnite(int nEnumType)
	{
		if (nEnumType>=0&&nEnumType<5)
			return strBeh[nEnumType];

		return "";
	}
};

//////////////////////////////////////////////////////////////////////////
class CCR_Health
{
public:
	CCR_Health()
	{
		strCR_Health[0] = "Ok";
		strCR_Health[1] = "Warning";
		strCR_Health[2] = "Alarm";
	}
	~CCR_Health()
	{

	}

	CString strCR_Health[3];

public:
	CString GetCR_HealthUnite(int nEnumType)
	{
		if (nEnumType>=0&&nEnumType<3)
			return strCR_Health[nEnumType];

		return "";
	}
};

//////////////////////////////////////////////////////////////////////////
class CSIUnit
{
public:
	CSIUnit();

	~CSIUnit()
	{

	}

	static CString g_strSIUnit[79];

public:
	CString GetSIUnite(int nEnumType)
	{
		if (nEnumType>0&&nEnumType<=79)
		{
			return g_strSIUnit[nEnumType-1];
		}
		return "";
	}

	int GetSIUniteIndex(CString strUnite)
	{
		for (int i=0;i<79;i++)
		{
			if (strUnite==g_strSIUnit[i])
				return i+1;
		}

		return 65535;
	}
};

//////////////////////////////////////////////////////////////////////////
class CMultiplier
{
public:
	CMultiplier();

	~CMultiplier()
	{

	}

	static CString g_strMultiplier[21];

public:
	CString GetMultiplierUnite(int nEnumType);
	int GetMultiplierUniteIndex(CString strUnite);
};