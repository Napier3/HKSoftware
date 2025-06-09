#include "StdAfx.h"
#include "GbtDataScript.h"
#include "GbtDataInterfaces.h"

#include "../../../Module/KeyDb/XMatchList.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbtDataKey::CGbtDataKey(void)
{
	m_strName = g_sLangTxt_DataMatchScript/*_T("数据匹配脚本")*/;
}

CGbtDataKey::~CGbtDataKey(void)
{
}

long CGbtDataKey::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataKey::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	return 0;
}

long CGbtDataKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);


	return 0;
}

CBaseObject* CGbtDataKey::Clone()
{
	CGbtDataKey* pGbtDataScript = new CGbtDataKey();
	Copy(pGbtDataScript);

	return pGbtDataScript;
}

//////////////////////////////////////////////////////////////////////////
CGbtDataOptr::CGbtDataOptr(void)
{
	m_strName = _T("And");
	m_strID= _T("And");
	m_dwValue = 0;
}

CGbtDataOptr::~CGbtDataOptr(void)
{
}

long CGbtDataOptr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataOptr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	return 0;
}

long CGbtDataOptr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbtDataOptr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptOptrAndKey)
	{
		return new CGbtDataOptrAnd();
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptOptrOrKey)
	{
		return new CGbtDataOptrOr();
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptOptrNotKey)
	{
		return new CGbtDataOptrNot();
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptFuncMustHaveKey)
	{
		return new CGbtDataFuncMustHave();
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScptFuncMustNotHaveKey)
	{
		return new CGbtDataFuncMustNotHave();
	}

// 	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataKeyKey)
// 	{
// 		return new CGbtDataKey();
// 	}

	return NULL;
}

DWORD CGbtDataOptr::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
	POS pos = GetHeadPosition();
	CGbtDataScptObj *pScptObj = NULL;

	while (pos != NULL)
	{
		pScptObj = (CGbtDataScptObj *)GetNext(pos);
		pScptObj->ScptCal(pXMatchObj, bAllMatchMode);
	}

	return 0;
}

CExBaseObject* CGbtDataOptr::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GBTDATASCPTOPTR_AND)
	{
		return new CGbtDataOptrAnd();
	}

	if (nClassID == GBCLASSID_GBTDATASCPTOPTR_OR)
	{
		return new CGbtDataOptrOr();
	}

	if (nClassID == GBCLASSID_GBTDATASCPTOPTR_NOT)
	{
		return new CGbtDataOptrNot();
	}

	if (nClassID == GBCLASSID_GBTDATASCPTFUNC_MUSTHAVE)
	{
		return new CGbtDataFuncMustHave();
	}

	if (nClassID == GBCLASSID_GBTDATASCPTFUNC_MUSTNOTHAVE)
	{
		return new CGbtDataFuncMustNotHave();
	}

	return NULL;
}

//And
CGbtDataOptrAnd::CGbtDataOptrAnd(void)
{
	m_strName = _T("And");
	m_strID= _T("And");
}

CGbtDataOptrAnd::~CGbtDataOptrAnd(void)
{
}

CBaseObject* CGbtDataOptrAnd::Clone()
{
	CGbtDataOptrAnd* pGbtDataOptr = new CGbtDataOptrAnd();
	Copy(pGbtDataOptr);

	return pGbtDataOptr;
}

DWORD CGbtDataOptrAnd::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
	CGbtDataOptr::ScptCal(pXMatchObj, bAllMatchMode);

	POS pos = GetHeadPosition();
	CGbtDataScptObj *pScptObj = NULL;
	m_dwValue = 1;

	while (pos != NULL)
	{
		pScptObj = (CGbtDataScptObj *)GetNext(pos);
		
		if (pScptObj->m_dwValue < 1)
		{
			m_dwValue = 0;
			break;
		}
	}

	return m_dwValue;
}

//Or
CGbtDataOptrOr::CGbtDataOptrOr(void)
{
	m_strName = _T("Or");
	m_strID= _T("Or");
}

CGbtDataOptrOr::~CGbtDataOptrOr(void)
{
}

CBaseObject* CGbtDataOptrOr::Clone()
{
	CGbtDataOptrOr* pGbtDataOptr = new CGbtDataOptrOr();
	Copy(pGbtDataOptr);

	return pGbtDataOptr;
}


DWORD CGbtDataOptrOr::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
	CGbtDataOptr::ScptCal(pXMatchObj, bAllMatchMode);

	POS pos = GetHeadPosition();
	CGbtDataScptObj *pScptObj = NULL;
	m_dwValue = 0;

	while (pos != NULL)
	{
		pScptObj = (CGbtDataScptObj *)GetNext(pos);

		if (pScptObj->m_dwValue >= 1)
		{
			m_dwValue = 1;
			break;
		}
	}

	return m_dwValue;
}


//Not
CGbtDataOptrNot::CGbtDataOptrNot(void)
{
	m_strName = _T("Not");
	m_strID= _T("Not");
}

CGbtDataOptrNot::~CGbtDataOptrNot(void)
{
}

CBaseObject* CGbtDataOptrNot::Clone()
{
	CGbtDataOptrNot* pGbtDataOptr = new CGbtDataOptrNot();
	Copy(pGbtDataOptr);

	return pGbtDataOptr;
}


DWORD CGbtDataOptrNot::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
	CGbtDataOptr::ScptCal(pXMatchObj, bAllMatchMode);

	POS pos = GetHeadPosition();
	CGbtDataScptObj *pScptObj = NULL;
	m_dwValue = 0;

	while (pos != NULL)
	{
		pScptObj = (CGbtDataScptObj *)GetNext(pos);

		if (pScptObj->m_dwValue >= 1)
		{
			m_dwValue = 1;
			break;
		}
	}

	return m_dwValue;
}


//////////////////////////////////////////////////////////////////////////
CGbtDataFunc::CGbtDataFunc(void)
{
	m_strName = _T("Func");
	m_strID= _T("Func");
}

CGbtDataFunc::~CGbtDataFunc(void)
{
}

long CGbtDataFunc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataFunc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	return 0;
}

long CGbtDataFunc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbtDataFunc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataKeyKey)
	{
		return new CGbtDataKey();
	}

	return NULL;
}

CExBaseObject* CGbtDataFunc::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GBTDATAKEY)
	{
		return new CGbtDataKey();
	}

	return NULL;
}

//MustHave
CGbtDataFuncMustHave::CGbtDataFuncMustHave(void)
{
	m_strName = g_sLangTxt_Include/*_T("包含")*/;
	m_strID= _T("must-have");
}

CGbtDataFuncMustHave::~CGbtDataFuncMustHave(void)
{
}

CBaseObject* CGbtDataFuncMustHave::Clone()
{
	CGbtDataFuncMustHave* pGbtDataOptr = new CGbtDataFuncMustHave();
	Copy(pGbtDataOptr);

	return pGbtDataOptr;
}

DWORD CGbtDataFuncMustHave::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
#ifdef DVM_USE_MAP
	POS pos = GetHeadPosition();
	CGbtDataKey *pKey = NULL;
	CXMatchObject *pXObj = (CXMatchObject*)pXMatchObj;
	CXKeyMatchRefList *pXKeyList = &pXObj->m_listMatchXKeys;

	if (bAllMatchMode)
	{
		m_dwValue = 1;

		while (pos != NULL)
		{
			pKey = (CGbtDataKey *)GetNext(pos);

			if (pXKeyList->FindByID(pKey->m_strID) == NULL && pXKeyList->FindByName(pKey->m_strName) == NULL)
			{
				m_dwValue = 0;
				break;
			}
		}
	}
	else
	{
		m_dwValue = 0;

		while (pos != NULL)
		{
			pKey = (CGbtDataKey *)GetNext(pos);

			//if (pXKeyList->FindByID(pKey->m_strID) != NULL)
			if (pXKeyList->FindByName(pKey->m_strName) != NULL)
			{
				m_dwValue++;
			}
		}

		pXObj->m_dwItemData = m_dwValue;
	}
#endif

	return m_dwValue;
}

//MustNotHave
CGbtDataFuncMustNotHave::CGbtDataFuncMustNotHave(void)
{
	m_strName = g_sLangTxt_CertainUninclude/*_T("必须不包含")*/;
	m_strID= _T("must-not-have");
}

CGbtDataFuncMustNotHave::~CGbtDataFuncMustNotHave(void)
{
}

CBaseObject* CGbtDataFuncMustNotHave::Clone()
{
	CGbtDataFuncMustNotHave* pGbtDataOptr = new CGbtDataFuncMustNotHave();
	Copy(pGbtDataOptr);

	return pGbtDataOptr;
}


DWORD CGbtDataFuncMustNotHave::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
#ifdef DVM_USE_MAP
	POS pos = GetHeadPosition();
	CGbtDataKey *pKey = NULL;
	CXKeyMatchRefList *pXKeyList = &((CXMatchObject*)pXMatchObj)->m_listMatchXKeys;
	m_dwValue = 1;

	while (pos != NULL)
	{
		pKey = (CGbtDataKey *)GetNext(pos);

		//if (pXKeyList->FindByID(pKey->m_strID) != NULL)
		if (pXKeyList->FindByName(pKey->m_strName) != NULL 
			|| pXKeyList->FindByID(pKey->m_strID) != NULL)
		{
			m_dwValue = 0;
			break;
		}
	}
#endif

	return m_dwValue;
}


//////////////////////////////////////////////////////////////////////////
CGbtDataScript::CGbtDataScript(void)
{
	m_strName = g_sLangTxt_DataMatchScript/*_T("数据匹配脚本")*/;
}

CGbtDataScript::~CGbtDataScript(void)
{
}

long CGbtDataScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strStandNameKey,oNode,m_strStandName);
	
	return 0;
}

long CGbtDataScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStandNameKey, oElement, m_strStandName);

	return 0;
}

long CGbtDataScript::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbtDataScript::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
// 	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataKey)
// 	{
// 		return new CDataObj();
// 	}

	return CGbtDataOptr::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);;
}

CExBaseObject* CGbtDataScript::CreateNewChild(long nClassID)
{
// 	if (nClassID == GBCLASSID_DATAOBJ)
// 	{
// 		return new CDataObj();
// 	}

	return CGbtDataOptr::CreateNewChild(nClassID);
}

CBaseObject* CGbtDataScript::Clone()
{
	CGbtDataScript* pGbtDataScript = new CGbtDataScript();
	Copy(pGbtDataScript);

	pGbtDataScript->m_strStandName = m_strStandName;

	return pGbtDataScript;
}

DWORD CGbtDataScript::ScptCal(CExBaseObject *pXMatchObj, BOOL bAllMatchMode)
{
	if (GetCount() == 0)
	{
		CGbtData *pGbtData = GetRefGbtData();

		if (pGbtData != NULL)
		{
			CXMatchObject *pXMatch = (CXMatchObject*)pXMatchObj;

			if (pXMatch->m_pRefObject->m_strName.Find(pGbtData->m_strName) >= 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return CGbtDataOptrAnd::ScptCal(pXMatchObj, bAllMatchMode);
	}
}

CGbtData* CGbtDataScript::GetRefGbtData()
{
	CGbtDataInterfaces *pGbtDataInterfaces = (CGbtDataInterfaces*)GetAncestor(GBCLASSID_GBTDATAINTERFACES);
	ASSERT (pGbtDataInterfaces != NULL);

	if (pGbtDataInterfaces == NULL)
	{
		return NULL;
	}

	ASSERT (pGbtDataInterfaces->m_pGbtDatas != NULL);

	if (pGbtDataInterfaces->m_pGbtDatas == NULL)
	{
		return NULL;
	}

	CGbtData *pGbtData = (CGbtData*)(pGbtDataInterfaces->m_pGbtDatas->FindByID(m_strID));

	return pGbtData;
}

BOOL CGbtDataScript::InitGbtData()
{
	CGbtData *pGbtData = GetRefGbtData();

	if (pGbtData != NULL)
	{
		return FALSE;
	}

	CGbtDataInterfaces *pGbtDataInterfaces = (CGbtDataInterfaces*)GetAncestor(GBCLASSID_GBTDATAINTERFACES);
	ASSERT (pGbtDataInterfaces != NULL);

	if (pGbtDataInterfaces == NULL)
	{
		return FALSE;
	}

	ASSERT (pGbtDataInterfaces->m_pGbtDatas != NULL);

	if (pGbtDataInterfaces->m_pGbtDatas == NULL)
	{
		return FALSE;
	}

	CGbtDatas *pGbtDatas = pGbtDataInterfaces->m_pGbtDatas;
	POS pos = pGbtDatas->GetHeadPosition();
	CGbtDataInterface *pGbtDataInterface = (CGbtDataInterface*)GetParent();
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pGbtData = (CGbtData *)pGbtDatas->GetNext(pos);

		if (pGbtData->IsGbtScriptObj())
		{
			if (pGbtDataInterface->FindByID(pGbtData->m_strID) == NULL)
			{
				InitGbtData(pGbtData);
				bTrue = TRUE;
				break;
			}
		}
	}

	return bTrue;
}

void CGbtDataScript::InitGbtData(CGbtData *pGbtData)
{
	m_strName = pGbtData->m_strName;
	m_strID = pGbtData->m_strID;
}

