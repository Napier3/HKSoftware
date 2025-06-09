//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgTool.cpp  CIecCfgTool


#include "stdafx.h"
#include "IecCfgTool.h"
#include "..\..\..\Module\XfileMngrBase\DlgXFileMngr.h"

const CString CIecCfgTool::g_strIecCfgSystemConfigFile = _T("IecCfgSystemConfig.xml");

CIecCfgTool* CIecCfgTool::g_pIecCfgTool = NULL;
long CIecCfgTool::g_nIecCfgTollRef = 0;

CIecCfgTool* CIecCfgTool::Create(BOOL bIxml, BOOL bIecfg)
{
	g_nIecCfgTollRef++;

	if (g_nIecCfgTollRef == 1)
	{
		g_pIecCfgTool = new CIecCfgTool();
		g_pIecCfgTool->InitIecCfgTool(bIxml, bIecfg);
	}

	return g_pIecCfgTool;
}

void CIecCfgTool::Release(BOOL bSave)
{
	g_nIecCfgTollRef--;

	if (g_nIecCfgTollRef == 0)
	{
		if (bSave)
		{
			g_pIecCfgTool->Save();
		}

		delete g_pIecCfgTool;
		g_pIecCfgTool = NULL;
	}
}

BOOL CIecCfgTool::IsModelUseHarm()//周宏军 20200616  增加AT02配置
{
	if ((g_nIecCfgTollRef<1)||(g_pIecCfgTool == NULL))
	{
		return FALSE;
	}

	return (g_pIecCfgTool->m_nAT02D_UseHarm!=0);
}

BOOL CIecCfgTool::IsVerifyVolCurChannel()//周宏军 20201128  增加AT02D配置
{
	if ((g_nIecCfgTollRef<1)||(g_pIecCfgTool == NULL))
	{
		return FALSE;
	}

	return (g_pIecCfgTool->m_nAT02D_VerifyVolCurChannel!=0);
}

BOOL CIecCfgTool::LinkGout()//周宏军 20200622  
{
	if ((g_nIecCfgTollRef<1)||(g_pIecCfgTool == NULL))
	{
		return FALSE;
	}

	return (g_pIecCfgTool->m_nLinkGout!=0);
}

BOOL CIecCfgTool::IsAutoOpenLast()//周宏军 20200914
{
	if ((g_nIecCfgTollRef<1)||(g_pIecCfgTool == NULL))
	{
		return FALSE;
	}

	return (g_pIecCfgTool->m_nAutoOpenLast!=0);
}

void CIecCfgTool::InitIecCfgTool(BOOL bIxml, BOOL bIecfg)
{
	//历史记录
	Open();

	if (!g_pIecCfgTool->IsAutoOpenLast())
	{
		CIecCfgFiles* pCurIecfgFiles = GetIecCfgFiles();

		if (pCurIecfgFiles != NULL)
		{
			pCurIecfgFiles->DeleteAll();
		}
	}

	if (bIxml)
	{
		InitIecCfgTool_ixml();
	}

	if (bIecfg)
	{
		InitIecCfgTool_iecfg();
	}
}

void CIecCfgTool::InitIecCfgTool_ixml()
{

	//配置文件检索
	CString strPath;
	strPath = _P_GetLibraryPath();
	strPath += _T("IEC61850Config\\");
	m_oIecCfgFileMngr.m_strName = g_sLangTxt_ConfigFileManag;//_T("测试仪IEC61850配置文件管理");
	CXFileType *pXFileType = m_oIecCfgFileMngr.AddFileType(g_sLangTxt_IecConfigFile/*_T("IEC61850配置文件")*/
		, g_strIecCfgFilePostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_IecConfigFile/*_T("IEC61850配置文件")*/
		, g_strIecCfgFilePostfix);

// 	pXFileType = m_oIecCfgFileMngr.AddFileType(_T("IEC61850配置文件(装置)"), g_strDeviceIecCfgFilePostfix, _T(""), _T(""));
// 	pXFileType->AddNewPostfix(_T("IEC61850配置文件(装置)"), g_strDeviceIecCfgFilePostfix);

	m_oIecCfgFileMngr.SetOnllySearchMainTypeFile(TRUE);
	m_oIecCfgFileMngr.InitByXFileTypes();
	m_oIecCfgFileMngr.SetLibraryPath(strPath);
}

void CIecCfgTool::InitIecCfgTool_iecfg()
{
	//配置文件检索
	CString strPath;
	CXFileType *pXFileType = NULL;

	//智能设备测试仪IEC61850配置文件管理
	strPath = _P_GetTemplatePath();
	m_oIecCfgDeviceFileMngr.m_strName = g_sLangTxt_DvIecConfigFileMngr;//_T("智能设备测试仪IEC61850配置文件管理");
// 	pXFileType = m_oIecCfgDeviceFileMngr.AddFileType(_T("IEC61850配置文件"), g_strIecCfgFilePostfix, _T(""), _T(""));
// 	pXFileType->AddNewPostfix(_T("IEC61850配置文件"), g_strIecCfgFilePostfix);

	pXFileType = m_oIecCfgDeviceFileMngr.AddFileType(g_sLangTxt_DvIecConfigFile/*_T("IEC61850配置文件(装置)")*/
		, g_strDeviceIecCfgFilePostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_DvIecConfigFile/*_T("IEC61850配置文件(装置)")*/, g_strDeviceIecCfgFilePostfix);

	m_oIecCfgDeviceFileMngr.SetOnllySearchMainTypeFile(TRUE);
	m_oIecCfgDeviceFileMngr.InitByXFileTypes();
	m_oIecCfgDeviceFileMngr.SetLibraryPath(strPath);
}

void CIecCfgTool::InitAutoSetUIChIndex()
{
	ASSERT (g_pIecCfgTool != NULL);
	g_pIecCfgTool->_InitAutoSetUIChIndex();
}

void CIecCfgTool::SetAutoSetUIChIndex(BOOL b)
{
	ASSERT (g_pIecCfgTool != NULL);
	g_pIecCfgTool->_SetAutoSetUIChIndex(b);
}

void CIecCfgTool::SetModelUseHarm(long nUseHarm)
{
	ASSERT (g_pIecCfgTool != NULL);
	g_pIecCfgTool->_SetModelUseHarm(nUseHarm);
}

void CIecCfgTool::SetVerifyVolCurChannel(long nVerifyVolCurChannel)
{
	ASSERT (g_pIecCfgTool != NULL);
	g_pIecCfgTool->_SetVerifyVolCurChannel(nVerifyVolCurChannel);
}

void CIecCfgTool::SetLinkGout(long nLinkGout)
{
	ASSERT (g_pIecCfgTool != NULL);
	g_pIecCfgTool->_SetLinkGout(nLinkGout);
}

void CIecCfgTool::SetAutoOpenLast(long nAutoOpenLast)
{
	ASSERT (g_pIecCfgTool != NULL);
	g_pIecCfgTool->_SetAutoOpenLast(nAutoOpenLast);
}

BOOL CIecCfgTool::GetAutoSetUIChIndex()
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_GetAutoSetUIChIndex();
}

void CIecCfgTool::AdjustIecCfgFile(CIecCfgFile *pIecfgFile)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_AdjustIecCfgFile(pIecfgFile);
}

CIecCfgFile* CIecCfgTool::NewIecCfgFile(const CString &strFileType)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_NewIecCfgFile(strFileType);
}

CIecCfgFile* CIecCfgTool::NewIecCfgFile(CXFile *pXFile)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_NewIecCfgFile(pXFile);
}

BOOL CIecCfgTool::IsIecFileOpen(const CString &strFile)
{
	return FALSE;
}

CIecCfgFile* CIecCfgTool::OpenIecFile(const CString &strFile)
{
	ASSERT (g_pIecCfgTool != NULL);

	return g_pIecCfgTool->_OpenIecFile(strFile);
}

CIecCfgFile* CIecCfgTool::FindIecFile(const CString &strFile)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_FindIecFile(strFile);
}

BOOL CIecCfgTool::CloseIecFile(CIecCfgFile *pFile, BOOL bDelete)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_CloseIecFile(pFile, bDelete);
}

BOOL CIecCfgTool::SaveIecFile(CIecCfgFile *pFile)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_SaveIecFile(pFile);
}

BOOL CIecCfgTool::HasFileInFolder(CXFolder *pFolder)
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->_HasFileInFolder(pFolder);
}

CXFileMngr* CIecCfgTool::GetIecCfgFileMngr()
{
	ASSERT (g_pIecCfgTool != NULL);
	return &g_pIecCfgTool->m_oIecCfgFileMngr;
}

CXFileMngr* CIecCfgTool::GetIecCfgDeviceFileMngr()
{
	ASSERT (g_pIecCfgTool != NULL);
	return &g_pIecCfgTool->m_oIecCfgDeviceFileMngr;
}

CIecCfgFiles* CIecCfgTool::GetIecCfgFiles()
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->m_pIecCfgFiles;
}

CSclFiles* CIecCfgTool::GetSclFiles()
{
	ASSERT (g_pIecCfgTool != NULL);
	return g_pIecCfgTool->m_pSclFiles;
}

BOOL CIecCfgTool::HasIecCfgFileModified(CString &strFiles)
{
	ASSERT (g_pIecCfgTool != NULL);
	ASSERT (g_pIecCfgTool->m_pIecCfgFiles != NULL);

	return g_pIecCfgTool->m_pIecCfgFiles->HasIecCfgFileModified(strFiles);
}

CString CIecCfgTool::GetIecCfgDownDllFile()
{
	ASSERT (g_pIecCfgTool != NULL);

	return g_pIecCfgTool->m_strIecCfgDownDllFile;
}

void CIecCfgTool::SetIecCfgSmvRates(CIecCfgSmvRates *pRates, CIecCfgFile *pFile)
{
	ASSERT (g_pIecCfgTool != NULL);

	g_pIecCfgTool->_SetIecCfgSmvRates(pRates, pFile);
}

void CIecCfgTool::SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon, CIecCfgFile *pFile)
{
	ASSERT (g_pIecCfgTool != NULL);

	g_pIecCfgTool->_SetIecCfgSmvCommon(pSmvCommon, pFile);
}

BOOL CIecCfgTool::IsViewOnlyUsedInChs()
{
	ASSERT (g_pIecCfgTool != NULL);

	if (g_pIecCfgTool == NULL)
	{
		return FALSE;
	}

	return (g_pIecCfgTool->m_pIecCfgFiles->m_nViewOnlyUsedInChs == 1);
}

BOOL CIecCfgTool::IsViewChsPath()
{
	ASSERT (g_pIecCfgTool != NULL);

	if (g_pIecCfgTool == NULL)
	{
		return FALSE;
	}

	return (g_pIecCfgTool->m_pIecCfgFiles->m_nViewChsPath == 1);
}

BOOL CIecCfgTool::SetViewOnlyUsedInChs()
{
	ASSERT (g_pIecCfgTool != NULL);

	if (g_pIecCfgTool == NULL)
	{
		return FALSE;
	}

	if (g_pIecCfgTool->m_pIecCfgFiles->m_nViewOnlyUsedInChs == 1)
	{
		g_pIecCfgTool->m_pIecCfgFiles->m_nViewOnlyUsedInChs = 0;
	}
	else
	{
		g_pIecCfgTool->m_pIecCfgFiles->m_nViewOnlyUsedInChs = 1;
	}

	g_pIecCfgTool->Save();
	return IsViewOnlyUsedInChs();
}

BOOL CIecCfgTool::SetViewChsPath()
{
	ASSERT (g_pIecCfgTool != NULL);

	if (g_pIecCfgTool == NULL)
	{
		return FALSE;
	}

	if (g_pIecCfgTool->m_pIecCfgFiles->m_nViewChsPath == 1)
	{
		g_pIecCfgTool->m_pIecCfgFiles->m_nViewChsPath = 0;
	}
	else
	{
		g_pIecCfgTool->m_pIecCfgFiles->m_nViewChsPath = 1;
	}

	g_pIecCfgTool->Save();
	return IsViewChsPath();
}

BOOL CIecCfgTool::FreeSclFileRead(CSclFile *pSclFile)
{
	ASSERT (g_pIecCfgTool != NULL);

	if (g_pIecCfgTool == NULL)
	{
		return FALSE;
	}

	pSclFile->FreeSclFileRead();
	g_pIecCfgTool->m_pSclFiles->FreeSclFileRead(pSclFile);

	return TRUE;
}

CString CIecCfgTool::PopSelIecfgFile(CWnd *pParent)
{
	if (pParent == NULL)
	{
		pParent = AfxGetMainWnd();
	}

	ASSERT (g_pIecCfgTool != NULL);

	if (g_pIecCfgTool == NULL)
	{
		return _T("");
	}

	CDlgXFileMngr dlg(0, _T("ppxml"),_T("规约模板文件"), CIecCfgTool::GetIecCfgFileMngr(),OPEN_FILE_MODE, pParent);

	if(dlg.DoModal() != IDOK)
	{
		return _T("");
	}

	CString strFile = dlg.GetFileName();
	return strFile;
}

//////////////////////////////////////////////////////////////////////////

CIecCfgTool::CIecCfgTool()
{
	//初始化属性

	//初始化成员变量
	m_pIecCfgFiles = NULL;
	m_pSclFiles = NULL;
	m_nAT02D_UseHarm = 0;
	m_nAT02D_VerifyVolCurChannel = 0;
	m_nLinkGout = 0;
	m_nAutoOpenLast = 0;
}

CIecCfgTool::~CIecCfgTool()
{
}

long CIecCfgTool::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strUseDebugKey, oNode, m_strUseDebug);
	xml_GetElementText(pXmlKeys->m_strAutoSetUIChIndexKey, oNode, m_strAutoSetUIChIndex);
	xml_GetElementText(pXmlKeys->m_strIecCfgDownDllFileKey, oNode, m_strIecCfgDownDllFile);
	xml_GetAttibuteValue(pXmlKeys->m_strAT02D_UseHarmKey, oNode, m_nAT02D_UseHarm);
	xml_GetAttibuteValue(pXmlKeys->m_strAT02D_VerifyVolCurChannelKey, oNode, m_nAT02D_VerifyVolCurChannel);
	xml_GetAttibuteValue(pXmlKeys->m_strLinkGoutKey, oNode, m_nLinkGout);
	xml_GetAttibuteValue(pXmlKeys->m_strAutoOpenLastKey, oNode, m_nAutoOpenLast);

	InitAutoSetUIChIndex();

	return 0;
}

long CIecCfgTool::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strUseDebugKey, oXMLDoc, oElement, m_strUseDebug);
	xml_SetElementText(pXmlKeys->m_strAutoSetUIChIndexKey, oXMLDoc, oElement, m_strAutoSetUIChIndex);
	xml_SetElementText(pXmlKeys->m_strIecCfgDownDllFileKey, oXMLDoc, oElement, m_strIecCfgDownDllFile);
	xml_SetAttributeValue(pXmlKeys->m_strAT02D_UseHarmKey, oElement, m_nAT02D_UseHarm);
	xml_SetAttributeValue(pXmlKeys->m_strAT02D_VerifyVolCurChannelKey, oElement, m_nAT02D_VerifyVolCurChannel);
	xml_SetAttributeValue(pXmlKeys->m_strLinkGoutKey, oElement, m_nLinkGout);
	xml_SetAttributeValue(pXmlKeys->m_strAutoOpenLastKey, oElement, m_nAutoOpenLast);

	return 0;
}

void CIecCfgTool::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IFTCLASSID_CIECCFGFILES)
		{
			m_pIecCfgFiles = (CIecCfgFiles*)p;
		}
		else if (nClassID == IFTCLASSID_CSCLFILES)
		{
			m_pSclFiles = (CSclFiles*)p;
		}
	}

	if (m_pIecCfgFiles == NULL)
	{
		m_pIecCfgFiles = (CIecCfgFiles*)AddNewChild(new CIecCfgFiles());
	}

	if (m_pSclFiles == NULL)
	{
		m_pSclFiles = (CSclFiles*)AddNewChild(new CSclFiles());
	}

}

BOOL CIecCfgTool::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgTool *p = (CIecCfgTool*)pObj;

	return TRUE;
}

BOOL CIecCfgTool::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgTool *p = (CIecCfgTool*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgTool::Clone()
{
	CIecCfgTool *p = new CIecCfgTool();
	Copy(p);
	return p;
}

BOOL CIecCfgTool::CanPaste(UINT nClassID)
{
	if (nClassID == IFTCLASSID_CIECCFGFILES)
	{
		return TRUE;
	}

	if (nClassID == IFTCLASSID_CSCLFILES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgTool::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgFilesKey)
	{
		pNew = new CIecCfgFiles();
	}
	else if (strClassID == pXmlKeys->m_strCSclFilesKey)
	{
		pNew = new CSclFiles();
	}

	return pNew;
}

CExBaseObject* CIecCfgTool::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IFTCLASSID_CIECCFGFILES)
	{
		pNew = new CIecCfgFiles();
	}
	else if (nClassID == IFTCLASSID_CSCLFILES)
	{
		pNew = new CSclFiles();
	}

	return pNew;
}


//////////////////////////////////////////////////////////////////////////

long CIecCfgTool::Open()
{
	ASSERT (CIecCfgToolXmlRWKeys::g_pXmlKeys != NULL);

	CString strFile = GetInitFile();

	BOOL b = OpenXmlFile(strFile, GetXmlElementKey(), CIecCfgToolXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
		InitAfterRead();
	}

	return b;
}

long CIecCfgTool::Save()
{
	ASSERT (CIecCfgToolXmlRWKeys::g_pXmlKeys != NULL);

	CString strFile = GetInitFile();

	if (IsFileExist(strFile))
	{
		ClearFileReadOnlyAttr(strFile);
	}

	SaveXmlFile(strFile, CIecCfgToolXmlRWKeys::g_pXmlKeys);

	return 1;
}

CString CIecCfgTool::GetInitFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += g_strIecCfgSystemConfigFile;
	return strFile;
}

//////////////////////////////////////////////////////////////////////////
void CIecCfgTool::_SetAutoSetUIChIndex(BOOL b)
{
	m_bAutoSetUIChIndex = b;
	if (m_bAutoSetUIChIndex)
	{
		m_strAutoSetUIChIndex = _T("auto");
	}
	else
	{
		m_strAutoSetUIChIndex = _T("manual");
	}

}

void CIecCfgTool::_SetModelUseHarm(long nUseHarm)
{
	m_nAT02D_UseHarm = nUseHarm;
}

void CIecCfgTool::_SetVerifyVolCurChannel(long nVerifyVolCurChannel)
{
	m_nAT02D_VerifyVolCurChannel = nVerifyVolCurChannel;
}

void CIecCfgTool::_SetLinkGout(long nLinkGout)
{
	m_nLinkGout = nLinkGout;
}

void CIecCfgTool::_SetAutoOpenLast(long nAutoOpenLast)
{
	m_nAutoOpenLast = nAutoOpenLast;
}

void CIecCfgTool::_AdjustIecCfgFile(CIecCfgFile *pIecfgFile)
{
	ASSERT (m_pIecCfgFiles != NULL);
	return m_pIecCfgFiles->AdjustIecCfgFile(pIecfgFile);
}

CIecCfgFile* CIecCfgTool::_NewIecCfgFile(const CString &strFileType)
{
	ASSERT (m_pIecCfgFiles != NULL);
	return m_pIecCfgFiles->NewIecCfgFile(strFileType);
}

CIecCfgFile* CIecCfgTool::_NewIecCfgFile(CXFile *pXFile)
{
	ASSERT (m_pIecCfgFiles != NULL);
	CString strFile = pXFile->GetTotalFileName();

	return _OpenIecFile(strFile);
}

BOOL CIecCfgTool::_IsIecFileOpen(const CString &strFile)
{
	return FALSE;
}

CIecCfgFile* CIecCfgTool::_OpenIecFile(const CString &strFile)
{
	ASSERT (m_pIecCfgFiles != NULL);

	return m_pIecCfgFiles->OpenIecFile(strFile);
}

CIecCfgFile* CIecCfgTool::_FindIecFile(const CString &strFile)
{
	ASSERT (m_pIecCfgFiles != NULL);
	CIecCfgFile *pFile = (CIecCfgFile*)m_pIecCfgFiles->FindByID(strFile);

	return pFile;
}

BOOL CIecCfgTool::_CloseIecFile(CIecCfgFile *pFile, BOOL bDelete)
{
	ASSERT( m_pIecCfgFiles != NULL );

	return m_pIecCfgFiles->CloseIecFile(pFile, bDelete);
}


BOOL CIecCfgTool::_HasFileInFolder(CXFolder *pFolder)
{
	ASSERT (m_pIecCfgFiles != NULL);
	CString strFolder = pFolder->GetFolderPath(TRUE);

	return m_pIecCfgFiles->HasFileInFolder(strFolder);
}

BOOL CIecCfgTool::_SaveIecFile(CIecCfgFile *pFile)
{
	return FALSE;
}


BOOL CIecCfgTool::_SaveAsIecFile(CIecCfgFile *pFile)
{
	return FALSE;
}

void CIecCfgTool::_SetIecCfgSmvRates(CIecCfgSmvRates *pRates, CIecCfgFile *pFile)
{
	m_pIecCfgFiles->SetIecCfgSmvRates(pRates, pFile);
}

void CIecCfgTool::_SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon, CIecCfgFile *pFile)
{
	m_pIecCfgFiles->SetIecCfgSmvCommon(pSmvCommon, pFile);
}
