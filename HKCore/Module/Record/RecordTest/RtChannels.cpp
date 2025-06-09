// RtChannels.cpp: implementation of the CRtChannels class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtChannels.h"
#include "RtVariables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CRtChannels::g_pszKeyChannels = "channels";

CRtChannels::CRtChannels()
{
	m_pScript = NULL;
	m_strName = "RtChannels";
	m_strID = m_strName;
}

CRtChannels::~CRtChannels()
{
}

UINT CRtChannels::GetClassID()
{
	return RTCLASSID_CHANNELS;
}
// 
// CExBaseObject* CRtChannels::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtChannels::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNew = NULL;
// 
// 	if(strcmp(pszClassID , CRtChannel::g_pszKeyChannel) == 0)
// 	{
// 		pNew = new CRtChannel();
// 	}
// 	else if(strcmp(pszClassID , CRtScript::g_pszKeyScript) == 0)
// 	{
// 		if (m_pScript == NULL)
// 		{
// 			m_pScript = new CRtScript();
// 			pNew = m_pScript;
// 		}
// 	}
// 
// 	return pNew;
// }
// 
// CExBaseObject* CRtChannels::CreateNewChild(long nClassID)
// {
// 	return NULL;
// }
// 
// const char* CRtChannels::GetXmlElementKey()
// {
// 	return g_pszKeyChannels;
// }
// 
// 
// long CRtChannels::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
// 
// BOOL CRtChannels::ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes)
// {
// 	int nCount = oNodes->Getlength();
// 	int nIndex = 0;
// 	MSXML::IXMLDOMNodePtr oNode = NULL;	
// 	CString strChanID;	
// 	CRtChannel *pChan = NULL;
// 
// 	POS pos  = GetHeadPosition();
// 	while(pos)
// 	{
// 		pChan = (CRtChannel *)GetNext(pos);
// 		oNode = oNodes->Getitem(nIndex);
// 		//xml_GetAttibuteValue(CRtChannel::g_pszKeyID, oNode, strChanID);	
// 		if(pChan != NULL && oNode != NULL)
// 		{
// 			pChan->ReadSetsValueXml(oNode);
// 		}
// 		nIndex++;
// 	}
// 	
// 	return TRUE;
// }
// 
// BOOL CRtChannels::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oChannels = NULL;
// 	oChannels = oXMLDoc->createElement(_bstr_t(g_pszKeyChannels));
// 
// 	CRtChannel *pChan = NULL;
// 	POS pos  = GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pChan = (CRtChannel *)GetNext(pos);
// 
// 		if(pChan->GetClassID() == RTCLASSID_CHANNEL) 
// 		{
// 			pChan->WriteSetsValueXml(oXMLDoc, oChannels);
// 		}
// 	}
// 
// 	oParent->appendChild(oChannels);
// 
// 	return TRUE;
// }

void CRtChannels::AutofitCreateMultiChChild(const CString &strMultiID, char **szAutoMultiChsName)
{
	long nCount = 0;
	CRtChannel *pNew = NULL;

	if ((_stricmp(strMultiID.GetString(), U3) == 0) || (_stricmp(strMultiID.GetString(), I3) == 0))
	{
		nCount = AUTO_MULTI_CH_NAME_COUNT;
	}
	else if ((_stricmp(strMultiID.GetString(), UI) == 0))
	{
		nCount = AUTO_MULTI_UI_CH_NAME_COUNT;
	}
	else
	{
	}

	for (long nIndex = 0; nIndex < nCount; nIndex++)
	{
		pNew = new CRtChannel();

		if (pNew != NULL)
		{
			pNew->SetParent(this);
			AddTail(pNew);
			pNew->InitChannal(szAutoMultiChsName[nIndex]);
		}
	}
}