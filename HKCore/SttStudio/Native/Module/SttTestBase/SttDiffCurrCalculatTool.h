#pragma once
#include "SttComplexp.h"


#define DIFF_CURR_CAL_CHANNEL_NUM_3I                       3//
#define DIFF_CURR_CAL_CHANNEL_MAX                          6

#define ElecRailway_TransType_0_YV                         0
#define ElecRailway_TransType_1_YD11                       1//��ת��
#define ElecRailway_TransType_2_Single                     2
#define ElecRailway_TransType_3_YDD                        3
#define ElecRailway_TransType_4_Scott1                     4
#define ElecRailway_TransType_5_VV1                        5
#define ElecRailway_TransType_6_VX                         6
#define ElecRailway_TransType_7_YA                         7
#define ElecRailway_TransType_8_ThreeVV                    8
#define ElecRailway_TransType_9_Scott2                     9
#define ElecRailway_TransType_10_Scott3                    10
#define ElecRailway_TransType_11_VV2                       11
#define ElecRailway_TransType_12_Scott4                    12
#define ElecRailway_TransType_13_ThreeVV2                  13
#define ElecRailway_TransType_14_ThreeVV3                  14
#define ElecRailway_TransType_15_ThreeYV2                  15//��ת��
#define ElecRailway_TransType_16_Scott5                    16
#define ElecRailway_TransType_17_YD11_YT                   17//��Y�����ת��
#define ElecRailway_TransType_18_ThreeYV2_YT               18//��Y�����ת��




typedef struct
{
	float famptitude;//fuzhi
	float fphase;
	float ffre;
}ChannelUI_Diff;


class CSttDiffCurrCalculatTool
{
public:
	CSttDiffCurrCalculatTool(void);
	virtual ~CSttDiffCurrCalculatTool(void);
	//��ȫ����������ͳһ��ʼ��
	void Init();

	//��ʼ��ϵͳ����,�������������ĵ���ֵ������Ļ���Ƶ��
    void InitSysParas(float fIOutmax = 100.0f, float fFreq = 50.0f);
	//��ʼ��ȫ������ϼ������(��ȥƽ��ϵ������)
	void InitParas6I(int nInSel,float fIbase,int nSearchMode,bool bMinAxis,int nAngleMode,int nIbiasCal,int nWindH,int nWindM,int nWindL,int nWindSide,
		float fFactor1,float fFactor2,int nConnectMode,int nPhase,bool bCTStarPoint,int nJXFactor);//��ʼ��ȫ����Ա����
	//�ֶ�����ƽ��ϵ����ָ��
	void InitParas_SetBalanceFactors(float fKph_Set,float fKpm_Set,float fKpl_Set);
	//ͨ����ѹ������,�Զ�����ƽ��ϵ��
	void InitParas_AutoCalBalanceFactors(float fSn,float fUh,float fUm,float fUl,float fCTPh,float fCTSh,float fCTPm,float fCTSm,float fCTPl,float fCTSl);

	void InitParas5I_ElecRailway(float fIbase,int nSearchMode,bool bMinAxis,int nIbiasCal,float fKpl,
		int nPhase,bool bCTStarPoint,int nRWCTconnect,int nTranSort,int nKphMode);//��ʼ������ǣ����
	void CurrentCal_ElecRailway(float *fId,float fIr,float &fIalpha,float &fIbeta);//�����ǣ����Ĳ���ֵ

	void InitParas3I_BP2();//zhouhj 20211211  ��ʼ��BP2��ʽ���ʲ����
	BOOL CurrentCal3I_BP2(float *fId,float fIr_Id);//���������BP2��ʽ���ʲ����

	 void  CurrentCal(float *fId,float fIr);
	ChannelUI_Diff* GetChannelCurrents(){return m_arryoCurrent;}

	void GetKps(float& fKph,float& fKpm,float& fKpl){ fKph = m_fKph; fKpm = m_fKpm; fKpl = m_fKpl;} //yyj 20211029 
	void GetKjx(float& fKjxh,float& fKjxl){ fKjxh = m_fKjxh; fKjxl = m_fKjxl; } //yyj 20211029
	void GetIet(float& fIet){ fIet = m_fIet; } //yyj 20211029

	static BOOL IsPhaseA(int nPhase){return (nPhase == APhase);}
	static BOOL IsPhaseB(int nPhase){return (nPhase == BPhase);}
	static BOOL IsPhaseC(int nPhase){return (nPhase == CPhase);}
	static BOOL IsPhaseABC(int nPhase){return (nPhase == ABCPhase);}
	static BOOL IsPhaseAB(int nPhase){return (nPhase == ABPhase);}
	static BOOL IsPhaseBC(int nPhase){return (nPhase == BCPhase);}
	static BOOL IsPhaseCA(int nPhase){return (nPhase == CAPhase);}


protected:
	int   GetMethod(int nClock,int nAngleMode);
	 int   GetSign(int nClock,int nAngleMode);

	 void  CalKjx();

	 void  CalKpx();
	 bool CurrentCal_SP(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh);	// Added by ZM 20180504		������ϼ���(�ѷ�ֹ)
	 bool CurrentCal_SP_D(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180816		������ϡ���У�����ǲ�ת�ǣ�
	 bool CurrentCal_SP_Y(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180816		�������Y��У�����ǲ�ת�ǣ�
	 bool CurrentCal_IP_D(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180504		�����ϡ���У�����ǲ�ת�ǣ�
	 bool CurrentCal_IP_Y(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180504		������Y��У�����ǲ�ת�ǣ�


	 enum TestPhasor_type {
		 APhase = 0,
		 BPhase = 1,
		 CPhase = 2,
		 ABCPhase = 3,
		 ABPhase = 4,
		 BCPhase = 5,
		 CAPhase = 6
	 };

	 enum BaseCurrentSelect {
		 HighSideSecondaryCurrent = 0,
		 SettingValue = 1,
		 AllSideCurrent = 2
	 };


private:
	void CalTranSort0_YV(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort1_YD11(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort2_Single(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort3_YDD(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort4_Scott1(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort5_VV1(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort6_VX(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort7_YA(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort8_ThreeVV(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort9_Scott2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort10_Scott3(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort11_VV2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort12_Scott4(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort13_ThreeVV2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort14_ThreeVV3(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort15_ThreeYV2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort16_Scott5(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort17_YD11_YT(float fIfault,float fReimbCurr_YD11,float &fIalpha,float &fIbeta);
	void CalTranSort18_ThreeYV2_YT(float fIfault,float fReimbCurr_YD11,float &fIalpha,float &fIbeta);



	ChannelUI_Diff m_arryoCurrent[DIFF_CURR_CAL_CHANNEL_MAX];
//	ChannelUI_Diff m_harmCurrent[DIFF_CURR_CAL_CHANNEL_MAX];

	 float m_fIOutmax;//��������������ֵ(�������ֻ�����,��ֵ���Ժܴ�;����ģ�����,��Ҫ�Ը�ֵ������)

	 int	m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-�����ζ����	ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
	 float	m_fIbase;	//��׼�����趨ֵ
	int m_nSearchMode; //0���ַ�,1�����ƽ�
//	float m_fResultId;//������Ĳ����
//	bool m_bResultJudge;//�о�
//	float m_fTtrip;//��������ʱ��
//	bool m_bJudge1;// �����о�1
//	bool m_bJudge2;//�����о�2
//	int m_nRunSer;//�������,��ֵ=1��
//	int m_nCurrentSerial;//������Ŀ�б���š���0��ʼ��
// 	float m_fIdiff1;//�ֵ1
// 	float m_fIdiff2;//�ֵ2
//	float m_fIdiff;//�����
	float m_fKjxh;//��ѹ�����ϵ��
	float m_fKjxl;//��ѹ�����ϵ��
	float m_fKph;
	float m_fKpl;//�ֱ�Ϊ��ѹ��͵�ѹ��ƽ��ϵ��
	float m_fKpm;


	bool m_bMinAxis;//=FALSE,TRUE,�ֱ��ʾ������ֵ������ֵ
	int m_nAngleMode;//У����ʽ��0,1,2=��У��,����У��,Y��У��;
	int m_nIbiasCal;//�ƶ����̡�0,1,2,3,4,5=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1,(|I1|+|I2|*K2)/K1,max(|I1|,|I2|),(|Id-|I1|-|I2||)/K1,|I2|,��(K1*I1*I2*Cos(��))
	int m_nWindH;//��ѹ�����������ʽ,0,1="Y","��"
	int m_nWindM;//��ѹ�����������ʽ,0,1="Y","��"
	int m_nWindL;//:��ѹ�����������ʽ,0,1="Y","��"
	int m_nWindSide;//�������飬0,1,2=�ߵͣ����У��е�
	float m_fFactor1;//��Ӧ�ƶ������е�K1
	float m_fFactor2;//��Ӧ�ƶ������е�K2
	float m_fIet;//��׼����,����ֵ����Ϊ����ֵʱ,��ֵ�̶�Ϊ1,��Ϊ����ֵʱ,��ֵ��Ҫ��������
	int m_nConnectMode;//:��������֮��ǲ�ӵ�����=0-12,"12��","1��","2��","3��","4��","5��","6��","7��","8��","9��","10��","11��"
	//    bool m_bConnectFactor;//FALSE,TRUE=���������������ʽ,�������������ʽ;
	int m_nPhase;//:���,0,1,2�ֱ��ʾΪA,B,C���� ,3λABC����
	bool m_bCTStarPoint;//,CT���ԣ�FALSE,TRUE�ֱ��ʾΪ�����Ժ͸�����
	int m_nKcal;//=0,1�ֱ��ʾƽ��ϵ���Զ�������ֶ�����,�ֶ�����ƽ��ϵ��ʱ�����е�ѹ��ƽ��ϵ���ֱ�Ϊ:Kph,Kpm��Kpl;
	int m_nJXFactor;//=0,1;�ֱ��ǲ��������������ʽ�Ϳ������������
	float m_fSn;//��ѹ�������
	float m_fUh;//��ѹ����ѹ����ѹ
	float m_fUm;
	float m_fUl;
	//CT���=CTPh/CTSh
	float m_fCTPh;
	float m_fCTSh;
	float m_fCTPm;
	float m_fCTSm;
	float m_fCTPl;
	float m_fCTSl;

	float m_fKpm_Set;// �ֶ������ô�ϵ��
	float m_fKph_Set;
	float m_fKpl_Set;
// 	float m_fIbias1;
// 	float m_fIbias2;
	float m_fFreq;//��ǰƵ��

	int m_nRWCTconnect_ElecRailway;//����ǣ������� ��ѹ��CT���߷�ʽ
	int m_nTranSort_ElecRailway;//����ǣ�������   ��ѹ��������ʽ
	int m_nKphMode_ElecRailway;//����ǣ�������    ƽ��ϵ�����㷽ʽ
	float m_fKph_ElecRailway;//����ǣ������ϵ��
};

