//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataset.cpp  CLogCtrls


#include "stdafx.h"
#include "LogCtrls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLogCtrls::CLogCtrls()
{
	m_strName = /*g_sLangTxt_DataSets*/_T("日志控制块");
	m_strID = _T("LogControl");

	//初始化属性

}

CLogCtrls::~CLogCtrls()
{
}

long CLogCtrls::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CLogCtrls::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}
long CLogCtrls::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CLogCtrls::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CLogCtrls::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CLogCtrls *p = (CLogCtrls*)pObj;

	return TRUE;
}

BOOL CLogCtrls::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CLogCtrls *p = (CLogCtrls*)pDest;

	return TRUE;
}

CBaseObject* CLogCtrls::Clone()
{
	CLogCtrls *p = new CLogCtrls();
	Copy(p);
	return p;
}

CExBaseObject* CLogCtrls::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCLogCtrlKey)
	{
		pNew = new CLogCtrl();
	}

	return pNew;
}

CExBaseObject* CLogCtrls::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CLOGCTRL)
	{
		pNew = new CLogCtrl();
	}

	return pNew;
}

BOOL CLogCtrls::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CLOGCTRL)
	{
		return TRUE;
	}

	return FALSE;
}

