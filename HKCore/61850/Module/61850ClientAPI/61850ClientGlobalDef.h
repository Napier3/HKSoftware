#pragma once

#include "mms_string.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ST_INT8     signed char     	
#define ST_INT16    signed short     	
#define ST_INT32    signed long     	
#define ST_INT64    __int64
#define ST_UINT8    unsigned char     	
#define ST_UINT16   unsigned short    	
#define ST_UINT32   unsigned long    	
#define ST_UINT64   __int64
#define ST_BOOLEAN  unsigned long	

#define ST_CHAR    char	
#define ST_INT     signed int		
#define ST_LONG    signed long int     	
#define ST_UCHAR   unsigned char	
#define ST_UINT    unsigned int		
#define ST_ULONG   unsigned long     	
#define ST_VOID    void      		
#define ST_DOUBLE  double		
#define ST_FLOAT   float	

#define ST_RET signed int	

#define SD_TRUE		1
#define SD_FALSE	0		
#define SD_SUCCESS 	0
#define SD_FAILURE 	1
#define SD_BIG_ENDIAN		0
#define SD_LITTLE_ENDIAN	1

//////////////////////////////////////////////////////////////////////////
#define     Max_dsType_Num			12

#define		dsType_NULL				-1
#define		dsType_Param			0
#define		dsType_Setting			1
#define		dsType_RelayEna			2
#define		dsType_RelayAin			3
#define		dsType_RelayDin			4
#define		dsType_RelayRec			5
#define		dsType_TripInfo			6
#define		dsType_Alarm			7
#define		dsType_Warning			8
#define     dsType_Soe				9
#define		dsType_SV				10
#define		dsType_GOOSE			11

//////////////////////////////////////////////////////////////////////////

#define		dsTripInfo          "LLN0$dsTripInfo"					//  0.  报告触发

#define		dsParameter			"LLN0$dsParameter"					//	1.	装置参数  fc="SP"
#define		dsSetting			"LLN0$dsSetting"					//  2.	保护定值  fc="SG"，fc="SP"
#define		dsRelayEna			"LLN0$dsRelayEna"					//	3.	保护压板  fc="ST"
#define		dsRelayAin			"LLN0$dsRelayAin"					//  4.	保护遥测（测控装置遥测） fc="MX"
#define		dsRelayDin			"LLN0$dsRelayDin"					//	5.	保护遥信（测控装置遥信） fc="ST"
#define		dsRelayRec			"LLN0$dsRelayRec"					//	6.	保护故障报告 fc="ST"
#define		dsTripInfo			"LLN0$dsTripInfo"					//	7.	保护事件 fc="ST"
#define		dsAlarm				"LLN0$dsAlarm"						//	8.	运行故障信号 fc="ST"
#define		dsWarning			"LLN0$dsWarning"					//	9.	运行告警信号 fc="ST"
#define		dsRelaySoe			"LLN0$dsRelaySoe"					//	10. 遥信  
#define		dsSV				"LLN0$dsSV"							//	11.	采样值  fc="MX"
#define		dsGOOSE				"LLN0$dsGOOSE"						//	12.	GOOSE fc="ST"，fc="MX"   

#define		dsEna				"LLN0$dsEna"						//	12.	压板
#define		dsAin				"LLN0$dsAin"						//	13.	遥测
#define		dsDin				"LLN0$dsDin"						//	14.	遥信(双点遥信)
#define		dsRec				"LLN0$dsRec"						//	15.	录波
#define		dsSoe				"LLN0$dsSoe"						//	15.	遥信
#define		dsSetGrpNum			"LLN0$dsSetGrpNum"					//	16.	定值区
#define		dsDout				"LLN0$dsDout"	
#define		dsDevStdMsg			"LLN0$dsDevStdMsg"	//在PROT下固定增加的装置标准信息数据集,根据测试要求
#define		dsRelayBlk			"LLN0$dsRelayBlk"						//	保护闭锁  
#define		dsRelayState		"LLN0$dsRelayState"						//	保护状态 
#define		dsRelayFunEn		"LLN0$dsRelayFunEn"						//	保护功能压板 
#define		dsLog	        	"LLN0$dsLog"						//	日志 


#define		key_dsParameter			"Parameter"	
#define		key_dsSetting			"Setting"
#define		key_dsRelayEna			"Ena"
#define		key_dsRelayAin			"Ain"
#define		key_dsRelayDin			"Din"
#define		key_dsRelayRec			"Rec"
#define		key_dsTripInfo			"TripInfo"
#define		key_dsAlarm				"Alarm"
#define		key_dsWarning			"Warning"
#define		key_dsGOOSE				"GOOSE"	  
#define		key_dsSetGrpNum			"SetGrpNum"
#define		key_dsDeviceState			"DeviceState"
#define		key_dsCommState			"CommState"
#define		key_dsLog			"Log"
#define		key_dsRelayBlk			"RelayBlk"
#define		key_dsRelayFunEn			"RelayFunEn"
#define		key_dsRelayState			"RelayState"
#define		key_dsDout					"Dout"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SERVICE_RESP_SIZE 11    /* BYTE size of service resp array      */

#define MAX_FILES_OPEN 100	/* maximum files open locally/remotely	*/
#define MAX_FILE_NAME  255	/* maximum length of a file pathname	*/
#define MAX_IDENT_LEN	100 //200	/* length of an Identifier variable	*/  
#define MAX_TYPE_LEN   200  //500
#define MAX_AR_LEN	64	/* length of a AR name			*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

