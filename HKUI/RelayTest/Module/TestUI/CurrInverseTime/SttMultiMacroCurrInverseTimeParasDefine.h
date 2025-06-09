#ifndef STTMULTIMACROCURRINVERPARASDEFINE_H
#define STTMULTIMACROCURRINVERPARASDEFINE_H

//#define STT_MACRO_ID_CurrInverseTime     "CurrInverseTime"

#define CURRINVERSE_FAULT_TYPE_AE                                                 0//�������Ͷ���
#define CURRINVERSE_FAULT_TYPE_BE                                                 1
#define CURRINVERSE_FAULT_TYPE_CE                                                 2
#define CURRINVERSE_FAULT_TYPE_AB                                                 3
#define CURRINVERSE_FAULT_TYPE_BC                                                 4
#define CURRINVERSE_FAULT_TYPE_CA                                                 5
#define CURRINVERSE_FAULT_TYPE_ABC                                                6
#define CURRINVERSE_FAULT_TYPE_3I0                                                7
#define CURRINVERSE_FAULT_TYPE_IAIBIC                                                8
#define CURRINVERSE_FAULT_TYPE_UAIA                                                9
#define CURRINVERSE_FAULT_TYPE_UAUB                                                10
#define CURRINVERSE_FAULT_TYPE_A                                                11
#define CURRINVERSE_FAULT_TYPE_B                                                12
#define CURRINVERSE_FAULT_TYPE_C                                                13

//���ڵ���,���������ͽ��з��ഴ���ļ���
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_AE         "CurrInverseTime-AE"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_BE         "CurrInverseTime-BE"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_CE         "CurrInverseTime-CE"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_AB         "CurrInverseTime-AB"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_BC         "CurrInverseTime-BC"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_CA         "CurrInverseTime-CA"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_ABC        "CurrInverseTime-ABC"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_3I0        "CurrInverseTime-3I0"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_IAIBIC        "CurrInverseTime-Ia+Ib+Ic"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_UAIA        "CurrInverseTime-Ua,Ia"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_UAUB        "CurrInverseTime-Va,Vb"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_A        "CurrInverseTime-A"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_B        "CurrInverseTime-B"
#define STT_MULTI_MACRO_CURRINVERSE_Items_ID_C       "CurrInverseTime-C"

//	���ܲ���ҳ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE			"FaultType"			//��������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt			"FaultVolt"			//��·��ѹ
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT			"FaultCurrent"			//����
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG			"FaultAngle"			//����̬��λ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre			"FaultFre"			//Ƶ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING			"SettingTime"			//����ʱ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS			"Ttrip_AbsErr_Pos"			//����ʱ������������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS			"Ttrip_AbsErr_Neg"			//����ʱ����Ը������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr			"Ttrip_RelErr"			//������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CMBFAULTVolt		"FaultVolType"		//���ϵ�ѹ���ͣ���·��ѹ��3U0��

//ͨ�ò���ҳ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFaultTime			"_PreFaultTime"		//����ǰʱ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_UPre				    "_UPre"			//����ǰ��ѹ
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IPre		            "_IPre"	   //����ǰ����
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle			    "PreAngle"			//����ǰ��λ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFre			        "PreFre"			//Ƶ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType			"RefValueType"		//��׼ֵ
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_In					"In"				//�����
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos				"CTPos"				//CT������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Ipu					"Ipu"				//��������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultTime			"FaultTime"			//����ʱ��ԣ��

//m_pAddMultiItemSelectDlg ѡ��ҳ�水����ʾ
#define STT_MULTI_MACRO_CurrInverTime_BTN_DELETESELITEM			_T("ɾ����ǰ")
#define STT_MULTI_MACRO_CurrInverTime_BTN_DELETEALLITEM			_T("ɾ��ȫ��")
#define STT_MULTI_MACRO_CurrInverTime_BTN_CLEARSELRESULT		_T("�����ǰ")
#define STT_MULTI_MACRO_CurrInverTime_BTN_CLEARALLRESULT		_T("���ȫ��")

//		���롢����ҳ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AndOr				"_AndOr"	//�����߼�
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A						"_BinSelectA"			//����A
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B						"_BinSelectB"			//����B
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C						"_BinSelectC"			//����C
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_D						"_BinSelectR"			//����D
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_E						"_BinSelecta"			//����E
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_F						"_BinSelectb"			//����F
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_G						"_BinSelectc"			//����G
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_H						"_BinSelectr"			//����H
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B01					"_Bout01"		//��̬����1״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B02					"_Bout02"		//��̬����2״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B03					"_Bout03"		//��̬����3״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B04					"_Bout04"		//��̬����4״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B05					"_Bout05"		//��̬����5״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B06					"_Bout06"		//��̬����6״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B07					"_Bout07"		//��̬����7״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B08					"_Bout08"		//��̬����8״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B1					"_Bout1"		//����̬����1״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B2					"_Bout2"		//����̬����2״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B3					"_Bout3"		//����̬����3״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B4					"_Bout4"		//����̬����4״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B5					"_Bout5"		//����̬����5״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B6					"_Bout6"		//����̬����6״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B7					"_Bout7"		//����̬����7״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B8					"_Bout8"		//����̬����8״̬

//QCurrInverAddMultDlg
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select				"Select"
//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt				"FaultVolt"	
//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG				"FaultAngle"
//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre				"FaultFre"	
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStart				"CurrentChangeStart"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeFinal				"CurrentChangeFinal"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStep			"CurrentChangeStep"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AN_CHECK						"FaultTypeA_Check"			
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BN_CHECK						"FaultTypeB_Check"			
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CN_CHECK						"FaultTypeC_Check"			
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AB_CHECK						"FaultTypeAB_Check"		
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BC_CHECK						"FaultTypeBC_Check"		
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CA_CHECK						"FaultTypeCA_Check"	
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABC_CHECK					"FaultTypeABC_Check"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IaIbIc_CHECK						"FaultTypeIa+Ib+Ic_Check"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_3I0_CHECK						"FaultType3I0_Check"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_I2_CHECK					"FaultTypeI2_Check"	
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A_CHECK					"FaultTypeA0_Check"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B_CHECK					"FaultTypeB0_Check"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C_CHECK					"FaultTypeC0_Check"//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle				"PreAngle"
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ErrorLogic				"Ttrip_ErrorLogic"
//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr				"Ttrip_RelErr"
//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS			"AbsErr_Plus"			//����ʱ������������
//#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS			"AbsErr_Minus"			//����ʱ����Ը������

#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_PreFaultTime			"_PreFaultTime"		//����ǰʱ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_UPre				    "_UPre"			//����ǰ��ѹ
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_IPre		            "_IPre"	   //����ǰ����
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_PreAngle			    "PreAngle"			//����ǰ��λ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_PreFre			        "PreFre"			//Ƶ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_RefValueType			"RefValueType"		//��׼ֵ
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_In					"In"				//�����
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_CTPos				"CTPos"				//CT������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_Ipu					"Ipu"				//��������
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_FaultTime			"FaultTime"			//����ʱ��ԣ��
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_A						"_BinSelectA"			//����A
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B						"_BinSelectB"			//����B
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_C						"_BinSelectC"			//����C
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_D						"_BinSelectD"			//����D
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_E						"_BinSelectE"			//����E
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_F						"_BinSelectF"			//����F
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_G						"_BinSelectG"			//����G
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_H						"_BinSelectH"			//����H
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_ANDOR					"_AndOr"			//�����߼�
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B01                     "_Bout01"		//��̬����1״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B02                     "_Bout02"		//��̬����2״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B03                     "_Bout03"		//��̬����3״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B04                     "_Bout04"		//��̬����4״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B05                     "_Bout05"		//��̬����5״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B06                     "_Bout06"		//��̬����6״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B07                     "_Bout07"		//��̬����7״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B08                     "_Bout08"		//��̬����8״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B1						"_Bout1"		//����̬����1״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B2						"_Bout2"		//����̬����2״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B3						"_Bout3"		//����̬����3״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B4						"_Bout4"		//����̬����4״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B5						"_Bout5"		//����̬����5״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B6						"_Bout6"		//����̬����6״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B7						"_Bout7"		//����̬����7״̬
#define STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B8						"_Bout8"		//����̬����8״̬

#define STT_MULTI_MACRO_CurrInverTime_PARAS_ID_DEFAULT					"0"

#endif // STTMULTIMACRODISTANCEPARASDEFINE_H