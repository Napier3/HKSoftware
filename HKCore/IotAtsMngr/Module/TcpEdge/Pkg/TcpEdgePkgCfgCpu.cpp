//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgCfgCpu.cpp  CTcpEdgePkgCfgCpu


#include "stdafx.h"
#include "TcpEdgePkgCfgCpu.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgCfgCpu::CTcpEdgePkgCfgCpu()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgCfgCpu::~CTcpEdgePkgCfgCpu()
{
}

BOOL CTcpEdgePkgCfgCpu::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】%1：[%2]=>[%3$%4$%5]必需字段缺失;\n").arg(m_strID).arg(PkgData_Node_Data).arg(m_strName).arg(PkgData_Node_CfgCpu).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%1：[%2]=>[%3$%4$%5]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(m_strName).arg(PkgData_Node_CfgCpu).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgCfgCpu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCpusKey, oNode, m_strCpus);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_strCpuLmt);

	m_strErrorInfo += CheckRangePer(_T(""), PkgData_Node_CfgCpu, PkgData_Node_CpuLmt, m_strCpuLmt);
	m_strRangeOut += CheckRangePer(_T(""), PkgData_Node_CfgCpu, PkgData_Node_CpuLmt, m_strCpuLmt);

	return 0;
}

long CTcpEdgePkgCfgCpu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCpusKey, oElement, m_strCpus);
	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_strCpuLmt);
	return 0;
}

long CTcpEdgePkgCfgCpu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCpus);
		BinarySerializeCalLen(oBinaryBuffer, m_strCpuLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCpus);
		BinarySerializeRead(oBinaryBuffer, m_strCpuLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCpus);
		BinarySerializeWrite(oBinaryBuffer, m_strCpuLmt);
	}
	return 0;
}

void CTcpEdgePkgCfgCpu::InitAfterRead()
{
}

BOOL CTcpEdgePkgCfgCpu::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgCfgCpu *p = (CTcpEdgePkgCfgCpu*)pObj;

	if(m_strCpus != p->m_strCpus)
	{
		return FALSE;
	}

	if(m_strCpuLmt != p->m_strCpuLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgCfgCpu::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgCfgCpu *p = (CTcpEdgePkgCfgCpu*)pDest;

	p->m_strCpus = m_strCpus;
	p->m_strCpuLmt = m_strCpuLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgCfgCpu::Clone()
{
	CTcpEdgePkgCfgCpu *p = new CTcpEdgePkgCfgCpu();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgCfgCpu::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgCfgCpu *p = new CTcpEdgePkgCfgCpu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgCfgCpu::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgCfgCpu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgCfgCpu::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgCfgCpu::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCpusKey, m_strCpus);
	pRecordset->GetFieldValue(pXmlKeys->m_strCpuLmtKey, m_strCpuLmt);
	return 0;
}

long CTcpEdgePkgCfgCpu::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCpusKey, m_strCpus);
	pRecordset->SetFieldValue(pXmlKeys->m_strCpuLmtKey, m_strCpuLmt);
	return 0;
}

CDvmDataset* CTcpEdgePkgCfgCpu::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_CfgCpu;
	pDataset->m_strDataType = PkgData_Type_Object;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Cpus);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CpuLmt);

	return pDataset;
}