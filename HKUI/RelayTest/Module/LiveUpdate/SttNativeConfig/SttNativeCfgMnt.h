#pragma once

#include "SttNativeCfgMngrGlobal.h"

class CSttNativeCfgMnt : public CExBaseObject
{
public:
	CSttNativeCfgMnt();
	virtual ~CSttNativeCfgMnt();

public:
	CString m_strRootFiles;
	
	//重载函数
public:
	virtual UINT GetClassID() {    return STTNATIVECFGCLASSID_MNT;   }
	virtual BSTR GetXmlElementKey()  {      return CSttNativeCfgXmlRWKeys::MntKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);

public:
	CString GetRootFiles()	{	return m_strRootFiles;	  }
	void SetRootFiles(const CString& strRootFiles)	{	m_strRootFiles = strRootFiles;	}
};


