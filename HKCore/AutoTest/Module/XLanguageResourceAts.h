//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"


class CXLanguageResourceAtsBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourceAtsBase();
	virtual ~CXLanguageResourceAtsBase();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsAtsBase;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsAtsBaseFile;
	extern CString g_sLangID_OpenTemplate;
	extern CString g_sLangTxt_OpenTemplate;
	extern CString g_sLangID_OpenPowerTestTemplate;
	extern CString g_sLangTxt_OpenPowerTestTemplate;
	extern CString g_sLangID_OpenSubTemplate;
	extern CString g_sLangTxt_OpenSubTemplate;
	extern CString g_sLangID_OutputWnd;
	extern CString g_sLangTxt_OutputWnd;

	extern CString g_sLangID_LastOne;
	extern CString g_sLangTxt_LastOne;
// 	extern CString g_sLangID_TraProtocol;
// 	extern CString g_sLangTxt_TraProtocol;
// 	extern CString g_sLangID_61850Protocol;
// 	extern CString g_sLangTxt_61850Protocol;
	extern CString g_sLangID_Edit;
	extern CString g_sLangTxt_Edit;
// 	extern CString g_sLangID_Browse;
// 	extern CString g_sLangTxt_Browse;

	extern CString g_sLangID_SelNone;    //全不选
	extern CString g_sLangTxt_SelNone;
	extern CString g_sLangID_ErrorMax;
	extern CString g_sLangTxt_ErrorMax;
	extern CString g_sLangID_Standdeviation;          //标准差
	extern CString g_sLangTxt_Standdeviation;
	extern CString g_sLangID_ExterScript;//外部脚本库文件
	extern CString g_sLangTxt_ExterScript;
	extern CString g_sLangID_InterScript;//模板内部脚本库
	extern CString g_sLangTxt_InterScript;

	extern CString g_sLangID_Attribute;   //属性
	extern CString g_sLangTxt_Atrribute;
	extern CString g_sLangID_Times;      //次数
	extern CString g_sLangTxt_Times;
	extern CString g_sLangID_DataPro;//数据处理
	extern CString g_sLangTxt_DataPro;

	extern CString g_sLangID_TestTemplateFile;
	extern CString g_sLangTxt_TestTemplateFile;
	extern CString g_sLangID_TestSubTemplateFile;
	extern CString g_sLangTxt_TestSubTemplateFile;
	extern CString g_sLangID_ReportTemplateFile;
	extern CString g_sLangTxt_ReportTemplateFile;
	//
	extern CString g_sLangID_ReportDefinition;
	extern CString g_sLangTxt_ReportDefinition;
	extern CString g_sLangID_TagManagement;
	extern CString g_sLangTxt_TagManagement;
	extern CString g_sLangID_TestTask; 
	extern CString g_sLangTxt_TestTask;

	extern CString g_sLangID_LetterForm;//宋体
	extern CString g_sLangTxt_LetterForm;
	extern CString g_sLangID_ViewDevPara;//查看设备参数
	extern CString g_sLangTxt_ViewDevPara;
	extern CString g_sLangID_TestInlegibleItems;//测试全部不合格项目
	extern CString g_sLangTxt_TestInlegibleItems;
	extern CString g_sLangID_TestCurrtItem;//测试当前项目
	extern CString g_sLangTxt_TestCurrtItem;
	extern CString g_sLangID_TestCurrtItemDev;//测试当前项目-装置独立测试
	extern CString g_sLangTxt_TestCurrtItemDev;
	extern CString g_sLangID_TestCurrtItemStart;//从当前项目开始测试
	extern CString g_sLangTxt_TestCurrtItemStart;
	extern CString g_sLangID_ParaMdf;//参数修改
	extern CString g_sLangTxt_ParaMdf;
	extern CString g_sLangID_UpdataPara;//更新参数
	extern CString g_sLangTxt_UpdataPara;
	extern CString g_sLangID_UpdataParaToGb;//更新参数
	extern CString g_sLangTxt_UpdataParaToGb;
	extern CString g_sLangID_ViewReport;//查看报告
	extern CString g_sLangTxt_ViewReport;
	extern CString g_sLangID_ViewRecordFile;//查看录波文件
	extern CString g_sLangTxt_ViewRecordFile;
	extern CString g_sLangID_ViewCharCurve;//查看特性曲线
	extern CString g_sLangTxt_ViewCharCurve;
	extern CString g_sLangID_ExpdNodes;//展开全部子节点
	extern CString g_sLangTxt_ExpdNodes;

	extern CString g_sLangID_ComictnComm;//通讯命令
	extern CString g_sLangTxt_ComictnComm;
	extern CString g_sLangID_ComictnFront;//通讯前延时
	extern CString g_sLangTxt_ComictnFront;
	extern CString g_sLangID_ComictnLater;//通讯后延时
	extern CString g_sLangTxt_ComictnLater;
	extern CString g_sLangID_ComputMode;//计算模式
	extern CString g_sLangTxt_ComputMode;
	extern CString g_sLangID_ComictnTime;//通讯次数
	extern CString g_sLangTxt_ComictnTime;
	extern CString g_sLangID_Text;         //文本
	extern CString g_sLangTxt_Text; 

	extern CString g_sLangID_CreatTestMngFail;//创建测试仪管理组件失败
	extern CString g_sLangTxt_CreatTestMngFail;
	extern CString g_sLangID_CreatTestAbnom;//创建测试仪通讯组件出现异常
	extern CString g_sLangTxt_CreatTestAbnom;
	extern CString g_sLangID_CreatTestCmtFail;//创建测试仪通讯组件失败
	extern CString g_sLangTxt_CreatTestCmtFail;
	extern CString g_sLangID_NoPrtcCpnt;//没有注册规约引擎组件
	extern CString g_sLangTxt_NoPrtcCpnt;
	extern CString g_sLangID_CreatPrtcFail;//创建规约通讯设备失败
	extern CString g_sLangTxt_CreatPrtcFail;
	extern CString g_sLangID_FileOpenFalseS;//打开文件\"%s\"出错
	extern CString g_sLangTxt_FileOpenFalseS;
	extern CString g_sLangID_TestFileOpenFalseS;//打开试验文件\"%s\"出错
	extern CString g_sLangTxt_TestFileOpenFalseS;
	extern CString g_sLangID_CommunItemD;//通讯命令项目个数：%d    电气量项目个数：%d
	extern CString g_sLangTxt_CommunItemD;
	extern CString g_sLangID_TestStopS;//【%s】测试停止
	extern CString g_sLangTxt_TestStopS;
	extern CString g_sLangID_CommunIgnored;//通讯次忽略的电气量测试功能消息......数
	extern CString g_sLangTxt_CommunIgnored;
	extern CString g_sLangID_OnlineFail;//联机失败
	extern CString g_sLangTxt_OnlineFail;
	extern CString g_sLangID_TestStartInf;//------收到电气量测试开始消息【%s】
	extern CString g_sLangTxt_TestStartInf;
	extern CString g_sLangID_ParaDnldFail;//------参数下载失败
	extern CString g_sLangTxt_ParaDnldFail;
	extern CString g_sLangID_TestUnsuptFctn;//------测试仪器底层功能接口不支持测试功能[%s]
	extern CString g_sLangTxt_TestUnsuptFctn;
	extern CString g_sLangID_TestOverTimeS;//------测试仪器底层测试功能[%s]测试超时, %d ms后重新测试
	extern CString g_sLangTxt_TestOverTimeS;
	extern CString g_sLangID_CommunOverTime;//通讯超时，测试终止！
	extern CString g_sLangTxt_CommunOverTime;
	extern CString g_sLangID_CommunTestStop;//通讯过程中出现错误，测试终止
	extern CString g_sLangTxt_CommunTestStop;
	extern CString g_sLangID_ReCommunD;//通讯过程中出现错误，重新通讯第%d次，共%d次
	extern CString g_sLangTxt_ReCommunD;
	extern CString g_sLangID_CommunFalse;//通讯过程中出现错误，pCommCmd==NULL
	extern CString g_sLangTxt_CommunFalse;

	extern CString g_sLangID_StartCommun;//连接设备成功，开始执行通讯命令
	extern CString g_sLangTxt_StartCommun;
	extern CString g_sLangID_ContNextItem;//继续连接下一个设备
	extern CString g_sLangTxt_ContNextItem;
	extern CString g_sLangID_TestContS;//【%s】：【%s】忽略通讯过程中出现错误，测试继续
	extern CString g_sLangTxt_TestContS;
	extern CString g_sLangID_TestStop3;//通讯引擎异常，测试终止
	extern CString g_sLangTxt_TestStop3;
	extern CString g_sLangID_NoTestItem;//没有需要测试的项目！
	extern CString g_sLangTxt_NoTestItem;
	extern CString g_sLangID_ItemTestTimeD;//------项目[%s]第%d次测试，共%d次
	extern CString g_sLangTxt_ItemTestTimeD;
	extern CString g_sLangID_ItemTestTimeD2;//------项目[%s]第1次测试，共1次
	extern CString g_sLangTxt_ItemTestTimeD2;
	extern CString g_sLangID_Communtioning;//通讯中.......
	extern CString g_sLangTxt_Communtioning;
	extern CString g_sLangID_MdfParaData;//调试子模板方式，请手动修改保护装置的参数数据
	extern CString g_sLangTxt_MdfParaData;
	extern CString g_sLangID_CommunTestTimeD;//----%s通讯命令[%s]第%d次测试，共%d次
	extern CString g_sLangTxt_CommunTestTimeD;
	extern CString g_sLangID_CommunCmdS;//----%s通讯命令[%s]
	extern CString g_sLangTxt_CommunCmdS;
	extern CString g_sLangID_CommunCmdItem;//----------%s通讯命令项目[%s]
	extern CString g_sLangTxt_CommunCmdItem;
	extern CString g_sLangID_CallRecordFail;//调用录波文件失败
	extern CString g_sLangTxt_CallRecordFail;
	extern CString g_sLangID_ReadRecordFileS;//读取录波文件：【%s】
	extern CString g_sLangTxt_ReadRecordFileS;
	extern CString g_sLangID_TestStop4;//    测试项目时序发生错误，测试停止
	extern CString g_sLangTxt_TestStop4;
	extern CString g_sLangID_TestCotrAbnom;//------测试仪控制程序发生异常
	extern CString g_sLangTxt_TestCotrAbnom;
	extern CString g_sLangID_ItemUncmpltS;//------电气量项目\"%s\"还有子项目没有完成
	extern CString g_sLangTxt_ItemUncmpltS;
	extern CString g_sLangID_TestCotrAbnom2;//      测试仪控制程序发生异常
	extern CString g_sLangTxt_TestCotrAbnom2;
	extern CString g_sLangID_EltrcProjectCmplt;//     电气量项目完成
	extern CString g_sLangTxt_EltrcProjectCmplt;
	extern CString g_sLangID_NotCommunCmd;//通讯过程中出现错误，不是通讯命令
	extern CString g_sLangTxt_NotCommunCmd;
	extern CString g_sLangID_CommunFalse2;//通讯过程中出现错误，Item==NULL
	extern CString g_sLangTxt_CommunFalse2;
	extern CString g_sLangID_TestItemFalse;//    >>>>>>>ExcuteCommCmd:测试项目时序发生错误
	extern CString g_sLangTxt_TestItemFalse;
	extern CString g_sLangID_CommunParaFalse;//    通讯命令项目【%s】定义的参数【%s】错误
	extern CString g_sLangTxt_CommunParaFalse;
	extern CString g_sLangID_ItemDataUnexistS;//项目(%s)通讯引擎设备数据模型()%s不存在
	extern CString g_sLangTxt_ItemDataUnexistS;
	extern CString g_sLangID_ItemDataUnexist;//项目(%s)通讯引擎设备数据模型不存在
	extern CString g_sLangTxt_ItemDataUnexist;
	extern CString g_sLangID_ItemDataUnexist2;//项目【%s】通讯引擎设备数据集【%s】不存在
	extern CString g_sLangTxt_ItemDataUnexist2;
	extern CString g_sLangID_ItemDataUnexist3;//项目【%s】设备数据模型【%s】不存在
	extern CString g_sLangTxt_ItemDataUnexist3;
	extern CString g_sLangID_ItemDataUnexist4;//项目【%s】通讯引擎设备数据模型不存在
	extern CString g_sLangTxt_ItemDataUnexist4;
	extern CString g_sLangID_SytmTestFalse;//系统测试错误：ExcuteCommCmdOnDelayBeforeFinish
	extern CString g_sLangTxt_SytmTestFalse;
	extern CString g_sLangID_TestAbnrm2;//测试发生异常，试验过程中通讯命令没有对应的项目
	extern CString g_sLangTxt_TestAbnrm2;
	extern CString g_sLangID_TestAbnrm3;//测试发生异常，试验过程中通讯命令没有对应的项目[TestNextSubItems]
	extern CString g_sLangTxt_TestAbnrm3;
	extern CString g_sLangID_DealCommunRst;//----处理通讯命令【%s】结果
	extern CString g_sLangTxt_DealCommunRst;
	extern CString g_sLangID_CreatRptFail;//创建报告对象失败
	extern CString g_sLangTxt_CreatRptFail;
	extern CString g_sLangID_WaitRtest;//***********标准源告警，等待%d分钟后重新开始测试************
	extern CString g_sLangTxt_WaitRtest;
	extern CString g_sLangID_CommunUnExist;//通讯设备不存在
	extern CString g_sLangTxt_CommunUnExist;
	extern CString g_sLangID_CmdFalse;//通讯配置文件【%s】不正确，命令【%s】错误
	extern CString g_sLangTxt_CmdFalse;
	extern CString g_sLangID_CommunEngineFalse;//    执行通讯过程：通讯引擎错误
	extern CString g_sLangTxt_CommunEngineFalse;
	extern CString g_sLangID_PrtcEngineFalse;//规约引擎设备数据对象错误
	extern CString g_sLangTxt_PrtcEngineFalse;
	extern CString g_sLangID_PathData;//路径：%s：数据个数%d
	extern CString g_sLangTxt_PathData;
	extern CString g_sLangID_PathFalse;//路径错误：%s
	extern CString g_sLangTxt_PathFalse;
	extern CString g_sLangID_FunctionError;//MtRegistPpDataMsg函数调用错误
	extern CString g_sLangTxt_FunctionError;
	extern CString g_sLangID_TestFctnNo;//测试功能组件没有实现GetExternMsgRcvWnd、G方法etExternMsgID
	extern CString g_sLangTxt_TestFctnNo;
	extern CString g_sLangID_UnCreatFctn;//还没有创建测试功能组件！
	extern CString g_sLangTxt_UnCreatFctn;
	extern CString g_sLangID_CallRecordFail2;//调用录波命令失败
	extern CString g_sLangTxt_CallRecordFail2;
	extern CString g_sLangID_CallCmdFail;//调用命令失败
	extern CString g_sLangTxt_CallCmdFail;
	extern CString g_sLangID_ReportExpSucc;//报告导出成功：\r\n
	extern CString g_sLangTxt_ReportExpSucc;
	//GuideBookDefine里的输出信息
	extern CString g_sLangID_Qualified;
	extern CString g_sLangTxt_Qualified;
	extern CString g_sLangID_Unqualified;
	extern CString g_sLangTxt_Unqualified;
	extern CString g_sLangID_ErrorID;
	extern CString g_sLangTxt_ErrorID;

	extern CString g_sLangID_CurrZoneIndex;    //当前定值区
	extern CString g_sLangTxt_CurrZoneIndex;
	extern CString g_sLangID_ZoneIndex;    
	extern CString g_sLangTxt_ZoneIndex;
	//
	extern CString g_sLangID_ModifyAndSave;    
	extern CString g_sLangTxt_ModifyAndSave;
	//CharTemplateSelDlg里的输出信息
	extern CString g_sLangID_SelCharCurve;    
	extern CString g_sLangTxt_SelCharCurve;
    //TestItemViewGrid
	extern CString g_sLangID_ItemType;  //项目类型  
	extern CString g_sLangTxt_ItemType;
	extern CString g_sLangID_Status;   //状态 
	extern CString g_sLangTxt_Status;
	extern CString g_sLangID_ItemPath;   //项目路径 
	extern CString g_sLangTxt_ItemPath;
	extern CString g_sLangID_ReportInf;   //报告信息 
	extern CString g_sLangTxt_ReportInf;
	extern CString g_sLangID_RetestQualified;    //重测合格
	extern CString g_sLangTxt_RetestQualified;
	extern CString g_sLangID_ElectrQuanPrjc;    //电气量项目
	extern CString g_sLangTxt_ElectrQuanPrjc;
	extern CString g_sLangID_ArtificialProject;    //人工项目
	extern CString g_sLangTxt_ArtificialProject;



    //Safety
	extern CString g_sLangID_ErrorDll;//错误的DLL调用 %s::%s(\"%s\", \"%s\")
	extern CString g_sLangTxt_ErrorDll;
	extern CString g_sLangID_DllUnStopTest;//DLL调用(%s::%s)处理中，不能终止测试...
	extern CString g_sLangTxt_DllUnStopTest;
    //Source\AutoTest\Module
	extern CString g_sLangID_CrtPrtlEgnFail; //创建规约引擎[%s]失败
	extern CString g_sLangTxt_CrtPrtlEgnFail;
	extern CString g_sLangID_RlsPrtlEgnFail; //释放规约引擎[%s]失败
	extern CString g_sLangTxt_RlsPrtlEgnFail;
	extern CString g_sLangID_TestLogMngmt; //测试记录文件管理
	extern CString g_sLangTxt_TestLogMngmt;
	extern CString g_sLangID_TestRptRecodFile; //测试报告记录文件
	extern CString g_sLangTxt_TestRptRecodFile;
	extern CString g_sLangID_TestRptFile; //测试报告文件
	extern CString g_sLangTxt_TestRptFile;
	extern CString g_sLangID_TestTaskFile; //测试任务文件
	extern CString g_sLangTxt_TestTaskFile;
	extern CString g_sLangID_SngDeviceRpt; //单装置多通道测试报告文件
	extern CString g_sLangTxt_SngDeviceRpt;
	extern CString g_sLangID_MulDeviceRpt; //多装置测试报告文件
	extern CString g_sLangTxt_MulDeviceRpt;
	extern CString g_sLangID_SngDeviceRpt2; //单装置多规约测试报告文件
	extern CString g_sLangTxt_SngDeviceRpt2;
	extern CString g_sLangID_MdvMgrpFile; //单装置多规约测试报告文件
	extern CString g_sLangTxt_MdvMgrpFile;
	extern CString g_sLangID_CreateCpntFail; //创建测试组件失败
	extern CString g_sLangTxt_CreateCpntFail;
	extern CString g_sLangID_MulDeviceRptS; //多装置测试报告文件(*.%s)|*.%s||
	extern CString g_sLangTxt_MulDeviceRptS;
	extern CString g_sLangID_SngDeviceRptS; //单装置多规约测试报告文件(*.%s)|*.%s||
	extern CString g_sLangTxt_SngDeviceRptS;
	extern CString g_sLangID_MdvMgrpFilter; //单装置多规约测试报告文件(*.%s)|*.%s||
	extern CString g_sLangTxt_MdvMgrpFilter;
	extern CString g_sLangID_FileRightError; //文件【%s】版本错误！
	extern CString g_sLangTxt_FileRightError;
	extern CString g_sLangID_DataIDUnext; //数据ID(%s)不存在
	extern CString g_sLangTxt_DataIDUnext;
	extern CString g_sLangID_TestCpntCopy; //        [%s]:[%s]测试完成(复制报告)
	extern CString g_sLangTxt_TestCpntCopy;
	extern CString g_sLangID_SngDevMulPrtc; //单装置多规约-路径1：%s
	extern CString g_sLangTxt_SngDevMulPrtc;
	extern CString g_sLangID_SngDevMulPrtc2; //单装置多规约-路径2：%s
	extern CString g_sLangTxt_SngDevMulPrtc2;
	extern CString g_sLangID_WaitSetting; //配置操作中，等待配置完成......
	extern CString g_sLangTxt_WaitSetting;
	extern CString g_sLangID_RecordFileRead; //读取录波文件前延时0秒,共%d秒
	extern CString g_sLangTxt_RecordFileRead;
	extern CString g_sLangID_RecordFileRead2; //读取录波文件前延时%d秒,共%d秒
	extern CString g_sLangTxt_RecordFileRead2;
	extern CString g_sLangID_ErrorMessage_a; //错误的处理消息...............
	extern CString g_sLangTxt_ErrorMessage_a;

    //GuideBook\Characteristic\CharMngr
	extern CString g_sLangID_ChrctCurDefn; //特性曲线定义
	extern CString g_sLangTxt_ChrctCurDefn;
	extern CString g_sLangID_ParaCurve; //曲线参数
	extern CString g_sLangTxt_ParaCurve;
	extern CString g_sLangID_ExpressionError; //表达式【%s】 错误
	extern CString g_sLangTxt_ExpressionError;
	extern CString g_sLangID_ExpressionVariable; //表达式变量【%s】 错误
	extern CString g_sLangTxt_ExpressionVariable;
    //GuideBook\Characteristic\Element
	extern CString g_sLangID_Arc; //圆弧（arc）
	extern CString g_sLangTxt_Arc;
	extern CString g_sLangID_Arcp; //圆弧（arcp）
	extern CString g_sLangTxt_Arcp;
	extern CString g_sLangID_Lens; //透镜（lens）
	extern CString g_sLangTxt_Lens;
	extern CString g_sLangID_Lined; //线段（lined）
	extern CString g_sLangTxt_Lined;
	extern CString g_sLangID_Line; //线（lined）
	extern CString g_sLangTxt_Line;
	extern CString g_sLangID_Linep; //线（linep）
	extern CString g_sLangTxt_Linep;
	extern CString g_sLangID_Liner; //射线（liner）
	extern CString g_sLangTxt_Liner;
	extern CString g_sLangID_Mho; //圆（mho）
	extern CString g_sLangTxt_Mho;
	extern CString g_sLangID_I2T; //I2T
	extern CString g_sLangTxt_I2T;
 	extern CString g_sLangID_IAC; //IAC
	extern CString g_sLangTxt_IAC;
	extern CString g_sLangID_IEC; //IEC
	extern CString g_sLangTxt_IEC;
	extern CString g_sLangID_IEEE; //IEEE
	extern CString g_sLangTxt_IEEE;
	extern CString g_sLangID_INVOWNDEF; //INVOWNDEF
	extern CString g_sLangTxt_INVOWNDEF;
    extern CString g_sLangID_Expr;//Expr
    extern CString g_sLangTxt_Expr;//表达式（Expr）
   //GuideBook\Characteristic\UI
	extern CString g_sLangID_CordnPtn; //坐标模式
	extern CString g_sLangTxt_CordnPtn;
	extern CString g_sLangID_TestFctnSel; //测试功能选择
	extern CString g_sLangTxt_TestFctnSel;
	extern CString g_sLangID_Location; //位置
	extern CString g_sLangTxt_Location;
	extern CString g_sLangID_RotationAngle; //旋转角度
	extern CString g_sLangTxt_RotationAngle;
	extern CString g_sLangID_CustomAngle; //自定义线角度
	extern CString g_sLangTxt_CustomAngle;
	extern CString g_sLangID_CoordinatesConflict; //特性曲线的坐标系“%s”与与图形管理模块的坐标系“%s”冲突
	extern CString g_sLangTxt_CoordinatesConflict;
	extern CString g_sLangID_VariableID; //变量ID
	extern CString g_sLangTxt_VariableID;
	extern CString g_sLangID_AssociationValue; //关联定值
	extern CString g_sLangTxt_AssociationValue;
	extern CString g_sLangID_EdgeType; //边类型
	extern CString g_sLangTxt_EdgeType;
	extern CString g_sLangID_TestPoint; //测点数
	extern CString g_sLangTxt_TestPoint;
	extern CString g_sLangID_ErrorBand; //误差带
	extern CString g_sLangTxt_ErrorBand;
	extern CString g_sLangID_EdgeDetails; //边详细信息
	extern CString g_sLangTxt_EdgeDetails;
	extern CString g_sLangID_CoordinateSystem; //坐标系
	extern CString g_sLangTxt_CoordinateSystem;
    //GuideBook\Device\Device
	extern CString g_sLangID_DataMatchScript; //数据匹配脚本
	extern CString g_sLangTxt_DataMatchScript;
	extern CString g_sLangID_Include; //包含
	extern CString g_sLangTxt_Include;
	extern CString g_sLangID_CertainUninclude; //必须不包含
	extern CString g_sLangTxt_CertainUninclude;
	extern CString g_sLangID_DataItfcMng; //数据接口管理
	extern CString g_sLangTxt_DataItfcMng;
	extern CString g_sLangID_DataItfc; //数据接口
	extern CString g_sLangTxt_DataItfc;
	extern CString g_sLangID_DataItfcVari; //数据接口变量
	extern CString g_sLangTxt_DataItfcVari;
	extern CString g_sLangID_DataDataUnExist; //数据【%s】在数据集【%s】不存在
	extern CString g_sLangTxt_DataDataUnExist;
	//GuideBook\Device
	extern CString g_sLangID_SoftStrap; //软压板
	extern CString g_sLangTxt_SoftStrap;
	extern CString g_sLangID_SetValue; //整定值
	extern CString g_sLangTxt_SetValue;
	extern CString g_sLangID_TestPara; //测试参数
	extern CString g_sLangTxt_TestPara;
	extern CString g_sLangID_ControlWord; //控制字
	extern CString g_sLangTxt_ControlWord;
	extern CString g_sLangID_OutputValue; //开出量
	extern CString g_sLangTxt_OutputValue;
	extern CString g_sLangID_InputValue; //开入量
	extern CString g_sLangTxt_InputValue;
	extern CString g_sLangID_AnalogValue; //模拟量
	extern CString g_sLangTxt_AnalogValue;
	//GuideBook\Item\CommCmd
	extern CString g_sLangID_PreDelay; //[%s]通讯前延时 (%s)==>>(%s)
	extern CString g_sLangTxt_PreDelay;
	extern CString g_sLangID_PostDelay; //[%s]通讯后延时 (%s)==>>(%s)
	extern CString g_sLangTxt_PostDelay;
	extern CString g_sLangID_RetryDelay; //[%s]重试前延时 (%s)==>>(%s)
	extern CString g_sLangTxt_RetryDelay;
	extern CString g_sLangID_CommunCmdUnExist; //通讯项目【%s】对应的通讯命令【%s】不存在
	extern CString g_sLangTxt_CommunCmdUnExist;
	extern CString g_sLangID_CommunCmdTimes; //通讯命令参数：%s
	extern CString g_sLangTxt_CommunCmdTimes;
	extern CString g_sLangID_AllRecord; //全部报文：%s
	extern CString g_sLangTxt_AllRecord;
	extern CString g_sLangID_StandardRecord; //标准报文：%s
	extern CString g_sLangTxt_StandardRecord;
	extern CString g_sLangID_NoRecord; //检索结果中没有报文【%s】=【%s】
	extern CString g_sLangTxt_NoRecord;
	extern CString g_sLangID_NoDefin; //没有定义【%s】
	extern CString g_sLangTxt_NoDefin;
	extern CString g_sLangID_RecordTimes; //报文【%s】【%s】时间差【%s】-【%s】=%d ms
	extern CString g_sLangTxt_RecordTimes;
	extern CString g_sLangID_TimeDiff; //CalSoeTimeEx：【%s，%s】【%s，%s】时间差【%s】-【%s】=%d ms
	extern CString g_sLangTxt_TimeDiff;
	extern CString g_sLangID_RecordResult; //报文验证的结果中没有【%s】
	extern CString g_sLangTxt_RecordResult;
	extern CString g_sLangID_Surplus; //多余：%s
	extern CString g_sLangTxt_Surplus;
	extern CString g_sLangID_AllExpRecord; //全部出口报文：%s
	extern CString g_sLangTxt_AllExpRecord;
	extern CString g_sLangID_Lack; //缺少：%s
	extern CString g_sLangTxt_Lack;
	//GuideBook\Item\MacroTest
	extern CString g_sLangID_CreatCharPara; //创建特性曲线搜索线：参数ID“%s”不存在
	extern CString g_sLangTxt_CreatCharPara;
	extern CString g_sLangID_Act; //动作
	extern CString g_sLangTxt_Act;
	extern CString g_sLangID_Unact; //未动作
	extern CString g_sLangTxt_Unact;
	extern CString g_sLangID_UndefinDataPara; //没有定义“%s”数据变量
	extern CString g_sLangTxt_UndefinDataPara;
	extern CString g_sLangID_ShowResult; //表达式【%s】计算结果为【%s】
	extern CString g_sLangTxt_ShowResult;
	extern CString g_sLangID_ParaMdf2; //[%s]参数修改： [%s] ==[%s] ->[%s]
	extern CString g_sLangTxt_ParaMdf2;
	//GuideBook\Item\Safety
	extern CString g_sLangID_LibraryFile; //库文件不存在【%s】
	extern CString g_sLangTxt_LibraryFile;
	extern CString g_sLangID_FctnNotFound; //【%s】write_qrcode_file 函数入口没找到
	extern CString g_sLangTxt_FctnNotFound;
	extern CString g_sLangID_MsgPrompt; //消息提示
	extern CString g_sLangTxt_MsgPrompt;
	//GuideBook\Item
	extern CString g_sLangID_TaskGuide2; //作业指导
	extern CString g_sLangTxt_TaskGuide2;
	extern CString g_sLangID_Delete2; //删除：%s
	extern CString g_sLangTxt_Delete2;
	extern CString g_sLangID_DelCommunPara; //删除通讯命令的参数：%s
	extern CString g_sLangTxt_DelCommunPara;
	extern CString g_sLangID_ItemRstError; //项目【%s】结果脚本语法错误
	extern CString g_sLangTxt_ItemRstError;
	//GuideBook\ReportMap
	extern CString g_sLangID_DataD2; //数据%d【%s】
	extern CString g_sLangTxt_DataD2;
	extern CString g_sLangID_NullReport; //空白报告部分使用“%s”替换
	extern CString g_sLangTxt_NullReport;
	extern CString g_sLangID_AdjustReport; //调整报告区域
	extern CString g_sLangTxt_AdjustReport;
	extern CString g_sLangID_ReDTest; //重复第%d次测试
	extern CString g_sLangTxt_ReDTest;
	extern CString g_sLangID_AreaDefin; //区域定义
	extern CString g_sLangTxt_AreaDefin;
	//GuideBook\Script
	extern CString g_sLangID_ScriptOverwrite; //脚本【%s】已经存在，并且两个脚本不一致，是否覆盖?
	extern CString g_sLangTxt_ScriptOverwrite;
	extern CString g_sLangID_DiffTypeData; //变量[%s]存在不同类型数据类型定义
	extern CString g_sLangTxt_DiffTypeData;
	extern CString g_sLangID_FileNewest; //引用脚本【%s】不存在，请检查脚本库文件是否为最新版本
	extern CString g_sLangTxt_FileNewest;
	extern CString g_sLangID_ParaError2; //ExitExe(\"%s\")参数错误
	extern CString g_sLangTxt_ParaError2;
	extern CString g_sLangID_NoDataReport; //没有报告数据
	extern CString g_sLangTxt_NoDataReport;
	extern CString g_sLangID_ParaError3; //CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！
	extern CString g_sLangTxt_ParaError3;
	extern CString g_sLangID_ParaError4; //CalAinStdError函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！
	extern CString g_sLangTxt_ParaError4;
	extern CString g_sLangID_ParaError5; //CalVariationEror函数:误差限[%f]都小于0，参数错误！
	extern CString g_sLangTxt_ParaError5;
	extern CString g_sLangID_FctnVariousUnExist; //CalVariationErrorEx函数:误差限变量[%s]不存在！
	extern CString g_sLangTxt_FctnVariousUnExist;
	extern CString g_sLangID_ErrFctnTest; //CalAinErr函数只用用于测试量值测试项目
	extern CString g_sLangTxt_ErrFctnTest;
	extern CString g_sLangID_ErrFctnUnExist; //CalAinErr函数数据【%s】不存在
	extern CString g_sLangTxt_ErrFctnUnExist;
	extern CString g_sLangID_StdErrorFctnTest; //CalAinStdError函数只用用于测试量值测试项目
	extern CString g_sLangTxt_StdErrorFctnTest;
	extern CString g_sLangID_StdErrorFctnUnExist; //CalAinStdError函数数据【%s】不存在
	extern CString g_sLangTxt_StdErrorFctnUnExist;
	extern CString g_sLangID_StdErrorFctnUnExistData; //CalAinStdError函数数据【%d】不存在不够
	extern CString g_sLangTxt_StdErrorFctnUnExistData;
	extern CString g_sLangID_FlterFctnTest;         //FlterCalErrorMax函数只用用于测试量值测试项目
	extern CString g_sLangTxt_FlterFctnTest;
	extern CString g_sLangID_FlterFctnUnExist; //FlterCalErrorMax函数数据【%s】不存在
	extern CString g_sLangTxt_FlterFctnUnExist;
	extern CString g_sLangID_FlterFctnUnExist2; //FlterCalErrorMax函数绝对误差数据【%s】不存在
	extern CString g_sLangTxt_FlterFctnUnExist2;
	extern CString g_sLangID_VariationFctnTest; //CalVariationErrorEx函数只用用于测量值测试项目
	extern CString g_sLangTxt_VariationFctnTest;
	extern CString g_sLangID_VariationFctnItem; //CalVariationErrorEx函数所在的项目的父项目不是电气量项目
	extern CString g_sLangTxt_VariationFctnItem;
	extern CString g_sLangID_VariationFctnUnExist; //CalVariationErrorEx函数数据【%s】不存在
	extern CString g_sLangTxt_VariationFctnUnExist;
	extern CString g_sLangID_VariationFctnUnExist2; //CalVariationErrorEx函数基准值【%s】不存在
	extern CString g_sLangTxt_VariationFctnUnExist2;
	extern CString g_sLangID_VariationFctnUnExist3; //CalVariationErrorEx函数数据【实测值】【%s】不存在
	extern CString g_sLangTxt_VariationFctnUnExist3;
	extern CString g_sLangID_VariationFctnUnExist4; //CalVariationErrorEx函数数据【理论值】【%s】不存在
	extern CString g_sLangTxt_VariationFctnUnExist4;
	extern CString g_sLangID_VariationFctnUnExist5; //CalVariationErrorEx函数：测试参数基准值【%s】不存在
	extern CString g_sLangTxt_VariationFctnUnExist5;
	extern CString g_sLangID_VariationFctnUnExist6;         //CalVariationErrorEx函数数据【结果变量】【%s】不存在
	extern CString g_sLangTxt_VariationFctnUnExist6;
	extern CString g_sLangID_ResultJude;//实测值=%.5f  ,理论值=%.5f  ,基准值=%.5f  变差=%.5f 误差限=%.5f  结果判断=%d
	extern CString g_sLangTxt_ResultJude;
	extern CString g_sLangID_SetItemIDUnExist; //SetItemParaValue ID不存在,Path(%s) ID(%s) items
	extern CString g_sLangTxt_SetItemIDUnExist;
	extern CString g_sLangID_SetItemIDUnExist2; //SetReportValue ID不存在,Path(%s) ID(%s) items
	extern CString g_sLangTxt_SetItemIDUnExist2;
	extern CString g_sLangID_PathItem; //路径检索的项目不唯一,Path(%s) select %d items
	extern CString g_sLangTxt_PathItem;
	extern CString g_sLangID_PathItem2; //路径指定的项目不存在,Path(%s) select %d items
	extern CString g_sLangTxt_PathItem2;
	extern CString g_sLangID_CalCall; //CalTmGap只能在通讯命令项目中被调用
	extern CString g_sLangTxt_CalCall;
	extern CString g_sLangID_NoDataReport2; //CalTmGap:没有报告数据
	extern CString g_sLangTxt_NoDataReport2;
	extern CString g_sLangID_PathNoItem; //路径[%s]没有选择的项目
	extern CString g_sLangTxt_PathNoItem;
	extern CString g_sLangID_PathSelItem; //路径[%s]选择的项目不唯一
	extern CString g_sLangTxt_PathSelItem;
	extern CString g_sLangID_CannotUse; //DownMacroPara不能在项目\"%s\"中使用
	extern CString g_sLangTxt_CannotUse;
	extern CString g_sLangID_CannotUse2; //DownMacroPara不能在项目\"%s\"中使用(项目的父对象错误)
	extern CString g_sLangTxt_CannotUse2;
	extern CString g_sLangID_CannotUse3; //DownMacroPara不能在项目\"%s\"中使用(项目的父对象非电气量项目)
	extern CString g_sLangTxt_CannotUse3;
	extern CString g_sLangID_NullDataReport; //FilterCombineReportEx函数：报告数据为空
	extern CString g_sLangTxt_NullDataReport;
	extern CString g_sLangID_DataReportID; //不存在ID为\"%s\"的报告数据
	extern CString g_sLangTxt_DataReportID;
	extern CString g_sLangID_DataUnExist; //ReportEx数据(Index=%d  AttrID=%s)不存在
	extern CString g_sLangTxt_DataUnExist;
	extern CString g_sLangID_DataUnExist2; //数据【%s】不存在
	extern CString g_sLangTxt_DataUnExist2;
	extern CString g_sLangID_DataUnExist3; //数据值【%s】不存在
	extern CString g_sLangTxt_DataUnExist3;
	extern CString g_sLangID_DataPathUn; //数据路径【%s】检索出的数据【%d】不存在
	extern CString g_sLangTxt_DataPathUn;
	extern CString g_sLangID_FtcnCmdUse; //CalSoeTime函数只能在通讯命令中使用
	extern CString g_sLangTxt_FtcnCmdUse;
	extern CString g_sLangID_FtcnCmdUse2; //SetCmdZoneIndex函数只能用于通讯命令
	extern CString g_sLangTxt_FtcnCmdUse2;
	extern CString g_sLangID_FtcnScriptCall; //函数ValidBeginEndValRange只能作为电气量项目的脚本调用
	extern CString g_sLangTxt_FtcnScriptCall;
	extern CString g_sLangID_FctnUnExist; //函数ValidBeginEndValRange:[%s]不存在
	extern CString g_sLangTxt_FctnUnExist;
	//GuideBook\SetFileImExport
	extern CString g_sLangID_FixedValueData; //%s(%s)定值单数据
	extern CString g_sLangTxt_FixedValueData;
	extern CString g_sLangID_Marking; //标示
	extern CString g_sLangTxt_Marking;
	extern CString g_sLangID_PdfFile; //Pdf定值文件
	extern CString g_sLangTxt_PdfFile;
	extern CString g_sLangID_XMLFile; //XML定值文件
	extern CString g_sLangTxt_XMLFile;
	extern CString g_sLangID_WordFile; //Word定值文件
	extern CString g_sLangTxt_WordFile;
	extern CString g_sLangID_ExcelFile; //Excel定值文件
	extern CString g_sLangTxt_ExcelFile;
	extern CString g_sLangID_OATSFile; //OATS自定义定值文件
	extern CString g_sLangTxt_OATSFile;
	//GuideBook
	extern CString g_sLangID_DataTypeUnExist2; //数据类型文件 [%s] 不存在
	extern CString g_sLangTxt_DataTypeUnExist2;
	extern CString g_sLangID_CommunSetUnExist; //通讯配置文件\"%s\"不存在
	extern CString g_sLangTxt_CommunSetUnExist;
	extern CString g_sLangID_TestTypeUnExist; //测试类型配置文件\"%s\"不存在
	extern CString g_sLangTxt_TestTypeUnExist;
	extern CString g_sLangID_CreatDomFail; //MSXML2创建DOMDocument失败
	extern CString g_sLangTxt_CreatDomFail;
	extern CString g_sLangID_OpenMsxmlFail; //MSXML2打开文件【%s】失败
	extern CString g_sLangTxt_OpenMsxmlFail;
	extern CString g_sLangID_YearMonDay; //%Y年%m月%d日
	extern CString g_sLangTxt_YearMonDay;
	extern CString g_sLangID_UnitPara; //装置参数
	extern CString g_sLangTxt_UnitPara;
	extern CString g_sLangID_FixedValue; //定值
	extern CString g_sLangTxt_FixedValue;
	extern CString g_sLangID_Platen; //压板
	extern CString g_sLangTxt_Platen;
	extern CString g_sLangID_Telemetering; //遥测
	extern CString g_sLangTxt_Telemetering;
	extern CString g_sLangID_Telecommunicating; //遥信
	extern CString g_sLangTxt_Telecommunicating;
	extern CString g_sLangID_FaultReport; //故障报告
	extern CString g_sLangTxt_FaultReport;
	extern CString g_sLangID_ProtectEvent; //保护事件
	extern CString g_sLangTxt_ProtectEvent;
	extern CString g_sLangID_FaultSignal; //故障信号
	extern CString g_sLangTxt_FaultSignal;
	extern CString g_sLangID_AlarmSignal; //告警信号
	extern CString g_sLangTxt_AlarmSignal;
	extern CString g_sLangID_SamplingValue; //采样值
	extern CString g_sLangTxt_SamplingValue;
	extern CString g_sLangID_Telecontrolling; //遥控
	extern CString g_sLangTxt_Telecontrolling;
	extern CString g_sLangID_Custom; //自定义
	extern CString g_sLangTxt_Custom;
	extern CString g_sLangID_SingDataMode; //单一数据填写模式
	extern CString g_sLangTxt_SingDataMode;
	extern CString g_sLangID_ExcelDataMode; //表格行填写模式
	extern CString g_sLangTxt_ExcelDataMode;
	extern CString g_sLangID_ExcelDataMode2; //表格列填写模式
	extern CString g_sLangTxt_ExcelDataMode2;

	//TaskMngr
	extern CString g_sLangID_NewCreatTask; //新建任务
	extern CString g_sLangTxt_NewCreatTask;
	extern CString g_sLangID_NewProject; //新建工程
	extern CString g_sLangTxt_NewProject;
	extern CString g_sLangID_DeleteTask; //删除任务
	extern CString g_sLangTxt_DeleteTask;
	extern CString g_sLangID_DeleteProject; //删除工程
	extern CString g_sLangTxt_DeleteProject;
	extern CString g_sLangID_TaskArchive; //任务归档
	extern CString g_sLangTxt_TaskArchive;
	extern CString g_sLangID_ProjectArchive; //工程归档
	extern CString g_sLangTxt_ProjectArchive;
	extern CString g_sLangID_OpenProject; //打开工程
	extern CString g_sLangTxt_OpenProject;
	extern CString g_sLangID_CloseProject; //关闭工程
	extern CString g_sLangTxt_CloseProject;
	extern CString g_sLangID_TestRecordFile; //测试记录文件
	extern CString g_sLangTxt_TestRecordFile;
	extern CString g_sLangID_RecordFile; //记录文件大小
	extern CString g_sLangTxt_RecordFile;
	extern CString g_sLangID_LastAccessedTimes; //最后访问时间
	extern CString g_sLangTxt_LastAccessedTimes;
	extern CString g_sLangID_ReportFile; //报告文件
	extern CString g_sLangTxt_ReportFile;
	extern CString g_sLangID_ReportFileSize; //报告文件大小
	extern CString g_sLangTxt_ReportFileSize;
	extern CString g_sLangID_NewTask; //新任务
	extern CString g_sLangTxt_NewTask;
	extern CString g_sLangID_EnterTask; //进入测试
	extern CString g_sLangTxt_EnterTask;
	extern CString g_sLangID_NewReport; //新报告
	extern CString g_sLangTxt_NewReport;

	extern CString g_sLangID_TestComplete; //测试完成
	extern CString g_sLangTxt_TestComplete;
	extern CString g_sLangID_TerminationTest; //终止测试
	extern CString g_sLangTxt_TerminationTest;
	extern CString g_sLangID_Testing; //测试中
	extern CString g_sLangTxt_Testing;
	extern CString g_sLangID_UnTest; //未测试
	extern CString g_sLangTxt_UnTest;
	extern CString g_sLangID_SystemPara; //系统参数
	extern CString g_sLangTxt_SystemPara;
	extern CString g_sLangID_CreatWordFail; //创建Word失败！导出任务报告失败！
	extern CString g_sLangTxt_CreatWordFail;
	extern CString g_sLangID_TestReport; //测试报告
	extern CString g_sLangTxt_TestReport;
	extern CString g_sLangID_Conclusion; //结论
	extern CString g_sLangTxt_Conclusion;
	extern CString g_sLangID_UnqualifiedItem; //有不合格项
	extern CString g_sLangTxt_UnqualifiedItem;
	extern CString g_sLangID_ViewPara; //查看参数
	extern CString g_sLangTxt_ViewPara;
	extern CString g_sLangID_FctnGbNotFound; //函数GbUICreate入口地址没有找到
	extern CString g_sLangTxt_FctnGbNotFound;

	extern CString g_sLangID_DataBatch; //数据集遍历批量
	extern CString g_sLangTxt_DataBatch;
	extern CString g_sLangID_Developing; //开发中
	extern CString g_sLangTxt_Developing;
	extern CString g_sLangID_ReportManager; //报告管理
	extern CString g_sLangTxt_ReportManager;
	extern CString g_sLangID_TestReady; //测试准备
	extern CString g_sLangTxt_TestReady;
	extern CString g_sLangID_TestWork; //测试工作恢复
	extern CString g_sLangTxt_TestWork;
	extern CString g_sLangID_CellpAdding; //单元格填充
	extern CString g_sLangTxt_CellpAdding;
	extern CString g_sLangID_ColumnFillMmode; //列填充模式
	extern CString g_sLangTxt_ColumnFillMmode;
	extern CString g_sLangID_HnagFillMmode; //行填充模式
	extern CString g_sLangTxt_HnagFillMmode;
	extern CString g_sLangID_ParaVarious; //参数变量
	extern CString g_sLangTxt_ParaVarious;
	extern CString g_sLangID_Format; //格式
	extern CString g_sLangTxt_Format;
	extern CString g_sLangID_Id; 
	extern CString g_sLangTxt_Id;
// 	extern CString g_sLangID_Variable; //变量
// 	extern CString g_sLangTxt_Variable;
	extern CString g_sLangID_DataVariousDefin; //数据接口变量定义
	extern CString g_sLangTxt_DataVariousDefin;
	extern CString g_sLangID_ProPaInf;    //项目的路径信息
	extern CString g_sLangTxt_ProPaInf;
	extern CString g_sLangID_TestProjInf;    //测试项目信息
	extern CString g_sLangTxt_TestProjInf;
	extern CString g_sLangID_SetAsReport;    //设为最终报告
	extern CString g_sLangTxt_SetAsReport;
	extern CString g_sLangID_ViewMessJud;    //查看报文判断
	extern CString g_sLangTxt_ViewMessJud;
	extern CString g_sLangID_TestProTestRep;    //测试项目实验报告
	extern CString g_sLangTxt_TestProTestRep;
	extern CString g_sLangID_InstrutionInfo;
	extern CString g_sLangTxt_InstrutionInfo;
	extern CString g_sLangID_GuideAutoWizardFile;
	extern CString g_sLangTxt_GuideAutoWizardFile;
	extern CString g_sLangID_NextStep;
	extern CString g_sLangTxt_NextStep;
	extern CString g_sLangID_ClickToNextStep;
	extern CString g_sLangTxt_ClickToNextStep;
	extern CString g_sLangID_OperCompleteToNext;
	extern CString g_sLangTxt_OperCompleteToNext;
	extern CString g_sLangID_DataSet;
	extern CString g_sLangTxt_DataSet;
	extern CString g_sLangID_TestItemNotExist;
	extern CString g_sLangTxt_TestItemNotExist;
	extern CString g_sLangID_SetItem;
	extern CString g_sLangTxt_SetItem;
	extern CString g_sLangID_DataMap;
	extern CString g_sLangTxt_DataMap;
	extern CString g_sLangID_DestRefData;
	extern CString g_sLangTxt_DestRefData;
	extern CString g_sLangID_TestItem;
	extern CString g_sLangTxt_TestItem;
	extern CString g_sLangID_NumberGroup;
	extern CString g_sLangTxt_NumberGroup;
	extern CString g_sLangID_ItemClassName;
	extern CString g_sLangTxt_ItemClassName;
	extern CString g_sLangID_ItemClassId;
	extern CString g_sLangTxt_ItemClassId;
	extern CString g_sLangID_BatchEnumGroup;
	extern CString g_sLangTxt_BatchEnumGroup;
	extern CString g_sLangID_BatchItemNoName;
	extern CString g_sLangTxt_BatchItemNoName;
	extern CString g_sLangID_BatchItemNoId;
	extern CString g_sLangTxt_BatchItemNoId;
	extern CString g_sLangID_BatchItemNoDataset;
	extern CString g_sLangTxt_BatchItemNoDataset;
	extern CString g_sLangID_DatasetNotExist;
	extern CString g_sLangTxt_DatasetNotExist;
	extern CString g_sLangID_DataMapNotOnly;
	extern CString g_sLangTxt_DataMapNotOnly;
	extern CString g_sLangID_ChannelCfg;
	extern CString g_sLangTxt_ChannelCfg;
	extern CString g_sLangID_InsertReportTem;
	extern CString g_sLangTxt_InsertReportTem;
	extern CString g_sLangID_CannotInstant;
	extern CString g_sLangTxt_CannotInstant;
	extern CString g_sLangID_InsertTestTem;
	extern CString g_sLangTxt_InsertTestTem;
	extern CString g_sLangID_CommCmdNoDataset;
	extern CString g_sLangTxt_CommCmdNoDataset;
	extern CString g_sLangID_Initial;
	extern CString g_sLangTxt_Initial;
	extern CString g_sLangID_DealSubTemTestPara;
	extern CString g_sLangTxt_DealSubTemTestPara;
	extern CString g_sLangID_OpenedWizardFile;
	extern CString g_sLangTxt_OpenedWizardFile;
	extern CString g_sLangID_SelTestSubTem;
	extern CString g_sLangTxt_SelTestSubTem;
	extern CString g_sLangID_SelSubTem;
	extern CString g_sLangTxt_SelSubTem;
	extern CString g_sLangID_SelTestSubTemInsert;
	extern CString g_sLangTxt_SelTestSubTemInsert;
	extern CString g_sLangID_SelTestSubTemInsert2;
	extern CString g_sLangTxt_SelTestSubTemInsert2;
	extern CString g_sLangID_SaveTestTem;
	extern CString g_sLangTxt_SaveTestTem;
	extern CString g_sLangID_SaveTestTemWizardOver;
	extern CString g_sLangTxt_SaveTestTemWizardOver;
	extern CString g_sLangID_SetTestTemAttr;
	extern CString g_sLangTxt_SetTestTemAttr;
	extern CString g_sLangID_SetTestTemAttr2;
	extern CString g_sLangTxt_SetTestTemAttr2;
	extern CString g_sLangID_SetSubTemInterface;
	extern CString g_sLangTxt_SetSubTemInterface;
	extern CString g_sLangID_SetDeviceDataModel;
	extern CString g_sLangTxt_SetDeviceDataModel;
	extern CString g_sLangID_SetDeviceAttr;
	extern CString g_sLangTxt_SetDeviceAttr;
	extern CString g_sLangID_SetDeviceDataType;
	extern CString g_sLangTxt_SetDeviceDataType;
	extern CString g_sLangID_SetDeviceCharCurve;
	extern CString g_sLangTxt_SetDeviceCharCurve;
	extern CString g_sLangID_SetDeviceAttr2;
	extern CString g_sLangTxt_SetDeviceAttr2;
	extern CString g_sLangID_SetDeviceDataType2;
	extern CString g_sLangTxt_SetDeviceDataType2;
	extern CString g_sLangID_SetDeviceCharCurve2;
	extern CString g_sLangTxt_SetDeviceCharCurve2;
	extern CString g_sLangID_Execute;
	extern CString g_sLangTxt_Execute;
	extern CString g_sLangID_CommCmdError;
	extern CString g_sLangTxt_CommCmdError;
	extern CString g_sLangID_DataPathNoData;
	extern CString g_sLangTxt_DataPathNoData;
	extern CString g_sLangID_IdReplace;
	extern CString g_sLangTxt_IdReplace;
	extern CString g_sLangID_NameReplaceCompleted;
	extern CString g_sLangTxt_NameReplaceCompleted;
	extern CString g_sLangID_AddObjMatchUnsucc;
	extern CString g_sLangTxt_AddObjMatchUnsucc;
	extern CString g_sLangID_ReplaceCompleted2;
	extern CString g_sLangTxt_ReplaceCompleted2;
	extern CString g_sLangID_DealCommCmd;
	extern CString g_sLangTxt_DealCommCmd;
	extern CString g_sLangID_RelNotOnly;
	extern CString g_sLangTxt_RelNotOnly;
	extern CString g_sLangID_DataInterfaceName;
	extern CString g_sLangTxt_DataInterfaceName;
	extern CString g_sLangID_DealMode;
	extern CString g_sLangTxt_DealMode;
	extern CString g_sLangID_StartValue;
	extern CString g_sLangTxt_StartValue;
	extern CString g_sLangID_StepNumber;
	extern CString g_sLangTxt_StepNumber;
	extern CString g_sLangID_SCLChannelName;
	extern CString g_sLangTxt_SCLChannelName;
	extern CString g_sLangID_DataName;
	extern CString g_sLangTxt_DataName;
	extern CString g_sLangID_ChannelIndex;
	extern CString g_sLangTxt_ChannelIndex;
	extern CString g_sLangID_DatasetTraverse;
	extern CString g_sLangTxt_DatasetTraverse;
	extern CString g_sLangID_NumberArithmetic;
	extern CString g_sLangTxt_NumberArithmetic;
	extern CString g_sLangID_InitOptimizeList;
	extern CString g_sLangTxt_InitOptimizeList;
	extern CString g_sLangID_InitPreTestList;
	extern CString g_sLangTxt_InitPreTestList;
	extern CString g_sLangID_InitTestRecoverList;
	extern CString g_sLangTxt_InitTestRecoverList;
	extern CString g_sLangID_OptimizePreTestItem;
	extern CString g_sLangTxt_OptimizePreTestItem;
	extern CString g_sLangID_OptimizeTestRecoverItem;
	extern CString g_sLangTxt_OptimizeTestRecoverItem;
	extern CString g_sLangID_OptimizeIecCfgDownload;
	extern CString g_sLangTxt_OptimizeIecCfgDownload;
	extern CString g_sLangID_OptimizeSysParaEditItem;
	extern CString g_sLangTxt_OptimizeSysParaEditItem;
	extern CString g_sLangID_ItemClassAllSubItem;
	extern CString g_sLangTxt_ItemClassAllSubItem;
	extern CString g_sLangID_ItemClassSubItem;
	extern CString g_sLangTxt_ItemClassSubItem;
	extern CString g_sLangID_SelItemClassMode;
	extern CString g_sLangTxt_SelItemClassMode;
	extern CString g_sLangID_ImportTo;
	extern CString g_sLangTxt_ImportTo;
	extern CString g_sLangID_NoDataObjDef;
	extern CString g_sLangTxt_NoDataObjDef;
	extern CString g_sLangID_FileNameWithout;
	extern CString g_sLangTxt_FileNameWithout;
	extern CString g_sLangID_FileMngr;
	extern CString g_sLangTxt_FileMngr;
	extern CString g_sLangID_Average;
	extern CString g_sLangTxt_Average;
	extern CString g_sLangID_CommCmdCheckComplete;
	extern CString g_sLangTxt_CommCmdCheckComplete;
	extern CString g_sLangID_CommCmdParaAbnormal;
	extern CString g_sLangTxt_CommCmdParaAbnormal;
	extern CString g_sLangID_DeleteInvalidPara;  
	extern CString g_sLangTxt_DeleteInvalidPara;
	extern CString g_sLangID_ElectricCheckComplete;
	extern CString g_sLangTxt_ElectricCheckComplete;
	extern CString g_sLangID_ElectricParaAbnormal;
	extern CString g_sLangTxt_ElectricParaAbnormal;
	extern CString g_sLangID_OpenWordFail;
	extern CString g_sLangTxt_OpenWordFail;
	extern CString g_sLangID_HaveMarkSureReplace;  
	extern CString g_sLangTxt_HaveMarkSureReplace;
	extern CString g_sLangID_NoWord;
	extern CString g_sLangTxt_NoWord;
	extern CString g_sLangID_OpenDocFail;
	extern CString g_sLangTxt_OpenDocFail;
	extern CString g_sLangID_BookMarkExist;
	extern CString g_sLangTxt_BookMarkExist;
	extern CString g_sLangID_InsertTitleFail;  
	extern CString g_sLangTxt_InsertTitleFail;
// 	extern CString g_sLangID_Title;
// 	extern CString g_sLangTxt_Title;
	extern CString g_sLangID_InsertFail;
	extern CString g_sLangTxt_InsertFail;
	extern CString g_sLangID_Finish;
	extern CString g_sLangTxt_Finish;
	extern CString g_sLangID_Unqualified2;
	extern CString g_sLangTxt_Unqualified2;
	extern CString g_sLangID_TestFinish;
	extern CString g_sLangTxt_TestFinish;

	extern CString g_sLangID_SelNoArea;  //_T("sSelNoArea");
	extern CString g_sLangTxt_SelNoArea;  //_T("没有选择表格区域！");
	extern CString g_sLangID_SelOnlyOneRowCol;  //_T("sSelOnlyOneRowCol");
	extern CString g_sLangTxt_SelOnlyOneRowCol;  //_T("选择表格区域只有一行一列，不具备批量插入条件！");
	extern CString g_sLangID_ColRowsNotSame;  //_T("sColRowsNotSame");
	extern CString g_sLangTxt_ColRowsNotSame;  //_T("选择表格区域每列的行列数不相同，不具备批量插入条件！");
	extern CString g_sLangID_SelNoItem;  //_T("sSelNoItem");
	extern CString g_sLangTxt_SelNoItem;  //_T("没有选择测试项目！");
	extern CString g_sLangID_MustSelYcItem;  //_T("sMustSelYcItem");
	extern CString g_sLangTxt_MustSelYcItem;  //_T("请选择包含遥测项目的项目分类！");
	extern CString g_sLangID_HasNoMacroTest;  //_T("sHasNoMacroTest");
	extern CString g_sLangTxt_HasNoMacroTest;  //_T("【%s】下没有电气量测试功能");
	extern CString g_sLangID_HasNoYcItem;  //_T("sHasNoYcItem");
	extern CString g_sLangTxt_HasNoYcItem;  //_T("【%s】下没有遥测测试电气量测试功能");
	extern CString g_sLangID_RepeatTimeNotSame;  //_T("sRepeatTimeNotSame");
	extern CString g_sLangTxt_RepeatTimeNotSame;  //_T("【%s】的重复次数%d与【%s】的重复次数%d不一致!");
	extern CString g_sLangID_MacroTestNotSame;  //_T("sMacroTestNotSame");
	extern CString g_sLangTxt_MacroTestNotSame;  //_T("【%s】与【%s】的测试功能不一致!");

	extern CString g_sLangID_AttrID_Value;  //_T("sAttrID_Value");
	extern CString g_sLangTxt_AttrID_Value;  //_T("数值(value)");
	extern CString g_sLangID_AttrID_Name;  //_T("sAttrID_Name");
	extern CString g_sLangTxt_AttrID_Name;  //_T("名称(Name)");

	extern CString g_sLangID_TestPrjNotFinish;
	extern CString g_sLangTxt_TestPrjNotFinish;

	extern CString g_sLangID_RsltExprScript;
	extern CString g_sLangTxt_RsltExprScript;

	extern CString g_sLangID_IgnoreAbnormal;  
	extern CString g_sLangTxt_IgnoreAbnormal;

	extern CString g_sLangID_SGroupS;//%s%s-组%d.%s
	extern CString g_sLangTxt_SGroupS;
	extern CString g_sLangID_SGroupFileName;//%s%s-组%d.%s
	extern CString g_sLangTxt_SGroupFileName;

// 	extern CString g_sLangID_IEC_Open;
// 	extern CString g_sLangTxt_IEC_Open;
	extern CString g_sLangID_IEC_AddSCL;
	extern CString g_sLangTxt_IEC_AddSCL;
	extern CString g_sLangID_IEC_DeleteNow;
	extern CString g_sLangTxt_IEC_DeleteNow;
	extern CString g_sLangID_IEC_Emptyout;
	extern CString g_sLangTxt_IEC_Emptyout;
 	extern CString g_sLangID_Native_FileName;
 	extern CString g_sLangTxt_Native_FileName;
// 	extern CString g_sLangID_Native_Choose;
// 	extern CString g_sLangTxt_Native_Choose;
	extern CString g_sLangID_Dates;
	extern CString g_sLangTxt_Dates;
// 	extern CString g_sLangID_Native_Form; //格式
// 	extern CString g_sLangTxt_Native_Form;

	extern CString g_sLangID_FilePath;
	extern CString g_sLangTxt_FilePath;

	extern CString g_sLangTxt_FileSize;
	extern CString g_sLangID_FileSize;

	extern CString g_sLangID_currentfile;
	extern CString g_sLangTxt_currentfile;
	extern CString g_sLangID_parsefile;
	extern CString g_sLangTxt_parsefile;
	extern CString g_sLangID_confirmfiles;
	extern CString g_sLangTxt_confirmfiles;
	extern CString g_sLangID_IEDdialog;
	extern CString g_sLangTxt_IEDdialog;
	extern CString g_sLangID_sameopen;
	extern CString g_sLangTxt_sameopen;

	extern CString g_sLangID_Native_ChooseOpenFile;
	extern CString g_sLangTxt_Native_ChooseOpenFile;
	extern  CString g_sLangID_Gradient_ShowUpath;  
	extern  CString g_sLangTxt_Gradient_ShowUpath;
	extern CString g_sLangID_warning;
	extern CString g_sLangTxt_warning;


	extern CString g_sLangID_UpdataFail                 ;//= _T("sUpdataFail");
	extern CString g_sLangTxt_UpdataFail                ;//= _T("测试仪更新:查询[系统标识:%d,版本标识:%d]更新信息失败!")
	extern CString g_sLangID_DownloadFile				 ;//= _T("sDownloadFile");
	extern CString g_sLangTxt_DownloadFile              ;//= _T("测试仪更新:查询信息完成，开始下载文件，请稍后...[系统标识:%d,版本标识:%d]");
	extern CString g_sLangID_DownloadFail               ;//= _T("sDownloadFail");
	extern CString g_sLangTxt_DownloadFail              ;//= _T("测试仪更新:下载版本文件[%s]失败!");
	extern CString g_sLangID_DownloadCompress           ;//= _T("sDownloadCompress ");
	extern CString g_sLangTxt_DownloadCompress          ;//= _T("测试仪更新:下载版本文件[%s]完成,准备解压缩!");
	extern CString g_sLangID_LocalUpgrades              ;//= _T("sLocalUpgrades");
	extern CString g_sLangTxt_LocalUpgrades             ;//= _T("测试仪更新:已结束与云平台交互,开始解压缩更新包并进行本地升级!");
	extern CString g_sLangID_Reboot                     ;//= _T("sReboot");
	extern CString g_sLangTxt_Reboot                    ;//= _T("测试仪更新:升级成功后,需将测试仪重启,请稍等......");	
	extern CString g_sLangID_UnpackSucc                 ;//= _T("sUnpackSucc");
	extern CString g_sLangTxt_UnpackSucc                ;//= _T("测试仪更新：解压本地更新包【%s】成功!");
	extern CString g_sLangID_UnpackFail                 ;//= _T("sUnpackFail");
	extern CString g_sLangTxt_UnpackFail                ;//= _T("测试仪更新：解压本地更新包【%s】失败!");
	extern CString g_sLangID_Update_UpdateSuccess       ;//= _T("sUpdate_UpdateSuccess");
	extern CString g_sLangTxt_Update_UpdateSuccess      ;//= _T("程序升级成功，请手动重启仪器");

	extern CString g_sLangID_Escalating		             ;//= _T("sEscalating");
	extern CString g_sLangTxt_Escalating			     ;//= _T("正在准备升级文件，请稍后...");
	extern CString g_sLangID_TesterUpdate				 ;//= _T("sTesterUpdate")
    extern CString g_sLangTxt_TesterUpdate		         ;//= _T("测试仪更新：已更新%.02f%%")
	extern CString g_sLangID_BackupSucc			         ;//= _T("sBackupSucc")
	extern CString g_sLangTxt_BackupSucc				 ;//=_T("测试仪更新：文件【%s】备份成功!")
	extern CString g_sLangID_BackupFail				     ;//= _T("sBackupFail")
	extern CString g_sLangTxt_BackupFail				 ;//=_T("测试仪更新：文件【%s】备份失败!")
	extern CString g_sLangID_CopySucc				     ;//= _T("sCopySucc")
	extern CString g_sLangTxt_CopySucc				     ;//=_T("测试仪更新：文件【%s】拷贝成功!")
	extern CString g_sLangID_TesterUpdataFail			 ;//= _T("sTesterUpdataFail")
	extern CString g_sLangTxt_TesterUpdataFail			 ;//=_T("测试仪更新：文件【%s】更新失败!")

	//yi
	extern CString g_sLangID_ExpSucc;
	extern CString g_sLangTxt_ExpSucc;
	extern CString g_sLangID_ExpFail;
	extern CString g_sLangTxt_ExpFail;
	extern CString g_sLangID_ImpSucc;
	extern CString g_sLangTxt_ImpSucc;
	extern CString g_sLangID_ImpFail;
	extern CString g_sLangTxt_ImpFail;
	extern CString g_sLangID_RemainingMemorySize;
	extern CString g_sLangTxt_RemainingMemorySize;
	extern CString g_sLangID_InsufficientSystemMemory;
	extern CString g_sLangTxt_InsufficientSystemMemory;
	extern CString g_sLangID_ExistenceSCDFiles;
	extern CString g_sLangTxt_ExistenceSCDFiles;
	extern CString g_sLangID_NoExistenceSCLFiles;
	extern CString g_sLangTxt_NoExistenceSCLFiles;
	extern CString g_sLangID_AnalysisSCLFiles;
	extern CString g_sLangTxt_AnalysisSCLFiles;
	extern CString g_sLangID_LoadSCLFiles;
	extern CString g_sLangTxt_LoadSCLFiles;
	extern CString g_sLangID_LoadSCLFilesProgressBar;
	extern CString g_sLangTxt_LoadSCLFilesProgressBar;
	extern CString 	g_sLangID_SaveSCLFiles ;
	extern CString g_sLangTxt_SaveSCLFiles;
	extern CString g_sLangID_State_No;
	extern CString g_sLangTxt_State_No;
	extern CString g_sLangID_State_Yes;
	extern CString g_sLangTxt_State_Yes;

//shaolei 2024-12-9
	extern CString g_sLangID_AutoTest_SvrName;                       //= _T("sAutoTest_SvrName")
	extern CString g_sLangTxt_AutoTest_SvrName;                      //= _T("自动测试服务名称")
	extern CString g_sLangID_AutoTest_SvrVersion;				      //= _T("sAutoTest_SvrVersion")
	extern CString g_sLangTxt_AutoTest_SvrVersion;                   //= _T("自动测试服务版本")

//国际版移植 20250207 xueyangfan
	extern CString g_sLangID_Xrio_EnterNumbers;                 //=_T("Xrio_EnterNumbers");
	extern CString g_sLangTxt_Xrio_EnterNumbers;                //=_T("请输入一个数字。");
	extern CString g_sLangID_Xrio_ValueLessThanOREqual;         //=_T("Xrio_ValueLessThanOREqual");
	extern CString g_sLangTxt_Xrio_ValueLessThanOREqual;        //=_T("值必须 <= ");
	extern CString g_sLangID_Xrio_ValueGreaterThanOREqual;      //=_T("Xrio_ValueGreaterThanOREqual");
	extern CString g_sLangTxt_Xrio_ValueGreaterThanOREqual;     //=_T("值必须 >= ");
	extern CString g_sLangID_Xrio_InvalidDoublePrecisionValue;  //= _T("Xrio_InvalidDoublePrecisionValue")
	extern CString g_sLangTxt_Xrio_InvalidDoublePrecisionValue; //= _T("无效的双精度值！")
	extern CString g_sLangID_Xrio_InvalidIntValue;              //= _T("Xrio_InvalidIntValue")
	extern CString g_sLangTxt_Xrio_InvalidIntValue;             //= _T("无效的整形值！")
	extern CString g_sLangID_Xrio_LogInfo_ParamDataType;        //= _T("Xrio_LogInfo_ParamDataType")
	extern CString g_sLangTxt_Xrio_LogInfo_ParamDataType;       //= _T("参数数据类型")
	extern CString g_sLangID_Xrio_LogInfo_NamePath;             //= _T("Xrio_LogInfo_NamePath")
	extern CString g_sLangTxt_Xrio_LogInfo_NamePath;            //= _T("名称路径")
	extern CString g_sLangID_Xrio_LogInfo_IDPath;               //= _T("Xrio_LogInfo_IDPath")
	extern CString g_sLangTxt_Xrio_LogInfo_IDPath;              //= _T("ID路径")
	extern CString g_sLangID_Xrio_LogInfo_InvalidParamDataType; //= _T("Xrio_LogInfo_InvalidParamDataType")
	extern CString g_sLangTxt_Xrio_LogInfo_InvalidParamDataType;//= _T("参数含无效数据类型！数据类型改为字符串型！")
	extern CString g_sLangID_Xrio_LogInfo_MinGreaterThanMax;    //= _T("Xrio_LogInfo_MinGreaterThanMax")
	extern CString g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax;   //= _T("最小值大于最大值！")
	extern CString g_sLangID_Xrio_InvalidEnumValue;             //= _T("Xrio_InvalidEnumValue")
	extern CString g_sLangTxt_Xrio_InvalidEnumValue;            //= _T("无效的枚举值！")
	extern CString g_sLangID_Xrio_InvalidBinaryValue;           //= _T("Xrio_InvalidBinaryValue")
	extern CString g_sLangTxt_Xrio_InvalidBinaryValue;          //= _T("无效的二进制值！")