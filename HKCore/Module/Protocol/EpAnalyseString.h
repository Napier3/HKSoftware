//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpAnalyseString.h  CEpAnalyseString

#pragma once

#include "EpAnalyseStringGlobal.h"


#include "EpAnalyseStringVal.h"

class CEpAnalyseString : public CExBaseList
{
public:
	CEpAnalyseString();
	virtual ~CEpAnalyseString();


	CString  m_strString;
//���غ���
public:
	virtual UINT GetClassID() {    return EPASCLASSID_CEPANALYSESTRING;   }
	virtual BSTR GetXmlElementKey()  {      return CEpAnalyseStringXmlRWKeys::CEpAnalyseStringKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CEpAnalyseStringVal* FindByValue(const CString &strValue);
};

