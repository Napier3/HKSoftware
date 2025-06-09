// ParseResultHandleObject.h: interface for the CContentHandleObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTENTHANDLEOBJECT_H__0F447ED4_C511_43B8_8787_1522AD5372F9__INCLUDED_)
#define AFX_CONTENTHANDLEOBJECT_H__0F447ED4_C511_43B8_8787_1522AD5372F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>

#include "..\ResultsRec.h"

#ifdef XERCES_CPP_NAMESPACE_USE 
XERCES_CPP_NAMESPACE_USE
#endif

#include <string>

class CContentHandleObject : public DefaultHandler  
{
public:
	long m_nErrorIndex;
	long m_nWarningIndex;
	long m_nFatalErrorIndex;

	CResultsRec *m_pResultsRec;
public:
	CContentHandleObject();
	virtual ~CContentHandleObject();
public:
	const char* GetErrorMessage(){return m_strErrorMessage.c_str();}
	const char* GetContent(){return m_strContent.c_str();}
private:
  virtual void startDocument();
  virtual void endDocument();
//   virtual void startElement(const XMLCh* const uri,const XMLCh* const localname,const XMLCh* const qname,const Attributes& attrs);
//   virtual void endElement(const XMLCh* const uri,const XMLCh* const localname,const XMLCh* const qname);
//   virtual void characters(const XMLCh* const chars,const unsigned int length);
//   virtual void skippedEntity(const	XMLCh* const name);
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

#endif // !defined(AFX_CONTENTHANDLEOBJECT_H__0F447ED4_C511_43B8_8787_1522AD5372F9__INCLUDED_)
