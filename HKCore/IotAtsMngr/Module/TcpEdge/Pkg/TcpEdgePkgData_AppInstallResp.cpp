//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppInstallResp.cpp  CTcpEdgePkgData_AppInstallResp


#include "stdafx.h"
#include "TcpEdgePkgData_AppInstallResp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppInstallResp::CTcpEdgePkgData_AppInstallResp()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_AppInstallResp::~CTcpEdgePkgData_AppInstallResp()
{
}

BOOL CTcpEdgePkgData_AppInstallResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】AppInstallResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】AppInstallResp：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_AppInstallResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJobIdKey, oNode, m_strJobId);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	return 0;
}

long CTcpEdgePkgData_AppInstallResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJobIdKey, oElement, m_strJobId);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	return 0;
}

long CTcpEdgePkgData_AppInstallResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJobId);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJobId);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJobId);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
	}
	return 0;
}

void CTcpEdgePkgData_AppInstallResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppInstallResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppInstallResp *p = (CTcpEdgePkgData_AppInstallResp*)pObj;

	if(m_strJobId != p->m_strJobId)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	if(m_strErrorCode != p->m_strErrorCode)
	{
		return FALSE;
	}

	if(m_strNote != p->m_strNote)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppInstallResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppInstallResp *p = (CTcpEdgePkgData_AppInstallResp*)pDest;

	p->m_strJobId = m_strJobId;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppInstallResp::Clone()
{
	CTcpEdgePkgData_AppInstallResp *p = new CTcpEdgePkgData_AppInstallResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppInstallResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppInstallResp *p = new CTcpEdgePkgData_AppInstallResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppInstallResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppInstallResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppInstallResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppInstallResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

long CTcpEdgePkgData_AppInstallResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

