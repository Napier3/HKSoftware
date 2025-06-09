//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgCfgMem.cpp  CTcpEdgePkgCfgMem


#include "stdafx.h"
#include "TcpEdgePkgCfgMem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgCfgMem::CTcpEdgePkgCfgMem()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgCfgMem::~CTcpEdgePkgCfgMem()
{
}

BOOL CTcpEdgePkgCfgMem::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】%1：[%2]=>[%3$%4$%5]必需字段缺失;\n").arg(m_strID).arg(PkgData_Node_Data).arg(m_strName).arg(PkgData_Node_CfgMem).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%1：[%2]=>[%3$%4$%5]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(m_strName).arg(PkgData_Node_CfgMem).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgCfgMem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMemoryKey, oNode, m_strMemory);
	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_strMemLmt);

	m_strErrorInfo += CheckRangePer(_T(""), PkgData_Node_CfgMem, PkgData_Node_MemLmt, m_strMemLmt);
	m_strRangeOut += CheckRangePer(_T(""), PkgData_Node_CfgMem, PkgData_Node_MemLmt, m_strMemLmt);

	return 0;
}

long CTcpEdgePkgCfgMem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMemoryKey, oElement, m_strMemory);
	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_strMemLmt);
	return 0;
}

long CTcpEdgePkgCfgMem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMemory);
		BinarySerializeCalLen(oBinaryBuffer, m_strMemLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMemory);
		BinarySerializeRead(oBinaryBuffer, m_strMemLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMemory);
		BinarySerializeWrite(oBinaryBuffer, m_strMemLmt);
	}
	return 0;
}

void CTcpEdgePkgCfgMem::InitAfterRead()
{
}

BOOL CTcpEdgePkgCfgMem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgCfgMem *p = (CTcpEdgePkgCfgMem*)pObj;

	if(m_strMemory != p->m_strMemory)
	{
		return FALSE;
	}

	if(m_strMemLmt != p->m_strMemLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgCfgMem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgCfgMem *p = (CTcpEdgePkgCfgMem*)pDest;

	p->m_strMemory = m_strMemory;
	p->m_strMemLmt = m_strMemLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgCfgMem::Clone()
{
	CTcpEdgePkgCfgMem *p = new CTcpEdgePkgCfgMem();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgCfgMem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgCfgMem *p = new CTcpEdgePkgCfgMem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgCfgMem::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgCfgMem::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgCfgMem::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgCfgMem::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strMemoryKey, m_strMemory);
	pRecordset->GetFieldValue(pXmlKeys->m_strMemLmtKey, m_strMemLmt);
	return 0;
}

long CTcpEdgePkgCfgMem::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strMemoryKey, m_strMemory);
	pRecordset->SetFieldValue(pXmlKeys->m_strMemLmtKey, m_strMemLmt);
	return 0;
}

CDvmDataset* CTcpEdgePkgCfgMem::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_CfgMem;
	pDataset->m_strDataType = PkgData_Type_Object;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Memory);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_MemLmt);

	return pDataset;
}
