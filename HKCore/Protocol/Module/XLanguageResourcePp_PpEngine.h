//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "XLanguageResourcePp.h"


class CXLanguageResourcePp_PpEngine : public CXLanguageResourcePpBase
{
public:
	CXLanguageResourcePp_PpEngine();
	virtual ~CXLanguageResourcePp_PpEngine();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsPp_PpEngine;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();
};

	
	extern CString  g_strXLangRsPp_PpEngineFile;
	extern CString g_sLangID_NotSelDev;       //没有选择设备
	extern CString g_sLangTxt_NotSelDev;
	extern CString g_sLangID_PrtcProHome;      //规约引擎操作主页
	extern CString g_sLangTxt_PrtcProHome;
	extern CString g_sLangID_DevOpera;      //设备操作
	extern CString g_sLangTxt_DevOpera;
	extern CString g_sLangID_NewAdd;          //新增
	extern CString g_sLangTxt_NewAdd;
	extern CString g_sLangID_Connection;       //连接
	extern CString g_sLangTxt_Connection;
	extern CString g_sLangID_DisConnection;       //断开连接
	extern CString g_sLangTxt_DisConnection;
	extern CString g_sLangID_Uninstall;       //卸载
	extern CString g_sLangTxt_Uninstall;
	extern CString g_sLangID_PointTableEdit;       //点表编辑
	extern CString g_sLangTxt_PointTableEdit;
	extern CString g_sLangID_CommuntSet;       //通讯设置
	extern CString g_sLangTxt_CommuntSet;
	extern CString g_sLangID_CommunProcess;       //通讯过程
	extern CString g_sLangTxt_CommunProcess;
	extern CString g_sLangID_OperationProcess;       //运行过程
	extern CString g_sLangTxt_OperationProcess;
	extern CString g_sLangID_ViewOprthPrcs;       //查看运行过程
	extern CString g_sLangTxt_ViewOprthPrcs;
	extern CString g_sLangID_StopProcess;       //终止过程
	extern CString g_sLangTxt_StopProcess;
	extern CString g_sLangID_ClearSOE;       //清空SOE
	extern CString g_sLangTxt_ClearSOE;
	extern CString g_sLangID_ClearMessage;       //清除报文
	extern CString g_sLangTxt_ClearMessage;
	extern CString g_sLangID_DebugMode;       //调试模式
	extern CString g_sLangTxt_DebugMode;
	extern CString g_sLangID_Report;       //报告
	extern CString g_sLangTxt_Report;
	extern CString g_sLangID_StartReport;       //启动报告
	extern CString g_sLangTxt_StartReport;
	extern CString g_sLangID_StopReport;       //停止报告
	extern CString g_sLangTxt_StopReport;
	extern CString g_sLangID_DevToolBar;       //设备工具栏
	extern CString g_sLangTxt_DevToolBar;
	extern CString g_sLangID_DevToolBarTip;       //显示或隐藏设备工具栏\n切换设备工具栏
	extern CString g_sLangTxt_DevToolBarTip;
	extern CString g_sLangID_OutputWnd;       //输出窗口
	extern CString g_sLangTxt_OutputWnd;
	extern CString g_sLangID_OutputWndTip;       //显示或隐藏输出窗口\n切换输出窗口
	extern CString g_sLangTxt_OutputWndTip;
	extern CString g_sLangID_MonitorBindError;       //监视绑定错误
	extern CString g_sLangTxt_MonitorBindError;
	extern CString g_sLangID_MonitorMessageInf;       //监视报文信息
	extern CString g_sLangTxt_MonitorMessageInf;
	extern CString g_sLangID_MonitorMessage;       //监视报文
	extern CString g_sLangTxt_MonitorMessage;

	extern CString g_sLangID_ClipboardData;       //剪切板数据
	extern CString g_sLangTxt_ClipboardData;
// 	extern CString g_sLangID_DataList;       //数据列表
// 	extern CString g_sLangTxt_DataList;
	extern CString g_sLangID_ReadClipboard;       //读取剪切板
	extern CString g_sLangTxt_ReadClipboard;
	extern CString g_sLangID_AddToList;       //添加到列表
	extern CString g_sLangTxt_AddToList;
	extern CString g_sLangID_InsertList;       //插入到列表尾
	extern CString g_sLangTxt_InsertList;
	extern CString g_sLangID_ClearList;       //清空列表
	extern CString g_sLangTxt_ClearList;
	extern CString g_sLangID_InsertIndex;       //插入起始索引号
	extern CString g_sLangTxt_InsertIndex;
	extern CString g_sLangID_PointDataPaste;       //点表数据粘贴
	extern CString g_sLangTxt_PointDataPaste;
	extern CString g_sLangID_NewDev;       //新建设备
	extern CString g_sLangTxt_NewDev;
	extern CString g_sLangID_PointListFile;       //点表文件
	extern CString g_sLangTxt_PointListFile;
	extern CString g_sLangID_ModifyClose;       //修改关闭
	extern CString g_sLangTxt_ModifyClose;

	extern CString g_sLangID_FormulaType;       //公式种类
	extern CString g_sLangTxt_FormulaType;
	extern CString g_sLangID_FormulaEdit;       //公式编辑
	extern CString g_sLangTxt_FormulaEdit;
	extern CString g_sLangID_SelType;       //选择分类
	extern CString g_sLangTxt_SelType;
	extern CString g_sLangID_FormulaEditD;       //公式编辑对话框
	extern CString g_sLangTxt_FormulaEditD;

	extern CString g_sLangID_MonitorPrtcMessage;       //监视规约报文
	extern CString g_sLangTxt_MonitorPrtcMessage;
	extern CString g_sLangID_MonitorSOE;       //监视SOE
	extern CString g_sLangTxt_MonitorSOE;
	extern CString g_sLangID_Empty;       //清空
	extern CString g_sLangTxt_Empty;
	extern CString g_sLangID_CommunMonitor;       //通讯监视
	extern CString g_sLangTxt_CommunMonitor;
	extern CString g_sLangID_SelCommunProcess;       //选择通讯过程
	extern CString g_sLangTxt_SelCommunProcess;
	extern CString g_sLangID_SelProcessSet;       //选择过程数据接口设置
	extern CString g_sLangTxt_SelProcessSet;

	extern CString g_sLangID_Vaule;       //数值
	extern CString g_sLangTxt_Vaule;
	extern CString g_sLangID_PrtcMonitor;       //规约监视
	extern CString g_sLangTxt_PrtcMonitor;
	extern CString g_sLangID_CannotAddView;       //无法加载位图: %x\n
	extern CString g_sLangTxt_CannotAddView;
	extern CString g_sLangID_NewFolder2;       //新建文件夹...
	extern CString g_sLangTxt_NewFolder2;
	extern CString g_sLangID_AddMemberFctn;       //添加成员函数...
	extern CString g_sLangTxt_AddMemberFctn;
	extern CString g_sLangID_RptPathUnExist;       //报告路径“%s”不存在
	extern CString g_sLangTxt_RptPathUnExist;
	extern CString g_sLangID_DataPathUnExist;       //数据集路径“%s”不存在
	extern CString g_sLangTxt_DataPathUnExist;
	extern CString g_sLangID_DiffError;       //当前过程【%s】；结束的过程【%s】，两者不同，发生错误
	extern CString g_sLangTxt_DiffError;
	extern CString g_sLangID_SendTestInf;       //===============发送测试完成消息[%s] WND=【%08x】 MSG=【%08x】
	extern CString g_sLangTxt_SendTestInf;
	extern CString g_sLangID_SendSystemMsg;       //发送系统消息 WND=【%08x】 MSG=【%08x】(%d, %d)
	extern CString g_sLangTxt_SendSystemMsg;
	extern CString g_sLangID_ColctnClcltFmla;       //采集计算公式
	extern CString g_sLangTxt_ColctnClcltFmla;
	extern CString g_sLangID_SendClcltFmla;       //发送计算公式
	extern CString g_sLangTxt_SendClcltFmla;

    /*  以下几个，移动到基类CXLanguageResourceBase。2024-1-4  shaolei
	extern CString g_sLangID_Voltage;       //电压
	extern CString g_sLangTxt_Voltage;
	extern CString g_sLangID_Current;       //电流
	extern CString g_sLangTxt_Current;
	extern CString g_sLangID_ActivePower;       //有功功率
	extern CString g_sLangTxt_ActivePower;
	extern CString g_sLangID_ReactivePower;       //无功功率
	extern CString g_sLangTxt_ReactivePower;
	extern CString g_sLangID_Frequency;       //频率
	extern CString g_sLangTxt_Frequency;
	extern CString g_sLangID_PowerFactor;       //功率因数
	extern CString g_sLangTxt_PowerFactor;
    */

	extern CString g_sLangID_Menu_32817;      
	extern CString g_sLangTxt_Menu_32817;
	extern CString g_sLangID_Menu_32818;      
	extern CString g_sLangTxt_Menu_32818;
	extern CString g_sLangID_Menu_32819;      
	extern CString g_sLangTxt_Menu_32819;
	extern CString g_sLangID_DeviceDataView;      
	extern CString g_sLangTxt_DeviceDataView;
