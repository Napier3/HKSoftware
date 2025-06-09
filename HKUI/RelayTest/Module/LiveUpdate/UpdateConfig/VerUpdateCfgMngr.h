#pragma once

#include "VerUpdateCfgYun.h"
#include "VerUpdateCfgSyses.h"

class CVerUpdateCfgMngr : public CExBaseList
{
public:
	CVerUpdateCfgMngr();
	virtual ~CVerUpdateCfgMngr();

	//重载函数
public:
	virtual UINT GetClassID() {    return VERUPDATECFGCLASSID_MNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateCfgXmlRWKeys::VerUpdateCfgKey();     }
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

private:
	CString m_strVerFileRoot;

	CVerUpdateCfgYun*  m_pCfgYun;
	CVerUpdateCfgSyses* m_pCfgSyses;

public:
	CString GetCfgFile();
	BOOL Open();
	BOOL Save();

	CString GetVerFileRoot()			{	return m_strVerFileRoot;  }
	void SetVerFileRoot(const CString& strRoot)	{	m_strVerFileRoot = strRoot;	 }

	CVerUpdateCfgYun* GetCfgYun()		{   return m_pCfgYun;	}
	CVerUpdateCfgSyses* GetCfgSyses()	{   return m_pCfgSyses;	}
};


