#ifndef TMT_BISYNC_TEST_H
#define TMT_BISYNC_TEST_H
#include "tmt_state_test.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"

typedef struct tmt_bisync_para
{
public:
	int		  m_nOutputTime;

	void init()
	{
		m_nOutputTime=60;//s
	}

	tmt_bisync_para(){}
	virtual ~tmt_bisync_para(){}
}tmt_BiSyncPara;

typedef struct tmt_bisync_test
{
public:
	tmt_BiSyncPara       m_oBiSyncPara;

	void init()
	{
		m_oBiSyncPara.init();
	}

	tmt_bisync_test()	{}
	virtual ~tmt_bisync_test(){}
}tmt_BiSyncTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_BiSyncTest();
void stt_init_paras(tmt_BiSyncPara *pParas);
void stt_xml_serialize(tmt_BiSyncPara *pPara, CSttXmlSerializeBase *pXmlSierialize);

#endif // TMT_BISYNC_TEST_H

