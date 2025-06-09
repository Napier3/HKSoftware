//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgCpu.cpp  CTcpEdgePkgCpu


#include "stdafx.h"
#include "TcpEdgePkgCpu.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgCpu::CTcpEdgePkgCpu()
{
	//��ʼ������

	//��ʼ����Ա����
	m_arrayNotMust[0] = PkgData_Node_Cache;
	m_arrayNotMust[1] = PkgData_Node_Arch;
	m_arrayNotMust[2] = PkgData_Node_CpuLmt;
}

CTcpEdgePkgCpu::~CTcpEdgePkgCpu()
{
}

BOOL CTcpEdgePkgCpu::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("�����󡿡�������ȱʧ��%1��[%2]=>[%3$%4]�����ֶ�ȱʧ;\n").arg(m_strID).arg(PkgData_Node_Data).arg(PkgData_Node_Cpu).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������%1��[%2]=>[%3$%4]�ֶ����ʹ���;\n").arg(m_strID).arg(PkgData_Node_Data).arg(PkgData_Node_Cpu).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgCpu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCpusKey, oNode, m_strCpus);
	xml_GetAttibuteValue(pXmlKeys->m_strFrequencyKey, oNode, m_strFrequency);
	xml_GetAttibuteValue(pXmlKeys->m_strCacheKey, oNode, m_strCache);
	xml_GetAttibuteValue(pXmlKeys->m_strArchKey, oNode, m_strArch);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_strCpuLmt);

	m_strErrorInfo += CheckRangePer(_T(""), PkgData_Node_Cpu, PkgData_Node_CpuLmt, m_strCpuLmt);
	m_strRangeOut += CheckRangePer(_T(""), PkgData_Node_Cpu, PkgData_Node_CpuLmt, m_strCpuLmt);

	return 0;
}

long CTcpEdgePkgCpu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCpusKey, oElement, m_strCpus);
	xml_SetAttributeValue(pXmlKeys->m_strFrequencyKey, oElement, m_strFrequency);
	xml_SetAttributeValue(pXmlKeys->m_strCacheKey, oElement, m_strCache);
	xml_SetAttributeValue(pXmlKeys->m_strArchKey, oElement, m_strArch);
	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_strCpuLmt);
	return 0;
}

long CTcpEdgePkgCpu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCpus);
		BinarySerializeCalLen(oBinaryBuffer, m_strFrequency);
		BinarySerializeCalLen(oBinaryBuffer, m_strCache);
		BinarySerializeCalLen(oBinaryBuffer, m_strArch);
		BinarySerializeCalLen(oBinaryBuffer, m_strCpuLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCpus);
		BinarySerializeRead(oBinaryBuffer, m_strFrequency);
		BinarySerializeRead(oBinaryBuffer, m_strCache);
		BinarySerializeRead(oBinaryBuffer, m_strArch);
		BinarySerializeRead(oBinaryBuffer, m_strCpuLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCpus);
		BinarySerializeWrite(oBinaryBuffer, m_strFrequency);
		BinarySerializeWrite(oBinaryBuffer, m_strCache);
		BinarySerializeWrite(oBinaryBuffer, m_strArch);
		BinarySerializeWrite(oBinaryBuffer, m_strCpuLmt);
	}
	return 0;
}

void CTcpEdgePkgCpu::InitAfterRead()
{
}

BOOL CTcpEdgePkgCpu::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgCpu *p = (CTcpEdgePkgCpu*)pObj;

	if(m_strCpus != p->m_strCpus)
	{
		return FALSE;
	}

	if(m_strFrequency != p->m_strFrequency)
	{
		return FALSE;
	}

	if(m_strCache != p->m_strCache)
	{
		return FALSE;
	}

	if(m_strArch != p->m_strArch)
	{
		return FALSE;
	}

	if(m_strCpuLmt != p->m_strCpuLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgCpu::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgCpu *p = (CTcpEdgePkgCpu*)pDest;

	p->m_strCpus = m_strCpus;
	p->m_strFrequency = m_strFrequency;
	p->m_strCache = m_strCache;
	p->m_strArch = m_strArch;
	p->m_strCpuLmt = m_strCpuLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgCpu::Clone()
{
	CTcpEdgePkgCpu *p = new CTcpEdgePkgCpu();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgCpu::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgCpu *p = new CTcpEdgePkgCpu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgCpu::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgCpu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgCpu::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgCpu::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCpusKey, m_strCpus);
	pRecordset->GetFieldValue(pXmlKeys->m_strFrequencyKey, m_strFrequency);
	pRecordset->GetFieldValue(pXmlKeys->m_strCacheKey, m_strCache);
	pRecordset->GetFieldValue(pXmlKeys->m_strArchKey, m_strArch);
	pRecordset->GetFieldValue(pXmlKeys->m_strCpuLmtKey, m_strCpuLmt);
	return 0;
}

long CTcpEdgePkgCpu::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCpusKey, m_strCpus);
	pRecordset->SetFieldValue(pXmlKeys->m_strFrequencyKey, m_strFrequency);
	pRecordset->SetFieldValue(pXmlKeys->m_strCacheKey, m_strCache);
	pRecordset->SetFieldValue(pXmlKeys->m_strArchKey, m_strArch);
	pRecordset->SetFieldValue(pXmlKeys->m_strCpuLmtKey, m_strCpuLmt);
	return 0;
}

