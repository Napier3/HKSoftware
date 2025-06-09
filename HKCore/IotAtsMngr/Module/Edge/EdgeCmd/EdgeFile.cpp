//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeFile.cpp  CEdgeFile


#include "stdafx.h"
#include "EdgeFile.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeFile::CEdgeFile()
{
	//初始化属性
	m_nSize = 0;

	//初始化成员变量
	m_pEdgeSign = NULL;
}

CEdgeFile::~CEdgeFile()
{
}

long CEdgeFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strUrlKey, oNode, m_strUrl);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	xml_GetAttibuteValue(pXmlKeys->m_strMd5Key, oNode, m_strMd5);
	xml_GetAttibuteValue(pXmlKeys->m_strFileTypeKey, oNode, m_strFileType);

	AddErrorInfo(pXmlKeys->m_strNameKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strUrlKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strSizeKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strMd5Key, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strFileTypeKey, oNode, CJSON_String);
	return 0;
}

long CEdgeFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	if(m_strUrl.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strUrlKey, oElement, m_strUrl);
	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	xml_SetAttributeValue(pXmlKeys->m_strMd5Key, oElement, m_strMd5);
	if(m_strFileType.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strFileTypeKey, oElement, m_strFileType);
	return 0;
}

long CEdgeFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strUrl);
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
		BinarySerializeCalLen(oBinaryBuffer, m_strMd5);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strUrl);
		BinarySerializeRead(oBinaryBuffer, m_nSize);
		BinarySerializeRead(oBinaryBuffer, m_strMd5);
		BinarySerializeRead(oBinaryBuffer, m_strFileType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strUrl);
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
		BinarySerializeWrite(oBinaryBuffer, m_strMd5);
		BinarySerializeWrite(oBinaryBuffer, m_strFileType);
	}
	return 0;
}

void CEdgeFile::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGESIGN)
		{
			m_pEdgeSign = (CEdgeSign*)p;
		}
	}

	m_strID = GetXmlElementKey();

	CExBaseList* pName = new CExBaseList;
	pName->m_strID = _T("name");
	pName->m_strName = m_strName;
	AddNewChild(pName);

	CExBaseList* pUrl = new CExBaseList;
	pUrl->m_strID = CEdgeCmdMngrXmlRWKeys::UrlKey();
	pUrl->m_strName = m_strUrl;
	AddNewChild(pUrl);

	CExBaseList* pSize = new CExBaseList;
	pSize->m_strID = CEdgeCmdMngrXmlRWKeys::SizeKey();
	pSize->m_strName.Format("%d", m_nSize);
	AddNewChild(pSize);

	CExBaseList* pMd5 = new CExBaseList;
	pMd5->m_strID = CEdgeCmdMngrXmlRWKeys::Md5Key();
	pMd5->m_strName = m_strMd5;
	AddNewChild(pMd5);

	CExBaseList* pFileType = new CExBaseList;
	pFileType->m_strID = CEdgeCmdMngrXmlRWKeys::FileTypeKey();
	pFileType->m_strName = m_strFileType;
	AddNewChild(pFileType);
}

BOOL CEdgeFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeFile *p = (CEdgeFile*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strUrl != p->m_strUrl)
	{
		return FALSE;
	}

	if(m_nSize != p->m_nSize)
	{
		return FALSE;
	}

	if(m_strMd5 != p->m_strMd5)
	{
		return FALSE;
	}

	if(m_strFileType != p->m_strFileType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeFile *p = (CEdgeFile*)pDest;

	p->m_strName = m_strName;
	p->m_strUrl = m_strUrl;
	p->m_nSize = m_nSize;
	p->m_strMd5 = m_strMd5;
	p->m_strFileType = m_strFileType;
	return TRUE;
}

CBaseObject* CEdgeFile::Clone()
{
	CEdgeFile *p = new CEdgeFile();
	Copy(p);
	return p;
}

CBaseObject* CEdgeFile::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeFile *p = new CEdgeFile();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeFile::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGESIGN)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeSignKey)
	{
		pNew = new CEdgeSign();
	}

	return pNew;
}

CExBaseObject* CEdgeFile::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGESIGN)
	{
		pNew = new CEdgeSign();
	}

	return pNew;
}
