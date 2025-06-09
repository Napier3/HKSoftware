//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppInstallStatusResp.cpp  CTcpEdgePkgData_AppInstallStatusResp


#include "stdafx.h"
#include "TcpEdgePkgData_AppInstallStatusResp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppInstallStatusResp::CTcpEdgePkgData_AppInstallStatusResp()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_AppInstallStatusResp::~CTcpEdgePkgData_AppInstallStatusResp()
{
}

BOOL CTcpEdgePkgData_AppInstallStatusResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】AppInstallStatusResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】AppInstallStatusResp：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_AppInstallStatusResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJobIdKey, oNode, m_strJobId);
	xml_GetAttibuteValue(pXmlKeys->m_strProgressKey, oNode, m_strProgress);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_strState);

	m_strErrorInfo += CheckRangePer(_T("AppInstallStatusResp"), PkgData_Node_Progress, m_strProgress);
	m_strRangeOut += CheckRangePer(_T("AppInstallStatusResp"), PkgData_Node_Progress, m_strProgress);

	//lmy,20230918修改
	/*if(m_strState != _T("0") || m_strState != _T("1")|| m_strState != _T("2") || m_strState != _T("3")
		|| m_strState != _T("4") || m_strState != _T("5"))*/
	if(m_strState != _T("0") && m_strState != _T("1") && m_strState != _T("2") && m_strState != _T("3")
		&& m_strState != _T("4") && m_strState != _T("5"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】AppInstallStatusResp: [Data]=>[State]字段超出范围, 无法判断当前应用安装执行状态;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_AppInstallStatusResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJobIdKey, oElement, m_strJobId);
	xml_SetAttributeValue(pXmlKeys->m_strProgressKey, oElement, m_strProgress);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_strState);
	return 0;
}

long CTcpEdgePkgData_AppInstallStatusResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJobId);
		BinarySerializeCalLen(oBinaryBuffer, m_strProgress);
		BinarySerializeCalLen(oBinaryBuffer, m_strState);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJobId);
		BinarySerializeRead(oBinaryBuffer, m_strProgress);
		BinarySerializeRead(oBinaryBuffer, m_strState);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJobId);
		BinarySerializeWrite(oBinaryBuffer, m_strProgress);
		BinarySerializeWrite(oBinaryBuffer, m_strState);
	}
	return 0;
}

void CTcpEdgePkgData_AppInstallStatusResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppInstallStatusResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppInstallStatusResp *p = (CTcpEdgePkgData_AppInstallStatusResp*)pObj;

	if(m_strJobId != p->m_strJobId)
	{
		return FALSE;
	}

	if(m_strProgress != p->m_strProgress)
	{
		return FALSE;
	}

	if(m_strState != p->m_strState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppInstallStatusResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppInstallStatusResp *p = (CTcpEdgePkgData_AppInstallStatusResp*)pDest;

	p->m_strJobId = m_strJobId;
	p->m_strProgress = m_strProgress;
	p->m_strState = m_strState;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppInstallStatusResp::Clone()
{
	CTcpEdgePkgData_AppInstallStatusResp *p = new CTcpEdgePkgData_AppInstallStatusResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppInstallStatusResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppInstallStatusResp *p = new CTcpEdgePkgData_AppInstallStatusResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppInstallStatusResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppInstallStatusResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppInstallStatusResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppInstallStatusResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->GetFieldValue(pXmlKeys->m_strProgressKey, m_strProgress);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_strState);
	return 0;
}

long CTcpEdgePkgData_AppInstallStatusResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->SetFieldValue(pXmlKeys->m_strProgressKey, m_strProgress);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_strState);
	return 0;
}

