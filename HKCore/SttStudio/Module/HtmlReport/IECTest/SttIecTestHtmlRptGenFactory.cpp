#include "SttIecTestHtmlRptGenFactory.h"
#include "SttHtmlRptGen_MUAccuracy.h"
#include "SttHtmlRptGen_MUZeroDrift.h"
#include "SttHtmlRptGen_MUTimingAccur.h"
#include "SttHtmlRptGen_MUPunctAccur.h"
#include "SttHtmlRptGen_IntelligentTerminal.h"
#include "../../UI/SttTestCntrCmdDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttHtmlRptGen_TerminalAuto.h"
#include "SttHtmlRptGen_ShortTimeOver.h"
#ifndef NOT_USE_XLANGUAGE
#include "../../../Module/XLanguage/XLanguageMngr.h"
#endif

CSttIecTestHtmlRptGenFactory::CSttIecTestHtmlRptGenFactory()
{
	//注册报告生成对象
	RegisterCreator(STT_ORG_MACRO_MUAccuracyTest, STT_ORG_MACRO_MUAccuracyTest, CSttHtmlRptGen_MUAccuracy::New);
//	RegisterCreator(STT_ORG_MACRO_MUZeroDriftTest, STT_ORG_MACRO_MUZeroDriftTest, CSttHtmlRptGen_MUZeroDrift::New);
	RegisterCreator(STT_ORG_MACRO_MUTimingAccurTest, STT_ORG_MACRO_MUTimingAccurTest, CSttHtmlRptGen_MUTimingAccur::New);
	RegisterCreator(STT_ORG_MACRO_MUPunctAccurTest, STT_ORG_MACRO_MUPunctAccurTest, CSttHtmlRptGen_MUPunctAccur::New);
	RegisterCreator(STT_ORG_MACRO_IntelligentTest, STT_ORG_MACRO_IntelligentTest, CSttHtmlRptGen_IntelligentTerminal::New);
	RegisterCreator(STT_ORG_MACRO_TerminalAutoTest, STT_ORG_MACRO_TerminalAutoTest, CSttHtmlRptGen_TerminalAuto::New);
	RegisterCreator(STT_ORG_MACRO_ShortTimeOverTest, STT_ORG_MACRO_ShortTimeOverTest, CSttHtmlRptGen_ShortTimeOver::New);
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
	debug_time_long_log("OpenDataTypesByMacroFileID TranslateByResourceFileEx", true);
}

void CSttIecTestHtmlRptGenFactory::FreeDataTypes()
{
	if (m_pDataTypes != NULL)
	{
		delete m_pDataTypes;
		m_pDataTypes = NULL;
	}
}
