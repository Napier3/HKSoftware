//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetDataSubs_SubSvcs.cpp  CPkg_GetDataSubs_SubSvcs


#include "stdafx.h"
#include "Pkg_GetDataSubs_SubSvcs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CPkg_GetDataSubs_SubSvcs::CPkg_GetDataSubs_SubSvcs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetDataSubs_SubSvcs::~CPkg_GetDataSubs_SubSvcs()
{
}

long CPkg_GetDataSubs_SubSvcs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubs_SubSvcs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubs_SubSvcs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
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

void CPkg_GetDataSubs_SubSvcs::InitAfterRead()
{
}

BOOL CPkg_GetDataSubs_SubSvcs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubs_SubSvcs *p = (CPkg_GetDataSubs_SubSvcs*)pObj;

	return TRUE;
}

BOOL CPkg_GetDataSubs_SubSvcs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubs_SubSvcs *p = (CPkg_GetDataSubs_SubSvcs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_GetDataSubs_SubSvcs::Clone()
{
	CPkg_GetDataSubs_SubSvcs *p = new CPkg_GetDataSubs_SubSvcs();
	Copy(p);
	return p;
}

CBaseObject* CPkg_GetDataSubs_SubSvcs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_GetDataSubs_SubSvcs *p = new CPkg_GetDataSubs_SubSvcs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_GetDataSubs_SubSvcs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubs_SubSvcs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubs_SubSvcs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup* CPkg_GetDataSubs_SubSvcs::ToDataset()
{
	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
	pDatasetArray->m_strDataType = PkgData_Type_Array;
	pDatasetArray->m_strID = PkgData_Node_Services;
	pDatasetArray->m_dwItemData = 1;
	//20230920，lmy添加
	pDatasetArray->m_dwReserved = 1;

	return pDatasetArray;
}