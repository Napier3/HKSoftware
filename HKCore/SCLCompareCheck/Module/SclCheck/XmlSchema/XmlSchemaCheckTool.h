#if !defined(AFX_XMLCHECKOBJECT_H__AA275D58_55FB_4578_9FBA_3D94F739371A__INCLUDED_)
#define AFX_XMLCHECKOBJECT_H__AA275D58_55FB_4578_9FBA_3D94F739371A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\xercesc\INTERNAL_STRUCTURES.h"

#include "..\ResultsRec.h"

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>

#include <string>
#include <xercesc/dom/DOMDocument.hpp>   
#include <xercesc/dom/DOM.hpp>

#ifdef XERCES_CPP_NAMESPACE_USE 
XERCES_CPP_NAMESPACE_USE
#endif

#include "..\ResultsRec.h"

#define XML_CHECK_TYPE_DOM               _T("DOM")

class CContentHandleObject : public DefaultHandler  
{
public:
	CContentHandleObject();
	virtual ~CContentHandleObject();

	long m_nErrorIndex;
	long m_nWarningIndex;
	long m_nFatalErrorIndex;

	CResultsRec *m_pResultsRec;

	const char* GetErrorMessage(){return m_strErrorMessage.c_str();}
	const char* GetContent(){return m_strContent.c_str();}
	void FormatString(CString &strText, const char *strFormat, ...);
private:
	virtual void startDocument();
	virtual void endDocument();
private:
	virtual void warning(const SAXParseException& exc);
	virtual void error(const SAXParseException& exc);
	virtual void fatalError(const SAXParseException& exc); 
private:
	bool SaveErrorMessage(const XMLCh* errorMessage,int rowNumber,int columnNumber,const XMLCh* publicId,const XMLCh* systemId  ,int nErrorType);
private:
	std::string m_strErrorMessage;
	std::string m_strContent;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CXmlSchemaCheckTool  
{
public:
	CXmlSchemaCheckTool();
	virtual ~CXmlSchemaCheckTool();

	void InitCheck(const CString strDomType,CResultsRec *pResultsRec);
    int StartCheckXmlValid(const CString &xsd_string,const CString &xml_input); //用dom解析器进行xml文档的验证
	BOOL m_nHasCheckFinished;//是否检测完成

protected:
	BOOL StartCheckXmlValid();
	void FreeProgCheckThread();
	static UINT ProgCheckThread(LPVOID pParam);

	CWinThread *m_pXmlCheckObjectThread;
	CString m_strXsdPath;
	CString m_strXmlPath;
	CResultsRec *m_pResultsRec;
	CString m_strDomType;
};

#endif
