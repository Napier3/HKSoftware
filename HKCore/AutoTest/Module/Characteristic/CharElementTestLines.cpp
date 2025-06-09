//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementTestLines.cpp  CCharElementTestLines


#include "stdafx.h"
#include "CharElementTestLines.h"
#include "CharElementLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementTestLines::CCharElementTestLines()
{
	//初始化属性
	m_pTestPoints = NULL;
}

CCharElementTestLines::~CCharElementTestLines()
{
}

long CCharElementTestLines::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharElementTestLines::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CCharElementTestLines::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementTestLines *p = (CCharElementTestLines*)pObj;

	return TRUE;
}

BOOL CCharElementTestLines::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementTestLines *p = (CCharElementTestLines*)pDest;

	return TRUE;
}

CBaseObject* CCharElementTestLines::Clone()
{
	CCharElementTestLines *p = new CCharElementTestLines();
	Copy(p);
	return p;
}

CBaseObject* CCharElementTestLines::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCharElementTestLines *p = new CCharElementTestLines();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCharElementTestLines::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTTESTPOINTS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharElementTestLines::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharElementTestLineKey)
	{
		pNew = new CCharElementTestLine();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementTestPointsKey)
	{
		pNew = new CXCharElementTestPoints();
	}
	
	return pNew;
}

CExBaseObject* CCharElementTestLines::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == CHARCLASSID_CCHARELEMENTTESTPOINTS)
	{
		pNew = new CXCharElementTestPoints();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINE)
	{
		pNew = new CCharElementTestLine();
	}
	
	return pNew;
}

void CCharElementTestLines::InitAfterRead()
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTPOINTS)
		{
			CXCharElementTestPoints *pTestPoints = (CXCharElementTestPoints *)pObj;
			m_pTestPoints = pTestPoints;
		}
	}

	if (m_pTestPoints == NULL)
	{
		m_pTestPoints = new CXCharElementTestPoints;
		AddNewChild(m_pTestPoints);
	}
}