//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpAnalyseStringVal.h  CEpAnalyseStringVal

#pragma once

#include "EpAnalyseStringGlobal.h"



class CEpAnalyseStringVal : public CExBaseObject
{
public:
	CEpAnalyseStringVal();
	virtual ~CEpAnalyseStringVal();


	CString  m_strValue;
	CString  m_strValue2;
//���غ���
public:
	virtual UINT GetClassID() {    return EPASCLASSID_CEPANALYSESTRINGVAL;   }
	virtual BSTR GetXmlElementKey()  {      return CEpAnalyseStringXmlRWKeys::CEpAnalyseStringValKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL IsValueIn(const CString &strValue);
};