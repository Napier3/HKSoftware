#include "stdafx.h"
#include "SttHtmlReportVIewInterface.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
#include "../../SttGlobalDef.h"

char* stt_ui_OpenFile(const CString &strPath)
{
	CFile oFile;

	if (! oFile.Open(strPath, CFile::modeRead))
	{
		return NULL;
	}

	long nLen = oFile.GetLength();
	char *pBuffer = new char [nLen + 1];
	oFile.Read(pBuffer, nLen);
	pBuffer[nLen] = 0;
	oFile.Close();

	return pBuffer;
}

CString stt_ui_GetHtmlFile(const CString &strHtmlFileName)
{
	CString strPath = _P_GetSystemPath();
	strPath = _P_GetDBPath();
	strPath += "ui/";
#ifdef NOT_USE_XLANGUAGE  //zhouhj 20220401 如果未使用多语言,固定用中文
	strPath += _T("chinese");
#else
	strPath += xlang_GetCurrLanguageID();
#endif
	strPath += "/";
	strPath += strHtmlFileName;

	return strPath;
}

char* stt_ui_OpenHtmlFile_GetChar(const CString &strHtmlFileName)
{
	CString strPath = stt_ui_GetHtmlFile(strHtmlFileName);
	return stt_ui_OpenFile(strPath);
}

bool stt_ui_OpenHtmlFile(const CString &strHtmlFileName, CString &strCurrRptFileData)
{
	strCurrRptFileData.Empty();
	char *pBuffer = stt_ui_OpenHtmlFile_GetChar(strHtmlFileName);

	if (pBuffer == NULL)
	{
		return false;
	}

	//提取网页中 <body>  </body>  中间的内容
	char *pszBegin = strstr(pBuffer, "<body>");
	
	if (pszBegin != NULL)
	{
		pszBegin += 6;  //"<body>"
		char *pszEnd = strstr(pszBegin,  "</body>");

		if (pszEnd != NULL)
		{
			*pszEnd = 0;
			strCurrRptFileData = pszBegin;
		}
	}

	delete pBuffer;

	return true;
}


bool stt_ui_OpenHtmlHeadFile(const CString &strHtmlFileName, CString &strCurrRptFileData)
{
	strCurrRptFileData.Empty();
	char *pBuffer = stt_ui_OpenHtmlFile_GetChar(strHtmlFileName);

	if (pBuffer == NULL)
	{
		return false;
	}

	unsigned char *pStringGBK = NULL;
	int nLenth = 0;

	utf8_to_gbk_r((const unsigned char*)pBuffer,strlen((char*)pBuffer),&pStringGBK,&nLenth);

	char *pszData = (char *)pStringGBK;
	//提取网页中 <div>  </div>  中间的内容
	char *pszBegin = strstr(strstr(pszData, "<div") + 1,  "<div");//获取到第二个div   

	if (pszBegin != NULL)
	{
		size_t secondPos  = pszBegin - pszData ;//计算第二个div位置

		const char* pszSecondLastDiv  = NULL;
		const char* p = pszData;
		
		const char* lastP = NULL;

		while ((p = strstr(p, "</div>")) != NULL) 
		{
			 lastP = pszSecondLastDiv ;
			pszSecondLastDiv  = p;
			p++;  // 继续搜索下一个 "</div>"
		}

		if (lastP   != NULL) 
		{
			// 找到了最后一个 "</div>"
			// 计算其位置
			size_t secondLastPos  = lastP  - pszData;

			// 提取中间的内容
			size_t contentStartPos = secondPos  ;
			size_t contentLength = secondLastPos  - contentStartPos+ strlen("</div>");
			char* content = new char[contentLength + 1];
			strncpy(content, pszData + contentStartPos, contentLength);
		
			content[contentLength] = '\0';

			strCurrRptFileData = content;
			delete[] content;
		}
	
	}

	delete pStringGBK;
	delete pBuffer;

	return true;
}


CString stt_ui_GetParasFile(const CString &strFileName)
{
	CString strPath;
	strPath = _P_GetDBPath();
	strPath += "atsgen/";
	strPath += strFileName;

	return strPath;
}

//2023-2-7  lijunqing
CString stt_ui_GetParasAiFile(const CString &strFileName)
{
	CString strTitle = GetFileTitleFromFilePath(strFileName);
	strTitle += _T("_Ai.xml");

	return stt_ui_GetParasFile(strTitle);
}

BOOL stt_ui_OpenParasFile(const CString &strFileName, CDataGroup *pParas)
{
	pParas->DeleteAll();
	CString strPath = stt_ui_GetParasFile(strFileName);
#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile	
	CString strPathB = ChangeFilePostfix(strPath, _T("bstt"));
	BOOL bRet = FALSE;

	if (::IsFileExist(strPathB))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, strPathB);
		bRet = dvm_OpenBinaryFile(pParas, strPathB, true);
		debug_time_long_log("stt_ui_OpenParasFile:Binary", true);
	}
	else
	{
	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::IncXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys::g_pXmlKeys);
		bRet = pParas->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::DecXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
		dvm_SaveBinaryFile(pParas, strPathB, true);
		debug_time_long_log("stt_ui_OpenParasFile XML", true);
	}
#else
	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::IncXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys::g_pXmlKeys);
	BOOL bRet = pParas->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::DecXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
#endif


	return bRet;
}

BOOL stt_ui_SaveParasFile(const CString &strFileName, CDataGroup *pParas, long nXmlRWType)
{
	CString strPath = stt_ui_GetParasFile(strFileName);

	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	//保存默认参数文件时，需要保存名称  shaolei 2023-7-25
	//CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys);
	
	BOOL bRet = pParas->SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys, nXmlRWType);
	
	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	//CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys);

	return bRet;
}

CString stt_ui_GetTestTemplateFile(const CString &strMacroUI)
{
	CString strPath = _P_GetSystemPath();
	strPath = _P_GetDBPath();
	strPath += "template/";
	strPath += strMacroUI;
	strPath += ".dscxml";

	return strPath;
}

CString stt_ui_GetDebugFile(const CString &strFileName)
{
	CString strPath = _P_GetSystemPath();
	strPath = _P_GetDBPath();
	strPath += "debug/";
	strPath += strFileName;

	return strPath;
}

BOOL stt_ui_OpenDebugFile(const CString &strFileName, char **ppszText)
{
	CString strPath = stt_ui_GetDebugFile(strFileName);

	*ppszText = stt_ui_OpenFile(strPath);

	return TRUE;
}

BOOL stt_ui_OpenDebugFile(const CString &strFileName, CString &strText)
{
	CString strPath = stt_ui_GetDebugFile(strFileName);

	char *pszBuffer = stt_ui_OpenFile(strPath);

	if (pszBuffer != NULL)
	{
		strText = pszBuffer;
		delete pszBuffer;
	}

	return TRUE;
}
