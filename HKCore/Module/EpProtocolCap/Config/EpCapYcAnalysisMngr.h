//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapYcAnalysisMngr.h  CEpCapYcAnalysisMngr

#pragma once

#include "MonitorCapConfigGlobal.h"


#include "EpCapYcAnalysis.h"

class CEpCapYcAnalysisMngr : public CExBaseList
{
public:
	CEpCapYcAnalysisMngr();
	virtual ~CEpCapYcAnalysisMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPYCANALYSISMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEpCapYcAnalysisMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CString GetConfigFile();

//˽�г�Ա�������ʷ���
public:
	void OpenYcDrawConfigFile();
	void SaveYcDrawConfigFile();
};

