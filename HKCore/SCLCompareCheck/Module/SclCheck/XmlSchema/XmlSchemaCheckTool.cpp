// XmlCheckObject.cpp: implementation of the CXmlCheckObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlSchemaCheckTool.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>//sax2解析器
#include <xercesc/sax2/XMLReaderFactory.hpp> //sax2解析器管理器

#include <xercesc/util/OutOfMemoryException.hpp>   
#include <xercesc/dom/DOM.hpp>   
#include <xercesc/parsers/XercesDOMParser.hpp>   
#include <xercesc/framework/XMLGrammarDescription.hpp>   
#include <xercesc/sax/ErrorHandler.hpp>   
#include <xercesc/sax/SAXParseException.hpp> 
#include <xercesc/framework/MemBufInputSource.hpp> //xml内存对象
#include<QTextCodec>
#include "../../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CContentHandleObject::CContentHandleObject()
{
	m_strErrorMessage.empty();
	m_strContent.empty();
	m_nErrorIndex = 0;
	m_nWarningIndex = 0;
	m_nFatalErrorIndex = 0;
}

CContentHandleObject::~CContentHandleObject()
{
}
void CContentHandleObject::startDocument()
{

}
void CContentHandleObject::endDocument()
{

}

///////////////////////////////////////////////////////////////////////////////
void CContentHandleObject::warning(const SAXParseException& exc)
{
	this->SaveErrorMessage(exc.getMessage(),exc.getLineNumber(),exc.getColumnNumber(),exc.getPublicId(),exc.getSystemId() ,1);
}
void CContentHandleObject::error(const SAXParseException& exc)
{
	this->SaveErrorMessage(exc.getMessage(),exc.getLineNumber(),exc.getColumnNumber(),exc.getPublicId(),exc.getSystemId() ,2);
}
void CContentHandleObject::fatalError(const SAXParseException& exc)
{
	this->SaveErrorMessage(exc.getMessage(),exc.getLineNumber(),exc.getColumnNumber(),exc.getPublicId(),exc.getSystemId() ,3);
}
bool CContentHandleObject::SaveErrorMessage(const XMLCh* errorMessage,int rowNumber,int columnNumber,const XMLCh* publicId,const XMLCh* systemId  ,int nErrorType)
{
	bool rc = false;
	char* pTranscodeBuf = NULL;
	char buf[32] = "\0";

	CString strStr;

	CResultRec *pResultRec = new CResultRec;
	m_pResultsRec->AddNewChild(pResultRec);

	if (nErrorType == 1)
	{
		m_nWarningIndex++;
		strStr = /*"告警"*/g_sLangTxt_SCLCompare_Warning;
		strStr.AppendFormat("%d ",m_nWarningIndex);
		pResultRec->m_nWarningIndex = 1;
	}
	else if (nErrorType == 2)
	{
		m_nErrorIndex++;
		strStr = /*"错误"*/g_sLangTxt_Native_error;
		strStr.AppendFormat("%d ",m_nErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (nErrorType == 3)
	{
		m_nFatalErrorIndex++;
		strStr = /*"严重"*/g_sLangTxt_SCLCompare_Serious;
		strStr.AppendFormat("%d ",m_nFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;
	}

	pResultRec->m_strErrorType = strStr;
	pResultRec->m_strErrorText = errorMessage;

	if(publicId)
	{
		pResultRec->m_strErrorText += ";public id:";
#ifdef _PSX_IDE_QT_
		pResultRec->m_strErrorText += (const char *)publicId;
#else
		pResultRec->m_strErrorText += publicId;
#endif
	}

// 	pResultRec->m_strErrorPos = "行号=";
// 	pResultRec->m_strErrorPos.AppendFormat("%d" ,rowNumber);
// 	pResultRec->m_strErrorPos += " ,";
// 	CString strLinetxt = "列号=";
// 	pResultRec->m_strErrorPos += strLinetxt;
// 	pResultRec->m_strErrorPos.AppendFormat("%d" ,columnNumber);
	//strStr = "%s=%d ,%s=%d";
	//pResultRec->m_strErrorPos.Format(strStr.GetString(), g_sLangTxt_SCLCompare_RowNum.GetString(), rowNumber, g_sLangTxt_SCLCompare_ColumnNum.GetString(), columnNumber);
	FormatString(pResultRec->m_strErrorPos, "%s=%d ,%s=%d", g_sLangTxt_SCLCompare_RowNum.GetString(), rowNumber, g_sLangTxt_SCLCompare_ColumnNum.GetString(), columnNumber);
	return rc;
}

void CContentHandleObject::FormatString(CString &strText, const char *strFormat, ...)
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlSchemaCheckTool::CXmlSchemaCheckTool()
{
	XMLPlatformUtils::Initialize();
	m_pResultsRec = NULL;
	m_strDomType = XML_CHECK_TYPE_DOM;

	m_strXsdPath = "";
	m_strXmlPath = "";
	m_pXmlCheckObjectThread = NULL;
	m_nHasCheckFinished = TRUE;
}

CXmlSchemaCheckTool::~CXmlSchemaCheckTool()
{
	FreeProgCheckThread();
	XMLPlatformUtils::Terminate();
}

void CXmlSchemaCheckTool::InitCheck(const CString strDomType,CResultsRec *pResultsRec)
{
	m_strDomType = strDomType;
	m_pResultsRec = pResultsRec;
}

void CXmlSchemaCheckTool::FreeProgCheckThread()
{
 #ifdef _PSX_IDE_QT_
	if (m_pXmlCheckObjectThread != NULL)
	{
		m_pXmlCheckObjectThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pXmlCheckObjectThread->wait();
		m_pXmlCheckObjectThread = NULL;
	}
#endif
}

//执行dom schema验证

int CXmlSchemaCheckTool::StartCheckXmlValid(const CString &xsd_string,const CString &xml_input)
{
	m_strXsdPath = xsd_string;
	m_strXmlPath = xml_input;
//	StartCheckXmlValid();
 #ifdef _PSX_IDE_QT_
	FreeProgCheckThread();
	m_nHasCheckFinished = FALSE;
 	m_pXmlCheckObjectThread = new CWinThread(ProgCheckThread, this);
	m_pXmlCheckObjectThread->m_bAutoDelete = FALSE;
 	m_pXmlCheckObjectThread->ResumeThread();
 #else
 	m_pXmlCheckObjectThread = AfxBeginThread(ProgCheckThread, this); //启动线程 
 	m_pXmlCheckObjectThread->m_bAutoDelete = TRUE;
 #endif

	return 1;

}

UINT CXmlSchemaCheckTool::ProgCheckThread(LPVOID pParam)
{
	CXmlSchemaCheckTool *pXmlCheckObject = (CXmlSchemaCheckTool *)pParam;
	return pXmlCheckObject->StartCheckXmlValid();
}

BOOL CXmlSchemaCheckTool::StartCheckXmlValid()
{
// 	CFile file;
// 
// 	if(!file.Open(m_strXmlPath.GetString(),CFile::modeRead|CFile::typeText))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件(%s)打开失败."),m_strXmlPath);
// 		m_nHasCheckFinished = TRUE;
// 		return 0;
// 	}

// 	long nLength = file.GetLength();
// 	char *pSclFileBuffer = new char [nLength+50];
// 	file.Read(pSclFileBuffer,nLength);
// 	pSclFileBuffer[nLength] = 0;
// 
// 	file.Close();
//
//	const char * pszXml = pSclFileBuffer;

	if (m_strDomType == XML_CHECK_TYPE_DOM)
	{
		XercesDOMParser parser;
		CContentHandleObject contentHandleObject;

		int rc = -1;
		contentHandleObject.m_pResultsRec = m_pResultsRec;

		parser.setErrorHandler(&contentHandleObject);

		//zhouhj 2023.11.26 置为false防止SCD检测时间太长
		parser.setIdentityConstraintChecking(false);

		parser.setDoNamespaces(true);   
		parser.setCreateEntityReferenceNodes(true);   
		parser.useCachedGrammarInParse(true); 
		parser.setDoSchema(true); 
		parser.setValidationScheme( XercesDOMParser::Val_Always);     
		parser.setValidationSchemaFullChecking(true);   

		if(parser.loadGrammar(m_strXsdPath.GetString()/*memBufXsdString*/, Grammar::SchemaGrammarType, true) == NULL)   
		{   
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*"导入检验语法串错误,请确认语法串正确."*/g_sLangTxt_SCLCompare_GrammerInvalid);
		} 

// 		MemBufInputSource memBufXmlString((const XMLByte*)pszXml,strlen(pszXml),"待测模型文件检查；",false); //构建内存xml流
// 		parser.parse(memBufXmlString);

		try
		{
			parser.parse(m_strXmlPath.GetString());
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("Schema语法检查中出现异常(CMemoryException).")*/g_sLangTxt_SCLCompare_CMemoryException);
		}

		m_pResultsRec->m_nAllWarningIndex = contentHandleObject.m_nWarningIndex;
		m_pResultsRec->m_nAllErrorIndex = contentHandleObject.m_nErrorIndex;
		m_pResultsRec->m_nAllFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);

		pResultRec->m_strErrorType = /*"结果统计"*/g_sLangTxt_SCLCompare_ResultStatistic;
		pResultRec->m_strErrorText = "\\";
		pResultRec->m_strErrorPos = "\\";
		pResultRec->m_nWarningIndex = contentHandleObject.m_nWarningIndex;
		pResultRec->m_nErrorIndex = contentHandleObject.m_nErrorIndex;
		pResultRec->m_nFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		if(parser.getErrorCount() == 0)
			rc = 0;
	} 
	else
	{
		int rc = -1;

		SAX2XMLReader* pParser = NULL;
		pParser = XMLReaderFactory::createXMLReader(); 

		CContentHandleObject contentHandleObject;
		contentHandleObject.m_pResultsRec = m_pResultsRec;
//		pParser->setContentHandler(&contentHandleObject); //设置内容处理句柄对象
		pParser->setErrorHandler(&contentHandleObject); 

		pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);//如果将这项属性设置为true，那么该解析器就支持名称空间，否则忽略。
		pParser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, true);//如果将这项属性设置为true，那么该解析器就支持名称空间前缀，否则忽略。
//这是一个非常重要的属性，正如fgXercesValidationErrorAsFatal名字的含义一样，如果该属性设置为true，那么当解析器执行校验时，将校验错误看作是致命的，系统就停止解析
 		pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, false);
 		pParser->setFeature(XMLUni::fgSAX2CoreValidation, false);
 		pParser->setFeature(XMLUni::fgXercesSchema, true);
 		pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
		//这是设置缓存属性，是否缓存加载的schema内容。
		pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);

		

		if(pParser->loadGrammar(m_strXsdPath.GetString()/*memXsdString*/, Grammar::SchemaGrammarType, true) == NULL)   
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*"导入检验语法串错误,请确认语法串正确."*/g_sLangTxt_SCLCompare_GrammerInvalid);
		}

// 		MemBufInputSource memXmlString((const XMLByte*)pszXml,strlen(pszXml),"business input check",false); //构建内存xml流
// 		pParser->parse(memXmlString);

		try
		{
			pParser->parse(m_strXmlPath.GetString());
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("Schema语法检查中出现异常(CMemoryException).")*/g_sLangTxt_SCLCompare_CMemoryException);
		}
		
		m_pResultsRec->m_nAllWarningIndex = contentHandleObject.m_nWarningIndex;
		m_pResultsRec->m_nAllErrorIndex = contentHandleObject.m_nErrorIndex;
		m_pResultsRec->m_nAllFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);

		pResultRec->m_strErrorType = /*"结果统计"*/g_sLangTxt_SCLCompare_ResultStatistic;
		pResultRec->m_strErrorText = "\\";
		pResultRec->m_strErrorPos = "\\";
		pResultRec->m_nWarningIndex = contentHandleObject.m_nWarningIndex;
		pResultRec->m_nErrorIndex = contentHandleObject.m_nErrorIndex;
		pResultRec->m_nFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		if(pParser->getErrorCount() == 0)
			rc = 0;
		delete pParser;
	}

	m_nHasCheckFinished = TRUE;
	return 1;
}
