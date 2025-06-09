//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataReadDevs.cpp  CPkg_DataReadDevs


#include "stdafx.h"
#include "Pkg_DataReadDevs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_DataReadDevs::CPkg_DataReadDevs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataReadDevs::~CPkg_DataReadDevs()
{
}

long CPkg_DataReadDevs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataReadDevs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataReadDevs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DataReadDevs::InitAfterRead()
{
}

BOOL CPkg_DataReadDevs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataReadDevs *p = (CPkg_DataReadDevs*)pObj;

	return TRUE;
}

BOOL CPkg_DataReadDevs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataReadDevs *p = (CPkg_DataReadDevs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DataReadDevs::Clone()
{
	CPkg_DataReadDevs *p = new CPkg_DataReadDevs();
	Copy(p);
	return p;
}

CBaseObject* CPkg_DataReadDevs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_DataReadDevs *p = new CPkg_DataReadDevs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_DataReadDevs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataReadDevs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataReadDevs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup* CPkg_DataReadDevs::ToDataset()
{
	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
	pDatasetArray->m_strDataType = PkgData_Type_Array;
	pDatasetArray->m_strID = PkgData_Node_Devices;
	pDatasetArray->m_dwItemData = 1;
	//20230920，lmy添加
	pDatasetArray->m_dwReserved = 1;

	return pDatasetArray;
}