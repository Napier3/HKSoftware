#pragma once
#include "../Common/tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

#define U2Power_U2M     0//切到主电源
#define U2Power_U2S     1//切到备电源
#define U2Power_U2MS    2//主备同时有效

#define Mode_4Ch  0//4路输出模式
#define Mode_aH   1//合并单路A输出模式
#define Mode_bH   2//合并单路B输出模式
#define Mode_cH   3//合并单路C输出模式
#define Mode_0H   4//合并单路0输出模式

#define Board_S1   1//切换到间隔板1输出
#define Board_S2   2//切换到间隔板2输出
#define Board_S3   3//切换到间隔板3输出
#define Board_S4   4//切换到间隔板4输出
#define Board_S5   5//切换到间隔板5输出
#define Board_S6   6//切换到间隔板6输出
#define Board_S7   7//切换到间隔板7输出
#define Board_S8   8//切换到间隔板8输出

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
	tmt_BinaryOut   m_binOut[8];//主板开关量
	float           m_fOutputTime;//输出时间,最小1秒
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
    tmt_BinaryOut   m_binOut[16];//主板开关量
    float           m_fOutputTime;//输出时间,最小1秒
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

