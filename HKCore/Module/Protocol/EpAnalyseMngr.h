//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpAnalyseMngr.h  CEpAnalyseMngr

#pragma once

#include "EpAnalyseStringGlobal.h"


#include "EpAnalyseString.h"

class CEpAnalyseMngr : public CExBaseList
{
public:
	CEpAnalyseMngr();
	virtual ~CEpAnalyseMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return EPASCLASSID_CEPANALYSEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CEpAnalyseStringXmlRWKeys::CEpAnalyseMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

