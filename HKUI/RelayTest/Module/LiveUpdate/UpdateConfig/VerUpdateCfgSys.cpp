// VerUpdateCfgSys.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgSys.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#define VERSIOM_BACKUP	_T("VerBackup\\")
#define VERSION_TEMP	_T("VerTemp\\")

// CVerUpdateCfgSys

CVerUpdateCfgSys::CVerUpdateCfgSys()
{
	//初始化属性
}

CVerUpdateCfgSys::~CVerUpdateCfgSys()
{
}

long CVerUpdateCfgSys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strIdxSysKey, oNode, m_idxSys);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetElementText(pXmlKeys->m_strRunPathKey, oNode, m_strRunPath);

	if (!m_strRunPath.IsEmpty())
	{
		m_strRunPath = _P_GetInstallPath();
	}

	//自动生成VerPath和BackupPath
	CString strTmpPath;
    strTmpPath.Format(_T("%s%s"),m_strRunPath.GetString(),VERSION_TEMP);
	SetVerPath(strTmpPath);

	CString strBkPath;
    strBkPath.Format(_T("%s%s"),m_strRunPath.GetString(),VERSIOM_BACKUP);
	SetBackupPath(strBkPath);

	return 0;
}

long CVerUpdateCfgSys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strIdxSysKey, oElement, m_idxSys);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetElementText(pXmlKeys->m_strRunPathKey, oXMLDoc, oElement, m_strRunPath);

	return 0;
}

long CVerUpdateCfgSys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_idxSys);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strRunPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_idxSys);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strRunPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_idxSys);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strRunPath);
	}

	return 0;
}

BOOL CVerUpdateCfgSys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CVerUpdateCfgSys *p = (CVerUpdateCfgSys*)pObj;

	if(m_idxSys != p->m_idxSys)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strRunPath != p->m_strRunPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CVerUpdateCfgSys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVerUpdateCfgSys *p = (CVerUpdateCfgSys*)pDest;
	p->m_idxSys = m_idxSys;
	p->m_strType = m_strType;
	p->m_strRunPath = m_strRunPath;
	p->m_strVerPath = m_strVerPath;
	p->m_strBackupPath = m_strBackupPath;

	return TRUE;
}

CBaseObject* CVerUpdateCfgSys::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CVerUpdateCfgSys();

	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}

	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	

	return pNew;
}
