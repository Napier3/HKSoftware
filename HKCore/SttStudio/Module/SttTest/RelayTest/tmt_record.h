#ifndef TMT_RECORD_H
#define TMT_RECORD_H

#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"

#define IECSIZE_MAX  64
typedef struct tmt_record_para
{
public:
	CString       dest_mac;//aabbccddeeff
	CString       appid;//0x
	CString       port;//0-15
	CString       ntype;//1-sv,2-gse,3-ft3

	void init()
	{
		dest_mac="AABBCCDDEEFF";
		appid="4001";
		port="2";
		ntype="1";
	}

	tmt_record_para()	{}
	virtual ~tmt_record_para(){}
}tmt_RecordPara;

typedef struct tmt_record_paras
{
public:
	tmt_RecordPara       m_paras[IECSIZE_MAX];
	int           m_mode;//0-detect,1-record
	int           m_nSubNumber;	

	void init(long nSubNumber = IECSIZE_MAX)
	{
		m_nSubNumber=nSubNumber;
		m_mode=0;
		for(int i=0;i<nSubNumber;i++)
		{
			m_paras[i].init();
		}
	}

	tmt_record_paras(){}
	virtual ~tmt_record_paras(){}
}tmt_RecordParas;

typedef struct tmt_record_test
{
public:
	tmt_RecordParas       m_oRecordPara;

	void init(long nSubNumber = IECSIZE_MAX)
	{
		m_oRecordPara.init(nSubNumber);
	}

	tmt_record_test()	{}
	virtual ~tmt_record_test(){}
}tmt_RecordTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_Record();
void stt_init_paras(tmt_RecordParas *pParas);
void stt_xml_serialize(tmt_RecordPara &oPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_RecordParas *pPara, CSttXmlSerializeBase *pXmlSierialize);
#endif // TMT_RECORD_H

