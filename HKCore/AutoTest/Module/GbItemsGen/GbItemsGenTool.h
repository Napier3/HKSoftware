#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
#include "GbItemsGen.h"
#include "../GuideBook/GuideBook.h"
#include "../../../SttStudio/Module/UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../../../SttStudio/Module/SttCmd/SttChMaps.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../SttStudio/Module/SttCmd/SttMacro.h"
#include "../../../SttStudio/Module/SttCmd/GuideBook/SttContents.h"
#include "../GuideBook/ItemRsltExprRun.h"
#include "../../../SttStudio/Module/SttSystemConfig/SttSystemConfig.h"
#include "../../../Module/Expression/XExprCal.h"

//测试功能参数界面类型：0-原生态界面；1-网页界面
#define TESTMACRO_UI_TYPE_ORIGINAL   0
#define TESTMACRO_UI_TYPE_WEB        1 
#define TESTMACRO_UI_TYPE_ERROR      2   //生成规则文件和界面HTML文件没有成套配置，认为配置出错

#define TEST_CLASS_AIN           _T("YC")//_T("精度测试")
#define TEST_CLASS_RELAY         _T("Relay")//_T("保护功能测试")
#define TEST_CLASS_INFO_Relay    _T("Info-Relay")//_T("信息规范化测试-保护功能")
#define TEST_CLASS_YK            _T("YK")//_T("信息规范化测试-远方操作")
#define TEST_CLASS_YX            _T("YX")//_T("遥信测试")

//测试模板生成模式：0-普通模式；1-开始测试时生成模板
#define TEMPLATE_GEN_MODE_NORMAL     0   //普通模式，需要重新生成测试前准备项目：系统配置、硬件通道配置、IEC配置
#define TEMPLATE_GEN_MODE_STARTTEST  1   //开始测试时生成模式，不重新生成测试前准备项目（测试前准备项目的参数，可能是重新设置过的，不能重新生成覆盖）
#define TEMPLATE_GEN_MODE_SAVE       2   //保存模板时，不对默认值的参数进行整理删减

#define FILENAME_STTIECCONCFIG	 "SttIecConfig.ixml"
#define FILENAME_STTSYSTEMPARAS	 "SystemParas.sysxml"
#define FILENAME_COMMCMDWZDCFG   "commcmd-wzd-cfg.xml"
#define FILENAME_STTCOMMCMDCFG   "SttCommCmdCfg.xml"
#define FILENAME_STTSYSTEMCONFIG	 "SystemConfig.xml"

//误差判断逻辑
#define ERROR_LOGIC_ABS    0   //绝对误差
#define ERROR_LOGIC_REL    1   //相对误差
#define ERROR_LOGIC_OR     2   //绝对误差  或  相对误差
#define ERROR_LOGIC_AND    3   //绝对误差  和  相对误差
#define ERROR_LOGIC_COMB   4   //组合误差   基准值 * rel% + abs

//递变相关
//1、递变类型
#define Gradient_VaryMode_Act      0    //动作值
#define Gradient_VaryMode_Return   1    //返回系数
#define Gradient_VaryMode_Angle    2    //最大灵敏角
//2、变量类型
#define Gradient_VarType_Val     0    //幅值递变
#define Gradient_VarType_Ph      1    //相位递变
#define Gradient_VarType_Freq    2    //频率递变
//3、当时幅值或者相位递变时，需要区分是电压递变还是电流递变
#define Gradient_VarIndexType_I     0    //电流递变
#define Gradient_VarIndexType_U     1    //电压递变
#define Gradient_VarIndexType_F     2    //频率递变

//谐波相关
#define Harm_VarIndexType_I     0    //电流递变
#define Harm_VarIndexType_U     1    //电压递变

//通用试验相关
#define Manual_VaryMode_Act      0    //动作值
#define Manual_VaryMode_Return   1    //返回系数

//序分量相关
#define SequenceManu_VaryMode_Act      0    //动作值
#define SequenceManu_VaryMode_Return   1    //返回系数

//递变-序分量
#define SequenceGradient_VarIndexType_I     0    //电流递变
#define SequenceGradient_VarIndexType_U     1    //电压递变

//通用试验-线电压
#define LineVoltManual_VarIndexType_I     0    //电流递变
#define LineVoltManual_VarIndexType_U     1    //电压递变

//递变-线电压
#define LineVolGradient_VarIndexType_I     0    //电流递变
#define LineVolGradient_VarIndexType_U     1    //电压递变

//电气量项目，重复测试时，报告计算方式
#define MACROTEST_RPTCALMODE_AVERAGE    0
#define MACROTEST_RPTCALMODE_MAX        1
#define MACROTEST_RPTCALMODE_MIN        2

class CGbItemsGenTool
{
public:
	CGbItemsGenTool(void);
	virtual ~CGbItemsGenTool(void);

	//2022-3-29  lijunqing  在使用SmartTest.exe的时候，系统路径应该是STT
	void InitGbGenSysPath(const CString &strSysPath);
	CString GetDBPath()		{	return m_strDbPath;		}
	CString GetConfigPath()	{	return m_strConfigPath;	}
	void AfterInitSysPath();
	CString GetDeviceModel();
	CString GetDevice_RelPath();  //获取具体装置型号下，相关文件的相对路径。

private:
	CString m_strDbPath;
	CString m_strConfigPath;

public:
	CDataGroup *m_pUIParasGroup;   //界面参数
	CDataGroup m_oUiParas_SortIdPath;  //根据界面参数，涉及到group嵌套的，获取参数的路径  //shaolei 2025-4-2
	CDataGroup *m_pCommCmd;        //通讯命令部分
	CItemsGenInterface *m_pCurrInstInterface;  //当前Class或者Define的Interface

	CGbItemsGen *m_pGbItemsGen;   //模板生成规则文件
	CSttChMaps *m_pChMaps;   //默认的硬件通道配置
	CTestMacros *m_pTestMacros;  //根据规则文件，解析对应的测试功能文件
	CIecCfgDatasMngr *m_pIecDatasMngr;   //IEC配置
	CSttMacro *m_pSysParameter;   //系统参数配置
	CCharacteristics *m_pCharacteristics;   //特性曲线
    long m_bHasDigital;
    long m_nGenWithDebug;
	long m_nLoopTest;

	UINT m_nUIType;
	CString m_strDvmFile;   //模型文件
	CString m_strTestClass;  //测试类型：精度测试、功能测试、信息规范化测试-保护功能、信息规范化测试-远方操作、遥信测试
	CDataGroup m_oCommCmdWzdCfg;  //通讯命令-向导批量添加的配置
	CDataGroup m_oSttCommCmdCfg;  //单个添加的通讯命令的数据集配置
	CDvmDevice m_oDvmDevice;
	CDataGroup *m_pAinDataMapCfg;  //上一次下发的遥测通道配置。在添加遥测项目时，如果这个配置不为空，则直接进行参数替换。

protected:
	UINT m_nGenMode;
	CExBaseList m_oBeforeTestBk;  //测试前准备项目的备份，用于存放CItems对象

private:
	CGuideBook *m_pGuideBook;
	CGbItemBase *m_pGbItemBase;  //通过GenerateItems单独生成的测试项目
	CMacroTest *m_pMacroTest;   //通过GenerateMacroTest指令，单独生成的电气量项目
	BOOL m_bMacroTestSaveParas;  //电气量项目，是否保存参数。Linux下，生成模板时不保存参数
	CItems *m_pItems_SelfDef;  //通过“macro-selfdef-gen”节点，生成的分类节点
	CItems *m_pDevReset; //装置复归态。复归态的定义：压板全投，控制字全退，其它定值全部设置为最大值
	CItems *m_pCmdAddGrp;  //测试前、后组合。创建的临时对象，用于存放测试前、后，用于返回应答报文。本身不放到模板中
	CItems *m_pItems_ImportDvm;  //导入模型后，根据模型重新生成的项目。临时对象，本身不放到模板中，仅用于返回应答报文
	CItems *m_pItems_AinCfg;  //遥测参数配置，返回配置好的通讯命令。临时对象，本身不放到模板中，仅用于返回应答报文。报文返回后，及时删除对象
	CExBaseList m_oListAinCommCmds;  //初次添加的遥测通讯命令，用于备份原始参数。克隆对象。ID记录项目路径
	CSttSystemConfig m_oSttSystemConfig;  //系统配置，可获取装置型号

public:
	void FreeItems_DevReset();
	void FreeItems_ImportDvm(BOOL bDelete = TRUE);
	void FreeItems_AinCfg();
	CDvmData* SelectErrorLogic();
	long SelectErrorLimits(CExBaseList &oListError);
	long SelectDatasSets(CExBaseList &oListSets);

	CDvmDataset* GetGlobalDatas();
	CExBaseList* GetSysPara();
	void SetMacroTestSaveParas(BOOL bSave)	{	m_bMacroTestSaveParas = bSave;	}
	CGuideBook* GetGuideBook()	{	return m_pGuideBook;	}
    void SetGuideBook(CGuideBook* pGuideBook);
	CGbItemBase* GetGbItemBase()	{	return m_pGbItemBase;	}
	CGbItemBase* GetGbItems_CmdAddGrp()	{	return m_pCmdAddGrp;	}
	CGbItemBase* GetGbItems_ImportDvm()	{	return m_pItems_ImportDvm;	}
	CGbItemBase* GetGbItems_AinCfg()	{	return m_pItems_AinCfg;	}
	CGbItemBase* GetItems_BeforeTest();
	CString GetItemsPath_BeforeTest();
	CMacroTest* GetMacroTest()	{	return m_pMacroTest;	}
	CTestMacro* GetTestMacroByID(const CString &strMacroID);
	UINT GetTemplateGenMode();
	void SetTemplateGenMode(UINT nMode);
	void SetChMaps(CSttChMaps *pChMaps);
	void SetIecCfgDatasMngr(CIecCfgDatasMngr *pIecDatasMngr);
	void SetSysParameter(CSttMacro *pSysParameter);

	void Reset();
	BOOL IsUI_Original()	{	return m_nUIType == TESTMACRO_UI_TYPE_ORIGINAL;		}
	BOOL IsUI_Web()		{	return m_nUIType == TESTMACRO_UI_TYPE_WEB;		}
	BOOL IsUI_Error()	{	return m_nUIType == TESTMACRO_UI_TYPE_ERROR;	}
	BOOL IsTestClass_Ain()	{	return m_strTestClass == TEST_CLASS_AIN;	}

	BOOL Init(const CString &strUI);
	BOOL Init(CDataGroup *pTestMacroUI);
	void Init_UIType(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_GenFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_UIParaFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_HdRsFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	BOOL Init_IecCfg();
	BOOL Init_SystemParas();

	void Init_UIType(CDataGroup *pGroup);
	BOOL Init_GenFile(CDataGroup *pGroup);    //模板生成规则文件
	BOOL Init_UIParaFile(CDataGroup *pGroup); //界面参数文件，读取默认参数
	BOOL Init_HdRsFile(CDataGroup *pGroup);   //硬件通道配置文件，读取默认硬件通道配置参数

	BOOL OpenGenFile(const CString &strFileName);
	BOOL OpenUIParaFile(const CString &strFileName);
	BOOL OpenHdRsFile(const CString &strFileName);
	BOOL OpenCommCmdWzdCfgFile();    //用于向导批量添加的通讯命令
	BOOL OpenSttCommCmdCfgFile();   //用于单个添加的通讯命令

	BOOL Init_DvmDevice_Ex(const CString &strDvmFile);
	void Init_DvmDevice(const CString &strDvmFile);
	void Init_DvmDevice();
	void Init_DvmDevice_GetFullPath(CString &strFullPath);  //获取全路径
	void Init_TestMacroFile();
	BOOL NeedSetRootNode(const CString &strMacroID);
	void Ats_ConfigDevice(CDataGroup *pSttParas);

	void GetXml_TestMacroCharParas(CString &strParas);
	void GetXml_TestMacroUiParas(CString &strParas, const CString &strMacroID = _T(""));
	void GetXml_TestMacroUiParas(CString &strParas, CDataGroup *pUIParas, const CString &strMacroID = _T(""));
	//界面参数和TestMacro中的默认参数比较，删除值 = 默认值的参数
	void SortTestMacroUiParas(CDataGroup *pUiParas, const CString &strMacroID);
	void SortTestMacroUiParas_ByDefault(CDataGroup *pUiParas, CDataGroup *pFaultParas);
	//如果是状态序列，根据状态数，删除多余的状态的参数
	void SortTestMacroUiParas_ByStateCount(CDataGroup *pUiParas);
	void SortTestMacroUiParas_RsltEvalute(CDataGroup *pUiParas);

	void GenGuideBook(const CString &strMacroName, const CString &strMacroID, const CString &strDvmFile
		, const CString &strEngineProgID, const CString &strPpxmlFile);
	BOOL GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, const CString &strParentItemPath
		, const CString &strItemsName, const CString &strItemsID, long nRepeatTimes=0, long nRptTitle=0, long nTitleLevel=1);
	//形参bGenerateRootItems，用于标识是否生成根的CItems节点。bGenerateBFT：是否生成测试前准备。
	void GenGuideBook_Items(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem, BOOL bGenerateRootItems = TRUE, BOOL bGenerateBFT = TRUE);
	void GenGuideBook_BeforeTest(CGbItemBase *pBeforeTestItems);
	void GenGuideBook_BeforeTest(CGbItemBase *pParentItem, const CString &strUI);
	void GenGuideBook_BeforeTest_FromFile(const CString &strUI);  //根据UI的ID，从基础模板中读取测试准备项目
	void GenguideBook_BeforeTest_CopyFormFile(CItems *pParentItems, const CString &strFile, const CString &strUI);
	void GenGuideBook_BeforeTest_StartTestMode(CGbItemBase *pBeforeTestItems);
	void GetBaseGbxmlFile(const CString &strUI, CString &strPath);
	CMacroTest* GenGuideBook_CreateMacroTest(const CString &strName, const CString &strID);

	void GenGbItemBase_Original(const CString &strMacroName, const CString &strMacroID, CGbItemBase *pParentItem, BOOL bGenerateBFT = TRUE);
	void GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenInst *pInst);
	void GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenNode *pNode);
	void GenGbItemBase_Define(CGbItemBase *pParentItem, CItemsGenCharItemLine *pLine, CCharacteristic *pCharacteristic, CItemsGenInst *pInst);
	//新建一个固定的测试分类项目，并返回。作为当前规则文件所有测试项目的根节点
	CItems* GenGbItemsBase_BaseItems(CItems *pRoot, const CString &strName, const CString &strID);
	CItems* GenGbItemsBase_Root(CMacroItemsGen *pMacroItemsGen, const CString &strName, const CString &strID);
	//新建测试分类，并返回新建的测试分类，作为下一个新建测试项目的父节点
	CGbItemBase* GenGbItemBase_Define_Items(CGbItemBase *pParentItem, CItemsGenNode *pNode); 
	//新建电气量项目，并返回电气量项目的父节点，作为下一个新建测试项目的父节点
	CGbItemBase* GenGbItemBase_Define_MacroTest(CGbItemBase *pParentItem, CItemsGenNode *pNode);
	void GenGbItemBase_Define_MacroTest_InitMacroPara(CMacroTest *pMacroTest, CItemsGenNode *pNode);
    void GenGbItemBase_Define_MacroTest_InitReport(CMacroTest *pMacroTest, CExBaseList *pListParasMap=NULL);  //2022-3-15 lijunqing
	void GenGbItemBase_Define_MacroTest_InitReport_SortByDefault(CReport *pReport, CExBaseList *pListParasMap);  //2023-2-27  shaolei
	void GenGbItemBase_Define_MacroTest_InitReport(CMacroCharItems *pMacroCharItems);
	void GenGbItemBase_Define_MacroTest_InitReport_Characteristic(CMacroTest *pMacroTest);
	void GenGbItemBase_Define_MacroTest_InitReport_Expression(CString &strValue, CReport *pReport, const CString &strExpress); //初始化报告，处理参数绑定定值、系统参数表达式


	//定点测试，添加定点电气量
	long GenGuideBook_MacroTest_Single(const CString& strMacroID, const CString& strParentItemPath, const CString& strItemsName, const CString& strItemsID, CDataGroup* pMacroParas);

	//处理结果判断
	void GenGbItemBase_MacroTest_RsltExpr(CMacroTest *pMacroTest); 
	void GenGbItemBase_MacroTest_RsltExpr_StateTest(CMacroTest *pMacroTest);  //状态序列
	void GenGbItemBase_MacroTest_RsltExpr_StateTest(long nIndex, CDataGroup *pEvaluteGrp, CXExprNode *pExprNode);  //状态序列，每一组结果评估
	void GenGbItemBase_MacroTest_RsltExpr_GradientTest(CMacroTest *pMacroTest);  //递变试验
	void GenGbItemBase_MacroTest_RsltExpr_HarmTest(CMacroTest *pMacroTest);  //谐波
	void GenGbItemBase_MacroTest_RsltExpr_ManualTest(CMacroTest *pMacroTest);  //通用试验
	void GenGbItemBase_MacroTest_RsltExpr_SequenceManuTest(CMacroTest *pMacroTest);//通用试验-序分量
	void GenGbItemBase_MacroTest_RsltExpr_SequenceGradientTest(CMacroTest *pMacroTest);//递变-序分量
	void GenGbItemBase_MacroTest_RsltExpr_LineVolGradientTest(CMacroTest *pMacroTest);//递变-线电压
	void GenGbItemBase_MacroTest_RsltExpr_LineVoltManualTest(CMacroTest *pMacroTest);//通用试验-线电压

	void GenGbItemBase_MacroTest_RsltExpr(CMacroCharItems *pMacroCharItems, CItemGenRsltExpr* pRsltExprGen, CExBaseList *pInterface); 

	void InitRsltExpr(CItemRsltExprRun *pRsltExprRun, CExBaseList *pInterface, CItemGenRsltExpr* pExprNode, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprNode* pExprNode, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCmp* pExprCmp, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprError* pExprError, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprErrorEx* pExprErrorEx, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprRange* pExprRange, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprRangeEx* pExprRangeEx, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprValueCal* pExprValueCal, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprValueCalEx* pExprValueCalEx, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprErrorCombined* pExprErrorCombined, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCal* pXExprCal, CExBaseList *pParasMap);
	void InitRsltExpr_Ex(CExBaseList *pParent, CExBaseList *pInterface, CXExprCalSRpt* pXExprCalSRpt, CExBaseList *pParasMap);
	void InitRsltExpr_Value(CExBaseList *pInterface, CXExprValue *pExprValue, CExBaseList *pParasMap);
	void InitRsltExpr_Value_Expression(CExBaseList *pInterface, CXExprValue *pExprValue, CExBaseList *pParasMap);   //处理pExprValue->m_strValueID是表达式的情况

	BOOL Expr_Mode_SetByMap(CExBaseList *pInterface, CString &strMode);   //误差判断逻辑，查找映射参数进行设置
	BOOL Expr_Use_SetByMap(CXExprBase *pExprBase, CExBaseList *pInterface);   //误差判断是否启用，查找界面参数进行设置

	//新建通讯命令项目，并返回通讯命令项目
	CGbItemBase* GenGbItemBase_Define_CommCmd(CGbItemBase *pParentItem, CItemsGenNode *pNode);
	void InitCommCmdAttr(CItemsGenCommCmd *pGenCommCmd, CCommCmd *pCommCmd);  //初始化通讯命令的属性
	void InitCommCmdParas(CItemsGenCommCmd *pGenCommCmd, CCommCmd *pCommCmd);  //初始化通讯命令的通讯参数

	void GenGbItem_CharItemLine(CMacroCharItemLineDef *pItemLineDef, CItemsGenCharItemLine *pItemGenLine);

	void GenGbCommCmd_After(CGbItemBase *pParentItem);
	void GenGbCommCmd_Before(CGbItemBase *pParentItem);
	void GenGbCommCmd(CGbItemBase *pParentItem, CDataGroup *pGroup);
	CGbItemBase*  GenGbCommCmd_Ex(CGbItemBase *pParentItem, CDataGroup *pGroup);
	void GenGbCommCmd_ReadAin(CGbItemBase *pParentItem);//生成固定的读遥信的通讯命令项目
	CCommCmd* GenGbCommCmd_NewCmd(CDataGroup *pGroup);
	BOOL GetCommCmdRwOptr(const CString &strCmdID, CString &strRwOptr);
	BOOL GetCommCmdName(const CString &strCmdID, CString &strName);

	void GenGbItemBase_Class(CGbItemBase *pParentItem, CItemsGenInst *pInst);

    BOOL SetItemPara(const CString &strMacroID, const CString &strItemPath, CDataGroup *pItemsParas, CSttContents *pContents);
    BOOL SetItemPara(CMacroTest *pMacroTest, CDataGroup *pItemsParas, CSttContents *pContents);
	BOOL SetItemPara(const CString &strItemPath, CSttContents *pRsltExpr);
    BOOL SetItemPara_SystemConfig(long nHasDigital);
	void SetItemPara_IecConfig(CSttContents *pContents);
	void SetItemPara_ChMapsConfig(CSttContents *pContents);

	BOOL UpdateItem(const CString &strItemPath, const CString &strItemType, CSttContents *pContents);
	BOOL QueryItem(const CString &strItemPath, CString &strItemPara);
	long OfflineSel(const CString &strDeviceModel, const CString &strDeviceSN);
	long Init_HdRsFile_Offline(const CString &strHdRsFile, const CString &strDeviceModel, const CString &strDeviceSN);
	long Init_SystemParas_Offline(const CString &strDeviceModel, const CString &strDeviceSN);
	long Init_IecCfg_Offline(long nHasDigital);

    void UpdateUIParas(CDataGroup *pUIParas);
	void AfterInitUIParas();  //界面参数初始化、更新后，整理参数的路径 shaolei 2025-4-2
	void AfterInitUIParas(CDataGroup *pGrp);  
	void UpdateCommCmd(CDataGroup *pCommCmd);
	void SetCharacteristics(CSttContents *pContents);
	CCharacteristic* FindCharacterByID(const CString &strID);
	void InitCharacteristicsByFile(const CString &strFile);
	void SaveGbXmlFile(const CString &strMacroID);
#ifndef _PSX_QT_LINUX_
	void SaveDscXmlFile(const CString &strMacroID);
#endif

	//对于特定的测试功能，对测试功能ID，进行修正，例如递变测试的最大灵敏角试验
	void GenGbItem_MacroID_Revise(CString &strMacroID, CDataGroup *pUIParas);
	//对于特定的电气量功能，对电气量项目的Name和ID进行修正。例如合并单元自动测试功能
	void ResetMacroNameId(CItemsGenNode *pNode, CString &strName, CString &strID);

	//2022-3-29  lijunqing
	long GenerateItemsOnly(CDataGroup *pParas);
	long GenerateItemsOnly_Create(CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ItemsDelete(CGbItemBase* pItemParent, const CString &strItemsID);
	long GenerateItemsOnly_Create_AddDevReset(CGbItemBase *pParentItem);
	long CreateCommCmds_Write_ByDatasets(CExBaseList *pListDatasets, UINT nType, CGbItemBase* pItemParent, BOOL bDevReset, CItems *pItems = NULL);
	CItems* CloneDevReset(BOOL bIDUseReset);
	long GenerateItemsOnly_ItemsMoveUp(CGbItemBase* pItemParent, const CString &strItemsID, CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ItemsMoveDown(CGbItemBase* pItemParent, const CString &strItemsID, CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ItemsPaste(CGbItemBase* pItemParent, CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_SafetyAdd(CGbItemBase* pItemParent, CDataGroup *pParas);
	long GenerateItemsOnly_CmdAddGrp(CGbItemBase* pItemParent,CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ImportDvmFile(CDataGroup *p_PARA_generate_items);
	long GenerateItemsOnly_ImportDvmFile_DvmMap(const CString &strDvmFile);   //使用模型映射
	long GenerateItemsOnly_ImportDvmFile_HasDvm(const CString &strDvmFile);
	long GenerateItemsOnly_ImportDvmFile_HasDvm(CGbItemBase *pGbItemParent);
	long GenerateItemsOnly_ImportDvmFile_HasDvm_Ex(CGbItemBase *pGbItemParent);
	long GenerateItemsOnly_ImportDvmFile_HasDvm(CGbItemBase *pGbItemParent, CItems* pItems, CGbCommCmd *pGbCmd);
	long GenerateItemsOnly_ImportDvmFile_NoDvm(const CString &strDvmFile);
	long GenerateItemsOnly_AinDataMap(CDataGroup *pAinDataMapCfg, CDataGroup *pAinRatios);
	long GenerateItemsOnly_AinDataMap(CItems *pItems, CDataGroup *pAinDataMapCfg);
	long GenerateItemsOnly_AinDataMap(CCommCmd *pCommCmd, CDataGroup *pAinDataMapCfg);
	long GenerateItemsOnly_AinDataMap(CXExprNode* pExprNode, CDataGroup *pAinDataMapCfg, CString &strDsPath);
	long GenerateItemsOnly_AinDataMap(CXExprValue *pExprValue, CDataGroup *pAinDataMapCfg, CString &strDsPath);
	long GenerateItemsOnly_CmdWzd(CDataGroup *pGenerateItems);
	void GenerateItemsOnly_Cmd_Ex(CDataGroup *pReply, CDataGroup *pParas, const CString &strMacroName);
	void GenerateItemsOnly_Cmd_Ex_register(CDataGroup *pReply, CGbCommCmd *pCmd);
	void GenerateItemsOnly_Cmd_Ex_write(CDataGroup *pReply, CGbCommCmd *pCmd, const CString &strMacroName);
	void GenerateItemsOnly_Cmd_Ex_read(CDataGroup *pReply, CGbCommCmd *pCmd, const CString &strMacroName);
	long GenerateItemsOnly_Cmd_Add(CDataGroup *pGenerateItems, CSttContents *pContents);
	long GenerateItemsOnly_Macro_Add(CDataGroup *pGenerateItems, CSttContents *pContents);
	long GenerateItemsOnly_Macro_Add_SystemConfig(CMacroTest *pMacroTest, CSttContents *pContents);

	void SetBinaryFileName();

	void GetdsKey(CStringArray &strKeyArray, const CString &strKey);
	CDevice* InitGuideBookForGenerateItemsOnly();
	BOOL m_bGenerateItemsOnly_CmdWzd;   //GenerateItems指令，通讯命令生成向导的标记。因为该指令与其它GenerateItems指令的应答不一致，故增加标记区分
	CDataGroup m_oGroupCmdWzdReply;    //通讯命令生成向导，应答的数据group

private:
	BOOL QueryItem_MacroTest(CExBaseObject *pItem, CString &strItemPara);
	BOOL QueryItem_Items(CExBaseObject *pItem, CString &strItemPara);
	BOOL QueryItem_CommCmd(CExBaseObject *pItem, CString &strItemPara);

	BOOL UpdateItem_MacroTest(CExBaseObject *pItem, CSttContents *pContents);
	BOOL UpdateItem_Items(CExBaseObject *pItem, CSttContents *pContents);
	BOOL UpdateItem_CommCmd(CExBaseObject *pItem, CSttContents *pContents);

	BOOL IsDvmData_BOOL(CDvmData *pData);

public:
	void ErrorLogicType(CXExprErrorEx *pErrorEx,long nErrorLogic);
	void ActionValueGradient(CItemRsltExprRun *pRsltExprRun,long nVarType,long nVarIndexType, const CString &strMacroID);//动作值递变
	void ReturnValueGradient(CItemRsltExprRun *pRsltExprRun);	//返回系数
	void MaxAngleValueGradient(CItemRsltExprRun *pRsltExprRun);//最大灵敏角	
	void ActionTimeValue(CItemRsltExprRun *pRsltExprRun);//动作时间

	//是否添加了“装置复归态”
	CItems* IsHasDevReset();
	BOOL IsItemDevReset(CGbItemBase *pItemBase);  //判断当前测试项，是不是属于装置复归态的
	BOOL IsGuideBookHasDvm();  //GuideBook是否已经添加了设备数据模型
	long GetGbCommCmdConfigs(CExBaseList *pListCommCmds, CExBaseList *pGbCommCmdConfigs);
	long GetDatasetsByGbCommCmd(CExBaseList *pListDatasets, CGbCommCmd *pGbCmd);
	void GetParentItemPath(const CString &strItemPath, CString &strParentPath); //从项目路径中，获取父项目路径。以$为分隔符
	long GetAllAinItems(CExBaseList *pDestLists);
	long GetAllAinItems(CGbItemBase *pItemBase, CExBaseList *pDestLists);
	BOOL IsAinItems(const CString &strItemsID);
};
