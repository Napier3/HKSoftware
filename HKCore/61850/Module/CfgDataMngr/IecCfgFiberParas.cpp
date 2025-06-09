//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFiberParas.cpp  CIecCfgFiberParas


#include "stdafx.h"
#include "IecCfgFiberParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgFiberParas::CIecCfgFiberParas()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgFiberParas::~CIecCfgFiberParas()
{
}

long CIecCfgFiberParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgFiberParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgFiberParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecCfgFiberParas::InitAfterRead()
{
}

BOOL CIecCfgFiberParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgFiberParas *p = (CIecCfgFiberParas*)pObj;

	return TRUE;
}

BOOL CIecCfgFiberParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgFiberParas *p = (CIecCfgFiberParas*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgFiberParas::Clone()
{
	CIecCfgFiberParas *p = new CIecCfgFiberParas();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgFiberParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgFiberParas *p = new CIecCfgFiberParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecCfgFiberParas::CanPaste(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGFIBERPARA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgFiberParas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgFiberParaKey)
	{
		pNew = new CIecCfgFiberPara();
	}

	return pNew;
}

CExBaseObject* CIecCfgFiberParas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGFIBERPARA)
	{
		pNew = new CIecCfgFiberPara();
	}

	return pNew;
}

void CIecCfgFiberParas::InitCommon(long nLC_Num,long nST_Num)
{
	CString strID;
	CIecCfgFiberPara *pFiberPara = NULL;
	int nIndex = 0;

	for (nIndex = 0;nIndex<nLC_Num;nIndex++)
	{
		strID.Format(_T("LC%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);

		if (pFiberPara == NULL)
		{
			pFiberPara = new CIecCfgFiberPara;
			pFiberPara->m_strID = strID;
			pFiberPara->m_strName = strID;
			AddNewChild(pFiberPara);
		}
	}

	for (nIndex = nLC_Num;nIndex<m_nCount;nIndex++)
	{
		strID.Format(_T("LC%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);

		if (pFiberPara != NULL)
		{
			Delete(pFiberPara);
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (nIndex = 0;nIndex<nST_Num;nIndex++)
	{
		strID.Format(_T("ST%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);

		if (pFiberPara == NULL)
		{
			pFiberPara = new CIecCfgFiberPara;
			pFiberPara->m_strID = strID;
			pFiberPara->m_strName = strID;
			AddNewChild(pFiberPara);
		}
	}

	for (nIndex = nST_Num;nIndex<m_nCount;nIndex++)
	{
		strID.Format(_T("ST%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)FindByID(strID);

		if (pFiberPara != NULL)
		{
			Delete(pFiberPara);
		}
	}
}
