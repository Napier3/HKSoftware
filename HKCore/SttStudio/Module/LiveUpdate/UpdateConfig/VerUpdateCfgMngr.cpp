// VerUpdateCfgMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgMngr.h"

#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/API/FileApi.h"

#include "../SttLiveUpdateDef.h"

// CVerUpdateCfgMngr

CVerUpdateCfgMngr::CVerUpdateCfgMngr()
{
	
}

CVerUpdateCfgMngr::~CVerUpdateCfgMngr()
{
}

long CVerUpdateCfgMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CVerUpdateCfgMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CVerUpdateCfgMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CVerUpdateCfgMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strYunKey)
	{
		pNew = new CVerUpdateCfgYun();
	}

	if (strClassID == pXmlKeys->m_strSysesKey)
	{
		pNew = new CVerUpdateCfgSyses();
	}

	return pNew;
}

CExBaseObject* CVerUpdateCfgMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == VERUPDATECFGCLASSID_YUN)
	{
		pNew = new CVerUpdateCfgYun();
	}

	if (nClassID == VERUPDATECFGCLASSID_SYSES)
	{
		pNew = new CVerUpdateCfgSyses();
	}

	return pNew;
}

void CVerUpdateCfgMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == VERUPDATECFGCLASSID_SYSES)
		{
			m_pCfgSyses = (CVerUpdateCfgSyses*)p;
		}
		else if (nClassID == VERUPDATECFGCLASSID_YUN)
		{
			m_pCfgYun = (CVerUpdateCfgYun*)p;
		}
	}

	if (m_pCfgSyses == NULL)
	{
		m_pCfgSyses = (CVerUpdateCfgSyses*)AddNewChild(new CVerUpdateCfgSyses());
	}

	if (m_pCfgYun == NULL)
	{
		m_pCfgYun = (CVerUpdateCfgYun*)AddNewChild(new CVerUpdateCfgYun());
	}
}

CString CVerUpdateCfgMngr::GetCfgFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += LIVEUPDATE_CFG_BASE;

	return strFile;
}

BOOL CVerUpdateCfgMngr::Open()
{
	CString strFile = GetCfgFile();

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("版本更新配置文件：%s 不存在"),strFile.GetString());

		return FALSE;
	}

	BOOL bRet = CExBaseObject::OpenXmlFile(strFile, CVerUpdateCfgXmlRWKeys::VerUpdateCfgKey(), CVerUpdateCfgXmlRWKeys::g_pXmlKeys);
	if (bRet)
	{
		InitAfterRead();
	}

	return bRet;
}

BOOL CVerUpdateCfgMngr::Save()
{
	CString strFile = GetCfgFile();
	return CExBaseObject::SaveXmlFile(strFile, CVerUpdateCfgXmlRWKeys::g_pXmlKeys);
}
