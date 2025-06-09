//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgDisk.cpp  CTcpEdgePkgDisk


#include "stdafx.h"
#include "TcpEdgePkgDisk.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgDisk::CTcpEdgePkgDisk()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgDisk::~CTcpEdgePkgDisk()
{
}

BOOL CTcpEdgePkgDisk::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("�����󡿡�������ȱʧ��%1��[%2]=>[%3$%4]�����ֶ�ȱʧ;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Disk).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������%1��[%2]=>[%3$%4]�ֶ����ʹ���;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Disk).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgDisk::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDiskKey, oNode, m_strDisk);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskLmtKey, oNode, m_strDiskLmt);

	m_strErrorInfo += CheckRangePer(_T(""), PkgData_Node_Disk, PkgData_Node_DiskLmt, m_strDiskLmt);
	m_strRangeOut += CheckRangePer(_T(""), PkgData_Node_Disk, PkgData_Node_DiskLmt, m_strDiskLmt);


	return 0;
}

long CTcpEdgePkgDisk::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDiskKey, oElement, m_strDisk);
	xml_SetAttributeValue(pXmlKeys->m_strDiskLmtKey, oElement, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgDisk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDisk);
		BinarySerializeCalLen(oBinaryBuffer, m_strDiskLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDisk);
		BinarySerializeRead(oBinaryBuffer, m_strDiskLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDisk);
		BinarySerializeWrite(oBinaryBuffer, m_strDiskLmt);
	}
	return 0;
}

void CTcpEdgePkgDisk::InitAfterRead()
{
}

BOOL CTcpEdgePkgDisk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgDisk *p = (CTcpEdgePkgDisk*)pObj;

	if(m_strDisk != p->m_strDisk)
	{
		return FALSE;
	}

	if(m_strDiskLmt != p->m_strDiskLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgDisk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgDisk *p = (CTcpEdgePkgDisk*)pDest;

	p->m_strDisk = m_strDisk;
	p->m_strDiskLmt = m_strDiskLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgDisk::Clone()
{
	CTcpEdgePkgDisk *p = new CTcpEdgePkgDisk();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgDisk::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgDisk *p = new CTcpEdgePkgDisk();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgDisk::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgDisk::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgDisk::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgDisk::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDiskKey, m_strDisk);
	pRecordset->GetFieldValue(pXmlKeys->m_strDiskLmtKey, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgDisk::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDiskKey, m_strDisk);
	pRecordset->SetFieldValue(pXmlKeys->m_strDiskLmtKey, m_strDiskLmt);
	return 0;
}

