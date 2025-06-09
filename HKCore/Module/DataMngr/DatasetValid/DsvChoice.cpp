//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvChoice.cpp  CDsvChoice


#include "stdafx.h"
#include "DsvChoice.h"

#include "DsvElement.h"
#include "DsvSequence.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvChoice::CDsvChoice()
{
	//初始化属性

	//初始化成员变量
}

CDsvChoice::~CDsvChoice()
{
}

long CDsvChoice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvSequence::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvChoice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvSequence::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvChoice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDsvSequence::SerializeOwn(oBinaryBuffer);
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

void CDsvChoice::InitAfterRead()
{
}

BOOL CDsvChoice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDsvBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvChoice *p = (CDsvChoice*)pObj;

	return TRUE;
}

BOOL CDsvChoice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvSequence::CopyOwn(pDest);

	CDsvChoice *p = (CDsvChoice*)pDest;

	return TRUE;
}

CBaseObject* CDsvChoice::Clone()
{
	CDsvChoice *p = new CDsvChoice();
	Copy(p);
	return p;
}

BOOL CDsvChoice::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDSVELEMENT)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDSVSEQUENCE)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDSVCHOICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDsvChoice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return CDsvSequence::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

// 	if (strClassID == pXmlKeys->m_strCDsvElementKey)
// 	{
// 		pNew = new CDsvElement();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCDsvAnyElementKey)
// 	{
// 		pNew = new CDsvAnyElement();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCDsvSequenceKey)
// 	{
// 		pNew = new CDsvSequence();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCDsvChoiceKey)
// 	{
// 		pNew = new CDsvChoice();
// 	}
// 
// 	return pNew;
}

CExBaseObject* CDsvChoice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	return CDsvSequence::CreateNewChild(nClassID);
}

// 
// CDsvElement* CDsvChoice::AddElement(const CString &strText, long nOption, long nUnbound)
// {
// 	CDsvElement *pNew = new CDsvElement();
// 
// 	pNew->m_strMode = strText;
// 	pNew->m_nMinOcc = nOption;
// 	pNew->m_nMaxOcc = nUnbound;
// 	AddNewChild(pNew);
// 
// 	return pNew;
// }
// 
// CDsvChoice*  CDsvChoice::AddChoice(long nOption, long nUnbound)
// {
// 	CDsvChoice *pNew = new CDsvChoice();
// 
// 	pNew->m_nMinOcc = nOption;
// 	pNew->m_nMaxOcc = nUnbound;
// 	AddNewChild(pNew);
// 
// 	return pNew;
// }
// 
// CDsvSequence* CDsvChoice::AddSequence(long nOption, long nUnbound)
// {
// 	CDsvSequence *pNew = new CDsvSequence();
// 
// 	pNew->m_nMinOcc = nOption;
// 	pNew->m_nMaxOcc = nUnbound;
// 	AddNewChild(pNew);
// 
// 	return pNew;
// }
// 
// 
BOOL CDsvChoice::DsValidate(CDvmDataset *pDataset, POS &posDataset, CValues *pRptValues, CDsvBase *pPrevAnlyDsvObj)
{
	if (posDataset == NULL)
	{
		if (m_nMinOcc == 0)
		{
			return TRUE;
		}

		return FALSE;
	}

	POS posDsv = GetHeadPosition();
	CDsvBase *pDsv = NULL;
	BOOL bTrue = FALSE;
	POS posBack = posDataset;

	while (posDsv != NULL)
	{
		pDsv = (CDsvBase *)GetNext(posDsv);
		posDataset = posBack;

		if (pDsv->DsValidate(pDataset, posDataset, pRptValues))
		{
			bTrue = TRUE;
			break;
		}
	}

	if (!bTrue)
	{
		posDataset = posBack;
	}

	return bTrue;
}

BOOL CDsvChoice::DsvQuery(CDvmDataset *pDataset, CValues *pRptValues)
{
	return FALSE;
}
