#pragma once

#include "VerUpdateCfgMngrGlobal.h"

class CVerUpdateCfgSys : public CExBaseObject
{
public:
	CVerUpdateCfgSys();
	virtual ~CVerUpdateCfgSys();

private:
	CString m_strType;
	
	CString m_strRunPath;
	CString m_strVerPath;
	CString m_strBackupPath;

	long    m_idxSys;

	//重载函数
public:
	virtual UINT GetClassID() {    return VERUPDATECFGCLASSID_SYS;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateCfgXmlRWKeys::SysKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);

public:
	CString GetType()		{	return m_strType;	}
	CString GetRunPath()	{	return m_strRunPath;	}
	CString GetVerPath()	{	return m_strVerPath;	}
	CString GetBackupPath()	{	return m_strBackupPath;	}
	long GetIdxSys()		{	return m_idxSys;	}

	void SetType(const CString& strType)		{	m_strType = strType;	}
	void SetRunPath(const CString& strRunPath)	{	m_strRunPath = strRunPath;	}
	void SetVerPath(const CString& strVerPath)	{	m_strVerPath = strVerPath;	}
	void SetBackupPath(const CString& strBackupPath)	{	m_strBackupPath = strBackupPath;	}
	void SetIdxSys(long idxSys)	{	m_idxSys = idxSys;	}
};


