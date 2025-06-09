//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TempFolders.cpp  CAts_Wzd_TempFolders


#include "stdafx.h"
#include "Ats_Wzd_TempFolders.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_TempFolders::CAts_Wzd_TempFolders()
{
	//初始化属性
	m_nSelect = 1;

	//初始化成员变量
}

CAts_Wzd_TempFolders::~CAts_Wzd_TempFolders()
{
}

long CAts_Wzd_TempFolders::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_TempFolders::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_TempFolders::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CAts_Wzd_TempFolders::InitAfterRead()
{
}

BOOL CAts_Wzd_TempFolders::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_TempFolders *p = (CAts_Wzd_TempFolders*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_TempFolders::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_TempFolders *p = (CAts_Wzd_TempFolders*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_TempFolders::Clone()
{
	CAts_Wzd_TempFolders *p = new CAts_Wzd_TempFolders();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_TempFolders::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_TempFolders *p = new CAts_Wzd_TempFolders();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_TempFolders::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_TempFolders::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_TempFolderKey)
	{
		pNew = new CAts_Wzd_TempFolder();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_TempFolders::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		pNew = new CAts_Wzd_TempFolder();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_TempFolders::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_TempFolder();

	return pNew;
}

CAts_Wzd_TempFolder* CAts_Wzd_TempFolders::FindFolderByIndex(long nIndex)
{
	CAts_Wzd_TempFolder *pFind = NULL;
	CAts_Wzd_TempFolder *pFolder = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pFolder = (CAts_Wzd_TempFolder *)GetNext(pos);

		if (pFolder->m_nIndex_Folder == nIndex)
		{
			pFind = pFolder;
			break;
		}

		pFind = pFolder->FindChildFolderByIndex(nIndex);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

void CAts_Wzd_TempFolders::UpdateFolderByIndex(long nIndex, const CString &strName)
{
	CAts_Wzd_TempFolder *pFind = FindFolderByIndex(nIndex);

	if (pFind != NULL)
	{
		pFind->m_strName = strName;
	}
}

void CAts_Wzd_TempFolders::RemoveAllTemplateUnits()
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
		{
			Remove(pObj);
			continue;
		}

		if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
		{
			CAts_Wzd_TempFolder *pFolder = (CAts_Wzd_TempFolder *)pObj;
			pFolder->RemoveAllTemplateUnits();
		}
	}
}

void AtsWzd_SetTemplateUnitSelectedState(CExBaseList *pList, long nSelect)
{
	AtsWzd_SetSelect(pList, nSelect);
	CExBaseList *pParent = (CExBaseList *)pList->GetParent();
	AtsWzd_UpdateTemplateUnitSelectedState(pParent);

	UINT nClassID = pList->GetClassID();

	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		return;
	}

	POS pos = pList->GetHeadPosition();
	CExBaseObject *pChildItem = NULL;

	while(pos != NULL)
	{
		pChildItem = pList->GetNext(pos);
		AtsWzd_SetTemplateUnitSelectedState((CExBaseList *)pChildItem, nSelect);
	}
}

void AtsWzd_UpdateTemplateUnitSelectedState(CExBaseList *pList)
{
	if (pList->GetClassID() == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDERS)
	{
		return;
	}

	ASSERT(pList != NULL);
	long nVal[3] = {0,0,0};

	POS pos = pList->GetHeadPosition();
	CExBaseObject* pChildItem = NULL;
	long nSelect = 0;

	while(pos != NULL)
	{
		pChildItem = pList->GetNext(pos);
		nSelect = AtsWzd_GetSelect(pChildItem);

		if( 0 <= nSelect && nSelect <= 2)
			nVal[nSelect] = 1;
		else
			nVal[2] = 1;
	}

	nSelect = 0;

	if (nVal[0] == 1 && nVal[1]==0 && nVal[2] == 0)
		nSelect = 0;
	else if (nVal[0] == 0 && nVal[1]==1 && nVal[2] == 0)
		nSelect = 1;
	else if (nVal[0] == 0 && nVal[1]==0 && nVal[2] == 0)
		nSelect = 0;
	else
		nSelect = 2;

	long n1 = AtsWzd_GetSelect(pList);

	if (nSelect == 0 || nSelect == 1)
	{
		if (nSelect != AtsWzd_GetSelect(pList))
		{
			AtsWzd_SetSelect(pList, nSelect);
			CExBaseList* pParent = (CExBaseList*)pList->GetParent();

			if (pParent != NULL)
			{
				AtsWzd_UpdateTemplateUnitSelectedState(pParent);
			}
		}
	}
	else
	{
		AtsWzd_SetSelect(pList, nSelect);
		CExBaseList* pParent = (CExBaseList*)pList->GetParent();

		if (pParent  != NULL)
		{
			AtsWzd_UpdateTemplateUnitSelectedState(pParent);
		}
	}
}

void AtsWzd_SetSelect(CExBaseObject *pObj, long nSelect)
{
	UINT nClassID = pObj->GetClassID();

	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDERS)
	{
		((CAts_Wzd_TempFolders*)pObj)->SetSelect(nSelect);
	}
	else if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		((CAts_Wzd_TempFolder *)pObj)->SetSelect(nSelect);
	}
	else if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		((CAts_Wzd_TemplateUnit *)pObj)->SetSelect(nSelect);
	}
}

long AtsWzd_GetSelect(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	long nSelect = 1;

	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDERS)
	{
		nSelect = ((CAts_Wzd_TempFolders*)pObj)->GetSelect();
	}
	else if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		nSelect = ((CAts_Wzd_TempFolder *)pObj)->GetSelect();
	}
	else if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		nSelect = ((CAts_Wzd_TemplateUnit *)pObj)->GetSelect();
	}

	return nSelect;
}