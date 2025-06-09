#ifndef STTMULTIMACRODIFFCBOPDEFINE_H
#define STTMULTIMACRODIFFCBOPDEFINE_H

#define STT_MULTI_MACRO_DIFFCBOP_PARAS_GRID_ID 	        "DiffCBOp-Grid"

#define DIFFCBOP_FAULT_TYPE_AN                                                 0//�迹��Ĺ������Ͷ���
#define DIFFCBOP_FAULT_TYPE_BN                                                 1
#define DIFFCBOP_FAULT_TYPE_CN                                                 2
#define DIFFCBOP_FAULT_TYPE_ABN                                                3
#define DIFFCBOP_FAULT_TYPE_BCN                                                4
#define DIFFCBOP_FAULT_TYPE_CAN                                                5
#define DIFFCBOP_FAULT_TYPE_ABC                                                6


#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_AN         "FaultType_AN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_BN         "FaultType_BN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_CN         "FaultType_CN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_ABN        "FaultType_ABN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_BCN        "FaultType_BCN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_CAN        "FaultType_CAN"
#define STT_MULTI_MACRO_DIFFCBOP_FaultType_Items_ID_ABC        "FaultType_ABC"


//QDistanceResultEstimateDlg	���ܲ����༭ҳ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE					"FaultType"			//��������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTLOCATION				"FaultLocation"		//���ϵ�λ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CURENT					"Current"			//����(A)
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FREP						"Freq"				//Ƶ��(Hz)
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_KCAL						"Kcal"				//�Ƿ�����ƽ��ϵ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKPH				"Kph"				//��ѹ����ѹ��ƽ��ϵ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVVOL				"Uh"				//��ѹ����ѹ����ѹ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCUR				"Inh"				//��ѹ����ѹ������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCT				"CTh"				//��ѹ����ѹ��CT���
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKVA				"SN"				//��ѹ�������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVKPM				"Kpm"				//��ѹ����ѹ��ƽ��ϵ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVVOL				"Um"				//��ѹ����ѹ����ѹ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCUR				"Inm"				//��ѹ����ѹ������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCT				"CTm"				//��ѹ����ѹ��CT���
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVKPL				"Kpl"				//��ѹ����ѹ��ƽ��ϵ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVVOL				"Ul"				//��ѹ����ѹ����ѹ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCUR				"Inl"				//��ѹ����ѹ������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCT				"CTl"				//��ѹ����ѹ��CT���
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SETTING					"Setting"			//����ֵ
//#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM					"AbsErrSum"			//�������(S) +
//#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE				"AbsErrReduce"		//�������(S) -
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM					"Trip_AbsErrPos"	//�������(S) +
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE				"Trip_AbsErrNeg"		//�������(S) -
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR				"RelErr"			//������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE					"ErrorType"			//�������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_DEFAULT					"0"					//ȱʡֵ

//QDiffProtectionParasDlg	ͨ�ò���ҳ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREPARETIME			"PrepareTime"			//׼��ʱ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PREFAULTTIME			"PreFaultTime"			//����ǰʱ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIME				"FaultTime"				//����ʱ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTIMEMARGIN		"FaultTimeMargin"		//����ʱ��ԣ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ACTIONHOLDTIME		"ActionHoldTime"		//�����󱣳�ʱ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH					"WindH"					//��ѹ�����������ʽ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM					"WindM"					//��ѹ�����������ʽ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL					"WindL"					//��ѹ�����������ʽ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE			"PhCorrectMode"			//����ѡ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND				"AdoptWind"				//��������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSEL					"InSel"					//��׼����
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSET					"InSet"					//�趨ֵ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STEP					"Step"					//���Ծ���
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG1					"Vg1"					//Ua1��Ub1��Uc1
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_VG2					"Vg2"					//Ua2��Ub2��Uc2
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHM		"AroundClockNumHM"		//��-�������ӵ���
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_AROUNDCLOCKNUMHL		"AroundClockNumHL"		//��-�������ӵ���
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSGROUPMODE		"TransGroupMode"		//��������֮��ǲ�(�ӵ���)
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS			"BalanceTerms"			//ƽ��ϵ������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT					"CTStarPoint"			//CT����
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH				"IbiasCal"				//�ƶ�����
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1					"Factor1"				//K1
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2					"Factor2"				//K2
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COMBINEFEATURE		"ComBineFeature"		//�������/��������
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ZEROSEQELIMITYPE		"ZeroSeqElimiType"		//����������ʽ
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_EARTHING				"Earthing"				//���Ե��Ƿ�ӵ�
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBSIMULATION			"CBSimulation"			//��·��ģ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBTRIPTIME			"CBTripTime"			//��բʱ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CBCLOSETIME			"CBCloseTime"			//��բʱ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE			"Coordinate"			//����

//QDiffCBOpBinarysDlg		���롢����ҳ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_A						"A"			//����A
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B						"B"			//����B
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_C						"C"			//����C
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_D						"R"			//����D
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_E						"E"			//����E
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_F						"F"			//����F
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_G						"G"			//����G
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_H						"H"			//����H
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B01					"_B01"		//��̬����1״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B02					"_B02"		//��̬����2״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B03					"_B03"		//��̬����3״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B04					"_B04"		//��̬����4״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B05					"_B05"		//��̬����5״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B06					"_B06"		//��̬����6״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B07					"_B07"		//��̬����7״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_B08					"_B08"		//��̬����8״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB01					"_FaultB01"	//����̬����1״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB02					"_FaultB02"	//����̬����2״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB03					"_FaultB03"	//����̬����3״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB04					"_FaultB04"	//����̬����4״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB05					"_FaultB05"	//����̬����5״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB06					"_FaultB06"	//����̬����6״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB07					"_FaultB07"	//����̬����7״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FB08					"_FaultB08"	//����̬����8״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BINLOGIC				"_AndOr"	//�����߼�

#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SELECT				"Select"	//ѡ��
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STATE					"State"		//״̬
#define STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TESTRSLT				"TestRslt"	//���Խ��
typedef enum{
	DIFF_ID_DELETEITEM_DLG = 0,//ɾ��������Ŀ
	DIFF_ID_CLEARSELRESULT = 1//������Խ��
}STT_MULTI_MACRO_DIFFCBOPTYPE;

#endif
