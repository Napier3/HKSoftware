#include "stdafx.h"
#include "GbStxmlFileMap.h"
#include "GbInsertStxmlFileTool.h"
#include "..\GuideBook\GbCommCmdSplit.h"
#include "..\..\..\Module\MemBuffer\BufferBase.h"
#include "..\XLanguageResourceAts.h"
//////////////////////////////////////////////////////////////////////////
//映射组别功能

//////////////////////////////////////////////////////////////////////////
CGbtDataScriptMapFilter::CGbtDataScriptMapFilter()
{
	m_nKeyCount = 0;
	m_dwFilterOptr = GBTSCRIPTMAP_FILTER_AND;
}

CGbtDataScriptMapFilter::~CGbtDataScriptMapFilter()
{

}

BOOL CGbtDataScriptMapFilter::Filter(const CString &strName)
{
	if (m_dwFilterOptr == GBTSCRIPTMAP_FILTER_AND)
	{
		return Filter_And(strName);
	}

	if (m_dwFilterOptr == GBTSCRIPTMAP_FILTER_OR)
	{
		return Filter_Or(strName);
	}

	return TRUE;
}

BOOL CGbtDataScriptMapFilter::ParseScript(const CString &strScript)
{
	m_nKeyCount = 0;

	if (strScript.GetLength() == 0)
	{
		return FALSE;
	}

	long nPosAnd = strScript.Find('+');
	long nPosOr  = strScript.Find('-');

	if (nPosOr >= 0 && nPosAnd >= 0)
	{
		return FALSE;
	}

	CBufferBase oBuffer;
	oBuffer.InitBuffer(strScript);
	m_dwFilterOptr = GBTSCRIPTMAP_FILTER_AND;

	if (nPosAnd >= 0)
	{
		m_dwFilterOptr = GBTSCRIPTMAP_FILTER_AND;
		oBuffer.FormatBuffer('+');
	}

	if (nPosOr >= 0)
	{
		m_dwFilterOptr = GBTSCRIPTMAP_FILTER_OR;
		oBuffer.FormatBuffer('-');
	}

	while (oBuffer.IsPoiterInBuffer())
	{
		m_astrKey[m_nKeyCount] = oBuffer.GetString();
		oBuffer.NextString();
		m_nKeyCount++;
	}

	return TRUE;
}

BOOL CGbtDataScriptMapFilter::Filter_And(const CString &strName)
{
	long nIndex = 0;
	BOOL bMatch = TRUE;

	for (nIndex=0; nIndex<m_nKeyCount; nIndex++)
	{
		if (strName.Find(m_astrKey[nIndex]) < 0)
		{
			bMatch = FALSE;
			break;
		}
	}

	return bMatch;
}

BOOL CGbtDataScriptMapFilter::Filter_Or(const CString &strName)
{
	long nIndex = 0;
	BOOL bMatch = FALSE;

	for (nIndex=0; nIndex<m_nKeyCount; nIndex++)
	{
		if (strName.Find(m_astrKey[nIndex]) >= 0)
		{
			bMatch = TRUE;
			break;
		}
	}

	return bMatch;
}


//////////////////////////////////////////////////////////////////////////
//
CGbtDataScriptMap::CGbtDataScriptMap()
{
	m_pRefObject = NULL;
	m_pGbtDataScript = NULL;
}

CGbtDataScriptMap::~CGbtDataScriptMap()
{
	RemoveAll();
}


CBaseObject* CGbtDataScriptMap::Clone()
{
	CGbtDataScriptMap *pNew = new CGbtDataScriptMap();
	Copy(pNew);
	return pNew;
}

BOOL CGbtDataScriptMap::CopyOwn(CBaseObject* pDest)
{
	((CGbtDataScriptMap*)pDest)->m_pGbtDataScript = m_pGbtDataScript;
	((CGbtDataScriptMap*)pDest)->m_pRefObject = m_pRefObject;
	((CGbtDataScriptMap*)pDest)->m_strDataValue = m_strDataValue;
	((CGbtDataScriptMap*)pDest)->m_strRefObjName = m_strRefObjName;
	((CGbtDataScriptMap*)pDest)->m_strRefObjPath = m_strRefObjPath;

	return CExBaseObject::CopyOwn(pDest);
}


long CGbtDataScriptMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strDataValueKey, oNode, m_strDataValue);
	xml_GetAttibuteValue(pXmlKeys->m_strRefObjNameKey, oNode, m_strRefObjName);
	xml_GetAttibuteValue(pXmlKeys->m_strRefObjPathKey, oNode, m_strRefObjPath);

	return 0;
}

long CGbtDataScriptMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataValueKey, oElement, m_strDataValue);
	xml_SetAttributeValue(pXmlKeys->m_strRefObjNameKey, oElement, m_strRefObjName);
	xml_SetAttributeValue(pXmlKeys->m_strRefObjPathKey, oElement, m_strRefObjPath);

	return 0;
}

CExBaseObject* CGbtDataScriptMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}


void CGbtDataScriptMap::InitByCopy(CGbtDataScriptMap *pSrc)
{
	RemoveAll();
	POS pos = pSrc->GetHeadPosition();

	m_strDataValue = pSrc->m_strDataValue;
	m_strRefObjName = pSrc->m_strRefObjName;
	m_strRefObjPath = pSrc->m_strRefObjPath;
	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;

	CGbInsertStxmlFileTool *pTool = (CGbInsertStxmlFileTool*)GetAncestor(GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL);
	CDevice *pDevice = pTool->GetCurrDeviceDest();

	if (pDevice == NULL)
	{
		return;
	}

	ASSERT (pDevice->m_pCpus != NULL);

	if (pDevice->m_pCpus == NULL)
	{
		return;
	}

	if (m_strRefObjPath.GetLength() > 0)
	{
		CDataObj *pDataObj = pDevice->m_pCpus->SelectDataObj(m_strRefObjPath);

		if (pDataObj != NULL)
		{
			m_pRefObject = pDataObj;
			AddTail(pDataObj);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("【%s】对应的数据集数据不存在")*/g_sLangTxt_DatasetNotExist, m_strRefObjPath);
		}
	}
}


BOOL CGbtDataScriptMap::Copy(CBaseObject* pDest)
{	
	CopyOwn(pDest);

	((CExBaseList*)pDest)->RemoveAll();
	((CExBaseList*)pDest)->Append(this);
	
	pDest->InitAfterRead(); 

	return TRUE;
}

void CGbtDataScriptMap::SetRefObject(CExBaseObject *pRefObject, BOOL bRemoveAll)
{
	if (bRemoveAll)
	{
		RemoveAll();
	}

	if (pRefObject != NULL)
	{
		AddTail(pRefObject);
		m_strRefObjName = pRefObject->m_strName;
		m_strRefObjPath = pRefObject->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}
	else
	{
		m_strRefObjName.Empty();
		m_strRefObjPath.Empty();
	}

	m_pRefObject = pRefObject;
}

void CGbtDataScriptMap::InitGbtDataScript(CGbtDataScript *pGbtDataScript)
{
	m_pGbtDataScript = pGbtDataScript;
	m_strName = pGbtDataScript->m_strName;
	m_strID = pGbtDataScript->m_strID;
}


void CGbtDataScriptMap::FilterByScript(CGbtDataScriptMapFilter &oFilter)
{
	if (GetCount() == 1)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList oListFilter;

	if (oFilter.m_dwFilterMode == GBTSCRIPTMAP_FILTER_MODE_HAVE)
	{
		while (pos != NULL)
		{
			p = GetNext(pos);

			if (oFilter.Filter(p->m_strName))
			{
				oListFilter.AddTail(p);
			}
		}
		
		RemoveAll();
		Append(oListFilter);
		oListFilter.RemoveAll();
		return;
	}

	if (oFilter.m_dwFilterMode == GBTSCRIPTMAP_FILTER_MODE_NOTHAVE)
	{
		while (pos != NULL)
		{
			p = GetNext(pos);

			if (!oFilter.Filter(p->m_strName))
			{
				oListFilter.AddTail(p);
			}
		}

		RemoveAll();
		Append(oListFilter);
		oListFilter.RemoveAll();
		return;
	}
}

void CGbtDataScriptMap::XMatch(CXMatchList &oXMatchList, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	if (bNotUpdateSingle)
	{
		if (GetCount() == 1)
		{
			return;
		}
	}

	if (bNotUpdateNone)
	{
		if (GetCount() == 0)
		{
			return;
		}
	}

	POS pos = oXMatchList.GetHeadPosition();
	CXMatchObject *pXMatch = NULL;
	RemoveAll();

	if (m_pGbtDataScript->m_strStandName.GetLength() > 0)
	{
		pos = oXMatchList.GetHeadPosition();

		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)oXMatchList.GetNext(pos);

			if (pXMatch->m_pRefObject->m_strName.Find(m_pGbtDataScript->m_strStandName) >= 0)
			{
				AddRefObject(pXMatch->m_pRefObject);
				pXMatch->m_pRefObject->m_dwReserved = 100;
			}
		}
	}


	//if (GetCount() == 0)
	{
		pos = oXMatchList.GetHeadPosition();

		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)oXMatchList.GetNext(pos);

			if (m_pGbtDataScript->ScptCal(pXMatch, TRUE) > 0)
			{
				pXMatch->m_pRefObject->m_dwReserved = pXMatch->m_dwReserved;
				AddRefObject(pXMatch->m_pRefObject);
				pXMatch->m_pRefObject->m_dwReserved = 100;
			}
		}
	}

	//if (GetCount() == 0)
	{
		pos = oXMatchList.GetHeadPosition();

		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)oXMatchList.GetNext(pos);

			if (m_pGbtDataScript->ScptCal(pXMatch, FALSE) > 0)
			{
				pXMatch->m_pRefObject->m_dwReserved = pXMatch->m_dwReserved;
				AddRefObject(pXMatch->m_pRefObject);
			}
		}
	}

	if (GetCount() == 1)
	{
		//SetRefObject((CExBaseObject*)GetTail());
		m_pRefObject = (CExBaseObject*)GetTail();
		m_strRefObjName = m_pRefObject->m_strName;
		m_strRefObjPath = m_pRefObject->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}
	else
	{
		m_pRefObject = NULL;
		m_strRefObjName.Empty();
		m_strRefObjPath.Empty();
	}

	Short();
}

void CGbtDataScriptMap::AddRefObject(CExBaseObject *pRefObj)
{
	if (Find(pRefObj) == NULL)
	{
		AddTail(pRefObj);
	}
}

void CGbtDataScriptMap::Short()
{
	if (GetCount() > 1)
	{
		CExBaseList oListTemp;
		POS pos = GetHeadPosition();
		POS posSort = NULL;
		CExBaseObject *pSort = NULL;
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = (CExBaseObject *)GetNext(pos);
			posSort = oListTemp.GetHeadPosition();
			BOOL bSort = FALSE;

			if (posSort == NULL)
			{
				oListTemp.AddTail(p);
				continue;
			}

			while(posSort != NULL)
			{
				pSort = (CExBaseObject *)oListTemp.GetAt(posSort);

				if (p->m_dwReserved > pSort->m_dwReserved)
				{
					oListTemp.InsertBefore(posSort, p);
					bSort = TRUE;
					break;
				}

				GetNext(posSort);
			}

			if (!bSort)
			{
				oListTemp.AddTail(p);
			}
		}

		RemoveAll();

		pos = oListTemp.GetHeadPosition();

		while (pos != NULL)
		{
			p = (CExBaseObject *)oListTemp.GetNext(pos);

			if (Find(p) == NULL)
			{
				AddTail(p);
			}
		}
		
		oListTemp.RemoveAll();
	}
}

BOOL CGbtDataScriptMap::HasAllKey(const CStringArray &astrKey, const CString &strName)
{
	long nCount = astrKey.GetCount();
	long nIndex = 0;
	BOOL bTrue = TRUE;
	CString strKey;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strKey = astrKey.GetAt(nIndex);

		if (strName.Find(strKey) < 0)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

BOOL CGbtDataScriptMap::HasKey(const CStringArray &astrKey, const CString &strName)
{
	long nCount = astrKey.GetCount();
	long nIndex = 0;
	BOOL bTrue = FALSE;
	CString strKey;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strKey = astrKey.GetAt(nIndex);

		if (strName.Find(strKey) >= 0)
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

void CGbtDataScriptMap::XMatch(CXMatchList &oXMatchList, const CStringArray &strKey, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	if (bNotUpdateSingle)
	{
		if (GetCount() == 1)
		{
			return;
		}
	}

	XMatch(oXMatchList, bNotUpdateSingle, bNotUpdateNone);
	
	if (strKey.GetCount() == 0)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *pRef = NULL;
	POS posCurr = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		pRef = (CExBaseObject*)GetNext(pos);

		if ( HasKey(strKey, pRef->m_strName) )
		{
			
		}
		else
		{
			RemoveAt(posCurr);
		}
	}

	if (GetCount() == 1)
	{
		m_pRefObject = (CExBaseObject*)GetTail();
	}
	else
	{
		m_pRefObject = NULL;
	}

	SetRefObject(m_pRefObject, FALSE);
}

BOOL CGbtDataScriptMap::InitRefObject()
{
	if (GetCount() == 1)
	{
		m_pRefObject = (CExBaseObject*)GetTail();
	}
	else
	{
		m_pRefObject = NULL;
	}

	return (m_pRefObject != NULL);
}

CString CGbtDataScriptMap::GetGbtDataScriptValue()
{
	CString strText;
	CDevice *pDevice = (CDevice*)m_pGbtDataScript->GetAncestor(GBCLASSID_DEVICE);
	CGbtDatas *pGbtDatas = pDevice->m_pGbtDataInterfaces->m_pGbtDatas;
	CGbtData *pData = (CGbtData*)pGbtDatas->FindByID(m_pGbtDataScript->m_strID);

	if (m_strDataValue.GetLength() > 0)
	{
		strText = m_strDataValue;
	}
	else
	{
		if (pData != NULL)
		{
			strText = pData->m_strValue;
		}
		else
		{
			strText = _T("0");
		}
	}

	return strText;
}

CString CGbtDataScriptMap::GetRefObjIDPath()
{
	CString strText;

	if (m_pRefObject == NULL)
	{
		CDevice *pDevice = (CDevice*)m_pGbtDataScript->GetAncestor(GBCLASSID_DEVICE);
		CGbtDatas *pGbtDatas = pDevice->m_pGbtDataInterfaces->m_pGbtDatas;
		CGbtData *pData = (CGbtData*)pGbtDatas->FindByID(m_pGbtDataScript->m_strID);

		if (m_strDataValue.GetLength() > 0)
		{
			strText = m_strDataValue;
		}
		else
		{
			if (pData != NULL)
			{
				strText = pData->m_strValue;
			}
			else
			{
				strText = _T("0");
			}
		}
	}
	else
	{
		UINT nClassID = m_pRefObject->GetClassID();
		CDataObj *pData = (CDataObj*)m_pRefObject;
		pData->GetIDForPath(strText);
	}

	return strText;
}

//////////////////////////////////////////////////////////////////////////
CGbtDataInterfaceMap::CGbtDataInterfaceMap()
{
	m_pGbtDataInterface = NULL;

}

CGbtDataInterfaceMap::~CGbtDataInterfaceMap()
{

}

CBaseObject* CGbtDataInterfaceMap::Clone()
{
	CGbtDataInterfaceMap *pNew = new CGbtDataInterfaceMap();
	Copy(pNew);
	return pNew;
}

BOOL CGbtDataInterfaceMap::CopyOwn(CBaseObject* pDest)
{
	((CGbtDataInterfaceMap*)pDest)->m_pGbtDataInterface = m_pGbtDataInterface;

	return CExBaseObject::CopyOwn(pDest);
}


long CGbtDataInterfaceMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataInterfaceMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CGbtDataInterfaceMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtDataScriptMapKey())
	{
		return new CGbtDataScriptMap();
	}

	return NULL;
}

void CGbtDataInterfaceMap::InitByCopy(CGbtDataInterfaceMap *pSrc)
{
	POS pos = pSrc->GetHeadPosition();
	CGbtDataScriptMap *p = NULL;
	CGbtDataScriptMap *pFind = NULL;

	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;

	while (pos != NULL)
	{
		p = (CGbtDataScriptMap *)pSrc->GetNext(pos);
		pFind = (CGbtDataScriptMap *)FindByID(p->m_strID);

		if (pFind != NULL)
		{
			pFind->InitByCopy(p);
		}
	}
}

void CGbtDataInterfaceMap::InitGbtDataInterface(CGbtDataInterface *pGbtDataInterface)
{
	CGbtDataScriptMap *pNew = NULL;
	POS pos = pGbtDataInterface->GetHeadPosition();
	CGbtDataScript *pScript = NULL;
	m_pGbtDataInterface = pGbtDataInterface;

	m_strName = pGbtDataInterface->m_strName;
	m_strID = pGbtDataInterface->m_strID;

	while (pos != NULL)
	{
		pScript = (CGbtDataScript *)pGbtDataInterface->GetNext(pos);
		pNew = new CGbtDataScriptMap();
		AddNewChild(pNew);
		pNew->InitGbtDataScript(pScript);
	}
}

void CGbtDataInterfaceMap::XMatch(CXMatchList &oXMatchList, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		pMap->XMatch(oXMatchList, bNotUpdateSingle, bNotUpdateNone);
	}
}

void CGbtDataInterfaceMap::FilterByScript(CGbtDataScriptMapFilter &oFilter)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		pMap->FilterByScript(oFilter);
	}
}

void CGbtDataInterfaceMap::XMatch(CXMatchList &oXMatchList, const CStringArray &strKey, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		pMap->XMatch(oXMatchList, strKey, bNotUpdateSingle, bNotUpdateNone);
	}
}

BOOL CGbtDataInterfaceMap::CanInsert()
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		
		if (pMap->InitRefObject() != NULL)
		{
			nCount++;
		}
	}

	return (/*(GetCount() == nCount) &&*/( nCount > 0) );
}

BOOL CGbtDataInterfaceMap::ValidateMapKeys(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);

		if (pMap->GetCount() > 1)
		{
			nCount++;
			strErrorMsg.Format(/*_T("数据接口映射【%s】不唯一")*/g_sLangTxt_DataMapNotOnly, pMap->m_strName);
		}
	}

	return ( nCount == 0 );
}

CGbInsertStxmlFile::CGbInsertStxmlFile()
{
	m_bInsertFileRoot =  TRUE;
	m_strName = _T("第1组");
	m_strID = _T("Items1");
	m_strKey = _T("");
	m_pGbtDataInterfaces = NULL;
	m_nAddRptGroupTitle = 1;

	m_pRptEditDest = NULL;
	m_pRptEditSrc = NULL;
}

CGbInsertStxmlFile::~CGbInsertStxmlFile()
{
	m_listDataset.RemoveAll();
}


CBaseObject* CGbInsertStxmlFile::Clone()
{
	CGbInsertStxmlFile *pNew = new CGbInsertStxmlFile();
	Copy(pNew);
	return pNew;
}

BOOL CGbInsertStxmlFile::CopyOwn(CBaseObject* pDest)
{
	((CGbInsertStxmlFile*)pDest)->m_pRptEditDest = m_pRptEditDest;
	((CGbInsertStxmlFile*)pDest)->m_pRptEditSrc = m_pRptEditSrc;
	((CGbInsertStxmlFile*)pDest)->m_strStxmlFile = m_strStxmlFile;

	return CExBaseObject::CopyOwn(pDest);
}


long CGbInsertStxmlFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strStxmlFileKey, oNode, m_strStxmlFile);
	//xml_GetAttibuteValue(pXmlKeys->m_strDatasetPathKey, oNode, m_bInsertFileRoot);
	xml_GetAttibuteValue(pXmlKeys->m_strIec61850ConfigFileKey, oNode, m_strIec61850ConfigFile);

	return 0;
}

long CGbInsertStxmlFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strStxmlFileKey, oElement, m_strStxmlFile);
	//xml_SetAttributeValue(pXmlKeys->m_strInsertFileRootKey, oElement, m_bInsertFileRoot);
	xml_SetAttributeValue(pXmlKeys->m_strIec61850ConfigFileKey, oElement, m_strIec61850ConfigFile);

	return 0;
}

CExBaseObject* CGbInsertStxmlFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtDataInterfaceMapKey())
	{
		return new CGbtDataInterfaceMap();
	}

	return NULL;
}


void CGbInsertStxmlFile::InitByCopy(CGbInsertStxmlFile *pSrc)//, CDevice *pDevice, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit)
{
	POS pos = pSrc->GetHeadPosition();
	CGbtDataInterfaceMap *p = NULL;
	CGbtDataInterfaceMap *pFind = NULL;

	SetKey(pSrc->m_strKey);
	
	//ASSERT (m_strStxmlFile == pSrc->m_strStxmlFile);
	m_strIec61850ConfigFile = pSrc->m_strIec61850ConfigFile;
	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;

	while (pos != NULL)
	{
		p = (CGbtDataInterfaceMap *)pSrc->GetNext(pos);
		pFind = (CGbtDataInterfaceMap *)FindByID(p->m_strID);

		if (pFind != NULL)
		{
			pFind->InitByCopy(p);
		}
	}
}

void CGbInsertStxmlFile::InitGbFileInsert(const CString &strStxmlFile, CRptEditInterface *pDestRptEdit, CRptEditInterface *pSrcRptEdit)
{
	m_pRptEditDest = pDestRptEdit;
	m_pRptEditSrc = pSrcRptEdit;
	m_strStxmlFile = strStxmlFile;
}

void CGbInsertStxmlFile::InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CRptEditInterface *pDestRptEdit, CRptEditInterface *pSrcRptEdit)
{
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	m_pRptEditDest = pDestRptEdit;
	m_pRptEditSrc = pSrcRptEdit;
	m_strStxmlFile = strStxmlFile;

	m_pGbtDataInterfaces =pDevice->m_pGbtDataInterfaces;
	ASSERT (m_pGbtDataInterfaces != NULL);

	if (m_pGbtDataInterfaces == NULL)
	{
		return;
	}

	UpdateGbtDataInterfaceMaps();
// 	POS pos = m_pGbtDataInterfaces->GetHeadPosition();
// 	CGbtDataInterface *pGbtDataInterface = NULL;
// 	CGbtDataInterfaceMap *pNew = NULL;
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = m_pGbtDataInterfaces->GetNext(pos);
// 
// 		if (p->GetClassID() == GBCLASSID_GBTDATAINTERFACE)
// 		{
// 			pGbtDataInterface = (CGbtDataInterface *)p;
// 			pNew = new CGbtDataInterfaceMap();
// 			AddNewChild(pNew);
// 			pNew->InitGbtDataInterface(pGbtDataInterface);
// 		}
// 	}
}

void CGbInsertStxmlFile::UpdateGbtDataInterfaceMaps()
{
	DeleteAll();
	POS pos = m_pGbtDataInterfaces->GetHeadPosition();
	CGbtDataInterface *pGbtDataInterface = NULL;
	CGbtDataInterfaceMap *pNew = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_pGbtDataInterfaces->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_GBTDATAINTERFACE)
		{
			pGbtDataInterface = (CGbtDataInterface *)p;
			pNew = new CGbtDataInterfaceMap();
			AddNewChild(pNew);
			pNew->InitGbtDataInterface(pGbtDataInterface);
		}
	}
}

void CGbInsertStxmlFile::XMatch(CXMatchList &oXMatchList, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
		pMap->XMatch(oXMatchList, m_astrKey, bNotUpdateSingle, bNotUpdateNone);
	}
}


CExBaseObject* CGbInsertStxmlFile::ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchItemGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress)
{
	long nStart = m_pRptEditDest->GetCurrPos();

	if (m_nAddRptGroupTitle != 0)
	{
		if (pBatchItemGroup != NULL)
		{
			//插入3级标题
			m_pRptEditDest->InsertTitle(pBatchItemGroup->m_strName, 3);
		}
		else
		{
			//插入2级标题；没有批量组别
			m_pRptEditDest->InsertTitle(pParentItems->m_strName, 2);
		}
	}


	//插入根目录，根目录为BatchItemGroup的名称，下面的分类为File各Map项目分类
	CExBaseList *pStxmlFileItems = pParentItems;

	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
		CItems *pNewItems = InsertByDataterfaceMap(pMap, pStxmlFileItems, oListStxmlItem, pThreadProgress);

		if (pNewItems == NULL)
		{
			continue;
		}

		if (pThreadProgress != NULL)
		{
			pThreadProgress->StepIt();
			CString strMsg;
			strMsg.Format(/*_T("插入报告模板【%s】")*/g_sLangTxt_InsertReportTem, pNewItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
			pThreadProgress->ShowMsg(strMsg);
		}

		if(pBatchItemGroup == NULL && m_nAddRptGroupTitle != 0)
		{
			m_pRptEditDest->InsertTitle(pMap->m_strName, 3);
		}

		InsertStxmlWord(pNewItems, 0);

		if (pBatchItemGroup != NULL)
		{
			if (pBatchItemGroup->GetClassID() == GBTWZDCLASSID_BATCHITEMGROUP)
			{
				//根据当前的映射关系pMap，更新pBatchItemGroup组的各数据的表达式
				ReplaceBatchItemGroup(pBatchItemGroup, pMap);
				UpdateByBatchGroup(pBatchItemGroup, pNewItems);
				UpdateByBatchGroup_MacroTest(pBatchItemGroup, pNewItems);
			}
			else
			{
				UpdateByBatchGroup_GbtDatas(pBatchItemGroup, pNewItems);
			}
		}

		CGbInsertStxmlFileTool *pToolRef = (CGbInsertStxmlFileTool*)GetAncestor(GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL);

		if (pToolRef != NULL)
		{
			CDevice *pDevice = pToolRef->m_pGuideBookDest->GetDevice();
			InitCommCmdItemDatasetPath(pDevice, pNewItems);
		}
	}

	long nEnd = m_pRptEditDest->GetCurrPos();
	m_pRptEditDest->AddArea((CGbItemBase*)pParentItems, nStart, nEnd);

	return pStxmlFileItems;
}

CItems* GbtWzd_InsertRootItems(CExBaseList *pParentItems, const CString &strName, const CString &strID)
{
	CItems *pNewItems = new CItems();
	pNewItems->m_strName = strName;
	pNewItems->m_strID = strID;
	pParentItems->AddNewChild(pNewItems, TRUE);
	return pNewItems;
}

void wzd_InsertIecConfigMacroTest(const CString &strIecFile, CExBaseList *pParent)
{
	//插入配置文件项目
	if (strIecFile.GetLength() > 4)
	{
		CMacroTest *pMacroTest = new CMacroTest();
		pMacroTest->m_strName.Format(/*_T("通道配置：%s")*/g_sLangTxt_ChannelCfg, strIecFile);
		pMacroTest->m_strID = CMtDataTypeMngr::g_strTestMacroID_IECConfig;
		pParent->AddNewChild(pMacroTest);
		pMacroTest->InitAfterRead();
		CMacroTestPara *pMacroPara = pMacroTest->GetMacroTestPara();
		CMacroTestParaDatas *pPatas = pMacroPara->GetFaultParaDatas();
		pMacroPara->SetMacroID(CMtDataTypeMngr::g_strTestMacroID_IECConfig);
		CMacroTestParaData* pParaData = (CMacroTestParaData*)pPatas->AddPara(_T("_IecCfgFile"));
		pParaData->SetExpression(strIecFile);
	}
}


CExBaseObject* CGbInsertStxmlFile::ExecInsertByBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress)
{
	//插入根目录，子模板组的名称，其子目录为BatchItem的各组
	//StxmlFile为根目录，BatchItemGroups为子目录
	CItems *pStxmlFileItems = NULL;
	pStxmlFileItems = new CItems();
	pStxmlFileItems->m_strName = m_strName;
	pStxmlFileItems->m_strID = m_strID;
	pParentItems->AddNewChild(pStxmlFileItems);
	long nStart = m_pRptEditDest->GetCurrPos();

	//插入2级标题
	if (m_nAddRptGroupTitle != 0)
	{
		m_pRptEditDest->InsertTitle(m_strName, 2);
	}

	POS pos = pBatchItemGroups->GetHeadPosition();
	CGbtBatchItemGroup *pGroup = NULL;
	//BOOL bBack = m_bInsertFileRoot;
	m_bInsertFileRoot = FALSE;

	//插入配置文件项目
	wzd_InsertIecConfigMacroTest(m_strIec61850ConfigFile, pStxmlFileItems);

	while (pos != NULL)
	{
		pGroup = (CGbtBatchItemGroup *)pBatchItemGroups->GetNext(pos);

		long nGStart = m_pRptEditDest->GetCurrPos();

		//添加Group对应的Items
		CItems *pItemsGroup = GbtWzd_InsertRootItems(pStxmlFileItems, pGroup->m_strName, pGroup->m_strID);

		//插入子模板到Group对应的Items下
		ExecInsertByBatchItemGroup(pGroup, pItemsGroup, oListStxmlItem, pThreadProgress);

		long nGEnd = m_pRptEditDest->GetCurrPos();
		m_pRptEditDest->AddArea(pItemsGroup, nGStart, nGEnd);
	}

	long nEnd = m_pRptEditDest->GetCurrPos();
	m_pRptEditDest->AddArea(pStxmlFileItems, nStart, nEnd);

	return pStxmlFileItems;
}

CDataObj *CGbInsertStxmlFile::FindMapDataObj(const CString &strGbtDataID)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	return NULL;
}

BOOL CGbInsertStxmlFile::FilterByScript(CGbtDataScriptMapFilter &oFilter)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
		pMap->FilterByScript(oFilter);
	}

	return TRUE;
}

CItems* CGbInsertStxmlFile::ExcuteInsertFile(CExBaseList *pParentItems
											, CExBaseList &oListStxmlItem
											, CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->Step();
	}

	long nOld = g_nCloneReportMapInCopy;
	g_nCloneReportMapInCopy = 1;

	
	if (pThreadProgress != NULL)
	{
		CString strMsg;
		strMsg.Format(/*_T("插入测试模板【%s】")*/g_sLangTxt_InsertTestTem, pParentItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		pThreadProgress->ShowMsg(strMsg);
		pThreadProgress->StepIt();
	}
	
	pParentItems->AppendCloneEx(oListStxmlItem, TRUE);
	
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		CString strMsg;
		strMsg.Format(/*_T("插入报告模板【%s】")*/g_sLangTxt_InsertReportTem, pParentItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		pThreadProgress->ShowMsg(strMsg);
	}

	InsertStxmlWord((CItems*)pParentItems, 0);

	return (CItems*)pParentItems;
}

CItems* CGbInsertStxmlFile::InsertByDataterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap
												   , CExBaseList *pParentItems
												   , CExBaseList &oListStxmlItem
												   , CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->Step();
	}

	if (!pGbtDataInterfaceMap->CanInsert())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("映射【%s】【%s】没有建立任何映射关系，不能被实例化！")*/g_sLangTxt_CannotInstant, pGbtDataInterfaceMap->m_strName, pGbtDataInterfaceMap->m_strID);
		return NULL;
	}

	long nOld = g_nCloneReportMapInCopy;
	g_nCloneReportMapInCopy = 1;


	CItems *pNewItems = new CItems();
	pNewItems->m_strName = pGbtDataInterfaceMap->m_pGbtDataInterface->m_strName;
	pNewItems->m_strID = pGbtDataInterfaceMap->m_pGbtDataInterface->m_strID;
	pParentItems->AddNewChild(pNewItems);

	if (pThreadProgress != NULL)
	{
		CString strMsg;
		strMsg.Format(/*_T("插入测试模板【%s】")*/g_sLangTxt_InsertTestTem, pNewItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		pThreadProgress->ShowMsg(strMsg);
		pThreadProgress->StepIt();
	}

	pNewItems->AppendCloneEx(oListStxmlItem, TRUE);

	CGbItemVariableIDReplace oReplace;

	POS pos = pGbtDataInterfaceMap->GetHeadPosition();
	CGbtDataScriptMap *pScptMap = NULL;
	CString strSrcID, strDestID;

	while (pos != NULL)
	{
		pScptMap = (CGbtDataScriptMap *)pGbtDataInterfaceMap->GetNext(pos);
		strSrcID = pScptMap->m_pGbtDataScript->m_strID;
		strDestID = pScptMap->GetRefObjIDPath();

		if (IsStringNumber(strDestID))
		{
			CString strDsFunc;
			strDsFunc.Format(_T("GetDsDataValue(\"%s\")"), strSrcID);
			oReplace.Replace(pNewItems, strDsFunc, strDestID);
		}

		oReplace.SetDestObject(pScptMap->GetRefObject());
		oReplace.Replace(pNewItems, strSrcID, strDestID);
		oReplace.ReplaceScriptLibLocal(pNewItems, strSrcID, strDestID);
	}

	g_nCloneReportMapInCopy = nOld;

	return pNewItems;
}

BOOL CGbInsertStxmlFile::MakeCommCmdValusValidate(CCommCmd *pCommCmd)
{
	CCmd *pCmd = pCommCmd->GetCmd();
	CExBaseList oListDataset;

	//处理没有关联的数据对象
	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);

		if (IsStringNumber(pValue->m_strID))
		{
			pCmd->Delete(pValue);
		}
	}

	return (pCmd->GetCount() > 0);
}

void CGbInsertStxmlFile::InitCommCmdItemDatasetPath(CDevice *pDevice, CCommCmd *pCommCmd)
{
	//去掉没有映射的通讯命令数据
	MakeCommCmdValusValidate(pCommCmd);

	pCommCmd->m_bWzdHasInitDataset = FALSE;
	CGbCommCmdSplit oSplit;
	oSplit.InitCommCmdItemDatasetPath(pDevice, pCommCmd);

	//如果没有数据集，请通讯命令为读的类型
	CCmd *pCmd = pCommCmd->GetCmd();

	if ((pCmd->m_strDatasetPath.GetLength() == 0) && pCommCmd->IsCmdNeedDataset())
	{
		CDataSet *pDataset = (CDataSet*)m_listDataset.GetHead();

		if (pDataset != NULL)
		{
			pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		}
	}

	if ((pCmd->m_strDatasetPath.GetLength() == 0)  && pCommCmd->IsCmdNeedDataset())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("通讯命令【%s】没有对应的数据集")*/g_sLangTxt_CommCmdNoDataset, pCommCmd->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
	}

	pCommCmd->m_bWzdHasInitDataset = TRUE;

}

void CGbInsertStxmlFile::InitCommCmdItemDatasetPath(CDevice *pDevice, CExBaseList *pItems)
{
	if (pDevice == NULL)
	{
		return;
	}

	UINT nClassID = 0;
	nClassID = pItems->GetClassID();

	if (nClassID == GBCLASSID_ITEMS || nClassID == GBCLASSID_MACROTEST)
	{
		POS pos = pItems->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = (CExBaseObject *)pItems->GetNext(pos);
			nClassID = p->GetClassID();

			if (nClassID == GBCLASSID_ITEMS)
			{
				InitCommCmdItemDatasetPath(pDevice, (CExBaseList*)p);
			}
			else if (nClassID == GBCLASSID_MACROTEST)
			{
				InitCommCmdItemDatasetPath(pDevice, (CExBaseList*)p);
			}
			else if (nClassID == GBCLASSID_COMMCMD)
			{
				InitCommCmdItemDatasetPath(pDevice, (CCommCmd*)p);

				//如果通讯命令没有通讯参数数据，则删除此命令, 2013-8-15
				CCommCmd *pCommCmd = (CCommCmd*)p;
				CCmd *pCmd = pCommCmd->GetCmd();

				if ( (pCmd->GetCount() == 0) && pCommCmd->IsWrite())// (strCommCmdID.Find(_T("write")) >= 0) )
				{
					CGbCommCmdMms *pCmdMms = pCommCmd->GetGbCommCmd();

					if ( (pCmdMms->m_strGbDataID != g_strDataSetIDKey[DSID_dsNone])
						&& (pCmdMms->m_strGbDataID == g_strDataSetIDKey[DSID_dsReport])
						&& (pCmdMms->m_strGbDataID == g_strDataSetIDKey[DSID_dsFile])
						&& (pCmdMms->m_strGbDataID != g_strDataSetIDKey[DSID_dsAll]) )
					{
						pItems->Delete(pCommCmd);
					}
				}
			}
		}
	}
	else if (nClassID == GBCLASSID_COMMCMD)
	{
		InitCommCmdItemDatasetPath(pDevice, (CCommCmd*)pItems);
	}
}

void CGbInsertStxmlFile::InsertStxmlWord(CItems *pCurrItems, long nTitleLevel)
{
	if (m_pRptEditDest == NULL)
	{
		return;
	}

	m_pRptEditSrc->m_dwMaxBkmkIndex = m_pRptEditDest->m_dwMaxBkmkIndex + 1;
	m_pRptEditSrc->OpenWord(m_strStxmlFile);

	g_pdwMaxBkmkIndex = &m_pRptEditSrc->m_dwMaxBkmkIndex;

	//更名标签
	RenameRptBkmks(pCurrItems);

	//插入到Word文档末尾
	m_pRptEditDest->InsertWordEdit(m_pRptEditSrc, m_nAddRptGroupTitle);
	m_pRptEditSrc->CloseWord();
	m_pRptEditDest->m_dwMaxBkmkIndex  = m_pRptEditSrc->m_dwMaxBkmkIndex + 1;
}

void CGbInsertStxmlFile::RenameRptBkmks(CExBaseList *pList)
{
//	wordrpt_RenameRptBkmks(pList, m_pWordRptEditSrc->m_WordApp, m_pWordRptEditSrc->m_doc);
	m_pRptEditSrc->rpt_RenameRptBkmks(pList);
}


void CGbInsertStxmlFile::UpdateByBatchGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems)
{
	if (pBatchGroup == NULL)
	{
		return;
	}

	ASSERT (pRootItems != NULL);

	if (pRootItems == NULL)
	{
		return;
	}

	POS pos = pBatchGroup->GetHeadPosition();
	CGbtBatchItemRef *pRef = NULL;

	while (pos != NULL)
	{
		pRef = (CGbtBatchItemRef *)pBatchGroup->GetNext(pos);
		UpdateByBatchItemRef(pRef, pRootItems);
	}
}


void CGbInsertStxmlFile::UpdateByBatchGroup_GbtDatas(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems)
{
	if (pBatchGroup == NULL)
	{
		return;
	}

	ASSERT (pRootItems != NULL);

	if (pRootItems == NULL)
	{
		return;
	}

	CGbtBatchGbtDataGroup *pGbtDataGroup = (CGbtBatchGbtDataGroup*)pBatchGroup;
	POS pos = pGbtDataGroup->GetHeadPosition();
	CGbtBatchGbtDataRef *pGbtDataRef = NULL;
	CGbItemVariableIDReplace oReplace;
	CString strSrcID, strDestID;
	CString strDsFunc;

	while (pos != NULL)
	{
		pGbtDataRef = (CGbtBatchGbtDataRef *)pGbtDataGroup->GetNext(pos);
		
		strDsFunc.Format(_T("GetDsDataValue(\"%s\")"), pGbtDataRef->m_strID);
		oReplace.Replace(pRootItems, strDsFunc, pGbtDataRef->m_strGbtDataValue);

// 		strDsFunc.Format(_T("GetDsDataValueEx(-1,\"%s\")"), pGbtDataRef->m_strID);
// 		oReplace.Replace(pRootItems, strDsFunc, pGbtDataRef->m_strGbtDataValue);

		oReplace.Replace(pRootItems, pGbtDataRef->m_strID, pGbtDataRef->m_strGbtDataValue);
	}
}

void CGbInsertStxmlFile::UpdateByBatchGroup_MacroTest(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems)
{
	if (pBatchGroup == NULL)
	{
		return;
	}

	ASSERT (pRootItems != NULL);

	if (pRootItems == NULL)
	{
		return;
	}

	POS pos = pBatchGroup->GetHeadPosition();
	CGbtBatchItemRef *pRef = NULL;

	while (pos != NULL)
	{
		pRef = (CGbtBatchItemRef *)pBatchGroup->GetNext(pos);
		UpdateByBatchItemRef_MacroTest(pRef, pRootItems);
	}
}

BOOL CGbInsertStxmlFile::ValidateMapKeys(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);

		if (!pMap->ValidateMapKeys(strErrorMsg))
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void CGbInsertStxmlFile::SetKey(const CString &strKey)
{
	m_strKey = strKey;
	m_strKey.Trim();

	if (m_strKey.GetLength() == 0)
	{
		m_astrKey.RemoveAll();
		return;
	}

	long nPos = 0;
	long nPrevPos = 0;
	CString strTemp;
	long nLen = m_strKey.GetLength();

	while (TRUE)
	{
		nPos = m_strKey.Find(';', nPrevPos);

		if (nPos < 0)
		{
			break;
		}

		if (nPos > nPrevPos)
		{
			strTemp = m_strKey.Mid(nPrevPos, nPos - nPrevPos);
			strTemp.Trim();

			if (strTemp.GetLength() > 0)
			{
				m_astrKey.Add(strTemp);
			}
		}

		nPrevPos = nPos + 1;

		if (nPrevPos >= nLen)
		{
			break;
		}
	}

	if (nPrevPos < nLen)
	{
		strTemp = m_strKey.Mid(nPrevPos);
		strTemp.Trim();

		if (strTemp.GetLength() > 0)
		{
			m_astrKey.Add(strTemp);
		}
	}
}

void CGbInsertStxmlFile::UpdateByBatchItemRef(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems)
{
	CExBaseObject *pItem = NULL;
	
	//根据BatchItemRef的路径查找到相应的项目
	pItem = SelectByRefItem(pBatchItemRef, pRootItems);
	ASSERT( pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	UINT nClassID = pItem->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		UpdateItem_CommCmd(pItem, pBatchItemRef);
		break;
// 	case GBCLASSID_MACROTEST:
// 		UpdateItem_MacroTest(pItem, pBatchItemRef);
// 		break;

	default:
		break;
	}
}

void CGbInsertStxmlFile::UpdateByBatchItemRef_MacroTest(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems)
{
	CExBaseObject *pItem = NULL;
	POS pos = NULL;
	UINT nClassID = pRootItems->GetClassID();

	if (nClassID == GBCLASSID_MACROTEST)
	{
		UpdateItem_MacroTest(pRootItems, pBatchItemRef);
	}
	else if (nClassID == GBCLASSID_ITEMS)
	{
		pos = pRootItems->GetHeadPosition();

		while (pos != NULL)
		{
			pItem = (CExBaseObject *)pRootItems->GetNext(pos);
			UpdateByBatchItemRef_MacroTest(pBatchItemRef, (CExBaseList*)pItem);
		}
	}
}

CExBaseObject* CGbInsertStxmlFile::SelectByRefItem(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems)
{
	CExBaseList *pRootList = pRootItems;


	CExBaseObject *pItem = NULL;
	CExBaseList oListItems;
	long nCount = 0;

	pRootList->SelectDatas(pBatchItemRef->m_strID, oListItems, _T("$"));
	nCount = oListItems.GetCount();

	if (nCount == 1)
	{
		pItem = (CExBaseObject *)oListItems.GetHead();
	}

	oListItems.RemoveAll();

	return pItem;
}

void CGbInsertStxmlFile::UpdateItem_CommCmd(CExBaseObject *pItem, CGbtBatchItemRef *pBatchItemRef)
{
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();

	pCmd->m_strDatasetPath = pBatchItemRef->m_strDatasetPath;
// 	pCmd->DeleteAll();
// 	pCmd->AppendCloneEx(*pBatchItemRef, TRUE);
	POS posDest = pCmd->GetHeadPosition();
	POS posSrc = pBatchItemRef->GetHeadPosition();
	CValue *pDest = NULL;
	CGbtBatchItemRefValue *pSrc = NULL;

	while (posSrc != NULL && posDest != NULL)
	{
		pDest = (CValue*)pCmd->GetNext(posDest);
		pSrc  = (CGbtBatchItemRefValue*)pBatchItemRef->GetNext(posSrc);
		pDest->m_strValue = pSrc->m_strRelValue;  //pSrc->m_strValue;
	}
}

void CGbInsertStxmlFile::ReplaceBatchItemGroup(CGbtBatchItemGroup *pBatchItemGroup, CGbtDataInterfaceMap *pGbtDataInterfaceMap)
{
	if (pBatchItemGroup == NULL)
	{
		return;
	}

	pBatchItemGroup->InitReplace();

	CGbItemVariableIDReplace oReplace;

	POS pos = pGbtDataInterfaceMap->GetHeadPosition();
	CGbtDataScriptMap *pScptMap = NULL;
	CString strSrcID, strDestID;

	while (pos != NULL)
	{
		pScptMap = (CGbtDataScriptMap *)pGbtDataInterfaceMap->GetNext(pos);
		strSrcID = pScptMap->m_pGbtDataScript->m_strID;
		strDestID = pScptMap->GetRefObjIDPath();
		oReplace.ReplaceGbtBatchItemGroup(pBatchItemGroup, strSrcID, strDestID);
	}
}

void CGbInsertStxmlFile::UpdateItem_MacroTest(CExBaseObject *pItem, CGbtBatchItemRef *pBatchItemRef)
{
	CMacroTest *pMacroTest = (CMacroTest*)pItem;
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CMacroTestParaDatas *pParaDatas = pMacroTestPara->GetFaultParaDatas();
	CMacroTestParaData *pData = NULL;
	POS posData = NULL;

	POS pos = pBatchItemRef->GetHeadPosition();
	CGbtBatchItemRefValue *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc  = (CGbtBatchItemRefValue*)pBatchItemRef->GetNext(pos);
		posData = pParaDatas->GetHeadPosition();

		while (posData != NULL)
		{
			pData = (CMacroTestParaData *)pParaDatas->GetNext(posData);

			//??????????没有考虑表达式部分
			if (pData->m_strExpressionBack == pSrc->m_strID)
			{
				if (IsStringNumber(pData->m_strExpression))
				{
					pData->m_strExpression = pSrc->m_strRelValue;//pSrc->m_strValue;
				}
			}
		}
	}
}

void CGbInsertStxmlFile::InitDatasetList(CDevice *pDevice, CGbtDataInterfaceMap *pMap)
{
	POS pos = pMap->GetHeadPosition();
	CGbtDataScriptMap *pScriptMap = NULL;
	CExBaseObject *pDataObjRef = NULL;
	CDataSet *pDataset = NULL;

	while (pos != NULL)
	{
		pScriptMap = (CGbtDataScriptMap *)pMap->GetNext(pos);
		pDataObjRef = pScriptMap->GetRefObject();

		if (pDataObjRef != NULL)
		{
			pDataset = (CDataSet *)pDataObjRef->GetParent();

			if (m_listDataset.Find(pDataset) == NULL)
			{
				m_listDataset.AddTail(pDataset);
			}
		}
	}
}

void CGbInsertStxmlFile::InitDatasetList(CDevice *pDevice)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
		InitDatasetList(pDevice, pMap);
	}
}

//////////////////////////////////////////////////////////////////////////

CGbInsertStxmlFileMngr::CGbInsertStxmlFileMngr()
{
	m_pHeadStxmlFile = NULL;
	m_nAddRptGroupTitle = 1;
}

CGbInsertStxmlFileMngr::~CGbInsertStxmlFileMngr()
{
	m_pHeadStxmlFile = NULL;
}


long CGbInsertStxmlFileMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbInsertStxmlFileMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CGbInsertStxmlFileMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbInsertStxmlFileKey())
	{
		return new CGbInsertStxmlFile();
	}

	return NULL;
}

CGbInsertStxmlFile* CGbInsertStxmlFileMngr::NewGbInsertStxmlFile()
{
	CGbInsertStxmlFile *pNew = (CGbInsertStxmlFile*)m_pHeadStxmlFile->Clone();
	long nIndex = GetCount() + 1;
	pNew->m_strName.Format(/*_T("第%d组")*/g_sLangTxt_NumberGroup, nIndex);
	pNew->m_strID.Format(_T("StxmlFile%d"), nIndex);
	AddNewChild(pNew, TRUE);
	return pNew;
}

void CGbInsertStxmlFileMngr::InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CRptEditInterface *pDestRptEdit, CRptEditInterface *pSrcRptEdit)
{
	if (m_pHeadStxmlFile != NULL)
	{
		return;
	}

	m_pHeadStxmlFile = new CGbInsertStxmlFile();
//	m_pHeadStxmlFile->InitGbtDataInterfaceMaps(pDevice, strStxmlFile, pDestWordEdit, pSrcWordEdit);
	m_pHeadStxmlFile->InitGbtDataInterfaceMaps(pDevice, strStxmlFile, pDestRptEdit, pSrcRptEdit);
	AddNewChild(m_pHeadStxmlFile);
}


void CGbInsertStxmlFileMngr::XMatch(CXMatchList &oXMatchList, long nIndex, BOOL bNotUpdateSingle,BOOL bNotUpdateNone)
{
	if (nIndex < 0)
	{
		POS pos = GetHeadPosition();
		CGbInsertStxmlFile *pStxmlFile = NULL;

		while (pos != NULL)
		{
			pStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);
			pStxmlFile->m_nAddRptGroupTitle = m_nAddRptGroupTitle;
			pStxmlFile->XMatch(oXMatchList, bNotUpdateSingle, bNotUpdateNone);
		}
	}
	else
	{
		CGbInsertStxmlFile *pStxmlFile = (CGbInsertStxmlFile*)GetAtIndex(nIndex);

		if (pStxmlFile != NULL)
		{
			pStxmlFile->m_nAddRptGroupTitle = m_nAddRptGroupTitle;
			pStxmlFile->XMatch(oXMatchList, bNotUpdateSingle, bNotUpdateNone);
		}
	}
}

long CGbInsertStxmlFileMngr::GetProgressStepCount()
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CGbInsertStxmlFile *)GetNext(pos);
		nCount += p->GetCount();
	}

	return nCount;
}

void CGbInsertStxmlFileMngr::InitByCopy(CGbInsertStxmlFileMngr *pSrc)
{
	if (pSrc->GetCount() == 0)
	{
		return;
	}

	//清空链表
	POS pos = GetHeadPosition();
	RemoveAt(pos);
	DeleteAll();
	AddNewChild(m_pHeadStxmlFile);

	pos = pSrc->GetHeadPosition();
	CGbInsertStxmlFile *pFile = NULL;
	CGbInsertStxmlFile *pNew = NULL;
	pFile = (CGbInsertStxmlFile*)pSrc->GetNext(pos);

	m_pHeadStxmlFile->InitByCopy(pFile);

	while (pos != NULL)
	{
		pFile = (CGbInsertStxmlFile*)pSrc->GetNext(pos);
		pNew = NewGbInsertStxmlFile();
		pNew->InitByCopy(pFile);
	}
}

CDataObj *CGbInsertStxmlFileMngr::FindMapDataObj(const CString &strGbtDataID)
{
	return NULL;
}

void CGbInsertStxmlFileMngr::InitDatasetList(CDevice *pDevice)
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *pStxmlFile = NULL;

	while (pos != NULL)
	{
		pStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);
		pStxmlFile->m_nAddRptGroupTitle = m_nAddRptGroupTitle;
		pStxmlFile->InitDatasetList(pDevice);
	}
}

void CGbInsertStxmlFileMngr::DeleteStxmlFile(long nIndex)
{
	long nCount = GetCount();

	if (nCount == 1)
	{
		return ;
	}

	if (nIndex == 0)
	{
		m_pHeadStxmlFile = (CGbInsertStxmlFile*)GetAtIndex(1);
	}

	DeleteAt(nIndex);
}


CExBaseObject* CGbInsertStxmlFileMngr::ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress)
{
	if (GetCount() == 0)
	{
		return NULL;
	}

	Validate();

	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *pStxmlFile = NULL;
	BOOL bInsertFileRoot = TRUE;

	while (pos != NULL)
	{
		pStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);
		pStxmlFile->m_nAddRptGroupTitle = m_nAddRptGroupTitle;
		pStxmlFile->m_nAddRptGroupTitle = m_nAddRptGroupTitle;

		//插入子模板的根目录项目
		CItems *pNewItemsFile = GbtWzd_InsertRootItems(pParentItems, pStxmlFile->m_strName, pStxmlFile->m_strID);

		//插入配置文件
		pStxmlFile->InsertIecConfigMacroTest(pNewItemsFile);

		pStxmlFile->ExecInsertByBatchItemGroup(pBatchGroup, pNewItemsFile, oListStxmlItem, pThreadProgress);
	}

	return NULL;
}

void CGbInsertStxmlFileMngr::Validate()
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *p = NULL;
	BOOL bInsertRoot = TRUE;

	if (GetCount() == 1)
	{
		bInsertRoot = FALSE;
	}

	while (pos != NULL)
	{
		p = (CGbInsertStxmlFile *)GetNext(pos);
		p->m_bInsertFileRoot = bInsertRoot;
	}
}

BOOL CGbInsertStxmlFileMngr::ValidateMapKeys(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *pGbInsertStxmlFile = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pGbInsertStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);

		if (!pGbInsertStxmlFile->ValidateMapKeys(strErrorMsg))
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

//////////////////////////////////////////////////////////////////////////

CExBaseObject* CGbWzdDatasetRefMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdDatasetRefKey())
	{
		return new CGbWzdDatasetRef();
	}

	return NULL;
}
