#include "stdafx.h"
#include "TestMacroInterface.h"
#include "../API/GlobalConfigApi.h"
#include "TestMacrosFileMngr.h"
#include "../XLanguage/XLanguageResource.h"
#include "../XLanguage/XLanguageMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

class _CTM_TestMacros_Creator : public CExBaseList
{
private:
	_CTM_TestMacros_Creator()
	{
		CTestMacroXmlRWKeys::Create();
	}

	virtual ~_CTM_TestMacros_Creator()
	{
		DeleteAll();
		CTestMacroXmlRWKeys::Release();
	}

	CTestMacros* CreateMacros(const CString &strMacroFile, const CString &strMacroFileID)
	{
		//2018-12-30  lijunqing
// 		CString strPath;
// 		strPath.Format(_T("%s%s"), CString(_P_GetConfigPath()), strMacroFile);
		CTestMacros *pTestMacros = (CTestMacros*)FindByName(strMacroFile); //2021-8-14  lijunqing 避免重复创建、打开

		if (pTestMacros != NULL)
		{
			return pTestMacros;
		}
		
		pTestMacros = new CTestMacros();
		pTestMacros->OpenTestMacroFile(strMacroFile, strMacroFileID);
		CTestMacroXmlRWKeys *pXmlKeys = CTestMacroXmlRWKeys::g_pXmlKeys;
// 		CString strFormatKey;
// 		strFormatKey = pXmlKeys->m_strFormatKey;
// 		pXmlKeys->m_strFormatKey = L"create-group";
// 		pTestMacros->OpenXmlFile(strPath, pXmlKeys->CTestMacrosKey(), pXmlKeys);
// 		pXmlKeys->m_strFormatKey = strFormatKey.AllocSysString();
// 		pTestMacros->m_strID = strMacroFile;
// 		pTestMacros->m_strName = strMacroFile;
		AddNewChild(pTestMacros);
//		pTestMacros->m_strMacroFile = strMacroFile;

		//数据类型文件
		CTestMacrosFile* pFind = CTestMacrosFileMngr::g_pTestMacrosFileMngr->FindByFile(strMacroFile);

		if (pFind != NULL)
		{
			pTestMacros->OpenDataTypeFile(pFind->DataTypeFile(TRUE));
		}

		//xlang_TranslateByResourceFile(pTestMacros, strMacroFile);
		//20161212 ： 考虑直接使用导出的TestMacro文件，不进行转换
#ifndef NOT_USE_XLANGUAGE
#ifndef _PSX_QT_LINUX_
        xlang_TranslateByResourceFileEx(pTestMacros, strMacroFile);
#endif
#endif

		return pTestMacros;
	}

	static long g_nTestMacrosCreatorRef;

public:
	static _CTM_TestMacros_Creator* g_pTestMacrosCreator;
	//static const CString g_strTestMacrosFile;

	static _CTM_TestMacros_Creator* Create()
	{
		g_nTestMacrosCreatorRef++;

		if (g_nTestMacrosCreatorRef == 1)
		{
			g_pTestMacrosCreator = new _CTM_TestMacros_Creator();
		}

		return g_pTestMacrosCreator;
	}

	static void Release()
	{
		g_nTestMacrosCreatorRef--;

		if (g_nTestMacrosCreatorRef == 0)
		{
			delete g_pTestMacrosCreator;
			g_pTestMacrosCreator = NULL;
		}
	}

	//根据测试功能文件创建测试功能集合对象
	static CTestMacros * GetTestMacros(CString &strMacroFile)
	{
		CString strFile = strMacroFile;
		CTestMacrosFile *pMacroFile = NULL;

		if (strFile.GetLength() == 0)
		{
			strFile = TM_GetDefaultTestMacrosFile();
		}
		//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
		if (! TM_IsTestMacroFile(strFile) )
		{
			//2017-10-29  测试功能ID
			strFile = CTestMacrosFileMngr::FindTestMacroFileByID(strMacroFile, &pMacroFile);
		}
		ASSERT (g_pTestMacrosCreator != NULL);

		if (g_pTestMacrosCreator == NULL)
		{
			return NULL;
		}

		CTestMacros *p = (CTestMacros*)g_pTestMacrosCreator->FindByID(strFile);

		if (p == NULL)
		{
			if (pMacroFile != NULL)
			{
				p = g_pTestMacrosCreator->CreateMacros(strFile, pMacroFile->m_strID);
				p->m_strProgID = pMacroFile->ActiveMacroTestID();
			}
			else
			{
				p = g_pTestMacrosCreator->CreateMacros(strFile, _T(""));
				pMacroFile = CTestMacrosFileMngr::g_pTestMacrosFileMngr->FindByFile(strMacroFile);

				if (pMacroFile != NULL)
				{
					strMacroFile = pMacroFile->m_strID;
				}
			}
		}

		if (p != NULL && pMacroFile != NULL)
		{
			p->m_strID = pMacroFile->m_strID;
		}
		
		return p;
	}

	static CTestMacrosFile* GetTestMacrosFile(CString &strMacroFile)
	{
		CString strFile = strMacroFile;
		CTestMacrosFile *pMacroFile = NULL;

		if (strFile.GetLength() == 0)
		{
			strFile = TM_GetDefaultTestMacrosFile();
		}

		//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
		if (! TM_IsTestMacroFile(strFile) )
		{
			//2017-10-29  测试功能ID
			strFile = CTestMacrosFileMngr::FindTestMacroFileByID(strMacroFile, &pMacroFile);
		}

		return pMacroFile;
	}

//2021-8-15  lijunqing
#ifndef NOT_USE_TestMacroScriptMngr
	static CTestMacroScriptMngr* GetTestMacroScriptMngr(CString &strMacroFile)
	{
		CTestMacros *p = GetTestMacros(strMacroFile);

		if (p == NULL)
		{
			return NULL;
		}
		
		return GetTestMacroScriptMngr(p);
	}

	static CTestMacroScriptMngr* GetTestMacroScriptMngr(CTestMacros *pMacros)
	{
		CTestMacroScriptMngr *pScriptMngr = (CTestMacroScriptMngr*)pMacros->GetMacroScriptMngr();

		if (pScriptMngr != NULL)
		{
			return pScriptMngr;
		}

		pScriptMngr = new CTestMacroScriptMngr();
		CString strFile;
        strFile.Format(_T("%sScript.xml"), pMacros->m_strID.GetString());
		pScriptMngr->m_strScriptFile = strFile;
		CString strPath;
		strPath = _P_GetConfigPath();
        strPath.AppendFormat(_T("%s\\%s"),  pMacros->m_strID.GetString(), strFile.GetString());
		BOOL bTrue = pScriptMngr->OpenXmlFile(strPath, CMacroScriptMngrXmlRWKeys::CTestMacroScriptMngrKey(), CMacroScriptMngrXmlRWKeys::g_pXmlKeys);
		pMacros->SetMacroScriptMngr(pScriptMngr);
	
		if (!bTrue)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_AddScriptFail.GetString()/* _T("加载功能脚本文件[%s]失败")*/, strPath.GetString());
        }

		return pScriptMngr;
	}

	static CTestMacroScript* GetTestMacroScript(CTestMacro *pMacro)
	{
		CTestMacros *pParent = (CTestMacros*)pMacro->GetParent();
		CTestMacroScriptMngr *pScptMngr = GetTestMacroScriptMngr(pParent);

		if (pScptMngr == NULL)
		{
			return NULL;
		}

		return (CTestMacroScript*)pScptMngr->FindByID(pMacro->m_strID);
	}
#endif

};

long _CTM_TestMacros_Creator::g_nTestMacrosCreatorRef = 0;
_CTM_TestMacros_Creator* _CTM_TestMacros_Creator::g_pTestMacrosCreator = NULL;
// const CString _CTM_TestMacros_Creator::g_strTestMacrosFile = _T("TestMacro.xml");


// CString g_strFormatMacroNotExist =  g_sLangTxt_TestFctnUnExist/*_T("测试功能\"%s\"不存在")*/;

void TM_GetTestMacroParasValues(CTestMacros *pTestMacros, const CString &strMacroID, CValues *pValues)
{
	ASSERT (_CTM_TestMacros_Creator::g_pTestMacrosCreator != NULL);

	CTestMacro *pMacro = NULL;
	pMacro = (CTestMacro*)pTestMacros->FindByID(strMacroID);
	//ASSERT (pMacro != NULL);

	if (pMacro == NULL)
	{
	}
	else
	{
		TM_GetTestMacroParasValues(pMacro,pValues);
	}
}

void TM_GetTestMacroParasShortDatas(CTestMacros *pTestMacros, const CString &strMacroID, CShortDatas  *pDatas)
{
	ASSERT (_CTM_TestMacros_Creator::g_pTestMacrosCreator != NULL);

	CTestMacro *pMacro = NULL;
	pMacro = (CTestMacro*)pTestMacros->FindByID(strMacroID);
	//ASSERT (pMacro != NULL);

	if (pMacro == NULL)
	{
		//		CLogPrint::LogFormatLevel(XLOGLEVEL_ERROR);
		//		CLogPrint::LogFormatString(g_strFormatMacroNotExist, strMacroID);
	}
	else
	{
		TM_GetTestMacroParasShortDatas(pMacro,pDatas);
	}
}

void TM_GetTestMacroParasValues(CTestMacro *pMacro, CValues *pValues)
{
	ASSERT (pMacro != NULL);
	ASSERT (pValues != NULL);

	if (pMacro == NULL || pValues == NULL)
	{
		return;
	}

	pValues->DeleteAll();//清空pValues；

// 	CShortDatas  *pDatas = NULL;
// 
// 	pDatas = pMacro->GetFaultParas();
// 	pDatas->AppendValues(pValues);
// 
// 	pDatas = pMacro->GetSysParas();
// 	pDatas->AppendValues(pValues);
	pMacro->GetParasValues(pValues);
}

void TM_GetTestMacroParasShortDatas(CTestMacro *pMacro, CShortDatas  *pDesDatas)
{
	ASSERT (pMacro != NULL);
	ASSERT (pDesDatas != NULL);

	if (pMacro == NULL || pDesDatas == NULL)
	{
		return;
	}

	pDesDatas->DeleteAll();//清空pValues；

	CShortDatas  *pDatas = NULL;

	pDatas = pMacro->GetFaultParas();
	pDesDatas->AppendClone(pDatas);

	pDatas = pMacro->GetSysParas();
	pDesDatas->AppendClone(pDatas);
}

CTestMacros* TM_GetTestMacros(CString &strMacroFile)
{
	return _CTM_TestMacros_Creator::GetTestMacros(strMacroFile);
}

CTestMacrosFile* TM_GetTestMacrosFile(CString &strMacroFile)
{
	return _CTM_TestMacros_Creator::GetTestMacrosFile(strMacroFile);
}

//2021-8-15  lijunqing
#ifndef NOT_USE_TestMacroScriptMngr
CTestMacroScriptMngr* TM_GetTestMacroScriptMngr(CString &strMacroFile)
{
	return _CTM_TestMacros_Creator::GetTestMacroScriptMngr(strMacroFile);
}

CTestMacroScriptMngr* TM_GetTestMacroScriptMngr(CTestMacros *pMacros)
{
	return _CTM_TestMacros_Creator::GetTestMacroScriptMngr(pMacros);
}

CTestMacroScript* TM_GetTestMacroScript(CTestMacro *pMacro)
{
	return _CTM_TestMacros_Creator::GetTestMacroScript(pMacro);
}
#endif

CTestMacros * TM_CreateTestMacros()
{
	_CTM_TestMacros_Creator::Create();
	return NULL;
}

void TM_ReleaseTestMacros()
{
	_CTM_TestMacros_Creator::Release();
}


// CString TM_GetDefaultTestMacrosFile()
// {
// 	return _CTM_TestMacros_Creator::g_strTestMacrosFile;
// }

// 
// //查找功能数据接口对象
// CTestMacro*  TM_FindTestMacro(const CString &strMacroID)
// {
// 	ASSERT (_CTM_TestMacros_Creator::g_pTestMacrosCreator != NULL);
// 
// 	CTestMacros * pTestMacros = _CTM_TestMacros_Creator::g_pTestMacrosCreator->GetTestMacros();
// 
// 	CTestMacro *pMacro = NULL;
// 	pMacro = (CTestMacro*)pTestMacros->FindByID(strMacroID);
// 	//ASSERT (pMacro != NULL);
// 
// 	if (pMacro == NULL)
// 	{
// 
// 	}
// 
// 	return pMacro;
// }
