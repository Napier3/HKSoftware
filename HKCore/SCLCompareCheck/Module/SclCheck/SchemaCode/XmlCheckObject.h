// XmlCheckObject.h: interface for the CXmlCheckObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLCHECKOBJECT_H__AA275D58_55FB_4578_9FBA_3D94F739371A__INCLUDED_)
#define AFX_XMLCHECKOBJECT_H__AA275D58_55FB_4578_9FBA_3D94F739371A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\xercesc\INTERNAL_STRUCTURES.h"
//#pragma comment(lib,"xerces-c_3.lib")

#include "..\ResultsRec.h"
#include "ContentHandleObject.h"  //
#include <string>

#include <xercesc/dom/DOMDocument.hpp>   
#include <xercesc/dom/DOM.hpp>
#define WM_XMLCHECKCLASSID_OBJECT             (WM_USER + 1902)

const int  max_xsd_buffer = 1024*20;

class CXmlCheckObject  
{
public:
	CXmlCheckObject(CWnd *pWnd = NULL);
	virtual ~CXmlCheckObject();

	CResultsRec *m_pResultsRec;
	bool m_bDomType;
	
    CString m_strXsdPath;
	CString m_strXmlPath;

	static UINT ProgCheckThread(LPVOID pParam);

    int SchemaCheckMap(const char* xsd_string,const char* xml_input); //用dom解析器进行xml文档的验证
	CWinThread *m_pXmlCheckObjectThread;
	BOOL StartCheckXmlValid();

private:
	CWnd *m_pMsgWnd;

};

//设定遍历的过滤器对象
class  MyFilter : public DOMNodeFilter 
{
public:
  MyFilter(short nodeType, bool reject=false) : DOMNodeFilter(), fNodeType(nodeType), fReject(reject) {};
  virtual FilterAction acceptNode(const DOMNode* node) const
  {
	  if (fNodeType == 0)
		  return  DOMNodeFilter::FILTER_ACCEPT;
	  if (node->getNodeType() ==  fNodeType) 
	  {
		  return  DOMNodeFilter::FILTER_ACCEPT;
	  }
	  else 
	  {
		  return  fReject ? DOMNodeFilter::FILTER_REJECT : DOMNodeFilter::FILTER_SKIP;
	  }
  }
private:
    short fNodeType;
    bool fReject;
};

#endif // !defined(AFX_XMLCHECKOBJECT_H__AA275D58_55FB_4578_9FBA_3D94F739371A__INCLUDED_)
