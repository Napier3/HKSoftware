#pragma once

#include "VerUpdateCfgMngrGlobal.h"

class CVerUpdateCfgMap : public CExBaseObject
{
public:
	CVerUpdateCfgMap();
	virtual ~CVerUpdateCfgMap();

private:
	CString m_strShellPath;
	long    m_idxSys;

	//重载函数
public:
	virtual UINT GetClassID() {    return VERUPDATECFGCLASSID_MAP;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateCfgXmlRWKeys::MapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	
public:
	CString GetShellPath()	{	return m_strShellPath;	}
	long GetIdxSys()		{	return m_idxSys;	}

	void SetShellPath(const CString& strShellPath)	{	m_strShellPath = strShellPath;	}
	void SetIdxSys(long idxSys)	{	m_idxSys = idxSys;	}
};


