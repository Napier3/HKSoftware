#include "stdafx.h"
#include "SttXmlSerialize.h"

#include"../../../Module/API/GlobalConfigApi.h"
#include"../../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttXmlSerializeTool
CSttXmlSerializeTool::CSttXmlSerializeTool()
{
	m_pSttXmlSerialize = NULL;
	m_pRWDoc = NULL;
}

CSttXmlSerializeTool::~CSttXmlSerializeTool()
{
	Release();
}

void CSttXmlSerializeTool::Release()
{
	if (m_pSttXmlSerialize != NULL)
	{
		delete m_pSttXmlSerialize;
		m_pSttXmlSerialize = NULL;
	}

	if (m_pRWDoc != NULL)
	{
		delete m_pRWDoc;
		m_pRWDoc = NULL;
	}
}

BOOL CSttXmlSerializeTool::is_serialize_mode_read()
{
	if (m_pSttXmlSerialize == NULL)
	{
		return FALSE;
	}

	return (m_pSttXmlSerialize->get_serialize_mode() == STT_XML_SERIALIZE_MODE_READ);
}

BOOL CSttXmlSerializeTool::is_serialize_mode_write()
{
	if (m_pSttXmlSerialize == NULL)
	{
		return FALSE;
	}

	return (m_pSttXmlSerialize->get_serialize_mode() == STT_XML_SERIALIZE_MODE_WRITE);
}

BOOL CSttXmlSerializeTool::is_serialize_mode_register()
{
	if (m_pSttXmlSerialize == NULL)
	{
		return FALSE;
	}

	return (m_pSttXmlSerialize->get_serialize_mode() == STT_XML_SERIALIZE_MODE_RIGISTER);
}
//#include<QDebug>
#ifdef _PSX_IDE_QT_
#include<QTextCodec>
#endif

long CSttXmlSerializeTool::SttXmlSerializeRead(CExBaseObject *pSttObj)
{
	ASSERT(m_pRWDoc != NULL);
	if (m_pRWDoc == NULL)
	{
		return 0;
	}

	CXmlRWNodeBase *pDocRoot = m_pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(pSttObj->GetXmlElementKey());

	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	long nRet = pSttObj->XmlRead(*pDocRoot, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	return nRet;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRead(CExBaseObject *pSttObj, const char *pszXmlBuffer, long nLen)
{//pszXmlBuffer:为utf-8字节流
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	pRWDoc->SetXml_UTF8((char *)pszXmlBuffer,nLen);
	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(pSttObj->GetXmlElementKey());

	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	long nRet = pSttObj->XmlRead(*pDocRoot, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	m_pRWDoc = pRWDoc;
	m_pSttXmlSerialize = new CSttXmlSerializeRead(m_pRWDoc, (CXmlRWElementBase*)pDocRoot);

	return m_pSttXmlSerialize;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRead(CExBaseObject *pSttObj, const CString &strFile)
{
	return CreateXmlSerializeRead(pSttObj->GetXmlElementKey(), strFile);
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRead(BSTR bstrXmlRootKey, const CString &strFile)
{
	if (!IsFileExist(strFile))
	{
		return NULL;
	}

	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strFile) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete pRWDoc;
			return NULL;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return NULL;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(bstrXmlRootKey);

	if ((pDocRoot == NULL) || (!pDocRoot->IsValid()))
	{
		delete pRWDoc;
		return NULL;
	}

	m_pRWDoc = pRWDoc;
	m_pSttXmlSerialize = new CSttXmlSerializeRead(m_pRWDoc, (CXmlRWElementBase*)pDocRoot);

	return m_pSttXmlSerialize;
}

//write
CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeWrite(CExBaseObject *pSttObj)
{
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	m_pRWDoc = pRWDoc;
	CXmlRWElementBase *pDocElement = pRWDoc->GetDocElement();
	pSttObj->XmlWrite(*m_pRWDoc, *pDocElement, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	
	pDocElement = pRWDoc->GetDocElement();
	CXmlRWElementBase *pRoot = (CXmlRWElementBase*)pDocElement->GetChildNode(pSttObj->GetXmlElementKey());
	m_pSttXmlSerialize = new CSttXmlSerializeWrite(m_pRWDoc, pRoot);
	return m_pSttXmlSerialize;
}

//register
CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRegister(CExBaseObject *pSttObj)
{
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	m_pRWDoc = pRWDoc;
	CXmlRWElementBase *pDocElement = pRWDoc->GetDocElement();
	pSttObj->XmlWrite(*m_pRWDoc, *pDocElement, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CXmlRWElementBase *pRoot = (CXmlRWElementBase*)pDocElement->GetChildNode(pSttObj->GetXmlElementKey());
	m_pSttXmlSerialize = new CSttXmlSerializeRegister(m_pRWDoc, pRoot);
	return m_pSttXmlSerialize;
}

//2021-5-30  lijunqing
CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeWrite(BSTR bstrXmlRootKey)
{
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	m_pRWDoc = pRWDoc;
	CXmlRWElementBase *pDocElement = pRWDoc->GetDocElement();
	
	CXmlRWElementBase *pElement = m_pRWDoc->CreateElement(bstrXmlRootKey,pDocElement);

	pDocElement = pRWDoc->GetDocElement();
	CXmlRWElementBase *pRoot = (CXmlRWElementBase*)pDocElement->GetChildNode(bstrXmlRootKey);
	m_pSttXmlSerialize = new CSttXmlSerializeWrite(m_pRWDoc, pRoot);
	
	return m_pSttXmlSerialize;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRegister(BSTR bstrXmlRootKey)
{
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	m_pRWDoc = pRWDoc;
	CXmlRWElementBase *pDocElement = pRWDoc->GetDocElement();
	CXmlRWElementBase *pElement = m_pRWDoc->CreateElement(bstrXmlRootKey,pDocElement);
	CXmlRWElementBase *pRoot = (CXmlRWElementBase*)pDocElement->GetChildNode(bstrXmlRootKey);
	m_pSttXmlSerialize = new CSttXmlSerializeRegister(m_pRWDoc, pRoot);

	return m_pSttXmlSerialize;
}


//2021-8-12  lijunqing
CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRead(const CString &strFile)
{
	if (!IsFileExist(strFile))
	{
		return NULL;
	}

	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strFile) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete pRWDoc;
			return NULL;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return NULL;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

	if ((pDocRoot == NULL) || (!pDocRoot->IsValid()))
	{
		delete pRWDoc;
		return NULL;
	}

	m_pRWDoc = pRWDoc;
	m_pSttXmlSerialize = new CSttXmlSerializeRead(m_pRWDoc, (CXmlRWElementBase*)pDocRoot);

	return m_pSttXmlSerialize;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRead_String(const CString &strXML)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	BSTR bstrXml = strXML.AllocSysString();

	try
	{
		if (!pRWDoc->SetXml(bstrXml))
		{
			::SysFreeString(bstrXml);
			delete pRWDoc;
			return NULL;
		}
	}
	catch (...)
	{
		::SysFreeString(bstrXml);
		delete pRWDoc;
		return NULL;
	}

	::SysFreeString(bstrXml);
	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

	if ((pDocRoot == NULL) || (!pDocRoot->IsValid()))
	{
		delete pRWDoc;
		return NULL;
	}

	m_pRWDoc = pRWDoc;
	m_pSttXmlSerialize = new CSttXmlSerializeRead(m_pRWDoc, (CXmlRWElementBase*)pDocRoot);

	return m_pSttXmlSerialize;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRead_String_UTF8(char *pszBuffer, long nLen)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	try
	{
		if (!pRWDoc->SetXml_UTF8(pszBuffer, nLen))
		{
			delete pRWDoc;
			return NULL;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return NULL;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

	if ((pDocRoot == NULL) || (!pDocRoot->IsValid()))
	{
		delete pRWDoc;
		return NULL;
	}

	m_pRWDoc = pRWDoc;
	m_pSttXmlSerialize = new CSttXmlSerializeRead(m_pRWDoc, (CXmlRWElementBase*)pDocRoot);

	return m_pSttXmlSerialize;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeWrite()
{
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	m_pRWDoc = pRWDoc;
	CXmlRWElementBase *pDocElement = pRWDoc->GetDocElement();
	m_pSttXmlSerialize = new CSttXmlSerializeWrite(m_pRWDoc, pDocElement);

	return m_pSttXmlSerialize;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::CreateXmlSerializeRegister()
{
	Release();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	m_pRWDoc = pRWDoc;
	CXmlRWElementBase *pDocElement = pRWDoc->GetDocElement();
	m_pSttXmlSerialize = new CSttXmlSerializeRegister(m_pRWDoc, pDocElement);

	return m_pSttXmlSerialize;
}



CSttXmlSerializeBase* CSttXmlSerializeTool::GetCmdChild(BSTR bstrElementKey)
{
	CString strID;
	strID = bstrElementKey;
	CSttXmlSerializeBase *pFind = (CSttXmlSerializeBase*)FindByID(strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	CXmlRWElementBase *pRootElement = m_pSttXmlSerialize->GetElement();

	if (pRootElement == NULL)
	{
		return NULL;
	}

	CXmlRWElementBase *pChildElement = (CXmlRWElementBase*)pRootElement->GetChildNode(bstrElementKey);

	if (pChildElement == NULL)
	{
		return NULL;
	}

	CSttXmlSerializeBase *pNew = m_pSttXmlSerialize->create_new(m_pRWDoc, pChildElement, FALSE);
	AddNewChild(pNew);
	pNew->m_strName = strID;
	pNew->m_strID = strID;

	return pNew;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::GetMacro()
{
	return GetCmdChild(stt_TestMacroKey());
}

CSttXmlSerializeBase* CSttXmlSerializeTool::GetMacroChild(BSTR bstrElementKey)
{
	CString strID, strKey;
	strID = stt_TestMacroKey();
	strKey = bstrElementKey;
	strID += strKey;

	CSttXmlSerializeBase *pFind = (CSttXmlSerializeBase*)FindByID(strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	CSttXmlSerializeBase *pMacro = GetMacro();

	if (pMacro == NULL)
	{
		return NULL;
	}

	CXmlRWElementBase *pMacroElement = pMacro->GetElement();

	if (pMacroElement == NULL)
	{
		return NULL;
	}

	CXmlRWElementBase *pChildElement = (CXmlRWElementBase*)pMacroElement->GetChildNode(bstrElementKey);

	if (pChildElement == NULL)
	{
		return NULL;
	}

	CSttXmlSerializeBase *pNew = m_pSttXmlSerialize->create_new(m_pRWDoc, pChildElement, FALSE);
	AddNewChild(pNew);
	pNew->m_strName = strID;
	pNew->m_strID = strID;

	return pNew;
}

CSttXmlSerializeBase* CSttXmlSerializeTool::GetMacroParas()
{
	return GetMacroChild(stt_ParasKey());
}

CSttXmlSerializeBase* CSttXmlSerializeTool::GetMacroResults()
{
	return GetMacroChild(stt_ResultsKey());
}

CSttXmlSerializeBase* CSttXmlSerializeTool::GetMacroSearchResults()
{
	return GetMacroChild(stt_SearchResultsKey());
}

CSttXmlSerializeBase* CSttXmlSerializeTool::GetParas()
{
	return GetCmdChild(stt_ParasKey());
}

CString CSttXmlSerializeTool::GetMacroID(BSTR bstElementKey)
{
    if(m_pRWDoc == NULL)
        return "";

    if(!m_pRWDoc->IsValid())
        return "";

    CString strMacroID = "";
    CXmlRWNodeBase *pRWNode = m_pRWDoc->GetDocNode();
	pRWNode = pRWNode->GetChildNode(bstElementKey);
    pRWNode = pRWNode->GetChildNode(CSttCmdDefineXmlRWKeys::CSttMacroKey());
    xml_GetAttibuteValue(L"id",*pRWNode,strMacroID);
    return strMacroID;
}

long CSttXmlSerializeTool::Stt_GetXml(char **ppszXmlBuffer, long nOffset)
{
	if (m_pRWDoc == NULL)
	{
        return 0;
	}

	long nLen = m_pRWDoc->GetXml(ppszXmlBuffer, nOffset);
	
    return nLen;
}

BOOL CSttXmlSerializeTool::Stt_WriteFile(const CString &strFile)
{
	if (m_pRWDoc == NULL)
	{
		return FALSE;
	}

	return m_pRWDoc->SaveXml(strFile);
}
