#include "stdafx.h"
#include "ResultsRec.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"
CResultsRec::CResultsRec()
{
	m_strName = _T("检查结果");
	m_strID = _T("CheckResults");

	//初始化属性
	m_nAllTipIndex = 0;
	m_nAllWarningIndex = 0;
	m_nAllErrorIndex = 0;
	m_nAllFatalErrorIndex = 0;
	m_bExportRpt = FALSE;


}

CResultsRec::~CResultsRec()
{
}

void CResultsRec::ResetRec()
{
	DeleteAll();
	m_nAllTipIndex = 0;
	m_nAllWarningIndex = 0;
	m_nAllErrorIndex = 0;
	m_nAllFatalErrorIndex = 0;
}

void CResultsRec::Statis_AllResults()
{
	CResultRec *pResultRec = new CResultRec;
	AddNewChild(pResultRec);

	pResultRec->m_strErrorType =/*"结果统计："*/g_sLangTxt_SCLCompare_ResultStatistic;
	pResultRec->m_strErrorText = "\\";
	pResultRec->m_strErrorPos = "\\";
	pResultRec->m_nTipIndex = m_nAllTipIndex;
	pResultRec->m_nWarningIndex = m_nAllWarningIndex;
	pResultRec->m_nErrorIndex = m_nAllErrorIndex;
	pResultRec->m_nFatalErrorIndex = m_nAllFatalErrorIndex;
}

// #ifdef XML_USE_TINYXML
// 
// long CResultsRec::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 	if (m_strName.GetLength() == 0)
// 	{
// 		m_strName = m_strID;
// 	}
// 
// 	return 0;
// }
// long CResultsRec::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 
// 
// 	return 0;
// }
// long CResultsRec::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
// }
// 
// #else
// 
// long CResultsRec::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 	if (m_strName.GetLength() == 0)
// 	{
// 		m_strName = m_strID;
// 	}
// 
// 	return 0;
// }
// 
// long CResultsRec::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 
// 	return 0;
// }
// long CResultsRec::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
// }
// 
// #endif

long CResultsRec::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

BOOL CResultsRec::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CResultsRec *p = (CResultsRec*)pObj;

	return TRUE;
}

BOOL CResultsRec::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CResultsRec *p = (CResultsRec*)pDest;

	return TRUE;
}

CBaseObject* CResultsRec::Clone()
{
	CResultsRec *p = new CResultsRec();
	Copy(p);
	return p;
}

CExBaseObject* CResultsRec::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptCtrlKey)
	{
		pNew = new CResultRec();
	}

	return pNew;
}

CExBaseObject* CResultsRec::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CRPTCTRL)
	{
		pNew = new CResultRec();
	}

	return pNew;
}

BOOL CResultsRec::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CRPTCTRL)
	{
		return TRUE;
	}

	return FALSE;
}

