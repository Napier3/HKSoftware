// RtFileWrite.cpp: implementation of the CRtFileWrite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtFileWrite.h"
#include "RtVariables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CRtFileFormatBuffer::g_pszKeyRtFileFormatBuffer = "buffer";
const char* CRtFileFormatBuffer::g_pszKeyBufferID           = "buf-id";

CRtFileFormatBuffer::CRtFileFormatBuffer()
{
	
}

CRtFileFormatBuffer::~CRtFileFormatBuffer()
{
	
}
// 
// long CRtFileFormatBuffer::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeyBufferID, oNode, m_strBufferID);
// 	m_strName = m_strID = m_strBufferID;
// 
// 	return 0;
// }
// 
// long CRtFileFormatBuffer::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	
// 	return 0;
// }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char* CRtFileFormat::g_pszKeyRtFileFormat_Comtrade = "comtrade";
const char* CRtFileFormat::g_pszKeyRtFileFormat_MR1200   = "mr1200";
const char* CRtFileFormat::g_pszKeyRtFileFormat_Record   = "record";
const char* CRtFileFormat::g_pszKeyUse                   = "use";

CRtFileFormat::CRtFileFormat()
{
	m_nUse = 0;
}

CRtFileFormat::~CRtFileFormat()
{

}
// 
// long CRtFileFormat::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeyUse, oNode, m_nUse);
// 
// 	return 0;
// }
// 
// long CRtFileFormat::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
// 
// 
// CExBaseObject* CRtFileFormat::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtFileFormat::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNew = NULL;
// 
// 	if (strcmp(pszClassID, CRtFileFormatBuffer::g_pszKeyRtFileFormatBuffer) ==0 )
// 	{
// 		pNew = new CRtFileFormatBuffer();
// 	}
// 	else
// 	{
// 	}
// 
// 	return pNew;
// }
// 
// CExBaseObject* CRtFileFormat::CreateNewChild(long nClassID)
// {
// 	CExBaseObject *pNew = NULL;
// 	
// 	if (nClassID == RTCLASSID_FILEFORMAT_BUFFER)
// 	{
// 		pNew = new CRtFileFormatBuffer();
// 	}
// 	else
// 	{
// 	}
// 	
// 	return pNew;
// }

long CRtFileFormat::GetIndexByStrBufferID(CString strBufferID)
{
	long nFind = -1;
	CRtFileFormatBuffer *pFileFormatBuffer = NULL;
	long nCount = GetCount();
	
	for(long nIndex = 0; nIndex < nCount; nIndex++)
	{
		pFileFormatBuffer = (CRtFileFormatBuffer *)GetAt(nIndex);
		ASSERT(pFileFormatBuffer != NULL);
		
		if (strBufferID == pFileFormatBuffer->m_strBufferID)
		{
			nFind = nIndex;
			break;
		} 
	}

	return nFind;
}

#ifdef AUTO_DEBUG
long CRtFileFormat::WriteXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
{
	return 0;
}
#endif

void CRtFileFormat::AutofitCreateRtFileRecord(CRtVariables *pVariables)
{
	DeleteAll();

	ASSERT(pVariables != NULL);

	if (m_nUse == 0)
	{
		return;
	}

	CRtSingleVariable *pVariable = NULL;
	CRtBinaryVariable *pBinaryVariable = NULL;
	CRtFileFormatBuffer *pNew= NULL;
	POS pos  = pVariables->m_oListAnologVariable.GetHeadPosition();

	//创建模拟通道的RecordBuffer
	while(pos != NULL)
	{
		pVariable = (CRtSingleVariable *)pVariables->m_oListAnologVariable.GetNext(pos);
		ASSERT(pVariable != NULL);

		if (pVariable->IsRtSingleVariable() && (pVariable->GetVariableUseState() == 1))
		{
			pNew = (CRtFileFormatBuffer *)CreateNewChild(RTCLASSID_FILEFORMAT_BUFFER);
			ASSERT(pNew != NULL);
			pNew->m_strBufferID = pVariable->m_strRecordBufferID;

			pNew->SetParent(this);
			AddTail(pNew);
		}
	}

	//创建开关通道的RecordBuffer
	pos = pVariables->m_oListBinaryVariable.GetHeadPosition();

	while(pos != NULL)
	{
		pBinaryVariable = (CRtBinaryVariable *)pVariables->m_oListBinaryVariable.GetNext(pos);
		ASSERT(pBinaryVariable != NULL);
		
		if (pBinaryVariable->IsRtBinaryVariable() && (pBinaryVariable->GetVariableUseState() == 1))
		{
			pNew = (CRtFileFormatBuffer *)CreateNewChild(RTCLASSID_FILEFORMAT_BUFFER);
			ASSERT(pNew != NULL);
			pNew->m_strBufferID = pVariable->m_strRecordBufferID;
			
			pNew->SetParent(this);
			AddTail(pNew);
			break;
		}
	}
}

void CRtFileFormat::AutofitCreateRtFileMR1200(CRtVariables *pVariables)
{
	DeleteAll();
	ASSERT(pVariables != NULL);
	
	if (m_nUse == 0)
	{
		return;
	}
	
	CRtVariable *pVariable = NULL;
	CRtDataAttribute *pAttr = NULL;
	CRtFileFormatBuffer *pNew= NULL;
	POS pos  = pVariables->GetHeadPosition();
	
	while(pos != NULL)
	{
		pVariable = (CRtVariable *)pVariables->GetNext(pos);
		ASSERT(pVariable != NULL);
		
		if (pVariable->IsRtSingleVariable() && (pVariable->GetVariableUseState() == 1))
		{
			CRtDataAttributes *pDataAttrs = pVariable->m_pDataAttrs;

			if (pDataAttrs != NULL)
			{
				POS posAttr = pDataAttrs->GetHeadPosition();
				
				while(posAttr != NULL)
				{
					pAttr = (CRtDataAttribute *)pDataAttrs->GetNext(posAttr);
					ASSERT(pAttr != NULL);

					if (pAttr->GetUse() == 1)
					{
						pNew = (CRtFileFormatBuffer *)CreateNewChild(RTCLASSID_FILEFORMAT_BUFFER);
						ASSERT(pNew != NULL);
						pNew->m_strBufferID = pAttr->m_strBufferID;
						
						pNew->SetParent(this);
						AddTail(pNew);
					}
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char* CRtFileWrite::g_pszKeyFileWrite            = "file-write";
const char* CRtFileWrite::g_pszKeyWriteFileMode        = "write-file-mode";
const char* CRtFileWrite::g_pszKeyWriteFileTimeGap     = "write-file-time-gap";
const char* CRtFileWrite::g_pszKeyWriteFileMode_Time   = "time";
const char* CRtFileWrite::g_pszKeyWriteFileMode_Buffer = "buffer";
const char* CRtFileWrite::g_pszKeyWriteFileMode_None   = "none";


CRtFileWrite::CRtFileWrite()
{
	m_nWriteFileMode     = RTFILEWRITE_MODE_NONE;
	m_nWriteFileTimeGap  = 0;
	
	m_strName = "RtFileWrite";
	m_strID = m_strName;

	m_pRtFileComtrade = NULL;
	m_pRtFileMR1200   = NULL;
	m_pRtFileRecord   = NULL;
	
}

CRtFileWrite::~CRtFileWrite()
{

}
// 
// 
// long CRtFileWrite::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CString strTemp;
// 	xml_GetAttibuteValue(g_pszKeyWriteFileMode, oNode, strTemp);
// 
// 	if (strTemp == g_pszKeyWriteFileMode_Time)
// 	{
// 		m_nWriteFileMode = RTFILEWRITE_MODE_TIME;
// 	}
// 	else if (strTemp == g_pszKeyWriteFileMode_Buffer)
// 	{
// 		m_nWriteFileMode = RTFILEWRITE_MODE_BUFFER;
// 	}
// 	else if (strTemp == g_pszKeyWriteFileMode_None)
// 	{
// 		m_nWriteFileMode = RTFILEWRITE_MODE_NONE;
// 	}
// 	else
// 	{
// 		m_nWriteFileMode = RTFILEWRITE_MODE_NONE;
// 	}
// 
// 	xml_GetAttibuteValue(g_pszKeyWriteFileTimeGap, oNode, m_nWriteFileTimeGap);
// 
// 	return 0;
// }
// 
// long CRtFileWrite::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
// 
// 
// CExBaseObject* CRtFileWrite::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtFileWrite::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CRtFileFormat *pNew = NULL;
// 
// 	if (strcmp(pszClassID, CRtFileFormat::g_pszKeyRtFileFormat_Comtrade) ==0 )
// 	{
// 		if (m_pRtFileComtrade == NULL)
// 		{
// 			pNew = new CRtFileFormat();
// 			m_pRtFileComtrade = pNew;
// 		}
// 	}
// 	else if (strcmp(pszClassID, CRtFileFormat::g_pszKeyRtFileFormat_MR1200) ==0 )
// 	{
// 		if (m_pRtFileMR1200 == NULL)
// 		{
// 			pNew = new CRtFileFormat();
// 			m_pRtFileMR1200 = pNew;
// 		}
// 	}
// 	else if (strcmp(pszClassID, CRtFileFormat::g_pszKeyRtFileFormat_Record) ==0 )
// 	{
// 		if (m_pRtFileRecord == NULL)
// 		{
// 			pNew = new CRtFileFormat();
// 			m_pRtFileRecord = pNew;
// 		}
// 	}
// 	else
// 	{
// 	}
// 	
// 	if (pNew != NULL)
// 	{
// 		pNew->m_strName = pNew->m_strID = pszClassID;			
// 	}
// 
// 	return pNew;
// }
// 
// CExBaseObject* CRtFileWrite::CreateNewChild(long nClassID)
// {	
// 	return NULL;
// }

void CRtFileWrite::AutofitCreateFileWrite(CRtVariables *pVariables)
{
	ASSERT(pVariables != NULL);

	//comtrade
	if (m_pRtFileComtrade == NULL)
	{
		m_pRtFileComtrade = new CRtFileFormat();
		ASSERT(m_pRtFileComtrade != NULL);
		AddTail(m_pRtFileComtrade);
		m_pRtFileComtrade->SetParent(this);
	}
	m_pRtFileComtrade->SetUse(1);

	//mr1200
	if (m_pRtFileMR1200 == NULL)
	{
		m_pRtFileMR1200 = new CRtFileFormat();
		ASSERT(m_pRtFileMR1200 != NULL);
		AddTail(m_pRtFileMR1200);
		m_pRtFileMR1200->SetParent(this);
	}
	else
	{
	}
	m_pRtFileMR1200->SetUse(1);
	m_pRtFileMR1200->AutofitCreateRtFileMR1200(pVariables);

	//record
	if (m_pRtFileRecord == NULL)
	{
		m_pRtFileRecord = new CRtFileFormat();
		ASSERT(m_pRtFileRecord != NULL);
		AddTail(m_pRtFileRecord);
		m_pRtFileRecord->SetParent(this);
	}
	else
	{
	}	
	m_pRtFileRecord->SetUse(1);
	m_pRtFileRecord->AutofitCreateRtFileRecord(pVariables);
}

