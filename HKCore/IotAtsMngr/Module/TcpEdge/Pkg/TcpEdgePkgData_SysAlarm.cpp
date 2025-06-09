//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_SysAlarm.cpp  CTcpEdgePkgData_SysAlarm


#include "stdafx.h"
#include "TcpEdgePkgData_SysAlarm.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_SysAlarm::CTcpEdgePkgData_SysAlarm()
{
	//��ʼ������

	//��ʼ����Ա����
	m_arrayNotMust[0] = PkgData_Node_Msg;

}

CTcpEdgePkgData_SysAlarm::~CTcpEdgePkgData_SysAlarm()
{
}

BOOL CTcpEdgePkgData_SysAlarm::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//�������жϱ����е�String�ֶ��Ƿ�����
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//ֵ������ʱ����Ƿ����
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("�����󡿡�������ȱʧ��SysAlarm��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������SysAlarm��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_SysAlarm::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strEventKey, oNode, m_strEvent);
	xml_GetAttibuteValue(pXmlKeys->m_strMsgKey, oNode, m_strMsg);

	//lmy,20230918�޸�
	/*if(m_strEvent != _T("1001") || m_strEvent != _T("1002") ||  m_strEvent != _T("1003") || m_strEvent != _T("1004") 
		|| m_strEvent != _T("1005") || m_strEvent != _T("2001") || m_strEvent != _T("2002") || m_strEvent != _T("2003")
		|| m_strEvent != _T("3004"))*/
	if(m_strEvent != _T("1001") && m_strEvent != _T("1002") && m_strEvent != _T("1003") && m_strEvent != _T("1004") 
		&& m_strEvent != _T("1005") && m_strEvent != _T("2001") && m_strEvent != _T("2002") && m_strEvent != _T("2003")
		&& m_strEvent != _T("3004"))
	{
		QString strTemp;
		strTemp = QString(_T("�����󡿡�������Χ��SysAlarm: [Data]=>[Event]�ֶγ�����Χ;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;

	}

	if(m_strMsg.GetLength()>256)
	{
		QString strTemp;
		strTemp = QString(_T("�����󡿡�������Χ��SysAlarm: [Data]=>[Msg]�ֶγ�����Χ;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_SysAlarm::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strEventKey, oElement, m_strEvent);
	xml_SetAttributeValue(pXmlKeys->m_strMsgKey, oElement, m_strMsg);
	return 0;
}

long CTcpEdgePkgData_SysAlarm::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strEvent);
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strEvent);
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strEvent);
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
	}
	return 0;
}

void CTcpEdgePkgData_SysAlarm::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_SysAlarm::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_SysAlarm *p = (CTcpEdgePkgData_SysAlarm*)pObj;

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

BOOL CTcpEdgePkgData_SysAlarm::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_SysAlarm *p = (CTcpEdgePkgData_SysAlarm*)pDest;

	p->m_strEvent = m_strEvent;
	p->m_strMsg = m_strMsg;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_SysAlarm::Clone()
{
	CTcpEdgePkgData_SysAlarm *p = new CTcpEdgePkgData_SysAlarm();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_SysAlarm::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_SysAlarm *p = new CTcpEdgePkgData_SysAlarm();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_SysAlarm::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_SysAlarm::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_SysAlarm::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_SysAlarm::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->GetFieldValue(pXmlKeys->m_strMsgKey, m_strMsg);
	return 0;
}

long CTcpEdgePkgData_SysAlarm::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->SetFieldValue(pXmlKeys->m_strMsgKey, m_strMsg);
	return 0;
}

