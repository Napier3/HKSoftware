#pragma once
#include"../../SttTestBase/SttXmlSerialize.h"

typedef struct tmt_pic200d_iotest
{
public:
    int m_nIO1[8];//1_IO
    int m_nIO2[16];//2_IO
    int m_nIO3[8];//3_IO
	void init()
	{
        for(int i = 0;i<8;i++)
        {
            m_nIO1[i] = 1;
            m_nIO3[i] = 1;
        }

        for(int i = 0;i<16;i++)
        {
            m_nIO2[i] = 1;
        }
	}
    tmt_pic200d_iotest() {}
}tmt_Pic200dIoTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize(tmt_Pic200dIoTest *pPara, CSttXmlSerializeBase *pXmlSierialize);
