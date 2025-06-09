//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ClassProcotolProjectGlobal.cpp

#include "stdafx.h"
#include "ClassProcotolProjectGlobal.h"
#include "../../../Module/API/FileApi.h"

//////////////////////////////////////////////////////////////////////////
//CClassProcotolProjectXmlRWKeys

CClassProcotolProjectXmlRWKeys* CClassProcotolProjectXmlRWKeys::g_pXmlKeys = NULL;
long CClassProcotolProjectXmlRWKeys::g_nPPRef = 0;


CClassProcotolProjectXmlRWKeys::CClassProcotolProjectXmlRWKeys()
{
	m_strCPpCfgOptrDeviceKey = L"device-optr";
	m_strCPpCfgOptrBatchKey = L"batch-config";
	m_strCPpCfgOptrBatchVarKey = L"batch-var";
	m_strCPpCfgOptrKey = L"optr";
	m_strCPpCfgOptrsKey = L"optrs";
	m_strCPpCfgDeviceKey = L"device";
	m_strCPpCfgOptrsMngrKey = L"optrs-mngr";
	m_strCPpCfgDevicesKey = L"devices";
	m_strCPpProjectConfigKey = L"protocol-project";
	m_strTemplateFileKey = L"template-file";
	m_strDdvmFileKey = L"ddvm-file";
	m_strTDelayKey = L"t-delay";
	m_strRunProcedureKey = L"run-procedure";
	m_strPachageIDKey = L"pkg-id";
	m_strIsRunningKey = L"is-running";
	m_strProcedureKey = L"procedure";
	m_strStepValKey = L"step-val";
	m_strStepCountKey = L"step-count";
}

CClassProcotolProjectXmlRWKeys::~CClassProcotolProjectXmlRWKeys()
{
}

CClassProcotolProjectXmlRWKeys* CClassProcotolProjectXmlRWKeys::Create()
{
	g_nPPRef++;

	if (g_nPPRef == 1)
	{
		g_pXmlKeys = new CClassProcotolProjectXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CClassProcotolProjectXmlRWKeys::Release()
{
	g_nPPRef--;

	if (g_nPPRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CClassProcotolProjectConstGlobal

long CClassProcotolProjectConstGlobal::g_nGlobalRef = 0;
CClassProcotolProjectConstGlobal* CClassProcotolProjectConstGlobal::g_pGlobal = NULL;


CClassProcotolProjectConstGlobal::CClassProcotolProjectConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CClassProcotolProjectConstGlobal::~CClassProcotolProjectConstGlobal()
{
}

CClassProcotolProjectConstGlobal* CClassProcotolProjectConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CClassProcotolProjectConstGlobal();
	}

	return g_pGlobal;
}

void CClassProcotolProjectConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;


CString Pp_GetPopCfgDeviceName(const CString &strPpTemplateFile, const CString &strDeviceFile, CExBaseList *pParent, BOOL bWithPostfix)
{
	CString strPpFileName, strDvmFileName, strID;
	strPpFileName = GetPathFileNameFromFilePathName(strPpTemplateFile);
	strDvmFileName = GetPathFileNameFromFilePathName(strDeviceFile);

	if (!bWithPostfix)
	{
		strPpFileName = ParseFileName(strPpFileName);
		strDvmFileName = ParseFileName(strDvmFileName);
	}

	long nIndex = 1;

	if (strPpFileName.GetLength() > 0)
	{
        strID.Format(_T("%s+%s(%d)"), strPpFileName.GetString(), strDvmFileName.GetString(), nIndex);
	}
	else
	{
        strID.Format(_T("%s(%d)"), strDvmFileName.GetString(), nIndex);
	}

	while (TRUE)
	{
		if (pParent->FindByID(strID) == NULL)
		{
			break;
		}

		if (strPpFileName.GetLength() > 0)
		{
            strID.Format(_T("%s+%s(%d)"), strPpFileName.GetString(), strDvmFileName.GetString(), nIndex);
		}
		else
		{
            strID.Format(_T("%s(%d)"), strDvmFileName.GetString(), nIndex);
		}

		nIndex++;
	}

	return strID;
}
