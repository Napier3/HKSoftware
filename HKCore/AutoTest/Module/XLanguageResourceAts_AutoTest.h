#pragma once

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLanguageResourceAts.h"

class CXLanguageResourceAts_AutoTest : public CXLanguageResourceAtsBase
{
// 构造
public:
	CXLanguageResourceAts_AutoTest();
	virtual ~CXLanguageResourceAts_AutoTest();
	
private:
	CXLanguage m_oXLangRsAutoTest;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();

	//2023-3-1  lijunqing
	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsAutoTestFile;
	extern CString g_sLangID_AutoTestVTip;//智能自动测试系统V1.0
	extern CString g_sLangTxt_AutoTestVTip;
// 	extern CString g_sLangID_FileOpen; 
// 	extern CString g_sLangTxt_FileOpen;
	extern CString g_sLangID_FileOpenTip; 
	extern CString g_sLangTxt_FileOpenTip;
	extern CString g_sLangID_Quit; 
	extern CString g_sLangTxt_Quit;
	extern CString g_sLangID_QuitTip; 
	extern CString g_sLangTxt_QuitTip;
	extern CString g_sLangID_RibbonRecentDocs; 
	extern CString g_sLangTxt_RibbonRecentDocs;
	extern CString g_sLangID_Config; 
	extern CString g_sLangTxt_Config;
	extern CString g_sLangID_AutoTestOper; 
	extern CString g_sLangTxt_AutoTestOper;
// 	extern CString g_sLangID_UpLoad; 
// 	extern CString g_sLangTxt_UpLoad;
// 	extern CString g_sLangID_DownLoad; 
// 	extern CString g_sLangTxt_DownLoad;
	extern CString g_sLangID_NewTest; 
	extern CString g_sLangTxt_NewTest;
	extern CString g_sLangID_MultiDevTest; 
	extern CString g_sLangTxt_MultiDevTest;
	extern CString g_sLangID_SinDevMulPro; 
	extern CString g_sLangTxt_SinDevMulPro;
	extern CString g_sLangID_MdvMgrpTest; 
	extern CString g_sLangTxt_MdvMgrpTest;
	extern CString g_sLangID_SubTempTest; 
	extern CString g_sLangTxt_SubTempTest;
	extern CString g_sLangID_SingleDevTest;
	extern CString g_sLangTxt_SingleDevTest;
	extern CString g_sLangID_UsePowerTestTemplate;
	extern CString g_sLangTxt_UsePowerTestTemplate;
	extern CString g_sLangID_Test;
	extern CString g_sLangTxt_Test; 
    extern CString g_sLangID_StartTest; 
	extern CString g_sLangTxt_StartTest;
	extern CString g_sLangID_StartReport;
	extern CString g_sLangTxt_StartReport;	
	extern CString g_sLangID_Stop; 
	extern CString g_sLangTxt_Stop;
	extern CString g_sLangID_Report; 
	extern CString g_sLangTxt_Report;
	extern CString g_sLangID_ShowScale; 
	extern CString g_sLangTxt_ShowScale;
	extern CString g_sLangID_AdReport; 
	extern CString g_sLangTxt_AdReport;
	extern CString g_sLangID_PrintReport; 
	extern CString g_sLangTxt_PrintReport;
	extern CString g_sLangID_Settings; 
	extern CString g_sLangTxt_Settings;	
	extern CString g_sLangID_ReConfig; 
	extern CString g_sLangTxt_ReConfig;
// 	extern CString g_sLangID_View; 
// 	extern CString g_sLangTxt_View;	
// 	extern CString g_sLangID_StatusBarTip; 
// 	extern CString g_sLangTxt_StatusBarTip;
	extern CString g_sLangID_OutpWind; 
	extern CString g_sLangTxt_OutpWind;
	extern CString g_sLangID_FileManBar; 
	extern CString g_sLangTxt_FileManBar;
	extern CString g_sLangID_TestInfBar; 
	extern CString g_sLangTxt_TestInfBar;//测试任务栏
	extern CString g_sLangID_SdvMgrpReTest; 
	extern CString g_sLangTxt_SdvMgrpReTest;//测试任务栏
	extern CString g_sLangID_CharCurTest; 
	extern CString g_sLangTxt_CharCurTest;//特性曲线测试
	extern CString g_sLangID_TestTaskBar;
	extern CString g_sLangTxt_TestTaskBar;
	extern CString g_sLangID_ShowTestInf; 
	extern CString g_sLangTxt_ShowTestInf;
	extern CString g_sLangID_ShowTestSpyWnd; 
	extern CString g_sLangTxt_ShowTestSpyWnd;
	extern CString g_sLangID_WriteLogFile; 
	extern CString g_sLangTxt_WriteLogFile;
	extern CString g_sLangID_ViewWordRpt; 
	extern CString g_sLangTxt_ViewWordRpt;
// 	extern CString g_sLangID_AboutTip; 
	extern CString g_sLangTxt_AboutTip;
	extern CString g_sLangID_ToAndCom; 
	extern CString g_sLangTxt_ToAndCom;
	extern CString g_sLangID_SysTools; 
	extern CString g_sLangTxt_SysTools;
	extern CString g_sLangID_SysCom; 
	extern CString g_sLangTxt_SysCom;
	extern CString g_sLangID_TestFileMan; 
	extern CString g_sLangTxt_TestFileMan;
	extern CString g_sLangID_TestItemField; 
	extern CString g_sLangTxt_TestItemField;
	extern CString g_sLangID_NewTestWork; //新建测试任务
	extern CString g_sLangTxt_NewTestWork;
	extern CString g_sLangID_TestInf; 
	extern CString g_sLangTxt_TestInf;
	extern CString g_sLangID_TaskName; 
	extern CString g_sLangTxt_TaskName;
	extern CString g_sLangID_TestType; 
	extern CString g_sLangTxt_TestType;
	extern CString g_sLangID_ProSet; 
	extern CString g_sLangTxt_ProSet;
	extern CString g_sLangID_ChoProTem; //选择规约模板
	extern CString g_sLangTxt_ChoProTem;
	extern CString g_sLangID_PoFile; 
	extern CString g_sLangTxt_PoFile;
	extern CString g_sLangID_ChoTest; 
	extern CString g_sLangTxt_ChoTest;
	extern CString g_sLangID_SelPoFile; //选择点表文件
	extern CString g_sLangTxt_SelPoFile;
	extern CString g_sLangID_TitleTask; 
	extern CString g_sLangTxt_TitleTask;
	extern CString g_sLangID_NewBuilt; //新建
	extern CString g_sLangTxt_NewBuilt;
	extern CString g_sLangID_ReportAdjSh;//报告调整提示 
	extern CString g_sLangTxt_ReportAdjSh;
	extern CString g_sLangID_TestChoPro;//测试仪选择（测试仪器选择改变，需重新启动自动测试程序才能是改变生效） 
	extern CString g_sLangTxt_TestChoPro;
	extern CString g_sLangID_AutoTestSysSet;//自动测试系统配置 
	extern CString g_sLangTxt_AutoTestSysSet;
	extern CString g_sLangID_AlarmAutoMain;//警告—自动测试主程序 
	extern CString g_sLangTxt_AlarmAutoMain;
	extern CString g_sLangID_TestFileName; //测试文件名
	extern CString g_sLangTxt_TestFileName;
	extern CString g_sLangID_TesTyp; //测试类型
	extern CString g_sLangTxt_TesTyp;
	extern CString g_sLangID_ProTypeCho; //规约种类选择
	extern CString g_sLangTxt_ProTypeCho;
	extern CString g_sLangID_TestTempFile; //测试模板文件
	extern CString g_sLangTxt_TestTempFile;
	extern CString g_sLangID_ProTempFile; //规约模板文件
	extern CString g_sLangTxt_ProTempFile;
	extern CString g_sLangID_ProHighSet; //规约高级设置
	extern CString g_sLangTxt_ProHighSet;
	extern CString g_sLangID_ProTabFile; //规约点表文件
	extern CString g_sLangTxt_ProTabFile;
	extern CString g_sLangID_RptData; //报告数据
	extern CString g_sLangTxt_RptData;
	extern CString g_sLangID_RptData2; //报告数据2
	extern CString g_sLangTxt_RptData2;
	extern CString g_sLangID_RptLog; //报告数据
	extern CString g_sLangTxt_RptLog;
	extern CString g_sLangID_TestTemp; //测试模板
	extern CString g_sLangTxt_TestTemp;
	extern CString g_sLangID_AppTestNo; //出现测试不合格项目处理
	extern CString g_sLangTxt_AppTestNo;
	extern CString g_sLangID_CTestCNum; //重复测试项目重复次数
	extern CString g_sLangTxt_CTestCNum;
	extern CString g_sLangID_CoeMus; //提示音乐
	extern CString g_sLangTxt_CoeMus;
	extern CString g_sLangID_AlarmMode; //告警方式
	extern CString g_sLangTxt_AlarmMode;
	extern CString g_sLangID_ContTest; //继续测试
	extern CString g_sLangTxt_ContTest;
	extern CString g_sLangID_LongAlarm; //长警告
	extern CString g_sLangTxt_LongAlarm;
	extern CString g_sLangID_ShortAlarm; //短警告
	extern CString g_sLangTxt_ShortAlarm;
	extern CString g_sLangID_CusRepeat; //自定义最大重复次数
	extern CString g_sLangTxt_CusRepeat;
	extern CString g_sLangID_ComFaReNu; //通讯失败后重试次数
	extern CString g_sLangTxt_ComFaReNu;
	extern CString g_sLangID_RetComS; //重试通讯前延时
	extern CString g_sLangTxt_RetComS;
	extern CString g_sLangID_TestCoDe; //测试项目测试完成出来
	extern CString g_sLangTxt_TestCoDe;
	extern CString g_sLangID_CoNuShow; //完成一级项目时进行提示
	extern CString g_sLangTxt_CoNuShow;
	extern CString g_sLangID_TestCoRe; //测试完成，报告自动导出路径（测试模板须调用……）
	extern CString g_sLangTxt_TestCoRe;
	extern CString g_sLangID_AdjustReportInfo; //调整报告完成如下操作
	extern CString g_sLangTxt_AdjustReportInfo;
// 	extern CString g_sLangID_DeNoChTe; //1.删除没有选择测试的项目分类报告部分
// 	extern CString g_sLangTxt_DeNoChTe;
// 	extern CString g_sLangID_RepUse; //2.对于没有测试的测试点，空白部分报告使用“——”替换
// 	extern CString g_sLangTxt_RepUse;
// 	extern CString g_sLangID_AdjustSure; //调整部分不可以回复，确定要调整吗？
// 	extern CString g_sLangTxt_AdjustSure;
	extern CString g_sLangID_StartX; //起点X
	extern CString g_sLangTxt_StartX;	
	extern CString g_sLangID_StartY; //起点Y
	extern CString g_sLangTxt_StartY;	
	extern CString g_sLangID_NowX; //当前X
	extern CString g_sLangTxt_NowX;
	extern CString g_sLangID_NowY; //当前Y
	extern CString g_sLangTxt_NowY;
	extern CString g_sLangID_EndPointX; //终点X
	extern CString g_sLangTxt_EndPointX;
	extern CString g_sLangID_EndPointY; //终点Y
	extern CString g_sLangTxt_EndPointY;
	extern CString g_sLangID_TestConR; //与测试仪控制接口程序握手，30s内握手失败，则终止进程，重新启动测试仪接口程序
	extern CString g_sLangTxt_TestConR;
	extern CString g_sLangID_WarningProTest; //程序检测到系统中有和系统相关的进程正在运行，点击“终止进程”关闭所有进程
	extern CString g_sLangTxt_WarningProTest;
	extern CString g_sLangID_StopProcess; //终止进程
	extern CString g_sLangTxt_StopProcess;
	extern CString g_sLangID_NeedCloPro; //需要关闭的进程
	extern CString g_sLangTxt_NeedCloPro;
	extern CString g_sLangID_SouRepPath;      //源报告路径
	extern CString g_sLangTxt_SouRepPath;
	extern CString g_sLangID_ExportSet;       //导出设置
	extern CString g_sLangTxt_ExportSet;
	extern CString g_sLangID_ExportPath;      //导出路径
	extern CString g_sLangTxt_ExportPath;
	extern CString g_sLangID_ExFileName;      //导出文件名称
	extern CString g_sLangTxt_ExFileName;
	extern CString g_sLangID_ChoFileModel;    //选择文件模型
	extern CString g_sLangTxt_ChoFileModel;
	extern CString g_sLangID_RepViewRat;    //报告显示比例
	extern CString g_sLangTxt_RepViewRat;
	extern CString g_sLangID_RepViRaCho;    //报告显示比例选择
	extern CString g_sLangTxt_RepViRaCho;
	extern CString g_sLangID_TestRepViRaSet;    //试验报告显示比例设置
	extern CString g_sLangTxt_TestRepViRaSet;
	extern CString g_sLangID_NoChProTem;//没有选择规约模板
	extern CString g_sLangTxt_NoChProTem;
	extern CString g_sLangID_NoChTestTem;//没有选择测试模板
	extern CString g_sLangTxt_NoChTestTem;
	extern CString g_sLangID_ChTemplet;//选择模板
	extern CString g_sLangTxt_ChTemplet;
	extern CString g_sLangID_ChProtocol;//选择规约
	extern CString g_sLangTxt_ChProtocol;
	extern CString g_sLangID_SettingsChoose;//设置组选择
	extern CString g_sLangTxt_SettingsChoose;
	extern CString g_sLangID_SetMulDev;//设置多装置
	extern CString g_sLangTxt_SetMulDev;
	extern CString g_sLangID_SetMulDevMgrp;//设置多装置多组
	extern CString g_sLangTxt_SetMulDevMgrp;
	extern CString g_sLangID_NoChTemFile;//没有选择模板文件
	extern CString g_sLangTxt_NoChTemFile;
	extern CString g_sLangID_RepFileNameNu;//报告文件名为空
	extern CString g_sLangTxt_RepFileNameNu;
	extern CString g_sLangID_NoChTestType;//没有选择测试类型
	extern CString g_sLangTxt_NoChTestType;
	extern CString g_sLangID_CommSetInf;//通讯设置信息不全
	extern CString g_sLangTxt_CommSetInf;
	extern CString g_sLangID_TabFileNoSel;//点表文件没有选择
	extern CString g_sLangTxt_TabFileNoSel;
	extern CString g_sLangID_AlreadyExists;//%s 已经存在
	extern CString g_sLangTxt_AlreadyExists;
	extern CString g_sLangID_UnquaItem;//不合格项目
	extern CString g_sLangTxt_UnquaItem;
// 	extern CString g_sLangID_ModelFile;//模型文件
// 	extern CString g_sLangTxt_ModelFile;
	extern CString g_sLangID_NoAddDevTestRep;//没有添加装置测试报告
	extern CString g_sLangTxt_NoAddDevTestRep;
	extern CString g_sLangID_OlAddOnRep;//只添加了一个装置测试报告
	extern CString g_sLangTxt_OlAddOnRep;
	extern CString g_sLangID_ProtocoTemplate;//规约模板
	extern CString g_sLangTxt_ProtocoTemplate;
	extern CString g_sLangID_ProtocoMatching;//规约配型
	extern CString g_sLangTxt_ProtocoMatching;
	extern CString g_sLangID_ChRptRe;//选择报告导出目标目录
	extern CString g_sLangTxt_ChRptRe;
	extern CString g_sLangID_AlOpen;//已经打开【%s】，请关闭后在创建测试报告！
	extern CString g_sLangTxt_AlOpen;
	extern CString g_sLangID_TaskTotalTime;//任务总时间
	extern CString g_sLangTxt_TaskTotalTime;
	extern CString g_sLangID_RptTotalTime;//报告总时间
	extern CString g_sLangTxt_RptTotalTime;
	extern CString g_sLangID_NoTitle;//无标题
	extern CString g_sLangTxt_NoTitle;
	extern CString g_sLangID_TestingClose;//正在测试中，不能关闭...
	extern CString g_sLangTxt_TestingClose;
	extern CString g_sLangID_FileUnExistS;//文件\"%s\"不存在
	extern CString g_sLangTxt_FileUnExistS;
	extern CString g_sLangID_SelOrCretFile;//文件夹【%s】包含有测试报告文件\n请选择或者创建一个空的文件夹
	extern CString g_sLangTxt_SelOrCretFile;
	extern CString g_sLangID_SelFilePath;//请选择报告文件存储的路径！
	extern CString g_sLangTxt_SelFilePath;
	extern CString g_sLangID_DelTaskYOrN;//是否要删除任务 %s 及其子项
	extern CString g_sLangTxt_DelTaskYOrN;
	extern CString g_sLangID_SureDelAgain;//请再次确定删除
	extern CString g_sLangTxt_SureDelAgain;
	extern CString g_sLangID_DelFailItem;//删除的任务中包含已经被打开的工程，删除失败
	extern CString g_sLangTxt_DelFailItem;
	extern CString g_sLangID_DelItemYOrN;//是否要删除工程 %s
	extern CString g_sLangTxt_DelItemYOrN;
	extern CString g_sLangID_DelFailure;//该工程已经被打开，删除失败
	extern CString g_sLangTxt_DelFailure;
	extern CString g_sLangID_StartRptYOrN;//“开始报告”功能只测试当前打开的测试报告，\r\n你确实只要测试测试任务中的单个测试报告吗？\r\n\r\n选择“是”测试单个报告\r\n选择“否”开始任务测试\r\n选择“取消”终止操作")
	extern CString g_sLangTxt_StartRptYOrN;
	extern CString g_sLangID_NewTestClear;//新建测试，清除当前报告数据吗？\r\n
	extern CString g_sLangTxt_NewTestClear;
	extern CString g_sLangID_SelYes;//选择“是”清除当前报告数据，新建测试\r\n
	extern CString g_sLangTxt_SelYes;
	extern CString g_sLangID_SelNo;//选择“否”，不清除当前报告数据，新建测试\r\n
	extern CString g_sLangTxt_SelNo;
	extern CString g_sLangID_SelCancel;//选择“取消”，不开始测试
	extern CString g_sLangTxt_SelCancel;
	extern CString g_sLangID_WavCpntNotExist;//录波组件不存在
	extern CString g_sLangTxt_WavCpntNotExist;
	extern CString g_sLangID_UnAutoTest;//没有启动自动测试，无法执行命令
	extern CString g_sLangTxt_UnAutoTest;
	extern CString g_sLangID_ToolUnExitS;//工具【%s】【%s】不存在
	extern CString g_sLangTxt_ToolUnExitS;
	extern CString g_sLangID_TestTaskFnshS;//测试任务【%s】测试完成
	extern CString g_sLangTxt_TestTaskFnshS;
	extern CString g_sLangID_StartTestS;//开始测试【%s】
	extern CString g_sLangTxt_StartTestS;
	extern CString g_sLangID_TestTempS;//测试模板*******%s
	extern CString g_sLangTxt_TestTempS;
	extern CString g_sLangID_ReportFileS;//报告文件*******%s
	extern CString g_sLangTxt_ReportFileS;
	extern CString g_sLangID_ModelFileS;//模型文件********%s
	extern CString g_sLangTxt_ModelFileS;
	extern CString g_sLangID_PrtcTemS;//规约模板********%s
	extern CString g_sLangTxt_PrtcTemS;
	extern CString g_sLangID_AutoTestContrl;//自动测试控制中心
	extern CString g_sLangTxt_AutoTestContrl;
// 	extern CString g_sLangID_SGroupS;//%s%s-组%d.%s
// 	extern CString g_sLangTxt_SGroupS;
// 	extern CString g_sLangID_SGroupFileName;//%s%s-组%d.%s
// 	extern CString g_sLangTxt_SGroupFileName;
	extern CString g_sLangID_RightBuy;//Demo版本，只能使用模板【Demo-PSL-641U】，请购买正式版本！
	extern CString g_sLangTxt_RightBuy;
	extern CString g_sLangID_MainView2;//主视图:
	extern CString g_sLangTxt_MainView2;
	extern CString g_sLangID_GroupReport;//组%d报告
	extern CString g_sLangTxt_GroupReport;
	extern CString g_sLangID_ProcessStop;//和测试相关的进程已经被终止
	extern CString g_sLangTxt_ProcessStop;
	extern CString g_sLangID_SelObjPath;//选择目标路径
	extern CString g_sLangTxt_SelObjPath;
	extern CString g_sLangID_FileNameIncl;//文件名称包含非法字符: %s
	extern CString g_sLangTxt_FileNameIncl;
	extern CString g_sLangID_ReportEptFinsh;//报告导出完成
	extern CString g_sLangTxt_ReportEptFinsh;
	extern CString g_sLangID_ObjFileExistOvwt;//目标文件已经存在,覆盖吗?
	extern CString g_sLangTxt_ObjFileExistOvwt;
	extern CString g_sLangID_ReportTestTempt;//报告【%s】对应的测试模板:【%s】
	extern CString g_sLangTxt_ReportTestTempt;
	extern CString g_sLangID_SureToDele;//你确实要删除【%s】吗？
	extern CString g_sLangTxt_SureToDele;
	extern CString g_sLangID_UnQualifadS;//[%s]不合格
	extern CString g_sLangTxt_UnQualifadS;
	extern CString g_sLangID_TestOver;//********测试结束********
	extern CString g_sLangTxt_TestOver;
	extern CString g_sLangID_CopyOutput;//复制输出
	extern CString g_sLangTxt_CopyOutput;
	extern CString g_sLangID_ClearOutput;//清除输出
	extern CString g_sLangTxt_ClearOutput;
// 	extern CString g_sLangID_Unqualified2;//%s[不合格]
// 	extern CString g_sLangTxt_Unqualified2;
	extern CString g_sLangID_NoAddTestRpt;//没有添加测试报告
	extern CString g_sLangTxt_NoAddTestRpt;
	extern CString g_sLangID_OneTestRpt;//只添加了一个测试报告
	extern CString g_sLangTxt_OneTestRpt;
	extern CString g_sLangID_NoSelPrtcTem;//装置报告列表第【%d】没有选择规约模板
	extern CString g_sLangTxt_NoSelPrtcTem;
	extern CString g_sLangID_NoSelFile;//装置报告列表第【%d】没有选择点表文件
	extern CString g_sLangTxt_NoSelFile;
	extern CString g_sLangID_NameSame;//装置报告列表第【%d】与第【%d】名称【%s】相同
	extern CString g_sLangTxt_NameSame;
	extern CString g_sLangID_PrtcSame;//装置报告列表第【%d】与第【%d】规约模板【%s】相同
	extern CString g_sLangTxt_PrtcSame;
	extern CString g_sLangID_IPSame;//装置报告列表第【%d】与第【%d】IP【%s】相同
	extern CString g_sLangTxt_IPSame;
	extern CString g_sLangID_ToolTip_32781;//打开报告
	extern CString g_sLangTxt_ToolTip_32781;
	extern CString g_sLangID_ToolTip_32776;//添加报告
	extern CString g_sLangTxt_ToolTip_32776;
	extern CString g_sLangID_ToolTip_32777;//删除报告
	extern CString g_sLangTxt_ToolTip_32777;
	extern CString g_sLangID_ToolTip_32783;//恢复到未完成的状态
	extern CString g_sLangTxt_ToolTip_32783;
	extern CString g_sLangID_ToolTip_32778;//上移报告
    extern CString g_sLangTxt_ToolTip_32778;
	extern CString g_sLangID_ToolTip_32779;//下移报告
	extern CString g_sLangTxt_ToolTip_32779;
	extern CString g_sLangID_ToolTip_32784;//显示报告对应的模板
	extern CString g_sLangTxt_ToolTip_32784;
	extern CString g_sLangID_ToolTip_32775;//导出任务报告
	extern CString g_sLangTxt_ToolTip_32775;
	extern CString g_sLangID_ToolTip_32782;//关闭任务
	extern CString g_sLangTxt_ToolTip_32782;

	extern CString g_sLangID_Menu_57634;
	extern CString g_sLangTxt_Menu_57634;
	extern CString g_sLangID_Menu_57632;
	extern CString g_sLangTxt_Menu_57632;

	extern CString g_sLangID_ToolTip_32789;
	extern CString g_sLangTxt_ToolTip_32789;
	extern CString g_sLangID_StitchRptFinish;
	extern CString g_sLangTxt_StitchRptFinish;

	//2016-12-10
	extern CString g_sLangID_ToolTip_2000;
	extern CString g_sLangTxt_ToolTip_2000;
	extern CString g_sLangID_ToolTip_32786;
	extern CString g_sLangTxt_ToolTip_32786;
	extern CString g_sLangID_ToolTip_32788;
	extern CString g_sLangTxt_ToolTip_32788;
	extern CString g_sLangID_ToolTip_2001;
	extern CString g_sLangTxt_ToolTip_2001;
	extern CString g_sLangID_ToolTip_32785;
	extern CString g_sLangTxt_ToolTip_32785;
	extern CString g_sLangID_ToolTip_351;
	extern CString g_sLangTxt_ToolTip_351;
	extern CString g_sLangID_ToolTip_314;
	extern CString g_sLangTxt_ToolTip_314;
	extern CString g_sLangID_ToolTip_320;
	extern CString g_sLangTxt_ToolTip_320;
	extern CString g_sLangID_ToolTip_330;
	extern CString g_sLangTxt_ToolTip_330;
	extern CString g_sLangID_ToolTip_358;
	extern CString g_sLangTxt_ToolTip_358;
	extern CString g_sLangID_ToolTip_347;
	extern CString g_sLangTxt_ToolTip_347;
	extern CString g_sLangID_ToolTip_310;
	extern CString g_sLangTxt_ToolTip_310;
	extern CString g_sLangID_ToolTip_348;
	extern CString g_sLangTxt_ToolTip_348;
	extern CString g_sLangID_ToolTip_349;
	extern CString g_sLangTxt_ToolTip_349;
	extern CString g_sLangID_ToolTip_350;
	extern CString g_sLangTxt_ToolTip_350;
	extern CString g_sLangID_ToolTip_357;
	extern CString g_sLangTxt_ToolTip_357;

	//shaolei 2024-3-25
	extern CString g_sLangID_GbDevice;  //=_T("sGbDevice");
	extern CString g_sLangTxt_GbDevice;  //=_T("设备");
	extern CString g_sLangID_SysParaCfg;  //=_T("sSysParaCfg");
	extern CString g_sLangTxt_SysParaCfg;  //=_T("系统参数配置");
	extern CString g_sLangID_ChMapsConfig;  //= _T("sChMapsConfig");
	extern CString g_sLangTxt_ChMapsConfig;  //= _T("硬件通道映射");
	extern CString g_sLangID_Iec61850Cfg;  //=_T("sIec61850Cfg");
	extern CString g_sLangTxt_Iec61850Cfg;  //=_T("IEC61850配置");
	extern CString g_sLangID_BeforeTest;  //=_T("sBeforeTest");
	extern CString g_sLangTxt_BeforeTest;  //=_T("测试前准备");
	extern CString g_sLangID_NotTest;  //=_T("sNotTest");
	extern CString g_sLangTxt_NotTest;  //=_T("未测试");
	extern CString g_sLangID_RsltEvaluation;  //=_T("sRsltEvaluation");
	extern CString g_sLangTxt_RsltEvaluation;  //=_T("结果评估");
	extern CString g_sLangID_TSet;  //=_T("sTSet");
	extern CString g_sLangTxt_TSet;  //=_T("动作时间整定值(s)");
	extern CString g_sLangID_USet;  //=_T("sUSet");
	extern CString g_sLangTxt_USet;  //=_T("电压整定动作值(V)");
	extern CString g_sLangID_ISet;  //=_T("sISet");
	extern CString g_sLangTxt_ISet;  //=_T("电流整定动作值(A)");
	extern CString g_sLangID_AngleSet;  //=_T("sAngleSet");
	extern CString g_sLangTxt_AngleSet;  //=_T("相位整定动作值(°)");
	extern CString g_sLangID_HzSet;  //=_T("sHzSet");
	extern CString g_sLangTxt_HzSet;  //=_T("频率整定动作值(Hz)");
	extern CString g_sLangID_ReturnCoefSet;  //=_T("sReturnCoefSet");
	extern CString g_sLangTxt_ReturnCoefSet;  //=_T("返回系数整定值");
	extern CString g_sLangID_MaxAngleSet;  //=_T("sMaxAngleSet");
	extern CString g_sLangTxt_MaxAngleSet;  //=_T("最大灵敏角整定值(°)");
	extern CString g_sLangID_AngleFSet;  //=_T("sAngleFSet");
	extern CString g_sLangTxt_AngleFSet;  //=_T("边界角1整定值(°)");
	extern CString g_sLangID_AngleSSet;  //=_T("sAngleSSet");
	extern CString g_sLangTxt_AngleSSet;  //=_T("边界角2整定值(°)");
	extern CString g_sLangID_T_AbsErr_Max;  //=_T("sT_AbsErr_Max");
	extern CString g_sLangTxt_T_AbsErr_Max;  //=_T("动作时间绝对误差最大值(ms)");
	extern CString g_sLangID_T_AbsErr_Min;  //=_T("sT_AbsErr_Min");
	extern CString g_sLangTxt_T_AbsErr_Min;  //=_T("动作时间绝对误差最小值(ms)");
	extern CString g_sLangID_T_RelErr_Max;  //=_T("sT_RelErr_Max");
	extern CString g_sLangTxt_T_RelErr_Max;  //=_T("动作时间相对误差最大值(%)");
	extern CString g_sLangID_T_RelErr_Min;  //=_T("sT_RelsErr_Min");
	extern CString g_sLangTxt_T_RelErr_Min;  //=_T("动作时间相对误差最小值(%)");
	extern CString g_sLangID_U_AbsErr_Max;  //=_T("sU_AbsErr_Max");
	extern CString g_sLangTxt_U_AbsErr_Max;  //=_T("电压动作值绝对误差最大值(V)");
	extern CString g_sLangID_U_AbsErr_Min;  //=_T("sU_AbsErr_Min");
	extern CString g_sLangTxt_U_AbsErr_Min;  //=_T("电压动作值绝对误差最小值(V)");
	extern CString g_sLangID_U_RelErr_Max;  //=_T("sU_RelErr_Max");
	extern CString g_sLangTxt_U_RelErr_Max;  //=_T("电压动作值相对误差最大值(%)");
	extern CString g_sLangID_U_RelErr_Min;  //=_T("sU_RelsErr_Min");
	extern CString g_sLangTxt_U_RelErr_Min;  //=_T("电压动作值相对误差最小值(%)");
	extern CString g_sLangID_I_AbsErr_Max;  //=_T("sI_AbsErr_Max");
	extern CString g_sLangTxt_I_AbsErr_Max;  //=_T("电流动作值绝对误差最大值(A)");
	extern CString g_sLangID_I_AbsErr_Min;  //=_T("sI_AbsErr_Min");
	extern CString g_sLangTxt_I_AbsErr_Min;  //=_T("电流动作值绝对误差最小值(A)");
	extern CString g_sLangID_I_RelErr_Max;  //=_T("sI_RelErr_Max");
	extern CString g_sLangTxt_I_RelErr_Max;  //=_T("电流动作值相对误差最大值(%)");
	extern CString g_sLangID_I_RelErr_Min;  //=_T("sI_RelsErr_Min");
	extern CString g_sLangTxt_I_RelErr_Min;  //=_T("电流动作值相对误差最小值(%)");
	extern CString g_sLangID_Angle_AbsErr_Max;  //=_T("sAngle_AbsErr_Max");
	extern CString g_sLangTxt_Angle_AbsErr_Max;  //=_T("相位动作值绝对误差最大值(°)");
	extern CString g_sLangID_Angle_AbsErr_Min;  //=_T("sAngle_AbsErr_Min");
	extern CString g_sLangTxt_Angle_AbsErr_Min;  //=_T("相位动作值绝对误差最小值(°)");
	extern CString g_sLangID_Hz_AbsErr_Max;  //=_T("sHz_AbsErr_Max");
	extern CString g_sLangTxt_Hz_AbsErr_Max;  //=_T("频率动作值绝对误差最大值(Hz)");
	extern CString g_sLangID_Hz_AbsErr_Min;  //=_T("sHz_AbsErr_Min");
	extern CString g_sLangTxt_Hz_AbsErr_Min;  //=_T("频率动作值绝对误差最小值(Hz)");
	extern CString g_sLangID_RetCoef_AbsErr_Max;  //=_T("sRetCoef_AbsErr_Max");
	extern CString g_sLangTxt_RetCoef_AbsErr_Max;  //=_T("返回系数绝对误差最大值");
	extern CString g_sLangID_RetCoef_AbsErr_Min;  //=_T("sRetCoef_AbsErr_Min");
	extern CString g_sLangTxt_RetCoef_AbsErr_Min;  //=_T("返回系数绝对误差最小值");
	extern CString g_sLangID_MaxAngle_AbsErr_Max;  //=_T("sMaxAngle_AbsErr_Max");
	extern CString g_sLangTxt_MaxAngle_AbsErr_Max;  //=_T("最大灵敏角绝对误差最大值(°)");
	extern CString g_sLangID_MaxAngle_AbsErr_Min;  //=_T("sMaxAngle_AbsErr_Min");
	extern CString g_sLangTxt_MaxAngle_AbsErr_Min;  //=_T("最大灵敏角绝对误差最小值(°)");
	extern CString g_sLangID_AngleF_AbsErr_Max;  //=_T("sAngleF_AbsErr_Max");
	extern CString g_sLangTxt_AngleF_AbsErr_Max;  //=_T("边界角1绝对误差最大值(°)");
	extern CString g_sLangID_AngleF_AbsErr_Min;  //=_T("sAngleF_AbsErr_Min");
	extern CString g_sLangTxt_AngleF_AbsErr_Min;  //=_T("边界角1绝对误差最小值(°)");
	extern CString g_sLangID_AngleS_AbsErr_Max;  //=_T("sAngleS_AbsErr_Max");
	extern CString g_sLangTxt_AngleS_AbsErr_Max;  //=_T("边界角2绝对误差最大值(°)");
	extern CString g_sLangID_AngleS_AbsErr_Min;  //=_T("sAngleS_AbsErr_Min");
	extern CString g_sLangTxt_AngleS_AbsErr_Min;  //=_T("边界角2角绝对误差最小值(°)");
	extern CString g_sLangID_T_Act;  //=_T("sT_Act");
	extern CString g_sLangTxt_T_Act;  //=_T("动作时间(s)");
	extern CString g_sLangID_T_ErrRel;  //=_T("sT_ErrRel");
	extern CString g_sLangTxt_T_ErrRel;  //=_T("动作时间相对误差限(%)");
	extern CString g_sLangID_T_ErrAbs;  //=_T("sT_ErrAbs");
	extern CString g_sLangTxt_T_ErrAbs;  //=_T("动作时间绝对误差限(s)");
	extern CString g_sLangID_T_RelErr;  //=_T("sT_RelErr");
	extern CString g_sLangTxt_T_RelErr;  //=_T("动作时间相对误差值(%)");
	extern CString g_sLangID_T_AbsErr;  //=_T("sT_AbsErr");
	extern CString g_sLangTxt_T_AbsErr;  //=_T("动作时间绝对误差值(ms)");
	extern CString g_sLangID_U_RelErr;  //=_T("sU_RelErr");
	extern CString g_sLangTxt_U_RelErr;  //=_T("电压动作值相对误差值(%)");
	extern CString g_sLangID_U_AbsErr;  //=_T("sU_AbsErr");
	extern CString g_sLangTxt_U_AbsErr;  //=_T("电压动作值绝对误差值(V)");
	extern CString g_sLangID_U_ErrRel;  //=_T("sU_ErrRel");
	extern CString g_sLangTxt_U_ErrRel;  //=_T("电压动作值相对误差限(%)");
	extern CString g_sLangID_U_ErrAbs;  //=_T("sU_ErrAbs");
	extern CString g_sLangTxt_U_ErrAbs;  //=_T("电压动作值绝对误差限(V)");
	extern CString g_sLangID_U_Act;  //=_T("sU_Act");
	extern CString g_sLangTxt_U_Act;  //=_T("电压动作值(V)");
	extern CString g_sLangID_I_RelErr;  //=_T("sI_RelErr");
	extern CString g_sLangTxt_I_RelErr;  //=_T("电流动作值相对误差值(%)");
	extern CString g_sLangID_I_AbsErr;  //=_T("sI_AbsErr");
	extern CString g_sLangTxt_I_AbsErr;  //=_T("电流动作值绝对误差值(A)");
	extern CString g_sLangID_I_ErrRel;  //=_T("sI_ErrRel");
	extern CString g_sLangTxt_I_ErrRel;  //=_T("电流动作值相对误差限(%)");
	extern CString g_sLangID_I_ErrAbs;  //=_T("sI_ErrAbs");
	extern CString g_sLangTxt_I_ErrAbs;  //=_T("电流动作值绝对误差限(A)");
	extern CString g_sLangID_I_Act;  //=_T("sI_Act");
	extern CString g_sLangTxt_I_Act;  //=_T("电流动作值(A)");
	extern CString g_sLangID_Angle_RelErr;  //=_T("sAngle_RelErr");
	extern CString g_sLangTxt_Angle_RelErr;  //=_T("相位动作值相对误差值(%)");
	extern CString g_sLangID_Angle_AbsErr;  //=_T("sAngle_AbsErr");
	extern CString g_sLangTxt_Angle_AbsErr;  //=_T("相位动作值绝对误差值(°)");
	extern CString g_sLangID_Angle_ErrRel;  //=_T("sAngle_ErrRel");
	extern CString g_sLangTxt_Angle_ErrRel;  //=_T("相位动作值相对误差限(%)");
	extern CString g_sLangID_Angle_ErrAbs;  //=_T("sAngle_ErrAbs");
	extern CString g_sLangTxt_Angle_ErrAbs;  //=_T("相位动作值绝对误差限(°)");
	extern CString g_sLangID_Angle_Act;  //=_T("sAngle_Act");
	extern CString g_sLangTxt_Angle_Act;  //=_T("相位动作值(°)");
	extern CString g_sLangID_Hz_RelErr;  //=_T("sHz_RelErr");
	extern CString g_sLangTxt_Hz_RelErr;  //=_T("频率动作值相对误差值(%)");
	extern CString g_sLangID_Hz_AbsErr;  //=_T("sHz_AbsErr");
	extern CString g_sLangTxt_Hz_AbsErr;  //=_T("频率动作值绝对误差值(Hz)");
	extern CString g_sLangID_Hz_ErrRel;  //=_T("sHz_ErrRel");
	extern CString g_sLangTxt_Hz_ErrRel;  //=_T("频率动作值相对误差限(%)");
	extern CString g_sLangID_Hz_ErrAbs;  //=_T("sHz_ErrAbs");
	extern CString g_sLangTxt_Hz_ErrAbs;  //=_T("频率动作值绝对误差限(Hz)");
	extern CString g_sLangID_Hz_Act;  //=_T("sHz_Act");
	extern CString g_sLangTxt_Hz_Act;  //=_T("频率动作值(Hz)");
	extern CString g_sLangID_ReturnCoef_AbsErr;  //=_T("sReturnCoef_AbsErr");
	extern CString g_sLangTxt_ReturnCoef_AbsErr;  //=_T("返回系数绝对误差值");
	extern CString g_sLangID_ReturnCoef_ErrAbs;  //=_T("sReturnCoef_ErrAbs");
	extern CString g_sLangTxt_ReturnCoef_ErrAbs;  //=_T("返回系数绝对误差限");
	extern CString g_sLangID_ReturnCoef_Act;  //=_T("sReturnCoef_Act");
	extern CString g_sLangTxt_ReturnCoef_Act;  //=_T("返回系数");
	extern CString g_sLangID_MaxAngle_AbsErr;  //=_T("sMaxAngle_AbsErr");
	extern CString g_sLangTxt_MaxAngle_AbsErr;  //=_T("最大灵敏角值绝对误差值(°)");
	extern CString g_sLangID_MaxAngle_ErrAbs;  //=_T("sMaxAngle_ErrAbs");
	extern CString g_sLangTxt_MaxAngle_ErrAbs;  //=_T("最大灵敏角绝对误差限(°)");
	extern CString g_sLangID_AngleF_AbsErr;  //=_T("sAngleF_AbsErr");
	extern CString g_sLangTxt_AngleF_AbsErr;  //=_T("边界角1值绝对误差值(°)");
	extern CString g_sLangID_AngleF_ErrAbs;  //=_T("sAngleF_ErrAbs");
	extern CString g_sLangTxt_AngleF_ErrAbs;  //=_T("边界角1绝对误差限(°)");
	extern CString g_sLangID_AngleS_AbsErr;  //=_T("sAngleS_AbsErr");
	extern CString g_sLangTxt_AngleS_AbsErr;  //=_T("边界角2值绝对误差值(°)");
	extern CString g_sLangID_AngleS_ErrAbs;  //=_T("sAngleS_ErrAbs");
	extern CString g_sLangTxt_AngleS_ErrAbs;  //=_T("边界角2绝对误差限(°)");
	extern CString g_sLangID_ReadAin;  //=_T("sReadAin");
	extern CString g_sLangTxt_ReadAin;  //=_T("读遥测");
	extern CString g_sLangID_WriteSetting;  //=_T("sWriteSetting");
	extern CString g_sLangTxt_WriteSetting;  //=_T("修改定值");
	extern CString g_sLangID_WriteEna;  //=_T("sWriteEna");
	extern CString g_sLangTxt_WriteEna;  //=_T("投退压板");
	extern CString g_sLangID_Reset;  //=_T("sReset");
	extern CString g_sLangTxt_Reset;  //=_T("-复归态");
	extern CString g_sLangID_BeforeTestGrp;  //=_T("sBeforeTestGrp");
	extern CString g_sLangTxt_BeforeTestGrp;  //=_T("测试前_后组合");
	extern CString g_sLangID_ImportDvm;  //=_T("sImportDvm");
	extern CString g_sLangTxt_ImportDvm;  //=_T("导入模型");
	extern CString g_sLangID_BeforeComm;  //=_T("sBeforeComm");
	extern CString g_sLangTxt_BeforeComm;  //=_T("通信前准备");
	extern CString g_sLangID_AfterComm;  //=_T("sAfterComm");
	extern CString g_sLangTxt_IAfterComm;  //=_T("通信后恢复");


	//add 2024-8-27
	extern CString g_sLangID_SpowerSet;  //=_T("sSpowerSet");
	extern CString g_sLangTxt_SpowerSet;  //=_T("视在功率整定动作值(VA)");
	extern CString g_sLangID_Spower_RelErr;  //=_T("sSpower_ErrRel"); 
	extern CString g_sLangTxt_Spower_RelErr;  //=_T("视在功率相对误差值(%)");
	extern CString g_sLangID_Spower_AbsErr;  //=_T("sSpower_AbsErr");
	extern CString g_sLangTxt_Spower_AbsErr;  //=_T("视在功率绝对误差值(VA)");
	extern CString g_sLangID_Spower_ErrRel;  //=_T("sSpower_ErrRel");
	extern CString g_sLangTxt_Spower_ErrRel;  //=_T("视在功率相对误差限(%)");
	extern CString g_sLangID_Spower_ErrAbs;  //=_T("sSpower_ErrAbs");
	extern CString g_sLangTxt_Spower_ErrAbs;  //=_T("视在功率绝对误差限(VA)");
	extern CString g_sLangID_PpowerSet;  //=_T("sPpowerSet");
	extern CString g_sLangTxt_PpowerSet;  //=_T("有功功率整定动作值(W)");
	extern CString g_sLangID_Ppower_RelErr;  //=_T("sPpower_RelErr");
	extern CString g_sLangTxt_Ppower_RelErr;  //=_T("有功功率相对误差值(%)");
	extern CString g_sLangID_Ppower_AbsErr;  //=_T("sPpower_AbsErr");
	extern CString g_sLangTxt_Ppower_AbsErr;  //=_T("有功功率绝对误差值(W)");
	extern CString g_sLangID_Ppower_ErrRel;  //=_T("sPpower_ErrRel");
	extern CString g_sLangTxt_Ppower_ErrRel;  //=_T("有功功率相对误差限(%)");
	extern CString g_sLangID_Ppower_ErrAbs;  //=_T("sPpower_ErrAbs");
	extern CString g_sLangTxt_Ppower_ErrAbs;  //=_T("有功功率绝对误差限(W)");
	extern CString g_sLangID_QpowerSet;  //=_T("sQpowerSet");
	extern CString g_sLangTxt_QpowerSet;  //=_T("无功功率整定动作值(Var)");
	extern CString g_sLangID_Qpower_RelErr;  //=_T("sQpower_RelErr");
	extern CString g_sLangTxt_Qpower_RelErr;  //=_T("无功功率相对误差值(%)");
	extern CString g_sLangID_Qpower_AbsErr;  //=_T("sQpower_AbsErr");
	extern CString g_sLangTxt_Qpower_AbsErr;  //=_T("无功功率绝对误差值(Var)");
	extern CString g_sLangID_Qpower_ErrRel;  //=_T("sQpower_ErrRel");
	extern CString g_sLangTxt_Qpower_ErrRel;  //=_T("无功功率相对误差限(%)");
	extern CString g_sLangID_Qpower_ErrAbs;  //=_T("sQpower_ErrAbs");
	extern CString g_sLangTxt_Qpower_ErrAbs;  //=_T("无功功率绝对误差限(Var)");
	extern CString g_sLangID_Spower_AbsErr_Max;  //=_T("sSpower_AbsErr_Max");
	extern CString g_sLangTxt_Spower_AbsErr_Max;  //=_T("视在功率绝对误差最大值(VA)");
	extern CString g_sLangID_Spower_RelErr_Max;  //=_T("sSpower_RelErr_Max");
	extern CString g_sLangTxt_Spower_RelErr_Max;  //=_T("视在功率相对误差最大值(%)");
	extern CString g_sLangID_Spower_AbsErr_Min;  //=_T("sSpower_AbsErr_Min");
	extern CString g_sLangTxt_Spower_AbsErr_Min;  //=_T("视在功率绝对误差最小值(VA)");
	extern CString g_sLangID_Spower_RelErr_Min;  //=_T("sSpower_RelErr_Min");
	extern CString g_sLangTxt_Spower_RelErr_Min;  //=_T("视在功率相对误差最小值(%)");
	extern CString g_sLangID_Ppower_AbsErr_Max;  //=_T("sPpower_AbsErr_Max");
	extern CString g_sLangTxt_Ppower_AbsErr_Max;  //=_T("有功功率绝对误差最大值(W)");
	extern CString g_sLangID_Ppower_RelErr_Max;  //=_T("sPpower_RelErr_Max");
	extern CString g_sLangTxt_Ppower_RelErr_Max;  //=_T("有功功率相对误差最大值(%)");
	extern CString g_sLangID_Ppower_AbsErr_Min;  //=_T("sPpower_AbsErr_Min");
	extern CString g_sLangTxt_Ppower_AbsErr_Min;  //=_T("有功功率绝对误差最小值(W)");
	extern CString g_sLangID_Ppower_RelErr_Min;  //=_T("sPpower_RelErr_Min");
	extern CString g_sLangTxt_Ppower_RelErr_Min;  //=_T("有功功率相对误差最小值(%)");
	extern CString g_sLangID_Qpower_AbsErr_Max;  //=_T("sQpower_AbsErr_Max");
	extern CString g_sLangTxt_Qpower_AbsErr_Max;  //=_T("无功功率绝对误差最大值(Var)");
	extern CString g_sLangID_Qpower_RelErr_Max;  //=_T("sQpower_RelErr_Max");
	extern CString g_sLangTxt_Qpower_RelErr_Max;  //=_T("无功功率相对误差最大值(%)");
	extern CString g_sLangID_Qpower_AbsErr_Min;  //=_T("sQpower_AbsErr_Min");
	extern CString g_sLangTxt_Qpower_AbsErr_Min;  //=_T("无功功率绝对误差最小值(Var)");
	extern CString g_sLangID_Qpower_RelErr_Min;  //=_T("sQpower_RelErr_Min");
	extern CString g_sLangTxt_Qpower_RelErr_Min;  //=_T("无功功率相对误差最小值(%)");
	extern CString g_sLangID_ImpAngleSet;  //=_T("sImpAngleSet");
	extern CString g_sLangTxt_ImpAngleSet;  //=_T("阻抗角整定动作值(°)");
	extern CString g_sLangID_ImpAngle_RelErr;  //=_T("sImpAngle_RelErr");
	extern CString g_sLangTxt_ImpAngle_RelErr;  //=_T("阻抗角动作值相对误差值(%)");
	extern CString g_sLangID_ImpAngle_AbsErr;  //=_T("sImpAngle_AbsErr");
	extern CString g_sLangTxt_ImpAngle_AbsErr;  //=_T("阻抗角动作值绝对误差值(°)");
	extern CString g_sLangID_ImpAngle_ErrRel;  //=_T("sImpAngle_ErrRel");
	extern CString g_sLangTxt_ImpAngle_ErrRel;  //=_T("阻抗角动作值相对误差限(%)");
	extern CString g_sLangID_ImpAngle_ErrAbs;  //=_T("sImpAngle_ErrAbs");
	extern CString g_sLangTxt_ImpAngle_ErrAbs;  //=_T("阻抗角动作值绝对误差限(°)");
	extern CString g_sLangID_ShortZImp;  //=_T("sShortZImp");
	extern CString g_sLangTxt_ShortZImp;  //=_T("短路阻抗整定动作值(Ω)");
	extern CString g_sLangID_ShortZImp_RelErr;  //=_T("sShortZImp_RelErr");
	extern CString g_sLangTxt_ShortZImp_RelErr;  //=_T("短路阻抗动作值相对误差值(%)");
	extern CString g_sLangID_ShortZImp_AbsErr;  //=_T("sShortZImp_AbsErr");
	extern CString g_sLangTxt_ShortZImp_AbsErr;  //=_T("短路阻抗动作值绝对误差值(Ω)");
	extern CString g_sLangID_ShortZImp_ErrRel;  //=_T("sShortZImp_ErrRel");
	extern CString g_sLangTxt_ShortZImp_ErrRel;  //=_T("短路阻抗动作值相对误差限(%)");
	extern CString g_sLangID_ShortZImp_ErrAbs;  //=_T("sShortZImp_ErrAbs");
	extern CString g_sLangTxt_ShortZImp_ErrAbs;  //=_T("短路阻抗动作值绝对误差限(Ω)");
	extern CString g_sLangID_ImpAngle_AbsErr_Max;  //=_T("sImpAngle_AbsErr_Max");
	extern CString g_sLangTxt_ImpAngle_AbsErr_Max;  //=_T("阻抗角动作值绝对误差最大值(°)");
	extern CString g_sLangID_ImpAngle_RelErr_Max;  //=_T("sImpAngle_RelErr_Max");
	extern CString g_sLangTxt_ImpAngle_RelErr_Max;  //=_T("阻抗角动作值相对误差最大值(%)");
	extern CString g_sLangID_ImpAngle_AbsErr_Min;  //=_T("sImpAngle_AbsErr_Min");
	extern CString g_sLangTxt_ImpAngle_AbsErr_Min;  //=_T("阻抗角动作值绝对误差最小值(°)");
	extern CString g_sLangID_ImpAngle_RelErr_Min;  //=_T("sImpAngle_RelErr_Min");
	extern CString g_sLangTxt_ImpAngle_RelErr_Min;  //=_T("阻抗角动作值相对误差最小值(%)");
	extern CString g_sLangID_ShortZImp_AbsErr_Max;  //=_T("sShortZImp_AbsErr_Max");
	extern CString g_sLangTxt_ShortZImp_AbsErr_Max;  //=_T("短路阻抗动作值绝对误差最大值(A)");
	extern CString g_sLangID_ShortZImp_RelErr_Max;  //=_T("sShortZImp_RelErr_Max");
	extern CString g_sLangTxt_ShortZImp_RelErr_Max;  //=_T("短路阻抗动作值相对误差最大值(%)");
	extern CString g_sLangID_ShortZImp_AbsErr_Min;  //=_T("sShortZImp_AbsErr_Min");
	extern CString g_sLangTxt_ShortZImp_AbsErr_Min;  //=_T("短路阻抗动作值绝对误差最小值(A)");
	extern CString g_sLangID_ShortZImp_RelErr_Min;  //=_T("sShortZImp_RelErr_Min");
	extern CString g_sLangTxt_ShortZImp_RelErr_Min;  //=_T("短路阻抗动作值相对误差最小值(%)");
	extern CString g_sLangID_Hz_RelErr_Max;  //=_T("sHz_RelErr_Max");
	extern CString g_sLangTxt_Hz_RelErr_Max;  //=_T("频率动作值相对误差最大值(%)");
	extern CString g_sLangID_Hz_RelErr_Min;  //=_T("sHz_RelErr_Min");
	extern CString g_sLangTxt_Hz_RelErr_Min;  //=_T("频率动作值相对误差最小值(%)")");
	extern CString g_sLangID_T_ErrAbsPos;  //=_T("sT_ErrAbsPos");
	extern CString g_sLangTxt_T_ErrAbsPos;  //=_T("动作时间正绝对误差限(s)");
	extern CString g_sLangID_T_ErrAbsNeg;  //=_T("sT_ErrAbsNeg");
	extern CString g_sLangTxt_T_ErrAbsNeg;  //=_T("动作时间负绝对误差限(s)");
