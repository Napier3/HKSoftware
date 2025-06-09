#pragma once

#include "GuideBookDefine.h"
//#include "..\..\..\Module\DataMngr\ShortData.h"
#include "DataSet.h"
#include "../../../Module/DataMngr/DataTypeValue.h"

class CGbtData :public CDataObj
{
public:
	CGbtData(void);
	virtual ~CGbtData(void);

	static CGbtData* _New(CExBaseObject *pParent)
	{
		CGbtData *pNew = new CGbtData();
		pNew->SetParent(pParent);
		pNew->InitAfterRead();
		return pNew;
	}
	
public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATA;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataKey ;	}

	virtual CBaseObject* Clone();
	virtual void InitAfterRead();

public:
	BOOL IsGbtScriptObj();
	BOOL IsBatchObj();
	CDataTypeValue* GetDataTypeValue();
};

//////////////////////////////////////////////////////////////////////////
class CGbtDatas : public CDataSet
{
public:
	CGbtDatas(void);
	virtual ~CGbtDatas(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATAS;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDatasKey ;	}

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

public:
	BOOL IsBatchGbtDataMode();
	void CreateGbtDatas(CExBaseList *pDatas);
};


extern const CString g_strGbtDatasName;

inline BOOL Gbt_IsOptrObject(CExBaseObject *pObj)
{
	ASSERT (pObj != NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();
	CExBaseList *pList = NULL;

	if (nClassID == GBCLASSID_GBTDATASCPTOPTR_AND
		|| nClassID == GBCLASSID_GBTDATASCPTOPTR_OR
		|| nClassID == GBCLASSID_GBTDATASCPTOPTR_NOT
		|| nClassID == GBCLASSID_GBTDATASCRIPT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


inline BOOL Gbt_IsFuncObject(CExBaseObject *pObj)
{
	ASSERT (pObj != NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();
	CExBaseList *pList = NULL;

	if (nClassID == GBCLASSID_GBTDATASCPTFUNC_MUSTHAVE 
		|| nClassID == GBCLASSID_GBTDATASCPTFUNC_MUSTNOTHAVE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}