#pragma once

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLanguageResourceIec.h"

class CXLanguageResourcePp_Mms: public CXLanguageResourceIecBase
{
// 构造
public:
	CXLanguageResourcePp_Mms();
	virtual ~CXLanguageResourcePp_Mms();

private:
	CXLanguage m_oXLangRsMms; 

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();

	
public:
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsMmsFile; 
	//装置操作
	extern CString g_sLangID_DeviceOperation;
	extern CString g_sLangTxt_DeviceOperation;
	extern CString g_sLangID_Online;
	extern CString g_sLangTxt_Online;
	extern CString g_sLangID_Disconnect;
	extern CString g_sLangTxt_Disconnect;
	extern CString g_sLangID_DisconnectTip;
	extern CString g_sLangTxt_DisconnectTip;
	extern CString g_sLangID_Return;
	extern CString g_sLangTxt_Return;
	//枚举
	extern CString g_sLangID_Enum;
	extern CString g_sLangTxt_Enum;
	extern CString g_sLangID_ReadNodes;
	extern CString g_sLangTxt_ReadNodes;
	extern CString g_sLangID_ReadNodesTip;
	extern CString g_sLangTxt_ReadNodesTip;
	extern CString g_sLangID_RefreshDirectory;
	extern CString g_sLangTxt_RefreshDirectory;
	extern CString g_sLangID_RefreshDirectoryTip;
	extern CString g_sLangTxt_RefreshDirectoryTip;
	extern CString g_sLangID_Device;
	extern CString g_sLangTxt_Device;
	extern CString g_sLangID_DeviceTip;
	extern CString g_sLangTxt_DeviceTip;
// 	extern CString g_sLangID_LogicDevice;
// 	extern CString g_sLangTxt_LogicDevice;
	extern CString g_sLangID_LogicDeviceTip;
	extern CString g_sLangTxt_LogicDeviceTip;
	extern CString g_sLangID_DataSet;
	extern CString g_sLangTxt_DataSet;
	extern CString g_sLangID_DataSetTip;
	extern CString g_sLangTxt_DataSetTip;
	//数据值
	extern CString g_sLangID_DataValue;
	extern CString g_sLangTxt_DataValue;
	extern CString g_sLangID_ReadData;
	extern CString g_sLangTxt_ReadData;
	extern CString g_sLangID_ReadDataTip;
	extern CString g_sLangTxt_ReadDataTip;
	extern CString g_sLangID_ModifyData;
	extern CString g_sLangTxt_ModifyData;
	//定值区
	extern CString g_sLangID_ReadFixedValueRegion;
	extern CString g_sLangTxt_ReadFixedValueRegion;
	extern CString g_sLangID_ModifyFixedValueRegion;
	extern CString g_sLangTxt_ModifyFixedValueRegion;

	//报告
	extern CString g_sLangID_StartReportTip;
	extern CString g_sLangTxt_StartReportTip;
	extern CString g_sLangID_StopReportTip;
	extern CString g_sLangTxt_StopReportTip;
	extern CString g_sLangID_DebugAdd;
	extern CString g_sLangTxt_DebugAdd;
	extern CString g_sLangID_DebugAddTip;
	extern CString g_sLangTxt_DebugAddTip;
	//文件
	extern CString g_sLangID_ExportModel;
	extern CString g_sLangTxt_ExportModel;
	extern CString g_sLangID_ExportModelTip;
	extern CString g_sLangTxt_ExportModelTip;
	extern CString g_sLangID_ImportModel;
	extern CString g_sLangTxt_ImportModel;
	extern CString g_sLangID_ExportMmsNodes;
	extern CString g_sLangTxt_ExportMmsNodes;
	extern CString g_sLangID_ExportMmsNodesTip;
	extern CString g_sLangTxt_ExportMmsNodesTip;
	//视图
	extern CString g_sLangID_DispMmsErrInfor;
	extern CString g_sLangTxt_DispMmsErrInfor;
	extern CString g_sLangID_DispMmsErrInforTip;
	extern CString g_sLangTxt_DispMmsErrInforTip;
	extern CString g_sLangID_ChangeAndRunArea;
	extern CString g_sLangTxt_ChangeAndRunArea;
	extern CString g_sLangID_PropertyBar;
	extern CString g_sLangTxt_PropertyBar;
	extern CString g_sLangID_DeviceToolbar;
	extern CString g_sLangTxt_DeviceToolbar;
	//启动报告
	extern CString g_sLangID_RptTypeSel;
	extern CString g_sLangTxt_RptTypeSel;
	extern CString g_sLangID_StartSendData;
	extern CString g_sLangTxt_StartSendData;
	extern CString g_sLangID_OptFldsSel;
	extern CString g_sLangTxt_OptFldsSel;
	extern CString g_sLangID_SerialNumber;
	extern CString g_sLangTxt_SerialNumber;
	extern CString g_sLangID_TimeScale;
	extern CString g_sLangTxt_TimeScale;
	extern CString g_sLangID_Reason;
	extern CString g_sLangTxt_Reason;
	extern CString g_sLangID_DataSetName;
	extern CString g_sLangTxt_DataSetName;
	extern CString g_sLangID_DataSetPath;
	extern CString g_sLangTxt_DataSetPath;
	extern CString g_sLangID_BufferOverflowFlag;
	extern CString g_sLangTxt_BufferOverflowFlag;
	extern CString g_sLangID_ItemNum;
	extern CString g_sLangTxt_ItemNum;
	extern CString g_sLangID_ConfigNum;
	extern CString g_sLangTxt_ConfigNum;
	extern CString g_sLangID_SubNumber;
	extern CString g_sLangTxt_SubNumber;
	extern CString g_sLangID_TrgOpsSel;
	extern CString g_sLangTxt_TrgOpsSel;
	extern CString g_sLangID_DataChange;
	extern CString g_sLangTxt_DataChange;
	extern CString g_sLangID_QualityChange;
	extern CString g_sLangTxt_QualityChange;
	extern CString g_sLangID_DataUpgrade;
	extern CString g_sLangTxt_DataUpgrade;
	extern CString g_sLangID_Integrity;
	extern CString g_sLangTxt_Integrity;
	extern CString g_sLangID_GeneralCall;
	extern CString g_sLangTxt_GeneralCall;
	//设置装置的当前运行组
	extern CString g_sLangID_SetCurGrpDevice;
	extern CString g_sLangTxt_SetCurGrpDevice;
	extern CString g_sLangID_FixedValueNum;
	extern CString g_sLangTxt_FixedValueNum;
	//和装置联机
	extern CString g_sLangID_LinkSet;
	extern CString g_sLangTxt_LinkSet;
	extern CString g_sLangID_IP;
	extern CString g_sLangTxt_IP;
	extern CString g_sLangID_EnumRptCtrlBlk;
	extern CString g_sLangTxt_EnumRptCtrlBlk;
	
	//网卡IP设置
	extern CString g_sLangID_NetwCardIpset;
	extern CString g_sLangTxt_NetwCardIpset;
	extern CString g_sLangID_NetwCardSel;
	extern CString g_sLangTxt_NetwCardSel;
	extern CString g_sLangID_IpAddr;
	extern CString g_sLangTxt_IpAddr;
	extern CString g_sLangID_SubNetwMask;
	extern CString g_sLangTxt_SubNetwMask;
	extern CString g_sLangID_AddIp;
	extern CString g_sLangTxt_AddIp;
	extern CString g_sLangID_Ethernet;
	extern CString g_sLangTxt_Ethernet;
	//进度条
	extern CString g_sLangID_InOperation;
	extern CString g_sLangTxt_InOperation;
	extern CString g_sLangID_DataOperation;
	extern CString g_sLangTxt_DataOperation;
	//选择路径
	extern CString g_sLangID_SelPath;
	extern CString g_sLangTxt_SelPath;
	//选择定值区
	extern CString g_sLangID_SelValueZone;
	extern CString g_sLangTxt_SelValueZone;
	extern CString g_sLangID_OperationZone;
	extern CString g_sLangTxt_OperationZone;
	//自动匹配数据集查看
	extern CString g_sLangID_AutoMatchView;
	extern CString g_sLangTxt_AutoMatchView;
	//BrcbCtrlDlg里的输出信息
	extern CString g_sLangID_NotEnum;
	extern CString g_sLangTxt_NotEnum;
	//DlgSelPath里的输出信息
	extern CString g_sLangID_EnterPath;
	extern CString g_sLangTxt_EnterPath;
	//IPSetObj里的输出信息
	extern CString g_sLangID_FileOprtFail;
	extern CString g_sLangTxt_FileOprtFail;
	//LinkSetDlg里的输出信息
	extern CString g_sLangID_RestartAndLink;
	extern CString g_sLangTxt_RestartAndLink;
	//LocalIpSetDlg里的输出信息
	extern CString g_sLangID_ResetIP;
	extern CString g_sLangTxt_ResetIP;
	//MainFrm里的输出信息
	extern CString g_sLangID_MmsPtclPrgm;
	extern CString g_sLangTxt_MmsPtclPrgm;
	extern CString g_sLangID_DeviceListView;
	extern CString g_sLangTxt_DeviceListView;
	extern CString g_sLangID_SelDeviceObj;
	extern CString g_sLangTxt_SelDeviceObj;
	extern CString g_sLangID_NoFixedValueRegion;
	extern CString g_sLangTxt_NoFixedValueRegion;
	extern CString g_sLangID_DeviceMdlFile;
	extern CString g_sLangTxt_DeviceMdlFile;
	extern CString g_sLangID_SendSuccMsg;
	extern CString g_sLangTxt_SendSuccMsg;
	extern CString g_sLangID_SendCommMsg;
	extern CString g_sLangTxt_SendCommMsg;
	extern CString g_sLangID_SendSySMsg;
	extern CString g_sLangTxt_SendSySMsg;
	extern CString g_sLangID_SetFixedValueRegionFail;
	extern CString g_sLangTxt_SetFixedValueRegionFail;
	extern CString g_sLangID_SetFixedValueRegion;
	extern CString g_sLangTxt_SetFixedValueRegion;
	extern CString g_sLangID_EditFixedValueRegionSucc;
	extern CString g_sLangTxt_EditFixedValueRegionSucc;
	extern CString g_sLangID_EditFixedValueRegionFail;
	extern CString g_sLangTxt_EditFixedValueRegionFail;
	extern CString g_sLangID_SolidFixedValueRegionSucc;
	extern CString g_sLangTxt_SolidFixedValueRegionSucc;
	extern CString g_sLangID_SolidFixedValueRegionFail;
	extern CString g_sLangTxt_SolidFixedValueRegionFail;
	extern CString g_sLangID_CtrlWriteSucc;
	extern CString g_sLangTxt_CtrlWriteSucc;
	extern CString g_sLangID_CtrlWriteFail;
	extern CString g_sLangTxt_CtrlWriteFail;
	extern CString g_sLangID_DeviceReturnSucc;
	extern CString g_sLangTxt_DeviceReturnSucc;
	extern CString g_sLangID_DeviceReturnFail;
	extern CString g_sLangTxt_DeviceReturnFail;
	extern CString g_sLangID_AllCommandExecuted;
	extern CString g_sLangTxt_AllCommandExecuted;
	//MmsDeviceTreeCtrl里的输出信息
	extern CString g_sLangID_MmsNodes;
	extern CString g_sLangTxt_MmsNodes;
	extern CString g_sLangID_RecdWaveFile;
	extern CString g_sLangTxt_RecdWaveFile;
	extern CString g_sLangID_LogRecord;
	extern CString g_sLangTxt_LogRecord;
	extern CString g_sLangID_TooMuchActualDevice;
	extern CString g_sLangTxt_TooMuchActualDevice;
	//NodeView里的输出信息
	extern CString g_sLangID_Attributes;
	extern CString g_sLangTxt_Attributes;
	extern CString g_sLangID_UnableloadBitmap;
	extern CString g_sLangTxt_UnableloadBitmap;
	//OutputWnd里的输出信息
	extern CString g_sLangID_Log;
	extern CString g_sLangTxt_Log;
	extern CString g_sLangID_ReportD;
	extern CString g_sLangTxt_ReportD;
	extern CString g_sLangID_SoeReportD;
	extern CString g_sLangTxt_SoeReportD;
	extern CString g_sLangID_Date;
	extern CString g_sLangTxt_Date;
	extern CString g_sLangID_TimeDiffer;
	extern CString g_sLangTxt_TimeDiffer;
	extern CString g_sLangID_DetailedInfor;
	extern CString g_sLangTxt_DetailedInfor;
	//PpMmsEngine的输出信息
	extern CString g_sLangID_InitSocketFailed;
	extern CString g_sLangTxt_InitSocketFailed;
	extern CString g_sLangID_WizardGeneratedApp;
	extern CString g_sLangTxt_WizardGeneratedApp;
	extern CString g_sLangID_Unknown;
	extern CString g_sLangTxt_Unknown;
	extern CString g_sLangID_ReadDeviceDataComplete;
	extern CString g_sLangTxt_ReadDeviceDataComplete;
	extern CString g_sLangID_Monitor;
	extern CString g_sLangTxt_Monitor;
	extern CString g_sLangID_NotEnumDataSet;
	extern CString g_sLangTxt_NotEnumDataSet;
	extern CString g_sLangID_TotalStep1;
	extern CString g_sLangTxt_TotalStep1;
	extern CString g_sLangID_TotalStep2;
	extern CString g_sLangTxt_TotalStep2;
	extern CString g_sLangID_Links;
	extern CString g_sLangTxt_Links;
	extern CString g_sLangID_CommProcessing;
	extern CString g_sLangTxt_CommProcessing;
	extern CString g_sLangID_ProgmInilFail;
	extern CString g_sLangTxt_ProgmInilFail;
	extern CString g_sLangID_ProgmRun;
	extern CString g_sLangTxt_ProgmRun;
	//PpMmsEngineView里的输出信息
	extern CString g_sLangID_DaXiao;
	extern CString g_sLangTxt_DaXiao;
	//ZoneSelDlg里的输出信息
	extern CString g_sLangID_RegionD;
	extern CString g_sLangTxt_RegionD;

	extern CString g_sLangID_Menu_32777;
	extern CString g_sLangID_Menu_32778;
	extern CString g_sLangID_Menu_32794;
	extern CString g_sLangID_Menu_32795;
	extern CString g_sLangID_Menu_32797;
	extern CString g_sLangID_Menu_32804;
	extern CString g_sLangID_Menu_32796;
	extern CString g_sLangID_Menu_32786;
	extern CString g_sLangID_Menu_32798;
	extern CString g_sLangTxt_Menu_32777;//"启动报告(&B)	Ctrl+B"
	extern CString g_sLangTxt_Menu_32778;//"停止报告(&P)	Ctrl+P"
	extern CString g_sLangTxt_Menu_32794;//调试模式(&D)
	extern CString g_sLangTxt_Menu_32795;//显示调试信息(&V)
	extern CString g_sLangTxt_Menu_32797;//调试-通讯失败(&F)
	extern CString g_sLangTxt_Menu_32804;//添加到SOE报告
	extern CString g_sLangTxt_Menu_32796;//单一设备模式(&S)
	extern CString g_sLangTxt_Menu_32786;//读测量值使用报告数据
	extern CString g_sLangTxt_Menu_32798;//复归命令只清空报告数据

	extern CString g_sLangID_HadNoDataNeedEdit;// _T("sHadNoDataNeedEdit");
	extern CString g_sLangTxt_HadNoDataNeedEdit;// _T("没有需要修改的数据");
	extern CString g_sLangID_ReadDeviceDirSucc;// _T("ReadDeviceDirSuccs");
	extern CString g_sLangTxt_ReadDeviceDirSucc;// _T("枚举装置目录成功.");
	extern CString g_sLangID_ReadDeviceDirFail;// _T("sReadDeviceDirFail");
	extern CString g_sLangTxt_ReadDeviceDirFail;// _T("枚举装置目录失败.");
	extern CString g_sLangID_SetZoneFail;// _T("sSetZoneFail");
	extern CString g_sLangTxt_SetZoneFail;// _T("设置当前定值运行区号失败!");
	extern CString g_sLangID_ConnectSucc;// _T("sConnectSucc");
	extern CString g_sLangTxt_ConnectSucc;// _T("和装置联机成功.");
	extern CString g_sLangID_ConnectFail;// _T("sConnectFail");
	extern CString g_sLangTxt_ConnectFail;// _T("和装置联机失败【Error】.");
	extern CString g_sLangID_DisConnectSucc;// _T("sDisConnectSucc");
	extern CString g_sLangTxt_DisConnectSucc;// _T("和装置断开连接成功.");
	extern CString g_sLangID_DisConnectFail;// _T("sDisConnectFail");
	extern CString g_sLangTxt_DisConnectFail;// _T("和装置断开连接失败【Error】.");
	extern CString g_sLangID_RdDatasetSucc;// _T("sRdDatasetSucc");
	extern CString g_sLangTxt_RdDatasetSucc;// _T("读数据集成功.");
	extern CString g_sLangID_RdDatasetFail;// _T("sRdDatasetFail");
	extern CString g_sLangTxt_RdDatasetFail;// _T("读数据集失败【Error】.");
	extern CString g_sLangID_ReadRecorDirFail;// _T("sReadRecorDirFail");
	extern CString g_sLangTxt_ReadRecorDirFail;// _T("读录波文件目录失败.");
	extern CString g_sLangID_ReadRecordDirSucc;// _T("sReadRecordDirSucc");
	extern CString g_sLangTxt_ReadRecordDirSucc;// _T("读录波文件目录成功.");
	extern CString g_sLangID_ReadRecordFileSucc;// _T("sReadRecordFileSucc");
	extern CString g_sLangTxt_ReadRecordFileSucc;// _T("读录波文件成功.");
	extern CString g_sLangID_ReadRecordFileFail;// _T("sReadRecordFileFail");
	extern CString g_sLangTxt_ReadRecordFileFail;// _T("读录波文件失败.");
	extern CString g_sLangID_WriteDataFail;// _T("sWriteDataFail");
	extern CString g_sLangTxt_WriteDataFail;// _T("写数据失败【Error】.");
	extern CString g_sLangID_WriteDataSucc;// _T("sWriteDataSucc");
	extern CString g_sLangTxt_WriteDataSucc;// _T("写数据成功.");
	extern CString g_sLangID_StartRptFail;// _T("sStartRptFail");
	extern CString g_sLangTxt_StartRptFail;// _T("启动报告失败【Error】.");
	extern CString g_sLangID_StartRptSucc;// _T("sStartRptSucc");
	extern CString g_sLangTxt_StartRptSucc;// _T("启动报告成功.");
	extern CString g_sLangID_StopRptFail;// _T("sStopRptFail");
	extern CString g_sLangTxt_StopRptFail;// _T("停止报告失败【Error】.");
	extern CString g_sLangID_StopRptSucc;// _T("sStopRptSucc");
	extern CString g_sLangTxt_StopRptSucc;// _T("停止报告成功.");
	extern CString g_sLangID_ReadZoneFail;// _T("sReadZoneFail");
	extern CString g_sLangTxt_ReadZoneFail;// _T("获取当前定值运行区号失败.");
	extern CString g_sLangID_NetConnect;// _T("sNetConnect");
	extern CString g_sLangTxt_NetConnect;// _T("网络连接正常.");
	extern CString g_sLangID_NetDisConnect;// _T("sNetDisConnect");
	extern CString g_sLangTxt_NetDisConnect;// _T("网络连接断开.");

	extern CString g_sLangID_Menu_57634;
	extern CString g_sLangTxt_Menu_57634;
	extern CString g_sLangID_Menu_57632;
	extern CString g_sLangTxt_Menu_57632;
	extern CString g_sLangID_Menu_149;
	extern CString g_sLangTxt_Menu_149;

	extern CString g_sLangID_WriteDataAfterWait;
	extern CString g_sLangTxt_WriteDataAfterWait;
	extern CString g_sLangID_DvRcvOverTime;
	extern CString g_sLangTxt_DvRcvOverTime;
	extern CString g_sLangID_HasNoRptCtrl;
	extern CString g_sLangTxt_HasNoRptCtrl;
	extern CString g_sLangID_RptCtrlHasStart;
	extern CString g_sLangTxt_RptCtrlHasStart;
	extern CString g_sLangID_StartRptCtrlFinish;
	extern CString g_sLangTxt_StartRptCtrlFinish;
	extern CString g_sLangID_StartRptCtrlFail;
	extern CString g_sLangTxt_StartRptCtrlFail;
	extern CString g_sLangID_HasNoNet;
	extern CString g_sLangTxt_HasNoNet;
	extern CString g_sLangID_SetEdtZnFail;
	extern CString g_sLangTxt_SetEdtZnFail;
	extern CString g_sLangID_SetEdtZnRd;
	extern CString g_sLangTxt_SetEdtZnRd;
	extern CString g_sLangID_IndexAndTotal;
	extern CString g_sLangTxt_IndexAndTotal;
	extern CString g_sLangID_WritDataFail;
	extern CString g_sLangTxt_WritDataFail;
	extern CString g_sLangID_WritDataSucc;
	extern CString g_sLangTxt_WritDataSucc;
	extern CString g_sLangID_WritDataPrgs;
	extern CString g_sLangTxt_WritDataPrgs;
	extern CString g_sLangID_BfExecNext;
	extern CString g_sLangTxt_BfExecNext;
	extern CString g_sLangID_EditDataFail;
	extern CString g_sLangTxt_EditDataFail;
	extern CString g_sLangID_GetNexLdZn;
	extern CString g_sLangTxt_GetNexLdZn;
	extern CString g_sLangID_NoLdHasZn;
	extern CString g_sLangTxt_NoLdHasZn;
	extern CString g_sLangID_RdSetZnsFail;
	extern CString g_sLangTxt_RdSetZnsFail;
	extern CString g_sLangID_RdCurSetZnsFail;
	extern CString g_sLangTxt_RdCurSetZnsFail;
	extern CString g_sLangID_SetCurSetZnFail;
	extern CString g_sLangTxt_SetCurSetZnFail;
	extern CString g_sLangID_SetCurSetZnSucc;
	extern CString g_sLangTxt_SetCurSetZnSucc;
	extern CString g_sLangID_LdHasNoZn;
	extern CString g_sLangTxt_LdHasNoZn;
	extern CString g_sLangID_SetCurEdtZnFail;
	extern CString g_sLangTxt_SetCurEdtZnFail;
	extern CString g_sLangID_SetCurEdtZnSucc;
	extern CString g_sLangTxt_SetCurEdtZnSucc;
	extern CString g_sLangID_SolidZnFail;
	extern CString g_sLangTxt_SolidZnFail;
	extern CString g_sLangID_SolidZnSucc;
	extern CString g_sLangTxt_SolidZnSucc;
	extern CString g_sLangID_SelEnaFail;
	extern CString g_sLangTxt_SelEnaFail;
	extern CString g_sLangID_SelEnaSucc;
	extern CString g_sLangTxt_SelEnaSucc;
	extern CString g_sLangID_AfterSelEna;
	extern CString g_sLangTxt_AfterSelEna;
	extern CString g_sLangID_ExecEnaFail;
	extern CString g_sLangTxt_ExecEnaFail;
	extern CString g_sLangID_ExecEnaSucc;
	extern CString g_sLangTxt_ExecEnaSucc;
	extern CString g_sLangID_EnaOptrTime;
	extern CString g_sLangTxt_EnaOptrTime;
	extern CString g_sLangID_WriteEnaParaErr;
	extern CString g_sLangTxt_WriteEnaParaErr;
	extern CString g_sLangID_EnaOptrFail;
	extern CString g_sLangTxt_EnaOptrFail;
	extern CString g_sLangID_DvResetFail;
	extern CString g_sLangTxt_DvResetFail;
	extern CString g_sLangID_DvResetFailEx;
	extern CString g_sLangTxt_DvResetFailEx;

	extern CString g_sLangTxt_FuncID_Connect;//_T("sFuncID_Connect");
	extern CString g_sLangID_FuncID_Connect;//_T("联机");
	extern CString g_sLangTxt_FuncID_DisConnect;//_T("s_FuncID_DisConnect");
	extern CString g_sLangID_FuncID__FuncID_DisConnect;//_T("与设备断开连接");
	extern CString g_sLangTxt_FuncID_WriteData;//_T("sFuncID_WriteData");
	extern CString g_sLangID_FuncID_WriteData;//_T("写数据");
	extern CString g_sLangTxt_FuncID_ReadData;//_T("sFuncID_ReadData");
	extern CString g_sLangID_FuncID_ReadData;//_T("读数据");
	extern CString g_sLangTxt_FuncID_StartRpt;//_T("sFuncID_StartRpt");
	extern CString g_sLangID_FuncID_StartRpt;//_T("启动报告");
	extern CString g_sLangTxt_FuncID_StopRpt;//_T("sFuncID_StopRpt");
	extern CString g_sLangID_FuncID_StopRpt;//_T("停止报告");
	extern CString g_sLangTxt_FuncID_GetRunZn;//_T("sFuncID_GetRunZn");
	extern CString g_sLangID_FuncID_GetRunZn;//_T("获取当前运行区");
	extern CString g_sLangTxt_FuncID_SetRunZn;//_T("sFuncID_SetRunZn");
	extern CString g_sLangID_FuncID_SetRunZn;//_T("设置当前运行区");
	extern CString g_sLangTxt_FuncID_EnumDvDir;//_T("sFuncID_EnumDvDir");
	extern CString g_sLangID_FuncID_EnumDvDir;//_T("枚举装置目录");
	extern CString g_sLangTxt_FuncID_ChangeEditZn;//_T("sFuncID_ChangeEditZn");
	extern CString g_sLangID_FuncID_ChangeEditZn;//_T("切换编辑定值区");
	extern CString g_sLangTxt_FuncID_SolidEditZn;//_T("sFuncID_SolidEditZn");
	extern CString g_sLangID_FuncID_SolidEditZn;//_T("固化编辑定值区");


	extern CString g_sLangID_CreatMmsComm;//_T("sCreatMmsComm");
	extern CString g_sLangTxt_CreatMmsComm;//_T("创建为MMS通讯命令模式【%s】");
	extern CString g_sLangID_ReachMax;//_T("sReachMax");
	extern CString g_sLangTxt_ReachMax;//_T("可创建的设备数已经达到最上限，不能创建【%s】设备");
	extern CString g_sLangID_ReleasMmsComm;//_T("sReleasMmsComm");
	extern CString g_sLangTxt_ReleasMmsComm;//_T("释放MMS通讯命令模式【%s】");

	extern CString g_sLangID_CurrentActSet;//_T("sCurrentActSet");
	extern CString g_sLangTxt_CurrentActSet;//_T("当前活动定值区");
	extern CString g_sLangID_SettingTotalNo;//_T("sSettingTotalNo");
	extern CString g_sLangTxt_SettingTotalNo;//_T("定值区总数");
	extern CString g_sLangID_CommandTotalTime;//_T("sCommandTotalTime");
	extern CString g_sLangTxt_CommandTotalTime;//_T("命令总时间");
	extern CString g_sLangID_CommandExecuTime;//_T("sCommandExecuTime");
	extern CString g_sLangTxt_CommandExecuTime;//_T("命令执行时间");
	extern CString g_sLangID_CommandChoseTime;//_T("sCCommandChoseTime");
	extern CString g_sLangTxt_CommandChoseTime;//_T("命令选择时间");
	extern CString g_sLangID_CommandExecuMess;//_T("sCommandExecuMess");
	extern CString g_sLangTxt_CommandExecuMess;//_T("命令执行信息");
	extern CString g_sLangID_CommandChoseMess;//_T("sCommandChoseMess");
	extern CString g_sLangTxt_CommandChoseMess;//_T("命令选择信息");
	extern CString g_sLangID_WrongMess;//_T("sWrongMess");
	extern CString g_sLangTxt_WrongMess;//_T("错误信息");
	extern CString g_sLangID_RecordPath;//_T("sRecordPath");
	extern CString g_sLangTxt_RecordPath;//_T("录波路径");
	extern CString g_sLangID_EnaChangeTime;//_T("sEnaChangeTime");
	extern CString g_sLangTxt_EnaChangeTime;//_T("压板修改间隔时间");
	extern CString g_sLangID_EnaChoseTime;//_T("sEnaChoseTime");
	extern CString g_sLangTxt_EnaChoseTime;//_T("压板选择执行间隔时间");
	extern CString g_sLangID_MonitErrorTime;//_T("sMonitErrorTime");
	extern CString g_sLangTxt_MonitErrorTime;//_T("监视错误信息");
	extern CString g_sLangID_BeforEnaRead;//_T("sBeforEnaRead");
	extern CString g_sLangTxt_BeforEnaRead;//_T("投退压板前读状态");
	extern CString g_sLangID_BeforEnaReadTime;//_T("sBeforEnaReadTime");
	extern CString g_sLangTxt_BeforEnaReadTime;//_T("投退压板前读状态后延时");

	extern CString g_sLangID_WritDataMess;//_T("sWritDataMess");
	extern CString g_sLangTxt_WritDataMess;//_T("写数据信息");
	extern CString g_sLangID_SetEdtTime;//_T("sSetEdtTime");
	extern CString g_sLangTxt_SetEdtTime;//_T("设置编辑区时间");
	extern CString g_sLangID_SetActTime;//_T("sSetActTime");
	extern CString g_sLangTxt_SetActTime;//_T("设置活动区时间");
	extern CString g_sLangID_SetEdtMess;//_T("sSetEdtMess");
	extern CString g_sLangTxt_SetEdtMess;//_T("设置编辑区信息");
	extern CString g_sLangID_SetActMess;//_T("sSetActMess");
	extern CString g_sLangTxt_SetActMess;//_T("设置活动区信息");
	extern CString g_sLangID_TestConnSta;//_T("sTestConnSta");
	extern CString g_sLangTxt_TestConnSta;//_T("测试连接状态");

	extern CString g_sLangID_ExecConnCommand;//_T("sExecConnCommand");
	extern CString g_sLangTxt_ExecConnCommand;//_T("执行外部通讯命令【%s】：ACSIDevice=%d  LdIndex=%d  DatasetIndex=%d");
	extern CString g_sLangID_DatasetPathError;//_T("sDatasetPathError");
	extern CString g_sLangTxt_DatasetPathError;//_T("数据集路径【%s】不正确");
	extern CString g_sLangID_Ena;//_T("sEna");
	extern CString g_sLangTxt_Ena;//_T("压板");
	extern CString g_sLangID_RemoteCtl;//_T("sRemoteCtl");
	extern CString g_sLangTxt_RemoteCtl;//_T("遥控");
	extern CString g_sLangID_UnRegRepDataSet;//_T("sUnRegRepDataSet");
	extern CString g_sLangTxt_UnRegRepDataSet;//_T("unregisterreport:数据集：%s");
	extern CString g_sLangID_SwitchSet;//_T("sSwitchSet");
	extern CString g_sLangTxt_SwitchSet;//_T("切换定值区：%d");
	extern CString g_sLangID_OnlyReadProp;//_T("sOnlyReadProp");
	extern CString g_sLangTxt_OnlyReadProp;//_T("属性【%s】为只读属性");
	extern CString g_sLangID_NoNeedCorect;//_T("sNoNeedCorect");
	extern CString g_sLangTxt_NoNeedCorect;//_T("没有需要修改的%s【%s】");
	extern CString g_sLangID_RegRepDataSetMiss;//_T("sRegRepDataSetMiss");
	extern CString g_sLangTxt_RegRepDataSetMiss;//_T("registerreport:数据集：%s 不存在");
	extern CString g_sLangID_StopRepDataSetMiss;//_T("sStopRepDataSetMiss");
	extern CString g_sLangTxt_StopRepDataSetMiss;//_T("stopreport:数据集：%s 不存在");

	extern CString g_sLangID_SendOverMesNotWin;//_T("sSendOverMesNotWin");
	extern CString g_sLangTxt_SendOverMesNotWin;//_T("发送测试完成消息 【%08x】 不是窗口");
	extern CString g_sLangID_SendOverMes;//_T("sSendOverMes");
	extern CString g_sLangTxt_SendOverMes;//_T("发送测试完成消息 WND=【%08x】 MSG=【%08x】");
	extern CString g_sLangID_DataNotExist;//_T("sDataNotExist");
	extern CString g_sLangTxt_DataNotExist;//_T("数据【%s】【%s】不存在");
	extern CString g_sLangID_RegistDataFail;//_T("sRegistDataFail");
	extern CString g_sLangTxt_RegistDataFail;//_T("RegisterDataChangedMsg(%s)失败");
	extern CString g_sLangID_RegistDataSuc ;//_T("sRegistDataSuc");
	extern CString g_sLangTxt_RegistDataSuc;//_T("RegisterDataChangedMsg(%s)成功");
	extern CString g_sLangID_CmdMsgFailWin;//_T("sCmdMsgFailWin");
	extern CString g_sLangTxt_CmdMsgFailWin;//_T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)失败：目标窗口不存在");
	extern CString g_sLangID_MapNotExist;//_T("sMapNotExist");
	extern CString g_sLangTxt_MapNotExist;//_T("数据集映射关系【%s】=【%s$%s】不存在");
	extern CString g_sLangID_ZnNumAndRunZn;
	extern CString g_sLangTxt_ZnNumAndRunZn;




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
