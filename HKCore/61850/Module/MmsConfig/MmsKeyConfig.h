#pragma once
#include "../MmsApi.h"
#include "MmsEngineConfigGlobal.h"

class CMmsKeyConfig : public CExBaseObject
{
public:
	CMmsKeyConfig();
	virtual ~CMmsKeyConfig();

	CString m_strFile;
	
public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return _bstr_t("mms-key-config");	}

private:
	void ReadFlag(CXmlRWNodeBase &oNode, BSTR bstrFlagNode, long *pnArrFlag, long nCount);
	void WriteFlag(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, BSTR bstrFlagNode, long *pnArrFlag, long nCount);
};
