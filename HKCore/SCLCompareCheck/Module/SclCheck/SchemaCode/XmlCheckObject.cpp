// XmlCheckObject.cpp: implementation of the CXmlCheckObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlCheckObject.h"

//#include "..\WaitingTimeDlg.h"


#include <xercesc/sax2/SAX2XMLReader.hpp>//sax2解析器
#include <xercesc/sax2/XMLReaderFactory.hpp> //sax2解析器管理器

#include <xercesc/util/OutOfMemoryException.hpp>   
#include <xercesc/dom/DOM.hpp>   
#include <xercesc/parsers/XercesDOMParser.hpp>   
#include <xercesc/framework/XMLGrammarDescription.hpp>   
#include <xercesc/sax/ErrorHandler.hpp>   
#include <xercesc/sax/SAXParseException.hpp> 
#include <xercesc/framework/MemBufInputSource.hpp> //xml内存对象

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlCheckObject::CXmlCheckObject(CWnd *pWnd)
{
	XMLPlatformUtils::Initialize();
	m_pResultsRec = NULL;
	m_bDomType = true;

	m_strXsdPath = "";
	m_strXmlPath = "";
	m_pXmlCheckObjectThread = NULL;

	m_pMsgWnd = pWnd;
}

CXmlCheckObject::~CXmlCheckObject()
{
	XMLPlatformUtils::Terminate();
}

//执行dom schema验证

int CXmlCheckObject::SchemaCheckMap(const char* xsd_string,const char* xml_input)
{
	m_strXsdPath = xsd_string;
	m_strXmlPath = xml_input;
	StartCheckXmlValid();
// #ifdef _PSX_IDE_QT_
// 	m_pXmlCheckObjectThread = new CWinThread(ProgCheckThread, this);
// 	m_pXmlCheckObjectThread->ResumeThread();
// #else
// 	m_pXmlCheckObjectThread = AfxBeginThread(ProgCheckThread, this); //启动线程 
// 	m_pXmlCheckObjectThread->m_bAutoDelete = TRUE;
// #endif

	return 1;

}

UINT CXmlCheckObject::ProgCheckThread(LPVOID pParam)
{
	CXmlCheckObject *pXmlCheckObject = (CXmlCheckObject *)pParam;

	return pXmlCheckObject->StartCheckXmlValid();

// 	CString xmlString;//记录scl文件的内容
// 	CString xsdString;//记录对应xsd文件的内容

	CFile file;
//	CString buffer;

//	xmlString.Empty();
//	buffer.Empty();

	if(!file.Open(pXmlCheckObject->m_strXmlPath.GetString(),CFile::modeRead|CFile::typeText))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件(%s)打开失败."),pXmlCheckObject->m_strXmlPath);
		return 0;
	}

	long nLength = file.GetLength();
	char *pSclFileBuffer = new char [nLength+50];
	file.Read(pSclFileBuffer,nLength);
	pSclFileBuffer[nLength] = 0;

// 	while(file.Read(buffer))
// 	{
// 		xmlString += buffer;
// 		xmlString += "\r\n";
// 	}

	file.Close();


// 	xsdString.Empty();
// 	buffer.Empty();
	if(!file.Open(pXmlCheckObject->m_strXsdPath.GetString(),CFile::modeRead|CFile::typeText))
	{
		delete pSclFileBuffer;
		return 0;
	}

	nLength = file.GetLength();
	char *pXsdFileBuffer = new char [nLength+50];
	file.Read(pXsdFileBuffer,nLength);
	pXsdFileBuffer[nLength] = 0;

// 	while(file.ReadString(buffer))
// 	{
// 		xsdString += buffer;
// 	}

	file.Close();

	const char * pszXml = pSclFileBuffer;
	const char * pszXsd = pXsdFileBuffer;

	if (pXmlCheckObject->m_bDomType)
	{
		XercesDOMParser parser;
		CContentHandleObject contentHandleObject;

		int rc = -1;
		contentHandleObject.m_pResultsRec = pXmlCheckObject->m_pResultsRec;

		parser.setErrorHandler(&contentHandleObject);

		parser.setIdentityConstraintChecking(true);

		parser.setDoNamespaces(true);   
		parser.setCreateEntityReferenceNodes(true);   
		parser.useCachedGrammarInParse(true); 
		parser.setDoSchema(true); 
		parser.setValidationScheme( XercesDOMParser::Val_Always);     
		parser.setValidationSchemaFullChecking(true);   

		MemBufInputSource memBufXsdString((const XMLByte*)pszXsd,strlen(pszXsd),"Schema文件本身检查；",false);

		if(parser.loadGrammar(memBufXsdString, Grammar::SchemaGrammarType, true) == NULL)   
		{   
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,"导入检验语法串错误,请确认语法串正确.");
		} 

		MemBufInputSource memBufXmlString((const XMLByte*)pszXml,strlen(pszXml),"待测模型文件检查；",false); //构建内存xml流

		parser.parse(memBufXmlString);

		pXmlCheckObject->m_pResultsRec->m_nAllWarningIndex = contentHandleObject.m_nWarningIndex;
		pXmlCheckObject->m_pResultsRec->m_nAllErrorIndex = contentHandleObject.m_nErrorIndex;
		pXmlCheckObject->m_pResultsRec->m_nAllFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		CResultRec *pResultRec = new CResultRec;
		pXmlCheckObject->m_pResultsRec->AddNewChild(pResultRec);

		pResultRec->m_strErrorType ="结果统计：";
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
		contentHandleObject.m_pResultsRec = pXmlCheckObject->m_pResultsRec;
//		pParser->setContentHandler(&contentHandleObject); //设置内容处理句柄对象
		pParser->setErrorHandler(&contentHandleObject); 

		//	pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
		//	pParser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, true);
		pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, false);
		pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
		pParser->setFeature(XMLUni::fgXercesSchema, true);
		pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);	  
		pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);

		MemBufInputSource memXsdString((const XMLByte*)pszXsd,strlen(pszXsd),"business input check xsd file");
		if(pParser->loadGrammar(memXsdString, Grammar::SchemaGrammarType, true) == NULL)   
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,"导入检验语法串错误,请确认语法串正确.");
		}

		MemBufInputSource memXmlString((const XMLByte*)pszXml,strlen(pszXml),"business input check",false); //构建内存xml流
		pParser->parse(memXmlString);
		pXmlCheckObject->m_pResultsRec->m_nAllWarningIndex = contentHandleObject.m_nWarningIndex;
		pXmlCheckObject->m_pResultsRec->m_nAllErrorIndex = contentHandleObject.m_nErrorIndex;
		pXmlCheckObject->m_pResultsRec->m_nAllFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		CResultRec *pResultRec = new CResultRec;
		pXmlCheckObject->m_pResultsRec->AddNewChild(pResultRec);

		pResultRec->m_strErrorType ="结果统计：";
		pResultRec->m_strErrorText = "\\";
		pResultRec->m_strErrorPos = "\\";
		pResultRec->m_nWarningIndex = contentHandleObject.m_nWarningIndex;
		pResultRec->m_nErrorIndex = contentHandleObject.m_nErrorIndex;
		pResultRec->m_nFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		if(pParser->getErrorCount() == 0)
			rc = 0;
		delete pParser;
	}

//	CWaitingTimeDlg::g_bOver =  true;

// 	if (pXmlCheckObject->m_pMsgWnd != NULL)
// 	{
// 		pXmlCheckObject->m_pMsgWnd->SendMessage(WM_XMLCHECKCLASSID_OBJECT);
// 	}

	return 1;
}

BOOL CXmlCheckObject::StartCheckXmlValid()
{
	CFile file;

	if(!file.Open(m_strXmlPath.GetString(),CFile::modeRead|CFile::typeText))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件(%s)打开失败."),m_strXmlPath);
		return 0;
	}

	long nLength = file.GetLength();
	char *pSclFileBuffer = new char [nLength+50];
	file.Read(pSclFileBuffer,nLength);
	pSclFileBuffer[nLength] = 0;

	file.Close();

	if(!file.Open(m_strXsdPath.GetString(),CFile::modeRead|CFile::typeText))
	{
		delete pSclFileBuffer;
		return 0;
	}

	nLength = file.GetLength();
	char *pXsdFileBuffer = new char [nLength+50];
	file.Read(pXsdFileBuffer,nLength);
	pXsdFileBuffer[nLength] = 0;

	// 	while(file.ReadString(buffer))
	// 	{
	// 		xsdString += buffer;
	// 	}

	file.Close();

	const char * pszXml = pSclFileBuffer;
	const char * pszXsd = pXsdFileBuffer;

	if (m_bDomType)
	{
		XercesDOMParser parser;
		CContentHandleObject contentHandleObject;

		int rc = -1;
		contentHandleObject.m_pResultsRec = m_pResultsRec;

		parser.setErrorHandler(&contentHandleObject);

		parser.setIdentityConstraintChecking(true);

		parser.setDoNamespaces(true);   
		parser.setCreateEntityReferenceNodes(true);   
		parser.useCachedGrammarInParse(true); 
		parser.setDoSchema(true); 
		parser.setValidationScheme( XercesDOMParser::Val_Always);     
		parser.setValidationSchemaFullChecking(true);   

		MemBufInputSource memBufXsdString((const XMLByte*)pszXsd,strlen(pszXsd),"Schema文件本身检查；",false);

		if(parser.loadGrammar(memBufXsdString, Grammar::SchemaGrammarType, true) == NULL)   
		{   
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,"导入检验语法串错误,请确认语法串正确.");
		} 

		MemBufInputSource memBufXmlString((const XMLByte*)pszXml,strlen(pszXml),"待测模型文件检查；",false); //构建内存xml流

		parser.parse(memBufXmlString);

		m_pResultsRec->m_nAllWarningIndex = contentHandleObject.m_nWarningIndex;
		m_pResultsRec->m_nAllErrorIndex = contentHandleObject.m_nErrorIndex;
		m_pResultsRec->m_nAllFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);

		pResultRec->m_strErrorType ="结果统计：";
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

		//	pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
		//	pParser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, true);
		pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, false);
		pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
		pParser->setFeature(XMLUni::fgXercesSchema, true);
		pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);	  
		pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);

		MemBufInputSource memXsdString((const XMLByte*)pszXsd,strlen(pszXsd),"business input check xsd file");
		if(pParser->loadGrammar(memXsdString, Grammar::SchemaGrammarType, true) == NULL)   
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,"导入检验语法串错误,请确认语法串正确.");
		}

		MemBufInputSource memXmlString((const XMLByte*)pszXml,strlen(pszXml),"business input check",false); //构建内存xml流
		pParser->parse(memXmlString);
		m_pResultsRec->m_nAllWarningIndex = contentHandleObject.m_nWarningIndex;
		m_pResultsRec->m_nAllErrorIndex = contentHandleObject.m_nErrorIndex;
		m_pResultsRec->m_nAllFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		CResultRec *pResultRec = new CResultRec;
		m_pResultsRec->AddNewChild(pResultRec);

		pResultRec->m_strErrorType ="结果统计：";
		pResultRec->m_strErrorText = "\\";
		pResultRec->m_strErrorPos = "\\";
		pResultRec->m_nWarningIndex = contentHandleObject.m_nWarningIndex;
		pResultRec->m_nErrorIndex = contentHandleObject.m_nErrorIndex;
		pResultRec->m_nFatalErrorIndex = contentHandleObject.m_nFatalErrorIndex;

		if(pParser->getErrorCount() == 0)
			rc = 0;
		delete pParser;
	}

	//	CWaitingTimeDlg::g_bOver =  true;

	// 	if (pXmlCheckObject->m_pMsgWnd != NULL)
	// 	{
	// 		pXmlCheckObject->m_pMsgWnd->SendMessage(WM_XMLCHECKCLASSID_OBJECT);
	// 	}

	return 1;
}
