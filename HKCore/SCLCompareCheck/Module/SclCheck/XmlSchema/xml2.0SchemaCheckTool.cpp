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
// 			//��������
// 			xmlResetError(const_cast<xmlErrorPtr>(error));
// 			return;
// 		}
		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);
		m_nErrorIndex++;
		strStr = /*"����"*/g_sLangTxt_Native_error;
		strStr.AppendFormat("%d ",m_nErrorIndex);//2024-1-2 zhouyangyong �޸��кŴ�ӡ����
		pResultRec->m_nErrorIndex = 1;
		pResultRec->m_strErrorType = strStr;
		strStr = error->message;
		utf8_to_gbk(strStr,strStrNew);
		pResultRec->m_strErrorText = strStrNew;//2024-1-8 zhouyangyong �޸Ĵ�����Ϣ����������
		pResultRec->m_strErrorText.Remove('\n');
		//pResultRec->m_strErrorPos.Format("%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
		FormatString(pResultRec->m_strErrorPos,"%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
	}
	else if (error->level == XML_ERR_WARNING)
	{
		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);
		m_nWarningIndex++;
		strStr = /*"�澯"*/g_sLangTxt_SCLCompare_Warning;
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
		strStr = /*"����"*/g_sLangTxt_SCLCompare_Serious;
		strStr.AppendFormat("%d ",m_nFatalErrorIndex);//2024-1-2 zhouyangyong �޸��кŴ�ӡ����
		pResultRec->m_nFatalErrorIndex = 1;
		pResultRec->m_strErrorType = strStr;
		strStr = error->message;
		utf8_to_gbk(strStr,strStrNew);
		pResultRec->m_strErrorText = strStrNew;
		pResultRec->m_strErrorText.Remove('\n');
		//pResultRec->m_strErrorPos.Format("%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
		FormatString(pResultRec->m_strErrorPos,"%s=%d ,%s=%d",g_sLangTxt_SCLCompare_RowNum.GetString(), line, g_sLangTxt_SCLCompare_ColumnNum.GetString(), column);
	}

	// ����������ǵ��ͷ�error����
	xmlResetError(const_cast<xmlErrorPtr>(error));
}

void Cxml2SchemaCheckTool::my_structured_error_handler(void *userData, const xmlError *error) 
{
	Cxml2SchemaCheckTool* instance = static_cast<Cxml2SchemaCheckTool*>(userData);
	instance->error_handle(error);
}

BOOL Cxml2SchemaCheckTool::validateXML(CString strxsdFilePath/*�﷨�ļ�*/, CString strxmlFilePath/*������ļ�*/)
{
	const char *xmlFilePath = strxmlFilePath.GetString();
	const char *xsdFilePath = strxsdFilePath.GetString();

	xmlSchemaPtr schema = NULL;
	xmlDocPtr beTestedDoc;//����xml��doc������
	xmlSchemaParserCtxtPtr ctxt;
	xmlSchemaValidCtxtPtr validCtxt;
	xmlSetStructuredErrorFunc(this,my_structured_error_handler);
	int isValid;
	// ����һ��Schema�﷨�ļ���doc������
	xmlDocPtr xsdDoc = xmlReadFile(xsdFilePath, NULL, XML_PARSE_BIG_LINES);//libxml2��Ĭ�ϴ�����������Ϊ65535���򿪴��ļ���Ҫ���������ʶ
	if (xsdDoc == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("�޷��򿪻����XSD�ļ���")*/g_sLangTxt_SCLCompare_UnableOpenXsdFile);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// ʹ��XSD�ĵ�����XML Schema
	ctxt = xmlSchemaNewDocParserCtxt(xsdDoc);
	if (ctxt == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("�޷�����XML Schema�����������ġ�")*/g_sLangTxt_SCLCompare_UnableCreateXmlSchemaParser);
		xmlFreeDoc(xsdDoc);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	//����XML Schema
	schema = xmlSchemaParse(ctxt);
	if (schema == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("�޷�����XML Schema��")*/g_sLangTxt_SCLCompare_UnableParseXmlSchema);
		xmlSchemaFreeParserCtxt(ctxt);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// ����һ����֤������
	validCtxt = xmlSchemaNewValidCtxt(schema);
	if (validCtxt == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("�޷�����XML Schema��֤�����ġ�")*/g_sLangTxt_SCLCompare_UnableCreateXmlSchemaNewValidCtxt);
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(ctxt);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// �򿪲�����XML�ļ�
	if (m_strDomType == XML_CHECK_TYPE_DOM)//ʹ��DOMģʽ
	{
		beTestedDoc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_BIG_LINES /*| XML_PARSE_NOBLANKS*/);
	}
	else//ʹ��SAXģʽ
	{
		beTestedDoc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_BIG_LINES | XML_PARSE_OLDSAX /*| XML_PARSE_NOBLANKS*/);
	}
	
	if (beTestedDoc == NULL) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("�޷��򿪻����XML�ļ���")*/g_sLangTxt_SCLCompare_UnableOpenXmlFile);
		xmlSchemaFreeValidCtxt(validCtxt);
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(ctxt);
		xmlFreeDoc(beTestedDoc);
		m_nSchemaCheckFinished = TRUE;
		return FALSE;
	}
	// ��֤XML�ĵ�
	isValid = xmlSchemaValidateDoc(validCtxt, beTestedDoc);
	if (isValid == 0) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, /*_T("Schema�﷨���������ļ�����Schema����")*/g_sLangTxt_SCLCompare_SchemaValidCheckFinish);
	} 
	else 
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Schema�﷨���������ļ�������Schema����"));
		//2024-1-2 zhouyangyong ע�͵���ȥ��������ӡ
	}
	m_nSchemaCheckFinished = TRUE;
	m_pResultsRec->m_nAllWarningIndex = m_nWarningIndex;
	m_pResultsRec->m_nAllErrorIndex = m_nErrorIndex;
	m_pResultsRec->m_nAllFatalErrorIndex = m_nFatalErrorIndex;

	CResultRec *pResultRec = new CResultRec;
	m_pResultsRec->AddNewChild(pResultRec);

	pResultRec->m_strErrorType = /*"���ͳ��"*/g_sLangTxt_SCLCompare_ResultStatistic;
	pResultRec->m_strErrorText = "\\";
	pResultRec->m_strErrorPos = "\\";
	pResultRec->m_nWarningIndex = m_nWarningIndex;
	pResultRec->m_nErrorIndex = m_nErrorIndex;
	pResultRec->m_nFatalErrorIndex = m_nFatalErrorIndex;
	// �ͷ���Դ
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
	m_pXml2CheckThread = AfxBeginThread(SchemaCheckThread, this); //�����߳� 
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