#include "StdAfx.h"
#include "GuideBook.h"
#include "Device.h"
#include "GuideBookDefine.h"
#include "JobGuide.h"
#include "../../../Module/TestMacro/TestMacroInterface.h"
#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../TCtrlCntrDefine.h"

#ifndef _PSX_QT_LINUX_
#include "MacroCharItems.h"
#endif

#include "../XLanguageResourceAts.h"
#include "../TaskMngr/TestGlobalDefine.h"
#include "../../../Module/DataMngr/DataMngrTrans.h"

#ifndef _PSX_QT_LINUX_
#include "../../../Module/EpotoInterface/EpotoInterface.h"
#include "../FactoryBatchTestMngr.h"
#endif

#include "GuideBookTool.h"
#include "GuideBookExportTool.h"

#include "../../../Module/Encrypt/XDes2.h"

#ifdef GUIDEBOOK_DEV_MODE
#include "../../../Module/LogicShapeMngr/VFlowExec_Visio.h"
#endif

#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long g_nLog_TestControl_Msg   = 0;
//2019-1-6:增加数据对象是否合格的功能   lijq
BOOL g_bAddDataErrorValueToRpt = FALSE;

const CString CGuideBook::g_strTestTypeConfigFile  = _T("TestType.xml");
const CString CGuideBook::g_strCmmCmdConfigFile  = _T("CommCmdConfig.xml");

#define ATS_GUIDEBOOK_INIT_NAME  _T("ATS-Template")

CGuideBook::CGuideBook(void):m_pJobGuide(NULL),m_pItemContainer(NULL)
{
	m_bIsOpenDscFile = FALSE;
	m_bWSetsUseMinMax = TRUE;
	m_nBinOffset = 0;
	m_nBoutOffset = 0;

	Gb_GbDevGlobalDefine_Init();

	m_pGlobalDatas = NULL;
	m_pGbDev = NULL;
	m_pTestAppDefine = NULL;
	m_pTestApp = NULL;
	//m_pTesters = NULL;
	m_strName = ATS_GUIDEBOOK_INIT_NAME;

	m_strDevBy = L"ATS";
	m_strVersion = L"1.0";
	m_strPpTemplateFile=_T("");      //2010-12-1  规约模板
	m_strDeviceModelFile = _T("");		//2010-12-17添加
	m_pTestMacros = NULL;
	m_pScriptLibGlobal = NULL;
	m_pScriptLibLocal = NULL;
	m_strPpEngineProgID = g_strPpEngineProgIDMms;

	m_strCommCmdConfigFile = g_strCmmCmdConfigFile;
	m_strTestTypeFile = g_strTestTypeConfigFile;
	m_bIsInGbWizardState = FALSE;
	m_nTestTimeLong = 0;
	m_bOpenBinaryFileSucc = TRUE;

	m_pTestBeginTime = NULL;
	m_pTestEndTime   = NULL;
	m_nTestControlMode = 0;

#ifdef CGuideBook_with_iecfg_file
	m_pIecCfgDevice = NULL;
	m_pIecfgDataType = NULL;
#endif

	m_pItemsRsltExprScriptMngr = NULL;
	m_pTestGlobalDatasMngr = NULL;
	m_nIsReadOnly = 0;
	m_pExtendRptTemplateDef = NULL;
	m_dwIsTestError = 0;
	m_strScriptMngrFile = GB_ScriptLibrary_Default_File;
	m_nIsSaveRptToDB = 0;

	m_bIsOpenXmlReportFile = FALSE;

	m_nXvmLength = 0;
	m_pXvmTasmBuffer = NULL;
	m_nScriptType = GBSCRIPT_TYPE_ID_LUA;
	m_strScriptType = GBSCRIPT_TYPE_LUA;

	//2021-11-17  lijunqing
	m_nGbDevSaveStruDescFile = 1; 
	m_nGbDevSaveStruDescDsv = 1; 

	m_pHdRes = NULL;
	m_pItemsTec = NULL;
	m_pAinDataMapCfg = NULL;
	////2026-6-18  lijunqing 为了资源申请部分项目的方便，测试完毕，立即从容器去掉当前项目
	m_bCanRemoveItemTestFinished = FALSE;
}

void CGuideBook::InitGuideBookAttrs()
{
	m_strDevBy = L"ATS";
	m_strVersion = L"1.0";
	m_strPpTemplateFile=_T("");      //2010-12-1  规约模板
	m_strDeviceModelFile = _T("");		//2010-12-17添加
	m_pTestMacros = NULL;
	m_pScriptLibGlobal = NULL;
	m_pScriptLibLocal = NULL;
	m_pItemsRsltExprScriptMngr = NULL;
	m_strPpEngineProgID = g_strPpEngineProgIDMms;
	m_strExpandConfigFile.Empty();
	m_strAuthoritySN.Empty();
	m_strAuthorityCop.Empty();
	m_nTestControlMode = 0;
	m_nIsReadOnly = 0;
}

void CGuideBook::OpenCommConfigFile(const CString &strCommConfigFile)
{
	if (strCommConfigFile.GetLength() > 4)
	{
		if (m_strCommCmdConfigFile == strCommConfigFile)
		{
			return;
		}

		m_strCommCmdConfigFile = strCommConfigFile;
	}
	else
	{
		if (m_strCommCmdConfigFile.GetLength() < 4)
		{
			m_strCommCmdConfigFile = g_strCmmCmdConfigFile;
		}
	}

	OpenCommConfigFile();
}

void CGuideBook::OpenCommConfigFile()
{
	//新建模板的时候，不处理
	if (m_strTestMacroFileID.GetLength() <= 2)
	{
		return;
	}

	m_oGbCommCmdConfig.DeleteAll();
	BOOL b = m_oGbCommCmdConfig.OpenXmlFile(TM_GetFileWithPath(m_strTestMacroFileID, m_strCommCmdConfigFile) );

	if (!b)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunSetUnExist.GetString()/*L"通讯配置文件\"%s\"不存在"*/, m_strCommCmdConfigFile.GetString());
	}
}

void CGuideBook::OpenTestTypeConfigFile(const CString &strConfigFile)
{
	if (strConfigFile.GetLength() > 4)
	{
		if (m_strTestTypeFile == strConfigFile)
		{
			return;
		}

		m_strTestTypeFile = strConfigFile;
	}
	else
	{
		m_strTestTypeFile = g_strTestTypeConfigFile;
	}

	OpenTestTypeConfigFile();
}

void CGuideBook::OpenTestTypeConfigFile()
{
	//新建模板的时候，不处理
	if (m_strTestMacroFileID.GetLength() <= 2)
	{
		return;
	}

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += TM_GetFileWithPath(m_strTestMacroFileID, m_strTestTypeFile);

	m_oTestTypes.DeleteAll();
	BOOL b = m_oTestTypes.Open(strFile);

	if (!b)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestTypeUnExist.GetString()/*L"测试类型配置文件\"%s\"不存在"*/, strFile.GetString());
	}
}

void CGuideBook::GetExtendRptFilePath(CStringArray &astrFile)
{
	ASSERT (FALSE);
	CString strTemplatePath;
	strTemplatePath = _P_GetTemplatePath();

	if (m_pExtendRptTemplateDef == NULL)
	{
		return;
	}

	POS pos = m_pExtendRptTemplateDef->GetHeadPosition();
	CDvmData *pRptEx = NULL;
	CString strFile;

	while (pos != NULL)
	{
		pRptEx = (CDvmData *)m_pExtendRptTemplateDef->GetNext(pos);
		GetPathFromRelative(strTemplatePath, pRptEx->m_strName, strFile);
		astrFile.Add(strFile);
	}
}

void CGuideBook::InitTestMacros()
{
	//新建模板的时候，不处理
	if (m_strTestMacroFileID.GetLength() <= 2)
	{
		return;
	}

	m_pTestMacros = TM_GetTestMacros(m_strTestMacroFileID);	//2017-10-29
	//ASSERT (m_pTestMacros != NULL);

//	if (m_pTestMacros != NULL)
//	{//lijq 2020-02-14  更新测试功能类型ID，测试功能类型ID标准化带来的问题
//		if (m_pTestMacros->m_strID != m_strTestMacroFileID)
//		{
//			m_strTestMacroFileID = m_pTestMacros->m_strID;
//		}
//	}

	OpenTestTypeConfigFile();
	OpenCommConfigFile();
}


void CGuideBook::InitGuideBook()
{
	if (m_pItemContainer == NULL)
	{
		m_pItemContainer = new CItemContainer;
	}

	m_pItemContainer->RemoveAll();
	m_pItemContainer->SetGuideBook(this);
}

void Gb_FindAndInitDataset(CDvmLogicDevice *pLdevice, CDvmDataset *pDataset, const CString &strID)
{
	CDvmDataset *pFind = (CDvmDataset*)pLdevice->FindByID(strID);

	if (pFind != NULL)
	{
		pDataset->AppendEx(*pFind);
		pFind->RemoveAll();
	}
}

CString CGuideBook::GetExpandFile()
{
	CString strFile;
	CTestMacrosFile *pFind = TM_GetTestMacrosFile(m_strTestMacroFileID);

	if (pFind == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%s has no expand file"), m_strGuideBookFile.GetString());
		strFile.Empty();
	}
	else
	{
		strFile = pFind->GetTestMacroCfgFile(pFind->ExpandConfigFile(FALSE));
	}

	//2020-02-16  lijq
/*	if (m_strExpandConfigFile.GetLength() < 4)
	{
		CTestMacrosFileMngr *pTestMacroFileMngr = CTestMacrosFileMngr::g_pTestMacrosFileMngr;;
		CTestMacrosFile *pFind = NULL;
		pFind = pTestMacroFileMngr->FindByFile(m_strTestMacroFileID, m_strCommCmdConfigFile);
		
		if (pFind != NULL)
		{
			m_strExpandConfigFile = pFind->ExpandConfigFile(FALSE);
			strFile += pFind->ExpandConfigFile(TRUE);

			if (! IsFileExist(strFile))
			{//2020-01-26:测试功能相关文件进行分路径管理，兼容部分路径管理的模式
				strFile += pFind->ExpandConfigFile(FALSE);
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%s has no expand file"), m_strGuideBookFile);
			strFile.Empty();
		}
	}
	else
	{
		strFile += m_strExpandConfigFile;
	}
*/

	return strFile;
}

void CGuideBook::OpenExpandFile(CDvmDataset *pDataset)
{
	CString strFile = GetExpandFile();

	CTestGlobalDefine oTestDefine;
	BOOL bRet = oTestDefine.OpenXmlFile(strFile, CGbXMLKeys::TestDefineKey(), CGbXMLKeys::g_pGbXMLKeys);

	if (bRet)
	{
		Gb_FindAndInitDataset(&oTestDefine, pDataset, DSID_COMMCMDMCONFIG);
	}
	else
	{
		pDataset->OpenXmlFile(strFile, CGbXMLKeys::g_pGbXMLKeys);
	}
}

void CGuideBook::OpenExpandFile(CDvmDataset *pCmmCmdManyConfig, CDvmDataset *pTestApp, CDvmDataset *pDeviceAttr)
{
	CString strFile = GetExpandFile();

	CTestGlobalDefine oTestDefine;
	BOOL bRet = oTestDefine.OpenXmlFile(strFile, CGbXMLKeys::TestDefineKey(), CGbXMLKeys::g_pGbXMLKeys);

	if (!bRet)
	{
		return;
	}

	Gb_FindAndInitDataset(&oTestDefine, pCmmCmdManyConfig, DSID_COMMCMDMCONFIG);
	Gb_FindAndInitDataset(&oTestDefine, pTestApp, DSID_TESTAPP_DEF);
	Gb_FindAndInitDataset(&oTestDefine, pDeviceAttr, DSID_DEVICEATTR);
}

void CGuideBook::RemoveExpandDatas()
{
	CDvmDataset oDatas;
	OpenExpandFile(&oDatas);
	CExBaseList listDevice;

	SelectChildrenByClassID(listDevice, GBCLASSID_DEVICE);

	POS pos = listDevice.GetHeadPosition();
	CDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CDevice *)listDevice.GetNext(pos);
		pDevice->RemoveExpandDatas(&oDatas);
	}

	listDevice.RemoveAll();
}

void CGuideBook::ImportExpandDatas()
{
	CDvmDataset oDatas;
	OpenExpandFile(&oDatas);
	CExBaseList listDevice;

	SelectChildrenByClassID(listDevice, GBCLASSID_DEVICE);

	POS pos = listDevice.GetHeadPosition();
	CDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CDevice *)listDevice.GetNext(pos);
		pDevice->ImportExpandDatas(&oDatas);
	}

	listDevice.RemoveAll();
}

void CGuideBook::ImportExpandDatas(CDvmDataset *pExpandDatas)
{
	CExBaseList listDevice;

	SelectChildrenByClassID(listDevice, GBCLASSID_DEVICE);

	POS pos = listDevice.GetHeadPosition();
	CDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CDevice *)listDevice.GetNext(pos);
		pDevice->ImportExpandDatas(pExpandDatas);
	}

	listDevice.RemoveAll();
}

void CGuideBook::ImportExpandDatas(CDevice *pDevice)
{
	CDvmDataset oDatas;
	OpenExpandFile(&oDatas);
	pDevice->ImportExpandDatas(&oDatas);
}

void CGuideBook::UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew)
{
	CDevice *pDevice = GetDevice();

	if (pDevice != NULL)
	{
		pDevice->UpdateSysPara(pSrcList, bCreateNew);
	}
}

void CGuideBook::FreeGuideBook()
{
	DeleteAll();
    m_nIndex = 0;
	m_pScriptLibGlobal = NULL;
	m_pScriptLibLocal = NULL;
	m_pItemsRsltExprScriptMngr = NULL;

	m_pJobGuide = NULL;
	m_pGlobalDatas = NULL;
	m_pGbDev = NULL;
	m_pTestAppDefine = NULL;
	m_pTestApp = NULL;
	m_pInitScriptText = NULL;
	m_pResultScriptText = NULL;
	m_pNameScriptText = NULL;
	m_pReports = NULL;
	m_pReportsBack = NULL;
	m_pRptMap = NULL;
    m_pTestEndTime = NULL;
    m_pTestBeginTime = NULL;
	m_pTestGlobalDatasMngr = NULL;
	m_pHdRes = NULL;
	m_pItemsTec = NULL;
	m_pAinDataMapCfg = NULL;

	if (m_pItemContainer != NULL)
	{
		delete m_pItemContainer;
		m_pItemContainer = NULL;
	}
	
	m_oVsdxPagesList.DeleteAll();
}

//形参：pListBk，存放需要保留的测试项目，作为备份
void CGuideBook::FreeGuideBook_ExceptItems(const CString &strItemID, CExBaseList *pListBk)
{
	CExBaseList oList;
	CDevice *pDevice = (CDevice *)GetDevice();

    if(pDevice != NULL)
    {
        Gb_GetAllItemsByID(pDevice, strItemID, oList, GBCLASSID_ITEMS);
    }

	POS pos = oList.GetHeadPosition();
	
	while(pos != NULL)
	{
		CItems *pItems = (CItems *)oList.GetNext(pos);
		CExBaseList *pParent = (CExBaseList *)pItems->GetParent();
		pParent->Remove(pItems);
	}

	pListBk->Append(oList);
	oList.RemoveAll();
	FreeGuideBook();
}

void CGuideBook::SetIecfgFile(const CString &strIecfgFile)
{
// 	m_strIecfgFile = strIecfgFile;

	//自动测试模式下，IecfgFile以二进制文件为参考
	//测试模板编辑模式下，Iecffile以模板文件路径为参考
#ifdef CGuideBook_with_iecfg_file
	CString strFile;
	
	if (strIecfgFile.GetLength() < 3)
	{
		InitByIecfFile();
	}
	else
	{
		if (::IsFileExist(strIecfgFile))
		{
			CString strPath;
			strPath = GetPathFromFilePathName(m_strGuideBookFile);
			GetRelativePathTo(strPath, strIecfgFile, m_strIecfgFile);
		}
	}

	InitByIecfFile();

#endif
}

CString CGuideBook::GetIecfgFile()
{
	CString strFile;

	if (m_strIecfgFile.GetLength() >= 5)
	{
#ifndef _PSX_QT_LINUX_
        TCHAR szOut[MAX_PATH] = _T("");
		CString strPath = GetPathFromFilePathName(m_strGuideBookFile);
		PathCombine(szOut,strPath,m_strIecfgFile);
		strFile = szOut;

		if (IsFileExist(strFile))
		{
			return strFile;
		}

		strPath = GetPathFromFilePathName(m_strGbXmlFile);
		PathCombine(szOut,strPath,m_strIecfgFile);
		strFile = szOut;

		if (IsFileExist(strFile))
		{
			return strFile;
		}

#endif
    }

	return strFile;
}

#ifdef CGuideBook_with_iecfg_file
CString CGuideBook::WriteIecfgTempFile(CMacroTestPara *pPara, const CString &strExp)
{
	CString strFile;

	if (m_strIecfgFile.GetLength() < 5)
	{
		return _T("");
	}

	strFile = GetIecfgFile();

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("测试仪配置文件【%s】不存在"), strFile);
		return _T("");
	}

	if (m_pIecCfgDevice == NULL)
	{
		m_pIecCfgDevice = new CIecCfgDevice;
		m_pIecCfgDevice->OpenIecCfgFile(strFile);
	}

	CIecCfgDatasMngr *pIecfgData = (CIecCfgDatasMngr*)m_pIecCfgDevice->FindByID(strExp);

	if (pIecfgData == NULL)
	{
		pIecfgData = (CIecCfgDatasMngr*)m_pIecCfgDevice->FindByName(strExp);
	}

	ASSERT (pIecfgData != NULL);

	if (pIecfgData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("测试仪配置文件【%s】中配置【%s】不存在"), strFile, strExp);
		strFile.Empty();
	}
	else
	{
		strFile = GetPathFromFilePathName(strFile);
		strFile += strExp;
		strFile = ChangeFilePostfix(strFile, CTestMacrosFileMngr::g_strDefaultIecConfigFile);
		pIecfgData->SaveAsIecCfgFile(strFile);
		
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("测试仪配置文件【%s】中配置【%s】"), m_strIecfgFile, strFile);
	}

	return strFile;
}

void CGuideBook::InitByIecfFile()
{
	CString strIecfgFile = GetIecfgFile();

	if (::IsFileExist(strIecfgFile))
	{
		if (m_pIecCfgDevice == NULL)
		{
			m_pIecCfgDevice = new CIecCfgDevice();
			m_pIecfgDataType = new CDataType();
		}

		m_pIecCfgDevice->DeleteAll();
		m_pIecCfgDevice->OpenIecCfgFile(strIecfgFile);
		m_pIecfgDataType->DeleteAll();
		m_pIecCfgDevice->InitIecfgDataType(m_pIecfgDataType);
	}
}

void CGuideBook::CopyIecCfgFile(const CString &strDestGuideBookFile)
{
	if (m_strIecfgFile.GetLength() == 0)
	{
		return;
	}

	CString strFrom, strTo;
	GetPathFromRelative(m_strGbXmlFile, m_strIecfgFile, strFrom);
	GetPathFromRelative(strDestGuideBookFile, m_strIecfgFile, strTo);
	::CopyFile(strFrom, strTo, TRUE);
}

#endif

CGuideBook::~CGuideBook(void)
{
	if (m_pItemContainer!=NULL)
	{
		delete m_pItemContainer;
	}

	m_pScriptLibGlobal = NULL;
	m_pScriptLibLocal = NULL;
	m_pItemsRsltExprScriptMngr = NULL;

#ifdef CGuideBook_with_iecfg_file
	if (m_pIecCfgDevice != NULL)
	{
		delete m_pIecCfgDevice;
		m_pIecCfgDevice = NULL;
	}

	if (m_pIecfgDataType != NULL)
	{
		delete m_pIecfgDataType;
		m_pIecfgDataType = NULL;
	}
#endif
// 	m_oScriptDataVariables.DeleteAll();

	FreeXvmTasmBuffer();
	m_oVsdxPagesList.DeleteAll();

// 	if (m_pTesters != NULL)
// 	{
// 		delete m_pTesters;
// 		m_pTesters = NULL;
// 	}
}

void CGuideBook::FreeXvmTasmBuffer()
{
	m_nXvmLength = 0;

	if (m_pXvmTasmBuffer != NULL)
	{
		delete m_pXvmTasmBuffer;
		m_pXvmTasmBuffer = NULL;
	}
}

long CGuideBook::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	m_strPpEngineProgID = g_strPpEngineProgID;

	xml_GetAttibuteValue(pGbXmlKeys->m_strMacroFileKey,oNode,m_strTestMacroFileID);
	xml_GetAttibuteValue(pGbXmlKeys->m_strTestTypeFileKey,oNode,m_strTestTypeFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDeviceIDKey,oNode,m_strDevID);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDevByKey,oNode,m_strDevBy);
	xml_GetAttibuteValue(pGbXmlKeys->m_strVersionKey,oNode,m_strVersion);
	xml_GetAttibuteValue(pGbXmlKeys->m_strCommCmdConfigFileKey,oNode,m_strCommCmdConfigFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strScriptMngrFileKey,oNode,m_strScriptMngrFile);

	xml_GetAttibuteValue(pGbXmlKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);

	if (m_strPpEngineProgID == g_strPpEngineProgIDMmsOld)
	{
		m_strPpEngineProgID = g_strPpEngineProgIDMms;
	}

	xml_GetAttibuteValue(pGbXmlKeys->m_strDvmFileKey,oNode,m_strDvmFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strStandNameFileKey,oNode,m_strStandNameFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDeviceModelFileKey,oNode,m_strDeviceModelFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strTestControlModeKey,oNode,m_nTestControlMode);
	xml_GetAttibuteValue(pGbXmlKeys->m_strExpandConfigFileKey,oNode,m_strExpandConfigFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strIecfgFileKey,oNode,m_strIecfgFile);

	xml_GetAttibuteValue(pGbXmlKeys->m_strReadOnlyKey,oNode,m_nIsReadOnly);
	xml_GetAttibuteValue(pGbXmlKeys->m_strSaveRptToDBKey,oNode,m_nIsSaveRptToDB);
	xml_GetAttibuteValue(pGbXmlKeys->m_strAuthoritySNKey,oNode,m_strAuthoritySN);
	xml_GetAttibuteValue(pGbXmlKeys->m_strAuthorityCopKey,oNode,m_strAuthorityCop);

	xml_GetAttibuteValue(pGbXmlKeys->m_strScriptTypeKey,oNode, m_strScriptType);

	//2021-11-17  lijunqing
	xml_GetAttibuteValue(pGbXmlKeys->m_strGbDevSaveStruDescFileKey,oNode, m_nGbDevSaveStruDescFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strGbDevSaveStruDescDsvKey,oNode, m_nGbDevSaveStruDescDsv);
	return 0;
}

long CGuideBook::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pGbXmlKeys->m_strTestTypeFileKey,oElement,m_strTestTypeFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strMacroFileKey,oElement,m_strTestMacroFileID);
	xml_SetAttributeValue(pGbXmlKeys->m_strDeviceIDKey,oElement, m_strDevID);
	xml_SetAttributeValue(pGbXmlKeys->m_strDevByKey,oElement,m_strDevBy);
	xml_SetAttributeValue(pGbXmlKeys->m_strVersionKey,oElement,m_strVersion);
	xml_SetAttributeValue(pGbXmlKeys->m_strCommCmdConfigFileKey,oElement,m_strCommCmdConfigFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strScriptMngrFileKey,oElement,m_strScriptMngrFile);

	xml_SetAttributeValue(pGbXmlKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);

	//2013-4-12
	xml_SetAttributeValue(pGbXmlKeys->m_strDvmFileKey,oElement,m_strDvmFile);

	xml_SetAttributeValue(pGbXmlKeys->m_strStandNameFileKey,oElement,m_strStandNameFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strDeviceModelFileKey,oElement,m_strDeviceModelFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strTestControlModeKey,oElement,m_nTestControlMode);
	xml_SetAttributeValue(pGbXmlKeys->m_strExpandConfigFileKey,oElement,m_strExpandConfigFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strIecfgFileKey,oElement,m_strIecfgFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strReadOnlyKey,oElement,m_nIsReadOnly);
	xml_SetAttributeValue(pGbXmlKeys->m_strSaveRptToDBKey,oElement,m_nIsSaveRptToDB);
	xml_SetAttributeValue(pGbXmlKeys->m_strAuthoritySNKey,oElement,m_strAuthoritySN);
	xml_SetAttributeValue(pGbXmlKeys->m_strAuthorityCopKey,oElement,m_strAuthorityCop);

	xml_SetAttributeValue(pGbXmlKeys->m_strScriptTypeKey,oElement, m_strScriptType);

	//2021-11-17  lijunqing
	xml_SetAttributeValue(pGbXmlKeys->m_strGbDevSaveStruDescFileKey,oElement, m_nGbDevSaveStruDescFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strGbDevSaveStruDescDsvKey,oElement, m_nGbDevSaveStruDescDsv);

	return 0;
}

long CGuideBook::Serialize(CBinarySerialBuffer &oBinaryBuffer)   //lijunqing 2020-07-07
{
	SerializeOwn(oBinaryBuffer);
	SerializeChildren(oBinaryBuffer);

	//XVM脚本
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_nXvmLength);
		BinarySerializeAddBufferLen(oBinaryBuffer,m_nXvmLength);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_40)
		{
			FreeXvmTasmBuffer();
			BinarySerializeRead(oBinaryBuffer,m_nXvmLength);

			if (m_nXvmLength > 0)
			{
				m_pXvmTasmBuffer = new BYTE[m_nXvmLength];
				oBinaryBuffer.ReadBuffer(m_pXvmTasmBuffer, m_nXvmLength, 1);
			}
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_nXvmLength);

		if (m_nXvmLength > 0)
		{
			oBinaryBuffer.WriteBuffer(m_pXvmTasmBuffer, m_nXvmLength);
		}
	}

	if (oBinaryBuffer.IsReadMode())
	{
		InitAfterRead();
	}

	return 0;
}

long CGuideBook::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strDevID);
		BinarySerializeCalLen(oBinaryBuffer,m_strDevBy);
		BinarySerializeCalLen(oBinaryBuffer,m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer,m_strCommCmdConfigFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strPpTemplateFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strDeviceModelFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strTestMacroFileID);
		BinarySerializeCalLen(oBinaryBuffer,m_strTestTypeFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strScriptMngrFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strPpEngineProgID);
		BinarySerializeCalLen(oBinaryBuffer,m_strGuideBookFileType);
		BinarySerializeCalLen(oBinaryBuffer,m_nTestTimeLong);
		BinarySerializeCalLen(oBinaryBuffer,m_strAotuSaveReportFileName);
		BinarySerializeCalLen(oBinaryBuffer,m_nTestControlMode);
		BinarySerializeCalLen(oBinaryBuffer,m_strExpandConfigFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strGbXmlFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strGbXmlFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strIecfgFile);
		BinarySerializeCalLen(oBinaryBuffer,m_nIsSaveRptToDB);
		BinarySerializeCalLen(oBinaryBuffer,m_strAuthoritySN);
		BinarySerializeCalLen(oBinaryBuffer,m_strAuthorityCop);
		BinarySerializeCalLen(oBinaryBuffer,m_strScriptType);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strDevID);
		BinarySerializeRead(oBinaryBuffer,m_strDevBy);
		BinarySerializeRead(oBinaryBuffer,m_strVersion);
		BinarySerializeRead(oBinaryBuffer,m_strCommCmdConfigFile);
		BinarySerializeRead(oBinaryBuffer,m_strPpTemplateFile);
		BinarySerializeRead(oBinaryBuffer,m_strDeviceModelFile);
		BinarySerializeRead(oBinaryBuffer,m_strTestMacroFileID);
		BinarySerializeRead(oBinaryBuffer,m_strTestTypeFile);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_2)
		{
			BinarySerializeRead(oBinaryBuffer,m_strScriptMngrFile);
		}
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_4)
		{
			BinarySerializeRead(oBinaryBuffer,m_strPpEngineProgID);
		}
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_6)
		{
			BinarySerializeRead(oBinaryBuffer,m_strGuideBookFileType);
		}
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_8)
		{
			BinarySerializeRead(oBinaryBuffer,m_nTestTimeLong);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_13)
		{
			BinarySerializeRead(oBinaryBuffer,m_strAotuSaveReportFileName);
		}

		if (m_strPpEngineProgID == g_strPpEngineProgIDMmsOld)
		{
			m_strPpEngineProgID = g_strPpEngineProgIDMms;
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_17)
		{
			BinarySerializeRead(oBinaryBuffer,m_nTestControlMode);
			BinarySerializeRead(oBinaryBuffer,m_strExpandConfigFile);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_22)
		{
			BinarySerializeRead(oBinaryBuffer,m_strGbXmlFile);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_24)
		{
			BinarySerializeRead(oBinaryBuffer,m_strIecfgFile);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_37)
		{
			BinarySerializeRead(oBinaryBuffer,m_nIsSaveRptToDB);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_38)
		{
			BinarySerializeRead(oBinaryBuffer,m_strAuthoritySN);
			BinarySerializeRead(oBinaryBuffer,m_strAuthorityCop);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_40)
		{
			BinarySerializeRead(oBinaryBuffer,m_strScriptType);
		}

		InitScriptTypeID();
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strDevID);
		BinarySerializeWrite(oBinaryBuffer,m_strDevBy);
		BinarySerializeWrite(oBinaryBuffer,m_strVersion);
		BinarySerializeWrite(oBinaryBuffer,m_strCommCmdConfigFile);
		BinarySerializeWrite(oBinaryBuffer,m_strPpTemplateFile);
		BinarySerializeWrite(oBinaryBuffer,m_strDeviceModelFile);
		BinarySerializeWrite(oBinaryBuffer,m_strTestMacroFileID);
		BinarySerializeWrite(oBinaryBuffer,m_strTestTypeFile);
		BinarySerializeWrite(oBinaryBuffer,m_strScriptMngrFile);
		BinarySerializeWrite(oBinaryBuffer,m_strPpEngineProgID);
		BinarySerializeWrite(oBinaryBuffer,m_strGuideBookFileType);
		BinarySerializeWrite(oBinaryBuffer,m_nTestTimeLong);
		BinarySerializeWrite(oBinaryBuffer,m_strAotuSaveReportFileName);
		BinarySerializeWrite(oBinaryBuffer,m_nTestControlMode);
		BinarySerializeWrite(oBinaryBuffer,m_strExpandConfigFile);
		BinarySerializeWrite(oBinaryBuffer,m_strGbXmlFile);
		BinarySerializeWrite(oBinaryBuffer,m_strIecfgFile);
		BinarySerializeWrite(oBinaryBuffer,m_nIsSaveRptToDB); //2019-5-24
		BinarySerializeWrite(oBinaryBuffer,m_strAuthoritySN); //2020-1-28
		BinarySerializeWrite(oBinaryBuffer,m_strAuthorityCop); //2020-1-28
		BinarySerializeWrite(oBinaryBuffer,m_strScriptType); //2020-6-2
	}

	return 0;
}

CExBaseObject* CGuideBook::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pGbXmlKeys->m_strJobGuideKey)
	{
		m_pJobGuide = new CJobGuide;
		return m_pJobGuide;
	}
	else if (strClassID == pGbXmlKeys->CShortDatasKey())
	{
		return new CShortDatas();
	}
	else if (strClassID == pGbXmlKeys->CDvmDatasetKey())
	{
		return new CDvmDataset();
	}
	else if (strClassID == pGbXmlKeys->m_strDeviceKey)
	{
		CDevice* pDevice = new CDevice;
		return pDevice;
	}
	else if (strClassID == pGbXmlKeys->m_strScriptMngrKey)
	{
		CScriptTextMngr *pScriptMngr = new CScriptTextMngr();
		return pScriptMngr;
	}
	else if (strClassID == pGbXmlKeys->m_strTestGlobalDatasMngrKey)
	{
		CTestGlobalDatasMngr *pGlobalDatasMngr = new CTestGlobalDatasMngr();
		return pGlobalDatasMngr;
	}
	else if (strClassID == pGbXmlKeys->m_strCDataGroupKey)
	{
		CDataGroup *p = new CDataGroup();
		return p;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}


void CGuideBook::InitAfterReadGb()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CExBaseList listDatas;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_JOBGUIDE:
			m_pJobGuide = (CJobGuide*)p;
			break;
		case GBCLASSID_SCRIPT_TEXT_MNGR:
			m_pScriptLibLocal = (CScriptTextMngr *)p;
			break;

		case DTMCLASSID_CSHORTDATAS:
			listDatas.AddTail(p);
			RemoveAt(posPrev);
			break;

		case DVMCLASSID_CDVMDATASET:
			if (p->m_strID ==g_strGbGlobalDatasID )
			{
				m_pGlobalDatas = (CDvmDataset *)p;
				//m_pGlobalDatas->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			}
			else if (p->m_strID == DSID_TESTAPP_DEF)
			{
				m_pTestAppDefine = (CDvmDataset *)p;
				m_pTestAppDefine->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			}
			else if (p->m_strID == DSID_TESTAPP)
			{
				m_pTestApp = (CDvmDataset *)p;
				m_pTestApp->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			}
			else if (p->m_strID == DSID_EXTEND_RPT_TEMPLATE_DEF)
			{
				m_pExtendRptTemplateDef = (CDvmDataset *)p;
				m_pExtendRptTemplateDef->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			}
			else if (p->m_strID == g_strGbDevForAuthority)
			{
				m_pGbDev = (CDvmDataset *)p;
			}
			else
			{
				m_pGlobalDatas = (CDvmDataset *)p;
				//m_pGlobalDatas->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			}
			break;

		case GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR:
			m_pItemsRsltExprScriptMngr = (CItemsRsltExprScriptMngr *)p; 
			break;

		case GBCLASSID_TESTGLOBALDATASMNGR:
			m_pTestGlobalDatasMngr = (CTestGlobalDatasMngr *)p;
			break;

		case DTMCLASSID_CDATAGROUP:
			if (p->m_strID == ID_HD_RES)
			{
				m_pHdRes = (CDataGroup *)p;
			}
			else if (p->m_strID == ID_ITEMS_TEC)
			{
				m_pItemsTec = (CDataGroup *)p;
			}
			else if (p->m_strID == ID_AIN_DATA_MAP_CFG)
			{
				m_pAinDataMapCfg = (CDataGroup *)p;
			}

			break;

		default:
			break;
		}
	}

	InitGlobalDatas(listDatas);
	listDatas.DeleteAll();

// 	if (m_pTesters == NULL)
// 	{
// 		m_pTesters = new CDvmDataset();
// 		m_pTesters->m_strName.Format(_T("测试人员定义"));
// 		m_pTesters->m_strID.Format(_T("Testers"));
// 		AddNewChild(m_pTesters);
// 	}

	if (m_pJobGuide == NULL)
	{
		m_pJobGuide = new CJobGuide;
		AddNewChild(m_pJobGuide);
	}

	if (m_pScriptLibLocal == NULL)
	{
		m_pScriptLibLocal = new CScriptTextMngr();
		AddNewChild(m_pScriptLibLocal);
	}

	if (m_pItemsRsltExprScriptMngr == NULL)
	{
		m_pItemsRsltExprScriptMngr = new CItemsRsltExprScriptMngr();
		AddNewChild(m_pItemsRsltExprScriptMngr);
	}

	m_pScriptLibGlobal = CScriptTextMngrGlobalPool::CreateScriptTextMngr(m_strScriptMngrFile);
//	m_strScriptMngrFile = m_pScriptLibGlobal->m_strScriptMngrFile;

	BringToHead(m_pScriptLibLocal);
	BringToHead(m_pItemsRsltExprScriptMngr);
	BringToHead(m_pJobGuide);
	BringToHead(m_pGlobalDatas);
	BringToHead(m_pTestAppDefine);

	//2020-01-29  lijq  模板加密
	InitGbDev();
	BringToHead(m_pGbDev);

	InitTestMacros();

	if (CGbParaTypeMngr::GetPpEngineType()->FindByID(m_strPpEngineProgID) == NULL)
	{
		m_strPpEngineProgID = g_strPpEngineProgID;
	}

	InitCanRemoveItemTestFinished();
}

void CGuideBook::InitCanRemoveItemTestFinished()
{
	CDevice *pDevice = GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	m_bCanRemoveItemTestFinished = FALSE;
	CDataObj *pPara = (CDataObj*)pDevice->m_pSysParas->FindByID(SYS_PARAID_CanRemoveItemTesteFinished);

	if (pPara == NULL)
	{
		return;
	}

	if (pPara->m_strValue == _T("0"))
	{
		m_bCanRemoveItemTestFinished = FALSE;
	}
	else
	{
		m_bCanRemoveItemTestFinished = TRUE;
	}
}

//离线测试模式   2021-1-20   lijunqing
BOOL CGuideBook::IsOfflineTestMode()
{
	if (m_pGlobalDatas == NULL)
	{
		return FALSE;
	}

	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(g_strAtsOfflineTestMode);

	if (pFind == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

void CGuideBook::SetOfflineTestMode(BOOL bIsOfflineTestMode)
{
	if (m_pGlobalDatas == NULL)
	{
		return;
	}

	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(g_strAtsOfflineTestMode);

	if (pFind == NULL)
	{
		if (!bIsOfflineTestMode)
		{
			return;
		}

		pFind = (CDvmData*)m_pGlobalDatas->AddNewData(g_strAtsOfflineTestMode, g_strAtsOfflineTestMode, _T("long"), _T("0"));
	}
	else
	{
		if (!bIsOfflineTestMode)
		{
			m_pGlobalDatas->Remove(pFind);
			return;
		}
	}

	pFind->m_strValue = _T("0");
}

BOOL CGuideBook::IsOfflineTestMode_Test()
{
	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(g_strAtsOfflineTestMode);

	if (pFind == NULL)
	{
		return FALSE;
	}

	return pFind->m_strValue == _T("0");
}

BOOL CGuideBook::IsOfflineTestMode_ImportResult()
{
	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(g_strAtsOfflineTestMode);

	if (pFind == NULL)
	{
		return FALSE;
	}

	return pFind->m_strValue == _T("1");
}

BOOL CGuideBook::SetOfflineTestMode_Test()
{
	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(g_strAtsOfflineTestMode);

	if (pFind == NULL)
	{
		return FALSE;
	}

	pFind->m_strValue = _T("0");

	return TRUE;
}

BOOL CGuideBook::SetOfflineTestMode_ImportResult()
{
	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(g_strAtsOfflineTestMode);

	if (pFind == NULL)
	{
		return FALSE;
	}

	pFind->m_strValue = _T("1");

	return TRUE;
}

void CGuideBook::InitGlobalDatas(CExBaseList &listDatas)
{
	GetGlobalDatas(TRUE);
	GetTestAppDefine(TRUE);

	POS pos = listDatas.GetHeadPosition();
	CShortDatas *pDatas = NULL;

	while (pos != NULL)
	{
		pDatas = (CShortDatas *)listDatas.GetNext(pos);

		if (pDatas->m_strID ==g_strGbGlobalDatasID )
		{
			Append_Datas(m_pGlobalDatas, pDatas, FALSE);
		}
		else if (pDatas->m_strID == DSID_TESTAPP_DEF)
		{
			Append_Datas(m_pTestAppDefine, pDatas, FALSE);
		}
		else
		{
			Append_Datas(m_pGlobalDatas, pDatas, FALSE);
		}
	}
}

void CGuideBook::InitAfterReadGbt()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_JOBGUIDE:
			m_pJobGuide = (CJobGuide*)p;
			break;
		case GBCLASSID_SCRIPT_TEXT_MNGR:
			m_pScriptLibLocal = (CScriptTextMngr *)p;
			break;

		case DTMCLASSID_CSHORTDATAS:
			DeleteAt(posPrev);
			break;
		case DVMCLASSID_CDVMDATASET:
			if (p->m_strID == g_strGbDevForAuthority)
			{
				m_pGbDev = (CDvmDataset *)p;
			}
			else
			{
				DeleteAt(posPrev);
			}
			break;
		
		case GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR:
			m_pItemsRsltExprScriptMngr = (CItemsRsltExprScriptMngr *)p; 
			break;

		default:
			break;
		}
	}

	if (m_pJobGuide != NULL)
	{
		Delete(m_pJobGuide);
		m_pJobGuide = NULL;
	}

	if (m_pScriptLibLocal == NULL)
	{
		m_pScriptLibLocal = new CScriptTextMngr();
		AddNewChild(m_pScriptLibLocal);
	}

	if (m_pItemsRsltExprScriptMngr == NULL)
	{
		m_pItemsRsltExprScriptMngr = new CItemsRsltExprScriptMngr();
		AddNewChild(m_pItemsRsltExprScriptMngr);
	}

	m_pScriptLibGlobal = CScriptTextMngrGlobalPool::CreateScriptTextMngr(m_strScriptMngrFile);
	m_strScriptMngrFile = m_pScriptLibGlobal->m_strScriptMngrFile;


	BringToHead(m_pScriptLibLocal);
	BringToHead(m_pItemsRsltExprScriptMngr);

	//2020-01-29  lijq  模板加密
	InitGbDev();
	BringToHead(m_pGbDev);

	InitTestMacros();
}

void CGuideBook::InitAfterRead()
{
	InitScriptTypeID();

	CGbItemBase::InitAfterRead();

	if (m_bIsOpenXmlReportFile)
	{
		return;
	}

	if (m_bIsOpenDscFile)
	{
		return;
	}

	if ( TM_IsTestMacroFile(m_strTestMacroFileID) )
	{
		CTestMacrosFile *pMacroFile = CTestMacrosFileMngr::g_pTestMacrosFileMngr->FindByFile(m_strTestMacroFileID);

		if (pMacroFile != NULL)
		{
			m_strTestMacroFileID = pMacroFile->m_strID;
		}
	}

	CTestMacrosFile *pMacroFile = (CTestMacrosFile *)CTestMacrosFileMngr::g_pTestMacrosFileMngr->FindByID(m_strTestMacroFileID);

	if (pMacroFile != NULL)
	{
		m_strCommCmdConfigFile = pMacroFile->CmmFile(FALSE);
	}

	if (m_strGuideBookFileType == g_strTGbFileFilter)
	{
		InitAfterReadGbt();
	}
	else if (m_strGuideBookFileType == g_strGbFileFilter)
	{
		InitAfterReadGb();
	}
	else
	{
		m_strGuideBookFileType = g_strGbFileFilter;
		InitAfterReadGb();
	}
//	CString strIecfgFile = GetIecfgFile();
//	SetIecfgFile(strIecfgFile);
}


BOOL CGuideBook::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_DEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGuideBook::CreateNewChild(long nClassID)
{
	if (nClassID==GBCLASSID_DEVICE)
	{
		CDevice* pObject = new CDevice;
		return pObject;
	}
	else if (nClassID == GBCLASSID_JOBGUIDE)
	{
		m_pJobGuide = new CJobGuide;
		return m_pJobGuide;
	}
	else if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		return new CShortDatas;
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		return new CDvmDataset;
	}
	else if (nClassID == GBCLASSID_SCRIPT_TEXT_MNGR)
	{
		CScriptTextMngr *pScriptMngr = new CScriptTextMngr();
		return pScriptMngr;
	}
	else if (nClassID == GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR)
	{
		CItemsRsltExprScriptMngr *pScriptMngr = new CItemsRsltExprScriptMngr();
		return pScriptMngr;
	}
	else if (nClassID == 0x00030061)
	{//GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR有BaseObject变为List   2017-7-14，兼容老版本的错误
		CItemsRsltExprScriptMngr *pScriptMngr = new CItemsRsltExprScriptMngr();
		return pScriptMngr;
	}
	else if (nClassID == GBCLASSID_TESTGLOBALDATASMNGR)
	{
		CTestGlobalDatasMngr *pGlobalDatasMngr = new CTestGlobalDatasMngr();
		return pGlobalDatasMngr;
	}
	else if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		CDataGroup *p = new CDataGroup();
		return p;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

void CGuideBook::SetGuideBookName(const CString &strName)
{
	m_strName = strName;
	m_strID = strName;

	CDevice *pDevice = GetDevice();
	pDevice->m_strName = strName;
	pDevice->m_strID = strName;

	CCpus *pCpus = pDevice->GetCpus();

	if (pCpus != NULL)
	{
		pCpus->m_strID = strName;
		pCpus->m_strName = strName;
	}
}

void CGuideBook::SetBinaryFileName(const CString &strName)
{
// 	CTestControlBase *pTestControl = (CTestControlBase *)GetParent();
// 
// 	if (pTestControl == NULL)
// 	{
// 		return;
// 	}
// 
// 	pTestControl->SetBinaryFile(strName);
}

CExBaseObject* CGuideBook::GetJobGuide()
{
	return m_pJobGuide;
}

CDvmDataset* CGuideBook::GetGlobalDatas(BOOL bCreate)
{
	if (bCreate)
	{
		if (m_pGlobalDatas == NULL)
		{
			m_pGlobalDatas = new CDvmDataset();
			AddNewChild(m_pGlobalDatas);
			m_pGlobalDatas->m_strID = g_strGbGlobalDatasID;
			m_pGlobalDatas->m_strName = g_sLangTxt_GlobalData;
			//m_pGlobalDatas->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			BringToHead(m_pGlobalDatas);
		}

		//InitGlobalDatas();
		AddGlobalDatas();
	}

	if (m_pGlobalDatas == NULL)
	{
		return NULL;
	}

	if (m_pTestBeginTime == NULL)
	{
		m_pTestBeginTime = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestBeginTime);
	}

	return m_pGlobalDatas;
}

CDvmDataset* CGuideBook::GetTestAppDefine(BOOL bCreate)
{
	if (bCreate)
	{
		if (m_pTestAppDefine == NULL)
		{
			m_pTestAppDefine = new CDvmDataset();
			AddNewChild(m_pTestAppDefine);
			m_pTestAppDefine->m_strID = DSID_TESTAPP_DEF;
			m_pTestAppDefine->m_strName = g_sLangTxt_TestAppDef;
			m_pTestAppDefine->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			BringToHead(m_pTestAppDefine);
		}
	}

	return m_pTestAppDefine;
}

CDvmDataset* CGuideBook::GetTestApp(BOOL bCreate)
{
	if (bCreate)
	{
		if (m_pTestApp == NULL)
		{
			m_pTestApp = new CDvmDataset();
			m_pTestApp->m_strID = DSID_TESTAPP;
			m_pTestApp->m_strName.Empty();
			m_pTestApp->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			AddNewChild(m_pTestApp);
			BringToHead(m_pTestApp);
		}
	}

	return m_pTestApp;
}

//2023-6-17  lijunqing
CDataGroup* CGuideBook::GetTestApps(BOOL bCreate)
{
	GetTestGlobalDatasMngr();

	return m_pTestGlobalDatasMngr->GetTestApps(bCreate);
}

CDvmDataset* CGuideBook::FindGlobalDataset(const CString &strID)
{
	if (DSID_TESTAPP_DEF == strID)
	{
		return m_pTestApp;
	}
	else
	{
		return NULL;
	}
}

CDvmDataset* CGuideBook::GetExtendRptTemplateDef(BOOL bCreate)
{
	if (bCreate)
	{
		if (m_pExtendRptTemplateDef == NULL)
		{
			m_pExtendRptTemplateDef = new CDvmDataset();
			m_pExtendRptTemplateDef->m_strID = DSID_EXTEND_RPT_TEMPLATE_DEF;
			m_pExtendRptTemplateDef->m_strName = DSID_EXTEND_RPT_TEMPLATE_DEF;
			m_pExtendRptTemplateDef->m_strDataType = CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;
			AddNewChild(m_pExtendRptTemplateDef);
			BringToHead(m_pExtendRptTemplateDef);
		}
	}

	return m_pExtendRptTemplateDef;
}

CExBaseObject* CGuideBook::GetItemContainer()
{
	if (m_pItemContainer == NULL)
	{
		m_pItemContainer = new CItemContainer;
	}

	return m_pItemContainer;
}

CScriptText* CGuideBook::FindScriptText(const CString &strID)
{
	CScriptText *pFind = NULL;

	if (m_pScriptLibGlobal != NULL)
	{
		pFind = (CScriptText *)m_pScriptLibGlobal->FindByID(strID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}
	
	pFind = (CScriptText *)m_pScriptLibLocal->FindByID(strID);

	return pFind;
}

CItemsRsltExprScript* CGuideBook::FindItemsRsltExprScript(const CString &strID)
{
	CItemsRsltExprScript *pFind = NULL;

	pFind = (CItemsRsltExprScript *)m_pItemsRsltExprScriptMngr->FindByID(strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = (CItemsRsltExprScript *)m_pItemsRsltExprScriptMngr->FindByID(strID);

	return pFind;
}

long CGuideBook::GetScriptLibItems()
{
	long nCount = 0;
	
	if (m_pScriptLibGlobal != NULL)
	{
		nCount += m_pScriptLibGlobal->GetCount();
	}

	nCount += m_pScriptLibLocal->GetCount();

	return nCount;
}

long CGuideBook::Open(const CString &strFile, BOOL bOnlyReadAttr)
{
	m_strGuideBookFile = strFile;

	long nResult = 0;
	long nPos = strFile.ReverseFind('.');

	if (nPos > 0)
	{
		CString strTemp = strFile.Mid(nPos+1);
		strTemp.MakeLower();

		if (strTemp == g_strGbFileFilter || strTemp == g_strTGbFileFilter)
		{
			m_strGbXmlFile = strFile;
			m_strGbXmlFile.MakeLower();
			nResult = OpenXMLFile(strFile, bOnlyReadAttr);
		}
		else
		{
			nResult = OpenBinaryFile(strFile, 0);
		}
	}
	else
	{
		nResult = -1;
	}

	return nResult;
}


CString ats_GetBinaryTempFile(CGbItemBase* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CString strTempFilePath = pGuideBook->GetItemTempPath();

	return ats_GetBinaryTempFile(strTempFilePath, pItem);
}

CString ats_GetBinaryTempFile(const CString strTempFilePath, CGbItemBase* pItem)
{
	CString strTempFileName;
    strTempFileName.Format(_T("%s%d.%s"), strTempFilePath.GetString(), pItem->m_nIndex, g_strTempGuideBookBinaryPostfix.GetString());

	return strTempFileName;
}

void gb_ClearReportDatasByMap(CGbItemBase *pItem, const CString &strTempFilePath, BOOL bIsWriteTestTempFile)
{
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pItem);
	CString strXmlFile = ChangeFilePostfix(strTempFileName, _T("xml"));

	if (IsFileExist(strTempFileName) || IsFileExist(strXmlFile))
	{
		CReport *pReport = NULL;
		CReports *pReports = pItem->GetReports();
		POS pos = pReports->GetHeadPosition();

		while (pos != NULL)
		{
			pReport = (CReport *)pReports->GetNext(pos);
			pReport->ClearReportDatasByMap();
		}
	}
}

void gb_ClearItemInDbState(CGbItemBase *pItem, const CString &strTempFilePath, BOOL bIsWriteTestTempFile)
{
	//gb_ClearReportDatasByMap(pItem, strTempFilePath, bIsWriteTestTempFile);
	pItem->ClearItemInDbState();
}

void gb_ClearReportDatasByMap(CExBaseList *pList, const CString &strTempFilePath, BOOL bIsWriteTestTempFile)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID  = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			pItem = (CGbItemBase *)p;
			gb_ClearReportDatasByMap(pItem, strTempFilePath, bIsWriteTestTempFile);
			gb_ClearReportDatasByMap((CExBaseList*)p, strTempFilePath, bIsWriteTestTempFile);
		}
		else if (Gb_IsItemsBaseClassID(nClassID))
		{
			gb_ClearReportDatasByMap((CExBaseList*)p, strTempFilePath, bIsWriteTestTempFile);
		}
	}
}

void gb_ClearItemInDbState(CExBaseList *pList, const CString &strTempFilePath, BOOL bIsWriteTestTempFile)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID  = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			pItem = (CGbItemBase *)p;
			gb_ClearItemInDbState(pItem, strTempFilePath, bIsWriteTestTempFile);
			gb_ClearItemInDbState((CExBaseList*)p, strTempFilePath, bIsWriteTestTempFile);
		}
		else if (Gb_IsItemsBaseClassID(nClassID))
		{
			gb_ClearItemInDbState((CExBaseList*)p, strTempFilePath, bIsWriteTestTempFile);
		}
	}
}

void gb_CalSize(CGuideBook *pGuideBook)
{
	long nObjCount = 0, nTotalSize=0;
	CString strFile = pGuideBook->m_strGuideBookFile;
	strFile = ChangeFilePostfix(strFile, _T("txt"));
	CFile oFile;

	if (oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		pGuideBook->CalObjSize(TRUE, nObjCount, nTotalSize, &oFile);
		CString strMsg;
		strMsg.Format(_T("nObjCount=%d   nTotalSize=%d\r\n"), nObjCount, nTotalSize);
        oFile.Write(strMsg.GetString(), strMsg.GetLength());
		oFile.Close();
	}
}

long CGuideBook::OpenBinaryFile(const CString &strFile, long nRWReportFileMode, BOOL bOnlyReadAttr)
{
	m_bOpenBinaryFileSucc = TRUE;
	FreeGuideBook();

	m_strGuideBookFile = strFile;

	CBinarySerialBuffer *pBuffer = NULL;

	if (nRWReportFileMode == 0)
	{
		pBuffer = new CBinarySerialBuffer();
	}
	else
	{
		pBuffer = new CBinarySerialBuffer(SERIAL_BUFFER_MODE_SHAREMEM);
	}

	Gb_InitGuideBookFileVersion(*pBuffer);
	pBuffer->ResetVersion();

	m_bOpenBinaryFileSucc = pBuffer->OpenFromFile(strFile);

	if (!m_bOpenBinaryFileSucc)
	{
		delete pBuffer;
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Opem file [%s] failed..."), strFile.GetString());
		return m_bOpenBinaryFileSucc;
	}

	pBuffer->SetReadMode();
	pBuffer->ReadVersion();
	pBuffer->SetVersionFindByID(g_dwDataMngrVersionID);

	try
	{
		Serialize(*pBuffer);
	}
	catch (...)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FileRightError.GetString()/*_T("文件【%s】版本错误！")*/, strFile.GetString());
		m_bOpenBinaryFileSucc = FALSE;
	}

	//2019-4-27  lijunqing   修改为测试前再初始化
	InitGuideBook();
	Gb_SetGbModifiedFlag(this, FALSE);
	InitTestError(NULL);

#ifdef _DEBUG
	gb_CalSize(this);
#endif
	
	delete pBuffer;
	return m_bOpenBinaryFileSucc;
}

BOOL CGuideBook::IsTestError()
{
	return (m_dwIsTestError > 0);
}

void CGuideBook::InitTestError(CDvmData *pData)
{
	CDvmData *pCommError = NULL;
	
	if (pData == NULL)
	{
		if (m_pGlobalDatas != NULL)
		{
			pCommError = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestError);
		}
	}
	else
	{
		pCommError = pData;
	}

	if (pCommError == NULL)
	{
		return ;
	}

	if (pCommError->m_strValue.GetLength() > 0)
	{
		m_dwIsTestError = 1;
	}
	else
	{
		m_dwIsTestError = 0;
	}
}

long CGuideBook::SaveBinaryFile(const CString &strFile, long nRWReportFileMode)
{
	if (!m_bOpenBinaryFileSucc)
	{
		return 0;
	}

	if (!Gb_GetGbModifiedFlag(this))
	{
		return 0;
	}

	m_strGuideBookFile = strFile;
	CBinarySerialBuffer *pBuffer = NULL;

	if (nRWReportFileMode == 0)
	{
		pBuffer = new CBinarySerialBuffer();
	}
	else
	{
		pBuffer = new CBinarySerialBuffer(SERIAL_BUFFER_MODE_SHAREMEM);
	}

	Gb_InitGuideBookFileVersion(*pBuffer);
	pBuffer->SetVersionFindByID(g_dwDataMngrVersionID);

	pBuffer->SetCalSizeMode();
	Serialize(*pBuffer);
	pBuffer->WriteVersion();
    pBuffer->AllocBuffer(2);
	pBuffer->CreateFile(strFile);

	pBuffer->SetWriteMode();
	pBuffer->WriteVersion();
	Serialize(*pBuffer);

	pBuffer->SaveToFile(strFile);
//    long nCalLen = pBuffer->Tell();
//    long nLenEnd = pBuffer->Tell_Curr_to_End();

	delete pBuffer;

	Gb_SetGbModifiedFlag(this, FALSE);

	return 0;
}

void CGuideBook::ReadAttr(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	FreeGuideBook();
	XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	CXmlRWNodeListBase *oNodes = oNode.GetChildNodes();
	long nCount = oNodes->GetNodeNum();
	long nIndex = 0;
	CXmlRWNodeBase *oChild = NULL;
	BOOL bAddToTail = TRUE;
	CDevice *pDevice = NULL;
	CString strID, strNodeName;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oChild = oNodes->GetChild(nIndex);
		strNodeName = oChild->GetNodeName();

		if (strNodeName == CGbXMLKeys::g_pGbXMLKeys->m_strCDvmDatasetKey)
		{//读取加密信息数据对象
			

			xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIDKey, *((CXmlRWElementBase*)oChild),strID);

			if ( strID == g_strGbDevForAuthority) 
			{
				if (m_pGbDev != NULL)
				{
					continue;
				}

				m_pGbDev = new CDvmDataset();
				AddNewChild(m_pGbDev);
				m_pGbDev->XmlRead(*oChild, pXmlRWKeys);
			}
			else if (strID == g_strGbGlobalDatasID)
			{//2021-1-22  lijunqing 全局信息
				if (m_pGlobalDatas != NULL)
				{
					continue;
				}

				m_pGlobalDatas =  new CDvmDataset();
				AddNewChild(m_pGlobalDatas);
				m_pGlobalDatas->XmlRead(*oChild, pXmlRWKeys);
			}

			continue;
		}

		if (strNodeName == CGbXMLKeys::g_pGbXMLKeys->m_strDeviceKey)
		{
			pDevice = new CDevice;
			pDevice->SetParent(this);
			AddNewChild(pDevice);
			pDevice->ReadAttr(*oChild, pXmlRWKeys);
			continue;
		}

	}
}

long CGuideBook::OpenXMLFile(const CString &strFile, BOOL bOnlyReadAttr,const long &nXmlRWType)
{
	FreeGuideBook();

	m_strGbXmlFile = strFile;
	m_strGuideBookFile = strFile;
	m_strGbXmlFile.MakeLower();
	m_strGuideBookFile.MakeLower();
	CGbXMLKeys::g_pGbXMLKeys->m_nIsGroupUseDvmData++;

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	if (!xml_OpenFile(pRWDoc, strFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_OpenMsxmlFail.GetString() /*_T("MSXML2打开文件【%s】失败")*/, strFile.GetString());
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(CGbXMLKeys::g_pGbXMLKeys->m_strGuideBookKey);

	if(!pDocRoot->IsValid())
	{
		CGbXMLKeys::g_pGbXMLKeys->m_nIsGroupUseDvmData--;
		return FALSE;
	}

	if (bOnlyReadAttr)
	{
		ReadAttr(*pDocRoot,CGbXMLKeys::g_pGbXMLKeys);
		InitTestMacros();
	}
	else
	{
		dvm_IncGroupUseDvmData(CGbXMLKeys::g_pGbXMLKeys);
		XmlRead(*pDocRoot,CGbXMLKeys::g_pGbXMLKeys);
		dvm_DecGroupUseDvmData(CGbXMLKeys::g_pGbXMLKeys);
	}

	//InitGuideBook();

	//打开对应的逻辑图
	OpenVisioFile(strFile);

	CString strFileType = Gb_GetGuideBookFileType(strFile);
	ASSERT (strFileType == m_strGuideBookFileType);

	delete pRWDoc;

	CGbXMLKeys::g_pGbXMLKeys->m_nIsGroupUseDvmData--;
	return TRUE;
}

long CGuideBook::OpenXMLFile_DscFile(const CString &strFile, const long &nXmlRWType)
{
	m_bIsOpenDscFile = TRUE;
	FreeGuideBook();

	m_strGbXmlFile = strFile;
	m_strGuideBookFile = strFile;
	m_strGbXmlFile.MakeLower();
	m_strGuideBookFile.MakeLower();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	if (!xml_OpenFile(pRWDoc, strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_OpenMsxmlFail.GetString() /*_T("MSXML2打开文件【%s】失败")*/, strFile.GetString());
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(CGbXMLKeys::g_pGbXMLKeys->m_strGuideBookKey);

	if(!pDocRoot->IsValid())
	{
		return FALSE;
	}

	XmlRead(*pDocRoot,CGbXMLKeys::g_pGbXMLKeys);
	delete pRWDoc;
	return TRUE;
}

long CGuideBook::OpenVisioFile(const CString &strFile)
{
	//测试模板编辑时，仅需要打开逻辑图文件，获取其中的页面链表即可
#ifdef GUIDEBOOK_DEV_MODE
	CVFlowExec_Visio oVisio;
	CString strVisio = ChangeFilePostfix(strFile, g_strGbVisioFileFilter);

	if (IsFileExist(strVisio))
	{
		if (oVisio.OpenVisioFile(strVisio, FALSE))
		{
			CExBaseList *pList = oVisio.GetPagesList();

			m_oVsdxPagesList.DeleteAll();
			CExBaseObject *pObj = new CExBaseObject;
			m_oVsdxPagesList.AddNewChild(pObj);
			m_oVsdxPagesList.AppendClone(pList);

			//关闭visio文档，关闭Visio进程
			oVisio.CloseFile();
			oVisio.QuitApp();
		}
	}
#endif

	return TRUE;
}

long CGuideBook::OpenXmlReportFile(const CString &strFile,const long &nXmlRWType)
{
	m_bIsOpenXmlReportFile = TRUE;
	FreeGuideBook();

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
	
	if (!xml_OpenFile(pRWDoc, strFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_OpenMsxmlFail.GetString() /*_T("MSXML2打开文件【%s】失败")*/, strFile.GetString());
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(CGbXMLKeys::g_pGbXMLKeys->m_strGuideBookKey);


	if(pDocRoot == NULL)
	{
		return FALSE;
	}

	XmlRead(*pDocRoot,CGbXMLKeys::g_pGbXMLKeys);

	return TRUE;
}

long CGuideBook::SaveXMLFile(const CString &strFile)
{
	ValidateGbName();
	SaveXmlFile(strFile, CGbXMLKeys::g_pGbXMLKeys);

	if (m_pScriptLibGlobal != NULL)
	{
		m_pScriptLibGlobal->SaveScriptMngrFile(m_strScriptMngrFile);
	}

	return 1;
}

long CGuideBook::SaveFinalXMLReport(const CString &strFile)
{
/*
	g_bGbExportXmlReportFile = TRUE;

	SaveXmlFile(strFile, CGbXMLKeys::g_pGbXMLKeys);

	g_bGbExportXmlReportFile = FALSE;
*/

	//2021-1-2  lijunqing
	g_bGbExportXmlReportFile = TRUE;
	CGuideBookExportTool oTool;
	oTool.ExportGuideBook(this, strFile);
	g_bGbExportXmlReportFile = FALSE;

	return 0;
}


long CGuideBook::BuildGbexe()
{
	CString strFile = ChangeFilePostfix(m_strGbXmlFile, g_strGbTemplateExeFileFilter);

	Gb_SetGbModifiedFlag(this, TRUE);
	SaveBinaryFile(strFile, 0);

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build template exe file: %s"), strFile.GetString());

	return 0;
}


BOOL CGuideBook::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CGuideBook* pGuideBook = (CGuideBook*)pDesObj;
	pGuideBook->m_strDevID = m_strDevID;
	pGuideBook->m_strDevBy = m_strDevBy;
	pGuideBook->m_strPpTemplateFile = m_strPpTemplateFile;
    pGuideBook->m_strTestMacroFileID = m_strTestMacroFileID;
    pGuideBook->m_strExpandConfigFile = m_strExpandConfigFile;
    pGuideBook->m_strDeviceModelFile = m_strDeviceModelFile;
    pGuideBook->m_nTestControlMode = m_nTestControlMode;
    pGuideBook->m_strTestTypeFile = m_strTestTypeFile;
    pGuideBook->m_strDvmFile = m_strDvmFile;
    pGuideBook->m_strStandNameFile = m_strStandNameFile;
    pGuideBook->m_strScriptMngrFile = m_strScriptMngrFile;
    pGuideBook->m_strPpEngineProgID = m_strPpEngineProgID;
    pGuideBook->m_strIecfgFile = m_strIecfgFile;
    pGuideBook->m_strGuideBookFileType = m_strGuideBookFileType;
    pGuideBook->m_strGbXmlFile = m_strGbXmlFile;
    pGuideBook->m_strGuideBookFile = m_strGuideBookFile;
	
	CExBaseObject::CopyOwn(pGuideBook);

	return TRUE;
}

CBaseObject* CGuideBook::Clone()
{
	CGuideBook* pGuideBook = new CGuideBook();
	Copy(pGuideBook);

	return pGuideBook;
}


CDevice* CGuideBook::GetDevice()
{
	CExBaseList oListDevice;
	long nCount = GetDevice(oListDevice);

	CDevice *pDevice = (CDevice*)oListDevice.GetHead();
	oListDevice.RemoveAll();

	return pDevice;
}

BOOL CGuideBook::Is61850Protocol()
{
	if (m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CGuideBook::IsScriptTextExist(CScriptText *pScriptText)
{
	//ASSERT (m_pScriptLibGlobal != NULL);
	ASSERT (m_pScriptLibLocal != NULL);

	if (m_pScriptLibGlobal != NULL)
	{
		if (m_pScriptLibGlobal->Find(pScriptText) != NULL)
		{
			return TRUE;
		}
	}

	if (m_pScriptLibLocal->Find(pScriptText) != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

long CGuideBook::GetDevice(CExBaseList &oListDevice)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DEVICE)
		{
			oListDevice.AddTail(p);
		}
	}

	return oListDevice.GetCount();
}

long CGuideBook::GetAllCpus(CExBaseList &oListCpus)
{
	CExBaseList oListDevice;
	GetDevice(oListDevice);
	POS pos = oListDevice.GetHeadPosition();
	CDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CDevice *)oListDevice.GetNext(pos);
		pDevice->GetCpusList(oListCpus, TRUE);
	}

	oListDevice.RemoveAll();

	return oListCpus.GetCount();
}

//////////////////////////////////////////////////////////////////////////
void CGuideBook::InitGlobalDatas_TestDefine()
{
	GetTestAppDefine(TRUE);
	GetGlobalDatas(TRUE);

	CDvmDataset dsCommCfg, dsTestAppDef, dsDeviceAttr;
	OpenExpandFile(&dsCommCfg, &dsTestAppDef, &dsDeviceAttr);

	m_pGlobalDatas->AppendClone(dsDeviceAttr, FALSE);
	m_pTestAppDefine->AppendClone(dsTestAppDef, FALSE);
// 	Append_Datas(m_pGlobalDatas, &, FALSE);
// 	Append_Datas(m_pTestAppDefine, &dsTestAppDef, FALSE);

}

void CGuideBook::InitGlobalDatas()
{
// 	if (m_pGlobalDatas == NULL)
// 	{
// 		return;
// 	}

	GetGlobalDatas(TRUE);
	AddGlobalDatas();
}

void CGuideBook::AddGlobalDatas()
{
//	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestBeginTime, g_strGbGlobalData_TestBeginTime, _T(""), _T(""), _T(""), _T("%Y - %m - %d "), FALSE);
//	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestEndTime,  g_strGbGlobalData_TestEndTime,   _T(""), _T(""), _T(""), _T("%Y - %m - %d "), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestBeginTime, g_strGbGlobalData_TestBeginTime, _T(""), _T(""), _T(""), _T("%Y年%m月%d日"), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestEndTime,  g_strGbGlobalData_TestEndTime,   _T(""), _T(""), _T(""), _T("%Y年%m月%d日"), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestType,       g_strGbGlobalData_TestType,      _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_Tester,           g_strGbGlobalData_Tester,        _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_GuideBookFile, g_strGbGlobalData_GuideBookFile, _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_DvmFile,         g_strGbGlobalData_DvmFile,       _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_Protocol,         g_strGbGlobalData_Protocol,      _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_ProjectName,   g_strGbGlobalData_ProjectName,   _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TaskName,   g_strGbGlobalData_TaskName,      _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_User,            g_strGbGlobalData_User,          _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_UserCop,       g_strGbGlobalData_UserCop,       _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_ReportSN,     g_strGbGlobalData_ReportSN,       _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestError,     g_strGbGlobalData_TestError,       _T(""), _T(""), _T(""), _T(""), FALSE);

	//shaolei  20211018
	m_pGlobalDatas->AddNew2(_T("测试人员：主检"), g_strGbGlobalData_MainInspection,  _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(_T("测试人员：校对"),       g_strGbGlobalData_Proofreader,       _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(_T("测试人员：审核"),     g_strGbGlobalData_Checker,       _T(""), _T(""), _T(""), _T(""), FALSE);
	m_pGlobalDatas->AddNew2(_T("检验依据标准"),     g_strGbGlobalData_InspectionBases,       _T(""), _T(""), _T(""), _T(""), FALSE);

}

void CGuideBook::AddTestMan(const CString &strName, const CString &strID)
{

}

void CGuideBook::InitTimeData(CDvmData *pData)
{
	InitTimeData(pData->m_dTime, pData->m_strFormat, pData->m_strValue);
}

void CGuideBook::InitTimeData(CShortData *pData)
{
	InitTimeData(pData->m_dTime, pData->m_strFormat, pData->m_strValue);

}

void CGuideBook::InitTimeData(double &dTime, const CString &strFormat, CString &strValue)
{
#ifndef _PSX_QT_LINUX_
    SYSTEMTIME tmSys;
	CTime tm = CTime::GetCurrentTime();
	tm.GetAsSystemTime(tmSys);

	COleDateTime timeDest(tmSys);
	CString strData;

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
#endif

	strData = timeDest.Format(strFormat);

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("eng"));
#endif

	__time64_t tm_t = tm.GetTime();
	memcpy(&dTime, &tm_t, sizeof(double));

	if (strData.GetLength() == 0)
	{
		strValue.Format(_T("%d-%d-%d %d:%d:%d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour
			, tmSys.wMinute, tmSys.wSecond);
	}
	else
	{
		strValue = strData;
	}
#endif
}

CValue* CGuideBook::FindReportData(const CString &strID)
{
	CReport *pReport = (CReport*)m_pReports->GetHead();

	if (pReport == NULL)
	{
		return NULL;
	}

	CValue *pFind = (CValue*)pReport->m_pValues->FindByID(strID);

	return pFind;
}

BOOL CGuideBook::SetTestBeginTime()
{
	if (m_pTestBeginTime == NULL)
	{
		m_pTestBeginTime = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestBeginTime);
	}

	if (m_pTestBeginTime == NULL)
	{
		return FALSE;
	}

	CValue *pFind = FindReportData(m_pTestBeginTime->m_strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	InitTimeData(m_pTestBeginTime);
	AddReportData(m_pTestBeginTime);

	return TRUE;
}

BOOL CGuideBook::SetTestEndTime()
{
	if (m_pTestEndTime == NULL)
	{
		m_pTestEndTime = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestEndTime);
	}

	if (m_pTestEndTime == NULL)
	{
		return FALSE;
	}

// 	if (m_pTestEndTime->m_strValue.GetLength() > 0)
// 	{
// 		return FALSE;
// 	}

	InitTimeData(m_pTestEndTime);
	AddReportData(m_pTestEndTime);

	return TRUE;
}


void CGuideBook::SetTestTime(CDvmData *pTestBeginTime, CDvmData *pTestEndTime)
{
	m_pTestBeginTime = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestBeginTime);
	m_pTestEndTime = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestEndTime);

	ASSERT (m_pTestBeginTime != NULL);
	ASSERT (m_pTestEndTime != NULL);
	ASSERT (pTestBeginTime != NULL);
	ASSERT (pTestEndTime != NULL);

	pTestBeginTime->Copy(m_pTestBeginTime);
	pTestEndTime->Copy(m_pTestEndTime);
	AddReportData(m_pTestBeginTime);
	AddReportData(m_pTestEndTime);
}

void CGuideBook::SetgVmProgID(const CString &strVmProgID)
{
	CDvmData *pData = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_VmProgID);

	if (pData == NULL)
	{
		pData = m_pGlobalDatas->AddNewData();
		pData->m_strName = g_strGbGlobalData_VmProgID;
		pData->m_strID = g_strGbGlobalData_VmProgID;
	}

	pData->m_strValue = strVmProgID;	
}

BOOL CGuideBook::SetTestError(const CString &strTestError)
{
	CDvmData *pCommError = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_TestError);
	ASSERT (pCommError != NULL);

	if (pCommError == NULL)
	{
		pCommError = m_pGlobalDatas->AddNew2(g_strGbGlobalData_TestError,     g_strGbGlobalData_TestError,       _T(""), _T(""), _T(""), _T(""), FALSE);
	}

	if (pCommError->m_strValue.GetLength() > 0)
	{
		return TRUE;
	}

	pCommError->m_strValue = strTestError;
	InitTestError(pCommError);

	AddReportData(pCommError);
	
#ifndef _PSX_QT_LINUX_
#ifndef GUIDEBOOK_DEV_MODE
	if (CFactoryBatchTestMngr::HasTestTasks())
	{
		CFactoryBatchTestMngr::PostFacBatchTestMsg(FacBatchTestMsg_Attr_TestErr, (LPARAM)this);
	}
#endif
#endif

	return TRUE;
}

CTestGlobalDatasMngr* CGuideBook::GetTestGlobalDatasMngr()
{
	if (m_pTestGlobalDatasMngr == NULL)
	{
		m_pTestGlobalDatasMngr = new CTestGlobalDatasMngr();
		AddNewChild(m_pTestGlobalDatasMngr);
	}

	return m_pTestGlobalDatasMngr;
}

void CGuideBook::SetTestGlobaoDatasMngrs(CDataSet *pDataset)
{
	if (m_pTestGlobalDatasMngr == NULL)
	{
		return;
	}

	m_pTestGlobalDatasMngr->SetTestGlobaoDatasMngrs(pDataset);
}

void CGuideBook::AddSysPara(const CString &strID, const CString &strValue)
{
	CExBaseList listDevice;
	SelectChildrenByClassID(listDevice, GBCLASSID_DEVICE);

	POS pos = listDevice.GetHeadPosition();
	CDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CDevice *)listDevice.GetNext(pos);
		pDevice->AddSysPara(strID, strValue);
	}

	listDevice.RemoveAll();
}

BOOL CGuideBook::IsTestFirstItem()
{
	if (m_pTestBeginTime == NULL)
	{
		return TRUE;
	}
	else
	{
		if (m_pTestBeginTime->m_strValue.GetLength() == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

// 	if (m_pReports == NULL)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (m_pReports->GetCount() == 0)
// 	{
// 		return TRUE;
// 	}
// 
// 	return FALSE;
}

BOOL CGuideBook::IsGuideBookFirstCreate()
{
	if (m_pTestApp == NULL)
	{
		if (m_pReports == NULL)
		{
			return TRUE;
		}

		return (m_pReports->GetCount() == 0);
	}

	if (m_pTestApp->m_strName.GetLength() > 2)
	{
		return FALSE;
	}

	m_pTestApp->m_strName = m_pTestApp->m_strID;

	return TRUE;
}

void CGuideBook::AddReportData(CShortData *pData)
{
	AddReportData(pData->m_strID, pData->m_strName, pData->m_strValue);
}

void CGuideBook::AddReportData(CDvmData *pData)
{
	AddReportData(pData->m_strID, pData->m_strName, pData->m_strValue);
}


void CGuideBook::AddReportData(const CString &strID, const CString &strValue)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		pReport = AddReport(g_strGbGlobalDatasID, g_strGbGlobalDatasID);
	}

	CValue *pValue = pReport->FindReportData(strID);

	if (pValue == NULL)
	{
		pValue = pReport->AddValue(strID, strValue);
	}
	else
	{
		pValue->m_strValue = strValue;
	}
}

void CGuideBook::AddReportData(const CString &strID, const CString &strName, const CString &strValue)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		pReport = AddReport(g_strGbGlobalDatasID, g_strGbGlobalDatasID);
	}

	CValue *pValue = pReport->FindReportData(strID);

	if (pValue == NULL)
	{
		pValue = pReport->AddValue(strID, strName, strValue);
	}
	else
	{
		pValue->m_strValue = strValue;
	}
}

void CGuideBook::AddReportData(CDvmDataset *pDvmDataset)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		pReport = AddReport(g_strGbGlobalDatasID, g_strGbGlobalDatasID);
	}

	pReport->AddRptDvmDataset(*pDvmDataset);
	pReport->m_pRptDvmDataset->m_strName = DSID_TESTAPP_DEF;
	pReport->m_pRptDvmDataset->m_strID = DSID_TESTAPP_DEF;
}

void CGuideBook::InitMacroCharTestItems()
{
	InitMacroCharTestItems(this);
}

void CGuideBook::InitMacroCharTestItems(CExBaseList *pList)
{
#ifndef _PSX_QT_LINUX_
    POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsItemsBaseClassID(nClassID))
		{
			InitMacroCharTestItems((CExBaseList*)p);
		}
		else if (nClassID == GBCLASSID_MACROCHARITEMS)
		{
			((CMacroCharItems*)p)->InitMacroTestItems();
		}
	}
#endif
}

void CGuideBook::SetGlobalDatas(const CString &strReportSN, CDvmDataset *pDsDeviceAttr, CDvmDataset *pTestApp)
{
	GetGlobalDatas(TRUE);
	GetTestApp(TRUE);

	//报告编号
	CDvmData *pDvmData = (CDvmData*)m_pGlobalDatas->FindByID(g_strGbGlobalData_ReportSN);
	ASSERT( pDvmData != NULL );
	pDvmData->m_strValue = strReportSN;
	AddReportData(g_strGbGlobalData_ReportSN, strReportSN);

	//测试仪
	SetGlobalDatas_TestApp(pTestApp);

	//装置属性
	SetGlobalDatas_DeviceAttr(pDsDeviceAttr);

	//测试人员
#ifndef _PSX_QT_LINUX_
#ifndef _not_use_safenet_
	AddReportData(g_strGbGlobalData_Tester, hasp_get_user_name(FALSE));
	AddReportData(g_strGbGlobalData_User, hasp_get_user_name(FALSE));
	AddReportData(g_strGbGlobalData_UserCop, hasp_get_user_cop(FALSE));
#endif
#endif
}

void CGuideBook::SetGlobalDatas_DeviceAttr(CDvmDataset *pDsDeviceAttr)
{
	ASSERT (pDsDeviceAttr != NULL);

	if (pDsDeviceAttr == NULL)
	{
		return ;
	}

	CDvmData *pDvmData = NULL;
	POS pos = pDsDeviceAttr->GetHeadPosition();
	CDvmData *pFind = NULL;
	CDevice *pDevice = GetDevice();
	ASSERT (pDevice != NULL);
	CSysParas *pSysParas = pDevice->GetSysParas();
	CDataObj *pSysPara = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pDsDeviceAttr->GetNext(pos);
		m_pGlobalDatas->AddNew2(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strUnit
			, pDvmData->m_strDataType, pDvmData->m_strValue, pDvmData->m_strFormat, FALSE);
		AddReportData(pDvmData->m_strID, pDvmData->m_strValue);

		pSysPara = (CDataObj*)pSysParas->FindByID(pDvmData->m_strID);

		if (pSysPara != NULL)
		{
			pSysPara->m_strValue = pDvmData->m_strValue;
		}
		else
		{
			POS posVal = pDvmData->GetHeadPosition();
			CDvmValue *pDvmValue = NULL;

			while (posVal != NULL)
			{
				pDvmValue = (CDvmValue *)pDvmData->GetNext(posVal);
				pSysPara = (CDataObj*)pSysParas->FindByID(pDvmData->m_strID);

				if (pSysPara != NULL)
				{
					pSysPara->m_strValue = pDvmData->m_strValue;
					break;
				}
			}
		}
	}
}

void CGuideBook::SetGlobalDatas_DeviceAttr(CDvmData *pTestDefineDvAttr)
{
	CDvmValue *pSrcAttr = NULL;
	POS pos = pTestDefineDvAttr->GetHeadPosition();
	CDvmData *pFind = NULL;
	CDevice *pDevice = GetDevice();
	ASSERT (pDevice != NULL);
	CSysParas *pSysParas = pDevice->GetSysParas();
	CDataObj *pSysPara = NULL;

	while (pos != NULL)
	{
		pSrcAttr = (CDvmValue *)pTestDefineDvAttr->GetNext(pos);
		m_pGlobalDatas->AddNew2(pSrcAttr->m_strName, pSrcAttr->m_strID, _T("")
			, pSrcAttr->m_strDataType, pSrcAttr->m_strValue, _T(""), FALSE);

		AddReportData(pSrcAttr->m_strID, pSrcAttr->m_strValue);

		pSysPara = (CDataObj*)pSysParas->FindByID(pSrcAttr->m_strID);

		if (pSysPara != NULL)
		{
			pSysPara->m_strValue = pSrcAttr->m_strValue;
		}
	}
}

void CGuideBook::SetGlobalDatas_TestApp(CDvmDataset *pTestApp)
{
	if (pTestApp == NULL)
	{
		return;
	}

	GetTestApp(TRUE);

	m_pTestApp->DeleteAll();
	m_pTestApp->AppendCloneEx(*pTestApp);
	AddReportData(pTestApp);
}

//所有依据，需要转换成一个数据保存，以便写入报告
void CGuideBook::SetGlobalDatas_InspectionBases(CDvmDataset *pInspectionBases)
{
	POS pos = pInspectionBases->GetHeadPosition();
	CString strName;
	long nCount = pInspectionBases->GetCount();
	long nIndex = 0;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pInspectionBases->GetNext(pos);
		CDvmValue *pName = (CDvmValue *)pData->FindByID(_T("Name"));
		nIndex++;

		if (pName == NULL)
		{
			continue;
		}

		if (nIndex == nCount)
		{
            strName += pName->m_strValue;
		}
		else
		{
            strName += pName->m_strValue;
            strName += _T("\r\n");
		}
	}

	m_pGlobalDatas->AddNew2(_T("检验依据标准"), g_strGbGlobalData_InspectionBases, _T("")
		, _T("string"), strName, _T(""), FALSE);

	AddReportData(g_strGbGlobalData_InspectionBases, strName);
}

/*
<group name="任务检验依据" id="InspectionBases" data-type="" value="">
	<data name="依据名称" id="Name" data-type="" default-value="" value="Q/GDW 12021-2019输变电设备物联网节点设备无线组网协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="依据名称" id="Name" data-type="" default-value="" value="PAL/BZ 12020-2020输变电设备物联网微功率无线网通信协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="依据名称" id="Name" data-type="" default-value="" value="PAL/BZ 12021-2020输变电设备物联网节点设备无线组网协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	……
</group>
*/
//所有依据，需要转换成一个数据保存，以便写入报告
void CGuideBook::SetGlobalDatas_InspectionBases_Ex(CDataGroup *pInspectionBases)
{
	POS pos = pInspectionBases->GetHeadPosition();
	CString strName;
	long nCount = pInspectionBases->GetCount();
	long nIndex = 0;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pInspectionBases->GetNext(pos);
		nIndex++;

		if (nIndex == nCount)
		{
			//最后一个，不用增加换行
			strName += pData->m_strValue;
		}
		else
		{
			strName += pData->m_strValue;
			strName += _T("\r\n");
		}
	}

	m_pGlobalDatas->AddNew2(_T("检验依据标准"), g_strGbGlobalData_InspectionBases, _T("")
		, _T("string"), strName, _T(""), FALSE);

	AddReportData(g_strGbGlobalData_InspectionBases, strName);
}

//检验人员，暂时只记录检验人员的姓名
void CGuideBook::SetGlobalDatas_Testers(CDvmDataset *pTesters)
{
	POS pos = pTesters->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pTesters->GetNext(pos);
		CDvmValue *pValue = (CDvmValue *)pData->FindByID(_T("Name"));

		if (pValue == NULL)
		{
			continue;
		}

		m_pGlobalDatas->AddNew2(pData->m_strName, pData->m_strID, _T("")
				, _T("string"), pValue->m_strValue, _T(""), FALSE);	
		
		AddReportData(pData->m_strID, pValue->m_strValue);
	}
}

void CGuideBook::SetGlobalDatas_GlobalDatas(CExBaseList *pGlobalDatas)
{
	POS pos = pGlobalDatas->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pGlobalDatas->GetNext(pos);

		CDvmData *pNewData = (CDvmData *)m_pGlobalDatas->FindByID(pData->m_strID);

		if (pNewData == NULL)
		{
			pNewData = new CDvmData();
			pNewData->m_strID = pData->m_strID;
			m_pGlobalDatas->AddNewChild(pNewData);
		}

		pNewData->m_strName = pData->m_strName;
		pNewData->m_strValue = pData->m_strValue;

		AddReportData(pNewData->m_strID, pNewData->m_strValue);
	}
}

void CGuideBook::SetTestAppDefine(CDvmDataset *pTestAppDefine)
{
	if (pTestAppDefine == NULL)
	{
		return;
	}

	POS pos = pTestAppDefine->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pTestAppDefine->GetNext(pos);

		CDvmData *pNewData = (CDvmData *)m_pTestAppDefine->FindByID(pData->m_strID);

		if (pNewData == NULL)
		{
			pNewData = new CDvmData();
			pNewData->m_strID = pData->m_strID;
			m_pGlobalDatas->AddNewChild(pNewData);
		}

		pNewData->m_strName = pData->m_strName;
		pNewData->m_strValue = pData->m_strValue;
	}
}

void CGuideBook::AddReportDatas_GlobalDatas()
{
	POS pos = m_pGlobalDatas->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pGlobalDatas->GetNext(pos);

		if (pData->m_strID == g_strTestResultDescriptKey
			|| pData->m_strID == g_strTestResultJudgeKey
			|| pData->m_strID == g_strTestResultTimeKey)
		{
			continue;
		}

		AddReportData(pData->m_strID, pData->m_strValue);
	}
}

void CGuideBook::AdjustByTkIDIndex(DWORD dwTkIDIndex, BOOL bDelete)
{
	if (bDelete)
	{
		AdjustByTkIDIndex_Delete(this, dwTkIDIndex);
	}
	else
	{
		AdjustByTkIDIndex_Select(this, dwTkIDIndex);
	}
}

void CGuideBook::AdjustByTkIDIndex(const CString strTestType, BOOL bDelete)
{
	if (strTestType.GetLength() == 0)
	{
		AdjustByTkIDIndex(_T("1"), bDelete);
		return;
	}

    if (IsStringNumber(strTestType.GetString()))
	{
		DWORD dwTkID_Index = 1;
		long nIndex = CString_To_long(strTestType);
		nIndex -= 1;
		dwTkID_Index = dwTkID_Index << nIndex;
		AdjustByTkIDIndex(dwTkID_Index, bDelete);
	}
	else
	{
		CTestType *pTestType = (CTestType*)m_oTestTypes.FindByName(strTestType);

		if (pTestType == NULL)
		{
			AdjustByTkIDIndex(_T("1"), bDelete);
		}
		else
		{
			//测试模板编辑，形成的测试类型ID根据类型的顺序来确定
			//因此在此处也需要按照顺序来进行处理
			CString strTestTypeIndex;
			long nIndex = m_oTestTypes.FindIndex(pTestType);
			strTestTypeIndex.Format(_T("%d"), nIndex+1);
			//AdjustByTkIDIndex(pTestType->m_strID, bDelete);
			AdjustByTkIDIndex(strTestTypeIndex, bDelete);
		}
	}
}

void CGuideBook::AdjustByTkIDIndex_Select(CExBaseList *pList, DWORD dwTkIDIndex)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)p;

			if ((pItem->m_nTkID & dwTkIDIndex) == 0)
			{
				pItem->m_nSelect = 0;
			}
		}
		else if (Gb_IsItemsBaseClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)p;

			if ((pItem->m_nTkID & dwTkIDIndex) == 0)
			{
				Gb_SetTestItemSelectedState(pItem, 0, FALSE);
				pItem->m_nSelect = 0;
			}
			else
			{
				AdjustByTkIDIndex_Select((CExBaseList*)p, dwTkIDIndex);
			}
		}
	}

	Gb_UpdateItemSelectedState((CGbItemBase*)pList);
}

void CGuideBook::AdjustByTkIDIndex_Delete(CExBaseList *pList, DWORD dwTkIDIndex)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)p;

			if ((pItem->m_nTkID & dwTkIDIndex) == 0)
			{
				pList->DeleteAt(posPrev);
			}
		}
		else if (Gb_IsItemsBaseClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)p;

			if ((pItem->m_nTkID & dwTkIDIndex) == 0)
			{
				pList->DeleteAt(posPrev);
			}
			else
			{
				AdjustByTkIDIndex_Delete((CExBaseList*)p, dwTkIDIndex);
			}
		}
	}
}

//装置的全局参数
void CGuideBook::GBS_SetGlobal_Str(const CString &strID, const CString &strValue)
{
	if (m_pGlobalDatas != NULL)
	{
		CDvmData *pData = (CDvmData*)m_pGlobalDatas->FindByID(strID);

		if (pData != NULL)
		{
			pData->m_strValue = strValue;
		}
		else
		{
			pData = new CDvmData();
			pData->m_strName = strID;
			pData->m_strID = strID;
			pData->m_strValue = strValue;
			m_pGlobalDatas->AddNewChild(pData);
		}
	}

	if (m_pReports != NULL)
	{
		CReport *pReport = (CReport*)m_pReports->GetTail();

		if (pReport != NULL)
		{
			pReport->SetValue(strID, strValue);
		}
	}
}

CString CGuideBook::GBS_GetGlobal_Str(const CString &strID)
{
	if (m_pGlobalDatas != NULL)
	{
		CDvmData *pData = (CDvmData*)m_pGlobalDatas->FindByID(strID);

		if (pData != NULL)
		{
			return pData->m_strValue;
		}
	}

	if (m_pReports != NULL)
	{
		CReport *pReport = (CReport*)m_pReports->GetTail();

		if (pReport != NULL)
		{
			CValue *pValue = pReport->FindReportData(strID);
			
			if (pValue != NULL)
			{
				return pValue->m_strValue;
			}
		}
	}

	return _T("");
}

BOOL CGuideBook::GBS_GetGlobal_Str(const CString &strID, CString &strValue)
{
	if (m_pGlobalDatas != NULL)
	{
		CDvmData *pData = (CDvmData*)m_pGlobalDatas->FindByID(strID);

		if (pData != NULL)
		{
			strValue = pData->m_strValue;
			return TRUE;
		}
	}

	if (m_pReports != NULL)
	{
		CReport *pReport = (CReport*)m_pReports->GetTail();

		if (pReport != NULL)
		{
			CValue *pValue = pReport->FindReportData(strID);

			if (pValue != NULL)
			{
				strValue = pValue->m_strValue;
				return TRUE;
			}
		}
	}

	return FALSE;
}

//字符串切割
long CGuideBook::GBS_InitStrTok(char *pszString, char *pControl)
{
	char ch = '\n';
	char *p = pControl;

	if (*pControl != 0)
	{
		ch = *pControl;
		p = pControl + 1;
	}

	m_oStringTokenizer.Init(pszString, ch);

	while (*p != 0)
	{
		m_oStringTokenizer.Format(*p);
		p++;
	}

	return m_oStringTokenizer.GetStringsCount();
}

long CGuideBook::GBS_StrTokCount()
{
	return m_oStringTokenizer.GetStringsCount();
}

const char* CGuideBook::GBS_StrTokIndex(long nIndex)
{
	return (char*)m_oStringTokenizer.GetToken(nIndex);
}

const char* CGuideBook::GBS_StrTokNext()
{
	return m_oStringTokenizer.NextToken();
}

CString CGuideBook::GetReportTemplateRelativePath(const CString &strFullPath)
{
	CString strRelativePath;

	GetRelativePathTo(m_strGbXmlFile, strFullPath, strRelativePath);

	return strRelativePath;
}

CString CGuideBook::GetReportTemplateFullPath(const CString &strRelPath)
{
	CString strFullPath;

	if (strRelPath.GetLength() == 0)
	{
		strFullPath = m_strGbXmlFile;
		strFullPath = ChangeFilePostfix(strFullPath, g_strDocFilePostfix);
	}
	else
	{
		GetPathFromRelative(m_strGbXmlFile, strRelPath, strFullPath);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("GetReportTemplateFullPath：%s"), strFullPath.GetString());
	//2019-10-30  不同路径下的系统，会带来问题，因为此路径为绝对路径
	if (! IsFileExist(strFullPath))
	{
		_P_ReplaceSystemPath(strFullPath);
	}

	return strFullPath;
}

CString CGuideBook::GetItemTempPath()
{
	CString strTempFilePath = m_strGuideBookFile;
	long nPos = strTempFilePath.ReverseFind('.');
	strTempFilePath = strTempFilePath.Left(nPos);
	strTempFilePath += _P_FOLDER_PATH_SEPARATOR_;

	return strTempFilePath;
}

void CGuideBook::OffsetBinary(long nBinOffset, long nBoutOffset)
{
	if (nBinOffset <= 0 && nBoutOffset <= 0)
	{
		return;
	}

	CGuideBookTool::OffsetBinary(this, nBinOffset, nBoutOffset);
}

void CGuideBook::OffsetBinary()
{
	m_nBinOffset = 0;
	m_nBoutOffset = 0;
	GetOffsetBinary(m_nBinOffset, m_nBoutOffset);	
	OffsetBinary(m_nBinOffset, m_nBoutOffset);
}

BOOL CGuideBook::UseBinaryOffset()
{
	if (m_pGlobalDatas == NULL)
	{
		return FALSE;
	}

	BOOL bUseBinaryOffset = FALSE;
	CDvmData *pData = NULL;

	pData = (CDvmData*)m_pGlobalDatas->FindByID(AtsRpcTestDef_bin_offset);

	if (pData != NULL)
	{
		bUseBinaryOffset = TRUE;
	}

	pData = (CDvmData*)m_pGlobalDatas->FindByID(AtsRpcTestDef_bout_offset);
	
	if (pData != NULL)
	{
		bUseBinaryOffset = TRUE;
	}

	return bUseBinaryOffset;
}

void CGuideBook::GetOffsetBinary(long &nBinOffset, long &nBoutOffset)
{
	nBinOffset = 0;
	nBoutOffset = 0;
	CDvmData *pData = NULL;

	pData = (CDvmData*)m_pGlobalDatas->FindByID(AtsRpcTestDef_bin_offset);

	if (pData != NULL)
	{
		nBinOffset = CString_To_long(pData->m_strValue);
	}

	pData = (CDvmData*)m_pGlobalDatas->FindByID(AtsRpcTestDef_bout_offset);

	if (pData != NULL)
	{
		nBoutOffset = CString_To_long(pData->m_strValue);
	}

	pData = (CDvmData*)m_pGlobalDatas->FindByID(AtsRpcTestDef_TestAppGroup);

	if (pData != NULL)
	{
		m_strTestAppGroup = pData->m_strValue;
	}

	m_nBinOffset = nBinOffset;
	m_nBoutOffset = nBoutOffset;
}


void CGuideBook::CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile)
{
	if (m_pItemContainer != NULL)
	{
#ifdef _DEBUG
        m_pItemContainer->m_strName.Format(_T("%s:ItemContainer"), m_strName.GetString());
        m_pItemContainer->m_strID.Format(_T("%s:ItemContainer"), m_strID.GetString());
#endif
		m_pItemContainer->CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}

	if (m_pScriptLibGlobal != NULL)
	{
#ifdef _DEBUG
        m_pScriptLibGlobal->m_strName.Format(_T("%s:ScriptLibGlobal"), m_strName.GetString());
        m_pScriptLibGlobal->m_strID.Format(_T("%s:ScriptLibGlobal"), m_strID.GetString());
#endif
		m_pScriptLibGlobal->CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}

	//if (m_oGbCommCmdConfig != NULL)
	{
#ifdef _DEBUG
        m_oGbCommCmdConfig.m_strName.Format(_T("%s:GbCommCmdConfig"), m_strName.GetString());
        m_oGbCommCmdConfig.m_strID.Format(_T("%s:GbCommCmdConfig"), m_strID.GetString());
#endif
		m_oGbCommCmdConfig.CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}
}

BOOL CGuideBook::IsAuthority()
{
#ifndef _PSX_QT_LINUX_
#ifndef _not_use_safenet_
    //能云公司的成员，能够使用任何模板
	if (CSafenet_Login::hasp_is_power_sky())
	{
		return TRUE;
	}

	CString strAuthoritySN, strName, strMacroFileID, strDevKey;
	BOOL bRet = GetAuthoritySN(strAuthoritySN, strName, strMacroFileID, strDevKey);

	if (!bRet)
	{//1-模板没有授权信息
		if (CSafenet_Login::hasp_get_template_authority_sn() == _T(""))
		{//1-1 兼容老版本：软件狗（没有授权码） == 没有授权信息的模板
			return TRUE;
		}
		else
		{//1-2 软件狗（有授权码） == 没有授权信息的模板，不能使用。需要能云团队成员对所有模板进行授权
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("软件狗授权：没有授权信息的模板，不能使用。请联系%s技术支持")
				, CSafenet_Login::hasp_get_develop(FALSE));
			return FALSE;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//2-模板有授权信息
	//2-1 能云公司的模板，都能够使用
	if (CSafenet_Login::hasp_is_power_sky(strAuthoritySN))
	{
		CString strUserCopSN2, strAuthoritySN2, strKeySN2, strUserID2, strDevKey2;

		if (strMacroFileID != m_strTestMacroFileID || m_strName != strName)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("没有使用[%s][%s][%s]的权限")
				, m_strName, m_strTestMacroFileID, GetPathFileNameFromFilePathName(m_strGbXmlFile));
			return FALSE;
		}

		if (GetGbDev(strUserCopSN2, strAuthoritySN2, strKeySN2, strUserID2, strDevKey2))
		{
			if (CSafenet_Login::hasp_is_power_sky(strAuthoritySN2))
			{//能云公司的软件狗加密的
				if (CSafenet_Login::hasp_get_template_authority_sn().GetLength() > 0)
				{//2-1-1 新的软件狗
					if (!CSafenet_Login::hasp_can_use_test_macro(m_strTestMacroFileID))
					{//软件狗支持此功能
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("没有使用[%s][%s][%s]的权限")
							, m_strName, m_strTestMacroFileID, GetPathFileNameFromFilePathName(m_strGbXmlFile));
						return FALSE;
					}
					else
					{
						return TRUE;
					}
				}
				else//if (CSafenet_Login::hasp_get_template_authority_sn().GetLength() > 0)
				{//2-1-2 老的软件狗，能够使用
					return TRUE;
				}
			}
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("没有使用[%s][%s][%s]的权限，模板加密信息错误")
			, m_strName, m_strTestMacroFileID, GetPathFileNameFromFilePathName(m_strGbXmlFile));

		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	//2-2 其他公司的模板

	if (CSafenet_Login::hasp_get_test_macros().GetLength() == 0 || CSafenet_Login::hasp_get_template_authority_sn().GetLength() == 0)
	{//2-2-1 其他公司的模板 老版本的软件狗，不能使用
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("你的软件狗，没有使用[%s][%s][%s]的权限")
			, m_strName, m_strTestMacroFileID, GetPathFileNameFromFilePathName(m_strGbXmlFile));

		return FALSE;
	}

	if (!CSafenet_Login::hasp_can_use_test_macro(m_strTestMacroFileID))
	{//2-2-2 其他公司的模板 新软件狗，没有使用功能的权限
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("没有使用[%s]的权限"), m_strTestMacroFileID);
		return FALSE;
	}

	//2-2-3 其他公司的模板 新软件狗，综合判断授权信息
	return IsAuthority(CSafenet_Login::hasp_get_template_authority_sn());
#else
	return TRUE;
#endif//#ifndef _not_use_safenet_

#else
	return TRUE;
#endif
}

BOOL CGuideBook::IsAuthority(const CString &strAuthoritySN)
{
    BOOL bRet = TRUE;
#ifndef _PSX_QT_LINUX_
#ifndef _not_use_safenet_
    //兼容之前版本的软件狗信息：授权码为空
	if (strAuthoritySN.GetLength() <= 1)
	{
		return FALSE;
	}

	//没有授权的测试模板
	if (m_strAuthoritySN.GetLength() <= 5)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("没有授权信息的模板，不能使用。请联系%s技术支持")
			, CSafenet_Login::hasp_get_develop(FALSE));
		return FALSE;
	}

	CString strTemp, strEncrypt, strDevKey;
	
	strTemp = GetEncryptString(strAuthoritySN);
	strEncrypt = xdes_Encrypt(strTemp);

    bRet =( strEncrypt == m_strAuthoritySN);

	if (!bRet)
	{
		CString strDec = xdes_Decrypt(m_strAuthoritySN);

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("没有使用模板[%s]的权限")
			, GetPathFileNameFromFilePathName(m_strGbXmlFile));

		CString strAuthoritySN2, strName2, strMacroID2, strDevKey2;
		GetAuthoritySN(strAuthoritySN2, strName2, strMacroID2, strDevKey2);
		GetGbDevKey(strDevKey);

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("SafenetEncrypt=[%s][%s][%s][%s]  template file=[%s][%s][%s][%s]")
			, strAuthoritySN2, strName2, strMacroID2, strDevKey2
			, strAuthoritySN, m_strName, m_strTestMacroFileID, strDevKey);

	}
#endif
#endif

    return bRet;
}

CString CGuideBook::GetEncryptString(const CString &strAuthoritySN)
{
	CString strTemp, strDevKey;
	
	strTemp = strAuthoritySN + _T("$") + m_strName;
	strTemp = strTemp + _T("$") + m_strTestMacroFileID;

	if (GetGbDevKey(strDevKey))
	{
		strTemp = strTemp + _T("$") + strDevKey;
	}

	return strTemp;
}

void CGuideBook::Encrypt(const CString &strAuthoritySN)
{
	if (strAuthoritySN.GetLength() <= 1)
	{
		return;
	}

	CString strTemp = GetEncryptString(strAuthoritySN);

	m_strAuthoritySN = xdes_Encrypt(strTemp);
}

void CGuideBook::UpdateAuthoritySN()
{
#ifndef _PSX_QT_LINUX_
#ifndef _not_use_safenet_

    CString strAuthoritySN = GetAuthoritySN();
	CString strAuthoritySN_Safenet = CSafenet_Login::hasp_get_template_authority_sn();

	//如果当前模板是POWER-SKY模板，则改为当前软件狗的模板授权
	if (strAuthoritySN != strAuthoritySN_Safenet)
	{//如果软件狗授权码与模板授权码不一致
		if (CSafenet_Login::hasp_is_power_sky(strAuthoritySN_Safenet))
		{//能云的软件狗，保持授权码不变
			//strAuthoritySN = strAuthoritySN;
		}
		else
		{
			strAuthoritySN = strAuthoritySN_Safenet;
		}
	}

	Encrypt(strAuthoritySN);
#endif
#endif
}

CString CGuideBook::GetAuthoritySN()
{
	if (m_strAuthoritySN.GetLength() < 5)
	{
		return _T("");
	}

	CString strTemp;
	strTemp = xdes_Decrypt(m_strAuthoritySN);
	long nPos = strTemp.Find('$');

	if (nPos <= 0)
	{
		return _T("");
	}

	return strTemp.Left(nPos);
}

BOOL CGuideBook::GetAuthoritySN(CString &strAuthoritySN, CString &strName, CString &strMacroID, CString &strDevKey)
{
	if (m_strAuthoritySN.GetLength() < 5)
	{
		return FALSE;
	}

	CString strTemp;
	strTemp = xdes_Decrypt(m_strAuthoritySN);
	CStringTokenizer oToken;
	oToken.Init(strTemp, '$');

	if (oToken.GetStringsCount() < 3)
	{
		return FALSE;
	}
	
	strAuthoritySN = oToken.NextToken();
	strName = oToken.NextToken();
	strMacroID = oToken.NextToken();
	strDevKey = oToken.NextToken();

	return TRUE;
}

void CGuideBook::ValidateGbName()
{
	if (m_strName == g_sLangTxt_OperIns)
	{
		m_strName = ATS_GUIDEBOOK_INIT_NAME;
		CString strAuthority = GetAuthoritySN();
		Encrypt(strAuthority);
	}
}

void CGuideBook::InitGbDev()
{
	if (m_pGbDev != NULL)
	{
		return;
	}
	
	m_pGbDev = new CDvmDataset();
	m_pGbDev->m_strName = m_pGbDev->m_strID = g_strGbDevForAuthority;
	AddHead(m_pGbDev);
	m_pGbDev->SetParent(this);
}

void CGuideBook::InitGbDev(const CString &strUserCopSN, const CString &strAuthoritySN, const CString &strKeySN, const CString &strUserID)
{
	if (m_pGbDev == NULL)
	{
		return;
	}

	CString strUserCopSN_Val = xdes_Encrypt(strUserCopSN);
	CString strKeySN_Val = xdes_Encrypt(strKeySN);
	CString strUserID_Val = xdes_Encrypt(strUserID);
	CString strAuthoritySN_Val = xdes_Encrypt(strAuthoritySN);
	
	CString strUserCop_ID = xdes_Encrypt(g_strGbGlobalData_UserCop);
	CString strKey_ID = xdes_Encrypt(g_strGbGlobalData_KeySN);
	CString strUser_ID = xdes_Encrypt(g_strGbGlobalData_User);
	CString strAuthority_ID = xdes_Encrypt(g_strGbGlobalData_AuthoritySN);
	CString strDevKey_ID = xdes_Encrypt(g_strGbGlobalData_DevKey);

	m_pGbDev->AddNewDataEx(strUserCop_ID, strUserCop_ID, _T(""), strUserCopSN_Val);
	m_pGbDev->AddNewDataEx(strUser_ID, strUser_ID, _T(""), strUserID_Val);
	m_pGbDev->AddNewDataEx(strKey_ID, strKey_ID, _T(""), strKeySN_Val);
	m_pGbDev->AddNewDataEx(strAuthority_ID, strAuthority_ID, _T(""), strAuthoritySN_Val);

#ifndef _PSX_QT_LINUX_
    __int64 n64Time = ::_time64(NULL);
	CString strDevKey_Val;
	strDevKey_Val.Format(_T("%I64X"), n64Time);
	m_pGbDev->AddNewDataEx(strDevKey_ID, strDevKey_ID, _T(""), strDevKey_Val);
#endif
}

BOOL CGuideBook::GetGbDev(CString &strUserCopSN, CString &strAuthoritySN, CString &strKeySN, CString &strUserID, CString &strDevKey)
{
	if (m_pGbDev == NULL)
	{
		return FALSE;
	}

	long nCount = 0;

	nCount += GetGbDevValue(g_strGbGlobalData_UserCop, strUserCopSN, TRUE);
	nCount += GetGbDevValue(g_strGbGlobalData_KeySN, strKeySN, TRUE);
	nCount += GetGbDevValue(g_strGbGlobalData_User, strUserID, TRUE);
	nCount += GetGbDevValue(g_strGbGlobalData_AuthoritySN, strAuthoritySN, TRUE);
	nCount += GetGbDevValue(g_strGbGlobalData_DevKey, strDevKey, FALSE);

	return nCount == 5;
}

long CGuideBook::GetGbDevValue(const CString &strKeyID, CString &strValue, BOOL bValDec)
{
	if (m_pGbDev == NULL)
	{
		return 0;
	}

	CString strEncrypt_ID = xdes_Encrypt(strKeyID);
	CDvmData *pFind = (CDvmData *)m_pGbDev->FindByID(strEncrypt_ID);

	if (pFind != NULL)
	{
		if (bValDec)
		{
			strValue = xdes_Decrypt(pFind->m_strValue);
		}
		else
		{
			strValue = pFind->m_strValue;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

BOOL CGuideBook::GetGbDevKey(CString &strDevKey)
{
	if (m_pGbDev == NULL)
	{
		return FALSE;
	}

	return GetGbDevValue(g_strGbGlobalData_DevKey, strDevKey, FALSE);
}


BOOL CGuideBook::IsScriptType_LUA()
{
	return  !IsScriptType_XVM();
}

BOOL CGuideBook::IsScriptType_XVM()
{
	return (m_nScriptType == GBSCRIPT_TYPE_ID_XVM);
}

void CGuideBook::SetScriptType_LUA()
{
	m_strScriptType = GBSCRIPT_TYPE_LUA;
	m_nScriptType = GBSCRIPT_TYPE_ID_LUA;
}

void CGuideBook::SetScriptType_XVM()
{
	m_strScriptType = GBSCRIPT_TYPE_XVM;
	m_nScriptType = GBSCRIPT_TYPE_ID_XVM;
}

void CGuideBook::InitScriptTypeID()
{
	if (m_strScriptType == GBSCRIPT_TYPE_XVM)
	{
		m_nScriptType = GBSCRIPT_TYPE_ID_XVM;
	}
	else
	{
		m_nScriptType = GBSCRIPT_TYPE_ID_LUA;
	}
}

void CGuideBook::SetXvmTasmBuffer(BYTE *pBuffer, long nLen)
{
	FreeXvmTasmBuffer();
	
	if (nLen < 0)
	{
		return;
	}

	m_pXvmTasmBuffer = new BYTE [nLen];
	memcpy(m_pXvmTasmBuffer, pBuffer, nLen);
	m_nXvmLength = nLen;
}

BOOL CGuideBook::HasLogic()
{
	CString strVisio = ChangeFilePostfix(m_strGbXmlFile, g_strGbVisioFileFilter);

	if (IsFileExist(strVisio))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CGuideBook::GetSummaryRslt()
{
	CString strRet = _T("合格");
	CDevice *pDevice = GetDevice();
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);

		if (Gb_IsGbItemClassID(pObj->GetClassID()) || pObj->GetClassID() == GBCLASSID_ITEMS)
		{
			CGbItemBase *pItem = (CGbItemBase*)pObj;
			strRet = Gb_GetSummaryRslt(pItem);

			if (strRet == _T("不合格"))
			{
				break;
			}
		}	
	}

	return strRet;
}

void CGuideBook::GetItemsCount(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	nEligibleCount = nInlegibleCount = 0;
	CDevice *pDevice = GetDevice();
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if(!Gb_IsItemBaseClassID(nClassID))
		{
			continue;
		}

		CGbItemBase *pItem = (CGbItemBase *)pObj;

		if (!pItem->GetSelect())
		{
			continue;
		}

		if (nClassID != GBCLASSID_ITEMS)
		{
			nTotalCount++;

			if (pItem->GetState() == TEST_STATE_ELIGIBLE || pItem->GetState() == TEST_STATE_ELIGIBLEEX)
			{
				nEligibleCount++;
			}
			else if (pItem->GetState() == TEST_STATE_INLEGIBLE)
			{
				nInlegibleCount++;
			}
		}

		long nTotal = 0, nEligible = 0, nInlegible = 0;
		pItem->GetItemsCount(nTotal, nEligible, nInlegible);
		nTotalCount += nTotal;
		nEligibleCount += nEligible;
		nInlegibleCount += nInlegible;
	}
}

void CGuideBook::GetItemsCountByItemsType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	nTotalCount = nEligibleCount = nInlegibleCount = 0;
	CDevice *pDevice = GetDevice();
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (!pItems->GetSelect())
		{
			continue;
		}

		if (pItems->IsTypeRootNode())
		{
			nTotalCount++;  //如果是功能类节点，则将整个CItems看作是一个测试项目，不进行子项目的统计；

			if (pItems->GetState() == TEST_STATE_ELIGIBLE || pItems->GetState() == TEST_STATE_ELIGIBLEEX)
			{
				nEligibleCount++;
			}
			else if (pItems->GetState() == TEST_STATE_INLEGIBLE)
			{
				nInlegibleCount++;
			}

			continue;
		}

		long nTotal = 0, nEligible = 0, nInegible = 0;
		pItems->GetItemsCountByType(nTotal, nEligible, nInegible);
		nTotalCount += nTotal;
		nEligibleCount += nEligible;
		nInlegibleCount += nInegible;
	}
}

//2023-3-29  lijunqing 通信协议部分，修改为SttIot模式
void CGuideBook::SetCommConfig_DvmFile(const CString &strDvmFile)
{
	GetTestGlobalDatasMngr();

	m_pTestGlobalDatasMngr->SetCommConfig_DvmFile(strDvmFile);
}

void CGuideBook::SetCommConfig(CDataGroup *pCommConfig)
{
	GetTestGlobalDatasMngr();

	m_pTestGlobalDatasMngr->SetCommConfig(pCommConfig);
}
void CGuideBook::SetCommConfigs(CDataGroup *pCommConfigs)
{
	GetTestGlobalDatasMngr();

	m_pTestGlobalDatasMngr->SetCommConfigs(pCommConfigs);
}

CDataGroup* CGuideBook::GetCommConfig(BOOL bCreateNew)
{
	GetTestGlobalDatasMngr();
	return m_pTestGlobalDatasMngr->GetCommConfig(bCreateNew);
}

CDataGroup* CGuideBook::GetCommConfigs(BOOL bCreateNew)
{
	GetTestGlobalDatasMngr();
	return m_pTestGlobalDatasMngr->GetCommConfigs(bCreateNew);
}

CDataGroup* CGuideBook::GetHdRes()
{
	return m_pHdRes;
}

void CGuideBook::SetHdRes(CDataGroup *pHdRes)
{
	m_pHdRes = (CDataGroup*)pHdRes->Clone();
	m_pHdRes->m_strName = ID_HD_RES;
	m_pHdRes->m_strID = ID_HD_RES;
	AddNewChild(m_pHdRes);
	BringToHead(m_pHdRes);
}

CDataGroup* CGuideBook::GetItemsTec()
{
	return m_pItemsTec;
}

void CGuideBook::SetItemsTec(CDataGroup *pItemsTec)
{
	if (m_pItemsTec != NULL)
	{
		Delete(m_pItemsTec);
	}

	if (pItemsTec == NULL)
	{
		m_pItemsTec = NULL;
		return;
	}

	m_pItemsTec = (CDataGroup*)pItemsTec->CloneEx(TRUE, TRUE);
	m_pItemsTec->m_strName = ID_ITEMS_TEC;
	m_pItemsTec->m_strID = ID_ITEMS_TEC;
	AddNewChild(m_pItemsTec);
	BringToHead(m_pItemsTec);
}

CDataGroup* CGuideBook::GetAinDataMapCfg()
{
	return m_pAinDataMapCfg;
}

void CGuideBook::SetAinDataMapCfg(CDataGroup *pAinDataMapCfg)
{
	if (m_pAinDataMapCfg != NULL)
	{
		Delete(m_pAinDataMapCfg);
	}

	if (pAinDataMapCfg == NULL)
	{
		m_pAinDataMapCfg = NULL;
		return;
	}

	m_pAinDataMapCfg = (CDataGroup*)pAinDataMapCfg->CloneEx(TRUE, TRUE);
	m_pAinDataMapCfg->m_strName = ID_AIN_DATA_MAP_CFG;
	m_pAinDataMapCfg->m_strID = ID_AIN_DATA_MAP_CFG;
	AddNewChild(m_pAinDataMapCfg);
	BringToHead(m_pAinDataMapCfg);
}

//获取采样值的变比信息。从全局数据获取
CDataGroup* CGuideBook::GetAinRatios()
{
	CDvmDataset *pGlobalDatas = GetGlobalDatas(FALSE);

	if (pGlobalDatas == NULL)
	{
		return NULL;
	}

	CDataGroup *pNewGrp = new CDataGroup();
	pNewGrp->m_strID = ID_AIN_RATIOS;
	pNewGrp->m_strName = ID_AIN_RATIOS;

	CDvmData *pDevMeas = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_DevMeas);

	if (pDevMeas != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pDevMeas->CloneEx());
	}

	CDvmData *pPtPrimary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pPtPrimary->CloneEx());
	}

	CDvmData *pPtSecondary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pPtSecondary->CloneEx());
	}

	CDvmData *pCtPrimary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pCtPrimary->CloneEx());
	}

	CDvmData *pCtSecondary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pCtSecondary->CloneEx());
	}

	return pNewGrp;
}

//将采样值的变比信息，更新到模板全局数据
void CGuideBook::SetAinRatios(CDataGroup *pAinRatios)
{
	if (pAinRatios == NULL)
	{
		return;
	}

	CDvmDataset *pGlobalDatas = GetGlobalDatas(TRUE);
	POS pos = pAinRatios->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pAinRatios->GetNext(pos);
		CDvmData *pFind = (CDvmData *)pGlobalDatas->FindByID(pData->m_strID);

		if (pFind == NULL)
		{
			pGlobalDatas->AddNewChild((CDvmData *)pData->Clone());
		}
		else
		{
			pFind->m_strValue = pData->m_strValue;
		}
	}
}

CDataGroup* CGuideBook::GetTestApps()
{
	GetTestGlobalDatasMngr();

	return m_pTestGlobalDatasMngr->GetTestApps(FALSE);
}

void CGuideBook::SetTestApps(CDataGroup *pTestApps)
{
	GetTestGlobalDatasMngr();

	m_pTestGlobalDatasMngr->SetTestApps(pTestApps);
}

void CGuideBook::UpdateTestApps(CDataGroup *pTestApps)
{
	GetTestGlobalDatasMngr();

	m_pTestGlobalDatasMngr->UpdateTestApps(pTestApps);
}

void CGuideBook::AddMacroFileToTestApps()
{
	GetTestGlobalDatasMngr();
	CString strTestMacroFile;
	strTestMacroFile = m_pTestMacros->m_strMacroFilePath + m_pTestMacros->m_strMacroFile;

	m_pTestGlobalDatasMngr->AddTestAppInfo(_T("MacroFile")/*STT_CMD_PARA_MacroFile*/, strTestMacroFile);
}


//20230817 huangliang 新增是否勾选定值单
void CGuideBook::UpdateGlobalDifferentData(const CString &strID, const CString &strName, const CString &strDataType, const CString &strValue
										   , const CString &strUnit, const CString &strMin, const CString &strMax, const CString &strStep)
{
	if(strID == _T("") || m_pGlobalDatas == NULL)
		return ;

	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(strID);
	if (pFind == NULL)
	{
		pFind = (CDvmData*)m_pGlobalDatas->AddNewData(strName, strID, strDataType, strValue, strUnit, strMin, strMax, strStep);
	}
	else
	{
		pFind->m_strDataType = strDataType;
		pFind->m_strValue = strValue;
		pFind->m_strUnit = strUnit;
		pFind->m_strMin = strMin;
		pFind->m_strMax = strMax;
		pFind->m_strStep = strStep;
	}
}

CDataTypeValue* CGuideBook::GetDataTypeValue(const CString &strMacroID, const CString &strIDPath, const CString &strValue)
{
	if (m_pTestMacros == NULL)
	{
		return NULL;
	}

	return m_pTestMacros->GetDataTypeValue(strMacroID, strIDPath, strValue);
}
//////////////////////////////////////////////////////////////////////////
//
CString Gb_GetItemPath(CExBaseObject *pItem)
{
	CString strPath = pItem->GetIDPathEx(GBCLASSID_GUIDEBOOK, FALSE);

	return strPath;
}

CExBaseObject* Gb_GetItem(CGuideBook *pGuideBook, CExBaseObject *pItem)
{
	if (pItem == NULL)
	{
		return NULL;
	}

	if (pItem->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		return pItem;
	}

	CString strPath = Gb_GetItemPath(pItem);//pItem->GetIDPathEx(GBCLASSID_GUIDEBOOK, FALSE);

	return Gb_GetItem(pGuideBook, strPath);
}

CExBaseObject* Gb_GetItem(CDevice *pGbDevice, const CString &strItemPath)
{
    CExBaseList listDest;
    CExBaseObject *pCurr = NULL;
    //兼容ID包含'$'符号的情况
    //pGuideBook->Select(strPath, listDest, '$');
    CString strPath = strItemPath;
    pGbDevice->FindByPathChildren(strPath, listDest, '$');

    if (listDest.GetCount() == 0)
    {
         return NULL;
    }
    else
    {

    }

    pCurr = (CExBaseObject *)listDest.GetHead();
    listDest.RemoveAll();

    return pCurr;
}

CExBaseObject* Gb_GetItem(CGuideBook *pGuideBook, const CString &strItemPath)
{
	//2022-3-30 lijunqing
	if (strItemPath.GetLength() == 0)
	{
		 CDevice *pDevice = pGuideBook->GetDevice();
		 return pDevice;
	}

	CExBaseList listDest;
	CExBaseObject *pCurr = NULL;
	//兼容ID包含'$'符号的情况
	//pGuideBook->Select(strPath, listDest, '$');
	CString strPath = strItemPath;

	pGuideBook->FindByPathChildren(strPath, listDest, '$');

	if (listDest.GetCount() == 0)
	{
        CDevice *pDevice = pGuideBook->GetDevice();

        if(pDevice == NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("查找项目出错！GuideBOOK下找不到Device！ItemPath = %s"), strItemPath.GetString());
            return NULL;
        }

        return Gb_GetItem(pDevice, strItemPath);
	}
	else
	{

	}

	pCurr = (CExBaseObject *)listDest.GetHead();
	listDest.RemoveAll();

	return pCurr;
}

//shaolei 2022 0527  通过项目名称形成的路径去查找对应的测试项目
CExBaseObject* Gb_GetItem_Name(CGuideBook *pGuideBook, const CString &strItemPath)
{
	//2022-3-30 lijunqing
	if (strItemPath.GetLength() == 0)
	{
		CDevice *pDevice = pGuideBook->GetDevice();
		return pDevice;
	}

	if (strItemPath == pGuideBook->m_strName)
	{
		return pGuideBook;
	}

	CExBaseList listDest;
	CExBaseObject *pCurr = NULL;
	//兼容ID包含'$'符号的情况
	//pGuideBook->Select(strPath, listDest, '$');
	CString strPath = strItemPath;
	pGuideBook->FindByPathChildren_Name(strPath, listDest, '$');

	if (listDest.GetCount() == 0)
	{
		CDevice *pDevice = pGuideBook->GetDevice();

		if(pDevice == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("查找项目出错！GuideBOOK下找不到Device！ItemPath = %s"), strItemPath.GetString());
			return NULL;
		}

		return Gb_GetItem_Name(pDevice, strItemPath);
	}
	else
	{

	}

	pCurr = (CExBaseObject *)listDest.GetHead();
	listDest.RemoveAll();

	return pCurr;
}

CExBaseObject* Gb_GetItem_Name(CDevice *pGbDevice, const CString &strItemPath)
{
	CExBaseList listDest;
	CExBaseObject *pCurr = NULL;
	//兼容ID包含'$'符号的情况
	//pGuideBook->Select(strPath, listDest, '$');
	CString strPath = strItemPath;
	pGbDevice->FindByPathChildren_Name(strPath, listDest, '$');

	if (listDest.GetCount() == 0)
	{
		return NULL;
	}
	else
	{

	}

	pCurr = (CExBaseObject *)listDest.GetHead();
	listDest.RemoveAll();

	return pCurr;
}

CDataType* Gb_GetDataType(CExBaseObject *pGbObj, CDataTypes *pDataTypes, const CString &strDataType)
{
	CGuideBook *pGuideBook = (CGuideBook *)pGbObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return NULL;
	}

	CDataType *pDataType = NULL;

#ifdef CGuideBook_with_iecfg_file
	if (strDataType == CMtDataTypeMngr::g_strMtDataType_IECConfig)
	{
		if (pGuideBook->m_strIecfgFile.GetLength() > 5)
		{
			pDataType = pGuideBook->m_pIecfgDataType;
		}
		else
		{
			pDataType = CMtDataTypeMngr::FindDataType(pDataTypes, strDataType);
		}
	}
	else
	{
		pDataType = CMtDataTypeMngr::FindDataType(pDataTypes, strDataType);
	}
#else
	pDataType = CMtDataTypeMngr::FindDataType(pDataTypes, strDataType);
#endif

	return pDataType;
}

CString Gb_GetMacroTestPara_Iec61850Config(CMacroTestPara *pPara, const CString &strExpress)
{
#ifdef CGuideBook_with_iecfg_file
	CGuideBook *pGuideBook = (CGuideBook *)pPara->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return strExpress;
	}

	CString strIecfgFile;

	strIecfgFile = pGuideBook->WriteIecfgTempFile(pPara, strExpress);

	if (strIecfgFile.GetLength() < 5)
	{
		strIecfgFile = mtdt_GetIecConfigFilePath();
		strIecfgFile += strExpress;
	}

	return strIecfgFile;
#else
	return strExpress;
#endif
}

BOOL CharVar_CalScriptValue(CCharInterfaceVariable *pCharVar)
{
	CDevice *pDevice = (CDevice*)pCharVar->GetAncestor(GBCLASSID_DEVICE);

// 	if (pDevice == NULL)
// 	{
// 		return FALSE;
// 	}

	double dValue = 0;

	if (Gb_CalParaExpression(pCharVar->m_strScript, pDevice, dValue, TRUE))
	{
		pCharVar->m_strValue.Format(_T("%f"), dValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CExBaseObject* CharVar_GetScriptValObj(CCharInterfaceVariable *pCharVar)
{
	CDevice *pDevice = (CDevice*)pCharVar->GetAncestor(GBCLASSID_DEVICE);

// 	if (pDevice == NULL)
// 	{
// 		return NULL;
// 	}

	CDataObj *pData = pDevice->FindDataObjByID(pCharVar->m_strScript, -1);

	return pData;
}

CString* CharVar_CalScriptValue(CExBaseObject *pData)
{
	ASSERT (pData != NULL);
	CDataObj *pDataObj = (CDataObj*)pData;
	return &pDataObj->m_strValue;
}

void CharVar_CalScriptValue(CExBaseObject *pData, CString &strValue)
{
	ASSERT (pData != NULL);
	CDataObj *pDataObj = (CDataObj*)pData;
	strValue = pDataObj->m_strValue;
}

CString Gb_GetReportFilePath(CExBaseObject *pObj, BOOL bHasRptFileFolder)
{
	CGuideBook *pGuideBook = NULL;

	if (pObj->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		pGuideBook = (CGuideBook *)pObj;
	}
	else
	{
		pGuideBook = (CGuideBook *)pObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	}

	CString strPath = pGuideBook->m_strGuideBookFile;

	if (bHasRptFileFolder)
	{
		long nPos = strPath.ReverseFind('.');
		strPath = strPath.Left(nPos);
		strPath += _P_FOLDER_PATH_SEPARATOR_;
	}
	else
	{
		strPath = GetPathFromFilePathName(strPath);
	}

	return strPath;
}

BOOL Gb_IsReadOnly(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return TRUE;
	}

	CGuideBook *pGuideBook = Gb_GetGuideBook(pObj);
	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return TRUE;
	}

	return pGuideBook->IsReadOnly();
}

CGuideBook* Gb_GetGuideBook(CExBaseObject *pObj)
{
	CGuideBook *pGuideBook = NULL;

	if (pObj->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		pGuideBook = (CGuideBook *)pObj;
	}
	else
	{
		pGuideBook = (CGuideBook *)pObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	}

	return pGuideBook;
}

CGbItemBase* Gb_GetItemByIndex(CExBaseList *pList, long nIndex)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_ITEMS)
		{
			pFind = Gb_GetItemByIndex((CExBaseList*)p, nIndex);
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			if ( ((CGbItemBase*)p)->m_nIndex == nIndex)
			{
				pFind = (CGbItemBase*)p;
				break;
			}
			else
			{
				pFind = Gb_GetItemByIndex((CExBaseList*)p, nIndex);
			}
		}
		else if (Gb_IsGbItemClassID(nClassID))
		{
			if ( ((CGbItemBase*)p)->m_nIndex == nIndex)
			{
				pFind = (CGbItemBase*)p;
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

void Gb_AddDataErrorToRpt_Rslt(CValues *pValues, const CString &strValueID, long nRslt)
{
	CString strErrDataID;
    strErrDataID.Format(_T("%s%s"), g_strDataResultJudgePrevKey.GetString(), strValueID.GetString());
	CValue *pValueRslt = (CValue*)pValues->FindByID(strErrDataID);

	if (pValueRslt == NULL)
	{
		pValueRslt = new CValue();
		pValueRslt->m_strName = strErrDataID;
		pValueRslt->m_strID = strErrDataID;
		pValues->AddNewChild(pValueRslt);
	}

// 	if (nRslt == 0)
// 	{
// 		nRslt = 1;
// 	}
// 	else
// 	{
// 		nRslt = 0;
// 	}

	pValueRslt->m_strValue.Format(_T("%d"), nRslt);
}

#ifndef _PSX_QT_LINUX_
BOOL Gb_GetItemPara(const CString &strExeModule, CExBaseObject *pItem, const CString &strGbXmlFile, BOOL bOpenModule)
{
	CString strItemPath;
	strItemPath = Gb_GetItemPath(pItem);

	return CXAtsSysSvrClient::GbGetItemPara(strExeModule, strGbXmlFile, strItemPath, bOpenModule);
}

BOOL Gb_SetItemPara(const CString &strExeModule, CExBaseObject *pItem, const CString &strGbXmlFile, BOOL bOpenModule)
{
	UINT nClassID = pItem->GetClassID();

	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_GUIDEBOOK || nClassID == GBCLASSID_JOBGUIDE)
	{
		return FALSE;
	}

	if (!CXAtsSysSvrClient::IsModuleParaExist(strExeModule, XMODULE_PARAID_FILE, strGbXmlFile))
	{
		return FALSE;
	}

	CString strItemXml, strItemPath;
	strItemXml = strGbXmlFile;
	strItemXml = ChangeFilePostfix(strItemXml, _T("xml"));
	pItem->SaveXmlFile(strItemXml, CGbXMLKeys::g_pGbXMLKeys);
	strItemPath = Gb_GetItemPath(pItem);
	return CXAtsSysSvrClient::GbSetItemPara(strExeModule, strGbXmlFile, strItemPath, strItemXml, bOpenModule);
}

void OnXAtsSvrClientMsg_GetItemPara(const CString &strExeModule, CGuideBook *pGuideBook, AtsSysSvr::CSysMsg &oSysMsg, BOOL bOpenModule)
{
	CString strGbXml, strItemPath;
	strGbXml = oSysMsg.FindParaByID(XPARA_ID_GBXMLFILE);
	strItemPath = oSysMsg.FindParaByID(XPARA_ID_Item_PATH);
	CExBaseObject *pFind = Gb_GetItem(pGuideBook, strItemPath);

	if (pFind == NULL)
	{
		return;
	}

	Gb_SetItemPara(strExeModule, pFind, pGuideBook->m_strGbXmlFile, bOpenModule);
}

CGbItemBase* OnXAtsSvrClientMsg_SetItemPara(CGuideBook *pGuideBook, AtsSysSvr::CSysMsg &oSysMsg, CExBaseObject **ppOldItem)
{
	CString strGbXml, strItemPath, strItemXml;
	strGbXml = oSysMsg.FindParaByID(XPARA_ID_GBXMLFILE);
	strItemPath = oSysMsg.FindParaByID(XPARA_ID_Item_PATH);
	strItemXml = oSysMsg.FindParaByID(XPARA_ID_Item_xml);

	CExBaseObject *pFind = Gb_GetItem(pGuideBook, strItemPath);

	if (pFind == NULL)
	{
		return NULL;
	}

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	if (!xml_OpenFile(pRWDoc, strItemXml))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("Open file [%s] failed"), strItemXml);
		delete pRWDoc;
		return NULL;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

	if (pDocRoot == NULL)
	{
		::DeleteFile(strItemXml);
		delete pRWDoc;
		return NULL;
	}

	CXmlRWNodeBase *pRoot = pRWDoc->GetFirstRootNode();

	if (pRoot == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Update Item [%s] : temp file error"), strItemPath);
		::DeleteFile(strItemXml);
		delete pRWDoc;
		return NULL;
	}

	CString strNodeName = pRoot->GetNodeName();
	CExBaseObject *pNewItem = NULL;
	BOOL bAddTail = FALSE;
	pNewItem = GbItems_CreateNewChild(strNodeName, bAddTail, CGbXMLKeys::g_pGbXMLKeys);

	if (pNewItem == NULL)
	{
		::DeleteFile(strItemXml);
		delete pRWDoc;
		return NULL;
	}

	pNewItem->XmlRead(*pRoot, CGbXMLKeys::g_pGbXMLKeys);
	CExBaseList *pParent = (CExBaseList*)pFind->GetParent();
	POS pos = pParent->Find(pFind);
	pParent->SetAt(pos, pNewItem);
	pNewItem->SetParent(pParent);
	pNewItem->Update(pFind);

#ifndef GUIDEBOOK_DEV_MODE
	CItemContainer *pItemContainer = (CItemContainer*)pGuideBook->GetItemContainer();

	ASSERT (pItemContainer != NULL);

	if (pItemContainer->m_pGuideBook != NULL)
	{
		pItemContainer->UpdateItem((CGbItemBase*)pNewItem);
		pItemContainer->SetGuideBook(pGuideBook);

		long nFilterIndex = pItemContainer->CreateAttrFilter(GbFilterAttrIndex,GbFilterOptrEqual, ((CGbItemBase*)pNewItem)->m_nIndex);
		pItemContainer->Query(nFilterIndex);
		CGbItemBase *pCurrItem = pItemContainer->GetFirstItem();
		CString strSyntax;

		while (pCurrItem != NULL)
		{
			if (pCurrItem->HasReport())
			{
				pCurrItem->RunResultScript(strSyntax);
			}

			pCurrItem = pItemContainer->GetNextItem();
		}
	}

#endif

	*ppOldItem = pFind;
	delete pRWDoc;
	::DeleteFile(strItemXml);

	return (CGbItemBase*)pNewItem;
}
#endif

BOOL Gb_IsScriptType_LUA(CExBaseObject *pObj)
{
	CGuideBook *pGuideBook = (CGuideBook*)pObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT(pGuideBook != NULL);

	return pGuideBook->IsScriptType_LUA();
}

BOOL Gb_IsScriptType_XVM(CExBaseObject *pObj)
{
	CGuideBook *pGuideBook = (CGuideBook*)pObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT(pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return FALSE;
	}

	return pGuideBook->IsScriptType_XVM();
}

