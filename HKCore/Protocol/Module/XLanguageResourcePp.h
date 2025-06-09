//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"

class CXLanguageResourcePpBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourcePpBase();
	virtual ~CXLanguageResourcePpBase();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsPpBase;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();

	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsPpBaseFile;
	extern CString g_sLangID_PrtcEngine;     //规约引擎程序
	extern CString g_sLangTxt_PrtcEngine;
	extern CString g_sLangID_FrameSend;     //帧\"%s\"没有指定发送通道
	extern CString g_sLangTxt_FrameSend;
	extern CString g_sLangID_OpenXMLFail;     //打开XML文件失败！
	extern CString g_sLangTxt_OpenXMLFail;
	extern CString g_sLangID_SaveSetFileFail;     //保存通讯配置文件失败！
	extern CString g_sLangTxt_SaveSetFileFail;
	extern CString g_sLangID_DataRltnshipError;     //数据绑定定义错误：
	extern CString g_sLangTxt_DataRltnshipError;
	extern CString g_sLangID_DataRltnshipError2;     //数据绑定定义错误
	extern CString g_sLangTxt_DataRltnshipError2;
	extern CString g_sLangID_DataRltnshipError3;     //%s : 数据绑定定义错误
	extern CString g_sLangTxt_DataRltnshipError3;
	extern CString g_sLangID_SureValueASDU;     //响应带确认写定值ASDU10
	extern CString g_sLangTxt_SureValueASDU;

	extern CString g_sLangID_PrcsFrameUnExist;     //过程节点[%s]关联的帧[%s]不存在
	extern CString g_sLangTxt_PrcsFrameUnExist;
	extern CString g_sLangID_PointFrameUnExist;     //节点\"%s\"关联的制造帧\"%s\"不存在
	extern CString g_sLangTxt_PointFrameUnExist;
	extern CString g_sLangID_PointNotFrame;     //节点\"%s\"关联的\"%s\"不是制造帧
	extern CString g_sLangTxt_PointNotFrame;
	extern CString g_sLangID_PrcsNoData;     //过程\"%s\"没有定义数据接口\"%s\"
	extern CString g_sLangTxt_PrcsNoData;
	extern CString g_sLangID_DataBufferError;     //字节块[%s]数据缓冲错误：nIndex=%d
	extern CString g_sLangTxt_DataBufferError;

	extern CString g_sLangID_FctnCallErrorBind;     //函数BindItemIndex调用错误
	extern CString g_sLangTxt_FctnCallErrorBind;
	extern CString g_sLangID_FctnSError;     //函数SBindItemIndex绑定错误
	extern CString g_sLangTxt_FctnSError;
	extern CString g_sLangID_DataErrorIndex;     //字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d
	extern CString g_sLangTxt_DataErrorIndex;
	extern CString g_sLangID_DataErrorIndex2;     //字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=4
	extern CString g_sLangTxt_DataErrorIndex2;
	extern CString g_sLangID_GetBbEmpty;     //SetBbValStr：字符串参数指针为空
	extern CString g_sLangTxt_GetBbEmpty;
	extern CString g_sLangID_GetBbError;     //%s(%s)：GetBbValStr(%d,%d)错误
	extern CString g_sLangTxt_GetBbError;
	extern CString g_sLangID_FctnDataCall;     //%s::GetBbDataStr函数必须在“格式文本”数据字节快中被调用
	extern CString g_sLangTxt_FctnDataCall;
	extern CString g_sLangID_DataUnExist;     //绑定的数据[%s]=[%s]不存在
	extern CString g_sLangTxt_DataUnExist;
	extern CString g_sLangID_FctnConDataError;     //函数SetBindDataL:绑定关系数据属性\"%s\"错误
	extern CString g_sLangTxt_FctnConDataError;
	extern CString g_sLangID_FctnCallError;     //函数AdBindDataList调用错误
	extern CString g_sLangTxt_FctnCallError;
	extern CString g_sLangID_FctnCallSysError4;     //函数AdBindDataList调用:系统错误(没有关联的设备数据模型)
	extern CString g_sLangTxt_FctnCallSysError4;
	extern CString g_sLangID_FctnCallData;     //函数AdBindDataList调用:数据绑定错误
	extern CString g_sLangTxt_FctnCallData;
	extern CString g_sLangID_FctnCallNode;     //函数AdBindDataList调用:节点\"%s\" 不存在
	extern CString g_sLangTxt_FctnCallNode;
	extern CString g_sLangID_FctnFireCallError;     //函数FireDataMsg调用错误
	extern CString g_sLangTxt_FctnFireCallError;
	extern CString g_sLangID_SystemErrorPath;     //系统错误(路径为空)
	extern CString g_sLangTxt_SystemErrorPath;
	extern CString g_sLangID_DataNodeUnExist4;     //InsertDsData:数据节点不存在
	extern CString g_sLangTxt_DataNodeUnExist4;
	extern CString g_sLangID_DataNodeUnExist3;     //InsertBindData:数据节点不存在
	extern CString g_sLangTxt_DataNodeUnExist3;
	extern CString g_sLangID_DataNodeUnExist2;     //InsertDataset:数据节点不存在
	extern CString g_sLangTxt_DataNodeUnExist2;
	extern CString g_sLangID_DataNodeUnExist;     //script_InsertLogicDevice:数据节点不存在
	extern CString g_sLangTxt_DataNodeUnExist;
	extern CString g_sLangID_FctnGetCallError;     //函数GetBindDataL调用错误
	extern CString g_sLangTxt_FctnGetCallError;
	extern CString g_sLangID_FctnSetError;     //函数SetBindDataL:字节块\"%s\"中绑定错误
	extern CString g_sLangTxt_FctnSetError;
	extern CString g_sLangID_FctnBindSet;     //函数SetBindDataL:字节块\"%s\"中绑定数据集
	extern CString g_sLangTxt_FctnBindSet;
	extern CString g_sLangID_FctnBindCallError;     //函数###BindData###调用错误
	extern CString g_sLangTxt_FctnBindCallError;
	extern CString g_sLangID_FctnGetError;     //函数GetBindDeviceDataNode:字节块\"%s\"中绑定错误
	extern CString g_sLangTxt_FctnGetError;
	extern CString g_sLangID_FctnDataSet;     //函数GetBindDeviceDataNode:字节块\"%s\"中绑定数据集
	extern CString g_sLangTxt_FctnDataSet;
	extern CString g_sLangID_PathNoData;     //path[%s]没有对应的数据节点
	extern CString g_sLangTxt_PathNoData;
	extern CString g_sLangID_SetVariUnExist;     //GetValue:变量\"%s\"不存在
	extern CString g_sLangTxt_SetVariUnExist;
	extern CString g_sLangID_SetLongVariUnExist;     //SetValueLong:变量\"%s\"不存在
	extern CString g_sLangTxt_SetLongVariUnExist;
	extern CString g_sLangID_GetFctnCallErrorLen;     //GetPkgLen函数调用错误
	extern CString g_sLangTxt_GetFctnCallErrorLen;
	extern CString g_sLangID_GetFctnCallErrorPkg;     //GetPkgNum函数调用错误
	extern CString g_sLangTxt_GetFctnCallErrorPkg;
	extern CString g_sLangID_AddFctnCallError;     //AddGlobal函数调用错误
	extern CString g_sLangTxt_AddFctnCallError;
	extern CString g_sLangID_GetFctnCallError;     //GetGlobal函数调用错误
	extern CString g_sLangTxt_GetFctnCallError;
	extern CString g_sLangID_SetFctnCallError;     //SetGlobal函数调用错误
	extern CString g_sLangTxt_SetFctnCallError;
	extern CString g_sLangID_FctnCallSysError3;     //函数Run调用:系统错误
	extern CString g_sLangTxt_FctnCallSysError3;
	extern CString g_sLangID_FctnCallSysError2;     //函数SetPpRunState调用:系统错误
	extern CString g_sLangTxt_FctnCallSysError2;
	extern CString g_sLangID_FctnCallSysError;     //函数SetPpValid调用:系统错误
	extern CString g_sLangTxt_FctnCallSysError;
	extern CString g_sLangID_DataIndexError;     //字节块[%s]数据缓冲错误：nIndex=%d Length=%d
	extern CString g_sLangTxt_DataIndexError;
	extern CString g_sLangID_FctnCallSystem;     //函数Connect调用:系统错误(没有关联的设备数据模型)
	extern CString g_sLangTxt_FctnCallSystem;
	extern CString g_sLangID_SystemErrorData8;     //系统错误(路径【%s】对应的数据不存在)
	extern CString g_sLangTxt_SystemErrorData8;
	extern CString g_sLangID_SystemErrorData7;     //系统错误(路径【%s】对应的逻辑设备不存在)
	extern CString g_sLangTxt_SystemErrorData7;
	extern CString g_sLangID_SystemErrorData6;     //系统错误(路径【%s】对应的设备不存在)
	extern CString g_sLangTxt_SystemErrorData6;
	extern CString g_sLangID_SystemErrorData5;     //系统错误(没有关联的设备数据模型)
	extern CString g_sLangTxt_SystemErrorData5;
	extern CString g_sLangID_SystemErrorData4;     //系统错误(不是多设备数据模型)
	extern CString g_sLangTxt_SystemErrorData4;
	extern CString g_sLangID_SystemErrorData3;     //系统错误(数据【%s】没有属性【%s】)
	extern CString g_sLangTxt_SystemErrorData3;
	extern CString g_sLangID_SystemErrorData2;     //系统错误(数据集【%s】没有属性【%s】)
	extern CString g_sLangTxt_SystemErrorData2;
	extern CString g_sLangID_SystemErrorData;     //系统错误(逻辑设备【%s】没有属性【%s】)
	extern CString g_sLangTxt_SystemErrorData;
	extern CString g_sLangID_FctnDataErrorDsData;     //函数AdDsDataList调用:数据绑定错误
	extern CString g_sLangTxt_FctnDataErrorDsData;
	extern CString g_sLangID_FctnCallNoReport;     //函数AdDsDataList调用:【%s】数据集没有启动报告
	extern CString g_sLangTxt_FctnCallNoReport;
	extern CString g_sLangID_FctnCallPoint;     //函数AdDsDataList调用:节点\"%s\" 不存在
	extern CString g_sLangTxt_FctnCallPoint;
	extern CString g_sLangID_FctnDataErrorDsPkg;     //函数AdDsPkgDetail调用:数据绑定错误
	extern CString g_sLangTxt_FctnDataErrorDsPkg;
	extern CString g_sLangID_FctnDataErrorVal;     //函数AdValPkgDetail调用:数据绑定错误
	extern CString g_sLangTxt_FctnDataErrorVal;
	extern CString g_sLangID_FctnCallLength;     //函数SetBcd24Float调用:缓冲区长度(%d)不够
	extern CString g_sLangTxt_FctnCallLength;
	
	extern CString g_sLangID_Constant;     //常量
	extern CString g_sLangTxt_Constant;
	extern CString g_sLangID_DataList;     //数据列表
	extern CString g_sLangTxt_DataList;
	extern CString g_sLangID_FormatText;     //格式文本
	extern CString g_sLangTxt_FormatText;
	extern CString g_sLangID_SumCheck;     //和校验
	extern CString g_sLangTxt_SumCheck;
	extern CString g_sLangID_CRCCheck;     //CRC校验(初始值0)
	extern CString g_sLangTxt_CRCCheck;
	extern CString g_sLangID_CRCCheck2;     //CRC校验(初始值0xFFFF)
	extern CString g_sLangTxt_CRCCheck2;
	extern CString g_sLangID_CRCCheck3;     //CRC校验(查表法)
	extern CString g_sLangTxt_CRCCheck3;
	extern CString g_sLangID_Script;     //脚本
	extern CString g_sLangTxt_Script;
	extern CString g_sLangID_EncodeModeNoneName;     //不编码
	extern CString g_sLangTxt_EncodeModeNoneName;
	extern CString g_sLangID_EncodeModeSendName;     //帧编码(发送)
	extern CString g_sLangTxt_EncodeModeSendName;
	extern CString g_sLangID_EncodeModeReceiveName;     //帧编码(接收)
	extern CString g_sLangTxt_EncodeModeReceiveName;
	extern CString g_sLangID_EncodeModeSAndRName;     //帧编码(发送接收统一)
	extern CString g_sLangTxt_EncodeModeSAndRName;
	extern CString g_sLangID_EncodeModeSOrRName;     //帧编码(发送接收独立)
	extern CString g_sLangTxt_EncodeModeSOrRName;
	extern CString g_sLangID_EncodeName;     //帧编码
	extern CString g_sLangTxt_EncodeName;
	extern CString g_sLangID_Receive;     //接收
	extern CString g_sLangTxt_Receive;
	extern CString g_sLangID_SingDev;     //单一设备
	extern CString g_sLangTxt_SingDev;
	extern CString g_sLangID_MultDev;     //多设备
	extern CString g_sLangTxt_MultDev;
	extern CString g_sLangID_NoDevDataModel;     //没有指定设备数据模型模式
	extern CString g_sLangTxt_NoDevDataModel;
	extern CString g_sLangID_ErrorMessage;     //错误报文:(Begin=%d      Len=%d)
	extern CString g_sLangTxt_ErrorMessage;
	extern CString g_sLangID_Send;     //发送
	extern CString g_sLangTxt_Send;
	extern CString g_sLangID_CommunPathUnExist;     //模板定义的通信通道不存在
	extern CString g_sLangTxt_CommunPathUnExist;
	extern CString g_sLangID_CommunPathUnExist2;     //模板定义的通信通道\"%s\"不存在
	extern CString g_sLangTxt_CommunPathUnExist2;
	extern CString g_sLangID_CommunPathUnExist3;     //节点\"%s\"定义的通信通道\"%s\"不存在
	extern CString g_sLangTxt_CommunPathUnExist3;
	extern CString g_sLangID_ProcessClose;     //----------过程\"%s\"结束----------
	extern CString g_sLangTxt_ProcessClose;
	extern CString g_sLangID_ProcessRun;     //过程\"%s\"已经运行
	extern CString g_sLangTxt_ProcessRun;
	extern CString g_sLangID_PrtcPrcsDfn;     //规约过程定义
	extern CString g_sLangTxt_PrtcPrcsDfn;
	extern CString g_sLangID_PrtcTempName;     //规约模板名称
	extern CString g_sLangTxt_PrtcTempName;
	extern CString g_sLangID_PrtcTempDiff;     //规约模板的模型模式【%s】与点表文件的模型模式【%s】不一致
	extern CString g_sLangTxt_PrtcTempDiff;
	extern CString g_sLangID_DataBindRlship;     //数据绑定关系：
	extern CString g_sLangTxt_DataBindRlship;
	extern CString g_sLangID_NoCorrespondingData;     //没有对应的数据
	extern CString g_sLangTxt_NoCorrespondingData;
	extern CString g_sLangID_LasterTestUnFinsh;     //    +++++++++++上次端口测试没结束: %s
	extern CString g_sLangTxt_LasterTestUnFinsh;
	extern CString g_sLangID_ChannelTest;     //通道测试：关闭测试通道用时%d
	extern CString g_sLangTxt_ChannelTest;
	extern CString g_sLangID_PointListEditor;     //点表编辑库PpDeviceModelEdit.dll不存在!
	extern CString g_sLangTxt_PointListEditor;
	extern CString g_sLangID_EditDevDataModel;     //[%s] 引擎数据无效，请编辑设备数据模型
	extern CString g_sLangTxt_EditDevDataModel;
	extern CString g_sLangID_ScriptCallError;     //脚本函数SetPkgLen调用错误:对应的模板不存在
	extern CString g_sLangTxt_ScriptCallError;
	extern CString g_sLangID_UnDefinScript;     //跳转节点\"%s\"没有定义脚本
	extern CString g_sLangTxt_UnDefinScript;
	extern CString g_sLangID_NoJumpNode;     //[%s]无跳转节点
	extern CString g_sLangTxt_NoJumpNode;
	extern CString g_sLangID_JumpNodeNoValue;     //跳转节点\"%s\"脚本【%s】没有返回值，使用\"return\"返回
	extern CString g_sLangTxt_JumpNodeNoValue;
	extern CString g_sLangID_PrtcTempFileError;     //规约模板文件\"%s\"  错误
	extern CString g_sLangTxt_PrtcTempFileError;
	extern CString g_sLangID_CreatDevFail;     //创建设备对象失败，设备点表文件\"%s\"错误
	extern CString g_sLangTxt_CreatDevFail;
	extern CString g_sLangID_RptDataSetUnExist;     //Reset:报告数据集不存在【%s】
	extern CString g_sLangTxt_RptDataSetUnExist;
	extern CString g_sLangID_RptDataSet;     //Reset:报告数据集【%d】=>>0
	extern CString g_sLangTxt_RptDataSet;
	extern CString g_sLangID_ResetMessage;     //Reset:报文抓包【%d】=>>0
	extern CString g_sLangTxt_ResetMessage;
	extern CString g_sLangID_ParaBoundsGet;     //GetBitInLong16参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsGet;
	extern CString g_sLangID_ParaBoundsSet;     //SetBitInLong16参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsSet;
	extern CString g_sLangID_ParaBoundsClear;     //ClearBitInLong16参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsClear;
	extern CString g_sLangID_ParaBoundsGet2;     //GetBitInLong32参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsGet2;
	extern CString g_sLangID_ParaBoundsSet2;     //SetBitInLong32参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsSet2;
	extern CString g_sLangID_ParaBoundsClear2;     //ClearBitInLong32参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsClear2;
	extern CString g_sLangID_ParaBoundsGet3;     //GetBitInLong8参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsGet3;
	extern CString g_sLangID_ParaBoundsSet3;     //SetBitInLong8参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsSet3;
	extern CString g_sLangID_ParaBoundsClear3;     //ClearBitInLong8参数nBitIndex=%d越界
	extern CString g_sLangTxt_ParaBoundsClear3;
	extern CString g_sLangID_ParaBoundsGet4;     //script_GetBitRangeInLong8参数nBitEnd=%d越界
	extern CString g_sLangTxt_ParaBoundsGet4;
	extern CString g_sLangID_DevDaraTmpFile;     //设备数据模型文件不存在：%s
	extern CString g_sLangTxt_DevDaraTmpFile;
	extern CString g_sLangID_CommunSetFile;     //通讯配置文件不存在：%s
	extern CString g_sLangTxt_CommunSetFile;
	extern CString g_sLangID_DevDataPoint;     //设备数据点表
	extern CString g_sLangTxt_DevDataPoint;
	extern CString g_sLangID_OpenSerialFail;     //打开串口%d失败！
	extern CString g_sLangTxt_OpenSerialFail;
	extern CString g_sLangID_ReceiveSerialFail;     //获取串口属性失败！
	extern CString g_sLangTxt_ReceiveSerialFail;
	extern CString g_sLangID_SetSerialError;     //设置串口属性错误！
	extern CString g_sLangTxt_SetSerialError;
	extern CString g_sLangID_SendMessageFail;     //向\"%s\"发送报文失败
	extern CString g_sLangTxt_SendMessageFail;

	extern CString g_sLangID_ExistSameName;     //存在同名的UDP服务器(IP=%s  Port=%d)
	extern CString g_sLangTxt_ExistSameName;
	extern CString g_sLangID_ExistSameName2;     //存在同名的TCP服务器(IP=%s  Port=%d)
	extern CString g_sLangTxt_ExistSameName2;
	extern CString g_sLangID_SendMessageFail2;     //向\"%s\"发送BroadCast报文失败
	extern CString g_sLangTxt_SendMessageFail2;
	extern CString g_sLangID_ItemNumber;       //条目号
	extern CString g_sLangTxt_ItemNumber;

	extern CString g_sLangID_PointTableFile;//点表文件(*.xml)|*.xml||
	extern CString g_sLangTxt_PointTableFile;

	extern CString g_sLangID_AddBytesBlock;
	extern CString g_sLangTxt_AddBytesBlock;
	extern CString g_sLangID_AddDataSets;
	extern CString g_sLangTxt_AddDataSets;
	extern CString g_sLangID_DataDef;
	extern CString g_sLangTxt_DataDef;
	extern CString g_sLangID_DataByteBlock;
	extern CString g_sLangTxt_DataByteBlock;
	extern CString g_sLangID_Length;//长度
	extern CString g_sLangTxt_Length;
	extern CString g_sLangID_Byte;
	extern CString g_sLangTxt_Byte;
	extern CString g_sLangID_Msg;
	extern CString g_sLangTxt_Msg;
	extern CString g_sLangID_DataTypeValue;
	extern CString g_sLangTxt_DataTypeValue;
	extern CString g_sLangID_FrameVariDefin2;//变量定义
	extern CString g_sLangTxt_FrameVariDefin2;


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
