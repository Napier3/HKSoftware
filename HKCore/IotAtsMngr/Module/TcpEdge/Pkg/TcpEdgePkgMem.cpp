//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgMem.cpp  CTcpEdgePkgMem


#include "stdafx.h"
#include "TcpEdgePkgMem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgMem::CTcpEdgePkgMem()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Virt;
	m_arrayNotMust[1] = PkgData_Node_MemLmt;

}

CTcpEdgePkgMem::~CTcpEdgePkgMem()
{
}

BOOL CTcpEdgePkgMem::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】%1：[%2]=>[%3$%4]必需字段缺失;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Mem).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%1：[%2]=>[%3$%4]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Mem).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgMem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPhyKey, oNode, m_strPhy);
	xml_GetAttibuteValue(pXmlKeys->m_strVirtKey, oNode, m_strVirt);
	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_strMemLmt);

	m_strErrorInfo += CheckRangePer(_T(""), PkgData_Node_Mem, PkgData_Node_MemLmt, m_strMemLmt);
	m_strRangeOut += CheckRangePer(_T(""), PkgData_Node_Mem, PkgData_Node_MemLmt, m_strMemLmt);


	return 0;
}

long CTcpEdgePkgMem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPhyKey, oElement, m_strPhy);
	xml_SetAttributeValue(pXmlKeys->m_strVirtKey, oElement, m_strVirt);
	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_strMemLmt);
	return 0;
}

long CTcpEdgePkgMem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPhy);
		BinarySerializeCalLen(oBinaryBuffer, m_strVirt);
		BinarySerializeCalLen(oBinaryBuffer, m_strMemLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPhy);
		BinarySerializeRead(oBinaryBuffer, m_strVirt);
		BinarySerializeRead(oBinaryBuffer, m_strMemLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPhy);
		BinarySerializeWrite(oBinaryBuffer, m_strVirt);
		BinarySerializeWrite(oBinaryBuffer, m_strMemLmt);
	}
	return 0;
}

void CTcpEdgePkgMem::InitAfterRead()
{
}

BOOL CTcpEdgePkgMem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgMem *p = (CTcpEdgePkgMem*)pObj;

	if(m_strPhy != p->m_strPhy)
	{
		return FALSE;
	}

	if(m_strVirt != p->m_strVirt)
	{
		return FALSE;
	}

	if(m_strMemLmt != p->m_strMemLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgMem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgMem *p = (CTcpEdgePkgMem*)pDest;

	p->m_strPhy = m_strPhy;
	p->m_strVirt = m_strVirt;
	p->m_strMemLmt = m_strMemLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgMem::Clone()
{
	CTcpEdgePkgMem *p = new CTcpEdgePkgMem();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgMem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgMem *p = new CTcpEdgePkgMem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgMem::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgMem::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgMem::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgMem::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strPhyKey, m_strPhy);
	pRecordset->GetFieldValue(pXmlKeys->m_strVirtKey, m_strVirt);
	pRecordset->GetFieldValue(pXmlKeys->m_strMemLmtKey, m_strMemLmt);
	return 0;
}

long CTcpEdgePkgMem::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strPhyKey, m_strPhy);
	pRecordset->SetFieldValue(pXmlKeys->m_strVirtKey, m_strVirt);
	pRecordset->SetFieldValue(pXmlKeys->m_strMemLmtKey, m_strMemLmt);
	return 0;
}

