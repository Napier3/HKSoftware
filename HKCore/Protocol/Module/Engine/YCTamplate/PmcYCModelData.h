#pragma once

class CPmcYCModelData :public CExBaseObject
{
public:
	CPmcYCModelData(void);
	virtual ~CPmcYCModelData(void);

public:
	//¶ÁÐ´
	virtual long XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

public:
	CString m_strUnit;
};
