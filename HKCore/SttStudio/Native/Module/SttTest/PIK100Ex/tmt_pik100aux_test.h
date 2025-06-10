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
typedef struct tmt_pik100aux_DAValue
{

	bool AdjCloseLoopMode;//设定此模式为校准模式，或者正常闭环模式

	void init()
	{
		AdjCloseLoopMode = 0;
	}
}tmt_pik100aux_DA;

typedef struct tmt_pik100aux_para
{
public:
	tmt_pik100aux_DA m_oauxDA;
public:
	void init()
	{
		m_oauxDA.init();
	}

	tmt_pik100aux_para()	{}
}tmt_Pik100AuxPara;

typedef struct tmt_pik100aux_test
{
public:
	tmt_Pik100AuxPara    m_oPik100AuxPara;

	void init()
	{
		m_oPik100AuxPara.init();
	}
	tmt_pik100aux_test() {}
}tmt_Pik100AuxTest;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_AuxTest();
void stt_init_paras(tmt_Pik100AuxPara *pPara);
void stt_xml_serialize(tmt_Pik100AuxPara *pPara, CSttXmlSerializeBase *pXmlSierialize);

