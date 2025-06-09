#include "StdAfx.h"
#include "StesFileToolsFactory.h"

#include "StesFilePdfTool.h"
#include "StesFileWordTool.h"
#include "StesFileExcelTool.h"
#include "StesFileXmlTool.h"
#include "StesFileBinaryTool.h"
#include "..\..\XLanguageResourceAts.h"

CStesFileToolsFactory* CStesFileToolsFactory::g_pStesFileToolsFactory = NULL;
long CStesFileToolsFactory::g_nStesFileToolsFactoryRef = 0;


CStesFileToolsFactory::CStesFileToolsFactory(void)
{
	RegisterCreator(g_sLangTxt_PdfFile/*_T("XML定值文件")*/, _T("pdf"), CStesFilePdfTool::Create);
// 	RegisterCreator(g_sLangTxt_XMLFile/*_T("XML定值文件")*/, _T("XML"), CStesFileXmlTool::Create);
// 	RegisterCreator(g_sLangTxt_WordFile/*_T("Word定值文件")*/, _T("doc"), CStesFileWordTool::Create);
// 	RegisterCreator(g_sLangTxt_ExcelFile/*_T("Excel定值文件")*/, _T("xls"), CStesFileExcelTool::Create);
// 	RegisterCreator(g_sLangTxt_OATSFile/*_T("OATS自定义定值文件")*/, _T("bsts"), CStesFileBinaryTool::Create);
}

CStesFileToolsFactory::~CStesFileToolsFactory(void)
{
}

CStesFileToolsFactory* CStesFileToolsFactory::Create()
{
	if (g_nStesFileToolsFactoryRef == 0)
	{
		g_pStesFileToolsFactory = new CStesFileToolsFactory();
	}

	g_nStesFileToolsFactoryRef++;
	return g_pStesFileToolsFactory;
}
void CStesFileToolsFactory::Release()
{
	g_nStesFileToolsFactoryRef--;

	if (g_nStesFileToolsFactoryRef == 0)
	{
		delete g_pStesFileToolsFactory;
		g_pStesFileToolsFactory = NULL;
	}
}

void CStesFileToolsFactory::AfterImportFile(CExBaseObject *pRefObject, CExBaseObject *pNewObject)
{
// 	CSysParaEditGroups *pCurrGroups = (CSysParaEditGroups*)pRefObject;
// 	CSysParaEditGroups *pNewGroups = (CSysParaEditGroups*)pNewObject;
// 	ASSERT (pNewGroups != NULL);
// 	pCurrGroups->InitValues(pNewGroups);
}

void CStesFileToolsFactory::SetsFileImport(const CString &strFileType)
{
	
}

