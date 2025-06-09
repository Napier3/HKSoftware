//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapYcAnalysisMngr.h  CEpCapYcAnalysisMngr

#pragma once

#include "MonitorCapConfigGlobal.h"


#include "EpCapYcAnalysis.h"

class CEpCapYcAnalysisMngr : public CExBaseList
{
public:
	CEpCapYcAnalysisMngr();
	virtual ~CEpCapYcAnalysisMngr();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPYCANALYSISMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEpCapYcAnalysisMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CString GetConfigFile();

//私有成员变量访问方法
public:
	void OpenYcDrawConfigFile();
	void SaveYcDrawConfigFile();
};

