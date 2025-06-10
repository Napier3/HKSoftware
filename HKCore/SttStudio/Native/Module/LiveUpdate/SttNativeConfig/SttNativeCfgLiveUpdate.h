#pragma once

#include "SttNativeCfgHisVer.h"

class CSttNativeCfgLiveUpdate : public CExBaseList
{
public:
	CSttNativeCfgLiveUpdate();
	virtual ~CSttNativeCfgLiveUpdate();

	CString m_strID_System;
	long m_nIndex_System;

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return STTNATIVECFGCLASSID_LIVEUPDATE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttNativeCfgXmlRWKeys::LiveUpdateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();
	
private:
	CSttNativeCfgHisVer*	m_pCfgHisVer;

public:
	CSttNativeCfgHisVer* GetCfgHisVer()	{	return m_pCfgHisVer;	}
	void UpdateHisVer(const CString& strDateTime,int nIndex_Sys,int nCurrVerIdx,const CString& strCurVer);
};


