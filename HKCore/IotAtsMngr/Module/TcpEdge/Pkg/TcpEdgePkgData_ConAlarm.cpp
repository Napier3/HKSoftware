//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_ConAlarm.cpp  CTcpEdgePkgData_ConAlarm


#include "stdafx.h"
#include "TcpEdgePkgData_ConAlarm.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_ConAlarm::CTcpEdgePkgData_ConAlarm()
{
	//��ʼ������

	//��ʼ����Ա����
	m_arrayNotMust[0] = PkgData_Node_Msg;
}

CTcpEdgePkgData_ConAlarm::~CTcpEdgePkgData_ConAlarm()
{
}

BOOL CTcpEdgePkgData_ConAlarm::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("�����󡿡�������ȱʧ��ConAlarm��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������ConAlarm��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_ConAlarm::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strEventKey, oNode, m_strEvent);
	xml_GetAttibuteValue(pXmlKeys->m_strMsgKey, oNode, m_strMsg);

	//lmy,20230918�޸�
	//if(m_strEvent != _T("4001") || m_strEvent != _T("4002") ||  m_strEvent != _T("4003") || m_strEvent != _T("4004") 
	//	|| m_strEvent != _T("4005") || m_strEvent != _T("4006") || m_strEvent != _T("4007"))
	if(m_strEvent != _T("4001") && m_strEvent != _T("4002") &&  m_strEvent != _T("4003") && m_strEvent != _T("4004") 
		&& m_strEvent != _T("4005") && m_strEvent != _T("4006") && m_strEvent != _T("4007"))
	{
		QString strTemp;
		strTemp = QString(_T("�����󡿡�������Χ��ConAlarm: [Data]=>[Event]�ֶγ�����Χ;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;

	}

	if(m_strMsg.GetLength()>256)
	{
		QString strTemp;
		strTemp = QString(_T("�����󡿡�������Χ��ConAlarm: [Data]=>[Msg]�ֶγ�����Χ;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_ConAlarm::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strEventKey, oElement, m_strEvent);
	xml_SetAttributeValue(pXmlKeys->m_strMsgKey, oElement, m_strMsg);
	return 0;
}

long CTcpEdgePkgData_ConAlarm::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strEvent);
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strEvent);
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strEvent);
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
	}
	return 0;
}

void CTcpEdgePkgData_ConAlarm::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ConAlarm::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ConAlarm *p = (CTcpEdgePkgData_ConAlarm*)pObj;

	if(m_strContainer != p->m_strContainer)
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

BOOL CTcpEdgePkgData_ConAlarm::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ConAlarm *p = (CTcpEdgePkgData_ConAlarm*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strEvent = m_strEvent;
	p->m_strMsg = m_strMsg;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ConAlarm::Clone()
{
	CTcpEdgePkgData_ConAlarm *p = new CTcpEdgePkgData_ConAlarm();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_ConAlarm::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_ConAlarm *p = new CTcpEdgePkgData_ConAlarm();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_ConAlarm::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ConAlarm::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ConAlarm::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_ConAlarm::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->GetFieldValue(pXmlKeys->m_strMsgKey, m_strMsg);
	return 0;
}

long CTcpEdgePkgData_ConAlarm::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->SetFieldValue(pXmlKeys->m_strMsgKey, m_strMsg);
	return 0;
}

