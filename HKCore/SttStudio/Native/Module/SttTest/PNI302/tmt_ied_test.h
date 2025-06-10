#ifndef TMT_IED_TEST_H
#define TMT_IED_TEST_H
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../Common/tmt_common_def.h"
#include "../Common/tmt_adjust_sys_parameter.h"

#define MAX_IO_SIZE 40  //8+32

//0-��ʱ���� 1-SOE���� 2-�籩���� 3-����
#define  DelayMode  0
#define  SOEMode    1
#define  RepeatMode 2

//Paras
typedef struct{
	unsigned int nTmHigh;				//�ߵ�ƽʱ�䳤�Ⱥ���
	unsigned int nTmLow;				//�͵�ƽʱ�䳤�Ⱥ���
	unsigned int nflipCnt;				//��ת����
}Drv_BoPara;

typedef struct{
	unsigned int nModule;			//ģ����
	unsigned int nBinOut[2];				//������ʼֵ
	unsigned int nType[2];			//ʵ������ 0������1ΪSOEʵ��
	Drv_BoPara param[64];
	unsigned int nDelayTime;//����ǰʱ��
	unsigned int nBeginTime[64];//���ʱ��
}Drv_SoeItem;

typedef struct{
	unsigned int nModuleCnt;		//ģ����
	unsigned int tm_h;		//����ʱ����ֵ
	unsigned int tm_l;		//����ʱ������ֵ
	Drv_SoeItem item[ADJUST_MAX_MODULE_COUNT+1];
}Drv_SoePara;

//Results
typedef struct{
	unsigned int module;			//ģ����
	unsigned int bo[2];				//����ֵ
	unsigned int bi[2];				//����ֵ
}Drv_SoeResultItem;

typedef struct{
	unsigned int nType;			//������� 1����ʼ   2��ֹͣ	3��������λ	4�������λ
	unsigned int nModuleCnt;
	unsigned int tm_h;			//ʱ����
	unsigned int tm_l;			//ʱ������
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
	int              m_nFaultPreTime;//����ǰʱ��
	int              m_nOutputTime;//״̬���ʱ�� ����
	int              m_nBoKeepTime;//��������ʱ�� ����
	int              m_nDataMode;//������ʽ 0-gse2bin,1-bo2gse 2-gse2bin���� 3-bo2gse����
	int              m_nTestType;//ʵ������ 0-��ʱ���� 1-SOE���� 2-�籩����
	int              m_nRepeatCount;//�籩�ظ�����
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

