//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdCreator.cpp  CSttCmdCreator


#include "stdafx.h"
#include "SttCmdCreator.h"
#include "SttCmdDefineGlobal.h"

#include "SttAssistCmd.h"
#include "SttAtsCmd.h"
#include "SttDebugCmd.h"
#include "SttRemoteCmd.h"
#include "SttSysState.h"
#include "SttSystemCmd.h"
#include "SttAdjustCmd.h"
#include "SttTestCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCmdCreator::CSttCmdCreator()
{

}

CSttCmdCreator::~CSttCmdCreator()
{
}

CExBaseObject* CSttCmdCreator::SttCmdCreate(const CString &strCmdXml)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	BSTR bstrCmdXml;
	bstrCmdXml = strCmdXml.AllocSysString();

	if (!pRWDoc->SetXml(bstrCmdXml))
	{
		delete pRWDoc;
		return NULL;
	}

	::SysFreeString(bstrCmdXml);

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetFirstRootNode();

	if (pDocRoot == NULL)
	{
		delete pRWDoc;
		return NULL;
	}

	if(!pDocRoot->IsValid())
	{
		delete pRWDoc;
		return NULL;
	}

	CString strNodeName;
	strNodeName = pDocRoot->GetNodeName();

	BOOL bAddTail = FALSE;
	CExBaseObject *pNew = CreateNewChild(strNodeName, bAddTail, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (pNew != NULL)
	{
		++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		pNew->XmlRead(*pDocRoot, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	}

	delete pRWDoc;	
	return pNew;
}


CExBaseObject* CSttCmdCreator::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSttSysStateKey)
	{
		pNew = new CSttSysState;
	}
	else if (strClassID == pXmlKeys->m_strCSttAssistCmdKey)
	{
		pNew = new CSttAssistCmd;
	}
	else if (strClassID == pXmlKeys->m_strCSttDebugCmdKey)
	{
		pNew = new CSttDebugCmd;
	}
	else if (strClassID == pXmlKeys->m_strCSttRemoteCmdKey)
	{
		pNew = new CSttRemoteCmd;
	}
	else if (strClassID == pXmlKeys->m_strCSttAtsCmdKey)
	{
		pNew = new CSttAtsCmd;
	}
	else if (strClassID == pXmlKeys->m_strCSttSystemCmdKey)
	{
		pNew = new CSttSystemCmd;
	}
	else if (strClassID == pXmlKeys->m_strCSttAdjustCmdKey)
	{
		pNew = new CSttAdjustCmd;
	}
	else if (strClassID == pXmlKeys->m_strCSttTestCmdKey)
	{
		pNew = new CSttTestCmd;
	}

	return pNew;
}
