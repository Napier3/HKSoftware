#ifndef STTMULTIMACROLOWVOLPARASDEFINE_H
#define STTMULTIMACROLOWVOLPARASDEFINE_H

#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTVALUE	        "LowVolAct"
#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTTIME	        "LowVolTime"
#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_SLIPTRIP	        "LowVolDvdt"
#define STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_IBLOCK				"LowVolILock"
//QLOWVOLResultEstimateDlg	���ܲ���ҳ��

//����ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE		"UAct"			//����ֵ������-����ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_CUR			"IAct"				//����ֵ������-����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_HOlDTIME		"HoldTime"			//����ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR		"TripVol_RelErr"			//����ֵ������-������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR		"TripVol_AbsErr"			//����ֵ������-�������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART 	"Vstart"		//����ֵ������-�ߵ�ѹ�仯��ʼֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND		"Vend"			//����ֵ������-�ߵ�ѹ�仯����ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP		"Vstep"			//����ֵ������-�ߵ�ѹ�仯����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_DVDT			"dvdt"				//����ֵ������-��ѹ����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VAR		 "FaultType"				 //����ֵ������-��ѹ�仯��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RSLTEVAL      "TripVol_ErrorLogic"        //��������߼�
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_UVARIABLE      "UVariable"        //��ѹ�仯��

//����ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_TSETTING		"UActTime"			//����ʱ�������-����ʱ�䶨ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_CUR				"IAct"				//����ʱ�������-����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_FSETTING		"UAct"			//����ʱ�������-��ѹ����ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_HOlDTIME		"HoldTime"			//����ʱ�������-����ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR			"Ttrip_RelErr"			//����ʱ�������-������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS		"Ttrip_AbsErrPos"			//����ʱ�������-���������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG		"Ttrip_AbsErrNeg"			//����ʱ�������-���������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_VEND			"Vend"					//����ʱ�������-��ѹ�仯��ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_DVDT			"dvdt"				//����ʱ�������-�ߵ�ѹ����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RSLTEVAL	    "Ttrip_ErrorLogic"           //��������߼�
//�������ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING		"DvdtClose"		//�������ֵ������-���ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_CUR				"IAct"				//�������ֵ������-����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_HOlDTIME			"HoldTime"			//�������ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR			"TripDvdt_RelErr"			//�������ֵ������-������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR			"TripDvdt_AbsErr"			//�������ֵ������-�������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VEND			"Vend"			//�������ֵ������-��ѹ�仯��ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP			"Step"		//�������ֵ������-����仯����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART			"BeginVal"			//�������ֵ������-����仯ʼֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND			"EndVal"			//�������ֵ������-����仯��ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RSLTEVAL		    "TripDvdt_ErrorLogic"       //��������߼�
//�͵�������ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING		"IAct"		//�͵�������ֵ������-�͵�������ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_HOlDTIME			"HoldTime"			//�͵�������ֵ������-����ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VAR					"IVariable"				//�͵�������ֵ������-���������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR				"Ilow_RelErr"				//�͵�������ֵ������-������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR				"Ilow_AbsErr"				//�͵�������ֵ������-�������
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTART				"BeginVal"				//�͵�������ֵ������-�����仯��ʼֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IEND				"EndVal"				//�͵�������ֵ������-�����仯����ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ISTEP				"Step"				//�͵�������ֵ������-�����仯����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_VEND				"Vend"				//�͵�������ֵ������-��ѹ�仯��ֵ
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_DVDT				"dvdt"				//�͵�������ֵ������-��ѹ����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RSLTEVAL		    "Ilow_ErrorLogic"           //��������߼�

//QLOWVOLCommonParasDlg	ͨ�ò���ҳ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_HoldTime               "HoldTime"          //����ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_PREFAULTTIME			"PreFaultTime"		//��̬ʱ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_IPRETIME				"IAct"				//��̬����
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_TIMEZERO				"DvdtTiming"			//��ʱ���
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_USETMODE				"USetMode"          //������ѹѡ��:�����ߵ�ѹ�������ѹ

//QLOWVOLBinarysDlg		���롢����ҳ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B01						"_Bout1"			//����1״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B02						"_Bout2"			//����2״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B03						"_Bout3"			//����3״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B04						"_Bout4"			//����4״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B05						"_Bout5"			//����5״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B06						"_Bout6"			//����6״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B07						"_Bout7"			//����7״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID__B08						"_Bout8"			//����8״̬
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_AndOr						"_AndOr"			//�����߼�
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_A							"_BinSelectA"		//����Aѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_B							"_BinSelectB"		//����Bѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_C							"_BinSelectC"		//����Cѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_D							"_BinSelectR"		//����Rѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_E							"_BinSelecta"		//����aѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_F							"_BinSelectb"		//����bѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_G							"_BinSelectc"		//����cѡ��
#define STT_MULTI_MACRO_LOWVOL_PARAS_ID_H							"_BinSelectr"		//����rѡ��

//������
#define STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_SELECT                 "Select"		//ѡ��
#define STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_STATE					"State"			//״̬
#define STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_TESTRSLT				"TestRslt"		//���Խ��
typedef enum{
	LOWVOL_ID_PsuLowVolAct = 0,   
	LOWVOL_ID_PsuLowVolTime = 1,   
	LOWVOL_ID_PsuLowVolDfdt = 2,    
	LOWVOL_ID_PsuLowVolILock = 3,       
}STT_MULTI_MACRO_LOWVOLTYPE;

typedef enum{
	LOWVOL_ID_VType_Line = 0,   
	LOWVOL_ID_VType_Phase = 1,  
}STT_MULTI_MACRO_LOWVOLVTYPE;
#endif // STTMULTIMACROLOWVOLPARASDEFINE_H
