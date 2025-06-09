#pragma once

#include "SttNativeCfgMngrGlobal.h"

class CSttNativeCfgHisVer : public CExBaseObject
{
public:
	CSttNativeCfgHisVer();
	virtual ~CSttNativeCfgHisVer();

	CString m_strDateTime;
	long	m_nCurrVerIdx;
	long	m_nPrevVerIdx;
	CString m_strCurrVer;
	CString m_strPrevVer;
	long    m_nUpdateDeviceXml;

	//重载函数
public:
	virtual UINT GetClassID() {    return STTNATIVECFGCLASSID_HISVER;   }
	virtual BSTR GetXmlElementKey()  {      return CSttNativeCfgXmlRWKeys::HisVerKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
};


