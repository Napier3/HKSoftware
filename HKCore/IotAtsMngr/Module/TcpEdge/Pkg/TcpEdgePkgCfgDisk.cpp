//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgCfgDisk.cpp  CTcpEdgePkgCfgDisk


#include "stdafx.h"
#include "TcpEdgePkgCfgDisk.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgCfgDisk::CTcpEdgePkgCfgDisk()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgCfgDisk::~CTcpEdgePkgCfgDisk()
{
}

BOOL CTcpEdgePkgCfgDisk::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("【错误】【必需项缺失】%1：[%2]=>[%3$%4$%5]必需字段缺失;\n").arg(m_strID).arg(PkgData_Node_Data).arg(PkgData_Node_ContCfgs).arg(PkgData_Node_CfgDisk).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%s：[%s]=>[%s$%s$%s]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(PkgData_Node_ContCfgs).arg(PkgData_Node_CfgDisk).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgCfgDisk::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDiskKey, oNode, m_strDisk);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskLmtKey, oNode, m_strDiskLmt);

	m_strErrorInfo += CheckRangePer(_T(""), PkgData_Node_CfgDisk, PkgData_Node_DiskLmt, m_strDiskLmt);
	m_strRangeOut += CheckRangePer(_T(""), PkgData_Node_CfgDisk, PkgData_Node_DiskLmt, m_strDiskLmt);


	return 0;
}

long CTcpEdgePkgCfgDisk::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDiskKey, oElement, m_strDisk);
	xml_SetAttributeValue(pXmlKeys->m_strDiskLmtKey, oElement, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgCfgDisk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDisk);
		BinarySerializeCalLen(oBinaryBuffer, m_strDiskLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDisk);
		BinarySerializeRead(oBinaryBuffer, m_strDiskLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDisk);
		BinarySerializeWrite(oBinaryBuffer, m_strDiskLmt);
	}
	return 0;
}

void CTcpEdgePkgCfgDisk::InitAfterRead()
{
}

BOOL CTcpEdgePkgCfgDisk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgCfgDisk *p = (CTcpEdgePkgCfgDisk*)pObj;

	if(m_strDisk != p->m_strDisk)
	{
		return FALSE;
	}

	if(m_strDiskLmt != p->m_strDiskLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgCfgDisk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgCfgDisk *p = (CTcpEdgePkgCfgDisk*)pDest;

	p->m_strDisk = m_strDisk;
	p->m_strDiskLmt = m_strDiskLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgCfgDisk::Clone()
{
	CTcpEdgePkgCfgDisk *p = new CTcpEdgePkgCfgDisk();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgCfgDisk::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgCfgDisk *p = new CTcpEdgePkgCfgDisk();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgCfgDisk::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgCfgDisk::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgCfgDisk::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgCfgDisk::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDiskKey, m_strDisk);
	pRecordset->GetFieldValue(pXmlKeys->m_strDiskLmtKey, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgCfgDisk::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDiskKey, m_strDisk);
	pRecordset->SetFieldValue(pXmlKeys->m_strDiskLmtKey, m_strDiskLmt);
	return 0;
}

CDvmDataset* CTcpEdgePkgCfgDisk::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_CfgDisk;
	pDataset->m_strDataType = PkgData_Type_Object;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Disk);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DiskLmt);

	return pDataset;
}