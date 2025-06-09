//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpExprTypesMngr.cpp  CPpExprTypesMngr


#include "stdafx.h"
#include "PpExprTypesMngr.h"

CPpExprTypesMngr::CPpExprTypesMngr()
{
	//初始化属性

	//初始化成员变量
	m_pExprRcvTypes = NULL;
	m_pExprSendTypes = NULL;

	CExprMngrXmlRWKeys::Create();
}

CPpExprTypesMngr::~CPpExprTypesMngr()
{
	CExprMngrXmlRWKeys::Release();
}

long CPpExprTypesMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprTypesMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprTypesMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CPpExprTypesMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EXPCLASSID_CPPEXPRRCVTYPES)
		{
			m_pExprRcvTypes = (CPpExprRcvTypes*)p;
		}
		else if (nClassID == EXPCLASSID_CPPEXPRSENDTYPES)
		{
			m_pExprSendTypes = (CPpExprSendTypes*)p;
		}
	}

	if (m_pExprRcvTypes == NULL)
	{
		m_pExprRcvTypes = (CPpExprRcvTypes*)AddNewChild(new CPpExprRcvTypes());
	}

	if (m_pExprSendTypes == NULL)
	{
		m_pExprSendTypes = (CPpExprSendTypes*)AddNewChild(new CPpExprSendTypes());
	}

}

BOOL CPpExprTypesMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpExprTypesMngr *p = (CPpExprTypesMngr*)pObj;

	return TRUE;
}

BOOL CPpExprTypesMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpExprTypesMngr *p = (CPpExprTypesMngr*)pDest;

	return TRUE;
}

CBaseObject* CPpExprTypesMngr::Clone()
{
	CPpExprTypesMngr *p = new CPpExprTypesMngr();
	Copy(p);
	return p;
}

BOOL CPpExprTypesMngr::CanPaste(UINT nClassID)
{
	if (nClassID == EXPCLASSID_CPPEXPRRCVTYPES)
	{
		return TRUE;
	}

	if (nClassID == EXPCLASSID_CPPEXPRSENDTYPES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpExprTypesMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpExprRcvTypesKey)
	{
		pNew = new CPpExprRcvTypes();
	}
	else if (strClassID == pXmlKeys->m_strCPpExprSendTypesKey)
	{
		pNew = new CPpExprSendTypes();
	}

	return pNew;
}

CExBaseObject* CPpExprTypesMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EXPCLASSID_CPPEXPRRCVTYPES)
	{
		pNew = new CPpExprRcvTypes();
	}
	else if (nClassID == EXPCLASSID_CPPEXPRSENDTYPES)
	{
		pNew = new CPpExprSendTypes();
	}

	return pNew;
}

CString CPpExprTypesMngr::GetExprMngrFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("Expressions.xml");

	return strFile;
}

void CPpExprTypesMngr::ReadExpressionXmlFile()
{
	CString strFile = GetExprMngrFile();
	OpenXmlFile(strFile, CExprMngrXmlRWKeys::g_pXmlKeys);
}

void CPpExprTypesMngr::WriteExpressionXmlFile()
{
	CString strFile = GetExprMngrFile();
	SaveXmlFile(strFile, CExprMngrXmlRWKeys::g_pXmlKeys);
}
