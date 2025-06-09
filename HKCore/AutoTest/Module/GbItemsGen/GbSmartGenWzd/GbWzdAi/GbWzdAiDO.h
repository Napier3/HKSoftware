#pragma once

#include "GbWzdAiBase.h"


//////////////////////////////////////////////////////////////////////////
class CGbWzdAiDoAttr : public CExBaseObject
{
public:
	CGbWzdAiDoAttr(void);
	virtual ~CGbWzdAiDoAttr(void);

	CString m_strAttrID;
	CString m_strOptr;
	CString m_strValue;

public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDOAttr;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDoAttrKey ;	}
	virtual CBaseObject* Clone();

public:
	virtual void InitGbAiDataKey(CXKeyDB *pKeyDB);
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};


//////////////////////////////////////////////////////////////////////////
class CGbWzdAiDO :public CGbAiOptrBase
{
public:
	CGbWzdAiDO(void);
	virtual ~CGbWzdAiDO(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDO;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDoKey ;	}
	virtual CBaseObject* Clone();

public:
	virtual void InitGbAiDataKey(CXKeyDB *pKeyDB);
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};
