#pragma once
#include "../../../Module/BaseClass/ExBaseList.h"

#define SCLCLASSID_CHECK_DATA    0x00001001
#define SCLCLASSID_CHECK_CHANNEL 0x00001002

class CResultRec : public CExBaseList
{
public:
	CResultRec();
	virtual ~CResultRec();

	CString m_strErrorType;
	CString m_strErrorText;
	CString m_strErrorPos;

	long m_nTipIndex;
	long m_nWarningIndex;
	long m_nErrorIndex;
	long m_nFatalErrorIndex;


//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CHECK_CHANNEL;   }
// 	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CLogCtrlKey();     }
// 
// #ifdef XML_USE_TINYXML
// 
// 	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
// 
// #else
// 
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 
// #endif
};

//////////////////////////////////////////////////////////////////////////
