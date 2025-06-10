#include "SttTestCtrlCntrWin.h"

CSttTestCtrlCntrWin::CSttTestCtrlCntrWin()
{
 
}

CSttTestCtrlCntrWin::~CSttTestCtrlCntrWin()
{

}

void CSttTestCtrlCntrWin::NewTest(CDataGroup *pDevice, CDataGroup *pTestApp, CDataGroup *pCommConfig)
{
	m_pSttGuideBook->ClearGuideBook();
	m_pSttGuideBook->InitDevice();
	
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, NULL, NULL, STT_CMD_PARA_generate_items_create);

	if (pDevice != NULL)
	{
		CDataGroup *pNew = new CDataGroup;
		pDevice->CopyEx(pNew, TRUE, TRUE);
		pGenParas->AddNewChild(pNew);
	}

	if (pTestApp != NULL)
	{
		CDataGroup *pNew = new CDataGroup;
		pTestApp->CopyEx(pNew, TRUE, TRUE);
		pGenParas->AddNewChild(pTestApp);
	}

	if (pCommConfig != NULL)
	{
		CDataGroup *pNew = new CDataGroup;
		pNew->AppendCloneEx(*pCommConfig, TRUE);
		pNew->m_strID = STT_CMD_PARA_CommConfig;
		pGenParas->AddNewChild(pNew);
	}

	m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

void CSttTestCtrlCntrWin::ConnectAtsServer()
{
	//后续修改为连接  127.0.0.1的服务提供端
	CSttTestCtrlCntrNative::ConnectAtsServer();
}


void CSttTestCtrlCntrWin::OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	CSttTestCtrlCntrBase::OpenMacroTestUI(pTestMacroUI);
	//m_pSttGuideBook->ClearGuideBook();
}


long CSttTestCtrlCntrWin::Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
											, CDataGroup *pCommCmd, const CString &strDvmFile, const CString strTestClass, long nRepeatTimes
											, long nRptTitle, long nTitleLevel, long nSynMode)
{
	return CSttTestCtrlCntrNative::Ats_GenerateItems(strItemParentPath, strItemsName, strItemsID, pCommCmd, strDvmFile, strTestClass, nRepeatTimes
		, nRptTitle, nTitleLevel, nSynMode);
}

//2022-3-29  lijunqing
long CSttTestCtrlCntrWin::Ats_NewItems(CExBaseList *pParent, CExBaseObject *pItems)
{
	//新建测试分类，重复次数已经在pItems的m_nRepeatTimes属性中，故此处不用传参
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	//在拼接参数时，将重复次数拼接进去
	Ats_InitGenerateItemsParas(&pGenParas, pParent, pItems, STT_CMD_PARA_generate_items_new);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

long CSttTestCtrlCntrWin::Ats_EditItems(CExBaseList *pParent, CExBaseObject *pItems, const CString &strItemsID)
{
	//测试项目编辑，重复次数已经在pItems的m_nRepeatTimes属性中，故此处不用传参
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	//在拼接参数时，将重复次数拼接进去
	Ats_InitGenerateItemsParas(&pGenParas, pParent, pItems, STT_CMD_PARA_generate_items_edit, strItemsID);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

long CSttTestCtrlCntrWin::Ats_DeleteItems(CExBaseList *pParent, CExBaseObject *pItems)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, pParent, pItems, STT_CMD_PARA_generate_items_delete);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

//2022-10-20  shaolei
long CSttTestCtrlCntrWin::Ats_MoveUpItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, pParent, pItems, STT_CMD_PARA_generate_items_move_up);
	pGenParas->AddNewData(STT_CMD_PARA_MoveTimes, nMoveTimes);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

long CSttTestCtrlCntrWin::Ats_MoveDownItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, pParent, pItems, STT_CMD_PARA_generate_items_move_down);
	pGenParas->AddNewData(STT_CMD_PARA_MoveTimes, nMoveTimes);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

//2023-2-1  shaolei
long CSttTestCtrlCntrWin::Ats_ItemPaste(CExBaseList *pParent, const CString& strSrcItemPath)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, pParent, NULL, STT_CMD_PARA_generate_items_paste);
	pGenParas->AddNewData(STT_CMD_PARA_ItemPath, strSrcItemPath);
	//pGenParas->AddNewData(STT_CMD_PARA_SrcParentItemsPath, strSrcParentItemsID);
	//pGenParas->AddNewData(STT_CMD_PARA_SrcItemsID, strSrcItemsID);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

//2023-8-11 shaolei //添加测试前、后通讯组合
//nAftUseReset：1=测试后恢复采用复归态；0=测试后恢复采用测试前取反
//nAddCommCmd：1=自动添加通讯命令项目；0=仅添加测试前、后的分类项目
long CSttTestCtrlCntrWin::Ats_CmdAddGrp(CExBaseList *pParent, long nAftUseReset, long nAddCommCmd)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, pParent, NULL, STT_CMD_PARA_generate_items_cmd_add_grp);
	pGenParas->AddNewData(XPARA_ID_AftUseDevReset, nAftUseReset);
	pGenParas->AddNewData(XPARA_ID_AddCommCmd, nAddCommCmd);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

long CSttTestCtrlCntrWin::Ats_ImportDvmFile(const CString &strDvmFile, long nIsDvmMap)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, NULL, NULL, STT_CMD_PARA_generate_items_import_dvm_file);
	pGenParas->AddNewData(STT_CMD_PARA_DvmFile, strDvmFile);
	pGenParas->AddNewData(XPARA_ID_IsDvmMap, nIsDvmMap);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

//2023-8-28 shaolei  //遥测参数映射
long CSttTestCtrlCntrWin::Ats_AinDataMap(CDataGroup *pMapParas, CDataGroup *pAinDevRatios)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = NULL;
	Ats_InitGenerateItemsParas(&pGenParas, NULL, NULL, STT_CMD_PARA_generate_items_ain_data_map);
	CDataGroup *pAinDataMapCfg = new CDataGroup();
	pGenParas->AddNewChild(pAinDataMapCfg);
	pAinDataMapCfg->m_strID = STT_CMD_PARA_generate_items_AinDataMapCfg;
	pAinDataMapCfg->AppendCloneEx(*pMapParas, TRUE);

	CDataGroup *pParaRatios = new CDataGroup();
	pGenParas->AddNewChild(pParaRatios);
	pParaRatios->m_strID = STT_CMD_PARA_generate_items_AinRatios;
	pParaRatios->AppendCloneEx(*pAinDevRatios, TRUE);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
}

//zhouhj 2023.12.6 该功能移入基类
//2023-8-29 shaolei  //配置装置
// long CSttTestCtrlCntrWin::Ats_ConfigDevice(CDataGroup *pCommCfg)
// {
// 	if (!m_oSttAtsClient.ConnectAtsTestServer())
// 	{
// 		return 0;
// 	}
// 
// 	return m_oSttAtsClient.Ats_ConfigDevice(pCommCfg);
// }

//2022-08-31 shaolei
long CSttTestCtrlCntrWin::Ats_GenrateItems_CmdWzd(CExBaseList *pParent, CDataGroup *pCommCmd, const CString &strMacroName, const CString &strTestClass, long nSynMode)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = new CDataGroup();

	pGenParas->m_strName = STT_CMD_PARA_generate_items;
	pGenParas->m_strID = STT_CMD_PARA_generate_items;
	pGenParas->m_strDataType = STT_CMD_PARA_generate_items;
	pGenParas->m_strValue = STT_CMD_PARA_generate_items_cmd_wzd;

	CString strParentItemsPath;
	strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	pGenParas->AddNewData(STT_CMD_PARA_ParentItemsPath, STT_CMD_PARA_ParentItemsPath, "string", strParentItemsPath);
	pGenParas->AddNewData(STT_CMD_PARA_MACRO_NAME, STT_CMD_PARA_MACRO_NAME, "string", strMacroName);
	pGenParas->AddNewData(STT_CMD_PARA_TestClass, STT_CMD_PARA_TestClass, "string", strTestClass);

	CDataGroup *pNew = pGenParas->AddNewGroup(_T("通信命令生成配置"), STT_CMD_PARA_CommCmd, _T(""));
	pNew->AppendCloneEx2(*pCommCmd, TRUE, TRUE);

	return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas, 0, true, 0, nSynMode);
}

long CSttTestCtrlCntrWin::Ats_GenrateItems_CmdAdd(const CString &strParentItemPath, CDataGroup *pCommCmd, CSttContents *pContents)
{
	if (!m_oSttAtsClient.ConnectAtsTestServer())
	{
		return 0;
	}

	CDataGroup *pGenParas = new CDataGroup();

	pGenParas->m_strName = STT_CMD_PARA_generate_items;
	pGenParas->m_strID = STT_CMD_PARA_generate_items;
	pGenParas->m_strDataType = STT_CMD_PARA_generate_items;
	pGenParas->m_strValue = STT_CMD_PARA_generate_items_cmd_add;

	pGenParas->AddNewData(STT_CMD_PARA_ParentItemsPath, STT_CMD_PARA_ParentItemsPath, "string", strParentItemPath);

	CDataGroup *pNew = pGenParas->AddNewGroup(_T("通信命令生成配置"), STT_CMD_PARA_CommCmd, _T(""));
	pNew->AppendCloneEx2(*pCommCmd, TRUE, TRUE);

	if (pContents != NULL)
	{
		return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas,(CSttContents*)pContents->Clone());
	}
	else
	{
		return m_oSttAtsClient.Ats_GenerateItems_Items(pGenParas);
	}
}

long CSttTestCtrlCntrWin::Ats_GenerateItems_AddSafety(CDataGroup *pParas, CExBaseList *pListDatas, CExBaseList *pMsgs)
{
	return CSttTestCtrlCntrNative::Ats_GenerateItems_AddSafety(pParas, pListDatas, pMsgs);
}

long CSttTestCtrlCntrWin::OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs) 
{
	if (m_pTestCtrlCntrMsg == NULL)
	{
		return -1;
	}

	m_pTestCtrlCntrMsg->OnInputData(pParas,pMsgs);

	return 0;
}

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
void CSttTestCtrlCntrWin::Ats_InitGenerateItemsParas(CDataGroup **ppGenParas, CExBaseList *pParent
													 , CExBaseObject *pItems, const CString &strCmdID, const CString &strItemsID)
{
	CDataGroup *pNew = new CDataGroup();
	*ppGenParas = pNew;

	pNew->m_strName = STT_CMD_PARA_generate_items;
	pNew->m_strID = STT_CMD_PARA_generate_items;
	pNew->m_strDataType = STT_CMD_PARA_generate_items;
	pNew->m_strValue = strCmdID;

	if (strItemsID.GetLength() > 0)
	{
		pNew->AddNewData(STT_CMD_PARA_ItemsID, STT_CMD_PARA_ItemsID, "string", strItemsID);
	}
	else
	{
		if (pItems != NULL)
		{
			pNew->AddNewData(STT_CMD_PARA_ItemsID, STT_CMD_PARA_ItemsID, "string", pItems->m_strID);
		}
	}

	if (pParent != NULL)
	{
		CString strParentItemsPath;
		strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
		pNew->AddNewData(STT_CMD_PARA_ParentItemsPath, STT_CMD_PARA_ParentItemsPath, "string", strParentItemsPath);
	}

	if (pItems != NULL)
	{
		CDataGroup *pItemsParas = pNew->AddNewGroup(STT_CMD_PARA_generate_items_items, STT_CMD_PARA_generate_items_items, STT_CMD_PARA_generate_items_items);
		pItemsParas->AddNewData("name", "name", "string", pItems->m_strName);
		pItemsParas->AddNewData("id", "id", "string", pItems->m_strID);

		if (pItems->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems *pSttItems = (CSttItems*)pItems;
			pItemsParas->AddNewData("type", "type", "string", pSttItems->m_strType);
			pItemsParas->AddNewData(STT_CMD_PARA_generate_items_RepeatTimes, pSttItems->m_nTestTimes);
			pItemsParas->AddNewData(STT_CMD_PARA_generate_items_RptTitle, pSttItems->m_nRptTitle);
			pItemsParas->AddNewData(STT_CMD_PARA_generate_items_TitleLevel, pSttItems->m_nTitleLevel);
		}
	}
}

