// RtCfgAppModels.cpp: implementation of the CRtCfgAppModels class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtCfgAppModels.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char* CRtCfgAppModel::g_pszKeyAppModel        = "app-model";
const char* CRtCfgAppModel::g_pszKeyMaxSpyBuffer    = "max-spy-buffer";
const char* CRtCfgAppModel::g_pszKeyMaxRecordBuffer = "max-record-buffer";
const char* CRtCfgAppModel::g_pszKeyHDBuffer        = "hd-buffer";

CRtCfgAppModel::CRtCfgAppModel()
{
	m_nMaxSpyBuffer    = 0;
	m_nMaxRecordBuffer = 0;
	m_nHDBuffer        = 0;
}

CRtCfgAppModel::~CRtCfgAppModel()
{
}
// 
// long CRtCfgAppModel::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 	
// 	xml_GetAttibuteValue(g_pszKeyMaxSpyBuffer,  oNode, m_nMaxSpyBuffer);
// 	xml_GetAttibuteValue(g_pszKeyMaxRecordBuffer,  oNode, m_nMaxRecordBuffer);
// 	xml_GetAttibuteValue(g_pszKeyHDBuffer,  oNode, m_nHDBuffer);
// 		
// 	return 0;
// }
// 
// long CRtCfgAppModel::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }

CRtCfgAppModel* CRtCfgAppModel::Clone()
{
	CRtCfgAppModel *pNew = new CRtCfgAppModel();

	pNew->m_strName          = m_strName;
	pNew->m_strID            = m_strID;
	pNew->m_nMaxSpyBuffer    = m_nMaxSpyBuffer;
	pNew->m_nMaxRecordBuffer = m_nMaxRecordBuffer;
	pNew->m_nHDBuffer        = m_nHDBuffer;

	return pNew;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtCfgAppModels* CRtCfgAppModels::g_pRtCfgAppModels = NULL;
long  CRtCfgAppModels::m_nRtCfgAppModelsRefCount    = 0;

CRtCfgAppModels* CRtCfgAppModels::CreateRtCfgAppModels()
{
	m_nRtCfgAppModelsRefCount++;

	if (m_nRtCfgAppModelsRefCount == 1)
	{
		g_pRtCfgAppModels = new CRtCfgAppModels();
	}

	return g_pRtCfgAppModels;
}

void CRtCfgAppModels::Release()
{
	m_nRtCfgAppModelsRefCount--;

	if (m_nRtCfgAppModelsRefCount == 0)
	{
		delete g_pRtCfgAppModels;
		g_pRtCfgAppModels = NULL;
	}
}


const char* CRtCfgAppModels::g_pszKeyAppModels = "app-models";

CRtCfgAppModels::CRtCfgAppModels()
{
	m_strName = "RtCfgAppModels";
}

CRtCfgAppModels::~CRtCfgAppModels()
{
}
// 
// CExBaseObject* CRtCfgAppModels::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtCfgAppModels::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNew = NULL;
// 
// 	if (strcmp(pszClassID, CRtCfgAppModel::g_pszKeyAppModel) == 0)
// 	{
// 		pNew = new CRtCfgAppModel();
// 	}
// 
// 	return pNew;
// }
// 
// CExBaseObject* CRtCfgAppModels::CreateNewChild(long nClassID)
// {
// 	return NULL;
// }
// 
// CRtCfgAppModel* CRtCfgAppModels::Clone(const CString &strID)
// {
// 	CRtCfgAppModel *pFind = (CRtCfgAppModel*)FindByID(strID);
// 	CRtCfgAppModel *pNew = NULL;
// 
// 	if (pFind != NULL)
// 	{
// 		pNew = pFind->Clone();
// 	}
// 
// 	return pNew;
// }

