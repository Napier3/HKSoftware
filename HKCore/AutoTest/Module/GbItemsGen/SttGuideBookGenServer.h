#pragma once

#include "GbItemsGenTool.h"

class CSttGuideBookGenServer
{
public:
	CSttGuideBookGenServer(void);
	virtual ~CSttGuideBookGenServer(void);

public:
	CGbItemsGenTool m_oTool;
	void InitGbGenSysPath(const CString &strSysPath);

public:
	//成功返回0，不成功返回!0
	long Process_Cmd_Ats_GenerateTemplate(CDataGroup *pSttParas); 
	long Process_Cmd_Ats_GenerateItems(CDataGroup *pSttParas); 
	long Process_Cmd_Ats_GenerateMacroTest(CDataGroup *pSttParas); 
	long Process_Cmd_Ats_SetItemPara(CDataGroup *pSttParas); 
    long Process_Cmd_Ats_SetItemPara_SystemConfig(CDataGroup *pSttParas);
	long Process_Cmd_Ats_UpdateItem(CDataGroup *pSttParas); 
	CString Process_Cmd_Ats_QueryItem(CDataGroup *pSttParas); 
	long Process_Cmd_Ats_ConfigDevice(CDataGroup *pSttParas);
	long Process_Cmd_Ats_OfflineSel(CDataGroup *pSttParas);


	CGuideBook* GetGuideBook()	{	return m_oTool.GetGuideBook();	}
    void SetGuideBook(CGuideBook* pGuideBook)     {   m_oTool.SetGuideBook(pGuideBook); }
	void SetMacroTestSaveParas(BOOL bSaveParas)	{	m_oTool.SetMacroTestSaveParas(bSaveParas);	}
	CItems* GetItems()	{	return (CItems *)m_oTool.GetGbItemBase();	}
	CItems* GetItems_CmdAddGrp()	{	return (CItems *)m_oTool.GetGbItems_CmdAddGrp();	}
	CItems* GetItems_ImportDvm()	{	return (CItems *)m_oTool.GetGbItems_ImportDvm();	}
	CItems* GetItems_AinCfg()	{	return (CItems *)m_oTool.GetGbItems_AinCfg();	}
	void FreeItems_AinCfg()	{	m_oTool.FreeItems_AinCfg();	}
	CItems* GetItems_BeforeTest()	{	return (CItems *)m_oTool.GetItems_BeforeTest();	}
	CString GetItemsPath_BeforeTest()	{	return m_oTool.GetItemsPath_BeforeTest();}
	CMacroTest* GetMacroTest();
	CDvmDataset* GetGlobalDatas();
	CExBaseList* GetSysPara();
	UINT GetTemplateGenMode();
	void SetTemplateGenMode(UINT nMode);
	BOOL Is_GenerateItems_CmdWzd();
	CDataGroup* GetGenrateItems_CmdWzd_Reply();
	void OpenDvmFile(const CString &strDvmFile);
	BOOL OpenDvmFile_Ex(const CString &strDvmFile);
};
