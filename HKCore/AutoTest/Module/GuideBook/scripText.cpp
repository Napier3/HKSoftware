#include "stdafx.h"
#include "scriptText.h"

#ifndef ScriptText_NoGb
#include "GbItemBase.h"
#include "GuideBook.h"
#endif

#include "../../../Module/API/FileApi.h"
#include "../XLanguageResourceAts.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CScriptText::CScriptText()
{
	//m_dwReserved = 1;
	m_nIsRef = 0;
// 	m_nScriptID = -1;
// 	m_strXmlKey = bstrXmlKey;
// 	if(m_strXmlKey == CGbXMLKeys::g_pGbXMLKeys->m_strScriptInitKey)
// 	{
// 		m_nScriptID = SCRIPTID_INITSCRIPT;
// 	}
// 	else if(m_strXmlKey == CGbXMLKeys::g_pGbXMLKeys->m_strScriptNameKey)
// 	{
// 		m_nScriptID = SCRIPTID_NAMESCRIPT;
// 	}
// 	else if(m_strXmlKey == CGbXMLKeys::g_pGbXMLKeys->m_strScriptResultKey)
// 	{
// 		m_nScriptID = SCRIPTID_RESULTSCRIPT;
// 	}
	m_nFuncNameLen = 0;
	memset(m_pszFuncName, 0, SCRIPT_FUNC_NAME_MAXLEN);
}

CScriptText::~CScriptText()
{

}

long CScriptText::InitFuncName(long &nScriptIndex)
{
	//如果是引用，则不处理
	if (m_nIsRef || m_strScriptText.GetLength() < 6)
	{
		m_pszFuncName[0] = 0;
		m_nFuncNameLen = 0;
		return m_nFuncNameLen;
	}

	sprintf(m_pszFuncName, "func%d", nScriptIndex);
	m_nFuncNameLen = strlen(m_pszFuncName);

	return m_nFuncNameLen;
}

long CScriptText::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (Gb_IsScriptType_XVM(this))
	{
		return SerializeOwn_XVM(oBinaryBuffer);
	}	

	if (oBinaryBuffer.IsCalSizeMode())
	{
//		BinarySerializeCalLen(oBinaryBuffer, m_nScriptID);
		BinarySerializeCalLen(oBinaryBuffer, m_strScriptText);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsRef);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
//		BinarySerializeRead(oBinaryBuffer, m_nScriptID);
		BinarySerializeRead(oBinaryBuffer, m_strScriptText);
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nIsRef);
		m_strName = m_strID;
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
//		BinarySerializeWrite(oBinaryBuffer, m_nScriptID);
		BinarySerializeWrite(oBinaryBuffer, m_strScriptText);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nIsRef);
	}

	return 0;
}

long CScriptText::SerializeOwn_XVM(CBinarySerialBuffer &oBinaryBuffer)
{
	int nLen = 0;

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsRef);
		BinarySerializeCalLen(oBinaryBuffer, m_nFuncNameLen);
		oBinaryBuffer.AddBufferLength(m_nFuncNameLen);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nIsRef);
		BinarySerializeRead(oBinaryBuffer, m_nFuncNameLen);

		if (m_nFuncNameLen > 0)
		{
			oBinaryBuffer.ReadBuffer(m_pszFuncName, m_nFuncNameLen);
		}

		m_strName = m_strID;
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
//		BinarySerializeWrite(oBinaryBuffer, m_nScriptID);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nIsRef);
		BinarySerializeWrite(oBinaryBuffer, m_nFuncNameLen);

		if (m_nFuncNameLen > 0)
		{
			oBinaryBuffer.WriteBuffer(m_pszFuncName, m_nFuncNameLen);
		}
	}

	return 0;
}

long CScriptText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strScriptIsRefKey, oNode, m_nIsRef);
	xml_GetCDATA(oNode, m_strScriptText);
	//if (m_nIsRef == 1)
	{
		//xml_GetCDATA(oNode, m_strScriptText);
	}

	return 0;
}

long CScriptText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strScriptIsRefKey, oElement, m_nIsRef);

	//if (m_nIsRef == 0)
	{
		xml_SetCDATA(oXMLDoc, oElement, m_strScriptText);
	}

	return 0;
}

BOOL CScriptText::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CScriptText* pScriptText = (CScriptText*)pObj;

		if(CExBaseObject::IsEqual(pObj) && pScriptText->m_strScriptText == m_strScriptText)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}	

BOOL CScriptText::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CScriptText* pScriptText = (CScriptText*)pDesObj;
	pScriptText->m_strScriptText = m_strScriptText;
	pScriptText->m_nIsRef = m_nIsRef;

	CExBaseObject::CopyOwn(pScriptText);

	return TRUE;
}

CBaseObject* CScriptText::Clone()
{
	CScriptText* pScriptText = new CScriptText();
	Copy(pScriptText);

	return pScriptText;
}

BOOL CScriptText::UpdateOwn(CBaseObject* pDest)
{
	CScriptText* pScriptText = (CScriptText*)pDest;
	pScriptText->m_strScriptText = m_strScriptText;
	pScriptText->m_nIsRef = m_nIsRef;

	return TRUE;
}

CExBaseObject* CScriptText::GetParentGbItem()
{
	CExBaseObject *pParent = (CExBaseObject*)GetParent();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;
	ASSERT (pParent != NULL);

	while (TRUE)
	{
		nClassID = pParent->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			pItem = pParent;
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent == NULL)
		{
			break;
		}
	}

	return pParent;
}

CExBaseObject* CScriptText::GetScriptTextMngr()
{
#ifndef ScriptText_NoGb
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GetScriptLibGlobal();
#else
	return NULL;
#endif
}

CScriptText* CScriptText::GetRefScriptText()
{
#ifndef ScriptText_NoGb
	//CScriptTextMngr *pMngr = (CScriptTextMngr*) GetScriptTextMngr();
	//CScriptText *pFind = (CScriptText*)pMngr->FindByID(m_strID);
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	CScriptText *pFind = pGuideBook->FindScriptText(m_strID);
	return pFind;
#else
	return NULL;
#endif
}

void CScriptText::ClearItemInDbState()
{
	m_strScriptText.Empty();
}

//////////////////////////////////////////////////////////////////////////
//
CBaseObject* CScriptTextInit::Clone()
{
	CScriptTextInit *pNew = new CScriptTextInit();

	Copy(pNew);

	return pNew;
}

CBaseObject* CScriptTextName::Clone()
{
	CScriptTextName *pNew = new CScriptTextName();

	Copy(pNew);

	return pNew;
}

CBaseObject* CScriptTextResult::Clone()
{
	CScriptTextResult *pNew = new CScriptTextResult();

	Copy(pNew);

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CScriptTextMngr::CScriptTextMngr()
{

}

CScriptTextMngr::~CScriptTextMngr()
{

}

long CScriptTextMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);
	return 0;
}

long CScriptTextMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CScriptTextMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CScriptTextMngr::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CScriptTextMngr::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CScriptTextMngr::Clone()
{
	CScriptTextMngr* pObj = new CScriptTextMngr();
	Copy(pObj);

	return pObj;
}


CExBaseObject* CScriptTextMngr::CreateNewChild(long nClassID)
{
	return new CScriptText();
}

CExBaseObject* CScriptTextMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return new CScriptText();
}

CScriptText* CScriptTextMngr::AddNewScriptText(const CString &strID)
{
	CScriptText *p = new CScriptText();
	p->m_strID = strID;
	p->m_strName = strID;
	AddTail(p);
	return p;
}

BOOL CScriptTextMngr::OpenScriptMngrFile(const CString &strFile)
{
	CString strScriptMngrFile = strFile;
	strScriptMngrFile.Trim();

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = GB_ScriptLibrary_Default_File;
	}

	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strScriptMngrFile;

	if (IsFileExist(strPath))
	{
		DeleteAll();

		if ( OpenXmlFile(strPath, GetXmlElementKey(), CGbXMLKeys::g_pGbXMLKeys) )
		{
			m_strScriptMngrFile = strScriptMngrFile;
			m_strID = strFile;
			m_strName = strFile;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CScriptTextMngr::SaveScriptMngrFile(const CString &strFile)
{
	CString strScriptMngrFile = strFile;
	strScriptMngrFile.Trim();

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = m_strScriptMngrFile;
	}

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = GB_ScriptLibrary_Default_File;
	}

	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strScriptMngrFile;

	return SaveXmlFile(strPath, CGbXMLKeys::g_pGbXMLKeys);
}

void CScriptTextMngr::Import(CScriptTextMngr *pSrc)
{
	POS pos = pSrc->GetHeadPosition();
	CScriptText *p    = NULL;
	CScriptText *pNew = NULL;

	while (pos != NULL)
	{
		p = (CScriptText *)pSrc->GetNext(pos);

		pNew = (CScriptText *)FindByID(p->m_strID);

		if (pNew == NULL)
		{
			pNew = (CScriptText*)p->Clone();
			AddNewChild(pNew);
		}
		else
		{
			//脚本不一致，弹出提示框，由于四方需要自动拼接模板，此处会打断自动拼接过程，暂时先注释掉
			//shaol  2019.04.24
// 			if (p->m_strScriptText != pNew->m_strScriptText)
// 			{
// 				CString strMsg;
// 				strMsg.Format(g_sLangTxt_ScriptOverwrite/*_T("脚本【%s】已经存在，并且两个脚本不一致，是否覆盖?")*/, p->m_strID);
// 				UINT nRet = AfxMessageBox(strMsg, MB_YESNO | MB_ICONQUESTION);
// 
// 				if (nRet == IDYES)
// 				{
// 					pNew->m_strScriptText = p->m_strScriptText;
// 				}
// 			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
CScriptTextMngrGlobalPool* CScriptTextMngrGlobalPool::g_pScriptTextMngrGlobalPool = NULL;
long CScriptTextMngrGlobalPool::g_nScriptTextMngrGlobalPool = 0;

CScriptTextMngrGlobalPool::CScriptTextMngrGlobalPool()
{

}

CScriptTextMngrGlobalPool::~CScriptTextMngrGlobalPool()
{
	
}

CScriptTextMngr* CScriptTextMngrGlobalPool::CreateScriptTextMngr(const CString &strFile)
{
	ASSERT (g_pScriptTextMngrGlobalPool != NULL);
	
	CString strScriptMngrFile = strFile;

//去掉空文件作为缺省文件的处理
// 	if (strScriptMngrFile.GetLength() == 0)
// 	{
// 		strScriptMngrFile = GB_ScriptLibrary_Default_File;
// 	}

	if (strScriptMngrFile.GetLength() == 0)
	{
		return NULL;
	}

	CScriptTextMngr *pFind = (CScriptTextMngr*)g_pScriptTextMngrGlobalPool->FindByID(strScriptMngrFile);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CScriptTextMngr();
	BOOL b = pFind->OpenScriptMngrFile(strScriptMngrFile);

	if (!b)
	{
		pFind->SaveScriptMngrFile(strScriptMngrFile);
	}

	g_pScriptTextMngrGlobalPool->AddNewChild(pFind);
	return pFind;
}


void CScriptTextMngrGlobalPool::Create()
{
	g_nScriptTextMngrGlobalPool++;

	if (g_nScriptTextMngrGlobalPool == 1)
	{
		g_pScriptTextMngrGlobalPool = new CScriptTextMngrGlobalPool();
	}
}

void CScriptTextMngrGlobalPool::Release()
{
	g_nScriptTextMngrGlobalPool--;

	if (g_nScriptTextMngrGlobalPool == 0)
	{
		delete g_pScriptTextMngrGlobalPool;
		g_pScriptTextMngrGlobalPool = NULL;
	}
}
