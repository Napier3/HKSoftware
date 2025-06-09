//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgDev.cpp  CTcpEdgePkgDev


#include "stdafx.h"
#include "TcpEdgePkgDev.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgDev::CTcpEdgePkgDev()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_HardVersion;
}

CTcpEdgePkgDev::~CTcpEdgePkgDev()
{
}

BOOL CTcpEdgePkgDev::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
			PkgData_Node_Dev).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%1：[%2]=>[%3$%4]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Dev).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDevTypeKey, oNode, m_strDevType);
	xml_GetAttibuteValue(pXmlKeys->m_strDevNameKey, oNode, m_strDevName);
	xml_GetAttibuteValue(pXmlKeys->m_strMfgInfoKey, oNode, m_strMfgInfo);
	xml_GetAttibuteValue(pXmlKeys->m_strHardVersionKey, oNode, m_strHardVersion);
	return 0;
}

long CTcpEdgePkgDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDevTypeKey, oElement, m_strDevType);
	xml_SetAttributeValue(pXmlKeys->m_strDevNameKey, oElement, m_strDevName);
	xml_SetAttributeValue(pXmlKeys->m_strMfgInfoKey, oElement, m_strMfgInfo);
	xml_SetAttributeValue(pXmlKeys->m_strHardVersionKey, oElement, m_strHardVersion);
	return 0;
}

long CTcpEdgePkgDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDevType);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevName);
		BinarySerializeCalLen(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeCalLen(oBinaryBuffer, m_strHardVersion);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDevType);
		BinarySerializeRead(oBinaryBuffer, m_strDevName);
		BinarySerializeRead(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeRead(oBinaryBuffer, m_strHardVersion);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDevType);
		BinarySerializeWrite(oBinaryBuffer, m_strDevName);
		BinarySerializeWrite(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeWrite(oBinaryBuffer, m_strHardVersion);
	}
	return 0;
}

void CTcpEdgePkgDev::InitAfterRead()
{
}

BOOL CTcpEdgePkgDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgDev *p = (CTcpEdgePkgDev*)pObj;

	if(m_strDevType != p->m_strDevType)
	{
		return FALSE;
	}

	if(m_strDevName != p->m_strDevName)
	{
		return FALSE;
	}

	if(m_strMfgInfo != p->m_strMfgInfo)
	{
		return FALSE;
	}

	if(m_strHardVersion != p->m_strHardVersion)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgDev *p = (CTcpEdgePkgDev*)pDest;

	p->m_strDevType = m_strDevType;
	p->m_strDevName = m_strDevName;
	p->m_strMfgInfo = m_strMfgInfo;
	p->m_strHardVersion = m_strHardVersion;
	return TRUE;
}

CBaseObject* CTcpEdgePkgDev::Clone()
{
	CTcpEdgePkgDev *p = new CTcpEdgePkgDev();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgDev::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgDev *p = new CTcpEdgePkgDev();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgDev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgDev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgDev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgDev::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDevTypeKey, m_strDevType);
	pRecordset->GetFieldValue(pXmlKeys->m_strDevNameKey, m_strDevName);
	pRecordset->GetFieldValue(pXmlKeys->m_strMfgInfoKey, m_strMfgInfo);
	pRecordset->GetFieldValue(pXmlKeys->m_strHardVersionKey, m_strHardVersion);
	return 0;
}

long CTcpEdgePkgDev::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDevTypeKey, m_strDevType);
	pRecordset->SetFieldValue(pXmlKeys->m_strDevNameKey, m_strDevName);
	pRecordset->SetFieldValue(pXmlKeys->m_strMfgInfoKey, m_strMfgInfo);
	pRecordset->SetFieldValue(pXmlKeys->m_strHardVersionKey, m_strHardVersion);
	return 0;
}

