#pragma once

#include "PpEngineDataType.h"

#include "../../../Module/DataMngr/DataTypes.h"


#define SAFETY_DATAMODE_LIST     0
#define SAFETY_DATAMODE_QRCODE  1
#define SAFETY_DATAMODE_SCRIPT   2
#define SAFETY_DATAMODE_DLLCALL  3

#define SAFETY_DLLCALL_PARATYPE_NONE		0
#define SAFETY_DLLCALL_PARATYPE_FILE		1
#define SAFETY_DLLCALL_PARATYPE_TEXT		2

class CGbParaTypeMngr
{
private:
	CGbParaTypeMngr(void);
	virtual ~CGbParaTypeMngr(void);

public:
	static long g_nGbParaTypeMngrRef;
	static CGbParaTypeMngr *g_pGbParaTypeMngr;

	static CGbParaTypeMngr* Create();
	static void Release();
	
public:
	static CExBaseList* GetSafetyType()				{		return &(g_pGbParaTypeMngr->m_oSafetyType);		}
	static CExBaseList* GetSafetyDllCallParaType()	{		return &(g_pGbParaTypeMngr->m_oSafetyDllCallParaType);		}
	static CExBaseList* GetPpEngineType()	{		return &(g_pGbParaTypeMngr->m_oPpEngineType);		}
	static CDvmDataset* GetDsEngineConfig()	{		return g_pGbParaTypeMngr->m_oPpEngineType.GetDsEngineConfig();		}


private:
	CDataType m_oSafetyType;
	CDataType m_oSafetyDllCallParaType;
	CPpEngineDataType m_oPpEngineType;

	void InitSafetyDllCallParaType();
	void InitSafetyType();
	void InitPpEngineType();


//////////////////////////////////////////////////////////////////////////
public:
	//Safety类型
	static const CString g_strDataMode_List;
	static const CString g_strDataMode_BarCode;
	static const CString g_strDataMode_Script;
	static const CString g_strDataMode_DllCall;

	//DLLCALL参数类型
	static const CString g_strDllCallParaTypeNone;
	static const CString g_strDllCallParaTypeFile;
	static const CString g_strDllCallParaTypeText;

};

//Safety类型
inline BOOL Gb_IsSafetyList(const CString &strType)
{
	return (strType == CGbParaTypeMngr::g_strDataMode_List);
}

inline BOOL Gb_IsSafetyTable(const CString &strType)
{
	return (strType == CGbParaTypeMngr::g_strDataMode_BarCode);
}

inline BOOL Gb_IsSafetyScript(const CString &strType)
{
	return (strType == CGbParaTypeMngr::g_strDataMode_Script);
}

inline BOOL Gb_IsSafetyDllCall(const CString &strType)
{
	return (strType == CGbParaTypeMngr::g_strDataMode_DllCall);
}

inline CString Gb_GetSafetyType(long nType)
{
	switch (nType)
	{
	case SAFETY_DATAMODE_LIST:
		return CGbParaTypeMngr::g_strDataMode_List;
		break;

	case SAFETY_DATAMODE_QRCODE:
		return CGbParaTypeMngr::g_strDataMode_BarCode;
		break;

	case SAFETY_DATAMODE_SCRIPT:
		return CGbParaTypeMngr::g_strDataMode_Script;
		break;

	case SAFETY_DATAMODE_DLLCALL:
		return CGbParaTypeMngr::g_strDataMode_DllCall;
		break;

	default:
		return CGbParaTypeMngr::g_strDataMode_List;
		break;
	}

}

inline long Gb_GetSafetyType(const CString &strType)
{
	if (strType == CGbParaTypeMngr::g_strDataMode_List)
	{
		return SAFETY_DATAMODE_LIST;
	}

	if (strType == CGbParaTypeMngr::g_strDataMode_BarCode)
	{
		return SAFETY_DATAMODE_QRCODE;
	}

	if (strType == CGbParaTypeMngr::g_strDataMode_Script)
	{
		return SAFETY_DATAMODE_SCRIPT;
	}

	if (strType == CGbParaTypeMngr::g_strDataMode_DllCall)
	{
		return SAFETY_DATAMODE_DLLCALL;
	}

	return SAFETY_DATAMODE_LIST;
}

//DLLCALL参数类型
inline BOOL Gb_IsSafetyDllCallParaNone(const CString &strParaType)
{
	return (strParaType == CGbParaTypeMngr::g_strDllCallParaTypeNone);
}

inline BOOL Gb_IsSafetyDllCallParaFile(const CString &strParaType)
{
	return (strParaType == CGbParaTypeMngr::g_strDllCallParaTypeFile);
}

inline BOOL Gb_IsSafetyDllCallParaText(const CString &strParaType)
{
	return (strParaType == CGbParaTypeMngr::g_strDllCallParaTypeText);
}

inline CString Gb_GetSaftyDllCallParaType(long nParaType)
{
	switch (nParaType)
	{
	case SAFETY_DLLCALL_PARATYPE_NONE:
		return CGbParaTypeMngr::g_strDllCallParaTypeNone;
		break;

	case SAFETY_DLLCALL_PARATYPE_FILE	:
		return CGbParaTypeMngr::g_strDllCallParaTypeFile;
		break;

	case SAFETY_DLLCALL_PARATYPE_TEXT:
		return CGbParaTypeMngr::g_strDllCallParaTypeText;
		break;

	default:
		return CGbParaTypeMngr::g_strDllCallParaTypeNone;
		break;
	}
}


inline long Gb_GetSaftyDllCallParaType(const CString &strParaType)
{
	if (strParaType == CGbParaTypeMngr::g_strDllCallParaTypeNone)
	{
		return SAFETY_DLLCALL_PARATYPE_NONE;
	}

	if (strParaType == CGbParaTypeMngr::g_strDllCallParaTypeFile)
	{
		return SAFETY_DLLCALL_PARATYPE_FILE;
	}

	if (strParaType == CGbParaTypeMngr::g_strDllCallParaTypeText)
	{
		return SAFETY_DLLCALL_PARATYPE_TEXT;
	}

	return SAFETY_DLLCALL_PARATYPE_NONE;
}

