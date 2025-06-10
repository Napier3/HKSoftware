#ifndef _SttPxCommCmdDef_H_
#define _SttPxCommCmdDef_H_

#include "../../Module/BaseClass/ExBaseList.h"

#define  STT_IOT_PP_TYPE_PpEngine      _T("PpEngine")
#define  STT_IOT_PP_TYPE_MmsEngine   _T("MmsEngine")
#define  STT_IOT_PP_TYPE_CmsEngine   _T("CmsEngine")

#define  ParaID_setzone      _T("Set_Zone_Index")
#define  ParaID_path      _T("Path")
#define  ParaID_tmStart           _T("tmStart")
#define  ParaID_tmEnd            _T("tmEnd")
#define  ParaID_NewFNum      _T("NewFNum")
#define  ParaID_DsID      _T("DsID")

#define  ParaID_CmdState  _T("CmdState")
#define  ParaID_wParam    _T("wParam")
#define  ParaID_lParam    _T("lParam")

#define  ParaID_TrgOps_1    _T("TrgOps_1")
#define  ParaID_TrgOps_4    _T("TrgOps_4")
#define  ParaID_IntgPd    _T("IntgPd")

//日志相关的函数
#define  ParaID_Log_bStart             _T("bStart")
#define  ParaID_Log_EntryIDStart    _T("EntryIDStart")
#define  ParaID_Log_bEnd              _T("bEnd")
#define  ParaID_Log_EntryIDEnd     _T("EntryIDEnd")
#define  ParaID_Log_EntryNum     _T("EntryNum")
#define  ParaID_File                      _T("File")
#define  ParaID_Dir                       _T("Dir")
#define  ParaID_Mode                   _T("Mode")

//枚举模型相关参数
#define  ParaID_FileName                   _T("FileName")
#define  ParaID_EnumSetting                _T("EnumSetting")
#define  ParaID_EnumRelayEna               _T("EnumRelayEna")
#define  ParaID_EnumParameter              _T("EnumParameter")
#define  ParaID_EnumRelayAin               _T("EnumRelayAin")
#define  ParaID_EnumRelayDin               _T("EnumRelayDin")
#define  ParaID_EnumTripInfo               _T("EnumTripInfo")
#define  ParaID_EnumAlarm_Warning          _T("EnumAlarm_Warning")
#define  ParaID_EnumRelayBlk               _T("EnumRelayBlk")
#define  ParaID_EnumRelayState             _T("EnumRelayState")
#define  ParaID_EnumRelayFunEn             _T("EnumRelayFunEn")
#define  ParaID_EnumLog                    _T("EnumLog")
#define  ParaID_DevStdMsg                  _T("DevStdMsg")

//针对readdataset命令，是否发送读数据命令
#define  ParaID_UseRead    _T("UseRead")

#define  CMDID_writeenaone  _T("writeenaone")
#define  CMDID_writeenasel  _T("writeenasel")//zhouhj 2024.1.24 新增用于PpEngine通讯，用于遥控选择  该ID已统一修改,此处注释掉
#define  CMDID_writeenaoper  _T("writeenaoper")//zhouhj 2024.1.24 新增用于PpEngine通讯，用于遥控执行
#define  CMDID_writeenarevk  _T("writeenarevk")//zhouhj 2024.1.24 新增用于PpEngine通讯，用于遥控撤销
#define  CMDID_changesetzone  _T("changesetzone")
#define  CMDID_readain  _T("readain")
#define  CMDID_readdin  _T("readdin")//zhouhj 2024.1.16 新增用于PpEngine通讯
#define  CMDID_readsetting  _T("readsetting")
#define  CMDID_writesetting  _T("writesetting")
#define  CMDID_readena       _T("readena")
#define  CMDID_writeena       _T("writeena")
#define  CMDID_writedout       _T("writedout")
#define  CMDID_readparameter       _T("readparameter")
#define  CMDID_writeparameter       _T("writeparameter")
#define  CMDID_readsoe       _T("readsoe")
#define  CMDID_readsoeds       _T("readsoeds")
#define  CMDID_reset       _T("reset")
#define  CMDID_registerreport       _T("registerreport")
#define  CMDID_unregisterreport       _T("unregisterreport")
#define  CMDID_readzone        _T("readzone")
#define  CMDID_readdataset        _T("readdataset")
#define  CMDID_read_dir        _T("readdir")
#define  CMDID_read_file        _T("readfile")
#define  CMDID_record_dir        _T("record_dir")
#define  CMDID_record_file        _T("record_file")
#define  CMDID_ReadMmsAttr        _T("readmmsattr")
#define  CMDID_WriteMmsAttr        _T("writemmsattr")

#define  CMDID_connect        _T("connect")
#define  CMDID_disconnect     _T("disconnect")
#define  CMDID_logmmserr      _T("logmmserr")
#define  CMDID_ReadDataOne       _T("readone")
#define  CMDID_SetDataRef       _T("setdaref")

#define  CMDID_SingleDoutSelect    _T("SingleDoutSelect")//单点遥控选择
#define  CMDID_SingleDoutExecute    _T("SingleDoutExecute")//单点遥控执行
#define  CMDID_SingleDoutQuash   _T("SingleDoutQuash")//单点遥控撤销
#define  CMDID_DoubleDoutSelect    _T("DoubleDoutSelect")//双点遥控选择
#define  CMDID_DoubleDoutExecute    _T("DoubleDoutExecute")//双点遥控执行
#define  CMDID_DoubleDoutQuash   _T("DoubleDoutQuash")//双点遥控撤销
#define  CMDID_SingleDout  _T("SingleDout")//单点遥控
#define  CMDID_DoubleDout   _T("DoubleDout")//双点遥控
#define  CMDID_Initialize        _T("Initialize")//zhouhj 2024.2.22 传统规约平台用于初始化
#define  CMDID_RegisterReport  _T("RegisterReport") //20240424 启动报告

#define     dsID_MmsDvmAttr         _T("dsmmsdvmattr")

//2020-5-21 lijunqing
#define  Pxi_ID_Procedure    _T("id-procedure")

//StartRecord兼容传统规约的StartRecord，主要是为了设置录波文件的路径
#define  CMDID_StartRecord       _T("startrecord")
#define  CMDID_ReadLogCount       _T("readlogcount")
#define  CMDID_ReadLog       _T("readlog")
#define  CMDID_uploadfile       _T("uploadfile")
#define  CMDID_dvmenum         _T("dvmenum")



//数据集相关定义
#define PX_DSID_ALL_DVM     0XFF

#define PX_DSID_dsParameter    0x0000
#define PX_DSID_dsSetting    0x0001
#define PX_DSID_dsEna    0x0002
#define PX_DSID_dsAin    0x0003
#define PX_DSID_dsDin    0x0004
#define PX_DSID_dsRec    0x0005
#define PX_DSID_dsTripInfo    0x0006
#define PX_DSID_dsAlarm    0x0007
#define PX_DSID_dsWarning    0x0008
#define PX_DSID_dsSoe    0x0009
#define PX_DSID_dsSV    0x000A
#define PX_DSID_dsGOOSE    0x000B
#define PX_DSID_dsDout    0x000C
#define PX_DSID_dsAll    0x000D
#define PX_DSID_dsOwnDef    0x000E
#define PX_DSID_dsNone    0x000F
#define PX_DSID_dsReport    0x0010
#define PX_DSID_dsLog    0x0011
#define PX_DSID_dsFile    0x0012
#define PX_DSID_dsMatrix    0x0013
#define PX_DSID_dsMaxCount    40

extern const CString g_strPxDataSetID[PX_DSID_dsMaxCount];
extern const CString g_strPxDataSetIDKey[PX_DSID_dsMaxCount];
extern const CString g_strPxDataSetName[PX_DSID_dsMaxCount];

const CString& Px_GetDataSetName(const CString &strIDKey);
const CString& Px_GetDataSetID(const CString &strID);
const CString& Px_GetDataSetKey(const CString &strID);
long Px_GetDataSetKey(const CString &strID, CStringArray &astrKeys);
BOOL Px_IsDataSetIDError(const CString &strID);
BOOL Px_JdgDataset(const CString &strDatasetID, long nPxDsID);
BOOL Px_JdgDataset(const CString &strDatasetID, const CString &strPxDsIDKey);
BOOL Px_DatasetCanWrite(const CString &strDatasetID);


//Global Attr
#define ATTRID_NUMOFSG      _T("NUMOFSG")
#define ATTRID_ACTSG        _T("ACTSG")
#define ATTRID_TMTOTAL      _T("TMTOTAL")
#define ATTRID_TMEXEC       _T("TMEXEC")
#define ATTRID_TMSEL        _T("TMSEL")
#define ATTRID_ERRINFO      _T("ERRINFO")
#define ATTRID_RECORD_PATH  _T("rcd-file-path")
#define ATTRID_TimeStartExec  _T("TimeStartExec")

#define ATTRID_InfoEXEC  _T("InfoEXEC")
#define ATTRID_InfoSEL  _T("InfoSEL")
#define ATTRID_TimeGapEnaWrite  _T("TimeGapEnaWrite")
#define ATTRID_TimeGapSelExec  _T("TimeGapSelExec")
#define ATTRID_LogMmsMsg  _T("LogMmsMsg")

#define ATTRID_InfoSetSE  _T("InfoSetSE")
#define ATTRID_InfoSetSG  _T("InfoSetSG")
#define ATTRID_tmSetSE       _T("TMSETSE")
#define ATTRID_tmSetSG        _T("TMSETSG")
#define ATTRID_InfoWriteData  _T("InfoWriteData")
#define ATTRID_TestLinkState  _T("TestLinkState")
#define ATTRID_EnaReadBeforeWrite  _T("ReadBeforeEnaWrite")
#define ATTRID_TEnaReadBeforeWrite  _T("ReadBeforeEnaWriteT")
#define ATTRID_LogCount  _T("LogCount")
#define ATTRID_CurDirFileNum  _T("CurDirFileNum")

#define ATTRID_DVM_NAME_IS_STD  _T("dvm_name_is_std")//zhouhj 20200210 SOE上送报文采用标准名称
#define ATTRID_COMM_Error_Code  _T("CommErrorCode")  ////通讯命令错误码值
#define ATTRID_COMM_Error_Class  _T("CommErrorClass")  ////通讯命令错误类
#define ATTRID_COMM_Error_InforRpt  _T("CommErrorInforRpt")  ////通讯命令错误信息报告

//2022-12-31  lijunqing  for cms
#define ATTRID_ENA_WRITE_CTRL_TYPE_  _T("ena_write_ctrl_type")//zhouhj 20211104 压板控制模式(0-直控,1-SWV,2-SBO)
#define ATTRID_READ_AIN_USE_REPORT_  _T("read_ain_use_report")//zhouhj 20211104 读遥测使用报告数据(0-不使用,1-使用)


//2023-3-9 lijunqing
typedef struct _mms_brcb_ctrl_config_
{
	long OptFlds_BP[9];// = {1,1,1,1,1,0,1,0,0};
	long OptFlds_RP[9];// = {1,1,1,1,1,0,0,0,1};
	long TrgOps_UI[5];// = {1,0,0,0,0};
	long nBrcbIndex;
	long nIntgPd;

	void init()
	{
		OptFlds_BP[0] = 1;
		OptFlds_BP[1] = 1;
		OptFlds_BP[2] = 1;
		OptFlds_BP[3] = 1;
		OptFlds_BP[4] = 1;
		OptFlds_BP[5] = 0;
		OptFlds_BP[6] = 1;
		OptFlds_BP[7] = 0;
		OptFlds_BP[8] = 0;

		OptFlds_RP[0] = 1;
		OptFlds_RP[1] = 1;
		OptFlds_RP[2] = 1;
		OptFlds_RP[3] = 1;
		OptFlds_RP[4] = 1;
		OptFlds_RP[5] = 0;
		OptFlds_RP[6] = 0;
		OptFlds_RP[7] = 0;
		OptFlds_RP[8] = 1;

		TrgOps_UI[0] = 1;
		TrgOps_UI[1] = 0;
		TrgOps_UI[2] = 0;
		TrgOps_UI[3] = 0;
		TrgOps_UI[4] = 0;

		nBrcbIndex = 0;
		nIntgPd = 3000;
	}
}MMS_BRCB_CTRL_CONFIG, *PMMS_BRCB_CTRL_CONFIG;

#endif//!_SttPxCommCmdDef_H_
