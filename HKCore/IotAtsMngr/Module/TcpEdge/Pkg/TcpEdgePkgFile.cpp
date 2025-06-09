//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgFile.cpp  CTcpEdgePkgFile


#include "stdafx.h"
#include "TcpEdgePkgFile.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgFile::CTcpEdgePkgFile()
{
	m_arrayNotMust[0] = PkgData_Node_FileType;
}

CTcpEdgePkgFile::~CTcpEdgePkgFile()
{
}

BOOL CTcpEdgePkgFile::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】%1：[%2]=>[%3$%4]必需字段缺失;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_File).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】%1：[%2]=>[%3$%4]字段类型错误;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_File).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFileTypeKey, oNode, m_strFileType);
	xml_GetAttibuteValue(pXmlKeys->m_strPathKey, oNode, m_strPath);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_strSize);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);

	return 0;
}

long CTcpEdgePkgFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFileTypeKey, oElement, m_strFileType);
	xml_SetAttributeValue(pXmlKeys->m_strPathKey, oElement, m_strPath);
	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_strSize);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);

	return 0;
}

long CTcpEdgePkgFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFileType);
		BinarySerializeCalLen(oBinaryBuffer, m_strPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strSize);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFileType);
		BinarySerializeRead(oBinaryBuffer, m_strPath);
		BinarySerializeRead(oBinaryBuffer, m_strSize);
		BinarySerializeRead(oBinaryBuffer, m_strName);

	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFileType);
		BinarySerializeWrite(oBinaryBuffer, m_strPath);
		BinarySerializeWrite(oBinaryBuffer, m_strSize);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
	}
	return 0;
}

void CTcpEdgePkgFile::InitAfterRead()
{
}

BOOL CTcpEdgePkgFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgFile *p = (CTcpEdgePkgFile*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strFileType != p->m_strFileType)
	{
		return FALSE;
	}

	if(m_strPath != p->m_strPath)
	{
		return FALSE;
	}

	if(m_strSize != p->m_strSize)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgFile *p = (CTcpEdgePkgFile*)pDest;

	p->m_strName = m_strName;
	p->m_strFileType = m_strFileType;
	p->m_strPath = m_strPath;
	p->m_strSize = m_strSize;
	return TRUE;
}

CBaseObject* CTcpEdgePkgFile::Clone()
{
	CTcpEdgePkgFile *p = new CTcpEdgePkgFile();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgFile::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgFile *p = new CTcpEdgePkgFile();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgFile::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgFile::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgFile::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strFileTypeKey, m_strFileType);
	pRecordset->GetFieldValue(pXmlKeys->m_strPathKey, m_strPath);
	pRecordset->GetFieldValue(pXmlKeys->m_strSizeKey, m_strSize);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CTcpEdgePkgFile::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strFileTypeKey, m_strFileType);
	pRecordset->SetFieldValue(pXmlKeys->m_strPathKey, m_strPath);
	pRecordset->SetFieldValue(pXmlKeys->m_strSizeKey, m_strSize);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

CDvmDataset* CTcpEdgePkgFile::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_File;
	pDataset->m_strDataType = PkgData_Type_Object;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Name);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileType, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Path);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Size);

	return pDataset;
}
