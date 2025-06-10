#ifndef __CSttTestCtrlCntrWin_H
#define __CSttTestCtrlCntrWin_H

#include "SttTestCtrlCntrNative.h"

class CSttTestCtrlCntrWin : public CSttTestCtrlCntrNative
{
public:
    CSttTestCtrlCntrWin();
    virtual ~CSttTestCtrlCntrWin();

public:
	virtual void NewTest(CDataGroup *pDevice, CDataGroup *pTestApp, CDataGroup *pCommConfig);

public:
	virtual void ConnectAtsServer();

	virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual long Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
		, CDataGroup *pCommCmd=NULL, const CString &strDvmFile=_T(""), const CString strTestClass=_T(""), long nRepeatTimes=1
		, long nRptTitle=0, long nTitleLevel=1, long nSynMode=STT_CMD_Send_Sync);

	//2022-3-29  lijunqing
	virtual long Ats_NewItems(CExBaseList *pParent, CExBaseObject *pItems);
	virtual long Ats_EditItems(CExBaseList *pParent, CExBaseObject *pItems, const CString &strItemsID);
	virtual long Ats_DeleteItems(CExBaseList *pParent, CExBaseObject *pItems);
	//2022-10-20  shaolei
	virtual long Ats_MoveUpItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes = 1);
	virtual long Ats_MoveDownItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes = 1);
	//2023-2-1  shaolei
	virtual long Ats_ItemPaste(CExBaseList *pParent, const CString& strSrcItemPath);
	//2023-8-11 shaolei //添加测试前、后通讯组合
	virtual long Ats_CmdAddGrp(CExBaseList *pParent, long nAftUseReset = 1, long nAddCommCmd = 1);
	//2023-8-14 shaolei  //导入模型文件(模型映射)
	virtual long Ats_ImportDvmFile(const CString &strDvmFile, long nIsDvmMap = 0);
	//2023-8-28 shaolei  //遥测参数映射
	virtual long Ats_AinDataMap(CDataGroup *pMapParas, CDataGroup *pAinDevRatios);

	//zhouhj 2023.12.6 该功能移入基类
	//2023-8-29 shaolei  //配置装置
//	virtual long Ats_ConfigDevice(CDataGroup *pCommCfg);

	//2022-08-31 shaolei
	virtual long Ats_GenrateItems_CmdWzd(CExBaseList *pParent, CDataGroup *pCommCmd, const CString &strMacroName, const CString &strTestClass, long nSynMode = STT_CMD_Send_Sync);
	virtual long Ats_GenrateItems_CmdAdd(const CString &strParentItemPath, CDataGroup *pCommCmd, CSttContents *pContents);

	virtual long Ats_GenerateItems_AddSafety(CDataGroup *pParas, CExBaseList *pListDatas, CExBaseList *pMsgs);

	virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs);

protected:
	void Ats_InitGenerateItemsParas(CDataGroup **ppGenParas, CExBaseList *pParent, CExBaseObject *pItems, const CString &strCmdID, const CString &strItemsID=_T(""));

//CAtsEventInterface
public:


public:

};

#endif // __CSttTestCtrlCntrWin_H
