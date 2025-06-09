#pragma once
#include "../Common/tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

#define U2Power_U2M     0//�е�����Դ
#define U2Power_U2S     1//�е�����Դ
#define U2Power_U2MS    2//����ͬʱ��Ч

#define Mode_4Ch  0//4·���ģʽ
#define Mode_aH   1//�ϲ���·A���ģʽ
#define Mode_bH   2//�ϲ���·B���ģʽ
#define Mode_cH   3//�ϲ���·C���ģʽ
#define Mode_0H   4//�ϲ���·0���ģʽ

#define Board_S1   1//�л��������1���
#define Board_S2   2//�л��������2���
#define Board_S3   3//�л��������3���
#define Board_S4   4//�л��������4���
#define Board_S5   5//�л��������5���
#define Board_S6   6//�л��������6���
#define Board_S7   7//�л��������7���
#define Board_S8   8//�л��������8���

typedef struct tmt_pik08_para
{
	int m_nU2Power;
	int m_nVoltMode;
	int m_nCurrMode;
	int m_nVoltBoardSel;
	int m_nCurrBoardSel;
public:
	void init()
	{
		m_nU2Power = U2Power_U2M;
		m_nVoltMode = Mode_4Ch;
		m_nCurrMode = Mode_4Ch;
		m_nVoltBoardSel = Board_S1;
		m_nCurrBoardSel = Board_S1;
	}

	tmt_pik08_para()	{}
}tmt_Pik08Para;

typedef struct tmt_pid01_para
{
	tmt_Pik08Para   m_oPik08Para[2];
	tmt_BinaryOut   m_binOut[8];//���忪����
	float           m_fOutputTime;//���ʱ��,��С1��
public:
	void init()
	{
		m_fOutputTime = 1.0f;
		m_oPik08Para[0].init();
		m_oPik08Para[1].init();
		for(int i=0;i<8;i++)
		{
			m_binOut[i].init();
		}
	}

	tmt_pid01_para()	{}
}tmt_Pid01Para;

typedef struct tmt_pid01_test
{
public:
	tmt_Pid01Para    m_oPid01Para;

	void init()
	{
		m_oPid01Para.init();
	}
	tmt_pid01_test() {}
}tmt_Pid01Test;

typedef struct tmt_pid16_para
{
    tmt_BinaryOut   m_binOut[16];//���忪����
    float           m_fOutputTime;//���ʱ��,��С1��
public:
    void init()
    {
        m_fOutputTime = 1.0f;
        for(int i=0;i<16;i++)
        {
            m_binOut[i].init();
        }
    }

    tmt_pid16_para()	{}
}tmt_Pid16Para;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_Pid01Test();
void stt_init_paras(tmt_Pid01Para *pPara);
void stt_xml_serialize(tmt_Pid01Para *pPara, CSttXmlSerializeBase *pXmlSierialize);

