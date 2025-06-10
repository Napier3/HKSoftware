#include "stdafx.h"
#include "GbWzdAiSwitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
CGbAiCase::CGbAiCase(void)
{
	m_pParas = NULL;
	m_pScript = NULL;
}

CGbAiCase::~CGbAiCase(void)
{
}

long CGbAiCase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbAiOptrBase::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey,oNode,m_strValue);
	
	return 0;
}

long CGbAiCase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbAiOptrBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

	return 0;
}

long CGbAiCase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbAiOptrBase::SerializeOwn(oBinaryBuffer);


	return 0;
}


BOOL CGbAiCase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbAiOptrBase::CopyOwn(pDest);

	CGbAiCase *p = (CGbAiCase*)pDest;
	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CGbAiCase::Clone()
{
	CGbAiCase* pCase = new CGbAiCase();
	Copy(pCase);

	return pCase;
}


CExBaseObject* CGbAiCase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiScriptKey)
	{
		m_pScript = new CGbAiParaScript();
		return m_pScript;
	}

	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiParasKey)
	{
		m_pParas = new CGbWzdAiParasBase();
		return m_pParas;
	}

	return NULL;
}

CExBaseObject* CGbAiCase::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiScript)
	{
		m_pScript = new CGbAiParaScript();
		return m_pScript;
	}

	if (nClassID == GBCLASSID_GbWzdAiParas)
	{
		m_pParas = new CGbWzdAiParasBase();
		return m_pParas;
	}

	return NULL;
}

DWORD CGbAiCase::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	if (m_pScript != NULL)
	{
		m_dwValue = m_pScript->ScptCal(pXMatchObj, bAllMatchMode, pSttGuideBook);
	}

	return m_dwValue;
}

void CGbAiCase::InitMacroPara(CDataGroup *pMacroParas)
{
	if (m_pParas != NULL)
	{
		m_pParas->InitMacroPara(pMacroParas);
	}
}


//针对需要第二轮进行数据处理的，例如switch/case
DWORD CGbAiCase::ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	if (m_pParas == NULL)
	{
		return 0;
	}

	m_pParas->SetMacroParasValueByAI(pDvmMatchListFilter, pSttGuideBook);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
CGbAiSwitch::CGbAiSwitch()
{
	m_pActiveCase = NULL;
}

CGbAiSwitch::~CGbAiSwitch()
{

}

long CGbAiSwitch::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbAiSwitch::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiCaseKey)
	{
		return new CGbAiCase();
	}

	return NULL;
}

CExBaseObject* CGbAiSwitch::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiCase)
	{
		return new CGbAiCase();
	}

	return NULL;
}

long CGbAiSwitch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbAiSwitch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

DWORD CGbAiSwitch::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbAiCase *pCase = NULL;
	m_dwValue = 0;

	while (pos != NULL)
	{
		pCase = (CGbAiCase *)GetNext(pos);

		if (pCase->ScptCal(pXMatchObj, TRUE, pSttGuideBook))
		{//设置成功
			m_pActiveCase = pCase;
			break;
		}
	}

	return 0;
}


void CGbAiSwitch::InitMacroPara(CDataGroup *pMacroParas)
{
	POS pos = GetHeadPosition();
	CGbAiCase *pCase = NULL;

	while (pos != NULL)
	{
		pCase = (CGbAiCase *)GetNext(pos);
		pCase->InitMacroPara(pMacroParas);
	}
}

//复归当前活动的case
void CGbAiSwitch::ClearScptState()
{
	m_pActiveCase = NULL;
	CGbAiOptrBase::ClearScptState();
}

//针对需要第二轮进行数据处理的，例如switch/case
DWORD CGbAiSwitch::ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	if (m_pActiveCase == NULL)
	{
		return 0;
	}

	m_pActiveCase->ScptCalEx(pDvmMatchListFilter, bAllMatchMode, pSttGuideBook);

	return 0;
}

