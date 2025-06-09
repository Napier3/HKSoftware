//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataMngrGlobal.cpp

#include "stdafx.h"
#include "SclCheckMngrGlobal.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"

//////////////////////////////////////////////////////////////////////////
//CDataMngrXmlRWKeys

CSclCheckMngrXmlRWKeys* CSclCheckMngrXmlRWKeys::g_pXmlKeys = NULL;
long CSclCheckMngrXmlRWKeys::g_nDataTypeTemRef = 0;


CSclCheckMngrXmlRWKeys::CSclCheckMngrXmlRWKeys()
{
#ifdef XML_USE_TINYXML
	m_strCSCLKey = "SCL";
	m_strCDataTypeTmpsKey = "DataTypeTemplates"; //
	m_strCLNodeTypeTKey = "LNodeTypeT"; //
	m_strCLNodeTypeKey = "LNodeType"; //
	m_strCDOTypeKey = "DOType"; //
	m_strCDATypeKey = "DAType"; //
	m_strCEnumTypeKey = "EnumType"; //

	m_strCDOValueKey = "DO"; //
	m_strCDOTValueKey = "DOt";//DOt
	m_strCDAValueKey = "DA"; //
	m_strCSDOValueKey = "SDO"; //SDO
	m_strCBDAValueKey = "BDA"; //
	m_strCEnumValKey = "EnumVal"; //

	m_strLnClassKey = "lnClass"; //
	m_strCDCKey = "cdc";
	m_strMopKey = "mop"; //mop

	m_strDchgKey = "dchg"; //
	m_strQchgKey = "qchg"; //qchg
	m_strBTypeKey = "bType"; //
	
	m_strFCKey = "fc"; //

	m_strOrdKey = "ord"; //
	m_strTypeKey = "type"; //
	m_strValueKey = "Val"; //
	m_strVertionKey = "vertion"; //vertion
	m_strMethodKey = "method"; //method

	m_strCLDeviceKey = "LDevice"; //LDevice
	m_strCDataSetKey = "DataSet"; //DataSet
	m_strCCDCKey = "CDC"; //CDC
	m_strDescKey = "desc"; //desc
	m_strBrcbnameKey = "brcbname"; //brcbname 
	m_strLcbnameKey = "lcbname"; //lcbname
	m_strTransientKey = "transient"; //transient

	m_strPrivateMSGKey = "privateMSG"; //privateMSG

	m_strCSclCheckObjectsSetKey = "all-checks"; //all-checks
	m_strCSchemaChecksKey = "schema-checks"; //schema-checks
	m_strCDLT860ModelChecksKey = "DLT860Model-checks"; //DLT860Model-checks
	m_strCProjAppModelChecksKey = "ProjAppModel-checks"; //ProjAppModel-checks
	m_strCVirLoopChecksKey = "virloop-checks"; //virloop-checks
	m_strCCheckObjectKey = "check-object"; //check-object
	m_strChoseKey = "chose"; //chose
	m_strPathKey = "path"; //path
	m_strCSchemaObjectKey = "schema-object"; //schema-object

	m_strCCheckPathsKey = "check-paths";//check-paths
	m_strCSinglePathKey = "single-path";//single-path
#else
	m_strCSCLKey = L"SCL";
	m_strCDataTypeTmpsKey = L"DataTypeTemplates"; //
	m_strCLNodeTypeTKey = L"LNodeTypeT"; //
	m_strCLNodeTypeKey = L"LNodeType"; //
	m_strCDOTypeKey = L"DOType"; //
	m_strCDATypeKey = L"DAType"; //
	m_strCEnumTypeKey = L"EnumType"; //

	m_strCDOValueKey = L"DO"; //
	m_strCDOTValueKey = L"DOt";//DOt
	m_strCDAValueKey = L"DA"; //
	m_strCSDOValueKey = L"SDO"; //SDO
	m_strCBDAValueKey = L"BDA"; //
	m_strCEnumValKey = L"EnumVal"; //

	m_strLnClassKey = L"lnClass"; //
	m_strCDCKey = L"cdc";
	m_strMopKey = L"mop"; //mop

	m_strDchgKey = L"dchg"; //
	m_strQchgKey = L"qchg"; //qchg
	m_strBTypeKey = L"bType"; //
	
	m_strFCKey = L"fc"; //

	m_strOrdKey = L"ord"; //

	m_strTypeKey = L"type"; //
	m_strValueKey = L"Val"; //
	m_strVertionKey = L"vertion"; //vertion
	m_strMethodKey = L"method"; //method

	m_strCLDeviceKey = L"LDevice"; //LDevice
	m_strCDataSetKey = L"DataSet"; //DataSet
	m_strCCDCKey = L"CDC"; //CDC
	m_strDescKey = L"desc"; //desc
	m_strBrcbnameKey = L"brcbname"; //brcbname 
	m_strLcbnameKey = L"lcbname"; //lcbname
	m_strTransientKey = L"transient"; //transient
	m_strPrivateMSGKey = L"privateMSG"; //privateMSG

	m_strCSclCheckObjectsSetKey = L"all-checks"; //all-checks
	m_strCSchemaChecksKey = L"schema-checks"; //schema-checks
	m_strCDLT860ModelChecksKey = L"DLT860Model-checks"; //DLT860Model-checks
	m_strCProjAppModelChecksKey = L"ProjAppModel-checks"; //ProjAppModel-checks
	m_strCVirLoopChecksKey = L"virloop-checks"; //virloop-checks
	m_strCCheckObjectKey = L"check-object"; //check-object
	m_strChoseKey = L"chose"; //chose
	m_strPathKey = L"path"; //path
	m_strCSchemaObjectKey = L"schema-object"; //schema-object
	m_strCCheckPathsKey = L"check-paths";//check-paths
	m_strCSinglePathKey = L"single-path";//single-path
#endif
}

CSclCheckMngrXmlRWKeys::~CSclCheckMngrXmlRWKeys()
{
}

CSclCheckMngrXmlRWKeys* CSclCheckMngrXmlRWKeys::Create()
{
	g_nDataTypeTemRef++;

	if (g_nDataTypeTemRef == 1)
	{
		g_pXmlKeys = new CSclCheckMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSclCheckMngrXmlRWKeys::Release()
{
	g_nDataTypeTemRef--;

	if (g_nDataTypeTemRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CSclCheckMngrConstGlobal

long CSclCheckMngrConstGlobal::g_nGlobalRef = 0;
CSclCheckMngrConstGlobal* CSclCheckMngrConstGlobal::g_pGlobal = NULL;


CSclCheckMngrConstGlobal::CSclCheckMngrConstGlobal()
{
	InitGlobal();
}

CSclCheckMngrConstGlobal::~CSclCheckMngrConstGlobal()
{
}

CSclCheckMngrConstGlobal* CSclCheckMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSclCheckMngrConstGlobal();
	}

	return g_pGlobal;
}

void CSclCheckMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

void CSclCheckMngrConstGlobal::InitGlobal()
{
	Init_checkObjectSetDataType();
	Init_schemaCheckObjectSetDataType();
	Init_schemaCheckMethodType();
}

void CSclCheckMngrConstGlobal::Init_checkObjectSetDataType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("checkObjectSetDataType"), _T("checkObjectSetDataTypeID"));
	pDataType->AddNewValue(/*_T("提示")*/g_sLangTxt_Native_LangTip, _T("tips"), _T("0"));
	pDataType->AddNewValue(/*_T("告警")*/g_sLangTxt_SCLCompare_Warning, _T("warning"), _T("1"));
	pDataType->AddNewValue(/*_T("错误")*/g_sLangTxt_Native_error, _T("error"), _T("2"));
	pDataType->AddNewValue(/*_T("严重错误")*/g_sLangTxt_SCLCompare_SeriousErr, _T("fatalerror"), _T("3"));
}

void CSclCheckMngrConstGlobal::Init_schemaCheckObjectSetDataType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("schemaCheckVertionType"), _T("schemaCheckVertionTypeID"));
	pDataType->AddNewValue(_T("SCL1.4"), _T("SCL1.4"), _T("0"));
	pDataType->AddNewValue(_T("SCL2.0"), _T("SCL2.0"), _T("1"));
	pDataType->AddNewValue(_T("SCL3.0"), _T("SCL3.0"), _T("2"));
}

void CSclCheckMngrConstGlobal::Init_schemaCheckMethodType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("schemaCheckMethodType"), _T("schemaCheckMethodTypeID"));
	pDataType->AddNewValue(/*_T("DOM方式")*/g_sLangTxt_SCLCompare_DOMMethod, _T("DOM"), _T("0"));
	pDataType->AddNewValue(/*_T("SAX方式")*/g_sLangTxt_SCLCompare_SAXMethod, _T("SAX"), _T("1"));
}

CDataType* CSclCheckMngrConstGlobal::FindIecRtdDataType(const  CString &strDataTypeID)
{
	ASSERT (g_pGlobal != NULL);
	CDataType *pDataType = NULL;

	pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(strDataTypeID);

	return pDataType;
}
