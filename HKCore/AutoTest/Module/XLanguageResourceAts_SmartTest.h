#pragma once

#include "..\..\Module\XLanguage\XLanguageMngr.h"
#include "XLanguageResourceAts.h"

class CXLanguageResourceAts_SmartTest : public CXLanguageResourceAtsBase
{
// 构造
public:
	CXLanguageResourceAts_SmartTest();
	virtual ~CXLanguageResourceAts_SmartTest();
	
private:
	CXLanguage m_oXLangRsAutoTest;
	static const CString  g_strXLangRsAutoTestFile;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();

public:
	static CString g_sLangID_Login; 
	static CString g_sLangTxt_Login;
	static CString g_sLangID_AutoTestVTip;//智能自动测试系统V1.0
	static CString g_sLangTxt_AutoTestVTip;
// 	static CString g_sLangID_FileOpen; 
// 	static CString g_sLangTxt_FileOpen;
	static CString g_sLangID_FileOpenTip; 
	static CString g_sLangTxt_FileOpenTip;
	static CString g_sLangID_Quit; 
	static CString g_sLangTxt_Quit;
	static CString g_sLangID_QuitTip; 
	static CString g_sLangTxt_QuitTip;
	static CString g_sLangID_RibbonRecentDocs; 
	static CString g_sLangTxt_RibbonRecentDocs;
	static CString g_sLangID_Config; 
	static CString g_sLangTxt_Config;
	static CString g_sLangID_AutoTestOper; 
	static CString g_sLangTxt_AutoTestOper;
// 	static CString g_sLangID_UpLoad; 
// 	static CString g_sLangTxt_UpLoad;
// 	static CString g_sLangID_DownLoad; 
// 	static CString g_sLangTxt_DownLoad;
	static CString g_sLangID_NewTest; 
	static CString g_sLangTxt_NewTest;
	static CString g_sLangID_MultiDevTest; 
	static CString g_sLangTxt_MultiDevTest;
	static CString g_sLangID_SinDevMulPro; 
	static CString g_sLangTxt_SinDevMulPro;
	static CString g_sLangID_SubTempTest; 
	static CString g_sLangTxt_SubTempTest;
	static CString g_sLangID_SingleDevTest;
	static CString g_sLangTxt_SingleDevTest;
	static CString g_sLangID_Test;
	static CString g_sLangTxt_Test; 
    static CString g_sLangID_StartTest; 
	static CString g_sLangTxt_StartTest;
	static CString g_sLangID_StartReport;
	static CString g_sLangTxt_StartReport;	
	static CString g_sLangID_Stop; 
	static CString g_sLangTxt_Stop;
	static CString g_sLangID_Report; 
	static CString g_sLangTxt_Report;
	static CString g_sLangID_ShowScale; 
	static CString g_sLangTxt_ShowScale;
	static CString g_sLangID_AdReport; 
	static CString g_sLangTxt_AdReport;
	static CString g_sLangID_PrintReport; 
	static CString g_sLangTxt_PrintReport;
	static CString g_sLangID_Settings; 
	static CString g_sLangTxt_Settings;	
	static CString g_sLangID_ReConfig; 
	static CString g_sLangTxt_ReConfig;
// 	static CString g_sLangID_View; 
// 	static CString g_sLangTxt_View;	
// 	static CString g_sLangID_StatusBarTip; 
// 	static CString g_sLangTxt_StatusBarTip;
	static CString g_sLangID_OutpWind; 
	static CString g_sLangTxt_OutpWind;
	static CString g_sLangID_FileManBar; 
	static CString g_sLangTxt_FileManBar;
	static CString g_sLangID_TestInfBar; 
	static CString g_sLangTxt_TestInfBar;//测试任务栏
	static CString g_sLangID_CharCurTest; 
	static CString g_sLangTxt_CharCurTest;//特性曲线测试
	static CString g_sLangID_TestTaskBar;
	static CString g_sLangTxt_TestTaskBar;
	static CString g_sLangID_ShowTestInf; 
	static CString g_sLangTxt_ShowTestInf;
// 	static CString g_sLangID_AboutTip; 
	static CString g_sLangTxt_AboutTip;
	static CString g_sLangID_ToAndCom; 
	static CString g_sLangTxt_ToAndCom;
	static CString g_sLangID_SysTools; 
	static CString g_sLangTxt_SysTools;
	static CString g_sLangID_SysCom; 
	static CString g_sLangTxt_SysCom;
	static CString g_sLangID_TestFileMan; 
	static CString g_sLangTxt_TestFileMan;
	static CString g_sLangID_TestItemField; 
	static CString g_sLangTxt_TestItemField;
	static CString g_sLangID_NewTestWork; //新建测试任务
	static CString g_sLangTxt_NewTestWork;
	static CString g_sLangID_TestInf; 
	static CString g_sLangTxt_TestInf;
	static CString g_sLangID_TaskName; 
	static CString g_sLangTxt_TaskName;
	static CString g_sLangID_TestType; 
	static CString g_sLangTxt_TestType;
	static CString g_sLangID_ProSet; 
	static CString g_sLangTxt_ProSet;
	static CString g_sLangID_ChoProTem; //选择规约模板
	static CString g_sLangTxt_ChoProTem;
	static CString g_sLangID_PoFile; 
	static CString g_sLangTxt_PoFile;
	static CString g_sLangID_ChoTest; 
	static CString g_sLangTxt_ChoTest;
	static CString g_sLangID_SelPoFile; //选择点表文件
	static CString g_sLangTxt_SelPoFile;
	static CString g_sLangID_TitleTask; 
	static CString g_sLangTxt_TitleTask;
	static CString g_sLangID_NewBuilt; //新建
	static CString g_sLangTxt_NewBuilt;
	static CString g_sLangID_ReportAdjSh;//报告调整提示 
	static CString g_sLangTxt_ReportAdjSh;
	static CString g_sLangID_TestChoPro;//测试仪选择（测试仪器选择改变，需重新启动自动测试程序才能是改变生效） 
	static CString g_sLangTxt_TestChoPro;
	static CString g_sLangID_AutoTestSysSet;//自动测试系统配置 
	static CString g_sLangTxt_AutoTestSysSet;
	static CString g_sLangID_AlarmAutoMain;//警告—自动测试主程序 
	static CString g_sLangTxt_AlarmAutoMain;
	static CString g_sLangID_TestFileName; //测试文件名
	static CString g_sLangTxt_TestFileName;
	static CString g_sLangID_TesTyp; //测试类型
	static CString g_sLangTxt_TesTyp;
	static CString g_sLangID_ProTypeCho; //规约种类选择
	static CString g_sLangTxt_ProTypeCho;
	static CString g_sLangID_TestTempFile; //测试模板文件
	static CString g_sLangTxt_TestTempFile;
	static CString g_sLangID_ProTempFile; //规约模板文件
	static CString g_sLangTxt_ProTempFile;
	static CString g_sLangID_ProHighSet; //规约高级设置
	static CString g_sLangTxt_ProHighSet;
	static CString g_sLangID_ProTabFile; //规约点表文件
	static CString g_sLangTxt_ProTabFile;
	static CString g_sLangID_RptData; //报告数据
	static CString g_sLangTxt_RptData;
	static CString g_sLangID_RptData2; //报告数据2
	static CString g_sLangTxt_RptData2;
	static CString g_sLangID_TestTemp; //测试模板
	static CString g_sLangTxt_TestTemp;
	static CString g_sLangID_AppTestNo; //出现测试不合格项目处理
	static CString g_sLangTxt_AppTestNo;
	static CString g_sLangID_CTestCNum; //重复测试项目重复次数
	static CString g_sLangTxt_CTestCNum;
	static CString g_sLangID_CoeMus; //提示音乐
	static CString g_sLangTxt_CoeMus;
	static CString g_sLangID_AlarmMode; //告警方式
	static CString g_sLangTxt_AlarmMode;
	static CString g_sLangID_ContTest; //继续测试
	static CString g_sLangTxt_ContTest;
	static CString g_sLangID_LongAlarm; //长警告
	static CString g_sLangTxt_LongAlarm;
	static CString g_sLangID_ShortAlarm; //短警告
	static CString g_sLangTxt_ShortAlarm;
	static CString g_sLangID_CusRepeat; //自定义最大重复次数
	static CString g_sLangTxt_CusRepeat;
	static CString g_sLangID_ComFaReNu; //通讯失败后重试次数
	static CString g_sLangTxt_ComFaReNu;
	static CString g_sLangID_RetComS; //重试通讯前延时
	static CString g_sLangTxt_RetComS;
	static CString g_sLangID_TestCoDe; //测试项目测试完成出来
	static CString g_sLangTxt_TestCoDe;
	static CString g_sLangID_CoNuShow; //完成一级项目时进行提示
	static CString g_sLangTxt_CoNuShow;
	static CString g_sLangID_TestCoRe; //测试完成，报告自动导出路径（测试模板须调用……）
	static CString g_sLangTxt_TestCoRe;
// 	static CString g_sLangID_AdjustReport; //调整报告完成如下操作
// 	static CString g_sLangTxt_AdjustReport;
	static CString g_sLangID_DeNoChTe; //1.删除没有选择测试的项目分类报告部分
	static CString g_sLangTxt_DeNoChTe;
	static CString g_sLangID_RepUse; //2.对于没有测试的测试点，空白部分报告使用“——”替换
	static CString g_sLangTxt_RepUse;
	static CString g_sLangID_AdjustSure; //调整部分不可以回复，确定要调整吗？
	static CString g_sLangTxt_AdjustSure;
	static CString g_sLangID_StartX; //起点X
	static CString g_sLangTxt_StartX;	
	static CString g_sLangID_StartY; //起点Y
	static CString g_sLangTxt_StartY;	
	static CString g_sLangID_NowX; //当前X
	static CString g_sLangTxt_NowX;
	static CString g_sLangID_NowY; //当前Y
	static CString g_sLangTxt_NowY;
	static CString g_sLangID_EndPointX; //终点X
	static CString g_sLangTxt_EndPointX;
	static CString g_sLangID_EndPointY; //终点Y
	static CString g_sLangTxt_EndPointY;
	static CString g_sLangID_TestConR; //与测试仪控制接口程序握手，30s内握手失败，则终止进程，重新启动测试仪接口程序
	static CString g_sLangTxt_TestConR;
	static CString g_sLangID_WarningProTest; //程序检测到系统中有和系统相关的进程正在运行，点击“终止进程”关闭所有进程
	static CString g_sLangTxt_WarningProTest;
	static CString g_sLangID_StopProcess; //终止进程
	static CString g_sLangTxt_StopProcess;
	static CString g_sLangID_NeedCloPro; //需要关闭的进程
	static CString g_sLangTxt_NeedCloPro;
	static CString g_sLangID_SouRepPath;      //源报告路径
	static CString g_sLangTxt_SouRepPath;
	static CString g_sLangID_ExportSet;       //导出设置
	static CString g_sLangTxt_ExportSet;
	static CString g_sLangID_ExportPath;      //导出路径
	static CString g_sLangTxt_ExportPath;
	static CString g_sLangID_ExFileName;      //导出文件名称
	static CString g_sLangTxt_ExFileName;
	static CString g_sLangID_ChoFileModel;    //选择文件模型
	static CString g_sLangTxt_ChoFileModel;
	static CString g_sLangID_RepViewRat;    //报告显示比例
	static CString g_sLangTxt_RepViewRat;
	static CString g_sLangID_RepViRaCho;    //报告显示比例选择
	static CString g_sLangTxt_RepViRaCho;
	static CString g_sLangID_TestRepViRaSet;    //试验报告显示比例设置
	static CString g_sLangTxt_TestRepViRaSet;
	static CString g_sLangID_NoChProTem;//没有选择规约模板
	static CString g_sLangTxt_NoChProTem;
	static CString g_sLangID_NoChTestTem;//没有选择测试模板
	static CString g_sLangTxt_NoChTestTem;
	static CString g_sLangID_ChTemplet;//选择模板
	static CString g_sLangTxt_ChTemplet;
	static CString g_sLangID_ChProtocol;//选择规约
	static CString g_sLangTxt_ChProtocol;
	static CString g_sLangID_SettingsChoose;//设置组选择
	static CString g_sLangTxt_SettingsChoose;
	static CString g_sLangID_SetMulDev;//设置多装置
	static CString g_sLangTxt_SetMulDev;
	static CString g_sLangID_NoChTemFile;//没有选择模板文件
	static CString g_sLangTxt_NoChTemFile;
	static CString g_sLangID_RepFileNameNu;//报告文件名为空
	static CString g_sLangTxt_RepFileNameNu;
	static CString g_sLangID_NoChTestType;//没有选择测试类型
	static CString g_sLangTxt_NoChTestType;
	static CString g_sLangID_CommSetInf;//通讯设置信息不全
	static CString g_sLangTxt_CommSetInf;
	static CString g_sLangID_TabFileNoSel;//点表文件没有选择
	static CString g_sLangTxt_TabFileNoSel;
	static CString g_sLangID_AlreadyExists;//%s 已经存在
	static CString g_sLangTxt_AlreadyExists;
	static CString g_sLangID_UnquaItem;//不合格项目
	static CString g_sLangTxt_UnquaItem;
	static CString g_sLangID_ModelFile;//模型文件
	static CString g_sLangTxt_ModelFile;
	static CString g_sLangID_NoAddDevTestRep;//没有添加装置测试报告
	static CString g_sLangTxt_NoAddDevTestRep;
	static CString g_sLangID_OlAddOnRep;//只添加了一个装置测试报告
	static CString g_sLangTxt_OlAddOnRep;
	static CString g_sLangID_ProtocoTemplate;//规约模板
	static CString g_sLangTxt_ProtocoTemplate;
	static CString g_sLangID_ProtocoMatching;//规约配型
	static CString g_sLangTxt_ProtocoMatching;
	static CString g_sLangID_ChRptRe;//选择报告导出目标目录
	static CString g_sLangTxt_ChRptRe;
	static CString g_sLangID_AlOpen;//已经打开【%s】，请关闭后在创建测试报告！
	static CString g_sLangTxt_AlOpen;
	static CString g_sLangID_TaskTotalTime;//任务总时间
	static CString g_sLangTxt_TaskTotalTime;
	static CString g_sLangID_RptTotalTime;//报告总时间
	static CString g_sLangTxt_RptTotalTime;
	static CString g_sLangID_NoTitle;//无标题
	static CString g_sLangTxt_NoTitle;
	static CString g_sLangID_TestingClose;//正在测试中，不能关闭...
	static CString g_sLangTxt_TestingClose;
	static CString g_sLangID_FileUnExistS;//文件\"%s\"不存在
	static CString g_sLangTxt_FileUnExistS;
	static CString g_sLangID_SelOrCretFile;//文件夹【%s】包含有测试报告文件\n请选择或者创建一个空的文件夹
	static CString g_sLangTxt_SelOrCretFile;
	static CString g_sLangID_SelFilePath;//请选择报告文件存储的路径！
	static CString g_sLangTxt_SelFilePath;
	static CString g_sLangID_DelTaskYOrN;//是否要删除任务 %s 及其子项
	static CString g_sLangTxt_DelTaskYOrN;
	static CString g_sLangID_SureDelAgain;//请再次确定删除
	static CString g_sLangTxt_SureDelAgain;
	static CString g_sLangID_DelFailItem;//删除的任务中包含已经被打开的工程，删除失败
	static CString g_sLangTxt_DelFailItem;
	static CString g_sLangID_DelItemYOrN;//是否要删除工程 %s
	static CString g_sLangTxt_DelItemYOrN;
	static CString g_sLangID_DelFailure;//该工程已经被打开，删除失败
	static CString g_sLangTxt_DelFailure;
	static CString g_sLangID_StartRptYOrN;//“开始报告”功能只测试当前打开的测试报告，\r\n你确实只要测试测试任务中的单个测试报告吗？\r\n\r\n选择“是”测试单个报告\r\n选择“否”开始任务测试\r\n选择“取消”终止操作")
	static CString g_sLangTxt_StartRptYOrN;
	static CString g_sLangID_NewTestClear;//新建测试，清除当前报告数据吗？\r\n
	static CString g_sLangTxt_NewTestClear;
	static CString g_sLangID_SelYes;//选择“是”清除当前报告数据，新建测试\r\n
	static CString g_sLangTxt_SelYes;
	static CString g_sLangID_SelNo;//选择“否”，不清除当前报告数据，新建测试\r\n
	static CString g_sLangTxt_SelNo;
	static CString g_sLangID_SelCancel;//选择“取消”，不开始测试
	static CString g_sLangTxt_SelCancel;
	static CString g_sLangID_WavCpntNotExist;//录波组件不存在
	static CString g_sLangTxt_WavCpntNotExist;
	static CString g_sLangID_UnAutoTest;//没有启动自动测试，无法执行命令
	static CString g_sLangTxt_UnAutoTest;
	static CString g_sLangID_ToolUnExitS;//工具【%s】【%s】不存在
	static CString g_sLangTxt_ToolUnExitS;
	static CString g_sLangID_TestTaskFnshS;//测试任务【%s】测试完成
	static CString g_sLangTxt_TestTaskFnshS;
	static CString g_sLangID_StartTestS;//开始测试【%s】
	static CString g_sLangTxt_StartTestS;
	static CString g_sLangID_TestTempS;//测试模板*******%s
	static CString g_sLangTxt_TestTempS;
	static CString g_sLangID_ReportFileS;//报告文件*******%s
	static CString g_sLangTxt_ReportFileS;
	static CString g_sLangID_ModelFileS;//模型文件********%s
	static CString g_sLangTxt_ModelFileS;
	static CString g_sLangID_PrtcTemS;//规约模板********%s
	static CString g_sLangTxt_PrtcTemS;
	static CString g_sLangID_AutoTestContrl;//自动测试控制中心
	static CString g_sLangTxt_AutoTestContrl;
	static CString g_sLangID_SGroupS;//%s%s-组%d.%s
	static CString g_sLangTxt_SGroupS;
	static CString g_sLangID_RightBuy;//Demo版本，只能使用模板【Demo-PSL-641U】，请购买正式版本！
	static CString g_sLangTxt_RightBuy;
	static CString g_sLangID_MainView2;//主视图:
	static CString g_sLangTxt_MainView2;
	static CString g_sLangID_GroupReport;//组%d报告
	static CString g_sLangTxt_GroupReport;
	static CString g_sLangID_ProcessStop;//和测试相关的进程已经被终止
	static CString g_sLangTxt_ProcessStop;
	static CString g_sLangID_SelObjPath;//选择目标路径
	static CString g_sLangTxt_SelObjPath;
	static CString g_sLangID_FileNameIncl;//文件名称包含非法字符: %s
	static CString g_sLangTxt_FileNameIncl;
	static CString g_sLangID_ReportEptFinsh;//报告导出完成
	static CString g_sLangTxt_ReportEptFinsh;
	static CString g_sLangID_ObjFileExistOvwt;//目标文件已经存在,覆盖吗?
	static CString g_sLangTxt_ObjFileExistOvwt;
	static CString g_sLangID_ReportTestTempt;//报告【%s】对应的测试模板:【%s】
	static CString g_sLangTxt_ReportTestTempt;
	static CString g_sLangID_SureToDele;//你确实要删除【%s】吗？
	static CString g_sLangTxt_SureToDele;
	static CString g_sLangID_UnQualifadS;//[%s]不合格
	static CString g_sLangTxt_UnQualifadS;
	static CString g_sLangID_TestOver;//********测试结束********
	static CString g_sLangTxt_TestOver;
	static CString g_sLangID_CopyOutput;//复制输出
	static CString g_sLangTxt_CopyOutput;
	static CString g_sLangID_ClearOutput;//清除输出
	static CString g_sLangTxt_ClearOutput;
// 	static CString g_sLangID_Unqualified2;//%s[不合格]
// 	static CString g_sLangTxt_Unqualified2;
	static CString g_sLangID_NoAddTestRpt;//没有添加测试报告
	static CString g_sLangTxt_NoAddTestRpt;
	static CString g_sLangID_OneTestRpt;//只添加了一个测试报告
	static CString g_sLangTxt_OneTestRpt;
	static CString g_sLangID_NoSelPrtcTem;//装置报告列表第【%d】没有选择规约模板
	static CString g_sLangTxt_NoSelPrtcTem;
	static CString g_sLangID_NoSelFile;//装置报告列表第【%d】没有选择点表文件
	static CString g_sLangTxt_NoSelFile;
	static CString g_sLangID_NameSame;//装置报告列表第【%d】与第【%d】名称【%s】相同
	static CString g_sLangTxt_NameSame;
	static CString g_sLangID_PrtcSame;//装置报告列表第【%d】与第【%d】规约模板【%s】相同
	static CString g_sLangTxt_PrtcSame;
	static CString g_sLangID_IPSame;//装置报告列表第【%d】与第【%d】IP【%s】相同
	static CString g_sLangTxt_IPSame;
	static CString g_sLangID_ToolTip_32781;//打开报告
	static CString g_sLangTxt_ToolTip_32781;
	static CString g_sLangID_ToolTip_32776;//添加报告
	static CString g_sLangTxt_ToolTip_32776;
	static CString g_sLangID_ToolTip_32777;//删除报告
	static CString g_sLangTxt_ToolTip_32777;
	static CString g_sLangID_ToolTip_32783;//恢复到未完成的状态
	static CString g_sLangTxt_ToolTip_32783;
	static CString g_sLangID_ToolTip_32778;//上移报告
    static CString g_sLangTxt_ToolTip_32778;
	static CString g_sLangID_ToolTip_32779;//下移报告
	static CString g_sLangTxt_ToolTip_32779;
	static CString g_sLangID_ToolTip_32784;//显示报告对应的模板
	static CString g_sLangTxt_ToolTip_32784;
	static CString g_sLangID_ToolTip_32775;//导出任务报告
	static CString g_sLangTxt_ToolTip_32775;
	static CString g_sLangID_ToolTip_32782;//关闭任务
	static CString g_sLangTxt_ToolTip_32782;

	static CString g_sLangID_Menu_57634;
	static CString g_sLangTxt_Menu_57634;
	static CString g_sLangID_Menu_57632;
	static CString g_sLangTxt_Menu_57632;

	static CString g_sLangID_ToolTip_32789;
	static CString g_sLangTxt_ToolTip_32789;
	static CString g_sLangID_StitchRptFinish;
	static CString g_sLangTxt_StitchRptFinish;

	//2016-12-10
	static CString g_sLangID_ToolTip_2000;
	static CString g_sLangTxt_ToolTip_2000;
	static CString g_sLangID_ToolTip_32786;
	static CString g_sLangTxt_ToolTip_32786;
	static CString g_sLangID_ToolTip_32788;
	static CString g_sLangTxt_ToolTip_32788;
	static CString g_sLangID_ToolTip_2001;
	static CString g_sLangTxt_ToolTip_2001;
	static CString g_sLangID_ToolTip_32785;
	static CString g_sLangTxt_ToolTip_32785;
	static CString g_sLangID_ToolTip_351;
	static CString g_sLangTxt_ToolTip_351;
	static CString g_sLangID_ToolTip_314;
	static CString g_sLangTxt_ToolTip_314;
	static CString g_sLangID_ToolTip_320;
	static CString g_sLangTxt_ToolTip_320;
	static CString g_sLangID_ToolTip_330;
	static CString g_sLangTxt_ToolTip_330;
	static CString g_sLangID_ToolTip_358;
	static CString g_sLangTxt_ToolTip_358;
	static CString g_sLangID_ToolTip_347;
	static CString g_sLangTxt_ToolTip_347;
	static CString g_sLangID_ToolTip_310;
	static CString g_sLangTxt_ToolTip_310;
	static CString g_sLangID_ToolTip_348;
	static CString g_sLangTxt_ToolTip_348;
	static CString g_sLangID_ToolTip_349;
	static CString g_sLangTxt_ToolTip_349;
	static CString g_sLangID_ToolTip_350;
	static CString g_sLangTxt_ToolTip_350;
	static CString g_sLangID_ToolTip_357;
	static CString g_sLangTxt_ToolTip_357;
};

