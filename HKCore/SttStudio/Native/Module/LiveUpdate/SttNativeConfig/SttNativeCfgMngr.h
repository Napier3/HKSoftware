#pragma once

#include "SttNativeCfgYun.h"
#include "SttNativeCfgLiveUpdate.h"
#include "SttNativeCfgMnt.h"

class CSttNativeCfgMngr : public CExBaseList
{
public:
	CSttNativeCfgMngr();
	virtual ~CSttNativeCfgMngr();

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return STTNATIVECFGCLASSID_MNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttNativeCfgXmlRWKeys::SttNativeCfgKey();     }
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

private:
	CSttNativeCfgYun*			m_pCfgYun;
	CSttNativeCfgLiveUpdate*	m_pCfgLiveUpdate;
	CSttNativeCfgMnt*		m_pCfgMnt;
public:
	CString GetCfgFile();
	BOOL Open();
	BOOL Save();

	CSttNativeCfgYun* GetCfgYun()				{   return m_pCfgYun;	}
	CSttNativeCfgLiveUpdate* GetCfgLiveUpdate()	{   return m_pCfgLiveUpdate;	}
	CSttNativeCfgMnt* GetCfgMnt()	{	return m_pCfgMnt;		}
};


