#pragma once

#include "../tmt_state_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_OVERCURRENT_SETTING_NUM                     5
#define TMT_OVERCURRENT_TESTNAME_LEN	64
#define TMT_OVERCURRENT_GROUPID_LEN		32

typedef struct tmt_voltage_pnv_paras :public tmt_StateParas
{
public:
	float	m_fTSetting;		//装置故障动作时间定值
    float   m_fFaultTime;//故障时间
    float   m_fPreFaultTime;//故障前时间
    int       m_nFaultTrigMode;//故障触发方式
    int       m_nOutputSwitchMode;
    float   m_fTimeTrig;
    float   m_fOutputHoldTime;

    long    m_nBinSelect;//开入量选择第几组   0-ABCD 1-EFGH 0
    long    m_nInputState[8];//开入量状态  0:单跳;1：三跳;2：重合
    int     m_nBout[4];//开出

	float  m_fVolAmp[8];//常态及故障态电压幅值Ua\Ub\Uc\Uz
	float  m_fVolAng[8];//常态及故障态电压相位Ua\Ub\Uc\Uz
    float  m_fCurAmp[6];//常态及故障态电流幅值Ia\Ib\Ic
    float  m_fCurAng[6];//常态及故障态电流相位Ia\Ib\Ic

public:
    virtual void init(int nStateNumbers)
	{
        tmt_StateParas::init(nStateNumbers);
		m_fTSetting = 5.0f;
        m_nBinSelect = 0;
        m_nOutputSwitchMode =  0;
        m_fTimeTrig = 0.0f;
        m_fOutputHoldTime = 0.01f;

		for (int nIndex = 0;nIndex<8;nIndex++)
		{
			m_fVolAmp[nIndex] = 57.74f;
			m_fVolAng[nIndex] = 0.0f;
		}
        for (int nIndex = 0;nIndex<6;nIndex++)
        {
            m_fCurAmp[nIndex] = 0.0f;
        }

		m_fVolAng[1] = -120.0f;
		m_fVolAng[2] = 120.0f;
		m_fVolAng[5] = -120.0f;
		m_fVolAng[6] = 120.0f;

        m_fCurAng[0] = 0.0f;
        m_fCurAng[1] = -120.0f;
        m_fCurAng[2] = 120.0f;
        m_fCurAng[3] = 0.0f;
        m_fCurAng[4] = -120.0f;
        m_fCurAng[5] = 120.0f;
	}

}tmt_VoltagePnvParas;
typedef struct tmt_voltage_pnv_results :public tmt_StateResults
{
public:
    int m_nBinSwitchCount[3];
    float m_fTimeBinAct[3];
    void init()
    {
        for(int i = 0;i<3;i++)
        {
            m_nBinSwitchCount[i] = 0;
            m_fTimeBinAct[i] = 0.0f;
        }
    }
}tmt_VoltagePnvResults;
typedef struct tmt_voltage_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_VoltagePnvParas m_oVoltageParas;
    tmt_VoltagePnvResults m_oVoltageResults;
    void init(long nStateNumbers)
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_VoltageTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oVoltageParas.init(nStateNumbers);
        m_oVoltageResults.init();
    }

    tmt_voltage_pnv_test(){	init(2);}
    virtual ~tmt_voltage_pnv_test(){}

}tmt_VoltagePnvTest;

void stt_init_paras(tmt_VoltagePnvParas *pParas);
void stt_init_paras(tmt_VoltagePnvResults *pParas);

void stt_xml_serialize_Voltage_Pnv(tmt_VoltagePnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Voltage_Pnv(tmt_VoltagePnvResults *pParas, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_VoltagePnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize);


