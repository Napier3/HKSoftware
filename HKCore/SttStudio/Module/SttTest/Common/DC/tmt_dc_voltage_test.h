#pragma once

#include "../Impedance/tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_DCVOLTAGE_SETTING_NUM     4
#define TMT_DCVOLTAGE_TESTNAME_LEN	  64
#define TMT_DCVOLTAGE_GROUPID_LEN	  32

typedef struct tmt_dc_voltage_paras
{
public:
    double m_fUSetting;           //����������ѹ
	int m_nFaultChannel;        //����ͨ��
	int m_nCurrentChannel;      //����ͨ��
	double m_fCurrent;          //����(A)
	float m_fRate;              //����
	float m_fMaxFaultTime;      //������ʱ��
	float m_fPreFaultTime;		//����ǰʱ��
	float m_fMarginTime;        //����ʱ��ԣ��
	float m_fPostFaultTime;		//�������������ʱ��  2.000f
	int   m_nFaultTrigMode;		//���ϴ�����ʽ S1=ʱ��,S2=����,S3=��������H������,S4=GPS 0(0:ʱ�䴥��,1:��������,2:����ӵ㷭ת����,3:GPS����)
    tmt_time m_tGps;
	BOOL  m_bCBSimulation;		//��·��ģ��  S1=��ģ��,S2=ģ�� 0(0:��ģ��,1:ģ��)
	float m_fCBTripTime;		//��բʱ��	200ms��ģ���·��ʱ�ķ�բʱ�䣩
	float m_fCBCloseTime;		//��բʱ��	100ms��ģ���·��ʱ�ĺ�բʱ�䣩
	double m_fPreFaultVol;      //����ǰ��ѹ
	double m_fPreFaultCur;      //����ǰ����

	float   m_fSettingOverVol[TMT_DCVOLTAGE_SETTING_NUM];//��ѹ��������ֵ
	float   m_fSettingTime[TMT_DCVOLTAGE_SETTING_NUM];//��ѹ��������ʱ��
	tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int m_nBinLogic; //0 1�߼����
	BOOL m_nVolType; //0 ����ѹ 1�͵�ѹ



	float  m_fVolAmp[8];//��̬������̬��ѹ��ֵUa\Ub\Uc\Uz
	float  m_fVolAng[8];//��̬������̬��ѹ��λUa\Ub\Uc\Uz

	//2022.5.23 caoxc ������Ŀ����
	char m_pszTestName[TMT_DCVOLTAGE_TESTNAME_LEN];
	//2022.5.26 caoxc ���ӷ���id
	char m_pszGroupID[TMT_DCVOLTAGE_GROUPID_LEN];

	double m_fR, m_fX;  //�迹ƽ����迹ֵ�����ڻ�ͼ
	float m_fImpAngle[2];		//�迹��(��һ�ι����迹���ڶ��ι����迹) m_fPhi



public:
	virtual void init()
	{
		m_fUSetting = 2.85f;
		m_nFaultChannel = 0;
		m_nCurrentChannel = 0;
		m_fCurrent = 0.000f;
		m_fRate = 1.0f;
		m_fMaxFaultTime = 0.200f;
		m_fPreFaultTime = 2.000f;		//����ǰʱ��
		m_fMarginTime = 0.2f;
		m_fPostFaultTime = 2.000f;		//�������������ʱ��  2.000f
		m_nFaultTrigMode = 0;					//���ϴ�����ʽ S1=ʱ��,S2=����,S3=��������H������,S4=GPS 0
		m_bCBSimulation = 0;		//��·��ģ��  S1=��ģ��,S2=ģ�� 0
		m_fCBTripTime = 0.200f;		//��բʱ��	200ms
		m_fCBCloseTime = 0.100f;		//��բʱ��	100ms
		m_fPreFaultVol = 57.74f;
		m_fPreFaultCur = 0.00f;
		m_nBinLogic = 1;
		m_nVolType = 0;


		m_fSettingOverVol[0] = 8.0f;
		m_fSettingOverVol[1] = 7.0f;
		m_fSettingOverVol[2] = 6.0f;
		m_fSettingOverVol[3] = 5.0f;
		m_fSettingTime[0] = 0.0f;
		m_fSettingTime[1] = 0.5f;
		m_fSettingTime[2] = 1.0f;
		m_fSettingTime[3] = 1.5f;

		m_fImpAngle[0] = 90;			//�迹�� m_fPhi
		m_fImpAngle[1] = 90;
		//2022.5.23 caoxc
		memset(m_pszTestName, 0, TMT_DCVOLTAGE_TESTNAME_LEN);
		//2022.5.26 caoxc
		memset(m_pszGroupID, 0, TMT_DCVOLTAGE_GROUPID_LEN);
		for (int nIndex = 0;nIndex<8;nIndex++)
		{
			m_fVolAmp[nIndex] = 57.74f;
			m_fVolAng[nIndex] = 0.0f;
		}


		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_binInEx[i].init();
		}

		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_binOutEx[i].init();
		}

		m_fVolAng[1] = -120.0f;
		m_fVolAng[2] = 120.0f;

		m_fVolAng[5] = -120.0f;
		m_fVolAng[6] = 120.0f;
	}
	void CopyOwn(tmt_dc_voltage_paras* pDest)
	{
		pDest->m_fUSetting = m_fUSetting;
		pDest->m_nFaultChannel = m_nFaultChannel;
		pDest->m_nCurrentChannel = m_nCurrentChannel;
		pDest->m_fCurrent = m_fCurrent;
		pDest->m_fRate = m_fRate;
		pDest->m_fMaxFaultTime = m_fMaxFaultTime;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_fPostFaultTime = m_fPostFaultTime;
		pDest->m_nFaultTrigMode = m_nFaultTrigMode;
		pDest->m_bCBSimulation = m_bCBSimulation;
		pDest->m_fCBTripTime = m_fCBTripTime;
		pDest->m_fCBCloseTime = m_fCBCloseTime;
		pDest->m_fPreFaultVol = m_fPreFaultVol;
		pDest->m_fPreFaultCur = m_fPreFaultCur;
		pDest->m_nVolType = m_nVolType;

		for(int nIndex = 0; nIndex < TMT_DCVOLTAGE_SETTING_NUM; nIndex++)
		{
			pDest->m_fSettingOverVol[nIndex] = m_fSettingOverVol[nIndex];
			pDest->m_fSettingTime[nIndex] = m_fSettingTime[nIndex];
		}

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_binIn[nIndex] = m_binIn[nIndex];
			pDest->m_binOut[nIndex] = m_binOut[nIndex];
			pDest->m_binInEx[nIndex] = m_binInEx[nIndex];
			pDest->m_binOutEx[nIndex] = m_binOutEx[nIndex];
		}
		
		for (int nIndex = 0; nIndex < 8; nIndex++)
		{
			pDest->m_fVolAmp[nIndex] = m_fVolAmp[nIndex];
			pDest->m_fVolAng[nIndex] = m_fVolAng[nIndex];
		}

		for (int nIndex = 0; nIndex < 2; nIndex++)
		{
			pDest->m_fImpAngle[nIndex] = m_fImpAngle[nIndex];
		}
		pDest->m_fVolAng[1] = m_fVolAng[1];
		pDest->m_fVolAng[2] = m_fVolAng[2];

		pDest->m_fVolAng[5] = m_fVolAng[5];
		pDest->m_fVolAng[6] = m_fVolAng[6];
	}
	int GetSttTrigMode()
	{
		int nSttTrigMode = TMT_MDSTATE_TIMETRIGGER;

		switch (m_nFaultTrigMode)
		{
		case 0:		// ʱ��
			nSttTrigMode = TMT_MDSTATE_TIMETRIGGER; 
			break;
		case 1:		// ����
			nSttTrigMode = TMT_MDSTATE_MEARSURETRIGGER; 
			break;
		case 2:		// ����ӵ�
			nSttTrigMode = TMT_MDSTATE_BINTRIGGER; 
			break;
		case 3:		// GPS
			nSttTrigMode = TMT_MDSTATE_GPSBTRIGGER; 
			break;
		default:
			break;
		}

		return nSttTrigMode;
	}


}tmt_DcVoltageParas;

typedef struct tmt_dc_voltage_paras_ex :public tmt_DcVoltageParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];//����������ѹ
	char m_maxTSetting[PARAS_RSLT_EXPR_LEN];//������ʱ��

	virtual void init()
	{
		tmt_DcVoltageParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_maxTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_DcVoltageParasEx;

typedef struct tmt_dc_voltage_results :public tmt_ImpedanceResults
{
public:
	float    m_fZshort;    //��·�迹
	float    m_fIShortAngle;   //��·������λ�� 
	float	 m_fFirstTripTime[8];//���붯��ʱ��
	float	 m_fRecloseTime;
	float	 m_fTripTime;   //����ʱ��
	long m_nActA,m_nActB,m_nActC,m_nActD;
	int		m_nActID[MAX_BINARYIN_COUNT];//��ԭ��m_nActA��B��C��ͳһΪ����
	float		m_fSecondTripTime;//����ٶ���
	long    m_nActAcc;//����ٶ�������
	float m_fFaultCurrent,m_fFaultVol;	//���ϵ�������ѹ
	float m_fDcVoltage;
	float m_fImpAngle;


public:
	virtual void init()
	{
		m_fZshort = 0.0f;
		m_fIShortAngle = 90.0f;
		m_fRecloseTime = 0;
		m_fTripTime = 0;
		m_fSecondTripTime = 0;
		m_nActA = m_nActB = m_nActC = 0;
		m_nActAcc = 0;
		m_fDcVoltage = m_fFaultVol = m_fFaultCurrent = 0;
		m_fImpAngle = 0;


		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			m_nActID[nIndex] = 0;

		}

		for(int i=0;i<4;i++)
		{
			m_fFirstTripTime[i] = m_fFirstTripTime[i+4] = 0;
			m_fRecordTime[i] = 0;
			m_fReturnTime[i] = m_fReturnTime[i+4] = 0;
		}

		tmt_ImpedanceResults::init();
	} 

	void CopyOwn(tmt_dc_voltage_results* pDest)
	{
		pDest->m_fZshort = m_fZshort;
		pDest->m_fIShortAngle = m_fIShortAngle;
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fTripTime = m_fTripTime;
		pDest->m_nActA = m_nActA;
		pDest->m_nActB = m_nActB;
		pDest->m_nActC = m_nActC;
		pDest->m_nActD = m_nActD;
		pDest->m_nActAcc = m_nActAcc;
		pDest->m_fFaultCurrent = m_fFaultCurrent;
		pDest->m_fFaultVol = m_fFaultVol;
		pDest->m_fDcVoltage = m_fDcVoltage;
		pDest->m_fImpAngle = m_fImpAngle;
	}
	void SetFault1TripTime(long nTripIndex,long nInputMapState,float fValue,bool bHasMapReclose)
	{
		if (fValue<=0)
		{
			return;
		}

		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_THREE)
		{
			m_fFirstTripTime[0] = fValue;
			m_fFirstTripTime[1] = fValue;
			m_fFirstTripTime[2] = fValue;
		}
		else if (nInputMapState == STT_IMPEDANCE_BIN_STATE_SINGLE)
		{
			m_fFirstTripTime[nTripIndex-bHasMapReclose] = fValue;
		}
	}

	void SetFault2TripTime(long nTripIndex,long nInputMapState,float fValue)
	{
		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_RECLOCE)
			return;

		if (fValue>=m_fSecondTripTime)
		{
			m_fSecondTripTime = fValue;
		}
	}

	float GetFirstTripTime()
	{
		float fValue = 0.0f;

		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			if (fValue<m_fFirstTripTime[nIndex])
			{
				fValue = m_fFirstTripTime[nIndex];
			}
		}

		return fValue;
	}

}tmt_DcVoltageResults;

typedef struct tmt_dc_voltage_test : public TMT_PARAS_HEAD
{
public:
	tmt_DcVoltageParasEx m_oDcVoltageParas;
	tmt_DcVoltageResults m_oDcVoltageResults;
	char m_szName[MAX_NAME_LEN];

	virtual void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_DCVoltageTest);//DCVoltageTest
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		memset(m_szName, 0, MAX_NAME_LEN);
		memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

		m_oDcVoltageParas.init();
		m_oDcVoltageResults.init();
	}

    tmt_dc_voltage_test()
    {
        init();
    }
    virtual void clear_result()
    {
        m_oDcVoltageResults.init();
    }
	virtual ~tmt_dc_voltage_test(){}

}tmt_DcVoltageTest;


void stt_init_paras(tmt_DcVoltageParas *pParas);
void stt_init_paras_ex(tmt_DcVoltageParasEx *pParas);
void stt_init_results(tmt_DcVoltageResults *pResults);

void stt_xml_serialize_DcVoltage(tmt_DcVoltageParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DcVoltage_ex(tmt_DcVoltageParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DcVoltageResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DcVoltageTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_write_DcVoltageTest();

