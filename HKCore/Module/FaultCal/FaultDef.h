//*---------------------------------------------------------------------------
//* file: FaultDef.h
//* --------------------------------------------------------------------------
//  1. 增加 Fault-IO 最大支持的开入/开出个数定义 MAX_IO_COUNT_EX
//* --------------------------------------------------------------------------
#if !defined(_FaultDEF)
#define _FaultDEF


//测试仪最多能支持的电压或电流通道数
#define MAX_CHANNEL_COUNT     16

// 测试仪最多能支持的开入量或开出量个数
#define MAX_IO_COUNT          16

// IO 测试装置最多能支持的开入量或开出量个数
#define MAX_IO_COUNT_EX      256

//测试仪ID最大长度
#define MAX_MACHINE_ID_LENGTH 32

//测试仪最多能支持的总通道数
#define TOTAL_CHANNEL_COUNT   (MAX_CHANNEL_COUNT*2)

// 测试仪最多能支持的总开关量个数
#define TOTAL_IO_COUNT        (MAX_IO_COUNT*2)

//=========================================支持的输出信号类型==============================================================

//小信号
#define Fault_SIGNALTYPE_XXH    0x10000L

//数字量
#define Fault_SIGNALTYPE_SZL_91 0x20000L
#define Fault_SIGNALTYPE_SZL_92 0x20001L

//功放
#define Fault_SIGNALTYPE_GF     0x30001L




//=========================================测试仪硬件型号定义=============================================================


//DevType 高16位表示硬件主型号
#define Fault_DEVTYPE_UNKNOWN   0x0000 //未知
#define Fault_DEVTYPE_A        0x0001 //A系列
#define Fault_DEVTYPE_D        0x0002 //D系列
#define Fault_DEVTYPE_F        0x0003 //F系列
#define Fault_DEVTYPE_BF       0x0004 //BF系列

//DevType 表示硬件型号

//---------------------A 系列测试仪型号定义-------------------------------
#define Fault_DEVTYPE_6630G   0x00010000		//0x02
#define Fault_DEVTYPE_4630G   0x00010001		//0x00
#define Fault_DEVTYPE_4620G   0x00010002		//0x0f
#define Fault_DEVTYPE_4350G   0x00010003		//0x01
#define Fault_DEVTYPE_A660       0x00010004		//0x06
#define Fault_DEVTYPE_A460       0x00010005		//0x05
#define Fault_DEVTYPE_A430       0x00010006		//0x03
#define Fault_DEVTYPE_A330       0x00010007		//0x03
#define Fault_DEVTYPE_AD661_761        0x00010008
#define Fault_DEVTYPE_AD461_561        0x00010009
#define Fault_DEVTYPE_AD431_531       0x00010010
#define Fault_DEVTYPE_AD331_321_311   0x00010011
#define Fault_DEVTYPE_AD991           0x00010012
#define Fault_DEVTYPE_AD961           0x00010013
#define Fault_DEVTYPE_AD931           0x00010014
#define Fault_DEVTYPE_AD691_791       0x00010015
#define Fault_DEVTYPE_AD491_591       0x00010016
#define Fault_DEVTYPE_AD631_731       0x00010017


//---------------------D系列测试仪型号定义---------------------------
#define Fault_DEVTYPE_D430       0x00020001		//0x01


//---------------------F系列测试仪型号定义---------------------------
#define Fault_DEVTYPE_F66        0x00030001    //深圳南瑞 WB821 板
#define Fault_DEVTYPE_F66D       0x00030002    //爱欧   IO821 板 D
#define Fault_DEVTYPE_F66DS      0x00030012    //爱欧   IO821 板 DS 
#define Fault_DEVTYPE_F1210A     0x00030003    

#define Fault_DEVTYPE_BF12      0x00040001

//=========================================Fault 测试仪硬件信息中特性标志定义===================================================================

//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-------+-------+-------+-------+-----------------------+
//  |P|X|D| | Power |  XXH  | Digit |       |      Common           |
//  +---+-+-+-------+-------+-------+-------+-----------------------+

//bit_31 : 是否支持内部功放
//bit_30 : 是否支持小信号输出
//bit_29 : 是否支持数字量输出
//bit_28 : 保留

//bit_27 -> bit_24 (功放子特性)

//bit_23 -> bit_20 (小信号子特性)

//bit_19 -> bit_16 (数字量子特性)

//bit_15 -> bit_12 (保留)

//bit_11 -> bit_0 (公共特性) 
//bit_1 : 是否内置对时装置
//bit_0 : 是否支持直流


#define DEV_IsSupportGF(Special)  (Special&(0x01<<31))

#define DEV_IsSupportXXH(Special)  (Special&(0x01<<30))

#define DEV_IsSupportSZL(Special)  (Special&(0x01<<29))

#define DEV_IsSupportDC(Special)  (Special&0x01)

#define DEV_IsSupportInnerGPSTimeSyn(Special)  (Special&0x02)
//=========================================Fault Com error define================================================================

//Fault defined HRESULT
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+---------------+---------------+
//  |Sev|C|R|     Facility          | Module Index  |   Module Code |
//  +---+-+-+-----------------------+---------------+---------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code : high byte is module code,low byte is

#define   Fault_E_FIRST    0xA0190000L

#define   MAKE_Fault_MODULE_ERROR(mi,mc)  (FaultDS_E_FIRST+MAKEWORD(mc,mi))

#define   MAKE_Fault_ERROR(mic)  (FaultDS_E_FIRST+mic)

//FaultDS Module Index = 0x01
//Error Code Define:
#define   FaultDS_E_FIRST       (Fault_E_FIRST+0x0100)

#define   E_FaultDS_FAIL        FaultDS_E_FIRST




//1. Network Error:
//=========================================应答反馈常量定义========================================================
//执行正确
#define CFM_CODE_OK				0x00

//当前命令下位机执行失败
#define CFM_CODE_FAIL			0x01
#define E_FaultDS_NET_FAIL      (FaultDS_E_FIRST+CFM_CODE_FAIL)

//网络通讯数据CRC校验错误
#define CFM_CODE_CRC_ERROR		0x02
#define E_FaultDS_NET_CRC       (FaultDS_E_FIRST+CFM_CODE_CRC_ERROR)   

//下位机内存不足，请联系厂家予以解决
#define CFM_CODE_OUTOF_MEMORY	0x03
#define E_FaultDS_NET_OUTOFMEMORY   (FaultDS_E_FIRST+CFM_CODE_OUTOF_MEMORY)  

//当前命令下位机不支持，请联系厂家予以解决
#define CFM_CODE_NOT_SUPPORT	0x04
#define E_FaultDS_NET_NOIMPLE   (FaultDS_E_FIRST+CFM_CODE_NOT_SUPPORT)  

//网络通讯数据发送超时，可能是网络不通，请查看网络连接是否正常
#define CFM_CODE_TIMEOUT		0x05
#define E_FaultDS_NET_TIMEOUT   (FaultDS_E_FIRST+CFM_CODE_TIMEOUT)   

//网络通讯数据发送失败，可能是网络不通或者不稳定，请查看网络连接是否正常
#define CFM_CODE_SEND_ERR		0x06
#define E_FaultDS_NET_SEND_ERR   (FaultDS_E_FIRST+CFM_CODE_SEND_ERR)  
 
//下位机发现测试ID不一致，请联系厂家予以解决
#define CFM_CODE_TESTID_ERR		0x07
#define E_FaultDS_TESTID_ERR    (FaultDS_E_FIRST+CFM_CODE_TESTID_ERR) 

//下位机补偿数据未初始化，请联系厂家予以解决
#define CFM_CODE_ADJ_UNINT      0x08
#define E_FaultDS_ADJ_UNINT     (FaultDS_E_FIRST+CFM_CODE_ADJ_UNINT)  

//读取下位机数据错误，请联系厂家予以解决
#define CFM_CODE_FLASHDATA_ERR  0x09
#define E_FaultDS_FLASHDATAERR  (FaultDS_E_FIRST+CFM_CODE_FLASHDATA_ERR)  

//文件格式错误
#define CFM_CODE_FILE_ERR       0x0A
#define E_FaultDS_FILE_ERR	    (FaultDS_E_FIRST+CFM_CODE_FILE_ERR)

//发现不支持的通道配置信号输出类型，请查看系统配置中通道配置是否正确
#define E_FaultDS_SIGNALNOTSUPPORT	 (FaultDS_E_FIRST+0x0B)

//获取下位机补偿数据失败，请联系厂家予以解决
#define E_FaultDS_GETADJFAILED	 (FaultDS_E_FIRST+0x0C)

//添加补偿数据页失败，数据页已经存在
#define E_FaultDS_ADJPAGEALREADYEXIST	 (FaultDS_E_FIRST+0x0D)

//波形回放: 试验下传波形前发现电压电流越界
#define E_FaultDS_UI_OVER	    (FaultDS_E_FIRST+0x0E)

//波形回放: 试验下传波形前插值时出现点的索引不对应
#define E_FaultDS_WAVEPLAY_INPERROR	  (FaultDS_E_FIRST+0x0F)


//波形回放: 下位机还没有波形数据
#define CFM_CODE_WAVEPLAY_NOWAVEDATA   0x10
#define E_FaultDS_WAVEPLAY_NOWAVEDATA  (FaultDS_E_FIRST+CFM_CODE_WAVEPLAY_NOWAVEDATA)


//=========================================FaultDS 组件事件ID===============================================================
//Device site events define

//返回发送大量数据过程中的进度
#define ODS_EVENT_SENDPROCESS     0x01

//返回网络通讯断开
#define ODS_EVENT_NET_UNCONNECTED 0x02




//=========================================Fault 测试组件命令ID===============================================================
//通知执行按键触发命令
//参数: 无
#define STSCMD_KEYPRESS 0L

//通知执行GPS分脉冲触发
//参数: 无
#define STSCMD_GPS_PPM	1L

//申请刷新数据
//参数: 无
#define STSCMD_ASKREFRESH 2L

//波形回放: 打开波形文件
//参数: 字符串，内容为 "COMTRADE文件路径;用户采样率" (注意: 二者用分号隔开)
//如：E:\\dd.cfg;1000
#define STSCMD_LOADCOMTRADEFILE 3L

//波形回放: 复制录波文件,并下传至下位机
//参数: 字符串，内容为 "COMTRADE文件路径;下位机存储文件名" (注意: 二者用分号隔开)
//如：E:\\dd.cfg;dd.cfg
#define STSCMD_COPYCOMTRADEFILE 4L

//向测试仪申请 GPS 时间
//参数: IGenericData, 保存内容为 FaultStruct_GPS 结构体
#define STSCMD_QUERYGPSTIME 5L

//生成功率振荡的波形
#define STSCMD_OSC_CREATEWAVE  6L


//=========================================Fault 测试服务器上传消息ID定义===============================================================
//////////////////////////////////////////////////////////////////////////

#define WM_Fault_DEVMSG (WM_USER+0x1000)
//wParam: 消息ID;
//lParam: FaultSERVERMSG*

//Description: 
//  无法识别的报文
//Content: 
//  FaultSERVERMSG.pMsg = 原始报文内容
//  FaultSERVERMSG.uLen = 原始报文大小
#define OSMSG_Unknown  0x01


//Description: 
//  开关量状态信息上传
//Content: 
//  FaultSERVERMSG.pMsg = FaultDeviceIOState*
//  FaultSERVERMSG.uLen = sizeof(FaultDeviceIOState)
#define OSMSG_ioState  0x02    


//Description: 
//  试验报告信息上传
//Content: 
//  FaultSERVERMSG.pMsg = Result Data
//  FaultSERVERMSG.uLen = Result Data Length
#define OSMSG_TestResult 0x03


//Description: 
//  试验过程刷新消息 
//Content: 
//  根据试验不同 
#define OSMSG_Refresh    0x04


//Description: 
//  DSP上传硬盘容量信息上传 
//Content: 
//  FreeSize(MB?) = FaultSERVERMSG.wParam 
#define OSMSG_DiskFreeSize 0x05


//Description: 
//  硬件试验终止消息
//Content: 
//  结束原因 = FaultSERVERMSG.wParam 
#define OSMSG_TestStop    0x06


//Description: 
//  硬件试验状态更新信息上传
//Content: 
//  试验进入第n状态 = FaultSERVERMSG.wParam 
#define OSMSG_TestProcess  0x07



#define Fault_DevFault_Curr  0x0001
#define Fault_DevFault_Volt  0x0002
#define Fault_DevFault_Dsp   0x0003

//Description: 
//  测试仪故障告警信息上传
//Content: 
//  测试仪故障信息 = FaultSERVERMSG.wParam (value: Fault_DevFault_开头的宏) 
#define OSMSG_DevFault       0x08


//Description: 
//  任务完成信息上传
//Content: 
//  未确定
#define OSMSG_TaskFinshed   0x09


#define Fault_LINKSTATE_OFFLINE 0x00
#define Fault_LINKSTATE_ONLINE  0x01

//Description: 
//  连机状态改变
//Content: 
//  (详细内容) ==> 
//  FaultSERVERMSG.wParam = 连接状态 : Fault_LINKSTATE_ ;
//  当连接状态为 Fault_LINKSTATE_ONLINE 时
//  {
//		FaultSERVERMSG.pMsg = FaultDeviceBaseInfo*
//		FaultSERVERMSG.uLen = sizeof(FaultDeviceBaseInfo)
//  }
//  否则
//		FaultSERVERMSG.pMsg = NULL
//		FaultSERVERMSG.uLen = 0
#define OSMSG_DevLinkStateChanged   0x10


/*
//Description: 
//  syscfg改变
//Content: 
//  FaultSERVERMSG.pMsg = FaultCFGPTCT*
//  FaultSERVERMSG.uLen = sizeof(FaultCFGPTCT)
#define OSMSG_QueryChannelCfg   0x11

#define OSMSG_ADJReady          0x12
*/


//服务层事件定义
//
//Description: 
//  下传文件事件
//Content: 
//  FaultSERVERMSG.wParam = 当前已下传的大小
//  FaultSERVERMSG.lParam = 文件总大小
#define OSMSG_DevSiteSendEvent   0x13


//Description: 
//  加载文件事件上传
//Content: 
//  FaultSERVERMSG.wParam = 当前已读取的大小
//  FaultSERVERMSG.lParam = 文件总大小
#define OSMSG_TestModuleEvent_LoadFile  0x14

//Description: 
//  GPS对时上传
//Content: 
//	FaultSERVERMSG.pMsg = SYSTEMTIME*
//	FaultSERVERMSG.uLen = sizeof(SYSTEMTIME)
#define OSMSG_GPSTime   0x15


//-------------------Fault-IO 开关量测试装置使用--------------------------------
//Description: 
//  开关量状态信息上传
//Content: 
//  FaultSERVERMSG.pMsg = FaultDeviceIOState_Ex*
//  FaultSERVERMSG.uLen = sizeof(FaultDeviceIOState_Ex)
#define OSMSG_ioState_Ex  0x16


#define OSMSG_HandleProcess 0x17

#endif