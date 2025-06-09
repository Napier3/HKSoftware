//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCpu.cpp  CEdgeCpu


#include "stdafx.h"
#include "EdgeCpu.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCpu::CEdgeCpu()
{
	//初始化属性
	m_nCpus = 0;
	m_fFrequency = 0;
	m_nCache = 0;
	m_nCpuLmt = 0;

	//初始化成员变量
}

CEdgeCpu::~CEdgeCpu()
{
}

long CEdgeCpu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCpusKey, oNode, m_nCpus);
	xml_GetAttibuteValue(pXmlKeys->m_strFrequencyKey, oNode, m_fFrequency);
	xml_GetAttibuteValue(pXmlKeys->m_strCacheKey, oNode, m_nCache);
	xml_GetAttibuteValue(pXmlKeys->m_strArchKey, oNode, m_strArch);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_nCpuLmt);
	
	AddErrorInfo(pXmlKeys->m_strCpusKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strFrequencyKey, oNode, CJSON_Double);
	AddErrorInfo(pXmlKeys->m_strCacheKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strArchKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strCpuLmtKey, oNode, CJSON_Int);
	
	return 0;
}

long CEdgeCpu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCpusKey, oElement, m_nCpus);
	xml_SetAttributeValue(pXmlKeys->m_strFrequencyKey, oElement, m_fFrequency);
	xml_SetAttributeValue(pXmlKeys->m_strCacheKey, oElement, m_nCache);
	xml_SetAttributeValue(pXmlKeys->m_strArchKey, oElement, m_strArch);
	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_nCpuLmt);
	return 0;
}

long CEdgeCpu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nCpus);
		BinarySerializeCalLen(oBinaryBuffer, m_fFrequency);
		BinarySerializeCalLen(oBinaryBuffer, m_nCache);
		BinarySerializeCalLen(oBinaryBuffer, m_strArch);
		BinarySerializeCalLen(oBinaryBuffer, m_nCpuLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nCpus);
		BinarySerializeRead(oBinaryBuffer, m_fFrequency);
		BinarySerializeRead(oBinaryBuffer, m_nCache);
		BinarySerializeRead(oBinaryBuffer, m_strArch);
		BinarySerializeRead(oBinaryBuffer, m_nCpuLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nCpus);
		BinarySerializeWrite(oBinaryBuffer, m_fFrequency);
		BinarySerializeWrite(oBinaryBuffer, m_nCache);
		BinarySerializeWrite(oBinaryBuffer, m_strArch);
		BinarySerializeWrite(oBinaryBuffer, m_nCpuLmt);
	}
	return 0;
}

void CEdgeCpu::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pCpus = new CExBaseList;
	pCpus->m_strID = CEdgeCmdMngrXmlRWKeys::CpusKey();
	pCpus->m_strName.Format("%d", m_nCpus);
	AddNewChild(pCpus);

	CExBaseList* pFrequency = new CExBaseList;
	pFrequency->m_strID = CEdgeCmdMngrXmlRWKeys::FrequencyKey();
	pFrequency->m_strName.Format("%d", m_fFrequency);
	AddNewChild(pFrequency);

	CExBaseList* pCache = new CExBaseList;
	pCache->m_strID = CEdgeCmdMngrXmlRWKeys::CacheKey();
	pCache->m_strName.Format("%d", m_nCache);
	AddNewChild(pCache);

	CExBaseList* pArch = new CExBaseList;
	pArch->m_strID = CEdgeCmdMngrXmlRWKeys::ArchKey();
	pArch->m_strName = m_strArch;
	AddNewChild(pArch);

	CExBaseList* pCpuLmt = new CExBaseList;
	pCpuLmt->m_strID = CEdgeCmdMngrXmlRWKeys::CpuLmtKey();
	pCpuLmt->m_strName.Format("%d", m_nCpuLmt);
	AddNewChild(pCpuLmt);
}

BOOL CEdgeCpu::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCpu *p = (CEdgeCpu*)pObj;

	if(m_nCpus != p->m_nCpus)
	{
		return FALSE;
	}

	if(m_fFrequency != p->m_fFrequency)
	{
		return FALSE;
	}

	if(m_nCache != p->m_nCache)
	{
		return FALSE;
	}

	if(m_strArch != p->m_strArch)
	{
		return FALSE;
	}

	if(m_nCpuLmt != p->m_nCpuLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeCpu::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCpu *p = (CEdgeCpu*)pDest;

	p->m_nCpus = m_nCpus;
	p->m_fFrequency = m_fFrequency;
	p->m_nCache = m_nCache;
	p->m_strArch = m_strArch;
	p->m_nCpuLmt = m_nCpuLmt;
	return TRUE;
}

CBaseObject* CEdgeCpu::Clone()
{
	CEdgeCpu *p = new CEdgeCpu();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCpu::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCpu *p = new CEdgeCpu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCpu::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeCpu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeCpu::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
