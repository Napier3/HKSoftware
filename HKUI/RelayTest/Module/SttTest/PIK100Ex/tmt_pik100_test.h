#pragma once
#include"../../SttTestBase/SttXmlSerialize.h"
#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0X0020
#define BIT6  0X0040
#define BIT7  0X0080
#define BIT8  0X0100
#define BIT9  0X0200
#define BIT10  0X0400
#define BIT11  0X0800
typedef struct tmt_pik100_DAValue
{
	/*<!--共有42个K，每一个K有17个状态，分别对应了 0表示所有的继电器都断开，从1到16依次表示
	24V;24VGND;   48V;48VGND;   220V;220VGND;   500V;500VGND
		1A;1AGND   Vsense；VsenseGND     Isense；IsenseGND     KR；KRGND   -->*/
	unsigned int StateStart;// 1启动正弦波，0停止正弦波
	unsigned int K1;//
	unsigned int K2;//
	unsigned int K3;//

	unsigned int K4;//
	unsigned int K5;//
	unsigned int K6;//

	unsigned int K7;//
	unsigned int K8;//
	unsigned int K9;//

	unsigned int K10;//
	unsigned int K11;//
	unsigned int K12;//

	unsigned int K13;//
	unsigned int K14;//
	unsigned int K15;//

	unsigned int K16;//
	unsigned int K17;//
	unsigned int K18;//

	unsigned int K19;//
	unsigned int K20;//
	unsigned int K21;//

	unsigned int K22;//
	unsigned int K23;//
	unsigned int K24;//

	unsigned int K25;//
	unsigned int K26;//
	unsigned int K27;//

	unsigned int K28;//
	unsigned int K29;//
	unsigned int K30;//

	unsigned int K31;//
	unsigned int K32;//
	unsigned int K33;//

	unsigned int K34;//
	unsigned int K35;//
	unsigned int K36;//

	unsigned int K37;//
	unsigned int K38;//
	unsigned int K39;//

	unsigned int K40;//
	unsigned int K41;//
	unsigned int K42;//
	unsigned int Addr010c;

	unsigned int VsenseFlag;//
	unsigned int V24VIsenseFlag;//
	unsigned int V220VIsenseFlag;//
	unsigned int StateReadyFlag;//
	unsigned int CountFlag;//0不计数，正常上传。1实验开启时开始计数，5S后上传数据和消息
	void init()
	{
		StateStart = 0;//
		K1=0;//
		K2=0;//
		K3=0;//

		K4=0;//
		K5=0;//
		K6=0;//

		K7=0;//
		K8=0;//
		K9=0;//

		K10=0;//
		K11=0;//
		K12=0;//

		K13=0;//
		K14=0;//
		K15=0;//

		K16=0;//
		K17=0;//
		K18=0;//

		K19=0;//
		K20=0;//
		K21=0;//

		K22=0;//
		K23=0;//
		K24=0;//

		K25=0;//
		K26=0;//
		K27=0;//

		K28=0;//
		K29=0;//
		K30=0;//

		K31=0;//
		K32=0;//
		K33=0;//

		K34=0;//
		K35=0;//
		K36=0;//

		K37=0;//
		K38=0;//
		K39=0;//

		K40=0;//
		K41=0;//
		K42=0;//
		Addr010c = 0;
		VsenseFlag=0;//

		V24VIsenseFlag=0;//
		V220VIsenseFlag = 0;
		StateReadyFlag = 0;
		CountFlag = 0;
	}
}tmt_pik100_DA;

typedef struct tmt_pik100_para
{
public:
	tmt_pik100_DA m_oDA;
public:
	void init()
	{
		m_oDA.init();
	}

	tmt_pik100_para()	{}
}tmt_Pik100Para;

typedef struct tmt_pik100_test
{
public:
	tmt_Pik100Para    m_oPik100Para;

	void init()
	{
		m_oPik100Para.init();
	}
	tmt_pik100_test() {}
}tmt_Pik100Test;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_PtTest();
void stt_init_paras(tmt_Pik100Para *pPara);
void stt_xml_serialize(tmt_Pik100Para *pPara, CSttXmlSerializeBase *pXmlSierialize);

