//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvAppearForErr.cpp  CDsvAppearForErr


#include "stdafx.h"
#include "DsvAppearForErr.h"

#include "DsvElement.h"
#include "DsvSequence.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvAppearForErr::CDsvAppearForErr()
{
	//初始化属性

	//初始化成员变量
}

CDsvAppearForErr::~CDsvAppearForErr()
{
}

long CDsvAppearForErr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvSequence::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvAppearForErr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvSequence::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvAppearForErr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDsvAppearForErr::InitAfterRead()
{
}

BOOL CDsvAppearForErr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDsvSequence::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvAppearForErr *p = (CDsvAppearForErr*)pObj;

	return TRUE;
}

BOOL CDsvAppearForErr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvSequence::CopyOwn(pDest);

	CDsvAppearForErr *p = (CDsvAppearForErr*)pDest;

	return TRUE;
}

CBaseObject* CDsvAppearForErr::Clone()
{
	CDsvAppearForErr *p = new CDsvAppearForErr();
	Copy(p);
	return p;
}

BOOL CDsvAppearForErr::CanPaste(UINT nClassID)
{
	return CDsvSequence::CanPaste(nClassID);
}

// CExBaseObject* CDsvAppearForErr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	return CDsvSequence::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);;
// }
// 
// CExBaseObject* CDsvAppearForErr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	return CDsvSequence::CreateNewChild(nClassID);
// }

BOOL CDsvAppearForErr::DsValidate(CDvmDataset *pDataset, CValues *pRptValues, CExBaseList &listAppearForError)
{
	POS pos = pDataset->GetHeadPosition();
	BOOL bTrue = TRUE;
	CDvmData *pData = NULL;
	POS posDsv = NULL;
	CDsvBase *pDsv = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		posDsv = GetHeadPosition();

		while (posDsv != NULL)
		{
			pDsv = (CDsvBase *)GetNext(posDsv);

			if (pDsv->GetClassID() != DVMCLASSID_CDSVELEMENT)
			{
				continue;
			}

			if ( ((CDsvElement *)pDsv)->ValidateData(pData, pRptValues) )
			{
				bTrue = FALSE;
				listAppearForError.AddTail(pData);
				break;
			}
		}
	}

	return bTrue;
}
