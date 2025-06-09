#include "stdafx.h"
#include "MacroScriptApi.h"
#include "..\..\AutoTest\Module\GuideBook\GbDataTypeMngr.h"

CShortData* TMS_FindData(CTestMacro *pMacro, const CString &strID)
{
	ASSERT (pMacro != NULL);

	if (pMacro == NULL)
	{
		return NULL;
	}

	CShortData *pData = (CShortData*)pMacro->GetFaultParas()->FindByID(strID);

	if (pData == NULL)
	{
		pData = (CShortData*)pMacro->GetSysParas()->FindByID(strID);
	}

	return pData;
}

BOOL TMS_CanAddScptData(CTestMacroScript *pScript, CExBaseObject *pData)
{
	if (pScript == NULL || pData == NULL)
	{
		return FALSE;
	}

	CTmScptData *pFind = (CTmScptData*)pScript->FindByID(pData->m_strID);

	if (pFind != NULL)
	{
		return FALSE;
	}

	CDataTypes *pDataTypes = CGbDataTypeMngr::GetMacroTestDataTypes();
	long nIndex = pDataTypes->FindIndexByID(((CShortData*)pData)->m_strDataTypeID);

	return (nIndex >= 4);
}

CTmScptData* TMS_AddScptData(CTestMacroScript *pScript, CExBaseObject *pData)
{
	CTmScptData *pFind = (CTmScptData*)pScript->FindByID(pData->m_strID);
	
	if (pFind != NULL)
	{
		return NULL;
	}

	CDataTypes *pDataTypes = CGbDataTypeMngr::GetMacroTestDataTypes();
	CDataType *pDataType = (CDataType*)pDataTypes->FindByID(((CShortData*)pData)->m_strDataTypeID);

	if (pDataType == NULL)
	{
		return NULL;
	}

	pFind = new CTmScptData();
	pFind->m_strID = pData->m_strID;
	pScript->AddNewChild(pFind);
	CDataTypeValue *pValue = NULL;
	POS pos = pDataType->GetHeadPosition();
	CTmScptValue *pScptValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataTypeValue *)pDataType->GetNext(pos);
		pScptValue = new CTmScptValue();
		pScptValue->m_strValue = pValue->m_strIndex;
		pFind->AddNewChild(pScptValue);
	}

	return pFind;
}

CTmScptCmd* TMS_AddScptCmd(CTmScptData *pScptData, CExBaseObject *pData, const CString &strAttrID)
{
	POS pos = pScptData->GetHeadPosition();
	CTmScptValue *pScptValue = NULL;

	while (pos != NULL)
	{
		pScptValue = (CTmScptValue*)pScptData->GetNext(pos);
		TMS_AddScptCmd(pScptValue, pData, strAttrID);
	}

	return NULL;
}

CTmScptCmd* TMS_AddScptCmd(CTmScptValue *pScptValue, CExBaseObject *pData, const CString &strAttrID)
{
	if (pData->GetClassID() == DTMCLASSID_CSHORTDATA)
	{
		CTmScptCmd *pCmd = new CTmScptCmd();
		pCmd->m_strDataID = pData->m_strID;
		pCmd->m_strAttrID = strAttrID;
		pCmd->m_strValue = _T("0");
		pScptValue->AddNewChild(pCmd);
		return pCmd;
	}
	else
	{
		CTmScptCmd *pCmd = new CTmScptGroupCmd();
		pCmd->m_strDataID = pData->m_strID;
		pCmd->m_strAttrID = strAttrID;
		pCmd->m_strValue = _T("0");
		pScptValue->AddNewChild(pCmd);
		return pCmd;
	}
}

BOOL TMS_DeleteScptCmd(CTmScptValue *pScptValue, CTmScptCmd *pScptCmd)
{
	if (pScptCmd == NULL || pScptValue == NULL)
	{
		return FALSE;
	}

	return TMS_DeleteScptCmd(pScptValue, pScptCmd->m_strDataID, pScptCmd->m_strAttrID);
}

BOOL TMS_DeleteScptCmd(CTmScptData *pScptData, CTmScptCmd *pScptCmd)
{
	if (pScptCmd == NULL || pScptData == NULL)
	{
		return FALSE;
	}

	return TMS_DeleteScptCmd(pScptData, pScptCmd->m_strDataID, pScptCmd->m_strAttrID);
}

BOOL TMS_DeleteScptCmd(CTmScptValue *pScptValue, const CString &strDataID, const CString &strAttrID)
{
	POS pos = pScptValue->GetHeadPosition();
	POS posPrev = NULL;
	CTmScptCmd *pScptCmd = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		posPrev = pos;
		pScptCmd = (CTmScptCmd *)pScptValue->GetNext(pos);

		if (pScptCmd->m_strAttrID == strAttrID && pScptCmd->m_strDataID == strDataID)
		{
			pScptValue->RemoveAt(posPrev);
			delete pScptCmd;
			nCount++;
		}
	}

	return (nCount > 0);
}

BOOL TMS_DeleteScptCmd(CTmScptData *pScptData, const CString &strDataID, const CString &strAttrID)
{
	POS pos = pScptData->GetHeadPosition();
	CTmScptValue *pScptValue = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pScptValue = (CTmScptValue *)pScptData->GetNext(pos);
		bTrue |= TMS_DeleteScptCmd(pScptValue, strDataID, strAttrID);
	}

	return bTrue;
}

BOOL TMS_Import(CTestMacroScript *pScript, CExBaseList *pList)
{
	if (pScript == NULL || pList == NULL)
	{
		return FALSE;
	}

	if (pList->GetCount() == 0)
	{
		return FALSE;
	}

	POS pos = pList->GetHeadPosition();
	CTmScptData *pScptData = NULL;
	CTmScptData *pNew = NULL;
	CTmScptData *pFind = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pScptData = (CTmScptData *)pList->GetNext(pos);
		pFind =  (CTmScptData *)pScript->FindByID(pScptData->m_strID);

		if (pFind == pScptData)
		{
			continue;
		}

		if (pFind != NULL)
		{
			pFind->AppendClone(pScptData);
			nCount++;
		}
		else
		{
			pNew =  (CTmScptData *)pScptData->Clone();
			pScript->AddNewChild(pNew);
			nCount++;
		}
	}

	return (nCount>0);
}


void TMS_InsertChildrenToListBox(CTestMacroScript *pScript, CListBox *pListBox, CTestMacro *pMacro)
{
	POS pos = pScript->GetHeadPosition();
	CTmScptData *pScptData = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pScptData = (CTmScptData *)pScript->GetNext(pos);
		TMS_InsertToListBox(pScptData, pListBox, pMacro);
	}
}

long TMS_InsertToListBox(CTmScptData *pScptData, CListBox *pListBox, CTestMacro *pMacro)
{
	CShortData *pData = TMS_FindData(pMacro, pScptData->m_strID);

	long nIndex = 0;

	if (pData != NULL)
	{
		nIndex = pListBox->AddString(pData->m_strName);
	}
	else
	{
		nIndex = pListBox->AddString(pScptData->m_strID);
	}

	pListBox->SetItemData(nIndex, (DWORD)pScptData);
	return nIndex;
}