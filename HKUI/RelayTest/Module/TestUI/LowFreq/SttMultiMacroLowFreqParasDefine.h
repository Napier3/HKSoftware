#ifndef STTMULTIMACROLOWFREQPARASDEFINE_H
#define STTMULTIMACROLOWFREQPARASDEFINE_H

#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTVALUE	        "LowFreqAct"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTTIME	        "LowFreqTime"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_SLIPTRIP	        "LowFreqDfdt"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_VBLOCK	        "LowFreqULock"
#define STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_IBLOCK	        "LowFreqILock"
//QLOWFREQResultEstimateDlg	���ܲ���ҳ��

//����ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE		"FAct"			//����ֵ������-����ֵ(����ֵ)
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_CUR			"Ilow"				//����ֵ������-����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_HOlDTIME		"HoldTime"			//����ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RELERR		"HzActVal_RelErr"			//����ֵ������-������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ABSERR		"HzActVal_AbsErr"			//����ֵ������-�������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RSLTEVAL      "HzActVal_ErrorLogic"         //��������߼�
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART 	"Fstart"		//����ֵ������-Ƶ����ʼֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND		"Fend"			//����ֵ������-Ƶ�ʽ���ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP		"Fstep"			//����ֵ������-Ƶ�ʱ仯����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_DVDT			"dvdt"				//����ֵ������-Ƶ�ʻ���

//����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING		"FActTime"			//����ʱ�������-����ʱ�䶨ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_CUR			"Ilow"				//����ʱ�������-����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FSETTING		"FAct"			//����ʱ�������-Ƶ�ʶ���ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_HOlDTIME		"HoldTime"			//����ʱ�������-����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RELERR			"Ttrip_RelErr"			//����ʱ�������-������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRPOS		"Ttrip_AbsErrPos"			//����ʱ�������-���������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_ABSERRNEG	"Ttrip_AbsErrNeg"			//����ʱ�������-���������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RSLTEVAL	    "Ttrip_ErrorLogic"          //��������߼�
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_FREQEND		"Fend"			//����ʱ�������-Ƶ�ʽ���ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_DFDT			"dvdt"				//����ʱ�������-Ƶ�ʻ���
//�������ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING		"DvdtClose"		//�������ֵ������-���ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_CUR				"Ilow"				//�������ֵ������-����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_HOlDTIME			"HoldTime"			//�������ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RELERR			"Dfdt_RelErr"			//�������ֵ������-������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_ABSERR			"Dfdt_AbsErr"			//�������ֵ������-�������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RSLTEVAL		    "Dfdt_ErrorLogic"         //��������߼�
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_FREQEND			"FreqEnd"			//�������ֵ������-Ƶ�ʱ仯��ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART			"BeginVal"		//�������ֵ������-����仯ʼֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND			"EndVal"			//�������ֵ������-����仯��ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP			"Step"			//�������ֵ������-����仯����

//�͵�ѹ����ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING		"Ulow"		//�͵�ѹ����ֵ������-�͵�ѹ����ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_CUR					"Ilow"				//�͵�ѹ����ֵ������-����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_HOlDTIME			"HoldTime"			//�͵�ѹ����ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VAR					"UVariable"				//�͵�ѹ����ֵ������-��ѹ�仯��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RELERR				"Ulow_RelErr"				//�͵�ѹ����ֵ������-������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_ABSERR				"Ulow_AbsErr"				//�͵�ѹ����ֵ������-�������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RSLTEVAL		    "Ulow_ErrorLogic"           //��������߼�
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTART				"BeginVal"				//�͵�ѹ����ֵ������-��ѹ�仯��ʼֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VEND				"EndVal"				//�͵�ѹ����ֵ������-��ѹ�仯����ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VSTEP				"Step"				//�͵�ѹ����ֵ������-��ѹ�仯����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_DFDT				"Dfdt"				//�͵�ѹ����ֵ������-Ƶ�ʻ���
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_FREQEND				"RampTo"			//�͵�ѹ����ֵ������-Ƶ�ʱ仯��ֵ

//�͵�������ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING		"Ilow"		//�͵�������ֵ������-�͵�������ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_HOlDTIME			"HoldTime"			//�͵�������ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_VAR					"IVariable"				//�͵�������ֵ������-���������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RELERR				"Ilow_RelErr"				//�͵�������ֵ������-������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ABSERR				"Ilow_AbsErr"				//�͵�������ֵ������-�������
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RSLTEVAL		    "Ilow_ErrorLogic"           //��������߼�
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTART				"BeginVal"				//�͵�������ֵ������-�����仯��ʼֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IEND				"EndVal"				//�͵�������ֵ������-�����仯����ֵ
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_ISTEP				"Step"				//�͵�������ֵ������-�����仯����
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_DFDT				"Dfdt"				//�͵�������ֵ������-Ƶ�ʻ���
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_FREQEND				"RampTo"			//�͵�������ֵ������-Ƶ�ʱ仯��ֵ

//QLOWFREQCommonParasDlg	ͨ�ò���ҳ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_HoldTime               "HoldTime"          //����ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_PREFAULTTIME			"PreFaultTime"		//��̬ʱ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_TIMEZERO				"DfdtTiming"			//��ʱ���
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE				"USetMode"          //������ѹѡ��:�����ߵ�ѹ�������ѹ

//QLOWFREQBinarysDlg		���롢����ҳ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B01						"_Bout1"			//����1״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B02						"_Bout2"			//����2״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B03						"_Bout3"			//����3״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B04						"_Bout4"			//����4״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B05						"_Bout5"			//����5״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B06						"_Bout6"			//����6״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B07						"_Bout7"			//����7״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B08						"_Bout8"			//����8״̬
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_AndOr						"_AndOr"			//�����߼�
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_A							"_BinSelectA"		//����Aѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_B							"_BinSelectB"		//����Bѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_C							"_BinSelectC"		//����Cѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_D							"_BinSelectR"		//����Rѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_E							"_BinSelecta"		//����aѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_F							"_BinSelectb"		//����bѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_G							"_BinSelectc"		//����cѡ��
#define STT_MULTI_MACRO_LOWFREQ_PARAS_ID_H							"_BinSelectr"		//����rѡ��

//������
#define STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_SELECT                 "Select"		//ѡ��
#define STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_STATE					"State"			//״̬
#define STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_TESTRSLT				"TestRslt"		//���Խ��

typedef enum{
LOWFREQ_ID_PsuLowFreqAct = 0,   
LOWFREQ_ID_PsuLowFreqTime = 1,   
LOWFREQ_ID_PsuLowFreqDfdt = 2,  
LOWFREQ_ID_PsuLowFreqULock = 3,     
LOWFREQ_ID_PsuLowFreqILock = 4,       
}STT_MULTI_MACRO_LOWFREQTYPE;

typedef enum{
	LOWFREQ_ID_VType_Line = 0,   
	LOWFREQ_ID_VType_Phase = 1,  
}STT_MULTI_MACRO_VTYPE;

#endif // STTMULTIMACROLOWFREQPARASDEFINE_H