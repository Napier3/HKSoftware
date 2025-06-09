//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppAlarm.cpp  CTcpEdgePkgData_AppAlarm


#include "stdafx.h"
#include "TcpEdgePkgData_AppAlarm.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppAlarm::CTcpEdgePkgData_AppAlarm()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Msg;
}

CTcpEdgePkgData_AppAlarm::~CTcpEdgePkgData_AppAlarm()
{
}

BOOL CTcpEdgePkgData_AppAlarm::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】AppAlarm：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】AppAlarm：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_AppAlarm::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	xml_GetAttibuteValue(pXmlKeys->m_strEventKey, oNode, m_strEvent);
	xml_GetAttibuteValue(pXmlKeys->m_strMsgKey, oNode, m_strMsg);

	//lmy,20230918修改
	//if(m_strEvent != _T("5001") || m_strEvent != _T("5002") ||  m_strEvent != _T("5003") || m_strEvent != _T("5004") 
	//	|| m_strEvent != _T("5005"))
	if(m_strEvent != _T("5001") && m_strEvent != _T("5002") &&  m_strEvent != _T("5003") && m_strEvent != _T("5004") 
		&& m_strEvent != _T("5005"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】AppAlarm: [Data]=>[Event]字段超出范围;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;

	}

	if(m_strMsg.GetLength()>256)
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】AppAlarm: [Data]=>[Msg]字段超出范围;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_AppAlarm::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	xml_SetAttributeValue(pXmlKeys->m_strEventKey, oElement, m_strEvent);
	xml_SetAttributeValue(pXmlKeys->m_strMsgKey, oElement, m_strMsg);
	return 0;
}

long CTcpEdgePkgData_AppAlarm::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strEvent);
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strApp);
		BinarySerializeRead(oBinaryBuffer, m_strEvent);
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
		BinarySerializeWrite(oBinaryBuffer, m_strEvent);
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
	}
	return 0;
}

void CTcpEdgePkgData_AppAlarm::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppAlarm::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppAlarm *p = (CTcpEdgePkgData_AppAlarm*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	if(m_strEvent != p->m_strEvent)
	{
		return FALSE;
	}

	if(m_strMsg != p->m_strMsg)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppAlarm::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppAlarm *p = (CTcpEdgePkgData_AppAlarm*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strApp = m_strApp;
	p->m_strEvent = m_strEvent;
	p->m_strMsg = m_strMsg;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppAlarm::Clone()
{
	CTcpEdgePkgData_AppAlarm *p = new CTcpEdgePkgData_AppAlarm();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppAlarm::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppAlarm *p = new CTcpEdgePkgData_AppAlarm();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppAlarm::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppAlarm::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppAlarm::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppAlarm::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	pRecordset->GetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->GetFieldValue(pXmlKeys->m_strMsgKey, m_strMsg);
	return 0;
}

long CTcpEdgePkgData_AppAlarm::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	pRecordset->SetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->SetFieldValue(pXmlKeys->m_strMsgKey, m_strMsg);
	return 0;
}

