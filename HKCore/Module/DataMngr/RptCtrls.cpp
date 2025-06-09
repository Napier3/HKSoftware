//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataset.cpp  CRptCtrls


#include "stdafx.h"
#include "RptCtrls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptCtrls::CRptCtrls()
{
	m_strName = /*g_sLangTxt_DataSets*/_T("报告控制块");
	m_strID = _T("ReportControl");

	//初始化属性


}

CRptCtrls::~CRptCtrls()
{
}

long CRptCtrls::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CRptCtrls::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}
long CRptCtrls::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CRptCtrls::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRptCtrls::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptCtrls *p = (CRptCtrls*)pObj;

	return TRUE;
}

BOOL CRptCtrls::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptCtrls *p = (CRptCtrls*)pDest;

	return TRUE;
}

CBaseObject* CRptCtrls::Clone()
{
	CRptCtrls *p = new CRptCtrls();
	Copy(p);
	return p;
}

CExBaseObject* CRptCtrls::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptCtrlKey)
	{
		pNew = new CRptCtrl();
	}

	return pNew;
}

CExBaseObject* CRptCtrls::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CRPTCTRL)
	{
		pNew = new CRptCtrl();
	}

	return pNew;
}

BOOL CRptCtrls::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CRPTCTRL)
	{
		return TRUE;
	}

	return FALSE;
}

