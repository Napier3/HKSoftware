//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeAuth.cpp  CEdgeAuth


#include "stdafx.h"
#include "EdgeAuth.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeAuth::CEdgeAuth()
{
	//初始化属性
	m_nIndex_Auth = 0;
	m_nIndex_Device = 0;
	m_nType = 0;

	//初始化成员变量
}

CEdgeAuth::~CEdgeAuth()
{
}

long CEdgeAuth::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexAuthKey, oNode, m_nIndex_Auth);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexDeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strModelKey, oNode, m_strModel);
	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetAttibuteValue(pXmlKeys->m_strAuthKey, oNode, m_strAuth);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_nType);
	return 0;
}

long CEdgeAuth::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexAuthKey, oElement, m_nIndex_Auth);
	xml_SetAttributeValue(pXmlKeys->m_strIndexDeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strModelKey, oElement, m_strModel);
	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_strSn);
	xml_SetAttributeValue(pXmlKeys->m_strAuthKey, oElement, m_strAuth);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_nType);
	return 0;
}

long CEdgeAuth::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Auth);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strAuth);
		BinarySerializeCalLen(oBinaryBuffer, m_nType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Auth);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_strModel);
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_strAuth);
		BinarySerializeRead(oBinaryBuffer, m_nType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Auth);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_strModel);
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_strAuth);
		BinarySerializeWrite(oBinaryBuffer, m_nType);
	}
	return 0;
}

void CEdgeAuth::InitAfterRead()
{
	m_strID = GetXmlElementKey();
}

BOOL CEdgeAuth::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeAuth *p = (CEdgeAuth*)pObj;

	if(m_nIndex_Auth != p->m_nIndex_Auth)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_strModel != p->m_strModel)
	{
		return FALSE;
	}

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_strAuth != p->m_strAuth)
	{
		return FALSE;
	}

	if(m_nType != p->m_nType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeAuth::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeAuth *p = (CEdgeAuth*)pDest;

	p->m_nIndex_Auth = m_nIndex_Auth;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_strModel = m_strModel;
	p->m_strSn = m_strSn;
	p->m_strAuth = m_strAuth;
	p->m_nType = m_nType;
	return TRUE;
}

CBaseObject* CEdgeAuth::Clone()
{
	CEdgeAuth *p = new CEdgeAuth();
	Copy(p);
	return p;
}

CBaseObject* CEdgeAuth::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeAuth *p = new CEdgeAuth();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeAuth::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeAuth::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeAuth::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

long CEdgeAuth::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndexAuthKey, m_nIndex_Auth);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndexDeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strModelKey, m_strModel);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strAuthKey, m_strAuth);
	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_nType);
	return 0;
}

long CEdgeAuth::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndexAuthKey, m_nIndex_Auth);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndexDeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strModelKey, m_strModel);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strAuthKey, m_strAuth);
	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_nType);
	return 0;
}

CString CEdgeAuth::CurTimeToString()
{
	CString strTime;
	GetCurrSystemtimeString(strTime);
	strTime.Replace(_T("-"), _T(""));
	strTime.Replace(_T(" "), _T(""));
	strTime.Replace(_T(":"), _T(""));
	CString strRand;
	strRand.Format("%d", rand());
	return strTime + strRand;
}

CString CEdgeAuth::QuenryEdgeMappingID(const CString& strSN, const CString& strModule, CXDbBaseLib *pXDbLib, CXmlRWKeys* pXmlKeys)
{
	CString strTable,strSql;
	strTable = CEdgeCmdMngrXmlRWKeys::CEdge_AuthKey();
	strSql.Format(_T("select * from %s where (sn=\"%s\" and model=\"%s\" and type=0 ) limit 1"), strTable, strSN, strModule);
	BOOL nRes = DB_Select_OwnEx(pXDbLib, pXmlKeys, strSql);

// 	if(nRes == NULL)
// 	{
// 		return _T("");
// 	}

	if(nRes == NULL)
	{
		CXDb_PKeyValue oPKeyValue;
		m_nType = 0;
		m_strSn = strSN;
		m_strModel = strModule;
		m_strAuth = m_strModel + CurTimeToString();
		//数据库表不存在数据
		DB_Insert(pXDbLib, pXmlKeys);
	}
	return m_strAuth;
}

CString CEdgeAuth::QuenryTopoMappingID(const CString& strSN, const CString& strModule, CXDbBaseLib *pXDbLib, CXmlRWKeys* pXmlKeys)
{
	CString strTable,strSql;
	strTable = CEdgeCmdMngrXmlRWKeys::CEdge_AuthKey();
	strSql.Format(_T("select * from %s where (sn=\"%s\" and model=\"%s\" and type=1 ) limit 1"), strTable, strSN, strModule);
	BOOL nRes = DB_Select_OwnEx(pXDbLib, pXmlKeys, strSql);

// 	if(nRes == NULL)
// 	{
// 		return _T("");
// 	}	

	if(nRes == NULL)
	{
		CXDb_PKeyValue oPKeyValue;
		m_nType = 1;
		m_strSn = strSN;
		m_strModel = strModule;
		m_strAuth = m_strModel + CurTimeToString();
		//数据库表不存在数据
		DB_Insert(pXDbLib, pXmlKeys);
	}
	return m_strAuth;
}