//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeBody.cpp  CEdgeBody


#include "stdafx.h"
#include "EdgeBody.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeBody::CEdgeBody()
{
	//初始化属性
	m_nFileSize = -1;
	m_nCode = -1;

	//初始化成员变量
}

CEdgeBody::~CEdgeBody()
{
}

long CEdgeBody::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFileDirKey, oNode, m_strFileDir);
	xml_GetAttibuteValue(pXmlKeys->m_strFileNameKey, oNode, m_strFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strFileSizeKey, oNode, m_nFileSize);
	xml_GetAttibuteValue(pXmlKeys->m_strContentKey, oNode, m_strContent);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_nCode);
	xml_GetAttibuteValue(pXmlKeys->m_strMessageKey, oNode, m_strMessage);
	return 0;
}

long CEdgeBody::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(m_strFileDir.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strFileDirKey, oElement, m_strFileDir);
	if(m_strFileName.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strFileNameKey, oElement, m_strFileName);
	if(m_nFileSize > 0)
		xml_SetAttributeValue(pXmlKeys->m_strFileSizeKey, oElement, m_nFileSize);
	if(m_strContent.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strContentKey, oElement, m_strContent);
	if(m_nCode >= 0)
		xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_nCode);
	if(m_strMessage.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strMessageKey, oElement, m_strMessage);
	return 0;
}

long CEdgeBody::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFileDir);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_nFileSize);
		BinarySerializeCalLen(oBinaryBuffer, m_strContent);
		BinarySerializeCalLen(oBinaryBuffer, m_nCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strMessage);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFileDir);
		BinarySerializeRead(oBinaryBuffer, m_strFileName);
		BinarySerializeRead(oBinaryBuffer, m_nFileSize);
		BinarySerializeRead(oBinaryBuffer, m_strContent);
		BinarySerializeRead(oBinaryBuffer, m_nCode);
		BinarySerializeRead(oBinaryBuffer, m_strMessage);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFileDir);
		BinarySerializeWrite(oBinaryBuffer, m_strFileName);
		BinarySerializeWrite(oBinaryBuffer, m_nFileSize);
		BinarySerializeWrite(oBinaryBuffer, m_strContent);
		BinarySerializeWrite(oBinaryBuffer, m_nCode);
		BinarySerializeWrite(oBinaryBuffer, m_strMessage);
	}
	return 0;
}

void CEdgeBody::InitAfterRead()
{
	CExBaseList* pFileDir = new CExBaseList;
	pFileDir->m_strID = CEdgeCmdMngrXmlRWKeys::FileDirKey();
	pFileDir->m_strName = m_strFileDir;
	AddNewChild(pFileDir);

	CExBaseList* pFileName = new CExBaseList;
	pFileName->m_strID = CEdgeCmdMngrXmlRWKeys::FileNameKey();
	pFileName->m_strName = m_strFileName;
	AddNewChild(pFileName);

	CExBaseList* pFileSize = new CExBaseList;
	pFileSize->m_strID = CEdgeCmdMngrXmlRWKeys::FileSizeKey();
	pFileSize->m_strName.Format("%d", m_nFileSize);
	AddNewChild(pFileSize);

	CExBaseList* pContent = new CExBaseList;
	pContent->m_strID = CEdgeCmdMngrXmlRWKeys::ContentKey();
	pContent->m_strName = m_strContent;
	AddNewChild(pContent);

	CExBaseList* pCode = new CExBaseList;
	pCode->m_strID = CEdgeCmdMngrXmlRWKeys::CodeKey();
	pCode->m_strName.Format("%d", m_nCode);
	AddNewChild(pCode);

	CExBaseList* pMessage = new CExBaseList;
	pMessage->m_strID = CEdgeCmdMngrXmlRWKeys::MessageKey();
	pMessage->m_strName = m_strMessage;
	AddNewChild(pMessage);
}

BOOL CEdgeBody::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeBody *p = (CEdgeBody*)pObj;

	if(m_strFileDir != p->m_strFileDir)
	{
		return FALSE;
	}

	if(m_strFileName != p->m_strFileName)
	{
		return FALSE;
	}

	if(m_nFileSize != p->m_nFileSize)
	{
		return FALSE;
	}

	if(m_strContent != p->m_strContent)
	{
		return FALSE;
	}

	if(m_nCode != p->m_nCode)
	{
		return FALSE;
	}

	if(m_strMessage != p->m_strMessage)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeBody::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeBody *p = (CEdgeBody*)pDest;

	p->m_strFileDir = m_strFileDir;
	p->m_strFileName = m_strFileName;
	p->m_nFileSize = m_nFileSize;
	p->m_strContent = m_strContent;
	p->m_nCode = m_nCode;
	p->m_strMessage = m_strMessage;
	return TRUE;
}

CBaseObject* CEdgeBody::Clone()
{
	CEdgeBody *p = new CEdgeBody();
	Copy(p);
	return p;
}

CBaseObject* CEdgeBody::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeBody *p = new CEdgeBody();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeBody::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeBody::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeBody::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
