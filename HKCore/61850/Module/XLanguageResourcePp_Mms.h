#pragma once

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLanguageResourceIec.h"

class CXLanguageResourcePp_Mms: public CXLanguageResourceIecBase
{
// ����
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
	//װ�ò���
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
	//ö��
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
	//����ֵ
	extern CString g_sLangID_DataValue;
	extern CString g_sLangTxt_DataValue;
	extern CString g_sLangID_ReadData;
	extern CString g_sLangTxt_ReadData;
	extern CString g_sLangID_ReadDataTip;
	extern CString g_sLangTxt_ReadDataTip;
	extern CString g_sLangID_ModifyData;
	extern CString g_sLangTxt_ModifyData;
	//��ֵ��
	extern CString g_sLangID_ReadFixedValueRegion;
	extern CString g_sLangTxt_ReadFixedValueRegion;
	extern CString g_sLangID_ModifyFixedValueRegion;
	extern CString g_sLangTxt_ModifyFixedValueRegion;

	//����
	extern CString g_sLangID_StartReportTip;
	extern CString g_sLangTxt_StartReportTip;
	extern CString g_sLangID_StopReportTip;
	extern CString g_sLangTxt_StopReportTip;
	extern CString g_sLangID_DebugAdd;
	extern CString g_sLangTxt_DebugAdd;
	extern CString g_sLangID_DebugAddTip;
	extern CString g_sLangTxt_DebugAddTip;
	//�ļ�
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
	//��ͼ
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
	//��������
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
	//����װ�õĵ�ǰ������
	extern CString g_sLangID_SetCurGrpDevice;
	extern CString g_sLangTxt_SetCurGrpDevice;
	extern CString g_sLangID_FixedValueNum;
	extern CString g_sLangTxt_FixedValueNum;
	//��װ������
	extern CString g_sLangID_LinkSet;
	extern CString g_sLangTxt_LinkSet;
	extern CString g_sLangID_IP;
	extern CString g_sLangTxt_IP;
	extern CString g_sLangID_EnumRptCtrlBlk;
	extern CString g_sLangTxt_EnumRptCtrlBlk;
	
	//����IP����
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
	//������
	extern CString g_sLangID_InOperation;
	extern CString g_sLangTxt_InOperation;
	extern CString g_sLangID_DataOperation;
	extern CString g_sLangTxt_DataOperation;
	//ѡ��·��
	extern CString g_sLangID_SelPath;
	extern CString g_sLangTxt_SelPath;
	//ѡ��ֵ��
	extern CString g_sLangID_SelValueZone;
	extern CString g_sLangTxt_SelValueZone;
	extern CString g_sLangID_OperationZone;
	extern CString g_sLangTxt_OperationZone;
	//�Զ�ƥ�����ݼ��鿴
	extern CString g_sLangID_AutoMatchView;
	extern CString g_sLangTxt_AutoMatchView;
	//BrcbCtrlDlg��������Ϣ
	extern CString g_sLangID_NotEnum;
	extern CString g_sLangTxt_NotEnum;
	//DlgSelPath��������Ϣ
	extern CString g_sLangID_EnterPath;
	extern CString g_sLangTxt_EnterPath;
	//IPSetObj��������Ϣ
	extern CString g_sLangID_FileOprtFail;
	extern CString g_sLangTxt_FileOprtFail;
	//LinkSetDlg��������Ϣ
	extern CString g_sLangID_RestartAndLink;
	extern CString g_sLangTxt_RestartAndLink;
	//LocalIpSetDlg��������Ϣ
	extern CString g_sLangID_ResetIP;
	extern CString g_sLangTxt_ResetIP;
	//MainFrm��������Ϣ
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
	//MmsDeviceTreeCtrl��������Ϣ
	extern CString g_sLangID_MmsNodes;
	extern CString g_sLangTxt_MmsNodes;
	extern CString g_sLangID_RecdWaveFile;
	extern CString g_sLangTxt_RecdWaveFile;
	extern CString g_sLangID_LogRecord;
	extern CString g_sLangTxt_LogRecord;
	extern CString g_sLangID_TooMuchActualDevice;
	extern CString g_sLangTxt_TooMuchActualDevice;
	//NodeView��������Ϣ
	extern CString g_sLangID_Attributes;
	extern CString g_sLangTxt_Attributes;
	extern CString g_sLangID_UnableloadBitmap;
	extern CString g_sLangTxt_UnableloadBitmap;
	//OutputWnd��������Ϣ
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
	//PpMmsEngine�������Ϣ
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
	//PpMmsEngineView��������Ϣ
	extern CString g_sLangID_DaXiao;
	extern CString g_sLangTxt_DaXiao;
	//ZoneSelDlg��������Ϣ
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
	extern CString g_sLangTxt_Menu_32777;//"��������(&B)	Ctrl+B"
	extern CString g_sLangTxt_Menu_32778;//"ֹͣ����(&P)	Ctrl+P"
	extern CString g_sLangTxt_Menu_32794;//����ģʽ(&D)
	extern CString g_sLangTxt_Menu_32795;//��ʾ������Ϣ(&V)
	extern CString g_sLangTxt_Menu_32797;//����-ͨѶʧ��(&F)
	extern CString g_sLangTxt_Menu_32804;//��ӵ�SOE����
	extern CString g_sLangTxt_Menu_32796;//��һ�豸ģʽ(&S)
	extern CString g_sLangTxt_Menu_32786;//������ֵʹ�ñ�������
	extern CString g_sLangTxt_Menu_32798;//��������ֻ��ձ�������

	extern CString g_sLangID_HadNoDataNeedEdit;// _T("sHadNoDataNeedEdit");
	extern CString g_sLangTxt_HadNoDataNeedEdit;// _T("û����Ҫ�޸ĵ�����");
	extern CString g_sLangID_ReadDeviceDirSucc;// _T("ReadDeviceDirSuccs");
	extern CString g_sLangTxt_ReadDeviceDirSucc;// _T("ö��װ��Ŀ¼�ɹ�.");
	extern CString g_sLangID_ReadDeviceDirFail;// _T("sReadDeviceDirFail");
	extern CString g_sLangTxt_ReadDeviceDirFail;// _T("ö��װ��Ŀ¼ʧ��.");
	extern CString g_sLangID_SetZoneFail;// _T("sSetZoneFail");
	extern CString g_sLangTxt_SetZoneFail;// _T("���õ�ǰ��ֵ��������ʧ��!");
	extern CString g_sLangID_ConnectSucc;// _T("sConnectSucc");
	extern CString g_sLangTxt_ConnectSucc;// _T("��װ�������ɹ�.");
	extern CString g_sLangID_ConnectFail;// _T("sConnectFail");
	extern CString g_sLangTxt_ConnectFail;// _T("��װ������ʧ�ܡ�Error��.");
	extern CString g_sLangID_DisConnectSucc;// _T("sDisConnectSucc");
	extern CString g_sLangTxt_DisConnectSucc;// _T("��װ�öϿ����ӳɹ�.");
	extern CString g_sLangID_DisConnectFail;// _T("sDisConnectFail");
	extern CString g_sLangTxt_DisConnectFail;// _T("��װ�öϿ�����ʧ�ܡ�Error��.");
	extern CString g_sLangID_RdDatasetSucc;// _T("sRdDatasetSucc");
	extern CString g_sLangTxt_RdDatasetSucc;// _T("�����ݼ��ɹ�.");
	extern CString g_sLangID_RdDatasetFail;// _T("sRdDatasetFail");
	extern CString g_sLangTxt_RdDatasetFail;// _T("�����ݼ�ʧ�ܡ�Error��.");
	extern CString g_sLangID_ReadRecorDirFail;// _T("sReadRecorDirFail");
	extern CString g_sLangTxt_ReadRecorDirFail;// _T("��¼���ļ�Ŀ¼ʧ��.");
	extern CString g_sLangID_ReadRecordDirSucc;// _T("sReadRecordDirSucc");
	extern CString g_sLangTxt_ReadRecordDirSucc;// _T("��¼���ļ�Ŀ¼�ɹ�.");
	extern CString g_sLangID_ReadRecordFileSucc;// _T("sReadRecordFileSucc");
	extern CString g_sLangTxt_ReadRecordFileSucc;// _T("��¼���ļ��ɹ�.");
	extern CString g_sLangID_ReadRecordFileFail;// _T("sReadRecordFileFail");
	extern CString g_sLangTxt_ReadRecordFileFail;// _T("��¼���ļ�ʧ��.");
	extern CString g_sLangID_WriteDataFail;// _T("sWriteDataFail");
	extern CString g_sLangTxt_WriteDataFail;// _T("д����ʧ�ܡ�Error��.");
	extern CString g_sLangID_WriteDataSucc;// _T("sWriteDataSucc");
	extern CString g_sLangTxt_WriteDataSucc;// _T("д���ݳɹ�.");
	extern CString g_sLangID_StartRptFail;// _T("sStartRptFail");
	extern CString g_sLangTxt_StartRptFail;// _T("��������ʧ�ܡ�Error��.");
	extern CString g_sLangID_StartRptSucc;// _T("sStartRptSucc");
	extern CString g_sLangTxt_StartRptSucc;// _T("��������ɹ�.");
	extern CString g_sLangID_StopRptFail;// _T("sStopRptFail");
	extern CString g_sLangTxt_StopRptFail;// _T("ֹͣ����ʧ�ܡ�Error��.");
	extern CString g_sLangID_StopRptSucc;// _T("sStopRptSucc");
	extern CString g_sLangTxt_StopRptSucc;// _T("ֹͣ����ɹ�.");
	extern CString g_sLangID_ReadZoneFail;// _T("sReadZoneFail");
	extern CString g_sLangTxt_ReadZoneFail;// _T("��ȡ��ǰ��ֵ��������ʧ��.");
	extern CString g_sLangID_NetConnect;// _T("sNetConnect");
	extern CString g_sLangTxt_NetConnect;// _T("������������.");
	extern CString g_sLangID_NetDisConnect;// _T("sNetDisConnect");
	extern CString g_sLangTxt_NetDisConnect;// _T("�������ӶϿ�.");

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
	extern CString g_sLangID_FuncID_Connect;//_T("����");
	extern CString g_sLangTxt_FuncID_DisConnect;//_T("s_FuncID_DisConnect");
	extern CString g_sLangID_FuncID__FuncID_DisConnect;//_T("���豸�Ͽ�����");
	extern CString g_sLangTxt_FuncID_WriteData;//_T("sFuncID_WriteData");
	extern CString g_sLangID_FuncID_WriteData;//_T("д����");
	extern CString g_sLangTxt_FuncID_ReadData;//_T("sFuncID_ReadData");
	extern CString g_sLangID_FuncID_ReadData;//_T("������");
	extern CString g_sLangTxt_FuncID_StartRpt;//_T("sFuncID_StartRpt");
	extern CString g_sLangID_FuncID_StartRpt;//_T("��������");
	extern CString g_sLangTxt_FuncID_StopRpt;//_T("sFuncID_StopRpt");
	extern CString g_sLangID_FuncID_StopRpt;//_T("ֹͣ����");
	extern CString g_sLangTxt_FuncID_GetRunZn;//_T("sFuncID_GetRunZn");
	extern CString g_sLangID_FuncID_GetRunZn;//_T("��ȡ��ǰ������");
	extern CString g_sLangTxt_FuncID_SetRunZn;//_T("sFuncID_SetRunZn");
	extern CString g_sLangID_FuncID_SetRunZn;//_T("���õ�ǰ������");
	extern CString g_sLangTxt_FuncID_EnumDvDir;//_T("sFuncID_EnumDvDir");
	extern CString g_sLangID_FuncID_EnumDvDir;//_T("ö��װ��Ŀ¼");
	extern CString g_sLangTxt_FuncID_ChangeEditZn;//_T("sFuncID_ChangeEditZn");
	extern CString g_sLangID_FuncID_ChangeEditZn;//_T("�л��༭��ֵ��");
	extern CString g_sLangTxt_FuncID_SolidEditZn;//_T("sFuncID_SolidEditZn");
	extern CString g_sLangID_FuncID_SolidEditZn;//_T("�̻��༭��ֵ��");


	extern CString g_sLangID_CreatMmsComm;//_T("sCreatMmsComm");
	extern CString g_sLangTxt_CreatMmsComm;//_T("����ΪMMSͨѶ����ģʽ��%s��");
	extern CString g_sLangID_ReachMax;//_T("sReachMax");
	extern CString g_sLangTxt_ReachMax;//_T("�ɴ������豸���Ѿ��ﵽ�����ޣ����ܴ�����%s���豸");
	extern CString g_sLangID_ReleasMmsComm;//_T("sReleasMmsComm");
	extern CString g_sLangTxt_ReleasMmsComm;//_T("�ͷ�MMSͨѶ����ģʽ��%s��");

	extern CString g_sLangID_CurrentActSet;//_T("sCurrentActSet");
	extern CString g_sLangTxt_CurrentActSet;//_T("��ǰ���ֵ��");
	extern CString g_sLangID_SettingTotalNo;//_T("sSettingTotalNo");
	extern CString g_sLangTxt_SettingTotalNo;//_T("��ֵ������");
	extern CString g_sLangID_CommandTotalTime;//_T("sCommandTotalTime");
	extern CString g_sLangTxt_CommandTotalTime;//_T("������ʱ��");
	extern CString g_sLangID_CommandExecuTime;//_T("sCommandExecuTime");
	extern CString g_sLangTxt_CommandExecuTime;//_T("����ִ��ʱ��");
	extern CString g_sLangID_CommandChoseTime;//_T("sCCommandChoseTime");
	extern CString g_sLangTxt_CommandChoseTime;//_T("����ѡ��ʱ��");
	extern CString g_sLangID_CommandExecuMess;//_T("sCommandExecuMess");
	extern CString g_sLangTxt_CommandExecuMess;//_T("����ִ����Ϣ");
	extern CString g_sLangID_CommandChoseMess;//_T("sCommandChoseMess");
	extern CString g_sLangTxt_CommandChoseMess;//_T("����ѡ����Ϣ");
	extern CString g_sLangID_WrongMess;//_T("sWrongMess");
	extern CString g_sLangTxt_WrongMess;//_T("������Ϣ");
	extern CString g_sLangID_RecordPath;//_T("sRecordPath");
	extern CString g_sLangTxt_RecordPath;//_T("¼��·��");
	extern CString g_sLangID_EnaChangeTime;//_T("sEnaChangeTime");
	extern CString g_sLangTxt_EnaChangeTime;//_T("ѹ���޸ļ��ʱ��");
	extern CString g_sLangID_EnaChoseTime;//_T("sEnaChoseTime");
	extern CString g_sLangTxt_EnaChoseTime;//_T("ѹ��ѡ��ִ�м��ʱ��");
	extern CString g_sLangID_MonitErrorTime;//_T("sMonitErrorTime");
	extern CString g_sLangTxt_MonitErrorTime;//_T("���Ӵ�����Ϣ");
	extern CString g_sLangID_BeforEnaRead;//_T("sBeforEnaRead");
	extern CString g_sLangTxt_BeforEnaRead;//_T("Ͷ��ѹ��ǰ��״̬");
	extern CString g_sLangID_BeforEnaReadTime;//_T("sBeforEnaReadTime");
	extern CString g_sLangTxt_BeforEnaReadTime;//_T("Ͷ��ѹ��ǰ��״̬����ʱ");

	extern CString g_sLangID_WritDataMess;//_T("sWritDataMess");
	extern CString g_sLangTxt_WritDataMess;//_T("д������Ϣ");
	extern CString g_sLangID_SetEdtTime;//_T("sSetEdtTime");
	extern CString g_sLangTxt_SetEdtTime;//_T("���ñ༭��ʱ��");
	extern CString g_sLangID_SetActTime;//_T("sSetActTime");
	extern CString g_sLangTxt_SetActTime;//_T("���û��ʱ��");
	extern CString g_sLangID_SetEdtMess;//_T("sSetEdtMess");
	extern CString g_sLangTxt_SetEdtMess;//_T("���ñ༭����Ϣ");
	extern CString g_sLangID_SetActMess;//_T("sSetActMess");
	extern CString g_sLangTxt_SetActMess;//_T("���û����Ϣ");
	extern CString g_sLangID_TestConnSta;//_T("sTestConnSta");
	extern CString g_sLangTxt_TestConnSta;//_T("��������״̬");

	extern CString g_sLangID_ExecConnCommand;//_T("sExecConnCommand");
	extern CString g_sLangTxt_ExecConnCommand;//_T("ִ���ⲿͨѶ���%s����ACSIDevice=%d  LdIndex=%d  DatasetIndex=%d");
	extern CString g_sLangID_DatasetPathError;//_T("sDatasetPathError");
	extern CString g_sLangTxt_DatasetPathError;//_T("���ݼ�·����%s������ȷ");
	extern CString g_sLangID_Ena;//_T("sEna");
	extern CString g_sLangTxt_Ena;//_T("ѹ��");
	extern CString g_sLangID_RemoteCtl;//_T("sRemoteCtl");
	extern CString g_sLangTxt_RemoteCtl;//_T("ң��");
	extern CString g_sLangID_UnRegRepDataSet;//_T("sUnRegRepDataSet");
	extern CString g_sLangTxt_UnRegRepDataSet;//_T("unregisterreport:���ݼ���%s");
	extern CString g_sLangID_SwitchSet;//_T("sSwitchSet");
	extern CString g_sLangTxt_SwitchSet;//_T("�л���ֵ����%d");
	extern CString g_sLangID_OnlyReadProp;//_T("sOnlyReadProp");
	extern CString g_sLangTxt_OnlyReadProp;//_T("���ԡ�%s��Ϊֻ������");
	extern CString g_sLangID_NoNeedCorect;//_T("sNoNeedCorect");
	extern CString g_sLangTxt_NoNeedCorect;//_T("û����Ҫ�޸ĵ�%s��%s��");
	extern CString g_sLangID_RegRepDataSetMiss;//_T("sRegRepDataSetMiss");
	extern CString g_sLangTxt_RegRepDataSetMiss;//_T("registerreport:���ݼ���%s ������");
	extern CString g_sLangID_StopRepDataSetMiss;//_T("sStopRepDataSetMiss");
	extern CString g_sLangTxt_StopRepDataSetMiss;//_T("stopreport:���ݼ���%s ������");

	extern CString g_sLangID_SendOverMesNotWin;//_T("sSendOverMesNotWin");
	extern CString g_sLangTxt_SendOverMesNotWin;//_T("���Ͳ��������Ϣ ��%08x�� ���Ǵ���");
	extern CString g_sLangID_SendOverMes;//_T("sSendOverMes");
	extern CString g_sLangTxt_SendOverMes;//_T("���Ͳ��������Ϣ WND=��%08x�� MSG=��%08x��");
	extern CString g_sLangID_DataNotExist;//_T("sDataNotExist");
	extern CString g_sLangTxt_DataNotExist;//_T("���ݡ�%s����%s��������");
	extern CString g_sLangID_RegistDataFail;//_T("sRegistDataFail");
	extern CString g_sLangTxt_RegistDataFail;//_T("RegisterDataChangedMsg(%s)ʧ��");
	extern CString g_sLangID_RegistDataSuc ;//_T("sRegistDataSuc");
	extern CString g_sLangTxt_RegistDataSuc;//_T("RegisterDataChangedMsg(%s)�ɹ�");
	extern CString g_sLangID_CmdMsgFailWin;//_T("sCmdMsgFailWin");
	extern CString g_sLangTxt_CmdMsgFailWin;//_T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)ʧ�ܣ�Ŀ�괰�ڲ�����");
	extern CString g_sLangID_MapNotExist;//_T("sMapNotExist");
	extern CString g_sLangTxt_MapNotExist;//_T("���ݼ�ӳ���ϵ��%s��=��%s$%s��������");
	extern CString g_sLangID_ZnNumAndRunZn;
	extern CString g_sLangTxt_ZnNumAndRunZn;




	extern CString  g_strXLangRsPp_PpEngineFile;
	extern CString g_sLangID_NotSelDev;       //û��ѡ���豸
	extern CString g_sLangTxt_NotSelDev;
	extern CString g_sLangID_PrtcProHome;      //��Լ���������ҳ
	extern CString g_sLangTxt_PrtcProHome;
	extern CString g_sLangID_DevOpera;      //�豸����
	extern CString g_sLangTxt_DevOpera;
	extern CString g_sLangID_NewAdd;          //����
	extern CString g_sLangTxt_NewAdd;
	extern CString g_sLangID_Connection;       //����
	extern CString g_sLangTxt_Connection;
	extern CString g_sLangID_DisConnection;       //�Ͽ�����
	extern CString g_sLangTxt_DisConnection;
	extern CString g_sLangID_Uninstall;       //ж��
	extern CString g_sLangTxt_Uninstall;
	extern CString g_sLangID_PointTableEdit;       //���༭
	extern CString g_sLangTxt_PointTableEdit;
	extern CString g_sLangID_CommuntSet;       //ͨѶ����
	extern CString g_sLangTxt_CommuntSet;
	extern CString g_sLangID_CommunProcess;       //ͨѶ����
	extern CString g_sLangTxt_CommunProcess;
	extern CString g_sLangID_OperationProcess;       //���й���
	extern CString g_sLangTxt_OperationProcess;
	extern CString g_sLangID_ViewOprthPrcs;       //�鿴���й���
	extern CString g_sLangTxt_ViewOprthPrcs;
	extern CString g_sLangID_StopProcess;       //��ֹ����
	extern CString g_sLangTxt_StopProcess;
	extern CString g_sLangID_ClearSOE;       //���SOE
	extern CString g_sLangTxt_ClearSOE;
	extern CString g_sLangID_ClearMessage;       //�������
	extern CString g_sLangTxt_ClearMessage;
	extern CString g_sLangID_DebugMode;       //����ģʽ
	extern CString g_sLangTxt_DebugMode;
	extern CString g_sLangID_Report;       //����
	extern CString g_sLangTxt_Report;
	extern CString g_sLangID_StartReport;       //��������
	extern CString g_sLangTxt_StartReport;
	extern CString g_sLangID_StopReport;       //ֹͣ����
	extern CString g_sLangTxt_StopReport;
	extern CString g_sLangID_DevToolBar;       //�豸������
	extern CString g_sLangTxt_DevToolBar;
	extern CString g_sLangID_DevToolBarTip;       //��ʾ�������豸������\n�л��豸������
	extern CString g_sLangTxt_DevToolBarTip;
	extern CString g_sLangID_OutputWnd;       //�������
	extern CString g_sLangTxt_OutputWnd;
	extern CString g_sLangID_OutputWndTip;       //��ʾ�������������\n�л��������
	extern CString g_sLangTxt_OutputWndTip;
	extern CString g_sLangID_MonitorBindError;       //���Ӱ󶨴���
	extern CString g_sLangTxt_MonitorBindError;
	extern CString g_sLangID_MonitorMessageInf;       //���ӱ�����Ϣ
	extern CString g_sLangTxt_MonitorMessageInf;
	extern CString g_sLangID_MonitorMessage;       //���ӱ���
	extern CString g_sLangTxt_MonitorMessage;

	extern CString g_sLangID_ClipboardData;       //���а�����
	extern CString g_sLangTxt_ClipboardData;
	// 	extern CString g_sLangID_DataList;       //�����б�
	// 	extern CString g_sLangTxt_DataList;
	extern CString g_sLangID_ReadClipboard;       //��ȡ���а�
	extern CString g_sLangTxt_ReadClipboard;
	extern CString g_sLangID_AddToList;       //��ӵ��б�
	extern CString g_sLangTxt_AddToList;
	extern CString g_sLangID_InsertList;       //���뵽�б�β
	extern CString g_sLangTxt_InsertList;
	extern CString g_sLangID_ClearList;       //����б�
	extern CString g_sLangTxt_ClearList;
	extern CString g_sLangID_InsertIndex;       //������ʼ������
	extern CString g_sLangTxt_InsertIndex;
	extern CString g_sLangID_PointDataPaste;       //�������ճ��
	extern CString g_sLangTxt_PointDataPaste;
	extern CString g_sLangID_NewDev;       //�½��豸
	extern CString g_sLangTxt_NewDev;
	extern CString g_sLangID_PointListFile;       //����ļ�
	extern CString g_sLangTxt_PointListFile;
	extern CString g_sLangID_ModifyClose;       //�޸Ĺر�
	extern CString g_sLangTxt_ModifyClose;

	extern CString g_sLangID_FormulaType;       //��ʽ����
	extern CString g_sLangTxt_FormulaType;
	extern CString g_sLangID_FormulaEdit;       //��ʽ�༭
	extern CString g_sLangTxt_FormulaEdit;
	extern CString g_sLangID_SelType;       //ѡ�����
	extern CString g_sLangTxt_SelType;
	extern CString g_sLangID_FormulaEditD;       //��ʽ�༭�Ի���
	extern CString g_sLangTxt_FormulaEditD;

	extern CString g_sLangID_MonitorPrtcMessage;       //���ӹ�Լ����
	extern CString g_sLangTxt_MonitorPrtcMessage;
	extern CString g_sLangID_MonitorSOE;       //����SOE
	extern CString g_sLangTxt_MonitorSOE;
	extern CString g_sLangID_Empty;       //���
	extern CString g_sLangTxt_Empty;
	extern CString g_sLangID_CommunMonitor;       //ͨѶ����
	extern CString g_sLangTxt_CommunMonitor;
	extern CString g_sLangID_SelCommunProcess;       //ѡ��ͨѶ����
	extern CString g_sLangTxt_SelCommunProcess;
	extern CString g_sLangID_SelProcessSet;       //ѡ��������ݽӿ�����
	extern CString g_sLangTxt_SelProcessSet;

	extern CString g_sLangID_Vaule;       //��ֵ
	extern CString g_sLangTxt_Vaule;
	extern CString g_sLangID_PrtcMonitor;       //��Լ����
	extern CString g_sLangTxt_PrtcMonitor;
	extern CString g_sLangID_CannotAddView;       //�޷�����λͼ: %x\n
	extern CString g_sLangTxt_CannotAddView;
	extern CString g_sLangID_NewFolder2;       //�½��ļ���...
	extern CString g_sLangTxt_NewFolder2;
	extern CString g_sLangID_AddMemberFctn;       //��ӳ�Ա����...
	extern CString g_sLangTxt_AddMemberFctn;
	extern CString g_sLangID_RptPathUnExist;       //����·����%s��������
	extern CString g_sLangTxt_RptPathUnExist;
	extern CString g_sLangID_DataPathUnExist;       //���ݼ�·����%s��������
	extern CString g_sLangTxt_DataPathUnExist;
	extern CString g_sLangID_DiffError;       //��ǰ���̡�%s���������Ĺ��̡�%s�������߲�ͬ����������
	extern CString g_sLangTxt_DiffError;
	extern CString g_sLangID_SendTestInf;       //===============���Ͳ��������Ϣ[%s] WND=��%08x�� MSG=��%08x��
	extern CString g_sLangTxt_SendTestInf;
	extern CString g_sLangID_SendSystemMsg;       //����ϵͳ��Ϣ WND=��%08x�� MSG=��%08x��(%d, %d)
	extern CString g_sLangTxt_SendSystemMsg;
	extern CString g_sLangID_ColctnClcltFmla;       //�ɼ����㹫ʽ
	extern CString g_sLangTxt_ColctnClcltFmla;
	extern CString g_sLangID_SendClcltFmla;       //���ͼ��㹫ʽ
	extern CString g_sLangTxt_SendClcltFmla;

    /*  ���¼������ƶ�������CXLanguageResourceBase��2024-1-4  shaolei
	extern CString g_sLangID_Voltage;       //��ѹ
	extern CString g_sLangTxt_Voltage;
	extern CString g_sLangID_Current;       //����
	extern CString g_sLangTxt_Current;
	extern CString g_sLangID_ActivePower;       //�й�����
	extern CString g_sLangTxt_ActivePower;
	extern CString g_sLangID_ReactivePower;       //�޹�����
	extern CString g_sLangTxt_ReactivePower;
	extern CString g_sLangID_Frequency;       //Ƶ��
	extern CString g_sLangTxt_Frequency;
	extern CString g_sLangID_PowerFactor;       //��������
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
