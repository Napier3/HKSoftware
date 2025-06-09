#include "stdafx.h"
#include "HdResReqest.h"
#include "GuideBook.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "../../../Module/TestMacro/TestMacroInterface.h"

CHdResReqest::CHdResReqest()
{
	m_strType = HdResReqType_request;
	m_pPara = NULL;
}

CHdResReqest::~CHdResReqest()
{
	
}

CGbItemBase* CHdResReqest::CloneForTempFile()
{
	return new CHdResReqest();
}

long CHdResReqest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

long CHdResReqest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);

	return 0;
}

long CHdResReqest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strType);

	return 0;
}


////2022-10-4  lijunqing
long CHdResReqest::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		//2022-10-4  lijunqing
		if (g_bGbSaveGbStruDscFile)
		{
			if (pObj->GetClassID() == DTMCLASSID_CDATAGROUP)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


void CHdResReqest::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case DTMCLASSID_CDATAGROUP:
			m_pPara = (CDataGroup*)p;
			break;

		default:
			break;
		}
	}

//2023-9-1 lijunqing 如果是新创建的对象，需要使用GuideBook的hd-res进行初始化
// 	if (m_pPara == NULL)
// 	{
// 		m_pPara = new CDataGroup();
// 		m_pPara->InitAfterRead();
// 		AddNewChild(m_pPara);
// 	}
}

CExBaseObject* CHdResReqest::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCDataGroupKey)
	{
		m_pPara = new CDataGroup();
		return m_pPara;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CHdResReqest::CreateNewChild(long nClassID)
{
	if(nClassID == DTMCLASSID_CDATAGROUP)
	{
		m_pPara = new CDataGroup();
		return m_pPara;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

BOOL CHdResReqest::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CHdResReqest::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

 	CHdResReqest* pHdResReqest = (CHdResReqest*)pDesObj;
	pHdResReqest->m_strType = m_strType;

	CGbItemBase::CopyOwn(pDesObj);

	return TRUE;
}

CBaseObject* CHdResReqest::Clone()
{
	CHdResReqest* pHdResReqest = new CHdResReqest();
	Copy(pHdResReqest);

	return pHdResReqest;
}

CBaseObject* CHdResReqest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CHdResReqest *p = new CHdResReqest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CHdResReqest::CanPaste(UINT nClassID)
{
	return FALSE;
}

CDataGroup* CHdResReqest::GetHdResReqestPara()
{
	if (m_pPara == NULL)
	{
		m_pPara = new CDataGroup();
		AddNewChild(m_pPara);

		CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

		if (pGuideBook->m_pHdRes != NULL)
		{
			m_pPara->AppendCloneEx(*pGuideBook->m_pHdRes);
		}
	}

	return m_pPara;		
}
