//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetDataSubs_Subs.cpp  CPkg_GetDataSubs_Subs


#include "stdafx.h"
#include "Pkg_GetDataSubs_Subs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CPkg_GetDataSubs_Subs::CPkg_GetDataSubs_Subs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetDataSubs_Subs::~CPkg_GetDataSubs_Subs()
{
}

long CPkg_GetDataSubs_Subs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubs_Subs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubs_Subs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_GetDataSubs_Subs::InitAfterRead()
{
}

BOOL CPkg_GetDataSubs_Subs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubs_Subs *p = (CPkg_GetDataSubs_Subs*)pObj;

	return TRUE;
}

BOOL CPkg_GetDataSubs_Subs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubs_Subs *p = (CPkg_GetDataSubs_Subs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_GetDataSubs_Subs::Clone()
{
	CPkg_GetDataSubs_Subs *p = new CPkg_GetDataSubs_Subs();
	Copy(p);
	return p;
}

CBaseObject* CPkg_GetDataSubs_Subs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_GetDataSubs_Subs *p = new CPkg_GetDataSubs_Subs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_GetDataSubs_Subs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubs_Subs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubs_Subs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup* CPkg_GetDataSubs_Subs::ToDataset()
{
	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
	pDatasetArray->m_strDataType = PkgData_Type_Array;
	pDatasetArray->m_strID = PkgData_Node_Subs;
	pDatasetArray->m_dwItemData = 1;

	//20230920，lmy添加
	pDatasetArray->m_dwReserved = 1;

	return pDatasetArray;
}