//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgOs.cpp  CTcpEdgePkgOs


#include "stdafx.h"
#include "TcpEdgePkgOs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgOs::CTcpEdgePkgOs()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgOs::~CTcpEdgePkgOs()
{

}

BOOL CTcpEdgePkgOs::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
			PkgData_Node_OS).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%1：[%2]=>[%3$%4]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_OS).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgOs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	//lmy,20230919修改,从构造类中移到这里
	m_arrayNotMust[0] = PkgData_Node_PathVersion;
	m_arrayNotMust[1] = PkgData_Node_PatchVersion;

	xml_GetAttibuteValue(pXmlKeys->m_strDistroKey, oNode, m_strDistro);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strKernelKey, oNode, m_strKernel);
	xml_GetAttibuteValue(pXmlKeys->m_strSoftVersionKey, oNode, m_strSoftVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strPatchVersionKey, oNode, m_strPatchVersion);
	return 0;
}

long CTcpEdgePkgOs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDistroKey, oElement, m_strDistro);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strKernelKey, oElement, m_strKernel);
	xml_SetAttributeValue(pXmlKeys->m_strSoftVersionKey, oElement, m_strSoftVersion);
	xml_SetAttributeValue(pXmlKeys->m_strPatchVersionKey, oElement, m_strPatchVersion);
	return 0;
}

long CTcpEdgePkgOs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDistro);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strKernel);
		BinarySerializeCalLen(oBinaryBuffer, m_strSoftVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strPatchVersion);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDistro);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strKernel);
		BinarySerializeRead(oBinaryBuffer, m_strSoftVersion);
		BinarySerializeRead(oBinaryBuffer, m_strPatchVersion);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDistro);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strKernel);
		BinarySerializeWrite(oBinaryBuffer, m_strSoftVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strPatchVersion);
	}
	return 0;
}

void CTcpEdgePkgOs::InitAfterRead()
{
}

BOOL CTcpEdgePkgOs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgOs *p = (CTcpEdgePkgOs*)pObj;

	if(m_strDistro != p->m_strDistro)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strKernel != p->m_strKernel)
	{
		return FALSE;
	}

	if(m_strSoftVersion != p->m_strSoftVersion)
	{
		return FALSE;
	}

	if(m_strPatchVersion != p->m_strPatchVersion)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgOs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgOs *p = (CTcpEdgePkgOs*)pDest;

	p->m_strDistro = m_strDistro;
	p->m_strVersion = m_strVersion;
	p->m_strKernel = m_strKernel;
	p->m_strSoftVersion = m_strSoftVersion;
	p->m_strPatchVersion = m_strPatchVersion;
	return TRUE;
}

CBaseObject* CTcpEdgePkgOs::Clone()
{
	CTcpEdgePkgOs *p = new CTcpEdgePkgOs();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgOs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgOs *p = new CTcpEdgePkgOs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgOs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgOs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgOs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgOs::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDistroKey, m_strDistro);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strKernelKey, m_strKernel);
	pRecordset->GetFieldValue(pXmlKeys->m_strSoftVersionKey, m_strSoftVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strPatchVersionKey, m_strPatchVersion);
	return 0;
}

long CTcpEdgePkgOs::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDistroKey, m_strDistro);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strKernelKey, m_strKernel);
	pRecordset->SetFieldValue(pXmlKeys->m_strSoftVersionKey, m_strSoftVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strPatchVersionKey, m_strPatchVersion);
	return 0;
}

