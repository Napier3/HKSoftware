#ifndef STTMULTIMACRODISTANCEPARASDEFINE_H
#define STTMULTIMACRODISTANCEPARASDEFINE_H

#define STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_ZPhi	        "DistanceZ-Phi"
#define STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_RX	        "DistanceR-X"

//QDistanceResultEstimateDlg	���ܲ���ҳ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE			"FaultType"			//��������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING			"ZSetting"			//�迹��ֵ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG				"ZAng"				//�迹��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE				"Rate"				//����
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE			"K0Mode"			//���򲹳�ϵ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR				"KlKr"				//���򲹳�ϵ��RE/RL
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX				"AngKx"				//���򲹳�ϵ��XE/XL
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_IMPREFTYPE		"ImpRefType"		//�迹�ο���ʽ
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT		"FaultCurrent"		//��·����
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION	"FaultDirection"	//���Ϸ���
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1		"FaultType1"		//��������
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING			"TSetting"			//ʱ�䶨ֵ
//�������
//������

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

//QDistanceBinarysDlg		���롢����ҳ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT				"BinSelect"	//������ѡ��
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_A						"A"			//����A
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_B						"B"			//����B
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_C						"C"			//����C
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_D						"D"			//����D
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_E						"E"			//����E
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_F						"F"			//����F
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_G						"G"			//����G
#define STT_MULTI_MACRO_DISTANCE_PARAS_ID_H						"H"			//����H
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

#endif // STTMULTIMACRODISTANCEPARASDEFINE_H