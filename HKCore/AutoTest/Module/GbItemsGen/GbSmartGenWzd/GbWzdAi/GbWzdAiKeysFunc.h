#pragma once

#include "GbWzdAiBase.h"

//////////////////////////////////////////////////////////////////////////
class CGbAiKeysFunc :public CGbAiOptrInterface
{
public:
	CGbAiKeysFunc(void);
	virtual ~CGbAiKeysFunc(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	virtual void InitGbAiDataKey(CXKeyDB *pKeyDB);

};

class CGbAiKeysFuncMustHave :public CGbAiKeysFunc
{
public:
	CGbAiKeysFuncMustHave(void);
	virtual ~CGbAiKeysFuncMustHave(void);

public:
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTHAVE;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptFuncMustHaveKey ;	}
	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};

class CGbAiKeysFuncMustNotHave :public CGbAiKeysFunc
{
public:
	CGbAiKeysFuncMustNotHave(void);
	virtual ~CGbAiKeysFuncMustNotHave(void);

public:
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTNOTHAVE;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptFuncMustNotHaveKey ;	}
	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
};
