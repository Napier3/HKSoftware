#ifndef TMT_IED_TEST_H
#define TMT_IED_TEST_H
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../Common/tmt_common_def.h"
#include "../Common/tmt_adjust_sys_parameter.h"

#define MAX_IO_SIZE 40  //8+32

//0-延时测试 1-SOE测试 2-风暴测试 3-复归
#define  DelayMode  0
#define  SOEMode    1
#define  RepeatMode 2

//Paras
typedef struct{
	unsigned int nTmHigh;				//高电平时间长度毫秒
	unsigned int nTmLow;				//低电平时间长度毫秒
	unsigned int nflipCnt;				//翻转次数
}Drv_BoPara;

typedef struct{
	unsigned int nModule;			//模块编号
	unsigned int nBinOut[2];				//开出初始值
	unsigned int nType[2];			//实验类型 0其它，1为SOE实验
	Drv_BoPara param[64];
	unsigned int nDelayTime;//故障前时间
	unsigned int nBeginTime[64];//间隔时间
}Drv_SoeItem;

typedef struct{
	unsigned int nModuleCnt;		//模块数
	unsigned int tm_h;		//持续时间秒值
	unsigned int tm_l;		//持续时间纳秒值
	Drv_SoeItem item[ADJUST_MAX_MODULE_COUNT+1];
}Drv_SoePara;

//Results
typedef struct{
	unsigned int module;			//模块编号
	unsigned int bo[2];				//开出值
	unsigned int bi[2];				//开入值
}Drv_SoeResultItem;

typedef struct{
	unsigned int nType;			//结果类型 1：开始   2：停止	3：开出变位	4：开入变位
	unsigned int nModuleCnt;
	unsigned int tm_h;			//时间秒
	unsigned int tm_l;			//时间纳秒
	Drv_SoeResultItem item[ADJUST_MAX_MODULE_COUNT+1];
}Drv_SoeResults;

typedef struct tmt_ied_para
{
public:		
	tmt_BinaryOut    m_binOut[256];

	void init()
	{
		for(int i=0;i<256;i++)
		{
			m_binOut[i].init();
		}
	}

	tmt_ied_para(){}
	virtual ~tmt_ied_para(){}
}tmt_IEDPara;

typedef struct tmt_ied_paras
{
public:
	int              m_nFaultPreTime;//故障前时间
	int              m_nOutputTime;//状态间隔时间 毫秒
	int              m_nBoKeepTime;//开出保持时间 毫秒
	int              m_nDataMode;//加量方式 0-gse2bin,1-bo2gse 2-gse2bin复归 3-bo2gse复归
	int              m_nTestType;//实验类型 0-延时测试 1-SOE测试 2-风暴测试
	int              m_nRepeatCount;//风暴重复次数
	int              m_nStateCount;

	tmt_IEDPara      m_otmt_IEDPara[256];

	void init()
	{
		m_nOutputTime=1000;
		m_nBoKeepTime=0;
		m_nDataMode=0;
		m_nTestType=0;
		m_nRepeatCount=0;
		m_nStateCount=256;
		for(int i=0;i<m_nStateCount;i++)
		{
			m_otmt_IEDPara[i].init();
		}
	}

	tmt_ied_paras(){}
	virtual ~tmt_ied_paras(){}
}tmt_IEDParas;

typedef struct tmt_ied_test
{
public:
	tmt_IEDParas       m_oIEDParas;

	void init()
	{		
		m_oIEDParas.init();
	}

	tmt_ied_test()	{}
	virtual ~tmt_ied_test(){}
}tmt_IEDTest;

void stt_xml_serialize_write_IEDTest();
void stt_xml_serialize(tmt_IEDParas *oParas, CSttXmlSerializeBase *pXmlSierialize);

#endif // TMT_TIMEMEASURE_TEST_H

