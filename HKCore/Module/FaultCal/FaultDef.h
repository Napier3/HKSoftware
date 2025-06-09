//*---------------------------------------------------------------------------
//* file: FaultDef.h
//* --------------------------------------------------------------------------
//  1. ���� Fault-IO ���֧�ֵĿ���/������������ MAX_IO_COUNT_EX
//* --------------------------------------------------------------------------
#if !defined(_FaultDEF)
#define _FaultDEF


//�����������֧�ֵĵ�ѹ�����ͨ����
#define MAX_CHANNEL_COUNT     16

// �����������֧�ֵĿ������򿪳�������
#define MAX_IO_COUNT          16

// IO ����װ�������֧�ֵĿ������򿪳�������
#define MAX_IO_COUNT_EX      256

//������ID��󳤶�
#define MAX_MACHINE_ID_LENGTH 32

//�����������֧�ֵ���ͨ����
#define TOTAL_CHANNEL_COUNT   (MAX_CHANNEL_COUNT*2)

// �����������֧�ֵ��ܿ���������
#define TOTAL_IO_COUNT        (MAX_IO_COUNT*2)

//=========================================֧�ֵ�����ź�����==============================================================

//С�ź�
#define Fault_SIGNALTYPE_XXH    0x10000L

//������
#define Fault_SIGNALTYPE_SZL_91 0x20000L
#define Fault_SIGNALTYPE_SZL_92 0x20001L

//����
#define Fault_SIGNALTYPE_GF     0x30001L




//=========================================������Ӳ���ͺŶ���=============================================================


//DevType ��16λ��ʾӲ�����ͺ�
#define Fault_DEVTYPE_UNKNOWN   0x0000 //δ֪
#define Fault_DEVTYPE_A        0x0001 //Aϵ��
#define Fault_DEVTYPE_D        0x0002 //Dϵ��
#define Fault_DEVTYPE_F        0x0003 //Fϵ��
#define Fault_DEVTYPE_BF       0x0004 //BFϵ��

//DevType ��ʾӲ���ͺ�

//---------------------A ϵ�в������ͺŶ���-------------------------------
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


//---------------------Dϵ�в������ͺŶ���---------------------------
#define Fault_DEVTYPE_D430       0x00020001		//0x01


//---------------------Fϵ�в������ͺŶ���---------------------------
#define Fault_DEVTYPE_F66        0x00030001    //�������� WB821 ��
#define Fault_DEVTYPE_F66D       0x00030002    //��ŷ   IO821 �� D
#define Fault_DEVTYPE_F66DS      0x00030012    //��ŷ   IO821 �� DS 
#define Fault_DEVTYPE_F1210A     0x00030003    

#define Fault_DEVTYPE_BF12      0x00040001

//=========================================Fault ������Ӳ����Ϣ�����Ա�־����===================================================================

//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-------+-------+-------+-------+-----------------------+
//  |P|X|D| | Power |  XXH  | Digit |       |      Common           |
//  +---+-+-+-------+-------+-------+-------+-----------------------+

//bit_31 : �Ƿ�֧���ڲ�����
//bit_30 : �Ƿ�֧��С�ź����
//bit_29 : �Ƿ�֧�����������
//bit_28 : ����

//bit_27 -> bit_24 (����������)

//bit_23 -> bit_20 (С�ź�������)

//bit_19 -> bit_16 (������������)

//bit_15 -> bit_12 (����)

//bit_11 -> bit_0 (��������) 
//bit_1 : �Ƿ����ö�ʱװ��
//bit_0 : �Ƿ�֧��ֱ��


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
//=========================================Ӧ������������========================================================
//ִ����ȷ
#define CFM_CODE_OK				0x00

//��ǰ������λ��ִ��ʧ��
#define CFM_CODE_FAIL			0x01
#define E_FaultDS_NET_FAIL      (FaultDS_E_FIRST+CFM_CODE_FAIL)

//����ͨѶ����CRCУ�����
#define CFM_CODE_CRC_ERROR		0x02
#define E_FaultDS_NET_CRC       (FaultDS_E_FIRST+CFM_CODE_CRC_ERROR)   

//��λ���ڴ治�㣬����ϵ�������Խ��
#define CFM_CODE_OUTOF_MEMORY	0x03
#define E_FaultDS_NET_OUTOFMEMORY   (FaultDS_E_FIRST+CFM_CODE_OUTOF_MEMORY)  

//��ǰ������λ����֧�֣�����ϵ�������Խ��
#define CFM_CODE_NOT_SUPPORT	0x04
#define E_FaultDS_NET_NOIMPLE   (FaultDS_E_FIRST+CFM_CODE_NOT_SUPPORT)  

//����ͨѶ���ݷ��ͳ�ʱ�����������粻ͨ����鿴���������Ƿ�����
#define CFM_CODE_TIMEOUT		0x05
#define E_FaultDS_NET_TIMEOUT   (FaultDS_E_FIRST+CFM_CODE_TIMEOUT)   

//����ͨѶ���ݷ���ʧ�ܣ����������粻ͨ���߲��ȶ�����鿴���������Ƿ�����
#define CFM_CODE_SEND_ERR		0x06
#define E_FaultDS_NET_SEND_ERR   (FaultDS_E_FIRST+CFM_CODE_SEND_ERR)  
 
//��λ�����ֲ���ID��һ�£�����ϵ�������Խ��
#define CFM_CODE_TESTID_ERR		0x07
#define E_FaultDS_TESTID_ERR    (FaultDS_E_FIRST+CFM_CODE_TESTID_ERR) 

//��λ����������δ��ʼ��������ϵ�������Խ��
#define CFM_CODE_ADJ_UNINT      0x08
#define E_FaultDS_ADJ_UNINT     (FaultDS_E_FIRST+CFM_CODE_ADJ_UNINT)  

//��ȡ��λ�����ݴ�������ϵ�������Խ��
#define CFM_CODE_FLASHDATA_ERR  0x09
#define E_FaultDS_FLASHDATAERR  (FaultDS_E_FIRST+CFM_CODE_FLASHDATA_ERR)  

//�ļ���ʽ����
#define CFM_CODE_FILE_ERR       0x0A
#define E_FaultDS_FILE_ERR	    (FaultDS_E_FIRST+CFM_CODE_FILE_ERR)

//���ֲ�֧�ֵ�ͨ�������ź�������ͣ���鿴ϵͳ������ͨ�������Ƿ���ȷ
#define E_FaultDS_SIGNALNOTSUPPORT	 (FaultDS_E_FIRST+0x0B)

//��ȡ��λ����������ʧ�ܣ�����ϵ�������Խ��
#define E_FaultDS_GETADJFAILED	 (FaultDS_E_FIRST+0x0C)

//��Ӳ�������ҳʧ�ܣ�����ҳ�Ѿ�����
#define E_FaultDS_ADJPAGEALREADYEXIST	 (FaultDS_E_FIRST+0x0D)

//���λط�: �����´�����ǰ���ֵ�ѹ����Խ��
#define E_FaultDS_UI_OVER	    (FaultDS_E_FIRST+0x0E)

//���λط�: �����´�����ǰ��ֵʱ���ֵ����������Ӧ
#define E_FaultDS_WAVEPLAY_INPERROR	  (FaultDS_E_FIRST+0x0F)


//���λط�: ��λ����û�в�������
#define CFM_CODE_WAVEPLAY_NOWAVEDATA   0x10
#define E_FaultDS_WAVEPLAY_NOWAVEDATA  (FaultDS_E_FIRST+CFM_CODE_WAVEPLAY_NOWAVEDATA)


//=========================================FaultDS ����¼�ID===============================================================
//Device site events define

//���ط��ʹ������ݹ����еĽ���
#define ODS_EVENT_SENDPROCESS     0x01

//��������ͨѶ�Ͽ�
#define ODS_EVENT_NET_UNCONNECTED 0x02




//=========================================Fault �����������ID===============================================================
//ִ֪ͨ�а�����������
//����: ��
#define STSCMD_KEYPRESS 0L

//ִ֪ͨ��GPS�����崥��
//����: ��
#define STSCMD_GPS_PPM	1L

//����ˢ������
//����: ��
#define STSCMD_ASKREFRESH 2L

//���λط�: �򿪲����ļ�
//����: �ַ���������Ϊ "COMTRADE�ļ�·��;�û�������" (ע��: �����÷ֺŸ���)
//�磺E:\\dd.cfg;1000
#define STSCMD_LOADCOMTRADEFILE 3L

//���λط�: ����¼���ļ�,���´�����λ��
//����: �ַ���������Ϊ "COMTRADE�ļ�·��;��λ���洢�ļ���" (ע��: �����÷ֺŸ���)
//�磺E:\\dd.cfg;dd.cfg
#define STSCMD_COPYCOMTRADEFILE 4L

//����������� GPS ʱ��
//����: IGenericData, ��������Ϊ FaultStruct_GPS �ṹ��
#define STSCMD_QUERYGPSTIME 5L

//���ɹ����񵴵Ĳ���
#define STSCMD_OSC_CREATEWAVE  6L


//=========================================Fault ���Է������ϴ���ϢID����===============================================================
//////////////////////////////////////////////////////////////////////////

#define WM_Fault_DEVMSG (WM_USER+0x1000)
//wParam: ��ϢID;
//lParam: FaultSERVERMSG*

//Description: 
//  �޷�ʶ��ı���
//Content: 
//  FaultSERVERMSG.pMsg = ԭʼ��������
//  FaultSERVERMSG.uLen = ԭʼ���Ĵ�С
#define OSMSG_Unknown  0x01


//Description: 
//  ������״̬��Ϣ�ϴ�
//Content: 
//  FaultSERVERMSG.pMsg = FaultDeviceIOState*
//  FaultSERVERMSG.uLen = sizeof(FaultDeviceIOState)
#define OSMSG_ioState  0x02    


//Description: 
//  ���鱨����Ϣ�ϴ�
//Content: 
//  FaultSERVERMSG.pMsg = Result Data
//  FaultSERVERMSG.uLen = Result Data Length
#define OSMSG_TestResult 0x03


//Description: 
//  �������ˢ����Ϣ 
//Content: 
//  �������鲻ͬ 
#define OSMSG_Refresh    0x04


//Description: 
//  DSP�ϴ�Ӳ��������Ϣ�ϴ� 
//Content: 
//  FreeSize(MB?) = FaultSERVERMSG.wParam 
#define OSMSG_DiskFreeSize 0x05


//Description: 
//  Ӳ��������ֹ��Ϣ
//Content: 
//  ����ԭ�� = FaultSERVERMSG.wParam 
#define OSMSG_TestStop    0x06


//Description: 
//  Ӳ������״̬������Ϣ�ϴ�
//Content: 
//  ��������n״̬ = FaultSERVERMSG.wParam 
#define OSMSG_TestProcess  0x07



#define Fault_DevFault_Curr  0x0001
#define Fault_DevFault_Volt  0x0002
#define Fault_DevFault_Dsp   0x0003

//Description: 
//  �����ǹ��ϸ澯��Ϣ�ϴ�
//Content: 
//  �����ǹ�����Ϣ = FaultSERVERMSG.wParam (value: Fault_DevFault_��ͷ�ĺ�) 
#define OSMSG_DevFault       0x08


//Description: 
//  ���������Ϣ�ϴ�
//Content: 
//  δȷ��
#define OSMSG_TaskFinshed   0x09


#define Fault_LINKSTATE_OFFLINE 0x00
#define Fault_LINKSTATE_ONLINE  0x01

//Description: 
//  ����״̬�ı�
//Content: 
//  (��ϸ����) ==> 
//  FaultSERVERMSG.wParam = ����״̬ : Fault_LINKSTATE_ ;
//  ������״̬Ϊ Fault_LINKSTATE_ONLINE ʱ
//  {
//		FaultSERVERMSG.pMsg = FaultDeviceBaseInfo*
//		FaultSERVERMSG.uLen = sizeof(FaultDeviceBaseInfo)
//  }
//  ����
//		FaultSERVERMSG.pMsg = NULL
//		FaultSERVERMSG.uLen = 0
#define OSMSG_DevLinkStateChanged   0x10


/*
//Description: 
//  syscfg�ı�
//Content: 
//  FaultSERVERMSG.pMsg = FaultCFGPTCT*
//  FaultSERVERMSG.uLen = sizeof(FaultCFGPTCT)
#define OSMSG_QueryChannelCfg   0x11

#define OSMSG_ADJReady          0x12
*/


//������¼�����
//
//Description: 
//  �´��ļ��¼�
//Content: 
//  FaultSERVERMSG.wParam = ��ǰ���´��Ĵ�С
//  FaultSERVERMSG.lParam = �ļ��ܴ�С
#define OSMSG_DevSiteSendEvent   0x13


//Description: 
//  �����ļ��¼��ϴ�
//Content: 
//  FaultSERVERMSG.wParam = ��ǰ�Ѷ�ȡ�Ĵ�С
//  FaultSERVERMSG.lParam = �ļ��ܴ�С
#define OSMSG_TestModuleEvent_LoadFile  0x14

//Description: 
//  GPS��ʱ�ϴ�
//Content: 
//	FaultSERVERMSG.pMsg = SYSTEMTIME*
//	FaultSERVERMSG.uLen = sizeof(SYSTEMTIME)
#define OSMSG_GPSTime   0x15


//-------------------Fault-IO ����������װ��ʹ��--------------------------------
//Description: 
//  ������״̬��Ϣ�ϴ�
//Content: 
//  FaultSERVERMSG.pMsg = FaultDeviceIOState_Ex*
//  FaultSERVERMSG.uLen = sizeof(FaultDeviceIOState_Ex)
#define OSMSG_ioState_Ex  0x16


#define OSMSG_HandleProcess 0x17

#endif