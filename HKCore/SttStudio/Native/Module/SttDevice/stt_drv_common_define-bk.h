#ifndef _stt_drv_common_define_H__
#define _stt_drv_common_define_H__

#define TIME_MAX_WAITING		300			//最长触发等待时间
#define TIME_ONLINE_DELAY		  1			//联机延时

#define STATECOUNT              250
#define CHANELMAXCHANGED        256
#define STATE_RESULT_MAX        250

#define MODULE_MAX	              8    //模块数
#define DIGITAL_MODULE_MAX	      4	//插件数
#define MAX_DIGITAL_GROUP_NUM     4
#define DATA_MAX               1536
#define CHANNEL_MAX               6    //volt\current通道数

#define SYS_INFO_COUNT           11
#define STATERESULTMAX         1000
#define GOOSE_CHANGE_POS_MAX    256
#define CHARPARALeng            256
#define DIGITAL_CHANNEL_MAX      37
#define HARMONIC_MAX             31//总谐波次数

#define DIGITAL_CHANNEL_MARK      1//模块电压标记
#define VOL_CHANNEL_MARK          2//模块电压标记
#define CUR_CHANNEL_MARK          4//模块电流标记

#define SMV_MAX           8
#define GOOSE_MAX        16
#define FT3_MAX          12
#define GOOSESUB_MAX     32

//TestType
#define ManualTest      0
#define GradientTest    1
#define HarmTest        2
#define StateTest       3
#define ShakeTest       4
#define IECDataCfg      5
#define SvCtrlCfg       6
#define GseCtrlCfg      7
#define FiberCtrlCfg    8
#define AbnoramlTest    9
#define ReplayTest      10
#define ReplayTestCfg   11
#define ReplayTestData  12
#define Record          13

//ModuleType
#define VOLT             1
#define CURRENT          2
#define DIGITAL          3
#define DCCURRENT        4
#define DCVOLT           5
#define SWITCH           6

#endif // _stt_drv_common_define_H__

