// EpotoInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DllCallInterface.h"
#include "..\GuideBook\DllCall.h"
#include "..\..\..\Module\MemBuffer\EquationBuffer.h"
#include "..\GuideBook\DataObj.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "..\TestControl/TestControl.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSafetyDllCallMngr
long CSafetyDllCallMngr::g_nSafetyDllCallMngrRef = 0;
CSafetyDllCallMngr* CSafetyDllCallMngr::g_pSafetyDllCallMngr = NULL;

CSafetyDllCallMngr::CSafetyDllCallMngr()
{

}

CSafetyDllCallMngr::~CSafetyDllCallMngr()
{

}


CSafetyDllCallMngr* CSafetyDllCallMngr::Create()
{
	g_nSafetyDllCallMngrRef++;

	if (g_nSafetyDllCallMngrRef == 1)
	{
		g_pSafetyDllCallMngr = new CSafetyDllCallMngr();
	}

	return g_pSafetyDllCallMngr;
}

void CSafetyDllCallMngr::Release()
{
	g_nSafetyDllCallMngrRef--;

	if (g_nSafetyDllCallMngrRef == 0)
	{
		delete g_pSafetyDllCallMngr;
		g_pSafetyDllCallMngr = NULL;
	}
}

BOOL CSafetyDllCallMngr::DllCall(CExBaseObject *pDllCall, CShortDatas *pResult, CExBaseList *pSysParas, CExBaseList *pGlobalDatas)
{
	ASSERT (g_pSafetyDllCallMngr != NULL);
	HINSTANCE hLib = g_pSafetyDllCallMngr->LoadLib(pDllCall);

	if (hLib == NULL)
	{
		return FALSE;
	}

	char *pszRet = g_pSafetyDllCallMngr->DllCall(hLib, pDllCall, pSysParas, pGlobalDatas);

	if (pszRet == NULL)
	{
		return FALSE;
	}

	CEquationBuffer oBuffer(pszRet);
	POS pos = oBuffer.GetHeadPosition();
	CEquationKey *pKey = NULL;
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pKey = (CEquationKey *)oBuffer.GetNext(pos);
		pData = (CShortData*)pResult->FindByID(pKey->GetKeyName());

		if (pData == NULL)
		{
			pData = new CShortData();
			pData->m_strName = pKey->GetKeyName();
			pData->m_strID = pData->m_strName;
			pResult->AddNewChild(pData);
		}

		pData->m_strValue = pKey->GetKeyValue();
	}

	return TRUE;
}

// #define _use_SafetyDllCall_debug_

char* CSafetyDllCallMngr::DllCall(HINSTANCE hLib, CExBaseObject *pDllCall, CExBaseList *pSysParas, CExBaseList *pGlobalDatas)
{
	CDllCall *pTemp = (CDllCall *)pDllCall;
	GB_DLLCALL_FUNC pFunc = NULL;
	char pszFuncName[MAX_PATH];
	CString_to_char(pTemp->m_strFuncName, pszFuncName);

	pFunc = (GB_DLLCALL_FUNC)GetProcAddress(hLib, pszFuncName);

	char *pszRet = NULL;

	if (pFunc == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DLL [%s] Function [%s] not exist!"), pTemp->m_strID, pTemp->m_strFuncName);
		return NULL;
	}

	char pszParaData[1024];
	CalParaData(pDllCall, pszParaData, pSysParas, pGlobalDatas);

	long nRet = 0;

#ifndef _use_SafetyDllCall_debug_
	nRet = pFunc(pszParaData, &pszRet);
#else

#endif

	if (nRet < 0)
	{
		return NULL;
	}
	else
	{
		return pszRet;
	}
}

void CSafetyDllCallMngr::CalParaData(CExBaseObject *pDllCall, char *pszPara, CExBaseList *pSysParas, CExBaseList *pGlobalDatas)
{
	CDllCall *pTemp = (CDllCall *)pDllCall;
	CEquationBuffer oBuffer;
	oBuffer.InitBuffer(pTemp->m_strParaData);
	POS pos = oBuffer.GetHeadPosition();
	CEquationKey *pKey = NULL;
	CString strValue, strName;
	CString strParaData;

#ifndef GUIDEBOOK_DEV_MODE
	CExBaseList *pDevice = (CExBaseList*)pSysParas->GetParent();
	CGbItemBase *pSafety = (CGbItemBase*)pDllCall->GetParent();
	CExBaseObject *pGuideBook = (CExBaseObject*)pSafety->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestComtrol = (CTestControl*)pGuideBook->GetParent();
#endif

	while (pos != NULL)
	{
		pKey = (CEquationKey *)oBuffer.GetNext(pos);
		pKey->GetKeyValue(strValue);
		pKey->GetKeyName(strName);

		if (IsStringNumber(strValue))
		{
			strParaData.AppendFormat(_T("%s=%s;"), strName, strValue);
		}
#ifndef GUIDEBOOK_DEV_MODE
		else if (pTestComtrol->Parse_Item_File_Path(pSafety, strValue, strValue))
		{
			CreateAllDirectories(strValue);
			strParaData.AppendFormat(_T("%s=%s;"), strName, strValue);
		}
		else if (pTestComtrol->Parse_Report_File_Path(pSafety, strValue, strValue))
		{
			CreateAllDirectories(strValue);
			strParaData.AppendFormat(_T("%s=%s;"), strName, strValue);
		}
#endif
		else
		{
			CDataObj *pDataObj = (CDataObj*)pSysParas->FindByID(strValue);

			if (pDataObj == NULL)
			{
				CDvmData *pDvmData = (CDvmData*)pGlobalDatas->FindByID(strValue);

				if (pDvmData == NULL)
				{
					strParaData.AppendFormat(_T("%s=%s;"), strName, strValue);
				}
				else
				{
					strParaData.AppendFormat(_T("%s=%s;"), strName, pDvmData->m_strValue);
				}
			}
			else
			{
				strParaData.AppendFormat(_T("%s=%s;"), strName, pDataObj->m_strValue);
			}
		}
	}

	CString_to_char(strParaData, pszPara);
}

HINSTANCE CSafetyDllCallMngr::LoadLib(CExBaseObject *pDllCall)
{
	CString strPath;
	CDllCall *pTemp = (CDllCall *)pDllCall;

	strPath = pTemp->GetDllFilePath();

	if (!pTemp->IsDllPathValid(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DLL [%s] not exist!"), strPath);
		return NULL;
	}

	HINSTANCE hLib = FindLib(strPath);

	if (hLib == NULL)
	{
		CDllLoadObj *pDllLib = AddLib(strPath);
		hLib = pDllLib->GetLibInstance();
	}

	if (hLib == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Load DLL [%s] failed!"), strPath);
	}

	return hLib;
}
