#include "SttIecTestHtmlRptGenFactory.h"
#include "../../UI/SttTestCntrCmdDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#ifndef NOT_USE_XLANGUAGE
#include "../../../Module/XLanguage/XLanguageMngr.h"
#endif

CSttIecTestHtmlRptGenFactory::CSttIecTestHtmlRptGenFactory()
{
	//注册报告生成对象
}

CSttIecTestHtmlRptGenFactory::~CSttIecTestHtmlRptGenFactory()
{
	FreeDataTypes();
}

void CSttIecTestHtmlRptGenFactory::OpenDataTypesFile(CString strFilePath)
{
	if (strFilePath.GetLength() <= 7)
	{
		strFilePath = _P_GetConfigPath();
		strFilePath += _T("RelayTest/MacroTestDataType.xml");
	}

	FreeDataTypes();
	m_pDataTypes = new CDataTypes();
	m_pDataTypes->Open(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
}
//2024-10-17 zhouyangyong 移植优化打开代码
void CSttIecTestHtmlRptGenFactory::OpenDataTypesByMacroFileID(const CString &strMacroFileID)
{
	CString strFilePath, strFilePathB;
	strFilePath = _P_GetConfigPath();

	if (strMacroFileID.IsEmpty())
	{
		strFilePath += _T("RelayTest");
	}
	else
	{
		strFilePath += strMacroFileID;
	}

	strFilePath += _T("/MacroTestDataType.xml");
	FreeDataTypes();
	m_pDataTypes = new CDataTypes();
#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile	
	strFilePathB = ChangeFilePostfix(strFilePath, _T("bxml"));

	if (::IsFileExist(strFilePathB))
	{
		dvm_OpenBinaryFile(m_pDataTypes, strFilePathB, true);
	}
	else
	{
		m_pDataTypes->Open(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
		dvm_SaveBinaryFile(m_pDataTypes, strFilePathB, true);
	}
	debug_time_long_log("OpenDataTypesByMacroFileID MacroTestDataType", true);
#else
	m_pDataTypes->Open(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(m_pDataTypes, strFilePath);
#endif
}

void CSttIecTestHtmlRptGenFactory::FreeDataTypes()
{
	if (m_pDataTypes != NULL)
	{
		delete m_pDataTypes;
		m_pDataTypes = NULL;
	}
}
