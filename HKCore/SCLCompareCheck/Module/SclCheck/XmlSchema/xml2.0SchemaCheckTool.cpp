#include "xml2.0SchemaCheckTool.h"
#include<libxml/xmlschemas.h>
#include<libxml/xmlerror.h>
#include "../../API/StringConvertApi.h"
#include "../../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"

Cxml2SchemaCheckTool::Cxml2SchemaCheckTool()
{
	m_pResultsRec = NULL;
	m_strXsdPath = "";
	m_strXmlPath = "";
	m_pXml2CheckThread = NULL;
	m_nSchemaCheckFinished = TRUE;
	m_nErrorIndex = 0;
	m_nWarningIndex = 0;
	m_nFatalErrorIndex = 0;
	m_strDomType = XML_CHECK_TYPE_DOM;
}

Cxml2SchemaCheckTool::~Cxml2SchemaCheckTool()
{

}

void Cxml2SchemaCheckTool::error_handle(const xmlError *error)
{
	CString strStr, strStrNew;
	long line = error->line;
	long column = error->int2;

	if (error->line == 65535)
	{
		line = 0;
	}
	if (error->level == XML_ERR_ERROR)
	{
// 		if(error->code ==XML_SCHEMAV_CVC_COMPLEX_TYPE_2_1
// 			||error->code == XML_SCHEMAV_CVC_COMPLEX_TYPE_4
// 			||error->code == XML_SCHEMAV_CVC_IDC
// 			||error->code == XML_SCHEMAV_CVC_COMPLEX_TYPE_3_2_1
// 			||error->code == XML_SCHEMAV_CVC_DATATYPE_VALID_1_2_3
// 			||error->code == XML_SCHEMAV_CVC_MINLENGTH_VALID
// 			)
// 		{
// 			//不做处理
// 			xmlResetError(const_cast<xmlErrorPtr>(error));
// 			return;
// 		}
		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);
		m_nErrorIndex++;
		strStr = /*"错误"*/g_sLangTxt_Native_error;
		strStr.AppendFormat("%d ",m_nErrorIndex);//2024-1-2 zhouyangyong 修改行号打印问题
		pResultRec->m_nErrorIndex = 1;
		pResultRec->m_strErrorType = strStr;
		strStr = error->message;
		utf8_to_gbk(strStr,strStrNew);
		pResultRec->m_strErrorText = strStrNew;//2024-1-8 zhouyangyong 修改错误信息里乱码问题
		pResultRec->m_strErrorText.Remove('\n');
		//pResultRec->m_strErrorPos.Format("%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
		FormatString(pResultRec->m_strErrorPos,"%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
	}
	else if (error->level == XML_ERR_WARNING)
	{
		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);
		m_nWarningIndex++;
		strStr = /*"告警"*/g_sLangTxt_SCLCompare_Warning;
		strStr.AppendFormat("%d ",m_nWarningIndex);
		pResultRec->m_nWarningIndex = 1;
		pResultRec->m_strErrorType = strStr;
		strStr = error->message;
		utf8_to_gbk(strStr,strStrNew);
		pResultRec->m_strErrorText = strStrNew;
		pResultRec->m_strErrorText.Remove('\n');
		//pResultRec->m_strErrorPos.Format("%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
		FormatString(pResultRec->m_strErrorPos,"%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
	}
	else if (error->level == XML_ERR_FATAL)
	{
		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);
		m_nFatalErrorIndex++;
		strStr = /*"严重"*/g_sLangTxt_SCLCompare_Serious;
		strStr.AppendFormat("%d ",m_nFatalErrorIndex);//2024-1-2 zhouyangyong 修改行号打印问题
		pResultRec->m_nFatalErrorIndex = 1;
		pResultRec->m_strErrorType = strStr;
		strStr = error->message;
		utf8_to_gbk(strStr,strStrNew);
		pResultRec->m_strErrorText = strStrNew;
		pResultRec->m_strErrorText.Remove('\n');
		//pResultRec->m_strErrorPos.Format("%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
		FormatString(pResultRec->m_strErrorPos,"%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
	}

	// 处理完错误后记得释放error对象
	xmlResetError(const_cast<xmlErrorPtr>(error));
}

void Cxml2SchemaCheckTool::my_structured_error_handler(void *userData, const xmlError *error) 
{
	Cxml2SchemaCheckTool* instance = static_cast<Cxml2SchemaCheckTool*>(userData);
	instance->error_handle(error);
}

BOOL Cxml2SchemaCheckTool::validateXML(CString strxsdFilePath/*语法文件*/, CString strxmlFilePath/*待检查文件*/)
{
	const char *xmlFilePath = strxmlFilePath.GetString();
	const char *xsdFilePath = strxsdFilePath.GetString();

	xmlSchemaPtr schema = NULL;
	xmlDocPtr beTestedDoc;//待测xml的doc解析器
	xmlSchemaParserCtxtPtr ctxt;
	xmlSchemaValidCtxtPtr validCtxt;
	xmlSetStructuredErrorFunc(this,my_structured_error_handler);
	int isValid;
	// 创建一个Schema语法文件的doc解析器
	xmlDocPtr xsdDoc = xmlReadFile(xsdFilePath, NULL, XML_PARSE_BIG_LINES);//libxml2库默认存贮行数上限为65535，打开大文件需要加上这个标识
	if (xsdDoc == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("无法打开或解析XSD文件。")*/g_sLangTxt_SCLCompare_UnableOpenXsdFile);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// 使用XSD文档构建XML Schema
	ctxt = xmlSchemaNewDocParserCtxt(xsdDoc);
	if (ctxt == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("无法创建XML Schema解析器上下文。")*/g_sLangTxt_SCLCompare_UnableCreateXmlSchemaParser);
		xmlFreeDoc(xsdDoc);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	//解析XML Schema
	schema = xmlSchemaParse(ctxt);
	if (schema == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("无法解析XML Schema。")*/g_sLangTxt_SCLCompare_UnableParseXmlSchema);
		xmlSchemaFreeParserCtxt(ctxt);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// 创建一个验证上下文
	validCtxt = xmlSchemaNewValidCtxt(schema);
	if (validCtxt == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("无法创建XML Schema验证上下文。")*/g_sLangTxt_SCLCompare_UnableCreateXmlSchemaNewValidCtxt);
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(ctxt);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// 打开并解析XML文件
	if (m_strDomType == XML_CHECK_TYPE_DOM)//使用DOM模式
	{
		beTestedDoc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_BIG_LINES /*| XML_PARSE_NOBLANKS*/);
	}
	else//使用SAX模式
	{
		beTestedDoc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_BIG_LINES | XML_PARSE_OLDSAX /*| XML_PARSE_NOBLANKS*/);
	}
	
	if (beTestedDoc == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("无法打开或解析XML文件。")*/g_sLangTxt_SCLCompare_UnableOpenXmlFile);
		xmlSchemaFreeValidCtxt(validCtxt);
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(ctxt);
		xmlFreeDoc(beTestedDoc);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// 验证XML文档
	isValid = xmlSchemaValidateDoc(validCtxt, beTestedDoc);
	if (isValid == 0) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("Schema语法检查结束，文件符合Schema规则。")*/g_sLangTxt_SCLCompare_SchemaValidCheckFinish);
	} 
	else 
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Schema语法检查结束，文件不符合Schema规则。"));
		//2024-1-2 zhouyangyong 注释掉，去除掉这句打印
	}
	m_nSchemaCheckFinished = TRUE;
	m_pResultsRec->m_nAllWarningIndex = m_nWarningIndex;
	m_pResultsRec->m_nAllErrorIndex = m_nErrorIndex;
	m_pResultsRec->m_nAllFatalErrorIndex = m_nFatalErrorIndex;

	CResultRec *pResultRec = new CResultRec;
	m_pResultsRec->AddNewChild(pResultRec);

	pResultRec->m_strErrorType = /*"结果统计"*/g_sLangTxt_SCLCompare_ResultStatistic;
	pResultRec->m_strErrorText = "\\";
	pResultRec->m_strErrorPos = "\\";
	pResultRec->m_nWarningIndex = m_nWarningIndex;
	pResultRec->m_nErrorIndex = m_nErrorIndex;
	pResultRec->m_nFatalErrorIndex = m_nFatalErrorIndex;
	// 释放资源
	xmlSchemaFreeValidCtxt(validCtxt);
	xmlSchemaFree(schema);
	xmlSchemaFreeParserCtxt(ctxt);
	xmlFreeDoc(beTestedDoc);
	xmlFreeDoc(xsdDoc);
	m_nErrorIndex = 0;
	m_nWarningIndex = 0;
	m_nFatalErrorIndex = 0;
	return TRUE;
}

BOOL Cxml2SchemaCheckTool::StartCheckXml2ValidNormal()
{
	return validateXML(m_strXsdPath, m_strXmlPath);
}

int Cxml2SchemaCheckTool::StartCheckXml2ValidFromThread(CString strXsdPath, CString strXmlPath)
{
	m_strXmlPath = strXmlPath;
	m_strXsdPath = strXsdPath;
#ifdef _PSX_IDE_QT_
	FreeSchemaCheckThread();
	m_nSchemaCheckFinished = FALSE;
	m_pXml2CheckThread = new CWinThread(SchemaCheckThread, this);
	m_pXml2CheckThread->m_bAutoDelete = FALSE;
	m_pXml2CheckThread->ResumeThread();
#else
	m_pXml2CheckThread = AfxBeginThread(SchemaCheckThread, this); //启动线程 
	m_pXml2CheckThread->m_bAutoDelete = TRUE;
#endif

	return 1;
}

void Cxml2SchemaCheckTool::FreeSchemaCheckThread()
{
#ifdef _PSX_IDE_QT_
	if (m_pXml2CheckThread != NULL)
	{
		m_pXml2CheckThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pXml2CheckThread->wait();
		m_pXml2CheckThread = NULL;
	}
#endif
}

UINT Cxml2SchemaCheckTool::SchemaCheckThread(LPVOID pParam)
{
	Cxml2SchemaCheckTool *pXmlCheckObject = (Cxml2SchemaCheckTool *)pParam;
	return pXmlCheckObject->StartCheckXml2ValidNormal();
}

void Cxml2SchemaCheckTool::InitCheck(CString strCheckType,CResultsRec *pResultsRec)
{
	m_strDomType = strCheckType;
	m_pResultsRec = pResultsRec;
}

void Cxml2SchemaCheckTool::FormatString(CString &strText, const char *strFormat, ...)
{
#ifdef _PSX_IDE_QT_
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strText);
	va_end( argList );
#else
	va_list argList;
    va_start( argList, format );
    strText.vsprintf(format, argList );
    va_end( argList );
#endif
}