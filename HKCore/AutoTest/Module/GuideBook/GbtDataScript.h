#pragma once

#include "GuideBookDefine.h"
#include "GbtData.h"

class CGbtDataKey :public CExBaseObject
{
public:
	CGbtDataKey(void);
	virtual ~CGbtDataKey(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATAKEY;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataKeyKey ;	}

	virtual CBaseObject* Clone();

};


class CGbtDataScptObj : public CExBaseList
{
public:
	CGbtDataScptObj(void)
	{
		m_dwValue = 0;
	}

	virtual ~CGbtDataScptObj(void)
	{

	}
	DWORD m_dwValue;

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode) = 0;
};

//////////////////////////////////////////////////////////////////////////
class CGbtDataOptr :public CGbtDataScptObj
{
public:
	CGbtDataOptr(void);
	virtual ~CGbtDataOptr(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTOPTR;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScriptKey ;	}

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);

};

class CGbtDataOptrAnd :public CGbtDataOptr
{
public:
	CGbtDataOptrAnd(void);
	virtual ~CGbtDataOptrAnd(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTOPTR_AND;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptOptrAndKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);
};

class CGbtDataOptrOr :public CGbtDataOptr
{
public:
	CGbtDataOptrOr(void);
	virtual ~CGbtDataOptrOr(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTOPTR_OR;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptOptrOrKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);
};


class CGbtDataOptrNot :public CGbtDataOptr
{
public:
	CGbtDataOptrNot(void);
	virtual ~CGbtDataOptrNot(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTOPTR_NOT;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptOptrNotKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);
};


//////////////////////////////////////////////////////////////////////////
class CGbtDataFunc :public CGbtDataScptObj
{
public:
	CGbtDataFunc(void);
	virtual ~CGbtDataFunc(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTFUNC;		}

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode) = 0;

};

class CGbtDataFuncMustHave :public CGbtDataFunc
{
public:
	CGbtDataFuncMustHave(void);
	virtual ~CGbtDataFuncMustHave(void);

public:
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTFUNC_MUSTHAVE;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptFuncMustHaveKey ;	}
	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);

};

class CGbtDataFuncMustNotHave :public CGbtDataFunc
{
public:
	CGbtDataFuncMustNotHave(void);
	virtual ~CGbtDataFuncMustNotHave(void);

public:
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCPTFUNC_MUSTNOTHAVE;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptFuncMustNotHaveKey ;	}
	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);
};

//////////////////////////////////////////////////////////////////////////
class CGbtDataScript :public CGbtDataOptrAnd
{
public:
	CGbtDataScript(void);
	virtual ~CGbtDataScript(void);
	
	static CGbtDataScript* _New(CExBaseObject *pParent)
	{
		CGbtDataScript *pNew = new CGbtDataScript();
		pNew->SetParent(pParent);
		return pNew;
	}

	CString m_strStandName;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATASCRIPT;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScriptKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode);
	CGbtData* GetRefGbtData();
	BOOL InitGbtData();
	void InitGbtData(CGbtData *pGbtData);
};

inline BOOL GbtDataScript_IsFunc(UINT nClassID)
{
	return ((nClassID == GBCLASSID_GBTDATASCPTFUNC_MUSTNOTHAVE)
		|| (nClassID == GBCLASSID_GBTDATASCPTFUNC_MUSTHAVE));
}

inline BOOL GbtDataScript_IsOptr(UINT nClassID)
{
	return ((nClassID == GBCLASSID_GBTDATASCPTOPTR_AND)
		|| (nClassID == GBCLASSID_GBTDATASCPTOPTR_OR)
		|| (nClassID == GBCLASSID_GBTDATASCPTOPTR_NOT) );
}

