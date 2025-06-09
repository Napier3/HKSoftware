#include "StdAfx.h"
#include "SttTestFactory.h"
#include "../../../Module/API/FileApi.h"

CSttTestFactory* g_pSttTestFactory = NULL;

CSttTestFactory::CSttTestFactory()
{
	//2020-10-25  lijunqing
	g_pSttTestFactory = this;

	//创建CMacroXmlKeys对象
	CMacroXmlKeys::Create();
}

CSttTestFactory::~CSttTestFactory()
{
	//销毁CMacroXmlKeys对象
	CMacroXmlKeys::Release();
}


void CSttTestFactory::RegisterTestMacro(const CString &strPxAppName, const CString &strName, const CString &strID, PFNCREATE* pFunCreate)
{
	CSttTestCreator* pSttTestCreator = NULL;
	pSttTestCreator = new CSttTestCreator(strPxAppName, strName, strID, pFunCreate);
	AddTail(pSttTestCreator);
	pSttTestCreator->SetParent(this);
}

CSttTestBase* CSttTestFactory::CreateTestMacroByMacroID(const CString &strMacroID)
{
	CSttTestCreator* pSttTestCreator = (CSttTestCreator*)FindByID(strMacroID);

	if (pSttTestCreator != NULL)
	{
		return pSttTestCreator->Create(TRUE);
	}

	return NULL;
}


CSttTestBase* CSttTestFactory::CreateTestMacroByIndex(long nIndex)
{
	CSttTestCreator* pSttTestCreator;
	long nCount = GetCount();
	
	if(nIndex < nCount)
	{
		pSttTestCreator = (CSttTestCreator*)GetAt(nIndex);
		return pSttTestCreator->Create(TRUE);
	}
	
	return NULL;
}

BOOL CSttTestFactory::BuildXMLFile(const CString &strPath, const CString &strProgID)
{
    if (strPath.GetLength() < 3)
    {
        return FALSE;
    }

    try
    {
        CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

        CXmlRWElementBase *pRoot = pRWDoc->GetDocElement();
        //XmlWrite(*pRWDoc,*pElement,pXmlRWKeys);
        CXmlRWElementBase *pMacros = pRWDoc->CreateElement(CMacroXmlKeys::g_pMacroXmlKeys->m_strTestMacrosKey, pRoot);
        //xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, pMacros, m_strName);
        //xml_SetAttributeValue(CMacroXmlKeys::g_pMacroXmlKeys->m_strProgIDKey, pMacros, strProgID);

        CSttTestCreator *pCreator = NULL;
        CSttTestBase *pSttTestBase = NULL;
        POS pos = GetHeadPosition();

        while (pos != NULL)
        {
            pCreator = (CSttTestCreator*)GetNext(pos);
            pSttTestBase = pCreator->Create(FALSE);
            pSttTestBase->XmlWrite(*pRWDoc, *pMacros, CMacroXmlKeys::g_pMacroXmlKeys);
            delete pSttTestBase;
        }

        ClearFileReadOnlyAttr(strPath);

        pRWDoc->SaveXml(strPath);

        delete pRWDoc;
    }
    catch (...)
    {
        return 0;
    }

	return TRUE;
}

BOOL CSttTestFactory::FindMacroID_NoChgCurrTest(const CString &strMacroID)
{
	CDvmData *pData = (CDvmData *)m_oMacroIDGroup.FindByID(strMacroID);

	if(pData == NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

CSttTestBase* stt_CreateTestMacroByMacroID(const CString &strMacroID)
{
	return g_pSttTestFactory->CreateTestMacroByMacroID(strMacroID);
}

void stt_BuildTestMacroXmlFile(const CString &strFile)
{
    g_pSttTestFactory->BuildXMLFile(strFile,"");
}

