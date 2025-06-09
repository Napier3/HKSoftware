#include "StdAfx.h"
#include "MtDataTypeMngr.h"
#include "TestMacrosFileMngr.h"
#include "../XLanguage/XLanguageResource.h"
#include "../API/GlobalConfigApi.h"		//yyj

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CMtDataTypeMngr::g_nMtDataTypeMngrRef = 0;
CMtDataTypeMngr* CMtDataTypeMngr::g_pMtDataTypeMngr = NULL;

const CString CMtDataTypeMngr::g_strMtDataType_Number = _T("number");
const CString CMtDataTypeMngr::g_strMtDataType_Set = _T("set");
const CString CMtDataTypeMngr::g_strMtDataType_String = _T("string");
const CString CMtDataTypeMngr::g_strMtDataType_Expression = _T("expression");
const CString CMtDataTypeMngr::g_strMtDataType_IECConfig = _T("iec-config");
const CString CMtDataTypeMngr::g_strMtDataType_ComtradeFile = _T("comtrade-file");
const CString CMtDataTypeMngr::g_strMtDataType_IECExpFile = _T("iec-exp-file");
const CString CMtDataTypeMngr::g_strTestMacroID_IECConfig = _T("IECConfig");
const CString CMtDataTypeMngr::g_strMtDataType_ConfigFile = _T("config-file");

CMtDataTypeMngr::CMtDataTypeMngr(void)
{
	CDataMngrXmlRWKeys::Create();
	m_pIecConfigDataType = NULL;
	m_pComtradeFileDataType = NULL;
	m_pIecExceptionDataType = NULL;
}

CMtDataTypeMngr::~CMtDataTypeMngr(void)
{
	CDataMngrXmlRWKeys::Release();

	if (m_pIecConfigDataType != NULL)
	{
		delete m_pIecConfigDataType;
		m_pIecConfigDataType = NULL;
	}

	if (m_pComtradeFileDataType != NULL)
	{
		delete m_pComtradeFileDataType;
		m_pComtradeFileDataType = NULL;
	}

	if (m_pIecExceptionDataType != NULL)
	{
		delete m_pIecExceptionDataType;
		m_pIecExceptionDataType = NULL;
	}
}


CMtDataTypeMngr* CMtDataTypeMngr::Create()
{
	g_nMtDataTypeMngrRef++;

	if (g_nMtDataTypeMngrRef == 1)
	{
		g_pMtDataTypeMngr = new CMtDataTypeMngr();
	}

	return g_pMtDataTypeMngr;
}

void CMtDataTypeMngr::Release()
{
	g_nMtDataTypeMngrRef--;

	if (g_nMtDataTypeMngrRef == 0)
	{
		delete g_pMtDataTypeMngr;
		g_pMtDataTypeMngr = NULL;
	}
}

#ifndef _PSX_IDE_QT_

void CMtDataTypeMngr::InitDataType(CDataType *pDataType, CXFolder *pFolder)
{
	POS pos = pFolder->GetHeadPosition();
	CXFile *pFile = NULL;
	CXFolder *pFolderTemp = NULL;
	CExBaseObject *p = NULL;
	CString strFilePostfxix;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFILE)
		{
			pFile = (CXFile *)p;
			CDataTypeValue *pNew = new CDataTypeValue();
			//pNew->m_strName = pFile->m_strFileName;
			pNew->m_strName = pFile->m_strName;
			//pNew->m_strID = pFile->m_strID;
			pNew->m_strIndex = pFile->m_strID;
			pNew->m_strID = pFile->GetRelativePath();
			pDataType->AddNewChild(pNew);
		}
	}

	pos = pFolder->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			pFolderTemp = (CXFolder*)p;
			InitDataType(pDataType, pFolderTemp);
		}
	}
}

void CMtDataTypeMngr::InitFileDataTypeByXFileMngr(CXFileMngr *pXFileMngr, CDataType *pDataType, CDataType &oFilePostFixMngr)
{
	InitDataType(pDataType, pXFileMngr);

	//去掉相同的名称
	POS pos = pDataType->GetHeadPosition();
	CDataType oDataTypeTemp;
	CString strName;
	CDataTypeValue *pValue = NULL;
	CString strFilePostfxix;

	while (pos != NULL)
	{
		pValue = (CDataTypeValue *)pDataType->GetNext(pos);
		ParseFileNameAndPostfix(pValue->m_strID, strName, strFilePostfxix);

		///if (oFilePostFixMngr.FindByID(strFilePostfxix) != NULL)
		if (XFile_IsFilePostFixExist(&oFilePostFixMngr, strFilePostfxix))
		{
			if (oDataTypeTemp.FindByName(strName) == NULL)
			{
				pValue->m_strID = strName;
				pValue->m_strName = strName;
				pValue->m_strIndex = strName;
				oDataTypeTemp.AddTail(pValue);
			}
			else
			{
				pDataType->Delete(pValue);
			}
		}
		else
		{
			pDataType->Delete(pValue);
		}
	}

	oDataTypeTemp.RemoveAll();
}
#endif

void CMtDataTypeMngr::InitIecConfigDataType()
{
#ifndef _PSX_IDE_QT_
    if (m_pIecConfigDataType == NULL)
	{
		m_pIecConfigDataType = new CDataType();
		//m_oMacroTestDataTypes.AddNewChild(m_pIecConfigDataType);
		m_pIecConfigDataType->m_strName = g_sLangTxt_IEC61850SetFile/*_T("IEC61850配置文件")*/;
		m_pIecConfigDataType->m_strID = g_strMtDataType_IECConfig;
	}

	m_pIecConfigDataType->DeleteAll();
	CString strPath = mtdt_GetIecConfigFilePath();

	CDataType oDataType;
	CTestMacrosFileMngr::GetAllIecConfigFileType(&oDataType);
	CString strFilePostfxix = _T("ixml");

	CXFileMngr oFileMngr;
	CXFileType *pXFileType = oFileMngr.AddFileType(g_sLangTxt_IEC61850SetFile/*_T("IEC61850配置文件")*/, strFilePostfxix, _T(""), _T(""));

	POS pos = oDataType.GetHeadPosition();
	CDataTypeValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataTypeValue*)oDataType.GetNext(pos);
		pXFileType->AddNewPostfix(pValue->m_strName, pValue->m_strID);
	}

	oFileMngr.SetOnllySearchMainTypeFile(FALSE);
	oFileMngr.InitByXFileTypes();
	oFileMngr.SetLibraryPath(strPath);

	InitFileDataTypeByXFileMngr(&oFileMngr, m_pIecConfigDataType, oDataType);
#endif
}

void CMtDataTypeMngr::InitComtradeFileDataType()
{
#ifndef _PSX_IDE_QT_
    if (m_pComtradeFileDataType == NULL)
	{
		m_pComtradeFileDataType = new CDataType();
		//m_oMacroTestDataTypes.AddNewChild(m_pIecConfigDataType);
		m_pComtradeFileDataType->m_strName = g_sLangTxt_ComtradeFile;
		m_pComtradeFileDataType->m_strID = g_strMtDataType_ComtradeFile;
	}

	m_pComtradeFileDataType->DeleteAll();
	CString strPath = mtdt_GetComtradeFilePath();

	CDataType oDataType;
	oDataType.AddNewValue(_T("cfg"), _T("cfg"), oDataType.GetCount());
	CString strFilePostfxix = _T("cfg");

	CXFileMngr oFileMngr;
	CXFileType *pXFileType = oFileMngr.AddFileType(g_sLangTxt_ComtradeFile
		, strFilePostfxix, _T(""), _T(""));

	POS pos = oDataType.GetHeadPosition();
	CDataTypeValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataTypeValue*)oDataType.GetNext(pos);
		pXFileType->AddNewPostfix(pValue->m_strName, pValue->m_strID);
	}

	oFileMngr.SetOnllySearchMainTypeFile(FALSE);
	oFileMngr.InitByXFileTypes();
	oFileMngr.SetLibraryPath(strPath);

    InitFileDataTypeByXFileMngr(&oFileMngr, m_pComtradeFileDataType, oDataType);
#endif
}

void CMtDataTypeMngr::InitIecExpFileDataType()
{
// 	m_pIecExceptionDataType = new CDataType();
// 	m_oMacroTestDataTypes.AddNewChild(m_pIecExceptionDataType);
// 	m_pIecExceptionDataType->m_strName = _T("IEC61850数字故障文件");
// 	m_pIecExceptionDataType->m_strID = g_strMtDataType_IECExpFile;
// 	m_pIecExceptionDataType->DeleteAll();
// 	CString strPath = mtdt_GetIecConfigFilePath();
// 
// 	CString strFilePostfxix = _T("ste");
// 	CDataType *pFind = (CDataType*)m_oMacroTestDataTypes.FindByName(_T("iec_Exception_File"));
// 
// 	if (pFind != NULL)
// 	{
// 		strFilePostfxix = pFind->m_strID;
// 	}
// 
// 	CXFileMngr oFileMngr;
// 	oFileMngr.Traverse(strPath,strFilePostfxix, FALSE);
// 	POS pos = oFileMngr.GetHeadPosition();
// 	CXFile *pFile = NULL;
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CExBaseObject *)oFileMngr.GetNext(pos);
// 
// 		if (p->GetClassID() == CLASSID_XFILE)
// 		{
// 			pFile = (CXFile*)p;
// 			CDataTypeValue *pNew = new CDataTypeValue();
// 			m_pIecExceptionDataType->AddNewChild(pNew);
// 			pNew->m_strName = pFile->m_strFileName;
// 			pNew->m_strName = pFile->m_strName;
// 			pNew->m_strID = pFile->m_strID;
// 			pNew->m_strIndex = pFile->m_strName;
// 		}
// 	}
}

CString mtdt_GetIecConfigFile(const CString &strFileName)
{
	CString strFile = mtdt_GetIecConfigFilePath();
	strFile += strFileName;
	return strFile;
}

CString mtdt_GetIecConfigFilePath()
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report\\Library\\IEC61850Config\\");
	return strPath;
}

CString mtdt_GetComtradeFilePath()
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report\\Comtrade\\");
	return strPath;
}

//lijq 20200228  all data types are defined in test-macro-file, 
// CDataTypes* CMtDataTypeMngr::GetMacroTestDataTypes()	
// {
// #ifdef _TEST_APP_
// 	ASSERT (FALSE);
// 	return NULL;
// 	////lijq 20200228  all data types are defined in test-macro-file, 
// 	//return &(g_pMtDataTypeMngr->m_oMacroTestDataTypes);	
// #else
// 	return NULL;
// #endif
// }

void CMtDataTypeMngr::InitMacroTestDataTypes(const CString &strDataTypeFile)
{
#ifdef _TEST_APP_
	ASSERT (FALSE);
//lijq 20200228  all data types are defined in test-macro-file, 
// 	CString strFile;
// 	strFile.Format(_T("%s%s"), CString(_P_GetConfigPath()), strDataTypeFile);
// 	g_pMtDataTypeMngr->m_oMacroTestDataTypes.Open(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
#endif

	g_pMtDataTypeMngr->InitIecConfigDataType();
	g_pMtDataTypeMngr->InitComtradeFileDataType();
	g_pMtDataTypeMngr->InitIecExpFileDataType();
}

CString CMtDataTypeMngr::GetDataTypeValueName(const CString &strDataTypeID, const CString &strValue)
{
	ASSERT (g_pMtDataTypeMngr != NULL);
	
	if (g_pMtDataTypeMngr == NULL)
	{
		return strValue;
	}
	
	CDataType *pDataType = g_pMtDataTypeMngr->FindDataType(strDataTypeID);
	
	if (pDataType == NULL)
	{
		return strValue;
	}
	
	CDataTypeValue *pValue = pDataType->FindByIndex(strValue);
	
	if (pValue == NULL)
	{
		return strValue;
	}
	
	return pValue->m_strName;	
}


CString CMtDataTypeMngr::GetDataTypeValueIndex(const CString &strDataTypeID, const CString &strName)
{
	ASSERT (g_pMtDataTypeMngr != NULL);

	if (g_pMtDataTypeMngr == NULL)
	{
		return _T("0");
	}

	CDataType *pDataType = g_pMtDataTypeMngr->FindDataType(strDataTypeID);

	if (pDataType == NULL)
	{
		return _T("0");
	}

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(strName);

	if (pValue == NULL)
	{
		return _T("0");
	}

	return pValue->m_strIndex;	
}

CString CMtDataTypeMngr::GetDataTypeName(const CString &strDataTypeID)
{
	ASSERT (g_pMtDataTypeMngr != NULL);

	if (g_pMtDataTypeMngr == NULL)
	{
		return strDataTypeID;
	}

	CDataType *pDataType = g_pMtDataTypeMngr->FindDataType(strDataTypeID);

	if (pDataType == NULL)
	{
		return strDataTypeID;
	}

	return pDataType->m_strName;	
}

BOOL CMtDataTypeMngr::IsDataTypeCombo(const CString &strDataTypeID)
{
	if (strDataTypeID == g_strMtDataType_Number)
	{
		return FALSE;
	}

	if (strDataTypeID == g_strMtDataType_Set)
	{
		return FALSE;
	}

	if (strDataTypeID == g_strMtDataType_String)
	{
		return FALSE;
	}

	if (strDataTypeID == g_strMtDataType_Expression)
	{
		return FALSE;
	}

	if (strDataTypeID == g_strMtDataType_ConfigFile)
	{
		return FALSE;
	}

	if (strDataTypeID == g_strMtDataType_IECConfig)
	{
		return TRUE;
	}

	if (strDataTypeID == g_strMtDataType_ComtradeFile)
	{
		return TRUE;
	}

	return TRUE;
}

CDataType* CMtDataTypeMngr::FindDataType(const CString &strDataTypeID)
{
	ASSERT (g_pMtDataTypeMngr != NULL);

	if (g_pMtDataTypeMngr == NULL)
	{
		return NULL;
	}

	CDataType *pDataType = NULL;

	if (strDataTypeID == g_strMtDataType_IECConfig)
	{
		pDataType = g_pMtDataTypeMngr->m_pIecConfigDataType;
	}
	else if (strDataTypeID == g_strMtDataType_ComtradeFile)
	{
		pDataType = g_pMtDataTypeMngr->m_pComtradeFileDataType;
	}
	else if (strDataTypeID == g_strMtDataType_IECExpFile)
	{
		pDataType = g_pMtDataTypeMngr->m_pIecExceptionDataType;
	}
	else
	{
#ifdef _TEST_APP_
		ASSERT (FALSE);
//lijq 20200228  all data types are defined in test-macro-file, 
//		pDataType = (CDataType*)g_pMtDataTypeMngr->m_oMacroTestDataTypes.FindByID(strDataTypeID);
#endif
	}

	return pDataType;
}

CDataType* CMtDataTypeMngr::FindDataType(CDataTypes *pDataTypes, const CString &strDataTypeID)
{
	ASSERT (g_pMtDataTypeMngr != NULL);

	if (g_pMtDataTypeMngr == NULL)
	{
		return NULL;
	}

	CDataType *pDataType = NULL;

	if (strDataTypeID == g_strMtDataType_IECConfig)
	{
		pDataType = g_pMtDataTypeMngr->m_pIecConfigDataType;
	}
	else if (strDataTypeID == g_strMtDataType_ComtradeFile)
	{
		pDataType = g_pMtDataTypeMngr->m_pComtradeFileDataType;
	}
	else
	{
		pDataType = (CDataType*)pDataTypes->FindByID(strDataTypeID);
	}

	return pDataType;
}

void CMtDataTypeMngr::UpdateIecConfigDataType()
{
	g_pMtDataTypeMngr->InitIecConfigDataType();
}

void CMtDataTypeMngr::UpdateComtradeFileDataType()
{
	g_pMtDataTypeMngr->InitComtradeFileDataType();
}
