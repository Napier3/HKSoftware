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

#define		dsTripInfo          "LLN0$dsTripInfo"					//  0.  ���津��

#define		dsParameter			"LLN0$dsParameter"					//	1.	װ�ò���  fc="SP"
#define		dsSetting			"LLN0$dsSetting"					//  2.	������ֵ  fc="SG"��fc="SP"
#define		dsRelayEna			"LLN0$dsRelayEna"					//	3.	����ѹ��  fc="ST"
#define		dsRelayAin			"LLN0$dsRelayAin"					//  4.	����ң�⣨���װ��ң�⣩ fc="MX"
#define		dsRelayDin			"LLN0$dsRelayDin"					//	5.	����ң�ţ����װ��ң�ţ� fc="ST"
#define		dsRelayRec			"LLN0$dsRelayRec"					//	6.	�������ϱ��� fc="ST"
#define		dsTripInfo			"LLN0$dsTripInfo"					//	7.	�����¼� fc="ST"
#define		dsAlarm				"LLN0$dsAlarm"						//	8.	���й����ź� fc="ST"
#define		dsWarning			"LLN0$dsWarning"					//	9.	���и澯�ź� fc="ST"
#define		dsRelaySoe			"LLN0$dsRelaySoe"					//	10. ң��  
#define		dsSV				"LLN0$dsSV"							//	11.	����ֵ  fc="MX"
#define		dsGOOSE				"LLN0$dsGOOSE"						//	12.	GOOSE fc="ST"��fc="MX"   

#define		dsEna				"LLN0$dsEna"						//	12.	ѹ��
#define		dsAin				"LLN0$dsAin"						//	13.	ң��
#define		dsDin				"LLN0$dsDin"						//	14.	ң��(˫��ң��)
#define		dsRec				"LLN0$dsRec"						//	15.	¼��
#define		dsSoe				"LLN0$dsSoe"						//	15.	ң��
#define		dsSetGrpNum			"LLN0$dsSetGrpNum"					//	16.	��ֵ��
#define		dsDout				"LLN0$dsDout"	
#define		dsDevStdMsg			"LLN0$dsDevStdMsg"	//��PROT�¹̶����ӵ�װ�ñ�׼��Ϣ���ݼ�,���ݲ���Ҫ��
#define		dsRelayBlk			"LLN0$dsRelayBlk"						//	��������  
#define		dsRelayState		"LLN0$dsRelayState"						//	����״̬ 
#define		dsRelayFunEn		"LLN0$dsRelayFunEn"						//	��������ѹ�� 
#define		dsLog	        	"LLN0$dsLog"						//	��־ 


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

