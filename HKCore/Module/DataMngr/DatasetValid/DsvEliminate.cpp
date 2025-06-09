//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvEliminate.cpp  CDsvEliminate


#include "stdafx.h"
#include "DsvEliminate.h"

#include "DsvElement.h"
#include "DsvSequence.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvEliminate::CDsvEliminate()
{
	//初始化属性

	//初始化成员变量
}

CDsvEliminate::~CDsvEliminate()
{
}

long CDsvEliminate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvEliminate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvEliminate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDvmDataset::SerializeOwn(oBinaryBuffer);
	
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

void CDsvEliminate::InitAfterRead()
{
}

BOOL CDsvEliminate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDvmDataset::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvEliminate *p = (CDsvEliminate*)pObj;

	return TRUE;
}

BOOL CDsvEliminate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataset::CopyOwn(pDest);

	CDsvEliminate *p = (CDsvEliminate*)pDest;

	return TRUE;
}

CBaseObject* CDsvEliminate::Clone()
{
	CDsvEliminate *p = new CDsvEliminate();
	Copy(p);
	return p;
}

BOOL CDsvEliminate::CanPaste(UINT nClassID)
{
	return CDvmDataset::CanPaste(nClassID);
}

CExBaseObject* CDsvEliminate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CDvmDataset::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);;
}

CExBaseObject* CDsvEliminate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return CDvmDataset::CreateNewChild(nClassID);
}
