//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvInDataset.cpp  CDsvInDataset


#include "stdafx.h"
#include "DsvInDataset.h"

#include "DsvElement.h"
#include "DsvChoice.h"


CDsvInDataset::CDsvInDataset()
{
	//初始化属性

	//初始化成员变量
}

CDsvInDataset::~CDsvInDataset()
{
}

long CDsvInDataset::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvBase::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvInDataset::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvInDataset::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDsvBase::SerializeOwn(oBinaryBuffer);
		
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

void CDsvInDataset::InitAfterRead()
{
}

BOOL CDsvInDataset::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDsvBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvInDataset *p = (CDsvInDataset*)pObj;

	return TRUE;
}

BOOL CDsvInDataset::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvBase::CopyOwn(pDest);

	CDsvInDataset *p = (CDsvInDataset*)pDest;

	return TRUE;
}

CBaseObject* CDsvInDataset::Clone()
{
	CDsvInDataset *p = new CDsvInDataset();
	Copy(p);
	return p;
}

BOOL CDsvInDataset::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDSVELEMENT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDsvInDataset::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDsvElementKey)
	{
		pNew = new CDsvElement();
	}

	return pNew;
}

CExBaseObject* CDsvInDataset::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDSVELEMENT)
	{
		pNew = new CDsvElement();
	}
	
	return pNew;
}

// CDsvElement* CDsvInDataset::AddElement(const CString &strText, long nOption, long nUnbound)
// {
// 	CDsvElement *pNew = new CDsvElement();
// 
// 	pNew->m_strText = strText;
// 	pNew->m_nMinOcc = nOption;
// 	pNew->m_nMaxOcc = nUnbound;
// 	AddNewChild(pNew);
// 	
// 	return pNew;
// }
// 
// BOOL CDsvInDataset::DsValidate(CDvmDataset *pDataset, POS &posDataset, CDsvBase *pPrevAnlyDsvObj)
// {
// 	if (posDataset == NULL)
// 	{
// 		if (m_nMinOcc == 0)
// 		{
// 			return TRUE;
// 		}
// 
// 		return FALSE;
// 	}
// 
// 	POS posDsv = GetHeadPosition();
// 	CDsvBase *pDsv = NULL;
// 	BOOL bTrue = TRUE;
// 	POS posBack = posDataset;
// 
// 	while (posDsv != NULL)
// 	{
// 		pDsv = (CDsvBase *)GetNext(posDsv);
// 
// 		if (!pDsv->DsValidate(pDataset, posDataset))
// 		{
// 			bTrue = FALSE;
// 			posDataset = posBack;
// 			break;
// 		}
// 	}
// 
// 	return bTrue;
// }
// 
// 
// BOOL CDsvInDataset::DsValidate(CDvmDataset *pDataset, BOOL bValidateHead)
// {
// 	POS pos = pDataset->GetHeadPosition();
// 	BOOL bTrue = TRUE;
// 
// 	if (bValidateHead)
// 	{
// 		bTrue = DsValidate(pDataset, pos);
// 	}
// 	else
// 	{
// 		while (pos != NULL)
// 		{
// 			bTrue = DsValidate(pDataset, pos);
// 
// 			if (bTrue)
// 			{
// 				break;
// 			}
// 
// 			pDataset->GetNext(pos);
// 		}
// 	}
// 
// 	return bTrue;
// }
// 
