#pragma once

#include "GbWzdAiOptr.h"

//////////////////////////////////////////////////////////////////////////
class CGbAiParaScript :public CGbAiOptrAnd
{
public:
	CGbAiParaScript(void);
	virtual ~CGbAiParaScript(void);
	
	static CGbAiParaScript* _New(CExBaseObject *pParent)
	{
		CGbAiParaScript *pNew = new CGbAiParaScript();
		pNew->SetParent(pParent);
		return pNew;
	}

	CString m_strDataType;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiScript;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiScriptKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

private:
	//集合对象的初始化接口，例如Key、OptrInterface等对象
	void InitGbAiDataKey(CExBaseList *pList, CXKeyDB *pKeyDB);
	
};
