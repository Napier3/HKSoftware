#include "StdAfx.h"
#include "GbWzdAiBase.h"

#include "GbWzdAiOptr.h"
#include "GbWzdAiKeysFunc.h"
#include "GbWzdAiDO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbAiDataKey::CGbAiDataKey(void)
{
	m_strName = _T("AiDataKey");
	m_pKeyMatchRef = NULL;
}

CGbAiDataKey::~CGbAiDataKey(void)
{
	if (m_pKeyMatchRef != NULL)
	{
		delete m_pKeyMatchRef;
		m_pKeyMatchRef = NULL;
	}
}

long CGbAiDataKey::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbAiDataKey::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CGbAiDataKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);


	return 0;
}

CBaseObject* CGbAiDataKey::Clone()
{
	CGbAiDataKey* pGbWzdAiDataScript = new CGbAiDataKey();
	Copy(pGbWzdAiDataScript);

	return pGbWzdAiDataScript;
}

void CGbAiDataKey::InitGbAiDataKey(CXKeyDB *pKeyDB)
{
	m_pKeyMatchRef = pKeyDB->CreateXKeyMatchRef (m_strName);

	if (m_pKeyMatchRef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%s : match key failed...."), m_strName.GetString());

#ifdef _PSX_IDE_QT_
		m_strName.ClearBytes();
#endif
	}
}

BOOL CGbAiDataKey::Match(CXMatchObject *pXMatchObj)
{
	if (m_pKeyMatchRef == NULL)
	{
		return FALSE;
	}

	CXKeyMatchRefList *pXKeyList = &pXMatchObj->m_listMatchXKeys;
	POS pos = pXKeyList->GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	while (pos != NULL)
	{
		p = (CXKeyMatchRef *)pXKeyList->GetNext(pos);

		if (p->Match(m_pKeyMatchRef))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
CGbAiOptrInterface::CGbAiOptrInterface(void)
{
	m_dwValue = 0;
}

CGbAiOptrInterface::~CGbAiOptrInterface(void)
{

}

DWORD CGbAiOptrInterface::ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	return 0;
}

void CGbAiOptrInterface::InitGbAiDataKey(CXKeyDB *pKeyDB)
{
	POS pos = GetHeadPosition();
	CGbAiOptrInterface *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiOptrInterface *)GetNext(pos);
		p->InitGbAiDataKey(pKeyDB);
	}
}

void CGbAiOptrInterface::InitMacroPara(CDataGroup *pMacroParas)
{

}

void CGbAiOptrInterface::ClearScptState()
{
	m_dwValue = 0;
}

//////////////////////////////////////////////////////////////////////////
CGbAiOptrBase::CGbAiOptrBase(void)
{
	m_dwValue = 0;
}

CGbAiOptrBase::~CGbAiOptrBase(void)
{
}

long CGbAiOptrBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbAiOptrBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CGbAiOptrBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbAiOptrBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptOptrAndKey)
	{
		return new CGbAiOptrAnd();
	}

	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptOptrOrKey)
	{
		return new CGbAiOptrOr();
	}

	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptOptrNotKey)
	{
		return new CGbAiOptrNot();
	}

	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptFuncMustHaveKey)
	{
		return new CGbAiKeysFuncMustHave();
	}

	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptFuncMustNotHaveKey)
	{
		return new CGbAiKeysFuncMustNotHave();
	}

	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDoKey)
	{
		return new CGbWzdAiDO();
	}

	return NULL;
}

DWORD CGbAiOptrBase::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbAiOptrInterface *pScptObj = NULL;

	while (pos != NULL)
	{
		pScptObj = (CGbAiOptrInterface *)GetNext(pos);
		pScptObj->ScptCal(pXMatchObj, TRUE, pSttGuideBook);
	}

	return 0;
}

void CGbAiOptrBase::ClearScptState()
{
	m_dwValue = 0;

	POS pos = GetHeadPosition();
	CGbAiOptrInterface *pScptObj = NULL;

	while (pos != NULL)
	{
		pScptObj = (CGbAiOptrInterface *)GetNext(pos);
		pScptObj->ClearScptState();
	}
}

CExBaseObject* CGbAiOptrBase::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiDATASCPTOPTR_AND)
	{
		return new CGbAiOptrAnd();
	}

	if (nClassID == GBCLASSID_GbWzdAiDATASCPTOPTR_OR)
	{
		return new CGbAiOptrOr();
	}

	if (nClassID == GBCLASSID_GbWzdAiDATASCPTOPTR_NOT)
	{
		return new CGbAiOptrNot();
	}

	if (nClassID == GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTHAVE)
	{
		return new CGbAiKeysFuncMustHave();
	}

	if (nClassID == GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTNOTHAVE)
	{
		return new CGbAiKeysFuncMustNotHave();
	}

	if (nClassID == GBCLASSID_GbWzdAiDO)
	{
		return new CGbWzdAiDO();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
#include "GbWzdAiMacroPara.h"

CDvmData* GbAiGetMacroPara(CExBaseObject *pGbAiObj)
{
	CGbWzdAiMacroPara *pPara = (CGbWzdAiMacroPara*)pGbAiObj->GetAncestor(GBCLASSID_GbWzdAiMacroPara);

	if (pPara == NULL)
	{
		return NULL;
	}

	return pPara->m_pMacroParaRef;
}
