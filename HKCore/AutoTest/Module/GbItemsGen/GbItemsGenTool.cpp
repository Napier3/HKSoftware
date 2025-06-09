#include "StdAfx.h"
#include "GbItemsGenTool.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
#include "../GuideBook/GuideBookStruDscTool.h"
#ifndef _not_use_autotest_
#include "../TCtrlCntrWorkSpace.h"
#endif

#include "../../../SttStudio/Module/SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
#include "ItemsGenDataMap.h"
#include "../TestControl/TestControlBase.h"
#include "../../../SttStudio/Module/SttCmd/SttAtsCmd.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../XLanguageResourceAts_AutoTest.h"

extern BOOL g_bGbExportXmlReportFile;
extern CDataGroup* g_pGlobalDatas_Gb_CalParaExp;

CGbItemsGenTool::CGbItemsGenTool(void)
{
	m_bGenerateItemsOnly_CmdWzd = FALSE;
	m_pChMaps = NULL;
	m_pUIParasGroup = NULL;
	m_pGbItemsGen = NULL;
	m_pGuideBook = NULL;
	m_pTestMacros = NULL;
	m_nUIType = TESTMACRO_UI_TYPE_ORIGINAL;
	m_bHasDigital = FALSE;
	m_pCurrInstInterface = NULL;
    m_nGenWithDebug = 0;
	m_pIecDatasMngr = NULL;
	m_pSysParameter = NULL;
	m_pMacroTest = NULL;
	m_pGbItemBase = NULL;
	m_pDevReset = NULL;
	m_nGenMode = TEMPLATE_GEN_MODE_NORMAL;
	m_pCharacteristics = NULL;
	m_strTestClass = TEST_CLASS_RELAY;
	m_pCommCmd = NULL;
	m_pItems_SelfDef = NULL;
#ifndef _PSX_QT_LINUX_
	m_bMacroTestSaveParas = TRUE;
#else
	m_bMacroTestSaveParas = FALSE;
#endif

	m_oGroupCmdWzdReply.m_strID = STT_CMD_PARA_CommCmd;
	m_oGroupCmdWzdReply.m_strName = _T("通讯命令生成配置");

	m_pCmdAddGrp = NULL;
	m_pItems_ImportDvm = NULL;
	m_pAinDataMapCfg = NULL;
	m_nLoopTest = 1;//是否闭环测试。闭环测试需要添加通讯命令。默认闭环测试。
}

CGbItemsGenTool::~CGbItemsGenTool(void)
{
	m_nGenMode = TEMPLATE_GEN_MODE_NORMAL;
	//Reset();
	m_nGenWithDebug = 0;

	if (m_pGbItemsGen != NULL)
	{
		delete m_pGbItemsGen;
		m_pGbItemsGen = NULL;
	}

	if (m_pUIParasGroup != NULL)
	{
		m_oUiParas_SortIdPath.RemoveAll();
		delete m_pUIParasGroup;
		m_pUIParasGroup = NULL;
		g_pGlobalDatas_Gb_CalParaExp = NULL;
	}

	if (m_pTestMacros != NULL)
	{
		delete m_pTestMacros;
		m_pTestMacros = NULL;
	}

	if (m_pChMaps != NULL)
	{
		delete m_pChMaps;
		m_pChMaps = NULL;
	}

	if (m_pIecDatasMngr != NULL)
	{
		delete m_pIecDatasMngr;
		m_pIecDatasMngr = NULL;
	}

	if (m_pSysParameter != NULL)
	{
		delete m_pSysParameter;
		m_pSysParameter = NULL;
	}

	if (m_pCharacteristics != NULL)
	{
		delete m_pCharacteristics;
		m_pCharacteristics = NULL;
	}

	if (m_pCommCmd != NULL)
	{
		delete m_pCommCmd;
		m_pCommCmd = NULL;
	}

	if (m_pCmdAddGrp != NULL)
	{
		m_pCmdAddGrp->RemoveAll();
		delete m_pCmdAddGrp;
		m_pCmdAddGrp = NULL;
	}

	if (m_pAinDataMapCfg != NULL)
	{
		delete m_pAinDataMapCfg;
		m_pAinDataMapCfg = NULL;
	}

	FreeItems_DevReset();
	FreeItems_ImportDvm();
}

void CGbItemsGenTool::InitGbGenSysPath(const CString &strSysPath)
{
	CString strPath = strSysPath;

	if (strPath.GetLength() == 0)
	{
		strPath = _P_GetSystemPath();
	}

	m_strConfigPath = strPath;
	m_strConfigPath += g_pszKeyConfig;
	m_strConfigPath += _T("/");

	m_strDbPath = strPath;
	m_strDbPath += g_pszKeyDB;
	m_strDbPath += _T("/");

	AfterInitSysPath();
}

void CGbItemsGenTool::AfterInitSysPath()
{
	CString strFile = GetConfigPath();
	strFile += FILENAME_STTSYSTEMCONFIG;

	m_oSttSystemConfig.OpenSystemConfig(strFile);
}

CString CGbItemsGenTool::GetDeviceModel()
{
	return m_oSttSystemConfig.GetDevModel();
}

CString CGbItemsGenTool::GetDevice_RelPath()
{
	CString strFile, strModel, strFile2;
	strFile = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_Device;

	strModel = GetDeviceModel();  //获取型号
	strFile += _T("/");
	strFile += strModel;
	strFile += _T("/");
	strFile2 = strFile;  //  DB/Device/型号/

	strFile += strModel;
	strFile += _T(".xml");  //  DB/Device/型号/型号.xml

	if (!IsFileExist(strFile))
	{
		return _T("");
	}

	CDvmDataset oModel;
	oModel.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	strFile2 += oModel.m_strID;
	strFile2 += _T("/");  //  DB/Device/型号/编号/

	return strFile2;
}

void CGbItemsGenTool::FreeItems_DevReset()
{
	if (m_pDevReset == NULL)
	{
		return;
	}

	if (m_pDevReset->GetParent() == NULL)
	{
		delete m_pDevReset;
		m_pDevReset = NULL;
	}
}

//针对导入模型后生成的项目，以项目位置为准，不同位置的项目，都用一个临时的CItems进行管理
//，这个临时的CItems，不存放到模板中。因此释放的时候，需要格外小心
void CGbItemsGenTool::FreeItems_ImportDvm(BOOL bDelete)
{
	if (m_pItems_ImportDvm == NULL)
	{
		return;
	}

	POS pos = m_pItems_ImportDvm->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = m_pItems_ImportDvm->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pChildItems = (CItems *)pObj;
			pChildItems->RemoveAll();  //移除的子对象为需要存放到模板中的通讯命令项目
			m_pItems_ImportDvm->Delete(pChildItems);
		}
	}

	if (bDelete)
	{
		delete m_pItems_ImportDvm;
		m_pItems_ImportDvm = NULL;
	}
}

void CGbItemsGenTool::FreeItems_AinCfg()
{
	if (m_pItems_AinCfg == NULL)
	{
		return;
	}

	POS pos = m_pItems_AinCfg->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = m_pItems_AinCfg->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pChildItems = (CItems *)pObj;  //这一级，同样是不放到模板中，临时对象。ID记录项目路径
			pChildItems->RemoveAll();  //移除的子对象为需要存放到模板中的通讯命令项目
		}
	}

	delete m_pItems_AinCfg;
	m_pItems_AinCfg = NULL;
}

//查找结果误差判断逻辑
CDvmData* CGbItemsGenTool::SelectErrorLogic()
{
	if (m_pUIParasGroup == NULL)
	{
		return NULL;
	}

	CDvmData *pFind = NULL;
	CExBaseList oList;
	m_pUIParasGroup->SelectDatas_IDHas(_T("ErrorLogic"), oList, FALSE);
	pFind = (CDvmData *)oList.GetHead();
	oList.RemoveAll();
	return pFind;
}

//查找误差限
long CGbItemsGenTool::SelectErrorLimits(CExBaseList &oListError)
{
	if (m_pUIParasGroup == NULL)
	{
		return 0;
	}

	//约定误差限放在界面参数的根节点，不进行嵌套。因此不递归查找
	m_pUIParasGroup->SelectDatas_IDHas(_T("Err"), oListError, FALSE);

	return oListError.GetCount();
}

//查找整定值
long CGbItemsGenTool::SelectDatasSets(CExBaseList &oListSets)
{
	if (m_pUIParasGroup == NULL)
	{
		return 0;
	}

	//约定整定值放在界面参数的根节点，不进行嵌套。因此不递归查找
	m_pUIParasGroup->SelectDatas_IDHas(_T("Set"), oListSets, FALSE);

	return oListSets.GetCount();
}

CDvmDataset* CGbItemsGenTool::GetGlobalDatas()
{
	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	return m_pGuideBook->m_pGlobalDatas;
}

CExBaseList* CGbItemsGenTool::GetSysPara()
{
	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	return pDevice->m_pSysParas;
}

void CGbItemsGenTool::SetGuideBook(CGuideBook* pGuideBook)
{
    m_pGuideBook = pGuideBook;
}

CTestMacro* CGbItemsGenTool::GetTestMacroByID(const CString &strMacroID)
{
	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	CTestMacros *pMacros = m_pGuideBook->m_pTestMacros;

	if (pMacros == NULL)
	{
		return NULL;
	}

	return (CTestMacro *)pMacros->FindByID(strMacroID);
}

CGbItemBase* CGbItemsGenTool::GetItems_BeforeTest()
{
	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	CExBaseList oList;
	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	Gb_GetAllItemsByID(pDevice, STT_ITEMS_ID_BEFORETEST, oList, GBCLASSID_ITEMS);
	CGbItemBase *pFind = (CGbItemBase *)oList.GetHead();
	oList.RemoveAll();
	return pFind;
}

CString CGbItemsGenTool::GetItemsPath_BeforeTest()
{
	CGbItemBase *pBeforeTest = GetItems_BeforeTest();

	if (pBeforeTest == NULL)
	{
		return _T("");
	}

	return pBeforeTest->GetIDPathEx(GBCLASSID_DEVICE, TRUE);
}

UINT CGbItemsGenTool::GetTemplateGenMode()
{
	return m_nGenMode;
}

void CGbItemsGenTool::SetTemplateGenMode(UINT nMode)
{
	m_nGenMode = nMode;
}

void CGbItemsGenTool::SetChMaps(CSttChMaps *pChMaps)
{
	if (m_pChMaps != NULL)
	{
		delete m_pChMaps;
	}

	m_pChMaps = pChMaps;
}

void CGbItemsGenTool::SetIecCfgDatasMngr(CIecCfgDatasMngr *pIecDatasMngr)
{
	if (m_pIecDatasMngr != NULL)
	{
		delete m_pIecDatasMngr;
	}

	m_pIecDatasMngr = pIecDatasMngr;
}

void CGbItemsGenTool::SetSysParameter(CSttMacro *pSysParameter)
{
	if (m_pSysParameter != NULL)
	{
		delete m_pSysParameter;
	}

	m_pSysParameter = pSysParameter;

	//同步系统参数到CDevice的m_pSysPara；
	CSttParas *pParas = m_pSysParameter->GetParas();
	CExBaseList oList;
	pParas->SelectAllDatas(oList);
	m_pGuideBook->UpdateSysPara(&oList, TRUE);
	oList.RemoveAll();
}

void CGbItemsGenTool::Reset()
{
	m_strTestClass = TEST_CLASS_RELAY;
    m_nGenWithDebug = 0;

	if (m_pGbItemsGen != NULL)
	{
		delete m_pGbItemsGen;
		m_pGbItemsGen = NULL;
	}

	if (m_pUIParasGroup != NULL)
	{
		m_oUiParas_SortIdPath.RemoveAll();
		delete m_pUIParasGroup;
		m_pUIParasGroup = NULL;
		g_pGlobalDatas_Gb_CalParaExp = NULL;
	}

	if (m_pTestMacros != NULL)
	{
		delete m_pTestMacros;
		m_pTestMacros = NULL;
	}

	if (m_pCharacteristics != NULL)
	{
		delete m_pCharacteristics;
		m_pCharacteristics = NULL;
	}

	if (m_nGenMode == TEMPLATE_GEN_MODE_NORMAL)
	{
		m_bHasDigital = FALSE;

		if (m_pGuideBook != NULL)
		{
			m_pGuideBook->FreeGuideBook();
		}
	}
	else
	{
		if (m_pGuideBook != NULL)
		{
			m_oBeforeTestBk.DeleteAll();
			m_pGuideBook->FreeGuideBook_ExceptItems(STT_ITEMS_ID_BEFORETEST, &m_oBeforeTestBk);
		}
	}

	if (m_pSysParameter != NULL)
	{
		//shaolei 2025-2-6 
		//因为系统参数还需要更新至模板CDevice下m_pSysPara，因此需要释放重新创建
		delete m_pSysParameter;
		m_pSysParameter = NULL;
	}
}

BOOL CGbItemsGenTool::Init(const CString &strUI)
{
	CSttMacroTestUI_TestMacroUIs *pUIs = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIs();
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = (CSttMacroTestUI_TestMacroUI *)pUIs->FindByID(strUI);	

	if (pTestMacroUI == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到参数界面配置信息【界面ID = %s】"), strUI.GetString());
		return FALSE;
	}

	Init_UIType(pTestMacroUI);

	if (IsUI_Error())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数界面类型配置出错【界面ID = %s】"), strUI.GetString());
		return FALSE;
	}

	BOOL bRet1 = Init_GenFile(pTestMacroUI);
	
	if (bRet1 && m_pGbItemsGen != NULL)
	{
		if (!m_pGbItemsGen->m_strEngineProgID.IsEmpty())
		{
#ifndef _not_use_autotest_
			CTCtrlCntrWorkSpace::s_SetPpEngineProgID(m_pGbItemsGen->m_strEngineProgID);
#endif

			if (m_pGuideBook != NULL)
			{
				m_pGuideBook->m_strPpEngineProgID = m_pGbItemsGen->m_strEngineProgID;
			}
		}
	}

	BOOL bRet2 = Init_UIParaFile(pTestMacroUI);
	BOOL bRet3 = Init_HdRsFile(pTestMacroUI);   //初始化硬件通道，硬件通道配置作为非必选项，初始化结果不作为返回结果。
	BOOL bRet4 = Init_IecCfg();
	BOOL bRet5 = Init_SystemParas();
	//可以不用单独初始化测试功能文件，在m_pGuideBook中有对应的测试功能集合m_pTestMacros
	//Init_TestMacroFile();

	return (bRet1 && bRet2);
}

BOOL CGbItemsGenTool::Init(CDataGroup *pTestMacroUI)
{
	Init_UIType(pTestMacroUI);

	CString strTestMacroID;
	pTestMacroUI->GetDataValue(STT_CMD_PARA_TestMacroUI_ID, strTestMacroID);

	if (IsUI_Error())
	{
        /*CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数界面类型配置出错【界面ID = %s】"), strTestMacroID.GetString());*/
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("UI_Error【UI_ID = %s】"), strTestMacroID.GetString());
		return FALSE;
	}

	BOOL bRet1 = Init_GenFile(pTestMacroUI);
	BOOL bRet2 = Init_UIParaFile(pTestMacroUI);
	BOOL bRet3 = Init_HdRsFile(pTestMacroUI);   //初始化硬件通道，硬件通道配置作为非必选项，初始化结果不作为返回结果。
	BOOL bRet4 = Init_IecCfg();
	BOOL bRet5 = Init_SystemParas();
	BOOL bRet6 = OpenCommCmdWzdCfgFile();
	OpenSttCommCmdCfgFile();

	//可以不用单独初始化测试功能文件，在m_pGuideBook中有对应的测试功能集合m_pTestMacros
	//Init_TestMacroFile();

	if (bRet1 && m_pGbItemsGen != NULL)
	{
		if (!m_pGbItemsGen->m_strEngineProgID.IsEmpty())
		{
#ifndef _not_use_autotest_
			CTCtrlCntrWorkSpace::s_SetPpEngineProgID(m_pGbItemsGen->m_strEngineProgID);
#endif

            if (m_pGuideBook != NULL)
            {
                m_pGuideBook->m_strPpEngineProgID = m_pGbItemsGen->m_strEngineProgID;
            }
		}
	}

	return (bRet1 && bRet2);
}

void CGbItemsGenTool::Init_UIType(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	if (pTestMacroUI->IsUIOriginal())
	{
		m_nUIType = TESTMACRO_UI_TYPE_ORIGINAL;
	}
	else if (pTestMacroUI->IsUIWeb())
	{
		m_nUIType = TESTMACRO_UI_TYPE_WEB;
	}
	else 
	{
		m_nUIType = TESTMACRO_UI_TYPE_ERROR;
	}
}

BOOL CGbItemsGenTool::Init_GenFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	bool bOpenFile = false;
	if (IsUI_Original())
	{
		//原生态模式下，没有ui-file。
		if (!pTestMacroUI->m_strGenFile.IsEmpty())
		{
			bOpenFile = OpenGenFile(pTestMacroUI->m_strGenFile);
		}

		if (m_pGbItemsGen != NULL)
		{
			delete m_pGbItemsGen;
			m_pGbItemsGen = NULL;
		}

		return TRUE;
	}

	bOpenFile = OpenGenFile(pTestMacroUI->m_strGenFile);

	if (!bOpenFile)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Init_GenFile failed, open file [%s] failed!"), pTestMacroUI->m_strGenFile.GetString());
	}

	return bOpenFile;
}

//初始化界面参数，解析文件
BOOL CGbItemsGenTool::Init_UIParaFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	BOOL bOpenFile = false;

	if (IsUI_Original())
	{
		//原生态模式下，没有ui-file
		if (! pTestMacroUI->m_strUI_ParaFile.IsEmpty())
		{
			bOpenFile = OpenUIParaFile(pTestMacroUI->m_strUI_ParaFile);
		}

		return TRUE;
	}

	bOpenFile = OpenUIParaFile(pTestMacroUI->m_strUI_ParaFile);

	if (! bOpenFile)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Init_UIParaFile failed, open file [%s] failed!"), pTestMacroUI->m_strUI_ParaFile.GetString());
	}

	return bOpenFile;
}

BOOL  CGbItemsGenTool::Init_HdRsFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	if (m_pChMaps != NULL)
	{
		//不同的模块，初始的硬件通道配置可能不一致，此处需删除后重新初始化
		delete m_pChMaps;
		m_pChMaps = NULL;
	}

	return OpenHdRsFile(pTestMacroUI->m_strHdRsFile);
}

BOOL CGbItemsGenTool::Init_IecCfg()
{
	if (m_pIecDatasMngr != NULL)
	{
		return TRUE;
	}

	CString strFile;
	strFile = GetConfigPath(); //2022-3-29 lijunqing _P_GetConfigPath();
	strFile += FILENAME_STTIECCONCFIG;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("IecCfgFile [%s] not exist"), strFile.GetString());
		return FALSE;
	}

	m_pIecDatasMngr = new CIecCfgDatasMngr;
	BOOL bRet = m_pIecDatasMngr->OpenIecCfgFile(strFile);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("IecCfgFile [%s] Open Failed"), strFile.GetString());
		delete m_pIecDatasMngr;
		m_pIecDatasMngr = NULL;
		return FALSE;
	}

	return TRUE;
}

BOOL CGbItemsGenTool::Init_SystemParas()
{
	if (m_pSysParameter != NULL)
	{
		return TRUE;
	}

	CString strFile, strFile2;
	strFile = GetDBPath(); //2022-3-29 lijunqing _P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_Device;
	strFile += _T("/");
	strFile += FILENAME_STTSYSTEMPARAS; //当具体型号指定的文件不存在时，用这个：DB/Device/SystemParas.sysxml

	strFile2 = GetDevice_RelPath();  //  DB/Device/型号/编号/
	strFile2 += FILENAME_STTSYSTEMPARAS;

	if (!IsFileExist(strFile2))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SystemParasFile [%s] not exist-1"), strFile2.GetString());
	}
	else
	{
		strFile = strFile2;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SystemParasFile [%s] not exist-2"), strFile.GetString());
		return FALSE;
	}

	m_pSysParameter = new CSttMacro;
	m_pSysParameter->SetCreateMacroChild(TRUE);
	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = m_pSysParameter->OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SystemParasFile [%s] Open Failed"), strFile.GetString());
		delete m_pSysParameter;
		m_pSysParameter = NULL;
		return FALSE;
	}

	//同步系统参数到CDevice的m_pSysPara；
	if (m_pGuideBook != NULL)
	{
		CSttParas *pParas = m_pSysParameter->GetParas();
		CExBaseList oList;
		pParas->SelectAllDatas(oList);
		m_pGuideBook->UpdateSysPara(&oList, TRUE);
		oList.RemoveAll();
	}

	return TRUE;
}

//shaolei  2023-11-14 合并单元自动测试改为采用模板生成文件生成方式
//此时是否包含模板生成文件不能作为原生界面的判据,如果包含m_strUI_File则为网页界面,否则为原生界面
void CGbItemsGenTool::Init_UIType(CDataGroup *pGroup)
{
	CString /*strGenFile, */strUIFile;
	//pGroup->GetDataValue(STT_CMD_PARA_GenFile, strGenFile);
	pGroup->GetDataValue(STT_CMD_PARA_UIFile, strUIFile);

	if (/*strGenFile.IsEmpty() && */strUIFile.IsEmpty())
	{
		m_nUIType = TESTMACRO_UI_TYPE_ORIGINAL;
	}
	else if (/*!strGenFile.IsEmpty() && */!strUIFile.IsEmpty())
	{
		m_nUIType = TESTMACRO_UI_TYPE_WEB;
	}
	else 
	{
		m_nUIType = TESTMACRO_UI_TYPE_ERROR;
	}
}

BOOL CGbItemsGenTool::Init_GenFile(CDataGroup *pGroup)
{
	CString strGenFile;
	pGroup->GetDataValue(STT_CMD_PARA_GenFile, strGenFile);

	if (IsUI_Original())
	{
		//原生态模式下，没有ui-file
		if (! strGenFile.IsEmpty())
		{
			return OpenGenFile(strGenFile);
		}

		if (m_pGbItemsGen != NULL)
		{
			delete m_pGbItemsGen;
			m_pGbItemsGen = NULL;
		}

		return TRUE;
	}

	return OpenGenFile(strGenFile);
}

BOOL CGbItemsGenTool::Init_UIParaFile(CDataGroup *pGroup)
{
	CString strUIFile;
	pGroup->GetDataValue(STT_CMD_PARA_UIParaFile, strUIFile);

	if (IsUI_Original())
	{
		//原生态模式下，没有ui-file
		if (! strUIFile.IsEmpty())
		{
			OpenUIParaFile(strUIFile);
		}

		return TRUE;
	}

	return OpenUIParaFile(strUIFile);
}

BOOL CGbItemsGenTool::Init_HdRsFile(CDataGroup *pGroup)
{
	if (m_pChMaps != NULL)
	{
		//不同的模块，初始的硬件通道配置可能不一致，此处需删除后重新初始化
		delete m_pChMaps;
		m_pChMaps = NULL;
	}

	CString strHdRsFile;
	pGroup->GetDataValue(STT_CMD_PARA_HdRsFile, strHdRsFile);

	return OpenHdRsFile(strHdRsFile);
}

BOOL CGbItemsGenTool::OpenGenFile(const CString &strFileName)
{
	CString strFile;
    strFile = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_ATSGEN;
    strFile += _T("/");
	strFile += strFileName;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("GenFile [%s] not exist"), strFile.GetString());
		return FALSE;
	}

	if (m_pGbItemsGen == NULL)
	{
		m_pGbItemsGen = new CGbItemsGen;
	}

	m_pGbItemsGen->DeleteAll();
	BOOL bRet = m_pGbItemsGen->OpenXmlFile(strFile, CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("GenFile [%s] Open Failed"), strFile.GetString());
		delete m_pGbItemsGen;
		m_pGbItemsGen = NULL;
	}

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(m_pGbItemsGen, strFileName);
#endif

	return bRet;
}

BOOL CGbItemsGenTool::OpenUIParaFile(const CString &strFileName)
{
	CString strFile;
	strFile = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_ATSGEN;
    strFile += _T("/");
	strFile += strFileName;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("UIParaFile [%s] not exist"), strFile.GetString());
		return FALSE;
	}

	if (m_pUIParasGroup == NULL)
	{
		m_pUIParasGroup = new CDataGroup();
	}

	m_oUiParas_SortIdPath.RemoveAll();
	m_pUIParasGroup->DeleteAll();
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = m_pUIParasGroup->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("UIParaFile [%s] Open Failed"), strFile.GetString());
		delete m_pUIParasGroup;
		m_pUIParasGroup = NULL;
		g_pGlobalDatas_Gb_CalParaExp = NULL;
	}

	AfterInitUIParas();
	return bRet;
}

//shaolei 2024-4-10修改。
/*
1、Linux系统下，不涉及不同设备不同型号，因此硬件配置文件的路径是DB/Device；
2、Windows系统下，涉及不同设备不同型号之间的切换，因此硬件配置文件的路径是DB/Device下具体型号、具体编号的子路径
*/
BOOL CGbItemsGenTool::OpenHdRsFile(const CString &strFileName)
{
	BOOL bRet = FALSE;
	CString strFile, strFile2;
	strFile = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_Device;
 	strFile += _T("/");
 	strFile += strFileName;  //当具体型号指定的文件不存在时，用这个：DB/Device/ChMapConfig.4u3i

	strFile2 = GetDevice_RelPath();  //  DB/Device/型号/编号/
	strFile2 += strFileName;
	
	if (!IsFileExist(strFile2))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("HdRsFile [%s] not exist-1"), strFile2.GetString());
	}
	else
	{
		strFile = strFile2;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("HdRsFile [%s] not exist-2"), strFile.GetString());
		return FALSE;
	}

	if (m_pChMaps == NULL)
	{
		m_pChMaps = new CSttChMaps();
	}

	m_pChMaps->DeleteAll();
	bRet = m_pChMaps->OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("HdRsFile [%s] Open Failed"), strFile.GetString());
		delete m_pChMaps;
		m_pChMaps = NULL;
	}

	return bRet;
}

/*
<group name="通讯命令生成向导配置" id="comm-cmd-wzd-cfg">
	<group name="精度测试" id="YC">
		<group name="启动报告" id="RegisterReport">
			<data name="遥测数据集" id="dsAin"/>
		</group>
		<group name="停止报告" id="UnRegisterReport">
			<data name="遥测数据集" id="dsAin"/>
		</group>
		</group>
	<group name="信息规范化测试-保护功能" id="Info-Relay">
		<group name="启动报告" id="RegisterReport">
			<data name="动作事件数据集" id="dsTripInfo"/>
		</group>
		<group name="停止报告" id="UnRegisterReport">
			<data name="动作事件数据集" id="dsTripInfo"/>
		</group>
	</group>
	……
</group>
*/
BOOL CGbItemsGenTool::OpenCommCmdWzdCfgFile()
{
	if (m_oCommCmdWzdCfg.GetCount() > 0)
	{
		return TRUE;
	}

	CString strFile = GetConfigPath();
	strFile += FILENAME_COMMCMDWZDCFG;

	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = m_oCommCmdWzdCfg.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oCommCmdWzdCfg, FILENAME_COMMCMDWZDCFG);
#endif


	return bRet;
}

BOOL CGbItemsGenTool::OpenSttCommCmdCfgFile()
{
	if (m_oSttCommCmdCfg.GetCount() > 0)
	{
		return TRUE;
	}

	CString strFile = GetConfigPath();
	strFile += FILENAME_STTCOMMCMDCFG;

	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = m_oSttCommCmdCfg.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oSttCommCmdCfg, FILENAME_STTCOMMCMDCFG);
#endif

	return bRet;
}

BOOL CGbItemsGenTool::Init_DvmDevice_Ex(const CString &strDvmFile)
{
	m_strDvmFile = strDvmFile;
	m_oDvmDevice.DeleteAll();

	if (m_strDvmFile.IsEmpty())
	{
		return FALSE;
	}

	CString strFullPath;
	Init_DvmDevice_GetFullPath(strFullPath);
	m_strDvmFile = strFullPath;
	SetBinaryFileName();
	return m_oDvmDevice.OpenXmlFile(m_strDvmFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CGbItemsGenTool::Init_DvmDevice(const CString &strDvmFile)
{
	if (m_strDvmFile != strDvmFile)
	{
		m_strDvmFile = strDvmFile;
		CString strFullPath;
		Init_DvmDevice_GetFullPath(strFullPath);
		m_strDvmFile = strFullPath;
		Init_DvmDevice();
	}
	
#ifndef _not_use_autotest_
	CTCtrlCntrWorkSpace::s_SetPpDeviceFile(strDvmFile);
#endif
	m_pGuideBook->m_strDeviceModelFile = strDvmFile/*m_strDvmFile*/;   //此处应该记录全路径；2025-2-22改为记录相对路径
}

void CGbItemsGenTool::Init_DvmDevice()
{
	m_oDvmDevice.DeleteAll();
	//第二个慢的地方
	m_oDvmDevice.OpenXmlFile(m_strDvmFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("还没创建测试，初始化模型失败！"));
		return;
	}

	CCpus *pCpus = pDevice->GetCpus();
	pCpus->OpenModelFile(m_strDvmFile);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("初始化模型结束 = %s"), m_strDvmFile.GetString());
}

void CGbItemsGenTool::Init_DvmDevice_GetFullPath(CString &strFullPath)
{
	if (m_strDvmFile.IsEmpty())
	{
		return;
	}

	//2025-2-22 采用相对路径，上位机传值为“NRJB/***.xml”
	//故此处补全绝对路径即可
	if (!IsFileExist(m_strDvmFile))
	{
		//文件不存在，则表示是相对路径
		strFullPath = _P_GetInstallPath();
		strFullPath += _T("e-Protocol/Library/");  //2025-3-4约定相对路径是相对e-Protocol/Library下的
		strFullPath += m_strDvmFile;
	}
	else
	{
		strFullPath = m_strDvmFile;
	}

/*
	if (m_strDvmFile.Find(_T("/")) < 0 && m_strDvmFile.Find(_T("\\")) < 0)
	{
#ifdef _PSX_QT_LINUX_
		strPath = _P_GetLibraryPath();
#else
		strPath = _P_GetInstallPath();
		strPath += _T("e-Protocol/Library/");
#endif
		strPath += m_strDvmFile;
	}
#ifndef _PSX_QT_LINUX_
	else if (m_strDvmFile.Find(_T(":")) < 0)   //windows下，可能携带的相对路径。例如：NR104_BJ/STD_MODEL.xml
	{
		strPath = _P_GetInstallPath();
		strPath += _T("e-Protocol/Library/");
		strPath += m_strDvmFile;
	}
#endif
	else 
	{
		strPath = m_strDvmFile;
	}
*/

	if (!IsFileExist(strFullPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("模型文件【%s】不存在，初始化模型失败！"), strFullPath.GetString());
		return;
	}
}

void CGbItemsGenTool::Init_TestMacroFile()
{
	CString strFile;
	strFile =_P_GetInstallPath();
	strFile += _T("e-Report\\Config\\");
	strFile += CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
	strFile += _T("\\");
	strFile += CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroFile;

	if (m_pTestMacros == NULL)
	{
		m_pTestMacros = new CTestMacros;
	}

	m_pTestMacros->DeleteAll();
	m_pTestMacros->OpenXmlFile(strFile, CTestMacroXmlRWKeys::g_pXmlKeys);
}

BOOL CGbItemsGenTool::NeedSetRootNode(const CString &strMacroID)
{
	if (strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		return FALSE;
	}

	if (strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		return FALSE;
	}

	if (strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		return FALSE;
	}

	return TRUE;
}

//这里只处理模型文件、规约模板相关的。通讯参数的，在外部已经处理过了
void CGbItemsGenTool::Ats_ConfigDevice(CDataGroup *pSttParas)
{
	CString strDvmFile, strPpXmlFile, strEngineProgID;
	pSttParas->GetDataValue(STT_CMD_PARA_DvmFile, strDvmFile);
	pSttParas->GetDataValue(STT_CMD_PARA_EngineProgID, strEngineProgID);
	pSttParas->GetDataValue(XPARA_ID_PPXMLFILE, strPpXmlFile);
	Init_DvmDevice(strDvmFile);

#ifndef _not_use_autotest_
	CTCtrlCntrWorkSpace::s_SetPpTemplateFile(strPpXmlFile);
	CTCtrlCntrWorkSpace::s_SetPpEngineProgID(strEngineProgID);
#endif

	if (strPpXmlFile.GetLength() > 5)
	{
		m_pGuideBook->m_strPpTemplateFile = strPpXmlFile;
	}

	m_pGuideBook->m_strPpEngineProgID = strEngineProgID;

	SetBinaryFileName();
}

void CGbItemsGenTool::GetXml_TestMacroCharParas(CString &strParas)
{
	if (m_pCharacteristics == NULL)
	{
		return;
	}

	strParas = m_pCharacteristics->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys);
}

void CGbItemsGenTool::GetXml_TestMacroUiParas(CString &strParas, const CString &strMacroID)
{
	if (m_pUIParasGroup == NULL)
	{
		return;
	}

	if (! strMacroID.IsEmpty())
	{
		SortTestMacroUiParas(m_pUIParasGroup, strMacroID);
	}

//#ifndef _PSX_QT_LINUX_
	//if (m_bMacroTestSaveParas)
	{
		++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();

		strParas = m_pUIParasGroup->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);

		--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();
	}
//#endif
}

void CGbItemsGenTool::GetXml_TestMacroUiParas(CString &strParas, CDataGroup *pUIParas, const CString &strMacroID)
{
	if (pUIParas == NULL)
	{
		return;
	}

	if (! strMacroID.IsEmpty())
	{
		SortTestMacroUiParas(pUIParas, strMacroID);
	}

//#ifndef _PSX_QT_LINUX_
	//if (m_bMacroTestSaveParas)
	{
		++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();

		strParas = pUIParas->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);

		--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();
	}
//#endif
}

//界面参数和TestMacro中的默认参数比较，删除值 = 默认值的参数
void CGbItemsGenTool::SortTestMacroUiParas(CDataGroup *pUiParas, const CString &strMacroID)
{
	//当测试功能不为空时，需要根据测试功能在TestMacro.xml中的定义，过滤掉值 = 默认值的参数，以节省流量
	CTestMacro *pTestMacro = GetTestMacroByID(strMacroID);

	if (pTestMacro != NULL)
	{
		//通过测试模板生成服务生成的功能，从TestMacro.xml中看，目前所有的故障参数都定义在扩展故障参数中；
		//此处直接使用扩展故障参数，后续有其它问题再修改
		CDataGroup *pFaultParasEx = pTestMacro->GetFaultParasEx();
		SortTestMacroUiParas_ByDefault(m_pUIParasGroup, pFaultParasEx);

		//如果是状态序列，根据状态数，删除多余的状态的参数
		if (strMacroID == _T("StateTest"))
		{
			SortTestMacroUiParas_ByStateCount(m_pUIParasGroup);
			SortTestMacroUiParas_RsltEvalute(m_pUIParasGroup);
		}
	}
}

//界面参数和TestMacro中的故障参数的默认值比较，删除“值 = 默认值”的参数
//界面参数与TestMacro中的故障参数的结构应当完全一致。
void CGbItemsGenTool::SortTestMacroUiParas_ByDefault(CDataGroup *pUiParas, CDataGroup *pFaultParas)
{
#ifndef _PSX_QT_LINUX_
	return;   //windows这边保留所有的结果参数
#endif

	if (m_nGenMode ==TEMPLATE_GEN_MODE_SAVE)
	{
		//Linux下，保存模板或记录时，不对参数进行默认值检查和删减
		return;
	}

	//以下代码是根据默认值，删除“值 = 默认值”的参数
	if (pUiParas == NULL || pFaultParas == NULL)
	{
		return;
	}

	UINT nClassID = 0;
	UINT nFaultParaClassID = 0;
	CExBaseObject *pObj = NULL;   //遍历的界面参数，可嵌套
	CExBaseObject *pFaultPara = NULL;  //根据界面参数的ID，查找到的故障参数，可嵌套
	POS pos = pUiParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pUiParas->GetNext(pos);

		if (pObj->m_strID == _T("StateCount"))
		{
			//对于状态序列，状态数始终保留
			continue;
		}

		pFaultPara = pFaultParas->FindByID(pObj->m_strID);

		if (pFaultPara == NULL)
		{
			//说明是界面参数比TestMacro定义中多出来的参数
			//保留该多出来的参数。例如：状态序列界面多的是否选择的参数 bSelect
			continue;
		}

		nClassID = pObj->GetClassID();
		nFaultParaClassID = pFaultPara->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			if (nClassID != nFaultParaClassID)
			{
				//对于嵌套的group，界面参数和TestMacro中定义的参数的类型必须一致
				continue;
			}

			CDataGroup *pUiGrp = (CDataGroup *)pObj;
			CDataGroup *pFaultParaGrp = (CDataGroup *)pFaultPara;
			SortTestMacroUiParas_ByDefault(pUiGrp, pFaultParaGrp);  //嵌套的参数，递归调用

			if (pUiGrp->GetCount() == 0)
			{
				pUiParas->Delete(pUiGrp);
			}

			continue;
		}

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pUiData = (CDvmData *)pObj;

			if (nFaultParaClassID != DTMCLASSID_CSHORTDATA)
			{
				//对于其它参数，TestMacro中定义的参数的类型必须是CShortData
				continue;
			}

			CShortData *pParaData = (CShortData *)pFaultPara;

			if (pParaData->m_strDataTypeID == _T("float")
				|| pParaData->m_strDataTypeID == _T("double")
				|| pParaData->m_strDataTypeID == _T("number"))
			{
				float fDefault = CString_To_double(pParaData->m_strDefaultValue);
				float fValue = CString_To_double(pUiData->m_strValue);

				if (fValue == fDefault)
				{
					pUiParas->Delete(pUiData);
				}
			}
			else if (pParaData->m_strDataTypeID == _T("long"))
			{
				long nDefault = CString_To_long(pParaData->m_strDefaultValue);
				long nValue = CString_To_long(pUiData->m_strValue);

				if (nValue == nDefault)
				{
					pUiParas->Delete(pUiData);
				}
			}
			else if (pParaData->m_strDefaultValue == pUiData->m_strValue)
			{
				pUiParas->Delete(pUiData);
			}
		}
	}
}

//如果是状态序列，根据状态数，删除多余的状态的参数
void CGbItemsGenTool::SortTestMacroUiParas_ByStateCount(CDataGroup *pUiParas)
{
	if (pUiParas == NULL)
	{
		return;
	}

	CDvmData *pStateCount = (CDvmData *)pUiParas->FindByID(_T("StateCount"));

	if (pStateCount == NULL)
	{
		return;
	}

	long nStateCount = CString_To_long(pStateCount->m_strValue);
	long nStateNum = -1;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	POS pos = pUiParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pUiParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		CDataGroup *pGrp = (CDataGroup *)pObj;
		long nPos = pGrp->m_strID.Find(_T("state"));

		if (nPos != 0)
		{
			continue;
		}

		CString strID = pGrp->m_strID.Mid(nPos + 5);
		nStateNum = CString_To_long(strID) + 1; //状态序列参数的定义，从0开始：state0、state1、……

		if (nStateNum > nStateCount)
		{
			pUiParas->Delete(pGrp);
			continue;
		}

		CDvmData *pSelect = (CDvmData *)pGrp->FindByID(_T("bSelect"));

		if (pSelect != NULL)
		{
			if (CString_To_long(pSelect->m_strValue) == 0)
			{
				pUiParas->Delete(pGrp);
			}
		}
	}
}

//如果是状态序列，根据结果评估是否启用，删除多余的评估的参数
void CGbItemsGenTool::SortTestMacroUiParas_RsltEvalute(CDataGroup *pUiParas)
{
	//此处不能根据是否启用删除多余的评估参数
	//因为上位机判断界面参数改变时，需要全部的评估参数
	return;

	if (pUiParas == NULL)
	{
		return;
	}

	CDataGroup *pRlstEvalueGrp = (CDataGroup *)pUiParas->FindByID(_T("rslt_evaluation"));

	if (pRlstEvalueGrp == NULL)
	{
		return;
	}

	CDataGroup *pRsltEvasluteChild = NULL;
	POS pos = pRlstEvalueGrp->GetHeadPosition();
	CDvmData *pUseError = NULL;
	
	while (pos != NULL)
	{
		pRsltEvasluteChild = (CDataGroup *)pRlstEvalueGrp->GetNext(pos);
		pUseError = (CDvmData *)pRsltEvasluteChild->FindByID(_T("UseError"));

		if (pUseError == NULL)
		{
			continue;
		}

		if (CString_To_long(pUseError->m_strValue) == 0)
		{
			pRlstEvalueGrp->Delete(pRsltEvasluteChild);
		}
	}
}

//strDvmFile和strEngineProgID，都是GenerateTemplate指令传过来的
void CGbItemsGenTool::GenGuideBook(const CString &strMacroName, const CString &strMacroID, const CString &strDvmFile, const CString &strEngineProgID, const CString &strPpxmlFile)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++begin GenGuideBook"));
	CString strID = strMacroID;

	if (strID == STT_CMD_ATS_MACRO_ID_GradientTest)
	{
		//返回给上位机的模板中，不需要进行测试功能ID的替换，而是给测试底层服务发送的指令中需要进行ID替换
		//因此注释此处  saholei 20220416
		//GenGbItem_MacroID_Revise(strID, m_pUIParasGroup);
	}

	if (m_pUIParasGroup == NULL && IsUI_Web())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("界面参数为空，生成模板失败"));
		return;
	}

	if (m_pGuideBook == NULL)
	{
		m_pGuideBook = new CGuideBook();
	}

    m_pGuideBook->m_strGuideBookFileType = _T("gbxml");
    m_pGuideBook->m_strTestMacroFileID = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
	m_pGuideBook->DeleteAll();
	m_pGuideBook->InitAfterRead();
	CDevice *pDevice = new CDevice();
	pDevice->m_strID = _T("Device");
	pDevice->m_strName = g_sLangTxt_GbDevice/*_T("设备")*/;
	m_pGuideBook->AddNewChild(pDevice);
	pDevice->InitAfterRead();
	m_pGuideBook->ImportExpandDatas(pDevice);

	if (/*strDvmFile != m_strDvmFile && */!strDvmFile.IsEmpty())
	{
		Init_DvmDevice(strDvmFile);
	}

	if (!strEngineProgID.IsEmpty())
	{
#ifndef _not_use_autotest_
		CTCtrlCntrWorkSpace::s_SetPpEngineProgID(strEngineProgID);
#endif

		m_pGuideBook->m_strPpEngineProgID = strEngineProgID;
	}

	if (!strPpxmlFile.IsEmpty())
	{
#ifndef _not_use_autotest_
		CTCtrlCntrWorkSpace::s_SetPpTemplateFile(strPpxmlFile);
#endif

		m_pGuideBook->m_strPpTemplateFile = strPpxmlFile;
	}

	CGbItemBase *pParentItem = pDevice;

	if (/*IsUI_Original()*/m_pGbItemsGen == NULL)
	{
		//为保证模板结构的统一，在Device下，创建一个统一管理的Items节点，此处新建一个CItems对象
	 	CItems *pItems = new CItems;
	 	pItems->m_strID = strID;
	 	pItems->m_strName = strMacroName;
		pItems->m_strType = GBITEMS_NODETYPE_ROOTNODE;
	 	pItems->InitAfterRead();
	 	pParentItem->AddNewChild(pItems);
		pParentItem = pItems;
	}

	GenGuideBook_Items(strMacroName, strID, pParentItem, TRUE, TRUE);
	SetBinaryFileName();
	//for debug
#ifdef _DEBUG
	CString strFile;
	strFile = _P_GetTemplatePath();
	strFile += _T("new_template.gbxml");
	m_pGuideBook->SaveXMLFile(strFile);
#endif
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------------end GenGuideBook"));
}

BOOL CGbItemsGenTool::GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, const CString &strParentItemPath
										 , const CString &strItemsName, const CString &strItemsID, long nRepeatTimes
										 , long nRptTitle, long nTitleLevel)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++begin GenGuideBook_Items"));
	m_bGenerateItemsOnly_CmdWzd = FALSE;
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	m_pGbItemBase = NULL;
	CGbItemBase *pParent = (CGbItemBase* )Gb_GetItem(m_pGuideBook, strParentItemPath);

	if (pParent == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("生成测试项目失败，父项目没找到【%s】"), strParentItemPath.GetString());
		return FALSE;
	}

	CString strID,strName;
	if (strItemsID.GetLength() > 0)
	{
		strName = strItemsName;
		strID = strItemsID;
	}
	else
	{
		strName = strMacroName;
		strID = strMacroID;
	}
	//GenerateItems，可能是Windows的单机软件发过来的保存参数的指令，因此需要先删除原先的，并按照最新的参数重新生成
	//strID对应的是rootnode的CItems节点。此处不能直接从pParent中删除strID对应的项目，否则会导致项目顺序不对应
	//pParent->DeleteByID(strID);
	CItems *pItems = (CItems *)pParent->FindByID(strID);

	if (pItems != NULL)
	{
		//此处处理待讨论，这样处理会删除报告
		pItems->DeleteAll();
		pItems->m_pReports = NULL;
		pItems->m_pReportsBack = NULL;
		pItems->SetTestMacroUiParas(NULL);
		pItems->SetTestMacroCharParas(NULL);
		pItems->m_pRptMap = NULL;

		//对于删除后重新生成的，需要重新InitGuideBook，否则ItemContainer中的数据是不对的
		//m_pTestControl->m_nCurrTestItemIndex = 0;
		m_pGuideBook->m_nIndex = 0;
	}
	else
	{	
		pItems = new CItems;

		if (NeedSetRootNode(strMacroID))
		{
			pItems->m_strType = GBITEMS_NODETYPE_ROOTNODE;
		}
		
		pItems->m_strID = strID;
		pItems->m_strName = strName;
		pParent->AddNewChild(pItems);
	}
	
	pItems->m_nTestTimes = nRepeatTimes;
	pItems->m_nRptTitle = nRptTitle;
	pItems->m_nTitleLevel = nTitleLevel;
	pItems->InitAfterRead();
	m_pGbItemBase = pItems;

	pParent = pItems;
	GenGuideBook_Items(strMacroName, strMacroID, pParent, FALSE, FALSE);

	//处理遥测项目
	if (pItems->IsTypeRootNode())
	{
		//该属性记录功能ID
		if (IsAinItems(pItems->m_strStxmlFile))
		{
			CExBaseList oListCommCmds;
			pItems->GetChildItem(GBCLASSID_COMMCMD, &oListCommCmds, TRUE);
			POS pos = oListCommCmds.GetHeadPosition();
			CString strItemPath;

			while (pos != NULL)
			{
				CCommCmd *pCommCmd = (CCommCmd *)oListCommCmds.GetNext(pos);
				strItemPath = pCommCmd->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

				//先将刚生成的项目，备份到m_oListAinCommCmds列表
				m_oListAinCommCmds.DeleteByID(strItemPath);  //ID记录路径
				CCommCmd *pNew = (CCommCmd *)pCommCmd->CloneEx(TRUE, TRUE);
				pNew->m_strID = strItemPath;
				m_oListAinCommCmds.AddTail(pNew);

				//如果已经有进行过配置，则直接进行参数映射
				if (m_pAinDataMapCfg != NULL)
				{
					CCmd *pCmd = pCommCmd->GetCmd();
					CItemRsltExprRun* pRsltExpr = pCommCmd->GetRsltExpr();

					CString strDsPath;
					GenerateItemsOnly_AinDataMap(pRsltExpr, m_pAinDataMapCfg, strDsPath);

					if (strDsPath.GetLength() > 0)
					{
						pCmd->m_strDatasetPath = strDsPath;
					}
				}
			}

			oListCommCmds.RemoveAll();
		}
	}
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("-----------------end GenGuideBook_Items"));
	return TRUE;
}

/*
//bGenerateRootItems：是否生成根的CItems节点
//通过GenerateTemplate指令，需要生成根的CItems节点，bGenerateRootItems = TRUE
//通过GenerateItems指令，不需要生成根的CItems节点，bGenerateRootItems = FALSE

//bGenerateBFT：是否生成测试前准备项目：硬件通道配置、IEC配置、系统参数配置
//通过GenerateTemplate指令，需要生成测试前准备项目，bGenerateBFT = TRUE
//通过GenerateItems指令，不需要生成测试前准备项目，bGenerateBFT = FALSE
*/
void CGbItemsGenTool::GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem, BOOL bGenerateRootItems, BOOL bGenerateBFT)
{
	if (/*IsUI_Original()*/m_pGbItemsGen == NULL)
	{
		CItems *pItems = (CItems *)pParentItem;
		pItems->m_strStxmlFile = strMacroID;
		GenGbItemBase_Original(strMacroName, strMacroID, pParentItem, bGenerateBFT);
		return;
	}

// 	if (m_pGbItemsGen == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("测试模板生成失败，找不到模板生成规则文件!"));
// 		return;
// 	}

	m_pGbItemsGen->InitParasMapByUIParas(&m_oUiParas_SortIdPath/*m_pUIParasGroup*/);
	CItems *pMacroItemsRoot = NULL;

	if (bGenerateRootItems == TRUE)
	{
		//生成整个功能模板的根节点
		CItems *pNewItems = new CItems();
		pParentItem->AddNewChild(pNewItems);
		pNewItems->InitAfterRead();
		pNewItems->m_strName = m_pGbItemsGen->m_strName;
		pNewItems->m_strID = m_pGbItemsGen->m_strID;  //？？？？ 作为复杂模板生成规则，ID和Name有外部系统传入
		pParentItem = pNewItems;
		pNewItems->SetTypeRootNode();
	}

	//对于网页功能，一个ROOT-TYPE的CItems节点，会生成多个电气量项目，作为其子节点
	//因此，将界面参数m_pDataGroup，存入items的子节点：test-macro-ui-paras中
	//<test-macro-ui-paras><![CDATA[      ]]></test-macro-ui-paras>
	CTestMacroUiParas *pUiParas = ((CItems *)pParentItem)->CreateTestMacroUiParas();
	CString strParas;
	GetXml_TestMacroUiParas(strParas);
	//pUiParas->SetParaText(strParas);
	pUiParas->m_strParaText = strParas;

	//对于网页功能，如果含特性曲线，则需要将特性曲线存入NOOT-TYPE的items节点
	CString strCharParas;
	GetXml_TestMacroCharParas(strCharParas);

	if (strCharParas.GetLength() > 0)
	{
		CTestMacroCharParas *pCharParas = ((CItems *)pParentItem)->CreateTestMacroCharParas();
		pCharParas->m_strParaText = strCharParas;
	}

	CItems *pItems = (CItems *)pParentItem;
	pItems->m_strStxmlFile = strMacroID;
	
	if (bGenerateBFT)
	{
		//测试前准备放在根目录
		CItems *pBeforeTestItems = GenGbItemsBase_BaseItems(pItems, strMacroName, strMacroID);
		//通讯前准备，放在测试前准备
		GenGbCommCmd_Before(pBeforeTestItems);
	}
	else
	{
		//通讯前准备，放在根目录
		GenGbCommCmd_Before(pItems);
	}

	POS pos = m_pGbItemsGen->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = m_pGbItemsGen->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CMACROITEMSGEN)
		{
			CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pObj;

			if (pMacroItemsGen->m_nNewItems == 1)
			{
				pMacroItemsRoot = GenGbItemsBase_Root(pMacroItemsGen, strMacroName, strMacroID);
				pParentItem->AddNewChild(pMacroItemsRoot);
			}
			else
			{
				pMacroItemsRoot = (CItems *)pParentItem;
			}

			POS pos2 = pMacroItemsGen->GetHeadPosition();

			while (pos2 != NULL)
			{
				CExBaseObject *pObj2 = pMacroItemsGen->GetNext(pos2);

				if (pObj2->GetClassID() != GBITEMSGENMNGRCLASSID_CITEMSGENINST)
				{
					continue;
				}

				CItemsGenInst *pInst = (CItemsGenInst *)pObj2;

				if (!pInst->IsEnable(&m_oUiParas_SortIdPath/*m_pUIParasGroup*/))
				{
					continue;
				}

				if (pInst->IsClassMode_Define())
				{
					GenGbItemBase_Define(pMacroItemsRoot, pInst);
				}
				else if (pInst->IsClassMode_Class())
				{
					GenGbItemBase_Class(pMacroItemsRoot, pInst);
				}
			}

			if (Gb_GetChildItemsCount(pMacroItemsRoot) == 0)
			{
				if (pMacroItemsRoot != pParentItem)
				{
					CExBaseList *pParent = (CExBaseList *)pMacroItemsRoot->GetParent();
					pParent->Delete(pMacroItemsRoot);
				}
			}

			continue;
		}

		if (nClassID == GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN)
		{
			CMacroSelfDefGen *pMacroSelfDef = (CMacroSelfDefGen *)pObj;
			CItems *pItems = new CItems;
			pItems->m_strName = pMacroSelfDef->m_strName;
			pItems->m_strID = pMacroSelfDef->m_strID;
			pParentItem->AddNewChild(pItems);
			pItems->InitAfterRead();
			m_pItems_SelfDef = pItems;
		}
	}

	//通讯后恢复，放在根目录
	GenGbCommCmd_After(pItems);
}

void CGbItemsGenTool::GenGuideBook_BeforeTest(CGbItemBase *pBeforeTestItems)
{
	if (m_nGenMode >= TEMPLATE_GEN_MODE_STARTTEST)
	{
		GenGuideBook_BeforeTest_StartTestMode(pBeforeTestItems);
		return;
	}

	CMacroTest *pMacroTest = GenGuideBook_CreateMacroTest(g_sLangTxt_ChMapsConfig/*_T("硬件通道映射")*/, STT_CMD_TYPE_ADJUST_ChMapsConfig);
	pBeforeTestItems->AddNewChild(pMacroTest);
	pMacroTest->InitMacroID();
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	pMacroTestPara->SetMacroID(STT_CMD_TYPE_ADJUST_ChMapsConfig);
	//具体参数通过SetItemParas确定，先弄一个空的参数
	CTestMacroUiParas *pUIParas = pMacroTest->CreateTestMacroUiParas();

	if (m_pChMaps != NULL)
	{
		CString strChMaps;
		strChMaps = m_pChMaps->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
        //pUIParas->SetParaText(strChMaps);
        pUIParas->m_strParaText = strChMaps;
	}

	pMacroTest = GenGuideBook_CreateMacroTest(g_sLangTxt_SysParaCfg/*_T("系统参数配置")*/, STT_CMD_TYPE_SYSTEM_SystemConfig);
	pBeforeTestItems->AddNewChild(pMacroTest);
	pMacroTest->InitMacroID();
	pMacroTestPara = pMacroTest->GetMacroTestPara();
	pMacroTestPara->SetMacroID(STT_CMD_TYPE_SYSTEM_SystemConfig);
	//具体参数通过SetItemParas确定，先弄一个空的参数
	pUIParas = pMacroTest->CreateTestMacroUiParas();

	if (m_pSysParameter != NULL)
	{
		CString strSysParameter;
		strSysParameter = m_pSysParameter->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
        //pUIParas->SetParaText(strSysParameter);
        pUIParas->m_strParaText = strSysParameter;
	}

	//此处先不管测试仪是否有数字部分，固定放一个IEC配置功能
	//在系统参数配置的SetItemParas中，根据HasDigital参数，判断是否有数字量
	//若没有数字量，则将IEC配置的项目的enable，show属性置为0。且在返回上位机的模板中，不返回该项目
	if (m_bHasDigital)
	{
		pMacroTest = GenGuideBook_CreateMacroTest(g_sLangTxt_Iec61850Cfg/*_T("IEC61850配置")*/, STT_CMD_TYPE_SYSTEM_IECConfig);
		pBeforeTestItems->AddNewChild(pMacroTest);
		pMacroTest->InitMacroID();
		pMacroTestPara = pMacroTest->GetMacroTestPara();
		pMacroTestPara->SetMacroID(_T("Iec61850Config"));
		//具体参数通过SetItemParas确定，先弄一个空的参数
		pUIParas = pMacroTest->CreateTestMacroUiParas();

		if (m_pIecDatasMngr != NULL)
		{
			CString strIecDatas;
			strIecDatas = m_pIecDatasMngr->GetXml(CCfgDataMngrXmlRWKeys::g_pXmlKeys);
            //pUIParas->SetParaText(strIecDatas);
            pUIParas->m_strParaText = strIecDatas;
		}
	}
}

void CGbItemsGenTool::GenGuideBook_BeforeTest(CGbItemBase * pParentItem, const CString &strUI)
{
	if (m_pGuideBook == NULL)
	{
		return;
	}

	CItems *pItems_UI = (CItems *)pParentItem->FindByID(strUI);

	if (pItems_UI == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("生成的模板中，找不到测试分类项目【%s】..."), strUI.GetString());
		return;
	}

	CItems *pItems = (CItems *)pItems_UI->FindByID(STT_ITEMS_ID_BEFORETEST);

	if (pItems == NULL)
	{
		pItems = new CItems;
		pItems->m_strName = g_sLangTxt_BeforeTest/*_T("测试前准备")*/;
		pItems->m_strID = STT_ITEMS_ID_BEFORETEST;
		pItems_UI->AddNewChild(pItems);
		pItems->InitAfterRead();
		pItems_UI->BringToHead(pItems);
	}

	GenGuideBook_BeforeTest(pItems);
}

/*  模板结构举例如下：ZeroTest
<device name="STT_ATS" id="STT_ATS">
	<items name="零序保护定值校验" id="ZeroTest" tkid="65535" select="1">
		<items name="_BeforeTest_" id="_BeforeTest_" tkid="65535" select="1">
			<macrotest name="硬件配置" id="HdConfig" tkid="65535" select="1"/>
			<macrotest name="IEC61850配置" id="IEC61850Config" tkid="65535" select="1"/>
			<macrotest name="系统配置" id="SystemConfig" tkid="65535" select="1"/>
		</items>
		<items name="零序Ⅰ段" id="Zero1" tkid="65535" select="1">
			<macrotest name="A相1.05倍" id="A105" tkid="65535" select="1"/>
			<macrotest name="A相0.95倍" id="A095" tkid="65535" select="1"/>
			<macrotest name="A相1.20倍" id="A120" tkid="65535" select="1"/>
			<macrotest name="B相1.05倍" id="B105" tkid="65535" select="1"/>
			<macrotest name="B相0.95倍" id="B105" tkid="65535" select="1"/>
			<macrotest name="B相1.20倍" id="B120" tkid="65535" select="1"/>
			<macrotest name="C相1.05倍" id="C105" tkid="65535" select="1"/>
			<macrotest name="C相0.95倍" id="C095" tkid="65535" select="1"/>
			<macrotest name="C相1.20倍" id="C120" tkid="65535" select="1"/>
		</items>
		<items name="零序Ⅱ段" id="Zero2" tkid="65535" select="1">
			<macrotest name="A相1.05倍" id="A105" tkid="65535" select="1"/>
			<macrotest name="A相0.95倍" id="A095" tkid="65535" select="1"/>
			<macrotest name="A相1.20倍" id="A120" tkid="65535" select="1"/>
			<macrotest name="B相1.05倍" id="B105" tkid="65535" select="1"/>
			<macrotest name="B相0.95倍" id="B105" tkid="65535" select="1"/>
			<macrotest name="B相1.20倍" id="B120" tkid="65535" select="1"/>
			<macrotest name="C相1.05倍" id="C105" tkid="65535" select="1"/>
			<macrotest name="C相0.95倍" id="C095" tkid="65535" select="1"/>
			<macrotest name="C相1.20倍" id="C120" tkid="65535" select="1"/>
		</items>
		<items name="零序Ⅲ段" id="Zero3" tkid="65535" select="1">
			<macrotest name="A相1.05倍" id="A105" tkid="65535" select="1"/>
			<macrotest name="A相0.95倍" id="A095" tkid="65535" select="1"/>
			<macrotest name="A相1.20倍" id="A120" tkid="65535" select="1"/>
			<macrotest name="B相1.05倍" id="B105" tkid="65535" select="1"/>
			<macrotest name="B相0.95倍" id="B105" tkid="65535" select="1"/>
			<macrotest name="B相1.20倍" id="B120" tkid="65535" select="1"/>
			<macrotest name="C相1.05倍" id="C105" tkid="65535" select="1"/>
			<macrotest name="C相0.95倍" id="C095" tkid="65535" select="1"/>
			<macrotest name="C相1.20倍" id="C120" tkid="65535" select="1"/>
		</items>
	</items>
</device>
*/
//根据UI的ID，从基础模板中读取测试准备项目
void CGbItemsGenTool::GenGuideBook_BeforeTest_FromFile(const CString &strUI)
{
	CString strFile;
	GetBaseGbxmlFile(strUI, strFile);

	if (!IsFileExist(strFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试功能界面【%s】，对应的默认模板文件【%s】不存在！")
                                   , strUI.GetString(), strFile.GetString());
		return;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();
	CItems *pItems_UI = (CItems *)pDevice->FindByID(strUI);

	if (pItems_UI == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("生成的模板中，找不到测试分类项目【%s】..."), strUI.GetString());
		return;
	}

	//将系统参数配置、硬件通道配置、IEC61850配置项目放到该“测试前准备”项目分类中
	CItems *pBeforeTest = (CItems *)pItems_UI->FindByID(STT_ITEMS_ID_BEFORETEST);

	if (pBeforeTest == NULL)
	{
		pBeforeTest = new CItems;
		pBeforeTest->m_strName = g_sLangTxt_BeforeTest/*_T("测试前准备")*/;
		pBeforeTest->m_strID = STT_ITEMS_ID_BEFORETEST;
		pItems_UI->AddNewChild(pBeforeTest);
		pBeforeTest->InitAfterRead();
		pItems_UI->BringToHead(pBeforeTest);
	}

	GenguideBook_BeforeTest_CopyFormFile(pBeforeTest, strFile, strUI);
}

void CGbItemsGenTool::GenguideBook_BeforeTest_CopyFormFile(CItems *pParentItems, const CString &strFile, const CString &strUI)
{
	CGuideBook oGuideBookBase;
	oGuideBookBase.OpenXMLFile(strFile);

	CDevice *pDevice = oGuideBookBase.GetDevice();
	CItems *pItems_UI = (CItems *)pDevice->FindByID(strUI);

	if (pItems_UI == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("模板【%s】中，找不到ID为【%s】的测试分类项目"), strUI.GetString());
		return;
	}

	//将系统参数配置、硬件通道配置、IEC61850配置项目放到该“测试前准备”项目分类中
	CItems *pBeforeTest = (CItems *)pItems_UI->FindByID(STT_ITEMS_ID_BEFORETEST);

	if (pBeforeTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("模板【%s】中，找不到ID为【%s】的测试分类项目"), STT_ITEMS_ID_BEFORETEST);
		return;
	}

	POS pos = pBeforeTest->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pBeforeTest->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_MACROTEST)
		{
			continue;
		}

		CMacroTest *pMacroTest = (CMacroTest *)pObj;
		pParentItems->AddNewChild(pMacroTest);
		pBeforeTest->Remove(pMacroTest);
	}
}

void CGbItemsGenTool::GenGuideBook_BeforeTest_StartTestMode(CGbItemBase *pBeforeTestItems)
{
	CItems *pItems = (CItems *)m_oBeforeTestBk.GetHead();  //此处可能会有多个，暂时只取第一个。脱机版本的程序中，此处应当只有一个对象

	if (pItems == NULL)
	{
		return;
	}

	pBeforeTestItems->AppendEx(*pItems);
	m_oBeforeTestBk.Remove(pItems);
}

void CGbItemsGenTool::GetBaseGbxmlFile(const CString &strUI, CString &strPath)
{
	strPath = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strPath += STT_MACROTEST_UI_REALPATH_TEMPLATE;
    strPath += _T("/");
	strPath += strUI;
	strPath += _T(".gbxml");
}

CMacroTest* CGbItemsGenTool::GenGuideBook_CreateMacroTest(const CString &strName, const CString &strID)
{
	CMacroTest *pMacroTest = new CMacroTest();
	pMacroTest->InitAfterRead();
	pMacroTest->m_strName = strName;
	pMacroTest->m_strID = strID;
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	//pMacroTest->InitMacroID();
	pMacroTestPara->SetMacroID(strID);
	pMacroTestPara->InitAfterRead();

	return pMacroTest;
}

//原生态模式下，生成的模板固定添加如下几个测试项目：
//硬件配置、系统参数配置、IEC61850配置和测试点（手动、状态序列、谐波、递变或者故障回放）
void CGbItemsGenTool::GenGbItemBase_Original(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem, BOOL bGenerateBFT)
{
	//对于硬件配置、系统参数配置、IEC61850项目的生成，放到智能生成服务中，该生成类只生成测试点相关的项目
// 	CItems *pItems = new CItems;
// 	pItems->m_strID = strMacroID;
// 	pItems->m_strName = strMacroName;
// 	pItems->InitAfterRead();
// 	pParentItem->AddNewChild(pItems);
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++begin GenGbItemBase_Original"));
	if (bGenerateBFT)
	{
		//固定添加一个测试前准备，供生成服务添加硬件配置、系统参数、测试仪IEC61850配置项目
		CItems *pBeforeTest = new CItems;
		pBeforeTest->m_strName = g_sLangTxt_BeforeTest/* _T("测试前准备")*/;
		pBeforeTest->m_strID = STT_ITEMS_ID_BEFORETEST;
		pParentItem->AddNewChild(pBeforeTest);
		pBeforeTest->InitAfterRead();
		GenGuideBook_BeforeTest(pBeforeTest);
	
		//通讯前准备，放在测试前准备
		GenGbCommCmd_Before(pBeforeTest);
	}
	else
	{
		//通讯前准备，放在根目录
		GenGbCommCmd_Before(pParentItem);
	}

	CMacroTest *pMacroTest = GenGuideBook_CreateMacroTest(strMacroName, strMacroID);
	pParentItem->AddNewChild(pMacroTest);

	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	pMacroTestPara->SetMacroID(strMacroID);
	pMacroTestPara->InitAfterRead();

    //先处理结果判断，因为处理参数时，会删除 =默认值的参数
    GenGbItemBase_MacroTest_RsltExpr(pMacroTest);

	//对于原生态功能，pParentItem为ROOT-TYPE的CItems节点，只生成一个电气量项目pMacroTest，作为起子项目
	//因此，将m_pDataGroup中的数据，存放到pMacroTest的子节点中
	//原生态功能，只需要将参数存到pUiParas中，而不需要存到pMacroTestPara中。执行测试时。优先获取pUiParas中的参数
	//  <test-macro-ui-paras><![CDATA[      ]]></test-macro-ui-paras>
	CTestMacroUiParas *pUiParas = pMacroTest->CreateTestMacroUiParas();
	CString strParas;
	GetXml_TestMacroUiParas(strParas, strMacroID);
    //pUiParas->SetParaText(strParas);
    pUiParas->m_strParaText = strParas;

	GenGbItemBase_Define_MacroTest_InitReport(pMacroTest);

// 	if (IsTestClass_Ain())
// 	{
// 		//精度测试，电气量项目固定增加读遥测通讯命令
// 		GenGbCommCmd_ReadAin(pMacroTest);
// 	}

	//通讯后恢复，放在根目录
	GenGbCommCmd_After(pParentItem);
	//调试代码
// 	CDataGroup oGroup;
// 	BSTR bstrText = strParas.AllocSysString();
// 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
// 	BOOL bRet = oGroup.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
// 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
// 	SysFreeString(bstrText);
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------end GenGbItemBase_Original"));
}

void CGbItemsGenTool::GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenInst *pInst)
{
	CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pInst->GetParent();
	CItemsGenDefine *pDefine = pMacroItemsGen->GetItemsGenDefine();
	CItems *pRootItems = (CItems*)pParentItem;
	CItems *pNewItems = NULL;
	long nChildCount = 0;

	if (pDefine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("测试项目实例生成项目失败，找不到项目生成规则对象【Define】"));
		return;
	}

	pDefine->SetCurrentInst(pInst);

	if (pInst->m_nNewItems)
	{
		pNewItems = new CItems;
		pNewItems->InitAfterRead();
		pParentItem->AddNewChild(pNewItems);
		pNewItems->m_strID = pInst->GetNameAdd_ID(m_pUIParasGroup);
		pNewItems->m_strName = pInst->GetNameAdd_Name(m_pUIParasGroup);
		pRootItems = pNewItems;  //此处将父项目进行赋值，后面代码可以不用判断pInst->m_nNewItems
		nChildCount = pNewItems->GetCount();   //InitAfterRead之后，所有子项目的数量：CReportMap、CScriptInit等
	}

	POS pos = pDefine->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	/*
	此处不用再进行参数映射初始化InitParaValueByUIParas(m_pUIParasGroup);了，因为在
	void CGbItemsGenTool::GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem)
	中，已经通过m_pGbItemsGen->InitParasMapByUIParas(m_pUIParasGroup); 进行过参数映射初始化了
	*/
	//此时，Interface下的参数，都已经是实际界面参数值了。此处通过Interface，初始化参数映射，是将界面参数传递给Define下的参数映射，用于电气量项目参数赋值
	m_pCurrInstInterface = pInst->GetInterface();  //2022-3-1 lijunqing
	CItemsGenParasMap *pItemsGenParasMap = pDefine->GetItemsGenParasMap();
	//pItemsGenParasMap->InitParaValueByUIParas(m_pUIParasGroup);
	pItemsGenParasMap->InitParasMapByInterface(m_pCurrInstInterface);
	pItemsGenParasMap->LogParasMapError(PARAMAP_LOG_LEVEL_INTERFACE);

	while (pos != NULL)
	{
		pObj = pDefine->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
		{
			CItemsGenNode *pNode = (CItemsGenNode *)pObj;
			GenGbItemBase_Define(pRootItems, pNode);
		}
		else if(nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCHARITEMLINE)
		{
			CItemsGenCharItemLine *pLine = (CItemsGenCharItemLine *)pObj;

			if (m_pCharacteristics == NULL)
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("缺少特性曲线定义，生成边界测试项目失败！"));
				continue;
			}
				
			//规则：根据曲线ID查找，没有找到，判断是否为“*_#”格式，“#”为数字，如果是，则结合CCharacteristic的index属性进行查找
			CCharacteristic *pCharacteristic = FindCharacterByID(pInst->m_strCharacteristic);

			if (pCharacteristic == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("缺少特性曲线【%s】定义，生成边界测试项目失败！"), pInst->m_strCharacteristic.GetString());
				continue;	
			}

			
			GenGbItemBase_Define(pRootItems, pLine, pCharacteristic, pInst);
		}	
	}

	//处理子项目为空的情况，所有的节点都使能为FALSE
	if (pNewItems != NULL)
	{
		if (pNewItems->GetCount() == nChildCount)
		{
			pParentItem->Delete(pNewItems);
		}
	}
}

//递归调用，一个pNode对应一个测试项目
void CGbItemsGenTool::GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenNode *pNode)
{
	CItemsGenInterface *pInterface = pNode->GetGenInterface();

	if (pInterface == NULL)
	{
		return;
	}

	if (!pNode->IsEnable(pInterface))
	{
		return;
	}

	//此处获取备份的数据接口，用于那些电气量参数，需要保存表达式的。因为备份的没有被实例初始化
	CItemsGenInterface *pInterfaceBK = pNode->GetGenInterface_BK();
	pNode->ResetParasMap();
	//根据界面参数，将当前节点的参数映射初始化为实际值，用于后面生成电气量项目时的参数设置
	pNode->InitParasMapByUIParas(&m_oUiParas_SortIdPath/*m_pUIParasGroup*/);
	pNode->InitParasMapByInterface_Ex(pInterface/*pInterfaceBK*/);
	pNode->LogParasMapError();

	CGbItemBase *pNewParentItem = pParentItem;
	CCommCmd *pNewCommCmd = NULL;
	//目前只考虑这三种情况
	if (pNode->IsNodeType_Items())
	{
		pNewParentItem = GenGbItemBase_Define_Items(pParentItem, pNode);
	}
	else if (pNode->IsNodeType_MacroTest())
	{
		pNewParentItem = GenGbItemBase_Define_MacroTest(pParentItem, pNode);
	}
	else if (pNode->IsNodeType_CommCmd())
	{
		if (m_nLoopTest)  //闭环测试
		{
			//通讯命令不能作为父项目，所以父节点不刷新
			pNewCommCmd = (CCommCmd *)GenGbItemBase_Define_CommCmd(pParentItem, pNode);
		}
	}
	else if (pNode->IsNodeType_None())
	{
		pNewParentItem = pParentItem;
	}

	CItemGenRsltExpr* pRsltExpr = pNode->GetRsltExpr();

	if (pRsltExpr != NULL)
	{
		CExBaseList listParasMap;
		CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pNode->GetAncestor(GBITEMSGENMNGRCLASSID_CMACROITEMSGEN);
		pNode->GetAllParasMap(listParasMap);
		CItemsGenParasMap *pParasMap = pMacroItemsGen->GetItemsGenParasMap();

		if (pParasMap != NULL)
		{
			listParasMap.Append(pParasMap);
		}

		if (pNewCommCmd != NULL && pNode->IsNodeType_CommCmd())
		{
			CItemRsltExprRun *pRsltExprRun = new CItemRsltExprRun;
			pRsltExprRun->InitOwnByRsltExprGen(pRsltExpr);
			InitRsltExpr(pRsltExprRun, pInterface, pRsltExpr, &listParasMap);

			pNewCommCmd->AddNewChild(pRsltExprRun);
			pNewCommCmd->m_pRsltExprRun = pRsltExprRun;

			CReports *pReports = pNewCommCmd->GetReports();
			pNewCommCmd->BringToTail(pReports);
		}
		else
		{
			if (pNode->IsNodeType_CommCmd() && m_nLoopTest == 0)
			{
				//通讯命令节点，且非闭环测试，则不处理结果判断
			}
			else
			{
				if (pNewParentItem != NULL && pNode->IsNodeType_MacroTest())
				{
					CItemRsltExprRun *pRsltExprRun = new CItemRsltExprRun;
					pRsltExprRun->InitOwnByRsltExprGen(pRsltExpr);
					InitRsltExpr(pRsltExprRun, pInterface, pRsltExpr, &listParasMap);

					pNewParentItem->AddNewChild(pRsltExprRun);
					pNewParentItem->m_pRsltExprRun = pRsltExprRun;

					CReports *pReports = pNewParentItem->GetReports();
					pNewParentItem->BringToTail(pReports);
				}
			}
		}

		listParasMap.RemoveAll();
	}

	POS pos = pNode->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pNode->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
		{
			continue;
		}

		CItemsGenNode *pChildNode = (CItemsGenNode *)pObj;
		GenGbItemBase_Define(pNewParentItem, pChildNode);
	}
}

//生成曲线搜索项目
//参数1：父节点项目；参数2：规则文件定义的char-item-line；参数3：从报文中查找的当前实例对应的特性曲线
void CGbItemsGenTool::GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenCharItemLine *pLine, CCharacteristic *pCharacteristic, CItemsGenInst *pInst)
{
	CMacroCharItems *pMacroCharItems = new CMacroCharItems;
	pParentItem->AddNewChild(pMacroCharItems);
	pMacroCharItems->m_strID = pInst->GetNameAdd_ID(m_pUIParasGroup);     //对于特性曲线的部分，实例的Inst一定要有name-add节点
	pMacroCharItems->m_strName = pInst->GetNameAdd_Name(m_pUIParasGroup);
	CItems *pItems = (CItems *)pParentItem;
	pItems->m_strCharacteristicID = pCharacteristic->m_strID;

// 	if (pLine->m_strName.GetLength() > 0)
// 	{
// 		pMacroCharItems->m_strName = pLine->m_strName;
// 	}
// 	else
// 	{
// 		pMacroCharItems->m_strName = _T("边界测试");
// 	}
// 
// 	if (pLine->m_strID.GetLength() > 0)
// 	{
// 		pMacroCharItems->m_strID = pLine->m_strID;
// 	}
// 	else
// 	{
// 		pMacroCharItems->m_strID = _T("MacroCharTest");
// 	}

	pMacroCharItems->InitAfterRead();

	//处理参数绑定部分
	CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pLine->GetAncestor(GBITEMSGENMNGRCLASSID_CMACROITEMSGEN);
	CMacroTestPara *pMacroTestPara = pMacroCharItems->m_pPara;
	pMacroTestPara->SetMacroID(pMacroItemsGen->m_strMacroID);
	pMacroTestPara->InitAfterRead();
	CItemsGenBase *pItemsGenDefine = (CItemsGenBase*)pLine->GetParent();
	CItemsGenParasMap *pMap = pItemsGenDefine->GetItemsGenParasMap(); 
	CExBaseList oParaMaps;
	oParaMaps.Append(pMap);
	pMap = pMacroItemsGen->GetItemsGenParasMap();
	oParaMaps.Append(pMap);

	POS pos = oParaMaps.GetHeadPosition();
	CMacroTestParaDatas *pFaultParas = pMacroTestPara->GetFaultParaDatas();

	while (pos != NULL)
	{
		CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)oParaMaps.GetNext(pos);

		//映射失败的参数，不作为电气量项目的参数
		if (!pDataMap->m_nIsMapSucc)
		{
			continue;
		}

		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pDataMap->m_strID);
		p->m_strExpression = pDataMap->m_strValue;
	}

	oParaMaps.RemoveAll();

	//处理参数设置
	CMacroCharItemLineDef *pItemLine = pMacroCharItems->m_pItemLineDef;
	GenGbItem_CharItemLine(pItemLine, pLine);

	//处理曲线设置部分
	CCharacteristic *pCharTemplate = pMacroCharItems->m_pCharTemplate;

	if (pCharTemplate == NULL)
	{
		pCharTemplate = new CCharacteristic;
		pMacroCharItems->AddNewChild(pCharTemplate);
		pMacroCharItems->m_pCharTemplate = pCharTemplate;
	}

	pCharTemplate->DeleteAll();
	pCharacteristic->CopyOwn(pCharTemplate);
	pCharTemplate->AppendCloneEx2(*pCharacteristic);
	pCharTemplate->InitAfterRead();

	//根据曲线，生成对应的CMacroTest项目
	pMacroCharItems->InitMacroTestItems();

	//生成的电气量项目，ID要是test1，test2，……，testn？
	pMacroCharItems->InitMacroTestIDByIndex();
	GenGbItemBase_Define_MacroTest_InitReport(pMacroCharItems);
	CItemsGenDefine *pDefine = (CItemsGenDefine *)pLine->GetParent();
	CExBaseList *pInterface = pDefine->GetItemsGenInterface();
	CItemGenRsltExpr *pRsltExprGen = pDefine->GetItemsGenRsltExpr();
	GenGbItemBase_MacroTest_RsltExpr(pMacroCharItems, pRsltExprGen, pInterface);

	//处理完结果判断后，将报告放到项目的Tail
	CExBaseList listMacroTest;
	pMacroCharItems->GetAllMacroTestItemsEx(&listMacroTest);

	pos = listMacroTest.GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)listMacroTest.GetNext(pos);
		CReports *pReports = pMacroTest->GetReports();
		pMacroTest->BringToTail(pReports);
	}

	listMacroTest.RemoveAll();
}

CItems* CGbItemsGenTool::GenGbItemsBase_Root(CMacroItemsGen *pMacroItemsGen, const CString &strName, const CString &strID)
{
	//添加一个固定的项目分类，将当前规则文件中所有的项目，都作为该项目分类的子项目--------------
	CItems *pItems = new CItems;

	if (pMacroItemsGen->m_strID.GetLength() == 0)
	{
		pItems->m_strName = strName;
		pItems->m_strID = strID;
	}
	else
	{
		pItems->m_strName = pMacroItemsGen->m_strName;
		pItems->m_strID = pMacroItemsGen->m_strID;
	}

	pItems->InitAfterRead();
	return pItems;
}

//新建一个固定的测试前准备分类项目，并添加测试前准备项目
CItems* CGbItemsGenTool::GenGbItemsBase_BaseItems(CItems *pRoot, const CString &strName, const CString &strID)
{	
	if (pRoot == NULL)
	{
		return NULL;
	}

	//固定添加一个测试前准备，供生成服务添加硬件配置、系统参数、测试仪IEC61850配置项目
	CItems *pBeforeTest = new CItems;
	pBeforeTest->m_strName = g_sLangTxt_BeforeTest/*_T("测试前准备")*/;
	pBeforeTest->m_strID = STT_ITEMS_ID_BEFORETEST;
	pRoot->AddNewChild(pBeforeTest);
	pBeforeTest->InitAfterRead();

	GenGuideBook_BeforeTest(pBeforeTest);
	return pBeforeTest;
}

CGbItemBase* CGbItemsGenTool::GenGbItemBase_Define_Items(CGbItemBase *pParentItem, CItemsGenNode *pNode)
{
	CItems *pItems = new CItems;
	pItems->InitAfterRead();
	pItems->m_strName = pNode->GetNameAdd_Name(pNode->GetItemsGenParaMap(), m_pUIParasGroup);
	pItems->m_strID = pNode->GetNameAdd_ID(pNode->GetItemsGenParaMap(), m_pUIParasGroup);
	pParentItem->AddNewChild(pItems);

	return pItems;
}

CGbItemBase* CGbItemsGenTool::GenGbItemBase_Define_MacroTest(CGbItemBase *pParentItem, CItemsGenNode *pNode)
{
	CString strName = pNode->GetNameAdd_Name(pNode->GetItemsGenParaMap(), m_pUIParasGroup);
	CString strID = pNode->GetNameAdd_ID(pNode->GetItemsGenParaMap(), m_pUIParasGroup);
	ResetMacroNameId(pNode, strName, strID);

	CMacroTest *pMacroTest = GenGuideBook_CreateMacroTest(strName, strID);
	pParentItem->AddNewChild(pMacroTest, TRUE);
	pMacroTest->InitMacroID();

	//处理电气量的重复测试
	//最开始的设计是放到node下的参数映射
	//CItemsGenParasMap *pItemsGenParaMap = pNode->GetItemsGenParaMap();
	//CItemsGenDataMap *pData = (CItemsGenDataMap *)pItemsGenParaMap->FindByID(STT_CMD_PARA_RepeatTimes);

	//后面统一放到interface下
	CItemsGenInterface *pInterface = pNode->GetGenInterface();
	CItemsGenData *pData = (CItemsGenData *)pInterface->FindByID(STT_CMD_PARA_RepeatTimes);

	if (pData != NULL)
	{
		if (!pData->m_strValue.IsEmpty())
		{
			pMacroTest->m_nRepeatTimes = CString_To_long(pData->m_strValue);
		}

		if (pMacroTest->m_nRepeatTimes <= 0)
		{
			pMacroTest->m_nRepeatTimes = 1;
		}

		//pMacroTest->m_nRepeatTimes = 2; //用于调试
	}

	pData = (CItemsGenData *)pInterface->FindByID(STT_CMD_PARA_RptCalMode);

	if (pData != NULL)
	{
		long nCalMode = CString_To_long(pData->m_strValue);

		switch (nCalMode)
		{
		case MACROTEST_RPTCALMODE_AVERAGE:
			pMacroTest->m_strReportMode = g_strCalMode_Average;
			break;
		case MACROTEST_RPTCALMODE_MAX:
			pMacroTest->m_strReportMode = g_strCalMode_Max;
			break;
		case MACROTEST_RPTCALMODE_MIN:
			pMacroTest->m_strReportMode = g_strCalMode_Min;
			break;
		default:
			pMacroTest->m_strReportMode = g_strCalMode_Average;
			break;
		}
	}

	//设置电气量项目的参数和功能ID
	GenGbItemBase_Define_MacroTest_InitMacroPara(pMacroTest, pNode);
	CReports *pReports = pMacroTest->GetReports();
	pMacroTest->BringToTail(pReports);

// 	if (IsTestClass_Ain())
// 	{
// 		//精度测试，电气量项目固定增加读遥测通讯命令
// 		GenGbCommCmd_ReadAin(pMacroTest);
// 	}

	return pMacroTest;
}

//shaolei 2023-1-30 增加形参pListParasMap。子对象为CItemsGenDataMap。
//pListParasMap为空，则说明是原生态功能，界面参数取自m_pUIParasGroup。
void CGbItemsGenTool::GenGbItemBase_Define_MacroTest_InitReport(CMacroTest *pMacroTest, CExBaseList *pListParasMap)  //2022-3-15 lijunqing
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++begin GenGbItemBase_Define_MacroTest_InitReport"));
    CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
    CString strMacroID = pMacroTestPara->GetMacroID();
    CTestMacro *pTestMacro = (CTestMacro *)m_pGuideBook->m_pTestMacros->FindByID(strMacroID);

    if (pTestMacro == NULL)
    {
        return;
    }

    CShortDatas *pFaultParas = pTestMacro->GetFaultParas();
    CShortDatas *pSysParas = pTestMacro->GetSysParas();
    CShortDatas oList, oListEx;
    oList.AppendEx(*pFaultParas, FALSE);
    oList.AppendEx(*pSysParas, FALSE);

	CReport *pReport = pMacroTest->AddReport(&oList);
	pReport->m_strID = STT_REPORT_ID_INIT;   //固定ID，在界面初始化之后，应当删除
	oList.RemoveAll(); 

	 //2023-1-6  新增扩展故障参数、扩展结果参数
	long nStateCount = -1;
	CDvmData *pStateCount = (CDvmData*)m_pUIParasGroup->FindByID(_T("StateCount"));

	if (pStateCount != NULL)
	{
		nStateCount = CString_To_long(pStateCount->m_strValue);
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++begin GenGbItemBase_Define_MacroTest_InitReport---------1"));
#ifndef _PSX_QT_LINUX_ 
	pTestMacro->InitFaultParasEx(oListEx, nStateCount);
#else 
	if (strMacroID != _T("StateTest"))
	{
		//Linux下，状态序列。不回传故障参数
		pTestMacro->InitFaultParasEx(oListEx, nStateCount);
	}
#endif
	pReport->AppendRptValues(&oListEx);
	CValues *pValues = pReport->m_pValues;
	oListEx.RemoveAll();
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++begin GenGbItemBase_Define_MacroTest_InitReport---------2"));
	//报告数据，只上传非默认值
	GenGbItemBase_Define_MacroTest_InitReport_SortByDefault(pReport, pListParasMap);

#ifndef _PSX_QT_LINUX_
	//Linux下，初始报告，不需要送TestMacro定义的结果参数
	//Linux下初始报告，不需要送TestMacro定义的结果参数
	CShortDatas *pResults = pTestMacro->GetResults();
	oList.AppendEx(*pResults, FALSE);
	pTestMacro->InitResultParasEx(oListEx, nStateCount);
 	pReport->AddReport(pResults);
	pReport->AppendRptValues(&oListEx);
	oListEx.RemoveAll();
	oList.RemoveAll();
#endif

	pReport->AddRptValues_ErrorCal();
	CValue *pRsltJdg = (CValue *)pValues->FindByID(g_strTestResultJudgeKey);

	if (pRsltJdg == NULL)
	{
		pValues->AddValue(g_strTestResultJudgeKey, _T("-1"));
	}
	else
	{
		pRsltJdg->m_strValue = _T("-1");
	}

	CValue *pRsltDsc = (CValue *)pValues->FindByID(g_strTestResultDescriptKey);

	if (pRsltDsc == NULL)
	{
		pValues->AddValue(g_strTestResultDescriptKey, g_sLangTxt_NotTest/*_T("未测试")*/);
	}
	else
	{
		pRsltDsc->m_strValue = g_sLangTxt_NotTest/*_T("未测试")*/;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("------------------end GenGbItemBase_Define_MacroTest_InitReport"));
}

void CGbItemsGenTool::GenGbItemBase_Define_MacroTest_InitReport_SortByDefault(CReport *pReport, CExBaseList *pListParasMap)
{
	CValues *pValues = pReport->m_pValues;
	CValue *pFind = NULL;

	if (pListParasMap != NULL)
	{
		//网页功能
		POS pos = pListParasMap->GetHeadPosition();

		while (pos != NULL)
		{
			CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pListParasMap->GetNext(pos);

			//映射失败的参数，不作为电气量项目的参数
			if (!pDataMap->m_nIsMapSucc)
			{
				continue;
			}

			pFind = (CValue*)pValues->FindByID(pDataMap->m_strID);

			if (pFind != NULL)
			{
				if (pDataMap->m_nKeepExpr)
				{
					//保留表达式的，需处理表达式
					GenGbItemBase_Define_MacroTest_InitReport_Expression(pFind->m_strValue, pReport, pDataMap->m_strValue); 
				}
				else
				{
					pFind->m_strValue = pDataMap->m_strValue;
				}
			}
		}
	}
	else
	{
		//原生态功能，此时，m_pUIParasGroup中的参数，已经经过非默认值过滤过了
		CExBaseList oListUiParas;
		m_pUIParasGroup->SelectAllDatas(oListUiParas);
		POS pos = oListUiParas.GetHeadPosition();
		
		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)oListUiParas.GetNext(pos);
			CString strDataPath = pData->GetIDPathEx(m_pUIParasGroup, FALSE);

			pFind = (CValue*)pValues->FindByID(strDataPath);

			if (pFind != NULL)
			{
				pFind->m_dwReserved = 1;
				pFind->m_strValue = pData->m_strValue;

				if (pData->m_strFormat.GetLength() > 0)
				{
					//有表达式绑定，再处理表达式
					GenGbItemBase_Define_MacroTest_InitReport_Expression(pFind->m_strValue, pReport, pData->m_strFormat); 
				}
			}
		}

		//再删除没有引用的结果参数，即：参数 = 默认值的
		pos = pValues->GetHeadPosition();

		while (pos != NULL)
		{
			CValue *pValue = (CValue *)pValues->GetNext(pos);

#ifdef _PSX_QT_LINUX_
			//windows这边保留所有的结果参数
// 			if (pValue->m_strID == g_strTestResultAbsRsltCal1Key||
// 				pValue->m_strID == g_strTestResultAbsRsltCal2Key||
// 				pValue->m_strID == g_strTestResultRelRsltCal1Key||
// 				pValue->m_strID == g_strTestResultRelRsltCal2Key)
// 			{
// 				//这几个参数永远保留，用于计算结果绑定
// 				continue;
// 			}

			if (pValue->m_dwReserved != 1)
			{
				pValues->Delete(pValue);
				continue;
			}
#endif

			if (pValue->m_strID == _T("TtripA"))
			{
				pValue->m_strValue = "合格";
			}
		}

		oListUiParas.RemoveAll();
	}

//     pFind = (CValue*)pValues->FindByID("TtripA");
// 
//     if (pFind != NULL)
//     {
//         pFind->m_strValue = "合格";
//     }
}

void CGbItemsGenTool::GenGbItemBase_Define_MacroTest_InitReport(CMacroCharItems *pMacroCharItems)
{
	//windows版本下，特性曲线下生成的电气量项目，自动生成初始报告
#ifdef _PSX_QT_LINUX_
	return;
#endif

	CExBaseList listMacroTest;
	pMacroCharItems->GetAllMacroTestItemsEx(&listMacroTest);

	POS pos = listMacroTest.GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)listMacroTest.GetNext(pos);
		GenGbItemBase_Define_MacroTest_InitReport_Characteristic(pMacroTest);
	}

	listMacroTest.RemoveAll();
}

void CGbItemsGenTool::GenGbItemBase_Define_MacroTest_InitReport_Characteristic(CMacroTest *pMacroTest)
{
#ifdef _PSX_QT_LINUX_
	return;
#endif
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CString strMacroID = pMacroTestPara->GetMacroID();
	CTestMacro *pTestMacro = (CTestMacro *)m_pGuideBook->m_pTestMacros->FindByID(strMacroID);

	if (pTestMacro == NULL)
	{
		return;
	}

	CShortDatas *pFaultParas = pTestMacro->GetFaultParas();
	CShortDatas *pSysParas = pTestMacro->GetSysParas();
	CShortDatas oList, oListEx;
	oList.AppendEx(*pFaultParas, FALSE);
	oList.AppendEx(*pSysParas, FALSE);

	CShortDatas *pResults = pTestMacro->GetResults();
	oList.AppendEx(*pResults, FALSE);
	CReport *pReport = pMacroTest->AddReport(&oList);
	pReport->m_strID = STT_REPORT_ID_INIT;   //固定ID，在界面初始化之后，应当删除
	oList.RemoveAll(); 

	//先添加所有的数据作为报告数据
	pTestMacro->InitFaultParasEx(oListEx, -1);
	pReport->AppendRptValues(&oListEx);
	oListEx.RemoveAll();
	CValues *pValues = pReport->m_pValues;

	//再根据参数，更新报告中的数据值
	CValue *pFind = NULL;
	CMacroTestParaDatas* pParas = pMacroTestPara->GetFaultParaDatas();
	POS pos = pParas->GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTestParaData* pData = (CMacroTestParaData*)pParas->GetNext(pos);
		pFind = (CValue *)pValues->FindByID(pData->m_strID);

		if (pFind != NULL)
		{
			pFind->m_strValue = pData->m_strExpression;
		}
	}

	pReport->AddRptValues_ErrorCal();
	CValue *pRsltJdg = (CValue *)pValues->FindByID(g_strTestResultJudgeKey);
	pRsltJdg->m_strValue = _T("-1");
	CValue *pRsltDsc = (CValue *)pValues->FindByID(g_strTestResultDescriptKey);
	pRsltDsc->m_strValue = g_sLangTxt_NotTest/*_T("未测试")*/;
}

//初始化报告，处理参数绑定定值、系统参数表达式
void CGbItemsGenTool::GenGbItemBase_Define_MacroTest_InitReport_Expression(CString &strValue, CReport *pReport, const CString &strExpress)
{
	double dValue = 0;

	if (strExpress.GetLength() == 0)
	{
		return;
	}

	CDevice *pDevice = (CDevice*)pReport->GetAncestor(GBCLASSID_DEVICE);

	if (!Gb_CalParaExpression(strExpress, pDevice, dValue, FALSE))
	{
#ifdef _DEBUG
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("电气量项目，计算初始报告结果值，表达式计算错误 [%s] ，结果值设置为0.000……"), strExpress.GetString());
#endif
		return;
	}

	strValue.Format(_T("%.3f"), dValue);
}

long CGbItemsGenTool::GenGuideBook_MacroTest_Single(const CString& strMacroID, const CString& strParentItemPath, const CString& strItemsName, const CString& strItemsID, CDataGroup* pMacroParas)
{
	CGbItemBase *pParent = (CGbItemBase* )Gb_GetItem(m_pGuideBook, strParentItemPath);

	if (pParent == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("生成测试项目失败，父项目没找到【%s】"), strParentItemPath.GetString());
		return -1;
	}

	if (pParent->GetClassID() != GBCLASSID_ITEMS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("生成测试项目失败，父项目类型不正确【%s】"), strParentItemPath.GetString());
		return -1;
	}

	if (pMacroParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数错误！缺少【%s】，测试项目参数设置失败！"), STT_CMD_PARA_generate_items_MacroParas);
		return FALSE;
	}

	CMacroTest *pMacroTest = new CMacroTest();
	m_pMacroTest = pMacroTest;
	pMacroTest->m_strName = strItemsName;
	pMacroTest->m_strID = strItemsID;
	pMacroTest->InitAfterRead();
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	pMacroTestPara->SetMacroID(strMacroID);
	pMacroTestPara->InitAfterRead();

	CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

	if (pUIParas != NULL)
	{
		CString strParasText;
		GetXml_TestMacroUiParas(strParasText, pMacroParas);
		//pUIParas->SetParaText(strParasText);
		pUIParas->m_strParaText = strParasText;
	}

	pParent->AddNewChild(pMacroTest);

	if (m_pItems_SelfDef == NULL)
	{
		return 0;
	}

	if (strParentItemPath != m_pItems_SelfDef->GetIDPathEx(GBCLASSID_DEVICE, FALSE))
	{
		return 0;
	}

	CMacroSelfDefGen *pSelfDef = (CMacroSelfDefGen *)m_pGbItemsGen->FindByClassID(GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN);

	if (pSelfDef == NULL)
	{
		return 0;
	}

	CItemGenRsltExpr* pRsltExprGen = pSelfDef->GetItemGenRsltExpr();

	if (pRsltExprGen == NULL)
	{
		return 0;
	}

	CItemRsltExprRun *pRsltExprRun = new CItemRsltExprRun;
	InitRsltExpr(pRsltExprRun, pSelfDef->GetItemsGenParasMap(), pRsltExprGen, NULL);
	pMacroTest->AddNewChild(pRsltExprRun);
	pMacroTest->m_pRsltExprRun = pRsltExprRun;

	return 0;
}

void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr(CMacroTest *pMacroTest)
{
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CString strMacroID = pMacroTestPara->GetMacroID();

	if (strMacroID == STT_CMD_ATS_MACRO_ID_GradientTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_GradientTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_StateTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_StateTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_ManualTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_ManualTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_SequenceManuTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_SequenceManuTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_HarmTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_HarmTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_SequenceGradientTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_SequenceGradientTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_LineVolGradientTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_LineVolGradientTest(pMacroTest);
	}
	else if (strMacroID == STT_CMD_ATS_MACRO_ID_LineVolManuTest)
	{
		GenGbItemBase_MacroTest_RsltExpr_LineVoltManualTest(pMacroTest);
	}
}

//处理结果判断 - 状态序列
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_StateTest(CMacroTest *pMacroTest)
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();  //构造函数中默认是逻辑与   logic == and
	pRsltExprRun->DeleteAll();

	CDataGroup *pRsltEvalute = (CDataGroup *)m_pUIParasGroup->FindByID(_T("rslt_evaluation"));   //结果评估

	if (pRsltEvalute == NULL)
	{
		return;
	}

	POS pos = pRsltEvalute->GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		CXExprNode *pExprNode = new CXExprNode();
		pRsltExprRun->AddNewChild(pExprNode);
		CDataGroup *pEvaluteGrp = (CDataGroup *)pRsltEvalute->GetNext(pos);
		GenGbItemBase_MacroTest_RsltExpr_StateTest(nIndex, pEvaluteGrp, pExprNode);
		nIndex++;
	}
}

//nIndex从0开始
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_StateTest(long nIndex, CDataGroup *pEvaluteGrp, CXExprNode *pExprNode)
{
	CString strID, strName, strIndex;
	strIndex.Format(_T("%d"), nIndex);
	strID.Format(_T("rslt_evaluation$rslt_evaluation%d$"), nIndex);
	strName = g_sLangTxt_RsltEvaluation;
	strName += _T("$");
	strName += g_sLangTxt_RsltEvaluation;
	strName += strIndex;
	strName += _T("$");
	//strName.Format(_T("结果评估$结果评估%d$"), nIndex+1);

	CString strValueID;
	CXExprBase *pExpr = NULL;
	long nUseError = 1;
	CDvmData *pUseError = (CDvmData *)pEvaluteGrp->FindByID(_T("UseError"));  //当前结果评估是否启用

	if (pUseError != NULL)
	{
		nUseError = CString_To_long(pUseError->m_strValue);
	}

	CDvmData *pErrorLogic = (CDvmData *)pEvaluteGrp->FindByID(_T("ErrorLogic"));
	long nErrorLogic = 0;

	if (pErrorLogic != NULL)
	{
		nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
	}

	CXExprValue* pValue = NULL;   //测试结果参数
	CXExprValueStd* pValueStd = NULL;   //基准参数
	CXExprValueErrorRel* pValueErrRel = NULL;  //相对误差限
	CXExprValueErrorAbs* pValueErrAbs = NULL;  //绝对误差限

	if (nErrorLogic == ERROR_LOGIC_COMB)
	{
		//组合误差 
		pExpr = new CXExprErrorCombined();
		CXExprErrorCombined *pExprCombined = (CXExprErrorCombined *)pExpr;

		pValue = pExprCombined->GetExprValue();
		pValueStd = pExprCombined->GetExprValueStd();
		pValueErrRel = pExprCombined->GetExprValueErrorRel();
		pValueErrAbs = pExprCombined->GetExprValueErrorAbs();

		CXExprValueErrorRslt* pAbsErrValue = pExprCombined->GetExprValueErrorRslt();
		pAbsErrValue->m_strType = _T("report");
		//strValueID.Format(_T("rslt_evaluation$rslt_evaluation%d$Ttrip_AbsErr"), nIndex);
		pAbsErrValue->m_strValueID = strID + _T("Ttrip_AbsErr");  //计算的绝对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueUnit = _T("ms");
	}
	else
	{
		//扩展误差计算
		pExpr = new CXExprErrorEx();
		CXExprErrorEx *pErrorEx = (CXExprErrorEx *)pExpr;
		pErrorEx->m_strOptr = _T("<");

		ErrorLogicType(pErrorEx,nErrorLogic);

		pValue = pErrorEx->GetExprValue();
		pValueStd = pErrorEx->GetExprValueStd();
		pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrAbs = pErrorEx->GetExprValueErrorAbs();

		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		//strValueID.Format(_T("rslt_evaluation$rslt_evaluation%d$Ttrip_RelErr"), nIndex);
		pRelErrValue->m_strValueID = strID + _T("Ttrip_RelErr")/*strValueID*/;  //计算的相对误差值，重新绑定回结果参数

		CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
		pAbsErrValue->m_strType = _T("report");
		//strValueID.Format(_T("rslt_evaluation$rslt_evaluation%d$Ttrip_AbsErr"), nIndex);
		pAbsErrValue->m_strValueID = strID + _T("Ttrip_AbsErr")/*strValueID*/;  //计算的绝对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueUnit = _T("ms");
	}
	
	pExprNode->AddNewChild(pExpr);
	pExprNode->m_nIsUse = nUseError;
	pExprNode->m_strUse.Format(_T("%d"), nUseError);

	pValue->m_strType = _T("report");
	//strValueID.Format(_T("rslt_evaluation$rslt_evaluation%d$Ttrip"), nIndex);
	pValue->m_strValueID = strID + _T("Ttrip")/*strValueID*/;  //19814底层计算好的时间差：自定义时间差

	CDvmData *pTSet = (CDvmData *)pEvaluteGrp->FindByID(_T("TSet"));  //整定值
	pValueStd->m_strType = _T("report");   //改成report，整定值回填到报告
	pValueStd->m_strValue = pTSet->m_strValue;
	//pValueStd->m_strValueName = _T("整定值(s)");
	pValueStd->m_strValueName = strName + g_sLangTxt_TSet/*_T("整定值(s)")*/;//.Format(_T("结果评估$结果评估%d$整定值(s)"), nIndex+1);
	pValueStd->m_strValueID = strID + _T("TSet");//.Format(_T("rslt_evaluation$rslt_evaluation%d$TSet"), nIndex);

	CDvmData *pRelErr = (CDvmData *)pEvaluteGrp->FindByID(_T("ActT_RelErr"));  //相对误差限
	pValueErrRel->m_strType = _T("number");
	pValueErrRel->m_strValue = pRelErr->m_strValue;
	pValueErrRel->m_strValueName = strName + g_sLangTxt_T_ErrRel/*_T("相对误差限(%)")*/;//.Format(_T("结果评估$结果评估%d$相对误差限(%)"), nIndex+1);
	//pValueErrRel->m_strValueName = _T("相对误差限(%)");

	CDvmData *pAbsErr = (CDvmData *)pEvaluteGrp->FindByID(_T("ActT_AbsErr"));  //绝对误差限
	pValueErrAbs->m_strType = _T("number");
	pValueErrAbs->m_strValue = pAbsErr->m_strValue;
	pValueErrAbs->m_strValueName = strName + g_sLangTxt_T_ErrAbs/*_T("绝对误差限(s)")*/;//.Format(_T("结果评估$结果评估%d$绝对误差限(s)"), nIndex+1);
	//pValueErrAbs->m_strValueName = _T("绝对误差限(s)");

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalMaxAbs = NULL;
	CXExprCal *pCalMinAbs = NULL; 
	CXExprCal *pCalMaxRel = NULL;
	CXExprCal *pCalMinRel = NULL; 
	CString strMaxMinAbs, strMaxMinRel;
	strMaxMinAbs.Format(_T("rslt_evaluation$rslt_evaluation%d$Ttrip_AbsErr"), nIndex);
	strMaxMinRel.Format(_T("rslt_evaluation$rslt_evaluation%d$Ttrip_RelErr"), nIndex);

	if (nErrorLogic == ERROR_LOGIC_COMB
		|| nErrorLogic == ERROR_LOGIC_ABS)
	{
		pCalMaxAbs = new CXExprCal();
		pExprNode->AddNewChild(pCalMaxAbs);

		pCalMinAbs = new CXExprCal();
		pExprNode->AddNewChild(pCalMinAbs);
	}
	else if (nErrorLogic == ERROR_LOGIC_REL)
	{
		pCalMaxRel = new CXExprCal();
		pExprNode->AddNewChild(pCalMaxRel);

		pCalMinRel = new CXExprCal();
		pExprNode->AddNewChild(pCalMinRel);
	}
	else if (nErrorLogic == ERROR_LOGIC_OR
		|| nErrorLogic == ERROR_LOGIC_AND)
	{
		pCalMaxAbs = new CXExprCal();
		pExprNode->AddNewChild(pCalMaxAbs);

		pCalMinAbs = new CXExprCal();
		pExprNode->AddNewChild(pCalMinAbs);
		pCalMaxRel = new CXExprCal();
		pExprNode->AddNewChild(pCalMaxRel);

		pCalMinRel = new CXExprCal();
		pExprNode->AddNewChild(pCalMinRel);
	}
	
	if (pCalMaxAbs != NULL)
	{
		pCalMaxAbs->AddQueryMax(strMaxMinAbs);
		pCalMaxAbs->m_strValueDstID = strID + _T("ActT_AbsErr_Max");// = _T("ActT_AbsErr_Max");
		pCalMaxAbs->m_strValueName = strName + g_sLangTxt_T_AbsErr_Max/*_T("绝对误差最大值(ms)")*/;// = _T("绝对误差最大值");
	}

	if (pCalMinAbs != NULL)
	{
		pCalMinAbs->AddQueryMin(strMaxMinAbs);
		pCalMinAbs->m_strValueDstID = strID + _T("ActT_AbsErr_Min");// = _T("ActT_AbsErr_Min");
		pCalMinAbs->m_strValueName = strName + g_sLangTxt_T_AbsErr_Min/*_T("绝对误差最小值(ms)")*/;// = _T("绝对误差最小值");
	}

	if (pCalMaxRel != NULL)
	{
		pCalMaxRel->AddQueryMax(strMaxMinRel);
		pCalMaxRel->m_strValueDstID = strID + _T("ActT_RelErr_Max");
		pCalMaxRel->m_strValueName = strName + g_sLangTxt_T_RelErr_Max/*_T("相对误差最大值(%)")*/;
	}

	if (pCalMinRel != NULL)
	{
		pCalMinRel->AddQueryMin(strMaxMinRel);
		pCalMinRel->m_strValueDstID = strID + _T("ActT_RelErr_Min");
		pCalMinRel->m_strValueName = strName + g_sLangTxt_T_RelErr_Min/*_T("相对误差最小值(%)")*/;
	}
}

//处理结果判断 - 递变试验
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_GradientTest(CMacroTest *pMacroTest)
{
	//用于调试重复次数
 	//pMacroTest->m_nRepeatTimes = 5;
 	//pMacroTest->m_strReportMode = g_strCalMode_Average;

	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();//new CItemRsltExprRun;
	pRsltExprRun->DeleteAll();
	long nVaryMode=0, nVarType=0, nVarIndexType = 0;
	CDvmData *pVaryMode = (CDvmData *)m_pUIParasGroup->FindByID(_T("VaryMode"));  //递变类型
	CDvmData *pVarType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarType"));   //变量类型
	CDvmData *pVarIndexType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarIndexType"));

	ASSERT(pVarIndexType != NULL && pVarType != NULL && pVaryMode != NULL);

	if (pVaryMode == NULL || pVarIndexType == NULL || pVarType == NULL)
	{
		return;
	}

	nVaryMode = CString_To_long(pVaryMode->m_strValue);
	nVarType = CString_To_long(pVarType->m_strValue);
	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);

	if (nVaryMode == Gradient_VaryMode_Act)//动作值
	{
		ActionValueGradient(pRsltExprRun, nVarType, nVarIndexType, STT_CMD_ATS_MACRO_ID_GradientTest);
	}
	else if (nVaryMode == Gradient_VaryMode_Return)
	{
		ReturnValueGradient(pRsltExprRun);
	}
	else if (nVaryMode == Gradient_VaryMode_Angle)
	{
		//最大灵敏角
		if (nVarType != Gradient_VarType_Ph)
		{
			//最大灵敏角只针对相位
			return; 
		}

		MaxAngleValueGradient(pRsltExprRun);
	}
}

/*
<group id="autoset" data-type="auto" value="">
	<data id="_bAutoChange" data-type="" value="1" />
	<data id="_Variable" data-type="" value="23" />
	<data id="_VarType" data-type="" value="0" />
	<data id="_HarmIndex" data-type="" value="1" />
	<data id="_BeginVal" data-type="" value="1.000" />
	<data id="_EndVal" data-type="" value="100.000" />
	<data id="_StepVal" data-type="" value="1.000" />
	<data id="_StepTime" data-type="" value="1.000" />
	<data id="VarIndexType" data-type="" value="1" />
</group>
*/
//处理结果判断-谐波
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_HarmTest(CMacroTest *pMacroTest)  //谐波
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();
	pRsltExprRun->DeleteAll();
	long nVarIndexType = 0;
	long nAuto = 0;

	//谐波模块，这两个参数在autoset的group中
	CDataGroup *pAusoSet = (CDataGroup *)m_pUIParasGroup->FindByID(_T("autoset"));
	ASSERT(pAusoSet != NULL);

	if (pAusoSet == NULL)
	{
		return;
	}

	CDvmData *pVarIndexType = (CDvmData *)pAusoSet->FindByID(_T("VarIndexType"));
	CDvmData *pAuto=(CDvmData*)pAusoSet->FindByID(_T("_bAutoChange"));

	ASSERT(pVarIndexType != NULL  && pAuto != NULL);

	if (pVarIndexType == NULL || pAuto == NULL)
	{
		return;
	}

	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);
	nAuto = CString_To_long(pAuto->m_strValue);

	if (nAuto)
	{
		CXExprErrorEx *pErrorEx = new CXExprErrorEx;
		pRsltExprRun->AddNewChild(pErrorEx);
		pErrorEx->m_strOptr = _T("<");
		CXExprValueStd* pValueStd = pErrorEx->GetExprValueStd();
		pValueStd->m_strType = _T("report");   //回填报告中去
		pValueStd->m_strValueID = _T("ActSet");
		long nErrorLogic = 0;
		CDvmData *pRelErr = NULL;
		CDvmData *pAbsErr = NULL;

		CXExprValueErrorAbs* pValueErrAbs = pErrorEx->GetExprValueErrorAbs();
		pValueErrAbs->m_strType = _T("number");

		CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
		pAbsErrValue->m_strType = _T("report");

		CXExprValue* pValue = pErrorEx->GetExprValue();
		pValue->m_strType = _T("report");
		pValue->m_strValueID = _T("ActValue");  //动作值的报告数据

		if(nVarIndexType == Harm_VarIndexType_U) //电压递变
		{
			CDvmData *pUSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("USet"));  //电压整定动作值
			pValueStd->m_strValue = pUSet->m_strValue;
			pValueStd->m_strValueName = g_sLangTxt_USet/*_T("电压整定动作值(V)")*/;

			CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_ErrorLogic"));  //电压动作值误差判断逻辑

			if (pErrorLogic != NULL)
			{
				nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
			}

			CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
			pValueErrRel->m_strType = _T("number");
			CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
			pRelErrValue->m_strType = _T("report");
			pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_RelErr"));  //电压动作值相对误差限
			pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_AbsErr"));  //电压动作值绝对误差限

			pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
			pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
			pRelErrValue->m_strValueName = g_sLangTxt_U_RelErr/*_T("电压动作值相对误差(%)")*/;
			pAbsErrValue->m_strValueName = g_sLangTxt_U_AbsErr/*_T("电压动作值绝对误差(V)")*/;
			pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
			pValueErrRel->m_strValueName = g_sLangTxt_U_ErrRel/*_T("电压动作值相对误差限(%)")*/;
			pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
			pValueErrAbs->m_strValueName = g_sLangTxt_U_ErrAbs/*_T("电压动作值绝对误差限(V)")*/;

			pValue->m_strValueName = g_sLangTxt_U_Act/*_T("电压动作值(V)")*/;
		}
		else //电流递变
		{
			CDvmData *pISet = (CDvmData *)m_pUIParasGroup->FindByID(_T("ISet"));  //电流整定动作值
			pValueStd->m_strValue = pISet->m_strValue;
			pValueStd->m_strValueName = g_sLangTxt_ISet/*_T("电流整定动作值(A)")*/;
			CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_ErrorLogic"));  //电流动作值误差判断逻辑

			if (pErrorLogic != NULL)
			{
				nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
			}

			CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
			pValueErrRel->m_strType = _T("number");
			CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
			pRelErrValue->m_strType = _T("report");
			pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_RelErr"));  //电流动作值相对误差限
			pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_AbsErr"));  //电流动作值绝对误差限

			pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
			pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
			pRelErrValue->m_strValueName = g_sLangTxt_I_RelErr/*_T("电流动作值相对误差(%)")*/;
			pAbsErrValue->m_strValueName = g_sLangTxt_I_AbsErr/*_T("电流动作值绝对误差(A)")*/;
			pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
			pValueErrRel->m_strValueName = g_sLangTxt_I_ErrRel/*_T("电流动作值相对误差限(%)")*/;
			pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
			pValueErrAbs->m_strValueName = g_sLangTxt_I_ErrAbs/*_T("电流动作值绝对误差限(A)")*/;

			pValue->m_strValueName = g_sLangTxt_I_Act/*_T("电流动作值(A)")*/;
		}
		
		ErrorLogicType(pErrorEx,nErrorLogic);
		
		//处理expr-cal。用于固定计算误差最大值和最小值
		CXExprCal *pCalRelMax = NULL;
		CXExprCal *pCalRelMin = NULL;
		CXExprCal *pCalAbsMax = NULL;
		CXExprCal *pCalAbsMin = NULL;

		if (pErrorEx->m_strMode == _T("real"))
		{
			pCalRelMax = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalRelMax);
			pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
			pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");//相对误差最大值

			pCalRelMin = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalRelMin);
			pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
			pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");//相对误差最小值
		}
		else if (pErrorEx->m_strMode == _T("abs"))
		{
			pCalAbsMax = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalAbsMax);
			pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
			pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");//绝对误差最大值

			pCalAbsMin = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalAbsMin);
			pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
			pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");//绝对误差最小值
		}
		else if (pErrorEx->m_strMode == _T("or") || pErrorEx->m_strMode == _T("and"))
		{
			pCalRelMax = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalRelMax);
			pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
			pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");

			pCalRelMin = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalRelMin);
			pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
			pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");

			pCalAbsMax = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalAbsMax);
			pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
			pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");

			pCalAbsMin = new CXExprCal();
			pRsltExprRun->AddNewChild(pCalAbsMin);
			pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
			pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
		}

		if (nVarIndexType == Harm_VarIndexType_U)//电压动作值递变
		{
			if (pCalAbsMax != NULL)
			{
				pCalAbsMax->m_strValueName = g_sLangTxt_U_AbsErr_Max/*_T("电压动作值绝对误差最大值(V)")*/;
			}
			if (pCalRelMax != NULL)
			{
				pCalRelMax->m_strValueName = g_sLangTxt_U_RelErr_Max/*_T("电压动作值相对误差最大值(%)")*/;
			}
			if (pCalAbsMin != NULL)
			{
				pCalAbsMin->m_strValueName = g_sLangTxt_U_AbsErr_Min/*_T("电压动作值绝对误差最小值(V)")*/;
			}
			if (pCalRelMin != NULL)
			{
				pCalRelMin->m_strValueName = g_sLangTxt_U_RelErr_Min/*_T("电压动作值相对误差最小值(%)")*/;
			}
		}

		if (nVarIndexType == Harm_VarIndexType_I)//电流动作值递变
		{
			if (pCalAbsMax != NULL)
			{
				pCalAbsMax->m_strValueName = g_sLangTxt_I_AbsErr_Max/*_T("电流动作值绝对误差最大值(A)")*/;
			}
			if (pCalRelMax != NULL)
			{
				pCalRelMax->m_strValueName = g_sLangTxt_I_RelErr_Max/*_T("电流动作值相对误差最大值(%)")*/;
			}
			if (pCalAbsMin != NULL)
			{
				pCalAbsMin->m_strValueName = g_sLangTxt_I_AbsErr_Min/*_T("电流动作值绝对误差最小值(A)")*/;
			}
			if (pCalRelMin != NULL)
			{
				pCalRelMin->m_strValueName = g_sLangTxt_I_RelErr_Min/*_T("电流动作值相对误差最小值(%)")*/;
			}
		}
	}

	//动作时间
	ActionTimeValue(pRsltExprRun);
}

//处理结果判断-通用试验
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_ManualTest(CMacroTest *pMacroTest)  //通用试验 
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();
	pRsltExprRun->DeleteAll();
	long nVaryMode=0, nVarType=0, nVarIndexType = 0;
	long nAuto = 0;
	CDvmData *pVaryMode = (CDvmData *)m_pUIParasGroup->FindByID(_T("Mode"));  //递变类型
	CDvmData *pVarType = (CDvmData *)m_pUIParasGroup->FindByID(_T("_GradientTpSelect")); //递变类型选择
	CDvmData *pVarIndexType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarIndexType"));
	CDvmData *pAuto=(CDvmData*)m_pUIParasGroup->FindByID(_T("_bAuto"));//自动

	ASSERT(pVarIndexType != NULL && pVarType != NULL && pVaryMode != NULL && pAuto != NULL);

	if (pVaryMode == NULL || pVarIndexType == NULL || pVarType == NULL  || pAuto == NULL)
	{
		return;
	}

	nVarType = CString_To_long(pVarType->m_strValue);
	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);
	nAuto = CString_To_long(pAuto->m_strValue);
	nVaryMode = CString_To_long(pVaryMode->m_strValue);

	if (nAuto)
	{
		if (nVaryMode == Manual_VaryMode_Act)//动作值
		{
			ActionValueGradient(pRsltExprRun,nVarType,nVarIndexType, STT_CMD_ATS_MACRO_ID_ManualTest);
		}
		else if (nVaryMode == Manual_VaryMode_Return)//返回系数
		{
			ReturnValueGradient(pRsltExprRun);
		}
	}

	//动作时间	
	ActionTimeValue(pRsltExprRun);
}

//处理结果判断-序分量
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_SequenceManuTest(CMacroTest *pMacroTest)  //序分量
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();
	pRsltExprRun->DeleteAll();
	long nVaryMode=0, nVarType=0, nVarIndexType = 0;
	long nAuto = 0;
	CDvmData *pVaryMode = (CDvmData *)m_pUIParasGroup->FindByID(_T("Mode"));  //递变类型
	CDvmData *pVarType = (CDvmData *)m_pUIParasGroup->FindByID(_T("_GradientTpSelect")); //递变类型选择
	CDvmData *pVarIndexType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarIndexType"));
	CDvmData *pAuto=(CDvmData*)m_pUIParasGroup->FindByID(_T("_bAuto"));//自动

	ASSERT(pVarIndexType != NULL && pVarType != NULL && pVaryMode != NULL && pAuto != NULL);

	if (pVaryMode == NULL || pVarIndexType == NULL || pVarType == NULL  || pAuto == NULL)
	{
		return;
	}

	nVarType = CString_To_long(pVarType->m_strValue);
	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);
	nAuto = CString_To_long(pAuto->m_strValue);
	nVaryMode = CString_To_long(pVaryMode->m_strValue);

	if (nAuto)
	{
		if (nVaryMode == SequenceManu_VaryMode_Act)//动作值
		{
			ActionValueGradient(pRsltExprRun,nVarType,nVarIndexType, STT_CMD_ATS_MACRO_ID_SequenceManuTest);
		}
		else if (nVaryMode == SequenceManu_VaryMode_Return)//返回系数
		{
			ReturnValueGradient(pRsltExprRun);
		}
	}

	//动作时间
	ActionTimeValue(pRsltExprRun);
}

//递变-序分量
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_SequenceGradientTest(CMacroTest *pMacroTest)
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();//new CItemRsltExprRun;
	pRsltExprRun->DeleteAll();
	long nVarIndexType = 0;
	CDvmData *pVarIndexType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarIndexType"));

	ASSERT(pVarIndexType != NULL );

	if (pVarIndexType == NULL)
	{
		return;
	}

	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);

	//动作值
	CXExprErrorEx *pErrorEx = new CXExprErrorEx;
	pRsltExprRun->AddNewChild(pErrorEx);
	pErrorEx->m_strOptr = _T("<");
	CXExprValueStd* pValueStd = pErrorEx->GetExprValueStd();
	pValueStd->m_strType = _T("report");   
	pValueStd->m_strValueID = _T("ActSet");
	long nErrorLogic = 0;
	CDvmData *pRelErr = NULL;
	CDvmData *pAbsErr = NULL;

	CXExprValueErrorAbs* pValueErrAbs = pErrorEx->GetExprValueErrorAbs();
	pValueErrAbs->m_strType = _T("number");

	CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
	pAbsErrValue->m_strType = _T("report");


	if (nVarIndexType == SequenceGradient_VarIndexType_I)
	{	
		CDvmData *pISet = (CDvmData *)m_pUIParasGroup->FindByID(_T("ISet"));  //电流整定动作值
		pValueStd->m_strValue = pISet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_ISet/*_T("电流整定动作值(A)")*/;
		CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_ErrorLogic"));  //电流动作值误差判断逻辑

		if (pErrorLogic != NULL)
		{
			nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
		}

		CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrRel->m_strType = _T("number");
		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_RelErr"));  //电流动作值相对误差限
		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_AbsErr"));  //电流动作值绝对误差限

		pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pRelErrValue->m_strValueName = g_sLangTxt_I_RelErr/*_T("电流动作值相对误差值(%)")*/;
		pAbsErrValue->m_strValueName = g_sLangTxt_I_AbsErr/*_T("电流动作值绝对误差值(A)")*/;

		pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
		pValueErrRel->m_strValueName = g_sLangTxt_I_ErrRel/*_T("电流动作值相对误差限(%)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_I_ErrAbs/*_T("电流动作值绝对误差限(A)")*/;
	}
	else if (nVarIndexType == SequenceGradient_VarIndexType_U)
	{
		CDvmData *pUSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("USet"));  //电压整定动作值
		pValueStd->m_strValue = pUSet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_USet/*_T("电压整定动作值(V)")*/;

		CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_ErrorLogic"));  //电压动作值误差判断逻辑

		if (pErrorLogic != NULL)
		{
			nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
		}

		CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrRel->m_strType = _T("number");
		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_RelErr"));  //电压动作值相对误差限
		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_AbsErr"));  //电压动作值绝对误差限

		pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pRelErrValue->m_strValueName = g_sLangTxt_U_RelErr/*_T("电压动作值相对误差值(%)")*/;
		pAbsErrValue->m_strValueName = g_sLangTxt_U_AbsErr/*_T("电压动作值绝对误差值(V)")*/;

		pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
		pValueErrRel->m_strValueName = g_sLangTxt_U_ErrRel/*_T("电压动作值相对误差限(%)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_U_ErrAbs/*_T("电压动作值绝对误差限(V)")*/;
	}

	switch(nErrorLogic)
	{
	case ERROR_LOGIC_ABS:
		pErrorEx->m_strMode = _T("abs");
		break;
	case ERROR_LOGIC_REL:
		pErrorEx->m_strMode = _T("real");
		break;
	case ERROR_LOGIC_OR:
		pErrorEx->m_strMode = _T("or");
		break;
	case ERROR_LOGIC_AND:
		pErrorEx->m_strMode = _T("and");
		break;
	default:
		pErrorEx->m_strMode = _T("or");
	}

	CXExprValue* pValue = pErrorEx->GetExprValue();
	pValue->m_strType = _T("report");
	pValue->m_strValueID = _T("TripValue");  //动作值的报告数据

	if (nVarIndexType == SequenceGradient_VarIndexType_I)
	{
		pValue->m_strValueName = g_sLangTxt_I_Act/*_T("电流动作值(A)")*/; 
	}
	else if (nVarIndexType == SequenceGradient_VarIndexType_U)
	{
		pValue->m_strValueName = g_sLangTxt_U_Act/*_T("电压动作值(V)")*/; 
	}

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalRelMax = NULL;
	CXExprCal *pCalRelMin = NULL;
	CXExprCal *pCalAbsMax = NULL;
	CXExprCal *pCalAbsMin = NULL;

	if (pErrorEx->m_strMode == _T("real"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");
	}
	else if (pErrorEx->m_strMode == _T("abs"))
	{
		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
	}
	else if (pErrorEx->m_strMode == _T("or") || pErrorEx->m_strMode == _T("and"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");

		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
	}

	//电流动作值递变
	if (nVarIndexType == SequenceGradient_VarIndexType_I)
	{
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_I_AbsErr_Max/*_T("电流动作值绝对误差最大值(A)")*/;
		}

		if (pCalRelMax != NULL)
		{
			pCalRelMax->m_strValueName = g_sLangTxt_I_RelErr_Max/*_T("电流动作值相对误差最大值(%)")*/;
		}

		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_I_AbsErr_Min/*_T("电流动作值绝对误差最小值(A)")*/;
		}

		if (pCalRelMin != NULL)
		{
			pCalRelMin->m_strValueName = g_sLangTxt_I_RelErr_Min/*_T("电流动作值相对误差最小值(%)")*/;
		}
	}
	//电压动作值递变
	else if (nVarIndexType == SequenceGradient_VarIndexType_U)
	{
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_U_AbsErr_Max/*_T("电压动作值绝对误差最大值(V)")*/;
		}

		if (pCalRelMax != NULL)
		{
			pCalRelMax->m_strValueName = g_sLangTxt_U_RelErr_Max/*_T("电压动作值相对误差最大值(%)")*/;
		}

		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_U_AbsErr_Min/*_T("电压动作值绝对误差最小值(V)")*/;
		}

		if (pCalRelMin != NULL)
		{
			pCalRelMin->m_strValueName = g_sLangTxt_U_RelErr_Min/*_T("电压动作值相对误差最小值(%)")*/;
		}
	}
}

//递变-线电压
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_LineVolGradientTest(CMacroTest *pMacroTest)
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();//new CItemRsltExprRun;
	pRsltExprRun->DeleteAll();
	long nVarIndexType = 0;
	CDvmData *pVarIndexType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarIndexType"));

	ASSERT(pVarIndexType != NULL );

	if (pVarIndexType == NULL)
	{
		return;
	}

	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);

	//动作值
	CXExprErrorEx *pErrorEx = new CXExprErrorEx;
	pRsltExprRun->AddNewChild(pErrorEx);
	pErrorEx->m_strOptr = _T("<");
	CXExprValueStd* pValueStd = pErrorEx->GetExprValueStd();
	pValueStd->m_strType = _T("report");  
	pValueStd->m_strValueID = _T("ActSet");
	long nErrorLogic = 0;
	CDvmData *pRelErr = NULL;
	CDvmData *pAbsErr = NULL;

	CXExprValueErrorAbs* pValueErrAbs = pErrorEx->GetExprValueErrorAbs();
	pValueErrAbs->m_strType = _T("number");

	CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
	pAbsErrValue->m_strType = _T("report");


	if (nVarIndexType == LineVolGradient_VarIndexType_I)
	{	
		CDvmData *pISet = (CDvmData *)m_pUIParasGroup->FindByID(_T("ISet"));  //电流整定动作值
		pValueStd->m_strValue = pISet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_ISet/*_T("电流整定动作值(A)")*/;
		CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_ErrorLogic"));  //电流动作值误差判断逻辑

		if (pErrorLogic != NULL)
		{
			nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
		}

		CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrRel->m_strType = _T("number");
		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_RelErr"));  //电流动作值相对误差限
		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_AbsErr"));  //电流动作值绝对误差限

		pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pRelErrValue->m_strValueName = g_sLangTxt_I_RelErr/*_T("电流动作值相对误差值(%)")*/;
		pAbsErrValue->m_strValueName = g_sLangTxt_I_AbsErr/*_T("电流动作值绝对误差值(A)")*/;

		pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
		pValueErrRel->m_strValueName = g_sLangTxt_I_ErrRel/*_T("电流动作值相对误差限(%)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_I_ErrAbs/*_T("电流动作值绝对误差限(A)")*/;
	}
	else if (nVarIndexType == LineVolGradient_VarIndexType_U)
	{
		CDvmData *pUSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("USet"));  //电压整定动作值
		pValueStd->m_strValue = pUSet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_USet/*_T("电压整定动作值(V)")*/;

		CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_ErrorLogic"));  //电压动作值误差判断逻辑

		if (pErrorLogic != NULL)
		{
			nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
		}

		CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrRel->m_strType = _T("number");
		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_RelErr"));  //电压动作值相对误差限
		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_AbsErr"));  //电压动作值绝对误差限

		pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pRelErrValue->m_strValueName = g_sLangTxt_U_RelErr/*_T("电压动作值相对误差值(%)")*/;
		pAbsErrValue->m_strValueName = g_sLangTxt_U_AbsErr/*_T("电压动作值绝对误差值(V)")*/;

		pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
		pValueErrRel->m_strValueName = g_sLangTxt_U_ErrRel/*_T("电压动作值相对误差限(%)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_U_ErrAbs/*_T("电压动作值绝对误差限(V)")*/;
	}

	switch(nErrorLogic)
	{
	case ERROR_LOGIC_ABS:
		pErrorEx->m_strMode = _T("abs");
		break;
	case ERROR_LOGIC_REL:
		pErrorEx->m_strMode = _T("real");
		break;
	case ERROR_LOGIC_OR:
		pErrorEx->m_strMode = _T("or");
		break;
	case ERROR_LOGIC_AND:
		pErrorEx->m_strMode = _T("and");
		break;
	default:
		pErrorEx->m_strMode = _T("or");
	}

	CXExprValue* pValue = pErrorEx->GetExprValue();
	pValue->m_strType = _T("report");
	pValue->m_strValueID = _T("TripValue");  //动作值的报告数据

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalRelMax = NULL;
	CXExprCal *pCalRelMin = NULL;
	CXExprCal *pCalAbsMax = NULL;
	CXExprCal *pCalAbsMin = NULL;

	if (pErrorEx->m_strMode == _T("real"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");
	}
	else if (pErrorEx->m_strMode == _T("abs"))
	{
		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
	}
	else if (pErrorEx->m_strMode == _T("or") || pErrorEx->m_strMode == _T("and"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");

		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
	}

	//电流动作值递变
	if (nVarIndexType == LineVolGradient_VarIndexType_I)
	{
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_I_AbsErr_Max/*_T("电流动作值绝对误差最大值(A)")*/;
		}

		if (pCalRelMax != NULL)
		{
			pCalRelMax->m_strValueName = g_sLangTxt_I_RelErr_Max/* _T("电流动作值相对误差最大值(%)")*/;
		}

		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_I_AbsErr_Min/*_T("电流动作值绝对误差最小值(A)")*/;
		}

		if (pCalRelMin != NULL)
		{
			pCalRelMin->m_strValueName = g_sLangTxt_I_RelErr_Min/*_T("电流动作值相对误差最小值(%)")*/;
		}
	}
	//电压动作值递变
	else if (nVarIndexType == LineVolGradient_VarIndexType_U)
	{
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_U_AbsErr_Max/*_T("电压动作值绝对误差最大值(V)")*/;
		}

		if (pCalRelMax != NULL)
		{
			pCalRelMax->m_strValueName = g_sLangTxt_U_RelErr_Max/*_T("电压动作值相对误差最大值(%)")*/;
		}

		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_U_AbsErr_Min/*_T("电压动作值绝对误差最小值(V)")*/;
		}

		if (pCalRelMin != NULL)
		{
			pCalRelMin->m_strValueName = g_sLangTxt_U_RelErr_Min/*_T("电压动作值相对误差最小值(%)")*/;
		}
	}
}

//通用试验-线电压
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr_LineVoltManualTest(CMacroTest *pMacroTest)  
{
	CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();
	pRsltExprRun->DeleteAll();
	long nVarIndexType = 0;
	long nAuto = 0;
	CDvmData *pVarIndexType = (CDvmData *)m_pUIParasGroup->FindByID(_T("VarIndexType"));
	CDvmData *pAuto=(CDvmData*)m_pUIParasGroup->FindByID(_T("_bAuto"));

	ASSERT(pVarIndexType != NULL  && pAuto != NULL);

	if (pVarIndexType == NULL || pAuto == NULL)
	{
		return;
	}

	nVarIndexType = CString_To_long(pVarIndexType->m_strValue);
	nAuto = CString_To_long(pAuto->m_strValue);

	//动作时间
	ActionTimeValue(pRsltExprRun);

	if (!nAuto)
	{
		return;
	}

	CXExprErrorEx *pErrorEx = new CXExprErrorEx;
	pRsltExprRun->AddNewChild(pErrorEx);
	pErrorEx->m_strOptr = _T("<");
	CXExprValueStd* pValueStd = pErrorEx->GetExprValueStd();
	pValueStd->m_strType = _T("report");   //回填报告中去
	pValueStd->m_strValueID = _T("ActSet");  //动作值的报告数据
	long nErrorLogic = 0;
	CDvmData *pRelErr = NULL;
	CDvmData *pAbsErr = NULL;

	CXExprValueErrorAbs* pValueErrAbs = pErrorEx->GetExprValueErrorAbs();
	pValueErrAbs->m_strType = _T("number");

	CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
	pAbsErrValue->m_strType = _T("report");


	if(nVarIndexType == LineVoltManual_VarIndexType_U) //电压递变
	{
		CDvmData *pUSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("USet"));  //电压整定动作值
		pValueStd->m_strValue = pUSet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_USet/*_T("电压整定动作值(V)")*/;

		CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_ErrorLogic"));  //电压动作值误差判断逻辑

		if (pErrorLogic != NULL)
		{
			nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
		}

		CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrRel->m_strType = _T("number");
		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_RelErr"));  //电压动作值相对误差限
		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_AbsErr"));  //电压动作值绝对误差限

		pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pRelErrValue->m_strValueName = g_sLangTxt_U_RelErr/*_T("电压动作值相对误差值(%)")*/;
		pAbsErrValue->m_strValueName = g_sLangTxt_U_AbsErr/*_T("电压动作值绝对误差值(V)")*/;

		pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
		pValueErrRel->m_strValueName = g_sLangTxt_U_ErrRel/*_T("电压动作值相对误差限(%)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_U_ErrAbs/*_T("电压动作值绝对误差限(V)")*/;
	}
	else //电流递变
	{
		CDvmData *pISet = (CDvmData *)m_pUIParasGroup->FindByID(_T("ISet"));  //电流整定动作值
		pValueStd->m_strValue = pISet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_ISet/*_T("电流整定动作值(A)")*/;
		CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_ErrorLogic"));  //电流动作值误差判断逻辑

		if (pErrorLogic != NULL)
		{
			nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
		}

		CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
		pValueErrRel->m_strType = _T("number");
		CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
		pRelErrValue->m_strType = _T("report");
		pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_RelErr"));  //电流动作值相对误差限
		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_AbsErr"));  //电流动作值绝对误差限

		pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pRelErrValue->m_strValueName = g_sLangTxt_I_RelErr/*_T("电流动作值相对误差值(%)")*/;
		pAbsErrValue->m_strValueName = g_sLangTxt_I_AbsErr/*_T("电流动作值绝对误差值(A)")*/;

		pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
		pValueErrRel->m_strValueName = g_sLangTxt_I_ErrRel/*_T("电流动作值相对误差限(%)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_I_ErrAbs/*_T("电流动作值绝对误差限(A)")*/;
	}

	switch(nErrorLogic)
	{
	case ERROR_LOGIC_ABS:
		pErrorEx->m_strMode = _T("abs");
		break;
	case ERROR_LOGIC_REL:
		pErrorEx->m_strMode = _T("real");
		break;
	case ERROR_LOGIC_OR:
		pErrorEx->m_strMode = _T("or");
		break;
	case ERROR_LOGIC_AND:
		pErrorEx->m_strMode = _T("and");
		break;
	default:
		pErrorEx->m_strMode = _T("or");
	}

	CXExprValue* pValue = pErrorEx->GetExprValue();
	pValue->m_strType = _T("report");
	pValue->m_strValueID = _T("ActValue");  //动作值的报告数据

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalRelMax = NULL;
	CXExprCal *pCalRelMin = NULL;
	CXExprCal *pCalAbsMax = NULL;
	CXExprCal *pCalAbsMin = NULL;

	if (pErrorEx->m_strMode == _T("real"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");//相对误差最大值

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");//相对误差最小值
	}
	else if (pErrorEx->m_strMode == _T("abs"))
	{
		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");//绝对误差最大值

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");//绝对误差最小值
	}
	else if (pErrorEx->m_strMode == _T("or") || pErrorEx->m_strMode == _T("and"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");

		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
	}

	if (nVarIndexType == LineVoltManual_VarIndexType_U)//电压动作值递变
	{
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_U_AbsErr_Max/*_T("电压动作值绝对误差最大值(V)")*/;
		}
		if (pCalRelMax != NULL)
		{
			pCalRelMax->m_strValueName = g_sLangTxt_U_RelErr_Max/*_T("电压动作值相对误差最大值(%)")*/;
		}
		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_U_AbsErr_Min/* _T("电压动作值绝对误差最小值(V)")*/;
		}
		if (pCalRelMin != NULL)
		{
			pCalRelMin->m_strValueName = g_sLangTxt_U_RelErr_Min/*_T("电压动作值相对误差最小值(%)")*/;
		}
	}

	if (nVarIndexType == LineVoltManual_VarIndexType_I)//电流动作值递变
	{
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_I_AbsErr_Max/*_T("电流动作值绝对误差最大值(A)")*/;
		}
		if (pCalRelMax != NULL)
		{
			pCalRelMax->m_strValueName = g_sLangTxt_I_RelErr_Max/*_T("电流动作值相对误差最大值(%)")*/;
		}
		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_I_AbsErr_Min/*_T("电流动作值绝对误差最小值(A)")*/;
		}
		if (pCalRelMin != NULL)
		{
			pCalRelMin->m_strValueName = g_sLangTxt_I_RelErr_Min/* _T("电流动作值相对误差最小值(%)")*/;
		}
	}
}

//处理特性曲线项目的结果判断
void CGbItemsGenTool::GenGbItemBase_MacroTest_RsltExpr(CMacroCharItems *pMacroCharItems, CItemGenRsltExpr* pRsltExprGen, CExBaseList *pInterface)
{
	if (pRsltExprGen == NULL)
	{
		return;
	}

	CExBaseList listMacroTest;
	pMacroCharItems->GetAllMacroTestItemsEx(&listMacroTest);

	POS pos = listMacroTest.GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)listMacroTest.GetNext(pos);
		CItemRsltExprRun *pRsltExprRun = pMacroTest->GetRsltExpr();
		pRsltExprRun->DeleteAll();

		InitRsltExpr(pRsltExprRun, pInterface, pRsltExprGen, NULL);
	}

	listMacroTest.RemoveAll();
}

//处理通用的结果判断，根据数据接口 + 模板配置规则，生成结果判断节点
void CGbItemsGenTool::InitRsltExpr(CItemRsltExprRun *pRsltExprRun, CExBaseList *pInterface, CItemGenRsltExpr* pExprNode, CExBaseList *pParasMap)
{
	POS pos = pExprNode->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pExprNode->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRNODE)
		{
			CXExprNode *pNode = (CXExprNode *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pNode, pParasMap);
		}
		else if(nClassID == XEXPRCLASSID_CXEXPRCMP)
		{
			CXExprCmp *pExprCmp = (CXExprCmp *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprCmp, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERROR)
		{
			CXExprError *pExprError = (CXExprError *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprError, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERROREX)
		{
			CXExprErrorEx *pExprErrorEx = (CXExprErrorEx *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprErrorEx, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRRANGE)
		{
			CXExprRange *pExprRange = (CXExprRange *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprRange, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRRANGEEX)
		{
			CXExprRangeEx *pExprRangeEx = (CXExprRangeEx *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprRangeEx, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECAL)
		{
			CXExprValueCal *pExprValueCal = (CXExprValueCal *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprValueCal, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALEX)
		{
			CXExprValueCalEx *pExprValueCalEx = (CXExprValueCalEx *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprValueCalEx, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED)
		{
			CXExprErrorCombined *pExprErrorCombined = (CXExprErrorCombined *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pExprErrorCombined, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRCAL)
		{
			CXExprCal *pXExprCal = (CXExprCal *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pXExprCal, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRCALSRPT)
		{
			CXExprCalSRpt *pXExprCalSRpt = (CXExprCalSRpt *)pObj;
			InitRsltExpr_Ex(pRsltExprRun, pInterface, pXExprCalSRpt, pParasMap);
		}
	}
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprNode* pExprNode, CExBaseList *pParasMap)
{
	CXExprNode *pNewNode = (CXExprNode *)pExprNode->Clone();
	pParent->AddNewChild(pNewNode);
	Expr_Use_SetByMap(pNewNode, pInterface);

	POS pos = pExprNode->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pExprNode->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRNODE)
		{
			CXExprNode *pNode = (CXExprNode *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pNode, pParasMap);
		}
		else if(nClassID == XEXPRCLASSID_CXEXPRCMP)
		{
			CXExprCmp *pExprCmp = (CXExprCmp *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprCmp, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERROR)
		{
			CXExprError *pExprError = (CXExprError *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprError, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERROREX)
		{
			CXExprErrorEx *pExprErrorEx = (CXExprErrorEx *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprErrorEx, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRRANGE)
		{
			CXExprRange *pExprRange = (CXExprRange *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprRange, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECAL)
		{
			CXExprValueCal *pExprValueCal = (CXExprValueCal *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprValueCal, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALEX)
		{
			CXExprValueCalEx *pExprValueCalEx = (CXExprValueCalEx *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprValueCalEx, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED)
		{
			CXExprErrorCombined *pExprErrorCombined = (CXExprErrorCombined *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pExprErrorCombined, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRCAL)
		{
			CXExprCal *pXExprCal = (CXExprCal *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pXExprCal, pParasMap);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRCALSRPT)
		{
			CXExprCalSRpt *pXExprCalSRpt = (CXExprCalSRpt *)pObj;
			InitRsltExpr_Ex(pNewNode, pInterface, pXExprCalSRpt, pParasMap);
		}
	}
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCmp* pExprCmp, CExBaseList *pParasMap)
{
	CXExprCmp *pNewCmp = (CXExprCmp *)pExprCmp->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewCmp);
	Expr_Use_SetByMap(pNewCmp, pInterface);
	CXExprValue1 *pValue1 = pNewCmp->GetExprValue1();
	CXExprValue2 *pValue2 = pNewCmp->GetExprValue2();

	InitRsltExpr_Value(pInterface, pValue1, pParasMap);
	InitRsltExpr_Value(pInterface, pValue2, pParasMap);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprError* pExprError, CExBaseList *pParasMap)
{
	CXExprError *pNewError = (CXExprError *)pExprError->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewError);
	Expr_Use_SetByMap(pNewError, pInterface);
	CXExprValue* pExprValue = pNewError->GetExprValue();
	CXExprValueStd* pExprValueStd = pNewError->GetExprValueStd();
	CXExprValueError* pExprValueError = pNewError->GetExprValueError();

	InitRsltExpr_Value(pInterface, pExprValue, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueStd, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueError, pParasMap);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprErrorEx* pExprErrorEx, CExBaseList *pParasMap)
{
	CXExprErrorEx *pNewErrorEx = (CXExprErrorEx *)pExprErrorEx->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewErrorEx);
	Expr_Use_SetByMap(pNewErrorEx, pInterface);
	CXExprValue* pExprValue = pNewErrorEx->GetExprValue();
	CXExprValueStd* pExprValueStd = pNewErrorEx->GetExprValueStd();
	CXExprValueErrorRel* pExprValueErrorRel = pNewErrorEx->GetExprValueErrorRel();
	CXExprValueErrorAbs* pExprValueErrorAbs = pNewErrorEx->GetExprValueErrorAbs();

	InitRsltExpr_Value(pInterface, pExprValue, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueStd, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueErrorRel, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueErrorAbs, pParasMap);

	Expr_Mode_SetByMap(pInterface, pNewErrorEx->m_strMode);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprRange* pExprRange, CExBaseList *pParasMap)
{
	CXExprRange *pNewRange = (CXExprRange *)pExprRange->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewRange);
	Expr_Use_SetByMap(pNewRange, pInterface);
	CXExprValue *pValue = pNewRange->GetExprValue();
	CXExprValueMin *pValueMin = pNewRange->GetExprValueMin();
	CXExprValueMax *pValueMax = pNewRange->GetExprValueMax();

	InitRsltExpr_Value(pInterface, pValue, pParasMap);
	InitRsltExpr_Value(pInterface, pValueMin, pParasMap);
	InitRsltExpr_Value(pInterface, pValueMax, pParasMap);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprRangeEx* pExprRangeEx, CExBaseList *pParasMap)
{
	CXExprRangeEx *pNewRangeEx = (CXExprRangeEx *)pExprRangeEx->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewRangeEx);
	Expr_Use_SetByMap(pNewRangeEx, pInterface);
	CXExprValue1 *pValue1 = pNewRangeEx->GetExprValue1();
	CXExprValue2 *pValue2 = pNewRangeEx->GetExprValue2();
	CXExprValueMin *pValueMin = pNewRangeEx->GetExprValueMin();
	CXExprValueMax *pValueMax = pNewRangeEx->GetExprValueMax();

	InitRsltExpr_Value(pInterface, pValue1, pParasMap);
	InitRsltExpr_Value(pInterface, pValue2, pParasMap);
	InitRsltExpr_Value(pInterface, pValueMin, pParasMap);
	InitRsltExpr_Value(pInterface, pValueMax, pParasMap);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprValueCal* pExprValueCal, CExBaseList *pParasMap)
{
	CXExprValueCal *pNewValueCal = (CXExprValueCal *)pExprValueCal->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewValueCal);
	Expr_Use_SetByMap(pNewValueCal, pInterface);
	CXExprValue1 *pValue1 = pNewValueCal->GetExprValue1();
	CXExprValue2 *pValue2 = pNewValueCal->GetExprValue2();
	CXExprValueStd* pExprValueStd = pNewValueCal->GetExprValueStd();
	CXExprValueError* pExprValueError = pNewValueCal->GetExprValueError();

	InitRsltExpr_Value(pInterface, pValue1, pParasMap);
	InitRsltExpr_Value(pInterface, pValue2, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueStd, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueError, pParasMap);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprValueCalEx* pExprValueCalEx, CExBaseList *pParasMap)
{
	CXExprValueCalEx *pNewValueCalEx = (CXExprValueCalEx *)pExprValueCalEx->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewValueCalEx);
	Expr_Use_SetByMap(pNewValueCalEx, pInterface);
	CXExprValue1 *pValue1 = pNewValueCalEx->GetExprValue1();
	CXExprValue2 *pValue2 = pNewValueCalEx->GetExprValue2();
	CXExprValueStd* pExprValueStd = pNewValueCalEx->GetExprValueStd();
	CXExprValueErrorRel* pExprValueErrorRel = pNewValueCalEx->GetExprValueErrorRel();
	CXExprValueErrorAbs* pExprValueErrorAbs = pNewValueCalEx->GetExprValueErrorAbs();

	InitRsltExpr_Value(pInterface, pValue1, pParasMap);
	InitRsltExpr_Value(pInterface, pValue2, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueStd, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueErrorRel, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueErrorAbs, pParasMap);

	Expr_Mode_SetByMap(pInterface, pExprValueCalEx->m_strMode);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprErrorCombined* pExprErrorCombined, CExBaseList *pParasMap)
{
	CXExprErrorCombined *pNewErrorCombined = (CXExprErrorCombined *)pExprErrorCombined->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewErrorCombined);
	Expr_Use_SetByMap(pNewErrorCombined, pInterface);
	CXExprValue* pExprValue = pNewErrorCombined->GetExprValue();
	CXExprValueStd* pExprValueStd = pNewErrorCombined->GetExprValueStd();
	CXExprValueErrorRel* pExprValueErrorRel = pNewErrorCombined->GetExprValueErrorRel();
	CXExprValueErrorAbs* pExprValueErrorAbs = pNewErrorCombined->GetExprValueErrorAbs();

	InitRsltExpr_Value(pInterface, pExprValue, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueStd, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueErrorRel, pParasMap);
	InitRsltExpr_Value(pInterface, pExprValueErrorAbs, pParasMap);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCal* pXExprCal, CExBaseList *pParasMap)
{
	CXExprCal *pNewExprCal = (CXExprCal *)pXExprCal->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewExprCal);
}

void CGbItemsGenTool::InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCalSRpt* pXExprCalSRpt, CExBaseList *pParasMap)
{
	CXExprCalSRpt *pNewExprCal = (CXExprCalSRpt *)pXExprCalSRpt->CloneEx(TRUE, TRUE);
	pParent->AddNewChild(pNewExprCal);
}

void CGbItemsGenTool::InitRsltExpr_Value(CExBaseList *pInterface, CXExprValue *pExprValue, CExBaseList *pParasMap)
{
	if (pInterface == NULL)
	{
		return;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	if (pExprValue->m_strType == _T("number")
		||pExprValue->m_strType == _T("report")	)
	{
		//对于需要绑定界面参数的，value-id属性填的是映射参数的ID
		pObj = pInterface->FindByID(pExprValue->m_strValueID);

		if (pObj == NULL)
		{
			//处理pExprValue->m_strValueID是表达式的情况
			InitRsltExpr_Value_Expression(pInterface, pExprValue, pParasMap);
			return;
		}

		nClassID = pObj->GetClassID();
		CString strValue;

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
		{
			CItemsGenData *pData = (CItemsGenData *)pObj;
			strValue = pData->m_strValue;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
		{
			CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pObj;
			strValue = pDataMap->m_strValue;
		}

		if (!IsStringNumber(strValue))
		{
			//说明是绑定的表达式，需要计算表达，该表达式可能绑定的系统参数
			double dValue = 0.0;
			if (!Gb_CalParaExpression(strValue, pDevice, dValue, FALSE))
			{
#ifdef _DEBUG
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("结果评估表达式，表达式计算错误 [%s] ，结果值设置为0.000……"), strValue.GetString());
#endif
			}

			pExprValue->m_strValue.Format(_T("%f"), dValue);
		}
		else
		{
			pExprValue->m_strValue = strValue;
		}

		if (pExprValue->m_strType == _T("number"))
		{
			pExprValue->m_strValueID = _T("");
		}
	}
	else
	{
		//处理value-id
		pObj = pInterface->FindByID(pExprValue->m_strValueID);

		if (pObj == NULL)
		{
			return;
		}

		nClassID = pObj->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
		{
			CItemsGenData *pData = (CItemsGenData *)pObj;
			pExprValue->m_strValueID = pData->m_strValue;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
		{
			CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pObj;
			pExprValue->m_strValueID = pDataMap->m_strValue;
		}
	}
}

//处理pExprValue->m_strValueID是表达式的情况
void CGbItemsGenTool::InitRsltExpr_Value_Expression(CExBaseList *pInterface, CXExprValue *pExprValue, CExBaseList *pParasMap)
{
	if (pExprValue->m_strValueID.IsEmpty())
	{
		return;
	}

	CEpExpression oEpEpr;

	if (oEpEpr.ChangeEpExpression(pExprValue->m_strValueID) == -1)
	{
		return;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = oEpEpr.GetHeadPosition();

	while (pos != NULL)
	{
		CEpExpVariable *pEpVar = (CEpExpVariable *)oEpEpr.GetNext(pos);
		pObj = pInterface->FindByID(pEpVar->m_strVarID);

		if (pObj == NULL)
		{
#ifdef _DEBUG
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("<<<<<<<<<<<<表达式错误<<<<接口参数中找不到id = %s 的参数"), pEpVar->m_strVarID.GetString());
#endif
			return;
		}

		nClassID = pObj->GetClassID();
		CString strValue;

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
		{
			CItemsGenData *pData = (CItemsGenData *)pObj;
			strValue = pData->m_strValue;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
		{
			CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pObj;
			strValue = pDataMap->m_strValue;
		}

		if (!IsStringNumber(strValue))
		{
			//说明是绑定的表达式，需要计算表达，该表达式可能绑定的系统参数
			if (!Gb_CalParaExpression(strValue, pDevice, pEpVar->m_dValue, FALSE))
			{
#ifdef _DEBUG
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("结果评估表达式，表达式计算错误 [%s] ，结果值设置为0.000……"), strValue.GetString());
#endif
				continue;
			}
		}
		else
		{
#ifdef _UNICODE
			pEpVar->m_dValue = _wtof(strValue);
#else
			pEpVar->m_dValue = atof(strValue.GetString());
#endif
		}
	}

	//此处表达式处理，仅将界面参数，根据表达式，计算出值，并将值放到结果评估中。
	double dValue = 0.0;
	oEpEpr.Value(dValue);
	pExprValue->m_strValue.Format(_T("%f"), dValue);

	//待处理：若需要报告回填，参数ID该如何处理？
	pExprValue->m_strValueID = _T("");
}

BOOL CGbItemsGenTool::Expr_Mode_SetByMap(CExBaseList *pInterface, CString &strMode)
{
	if (strMode == _T("abs")
		|| strMode == _T("real")
		|| strMode == _T("or")
		|| strMode == _T("and")
		|| strMode == _T("combined"))
	{
		return TRUE;
	}

	long nErrorLogic = 0;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	pObj = pInterface->FindByID(strMode);

	if (pObj == NULL)
	{
		strMode = _T("or");
		return FALSE;
	}

	nClassID = pObj->GetClassID();

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
	{
		CItemsGenData *pData = (CItemsGenData *)pObj;
		nErrorLogic = CString_To_long(pData->m_strValue);
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pObj;
		nErrorLogic = CString_To_long(pDataMap->m_strValue);
	}

	switch(nErrorLogic)
	{
	case ERROR_LOGIC_ABS:
		strMode = _T("abs");
		break;
	case ERROR_LOGIC_REL:
		strMode = _T("real");
		break;
	case ERROR_LOGIC_OR:
		strMode = _T("or");
		break;
	case ERROR_LOGIC_AND:
		strMode = _T("and");
		break;
	case ERROR_LOGIC_COMB:
		strMode = _T("combined");
		break;
	default:
		strMode = _T("or");
	}

	return TRUE;
}

BOOL CGbItemsGenTool::Expr_Use_SetByMap(CXExprBase *pExprBase, CExBaseList *pInterface)
{
	if (pExprBase->m_strUse == _T("1") || pExprBase->m_strUse == _T("0"))
	{
		return TRUE;
	}

	CDvmData *pData = NULL;
	CItemsGenData *pInterfaceData = NULL;

	if (m_pUIParasGroup != NULL)
	{
		pData = (CDvmData *)m_pUIParasGroup->FindByID(pExprBase->m_strUse);
	}

	if (pData == NULL)
	{
		//pInterface实际可能是ParasMap，例如：GenGuideBook_MacroTest_Single
		CExBaseObject *pObj = pInterface->FindByID(pExprBase->m_strUse);

		if (pObj != NULL)
		{
			UINT nClassID = pObj->GetClassID();
			if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
				pInterfaceData = (CItemsGenData *)pObj;
		}

		//从界面参数查找不到，则动映射接口中查找 2024-12-13
		//pInterfaceData = (CItemsGenData *)pInterface->FindByID(pExprBase->m_strUse);
	}

	if (pData == NULL && pInterfaceData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Expr Set Use Faild, UIParas has no para [%s]"), pExprBase->m_strUse.GetString());
		pExprBase->m_strUse = _T("0");
		pExprBase->m_nIsUse = 0;
		return FALSE;
	}

	CString strValue, strDataType;

	if (pData != NULL)
	{
		strValue = pData->m_strValue;
		strDataType = pData->m_strDataType;
	}
	else
	{
		strValue = pInterfaceData->m_strValue;
		strDataType = pInterfaceData->m_strDataType;
	}

	if (strValue.GetLength() == 0)
	{
		pExprBase->m_strUse = _T("0");
		pExprBase->m_nIsUse = 0;
	}
	else if (IsStringNumber(strValue))
	{
		//pExprBase->m_strUse = strValue;
		pExprBase->m_nIsUse = CString_To_long(strValue);
		pExprBase->m_strUse.Format(_T("%d"), pExprBase->m_nIsUse);
	}
	else if (strValue.GetLength() > 0 && strDataType == _T("string"))
	{
		pExprBase->m_strUse = _T("1");
		pExprBase->m_nIsUse = 1;
	}
	else
	{
		pExprBase->m_strUse = strValue;
		pExprBase->m_nIsUse = CString_To_long(strValue);
	}
	
	return TRUE;
}

//新建通讯命令项目，并返回通讯命令项目
CGbItemBase* CGbItemsGenTool::GenGbItemBase_Define_CommCmd(CGbItemBase *pParentItem, CItemsGenNode *pNode)
{
	CItemsGenCommCmd *pGenCommCmd = pNode->GetItemsGenCommCmd();

	if (pGenCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("生成通信命令项目错误！没有规则文件中没有commcmd节点！"));
		return pParentItem;
	}

	pGenCommCmd->InitDataMapsByInterface();

	CCommCmd *pCommCmd = new CCommCmd;
	pCommCmd->m_strName = pNode->m_strName;
	pCommCmd->m_strID = pNode->m_strID;

	pCommCmd->InitAfterRead();
	pParentItem->AddNewChild(pCommCmd, TRUE);

	InitCommCmdAttr(pGenCommCmd, pCommCmd);
	InitCommCmdParas(pGenCommCmd, pCommCmd);

	if (pParentItem->GetClassID() == GBCLASSID_MACROTEST
		|| pParentItem->GetClassID() == GBCLASSID_SAFETY
		|| pParentItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
	{
		pCommCmd->m_bIsSubItem = TRUE;
		pParentItem->m_oSubGbItems.AddTail(pCommCmd);
	}

 	return pCommCmd;
}

void CGbItemsGenTool::InitCommCmdAttr(CItemsGenCommCmd *pGenCommCmd, CCommCmd *pCommCmd)
{
	if (pGenCommCmd == NULL || pCommCmd == NULL)
	{
		return;
	}

	pCommCmd->m_strCommCmdID = pGenCommCmd->m_strCmdID;
	pCommCmd->m_strRwOptr = pGenCommCmd->m_strRwOptr;
	pCommCmd->m_nFillRptDataset = pGenCommCmd->m_nRptFillDs;
	CCmd *pCmd = pCommCmd->GetCmd();

	POS pos = pGenCommCmd->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CItemsGenDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pObj = pGenCommCmd->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
		{
			continue;
		}

		pDataMap = (CItemsGenDataMap *)pObj;

		if (pDataMap->m_strID == STT_CMD_PARA_DelayBeforeCmd)
		{
			long nDelay = CString_To_long(pDataMap->m_strValue);
			pCmd->m_strDelayBeforeCmd.Format(_T("%d"), nDelay);
		}

		if (pDataMap->m_strID == STT_CMD_PARA_DelayAfterCmd)
		{
			long nDelay = CString_To_long(pDataMap->m_strValue);
			pCmd->m_strDelayAfterCmd.Format(_T("%d"), nDelay);
		}

		if (pDataMap->m_strID == STT_CMD_PARA_RepeatTimes)
		{
			pCmd->m_nRepeatTimes = CString_To_long(pDataMap->m_strValue);
		}

		if (pDataMap->m_strID == STT_CMD_PARA_DatasetPath)
		{
			CDvmDataset *pDataset = m_oDvmDevice.FindDataset(pDataMap->m_strValue);

			if (pDataset == NULL)
			{
				pCmd->m_strDatasetPath = pDataMap->m_strValue;

				//遥测的，因为没映射，肯定找不到数据集。所以不打印
				if (pDataMap->m_strValue != _T("dsAin"))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("通讯命令参数错误，找不到数据集【%s】"), pDataMap->m_strValue.GetString());
				}
			}
			else
			{
				CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
				pCmd->m_strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;
			}
		}
	}	
}

void CGbItemsGenTool::InitCommCmdParas(CItemsGenCommCmd *pGenCommCmd, CCommCmd *pCommCmd)
{
	if (pGenCommCmd == NULL || pCommCmd == NULL)
	{
		return;
	}

	CCmd *pCmd = pCommCmd->GetCmd();
	POS pos = pGenCommCmd->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CItemsGenDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pObj = pGenCommCmd->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBITEMSGENMNGRCLASSID_CITEMSGENDATASET)
		{
			continue;
		}

		pDataset = (CItemsGenDataset *)pObj;
		pCmd->AddValue(pDataset->m_strID, pDataset->m_strValue);
	}
}

//将规则文件中的参数，赋值给模板中曲线的定义
void CGbItemsGenTool::GenGbItem_CharItemLine(CMacroCharItemLineDef *pItemLineDef, CItemsGenCharItemLine *pItemGenLine)
{
	if (pItemGenLine == NULL || pItemLineDef == NULL)
	{
		return;
	}

	pItemLineDef->m_strName = pItemGenLine->m_strName;
	pItemLineDef->m_strID = pItemGenLine->m_strID;

	pItemLineDef->m_strType = pItemGenLine->m_strType;
	pItemLineDef->m_strAxisMode = pItemGenLine->m_strAxisMode;
	pItemLineDef->m_strParaIdXb = pItemGenLine->m_strParaIdXb;
	pItemLineDef->m_strParaIdYb = pItemGenLine->m_strParaIdYb;
	pItemLineDef->m_strParaIdYe = pItemGenLine->m_strParaIdYe;
	pItemLineDef->m_strParaIdXe = pItemGenLine->m_strParaIdXe;
	pItemLineDef->m_strParaIdYset = pItemGenLine->m_strParaIdYset;
	pItemLineDef->m_strParaIdXset = pItemGenLine->m_strParaIdXset;
	pItemLineDef->m_strParaIdXact = pItemGenLine->m_strParaIdXact;
	pItemLineDef->m_strParaIdYact = pItemGenLine->m_strParaIdYact;
	pItemLineDef->m_strParaIdFlagAct = pItemGenLine->m_strParaIdFlagAct;

	pItemLineDef->m_strParaIdSearchXb = pItemGenLine->m_strParaIdSearchXb;
	pItemLineDef->m_strParaIdSearchYb = pItemGenLine->m_strParaIdSearchYb;
	pItemLineDef->m_strParaIdSearchActb = pItemGenLine->m_strParaIdSearchActb;
	pItemLineDef->m_strParaIdSearchXe = pItemGenLine->m_strParaIdSearchXe;
	pItemLineDef->m_strParaIdSearchYe = pItemGenLine->m_strParaIdSearchYe;
	pItemLineDef->m_strParaIdSearchActe = pItemGenLine->m_strParaIdSearchActe;
	pItemLineDef->m_strParaIdSearchXc = pItemGenLine->m_strParaIdSearchXc;
	pItemLineDef->m_strParaIdSearchYc = pItemGenLine->m_strParaIdSearchYc;
}

void CGbItemsGenTool::GenGbCommCmd_After(CGbItemBase *pParentItem)
{
	if (pParentItem == NULL || m_pCommCmd == NULL)
	{
		return;
	}

	CItems *pItems = IsHasDevReset();

	//装置复归态不为空，则用装置复归态，代替测试后恢复
	if (pItems != NULL)
	{
		CItems *pNewItems = (CItems *)pItems->CloneEx(TRUE, TRUE);
		pNewItems->m_strName = STT_ITEMS_Name_COMM_AFT;
		pNewItems->m_strID = STT_ITEMS_ID_AFTERTEST;
		pParentItem->AddNewChild(pNewItems);
		return;
	}

	CDataGroup *pAfterTest = (CDataGroup *)m_pCommCmd->FindByID(STT_CMD_PARA_After_Test);

	if (pAfterTest == NULL)
	{
		return;
	}

	if (pAfterTest->GetCount() == 0)
	{
		return;
	}

	CItems *pAFT = (CItems *)pParentItem->FindByID(STT_ITEMS_ID_AFTERTEST);

	if (pAFT == NULL)
	{
		pAFT = new CItems;
		pAFT->m_strName = STT_ITEMS_Name_COMM_AFT;
		pAFT->m_strID = STT_ITEMS_ID_AFTERTEST;
		pParentItem->AddNewChild(pAFT);
		pAFT->InitAfterRead();
	}

	GenGbCommCmd(pAFT, pAfterTest);
}

void CGbItemsGenTool::GenGbCommCmd_Before(CGbItemBase *pParentItem)
{
	if (pParentItem == NULL || m_pCommCmd == NULL)
	{
		return;
	}

	CDataGroup *pBeforeTest = (CDataGroup *)m_pCommCmd->FindByID(STT_CMD_PARA_Before_Test);

	if (pBeforeTest == NULL)
	{
		return;
	}

	if (pBeforeTest->GetCount() == 0)
	{
		return;
	}

	//有测试前准备，则不创建新的CItems
	if (pParentItem->m_strID == STT_ITEMS_ID_BEFORETEST)
	{
		GenGbCommCmd(pParentItem, pBeforeTest);
		return;
	}

	CItems *pBFT = (CItems *)pParentItem->FindByID(STT_ITEMS_ID_BEFORETEST);

	if (pBFT == NULL)
	{
		pBFT = new CItems;
		pBFT->m_strName = STT_ITEMS_Name_COMM_BFT;
		pBFT->m_strID = STT_ITEMS_ID_BEFORETEST;
		pParentItem->AddNewChild(pBFT);
		pBFT->InitAfterRead();
	}

	GenGbCommCmd(pBFT, pBeforeTest);
}

/*
<group id="_BeforeTest_" name="通信前准备">
	<group id="ReadSetting" data-type="read" value="">
		<group id="PT2201APROT$LLN0$dsSetting1" data-type="string"/>
		<group id="PT2201APROT$LLN0$dsSetting2" data-type="string"/>
		<!--读指令，每个子group都对应一个数据集，ID = 数据集路径-->
	</group>

	<group id="WriteSetting" name="修改定值">
		<group name="" id="PROT$LLN0$dsSetting1" data-type="" >
			<data name="" id="" data-type="" value=""/>
			...............................
		</group>
	</group>
	<group id="WriteSetting" name="修改定值">
		<group name="" id="PROT$LLN0$dsSetting2" data-type="" >
			<data name="" id="" data-type="" value=""/>
			...............................
		</group>
	</group>
	<!--写指令，每个数据集都对应一个大的group，有一个ID为数据集路径的子group，该子group携带data-->

	<group id="RegisterReport" name="启动报告">  
		<group name="" id="PROT$LLN0$dsTripInfo" data-type="" />
		...............................
	</group>
	<!--register命令：与读命令结构一致；-->
</group>
*/
//形参pGroup为_BeforeTest_或_AfterTest_
void CGbItemsGenTool::GenGbCommCmd(CGbItemBase *pParentItem, CDataGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CDataGroup *pCmdGroup = NULL;

	while (pos != NULL)
	{
		pCmdGroup = (CDataGroup *)pGroup->GetNext(pos);
		GenGbCommCmd_Ex(pParentItem, pCmdGroup);   //按照数据结构，pCmdGroup的子对象，只有CDataGroup

// 		if (pCmdGroup->GetChildCount(DTMCLASSID_CDATAGROUP) > 0)
// 		{
// 			//表示一个指令，需要修改多个数据集的数据；每个数据集都应当生成一个项目；
// 			GenGbCommCmd_Ex(pParentItem, pCmdGroup);
// 			continue;
// 		}

// 		//没有子对象group，说明有ds-path的data节点，且该指令不携带通讯参数
// 		CString strDsPath, strDsID;
// 		BOOL bFind = pCmdGroup->GetDataValue(STT_CMD_PARA_DS_PATH, strDsPath);
// 
// 		if (!bFind)
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("通讯命令生成，通讯命令【%s】没有携带数据集路径参数"), pCmdGroup->m_strID.GetString());
// 		}
// 
// 		long nPos = strDsPath.ReverseFind('$');
// 
// 		if (nPos > 0)
// 		{
// 			strDsID = strDsPath.Mid(nPos + 1);
// 		}
// 		else
// 		{
// 			strDsID = strDsPath;
// 		}
// 
// 		CCommCmd *pCommCmd = new CCommCmd;
// 		pCommCmd->m_strID.Format(_T("%s_%s"), pCmdGroup->m_strID.GetString(), strDsID.GetString());
// 		pCommCmd->m_strName.Format(_T("%s_%s"), pCmdGroup->m_strName.GetString(), strDsID.GetString());
// 		pCommCmd->m_strCommCmdID = pCmdGroup->m_strID;
// 
// 		if (GetCommCmdRwOptr(pCmdGroup->m_strID, pCommCmd->m_strRwOptr))
// 		{
// 		}
// 		else
// 		{
// 			pCommCmd->m_strRwOptr = pCmdGroup->m_strValue;   //read、write、none、register。暂停从m_strValue获取
// 		}
// 		
// 		pCommCmd->InitAfterRead();
// 		pParentItem->AddNewChild(pCommCmd);
// 		CCmd *pCmd = pCommCmd->GetCmd();
// 		pCmd->m_strDatasetPath = strDsPath;
	}
}

//返回最新创建的通讯命令项目
CGbItemBase* CGbItemsGenTool::GenGbCommCmd_Ex(CGbItemBase *pParentItem, CDataGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDataGroup *pCmdGroup = NULL;
	CCommCmd *pCommCmd = NULL;

	if (pos == NULL)
	{
		//如果没有子对象，则说明是新建单个通讯命令。新建时不带参数，而是新建后通过UpdateItem进行参数更新
		pCommCmd = GenGbCommCmd_NewCmd(pGroup);
		pParentItem->AddNewChild(pCommCmd, TRUE);

		if (pParentItem->GetClassID() == GBCLASSID_MACROTEST
			|| pParentItem->GetClassID() == GBCLASSID_SAFETY
			|| pParentItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
		{
			pCommCmd->m_bIsSubItem = TRUE;
			pParentItem->m_oSubGbItems.AddTail(pCommCmd);
		}

		//判断是否是RegisterReport
		return pCommCmd;
	}

	while (pos != NULL)
	{
		pObj = pGroup->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pCmdGroup = (CDataGroup *)pObj; //pGroup下，每一个子Group，都要生成一个通讯命令项目

		pCommCmd = GenGbCommCmd_NewCmd(pGroup);
		pParentItem->AddNewChild(pCommCmd, TRUE);//第二个参数传TRUE，会根据name、id，对其重新整理

		if (pParentItem->GetClassID() == GBCLASSID_MACROTEST
			|| pParentItem->GetClassID() == GBCLASSID_SAFETY
			|| pParentItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
		{
			pCommCmd->m_bIsSubItem = TRUE;
			pParentItem->m_oSubGbItems.AddTail(pCommCmd);
		}

		CCmd *pCmd = pCommCmd->GetCmd();
		pCmd->m_strDatasetPath = pCmdGroup->m_strID;

		POS posData = pCmdGroup->GetHeadPosition();
		CDvmData *pData = NULL;

		while (posData != NULL)
		{
			pData = (CDvmData *)pCmdGroup->GetNext(posData);
			pCmd->AddValue(pData->m_strID, pData->m_strValue);
		}

		if (pGroup->m_strID == _T("WriteSetting") || pGroup->m_strID == _T("ReadSetting"))
		{
			CDvmData *pZoneIndex = (CDvmData *)pGroup->FindByID(STT_CMD_PARA_ZoneIndex);

			if (pZoneIndex != NULL)
			{
				pCmd->m_nZoneIndex = CString_To_long(pZoneIndex->m_strValue);
			}
		}

		CDvmData *pDelay = (CDvmData *)pGroup->FindByID(STT_CMD_PARA_DelayBeforeCmd);
		long nDelay = 0;

		if (pDelay != NULL)
		{
			nDelay = CString_To_long(pDelay->m_strValue);
			pCmd->m_strDelayBeforeCmd.Format(_T("%d"), nDelay);
			//pCmd->m_strDelayBeforeCmd = ;
		}

		pDelay = (CDvmData *)pGroup->FindByID(STT_CMD_PARA_DelayAfterCmd);

		if (pDelay != NULL)
		{
			nDelay = CString_To_long(pDelay->m_strValue);
			pCmd->m_strDelayAfterCmd.Format(_T("%d"), nDelay);
			//pCmd->m_strDelayAfterCmd = pDelay->m_strValue;
		}
	}

	return pCommCmd;
}

//精度测试模式下，电气量项目，添加固定的读遥测指令
void CGbItemsGenTool::GenGbCommCmd_ReadAin(CGbItemBase *pParentItem)
{
	CString strDatasetPath = _T("LLN0$dsRelayAin");
	CDvmDataset *pDataset = m_oDvmDevice.FindDataset(strDatasetPath);

	if (pDataset != NULL)
	{
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice *)pDataset->GetParent();
		strDatasetPath = pLogicDevice->m_strID + _T("$");
		strDatasetPath += pDataset->m_strID;
	}

	CCommCmd *pCommCmd = new CCommCmd;
	pCommCmd->m_strID = _T("ReadAin");
	pCommCmd->m_strName = g_sLangTxt_ReadAin/*_T("读遥测")*/;
	//pCommCmd->m_nFillRptDataset = 1;
	pCommCmd->InitAfterRead();
	pParentItem->AddNewChild(pCommCmd);
	CCmd *pCmd = pCommCmd->GetCmd();
	pCmd->m_strDatasetPath = strDatasetPath;
	pCommCmd->m_strCommCmdID = _T("ReadAin");
	pCommCmd->m_strRwOptr = _T("read");

	if (pParentItem->GetClassID() == GBCLASSID_MACROTEST
		|| pParentItem->GetClassID() == GBCLASSID_SAFETY
		|| pParentItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
	{
		pCommCmd->m_bIsSubItem = TRUE;
		pParentItem->m_oSubGbItems.AddTail(pCommCmd);
	}
}

CCommCmd* CGbItemsGenTool::GenGbCommCmd_NewCmd(CDataGroup *pGroup)
{
	CCommCmd *pCommCmd = new CCommCmd;
	pCommCmd->m_strID = pGroup->m_strID;
	pCommCmd->m_strName = pGroup->m_strName;
	pCommCmd->m_strCommCmdID = pGroup->m_strID;
	//pCommCmd->m_nFillRptDataset = 1;

	if (GetCommCmdRwOptr(pGroup->m_strID, pCommCmd->m_strRwOptr))
	{
	}
	else
	{
		pCommCmd->m_strRwOptr = pGroup->m_strDataType;   //read、write、none、register。从m_strDataType获取
	}

	if (pCommCmd->m_strName.IsEmpty())
	{
		GetCommCmdName(pGroup->m_strID, pCommCmd->m_strName);
	}

	pCommCmd->InitAfterRead();
	return pCommCmd;
}

BOOL CGbItemsGenTool::GetCommCmdRwOptr(const CString &strCmdID, CString &strRwOptr)
{
	CGbCommCmd *pCmd = (CGbCommCmd *)m_pGuideBook->m_oGbCommCmdConfig.FindByID(strCmdID);

	if (pCmd != NULL)
	{
		strRwOptr = pCmd->m_strGbRwOptr;
		return TRUE;
	}

	return FALSE;
}

BOOL CGbItemsGenTool::GetCommCmdName(const CString &strCmdID, CString &strName)
{
	CGbCommCmd *pCmd = (CGbCommCmd *)m_pGuideBook->m_oGbCommCmdConfig.FindByID(strCmdID);

	if (pCmd != NULL)
	{
		strName = pCmd->m_strName;
		return TRUE;
	}

	return FALSE;
}

void CGbItemsGenTool::GenGbItemBase_Define_MacroTest_InitMacroPara(CMacroTest *pMacroTest, CItemsGenNode *pNode)
{
	CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pNode->GetAncestor(GBITEMSGENMNGRCLASSID_CMACROITEMSGEN);
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	pMacroTestPara->SetMacroID(pMacroItemsGen->m_strMacroID);
	pMacroTestPara->InitAfterRead();
	CExBaseList listParasMap;

	//shaolei 2023-11-14 注释此处。
	//进入到该函数，肯定是有生成规则的。有生成规则，则按网页处理
// 	if (IsUI_Original())
// 	{
// 		//对于原生态功能，pParentItem为ROOT-TYPE的CItems节点，只生成一个电气量项目pMacroTest，作为其子项目
// 		//因此，将m_pDataGroup中的数据，存放到pMacroTest的子节点中
// 		//原生态功能，只需要将参数存到pUiParas中，而不需要存到pMacroTestPara中。执行测试时。优先获取pUiParas中的参数
// 		//  <test-macro-ui-paras><![CDATA[      ]]></test-macro-ui-paras>
// 		CTestMacroUiParas *pUiParas = pMacroTest->CreateTestMacroUiParas();
// 		CString strParas;
// 		GetXml_TestMacroUiParas(strParas, pMacroItemsGen->m_strMacroID);
//         //pUiParas->SetParaText(strParas);
//         pUiParas->m_strParaText = strParas;
// 	}
// 	else if (IsUI_Web())
	{
		//将所有的参数映射，都汇总到临时链表中，此时参数映射中的值，已经是通过界面参数赋值过的
		pNode->GetAllParasMap(listParasMap);
		CItemsGenParasMap *pParasMap = pMacroItemsGen->GetItemsGenParasMap();

		if (pParasMap != NULL)
		{
			listParasMap.Append(pParasMap);
		}
	
		CMacroTestParaDatas *pFaultParas = pMacroTestPara->GetFaultParaDatas();

		POS pos = listParasMap.GetHeadPosition();

		while (pos != NULL)
		{
			CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)listParasMap.GetNext(pos);

			//映射失败的参数，不作为电气量项目的参数
			if (!pDataMap->m_nIsMapSucc)
			{
				continue;
			}

			CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pDataMap->m_strID);
			p->m_strExpression = pDataMap->m_strValue;
		}
		//后期可以考虑增加一个校验，校验参数映射中的参数的ID与测试功能定义中的参数ID是否一致
// 		CTestMacros *pTestMacros = m_pGuideBook->m_pTestMacros;
// 		CTestMacro *pTestMacro = pTestMacros->FindByID(pMacroItemsGen->m_strMacroID);
// 		//对于网页参数生成模板，仅考虑故障参数和系统参数，不考虑扩展故障参数
// 		CTmFaultParas *pTmFaultParas = pTestMacro->GetFaultParas();

	}

    GenGbItemBase_Define_MacroTest_InitReport(pMacroTest, &listParasMap);
	listParasMap.RemoveAll();
}

void CGbItemsGenTool::GenGbItemBase_Class(CGbItemBase *pParentItem, CItemsGenInst *pInst)
{
	//暂时不实现
	//可以考虑将Class模式的的规则定义，转换成Define模式的规则定义，再进行模板生成
}

BOOL CGbItemsGenTool::SetItemPara(const CString &strMacroID, const CString &strItemPath, CDataGroup *pItemsParas, CSttContents *pContents)
{
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	//IEC配置和硬件通道配置，需要记录参数到对应指针
	//SystemConfig，在CSttGuideBookGenServer::Process_Cmd_Ats_SetItemPara_SystemConfig中记录
	if (strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		SetItemPara_IecConfig(pContents);
	}

	if (strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		SetItemPara_ChMapsConfig(pContents);
	}

	if (strItemPath.IsEmpty())
	{
		return TRUE;  //当项目路径为空，则说明是主界面直接设置的参数，直接返回成功
	}

	CExBaseObject *pObj = Gb_GetItem(m_pGuideBook, strItemPath);

	if (pObj == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("设置项目参数失败！找不到对应项目，项目路径=【%s】"), strItemPath.GetString());
		return FALSE;
	}

	if (pObj->GetClassID() != GBCLASSID_MACROTEST)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("设置项目参数失败！项目类型不正确，项目路径=【%s】"), strItemPath.GetString());
		return FALSE;
	}

	CMacroTest *pMacroTest = (CMacroTest *)pObj;
    CString strItemMacroID = pMacroTest->GetTestMacroID() ;

    if(strItemMacroID != strMacroID)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("设置项目参数失败！功能ID不一致，模板中功能ID = 【%s】， 报文参数中功能ID = 【%s】，项目路径=【%s】"), strItemMacroID.GetString(),  strMacroID.GetString(), strItemPath.GetString());
        return FALSE;
    }

    if(strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig || strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig || strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
    {
        return SetItemPara(pMacroTest, pItemsParas, pContents);
    }

 	if (pItemsParas == NULL)
 	{
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数错误！缺少【%s】，测试项目参数设置失败！"), STT_CMD_PARA_ItemParas);
 		return FALSE;
 	}

    CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

	if (pUIParas != NULL)
	{
		CString strParasText;
		GetXml_TestMacroUiParas(strParasText, pItemsParas, strItemMacroID);
        //pUIParas->SetParaText(strParasText);
        pUIParas->m_strParaText = strParasText;
		return TRUE;
	}

	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CMacroTestParaDatas *pFaultParas = pMacroTestPara->GetFaultParaDatas();
	pFaultParas->DeleteAll();   //删除原先所有的参数，此处默认更新的参数是全部参数
	POS pos = pItemsParas->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pItemsParas->GetNext(pos);
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pData->m_strID);
		p->m_strExpression = pData->m_strValue;
	}

	return TRUE;
}

BOOL CGbItemsGenTool::SetItemPara(CMacroTest *pMacroTest, CDataGroup *pItemsParas, CSttContents *pContents)
{
	if (pContents == NULL)
	{
		return FALSE;
	}

    CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

    if (pUIParas == NULL)
    {
        return FALSE;
    }

    pUIParas->m_strParaText = pContents->m_strText;

    return TRUE;
}

BOOL CGbItemsGenTool::SetItemPara(const CString &strItemPath, CSttContents *pRsltExpr)
{
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	if (strItemPath.IsEmpty())
	{
		return FALSE;  
	}

	CGbItemBase *pItem = (CGbItemBase *)Gb_GetItem(m_pGuideBook, strItemPath);

	if (pItem == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("设置项目结果判断表达式失败！找不到对应项目，项目路径=【%s】"), strItemPath.GetString());
		return FALSE;
	}

	CItemRsltExprRun *pRsltExprRun = pItem->GetRsltExpr();
	pRsltExprRun->DeleteAll();
	BSTR bstrText = pRsltExpr->m_strText.AllocSysString();
	pRsltExprRun->SetXml(bstrText, CGbXMLKeys::g_pXmlKeys);
#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif

	return TRUE;
}

BOOL CGbItemsGenTool::SetItemPara_SystemConfig(long nHasDigital)
{
    if (m_pGuideBook == NULL)
    {
        return FALSE;
    }

    CExBaseList oList;
    CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return FALSE;
	}

    Gb_GetAllItemsByID(pDevice, STT_ITEMS_ID_BEFORETEST, oList, GBCLASSID_ITEMS);

    POS pos = oList.GetHeadPosition();
    CItems *pItems = NULL;

    while(pos != NULL)
    {
        pItems = (CItems *)oList.GetNext(pos);

        if(nHasDigital == 0)
        {
            pItems->DeleteByID(STT_CMD_TYPE_SYSTEM_IECConfig);
            continue;
        }

        if(pItems->FindByID(STT_CMD_TYPE_SYSTEM_IECConfig) != NULL)
        {
            continue;
        }

		CMacroTest *pMacroTest = GenGuideBook_CreateMacroTest(g_sLangTxt_Iec61850Cfg/*_T("IEC61850配置")*/, STT_CMD_TYPE_SYSTEM_IECConfig);
		pItems->AddNewChild(pMacroTest);
		pMacroTest->InitMacroID();
		CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
		pMacroTestPara->SetMacroID(_T("Iec61850Config"));
		//具体参数通过SetItemParas确定，先弄一个空的参数
		CTestMacroUiParas *pUIParas = pMacroTest->CreateTestMacroUiParas();

		if (m_pIecDatasMngr != NULL)
		{
			CString strIecDatas;
			strIecDatas = m_pIecDatasMngr->GetXml(CCfgDataMngrXmlRWKeys::g_pXmlKeys);
			pUIParas->m_strParaText = strIecDatas;
		}
    }

	oList.RemoveAll();
    return TRUE;
}

void CGbItemsGenTool::SetItemPara_IecConfig(CSttContents *pContents)
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = new CIecCfgDatasMngr;
	BSTR bstrText = pContents->m_strText.AllocSysString();
	pIecCfgDatasMngr->SetXml(bstrText, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif

	SetIecCfgDatasMngr(pIecCfgDatasMngr);
}

void CGbItemsGenTool::SetItemPara_ChMapsConfig(CSttContents *pContents)
{
	CSttChMaps *pChMaps = new CSttChMaps;
	BSTR bstrText = pContents->m_strText.AllocSysString();
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	pChMaps->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif

	SetChMaps(pChMaps);
}

//UpdateItem，仅用于原生态功能，更新项目参数用
BOOL CGbItemsGenTool::UpdateItem(const CString &strItemPath, const CString &strItemType, CSttContents *pContents)
{
	if (pContents == NULL)
	{
		return FALSE;
	}

	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	//UpdateItem指令，传递的strItemPath，对应的项目应该是ROOT-TYPE的CItems项目
	CExBaseObject *pObj = Gb_GetItem(m_pGuideBook, strItemPath);

	if (pObj == NULL)
	{
		if (strItemType != _T("commcmd"))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("更新测试项目参数失败！找不到对应项目，项目路径=【%s】"), strItemPath.GetString());
			return FALSE;
		}
		else
		{
			CString strParentItemPath;
			GetParentItemPath(strItemPath, strParentItemPath);
			CGbItemBase *pParent = (CGbItemBase *)Gb_GetItem(m_pGuideBook, strParentItemPath);

			if (pParent == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("更新测试项目参数失败！找不到对应的父项目，项目路径=【%s】"), strParentItemPath.GetString());
				return FALSE;
			}

			CCommCmd *pNew = new CCommCmd();
			pParent->AddNewChild(pNew);
			UINT nClassID = pParent->GetClassID();

			if (nClassID == GBCLASSID_MACROTEST
				|| nClassID == GBCLASSID_SAFETY
				|| nClassID == GBCLASSID_SYSPARAEDIT)
			{
				pNew->m_bIsSubItem = TRUE;
				pParent->m_oSubGbItems.AddTail(pNew);
			}

			return UpdateItem_CommCmd(pNew, pContents);
		}
	}

	if (pObj->GetClassID() == GBCLASSID_ITEMS)
	{
		return UpdateItem_Items(pObj, pContents);
	}

	if (pObj->GetClassID() == GBCLASSID_MACROTEST)
	{
		return UpdateItem_MacroTest(pObj, pContents);
	}

	if (pObj->GetClassID() == GBCLASSID_COMMCMD)
	{
		return UpdateItem_CommCmd(pObj, pContents);
	}

	return FALSE;
}

BOOL CGbItemsGenTool::UpdateItem_MacroTest(CExBaseObject *pItem, CSttContents *pContents)
{
	CMacroTest *pMacroTest = (CMacroTest *)pItem;
	CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

	//对于原生态功能，电气量相关的参数，保存在pUIParas节点中。
	if (pUIParas != NULL)
	{
		pUIParas->m_strParaText = pContents->m_strText;

		CMacroTestPara *pMacroPara = pMacroTest->GetMacroTestPara();
		CString strMacroID = pMacroPara->GetMacroID();

		if (strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
		{
			long nHasDigital = 0;
			CSttMacro *pSttMacro = new CSttMacro;
			pSttMacro->SetCreateMacroChild(TRUE);
			BSTR bstrText = pContents->m_strText.AllocSysString();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			pSttMacro->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#ifdef _PSX_IDE_QT_
			delete bstrText;
#else
			SysFreeString(bstrText);// 用完释放
#endif

// 			CSttParas *pItemParas = pSttMacro->GetParas();
// 			pItemParas->GetDataValue(STT_CMD_PARA_HasDigital, nHasDigital);
			//Windows下，不根据是否含有数字量，对IEC61850配置项目进行处理
			//SetItemPara_SystemConfig(nHasDigital);
			SetSysParameter(pSttMacro);

			return TRUE;
		}

		if (strMacroID == STT_CMD_ATS_MACRO_ID_GradientTest || STT_CMD_ATS_MACRO_ID_StateTest)
		{
			if (m_pUIParasGroup == NULL)
			{
				m_pUIParasGroup = new CDataGroup;
			}

			m_oUiParas_SortIdPath.RemoveAll();
			m_pUIParasGroup->DeleteAll();
			CDataGroup oUiParas;
		 	BSTR bstrText = pContents->m_strText.AllocSysString();
		 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		 	BOOL bRet = oUiParas.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
		 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		 	
#ifdef _PSX_IDE_QT_
            delete bstrText;
#else
            SysFreeString(bstrText);// 用完释放
#endif

			m_pUIParasGroup->AppendCloneEx(oUiParas, TRUE);
			AfterInitUIParas();

			GenGbItemBase_MacroTest_RsltExpr(pMacroTest);
		}
	
		return TRUE;
	}

	return FALSE;
}

BOOL CGbItemsGenTool::UpdateItem_Items(CExBaseObject *pItem, CSttContents *pContents)
{

	CItems *pRootTypeItems = (CItems *)pItem;
	CMacroTest *pMacroTest = (CMacroTest *)pRootTypeItems->FindByID(pRootTypeItems->m_strStxmlFile);

	if (pMacroTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("更新测试项目参数失败！找不到对应的电气量项目，项目标识=【%s】")
			, pRootTypeItems->m_strStxmlFile.GetString());
	
		return FALSE;
	}

	CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

	//对于原生态功能，电气量相关的参数，保存在pUIParas节点中。
	if (pUIParas != NULL)
	{
		pUIParas->m_strParaText = pContents->m_strText;
		return TRUE;
	}

	return FALSE;
}

BOOL CGbItemsGenTool::UpdateItem_CommCmd(CExBaseObject *pItem, CSttContents *pContents)
{
	CSttCommCmd oSttCommCmd;
	CCommCmd *pDest = (CCommCmd*)pItem;

	BSTR bstrPara = pContents->m_strText.AllocSysString();
	oSttCommCmd.SetXml(bstrPara, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
#ifdef _PSX_IDE_QT_
	delete bstrPara;
#else
	SysFreeString(bstrPara);// 用完释放
#endif

	CSttCmdGuideBookTransTool oTool;
	oTool.Trans(&oSttCommCmd, pDest);

	return TRUE;
}

BOOL CGbItemsGenTool::QueryItem(const CString &strItemPath, CString &strItemPara)
{
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	//UpdateItem指令，传递的strItemPath，对应的项目应该是ROOT-TYPE的CItems项目
	CExBaseObject *pObj = Gb_GetItem(m_pGuideBook, strItemPath);

	if (pObj == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("查询测试项目参数失败！找不到对应项目，项目路径=【%s】"), strItemPath.GetString());
		return FALSE;
	}

	if (pObj->GetClassID() == GBCLASSID_MACROTEST)
	{
		return QueryItem_MacroTest(pObj, strItemPara);
	}
	else if(pObj->GetClassID() == GBCLASSID_ITEMS)
	{
		return QueryItem_Items(pObj, strItemPara);
	}
	else
	{
		return QueryItem_CommCmd(pObj, strItemPara);
	}

	return FALSE;
}

long CGbItemsGenTool::OfflineSel(const CString &strDeviceModel, const CString &strDeviceSN)
{
	if (m_pGuideBook == NULL)
	{
		return -1;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();//取第一个device

	if (pDevice == NULL)
	{
		return -1;
	}

	//先处理硬件通道配置
	CItems *pRootNode = pDevice->FindFirstRootTypeItem();
	long nRet1 = -1;

	if (pRootNode != NULL)
	{
		CSttMacroTestUI_TestMacroUIs *pUIs = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIs();
		CSttMacroTestUI_TestMacroUI *pTestMacroUI = (CSttMacroTestUI_TestMacroUI *)pUIs->FindByID(pRootNode->m_strStxmlFile);

		if (pTestMacroUI != NULL)
		{
			//初始化硬件通道配置
			nRet1 = Init_HdRsFile_Offline(pTestMacroUI->m_strHdRsFile, strDeviceModel, strDeviceSN);
		}
	}

	//再处理系统参数配置
	long nRet2 = Init_SystemParas_Offline(strDeviceModel, strDeviceSN);
	
	if (nRet2 == -1 || nRet1 == -1)
	{
		return -1;
	}

	//最后处理IEC61850Config
	long nHasDigital = 0;
	CSttParas *pItemParas = m_pSysParameter->GetParas();
	pItemParas->GetDataValue(STT_CMD_PARA_HasDigital, nHasDigital);
	Init_IecCfg_Offline(nHasDigital);

	return 0;
}

long CGbItemsGenTool::Init_HdRsFile_Offline(const CString &strHdRsFile, const CString &strDeviceModel, const CString &strDeviceSN)
{
	if (m_pGuideBook == NULL)
	{
		return -1;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();//取第一个device

	if (pDevice == NULL)
	{
		return -1;
	}

	BOOL bRet = FALSE;
	CString strFile;
	strFile = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_Device;
	strFile += _T("/");
	strFile += strDeviceModel;
	strFile += _T("/");
	strFile += strDeviceSN; //DB/Device/型号/编号/
	strFile += _T("/");
	strFile += strHdRsFile;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("HdRsFile [%s] not exist-1"), strFile.GetString());
		return -1;
	}

	if (m_pChMaps != NULL)
	{
		//不同的模块，初始的硬件通道配置可能不一致，此处需删除后重新初始化
		delete m_pChMaps;
		m_pChMaps = NULL;
	}

	if (m_pChMaps == NULL)
	{
		m_pChMaps = new CSttChMaps();
	}

	m_pChMaps->DeleteAll();
	bRet = m_pChMaps->OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("HdRsFile [%s] Open Failed"), strFile.GetString());
		delete m_pChMaps;
		m_pChMaps = NULL;
		return -1;
	}

	CItems *pBeforeTest = (CItems *)GetItems_BeforeTest();

	if (pBeforeTest != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)pBeforeTest->FindByID(STT_CMD_TYPE_ADJUST_ChMapsConfig);

		if (pMacroTest != NULL)
		{
			CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

			if (pUIParas != NULL)
			{
				CString strText;
				strText = m_pChMaps->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
				pUIParas->m_strParaText = strText;
			}
		}
	}

	return 0;
}

long CGbItemsGenTool::Init_SystemParas_Offline(const CString &strDeviceModel, const CString &strDeviceSN)
{
	if (m_pGuideBook == NULL)
	{
		return -1;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();//取第一个device

	if (pDevice == NULL)
	{
		return -1;
	}

	BOOL bRet = FALSE;
	CString strFile;
	strFile = GetDBPath(); //2022-3-29 lijunqing     (CString)_P_GetDBPath();
	strFile += STT_MACROTEST_UI_REALPATH_Device;
	strFile += _T("/");
	strFile += strDeviceModel;
	strFile += _T("/");
	strFile += strDeviceSN; //DB/Device/型号/编号/
	strFile += _T("/");
	strFile += FILENAME_STTSYSTEMPARAS;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SystemParasFile [%s] not exist-1"), strFile.GetString());
		return -1;
	}

	if (m_pSysParameter != NULL)
	{
		delete m_pSysParameter;
		m_pSysParameter = NULL;
	}

	if (m_pSysParameter == NULL)
	{
		m_pSysParameter = new CSttMacro();
	}

	m_pSysParameter->SetCreateMacroChild(TRUE);
	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	bRet = m_pSysParameter->OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SystemParasFile [%s] Open Failed"), strFile.GetString());
		delete m_pSysParameter;
		m_pSysParameter = NULL;
		return -1;
	}

	//同步系统参数到CDevice的m_pSysPara；
	CSttParas *pParas = m_pSysParameter->GetParas();
	CExBaseList oList;
	pParas->SelectAllDatas(oList);
	m_pGuideBook->UpdateSysPara(&oList, TRUE);
	oList.RemoveAll();

	CItems *pBeforeTest = (CItems *)GetItems_BeforeTest();

	if (pBeforeTest != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)pBeforeTest->FindByID(STT_CMD_TYPE_SYSTEM_SystemConfig);

		if (pMacroTest != NULL)
		{
			CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

			if (pUIParas != NULL)
			{
				CString strText;
				strText = m_pSysParameter->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
				pUIParas->m_strParaText = strText;
			}
		}
	}

	return 0;
}

long CGbItemsGenTool::Init_IecCfg_Offline(long nHasDigital)
{
	//IEC配置，是从Stt/Config/SttIecConfig.ixml来的
	//跟装置型号、编号无关
	//因此，脱机选择时，只需要根据是否有数字量，删除或重新生成即可
	SetItemPara_SystemConfig(nHasDigital);
	return 0;
}

BOOL CGbItemsGenTool::QueryItem_MacroTest(CExBaseObject *pItem, CString &strItemPara)
{
	CMacroTest *pMacroTest = (CMacroTest *)pItem;
	CTestMacroUiParas *pUIParas = pMacroTest->GetTestMacroUiParas();

	if (pUIParas == NULL)		//如果是电气量项目，先查找自身的参数，再查找最近的ROOT-TYPE父节点
	{
		CItems *pRootTypeItems = Gb_GetFirstParentItems(pMacroTest, TRUE);

		if (pRootTypeItems != NULL)
		{
			pUIParas = pRootTypeItems->GetTestMacroUiParas();
			strItemPara = pUIParas->m_strParaText;
			return TRUE;
		}	
		else
		{
			return FALSE;
		}
	}
	else
	{
		strItemPara = pUIParas->m_strParaText;
		return TRUE;
	}
}

BOOL CGbItemsGenTool::QueryItem_Items(CExBaseObject *pItem, CString &strItemPara)
{
	CItems *pItems = (CItems *)pItem;

	if (! pItems->IsTypeRootNode())
	{
		return FALSE;
	}

	CTestMacroUiParas *pUIParas = pItems->GetTestMacroUiParas();

	//如果是测试项目分类，先查找自身的参数，再查找子电气量项目
	if (pUIParas == NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)pItems->FindByID(pItems->m_strStxmlFile);

		if (pMacroTest != NULL)
		{
			pUIParas = pMacroTest->GetTestMacroUiParas();
			strItemPara = pUIParas->m_strParaText;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		strItemPara = pUIParas->m_strParaText;
		return TRUE;
	}
}

BOOL CGbItemsGenTool::QueryItem_CommCmd(CExBaseObject *pItem, CString &strItemPara)
{
	CSttCmdGuideBookTransTool oTool;
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CSttCommCmd oSttCommCmd;
	oTool.Trans(pCommCmd, &oSttCommCmd);

	oSttCommCmd.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strItemPara);

	return TRUE;
}

void CGbItemsGenTool::UpdateUIParas(CDataGroup *pUIParas)
{
    m_bHasDigital = 0;

    if (pUIParas == NULL)
    {
        return;
    }

	if (m_pUIParasGroup == NULL)
	{
		m_pUIParasGroup = new CDataGroup();
	}

	//m_pUIParasGroup->DeleteAll();
	//m_pUIParasGroup->AppendCloneEx(*pUIParas, TRUE);
	//为了保持data-type属性，采用更新方式（下发报文中不一定携带数据类型）
	m_pUIParasGroup->InitDataValues(pUIParas, TRUE);
	AfterInitUIParas();

	if (m_pUIParasGroup->GetDataValue(STT_CMD_PARA_LoopTest, m_nLoopTest))
	{
		//取到了，就用界面里的值
	}
	else
	{
		m_nLoopTest = 1; //取不到，默认闭环测试
	}
}

//界面参数初始化、更新后，整理参数的路径 shaolei 2025-4-2
void CGbItemsGenTool::AfterInitUIParas()
{
	if (m_pUIParasGroup == NULL)
	{
		return;
	}

	m_oUiParas_SortIdPath.RemoveAll();

	CString strDataPath;
	POS pos = m_pUIParasGroup->GetHeadPosition();
	UINT nClassID = 0;

	while (pos != NULL)
	{
		CExBaseObject *pObj = (CExBaseObject *)m_pUIParasGroup->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			strDataPath = pData->GetIDPathEx(m_pUIParasGroup, FALSE);

			pData->m_strStep = strDataPath;  //用step属性，记录路径信息
			m_oUiParas_SortIdPath.AddTail(pData);
			continue;
		}

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGrp = (CDataGroup *)pObj;
			AfterInitUIParas(pGrp);  //递归调用
		}
	}
}

void CGbItemsGenTool::AfterInitUIParas(CDataGroup *pGrp)
{
	if (m_pUIParasGroup == NULL || pGrp == NULL)
	{
		return;
	}

	CString strDataPath;
	POS pos = pGrp->GetHeadPosition();
	CDvmData *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		CExBaseObject *pObj = (CExBaseObject *)pGrp->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			strDataPath = pData->GetIDPathEx(m_pUIParasGroup, FALSE);

			pData->m_strStep = strDataPath;  //用step属性，记录路径信息
			m_oUiParas_SortIdPath.AddTail(pData);
			continue;
		}

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pChildGrp = (CDataGroup *)pObj;
			AfterInitUIParas(pChildGrp);  //递归调用
		}
	}
}

void CGbItemsGenTool::UpdateCommCmd(CDataGroup *pCommCmd)
{
	if (pCommCmd == NULL)
	{
		delete m_pCommCmd;
		m_pCommCmd = NULL;
		return;
	}

	if (m_pCommCmd == NULL)
	{
		m_pCommCmd = new CDataGroup;
	}

	m_pCommCmd->DeleteAll();
	m_pCommCmd->AppendCloneEx2(*pCommCmd, TRUE);
}

void CGbItemsGenTool::SetCharacteristics(CSttContents *pContents)
{
	if (pContents == NULL)
	{
		delete m_pCharacteristics;
		m_pCharacteristics = NULL;
		return;
	}

	if (m_pCharacteristics == NULL)
	{
		m_pCharacteristics = new CCharacteristics;
	}

	m_pCharacteristics->DeleteAll();
	//如果有特性曲线，则将界面参数赋值给全局指针
	g_pGlobalDatas_Gb_CalParaExp = m_pUIParasGroup;

	BSTR bstrText = pContents->m_strText.AllocSysString();
	m_pCharacteristics->SetXml(bstrText, CCharacteristicXmlRWKeys::g_pXmlKeys);
#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif
}

//根据曲线ID查找，没有找到，判断是否为“*_#”格式，“#”为数字，如果是，则结合CCharacteristic的index属性进行查找
CCharacteristic* CGbItemsGenTool::FindCharacterByID(const CString &strID)
{
	if (m_pCharacteristics == NULL)
	{
		return NULL;
	}

	CCharacteristic *pFind = NULL;

	if (strID.IsEmpty())
	{
		return (CCharacteristic *)m_pCharacteristics->GetHead();
	}
	
	pFind = (CCharacteristic *)m_pCharacteristics->FindByID(strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	long nPos = strID.Find(_T("_"));   //下划线为分隔符，左边为曲线ID，右边正常应该为数字

	if (nPos < 0)
	{
		return NULL;
	}

	//如果是“*_#”格式。
	CString strID2 = strID;
	CString strLeft,strRight;
	strLeft = strID.Left(nPos);
	strRight = strID.Mid(nPos + 1);

	if ('0' <= strRight[0] && strRight[0] <= '9')
	{
		pFind = (CCharacteristic *)m_pCharacteristics->FindCharByID_Index(strLeft, strRight);

		if (pFind != NULL)
		{
			return pFind;
		}

		//如果id+index找不到，则查找ALL+index
		return (CCharacteristic *)m_pCharacteristics->FindCharByID_Index(_T("ALL"), strRight);
	}

	return NULL;
}

void CGbItemsGenTool::InitCharacteristicsByFile(const CString &strFile)
{
	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("特性曲线文件不存在！【%s】"), strFile.GetString());
		return;
	}

	if (m_pCharacteristics == NULL)
	{
		m_pCharacteristics = new CCharacteristics;
	}

	m_pCharacteristics->DeleteAll();
	m_pCharacteristics->OpenXmlFile(strFile, CCharacteristicXmlRWKeys::g_pXmlKeys);

	//如果有特性曲线，则将界面参数赋值给全局指针
	g_pGlobalDatas_Gb_CalParaExp = m_pUIParasGroup;
}

void CGbItemsGenTool::SaveGbXmlFile(const CString &strMacroID)
{
	CString strFilePath;
	strFilePath = (CString)_P_GetInstallPath();
    strFilePath += _T("e-Report/Template/");

	if (/*IsUI_Web()*/m_pGbItemsGen != NULL)
	{
		strFilePath += m_pGbItemsGen->GetGbxmlName();
	}
	else /*if (IsUI_Original())*/
	{
		strFilePath += strMacroID;
		strFilePath += _T(".gbxml");
	}

	//g_bGbExportXmlReportFile = TRUE;
	m_pGuideBook->SaveXMLFile(strFilePath);
	//g_bGbExportXmlReportFile = FALSE;
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("保存模板【%s】"), strFilePath.GetString());
}

#ifndef _PSX_QT_LINUX_
void CGbItemsGenTool::SaveDscXmlFile(const CString &strMacroID)
{
	CString strFilePath;
	strFilePath = (CString)_P_GetInstallPath();
	strFilePath += _T("e-Report/Template/");

	if (/*IsUI_Web()*/m_pGbItemsGen != NULL)
	{
		strFilePath += m_pGbItemsGen->GetGbxmlName();
	}
	else/* if (IsUI_Original())*/
	{
		strFilePath += strMacroID;
		strFilePath += _T(".dscxml");
	}
	
	CGuideBookStruDscTool oTool;
	oTool.ExportGuideBookStruDsc(m_pGuideBook, strFilePath);
}
#endif

void CGbItemsGenTool::GenGbItem_MacroID_Revise(CString &strMacroID, CDataGroup *pUIParas)
{
	if (pUIParas == NULL)
	{
		return;
	}

	if (strMacroID == STT_CMD_ATS_MACRO_ID_GradientTest)
	{
		long nVarType, nVaryMode = 0;
		pUIParas->GetDataValue(STT_CMD_PARA_VarType, nVarType);
		pUIParas->GetDataValue(STT_CMD_PARA_VaryMode, nVaryMode);

		if (nVarType == 1 && nVaryMode == 2)
		{
			strMacroID = STT_CMD_ATS_MACRO_ID_GradientMaxAngleTest;
		}
	}
}

void CGbItemsGenTool::ResetMacroNameId(CItemsGenNode *pNode, CString &strName, CString &strID)
{
	CItemsGenInterface *pInterface = pNode->GetGenInterface();

	//合并单元，需要特殊处理
	if (strName == _T("name_item"))
	{
		CItemsGenData *pData = (CItemsGenData *)pInterface->FindByID(strName);

		if (pData != NULL)
		{
			strName = pData->m_strValue;
		}
	}

	if (strID == _T("id_item"))
	{
		CItemsGenData *pData = (CItemsGenData *)pInterface->FindByID(strID);

		if (pData != NULL)
		{
			strID = pData->m_strValue;
		}
	}
}

//2022-3-29  lijunqing
/*
<ats-cmd name="" id="GenerateTemplate" testor="ATS">
	<paras name="" id="">
		<group name="generate-items" id="generate-items" data-type="generate-items" value="new / delete/ edit/ move /insert-after /insert-before /insert-head /insert-tail">
			<data name="" id="ParentItemsPath" data-type="string" value=""/> 父项目分类
			<data name="" id="ItemsID" data-type="string" value=""/>    当前项目分类ID
			<group name="items" id="items" data-type="items" value=""> 当前项目分类详细数据
				<data name="name" id="name" data-type="" value=""/>
				<data name="id" id="id" data-type="" value=""/>
				<data name="type" id="type" data-type="" value=""/>
			</group>
		</group>
	</paras>
</ats-cmd>
*/
long CGbItemsGenTool::GenerateItemsOnly(CDataGroup *pParas)
{
	m_pGbItemBase = NULL;
	m_bGenerateItemsOnly_CmdWzd = FALSE;
	CString strParentItemsPath, strItemsID;
	CString strName, strID, strType;
	long nRepeatTimes = 0;
	long nRptTitle = 0;
	long nTitleLevel = 0;
	CDataGroup *p_PARA_generate_items = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_generate_items);
	CDataGroup *p_items_paras = (CDataGroup*)p_PARA_generate_items->FindByID(STT_CMD_PARA_generate_items_items);
	p_PARA_generate_items->GetDataValue(STT_CMD_PARA_ParentItemsPath, strParentItemsPath);
	p_PARA_generate_items->GetDataValue(STT_CMD_PARA_ItemsID, strItemsID);
	CItems *pCurr = NULL;
	CGbItemBase *pItemParent = (CGbItemBase*)Gb_GetItem(m_pGuideBook, strParentItemsPath);

	if (pItemParent == NULL)
	{
		if (p_PARA_generate_items->m_strValue != STT_CMD_PARA_generate_items_create
			&& p_PARA_generate_items->m_strValue != STT_CMD_PARA_generate_items_cmd_wzd)
		{
			CString strMsg;
			strMsg = STT_CMD_PARA_ParentItemsPath;
			strMsg += "=[" + strParentItemsPath;
			strMsg += "] =不存在";
			CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);
			return -1;
		}
	}

	if (p_items_paras != NULL)
	{
		p_items_paras->GetDataValue(_T("name"), strName);
		p_items_paras->GetDataValue(_T("id"), strID);
		p_items_paras->GetDataValue(_T("type"), strType);
		p_items_paras->GetDataValue(STT_CMD_PARA_generate_items_RepeatTimes, nRepeatTimes);
		p_items_paras->GetDataValue(STT_CMD_PARA_generate_items_RptTitle, nRptTitle);
		p_items_paras->GetDataValue(STT_CMD_PARA_generate_items_TitleLevel, nTitleLevel);
	}

	if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_create)
	{
		return GenerateItemsOnly_Create(p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_new)
	{
		pCurr = new CItems();
		pCurr->m_strName = strName;
		pCurr->m_strID = strID;
		pCurr->m_strType = strType;
		pCurr->m_nTestTimes = nRepeatTimes;
		pCurr->m_nRptTitle = nRptTitle;
		pCurr->m_nTitleLevel = nTitleLevel;
		pItemParent->AddNewChild(pCurr);

		if (strID == STT_ITEMS_ID_BEFORETEST)
		{
			pItemParent->BringToHead(pCurr);
		}
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_edit)
	{
		CGbItemBase *pItemBase = (CGbItemBase*)pItemParent->FindByID(strItemsID);
		
		if (pItemBase == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ItemsID=[%s] is error"), strItemsID.GetString());
		}
		else
		{
			pItemBase->m_strName = strName;
			pItemBase->m_strID = strID;

			if (pItemBase->GetClassID() == GBCLASSID_ITEMS)
			{
				pCurr = (CItems *)pItemBase;
				pCurr->m_strType = strType;
				pCurr->m_nTestTimes = nRepeatTimes;
				pCurr->m_nRptTitle = nRptTitle;
				pCurr->m_nTitleLevel = nTitleLevel;
			}
		}
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_delete)
	{
		return GenerateItemsOnly_ItemsDelete(pItemParent, strItemsID);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_cmd_wzd)
	{
		m_bGenerateItemsOnly_CmdWzd = TRUE;
		return GenerateItemsOnly_CmdWzd(p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_cmd_add)
	{
		CSttParas *pSttParas = (CSttParas *)pParas;
		CSttContents *pContents = (CSttContents *)pSttParas->FindByID(STT_CMD_PARA_ItemParas);
		return GenerateItemsOnly_Cmd_Add(p_PARA_generate_items, pContents);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_macro_add)
	{
		CSttParas *pSttParas = (CSttParas *)pParas;
		CSttContents *pContents = (CSttContents *)pSttParas->FindByID(STT_CMD_PARA_ItemParas);
		return GenerateItemsOnly_Macro_Add(p_PARA_generate_items, pContents);
	}	
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_move_up)
	{
		return GenerateItemsOnly_ItemsMoveUp(pItemParent, strItemsID, p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_move_down)
	{
		return GenerateItemsOnly_ItemsMoveDown(pItemParent, strItemsID, p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_paste)
	{
		return GenerateItemsOnly_ItemsPaste(pItemParent, p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_safety_add)
	{
		return GenerateItemsOnly_SafetyAdd(pItemParent, pParas);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_cmd_add_grp)
	{
		return GenerateItemsOnly_CmdAddGrp(pItemParent, p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_import_dvm_file)
	{
		return GenerateItemsOnly_ImportDvmFile(p_PARA_generate_items);
	}
	else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_ain_data_map)
	{
		CDataGroup *pAinDataMapCfg = (CDataGroup *)p_PARA_generate_items->FindByID(STT_CMD_PARA_generate_items_AinDataMapCfg);
		CDataGroup *pAinRatios = (CDataGroup *)p_PARA_generate_items->FindByID(STT_CMD_PARA_generate_items_AinRatios);

		return GenerateItemsOnly_AinDataMap(pAinDataMapCfg, pAinRatios);
	}

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_Create(CDataGroup *p_PARA_generate_items)
{
	Reset();
	CDevice *pDevice = InitGuideBookForGenerateItemsOnly();
	m_pGuideBook->m_strTestMacroFileID = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
	m_pGuideBook->InitAfterRead();
	m_pGuideBook->ImportExpandDatas(pDevice);

	//创建测试时，更新系统参数
	Init_SystemParas();

	CDataGroup *p_device = (CDataGroup*)p_PARA_generate_items->FindByID(XPARA_ID_device);
	long nAddDevReset = 0;  //是否添加装置复归态

	/*
	<group id="device" data-type="device" value="">
		<data id="EngineProgID" data-type="string" value="PpMmsEngine.PoEngine" />
		<data id="ppxml-file" data-type="string" value="d:/Program Files/EPOTO/e-Protocol/Template/qqq.ppxml" />
		<data id="dvm-file" data-type="string" value="d:/Program Files/EPOTO/e-Report/Template/ats_test_11_templatefile.xml" />
		<data id="remote-ip" data-type="string" value="1" />
		<data id="remote-port" data-type="string" value="1" />
	</group>
	*/
	if (p_device != NULL)
	{
		CString strDvmFile, strPpXmlFile, strEngineProgID;
		long nTimeUnitMs = 0;  //时间定值单位是否为ms
		p_device->GetDataValue(STT_CMD_PARA_DvmFile, strDvmFile);
		p_device->GetDataValue(STT_CMD_PARA_EngineProgID, strEngineProgID);
		p_device->GetDataValue(XPARA_ID_PPXMLFILE, strPpXmlFile);
		p_device->GetDataValue(XPARA_ID_AddDevReset, nAddDevReset);

		if (p_device->GetDataValue(XPARA_ID_Time_unit_ms, nTimeUnitMs))
		{
			pDevice->m_nIsTimeSetsUnit_ms = nTimeUnitMs;
		}

		//创建测试时，SmartTest可能没有关闭。此时guideBook里面的模型被删掉了，需要重新打开模型
		//故此处注释掉判断模型文件路径是否相同  2023-3-25
		//if (strDvmFile != m_strDvmFile)
		{
			Init_DvmDevice(strDvmFile);
		}

#ifndef _not_use_autotest_
		CTCtrlCntrWorkSpace::s_SetPpTemplateFile(strPpXmlFile);
		CTCtrlCntrWorkSpace::s_SetPpEngineProgID(strEngineProgID);
#endif

		if (strPpXmlFile.GetLength() > 5)
		{
			m_pGuideBook->m_strPpTemplateFile = strPpXmlFile;
		}

		m_pGuideBook->m_strPpEngineProgID = strEngineProgID;

		SetBinaryFileName();
		//还需要处理被测设备的IP和端口。在CommmConfig的时候用到
	}

	CDataGroup *p_CommConfig = (CDataGroup*)p_PARA_generate_items->FindByID(STT_CMD_PARA_CommConfig);

	/*
		<group id="comm-config" data-type="" value="">
			<data id="DeviceSN" data-type="string" value="UT-5831" />
			<data id="ppxml-file" data-type="string" value="" />
			<data id="dvm-file" data-type="string" value="D:/Program Files/EPOTO/e-Protocol/Library/UT-5831.xml" />
			<data id="EngineProgID" data-type="string" value="MmsEngine" />
			<group id="comm-config" data-type="" value="">
				<data id="mms" data-type="" value="">
					<value id="local-ip" data-type="" value="172.21.0.100" />
					<value id="remote-ip" data-type="" value="192.168.0.37" />
					<value id="remote-port" data-type="" value="102" />
					<value id="PSW" data-type="" value="" />
					<value id="KEY" data-type="" value="" />
				</data>
			</group>
		</group>
	*/
	if (p_CommConfig != NULL)
	{
#ifndef _PSX_QT_LINUX_
#ifndef _not_use_autotest_
		CTCtrlCntrWorkSpace::SetSttCommConfig((CPpSttCommConfig *)p_CommConfig);
#endif
#endif
		m_pGuideBook->SetCommConfig(p_CommConfig);
	}

	if (nAddDevReset == 1)
	{
		GenerateItemsOnly_Create_AddDevReset(pDevice);
	}
	
	return 0;
}

//添加装置复归态：控制字全退、压板全退、定值全部设置为最大值
long CGbItemsGenTool::GenerateItemsOnly_Create_AddDevReset(CGbItemBase *pParentItem)
{
	CItems *pItems = new CItems();
	pItems->m_strName = STT_ITEMS_Name_DEVRESET;
	pItems->m_strID = STT_ITEMS_ID_DEVRESET;

	if (pParentItem != NULL)
	{
		pParentItem->AddNewChild(pItems);
		m_pGbItemBase = pItems;
	}
	
	pItems->InitAfterRead();
	m_pDevReset = pItems;

	CExBaseList oListDataset;
	CString strDatasetKey;
	//先处理定值数据集
	strDatasetKey = _T("dsSetting");
	m_oDvmDevice.GetDatasetList(strDatasetKey, oListDataset);

	CreateCommCmds_Write_ByDatasets(&oListDataset, 1, pItems, TRUE);   //1=定值

	//再处理压板数据集
	CStringArray strKeyArray;
	strDatasetKey = _T("dsEna");
	strKeyArray.Add(strDatasetKey);
	strDatasetKey = _T("dsRelayEna");
	strKeyArray.Add(strDatasetKey);
	oListDataset.RemoveAll();
	m_oDvmDevice.GetDatasetList(strKeyArray, oListDataset);

	CreateCommCmds_Write_ByDatasets(&oListDataset, 2, pItems, TRUE);   //2=压板

	oListDataset.RemoveAll();
	return 0;
}

//nType：1=定值；2=压板
//pItems：返回应答报文的临时对象，本身不添加到模板树
long CGbItemsGenTool::CreateCommCmds_Write_ByDatasets(CExBaseList *pListDatasets, UINT nType, CGbItemBase* pItemParent, BOOL bDevReset, CItems *pItems)
{
	POS pos = pListDatasets->GetHeadPosition();
	UINT nClassID = pItemParent->GetClassID();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)pListDatasets->GetNext(pos);
		CCommCmd *pNewCommCmd = new CCommCmd();

		if (nType == 1)
		{
			pNewCommCmd->m_strName = g_sLangTxt_WriteSetting/*_T("修改定值")*/;
			pNewCommCmd->m_strID = _T("WriteSetting");
			pNewCommCmd->m_strCommCmdID = _T("WriteSetting");
		}
		else
		{
			pNewCommCmd->m_strName = g_sLangTxt_WriteEna/*_T("投退压板")*/;
			pNewCommCmd->m_strID = _T("WriteEna");
			pNewCommCmd->m_strCommCmdID = _T("WriteEna");
		}

		if (bDevReset)
		{
			pNewCommCmd->m_strName += g_sLangTxt_Reset/*_T("-复归态")*/;
			pNewCommCmd->m_strID += _T("_Reset");
		}
		
		pNewCommCmd->m_strRwOptr = _T("write");
		pItemParent->AddNewChild(pNewCommCmd, TRUE);
		pNewCommCmd->InitAfterRead();

		if (pItems != NULL)
		{
			pItems->AddTail(pNewCommCmd);
		}

		CCmd *pCmd = pNewCommCmd->GetCmd();
		pCmd->m_strDelayBeforeCmd = _T("2000");
		pCmd->m_strDelayAfterCmd = _T("2000");

		CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
		pCmd->m_strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;

		if (nClassID == GBCLASSID_MACROTEST
			|| nClassID == GBCLASSID_SAFETY
			|| nClassID == GBCLASSID_SYSPARAEDIT)
		{
			pNewCommCmd->m_bIsSubItem = TRUE;
			pItemParent->m_oSubGbItems.AddTail(pNewCommCmd);
		}

		//添加通讯命令参数
		if (nType == 1)
		{
			POS posPara = pDataset->GetHeadPosition();

			while (posPara != NULL)
			{
				CDvmData *pData = (CDvmData *)pDataset->GetNext(posPara);

				if (pData->m_strName.Find(_T("识别码")) >= 0)
				{
					continue;
				}

				if (IsDvmData_BOOL(pData))
				{
					//控制字：全部退掉
					//控制字：不管是否装置复归态，都全部退掉。因为上位机界面是勾选框，需要界面和实际保持一致
					pCmd->AddValue(pData->m_strID, _T("0"));
				}
				else
				{
					if (bDevReset)
					{
						//定值：跳闸矩阵按普通定值处理，因为通讯命令中下发的参数是十进制
						pCmd->AddValue(pData->m_strID, pData->m_strMax);  //全部设置为最大值
					}
				}
			}
		}
		else if (nType == 2)
		{
			POS posPara = pDataset->GetHeadPosition();

			while (posPara != NULL)
			{
				CDvmData *pData = (CDvmData *)pDataset->GetNext(posPara);

				if (bDevReset)
				{
					//2023-9-4  按照王工最新的要求，压板全投，控制字全退
					pCmd->AddValue(pData->m_strID, _T("1"));
					continue;
				}

				if (pData->m_strName.Find(_T("远方")) >= 0)
				{
					//远方压板
					//此处添加到通讯命令，是为了保持参数和实际界面保持一致。
					pCmd->AddValue(pData->m_strID, _T("1"));
					continue;
				}

				//软压板：全部退掉
				//软压板：不管是否装置复归态，都全部退掉。因为上位机界面是勾选框，需要界面和实际保持一致
				pCmd->AddValue(pData->m_strID, _T("0"));
			}
		}
	}

	return 0;
}

//克隆装置复归态，仅克隆通讯命令【防止有其它的测试项目】
CItems* CGbItemsGenTool::CloneDevReset(BOOL bIDUseReset)
{
	ASSERT(m_pDevReset != NULL);

	if (m_pDevReset == NULL)
	{
		return NULL;
	}

	CItems *pItems = new CItems();
	POS pos = m_pDevReset->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = m_pDevReset->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_COMMCMD)
		{
			continue;
		}

		CCommCmd *pCommCmd = (CCommCmd *)pObj;
		CCommCmd *pNew = (CCommCmd *)pCommCmd->CloneEx(TRUE, TRUE);
		pItems->AddNewChild(pNew);

		if (!bIDUseReset)
		{
			pNew->m_strID.Replace(_T("_Reset"), _T(""));
			pNew->m_strName.Replace(g_sLangTxt_Reset/*_T("-复归态")*/, _T(""));
		}
	}

	return pItems;
}

long CGbItemsGenTool::GenerateItemsOnly_ItemsDelete(CGbItemBase* pItemParent, const CString &strItemsID)
{
	CGbItemBase *pItemCurr = (CGbItemBase*)pItemParent->FindByID(strItemsID);

	if (pItemCurr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ItemsID=[%s] is error"), strItemsID.GetString());
	}
	else
	{
		//安全措施项目，可以直接删除，不用考虑其它逻辑
		if (pItemCurr->GetClassID() == GBCLASSID_SAFETY)
		{
			pItemParent->Delete(pItemCurr);
			//删除项目，需要重新QueryItem，否则ItemContainer中的数据是错乱的
			m_pGuideBook->m_nIndex = 0;

			return 0;
		}

		if (pItemParent->GetClassID() == GBCLASSID_MACROTEST
			&& pItemCurr->GetClassID() == GBCLASSID_COMMCMD
			&& pItemCurr->m_bIsSubItem == TRUE)
		{
			pItemParent->m_oSubGbItems.Remove(pItemCurr);
		}

		if (m_pItems_SelfDef == pItemCurr)
		{
			m_pItems_SelfDef = NULL;
		}

		if (m_pMacroTest == pItemCurr)
		{
			m_pMacroTest = NULL;
		}

		if (m_pGbItemBase == pItemCurr)
		{
			m_pGbItemBase = NULL;
		}

		if (m_pDevReset == pItemCurr)
		{
			m_pDevReset = NULL;
		}

		CString strItemPath1, strItemPath2;
		strItemPath1 = pItemCurr->GetIDPathEx(GBCLASSID_DEVICE, FALSE);  //被删项目的路径

		if (m_pMacroTest != NULL)
		{
			strItemPath2 = m_pMacroTest->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

			if (strItemPath2.Find(strItemPath1) == 0)
			{
				//路径1是路径2的子集，说明 被删项目 是 路径2对应的项目 的祖先节点，会被一起删除
				m_pMacroTest = NULL;
			}
		}

		if (m_pItems_SelfDef != NULL)
		{
			strItemPath2 = m_pItems_SelfDef->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

			if (strItemPath2.Find(strItemPath1) == 0)
			{
				//路径1是路径2的子集，说明 被删项目 是 路径2对应的项目 的祖先节点，会被一起删除
				m_pItems_SelfDef = NULL;
			}
		}

		pItemParent->Delete(pItemCurr);
	}

	//删除项目，需要重新QueryItem，否则ItemContainer中的数据是错乱的
	m_pGuideBook->m_nIndex = 0;

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_ItemsMoveUp(CGbItemBase* pItemParent, const CString &strItemsID, CDataGroup *p_PARA_generate_items)
{
	CGbItemBase *pItemCurr = (CGbItemBase*)pItemParent->FindByID(strItemsID);

	if (pItemCurr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ItemsID=[%s] is error"), strItemsID.GetString());
	}
	else
	{
		CGbItemBase *pItemPrev = NULL;
		long nMoveTimes = 0;
		p_PARA_generate_items->GetDataValue(STT_CMD_PARA_MoveTimes, nMoveTimes);

		if (nMoveTimes <= 0)
		{
			nMoveTimes = 1;
		}

		while (nMoveTimes >= 1)
		{
			pItemPrev = ((CGbItemBase*)pItemParent)->GetPrevItem(pItemCurr);

			if (pItemPrev == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ItemsID=[%s] 查找前一个项目失败"), strItemsID.GetString());
				break;
			}

			pItemParent->ChangePosition(pItemPrev, pItemCurr);
			nMoveTimes--;
		}
	}

	//移动项目顺序，需要重新QueryItem，否则ItemContainer中的数据是错乱的
	m_pGuideBook->m_nIndex = 0;

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_ItemsMoveDown(CGbItemBase* pItemParent, const CString &strItemsID, CDataGroup *p_PARA_generate_items)
{
	CGbItemBase *pItemCurr = (CGbItemBase*)pItemParent->FindByID(strItemsID);

	if (pItemCurr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ItemsID=[%s] is error"), strItemsID.GetString());
	}
	else
	{
		CGbItemBase *pItemNext = NULL;
		long nMoveTimes = 0;
		p_PARA_generate_items->GetDataValue(STT_CMD_PARA_MoveTimes, nMoveTimes);

		if (nMoveTimes <= 0)
		{
			nMoveTimes = 1;
		}

		while (nMoveTimes >= 1)
		{
			pItemNext = ((CGbItemBase*)pItemParent)->GetNextItem(pItemCurr);

			if (pItemNext == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ItemsID=[%s] 查找后一个项目失败"), strItemsID.GetString());
				break;
			}

			pItemParent->ChangePosition(pItemNext, pItemCurr);
			nMoveTimes--;
		}
	}

	//移动项目顺序，需要重新QueryItem，否则ItemContainer中的数据是错乱的
	m_pGuideBook->m_nIndex = 0;

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_ItemsPaste(CGbItemBase* pItemParent, CDataGroup *p_PARA_generate_items)
{
	//pItemParent //目标父项目
	CString strItemPath;
	p_PARA_generate_items->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);
	CGbItemBase *pItemBaseSrc = (CGbItemBase*)Gb_GetItem(m_pGuideBook, strItemPath);  //被复制的源项目

	if (pItemBaseSrc == NULL)
	{
		CString strMsg;
		strMsg = STT_CMD_PARA_ItemPath;
		strMsg += "=[" + strItemPath;
		strMsg += "] =不存在";
		CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);
		return -1;
	}

	UINT nClassID = pItemBaseSrc->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_ITEMS:
		{
			CItems *pSrcItem = (CItems *)pItemBaseSrc;
			CItems *pNewItem = (CItems *)pSrcItem->CloneEx(TRUE, TRUE);
			pItemParent->InitNameAndIDForPaste(pNewItem);
			pItemParent->AddNewChild(pNewItem);
		}

		break;

	case GBCLASSID_MACROTEST:
		{
			CMacroTest *pSrcItem = (CMacroTest *)pItemBaseSrc;
			CMacroTest *pNewItem = (CMacroTest *)pSrcItem->CloneEx(TRUE, TRUE);
			pItemParent->InitNameAndIDForPaste(pNewItem);
			pItemParent->AddNewChild(pNewItem);
		}

		break;

	case GBCLASSID_COMMCMD:
		{
			CCommCmd *pSrcItem = (CCommCmd *)pItemBaseSrc;
			CCommCmd *pNewItem = (CCommCmd *)pSrcItem->CloneEx(TRUE, TRUE);
			pItemParent->InitNameAndIDForPaste(pNewItem);
			pItemParent->AddNewChild(pNewItem);
		}

		break;
	default:
		return 0;
	}

	//粘贴项目，需要重新QueryItem，否则ItemContainer中的数据是错乱的
	m_pGuideBook->m_nIndex = 0;
	return 0;
}

/*
<ats-cmd name="" id="GenerateItems" mid="0" time="2023-07-19 09:24:56" testor="ATS">
	<paras name="" id="">
		<group id="generate-items" data-type="generate-items" value="safety-add">
			<data id="ParentItemsPath" data-type="string" value=""/>
			<data id="ItemName" data-type="string" value="">
			<group id="safety-datas" data-type="" value="">
				<data name="额定电压" id="Un" value="220"/>
				<data name="额定电流" id="In" value="5"/>
				<data name="额定电频率" id="Fre" value="50"/>
				……
			</group>
		</group>
	</paras>
	<msgs>
		<msg type="" id="" time="" level=""><![CDATA[提示信息]]></msg>
		<msg type="" id="" time="" level=""><![CDATA[提示信息]]></msg>
	</msgs>
</ats-cmd>
*/
long CGbItemsGenTool::GenerateItemsOnly_SafetyAdd(CGbItemBase* pItemParent, CDataGroup *pParas)
{
	if (pItemParent == NULL)
	{
		return -1;
	}

	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)pParas->GetParent();
	CDataGroup *p_PARA_generate_items = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_generate_items);
	CDataGroup *pSafetyDatas = (CDataGroup*)p_PARA_generate_items->FindByID(STT_CMD_PARA_SafetyDatas);
	CSttMsgs *pSttMsgs = pAtsCmd->GetSttMsgs();
	CString strItemName, strItemID;
	p_PARA_generate_items->GetDataValue(STT_CMD_PARA_ItemName, strItemName);
	p_PARA_generate_items->GetDataValue(STT_CMD_PARA_ItemID, strItemID);

	CSafety *pSafety = NULL;
	CShortDatas *pDatas = NULL;
	//name是允许编辑的，通过ID进行判断
	pSafety = (CSafety *)pItemParent->FindByID(strItemID);

	if (pSafety != NULL)
	{
		//如果已经存在，则认为是编辑更新
		pDatas = pSafety->GetDatas();

		if (pDatas != NULL)
		{
			pDatas->DeleteAll();
		}
		
		pSafety->DeleteAllMsgs();
	}
	else
	{
		pSafety = new CSafety();
		pItemParent->AddNewChild(pSafety, TRUE);
	}

	pSafety->m_strName = strItemName;
	pSafety->m_strID = strItemID;
	pSafety->m_nDataMode = SAFETY_DATAMODE_LIST;//默认为数据列表，需要别的类型时，再新增参数

	//处理数据列表
	if (pDatas = NULL)
	{
		pDatas = new CShortDatas();
		pSafety->AddNewChild(pDatas);
	}

	if (pSafetyDatas != NULL)
	{
		POS pos = pSafetyDatas->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pSafetyDatas->GetNext(pos);
			CShortData *pNewData = new CShortData();
			pDatas->AddNewChild(pNewData);

			pNewData->m_strName = pData->m_strName;
			pNewData->m_strID = pData->m_strID;
			pNewData->m_dwReserved = 1;
			pNewData->m_strDataTypeID = pData->m_strDataType;
			pNewData->m_strFormat = pData->m_strFormat;
			pNewData->m_strUnit = pData->m_strUnit;
		}
	}

	//处理提示信息
	POS pos2 = pSttMsgs->GetHeadPosition();

	while (pos2 != NULL)
	{
		CSttMsg *pSttMsg = (CSttMsg *)pSttMsgs->GetNext(pos2);
		CMsg *pNewMsg = new CMsg();
		pSafety->AddNewChild(pNewMsg);
		pNewMsg->m_strMsg = pSttMsg->m_strMsg;
	}

	pSafety->InitAfterRead();
	return 0;
}

/*
<ats-cmd name="" id="GenerateItems" mid="0" time="2023-08-11 16:59:47" testor="ATS">
	<paras name="" id="">
		<group id="generate-items" data-type="generate-items" value="cmd-add-grp">
			<data id="ParentItemsPath" data-type="string" value="Items" />
			<data id="aft-use-devreset" data-type="long" value="1" />
		</group>
	</paras>
</ats-cmd>
*/
//添加测试前、后组合。测试前放到pItemParent的头，测试后放到pItemParent的尾
long CGbItemsGenTool::GenerateItemsOnly_CmdAddGrp(CGbItemBase* pItemParent, CDataGroup *p_PARA_generate_items)
{
	if (pItemParent == NULL)
	{
		return -1;
	}

	if (m_pCmdAddGrp == NULL)
	{
		m_pCmdAddGrp = new CItems();
		m_pCmdAddGrp->m_strID = STT_CMD_PARA_generate_items_cmd_add_grp;
		m_pCmdAddGrp->m_strName = g_sLangTxt_BeforeTestGrp/*_T("测试前_后组合")*/;
	}
	
	m_pCmdAddGrp->RemoveAll();

	//是否添加通讯命令项目
	long nAddCommCmd = 0;
	p_PARA_generate_items->GetDataValue(XPARA_ID_AddCommCmd, nAddCommCmd);
	CItems *pAFT = NULL;
	CItems *pBFT = NULL;

	//不添加通讯命令，只返回空的分类节点
	if (nAddCommCmd == 0)
	{
		//处理测试前准备
		pBFT = new CItems();
		pBFT->m_strName = STT_ITEMS_Name_COMM_BFT;
		pBFT->m_strID = STT_ITEMS_ID_BEFORETEST;
		pItemParent->AddNewChild(pBFT);
		pItemParent->BringToHead(pBFT);
		m_pCmdAddGrp->AddTail(pBFT);
		pBFT->InitAfterRead();

		//处理测试后恢复
		pAFT = new CItems();
		pAFT->m_strName = STT_ITEMS_Name_COMM_AFT;
		pAFT->m_strID = STT_ITEMS_ID_AFTERTEST;
		pItemParent->AddNewChild(pAFT);
		m_pCmdAddGrp->AddTail(pAFT);
		pAFT->InitAfterRead();
		return 0;
	}

	//最开始的设计是，只有测试后恢复使用复归态。最新的修改为：测试前和测试后，都使用复归态
	//处理测试后恢复
	//测试后恢复是否使用“装置复归态”。否则根据测试前准备取反
	long nAftUseDevReset = 0;
	p_PARA_generate_items->GetDataValue(XPARA_ID_AftUseDevReset, nAftUseDevReset);

	if (nAftUseDevReset)
	{
		if (m_pDevReset == NULL)
		{
			GenerateItemsOnly_Create_AddDevReset(NULL);
		}

		//克隆装置复归态，只克隆CommCmd
		pBFT = CloneDevReset(FALSE);
		pAFT = CloneDevReset(TRUE);

		pBFT->m_strName = STT_ITEMS_Name_COMM_BFT;
		pBFT->m_strID = STT_ITEMS_ID_BEFORETEST;
		pItemParent->AddNewChild(pBFT);
		pItemParent->BringToHead(pBFT);
		m_pCmdAddGrp->AddTail(pBFT);
		pBFT->InitAfterRead();

		pAFT->m_strName = STT_ITEMS_Name_COMM_AFT;
		pAFT->m_strID = STT_ITEMS_ID_AFTERTEST;
		pItemParent->AddNewChild(pAFT);
		pItemParent->BringToTail(pAFT);
		m_pCmdAddGrp->AddTail(pAFT);
		return 0;
	}


	//处理测试前准备
	pBFT = new CItems();
	pBFT->m_strName = STT_ITEMS_Name_COMM_BFT;
	pBFT->m_strID = STT_ITEMS_ID_BEFORETEST;
	pItemParent->AddNewChild(pBFT);
	pItemParent->BringToHead(pBFT);
	m_pCmdAddGrp->AddTail(pBFT);
	pBFT->InitAfterRead();

	CExBaseList oListDataset;
	CString strDatasetKey;
	//先处理定值数据集
	strDatasetKey = _T("dsSetting");
	m_oDvmDevice.GetDatasetList(strDatasetKey, oListDataset);
	CreateCommCmds_Write_ByDatasets(&oListDataset, 1, pBFT, FALSE);   //1=定值

	//再处理压板数据集
	CStringArray strKeyArray;
	strDatasetKey = _T("dsEna");
	strKeyArray.Add(strDatasetKey);
	strDatasetKey = _T("dsRelayEna");
	strKeyArray.Add(strDatasetKey);
	oListDataset.RemoveAll();
	m_oDvmDevice.GetDatasetList(strKeyArray, oListDataset);
	CreateCommCmds_Write_ByDatasets(&oListDataset, 2, pBFT, FALSE);   //2=压板
	oListDataset.RemoveAll();

	//暂时无法取反，因为测试前准备中也没有通讯参数
	//所以测试后恢复，直接与测试前准备一致即可
	pAFT = (CItems *)pBFT->CloneEx(TRUE, TRUE);
	pAFT->m_strName = STT_ITEMS_Name_COMM_AFT;
	pAFT->m_strID = STT_ITEMS_ID_AFTERTEST;
	pItemParent->AddNewChild(pAFT);
	pItemParent->BringToTail(pAFT);
	m_pCmdAddGrp->AddTail(pAFT);

	return 0;
}

/*
<ats-cmd name="" id="GenerateItems" mid="0" time="2023-08-11 16:59:47" testor="ATS">
	<paras name="" id="">
		<group id="generate-items" data-type="generate-items" value="import-dvm-file">
			<data id="dvm-file" value="SZNR-TTU.xml"/>
			<data id="is-dvm-map" value="0"/>   是否进行模型映射。0-不映射
		</group>
	</paras>
</ats-cmd>
*/
long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile(CDataGroup *p_PARA_generate_items)
{
	CString strDvmFile;
	long nIsDvmMap = 0;
	p_PARA_generate_items->GetDataValue(XPARA_ID_IsDvmMap, nIsDvmMap);
	p_PARA_generate_items->GetDataValue(STT_CMD_PARA_DvmFile, strDvmFile);

	CString strName;

	if (strDvmFile.Find(_T("/")) > 0)
	{
		strName = GetFileTitleFromFilePath(strDvmFile, '/');
	}
	else
	{
		strName = GetFileTitleFromFilePath(strDvmFile);
	}

	m_pGuideBook->SetGuideBookName(strName);

	CDataGroup* pCommCfg = m_pGuideBook->GetCommConfig(FALSE);
	ASSERT(pCommCfg != NULL);

	if (pCommCfg != NULL)
	{
		pCommCfg->SetDataValue(STT_CMD_PARA_DvmFile, strDvmFile);
		pCommCfg->SetDataValue(STT_CMD_PARA_DeviceSN, strName);
	}

	//重新导入模型，如果遥测参数映射不为空，则需要清空。
	if (m_pAinDataMapCfg != NULL)
	{
		delete m_pAinDataMapCfg;
		m_pAinDataMapCfg = NULL;
	}

	if (nIsDvmMap == 1)
	{
		return GenerateItemsOnly_ImportDvmFile_DvmMap(strDvmFile);
	}

	if (IsGuideBookHasDvm())
	{
		return GenerateItemsOnly_ImportDvmFile_HasDvm(strDvmFile);
	}

	return GenerateItemsOnly_ImportDvmFile_NoDvm(strDvmFile);
}

//使用模型映射，暂不实现
long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile_DvmMap(const CString &strDvmFile)
{
	if (! IsGuideBookHasDvm())
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Import-Dvm-File失败！模板中没有模型，无法映射！"));
		return -1;
	}

	return 0;
}

//不模型映射，只模型替换。且模板中已经存在模型了
//模板中已经存在模型时，在原有通讯命令存在的项目，以新模型。创建同类型的通讯命令，并删除原通讯命令
long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile_HasDvm(const CString &strDvmFile)
{
	Init_DvmDevice(strDvmFile);

	if (m_pItems_ImportDvm == NULL)
	{
		m_pItems_ImportDvm = new CItems();
		m_pItems_ImportDvm->m_strID = STT_CMD_PARA_generate_items_import_dvm_file;
		m_pItems_ImportDvm->m_strName = g_sLangTxt_ImportDvm/*_T("导入模型")*/;
	}

	FreeItems_ImportDvm(FALSE);

	CDevice *pDevice = m_pGuideBook->GetDevice();
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();
		
		if (! Gb_IsItemBaseClassID(nClassID))
		{
			continue;
		}

		CGbItemBase *pItemBase = (CGbItemBase *)pObj;
		GenerateItemsOnly_ImportDvmFile_HasDvm(pItemBase);

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItems = (CItems *)pObj;
			GenerateItemsOnly_ImportDvmFile_HasDvm_Ex(pItems);  //递归遍历
		}
	}

	FreeItems_DevReset();

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile_HasDvm(CGbItemBase *pGbItemParent)
{
	if (! pGbItemParent->IsHasChildItem(GBCLASSID_COMMCMD))
	{
		//没有通讯命令子项目
		return 0;
	}

	CExBaseList oListCommCmds, oListGbCommCmdConfigs;
	pGbItemParent->GetChildItem(GBCLASSID_COMMCMD, &oListCommCmds);   //筛选出所有的通讯命令项目
	GetGbCommCmdConfigs(&oListCommCmds, &oListGbCommCmdConfigs);  //从通讯命令配置文件中，筛选出存在的通讯命令类型

	pGbItemParent->DeleteChildItem_Commcmd(FALSE);  //删除原有的所有通讯命令
	oListCommCmds.RemoveAll();

	CItems* pItems = new CItems();  //用于存放新增通讯命令的分类，本身不放到模板中
	CString strItemPath;
	strItemPath = pGbItemParent->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
	pItems->m_strID = strItemPath;  //ID存放父项目的路径，用于返回应答后，上位机将新增通讯命令添加到对应的父项目
	pItems->m_strName = pGbItemParent->m_strName;
	m_pItems_ImportDvm->AddNewChild(pItems);

	POS pos = oListGbCommCmdConfigs.GetHeadPosition();

	while (pos != NULL)
	{
		CGbCommCmd *pGbCmd = (CGbCommCmd *)oListGbCommCmdConfigs.GetNext(pos);
		GenerateItemsOnly_ImportDvmFile_HasDvm(pGbItemParent, pItems, pGbCmd);
	}

	oListGbCommCmdConfigs.RemoveAll();
	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile_HasDvm_Ex(CGbItemBase *pGbItemParent)
{
	POS pos = pGbItemParent->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pGbItemParent->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (! Gb_IsItemBaseClassID(nClassID))
		{
			continue;
		}

		CGbItemBase *pItemBase = (CGbItemBase *)pObj;
		GenerateItemsOnly_ImportDvmFile_HasDvm(pItemBase);

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItems = (CItems *)pObj;
			GenerateItemsOnly_ImportDvmFile_HasDvm_Ex(pItems);  //递归遍历
		}
	}

	return 0;
}

//形参pItems，为返回报文的CItems节点
long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile_HasDvm(CGbItemBase *pGbItemParent, CItems* pItems, CGbCommCmd *pGbCmd)
{
	CExBaseList oListDataset;
	GetDatasetsByGbCommCmd(&oListDataset, pGbCmd);

	if (IsItemDevReset(pGbItemParent))
	{
		//如果是装置复归态，则启用装置复归
		if (pGbCmd->m_strID == _T("WriteEna")
			|| pGbCmd->m_strID == _T("WriteSetting"))
		{
			//1=定值；2=压板
			UINT nType = 1;

			if (pGbCmd->m_strID ==_T("WriteEna"))
			{
				nType = 2;
			}

			long nRet = CreateCommCmds_Write_ByDatasets(&oListDataset, nType, pGbItemParent, TRUE, pItems);
			oListDataset.RemoveAll();
			return nRet;
		}
	}

	UINT nClassID = pGbItemParent->GetClassID();
	POS pos = oListDataset.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)oListDataset.GetNext(pos);
		CCommCmd *pNewCommCmd = new CCommCmd();
		pNewCommCmd->m_strRwOptr = pGbCmd->m_strGbRwOptr;
		pNewCommCmd->m_strName = pGbCmd->m_strName;
		pNewCommCmd->m_strID = pGbCmd->m_strID;
		pNewCommCmd->m_strCommCmdID = pGbCmd->m_strID;
		pGbItemParent->AddNewChild(pNewCommCmd, TRUE);
		pNewCommCmd->InitAfterRead();
		pItems->AddTail(pNewCommCmd);

		CCmd *pCmd = pNewCommCmd->GetCmd();
		pCmd->m_strDelayBeforeCmd = _T("2000");
		pCmd->m_strDelayAfterCmd = _T("2000");
		CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
		pCmd->m_strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;

		if (nClassID == GBCLASSID_MACROTEST
			|| nClassID == GBCLASSID_SAFETY
			|| nClassID == GBCLASSID_SYSPARAEDIT)
		{
			pNewCommCmd->m_bIsSubItem = TRUE;
			pGbItemParent->m_oSubGbItems.AddTail(pNewCommCmd);
		}

		//添加通讯命令配置中携带的参数
		POS posPara = pGbCmd->GetHeadPosition();

		while (posPara != NULL)
		{
			CGbCommCmdPara *pPara = (CGbCommCmdPara *)pGbCmd->GetNext(posPara);
			pCmd->AddValue(pPara->m_strID, pPara->m_strValue);
		}

		if (pGbCmd->m_strGbRwOptr != _T("write"))
		{
			continue;
		}

		//对于写指令，添加通讯命令参数
		posPara = pDataset->GetHeadPosition();

		while (posPara != NULL)
		{
			CDvmData *pData = (CDvmData *)pDataset->GetNext(posPara);

			//控制字和压板，全部退掉
			if (IsDvmData_BOOL(pData))
			{
				if (pData->m_strName.Find(_T("远方")) >= 0)
				{
					//远方压板
					//此处添加到通讯命令，是为了保持参数和实际界面保持一致。
					pCmd->AddValue(pData->m_strID, _T("1"));
					continue;
				}

				pCmd->AddValue(pData->m_strID, _T("0"));
			}
		}
	}

	oListDataset.RemoveAll();
	return 0;
}

//不模型映射，只模型替换。且模板中不存在模型了
//模板中不存在模型时，只在rootnode的CItems节点，自动添加测试前、后准备，并添加修改定值、投退压板的通讯命令
long CGbItemsGenTool::GenerateItemsOnly_ImportDvmFile_NoDvm(const CString &strDvmFile)
{
	Init_DvmDevice(strDvmFile);

	if (m_pItems_ImportDvm == NULL)
	{
		m_pItems_ImportDvm = new CItems();
		m_pItems_ImportDvm->m_strID = STT_CMD_PARA_generate_items_import_dvm_file;
		m_pItems_ImportDvm->m_strName = g_sLangTxt_ImportDvm/*_T("导入模型")*/;
	}

	FreeItems_ImportDvm(FALSE);

	return 0;
}

/*
<group id="AinRatios" name="采样变比信息">
	<data name="装置采样" id="DevMeas" value="1" data-type=""/>【装置采样是一次值、还是二次值。取值：1|2】
	<data name="PT一次侧" id="PtPrimary" value="220" data-type=""/>【PT一次侧单位为kV】
	<data name="Pt二次侧" id="PtSecondary" value="100" data-type=""/>【PT二次侧单位为V】
	<data name="Ct一次侧" id="CtPrimary" value="" data-type=""/>
	<data name="Ct二次侧" id="CtSecondary" value="" data-type=""/>【CT一次、二次侧单位均为A】
</group>
*/
long CGbItemsGenTool::GenerateItemsOnly_AinDataMap(CDataGroup *pAinDataMapCfg, CDataGroup *pAinRatios)
{
	if (pAinDataMapCfg == NULL)
	{
		return -1;
	}

	if (m_pAinDataMapCfg != NULL)
	{
		delete m_pAinDataMapCfg;
		m_pAinDataMapCfg = NULL;
	}

	m_pGuideBook->SetAinDataMapCfg(pAinDataMapCfg);
	m_pGuideBook->SetAinRatios(pAinRatios);
	m_pAinDataMapCfg = new CDataGroup();
	m_pAinDataMapCfg->AppendCloneEx(*pAinDataMapCfg, TRUE);

	//这个临时链表，存的是所有遥测的rootnode
	CExBaseList oListAinItems;
	long nCount = GetAllAinItems(&oListAinItems);

	if (nCount == 0)
	{
		return -2;
	}

	POS pos = oListAinItems.GetHeadPosition();

	while (pos != NULL)
	{
		CItems *pItems = (CItems *)oListAinItems.GetNext(pos);
		GenerateItemsOnly_AinDataMap(pItems, pAinDataMapCfg);
	}

	oListAinItems.RemoveAll();
	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_AinDataMap(CItems *pItems, CDataGroup *pAinDataMapCfg)
{
	CExBaseList oListCommCmds;
	pItems->GetChildItem(GBCLASSID_COMMCMD, &oListCommCmds, TRUE);
	POS pos = oListCommCmds.GetHeadPosition();

	while (pos != NULL)
	{
		CCommCmd *pCommCmd = (CCommCmd *)oListCommCmds.GetNext(pos);
		GenerateItemsOnly_AinDataMap(pCommCmd, pAinDataMapCfg);
	}

	oListCommCmds.RemoveAll();
	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_AinDataMap(CCommCmd *pCommCmd, CDataGroup *pAinDataMapCfg)
{
	CString strItemPath;
	strItemPath = pCommCmd->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

	//初始备份的通讯命令，没有进行过遥测参数、数据集配置的
	CCommCmd *pCommCmdBk = (CCommCmd *)m_oListAinCommCmds.FindByID(strItemPath);

	if (pCommCmdBk != NULL)
	{
		if (! pCommCmdBk->IsEqualChildren(pCommCmd))
		{
			//初始备份的通讯命令与模板中现有的通讯命令不一致。
			//说明不是第一次遥测参数配置，先将模板中的通讯参数，还原会初始参数
			CString strID = pCommCmd->m_strID;
			pCommCmdBk->CopyEx((CExBaseObject *)pCommCmd, TRUE, TRUE);
			pCommCmd->m_strID = strID;
		}
	}

	if (m_pItems_AinCfg == NULL)
	{
		m_pItems_AinCfg = new CItems();
		m_pItems_AinCfg->m_strID = STT_CMD_PARA_generate_items_ain_data_map;
	}

	CItems *pItems = new CItems();
	pItems->m_strID = strItemPath;
	m_pItems_AinCfg->AddNewChild(pItems);

	CCmd *pCmd = pCommCmd->GetCmd();
	CItemRsltExprRun* pRsltExpr = pCommCmd->GetRsltExpr();

	CString strDsPath;
	GenerateItemsOnly_AinDataMap(pRsltExpr, pAinDataMapCfg, strDsPath);
	pItems->AddTail(pCommCmd);

	if (strDsPath.GetLength() > 0)
	{
		pCmd->m_strDatasetPath = strDsPath;
	}

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_AinDataMap(CXExprNode* pExprNode, CDataGroup *pAinDataMapCfg, CString &strDsPath)
{
	POS pos = pExprNode->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pExprNode->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRNODE)
		{
			CXExprNode *pNode = (CXExprNode *)pObj;
			GenerateItemsOnly_AinDataMap(pNode, pAinDataMapCfg, strDsPath);
		}
		else if(nClassID == XEXPRCLASSID_CXEXPRCMP)
		{
			CXExprCmp *pExprCmp = (CXExprCmp *)pObj;
			CXExprValue1 *pValue1 = pExprCmp->GetExprValue1();
			CXExprValue2 *pValue2 = pExprCmp->GetExprValue2();

			GenerateItemsOnly_AinDataMap(pValue1, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pValue2, pAinDataMapCfg, strDsPath);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERROR)
		{
			CXExprError *pExprError = (CXExprError *)pObj;
			CXExprValue* pExprValue = pExprError->GetExprValue();
			CXExprValueStd* pExprValueStd = pExprError->GetExprValueStd();
			CXExprValueError* pExprValueError = pExprError->GetExprValueError();

			GenerateItemsOnly_AinDataMap(pExprValue, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueStd, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueError, pAinDataMapCfg, strDsPath);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERROREX)
		{
			CXExprErrorEx *pExprErrorEx = (CXExprErrorEx *)pObj;
			CXExprValue* pExprValue = pExprErrorEx->GetExprValue();
			CXExprValueStd* pExprValueStd = pExprErrorEx->GetExprValueStd();
			CXExprValueErrorRel* pExprValueErrorRel = pExprErrorEx->GetExprValueErrorRel();
			CXExprValueErrorAbs* pExprValueErrorAbs = pExprErrorEx->GetExprValueErrorAbs();

			GenerateItemsOnly_AinDataMap(pExprValue, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueStd, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueErrorRel, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueErrorAbs, pAinDataMapCfg, strDsPath);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRRANGE)
		{
			CXExprRange *pExprRange = (CXExprRange *)pObj;
			CXExprValue *pValue = pExprRange->GetExprValue();
			CXExprValueMin *pValueMin = pExprRange->GetExprValueMin();
			CXExprValueMax *pValueMax = pExprRange->GetExprValueMax();

			GenerateItemsOnly_AinDataMap(pValue, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pValueMin, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pValueMax, pAinDataMapCfg, strDsPath);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECAL)
		{
			CXExprValueCal *pExprValueCal = (CXExprValueCal *)pObj;
			CXExprValue1 *pValue1 = pExprValueCal->GetExprValue1();
			CXExprValue2 *pValue2 = pExprValueCal->GetExprValue2();
			CXExprValueStd* pExprValueStd = pExprValueCal->GetExprValueStd();
			CXExprValueError* pExprValueError = pExprValueCal->GetExprValueError();

			GenerateItemsOnly_AinDataMap(pValue1, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pValue2, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueStd, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueError, pAinDataMapCfg, strDsPath);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALEX)
		{
			CXExprValueCalEx *pExprValueCalEx = (CXExprValueCalEx *)pObj;
			CXExprValue1 *pValue1 = pExprValueCalEx->GetExprValue1();
			CXExprValue2 *pValue2 = pExprValueCalEx->GetExprValue2();
			CXExprValueStd* pExprValueStd = pExprValueCalEx->GetExprValueStd();
			CXExprValueErrorRel* pExprValueErrorRel = pExprValueCalEx->GetExprValueErrorRel();
			CXExprValueErrorAbs* pExprValueErrorAbs = pExprValueCalEx->GetExprValueErrorAbs();

			GenerateItemsOnly_AinDataMap(pValue1, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pValue2, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueStd, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueErrorRel, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueErrorAbs, pAinDataMapCfg, strDsPath);
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRERRORCOMBINED)
		{
			CXExprErrorCombined *pExprErrorCombined = (CXExprErrorCombined *)pObj;
			CXExprValue* pExprValue = pExprErrorCombined->GetExprValue();
			CXExprValueStd* pExprValueStd = pExprErrorCombined->GetExprValueStd();
			CXExprValueErrorRel* pExprValueErrorRel = pExprErrorCombined->GetExprValueErrorRel();
			CXExprValueErrorAbs* pExprValueErrorAbs = pExprErrorCombined->GetExprValueErrorAbs();

			GenerateItemsOnly_AinDataMap(pExprValue, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueStd, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueErrorRel, pAinDataMapCfg, strDsPath);
			GenerateItemsOnly_AinDataMap(pExprValueErrorAbs, pAinDataMapCfg, strDsPath);
		}
	}

	return 0;
}

/*value属性记录数据ID。data-type记录数据集路径
<group id="AinDataMapCfg" name="遥测数据映射配置">
	<data name="A相电流" id="MIa" value="" data-type=""/>
	<data name="B相电流" id="MIb" value="" data-type=""/>
	<data name="C相电流" id="MIc" value="" data-type=""/>
	<data name="A相电压" id="MUa" value="" data-type=""/>
	<data name="B相电压" id="MUb" value="" data-type=""/>
	<data name="C相电压" id="MUc" value="" data-type=""/>
	<data name="总有功功率" id="P" value="" data-type=""/>
	<data name="总无功功率" id="Q" value="" data-type=""/>
	<data name="功率因数" id="cos" value="" data-type=""/>
	<data name="频率" id="F" value="" data-type=""/>
</group>
*/
long CGbItemsGenTool::GenerateItemsOnly_AinDataMap(CXExprValue *pExprValue, CDataGroup *pAinDataMapCfg, CString &strDsPath)
{
	CDvmData *pDataCfg = (CDvmData *)pAinDataMapCfg->FindByID(pExprValue->m_strValueID);

	if (pDataCfg != NULL)
	{
		if (pDataCfg->m_strValue.IsEmpty())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("遥测通讯参数配置，参数数据【%s】的映射为空！")
				, pExprValue->m_strValueID.GetString());
			return -1;
		}

		pExprValue->m_strValueID = pDataCfg->m_strValue;

		//2023-9-4  由于传递报文时，只传递了name、id、value、data-type。
		//记录数据集路径的属性，由format改为data-type
		if (pDataCfg->m_strDataType.GetLength() > 0)
		{
			//暂时这样处理。这样处理存在以下问题：映射的数据，是不同数据集的，第一次映射的会被第二次映射的覆盖
			//必须保证一个结果判断里面，用到的判断参数，都是来自同一个数据集。
			strDsPath = pDataCfg->m_strDataType;
		}
	}

	return 0;
}
/*
形参：pGenerateItems如下：
<group name="generate-items" id="generate-items" data-type="generate-items" value="cmd">
	<data name="" id="ParentItemsPath" data-type="string" value=""/> 父项目分类-名称
	<data name="" id="macro-name" data-type="string" value="距离保护"/>测试功能的名称   【根据功能名称，筛选对应的定值、压板、控制字】
	<group id="comm-cmd" name="通信命令生成配置">
		<group id="_BeforeTest_" name="通信前准备">
			<data id="ReadSetting" name="读定值"/>
			<data id="WriteSetting" name="修改定值"/>
			<data id="ReadEna" name="读软压板"/>
			<data id="WriteEna" name="修改软压板"/>
			<data id="ReadParameter" name="读装置参数"/>
			<data id="WriteParameter" name="修改装置参数"/>
			<data id="RegisterReport" name="启动报告"/>
			<data id="UnRegisterReport" name="停止报告"/>
		</group>
		<group id="_AfterTest_" name="通信后恢复">
			<data id="WriteSetting" name="修改定值"/>
			<data id="WriteEna" name="修改软压板"/>
			<data id="WriteParameter" name="修改装置参数"/>
			<data id="UnRegisterReport" name="停止报告"/>
		</group>
	</group>
</group>

应答报文结构如下：m_oGroupCmdReply对应报文中的ID为“comm-cmd”的group
<sys-state name="" id="GenerateItems" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="3" unit=""/>
		<group id="comm-cmd" name="通信命令生成配置">
			<group id="_BeforeTest_" name="通信前准备">
				<group id="ReadSetting" data-type="read" value="">
					<group id="PT2201APROT$LLN0$dsSetting1" data-type="string"/>
					<group id="PT2201APROT$LLN0$dsSetting2" data-type="string"/>
					<!--读指令，每个子group都对应一个数据集，ID = 数据集路径-->
				</group>
				<group id="WriteSetting" name="修改定值">
					<group name="" id="PROT$LLN0$dsSetting1" data-type="" >
						<data name="" id="" data-type="" value=""/>
						...............................
					</group>
				</group>
				<group id="WriteSetting" name="修改定值">
					<group name="" id="PROT$LLN0$dsSetting2" data-type="" >
						<data name="" id="" data-type="" value=""/>
						...............................
					</group>
				</group>
				<!--写指令，每个数据集都对应一个大的group，有一个ID为数据集路径的子group，该子group携带data-->
				<group id="RegisterReport" name="启动报告">  
					<group name="" id="PROT$LLN0$dsTripInfo" data-type="" />
					...............................
				</group>
				<!--register命令：与读命令结构一致；-->
			</group>
			<group id="_AfterTest_" name="通信后恢复">
				...............................
			</group>
		</group>
	</paras>
</sys-state>
*/
long CGbItemsGenTool::GenerateItemsOnly_CmdWzd(CDataGroup *pGenerateItems)
{
	m_oGroupCmdWzdReply.DeleteAll();
	
	if (pGenerateItems == NULL)
	{
		return -1;
	}

	CDataGroup *pCommCmd = (CDataGroup *)pGenerateItems->FindByID(STT_CMD_PARA_CommCmd);

	if (pCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("通讯命令生成向导，报文缺少【comm-cmd】节点，生成失败！"));
		return -1;
	}

	CString strMacroName, strTestClass;
	pGenerateItems->GetDataValue(STT_CMD_PARA_MACRO_NAME, strMacroName);
	pGenerateItems->GetDataValue(STT_CMD_PARA_TestClass, strTestClass);

	if (strTestClass.GetLength() > 0)
	{
		m_strTestClass = strTestClass;
	}

	CDataGroup *pBeforeTest = (CDataGroup *)pCommCmd->FindByID(STT_CMD_PARA_Before_Test);

	if (pBeforeTest != NULL)
	{
		CDataGroup *pBFT = m_oGroupCmdWzdReply.AddNewGroup(g_sLangTxt_BeforeComm/*_T("通信前准备")*/, STT_CMD_PARA_Before_Test, _T(""));
		GenerateItemsOnly_Cmd_Ex(pBFT, pBeforeTest, strMacroName);
	}

	CDataGroup *pAfterTest = (CDataGroup *)pCommCmd->FindByID(STT_CMD_PARA_After_Test);

	if (pAfterTest != NULL)
	{
		CDataGroup *pAFT = m_oGroupCmdWzdReply.AddNewGroup(g_sLangTxt_IAfterComm/*_T("通信后恢复")*/, STT_CMD_PARA_After_Test, _T(""));
		GenerateItemsOnly_Cmd_Ex(pAFT, pAfterTest, strMacroName);
	}

	if (pBeforeTest == NULL && pAfterTest == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("通讯命令生成向导，报文缺少【_BeforeTest_ & _AfterTest_】节点，生成失败！"));
		return -1;
	}

	return 0;
}

void CGbItemsGenTool::GenerateItemsOnly_Cmd_Ex(CDataGroup *pReply, CDataGroup *pParas, const CString &strMacroName)
{
	POS pos = pParas->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pParas->GetNext(pos);  //一个data，为一个通讯命令
		CGbCommCmd *pCmd = (CGbCommCmd *)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pData->m_strID);

		if (pCmd == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("装置通讯命令配置文件中，没有通讯命令【%s】"), pData->m_strID.GetString());
			continue;
		}

		if (pCmd->IsRegister())
		{
			GenerateItemsOnly_Cmd_Ex_register(pReply, pCmd);
			continue;
		}

		if (pCmd->IsWrite())
		{
			GenerateItemsOnly_Cmd_Ex_write(pReply, pCmd, strMacroName);
			continue;
		}

		//去掉write和register指令，还有操作模式为none和read的。都可以按照read来处理
		GenerateItemsOnly_Cmd_Ex_read(pReply, pCmd, strMacroName);
	}
}

//数据集配置为all的通讯命令，需要从通讯命令向导配置中，获取对应的数据集
/*
<group id="RegisterReport" name="启动报告">  
	<group name="" id="PROT$LLN0$dsTripInfo" data-type="" />
	...............................
</group>
<!--register命令：与读命令结构一致；-->
*/
void CGbItemsGenTool::GenerateItemsOnly_Cmd_Ex_register(CDataGroup *pReply, CGbCommCmd *pCmd)
{
	//查找所有的数据集
	CStringArray strKeyArray;
	CDataGroup *pTestClass = (CDataGroup *)m_oCommCmdWzdCfg.FindByID(m_strTestClass);

	if (pTestClass != NULL)
	{
		CDataGroup *pCmdCfg = (CDataGroup *)pTestClass->FindByID(pCmd->m_strID);   //通讯命令的ID

		if (pCmdCfg != NULL)
		{
			POS pos = pCmdCfg->GetHeadPosition();

			while (pos != NULL)
			{
				CDvmData *pData = (CDvmData *)pCmdCfg->GetNext(pos);  //通讯命令关联的数据集的ID
				GetdsKey(strKeyArray, pData->m_strID);
			}
		}
	}

	if (strKeyArray.GetCount() == 0)
	{
		strKeyArray.Add(_T("all"));
	}

	CExBaseList oListDataset;
	m_oDvmDevice.GetDatasetList(strKeyArray, oListDataset);  //根据关联的数据集ID，查找所有的数据集

	CDataGroup *pGrp = pReply->AddNewGroup(pCmd->m_strName, pCmd->m_strID, _T("register"));   //一个大的group
	POS pos = oListDataset.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)oListDataset.GetNext(pos);
		CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();

		pGrp->AddNewGroup(pDataset->m_strName, pLd->m_strID + _T("$") + pDataset->m_strID, _T(""), FALSE);   //一个数据集，对应一个小的group
	}

	oListDataset.RemoveAll();
}

/*
<group id="WriteSetting" name="修改定值">
	<group name="" id="PROT$LLN0$dsSetting1" data-type="" >
		<data name="" id="" data-type="" value=""/>
		...............................
	</group>
	</group>
<group id="WriteSetting" name="修改定值">
	<group name="" id="PROT$LLN0$dsSetting2" data-type="" >
		<data name="" id="" data-type="" value=""/>
		...............................
	</group>
</group>
<!--写指令，每个数据集都对应一个大的group，有一个ID为数据集路径的子group，该子group携带data-->
*/
void CGbItemsGenTool::GenerateItemsOnly_Cmd_Ex_write(CDataGroup *pReply, CGbCommCmd *pCmd, const CString &strMacroName)
{
	CExBaseList oListDataset;
	GetDatasetsByGbCommCmd(&oListDataset, pCmd);
	POS pos = oListDataset.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)oListDataset.GetNext(pos);
		CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();

		CDataGroup *pGrp = pReply->AddNewGroup(pCmd->m_strName, pCmd->m_strID, _T("write"), FALSE);//此处若是多个数据集，则添加的group的ID是重复的。在生成测试项时处理测试项的ID
		CDataGroup *pNew = pGrp->AddNewGroup(pDataset->m_strName, pLd->m_strID + _T("$") + pDataset->m_strID, _T(""), FALSE);
		//此处需要根据功能名称，筛选出关联的数据
		pNew->AppendClone(pDataset);  //暂时将数据集下所有的data都放过去
	}

	oListDataset.RemoveAll();
}

/*
<group id="ReadSetting" data-type="read" value="">
	<group id="PT2201APROT$LLN0$dsSetting1" data-type="string"/>
	<group id="PT2201APROT$LLN0$dsSetting2" data-type="string"/>
<!--读指令，每个子group都对应一个数据集，ID = 数据集路径-->
</group>
*/
void CGbItemsGenTool::GenerateItemsOnly_Cmd_Ex_read(CDataGroup *pReply, CGbCommCmd *pCmd, const CString &strMacroName)
{
	CString strDatasetKey = pCmd->m_strGbDataID;
	CExBaseList oListDataset;
	CDataGroup *pNew = NULL;
	pNew = pReply->AddNewGroup(pCmd->m_strName, pCmd->m_strID, _T("read"));

	long nPos = strDatasetKey.Find(_T("ds"));

	if (nPos < 0)
	{
		m_oDvmDevice.GetDatasetList(strDatasetKey, oListDataset);
	}
	else
	{
		m_oDvmDevice.GetDatasetList(strDatasetKey.Mid(nPos + 2), oListDataset);
	}

	if (oListDataset.GetCount() == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("读指令，模型中找不到数据集【%s】"), strDatasetKey.GetString());

		//没有找到对应的数据集，说明命令关联的dataset属性为none、report等
		pNew->AddNewGroup(pCmd->m_strGbDataID, pCmd->m_strGbDataID, _T(""));
	}
	else
	{
		POS pos = oListDataset.GetHeadPosition();

		while (pos != NULL)
		{
			CDvmDataset *pDataset = (CDvmDataset *)oListDataset.GetNext(pos);
			CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();

			pNew->AddNewGroup(pDataset->m_strName, pLd->m_strID + _T("$") + pDataset->m_strID, _T(""), FALSE);  //每个数据集，作为一个子group添加
		}
	}

	oListDataset.RemoveAll();
}

long CGbItemsGenTool::GenerateItemsOnly_Cmd_Add(CDataGroup *pGenerateItems, CSttContents *pContents)
{
	if (pGenerateItems == NULL)
	{
		return -1;
	}

	CDataGroup *pCommCmd = (CDataGroup *)pGenerateItems->FindByID(STT_CMD_PARA_CommCmd);

	if (pCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("通讯命令生成向导，报文缺少【comm-cmd】节点，生成失败！"));
		return -1;
	}

	CString strParentItemsPath;
	pGenerateItems->GetDataValue(STT_CMD_PARA_ParentItemsPath, strParentItemsPath);

	CGbItemBase *pItemParent = (CGbItemBase*)Gb_GetItem(m_pGuideBook, strParentItemsPath);

	if (pItemParent == NULL)
	{
		return -1;
	}

	POS pos = pCommCmd->GetHeadPosition();
	CGbItemBase *pNewCommCmd = NULL;

	while (pos != NULL)
	{
		CDataGroup *pCmdGrp = (CDataGroup *)pCommCmd->GetNext(pos);
		pNewCommCmd = GenGbCommCmd_Ex(pItemParent, pCmdGrp);

		//对于单个添加的通讯命令，如果通讯配置文件中配置了参数，则将配置的参数作为通讯命令的默认参数
		CCommCmd *pCommCmd = (CCommCmd *)pNewCommCmd;
		CGbCommCmd *pGbCmd = (CGbCommCmd *)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);
		CCmd *pCmd = pCommCmd->GetCmd();

		if (pGbCmd != NULL)
		{
			POS posPara = pGbCmd->GetHeadPosition();

			while (posPara != NULL)
			{
				CGbCommCmdPara *pPara = (CGbCommCmdPara *)pGbCmd->GetNext(posPara);
				pCmd->AddValue(pPara->m_strID, pPara->m_strValue);
			}
		}
	}

	if (pContents != NULL)
	{
		if (pCommCmd->GetCount() > 1)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, _T("【异常！】通讯命令生成向导，报文中【comm-cmd】节点包含多个通讯命令"));
		}

		UpdateItem_CommCmd(pNewCommCmd, pContents);
	}
	else
	{
		//单个添加的指令，指定一个默认的数据集路径
		CDataGroup *pCmdCfgSingle = (CDataGroup *)m_oSttCommCmdCfg.FindByID(STT_CMD_PARA_CMDSINGLE);

		if (pCmdCfgSingle == NULL)
		{
			return 0;
		}

		CCommCmd *pCommCmd = (CCommCmd *)pNewCommCmd;
		CDvmData *pCmdCfgData = (CDvmData *)pCmdCfgSingle->FindByID(pCommCmd->m_strCommCmdID);

		if (pCmdCfgData == NULL)
		{
			return 0;
		}

		CExBaseList oListDataset;

		long nPos = pCmdCfgData->m_strFormat.Find(_T("ds"));

		if (nPos < 0)
		{
			m_oDvmDevice.GetDatasetList(pCmdCfgData->m_strFormat, oListDataset);
		}
		else
		{
			m_oDvmDevice.GetDatasetList(pCmdCfgData->m_strFormat.Mid(nPos + 2), oListDataset);
		}

		CDvmDataset *pDataset = (CDvmDataset *)oListDataset.GetHead();

		if (pDataset != NULL)
		{
			CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
			CCmd *pCmd = pCommCmd->GetCmd();
			pCmd->m_strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID; 
		}

		oListDataset.RemoveAll();
	}

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_Macro_Add(CDataGroup *pGenerateItems, CSttContents *pContents)
{
	if (pGenerateItems == NULL)
	{
		return -1;
	}

	CString strParentItemsPath, strMacroID, strItemName, strItemID;
	pGenerateItems->GetDataValue(STT_CMD_PARA_ParentItemsPath, strParentItemsPath);
	pGenerateItems->GetDataValue(STT_CMD_PARA_MacroID, strMacroID);
	pGenerateItems->GetDataValue(STT_CMD_PARA_ItemName, strItemName);
	pGenerateItems->GetDataValue(STT_CMD_PARA_ItemID, strItemID);

	CGbItemBase *pItemParent = (CGbItemBase*)Gb_GetItem(m_pGuideBook, strParentItemsPath);

	if (pItemParent == NULL)
	{
		return -1;
	}

	CMacroTest *pMacroTest = new CMacroTest;
	pMacroTest->InitAfterRead();
	pItemParent->AddNewChild(pMacroTest);

	//CSttMacroTestUI_TestMacroUIs *pUIs = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIs();
	//CSttMacroTestUI_TestMacroUI *pTestMacroUI = (CSttMacroTestUI_TestMacroUI *)pUIs->FindByID(strMacroID);	

	//pMacroTest->m_strName = pTestMacroUI->m_strName;
	pMacroTest->m_strID = strItemID;
	pMacroTest->m_strName = strItemName;

	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	//pMacroTest->InitMacroID();
	pMacroTestPara->SetMacroID(strMacroID);
	pMacroTestPara->InitAfterRead();


	if (strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		SetItemPara_ChMapsConfig(pContents);
	}
	else if (strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		SetItemPara_IecConfig(pContents);
	}
	else if (strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		GenerateItemsOnly_Macro_Add_SystemConfig(pMacroTest, pContents);
	}
	else
	{
		//其它电气量项目创建
		return 0;
	}

	if (pContents != NULL)
	{
		CTestMacroUiParas *pUIParas = pMacroTest->CreateTestMacroUiParas();

		if (pUIParas != NULL)
		{
			pUIParas->m_strParaText = pContents->m_strText;
		}
	}

	return 0;
}

long CGbItemsGenTool::GenerateItemsOnly_Macro_Add_SystemConfig(CMacroTest *pMacroTest, CSttContents *pContents)
{
	CSttMacro *pSttMacro = new CSttMacro;
	pSttMacro->SetCreateMacroChild(TRUE);
	BSTR bstrText = pContents->m_strText.AllocSysString();
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	pSttMacro->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif

	SetSysParameter(pSttMacro);

	return 0;
}

void CGbItemsGenTool::SetBinaryFileName()
{
	if (m_strDvmFile.IsEmpty())
	{
		return;
	}

	if (m_pGuideBook == NULL)
	{
		return;
	}

	CString strName;

	if (m_strDvmFile.Find(_T("/")) > 0)
	{
		strName = GetFileTitleFromFilePath(m_strDvmFile, '/');
	}
	else
	{
		strName = GetFileTitleFromFilePath(m_strDvmFile);
	}

	m_pGuideBook->SetGuideBookName(strName);
	
#ifndef _PSX_QT_LINUX_
	CString strBinFileName;
	SYSTEMTIME oTime;
	::GetLocalTime(&oTime);
	strBinFileName.Format(_T("_(%04d%02d%02d_%02d%02d%02d).gbrpt")
		, oTime.wYear, oTime.wMonth, oTime.wDay
		, oTime.wHour, oTime.wMinute, oTime.wSecond);
	strBinFileName = strName + strBinFileName;
	strBinFileName = _P_GetWorkspacePath() + strBinFileName;
	CTestControlBase *pTestControl = (CTestControlBase *)m_pGuideBook->GetParent();
	pTestControl->SetBinaryFile(strBinFileName);
#endif
}

void CGbItemsGenTool::GetdsKey(CStringArray &strKeyArray, const CString &strKey)
{
	long nPos = strKey.Find(_T("ds"));

	if (nPos < 0)
	{
		strKeyArray.Add(strKey);
	}
	else
	{
		strKeyArray.Add(strKey.Mid(nPos + 2));
	}
}

CDevice* CGbItemsGenTool::InitGuideBookForGenerateItemsOnly()
{
	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		pDevice = new CDevice();
		m_pGuideBook->AddNewChild(pDevice);
		pDevice->InitAfterRead();
	}

	return pDevice;
}

BOOL CGbItemsGenTool::IsDvmData_BOOL(CDvmData *pData)
{
	if (pData == NULL)
	{
		return FALSE;
	}

	CDvmValue *pFind = pData->GetDataValue();   //返回除$t  $q之外的第一个pDvmData子对象

	if (pFind == NULL)
	{
		return (pData->m_strDataType == _T("BOOL"));
	}

	return (pFind->m_strDataType == _T("BOOL"));
}

void CGbItemsGenTool::ErrorLogicType(CXExprErrorEx *pErrorEx,long nErrorLogic)
{
	switch(nErrorLogic)
	{
	case ERROR_LOGIC_ABS:
		pErrorEx->m_strMode = _T("abs");
		break;
	case ERROR_LOGIC_REL:
		pErrorEx->m_strMode = _T("real");
		break;
	case ERROR_LOGIC_OR:
		pErrorEx->m_strMode = _T("or");
		break;
	case ERROR_LOGIC_AND:
		pErrorEx->m_strMode = _T("and");
		break;
	default:
		pErrorEx->m_strMode = _T("or");
	}
}


void CGbItemsGenTool::ActionValueGradient(CItemRsltExprRun *pRsltExprRun,long nVarType,long nVarIndexType, const CString &strMacroID)	//动作值递变
{
	CXExprErrorEx *pErrorEx = new CXExprErrorEx;
	pRsltExprRun->AddNewChild(pErrorEx);
	pErrorEx->m_strOptr = _T("<");
	CXExprValueStd* pValueStd = pErrorEx->GetExprValueStd();
	pValueStd->m_strType = _T("report");   //回填报告中去
	pValueStd->m_strValueID = _T("ActSet");
	long nErrorLogic = 0;
	CDvmData *pRelErr = NULL;
	CDvmData *pAbsErr = NULL;

	CXExprValueErrorAbs* pValueErrAbs = pErrorEx->GetExprValueErrorAbs();
	pValueErrAbs->m_strType = _T("number");

	CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
	pAbsErrValue->m_strType = _T("report");

	CXExprValue* pValue = pErrorEx->GetExprValue();
	pValue->m_strType = _T("report");
	pValue->m_strValueID = _T("TripValue");  //动作值的报告数据

	if (strMacroID == STT_CMD_ATS_MACRO_ID_ManualTest
		|| strMacroID == STT_CMD_ATS_MACRO_ID_SequenceManuTest)
	{
		pValue->m_strValueID = _T("ActValue");
	}

 	if (nVarType == Gradient_VarType_Val) //幅值递变
 	{
		if (nVarIndexType == Gradient_VarIndexType_I)
		{
			//电流递变
			CDvmData *pISet = (CDvmData *)m_pUIParasGroup->FindByID(_T("ISet"));  //电流整定动作值
			pValueStd->m_strValue = pISet->m_strValue;
			pValueStd->m_strValueName = g_sLangTxt_ISet/*_T("电流整定动作值(A)")*/;
			CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_ErrorLogic"));  //电流动作值误差判断逻辑

			if (pErrorLogic != NULL)
			{
				nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
			}

			CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
			pValueErrRel->m_strType = _T("number");
			CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
			pRelErrValue->m_strType = _T("report");
			pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_RelErr"));  //电流动作值相对误差限
			pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("IActVal_AbsErr"));  //电流动作值绝对误差限

			pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
			pRelErrValue->m_strValueName = g_sLangTxt_I_RelErr/*_T("电流动作值相对误差(%)")*/;
			pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
			pAbsErrValue->m_strValueName = g_sLangTxt_I_AbsErr/*_T("电流动作值绝对误差(A)")*/;
			pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
			pValueErrRel->m_strValueName = g_sLangTxt_I_ErrRel/*_T("电流动作值相对误差限(%)")*/;
			pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
			pValueErrAbs->m_strValueName = g_sLangTxt_I_ErrAbs/*_T("电流动作值绝对误差限(A)")*/;

			pValue->m_strValueName = g_sLangTxt_I_Act/*_T("电流动作值(A)")*/;
		}
		else if (nVarIndexType == Gradient_VarIndexType_U)
		{
			//电压递变
			CDvmData *pUSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("USet"));  //电压整定动作值
			pValueStd->m_strValue = pUSet->m_strValue;
			pValueStd->m_strValueName = g_sLangTxt_USet/*_T("电压整定动作值(V)")*/;

			CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_ErrorLogic"));  //电压动作值误差判断逻辑

			if (pErrorLogic != NULL)
			{
				nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
			}

			CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
			pValueErrRel->m_strType = _T("number");
			CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
			pRelErrValue->m_strType = _T("report");
			pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_RelErr"));  //电压动作值相对误差限
			pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("UActVal_AbsErr"));  //电压动作值绝对误差限

			pRelErrValue->m_strValueID = _T("TripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
			pRelErrValue->m_strValueName = g_sLangTxt_U_RelErr/*_T("电压动作值相对误差(%)")*/;
			pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
			pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
			pAbsErrValue->m_strValueName = g_sLangTxt_U_AbsErr/*_T("电压动作值绝对误差(V)")*/;
			pValueErrRel->m_strValueName = g_sLangTxt_U_ErrRel/*_T("电压动作值相对误差限(%)")*/;
			pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
			pValueErrAbs->m_strValueName = g_sLangTxt_U_ErrAbs/*_T("电压动作值绝对误差限(V)")*/;

			pValue->m_strValueName = g_sLangTxt_U_Act/*_T("电压动作值(V)")*/;
		}
	}
	else if (nVarType == Gradient_VarType_Ph)
	{
		//相位递变
		CDvmData *pAngleSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("AngleSet"));  //相位整定动作值
		pValueStd->m_strValue = pAngleSet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_AngleSet/*_T("相位整定动作值(°)")*/;
		nErrorLogic = ERROR_LOGIC_ABS;  //相位动作值，只能是绝对误差

		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("AngleActVal_AbsErr"));  //相位动作值绝对误差限
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueName = g_sLangTxt_Angle_AbsErr/*_T("相位动作值绝对误差(°)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_Angle_ErrAbs/*_T("相位动作值绝对误差限(°)")*/;

		pValue->m_strValueName = g_sLangTxt_Angle_Act/*_T("相位动作值(°)")*/;
	}
	else if (nVarType == Gradient_VarType_Freq)
	{
		//频率递变
		CDvmData *pHzSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("HzSet"));  //频率整定动作值
		pValueStd->m_strValue = pHzSet->m_strValue;
		pValueStd->m_strValueName = g_sLangTxt_HzSet/*_T("频率整定动作值(Hz)")*/;
		nErrorLogic = ERROR_LOGIC_ABS;  //频率动作值，只能是绝对误差

		pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("HzActVal_AbsErr"));  //频率动作值绝对误差限
		pAbsErrValue->m_strValueID = _T("TripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
		pAbsErrValue->m_strValueName = g_sLangTxt_Hz_AbsErr/*_T("频率动作值绝对误差(Hz)")*/;
		pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
		pValueErrAbs->m_strValueName = g_sLangTxt_Hz_ErrAbs/*_T("频率动作值绝对误差限(Hz)")*/;

		pValue->m_strValueName = g_sLangTxt_Hz_Act/*_T("频率动作值(Hz)")*/;
	}

	ErrorLogicType(pErrorEx,nErrorLogic);

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalRelMax = NULL;
	CXExprCal *pCalRelMin = NULL;
	CXExprCal *pCalAbsMax = NULL;
	CXExprCal *pCalAbsMin = NULL;

	if (pErrorEx->m_strMode == _T("real"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");
		//pCalRelMax->m_strValueName = _T("相对误差最大值");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");
		//pCalRelMin->m_strValueName = _T("相对误差最小值");
	}
	else if (pErrorEx->m_strMode == _T("abs"))
	{
		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");
		//pCalAbsMax->m_strValueName = _T("绝对误差最大值");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
		//pCalAbsMin->m_strValueName = _T("绝对误差最小值");
	}
	else if (pErrorEx->m_strMode == _T("or") || pErrorEx->m_strMode == _T("and"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TripErrRelVal_Max");
		//pCalRelMax->m_strValueName = _T("相对误差最大值");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TripErrRelVal_Min");
		//pCalRelMin->m_strValueName = _T("相对误差最小值");

		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TripErrAbsVal_Max");
		//pCalAbsMax->m_strValueName = _T("绝对误差最大值");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TripErrAbsVal_Min");
		//pCalAbsMin->m_strValueName = _T("绝对误差最小值");
	}

	//幅值递变
	if (nVarType == Gradient_VarType_Val) //幅值递变
	{
		//电流动作值递变
		if (nVarIndexType == Gradient_VarIndexType_I)
		{
			if (pCalAbsMax != NULL)
			{
				pCalAbsMax->m_strValueName = g_sLangTxt_I_AbsErr_Max/*_T("电流动作值绝对误差最大值(A)")*/;
			}

			if (pCalRelMax != NULL)
			{
				pCalRelMax->m_strValueName = g_sLangTxt_I_RelErr_Max/*_T("电流动作值相对误差最大值(%)")*/;
			}

			if (pCalAbsMin != NULL)
			{
				pCalAbsMin->m_strValueName = g_sLangTxt_I_AbsErr_Min/*_T("电流动作值绝对误差最小值(A)")*/;
			}

			if (pCalRelMin != NULL)
			{
				pCalRelMin->m_strValueName = g_sLangTxt_I_RelErr_Min /*_T("电流动作值相对误差最小值(%)")*/;
			}
		}
		//电压动作值递变
		else if (nVarIndexType == Gradient_VarIndexType_U)
		{
			if (pCalAbsMax != NULL)
			{
				pCalAbsMax->m_strValueName = g_sLangTxt_U_AbsErr_Max/*_T("电压动作值绝对误差最大值(V)")*/;
			}

			if (pCalRelMax != NULL)
			{
				pCalRelMax->m_strValueName = g_sLangTxt_U_RelErr_Max/*_T("电压动作值相对误差最大值(%)")*/;
			}

			if (pCalAbsMin != NULL)
			{
				pCalAbsMin->m_strValueName = g_sLangTxt_U_AbsErr_Min/*_T("电压动作值绝对误差最小值(V)")*/;
			}

			if (pCalRelMin != NULL)
			{
				pCalRelMin->m_strValueName = g_sLangTxt_U_RelErr_Min/*_T("电压动作值相对误差最小值(%)")*/;
			}
		}
	}
	
	//相位递变
	if (nVarType == Gradient_VarType_Ph)
	{
		//相位递变，只有绝对误差
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_Angle_AbsErr_Max/*_T("相位动作值绝对误差最大值(°)")*/;
		}

		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_Angle_AbsErr_Min/*_T("相位动作值绝对误差最小值(°)")*/;
		}
	}
	//频率递变
	if (nVarType == Gradient_VarType_Freq)
	{
		//频率递变，只有绝对误差
		if (pCalAbsMax != NULL)
		{
			pCalAbsMax->m_strValueName = g_sLangTxt_Hz_AbsErr_Max/*_T("频率动作值绝对误差最大值(Hz)")*/;
		}

		if (pCalAbsMin != NULL)
		{
			pCalAbsMin->m_strValueName = g_sLangTxt_Hz_AbsErr_Min/*_T("频率动作值绝对误差最小值(Hz)")*/;
		}
	}
}

void CGbItemsGenTool::ReturnValueGradient(CItemRsltExprRun *pRsltExprRun)	//返回系数
{
	CXExprError *pError = new CXExprError;
	pRsltExprRun->AddNewChild(pError);
	pError->m_strOptr = _T("<");
	pError->m_strMode = _T("abs");  //返回系数固化用绝对误差
	//CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("RetCoef_ErrorLogic"));
	CXExprValueStd* pValueStd = pError->GetExprValueStd();
	pValueStd->m_strType = _T("report");  //回填到报告中去
	pValueStd->m_strValueName = g_sLangTxt_ReturnCoefSet/*_T("返回系数整定值")*/;
	pValueStd->m_strValueID = _T("RetCoefSet");
	CDvmData *pRetCoefSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("RetCoefSet"));  //返回系数整定值
	pValueStd->m_strValue = pRetCoefSet->m_strValue;

	CXExprValue* pValue = pError->GetExprValue();
	pValue->m_strType = _T("report");
	pValue->m_strValueID = _T("ReturnCoef");  //返回系数的报告数据
	pValue->m_strValueName = g_sLangTxt_ReturnCoef_Act/*_T("返回系数")*/;  //返回系数的报告数据

	CXExprValueError* pExprValueError = pError->GetExprValueError();   //误差限
	pExprValueError->m_strType = _T("number");
	CDvmData *pErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("RetCoef_AbsErr"));  //返回系数绝对误差限
	pExprValueError->m_strValue = pErr->m_strValue;
	pExprValueError->m_strValueName = g_sLangTxt_ReturnCoef_ErrAbs/*_T("返回系数绝对误差限")*/;

	CXExprValueErrorRslt* pExprValueErrorRslt = pError->GetExprValueErrorRslt();  //误差结果
	pExprValueErrorRslt->m_strType = _T("report");
	pExprValueErrorRslt->m_strValueID = _T("RetCoefErrVal");
	pExprValueErrorRslt->m_strValueName = g_sLangTxt_ReturnCoef_AbsErr/*_T("返回系数误差值")*/;

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalMax = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMax);
	pCalMax->AddQueryMax(_T("RetCoefErrVal"));
	pCalMax->m_strValueDstID = _T("RetCoefErrVal_Max");
	pCalMax->m_strValueName = g_sLangTxt_RetCoef_AbsErr_Max/*_T("返回系数绝对误差最大值")*/;

	CXExprCal *pCalMin = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMin);
	pCalMin->AddQueryMin(_T("RetCoefErrVal"));
	pCalMin->m_strValueDstID = _T("RetCoefErrVal_Min");
	pCalMin->m_strValueName = g_sLangTxt_RetCoef_AbsErr_Min/*_T("返回系数绝对误差最小值")*/;
}


void CGbItemsGenTool::MaxAngleValueGradient(CItemRsltExprRun *pRsltExprRun)//最大灵敏角
{
	//最大灵敏角判断
	CXExprError *pError1 = new CXExprError;
	pRsltExprRun->AddNewChild(pError1);
	pError1->m_strOptr = _T("<");
	pError1->m_strMode = _T("abs");  //最大灵敏角固化用绝对误差
	CXExprValueStd* pValueStd1 = pError1->GetExprValueStd();
	pValueStd1->m_strType = _T("report");   //回填到报告中去
	pValueStd1->m_strValueName = g_sLangTxt_MaxAngleSet/*_T("最大灵敏角整定值(°)")*/;
	CDvmData *pAngleSet = (CDvmData *)m_pUIParasGroup->FindByID(_T("MaxAngleSet"));  //最大灵敏角整定值
	pValueStd1->m_strValue = pAngleSet->m_strValue;
	pValueStd1->m_strValueID = _T("MaxAngleSet");

	CXExprValue* pValue1 = pError1->GetExprValue();
	pValue1->m_strType = _T("report");
	pValue1->m_strValueID = _T("MaxAngle");  //最大灵敏角的报告数据

	CXExprValueError* pExprValueError1 = pError1->GetExprValueError();   //误差限
	pExprValueError1->m_strType = _T("number");
	pExprValueError1->m_strValueName = g_sLangTxt_MaxAngle_ErrAbs/*_T("最大灵敏角绝对误差限(°)")*/;
	CDvmData *pErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("MaxAngle_AbsErr"));  //最大灵敏角绝对误差限
	pExprValueError1->m_strValue = pErr->m_strValue;

	CXExprValueErrorRslt* pExprValueErrorRslt1 = pError1->GetExprValueErrorRslt();  //误差结果
	pExprValueErrorRslt1->m_strType = _T("report");
	pExprValueErrorRslt1->m_strValueID = _T("MaxAngleErrVal");

	//边界角1判断
	CXExprError *pError2 = new CXExprError;
	pRsltExprRun->AddNewChild(pError2);
	pError2->m_strOptr = _T("<");
	pError2->m_strMode = _T("abs");  //边界角1固化用绝对误差
	CXExprValueStd* pValueStd2 = pError2->GetExprValueStd();
	pValueStd2->m_strType = _T("report");   //回填到报告中去
	pValueStd2->m_strValueName = g_sLangTxt_AngleFSet/*_T("边界角1整定值(°)")*/;
	CDvmData *pAngleF = (CDvmData *)m_pUIParasGroup->FindByID(_T("AngleFSet"));  //边界角1整定值
	pValueStd2->m_strValue = pAngleF->m_strValue;
	pValueStd2->m_strValueID = _T("AngleFSet");

	CXExprValue* pValue2 = pError2->GetExprValue();
	pValue2->m_strType = _T("report");
	pValue2->m_strValueID = _T("AngleF");  //边界角1的报告数据

	CXExprValueError* pExprValueError2 = pError2->GetExprValueError();   //误差限
	pExprValueError2->m_strType = _T("number");
	pExprValueError2->m_strValueName = g_sLangTxt_AngleF_ErrAbs/*_T("边界角1绝对误差限(°)")*/;
	CDvmData *pAngleFErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("AngleF_AbsErr"));  //边界角1绝对误差限
	pExprValueError2->m_strValue = pAngleFErr->m_strValue;

	CXExprValueErrorRslt* pExprValueErrorRslt2 = pError2->GetExprValueErrorRslt();  //误差结果
	pExprValueErrorRslt2->m_strType = _T("report");
	pExprValueErrorRslt2->m_strValueID = _T("AngleFErrVal");

	//边界角2判断
	CXExprError *pError3 = new CXExprError;
	pRsltExprRun->AddNewChild(pError3);
	pError3->m_strOptr = _T("<");
	pError3->m_strMode = _T("abs");  //边界角2固化用绝对误差
	CXExprValueStd* pValueStd3 = pError3->GetExprValueStd();
	pValueStd3->m_strType = _T("report");   //回填到报告中去
	pValueStd3->m_strValueName = g_sLangTxt_AngleSSet/*_T("边界角2整定值(°)")*/;
	CDvmData *pAngleS = (CDvmData *)m_pUIParasGroup->FindByID(_T("AngleSSet"));  //边界角2整定值
	pValueStd3->m_strValue = pAngleS->m_strValue;
	pValueStd3->m_strValueID = _T("AngleSSet");

	CXExprValue* pValue3 = pError3->GetExprValue();
	pValue3->m_strType = _T("report");
	pValue3->m_strValueID = _T("AngleS");  //边界角2的报告数据

	CXExprValueError* pExprValueError3 = pError3->GetExprValueError();   //误差限
	pExprValueError3->m_strType = _T("number");
	pExprValueError3->m_strValueName = g_sLangTxt_AngleS_ErrAbs/*_T("边界角2绝对误差限(°)")*/;
	CDvmData *pAngleSErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("AngleS_AbsErr"));  //边界角2绝对误差限
	pExprValueError3->m_strValue = pAngleSErr->m_strValue;

	CXExprValueErrorRslt* pExprValueErrorRslt3 = pError3->GetExprValueErrorRslt();  //误差结果
	pExprValueErrorRslt3->m_strType = _T("report");
	pExprValueErrorRslt3->m_strValueID = _T("AngleSErrVal");

	//处理expr-cal。用于固定计算误差最大值和最小值
	//最大灵敏角
	CXExprCal *pCalMax_MaxAngle = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMax_MaxAngle);
	pCalMax_MaxAngle->AddQueryMax(_T("MaxAngleErrVal"));
	pCalMax_MaxAngle->m_strValueDstID = _T("MaxAngleErrVal_Max");
	pCalMax_MaxAngle->m_strValueName = g_sLangTxt_MaxAngle_AbsErr_Max/*_T("最大灵敏角绝对误差最大值(°)")*/;

	CXExprCal *pCalMin_MaxAngle = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMin_MaxAngle);
	pCalMin_MaxAngle->AddQueryMin(_T("MaxAngleErrVal"));
	pCalMin_MaxAngle->m_strValueDstID = _T("MaxAngleErrVal_Min");
	pCalMin_MaxAngle->m_strValueName = g_sLangTxt_MaxAngle_AbsErr_Min/*_T("最大灵敏角绝对误差最小值(°)")*/;

	//处理expr-cal。用于固定计算误差最大值和最小值
	//边界角1
	CXExprCal *pCalMax_AngleF = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMax_AngleF);
	pCalMax_AngleF->AddQueryMax(_T("AngleFErrVal"));
	pCalMax_AngleF->m_strValueDstID = _T("AngleFErrVal_Max");
	pCalMax_AngleF->m_strValueName = g_sLangTxt_AngleF_AbsErr_Max/*_T("边界角1绝对误差最大值(°)")*/;

	CXExprCal *pCalMin_AngleF = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMin_AngleF);
	pCalMin_AngleF->AddQueryMin(_T("AngleFErrVal"));
	pCalMin_AngleF->m_strValueDstID = _T("AngleFErrVal_Min");
	pCalMin_AngleF->m_strValueName = g_sLangTxt_AngleF_AbsErr_Min/*_T("边界角1绝对误差最小值(°)")*/;

	//处理expr-cal。用于固定计算误差最大值和最小值
	//边界角2
	CXExprCal *pCalMax_AngleS = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMax_AngleS);
	pCalMax_AngleS->AddQueryMax(_T("AngleSErrVal"));
	pCalMax_AngleS->m_strValueDstID = _T("AngleSErrVal_Max");
	pCalMax_AngleS->m_strValueName = g_sLangTxt_AngleS_AbsErr_Max/*_T("边界角2绝对误差最大值(°)")*/;

	CXExprCal *pCalMin_AngleS = new CXExprCal();
	pRsltExprRun->AddNewChild(pCalMin_AngleS);
	pCalMin_AngleS->AddQueryMin(_T("AngleSErrVal"));
	pCalMin_AngleS->m_strValueDstID = _T("AngleSErrVal_Min");
	pCalMin_AngleS->m_strValueName = g_sLangTxt_AngleS_AbsErr_Min/*_T("边界角2绝对误差最小值(°)")*/;
	return;
}

void CGbItemsGenTool::ActionTimeValue(CItemRsltExprRun *pRsltExprRun)//动作时间
{
	CXExprErrorEx *pErrorEx = new CXExprErrorEx;
	pRsltExprRun->AddNewChild(pErrorEx);
	pErrorEx->m_strOptr = _T("<");
	CXExprValueStd* pValueStd = pErrorEx->GetExprValueStd();
	pValueStd->m_strType = _T("report");   //回填报告中去
	pValueStd->m_strValueID = _T("TSet");
	pValueStd->m_strValueName = g_sLangTxt_TSet/*_T("动作时间整定值(s)")*/;

	long nErrorLogic = 0;
	CDvmData *pRelErr = NULL;
	CDvmData *pAbsErr = NULL;

	CXExprValueErrorAbs* pValueErrAbs = pErrorEx->GetExprValueErrorAbs();
	pValueErrAbs->m_strType = _T("number");

	CXExprValueErrorAbsRslt* pAbsErrValue = pErrorEx->GetExprValueErrorAbsRslt();
	pAbsErrValue->m_strType = _T("report");
	pAbsErrValue->m_strValueUnit = _T("ms");

	CDvmData *pISet = (CDvmData *)m_pUIParasGroup->FindByID(_T("TSet"));//动作时间整定值
	pValueStd->m_strValue = pISet->m_strValue;

	CDvmData *pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("Ttrip_ErrorLogic"));  //动作时间误差判断逻辑

	if (pErrorLogic == NULL)
	{
		pErrorLogic = (CDvmData *)m_pUIParasGroup->FindByID(_T("TimeValue_ErrorLogic"));
	}

	if (pErrorLogic != NULL)
	{
		nErrorLogic = CString_To_long(pErrorLogic->m_strValue);
	}

	ErrorLogicType(pErrorEx,nErrorLogic);

	CXExprValueErrorRel* pValueErrRel = pErrorEx->GetExprValueErrorRel();
	pValueErrRel->m_strType = _T("number");
	CXExprValueErrorRelRslt* pRelErrValue = pErrorEx->GetExprValueErrorRelRslt();
	pRelErrValue->m_strType = _T("report");
	pRelErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("Ttrip_RelErr"));  //动作时间相对误差限
	pAbsErr = (CDvmData *)m_pUIParasGroup->FindByID(_T("Ttrip_AbsErr"));  //动作时间绝对误差限

	pRelErrValue->m_strValueID = _T("TTripErrRelVal");  //计算的相对误差值，重新绑定回结果参数
	pRelErrValue->m_strValueName = g_sLangTxt_T_RelErr/*_T("动作时间相对误差(%)")*/;
	pAbsErrValue->m_strValueID = _T("TTripErrAbsVal");  //计算的绝对误差值，重新绑定回结果参数
	pAbsErrValue->m_strValueName = g_sLangTxt_T_AbsErr/*_T("动作时间绝对误差(ms)")*/;
	pValueErrRel->m_strValue = pRelErr->m_strValue;  //相对误差限
	pValueErrRel->m_strValueName = g_sLangTxt_T_ErrRel/*_T("动作时间相对误差限(%)")*/;
	pValueErrAbs->m_strValue = pAbsErr->m_strValue;  //绝对误差限
	pValueErrAbs->m_strValueName = g_sLangTxt_T_ErrAbs/*_T("动作时间绝对误差限(s)")*/;

	CXExprValue* pValue = pErrorEx->GetExprValue();
	pValue->m_strType = _T("report");
	pValue->m_strValueID = _T("TripTime");  //动作时间的报告数据
	pValue->m_strValueName = g_sLangTxt_T_Act/*_T("动作时间(s)")*/;  //动作时间的报告数据

	//处理expr-cal。用于固定计算误差最大值和最小值
	CXExprCal *pCalRelMax = NULL;
	CXExprCal *pCalRelMin = NULL;
	CXExprCal *pCalAbsMax = NULL;
	CXExprCal *pCalAbsMin = NULL;

	if (pErrorEx->m_strMode == _T("real"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TTripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TimeErrRelVal_Max");//相对误差最大值

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TTripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TimeErrRelVal_Min");//相对误差最小值
	}
	else if (pErrorEx->m_strMode == _T("abs"))
	{
		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TTripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TimeErrAbsVal_Max");//绝对误差最大值

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TTripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TimeErrAbsVal_Min");//绝对误差最小值
	}
	else if (pErrorEx->m_strMode == _T("or") || pErrorEx->m_strMode == _T("and"))
	{
		pCalRelMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMax);
		pCalRelMax->AddQueryMax(_T("TTripErrRelVal"));
		pCalRelMax->m_strValueDstID = _T("TimeErrRelVal_Max");

		pCalRelMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalRelMin);
		pCalRelMin->AddQueryMin(_T("TTripErrRelVal"));
		pCalRelMin->m_strValueDstID = _T("TimeErrRelVal_Min");

		pCalAbsMax = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMax);
		pCalAbsMax->AddQueryMax(_T("TTripErrAbsVal"));
		pCalAbsMax->m_strValueDstID = _T("TimeErrAbsVal_Max");

		pCalAbsMin = new CXExprCal();
		pRsltExprRun->AddNewChild(pCalAbsMin);
		pCalAbsMin->AddQueryMin(_T("TTripErrAbsVal"));
		pCalAbsMin->m_strValueDstID = _T("TimeErrAbsVal_Min");
	}

	if (pCalAbsMax != NULL)
	{
		pCalAbsMax->m_strValueName = g_sLangTxt_T_AbsErr_Max/*_T("动作时间绝对误差最大值(ms)")*/;
	}
	if (pCalRelMax != NULL)
	{
		pCalRelMax->m_strValueName = g_sLangTxt_T_RelErr_Max/*_T("动作时间相对误差最大值(%)")*/;
	}
	if (pCalAbsMin != NULL)
	{
		pCalAbsMin->m_strValueName = g_sLangTxt_T_AbsErr_Min/*_T("动作时间绝对误差最小值(ms)")*/;
	}
	if (pCalRelMin != NULL)
	{
		pCalRelMin->m_strValueName = g_sLangTxt_T_RelErr_Min/*_T("动作时间相对误差最小值(%)")*/;
	}
	return;	
}

CItems* CGbItemsGenTool::IsHasDevReset()
{
	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	return ((CItems *)pDevice->FindByID(STT_ITEMS_ID_DEVRESET));
}

BOOL CGbItemsGenTool::IsItemDevReset(CGbItemBase *pItemBase)
{
	if (IsHasDevReset() == NULL)
	{
		//没添加装置复归态，则不是
		return FALSE;
	}

	if (pItemBase->GetClassID() != GBCLASSID_ITEMS)
	{
		//不是分类项目，则不是
		return FALSE;
	}

	if (pItemBase->m_strID == STT_ITEMS_ID_AFTERTEST
		|| pItemBase->m_strID == STT_ITEMS_ID_DEVRESET)
	{
		//测试后恢复+装置复归态。认为是复归态
		//可以通过ID判断的原因，上位机不允许修改ID
		return TRUE;
	}

	return FALSE;
}

BOOL CGbItemsGenTool::IsGuideBookHasDvm()
{
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	return (pDevice->IsDeviceHasDvm()) && (m_oDvmDevice.GetCount() > 0);
}

long CGbItemsGenTool::GetGbCommCmdConfigs(CExBaseList *pListCommCmds, CExBaseList *pGbCommCmdConfigs)
{
	POS pos = pListCommCmds->GetHeadPosition();

	while (pos != NULL)
	{
		CCommCmd *pCommCmd = (CCommCmd *)pListCommCmds->GetNext(pos);
		CGbCommCmd *pGbCmd = (CGbCommCmd *)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);

		if (pGbCommCmdConfigs->FindByID(pGbCmd->m_strID) == NULL)
		{
			pGbCommCmdConfigs->AddTail(pGbCmd);
		}
	}

	return pGbCommCmdConfigs->GetCount();
}

//根据通讯命令配置，筛选数据集
long CGbItemsGenTool::GetDatasetsByGbCommCmd(CExBaseList *pListDatasets, CGbCommCmd *pGbCmd)
{
	CString strDatasetKey = pGbCmd->m_strGbDataID;
	CStringArray strKeyArray;
	CExBaseList oListDataset;
	//write指令，关联的数据集可能是多个，例如：dsDout#dsGOOSE。以#号分隔。
	while (TRUE)
	{
		long nPos = strDatasetKey.Find('#');

		if (nPos > 0)
		{
			CString strKey = strDatasetKey.Left(nPos);
			strDatasetKey = strDatasetKey.Mid(nPos+1);
			GetdsKey(strKeyArray, strKey);
		}
		else
		{
			GetdsKey(strKeyArray, strDatasetKey);
			break;
		}
	}

	CString strKey;

	for (int n=0; n<strKeyArray.GetCount();n++)
	{
		strKey.AppendFormat(strKeyArray.GetAt(n));
	}

	m_oDvmDevice.GetDatasetList(strKeyArray, *pListDatasets);
	long nCount = pListDatasets->GetCount();

	if (nCount == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("写指令，模型中找不到数据集【%s】，添加通讯命令失败"), strKey.GetString());
	}

	return nCount;
}

void CGbItemsGenTool::GetParentItemPath(const CString &strItemPath, CString &strParentPath)
{
	long nPos = strItemPath.ReverseFind('$');

	if (nPos < 0)
	{
		//找不到，说明项目路径为CDevice下第一级。父项目路径为""即可。
		return;
	}

	strParentPath = strItemPath.Left(nPos);
}

long CGbItemsGenTool::GetAllAinItems(CExBaseList *pDestLists)
{
	CDevice *pDevice = m_pGuideBook->GetDevice();

	return GetAllAinItems(pDevice, pDestLists);
}

long CGbItemsGenTool::GetAllAinItems(CGbItemBase *pItemBase, CExBaseList *pDestLists)
{
	POS pos = pItemBase->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CItems *pItems = NULL;

	while (pos != NULL)
	{
		pObj = pItemBase->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		pItems= (CItems *)pObj;

		if (pItems->IsTypeRootNode())
		{
			//该属性记录功能ID
			if (IsAinItems(pItems->m_strStxmlFile))
			{
				pDestLists->AddTail(pItems);
			}
			
			continue;  //rootnode不会嵌套，无需递归
		}

		GetAllAinItems(pItems, pDestLists);
	}

	return pDestLists->GetCount();
}

BOOL CGbItemsGenTool::IsAinItems(const CString &strItemsID)
{
	if (strItemsID == _T("AccuracyTest")
		|| strItemsID == _T("PowerAccuracyTest")
		|| strItemsID == _T("FreqPFTest")
		|| strItemsID == _T("FreqCurrTest")
		|| strItemsID == _T("SupplyVolHeatTest")
		|| strItemsID == _T("HarmChangeTest")
		|| strItemsID == _T("PFOverTest")
		|| strItemsID == _T("PowerVolCurrTest"))
	{
		return TRUE;
	}

	return FALSE;
}
