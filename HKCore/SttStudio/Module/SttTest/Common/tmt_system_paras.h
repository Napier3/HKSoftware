#pragma once

#include"../../SttTestBase/SttXmlSerialize.h"

typedef struct tmt_system_paras		// PSU ״̬�ڵݱ����
{
	int		m_nOutputMode;	//0-ģ�� 1-����   2-����+ģ��
	float	m_fVNom;			//�ֵ
	float	m_fINom;
	float	m_fFNom;
	float 	m_fStabTime;		//����ʱ��
	float	m_fVPrimary[4];		//PT���
	float	m_fVSecondary[4];
	float	m_fIPrimary[4];		//CT���
	float	m_fISecondary[4];

	int	m_nIecFormat;		//���������ʽ  0-IEC61850-9-2��1-IEC61850-9-1��2-IEC60044-8(����)��3-�ɼ������(�������)
	//4-���ź������5-�ɼ������(���)��6-�ɼ������(����)��7-IEC60044-8(����)��8-�����ɼ������(�е�����)
	int	m_nWSgnMode;		//���ź�������� 0-���źŲ������1-Va',...Ic'����Ϊ���ź� ԭm_nLLOutput
	int	m_n588InPort;		//IEC61588���տ� 0-7
	int	m_n588Syn;			//IEC61588ͬ������ 0-��ʱ����-��Ӧ 1-�Ե���ʱ
	int	m_nParaMode;		//��������ѡ�� 0-һ��ֵ 1-����ֵ ��m_bPrimaryPara�෴ ���õ��ĵط��Ѿ�ȫ����������
	int	m_nPkgOutMode;		//�������ѡ�� 0-һ��ֵ 1-����ֵ ��m_bPrimaryValue�෴ ���õ��ĵط��Ѿ�ȫ����������
	int	m_nBCodeMode;		//B���߼� 0-���߼� 1-���߼�
	int	m_nLoopMode;			//�������ӷ�ʽ 0-˫�� 1-����

	void init()
	{
		m_nOutputMode = 2;
		m_fVNom=57.735;
		m_fINom=1;
		m_fFNom=50.0f;
		m_fStabTime=0;

		for(int nIndex = 0;nIndex<4;nIndex++)
		{
			m_fVPrimary[nIndex] = 110.0f;
			m_fVSecondary[nIndex] = 100.0f;
			m_fIPrimary[nIndex] = 1000.0f;
			m_fISecondary[nIndex] = 1.0f;
			m_nIecFormat = 0;
			m_nWSgnMode = 0;
			m_n588InPort = 0;
			m_n588Syn = 0;
			m_nParaMode = 0;
			m_nPkgOutMode = 1;
			m_nBCodeMode = 0;
			m_nLoopMode = 0;
		}
	}

	tmt_system_paras(){}
	virtual ~tmt_system_paras(){}

	float PkgModePTRate(int nGroup)
	{
		float fPTRate = 1;

		if(m_nParaMode&&(!m_nPkgOutMode))//��������Ϊһ��ֵ���������Ϊ����ֵ
		{
			fPTRate = m_fVSecondary[nGroup]/(1000*m_fVPrimary[nGroup]);
		}
		else if((!m_nParaMode)&&m_nPkgOutMode)//��������Ϊ����ֵ���������Ϊһ��ֵ
		{
			fPTRate = 1000*m_fVPrimary[nGroup]/m_fVSecondary[nGroup];
		}

		return fPTRate;
	}

	float PkgModeCTRate(int nGroup)
	{
		float fCTRate = 1;

		if(m_nParaMode&&(!m_nPkgOutMode))//��������Ϊһ��ֵ���������Ϊ����ֵ
		{
			fCTRate = m_fISecondary[nGroup]/m_fIPrimary[nGroup];
		}
		else if((!m_nParaMode)&&m_nPkgOutMode)//��������Ϊ����ֵ���������Ϊһ��ֵ
		{
			fCTRate = m_fIPrimary[nGroup]/m_fISecondary[nGroup];
		}

		return fCTRate;
	}
}tmt_SystemParas;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_SystemParas();
void stt_init_paras(tmt_SystemParas *pParas);
void stt_xml_serialize(tmt_SystemParas *pParas, CSttXmlSerializeBase *pXmlSierialize);


