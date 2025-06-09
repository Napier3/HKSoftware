// SttNativeCfgMngr.cpp
//

#include "stdafx.h"
#include "../../../../Module/API/FileApi.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttNativeCfgMngr.h"

#include "../SttLiveUpdateDef.h"

// CSttNativeCfgMngr

CSttNativeCfgMngr::CSttNativeCfgMngr()
{
	//初始化属性
	m_pCfgYun = NULL;
	m_pCfgLiveUpdate = NULL;
	m_pCfgMnt = NULL;
}

CSttNativeCfgMngr::~CSttNativeCfgMngr()
{
}

long CSttNativeCfgMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgYun *pXmlKeys = (CSttNativeCfgYun*)pXmlRWKeys;
	
	return 0;
}

long CSttNativeCfgMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgYun *pXmlKeys = (CSttNativeCfgYun*)pXmlRWKeys;
	
	return 0;
}

long CSttNativeCfgMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		
	}

	return 0;
}

CExBaseObject* CSttNativeCfgMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strYunKey)
	{
		pNew = new CSttNativeCfgYun();
	}

	if (strClassID == pXmlKeys->m_strLiveUpdateKey)
	{
		pNew = new CSttNativeCfgLiveUpdate();
	}

	if (strClassID == pXmlKeys->m_strMntKey)
	{
		pNew = new CSttNativeCfgMnt();
	}

	return pNew;
}

CExBaseObject* CSttNativeCfgMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == STTNATIVECFGCLASSID_YUN)
	{
		pNew = new CSttNativeCfgYun();
	}

	if (nClassID == STTNATIVECFGCLASSID_LIVEUPDATE)
	{
		pNew = new CSttNativeCfgLiveUpdate();
	}

	if (nClassID == STTNATIVECFGCLASSID_MNT)
	{
		pNew = new CSttNativeCfgMnt();
	}

	return pNew;
}

void CSttNativeCfgMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == STTNATIVECFGCLASSID_YUN)
		{
			m_pCfgYun = (CSttNativeCfgYun*)p;
		}
		else if (nClassID == STTNATIVECFGCLASSID_LIVEUPDATE)
		{
			m_pCfgLiveUpdate = (CSttNativeCfgLiveUpdate*)p;
		}
		else if (nClassID == STTNATIVECFGCLASSID_MNT)
		{
			m_pCfgMnt = (CSttNativeCfgMnt*)p;
		}
	}

	if (m_pCfgYun == NULL)
	{
		m_pCfgYun = (CSttNativeCfgYun*)AddNewChild(new CSttNativeCfgYun());
	}

	if (m_pCfgLiveUpdate == NULL)
	{
		m_pCfgLiveUpdate = (CSttNativeCfgLiveUpdate*)AddNewChild(new CSttNativeCfgLiveUpdate());
	}

	if (m_pCfgMnt == NULL)
	{
		m_pCfgMnt = (CSttNativeCfgMnt*)AddNewChild(new CSttNativeCfgMnt());
	}

	m_pCfgLiveUpdate->InitAfterRead();
}

CString CSttNativeCfgMngr::GetCfgFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += LIVEUPDATE_CFG_NATIVE;

	return strFile;
}

BOOL CSttNativeCfgMngr::Open()
{
	CString strFile = GetCfgFile();

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("版本更新配置文件：%s 不存在"),strFile.GetString());
		return FALSE;
	}

	BOOL bRet = CExBaseObject::OpenXmlFile(strFile, CSttNativeCfgXmlRWKeys::SttNativeCfgKey(), CSttNativeCfgXmlRWKeys::g_pXmlKeys);
	if (bRet)
	{
		InitAfterRead();
	}
	
	return bRet;
}

BOOL CSttNativeCfgMngr::Save()
{
	CString strFile = GetCfgFile();
	return CExBaseObject::SaveXmlFile(strFile, CSttNativeCfgXmlRWKeys::g_pXmlKeys);
}
