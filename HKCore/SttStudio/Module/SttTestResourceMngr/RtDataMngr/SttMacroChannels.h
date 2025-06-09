#pragma once
#include "../../SttTest/Common/tmt_rtdata_def.h"
#include "../../SttCmd/SttParas.h"
#include "../../SttCmd/SttChMap.h"
#include "../../../../Module/MemBuffer/TCycleMemBuffer.h"

#define STT_RT_DATA_MODE_NONE                                             0
#define STT_RT_DATA_MODE_ASYN                                             1
#define STT_RT_DATA_MODE_SYN                                              2

#define STT_MACRO_CH_TYPE_VOL                                             0
#define STT_MACRO_CH_TYPE_CUR                                             1

#define STT_HISDATA_MEMBUFFER_MAX_NUM	                             	8000   //��ʷ����ѭ��������󳤶�

#define STT_MACRO_ID_FAULT_CH_VOL											"Uf"
#define STT_MACRO_ID_FAULT_CH_CUR											"If"//��������ͨ��



typedef CTCycleMemBuffer<tmt_RtDataCh> CCycleMemBuffer_rtdata;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttMacroChannel :public CExBaseObject
{
public:
	CSttMacroChannel(void);
	virtual ~CSttMacroChannel(void);

public:
	long m_nChannelType;  //��ʾͨ�����ͣ������ѹ�������ȣ����ͳһ����
	CSttChMap *m_pHdMaps;//�������Դ������ȫ��Ӳ����Դͨ��
	tmt_rtdata_ch m_oRtDataCh;  //����ͷ��ʱ���ṹ�壬ʵʱ����

	CCycleMemBuffer_float m_oHisMagBuf;		//��ʷ���ݷ�ֵ
	CCycleMemBuffer_rtdata m_oHisDataBuf;	//��ʷ����		//yyj add 2021-08-25

	CString m_strHisTitle;
	float *m_pfHisMagMax;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMacroChGroup :public CExBaseList
{
public:
	CMacroChGroup(void);
	virtual ~CMacroChGroup(void);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttMacroChannels :public CExBaseList
{
public:
	CSttMacroChannels(void);
	virtual ~CSttMacroChannels(void);

public:
	CCycleMemBuffer_double m_oHisTimesBuf;  ////��ʷ���ݵľ���ʱ��
	CCycleMemBuffer_double m_oHisRealTimesBuf;//��ʷ���ݵ����ʱ��
	//����ͷ������Ϊ��ʷ���ݾ���ʱ�̣�
	CExBaseList m_oListGroups;//��������Ϊȫ������,�˴�Ϊ������ʽ��ʵ��ͨ������CMacroChGroup��ɾ��

	void InitGroup();//��ʼ������ͨ������
	void ClearAllChs();
	void ClearHisDatas();
	CSttMacroChannel* AddNewCh(const CString &strName,const CString &strID,CSttChMap *pHdMaps);

	CExBaseList m_oVolChListRef;//ȫ����ѹͨ����Դ����
	CExBaseList m_oCurChListRef;//ȫ������ͨ����Դ����
	CSttMacroChannel m_oUfCh;//zhouhj 2023.12.20 �������ڹ��ϵ�ѹ�����ϵ���ͨ��
	CSttMacroChannel m_oIfCh;

protected:
	void ClearGroups();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttBinChlMngr :public CExBaseList
{
public:
	CSttBinChlMngr(void);
	virtual ~CSttBinChlMngr(void);

public:
	CCycleMemBuffer_double m_oHisTimesBuf;  ////��ʷ���ݵľ���ʱ��
	CCycleMemBuffer_double m_oHisRealTimesBuf;//��ʷ���ݵ����ʱ��

	//Ĭ��8ͨ�����롢������ʷ����
	CCycleMemBuffer_BYTE m_arrHisBinInBuf[MAX_BINARYIN_COUNT];
	CCycleMemBuffer_BYTE m_arrHisBinOutBuf[MAX_BINARYOUT_COUNT];

	//��չ��������ʷ����
	CCycleMemBuffer_BYTE m_arrHisBinInExBuf[MAX_ExBINARY_COUNT];
	CCycleMemBuffer_BYTE m_arrHisBinOutExBuf[MAX_ExBINARY_COUNT];
};