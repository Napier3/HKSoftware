#pragma once

#include "../../../AutoTest/Module/GbItemsGenTool.h"
#include "../SttGlobalDef.h"

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
	long Process_Cmd_Ats_SetItemPara(CDataGroup *pSttParas); 
    long Process_Cmd_Ats_SetItemPara_SystemConfig(CDataGroup *pSttParas);

	CGuideBook* GetGuideBook()	{	return m_oTool.GetGuideBook();	}
    void SetGuideBook(CGuideBook* pGuideBook)     {   m_oTool.SetGuideBook(pGuideBook); }
	CItems* GetItems()	{	return (CItems *)m_oTool.GetGbItemBase();	}
	UINT GetTemplateGenMode();
	void SetTemplateGenMode(UINT nMode);
	BOOL Is_GenerateItems_CmdWzd();
	CDataGroup* GetGenrateItems_CmdWzd_Reply();
};
