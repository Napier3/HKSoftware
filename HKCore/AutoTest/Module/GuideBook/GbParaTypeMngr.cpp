#include "StdAfx.h"
#include "GbParaTypeMngr.h"
#include "GbXMLKeys.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long CGbParaTypeMngr::g_nGbParaTypeMngrRef = 0;
CGbParaTypeMngr* CGbParaTypeMngr::g_pGbParaTypeMngr = NULL;

const CString CGbParaTypeMngr::g_strDataMode_List = _T("list");
const CString CGbParaTypeMngr::g_strDataMode_BarCode = _T("barcode");
const CString CGbParaTypeMngr::g_strDataMode_Script = _T("script");
const CString CGbParaTypeMngr::g_strDataMode_DllCall = _T("dllcall");

const CString CGbParaTypeMngr::g_strDllCallParaTypeNone = _T("none");
const CString CGbParaTypeMngr::g_strDllCallParaTypeFile = _T("file");
const CString CGbParaTypeMngr::g_strDllCallParaTypeText = _T("text");

CGbParaTypeMngr::CGbParaTypeMngr(void)
{
	InitSafetyDllCallParaType();
	InitSafetyType();
	InitPpEngineType();
}

CGbParaTypeMngr::~CGbParaTypeMngr(void)
{
	
}


CGbParaTypeMngr* CGbParaTypeMngr::Create()
{
	g_nGbParaTypeMngrRef++;

	if (g_nGbParaTypeMngrRef == 1)
	{
		g_pGbParaTypeMngr = new CGbParaTypeMngr();
	}

	return g_pGbParaTypeMngr;
}

void CGbParaTypeMngr::Release()
{
	g_nGbParaTypeMngrRef--;

	if (g_nGbParaTypeMngrRef == 0)
	{
		delete g_pGbParaTypeMngr;
		g_pGbParaTypeMngr = NULL;
	}
}

void CGbParaTypeMngr::InitSafetyDllCallParaType()
{
	m_oSafetyDllCallParaType.AddNewValue(/*_T("无")*/g_sLangTxt_None, _T("none"), 0);
	m_oSafetyDllCallParaType.AddNewValue(/*_T("文件")*/g_sLangTxt_File, _T("file"), 1);
	m_oSafetyDllCallParaType.AddNewValue(/*_T("文本")*/g_sLangTxt_Text, _T("text"), 2);
}

void CGbParaTypeMngr::InitSafetyType()
{
	m_oSafetyType.AddNewValue(g_strDataMode_List, g_strDataMode_List, 0);
	m_oSafetyType.AddNewValue(g_strDataMode_BarCode, g_strDataMode_BarCode, 1);
	m_oSafetyType.AddNewValue(g_strDataMode_Script, g_strDataMode_Script, 2);
	m_oSafetyType.AddNewValue(g_strDataMode_DllCall, g_strDataMode_DllCall, 3);
}

void CGbParaTypeMngr::InitPpEngineType()
{
	m_oPpEngineType.InitPpEngineType();
}

