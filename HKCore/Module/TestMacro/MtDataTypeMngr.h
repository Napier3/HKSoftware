#pragma once

#include "../../Module/DataMngr/DataMngrGlobal.h"
#include "../../Module/DataMngr/DataTypes.h"
// #include "..\..\Module\FileMngr\FileMngrBase.h"

#ifndef _PSX_IDE_QT_
#include "../../Module/XfileMngrBase/XFileMngr.h"
#endif

// #include "TestMacroConfigs.h"

class CMtDataTypeMngr
{
private:
	CMtDataTypeMngr(void);
	virtual ~CMtDataTypeMngr(void);

	static long g_nMtDataTypeMngrRef;
	static CMtDataTypeMngr *g_pMtDataTypeMngr;

public:
	static const CString g_strMtDataType_Number;
	static const CString g_strMtDataType_Set;
	static const CString g_strMtDataType_String;
	static const CString g_strMtDataType_Expression;
	static const CString g_strMtDataType_IECConfig;
	static const CString g_strMtDataType_ComtradeFile;
	static const CString g_strMtDataType_IECExpFile;
	static const CString g_strMtDataType_ConfigFile;

	static const CString g_strTestMacroID_IECConfig;

public:
	static CMtDataTypeMngr* Create();
	static void Release();
	
public:
	//lijq 20200228  all data types are defined in test-macro-file, 
	//static CDataTypes* GetMacroTestDataTypes();//			{		return &(g_pMtDataTypeMngr->m_oMacroTestDataTypes);		}
	static void InitMacroTestDataTypes(const CString &strDataTypeFile);
	static CString GetDataTypeValueName(const CString &strDataTypeID, const CString &strValue);
	static CString GetDataTypeValueIndex(const CString &strDataTypeID, const CString &strName);
	static CString GetDataTypeName(const CString &strDataTypeID);
	static BOOL IsDataTypeCombo(const CString &strDataTypeID);
	static CDataType* FindDataType(const CString &strDataTypeID);
	static CDataType* FindDataType(CDataTypes *pDataTypes, const CString &strDataTypeID);
	static void UpdateIecConfigDataType();
	static void UpdateComtradeFileDataType();
	
private:
#ifdef _TEST_APP_
	//lijq 20200228  all data types are defined in test-macro-file, 
	//CDataTypes m_oMacroTestDataTypes;
#endif

	CDataType  *m_pIecConfigDataType;
	CDataType  *m_pComtradeFileDataType;
	CDataType  *m_pIecExceptionDataType;

	void InitIecConfigDataType();
	void InitComtradeFileDataType();
	void InitIecExpFileDataType();

#ifndef _PSX_IDE_QT_
    void InitFileDataTypeByXFileMngr(CXFileMngr *pXFileMngr, CDataType *pDataType, CDataType &oFilePostFixMngr);
	void InitDataType(CDataType *pDataType, CXFolder *pFolder);
#endif
};

CString mtdt_GetIecConfigFile(const CString &strFileName);
CString mtdt_GetIecConfigFilePath();
CString mtdt_GetComtradeFilePath();


