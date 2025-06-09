
#include "stdafx.h"
#include "XLanguageResourcePp_Mms.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView
CString  g_strXLangRsMmsFile = _T("PpMmsEngine");

CXLanguageResourcePp_Mms::CXLanguageResourcePp_Mms()
{
	m_pXLangRsExe = &m_oXLangRsMms;
	m_oXLangRsMms.m_strID = g_strXLangRsMmsFile;
	m_oXLangRsMms.m_strName = g_strXLangRsMmsFile;
}

CXLanguageResourcePp_Mms::~CXLanguageResourcePp_Mms()
{
	m_oXLangRsMms.RemoveAll();
}
CXLangItem* CXLanguageResourcePp_Mms::rs_AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString);

	m_oXLangRsMms.AddTail(p); 

	return p;
}


void CXLanguageResourcePp_Mms::InitLangRsByFile()
{
	CXLanguageResourceIecBase::InitLangRsByFile();

	InitLangRsByFileEx(&m_oXLangRsMms, g_strXLangRsMmsFile);
}


void CXLanguageResourcePp_Mms::RegisterLanguageResource()
{
	CXLanguageResourceIecBase::RegisterLanguageResource();
//装置操作
	rs_AddString(g_sLangID_DeviceOperation,&g_sLangTxt_DeviceOperation);
	rs_AddString(g_sLangID_Online,&g_sLangTxt_Online);
	rs_AddString(g_sLangID_Disconnect,&g_sLangTxt_Disconnect);
	rs_AddString(g_sLangID_DisconnectTip,&g_sLangTxt_DisconnectTip);
	rs_AddString(g_sLangID_Return,&g_sLangTxt_Return);
//视图
	rs_AddString(g_sLangID_DispMmsErrInfor,&g_sLangTxt_DispMmsErrInfor);
	rs_AddString(g_sLangID_DispMmsErrInforTip,&g_sLangTxt_DispMmsErrInforTip);
	rs_AddString(g_sLangID_ChangeAndRunArea,&g_sLangTxt_ChangeAndRunArea);
	rs_AddString(g_sLangID_PropertyBar,&g_sLangTxt_PropertyBar);
	rs_AddString(g_sLangID_DeviceToolbar,&g_sLangTxt_DeviceToolbar);

//枚举
	rs_AddString(g_sLangID_Enum,&g_sLangTxt_Enum);
	rs_AddString(g_sLangID_ReadNodes,&g_sLangTxt_ReadNodes);
	rs_AddString(g_sLangID_ReadNodesTip,&g_sLangTxt_ReadNodesTip);
	rs_AddString(g_sLangID_RefreshDirectory,&g_sLangTxt_RefreshDirectory);
	rs_AddString(g_sLangID_RefreshDirectoryTip,&g_sLangTxt_RefreshDirectoryTip);
	rs_AddString(g_sLangID_Device,&g_sLangTxt_Device);
	rs_AddString(g_sLangID_DeviceTip,&g_sLangTxt_DeviceTip);
	//rs_AddString(g_sLangID_LogicDevice,&g_sLangTxt_LogicDevice);
	rs_AddString(g_sLangID_LogicDeviceTip,&g_sLangTxt_LogicDeviceTip);
	rs_AddString(g_sLangID_DataSetTip,&g_sLangTxt_DataSetTip);

//数据值
	rs_AddString(g_sLangID_DataValue,&g_sLangTxt_DataValue);
	rs_AddString(g_sLangID_ReadData,&g_sLangTxt_ReadData);
	rs_AddString(g_sLangID_ReadDataTip,&g_sLangTxt_ReadDataTip);
	rs_AddString(g_sLangID_ModifyData,&g_sLangTxt_ModifyData);
//定值区
	rs_AddString(g_sLangID_ReadFixedValueRegion,&g_sLangTxt_ReadFixedValueRegion);
	rs_AddString(g_sLangID_ModifyFixedValueRegion,&g_sLangTxt_ModifyFixedValueRegion);
//报告
	rs_AddString(g_sLangID_StartReportTip,&g_sLangTxt_StartReportTip);
	rs_AddString(g_sLangID_StopReportTip,&g_sLangTxt_StopReportTip);
	rs_AddString(g_sLangID_DebugAdd,&g_sLangTxt_DebugAdd);
	rs_AddString(g_sLangID_DebugAddTip,&g_sLangTxt_DebugAddTip);
//文件
	rs_AddString(g_sLangID_ExportModel,&g_sLangTxt_ExportModel);
	rs_AddString(g_sLangID_ExportModelTip,&g_sLangTxt_ExportModelTip);
	rs_AddString(g_sLangID_ImportModel,&g_sLangTxt_ImportModel);
	rs_AddString(g_sLangID_ExportMmsNodes,&g_sLangTxt_ExportMmsNodes);
	rs_AddString(g_sLangID_ExportMmsNodesTip,&g_sLangTxt_ExportMmsNodesTip);
//启动报告
	rs_AddString(g_sLangID_RptTypeSel,&g_sLangTxt_RptTypeSel);
	rs_AddString(g_sLangID_StartSendData,&g_sLangTxt_StartSendData);
	rs_AddString(g_sLangID_OptFldsSel,&g_sLangTxt_OptFldsSel);
	rs_AddString(g_sLangID_SerialNumber,&g_sLangTxt_SerialNumber);
	rs_AddString(g_sLangID_TimeScale,&g_sLangTxt_TimeScale);
	rs_AddString(g_sLangID_Reason,&g_sLangTxt_Reason);
	rs_AddString(g_sLangID_DataSetName,&g_sLangTxt_DataSetName);
	rs_AddString(g_sLangID_DataSetPath,&g_sLangTxt_DataSetPath);
	rs_AddString(g_sLangID_BufferOverflowFlag,&g_sLangTxt_BufferOverflowFlag);
	rs_AddString(g_sLangID_ItemNum,&g_sLangTxt_ItemNum);
	rs_AddString(g_sLangID_ConfigNum,&g_sLangTxt_ConfigNum);
	rs_AddString(g_sLangID_SubNumber,&g_sLangTxt_SubNumber);
	rs_AddString(g_sLangID_TrgOpsSel,&g_sLangTxt_TrgOpsSel);
	rs_AddString(g_sLangID_DataChange,&g_sLangTxt_DataChange);
	rs_AddString(g_sLangID_QualityChange,&g_sLangTxt_QualityChange);
	rs_AddString(g_sLangID_DataUpgrade,&g_sLangTxt_DataUpgrade);
	rs_AddString(g_sLangID_Integrity,&g_sLangTxt_Integrity);
	rs_AddString(g_sLangID_GeneralCall,&g_sLangTxt_GeneralCall);
	//设置装置的当前运行组
	rs_AddString(g_sLangID_SetCurGrpDevice,&g_sLangTxt_SetCurGrpDevice);
	rs_AddString(g_sLangID_FixedValueNum,&g_sLangTxt_FixedValueNum);
	//和装置联机
	rs_AddString(g_sLangID_LinkSet,&g_sLangTxt_LinkSet);
	rs_AddString(g_sLangID_IP,&g_sLangTxt_IP);
	rs_AddString(g_sLangID_EnumRptCtrlBlk,&g_sLangTxt_EnumRptCtrlBlk);
	
	//网卡IP设置
	rs_AddString(g_sLangID_NetwCardIpset,&g_sLangTxt_NetwCardIpset);
	rs_AddString(g_sLangID_NetwCardSel,&g_sLangTxt_NetwCardSel);
	rs_AddString(g_sLangID_IpAddr,&g_sLangTxt_IpAddr);
	rs_AddString(g_sLangID_SubNetwMask,&g_sLangTxt_SubNetwMask);
	rs_AddString(g_sLangID_AddIp,&g_sLangTxt_AddIp);
	rs_AddString(g_sLangID_Ethernet,&g_sLangTxt_Ethernet);
	
	//进度条
	rs_AddString(g_sLangID_InOperation,&g_sLangTxt_InOperation);
	rs_AddString(g_sLangID_DataOperation,&g_sLangTxt_DataOperation);
	//选择路径
	rs_AddString(g_sLangID_SelPath,&g_sLangTxt_SelPath);
	//选择定值区
	rs_AddString(g_sLangID_SelValueZone,&g_sLangTxt_SelValueZone);
	rs_AddString(g_sLangID_OperationZone,&g_sLangTxt_OperationZone);
	//自动匹配数据集查看
	rs_AddString(g_sLangID_AutoMatchView,&g_sLangTxt_AutoMatchView);
	//BrcbCtrlDlg里的输出信息
	rs_AddString(g_sLangID_NotEnum,&g_sLangTxt_NotEnum);
	//DlgSelPath里的输出信息
	rs_AddString(g_sLangID_EnterPath,&g_sLangTxt_EnterPath);
	//IPSetObj里的输出信息
	rs_AddString(g_sLangID_FileOprtFail,&g_sLangTxt_FileOprtFail);
	//LinkSetDlg里的输出信息
	rs_AddString(g_sLangID_RestartAndLink,&g_sLangTxt_RestartAndLink);
	//LocalIpSetDlg里的输出信息
	rs_AddString(g_sLangID_ResetIP,&g_sLangTxt_ResetIP);
	//MainFrm里的输出信息
	rs_AddString(g_sLangID_MmsPtclPrgm,&g_sLangTxt_MmsPtclPrgm);
	rs_AddString(g_sLangID_DeviceListView,&g_sLangTxt_DeviceListView);
	rs_AddString(g_sLangID_SelDeviceObj,&g_sLangTxt_SelDeviceObj);
	rs_AddString(g_sLangID_NoFixedValueRegion,&g_sLangTxt_NoFixedValueRegion);
	rs_AddString(g_sLangID_DeviceMdlFile,&g_sLangTxt_DeviceMdlFile);
	rs_AddString(g_sLangID_SendSuccMsg,&g_sLangTxt_SendSuccMsg);
	rs_AddString(g_sLangID_SendCommMsg,&g_sLangTxt_SendCommMsg);
	rs_AddString(g_sLangID_SendSySMsg,&g_sLangTxt_SendSySMsg);
	rs_AddString(g_sLangID_SetFixedValueRegionFail,&g_sLangTxt_SetFixedValueRegionFail);
	rs_AddString(g_sLangID_SetFixedValueRegion,&g_sLangTxt_SetFixedValueRegion);
	rs_AddString(g_sLangID_EditFixedValueRegionSucc,&g_sLangTxt_EditFixedValueRegionSucc);
	rs_AddString(g_sLangID_EditFixedValueRegionFail,&g_sLangTxt_EditFixedValueRegionFail);
	rs_AddString(g_sLangID_SolidFixedValueRegionSucc,&g_sLangTxt_SolidFixedValueRegionSucc);
	rs_AddString(g_sLangID_SolidFixedValueRegionFail,&g_sLangTxt_SolidFixedValueRegionFail);
	rs_AddString(g_sLangID_CtrlWriteSucc,&g_sLangTxt_CtrlWriteSucc);
	rs_AddString(g_sLangID_CtrlWriteFail,&g_sLangTxt_CtrlWriteFail);
	rs_AddString(g_sLangID_DeviceReturnSucc,&g_sLangTxt_DeviceReturnSucc);
	rs_AddString(g_sLangID_DeviceReturnFail,&g_sLangTxt_DeviceReturnFail);
	rs_AddString(g_sLangID_AllCommandExecuted,&g_sLangTxt_AllCommandExecuted);
	//MmsDeviceTreeCtrl里的输出信息
	rs_AddString(g_sLangID_MmsNodes,&g_sLangTxt_MmsNodes);
	rs_AddString(g_sLangID_RecdWaveFile,&g_sLangTxt_RecdWaveFile);
	rs_AddString(g_sLangID_LogRecord,&g_sLangTxt_LogRecord);
	rs_AddString(g_sLangID_TooMuchActualDevice,&g_sLangTxt_TooMuchActualDevice);
	//NodeView里的输出信息
	rs_AddString(g_sLangID_Attributes,&g_sLangTxt_Attributes);
	rs_AddString(g_sLangID_UnableloadBitmap,&g_sLangTxt_UnableloadBitmap);
	//OutputWnd里的输出信息
	rs_AddString(g_sLangID_Log,&g_sLangTxt_Log);
	rs_AddString(g_sLangID_ReportD,&g_sLangTxt_ReportD);
	rs_AddString(g_sLangID_SoeReportD,&g_sLangTxt_SoeReportD);
	rs_AddString(g_sLangID_Date,&g_sLangTxt_Date);
	rs_AddString(g_sLangID_TimeDiffer,&g_sLangTxt_TimeDiffer);
	rs_AddString(g_sLangID_DetailedInfor,&g_sLangTxt_DetailedInfor);
	//PpMmsEngine的输出信息
	rs_AddString(g_sLangID_InitSocketFailed,&g_sLangTxt_InitSocketFailed);
	rs_AddString(g_sLangID_WizardGeneratedApp,&g_sLangTxt_WizardGeneratedApp);
	rs_AddString(g_sLangID_Unknown,&g_sLangTxt_Unknown);
	rs_AddString(g_sLangID_ReadDeviceDataComplete,&g_sLangTxt_ReadDeviceDataComplete);
	rs_AddString(g_sLangID_Monitor,&g_sLangTxt_Monitor);
	rs_AddString(g_sLangID_NotEnumDataSet,&g_sLangTxt_NotEnumDataSet);
	rs_AddString(g_sLangID_TotalStep1,&g_sLangTxt_TotalStep1);
	rs_AddString(g_sLangID_TotalStep2,&g_sLangTxt_TotalStep2);
	rs_AddString(g_sLangID_Links,&g_sLangTxt_Links);
	rs_AddString(g_sLangID_CommProcessing,&g_sLangTxt_CommProcessing);
	rs_AddString(g_sLangID_ProgmInilFail,&g_sLangTxt_ProgmInilFail);
	rs_AddString(g_sLangID_ProgmRun,&g_sLangTxt_ProgmRun);
	//PpMmsEngineView里的输出信息
	rs_AddString(g_sLangID_DaXiao,&g_sLangTxt_DaXiao);
	//ZoneSelDlg里的输出信息
	rs_AddString(g_sLangID_RegionD,&g_sLangTxt_RegionD);

	rs_AddString(g_sLangID_Menu_32777,&g_sLangTxt_Menu_32777 );
	rs_AddString(g_sLangID_Menu_32778,&g_sLangTxt_Menu_32778 );
	rs_AddString(g_sLangID_Menu_32794,&g_sLangTxt_Menu_32794 );
	rs_AddString(g_sLangID_Menu_32795,&g_sLangTxt_Menu_32795 );
	rs_AddString(g_sLangID_Menu_32797,&g_sLangTxt_Menu_32797 );
	rs_AddString(g_sLangID_Menu_32804,&g_sLangTxt_Menu_32804 );
	rs_AddString(g_sLangID_Menu_32796,&g_sLangTxt_Menu_32796 );
	rs_AddString(g_sLangID_Menu_32786,&g_sLangTxt_Menu_32786 );
	rs_AddString(g_sLangID_Menu_32798,&g_sLangTxt_Menu_32798 );

	rs_AddString(g_sLangID_HadNoDataNeedEdit, &g_sLangTxt_HadNoDataNeedEdit);
	rs_AddString(g_sLangID_ReadDeviceDirSucc, &g_sLangTxt_ReadDeviceDirSucc);
	rs_AddString(g_sLangID_ReadDeviceDirFail, &g_sLangTxt_ReadDeviceDirFail);
	rs_AddString(g_sLangID_SetZoneFail, &g_sLangTxt_SetZoneFail);
	rs_AddString(g_sLangID_ConnectSucc, &g_sLangTxt_ConnectSucc);
	rs_AddString(g_sLangID_ConnectFail, &g_sLangTxt_ConnectFail);
	rs_AddString(g_sLangID_DisConnectSucc, &g_sLangTxt_DisConnectSucc);
	rs_AddString(g_sLangID_DisConnectFail, &g_sLangTxt_DisConnectFail);
	rs_AddString(g_sLangID_RdDatasetSucc, &g_sLangTxt_RdDatasetSucc);
	rs_AddString(g_sLangID_RdDatasetFail, &g_sLangTxt_RdDatasetFail);
	rs_AddString(g_sLangID_ReadRecorDirFail, &g_sLangTxt_ReadRecorDirFail);
	rs_AddString(g_sLangID_ReadRecordDirSucc, &g_sLangTxt_ReadRecordDirSucc);
	rs_AddString(g_sLangID_ReadRecordFileSucc, &g_sLangTxt_ReadRecordFileSucc);
	rs_AddString(g_sLangID_ReadRecordFileFail, &g_sLangTxt_ReadRecordFileFail);
	rs_AddString(g_sLangID_WriteDataFail, &g_sLangTxt_WriteDataFail);
	rs_AddString(g_sLangID_WriteDataSucc, &g_sLangTxt_WriteDataSucc);
	rs_AddString(g_sLangID_StartRptFail, &g_sLangTxt_StartRptFail);
	rs_AddString(g_sLangID_StartRptSucc, &g_sLangTxt_StartRptSucc);
	rs_AddString(g_sLangID_StopRptFail, &g_sLangTxt_StopRptFail);
	rs_AddString(g_sLangID_StopRptSucc, &g_sLangTxt_StopRptSucc);
	rs_AddString(g_sLangID_ReadZoneFail, &g_sLangTxt_ReadZoneFail);
	rs_AddString(g_sLangID_NetConnect, &g_sLangTxt_NetConnect);
	rs_AddString(g_sLangID_NetDisConnect, &g_sLangTxt_NetDisConnect);


	rs_AddString(g_sLangID_Menu_57634,&g_sLangTxt_Menu_57634);
	rs_AddString(g_sLangID_Menu_57632,&g_sLangTxt_Menu_57632);
	rs_AddString(g_sLangID_Menu_149,&g_sLangTxt_Menu_149);

	rs_AddString(g_sLangID_WriteDataAfterWait,&g_sLangTxt_WriteDataAfterWait);
	rs_AddString(g_sLangID_DvRcvOverTime, &g_sLangTxt_DvRcvOverTime);
	rs_AddString(g_sLangID_HasNoRptCtrl, &g_sLangTxt_HasNoRptCtrl);
	rs_AddString(g_sLangID_RptCtrlHasStart, &g_sLangTxt_RptCtrlHasStart);
	rs_AddString(g_sLangID_StartRptCtrlFinish, &g_sLangTxt_StartRptCtrlFinish);
	rs_AddString(g_sLangID_StartRptCtrlFail, &g_sLangTxt_StartRptCtrlFail);
	rs_AddString(g_sLangID_HasNoNet, &g_sLangTxt_HasNoNet);
	rs_AddString(g_sLangID_SetEdtZnFail, &g_sLangTxt_SetEdtZnFail);
	rs_AddString(g_sLangID_SetEdtZnRd, &g_sLangTxt_SetEdtZnRd);
	rs_AddString(g_sLangID_IndexAndTotal, &g_sLangTxt_IndexAndTotal);
	rs_AddString(g_sLangID_WritDataFail, &g_sLangTxt_WritDataFail);
	rs_AddString(g_sLangID_WritDataSucc, &g_sLangTxt_WritDataSucc);
	rs_AddString(g_sLangID_WritDataPrgs, &g_sLangTxt_WritDataPrgs);
	rs_AddString(g_sLangID_BfExecNext, &g_sLangTxt_BfExecNext);
	rs_AddString(g_sLangID_EditDataFail, &g_sLangTxt_EditDataFail);
	rs_AddString(g_sLangID_GetNexLdZn, &g_sLangTxt_GetNexLdZn);
	rs_AddString(g_sLangID_NoLdHasZn, &g_sLangTxt_NoLdHasZn);
	rs_AddString(g_sLangID_RdSetZnsFail, &g_sLangTxt_RdSetZnsFail);
	rs_AddString(g_sLangID_RdCurSetZnsFail, &g_sLangTxt_RdCurSetZnsFail);
	rs_AddString(g_sLangID_SetCurSetZnFail, &g_sLangTxt_SetCurSetZnFail);
	rs_AddString(g_sLangID_SetCurSetZnSucc, &g_sLangTxt_SetCurSetZnSucc);
	rs_AddString(g_sLangID_LdHasNoZn, &g_sLangTxt_LdHasNoZn);
	rs_AddString(g_sLangID_SetCurEdtZnFail, &g_sLangTxt_SetCurEdtZnFail);
	rs_AddString(g_sLangID_SetCurEdtZnSucc, &g_sLangTxt_SetCurEdtZnSucc);
	rs_AddString(g_sLangID_SolidZnFail, &g_sLangTxt_SolidZnFail);
	rs_AddString(g_sLangID_SolidZnSucc, &g_sLangTxt_SolidZnSucc);
	rs_AddString(g_sLangID_SelEnaFail, &g_sLangTxt_SelEnaFail);
	rs_AddString(g_sLangID_SelEnaSucc, &g_sLangTxt_SelEnaSucc);
	rs_AddString(g_sLangID_AfterSelEna, &g_sLangTxt_AfterSelEna);
	rs_AddString(g_sLangID_ExecEnaFail, &g_sLangTxt_ExecEnaFail);
	rs_AddString(g_sLangID_ExecEnaSucc, &g_sLangTxt_ExecEnaSucc);
	rs_AddString(g_sLangID_EnaOptrTime, &g_sLangTxt_EnaOptrTime);
	rs_AddString(g_sLangID_WriteEnaParaErr, &g_sLangTxt_WriteEnaParaErr);
	rs_AddString(g_sLangID_EnaOptrFail, &g_sLangTxt_EnaOptrFail);
	rs_AddString(g_sLangID_DvResetFail, &g_sLangTxt_DvResetFail);
	rs_AddString(g_sLangID_DvResetFailEx, &g_sLangTxt_DvResetFailEx);

	rs_AddString(g_sLangID_FuncID_Connect, &g_sLangTxt_FuncID_Connect);
	rs_AddString(g_sLangID_FuncID__FuncID_DisConnect, &g_sLangTxt_FuncID_DisConnect);
	rs_AddString(g_sLangID_FuncID_WriteData, &g_sLangTxt_FuncID_WriteData);
	rs_AddString(g_sLangID_FuncID_ReadData, &g_sLangTxt_FuncID_ReadData);
	rs_AddString(g_sLangID_FuncID_StartRpt, &g_sLangTxt_FuncID_StartRpt);
	rs_AddString(g_sLangID_FuncID_StopRpt, &g_sLangTxt_FuncID_StopRpt);
	rs_AddString(g_sLangID_FuncID_GetRunZn, &g_sLangTxt_FuncID_GetRunZn);
	rs_AddString(g_sLangID_FuncID_SetRunZn, &g_sLangTxt_FuncID_SetRunZn);
	rs_AddString(g_sLangID_FuncID_EnumDvDir, &g_sLangTxt_FuncID_EnumDvDir);
	rs_AddString(g_sLangID_FuncID_ChangeEditZn, &g_sLangTxt_FuncID_ChangeEditZn);
	rs_AddString(g_sLangID_FuncID_SolidEditZn, &g_sLangTxt_FuncID_SolidEditZn);


	rs_AddString(g_sLangID_CreatMmsComm, &g_sLangTxt_CreatMmsComm);
	rs_AddString(g_sLangID_ReachMax, &g_sLangTxt_ReachMax);
	rs_AddString(g_sLangID_ReleasMmsComm, &g_sLangTxt_ReleasMmsComm);

// 	rs_AddString(g_sLangID_CurrentActSet, &g_sLangTxt_CurrentActSet);
// 	rs_AddString(g_sLangID_SettingTotalNo, &g_sLangTxt_SettingTotalNo);
// 	rs_AddString(g_sLangID_CommandTotalTime, &g_sLangTxt_CommandTotalTime);
// 	rs_AddString(g_sLangID_CommandExecuTime, &g_sLangTxt_CommandExecuTime);
// 	rs_AddString(g_sLangID_CommandChoseTime, &g_sLangTxt_CommandChoseTime);
// 	rs_AddString(g_sLangID_CommandExecuMess, &g_sLangTxt_CommandExecuMess);
// 	rs_AddString(g_sLangID_CommandChoseMess, &g_sLangTxt_CommandChoseMess);
// 	rs_AddString(g_sLangID_WrongMess, &g_sLangTxt_WrongMess);
// 	rs_AddString(g_sLangID_RecordPath, &g_sLangTxt_RecordPath);
// 	rs_AddString(g_sLangID_EnaChangeTime, &g_sLangTxt_EnaChangeTime);
// 	rs_AddString(g_sLangID_EnaChoseTime, &g_sLangTxt_EnaChoseTime);
// 	rs_AddString(g_sLangID_MonitErrorTime, &g_sLangTxt_MonitErrorTime);
// 	rs_AddString(g_sLangID_BeforEnaRead, &g_sLangTxt_BeforEnaRead);
// 	rs_AddString(g_sLangID_BeforEnaReadTime, &g_sLangTxt_BeforEnaReadTime);
// 
// 	rs_AddString(g_sLangID_WritDataMess, &g_sLangTxt_WritDataMess);
// 	rs_AddString(g_sLangID_SetEdtTime, &g_sLangTxt_SetEdtTime);
// 	rs_AddString(g_sLangID_SetActTime, &g_sLangTxt_SetActTime);
// 	rs_AddString(g_sLangID_SetEdtMess, &g_sLangTxt_SetEdtMess);
// 	rs_AddString(g_sLangID_SetActMess, &g_sLangTxt_SetActMess);
// 	rs_AddString(g_sLangID_TestConnSta, &g_sLangTxt_TestConnSta);

	rs_AddString(g_sLangID_ExecConnCommand, &g_sLangTxt_ExecConnCommand);
	rs_AddString(g_sLangID_DatasetPathError, &g_sLangTxt_DatasetPathError);
	rs_AddString(g_sLangID_Ena, &g_sLangTxt_Ena);
	rs_AddString(g_sLangID_RemoteCtl, &g_sLangTxt_RemoteCtl);
	rs_AddString(g_sLangID_UnRegRepDataSet, &g_sLangTxt_UnRegRepDataSet);
	rs_AddString(g_sLangID_SwitchSet, &g_sLangTxt_SwitchSet);
	rs_AddString(g_sLangID_OnlyReadProp, &g_sLangTxt_OnlyReadProp);
	rs_AddString(g_sLangID_NoNeedCorect, &g_sLangTxt_NoNeedCorect);
	rs_AddString(g_sLangID_RegRepDataSetMiss, &g_sLangTxt_RegRepDataSetMiss);
	rs_AddString(g_sLangID_StopRepDataSetMiss, &g_sLangTxt_StopRepDataSetMiss);

	rs_AddString(g_sLangID_SendOverMesNotWin, &g_sLangTxt_SendOverMesNotWin);
	rs_AddString(g_sLangID_SendOverMes, &g_sLangTxt_SendOverMes);
	rs_AddString(g_sLangID_DataNotExist, &g_sLangTxt_DataNotExist);
	rs_AddString(g_sLangID_RegistDataFail, &g_sLangTxt_RegistDataFail);
	rs_AddString(g_sLangID_RegistDataSuc , &g_sLangTxt_RegistDataSuc);
	rs_AddString(g_sLangID_CmdMsgFailWin, &g_sLangTxt_CmdMsgFailWin);
	rs_AddString(g_sLangID_MapNotExist, &g_sLangTxt_MapNotExist);

	rs_AddString(g_sLangID_ZnNumAndRunZn, &g_sLangTxt_ZnNumAndRunZn);

}

static long g_nCXLanguageResourcePp_Mms_InitLangTxt = 0;

void CXLanguageResourcePp_Mms::InitLangTxt()
{
	CXLanguageResourceIecBase::InitLangTxt();

	if (g_nCXLanguageResourcePp_Mms_InitLangTxt > 1)
	{
		return;
	}

	g_nCXLanguageResourcePp_Mms_InitLangTxt = 1;

	//装置操作
	g_sLangID_DeviceOperation                  = _T("sDeviceOperation");
	g_sLangTxt_DeviceOperation                 = _T("装置操作");
	g_sLangID_Online                           = _T("sOnline");
	g_sLangTxt_Online                          = _T("联机");
	g_sLangID_Disconnect                       = _T("sDisconnect");
	g_sLangTxt_Disconnect                      = _T("断开");
	g_sLangID_DisconnectTip                    = _T("sDisconnectTip");
	g_sLangTxt_DisconnectTip                   = _T("断开装置\n断开装置");
	g_sLangID_Return                           = _T("sReturn");
	g_sLangTxt_Return                          = _T("复归");
	//枚举
	g_sLangID_Enum                             = _T("sEnum");
	g_sLangTxt_Enum                            = _T("枚举");
	g_sLangID_ReadNodes                 = _T("sReadNodes");
	g_sLangTxt_ReadNodes                = _T("读取模型");
	g_sLangID_ReadNodesTip              = _T("sReadNodesTip");
	g_sLangTxt_ReadNodesTip             = _T("读取装置建模模型\n读取模型");
	g_sLangID_RefreshDirectory                 = _T("sRefreshDirectory");
	g_sLangTxt_RefreshDirectory                = _T("刷新目录");
	g_sLangID_RefreshDirectoryTip              = _T("sRefreshDirectoryTip");
	g_sLangTxt_RefreshDirectoryTip             = _T("刷新目录\n刷新");
	g_sLangID_Device                           = _T("sDevice");
	g_sLangTxt_Device                          = _T("装置");
	g_sLangID_DeviceTip                        = _T("sDeviceTip");
	g_sLangTxt_DeviceTip                       = _T("读设备全部数据\n读设备数据");
	//  g_sLangID_LogicDevice                      = _T("sLogicDevice");
	//  g_sLangTxt_LogicDevice                     = _T("逻辑设备");
	g_sLangID_LogicDeviceTip                   = _T("sLogicDeviceTip");
	g_sLangTxt_LogicDeviceTip                  = _T("读逻辑设备数据\n读逻辑设备");
	g_sLangID_DataSetTip                       = _T("sDataSetTip");
	g_sLangTxt_DataSetTip                      = _T("读当前数据\n读当前数据");
	//数据值
	g_sLangID_DataValue                        = _T("sDataValue");
	g_sLangTxt_DataValue                       = _T("数据值");
	g_sLangID_ReadData                         = _T("sReadData");
	g_sLangTxt_ReadData                        = _T("读数据");
	g_sLangID_ReadDataTip                      = _T("sReadDataTip");
	g_sLangTxt_ReadDataTip                     = _T("获取数值\n获取数值");
	g_sLangID_ModifyData                       = _T("sModifyData");
	g_sLangTxt_ModifyData                      = _T("修改数据");
	//定值区
	g_sLangID_ReadFixedValueRegion             = _T("sReadFixedValueRegion");
	g_sLangTxt_ReadFixedValueRegion            = _T("读定值区");
	g_sLangID_ModifyFixedValueRegion           = _T("sModifyFixedValueRegion");
	g_sLangTxt_ModifyFixedValueRegion          = _T("修改定值区");
	//报告
	g_sLangID_StartReportTip                   = _T("sStartReportTip");
	g_sLangTxt_StartReportTip                  = _T("启动报告\n启动");
	g_sLangID_StopReportTip                    = _T("sStopReportTip");
	g_sLangTxt_StopReportTip                   = _T("停止报告\n停止");
	g_sLangID_DebugAdd                         = _T("sDebugAdd");
	g_sLangTxt_DebugAdd                        = _T("调试-添加");
	g_sLangID_DebugAddTip                      = _T("sDebugAddTip");
	g_sLangTxt_DebugAddTip                     = _T("添加到SOE报告(F2)\n添加到SOE报告");
	//文件
	g_sLangID_ExportModel                      = _T("sExportModel");
	g_sLangTxt_ExportModel                     = _T("导出模型");
	g_sLangID_ExportModelTip                   = _T("sExportModelTip");
	g_sLangTxt_ExportModelTip                  = _T("导出设备模型为XML文件\n导出");
	g_sLangID_ImportModel                      = _T("sImportModel");
	g_sLangTxt_ImportModel                     = _T("导入模型");
	g_sLangID_ExportMmsNodes                      = _T("sExportMmsNodes");
	g_sLangTxt_ExportMmsNodes                    = _T("导出建模");
	g_sLangID_ExportMmsNodesTip                   = _T("sExportMmsNodesTip");
	g_sLangTxt_ExportMmsNodesTip                  = _T("导出设备建模模型为XML文件\n导出");
	//视图
	g_sLangID_DispMmsErrInfor                  = _T("sDispMmsErrInfor");
	g_sLangTxt_DispMmsErrInfor                 = _T("显示MMS错误信息");
	g_sLangID_DispMmsErrInforTip               = _T("sDispMmsErrInforTip");
	g_sLangTxt_DispMmsErrInforTip              = _T("显示MMS错误信息\n显示MMS错误信息");
	g_sLangID_ChangeAndRunArea                 = _T("sChangeAndRunArea");
	g_sLangTxt_ChangeAndRunArea                = _T("能改运行区");
	g_sLangID_PropertyBar                      = _T("sPropertyBar");
	g_sLangTxt_PropertyBar                     = _T("属性栏");
	g_sLangID_DeviceToolbar                    = _T("sDeviceToolbar");
	g_sLangTxt_DeviceToolbar                   = _T("设备工具栏");
	//启动报告
	g_sLangID_RptTypeSel                       = _T("sRptTypeSel");
	g_sLangTxt_RptTypeSel                      = _T("报告控制块类型选择");
	g_sLangID_StartSendData                    = _T("sStartSendData");
	g_sLangTxt_StartSendData                   = _T("启动上送报告数据");
	g_sLangID_OptFldsSel                       = _T("sOptFldsSel");
	g_sLangTxt_OptFldsSel                      = _T("OptFlds(2字节，0位保留)");
	g_sLangID_SerialNumber                     = _T("sSerialNumber");
	g_sLangTxt_SerialNumber                    = _T("1-序号");
	g_sLangID_TimeScale                        = _T("sTimeScale");
	g_sLangTxt_TimeScale                       = _T("2-报告生成时标");
	g_sLangID_Reason                           = _T("sReason");
	g_sLangTxt_Reason                          = _T("3-原因");
	g_sLangID_DataSetName                      = _T("sDataSetName");
	g_sLangTxt_DataSetName                     = _T("4-数据集名称");
	g_sLangID_DataSetPath                      = _T("sDataSetPath");
	g_sLangTxt_DataSetPath                     = _T("5-数据集路径");
	g_sLangID_BufferOverflowFlag               = _T("sBufferOverflowFlag");
	g_sLangTxt_BufferOverflowFlag              = _T("6-缓存溢出标志");
	g_sLangID_ItemNum                          = _T("sItemNum");
	g_sLangTxt_ItemNum                         = _T("7-条目号");
	g_sLangID_ConfigNum                        = _T("sConfigNum");
	g_sLangTxt_ConfigNum                       = _T("8-配置号");
	g_sLangID_SubNumber                        = _T("sSubNumber");
	g_sLangTxt_SubNumber                       = _T("9-子序号");
	g_sLangID_TrgOpsSel                        = _T("sTrgOpsSel");
	g_sLangTxt_TrgOpsSel                       = _T("TrgOpsSel(1字节，0位保留)");
	g_sLangID_DataChange                       = _T("sDataChange");
	g_sLangTxt_DataChange                      = _T("1-数据改变（变化上送）");
	g_sLangID_QualityChange                    = _T("sQualityChange");
	g_sLangTxt_QualityChange                   = _T("2-质量改变（例品质有效无效）");
	g_sLangID_DataUpgrade                      = _T("sDataUpgrade");
	g_sLangTxt_DataUpgrade                     = _T("3-数据升级");
	g_sLangID_Integrity                        = _T("sIntegrity");
	g_sLangTxt_Integrity                       = _T("4-完整性（周期上送）");
	g_sLangID_GeneralCall                      = _T("sGeneralCall");
	g_sLangTxt_GeneralCall                     = _T("5-总召唤（总召上送）");
	//设置装置的当前运行组
	g_sLangID_SetCurGrpDevice                  = _T("sSetCurGrpDevice");
	g_sLangTxt_SetCurGrpDevice                 = _T("设置装置的当前运行组");
	g_sLangID_FixedValueNum                    = _T("sFixedValueNum");
	g_sLangTxt_FixedValueNum                   = _T("定值组号");

	//和装置联机
	g_sLangID_LinkSet                          = _T("sLinkSet");
	g_sLangTxt_LinkSet                         = _T("和装置联机设置");
	g_sLangID_IP                               = _T("sIP");
	g_sLangTxt_IP                              = _T("装置IP地址");
	g_sLangID_EnumRptCtrlBlk                   = _T("sEnumRptCtrlBlk");
	g_sLangTxt_EnumRptCtrlBlk                  = _T("是否枚举报告控制块？");

	//网卡IP设置
	g_sLangID_NetwCardIpset                    = _T("sNetwCardIpset");
	g_sLangTxt_NetwCardIpset                   = _T("网卡IP设置");
	g_sLangID_NetwCardSel                      = _T("sNetwCardSel");
	g_sLangTxt_NetwCardSel                     = _T("网卡选择");
	g_sLangID_IpAddr                           = _T("sIpAddr");
	g_sLangTxt_IpAddr                          = _T("IP地址");
	g_sLangID_SubNetwMask                      = _T("sSubNetwMask");
	g_sLangTxt_SubNetwMask                     = _T("子网掩码");
	g_sLangID_AddIp                            = _T("sAddIp");
	g_sLangTxt_AddIp                           = _T("添加IP");
	g_sLangID_Ethernet                            = _T("sEthernet");
	g_sLangTxt_Ethernet                           = _T("以太网");
	//进度条
	g_sLangID_InOperation                      = _T("sInOperation");
	g_sLangTxt_InOperation                     = _T("处理中，请稍候");
	g_sLangID_DataOperation                    = _T("sDataOperation");
	g_sLangTxt_DataOperation                   = _T("数据操作中...");
	//选择路径
	g_sLangID_SelPath                          = _T("sSelPath");
	g_sLangTxt_SelPath                         = _T("选择路径");
	//选择定值区
	g_sLangID_SelValueZone                     = _T("sSelValueZone");
	g_sLangTxt_SelValueZone                    = _T("选择定值区");
	g_sLangID_OperationZone                    = _T("sOperationZone");
	g_sLangTxt_OperationZone                   = _T("运行区");
	//自动匹配数据集查看
	g_sLangID_AutoMatchView                    = _T("sAutoMatchView");
	g_sLangTxt_AutoMatchView                   = _T("自动匹配数据集查看");
	//BrcbCtrlDlg里的输出信息
	g_sLangID_NotEnum                          = _T("sNotEnum");
	g_sLangTxt_NotEnum                         = _T("没有枚举数据，不能设置报告召唤");
	//DlgSelPath里的输出信息
	g_sLangID_EnterPath                        = _T("sEnterPath");
	g_sLangTxt_EnterPath                       = _T("请输入路径");
	//IPSetObj里的输出信息
	g_sLangID_FileOprtFail                     = _T("sFileOprtFail");
	g_sLangTxt_FileOprtFail                    = _T("VMD.INI 文件操作失败!");
	//LinkSetDlg里的输出信息
	g_sLangID_RestartAndLink                   = _T("sRestartAndLink");
	g_sLangTxt_RestartAndLink                  = _T("装置ip已发生改变,请重启程序再联机!");
	//LocalIpSetDlg里的输出信息
	g_sLangID_ResetIP                          = _T("sResetIP");
	g_sLangTxt_ResetIP                         = _T("当前设置的IP已经存在,请重新设置!");
	//MainFrm里的输出信息
	g_sLangID_MmsPtclPrgm                      = _T("sMmsPtclPrgm");
	g_sLangTxt_MmsPtclPrgm                     = _T("61850MMS规约引擎程序");
	g_sLangID_DeviceListView                   = _T("sDeviceListView");
	g_sLangTxt_DeviceListView                  = _T("设备列表视图");
	g_sLangID_SelDeviceObj                     = _T("sSelDeviceObj");
	g_sLangTxt_SelDeviceObj                    = _T("请选择设备对象");
	g_sLangID_NoFixedValueRegion               = _T("sNoFixedValueRegion");
	g_sLangTxt_NoFixedValueRegion              = _T("【%s】没有定义定值区");
	g_sLangID_DeviceMdlFile                    = _T("sDeviceMdlFile");
	g_sLangTxt_DeviceMdlFile                   = _T("设备模型文件（xml)|*.xml|");
	g_sLangID_SendSuccMsg                      = _T("sSendSuccMsg");
	g_sLangTxt_SendSuccMsg                     = _T("+++++++++++发送连接设备成功消息+++++++++++");
	g_sLangID_SendCommMsg                      = _T("sSendCommMsg");
	g_sLangTxt_SendCommMsg                     = _T("发送通讯消息：wParam=%d  lParam=%d");
	g_sLangID_SendSySMsg                       = _T("sSendSySMsg");
	g_sLangTxt_SendSySMsg                      = _T("发送系统消息：wParam=%d  lParam=%d");
	g_sLangID_SetFixedValueRegionFail          = _T("sSetFixedValueRegionFail");
	g_sLangTxt_SetFixedValueRegionFail         = _T("【%d】设置当前定值运行区号%d失败【Error】");
	g_sLangID_SetFixedValueRegion              = _T("sSetFixedValueRegion");
	g_sLangTxt_SetFixedValueRegion             = _T("设置当前运行定值区为%d");
	g_sLangID_EditFixedValueRegionSucc         = _T("sEditFixedValueRegionSucc");
	g_sLangTxt_EditFixedValueRegionSucc        = _T("切换编辑定值区%d成功");
	g_sLangID_EditFixedValueRegionFail         = _T("sEditFixedValueRegionFail");
	g_sLangTxt_EditFixedValueRegionFail        = _T("切换编辑定值区%d失败【Error】");
	g_sLangID_SolidFixedValueRegionSucc        = _T("sSolidFixedValueRegionSucc");
	g_sLangTxt_SolidFixedValueRegionSucc       = _T("固化定值区%d定值成功");
	g_sLangID_SolidFixedValueRegionFail        = _T("sSolidFixedValueRegionFail");
	g_sLangTxt_SolidFixedValueRegionFail       = _T("固化定值区%d定值失败【Error】");
	g_sLangID_CtrlWriteSucc                    = _T("sCtrlWriteSucc");
	g_sLangTxt_CtrlWriteSucc                   = _T("控制写成功");
	g_sLangID_CtrlWriteFail                    = _T("sCtrlWriteFail");
	g_sLangTxt_CtrlWriteFail                   = _T("控制写失败【Error】");
	g_sLangID_DeviceReturnSucc                 = _T("sDeviceReturnSucc");
	g_sLangTxt_DeviceReturnSucc                = _T("装置复归成功");
	g_sLangID_DeviceReturnFail                 = _T("sDeviceReturnFail");
	g_sLangTxt_DeviceReturnFail                = _T("装置复归失败【Error】");
	g_sLangID_AllCommandExecuted               = _T("sAllCommandExecuted");
	g_sLangTxt_AllCommandExecuted              = _T("自动测试模式，命令全部执行完毕!!");
	//MmsDeviceTreeCtrl里的输出信息
	g_sLangID_MmsNodes                     = _T("sMmsNodes");
	g_sLangTxt_MmsNodes                    = _T("建模模型");
	g_sLangID_RecdWaveFile                     = _T("sRecdWaveFile");
	g_sLangTxt_RecdWaveFile                    = _T("录波文件");
	g_sLangID_LogRecord                        = _T("sLogRecord");
	g_sLangTxt_LogRecord                       = _T("日志记录");
	g_sLangID_TooMuchActualDevice              = _T("sTooMuchActualDevice");
	g_sLangTxt_TooMuchActualDevice             = _T("实际装置数大于假设最大装置数!");
	//NodeView里的输出信息
	g_sLangID_Attributes                       = _T("sAttributes");
	g_sLangTxt_Attributes                      = _T("属性....");
	g_sLangID_UnableloadBitmap                 = _T("sUnableloadBitmap");
	g_sLangTxt_UnableloadBitmap                = _T("无法加载位图: %x\n");
	//OutputWnd里的输出信息
	g_sLangID_Log                              = _T("sLog");
	g_sLangTxt_Log                             = _T("日志");
	g_sLangID_ReportD                          = _T("sReportD");
	g_sLangTxt_ReportD                         = _T("报告%d");
	g_sLangID_SoeReportD                          = _T("sSoeReportD");
	g_sLangTxt_SoeReportD                         = _T("装置事件");
	g_sLangID_Date                             = _T("sDate");
	g_sLangTxt_Date                            = _T("%d年-%d月-%d日-%d时-%d分-%d秒：%s");
	g_sLangID_TimeDiffer                       = _T("sTimeDiffer");
	g_sLangTxt_TimeDiffer                      = _T("时差ms");
	g_sLangID_DetailedInfor                    = _T("sDetailedInfor");
	g_sLangTxt_DetailedInfor                   = _T("详细信息");
	//PpMmsEngine的输出信息
	g_sLangID_InitSocketFailed                 = _T("sInitSocketFailed");
	g_sLangTxt_InitSocketFailed                = _T("初始化SOCKET失败！");
	g_sLangID_WizardGeneratedApp               = _T("sWizardGeneratedApp");
	g_sLangTxt_WizardGeneratedApp              = _T("应用程序向导生成的本地应用程序");
	g_sLangID_Unknown                          = _T("sUnknown");
	g_sLangTxt_Unknown                         = _T("未知");
	g_sLangID_ReadDeviceDataComplete           = _T("sReadDeviceDataComplete");
	g_sLangTxt_ReadDeviceDataComplete          = _T("读取装置数据完成!");
	g_sLangID_Monitor                          = _T("sMonitor");
	g_sLangTxt_Monitor                         = _T("监视【%d】 RunSGIndex=【%08x】");
	g_sLangID_NotEnumDataSet                   = _T("sNotEnumDataSet");
	g_sLangTxt_NotEnumDataSet                  = _T("【%d-%d-%d】没有枚举数据集");
	g_sLangID_TotalStep1                       = _T("sTotalStep1");
	g_sLangTxt_TotalStep1                      = _T("第%d步 共%d步 ： %s");
	g_sLangID_TotalStep2                       = _T("sTotalStep2");
	g_sLangTxt_TotalStep2                      = _T("第%d步 共%d步 ： 设备%d - 逻辑设备%d - %s - %s");
	g_sLangID_Links                            = _T("sLinks");
	g_sLangTxt_Links                           = _T("联机：%s");
	g_sLangID_CommProcessing                   = _T("sCommProcessing");
	g_sLangTxt_CommProcessing                  = _T("MMS通讯处理中，请稍候............");
	g_sLangID_ProgmInilFail                    = _T("sProgmInilFail");
	g_sLangTxt_ProgmInilFail                   = _T("程序初始化失败!                ");
	g_sLangID_ProgmRun                         = _T("sProgmRun");
	g_sLangTxt_ProgmRun                        = _T("“%s”程序正在运行...");
	//PpMmsEngineView里的输出信息
	g_sLangID_DaXiao                           = _T("sDaXiao");
	g_sLangTxt_DaXiao                          = _T("大小");
	//ZoneSelDlg里的输出信息
	g_sLangID_RegionD                           = _T("sRegionD");
	g_sLangTxt_RegionD                          = _T("区-%d");

	g_sLangTxt_Menu_32777 = _T("启动报告(&B)	Ctrl+B");
	g_sLangTxt_Menu_32778 = _T("停止报告(&P)	Ctrl+P");
	g_sLangTxt_Menu_32794 = _T("调试模式(&D)");
	g_sLangTxt_Menu_32795 = _T("显示调试信息(&V)");
	g_sLangTxt_Menu_32797 = _T("调试-通讯失败(&F)");
	g_sLangTxt_Menu_32804 = _T("添加到SOE报告");
	g_sLangTxt_Menu_32796 = _T("单一设备模式(&S)");
	g_sLangTxt_Menu_32786 = _T("读测量值使用报告数据");
	g_sLangTxt_Menu_32798 = _T("复归命令只清空报告数据");
	g_sLangID_Menu_32777 = _T("sMenu_32777");
	g_sLangID_Menu_32778 = _T("sMenu_32778");
	g_sLangID_Menu_32794 = _T("sMenu_32794");
	g_sLangID_Menu_32795 = _T("sMenu_32795");
	g_sLangID_Menu_32797 = _T("sMenu_32797");
	g_sLangID_Menu_32804 = _T("sMenu_32804");
	g_sLangID_Menu_32796 = _T("sMenu_32796");
	g_sLangID_Menu_32786 = _T("sMenu_32786");
	g_sLangID_Menu_32798 = _T("sMenu_32798");

	g_sLangID_HadNoDataNeedEdit = _T("sHadNoDataNeedEdit");
	g_sLangTxt_HadNoDataNeedEdit = _T("没有需要修改的数据");
	g_sLangID_ReadDeviceDirSucc = _T("sReadDeviceDirSucc");
	g_sLangTxt_ReadDeviceDirSucc = _T("枚举装置目录成功.");
	g_sLangID_ReadDeviceDirFail = _T("sReadDeviceDirFail");
	g_sLangTxt_ReadDeviceDirFail = _T("枚举装置目录失败.");
	g_sLangID_SetZoneFail = _T("sSetZoneFail");
	g_sLangTxt_SetZoneFail = _T("设置当前定值运行区号失败!");
	g_sLangID_ConnectSucc = _T("sConnectSucc");
	g_sLangTxt_ConnectSucc = _T("和装置联机成功.");
	g_sLangID_ConnectFail = _T("sConnectFail");
	g_sLangTxt_ConnectFail = _T("和装置联机失败【Error】.");
	g_sLangID_DisConnectSucc = _T("sDisConnectSucc");
	g_sLangTxt_DisConnectSucc = _T("和装置断开连接成功.");
	g_sLangID_DisConnectFail = _T("sDisConnectFail");
	g_sLangTxt_DisConnectFail = _T("和装置断开连接失败【Error】.");
	g_sLangID_RdDatasetSucc = _T("sRdDatasetSucc");
	g_sLangTxt_RdDatasetSucc = _T("读数据集成功.");
	g_sLangID_RdDatasetFail = _T("sRdDatasetFail");
	g_sLangTxt_RdDatasetFail = _T("读数据集失败【Error】.");
	g_sLangID_ReadRecorDirFail = _T("sReadRecorDirFail");
	g_sLangTxt_ReadRecorDirFail = _T("读录波文件目录失败.");
	g_sLangID_ReadRecordDirSucc = _T("sReadRecordDirSucc");
	g_sLangTxt_ReadRecordDirSucc = _T("读录波文件目录成功.");
	g_sLangID_ReadRecordFileSucc = _T("sReadRecordFileSucc");
	g_sLangTxt_ReadRecordFileSucc = _T("读录波文件成功.");
	g_sLangID_ReadRecordFileFail = _T("sReadRecordFileFail");
	g_sLangTxt_ReadRecordFileFail = _T("读录波文件失败.");
	g_sLangID_WriteDataFail = _T("sWriteDataFail");
	g_sLangTxt_WriteDataFail = _T("写数据失败【Error】.");
	g_sLangID_WriteDataSucc = _T("sWriteDataSucc");
	g_sLangID_StartRptFail = _T("sStartRptFail");
	g_sLangTxt_WriteDataSucc = _T("写数据成功.");
	g_sLangTxt_StartRptFail = _T("启动报告失败【Error】.");
	g_sLangID_StartRptSucc = _T("sStartRptSucc");
	g_sLangTxt_StartRptSucc = _T("启动报告成功.");
	g_sLangID_StopRptFail = _T("sStopRptFail");
	g_sLangTxt_StopRptFail = _T("停止报告失败【Error】.");
	g_sLangID_StopRptSucc = _T("sStopRptSucc");
	g_sLangTxt_StopRptSucc = _T("停止报告成功.");
	g_sLangID_ReadZoneFail = _T("sReadZoneFail");
	g_sLangTxt_ReadZoneFail = _T("获取当前定值运行区号失败.");
	g_sLangID_NetConnect = _T("sNetConnect");
	g_sLangTxt_NetConnect = _T("网络连接正常.");
	g_sLangID_NetDisConnect = _T("sNetDisConnect");
	g_sLangTxt_NetDisConnect = _T("网络连接断开.");

	g_sLangID_Menu_57634 = _T("sMenu_57634");
	g_sLangTxt_Menu_57634 = _T("复制(&C)");
	g_sLangID_Menu_57632 = _T("sMenu_57632");
	g_sLangTxt_Menu_57632 = _T("清除(&C)");
	g_sLangID_Menu_149 = _T("sMenu_149");
	g_sLangTxt_Menu_149 = _T("隐藏(&H)");

	g_sLangID_WriteDataAfterWait = _T("sWriteDataAfterWait");
	g_sLangTxt_WriteDataAfterWait = _T("%s:%s:等待%d毫秒");
	g_sLangID_DvRcvOverTime = _T("sDvRcvOverTime");
	g_sLangTxt_DvRcvOverTime = _T("装置响应超时【第%d次】");
	g_sLangID_HasNoRptCtrl = _T("sHasNoRptCtrl");
	g_sLangTxt_HasNoRptCtrl = _T("启动报告：不存在报告控制块");
	g_sLangID_RptCtrlHasStart = _T("sRptCtrlHasStart");
	g_sLangTxt_RptCtrlHasStart = _T("启动报告：报告控制块【%s】已经启动");
	g_sLangID_StartRptCtrlFinish = _T("sStartRptCtrlFinish");
	g_sLangTxt_StartRptCtrlFinish = _T("启动报告[%s]完成");
	g_sLangID_StartRptCtrlFail = _T("sStartRptCtrlFail");
	g_sLangTxt_StartRptCtrlFail = _T("启动报告[%s]失败");
	g_sLangID_HasNoNet = _T("sHasNoNet");
	g_sLangTxt_HasNoNet = _T("网络连接未创建.");
	g_sLangID_SetEdtZnFail = _T("sSetEdtZnFail");
	g_sLangTxt_SetEdtZnFail = _T("读定值区%d时，切换编辑区失败【运行区=%d】");
	g_sLangID_SetEdtZnRd = _T("sSetEdtZnRd");
	g_sLangTxt_SetEdtZnRd = _T("读定值区%d时，切换编辑区【运行区=%d】");
	g_sLangID_IndexAndTotal = _T("sIndexAndTotal");
	g_sLangTxt_IndexAndTotal = _T("第%d个  共%d个");
	g_sLangID_WritDataFail = _T("sWritDataFail");
	g_sLangTxt_WritDataFail = _T("写数据【%s】【%s】=【%s】失败");
	g_sLangID_WritDataSucc = _T("sWritDataSucc");
	g_sLangTxt_WritDataSucc = _T( "写数据成功");
	g_sLangID_WritDataPrgs = _T("sWritDataPrgs");
	g_sLangTxt_WritDataPrgs = _T("第%d，共%d 【%s】=【%s】");
	g_sLangID_BfExecNext = _T("sBfExecNext");
	g_sLangTxt_BfExecNext = _T("执行下一个参数修改前：");
	g_sLangID_EditDataFail = _T("sEditDataFail");
	g_sLangTxt_EditDataFail = _T("修改【%s】【%s】失败");
	g_sLangID_GetNexLdZn = _T("sGetNexLdZn");
	g_sLangTxt_GetNexLdZn = _T("获取下一个逻辑设备读取定值区:%d, %d");
	g_sLangID_NoLdHasZn = _T("sNoLdHasZn");
	g_sLangTxt_NoLdHasZn = _T("*****************没有定值区相关的逻辑设备*****************");
	g_sLangID_RdSetZnsFail = _T("sRdSetZnsFail");
	g_sLangTxt_RdSetZnsFail = _T("读取定值区数目失败.");
	g_sLangID_RdCurSetZnsFail = _T("sRdCurSetZnsFail");
	g_sLangTxt_RdCurSetZnsFail = _T("读取当前定值运行区号失败.");
	g_sLangID_SetCurSetZnFail = _T("sSetCurSetZnFail");
	g_sLangTxt_SetCurSetZnFail = _T("设置当前定值运行区号%d失败.");
	g_sLangID_SetCurSetZnSucc = _T("sSetCurSetZnSucc");
	g_sLangTxt_SetCurSetZnSucc = _T("设置当前定值运行区号%d成功.");
	g_sLangID_LdHasNoZn = _T("sLdHasNoZn");
	g_sLangTxt_LdHasNoZn = _T("逻辑设备【%s】无定值区号.");
	g_sLangID_SetCurEdtZnFail = _T("sSetCurEdtZnFail");
	g_sLangTxt_SetCurEdtZnFail = _T("【%d】设置当前编辑区【%d】失败.");
	g_sLangID_SetCurEdtZnSucc = _T("sSetCurEdtZnSucc");
	g_sLangTxt_SetCurEdtZnSucc = _T("【%d】设置当前编辑区【%d】成功.");
	g_sLangID_SolidZnFail = _T("sSolidZnFail");
	g_sLangTxt_SolidZnFail = _T("固化定值区【%d】失败");
	g_sLangID_SolidZnSucc = _T("sSolidZnSucc");
	g_sLangTxt_SolidZnSucc = _T("固化定值区【%d】成功");
	g_sLangID_SelEnaFail = _T("sSelEnaFail");
	g_sLangTxt_SelEnaFail = _T("选择压板【%s】【%d】失败");
	g_sLangID_SelEnaSucc = _T("sSelEnaSucc");
	g_sLangTxt_SelEnaSucc = _T("选择压板【%s】【%d】成功");
	g_sLangID_AfterSelEna = _T("sAfterSelEna");
	g_sLangTxt_AfterSelEna = _T("压板选择后：");
	g_sLangID_ExecEnaFail = _T("sExecEnaFail");
	g_sLangTxt_ExecEnaFail = _T("执行压板【%s】【%d】失败");
	g_sLangID_ExecEnaSucc = _T("sExecEnaSucc");
	g_sLangTxt_ExecEnaSucc = _T("执行压板【%s】【%d】成功");
	g_sLangID_EnaOptrTime = _T("sEnaOptrTime");
	g_sLangTxt_EnaOptrTime = _T("选择时间=%d   执行时间=%d");
	g_sLangID_WriteEnaParaErr = _T("sWriteEnaParaErr");
	g_sLangTxt_WriteEnaParaErr = _T("修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】");
	g_sLangID_EnaOptrFail = _T("sEnaOptrFail");
	g_sLangTxt_EnaOptrFail = _T("压板操作【%s】【%s】=【%s】失败 ");
	g_sLangID_DvResetFail = _T("sDvResetFail");
	g_sLangTxt_DvResetFail = _T("装置复归【%d】失败");
	g_sLangID_DvResetFailEx = _T("sDvResetFailEx");
	g_sLangTxt_DvResetFailEx = _T("装置复归【%d】【%s】【%s】失败");

	g_sLangTxt_FuncID_Connect = _T("联机");
	g_sLangID_FuncID_Connect = _T("sFuncID_Connect");
	g_sLangTxt_FuncID_DisConnect = _T("与设备断开连接");
	g_sLangID_FuncID__FuncID_DisConnect = _T("s_FuncID_DisConnect");
	g_sLangTxt_FuncID_WriteData = _T("写数据");
	g_sLangID_FuncID_WriteData = _T("sFuncID_WriteData");
	g_sLangTxt_FuncID_ReadData = _T("读数据");
	g_sLangID_FuncID_ReadData = _T("sFuncID_ReadData");
	g_sLangTxt_FuncID_StartRpt = _T("启动报告");
	g_sLangID_FuncID_StartRpt = _T("sFuncID_StartRpt");
	g_sLangTxt_FuncID_StopRpt = _T("停止报告");
	g_sLangID_FuncID_StopRpt = _T("sFuncID_StopRpt");
	g_sLangTxt_FuncID_GetRunZn = _T("获取当前运行区");
	g_sLangID_FuncID_GetRunZn = _T("sFuncID_GetRunZn");
	g_sLangTxt_FuncID_SetRunZn =  _T("设置当前运行区");
	g_sLangID_FuncID_SetRunZn =_T("sFuncID_SetRunZn");
	g_sLangTxt_FuncID_EnumDvDir = _T("枚举装置目录");
	g_sLangID_FuncID_EnumDvDir = _T("sFuncID_EnumDvDir");
	g_sLangTxt_FuncID_ChangeEditZn = _T("切换编辑定值区");
	g_sLangID_FuncID_ChangeEditZn = _T("sFuncID_ChangeEditZn");
	g_sLangTxt_FuncID_SolidEditZn = _T("固化编辑定值区");
	g_sLangID_FuncID_SolidEditZn = _T("sFuncID_SolidEditZn");


	g_sLangID_CreatMmsComm = _T("sCreatMmsComm");
	g_sLangTxt_CreatMmsComm = _T("创建为MMS通讯命令模式【%s】");
	g_sLangID_ReachMax = _T("sReachMax");
	g_sLangTxt_ReachMax = _T("可创建的设备数已经达到最上限，不能创建【%s】设备");
	g_sLangID_ReleasMmsComm = _T("sReleasMmsComm");
	g_sLangTxt_ReleasMmsComm = _T("释放MMS通讯命令模式【%s】");

// 	g_sLangID_CurrentActSet = _T("sCurrentActSet");
// 	g_sLangTxt_CurrentActSet = _T("当前活动定值区");
// 	g_sLangID_SettingTotalNo = _T("sSettingTotalNo");
// 	g_sLangTxt_SettingTotalNo = _T("定值区总数");
// 	g_sLangID_CommandTotalTime = _T("sCommandTotalTime");
// 	g_sLangTxt_CommandTotalTime = _T("命令总时间");
// 	g_sLangID_CommandExecuTime = _T("sCommandExecuTime");
// 	g_sLangTxt_CommandExecuTime = _T("命令执行时间");
// 	g_sLangID_CommandChoseTime = _T("sCCommandChoseTime");
// 	g_sLangTxt_CommandChoseTime = _T("命令选择时间");
// 	g_sLangID_CommandExecuMess = _T("sCommandExecuMess");
// 	g_sLangTxt_CommandExecuMess = _T("命令执行信息");
// 	g_sLangID_CommandChoseMess = _T("sCommandChoseMess");
// 	g_sLangTxt_CommandChoseMess = _T("命令选择信息");
// 	g_sLangID_WrongMess = _T("sWrongMess");
// 	g_sLangTxt_WrongMess = _T("错误信息");
// 	g_sLangID_RecordPath = _T("sRecordPath");
// 	g_sLangTxt_RecordPath = _T("录波路径");
// 	g_sLangID_EnaChangeTime = _T("sEnaChangeTime");
// 	g_sLangTxt_EnaChangeTime = _T("压板修改间隔时间");
// 	g_sLangID_EnaChoseTime = _T("sEnaChoseTime");
// 	g_sLangTxt_EnaChoseTime = _T("压板选择执行间隔时间");
// 	g_sLangID_MonitErrorTime = _T("sMonitErrorTime");
// 	g_sLangTxt_MonitErrorTime = _T("监视错误信息");
// 	g_sLangID_BeforEnaRead = _T("sBeforEnaRead");
// 	g_sLangTxt_BeforEnaRead = _T("投退压板前读状态");
// 	g_sLangID_BeforEnaReadTime = _T("sBeforEnaReadTime");
// 	g_sLangTxt_BeforEnaReadTime = _T("投退压板前读状态后延时");
// 
// 	g_sLangID_WritDataMess = _T("sWritDataMess");
// 	g_sLangTxt_WritDataMess = _T("写数据信息");
// 	g_sLangID_SetEdtTime = _T("sSetEdtTime");
// 	g_sLangTxt_SetEdtTime = _T("设置编辑区时间");
// 	g_sLangID_SetActTime = _T("sSetActTime");
// 	g_sLangTxt_SetActTime = _T("设置活动区时间");
// 	g_sLangID_SetEdtMess = _T("sSetEdtMess");
// 	g_sLangTxt_SetEdtMess = _T("设置编辑区信息");
// 	g_sLangID_SetActMess = _T("sSetActMess");
// 	g_sLangTxt_SetActMess = _T("设置活动区信息");
// 	g_sLangID_TestConnSta = _T("sTestConnSta");
// 	g_sLangTxt_TestConnSta = _T("测试连接状态");

	g_sLangID_ExecConnCommand = _T("sExecConnCommand");
	g_sLangTxt_ExecConnCommand = _T("执行外部通讯命令【%s】：ACSIDevice=%d  LdIndex=%d  DatasetIndex=%d");
	g_sLangID_DatasetPathError = _T("sDatasetPathError");
	g_sLangTxt_DatasetPathError = _T("数据集路径【%s】不正确");
	g_sLangID_Ena = _T("sEna");
	g_sLangTxt_Ena = _T("压板");
	g_sLangID_RemoteCtl = _T("sRemoteCtl");
	g_sLangTxt_RemoteCtl = _T("遥控");
	g_sLangID_UnRegRepDataSet = _T("sUnRegRepDataSet");
	g_sLangTxt_UnRegRepDataSet = _T("unregisterreport:数据集：%s");
	g_sLangID_SwitchSet = _T("sSwitchSet");
	g_sLangTxt_SwitchSet = _T("切换定值区：%d");
	g_sLangID_OnlyReadProp = _T("sOnlyReadProp");
	g_sLangTxt_OnlyReadProp = _T("属性【%s】为只读属性");
	g_sLangID_NoNeedCorect = _T("sNoNeedCorect");
	g_sLangTxt_NoNeedCorect = _T("没有需要修改的%s【%s】");
	g_sLangID_RegRepDataSetMiss = _T("sRegRepDataSetMiss");
	g_sLangTxt_RegRepDataSetMiss = _T("registerreport:数据集：%s 不存在");
	g_sLangID_StopRepDataSetMiss = _T("sStopRepDataSetMiss");
	g_sLangTxt_StopRepDataSetMiss = _T("stopreport:数据集：%s 不存在");

	g_sLangID_SendOverMesNotWin = _T("sSendOverMesNotWin");
	g_sLangTxt_SendOverMesNotWin = _T("发送测试完成消息 【%08x】 不是窗口");
	g_sLangID_SendOverMes = _T("sSendOverMes");
	g_sLangTxt_SendOverMes = _T("发送测试完成消息 WND=【%08x】 MSG=【%08x】");
	g_sLangID_DataNotExist = _T("sDataNotExist");
	g_sLangTxt_DataNotExist = _T("数据【%s】【%s】不存在");
	g_sLangID_RegistDataFail = _T("sRegistDataFail");
	g_sLangTxt_RegistDataFail = _T("RegisterDataChangedMsg(%s)失败");
	g_sLangID_RegistDataSuc  = _T("sRegistDataSuc");
	g_sLangTxt_RegistDataSuc = _T("RegisterDataChangedMsg(%s)成功");
	g_sLangID_CmdMsgFailWin = _T("sCmdMsgFailWin");
	g_sLangTxt_CmdMsgFailWin = _T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)失败：目标窗口不存在");
	g_sLangID_MapNotExist = _T("sMapNotExist");
	g_sLangTxt_MapNotExist = _T("数据集映射关系【%s】=【%s$%s】不存在");

	g_sLangID_ZnNumAndRunZn = _T("sZnNumAndRunZn");
	g_sLangTxt_ZnNumAndRunZn = _T("【%d】定值区数：%d;当前运行区：%d;");

}

//装置操作
CString g_sLangID_DeviceOperation                  ;  //= _T("sDeviceOperation");
CString g_sLangTxt_DeviceOperation                 ;  //= _T("装置操作");
CString g_sLangID_Online                           ;  //= _T("sOnline");
CString g_sLangTxt_Online                          ;  //= _T("联机");
CString g_sLangID_Disconnect                       ;  //= _T("sDisconnect");
CString g_sLangTxt_Disconnect                      ;  //= _T("断开");
CString g_sLangID_DisconnectTip                    ;  //= _T("sDisconnectTip");
CString g_sLangTxt_DisconnectTip                   ;  //= _T("断开装置\n断开装置");
CString g_sLangID_Return                           ;  //= _T("sReturn");
CString g_sLangTxt_Return                          ;  //= _T("复归");
//枚举
CString g_sLangID_Enum                             ;  //= _T("sEnum");
CString g_sLangTxt_Enum                            ;  //= _T("枚举");
CString g_sLangID_ReadNodes                 ;  //= _T("sReadNodes");
CString g_sLangTxt_ReadNodes                ;  //= _T("读取模型");
CString g_sLangID_ReadNodesTip              ;  //= _T("sReadNodesTip");
CString g_sLangTxt_ReadNodesTip             ;  //= _T("读取装置建模模型\n读取模型");
CString g_sLangID_RefreshDirectory                 ;  //= _T("sRefreshDirectory");
CString g_sLangTxt_RefreshDirectory                ;  //= _T("刷新目录");
CString g_sLangID_RefreshDirectoryTip              ;  //= _T("sRefreshDirectoryTip");
CString g_sLangTxt_RefreshDirectoryTip             ;  //= _T("刷新目录\n刷新");
CString g_sLangID_Device                           ;  //= _T("sDevice");
CString g_sLangTxt_Device                          ;  //= _T("装置");
CString g_sLangID_DeviceTip                        ;  //= _T("sDeviceTip");
CString g_sLangTxt_DeviceTip                       ;  //= _T("读设备全部数据\n读设备数据");
// CString g_sLangID_LogicDevice                      ;  //= _T("sLogicDevice");
// CString g_sLangTxt_LogicDevice                     ;  //= _T("逻辑设备");
CString g_sLangID_LogicDeviceTip                   ;  //= _T("sLogicDeviceTip");
CString g_sLangTxt_LogicDeviceTip                  ;  //= _T("读逻辑设备数据\n读逻辑设备");
CString g_sLangID_DataSetTip                       ;  //= _T("sDataSetTip");
CString g_sLangTxt_DataSetTip                      ;  //= _T("读当前数据\n读当前数据");
//数据值
CString g_sLangID_DataValue                        ;  //= _T("sDataValue");
CString g_sLangTxt_DataValue                       ;  //= _T("数据值");
CString g_sLangID_ReadData                         ;  //= _T("sReadData");
CString g_sLangTxt_ReadData                        ;  //= _T("读数据");
CString g_sLangID_ReadDataTip                      ;  //= _T("sReadDataTip");
CString g_sLangTxt_ReadDataTip                     ;  //= _T("获取数值\n获取数值");
CString g_sLangID_ModifyData                       ;  //= _T("sModifyData");
CString g_sLangTxt_ModifyData                      ;  //= _T("修改数据");
//定值区
CString g_sLangID_ReadFixedValueRegion             ;  //= _T("sReadFixedValueRegion");
CString g_sLangTxt_ReadFixedValueRegion            ;  //= _T("读定值区");
CString g_sLangID_ModifyFixedValueRegion           ;  //= _T("sModifyFixedValueRegion");
CString g_sLangTxt_ModifyFixedValueRegion          ;  //= _T("修改定值区");
//报告
CString g_sLangID_StartReportTip                   ;  //= _T("sStartReportTip");
CString g_sLangTxt_StartReportTip                  ;  //= _T("启动报告\n启动");
CString g_sLangID_StopReportTip                    ;  //= _T("sStopReportTip");
CString g_sLangTxt_StopReportTip                   ;  //= _T("停止报告\n停止");
CString g_sLangID_DebugAdd                         ;  //= _T("sDebugAdd");
CString g_sLangTxt_DebugAdd                        ;  //= _T("调试-添加");
CString g_sLangID_DebugAddTip                      ;  //= _T("sDebugAddTip");
CString g_sLangTxt_DebugAddTip                     ;  //= _T("添加到SOE报告(F2)\n添加到SOE报告");
//文件
CString g_sLangID_ExportModel                      ;  //= _T("sExportModel");
CString g_sLangTxt_ExportModel                     ;  //= _T("导出模型");
CString g_sLangID_ExportModelTip                   ;  //= _T("sExportModelTip");
CString g_sLangTxt_ExportModelTip                  ;  //= _T("导出设备模型为XML文件\n导出");
CString g_sLangID_ImportModel                      ;  //= _T("sImportModel");
CString g_sLangTxt_ImportModel                     ;  //= _T("导入模型");
CString g_sLangID_ExportMmsNodes                      ;  //= _T("sExportMmsNodes");
CString g_sLangTxt_ExportMmsNodes                    ;  //= _T("导出建模");
CString g_sLangID_ExportMmsNodesTip                   ;  //= _T("sExportMmsNodesTip");
CString g_sLangTxt_ExportMmsNodesTip                  ;  //= _T("导出设备建模模型为XML文件\n导出");
//视图
CString g_sLangID_DispMmsErrInfor                  ;  //= _T("sDispMmsErrInfor");
CString g_sLangTxt_DispMmsErrInfor                 ;  //= _T("显示MMS错误信息");
CString g_sLangID_DispMmsErrInforTip               ;  //= _T("sDispMmsErrInforTip");
CString g_sLangTxt_DispMmsErrInforTip              ;  //= _T("显示MMS错误信息\n显示MMS错误信息");
CString g_sLangID_ChangeAndRunArea                 ;  //= _T("sChangeAndRunArea");
CString g_sLangTxt_ChangeAndRunArea                ;  //= _T("能改运行区");
CString g_sLangID_PropertyBar                      ;  //= _T("sPropertyBar");
CString g_sLangTxt_PropertyBar                     ;  //= _T("属性栏");
CString g_sLangID_DeviceToolbar                    ;  //= _T("sDeviceToolbar");
CString g_sLangTxt_DeviceToolbar                   ;  //= _T("设备工具栏");
//启动报告
CString g_sLangID_RptTypeSel                       ;  //= _T("sRptTypeSel");
CString g_sLangTxt_RptTypeSel                      ;  //= _T("报告控制块类型选择");
CString g_sLangID_StartSendData                    ;  //= _T("sStartSendData");
CString g_sLangTxt_StartSendData                   ;  //= _T("启动上送报告数据");
CString g_sLangID_OptFldsSel                       ;  //= _T("sOptFldsSel");
CString g_sLangTxt_OptFldsSel                      ;  //= _T("OptFlds(2字节，0位保留)");
CString g_sLangID_SerialNumber                     ;  //= _T("sSerialNumber");
CString g_sLangTxt_SerialNumber                    ;  //= _T("1-序号");
CString g_sLangID_TimeScale                        ;  //= _T("sTimeScale");
CString g_sLangTxt_TimeScale                       ;  //= _T("2-报告生成时标");
CString g_sLangID_Reason                           ;  //= _T("sReason");
CString g_sLangTxt_Reason                          ;  //= _T("3-原因");
CString g_sLangID_DataSetName                      ;  //= _T("sDataSetName");
CString g_sLangTxt_DataSetName                     ;  //= _T("4-数据集名称");
CString g_sLangID_DataSetPath                      ;  //= _T("sDataSetPath");
CString g_sLangTxt_DataSetPath                     ;  //= _T("5-数据集路径");
CString g_sLangID_BufferOverflowFlag               ;  //= _T("sBufferOverflowFlag");
CString g_sLangTxt_BufferOverflowFlag              ;  //= _T("6-缓存溢出标志");
CString g_sLangID_ItemNum                          ;  //= _T("sItemNum");
CString g_sLangTxt_ItemNum                         ;  //= _T("7-条目号");
CString g_sLangID_ConfigNum                        ;  //= _T("sConfigNum");
CString g_sLangTxt_ConfigNum                       ;  //= _T("8-配置号");
CString g_sLangID_SubNumber                        ;  //= _T("sSubNumber");
CString g_sLangTxt_SubNumber                       ;  //= _T("9-子序号");
CString g_sLangID_TrgOpsSel                        ;  //= _T("sTrgOpsSel");
CString g_sLangTxt_TrgOpsSel                       ;  //= _T("TrgOpsSel(1字节，0位保留)");
CString g_sLangID_DataChange                       ;  //= _T("sDataChange");
CString g_sLangTxt_DataChange                      ;  //= _T("1-数据改变（变化上送）");
CString g_sLangID_QualityChange                    ;  //= _T("sQualityChange");
CString g_sLangTxt_QualityChange                   ;  //= _T("2-质量改变（例品质有效无效）");
CString g_sLangID_DataUpgrade                      ;  //= _T("sDataUpgrade");
CString g_sLangTxt_DataUpgrade                     ;  //= _T("3-数据升级");
CString g_sLangID_Integrity                        ;  //= _T("sIntegrity");
CString g_sLangTxt_Integrity                       ;  //= _T("4-完整性（周期上送）");
CString g_sLangID_GeneralCall                      ;  //= _T("sGeneralCall");
CString g_sLangTxt_GeneralCall                     ;  //= _T("5-总召唤（总召上送）");
//设置装置的当前运行组
CString g_sLangID_SetCurGrpDevice                  ;  //= _T("sSetCurGrpDevice");
CString g_sLangTxt_SetCurGrpDevice                 ;  //= _T("设置装置的当前运行组");
CString g_sLangID_FixedValueNum                    ;  //= _T("sFixedValueNum");
CString g_sLangTxt_FixedValueNum                   ;  //= _T("定值组号");

//和装置联机
CString g_sLangID_LinkSet                          ;  //= _T("sLinkSet");
CString g_sLangTxt_LinkSet                         ;  //= _T("和装置联机设置");
CString g_sLangID_IP                               ;  //= _T("sIP");
CString g_sLangTxt_IP                              ;  //= _T("装置IP地址");
CString g_sLangID_EnumRptCtrlBlk                   ;  //= _T("sEnumRptCtrlBlk");
CString g_sLangTxt_EnumRptCtrlBlk                  ;  //= _T("是否枚举报告控制块？");

//网卡IP设置
CString g_sLangID_NetwCardIpset                    ;  //= _T("sNetwCardIpset");
CString g_sLangTxt_NetwCardIpset                   ;  //= _T("网卡IP设置");
CString g_sLangID_NetwCardSel                      ;  //= _T("sNetwCardSel");
CString g_sLangTxt_NetwCardSel                     ;  //= _T("网卡选择");
CString g_sLangID_IpAddr                           ;  //= _T("sIpAddr");
CString g_sLangTxt_IpAddr                          ;  //= _T("IP地址");
CString g_sLangID_SubNetwMask                      ;  //= _T("sSubNetwMask");
CString g_sLangTxt_SubNetwMask                     ;  //= _T("子网掩码");
CString g_sLangID_AddIp                            ;  //= _T("sAddIp");
CString g_sLangTxt_AddIp                           ;  //= _T("添加IP");
CString g_sLangID_Ethernet                            ;  //= _T("sEthernet");
CString g_sLangTxt_Ethernet                           ;  //= _T("以太网");

//进度条
CString g_sLangID_InOperation                      ;  //= _T("sInOperation");
CString g_sLangTxt_InOperation                     ;  //= _T("处理中，请稍候");
CString g_sLangID_DataOperation                    ;  //= _T("sDataOperation");
CString g_sLangTxt_DataOperation                   ;  //= _T("数据操作中...");
//选择路径
CString g_sLangID_SelPath                          ;  //= _T("sSelPath");
CString g_sLangTxt_SelPath                         ;  //= _T("选择路径");
//选择定值区
CString g_sLangID_SelValueZone                     ;  //= _T("sSelValueZone");
CString g_sLangTxt_SelValueZone                    ;  //= _T("选择定值区");
CString g_sLangID_OperationZone                    ;  //= _T("sOperationZone");
CString g_sLangTxt_OperationZone                   ;  //= _T("运行区");
//自动匹配数据集查看
CString g_sLangID_AutoMatchView                    ;  //= _T("sAutoMatchView");
CString g_sLangTxt_AutoMatchView                   ;  //= _T("自动匹配数据集查看");
//BrcbCtrlDlg里的输出信息
CString g_sLangID_NotEnum                          ;  //= _T("sNotEnum");
CString g_sLangTxt_NotEnum                         ;  //= _T("没有枚举数据，不能设置报告召唤");
//DlgSelPath里的输出信息
CString g_sLangID_EnterPath                        ;  //= _T("sEnterPath");
CString g_sLangTxt_EnterPath                       ;  //= _T("请输入路径");
//IPSetObj里的输出信息
CString g_sLangID_FileOprtFail                     ;  //= _T("sFileOprtFail");
CString g_sLangTxt_FileOprtFail                    ;  //= _T("VMD.INI 文件操作失败!");
//LinkSetDlg里的输出信息
CString g_sLangID_RestartAndLink                   ;  //= _T("sRestartAndLink");
CString g_sLangTxt_RestartAndLink                  ;  //= _T("装置ip已发生改变,请重启程序再联机!");
//LocalIpSetDlg里的输出信息
CString g_sLangID_ResetIP                          ;  //= _T("sResetIP");
CString g_sLangTxt_ResetIP                         ;  //= _T("当前设置的IP已经存在,请重新设置!");
//MainFrm里的输出信息
CString g_sLangID_MmsPtclPrgm                      ;  //= _T("sMmsPtclPrgm");
CString g_sLangTxt_MmsPtclPrgm                     ;  //= _T("61850MMS规约引擎程序");
CString g_sLangID_DeviceListView                   ;  //= _T("sDeviceListView");
CString g_sLangTxt_DeviceListView                  ;  //= _T("设备列表视图");
CString g_sLangID_SelDeviceObj                     ;  //= _T("sSelDeviceObj");
CString g_sLangTxt_SelDeviceObj                    ;  //= _T("请选择设备对象");
CString g_sLangID_NoFixedValueRegion               ;  //= _T("sNoFixedValueRegion");
CString g_sLangTxt_NoFixedValueRegion              ;  //= _T("【%s】没有定义定值区");
CString g_sLangID_DeviceMdlFile                    ;  //= _T("sDeviceMdlFile");
CString g_sLangTxt_DeviceMdlFile                   ;  //= _T("设备模型文件（xml)|*.xml|");
CString g_sLangID_SendSuccMsg                      ;  //= _T("sSendSuccMsg");
CString g_sLangTxt_SendSuccMsg                     ;  //= _T("+++++++++++发送连接设备成功消息+++++++++++");
CString g_sLangID_SendCommMsg                      ;  //= _T("sSendCommMsg");
CString g_sLangTxt_SendCommMsg                     ;  //= _T("发送通讯消息：wParam;  //=%d  lParam;  //=%d");
CString g_sLangID_SendSySMsg                       ;  //= _T("sSendSySMsg");
CString g_sLangTxt_SendSySMsg                      ;  //= _T("发送系统消息：wParam;  //=%d  lParam;  //=%d");
CString g_sLangID_SetFixedValueRegionFail          ;  //= _T("sSetFixedValueRegionFail");
CString g_sLangTxt_SetFixedValueRegionFail         ;  //= _T("【%d】设置当前定值运行区号%d失败【Error】");
CString g_sLangID_SetFixedValueRegion              ;  //= _T("sSetFixedValueRegion");
CString g_sLangTxt_SetFixedValueRegion             ;  //= _T("设置当前运行定值区为%d");
CString g_sLangID_EditFixedValueRegionSucc         ;  //= _T("sEditFixedValueRegionSucc");
CString g_sLangTxt_EditFixedValueRegionSucc        ;  //= _T("切换编辑定值区%d成功");
CString g_sLangID_EditFixedValueRegionFail         ;  //= _T("sEditFixedValueRegionFail");
CString g_sLangTxt_EditFixedValueRegionFail        ;  //= _T("切换编辑定值区%d失败【Error】");
CString g_sLangID_SolidFixedValueRegionSucc        ;  //= _T("sSolidFixedValueRegionSucc");
CString g_sLangTxt_SolidFixedValueRegionSucc       ;  //= _T("固化定值区%d定值成功");
CString g_sLangID_SolidFixedValueRegionFail        ;  //= _T("sSolidFixedValueRegionFail");
CString g_sLangTxt_SolidFixedValueRegionFail       ;  //= _T("固化定值区%d定值失败【Error】");
CString g_sLangID_CtrlWriteSucc                    ;  //= _T("sCtrlWriteSucc");
CString g_sLangTxt_CtrlWriteSucc                   ;  //= _T("控制写成功");
CString g_sLangID_CtrlWriteFail                    ;  //= _T("sCtrlWriteFail");
CString g_sLangTxt_CtrlWriteFail                   ;  //= _T("控制写失败【Error】");
CString g_sLangID_DeviceReturnSucc                 ;  //= _T("sDeviceReturnSucc");
CString g_sLangTxt_DeviceReturnSucc                ;  //= _T("装置复归成功");
CString g_sLangID_DeviceReturnFail                 ;  //= _T("sDeviceReturnFail");
CString g_sLangTxt_DeviceReturnFail                ;  //= _T("装置复归失败【Error】");
CString g_sLangID_AllCommandExecuted               ;  //= _T("sAllCommandExecuted");
CString g_sLangTxt_AllCommandExecuted              ;  //= _T("自动测试模式，命令全部执行完毕!!");
//MmsDeviceTreeCtrl里的输出信息
CString g_sLangID_MmsNodes                     ;  //= _T("sMmsNodes");
CString g_sLangTxt_MmsNodes                    ;  //= _T("建模模型");
CString g_sLangID_RecdWaveFile                     ;  //= _T("sRecdWaveFile");
CString g_sLangTxt_RecdWaveFile                    ;  //= _T("录波文件");
CString g_sLangID_LogRecord                        ;  //= _T("sLogRecord");
CString g_sLangTxt_LogRecord                       ;  //= _T("日志记录");
CString g_sLangID_TooMuchActualDevice              ;  //= _T("sTooMuchActualDevice");
CString g_sLangTxt_TooMuchActualDevice             ;  //= _T("实际装置数大于假设最大装置数!");
//NodeView里的输出信息
CString g_sLangID_Attributes                       ;  //= _T("sAttributes");
CString g_sLangTxt_Attributes                      ;  //= _T("属性....");
CString g_sLangID_UnableloadBitmap                 ;  //= _T("sUnableloadBitmap");
CString g_sLangTxt_UnableloadBitmap                ;  //= _T("无法加载位图: %x\n");
//OutputWnd里的输出信息
CString g_sLangID_Log                              ;  //= _T("sLog");
CString g_sLangTxt_Log                             ;  //= _T("日志");
CString g_sLangID_ReportD                          ;  //= _T("sReportD");
CString g_sLangTxt_ReportD                         ;  //= _T("报告%d");
CString g_sLangID_SoeReportD                          ;  //= _T("sSoeReportD");
CString g_sLangTxt_SoeReportD                         ;  //= _T("装置事件");
CString g_sLangID_Date                             ;  //= _T("sDate");
CString g_sLangTxt_Date                            ;  //= _T("%d年-%d月-%d日-%d时-%d分-%d秒：%s");
CString g_sLangID_TimeDiffer                       ;  //= _T("sTimeDiffer");
CString g_sLangTxt_TimeDiffer                      ;  //= _T("时差ms");
CString g_sLangID_DetailedInfor                    ;  //= _T("sDetailedInfor");
CString g_sLangTxt_DetailedInfor                   ;  //= _T("详细信息");
//PpMmsEngine的输出信息
CString g_sLangID_InitSocketFailed                 ;  //= _T("sInitSocketFailed");
CString g_sLangTxt_InitSocketFailed                ;  //= _T("初始化SOCKET失败！");
CString g_sLangID_WizardGeneratedApp               ;  //= _T("sWizardGeneratedApp");
CString g_sLangTxt_WizardGeneratedApp              ;  //= _T("应用程序向导生成的本地应用程序");
CString g_sLangID_Unknown                          ;  //= _T("sUnknown");
CString g_sLangTxt_Unknown                         ;  //= _T("未知");
CString g_sLangID_ReadDeviceDataComplete           ;  //= _T("sReadDeviceDataComplete");
CString g_sLangTxt_ReadDeviceDataComplete          ;  //= _T("读取装置数据完成!");
CString g_sLangID_Monitor                          ;  //= _T("sMonitor");
CString g_sLangTxt_Monitor                         ;  //= _T("监视【%d】 RunSGIndex;  //=【%08x】");
CString g_sLangID_NotEnumDataSet                   ;  //= _T("sNotEnumDataSet");
CString g_sLangTxt_NotEnumDataSet                  ;  //= _T("【%d-%d-%d】没有枚举数据集");
CString g_sLangID_TotalStep1                       ;  //= _T("sTotalStep1");
CString g_sLangTxt_TotalStep1                      ;  //= _T("第%d步 共%d步 ： %s");
CString g_sLangID_TotalStep2                       ;  //= _T("sTotalStep2");
CString g_sLangTxt_TotalStep2                      ;  //= _T("第%d步 共%d步 ： 设备%d - 逻辑设备%d - %s - %s");
CString g_sLangID_Links                            ;  //= _T("sLinks");
CString g_sLangTxt_Links                           ;  //= _T("联机：%s");
CString g_sLangID_CommProcessing                   ;  //= _T("sCommProcessing");
CString g_sLangTxt_CommProcessing                  ;  //= _T("MMS通讯处理中，请稍候............");
CString g_sLangID_ProgmInilFail                    ;  //= _T("sProgmInilFail");
CString g_sLangTxt_ProgmInilFail                   ;  //= _T("程序初始化失败!                ");
CString g_sLangID_ProgmRun                         ;  //= _T("sProgmRun");
CString g_sLangTxt_ProgmRun                        ;  //= _T("“%s”程序正在运行...");
//PpMmsEngineView里的输出信息
CString g_sLangID_DaXiao                           ;  //= _T("sDaXiao");
CString g_sLangTxt_DaXiao                          ;  //= _T("大小");
//ZoneSelDlg里的输出信息
CString g_sLangID_RegionD                           ;  //= _T("sRegionD");
CString g_sLangTxt_RegionD                          ;  //= _T("区-%d");

CString g_sLangTxt_Menu_32777 ;  //= _T("启动报告(&B)	Ctrl+B");
CString g_sLangTxt_Menu_32778 ;  //= _T("停止报告(&P)	Ctrl+P");
CString g_sLangTxt_Menu_32794 ;  //= _T("调试模式(&D)");
CString g_sLangTxt_Menu_32795 ;  //= _T("显示调试信息(&V)");
CString g_sLangTxt_Menu_32797 ;  //= _T("调试-通讯失败(&F)");
CString g_sLangTxt_Menu_32804 ;  //= _T("添加到SOE报告");
CString g_sLangTxt_Menu_32796 ;  //= _T("单一设备模式(&S)");
CString g_sLangTxt_Menu_32786 ;  //= _T("读测量值使用报告数据");
CString g_sLangTxt_Menu_32798 ;  //= _T("复归命令只清空报告数据");
CString g_sLangID_Menu_32777 ;  //= _T("sMenu_32777");
CString g_sLangID_Menu_32778 ;  //= _T("sMenu_32778");
CString g_sLangID_Menu_32794 ;  //= _T("sMenu_32794");
CString g_sLangID_Menu_32795 ;  //= _T("sMenu_32795");
CString g_sLangID_Menu_32797 ;  //= _T("sMenu_32797");
CString g_sLangID_Menu_32804 ;  //= _T("sMenu_32804");
CString g_sLangID_Menu_32796 ;  //= _T("sMenu_32796");
CString g_sLangID_Menu_32786 ;  //= _T("sMenu_32786");
CString g_sLangID_Menu_32798 ;  //= _T("sMenu_32798");

CString g_sLangID_HadNoDataNeedEdit ;  //= _T("sHadNoDataNeedEdit");
CString g_sLangTxt_HadNoDataNeedEdit ;  //= _T("没有需要修改的数据");
CString g_sLangID_ReadDeviceDirSucc ;  //= _T("sReadDeviceDirSucc");
CString g_sLangTxt_ReadDeviceDirSucc ;  //= _T("枚举装置目录成功.");
CString g_sLangID_ReadDeviceDirFail ;  //= _T("sReadDeviceDirFail");
CString g_sLangTxt_ReadDeviceDirFail ;  //= _T("枚举装置目录失败.");
CString g_sLangID_SetZoneFail ;  //= _T("sSetZoneFail");
CString g_sLangTxt_SetZoneFail ;  //= _T("设置当前定值运行区号失败!");
CString g_sLangID_ConnectSucc ;  //= _T("sConnectSucc");
CString g_sLangTxt_ConnectSucc ;  //= _T("和装置联机成功.");
CString g_sLangID_ConnectFail ;  //= _T("sConnectFail");
CString g_sLangTxt_ConnectFail ;  //= _T("和装置联机失败【Error】.");
CString g_sLangID_DisConnectSucc ;  //= _T("sDisConnectSucc");
CString g_sLangTxt_DisConnectSucc ;  //= _T("和装置断开连接成功.");
CString g_sLangID_DisConnectFail ;  //= _T("sDisConnectFail");
CString g_sLangTxt_DisConnectFail ;  //= _T("和装置断开连接失败【Error】.");
CString g_sLangID_RdDatasetSucc ;  //= _T("sRdDatasetSucc");
CString g_sLangTxt_RdDatasetSucc ;  //= _T("读数据集成功.");
CString g_sLangID_RdDatasetFail ;  //= _T("sRdDatasetFail");
CString g_sLangTxt_RdDatasetFail ;  //= _T("读数据集失败【Error】.");
CString g_sLangID_ReadRecorDirFail ;  //= _T("sReadRecorDirFail");
CString g_sLangTxt_ReadRecorDirFail ;  //= _T("读录波文件目录失败.");
CString g_sLangID_ReadRecordDirSucc ;  //= _T("sReadRecordDirSucc");
CString g_sLangTxt_ReadRecordDirSucc ;  //= _T("读录波文件目录成功.");
CString g_sLangID_ReadRecordFileSucc ;  //= _T("sReadRecordFileSucc");
CString g_sLangTxt_ReadRecordFileSucc ;  //= _T("读录波文件成功.");
CString g_sLangID_ReadRecordFileFail ;  //= _T("sReadRecordFileFail");
CString g_sLangTxt_ReadRecordFileFail ;  //= _T("读录波文件失败.");
CString g_sLangID_WriteDataFail ;  //= _T("sWriteDataFail");
CString g_sLangTxt_WriteDataFail ;  //= _T("写数据失败【Error】.");
CString g_sLangID_WriteDataSucc ;  //= _T("sWriteDataSucc");
CString g_sLangID_StartRptFail ;  //= _T("sStartRptFail");
CString g_sLangTxt_WriteDataSucc ;  //= _T("写数据成功.");
CString g_sLangTxt_StartRptFail ;  //= _T("启动报告失败【Error】.");
CString g_sLangID_StartRptSucc ;  //= _T("sStartRptSucc");
CString g_sLangTxt_StartRptSucc ;  //= _T("启动报告成功.");
CString g_sLangID_StopRptFail ;  //= _T("sStopRptFail");
CString g_sLangTxt_StopRptFail ;  //= _T("停止报告失败【Error】.");
CString g_sLangID_StopRptSucc ;  //= _T("sStopRptSucc");
CString g_sLangTxt_StopRptSucc ;  //= _T("停止报告成功.");
CString g_sLangID_ReadZoneFail ;  //= _T("sReadZoneFail");
CString g_sLangTxt_ReadZoneFail ;  //= _T("获取当前定值运行区号失败.");
CString g_sLangID_NetConnect ;  //= _T("sNetConnect");
CString g_sLangTxt_NetConnect ;  //= _T("网络连接正常.");
CString g_sLangID_NetDisConnect ;  //= _T("sNetDisConnect");
CString g_sLangTxt_NetDisConnect ;  //= _T("网络连接断开.");

CString g_sLangID_Menu_57634 ;  //= _T("sMenu_57634");
CString g_sLangTxt_Menu_57634 ;  //= _T("复制(&C)");
CString g_sLangID_Menu_57632 ;  //= _T("sMenu_57632");
CString g_sLangTxt_Menu_57632 ;  //= _T("清除(&C)");
CString g_sLangID_Menu_149 ;  //= _T("sMenu_149");
CString g_sLangTxt_Menu_149 ;  //= _T("隐藏(&H)");

CString g_sLangID_WriteDataAfterWait ;  //= _T("sWriteDataAfterWait");
CString g_sLangTxt_WriteDataAfterWait ;  //= _T("%s:%s:等待%d毫秒");
CString g_sLangID_DvRcvOverTime ;  //= _T("sDvRcvOverTime");
CString g_sLangTxt_DvRcvOverTime ;  //= _T("装置响应超时【第%d次】");
CString g_sLangID_HasNoRptCtrl ;  //= _T("sHasNoRptCtrl");
CString g_sLangTxt_HasNoRptCtrl ;  //= _T("启动报告：不存在报告控制块");
CString g_sLangID_RptCtrlHasStart ;  //= _T("sRptCtrlHasStart");
CString g_sLangTxt_RptCtrlHasStart ;  //= _T("启动报告：报告控制块【%s】已经启动");
CString g_sLangID_StartRptCtrlFinish ;  //= _T("sStartRptCtrlFinish");
CString g_sLangTxt_StartRptCtrlFinish ;  //= _T("启动报告[%s]完成");
CString g_sLangID_StartRptCtrlFail ;  //= _T("sStartRptCtrlFail");
CString g_sLangTxt_StartRptCtrlFail ;  //= _T("启动报告[%s]失败");
CString g_sLangID_HasNoNet ;  //= _T("sHasNoNet");
CString g_sLangTxt_HasNoNet ;  //= _T("网络连接未创建.");
CString g_sLangID_SetEdtZnFail ;  //= _T("sSetEdtZnFail");
CString g_sLangTxt_SetEdtZnFail ;  //= _T("读定值区%d时，切换编辑区失败【运行区;  //=%d】");
CString g_sLangID_SetEdtZnRd ;  //= _T("sSetEdtZnRd");
CString g_sLangTxt_SetEdtZnRd ;  //= _T("读定值区%d时，切换编辑区【运行区;  //=%d】");
CString g_sLangID_IndexAndTotal ;  //= _T("sIndexAndTotal");
CString g_sLangTxt_IndexAndTotal ;  //= _T("第%d个  共%d个");
CString g_sLangID_WritDataFail ;  //= _T("sWritDataFail");
CString g_sLangTxt_WritDataFail ;  //= _T("写数据【%s】【%s】;  //=【%s】失败");
CString g_sLangID_WritDataSucc ;  //= _T("sWritDataSucc");
CString g_sLangTxt_WritDataSucc ;  //= _T( "写数据成功");
CString g_sLangID_WritDataPrgs ;  //= _T("sWritDataPrgs");
CString g_sLangTxt_WritDataPrgs ;  //= _T("第%d，共%d 【%s】;  //=【%s】");
CString g_sLangID_BfExecNext ;  //= _T("sBfExecNext");
CString g_sLangTxt_BfExecNext ;  //= _T("执行下一个参数修改前：");
CString g_sLangID_EditDataFail ;  //= _T("sEditDataFail");
CString g_sLangTxt_EditDataFail ;  //= _T("修改【%s】【%s】失败");
CString g_sLangID_GetNexLdZn ;  //= _T("sGetNexLdZn");
CString g_sLangTxt_GetNexLdZn ;  //= _T("获取下一个逻辑设备读取定值区:%d, %d");
CString g_sLangID_NoLdHasZn ;  //= _T("sNoLdHasZn");
CString g_sLangTxt_NoLdHasZn ;  //= _T("*****************没有定值区相关的逻辑设备*****************");
CString g_sLangID_RdSetZnsFail ;  //= _T("sRdSetZnsFail");
CString g_sLangTxt_RdSetZnsFail ;  //= _T("读取定值区数目失败.");
CString g_sLangID_RdCurSetZnsFail ;  //= _T("sRdCurSetZnsFail");
CString g_sLangTxt_RdCurSetZnsFail ;  //= _T("读取当前定值运行区号失败.");
CString g_sLangID_SetCurSetZnFail ;  //= _T("sSetCurSetZnFail");
CString g_sLangTxt_SetCurSetZnFail ;  //= _T("设置当前定值运行区号%d失败.");
CString g_sLangID_SetCurSetZnSucc ;  //= _T("sSetCurSetZnSucc");
CString g_sLangTxt_SetCurSetZnSucc ;  //= _T("设置当前定值运行区号%d成功.");
CString g_sLangID_LdHasNoZn ;  //= _T("sLdHasNoZn");
CString g_sLangTxt_LdHasNoZn ;  //= _T("逻辑设备【%s】无定值区号.");
CString g_sLangID_SetCurEdtZnFail ;  //= _T("sSetCurEdtZnFail");
CString g_sLangTxt_SetCurEdtZnFail ;  //= _T("【%d】设置当前编辑区【%d】失败.");
CString g_sLangID_SetCurEdtZnSucc ;  //= _T("sSetCurEdtZnSucc");
CString g_sLangTxt_SetCurEdtZnSucc ;  //= _T("【%d】设置当前编辑区【%d】成功.");
CString g_sLangID_SolidZnFail ;  //= _T("sSolidZnFail");
CString g_sLangTxt_SolidZnFail ;  //= _T("固化定值区【%d】失败");
CString g_sLangID_SolidZnSucc ;  //= _T("sSolidZnSucc");
CString g_sLangTxt_SolidZnSucc ;  //= _T("固化定值区【%d】成功");
CString g_sLangID_SelEnaFail ;  //= _T("sSelEnaFail");
CString g_sLangTxt_SelEnaFail ;  //= _T("选择压板【%s】【%d】失败");
CString g_sLangID_SelEnaSucc ;  //= _T("sSelEnaSucc");
CString g_sLangTxt_SelEnaSucc ;  //= _T("选择压板【%s】【%d】成功");
CString g_sLangID_AfterSelEna ;  //= _T("sAfterSelEna");
CString g_sLangTxt_AfterSelEna ;  //= _T("压板选择后：");
CString g_sLangID_ExecEnaFail ;  //= _T("sExecEnaFail");
CString g_sLangTxt_ExecEnaFail ;  //= _T("执行压板【%s】【%d】失败");
CString g_sLangID_ExecEnaSucc ;  //= _T("sExecEnaSucc");
CString g_sLangTxt_ExecEnaSucc ;  //= _T("执行压板【%s】【%d】成功");
CString g_sLangID_EnaOptrTime ;  //= _T("sEnaOptrTime");
CString g_sLangTxt_EnaOptrTime ;  //= _T("选择时间;  //=%d   执行时间;  //=%d");
CString g_sLangID_WriteEnaParaErr ;  //= _T("sWriteEnaParaErr");
CString g_sLangTxt_WriteEnaParaErr ;  //= _T("修改压板命令参数错误【Dev;  //=%d  LD;  //=%d DS;  //=%d  DA;  //=%d】");
CString g_sLangID_EnaOptrFail ;  //= _T("sEnaOptrFail");
CString g_sLangTxt_EnaOptrFail ;  //= _T("压板操作【%s】【%s】;  //=【%s】失败 ");
CString g_sLangID_DvResetFail ;  //= _T("sDvResetFail");
CString g_sLangTxt_DvResetFail ;  //= _T("装置复归【%d】失败");
CString g_sLangID_DvResetFailEx ;  //= _T("sDvResetFailEx");
CString g_sLangTxt_DvResetFailEx ;  //= _T("装置复归【%d】【%s】【%s】失败");

CString g_sLangTxt_FuncID_Connect ;  //= _T("联机");
CString g_sLangID_FuncID_Connect ;  //= _T("sFuncID_Connect");
CString g_sLangTxt_FuncID_DisConnect ;  //= _T("与设备断开连接");
CString g_sLangID_FuncID__FuncID_DisConnect ;  //= _T("s_FuncID_DisConnect");
CString g_sLangTxt_FuncID_WriteData ;  //= _T("写数据");
CString g_sLangID_FuncID_WriteData ;  //= _T("sFuncID_WriteData");
CString g_sLangTxt_FuncID_ReadData ;  //= _T("读数据");
CString g_sLangID_FuncID_ReadData ;  //= _T("sFuncID_ReadData");
CString g_sLangTxt_FuncID_StartRpt ;  //= _T("启动报告");
CString g_sLangID_FuncID_StartRpt ;  //= _T("sFuncID_StartRpt");
CString g_sLangTxt_FuncID_StopRpt ;  //= _T("停止报告");
CString g_sLangID_FuncID_StopRpt ;  //= _T("sFuncID_StopRpt");
CString g_sLangTxt_FuncID_GetRunZn ;  //= _T("获取当前运行区");
CString g_sLangID_FuncID_GetRunZn ;  //= _T("sFuncID_GetRunZn");
CString g_sLangTxt_FuncID_SetRunZn ;  //=  _T("设置当前运行区");
CString g_sLangID_FuncID_SetRunZn ;  //=_T("sFuncID_SetRunZn");
CString g_sLangTxt_FuncID_EnumDvDir ;  //= _T("枚举装置目录");
CString g_sLangID_FuncID_EnumDvDir ;  //= _T("sFuncID_EnumDvDir");
CString g_sLangTxt_FuncID_ChangeEditZn ;  //= _T("切换编辑定值区");
CString g_sLangID_FuncID_ChangeEditZn ;  //= _T("sFuncID_ChangeEditZn");
CString g_sLangTxt_FuncID_SolidEditZn ;  //= _T("固化编辑定值区");
CString g_sLangID_FuncID_SolidEditZn ;  //= _T("sFuncID_SolidEditZn");


CString g_sLangID_CreatMmsComm ;  //= _T("sCreatMmsComm");
CString g_sLangTxt_CreatMmsComm ;  //= _T("创建为MMS通讯命令模式【%s】");
CString g_sLangID_ReachMax ;  //= _T("sReachMax");
CString g_sLangTxt_ReachMax ;  //= _T("可创建的设备数已经达到最上限，不能创建【%s】设备");
CString g_sLangID_ReleasMmsComm ;  //= _T("sReleasMmsComm");
CString g_sLangTxt_ReleasMmsComm ;  //= _T("释放MMS通讯命令模式【%s】");

// CString g_sLangID_CurrentActSet ;  //= _T("sCurrentActSet");
// CString g_sLangTxt_CurrentActSet ;  //= _T("当前活动定值区");
// CString g_sLangID_SettingTotalNo ;  //= _T("sSettingTotalNo");
// CString g_sLangTxt_SettingTotalNo ;  //= _T("定值区总数");
// CString g_sLangID_CommandTotalTime ;  //= _T("sCommandTotalTime");
// CString g_sLangTxt_CommandTotalTime ;  //= _T("命令总时间");
// CString g_sLangID_CommandExecuTime ;  //= _T("sCommandExecuTime");
// CString g_sLangTxt_CommandExecuTime ;  //= _T("命令执行时间");
// CString g_sLangID_CommandChoseTime ;  //= _T("sCCommandChoseTime");
// CString g_sLangTxt_CommandChoseTime ;  //= _T("命令选择时间");
// CString g_sLangID_CommandExecuMess ;  //= _T("sCommandExecuMess");
// CString g_sLangTxt_CommandExecuMess ;  //= _T("命令执行信息");
// CString g_sLangID_CommandChoseMess ;  //= _T("sCommandChoseMess");
// CString g_sLangTxt_CommandChoseMess ;  //= _T("命令选择信息");
// CString g_sLangID_WrongMess ;  //= _T("sWrongMess");
// CString g_sLangTxt_WrongMess ;  //= _T("错误信息");
// CString g_sLangID_RecordPath ;  //= _T("sRecordPath");
// CString g_sLangTxt_RecordPath ;  //= _T("录波路径");
// CString g_sLangID_EnaChangeTime ;  //= _T("sEnaChangeTime");
// CString g_sLangTxt_EnaChangeTime ;  //= _T("压板修改间隔时间");
// CString g_sLangID_EnaChoseTime ;  //= _T("sEnaChoseTime");
// CString g_sLangTxt_EnaChoseTime ;  //= _T("压板选择执行间隔时间");
// CString g_sLangID_MonitErrorTime ;  //= _T("sMonitErrorTime");
// CString g_sLangTxt_MonitErrorTime ;  //= _T("监视错误信息");
// CString g_sLangID_BeforEnaRead ;  //= _T("sBeforEnaRead");
// CString g_sLangTxt_BeforEnaRead ;  //= _T("投退压板前读状态");
// CString g_sLangID_BeforEnaReadTime ;  //= _T("sBeforEnaReadTime");
// CString g_sLangTxt_BeforEnaReadTime ;  //= _T("投退压板前读状态后延时");
// 
// CString g_sLangID_WritDataMess ;  //= _T("sWritDataMess");
// CString g_sLangTxt_WritDataMess ;  //= _T("写数据信息");
// CString g_sLangID_SetEdtTime ;  //= _T("sSetEdtTime");
// CString g_sLangTxt_SetEdtTime ;  //= _T("设置编辑区时间");
// CString g_sLangID_SetActTime ;  //= _T("sSetActTime");
// CString g_sLangTxt_SetActTime ;  //= _T("设置活动区时间");
// CString g_sLangID_SetEdtMess ;  //= _T("sSetEdtMess");
// CString g_sLangTxt_SetEdtMess ;  //= _T("设置编辑区信息");
// CString g_sLangID_SetActMess ;  //= _T("sSetActMess");
// CString g_sLangTxt_SetActMess ;  //= _T("设置活动区信息");
// CString g_sLangID_TestConnSta ;  //= _T("sTestConnSta");
// CString g_sLangTxt_TestConnSta ;  //= _T("测试连接状态");

CString g_sLangID_ExecConnCommand ;  //= _T("sExecConnCommand");
CString g_sLangTxt_ExecConnCommand ;  //= _T("执行外部通讯命令【%s】：ACSIDevice;  //=%d  LdIndex;  //=%d  DatasetIndex;  //=%d");
CString g_sLangID_DatasetPathError ;  //= _T("sDatasetPathError");
CString g_sLangTxt_DatasetPathError ;  //= _T("数据集路径【%s】不正确");
CString g_sLangID_Ena ;  //= _T("sEna");
CString g_sLangTxt_Ena ;  //= _T("压板");
CString g_sLangID_RemoteCtl ;  //= _T("sRemoteCtl");
CString g_sLangTxt_RemoteCtl ;  //= _T("遥控");
CString g_sLangID_UnRegRepDataSet ;  //= _T("sUnRegRepDataSet");
CString g_sLangTxt_UnRegRepDataSet ;  //= _T("unregisterreport:数据集：%s");
CString g_sLangID_SwitchSet ;  //= _T("sSwitchSet");
CString g_sLangTxt_SwitchSet ;  //= _T("切换定值区：%d");
CString g_sLangID_OnlyReadProp ;  //= _T("sOnlyReadProp");
CString g_sLangTxt_OnlyReadProp ;  //= _T("属性【%s】为只读属性");
CString g_sLangID_NoNeedCorect ;  //= _T("sNoNeedCorect");
CString g_sLangTxt_NoNeedCorect ;  //= _T("没有需要修改的%s【%s】");
CString g_sLangID_RegRepDataSetMiss ;  //= _T("sRegRepDataSetMiss");
CString g_sLangTxt_RegRepDataSetMiss ;  //= _T("registerreport:数据集：%s 不存在");
CString g_sLangID_StopRepDataSetMiss ;  //= _T("sStopRepDataSetMiss");
CString g_sLangTxt_StopRepDataSetMiss ;  //= _T("stopreport:数据集：%s 不存在");

CString g_sLangID_SendOverMesNotWin ;  //= _T("sSendOverMesNotWin");
CString g_sLangTxt_SendOverMesNotWin ;  //= _T("发送测试完成消息 【%08x】 不是窗口");
CString g_sLangID_SendOverMes ;  //= _T("sSendOverMes");
CString g_sLangTxt_SendOverMes ;  //= _T("发送测试完成消息 WND;  //=【%08x】 MSG;  //=【%08x】");
CString g_sLangID_DataNotExist ;  //= _T("sDataNotExist");
CString g_sLangTxt_DataNotExist ;  //= _T("数据【%s】【%s】不存在");
CString g_sLangID_RegistDataFail ;  //= _T("sRegistDataFail");
CString g_sLangTxt_RegistDataFail ;  //= _T("RegisterDataChangedMsg(%s)失败");
CString g_sLangID_RegistDataSuc  ;  //= _T("sRegistDataSuc");
CString g_sLangTxt_RegistDataSuc ;  //= _T("RegisterDataChangedMsg(%s)成功");
CString g_sLangID_CmdMsgFailWin ;  //= _T("sCmdMsgFailWin");
CString g_sLangTxt_CmdMsgFailWin ;  //= _T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)失败：目标窗口不存在");
CString g_sLangID_MapNotExist ;  //= _T("sMapNotExist");
CString g_sLangTxt_MapNotExist ;  //= _T("数据集映射关系【%s】;  //=【%s$%s】不存在");

CString g_sLangID_ZnNumAndRunZn ;  //= _T("sZnNumAndRunZn");
CString g_sLangTxt_ZnNumAndRunZn ;  //= _T("【%d】定值区数：%d;当前运行区：%d;");
