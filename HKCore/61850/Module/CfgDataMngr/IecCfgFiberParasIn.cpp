//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFiberParasIn.cpp  IecCfgFiberParasIn


#include "stdafx.h"
#include "IecCfgFiberParasIn.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgFiberParasIn::CIecCfgFiberParasIn()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgFiberParasIn::~CIecCfgFiberParasIn()
{
}

long CIecCfgFiberParasIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgFiberParasIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgFiberParasIn::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecCfgFiberParasIn::InitAfterRead()
{
}

BOOL CIecCfgFiberParasIn::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgFiberParasIn *p = (CIecCfgFiberParasIn*)pObj;

	return TRUE;
}

BOOL CIecCfgFiberParasIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgFiberParasIn *p = (CIecCfgFiberParasIn*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgFiberParasIn::Clone()
{
	CIecCfgFiberParasIn *p = new CIecCfgFiberParasIn();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgFiberParasIn::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgFiberParasIn *p = new CIecCfgFiberParasIn();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecCfgFiberParasIn::CanPaste(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGFIBERPARA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgFiberParasIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgFiberParaKey)
	{
		pNew = new CIecCfgFiberPara();
	}

	return pNew;
}

CExBaseObject* CIecCfgFiberParasIn::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGFIBERPARA)
	{
		pNew = new CIecCfgFiberPara();
	}

	return pNew;
}

void CIecCfgFiberParasIn::InitCommon(long nLC_Num,long nST_Num)
{
// 	CString strID;
// 	CIecCfgFiberPara *pFiberPara = NULL;
// 	int nIndex = 0;
//
// 	for (nIndex = 0;nIndex<nLC_Num;nIndex++)
// 	{
// 		strID.Format(_T("LC%d"),nIndex+1);
// 		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);
// 
// 		if (pFiberPara == NULL)
// 		{
// 			pFiberPara = new CIecCfgFiberPara;
// 			pFiberPara->m_strID = strID;
// 			pFiberPara->m_strName = strID;
// 			AddNewChild(pFiberPara);
// 		}
// 	}
// 
// 	for (nIndex = nLC_Num;nIndex<m_nCount;nIndex++)
// 	{
// 		strID.Format(_T("LC%d"),nIndex+1);
// 		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);
// 
// 		if (pFiberPara != NULL)
// 		{
// 			Delete(pFiberPara);
// 		}
// 	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	for (nIndex = 0;nIndex<nST_Num;nIndex++)
// 	{
// 		strID.Format(_T("ST%d"),nIndex+1);
// 		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);
// 
// 		if (pFiberPara == NULL)
// 		{
// 			pFiberPara = new CIecCfgFiberPara;
// 			pFiberPara->m_strID = strID;
// 			pFiberPara->m_strName = strID;
// 			AddNewChild(pFiberPara);
// 		}
// 	}
// 
// 	for (nIndex = nST_Num;nIndex<m_nCount;nIndex++)
// 	{
// 		strID.Format(_T("ST%d"),nIndex+1);
// 		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);
// 
// 		if (pFiberPara != NULL)
// 		{
// 			Delete(pFiberPara);
// 		}
// 	}
}
