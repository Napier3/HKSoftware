// XrioCustomBlock.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioCustomBlock.h"
#include "XrioObjectCfg.h"
#include "XrioListCfg.h"
#include "XrioCustomParameter.h"

// CXrioCustomBlock

CXrioCustomBlock::CXrioCustomBlock()
{
	//初始化属性
	//m_strBlockID = _T("");
	m_strEnabled = _T("");
	m_strEnabledFormula = _T("");
	m_strDescription = _T("");
}

CXrioCustomBlock::~CXrioCustomBlock()
{
}

long CXrioCustomBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
	xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetElementText(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetElementText(pXmlKeys->m_strEnabledFormulaKey, oNode, m_strEnabledFormula);

	return 0;
}

long CXrioCustomBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
	xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);
	xml_SetElementText(pXmlKeys->m_strDescriptionKey, oXMLDoc, oElement, m_strDescription);
	xml_SetElementText(pXmlKeys->m_strEnabledFormulaKey, oXMLDoc, oElement, m_strEnabledFormula);

	return 0;
}

long CXrioCustomBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strEnabled);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strEnabledFormula);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strEnabled);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strEnabledFormula);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strEnabled);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strEnabledFormula);
	}
	return 0;
}

void CXrioCustomBlock::InitAfterRead()
{
}

BOOL CXrioCustomBlock::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioCustomBlock *p = (CXrioCustomBlock*)pObj;

// 	if(m_strBlockID != p->m_strBlockID)
// 	{
// 		return FALSE;
// 	}

	if(m_strEnabled != p->m_strEnabled)
	{
		return FALSE;
	}

	if (m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if (m_strEnabledFormula != p->m_strEnabledFormula)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioCustomBlock::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioCustomBlock *p = (CXrioCustomBlock*)pDest;

	//p->m_strBlockID = m_strBlockID;
	p->m_strEnabled = m_strEnabled;
	p->m_strEnabledFormula = m_strEnabledFormula;
	p->m_strDescription = m_strDescription;
	
	return TRUE;
}

CBaseObject* CXrioCustomBlock::Clone()
{
	CXrioCustomBlock *p = new CXrioCustomBlock();
	Copy(p);
	return p;
}

BOOL CXrioCustomBlock::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_ENABLEDREFLIST ||
	    nClassID == XRIOCLASSID_CUSTOMBLOCK ||
	    nClassID == XRIOCLASSID_CUSTOMPARAMETER
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CXrioCustomBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCustomParameterKey)
	{
		pNew = new CXrioCustomParameter();
	}
	else if (strClassID == pXmlKeys->m_strCustomBlockKey)
	{
		pNew = new CXrioCustomBlock();
	}
	else if (strClassID == pXmlKeys->m_strEnabledRefListKey)
	{
		pNew = new CXrioEnabledRefList();
	}

	return pNew;
}

CExBaseObject* CXrioCustomBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_CUSTOMPARAMETER)
	{
		pNew = new CXrioCustomParameter();
	}
	else if (nClassID == XRIOCLASSID_CUSTOMBLOCK)
	{
		pNew = new CXrioCustomBlock();
	}
	else if (nClassID == XRIOCLASSID_ENABLEDREFLIST)
	{
		pNew = new CXrioEnabledRefList();
	}

	return pNew;
}

void CXrioCustomBlock::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	CString strBlockInfo;
	strBlockInfo.Format(_T("Block Id = %s"),m_strID);
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strBlockInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

CExBaseObject *CXrioCustomBlock::FindParaByName(const CString &strMap,const CString &strForeignId)
{
	CXrioCustomParameter *pParameter = NULL;
	CExBaseObject *pCurObj = NULL;
	CExBaseObject *pFind = FindOwnParaByName(strMap,strForeignId);

	POS pos_para = GetHeadPosition();

	while((pos_para)&&(pFind == NULL))
	{
		pCurObj = GetNext(pos_para);

		if (pCurObj->GetClassID() == XRIOCLASSID_CUSTOMBLOCK)
		{
			pFind = ((CXrioCustomBlock*)pCurObj)->FindParaByName(strMap,strForeignId);
		}
	}

	return pFind;
}

CExBaseObject *CXrioCustomBlock::FindParaByFullPath(const CString &strMap)
{
	CXrioCustomParameter *pParameter = NULL;
	CExBaseObject *pCurObj = NULL;
	CString strParaID,strMapPath;
	long nIndex = strMap.Find('$');

	if (nIndex == -1)
	{
		strParaID = strMap;
		strMapPath = _T("");
	}
	else
	{
		strParaID = strMap.Left(nIndex);
		strMapPath = strMap.Mid(nIndex+1);
	}

	CExBaseObject *pFind = FindByID(strParaID);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (pFind->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER)
	{
		return pFind;
	}
	else if (pFind->GetClassID() == XRIOCLASSID_CUSTOMBLOCK)
	{
		CXrioCustomBlock *pCurBlock = (CXrioCustomBlock*)pFind;
		return pCurBlock->FindParaByFullPath(strMapPath);
	}
	else
		return NULL;
}

CExBaseObject *CXrioCustomBlock::FindOwnParaByName(const CString &strMap,const CString &strForeignId)
{
	CXrioCustomParameter *pParameter = NULL;
	CExBaseObject *pCurObj = NULL;
	CExBaseObject *pFind = NULL;

	POS pos_para = GetHeadPosition();

	while(pos_para)
	{
		pCurObj = GetNext(pos_para);

		if (pCurObj->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER)
		{
			pParameter = (CXrioCustomParameter *)pCurObj;

			if ((pParameter->m_strID == strMap)&&((strForeignId.IsEmpty())||(pParameter->m_strForeignId == strForeignId)))
			{
				pFind = pParameter;
				break;
			}
		}
	}

	return pFind;
}