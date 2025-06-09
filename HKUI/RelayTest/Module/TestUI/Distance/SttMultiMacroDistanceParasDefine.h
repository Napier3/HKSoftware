#ifndef STTMULTIMACRODISTANCEPARASDEFINE_H
#define STTMULTIMACRODISTANCEPARASDEFINE_H
#include "../SttMultiMacroParasDefine.h"

#define STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_ZPhi	        "DistanceZ-Phi"
#define STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_RX	        "DistanceR-X"

#define IMPEDANCE_FAULT_TYPE_AN                                                 0//�迹��Ĺ������Ͷ���
#define IMPEDANCE_FAULT_TYPE_BN                                                 1
#define IMPEDANCE_FAULT_TYPE_CN                                                 2
#define IMPEDANCE_FAULT_TYPE_AB                                                 3
#define IMPEDANCE_FAULT_TYPE_BC                                                 4
#define IMPEDANCE_FAULT_TYPE_CA                                                 5
#define IMPEDANCE_FAULT_TYPE_ABN                                                6
#define IMPEDANCE_FAULT_TYPE_BCN                                                7
#define IMPEDANCE_FAULT_TYPE_CAN                                                8
#define IMPEDANCE_FAULT_TYPE_ABC                                                9
#define IMPEDANCE_FAULT_TYPE_ONE                                                10

//������ڵ���,���������ͽ��з��ഴ���ļ���
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_AN         "FaultType_AN"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_BN         "FaultType_BN"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_CN         "FaultType_CN"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_AB         "FaultType_AB"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_BC         "FaultType_BC"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_CA         "FaultType_CA"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_ABN        "FaultType_ABN"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_BCN        "FaultType_BCN"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_CAN        "FaultType_CAN"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_ABC        "FaultType_ABC"
#define STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_ONE        "FaultType_ONE"

#define STT_MULTI_MACRO_CURR_MAX	20
#define STT_MULTI_MACRO_CURR_MIN	0
#define STT_MULTI_MACRO_TSet_MAX	999.999
#define STT_MULTI_MACRO_TSet_MIN	0
#define STT_MULTI_MACRO_ZSet_MAX	999.999
#define STT_MULTI_MACRO_ZSet_MIN	0.001
#define STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX	999.999//R��X���ֵ��Сֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN	-999.999
#define STT_MULTI_MACRO_ANGPLACES	2

#define STT_MULTI_MACRO_PLACES_3	3//R��X��TSet��ZSet��Curr��Abs��Rel����3λС��
#define STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemFault			"SystemFault"//�������Ͷ�ӦDataTypeId
//QDistanceResultEstimateDlg	���ܲ����༭ҳ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING			"ZSetting"			//�迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE				"Rate"				//����
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE			"K0Mode"			//���򲹳�ϵ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR				"KlKr"				//���򲹳�ϵ��K0
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX				"AngKx"				//���򲹳�ϵ��Phi(K0)
//#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_IMPREFTYPE		"ImpRefType"//		//�迹�ο���ʽ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT		"FaultIf"		//��·����20240806 luozibing ��FaultCurrent
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION	"FaultDirection"	//���Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1		"FaultPermanent"	//�������� 20240717 luozibing �����޸�
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING		"RSetting"	//���趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING		"XSetting"	//�翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng		"ZSetByAng"	//�迹��ֵ��Ӧ�Ƕȡ����Ρ���������


#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT			"0"			//ȱʡֵ

//QDistanceCommonParasDlg	ͨ�ò���ҳ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME			"PreFaultTime"		//����ǰʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME				"FaultTime"			//����ʱ��ԣ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER		"TimeAfterTrigger"	//�������������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE			"FaultTrigMode"		//���ϴ�����ʽ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS					"PTPos"				//PT��װλ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS					"CTPos"				//CT������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD					"ILoad"				//���ɵ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH				"ILoadPh"			//���ɹ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY	"SimulateBreakerDelay"//�Ƿ�ģ���·����ʱ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME			"BrkBreakTime"			//��բʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME			"BrkCloseTime"			//��·����բ��ʱ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE				"VzDefine"				//��ȡ��ѹ�������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE			"VzPhDefine"			//��ȡ��ѹ�ο����
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH					"VzPh"					//��ȡ��ѹ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_MINTRIPTIME			"MinTripTime"			//��С����ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE			"Zl"					//��·�����迹��ֵ

//QDistanceBinarysDlg		���롢����ҳ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT				"_AndOr"	//������ѡ��//20240809luozibing��������TestMacro.xml�޸�
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_A						"BinA"			//����A
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_B						"BinB"			//����B
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_C						"BinC"			//����C
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_D						"BinD"			//����D
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_E						"BinE"			//����E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_F						"BinF"			//����F
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_G						"BinG"			//����G
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_H						"BinH"			//����H
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01					"_B01"		//��̬����1״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02					"_B02"		//��̬����2״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03					"_B03"		//��̬����3״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04					"_B04"		//��̬����4״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05					"_B05"		//��̬����5״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06					"_B06"		//��̬����6״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07					"_B07"		//��̬����7״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08					"_B08"		//��̬����8״̬
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE		"_OutputSwitchMode"		//������ת������ʽ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME		"_OutputKeepTime"		//��������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME		"_OutputDelayTime"		//������תʱ��

typedef enum{
	IMPREFTYPE_Z_PHI = 0,//Z-Phi
	IMPREFTYPE_R_X   = 1,//R-X
}STT_MULTI_MACRO_DISTANCE_IMPREFTYPE;

//QDistanceAddSinglePhaseDlg	��ӵ���ӵع���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095_CHECK				"Rate_095_Check"				//����ѡ��-0.95
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105_CHECK				"Rate_105_Check"				//����ѡ��-1.05
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070_CHECK				"Rate_070_Check"				//����ѡ��-0.70
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100_CHECK				"Rate_100_Check"				//����ѡ��-1.00
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_100						"Rate_100"						//����-�Զ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_095						"Rate_095"						//����-0.95
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_105						"Rate_105"						//����-1.05
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE_070						"Rate_070"						//����-0.70
// #define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR						"Zone1_RelErr"					//���붯��ʱ����������
// #define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC					"Zone1_ErrorLogic"				//���붯��ʱ������߼��ж�

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1					"Zone1_AbsErr_p"				//I�ξ��붯��ʱ�������������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1					"Zone1_AbsErr_n"			//I�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1						"Zone1_RelErr"					//I�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1					"Zone1_ErrorLogic"				//I�ξ��붯��ʱ������߼��ж�

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2					"Zone2_AbsErr_p"				//II�ξ��붯��ʱ�������������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2					"Zone2_AbsErr_n"			//II�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2						"Zone2_RelErr"					//II�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2					"Zone2_ErrorLogic"				//II�ξ��붯��ʱ������߼��ж�

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3					"Zone3_AbsErr_p"				//III�ξ��붯��ʱ�������������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3					"Zone3_AbsErr_n"			//III�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3						"Zone3_RelErr"					//III�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3					"Zone3_ErrorLogic"				//III�ξ��붯��ʱ������߼��ж�

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4					"Zone4_AbsErr_p"				//IV�ξ��붯��ʱ�������������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4					"Zone4_AbsErr_n"			//IV�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4						"Zone4_RelErr"					//IV�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4					"Zone4_ErrorLogic"				//IV�ξ��붯��ʱ������߼��ж�

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5					"Zone5_AbsErr_p"				//V�ξ��붯��ʱ�������������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5					"Zone5_AbsErr_n"			//V�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5						"Zone5_RelErr"					//V�ξ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5					"Zone5_ErrorLogic"				//V�ξ��붯��ʱ������߼��ж�

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS6					"ZoneLine_AbsErr_p"			//��·���Ⱦ��붯��ʱ�������������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS6					"ZoneLine_AbsErr_n"			//��·���Ⱦ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR6						"ZoneLine_RelErr"				//��·���Ⱦ��붯��ʱ����������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6					"ZoneLine_ErrorLogic"			//��·���Ⱦ��붯��ʱ������߼��ж�

//QDistanceAddMultDlg
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK				"LNZone1_Check"	//�ӵع���-I��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK				"LNZone2_Check"	//�ӵع���-II��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK				"LNZone3_Check"	//�ӵع���-III��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK				"LNZone4_Check"	//�ӵع���-IV��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK				"LNZone5_Check"	//�ӵع���-V��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK				"LNZone_Line"	//�ӵع���-��·����
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK				"LLZone1_Check"	//������-I��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK				"LLZone2_Check"	//������-II��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK				"LLZone3_Check"	//������-III��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK				"LLZone4_Check"	//������-IV��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK				"LLZone5_Check"	//������-V��ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK				"LLZone_Line"	//������-��·����

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N1		"Direction_Radio_N1"//�ӵع���I�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N2		"Direction_Radio_N2"//�ӵع���II�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N3		"Direction_Radio_N3"//�ӵع���III�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N4		"Direction_Radio_N4"//�ӵع���IV�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N5		"Direction_Radio_N5"//�ӵع���V�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_N6		"Direction_Radio_NLine"//�ӵع�����·���ȹ��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L1		"Direction_Radio_L1"//������I�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L2		"Direction_Radio_L2"//������II�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L3		"Direction_Radio_L3"//������III�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L4		"Direction_Radio_L4"//������IV�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L5		"Direction_Radio_L5"//������V�ι��Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_DIRECTION_RADIO_L6		"Direction_Radio_LLine"//��������·���ȹ��Ϸ���

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE1_CHECK		"FaultTypeAE1_Check"//�ӵع���I�ι���ѡ��-A-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE1_CHECK		"FaultTypeBE1_Check"//�ӵع���I�ι���ѡ��-B-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE1_CHECK		"FaultTypeCE1_Check"//�ӵع���I�ι���ѡ��-C-E
//#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABCE1_CHECK		"FaultTypeABCE1_Check"//�ӵع���I�ι���ѡ��-ABC-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE2_CHECK		"FaultTypeAE2_Check"//�ӵع���II�ι���ѡ��-A-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE2_CHECK		"FaultTypeBE2_Check"//�ӵع���II�ι���ѡ��-B-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE2_CHECK		"FaultTypeCE2_Check"//�ӵع���II�ι���ѡ��-C-E
//#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABCE2_CHECK		"FaultTypeABCE2_Check"//�ӵع���II�ι���ѡ��-ABC-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE3_CHECK		"FaultTypeAE3_Check"//�ӵع���III�ι���ѡ��-A-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE3_CHECK		"FaultTypeBE3_Check"//�ӵع���III�ι���ѡ��-B-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE3_CHECK		"FaultTypeCE3_Check"//�ӵع���III�ι���ѡ��-C-E
//#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABCE3_CHECK		"FaultTypeABCE3_Check"//�ӵع���III�ι���ѡ��-ABC-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE4_CHECK		"FaultTypeAE4_Check"//�ӵع���IV�ι���ѡ��-A-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE4_CHECK		"FaultTypeBE4_Check"//�ӵع���IV�ι���ѡ��-B-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE4_CHECK		"FaultTypeCE4_Check"//�ӵع���IV�ι���ѡ��-C-E
//#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABCE4_CHECK		"FaultTypeABCE4_Check"//�ӵع���IV�ι���ѡ��-ABC-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE5_CHECK		"FaultTypeAE5_Check"//�ӵع���V�ι���ѡ��-A-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE5_CHECK		"FaultTypeBE5_Check"//�ӵع���V�ι���ѡ��-B-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE5_CHECK		"FaultTypeCE5_Check"//�ӵع���V�ι���ѡ��-C-E

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAE6_CHECK		"FaultTypeAE_Line"//�ӵع�����·���ȹ���ѡ��-A-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBE6_CHECK		"FaultTypeBE_Line"//�ӵع�����·���ȹ���ѡ��-B-E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECE6_CHECK		"FaultTypeCE_Line"//�ӵع�����·���ȹ���ѡ��-C-E

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB1_CHECK		"FaultTypeAB1_Check"//������I�ι���ѡ��-AB
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC1_CHECK		"FaultTypeBC1_Check"//������I�ι���ѡ��-BC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA1_CHECK		"FaultTypeCA1_Check"//������I�ι���ѡ��-CA
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC1_CHECK		"FaultTypeABC1_Check"//������I�ι���ѡ��-ABC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB2_CHECK		"FaultTypeAB2_Check"//������II�ι���ѡ��-AB
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC2_CHECK		"FaultTypeBC2_Check"//������II�ι���ѡ��-BC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA2_CHECK		"FaultTypeCA2_Check"//������II�ι���ѡ��-CA
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC2_CHECK		"FaultTypeABC2_Check"//������II�ι���ѡ��-ABC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB3_CHECK		"FaultTypeAB3_Check"//������III�ι���ѡ��-AB
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC3_CHECK		"FaultTypeBC3_Check"//������III�ι���ѡ��-BC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA3_CHECK		"FaultTypeCA3_Check"//������III�ι���ѡ��-CA
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC3_CHECK		"FaultTypeABC3_Check"//������III�ι���ѡ��-ABC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB4_CHECK		"FaultTypeAB4_Check"//������IV�ι���ѡ��-AB
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC4_CHECK		"FaultTypeBC4_Check"//������IV�ι���ѡ��-BC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA4_CHECK		"FaultTypeCA4_Check"//������IV�ι���ѡ��-CA
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC4_CHECK		"FaultTypeABC4_Check"//������IV�ι���ѡ��-ABC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB5_CHECK		"FaultTypeAB5_Check"//������V�ι���ѡ��-AB
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC5_CHECK		"FaultTypeBC5_Check"//������V�ι���ѡ��-BC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA5_CHECK		"FaultTypeCA5_Check"//������V�ι���ѡ��-CA
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC5_CHECK		"FaultTypeABC5_Check"//������V�ι���ѡ��-ABC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEAB6_CHECK		"FaultTypeAB_Line"//��������·���ȹ���ѡ��-AB
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEBC6_CHECK		"FaultTypeBC_Line"//��������·���ȹ���ѡ��-BC
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPECA6_CHECK		"FaultTypeCA_Line"//��������·���ȹ���ѡ��-CA
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPEABC6_CHECK		"FaultTypeABC_Line"//��������·���ȹ���ѡ��-ABC


#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTANGLE			"FaultAngle"//�����迹��

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1		"ZSetingLN_Zone1"//�ӵؾ���I���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2		"ZSetingLN_Zone2"//�ӵؾ���II���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3		"ZSetingLN_Zone3"//�ӵؾ���III���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4		"ZSetingLN_Zone4"//�ӵؾ���IV���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5		"ZSetingLN_Zone5"//�ӵؾ���V���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6		"ZSetingLN_Line"//�ӵؾ�����·�����迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1		"ZSetingLL_Zone1"//������I���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2		"ZSetingLL_Zone2"//������II���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3		"ZSetingLL_Zone3"//������III���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4		"ZSetingLL_Zone4"//������IV���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5		"ZSetingLL_Zone5"//������V���迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6		"ZSetingLL_Line"//��������·�����迹��ֵ

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1		"ZAngLN_Zone1"//�ӵؾ���I���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2		"ZAngLN_Zone2"//�ӵؾ���II���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3		"ZAngLN_Zone3"//�ӵؾ���III���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4		"ZAngLN_Zone4"//�ӵؾ���IV���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5		"ZAngLN_Zone5"//�ӵؾ���V���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE6		"ZAngLN_Line"//�ӵؾ�����·�����迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1		"ZAngLL_Zone1"//������I���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2		"ZAngLL_Zone2"//������II���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3		"ZAngLL_Zone3"//������III���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4		"ZAngLL_Zone4"//������IV���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5		"ZAngLL_Zone5"//������V���迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE6		"ZAngLL_Line"//��������·�����迹��

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1		"TSetingLN_Zone1"//�ӵؾ���I����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2		"TSetingLN_Zone2"//�ӵؾ���II����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3		"TSetingLN_Zone3"//�ӵؾ���III����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4		"TSetingLN_Zone4"//�ӵؾ���IV����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5		"TSetingLN_Zone5"//�ӵؾ���V����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE6		"TSetingLN_Line"//�ӵؾ�����·������������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1		"TSetingLL_Zone1"//������I����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2		"TSetingLL_Zone2"//������II����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3		"TSetingLL_Zone3"//������III����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4		"TSetingLL_Zone4"//������IV����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5		"TSetingLL_Zone5"//������V����������ʱ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE6		"TSetingLL_Line"//��������·������������ʱ��

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE1		"RSetingLN_Zone1"//�ӵؾ���I�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE2		"RSetingLN_Zone2"//�ӵؾ���II�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE3		"RSetingLN_Zone3"//�ӵؾ���III�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE4		"RSetingLN_Zone4"//�ӵؾ���IV�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE5		"RSetingLN_Zone5"//�ӵؾ���V�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLN_ZONE6		"RSetingLN_Line"//�ӵؾ�����·���ȵ��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE1		"RSetingLL_Zone1"//������I�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE2		"RSetingLL_Zone2"//������II�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE3		"RSetingLL_Zone3"//������III�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE4		"RSetingLL_Zone4"//������IV�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE5		"RSetingLL_Zone5"//������V�ε��趨ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETINGLL_ZONE6		"RSetingLL_Line"//��������·���ȵ��趨ֵ

#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE1		"XSetingLN_Zone1"//�ӵؾ���I�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE2		"XSetingLN_Zone2"//�ӵؾ���II�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE3		"XSetingLN_Zone3"//�ӵؾ���III�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE4		"XSetingLN_Zone4"//�ӵؾ���IV�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE5		"XSetingLN_Zone5"//�ӵؾ���V�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLN_ZONE6		"XSetingLN_Line"//�ӵؾ�����·���ȵ翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE1		"XSetingLL_Zone1"//������I�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE2		"XSetingLL_Zone2"//������II�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE3		"XSetingLL_Zone3"//������III�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE4		"XSetingLL_Zone4"//������IV�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE5		"XSetingLL_Zone5"//������V�ε翹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETINGLL_ZONE6		"XSetingLL_Line"//��������·���ȵ翹��ֵ

//����ֵ
#define STT_MULTI_MACRO_ZONE1		2//I��
#define STT_MULTI_MACRO_ZONE2		3//II��
#define STT_MULTI_MACRO_ZONE3		4//III��
#define STT_MULTI_MACRO_ZONE4		5//IV��
#define STT_MULTI_MACRO_ZONE5		6//V��
#endif // STTMULTIMACRODISTANCEPARASDEFINE_H